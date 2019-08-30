//
//  DCBLib.cpp
//
//  WaveDAQ DCB Interface Library
//
//  Created by Stefan Ritt on 30/8/2019.
//

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <thread>
#include <cstring>
#include <algorithm>

#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <assert.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>

#ifdef __linux__
#include <linux/sockios.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <pthread.h>
#endif
#ifdef __APPLE__
#include <net/if_dl.h>
#include <pthread.h>
#endif

#include "WDBLib.h"
#include "register_map_wd2.h"
#include "WDBReg.h"

#define DCB_CMD_PORT_BIN          4000
#define DCB_CMD_PORT_ASCII        3000

int WDB::gBinSocket   = 0;
unsigned short WDB::udpSequenceNumber = 0; // sequence number to identify related send/acknowledge packets

//--------------------------------------------------------------------

// convert one data type into other, replaces *((float *)(&int))

template<typename T, typename U>
T access_as(U* p)
{
   T d;
   memcpy(&d, p, sizeof(d));
   return d;
}


//--------------------------------------------------------------------

DCB::DCB(std::string name, bool verbose)
{
   mDCBName = name;
   mVerbose = verbose;
   mLogfile = "";
   mSendBlocked = false;
   mReceiveTimeoutMs = cDefaultReceiveTimeoutMs;
   mTimingReferenceSignal = cTimingReferenceOff;
}

//--------------------------------------------------------------------

void DCB::WriteUDP(unsigned int ofs, std::vector<unsigned int> data)
{
   size_t i;
   fd_set readfds;
   struct timeval timeout;
   int    status, ms, retry;
   struct sockaddr_in client_addr;
   bool   bSuccess = false;

   udpSequenceNumber++;
   std::memcpy(&client_addr, mEthAddrBin, sizeof(client_addr));

   std::vector<unsigned char> writeBuf(8);
   std::vector<unsigned char> readBuf(1600);

   writeBuf[0] = 0x14; // Write32 command
   writeBuf[1] = 0;
   writeBuf[2] = udpSequenceNumber >> 8;
   writeBuf[3] = udpSequenceNumber & 0xFF;

   writeBuf[4] = (ofs >> 24) & 0xFF;
   writeBuf[5] = (ofs >> 16) & 0xFF;
   writeBuf[6] = (ofs >>  8) & 0xFF;
   writeBuf[7] = (ofs >>  0) & 0xFF;

   for (auto &d: data) {
      writeBuf.push_back((d >> 24) & 0xFF);
      writeBuf.push_back((d >> 16) & 0xFF);
      writeBuf.push_back((d >>  8) & 0xFF);
      writeBuf.push_back((d >>  0) & 0xFF);
   }

   auto startTime = std::chrono::high_resolution_clock::now();

   // retry max ten times
   for (retry=0 ; retry < 10 ; retry++) {

      // clear input queue
      do {
         FD_ZERO(&readfds);
         FD_SET(gBinSocket, &readfds);

         timeout.tv_sec = 0;
         timeout.tv_usec = 0;
         do {
            status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
         } while (status == -1); // don't return on interrupt

         if (!FD_ISSET(gBinSocket, &readfds))
            break;

         i = recv(gBinSocket, &readBuf[0], readBuf.size(), 0);
      } while (true);

      // send request
      i = sendto(gBinSocket,
                 &writeBuf[0],
                 writeBuf.size(),
                 0,
                 (struct sockaddr *)&client_addr,
                 sizeof(client_addr));

      if (i != writeBuf.size()) {
         if (this->mVerbose)
            std::cout << mWDBName << " send retry " << retry+1 << std::endl;
         continue;
      }

      // don't wait for reply for reset FPGA command
      if (mReceiveTimeoutMs < 0)
         return;

      // retrieve reply until acknowledge is found
      do {
         std::fill(readBuf.begin(), readBuf.end(), 0);

         FD_ZERO(&readfds);
         FD_SET(gBinSocket, &readfds);

         ms = mReceiveTimeoutMs;
         timeout.tv_sec = ms / 1000;
         timeout.tv_usec = (ms % 1000) * 1000;

         do {
            status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
         } while (status == -1);        /* dont return if an alarm signal was cought */

         if (!FD_ISSET(gBinSocket, &readfds))
            break;

         i = recv(gBinSocket, &readBuf[0], readBuf.size(), 0);
         assert(i > 0);

         // check for acknowledge
         bSuccess = readBuf[0] == 0x14 &&
                    readBuf[1] == 0x01 &&
                    readBuf[2] == ((udpSequenceNumber >> 8) & 0xFF) &&
                    readBuf[3] == (udpSequenceNumber & 0xFF);
         if (bSuccess)
            return;

      } while (1);


      if (this->mVerbose)
         std::cout << mWDBName << " retry " << retry+1 << std::endl;
   }

   if (this->mVerbose && retry > 0) {
      auto elapsed = std::chrono::high_resolution_clock::now() - startTime;
      std::cout << "Communication to " << mWDBName << " took " <<
         std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() <<
         " ms" << std::endl;

   }

   if (!bSuccess) {
      throw std::runtime_error(std::string("Error writing binary UDP data to "+mWDBName+"."));
      return;
   }
}

//--------------------------------------------------------------------

std::vector<unsigned int> DCB::ReadUDP(unsigned int ofs, unsigned int nReg)
{
   size_t i;
   fd_set readfds;
   struct timeval timeout;
   int    status, ms;
   struct sockaddr_in client_addr;
   bool   bSuccess = false;
   std::vector<unsigned int> result;

   udpSequenceNumber++;
   auto len = nReg * sizeof(unsigned int);
   std::memcpy(&client_addr, mEthAddrBin, sizeof(client_addr));

   std::vector<unsigned char> writeBuf(12);
   std::vector<unsigned char> readBuf(1600);

   writeBuf[ 0] = 0x24; // Read32 command
   writeBuf[ 1] = 0;
   writeBuf[ 2] = udpSequenceNumber >> 8;
   writeBuf[ 3] = udpSequenceNumber & 0xFF;

   writeBuf[ 4] = (ofs >> 24) & 0xFF;
   writeBuf[ 5] = (ofs >> 16) & 0xFF;
   writeBuf[ 6] = (ofs >>  8) & 0xFF;
   writeBuf[ 7] = (ofs >>  0) & 0xFF;

   writeBuf[ 8] = (len >> 24) & 0xFF;
   writeBuf[ 9] = (len >> 16) & 0xFF;
   writeBuf[10] = (len >>  8) & 0xFF;
   writeBuf[11] = (len >>  0) & 0xFF;

   // retry max ten times
   for (int retry=0 ; retry < 10 ; retry++) {

      // clear input queue
      do {
         FD_ZERO(&readfds);
         FD_SET(gBinSocket, &readfds);

         timeout.tv_sec = 0;
         timeout.tv_usec = 0;
         do {
            status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
         } while (status == -1); // don't return on interrupt

         if (!FD_ISSET(gBinSocket, &readfds))
            break;

         i = recv(gBinSocket, &readBuf[0], readBuf.size(), 0);
      } while (true);

      // send request
      i = sendto(gBinSocket,
                 &writeBuf[0],
                 writeBuf.size(),
                 0,
                 (struct sockaddr *)&client_addr,
                 sizeof(client_addr));

      if (i != writeBuf.size()) {
         if (this->mVerbose)
            std::cout << mWDBName << " send retry " << retry+1 << std::endl;
         continue;
      }

      // retrieve reply until acknowledge is found
      do {
         std::fill(readBuf.begin(), readBuf.end(), 0);

         FD_ZERO(&readfds);
         FD_SET(gBinSocket, &readfds);

         ms = mReceiveTimeoutMs;
         timeout.tv_sec = ms / 1000;
         timeout.tv_usec = (ms % 1000) * 1000;

         do {
            status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
         } while (status == -1);        /* dont return if an alarm signal was cought */

         if (!FD_ISSET(gBinSocket, &readfds))
            break;

         i = recv(gBinSocket, &readBuf[0], readBuf.size(), 0);
         assert(i > 0);

         // check for acknowledge
         bSuccess = readBuf[0] == 0x24 &&
                    readBuf[1] == 0x01 &&
                    readBuf[2] == ((udpSequenceNumber >> 8) & 0xFF) &&
                    readBuf[3] == (udpSequenceNumber & 0xFF);

         // check for data length (limited to one UDP frame at the moment)
         bSuccess = bSuccess && (i == len + 4);

         if (bSuccess) {
            // copy data
            for (unsigned int i=0 ; i<len/4 ; i++)
               result.push_back(readBuf[i*4+4] << 24 |
                                readBuf[i*4+5] << 16 |
                                readBuf[i*4+6] <<  8 |
                                readBuf[i*4+7]);
            return result;
         }

      } while (1);


      if (this->mVerbose)
         std::cout << mWDBName << " retry " << retry+1 << std::endl;
   }

   if (!bSuccess)
      throw std::runtime_error(std::string("Error reading binary UDP data from "+mWDBName+"."));

   return result;
}

//--------------------------------------------------------------------

void DCB::Connect()
{
   struct sockaddr_in client_addr;
   struct hostent *phe;

#ifdef _MSC_VER
   {
   WSADATA WSAData;

   // Start windows sockets
   if (WSAStartup(MAKEWORD(1, 1), &WSAData) != 0)
      return -1;
   }
#endif

   // create UDB socket for binary commands
   if (gBinSocket == 0)
      gBinSocket = socket(AF_INET, SOCK_DGRAM, 0);
   assert(gBinSocket);

   // retrieve Ethernet address of board
   phe = gethostbyname(mWDBName.c_str());
   if (phe == NULL)
      throw std::runtime_error(std::string("Cannot resolve host name ")+mWDBName+".");

   std::memcpy((char *)&client_addr.sin_addr, phe->h_addr, phe->h_length);
   client_addr.sin_family = AF_INET;
   client_addr.sin_port = htons(WD2_CMD_PORT_ASCII);
   std::memcpy(mEthAddrAscii, &client_addr, sizeof(client_addr));

   client_addr.sin_port = htons(WD2_CMD_PORT_BIN);
   std::memcpy(mEthAddrBin, &client_addr, sizeof(client_addr));

   // check if board is alive
   try {
      DCB::ReadUDP(0, 1);
   } catch (...) {
      throw std::runtime_error(std::string("Cannot connect to board ")+mWDBName+".");
   }

   // check firmware compatibility level
   ReceiveStatusRegister(WD2_FW_COMPAT_LEVEL_REG);
   ReceiveStatusRegister(WD2_REG_LAYOUT_COMP_LEVEL_REG);
   ReceiveStatusRegister(WD2_REG_PROT_VER);
   if (GetFwCompatLevel() < cRequiredFwCompatLevel) {
      std::string str("Board ");
      str += mWDBName + " has incompatible firmware, please upgrade (Board compatibility level: "+
      std::to_string(GetFwCompatLevel())+", Software compatibility level: "+
      std::to_string(cRequiredFwCompatLevel)+")";
      throw std::runtime_error(str);
   }
   if (cRequiredFwCompatLevel < GetFwCompatLevel()) {
      std::string str("Board ");
      str += mWDBName + " has newer incompatible firmware, please update WD library (Firmware compatibility level: "+
      std::to_string(GetFwCompatLevel())+", Software compatibility level: "+
      std::to_string(cRequiredFwCompatLevel)+")";
      throw std::runtime_error(str);
   }
   // check register layout compatibility level
   if (GetRegLayoutCompLevel() < cRequiredRegLayoutCompatLevel) {
      std::string str("Board ");
      str += mWDBName + " has incompatible register layout, please upgrade (Board compatibility level: "+
      std::to_string(GetRegLayoutCompLevel())+", Software compatibility level: "+
      std::to_string(cRequiredRegLayoutCompatLevel)+")";
      throw std::runtime_error(str);
   }
   if (cRequiredRegLayoutCompatLevel < GetRegLayoutCompLevel()) {
      std::string str("Board ");
      str += mWDBName + " has newer register layout, please update WD library (Board compatibility level: "+
      std::to_string(GetRegLayoutCompLevel())+", Software compatibility level: "+
      std::to_string(cRequiredRegLayoutCompatLevel)+")";
      throw std::runtime_error(str);
   }
}

//--------------------------------------------------------------------

unsigned int DCB::BitExtractStatus(unsigned int rofs, unsigned int mask, unsigned int ofs)
{
   return (sreg[(rofs & 0x0FFF)/4] & mask) >> ofs;
}

unsigned int DCB::BitExtractControl(unsigned int rofs, unsigned int mask, unsigned int ofs)
{
   return (creg[(rofs & 0x0FFF)/4] & mask) >> ofs;
}

void bitReplace(unsigned int &reg, unsigned int mask, unsigned int ofs, unsigned int value)
{
   reg = reg & (~mask); // clear bits from mask
   value <<= ofs;       // shift values
   value &= mask;
   reg |= value;        // set makes bits
}

//--------------------------------------------------------------------

void DCB::ReceiveControlRegisters(unsigned int index, unsigned int nReg)
{
   std::vector<unsigned int> result = ReadUDP(WD2_REG_WDB_LOC+index*4, nReg);
   assert(result.size() == nReg);
   for (unsigned int i=0 ; i<nReg ; i++)
     this->creg[index+i] = result[i];
}

void DCB::ReceiveStatusRegisters(unsigned int index, unsigned int nReg)
{
   std::vector<unsigned int> result = ReadUDP(WD2_STAT_REG_BASE_OFS+index*4, nReg);
   assert(result.size() == nReg);
   for (unsigned int i=0 ; i<nReg ; i++)
      this->sreg[index+i] = result[i];
}

void DCB::ReceiveStatusRegister(int rofs)
{
   int index = (rofs & 0x0FFF)/4;

   std::vector<unsigned int> result = ReadUDP(rofs, 1);
   this->sreg[index] = result[0];
}

void WDB::SetRegMask(unsigned int rofs, unsigned int mask, unsigned int ofs, unsigned int v)
{
   int index = (rofs & 0x0FFF)/4;

   unsigned int r = this->creg[index];

   bitReplace(r, mask, ofs, v);

   if (!mSendBlocked) {
      WriteUDP(rofs, std::vector<unsigned int> { r });
   }

   this->creg[index] = r;
}

void WDB::SendControlRegisters()
{
   std::vector<unsigned int> v;
   for (int i=0 ; i<REG_NR_OF_CTRL_REGS ; i++)
      v.push_back(this->creg[i]);
   WriteUDP(WD2_CTRL_REG_BASE_OFS, v);
}

//-- Status registers ------------------------------------------------

void DCB::PrintVersion()
{
   std::cout << GetFwBuild() << std::endl;
   std::cout << GetHwVersion() << std::endl;
   std::cout << "Protocol version:    " << GetProtocolVersion() << std::endl;
   std::cout << "Serial number:       " << GetSerialNumber() << std::endl;
}

unsigned int bcd2dec(unsigned int bcd)
{
   return ((bcd & 0xF000) >> 12) * 1000 + ((bcd & 0x0F00) >> 8) * 100 + ((bcd & 0x00F0) >> 4) * 10 + (bcd & 0xF);
}

std::string DCB::GetFwBuild()
{
   std::ostringstream s;
   std::vector<std::string> monthName = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

   s << "FW. Compat. Level:   ";
   s << GetFwCompatLevel() << std::endl;
   s << "Reg. Compat. Level:  ";
   s << GetRegLayoutCompLevel() << std::endl;
   s << "FW GIT Revision:     ";
   s << "0x" << std::hex << std::uppercase << GetFwGitHashTag() << std::endl;

   s << "FW Build:            ";
   s << std::dec << std::setw(2) << std::setfill('0');
   s << monthName[bcd2dec(GetFwBuildMonth())-1] << ' ';
   s << bcd2dec(GetFwBuildDay()) << ' ';
   s << bcd2dec(GetFwBuildYear()) << "  ";
   s << std::setfill('0') << std::setw(2) << bcd2dec(GetFwBuildHour()) << ':';
   s << std::setfill('0') << std::setw(2) << bcd2dec(GetFwBuildMinute()) << ':';
   s << std::setfill('0') << std::setw(2) << bcd2dec(GetFwBuildSecond()) << std::endl;

   s << "SW GIT Revision:     ";
   s << "0x" << std::hex << std::uppercase << GetSwGitHashTag() << std::endl;

   s << "SW Build:            ";
   s << std::dec << std::setw(2) << std::setfill('0');
   s << monthName[bcd2dec(GetSwBuildMonth())-1] << ' ';
   s << bcd2dec(GetSwBuildDay()) << ' ';
   s << bcd2dec(GetSwBuildYear()) << "  ";
   s << std::setfill('0') << std::setw(2) << bcd2dec(GetSwBuildHour()) << ':';
   s << std::setfill('0') << std::setw(2) << bcd2dec(GetSwBuildMinute()) << ':';
   s << std::setfill('0') << std::setw(2) << bcd2dec(GetSwBuildSecond()) << std::endl;

   return s.str();
}

std::string DCB::GetHwVersion()
{
   std::ostringstream s;

   assert(GetBoardMagic() == 0xAC);

   s << "Board Vendor:        ";
   if (GetVendorId() == 0x01)
      s << "PSI";
   else
      s << "unknown";
   s << std::endl;
   s << "Board Type:          ";
   s << "WaveDREAM" << GetBoardType() << std::endl;
   s << "Board Revision:      ";
   s << (char)('A'+GetBoardRevision()) << std::endl;
   s << "Board Variant:       ";
   s << std::showbase << std::internal << std::setfill('0') << std::hex << std::setw(4) << GetBoardVariant();
   s << std::endl;

   return s.str();
}

float DCB::GetTemperatureDegree(bool refresh)
// temperature in deg. C
{
   if (mDemoMode)
      return 37.5;

   if (refresh)
      ReceiveStatusRegister(WD2_TEMPERATURE_REG);
   float temp = GetTemperature() * 0.0625;
   temp = std::roundf(temp * 10 + 0.5) / 10.0f;
   return temp;
}

unsigned int DCB::GetPllLock(bool refresh)
// all PLLs (DRS, LMK, FPGA DAQ, ISERDES, OSERDES)
{
   if (mDemoMode)
      return 0x1FF;

   if (refresh)
      ReceiveStatusRegister(WD2_SYS_DCM_LOCK_REG);
   unsigned int mask =
      GetSysDcmLock()        << WD2_SYS_DCM_LOCK_OFS         |
      GetDaqPllLock()        << WD2_DAQ_PLL_LOCK_OFS         |
      GetOserdesPllLockDcb() << WD2_OSERDES_PLL_LOCK_DCB_OFS |
      GetOserdesPllLockTcb() << WD2_OSERDES_PLL_LOCK_TCB_OFS |
      GetIserdesPllLock0()   << WD2_ISERDES_PLL_LOCK_0_OFS   |
      GetIserdesPllLock1()   << WD2_ISERDES_PLL_LOCK_1_OFS   |
      GetDrsPllLock0()       << WD2_DRS_PLL_LOCK_0_OFS       |
      GetDrsPllLock1()       << WD2_DRS_PLL_LOCK_1_OFS       |
      GetLmkPllLock()        << WD2_LMK_PLL_LOCK_OFS;

   return mask;
}

//
//  DCBLib.cpp
//
//  WaveDAQ DCB Interface Library
//
//  Created by Stefan Ritt on 30/8/2019.
//

#pragma ide diagnostic ignored "hicpp-signed-bitwise"

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
#include "DCBLib.h"
#include "register_map_dcb.h"
#include "DCBReg.h"

#define DCB_CMD_PORT_ASCII        3000
#define DCB_CMD_PORT_BIN          4000

int DCB::gBinSocket = 0;
int DCB::gASCIISocket = 0;
unsigned short DCB::udpSequenceNumber = 0; // sequence number to identify related send/acknowledge packets

//--------------------------------------------------------------------

DCB::DCB(const std::string &name, bool verbose) {
   mDCBName = name;
   mPrompt = "";
   mVerbose = verbose;
   mReceiveTimeoutMs = cDefaultReceiveTimeoutMs;
}

//--------------------------------------------------------------------

void DCB::SendUDP(std::string str)
{
   std::string result;
   result = SendReceiveUDP(str);
}

//--------------------------------------------------------------------

std::string DCB::SendReceiveUDP(std::string str)
{
   size_t i;
   fd_set readfds;
   struct timeval timeout;
   int    status, ms;
   struct sockaddr_in client_addr;
   char   rx_buffer[1600];
   std::string result;

   std::memcpy(&client_addr, mEthAddrAscii, sizeof(client_addr));

   if (str.back() != '\n')
      str += '\n';

   result.clear();

   // retry max ten times
   for (int retry=0 ; retry < 10 ; retry++) {

      // clear input queue
      do {
         FD_ZERO(&readfds);
         FD_SET(gASCIISocket, &readfds);

         timeout.tv_sec = 0;
         timeout.tv_usec = 0;
         do {
            status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
         } while (status == -1); // don't return on interrupt

         if (!FD_ISSET(gASCIISocket, &readfds))
            break;

         i = recv(gASCIISocket, rx_buffer, sizeof(rx_buffer), 0);
      } while (true);

      // send request
      i = sendto(gASCIISocket,
                 str.c_str(),
                 str.size(),
                 0,
                 (struct sockaddr *)&client_addr,
                 sizeof(client_addr));

      if (i != str.size()) {
         if (this->mVerbose)
            std::cout << mDCBName << " send retry " << retry+1 << std::endl;
         continue;
      }

      // retrieve reply until prompt is found
      do {
         std::memset(rx_buffer, 0, sizeof(rx_buffer));

         FD_ZERO(&readfds);
         FD_SET(gASCIISocket, &readfds);


         if (retry == 0)
            ms = mReceiveTimeoutMs;
         else
            ms *= 1.3;   // increase timeout after each retry

         timeout.tv_sec = ms / 1000;
         timeout.tv_usec = (ms % 1000) * 1000;

         do {
            status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
         } while (status == -1);        /* dont return if an alarm signal was cought */

         if (!FD_ISSET(gASCIISocket, &readfds))
            break;

         i = recv(gASCIISocket, rx_buffer, sizeof(rx_buffer), 0);
         assert(i > 0);

         if (rx_buffer[i-1] == 0) // don't count trailing zero
            i--;

         result += rx_buffer;

         // on th first contact, read back prompt
         if (mPrompt == "")
            mPrompt = result;

         // check for prompt
         if (result.substr(result.size()-mPrompt.size()) == mPrompt)
            break;

      } while (1);

      // check for prompt
      if (mPrompt.size() > 0 && result.size() >= mPrompt.size() && result.substr(result.size()-mPrompt.size()) == mPrompt)
         break;

      if (this->mVerbose)
         std::cout << mDCBName << " retry " << retry+1 << std::endl;
      result.clear();
   }

   if (result.size() == 0) {
      if (str.back() == '\n')
         str = str.substr(0, str.size()-1);
      throw std::runtime_error(std::string("Error sending \"")+str+"\" to "+mDCBName+".");
      return result;
   }

   // chop off prompt
   if (result.size() >= mPrompt.size())
      result = result.substr(0, result.size()-mPrompt.size());

   return result;
}

//--------------------------------------------------------------------

void DCB::WriteUDP(unsigned int slot, unsigned int ofs, std::vector<unsigned int> data) {
   size_t i;
   fd_set readfds;
   struct timeval timeout;
   int status, ms, retry;
   struct sockaddr_in client_addr;
   bool bSuccess = false;

   udpSequenceNumber++;
   std::memcpy(&client_addr, mEthAddrBin, sizeof(client_addr));

   std::vector<unsigned char> writeBuf(8);
   std::vector<unsigned char> readBuf(1600);

   writeBuf[0] = 0x14; // Write32 command
   writeBuf[1] = slot;
   writeBuf[2] = udpSequenceNumber >> 8u;
   writeBuf[3] = udpSequenceNumber & 0xFFu;

   writeBuf[4] = (ofs >> 24u) & 0xFFu;
   writeBuf[5] = (ofs >> 16u) & 0xFFu;
   writeBuf[6] = (ofs >>  8u) & 0xFFu;
   writeBuf[7] = (ofs >>  0u) & 0xFFu;

   for (auto &d: data) {
      writeBuf.push_back((d >> 24u) & 0xFFu); // big endian!
      writeBuf.push_back((d >> 16u) & 0xFFu);
      writeBuf.push_back((d >>  8u) & 0xFFu);
      writeBuf.push_back((d >>  0u) & 0xFFu);
   }

   auto startTime = std::chrono::high_resolution_clock::now();

   // retry max ten times
   for (retry = 0; retry < 10; retry++) {

      // clear input queue
      do {
         FD_ZERO(&readfds);
         FD_SET(gBinSocket, &readfds);

         timeout.tv_sec = 0;
         timeout.tv_usec = 0;
         do {
            status = select(FD_SETSIZE, &readfds, nullptr, nullptr, &timeout);
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
                 (struct sockaddr *) &client_addr,
                 sizeof(client_addr));

      if (i != writeBuf.size()) {
         if (this->mVerbose)
            std::cout << mDCBName << " send retry " << retry + 1 << std::endl;
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

         if (retry == 0)
            ms = mReceiveTimeoutMs;
         else
            ms *= 1.3;   // increase timeout after each retry

         timeout.tv_sec = ms / 1000;
         timeout.tv_usec = (ms % 1000) * 1000;

         do {
            status = select(FD_SETSIZE, &readfds, nullptr, nullptr, &timeout);
         } while (status == -1);        /* dont return if an alarm signal was cought */

         if (!FD_ISSET(gBinSocket, &readfds))
            break;

         i = recv(gBinSocket, &readBuf[0], readBuf.size(), 0);
         assert(i > 0);

         // check for acknowledge
         bSuccess = readBuf[0] == 0x14 &&
                    readBuf[1] == 0x01 &&
                    readBuf[2] == ((udpSequenceNumber >> 8u) & 0xFFu) &&
                    readBuf[3] == (udpSequenceNumber & 0xFFu);
         if (bSuccess)
            return;

      } while (1);

      if (this->mVerbose)
         std::cout << mDCBName << " retry " << retry + 1 << std::endl;
   }

   if (this->mVerbose && retry > 0) {
      auto elapsed = std::chrono::high_resolution_clock::now() - startTime;
      std::cout << "Communication to " << mDCBName << " took " <<
                std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() <<
                " ms" << std::endl;

   }

   if (!bSuccess) {
      throw std::runtime_error(std::string("Error writing binary UDP data to " + mDCBName + "."));
      return;
   }
}

//--------------------------------------------------------------------

std::vector<unsigned int> DCB::ReadUDP(unsigned int slot, unsigned int ofs, unsigned int nReg) {
   size_t i;
   fd_set readfds;
   struct timeval timeout;
   int status, ms;
   struct sockaddr_in client_addr;
   bool bSuccess = false;
   std::vector<unsigned int> result;

   udpSequenceNumber++;
   auto len = nReg * sizeof(unsigned int);
   std::memcpy(&client_addr, mEthAddrBin, sizeof(client_addr));

   std::vector<unsigned char> writeBuf(12);
   std::vector<unsigned char> readBuf(1600);

   writeBuf[0]  = 0x24; // Read32 command
   writeBuf[1]  = slot;
   writeBuf[2]  = udpSequenceNumber >> 8;
   writeBuf[3]  = udpSequenceNumber & 0xFF;

   writeBuf[4]  = (ofs >> 24) & 0xFF;
   writeBuf[5]  = (ofs >> 16) & 0xFF;
   writeBuf[6]  = (ofs >>  8) & 0xFF;
   writeBuf[7]  = (ofs >>  0) & 0xFF;

   writeBuf[8]  = (len >> 24) & 0xFF;
   writeBuf[9]  = (len >> 16) & 0xFF;
   writeBuf[10] = (len >>  8) & 0xFF;
   writeBuf[11] = (len >>  0) & 0xFF;

   // retry max ten times
   for (int retry = 0; retry < 10; retry++) {

      // clear input queue
      do {
         FD_ZERO(&readfds);
         FD_SET(gBinSocket, &readfds);

         timeout.tv_sec = 0;
         timeout.tv_usec = 0;
         do {
            status = select(FD_SETSIZE, &readfds, nullptr, nullptr, &timeout);
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
                 (struct sockaddr *) &client_addr,
                 sizeof(client_addr));

      if (i != writeBuf.size()) {
         if (this->mVerbose)
            std::cout << mDCBName << " send retry " << retry + 1 << std::endl;
         continue;
      }

      // retrieve reply until acknowledge is found
      do {
         std::fill(readBuf.begin(), readBuf.end(), 0);

         FD_ZERO(&readfds);
         FD_SET(gBinSocket, &readfds);

         if (retry == 0)
            ms = mReceiveTimeoutMs;
         else
            ms *= 1.3;   // increase timeout after each retry

         timeout.tv_sec = ms / 1000;
         timeout.tv_usec = (ms % 1000) * 1000;

         do {
            status = select(FD_SETSIZE, &readfds, nullptr, nullptr, &timeout);
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
            for (unsigned int i = 0; i < len / 4; i++)
               result.push_back((readBuf[i * 4 + 4] << 24) |
                                (readBuf[i * 4 + 5] << 16) |
                                (readBuf[i * 4 + 6] <<  8) |
                                (readBuf[i * 4 + 7] <<  0));
            return result;
         }

      } while (1);


      if (this->mVerbose)
         std::cout << mDCBName << " retry " << retry + 1 << std::endl;
   }

   if (!bSuccess)
      throw std::runtime_error(std::string("Error reading binary UDP data from " + mDCBName + "."));

   return result;
}

//--------------------------------------------------------------------

void DCB::Connect() {
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

   // create UDP socket for ASCII command interpreter
   if (gASCIISocket == 0)
      gASCIISocket = socket(AF_INET, SOCK_DGRAM, 0);
   assert(gASCIISocket);

   // create UDP socket for binary commands
   if (gBinSocket == 0)
      gBinSocket = socket(AF_INET, SOCK_DGRAM, 0);
   assert(gBinSocket);

   // retrieve Ethernet address of board
   phe = gethostbyname(mDCBName.c_str());
   if (phe == nullptr)
      throw std::runtime_error(std::string("Cannot resolve host name ") + mDCBName + ".");

   std::memcpy((char *) &client_addr.sin_addr, phe->h_addr, phe->h_length);
   client_addr.sin_family = AF_INET;
   client_addr.sin_port = htons(DCB_CMD_PORT_ASCII);
   std::memcpy(mEthAddrAscii, &client_addr, sizeof(client_addr));

   client_addr.sin_port = htons(DCB_CMD_PORT_BIN);
   std::memcpy(mEthAddrBin, &client_addr, sizeof(client_addr));

   // check if board is alive
   try {
      DCB::SendUDP("");
   } catch (...) {
      throw std::runtime_error(std::string("Cannot connect to board ") + mDCBName + ".");
   }

   // check firmware compatibility level
   ReceiveRegisters();
   if (GetFwCompatLevel() < cRequiredFwCompatLevel) {
      std::string str("Board ");
      str += mDCBName + " has incompatible firmware, please upgrade (Board compatibility level: " +
             std::to_string(GetFwCompatLevel()) + ", Software compatibility level: " +
             std::to_string(cRequiredFwCompatLevel) + ")";
      throw std::runtime_error(str);
   }
   if (cRequiredFwCompatLevel < GetFwCompatLevel()) {
      std::string str("Board ");
      str += mDCBName + " has newer incompatible firmware, please update WD library (Firmware compatibility level: " +
             std::to_string(GetFwCompatLevel()) + ", Software compatibility level: " +
             std::to_string(cRequiredFwCompatLevel) + ")";
      throw std::runtime_error(str);
   }
   // check register layout compatibility level
   if (GetRegLayoutCompLevel() < cRequiredRegLayoutCompatLevel) {
      std::string str("Board ");
      str += mDCBName + " has incompatible register layout, please upgrade (Board compatibility level: " +
             std::to_string(GetRegLayoutCompLevel()) + ", Software compatibility level: " +
             std::to_string(cRequiredRegLayoutCompatLevel) + ")";
      throw std::runtime_error(str);
   }
   if (cRequiredRegLayoutCompatLevel < GetRegLayoutCompLevel()) {
      std::string str("Board ");
      str += mDCBName + " has newer register layout, please update WD library (Board compatibility level: " +
             std::to_string(GetRegLayoutCompLevel()) + ", Software compatibility level: " +
             std::to_string(cRequiredRegLayoutCompatLevel) + ")";
      throw std::runtime_error(str);
   }
}

//--------------------------------------------------------------------

unsigned int DCB::BitExtract(unsigned int rofs, unsigned int mask, unsigned int ofs) {
   return (reg[(rofs & 0x0FFF) / 4] & mask) >> ofs;
}

void DCB::bitReplace(unsigned int &reg, unsigned int mask, unsigned int ofs, unsigned int value) {
   reg = reg & (~mask); // clear bits from mask
   value <<= ofs;       // shift values
   value &= mask;
   reg |= value;        // set makes bits
}

//--------------------------------------------------------------------

void DCB::ReceiveRegisters(unsigned int adr, unsigned int nReg) {
   std::vector<unsigned int> result = ReadUDP(SLOT_DCB, adr, nReg);
   assert(result.size() == nReg);
   for (unsigned int i = 0; i < nReg; i++)
      this->reg[adr / 4 + i] = result[i];
}

void DCB::SetRegMask(unsigned int rofs, unsigned int mask, unsigned int ofs, unsigned int v) {
   int index = (rofs & 0x0FFF) / 4;

   unsigned int r = this->reg[index];

   bitReplace(r, mask, ofs, v);

   if (!mSendBlocked) {
      WriteUDP(SLOT_DCB, rofs, std::vector<unsigned int>{r});
   }

   this->reg[index] = r;
}

void DCB::SendRegisters(unsigned int index, unsigned int nReg) {
   std::vector<unsigned int> v;
   for (int i = 0; i < nReg; i++)
      v.push_back(this->reg[index + i]);
   WriteUDP(SLOT_DCB, index * 4, v);
}

//-- Status registers ------------------------------------------------

void DCB::PrintVersion() {
   std::cout << GetFwBuild() << std::endl;
   std::cout << GetHwVersion() << std::endl;
   std::cout << "Protocol version:    " << GetProtocolVersion() << std::endl;
   std::cout << "Serial number:       " << GetSerialNumber() << std::endl;
}

unsigned int DCB::bcd2dec(const unsigned int bcd) {
   return ((bcd & 0xF000) >> 12) * 1000 + ((bcd & 0x0F00) >> 8) * 100 + ((bcd & 0x00F0) >> 4) * 10 + (bcd & 0xF);
}

std::string DCB::GetFwBuild() {
   std::ostringstream s;
   std::vector<std::string> monthName = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov",
                                         "Dec"};

   if (GetFwBuildMonth() == 0 || GetSwBuildMonth() == 0)
      return "Invalid date";

   s << "FW. Compat. Level:   ";
   s << GetFwCompatLevel() << std::endl;
   s << "Reg. Compat. Level:  ";
   s << GetRegLayoutCompLevel() << std::endl;
   s << "FW GIT Revision:     ";
   s << "0x" << std::hex << std::uppercase << GetFwGitHashTag() << std::endl;

   s << "FW Build:            ";
   s << std::dec << std::setw(2) << std::setfill('0');
   s << monthName[bcd2dec(GetFwBuildMonth() - 1)] << ' ';
   s << bcd2dec(GetFwBuildDay()) << ' ';
   s << bcd2dec(GetFwBuildYear()) << "  ";
   s << std::setfill('0') << std::setw(2) << bcd2dec(GetFwBuildHour()) << ':';
   s << std::setfill('0') << std::setw(2) << bcd2dec(GetFwBuildMinute()) << ':';
   s << std::setfill('0') << std::setw(2) << bcd2dec(GetFwBuildSecond()) << std::endl;

   s << "SW GIT Revision:     ";
   s << "0x" << std::hex << std::uppercase << GetSwGitHashTag() << std::endl;

   s << "SW Build:            ";
   s << std::dec << std::setw(2) << std::setfill('0');
   s << monthName[bcd2dec(GetSwBuildMonth()) - 1] << ' ';
   s << bcd2dec(GetSwBuildDay()) << ' ';
   s << bcd2dec(GetSwBuildYear()) << "  ";
   s << std::setfill('0') << std::setw(2) << bcd2dec(GetSwBuildHour()) << ':';
   s << std::setfill('0') << std::setw(2) << bcd2dec(GetSwBuildMinute()) << ':';
   s << std::setfill('0') << std::setw(2) << bcd2dec(GetSwBuildSecond()) << std::endl;

   return s.str();
}

std::string DCB::GetHwVersion() {
   std::ostringstream s;

   assert(GetBoardMagic() == 0xFF);

   s << "Board Vendor:        ";
   if (GetVendorId() == 0x01)
      s << "PSI";
   else
      s << "unknown";
   s << std::endl;
   s << "Board Type:          ";
   s << "DCB" << GetBoardType() - 2 << std::endl;
   s << "Board Revision:      ";
   s << (char) ('A' + GetBoardRevision()) << std::endl;
   s << "Board Variant:       ";
   s << std::showbase << std::internal << std::setfill('0') << std::hex << std::setw(4) << GetBoardVariant();
   s << std::endl;

   return s.str();
}

float DCB::GetTemperatureDegree(bool refresh)
// temperature in deg. C
{
   if (refresh)
      ReceiveRegisters(DCB_TEMPERATURE_REG, 1);
   float temp = GetTemperature() * 0.0625;
   temp = std::roundf(temp * 10) / 10.0f;
   return temp;
}

unsigned int DCB::GetPllLock(bool refresh)
// all PLLs (DRS, LMK, FPGA DAQ, ISERDES, OSERDES)
{
   if (refresh)
      ReceiveRegisters(DCB_SYS_DCM_LOCK_REG, 1);
   unsigned int mask =
           GetSysDcmLock() << DCB_SYS_DCM_LOCK_OFS |
           GetLmkPllLock() << DCB_LMK_PLL_LOCK_OFS;

   return mask;
}

//--------------------------------------------------------------------

std::vector<WDB *> DCB::ScanWDB()
{
   std::vector<WDB *> wdb;

   for (auto slot=0 ; slot<16 ; slot++) {
      auto result = ReadUDP(slot, 0x0000, 1);
      if (result[0] == 0xAC010213 ||
          result[0] == 0xAC01021B) {
         wdb.push_back(new WDB(this, slot));
      }
   }

   return wdb;
}
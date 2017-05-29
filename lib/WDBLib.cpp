//
//  wd
//  WaveDAQ Ethernet Interface
//
//  Created by Stefan Ritt on 13/8/15.
//

#include <string>
#include <sstream>
#include <iostream>
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

#define WD2_USE_UDP_BIN

#define WD2_CMD_PORT_BIN          4000
#define WD2_CMD_PORT_ASCII        3000

#define WD2_UDP_PROTOCOL_VERSION  4

int WP::gDataSocket   = 0;
int WP::gServerPort   = 0;
int WDB::gASCIISocket = 0;
int WDB::gBinSocket   = 0;

unsigned short WDB::udpSequenceNumber = 0; // sequence number to identify related send/acknowledge packets

//--------------------------------------------------------------------

void WDB::SendUDP(std::string str, int timeout_ms)
{
   std::string result;
   result = SendReceiveUDP(str, timeout_ms);
}

//--------------------------------------------------------------------

std::string WDB::SendReceiveUDP(std::string str, int timeout_ms)
{
   size_t i;
   fd_set readfds;
   struct timeval timeout;
   int    status, ms;
   struct sockaddr_in client_addr;
   char   rx_buffer[1600];
   std::string prompt, result;
   
   std::memcpy(&client_addr, mEthAddrAscii, sizeof(client_addr));
   
   if (str.back() != '\n')
      str += '\n';
   
   result.clear();
   
   // assemble prompt
   prompt = mName + " > ";
   
   // retry max five times
   for (int retry=0 ; retry < 5 ; retry++) {

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
            std::cout << mName << " send retry " << retry+1 << std::endl;
         continue;
      }
      
      // retrieve reply until prompt is found
      do {
         std::memset(rx_buffer, 0, sizeof(rx_buffer));
         
         FD_ZERO(&readfds);
         FD_SET(gASCIISocket, &readfds);
         
         ms = timeout_ms;
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
         
         // check for prompt
         if (result.substr(result.size()-prompt.size()) == prompt)
            break;
         
      } while (1);
      
      // check for prompt
      if (result.size() >= prompt.size() && result.substr(result.size()-prompt.size()) == prompt)
         break;
      
      if (this->mVerbose)
         std::cout << mName << " retry " << retry+1 << std::endl;
      result.clear();
   }
   
   if (result.size() == 0) {
      if (str.back() == '\n')
        str = str.substr(0, str.size()-1);
      throw std::runtime_error(std::string("Error sending \"")+str+"\" to "+mName+".");
      return result;
   }
   
   // chop off prompt
   if (result.size() >= prompt.size())
      result = result.substr(0, result.size()-prompt.size());
   
   return result;
}

//--------------------------------------------------------------------

void WDB::WriteUDP(unsigned int ofs, std::vector<unsigned int> data, int timeout_ms)
{
   size_t i;
   fd_set readfds;
   struct timeval timeout;
   int    status, ms;
   struct sockaddr_in client_addr;
   bool   bSuccess = false;
   
   if (mDemoMode)
      return;

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
   
   // retry max five times
   for (int retry=0 ; retry < 5 ; retry++) {
      
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
            std::cout << mName << " send retry " << retry+1 << std::endl;
         continue;
      }
      
      // retrieve reply until acknowledge is found
      do {
         std::fill(readBuf.begin(), readBuf.end(), 0);
         
         FD_ZERO(&readfds);
         FD_SET(gBinSocket, &readfds);
         
         ms = timeout_ms;
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
         std::cout << mName << " retry " << retry+1 << std::endl;
   }
   
   if (!bSuccess) {
      throw std::runtime_error(std::string("Error writing binary UDP data to "+mName+"."));
      return;
   }
}

//--------------------------------------------------------------------

std::vector<unsigned int> WDB::ReadUDP(unsigned int ofs, unsigned int nReg, int timeout_ms)
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

   // retry max five times
   for (int retry=0 ; retry < 5 ; retry++) {
      
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
            std::cout << mName << " send retry " << retry+1 << std::endl;
         continue;
      }
      
      // retrieve reply until acknowledge is found
      do {
         std::fill(readBuf.begin(), readBuf.end(), 0);
         
         FD_ZERO(&readfds);
         FD_SET(gBinSocket, &readfds);
         
         ms = timeout_ms;
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
            for (unsigned int i=0 ; i<len ; i++)
               result.push_back(readBuf[i*4+4] << 24 |
                                readBuf[i*4+5] << 16 |
                                readBuf[i*4+6] <<  8 |
                                readBuf[i*4+7]);
            return result;
         }

      } while (1);
      
      
      if (this->mVerbose)
         std::cout << mName << " retry " << retry+1 << std::endl;
   }
   
   if (!bSuccess)
      throw std::runtime_error(std::string("Error reading binary UDP data from "+mName+"."));
   
   return result;
}

//--------------------------------------------------------------------

void WDB::Connect()
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
   
   // create UDB socket for ASCII command interpreter
   if (gASCIISocket == 0)
      gASCIISocket = socket(AF_INET, SOCK_DGRAM, 0);
   assert(gASCIISocket);

   // create UDB socket for binary commands
   if (gBinSocket == 0)
      gBinSocket = socket(AF_INET, SOCK_DGRAM, 0);
   assert(gBinSocket);

   // retrieve Ethernet address of board
   phe = gethostbyname(mName.c_str());
   if (phe == NULL)
      throw std::runtime_error(std::string("Cannot resolve host name ")+mName+".");
   
   std::memcpy((char *)&client_addr.sin_addr, phe->h_addr, phe->h_length);
   client_addr.sin_family = AF_INET;
   client_addr.sin_port = htons(WD2_CMD_PORT_ASCII);
   std::memcpy(mEthAddrAscii, &client_addr, sizeof(client_addr));

   client_addr.sin_port = htons(WD2_CMD_PORT_BIN);
   std::memcpy(mEthAddrBin, &client_addr, sizeof(client_addr));

   // check if board is alive
   try {
      WDB::SendUDP("", 500);
   } catch (...) {
      throw std::runtime_error(std::string("Cannot connect to board ")+mName+".");
   }
   
   // set dbglevel none
   SendUDP("dbglvl none");
}

void WDB::SetDestinationPort(int port)
{
   if (mDemoMode)
      return;
   
   // set destinantion port in WD board
   SendUDP(std::string("setenv dstport ")+std::to_string(port));
   
   // set MAC address and IP address of this computer in WD board
   SendUDP("cfgdst");
}

//--------------------------------------------------------------------

unsigned int bitExtract(unsigned int reg[], unsigned int rofs, unsigned int mask, unsigned int ofs)
{
   return (reg[(rofs & 0x0FFF)/4] & mask) >> ofs;
}

void bitReplace(unsigned int &reg, unsigned int mask, unsigned int ofs, unsigned int value)
{
   reg = reg & (~mask); // clear bits from mask
   value <<= ofs;       // shift values
   value &= mask;
   reg |= value;        // set makes bits
}

//--------------------------------------------------------------------

void WDB::ReceiveControlRegisters(unsigned int index, unsigned int nReg)
{
   if (mDemoMode) {
      for (auto i=index ; i<index+nReg ; i++)
         this->creg[i] = 0;
      return;
   }

#ifdef WD2_USE_UDP_BIN
   std::vector<unsigned int> result = ReadUDP(WD2_REG_WDB_LOC_OFS+index*4, nReg);
   for (unsigned int i=0 ; i<nReg ; i++)
      this->creg[index+i] = result[i];
#else
   std::string result;
   std::ostringstream req;
   req << "rr 0x" << std::hex << WD2_REG_WDB_LOC_OFS+index*4 << " " << std::dec << nReg;
   
   result = SendReceiveUDP(req.str(), 500);
   std::stringstream ss(result);
   std::string line;
   
   for (auto i=index ; i<index+nReg ; i++) {
      std::getline(ss, line, '\r');
      auto adr = (unsigned int)std::stoul(line.substr(3), nullptr, 16);
      auto idx = (adr - WD2_REG_WDB_LOC_OFS) / 4;
      if (idx < REG_NR_OF_CTRL_REGS)
         this->creg[idx] = (unsigned int)std::stoul(line.substr(10), nullptr, 16);
   }
#endif
}

void WDB::ReceiveStatusRegisters(unsigned int index, unsigned int nReg)
{
   if (mDemoMode) {
      for (auto i=index ; i<index+nReg ; i++)
         this->sreg[i] = 0;
      return;
   }
   
#ifdef WD2_USE_UDP_BIN
   std::vector<unsigned int> result = ReadUDP(WD2_REG_HW_VER_OFS+index*4, nReg);
   for (unsigned int i=0 ; i<nReg ; i++)
      this->sreg[index+i] = result[i];
#else
   std::string result;
   std::ostringstream req;
   req << "rr 0x" << std::hex << WD2_REG_HW_VER_OFS+index*4 << " " << std::dec << nReg;
   
   result = SendReceiveUDP(req.str(), 500);
   std::stringstream ss(result);
   std::string line;
   
   for (unsigned int i=index ; i<index+nReg ; i++) {
      std::getline(ss, line, '\r');
      auto adr = (unsigned int)std::stoul(line.substr(3), nullptr, 16);
      auto idx = (adr - WD2_REG_HW_VER_OFS) / 4;
      if (idx < REG_NR_OF_STAT_REGS) {
         this->sreg[idx] = (unsigned int)std::stoul(line.substr(10), nullptr, 16);
      }
   }
#endif
}

void WDB::ReceiveStatusRegister(int rofs)
{
   int index = (rofs & 0x0FFF)/4;
   
   if (mDemoMode) {
      this->sreg[index] = 0;
      return;
   }

#ifdef WD2_USE_UDP_BIN
   std::vector<unsigned int> result = ReadUDP(rofs, 1);
   this->sreg[index] = result[0];
#else
   std::string result;
   std::ostringstream req;
   req << "rr 0x" << std::hex << rofs << " 1";
      
   result = SendReceiveUDP(req.str());
   this->sreg[index] = (unsigned int)std::stoul(result.substr(13), nullptr, 16);
#endif
}

void WDB::SetRegMask(unsigned int rofs, unsigned int mask, unsigned int ofs, unsigned int v, bool send)
{
   int index = (rofs & 0x0FFF)/4;

   unsigned int r = this->creg[index];
   
   bitReplace(r, mask, ofs, v);
   
   if (!mDemoMode && send && !mSendBlocked) {
#ifdef WD2_USE_UDP_BIN
      WriteUDP(rofs, std::vector<unsigned int> { r });
#else
      std::ostringstream req;
      req << "rw 0x" << std::hex << rofs << " 0x" << r;
   
      SendUDP(req.str());
#endif
   }
   
   this->creg[index] = r;
}

void WDB::SendControlRegisters()
{
   std::vector<unsigned int> v;
   for (int i=0 ; i<REG_NR_OF_CTRL_REGS ; i++)
      v.push_back(this->creg[i]);
   WriteUDP(WD2_REG_WDB_LOC_OFS, v);
}

//-- Status registers ------------------------------------------------

void WDB::PrintVersion()
{
   std::cout << GetFwBuild() << std::endl;
   std::cout << GetHwVersion() << std::endl;
   std::cout << "Protocol version:    " << GetProtocolVersion() << std::endl;
   std::cout << "Serial number:       " << GetSerialNumber() << std::endl;
}

std::string WDB::GetFwBuild()
{
   std::ostringstream s;
   std::vector<std::string> monthName = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
   
   s << "Compatibility Level: ";
   s << bitExtract(sreg, WD2_REG_REG_LAYOUT_VER_OFS, WD2_BIT_FW_COMPAT_LEVEL_MASK, WD2_BIT_FW_COMPAT_LEVEL_OFS) << std::endl;
   s << "FW GIT Revision:     ";
   s << "0x" << std::hex << std::uppercase << bitExtract(sreg, WD2_REG_GIT_HASH_TAG_OFS, WD2_BIT_GIT_HASH_TAG_MASK, WD2_BIT_GIT_HASH_TAG_OFS) << std::endl;
   
   s << "FW Build:            ";
   s << std::dec << std::setw(2) << std::setfill('0');
   s << monthName[bitExtract(sreg, WD2_REG_FW_BUILD_DATE_OFS, WD2_BIT_FW_BUILD_MONTH_MASK, WD2_BIT_FW_BUILD_MONTH_OFS)-1] << ' ';
   s << bitExtract(sreg, WD2_REG_FW_BUILD_DATE_OFS, WD2_BIT_FW_BUILD_DAY_MASK, WD2_BIT_FW_BUILD_DAY_OFS) << ' ';
   s << bitExtract(sreg, WD2_REG_FW_BUILD_DATE_OFS, WD2_BIT_FW_BUILD_YEAR_MASK, WD2_BIT_FW_BUILD_YEAR_OFS) << "  ";
   
   s << std::setfill('0') << std::setw(2) << bitExtract(sreg, WD2_REG_FW_BUILD_TIME_OFS, WD2_BIT_FW_BUILD_HOUR_MASK, WD2_BIT_FW_BUILD_HOUR_OFS) << ':';
   s << std::setfill('0') << std::setw(2) << bitExtract(sreg, WD2_REG_FW_BUILD_TIME_OFS, WD2_BIT_FW_BUILD_MINUTE_MASK, WD2_BIT_FW_BUILD_MINUTE_OFS) << ':';
   s << std::setfill('0') << std::setw(2) << bitExtract(sreg, WD2_REG_FW_BUILD_TIME_OFS, WD2_BIT_FW_BUILD_SECOND_MASK, WD2_BIT_FW_BUILD_SECOND_OFS) << std::endl;
   
   return s.str();
}

std::string WDB::GetHwVersion()
{
   std::ostringstream s;
   
   assert(bitExtract(sreg, WD2_REG_HW_VER_OFS, WD2_BIT_BOARD_MAGIC_MASK, WD2_BIT_BOARD_MAGIC_OFS) == 0xAC);
   
   s << "Board Vendor:        ";
   if (bitExtract(sreg, WD2_REG_HW_VER_OFS, WD2_BIT_VENDOR_ID_MASK, WD2_BIT_VENDOR_ID_OFS) == 0x01)
      s << "PSI";
   else
      s << "unknown";
   s << std::endl;
   s << "Board Type:          ";
   s << "WaveDREAM" << bitExtract(sreg, WD2_REG_HW_VER_OFS, WD2_BIT_BOARD_TYPE_MASK, WD2_BIT_BOARD_TYPE_OFS) << std::endl;
   s << "Board Revision:      ";
   s << (char)('A'+bitExtract(sreg, WD2_REG_HW_VER_OFS, WD2_BIT_BOARD_REVISION_MASK, WD2_BIT_BOARD_REVISION_OFS)) << std::endl;
   s << "Board Variant:       ";
   s << std::showbase << std::internal << std::setfill('0') << std::hex << std::setw(4) << bitExtract(sreg, WD2_REG_HW_VER_OFS, WD2_BIT_BOARD_VARIANT_MASK, WD2_BIT_BOARD_VARIANT_OFS);
   s << std::endl;
   
   return s.str();
}

unsigned int WDB::GetProtocolVersion()
// currently 4
{
   return bitExtract(sreg, WD2_REG_PROT_VER_OFS, WD2_BIT_PROTOCOL_VERSION_MASK, WD2_BIT_PROTOCOL_VERSION_OFS);
}

unsigned int WDB::GetSerialNumber()
{
   return bitExtract(sreg, WD2_REG_SN_OFS, WD2_BIT_SERIAL_NUMBER_MASK, WD2_BIT_SERIAL_NUMBER_OFS);
}

float WDB::GetTemperature(bool refresh)
// temperature in deg. C
{
   if (mDemoMode)
      return 37.5;
   
   if (refresh)
      ReceiveStatusRegister(WD2_REG_STATUS_OFS);
   float temp = bitExtract(sreg, WD2_REG_STATUS_OFS, WD2_BIT_TEMPERATURE_MASK, WD2_BIT_TEMPERATURE_OFS) * 0.0625;
   temp = std::roundf(temp * 10 + 0.5) / 10.0f;
   return temp;
}

bool WDB::IsFlashSelect()
{
   return bitExtract(sreg, WD2_REG_STATUS_OFS, WD2_BIT_FLASH_SEL_MASK, WD2_BIT_FLASH_SEL_OFS) == 0;
}

bool WDB::IsBoardSelect()
{
   return bitExtract(sreg, WD2_REG_STATUS_OFS, WD2_BIT_BOARD_SEL_MASK, WD2_BIT_BOARD_SEL_OFS) == 0;
}

bool WDB::IsSerialBusy()
{
   return bitExtract(sreg, WD2_REG_STATUS_OFS, WD2_BIT_SERIAL_BUSY_MASK, WD2_BIT_SERIAL_BUSY_OFS) == 0;
}

bool WDB::IsSysBusy()
{
   return bitExtract(sreg, WD2_REG_STATUS_OFS, WD2_BIT_SYS_BUSY_MASK, WD2_BIT_SYS_BUSY_OFS) == 0;
}

bool WDB::IsWDBBusy()
{
   return bitExtract(sreg, WD2_REG_STATUS_OFS, WD2_BIT_WDB_BUSY_MASK, WD2_BIT_WDB_BUSY_OFS) == 0;
}

bool WDB::IsHvBoardPlugged()
{
   return bitExtract(sreg, WD2_REG_STATUS_OFS, WD2_BIT_HV_BOARD_PLUGGED_MASK, WD2_BIT_HV_BOARD_PLUGGED_OFS) == 1;
}

bool WDB::IsBackplanePlugged()
{
   return bitExtract(sreg, WD2_REG_STATUS_OFS, WD2_BIT_BACKPLANE_PLUGGED_MASK, WD2_BIT_BACKPLANE_PLUGGED_OFS) == 1;
}

unsigned int WDB::GetExtPllLck(bool refresh)
// external PLLs (DRS, LMK)
{
   if (refresh)
      ReceiveStatusRegister(WD2_REG_PLL_LOCK_OFS);
   return bitExtract(sreg, WD2_REG_PLL_LOCK_OFS, WD2_BIT_DRS_PLL_LOCK_0_MASK |
                     WD2_BIT_DRS_PLL_LOCK_1_MASK | WD2_BIT_LMK_PLL_LOCK_MASK,
                     WD2_BIT_LMK_PLL_LOCK_OFS);
}

bool WDB::IsExtPllLck(bool refresh)
{
   if (mDemoMode)
      return true;

   unsigned int mask = WD2_BIT_DRS_PLL_LOCK_0_MASK |
                       WD2_BIT_DRS_PLL_LOCK_1_MASK |
                       WD2_BIT_LMK_PLL_LOCK_MASK;
   mask >>= WD2_BIT_LMK_PLL_LOCK_OFS;
   
   return (GetExtPllLck(refresh) == mask);
}

unsigned int WDB::GetIntPllLck(bool refresh)
// internal PLLs (FPGA DAQ, ISERDES, OSERDES)
{
   if (refresh)
      ReceiveStatusRegister(WD2_REG_PLL_LOCK_OFS);
   auto mask =
   WD2_BIT_SYS_DCM_LOCK_MASK |
   WD2_BIT_DAQ_PLL_LOCK_MASK |
   WD2_BIT_OSERDES_PLL_LOCK_DCB_MASK |
   WD2_BIT_OSERDES_PLL_LOCK_TCB_MASK |
   WD2_BIT_ISERDES_PLL_LOCK_0_MASK |
   WD2_BIT_ISERDES_PLL_LOCK_1_MASK;
   
   return bitExtract(sreg, WD2_REG_PLL_LOCK_OFS, mask, WD2_BIT_ISERDES_PLL_LOCK_1_OFS);
}

bool WDB::IsIntPllLck(bool refresh)
{
   if (mDemoMode)
      return true;

   unsigned int mask =
   WD2_BIT_SYS_DCM_LOCK_MASK |
   WD2_BIT_DAQ_PLL_LOCK_MASK |
   WD2_BIT_OSERDES_PLL_LOCK_DCB_MASK |
   WD2_BIT_OSERDES_PLL_LOCK_TCB_MASK |
   WD2_BIT_ISERDES_PLL_LOCK_0_MASK |
   WD2_BIT_ISERDES_PLL_LOCK_1_MASK;
   mask >>= WD2_BIT_ISERDES_PLL_LOCK_1_OFS;
   return (GetIntPllLck(refresh) == mask);
}


unsigned int WDB::GetDrsSampleFreq()
// sampling frequency in MHz
{
   if (mDemoMode)
      return 5120;
   
   return bitExtract(sreg, WD2_REG_DRS_SAMPLE_FREQ_OFS, WD2_BIT_DRS_SAMPLE_FREQ_MASK, WD2_BIT_DRS_SAMPLE_FREQ_OFS);
}

void WDB::SetDrsSampleFreq(unsigned int f)
// sampling frequency in MHz
{
   if (mDemoMode) {
      int index = (WD2_REG_DRS_SAMPLE_FREQ_OFS & 0x0FFF)/4;
      unsigned int r = this->creg[index];
      bitReplace(r, WD2_BIT_DRS_SAMPLE_FREQ_MASK, WD2_BIT_DRS_SAMPLE_FREQ_OFS, f);
      this->sreg[index] = r;
      return;
   }
   
   // 200 MHz LMK bus frequency
   auto divider = (int) (200.0 / f * 2048 + 0.5);
   divider /= 2; // LMK multiplies divider by 2
   
   SetRegMask(WD2_REG_LMK_0_OFS, WD2_BIT_LMK0_CLKOUT0_DIV_MASK, WD2_BIT_LMK0_CLKOUT0_DIV_OFS, divider);
   ApplyLmkSettings();
   
   LmkSyncLocal();
   
   // read back new sampling frquency in status register
   ReceiveStatusRegister(WD2_REG_DRS_SAMPLE_FREQ_OFS);
}

unsigned int WDB::GetAdcSampleFreq()
// sampling frequency in MHz
{
   if (mDemoMode)
      return 80;

   return bitExtract(sreg, WD2_REG_ADC_SAMPLE_FREQ_OFS, WD2_BIT_ADC_SAMPLE_FREQ_MASK, WD2_BIT_ADC_SAMPLE_FREQ_OFS);
}

unsigned int WDB::GetAdcInfo()
// chip ID (0x93 for AD9637), speed grade (0=40MS, 1=80MS)
{
   auto mask = WD2_BIT_ADC_0_CHIP_ID_MASK | WD2_BIT_ADC_0_SPEED_MASK |
               WD2_BIT_ADC_1_CHIP_ID_MASK | WD2_BIT_ADC_1_SPEED_MASK;
   return bitExtract(sreg, WD2_REG_ADC_INFO_OFS, mask, WD2_BIT_ADC_1_SPEED_OFS);
}

void WDB::GetScalers(std::vector<unsigned long> &scaler, bool refresh)
{
   if (refresh)
      ReceiveStatusRegisters((WD2_REG_SCALER_0_LSB_OFS-WD2_REG_HW_VER_OFS)/4, 34);

   // channels 0-15 are 64 bit counters
   for (unsigned int i=0 ; i<16 ; i++) {
      unsigned long v = this->sreg[WD2_REG_SCALER_0_LSB_OFS/4+i*2] |
      ((unsigned long)this->sreg[WD2_REG_SCALER_0_LSB_OFS/4+i*2+1] << 32);
      
      if (scaler.size() < i+1)
         scaler.push_back(v);
      else
         scaler[i] = v;
   }
   
   // channels 16 and 17 are 32 bit counters
   for (unsigned int i=16 ; i<18 ; i++) {
      unsigned long v = this->sreg[WD2_REG_SCALER_TRG_OFS/4+(i-16)];
      
      if (scaler.size() < i+1)
         scaler.push_back(v);
      else
         scaler[i] = v;
   }
   
}

unsigned int WDB::GetCompChannelStatus()
// comparator status for 16 channels (1 = above threshold)
{
   return bitExtract(sreg, WD2_REG_COMP_CH_STAT_OFS, WD2_BIT_COMP_CH_STAT_MASK, WD2_BIT_COMP_CH_STAT_OFS);
}

unsigned int WDB::GetLastEventNumber()
// number of last event sent
{
   return bitExtract(sreg, WD2_REG_EVENT_NR_OFS, WD2_BIT_EVENT_NUMBER_MASK, WD2_BIT_EVENT_NUMBER_OFS);
}

unsigned int WDB::GetTriggerBusParityErrorCount()
// error counter for trigger bus parity errors
{
   return bitExtract(sreg, WD2_REG_TRB_PARITY_ERR_OFS, WD2_BIT_TRB_PARITY_ERROR_COUNT_MASK, WD2_BIT_TRB_PARITY_ERROR_COUNT_OFS);
}

unsigned int WDB::GetTriggerBusType()
// trigger type broadcasted via trigger bus
{
   return bitExtract(sreg, WD2_REG_TRB_INFO_OFS, WD2_BIT_TRB_TYPE_MASK, WD2_BIT_TRB_TYPE_OFS);
}

unsigned int WDB::GetTriggerBusNumber()
// event number LSB broadcasted via trigger bus
{
   return bitExtract(sreg, WD2_REG_TRB_INFO_OFS, WD2_BIT_TRB_NUMBER_MASK, WD2_BIT_TRB_NUMBER_OFS);
}

unsigned int WDB::GetAdvTriggerStatus(int r)
{
   assert(r >= 0 && r < 10);
   return bitExtract(sreg, WD2_REG_ADV_TRG_STAT0_OFS+r*4, WD2_BIT_ADV_TRG_CFG_0_MASK, WD2_BIT_ADV_TRG_CFG_0_OFS);
}

//-- Control registers -----------------------------------------------

unsigned int WDB::GetCrateId()
// id of crate (0-255)
{
   return bitExtract(creg, WD2_REG_WDB_LOC_OFS, WD2_BIT_CRATE_ID_MASK, WD2_BIT_CRATE_ID_OFS);
}

void WDB::SetCrateId(unsigned int value)
{
   SetRegMask(WD2_REG_WDB_LOC_OFS, WD2_BIT_CRATE_ID_MASK, WD2_BIT_CRATE_ID_OFS, value);
}

unsigned int WDB::GetSlotId()
// WaveDAQ crate slot number (0-15)
{
   return bitExtract(creg, WD2_REG_WDB_LOC_OFS, WD2_BIT_SLOT_ID_MASK, WD2_BIT_SLOT_ID_OFS);
}

void WDB::SetSlotId(unsigned int value)
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_SLOT_ID_MASK, WD2_BIT_SLOT_ID_OFS, value);
}

unsigned int WDB::GetValidDelayADC()
// delay of data valid at the ISERDES of the ADCs
{
   return bitExtract(creg, WD2_REG_WDB_LOC_OFS, WD2_BIT_VALID_DELAY_ADC_MASK, WD2_BIT_VALID_DELAY_ADC_OFS);
}

void WDB::SetValidDelayADC(unsigned int value)
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_VALID_DELAY_ADC_MASK, WD2_BIT_VALID_DELAY_ADC_OFS, value);
}

unsigned int WDB::GetDaqDataPhase()
// phase step setting of the PLL generating the common DAQ clock
{
   return bitExtract(creg, WD2_REG_CTRL_OFS, WD2_BIT_DAQ_DATA_PHASE_MASK, WD2_BIT_DAQ_DATA_PHASE_OFS);
}

void WDB::SetDaqDataPhase(unsigned int value)
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_DAQ_DATA_PHASE_MASK, WD2_BIT_DAQ_DATA_PHASE_OFS, value);
}

bool WDB::IsCompPowerEnable()
// comperator power enable
{
   return bitExtract(creg, WD2_REG_CTRL_OFS, WD2_BIT_COMP_POWER_EN_MASK, WD2_BIT_COMP_POWER_EN_OFS) == 1;
}

void WDB::SetCompPowerEnable(bool value)
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_COMP_POWER_EN_MASK, WD2_BIT_COMP_POWER_EN_OFS, value ? 1 : 0);
}

unsigned int WDB::GetReadoutSrcSel()
// cReadoutSrcDrs / cReadoutSrcAdc / cReadoutSrcTdc
{
   auto v = bitExtract(creg, WD2_REG_CTRL_OFS, WD2_BIT_READOUT_SRC_SEL_MASK, WD2_BIT_READOUT_SRC_SEL_OFS);
   // temporary fix: use 0/1 until selection is implemented in FPGA
   if (v)
      return 0x02;
   return 0x01;
}

void WDB::SetReadoutSrcSel(unsigned int value)
{
   // cReadoutSrcDrs or cReadoutSrcAdc or cReadoutSrcTdc

   // temporary fix: use 0/1 until selection is implemented in FPGA
   unsigned int v = (value == 0x02);
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_READOUT_SRC_SEL_MASK, WD2_BIT_READOUT_SRC_SEL_OFS, v);
}

unsigned int WDB::GetDRSReadoutMode()
// 0 = start from first sampling cell / 1 = start from stop cell
{
   return bitExtract(creg, WD2_REG_CTRL_OFS, WD2_BIT_DRS_READOUT_MODE_MASK, WD2_BIT_DRS_READOUT_MODE_OFS);
}

void WDB::SetDRSReadoutMode(unsigned int value)
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_DRS_READOUT_MODE_MASK, WD2_BIT_DRS_READOUT_MODE_OFS, value);
}

bool WDB::IsDRSWaveContinous()
// run domino wave continously even during readout
{
   return bitExtract(creg, WD2_REG_CTRL_OFS, WD2_BIT_DRS_WAVE_CONTINUOUS_MASK, WD2_BIT_DRS_WAVE_CONTINUOUS_OFS) == 1;
}

void WDB::SetDRSWaveContinous(bool value)
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_DRS_WAVE_CONTINUOUS_MASK, WD2_BIT_DRS_WAVE_CONTINUOUS_OFS, value ? 1 : 0);
}

void WDB::TrgDRSConfigure()
// triggers a DRS chip register configuration
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_DRS_CONFIGURE_MASK, WD2_BIT_DRS_CONFIGURE_OFS, 1);
}

void WDB::TrgDAQSoft(bool value)
// software trigger of a DRS readout
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_DAQ_SOFT_TRIGGER_MASK, WD2_BIT_DAQ_SOFT_TRIGGER_OFS, value);
}

void WDB::TrgDAQReinit()
// stop & reset the DRS readout state machine
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_DAQ_REINIT_MASK, WD2_BIT_DAQ_REINIT_OFS, 1);
}

bool WDB::IsDAQNormal()
// "normal" acquisition mode like on an oscilloscope
{
   return bitExtract(creg, WD2_REG_CTRL_OFS, WD2_BIT_DAQ_NORMAL_MASK, WD2_BIT_DAQ_NORMAL_OFS) == 1;
}

void WDB::SetDaqNormal(bool value)
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_DAQ_NORMAL_MASK, WD2_BIT_DAQ_NORMAL_OFS, value ? 1 : 0);
}

bool WDB::IsDaqSingle()
// "single" acquisition mode like on an oscilloscope
{
   return bitExtract(creg, WD2_REG_CTRL_OFS, WD2_BIT_DAQ_SINGLE_MASK, WD2_BIT_DAQ_SINGLE_OFS) == 1;
}

void WDB::SetDaqSingle(bool value)
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_DAQ_SINGLE_MASK, WD2_BIT_DAQ_SINGLE_OFS, value ? 1 : 0);
}

void WDB::StartDaqSingle()
{
   SetRegMask(WD2_REG_CTRL_OFS, WD2_BIT_DAQ_SINGLE_MASK, WD2_BIT_DAQ_SINGLE_OFS, 1);
}

unsigned int WDB::GetDrs0TimingRefSel()
// 0 = oscillator / 1 = LMK
{
   return bitExtract(creg, WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_DRS_0_TIMING_REF_SEL_MASK, WD2_BIT_DRS_0_TIMING_REF_SEL_OFS);
}

void WDB::SetDrs0TimingRefSel(unsigned int value)
{
   SetRegMask(WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_DRS_0_TIMING_REF_SEL_MASK, WD2_BIT_DRS_0_TIMING_REF_SEL_OFS, value);
}

unsigned int WDB::GetDrs1TimingRefSel()
// 0 = oscillator / 1 = LMK
{
   return bitExtract(creg, WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_DRS_1_TIMING_REF_SEL_MASK, WD2_BIT_DRS_1_TIMING_REF_SEL_OFS);
}

void WDB::SetDrs1TimingRefSel(unsigned int value)
{
   SetRegMask(WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_DRS_1_TIMING_REF_SEL_MASK, WD2_BIT_DRS_1_TIMING_REF_SEL_OFS, value);
}

bool WDB::IsCalibBufferEnable()
// enable (power) buffers driving the timing calibration signal to the frontend MUX
{
   return bitExtract(creg, WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_CALIB_BUFFER_EN_MASK, WD2_BIT_CALIB_BUFFER_EN_OFS) == 1;
}

void WDB::SetCalibBufferEnable(bool value)
{
   SetRegMask(WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_CALIB_BUFFER_EN_MASK, WD2_BIT_CALIB_BUFFER_EN_OFS, value ? 1 : 0);
}

bool WDB::IsTimingCalibSignalEnable()
// switch on/off the 100 MHz calibration signal for the DRS chips
{
   return bitExtract(creg, WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_TIMING_CALIB_SIGNAL_EN_MASK, WD2_BIT_TIMING_CALIB_SIGNAL_EN_OFS) == 1;
}

void WDB::SetTimingCalibSignalEnable(bool value)
{
   // switch TCA_CTRL
   SetRegMask(WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_TIMING_CALIB_SIGNAL_EN_MASK, WD2_BIT_TIMING_CALIB_SIGNAL_EN_OFS, value ? 1 : 0);

   // enable delay on LMK output #0
   SetRegMask(WD2_REG_LMK_0_OFS, WD2_BIT_LMK0_CLKOUT0_MUX_MASK, WD2_BIT_LMK0_CLKOUT0_MUX_OFS, 3);
   
   // switch LMK output #6
   
   // enable divider and delay
   SetRegMask(WD2_REG_LMK_6_OFS, WD2_BIT_LMK6_CLKOUT6_MUX_MASK, WD2_BIT_LMK6_CLKOUT6_MUX_OFS, 3);
   // divide 200 MHz by 2x1 = 100 MHz
   SetRegMask(WD2_REG_LMK_6_OFS, WD2_BIT_LMK6_CLKOUT6_DIV_MASK, WD2_BIT_LMK6_CLKOUT6_DIV_OFS, 1);
   // enbable/disable output
   SetRegMask(WD2_REG_LMK_6_OFS, WD2_BIT_LMK6_CLKOUT6_EN_MASK, WD2_BIT_LMK6_CLKOUT6_EN_OFS, value);
   ApplyLmkSettings();
}

void WDB::SetTimingCalibSignalDelay(int value)
{
   // set delay of LMK output #6
   assert(value >= -16 && value <= 16);
   if (value >= 0) {
      SetRegMask(WD2_REG_LMK_0_OFS, WD2_BIT_LMK0_CLKOUT0_DLY_MASK, WD2_BIT_LMK0_CLKOUT0_DLY_OFS, 0);
      // delay channel 6
      if (value == 16)
         SetRegMask(WD2_REG_LMK_6_OFS, WD2_BIT_LMK6_CLKOUT6_MUX_MASK, WD2_BIT_LMK6_CLKOUT6_MUX_OFS, 1);
      else {
         SetRegMask(WD2_REG_LMK_6_OFS, WD2_BIT_LMK6_CLKOUT6_MUX_MASK, WD2_BIT_LMK6_CLKOUT6_MUX_OFS, 3);
         SetRegMask(WD2_REG_LMK_6_OFS, WD2_BIT_LMK6_CLKOUT6_DLY_MASK, WD2_BIT_LMK6_CLKOUT6_DLY_OFS, value);
      }
   } else {
      // delay channel 0
      if (value == -16)
         SetRegMask(WD2_REG_LMK_0_OFS, WD2_BIT_LMK0_CLKOUT0_MUX_MASK, WD2_BIT_LMK0_CLKOUT0_MUX_OFS, 1);
      else {
         SetRegMask(WD2_REG_LMK_0_OFS, WD2_BIT_LMK0_CLKOUT0_MUX_MASK, WD2_BIT_LMK0_CLKOUT0_MUX_OFS, 3);
         SetRegMask(WD2_REG_LMK_0_OFS, WD2_BIT_LMK0_CLKOUT0_DLY_MASK, WD2_BIT_LMK0_CLKOUT0_DLY_OFS, -value);
      }
      SetRegMask(WD2_REG_LMK_6_OFS, WD2_BIT_LMK6_CLKOUT6_DLY_MASK, WD2_BIT_LMK6_CLKOUT6_DLY_OFS, 0);
   }
   
   ApplyLmkSettings();
}

int WDB::GetTimingCalibSignalDelay()
{
   int v1 = bitExtract(creg, WD2_REG_LMK_0_OFS, WD2_BIT_LMK0_CLKOUT0_DLY_MASK, WD2_BIT_LMK0_CLKOUT0_DLY_OFS);
   int v2 = bitExtract(creg, WD2_REG_LMK_6_OFS, WD2_BIT_LMK6_CLKOUT6_DLY_MASK, WD2_BIT_LMK6_CLKOUT6_DLY_OFS);
   if (v2 > 0)
      return -v2;
   return v1;
}

unsigned int WDB::GetDaqClkSrcSel()
// 0 = crate clock / 1 = on-board oscillator
{
   return bitExtract(creg, WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_DAQ_CLK_SRC_SEL_MASK, WD2_BIT_DAQ_CLK_SRC_SEL_OFS);
}

int WDB::GetTimingReferenceSignal()
{
   if (GetDrs0TimingRefSel()) {
      if (bitExtract(creg, WD2_REG_LMK_1_OFS, WD2_BIT_LMK1_CLKOUT1_EN_MASK, WD2_BIT_LMK1_CLKOUT1_EN_OFS))
         return 2;
   } else {
      if (IsTimingCalibSignalEnable())
         return 1;
   }
   return 0;
}

void WDB::SetTimingReferenceSignal(int value)
{
   if (value == cTimingReferenceOff) { // turn reference signal off
      
      // select LMK outputs
      SetDrs0TimingRefSel(1);
      SetDrs1TimingRefSel(1);
      
      // disable LMK outputs #1 and #2
      SetRegMask(WD2_REG_LMK_1_OFS, WD2_BIT_LMK1_CLKOUT1_EN_MASK, WD2_BIT_LMK1_CLKOUT1_EN_OFS, 0);
      SetRegMask(WD2_REG_LMK_2_OFS, WD2_BIT_LMK2_CLKOUT2_EN_MASK, WD2_BIT_LMK2_CLKOUT2_EN_OFS, 0);
      
      ApplyLmkSettings();
      
   } else if (value == cTimingReferenceSine) { // seclect sine wave generator
      
      // turn on sine wave generator
      SetTimingCalibSignalEnable(true);
      
      // select sine wave
      SetDrs0TimingRefSel(0);
      SetDrs1TimingRefSel(0);
      
      // disable LMK outputs #1 and #2
      SetRegMask(WD2_REG_LMK_1_OFS, WD2_BIT_LMK1_CLKOUT1_EN_MASK, WD2_BIT_LMK1_CLKOUT1_EN_OFS, 0);
      SetRegMask(WD2_REG_LMK_2_OFS, WD2_BIT_LMK2_CLKOUT2_EN_MASK, WD2_BIT_LMK2_CLKOUT2_EN_OFS, 0);
      
      ApplyLmkSettings();
      
   } else if (value == ctimingReferenceSquare){ // select square wave
      
      // select LMK outputs #1 and #2
      SetDrs0TimingRefSel(1);
      SetDrs1TimingRefSel(1);
      
      // turn on LMK outputs #1 and #2
      SetRegMask(WD2_REG_LMK_1_OFS, WD2_BIT_LMK1_CLKOUT1_MUX_MASK, WD2_BIT_LMK1_CLKOUT1_MUX_OFS, 1);
      SetRegMask(WD2_REG_LMK_1_OFS, WD2_BIT_LMK1_CLKOUT1_DIV_MASK, WD2_BIT_LMK1_CLKOUT1_DIV_OFS, 1);
      SetRegMask(WD2_REG_LMK_1_OFS, WD2_BIT_LMK1_CLKOUT1_EN_MASK,  WD2_BIT_LMK1_CLKOUT1_EN_OFS, 1);
      
      SetRegMask(WD2_REG_LMK_2_OFS, WD2_BIT_LMK2_CLKOUT2_MUX_MASK, WD2_BIT_LMK2_CLKOUT2_MUX_OFS, 1);
      SetRegMask(WD2_REG_LMK_2_OFS, WD2_BIT_LMK2_CLKOUT2_DIV_MASK, WD2_BIT_LMK2_CLKOUT2_DIV_OFS, 1);
      SetRegMask(WD2_REG_LMK_2_OFS, WD2_BIT_LMK2_CLKOUT2_EN_MASK,  WD2_BIT_LMK2_CLKOUT2_EN_OFS, 1);
      
      ApplyLmkSettings();
      
      LmkSyncLocal();
   }
}

void WDB::SetDaqClkSrcSel(unsigned int value)
{
   SetRegMask(WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_DAQ_CLK_SRC_SEL_MASK, WD2_BIT_DAQ_CLK_SRC_SEL_OFS, value);
}

unsigned int WDB::GetExtClkInSel()
// 0 = crate clock / 1 = MCX connector input
{
   return bitExtract(creg, WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_EXT_CLK_IN_SEL_MASK, WD2_BIT_EXT_CLK_IN_SEL_OFS);
}

void WDB::SetExtClkInSel(unsigned int value)
{
   SetRegMask(WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_EXT_CLK_IN_SEL_MASK, WD2_BIT_EXT_CLK_IN_SEL_OFS, value);
}

unsigned int WDB::GetExtClkFreq()
// external clock frequency in MHz
{
   return bitExtract(creg, WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_EXT_CLK_FREQ_MASK, WD2_BIT_EXT_CLK_FREQ_OFS);
}

unsigned int WDB::GetLocalClkFreq()
// on-board clock frequency in MHz
{
   return bitExtract(creg, WD2_REG_CLK_CAL_CTRL_OFS, WD2_BIT_LOCAL_CLK_FREQ_MASK, WD2_BIT_LOCAL_CLK_FREQ_OFS);
}

unsigned int WDB::GetDrs1ChnTxEnable()
// channel transmission enable of DRS1 [CH8:CH0], CH8:clock channel
{
   return bitExtract(creg, WD2_REG_CH_TX_EN_OFS, WD2_BIT_DRS_1_CH_TX_EN_MASK, WD2_BIT_DRS_1_CH_TX_EN_OFS);
}

void WDB::SetDrs1ChnTxEnable(unsigned int value)
{
   SetRegMask(WD2_REG_CH_TX_EN_OFS, WD2_BIT_DRS_1_CH_TX_EN_MASK, WD2_BIT_DRS_1_CH_TX_EN_OFS, value);
}

unsigned int WDB::GetDrs0ChnTxEnable()
// channel transmission enable of DRS0 [CH8:CH0], CH8:clock channel
{
   return bitExtract(creg, WD2_REG_CH_TX_EN_OFS, WD2_BIT_DRS_0_CH_TX_EN_MASK, WD2_BIT_DRS_0_CH_TX_EN_OFS);
}

void WDB::SetDrs0ChnTxEnable(unsigned int value)
{
   SetRegMask(WD2_REG_CH_TX_EN_OFS, WD2_BIT_DRS_0_CH_TX_EN_MASK, WD2_BIT_DRS_0_CH_TX_EN_OFS, value);
}

unsigned int WDB::GetDrsControl()
/* bits
    18:  drs_wsrloop
    17:  drs_pllen
    16:  drs_dmode
    15:8 drs_wsr
     7:0 drs_wcr
*/
{
   auto mask = WD2_BIT_DRS_WSRLOOP_MASK |
               WD2_BIT_DRS_PLLEN_MASK |
               WD2_BIT_DRS_DMODE_MASK |
               WD2_BIT_DRS_WSR_MASK |
               WD2_BIT_DRS_WCR_MASK;
   
   return bitExtract(creg, WD2_REG_DRS_CTRL_OFS, mask, WD2_BIT_DRS_WCR_OFS);
}

void WDB::SetDrsControl(unsigned int value)
{
   auto mask = WD2_BIT_DRS_WSRLOOP_MASK |
   WD2_BIT_DRS_PLLEN_MASK |
   WD2_BIT_DRS_DMODE_MASK |
   WD2_BIT_DRS_WSR_MASK |
   WD2_BIT_DRS_WCR_MASK;

   SetRegMask(WD2_REG_DRS_CTRL_OFS, mask, WD2_BIT_DRS_WCR_OFS, value);
}

unsigned int WDB::GetDataDestination()
// 0 = Ethernet / 1 = oserdes to backplane
{
   return bitExtract(creg, WD2_REG_COM_CTRL_OFS, WD2_BIT_DATA_DESTINATION_MASK, WD2_BIT_DATA_DESTINATION_OFS);
}

void WDB::SetDataDestination(unsigned int value)
{
   SetRegMask(WD2_REG_COM_CTRL_OFS, WD2_BIT_DATA_DESTINATION_MASK, WD2_BIT_DATA_DESTINATION_OFS, value);
}

unsigned int WDB::GetDCBSerdesTrain()
// enable training pattern for DCB serdes connection
{
   return bitExtract(creg, WD2_REG_COM_CTRL_OFS, WD2_BIT_DCB_SERDES_TRAIN_MASK, WD2_BIT_DCB_SERDES_TRAIN_OFS);
}

void WDB::SetDCBSerdesTrain(unsigned int value)
{
   SetRegMask(WD2_REG_COM_CTRL_OFS, WD2_BIT_DCB_SERDES_TRAIN_MASK, WD2_BIT_DCB_SERDES_TRAIN_OFS, value);
}

unsigned int WDB::GetTcbSerdesTrain()
// enable training pattern for TCB serdes connection
{
   return bitExtract(creg, WD2_REG_COM_CTRL_OFS, WD2_BIT_TCB_SERDES_TRAIN_MASK, WD2_BIT_TCB_SERDES_TRAIN_OFS);
}

void WDB::SetTcbSerdesTrain(unsigned int value)
{
   SetRegMask(WD2_REG_COM_CTRL_OFS, WD2_BIT_TCB_SERDES_TRAIN_MASK, WD2_BIT_TCB_SERDES_TRAIN_OFS, value);
}

unsigned int WDB::GetInterPacketDelay()
// delay between transmission of two UDP packages (in ticks?)
{
   return bitExtract(creg, WD2_REG_COM_CTRL_OFS, WD2_BIT_INTER_PKG_DELAY_MASK, WD2_BIT_INTER_PKG_DELAY_OFS);
}

void WDB::SetInterPacketDelay(unsigned int value)
{
   SetRegMask(WD2_REG_COM_CTRL_OFS, WD2_BIT_INTER_PKG_DELAY_MASK, WD2_BIT_INTER_PKG_DELAY_OFS, value);
}

void WDB::ResetDaqPll
()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_DAQ_PLL_RST_MASK, WD2_BIT_DAQ_PLL_RST_OFS, 1);
}

void WDB::ResetDcbOserdesPll()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_DCB_OSERDES_PLL_RST_MASK, WD2_BIT_DCB_OSERDES_PLL_RST_OFS, 1);
}

void WDB::ResetDcbOserdesIf()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_DCB_OSERDES_IF_RST_MASK, WD2_BIT_DCB_OSERDES_IF_RST_OFS, 1);
}

void WDB::ResetTcbOserdesPll()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_TCB_OSERDES_IF_RST_MASK, WD2_BIT_TCB_OSERDES_IF_RST_OFS, 1);
}

void WDB::ResetTcbOserdesIf()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_TCB_OSERDES_IF_RST_MASK, WD2_BIT_TCB_OSERDES_IF_RST_OFS, 1);
}

void WDB::ResetScaler()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_SCALER_RST_MASK, WD2_BIT_SCALER_RST_OFS, 1);
}

void WDB::ResetTriggerParityErrorCounter()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_TRB_PARITY_ERROR_COUNT_RST_MASK, WD2_BIT_TRB_PARITY_ERROR_COUNT_RST_OFS, 1);
}

void WDB::LmkSyncLocal()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_LMK_SYNC_LOCAL_MASK, WD2_BIT_LMK_SYNC_LOCAL_OFS, 1);
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_LMK_SYNC_LOCAL_MASK, WD2_BIT_LMK_SYNC_LOCAL_OFS, 0);
}

void WDB::ResetAdcIf()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_ADC_IF_RST_MASK, WD2_BIT_ADC_IF_RST_OFS, 1);
}

void WDB::ResetPackager()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_WD_PKGR_RST_MASK, WD2_BIT_WD_PKGR_RST_OFS, 1);
}

void WDB::ResetEventCounter()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_EVENT_COUNTER_RST_MASK, WD2_BIT_EVENT_COUNTER_RST_OFS, 1);
}

void WDB::ResetDrsControlFsm()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_DRS_CTRL_FSM_RST_MASK, WD2_BIT_DRS_CTRL_FSM_RST_OFS, 1);
}

void WDB::ReconfigureFpga()
{
   SetRegMask(WD2_REG_RST_OFS, WD2_BIT_RECONFIGURE_FPGA_MASK, WD2_BIT_RECONFIGURE_FPGA_OFS, 1);
}

void WDB::ApplyDrsSettings()
{
   SetRegMask(WD2_REG_APLY_CFG_OFS, WD2_BIT_APPLY_SETTINGS_DRS_MASK, WD2_BIT_APPLY_SETTINGS_DRS_OFS, 1);
}

void WDB::ApplyDacSettings()
{
   SetRegMask(WD2_REG_APLY_CFG_OFS, WD2_BIT_APPLY_SETTINGS_DAC_MASK, WD2_BIT_APPLY_SETTINGS_DAC_OFS, 1);
}

void WDB::ApplyFrontendSettings()
{
   SetRegMask(WD2_REG_APLY_CFG_OFS, WD2_BIT_APPLY_SETTINGS_DRS_MASK, WD2_BIT_APPLY_SETTINGS_DRS_OFS, 1);
}

void WDB::ApplyControlSettings()
{
   SetRegMask(WD2_REG_APLY_CFG_OFS, WD2_BIT_APPLY_SETTINGS_CTRL_MASK, WD2_BIT_APPLY_SETTINGS_CTRL_OFS, 1);
}

void WDB::ApplyAdcSettings()
{
   SetRegMask(WD2_REG_APLY_CFG_OFS, WD2_BIT_APPLY_SETTINGS_ADC_MASK, WD2_BIT_APPLY_SETTINGS_ADC_OFS, 1);
}

void WDB::ApplyLmkSettings()
{
   SetRegMask(WD2_REG_APLY_CFG_OFS, WD2_BIT_APPLY_SETTINGS_LMK_MASK, WD2_BIT_APPLY_SETTINGS_LMK_OFS, 1);
}

float WDB::GetDacRofsV()
{
   auto d = bitExtract(creg, WD2_REG_DAC0_A_B_OFS, WD2_BIT_DAC0_CH_A_MASK, WD2_BIT_DAC0_CH_A_OFS);
   return d / 65535.0 * 2.5;
}

void WDB::SetDacRofsV(float v)
{
   auto d = (unsigned int)(v / 2.5 * 65535 + 0.5);
   SetRegMask(WD2_REG_DAC0_A_B_OFS, WD2_BIT_DAC0_CH_A_MASK, WD2_BIT_DAC0_CH_A_OFS, d);
}

float WDB::GetDacOfsV()
{
   auto d = bitExtract(creg, WD2_REG_DAC0_A_B_OFS, WD2_BIT_DAC0_CH_B_MASK, WD2_BIT_DAC0_CH_B_OFS);
   return d / 65535.0 * 2.5;
}

void WDB::SetDacOfsV(float v)
{
   auto d = (unsigned int)(v / 2.5 * 65535 + 0.5);
   SetRegMask(WD2_REG_DAC0_A_B_OFS, WD2_BIT_DAC0_CH_B_MASK, WD2_BIT_DAC0_CH_B_OFS, d);
}

float WDB::GetDacCalDcV()
{
   if (mDemoMode)
      return 0;

   auto v = GetDacOfsV();
   v = v - 0.68;
   return v;
}

void WDB::SetDacCalDcV(float v)
{
   v = v + 0.68;
   if (v < 0)
      v = 0;
   if (v > 2.5)
      v = 2.5;

   // shift OFS voltage since CAL_DC is AC coupled
   SetDacOfsV(v);
}

float WDB::GetRange()
{
   float r = -GetDacCalDcV();
   r = (int)(r * 100) / 100.0;
   return r;
}

void WDB::SetRange(float r)
{
   SetDacCalDcV(-r);
}

float WDB::GetDacPulseAmpV()
{
   auto d = bitExtract(creg, WD2_REG_DAC0_C_D_OFS, WD2_BIT_DAC0_CH_D_MASK, WD2_BIT_DAC0_CH_D_OFS);
   return d / 65535.0 * 2.5;
}

void WDB::SetDacPulseAmpV(float v)
{
   auto d = (unsigned int)(v / 2.5 * 65535 + 0.5);
   SetRegMask(WD2_REG_DAC0_C_D_OFS, WD2_BIT_DAC0_CH_D_MASK, WD2_BIT_DAC0_CH_D_OFS, d);
}

std::vector<float> pzcLevel = { 0, 0.5, 1, 1.5, 1.8, 2, 2.5 };

float WDB::GetDacPzcLevelV()
{
   auto d = bitExtract(creg, WD2_REG_DAC0_E_F_OFS, WD2_BIT_DAC0_CH_E_MASK, WD2_BIT_DAC0_CH_E_OFS);
   return d / 65535.0 * 2.5;
}

void WDB::SetDacPzcLevelV(float v)
{
   auto d = (unsigned int)(v / 2.5 * 65535 + 0.5);
   SetRegMask(WD2_REG_DAC0_E_F_OFS, WD2_BIT_DAC0_CH_E_MASK, WD2_BIT_DAC0_CH_E_OFS, d);
}

int WDB::GetDacPzcLevelN()
{
   unsigned int i;
   auto v = GetDacPzcLevelV();
   for (i=0 ; i<pzcLevel.size() ; i++)
      if (pzcLevel[i] == v)
        break;
   return (int)i+1;
}

void WDB::SetDacPzcLevelN(int i)
{
   assert(i >= 0 && i < (int)pzcLevel.size());
   SetDacPzcLevelV(pzcLevel[i]);
}

float WDB::GetDacBiasV()
{
   auto d = bitExtract(creg, WD2_REG_DAC0_G_H_OFS, WD2_BIT_DAC0_CH_H_MASK, WD2_BIT_DAC0_CH_H_OFS);
   return d / 65535.0 * 2.5;
}

void WDB::SetDacBiasV(float v)
{
   auto d = (unsigned int)(v / 2.5 * 65535 + 0.5);
   SetRegMask(WD2_REG_DAC0_G_H_OFS, WD2_BIT_DAC0_CH_H_MASK, WD2_BIT_DAC0_CH_H_OFS, d);
}

float WDB::GetDacTriggerLevelV(int chn)
{
   unsigned int d;
   
   if (mDemoMode)
      return 0;
   
   assert(chn < 16);
   if (chn % 2 == 0)
      d = bitExtract(creg, WD2_REG_DAC1_A_B_OFS+(chn/2)*4, WD2_BIT_DAC1_CH_A_MASK, WD2_BIT_DAC1_CH_A_OFS);
   else
      d = bitExtract(creg, WD2_REG_DAC1_A_B_OFS+(chn/2)*4, WD2_BIT_DAC1_CH_B_MASK, WD2_BIT_DAC1_CH_B_OFS);
   
   // convert to Volts taking WDB comparator offset into account
   float v = ((d / 65535.0 * 2500) - 900) / 500.0;
   return (int)(v * 1000 + 0.5) / 1000.0;
}

void WDB::SetDacTriggerLevelV(int chn, float v)
{
   // convert to mV taking WDB comparator offset into account
   v = v*500 + 900;
   
   // convert from mV to DAC bits
   auto d = (unsigned int)(v / 2500.0 * 65535 + 0.5);
   
   assert(chn < 16);
   if (chn == -1) {
      std::vector<unsigned int> regs;
      for (chn=0 ; chn<16 ; chn++) {
         if (chn % 2 == 0)
            SetRegMask(WD2_REG_DAC1_A_B_OFS+(chn/2)*4, WD2_BIT_DAC1_CH_A_MASK, WD2_BIT_DAC1_CH_A_OFS, d, false);
         else
            SetRegMask(WD2_REG_DAC1_A_B_OFS+(chn/2)*4, WD2_BIT_DAC1_CH_B_MASK, WD2_BIT_DAC1_CH_B_OFS, d, false);
      }
      for (chn=0 ; chn<8 ; chn++)
         regs.push_back(creg[(WD2_REG_DAC1_A_B_OFS-WD2_REG_WDB_LOC_OFS)/4+chn]);
#ifdef WD2_USE_UDP_BIN
      WriteUDP(WD2_REG_DAC1_A_B_OFS, regs);
#else
      for (chn=0 ; chn<8 ; chn++) {
         std::ostringstream req;
         req << "rw 0x" << std::hex << WD2_REG_DAC1_A_B_OFS+(chn/2)*4 << " 0x" << creg[(WD2_REG_DAC1_A_B_OFS-WD2_REG_WDB_LOC_OFS)/4+chn];
         
         SendUDP(req.str());
      }
#endif

   } else {
      if (chn % 2 == 0)
         SetRegMask(WD2_REG_DAC1_A_B_OFS+(chn/2)*4, WD2_BIT_DAC1_CH_A_MASK, WD2_BIT_DAC1_CH_A_OFS, d);
      else
         SetRegMask(WD2_REG_DAC1_A_B_OFS+(chn/2)*4, WD2_BIT_DAC1_CH_B_MASK, WD2_BIT_DAC1_CH_B_OFS, d);
   }
}

bool WDB::IsFePzc(int chn)
// pole-zero canellation
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_PZC_EN_MASK : WD2_BIT_FE1_PZC_EN_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_PZC_EN_OFS  : WD2_BIT_FE1_PZC_EN_OFS;
   return bitExtract(creg, rofs, mask, ofs) > 0;
}

void WDB::SetFePzc(int chn, bool v)
{
   if (chn == -1) {
      for (int i=0 ; i<16 ; i++)
         SetFePzc(i, v);
      return;
   }
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_PZC_EN_MASK : WD2_BIT_FE1_PZC_EN_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_PZC_EN_OFS  : WD2_BIT_FE1_PZC_EN_OFS;
   SetRegMask(rofs, mask, ofs, v ? 1 : 0);
}

unsigned int WDB::GetFeAmp2Comp(int chn)
// amplifier 2 compensation enable
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_COMP_EN_MASK : WD2_BIT_FE1_AMPLIFIER2_COMP_EN_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_COMP_EN_OFS  : WD2_BIT_FE1_AMPLIFIER2_COMP_EN_OFS;
   return bitExtract(creg, rofs, mask, ofs);
}

void WDB::SetFeAmp2Comp(int chn, unsigned int v)
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_COMP_EN_MASK : WD2_BIT_FE1_AMPLIFIER2_COMP_EN_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_COMP_EN_OFS  : WD2_BIT_FE1_AMPLIFIER2_COMP_EN_OFS;
   SetRegMask(rofs, mask, ofs, v);
}

unsigned int WDB::GetFeAmp2Enable(int chn)
// amplifier 2 enable (gain 10)
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_EN_MASK : WD2_BIT_FE1_AMPLIFIER2_EN_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_EN_OFS  : WD2_BIT_FE1_AMPLIFIER2_EN_OFS;
   return bitExtract(creg, rofs, mask, ofs);
}

void WDB::SetFeAmp2Enable(int chn, unsigned int v)
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_EN_MASK : WD2_BIT_FE1_AMPLIFIER2_EN_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_EN_OFS  : WD2_BIT_FE1_AMPLIFIER2_EN_OFS;
   SetRegMask(rofs, mask, ofs, v);
}

unsigned int WDB::GetFeAmp1Comp(int chn)
// amplifier 1 compensation enable
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_COMP_EN_MASK : WD2_BIT_FE1_AMPLIFIER1_COMP_EN_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_COMP_EN_OFS  : WD2_BIT_FE1_AMPLIFIER1_COMP_EN_OFS;
   return bitExtract(creg, rofs, mask, ofs);
}

void WDB::SetFeAmp1Comp(int chn, unsigned int v)
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_COMP_EN_MASK : WD2_BIT_FE1_AMPLIFIER1_COMP_EN_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_COMP_EN_OFS  : WD2_BIT_FE1_AMPLIFIER1_COMP_EN_OFS;
   SetRegMask(rofs, mask, ofs, v);
}

unsigned int WDB::GetFeAmp1Enable(int chn)
// amplifier 1 enable (gain 10)
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_EN_MASK : WD2_BIT_FE1_AMPLIFIER1_EN_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_EN_OFS  : WD2_BIT_FE1_AMPLIFIER1_EN_OFS;
   return bitExtract(creg, rofs, mask, ofs);
}

void WDB::SetFeAmp1Enable(int chn, unsigned int v)
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_EN_MASK : WD2_BIT_FE1_AMPLIFIER1_EN_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_EN_OFS  : WD2_BIT_FE1_AMPLIFIER1_EN_OFS;
   SetRegMask(rofs, mask, ofs, v);
}

unsigned int WDB::GetFeAttenuation(int chn)
// attenuation: 0 = 0dB / 1 = 6dB / 2 = 12dB / 8 = 18dB
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_ATTENUATION_MASK : WD2_BIT_FE1_ATTENUATION_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_ATTENUATION_OFS  : WD2_BIT_FE1_ATTENUATION_OFS;
   return bitExtract(creg, rofs, mask, ofs);
}

void WDB::SetFeAttenuation(int chn, unsigned int v)
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_ATTENUATION_MASK : WD2_BIT_FE1_ATTENUATION_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_ATTENUATION_OFS  : WD2_BIT_FE1_ATTENUATION_OFS;
   SetRegMask(rofs, mask, ofs, v);
}

// input configuration according to FE_bits_2E.xlsx
struct {
   float gain;
   int   att0;
   int   att1;
   int   en1;
   int   comp1;
   int   en2;
   int   comp2;
} gain_table[] = {
   { 0.5, 1, 0, 0, 0, 0, 0},
   {   1, 0, 0, 0, 0, 0, 0},
   { 2.5, 0, 1, 1, 0, 0, 0},
   {   5, 1, 0, 1, 0, 0, 0},
   {  10, 0, 0, 1, 0, 0, 0},
   {  25, 0, 1, 1, 0, 1, 0},
   {  50, 1, 0, 1, 0, 1, 0},
   { 100, 0, 0, 1, 0, 1, 0},
   
};

float WDB::GetFeGain(int chn)
{
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_ATTENUATION_MASK : WD2_BIT_FE1_ATTENUATION_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_ATTENUATION_OFS  : WD2_BIT_FE1_ATTENUATION_OFS;
   int att = bitExtract(creg, rofs, mask, ofs);
   mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_EN_MASK : WD2_BIT_FE1_AMPLIFIER1_EN_MASK;
   ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_EN_OFS  : WD2_BIT_FE1_AMPLIFIER1_EN_OFS;
   int en1 = bitExtract(creg, rofs, mask, ofs);
   mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_EN_MASK : WD2_BIT_FE1_AMPLIFIER2_EN_MASK;
   ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_EN_OFS  : WD2_BIT_FE1_AMPLIFIER2_EN_OFS;
   int en2 = bitExtract(creg, rofs, mask, ofs);
   
   for (int i=0 ; i<8 ; i++)
      if (((gain_table[i].att0 | (gain_table[i].att1 << 1)) == att) &&
          gain_table[i].en1 == en1 &&
          gain_table[i].en2 == en2) {
         return gain_table[i].gain;
      }

   return 0;
}

void WDB::SetFeGain(int chn, float gain)
{
   if (chn == -1) {
      for (int i=0 ; i<16 ; i++)
         SetFeGain(i, gain);
      return;
   }
   
   int i;
   for (i=0 ; i<8 ; i++)
      if (gain_table[i].gain == gain)
         break;
   
   if (i < 8) {
      auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
      
      auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_ATTENUATION_MASK : WD2_BIT_FE1_ATTENUATION_MASK;
      auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_ATTENUATION_OFS  : WD2_BIT_FE1_ATTENUATION_OFS;
      SetRegMask(rofs, mask, ofs, gain_table[i].att0 | (gain_table[i].att1 << 1), false);
      
      mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_EN_MASK : WD2_BIT_FE1_AMPLIFIER1_EN_MASK;
      ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_EN_OFS  : WD2_BIT_FE1_AMPLIFIER1_EN_OFS;
      SetRegMask(rofs, mask, ofs, gain_table[i].en1, false);
      
      mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_COMP_EN_MASK : WD2_BIT_FE1_AMPLIFIER1_COMP_EN_MASK;
      ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER1_COMP_EN_OFS  : WD2_BIT_FE1_AMPLIFIER1_COMP_EN_OFS;
      SetRegMask(rofs, mask, ofs, gain_table[i].comp1, false);
      
      mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_EN_MASK : WD2_BIT_FE1_AMPLIFIER2_EN_MASK;
      ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_EN_OFS  : WD2_BIT_FE1_AMPLIFIER2_EN_OFS;
      SetRegMask(rofs, mask, ofs, gain_table[i].en2, false);
      
      mask = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_COMP_EN_MASK : WD2_BIT_FE1_AMPLIFIER2_COMP_EN_MASK;
      ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_AMPLIFIER2_COMP_EN_OFS  : WD2_BIT_FE1_AMPLIFIER2_COMP_EN_OFS;
      SetRegMask(rofs, mask, ofs, gain_table[i].comp2, true); // send register
   }
}

unsigned int WDB::GetFeMux(int chn)
// multiplexer: 0 = next channel / 1 = previous channel / 2 = input / 3 = cal source
{
   assert(chn < 16);
   auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
   auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_MUX_MASK : WD2_BIT_FE1_MUX_MASK;
   auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_MUX_OFS  : WD2_BIT_FE1_MUX_OFS;
   return bitExtract(creg, rofs, mask, ofs);
}

void WDB::SetFeMux(int chn, unsigned int v)
{
   assert(chn < 16);
   if (chn == -1) {
      std::vector<unsigned int> regs;
      for (chn=0 ; chn<16 ; chn++) {
         auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
         auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_MUX_MASK : WD2_BIT_FE1_MUX_MASK;
         auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_MUX_OFS  : WD2_BIT_FE1_MUX_OFS;
         SetRegMask(rofs, mask, ofs, v);
      }
      for (chn=0 ; chn<8 ; chn++)
         regs.push_back(creg[(WD2_REG_FE_CFG_0_1_OFS-WD2_REG_WDB_LOC_OFS)/4+chn]);
#ifdef WD2_USE_UDP_BIN
      WriteUDP(WD2_REG_FE_CFG_0_1_OFS, regs);
#else
      for (chn=0 ; chn<8 ; chn++) {
         std::ostringstream req;
         req << "rw 0x" << std::hex << WD2_REG_FE_CFG_0_1_OFS+(chn/2)*4 << " 0x" << creg[(WD2_REG_FE_CFG_0_1_OFS-WD2_REG_WDB_LOC_OFS)/4+chn];
         
         SendUDP(req.str());
      }
#endif
   } else {
      auto rofs = WD2_REG_FE_CFG_0_1_OFS + (chn/2)*4;
      auto mask = (chn % 2 == 0) ? WD2_BIT_FE0_MUX_MASK : WD2_BIT_FE1_MUX_MASK;
      auto ofs  = (chn % 2 == 0) ? WD2_BIT_FE0_MUX_OFS  : WD2_BIT_FE1_MUX_OFS;
      SetRegMask(rofs, mask, ofs, v);
   }
}

unsigned int WDB::GetLmk(int reg)
{
   assert(reg < 16);
   return creg[WD2_REG_LMK_0_OFS/4+reg];
}

void WDB::SetLmk(int reg, unsigned int v)
{
   assert(reg < 16);
   SetRegMask(WD2_REG_LMK_0_OFS+reg*4, 0xFFFFFFFF, 0, v);
}

bool WDB::IsTriggerShaperEnable()
{
   return bitExtract(creg, WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_SHAPER_ENABLE_MASK, WD2_BIT_TRIGGER_SHAPER_ENABLE_OFS);
}

void WDB::SetTriggerShaperEnable(bool v)
{
   SetRegMask(WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_SHAPER_ENABLE_MASK, WD2_BIT_TRIGGER_SHAPER_ENABLE_OFS, v);
}

unsigned int WDB::GetTriggerPulseLength()
{
   return bitExtract(creg, WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_OUT_PULSE_LENGTH_MASK, WD2_BIT_TRIGGER_OUT_PULSE_LENGTH_OFS);
}

void WDB::SetTriggerPulseLength(unsigned int v)
{
   SetRegMask(WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_OUT_PULSE_LENGTH_MASK, WD2_BIT_TRIGGER_OUT_PULSE_LENGTH_OFS, v);
}

bool WDB::IsTriggerEnable()
{
   return bitExtract(creg, WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_ENABLE_MASK, WD2_BIT_TRIGGER_ENABLE_OFS);
}

void WDB::SetTriggerEnable(bool v)
{
   SetRegMask(WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_ENABLE_MASK, WD2_BIT_TRIGGER_ENABLE_OFS, v);
}

bool WDB::IsTriggerFallingEdge()
{
   return bitExtract(creg, WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_FALLING_EDGE_MASK, WD2_BIT_TRIGGER_FALLING_EDGE_OFS);
}

void WDB::SetTriggerFallingEdge(bool v)
{
   SetRegMask(WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_FALLING_EDGE_MASK, WD2_BIT_TRIGGER_FALLING_EDGE_OFS, v);
}

bool WDB::IsTriggerExternalOr()
{
   return bitExtract(creg, WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_CFG_EXT_OR_MASK, WD2_BIT_TRIGGER_CFG_EXT_OR_OFS);
}

void WDB::SetTriggerExternalOr(bool v)
{
   SetRegMask(WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_CFG_EXT_OR_MASK, WD2_BIT_TRIGGER_CFG_EXT_OR_OFS, v);
}

bool WDB::IsTriggerExternalAnd()
{
   return bitExtract(creg, WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_CFG_EXT_AND_MASK, WD2_BIT_TRIGGER_CFG_EXT_AND_OFS);
}

void WDB::SetTriggerExternalAnd(bool v)
{
   SetRegMask(WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_CFG_EXT_AND_MASK, WD2_BIT_TRIGGER_CFG_EXT_AND_OFS, v);
}

bool WDB::IsTriggerDelayEnable()
{
   return bitExtract(creg, WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_DELAY_ENABLE_MASK, WD2_BIT_TRIGGER_DELAY_ENABLE_OFS);
}

void WDB::SetTriggerDelayEnable(bool v)
{
   SetRegMask(WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_DELAY_ENABLE_MASK, WD2_BIT_TRIGGER_DELAY_ENABLE_OFS, v);
}

unsigned int WDB::GetTriggerDelay()
{
   return bitExtract(creg, WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_DELAY_MASK, WD2_BIT_TRIGGER_DELAY_OFS);
}

void WDB::SetTriggerDelay(unsigned int v)
{
   SetRegMask(WD2_REG_TRG_CFG_OFS, WD2_BIT_TRIGGER_DELAY_MASK, WD2_BIT_TRIGGER_DELAY_OFS, v);
}

unsigned int WDB::GetTriggerComparatorMask()
{
   return bitExtract(creg, WD2_REG_TRG_COMP_MASK_OFS, WD2_BIT_TRIGGER_COMP_MASK_MASK, WD2_BIT_TRIGGER_COMP_MASK_OFS);
}

void WDB::SetTriggerComparatorMask(unsigned int v)
{
   SetRegMask(WD2_REG_TRG_COMP_MASK_OFS, WD2_BIT_TRIGGER_COMP_MASK_MASK, WD2_BIT_TRIGGER_COMP_MASK_OFS, v);
}

unsigned int WDB::GetTriggerCfgOr()
{
   return bitExtract(creg, WD2_REG_TRG_CH_CMB_OFS, WD2_BIT_TRIGGER_CFG_OR_MASK, WD2_BIT_TRIGGER_CFG_OR_OFS);
}

void WDB::SetTriggerCfgOr(unsigned int v)
{
   SetRegMask(WD2_REG_TRG_CH_CMB_OFS, WD2_BIT_TRIGGER_CFG_OR_MASK, WD2_BIT_TRIGGER_CFG_OR_OFS, v);
}

unsigned int WDB::GetTriggerCfgAnd()
{
   return bitExtract(creg, WD2_REG_TRG_CH_CMB_OFS, WD2_BIT_TRIGGER_CFG_AND_MASK, WD2_BIT_TRIGGER_CFG_AND_OFS);
}

void WDB::SetTriggerCfgAnd(unsigned int v)
{
   SetRegMask(WD2_REG_TRG_CH_CMB_OFS, WD2_BIT_TRIGGER_CFG_AND_MASK, WD2_BIT_TRIGGER_CFG_AND_OFS, v);
}

unsigned int WDB::GetTriggerLocalScheme()
// 0 = simple trigger / 2 = pattern trigger
{
   return bitExtract(creg, WD2_REG_TRG_SCH_SEL_OFS, WD2_BIT_PATTERN_TRIGGER_SELECT_MASK, WD2_BIT_PATTERN_TRIGGER_SELECT_OFS);
}

void WDB::SetTriggerLocalScheme(unsigned int v)
{
   SetRegMask(WD2_REG_TRG_SCH_SEL_OFS, WD2_BIT_PATTERN_TRIGGER_SELECT_MASK, WD2_BIT_PATTERN_TRIGGER_SELECT_OFS, v);
}

unsigned int WDB::GetTriggerBackplaneScheme(int chn)
{
   assert(chn < 8);
   auto mask = WD2_BIT_BACKPLANE_TRIGGER0_MASK >> (chn * 2);
   return bitExtract(creg, WD2_REG_TRG_SCH_SEL_OFS, mask, WD2_BIT_BACKPLANE_TRIGGER0_OFS - chn * 2);
}

void WDB::SetTriggerBackplaneScheme(int chn, unsigned int v)
{
   assert(chn < 8);
   auto mask = WD2_BIT_BACKPLANE_TRIGGER0_MASK >> (chn * 2);
   SetRegMask(WD2_REG_TRG_SCH_SEL_OFS, mask, WD2_BIT_BACKPLANE_TRIGGER0_OFS - chn * 2, v);
}

unsigned int WDB::GetTriggerPatternEnLocal()
// a 1 enables the corresponding trigger pattern for the local trigger
{
   return bitExtract(creg, WD2_REG_TRG_PTRN_EN_LOCAL_OFS, WD2_BIT_TRG_PTRN_EN_LOCAL_MASK, WD2_BIT_TRG_PTRN_EN_LOCAL_OFS);
}

void WDB::SetTriggerPatternEnLocal(unsigned int v)
{
   SetRegMask(WD2_REG_TRG_PTRN_EN_LOCAL_OFS, WD2_BIT_TRG_PTRN_EN_LOCAL_MASK, WD2_BIT_TRG_PTRN_EN_LOCAL_OFS, v);
}

unsigned int WDB::GetTriggerPatternEnBackplane(int chn)
// a 1 enables the corresponding trigger pattern for the local trigger
{
   assert(chn < 8);
   return bitExtract(creg, WD2_REG_TRG_PTRN_EN_BPL0_OFS+chn*4, WD2_BIT_TRG_PTRN_EN_BPL0_MASK, WD2_BIT_TRG_PTRN_EN_BPL0_OFS);
}

void WDB::SetTriggerPatternEnBackplane(int chn, unsigned int v)
{
   assert(chn < 8);
   SetRegMask(WD2_REG_TRG_PTRN_EN_BPL0_OFS+chn*4, WD2_BIT_TRG_PTRN_EN_BPL0_MASK, WD2_BIT_TRG_PTRN_EN_BPL0_OFS, v);
}

unsigned int WDB::GetTriggerPattern(int i)
{
   assert(i < 32);
   return bitExtract(creg, WD2_REG_TRG_PTRN0_OFS+i*4, WD2_BIT_TRG_PTRN0_MASK, WD2_BIT_TRG_PTRN0_OFS);
}

void WDB::SetTriggerPattern(int i, unsigned int v)
{
   assert(i < 32);
   SetRegMask(WD2_REG_TRG_PTRN0_OFS+i*4, WD2_BIT_TRG_PTRN0_MASK, WD2_BIT_TRG_PTRN0_OFS, v);
}

unsigned int WDB::GetAdvTrgCfg(int i)
{
   assert(i < 30);
   return bitExtract(creg, WD2_REG_ADV_TRG_CFG0_OFS+i*4, WD2_BIT_ADV_TRG_CFG_0_MASK, WD2_BIT_ADV_TRG_CFG_0_OFS);
}

void WDB::SetAdvTrgCfg(int i, unsigned int v)
{
   assert(i < 30);
   SetRegMask(WD2_REG_ADV_TRG_CFG0_OFS+i*4, WD2_BIT_ADV_TRG_CFG_0_MASK, WD2_BIT_ADV_TRG_CFG_0_OFS, v);
}


unsigned int WDB::GetCrc32RegBank()
{
   return bitExtract(creg, WD2_REG_CRC32_REG_BANK_OFS, WD2_BIT_CRC32_REG_BANK_MASK, WD2_BIT_CRC32_REG_BANK_OFS);
}

//--------------------------------------------------------------------

unsigned int WDB::GetTriggerDelayNs()
{
   auto v = GetTriggerDelay();
   
   v = (unsigned int)(v / 255.0 * 450 + 0.5);
   return v;
}

void WDB::SetTriggerDelayNs(unsigned int ns)
{
   SetTriggerDelayEnable(ns > 0);
   
   unsigned int v = (unsigned int)(ns / 450.0 * 255 + 0.5);
   if (v > 255)
      v = 255;
   SetTriggerDelay(v);
}

//--------------------------------------------------------------------

void WDB::RequestEvent()
{
   //if (GetReadoutSrcSel() == WDB::cReadoutSrcDrs)
   //   SendReceive("drsget");
   //else
   //   SendReceive("adcget");
   
   SetDaqSingle(true);  // start DRS domino wave
   SetDaqSingle(false);
   
   TrgDAQSoft(true);
   TrgDAQSoft(false);
}

//--------------------------------------------------------------------

void WDB::SaveVoltageCalibration(int freq)
{
   mkdir("calib", 0755);
   mVCalib.save(this, "calib/"+mName+"-"+std::to_string(freq)+".vcal");
}

//--------------------------------------------------------------------

bool WDB::LoadVoltageCalibration(int freq)
{
   if (mVerbose)
      std::cout << "Loading voltage calibration for "+mName+" for " << freq/1000.0 << " GSPS ... ";
   
   mVCalib.load(this, "calib/"+mName+"-"+std::to_string(freq)+".vcal");
   
   if (mVerbose)
      std::cout << (mVCalib.IsValid() ? "ok" : "failure") << std::endl;
   return mVCalib.IsValid();
}

//--------------------------------------------------------------------

void WDB::SaveTimeCalibration(int freq)
{
   mkdir("calib", 0755);
   mTCalib.save(this, "calib/"+mName+"-"+std::to_string(freq)+".tcal");
}

//--------------------------------------------------------------------

bool WDB::LoadTimeCalibration(int freq)
{
   if (mVerbose)
      std::cout << "Loading time calibration for "+mName+" for " << freq/1000.0 << " GSPS ... ";
   
   mTCalib.load(this, "calib/"+mName+"-"+std::to_string(freq)+".tcal");

   if (mVerbose)
      std::cout << (mVCalib.IsValid() ? "ok" : "failure") << std::endl;
   return mTCalib.IsValid();
}

//====================================================================

void WDEvent::SetEventHeaderInfo(WD2_FRAME_HEADER *ph)
{
   mBoardId = ph->board_id;
   mCrateId = ph->crate_id;
   mSlotId  = ph->slot_id;
   mEventNumber = ph->event_number;
   mSamplingFrequency = ph->sampling_frequency;
   mTriggerNumber = ph->trigger_number;
   mTriggerCell[0] = ph->drs0_trigger_cell;
   mTriggerCell[1] = ph->drs1_trigger_cell;
   mTriggerType = ph->trigger_type;
   mTemperature = std::round(ph->temperature*0.0625 * 10 + 0.5) / 10.0f;
   mWFTypeADC = mSamplingFrequency <= 100;
}

//--------------------------------------------------------------------

bool WDEventRequest::IsWfValid()
{
   for (int i=0 ; i<WD_N_CHANNELS ; i++)
      if (mChannelMask & (1 << i))
         if (!mWfValid[i][0] || !mWfValid[i][1])
            return false;
   return true;
}

//--------------------------------------------------------------------

WP::WP(std::vector<WDB *> w, int verbose, bool demo)
{
   struct sockaddr_in server_addr;

   mVerbose = verbose;
   mDemoMode = demo;
   mWdb = w;
   
   mRotateWaveform = true;
   mOfsCalib1 = false;
   mOfsCalib2 = false;
   mGainCalib = false;
   mRangeCalib = false;
   mTimeCalib1 = false;
   mTimeCalib2 = false;
   mTimeCalib3 = false;
   mRemoveSpikes = false;
   
   li.fh = 0;
   li.xml = NULL;
   
   // create UDB socket to receive binary data from WDB
   if (!mDemoMode && WP::gDataSocket == 0) {
      WP::gDataSocket = socket(AF_INET, SOCK_DGRAM, 0);
      assert(WP::gDataSocket);
      
      // bind socket to port chosen by OS
      std::memset((char*)&server_addr, 0, sizeof(server_addr));
      server_addr.sin_family = AF_INET;
      server_addr.sin_port = htons(0); // let OS choose port
      server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
      if (::bind(gDataSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
         perror("bind");
         throw std::runtime_error(std::string("Cannot bind socket"));
      }
      auto size = sizeof(server_addr);
      getsockname(WP::gDataSocket, (struct sockaddr *) &server_addr, (socklen_t *) &size);
      WP::gServerPort = ntohs(server_addr.sin_port);
      
      if (this->mVerbose)
         std::cout << std::endl << "Listening on data port " << WP::gServerPort << "." << std::endl;
   }

   // allocated event buffer and requests for all WDB
   for (unsigned int i=0 ; i<mWdb.size() ; i++)
      mEventRequest.push_back(new WDEventRequest(mWdb[i]->GetSerialNumber()));
   for (unsigned int i=0 ; i<mWdb.size() ; i++)
      mEvent.push_back(new WDEvent(mWdb[i]->GetSerialNumber()));
   for (unsigned int i=0 ; i<mWdb.size() ; i++)
      mEventLast.push_back(new WDEvent(mWdb[i]->GetSerialNumber()));
   
   mEventEmpty = true;
   
   // start waveform collector thread
   mThreadCollector = this->SpawnCollectorThread();
   
   memset(&calibProg, 0, sizeof(calibProg));
}

//--------------------------------------------------------------------

void WP::SetEventRequestMasks()
{
   // set request mask from tx enable
   int i=0;
   for (auto &b: mWdb) {
      auto mask = (b->GetDrs0ChnTxEnable() & 0xFF);
      mask |= (b->GetDrs1ChnTxEnable() & 0xFF) << 8;
      if (b->GetDrs0ChnTxEnable() & 0x100 && b->GetReadoutSrcSel() == WDB::cReadoutSrcDrs)
         mask |= 0x10000;
      if (b->GetDrs1ChnTxEnable() & 0x100 && b->GetReadoutSrcSel() == WDB::cReadoutSrcDrs)
         mask |= 0x20000;

      mEventRequest[i++]->SetMask(mask);
   }
}

unsigned int WP::GetEventRequestMask(int board_id)
{
   for (auto &r: mEventRequest)
      if (r->GetBoardId() == board_id)
         return r->GetMask();
   return 0;
}

WDB* WP::GetBoard(int board_id)
{
   for (auto &b: mWdb)
      if ((int)b->GetSerialNumber() == board_id)
         return b;
   return 0;
}

void WP::RequestBoard(WDB *b)
{
   for (auto &r: mEventRequest) {
      r->SetRequested(r->GetBoardId() == (int)b->GetSerialNumber());
   }
   
   SetEventRequestMasks();
}

void WP::RequestAllBoards()
{
   for (auto &r: mEventRequest)
      r->SetRequested(true);

   SetEventRequestMasks();
}

//--------------------------------------------------------------------

bool WP::RequestEvent(WDB *b, int timeout, WDEvent &event)
{
   RequestBoard(b);
   b->RequestEvent();
   
   return GetLastEvent(b, timeout, event);
}

//--------------------------------------------------------------------

bool WP::GetLastEvent(WDB *b, int timeout, WDEvent& event)
{
   // wait for new event with timeout
   {
      std::unique_lock<std::mutex> lock(mEventMutex);
      if (!(mEventCV.wait_for(lock, std::chrono::milliseconds(timeout), [this](){return mEventNew;})))
         return false;
   }
   
   {
      std::lock_guard<std::mutex> lock(mEventAccessMutex);

      for (auto e: mEventLast)
         if (e->mBoardId == b->GetSerialNumber())
            event = *e;
      mEventNew = false;
      return true;
   }
}

//--------------------------------------------------------------------

bool WP::GetLastEvent(int timeout, std::vector<WDEvent *> event)
{
   // wait for new event with timeout
   {
   std::unique_lock<std::mutex> lock(mEventMutex);
   if (!(mEventCV.wait_for(lock, std::chrono::milliseconds(timeout), [this](){return mEventNew;})))
      return false;
   }
   
   {
   std::lock_guard<std::mutex> lock(mEventAccessMutex);
   
   std::vector<WDEvent*>::iterator ed = event.begin();
   for (auto es: mEventLast)
         **(ed++) = *es;
   mEventNew = false;
   return true;
   }
}

//--------------------------------------------------------------------

void WP::InvalidateAllWf()
{
   for (auto &er: mEventRequest) {
      for (int i=0 ; i<WD_N_CHANNELS ; i++) {
         er->SetWfValid(i, 0, false);
         er->SetWfValid(i, 1, false);
         er->SetDrs0TriggerCell(-1);
         er->SetDrs1TriggerCell(-1);
      }
   }
   
   mPacketsReceived = 0;
   mCurrentEvent = -1;
}

//--------------------------------------------------------------------

bool WP::AllPacketsReceived()
{
   auto it = mEventRequest.begin();
   while (it != mEventRequest.end()) {
      if ((*it)->IsRequested()  && !(*it)->IsWfValid())
         break;
      it++;
   }
   if (it == mEventRequest.end())
      return true;
   return false;
}

//--------------------------------------------------------------------

void WP::ReceiveWfPacket()
{
   fd_set readfds;
   struct timeval timeout;
   int status;
   
   FD_ZERO(&readfds);
   FD_SET(WP::gDataSocket, &readfds);
   
   timeout.tv_sec = 1;
   timeout.tv_usec = 0;
   
   do {
      status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
   } while (status == -1 && errno == EINTR);  // don't return if an alarm signal was caught
   
   if (status == -1)
      perror("select");
   
   if (FD_ISSET(WP::gDataSocket, &readfds)) {
      // packet is available, so receive it
      struct sockaddr_in remote_addr;
      unsigned char buffer[1800];
      
      int len = sizeof(remote_addr);
      int n = (int)recvfrom(WP::gDataSocket, (char *)buffer, sizeof(buffer), 0,
                            (struct sockaddr *)&remote_addr, (socklen_t *)&len);
      if (n > (int)sizeof(WD2_FRAME_HEADER)) {
         WD2_FRAME_HEADER *ph = (WD2_FRAME_HEADER *)buffer;
         
         // check protocol version
         if (ph->protocol_version != WD2_UDP_PROTOCOL_VERSION) {
            std::cerr << "Invalid protocol version " << ph->protocol_version << ", expected " << WD2_UDP_PROTOCOL_VERSION << ". Probably WD firmware update required." << std::endl;
            return;
         }
         
         mPacketsReceived++;
         
         // correct endianness of header data
         ph->board_id                 = SWAP_UINT16(ph->board_id);
         int header_adc               = (ph->adc_and_channel_info >> 4) & 0x0f;
         int header_channel           = (ph->adc_and_channel_info) & 0x0f;
         int channel_segment          = (ph->segment_and_package_type >> 4) & 0x0f;
         int package_type             = (ph->segment_and_package_type) & 0x0f;
         ph->event_number             = SWAP_UINT32(ph->event_number);
         ph->sampling_frequency       = SWAP_UINT16(ph->sampling_frequency);
         ph->payload_length           = SWAP_UINT16(ph->payload_length);
         ph->trigger_number           = SWAP_UINT16(ph->trigger_number);
         ph->drs0_trigger_cell        = SWAP_UINT16(ph->drs0_trigger_cell);
         ph->drs1_trigger_cell        = SWAP_UINT16(ph->drs1_trigger_cell);
         ph->trigger_type             = SWAP_UINT16(ph->trigger_type);
         ph->temperature              = SWAP_UINT16(ph->temperature);
         ph->packet_sequence_number   = SWAP_UINT16(ph->packet_sequence_number);

         std::string str(inet_ntoa(remote_addr.sin_addr));
         str += ":";
         str += std::to_string(ntohs(remote_addr.sin_port));
         while (str.size() < 20)
            str += " ";

         if (mVerbose > 1)
            printf("#%03d from WD%03d (%s), event=%5d type=%d ADC/Chn/Segment=%d/%d/%d Tcell=%04d/%04d T=%1.1lf\n",
                   mPacketsReceived-1,
                   ph->board_id,
                   str.c_str(),
                   ph->event_number,
                   package_type,
                   header_adc,
                   header_channel,
                   channel_segment,
                   ph->drs0_trigger_cell,
                   ph->drs1_trigger_cell,
                   ph->temperature*0.0625);
         
         
         // drop package (for now...) if it is not event data
         if (package_type != 0) {
            std::cerr << "Package dropped, package type=" << package_type << ", "
            << "board id = " << ph->board_id << std::endl;
            return;
         }
         
         // find event request belonging to this board
         WDEventRequest *er = nullptr;
         for (auto r: mEventRequest)
            if (r->GetBoardId() == ph->board_id) {
               er = r;
               break;
            }
         if (!er) {
            if (mVerbose)
               std::cerr << "Received unexpected packet from board #" << ph->board_id << std::endl;
            return;
         }
         
         if (mCurrentEvent == -1)
            mCurrentEvent = ph->event_number;
         if (er->GetDrs0TriggerCell() == -1)
            er->SetDrs0TriggerCell(ph->drs0_trigger_cell);
         if (er->GetDrs1TriggerCell() == -1)
            er->SetDrs1TriggerCell(ph->drs1_trigger_cell);
         
         // drop package if it belongs to older event
         if (ph->event_number < (unsigned int)mCurrentEvent) {
            std::cerr << "Package dropped, package event=" << ph->event_number << ", "
            << "current event=" << mCurrentEvent << ", "
            << "board id = " << ph->board_id << std::endl;
            return;
         }

         // print warning if inconsistent trigger cells are found
         if (ph->event_number == (unsigned int)mCurrentEvent &&
             (ph->drs0_trigger_cell != er->GetDrs0TriggerCell() ||
              ph->drs1_trigger_cell != er->GetDrs1TriggerCell())) {
                std::cerr << "Found inconsistend trigger cell for event " << ph->event_number << std::endl;
         }
         
         // drop whole event if package of next event has been received
         if (ph->event_number > (unsigned int)mCurrentEvent) {
            if (mVerbose)
               std::cerr << "Event dropped, package event=" << ph->event_number << ", "
               << "current event=" << mCurrentEvent << ", "
               << "board id = " << ph->board_id << std::endl;
            
            // switch to new frame
            InvalidateAllWf();
            mCurrentEvent = ph->event_number;
            er->SetDrs0TriggerCell(ph->drs0_trigger_cell);
            er->SetDrs1TriggerCell(ph->drs1_trigger_cell);
            mPacketsReceived = 1;
         }
         
         // map ADC and channel to WD channel (0..7, 8..15, 16+17)
         int wfChannel;
         if (header_channel == 8)
            wfChannel = 16 + header_adc;
         else
            wfChannel = header_adc*8+header_channel;
         assert(wfChannel < WD_N_CHANNELS);
         
         // mark valid package received
         er->SetWfValid(wfChannel, channel_segment, true);
         
         // find event belonging to this baord
         WDEvent *event = nullptr;
         for (auto e: mEvent) {
            if (e->mBoardId == ph->board_id) {
               event = e;
               break;
            }
         }
         if (!event) {
            std::cerr << "Received unexpected packet from board #" << ph->board_id << std::endl;
            return;
         }
         
         event->SetEventHeaderInfo(ph);
         event->mVCalibrated = false;
         event->mTCalibrated = false;

         // decode waveform data
         auto pd = (unsigned char*)(ph+1);
         for (int i=0 ; i<512 ; i+=2) {
            short data1   = ((pd[1] & 0x0F) << 8) | pd[0];
            short data2 = ((unsigned short)pd[2] << 4) | (pd[1] >> 4);
            // subtract binary offset
            data1 -= 0x800;
            data2 -= 0x800;
            pd+=3;
            
            if (channel_segment == 0) {
               // first segment
               event->mWfU[wfChannel][i]         = (float)data1 * (1 / 4096.0); // 1V DRS range with 12 bits
               event->mWfU[wfChannel][i+1]       = (float)data2 * (1 / 4096.0);
            } else {
               // second segment
               event->mWfU[wfChannel][512+i]     = (float)data1 * (1 / 4096.0);
               event->mWfU[wfChannel][512+i+1]   = (float)data2 * (1 / 4096.0);
            }
         }
      }
   }

}

//--------------------------------------------------------------------

void WP::RotateWaveforms()
{
   for (auto it = mEvent.begin() ; it != mEvent.end() ; it++) {
      auto ev = (*it);
      if (ev->mWFTypeADC)
         continue;
      
      float wf[WD_N_CHANNELS][1024];
      
      for (int i=0 ; i<WD_N_CHANNELS ; i++)
         for (int j=0 ; j<1024 ; j++)
            wf[i][j] = ev->mWfU[i][j];
      
      // un-rotate waveforms
      if (mRotateWaveform) {
         for (int i=0 ; i<WD_N_CHANNELS ; i++)
            for (int j=0 ; j<1024 ; j++)
               ev->mWfU[i][j] = ev->mWfU[i][j];
      } else {
         for (int i=0 ; i<WD_N_CHANNELS ; i++) {
            int tc = i < 8 || i == 16 ? ev->mTriggerCell[0] : ev->mTriggerCell[1];
            for (int j=0 ; j<1024 ; j++)
               ev->mWfU[i][(j+tc) % 1024] = wf[i][j];
         }
      }
   }
}

//--------------------------------------------------------------------

void WP::RemoveSpikes(int trigger_cell, float wf[][1024])
{
   /*
    Remove a specific kind of spike on DRS4.
    
    This spike has some specific features, namely:
    - Common on all the channels on a chip
    - Constant heigh and width
    - Two spikes per channel
    - Symmetric to cell #0.
    
    
    Please note that this is not a general purpose spike-remal function.
    */
   
   int i, j, k, l;
   double hp, x, y;
   int sp[8][10];
   int rsp[10], rot_sp[10];
   int n_sp[8], n_rsp;
   int  nNeighbor, nSymmetric;
   float cwf[WD_N_CHANNELS][1024];
   
  
   /* rotate waveform back relative to cell #0 */
   if (mRotateWaveform) {
      for (i=0 ; i<8 ; i++)
         for (j=0 ; j<1024 ; j++)
            cwf[i][(j+trigger_cell) % 1024] = wf[i][j];
   } else {
      for (i=0 ; i<8 ; i++)
         for (j=0 ; j<1024 ; j++)
            cwf[i][j] = wf[i][j];
   }
   
   memset(sp, 0, sizeof(sp));
   memset(n_sp, 0, sizeof(n_sp));
   memset(rsp, 0, sizeof(rsp));
   n_rsp = 0;
   
   /* find spikes with special high-pass filter, skip last values */
   for (j=0 ; j<1020 ; j++) {
      for (i=1 ; i<4 ; i++) { // TBD: temporary fix for bad channels 1,5,6,7
         hp = -cwf[i][j] + cwf[i][(j+1)%1024]+cwf[i][(j+2)%1024] - cwf[i][(j+3) % 1024];
         if (hp > 0.020) {
            if (n_sp[i] < 10) // record maximum of 10 spikes
               sp[i][n_sp[i]++] = j;
            else
               return;        // too many spikes -> something wrong
         }
      }
   }
   
   /* go through all spikes and look for symmetric spikes and neighbors */
   for (i=0 ; i<8 ; i++) {
      for (j=0 ; j<n_sp[i] ; j++) {
         /* check if this spike has a symmetric partner in any channel */
         for (k=nSymmetric=0 ; k<8 ; k++) {
            for (l=0 ; l<n_sp[k] ; l++)
               if (sp[i][j] == (1020-sp[k][l]+1024) % 1024) {
                  nSymmetric++;
                  break;
               }
         }
         
         /* check if this spike has same spike in any other channels */
         for (k=nNeighbor=0 ; k<8 ; k++)
            if (i != k) {
               for (l=0 ; l<n_sp[k] ; l++)
                  if (sp[i][j] == sp[k][l]) {
                     nNeighbor++;
                     break;
                  }
            }
         
         if (nSymmetric + nNeighbor >= 2) {
            /* if at least two matching spikes, treat this as a real spike */
            for (k=0 ; k<n_rsp ; k++)
               if (rsp[k] == sp[i][j])
                  break;
            if (n_rsp < 10 && k == n_rsp)
               rsp[n_rsp++] = sp[i][j];
         }
      }
   }
   
   /* rotate spikes according to trigger cell */
   if (mRotateWaveform) {
      for (i=0 ; i<n_rsp ; i++)
         rot_sp[i] = (rsp[i] - trigger_cell + 1024) % 1024;
   } else {
      for (i=0 ; i<n_rsp ; i++)
         rot_sp[i] = rsp[i];
   }
   
   /* recognize spikes if at least one channel has it */
   for (k=0 ; k<n_rsp ; k++) {
      for (i=0 ; i<8 ; i++) {
         
         if (k < n_rsp-1 && rsp[k] == 0 && rsp[k+1] == 1020) {
            /* remove double spike */
            j = rot_sp[k] > rot_sp[k+1] ? rot_sp[k+1] : rot_sp[k];
            x = wf[i][(j+1) % 1024];
            y = wf[i][(j+6) % 1024];
            if (fabs(x-y) < 0.015) {
               wf[i][(j+2) % 1024] = (float)(x + 1*(y-x)/5);
               wf[i][(j+3) % 1024] = (float)(x + 2*(y-x)/5);
               wf[i][(j+4) % 1024] = (float)(x + 3*(y-x)/5);
               wf[i][(j+5) % 1024] = (float)(x + 4*(y-x)/5);
            } else {
               wf[i][(j+2) % 1024] -= 0.0148f;
               wf[i][(j+3) % 1024] -= 0.0148f;
               wf[i][(j+4) % 1024] -= 0.0148f;
               wf[i][(j+5) % 1024] -= 0.0148f;
            }
         } else {
            /* remove single spike */
            x = wf[i][rot_sp[k]];
            y = wf[i][(rot_sp[k]+3) % 1024];
            
            if (fabs(x-y) < 0.010) {
               wf[i][(rot_sp[k]+1) % 1024] = (float)(x + 1*(y-x)/3);
               wf[i][(rot_sp[k]+2) % 1024] = (float)(x + 2*(y-x)/3);
            } else {
               wf[i][(rot_sp[k]+1) % 1024] -= 0.009f;
               wf[i][(rot_sp[k]+2) % 1024] -= 0.009f;
            }
         }
      }
      if (k < n_rsp-1 && rsp[k] == 0 && rsp[k+1] == 1020)
         k++; // skip second half of double spike
   }
}

//--------------------------------------------------------------------

void WP::CalibrateWaveforms()
{
   for (auto it = mEvent.begin() ; it != mEvent.end() ; it++) {
      auto ev = (*it);
      
      // search board belonging to this event
      WDB* wdb = nullptr;
      for (auto b: mWdb)
         if (b->GetSerialNumber() == ev->mBoardId) {
            wdb = b;
            break;
         }
      assert(wdb);
      
      if (ev->mWFTypeADC) { //---------- calibrate ADC data ----------
         
         ev->mTCalibrated = true;
         
         if (mRangeCalib) {
            float ofs;
            
            ev->mVCalibrated = true;
            for (int i=0 ; i<WD_N_CHANNELS-2 ; i++) { // exclude clock channels
               if (fabs(wdb->GetRange() - (-0.45)) < 0.001)
                  ofs = wdb->mVCalib.mCalib.adc_offset_range0[i];
               else if (fabs(wdb->GetRange()) < 0.001)
                  ofs = wdb->mVCalib.mCalib.adc_offset_range1[i];
               else if (fabs(wdb->GetRange() - 0.45) < 0.001)
                  ofs = wdb->mVCalib.mCalib.adc_offset_range2[i];
               else
                  ofs = 0;
               for (int j=0 ; j<1024 ; j++)
                  ev->mWfU[i][j] -= ofs;
            }
         }
         
         // just set nominal time bins from ADC sampling rate
         for (int i=0 ; i<WD_N_CHANNELS ; i++)
            for (int j=0 ; j<1024 ; j++)
               ev->mWfT[i][j] = (float)(j * 1E-6/ev->mSamplingFrequency);

         // shift ADC values
         for (int i=0 ; i<WD_N_CHANNELS ; i++)
            for (int j=0 ; j<1024 ; j++)
               ev->mWfU[i][j] += 0.35;

      } else {  //---------- calibrate DRS data ----------

         bool bValid = (ev->mSamplingFrequency == wdb->mVCalib.GetSamplingFrequency() &&
                        wdb->mVCalib.IsValid());

         // cell-by-cell offset calibration
         if (mOfsCalib1 && bValid) {
            ev->mVCalibrated = true;

            if (mRotateWaveform) {
               for (int i=0 ; i<WD_N_CHANNELS ; i++) {
                  int tc = i < 8 || i == 16  ? ev->mTriggerCell[0] : ev->mTriggerCell[1];
                  for (int j=0 ; j<1024 ; j++)
                     ev->mWfU[i][j] -= wdb->mVCalib.mCalib.wf_offset1[i][(j+tc) % 1024];
               }
            } else {
               for (int i=0 ; i<WD_N_CHANNELS ; i++)
                  for (int j=0 ; j<1024 ; j++)
                     ev->mWfU[i][j] -= wdb->mVCalib.mCalib.wf_offset1[i][j];
            }
         };
         
         // start-to-end offset calibration
         if (mOfsCalib2 && bValid) {
            for (int i=0 ; i<WD_N_CHANNELS ; i++)
               for (int j=0 ; j<1024 ; j++)
                  ev->mWfU[i][j] -= wdb->mVCalib.mCalib.wf_offset2[i][j];
         };
         
         // gain calibration
         if (mGainCalib && bValid) {
            if (mRotateWaveform) {
               for (int i=0 ; i<WD_N_CHANNELS-2 ; i++) { // exclude clock channels
                  int tc = i < 8 || i == 16  ? ev->mTriggerCell[0] : ev->mTriggerCell[1];
                  for (int j=0 ; j<1024 ; j++) {
                     if (ev->mWfU[i][j] > 0)
                        ev->mWfU[i][j] /= wdb->mVCalib.mCalib.wf_gain1[i][(j+tc) % 1024];
                     else
                        ev->mWfU[i][j] /= wdb->mVCalib.mCalib.wf_gain2[i][(j+tc) % 1024];
                  }
               }
            } else {
               for (int i=0 ; i<WD_N_CHANNELS-2 ; i++)
                  for (int j=0 ; j<1024 ; j++) {
                     if (ev->mWfU[i][j] > 0)
                        ev->mWfU[i][j] /= wdb->mVCalib.mCalib.wf_gain1[i][j];
                     else
                        ev->mWfU[i][j] /= wdb->mVCalib.mCalib.wf_gain2[i][j];
                  }
            }
         };
         
         // range calibration
         if (mRangeCalib && bValid) {
            float ofs;
            
            for (int i=0 ; i<WD_N_CHANNELS-2 ; i++) { // exclude clock channels
               if (fabs(wdb->GetRange() - (-0.45)) < 0.001)
                  ofs = wdb->mVCalib.mCalib.drs_offset_range0[i];
               else if (fabs(wdb->GetRange()) < 0.001)
                  ofs = wdb->mVCalib.mCalib.drs_offset_range1[i];
               else if (fabs(wdb->GetRange() - 0.45) < 0.001)
                  ofs = wdb->mVCalib.mCalib.drs_offset_range2[i];
               else
                  ofs = 0;
               for (int j=0 ; j<1024 ; j++)
                  ev->mWfU[i][j] -= ofs;
            }
         };

         // remove spikes
         if (mRemoveSpikes) {
            RemoveSpikes(ev->mTriggerCell[0], ev->mWfU);
            RemoveSpikes(ev->mTriggerCell[0], ev->mWfU+WD_N_CHANNELS/2);
         };

         // calculate calibrated time for each event
         bValid = (ev->mSamplingFrequency == wdb->mTCalib.GetSamplingFrequency() &&
                   wdb->mTCalib.IsValid());
         if (mTimeCalib1 && bValid) {
            ev->mTCalibrated = true;
 
            // integrate time from delta-t values
            for (int ch=0 ; ch<WD_N_CHANNELS ; ch++) {
               int tc = ch < 8 || ch == 16  ? ev->mTriggerCell[0] : ev->mTriggerCell[1];
               if (!mRotateWaveform)
                  tc = 0;
               ev->mWfT[ch][0] = 0;
               for (int i=1 ; i<1024 ; i++)
                  ev->mWfT[ch][i] = ev->mWfT[ch][i-1] + wdb->mTCalib.mCalib.dt[ch][(i-1+tc)%1024];
            }
            // align cell#0 of all channels inside chip0
            int tc = mRotateWaveform ? ev->mTriggerCell[0] : 0;
            float t1 = ev->mWfT[0][(1024-tc) % 1024];
            for (int ch=1 ; ch<8 ; ch++) {
               float t2 = ev->mWfT[ch][(1024-tc) % 1024];
               float dt = t1 - t2;
               for (int i=0 ; i<1024 ; i++)
                  ev->mWfT[ch][i] += dt;
            }
            float t2 = ev->mWfT[16][(1024-tc) % 1024];
            float dt = t1 - t2;
            for (int i=0 ; i<1024 ; i++)
               ev->mWfT[16][i] += dt;
            
            // align cell#0 of all channels inside chip1 to chip0
            tc = mRotateWaveform ? ev->mTriggerCell[1] : 0;
            for (int ch=8 ; ch<16 ; ch++) {
               float t2 = ev->mWfT[ch][(1024-tc) % 1024];
               float dt = t1 - t2;
               for (int i=0 ; i<1024 ; i++)
                  ev->mWfT[ch][i] += dt;
            }
            t2 = ev->mWfT[17][(1024-tc) % 1024];
            dt = t1 - t2;
            for (int i=0 ; i<1024 ; i++)
               ev->mWfT[17][i] += dt;
            
         } else {
            // set nominal sampling intervals
            for (int i=0 ; i<WD_N_CHANNELS ; i++)
               for (int j=0 ; j<1024 ; j++)
                  ev->mWfT[i][j] = (float)(j * 1E-6/ev->mSamplingFrequency);
         }
         
         // apply time offsets (different PCB path traces)
         if (mTimeCalib2 && bValid) {
            for (int i=0 ; i<WD_N_CHANNELS ; i++)
               for (int j=0 ; j<1024 ; j++)
                  ev->mWfT[i][j] -= wdb->mTCalib.mCalib.offset[i];
         }

         // apply horizontal trigger position correction
         if (mTimeCalib3 && bValid) {
            bool bFound = false;
            for (int i=4 ; i<1020 ; i++) {
               for (int c=0 ; c<16 ; c++) {
                  if ((GetEventRequestMask(ev->mBoardId) & (1 << c)) == 0)
                     continue;
                  
                  double tl = wdb->GetDacTriggerLevelV(c);
                  if (wdb->IsTriggerFallingEdge()) {
                     if ((GetEventRequestMask(ev->mBoardId) & (1 << c)) > 0) {
                        // falling edge
                        if (ev->mWfU[c][i] > tl && ev->mWfU[c][i+1] <= tl) {
                           double t0 = ev->mWfT[c][i] + (ev->mWfT[c][i+1]-ev->mWfT[c][i])*(tl-ev->mWfU[c][i])/(ev->mWfU[c][i+1]-ev->mWfU[c][i]);
                           t0 -= 1024*1E-6/wdb->GetDrsSampleFreq() - 30E-9 - wdb->GetTriggerDelayNs() * 1E-9;
                           for (i=0 ; i<WD_N_CHANNELS ; i++)
                              for (int j=0 ; j<1024 ; j++)
                                 ev->mWfT[i][j] -= (float)t0;
                           bFound = true;
                           break;
                        }
                     }
                  } else {
                     // rising edge
                     if (ev->mWfU[c][i] < tl && ev->mWfU[c][i+1] >= tl) {
                        double t0 = ev->mWfT[c][i] + (ev->mWfT[c][i+1]-ev->mWfT[c][i])*(tl-ev->mWfU[c][i])/(ev->mWfU[c][i+1]-ev->mWfU[c][i]);
                        t0 -= 1024*1E-6/wdb->GetDrsSampleFreq() - 30E-9 - wdb->GetTriggerDelayNs() * 1E-9;
                        for (i=0 ; i<WD_N_CHANNELS ; i++)
                           for (int j=0 ; j<1024 ; j++)
                              ev->mWfT[i][j] -= (float)t0;
                        bFound = true;
                        break;
                     }
                  }
               }
               if (bFound)
                  break;
            }
         }
      }
   }
}

//--------------------------------------------------------------------

typedef struct {
   unsigned short Year;
   unsigned short Month;
   unsigned short Day;
   unsigned short Hour;
   unsigned short Minute;
   unsigned short Second;
   unsigned short Milliseconds;
} TIMESTAMP;

void GetTimeStamp(TIMESTAMP &ts)
{
#ifdef _MSC_VER
   SYSTEMTIME t;
   static unsigned int ofs = 0;
   
   GetLocalTime(&t);
   if (ofs == 0)
      ofs = timeGetTime() - t.wMilliseconds;
   ts.Year         = t.wYear;
   ts.Month        = t.wMonth;
   ts.Day          = t.wDay;
   ts.Hour         = t.wHour;
   ts.Minute       = t.wMinute;
   ts.Second       = t.wSecond;
   ts.Milliseconds = (timeGetTime() - ofs) % 1000;
#else
   struct timeval t;
   struct tm *lt;
   time_t now;
   
   gettimeofday(&t, NULL);
   time(&now);
   lt = localtime(&now);
   
   ts.Year         = lt->tm_year+1900;
   ts.Month        = lt->tm_mon+1;
   ts.Day          = lt->tm_mday;
   ts.Hour         = lt->tm_hour;
   ts.Minute       = lt->tm_min;
   ts.Second       = lt->tm_sec;
   ts.Milliseconds = t.tv_usec/1000;
#endif /* OS_UNIX */
}

//--------------------------------------------------------------------

void WP::SaveWaveforms()
{
   static unsigned char *buffer = NULL;
   unsigned char *p;
   
   int buffer_size = 8 + 4 + (1024*4+12)*18 + (1024*2+12)*18;
   if (!buffer)
      buffer = (unsigned char *)malloc(buffer_size);
   
   if (li.fh == 0 && li.xml == NULL)
      return;
   
   TIMESTAMP ts;
   GetTimeStamp(ts);
   
   if (li.format == cLiFormatXML) {
      char str[256];
      mxml_start_element(li.xml, "Event");
      sprintf(str, "%d", li.nLogged+1);
      mxml_write_element(li.xml, "Serial", str);
      sprintf(str, "%4d/%02d/%02d %02d:%02d:%02d.%03d", ts.Year, ts.Month,
              ts.Day, ts.Hour, ts.Minute, ts.Second, ts.Milliseconds);
      mxml_write_element(li.xml, "Time", str);
      mxml_write_element(li.xml, "HUnit", "ns");
      mxml_write_element(li.xml, "VUnit", "mV");
      
      for (auto it = mEvent.begin() ; it != mEvent.end() ; it++) {
         auto ev = (*it);
         int mask = GetEventRequestMask(ev->mBoardId);
         
         sprintf(str, "Board_%d", ev->mBoardId);
         mxml_start_element(li.xml, str);
         for (int i=0 ; i<WD_N_CHANNELS ; i++) {
            if (mask & (1 << i)) {
               sprintf(str, "CHN%d", i);
               mxml_start_element(li.xml, str);
               sprintf(str, "%d", i < 8 || i == 16 ? ev->mTriggerCell[0] : ev->mTriggerCell[1]);
               mxml_write_element(li.xml, "Trigger_Cell", str);
               
               unsigned int s = 0;
               for (auto &b: mWdb)
                  if (b->GetSerialNumber() == ev->mBoardId) {
                     std::vector<unsigned long>sc;
                     b->GetScalers(sc, false);
                     s = sc[i];
                     break;
                  }
               sprintf(str, "%u", s);
               mxml_write_element(li.xml, "Scaler", str);

               mxml_start_element(li.xml, "Waveform");
               strcpy(str, "\n");
               for (int j=0 ; j<1024 ; j++) {
                  sprintf(str, "%1.3f,%1.1f", ev->mWfT[i][j]*1E9, ev->mWfU[i][j]*1E3);
                  mxml_write_element(li.xml, "Data", str);
               }
               mxml_end_element(li.xml); // CHNx
               mxml_end_element(li.xml); // CHNx
            }
         }
         mxml_end_element(li.xml); //Board
      }
      mxml_end_element(li.xml); // Event
   }
   
   if (li.format == cLiFormatBinary) {
      p = buffer;
      
      if (li.nLogged == 0) {
         memcpy(p, "DRS8", 4); // File identifier and version
         p += 4;
         
         // time calibration header
         memcpy(p, "TIME", 4);
         p += 4;
         
         for (auto it = mEvent.begin() ; it != mEvent.end() ; it++) {
            auto ev = (*it);
            int mask = GetEventRequestMask(ev->mBoardId);
            WDB *wdb = GetBoard(ev->mBoardId);
            assert(wdb);

            // store board serial number
            sprintf((char *)p, "B#");
            p += 2;
            *(unsigned short *)p = ev->mBoardId;
            p += sizeof(unsigned short);
            
            for (int i=0 ; i<WD_N_CHANNELS ; i++) {
               if (mask & (1 << i)) {
                  
                  sprintf((char *)p, "C%03d", i);
                  p += 4;
                  for (int j=0 ; j<1024 ; j++) {
                     // save binary time as 32-bit float value
                     *(float *)p = wdb->mTCalib.mCalib.dt[i][j];
                     p += sizeof(float);
                  }
               }
            }
         }
      }
      
      memcpy(p, "EHDR", 4);
      p += 4;
      *(int *)p = li.nLogged;
      p += sizeof(int);
      *(unsigned short *)p = ts.Year;
      p += sizeof(unsigned short);
      *(unsigned short *)p = ts.Month;
      p += sizeof(unsigned short);
      *(unsigned short *)p = ts.Day;
      p += sizeof(unsigned short);
      *(unsigned short *)p = ts.Hour;
      p += sizeof(unsigned short);
      *(unsigned short *)p = ts.Minute;
      p += sizeof(unsigned short);
      *(unsigned short *)p = ts.Second;
      p += sizeof(unsigned short);
      *(unsigned short *)p = ts.Milliseconds;
      p += sizeof(unsigned short);
      *(unsigned short *)p = (unsigned short)(0); // range
      p += sizeof(unsigned short);
      
      for (auto it = mEvent.begin() ; it != mEvent.end() ; it++) {
         auto ev = (*it);
         int mask = GetEventRequestMask(ev->mBoardId);
         
         // store board serial number
         sprintf((char *)p, "B#");
         p += 2;
         *(unsigned short *)p = ev->mBoardId;
         p += sizeof(unsigned short);
         
         for (int i=0 ; i<WD_N_CHANNELS ; i++) {
            if (mask & (1 << i)) {
               // channel header
               sprintf((char *)p, "C%03d", i);
               p += 4;
               
               // write scaler
               WDB *wdb = GetBoard(ev->mBoardId);
               assert(wdb);
               
               std::vector<unsigned long>sc;
               wdb->GetScalers(sc, false);
               unsigned int s = sc[i];
               memcpy(p, &s, sizeof(unsigned int));
               p += sizeof(int);
               
               // write trigger cell
               sprintf((char *)p, "T#");
               p += 2;
               *(unsigned short *)p = i < 8 || i == 16 ? ev->mTriggerCell[0] : ev->mTriggerCell[1];
               p += sizeof(unsigned short);
               
               for (int j=0 ; j<1024 ; j++) {
                  // save binary date as 16-bit value:
                  // 0 = -0.5V,  65535 = +0.5V    for range 0
                  // 0 = -0.05V, 65535 = +0.95V   for range 0.45
                  unsigned short d = (unsigned short)((ev->mWfU[i][j] - wdb->GetRange() + 0.5) * 65535);
                  *(unsigned short *)p = d;
                  p += sizeof(unsigned short);
               }
            }
         }
      }
      
      int size = p - buffer;
      int n = write(li.fh, buffer, size);
      assert(n == size);
      assert(size < buffer_size);
   }
   
   li.nLogged++;

   if (li.nLogged == li.nRequest && li.fh) {
      close(li.fh);
      li.fh = 0;
   }

   if (li.nLogged == li.nRequest && li.xml) {
      mxml_close_file(li.xml);
      li.xml = NULL;
   }
}

//--------------------------------------------------------------------

void WP::Collector()
{
   mCurrentEvent = -1;
   
   if (mVerbose)
      std::cout << std::endl << "Started waveform collector." << std::endl;

   do {

      InvalidateAllWf();
      
      do {
         
         ReceiveWfPacket();

      } while (!AllPacketsReceived());
      
      
      // do various calibrations
      RotateWaveforms();
      CalibrateWaveforms();
      SaveWaveforms();
      
      {
         std::lock_guard<std::mutex> lock(mEventAccessMutex);
   
         if (!mEventNew) {
            // copy last event
            auto es = mEvent.begin();
            auto ed = mEventLast.begin();
      
            while (es != mEvent.end())
               **(ed++) = **(es++);
      
            mEventNew = true;
         }
      }
      mEventCV.notify_one();
      
   } while (1);
   
}

//--------------------------------------------------------------------

void WP::DoCalibrationVoltageStep()
{
   if (calibProg.state == cCsFirstBoard) {
      calibProg.state    = cCsFirstSample;
      calibProg.progress = 0;
      calibProg.nIter1   = 200;
      calibProg.nIter2   = 200;
      calibProg.nIter3   = 200;
      calibProg.nIter4   = 200;
      calibProg.iIter1   = 0;
      calibProg.iIter2   = 0;
      calibProg.iIter3   = 0;
      calibProg.iIter4   = 0;
   }
   
   WDB *b = mWdb[calibProg.iBoard];

   if (calibProg.state == cCsFirstSample) {
      calibProg.progress = 0;
      calibProg.iIter1   = 0;
      calibProg.iIter2   = 0;
      calibProg.iIter3   = 0;
      calibProg.iIter4   = 0;
      calibProg.state    = cCsRunning;

      // save current board settings
      mOldRange = b->GetRange();
      mOldMask0 = b->GetDrs0ChnTxEnable();
      mOldMask1 = b->GetDrs1ChnTxEnable();
      
      mOldReadoutSrc  = b->GetReadoutSrcSel();
      mOldCalibClock  = b->IsTimingCalibSignalEnable();
      mOldFeMux       = b->GetFeMux(0);
      mOldCalibBuffer = b->IsCalibBufferEnable();
      
      b->mVCalib.mCalib.sampling_frequency = b->GetDrsSampleFreq();
      
      // turn off all calibration
      mRotateWaveform      = false;
      mOfsCalib1           = false;
      mOfsCalib2           = false;
      mGainCalib           = false;
      mRangeCalib          = false;
      mRemoveSpikes        = false;
      
      // turn on power for calibration input (needed for clock channels)
      b->SetCalibBufferEnable(true);

      // turn off calibration clock
      b->SetTimingCalibSignalEnable(false);
      
      // switch multiplexer to calibration source
      b->SetFeMux(-1, WDB::cFeMuxCalSource);
      
      // enable all channels
      b->SetReadoutSrcSel(WDB::cReadoutSrcDrs);
      b->SetDrs0ChnTxEnable(0x1FF);
      b->SetDrs1ChnTxEnable(0x1FF);
      
      // range -0.5 ... + 0.5V
      b->SetRange(0);
      
      // set gain 1
      b->SetFeGain(-1, 1);
      
      // set offset zero
      b->SetDacCalDcV(0);
      
      int n = calibProg.nIter1;
      n = std::max(n, calibProg.nIter2);
      n = std::max(n, calibProg.nIter3);
      n = std::max(n, calibProg.nIter4);
      
      calibProg.ave = new Averager(1, WD_N_CHANNELS, 1024, n);
   }
   
   //---- Primary Calibration ----
   
   
   if (calibProg.iIter1 < calibProg.nIter1) {
      
      calibProg.iIter1++;
      
      // get one event from board
      WDEvent event(b->GetSerialNumber());
      if (!RequestEvent(b, 1000, event))
         return; // just skip this event
      
      for (int ch=0 ; ch<WD_N_CHANNELS ; ch++)
         for (int bin=0 ; bin<1024 ; bin++)
            calibProg.ave->Add(0, ch, bin, event.mWfU[ch][bin]);
      
      calibProg.progress = (double)(calibProg.iIter1 + calibProg.iIter2 + calibProg.iIter3 + calibProg.iIter4) /
      (calibProg.nIter1 + calibProg.nIter2 + calibProg.nIter3 + calibProg.nIter4);
      
      // calibration finished
      if (calibProg.iIter1 == calibProg.nIter1) {
         for (int ch=0 ; ch<WD_N_CHANNELS ; ch++)
            for (int bin=0 ; bin<1024 ; bin++)
               b->mVCalib.mCalib.wf_offset1[ch][bin] = (float)calibProg.ave->Median(0, ch, bin);
         
         // ave->SaveNormalizedDistribution("wf.csv", 0);
         calibProg.ave->Reset();
      }
      
      sleep_ms(10); // obtain 100 Hz rate
      return;
   }
   
   //---- Secondary Calibration
   
   if (calibProg.iIter2 < calibProg.nIter2) {
      
      // initialize data on first iteration
      if (calibProg.iIter2 == 0) {
         calibProg.ave->Reset();
         mRotateWaveform      = true;  // rotate waveforms
         mOfsCalib1           = true;  // do 1st calibration
         b->mVCalib.SetValid(true);
      }
      
      calibProg.iIter2++;
      
      // get one event from board
      WDEvent event(b->GetSerialNumber());
      if (!RequestEvent(b, 1000, event))
         return; // just skip this event
      
      for (int ch=0 ; ch<WD_N_CHANNELS ; ch++)
         for (int bin=0 ; bin<1024 ; bin++)
            calibProg.ave->Add(0, ch, bin, event.mWfU[ch][bin]);
      
      calibProg.progress = (double)(calibProg.iIter1 + calibProg.iIter2 + calibProg.iIter3 + calibProg.iIter4) /
      (calibProg.nIter1 + calibProg.nIter2 + calibProg.nIter3 + calibProg.nIter4);
      
      // calibration finished
      if (calibProg.iIter2 == calibProg.nIter2) {
         for (int ch=0 ; ch<WD_N_CHANNELS ; ch++)
            for (int bin=0 ; bin<1024 ; bin++)
               b->mVCalib.mCalib.wf_offset2[ch][bin] = (float)calibProg.ave->Median(0, ch, bin);
         
         calibProg.ave->Reset();
      }
      
      sleep_ms(10); // obtain 100 Hz rate
      return;
   }
   
   //---- Positive Gain Calibration
   
   if (calibProg.iIter3 < calibProg.nIter3) {
      
      // initialize data on first iteration
      if (calibProg.iIter3 == 0) {
         calibProg.ave->Reset();
         mRotateWaveform      = true;  // rotate waveforms
         mOfsCalib1           = true;  // do 1st calibration
         mOfsCalib2           = true;  // do 2nd calibration

         b->SetDacCalDcV(0.45);
      }
      
      calibProg.iIter3++;
      
      // get one event from board
      WDEvent event(b->GetSerialNumber());
      if (!RequestEvent(b, 1000, event))
         return; // just skip this event
      
      for (int ch=0 ; ch<WD_N_CHANNELS-2 ; ch++)
         for (int bin=0 ; bin<1024 ; bin++)
            calibProg.ave->Add(0, ch, bin, event.mWfU[ch][bin]);
      
      calibProg.progress = (double)(calibProg.iIter1 + calibProg.iIter2 + calibProg.iIter3 + calibProg.iIter4) /
      (calibProg.nIter1 + calibProg.nIter2 + calibProg.nIter3 + calibProg.nIter4);
      
      // calibration finished
      if (calibProg.iIter3 == calibProg.nIter3) {
         for (int ch=0 ; ch<WD_N_CHANNELS-2 ; ch++) // exclude clock channels
            for (int bin=0 ; bin<1024 ; bin++)
               b->mVCalib.mCalib.wf_gain1[ch][bin] = (float)(calibProg.ave->Median(0, ch, bin) / 0.45);
         
         calibProg.ave->Reset();
      }
      
      sleep_ms(10); // obtain 100 Hz rate
      return;
   }
   
   //---- Negative Gain Calibration
   
   if (calibProg.iIter4 < calibProg.nIter4) {
      
      // initialize data on first iteration
      if (calibProg.iIter4 == 0) {
         calibProg.ave->Reset();
         
         b->SetDacCalDcV(-0.45);
      }
      
      calibProg.iIter4++;
      
      // get one event from board
      WDEvent event(b->GetSerialNumber());
      if (!RequestEvent(b, 1000, event))
         return; // just skip this event
      
      for (int ch=0 ; ch<WD_N_CHANNELS-2 ; ch++)
         for (int bin=0 ; bin<1024 ; bin++)
            calibProg.ave->Add(0, ch, bin, event.mWfU[ch][bin]);
      
      calibProg.progress = (double)(calibProg.iIter1 + calibProg.iIter2 + calibProg.iIter3 + calibProg.iIter4) /
      (calibProg.nIter1 + calibProg.nIter2 + calibProg.nIter3 + calibProg.nIter4);
      
      // calibration finished
      if (calibProg.iIter4 == calibProg.nIter4) {
         for (int ch=0 ; ch<WD_N_CHANNELS-2 ; ch++) // exclude clock channels
            for (int bin=0 ; bin<1024 ; bin++)
               b->mVCalib.mCalib.wf_gain2[ch][bin] = (float)(calibProg.ave->Median(0, ch, bin) / -0.45);
         
         delete calibProg.ave;
         calibProg.ave = NULL;
      }
      
      sleep_ms(10); // obtain 100 Hz rate
      return;
   }
   
   mRotateWaveform = true;
   mOfsCalib1      = true;
   mOfsCalib2      = true;
   mGainCalib      = true;
   mRangeCalib     = false;
   mRemoveSpikes   = false;

   // measure offset at different ranges
   
   // Range -0.45
   b->SetDacCalDcV(0);
   b->SetRange(-0.45);

   // DRS events
   b->SetReadoutSrcSel(WDB::cReadoutSrcDrs);
   WDEvent event(b->GetSerialNumber());
   for (int i=0 ; i<10 ; i++) {
      RequestEvent(b, 1000, event);
      sleep_ms(10);
   }
   while (!RequestEvent(b, 1000, event));
   
   for (int ch=0 ; ch<WD_N_CHANNELS-2 ; ch++) {
      float sum = 0;
      for (int i=10 ; i<1020 ; i++)
         sum += event.mWfU[ch][i];
      b->mVCalib.mCalib.drs_offset_range0[ch] = sum / 1010;
   }
   
   // ADC events
   b->SetReadoutSrcSel(WDB::cReadoutSrcAdc);
   for (int i=0 ; i<10 ; i++) {
      RequestEvent(b, 1000, event);
      sleep_ms(10);
   }
   while (!RequestEvent(b, 1000, event));
   
   for (int ch=0 ; ch<WD_N_CHANNELS-2 ; ch++) {
      float sum = 0;
      for (int i=10 ; i<1020 ; i++)
         sum += event.mWfU[ch][i];
      b->mVCalib.mCalib.adc_offset_range0[ch] = sum / 1010;
   }
   
   // Range 0
   b->SetRange(0);
   
   // DRS events
   b->SetReadoutSrcSel(WDB::cReadoutSrcDrs);
   for (int i=0 ; i<10 ; i++) {
      RequestEvent(b, 1000, event);
      sleep_ms(10);
   }
   while (!RequestEvent(b, 1000, event));
   
   for (int ch=0 ; ch<WD_N_CHANNELS-2 ; ch++) {
      float sum = 0;
      for (int i=10 ; i<1020 ; i++)
         sum += event.mWfU[ch][i];
      b->mVCalib.mCalib.drs_offset_range1[ch] = sum / 1010;
   }
   
   // ADC events
   b->SetReadoutSrcSel(WDB::cReadoutSrcAdc);
   for (int i=0 ; i<10 ; i++) {
      RequestEvent(b, 1000, event);
      sleep_ms(10);
   }
   while (!RequestEvent(b, 1000, event));
   
   for (int ch=0 ; ch<WD_N_CHANNELS-2 ; ch++) {
      float sum = 0;
      for (int i=10 ; i<1020 ; i++)
         sum += event.mWfU[ch][i];
      b->mVCalib.mCalib.adc_offset_range1[ch] = sum / 1010;
   }
   
   // Range 0.45
   b->SetRange(0.45);
   
   // DRS events
   b->SetReadoutSrcSel(WDB::cReadoutSrcDrs);
   for (int i=0 ; i<10 ; i++) {
      RequestEvent(b, 1000, event);
      sleep_ms(10);
   }
   while (!RequestEvent(b, 1000, event));
   
   for (int ch=0 ; ch<WD_N_CHANNELS-2 ; ch++) {
      float sum = 0;
      for (int i=10 ; i<1020 ; i++)
         sum += event.mWfU[ch][i];
      b->mVCalib.mCalib.drs_offset_range2[ch] = sum / 1010;
   }
   
   // ADC events
   b->SetReadoutSrcSel(WDB::cReadoutSrcAdc);
   for (int i=0 ; i<10 ; i++) {
      RequestEvent(b, 1000, event);
      sleep_ms(10);
   }
   while (!RequestEvent(b, 1000, event));
   
   for (int ch=0 ; ch<WD_N_CHANNELS-2 ; ch++) {
      float sum = 0;
      for (int i=10 ; i<1020 ; i++)
         sum += event.mWfU[ch][i];
      b->mVCalib.mCalib.adc_offset_range2[ch] = sum / 1010;
   }
   
   delete calibProg.ave;
   calibProg.ave = NULL;

   // save calibration
   b->SaveVoltageCalibration(b->GetDrsSampleFreq());
   
   // switch to next board
   calibProg.iBoard++;
   calibProg.state    = cCsFirstSample;
   calibProg.progress = 1;
   
   // switch back to old board settings
   b->SetRange(mOldRange);
   b->SetDrs0ChnTxEnable(mOldMask0);
   b->SetDrs1ChnTxEnable(mOldMask1);
   
   b->SetReadoutSrcSel(mOldReadoutSrc);
   b->SetTimingCalibSignalEnable(mOldCalibClock);
   b->SetFeMux(-1, mOldFeMux);
   b->SetCalibBufferEnable(mOldCalibBuffer);
   
   if (calibProg.iBoard == calibProg.nBoard) {
      calibProg.state = cCsInactive;
      calibProg.mode  = cCmNone;
      
      mRangeCalib     = true;
      mRemoveSpikes   = true;
   }
   
   return;
}

//--------------------------------------------------------------------

void WP::AnalyzePeriod(WDEvent *event, WDB *b)
{
   for (int ch=0 ; ch<WD_N_CHANNELS ; ch++) {
      int tc = ch < 8 || ch == 16 ? event->mTriggerCell[0] : event->mTriggerCell[1];
      
      // rising edges
      for (int i1=tc+5; i1<tc+1024-5 ; i1++) {
         if (event->mWfU[ch][i1 % 1024] <= 0 && event->mWfU[ch][(i1+1) % 1024] > 0) {
            for (int i2=i1+1 ; i2<i1+1024 && i2<tc+1024-3; i2++) {
               if (event->mWfU[ch][i2 % 1024] <= 0 && event->mWfU[ch][(i2+1) % 1024] > 0) {
                  
                  // first partial cell
                  double tPeriod = b->mTCalib.mCalib.dt[ch][i1%1024]*(1/(1-event->mWfU[ch][i1%1024]/event->mWfU[ch][(i1+1)%1024]));
                  
                  // full cells between i1 and i2
                  if (i2 < i1)
                     i2 += 1024;
                  for (int j=i1+1 ; j<i2 ; j++)
                     tPeriod += b->mTCalib.mCalib.dt[ch][j%1024];
                  
                  // second partial cell
                  tPeriod += b->mTCalib.mCalib.dt[ch][i2 % 1024]*(1/(1-event->mWfU[ch][(i2+1)%1024]/event->mWfU[ch][i2%1024]));
                  
                  b->mTCalib.mCalib.period[ch][i1%1024] = (float)tPeriod;
                  
                  break;
               }
            }
         }
      }
      
      // falling edges
      for (int i1=tc+5; i1<tc+1024-5 ; i1++) {
         if (event->mWfU[ch][i1 % 1024] >= 0 && event->mWfU[ch][(i1+1) % 1024] < 0) {
            for (int i2=i1+1 ; i2<i1+1024 && i2<tc+1024-3; i2++) {
               if (event->mWfU[ch][i2 % 1024] >= 0 && event->mWfU[ch][(i2+1) % 1024] < 0) {
                  
                  // first partial cell
                  double tPeriod = b->mTCalib.mCalib.dt[ch][i1%1024]*(1/(1-event->mWfU[ch][i1%1024]/event->mWfU[ch][(i1+1)%1024]));
                  
                  // full cells between i1 and i2
                  if (i2 < i1)
                     i2 += 1024;
                  for (int j=i1+1 ; j<i2 ; j++)
                     tPeriod += b->mTCalib.mCalib.dt[ch][j%1024];
                  
                  // second partial cell
                  tPeriod += b->mTCalib.mCalib.dt[ch][i2 % 1024]*(1/(1-event->mWfU[ch][(i2+1)%1024]/event->mWfU[ch][i2%1024]));
                  
                  b->mTCalib.mCalib.period[ch][i1%1024] = (float)tPeriod;
                  
                  break;
               }
            }
         }
      }
   }
}

/*-----------------------------------------------------------------------------------------*/

void WP::AnalyzeTimeOffset(WDEvent *event, WDB *b)
{
   
   // find rising edge in channel #0
   for (int i=10; i<1024-10 ; i++) {
      if (event->mWfU[0][i] <= 0 && event->mWfU[0][i+1] > 0) {
         double t0 = event->mWfT[0][i] + (event->mWfT[0][i+1]-event->mWfT[0][i]) * (event->mWfU[0][i]/(event->mWfU[0][i]-event->mWfU[0][i+1]));
         
         for (int ch=1 ; ch<WD_N_CHANNELS ; ch++) {
            for (int j=10; j<1024-10 ; j++) {
               if (event->mWfU[ch][j] <= 0 && event->mWfU[ch][j+1] > 0) {
                  double t = event->mWfT[ch][j] + (event->mWfT[ch][j+1]-event->mWfT[ch][j])*(event->mWfU[ch][j]/(event->mWfU[ch][j]-event->mWfU[ch][j+1]));
                  double dt = t - t0;
                  if (ch > 15)
                     dt -= 2E-9; // timing channels have a 2 ns offset
                  if (fabs(dt) < 1E-9) {
                     calibProg.ave->Add(0, ch, 0, (float)dt);
                  }
               }
            }
         }
      }
   }
}

/*-----------------------------------------------------------------------------------------*/

void WP::CalibrateLocal(WDEvent *event, WDB *b)
{
   float dv, llim, ulim;
   
   if (b->GetDrsSampleFreq() >= 3000) {
      llim = -0.15f;
      ulim =  0.15f;
   } else {
      llim = -0.3f;
      ulim =  0.3f;
   }
   
   for (int ch=0 ; ch<WD_N_CHANNELS ; ch++) {
      int tc = ch < 8 || ch == 16 ? event->mTriggerCell[0] : event->mTriggerCell[1];
      
      for (int i=tc+5; i<tc+1024-5 ; i++) {
         
         // rising edges
         
         // test slope between previous and next cell to allow for negative cell width
         if (event->mWfU[ch][(i+1024-1) % 1024] < event->mWfU[ch][(i+2) % 1024] &&
             event->mWfU[ch][i % 1024] > llim &&
             event->mWfU[ch][(i+1) % 1024] < ulim) {
            
            // calculate delta_v
            dv = event->mWfU[ch][(i+1) % 1024] - event->mWfU[ch][i % 1024];
            
            // average delta_v
            calibProg.ave->Add(0, ch, i % 1024, dv);
         }
         
         // falling edges
         if (event->mWfU[ch][(i+1024-1) % 1024] > event->mWfU[ch][(i+2) % 1024] &&
             event->mWfU[ch][i % 1024] < ulim &&
             event->mWfU[ch][(i+1) % 1024] > llim) {
            
            // calculate delta_v
            dv = event->mWfU[ch][(i+1) % 1024] - event->mWfU[ch][i % 1024];
            
            // average delta_v
            calibProg.ave->Add(0, ch, i % 1024, -dv);
         }
      }
      
      // calculate calibration every 100 events
      if (calibProg.iIter1 % 100 == 0) {
         // average over all 1024 dU
         double sum = 0;
         double cellDV[1024];
         
         for (int i=0 ; i<1024 ; i++) {
            cellDV[i] = calibProg.ave->RobustAverage(0, ch, i);
            sum += cellDV[i];
         }
         
         sum /= 1024;
         double dtCell = 1.0/b->GetDrsSampleFreq()*1E-6;
         
         // here comes the central calculation, dT = dV/average * dtCell
         for (int i=0 ; i<1024 ; i++)
            b->mTCalib.mCalib.dt[ch][i] = (float)(cellDV[i] / sum * dtCell);
      }
      
   }
}

/*-----------------------------------------------------------------------------------------*/

void WP::CalibrateGlobal(WDEvent *event, WDB *b)
{
   float damping = 0.1f;
   
   for (int ch=0 ; ch<WD_N_CHANNELS ; ch++) {
      int tc = ch < 8 || ch == 16 ? event->mTriggerCell[0] : event->mTriggerCell[1];
      
      // rising edges
      for (int i1=tc+5; i1<tc+1024-5 ; i1++) {
         if (event->mWfU[ch][i1 % 1024] <= 0 && event->mWfU[ch][(i1+1) % 1024] > 0) {
            for (int i2=i1+1 ; i2<i1+1024 && i2<tc+1024-3; i2++) {
               if (event->mWfU[ch][i2 % 1024] <= 0 && event->mWfU[ch][(i2+1) % 1024] > 0) {
                  
                  // first partial cell
                  double tPeriod = b->mTCalib.mCalib.dt[ch][i1%1024]*(1/(1-event->mWfU[ch][i1%1024]/event->mWfU[ch][(i1+1)%1024]));
                  
                  // full cells between i1 and i2
                  if (i2 < i1)
                     i2 += 1024;
                  for (int j=i1+1 ; j<i2 ; j++)
                     tPeriod += b->mTCalib.mCalib.dt[ch][j%1024];
                  
                  // second partial cell
                  tPeriod += b->mTCalib.mCalib.dt[ch][i2 % 1024]*(1/(1-event->mWfU[ch][(i2+1)%1024]/event->mWfU[ch][i2%1024]));
                  
                  // calculate correction to nominal period of 10 ns as a fraction
                  float corr = (float)((10E-9) / tPeriod);
                  
                  // skip big corrections (probably noise)
                  if (corr > 1.01 || corr < 0.99)
                     continue;
                  
                  // apply damping factor
                  corr = (corr - 1)*damping + 1;
                  
                  // distribute correction equally into bin inside the region
                  for (int j=i1+1 ; j<i2 ; j++)
                     b->mTCalib.mCalib.dt[ch][j % 1024] *= corr;
                  
                  break;
               }
            }
         }
      }
      
      // falling edges
      for (int i1=tc+5; i1<tc+1024-5 ; i1++) {
         if (event->mWfU[ch][i1 % 1024] >= 0 && event->mWfU[ch][(i1+1) % 1024] < 0) {
            for (int i2=i1+1 ; i2<i1+1024 ; i2++) {
               if (event->mWfU[ch][i2 % 1024] >= 0 && event->mWfU[ch][(i2+1) % 1024] < 0) {
                  
                  // first partial cell
                  double tPeriod = b->mTCalib.mCalib.dt[ch][i1%1024]*(1/(1-event->mWfU[ch][i1%1024]/event->mWfU[ch][(i1+1)%1024]));
                  
                  // full cells between i1 and i2
                  if (i2 < i1)
                     i2 += 1024;
                  for (int j=i1+1 ; j<i2 ; j++)
                     tPeriod += b->mTCalib.mCalib.dt[ch][j%1024];
                  
                  // second partial cell
                  tPeriod += b->mTCalib.mCalib.dt[ch][i2 % 1024]*(1/(1-event->mWfU[ch][(i2+1)%1024]/event->mWfU[ch][i2%1024]));
                  
                  // calculate correction to nominal period of 10 ns as a fraction
                  float corr = (float)((10E-9) / tPeriod);
                  
                  // skip big corrections (probably noise)
                  if (corr > 1.01 || corr < 0.99)
                     continue;
                  
                  // apply damping factor
                  corr = (corr - 1)*damping + 1;
                  
                  // distribute correction equally into bin inside the region
                  for (int j=i1+1 ; j<i2 ; j++)
                     b->mTCalib.mCalib.dt[ch][j % 1024] *= corr;
                  
                  break;
               }
            }
         }
      }
   }
}

//--------------------------------------------------------------------

void WP::DoCalibrationTimeStep()
{
   
   if (calibProg.state == cCsFirstBoard) {
      
      calibProg.state       = cCsFirstSample;
      calibProg.nIter1      = 510; // multiple of 30!
      calibProg.nIter2      = 510;
      calibProg.nIter3      = 100;
      calibProg.nIter4      = 0;
      calibProg.phase       = 0;
      
      // turn off all calibration
      mRotateWaveform       = false;
      mOfsCalib1            = true;
      mOfsCalib2            = true;
      mGainCalib            = true;
      mRangeCalib           = true;
      mRemoveSpikes         = true;

      mTimeCalib1           = false;
      mTimeCalib2           = false;
      mTimeCalib3           = false;
   }
   
   WDB *b = mWdb[calibProg.iBoard];

   if (calibProg.state == cCsFirstSample) {
      calibProg.progress    = 0;
      calibProg.iIter1      = 0;
      calibProg.iIter2      = 0;
      calibProg.iIter3      = 0;
      calibProg.iIter4      = 0;
      calibProg.state       = cCsRunning;
      
      // save current board settings
      mOldRange = b->GetRange();
      mOldMask0 = b->GetDrs0ChnTxEnable();
      mOldMask1 = b->GetDrs1ChnTxEnable();
      
      mOldReadoutSrc  = b->GetReadoutSrcSel();
      mOldCalibClock  = b->IsTimingCalibSignalEnable();
      mOldFeMux       = b->GetFeMux(0);
      mOldCalibBuffer = b->IsCalibBufferEnable();

      b->mTCalib.mCalib.sampling_frequency = b->GetDrsSampleFreq();

      mRotateWaveform       = false;
      mTimeCalib1           = false;
      
      // initialize delta-t array with nominal values
      for (int ch=0 ; ch<WD_N_CHANNELS ; ch++)
         for (int bin=0 ; bin<1024 ; bin++) {
            b->mTCalib.mCalib.dt[ch][bin] = (float)(1.0/b->GetDrsSampleFreq()*1E-6); // [s]
            b->mTCalib.mCalib.period[ch][bin] = 0;
         }
      
      // range -0.5 ... + 0.5V
      b->SetRange(0);
      
      // set gain 1
      b->SetFeGain(-1, 1);
      
      // set offset zero
      b->SetDacCalDcV(0);

      // turn on calibration clock
      b->SetCalibBufferEnable(true);
      b->SetTimingCalibSignalEnable(true);
      b->SetFeMux(-1, WDB::cFeMuxCalSource);
      
      // enable all channels
      b->SetDrs0ChnTxEnable(0x1FF);
      b->SetDrs1ChnTxEnable(0x1FF);

      calibProg.phase = 0;
      b->SetTimingCalibSignalDelay(calibProg.phase);

      calibProg.ave = new Averager(1, WD_N_CHANNELS, 1024, std::max(calibProg.nIter1, calibProg.nIter2));
   }
   
   //---- Local Calibration ----
   
   if (calibProg.iIter1 < calibProg.nIter1) {
      
      calibProg.iIter1++;
      
      // switch phase of LMK clock
      if (calibProg.iIter1 % 10 == 0) {
         calibProg.phase++;
         if (calibProg.phase == 17)
            calibProg.phase = -16;
         b->SetTimingCalibSignalDelay(calibProg.phase);
      }
      
      // get one event from board
      WDEvent event(b->GetSerialNumber());
      if (!RequestEvent(b, 1000, event))
         return; // just skip this event
      
      AnalyzePeriod(&event, b);
      CalibrateLocal(&event, b);

      calibProg.progress = (double)(calibProg.iIter1 + calibProg.iIter2 + calibProg.iIter3) /
         (calibProg.nIter1 + calibProg.nIter2 + calibProg.nIter3);
      
      if (calibProg.iIter1 == calibProg.nIter1) {
         calibProg.ave->Reset();
         calibProg.phase = 0;
         b->SetTimingCalibSignalDelay(calibProg.phase);
      }
      
      sleep_ms(10); // obtain 100 Hz rate
      return;
   }
   
   //---- Global Calibration
   
   if (calibProg.iIter2 < calibProg.nIter2) {
      
      calibProg.iIter2++;
      
      // switch phase of LMK clock
      if (calibProg.iIter1 % 10 == 0) {
         calibProg.phase++;
         if (calibProg.phase == 17)
            calibProg.phase = -16;
         b->SetTimingCalibSignalDelay(calibProg.phase);
      }
      
      // get one event from board
      WDEvent event(b->GetSerialNumber());
      if (!RequestEvent(b, 1000, event))
         return; // just skip this event
      
      AnalyzePeriod(&event, b);
      CalibrateGlobal(&event, b);
      
      calibProg.progress = (double)(calibProg.iIter1 + calibProg.iIter2 + calibProg.iIter3) /
      (calibProg.nIter1 + calibProg.nIter2 + calibProg.nIter3);

      if (calibProg.iIter2 == calibProg.nIter2) {
         calibProg.ave->Reset();
         calibProg.phase = 0;
         b->SetTimingCalibSignalDelay(calibProg.phase);
         mRotateWaveform       = true;
         mTimeCalib1           = true;
         b->mTCalib.SetValid(true);
      }

      sleep_ms(10); // obtain 100 Hz rate
      return;
   }
   
   //---- Offset Calibration
   
   if (calibProg.iIter3 < calibProg.nIter3) {
      
      calibProg.iIter3++;
      
      // get one event from board
      WDEvent event(b->GetSerialNumber());
      if (!RequestEvent(b, 1000, event))
         return; // just skip this event
      
      AnalyzeTimeOffset(&event, b);
      
      calibProg.progress = (double)(calibProg.iIter1 + calibProg.iIter2 + calibProg.iIter3) /
      (calibProg.nIter1 + calibProg.nIter2 + calibProg.nIter3);
      
      if (calibProg.iIter3 == calibProg.nIter3) {
         b->mTCalib.mCalib.offset[0] = 0; // by definition
         for (int ch=1 ; ch<WD_N_CHANNELS ; ch++)
            b->mTCalib.mCalib.offset[ch] = (float)(calibProg.ave->RobustAverage(0, ch, 0));
      }
      
      sleep_ms(10); // obtain 100 Hz rate
      return;
   }
   
   delete calibProg.ave;
   calibProg.ave = NULL;
   
   b->SaveTimeCalibration(b->GetDrsSampleFreq());
   
   // switch to next board
   calibProg.iBoard++;
   calibProg.state    = cCsFirstSample;
   calibProg.progress = 1;
   
   // switch back to old board settings
   b->SetRange(mOldRange);
   b->SetDrs0ChnTxEnable(mOldMask0);
   b->SetDrs1ChnTxEnable(mOldMask1);
   
   b->SetReadoutSrcSel(mOldReadoutSrc);
   b->SetTimingCalibSignalEnable(mOldCalibClock);
   b->SetFeMux(-1, mOldFeMux);
   b->SetCalibBufferEnable(mOldCalibBuffer);

   if (calibProg.iBoard == calibProg.nBoard) {
      calibProg.state = cCsInactive;
      calibProg.mode  = cCmNone;
      
      mTimeCalib1     = true;
      mTimeCalib2     = true;
      mTimeCalib3     = true;
   }
}

//--------------------------------------------------------------------

void WP::StartWaveformSaving(std::string fileName, int format, bool all, int nEvents)
{
   li.fileName = fileName;
   li.format  = format;
   li.nRequest = nEvents;
   li.bAll  = all;
   li.nLogged = 0;
   
   if (li.format == cLiFormatBinary) {
      if (li.fh > 0)
         close(li.fh);
      
      li.fh = open(li.fileName.c_str(), O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0644);
      assert(li.fh > 0);
   }
   
   if (li.format == cLiFormatXML) {
      if (li.xml)
         mxml_close_file(li.xml);
      
      li.xml = mxml_open_file(li.fileName.c_str());
      assert(li.xml);
   }
}

//--------------------------------------------------------------------

void WP::StopLogging()
{
   li.nRequest = li.nLogged;
   if (li.fh) {
      close(li.fh);
      li.fh = 0;
   }
   if (li.xml) {
      mxml_close_file(li.xml);
      li.xml = NULL;
   }
   li.nLogged = 0;
}

//--------------------------------------------------------------------

VCALIB::VCALIB()
{
   bValid = false; // not yet loaded
   memset(mCalib.wf_offset1, 0, sizeof(float)*16*1024);
   memset(mCalib.wf_offset2, 0, sizeof(float)*16*1024);
   for (int ch=0 ; ch < WD_N_CHANNELS ; ch++) {
      for (int bin=0 ; bin<1024 ; bin++) {
         mCalib.wf_gain1[ch][bin] = 1;
         mCalib.wf_gain2[ch][bin] = 1;
      }
      mCalib.drs_offset_range0[ch] = 0.45f;
      mCalib.drs_offset_range1[ch] = 0;
      mCalib.drs_offset_range2[ch] = -0.45f;
      
      mCalib.adc_offset_range0[ch] = 0;
      mCalib.adc_offset_range1[ch] = 0;
      mCalib.adc_offset_range2[ch] = 0;
   }
}

void VCALIB::save(WDB *b, std::string filename)
{
   std::memcpy(mCalib.version_id, "CAL2", 4);
   mCalib.sampling_frequency = b->GetDrsSampleFreq();
   mCalib.temperature = b->GetTemperature();
   
   int fh = open(filename.c_str(), O_WRONLY | O_CREAT, 0644);
   assert(fh > 0);
   assert(write(fh, &mCalib, sizeof(VCALIB_DATA)) == sizeof(VCALIB_DATA));
   close(fh);
}

void VCALIB::load(WDB *b, std::string filename)
{
   bValid = false;
   int fh = open(filename.c_str(), O_RDONLY, 0644);
   if (fh > 0) {
      int size = read(fh, &mCalib, sizeof(VCALIB_DATA));
      close(fh);

      if (size != sizeof(VCALIB_DATA)) {
         std::cerr << "Invalid voltage calibration file size in " << filename << ". Aborting." << std::endl;
         return;
      }
      
      if (memcmp(mCalib.version_id, "CAL2", 4) != 0) {
         std::cerr << "Invalid voltage calibration file format in " << filename << ". Aborting." << std::endl;
         return;
      }
      
      if (fabs((float)mCalib.sampling_frequency - b->GetDrsSampleFreq()) > 1) {
         std::cerr << "Warning: Voltage calibration data in " << filename << " is for "
         << mCalib.sampling_frequency/1000.0
         << " GSPS, running now at "
         << b->GetDrsSampleFreq()/1000.0 << " GSPS"  << std::endl;
      }

      if (fabs(mCalib.temperature - b->GetTemperature()) > 5) {
         std::cerr << "Warning: Voltage calibration data in " << filename << " is for "
         << mCalib.temperature
         << " deg. C, running now at "
         << b->GetTemperature() << " deg. C" << std::endl;
      }
      bValid = true;
   }
}

//--------------------------------------------------------------------

TCALIB::TCALIB()
{
   bValid = false; // not yet loaded
   memset(&mCalib, 0, sizeof(mCalib));
}

void TCALIB::save(WDB *b, std::string filename)
{
   std::memcpy(mCalib.version_id, "CAL2", 4);
   mCalib.sampling_frequency = b->GetDrsSampleFreq();
   mCalib.temperature = b->GetTemperature();
   
   int fh = open(filename.c_str(), O_WRONLY | O_CREAT, 0644);
   assert(fh > 0);
   assert(write(fh, &mCalib, sizeof(TCALIB_DATA)) == sizeof(TCALIB_DATA));
   close(fh);
}

void TCALIB::load(WDB *b, std::string filename)
{
   bValid = false;
   int fh = open(filename.c_str(), O_RDONLY, 0644);
   if (fh > 0) {
      int size = read(fh, &mCalib, sizeof(TCALIB_DATA));
      close(fh);
      
      if (size != sizeof(TCALIB_DATA)) {
         std::cerr << "Invalid time calibration file size in " << filename << ". Aborting." << std::endl;
         return;
      }
      
      if (memcmp(mCalib.version_id, "CAL2", 4) != 0) {
         std::cerr << "Invalid time calibration file format in " << filename << ". Aborting." << std::endl;
         return;
      }
      
      if (fabs((float)mCalib.sampling_frequency - b->GetDrsSampleFreq()) > 1) {
         std::cerr << "Error: Time calibration data in " << filename << " is for "
         << mCalib.sampling_frequency/1000.0
         << " GSPS, running now at "
         << b->GetDrsSampleFreq()/1000.0 << " GSPS"  << std::endl;
         return;
      }
      
      if (fabs(mCalib.temperature - b->GetTemperature()) > 5) {
         std::cerr << "Warning: Time calibration data in " << filename << " is for "
         << mCalib.temperature
         << " deg. C, running now at "
         << b->GetTemperature() << " deg. C" << std::endl;
      }
      bValid = true;
   }
}

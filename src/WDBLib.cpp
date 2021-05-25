//
//  WDBLib.cpp
//
//  WaveDAQ Interface Library
//
//  Created by Stefan Ritt on 13/8/15.
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
#include <netdb.h>
#include <assert.h>
#include <stdio.h>
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
#endif

#include "git-revision.h"
#include "WDBLib.h"
#include "WDBReg.h"

#define WD2_USE_UDP_BIN

#define WD2_CMD_PORT_BIN          4000
#define WD2_CMD_PORT_ASCII        3000

#define WD2_UDP_PROTOCOL_VERSION  8

int WP::gDataSocket = 0;
int WDB::gASCIISocket = 0;
int WDB::gBinSocket = 0;

unsigned short WDB::udpSequenceNumber = 0; // sequence number to identify related send/acknowledge packets

#define CALIB_TIMEOUT 1000

//--------------------------------------------------------------------

// convert one data type into other, replaces *((float *)(&int))

template<typename T, typename U>
T access_as(U *p) {
   T d;
   memcpy(&d, p, sizeof(d));
   return d;
}


//--------------------------------------------------------------------

std::string getWdbLibRevision()
{
   std::string r(GIT_REVISION);
   return r;
}

//--------------------------------------------------------------------

WDB::WDB(std::string name, bool verbose) : WDBREG() {
   for (auto &c: name) c = toupper(c);
   mWDBName = name;
   mWDBAddr = name;
   mDCB = nullptr;
   mSlot = 0;
   mPrompt = "";
   mVerbose = verbose;
   mLogfile = "";
   mDemoMode = (name == "demo");
   mSendBlocked = false;
   mReceiveTimeoutMs = cDefaultReceiveTimeoutMs;
   mTimingReferenceSignal = cTimingReferenceOff;
}

//--------------------------------------------------------------------

WDB::WDB(DCB *dcb, int slot, bool verbose) : WDBREG() {
   mWDBName = "WDxxx";
   mWDBAddr = dcb->GetName() + ":" + std::to_string(slot);
   mDCB = dcb;
   mSlot = slot;
   mPrompt = "";
   mVerbose = verbose;
   mLogfile = "";
   mSendBlocked = false;
   mReceiveTimeoutMs = cDefaultReceiveTimeoutMs;
   mTimingReferenceSignal = cTimingReferenceOff;
}

//--------------------------------------------------------------------

void WDB::SetDcbInterface(DCB *dcb, int slot) {
   mWDBAddr = dcb->GetName() + ":" + std::to_string(slot);
   mDCB = dcb;
   mSlot = slot;
}

//--------------------------------------------------------------------

void WDB::SendUDP(std::string str, unsigned char *ethAddr) {
   std::string result;
   result = SendReceiveUDP(str, ethAddr);
}

//--------------------------------------------------------------------

std::string WDB::SendReceiveUDP(std::string str, unsigned char *ethAddr) {
   size_t i;
   fd_set readfds;
   struct timeval timeout;
   int status, ms;
   struct sockaddr_in client_addr;
   char rx_buffer[1600];
   std::string result;

   if (ethAddr)
      std::memcpy(&client_addr, ethAddr, sizeof(client_addr));
   else if (mDCB) {
      return mDCB->SendReceiveUDP(std::string("slot ") + std::to_string(mSlot) + " " + str);
   } else
      std::memcpy(&client_addr, mEthAddrAscii, sizeof(client_addr));

   if (str.empty())
      str = "\n";

   if (str.back() != '\n')
      str += '\n';

   result.clear();

   // retry max ten times
   ms = mReceiveTimeoutMs;
   for (int retry = 0; retry < 10; retry++) {

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

         recv(gASCIISocket, rx_buffer, sizeof(rx_buffer), 0);
      } while (true);

      // send request
      i = sendto(gASCIISocket,
                 str.c_str(),
                 str.size(),
                 0,
                 (struct sockaddr *) &client_addr,
                 sizeof(client_addr));

      if (i != str.size()) {
         if (this->mVerbose)
            std::cout << mWDBName << " send retry " << retry + 1 << std::endl;
         continue;
      }

      // retrieve reply until prompt is found
      do {
         std::memset(rx_buffer, 0, sizeof(rx_buffer));

         FD_ZERO(&readfds);
         FD_SET(gASCIISocket, &readfds);

         if (retry > 0)
            ms *= 1.3;   // increase timeout after each retry

         timeout.tv_sec = ms / 1000;
         timeout.tv_usec = (ms % 1000) * 1000;

         do {
            status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
         } while (status == -1 && errno == EINTR);        /* dont return if an alarm signal was cought */

         if (!FD_ISSET(gASCIISocket, &readfds))
            break;

         i = recv(gASCIISocket, rx_buffer, sizeof(rx_buffer), 0);
         assert(i > 0);

         result += rx_buffer;

         // on th first contact, read back prompt
         if (mPrompt == "")
            mPrompt = result;

         // check for prompt
         if (result.substr(result.size() - mPrompt.size()) == mPrompt)
            break;

      } while (1);

      // check for prompt
      if (mPrompt.size() > 0 && result.size() >= mPrompt.size() &&
          result.substr(result.size() - mPrompt.size()) == mPrompt)
         break;

      if (this->mVerbose)
         std::cout << mWDBName << " retry " << retry + 1 << " with " << ms << " ms" << std::endl;

      result.clear();
   }

   if (result.size() == 0) {
      if (str.back() == '\n')
         str = str.substr(0, str.size() - 1);
      throw std::runtime_error(std::string("Error sending \"") + str + "\" to " + mWDBName);
   }

   // chop off prompt
   if (result.size() >= mPrompt.size())
      result = result.substr(0, result.size() - mPrompt.size());

   return result;
}

//--------------------------------------------------------------------

void WDB::WriteUDP(unsigned int ofs, std::vector<unsigned int> data) {
   size_t i;
   fd_set readfds;
   struct timeval timeout;
   int status, ms, retry;
   struct sockaddr_in client_addr;
   bool bSuccess;

   if (mDemoMode)
      return;

   if (mDCB)
      return mDCB->WriteUDP(mSlot, ofs, data);

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
   writeBuf[6] = (ofs >> 8) & 0xFF;
   writeBuf[7] = (ofs >> 0) & 0xFF;

   for (auto &d: data) {
      writeBuf.push_back((d >> 24) & 0xFF);
      writeBuf.push_back((d >> 16) & 0xFF);
      writeBuf.push_back((d >> 8) & 0xFF);
      writeBuf.push_back((d >> 0) & 0xFF);
   }

   auto startTime = WP::usStart();

   // retry max ten times
   ms = mReceiveTimeoutMs;
   for (retry = 0; retry < 10; retry++) {

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

         recv(gBinSocket, &readBuf[0], readBuf.size(), 0);
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
            std::cout << mWDBName << " send retry " << retry + 1 << std::endl;
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

         if (retry > 0)
            ms *= 1.3;   // increase timeout after each retry

         timeout.tv_sec = ms / 1000;
         timeout.tv_usec = (ms % 1000) * 1000;

         do {
            status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
         } while (status == -1);        /* dont return if an alarm signal was caught */

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
         std::cout << mWDBName << " retry " << retry + 1 << " with " << ms << " ms" << std::endl;
   }

   if (this->mVerbose && retry > 0) {
      std::cout << "Communication to " << mWDBName << " took " <<
                WP::usSince(startTime)/1000.0 <<
                " ms" << std::endl;

   }

   throw std::runtime_error(std::string("Error writing binary UDP data to " + mWDBName));
}

//--------------------------------------------------------------------

std::vector<unsigned int> WDB::ReadUDP(unsigned int ofs, unsigned int nReg) {
   size_t i;
   fd_set readfds;
   struct timeval timeout;
   int status, ms;
   struct sockaddr_in client_addr;
   bool bSuccess;
   std::vector<unsigned int> result;

   if (mDCB) {
      return mDCB->ReadUDP(mSlot, ofs, nReg);
   }

   udpSequenceNumber++;
   auto len = nReg * sizeof(unsigned int);
   std::memcpy(&client_addr, mEthAddrBin, sizeof(client_addr));

   std::vector<unsigned char> writeBuf(12);
   std::vector<unsigned char> readBuf(1600);

   writeBuf[0] = 0x24; // Read32 command
   writeBuf[1] = 0;
   writeBuf[2] = udpSequenceNumber >> 8;
   writeBuf[3] = udpSequenceNumber & 0xFF;

   writeBuf[4] = (ofs >> 24) & 0xFF;
   writeBuf[5] = (ofs >> 16) & 0xFF;
   writeBuf[6] = (ofs >> 8) & 0xFF;
   writeBuf[7] = (ofs >> 0) & 0xFF;

   writeBuf[8] = (len >> 24) & 0xFF;
   writeBuf[9] = (len >> 16) & 0xFF;
   writeBuf[10] = (len >> 8) & 0xFF;
   writeBuf[11] = (len >> 0) & 0xFF;

   // retry max ten times
   ms = mReceiveTimeoutMs;

   for (int retry = 0; retry < 10; retry++) {

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

         recv(gBinSocket, &readBuf[0], readBuf.size(), 0);
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
            std::cout << mWDBName << " send retry " << retry + 1 << std::endl;
         continue;
      }

      // retrieve reply until acknowledge is found
      do {
         std::fill(readBuf.begin(), readBuf.end(), 0);

         FD_ZERO(&readfds);
         FD_SET(gBinSocket, &readfds);

         if (retry > 0)
            ms *= 1.3;   // increase timeout after each retry

         timeout.tv_sec = ms / 1000;
         timeout.tv_usec = (ms % 1000) * 1000;

         do {
            status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
         } while (status == -1 && errno == EINTR);        /* dont return if an alarm signal was cought */

         if (status == -1) {
            perror("ReadUDP");
            break;
         }

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
            for (unsigned int ii = 0; ii < len / 4; ii++)
               result.push_back(readBuf[ii * 4 + 4] << 24 |
                                readBuf[ii * 4 + 5] << 16 |
                                readBuf[ii * 4 + 6] << 8 |
                                readBuf[ii * 4 + 7]);
            return result;
         }

      } while (1);

      if (this->mVerbose)
         std::cout << mWDBName << " retry " << retry + 1 << " with " << ms << " ms" << std::endl;
   }

   throw std::runtime_error(std::string("Error reading binary UDP data from " + mWDBName));
}

//--------------------------------------------------------------------

void WDB::Connect() {
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

   if (mDemoMode) {
      SetVersion(8);
      this->sreg.resize(GetNrOfStatRegs());
      this->creg.resize(GetNrOfCtrlRegs());

      for (auto i = 0; i < GetNrOfCtrlRegs(); i++)
         this->creg[i] = 0;
      for (auto i = 0; i < GetNrOfStatRegs(); i++)
         this->sreg[i] = 0;
      // set some meaningful values in demo mode to make wds happy
      this->sreg[(GetDrsSampleFreqLoc() & 0x0FFF) / 4] = 5120;
      this->sreg[(GetAdcSampleFreqLoc() & 0x0FFF) / 4] = 80;
      return;
   }

   if (!mDCB ) {
      // create UDP socket for ASCII command interpreter
      if (gASCIISocket == 0)
         gASCIISocket = socket(AF_INET, SOCK_DGRAM, 0);
      assert(gASCIISocket);

      // create UDP socket for binary commands
      if (gBinSocket == 0)
         gBinSocket = socket(AF_INET, SOCK_DGRAM, 0);
      assert(gBinSocket);

      // retrieve Ethernet address of board
      phe = gethostbyname(mWDBAddr.c_str());
      if (phe == NULL)
         throw std::runtime_error(std::string("Cannot resolve host name ") + mWDBAddr);

      std::memset((char *) &client_addr, 0, sizeof(client_addr));
      std::memcpy((char *) &client_addr.sin_addr, phe->h_addr, phe->h_length);
      client_addr.sin_family = AF_INET;
      client_addr.sin_port = htons(WD2_CMD_PORT_ASCII);
      std::memcpy(mEthAddrAscii, &client_addr, sizeof(client_addr));

      client_addr.sin_port = htons(WD2_CMD_PORT_BIN);
      std::memcpy(mEthAddrBin, &client_addr, sizeof(client_addr));

      inet_ntop(AF_INET, &client_addr.sin_addr, mEthAddrStr, sizeof(mEthAddrStr));

      // check if board is alive
      try {
         WDB::SendUDP("\n");
      } catch (...) {
         throw std::runtime_error(std::string("Cannot connect to board ") + mWDBAddr);
      }

      // set dbglevel none
      SendUDP("dbglvl none");
   } else {
      // check if board is alive
      try {
         auto result = ReadUDP(0x0000, 1);
         auto magic  = (result[0] & 0xFF000000) >> 24;
         if (magic != 0xAC)
            throw std::runtime_error(std::string("Cannot connect to board ") + mWDBAddr);
      } catch (...) {
         throw std::runtime_error(std::string("Cannot connect to board ") + mWDBAddr);
      }
   }

   // check register layout
   auto result = ReadUDP(0x0004, 1);
   unsigned int version = (result[0] & 0xFFFF);
   SetVersion(version);
   this->sreg.resize(GetNrOfStatRegs());
   this->creg.resize(GetNrOfCtrlRegs());

   // check firmware compatibility level
   ReceiveStatusRegisters(0x0000, 10);

   if (GetBoardRevision() + 'A' == 'E' || GetBoardRevision() + 'A' == 'F') {
      if (GetFwCompatLevel() < cRequiredFwCompatLevel2F) {
         std::string str("Board ");
         str += mWDBAddr + " has incompatible firmware, please upgrade (Board compatibility level: " +
                std::to_string(GetFwCompatLevel()) + ", Software compatibility level: " +
                std::to_string(cRequiredFwCompatLevel2F) + ")";
         throw std::runtime_error(str);
      }
      if (cRequiredFwCompatLevel2F < GetFwCompatLevel()) {
         std::string str("Board ");
         str += mWDBAddr +
                " has newer incompatible firmware, please update WD library (Firmware compatibility level: " +
                std::to_string(GetFwCompatLevel()) + ", Software compatibility level: " +
                std::to_string(cRequiredFwCompatLevel2F) + ")";
         throw std::runtime_error(str);
      }
      // check register layout compatibility level
      if (GetRegLayoutCompLevel() < cRequiredRegLayoutCompatLevel2F) {
         std::string str("Board ");
         str += mWDBAddr + " has incompatible register layout, please upgrade (Board compatibility level: " +
                std::to_string(GetRegLayoutCompLevel()) + ", Software compatibility level: " +
                std::to_string(cRequiredRegLayoutCompatLevel2F) + ")";
         throw std::runtime_error(str);
      }
      if (cRequiredRegLayoutCompatLevel2F < GetRegLayoutCompLevel()) {
         std::string str("Board ");
         str += mWDBAddr + " has newer register layout, please update WD library (Board compatibility level: " +
                std::to_string(GetRegLayoutCompLevel()) + ", Software compatibility level: " +
                std::to_string(cRequiredRegLayoutCompatLevel2F) + ")";
         throw std::runtime_error(str);
      }
   }

   if (GetBoardRevision() + 'A' == 'G') {
      if (GetFwCompatLevel() < cRequiredFwCompatLevel2G) {
         std::string str("Board ");
         str += mWDBAddr + " has incompatible firmware, please upgrade (Board compatibility level: " +
                std::to_string(GetFwCompatLevel()) + ", Software compatibility level: " +
                std::to_string(cRequiredFwCompatLevel2G) + ")";
         throw std::runtime_error(str);
      }
      if (cRequiredFwCompatLevel2G < GetFwCompatLevel()) {
         std::string str("Board ");
         str += mWDBAddr +
                " has newer incompatible firmware, please update WD library (Firmware compatibility level: " +
                std::to_string(GetFwCompatLevel()) + ", Software compatibility level: " +
                std::to_string(cRequiredFwCompatLevel2G) + ")";
         throw std::runtime_error(str);
      }
      // check register layout compatibility level
      if (GetRegLayoutCompLevel() < cRequiredRegLayoutCompatLevel2G) {
         std::string str("Board ");
         str += mWDBAddr + " has incompatible register layout, please upgrade (Board compatibility level: " +
                std::to_string(GetRegLayoutCompLevel()) + ", Software compatibility level: " +
                std::to_string(cRequiredRegLayoutCompatLevel2G) + ")";
         throw std::runtime_error(str);
      }
      if (cRequiredRegLayoutCompatLevel2G < GetRegLayoutCompLevel()) {
         std::string str("Board ");
         str += mWDBAddr + " has newer register layout, please update WD library (Board compatibility level: " +
                std::to_string(GetRegLayoutCompLevel()) + ", Software compatibility level: " +
                std::to_string(cRequiredRegLayoutCompatLevel2G) + ")";
         throw std::runtime_error(str);
      }
   }

   if (GetProtocolVersion() > WD2_UDP_PROTOCOL_VERSION) {
      std::string str("Board ");
      str += mWDBAddr + " has protocol version " + std::to_string(GetProtocolVersion()) +
             ", WDBLib library has version " + std::to_string(WD2_UDP_PROTOCOL_VERSION) +
             ". Please update WDBLib library.";
      throw std::runtime_error(str);
   }
   if (GetProtocolVersion() < WD2_UDP_PROTOCOL_VERSION) {
      std::string str("Board ");
      str += mWDBAddr + " has protocol version " + std::to_string(GetProtocolVersion()) +
             ", WDBLib library has version " + std::to_string(WD2_UDP_PROTOCOL_VERSION) +
             ". Please upgrade WDB firmware.";
      throw std::runtime_error(str);
   }

   // retrieve name from serial number
   char str[32];
   sprintf(str, "WD%03d", GetSerialNumber());
   mWDBName = std::string(str);

   // set internal slot register
   if (mDCB) {
      SetSlotId(mSlot);
      auto s = mDCB->GetName().substr(3);
      SetCrateId(std::stod(s));
   }
}

bool WDB::Ping() {
   try {
      // read magic number
      std::vector<unsigned int> result = ReadUDP(0, 1);
      if ((result[0] & 0xFF000000) == 0xAC000000)
         return true;
      return false;
   } catch (...) {
      return false;
   }
   return true;
}

//--------------------------------------------------------------------

void WDB::SetDestinationPort(int port) {
   if (mDemoMode)
      return;

   // set destination port in WD board, MAC and IP is used automatically form UDP packet
   SendUDP(std::string("cfgdst ") + std::to_string(port));
}

//--------------------------------------------------------------------

unsigned int WDB::BitExtractStatus(unsigned int rofs, unsigned int mask, unsigned int ofs) {
   return (sreg[(rofs & 0x0FFF) / 4] & mask) >> ofs;
}

unsigned int WDB::BitExtractControl(unsigned int rofs, unsigned int mask, unsigned int ofs) {
   return (creg[(rofs & 0x0FFF) / 4] & mask) >> ofs;
}

void WDB::bitReplace(unsigned int &reg, unsigned int mask, unsigned int ofs, unsigned int value) {
   reg = reg & (~mask); // clear bits from mask
   value <<= ofs;       // shift values
   value &= mask;
   reg |= value;        // set makes bits
}

//--------------------------------------------------------------------

void WDB::ReceiveControlRegisters(unsigned int index, unsigned int nReg) {
   if (nReg == 0)
      nReg = GetNrOfCtrlRegs();
   if (mDemoMode) {
      for (auto i = index; i < index + nReg; i++)
         this->creg[i] = 0;
      return;
   }

#ifdef WD2_USE_UDP_BIN
   std::vector<unsigned int> result = ReadUDP(GetSlotIdLoc() + index * 4, nReg);
   assert(result.size() == nReg);
   for (unsigned int i = 0; i < nReg; i++)
      this->creg[index + i] = result[i];
#else
   std::string result;
   std::ostringstream req;
   req << "rr 0x" << std::hex << WD2_REG_WDB_LOC+index*4 << " " << std::dec << nReg;

   result = SendReceiveUDP(req.str());
   std::stringstream ss(result);
   std::string line;

   for (auto i=index ; i<index+nReg ; i++) {
      std::getline(ss, line, '\n');
      auto adr = (unsigned int)std::stoul(line.substr(3), nullptr, 16);
      auto idx = (adr - WD2_REG_WDB_LOC) / 4;
      if (idx < REG_NR_OF_CTRL_REGS)
         this->creg[idx] = (unsigned int)std::stoul(line.substr(12), nullptr, 16);
   }
#endif
}

void WDB::ReceiveStatusRegisters(unsigned int index, unsigned int nReg) {
   if (nReg == 0)
      nReg = GetNrOfStatRegs();
   if (mDemoMode) {
      for (auto i = index; i < index + nReg; i++)
         this->sreg[i] = 0;
      return;
   }

#ifdef WD2_USE_UDP_BIN
   std::vector<unsigned int> result = ReadUDP(GetBoardMagicLoc() + index * 4, nReg);
   assert(result.size() == nReg);
   for (unsigned int i = 0; i < nReg; i++)
      this->sreg[index + i] = result[i];
#else
   std::string result;
   std::ostringstream req;
   req << "rr 0x" << std::hex << WD2_STAT_REG_BASE_OFS+index*4 << " " << std::dec << nReg;

   result = SendReceiveUDP(req.str());
   std::stringstream ss(result);
   std::string line;

   for (unsigned int i=index ; i<index+nReg ; i++) {
      std::getline(ss, line, '\n');
      auto adr = (unsigned int)std::stoul(line.substr(3), nullptr, 16);
      auto idx = (adr - WD2_STAT_REG_BASE_OFS) / 4;
      if (idx < REG_NR_OF_STAT_REGS) {
         this->sreg[idx] = (unsigned int)std::stoul(line.substr(12), nullptr, 16);
      }
   }
#endif

   // set calibration clock frequency
   mCalibClkFreq = 100; // 100 MHz
}

void WDB::ReceiveStatusRegister(int rofs) {
   int index = (rofs & 0x0FFF) / 4;

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
   this->sreg[index] = (unsigned int)std::stoul(result.substr(12), nullptr, 16);
#endif
}

void WDB::SetRegMask(unsigned int rofs, unsigned int mask, unsigned int ofs, unsigned int v) {
   int index = (rofs & 0x0FFF) / 4;

   unsigned int r = this->creg[index];

   bitReplace(r, mask, ofs, v);

   if (!mDemoMode && !mSendBlocked) {
#ifdef WD2_USE_UDP_BIN
      WriteUDP(rofs, std::vector<unsigned int>{r});
#else
      std::ostringstream req;
      req << "rw 0x" << std::hex << rofs << " 0x" << r;

      SendUDP(req.str());
#endif
   }

   this->creg[index] = r;
}

void WDB::SendControlRegisters(bool wait) {
   // first half until HV
   std::vector<unsigned int> v;
   for (int i = 0; i < (GetHvUTarget0Loc() - GetSlotIdLoc()) / 4; i++)
      v.push_back(this->creg[i]);
   WriteUDP(GetSlotIdLoc(), v);
   if (wait)
      sleep_ms(1000); // Reconfig of LMK takes some time...

   // second half after HV
   v.clear();
   for (int i = (GetLmk0ResetLoc() - GetSlotIdLoc()) / 4; i < GetNrOfCtrlRegs(); i++)
      v.push_back(this->creg[i]);
   WriteUDP(GetLmk0ResetLoc(), v);
}

//-- Status registers ------------------------------------------------

void WDB::PrintVersion() {
   std::cout << "Name:                " << GetName() << std::endl;
   std::cout << "Serial number:       " << GetSerialNumber() << std::endl;
   std::cout << "Protocol version:    " << GetProtocolVersion() << std::endl;
   std::cout << GetHwVersion() << std::endl;
   std::cout << GetFullBuild() << std::endl;
}

unsigned int WDB::bcd2dec(const unsigned int bcd) {
   return ((bcd & 0xF000) >> 12) * 1000 + ((bcd & 0x0F00) >> 8) * 100 + ((bcd & 0x00F0) >> 4) * 10 + (bcd & 0xF);
}

std::string WDB::GetFwBuild() {
   std::ostringstream s;
   std::vector<std::string> monthName = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov",
                                         "Dec"};

   s << std::dec << std::setw(2) << std::setfill('0');
   int m = bcd2dec(GetFwBuildMonth()) - 1;
   if (m >= 0 && m < 12)
      s << monthName[bcd2dec(GetFwBuildMonth()) - 1] << ' ';
   else
      s << "unknown ";
   s << bcd2dec(GetFwBuildDay()) << ' ';
   s << bcd2dec(GetFwBuildYear()) << "  ";
   s << std::setfill('0') << std::setw(2) << bcd2dec(GetFwBuildHour()) << ':';
   s << std::setfill('0') << std::setw(2) << bcd2dec(GetFwBuildMinute()) << ':';
   s << std::setfill('0') << std::setw(2) << bcd2dec(GetFwBuildSecond());

   return s.str();
}

std::string WDB::GetSwBuild() {
   std::ostringstream s;
   std::vector<std::string> monthName = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov",
                                         "Dec"};

   s << std::dec << std::setw(2) << std::setfill('0');
   if (GetSwBuildMonth() == 0)
      s << "Invalid Month ";
   else
     s << monthName[bcd2dec(GetSwBuildMonth()) - 1] << ' ';
   s << bcd2dec(GetSwBuildDay()) << ' ';
   s << bcd2dec(GetSwBuildYear()) << "  ";
   s << std::setfill('0') << std::setw(2) << bcd2dec(GetSwBuildHour()) << ':';
   s << std::setfill('0') << std::setw(2) << bcd2dec(GetSwBuildMinute()) << ':';
   s << std::setfill('0') << std::setw(2) << bcd2dec(GetSwBuildSecond());

   return s.str();
}

std::string WDB::GetFullBuild() {
   std::ostringstream s;
   std::vector<std::string> monthName = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov",
                                         "Dec"};

   s << "FW. Compat. Level:   ";
   s << GetFwCompatLevel() << std::endl;
   s << "Reg. Compat. Level:  ";
   s << GetRegLayoutCompLevel() << std::endl;
   s << "FW GIT Revision:     ";
   s << GetFwGitHashStr() << std::endl;
   s << "FW Build:            ";
   s << GetFwBuild() << std::endl;
   s << "SW GIT Revision:     ";
   s << GetSwGitHashStr() << std::endl;
   s << "SW Build:            ";
   s << GetSwBuild() << std::endl;

   return s.str();
}

std::string WDB::GetFwGitHashStr() {
   std::ostringstream s;
   s << "0x" << std::hex << std::setw(7) << std::setfill('0') << std::uppercase << GetFwGitHashTag();
   return s.str();
}

std::string WDB::GetSwGitHashStr() {
   std::ostringstream s;
   s << "0x" << std::hex << std::setw(7) << std::setfill('0') << std::uppercase << GetSwGitHashTag();
   return s.str();
}

std::string WDB::GetHwVersion() {
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
   s << (char) ('A' + GetBoardRevision()) << std::endl;
   s << "Board Variant:       ";
   s << std::showbase << std::internal << std::setfill('0') << std::hex << std::setw(4) << GetBoardVariant();
   s << std::endl;

   return s.str();
}

float WDB::GetTemperatureDegree(bool refresh)
// temperature in deg. C
{
   if (mDemoMode)
      return 37.5;

   if (refresh)
      ReceiveStatusRegister(GetTemperatureLoc());
   float temp = GetTemperature() * 0.0625;
   temp = std::roundf(temp * 10) / 10.0f;
   return temp;
}

float WDB::GetVCalibTemperature()
{
   return mVCalib.GetTemperature();
}

float WDB::GetTCalibTemperature()
{
   return mTCalib.GetTemperature();
}

unsigned int WDB::GetPllLock(bool refresh)
// all PLLs (DRS, LMK, FPGA DAQ, ISERDES, OSERDES)
{
   if (mDemoMode)
      return 0x1FF;

   if (refresh)
      ReceiveStatusRegister(GetSysDcmLockLoc());

   return this->sreg[GetSysDcmLockLoc() / 4];
}

unsigned int WDB::GetLEDState(bool refresh)
// all PLLs (DRS, LMK, FPGA DAQ, ISERDES, OSERDES)
{
   if (mDemoMode)
      return 0;

   if (refresh)
      ReceiveStatusRegister(GetLedStateLoc());

   return this->GetLedState();
}

bool WDB::WaitPllLock(int timeout)
// wait until all PLLs have locked with timeout
{
   for (int i=0 ; i<timeout ; i++) {
      auto l = GetPllLock(true);
      if (l == 0x1FF) {
         if (mVerbose && i > 0)
            std::cout << "PLL locked after " << i*10 << " ms" << std::endl;
         return true;
      }
      sleep_ms(10);
   }

   return false;
}

unsigned int WDB::GetExtClkActive(bool refresh)
{
   if (refresh)
      ReceiveStatusRegister(GetExtClkActiveLoc());

   return WDBREG::GetExtClkActive();
}

void WDB::SetDrsSampleFreq(unsigned int f, bool wait)
// sampling frequency in MHz
{
   if (mDemoMode) {
      unsigned int mask, ofs;
      int index = (GetDrsSampleFreqLoc(&mask, &ofs) & 0x0FFF) / 4;
      unsigned int r = this->creg[index];
      bitReplace(r, mask, ofs, f);
      this->sreg[index] = r;
      return;
   }

   auto divider = (int) (160.0 / f * 2048 + 0.5);
   divider /= 2; // LMK multiplies divider by 2

   //keep ADC Interface reset in the meanwhile (only if waiting)
   if (wait) SetAdcIfRst(1);

   SetLmk0ClkoutDiv(divider);

   // CH5: mirror output to FPGA
   SetLmk5ClkoutDiv(divider);
   SetLmk5ClkoutEn(true);
   SetLmk5ClkoutMux(1);
   SetLmk5ClkoutDly(0);

   if (wait) {
      // read back new sampling frquency in status register
      ReceiveStatusRegister(GetDrsSampleFreqLoc());

      LmkSyncLocal();
      SetAdcIfRst(0);

      ResetAdc();

      if (mVerbose && !WaitPllLock())
         std::cout << "PLLs on " << GetName() << " did not lock after 1s, mask=0x" <<
                   std::hex << GetPllLock(false) << std::dec << std::endl;
   }

}

void WDB::GetScalers(std::vector<uint64_t> &scaler, bool refresh) {
   if (refresh)
      ReceiveStatusRegisters(GetScaler0Loc() / 4, 19);

   // decode scalers according to their bit width
   uint64_t v;
   for (unsigned int i = 0; i < 19; i++) {
      v = this->sreg[GetScaler0Loc() / 4 + i];

      if (scaler.size() < i + 1)
         scaler.push_back(v);
      else
         scaler[i] = v;
   }
}

void WDB::GetHVCurrents(std::vector<float> &current, bool refresh) {
   if (refresh)
      ReceiveStatusRegisters((GetHvIMeas0Loc()) / 4, 21);

   for (unsigned int i = 0; i < 16; i++)
      current.push_back(access_as<float>(&this->sreg[GetHvIMeas0Loc() / 4 + i]));
}

void WDB::GetHVBaseVoltage(float &voltage, bool refresh) {
   if (refresh)
      ReceiveStatusRegisters(GetHvUBaseMeasLoc() / 4, 1);

   voltage = access_as<float>(&this->sreg[GetHvUBaseMeasLoc() / 4]);
}

void WDB::Get1wireTemperatures(std::vector<float> &temp, bool refresh) {
   if (refresh)
      ReceiveStatusRegisters(GetHvTemp0Loc() / 4, 4);

   for (unsigned int i = 0; i < 4; i++)
      temp.push_back(access_as<float>(&this->sreg[GetHvTemp0Loc() / 4 + i]));
}


//-- Control registers -----------------------------------------------

void WDB::SetLmkInputFreq(unsigned int f) {
   if (f == 100) {       // R = 20, N = 32, VCO DIV = 8
      SetLmk14PllR(20);
      SetLmk15PllN(32);
      SetLmk15VcoDiv(8);
      SetLmk13OscinFreq(100);
      SetExtClkFreq(100);
   } else if (f == 80) { // R = 20, N = 40, VCO DIV = 8
      SetLmk14PllR(20);
      SetLmk15PllN(40);
      SetLmk15VcoDiv(8);
      SetLmk13OscinFreq(80);
      SetExtClkFreq(80);
   } else {
      throw std::runtime_error(std::string("Unsupported LMK03000 input frequency"));
   }

   SetApplySettingsLmk(1);
}

unsigned int WDB::GetLmkInputFreq() {
   return GetExtClkFreq();
}

void WDB::SetSineWaveEnable(bool value) {
   // switch TCA_CTRL
   SetTimingCalibSignalEn(value);
}

int WDB::GetTimingReferenceSignal() {
   return mTimingReferenceSignal;
}

void WDB::SetTimingReferenceSignal(int value) {
   mTimingReferenceSignal = value;

   if (value == cTimingReferenceOff) { // turn reference signal off

      // turn off sine wave generator
      SetSineWaveEnable(false);

      // turn off calibration buffer
      SetCalibBufferEn(false);

      // select LMK outputs
      SetDrs0TimingRefSel(1);
      SetDrs1TimingRefSel(1);

      // disable LMK outputs #1 and #2
      SetLmk1ClkoutMux(0);
      SetLmk1ClkoutDiv(0);
      SetLmk1ClkoutEn(0);
      SetLmk2ClkoutMux(0);
      SetLmk2ClkoutDiv(0);
      SetLmk2ClkoutEn(0);

   } else if (value == cTimingReferenceSine) { // seclect sine wave generator

      // turn on sine wave generator
      SetSineWaveEnable(true);

      // turn on calibration buffer
      SetCalibBufferEn(true);

      // select sine wave
      SetDrs0TimingRefSel(0);
      SetDrs1TimingRefSel(0);

      // disable LMK outputs #1 and #2
      SetLmk1ClkoutMux(0);
      SetLmk1ClkoutDiv(0);
      SetLmk1ClkoutEn(0);
      SetLmk2ClkoutMux(0);
      SetLmk2ClkoutDiv(0);
      SetLmk2ClkoutEn(0);

   } else if (value == cTimingReferenceSquare) { // select square wave

      // turn off sine wave generator
      SetSineWaveEnable(false);

      // turn off calibration buffer
      SetCalibBufferEn(false);

      // select LMK outputs #1 and #2
      SetDrs0TimingRefSel(1);
      SetDrs1TimingRefSel(1);

      // turn on LMK outputs #1 and #2
      SetLmk1ClkoutMux(1);
      SetLmk1ClkoutDiv(1);
      SetLmk1ClkoutEn(1);
      SetLmk2ClkoutMux(1);
      SetLmk2ClkoutDiv(1);
      SetLmk2ClkoutEn(1);

      LmkSyncLocal();
   }
}

void WDB::ResetDaqPll() {
   SetDaqPllRst(1);
   SetDaqPllRst(0);
}

void WDB::ResetDcbOserdesPll() {
   SetDcbOserdesPllRst(1);
   SetDcbOserdesPllRst(0);
}

void WDB::ResetTcbOserdesPll() {
   SetTcbOserdesPllRst(1);
   SetTcbOserdesPllRst(0);
}

void WDB::ResetDcbOserdesIf() {
   SetDcbOserdesIfRst(1);
   SetDcbOserdesIfRst(0);
}

void WDB::ResetTcbOserdesIf() {
   SetTcbOserdesIfRst(1);
   SetTcbOserdesIfRst(0);
}

void WDB::ResetAllPll() {
   //   SetSendBlocked(true); // TBD: test this!
   ResetDaqPll();
   ResetDcbOserdesPll();
   ResetTcbOserdesPll();
   ResetDcbOserdesIf();
   //   SetSendBlocked(false);
   ResetTcbOserdesIf();
}

void WDB::ResetScaler() {
   SetScalerRst(1);
   SetScalerRst(0);
}

void WDB::ResetTriggerParityErrorCounter() {
   SetTrbParityErrorCountRst(1);
   SetTrbParityErrorCountRst(0);
}

void WDB::LmkSyncLocal() {
   SetLmkSyncLocal(1);
   SetLmkSyncLocal(0);
}

void WDB::ResetAdcIf() {
   SetAdcIfRst(1);
   SetAdcIfRst(0);
}

void WDB::ResetAdc() {
   SetAdcRst(1);
   SetAdcRst(0);
}

void WDB::ResetDataLinkIf() {
   SetDataLinkIfRst(1);
   SetDataLinkIfRst(0);
}

void WDB::ResetPackager() {
   SetWdPkgrRst(1);
   SetWdPkgrRst(0);
}

void WDB::ResetEventCounter() {
   SetEventCounterRst(1);
   SetEventCounterRst(0);
}

void WDB::ResetDrsControlFsm() {
   SetDrsCtrlFsmRst(1);
   SetDrsCtrlFsmRst(0);
}

void WDB::ReconfigureFpga() {
   int to = mReceiveTimeoutMs;
   mReceiveTimeoutMs = -1;
   SetReconfigureFpga(1);
   mReceiveTimeoutMs = to;
}

float WDB::GetDacRofsV() {
   auto d = GetDac0ChA();
   return d / 65535.0 * 2.5;
}

void WDB::SetDacRofsV(float v) {
   auto d = (unsigned int) (v / 2.5 * 65535 + 0.5);
   SetDac0ChA(d);
}

float WDB::GetDacOfsV() {
   auto d = GetDac0ChB();
   return d / 65535.0 * 2.5;
}

void WDB::SetDacOfsV(float v) {
   auto d = (unsigned int) (v / 2.5 * 65535 + 0.5);
   SetDac0ChB(d);
}

float WDB::GetDacCalDcV() {
   if (mDemoMode)
      return 0;

   auto v = GetDacOfsV();
   v = v - 0.68;
   return v;
}

void WDB::SetDacCalDcV(float v, bool wait) {
   v = v + 0.68;
   if (v < 0)
      v = 0;
   if (v > 2.5)
      v = 2.5;

   // shift OFS voltage since CAL_DC is AC coupled
   SetDacOfsV(v);

   // we have to wait until the uBlaze picked up and programmed the new DAC value
   // otherwise we get problems in the calibration routine where we quickly switch ranges
   if(wait) sleep_ms(200);
}

float WDB::GetRange() {
   float r = -GetDacCalDcV();
   r = (int) (r * 100) / 100.0;
   return r;
}

void WDB::SetRange(float r, bool wait) {
   SetDacCalDcV(-r, wait);
}

float WDB::GetDacPulseAmpV() {
   auto d = GetDac0ChD();
   return d / 65535.0 * 2.5;
}

void WDB::SetDacPulseAmpV(float v) {
   auto d = (unsigned int) (v / 2.5 * 65535 + 0.5);
   SetDac0ChD(d);
}

std::vector<float> pzcLevel = {0, 0.5, 1, 1.5, 1.8, 2, 2.5};

float WDB::GetDacPzcLevelV() {
   auto d = GetDac0ChE();
   return d / 65535.0 * 2.5;
}

void WDB::SetDacPzcLevelV(float v) {
   auto d = (unsigned int) (v / 2.5 * 65535 + 0.5);
   SetDac0ChE(d);
}

int WDB::GetDacPzcLevelN() {
   unsigned int i;
   auto v = GetDacPzcLevelV();
   for (i = 0; i < pzcLevel.size(); i++)
      if (pzcLevel[i] == v)
         break;
   return (int) i + 1;
}

void WDB::SetDacPzcLevelN(int i) {
   assert(i >= 0 && i < (int) pzcLevel.size());
   SetDacPzcLevelV(pzcLevel[i]);
}

float WDB::GetDacBiasV() {
   auto d = GetDac0ChH();
   return d / 65535.0 * 2.5;
}

void WDB::SetDacBiasV(float v) {
   auto d = (unsigned int) (v / 2.5 * 65535 + 0.5);
   SetDac0ChH(d);
}

float WDB::GetDacTriggerLevelV(int chn) {
   unsigned int d;

   if (mDemoMode)
      return 0;

   assert(chn < 16);

   unsigned int reg, mask, ofs;
   if (chn % 2 == 0)
      reg = GetDac1ChALoc(&mask, &ofs);
   else
      reg = GetDac1ChBLoc(&mask, &ofs);
   d = BitExtractControl(reg + (chn / 2) * 4, mask, ofs);

   // convert to Volts taking WDB comparator offset into account
   float v=-1;
   switch(GetVersion())
   {
   case 8:
      v = ((d / 65535.0 * 2500) - 900) / 500.0;
      break;
   case 9:
      v = ((d / 65535.0 * 2500) - 900) / 1000.0;
      break;
   }
   return (int) (v * 1000 + 0.5) / 1000.0;
}

void WDB::SetDacTriggerLevelV(int chn, float v) {
   // convert to mV taking WDB comparator offset into account
  switch(GetVersion())
    {
    case 8:
      v = v * 500 + 900;
      break;
    case 9:
      v = v * 1000 + 900;
      break;
    }

   // convert from mV to DAC bits
   auto d = (unsigned int) (v / 2500.0 * 65535 + 0.5);

   assert(chn < 16);
   if (chn == -1) {
      unsigned int reg, mask, ofs;
      bool blocked = GetSendBlock();
      if (!blocked)
         SetSendBlock(true);
      for (chn = 0; chn < 16; chn++) {
         if (chn % 2 == 0)
            reg = GetDac1ChALoc(&mask, &ofs);
         else
            reg = GetDac1ChBLoc(&mask, &ofs);
         SetRegMask(reg + (chn / 2) * 4, mask, ofs, d);
      }
      if (!blocked)
         SetSendBlock(false);
      std::vector<unsigned int> regs;
      for (chn = 0; chn < 8; chn++)
         regs.push_back(creg[(GetDac1ChALoc() & 0xFFF) / 4 + chn]);
#ifdef WD2_USE_UDP_BIN
      if (!mDemoMode && !mSendBlocked)
         WriteUDP(GetDac1ChALoc(), regs);
#else
      for (chn=0 ; chn<8 ; chn++) {
         std::ostringstream req;
         req << "rw 0x" << std::hex << WD2_DAC1_CH_A_REG+(chn/2)*4 << " 0x" << creg[(WD2_DAC1_CH_A_REG & 0x0FFF)/4+chn];

         SendUDP(req.str());
      }
#endif

   } else {
      unsigned int reg, mask, ofs;
      if (chn % 2 == 0)
         reg = GetDac1ChALoc(&mask, &ofs);
      else
         reg = GetDac1ChBLoc(&mask, &ofs);
      SetRegMask(reg + chn / 2 * 4, mask, ofs, d);
   }
}

bool WDB::GetFePzc(int chn)
// pole-zero canellation
{
   assert(chn < 16);
   unsigned int mask, ofs;
   auto rofs = GetFe0PzcEnLoc() + (chn / 2) * 4;
   if (chn % 2 == 0) GetFe0PzcEnLoc(&mask, &ofs); else GetFe1PzcEnLoc(&mask, &ofs);
   return BitExtractControl(rofs, mask, ofs) > 0;
}

void WDB::SetFePzc(int chn, bool v) {
   if (chn == -1) {
      for (int i = 0; i < 16; i++)
         SetFePzc(i, v);
      return;
   }
   assert(chn < 16);
   unsigned int mask, ofs;
   auto rofs = GetFe0PzcEnLoc() + (chn / 2) * 4;
   if (chn % 2 == 0) GetFe0PzcEnLoc(&mask, &ofs); else GetFe1PzcEnLoc(&mask, &ofs);
   SetRegMask(rofs, mask, ofs, v ? 1 : 0);
}

unsigned int WDB::GetFeAmp2Comp(int chn)
// amplifier 2 compensation enable
{
   assert(chn < 16);
   unsigned int mask, ofs;
   auto rofs = GetFe0Amplifier2CompEnLoc() + (chn / 2) * 4;
   if (chn % 2 == 0) GetFe0Amplifier2CompEnLoc(&mask, &ofs); else GetFe1Amplifier2CompEnLoc(&mask, &ofs);
   return BitExtractControl(rofs, mask, ofs);
}

void WDB::SetFeAmp2Comp(int chn, unsigned int v) {
   assert(chn < 16);
   unsigned int mask, ofs;
   auto rofs = GetFe0Amplifier2CompEnLoc() + (chn / 2) * 4;
   if (chn % 2 == 0) GetFe0Amplifier2CompEnLoc(&mask, &ofs); else GetFe1Amplifier2CompEnLoc(&mask, &ofs);
   SetRegMask(rofs, mask, ofs, v);
}

unsigned int WDB::GetFeAmp2Enable(int chn)
// amplifier 2 enable (gain 10)
{
   assert(chn < 16);
   unsigned int mask, ofs;
   auto rofs = GetFe0Amplifier2EnLoc() + (chn / 2) * 4;
   if (chn % 2 == 0) GetFe0Amplifier2EnLoc(&mask, &ofs); else GetFe1Amplifier2EnLoc(&mask, &ofs);
   return BitExtractControl(rofs, mask, ofs);
}

void WDB::SetFeAmp2Enable(int chn, unsigned int v) {
   assert(chn < 16);
   unsigned int mask, ofs;
   auto rofs = GetFe0Amplifier2EnLoc() + (chn / 2) * 4;
   if (chn % 2 == 0) GetFe0Amplifier2EnLoc(&mask, &ofs); else GetFe1Amplifier2EnLoc(&mask, &ofs);
   SetRegMask(rofs, mask, ofs, v);
}

unsigned int WDB::GetFeAmp1Comp(int chn)
// amplifier 1 compensation enable
{
   assert(chn < 16);
   unsigned int mask, ofs;
   auto rofs = GetFe0Amplifier1CompEnLoc() + (chn / 2) * 4;
   if (chn % 2 == 0) GetFe0Amplifier1CompEnLoc(&mask, &ofs); else GetFe1Amplifier1CompEnLoc(&mask, &ofs);
   return BitExtractControl(rofs, mask, ofs);
}

void WDB::SetFeAmp1Comp(int chn, unsigned int v) {
   assert(chn < 16);
   unsigned int mask, ofs;
   auto rofs = GetFe0Amplifier1CompEnLoc() + (chn / 2) * 4;
   if (chn % 2 == 0) GetFe0Amplifier1CompEnLoc(&mask, &ofs); else GetFe1Amplifier1CompEnLoc(&mask, &ofs);
   SetRegMask(rofs, mask, ofs, v);
}

unsigned int WDB::GetFeAmp1Enable(int chn)
// amplifier 1 enable (gain 10)
{
   assert(chn < 16);
   unsigned int mask, ofs;
   auto rofs = GetFe0Amplifier1EnLoc() + (chn / 2) * 4;
   if (chn % 2 == 0) GetFe0Amplifier1EnLoc(&mask, &ofs); else GetFe1Amplifier1EnLoc(&mask, &ofs);
   return BitExtractControl(rofs, mask, ofs);
}

void WDB::SetFeAmp1Enable(int chn, unsigned int v) {
   assert(chn < 16);
   unsigned int mask, ofs;
   auto rofs = GetFe0Amplifier1EnLoc() + (chn / 2) * 4;
   if (chn % 2 == 0) GetFe0Amplifier1EnLoc(&mask, &ofs); else GetFe1Amplifier1EnLoc(&mask, &ofs);
   SetRegMask(rofs, mask, ofs, v);
}

unsigned int WDB::GetFeAttenuation(int chn)
// attenuation: 0 = 0dB / 1 = 6dB / 2 = 12dB / 8 = 18dB
{
   assert(chn < 16);
   unsigned int mask, ofs;
   auto rofs = GetFe0AttenuationLoc() + (chn / 2) * 4;
   if (chn % 2 == 0) GetFe0AttenuationLoc(&mask, &ofs); else GetFe1AttenuationLoc(&mask, &ofs);
   return BitExtractControl(rofs, mask, ofs);
}

void WDB::SetFeAttenuation(int chn, unsigned int v) {
   assert(chn < 16);
   unsigned int mask, ofs;
   auto rofs = GetFe0AttenuationLoc() + (chn / 2) * 4;
   if (chn % 2 == 0) GetFe0AttenuationLoc(&mask, &ofs); else GetFe1AttenuationLoc(&mask, &ofs);
   SetRegMask(rofs, mask, ofs, v);
}

// input configuration according to FE_bits_2E.xlsx
struct {
   float gain;
   int att0;
   int att1;
   int en1;
   int comp1;
   int en2;
   int comp2;
} gain_table[] = {
        {0.5, 1, 0, 0, 0, 0, 0},
        {1,   0, 0, 0, 0, 0, 0},
        {2.5, 0, 1, 1, 0, 0, 0},
        {5,   1, 0, 1, 0, 0, 0},
        {10,  0, 0, 1, 0, 0, 0},
        {25,  0, 1, 1, 0, 1, 0},
        {50,  1, 0, 1, 0, 1, 0},
        {100, 0, 0, 1, 0, 1, 0},

};

float WDB::GetFeGain(int chn) {
   int att = GetFeAttenuation(chn);
   int en1 = GetFeAmp1Enable(chn);
   int en2 = GetFeAmp2Enable(chn);

   for (int i = 0; i < 8; i++)
      if (((gain_table[i].att0 | (gain_table[i].att1 << 1)) == att) &&
          gain_table[i].en1 == en1 &&
          gain_table[i].en2 == en2) {
         return gain_table[i].gain;
      }

   return 0;
}

void WDB::SetFeGain(int chn, float gain) {
   if (chn == -1) {
      for (int i = 0; i < 16; i++)
         SetFeGain(i, gain);
      return;
   }

   int i;
   for (i = 0; i < 8; i++)
      if (gain_table[i].gain == gain)
         break;

   if (i < 8) {
      auto blocked = GetSendBlock();
      if (!blocked)
         SetSendBlock(true);

      SetFeAttenuation(chn, gain_table[i].att0 | (gain_table[i].att1 << 1));
      SetFeAmp1Enable(chn, gain_table[i].en1);
      SetFeAmp1Comp(chn, gain_table[i].comp1);
      SetFeAmp2Enable(chn, gain_table[i].en2);

      if (!blocked)
         SetSendBlock(false); // now send register
      SetFeAmp1Comp(chn, gain_table[i].comp2);
   }
}

unsigned int WDB::GetFeMux(int chn)
// multiplexer: 0 = next channel / 1 = previous channel / 2 = input / 3 = cal source
{
   assert(chn < 16);
   unsigned int mask, ofs;
   auto rofs = GetFe0MuxLoc() + (chn / 2) * 4;
   if (chn % 2 == 0) GetFe0MuxLoc(&mask, &ofs); else GetFe1MuxLoc(&mask, &ofs);
   return BitExtractControl(rofs, mask, ofs);
}

void WDB::SetFeMux(int chn, unsigned int v) {
   assert(chn < 16);
   if (chn == -1) {
      std::vector<unsigned int> regs;
      for (chn = 0; chn < 16; chn++) {
         unsigned int mask, ofs;
         auto rofs = GetFe0MuxLoc() + (chn / 2) * 4;
         if (chn % 2 == 0) GetFe0MuxLoc(&mask, &ofs); else GetFe1MuxLoc(&mask, &ofs);
         SetRegMask(rofs, mask, ofs, v);
      }
      for (chn = 0; chn < 8; chn++)
         regs.push_back(creg[(GetFe0MuxLoc() & 0x0FFF) / 4 + chn]);
#ifdef WD2_USE_UDP_BIN
      if (!mDemoMode && !mSendBlocked)
         WriteUDP(GetFe0MuxLoc(), regs);
#else
      for (chn=0 ; chn<8 ; chn++) {
         std::ostringstream req;
         req << "rw 0x" << std::hex << WD2_FE0_MUX_REG+(chn/2)*4 << " 0x" << creg[(WD2_FE0_MUX_REG & 0x0FFF)/4+chn];

         SendUDP(req.str());
      }
#endif
   } else {
      unsigned int mask, ofs;
      auto rofs = GetFe0MuxLoc() + (chn / 2) * 4;
      if (chn % 2 == 0) GetFe0MuxLoc(&mask, &ofs); else GetFe1MuxLoc(&mask, &ofs);
      SetRegMask(rofs, mask, ofs, v);
   }
}

void WDB::SetHVTarget(int chn, float v) {
   assert(chn < 16);
   unsigned int reg, mask, ofs;
   reg = GetHvUTarget0Loc(&mask, &ofs);
   SetRegMask(reg + chn * 4, mask, ofs, access_as<unsigned int>(&v));
}

std::string WDB::GetHvVersion() {
   std::ostringstream s;
   s << (GetHvVer() >> 16) << " V / " << (GetHvVer() & 0xFFFF) << " mA";
   return s.str();
}

void WDB::GetHVTarget(std::vector<float> &hv) {
   ReceiveControlRegisters((GetHvUTarget0Loc() & 0x0FFF) / 4, 16);
   for (unsigned int i = 0; i < 16; i++) {
      float f;
      memcpy(&f, &this->creg[(GetHvUTarget0Loc() & 0x0FFF) / 4 + i], sizeof(float));
      hv.push_back(f);
   }
}

unsigned int WDB::GetLmk(int reg) {
   assert(reg < 16);
   return creg[(GetLmk0ResetLoc() & 0xFFF)/ 4 + reg];
}

void WDB::SetLmk(int reg, unsigned int v) {
   assert(reg < 16);
   SetRegMask(GetLmk0ResetLoc() + reg * 4, 0xFFFFFFFF, 0, v);
}

//--------------------------------------------------------------------

unsigned int WDB::GetTrgSrcEnPtrn(int i) {
   assert(i >= 0 && i < 18);
   unsigned int reg, mask, ofs;
   reg = GetTrgSrcEnPtrn0Loc(&mask, &ofs);
   return BitExtractControl(reg + i * 4 * 2, mask, ofs);
}

void WDB::SetTrgSrcEnPtrn(int i, unsigned int value) {
   unsigned int reg, mask, ofs;
   reg = GetTrgSrcEnPtrn0Loc(&mask, &ofs);
   SetRegMask(reg + i * 4 * 2, mask, ofs, value);
}

unsigned int WDB::GetTrgStatePtrn(int i) {
   assert(i >= 0 && i < 18);
   unsigned int reg, mask, ofs;
   reg = GetTrgStatePtrn0Loc(&mask, &ofs);
   return BitExtractControl(reg + i * 4 * 2, mask, ofs);
}

void WDB::SetTrgStatePtrn(int i, unsigned int value) {
   unsigned int reg, mask, ofs;
   reg = GetTrgStatePtrn0Loc(&mask, &ofs);
   SetRegMask(reg + i * 4 * 2, mask, ofs, value);
}

unsigned int WDB::GetTriggerDelayNs() {
   auto v = GetTriggerDelay();

   v = (unsigned int) (v * 6.25 + 0.5);
   return v;
}

void WDB::SetTriggerDelayNs(unsigned int ns) {
   unsigned int v = (unsigned int) (ns / 6.25 + 0.5);
   if (v > 255)
      v = 255;
   SetTriggerDelay(v);
}

//--------------------------------------------------------------------

void WDB::TriggerSoftEvent() {
   SetDaqSingle(true);  // start DRS domino wave

   sleep_ms(mTriggerHoldoff);

   SetDaqSoftTrigger(true);
}

void WDB::SetDaqSoftNormal(int value) {
   SetRegMask(0x1004, 0x00000008, 3, value);
}

int WDB::GetDaqSoftNormal() {
   return BitExtractControl(0x1004, 0x00000008, 3);
}

//--------------------------------------------------------------------

unsigned int WDB::GetDrsSampleFreqMhz() {
   return (unsigned int) (GetDrsSampleFreq() / 1000.0 + 0.5);
}

//--------------------------------------------------------------------

void WDB::SaveVoltageCalibration(int freq, std::string path) {
   auto p(path);
   if (p.length() > 0 && p.back() != '/')
      p += "/";
   p += "calib/";
   auto fn(p + mWDBName + "-" + std::to_string(freq) + ".vcal");
   if (mVerbose)
      std::cout << "Saving voltage calibration to " + fn + " for " << freq / 1000.0 << " GSPS" << std::endl;

   mkdir(p.c_str(), 0755);

   mVCalib.save(this, fn);
}

//--------------------------------------------------------------------

bool WDB::LoadVoltageCalibration(int freq, std::string path) {
   auto p(path);
   if (p.length() > 0 && p.back() != '/')
      p += "/";
   auto fn(p + "calib/" + mWDBName + "-" + std::to_string(freq) + ".vcal");
   if (mVerbose)
      std::cout << "Loading voltage calibration " + fn + " for " << freq / 1000.0 << " GSPS ... ";

   mVCalib.load(this, fn);
   if (mVerbose)
      std::cout << (mVCalib.IsValid() ? "ok" : "failure") << std::endl;
   return mVCalib.IsValid();
}

//--------------------------------------------------------------------

void WDB::SaveTimeCalibration(int freq, std::string path) {
   auto p(path);
   if (p.length() > 0 && p.back() != '/')
      p += "/";
   p += "calib/";
   auto fn(p + mWDBName + "-" + std::to_string(freq) + ".tcal");
   if (mVerbose)
      std::cout << "Saving time calibration to " + fn + " for " << freq / 1000.0 << " GSPS" << std::endl;

   mkdir(p.c_str(), 0755);

   mTCalib.save(this, fn);
}

//--------------------------------------------------------------------

bool WDB::LoadTimeCalibration(int freq, std::string path) {
   auto p(path);
   if (p.length() > 0 && p.back() != '/')
      p += "/";
   auto fn(p + "calib/" + mWDBName + "-" + std::to_string(freq) + ".tcal");
   if (mVerbose)
      std::cout << "Loading time calibration    " + fn + " for " << freq / 1000.0 << " GSPS ... ";

   mTCalib.load(this, fn);
   if (mVerbose)
      std::cout << (mTCalib.IsValid() ? "ok" : "failure") << std::endl;
   return mTCalib.IsValid();
}

//--------------------------------------------------------------------

void WDBS::Save(WDB *b) {
   mRange = b->GetRange();
   mFeGain = b->GetFeGain(-1);
   mDacCalDcV = b->GetDacCalDcV();
   mDrsChTxEn = b->GetDrsChTxEn();
   mAdcChTxEn = b->GetAdcChTxEn();
   mFeMux = b->GetFeMux(0);
   mInterPkgDelay = b->GetInterPkgDelay();
   mTriggerHoldoff = b->GetTriggerHoldoff();
   mTimingCalibSignalEn = b->GetTimingCalibSignalEn();
   mCalibBufferEn = b->GetCalibBufferEn();
   mTimingReferenceSignal = b->GetTimingReferenceSignal();
   mExtAsyncTriggerEn = b->GetExtAsyncTriggerEn();
   mPatternTriggerEn = b->GetPatternTriggerEn();
   mZeroSuprEn = b->GetZeroSuprEn();
}

void WDBS::Restore(WDB *b) {
   b->SetRange(mRange);
   b->SetFeGain(-1, mFeGain);
   b->SetDacCalDcV(mDacCalDcV);
   b->SetDrsChTxEn(mDrsChTxEn);
   b->SetAdcChTxEn(mAdcChTxEn);
   b->SetFeMux(-1, mFeMux);
   b->SetInterPkgDelay(mInterPkgDelay);
   b->SetTriggerHoldoff(mTriggerHoldoff);
   b->SetTimingCalibSignalEn(mTimingCalibSignalEn);
   b->SetCalibBufferEn(mCalibBufferEn);
   b->SetTimingReferenceSignal(mTimingReferenceSignal);
   b->SetExtAsyncTriggerEn(mExtAsyncTriggerEn);
   b->SetPatternTriggerEn(mPatternTriggerEn);
   b->SetZeroSuprEn(mZeroSuprEn);
}

//====================================================================

void WDEvent::ClearEvent() {
   mEventValid = false;

   mVCalibrated = false;
   mTCalibrated = false;

   mHasADCData = false;
   mHasDRSData = false;
   mHasTDCData = false;
   mHasTRGData = false;
   mHasScalerData = false;

   mSOEReceived = false;
   mEOEReceived = false;

   mFirstPacketNumber = 0;
   mLastPacketNumber = 0;
   mReceivedPackets = 0;

   for (int i = 0; i < WD_N_CHANNELS; i++) {
      mDRSChannelPresent[i] = false;
      mADCChannelPresent[i] = false;
      mTDCChannelPresent[i] = false;
   }
}

void WDEvent::SetEventHeaderInfo(FRAME_WDAQ_HEADER *pdaqh) {
   mBoardId = pdaqh->serial_number;
   mCrateId = pdaqh->crate_id;
   mSlotId = pdaqh->slot_id;
}

void WDEvent::SetWDEventHeaderInfo(FRAME_WDAQ_HEADER *pdaqh, FRAME_WDB_HEADER *ph) {
   int channel = ph->channel_info & 0x1F;
   if (pdaqh->data_type == cDataTypeDRS) {
      mDRSSamplingFrequency = (unsigned int) (ph->sampling_frequency / 1000.0 + 0.5);  // convert kHz to MHz
      mTriggerCell[channel] = ph->drs_trigger_cell;
   }
   if (pdaqh->data_type == cDataTypeADC) {
      mADCSamplingFrequency = (unsigned int) (ph->sampling_frequency / 1000.0 + 0.5);  // convert kHz to MHz
   } if (pdaqh->data_type == cDataTypeTDC)
      mTDCChannelPresent[channel] = true;

   mEventNumber = pdaqh->event_number;
   mTriggerNumber = pdaqh->trigger_information[5] | (pdaqh->trigger_information[4] << 8);
   mTriggerType = pdaqh->trigger_information[1] | (pdaqh->trigger_information[0] << 8);
   mTemperature = std::round(ph->temperature * 0.0625 * 10) / 10.0f;
}

bool WDEvent::IsEventValid() {
   return mEventValid;
}

void WDEvent::ProcessPacket(FRAME_WDAQ_HEADER *pdaqh) {
   mReceivedPackets++;

   if (pdaqh->wdaq_flags & (1 << cWDAQFlagStartOfEvent)) {
      mSOEReceived = true;
      mFirstPacketNumber = pdaqh->packet_number;
   } else {
      mLastPacketNumber = pdaqh->packet_number;
      if (mLastPacketNumber < mFirstPacketNumber)
         mLastPacketNumber += 65536; // fix 16-bit overflow
   }

   if (pdaqh->wdaq_flags & (1 << cWDAQFlagEndOfEvent)) {
      mEOEReceived = true;
      mEventValid = (mSOEReceived && mLastPacketNumber - mFirstPacketNumber + 1 == mReceivedPackets);
   }

   // set data type flags from packet
   if (pdaqh->data_type == cDataTypeDRS)
      this->mHasDRSData = true;
   else if (pdaqh->data_type == cDataTypeADC)
      this->mHasADCData = true;
   else if (pdaqh->data_type == cDataTypeTDC)
      this->mHasTDCData = true;
   else if (pdaqh->data_type == cDataTypeTrg)
      this->mHasTRGData = true;
   else if (pdaqh->data_type == cDataTypeScaler)
      this->mHasScalerData = true;
   else if (pdaqh->data_type != cDataTypeDummy &&
            pdaqh->data_type != cDataTypeTCB) {
      std::cerr << "Package with unknown data type " << pdaqh->data_type << " received" << std::endl;
   }
}

//--------------------------------------------------------------------

WP::WP(int verbose, std::string wdsDir, std::string logfile, bool demo) {
   struct sockaddr_in server_addr;

   mVerbose = verbose;
   mLogfile = logfile;
   mWdsDir = wdsDir;
   mDemoMode = demo;

   mRotateWaveform = true;
   mCalibrateWaveform = true;
   mOfsCalib1 = true;
   mOfsCalib2 = true;
   mGainCalib = true;
   mRangeCalib = true;
   mTimeCalib1 = true;
   mTimeCalib2 = true;
   mTimeCalib3 = true;

   mWDReceivedPackets = 0;
   mWDDroppedPackets = 0;
   mReceivedPacketsThisEvent = 0;
   mLastEventNumber = 0;
   mPacketEfficiency = -1;
   mStartStatistics = 0;

   li.fh = 0;
   li.xml = NULL;

   // create UDB socket to receive binary data from WDB
   if (!mDemoMode && WP::gDataSocket == 0) {
      WP::gDataSocket = socket(AF_INET, SOCK_DGRAM, 0);
      assert(WP::gDataSocket);

      // increase receive buffer size
#ifdef __linux__
      int rcvBufferSizeSet = 8 * 1024 * 1024; // 8 MB
#else
      int rcvBufferSizeSet = 4 * 1024 * 1024; // 4 MB
#endif
      int rcvBufferSizeGetOrig;
      int rcvBufferSizeGet;
      socklen_t sockOptSize = sizeof(rcvBufferSizeGetOrig);

      getsockopt(WP::gDataSocket, SOL_SOCKET, SO_RCVBUF, &rcvBufferSizeGetOrig, &sockOptSize);
      if (rcvBufferSizeGetOrig < rcvBufferSizeSet) {
         setsockopt(WP::gDataSocket, SOL_SOCKET, SO_RCVBUF, &rcvBufferSizeSet, sizeof(rcvBufferSizeSet));
         getsockopt(WP::gDataSocket, SOL_SOCKET, SO_RCVBUF, &rcvBufferSizeGet, &sockOptSize);

         if (rcvBufferSizeGet < rcvBufferSizeSet) {
            std::cout << "Initial rcvBufferSizeGet  : " << rcvBufferSizeGetOrig/1024 << " kB" << std::endl;
            std::cout << "Modified rcvBufferSizeGet : " << rcvBufferSizeGet/1024 << " kB" << std::endl;
            std::cout << "Warning: Receive Buffer Size quite small, consider:" << std::endl << std::endl
                      #ifdef __linux__
                      << "$ sudo sysctl -w net.core.rmem_max=" << rcvBufferSizeSet << std::endl << std::endl
            << "or insert to /etc/sysctl.d/99-sysctl.conf (/etc/sysctl.conf on legacy systems)"  << std::endl
            << "for permanent settings" << std::endl;
                      #endif
                      #ifdef __APPLE__
                      << "$ sudo sysctl net.inet.udp.recvspace=" << rcvBufferSizeSet << std::endl << std::endl
                      << "or insert this into /etc/sysctl.conf to make it permanent" << std::endl;
#endif
         }
      }

      // bind socket to port chosen by OS
      std::memset((char *) &server_addr, 0, sizeof(server_addr));
      server_addr.sin_family = AF_INET;
      server_addr.sin_port = htons(0); // let OS choose port
      server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
      if (::bind(gDataSocket, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
         perror("bind");
         throw std::runtime_error(std::string("Cannot bind socket"));
      }
      auto size = sizeof(server_addr);
      getsockname(WP::gDataSocket, (struct sockaddr *) &server_addr, (socklen_t *) &size);
      WP::mServerPort = ntohs(server_addr.sin_port);

      std::cout << "Listening on UDP port " << WP::mServerPort << std::endl;
   }

   // initialize event flags
   mEventEmpty = true;
   mEventNew = false;

   // start waveform collector thread
   mThreadCollector = this->SpawnCollectorThread();

   memset(&calibProg, 0, sizeof(calibProg));
}

//--------------------------------------------------------------------

void WP::SetWDBList(std::vector<WDB *> wdb) {
   mWdb.clear();
   mWdbMap.clear();

   for (auto &b: wdb) {
      mWdb.push_back(b);

      // build mapping WDB id -> wdb
      mWdbMap[b->GetSerialNumber()] = b;
   }
}

WDB *WP::GetBoard(int board_id) {
   return mWdbMap.at(board_id);
}

//--------------------------------------------------------------------

void WP::SetRequestedBoard(std::vector<WDB *>wdb) {
   mWdbRequested.clear();
   for (auto &b: wdb) {
      mWdbRequested.push_back(b);
   }
}

void WP::SetRequestedBoard(WDB *b) {
   mWdbRequested.clear();
   mWdbRequested.push_back(b);
}

//--------------------------------------------------------------------

bool WP::RequestEvent(WDB *b, int timeout, WDEvent &event) {
   WP::SetRequestedBoard(b);
   b->TriggerSoftEvent();
   return GetLastEvent(b, timeout, event);
}

//--------------------------------------------------------------------

bool WP::WaitNewEvent(int timeout) {
   // wait for new event with timeout
   {
      std::unique_lock<std::mutex> lock(mEventMutex);
      if (!(mEventCV.wait_for(lock, std::chrono::milliseconds(timeout), [this]() { return mEventNew; })))
         return false;
   }

   return true;
}

//--------------------------------------------------------------------

bool WP::GetLastEvent(WDB *b, int timeout, WDEvent &event) {
   // wait for new event with timeout
   {
      std::unique_lock<std::mutex> lock(mEventMutex);
      if (!(mEventCV.wait_for(lock, std::chrono::milliseconds(timeout), [this]() { return mEventNew; })))
         return false;
   }

   {
      std::lock_guard<std::mutex> lock(mEventAccessMutex);

      if (mEventLast.size() == 0)
         return false;

      event = *mEventLast[b->GetSerialNumber()];
      mEventNew = false;
      return true;
   }
}

//--------------------------------------------------------------------

bool WP::GetLastEvent(int timeout, std::vector<WDEvent *> event) {
   // wait for new event with timeout
   {
      std::unique_lock<std::mutex> lock(mEventMutex);
      if (!(mEventCV.wait_for(lock, std::chrono::milliseconds(timeout), [this]() { return mEventNew; }))) {

         if (mLogfile != "") {
            std::ofstream f;
            f.open(mLogfile, std::ios_base::app);
            f << "Timeout receiving event after " << timeout << "000us." << std::endl;
         }

         return false;
      }
   }

   auto startTime = usStart();

   {
      std::lock_guard<std::mutex> lock(mEventAccessMutex);
      int copied = 0;

      for (auto ed: event) {
         WDEvent *es = mEventLast[ed->mBoardId];
         if (es->IsEventValid()) {
            *ed = *es;
            copied++;
         } else {
            ed->mEventValid = false;
         }
      }

      mEventNew = false;
      if (mLogfile != "") {
         std::ofstream f;
         f.open(mLogfile, std::ios_base::app);
         f << "Fully copied event " << usSince(startTime) << " us with " << copied << " boards" << std::endl;
      }
      return true;
   }
}

//--------------------------------------------------------------------

void WP::StartNewEvent() {
   for (auto &e: mEvent) {
      e.second->ClearEvent();
   }

   mReceivedPacketsThisEvent = 0;
   mCurrentEvent = -1;
}

//--------------------------------------------------------------------

bool WP::IsEventValid() {

   for (auto &e: mWdbRequested) {
      auto boardId = e->GetSerialNumber();
      auto it = mEvent.find(boardId);
      if (it == mEvent.end())
         return false;
      if (!it->second->IsEventValid())
         return false;
   }

   return true;
}

void WP::LogEvent(FRAME_WDAQ_HEADER *pdaqh, FRAME_WDB_HEADER *ph) {
   if (mLogfile != "" || mVerbose >= 3) {
      std::ofstream f;
      char line[256];
      std::string flags;
      f.open(mLogfile, std::ios_base::app);

      // new line at start of event
      if (pdaqh->wdaq_flags & (1 << cWDAQFlagStartOfEvent)) {
         f << std::endl;
         if (mVerbose >= 3)
            std::cout << std::endl;
      }

      if (pdaqh->wdaq_flags & (1 << cWDAQFlagEndOfEvent))
         flags += "EOE,";
      if (pdaqh->wdaq_flags & (1 << cWDAQFlagStartOfEvent))
         flags += "BOE,";
      if (pdaqh->wdaq_flags & (1 << cWDAQFlagEndOfType))
         flags += "EOT,";
      if (pdaqh->wdaq_flags & (1 << cWDAQFlagStartOfType))
         flags += "BOT,";

      if (flags.back() == ',')
         flags.pop_back();

      snprintf(line, sizeof(line), "%06dus #%04d from WD%03d, P#=%5d T=%s F=%15s PL=%4d OF=%5d, ",
               usSince(mEventStartTime),
               mReceivedPacketsThisEvent - 1,
               pdaqh->serial_number,
               pdaqh->packet_number,
               pdaqh->data_type == cDataTypeDRS ? "DRS" :
               pdaqh->data_type == cDataTypeADC ? "ADC" :
               pdaqh->data_type == cDataTypeTDC ? "TDC" :
               pdaqh->data_type == cDataTypeTrg ? "TRG" :
               pdaqh->data_type == cDataTypeScaler ? "SLR" :
               pdaqh->data_type == cDataTypeDummy ? "DMY" :
               pdaqh->data_type == cDataTypeTCB ? "TCB" : "UNK",
               flags.c_str(),
               pdaqh->payload_length,
               pdaqh->data_chunk_offset
      );

      f << line;

      if (mVerbose >= 3)
         std::cout << line;

      // log event type specific data
      if (pdaqh->data_type == cDataTypeDRS || pdaqh->data_type == cDataTypeADC) {
         flags.clear();
         if (ph->wd_flags & (1 << cWDFlagDRSPLLLock))
            flags += "DLK,";
         if (ph->wd_flags & (1 << cWDFlagLMKPLLLock))
            flags += "LLK,";
         if (ph->wd_flags & (1 << cWDFlagNewTriggerInfo))
            flags += "TIF,";
         if (ph->wd_flags & (1 << cWDFlagTriggerInfoParityError))
            flags += "TPE,";
         if (ph->wd_flags & (1 << cWDFlagZeroSuppEnable))
            flags += "ZSE,";
         if (ph->wd_flags & (1 << cWDFalgZeroSuppInhibit))
            flags += "ZSI,";
         if (flags.back() == ',')
            flags.pop_back();

         snprintf(line, sizeof(line), "WF=%7s EN=%5d A/C=%d/%02d TC=%04d T=%1.1lf\n",
                  flags.c_str(),
                  pdaqh->event_number,
                  (ph->channel_info >> 7) & 0x1,
                  (ph->channel_info) & 0x1f,
                  ph->drs_trigger_cell,
                  ph->temperature * 0.0625);
      } else
         snprintf(line, sizeof(line), "\n");

      f << line;

      if (mVerbose >= 3)
         std::cout << line;

      if (mVerbose >= 4) {
         unsigned char *p = (unsigned char *)(ph+1);
         for (int i = 0; i < 16; i++)
            std::cout << std::showbase << std::internal << std::setfill('0') << std::hex << std::setw(4) << (unsigned int)(*p++) << " ";
         std::cout << std::endl << std::endl;
      }
   }
}

//--------------------------------------------------------------------

int WP::ReceiveWfPacket() {
   fd_set readfds;
   struct timeval timeout;
   int status;

   FD_ZERO(&readfds);
   FD_SET(WP::gDataSocket, &readfds);

   timeout.tv_sec = 5;
   timeout.tv_usec = 0;

   do {
      status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
   } while (status == -1 && errno == EINTR);  // don't return if an alarm signal was caught

   if (status == -1)
      perror("select");

   if (!FD_ISSET(WP::gDataSocket, &readfds)) {
      return TIMEOUT;
   }

   // packet is available, so receive it
   struct sockaddr_in remote_addr;
   unsigned char buffer[1800];

   int len = sizeof(remote_addr);
   int n = (int) recvfrom(WP::gDataSocket, (char *) buffer, sizeof(buffer), 0,
                          (struct sockaddr *) &remote_addr, (socklen_t *) &len);

   FRAME_WDAQ_HEADER *pwdaq_header = (FRAME_WDAQ_HEADER *) buffer;
   FRAME_WDB_HEADER *pwdb_header = (FRAME_WDB_HEADER *) (((FRAME_WDAQ_HEADER *) buffer) + 1);

   // return if invalid header
   if (n < (int) sizeof(FRAME_WDAQ_HEADER))
      return 0;

   // check protocol version
   if (pwdaq_header->protocol_version > WD2_UDP_PROTOCOL_VERSION) {
      std::cerr << "Invalid protocol version " << (int) pwdaq_header->protocol_version << ", expected "
                << WD2_UDP_PROTOCOL_VERSION << ". Probably WDBLib library update required." << std::endl;
      return 0;
   }
   if (pwdaq_header->protocol_version < WD2_UDP_PROTOCOL_VERSION) {
      std::cerr << "Invalid protocol version " << (int) pwdaq_header->protocol_version << ", expected "
                << WD2_UDP_PROTOCOL_VERSION << ". Probably WDB firmware update required." << std::endl;
      return 0;
   }

   if (mReceivedPacketsThisEvent == 0)
      mEventStartTime = usStart();

   mReceivedPacketsThisEvent++;
   mWDReceivedPackets++;

   // correct endianness of header data
   pwdaq_header->serial_number = SWAP_UINT16(pwdaq_header->serial_number);
   pwdaq_header->packet_number = SWAP_UINT16(pwdaq_header->packet_number);
   pwdaq_header->event_number = SWAP_UINT32(pwdaq_header->event_number);
   pwdaq_header->payload_length = SWAP_UINT16(pwdaq_header->payload_length);
   pwdaq_header->data_chunk_offset = SWAP_UINT16(pwdaq_header->data_chunk_offset);

   // correct endianness of WD header data
   if (pwdaq_header->data_type == cDataTypeDRS || pwdaq_header->data_type == cDataTypeADC) {
      pwdb_header->samples_per_event_per_channel = SWAP_UINT16(pwdb_header->samples_per_event_per_channel);
      pwdb_header->sampling_frequency = SWAP_UINT32(pwdb_header->sampling_frequency);
      pwdb_header->zero_suppression_mask = SWAP_UINT16(pwdb_header->zero_suppression_mask);
      pwdb_header->tx_enable = SWAP_UINT32(pwdb_header->tx_enable);
      pwdb_header->drs_trigger_cell = SWAP_UINT16(pwdb_header->drs_trigger_cell);
      pwdb_header->temperature = SWAP_UINT16(pwdb_header->temperature);
      pwdb_header->dac_pzc = SWAP_UINT16(pwdb_header->dac_pzc);
      pwdb_header->dac_ofs = SWAP_UINT16(pwdb_header->dac_ofs);
      pwdb_header->dac_rofs = SWAP_UINT16(pwdb_header->dac_rofs);
      pwdb_header->frontend_settings = SWAP_UINT16(pwdb_header->frontend_settings);
      pwdb_header->time_stamp = SWAP_UINT64(pwdb_header->time_stamp);
   }

   // use following code to artificially dop packages for testing
//   if ((double)rand()/RAND_MAX < 0.001) {
//      std::cout << "Packet artificially dropped" << std::endl;
//      return SUCCESS;
//   }

   // find event belonging to this board
   if (mEvent.find(pwdaq_header->serial_number) == mEvent.end()) {
      // create new event
      mEvent[pwdaq_header->serial_number] = new WDEvent(pwdaq_header->serial_number);
      mEventLast[pwdaq_header->serial_number] = new WDEvent(pwdaq_header->serial_number);
   }
   WDEvent *event = mEvent[pwdaq_header->serial_number];

   // on first packet for event, start new event if previous event not fully received
   if ((pwdaq_header->wdaq_flags & (1 << cWDAQFlagStartOfEvent)) &&
       event->mReceivedPackets > 0) {

      if (!IsEventValid() && event->mReceivedPackets > 1) {
         if (mVerbose)
            std::cerr << "Partially received event dropped, board id=" << pwdaq_header->serial_number
                      << ", efficiency=" << GetWDPacketEfficiency() << std::endl;

         if (mLogfile != "") {
            std::ofstream f;
            f.open(mLogfile, std::ios_base::app);
            f << "Partially received event dropped, board id=" << pwdaq_header->serial_number << std::endl;
         }

         if (event->mFirstPacketNumber > 0)
            mWDDroppedPackets += event->mLastPacketNumber - event->mFirstPacketNumber + 1 - event->mReceivedPackets;
      }

      StartNewEvent();
      mReceivedPacketsThisEvent = 1;
      mEventStartTime = usStart();
   }

   // log and display general event header
   LogEvent(pwdaq_header, pwdb_header);

   // set general event header from packet
   event->SetEventHeaderInfo(pwdaq_header);

   // evaluate SOE / EOE, packet type etc.
   event->ProcessPacket(pwdaq_header);

   // calculate packet efficiency every ten seconds
   time_t now;
   time(&now);
   if (now > mStartStatistics + 3) {
      mPacketEfficiency = (double) mWDReceivedPackets / (mWDReceivedPackets + mWDDroppedPackets);
      mWDReceivedPackets = mWDDroppedPackets = 0;
      mStartStatistics = now;
   }

   // check package consistency for DRS and ADC events
   if (pwdaq_header->data_type == cDataTypeDRS || pwdaq_header->data_type == cDataTypeADC) {
      int channel_number = (pwdb_header->channel_info) & 0x1f;

      if (mCurrentEvent == -1)
         mCurrentEvent = pwdaq_header->event_number;

      // check for valid channel number
      if (channel_number >= WD_N_CHANNELS) {
         std::cerr << "Found invalid DRS channel " << channel_number << " for event " << pwdaq_header->event_number << std::endl;
         return 0;
      }

      // drop package if it belongs to previous event
      if (pwdaq_header->event_number < (unsigned int) mCurrentEvent) {
         std::cerr << "Package of previous event dropped, package event=" << pwdaq_header->event_number << ", "
                   << "current event=" << mCurrentEvent << ", "
                   << "board id=" << pwdaq_header->serial_number << std::endl;

         if (mLogfile != "") {
            std::ofstream f;
            f.open(mLogfile, std::ios_base::app);
            f << "Package of previous event dropped, package event=" << pwdaq_header->event_number << ", "
              << "current event=" << mCurrentEvent << ", "
              << "board id=" << pwdaq_header->serial_number << std::endl;
         }
         return 0;
      }
   }

   // decode DRS waveform data ----------
   if (pwdaq_header->data_type == cDataTypeDRS) {

      // return on invalid header
      if (pwdaq_header->payload_length % 3 != 0)
         return 0;
      if (pwdaq_header->data_chunk_offset % 3 != 0)
         return 0;

      int numberBins = (int) pwdaq_header->payload_length / 1.5;
      int firstBin = pwdaq_header->data_chunk_offset / 1.5;
      int channel_number = (pwdb_header->channel_info) & 0x1f;

      // set DRS specific part from packet
      event->SetWDEventHeaderInfo(pwdaq_header, pwdb_header);
      event->mVCalibrated = false;
      event->mTCalibrated = false;
      mLastEventNumber = pwdaq_header->event_number;

      if (pwdaq_header->wdaq_flags & (1 << cWDAQFlagStartOfType)) {
         event->mTriggerCellDrs0 = -1;
         event->mTriggerCellDrs1 = -1;
      }

      if (channel_number < 8 || channel_number == 16) {
         if (event->mTriggerCellDrs0 == -1)
            event->mTriggerCellDrs0 = pwdb_header->drs_trigger_cell;
      } else {
         if (event->mTriggerCellDrs1 == -1)
            event->mTriggerCellDrs1 = pwdb_header->drs_trigger_cell;
      }

      // print warning if inconsistent trigger cells are found
      if (channel_number < 8 || channel_number == 16) {
         if (event->mTriggerCellDrs0 != pwdb_header->drs_trigger_cell)
            std::cerr << "Found inconsistend trigger cell for event " << pwdaq_header->event_number << std::endl;
      } else {
         if (event->mTriggerCellDrs1 != pwdb_header->drs_trigger_cell)
            std::cerr << "Found inconsistend trigger cell for event " << pwdaq_header->event_number << std::endl;
      }

      auto pd = (unsigned char *) (pwdb_header + 1);
      for (int i = 0; i < numberBins; i += 2) {
         // decode two bins
         short data1 = ((pd[1] & 0x0F) << 8) | pd[0];
         short data2 = ((unsigned short) pd[2] << 4) | (pd[1] >> 4);
         // subtract binary offset
         data1 -= 0x800;
         data2 -= 0x800;
         pd += 3;

         event->mWfUDRS[channel_number][firstBin + i] = (float) data1 * (1 / 4096.0); // 1V DRS range with 12 bits
         event->mWfUDRS[channel_number][firstBin + i + 1] = (float) data2 * (1 / 4096.0);
      }

      // mark received channel
      event->mDRSChannelPresent[channel_number] = true;
   }

   // decode ADC waveform data ----------
   if (pwdaq_header->data_type == cDataTypeADC) {

      // return on invalid header
      if (pwdaq_header->payload_length % 3 != 0)
         return 0;
      if (pwdaq_header->data_chunk_offset % 3 != 0)
         return 0;

      int numberBins = (int) pwdaq_header->payload_length / 1.5;
      int firstBin = pwdaq_header->data_chunk_offset / 1.5;
      int channel_number = (pwdb_header->channel_info) & 0x1f;

      // set ADC specific part from packet
      event->SetWDEventHeaderInfo(pwdaq_header, pwdb_header);
      event->mVCalibrated = false;
      event->mTCalibrated = false;
      mLastEventNumber = pwdaq_header->event_number;

      auto pd = (unsigned char *) (pwdb_header + 1);
      for (int i = 0; i < numberBins; i += 2) {
         // decode two bins
         short data1 = ((pd[1] & 0x0F) << 8) | pd[0];
         short data2 = ((unsigned short) pd[2] << 4) | (pd[1] >> 4);
         // subtract binary offset
         data1 -= 0x800;
         data2 -= 0x800;
         pd += 3;

         event->mWfUADC[channel_number][firstBin + i] = (float) data1 * (2 / 4096.0); // 2V ADC range with 12 bits
         event->mWfUADC[channel_number][firstBin + i + 1] = (float) data2 * (2 / 4096.0);
      }

      // mark received channel
      event->mADCChannelPresent[channel_number] = true;
   }

   // decode TDC waveform data
   if (pwdaq_header->data_type == cDataTypeTDC) {
      int channel_number = (pwdb_header->channel_info) & 0x1f;

      auto pd = (unsigned char *) (pwdb_header + 1);
      memcpy(&event->mWfTDC[channel_number][pwdaq_header->data_chunk_offset], pd, pwdaq_header->payload_length);

      // mark received channel
      event->mTDCChannelPresent[channel_number] = true;
   }

   // decode advanced trigger data
   if (pwdaq_header->data_type == cDataTypeTrg) {
      auto pd = (unsigned long long *) (pwdb_header + 1);
      //assure data are transmitted in 64-bit blocks
      if (pwdaq_header->payload_length % 8 != 0)
         return 0;
      if (pwdaq_header->data_chunk_offset % 8 != 0)
         return 0;
      for (int i = 0; i < pwdaq_header->payload_length / 8; i++) {
         event->mTrgData[pwdaq_header->data_chunk_offset / 8 + i] = SWAP_UINT64(pd[i]);
      }
   }

   // decode scaler data
   if (pwdaq_header->data_type == cDataTypeScaler) {
      auto pd = (unsigned long long *) (pwdb_header + 1);
      if (pwdaq_header->payload_length > sizeof(event->mScaler))
         return 0;
      for (int i = 0; i < WD_N_SCALER; i++)
         event->mScaler[i] = SWAP_UINT64(pd[17 - i]);
   }

   return SUCCESS;
}

//--------------------------------------------------------------------

void WP::UnrotateWaveforms() {
   for (auto &ev: mEvent) {
      if (!ev.second->mEventValid)
         continue;

      float wf[WD_N_CHANNELS][1024];

      for (int i = 0; i < WD_N_CHANNELS; i++)
         for (int j = 0; j < 1024; j++)
            wf[i][j] = ev.second->mWfUDRS[i][j];

      // un-rotate waveforms
      for (int i = 0; i < WD_N_CHANNELS; i++) {
         int tc = ev.second->mTriggerCell[i];
         for (int j = 0; j < 1024; j++)
            ev.second->mWfUDRS[i][(j + tc) % 1024] = wf[i][j];
      }
   }
}

//--------------------------------------------------------------------

void WP::StartCalibrationVoltage(WDB *wdb) {
   int i;
   if (wdb != nullptr) {
      for (i = 0; i < mWdb.size(); i++)
         if (mWdb[i]->GetSerialNumber() == wdb->GetSerialNumber())
            break;
   }

   calibProg.mode = cCmVoltage;
   calibProg.lastBoard = (wdb == nullptr) ? mWdb.size() : i+1;
   calibProg.iBoard = (wdb == nullptr) ? 0 : i;
   calibProg.state = cCsFirstBoard;
}

//--------------------------------------------------------------------

void WP::StartCalibrationTime(WDB *wdb) {
   int i;
   if (wdb != nullptr) {
      for (i = 0; i < mWdb.size(); i++)
         if (mWdb[i]->GetSerialNumber() == wdb->GetSerialNumber())
            break;
   }

   calibProg.mode = cCmTime;
   calibProg.lastBoard = (wdb == nullptr) ? mWdb.size() : i+1;
   calibProg.iBoard = (wdb == nullptr) ? 0 : i;
   calibProg.state = cCsFirstBoard;
};

//--------------------------------------------------------------------

void WP::CalibrateWaveforms(std::map<int, WDEvent *> event) {
   for (auto &ev: event) {
      if (ev.second->IsEventValid())
         CalibrateWaveforms(ev.second);
   }
}

//--------------------------------------------------------------------

void WP::CalibrateWaveforms(WDEvent *ev) {
   // search board belonging to this event
   WDB *wdb = WP::GetBoard(ev->mBoardId);

   if (ev->mHasADCData) { //---------- calibrate ADC data ----------

      ev->mTCalibrated = true;

      if (mRangeCalib) {
         float ofs;

         ev->mVCalibrated = true;
         for (int i = 0; i < WD_N_CHANNELS - 2; i++) { // exclude clock channels
            if (fabs(wdb->GetRange() - (-0.45)) < 0.001)
               ofs = wdb->mVCalib.mCalib.adc_offset_range0[i];
            else if (fabs(wdb->GetRange()) < 0.001)
               ofs = wdb->mVCalib.mCalib.adc_offset_range1[i];
            else if (fabs(wdb->GetRange() - 0.45) < 0.001)
               ofs = wdb->mVCalib.mCalib.adc_offset_range2[i];
            else
               ofs = 0;
            for (int j = 0; j < 2048; j++)
               ev->mWfUADC[i][j] -= ofs;
         }

         if (mLogfile != "") {
            std::ofstream f;
            f.open(mLogfile, std::ios_base::app);
            f << "Calibrated ADC for board " << wdb->GetName() << " (time = " << usSince(mEventStartTime) << "us)"
              << std::endl;
         }
      }

      // just set nominal time bins from ADC sampling rate
      for (int i = 0; i < WD_N_CHANNELS; i++)
         for (int j = 0; j < 2048; j++)
            ev->mWfTADC[i][j] = (float) (j * 1E-6 / ev->mADCSamplingFrequency);

      // shift ADC values
      for (int i = 0; i < WD_N_CHANNELS - 2; i++)
         for (int j = 0; j < 2048; j++)
            ev->mWfUADC[i][j] += 0.7;

   }

   if (ev->mHasDRSData) {  //---------- calibrate DRS data ----------

      bool bValid = (ev->mDRSSamplingFrequency == wdb->mVCalib.GetSamplingFrequency() &&
                     wdb->mVCalib.IsValid());

      if (!bValid) {
         if (mLogfile != "") {
            std::ofstream f;
            f.open(mLogfile, std::ios_base::app);
            f << "DRS data received for board " << wdb->GetName() << " but calibrations not valid: event sampling freq "
              << ev->mDRSSamplingFrequency << " calibration frequency " << wdb->mVCalib.GetSamplingFrequency()
              << ", calibration valid flag " << wdb->mVCalib.IsValid() << " (time = " << usSince(mEventStartTime)
              << "us)" << std::endl;
         }
      } else {
         if (mLogfile != "") {
            std::ofstream f;
            f.open(mLogfile, std::ios_base::app);
            f << "DRS data received for board " << wdb->GetName() << ", starting calibrations (time = "
              << usSince(mEventStartTime) << "us)" << std::endl;
         }
      }

      // cell-by-cell offset calibration
      if (mOfsCalib1 && bValid) {
         ev->mVCalibrated = true;

         if (mRotateWaveform) {
            for (int i = 0; i < WD_N_CHANNELS; i++) {
               int tc = ev->mTriggerCell[i];
               for (int j = 0; j < 1024; j++)
                  ev->mWfUDRS[i][j] -= wdb->mVCalib.mCalib.wf_offset1[i][(j + tc) % 1024];
            }
         } else {
            for (int i = 0; i < WD_N_CHANNELS; i++)
               for (int j = 0; j < 1024; j++)
                  ev->mWfUDRS[i][j] -= wdb->mVCalib.mCalib.wf_offset1[i][j];
         }

         if (mLogfile != "") {
            std::ofstream f;
            f.open(mLogfile, std::ios_base::app);
            f << "DRS cell calibrated for board " << wdb->GetName() << " (time = " << usSince(mEventStartTime) << "us)"
              << std::endl;
         }
      }

      // start-to-end offset calibration
      if (mOfsCalib2 && bValid) {
         for (int i = 0; i < WD_N_CHANNELS - 2; i++)
            for (int j = 0; j < 1024; j++)
               ev->mWfUDRS[i][j] -= wdb->mVCalib.mCalib.wf_offset2[i][j];
         if (mLogfile != "") {
            std::ofstream f;
            f.open(mLogfile, std::ios_base::app);
            f << "DRS start to end calibrated for board " << wdb->GetName() << " (time = " << usSince(mEventStartTime)
              << "us)" << std::endl;
         }
      }

      // gain calibration
      if (mGainCalib && bValid) {
         if (mRotateWaveform) {
            for (int i = 0; i < WD_N_CHANNELS - 2; i++) { // exclude clock channels
               int tc = ev->mTriggerCell[i];
               for (int j = 0; j < 1024; j++) {
                  if (ev->mWfUDRS[i][j] > 0)
                     ev->mWfUDRS[i][j] /= wdb->mVCalib.mCalib.wf_gain1[i][(j + tc) % 1024];
                  else
                     ev->mWfUDRS[i][j] /= wdb->mVCalib.mCalib.wf_gain2[i][(j + tc) % 1024];
               }
            }
         } else {
            for (int i = 0; i < WD_N_CHANNELS - 2; i++)
               for (int j = 0; j < 1024; j++) {
                  if (ev->mWfUDRS[i][j] > 0)
                     ev->mWfUDRS[i][j] /= wdb->mVCalib.mCalib.wf_gain1[i][j];
                  else
                     ev->mWfUDRS[i][j] /= wdb->mVCalib.mCalib.wf_gain2[i][j];
               }
         }
         if (mLogfile != "") {
            std::ofstream f;
            f.open(mLogfile, std::ios_base::app);
            f << "DRS gain calibrated for board " << wdb->GetName() << " (time = " << usSince(mEventStartTime) << "us)"
              << std::endl;
         }
      }

      // range calibration
      if (mRangeCalib && bValid) {
         float ofs;

         for (int i = 0; i < WD_N_CHANNELS - 2; i++) { // exclude clock channels
            if (fabs(wdb->GetRange() - (-0.45)) < 0.001)
               ofs = wdb->mVCalib.mCalib.drs_offset_range0[i];
            else if (fabs(wdb->GetRange()) < 0.001)
               ofs = wdb->mVCalib.mCalib.drs_offset_range1[i];
            else if (fabs(wdb->GetRange() - 0.45) < 0.001)
               ofs = wdb->mVCalib.mCalib.drs_offset_range2[i];
            else
               ofs = 0;
            for (int j = 0; j < 1024; j++)
               ev->mWfUDRS[i][j] -= ofs;
         }
         if (mLogfile != "") {
            std::ofstream f;
            f.open(mLogfile, std::ios_base::app);
            f << "DRS range calibrated for board " << wdb->GetName() << " (time = " << usSince(mEventStartTime) << "us)"
              << std::endl;
         }
      }

      // calculate calibrated time for each event
      bValid = (ev->mDRSSamplingFrequency == wdb->mTCalib.GetSamplingFrequency() &&
                wdb->mTCalib.IsValid());
      if (mTimeCalib1 && bValid) {
         ev->mTCalibrated = true;

         // integrate time from delta-t values
         for (int ch = 0; ch < WD_N_CHANNELS; ch++) {
            int tc = ev->mTriggerCell[ch];
            if (!mRotateWaveform)
               tc = 0;
            ev->mWfTDRS[ch][0] = 0;
            for (int i = 1; i < 1024; i++)
               ev->mWfTDRS[ch][i] = ev->mWfTDRS[ch][i - 1] + wdb->mTCalib.mCalib.dt[ch][(i - 1 + tc) % 1024];
         }
         // align cell#0 of all channels inside chip0
         int tc = mRotateWaveform ? ev->mTriggerCellDrs0 : 0;
         float t1 = ev->mWfTDRS[0][(1024 - tc) % 1024];
         for (int ch = 1; ch < 8; ch++) {
            float t2 = ev->mWfTDRS[ch][(1024 - tc) % 1024];
            float dt = t1 - t2;
            for (int i = 0; i < 1024; i++)
               ev->mWfTDRS[ch][i] += dt;
         }
         float t2 = ev->mWfTDRS[16][(1024 - tc) % 1024];
         float dt = t1 - t2;
         for (int i = 0; i < 1024; i++)
            ev->mWfTDRS[16][i] += dt;

         // align cell#0 of all channels inside chip1 to chip0
         tc = mRotateWaveform ? ev->mTriggerCellDrs1 : 0;
         for (int ch = 8; ch < 16; ch++) {
            t2 = ev->mWfTDRS[ch][(1024 - tc) % 1024];
            dt = t1 - t2;
            for (int i = 0; i < 1024; i++)
               ev->mWfTDRS[ch][i] += dt;
         }
         t2 = ev->mWfTDRS[17][(1024 - tc) % 1024];
         dt = t1 - t2;
         for (int i = 0; i < 1024; i++)
            ev->mWfTDRS[17][i] += dt;

      } else {
         // set nominal sampling intervals
         for (int i = 0; i < WD_N_CHANNELS; i++)
            for (int j = 0; j < 1024; j++)
               ev->mWfTDRS[i][j] = (float) (j * 1E-6 / ev->mDRSSamplingFrequency);
      }

      // apply time offsets (different PCB path traces)
      if (mTimeCalib2 && bValid) {
         for (int i = 0; i < WD_N_CHANNELS; i++)
            for (int j = 0; j < 1024; j++)
               ev->mWfTDRS[i][j] -= wdb->mTCalib.mCalib.offset[i];
      }

      // apply horizontal trigger position correction
      if (mTimeCalib3 && bValid) {
         bool bFound = false;
         double dt_min = 1;
         for (int i = 4; i < 1020; i++) {
            for (int c = 0; c < 16; c++) {
               if (!ev->mDRSChannelPresent[c])
                  continue;

               // check if current channel is in any pattern
               bool chActive = false;
               for (int p = 0; p < 18; p++) {
                  if (wdb->GetTrgPtrnEn() & (1 << p)) {
                     if (wdb->GetTrgSrcEnPtrn(p) & (1 << c)) {
                        chActive = true;
                        break;
                     }
                  }
               }

               if (!chActive)
                  continue;

               double tl = wdb->GetDacTriggerLevelV(c);

               // try to figure out if we trigger on rising or falling edge
               bool rising = ((wdb->GetLeadTrailEdgeSel() == 0) &&
                              ((wdb->GetTrgSrcPolarity() & (1 << c)) == 0)) ||
                             ((wdb->GetLeadTrailEdgeSel() == 1) &&
                              ((wdb->GetTrgSrcPolarity() & (1 << c)) > 0));

               bool bEdge = false;
               if (rising) {
                  if (ev->mWfUDRS[c][i] < tl && ev->mWfUDRS[c][i + 1] >= tl)
                     bEdge = true;
               } else {
                  if (ev->mWfUDRS[c][i] > tl && ev->mWfUDRS[c][i + 1] <= tl)
                     bEdge = true;
               }

               if (bEdge) {
                  double t0 = ev->mWfTDRS[c][i] +
                              (ev->mWfTDRS[c][i + 1] - ev->mWfTDRS[c][i]) * (tl - ev->mWfUDRS[c][i]) /
                              (ev->mWfUDRS[c][i + 1] - ev->mWfUDRS[c][i]);
                  double iofs = 95 - (wdb->GetDrsSampleFreqMhz() / 1000 - 1) * 5;
                  double dt = t0 - (1024 * 1E-6 / wdb->GetDrsSampleFreqMhz() - iofs * 1E-9
                                    - wdb->GetTriggerDelayNs() * 1E-9);
                  if (fabs(dt) < fabs(dt_min)) {
                     dt_min = dt;
                     bFound = true;
                  }
               }
            }
         }

         if (bFound) {
            for (int i = 0; i < WD_N_CHANNELS; i++)
               for (int j = 0; j < 1024; j++)
                  ev->mWfTDRS[i][j] -= (float) dt_min;
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

void GetTimeStamp(TIMESTAMP &ts) {
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

   ts.Year = lt->tm_year + 1900;
   ts.Month = lt->tm_mon + 1;
   ts.Day = lt->tm_mday;
   ts.Hour = lt->tm_hour;
   ts.Minute = lt->tm_min;
   ts.Second = lt->tm_sec;
   ts.Milliseconds = t.tv_usec / 1000;
#endif /* OS_UNIX */
}

//--------------------------------------------------------------------

void WP::SaveWaveforms() {
   static unsigned char *buffer = NULL;
   int buffer_size;
   unsigned char *p;

   if (li.fh == 0 && li.xml == NULL)
      return;

   int n = mEvent.size();
   buffer_size = 8 + n * (4 + 18 * (4 + 1024 * 4)); // time array
   buffer_size += 8 + 16 + n * (4 + 18 * (12 + 1024 * 2));  // voltage array
   buffer_size += n * (18 * (4 + 2048 * 2));  // adc array
   buffer_size += n * (18 * (4 + 512 * 1));  // tdc array
   buffer_size += n * (4 + 512 * 4);  // trg array
   if (!buffer) {
      buffer = (unsigned char *) malloc(buffer_size);
      assert(buffer);
   }

   TIMESTAMP ts;
   GetTimeStamp(ts);

   if (li.format == cLiFormatXML) {
      char str[256];
      mxml_start_element(li.xml, "Event");
      sprintf(str, "%d", li.nLogged + 1);
      mxml_write_element(li.xml, "Serial", str);
      sprintf(str, "%4d/%02d/%02d %02d:%02d:%02d.%03d", ts.Year, ts.Month,
              ts.Day, ts.Hour, ts.Minute, ts.Second, ts.Milliseconds);
      mxml_write_element(li.xml, "Time", str);
      mxml_write_element(li.xml, "HUnit", "ns");
      mxml_write_element(li.xml, "VUnit", "mV");

      int b = 0;
      for (auto &it: mEvent) {
         auto ev = it.second;

         if (!li.bAll && b != li.board)
            continue;

         sprintf(str, "Board_%d", it.first);
         mxml_start_element(li.xml, str);
         for (int i = 0; i < WD_N_CHANNELS; i++) {
            if (ev->mDRSChannelPresent[i]) {
               sprintf(str, "CHN%d", i);
               mxml_start_element(li.xml, str);
               sprintf(str, "%d", ev->mTriggerCell[i]);
               mxml_write_element(li.xml, "Trigger_Cell", str);

               uint64_t s = 0;
               for (auto &bi: mWdb)
                  if (bi->GetSerialNumber() == ev->mBoardId) {
                     std::vector<uint64_t> sc;
                     bi->GetScalers(sc, false);
                     s = sc[i];
                     break;
                  }
               sprintf(str, "%llu", s);
               mxml_write_element(li.xml, "Scaler", str);

               mxml_start_element(li.xml, "Waveform");
               strcpy(str, "\n");

               if (ev->mHasDRSData) {
                  for (int j = 0; j < 1024; j++) {
                     sprintf(str, "%1.3f,%1.1f", ev->mWfTDRS[i][j] * 1E9, ev->mWfUDRS[i][j] * 1E3);
                     mxml_write_element(li.xml, "DRSData", str);
                  }
               }

               if (ev->mHasADCData) {
                  for (int j = 0; j < 2048; j++) {
                     sprintf(str, "%1.3f,%1.1f", ev->mWfTADC[i][j] * 1E9, ev->mWfUADC[i][j] * 1E3);
                     mxml_write_element(li.xml, "ADCData", str);
                  }
               }

               mxml_end_element(li.xml); // CHNx
               mxml_end_element(li.xml); // CHNx
            }
         }
         mxml_end_element(li.xml); //Board
         b++;
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

         int b = 0;
         for (auto const &it: mEvent) {
            auto ev = it.second;
            WDB *wdb = GetBoard(it.first);
            assert(wdb);

            if (!li.bAll && b != li.board)
               continue;

            // store board serial number
            sprintf((char *) p, "B#");
            p += 2;
            *(unsigned short *) p = ev->mBoardId;
            p += sizeof(unsigned short);

            for (int i = 0; i < WD_N_CHANNELS; i++) {
               if (ev->mDRSChannelPresent[i]) {

                  sprintf((char *) p, "C%03d", i);
                  p += 4;
                  for (int j = 0; j < 1024; j++) {
                     // save binary time as 32-bit float value
                     *(float *) p = wdb->mTCalib.mCalib.dt[i][j];
                     p += sizeof(float);
                  }
               }
            }
            b++;
         }
      }

      memcpy(p, "EHDR", 4);
      p += 4;
      *(int *) p = li.nLogged;
      p += sizeof(int);
      *(unsigned short *) p = ts.Year;
      p += sizeof(unsigned short);
      *(unsigned short *) p = ts.Month;
      p += sizeof(unsigned short);
      *(unsigned short *) p = ts.Day;
      p += sizeof(unsigned short);
      *(unsigned short *) p = ts.Hour;
      p += sizeof(unsigned short);
      *(unsigned short *) p = ts.Minute;
      p += sizeof(unsigned short);
      *(unsigned short *) p = ts.Second;
      p += sizeof(unsigned short);
      *(unsigned short *) p = ts.Milliseconds;
      p += sizeof(unsigned short);
      *(unsigned short *) p = (unsigned short) (0); // range
      p += sizeof(unsigned short);

      int b = 0;
      for (auto &it: mEvent) {
         auto ev = it.second;

         if (!li.bAll && b != li.board)
            continue;

         // store board serial number
         sprintf((char *) p, "B#");
         p += 2;
         *(unsigned short *) p = ev->mBoardId;
         p += sizeof(unsigned short);

         //Get Board
         WDB *wdb = GetBoard(ev->mBoardId);
         assert(wdb);

         //Get Scalers
         std::vector<uint64_t> sc;
         wdb->GetScalers(sc, false);

         if (ev->mHasDRSData) {
            for (int i = 0; i < WD_N_CHANNELS; i++) {
               if (ev->mDRSChannelPresent[i]) {
                  // channel header
                  sprintf((char *) p, "C%03d", i);
                  p += 4;

                  // write scaler
                  uint64_t s = sc[i];
                  memcpy(p, &s, sizeof(unsigned int));
                  p += sizeof(int);

                  // write trigger cell
                  sprintf((char *) p, "T#");
                  p += 2;
                  *(unsigned short *) p = ev->mTriggerCell[i];
                  p += sizeof(unsigned short);

                  for (int j = 0; j < 1024; j++) {
                     // save binary date as 16-bit value:
                     // 0 = -0.5V,  65535 = +0.5V    for range 0
                     // 0 = -0.05V, 65535 = +0.95V   for range 0.45
                     // 0 = -0.95V, 65535 = +0.05V   for range -0.45
                     float f = ev->mWfUDRS[i][j] - wdb->GetRange();
                     if (f < -0.5)
                        f = -0.5;
                     if (f > 0.5)
                        f = 0.5;
                     unsigned short d = (unsigned short) ((f + 0.5) * 65535);
                     *(unsigned short *) p = d;
                     p += sizeof(unsigned short);
                  }
               }
            }
         }

         if (ev->mHasADCData) {
            for (int i = 0; i < WD_N_CHANNELS; i++) {
               if (ev->mADCChannelPresent[i]) {
                  // channel header
                  sprintf((char *) p, "A%03d", i);
                  p += 4;
                  for (int j = 0; j < 2048; j++) {
                     // save binary date as 16-bit value:
                     // 0 = -0.5V,  65535 = +0.5V    for range 0
                     // 0 = -0.05V, 65535 = +0.95V   for range 0.45
                     // 0 = -0.95V, 65535 = +0.05V   for range -0.45
                     float f = ev->mWfUADC[i][j] - wdb->GetRange();
                     if (f < -0.5)
                        f = -0.5;
                     if (f > 0.5)
                        f = 0.5;
                     unsigned short d = (unsigned short) ((f + 0.5) * 65535);
                     *(unsigned short *) p = d;
                     p += sizeof(unsigned short);
                  }
               }
            }
         }

         if (ev->mHasTDCData) {
            for (int i = 0; i < WD_N_CHANNELS; i++) {
               if (ev->mTDCChannelPresent[i]) {
                  // channel header
                  sprintf((char *) p, "T%03d", i);
                  p += 4;
                  for (int j = 0; j < 512; j++) {
                     *(unsigned char *) p = ev->mWfTDC[i][j];
                     p += sizeof(unsigned char);
                  }
               }
            }
         }

         if (ev->mHasTRGData) {
            // channel header
            sprintf((char *) p, "TRGD");
            p += 4;
            for (int j = 0; j < 512; j++) {
               *(uint64_t *) p = ev->mTrgData[j];
               p += sizeof(uint64_t);
            }
         }

         b++;
      }

      int size = p - buffer;
      n = write(li.fh, buffer, size);
      assert(n == size);
      assert(size <= buffer_size);
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

std::chrono::time_point<std::chrono::high_resolution_clock> WP::usStart()
{
   return std::chrono::high_resolution_clock::now();
}

unsigned int WP::usSince(std::chrono::time_point<std::chrono::high_resolution_clock> start) {
   auto elapsed = std::chrono::high_resolution_clock::now() - start;
   return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
}

//--------------------------------------------------------------------

void WP::Collector() {
   int status;

   if (mVerbose)
      std::cout << "Started waveform collector thread" << std::endl;

   do {

      StartNewEvent();

      do {

         status = ReceiveWfPacket();
         if (status != SUCCESS && status != TIMEOUT) {
            if (mVerbose >= 2)
               std::cout << "Abort collecting event, status = " << status << ". (time = " << usSince(mEventStartTime)
                         << "us)" << std::endl;
            if (mLogfile != "") {
               std::ofstream f;
               f.open(mLogfile, std::ios_base::app);
               f << "Abort collecting event, status = " << status << ". (time = " << usSince(mEventStartTime) << "us)"
                 << std::endl;
            }
            break; // abort loop if timeout or wrong packet etc.
         }

      } while (!IsEventValid());

      if (mLogfile != "") {
         auto it = mEvent.begin();
         auto ev = (*it);
         std::ofstream f;
         f.open(mLogfile, std::ios_base::app);
         if (status == SUCCESS)
            f << std::setfill('0') << std::setw(6) << usSince(mEventStartTime) <<
              "us All packets of event " << ev.second->mEventNumber << " received" << std::endl;
         else
            f << std::setfill('0') << std::setw(6) << usSince(mEventStartTime) <<
              "us Abort receiving of event" << std::endl;
      }

      // if all packets have been received process the event
      if (status == SUCCESS) {

         // do various calibrations
         if (!mRotateWaveform)
            UnrotateWaveforms();

         if (mCalibrateWaveform)
            CalibrateWaveforms(mEvent);

         if (li.fh != 0 || li.xml != NULL)
            SaveWaveforms();

         // debug output
         if (mLogfile != "") {
            std::ofstream f;
            f.open(mLogfile, std::ios_base::app);
            f << std::setfill('0') << std::setw(6) << usSince(mEventStartTime) <<
              "us Fully calibrated WD event" << std::endl;
            f << "==============================================================================================="
              << std::endl;
         }

         // copy event to buffer
         {
            std::lock_guard<std::mutex> lock(mEventAccessMutex);

            // always overwrite last event
            auto es = mEvent.begin();
            auto ed = mEventLast.begin();

            while (es != mEvent.end()) {
               if ((*es).second->mEventValid) {
                  *(*ed).second = *(*es).second;
               } else {
                  (*ed).second->mEventValid = false;
               }
               es++;
               ed++;
            }

            mEventNew = true;
         }
         mEventCV.notify_one();


         // debug output
         if (mVerbose >= 2)
            std::cout << "Ready to be read WD event. (time = " << usSince(mEventStartTime) << "us)" << std::endl;

         if (mLogfile != "") {
            std::ofstream f;
            f.open(mLogfile, std::ios_base::app);
            f << "Ready to be read WD event. (time = " << usSince(mEventStartTime) << "us)" << std::endl;
            f << "==============================================================================================="
              << std::endl;
         }

      } else {
         {
            std::lock_guard<std::mutex> lock(mEventAccessMutex);
            mEventNew = false;
         }
      }
   } while (1);

}

//--------------------------------------------------------------------

void WP::DoVoltageCalibrationStep() {
   if (calibProg.state == cCsFirstBoard) {
      calibProg.state = cCsFirstSample;
      calibProg.progress = 0;
      calibProg.nIter1 = 50; // primary
      calibProg.nIter2 = 50; // secondary
      calibProg.nIter3 = 50; // positive gain
      calibProg.nIter4 = 50; // negative gain
      calibProg.nIter5 = 50; // timing channels

      calibProg.nIterTotal = calibProg.nIter1 + calibProg.nIter2 +
                             calibProg.nIter3 + calibProg.nIter4 + calibProg.nIter5 + 4;
   }

   WDB *b = mWdb[calibProg.iBoard];

   if (calibProg.state == cCsFirstSample) {
      calibProg.progress = 0;
      calibProg.iIter1 = 0;
      calibProg.iIter2 = 0;
      calibProg.iIter3 = 0;
      calibProg.iIter4 = 0;
      calibProg.iIter5 = 0;
      calibProg.iIterTotal = 0;
      calibProg.state = cCsRunning;

      // make sure the sampling speed is up to date
      b->ReceiveStatusRegister(b->GetDrsSampleFreqLoc());

      // save current board settings
      b->Save();

      b->mVCalib.mCalib.sampling_frequency = b->GetDrsSampleFreqMhz();

      for (int ch = 0; ch < WD_N_CHANNELS; ch++)
         for (int bin = 0; bin < 1024; bin++) {
            b->mVCalib.mCalib.wf_offset1[ch][bin] = 0;
            b->mVCalib.mCalib.wf_offset2[ch][bin] = 0;
            b->mVCalib.mCalib.wf_calibrated[ch][bin] = 1; // move out of the window
         }

      // turn off all calibration
      mRotateWaveform = false;
      mOfsCalib1 = false;
      mOfsCalib2 = false;
      mGainCalib = false;
      mRangeCalib = false;

      // turn on square clock to correct for crosstalk
      b->SetTimingReferenceSignal(WDB::cTimingReferenceSquare);

      // disconnect channel from input
      b->SetFeMux(-1, WDB::cFeMuxCalSource);
      b->SetCalibBufferEn(true);

      // enable all DRSchannels
      b->SetDrsChTxEn(0x3FFFF);
      b->SetAdcChTxEn(0);

      // turn off zero suppression
      b->SetZeroSuprEn(false);

      // range -0.5 ... + 0.5V
      b->SetRange(0);

      // set gain 1
      b->SetFeGain(-1, 1);

      // set offset zero
      b->SetDacCalDcV(0);

      // set holdoff to meet target DAQ rate
      b->SetTriggerHoldoff(20);

      // disable external trigger
      b->SetExtAsyncTriggerEn(0);
      b->SetPatternTriggerEn(0);

      // set inter-packet delay to default value
      b->SetInterPkgDelay(1875);

      int n = calibProg.nIter1;
      n = std::max(n, calibProg.nIter2);
      n = std::max(n, calibProg.nIter3);
      n = std::max(n, calibProg.nIter4);

      calibProg.ave = new Averager(1, WD_N_CHANNELS, 1024, n);
   }

   calibProg.iIterTotal++;
   calibProg.progress = (double) calibProg.iIterTotal / calibProg.nIterTotal;

   //---- Primary Calibration ----

   if (calibProg.iIter1 < calibProg.nIter1) {
      // get one event from board
      WDEvent event(b->GetSerialNumber());
      if (!RequestEvent(b, CALIB_TIMEOUT, event))
         return;

      calibProg.iIter1++;

      for (int ch = 0; ch < WD_N_CHANNELS - 2; ch++) {
         int tc = event.mTriggerCell[ch];
         for (int bin = 0; bin < 1024; bin++) {
            // drop bins +-20 cells around trigger cell
            int dist = abs(bin - tc);
            if (dist > 1024 - 20)
               dist -= 1024;
            if (dist > 20)
               calibProg.ave->Add(0, ch, bin, event.mWfUDRS[ch][bin]);
         }
      }

      if (calibProg.iIter1 % 10 == 0) {
         for (int ch = 0; ch < WD_N_CHANNELS - 2; ch++)
            for (int bin = 0; bin < 1024; bin++)
               b->mVCalib.mCalib.wf_offset1[ch][bin] = (float) calibProg.ave->Median(0, ch, bin);

         for (int ch = 0; ch < WD_N_CHANNELS - 2; ch++)
            for (int bin = 0; bin < 1024; bin++)
               b->mVCalib.mCalib.wf_calibrated[ch][bin] =
                       event.mWfUDRS[ch][bin] - b->mVCalib.mCalib.wf_offset1[ch][bin];

         for (int ch = 16; ch < WD_N_CHANNELS ; ch++)
            for (int bin = 0; bin < 1024; bin++)
               b->mVCalib.mCalib.wf_calibrated[ch][bin] = 1; // move out of the window
      }

      // calibration finished
      if (calibProg.iIter1 == calibProg.nIter1) {
         // calibProg.ave->SaveNormalizedDistribution("wf.csv", 0);
         calibProg.ave->Reset();
      }
      return;
   }

   //---- Secondary Calibration

   if (calibProg.iIter2 < calibProg.nIter2) {

      // initialize data on first iteration
      if (calibProg.iIter2 == 0) {
         calibProg.ave->Reset();
         mRotateWaveform = true;  // rotate waveforms
         mOfsCalib1 = true;  // do 1st calibration
         b->mVCalib.SetValid(true);
      }

      // get one event from board
      WDEvent event(b->GetSerialNumber());
      if (!RequestEvent(b, CALIB_TIMEOUT, event))
         return;

      calibProg.iIter2++;

      for (int ch = 0; ch < WD_N_CHANNELS - 2; ch++)
         for (int bin = 0; bin < 1024; bin++)
            calibProg.ave->Add(0, ch, bin, event.mWfUDRS[ch][bin]);

      if (calibProg.iIter2 % 10 == 0) {
         for (int ch = 0; ch < WD_N_CHANNELS - 2; ch++)
            for (int bin = 0; bin < 1024; bin++)
               b->mVCalib.mCalib.wf_offset2[ch][bin] = (float) calibProg.ave->Median(0, ch, bin);

         for (int ch = 0; ch < WD_N_CHANNELS - 2; ch++)
            for (int bin = 0; bin < 1024; bin++)
               b->mVCalib.mCalib.wf_calibrated[ch][bin] =
                       event.mWfUDRS[ch][bin] - b->mVCalib.mCalib.wf_offset2[ch][bin];
      }
      // calibration finished
      if (calibProg.iIter2 == calibProg.nIter2)
         calibProg.ave->Reset();
      return;
   }

   //---- Positive Gain Calibration

   if (calibProg.iIter3 < calibProg.nIter3) {

      // initialize data on first iteration
      if (calibProg.iIter3 == 0) {
         calibProg.ave->Reset();
         mRotateWaveform = false; // do not rotate waveforms
         mOfsCalib1 = true;  // do 1st calibration
         mOfsCalib2 = false; // do not do 2nd calibration

         b->SetDacCalDcV(0.45);
      }

      // get one event from board
      WDEvent event(b->GetSerialNumber());
      if (!RequestEvent(b, CALIB_TIMEOUT, event))
         return;

      calibProg.iIter3++;

      for (int ch = 0; ch < WD_N_CHANNELS - 2; ch++)
         for (int bin = 0; bin < 1024; bin++)
            calibProg.ave->Add(0, ch, bin, event.mWfUDRS[ch][bin]);

      if (calibProg.iIter3 % 10 == 0) {
         for (int ch = 0; ch < WD_N_CHANNELS - 2; ch++) // exclude clock channels
            for (int bin = 0; bin < 1024; bin++)
               b->mVCalib.mCalib.wf_gain1[ch][bin] = (float) (calibProg.ave->Median(0, ch, bin) / 0.45);

         for (int ch = 0; ch < WD_N_CHANNELS - 2; ch++) {
            int tc = event.mTriggerCell[ch];
            for (int bin = 0; bin < 1024; bin++)
               b->mVCalib.mCalib.wf_calibrated[ch][bin] =
                       event.mWfUDRS[ch][bin] / b->mVCalib.mCalib.wf_gain1[ch][(bin + tc) % 1024] - 0.48;
         }
      }

      // calibration finished
      if (calibProg.iIter3 == calibProg.nIter3)
         calibProg.ave->Reset();

      return;
   }

   //---- Negative Gain Calibration

   if (calibProg.iIter4 < calibProg.nIter4) {

      // initialize data on first iteration
      if (calibProg.iIter4 == 0) {
         b->SetDacCalDcV(-0.45);
      }

      // get one event from board
      WDEvent event(b->GetSerialNumber());
      if (!RequestEvent(b, CALIB_TIMEOUT, event))
         return;

      calibProg.iIter4++;

      for (int ch = 0; ch < WD_N_CHANNELS - 2; ch++)
         for (int bin = 0; bin < 1024; bin++)
            calibProg.ave->Add(0, ch, bin, event.mWfUDRS[ch][bin]);

      if (calibProg.iIter4 % 10 == 0) {
         for (int ch = 0; ch < WD_N_CHANNELS - 2; ch++) // exclude clock channels
            for (int bin = 0; bin < 1024; bin++)
               b->mVCalib.mCalib.wf_gain2[ch][bin] = (float) (calibProg.ave->Median(0, ch, bin) / -0.45);

         for (int ch = 0; ch < WD_N_CHANNELS - 2; ch++) {
            int tc = event.mTriggerCell[ch];
            for (int bin = 0; bin < 1024; bin++)
               b->mVCalib.mCalib.wf_calibrated[ch][bin] =
                       event.mWfUDRS[ch][bin] / b->mVCalib.mCalib.wf_gain2[ch][(bin + tc) % 1024] + 0.48;
         }
      }

      // calibration finished
      if (calibProg.iIter4 == calibProg.nIter4)
         calibProg.ave->Reset();

      return;
   }

   //---- Timing channels calibration

   if (calibProg.iIter5 < calibProg.nIter5) {

      // initialize data on first iteration
      if (calibProg.iIter5 == 0) {
         // set offset zero
         b->SetDacCalDcV(0);

         // turn off square clock to get DC level
         b->SetTimingReferenceSignal(WDB::cTimingReferenceOff);

         mRotateWaveform = false;
         mOfsCalib1 = false;
         mOfsCalib2 = false;
         mGainCalib = false;
         mRangeCalib = false;
      }

      // get one event from board
      WDEvent event(b->GetSerialNumber());
      if (!RequestEvent(b, CALIB_TIMEOUT, event))
         return;

      calibProg.iIter5++;

      for (int ch = 16; ch < WD_N_CHANNELS; ch++)
         for (int bin = 0; bin < 1024; bin++)
            calibProg.ave->Add(0, ch, bin, event.mWfUDRS[ch][bin]);

      if (calibProg.iIter5 % 10 == 0) {
         for (int ch = 16; ch < WD_N_CHANNELS; ch++) // only clock channels
            for (int bin = 0; bin < 1024; bin++)
               b->mVCalib.mCalib.wf_offset1[ch][bin] = (float) calibProg.ave->Median(0, ch, bin);

         for (int ch = 0; ch < WD_N_CHANNELS - 1; ch++)
            for (int bin = 0; bin < 1024; bin++)
               b->mVCalib.mCalib.wf_calibrated[ch][bin] = 1; // move out of the window

         for (int ch = 16; ch < WD_N_CHANNELS; ch++)
            for (int bin = 0; bin < 1024; bin++)
               b->mVCalib.mCalib.wf_calibrated[ch][bin] =
                       event.mWfUDRS[ch][bin] - b->mVCalib.mCalib.wf_offset1[ch][bin];
      }

      // calibration finished
      if (calibProg.iIter5 == calibProg.nIter5) {
         delete calibProg.ave;
         calibProg.ave = NULL;
      }

      return;
   }

   mRotateWaveform = true;
   mOfsCalib1 = true;
   mOfsCalib2 = true;
   mGainCalib = true;
   mRangeCalib = false;

   // reset reference clocks
   b->SetTimingReferenceSignal(WDB::cTimingReferenceSquare);

   //---- measure offset at different ranges

   // disconnect channel from input
   b->SetFeMux(-1, WDB::cFeMuxCalSource);
   b->SetCalibBufferEn(true);

   // Range -0.45
   b->SetDacCalDcV(0);
   b->SetRange(-0.45);

   // DRS events
   b->SetDrsChTxEn(0x3FFFF);
   b->SetAdcChTxEn(0);
   WDEvent event(b->GetSerialNumber());
   RequestEvent(b, CALIB_TIMEOUT, event);
   if (!RequestEvent(b, CALIB_TIMEOUT, event))
      return;

   for (int ch = 0; ch < WD_N_CHANNELS - 2; ch++) {
      float sum = 0;
      for (int i = 10; i < 1020; i++)
         sum += event.mWfUDRS[ch][i];
      b->mVCalib.mCalib.drs_offset_range0[ch] = sum / 1010;
   }

   // ADC events
   b->SetDrsChTxEn(0);
   b->SetAdcChTxEn(0xFFFF);
   RequestEvent(b, CALIB_TIMEOUT, event);
   if (!RequestEvent(b, CALIB_TIMEOUT, event))
      return;

   for (int ch = 0; ch < WD_N_CHANNELS - 2; ch++) {
      float sum = 0;
      for (int i = 10; i < 1020; i++)
         sum += event.mWfUADC[ch][i];
      b->mVCalib.mCalib.adc_offset_range0[ch] = sum / 1010;
   }

   // Range 0
   b->SetRange(0);

   // DRS events
   b->SetDrsChTxEn(0x3FFFF);
   b->SetAdcChTxEn(0);
   RequestEvent(b, CALIB_TIMEOUT, event);
   if (!RequestEvent(b, CALIB_TIMEOUT, event))
      return;

   for (int ch = 0; ch < WD_N_CHANNELS - 2; ch++) {
      float sum = 0;
      for (int i = 10; i < 1020; i++)
         sum += event.mWfUDRS[ch][i];
      b->mVCalib.mCalib.drs_offset_range1[ch] = sum / 1010;
   }

   // ADC events
   b->SetDrsChTxEn(0);
   b->SetAdcChTxEn(0xFFFF);
   RequestEvent(b, CALIB_TIMEOUT, event);
   if (!RequestEvent(b, CALIB_TIMEOUT, event))
      return;

   for (int ch = 0; ch < WD_N_CHANNELS - 2; ch++) {
      float sum = 0;
      for (int i = 10; i < 1020; i++)
         sum += event.mWfUADC[ch][i];
      b->mVCalib.mCalib.adc_offset_range1[ch] = sum / 1010;
   }

   // Range 0.45
   b->SetRange(0.45);

   // DRS events
   b->SetDrsChTxEn(0x3FFFF);
   b->SetAdcChTxEn(0);
   RequestEvent(b, CALIB_TIMEOUT, event);
   if (!RequestEvent(b, CALIB_TIMEOUT, event))
      return;

   for (int ch = 0; ch < WD_N_CHANNELS - 2; ch++) {
      float sum = 0;
      for (int i = 10; i < 1020; i++)
         sum += event.mWfUDRS[ch][i];
      b->mVCalib.mCalib.drs_offset_range2[ch] = sum / 1010;
   }

   // ADC events
   b->SetDrsChTxEn(0);
   b->SetAdcChTxEn(0xFFFF);
   RequestEvent(b, CALIB_TIMEOUT, event);
   if (!RequestEvent(b, CALIB_TIMEOUT, event))
      return;

   for (int ch = 0; ch < WD_N_CHANNELS - 2; ch++) {
      float sum = 0;
      for (int i = 10; i < 1020; i++)
         sum += event.mWfUADC[ch][i];
      b->mVCalib.mCalib.adc_offset_range2[ch] = sum / 1010;
   }

   delete calibProg.ave;
   calibProg.ave = NULL;

   // save calibration
   b->SaveVoltageCalibration(b->GetDrsSampleFreqMhz(), mWdsDir);

   // switch to next board
   calibProg.iBoard++;
   calibProg.state = cCsFirstSample;
   calibProg.progress = 1;

   // switch back to old board settings
   b->Restore();

   if (calibProg.iBoard == calibProg.lastBoard) {
      calibProg.state = cCsInactive;
      calibProg.mode = cCmNone;

      mRangeCalib = true;
   }

   return;
}

//--------------------------------------------------------------------

int WP::AnalyzePeriod(WDEvent *event, WDB *b) {
   for (int ch = 0; ch < WD_N_CHANNELS; ch++) {
      int tc = event->mTriggerCell[ch];

      double umin = 0, umax = 0;
      for (int i1 = tc + 5; i1 < tc + 1024 - 5; i1++) {
         if (event->mWfUDRS[ch][i1 % 1024] > umax)
            umax = event->mWfUDRS[ch][i1 % 1024];
         if (event->mWfUDRS[ch][i1 % 1024] < umin)
            umin = event->mWfUDRS[ch][i1 % 1024];
      }

      if (umax - umin < 0.1)
         return -1;

      // rising edges
      for (int i1 = tc + 5; i1 < tc + 1024 - 5; i1++) {
         if (event->mWfUDRS[ch][i1 % 1024] <= 0 && event->mWfUDRS[ch][(i1 + 1) % 1024] > 0) {
            for (int i2 = i1 + 1; i2 < i1 + 1024 && i2 < tc + 1024 - 3; i2++) {
               if (event->mWfUDRS[ch][i2 % 1024] <= 0 && event->mWfUDRS[ch][(i2 + 1) % 1024] > 0) {

                  // first partial cell
                  double tPeriod = b->mTCalib.mCalib.dt[ch][i1 % 1024] *
                                   (1 / (1 - event->mWfUDRS[ch][i1 % 1024] / event->mWfUDRS[ch][(i1 + 1) % 1024]));

                  // full cells between i1 and i2
                  if (i2 < i1)
                     i2 += 1024;
                  for (int j = i1 + 1; j < i2; j++)
                     tPeriod += b->mTCalib.mCalib.dt[ch][j % 1024];

                  // second partial cell
                  tPeriod += b->mTCalib.mCalib.dt[ch][i2 % 1024] *
                             (1 / (1 - event->mWfUDRS[ch][(i2 + 1) % 1024] / event->mWfUDRS[ch][i2 % 1024]));

                  b->mTCalib.mCalib.period[ch][i1 % 1024] = (float) tPeriod;

                  break;
               }
            }
         }
      }

      // falling edges
      for (int i1 = tc + 5; i1 < tc + 1024 - 5; i1++) {
         if (event->mWfUDRS[ch][i1 % 1024] >= 0 && event->mWfUDRS[ch][(i1 + 1) % 1024] < 0) {
            for (int i2 = i1 + 1; i2 < i1 + 1024 && i2 < tc + 1024 - 3; i2++) {
               if (event->mWfUDRS[ch][i2 % 1024] >= 0 && event->mWfUDRS[ch][(i2 + 1) % 1024] < 0) {

                  // first partial cell
                  double tPeriod = b->mTCalib.mCalib.dt[ch][i1 % 1024] *
                                   (1 / (1 - event->mWfUDRS[ch][i1 % 1024] / event->mWfUDRS[ch][(i1 + 1) % 1024]));

                  // full cells between i1 and i2
                  if (i2 < i1)
                     i2 += 1024;
                  for (int j = i1 + 1; j < i2; j++)
                     tPeriod += b->mTCalib.mCalib.dt[ch][j % 1024];

                  // second partial cell
                  tPeriod += b->mTCalib.mCalib.dt[ch][i2 % 1024] *
                             (1 / (1 - event->mWfUDRS[ch][(i2 + 1) % 1024] / event->mWfUDRS[ch][i2 % 1024]));

                  b->mTCalib.mCalib.period[ch][i1 % 1024] = (float) tPeriod;

                  break;
               }
            }
         }
      }
   }

   return 1;
}

/*-----------------------------------------------------------------------------------------*/

void WP::AnalyzeTimeOffset(WDEvent *event) {

   // find rising edge in channel #0
   for (int i = 10; i < 1024 - 10; i++) {
      if (event->mWfUDRS[0][i] <= 0 && event->mWfUDRS[0][i + 1] > 0) {
         double t0 = event->mWfTDRS[0][i] + (event->mWfTDRS[0][i + 1] - event->mWfTDRS[0][i]) *
                                            (event->mWfUDRS[0][i] / (event->mWfUDRS[0][i] - event->mWfUDRS[0][i + 1]));

         for (int ch = 1; ch < WD_N_CHANNELS; ch++) {
            for (int j = 10; j < 1024 - 10; j++) {
               if (event->mWfUDRS[ch][j] <= 0 && event->mWfUDRS[ch][j + 1] > 0) {
                  double t = event->mWfTDRS[ch][j] + (event->mWfTDRS[ch][j + 1] - event->mWfTDRS[ch][j]) *
                                                     (event->mWfUDRS[ch][j] /
                                                      (event->mWfUDRS[ch][j] - event->mWfUDRS[ch][j + 1]));
                  double dt = t - t0;
                  if (ch > 15)
                     dt -= 2E-9; // timing channels have a 2 ns offset
                  if (fabs(dt) < 1E-9) {
                     calibProg.ave->Add(0, ch, 0, (float) dt);
                  }
               }
            }
         }
      }
   }
}

/*-----------------------------------------------------------------------------------------*/

void WP::CalibrateLocal(WDEvent *event, WDB *b) {
   float u1, u2, llim, ulim;

   llim = -0.35f;
   ulim = 0.35f;

   for (int ch = 0; ch < WD_N_CHANNELS; ch++) {
      int tc = event->mTriggerCell[ch];

      for (int i = tc + 5; i < tc + 1024 - 5; i++) {

         u1 = event->mWfUDRS[ch][i % 1024];
         u2 = event->mWfUDRS[ch][(i + 1) % 1024];

         // check if samples inside the limits
         if (u1 < llim || u1 > ulim || u2 < llim || u2 > ulim)
            continue;

         // test slope between previous and next cell to allow for negative cell width

         // rising edges
         if (event->mWfUDRS[ch][(i + 1024 - 1) % 1024] < event->mWfUDRS[ch][(i + 2) % 1024]) {
            calibProg.ave->Add(0, ch, i % 1024, u2 - u1);
         }

         // falling edges
         if (event->mWfUDRS[ch][(i + 1024 - 1) % 1024] > event->mWfUDRS[ch][(i + 2) % 1024]) {
            calibProg.ave->Add(0, ch, i % 1024, u1 - u2);
         }
      }

      // calculate calibration every 100 events
      if (calibProg.iIter1 % 100 == 0) {
         // average over all 1024 dU
         double sum = 0;
         double cellDV[1024];
         int sum_n = 0;

         for (int i = 0; i < 1024; i++) {
            cellDV[i] = calibProg.ave->Average(0, ch, i);
            if (cellDV[i] > 0) {
               sum += cellDV[i];
               sum_n++;
            }
         }

         /*
         if (calibProg.iIter1 == calibProg.nIter1 && ch == 0)
            calibProg.ave->SaveDistribution("dist.txt", 0, 0, -1);
         */

         sum /= sum_n;
         double dtCell = 1.0 / b->GetDrsSampleFreqMhz() * 1E-6;

         // here comes the central calculation, dT = dV/average * dtCell
         for (int i = 0; i < 1024; i++)
            if (cellDV[i] == 0)
               b->mTCalib.mCalib.dt[ch][i] = dtCell; // set default value if cell has no data
            else
               b->mTCalib.mCalib.dt[ch][i] = (float) (cellDV[i] / sum * dtCell);
      }

   }
}

/*-----------------------------------------------------------------------------------------*/

void WP::CalibrateGlobal(WDEvent *event, WDB *b) {
   double damping = 0.1f;
   double nominalPeriod = 1.0 / b->GetCalibClkFreq() / 1E6; // Period of calibration clock

   for (int ch = 0; ch < WD_N_CHANNELS; ch++) {
      int tc = event->mTriggerCell[ch];

      // rising edges
      for (int i1 = tc + 5; i1 < tc + 1024 - 5; i1++) {
         if (event->mWfUDRS[ch][i1 % 1024] <= 0 && event->mWfUDRS[ch][(i1 + 1) % 1024] > 0) {
            for (int i2 = i1 + 1; i2 < i1 + 1024 && i2 < tc + 1024 - 5; i2++) {
               if (event->mWfUDRS[ch][i2 % 1024] <= 0 && event->mWfUDRS[ch][(i2 + 1) % 1024] > 0) {

                  // first partial cell
                  double tPeriod = b->mTCalib.mCalib.dt[ch][i1 % 1024] *
                                   (1 / (1 - event->mWfUDRS[ch][i1 % 1024] / event->mWfUDRS[ch][(i1 + 1) % 1024]));

                  // full cells between i1 and i2
                  if (i2 < i1)
                     i2 += 1024;
                  for (int j = i1 + 1; j < i2; j++)
                     tPeriod += b->mTCalib.mCalib.dt[ch][j % 1024];

                  // second partial cell
                  tPeriod += b->mTCalib.mCalib.dt[ch][i2 % 1024] *
                             (1 / (1 - event->mWfUDRS[ch][(i2 + 1) % 1024] / event->mWfUDRS[ch][i2 % 1024]));

                  // calculate correction to nominal period of 10 ns as a fraction
                  float corr = (float) (nominalPeriod / tPeriod);

                  // skip big corrections (probably noise)
                  if (corr > 1.01 || corr < 0.99)
                     continue;

                  // apply damping factor
                  corr = (corr - 1) * damping + 1;

                  // distribute correction equally into bin inside the region
                  for (int j = i1 + 1; j < i2; j++)
                     b->mTCalib.mCalib.dt[ch][j % 1024] *= corr;

                  break;
               }
            }
         }
      }

      // falling edges
      for (int i1 = tc + 5; i1 < tc + 1024 - 5; i1++) {
         if (event->mWfUDRS[ch][i1 % 1024] >= 0 && event->mWfUDRS[ch][(i1 + 1) % 1024] < 0) {
            for (int i2 = i1 + 1; i2 < i1 + 1024 && i2 < tc + 1024 - 5; i2++) {
               if (event->mWfUDRS[ch][i2 % 1024] >= 0 && event->mWfUDRS[ch][(i2 + 1) % 1024] < 0) {

                  // first partial cell
                  double tPeriod = b->mTCalib.mCalib.dt[ch][i1 % 1024] *
                                   (1 / (1 - event->mWfUDRS[ch][i1 % 1024] / event->mWfUDRS[ch][(i1 + 1) % 1024]));

                  // full cells between i1 and i2
                  if (i2 < i1)
                     i2 += 1024;
                  for (int j = i1 + 1; j < i2; j++)
                     tPeriod += b->mTCalib.mCalib.dt[ch][j % 1024];

                  // second partial cell
                  tPeriod += b->mTCalib.mCalib.dt[ch][i2 % 1024] *
                             (1 / (1 - event->mWfUDRS[ch][(i2 + 1) % 1024] / event->mWfUDRS[ch][i2 % 1024]));

                  // calculate correction to nominal period of 10 ns as a fraction
                  float corr = (float) (nominalPeriod / tPeriod);

                  // skip big corrections (probably noise)
                  if (corr > 1.01 || corr < 0.99)
                     continue;

                  // apply damping factor
                  corr = (corr - 1) * damping + 1;

                  // distribute correction equally into bin inside the region
                  for (int j = i1 + 1; j < i2; j++)
                     b->mTCalib.mCalib.dt[ch][j % 1024] *= corr;

                  break;
               }
            }
         }
      }
   }
}

void saveCalib(WDB *b, const char *fn) {
   FILE *f;

   f = fopen(fn, "wt");
   for (int i = 0; i < 1024; i++)
      fprintf(f, "%lf\t%lf\n", b->mTCalib.mCalib.dt[0][i] * 1E9, b->mTCalib.mCalib.dt[1][i] * 1E9);
   fclose(f);
}

//--------------------------------------------------------------------

void WP::DoTimeCalibrationStep() {

   if (calibProg.state == cCsFirstBoard) {

      calibProg.state = cCsFirstSample;
      calibProg.nIter1 = 500;  // local calibration
      calibProg.nIter2 = 500;  // global calibration
      calibProg.nIter3 = 30;   // offset calibration
      calibProg.nIter4 = 0;

      // turn off all calibration
      mRotateWaveform = false;
      mOfsCalib1 = true;
      mOfsCalib2 = true;
      mGainCalib = true;
      mRangeCalib = true;

      mTimeCalib1 = false;
      mTimeCalib2 = false;
      mTimeCalib3 = false;
   }

   WDB *b = mWdb[calibProg.iBoard];

   if (calibProg.state == cCsFirstSample) {
      calibProg.progress = 0;
      calibProg.iIter1 = 0;
      calibProg.iIter2 = 0;
      calibProg.iIter3 = 0;
      calibProg.iIter4 = 0;
      calibProg.state = cCsRunning;

      // make sure the sampling speed is up to date
      b->ReceiveStatusRegister(b->GetDrsSampleFreqLoc());

      // save current board settings
      b->Save();

      b->mTCalib.mCalib.sampling_frequency = b->GetDrsSampleFreqMhz();

      mRotateWaveform = false;
      mTimeCalib1 = false;

      // initialize delta-t array with nominal values
      for (int ch = 0; ch < WD_N_CHANNELS; ch++)
         for (int bin = 0; bin < 1024; bin++) {
            b->mTCalib.mCalib.dt[ch][bin] = (float) (1.0 / b->GetDrsSampleFreqMhz() * 1E-6); // [s]
            b->mTCalib.mCalib.period[ch][bin] = 0;
         }

      // range -0.5 ... + 0.5V
      b->SetRange(0);

      // set gain 1
      b->SetFeGain(-1, 1);

      // set offset zero
      b->SetDacCalDcV(0);

      // turn on calibration clock
      b->SetTimingReferenceSignal(WDB::cTimingReferenceSine);

      // connect channel input to sine wave generator
      b->SetFeMux(-1, WDB::cFeMuxCalSource);

      // enable all channels
      b->SetDrsChTxEn(0x3FFFF);

      // turn off zero suppression
      b->SetZeroSuprEn(false);

      // set holdoff to minimum
      b->SetTriggerHoldoff(0);

      // disable external trigger
      b->SetExtAsyncTriggerEn(0);
      b->SetPatternTriggerEn(0);

      // set inter-packet delay to default value
      b->SetInterPkgDelay(1875);

      calibProg.ave = new Averager(1, WD_N_CHANNELS, 1024, std::max(calibProg.nIter1, calibProg.nIter2));
   }

   //---- Local Calibration ----

   if (calibProg.iIter1 < calibProg.nIter1) {

      // get one event from board
      WDEvent event(b->GetSerialNumber());
      if (calibProg.iIter1 == 0) // skip one event until clock is available
         RequestEvent(b, CALIB_TIMEOUT, event);
      if (!RequestEvent(b, CALIB_TIMEOUT, event))
         return;

      calibProg.iIter1++;

      if (AnalyzePeriod(&event, b) == -1) {
         b->Restore();
         calibProg.state = cCsInactive;
         calibProg.mode = cCmTimeError;
         return;
      }

      CalibrateLocal(&event, b);

      calibProg.progress = (double) (calibProg.iIter1 + calibProg.iIter2 + calibProg.iIter3) /
                           (calibProg.nIter1 + calibProg.nIter2 + calibProg.nIter3);

      if (calibProg.iIter1 == calibProg.nIter1) {
         calibProg.ave->Reset();
         //saveCalib(b, "_local.txt");
      }

      return;
   }

   //---- Global Calibration

   if (calibProg.iIter2 < calibProg.nIter2) {

      // get one event from board
      WDEvent event(b->GetSerialNumber());
      if (!RequestEvent(b, CALIB_TIMEOUT, event))
         return;

      calibProg.iIter2++;

      AnalyzePeriod(&event, b);
      CalibrateGlobal(&event, b);

      calibProg.progress = (double) (calibProg.iIter1 + calibProg.iIter2 + calibProg.iIter3) /
                           (calibProg.nIter1 + calibProg.nIter2 + calibProg.nIter3);

      if (calibProg.iIter2 == calibProg.nIter2) {
         calibProg.ave->Reset();
         mRotateWaveform = true;
         mTimeCalib1 = true;
         b->mTCalib.SetValid(true);
         //saveCalib(b, "_global.txt");
      }

      return;
   }

   //---- Offset Calibration

   if (calibProg.iIter3 < calibProg.nIter3) {

      // get one event from board
      WDEvent event(b->GetSerialNumber());
      if (!RequestEvent(b, CALIB_TIMEOUT, event))
         return;

      calibProg.iIter3++;

      AnalyzeTimeOffset(&event);

      calibProg.progress = (double) (calibProg.iIter1 + calibProg.iIter2 + calibProg.iIter3) /
                           (calibProg.nIter1 + calibProg.nIter2 + calibProg.nIter3);

      if (calibProg.iIter3 == calibProg.nIter3) {
         b->mTCalib.mCalib.offset[0] = 0; // by definition
         for (int ch = 1; ch < WD_N_CHANNELS; ch++)
            b->mTCalib.mCalib.offset[ch] = (float) (calibProg.ave->RobustAverage(0, ch, 0));
      }

      return;
   }

   delete calibProg.ave;
   calibProg.ave = NULL;

   b->SaveTimeCalibration(b->GetDrsSampleFreqMhz(), mWdsDir);

   // switch to next board
   calibProg.iBoard++;
   calibProg.state = cCsFirstSample;
   calibProg.progress = 1;

   // switch back to old board settings
   b->Restore();

   if (calibProg.iBoard == calibProg.lastBoard) {
      calibProg.state = cCsInactive;
      calibProg.mode = cCmNone;

      mTimeCalib1 = true;
      mTimeCalib2 = true;
      mTimeCalib3 = true;
   }
}

//--------------------------------------------------------------------

void WP::StartWaveformSaving(std::string fileName, int format, bool all, int board, int nEvents) {
   li.fileName = fileName;
   li.format = format;
   li.nRequest = nEvents;
   li.bAll = all;
   li.board = board;
   li.nLogged = 0;

   if (li.format == cLiFormatBinary) {
      if (li.fh > 0)
         close(li.fh);

      li.fh = open(li.fileName.c_str(), O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0644);
      if (li.fh < 0) {
         std::string s = "Cannot write to file \"" + li.fileName + "\": ";
         perror(s.c_str());
      }
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

bool WP::IsXMLLogging() {
   return li.xml != NULL;
}

void WP::StopLogging() {
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

VCALIB::VCALIB() {
   bValid = false; // not yet loaded
   memset(mCalib.wf_offset1, 0, sizeof(float) * 16 * 1024);
   memset(mCalib.wf_offset2, 0, sizeof(float) * 16 * 1024);
   for (int ch = 0; ch < WD_N_CHANNELS; ch++) {
      for (int bin = 0; bin < 1024; bin++) {
         mCalib.wf_gain1[ch][bin] = 1;
         mCalib.wf_gain2[ch][bin] = 1;
      }
   }
   for (int ch = 0; ch < WD_N_CHANNELS - 2; ch++) {
      mCalib.drs_offset_range0[ch] = 0.45f;
      mCalib.drs_offset_range1[ch] = 0;
      mCalib.drs_offset_range2[ch] = -0.45f;

      mCalib.adc_offset_range0[ch] = 0;
      mCalib.adc_offset_range1[ch] = 0;
      mCalib.adc_offset_range2[ch] = 0;
   }
}

void VCALIB::save(WDB *b, std::string filename) {
   std::memcpy(mCalib.version_id, "CAL2", 4);
   mCalib.sampling_frequency = b->GetDrsSampleFreqMhz();
   mCalib.temperature = b->GetTemperatureDegree();

   int fh = open(filename.c_str(), O_WRONLY | O_CREAT, 0644);
   if (fh < 0)
      throw std::runtime_error(std::string("Cannot creat file " + filename));

   int i = write(fh, &mCalib, sizeof(VCALIB_DATA));
   if (i != sizeof(VCALIB_DATA))
      throw std::runtime_error(std::string("Cannot write to file " + filename));

   close(fh);
}

void VCALIB::load(WDB *b, std::string filename) {
   bValid = false;
   int fh = open(filename.c_str(), O_RDONLY, 0644);
   if (fh > 0) {
      int size = read(fh, &mCalib, sizeof(VCALIB_DATA));
      close(fh);

      if (size != sizeof(VCALIB_DATA)) {
         std::cerr << "Invalid voltage calibration file size in " << filename << std::endl;
         return;
      }

      if (memcmp(mCalib.version_id, "CAL2", 4) != 0) {
         std::cerr << "Invalid voltage calibration file format in " << filename << std::endl;
         return;
      }

      if (fabs((float) mCalib.sampling_frequency - b->GetDrsSampleFreqMhz()) > 1) {
         std::cerr << "Warning: Voltage calibration data in " << filename << " is for "
                   << mCalib.sampling_frequency / 1000.0
                   << " GSPS, running now at "
                   << b->GetDrsSampleFreqMhz() / 1000.0 << " GSPS" << std::endl;
      }

      bValid = true;
   }
}

//--------------------------------------------------------------------

TCALIB::TCALIB() {
   bValid = false; // not yet loaded
   memset(&mCalib, 0, sizeof(mCalib));
}

void TCALIB::save(WDB *b, std::string filename) {
   std::memcpy(mCalib.version_id, "CAL2", 4);
   mCalib.sampling_frequency = b->GetDrsSampleFreqMhz();
   mCalib.temperature = b->GetTemperatureDegree();

   int fh = open(filename.c_str(), O_WRONLY | O_CREAT, 0644);
   if (fh < 0)
      throw std::runtime_error(std::string("Cannot creat file " + filename));

   int i = write(fh, &mCalib, sizeof(TCALIB_DATA));
   if (i != sizeof(TCALIB_DATA))
      throw std::runtime_error(std::string("Cannot write to file " + filename));

   close(fh);
}

void TCALIB::load(WDB *b, std::string filename) {
   bValid = false;
   int fh = open(filename.c_str(), O_RDONLY, 0644);
   if (fh > 0) {
      int size = read(fh, &mCalib, sizeof(TCALIB_DATA));
      close(fh);

      if (size != sizeof(TCALIB_DATA)) {
         std::cerr << "Invalid time calibration file size in " << filename <<  std::endl;
         return;
      }

      if (memcmp(mCalib.version_id, "CAL2", 4) != 0) {
         std::cerr << "Invalid time calibration file format in " << filename << std::endl;
         return;
      }

      if (fabs((float) mCalib.sampling_frequency - b->GetDrsSampleFreqMhz()) > 1) {
         std::cerr << "Error: Time calibration data in " << filename << " is for "
                   << mCalib.sampling_frequency / 1000.0
                   << " GSPS, running now at "
                   << b->GetDrsSampleFreqMhz() / 1000.0 << " GSPS" << std::endl;
         return;
      }

      bValid = true;
   }
}

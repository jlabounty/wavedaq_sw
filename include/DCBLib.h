//
//  DCBLib.h
//  WaveDAQ DCB Library Header File
//
//  Created by Stefan Ritt on 30 Aug 2019
//
//  Naming convention: mXxx for member variables
//                     gXxx for global (static) variables
//                     kXxx for constants
//
//

#ifndef __dcblib_h__
#define __dcblib_h__

#include "WDBReg.h"

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <map>
#include "averager.h"
#include "mxml.h"

#define SUCCESS        1

//--------------------------------------------------------------------

// Data Concentrator Board class. Interface functions to all WDB registers
class DCB: public WDBREG {
   std::string      mDCBName;
   unsigned char    mEthAddrAscii[16];
   unsigned char    mEthAddrBin[16];
   bool             mVerbose;
   std::string      mLogfile;
   bool             mSendBlocked;
   int              mReceiveTimeoutMs;

   unsigned int     creg[REG_NR_OF_CTRL_REGS];
   unsigned int     sreg[REG_NR_OF_STAT_REGS];
   
   static int       gASCIISocket;
   static int       gBinSocket;
   static unsigned short udpSequenceNumber;

   void             WriteUDP(unsigned int ofs, std::vector<unsigned int> data);
   std::vector<unsigned int> ReadUDP(unsigned int ofs, unsigned int len);

public:
   
   // constructor
   DCB(std::string name, bool verbose = false);

   const unsigned int cRequiredRegLayoutCompatLevel = 8;
   const unsigned int cRequiredFwCompatLevel = 4;
   const int cDefaultReceiveTimeoutMs = 100;

   // register functions, overload pure virtual functions from WDBREG
   void SetRegMask(unsigned int rofs, unsigned int mask, unsigned int ofs, unsigned int v);
   unsigned int BitExtractStatus(unsigned int rofs, unsigned int mask, unsigned int ofs);
   unsigned int BitExtractControl(unsigned int rofs, unsigned int mask, unsigned int ofs);
   
   // interface functions
   void SetVerbose(int verbose) { mVerbose = verbose; }
   int IsVerbose() { return mVerbose; }
   void SetLogFile(std::string logfile) { mLogfile = logfile; }
   void Connect();
   void SetDestinationPort(int port);
   void ReceiveControlRegisters(unsigned int index=0, unsigned int nReg=REG_NR_OF_CTRL_REGS);
   void ReceiveStatusRegisters(unsigned int index=0, unsigned int nReg=REG_NR_OF_STAT_REGS);
   void ReceiveStatusRegister(int ofs);
   void SendControlRegisters();
   void PrintVersion();
   bool GetSendBlock() { return mSendBlocked; }
   void SetSendBlock(bool flag) { mSendBlocked = flag; }

   // setter & getter ----------
   std::string GetName() { return mWDBName; }
   int GetReceiveTimeoutMs() { return mReceiveTimeoutMs; };
   void SetReceiveTimeoutMs(int to) { mReceiveTimeoutMs = to; };
   
   // high level status registers
   std::string GetFwBuild();
   std::string GetHwVersion();
   float GetTemperatureDegree(bool refresh = true);
   unsigned int GetPllLock(bool refresh = true);
};

//--------------------------------------------------------------------

// linux and MAC specific things
#if defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#define O_BINARY 0
#define sleep_ms(x) usleep(x*1000)
#endif // __linux__ || __APLE__

// Windows specific things
#if defined(_WIN32)
#include <windows.h>
#define sleep_ms(x) Sleep(x)
#endif // _WIN32

/* Byte and Word swapping big endian <-> little endian */
#define SWAP_UINT16(x) (((x) >> 8) | ((x) << 8))
#define SWAP_UINT32(x) (((x) >> 24) | \
                       (((x) & 0x00FF0000) >> 8) | \
                       (((x) & 0x0000FF00) << 8) | \
                       ((x) << 24))
#define SWAP_UINT64(x) (((uint64_t)(x) << 56) | \
                       (((uint64_t)(x) << 40) & 0xff000000000000ULL) | \
                       (((uint64_t)(x) << 24) & 0xff0000000000ULL) | \
                       (((uint64_t)(x) << 8)  & 0xff00000000ULL) | \
                       (((uint64_t)(x) >> 8)  & 0xff000000ULL) | \
                       (((uint64_t)(x) >> 24) & 0xff0000ULL) | \
                       (((uint64_t)(x) >> 40) & 0xff00ULL) | \
                       ((uint64_t)(x)  >> 56))
#endif /* defined(__wdblib_h__) */

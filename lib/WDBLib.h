//
//  WDBLib.h
//  WaveDAQ Library Header File
//
//  Created by Stefan Ritt on 31 Jan 2017
//
//  Naming convention: mXxx for member variables
//                     gXxx for global (static) variables
//                     kXxx for constants
//
//

#ifndef __wdblib_h__
#define __wdblib_h__

#include <string>

#include "register_map.h"

//--------------------------------------------------------------------

typedef struct {
   char             version_id[4];
   unsigned int     crc;
   float            sampling_frequency;
   float            temperature;
   float            wf_offset1[16][1024];
   float            wf_offset2[16][1024];
   float            wf_gain1[16][1024];
   float            wf_gain2[16][1024];
   float            drs_offset_range0[16];
   float            drs_offset_range1[16];
   float            drs_offset_range2[16];
   float            adc_offset_range0[16];
   float            adc_offset_range1[16];
   float            adc_offset_range2[16];
} VCALIB_DATA;

class vcalib {
   VCALIB_DATA      fCalib;
   
public:
   vcalib();
   void save();
   void load();
};

//--------------------------------------------------------------------

typedef struct {
   char             version_id[4];
   unsigned int     crc;
   float            sampling_frequency;
   float            temperature;
   float            dt[16][1024];
   float            period[16][1024];
   float            offset[16];
} TCALIB_DATA;

class tcalib {
   TCALIB_DATA      fCalib;
   
public:
   tcalib();
   void save();
   void load();
};

//--------------------------------------------------------------------

class WDB {
   std::string      mName;
   unsigned char    mEthAddr[16];

   unsigned int     creg[REG_CRC32_REG_BANK_OFFSET/4+1];
   unsigned int     sreg[REG_ADC_01_CLK_MOD_FLAG_OFFSET/4+1];
   
   static int       gServerPort;
   static int       gDataSocket;
   static int       gCmdSocket;

   std::string      SendReceive(std::string str, int timeout_ms = 100);
   void             Send(std::string str, int timeout_ms = 100);

public:
   
   // constructor
   WDB(std::string name) {
      mName = name;
   }

   // setter & getter
   std::string getName() { return mName; }
   
   // interface functions
   void Connect();
   void ReceiveControlRegisters();
   void ReceiveStatusRegisters();
   
   unsigned int GetSerialNumber();
   unsigned int GetSlotId();
   unsigned int GetCrateId();
   unsigned int GetProtocolVersion();
   unsigned int GetBufferCtrl();
   unsigned int GetTcaCtrl();
   unsigned int GetClkDivAdcDrs();
   unsigned int GetClkSelDaq();
   unsigned int GetClkSelExt();
   unsigned int GetExtClkFreq();
   unsigned int GetLocalClkFreq();
   unsigned int GetDacRofs();
   unsigned int GetDacOfs();
   unsigned int GetDacCalDc();
   unsigned int GetDacPulseAmp();
   unsigned int GetDacPczLevel();
   float GetDacTlevel(int chn);
   unsigned int GetFrontend(int chn);
   unsigned int GetLmk(int r);
   unsigned int GetTriggerOutPulseLength();
   unsigned int GetTriggerEnable();
   unsigned int GetTriggerFallingEdge();
   unsigned int GetTriggerCfgExtOr();
   unsigned int GetTriggerCfgExtAnd();
   unsigned int GetTriggerDelayEnable();
   unsigned int GetTriggerDelay();
   unsigned int GetTriggerCompMask();
   unsigned int GetTriggerCfgOr();
   unsigned int GetTriggerCfgAnd();
   unsigned int GetTriggerLocalScheme();
   unsigned int GetTriggerBackplaneScheme(int chn);
   unsigned int GetTriggerPatternEnLocal();
   unsigned int GetTriggerPatternEnBackplane(int chn);
   unsigned int GetTriggerPattern(int chn);
   unsigned int GetCrc32RegBank();
   std::string GetFwBuild();
   std::string GetHwVersion();
   
   void SetRegMask(unsigned int ofs, unsigned int mask, unsigned int v);
   void SetDacRofs(unsigned int v);
   void SetDacOfs(unsigned int v);
   void SetDacCalDc(unsigned int v);
   void SetDacPulseAmp(unsigned int v);
   void SetDacPczLevel(unsigned int v);
   void SetDacTlevel(int chn, float v);
   void SetFrontend(int chn, unsigned int v);
   void SetLmk(int r, unsigned int v);
   void SetTriggerOutPulseLength(unsigned int v);
   void SetTriggerEnable(unsigned int v);
   void SetTriggerFallingEdge(unsigned int v);
   void SetTriggerCfgExtOr(unsigned int v);
   void SetTriggerCfgExtAnd(unsigned int v);
   void SetTriggerDelayEnable(unsigned int v);
   void SetTriggerDelay(unsigned int v);
   void SetTriggerCompMask(unsigned int v);
   void SetTriggerCfgOr(unsigned int v);
   void SetTriggerCfgAnd(unsigned int v);
   void SetTriggerLocalScheme(unsigned int v);
   void SetTriggerBackplaneScheme(int chn, unsigned int v);
   void SetTriggerPatternEnLocal(unsigned int v);
   void SetTriggerPatternEnBackplane(int chn, unsigned int v);
   void SetTriggerPattern(int chn, unsigned int v);
};

//--------------------------------------------------------------------

// linux and MAC specific things
#if defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#define sleep(x) usleep(x*1000)
#endif // __linux__ || __APLE__

// Windows specific things
#if defined(_WIN32)
#include <windows.h>
#define sleep(x) Sleep(x)
#endif // _WIN32

/* Byte and Word swapping big endian <-> little endian */
#define SWAP_UINT16(x) (((x) >> 8) | ((x) << 8))
#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))

#endif /* defined(__wdblib_h__) */

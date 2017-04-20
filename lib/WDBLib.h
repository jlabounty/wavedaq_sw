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

#include "register_map_wd2.h"

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

   unsigned int     creg[WD2_REG_CRC32_REG_BANK_OFS/4+1];
   unsigned int     sreg[WD2_REG_ADC_01_CLK_MOD_FLAG_OFS/4+1];
   
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
   void ReceiveStatusRegister(int ofs);
   void SetRegMask(unsigned int rofs, unsigned int mask, unsigned int ofs, unsigned int v);

   // status registers
   std::string GetFwBuild();
   std::string GetHwVersion();
   unsigned int GetProtocolVersion();
   unsigned int GetSerialNumber();
   float GetTemperature();
   bool IsFlashSelect();
   bool IsBoardSelect();
   bool IsSerialBusy();
   bool IsSysBusy();
   bool IsWDBBusy();
   bool IsHvBoardPlugged();
   bool IsBackplanePlugged();
   unsigned int GetExtPllLck();
   bool IsExtPllLck();
   unsigned int GetIntPllLck();
   bool IsIntPllLck();
   unsigned int GetDrsSampleFreq();
   unsigned int GetAdcSampleFreq();
   unsigned int GetAdcInfo();
   
   void GetScalers(std::vector<unsigned long> &s);

   unsigned int GetCompChannelStatus();
   unsigned int GetLastEventNumber();
   unsigned int GetTriggerBusParityErrorCount();
   unsigned int GetTriggerBusType();
   unsigned int GetTriggerBusNumber();

   // control registers
   unsigned int GetCrateId();
   void SetCrateId(unsigned int value);
   unsigned int GetSlotId();
   void SetSlotId(unsigned int value);
   unsigned int GetValidDelayADC();
   void SetValidDelayADC(unsigned int value);
   unsigned int GetDAQDataPhase();
   void SetDAQDataPhase(unsigned int value);
   bool IsCompPowerEnable();
   void SetCompPowerEnable(bool value);
   unsigned int GetReadoutSrcSel();
   void SetReadoutSrcSel(unsigned int value);
   unsigned int GetDRSReadoutMode();
   void SetDRSReadoutMode(unsigned int value);
   bool IsDRSWaveContinous();
   void SetDRSWaveContinous(bool value);
   
   void TrgDRSConfigure();
   void TrgDAQSoft();
   void TrgDAQReinit();
   bool IsDAQNormal();
   
   void SetDAQNormal(bool value);
   bool IsDAQSingle();
   void SetDAQSingle(bool value);
   unsigned int GetDRS0TimingRefSel();
   void SetDRS0TimingRefSel(unsigned int value);
   unsigned int GetDRS1TimingRefSel();
   void SetDRS1TimingRefSel(unsigned int value);
   bool IsTimingCalibBufferEnable();
   void SetTimingCalibBufferEnable(bool value);
   bool IsTimingCalibSignalEnable();
   void SetTimingCalibSignalEnable(bool value);
   unsigned int GetDAQClkSrcSel();
   void SetDAQClkSrcSel(unsigned int value);
   unsigned int GetExtClkInSel();
   void SetExtClkInSel(unsigned int value);
   unsigned int GetExtClkFreq();
   unsigned int GetLocalClkFreq();
   unsigned int GetDRS1ChnTxEnable();
   void SetDRS1ChnTxEnable(unsigned int value);
   unsigned int GetDRS0ChnTxEnable();
   void SetDRS0ChnTxEnable(unsigned int value);
   unsigned int GetDRSControl();
   void SetDRSControl(unsigned int value);
   unsigned int GetDataDestination();
   void SetDataDestination(unsigned int value);
   unsigned int GetDCBSerdesTrain();
   void SetDCBSerdesTrain(unsigned int value);
   unsigned int GetTCBSerdesTrain();
   void SetTCBSerdesTrain(unsigned int value);
   unsigned int GetInterPacketDelay();
   void SetInterPacketDelay(unsigned int value);
   
   void ResetDAQPLL();
   void ResetDCBOserdesPLL();
   void ResetDCBOserdesIF();
   void ResetTCBOserdesPLL();
   void ResetTCBOserdesIF();
   void ResetScaler();
   void ResetTriggerParityErrorCounter();
   void LMKSyncLocal();
   void ResetADCIF();
   void ResetPackager();
   void ResetEventCounter();
   void ResetDRSControlFSM();
   void ReconfigureFPGA();
   
   void ApplyDRSSettings();
   void ApplyDACSettings();
   void ApplyFrontendSettings();
   void ApplyControlSettings();
   void ApplyADCSettings();
   void ApplyLMKSettings();

   unsigned int GetDacRofs();
   void SetDacRofs(unsigned int v);
   unsigned int GetDacOfs();
   void SetDacOfs(unsigned int v);
   unsigned int GetDacCalDc();
   void SetDacCalDc(unsigned int v);
   unsigned int GetDacPulseAmp();
   void SetDacPulseAmp(unsigned int v);
   unsigned int GetDacPZCLevel();
   void SetDacPZCLevel(unsigned int v);
   unsigned int GetDacBias();
   void SetDacBias(unsigned int v);
   float GetDacTlevel(int chn);
   void SetDacTlevel(int chn, float v);

   unsigned int GetFEPZC(int chn);
   void SetFEPZC(int chn, unsigned int v);
   unsigned int GetFEAmp2Comp(int chn);
   void SetFEAmp2Comp(int chn, unsigned int v);
   unsigned int GetFEAmp2Enable(int chn);
   void SetFEAmp2Enable(int chn, unsigned int v);
   unsigned int GetFEAmp1Comp(int chn);
   void SetFEAmp1Comp(int chn, unsigned int v);
   unsigned int GetFEAmp1Enable(int chn);
   void SetFEAmp1Enable(int chn, unsigned int v);
   unsigned int GetFEAttenuation(int chn);
   void SetFEAttenuation(int chn, unsigned int v);
   unsigned int GetFEMux(int chn);
   void SetFEMux(int chn, unsigned int v);

   unsigned int GetLMK(int reg);
   void SetLMK(int reg, unsigned int v);

   // ADC configuration intentionally skipped ...
   
   unsigned int GetTriggerPulseLength();
   void SetTriggerShaperEnable(bool v);
   bool IsTriggerShaperEnable();
   void SetTriggerPulseLength(unsigned int v);
   bool IsTriggerEnable();
   void SetTriggerEnable(bool v);
   bool IsTriggerFallingEdge();
   void SetTriggerFallingEdge(bool v);
   bool IsTriggerExternalOr();
   void SetTriggerExternalOr(bool v);
   bool IsTriggerExternalAnd();
   void SetTriggerExternalAnd(bool v);
   bool IsTriggerDelayEnable();
   void SetTriggerDelayEnable(bool v);
   unsigned int GetTriggerDelay();
   void SetTriggerDelay(unsigned int v);
   unsigned int GetTriggerComparatorMask();
   void SetTriggerComparatorMask(unsigned int v);
   unsigned int GetTriggerCfgOr();
   void SetTriggerCfgOr(unsigned int v);
   unsigned int GetTriggerCfgAnd();
   void SetTriggerCfgAnd(unsigned int v);
   unsigned int GetTriggerLocalScheme();
   void SetTriggerLocalScheme(unsigned int v);
   unsigned int GetTriggerBackplaneScheme(int chn);
   void SetTriggerBackplaneScheme(int chn, unsigned int v);
   unsigned int GetTriggerPatternEnLocal();
   void SetTriggerPatternEnLocal(unsigned int v);
   unsigned int GetTriggerPatternEnBackplane(int chn);
   void SetTriggerPatternEnBackplane(int chn, unsigned int v);
   unsigned int GetTriggerPattern(int chn);
   void SetTriggerPattern(int chn, unsigned int v);
   unsigned int GetCrc32RegBank();
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

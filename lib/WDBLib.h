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

#include "register_map_wd2.h"

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

#define WD_N_CHANNELS 18

//--------------------------------------------------------------------

#pragma pack(1) // byte-level alignement for frame header

typedef struct {
   unsigned char  protocol_version;
   unsigned char  board_version;
   unsigned short board_id;
   unsigned char  crate_id;
   unsigned char  slot_id;
   unsigned char  adc_and_channel_info;
   unsigned char  segment_and_package_type;
   unsigned int   event_number;
   unsigned short sampling_frequency;
   unsigned short payload_length;
   unsigned short trigger_number;
   unsigned short drs0_trigger_cell;
   unsigned short drs1_trigger_cell;
   unsigned short trigger_type;
   unsigned short temperature;
   unsigned int   reserved;
   unsigned short packet_sequence_number;
} WD2_FRAME_HEADER;

#pragma pack() // reset alignment to default value

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

class WDEvent {
public:
   
   unsigned short   mBoardId;
   unsigned short   mCrateId;
   unsigned short   mSlotId;
   unsigned int     mEventNumber;
   unsigned short   mSamplingFrequency;
   unsigned short   mTriggerNumber;
   int              mTriggerCell[2];
   unsigned short   mTriggerType;
   float            mTemperature;
   bool             mWFTypeADC;
   
   float            mWfU[WD_N_CHANNELS][1024];
   float            mWfT[WD_N_CHANNELS][1024];
   
   WDEvent(int boardId) { mBoardId = boardId; };

   void             SetEventHeaderInfo(WD2_FRAME_HEADER *);
};

//--------------------------------------------------------------------

template <class T> class tqueue {
   std::mutex mutex;
   std::condition_variable full, empty;
   std::queue<T> queue;
   
   int mSize;
   
public:
   tqueue(int size) { mSize = size; };
   ~tqueue() {};
   
   void push(T e) {
      std::unique_lock<std::mutex> lock(mutex);
      while (queue.size() > mSize) {
         //std::cout << "producer waiting" << std::endl;
         full.wait(lock);
      }
      queue.push(e);
      empty.notify_one();
      lock.unlock();
   }
   T pop(int timeout = 0) {
      auto start = std::chrono::system_clock::now();
      std::unique_lock<std::mutex> lock(mutex);
      while (queue.empty()) {
         //std::cout << "consumer waiting" << std::endl;
         if (timeout == 0)
            empty.wait(lock); // this is twice faster on MacOS
         else
            empty.wait_for(lock, std::chrono::milliseconds(timeout));
         if (std::chrono::system_clock::now() > start + std::chrono::milliseconds(timeout))
            break;
      }
      if (queue.empty())
         return nullptr;
      T e = queue.front();
      queue.pop();
      full.notify_one();
      lock.unlock();
      return e;
   }
   size_t size() { return queue.size(); }
};

//--------------------------------------------------------------------

class WDEventRequest {
   unsigned short   mBoardId;
   bool             mWfValid[WD_N_CHANNELS][2];
   unsigned int     mChannelMask;
 
public:
   WDEventRequest(int boardId) {
      mBoardId = boardId;
      for (int i=0 ; i<WD_N_CHANNELS ; i++) {
         mWfValid[i][0] = false;
         mWfValid[i][1] = false;
      }
      mChannelMask = 0xFFFF;
   } ;
   
   int              GetBoardId() { return mBoardId; }
   void             SetWfValid(int channel, int segment, bool v) { mWfValid[channel][segment] = v; }
   bool             IsWfValid();
};

//--------------------------------------------------------------------

// waveform processor (waveform decoding, calibration, saving, ...
class WP {
   static int       gDataSocket;
   static int       gServerPort;

   bool             mVerbose;
   bool             mDemoMode;
  
   bool             mRotateWaveform;
   bool             mOfsCalib1;
   bool             mOfsCalib2;
   bool             mGainCalib;
   bool             mRangeCalib;
   bool             mTimeCalib1;
   bool             mTimeCalib2;
   bool             mTimeCalib3;
   bool             mRemoveSpikes;
   
   int              mPacketsReceived;
   int              mCurrentEvent;
   
   std::thread      mThreadCollector;
   void Collector();
   std::thread SpawnCollectorThread() {
      return std::thread([=] { Collector(); });
   };
   
   bool             mNewEvent;
   std::vector<WDEventRequest *> mEventRequest;
   std::vector<WDEvent *> mEvent;
   
   tqueue<std::vector<WDEvent *> *> *mTqueue;
   
   void             InvalidateAllWf();
   void             ReceiveWfPacket();
   bool             AllPacketsReceived();
   void             RotateWaveforms();
   void             CalibrateWaveforms();
   
public:
   
   // constructor
   WP(bool verbose = false, bool demo = false);
   
   // setter & getter
   int GetDataSocket() { return gDataSocket; }
   int GetServerPort() { return gServerPort; }
   bool IsVerbose() { return mVerbose; }
   bool IsDemoMode() { return mDemoMode; }
   bool IsRotateWaveform() { return mRotateWaveform;}
   bool IsOfsCalib1() { return mOfsCalib1;}
   bool IsOfsCalib2() { return mOfsCalib2;}
   bool IsGainCalib() { return mGainCalib;}
   bool IsRangeCalib() { return mRangeCalib;}
   bool IsTimeCalib1() { return mTimeCalib1;}
   bool IsTimeCalib2() { return mTimeCalib2;}
   bool IsTimeCalib3() { return mTimeCalib3;}
   bool IsRemoveSpikes() { return mRemoveSpikes; }
   std::vector<WDEvent *>* GetEvent(int timeout) { return mTqueue->pop(timeout); }

   void SetRotateWaveform(bool f) { mRotateWaveform = f; }
   void SetOfsCalib1(bool f) { mOfsCalib1 = f; }
   void SetOfsCalib2(bool f) { mOfsCalib2 = f; }
   void SetGainCalib(bool f) { mGainCalib = f; }
   void SetRangeCalib(bool f) { mRangeCalib = f; }
   void SetTimeCalib1(bool f) { mTimeCalib1 = f; }
   void SetTimeCalib2(bool f) { mTimeCalib2 = f; }
   void SetTimeCalib3(bool f) { mTimeCalib3 = f; }
   void SetRemoveSpikes(bool f) { mRemoveSpikes = f; }
   
   void AddEventRequest(int boardID);
   void RemoveEventRequest(int boardID);
   
};

//--------------------------------------------------------------------

// WaveDREAM board class. Interface functions to all WDB registers
class WDB {
   std::string      mName;
   unsigned char    mEthAddrAscii[16];
   unsigned char    mEthAddrBin[16];
   bool             mVerbose;
   bool             mDemoMode;

   unsigned int     creg[WD2_REG_CRC32_REG_BANK_OFS/4+1];
   unsigned int     sreg[WD2_REG_ADC_01_CLK_MOD_FLAG_OFS/4+1];
   
   static int       gASCIISocket;
   static int       gBinSocket;
   static unsigned short udpSequenceNumber;

   std::string      SendReceiveUDP(std::string str, int timeout_ms = 100);
   void             SendUDP(std::string str, int timeout_ms = 100);

   void             WriteUDP(unsigned int ofs, std::vector<unsigned int> data, int timeout_ms = 250);
   std::vector<unsigned int> ReadUDP(unsigned int ofs, unsigned int len, int timeout_ms = 250);

   float            mFEGain;

public:
   
   // constructor
   WDB(std::string name, bool verbose = false) {
      mName = name;
      mVerbose = verbose;
      mDemoMode = (name == "demo");
   }

   // constants
   static const int cReadoutSrcDrs = 0x01;
   static const int cReadoutSrcAdc = 0x02;
   static const int cReadoutSrcTdc = 0x04;

   // interface functions
   void SetVerbose(bool verbose) { mVerbose = verbose; }
   void Connect(int port);
   void ReceiveControlRegisters(unsigned int index=0, unsigned int nReg=REG_NR_OF_CTRL_REGS);
   void ReceiveStatusRegisters(unsigned int index=0, unsigned int nReg=REG_NR_OF_STAT_REGS);
   void ReceiveStatusRegister(int ofs);
   void SetRegMask(unsigned int rofs, unsigned int mask, unsigned int ofs, unsigned int v, bool send=true);
   void PrintVersion();

   // setter & getter ----------
   std::string GetName() { return mName; }

   // status registers
   std::string GetFwBuild();
   std::string GetHwVersion();
   unsigned int GetProtocolVersion();
   unsigned int GetSerialNumber();
   float GetTemperature(bool refresh = true);
   bool IsFlashSelect();
   bool IsBoardSelect();
   bool IsSerialBusy();
   bool IsSysBusy();
   bool IsWDBBusy();
   bool IsHvBoardPlugged();
   bool IsBackplanePlugged();
   unsigned int GetExtPllLck(bool refresh = true);
   bool IsExtPllLck(bool refresh = true);
   unsigned int GetIntPllLck(bool refresh = true);
   bool IsIntPllLck(bool refresh = true);
   unsigned int GetDrsSampleFreq();
   void SetDrsSampleFreq(unsigned int f);
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
   unsigned int GetDaqDataPhase();
   void SetDaqDataPhase(unsigned int value);
   bool IsCompPowerEnable();
   void SetCompPowerEnable(bool value);
   unsigned int GetReadoutSrcSel();
   void SetReadoutSrcSel(unsigned int value);
   unsigned int GetDRSReadoutMode();
   void SetDRSReadoutMode(unsigned int value);
   bool IsDRSWaveContinous();
   void SetDRSWaveContinous(bool value);
   
   void TrgDRSConfigure();
   void TrgDAQSoft(bool value);
   void TrgDAQReinit();
   bool IsDAQNormal();
   
   void SetDaqNormal(bool value);
   bool IsDaqSingle();
   void SetDaqSingle(bool value);
   void StartDaqSingle();
   unsigned int GetDrs0TimingRefSel();
   void SetDrs0TimingRefSel(unsigned int value);
   unsigned int GetDrs1TimingRefSel();
   void SetDrs1TimingRefSel(unsigned int value);
   bool IsCalibBufferEnable();
   void SetCalibBufferEnable(bool value);
   bool IsTimingCalibSignalEnable();
   void SetTimingCalibSignalEnable(bool value);
   unsigned int GetDaqClkSrcSel();
   void SetDaqClkSrcSel(unsigned int value);
   unsigned int GetExtClkInSel();
   void SetExtClkInSel(unsigned int value);
   unsigned int GetExtClkFreq();
   unsigned int GetLocalClkFreq();
   unsigned int GetDrs1ChnTxEnable();
   void SetDrs1ChnTxEnable(unsigned int value);
   unsigned int GetDrs0ChnTxEnable();
   void SetDrs0ChnTxEnable(unsigned int value);
   unsigned int GetDrsControl();
   void SetDrsControl(unsigned int value);
   unsigned int GetDataDestination();
   void SetDataDestination(unsigned int value);
   unsigned int GetDCBSerdesTrain();
   void SetDCBSerdesTrain(unsigned int value);
   unsigned int GetTcbSerdesTrain();
   void SetTcbSerdesTrain(unsigned int value);
   unsigned int GetInterPacketDelay();
   void SetInterPacketDelay(unsigned int value);
   
   void ResetDaqPll();
   void ResetDcbOserdesPll();
   void ResetDcbOserdesIf();
   void ResetTcbOserdesPll();
   void ResetTcbOserdesIf();
   void ResetScaler();
   void ResetTriggerParityErrorCounter();
   void LmkSyncLocal();
   void ResetAdcIf();
   void ResetPackager();
   void ResetEventCounter();
   void ResetDrsControlFsm();
   void ReconfigureFpga();
   
   void ApplyDrsSettings();
   void ApplyDacSettings();
   void ApplyFrontendSettings();
   void ApplyControlSettings();
   void ApplyAdcSettings();
   void ApplyLmkSettings();

   float GetDacRofsV();
   void SetDacRofsV(float v);
   float GetDacOfsV();
   void SetDacOfsV(float v);
   float GetDacCalDcV();
   void SetDacCalDcV(float v);
   float GetDacPulseAmpV();
   void SetDacPulseAmpV(float v);
   float GetDacPZCLevelV();
   void SetDacPZCLevelV(float v);
   int GetDacPZCLevelN();
   void SetDacPZCLevelN(int n);
   float GetDacBiasV();
   void SetDacBiasV(float v);
   float GetDacTriggerLevelV(int chn);
   void SetDacTriggerLevelV(int chn, float v);

   bool IsFePzc(int chn);
   void SetFePzc(int chn, bool v);
   unsigned int GetFeAmp2Comp(int chn);
   void SetFeAmp2Comp(int chn, unsigned int v);
   unsigned int GetFeAmp2Enable(int chn);
   void SetFeAmp2Enable(int chn, unsigned int v);
   unsigned int GetFeAmp1Comp(int chn);
   void SetFeAmp1Comp(int chn, unsigned int v);
   unsigned int GetFeAmp1Enable(int chn);
   void SetFeAmp1Enable(int chn, unsigned int v);
   unsigned int GetFeAttenuation(int chn);
   void SetFeAttenuation(int chn, unsigned int v);
   unsigned int GetFeMux(int chn);
   void SetFeMux(int chn, unsigned int v);

   float GetFeGain(int chn);
   void SetFeGain(int chn, float v);

   unsigned int GetLmk(int reg);
   void SetLmk(int reg, unsigned int v);

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
   
   // hihg level methods ----------
   unsigned int GetTriggerDelayNs();
   void SetTriggerDelayNs(unsigned int ns);
   
   void SetRange(float r);
   float GetRange();
   
   void RequestEvent();
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

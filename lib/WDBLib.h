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
#include "averager.h"
#include "mxml.h"

#define WD_N_CHANNELS 18

class WDB;

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
   unsigned short   sampling_frequency;
   float            temperature;
   float            wf_offset1[18][1024];
   float            wf_offset2[18][1024];
   float            wf_gain1[18][1024];
   float            wf_gain2[18][1024];
   float            drs_offset_range0[16];
   float            drs_offset_range1[16];
   float            drs_offset_range2[16];
   float            adc_offset_range0[16];
   float            adc_offset_range1[16];
   float            adc_offset_range2[16];
} VCALIB_DATA;

class VCALIB {
   bool             bValid;

public:
   VCALIB_DATA      mCalib;
   VCALIB();
   void SetValid(bool f) { bValid = f; }
   bool IsValid() { return bValid; }
   int  GetSamplingFrequency() { return mCalib.sampling_frequency; }
   void save(WDB *b, std::string filename);
   void load(WDB *b, std::string filename);
};

//--------------------------------------------------------------------

typedef struct {
   char             version_id[4];
   unsigned int     crc;
   float            sampling_frequency;
   float            temperature;
   float            dt[18][1024];
   float            period[18][1024];
   float            offset[18];
} TCALIB_DATA;

class TCALIB {
   bool             bValid;

public:
   TCALIB_DATA      mCalib;
   TCALIB();
   void SetValid(bool f) { bValid = f; }
   bool IsValid() { return bValid; }
   int  GetSamplingFrequency() { return mCalib.sampling_frequency; }
   void save(WDB *b, std::string filename);
   void load(WDB *b, std::string filename);
};

//--------------------------------------------------------------------

typedef struct {
   int            mode;
   int            state;
   double         progress;
   int            nBoard;
   int            iBoard;
   int            nIter1;
   int            iIter1;
   int            nIter2;
   int            iIter2;
   int            nIter3;
   int            iIter3;
   int            nIter4;
   int            iIter4;
   Averager       *ave;
   int            phase;
} CALIB_PROGRESS;

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
   
   bool             mVCalibrated;
   bool             mTCalibrated;
   
   WDEvent(int boardId) { mBoardId = boardId; };

   void             SetEventHeaderInfo(WD2_FRAME_HEADER *);
};

//--------------------------------------------------------------------

template <class T> class tqueue {
   std::mutex mutex;
   std::condition_variable full, empty;
   std::queue<T> queue;
   
   int mSize;
   bool mWait;
   
public:
   tqueue(int size, bool wait=true) { mSize = size; mWait = wait; };
   ~tqueue() {};
   
   void push(T e) {
      std::unique_lock<std::mutex> lock(mutex);
      if (!mWait && queue.size() >= mSize) {
         return;
      }
      while (queue.size() >= mSize) {
         //std::cout << "producer waiting" << std::endl;
         full.wait(lock);
      }
      queue.push(e);
      empty.notify_one();
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
   bool             mBoardRequested;
   bool             mWfValid[WD_N_CHANNELS][2];
   unsigned int     mChannelMask;
   int              mDrs0TriggerCell;
   int              mDrs1TriggerCell;
 
public:
   WDEventRequest(int boardId, unsigned int mask = 0xFFFF) {
      mBoardId = boardId;
      mBoardRequested = true;
      for (int i=0 ; i<WD_N_CHANNELS ; i++) {
         mWfValid[i][0] = false;
         mWfValid[i][1] = false;
      }
      mChannelMask = mask;
   } ;
   
   int              GetBoardId() { return mBoardId; }
   void             SetRequested(bool flag) { mBoardRequested = flag; }
   bool             IsRequested() { return mBoardRequested; }
   void             SetWfValid(int channel, int segment, bool v) { mWfValid[channel][segment] = v; }
   void             SetDrs0TriggerCell(unsigned int c) { mDrs0TriggerCell = c; }
   void             SetDrs1TriggerCell(unsigned int c) { mDrs1TriggerCell = c; }
   int              GetDrs0TriggerCell() { return mDrs0TriggerCell; }
   int              GetDrs1TriggerCell() { return mDrs1TriggerCell; }
   void             SetMask(unsigned int mask) { mChannelMask = mask; }
   unsigned int     GetMask() { return mChannelMask; }
   bool             IsWfValid();
};

//--------------------------------------------------------------------

// waveform processor (waveform decoding, calibration, saving, ...
class WP {
   // calibration states
   enum { cCsInactive = 0,
      cCsSingleBoard  = 1,
      cCsFirstBoard   = 2,
      cCsFirstSample  = 3,
      cCsRunning      = 4 };

   enum { cCmNone     = 0,
      cCmVoltage      = 1,
      cCmTime         = 2 };

   static int        gDataSocket;
   static int        gServerPort;

   int               mVerbose;
   bool              mDemoMode;
  
   std::vector<WDB*> mWdb;

   bool              mRotateWaveform;
   bool              mOfsCalib1;
   bool              mOfsCalib2;
   bool              mGainCalib;
   bool              mRangeCalib;
   bool              mTimeCalib1;
   bool              mTimeCalib2;
   bool              mTimeCalib3;
   bool              mRemoveSpikes;
   
   int               mPacketsReceived;
   int               mCurrentEvent;
   
   std::thread       mThreadCollector;
   void Collector();
   std::thread SpawnCollectorThread() {
      return std::thread([=] { Collector(); });
   };
   
   std::vector<WDEventRequest *> mEventRequest;
   std::vector<WDEvent *> mEvent;
   std::vector<WDEvent *> mEventLast;

   std::mutex        mEventMutex;
   std::mutex        mEventAccessMutex;
   std::condition_variable mEventCV;
   bool              mEventNew;
   bool              mEventEmpty;

   void              InvalidateAllWf();
   void              ReceiveWfPacket();
   bool              AllPacketsReceived();
   void              RotateWaveforms();
   void              CalibrateWaveforms();
   void              RemoveSpikes(int tc, float wf[][1024]);
   //   void              LogWaveforms();
   
   CALIB_PROGRESS    calibProg;
   
   struct {
      std::string    fileName;
      int            fh;
      MXML_WRITER    *xml;
      int            format; // cLiFormatBinary / cLiFormatXML
      bool           bAll;
      int            board;
      int            nRequest;
      int            nLogged;
   } li;
   
   float             mOldRange;
   int               mOldMask0;
   int               mOldMask1;

   int               mOldReadoutSrc;
   bool              mOldCalibClock;
   int               mOldFeMux;
   bool              mOldCalibBuffer;
   
   void              AnalyzePeriod(WDEvent *, WDB *);
   void              AnalyzeTimeOffset(WDEvent *, WDB *);
   void              CalibrateLocal(WDEvent *, WDB *);
   void              CalibrateGlobal(WDEvent *, WDB *);
   
   unsigned int      mWDEvents;
   unsigned int      mWDReceivedEvents;
   
public:
   enum { cLiFormatBinary = 1, cLiFormatXML = 2};

   // constructor
   WP(std::vector<WDB*> w, int verbose = 0, bool demo = false);
   
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

   void SetRotateWaveform(bool f) { mRotateWaveform = f; }
   void SetOfsCalib1(bool f) { mOfsCalib1 = f; }
   void SetOfsCalib2(bool f) { mOfsCalib2 = f; }
   void SetGainCalib(bool f) { mGainCalib = f; }
   void SetRangeCalib(bool f) { mRangeCalib = f; }
   void SetTimeCalib1(bool f) { mTimeCalib1 = f; }
   void SetTimeCalib2(bool f) { mTimeCalib2 = f; }
   void SetTimeCalib3(bool f) { mTimeCalib3 = f; }
   void SetRemoveSpikes(bool f) { mRemoveSpikes = f; }
   void SetAllCalib(bool f) {
      mOfsCalib1 = f; mOfsCalib2 = f; mGainCalib = f; mRangeCalib = f;
      mTimeCalib1 = f; mTimeCalib2 = f; mTimeCalib3 = f;
   }
   
   bool IsVcalibActive() { return calibProg.mode == cCmVoltage; }
   bool IsTcalibActive() { return calibProg.mode == cCmTime; }
   
   int  GetVcalibBoard() { return calibProg.iBoard; }
   float GetVcalibProgress() { return calibProg.progress; }

   int  GetTcalibBoard() { return calibProg.iBoard; }
   float GetTcalibProgress() { return calibProg.progress; }

   // functions
   void RequestAllBoards();
   void RequestBoard(WDB* b);
   void SetEventRequestMasks();
   WDB* GetBoard(int board_id);
   unsigned int GetEventRequestMask(int board_id);
   
   bool GetLastEvent(WDB* b, int timeout, WDEvent& event);
   bool GetLastEvent(int timeout, std::vector<WDEvent *> event);
   bool RequestEvent(WDB* b, int timeout, WDEvent& event);
   
   void StartCalibrationVoltage(int b) {
      calibProg.mode = cCmVoltage;
      calibProg.nBoard = (b == -1) ? mWdb.size() : b+1;
      calibProg.iBoard = (b == -1) ? 0 : b;
      calibProg.state = cCsFirstBoard; }
   void StartCalibrationTime(int b) {
      calibProg.mode = cCmTime;
      calibProg.nBoard = (b == -1) ? mWdb.size() : b+1;
      calibProg.iBoard = (b == -1) ? 0 : b;
      calibProg.state = cCsFirstBoard; };
   void DoCalibrationVoltageStep();
   void DoCalibrationTimeStep();
   
   void StartWaveformSaving(std::string fileName, int format, bool bAll, int board, int nEvents);
   void StopLogging();
   unsigned int GetNLogged() { return li.nLogged; }
   void SaveWaveforms();
   
   void ResetStatistics() { mWDEvents = mWDReceivedEvents = 0; }
   int GetWDEvents() { return mWDEvents; }
   int GetWDReceivedEvents() { return mWDReceivedEvents; }
};

//--------------------------------------------------------------------

// WaveDREAM board class. Interface functions to all WDB registers
class WDB {
   std::string      mName;
   unsigned char    mEthAddrAscii[16];
   unsigned char    mEthAddrBin[16];
   int              mVerbose;
   bool             mDemoMode;
   bool             mSendBlocked;

   unsigned int     creg[REG_NR_OF_CTRL_REGS];
   unsigned int     sreg[REG_NR_OF_STAT_REGS];
   
   static int       gASCIISocket;
   static int       gBinSocket;
   static unsigned short udpSequenceNumber;

   std::string      SendReceiveUDP(std::string str, int timeout_ms = 100);
   void             SendUDP(std::string str, int timeout_ms = 100);

   void             WriteUDP(unsigned int ofs, std::vector<unsigned int> data, int timeout_ms = 250);
   std::vector<unsigned int> ReadUDP(unsigned int ofs, unsigned int len, int timeout_ms = 250);

public:
   
   // constructor
   WDB(std::string name, int verbose = 0) {
      mName = name;
      mVerbose = verbose;
      mDemoMode = (name == "demo");
      mSendBlocked = false;
   }

   const unsigned int cRequiredCompatibilityLevel = 1;
   
   // constants
   enum { cReadoutSrcDrs       = 0x01,
      cReadoutSrcAdc           = 0x02,
      cReadoutSrcTdc           = 0x04 };
   
   enum { cFeMuxNextChannel    = 0,
      cFeMuxPreviousChannel    = 1,
      cFeMuxInput              = 2,
      cFeMuxCalSource          = 3 };

   enum { cTriggerSchemeSimple = 0,
      cTriggerSchemeOr         = 1,
      cTriggerSchemePattern    = 2};

   enum { cTimingReferenceOff  = 0,
      cTimingReferenceSine     = 1,
      ctimingReferenceSquare   = 2};
   
   // calibrations
   VCALIB           mVCalib;
   TCALIB           mTCalib;
   
   // interface functions
   void SetVerbose(int verbose) { mVerbose = verbose; }
   void Connect();
   void SetDestinationPort(int port);
   void ReceiveControlRegisters(unsigned int index=0, unsigned int nReg=REG_NR_OF_CTRL_REGS);
   void ReceiveStatusRegisters(unsigned int index=0, unsigned int nReg=REG_NR_OF_STAT_REGS);
   void ReceiveStatusRegister(int ofs);
   void SetRegMask(unsigned int rofs, unsigned int mask, unsigned int ofs, unsigned int v, bool send=true);
   void SendControlRegisters();
   void PrintVersion();
   void SetSendBlocked(bool f) { mSendBlocked = f; }

   // setter & getter ----------
   std::string GetName() { return mName; }
   
   // status registers
   std::string GetFwBuild();
   std::string GetHwVersion();
   unsigned int GetCompatibilityLevel();
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
   unsigned int GetPllLck(bool refresh = true);
   bool IsExtPllLck(bool refresh = true);
   bool IsIntPllLck(bool refresh = true);
   unsigned int GetDrsSampleFreq();
   void SetDrsSampleFreq(unsigned int f);
   unsigned int GetLmkInputFreq();
   void SetLmkInputFreq(unsigned int f);
   unsigned int GetAdcSampleFreq();
   unsigned int GetAdcInfo();
   
   void GetScalers(std::vector<unsigned long> &s, bool refresh = true);

   unsigned int GetCompChannelStatus();
   unsigned int GetLastEventNumber();
   unsigned int GetTriggerBusParityErrorCount();
   unsigned int GetTriggerBusType();
   unsigned int GetTriggerBusNumber();
   
   unsigned int GetAdvTriggerStatus(int r);

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
   void SetTimingCalibSignalDelay(int value);
   int GetTimingCalibSignalDelay();
   int GetTimingReferenceSignal();
   void SetTimingReferenceSignal(int value);
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
   float GetDacPzcLevelV();
   void SetDacPzcLevelV(float v);
   int GetDacPzcLevelN();
   void SetDacPzcLevelN(int n);
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
   void SetAdvTrgCfg(int i, unsigned int v);
   unsigned int GetAdvTrgCfg(int i);
   
   // hihg level methods ----------
   unsigned int GetTriggerDelayNs();
   void SetTriggerDelayNs(unsigned int ns);
   
   void SetRange(float r);
   float GetRange();
   
   void RequestEvent();
   
   void SaveVoltageCalibration(int freq);
   bool LoadVoltageCalibration(int freq);
   void SaveTimeCalibration(int freq);
   bool LoadTimeCalibration(int freq);
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
#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))

#endif /* defined(__wdblib_h__) */

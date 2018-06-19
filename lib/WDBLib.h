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
#include "WDBReg.h"

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <map>
#include "averager.h"
#include "mxml.h"

#define WD_N_CHANNELS 18
#define SUCCESS        1

class WDB;

//--------------------------------------------------------------------

#pragma pack(1) // byte-level alignement for frame header

typedef struct {
   unsigned char  protocol_version;
   unsigned char  board_revision;
   unsigned short serial_number;
   unsigned char  crate_id;
   unsigned char  slot_id;
   unsigned char  channel_info;
   unsigned char  data_type;
   unsigned int   tx_enable;
   unsigned short zero_suppression_mask;
   unsigned short flags;
   unsigned char  trigger_source;
   unsigned char  bits_per_sample;
   unsigned short samples_per_event_per_channel;
   unsigned short payload_length;
   unsigned short data_offset;
   unsigned char  time_stamp[8];
   unsigned int   event_number;
   unsigned char  trigger_information[6];
   unsigned short drs_trigger_cell;
   unsigned int   sampling_frequency;
   unsigned short temperature;
   unsigned short dac_ofs;
   unsigned short dac_rofs;
   unsigned short frontend_settings;
   unsigned char  reserved[8];
} WD2_FRAME_HEADER;

#pragma pack() // reset alignment to default value

enum {
   cDataTypeDRS    = 0,
   cDataTypeADC    = 1,
   cDataTypeTDC    = 2,
   cDataTypeTrg    = 3,
   cDataTypeScaler = 4,
   cDataTypeDummy  = 5
};

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
   unsigned int GetSamplingFrequency() { return mCalib.sampling_frequency; }
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
   unsigned int GetSamplingFrequency() { return mCalib.sampling_frequency; }
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
   
   bool             mValid;
   unsigned short   mBoardId;
   unsigned short   mCrateId;
   unsigned short   mSlotId;
   unsigned int     mEventNumber;
   unsigned int     mSamplingFrequency;
   unsigned short   mTriggerNumber;
   int              mTriggerCell[WD_N_CHANNELS];
   int              mTriggerCellDrs0;
   int              mTriggerCellDrs1;
   unsigned short   mTriggerType;
   float            mTemperature;
   bool             mWFTypeADC;
   
   float            mWfU[WD_N_CHANNELS][1024];
   float            mWfT[WD_N_CHANNELS][1024];

   float            mWfUADC[WD_N_CHANNELS][2048];
   float            mWfTADC[WD_N_CHANNELS][2048];

   bool             mVCalibrated;
   bool             mTCalibrated;
   
   WDEvent(int boardId) { mBoardId = boardId; mValid = false; };

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
   int              mRequestedSegments;
   bool             mWfValid[WD_N_CHANNELS][3];
   unsigned int     mChannelMask;
   int              mWfType;
   int              mDrsTriggerCell[WD_N_CHANNELS];
 
public:
   WDEventRequest(int boardId, unsigned int mask = 0xFFFF, int segments = 2, int type = cDataTypeDRS) {
      mBoardId = boardId;
      mBoardRequested = true;
      mRequestedSegments = segments;
      for (int i=0 ; i<WD_N_CHANNELS ; i++) {
         mWfValid[i][0] = false;
         mWfValid[i][1] = false;
         mWfValid[i][2] = false;
         mDrsTriggerCell[i] = -1;
      }
      mChannelMask = mask;
      mWfType = type;
   } ;
   
   int              GetBoardId() { return mBoardId; }
   void             SetRequested(bool flag) { mBoardRequested = flag; }
   void             SetRequestedSegments(int s) { mRequestedSegments = s; }
   bool             IsRequested() { return mBoardRequested; }
   void             SetWfValid(int channel, int segment, bool v) { if (segment<3) mWfValid[channel][segment] = v; }
   void             SetDrsTriggerCell(int ch, unsigned int c) { mDrsTriggerCell[ch] = c; }
   int              GetDrsTriggerCell(int ch) { return mDrsTriggerCell[ch]; }
   void             SetMask(unsigned int mask) { mChannelMask = mask; }
   unsigned int     GetMask() { return mChannelMask; }
   void             SetWfType(int type) { mWfType = type; }
   int              GetWfType() { return mWfType; }
   bool             IsWfValid();
};

//--------------------------------------------------------------------

// waveform processor (waveform decoding, calibration, saving, ...
class WP {
   // calibration states
   enum {
      cCsInactive     = 0,
      cCsSingleBoard  = 1,
      cCsFirstBoard   = 2,
      cCsFirstSample  = 3,
      cCsRunning      = 4
   };

   enum {
      cCmNone         = 0,
      cCmVoltage      = 1,
      cCmTime         = 2
   };

   static int        gDataSocket;
   static int        gServerPort;

   int               mVerbose;
   std::string       mLogfile;
   bool              mDemoMode;
  
   std::vector<WDB*> mWdb;
   std::map<int, WDB*> mWdbMap;

   bool              mRotateWaveform;
   bool              mCalibrateWaveform;
   bool              mOfsCalib1;
   bool              mOfsCalib2;
   bool              mGainCalib;
   bool              mRangeCalib;
   bool              mTimeCalib1;
   bool              mTimeCalib2;
   bool              mTimeCalib3;
   
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

   unsigned int      usSince(std::chrono::time_point<std::chrono::high_resolution_clock> start);
   void              InvalidateAllWf();
   int               ReceiveWfPacket();
   bool              AllPacketsReceived();
   void              UnrotateWaveforms();
   void              RemoveSpikes(int tc, float wf[][1024]);
   std::chrono::time_point<std::chrono::high_resolution_clock> mEventStartTime;
   
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
   int               mOldMaskDrs;
   int               mOldMaskAdc;

   int               mOldReadoutSrc;
   bool              mOldCalibClock;
   int               mOldFeMux;
   bool              mOldCalibBuffer;
   
   void              AnalyzePeriod(WDEvent *, WDB *);
   void              AnalyzeTimeOffset(WDEvent *, WDB *);
   void              CalibrateLocal(WDEvent *, WDB *);
   void              CalibrateGlobal(WDEvent *, WDB *);
   
   unsigned int      mWDReceivedEvents;
   unsigned int      mWDDroppedEvents;
   unsigned int      mLastEventNumber;

public:
   enum { cLiFormatBinary = 1, cLiFormatXML = 2};

   // constructor
   WP(std::vector<WDB*> w, int verbose = 0, std::string logfile = "", bool demo = false);
   
   // setter & getter
   int GetDataSocket() { return gDataSocket; }
   int GetServerPort() { return gServerPort; }
   bool IsVerbose() { return mVerbose; }
   bool IsDemoMode() { return mDemoMode; }
   bool IsRotateWaveform() { return mRotateWaveform;}
   bool IsCalibrateWaveform() { return mCalibrateWaveform;}
   bool IsOfsCalib1() { return mOfsCalib1;}
   bool IsOfsCalib2() { return mOfsCalib2;}
   bool IsGainCalib() { return mGainCalib;}
   bool IsRangeCalib() { return mRangeCalib;}
   bool IsTimeCalib1() { return mTimeCalib1;}
   bool IsTimeCalib2() { return mTimeCalib2;}
   bool IsTimeCalib3() { return mTimeCalib3;}

   void SetRotateWaveform(bool f) { mRotateWaveform = f; }
   void SetCalibrateWaveform(bool f) { mCalibrateWaveform = f; }
   void SetOfsCalib1(bool f) { mOfsCalib1 = f; }
   void SetOfsCalib2(bool f) { mOfsCalib2 = f; }
   void SetGainCalib(bool f) { mGainCalib = f; }
   void SetRangeCalib(bool f) { mRangeCalib = f; }
   void SetTimeCalib1(bool f) { mTimeCalib1 = f; }
   void SetTimeCalib2(bool f) { mTimeCalib2 = f; }
   void SetTimeCalib3(bool f) { mTimeCalib3 = f; }
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
   void SetEventRequestType();
   void SetRequestedSegments(int s);
   WDB* GetBoard(int board_id);
   unsigned int GetEventRequestMask(int board_id);
   
   bool WaitNewEvent(int timeout);
   bool GetLastEvent(WDB* b, int timeout, WDEvent& event);
   bool GetLastEvent(int timeout, std::vector<WDEvent *> event);
   bool RequestEvent(WDB* b, int timeout, WDEvent& event);
   
   void CalibrateWaveforms(WDEvent* event);
   void CalibrateWaveforms(std::vector<WDEvent *> event);

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
   
   void ResetStatistics() { mLastEventNumber = mWDReceivedEvents = mWDDroppedEvents = 0; }
   int GetWDReceivedEvents() { return mWDReceivedEvents; }
   int GetWDDroppedEvents() { return mWDDroppedEvents; }
};

//--------------------------------------------------------------------

// WaveDREAM board class. Interface functions to all WDB registers
class WDB: public WDBREG {
   std::string      mName;
   std::string      mPrompt;
   unsigned char    mEthAddrAscii[16];
   unsigned char    mEthAddrBin[16];
   int              mVerbose;
   std::string      mLogfile;
   bool             mDemoMode;
   bool             mSendBlocked;
   int              mReceiveTimeoutMs;
   unsigned int     mChnTxEn;

   unsigned int     creg[REG_NR_OF_CTRL_REGS];
   unsigned int     sreg[REG_NR_OF_STAT_REGS];
   
   static int       gASCIISocket;
   static int       gBinSocket;
   static unsigned short udpSequenceNumber;

   void             BlockSend(bool flag) { mSendBlocked = flag; }
   int              GetReceiveTimeoutMs() { return mReceiveTimeoutMs; };
   void             SetReceiveTimeoutMs(int to) { mReceiveTimeoutMs = to; };

   std::string      SendReceiveUDP(std::string str);
   void             SendUDP(std::string str);

   void             WriteUDP(unsigned int ofs, std::vector<unsigned int> data);
   std::vector<unsigned int> ReadUDP(unsigned int ofs, unsigned int len);

public:
   
   // constructor
   WDB(std::string name, int verbose = 0);

   const unsigned int cRequiredRegLayoutCompatLevel = 6;
   const unsigned int cRequiredFwCompatLevel = 2;
   const int cDefaultReceiveTimeoutMs = 100;

   // constants
   enum {
      cReadoutSrcDrs           = 0x01,
      cReadoutSrcAdc           = 0x02,
      cReadoutSrcTdc           = 0x04
   };
   
   enum {
      cFeMuxNextChannel        = 0,
      cFeMuxPreviousChannel    = 1,
      cFeMuxInput              = 2,
      cFeMuxCalSource          = 3
   };

   enum {
      cTriggerSchemeSimple     = 0,
      cTriggerSchemeOr         = 1,
      cTriggerSchemePattern    = 2
   };

   enum {
      cTimingReferenceOff      = 0,
      cTimingReferenceSine     = 1,
      cTimingReferenceSquare   = 2
   };
   
   enum {
      cDbgUart                 = 0x0,
      cDbgTrigger              = 0x1,
      cDbgSoftTrigger          = 0x2,
      cDbgExtTrigger           = 0x3,
      cDbgSyncDirect           = 0x4,
      cDbgSyncSampled          = 0x5,
      cDbgBusyLocal            = 0x6,
      cDbgBusyBackplane        = 0x7,
      cDbgLMKInputClk          = 0x8,
      cDbgADCClk               = 0x9,
      cDbgDataClk              = 0xA
   };

   // calibrations
   VCALIB           mVCalib;
   TCALIB           mTCalib;
   
   // register functions, overload pure virtual functions from WDBREG
   void SetRegMask(unsigned int rofs, unsigned int mask, unsigned int ofs, unsigned int v);
   unsigned int BitExtractStatus(unsigned int rofs, unsigned int mask, unsigned int ofs);
   unsigned int BitExtractControl(unsigned int rofs, unsigned int mask, unsigned int ofs);
   
   // interface functions
   void SetVerbose(int verbose) { mVerbose = verbose; }
   void SetLogFile(std::string logfile) { mLogfile = logfile; }
   void Connect();
   void SetDestinationPort(int port);
   void ReceiveControlRegisters(unsigned int index=0, unsigned int nReg=REG_NR_OF_CTRL_REGS);
   void ReceiveStatusRegisters(unsigned int index=0, unsigned int nReg=REG_NR_OF_STAT_REGS);
   void ReceiveStatusRegister(int ofs);
   void SendControlRegisters();
   void PrintVersion();
   void SetSendBlocked(bool f) { mSendBlocked = f; }

   // setter & getter ----------
   std::string GetName() { return mName; }
   
   // high level status registers
   std::string GetFwBuild();
   std::string GetHwVersion();
   float GetTemperatureDegree(bool refresh = true);
   unsigned int GetPllLock(bool refresh = true);
   void GetScalers(std::vector<unsigned long> &s, bool refresh = true);
   void GetHVCurrents(std::vector<float> &c, bool refresh = true);
   void GetHVBaseVoltage(float &voltage, bool refresh = true);
   void Get1wireTemperatures(std::vector<float> &c, bool refresh = true);

   // high level control registers
   void SetDrsSampleFreq(unsigned int f);
   void SetLmkInputFreq(unsigned int f);
   unsigned int GetLmkInputFreq();

   void SetTimingCalibSignalEnable(bool value);
   void SetTimingCalibSignalDelay(int value);
   int GetTimingCalibSignalDelay();
   void SetTimingReferenceSignal(int value);
   int GetTimingReferenceSignal();

   void ResetDaqPll();
   void ResetDcbOserdesPll();
   void ResetDcbOserdesIf();
   void ResetTcbOserdesPll();
   void ResetTcbOserdesIf();
   void ResetAllPll();
   void ResetScaler();
   void ResetTriggerParityErrorCounter();
   void LmkSyncLocal();
   void ResetAdcIf();
   void ResetDataLinkIf();
   void ResetPackager();
   void ResetEventCounter();
   void ResetDrsControlFsm();
   void ReconfigureFpga();
   
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

   bool GetFePzc(int chn);
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

   void GetHVTarget(std::vector<float> &hv);
   void SetHVTarget(int chn, float v);
   
   unsigned int GetLmk(int reg);
   void SetLmk(int reg, unsigned int v);

   unsigned int GetTrgSrcEnPtrn(int i);
   void SetTrgSrcEnPtrn(int i, unsigned int value);

   unsigned int GetTrgStatePtrn(int i);
   void SetTrgStatePtrn(int i, unsigned int value);

   // high level methods ----------
   unsigned int GetTriggerDelayNs();
   void SetTriggerDelayNs(unsigned int ns);
   
   void SetRange(float r);
   float GetRange();
   
   void RequestEvent();
   
   unsigned int GetDrsSampleFreqMhz();
   void SaveVoltageCalibration(int freq);
   bool LoadVoltageCalibration(int freq, std::string path="");
   void SaveTimeCalibration(int freq);
   bool LoadTimeCalibration(int freq, std::string path="");
   
   unsigned int GetTriggerFallingEdge();
   void SetTriggerFallingEdge(unsigned int value);
   
   unsigned int GetChnTxEn() { return mChnTxEn; };
   void SetChnTxEn(int mask) { mChnTxEn = mask; };
   // int GetTimingReferenceSignal() { return mTimingReferenceSignal; }
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

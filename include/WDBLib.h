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

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <map>
#include "averager.h"
#include "mxml.h"

#include "WDBReg.h"
#include "DCBLib.h"

#define WD_N_CHANNELS 18
#define WD_N_SCALER 19
#define SUCCESS        1

class WDB;

std::string getWdbLibRevision();

//--------------------------------------------------------------------

#pragma pack(1) // byte-level alignment for frame header

typedef struct {
   uint8_t        protocol_version;
   uint8_t        board_type_revision;
   uint16_t       serial_number;
   uint8_t        crate_id;
   uint8_t        slot_id;
   uint16_t       packet_number;
   uint8_t        data_type;
   uint8_t        wdaq_flags;
   uint8_t        trigger_information[6];
   uint32_t       event_number;
   uint16_t       payload_length;
   uint16_t       data_chunk_offset;
} FRAME_WDAQ_HEADER;

typedef struct {
   uint8_t        channel_info;
   uint8_t        wd_flags;
   uint16_t       samples_per_event_per_channel;
   uint32_t       sampling_frequency;
   uint8_t        bits_per_sample;
   uint8_t        trigger_source;
   uint16_t       zero_suppression_mask;
   uint32_t       tx_enable;
   uint16_t       drs_trigger_cell;
   uint32_t       reserved;
   uint16_t       temperature;
   uint16_t       dac_pzc;
   uint16_t       dac_ofs;
   uint16_t       dac_rofs;
   uint16_t       frontend_settings;
   uint64_t       time_stamp;
} FRAME_WDB_HEADER;

#pragma pack() // reset alignment to default value

enum Type {
   cDataTypeDRS                  = 0,
   cDataTypeADC                  = 1,
   cDataTypeTDC                  = 2,
   cDataTypeTrg                  = 3,
   cDataTypeScaler               = 4,
   cDataTypeDummy                = 5,
   cDataTypeTCB                  = 8
};

static const Type DataTypeAll[] = {
   cDataTypeDRS,
   cDataTypeADC,
   cDataTypeTDC,
   cDataTypeTrg,
   cDataTypeScaler,
   cDataTypeDummy,
   cDataTypeTCB
};

enum {
   cWDAQFlagEndOfEvent           = 0,
   cWDAQFlagStartOfEvent         = 1,
   cWDAQFlagEndOfType            = 2,
   cWDAQFlagStartOfType          = 3
};

enum {
   cWDFlagDRSPLLLock             = 0,
   cWDFlagLMKPLLLock             = 1,
   cWDFlagNewTriggerInfo         = 2,
   cWDFlagTriggerInfoParityError = 3,
   cWDFlagZeroSuppEnable         = 4,
   cWDFalgZeroSuppInhibit        = 5
};

//--------------------------------------------------------------------

typedef struct {
   char             version_id[4];
   unsigned int     crc;
   uint16_t         sampling_frequency;
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
   float GetTemperature() { return mCalib.temperature; }
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
   float GetTemperature() { return mCalib.temperature; }
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
   int            nIter5;
   int            iIter5;
   int            iIterTotal;
   int            nIterTotal;
   Averager       *ave;
} CALIB_PROGRESS;

//--------------------------------------------------------------------

class WDEvent {
public:

   unsigned short   mBoardId;
   unsigned short   mCrateId;
   unsigned short   mSlotId;
   unsigned int     mEventNumber;
   unsigned int     mDRSSamplingFrequency;
   unsigned int     mADCSamplingFrequency;
   unsigned short   mTriggerNumber;
   int              mTriggerCell[WD_N_CHANNELS];
   int              mTriggerCellDrs0;
   int              mTriggerCellDrs1;
   unsigned short   mTriggerType;
   float            mTemperature;

   int              mDRSChannelPresent[WD_N_CHANNELS];
   float            mWfUDRS[WD_N_CHANNELS][1024];
   float            mWfTDRS[WD_N_CHANNELS][1024];

   int              mADCChannelPresent[WD_N_CHANNELS];
   float            mWfUADC[WD_N_CHANNELS][2048];
   float            mWfTADC[WD_N_CHANNELS][2048];

   int              mTDCChannelPresent[WD_N_CHANNELS];
   unsigned char    mWfTDC[WD_N_CHANNELS][512];

   uint64_t         mTrgData[512];

   uint64_t         mScaler[WD_N_SCALER];

   bool             mVCalibrated;
   bool             mTCalibrated;

   // statistics
   bool             mHasADCData;
   bool             mHasDRSData;
   bool             mHasTDCData;
   bool             mHasTRGData;
   bool             mHasScalerData;

   bool             mSOEReceived;
   bool             mEOEReceived;
   uint32_t         mFirstPacketNumber;
   uint32_t         mLastPacketNumber;
   uint32_t         mReceivedPackets;

   bool             mEventValid;

   WDEvent(int boardId) { mBoardId = boardId; };

   void             ClearEvent();
   void             SetEventHeaderInfo(FRAME_WDAQ_HEADER *);
   void             SetWDEventHeaderInfo(FRAME_WDAQ_HEADER *, FRAME_WDB_HEADER *);
   void             ProcessPacket(FRAME_WDAQ_HEADER *pdaqh);
   bool             IsEventValid();
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
      cCmTime         = 2,
      cCmTimeError    = 3
   };

   static int        gDataSocket;
   int               mServerPort;

   std::string       mWdsDir;

   int               mVerbose;
   std::string       mLogfile;
   bool              mDemoMode;

   std::vector<WDB*> mWdb;
   std::map<int, WDB*> mWdbMap;
   std::vector<WDB*> mWdbRequested;

   bool              mRotateWaveform;
   bool              mCalibrateWaveform;
   bool              mOfsCalib1;
   bool              mOfsCalib2;
   bool              mGainCalib;
   bool              mRangeCalib;
   bool              mTimeCalib1;
   bool              mTimeCalib2;
   bool              mTimeCalib3;

   int               mReceivedPacketsThisEvent;
   int               mCurrentEvent;

   std::thread       mThreadCollector;
   void Collector();
   std::thread SpawnCollectorThread() {
      return std::thread([=] { Collector(); });
   };

   std::map<int, WDEvent *> mEvent;
   std::map<int, WDEvent *> mEventLast;

   std::mutex        mEventMutex;
   std::mutex        mEventAccessMutex;
   std::condition_variable mEventCV;
   bool              mEventNew;
   bool              mEventEmpty;

   void              StartNewEvent();
   void              LogEvent(FRAME_WDAQ_HEADER *pdaqh, FRAME_WDB_HEADER   *ph);
   int               ReceiveWfPacket();
   bool              IsEventValid();
   void              UnrotateWaveforms();
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
   int               mOldFeMux;
   int               mOldTimingCalibSignalEn;
   int               mOldCalibBufferEn;
   int               mOldTimingReference;
   int               mOldExtAsyncTriggerEn;
   int               mOldPatternTriggerEn;
   int               mOldTriggerHoldoff;

   static int        AnalyzePeriod(WDEvent *, WDB *);
   void              AnalyzeTimeOffset(WDEvent *);
   void              CalibrateLocal(WDEvent *, WDB *);
   static void       CalibrateGlobal(WDEvent *, WDB *);

   time_t            mStartStatistics;
   unsigned int      mWDReceivedPackets;
   unsigned int      mWDDroppedPackets;
   unsigned int      mLastEventNumber;
   double            mPacketEfficiency;

public:
   enum { cLiFormatBinary = 1, cLiFormatXML = 2};

   // constructor
   WP(int verbose = 0, std::string wdsDir = "", std::string logfile = "", bool demo = false);

   // duration calculator
   static std::chrono::time_point<std::chrono::high_resolution_clock> usStart();
   static unsigned int usSince(std::chrono::time_point<std::chrono::high_resolution_clock> start);

   // setter & getter
   void SetWDBList(std::vector<WDB *> w);
   static int GetDataSocket() { return gDataSocket; }
   int GetServerPort() { return mServerPort; }
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
   bool IsTcalibError() { return calibProg.mode == cCmTimeError; }
   void ClearTcalibError() { calibProg.mode = cCmNone; }

   int  GetVcalibBoard() { return calibProg.iBoard; }
   float GetVcalibProgress() { return calibProg.progress; }

   int  GetTcalibBoard() { return calibProg.iBoard; }
   float GetTcalibProgress() { return calibProg.progress; }

   // functions
   void SetRequestedBoard(WDB* b);
   void SetRequestedBoard(std::vector<WDB *>wdb);
   WDB* GetBoard(int board_id);

   bool WaitNewEvent(int timeout);
   bool GetLastEvent(WDB* b, int timeout, WDEvent& event);
   bool GetLastEvent(int timeout, std::vector<WDEvent *> event);
   bool RequestEvent(WDB* b, int timeout, WDEvent& event);

   void CalibrateWaveforms(WDEvent* event);
   void CalibrateWaveforms(std::map<int, WDEvent *> event);

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
   void DoVoltageCalibrationStep();
   void DoTimeCalibrationStep();

   void StartWaveformSaving(std::string fileName, int format, bool bAll, int board, int nEvents);
   void StopLogging();
   unsigned int GetNLogged() { return li.nLogged; }
   void SaveWaveforms();
   bool IsXMLLogging();

   double GetWDPacketEfficiency() { return mPacketEfficiency; }
};

//--------------------------------------------------------------------

class WDBS {
   int mRange;
   int mDrsChTxEn;
   int mAdcChTxEn;
   int mFeMux;
   int mFeGain;
   int mDacCalDcV;
   int mInterPkgDelay;
   int mTriggerHoldoff;
   int mTimingCalibSignalEn;
   int mCalibBufferEn;
   int mTimingReferenceSignal;
   int mExtAsyncTriggerEn;
   int mPatternTriggerEn;

public:
   void Save(WDB *b);
   void Restore(WDB *b);
};

// WaveDREAM board class. Interface functions to all WDB registers
class WDB: public WDBREG {
   std::string      mWDBName;
   std::string      mWDBAddr;
   std::string      mPrompt;
   DCB*             mDCB;
   unsigned int     mSlot;
   unsigned char    mEthAddrAscii[16];
   unsigned char    mEthAddrBin[16];
   char             mEthAddrStr[16];
   bool             mVerbose;
   std::string      mLogfile;
   bool             mDemoMode;
   bool             mSendBlocked;
   int              mReceiveTimeoutMs;
   unsigned int     mChnTxEn;
   int              mTriggerHoldoff;
   int              mTimingReferenceSignal;

   int              mCalibClkFreq;

   std::vector<unsigned int> creg;
   std::vector<unsigned int> sreg;

   static int       gASCIISocket;
   static int       gBinSocket;
   static unsigned short udpSequenceNumber;

   std::string      SendReceiveUDP(std::string str, unsigned char *ethAddr = NULL);
   void             SendUDP(std::string str, unsigned char *ethAddr = NULL);

   void             WriteUDP(unsigned int ofs, std::vector<unsigned int> data);
   std::vector<unsigned int> ReadUDP(unsigned int ofs, unsigned int len);

   WDBS             mSave;
public:

   // constructor
   WDB(std::string name, bool verbose = false);
   WDB(DCB *dcb, int slot, bool verbose = false);

   // static functions
   static unsigned int bcd2dec(const unsigned int bcd);
   static void bitReplace(unsigned int &reg, unsigned int mask, unsigned int ofs, unsigned int value);

   // setter to add DCB interface to an already constructed WDB 
   void SetDcbInterface(DCB* dcb, int slot);
   // getter of Dcb interface
   DCB* GetDcbInterface(){ return mDCB; };
   // check if is using DCB interface
   bool IsDcbInterface(){ return mDCB != nullptr; };

   const unsigned int cRequiredRegLayoutCompatLevel2F = 8;
   const unsigned int cRequiredFwCompatLevel2F = 4;
   const unsigned int cRequiredRegLayoutCompatLevel2G = 9;
   const unsigned int cRequiredFwCompatLevel2G = 5;

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
      cDbgSyncInternal         = 0x6,
      cDbgBusyLocal            = 0x7,
      cDbgBusyBackplane        = 0x8,
      cDbgLMKInputClk          = 0x9,
      cDbgADCClk               = 0xA,
      cDbgDataClk              = 0xB,
      cDbgLMK5Clk              = 0xC,
      cDbgLMKChipSelect        = 0xD
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
   int IsVerbose() { return mVerbose; }
   void SetLogFile(std::string logfile) { mLogfile = logfile; }
   void Connect();
   bool Ping();

   void SetDestinationPort(int port);

   void ReceiveControlRegisters(unsigned int index=0, unsigned int nReg=0);
   void ReceiveStatusRegisters(unsigned int index=0, unsigned int nReg=0);
   void ReceiveStatusRegister(int ofs);
   void SendControlRegisters();
   void PrintVersion();
   bool GetSendBlock() { return mSendBlocked; }
   void SetSendBlock(bool flag) { mSendBlocked = flag; }

   // setter & getter ----------
   std::string GetName() { return mWDBName; }
   std::string GetAddr() { return mWDBAddr; }
   std::string GetEthAddrStr() { return mEthAddrStr; }
   int GetReceiveTimeoutMs() { return mReceiveTimeoutMs; };
   void SetReceiveTimeoutMs(int to) { mReceiveTimeoutMs = to; };
   int GetSlotNumber() { return mSlot; }

   // high level status registers
   std::string GetFullBuild();
   std::string GetFwGitHashStr();
   std::string GetFwBuild();
   std::string GetSwGitHashStr();
   std::string GetSwBuild();
   std::string GetHwVersion();
   std::string GetHvVersion();
   float GetTemperatureDegree(bool refresh = true);
   float GetVCalibTemperature();
   float GetTCalibTemperature();
   unsigned int GetPllLock(bool refresh = true);
   void GetScalers(std::vector<uint64_t> &s, bool refresh = true);
   void GetHVCurrents(std::vector<float> &c, bool refresh = true);
   void GetHVBaseVoltage(float &voltage, bool refresh = true);
   void Get1wireTemperatures(std::vector<float> &c, bool refresh = true);
   int GetCalibClkFreq() { return mCalibClkFreq; }

   void Save() { mSave.Save(this); };
   void Restore() { mSave.Restore(this); };

   // high level control registers
   void SetDrsSampleFreq(unsigned int f);
   void SetLmkInputFreq(unsigned int f);
   unsigned int GetLmkInputFreq();

   void SetSineWaveEnable(bool value);
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

   void TriggerSoftEvent();

   unsigned int GetDrsSampleFreqMhz();
   void SaveVoltageCalibration(int freq, std::string path="");
   bool LoadVoltageCalibration(int freq, std::string path="");
   void SaveTimeCalibration(int freq, std::string path="");
   bool LoadTimeCalibration(int freq, std::string path="");

   unsigned int GetChnTxEn() { return mChnTxEn; };
   void SetChnTxEn(int mask) { mChnTxEn = mask; };

   void SetTriggerHoldoff(int holdoff) { mTriggerHoldoff = holdoff; }
   int GetTriggerHoldoff() { return mTriggerHoldoff; }
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

#include "DAQLib.h"
#include "WDBLib.h"
#include <cmath>
#include <list>
#include <vector>
#include <iostream>
#include <fstream>

#define USEMEMORYPOOL

#ifndef WDAQLIB_H
#define WDAQLIB_H

#include "WDLib.h"
#include "wdaq_board_id.h"

//Error definition
#define WDAQLIB_ERROR_CORRUPTEDPACKET 1
#define WDAQLIB_ERROR_NOTBUILDING 2
#define WDAQLIB_ERROR_MISSINGCALIB 3
#define WDAQLIB_ERROR_CALIBTEMPERATURE 4
#define WDAQLIB_ERROR_PLLLOCK 5
#define WDAQLIB_ERROR_TEMPERATURE 6
#define WDAQLIB_ERROR_LAST WDAQLIB_ERROR_TEMPERATURE

//classes in this file
class WDAQPacketData;
class WDAQWdbPacketData;
class WDAQDRSPacketData;
class WDAQADCPacketData;
class WDAQTDCPacketData;
class WDAQTRGPacketData;
class WDAQScaPacketData;
class WDAQDummyPacketData;
class WDAQTcbPacketData;

class WDAQBoardEvent;
class WDAQWdbEvent;
class WDAQTcbBank;
class WDAQTcbEvent;

class WDAQEvent;

class WDAQPacketCollector;
class WDAQTCBReader;
class WDAQEventBuilder;
class WDAQWorker;
class WDAQEventWriter;

//forward declarations
class WDTCB;

#define EOE 1
#define SOE 2
#define EOT 4
#define SOT 8
#define CRC_ERROR 16
#define DATAGRAM_ERROR 32
#define BUFFER_ERROR 64

//#define WD2_BOARD_ID 0
//#define TCB_BOARD_ID 1

typedef struct {
   char           bank_name[4];
   unsigned int   time_stamp;
   unsigned short temperature;
   unsigned char reserved[6];
} FRAME_TCB_HEADER;

//WDAQ Packet Data - class for UDP DAQ packets 
class WDAQPacketData{
   public:
   //informations from WDAQ packet header
   unsigned char    mProtocolVersion;
   unsigned char    mBoardType;
   unsigned char    mBoardRevision;
   unsigned short   mBoardId;
   unsigned short   mCrateId;
   unsigned short   mSlotId;
   unsigned short   mPacketNumber;
   unsigned char    mDataType;
   unsigned char    mWDAQFlags;
   unsigned short   mPayloadLength;
   unsigned short   mDataOffset; 
   unsigned int     mEventNumber;
   unsigned short   mTriggerNumber;
   unsigned char    mTriggerType;
   unsigned short   mSerialTriggerData;  
   //Set properties according to UDP event header
   void SetEventHeaderInfo(FRAME_WDAQ_HEADER *);

   //idea to how to handle board event merging across different board types
   bool AddToBoardEvent(WDAQBoardEvent *e) {
      HeaderToBoardEvent(e);
      return AddDataToBoardEvent(e);
   };

   virtual ~WDAQPacketData() { };

#ifdef USEMEMORYPOOL
   //memory pool operators
   void* operator new(size_t size);
   void operator delete(void* ptr);
#endif

   protected:
   //Set WDAQBoardEvent Header
   void HeaderToBoardEvent(WDAQBoardEvent *e);

   //To be overwritten by derived classes, return false on failure
   virtual bool AddDataToBoardEvent(WDAQBoardEvent *e) { return true; }
};

//WDAQ WDB Packet Data - class for WDB UDP DAQ packets 
class WDAQWdbPacketData: public WDAQPacketData{
   //informations from packet header
   public:
   unsigned char    mADC;
   unsigned char    mChannel;
   unsigned int     mTxEnable;
   unsigned short   mZeroSuppressionMask;
   unsigned char    mWDBFlags;
   unsigned char    mTriggerSource;//serve?
   unsigned char    mBitsPerSample;//serve?
   unsigned short   mSamplesPerEventPerChannel;//serve?
   unsigned long    mTimeStamp;
   unsigned short   mTriggerCell;
   unsigned int     mSamplingFrequency;
   float            mTemperature;
   unsigned short   mDacOFS;
   unsigned short   mDacROFS;
   unsigned short   mFrontendSettings;
   
   //Set properties according to UDP event header
   void SetWdbHeaderInfo(FRAME_WDB_HEADER *);

   //merge this packet information in given board event, to be implemented according to data
   virtual bool AddDataToBoardEvent(WDAQBoardEvent *e) { return true; }

#ifdef USEMEMORYPOOL
   //memory pool operators
   void* operator new(size_t size);
   void operator delete(void* ptr);
#endif

   virtual ~WDAQWdbPacketData() { };
};

//WDAQ DRS Packet Data -  derived packet class to host DRS data
class WDAQDRSPacketData : public WDAQWdbPacketData{
public:
   float data[1024];

   //Add packet info to given Board Event
   bool AddDataToBoardEvent(WDAQBoardEvent *e);

#ifdef USEMEMORYPOOL
   //memory pool operators
   void* operator new(size_t size);
   void operator delete(void* ptr);
#endif

   virtual ~WDAQDRSPacketData() { };
};

//WDAQ ADC Packet Data -  derived packet class to host ADC data
class WDAQADCPacketData : public WDAQWdbPacketData{
public:
   unsigned short data[2048];

   //Add packet info to given Board Event
   bool AddDataToBoardEvent(WDAQBoardEvent *e);

#ifdef USEMEMORYPOOL
   //memory pool operators
   void* operator new(size_t size);
   void operator delete(void* ptr);
#endif

   virtual ~WDAQADCPacketData() { };
};

//WDAQ TDC Packet Data -  derived packet class to host TDC data
class WDAQTDCPacketData : public WDAQWdbPacketData{
public:
   unsigned char data[512];

   //Add packet info to given Board Event
   bool AddDataToBoardEvent(WDAQBoardEvent *e);

#ifdef USEMEMORYPOOL
   //memory pool operators
   void* operator new(size_t size);
   void operator delete(void* ptr);
#endif

   virtual ~WDAQTDCPacketData() { };
};

//WDAQ TRG Packet Data -  derived packet class to host TRG data
class WDAQTRGPacketData : public WDAQWdbPacketData{
public:
   unsigned long data[512];

   //Add packet info to given Board Event
   bool AddDataToBoardEvent(WDAQBoardEvent *e);

#ifdef USEMEMORYPOOL
   //memory pool operators
   void* operator new(size_t size);
   void operator delete(void* ptr);
#endif

   virtual ~WDAQTRGPacketData() { };
};

//WDAQ Scaler Packet Data -  derived packet class to host scaler
class WDAQScaPacketData : public WDAQWdbPacketData{
public:
  unsigned long data[WD_N_SCALER];

   //Add packet info to given Board Event
   bool AddDataToBoardEvent(WDAQBoardEvent *e);

#ifdef USEMEMORYPOOL
   //memory pool operators
   void* operator new(size_t size);
   void operator delete(void* ptr);
#endif

   virtual ~WDAQScaPacketData() { };
};

//WDAQ Dummy Packet Data -  derived packet class for fully zero suppressed board
class WDAQDummyPacketData : public WDAQWdbPacketData{
public:

   //Add packet info to given Board Event
   bool AddDataToBoardEvent(WDAQBoardEvent *e);

#ifdef USEMEMORYPOOL
   //memory pool operators
   void* operator new(size_t size);
   void operator delete(void* ptr);
#endif

   virtual ~WDAQDummyPacketData() { };
};

//WDAQ TCB Packet Data - class for TCB UDP DAQ packets 
class WDAQTcbPacketData: public WDAQPacketData{
   public:
   //informations from packet header
   std::array<char,4> mBankName;
   unsigned int       mTimeStamp;
   float              mTemperature;
   
   unsigned int     data[1024];//update this to match max event size
   //Set properties according to UDP event header
   void SetTcbHeaderInfo(FRAME_TCB_HEADER *);

   //merge this packet information in given board event, to be implemented according to data
   bool AddDataToBoardEvent(WDAQBoardEvent *e);

#ifdef USEMEMORYPOOL
   //memory pool operators
   void* operator new(size_t size);
   void operator delete(void* ptr);
#endif

   virtual ~WDAQTcbPacketData(){};
};

//WDAQ board event - Board Event class
class WDAQBoardEvent {
public:
   //from WDAQ header 
   unsigned char    mBoardType;
   unsigned char    mBoardRevision;
   unsigned short   mBoardId;
   unsigned short   mCrateId;
   unsigned short   mSlotId;
   unsigned short   mWDAQFlags;

   //event status
   bool             mComplete;
   bool             mEndFlagReceived;
   bool             mStartFlagReceived;
   int              mPacketsReceived;
   int              mFirstPacket;
   int              mLastPacket;

   bool IsComplete() { return mComplete; }
   void UpdateIsComplete();
   WDAQBoardEvent(WDAQPacketData* pkt);

#ifdef USEMEMORYPOOL
   //memory pool operators
   void* operator new(size_t size);
   void operator delete(void* ptr);
#endif

   virtual ~WDAQBoardEvent(){};
};

//WDB board event - WDB Board Event class
class WDAQWdbEvent : public WDAQBoardEvent {
public:
   //from WDB header 
   unsigned int     mSamplingFrequency;
   unsigned short   mWDBFlags;
   unsigned char    mTriggerSource;//serve?
   unsigned long    mTimeStamp;
   unsigned short   mDacOFS;
   unsigned short   mDacROFS;
   float            mTemperature;

   //set by Worker if temperature is not in calibration range
   bool             mTemperatureOk;

   //channel or data depenant
   unsigned short   mFrontendSettings[WD_N_CHANNELS];
   unsigned int     mTriggerCell[WD_N_CHANNELS];
   unsigned int     mDrsTxEnable;
   unsigned int     mAdcTxEnable;
   unsigned int     mTdcTxEnable;
   unsigned int     mTrgTxEnable;
   unsigned short   mDrsZeroSuppressionMask;
   unsigned short   mAdcZeroSuppressionMask;
   unsigned short   mTdcZeroSuppressionMask;
   
   float            mDrsU[WD_N_CHANNELS][1024];
   unsigned short   mAdcU[WD_N_CHANNELS-2][2048];
   unsigned char    mTdc[WD_N_CHANNELS-2][512];
   unsigned long    mTrg[512];
   unsigned long    mScaler[WD_N_SCALER];

   //event status
   bool             mVCalibrated;
   bool             mDrsHasData[WD_N_CHANNELS];
   int              mDrsByteNumber[WD_N_CHANNELS];
   bool             mAdcHasData[WD_N_CHANNELS];
   int              mAdcByteNumber[WD_N_CHANNELS];
   bool             mTdcHasData[WD_N_CHANNELS];
   int              mTdcByteNumber[WD_N_CHANNELS];
   bool             mTrgHasData;
   bool             mScalerHasData;
   int              mTrgByteNumber;

   float GetRange() {
      return (int)((0.68 - (mDacOFS/65535.0*2.5))*100)/100.0;
   };
   
   WDAQWdbEvent(WDAQPacketData* pkt);

#ifdef USEMEMORYPOOL
   //memory pool operators
   void* operator new(size_t size);
   void operator delete(void* ptr);
#endif

   virtual ~WDAQWdbEvent(){};
};

class WDAQTcbBank {
public:
   std::vector<unsigned int> data;
   std::array<char,4> fName;

   WDAQTcbBank(std::array<char,4> name){
      fName = name;
      data.clear();
      data.reserve(1000);//should be the max bank size to be matched with WDAQTcbPacket
   }

   void SetValues(unsigned long pos, unsigned long len, unsigned int *vals){
      //extends values if needed;
      if(pos+len >= data.size()) {
         //printf("from size %d to size %d\n", data.size(), pos+len+1);
         data.resize(pos+len);
      }
      for(int i=0; i<len; i++)
         data[pos+i] = vals[i];
   }

   unsigned long GetSize(){
      return data.size();
   }

#ifdef USEMEMORYPOOL
   //memory pool operators
   void* operator new(size_t size);
   void operator delete(void* ptr);
#endif
};

//TCB board event - TCB Board Event class
class WDAQTcbEvent : public WDAQBoardEvent {
public:
   //from TCB header 
   unsigned long    mTimeStamp;
   float            mTemperature;

   //data
   std::map<std::array<char,4>,WDAQTcbBank*>     mBanks;

   WDAQTcbEvent(WDAQPacketData* pkt);

   virtual ~WDAQTcbEvent(){
      for(auto i: mBanks)
         delete i.second;
      mBanks.clear();
   }

#ifdef USEMEMORYPOOL
   //memory pool operators
   void* operator new(size_t size);
   void operator delete(void* ptr);
#endif
};

//WDAQ Event - global DAQ event
class WDAQEvent {
public:
   unsigned int     mEventNumber;
   unsigned short   mTriggerNumber;
   unsigned short   mTriggerType;
   unsigned short   mSerialTriggerData;
   int              mCompletedBoards;

   // Monotonic counter assigned by the builder when this event is created, so "oldest
   // pending event" can mean what it says. The map is keyed on the event/trigger number,
   // and the smallest key is NOT the oldest entry once that counter resets at
   // begin-of-run. See HARDENING.md 2.1.
   unsigned long    mInsertionSeq;

   //map (BoardType -> map(BoardSerial -> Board))
   std::map<unsigned char, std::map<unsigned short, WDAQBoardEvent *>> fBoard;
   
   bool AddPacket(WDAQPacketData* pkt);
   void UpdateIsComplete();
   int IsComplete() { return mCompletedBoards; }
   
   //constructor
   WDAQEvent(WDAQPacketData* pkt);

   //destructor
   ~WDAQEvent();

#ifdef USEMEMORYPOOL
   //memory pool operators
   void* operator new(size_t size);
   void operator delete(void* ptr);
#endif
}; 

//---------- THREAD implementation -------
//Packet Collector - Thread to collect packets
#define WDAQ_UDP_PROTOCOL_VERSION  8

class WDAQPacketCollector: public DAQServerThread{
   DAQFanoutBuffer<WDAQPacketData> *fBuf;

   //statistics
   unsigned long fNPackets;
   unsigned long fCorruptedPackets;
   unsigned long fDroppedPackets;
   // Datagrams discarded from the kernel buffer at begin-of-run, i.e. the previous run's
   // backlog. Nonzero is normal; a large or growing value means the gap between runs is
   // letting a lot accumulate.
   unsigned long fStaleDatagrams;

   void Begin();

   void GotData();
   void PushPackets(std::vector<WDAQPacketData*> &);
   
   void End();

   public:
   WDAQPacketCollector(DAQFanoutBuffer<WDAQPacketData> *buf, int nBoards=1, DAQSystem* parent=nullptr): DAQServerThread(nBoards*1*1024*1024, parent, "PacketCollector"){ //  1*1MB/Board
      fBuf = buf;
      fNPackets = 0;
      fCorruptedPackets = 0;
      fDroppedPackets = 0;
      fStaleDatagrams = 0;
   }

   //Statistics getters
   unsigned long GetReceivedPackets() const { return fNPackets; }
   unsigned long GetCorruptedPackets() const { return fCorruptedPackets; }
   unsigned long GetDroppedPackets() const { return fDroppedPackets; }
   unsigned long GetStaleDatagrams() const { return fStaleDatagrams; }
};

// temporary thread to read TCB
class WDAQTCBReader: public DAQThread{
   DAQFanoutBuffer<WDAQPacketData> *fBuf;
   WDTCB *fBoard;

   void Begin();

   void Loop();
   
   void End();

   public:
   WDAQTCBReader(DAQFanoutBuffer<WDAQPacketData> *buf, WDTCB *board, DAQSystem* parent=nullptr) : DAQThread(parent, "TcbReader") {
      fBuf = buf;
      fBoard = board;
   }
};

//Event builder - Thread that build events from packets
class WDAQEventBuilder : public DAQThread{
   DAQBuffer<WDAQPacketData> *fSource;
   DAQBuffer<WDAQEvent> *fDestination;
   //structure to group together packets belonging to same event
   std::map<int, WDAQEvent*> fEvents;

   //number of boards to wait
   int           fNBoards;

   //statistics
   unsigned long fBuildedEvent;
   unsigned long fDroppedEvent;
   // Split out of the single fOldEvent counter, which conflated two very different
   // things and so could not distinguish healthy operation from a wedged builder:
   //   fReorderPurged      an event aged out because the stream moved past it. Normal
   //                       in small numbers; it is how incomplete events are reclaimed.
   //   fMapOverflowDropped the pending map hit its cap and something had to go. Always
   //                       a symptom -- events are arriving that cannot be completed.
   unsigned long fReorderPurged;
   unsigned long fMapOverflowDropped;
   unsigned long fBadPackets;
   // Assigns each pending event an arrival order, so the overflow guard can drop the
   // one that has actually been waiting longest rather than the smallest key.
   unsigned long fInsertionCounter;
   //flags
   bool          fNotBuilding;
   bool          fDropping;

   // Which packet field identifies the event this packet belongs to.
   //
   // Default is the trigger-bus number, which a TCB distributes so that every board
   // in a crate tags the same physical event identically. A board addressed directly
   // over Ethernet has no TCB, so trigger_information is always zero and every packet
   // would be keyed 0 -- all events collapse into one container, AddPacket() starts
   // refusing, and throughput dies. For that case key on the board's own event
   // counter instead, which increments correctly.
   //
   // Selected by the "BuilderKey" DAQ property: "TriggerNumber" (default) or
   // "EventNumber". Crate behaviour is unchanged unless it is set explicitly.
   bool          fKeyOnEventNumber;

   void Begin();

   void Loop();

   void End();

   public:
   WDAQEventBuilder(DAQBuffer<WDAQPacketData> *source, DAQBuffer<WDAQEvent> *destination, int nNBoards, DAQSystem* parent = nullptr): DAQThread(parent, "EventBuilder"){
      fSource = source;
      fDestination = destination;
      fNBoards = nNBoards;
      
      fBuildedEvent = 0;
      fDroppedEvent = 0;
      fBadPackets = 0;
      fReorderPurged = 0;
      fMapOverflowDropped = 0;
      fInsertionCounter = 0;
      fNotBuilding = false;
      fDropping = false;
      fKeyOnEventNumber = false;
   }

   // "TriggerNumber" (default) or "EventNumber" -- see fKeyOnEventNumber.
   void SetKeyOnEventNumber(bool flag){ fKeyOnEventNumber = flag; }
   bool GetKeyOnEventNumber() const { return fKeyOnEventNumber; }

   //building state getters
   bool GetIsNotBuilding() const { return fNotBuilding; }
   bool GetIsDropping() const { return fDropping; }

   //Statistics getters
   unsigned long GetBuildedEvents() const { return fBuildedEvent; }
   unsigned long GetDroppedEvents() const { return fDroppedEvent; }
   unsigned long GetBadPackets() const { return fBadPackets; }
   // Unchanged meaning and unchanged callers: the total of both drop reasons.
   unsigned long GetOldEvents() const { return fReorderPurged + fMapOverflowDropped; }
   // Use these to tell a healthy purge from a wedge -- see the member comments.
   unsigned long GetReorderPurged() const { return fReorderPurged; }
   unsigned long GetMapOverflowDropped() const { return fMapOverflowDropped; }
   unsigned long GetEventsInQueue() const { return fEvents.size(); }
};

//Event worker - Thread that calibrate events
class WDAQWorker : public DAQThread{
   DAQBuffer<WDAQEvent> *fSource;
   DAQBuffer<WDAQEvent> *fDestination;

   //map for time bins
   std::map<int, VCALIB*> fVCalib;

   //statistics
   unsigned long fNEvent;
   unsigned long fDroppedEvent;

   //single board calibration
   void calibrateBoard(WDAQWdbEvent *ev);

   void Begin();

   void Loop();

   void End();

   public:
   void AddVoltageCalibration(int id, VCALIB *calib){
         fVCalib[id] = calib;
   }

   unsigned long GetDroppedEvents() const { return fDroppedEvent; }

   WDAQWorker(DAQBuffer<WDAQEvent> *source, DAQBuffer<WDAQEvent> *destination, DAQSystem* parent = nullptr): DAQThread(parent, "Worker"){
      fSource = source;
      fDestination = destination;
   }

   ~WDAQWorker(){
   }

};


//Event writer - Thread that writes event to file
class WDAQEventWriter : public DAQThread{
   DAQBuffer<WDAQEvent> *fSource;

   //map for time bins
   std::map<int, TCALIB*> fTCalib;

   //vetor to hold tcb numbers
   std::vector<int> fTCBList;

   //output file data
   std::string fFileName;
   std::ofstream fFile;
   unsigned int fRunNumber;

   //statistics
   unsigned long fNEvent;
   unsigned long fLastEvent;

   //event per file
   unsigned int fEventsPerFile;

   void Begin();

   void Loop();

   void End();

   //write run header to file
   void WriteRunHeader();

   //return current file name inserting runnumber
   std::string GetFileName();

   public:
   void AddTimeCalibration(int id, TCALIB *calib){
         fTCalib[id] = calib;
   }
   void AddTcbName(int id){
         fTCBList.push_back(id);
   }

   WDAQEventWriter(DAQBuffer<WDAQEvent> *source, std::string file, unsigned int eventsPerFile = 0, unsigned int startRunNumber = 0, DAQSystem* parent = nullptr) : DAQThread(parent, "EventWriter"){
      fSource = source;
      fFileName = file;
      fEventsPerFile = eventsPerFile;
      fRunNumber = startRunNumber;

      fNEvent = 0;
      fLastEvent = 0;
   }

   ~WDAQEventWriter(){
   }

};

#endif

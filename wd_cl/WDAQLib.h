#include "DAQLib.h"
#include "WDBLib.h"
#include <cmath>
#include <list>
#include <iostream>
#include <fstream>

#define EOE 1
#define SOE 2
#define EOT 4
#define SOT 8

class WDAQBoardEvent;

//WDAQ Packet Data - class for UDP DAQ packets 
class WDAQPacketData{
   //informations from packet header
   public:
   unsigned short   mBoardId;
   unsigned short   mCrateId;
   unsigned short   mSlotId;
   unsigned char    mADC;
   unsigned char    mChannel;
   unsigned short   mPacketNumber;
   unsigned char    mDataType;
   unsigned int     mTxEnable;
   unsigned short   mZeroSuppressionMask;
   unsigned short   mFlags;
   unsigned char    mTriggerSource;//serve?
   unsigned char    mBitsPerSample;//serve?
   unsigned short   mSamplesPerEventPerChannel;//serve?
   unsigned short   mPayloadLenght;//serve?
   unsigned short   mDataOffset;
   unsigned char    mTimeStamp[8];
   unsigned int     mEventNumber;
   //unsigned char    mTriggerInfo[6];
   unsigned char    mTriggerType;
   unsigned int     mTriggerNumber;
   unsigned short   mTriggerCell;
   unsigned int     mSamplingFrequency;
   float            mTemperature;
   unsigned short   mDacOFS;
   unsigned short   mDacROFS;
   unsigned short   mFrontendSettings;
   
   //Set properties according to UDP event header
   void SetEventHeaderInfo(WD_FRAME_HEADER *, WDAQ_FRAME_HEADER *);

   //merge this packet information in given board event, to be implemented according to data
   virtual void AddToBoardEvent(WDAQBoardEvent *e) { };

   virtual ~WDAQPacketData() { };
};

//WDAQ DRS Packet Data -  derived packet class to host DRS data
class WDAQDRSPacketData : public WDAQPacketData{
public:
   float data[1024];

   //Add packet info to given Board Event
   void AddToBoardEvent(WDAQBoardEvent *e);

   ~WDAQDRSPacketData() { };
};

//WDAQ ADC Packet Data -  derived packet class to host ADC data
class WDAQADCPacketData : public WDAQPacketData{
public:
   unsigned short data[1024];

   //Add packet info to given Board Event
   void AddToBoardEvent(WDAQBoardEvent *e);

   ~WDAQADCPacketData() { };
};

//WDAQ TDC Packet Data -  derived packet class to host TDC data
class WDAQTDCPacketData : public WDAQPacketData{
public:
   unsigned char data[512];

   //Add packet info to given Board Event
   void AddToBoardEvent(WDAQBoardEvent *e);

   ~WDAQTDCPacketData() { };
};

//WDAQ TRG Packet Data -  derived packet class to host TRG data
class WDAQTRGPacketData : public WDAQPacketData{
public:
   unsigned long data[512];

   //Add packet info to given Board Event
   void AddToBoardEvent(WDAQBoardEvent *e);

   ~WDAQTRGPacketData() { };
};

//WDAQ Scaler Packet Data -  derived packet class to host scaler
class WDAQScaPacketData : public WDAQPacketData{
public:
   unsigned long data[18];

   //Add packet info to given Board Event
   void AddToBoardEvent(WDAQBoardEvent *e);

   ~WDAQScaPacketData() { };
};

//WDAQ Dummy Packet Data -  derived packet class for fully zero suppressed board
class WDAQDummyPacketData : public WDAQPacketData{
public:

   //Add packet info to given Board Event
   void AddToBoardEvent(WDAQBoardEvent *e);

   ~WDAQDummyPacketData() { };
};

//WDAQ board event - Board Event class
class WDAQBoardEvent {
public:
   //from header 
   unsigned short   mBoardId;
   unsigned short   mCrateId;
   unsigned short   mSlotId;
   unsigned short   mSamplingFrequency;
   unsigned short   mFlags;
   unsigned char    mTriggerSource;//serve?
   unsigned char    mTimeStamp[8];
   unsigned short   mDacOFS;
   unsigned short   mDacROFS;
   float            mTemperature;

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
   unsigned long    mScaler[WD_N_CHANNELS];

   //event status
   bool             mVCalibrated;
   bool             mEndFlagReceived;
   bool             mStartFlagReceived;
   int              mPacketsReceived;
   int              mFirstPacket;
   int              mLastPacket;
   bool             mDrsHasData[WD_N_CHANNELS];
   int              mDrsByteNumber[WD_N_CHANNELS];
   bool             mAdcHasData[WD_N_CHANNELS];
   int              mAdcByteNumber[WD_N_CHANNELS];
   bool             mTdcHasData[WD_N_CHANNELS];
   int              mTdcByteNumber[WD_N_CHANNELS];
   bool             mTrgHasData;
   int              mTrgByteNumber;

   bool IsComplete();
   float GetRange() {
      return (int)((0.68 - (mDacOFS/65535.0*2.5))*100)/100.0;
   };
   
   WDAQBoardEvent(WDAQPacketData* pkt);
};

//WDAQ Event - global DAQ event
class WDAQEvent {
public:
   unsigned int     mEventNumber;
   unsigned short   mTriggerNumber;
   unsigned short   mTriggerType;
   std::map<unsigned short, WDAQBoardEvent *> fBoard;
   
   void AddPacket(WDAQPacketData* pkt);
   bool IsComplete();
   
   //constructor
   WDAQEvent(WDAQPacketData* pkt);

   //destructor
   ~WDAQEvent();

}; 

//---------- THREAD implementation -------
//Packet Collector - Thread to collect packets
#define WD2_UDP_PROTOCOL_VERSION  6

class WDAQPacketCollector: public DAQServerThread{
   DAQBuffer<WDAQPacketData> *fBuf;

   //statistics
   unsigned long fNPackets;
   unsigned long fDroppedPackets;

   void Begin();

   void GotData(int size, unsigned char* dataptr);
   
   void End();

   public:
   WDAQPacketCollector(DAQBuffer<WDAQPacketData> *buf){
      fBuf = buf;
      fNPackets = 0;
      fDroppedPackets = 0;
   }
};

//Event builder - Thread that build events from packets
class WDAQEventBuilder : public DAQThread{
   DAQBuffer<WDAQPacketData> *fSource;
   DAQBuffer<WDAQEvent> *fDestination;
   //structure to group together packets belonging to same event
   std::map<int, WDAQEvent*> fEvents;

   //statistics
   unsigned long fBuildedEvent;
   unsigned long fDroppedEvent;
   unsigned long fOldEvent;

   void Begin();

   void Loop();

   void End();

   public:
   WDAQEventBuilder(DAQBuffer<WDAQPacketData> *source, DAQBuffer<WDAQEvent> *destination){
      fSource = source;
      fDestination = destination;

      fBuildedEvent = 0;
      fDroppedEvent = 0;
      fOldEvent = 0;
   }
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
   void calibrateBoard(WDAQBoardEvent *ev);

   void Begin();

   void Loop();

   void End();

   public:
   void AddVoltageCalibration(int id, VCALIB *calib){
         fVCalib[id] = calib;
   }

   WDAQWorker(DAQBuffer<WDAQEvent> *source, DAQBuffer<WDAQEvent> *destination){
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

   //output file data
   std::string fFileName;
   std::ofstream fFile;

   //statistics
   unsigned long fNEvent;
   unsigned long fLastEvent;

   void Begin();

   void Loop();

   void End();

   public:
   void AddTimeCalibration(int id, TCALIB *calib){
         fTCalib[id] = calib;
   }

   WDAQEventWriter(DAQBuffer<WDAQEvent> *source, std::string file){
      fSource = source;
      fFileName = file;
   }

   ~WDAQEventWriter(){
   }

};


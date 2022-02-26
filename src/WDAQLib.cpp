#include "WDLib.h"
#include "WDAQLib.h"

#ifdef USEMEMORYPOOL
//Memory pool template specializations
template class DAQMemoryPool<WDAQPacketData>;
template class DAQMemoryPool<WDAQWdbPacketData>;
template class DAQMemoryPool<WDAQDRSPacketData>;
template class DAQMemoryPool<WDAQADCPacketData>;
template class DAQMemoryPool<WDAQTDCPacketData>;
template class DAQMemoryPool<WDAQTRGPacketData>;
template class DAQMemoryPool<WDAQScaPacketData>;
template class DAQMemoryPool<WDAQDummyPacketData>;
template class DAQMemoryPool<WDAQTcbPacketData>;
template class DAQMemoryPool<WDAQBoardEvent>;
template class DAQMemoryPool<WDAQWdbEvent>;
template class DAQMemoryPool<WDAQTcbBank>;
template class DAQMemoryPool<WDAQTcbEvent>;
template class DAQMemoryPool<WDAQEvent>;
#endif

//WDAQ Packet Data - class for UDP DAQ packets 
//Set properties according to UDP event header
void WDAQPacketData::SetEventHeaderInfo(FRAME_WDAQ_HEADER *pdaqh){
   mProtocolVersion =  pdaqh->protocol_version;
   mBoardType = pdaqh->board_type_revision >> 4;
   mBoardRevision = pdaqh->board_type_revision & 0xF;
   mBoardId = pdaqh->serial_number; // gets board Id (i.e. serial number)
   mCrateId = pdaqh->crate_id;      // gets crate Id
   mSlotId  = pdaqh->slot_id;       // gets slot Id 
   mPacketNumber = pdaqh->packet_number; // packet number
   mDataType = pdaqh->data_type; // type of data in the packet
   mWDAQFlags = pdaqh->wdaq_flags;
   mPayloadLength = pdaqh->payload_length;
   mDataOffset = pdaqh->data_chunk_offset;
   mEventNumber = pdaqh->event_number;
   mTriggerNumber = pdaqh->trigger_information[5] | (pdaqh->trigger_information[4] << 8);
   mTriggerType = pdaqh->trigger_information[1] | (pdaqh->trigger_information[0] << 8);
   mSerialTriggerData = pdaqh->trigger_information[3] | (pdaqh->trigger_information[2] << 8);
   mEventNumber = pdaqh->event_number;
}
//Set WDAQBoardEvent header from Packet Data
void WDAQPacketData::HeaderToBoardEvent(WDAQBoardEvent *e){
   //check if end of event is received
   if(mWDAQFlags & EOE) {
     e->mEndFlagReceived = true;
     e->mLastPacket = mPacketNumber;
   }
   // the packet number offset is from the first packet
   if(mWDAQFlags & SOE) {
     e->mStartFlagReceived = true;
     e->mFirstPacket = mPacketNumber;
   }

   //anyway increase packet counter
   e->mPacketsReceived++;
}

#ifdef USEMEMORYPOOL
//memory pool operators
void* WDAQPacketData::operator new(size_t size){
   auto& mp = DAQMemoryPool<WDAQPacketData>::GetInstance();
   return mp.Allocate();
}

void WDAQPacketData::operator delete(void* ptr){
   auto& mp = DAQMemoryPool<WDAQPacketData>::GetInstance();
   mp.Deallocate(ptr);
}
#endif

//WDAQ WDB Packet Data - class for WDB UDP DAQ packets 
//Set properties according to UDP event header
void WDAQWdbPacketData::SetWdbHeaderInfo(FRAME_WDB_HEADER *ph){

  mTemperature = std::round(ph->temperature*0.0625 * 10 + 0.5) / 10.0f;
  mChannel = (ph->channel_info &0x1F); 
  mADC = (ph->channel_info >> 7) & 0x01; //which ADC sampled the data
  mTxEnable = ph->tx_enable; // DRS transmission enble mask
  mZeroSuppressionMask = ph->zero_suppression_mask; // mask for zero suppression
  mWDBFlags = ph->wd_flags;
  mTriggerSource = ph->trigger_source;
  mBitsPerSample = ph->bits_per_sample;
  mSamplesPerEventPerChannel = ph->samples_per_event_per_channel;
  mTimeStamp = ph->time_stamp;
  mTriggerCell = ph->drs_trigger_cell;
  mSamplingFrequency = ph->sampling_frequency;
  mDacOFS = ph->dac_ofs;
  mDacROFS = ph->dac_rofs;
  mFrontendSettings = ph->frontend_settings;
}

#ifdef USEMEMORYPOOL
//memory pool operators
void* WDAQWdbPacketData::operator new(size_t size){
   auto& mp = DAQMemoryPool<WDAQWdbPacketData>::GetInstance();
   return mp.Allocate();
}

void WDAQWdbPacketData::operator delete(void* ptr){
   auto& mp = DAQMemoryPool<WDAQWdbPacketData>::GetInstance();
   mp.Deallocate(ptr);
}
#endif

//WDAQ DRS Packet Data -  derived packet class to host DRS data
//Add packet info to given Board Event
bool WDAQDRSPacketData::AddDataToBoardEvent(WDAQBoardEvent *e){
   //Should check e->mBoardType is WDB 
   WDAQWdbEvent *wdb_e = static_cast<WDAQWdbEvent*>(e);

   //int channel = (mChannel!=8)? mChannel+8*mADC : 16+mADC;//arrange clock channel
   int channel = mChannel;
   int numberBins = (int) mPayloadLength / 1.5;
   int firstBin = mDataOffset / 1.5;

   if((firstBin + numberBins) > 1024 || channel >= WD_N_CHANNELS)
      return false;

   for(int i=0; i<numberBins; i++){
      wdb_e->mDrsU[channel][firstBin+i] = data[i];
   }

   wdb_e->mFrontendSettings[channel] = mFrontendSettings;
   wdb_e->mTriggerCell[channel] = mTriggerCell;
   wdb_e->mDrsTxEnable = mTxEnable;
   wdb_e->mDrsZeroSuppressionMask = mZeroSuppressionMask;
   wdb_e->mSamplingFrequency = mSamplingFrequency;
   wdb_e->mTriggerSource = mTriggerSource;
   wdb_e->mTimeStamp = mTimeStamp;
   wdb_e->mDacOFS = mDacOFS;
   wdb_e->mDacROFS = mDacROFS;
   wdb_e->mTemperature = mTemperature;
   wdb_e->mWDBFlags = mWDBFlags;

   //check all data received
   wdb_e->mDrsByteNumber[channel] += mPayloadLength*8;
   if(wdb_e->mDrsByteNumber[channel] >= mSamplesPerEventPerChannel*mBitsPerSample){
   // set the flag of drs channel data reception for the writer
     wdb_e->mDrsHasData[channel] = true; 
   }

   return true;

}

#ifdef USEMEMORYPOOL
//memory pool operators
void* WDAQDRSPacketData::operator new(size_t size){
   auto& mp = DAQMemoryPool<WDAQDRSPacketData>::GetInstance();
   return mp.Allocate();
}

void WDAQDRSPacketData::operator delete(void* ptr){
   auto& mp = DAQMemoryPool<WDAQDRSPacketData>::GetInstance();
   mp.Deallocate(ptr);
}
#endif

//WDAQ ADC Packet Data -  derived packet class to host ADC data
//Add packet info to given Board Event
bool WDAQADCPacketData::AddDataToBoardEvent(WDAQBoardEvent *e){
   //Should check e->mBoardType is WDB 
   WDAQWdbEvent *wdb_e = static_cast<WDAQWdbEvent*>(e);

   int channel = mChannel;
   int numberBins = (int) mPayloadLength / 1.5;
   int firstBin = mDataOffset / 1.5;

   if((firstBin + numberBins) > 2048 || channel >= (WD_N_CHANNELS-2))
      return false;

   for(int i=0; i<numberBins; i++){
      wdb_e->mAdcU[channel][firstBin+i] = data[i];
   }

   wdb_e->mAdcTxEnable = mTxEnable;
   wdb_e->mAdcZeroSuppressionMask = mZeroSuppressionMask;

   //check all data received
   wdb_e->mAdcByteNumber[channel] += mPayloadLength*8;
   if(wdb_e->mAdcByteNumber[channel] >= mSamplesPerEventPerChannel*mBitsPerSample){
     // set the flag of adc channel data reception for the writer
      wdb_e->mAdcHasData[channel] = true; 
   }

   return true;
}

#ifdef USEMEMORYPOOL
//memory pool operators
void* WDAQADCPacketData::operator new(size_t size){
   auto& mp = DAQMemoryPool<WDAQADCPacketData>::GetInstance();
   return mp.Allocate();
}

void WDAQADCPacketData::operator delete(void* ptr){
   auto& mp = DAQMemoryPool<WDAQADCPacketData>::GetInstance();
   mp.Deallocate(ptr);
}
#endif

//WDAQ TDC Packet Data -  derived packet class to host TDC data
//Add packet info to given Board Event
bool WDAQTDCPacketData::AddDataToBoardEvent(WDAQBoardEvent *e){
   //Should check e->mBoardType is WDB 
   WDAQWdbEvent *wdb_e = static_cast<WDAQWdbEvent*>(e);

   int channel = mChannel;
   int numberBins = (int) mPayloadLength;
   int firstBin = mDataOffset;

   if((firstBin + numberBins) > 512 || channel >= (WD_N_CHANNELS-2))
      return false;

   for(int i=0; i<numberBins; i++){
      wdb_e->mTdc[channel][firstBin+i] = data[i];
   }

   wdb_e->mTdcTxEnable = mTxEnable;
   wdb_e->mTdcZeroSuppressionMask = mZeroSuppressionMask;

   //check all data received
   wdb_e->mTdcByteNumber[channel] += mPayloadLength*8;
   if(wdb_e->mTdcByteNumber[channel] >= mSamplesPerEventPerChannel*mBitsPerSample){
   // set the flag of tdc channel data reception for the writer
     wdb_e->mTdcHasData[channel] = true; 
   }

   return true;
}

#ifdef USEMEMORYPOOL
//memory pool operators
void* WDAQTDCPacketData::operator new(size_t size){
   auto& mp = DAQMemoryPool<WDAQTDCPacketData>::GetInstance();
   return mp.Allocate();
}

void WDAQTDCPacketData::operator delete(void* ptr){
   auto& mp = DAQMemoryPool<WDAQTDCPacketData>::GetInstance();
   mp.Deallocate(ptr);
}
#endif

//WDAQ TRG Packet Data -  derived packet class to host TRG data
//Add packet info to given Board Event
bool WDAQTRGPacketData::AddDataToBoardEvent(WDAQBoardEvent *e){
   //Should check e->mBoardType is WDB 
   WDAQWdbEvent *wdb_e = static_cast<WDAQWdbEvent*>(e);

   int numberBins = (int) mPayloadLength/8;
   int firstBin = mDataOffset/8;

   if((firstBin + numberBins) > 512)
      return false;

   for(int i=0; i<numberBins; i++){
      wdb_e->mTrg[firstBin+i] = data[i];
   }

   wdb_e->mTrgTxEnable = 0; //this must be changed with proper TRG data treatment
      
   //check all data received
   wdb_e->mTrgByteNumber += mPayloadLength*8;
   if(wdb_e->mTrgByteNumber >= mSamplesPerEventPerChannel*mBitsPerSample){
   // set the flag of trigger data reception for the writer
     wdb_e->mTrgHasData = true; 
   }

   return true;
}

#ifdef USEMEMORYPOOL
//memory pool operators
void* WDAQTRGPacketData::operator new(size_t size){
   auto& mp = DAQMemoryPool<WDAQTRGPacketData>::GetInstance();
   return mp.Allocate();
}

void WDAQTRGPacketData::operator delete(void* ptr){
   auto& mp = DAQMemoryPool<WDAQTRGPacketData>::GetInstance();
   mp.Deallocate(ptr);
}
#endif

//WDAQ Scaler Packet Data -  derived packet class to host Scaler data
//Add packet info to given Board Event
bool WDAQScaPacketData::AddDataToBoardEvent(WDAQBoardEvent *e){
   //Should check e->mBoardType is WDB 
   WDAQWdbEvent *wdb_e = static_cast<WDAQWdbEvent*>(e);

   wdb_e->mTimeStamp = mTimeStamp;
   for(int i=0; i<WD_N_SCALER; i++){
      wdb_e->mScaler[i] = data[i];
   }
   // set the flag of scaler reception for the writer
   wdb_e->mScalerHasData = true; 

   return true;
}

#ifdef USEMEMORYPOOL
//memory pool operators
void* WDAQScaPacketData::operator new(size_t size){
   auto& mp = DAQMemoryPool<WDAQScaPacketData>::GetInstance();
   return mp.Allocate();
}

void WDAQScaPacketData::operator delete(void* ptr){
   auto& mp = DAQMemoryPool<WDAQScaPacketData>::GetInstance();
   mp.Deallocate(ptr);
}
#endif

//WDAQ Dummy Packet Data -  derived packet class to host zero-suppressed data
//Add packet info to given Board Event: this packet is EMPTY
// this board has been fully zero suppressed
bool WDAQDummyPacketData::AddDataToBoardEvent(WDAQBoardEvent *e){
   return true;
}

#ifdef USEMEMORYPOOL
//memory pool operators
void* WDAQDummyPacketData::operator new(size_t size){
   auto& mp = DAQMemoryPool<WDAQDummyPacketData>::GetInstance();
   return mp.Allocate();
}

void WDAQDummyPacketData::operator delete(void* ptr){
   auto& mp = DAQMemoryPool<WDAQDummyPacketData>::GetInstance();
   mp.Deallocate(ptr);
}
#endif

//WDAQ TCB Packet Data - class for TCB UDP DAQ packets 
//Set properties according to UDP event header
void WDAQTcbPacketData::SetTcbHeaderInfo(FRAME_TCB_HEADER *ph){

   mBankName[3] = ph->bank_name[3];
   mBankName[2] = ph->bank_name[2];
   mBankName[1] = ph->bank_name[1];
   mBankName[0] = ph->bank_name[0];
   mTimeStamp = 0.;

}
//Add packet info to given Board Event
bool WDAQTcbPacketData::AddDataToBoardEvent(WDAQBoardEvent *e){
   //Should check e->mBoardType is TCB 
   WDAQTcbEvent *tcb_e = static_cast<WDAQTcbEvent*>(e);
   
   //printf("additing event %c%c%c%c flags:%x size:%d offset:%d\n", mBankName[0], mBankName[1], mBankName[2], mBankName[3], mWDAQFlags, mPayloadLength, mDataOffset);

   int numberBins = (int) mPayloadLength/4;
   int firstBin = mDataOffset/4;
   WDAQTcbBank* bank;

   try{
      bank = tcb_e->mBanks.at(mBankName);
   }catch (const std::out_of_range&){
      bank = new WDAQTcbBank(mBankName);
      tcb_e->mBanks[mBankName] = bank;
   }

   bank->SetValues(firstBin, numberBins, data);
   //for(int i=0; i<bank->data.size(); i++)
   //   printf("%d: %08x\n", i, bank->data[i]);

   //tcb_e->UpdateIsComplete();
   //printf("TCB event is complete %d: %d %d %d %d\n", tcb_e->IsComplete(), tcb_e->mStartFlagReceived, tcb_e->mEndFlagReceived, tcb_e->mLastPacket-tcb_e->mFirstPacket+1, tcb_e->mPacketsReceived);

   return true;
}

#ifdef USEMEMORYPOOL
//memory pool operators
void* WDAQTcbPacketData::operator new(size_t size){
   auto& mp = DAQMemoryPool<WDAQTcbPacketData>::GetInstance();
   return mp.Allocate();
}

void WDAQTcbPacketData::operator delete(void* ptr){
   auto& mp = DAQMemoryPool<WDAQTcbPacketData>::GetInstance();
   mp.Deallocate(ptr);
}
#endif

//WDAQ Board Event - single board DAQ event
//Constructor, init from packet data
WDAQBoardEvent::WDAQBoardEvent(WDAQPacketData* pkt){
   mBoardType = pkt->mBoardType; 
   mBoardRevision = pkt->mBoardRevision;
   mWDAQFlags = pkt->mWDAQFlags;
   mBoardId = pkt->mBoardId;
   mCrateId = pkt->mCrateId;
   mSlotId = pkt->mSlotId;

   mComplete = false;
   mStartFlagReceived = false;
   mEndFlagReceived = false;
   mPacketsReceived = 0;
}

//check complete
void WDAQBoardEvent::UpdateIsComplete(){
   // check that all the packets are received:
   // start of the event is received
   // end of the event is received
   // check if last packet is smaller than first, in case sum to last 2^16

  if(mEndFlagReceived && mStartFlagReceived) {
    
    if(mLastPacket<mFirstPacket)
      mLastPacket += 65536;
    
    if(mLastPacket-mFirstPacket+1 == mPacketsReceived)
       mComplete = true;

  }
}

#ifdef USEMEMORYPOOL
//memory pool operators
void* WDAQBoardEvent::operator new(size_t size){
   auto& mp = DAQMemoryPool<WDAQBoardEvent>::GetInstance();
   return mp.Allocate();
}

void WDAQBoardEvent::operator delete(void* ptr){
   auto& mp = DAQMemoryPool<WDAQBoardEvent>::GetInstance();
   mp.Deallocate(ptr);
}
#endif

//WDAQ Wdb Event - single Wdb DAQ event
//Constructor, init from packet data
WDAQWdbEvent::WDAQWdbEvent(WDAQPacketData* pkt): WDAQBoardEvent(pkt){
   //reset status
   mVCalibrated = false;
   mTemperatureOk = false;
   mDrsTxEnable = 0;
   mAdcTxEnable = 0;
   mTdcTxEnable = 0;
   mTrgTxEnable = 0;
   for(int i=0; i<WD_N_CHANNELS; i++){
      mDrsHasData[i] = false;
      mAdcHasData[i] = false;
      mTdcHasData[i] = false;
      mDrsByteNumber[i] = 0;
      mAdcByteNumber[i] = 0;
      mTdcByteNumber[i] = 0;
   }
   mTrgHasData = false;
   mScalerHasData = false;
   mTrgByteNumber = 0;
}

#ifdef USEMEMORYPOOL
//memory pool operators
void* WDAQWdbEvent::operator new(size_t size){
   auto& mp = DAQMemoryPool<WDAQWdbEvent>::GetInstance();
   return mp.Allocate();
}

void WDAQWdbEvent::operator delete(void* ptr){
   auto& mp = DAQMemoryPool<WDAQWdbEvent>::GetInstance();
   mp.Deallocate(ptr);
}
#endif

//WDAQ Tcb Bank - single Tcb DAQ data bank
#ifdef USEMEMORYPOOL
//memory pool operators
void* WDAQTcbBank::operator new(size_t size){
   auto& mp = DAQMemoryPool<WDAQTcbBank>::GetInstance();
   return mp.Allocate();
}

void WDAQTcbBank::operator delete(void* ptr){
   auto& mp = DAQMemoryPool<WDAQTcbBank>::GetInstance();
   mp.Deallocate(ptr);
}
#endif

//WDAQ Tcb Event - single Tcb DAQ event
//Constructor, init from packet data
WDAQTcbEvent::WDAQTcbEvent(WDAQPacketData* pkt): WDAQBoardEvent(pkt){
   //should reset
}

#ifdef USEMEMORYPOOL
//memory pool operators
void* WDAQTcbEvent::operator new(size_t size){
   auto& mp = DAQMemoryPool<WDAQTcbEvent>::GetInstance();
   return mp.Allocate();
}

void WDAQTcbEvent::operator delete(void* ptr){
   auto& mp = DAQMemoryPool<WDAQTcbEvent>::GetInstance();
   mp.Deallocate(ptr);
}
#endif

//WDAQ Event - global DAQ event
//constructor, copies data from given packet
WDAQEvent::WDAQEvent(WDAQPacketData* pkt){

   //copies info from first packet
   mEventNumber = pkt->mEventNumber;
   mTriggerNumber = pkt->mTriggerNumber;
   mTriggerType = pkt->mTriggerType&0x3F;
   mSerialTriggerData = pkt->mSerialTriggerData;

   //reset event building informations
   mCompletedBoards = 0;
}

//add packet to event
bool WDAQEvent::AddPacket(WDAQPacketData* pkt){
   unsigned char type = pkt->mBoardType;
   unsigned short id = pkt->mBoardId;
   WDAQBoardEvent *boardEvent;
   //printf("Got Packet for event %d board type %d-%d\n", mEventNumber, type, id);

   try {
      boardEvent = fBoard.at(type).at(id);
   } catch (const std::out_of_range&){
      //no event, allocate a new one according to Board Type
      if(type == BRD_TYPE_ID_WDB){
         boardEvent = new WDAQWdbEvent(pkt);
         //printf("Event %d: Created WDB board event for board %d-%d\n", mEventNumber, type, id);
      } else if(type == BRD_TYPE_ID_TCB) {
         boardEvent = new WDAQTcbEvent(pkt);
         //printf("Event %d: Created TCB board event for board %d-%d\n", mEventNumber, type, id);
      } else {
         //no boards with given ID: bad packet
         return false;
         //boardEvent = new WDAQBoardEvent(pkt);
         //printf("Event %d: Created board event for board %d-%d\n", mEventNumber, type, id);
      }

      fBoard[type][id] = boardEvent;
   }

   //process packet content
   bool success = pkt->AddToBoardEvent(boardEvent);
   if(success){
      boardEvent->UpdateIsComplete();

      if(boardEvent->IsComplete()){
         //printf("event %d of board %d-%d is completed\n", mEventNumber, type, id);
         UpdateIsComplete();
      } 
   }
   return success;
}

//check event complete
void WDAQEvent::UpdateIsComplete(){
   int nboards = 0;

   for(auto &e1 :fBoard){
      for(auto &e2 :e1.second){
        //check only if end of event received
        if(e2.second->IsComplete())
           nboards++;
      }
   }

   mCompletedBoards = nboards;
}


//destructor to remove child WDBoardEvent
WDAQEvent::~WDAQEvent(){
   for(auto &e1 :fBoard)
      for(auto &e2 :e1.second)
         delete e2.second;
}

#ifdef USEMEMORYPOOL
//memory pool operators
void* WDAQEvent::operator new(size_t size){
   auto& mp = DAQMemoryPool<WDAQEvent>::GetInstance();
   return mp.Allocate();
}

void WDAQEvent::operator delete(void* ptr){
   auto& mp = DAQMemoryPool<WDAQEvent>::GetInstance();
   mp.Deallocate(ptr);
}
#endif


//---------- THREAD implementation -------

//Packet Collector - Thread to collect packets
//Reset statistics at begin
void WDAQPacketCollector::Begin(){
   //reset statistics
   fNPackets=0;
   fCorruptedPackets=0;
   fDroppedPackets=0;
}

//push a packet to the output buffer
void WDAQPacketCollector::PushPackets(std::vector<WDAQPacketData*> &packets){
   fNPackets += packets.size();

   std::vector<unsigned int> keys;
   keys.reserve(packets.size());
   for(auto &p: packets){
      keys.push_back(p->mTriggerNumber);
   }

   //push to buffer
   if(!fBuf->Try_push(packets, keys)){
      //could not push packet to buffer
      //printf("overflow pk\n");
      for(auto &p: packets){
         if(p != nullptr){
            fDroppedPackets++;
            delete p;
            p = nullptr;
         }
      }
   }
}

//called on every UDP packet
void WDAQPacketCollector::GotData(){
   unsigned int nmsg = GetMessages();
   std::vector<WDAQPacketData*> decodedPackets;
   decodedPackets.reserve(nmsg);

   for(unsigned int imsg=0; imsg<nmsg; imsg++){
      int size = GetMessageSize(imsg);
      unsigned char* dataptr = GetMessageData(imsg);

      //check size of received datagram
      if(size < (int)sizeof(FRAME_WDAQ_HEADER)) {
         char *ip = GetMessageSourceAddress(imsg);
         const std::string alarmMessage = "Message from " + std::string(ip) + ": Problem with size\n";
         //std::cout << alarmMessage << std::endl;
         if(! GetSystem()->GetAlarms()->Test(WDAQLIB_ERROR_CORRUPTEDPACKET)){
            GetSystem()->GetAlarms()->Trigger(WDAQLIB_ERROR_CORRUPTEDPACKET, alarmMessage);
         }

         fCorruptedPackets++;
         return;
      }

      //first link to the WDAQ_FRAME_HEADER
      FRAME_WDAQ_HEADER* daqdata = (FRAME_WDAQ_HEADER*)dataptr;


      // check protocol version
      if (daqdata->protocol_version != WDAQ_UDP_PROTOCOL_VERSION) {
         char *ip = GetMessageSourceAddress(imsg);
         //printf("Message from %s: received packet with wrong protocol version, got %d required %d\n", ip, daqdata->protocol_version, WDAQ_UDP_PROTOCOL_VERSION);
         const std::string alarmMessage = "Message from " + std::string(ip) + ": received packet with wrong protocol version";
         //std::cout << alarmMessage << std::endl;
         if(! GetSystem()->GetAlarms()->Test(WDAQLIB_ERROR_CORRUPTEDPACKET)){
            GetSystem()->GetAlarms()->Trigger(WDAQLIB_ERROR_CORRUPTEDPACKET, alarmMessage);
         }

         fCorruptedPackets++;
         return;
      }
      //correct endianess
      daqdata->serial_number               = SWAP_UINT16(daqdata->serial_number);
      daqdata->payload_length              = SWAP_UINT16(daqdata->payload_length);
      daqdata->packet_number               = SWAP_UINT16(daqdata->packet_number);
      daqdata->data_chunk_offset           = SWAP_UINT16(daqdata->data_chunk_offset);
      daqdata->event_number                = SWAP_UINT32(daqdata->event_number);

      //#define DEBUGGOT 
      
#ifdef DEBUGGOT
      printf("---------------------------------\n");
      printf("---------------------------------\n");
      printf("serial number    \t %d\n", daqdata->serial_number);
      printf("board type & rev \t 0x%x\n", daqdata->board_type_revision);
      if(daqdata->board_type_revision>>4 == BRD_TYPE_ID_WDB) 
         printf("                 \t WDB!\n");
      else if(daqdata->board_type_revision>>4 == BRD_TYPE_ID_TCB) 
         printf("                 \t TCB!\n");

      printf("packet num       \t %d\n", daqdata->packet_number);
      printf("flags            \t %d\n", daqdata->wdaq_flags);
      if(daqdata->wdaq_flags & SOE)
         printf("                 \t SOE\n");
      if(daqdata->wdaq_flags & EOE)
         printf("                 \t EOE\n");

      printf("payload length   \t %d\n", daqdata->payload_length);
      printf("data chunk off   \t %d\n", daqdata->data_chunk_offset);
      printf("data type        \t 0x%x\n", daqdata->data_type);
      if(daqdata->data_type == cDataTypeDRS)
         printf("                 \t DRS!\n");
      else if(daqdata->data_type == cDataTypeADC)
         printf("                 \t ADC!\n");
      else if(daqdata->data_type == cDataTypeTDC)
         printf("                 \t TDC!\n");
      else if(daqdata->data_type == cDataTypeTrg)
         printf("                 \t Trg!\n");
      else if(daqdata->data_type == cDataTypeScaler)
         printf("                 \t Scaler!\n");
      else if(daqdata->data_type == cDataTypeDummy)
         printf("                 \t Dummy!\n");
      else if(daqdata->data_type == cDataTypeTCB)
         printf("                 \t TCB!\n");

      printf("\n");
      printf("event number     \t %d\n", daqdata->event_number);
      printf("trigger event    \t %d\n", daqdata->trigger_information[5] | (daqdata->trigger_information[4] << 8));
      printf("trigger data     \t %d\n", daqdata->trigger_information[3] | (daqdata->trigger_information[2] << 8));
      printf("trigger type     \t %d\n", daqdata->trigger_information[1] | (daqdata->trigger_information[0] << 8));
      
#endif

      //from WDB
      if(daqdata->board_type_revision>>4 == BRD_TYPE_ID_WDB){
         //then do the WD_FRAME_HEADER
         FRAME_WDB_HEADER* data = (FRAME_WDB_HEADER*) (dataptr + sizeof(FRAME_WDAQ_HEADER));

         //correct endianess
         data->tx_enable                      = SWAP_UINT32(data->tx_enable);
         data->zero_suppression_mask          = SWAP_UINT16(data->zero_suppression_mask);
         data->samples_per_event_per_channel  = SWAP_UINT16(data->samples_per_event_per_channel);
         data->drs_trigger_cell               = SWAP_UINT16(data->drs_trigger_cell);
         data->sampling_frequency             = SWAP_UINT32(data->sampling_frequency);
         data->temperature                    = SWAP_UINT16(data->temperature);
         data->dac_ofs                        = SWAP_UINT16(data->dac_ofs);
         data->dac_rofs                       = SWAP_UINT16(data->dac_rofs);
         data->frontend_settings              = SWAP_UINT16(data->frontend_settings);
         data->time_stamp                     = SWAP_UINT64(data->time_stamp);


#ifdef DEBUGGOT
         printf("tx enable        \t 0x%x\n", data->tx_enable);
         printf("zero supp mask   \t 0x%d\n", data->zero_suppression_mask);
         printf("sampl  ev cha    \t %d\n", data->samples_per_event_per_channel);
         printf("drs trig cell    \t %d\n", data->drs_trigger_cell);
         printf("sampl freq       \t %d\n", data->sampling_frequency);
         printf("temperature      \t %d\n", data->temperature);
         printf("dac ofs          \t %d\n", data->dac_ofs);
         printf("daq rofs         \t %x\n", data->dac_rofs);
         printf("frontend sets    \t %x\n", data->frontend_settings);
         printf("flags            \t %x\n", data->wd_flags);
         printf("\n");
         printf("\n");
#endif

         //check payload lenght
         if(size != sizeof(FRAME_WDAQ_HEADER) + sizeof(FRAME_WDB_HEADER) + daqdata->payload_length ){
            char *ip = GetMessageSourceAddress(imsg);
            //printf("Message from %s: size %u expected %u + %u + %u\n", ip, size, sizeof(FRAME_WDAQ_HEADER), sizeof(FRAME_WDB_HEADER), daqdata->payload_length);
            const std::string alarmMessage = "Message from " + std::string(ip) + ": received packet with wrong size";
            //std::cout << alarmMessage << std::endl;
            if(! GetSystem()->GetAlarms()->Test(WDAQLIB_ERROR_CORRUPTEDPACKET)){
               GetSystem()->GetAlarms()->Trigger(WDAQLIB_ERROR_CORRUPTEDPACKET, alarmMessage);
            }

            fCorruptedPackets++;
            return;
         }

         if(daqdata->data_type == cDataTypeDRS){
            //DRS Data
            //create new packet
            WDAQDRSPacketData *packet = new WDAQDRSPacketData();
            packet->SetEventHeaderInfo(daqdata);
            packet->SetWdbHeaderInfo(data);

            // decode waveform data
            auto pd = (unsigned char*)(data+1);
            int numberBins = (int) packet->mPayloadLength / 1.5;
            for (int i=0 ; i<numberBins ; i+=2) {
               short data1   = ((pd[1] & 0x0F) << 8) | pd[0];
               short data2 = ((unsigned short)pd[2] << 4) | (pd[1] >> 4);
               // subtract binary offset
               data1 -= 0x800;
               data2 -= 0x800;
               pd+=3;

               // first segment
               packet->data[i]         = (float)data1 * (1 / 4096.0); // 1V DRS range with 12 bits
               packet->data[i+1]       = (float)data2 * (1 / 4096.0);
            }

            //PushPacket(packet);
            decodedPackets.push_back(packet);

         } else if (daqdata->data_type == cDataTypeADC){
            //ADC Data

            //create new packet
            WDAQADCPacketData *packet = new WDAQADCPacketData();
            packet->SetEventHeaderInfo(daqdata);
            packet->SetWdbHeaderInfo(data);

            // decode waveform data
            auto pd = (unsigned char*)(data+1);
            int numberBins = (int) packet->mPayloadLength / 1.5;
            for (int i=0 ; i<numberBins ; i+=2) {
               unsigned short data1   = ((pd[1] & 0x0F) << 8) | pd[0];
               unsigned short data2 = ((unsigned short)pd[2] << 4) | (pd[1] >> 4);
               pd+=3;

               // first segment
               packet->data[i]         = data1; // 1V DRS range with 12 bits
               packet->data[i+1]       = data2;
            }

            //PushPacket(packet);
            decodedPackets.push_back(packet);
         } else if (daqdata->data_type == cDataTypeTDC){
            //TDC Data

            //create new packet
            WDAQTDCPacketData *packet = new WDAQTDCPacketData();
            packet->SetEventHeaderInfo(daqdata);
            packet->SetWdbHeaderInfo(data);

            // decode waveform data
            auto pd = (unsigned char*)(data+1);
            int numberBins = (int) packet->mPayloadLength;
            for (int i=0 ; i<numberBins ; i++) {
               packet->data[i] = pd[i];
            }

            //PushPacket(packet);
            decodedPackets.push_back(packet);
         } else if (daqdata->data_type == cDataTypeTrg){
            //TRG Data
            //create new packet
            WDAQTRGPacketData *packet = new WDAQTRGPacketData();
            packet->SetEventHeaderInfo(daqdata);
            packet->SetWdbHeaderInfo(data);

            // decode waveform data
            auto pd = (uint64_t*)(data+1);
            int numberBins = (int) packet->mPayloadLength/8;
            for (int i=0 ; i<numberBins ; i++) {
               packet->data[i] = SWAP_UINT64(pd[i]);
            }

            //PushPacket(packet);
            decodedPackets.push_back(packet);
         } else if (daqdata->data_type == cDataTypeScaler) {
            //Scaler data
            //create new packet
            WDAQScaPacketData *packet = new WDAQScaPacketData();
            packet->SetEventHeaderInfo(daqdata);
            packet->SetWdbHeaderInfo(data);

            // decode waveform data
            auto pd = (uint64_t*)(data+1);
            for (int i=0 ; i<WD_N_SCALER ; i++) {//Ch 0->16, Trigger, External Clock
               packet->data[i] = SWAP_UINT64(pd[i]);
            }

            //PushPacket(packet);
            decodedPackets.push_back(packet);
         } else if (daqdata->data_type == cDataTypeDummy) {
            //Scaler data
            //create new packet
            WDAQDummyPacketData *packet = new WDAQDummyPacketData();
            packet->SetEventHeaderInfo(daqdata);
            packet->SetWdbHeaderInfo(data);

            //PushPacket(packet);
            decodedPackets.push_back(packet);

         }// end if data is dummy (completely zero suppressed)

      }else if(daqdata->board_type_revision>>4 == BRD_TYPE_ID_TCB) {
         //TCB board
         //then do the FRAME_TCB_HEADER
         FRAME_TCB_HEADER* tcbdata = (FRAME_TCB_HEADER*) (dataptr + sizeof(FRAME_WDAQ_HEADER));

         tcbdata->time_stamp       = SWAP_UINT32(tcbdata->time_stamp);
         tcbdata->temperature      = SWAP_UINT32(tcbdata->temperature);

#ifdef DEBUGGOT
         printf("bank name        \t %c%c%c%c\n", tcbdata->bank_name[0], tcbdata->bank_name[1], tcbdata->bank_name[2], tcbdata->bank_name[3]);
         printf("timestamp        \t 0x%x\n", tcbdata->time_stamp);
         printf("temperature      \t %d\n", tcbdata->temperature);
         printf("\n");
         printf("\n");
#endif

         //check payload lenght
         if(size != sizeof(FRAME_WDAQ_HEADER) + sizeof(FRAME_TCB_HEADER) + daqdata->payload_length ){
            char *ip = GetMessageSourceAddress(imsg);
            //printf("Message from %s: size %u expected %u + %u + %u\n", ip, size, sizeof(FRAME_WDAQ_HEADER), sizeof(FRAME_WDB_HEADER), daqdata->payload_length);
            const std::string alarmMessage = "Message from " + std::string(ip) + ": received packet with wrong size";
            std::cout << alarmMessage << std::endl;
            if(! GetSystem()->GetAlarms()->Test(WDAQLIB_ERROR_CORRUPTEDPACKET)){
               GetSystem()->GetAlarms()->Trigger(WDAQLIB_ERROR_CORRUPTEDPACKET, alarmMessage);
            }

            fCorruptedPackets++;
            return;
         }

         if(daqdata->data_type == cDataTypeTCB) {
            WDAQTcbPacketData *packet = new WDAQTcbPacketData();
            packet->SetEventHeaderInfo(daqdata); 
            packet->SetTcbHeaderInfo(tcbdata);

            auto pd = (unsigned int*)(tcbdata+1);
            int numberBins = (int) packet->mPayloadLength/4;
            for (int i=0 ; i<numberBins ; i++) {
               //printf("%d: %08x\n", i, SWAP_UINT32(pd[i]));
               packet->data[i] = SWAP_UINT32(pd[i]);
            }

            //PushPacket(packet);
            decodedPackets.push_back(packet);
         }

      }
   }
   PushPackets(decodedPackets);
}

//print statistics at thread end
void WDAQPacketCollector::End(){
   Clean();
   printf("Got %lu packets\nDropped %lu packets\nReceived %lu corrupted packets\n", fNPackets, fDroppedPackets, fCorruptedPackets);
}

// functionalies of WDAQTCBReader
void WDAQTCBReader::Begin(){
   fBoard->SetPacketizerBus(true);
   fBoard->SetPacketizerEnable(true);
   fBoard->SetPacketizerAutostart(true);

   // reset the buffer pointers and busy
   fBoard->ResetBufferLogic();
}

void WDAQTCBReader::Loop(){
  // polling on the buffer status searching for an event
  if(fBoard->GetBufferState() != 0) { 
     FRAME_WDAQ_HEADER daqdata;
     daqdata.board_type_revision = BRD_TYPE_ID_TCB<<4;
     daqdata.crate_id = fBoard->GetCrate()->GetCrateNumber();
     daqdata.slot_id = fBoard->GetSlot();
     daqdata.serial_number = fBoard->GetSerialNumber();
     daqdata.packet_number = 0;
     daqdata.data_chunk_offset = 0;

     FRAME_TCB_HEADER ph;

     int nBanks=0;
     int iBank=0;
     int length;

     unsigned int trg_info0;
     unsigned int trg_info1;
     u_int32_t ptr= fBoard->GetBufferHeadSPI(&nBanks, &daqdata.event_number, &ph.time_stamp, &trg_info0, &trg_info1);
     daqdata.trigger_information[5] = trg_info1 & 0xFF;
     daqdata.trigger_information[4] = (trg_info1 >>8) & 0xFF;
     daqdata.trigger_information[3] = (trg_info1 >>16) & 0xFF;
     daqdata.trigger_information[2] = (trg_info1 >>24) & 0xFF;
     daqdata.trigger_information[1] = trg_info0 & 0xFF;
     daqdata.trigger_information[0] = (trg_info0 >>8) & 0xFF;

     //printf("%d banks, %08x %08x %0x%0x %0x%0x\n", nBanks, ph.event_number, ph.time_stamp, ph.trigger_information[4], ph.trigger_information[3], ph.trigger_information[1], ph.trigger_information[0]);

     while(fBoard->HasBufferBankSPI(ptr, ph.bank_name, &length) && iBank<nBanks){
        WDAQTcbPacketData *packet = new WDAQTcbPacketData();

        //printf("Got bank %c %c %c %c\n", ph.bank_name[3], ph.bank_name[2], ph.bank_name[1], ph.bank_name[0]);
        //u_int32_t *data = new u_int32_t[length];
        //printf("Data:\n");
        //fBoard->GetBufferBankDataSPI(ptr, data, length);
        fBoard->GetBufferBankDataSPI(ptr, packet->data, length);
        //for(int i=0; i<length; i++ ) printf("%3d: %08x\n", i, data[i]);
        //delete[] data;
        ptr = fBoard->SkipBufferBankSPI(ptr, length);
     
        //set flags and length
        daqdata.wdaq_flags = EOT | SOT;
        if (iBank == 0) daqdata.wdaq_flags = SOE | EOT | SOT;
        if(iBank == (nBanks-1)) daqdata.wdaq_flags |= EOE;

        daqdata.payload_length = length*4;

        packet->SetEventHeaderInfo(&daqdata); 
        packet->SetTcbHeaderInfo(&ph);

        daqdata.packet_number++;//prepare for next packet
        iBank++;

        if(!fBuf->Try_push(packet, packet->mTriggerNumber)){
           delete packet;
        }
     }

     //generate dummy package if no bank is available
     if(nBanks==0){
        WDAQPacketData *packet = new WDAQPacketData();
        daqdata.wdaq_flags = SOE | EOT | SOT | EOE;
        daqdata.payload_length = 0;
        packet->SetEventHeaderInfo(&daqdata); 
        packet->mTriggerNumber = daqdata.trigger_information[5] | (daqdata.trigger_information[4] << 8);
        packet->mTriggerType = daqdata.trigger_information[1] | (daqdata.trigger_information[0] << 8);
        packet->mSerialTriggerData = daqdata.trigger_information[3] | (daqdata.trigger_information[2] << 8);
        packet->mEventNumber=daqdata.event_number;

        daqdata.packet_number++;//prepare for next packet

        if(!fBuf->Try_push(packet, packet->mTriggerNumber)){
           delete packet;
        }

     }

     fBoard->IncrementBufferPointer();
  }

  //slow down
  std::this_thread::sleep_for(fIdleLoopDuration);
}

void WDAQTCBReader::End(){
  fBoard->SetPacketizerBus(false);
}

//Event builder - Thread that build events from packets
//reset statistics and drop packets at start
void WDAQEventBuilder::Begin(){
   fBuildedEvent = 0;
   fBadPackets = 0;
   fDroppedEvent = 0;
   fOldEvent = 0;
   fNotBuilding = false;
   fDropping = false;

   //clean event builder buffer
   for(auto event: fEvents){
      delete event.second;
   }
   fEvents.clear();
}
//thread loop
void WDAQEventBuilder::Loop(){
   std::vector<WDAQPacketData *> vec;
   if(fSource->Try_pop(vec)){
      for(auto &ptr : vec){

         //search for matching packets
         short new_event_number = ptr->mTriggerNumber;

         WDAQEvent *evt_ptr;

         auto it = fEvents.find(new_event_number);

         if(it == fEvents.end()){
            //no event with this event number -> new Event
            evt_ptr = new WDAQEvent(ptr);
            fEvents[new_event_number] = evt_ptr; 
         } else {
            //have it
            evt_ptr = it->second;
         }

         if(! evt_ptr->AddPacket(ptr)){
            const std::string alarmMessage = "Packet from " + std::to_string(ptr->mBoardId) + ": cannot fit into event";
            //std::cout << alarmMessage << std::endl;
            if(! GetSystem()->GetAlarms()->Test(WDAQLIB_ERROR_CORRUPTEDPACKET)){
               GetSystem()->GetAlarms()->Trigger(WDAQLIB_ERROR_CORRUPTEDPACKET, alarmMessage);
            }

            fBadPackets++;
            delete ptr;
            return;
         }
         delete ptr;

         //printf("%d/%d\n", evt_ptr->IsComplete(), fNBoards);

         //check if event complete
         if(evt_ptr->IsComplete() == fNBoards){
            //event complete
            fBuildedEvent++;

            //managed to build an event: reset error
            fNotBuilding = false;

            if(!fDestination->Try_push(evt_ptr)){
               //could not push to buffer
               //printf("overflow eve\n");
               fDroppedEvent++;
               delete evt_ptr;
            }


            //remove from local event list
            fEvents.erase(new_event_number);

            //#define DEBUGBUILDER 

            //check older events (event id smaller than built one by 10)
            for(auto ev = fEvents.cbegin(); ev != fEvents.cend();){
               if((new_event_number - ev->first)>10){
#ifdef DEBUGBUILDER
                  //This is to print debug information
                  printf("Old event %hu %hu (%d/%d): \n", ev->first, ev->second->mTriggerType, ev->second->IsComplete(), fNBoards);
                    for(auto be: ev->second->fBoard[BRD_TYPE_ID_WDB]){
                       if(be.second->IsComplete()==0 || ev->first == 0) {
                          printf("\tWDB board %d (%d)\n\t\t", be.first, be.second->IsComplete());
                          for(int i=0; i<18; i++) printf("%d-%d-%d ", 
                                                         static_cast<WDAQWdbEvent*>(be.second)->mDrsHasData[i],
                                                         static_cast<WDAQWdbEvent*>(be.second)->mAdcHasData[i],
                                                         static_cast<WDAQWdbEvent*>(be.second)->mTdcHasData[i]);
                          printf("%d %d\n", static_cast<WDAQWdbEvent*>(be.second)->mTrgHasData, be.second->mEndFlagReceived);
                       }
                    }
                    for(auto& boardEvent : ev->second->fBoard[BRD_TYPE_ID_TCB]) {
                       if(boardEvent.second->IsComplete()==0 || ev->first == 0) {
                          printf("\tTCB board %X (%d)\n", boardEvent.first, boardEvent.second->IsComplete());
                          WDAQTcbEvent* tcbeve = static_cast<WDAQTcbEvent*>(boardEvent.second);
                          for(auto bank : tcbeve->mBanks){
                              printf("\t\t%c%c%c%c\n", bank.first[0], bank.first[1], bank.first[2], bank.first[3]);
                              for(auto w: bank.second->data)
                                 printf("%08x\n", w);
                          }
                       }
                  }
#endif
                  //remove old event from list
                  delete ev->second;
                  fEvents.erase(ev++);
                  fOldEvent++;
                  fDropping = true;
               } else { // end if event difference larger than 10 
                  ++ev;
               } //end else
            } // end for on events
         }// end if evt_ptr->IsComplete()

         //check for too many events in the building map
         if(fEvents.size() > 20){
            // not building any event:
            // dropping oldest
            auto ev = fEvents.cbegin();

#ifdef DEBUGBUILDER
            //debug printf
            printf("dropping event %d constaining %d boards\n", ev->first, ev->second->IsComplete());
            for(auto& boardEvent : ev->second->fBoard[BRD_TYPE_ID_WDB])
               if(boardEvent.second->IsComplete()==0 || ev->first == 0)
                  printf("WDB board %d (%d)\n", boardEvent.first, boardEvent.second->IsComplete());
            for(auto& boardEvent : ev->second->fBoard[BRD_TYPE_ID_TCB])
               if(boardEvent.second->IsComplete()==0 || ev->first == 0)
                  printf("TCB board %X (%d)\n", boardEvent.first, boardEvent.second->IsComplete());
#endif

            if(! GetSystem()->GetAlarms()->Test(WDAQLIB_ERROR_NOTBUILDING)){
               const std::string alarmMessage = "Dropping event " + std::to_string(ev->first) + ": containing " + std::to_string(ev->second->IsComplete()) + " boards";
               GetSystem()->GetAlarms()->Trigger(WDAQLIB_ERROR_NOTBUILDING, alarmMessage);
            }
            delete ev->second;
            fEvents.erase(ev);

            fNotBuilding = true;
            fOldEvent++;
         }
      }
   }
}

//print statistics at thread end
void WDAQEventBuilder::End(){
   printf("event built: %lu\nbad packets: %lu\nevent dropped: %lu\nevent dropped because old: %lu\nevent in queue: %lu\n", fBuildedEvent, fBadPackets, fDroppedEvent, fOldEvent, fEvents.size());
}

//Event worker - Thread that calibrate events
//reset statistics at start
void WDAQWorker::Begin(){
   //reset statistics
   fNEvent=0;
   fDroppedEvent=0;
}

//single board calibration
void WDAQWorker::calibrateBoard(WDAQWdbEvent *ev){
   auto calibptr = fVCalib.find(ev->mBoardId);
   if(calibptr == fVCalib.end()){
      if(! GetSystem()->GetAlarms()->Test(WDAQLIB_ERROR_MISSINGCALIB)){
         const std::string alarmMessage = "Missing voltage calibration for board " + std::to_string(ev->mBoardId);
         GetSystem()->GetAlarms()->Trigger(WDAQLIB_ERROR_MISSINGCALIB, alarmMessage);
      }
      return;
   }

   VCALIB* calib = calibptr->second;

   // CLK channels masked with the presence of at least one associated channels in the event
   ev->mDrsHasData[16] &= ev->mDrsHasData[0]|ev->mDrsHasData[1]|ev->mDrsHasData[2]|ev->mDrsHasData[3]|ev->mDrsHasData[4]|ev->mDrsHasData[5]|ev->mDrsHasData[6]|ev->mDrsHasData[7];
   ev->mDrsHasData[17] &= ev->mDrsHasData[8]|ev->mDrsHasData[9]|ev->mDrsHasData[10]|ev->mDrsHasData[11]|ev->mDrsHasData[12]|ev->mDrsHasData[13]|ev->mDrsHasData[14]|ev->mDrsHasData[15];

   //check temperature
   if(calib->IsValid() && fabs(calib->GetTemperature() - ev->mTemperature) > 5){
      ev->mTemperatureOk = false;
      //printf("Board %d: temperature difference too big! %f %f\n", ev->mBoardId, calib->GetTemperature(), ev->mTemperature);
      if(! GetSystem()->GetAlarms()->Test(WDAQLIB_ERROR_CALIBTEMPERATURE)){
         const std::string alarmMessage = "Calibration out of temperature: board " + std::to_string(ev->mBoardId) + " has T=" + std::to_string(ev->mTemperature) + ", calib at T=" + std::to_string(calib->GetTemperature());
         GetSystem()->GetAlarms()->Trigger(WDAQLIB_ERROR_CALIBTEMPERATURE, alarmMessage);
      }
   } else {
      ev->mTemperatureOk = true;
   }

   //amplitude e->mDrsU[ch][bin];
   //unrotate
   float range = ev->GetRange();
   bool anyChannel = false;
   for(int ch=0; ch<WD_N_CHANNELS; ch++){
      //calibrate only channels with data
      if(ev->mDrsHasData[ch]){
         int tc = ev->mTriggerCell[ch];

         //extract range offset
         float ofs;
         if (fabs(range - (-0.45)) < 0.001){
            ofs = calib->mCalib.drs_offset_range0[ch];
         }else if (fabs(range) < 0.001){
            ofs = calib->mCalib.drs_offset_range1[ch];
         }else if (fabs(range - 0.45) < 0.001){
            ofs = calib->mCalib.drs_offset_range2[ch];
         }else{
            ofs = 0;
         }

         for (int bin=0 ; bin<1024 ; bin++){
            //offset calibration
            ev->mDrsU[ch][bin] -= calib->mCalib.wf_offset1[ch][(bin+tc)%1024];
            ev->mDrsU[ch][bin] -= calib->mCalib.wf_offset2[ch][bin];

            //exclude clock channels from gain calibration
            if(ch<WD_N_CHANNELS-2){
               //gain calibration
               if (ev->mDrsU[ch][bin] > 0)
                  ev->mDrsU[ch][bin] /= calib->mCalib.wf_gain1[ch][(bin+tc) % 1024];
               else
                  ev->mDrsU[ch][bin] /= calib->mCalib.wf_gain2[ch][(bin+tc) % 1024];

               //range offset
               //ev->mDrsU[ch][bin] -= calib->mCalib.drs_offset_range2[ch];
               //
               ev->mDrsU[ch][bin] -= ofs;
            }
         }

         anyChannel = true;
      }
   }

   // check PLL
   if(! GetSystem()->GetAlarms()->Test(WDAQLIB_ERROR_PLLLOCK)){
      if(anyChannel) {
         if(
               (ev->mWDBFlags & (1 << cWDFlagDRSPLLLock)) == 0 ||
               (ev->mWDBFlags & (1 << cWDFlagLMKPLLLock)) == 0
            ){
            const std::string alarmMessage = "PLL Not locked: board " + std::to_string(ev->mBoardId) + " has flags=" + std::to_string(ev->mWDBFlags);
            
            GetSystem()->GetAlarms()->Trigger(WDAQLIB_ERROR_PLLLOCK, alarmMessage);
         }
      }
   }

   ev->mVCalibrated = true;
}

//writer thread loop
void WDAQWorker::Loop(){
   WDAQEvent *ptr = nullptr;
   if(fSource->Try_pop(ptr)){
      //new event to calibrate
      for(auto& boardEvent : ptr->fBoard[BRD_TYPE_ID_WDB])
         calibrateBoard(static_cast<WDAQWdbEvent*>(boardEvent.second));

      //statistics
      fNEvent++;

      if(! fDestination->Try_push(ptr)){
         //could not push to destination buffer (full)
         fDroppedEvent++;
         delete ptr;
      }
   }
}

//print statistics
void WDAQWorker::End(){
   printf("closed with %lu events calibrated\nevent calibrated but dropped: %lu\n", fNEvent, fDroppedEvent);
}

//Event writer - Thread that writes event to file
//function to write headers and DRS time bins
std::string WDAQEventWriter::GetFileName(){
   std::string ret = fFileName;
   std::size_t found = ret.find('%');  
   if (found!=std::string::npos){
      ret.replace(found, 1, std::to_string(fRunNumber));
   }

   return ret;
}
//function to write headers and DRS time bins
void WDAQEventWriter::WriteRunHeader(){
   //headers
   const char head[] = "WDQ0";
   fFile.write(head, 4);
   const char time_head[] = "TIME";
   fFile.write(time_head, 4);

   //DRS time bins
   for(auto it : fTCalib){
      TCALIB *calib = it.second;
      unsigned short board_id = it.first;
      const char board_head[] = "B#";
      fFile.write(board_head, 2);
      fFile.write((const char *)&board_id, 2);
      for(int ch=0; ch<18; ch++){
         std::string chn_header = "C";
         if(ch<=9) chn_header += "00";
         else chn_header += "0";
         chn_header += std::to_string(ch);
         fFile.write(chn_header.c_str(), 4);
         fFile.write((char *)(calib->mCalib.dt[ch]), 1024*sizeof(float));
      }
   }

   //TCB boards
   for(auto it : fTCBList){
      const char board_head[] = "T#";
      fFile.write(board_head, 2);
      fFile.write((const char *)&it, 2);
   }
}

//open file and writes headers and DRS time bins
void WDAQEventWriter::Begin(){
   //open file
   fFile.open(GetFileName(), std::ios::binary);
   printf("File %s opened\n", fFileName.c_str());

   WriteRunHeader();

   //reset statistics
   fNEvent=0;
}

//writer thread loop
void WDAQEventWriter::Loop(){
   WDAQEvent *ptr = nullptr;
   if(fSource->Try_pop(ptr)){
      //new event to write
      const char head[] = "EHDR";
      const char temp = 0;
      fFile.write(head, 4);
      // write the event number from trigger bus
      fFile.write((const char *)&ptr->mTriggerNumber, 2);
      // write the trigger type from trigger bus
      fFile.write((const char *)&ptr->mTriggerType, 2);
      // write the serial trigger data from trigger bus
      fFile.write((const char *)&ptr->mSerialTriggerData, 2);
      fFile.write((const char *)&temp, 1);
      fFile.write((const char *)&temp, 1);
      
      //write WDB data
      for(auto &keyval : ptr->fBoard[BRD_TYPE_ID_WDB]){
         WDAQWdbEvent* board= static_cast<WDAQWdbEvent*>(keyval.second);
         // write board Id
         const char board_head[] = "B#";
         fFile.write(board_head, 2);
         fFile.write((const char *)&board->mBoardId, 2);
         //write board temperature
         fFile.write((const char *)&board->mTemperature, sizeof(float));
         //write board range
         float range = board->GetRange();
         fFile.write((const char *)&range, sizeof(float));
         //write board sampling speed
         short sampl = board->mSamplingFrequency/1000;
         fFile.write((const char *)&sampl, 2);
         //write board flags
         fFile.write((const char *)&board->mWDBFlags, 2);
         for(int ch=0;ch<18;ch++){
            //write only channels with data
            if(board->mDrsHasData[ch]){
               std::string chn_header = "C";
               if(ch<=9) chn_header += "00";
               else chn_header += "0";
               chn_header += std::to_string(ch);
               fFile.write(chn_header.c_str(), 4);

               //write frontend settings
               fFile.write((const char *)&(board->mFrontendSettings[ch]), 2);
               //write trigger cell
               fFile.write((const char *)&(board->mTriggerCell[ch]), 2);

               for(int bin=0; bin<1024; bin++){
                  unsigned short val = (unsigned short) ((board->mDrsU[ch][bin]-range+0.5)*65535);
                  fFile.write((const char *)&val, 2);
               }
            }
         }// end if there are drs data
         for(int ch=0;ch<16;ch++){
            //write only channels with data
            if(board->mAdcHasData[ch]){
               std::string chn_header = "A";
               if(ch<=9) chn_header += "00";
               else chn_header += "0";
               chn_header += std::to_string(ch);
               fFile.write(chn_header.c_str(), 4);

               for(int bin=0; bin<2048; bin++){
                  unsigned short val = board->mAdcU[ch][bin];
                  fFile.write((const char *)&val, 2);
               }
            }
         }// end if there are adc data
         for(int ch=0;ch<16;ch++){
            //write only channels with data
            if(board->mTdcHasData[ch]){
               std::string chn_header = "T";
               if(ch<=9) chn_header += "00";
               else chn_header += "0";
               chn_header += std::to_string(ch);
               fFile.write(chn_header.c_str(), 4);

               for(int bin=0; bin<512; bin++){
                  unsigned char val = board->mTdc[ch][bin];
                  fFile.write((const char *)&val, 1);
               }
            }
         }// end if there are tdc data
         if(board->mTrgHasData){
            std::string chn_header = "TRGO";
            fFile.write(chn_header.c_str(), 4);

            for(int bin=0; bin<512; bin++){
               uint64_t val = board->mTrg[bin];
               fFile.write((const char *)&val, 8);
            }

         }// end if there are trg data
         if(board->mScalerHasData){
            std::string chn_header = "SCAL";
            fFile.write(chn_header.c_str(), 4);
            // first write 19 integral scaler values as received
            for(int bin=0; bin<WD_N_SCALER; bin++){
               uint64_t val = board->mScaler[bin];
               fFile.write((const char *)&val, 8);
            }
            // then the board time counter @80MHz
            uint64_t lval = board->mTimeStamp;
            fFile.write((const char *)&lval, 8);

         }// end if there are scaler data
      }
      for(auto &keyval : ptr->fBoard[BRD_TYPE_ID_TCB]){
         WDAQTcbEvent* board= static_cast<WDAQTcbEvent*>(keyval.second);
         // write board Id
         const char board_head[] = "T#";
         fFile.write(board_head, 2);
         fFile.write((const char *)&board->mBoardId, 2);
         unsigned int nbanks = board->mBanks.size();
         fFile.write((const char *)&nbanks, 4);
         for(auto &keybank : board->mBanks){
            //write bank header
            WDAQTcbBank *bank= keybank.second;
            fFile.write((const char *)&bank->fName[0], 1);
            fFile.write((const char *)&bank->fName[1], 1);
            fFile.write((const char *)&bank->fName[2], 1);
            fFile.write((const char *)&bank->fName[3], 1);
            int size = (int) bank->data.size();
            fFile.write((const char *)&size, 4);

            //write bank content
            for(int bin=0; bin < size; bin++){
               unsigned int val = bank->data[bin];
               fFile.write((const char *)&val, 4);
            }

         }
      }

      //statistics
      fNEvent++;
      fLastEvent = ptr->mTriggerNumber;
      delete ptr;

      //check if new file is needed
      if(fEventsPerFile && fNEvent>fEventsPerFile){
         fFile.close();
         fRunNumber++;
         
         //open file
         fFile.open(GetFileName(), std::ios::binary);
         //printf("File %s opened\n", fFileName.c_str());
         printf("Starting run number %d\n", fRunNumber);
         fNEvent = 0;

         //write header
         WriteRunHeader();
      }
   }
}

//print statistics and close file stream at thread end
void WDAQEventWriter::End(){
   fFile.close();
   printf("closed with %lu, last event %lu\n", fNEvent, fLastEvent);
}

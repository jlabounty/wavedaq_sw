#include "WDAQLib.h"

//WDAQ Packet Data - class for UDP DAQ packets 
//Set properties according to UDP event header
void WDAQPacketData::SetEventHeaderInfo(WD_FRAME_HEADER *ph, WDAQ_FRAME_HEADER *pdaqh){
  mBoardId = pdaqh->serial_number; // gets board Id (i.e. serial number)
  mCrateId = pdaqh->crate_id;      // gets crate Id
  mSlotId  = pdaqh->slot_id;       // gets slot Id 
  mChannel = ph->channel_info & 0x1F; // channel in thi s packet
  mPacketNumber = pdaqh->packet_number; // packet number
  mDataType = pdaqh->data_type; // type of data in the packet
  mEventNumber = ph->event_number; 
  mTriggerNumber = ph->trigger_information[5] | (ph->trigger_information[4] << 8);
  mTriggerType = ph->trigger_information[1] | (ph->trigger_information[0] << 8);   
  mSerialTriggerData = ph->trigger_information[3] | (ph->trigger_information[2] << 8);   
  mTemperature = std::round(ph->temperature*0.0625 * 10 + 0.5) / 10.0f;

  mADC = (ph->channel_info >> 7) & 0x01; //which ADC sampled the data
  mTxEnable = ph->tx_enable; // DRS transmission enble mask
  mZeroSuppressionMask = ph->zero_suppression_mask; // mask for zero suppression
  mFlags = pdaqh->wdaq_flags;
  mTriggerSource = ph->trigger_source;
  mBitsPerSample = ph->bits_per_sample;
  mSamplesPerEventPerChannel = ph->samples_per_event_per_channel;
  mPayloadLenght = pdaqh->payload_length;
  mDataOffset = pdaqh->data_chunk_offset;
  mTimeStamp = ph->time_stamp;
  mEventNumber = ph->event_number;
  mTriggerCell = ph->drs_trigger_cell;
  mSamplingFrequency = ph->sampling_frequency;
  mDacOFS = ph->dac_ofs;
  mDacROFS = ph->dac_rofs;
  mFrontendSettings = ph->frontend_settings;
}

//WDAQ DRS Packet Data -  derived packet class to host DRS data
//Add packet info to given Board Event
void WDAQDRSPacketData::AddToBoardEvent(WDAQBoardEvent *e){

   //int channel = (mChannel!=8)? mChannel+8*mADC : 16+mADC;//arrange clock channel
   int channel = mChannel;
   int numberBins = (int) mPayloadLenght / 1.5;
   int firstBin = mDataOffset / 1.5;

   for(int i=0; i<numberBins; i++){
      e->mDrsU[channel][firstBin+i] = data[i];
   }

   e->mFrontendSettings[channel] = mFrontendSettings;
   e->mTriggerCell[channel] = mTriggerCell;
   e->mDrsTxEnable = mTxEnable;
   e->mDrsZeroSuppressionMask = mZeroSuppressionMask;

   //check all data received
   e->mDrsByteNumber[channel] += mPayloadLenght*8;
   if(e->mDrsByteNumber[channel] >= mSamplesPerEventPerChannel*mBitsPerSample){
   // set the flag of drs channel data reception for the writer
     e->mDrsHasData[channel] = true; 
   }

   //check if end of event is received
   if(mFlags & EOE) {
     e->mEndFlagReceived = true;
     e->mLastPacket = mPacketNumber;
   }
   // the packet number offset is from the first packet
   if(mFlags & SOE) {
     e->mStartFlagReceived = true;
     e->mFirstPacket = mPacketNumber;
   }

   //anyway increase packet counter
   e->mPacketsReceived++;

}

//WDAQ ADC Packet Data -  derived packet class to host ADC data
//Add packet info to given Board Event
void WDAQADCPacketData::AddToBoardEvent(WDAQBoardEvent *e){

   int channel = mChannel;
   int numberBins = (int) mPayloadLenght / 1.5;
   int firstBin = mDataOffset / 1.5;

   for(int i=0; i<numberBins; i++){
      e->mAdcU[channel][firstBin+i] = data[i];
   }

   e->mAdcTxEnable = 0; //this must be changed with proper ADC treatment!!
   e->mAdcZeroSuppressionMask = mZeroSuppressionMask;

   //check all data received
   e->mAdcByteNumber[channel] += mPayloadLenght*8;
   if(e->mAdcByteNumber[channel] >= mSamplesPerEventPerChannel*mBitsPerSample){
     // set the flag of adc channel data reception for the writer
      e->mAdcHasData[channel] = true; 
   }

   //check if end of event is received
   if(mFlags & EOE) {
     e->mEndFlagReceived = true;
     e->mLastPacket = mPacketNumber;
   }
   // the packet number offset is from the first packet
   if(mFlags & SOE) {
     e->mStartFlagReceived = true;
     e->mFirstPacket = mPacketNumber;
   }

   //anyway increase packet counter
   e->mPacketsReceived++;

}

//WDAQ TDC Packet Data -  derived packet class to host TDC data
//Add packet info to given Board Event
void WDAQTDCPacketData::AddToBoardEvent(WDAQBoardEvent *e){

   int channel = mChannel;
   int numberBins = (int) mPayloadLenght;
   int firstBin = mDataOffset;

   for(int i=0; i<numberBins; i++){
      e->mTdc[channel][firstBin+i] = data[i];
   }

   e->mTdcTxEnable = 0; //this must be changed with proper TDC treament!!
   e->mTdcZeroSuppressionMask = mZeroSuppressionMask;

   //check all data received
   e->mTdcByteNumber[channel] += mPayloadLenght*8;
   if(e->mTdcByteNumber[channel] >= mSamplesPerEventPerChannel*mBitsPerSample){
   // set the flag of tdc channel data reception for the writer
     e->mTdcHasData[channel] = true; 
   }
 
   //check if end of event is received
   if(mFlags & EOE) {
     e->mEndFlagReceived = true;
     e->mLastPacket = mPacketNumber;
   }
   // the packet number offset is from the first packet
   if(mFlags & SOE) {
     e->mStartFlagReceived = true;
     e->mFirstPacket = mPacketNumber;
   }

   //anyway increase packet counter
   e->mPacketsReceived++;

}

//WDAQ TRG Packet Data -  derived packet class to host TRG data
//Add packet info to given Board Event
void WDAQTRGPacketData::AddToBoardEvent(WDAQBoardEvent *e){

   int numberBins = (int) mPayloadLenght/8;
   int firstBin = mDataOffset/8;

   for(int i=0; i<numberBins; i++){
      e->mTrg[firstBin+i] = data[i];
   }

   e->mTrgTxEnable = 0; //this must be changed with proper TRG data treatment
      
   //check all data received
   e->mTrgByteNumber += mPayloadLenght*8;
   if(e->mTrgByteNumber >= mSamplesPerEventPerChannel*mBitsPerSample){
   // set the flag of trigger data reception for the writer
     e->mTrgHasData = true; 
   }
   
   //check if end of event is received
   if(mFlags & EOE) {
     e->mEndFlagReceived = true;
     e->mLastPacket = mPacketNumber;
   }
   // the packet number offset is from the first packet
   if(mFlags & SOE) {
     e->mStartFlagReceived = true;
     e->mFirstPacket = mPacketNumber;
   }

   //anyway increase packet counter
   e->mPacketsReceived++;
}

//WDAQ Scaler Packet Data -  derived packet class to host Scaler data
//Add packet info to given Board Event
void WDAQScaPacketData::AddToBoardEvent(WDAQBoardEvent *e){

   for(int i=0; i<WD_N_SCALER; i++){
      e->mScaler[i] = data[i];
   }
   // set the flag of scaler reception for the writer
   e->mScalerHasData = true; 
   //check if end of event is received
   if(mFlags & EOE) {
     e->mEndFlagReceived = true;
     e->mLastPacket = mPacketNumber;
   }
   // the packet number offset is from the first packet
   if(mFlags & SOE) {
     e->mStartFlagReceived = true;
     e->mFirstPacket = mPacketNumber;
   }

   //anyway increase packet counter
   e->mPacketsReceived++;
}

//WDAQ Scaler Packet Data -  derived packet class to host Scaler data
//Add packet info to given Board Event: this packet is EMPTY
// this board has been fully zero suppressed
void WDAQDummyPacketData::AddToBoardEvent(WDAQBoardEvent *e){

   //check if end of event is received
   if(mFlags & EOE) {
     e->mEndFlagReceived = true;
     e->mLastPacket = mPacketNumber;
   }
   // the packet number offset is from the first packet
   if(mFlags & SOE) {
     e->mStartFlagReceived = true;
     e->mFirstPacket = mPacketNumber;
   }

   //anyway increase packet counter
   e->mPacketsReceived++;
}

//WDAQ Board Event - single WDB DAQ event
//Constructor, init from packet data
WDAQBoardEvent::WDAQBoardEvent(WDAQPacketData* pkt){
   mBoardId = pkt->mBoardId;
   mCrateId = pkt->mCrateId;
   mSlotId = pkt->mSlotId;
   mSamplingFrequency = pkt->mSamplingFrequency;
   mFlags = pkt->mFlags;
   mTriggerSource = pkt->mTriggerSource;
   mTimeStamp = pkt->mTimeStamp;
   mDacOFS = pkt->mDacOFS;
   mDacROFS = pkt->mDacROFS;
   mTemperature = pkt->mTemperature;

   //reset status
   mVCalibrated = false;
   mStartFlagReceived = false;
   mEndFlagReceived = false;
   mPacketsReceived = 0;
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
      //for(int j=0; j<1024; j++) mDrsU[i][j] = 0;
   }
   mTrgHasData = false;
   mScalerHasData = false;
   mTrgByteNumber = 0;
}

//check complete
bool WDAQBoardEvent::IsComplete(){
   // check that all the packets are received:
   // start of the event is received
   // end of the event is received
   // check if last packet is smaller than first, in case sum to last 2^16

  bool ret = false;
  if(mEndFlagReceived && mStartFlagReceived) {
    
    if(mLastPacket<mFirstPacket)
      mLastPacket += 65536;
    
    if(mLastPacket-mFirstPacket+1 == mPacketsReceived)
      ret = true;
    
  }
  return ret;
   
}


//WDAQ Event - global DAQ event
//constructor, copies data from given packet
WDAQEvent::WDAQEvent(WDAQPacketData* pkt){

   //copies info from first packet
   mEventNumber = pkt->mEventNumber;
   mTriggerNumber = pkt->mTriggerNumber;
   mTriggerType = pkt->mTriggerType&0x3F;
   mSerialTriggerData = pkt->mSerialTriggerData;

}

//add packet to event
void WDAQEvent::AddPacket(WDAQPacketData* pkt){
   unsigned short id = pkt->mBoardId;
   WDAQBoardEvent *boardEvent;

   try {
      boardEvent = fBoard.at(id);
   } catch (const std::out_of_range&){
      //no event, allocate a new one
      boardEvent = new WDAQBoardEvent(pkt);
      fBoard[id] = boardEvent;
   }

   //process packet content
   pkt->AddToBoardEvent(boardEvent);

}

//check event complete
int WDAQEvent::IsComplete(){
   bool ret = true;
   int nboards = 0;

   for(auto e :fBoard){
     //check only if end of event received
     ret &= e.second->IsComplete();
     nboards++;
   }
   if(ret)
     return nboards;
   else
     return 0;
}


//destructor to remove child WDBoardEvent
WDAQEvent::~WDAQEvent(){
   for(auto e :fBoard)
      delete e.second;
}

//---------- THREAD implementation -------

//Packet Collector - Thread to collect packets
//Reset statistics at begin
void WDAQPacketCollector::Begin(){
   //reset statistics
   fNPackets=0;
   fDroppedPackets=0;
}

//called on every UDP packet
void WDAQPacketCollector::GotData(int size, unsigned char* dataptr){

   //check size of received datagram
  if(size < (int)sizeof(WDAQ_FRAME_HEADER)) {
    printf("Problem with size\n");
    return;
  }

   //first link to the WDAQ_FRAME_HEADER
   WDAQ_FRAME_HEADER* daqdata = (WDAQ_FRAME_HEADER*)dataptr;
   //then to the WD_FRAME_HEADER
   WD_FRAME_HEADER* data = (WD_FRAME_HEADER*) (dataptr + sizeof(WDAQ_FRAME_HEADER));

   
   // check protocol version
   if (daqdata->protocol_version != WD2_UDP_PROTOCOL_VERSION) {
     printf("received packet with wrong protocol version, got %d required %d\n",daqdata->protocol_version, WD2_UDP_PROTOCOL_VERSION);
      return;
   }

   //correct endianess
   daqdata->serial_number               = SWAP_UINT16(daqdata->serial_number);
   data->tx_enable                      = SWAP_UINT32(data->tx_enable);
   data->zero_suppression_mask          = SWAP_UINT16(data->zero_suppression_mask);
   data->samples_per_event_per_channel  = SWAP_UINT16(data->samples_per_event_per_channel);
   daqdata->payload_length              = SWAP_UINT16(daqdata->payload_length);
   daqdata->packet_number               = SWAP_UINT16(daqdata->packet_number);
   daqdata->data_chunk_offset           = SWAP_UINT16(daqdata->data_chunk_offset);
   data->event_number                   = SWAP_UINT32(data->event_number);
   data->drs_trigger_cell               = SWAP_UINT16(data->drs_trigger_cell);
   data->sampling_frequency             = SWAP_UINT32(data->sampling_frequency);
   data->temperature                    = SWAP_UINT16(data->temperature);
   data->dac_ofs                        = SWAP_UINT16(data->dac_ofs);
   data->dac_rofs                       = SWAP_UINT16(data->dac_rofs);
   data->frontend_settings              = SWAP_UINT16(data->frontend_settings);
   data->time_stamp                     = SWAP_UINT64(data->time_stamp);

   //#define DEBUGGOT 

   #ifdef DEBUGGOT
   printf("---------------------------------\n");
   printf("---------------------------------\n");
   printf("serial number \t %d\n", daqdata->serial_number);
   printf("tx enable \t %x\n", data->tx_enable);
   printf("zero supp mask \t %d\n", data->zero_suppression_mask);
   printf("packet num \t\t %d\n", daqdata->packet_number);
   printf("flags \t\t %d\n", daqdata->wdaq_flags);
   printf("sampl  ev cha \t %d\n", data->samples_per_event_per_channel);
   printf("payload length \t %d\n", daqdata->payload_length);
   printf("data chunk off \t %d\n", daqdata->data_chunk_offset);
   printf("event number \t %d\n", data->event_number);
   printf("drs trig cell \t %d\n", data->drs_trigger_cell);
   printf("sampl freq \t %d\n", data->sampling_frequency);
   printf("temperature \t %d\n", data->temperature);
   printf("dac ofs \t %d\n", data->dac_ofs);
   printf("daq rofs \t %x\n", data->dac_rofs);
   printf("frontend sets \t %x\n", data->frontend_settings);
   printf("data type \t %x\n", daqdata->data_type);
   printf("flags   \t %x\n", data->wd_flags);
   printf("\n");
   printf("\n");
   #endif

   if(daqdata->data_type == cDataTypeDRS){
      //DRS Data
      //create new packet
      WDAQDRSPacketData *packet = new WDAQDRSPacketData();
      packet->SetEventHeaderInfo(data, daqdata);

      // decode waveform data
      auto pd = (unsigned char*)(data+1);
      int numberBins = (int) packet->mPayloadLenght / 1.5;
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
      fNPackets++;

      //push to buffer
      if(!fBuf->Try_push(packet)){
         //could not push packet to buffer
         //printf("overflow pk\n");
         fDroppedPackets++;
         delete packet;
      }
   } else if (daqdata->data_type == cDataTypeADC){
      //ADC Data

      //create new packet
      WDAQADCPacketData *packet = new WDAQADCPacketData();
      packet->SetEventHeaderInfo(data, daqdata);

      // decode waveform data
      auto pd = (unsigned char*)(data+1);
      int numberBins = (int) packet->mPayloadLenght / 1.5;
      for (int i=0 ; i<numberBins ; i+=2) {
         unsigned short data1   = ((pd[1] & 0x0F) << 8) | pd[0];
         unsigned short data2 = ((unsigned short)pd[2] << 4) | (pd[1] >> 4);
         pd+=3;

         // first segment
         packet->data[i]         = data1; // 1V DRS range with 12 bits
         packet->data[i+1]       = data2;
      }
      fNPackets++;

      //push to buffer
      if(!fBuf->Try_push(packet)){
         //could not push packet to buffer
         //printf("overflow pk\n");
         fDroppedPackets++;
         delete packet;
      }
   } else if (daqdata->data_type == cDataTypeTDC){
      //TDC Data

      //create new packet
      WDAQTDCPacketData *packet = new WDAQTDCPacketData();
      packet->SetEventHeaderInfo(data, daqdata);

      // decode waveform data
      auto pd = (unsigned char*)(data+1);
      int numberBins = (int) packet->mPayloadLenght;
      for (int i=0 ; i<numberBins ; i++) {
         packet->data[i] = pd[i];
      }
      fNPackets++;

      //push to buffer
      if(!fBuf->Try_push(packet)){
         //could not push packet to buffer
         //printf("overflow pk\n");
         fDroppedPackets++;
         delete packet;
      }
   } else if (daqdata->data_type == cDataTypeTrg){
      //TRG Data
      //create new packet
      WDAQTRGPacketData *packet = new WDAQTRGPacketData();
      packet->SetEventHeaderInfo(data,daqdata);

      // decode waveform data
      auto pd = (unsigned long*)(data+1);
      int numberBins = (int) packet->mPayloadLenght/8;
      for (int i=0 ; i<numberBins ; i++) {
         packet->data[i] = SWAP_UINT64(pd[i]);
      }
      fNPackets++;

      //push to buffer
      if(!fBuf->Try_push(packet)){
         //could not push packet to buffer
         //printf("overflow pk\n");
         fDroppedPackets++;
         delete packet;
      }
   } else if (daqdata->data_type == cDataTypeScaler) {
      //Scaler data
      //create new packet
      WDAQScaPacketData *packet = new WDAQScaPacketData();
      packet->SetEventHeaderInfo(data,daqdata);

      // decode waveform data
      auto pd = (unsigned long*)(data+1);
      for (int i=0 ; i<WD_N_SCALER ; i++) {//Ch 0->16, Trigger, External Clock
         packet->data[i] = SWAP_UINT64(pd[17-i]);
      }
      fNPackets++;

      //push to buffer
      if(!fBuf->Try_push(packet)){
         //could not push packet to buffer
         //printf("overflow pk\n");
         fDroppedPackets++;
         delete packet;
      }
   } else if (daqdata->data_type == cDataTypeDummy) {
      //Scaler data
      //create new packet
      WDAQDummyPacketData *packet = new WDAQDummyPacketData();
      packet->SetEventHeaderInfo(data,daqdata);

      fNPackets++;

      //push to buffer
      if(!fBuf->Try_push(packet)){
         //could not push packet to buffer
         //printf("overflow pk\n");
         fDroppedPackets++;
         delete packet;
      }
      
   }// end if data is dummy (completely zero suppressed)
}

//print statistics at thread end
void WDAQPacketCollector::End(){
   printf("Got %lu packets\n", fNPackets);
   printf("Dropped %lu packets\n", fDroppedPackets);
}

// functionalies of WDAQTCBReader
void WDAQTCBReader::Begin(){
  // reset the buffer pointers and busy
  fBoard->ResetBufferLogic();
  fBoard->SetPacketizerBus(true);
  //printf("buffer logic resetted\n");
}

void WDAQTCBReader::Loop(){
  // polling on the buffer status searching for an event
  if(fBoard->GetBufferState() != 0) { 
  // read the last available buffer on TCB
    //uint32_t state = fBoard->GetBufferState();
    //uint32_t pointer = fBoard->GetSPIBufferPointer();
    //uint32_t pointer2 = fBoard->GetPacketizerBufferPointer();
    uint32_t data[3];
    fBoard->ReadBuffer(data, 1);
    // remove the busy for the just read buffer
    fBoard->IncrementBufferPointer();
    //printf("got event %x, bufferstate %x pointer %x/%x\n",data[0], state, pointer, pointer2);
  }
}

void WDAQTCBReader::End(){
  fBoard->SetPacketizerBus(false);
}

//Event builder - Thread that build events from packets
//reset statistics and drop packets at start
void WDAQEventBuilder::Begin(){
   fBuildedEvent = 0;
   fDroppedEvent = 0;
   fOldEvent = 0;

   //clean event builder buffer
   for(auto event: fEvents){
      delete event.second;
   }
   fEvents.clear();
}
//thread loop
void WDAQEventBuilder::Loop(){
   WDAQPacketData *ptr = nullptr;
   if(fSource->Try_pop(ptr)){

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

      evt_ptr->AddPacket(ptr); 
      delete ptr;

      //check if event complete
      if(evt_ptr->IsComplete() == fNWDB){
	//event complete
	fBuildedEvent++;
	
	if(!fDestination->Try_push(evt_ptr)){
	  //could not push to buffer
	  //printf("overflow eve\n");
	  fDroppedEvent++;
	  delete evt_ptr;
	}
	
	
	//remove from local event list
	fEvents.erase(new_event_number);
	
	//check older events (event id smaller than built one by 10)
	for(auto ev = fEvents.cbegin(); ev != fEvents.cend();){
	  if((new_event_number - ev->first)>10){
	    //This is to print debug information
	    /*printf("Old event %d: ", ev->first);
	      for(auto be: ev->second->fBoard){
	      for(int i=0; i<18; i++) printf("%d-%d-%d ", be.second->mDrsHasData[i], be.second->mAdcHasData[i], be.second->mTdcHasData[i]);
	      printf("%d %d\n", be.second->mTrgHasData, be.second->mEndFlagReceived);
	      }*/
	    //remove old event from list
	    delete ev->second;
	    fEvents.erase(ev++);
	    fOldEvent++;
	  }else{
	    ++ev;
	  }
	}
      }// end if evt_ptr->IsComplete()
   }
}

//print statistics at thread end
void WDAQEventBuilder::End(){
   printf("event built: %lu\n", fBuildedEvent);
   printf("event dropped: %lu\n", fDroppedEvent);
   printf("event dropped because old: %lu\n", fOldEvent);
   printf("in queue: %lu\n", fEvents.size());
}

//Event worker - Thread that calibrate events
//reset statistics at start
void WDAQWorker::Begin(){
   //reset statistics
   fNEvent=0;
   fDroppedEvent=0;
}

//single board calibration
void WDAQWorker::calibrateBoard(WDAQBoardEvent *ev){
   VCALIB *calib = fVCalib.at(ev->mBoardId);

   //amplitude e->mDrsU[ch][bin];
   //unrotate
   float range = ev->GetRange();
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
      }
   }

   ev->mVCalibrated = true;
}

//writer thread loop
void WDAQWorker::Loop(){
   WDAQEvent *ptr = nullptr;
   if(fSource->Try_pop(ptr)){
      //new event to calibrate
      for(auto boardEvent : ptr->fBoard)
         calibrateBoard(boardEvent.second);

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
   printf("closed with %lu events calibrated\n", fNEvent);
   printf("event calibrated but dropped: %lu\n", fDroppedEvent);
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
      
      //write DRS data
      for(auto keyval : ptr->fBoard){
         WDAQBoardEvent* board= keyval.second;
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
	 fFile.write((const char *)&board->mSamplingFrequency, 2);
	 //write board flags
	 fFile.write((const char *)&board->mFlags, 2); //useless to now, to be changed with WDBFlags earlier than 2030
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
               unsigned long val = board->mTrg[bin];
               fFile.write((const char *)&val, 8);
            }

         }// end if there are trg data
         if(board->mScalerHasData){
            std::string chn_header = "SCAL";
            fFile.write(chn_header.c_str(), 4);
	    // first write 18 integral scaler values as received
            for(int bin=0; bin<WD_N_SCALER; bin++){
               unsigned long val = board->mScaler[bin];
               fFile.write((const char *)&val, 8);
            }
	    // then the board time counter @80MHz
	    unsigned long lval = board->mTimeStamp;
	    fFile.write((const char *)&lval, 8);

         }// end if there are scaler data
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
	 //         printf("File %s opened\n", fFileName.c_str());
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

#include "WDAQLib.h"

#define SWAP_UINT64(x) (((uint64_t)SWAP_UINT32((uint32_t)((x) & 0xffffffff)) << 32) | (uint64_t)SWAP_UINT32((uint32_t)((x) >> 32)))

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
  mTriggerNumber = ph->trigger_information[0] | (ph->trigger_information[1] << 8); // ## to be changed
  mTriggerType = ph->trigger_information[2] | (ph->trigger_information[3] << 8);   // ## to be changed
  mTemperature = std::round(ph->temperature*0.0625 * 10 + 0.5) / 10.0f;

  mADC = (ph->channel_info >> 7) & 0x01; //which ADC sampled the data
  mTxEnable = ph->tx_enable; // DRS transmission enble mask
  mZeroSuppressionMask = ph->zero_suppression_mask; // mask for zero suppression
  mFlags = ph->wd_flags;
  mTriggerSource = ph->trigger_source;
  mBitsPerSample = ph->bits_per_sample;
  mSamplesPerEventPerChannel = ph->samples_per_event_per_channel;
  mPayloadLenght = pdaqh->payload_length;
  mDataOffset = pdaqh->data_chunk_offset;
  for(int i=0; i<8; i++) mTimeStamp[i] = ph->time_stamp[i];
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
      e->mDrsHasData[channel] = true; 
   }

   if(mFlags & 0x1) e->mEndFlagReceived = true;

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
      e->mAdcHasData[channel] = true; 
   }

   //   if(mFlags & 0x1) e->mEndFlagReceived = true;

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
      e->mTdcHasData[channel] = true; 
   }

   //   if(mFlags & 0x1) e->mEndFlagReceived = true;

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
      e->mTrgHasData = true; 
   }

   //   if(mFlags & 0x1) e->mEndFlagReceived = true;

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
   for(int i=0; i<8; i++) mTimeStamp[i] = pkt->mTimeStamp[i];
   mDacOFS = pkt->mDacOFS;
   mDacROFS = pkt->mDacROFS;
   mTemperature = pkt->mTemperature;

   //reset status
   mVCalibrated = false;
   mEndFlagReceived = false;
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
   mTrgByteNumber = 0;
}

//check complete
bool WDAQBoardEvent::IsComplete(){
   bool ret = true;
   // first version ckecking that all the enabled channels sent data
   for(int i=0; i<WD_N_CHANNELS; i++){
     if(mDrsTxEnable & (1<<i))
       if(mDrsHasData[i]==false) 
	 ret = false; 
     if(mAdcTxEnable & (1<<i))
       if(mAdcHasData[i]==false)
	 ret = false; 
     if(mTdcTxEnable & (1<<i))
       if(mTdcHasData[i]==false)
	 ret = false;
   }
   if(mTrgTxEnable)
     if(mTrgHasData==false)
       ret = false;
   return ret;
   

   //second version: check that all the packets are received:
   // start of the event is received
   // end of the event is received
   

}


//WDAQ Event - global DAQ event
//constructor, copies data from given packet
WDAQEvent::WDAQEvent(WDAQPacketData* pkt){

   //copies info from first packet
   mEventNumber = pkt->mEventNumber;
   mTriggerNumber = pkt->mTriggerNumber;
   mTriggerType = pkt->mTriggerType;

   //   printf("event number = %d\n",mTriggerNumber);

}

//add packet to event
void WDAQEvent::AddPacket(WDAQPacketData* pkt){
   int id = pkt->mBoardId;
   bool found = false;
   WDAQBoardEvent *boardEvent;

   for(auto b :fBoard){
      if(b->mBoardId==id){
         found = true;
         boardEvent = b;
         break;
      }
   }

   if(!found){
      WDAQBoardEvent *e = new WDAQBoardEvent(pkt);
      pkt->AddToBoardEvent(e);
      fBoard.push_back(e);
   } else{
      pkt->AddToBoardEvent(boardEvent);
   }

}

//check event complete
bool WDAQEvent::IsComplete(){
   bool ret = true;

   for(auto e :fBoard){
     //check only if end of event received
     if(e->mEndFlagReceived)
       ret &= e->IsComplete();
   }

   return ret;
}


//destructor to remove child WDBoardEvent
WDAQEvent::~WDAQEvent(){
   for(auto e :fBoard)
      delete e;
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
   daqdata->wdaq_flags                  = SWAP_UINT16(daqdata->wdaq_flags);
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

   //   #define DEBUGGOT 

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

   if(daqdata->data_type == 0){
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
   } else if (daqdata->data_type == 1) {
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
   } else if (daqdata->data_type == 2) {
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
   } else if (daqdata->data_type == 3) {
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
      
   }
}

//print statistics at thread end
void WDAQPacketCollector::End(){
   printf("Got %lu packets\n", fNPackets);
   printf("Dropped %lu packets\n", fDroppedPackets);
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
      int new_event_number = ptr->mEventNumber;
      //      int new_event_number = ptr->mTriggerNumber;

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
      if(evt_ptr->IsComplete()){
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
	      for(int i=0; i<18; i++) printf("%d-%d-%d ", be->mDrsHasData[i], be->mAdcHasData[i], be->mTdcHasData[i]);
	      printf("%d %d\n", be->mTrgHasData, be->mEndFlagReceived);
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
         int tc = ch < 8 || ch == 16  ? ev->mTriggerCell[0] : ev->mTriggerCell[1];

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

            //exclude clock channels from grain calibration
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
         calibrateBoard(boardEvent);

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
//open file and writes headers and DRS time bins
void WDAQEventWriter::Begin(){
   //open file
   fFile.open(fFileName, std::ios::binary);

   //headers
   const char head[] = "DRS8";
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

      //reset statistics
      fNEvent=0;
   }
}

//writer thread loop
void WDAQEventWriter::Loop(){
   WDAQEvent *ptr = nullptr;
   if(fSource->Try_pop(ptr)){
      //new event to write
      const char head[] = "EHDR";
      fFile.write(head, 4);
      fFile.write((const char *)&ptr->mEventNumber, 4);
      const char temp = 0;
      for(int i=0; i<16; i++) fFile.write(&temp, 1);

      //write DRS data
      for(auto DRS : ptr->fBoard){
         const char board_head[] = "B#";
         fFile.write(board_head, 2);
         fFile.write((const char *)&DRS->mBoardId, 2);
         float range = DRS->GetRange();
         for(int ch=0;ch<18;ch++){
            //write only channels with data
            if(DRS->mDrsHasData[ch]){
               std::string chn_header = "C";
               if(ch<=9) chn_header += "00";
               else chn_header += "0";
               chn_header += std::to_string(ch);
               fFile.write(chn_header.c_str(), 4);

               const char trgcell_head[] = "T#";
               fFile.write(trgcell_head, 2);
               fFile.write((const char *)&(DRS->mTriggerCell[(ch<7||ch==16)?0:1]), 2);
               fFile.write(trgcell_head, 2);
               fFile.write(trgcell_head, 2);

               for(int bin=0; bin<1024; bin++){
                  unsigned short val = (unsigned short) ((DRS->mDrsU[ch][bin]-range+0.5)*65535);
                  fFile.write((const char *)&val, 2);
               }
            }
         }
         for(int ch=0;ch<18;ch++){
            //write only channels with data
            if(DRS->mAdcHasData[ch]){
               std::string chn_header = "A";
               if(ch<=9) chn_header += "00";
               else chn_header += "0";
               chn_header += std::to_string(ch);
               fFile.write(chn_header.c_str(), 4);

               for(int bin=0; bin<2048; bin++){
                  unsigned short val = DRS->mAdcU[ch][bin];
                  fFile.write((const char *)&val, 2);
               }
            }
         }
         for(int ch=0;ch<18;ch++){
            //write only channels with data
            if(DRS->mTdcHasData[ch]){
               std::string chn_header = "T";
               if(ch<=9) chn_header += "00";
               else chn_header += "0";
               chn_header += std::to_string(ch);
               fFile.write(chn_header.c_str(), 4);

               for(int bin=0; bin<512; bin++){
                  unsigned char val = DRS->mTdc[ch][bin];
                  fFile.write((const char *)&val, 1);
               }
            }
         }
         if(DRS->mTrgHasData){
            std::string chn_header = "TRGO";
            fFile.write(chn_header.c_str(), 4);

            for(int bin=0; bin<512; bin++){
               unsigned long val = DRS->mTrg[bin];
               fFile.write((const char *)&val, 8);
            }

         }
      }

      //statistics
      fNEvent++;
      fLastEvent = ptr->mEventNumber;
      //      fLastEvent = ptr->mTriggerNumber;

      delete ptr;
   }
}

//print statistics and close file stream at thread end
void WDAQEventWriter::End(){
   fFile.close();
   printf("closed with %lu, last event %lu\n", fNEvent, fLastEvent);
}

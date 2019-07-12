#include "WDLib.h"
#include "mxml.h"

// --- WDBoard --- 
// Set a property
void WDBoard::AddProperty(std::string name, std::string val){
   fProperties[name].SetStringValue(val);
}
Property& WDBoard::GetProperty(std::string name){
   try{
      return fProperties.at(name);
   } catch (const std::out_of_range& ex){
      //no value in local property list
      //try group one

      try{
         WDSystem* sysptr = fCrate->GetSystem();
         if(sysptr!= nullptr){
            return sysptr->GetGroupProperties(fGroupName).at(name);
         } else
            throw  std::out_of_range("");
      } catch (const std::out_of_range& ex){
         //no property with given name

         throw std::runtime_error("No property with given name");
      }
   }

}
// Getters
void WDBoard::SetProperties(const PropertyGroup &properties){
   fProperties = properties;
}
// Configure
void WDBoard::Configure(){
   //printf("configuring board %s\n", GetBoardName().c_str());
   ConfigurationStarted(); 

   WDSystem* sysptr = fCrate->GetSystem();
   //loop on Group Properties
   bool groupExist;
   try{
      sysptr->GetGroupProperties(fGroupName);
      groupExist = true;
   } catch (const std::out_of_range& ex){
      groupExist = false;
   }
   if(sysptr!=nullptr && groupExist){
      for(auto it : sysptr->GetGroupProperties(fGroupName)){
         //checks property is not overwritten in local board
         if(! fProperties.contains(it.first))
            ConfigureProperty(it.first, it.second);
      }
   }
   //loop on Board local properties
   for(auto it : fProperties){
      ConfigureProperty(it.first, it.second);
   }
   ConfigurationEnded(); 
}
// Contructor
WDBoard::WDBoard(WDCrate * crate, char slot, std::string name){
   fBoardName = name;
   crate->AddBoard(this, slot);
}

// --- WDCrate --- 
// Board Adder
void WDCrate::AddBoard(WDBoard *board, int slot){
   if(slot > 17 || slot < -1) throw std::runtime_error("slot out of range");
   if(fBoard[slot] != 0) throw std::runtime_error("two board in same slot");
   fBoard[slot] = board;
   //board->SetCrate(this, slot);
   board->fSlot = slot;
   board->fCrate = this;
   if(fSystem != nullptr) {
      fSystem->fBoardMap[board->fBoardName] = WDPosition(fCrateNumber, slot);
   }
}

// Checks slot is filled
bool WDCrate::HasBoardIn(int slot){
   if(fBoard[slot]) return true;
   else return false;
}

//Power On
void WDCrate::PowerOn(){
   char val = 1;
   int status = mscb_write(fMscbHandle, 20, 0, &val, sizeof(val));
   // print something only in case of error
   if (status != MSCB_SUCCESS)
      printf("Error: status = %d\n", status);
   
}

//Power Off
void WDCrate::PowerOff(){
   char val = 0;
   int status = mscb_write(fMscbHandle, 20, 0, &val, sizeof(val));
   // print something only in case of error
   if (status != MSCB_SUCCESS)
      printf("Error: status = %d\n", status);
}

//Check Power state
bool WDCrate::IsPowered(){
   char val = 0;
   int size = 1;
   int status = mscb_read(fMscbHandle, 20, 0, &val, &size);
   // print something only in case of error
   if (status != MSCB_SUCCESS)
      printf("Error: status = %d\n", status);

   return (val==1)? true: false;
}

// Board Getter
WDBoard* WDCrate::GetBoardAt(int slot){
   if(fBoard[slot]) return fBoard[slot];
   else throw std::runtime_error("no board in slot");
}

// --- WDSystem --- 
// Crate Adder
void WDSystem::AddCrate(WDCrate *crate){
   fCrate.push_back(crate);
   //if no trigger crate new crate is defined so
   if(fTrgCrateId < 0) {
      fTrgCrateId = fCrate.size() - 1;
   }

   crate->fSystem = this;
   crate->fCrateNumber = fCrate.size() - 1;

   //add boards already in crate in the map
   for(int slot=0; slot<18; slot++){
      if(crate->HasBoardIn(slot)){ 
         WDBoard *b = crate->GetBoardAt(slot);
         fBoardMap[b->GetBoardName()] = WDPosition(crate->fCrateNumber, slot);
      }
   }
}

// crate board properties from XML
void WDSystem::CreatePropertiesFromXml(WDBoard *board, MXML_NODE *board_node){
   PropertyGroup p;
   for(int i=0; i<mxml_get_number_of_children(board_node); i++){
      MXML_NODE *child_node = mxml_subnode(board_node, i);
      std::string name = std::string(mxml_get_name(child_node));
      std::string value = std::string(mxml_get_value(child_node));
      p[name].SetStringValue(value);
   }

   board->SetProperties(p);
}

// Create from XML
void WDSystem::CreateFromXml(std::string filepath){

   char* error = nullptr;
   int line;
   MXML_NODE *root_xml = mxml_parse_file(filepath.c_str(), error, sizeof(error), &line);
   //mxml_debug_tree(root_xml, 0);
   MXML_NODE *system_xml = mxml_subnode(root_xml, 0);

   //loop in crates
   for(int i=0; i<mxml_get_number_of_children(system_xml); i++){
      MXML_NODE *crate_xml= mxml_subnode(system_xml, i);
      std::string crate_node_name = std::string(mxml_get_name(crate_xml));
      if(crate_node_name == "Crate"){
         //create a new Crate
         char* mscbnodestring = mxml_get_attribute(crate_xml, "MscbNode");
         if(mscbnodestring==NULL){
            printf("error parsing XML: Crate need MscbNode attribute\n");
            return;
         }

         char* cratenamestring = mxml_get_attribute(crate_xml, "Name");
         if(cratenamestring==NULL){
            printf("warning parsing XML: MscbNode used as crate name\n");
            cratenamestring = mscbnodestring;
         }

         WDCrate *c = new WDCrate(std::string(cratenamestring), std::string(mscbnodestring));

         bool triggerFlag = false;
         //loop on Boards
         for(int i=0; i<mxml_get_number_of_children(crate_xml); i++){
            MXML_NODE *board_xml= mxml_subnode(crate_xml, i);
            std::string board_node_name = std::string(mxml_get_name(board_xml));
            if(board_node_name == "Board"){
               //create a new board
               char* slotstring = mxml_get_attribute(board_xml, "Slot");
               if(slotstring==NULL){
                  printf("error parsing XML: Board needs a Slot attributes\n");
                  return;
               }
               WDBoard *b = new WDBoard(c, atoi(slotstring));

               //board property group is optional
               char* groupstring = mxml_get_attribute(board_xml, "Group");
               if(groupstring!=NULL){
                  b->SetGroup(groupstring);
               }

               //parse remaining tags as properties
               CreatePropertiesFromXml(b, board_xml);
            }
            else if(board_node_name == "WDB"){
               //create a new board
               char* slotstring = mxml_get_attribute(board_xml, "Slot");
               char* namestring = mxml_get_attribute(board_xml, "Name");
               if(slotstring == NULL || namestring==NULL) {
                  printf("error parsing XML: WDB needs a Slot and a Name attributes\n");
                  return;
               }

               //try to get a Node (ip), if not given use Name attribute
               char* mscbnodestring = mxml_get_attribute(board_xml, "MscbNode");
               if(mscbnodestring == NULL) {
                  printf("warning parsing XML: WDB Name used as MscbNode name\n");
                  mscbnodestring = namestring;
               }

               WDWDB *b = new WDWDB(c, atoi(slotstring), std::string(namestring), std::string(mscbnodestring));

               //board property group is optional
               char* groupstring = mxml_get_attribute(board_xml, "Group");
               if(groupstring!=NULL){
                  b->SetGroup(groupstring);
               }

               //parse remaining tags as properties
               CreatePropertiesFromXml(b, board_xml);
            }
            else if(board_node_name == "TCB"){
               //create a new board
               
               char* slotstring = mxml_get_attribute(board_xml, "Slot");
               char* namestring = mxml_get_attribute(board_xml, "Name");
               if(slotstring == NULL || namestring==NULL) {
                  printf("error parsing XML: TCB needs a Slot and a Name attributes\n");
                  return;
               }

               WDTCB *b = new WDTCB(c, atoi(slotstring), std::string(namestring));

               //board property group is optional
               char* groupstring = mxml_get_attribute(board_xml, "Group");
               if(groupstring!=NULL){
                  b->SetGroup(groupstring);
               }

               //parse remaining tags as properties
               CreatePropertiesFromXml(b, board_xml);
            }
            else if(board_node_name == "Trigger") triggerFlag = true;
         }

         AddCrate(c);
         if(triggerFlag){
            SetTriggerCrateId(GetCrateSize()-1);
         }
      } else if (crate_node_name == "Group"){
         //create a new property group
         char* namestring = mxml_get_attribute(crate_xml, "Name");
         if(namestring==NULL){
            printf("error parsing XML: Group needs a Name attribute");
            return;
         }
         std::string groupname = std::string(namestring);

         PropertyGroup p;
         for(int i=0; i<mxml_get_number_of_children(crate_xml); i++){
            MXML_NODE *child_node = mxml_subnode(crate_xml, i);
            std::string name = std::string(mxml_get_name(child_node));
            std::string value = std::string(mxml_get_value(child_node));
            p[name].SetStringValue(value);
         }

         SetGroupProperties(groupname, p);

      } else if (crate_node_name == "Daq"){
         //create a new property group For DAQ
         if(fDaqProperties.size() != 0){
            printf("overwriting previous Daq Configuration!");
         }

         for(int i=0; i<mxml_get_number_of_children(crate_xml); i++){
            MXML_NODE *child_node = mxml_subnode(crate_xml, i);
            std::string name = std::string(mxml_get_name(child_node));
            std::string value = std::string(mxml_get_value(child_node));
            fDaqProperties[name].SetStringValue(value);
         }

         printf("DAQ Properties:\n");
         for(auto p: fDaqProperties){
            printf("\t%s:\t%s\n", p.first.c_str(), p.second.GetStringValue().c_str());
         }

      }
   }

   mxml_free_tree(root_xml);
}

//Configure all board in the system
void WDSystem::Configure(){
   for(auto &c : fCrate){
      printf("configuring crate %s\n", c->GetMscbName().c_str());
      for(int i=0; i<18; i++){
         if(c->HasBoardIn(i)) 
            c->GetBoardAt(i)->Configure();
      }
   }

}

//Power On
void WDSystem::PowerOn(){
   //first switch on trigger crate
   GetTriggerCrate()->PowerOn();
   for(auto &c : fCrate){
      c->PowerOn();
   }
   std::this_thread::sleep_for(std::chrono::seconds(10));
   for(auto &c : fCrate){
      for(auto &b : *c){
         if(b)
            b->Connect();
      }
   }
   
}

//Power Off
void WDSystem::PowerOff(){
   for(auto &c : fCrate)
      c->PowerOff();
}
void WDSystem::SetSerdesTraining(bool state){
   for(auto &c : fCrate){
      for(auto &b : *c){
         if(b) b->SetSerdesTraining(state);
      }
   }
}

//Go Run
void WDSystem::GoRun(){
   GetTriggerBoard()->Sync();
   if(fCollectorThread) fCollectorThread->GoRun();
   if(fBuilderThread) fBuilderThread->GoRun();
   if(fWriterThread) fWriterThread->GoRun();
   if(fWorkerThread) fWorkerThread->GoRun();
   for(auto t: fTCBReaderThreads) t->GoRun();
   sleep(1);
   GetTriggerBoard()->GoRun();
}

//Stop Run
void WDSystem::StopRun(){
   GetTriggerBoard()->StopRun();
   if(fCollectorThread) fCollectorThread->StopRun();
   if(fBuilderThread) fBuilderThread->StopRun();
   if(fWriterThread) fWriterThread->StopRun();
   if(fWorkerThread) fWorkerThread->StopRun();
   for(auto t: fTCBReaderThreads) t->StopRun();
}
//train serial links
void WDSystem::TrainSerdes(){
   GetTriggerBoard()->Sync();

   for(auto &c : fCrate){
      for(auto &b : *c){
         if(b) b->TrainSerdes();
      }
   }
} 

//allocate buffers and spawn DAQ threads
void WDSystem::SpawnDAQ(){
   //number of buffer at each buffer stage
   const int number_of_buffers = 50;
   const int number_of_calibrated_buffers = 100000;

   printf("starting all threads\n");

   //compute number of WDBs and expected number of packets
   int nWDBs=0;
   for(auto &c : fCrate){
      for(auto &b : *c){
         if(b) if(dynamic_cast<WDWDB*>(b) != nullptr) nWDBs++;
      }
   }

   printf("spawning DAQ for %d WDBs...\n", nWDBs);

   //create buffers
   fPacketBuffer= new DAQBuffer<WDAQPacketData>(nWDBs*128*number_of_buffers, "PACKETBUFFER");
   fEventBuffer= new DAQBuffer<WDAQEvent>(number_of_calibrated_buffers, "BUILDBUFFER");
   fCalibratedBuffer= new DAQBuffer<WDAQEvent>(number_of_calibrated_buffers, "EVENTBUFFER");

   // create the TCBReadrer thread

   int nTCBs=0;
   for(auto &c : fCrate){
      for(auto &b : *c){
         if(b) if(dynamic_cast<WDTCB*>(b) != nullptr){
            std::string readEnable;
            try{
               readEnable = b->GetProperty("ReadEnable").GetStringValue();
            } catch (const std::runtime_error& ex){
               readEnable = "false";
            }

            if(readEnable=="true"){
               WDAQTCBReader* tcbreaderthread = new WDAQTCBReader(fPacketBuffer,static_cast<WDTCB*>(b));
               tcbreaderthread->Start();
               fTCBReaderThreads.push_back(tcbreaderthread);
               nTCBs++;
            }
            
         }
      }
   }
   if(fTCBReaderThreads.size())
      printf("including %d TCBs...\n", nTCBs);

   //spawn threads
   fCollectorThread = new WDAQPacketCollector(fPacketBuffer);
   fCollectorThread->Start();
   fBuilderThread = new WDAQEventBuilder(fPacketBuffer, fEventBuffer, nWDBs+nTCBs);
   fBuilderThread->Start();
   fWorkerThread = new WDAQWorker(fEventBuffer, fCalibratedBuffer);
   for(auto &c : fCrate){
      for(auto &b : *c){
         if(b) {
            if(dynamic_cast<WDWDB*>(b) != nullptr){
                fWorkerThread->AddVoltageCalibration(static_cast<WDWDB*>(b)->GetSerialNumber(), &(static_cast<WDWDB*>(b)->mVCalib));
            }
         }
      }
   }
   fWorkerThread->Start();

   std::string noWriter;
   try{
      noWriter = GetDaqProperty("NoWriter").GetStringValue();
   } catch (const std::out_of_range& ex){
      noWriter = "false";
   }
   if(noWriter != "true"){
      std::string filename;
      unsigned int eventsPerFile;
      unsigned int startRunNumber;
      try{
         filename = GetDaqProperty("FileName").GetStringValue();
      } catch (const std::out_of_range& ex){
         filename = "out.bin";
      }
      try{
         eventsPerFile = GetDaqProperty("EventsPerFile").GetUInt();
      } catch (const std::out_of_range& ex){
         eventsPerFile = 0;
      }
      try{
         startRunNumber = GetDaqProperty("StartRunNumber").GetUInt();
      } catch (const std::out_of_range& ex){
         startRunNumber = 0;
      }
      fWriterThread = new WDAQEventWriter(fCalibratedBuffer, filename, eventsPerFile, startRunNumber);
      //fWriterThread = new WDAQEventWriter(fEventBuffer, filename);
      //pass time calibrations to Event Writer
      for(auto &c : fCrate){
         for(auto &b : *c){
            if(b) {
               if(dynamic_cast<WDWDB*>(b) != nullptr){
                  fWriterThread->AddTimeCalibration(dynamic_cast<WDWDB*>(b)->GetSerialNumber(), &(dynamic_cast<WDWDB*>(b)->mTCalib));
               } else if (dynamic_cast<WDTCB*>(b) != nullptr){
                     std::hash<std::string> hashFunc;
                     fWriterThread->AddTcbName(hashFunc(b->GetBoardName()));
               }
            }

         }
      }
      fWriterThread->Start();
   } else {
      printf("No writer thread running\n");
   }

   //wait for server port
   while(fCollectorThread->GetServerPort() == -1){  };
   printf("started on port %d\n", fCollectorThread->GetServerPort());

   //assign server port
   fDAQServerPort = fCollectorThread->GetServerPort();

}

void WDSystem::StopDAQ(){
   fCollectorThread->Stop();
   fBuilderThread->Stop();
   fWorkerThread->Stop();
   fWriterThread->Stop();

   std::this_thread::sleep_for(std::chrono::seconds(10));
   delete fPacketBuffer;
   delete fEventBuffer;
   delete fCalibratedBuffer;
   delete fCollectorThread;
   delete fBuilderThread;
   delete fWorkerThread;
   delete fWriterThread;
}

WDPosition &WDSystem::FindBoard(std::string name){
   return fBoardMap[name];
}

// --- WDWDB ---
// WDBoard derived methods

//connect to the board
void WDWDB::Connect(){
   WDB::Connect();
   ReceiveControlRegisters();
   ReceiveStatusRegisters();
   printf("WD number %d\n", GetSerialNumber());
}

void WDWDB::SetSerdesTraining(bool state){
   unsigned int regbits = GetAdvTrgCtrl();
   SetAdvTrgCtrl((regbits&0xFFFF7FF) | 0x00000430);//MASKSYNC=0, DEBUG_CTRL=1, ALGSEL=3
   SetInCrate();
}

bool WDWDB::IsSerdesTraining(){
   return (((GetAdvTrgCtrl() >>4) ^ 0x43)|0x3C)==0xFF;//require MASKSYNC=0, DEBUG_CTRL=1, ALGSEL=3

}

//Properties
void WDWDB::ConfigureProperty(const std::string &name, Property &property) { 
   if(name=="IPD"){
      ConfigureIPD(property);
   } else if(name=="FrontendGain"){
      ConfigureFrontendGain(property);
   } else if(name=="FrontendPzc"){
      ConfigureFrontendPzc(property);
   } else if(name=="FrontendPzcLevel"){
      ConfigureFrontendPzcLevel(property);
   } else if(name=="TriggerLevel"){
      ConfigureTriggerLevel(property);
   } else if(name=="ChannelPolarity"){
      ConfigureChannelPolarity(property);
   } else if(name=="ChannelHV"){
      ConfigureChannelHV(property);
   } else if(name=="BaselineShift"){
      ConfigureBaselineShift(property);
   } else if(name=="DRSChannelTxEnable"){
      ConfigureDRSChannelTxEnable(property);
   } else if(name=="ADCChannelTxEnable"){
      ConfigureADCChannelTxEnable(property);
   } else if(name=="TDCChannelTxEnable"){
      ConfigureTDCChannelTxEnable(property);
   } else if(name=="TRGTxEnable"){
      ConfigureTRGTxEnable(property);
   } else if(name=="ScalerTxEnable"){
      ConfigureScalerTxEnable(property);
   } else if(name=="ZeroSuppressionEnable"){
      ConfigureZeroSuppression(property);
   } else if(name=="TimingReference"){
      ConfigureTimingReference(property);
   } else if(name=="TriggerAlgorithm"){
      ConfigureTriggerAlgorithm(property);
   } else if(name=="TriggerGain"){
      ConfigureTriggerGain(property);
   } else if(name=="TriggerTdcMask"){
      ConfigureTriggerTdcMask(property);
   } else if(name=="TriggerTdcOffset"){
      ConfigureTriggerTdcOffset(property);
   } else if(name=="TxDebugSignal"){
      ConfigureDebugSignal(0, property);
   } else if(name=="RxDebugSignal"){
      ConfigureDebugSignal(1, property);
   } else if(name=="SamplingFrequency"){
      ConfigureSamplingFrequency(property);
   } else {
      printf("Unknown property %s in WDWDB\n", name.c_str());
   }
};

void WDWDB::ConfigurationStarted(){
   //SetSendBlock(true);
   SetDestinationPort(GetCrate()->GetSystem()->GetDAQServerPort());
   SetFeMux(-1, WDB::cFeMuxInput);
   SetTriggerOutPulseLength(4);
}

void WDWDB::ConfigurationEnded(){
   //SetSendBlock(false);
   //SendControlRegisters();
   SetDaqNormal(true);
   ReceiveStatusRegisters();
}

void WDWDB::ConfigureIPD(Property &property) {
   unsigned int interpacket_delay;
   interpacket_delay = property.GetUHex(); 
   if(interpacket_delay != 0){
      SetInterPkgDelay(interpacket_delay);
   }
}

void WDWDB::ConfigureFrontendGain(Property &property) {
   long arraySize = 0;
   const float* gain;
   gain = property.GetFloatVector(&arraySize);
   
   if(arraySize == 1){
      if(gain[0] != 0.5 && gain[0] != 1 && gain[0] != 2.5 && gain[0] != 5 && gain[0] != 10 && gain[0] != 25 && gain[0] != 50 && gain[0] != 100)
         throw std::runtime_error("Invalid FrontendGain, supported values: 0.5, 1, 2.5, 5, 10, 25, 50, 100");
      else
         SetFeGain(-1, gain[0]);
   } else if(arraySize == 16){
      for(int i=0; i<16; i++){
         if(gain[i] != 0.5 && gain[i] != 1 && gain[i] != 2.5 && gain[i] != 5 && gain[i] != 10 && gain[i] != 25 && gain[i] != 50 && gain[i] != 100)
            throw std::runtime_error("Invalid FrontendGain, supported values: 0.5, 1, 2.5, 5, 10, 25, 50, 100");
         else
            SetFeGain(i, gain[i]);
      }
   } else
      throw std::runtime_error("FrontendGain size should be 1 or 16 values");
}

void WDWDB::ConfigureFrontendPzc(Property &property) {
   long arraySize = 0;
   const int* pzc;
   pzc = property.GetIntVector(&arraySize);
   
   if(arraySize == 1){
      if(pzc[0]!=0 && pzc[0]!=1){
            throw std::runtime_error("Invalid FrontendPzc, supported values: 0 to disable, 1 to enable");
      } else {
         SetFePzc(-1, pzc[0]);
      }
   } else if(arraySize == 16) {
      for(int i=0; i<16; i++){
         if(pzc[i]!=0 && pzc[i]!=1){
            throw std::runtime_error("Invalid FrontendPzc, supported values: 0 to disable, 1 to enable");
         } else {
            SetFePzc(i, pzc[i]);
         }
      }
   } else
      throw std::runtime_error("FrontendPzc size should be 1 or 16 values");
}

void WDWDB::ConfigureFrontendPzcLevel(Property &property) {
   int pzc_value;
   pzc_value = property.GetInt(); 
   if(pzc_value<0 || pzc_value>7)
      throw std::runtime_error("Invalid FrontendPzcLevel, supported values: from 1 to 7");
   else
      SetDacPzcLevelN(pzc_value-1);
}

void WDWDB::ConfigureTriggerLevel(Property &property) {
   long arraySize = 0;
   const float* trigger_level;
   trigger_level = property.GetFloatVector(&arraySize);
   
   if(arraySize == 1){
      if(trigger_level[0]<-1 || trigger_level[0]>1) 
         throw std::runtime_error("Invalid TriggerLevel, supported values: beetween -1 and 1");
      else
         SetDacTriggerLevelV(-1, trigger_level[0]);
   } else if(arraySize == 16){
      for(int i=0; i<16; i++){
         if(trigger_level[i]<-1 || trigger_level[i]>1) 
            throw std::runtime_error("Invalid TriggerLevel, supported values: beetween -1 and 1");
         else
            SetDacTriggerLevelV(i, trigger_level[i]);
      }
   } else
      throw std::runtime_error("TriggerLevel size should be 1 or 16 values");
}

void WDWDB::ConfigureChannelPolarity(Property &property) {
   unsigned int channel_polarity;
   channel_polarity = property.GetUHex();
   channel_polarity &=0xFFFF;

   SetTrgSrcPolarity(channel_polarity);
}

void WDWDB::ConfigureChannelHV(Property &property) {
   long arraySize = 0;
   const float* demand;
   demand = property.GetFloatVector(&arraySize);
   
   if(arraySize == 1){
      for(int i=0; i<16; i++){
         SetHVTarget(i, demand[0]);
      }
   } else if(arraySize == 16){
      for(int i=0; i<16; i++){
         SetHVTarget(i, demand[i]);
      }
   } else
      throw std::runtime_error("ChannelHV size should be 1 or 16 values");
}

void WDWDB::ConfigureBaselineShift(Property &property) {
   float baseline;
   baseline = property.GetFloat();
   if(baseline>1 || baseline<-1)
      throw std::runtime_error("Invalid BaselineShift, supported values: beetween -1 and 1");
   else
      SetRange(baseline);
}

void WDWDB::ConfigureDRSChannelTxEnable(Property &property) {
   unsigned int drstx_ena;
   drstx_ena = property.GetUHex();
   SetDrsChTxEn(drstx_ena);
}

void WDWDB::ConfigureADCChannelTxEnable(Property &property) {
   unsigned int adctx_ena;
   adctx_ena = property.GetUHex();
   SetAdcChTxEn(adctx_ena);
}

void WDWDB::ConfigureTDCChannelTxEnable(Property &property) {
   unsigned int tdctx_ena;
   tdctx_ena = property.GetUHex();
   SetTdcChTxEn(tdctx_ena);
}

void WDWDB::ConfigureTRGTxEnable(Property &property) {
   bool trgtx_ena;
   trgtx_ena = property.GetBool();
   SetTrgTxEn(trgtx_ena);
}

void WDWDB::ConfigureScalerTxEnable(Property &property) {
   bool scalertx_ena;
   scalertx_ena = property.GetBool();
   SetSclTxEn(scalertx_ena);
}

void WDWDB::ConfigureZeroSuppression(Property &property) {
   bool zerosuppr_ena;
   zerosuppr_ena = property.GetBool();
   SetZeroSuprEn(zerosuppr_ena);
}

void WDWDB::ConfigureTimingReference(Property &property) {
   std::string timingreference;
   timingreference = property.GetStringValue();
   if(timingreference == "Off"){
      SetTimingReferenceSignal(WDB::cTimingReferenceOff);
   } else if (timingreference == "Sine"){
      SetTimingReferenceSignal(WDB::cTimingReferenceSine);
   } else if (timingreference == "Square"){
      SetTimingReferenceSignal(WDB::cTimingReferenceSquare);
   } else
      throw std::runtime_error("Invalid TimingReference, supported values: Off, Sine or Square");

}

void WDWDB::ConfigureTriggerAlgorithm(Property &property) {
   unsigned char algorithm;
   algorithm = property.GetUInt();
   SetAdvTrgCtrl(0x00000203 | ((algorithm & 0xF) << 4) );//TDCPolarity, FADCMODE, RUNMODE
   SetAdvTrgPedCfg(0x013E000A);
}

void WDWDB::ConfigureTriggerGain(Property &property) {
   long arraySize = 0;
   const int* trigger_gain;
   trigger_gain = property.GetIntVector(&arraySize);

   int trg_gain[16];
   if(arraySize ==1){
      for(int i=0; i<15; i++) trg_gain[i] = trigger_gain[0];
      arraySize = 16;
   } else if(arraySize ==16) {
      for(int i=0; i<15; i++) trg_gain[i] =  trigger_gain[i];
   } else
      throw std::runtime_error("TriggerGain size should be 1 or 16 values");

   for(int i=0; i<4; i++){
      unsigned int calib=0;
      for (int j=0 ; j<4 ; j++){
         unsigned int temp = trg_gain[i*4+j];
         temp &= 0xFF;
         calib |= temp<<(j*8);
      }
      switch(i){
      case 0:
         SetAdvTrgChCal0(calib);
         break;
      case 1:
         SetAdvTrgChCal1(calib);
         break;
      case 2:
         SetAdvTrgChCal2(calib);
         break;
      case 3:
         SetAdvTrgChCal3(calib);
         break;
      }
   }
}

void WDWDB::ConfigureTriggerTdcMask(Property &property) {
   unsigned int tdcmask;
   tdcmask = property.GetUHex();

   tdcmask &= 0xFFFF;
   SetAdvTrgTdcChMask(tdcmask);
}

void WDWDB::ConfigureTriggerTdcOffset(Property &property) {
   long arraySize = 0;
   const int* tdc_offset;
   tdc_offset = property.GetIntVector(&arraySize);

   int trg_offset[16];
   if(arraySize ==1){
      for(int i=0; i<15; i++) trg_offset[i] = tdc_offset[0];
      arraySize = 16;
   } else if(arraySize ==16) {
      for(int i=0; i<15; i++) trg_offset[i] =  tdc_offset[i];
   } else
      throw std::runtime_error("TriggerTdcOffset size should be 1 or 16 values");

   for(int i=0; i<1; i++){
      unsigned int calib=0;
      for (int j=0 ; j<8 ; j++){
         unsigned int temp = trg_offset[i*8+j];
         temp &= 0xF;
         calib |= temp<<(j*4);
      }
      switch(i){
      case 0:
         SetAdvTrgCfg12(calib);
         break;
      case 1:
         SetAdvTrgCfg13(calib);
         break;
      }
   }
}

void WDWDB::ConfigureDebugSignal(int port, Property &property) {
   std::string confString;
   int conf;

   confString = property.GetStringValue();
   if(confString == "Uart"){
      conf = WDB::cDbgUart; 
   } else if (confString == "Trigger"){
      conf = WDB::cDbgTrigger; 
   } else if (confString == "SoftTrigger"){
      conf = WDB::cDbgSoftTrigger; 
   } else if (confString == "ExtTrigger"){
      conf = WDB::cDbgExtTrigger; 
   } else if (confString == "SyncDirect"){
      conf = WDB::cDbgSyncDirect; 
   } else if (confString == "SyncSampled"){
      conf = WDB::cDbgSyncSampled; 
   } else if (confString == "SyncLogic"){
      conf = WDB::cDbgSyncInternal; 
   } else if (confString == "BusyLocal"){
      conf = WDB::cDbgBusyLocal; 
   } else if (confString == "BusyBackplane"){
      conf = WDB::cDbgBusyBackplane; 
   } else if (confString == "LMKInputClk"){
      conf = WDB::cDbgLMKInputClk; 
   } else if (confString == "ADCClk"){
      conf = WDB::cDbgADCClk; 
   } else if (confString == "DataClk"){
      conf = WDB::cDbgDataClk; 
   } else if (confString == "LMK5Clk"){
      conf = WDB::cDbgLMK5Clk; 
   } else if (confString == "LMKChipSelect"){
      conf = WDB::cDbgLMKChipSelect; 
   } else {
      conf = WDB::cDbgSyncDirect; 
   }

   switch(port){
   case 0:
      SetMcxTxSigSel(conf);
      break;
   case 1:
      SetMcxRxSigSel(conf);
      break;
   default:
      break;
   }
}

void WDWDB::ConfigureSamplingFrequency(Property &property) {
   unsigned int freq;
   freq = property.GetUInt();

   bool isSendBlocked = GetSendBlock();
   if(isSendBlocked) SetSendBlock(false);
   SetDrsSampleFreq(freq);
   if(isSendBlocked) SetSendBlock(true);

   if (!LoadVoltageCalibration(GetDrsSampleFreqMhz(), "/home/git/wavedaq/software/wds/")) {
      printf("missing voltage calibration file\n");
   }
   if (!LoadTimeCalibration(GetDrsSampleFreqMhz(), "/home/git/wavedaq/software/wds/")) {
      printf("missing time calibration file\n");
   }

}

// Set configurations to be used in a crate
void WDWDB::SetInCrate(){
   SetPatternTriggerEn(0);
   SetExtAsyncTriggerEn(1);
   SetExtTriggerOutEnable(0);

   if(GetExtClkInSel() != 0 || GetDaqClkSrcSel() != 0 || GetLmkInputFreq() != 80){

      SetSendBlock(true);
      SetExtClkInSel(0);
      SetDaqClkSrcSel(0);
      SetLmkInputFreq(80);
      SetSendBlock(false);
      SendControlRegisters();

      SetApplySettingsLmk(1);
      LmkSyncLocal();
      ReceiveStatusRegister(WD2_DRS_SAMPLE_FREQ_REG);

      //Reset everything
      ResetAllPll();
      ResetTcbOserdesIf();
      ResetDrsControlFsm();
   }
}

// --- WDTCB ---
// WDBoard derived methods
void WDTCB::Connect(){
   SetIDCode();
   SetNTRG();
   printf("connected to TCB with IDCode = %04x\n", fidcode);

   //reset stuff
   ResetIDLYCTRL();
   ResetSyncWaveformSerdes();
   ResetBufferLogic();
}

void WDTCB::SetSerdesTraining(bool state){
   u_int32_t rrun;
   ReadReg(RRUN,&rrun);
   rrun |= 0x4000; //enable MASKSYNC
   rrun |= 0x10;   //enable ENABLE TRGBUS
   //enable serdespattern according to request
   if(state){
      rrun |= 0x00000200;

      //if enabling also reset transmitter SERDES
      ResetTransmitter();
   } else {
      rrun &= 0xFFFFFDFF;
   }
   SetRRUN(&rrun);
}

bool WDTCB::IsSerdesTraining(){
   unsigned int val=0;
   GetRRUN( &val );
   return (val >> 9) & 0x1;

}

void WDTCB::ConfigureProperty(const std::string &name, Property &property) { 
   if(name=="TriggerEnable"){
      ConfigureTriggerEnable(property);
   } else if(name=="TriggerPrescaling"){
      ConfigureTriggerPrescaling(property);
   } else if(name=="TriggerDelay"){
      ConfigureTriggerDelay(property);
   } else if(name=="TriggerAlgorithm"){
      ConfigureTriggerAlgorithm(property);
   } else if(name=="Parameters"){
      ConfigureParameters(property);
   } else if(name=="ReadEnable"){
      ConfigurePacketizer(property);
   } else if(name=="ExtDAQBusyMask"){
      ConfigureExtDAQ(property);
   } else if(name=="XecHighThreshold"){
      ConfigureXecHighThreshold(property);
   } else if(name=="XecLowThreshold"){
      ConfigureXecLowThreshold(property);
   } else if(name=="XecVetoThreshold"){
      ConfigureXecVetoThreshold(property);
   } else if(name=="XecPatchId"){
      ConfigureXecPatchId(property);
   } else if(name=="XecAlfaThreshold"){
      ConfigureXecAlfaThreshold(property);
   } else if(name=="XecAlfaScale"){
      ConfigureXecAlfaScale(property);
   } else if(name=="XecMovingAverage"){
      ConfigureXecMovingAverage(property);
   } else if(name=="TcMask"){
      ConfigureTcMask(property);
   } else if(name=="TcMultiplicityThreshold"){
      ConfigureTcMultiplicityThreshold(property);
   } else if(name=="TcCrateMergeThreshold"){
      ConfigureTcCrateMergeThreshold(property);
   } else if(name=="TcSectorMergeThreshold"){
      ConfigureTcSectorMergeThreshold(property);
   } else if(name=="BgoThreshold"){
      ConfigureBgoThreshold(property);
   } else if(name=="BgoVetoThreshold"){
      ConfigureBgoVetoThreshold(property);
   } else if(name=="BgoHitDelay"){
      ConfigureBgoHitDelay(property);
   } else if(name=="BgoTriggerMask"){
      ConfigureBgoTriggerMask(property);
   } else if(name=="RdcThreshold"){
      ConfigureRdcThreshold(property);
   } else if(name=="RdcTriggerMask"){
      ConfigureRdcTriggerMask(property);
   } else if(name=="CrcHitMask"){
      ConfigureCrcHitMask(property);
   } else if(name=="CrcPairMask"){
      ConfigureCrcPairMask(property);
   } else {
      printf("Unknown property %s in WDTCB\n", name.c_str());
   }
};

void WDTCB::ConfigurationStarted(){
   u_int32_t rrun_config = 0x0000E014;  //masktrg, masksync, maskbusy, fadcmode, enable trg_bus
   SetRRUN(&rrun_config);
   u_int32_t syncdly=0x1F;
   u_int32_t trgdly=0x1F;
   u_int32_t sprdly=0x1F;
   SetTRGBusIDLY(&syncdly, &trgdly, &sprdly);
   syncdly=0x10;
   trgdly=0x10;
   sprdly=0x10;
   SetTRGBusODLY(&syncdly, &trgdly, &sprdly);
   SetPacketizerAutostart(true);
   SetPacketizerEnable(true);
}

void WDTCB::ConfigurationEnded(){
   //if((fidcode >>12) != 3)
   //   GoRun();
}

void WDTCB::ConfigureTriggerEnable(Property &property){
   long arraySize = 0;
   const unsigned int* trigger_enable;
   trigger_enable = GetProperty("TriggerEnable").GetUIntVector(&arraySize);

   bool trg_ena[64];
   for(int i=0; i<64; i++) trg_ena[i] = false;
   for(unsigned long i=0; i<arraySize; i++) 
      if(trigger_enable[i] < 64)
         trg_ena[trigger_enable[i]] = true;

   SetTriggerEnable(trg_ena);
}

void WDTCB::ConfigureTriggerPrescaling(Property &property){
   long arraySize = 0;
   const unsigned int* trigger_prescaling;
   trigger_prescaling = property.GetUIntVector(&arraySize);

   long arraySizeEnable = 0;
   const unsigned int* trigger_enable;
   try{
      trigger_enable = GetProperty("TriggerEnable").GetUIntVector(&arraySizeEnable);
   } catch (const std::runtime_error& ex){
      throw std::runtime_error("Cannot set TriggerPrescaling: TriggerEnable should be also defined");
   }
   unsigned int trg_presca[64];
   for(int i=0; i<64; i++) trg_presca[i] = 0;
   if(arraySizeEnable != arraySize)
      throw std::runtime_error("Cannot set TriggerPrescaling: TriggerEnable has a different array length");
   else {
      for(unsigned long i=0; i<arraySize; i++)
         if(trigger_enable[i] < 64)
            trg_presca[trigger_enable[i]] = trigger_prescaling[i];

      SetPrescaling(trg_presca);
   }
}

void WDTCB::ConfigureTriggerDelay(Property &property){
   long arraySize = 0;
   const unsigned int* trigger_delay;
   trigger_delay = property.GetUIntVector(&arraySize);

   long arraySizeEnable = 0;
   const unsigned int* trigger_enable;
   try{
      trigger_enable = GetProperty("TriggerEnable").GetUIntVector(&arraySizeEnable);
   } catch (const std::runtime_error& ex){
      throw std::runtime_error("Cannot set TriggerDelay: TriggerEnable should be also defined");
   }
   unsigned int trg_delay[64];
   for(int i=0; i<64; i++) trg_delay[i] = 0;
   if(arraySizeEnable != arraySize)
      throw std::runtime_error("Cannot set TriggerDelay: TriggerEnable has a different array length");
   else {
      for(unsigned long i=0; i<arraySize; i++)
         if(trigger_enable[i] < 64)
            trg_delay[trigger_enable[i]] = trigger_delay[i];

      SetTRGDLY(trg_delay);
   }
}

void WDTCB::ConfigureTriggerAlgorithm(Property &property){
   unsigned int algorithm;
   algorithm = property.GetUInt();

   SetRALGSEL((unsigned int *)&algorithm);
}

void WDTCB::ConfigureParameters(Property &property){
   long arraySize = 0;
   const unsigned int* parameters;

   parameters = property.GetUHexVector(&arraySize);
   for(int i=0; i<arraySize-1; i+=2){
      unsigned int val = parameters[i+1];
      SetParameter(parameters[i], &val);
   }
}

void WDTCB::ConfigurePacketizer(Property &property){
   bool readEnable;
   readEnable = property.GetBool();

   if(readEnable){
      std::vector<PacketInstruction> instVec;
      PacketInstruction inst;

      inst.offset = 0;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 3;//nbanks
      inst.arg1 = BUFFERBASE;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::BLOCK_COPY;
      inst.arg0 = MEMBASEADDR;
      inst.arg1 = BUFFERBASE+10;
      inst.arg2 = 1024;
      instVec.push_back(inst);
      inst.arg2 = 0;

      inst.offset += 1;
      inst.cmd = ::BLOCK_COPY;
      inst.arg0 = MEMBASEADDR;
      inst.arg1 = BUFFERBASE+10;
      inst.arg2 = 1024;
      instVec.push_back(inst);
      inst.arg2 = 0;

      inst.offset += 1;
      inst.cmd = ::COPY;
      inst.arg0 = REVECOU;
      inst.arg1 = BUFFERBASE+1;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::COPY;
      inst.arg0 = RTOTTIME;
      inst.arg1 = BUFFERBASE+2;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::COPY;
      inst.arg0 = RSYSTRITYPE;
      inst.arg1 = BUFFERBASE+3;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::COPY;
      inst.arg0 = RSYSEVECOU;
      inst.arg1 = BUFFERBASE+4;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 0x494E3035;//IN05
      inst.arg1 = BUFFERBASE+5;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 2*MEMDIM+1;
      inst.arg1 = BUFFERBASE+6;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::COPY;
      inst.arg0 = RMEMADDR;
      inst.arg1 = BUFFERBASE+7;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::BLOCK_COPY;
      inst.arg0 = MEMBASEADDR+5*(MEMDIM*2);
      inst.arg1 = BUFFERBASE+8;
      inst.arg2 = 2*MEMDIM;
      instVec.push_back(inst);
      inst.arg2 = 0;

      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 0x494E3038;//IN08
      inst.arg1 = BUFFERBASE+8+(2*MEMDIM);
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 2*MEMDIM+1;
      inst.arg1 = BUFFERBASE+8+(2*MEMDIM)+1;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::COPY;
      inst.arg0 = RMEMADDR;
      inst.arg1 = BUFFERBASE+8+(2*MEMDIM)+2;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::BLOCK_COPY;
      inst.arg0 = MEMBASEADDR+8*(MEMDIM*2);
      inst.arg1 = BUFFERBASE+8+(2*MEMDIM)+3;
      inst.arg2 = 2*MEMDIM;
      instVec.push_back(inst);
      inst.arg2 = 0;

      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 0x47454e54;//GENT
      inst.arg1 = BUFFERBASE+8+(2*MEMDIM)+3+(2*MEMDIM);
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 2*GENTDIM+1;
      inst.arg1 = BUFFERBASE+8+(2*MEMDIM)+3+(2*MEMDIM)+1;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::COPY;
      inst.arg0 = RMEMADDR;
      inst.arg1 = BUFFERBASE+8+(2*MEMDIM)+3+(2*MEMDIM)+2;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::BLOCK_COPY;
      inst.arg0 = GENTMEMBASE;
      inst.arg1 = BUFFERBASE+8+(2*MEMDIM)+3+(2*MEMDIM)+3;
      inst.arg2 = 2*GENTDIM;
      instVec.push_back(inst);
      inst.arg2 = 0;

      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 1;
      inst.arg1 = PACK_NEXT_BUFFER;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::STOP;
      instVec.push_back(inst);

      WritePacketizerProgram(instVec);
   } else {
      SetPacketizerCommandAt(0, STOP, 0, 0);
   }
}

void WDTCB::ConfigureExtDAQ(Property &property){
   bool extdaqbmask;
   extdaqbmask = property.GetBool();

   SetFMask(false, extdaqbmask);
}

void WDTCB::ConfigureXecHighThreshold(Property &property){
   unsigned int xechighthreshold;
   xechighthreshold = property.GetUHex();

   SetSumHighThreshold(&xechighthreshold);
}

void WDTCB::ConfigureXecLowThreshold(Property &property){
   unsigned int xeclowthreshold;
   xeclowthreshold = property.GetUHex();

   SetSumLowThreshold(&xeclowthreshold);
}

void WDTCB::ConfigureXecVetoThreshold(Property &property){
   unsigned int xecvetothreshold;
   xecvetothreshold = property.GetUHex();

   SetSumVetoThreshold(&xecvetothreshold);
}

void WDTCB::ConfigureXecPatchId(Property &property){
   unsigned int xecpatchid;
   xecpatchid = property.GetUHex();

   SetSumPatch(&xecpatchid);
}

void WDTCB::ConfigureXecAlfaThreshold(Property &property){
   unsigned int xecalfathreshold;
   xecalfathreshold = property.GetUHex();

   SetAlphaThreshold(&xecalfathreshold);
}

void WDTCB::ConfigureXecAlfaScale(Property &property){
   float xecalfascale;
   xecalfascale = property.GetFloat();

   SetAlphaPeakScale(xecalfascale);
}

void WDTCB::ConfigureXecMovingAverage(Property &property){
   bool xecmovingaverage;
   xecmovingaverage = property.GetBool();

   unsigned int val;
   if(xecmovingaverage){
      val = 1;
   } else {
      val = 0;
   }

   SetQsumSelect(&val);
}

void WDTCB::ConfigureTcMask(Property &property){
   long arraySize = 0;
   const unsigned int* masks;

   masks = property.GetUHexVector(&arraySize);
   if(arraySize == 4){
      SetTCMasks((unsigned int*)masks);
   } else
      throw std::runtime_error("TcMask size should be 4 values");
}

void WDTCB::ConfigureTcMultiplicityThreshold(Property &property){
   unsigned int multtheshold;
   multtheshold = property.GetInt();

   SetAlphaThreshold(&multtheshold);
}

void WDTCB::ConfigureTcCrateMergeThreshold(Property &property){
   long arraySize = 0;
   const unsigned int* thresholds;

   thresholds = property.GetUHexVector(&arraySize);
   if(arraySize == 2){
      SetTCCrateMergeThreshold((unsigned int*)thresholds, (unsigned int*)thresholds+1);
   } else
      throw std::runtime_error("TcCrateMergeThreshold size should be 2 values");
}

void WDTCB::ConfigureTcSectorMergeThreshold(Property &property){
   long arraySize = 0;
   const unsigned int* thresholds;

   thresholds = property.GetUHexVector(&arraySize);
   if(arraySize == 2){
      SetTCSectorMergeThreshold((unsigned int*)thresholds, (unsigned int*)thresholds+1);
   } else
      throw std::runtime_error("TcSectorMergeThreshold size should be 2 values");
}

void WDTCB::ConfigureBgoThreshold(Property &property){
   unsigned int bgothreshold;
   bgothreshold = property.GetUHex();

   SetBGOThreshold(&bgothreshold);
}

void WDTCB::ConfigureBgoVetoThreshold(Property &property){
   unsigned int bgovetothreshold;
   bgovetothreshold = property.GetUHex();

   SetBGOVetoThreshold(&bgovetothreshold);
}

void WDTCB::ConfigureBgoHitDelay(Property &property){
   unsigned int bgohitdelay;
   bgohitdelay = property.GetUInt();

   SetBGOHitDelay(&bgohitdelay);
}

void WDTCB::ConfigureBgoTriggerMask(Property &property){
   unsigned int bgotriggermask;
   bgotriggermask = property.GetUHex();

   SetBGOTriggerMask(&bgotriggermask);
}

void WDTCB::ConfigureRdcThreshold(Property &property){
   unsigned int rdcthreshold;
   rdcthreshold = property.GetUHex();

   SetRDCThreshold(&rdcthreshold);
}

void WDTCB::ConfigureRdcTriggerMask(Property &property){
   unsigned int rdctriggermask;
   rdctriggermask = property.GetUHex();

   SetRDCTriggerMask(&rdctriggermask);
}

void WDTCB::ConfigureCrcHitMask(Property &property){
   unsigned int crchitmask;
   crchitmask = property.GetUHex();

   SetCRCHitMask(&crchitmask);
}

void WDTCB::ConfigureCrcPairMask(Property &property){
   unsigned int crcpairmask;
   crcpairmask = property.GetUHex();

   SetCRCPairEnable(&crcpairmask);
}

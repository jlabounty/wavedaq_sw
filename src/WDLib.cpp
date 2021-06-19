#include "WDLib.h"
#include "WDAQLib.h"
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

// Contructor in a crate
WDBoard::WDBoard(WDCrate * crate, char slot, std::string name){
   fBoardName = name;

   crate->AddBoard(this, slot);
}

// Get board position
WDPosition WDBoard::GetPosition(){
   long crateid = -1;
   WDCrate* c= GetCrate();

   if(c)
      crateid = c->GetCrateNumber();
   WDPosition p(crateid, fSlot);
   return p;
}


// --- WDCrate --- 
// Board Adder
void WDCrate::AddBoard(WDBoard *board, int slot){
   if(slot > 17 || slot < -1) throw std::runtime_error("slot out of range");
   if(fBoard[slot] != 0) throw std::runtime_error("two board in same slot");

   //Add Board
   fBoard[slot] = board;
   board->fSlot = slot;
   board->fCrate = this;

   //Add to System Map
   if(fSystem != nullptr) {
      fSystem->fBoardMap[board->fBoardName] = WDPosition(fCrateNumber, slot);
   }

   //if crate has a group set board one to match
   if(fGroupName.length() > 0 ){
      board->SetGroup(fGroupName);
   }
}

// Checks slot is filled
bool WDCrate::HasBoardIn(int slot){
   if(fBoard[slot]) return true;
   else return false;
}

//Power On
void WDCrate::PowerOn(){
   if(fMscbHandle){
      char val = 1;
      int status = mscb_write(fMscbHandle, 20, 0, &val, sizeof(val));
      // print something only in case of error
      if (status != MSCB_SUCCESS)
         printf("Error: status = %d\n", status);
   } 
}

//Power Off
void WDCrate::PowerOff(){
   if(fMscbHandle){
      char val = 0;
      int status = mscb_write(fMscbHandle, 20, 0, &val, sizeof(val));
      // print something only in case of error
      if (status != MSCB_SUCCESS)
         printf("Error: status = %d\n", status);
   } 
}

//Check Power state
bool WDCrate::IsPowered(){
   if(fMscbHandle){
      char val = 0;
      int size = 1;
      int status = mscb_read(fMscbHandle, 20, 0, &val, &size);
      // print something only in case of error
      if (status != MSCB_SUCCESS)
         printf("Error: status = %d\n", status);

      return (val==1)? true: false;
   } else {
      return true;
   }
}

// Board Getter
WDBoard* WDCrate::GetBoardAt(int slot){
   if(fBoard[slot]) return fBoard[slot];
   else return nullptr;
}

// --- WDSystem --- 
// Get tagged Crates
WDCrate *WDSystem::GetTriggerCrate(){ 
   if(fTrgCrateId >= 0)
      return fCrate.at(fTrgCrateId);
   else 
      return nullptr;
}
WDCrate *WDSystem::GetDistributionCrate(){
   if(fDistributionCrateId >= 0)
      return fCrate.at(fDistributionCrateId);
   else return nullptr;
}

// Get tagged Boards
WDBoard *WDSystem::GetTriggerBoard(){
   WDCrate *trgCrate = GetTriggerCrate();
   if(trgCrate)
      return GetTriggerCrate()->GetBoardAt(17);
   else
      return nullptr;
}
WDBoard *WDSystem::GetDistributionBoard(){
   WDCrate *distribCrate = GetDistributionCrate();
   if(distribCrate)
      return GetDistributionCrate()->GetBoardAt(16);
   else
      return nullptr;
}

// Crate Adder
void WDSystem::AddCrate(WDCrate *crate){
   fCrate.push_back(crate);
   //if no trigger crate new crate is defined so
   if(fTrgCrateId < 0) {
      fTrgCrateId = fCrate.size() - 1;
   }
   //if no distribution crate new crate is defined so
   if(fDistributionCrateId < 0) {
      fDistributionCrateId = fCrate.size() - 1;
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

   char error[100];
   int line;
   MXML_NODE *root_xml = mxml_parse_file(filepath.c_str(), error, sizeof(error), &line);
   if(root_xml == NULL){
      throw std::runtime_error(error);
   }
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

         //add a group for that crate
         char* crategroupstring = mxml_get_attribute(crate_xml, "Group");
         if(crategroupstring!=NULL){
            c->SetGroup(std::string(crategroupstring));
         }

         AddCrate(c);

         bool triggerFlag = false;
         bool distributionFlag = false;
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

               //try to get a HostName (ip), if not given use Name attribute
               char* hostnamestring = mxml_get_attribute(board_xml, "HostName");
               if(hostnamestring == NULL) {
                  hostnamestring = namestring;
               }

               WDWDB *b = new WDWDB(c, atoi(slotstring), std::string(namestring), std::string(hostnamestring));

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
            else if(board_node_name == "DCB"){
               //create a new board
               
               char* slotstring = mxml_get_attribute(board_xml, "Slot");
               char* namestring = mxml_get_attribute(board_xml, "Name");
               if(slotstring == NULL || namestring==NULL) {
                  printf("error parsing XML: DCB needs a Slot and a Name attributes\n");
                  return;
               }

               //try to get a HostName (ip), if not given use Name attribute
               char* hostnamestring = mxml_get_attribute(board_xml, "HostName");
               if(hostnamestring == NULL) {
                  printf("warning parsing XML: DCB Name used as MscbNode name\n");
                  hostnamestring = hostnamestring;
               }

               WDDCB *b = new WDDCB(c, atoi(slotstring), std::string(namestring),  std::string(hostnamestring));

               //board property group is optional
               char* groupstring = mxml_get_attribute(board_xml, "Group");
               if(groupstring!=NULL){
                  b->SetGroup(groupstring);
               }

               //parse remaining tags as properties
               CreatePropertiesFromXml(b, board_xml);
            }
            else if(board_node_name == "Trigger") triggerFlag = true;
            else if(board_node_name == "Distribution") distributionFlag = true;
         }

         if(triggerFlag){
            SetTriggerCrateId(GetCrateSize()-1);
         }
         if(distributionFlag){
            SetDistributionCrateId(GetCrateSize()-1);
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

//Connect to all board in the system
void WDSystem::Connect(){
   for(auto &c : fCrate){
      printf("Connecting to crate %s:\n", c->GetCrateName().c_str());
      //Connect to central slots
      if(c->HasBoardIn(16)) 
         c->GetBoardAt(16)->Connect();
      if(c->HasBoardIn(17)) 
         c->GetBoardAt(17)->Connect();

      //Connect to other slots
      for(int i=0; i<16; i++){
         if(c->HasBoardIn(i)) 
            c->GetBoardAt(i)->Connect();
      }
   }

}


//Configure all board in the system
void WDSystem::Configure(bool wait){
   for(auto &c : fCrate){
      printf("configuring crate %s\n", c->GetCrateName().c_str());
      for(int i=0; i<18; i++){
         if(c->HasBoardIn(i)) 
            c->GetBoardAt(i)->Configure();
      }
   }

   Sync();//this is to assure everything is loaded

   if(wait) WaitReady();
}

//Power On
void WDSystem::PowerOn(){
   //first switch on distribution and trigger crate
   GetDistributionCrate()->PowerOn();
   sleep(10);
   GetTriggerCrate()->PowerOn();
   for(auto &c : fCrate){
      c->PowerOn();
   }
   //std::this_thread::sleep_for(std::chrono::seconds(10));
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
   sleep(5);
}

//System Sync
void WDSystem::Sync(){
   WDBoard *syncBoard = GetDistributionBoard();

   if(! syncBoard){
      syncBoard = GetTriggerBoard();
   }

   //SYNC!
   if(syncBoard){
      syncBoard->Sync();
   //this is to crash if no board is available: disabled
   //} else {
   //   throw std::runtime_error("no board to generate sync");
   }
}

//Go Run
void WDSystem::GoRun(){
   Sync();

   //start DAQ system run
   fDaqSystem->GoRun();
   fDaqSystem->WaitRunStarted();

   //start master trigger board
   WDBoard* triggerBoard = GetTriggerBoard();
   if(triggerBoard) {
      triggerBoard->GoRun();
   //this is to crash if no board is available: disabled
   //} else {
   //   throw std::runtime_error("no trigger board");
   }
}

//Stop Run
void WDSystem::StopRun(){
   //stop master trigger board
   WDBoard* triggerBoard = GetTriggerBoard();
   if(triggerBoard) {
      triggerBoard->StopRun();
   //this is to crash if no board is available: disabled
   //} else {
   //   throw std::runtime_error("no trigger board");
   }

   //stop DAQ system run
   fDaqSystem->StopRun();
   fDaqSystem->WaitRunStopped();

   //clean all DAQ buffers 
   fDaqSystem->CleanBuffers();

}

//train serial links
void WDSystem::TrainSerdes(bool wait){
   //WaitClockLock();

   Sync();

   WaitClockLock();

   for(auto &c : fCrate){
      for(auto &b : *c){
         if(b) b->TrainSerdes();
      }
   }
   
   if(wait) WaitSerdesTrainingFinish();
} 

//block until all boards serdes were trained
void WDSystem::WaitSerdesTrainingFinish(){
   for(auto &c : fCrate){
      for(auto &b : *c){
         if(b) b->WaitSerdesTrainingFinish();
      }
   }
}

//block until all boards PLLs are locked
void WDSystem::WaitClockLock(){
   for(auto &c : fCrate){
      for(auto &b : *c){
         if(b) b->WaitClockLock();
      }
   }
}

//block until all boards are ready
void WDSystem::WaitReady(){
   for(auto &c : fCrate){
      for(auto &b : *c){
         if(b) b->WaitReady();
      }
   }
}

//check all serdes lines are good
bool WDSystem::IsSerdesGood(){
   for(auto &c : fCrate){
      for(auto &b : *c){
         if(b)
            if(!b->IsSerdesGood())
               return false;
      }
   }

   return true;
}

//allocate buffers and spawn DAQ threads
void WDSystem::SpawnDAQ(){
   //number of buffer at each buffer stage
  const int number_of_buffers = 10; 
  const int number_of_calibrated_buffers = 10; 

   printf("starting all threads\n");

   //compute number of WDBs and expected number of packets
   int nWDBs=0;
   int nTCBs=0;
   for(auto &c : fCrate){
      for(auto &b : *c){
         if(b) if(dynamic_cast<WDWDB*>(b) != nullptr) nWDBs++;
         if(b) if(dynamic_cast<WDTCB*>(b) != nullptr) nTCBs++;
      }
   }

   printf("spawning DAQ for %d WDBs and %d TCBs...\n", nWDBs, nTCBs);

   //preallocate Memory pool objects
   #ifdef USEMEMORYPOOL
   DAQMemoryPool<WDAQDRSPacketData>::GetInstance().PreAllocate(2*18*number_of_buffers*nWDBs);
   DAQMemoryPool<WDAQADCPacketData>::GetInstance().PreAllocate(4*16*number_of_buffers*nWDBs);
   DAQMemoryPool<WDAQTDCPacketData>::GetInstance().PreAllocate(16*number_of_buffers*nWDBs);
   DAQMemoryPool<WDAQTRGPacketData>::GetInstance().PreAllocate(4*number_of_buffers*nWDBs);
   DAQMemoryPool<WDAQScaPacketData>::GetInstance().PreAllocate(number_of_buffers*nWDBs);
   DAQMemoryPool<WDAQDummyPacketData>::GetInstance().PreAllocate(number_of_buffers*nWDBs);
   DAQMemoryPool<WDAQTcbPacketData>::GetInstance().PreAllocate(5*number_of_buffers*nTCBs);
   DAQMemoryPool<WDAQWdbEvent>::GetInstance().PreAllocate(number_of_calibrated_buffers*nWDBs*4);
   DAQMemoryPool<WDAQTcbBank>::GetInstance().PreAllocate(5*number_of_calibrated_buffers*nTCBs*4);
   DAQMemoryPool<WDAQTcbEvent>::GetInstance().PreAllocate(number_of_calibrated_buffers*nTCBs*4);
   DAQMemoryPool<WDAQEvent>::GetInstance().PreAllocate(number_of_calibrated_buffers*4);
   #endif
   //create buffers
   int nBuilders;
   try{
      nBuilders = GetDaqProperty("Builders").GetInt();
      if(nBuilders < 1) nBuilders = 1; //make sure at least a builder is running
   } catch (const std::out_of_range& ex){
      nBuilders = 1;
   }
   fPacketBuffer= new DAQFanoutBuffer<WDAQPacketData>(nBuilders,(nWDBs*128+nTCBs*5)*number_of_buffers*(1./nBuilders), "PACKETBUFFER", fDaqSystem);
   fEventBuffer= new DAQBuffer<WDAQEvent>(number_of_calibrated_buffers, "BUILDBUFFER", fDaqSystem);
   fCalibratedBuffer= new DAQBuffer<WDAQEvent>(number_of_calibrated_buffers, "EVENTBUFFER", fDaqSystem);

   // counts TCB transmitting data, create the TCBReadrer thread if needed
   nTCBs=0;
   for(auto &c : fCrate){
      for(auto &b : *c){
         if(b) if(dynamic_cast<WDTCB*>(b) != nullptr){
            std::string readEnable;
            try{
               readEnable = b->GetProperty("Banks").GetStringValue();
               
               //if there is no DCB try trough CMB
               if(! static_cast<WDTCB*>(b)->HasDcbInterface()){
                  WDAQTCBReader* tcbreaderthread = new WDAQTCBReader(fPacketBuffer,static_cast<WDTCB*>(b), fDaqSystem);
                  tcbreaderthread->SetIdleLoopDuration(std::chrono::milliseconds(10));
                  fTCBReaderThreads.push_back(tcbreaderthread);
               }
               nTCBs++;

            } catch (const std::runtime_error& ex){
            }
            
         }
      }
   }
   if(fTCBReaderThreads.size())
      printf("including %d TCB reader...\n", nTCBs);

   //spawn threads
   //Collectors
   int nCollectors;
   try{
      nCollectors = GetDaqProperty("Collectors").GetInt();
      if(nCollectors < 1) nCollectors = 1; //make sure at least a collector is running
   } catch (const std::out_of_range& ex){
      nCollectors = 1;
   }

   for(int i=0; i<nCollectors; i++){
      WDAQPacketCollector* collector = new WDAQPacketCollector(fPacketBuffer, nWDBs+nTCBs, fDaqSystem);
      try{
         int daqport = GetDaqProperty("Port").GetInt();
         collector->SetServerPort(daqport);
      } catch (const std::out_of_range& ex){
      }

      fCollectorThreads.push_back(collector);
   }

   //Builder
   for(int i=0; i<nBuilders; i++){
      WDAQEventBuilder* builder = new WDAQEventBuilder(fPacketBuffer->GetBufferAt(i), fEventBuffer, nWDBs+nTCBs, fDaqSystem);
      fBuilderThreads.push_back(builder);
   }

   //Workers
   int nWorkers;
   try{
      nWorkers = GetDaqProperty("Workers").GetInt();
   } catch (const std::out_of_range& ex){
      nWorkers = 1;
   }

   for(int i=0; i<nWorkers; i++){
      WDAQWorker* workerThread = new WDAQWorker(fEventBuffer, fCalibratedBuffer, fDaqSystem);
      for(auto &c : fCrate){
         for(auto &b : *c){
            if(b) {
               if(dynamic_cast<WDWDB*>(b) != nullptr){
                   workerThread->AddVoltageCalibration(b->GetSerialNumber(), &(static_cast<WDWDB*>(b)->mVCalib));
               }
            }
         }
      }
      fWorkerThreads.push_back(workerThread);
   }

   //Writer
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
      fWriterThread = new WDAQEventWriter(fCalibratedBuffer, filename, eventsPerFile, startRunNumber, fDaqSystem);
      //fWriterThread = new WDAQEventWriter(fEventBuffer, filename, eventsPerFile, StartRunNumber, fDaqSystem);
      //pass time calibrations to Event Writer
      for(auto &c : fCrate){
         for(auto &b : *c){
            if(b) {
               if(dynamic_cast<WDWDB*>(b) != nullptr){
                  fWriterThread->AddTimeCalibration(b->GetSerialNumber(), &(static_cast<WDWDB*>(b)->mTCalib));
               } else if (dynamic_cast<WDTCB*>(b) != nullptr){
                     fWriterThread->AddTcbName(b->GetSerialNumber());
               }
            }

         }
      }
   } else {
      printf("No writer thread running\n");
   }

   fDaqSystem->Start();

   //wait for server port
   for(auto t: fCollectorThreads) {
      while(t->GetServerPort() == 0) std::this_thread::yield();
      printf("started on port %d\n", t->GetServerPort());
      //assign server port
      AddDAQServerPort(t->GetServerPort());
   }
}

void WDSystem::StopDAQ(){
   delete fDaqSystem;
   fDaqSystem = new DAQSystem();

   //also invalidate local pointers to threads
   fPacketBuffer = nullptr;
   fEventBuffer = nullptr;
   fCalibratedBuffer = nullptr;
   fCollectorThreads.clear();
   fBuilderThreads.clear();
   fWorkerThreads.clear();
   fWriterThread = nullptr;
   fTCBReaderThreads.clear();
}

WDPosition &WDSystem::FindBoard(std::string name){
   return fBoardMap[name];
}

// --- WDWDB ---
// Constructor
WDWDB::WDWDB(WDCrate *crate, int slot, std::string name, std::string netname, bool verbose) : WDB(netname, verbose), WDBoard(crate, slot, name){
   if(crate->HasBoardIn(16)){
      //Get board in slot 16 (DCB slot)
      WDBoard *b = crate->GetBoardAt(16);

      if(dynamic_cast<WDDCB*>(b)!=nullptr){
         //crate has a DCB in slot 16, switch to it
         SetDcbInterface(static_cast<WDDCB*>(b), slot);
      }
   } else {
      // no DCB (yet?)
   }
}

// WDBoard derived methods

//connect to the board
void WDWDB::Connect(){
   WDB::Connect();
   ReceiveControlRegisters();
   ReceiveStatusRegisters();

   //Set SlotId and CrateId
   WDCrate *crate = GetCrate();
   if(crate != nullptr){
      //Set SlotId
      SetSlotId(GetSlot());

      int64_t crateNumber = crate->GetCrateNumber();
      if(crateNumber >= 0){
         //Set CrateId
         SetCrateId(crateNumber);
      } else {
         //WDCrate not in a WDSystem
         //could work if only a WDCrate is used
         printf("Board %s in a crate not belonging to any system, cannot set CrateId\n", GetBoardName().c_str());
      }
   } else {
      //WDBoard not in a WDCrate
      //ok for standalone cards
      printf("Board %s not in a crate, cannot set SlotId and CrateId\n", GetBoardName().c_str());
   }

   printf("Connected to WD%03d\n", GetSerialNumber());

   if(IsDcbInterface()){
      SetEthComEn(0);
      SetSerdesComEn(1);
   }
}

void WDWDB::SetSerdesTraining(bool state){
   unsigned int regbits = GetAdvTrgCtrl();
   SetAdvTrgCtrl((regbits&0xFFFF7FF) | 0x00000430);//MASKSYNC=0, DEBUG_CTRL=1, ALGSEL=3
   SetInCrate();
}

bool WDWDB::IsSerdesTraining(){
   return (((GetAdvTrgCtrl() >>4) ^ 0x43)|0x3C)==0xFF;//require MASKSYNC=0, DEBUG_CTRL=1, ALGSEL=3

}

void WDWDB::WaitClockLock(){
   //Check clock and backplane clock source
   bool done=false;
   int count=30;

   do{
      ReceiveStatusRegister(GetDaqPllLockLoc());
      done = (GetDaqPllLock() == 1);
      done &= (GetLmkPllLock() == 1);
      if(GetDrsChTxEn()){
         done &= (GetDrsPllLock0() == 1);
         done &= (GetDrsPllLock1() == 1);
      }
      done &= (GetOserdesPllLockDcb() == 1);
      done &= (GetOserdesPllLockTcb() == 1);
      done &= (GetSysDcmLock() == 1);

      done &= (GetExtClkActive(true) == 1);

      if(!done) {
         usleep(100000);
         count--;
         if(count == 0){
            printf("check %s!\n", GetBoardName().c_str());
            throw std::runtime_error("WDB clock is not locked");
         }
      }
   } while(!done);
}

void WDWDB::WaitReady(){
   //check only clock lock
   bool done=false;
   int count=30;

   do{
      ReceiveStatusRegister(GetDaqPllLockLoc());
      done = (GetDaqPllLock() == 1);
      done &= (GetLmkPllLock() == 1);
      if(GetDrsChTxEn()){
         done &= (GetDrsPllLock0() == 1);
         done &= (GetDrsPllLock1() == 1);
      }
      done &= (GetOserdesPllLockDcb() == 1);
      done &= (GetOserdesPllLockTcb() == 1);
      done &= (GetSysDcmLock() == 1);

      if(!done) {
         usleep(100000);
         count--;
         if(count == 0){
            printf("check %s!\n", GetBoardName().c_str());
            throw std::runtime_error("WDB is not ready");
         }
      }
   } while(!done);

   ReceiveStatusRegisters();

   LoadCalibrationFiles();
}

//Properties
void WDWDB::ConfigureProperty(const std::string &name, Property &property) { 
   if(name=="IPD"){
      ConfigureIPD(property);
   } else if(name=="FPD"){
      ConfigureFPD(property);
   } else if(name=="MTU"){
      ConfigureMTU(property);
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
   } else if(name=="TriggerDelay"){
      ConfigureTriggerDelay(property);
   } else if(name=="TriggerTdcOffset"){
      ConfigureTriggerTdcOffset(property);
   } else if(name=="TriggerPedestalThreshold"){
      ConfigureTriggerPedestalThreshold(property);
   } else if(name=="TriggerPedestalDelay"){
      ConfigureTriggerPedestalDelay(property);
   } else if(name=="TriggerPedestalAddersel"){
      ConfigureTriggerPedestalAddersel(property);
   } else if(name=="TxDebugSignal"){
      ConfigureDebugSignal(0, property);
   } else if(name=="RxDebugSignal"){
      ConfigureDebugSignal(1, property);
   } else if(name=="SamplingFrequency"){
      ConfigureSamplingFrequency(property);
   } else if(name=="ForceEthernet"){
      ConfigureForceEthernet(property);
   } else {
      printf("Unknown property %s in WDWDB\n", name.c_str());
   }
};

void WDWDB::ConfigurationStarted(){
   SetSendBlock(true);
   // in case no DCB is used
   if(!IsDcbInterface()){
      int destPort = GetCrate()->GetSystem()->GetDAQServerPort();
      if(destPort) SetDestinationPort(destPort);
   }

   SetFeMux(-1, WDB::cFeMuxInput);
   SetTriggerOutPulseLength(4); // 4 clock shaping
   //SetAdvTrgPedCfg(0x0124000A); // default pedestal subtraction config
   SetAdvTrgPedCfg(0x0124000A); // default pedestal subtraction config
   //SetAdvTrgPedCfg(0x010A000A); // default pedestal subtraction config
   //SetAdvTrgPedCfg(0x010A0018); // default pedestal subtraction config
}

void WDWDB::ConfigurationEnded(){
   SetSendBlock(false);
   SendControlRegisters(false);
   SetDaqNormal(true);

   //reset from WDB::SetDrsSamplFreq, Already done in WDB???
   SetAdcIfRst(1);
   LmkSyncLocal();
   SetAdcIfRst(0);
   ResetAdc();
}

void WDWDB::ConfigureIPD(Property &property) {
   unsigned int interpacket_delay;
   interpacket_delay = property.GetUHex(); 
   if(interpacket_delay != 0){
      SetInterPkgDelay(interpacket_delay);
   }
}

void WDWDB::ConfigureFPD(Property &property) {
   unsigned int firstpacket_delay;
   firstpacket_delay = property.GetUHex(); 
   if(firstpacket_delay != 0){
      SetFirstPkgDly(firstpacket_delay);
   }
}

void WDWDB::ConfigureMTU(Property &property) {
   unsigned int com_pld_size;
   com_pld_size = property.GetUHex(); 
   if(com_pld_size != 0){
      com_pld_size = (com_pld_size / 6) * 6;
      SetComPldSize(com_pld_size);
   }
}

void WDWDB::ConfigureFrontendGain(Property &property) {
   int64_t arraySize = 0;
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
   int64_t arraySize = 0;
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
   int64_t arraySize = 0;
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
   int64_t arraySize = 0;
   const float* demand;
   demand = property.GetFloatVector(&arraySize);
   
   // Make Sure HV is written if SendBlock
   bool prevBlock = GetSendBlock();
   if(prevBlock){
      SetSendBlock(false);
   }
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

      SetSendBlock(prevBlock);
}

void WDWDB::ConfigureBaselineShift(Property &property) {
   float baseline;
   baseline = property.GetFloat();
   if(baseline>1 || baseline<-1)
      throw std::runtime_error("Invalid BaselineShift, supported values: beetween -1 and 1");
   else
      SetRange(baseline, false);
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
}

void WDWDB::ConfigureTriggerGain(Property &property) {
   int64_t arraySize = 0;
   const int* trigger_gain;
   trigger_gain = property.GetIntVector(&arraySize);

   int trg_gain[16];
   if(arraySize ==1){
      for(int i=0; i<16; i++) trg_gain[i] = trigger_gain[0];
      arraySize = 16;
   } else if(arraySize ==16) {
      for(int i=0; i<16; i++) trg_gain[i] =  trigger_gain[i];
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

void WDWDB::ConfigureTriggerDelay(Property &property) {
   unsigned int delay;
   delay = property.GetUInt();
   // if delay = 0 then use the async trigger
   if(delay == 0) { // this the same as SetInCrate
     SetPatternTriggerEn(0);
     SetExtAsyncTriggerEn(1);
   }
   // else: set trigger delay
   // select PatternTriggerEn
   // use ext trigger in the pattern logic
   else {
     SetPatternTriggerEn(1);
     SetExtAsyncTriggerEn(0);
     SetTriggerDelay(delay);
     //enable pattern 1
     SetTrgPtrnEn(1);
     // enable ext trigger
     SetTrgSrcEnPtrn(0,0x10000);
     // ask it as an hit
     SetTrgStatePtrn(0,0x10000);
   }
}

void WDWDB::ConfigureTriggerTdcOffset(Property &property) {
   int64_t arraySize = 0;
   const int* tdc_offset;
   tdc_offset = property.GetIntVector(&arraySize);

   int trg_offset[16];
   if(arraySize ==1){
      for(int i=0; i<16; i++) trg_offset[i] = tdc_offset[0];
      arraySize = 16;
   } else if(arraySize ==16) {
      for(int i=0; i<16; i++) trg_offset[i] =  tdc_offset[i];
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

void WDWDB::ConfigureTriggerPedestalThreshold(Property &property){
   unsigned int thr;
   thr = property.GetUHex();
   unsigned int pedconf = GetAdvTrgPedCfg();

   pedconf &= 0xFFFF0000;
   pedconf |= thr & 0xFFFF;

   SetAdvTrgPedCfg(pedconf);
}

void WDWDB::ConfigureTriggerPedestalDelay(Property &property){
   unsigned int dly;
   dly = property.GetUHex();
   unsigned int pedconf = GetAdvTrgPedCfg();

   pedconf &= 0xFFC0FFFF;
   pedconf |= (dly & 0x3F) << 16;

   SetAdvTrgPedCfg(pedconf);
}

void WDWDB::ConfigureTriggerPedestalAddersel(Property &property){
   unsigned int addersel;
   addersel = property.GetUHex();
   unsigned int pedconf = GetAdvTrgPedCfg();

   pedconf &= 0xF8FFFFFF;
   pedconf |= (addersel & 0x7) << 24;

   SetAdvTrgPedCfg(pedconf);
}

void WDWDB::ConfigureForceEthernet(Property &property){
   bool forceEth = property.GetBool();
   if(forceEth){
      SetEthComEn(1);
      SetSerdesComEn(0);
   } else {
      SetEthComEn(0);
      SetSerdesComEn(1);
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

   if(GetSendBlock()){
      //called within WDSystem::Configure()
      SetDrsSampleFreq(freq, false);
   } else  {
      //called when SamplingFrequency Property is changed
      SetDrsSampleFreq(freq);
      LoadCalibrationFiles();
   }


}

// Set configurations to be used in a crate
void WDWDB::SetInCrate(){

   //switch to backplane trigger
   SetPatternTriggerEn(0);
   SetExtAsyncTriggerEn(1);
   SetExtTriggerOutEnable(0);

   //switch to backplane clock
   if(GetExtClkInSel() != 0 || GetDaqClkSrcSel() != 0 || GetLmkInputFreq() != 80){

      printf("switching clock for %s\n", GetBoardName().c_str());

      SetSendBlock(true);
      SetExtClkInSel(0);

      SetDaqClkSrcSel(0);

      SetLmkInputFreq(80);
      SetSendBlock(false);

      SendControlRegisters(false);

      // left temporary to check if needed
      //Reset everything
//      ResetTcbOserdesIf();
//      ResetDrsControlFsm();
   }
   
   //Reset anyway
   //ResetAllPll();
}

//Helper function to calibration files
void WDWDB::LoadCalibrationFiles(){
   std::string calibpath = "."; 
   WDCrate* c = GetCrate();
   if(c!=nullptr){
      WDSystem * sys= c->GetSystem();
      if(sys!=nullptr){
         try{
       calibpath = sys->GetDaqProperty("CalibPath").GetStringValue();
    } catch (const std::out_of_range& ex){
         }
      }
   }

   if (!LoadVoltageCalibration(GetDrsSampleFreqMhz(), calibpath.c_str())) {
      printf("WDB %s: missing voltage calibration file\n", GetBoardName().c_str());
   }
   if (!LoadTimeCalibration(GetDrsSampleFreqMhz(), calibpath.c_str())) {
      printf("WDB %s: missing time calibration file\n", GetBoardName().c_str());
   }
}

// --- WDTCB ---
// Constructor
WDTCB::WDTCB(WDCrate *crate, int slot, std::string name, int verbose) : TCB(verbose), WDBoard(crate, slot, name){

   //Get Mscb handle from crate
   int hdle = crate->GetMscbHandle();
   SetMscbHandle(hdle, slot);

   if(crate->HasBoardIn(16)){
      //Get board in slot 16 (DCB slot)
      WDBoard *b = crate->GetBoardAt(16);

      if(dynamic_cast<WDDCB*>(b)!=nullptr){
         //crate has a DCB in slot 16, switch to it
         SetDcbInterface(static_cast<WDDCB*>(b), slot);
      }
   } else {
      // no DCB (yet?)
   }
}

// WDBoard derived methods
void WDTCB::Connect(){
   SetIDCode();

   if(fidcode == 0){
      printf("try again in TCB connection...\n");
      sleep(2);
      SetIDCode();

   }

   SetNTRG();
   fverbose= true;

   //Set SlotId and CrateId
   WDCrate *crate = GetCrate();
   if(crate != nullptr){
      int64_t crateNumber = crate->GetCrateNumber();

      SetBoardId(GetSerialNumber(), crateNumber, GetSlot());
   } else {
      //WDBoard not in a WDCrate
      //ok for standalone cards
      printf("Board %s not in a crate, cannot set SlotId and CrateId\n", GetBoardName().c_str());
   }

   printf("Connected to TCB with IDCode = %04x\n", fidcode);

   //make sure board is stopped
   StopRun();

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

void WDTCB::WaitSerdesTrainingFinish(){
   unsigned int val=0xFFFF;
   int count=100;
   do{
      GetAutoCalibrateBusy(&val);

      if(val != 0) {
         usleep(10000);
         count--;
         if(count == 0){
            printf("check %s!\n", GetBoardName().c_str());
            throw std::runtime_error("Cannot lock TCB serdes");
         }
      }
   } while(val != 0);
}

//check serdes is good (like expected ones)
bool WDTCB::IsSerdesGood(){
   unsigned int val=0;

   //temporarely skip 
   if((GetIDCode() >> 12) == 2){
      return true;
   }

   GetAutoCalibrateFail(&val);

   //check all slots
   for(int i=0; i<16; i++){
      if(GetCrate()->HasBoardIn(i)){
         if((val >> i) & 0x1){
            printf("Failed slot %d in board %s\n", i, GetBoardName().c_str());
            return false;
         }
      }
   }

   //check serdes align fsm
   if ((val>>31) & 0x1){
      printf("Failed serdes alignment in board %s, value=0x%08x\n", GetBoardName().c_str(), val);
      return false;
   }

   return true;
}

void WDTCB::WaitClockLock(){
   //unsigned int val=0xFFFF;
   //do{
      //GetAutoCalibrateBusy(&val);

      //if(val != 0)
         //usleep(1000);
   //} while(val != 0);

   //Should check PLL state when on register
}

void WDTCB::WaitReady(){
   WaitClockLock();
   //Should check something else??
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
   } else if(name=="Banks"){
      ConfigurePacketizer(property);
   } else if(name=="ExtDAQBusyMask"){
      ConfigureExtDAQ(property);
   } else if(name=="DetectorDelay"){
      ConfigureDetectorDelay(property);
   } else if(name=="TimeNarrowThreshold"){
      ConfigureTimeNarrowThreshold(property);
   } else if(name=="TimeWideThreshold"){
      ConfigureTimeWideThreshold(property);
   } else if(name=="XecHighThreshold"){
      ConfigureXecHighThreshold(property);
   } else if(name=="XecLowThreshold"){
      ConfigureXecLowThreshold(property);
   } else if(name=="XecVetoThreshold"){
      ConfigureXecVetoThreshold(property);
   } else if(name=="XecPatchId"){
      ConfigureXecPatchId(property);
   } else if(name=="XecPatchThreshold"){
      ConfigureXecPatchThreshold(property);
   } else if(name=="XecPatchDelay"){
      ConfigureXecPatchDelay(property);
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
   } else if(name=="CdchMask"){
      ConfigureCdchMask(property);
   } else if(name=="CdchUSMultiplicityThreshold"){
      ConfigureCdchUSMultiplicityThreshold(property);
   } else if(name=="CdchDSMultiplicityThreshold"){
     ConfigureCdchDSMultiplicityThreshold(property);
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
   } else if(name=="RdcVetoThreshold"){
      ConfigureRdcVetoThreshold(property);
   } else if(name=="RdcHitDelay"){
      ConfigureRdcHitDelay(property);
   } else if(name=="RdcHitMask"){
      ConfigureRdcHitMask(property);
   } else if(name=="RdcTriggerMask"){
      ConfigureRdcTriggerMask(property);
   } else if(name=="CrcHitMask"){
      ConfigureCrcHitMask(property);
   } else if(name=="CrcPairMask"){
      ConfigureCrcPairMask(property);
   } else if(name=="NgenHighThreshold"){
      ConfigureNgenHighThreshold(property);
   } else if(name=="NgenLowThreshold"){
      ConfigureNgenLowThreshold(property);
   } else if(name=="NgenDelay"){
      ConfigureNgenDelay(property);
   } else if(name=="NgenWidth"){
      ConfigureNgenWidth(property);
   } else if(name=="FHitShaper"){ 
      ConfigureFHitShaper(property);
   } else if(name=="FVetoShaper"){ 
      ConfigureFVetoShaper(property);
   } else if(name=="MargaritaMajVal"){ 
      ConfigureMargaritaMajVal(property);
   } else if(name=="MargaritaTrgDly"){ 
      ConfigureMargaritaTrgDly(property);
   } else if(name=="MargaritaMask"){ 
      ConfigureMargaritaMask(property);
   } else if(name=="TofBarHitLogic"){ 
      ConfigureTofBarHitLogic(property);
   } else if(name=="TofHitLogic"){ 
      ConfigureTofHitLogic(property);
   } else if(name=="TofHitLogicAlternative"){ 
      ConfigureTofHitLogicAlternative(property);
   } else if(name=="TofXMask"){ 
      ConfigureTofXMask(property); 
   } else if(name=="TofYMask"){ 
      ConfigureTofYMask(property);
   } else if(name=="FCaloMask"){ 
      ConfigureFCaloMask(property);
   } else if(name=="FNeutronMask"){ 
      ConfigureFNeutronMask(property);
   } else if(name=="MatrixMask"){ 
      ConfigureMatrixMask(property);
   } else if(name=="InterspillDly"){ 
      ConfigureInterspillDly(property);
   } else if(name=="LoLXMask"){ 
      ConfigureLoLXMask(property);
   } else if(name=="LoLXMajValScin"){ 
      ConfigureLoLXMajScinVal(property);
   } else if(name=="LoLXMajValCher"){ 
      ConfigureLoLXMajCherVal(property);
   } else if(name=="LoLXMajValBare"){ 
      ConfigureLoLXMajBareVal(property);
   } else if(name=="NoLocalTrigger"){  
   } else {
      printf("Unknown property %s in WDTCB\n", name.c_str());
   }
};

void WDTCB::ConfigurationStarted(){
   u_int32_t rrun_config = 0x0000E014;  //masktrg, masksync, maskbusy, fadcmode, enable trg_bus

   //get crate and system
   WDSystem *sys = GetCrate()->GetSystem();
   if(GetCrate()->GetCrateNumber()==sys->GetTriggerCrateId() && GetSlot()==17){
      //TCB is system Master
      if(sys->GetTriggerCrateId() == sys->GetDistributionCrateId()){
         //Distribution within same crate -> can use Local trigger
         bool cableOnly;
         try{
            //check for cable being requested
            cableOnly = GetProperty("NoLocalTrigger").GetBool();
         }catch (const std::runtime_error& ex){
            // enabled if nothig specified
            cableOnly = false;
         }
         if(!cableOnly){
            printf("Enabling local trigger: make sure FCI cable is not connected\n");
            rrun_config |= 0x00000800; //LOCAL_TRG enable
         } else {
            printf("Local trigger manually disabled: using FCI cable instead\n");
         }
      }
   }

   SetRRUN(&rrun_config);
   u_int32_t syncdly=0x1F;
   u_int32_t trgdly=0x1F;
   u_int32_t sprdly=0x1F;
   SetTRGBusIDLY(&syncdly, &trgdly, &sprdly);
   syncdly=0x10;
   trgdly=0x10;
   sprdly=0x10;
   if((fidcode >>12) == 3) {
     SetTRGBusODLY(&syncdly, &trgdly, &sprdly);
   }
   SetPacketizerCommandAt(0, ::STOP, 0, 0);
   SetPacketizerAutostart(true);
   SetPacketizerEnable(true);
   SetPacketizerBus(true);
   SetReadoutEnable(true);
   unsigned int val = 0;
   SetMaxPayload(&val);
}

void WDTCB::ConfigurationEnded(){
   if((fidcode >>12) != 3)
      GoRun();
}

void WDTCB::ConfigureTriggerEnable(Property &property){
   int64_t arraySize = 0;
   const unsigned int* trigger_enable;
   trigger_enable = GetProperty("TriggerEnable").GetUIntVector(&arraySize);

   bool trg_ena[64];
   for(int i=0; i<64; i++) trg_ena[i] = false;
   for(long i=0; i<arraySize; i++) 
      if(trigger_enable[i] < 64)
         trg_ena[trigger_enable[i]] = true;

   SetTriggerEnable(trg_ena);
}

void WDTCB::ConfigureTriggerPrescaling(Property &property){
   int64_t arraySize = 0;
   const unsigned int* trigger_prescaling;
   trigger_prescaling = property.GetUIntVector(&arraySize);

   int64_t arraySizeEnable = 0;
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
      for(long i=0; i<arraySize; i++)
         if(trigger_enable[i] < 64)
            trg_presca[trigger_enable[i]] = trigger_prescaling[i];

      SetPrescaling(trg_presca);
   }
}

void WDTCB::ConfigureTriggerDelay(Property &property){
   int64_t arraySize = 0;
   const unsigned int* trigger_delay;
   trigger_delay = property.GetUIntVector(&arraySize);

   int64_t arraySizeEnable = 0;
   const unsigned int* trigger_enable;
   try{
      trigger_enable = GetProperty("TriggerEnable").GetUIntVector(&arraySizeEnable);
   } catch (const std::runtime_error& ex){
      throw std::runtime_error("Cannot set TriggerDelay: TriggerEnable should be also defined");
   }
   unsigned int trg_delay[64];
   bool trg_delay_enable[64];
   for(int i=0; i<64; i++) {
      trg_delay[i] = 0;
      trg_delay_enable[i] = false;
   }
   if(arraySizeEnable != arraySize)
      throw std::runtime_error("Cannot set TriggerDelay: TriggerEnable has a different array length");
   else {
      for(long i=0; i<arraySize; i++)
         if(trigger_enable[i] < 64){
            if(trigger_delay[i] > 0){
               trg_delay_enable[trigger_enable[i]] = true;
               trg_delay[trigger_enable[i]] = trigger_delay[i]-1;
            }
         }

      SetTRGDLY(trg_delay_enable, trg_delay);
   }
}

void WDTCB::ConfigureTriggerAlgorithm(Property &property){
   unsigned int algorithm;
   algorithm = property.GetUInt();

   SetRALGSEL((unsigned int *)&algorithm);
}

void WDTCB::ConfigureParameters(Property &property){
   int64_t arraySize = 0;
   const unsigned int* parameters;

   parameters = property.GetUHexVector(&arraySize);
   for(int i=0; i<arraySize-1; i+=2){
      unsigned int val = parameters[i+1];
      SetParameter(parameters[i], &val);
   }
}

void WDTCB::ConfigurePacketizer(Property &property){
   std::string list = property.GetStringValue();

   std::vector<PacketInstruction> instVec;
   PacketInstruction inst;

   //to be changed: waiting for deserialization
   inst.offset = 0;
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

   //fill header
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

   int bufptr = BUFFERBASE+5;
   int nbank = 0;

   if(list.find("TRGI")!=std::string::npos){
     // bank name
     inst.offset += 1;
     inst.cmd = ::DIRECT_WRITE;
     inst.arg0 = 0x54524749;//TRGI
     inst.arg1 = bufptr++;
     instVec.push_back(inst);
     // bank size
     inst.offset += 1;
     inst.cmd = ::DIRECT_WRITE;
     inst.arg0 = 7;
     inst.arg1 = bufptr++;
     instVec.push_back(inst);
     // trigger type
     inst.offset += 1;
     inst.cmd = ::COPY;
     inst.arg0 = RTRITYPE;
     inst.arg1 = bufptr++;
     instVec.push_back(inst);
     // trigger pattern (2 words)
     inst.offset += 1;
     inst.cmd = ::BLOCK_COPY;
     inst.arg0 = RTRIPATT;
     inst.arg1 = bufptr;
     inst.arg2 = 2;
     instVec.push_back(inst);
     // this is to RESET arg2 for next instructions!
     inst.arg2 = 0;
     bufptr += 2;
     // total time
     inst.offset += 1;
     inst.cmd = ::COPY;
     inst.arg0 = RTOTTIME;
     inst.arg1 = bufptr++;
     instVec.push_back(inst);
     // live time
     inst.offset += 1;
     inst.cmd = ::COPY;
     inst.arg0 = RLIVETIME;
     inst.arg1 = bufptr++;
     instVec.push_back(inst);
     // event counter
     inst.offset += 1;
     inst.cmd = ::COPY;
     inst.arg0 = REVECOU;
     inst.arg1 = bufptr++;
     instVec.push_back(inst);
     // LOGIC BELOW: IF FOOT JUMPS TO THE END --> BCO COUNTER
     // IN ALL OTHER CASES WRITE PCURR AND JUMPS AFTER BCO
     // DIFFERENT BEHAVIOUR FOR LOLX SCIFI TO BE IMPLEMENTED IN THE FUTURE
     // JUMP_IF FOOT
     inst.offset += 1;
     inst.cmd = ::JUMP_IF;
     inst.arg0 = RRUN;
     inst.arg1 = 0x2<<16; // bit on RRUN reg if compiled for FOOT
     inst.arg2 = inst.offset+3; // this is the address to jump into if condition is true, i.e. skip the copy
     instVec.push_back(inst);
     // this is to RESET arg2 for next instructions!
     inst.arg2 = 0;
     //if above true this is jumped
     inst.offset += 1;
     inst.cmd = ::COPY;
     inst.arg0 = RPCURR;
     inst.arg1 = bufptr;
     instVec.push_back(inst);
     // JUMP --> after BCO!
     inst.offset += 1;
     inst.cmd = ::JUMP;
     inst.arg0 = 0;
     inst.arg1 = 0; // bit on RRUN reg if compiled for FOOT
     inst.arg2 = inst.offset+2; // this is the address to jump into if condition is true, i.e. skip the copy
     instVec.push_back(inst);
     // this is to RESET arg2 for next instructions!
     inst.arg2 = 0;
     //if above true this is jumped
     inst.offset += 1;
     inst.cmd = ::COPY;  
     inst.arg0 = RFSTIME;
     inst.arg1 = bufptr;
     instVec.push_back(inst);
     bufptr++;
     
     nbank++;
   }
   if(list.find("TRGC")!=std::string::npos){
      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 0x54524743;//TRGC
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 64;
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::BLOCK_COPY;
      inst.arg0 = RTRGCOU;
      inst.arg1 = bufptr;
      inst.arg2 = 64;
      instVec.push_back(inst);
      inst.arg2 = 0;

      bufptr += 64;

      nbank++;
   }
   if(list.find("TGEN")!=std::string::npos){
      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 0x5447454e;//TGEN
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 2*GENTDIM+1;
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::COPY;
      inst.arg0 = RMEMADDR;
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::BLOCK_COPY;
      inst.arg0 = GENTMEMBASE;
      inst.arg1 = bufptr;
      inst.arg2 = 2*GENTDIM;
      instVec.push_back(inst);
      inst.arg2 = 0;

      bufptr += 2*GENTDIM;
      nbank++;
   }
   if(list.find("BGO")!=std::string::npos){
      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 0x5442474F;//TBGO
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = MEMDIM+1;
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::COPY;
      inst.arg0 = RMEMADDR;
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::BLOCK_COPY;
      inst.arg0 = BGOMEMBASE;
      inst.arg1 = bufptr;
      inst.arg2 = MEMDIM;
      instVec.push_back(inst);
      inst.arg2 = 0;

      bufptr += MEMDIM;
      nbank++;
   }
   if(list.find("RDC")!=std::string::npos){
      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 0x54524443;//TRDC
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 2*MEMDIM+1;
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::COPY;
      inst.arg0 = RMEMADDR;
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::BLOCK_COPY;
      inst.arg0 = RDCMEMBASE;
      inst.arg1 = bufptr;
      inst.arg2 = 2*MEMDIM;
      instVec.push_back(inst);
      inst.arg2 = 0;

      bufptr += 2*MEMDIM;
      nbank++;
   }
   if(list.find("ALFA")!=std::string::npos){
      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 0x54414c46;//TALF
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 2*MEMDIM+1;
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::COPY;
      inst.arg0 = RALGCLKMEMADDR;
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::BLOCK_COPY;
      inst.arg0 = ALFAMEMBASE;
      inst.arg1 = bufptr;
      inst.arg2 = 2*MEMDIM;
      instVec.push_back(inst);
      inst.arg2 = 0;

      bufptr += 2*MEMDIM;
      nbank++;
   }
   if(list.find("XEC")!=std::string::npos){
      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 0x54584543;//TXEC
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 2*MEMDIM+1;
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::COPY;
      inst.arg0 = RMEMADDR;
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::BLOCK_COPY;
      inst.arg0 = XECMEMBASE;
      inst.arg1 = bufptr;
      inst.arg2 = 2*MEMDIM;
      instVec.push_back(inst);
      inst.arg2 = 0;

      bufptr += 2*MEMDIM;
      nbank++;
   }
   if(list.find("SPX")!=std::string::npos){
      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 0x54535058;//TSPX
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 2*MEMDIM+1;
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::COPY;
      inst.arg0 = RMEMADDR;
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::BLOCK_COPY;
      inst.arg0 = TCMEMBASE;
      inst.arg1 = bufptr;
      inst.arg2 = 2*MEMDIM;
      instVec.push_back(inst);
      inst.arg2 = 0;

      bufptr += 2*MEMDIM;
      nbank++;
   }
 if(list.find("CDCH")!=std::string::npos){
      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 0x54444348;//TDCH                                                                                                                                                                    
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 2*MEMDIM+1;
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::COPY;
      inst.arg0 = RMEMADDR;
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::BLOCK_COPY;
      inst.arg0 = CDCHMEMBASE;
      inst.arg1 = bufptr;
      inst.arg2 = 2*MEMDIM;
      instVec.push_back(inst);
      inst.arg2 = 0;

      bufptr += 2*MEMDIM;
      nbank++;
   }
   if(list.find("SCIFI")!=std::string::npos){
      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 0x54534346;//TSCF
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 44;
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::BLOCK_COPY;
      inst.arg0 = RFIBCOUNTER;
      inst.arg1 = bufptr;
      inst.arg2 = 43;
      instVec.push_back(inst);
      inst.arg2 = 0;
      
      bufptr += 43;

      inst.offset += 1;
      inst.cmd = ::COPY;
      inst.arg0 = RTOTTIME;
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      nbank++;
   }
   if(list.find("SCIFI")!=std::string::npos){
      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 0x54534643;//TSFC
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::DIRECT_WRITE;
      inst.arg0 = 442;
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      inst.offset += 1;
      inst.cmd = ::BLOCK_COPY;
      inst.arg0 = SCIFICOINCBASE;
      inst.arg1 = bufptr;
      inst.arg2 = 441;
      instVec.push_back(inst);
      inst.arg2 = 0;
      
      bufptr += 441;

      inst.offset += 1;
      inst.cmd = ::COPY;
      inst.arg0 = RTOTTIME;
      inst.arg1 = bufptr++;
      instVec.push_back(inst);

      nbank++;
   }

   inst.offset += 1;
   inst.cmd = ::DIRECT_WRITE;
   inst.arg0 = 0;
   inst.arg1 = bufptr++;
   instVec.push_back(inst);

   inst.offset += 1;
   inst.cmd = ::DIRECT_WRITE;
   inst.arg0 = nbank;//nbanks
   inst.arg1 = BUFFERBASE;
   instVec.push_back(inst);

   inst.offset += 1;
   inst.cmd = ::DIRECT_WRITE;
   inst.arg0 = 1;
   inst.arg1 = PACK_NEXT_BUFFER;
   instVec.push_back(inst);

   inst.offset += 1;
   inst.cmd = ::STOP;
   instVec.push_back(inst);

   WritePacketizerProgram(instVec);
}

void WDTCB::ConfigureExtDAQ(Property &property){
   bool extdaqbmask;
   extdaqbmask = property.GetBool();

   SetFMask(false, extdaqbmask);
}

void WDTCB::ConfigureDetectorDelay(Property &property){
   int64_t arraySize = 0;
   const unsigned int* dlys;

   dlys = property.GetUIntVector(&arraySize);
   if(arraySize == 6){
      bool enable[6];
      u_int32_t val[6];
      for(int i=0; i<6; i++){
         if(dlys[i] == 0){
            enable[i] = false;
            val[i] = 0;
         } else {
            enable[i] = true;
            val[i] = dlys[i]-1;
         }
      }
      SetDetectorDelay(enable, val);
   } else
      throw std::runtime_error("DetectorDelay size should be 6 values");
   
}

void WDTCB::ConfigureTimeNarrowThreshold(Property &property){
   unsigned int timenarrow;
   timenarrow = property.GetUHex();

   SetTimeNarrow(&timenarrow);
}

void WDTCB::ConfigureTimeWideThreshold(Property &property){
   unsigned int timewide;
   timewide = property.GetUHex();

   SetTimeWide(&timewide);
}

void WDTCB::ConfigureXecHighThreshold(Property &property){
   unsigned int xechighthreshold;
   xechighthreshold = property.GetUHex();
   xechighthreshold /= 8;

   SetSumHighThreshold(&xechighthreshold);
}

void WDTCB::ConfigureXecLowThreshold(Property &property){
   unsigned int xeclowthreshold;
   xeclowthreshold = property.GetUHex();
   xeclowthreshold /= 8;

   SetSumLowThreshold(&xeclowthreshold);
}

void WDTCB::ConfigureXecVetoThreshold(Property &property){
   unsigned int xecvetothreshold;
   xecvetothreshold = property.GetUHex();
   xecvetothreshold /= 8;

   SetSumVetoThreshold(&xecvetothreshold);
}

void WDTCB::ConfigureXecPatchId(Property &property){
   unsigned int xecpatchid;
   xecpatchid = property.GetUHex();

   SetPatch(&xecpatchid);
}

void WDTCB::ConfigureXecPatchThreshold(Property &property){
   unsigned int xecpatchthreshold;
   xecpatchthreshold = property.GetUHex();

   SetPatchThreshold(&xecpatchthreshold);
}

void WDTCB::ConfigureXecPatchDelay(Property &property){
   unsigned int xecpatchdelay;
   xecpatchdelay = property.GetUInt();

   bool enable;
   if(xecpatchdelay > 0){
      enable = true;
      xecpatchdelay -= 1;
   } else {
      enable = false;
      xecpatchdelay = 0;
   }

   SetPatchDelay(enable, xecpatchdelay);
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
   int64_t arraySize = 0;
   const unsigned int* masks;

   masks = property.GetUHexVector(&arraySize);
   if(arraySize == 4){
      SetTCMasks((unsigned int*)masks);
   } else
      throw std::runtime_error("TcMask size should be 4 values");
}

void WDTCB::ConfigureLoLXMask(Property &property){
   unsigned int lolxmask;
   lolxmask = property.GetUHex();

   SetLoLXMasks(&lolxmask);
}

void WDTCB::ConfigureLoLXMajScinVal(Property &property){
   unsigned int majval;
   majval = property.GetUHex();

   SetLoLXMajScinVal(&majval);
}

void WDTCB::ConfigureLoLXMajCherVal(Property &property){
   unsigned int majval;
   majval = property.GetUHex();

   SetLoLXMajCherVal(&majval);
}

void WDTCB::ConfigureLoLXMajBareVal(Property &property){
   unsigned int majval;
   majval = property.GetUHex();

   SetLoLXMajBareVal(&majval);
}

void WDTCB::ConfigureTcMultiplicityThreshold(Property &property){
   unsigned int multtheshold;
   multtheshold = property.GetInt();

   SetTCMultiplicityThreshold(&multtheshold);
}

void WDTCB::ConfigureTcCrateMergeThreshold(Property &property){
   int64_t arraySize = 0;
   const unsigned int* thresholds;

   thresholds = property.GetUHexVector(&arraySize);
   if(arraySize == 2){
      SetTCCrateMergeThreshold((unsigned int*)thresholds, (unsigned int*)thresholds+1);
   } else
      throw std::runtime_error("TcCrateMergeThreshold size should be 2 values");
}

void WDTCB::ConfigureTcSectorMergeThreshold(Property &property){
   int64_t arraySize = 0;
   const unsigned int* thresholds;

   thresholds = property.GetUHexVector(&arraySize);
   if(arraySize == 2){
      SetTCSectorMergeThreshold((unsigned int*)thresholds, (unsigned int*)thresholds+1);
   } else
      throw std::runtime_error("TcSectorMergeThreshold size should be 2 values");
}

void WDTCB::ConfigureCdchMask(Property &property){
   int64_t arraySize = 0;
   const unsigned int* masks;

   masks = property.GetUHexVector(&arraySize);
   if(arraySize == 8){
     SetCDCHMasks((unsigned int*) masks);
   } else
      throw std::runtime_error("CdchMask size should be 8 values");
}

void WDTCB::ConfigureCdchUSMultiplicityThreshold(Property &property){
   unsigned int threshold;
   threshold = property.GetInt();

   SetCDCHUSMultThr(&threshold);
}

void WDTCB::ConfigureCdchDSMultiplicityThreshold(Property &property){
   unsigned int threshold;
   threshold = property.GetInt();

   SetCDCHDSMultThr(&threshold);
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
   int64_t arraySize = 0;
   
   const unsigned int *bgohitdelay = property.GetUIntVector(&arraySize);

   if(arraySize == 2)
      SetBGOHitDelay(bgohitdelay[0], bgohitdelay[1]);
   else
      throw std::runtime_error("BgoHitDelay size should be 2 values");
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

void WDTCB::ConfigureRdcVetoThreshold(Property &property){
   unsigned int rdcvetothreshold;
   rdcvetothreshold = property.GetUHex();

   SetRDCVetoThreshold(&rdcvetothreshold);
}

void WDTCB::ConfigureRdcHitDelay(Property &property){
   unsigned int rdchitdelay;
   rdchitdelay = property.GetUInt();

   SetRDCHitDelay(&rdchitdelay);
}

void WDTCB::ConfigureRdcHitMask(Property &property){
   int64_t arraySize = 0;
   
   const unsigned int *rdchitmask = property.GetUHexVector(&arraySize);

   if(arraySize == 3)
      SetRDCHitMask((unsigned int*)rdchitmask);
   else
      throw std::runtime_error("RdcHitMask size should be 3 values");
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

void WDTCB::ConfigureNgenDelay(Property &property){
   unsigned int ngendly;
   ngendly = property.GetUHex();

   SetNGENDly(&ngendly);
}

void WDTCB::ConfigureNgenWidth(Property &property){
   unsigned int ngenwidth;
   ngenwidth = property.GetUHex();

   SetNGENWidth(&ngenwidth);
}

void WDTCB::ConfigureNgenHighThreshold(Property &property){
   unsigned int ngenhigh;
   ngenhigh = property.GetUHex();
   ngenhigh /= 8;

   SetNGENHighThreshold(&ngenhigh);
}

void WDTCB::ConfigureNgenLowThreshold(Property &property){
   unsigned int ngenlow;
   ngenlow = property.GetUHex();
   ngenlow /= 8;

   SetNGENLowThreshold(&ngenlow);
}

void WDTCB::ConfigureFHitShaper(Property &property){
   unsigned int hitshaper;
   hitshaper = property.GetUInt();

   SetFHitShaper(&hitshaper);
}

void WDTCB::ConfigureFVetoShaper(Property &property){
   unsigned int vetoshaper;
   vetoshaper = property.GetUInt();

   SetFVetoShaper(&vetoshaper);
}

void WDTCB::ConfigureMargaritaMajVal(Property &property){
   unsigned int majval;
   majval = property.GetUInt();

   SetMargaritaMajVal(&majval);
}

void WDTCB::ConfigureMargaritaTrgDly(Property &property){
   unsigned int majtrgdly;
   majtrgdly = property.GetUInt();

   SetMargaritaTrgDly(&majtrgdly);
}

void WDTCB::ConfigureMargaritaMask(Property &property){
   unsigned int mask;
   mask = property.GetUHex();

   SetMargaritaMask(&mask);
}

void WDTCB::ConfigureTofBarHitLogic(Property &property){
   unsigned int logic;
   logic = property.GetUHex();

   SetTofBarHitLogic(&logic);
}

void WDTCB::ConfigureTofHitLogic(Property &property){
   unsigned int logic;
   logic = property.GetUHex();

   SetTofHitLogic(&logic);
}

void WDTCB::ConfigureTofHitLogicAlternative(Property &property){
   unsigned int logic;
   logic = property.GetUHex();

   SetTofHitLogicAlternative(&logic);
}

void WDTCB::ConfigureTofXMask(Property &property){
   int64_t arraySize = 0;
   const unsigned int* masks;

   masks = property.GetUHexVector(&arraySize);
   if(arraySize == 2){
      SetTofXMask((unsigned int*)masks);
   } else
      throw std::runtime_error("TofXMask size should be 2 values");
}

void WDTCB::ConfigureTofYMask(Property &property){
   int64_t arraySize = 0;
   const unsigned int* masks;

   masks = property.GetUHexVector(&arraySize);
   if(arraySize == 2){
      SetTofYMask((unsigned int*)masks);
   } else
      throw std::runtime_error("TofYMask size should be 2 values");
}

void WDTCB::ConfigureFCaloMask(Property &property){
   unsigned int mask;
   mask = property.GetUHex();
   SetFCaloMask(&mask);
}

void WDTCB::ConfigureFNeutronMask(Property &property){
   unsigned int mask;
   mask = property.GetUHex();
   SetFNeutronMask(&mask);
}

void WDTCB::ConfigureMatrixMask(Property &property){
   int64_t arraySize = 0;
   const unsigned int* masks;

   masks = property.GetUHexVector(&arraySize);
   if(arraySize == 3){
      SetMatrixMask((unsigned int*)masks);
   } else
      throw std::runtime_error("TofYMask size should be 2 values");
}

void WDTCB::ConfigureInterspillDly(Property &property){
   unsigned int dly;
   dly = property.GetUInt();

   SetInterspillDly(&dly);
}

// --- WDDCB ---
// constructor
WDDCB::WDDCB(WDCrate *crate, int slot, std::string name, std::string netname, bool verbose) : DCB(netname, verbose), WDBoard(crate, slot, name) {
   //if DCB is in slot 16
   if(slot==16){

      //loop on all boards in the crate
      for(int i=0; i<18; i++){
         if(crate->HasBoardIn(i)){
            WDBoard* b = crate->GetBoardAt(i);

            //switch WDB and TCB to use DCB for readout
            if(dynamic_cast<WDWDB*>(b) != nullptr){
               static_cast<WDWDB*>(b)->SetDcbInterface(this, i);

            } else if(dynamic_cast<WDTCB*>(b) != nullptr){
               static_cast<WDTCB*>(b)->SetDcbInterface(this, i);

            } else {
               //unsupported board (DCB or other)
            }
         }
      }

   }
}

// WDBoard derived methods
void WDDCB::Connect(){
   DCB::Connect();

   //then enable clock distributor and dps for all slots
   SetDistributorClkOutEn(0xFFFFC);
   SetDpsSlotEnable(0x1FFFF);

   //Scan Crate to get actual board map 
   ScanCrate();

   //retrieve crate pointer
   WDCrate *crate = GetCrate();

   //Set SlotId
   SetSendBlock(true);
   SetSlotId(GetSlot());
   SetSendBlock(false);

   int64_t crateNumber = crate->GetCrateNumber();
   if(crateNumber >= 0){
      //Set CrateId
      SetCrateId(crateNumber);
   } else {
      //WDCrate not in a WDSystem
      //could work if only a WDCrate is used
      printf("Board %s in a crate not belonging to any system, cannot set CrateId\n", GetBoardName().c_str());
   }

   //build crate slot mask
   unsigned int clkmask = 0x00004; //DCB FPGA
   unsigned int packetmask = 0x00000;
   for(int i=0; i<16; i++)
      if(crate->HasBoardIn(i)){
         clkmask |= (0x10<<i);
         packetmask |= (0x1<<i);
      }
   if(crate->HasBoardIn(17)){
      clkmask |= 0x8;
      packetmask |= (0x10000);
   }

   //printf("setting clock mask to %x\n", clkmask);
   SetDistributorClkOutEn(clkmask);
   //printf("setting packet mask to %x\n", packetmask);
   SetDpsSlotEnable(packetmask);


   //reset any stuff
   ResetDps();

   printf("Connected to DCB%02d\n", GetSerialNumber());
}

void WDDCB::SetSerdesTraining(bool state){
}

bool WDDCB::IsSerdesTraining(){
   return false;
}

void WDDCB::TrainSerdes(){
   ResetSerdes(0, false);
}

void WDDCB::WaitSerdesTrainingFinish(){
   bool done=false;
   int count=10;

   do{
      ReceiveRegisters(DCB_REG_SERDES_STATUS_00_07, 3);
      done = (GetDelaySyncDone00() == 1);
      done &= (GetDelaySyncDone01() == 1);
      done &= (GetDelaySyncDone02() == 1);
      done &= (GetDelaySyncDone03() == 1);
      done &= (GetDelaySyncDone04() == 1);
      done &= (GetDelaySyncDone05() == 1);
      done &= (GetDelaySyncDone06() == 1);
      done &= (GetDelaySyncDone07() == 1);
      done &= (GetDelaySyncDone08() == 1);
      done &= (GetDelaySyncDone09() == 1);
      done &= (GetDelaySyncDone10() == 1);
      done &= (GetDelaySyncDone11() == 1);
      done &= (GetDelaySyncDone12() == 1);
      done &= (GetDelaySyncDone13() == 1);
      done &= (GetDelaySyncDone14() == 1);
      done &= (GetDelaySyncDone15() == 1);
      done &= (GetDelaySyncDone17() == 1);

      if(!done) {
         usleep(10000);
         count--;
         if(count == 0){
            printf("check %s!\n", GetBoardName().c_str());
            throw std::runtime_error("Cannot lock DCB serdes");
         }
      }
   } while(!done);

   ResetSerdes(1, false);
   //SendUDP("dpsreset"); 
}

//check serdes is good (like expected ones)
bool WDDCB::IsSerdesGood(){
   ReceiveRegisters(DCB_REG_SERDES_STATUS_00_07, 3);

   bool ok = (GetCrate()->HasBoardIn(0))? GetSyncDone00() : true;
   ok &= (GetCrate()->HasBoardIn(1))? GetSyncDone01() : true;
   ok &= (GetCrate()->HasBoardIn(2))? GetSyncDone02() : true;
   ok &= (GetCrate()->HasBoardIn(3))? GetSyncDone03() : true;
   ok &= (GetCrate()->HasBoardIn(4))? GetSyncDone04() : true;
   ok &= (GetCrate()->HasBoardIn(5))? GetSyncDone05() : true;
   ok &= (GetCrate()->HasBoardIn(6))? GetSyncDone06() : true;
   ok &= (GetCrate()->HasBoardIn(7))? GetSyncDone07() : true;
   ok &= (GetCrate()->HasBoardIn(8))? GetSyncDone08() : true;
   ok &= (GetCrate()->HasBoardIn(9))? GetSyncDone09() : true;
   ok &= (GetCrate()->HasBoardIn(10))? GetSyncDone10() : true;
   ok &= (GetCrate()->HasBoardIn(11))? GetSyncDone11() : true;
   ok &= (GetCrate()->HasBoardIn(12))? GetSyncDone12() : true;
   ok &= (GetCrate()->HasBoardIn(13))? GetSyncDone13() : true;
   ok &= (GetCrate()->HasBoardIn(14))? GetSyncDone14() : true;
   ok &= (GetCrate()->HasBoardIn(15))? GetSyncDone15() : true;
   ok &= (GetCrate()->HasBoardIn(17))? GetSyncDone17() : true;

   return ok;
}

void WDDCB::WaitClockLock(){
   bool done=false;
   int count=30;
   do{
      ReceiveRegisters(DCB_REG_PLL_LOCK);
      done = (GetLmkPllLock() == 1);
//      done &= (GetSysDcmLock() == 1); // ask Elmar....
      done &= (GetWdbClkMgrLock() == 1);
      done &= (GetSerdesClkMgrLock() == 1);

      if(!done) {
         usleep(100000);
         count--;
         if(count == 0){
            printf("check %s!\n", GetBoardName().c_str());
            throw std::runtime_error("DCB clock is not locked");
         }
      }
   } while(!done);

}

void WDDCB::WaitReady(){
   //Wait Clock locked
   WaitClockLock();

   //Should wait some kind of initialization?

   //Then reset DPS for good measure
   ResetDps();
}

void WDDCB::ConfigureProperty(const std::string &name, Property &property) { 
   if(name=="SyncDelay"){
      ConfigureSyncDelay(property);
   } else {
      printf("Unknown property %s in WDDCB\n", name.c_str());
   }
};

void WDDCB::ConfigurationStarted(){
   int destPort = GetCrate()->GetSystem()->GetDAQServerPort();
   if(destPort) SetDestinationPort(destPort);
}

void WDDCB::ConfigurationEnded(){
}

void WDDCB::ConfigureSyncDelay(Property &property){
   unsigned int syncdelay;
   syncdelay = property.GetUHex();

   SetSyncDelay(syncdelay);
}

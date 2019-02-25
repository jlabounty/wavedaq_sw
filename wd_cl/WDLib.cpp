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

     PropertyGroup  group = fCrate->GetSystem()->GetGroupProperties(fGroupName);
      try{
         return group.at(name);
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
            printf("error parsing XML: Crate need MscbNode attribute");
            return;
         }
         WDCrate *c = new WDCrate(std::string(mscbnodestring));

         bool triggerFlag = false;
         //loop on Boards
         for(int i=0; i<mxml_get_number_of_children(crate_xml); i++){
            MXML_NODE *board_xml= mxml_subnode(crate_xml, i);
            std::string board_node_name = std::string(mxml_get_name(board_xml));
            if(board_node_name == "Board"){
               //create a new board
               char* slotstring = mxml_get_attribute(board_xml, "Slot");
               if(slotstring==NULL){
                  printf("error parsing XML: Board needs a Slot attributes");
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
                  printf("error parsing XML: WDB needs a Slot and a Name attributes");
                  return;
               }

               WDWDB *b = new WDWDB(c, atoi(slotstring), std::string(namestring));

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
                  printf("error parsing XML: TCB needs a Slot and a Name attributes");
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
   if(fTCBReaderThread) fTCBReaderThread->GoRun();
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
   if(fTCBReaderThread) fTCBReaderThread->StopRun();
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
   const int number_of_buffers = 5;

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
   fEventBuffer= new DAQBuffer<WDAQEvent>(number_of_buffers, "BUILDBUFFER");
   fCalibratedBuffer= new DAQBuffer<WDAQEvent>(number_of_buffers, "EVENTBUFFER");

   //spawn threads
   fCollectorThread = new WDAQPacketCollector(fPacketBuffer);
   fCollectorThread->Start();
   fBuilderThread = new WDAQEventBuilder(fPacketBuffer, fEventBuffer);
   fBuilderThread->Start();
   fWorkerThread = new WDAQWorker(fEventBuffer, fCalibratedBuffer);
   for(auto &c : fCrate){
      for(auto &b : *c){
         if(b) if(dynamic_cast<WDWDB*>(b) != nullptr) fWorkerThread->AddVoltageCalibration(dynamic_cast<WDWDB*>(b)->GetSerialNumber(), &(dynamic_cast<WDWDB*>(b)->mVCalib));
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
            if(b) if(dynamic_cast<WDWDB*>(b) != nullptr) fWriterThread->AddTimeCalibration(dynamic_cast<WDWDB*>(b)->GetSerialNumber(), &(dynamic_cast<WDWDB*>(b)->mTCalib));
         }
      }
      fWriterThread->Start();
   } else {
      printf("No writer thread running\n");
   }

   // create the TCBReadrer thread

   std::string readEnable;
   WDTCB* tcbboard = nullptr;
   try{
      WDBoard *trboard = GetTriggerBoard();
      tcbboard = dynamic_cast <WDTCB*> (trboard);
      if(tcbboard != nullptr) readEnable = tcbboard->GetProperty("ReadEnable").GetStringValue();
   } catch(const std::out_of_range &e){
      readEnable = "false";
   }

   if(readEnable=="true"){
      fTCBReaderThread = new WDAQTCBReader(fPacketBuffer,tcbboard);
      fTCBReaderThread->Start();
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

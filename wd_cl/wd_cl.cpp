#include "WDLib.h"
#include <vector>
#include <chrono>
#include <stdlib.h>
//debug - Thread that prints packets
class PacketDebug : public DAQThread{
   DAQBuffer<WDAQWdbPacketData> *fSource;

   void Begin(){ };

   void Loop(){
      WDAQWdbPacketData *ptr = nullptr;
      if(fSource->Try_pop(ptr)){
#if 0
         printf("received packet\n");
         printf("\t Board:%d\n", ptr->mBoardId);
         printf("\t Crate:%d\n", ptr->mCrateId);
         printf("\t Slot:%d\n", ptr->mSlotId);
         printf("\t ADC:%d\n", ptr->mADC);
         printf("\t Channel:%d\n", ptr->mChannel);
         printf("\t DataType:%d\n", ptr->mDataType);
         printf("\t TxEnable:%x\n", ptr->mTxEnable);
         printf("\t ZeroSuppressionMask:%x\n", ptr->mZeroSuppressionMask);
         printf("\t WDAQ Flags:%x\n", ptr->mWDAQFlags);
         printf("\t WDB Flags:%x\n", ptr->mWDBFlags);
         printf("\t TriggerSource:%d\n", ptr->mTriggerSource);
         printf("\t BitsPerSample:%d\n", ptr->mBitsPerSample);
         printf("\t SamplesPerEventPerChannel:%d\n", ptr->mSamplesPerEventPerChannel);
         printf("\t PayloadLenght:%d\n", ptr->mPayloadLength);
         printf("\t DataOffset:%d\n", ptr->mDataOffset);
         printf("\t EventNumber:%d\n", ptr->mEventNumber);
         printf("\t TriggerType:%x\n", ptr->mTriggerType);
         printf("\t TriggerNumber:%d\n", ptr->mTriggerNumber);
         printf("\t TriggerCell:%d\n", ptr->mTriggerCell);
         printf("\t SamplingFrequency:%d\n", ptr->mSamplingFrequency);
         printf("\t Temperature:%f\n", ptr->mTemperature);
         printf("\t DacOFS:%d\n", ptr->mDacOFS);
         printf("\t DacROFS:%d\n", ptr->mDacROFS);
         printf("\t FrontendSettings:%x\n", ptr->mFrontendSettings);
#endif

         delete ptr;
      }
   }
      

   void End() { };

   public:
   PacketDebug(DAQBuffer<WDAQWdbPacketData> *source){
      fSource = source;
   }
};
//debug events, to be used with no-writer
class EventDebug : public DAQThread{
   DAQBuffer<WDAQEvent> *fSource;
   void Setup(){
      printf("DAQ event debug thread started\n");
   }

   void Begin(){
      printf("DAQ event debug thread running\n");
   };

   void Loop(){
      WDAQEvent *ptr = nullptr;
      if(fSource->Try_pop(ptr)){
#if 0
         printf("Got Event %d\n", ptr->mTriggerNumber);
#endif

         delete ptr;
      }
   }
   void End() { };

   public:
   EventDebug(DAQBuffer<WDAQEvent> *source){
      fSource = source;
   }
};


#define BARSIZE 80 
void drawBar(const char* name, float value, float valueMax, bool printData = false){
   float v = value * 1./valueMax;
   bool overscale = false;
   if(v>1) {
      overscale=true;
      v = 1;
      printf("\e[1;31m");//all make red
   }
   printf("%10s (%5.1f%%):", name, v*100);

   if(v>=0.9) printf("\e[1;31m");//red
   else if(v>=0.7) printf("\e[1;33m");//yellow
   else printf("\e[1;32m");//green

   for(int i=0; i< BARSIZE; i++) if(i*1./BARSIZE < v) putchar('-'); else putchar(' ');
   printf("\e[0m|");//reset color
   if(printData){
      //print values
      printf("%g:%g|", value, valueMax);
   }
   printf("\n");
}

std::map<short, FILE*> CreateScalerFiles(WDSystem* sys, int n, float down, float up, std::string group=""){
   std::map<short, FILE*> map;

   for(auto c : *sys)
      for(auto b :*c)
         if(b){
            WDWDB* wdb = dynamic_cast<WDWDB*>(b);
            if(wdb != nullptr){
               if(!group.length() || wdb->GetGroup() == group){
                  char buf[100];
                  sprintf(buf, "out-%s.dat", wdb->GetName().c_str());
                  FILE *f= fopen(buf, "w");

                  //print header
                  fprintf(f, "# Name: %s\n", wdb->GetBoardName().c_str());
                  fprintf(f, "# WDB: %s\n", wdb->GetName().c_str());
                  fprintf(f, "# Revision: %c\n", wdb->GetBoardRevision() + 'A');
                  fprintf(f, "# Crate: %s\n", wdb->GetCrate()->GetCrateName().c_str());
                  fprintf(f, "# Slot: %d\n", wdb->GetSlot());
                  fprintf(f, "# Gain: ");
                  for(int iCh=0; iCh<16; iCh++){
                     if(iCh>0)
                        fprintf(f, ", ");
                     fprintf(f, "%f", wdb->GetFeGain(iCh));
                  }
                  fprintf(f, "\n");
                  fprintf(f, "# PZC: ");
                  for(int iCh=0; iCh<16; iCh++){
                     if(iCh>0)
                        fprintf(f, ", ");
                     fprintf(f, "%d", wdb->GetFePzc(iCh));
                  }
                  fprintf(f, "\n");
                  fprintf(f, "# PZC level: %d\n", wdb->GetDacPzcLevelN());
                  fprintf(f, "# Channel Polarity: %04x\n", wdb->GetTrgSrcPolarity() & 0xFFFF);
                  fprintf(f, "# Down: %f\n", down);
                  fprintf(f, "# Up: %f\n", up);
                  fprintf(f, "# N: %d\n", n);
               
                  map[wdb->GetSerialNumber()] = f;
               }
            }
         }

   return map;
}
void SetThreshold(WDSystem* sys, float v, std::string group=""){
   for(auto c : *sys)
      for(auto b :*c)
         if(b){
            WDWDB* wdb = dynamic_cast<WDWDB*>(b);
            if(wdb != nullptr){
               if(!group.length() || wdb->GetGroup() == group)
                  wdb->SetDacTriggerLevelV(-1,v);
            }
         }

}

void SaveScalers(WDSystem* sys, std::map<short, FILE*>& files, float v, std::string group = ""){
   for(auto c : *sys)
      for(auto b :*c)
         if(b){
            WDWDB* wdb = dynamic_cast<WDWDB*>(b);
            if(wdb != nullptr){
               if(!group.length() || wdb->GetGroup() == group){
                  wdb->SetScalerRst(1);
                  wdb->SetScalerRst(0);
               }
            }
         }

   sleep(3);
   for(auto c : *sys)
      for(auto b :*c)
         if(b){
            WDWDB* wdb = dynamic_cast<WDWDB*>(b);
            if(wdb != nullptr){
               if(!group.length() || wdb->GetGroup() == group){
                  FILE* f = files.at(wdb->GetSerialNumber());
                  std::vector<uint64_t> s;
                  wdb->GetScalers(s);
                  fprintf(f, "%f ", v);
                  for(int j=0; j<16; j++) fprintf(f,"%lld ", s[j]);
                  fprintf(f, "\n");
               }
            }
         }
}

void CloseScalerFile(std::map<short, FILE*>& files){
   for(auto f :files)
      fclose(f.second);
}

void GenerateGroupMap(WDSystem* sys, std::map<std::string,std::vector<WDPosition>> &groups, std::vector<WDPosition> &system, int boardType = BRD_TYPE_ID_BLANK){
   for(auto c : *sys){
      std::string crategroup = c->GetGroup();
      WDPosition crateposition = c->GetPosition();

      bool anyBoard = false;
      for(auto b :*c)
         if(b){
            std::string group = b->GetGroup();
            WDPosition position = b->GetPosition();
            if(boardType == BRD_TYPE_ID_BLANK ||
               (boardType == BRD_TYPE_ID_WDB && dynamic_cast<WDWDB*>(b) != nullptr)||
               (boardType == BRD_TYPE_ID_TCB && dynamic_cast<WDTCB*>(b) != nullptr)||
               (boardType == BRD_TYPE_ID_DCB && dynamic_cast<WDDCB*>(b) != nullptr)){

               if(crategroup.length()==0 && group.length()){
                  //board with group in crate without group

                  groups[group].push_back(position);
               }

               anyBoard = true;
            }
         }
      
      if(anyBoard){
         if(crategroup.length()){
            //at least one board in a crate with group
            groups[crategroup].push_back(crateposition);
         }

         //if at least one board add to system
         system.push_back(crateposition);
      }
   }

}

//control if parameters are written istantaneously (true) or on ApplySettings (false)
const bool sequencerNotifyFrontend = false;

// limit on number of lines for each function, negative number to skip
const int sequencerFunctionLineLimit = 700;

FILE* CreateSequencerFile(std::string filename){
   time_t rawtime;
   FILE* fHandle = fopen((filename + ".msl").c_str(), "w");

   time (&rawtime);

   fprintf(fHandle, "LIBRARY %s\n", filename.c_str());
   fprintf(fHandle, "COMMENT library \"%s\" created on %.19s by automatic script\n\n", filename.c_str(), ctime(&rawtime));

   return fHandle;
}

int CreateSequencerFunction(std::stringstream &s, std::string name, bool odbsubdir=false){
   s << "SUBROUTINE " << name << std::endl;
   if(odbsubdir){
      s << "ODBSUBDIR \"/Equipment/Trigger/Settings/WaveDAQ/\"" << std::endl;
      return 2;
   }
   return 1;
}

int CloseSequencerFunction(std::stringstream &s, bool odbsubdir=false){
   if(odbsubdir) s << "ENDODBSUBDIR" << std::endl;
   s << "ENDSUBROUTINE" << std::endl << std::endl;

   if (odbsubdir) return 3;
   else return 2;
}

bool IsSequencerArray(const std::string &p, std::string *midasType=nullptr, int *arraySize=nullptr){
   //if a key is given then the value is a scalar
   if (p.find('[') != std::string::npos)
      return false;

   //else check the name (to be kept up to date with wdaq_fe)
   if(p == "FrontendGain"){
      if(midasType!=nullptr) *midasType="FLOAT";
      if(arraySize!=nullptr) *arraySize=16;
      return true;
   } else if(p == "FrontendPzc"){
      if(midasType!=nullptr) *midasType="BOOL";
      if(arraySize!=nullptr) *arraySize=16;
      return true;
   } else if(p == "TriggerLevel"){
      if(midasType!=nullptr) *midasType="FLOAT";
      if(arraySize!=nullptr) *arraySize=16;
      return true;
   } else if(p == "TriggerGain"){
      if(midasType!=nullptr) *midasType="INT8";
      if(arraySize!=nullptr) *arraySize=16;
      return true;
   } else if(p == "TriggerTdcOffset"){
      if(midasType!=nullptr) *midasType="UINT8";
      if(arraySize!=nullptr) *arraySize=16;
      return true;
   } else if(p == "BgoHitDelay"){
      if(midasType!=nullptr) *midasType="INT32";
      if(arraySize!=nullptr) *arraySize=2;
      return true;
   } else if(p == "RdcHitMask"){
      if(midasType!=nullptr) *midasType="UINT32";
      if(arraySize!=nullptr) *arraySize=3;
      return true;
   } else if(p == "TcMask"){
      if(midasType!=nullptr) *midasType="UINT32";
      if(arraySize!=nullptr) *arraySize=4;
      return true;
   } else if(p == "CdchMask"){
      if(midasType!=nullptr) *midasType="UINT32";
      if(arraySize!=nullptr) *arraySize=8;
      return true;
   } else if(p == "TriggerEnable"){
      if(midasType!=nullptr) *midasType="BOOL";
      if(arraySize!=nullptr) *arraySize=64;
      return true;
   } else if(p == "TriggerPrescaling"){
      if(midasType!=nullptr) *midasType="UINT32";
      if(arraySize!=nullptr) *arraySize=64;
      return true;
   } else if(p == "TriggerDelay"){
      if(midasType!=nullptr) *midasType="INT32";
      if(arraySize!=nullptr) *arraySize=64;
      return true;
   } else if(p == "DetectorDelay"){
      if(midasType!=nullptr) *midasType="INT32";
      if(arraySize!=nullptr) *arraySize=6;
      return true;
   } else if(p == "SwZeroSuppressionRebinThr"){
      if(midasType!=nullptr) *midasType="FLOAT";
      if(arraySize!=nullptr) *arraySize=2;
      return true;
   } else {
      return false;
   }
};

int CreateSequencerODBSet(std::stringstream &s, const std::string& crate, const std::string& board, const std::string& p, const std::string& val){
   int count = 0;
   if(IsSequencerArray(p)){
      //check value to set is an array
      if (val.find(',') != std::string::npos) {
         //set value is array
         std::istringstream is(val);
         std::string ival;
         int element =0;
         while (getline(is, ival, ',')){
            s << "ODBSET " << crate << "/" << board << "/" << p << "["<< element << "], " << ival << ", " << ((sequencerNotifyFrontend)?"1":"0") << std::endl;
            element ++;
            count++;
         }

      } else {
         //single value
         s << "ODBSET " << crate << "/" << board << "/" << p << "[*], " << val << ", " << ((sequencerNotifyFrontend)?"1":"0") << std::endl;
         count++;
      }
   } else {
      //value in ODB is a single key
      auto comma = val.find(',');
      if(comma != std::string::npos) {
         std::string v(val.begin(), val.begin() + comma);
         s << "ODBSET " << crate << "/" << board << "/" << p << ", " << v << ", " << ((sequencerNotifyFrontend)?"1":"0") << std::endl;
      } else {
         s << "ODBSET " << crate << "/" << board << "/" << p << ", " << val << ", " << ((sequencerNotifyFrontend)?"1":"0") << std::endl;
      }
      count++;
   }

   return count;
}

int CreateSequencerSet(std::stringstream &s, WDSystem* sys, WDPosition& pos, std::string& p){
   WDCrate* c = sys->GetCrateAt(pos);
   WDBoard* b = sys->GetBoardAt(pos);

   std::string boardname("*");
   if(b){
      //ODBSet for single board
      boardname = b->GetBoardName();
   }

   return CreateSequencerODBSet(s, c->GetCrateName(), boardname, p, "$1");
}

int CreateSequencerReset(std::stringstream &s, WDSystem* sys, WDPosition& pos, std::string& p, std::string& propertyName, std::string& otherVal){
   int count = 0;
   WDCrate* c = sys->GetCrateAt(pos);
   WDBoard* b = sys->GetBoardAt(pos);

   if(b){
      //ODBSet for single board
      try{
         Property& prop = b->GetProperty(p);
         std::string val = prop.GetStringValue();
         count += CreateSequencerODBSet(s, c->GetCrateName(), b->GetBoardName(), p, val);
      } catch (...){
         //if no property value use alternative value
         if(otherVal.length())
            count += CreateSequencerODBSet(s, c->GetCrateName(), b->GetBoardName(), p, otherVal);
      }
   } else {
      //Set to default external value
      if(otherVal.length())
         count += CreateSequencerODBSet(s, c->GetCrateName(), "*", p, otherVal);

      for(auto& board : *c){
         if(board){
            try{
               Property& prop = board->GetProperty(propertyName);
               std::string val = prop.GetStringValue();

               //board with different property from group...
               if(val != otherVal){
                  count += CreateSequencerODBSet(s, c->GetCrateName(), board->GetBoardName(), p, val);
               }
            } catch (...){
               //already accounted by crate ODBSet
            }
         }
      }
   }

   return count;
}

bool CreateEntryOdbFile(FILE* fHandle, const std::string &crate, const std::string &board, const std::string &property, const std::string &val){
   std::string midasType;
   int arraySize;
   if (IsSequencerArray(property, &midasType, &arraySize)){

      fprintf(fHandle, "[/Equipment/Trigger/Settings/WaveDAQ/%s/%s]\n", crate.c_str(), board.c_str());
      fprintf(fHandle, "%s = %s[%d] :\n", property.c_str(), midasType.c_str(), arraySize);
      if (val.find(',') != std::string::npos) {
         //set value is array
         std::istringstream is(val);
         std::string ival;
         int element =0;
         while (getline(is, ival, ',')){
            fprintf(fHandle, "[%d] %s\n", element, ival.c_str());
            element ++;
         }
         if(element != arraySize){
            printf("number of properties %d do not match array size %d\n", element, arraySize);
         }
      } else {
         for(int element=0; element<arraySize; element++){
            fprintf(fHandle, "[%d] %s\n", element, val.c_str());
         }
      }

      fprintf(fHandle, "\n");

      return true;
   } else {
      printf("property %s not supported in ODB load files\n", property.c_str());
      return false;
   }
}

bool CreateOdbFile(std::string filename, WDSystem* sys, std::vector<WDPosition>& items, std::string& p){
   FILE* fHandle = fopen((filename + ".odb").c_str(), "w");

   for(auto &pos : items){
      WDCrate* c = sys->GetCrateAt(pos);
      WDBoard* b = sys->GetBoardAt(pos);

      if(b){
         try{
            Property& prop = b->GetProperty(p);
            std::string val = prop.GetStringValue();
            bool ret = CreateEntryOdbFile(fHandle, c->GetCrateName(), b->GetBoardName(), p, val);
            if(!ret){
               fclose(fHandle);
               return false;
            }
         } catch (...){
         }
      } else { 
         for(auto& board : *c){
            if(board){
               try{
                  Property& prop = board->GetProperty(p);
                  std::string val = prop.GetStringValue();
                  bool ret = CreateEntryOdbFile(fHandle, c->GetCrateName(), board->GetBoardName(), p, val);
                  if(!ret){
                     fclose(fHandle);
                     return false;
                  }
               } catch (...){
               }
            }
         }
      }
   }

   fclose(fHandle);
   return true;
}

FILE* GenerateSequencer(WDSystem* sys, std::vector<WDPosition> &items, std::string filename, std::vector<std::string> &properties){

   //find corresponding property group

   FILE* f = CreateSequencerFile("WDAQ" + filename);

   for(auto& p: properties){
      std::stringstream s;
      int lines = 0;

      auto bracket = p.find('[');
      std::string propertyname;
      std::string propertyindex;

      if(bracket != std::string::npos){
         propertyname.append(p.begin(), p.begin() + bracket);
         //Property name contains [, strip it down in the function name
         auto otherbracket = p.find(']');
         if(otherbracket != std::string::npos){
            propertyindex.append(p.begin() + bracket + 1, p.begin() + otherbracket);
         }
      }else{
         propertyname = p;
      }
      
      if(propertyindex.length()){
         lines += CreateSequencerFunction(s, "Set" + filename + propertyname + propertyindex, true);
      } else {
         lines += CreateSequencerFunction(s, "Set" + filename + propertyname, true);
      }

      for(auto& pos: items){
         lines += CreateSequencerSet(s, sys, pos, p);
      }
      lines += CloseSequencerFunction(s, true);
      //printf("function %s lines %d\n", ("Set" + filename + p).c_str(), lines);
      if(lines < sequencerFunctionLineLimit || sequencerFunctionLineLimit < 0) fputs(s.str().c_str(), f);
      else printf("***** function %s (lines %d) skipped!\n", ("Set" + filename + p).c_str(), lines);

      s.str("");
      lines = 0;

      if(propertyindex.length()){
         lines += CreateSequencerFunction(s, "Reset" + filename + propertyname + propertyindex, true);
      } else {
         lines += CreateSequencerFunction(s, "Reset" + filename + propertyname, true);
      }
      for(auto& pos: items){
         std::string groupname = filename;
         if(filename == "System"){
            WDBoard *b = sys->GetBoardAt(pos);
            WDCrate *c = sys->GetCrateAt(pos);
            if(b) groupname = b->GetGroup();
            else groupname = c->GetGroup();
         }
         std::string val = "";
         try{
            PropertyGroup &pg = sys->GetGroupProperties(groupname);
            Property& prop = pg.at(propertyname);
            val = prop.GetStringValue();
         } catch (...){
         }

         lines += CreateSequencerReset(s, sys, pos, p, propertyname, val);
      }
      lines += CloseSequencerFunction(s, true);
      //printf("function %s lines %d\n", ("Reset" + filename + p).c_str(), lines);
      if(lines < sequencerFunctionLineLimit || sequencerFunctionLineLimit < 0) fputs(s.str().c_str(), f);
      else {
         printf("***** function %s (lines %d) replaced!\n", ("Reset" + filename + p).c_str(), lines);

         bool ret = CreateOdbFile("WDAQReset" + filename + p, sys, items, p);

         if(ret){
            //add sequencer function to load the ODB file
            s.str("");
            lines = 0;
            lines += CreateSequencerFunction(s, "Reset" + filename + p);

            s << "ODBLOAD $/lib/WDAQReset" << filename << p << ".odb" << std::endl;
            lines++;
            lines += CloseSequencerFunction(s);

            fputs(s.str().c_str(), f);
         }

      }
   }

   return f;
}

void CloseSequencer(FILE* f){
   fclose(f);
}

int main(int argc, char *argv[])
{
   int option;
   WDSystem *sys;
   if(argc<2){
      printf("exectute %s wdsystem.xml [-n]\n", argv[0]);
      printf("use -n flag to skip connecting the system\n");
      return -1;
   }

   sys = new WDSystem();
   sys->CreateFromXml(std::string(argv[1]));

   //check any crate is off
   bool crateOff = false;
   for(auto &c: *sys){
      if(! c->IsPowered())
         crateOff = true;
   }

   //if off ask to switch on
   if(crateOff){
      char choice;
      printf("A crate is off, power on? [y/n] ");
      scanf(" %c", &choice);
      if(choice == 'y'){
         printf("powering on...");
         sys->PowerOn();
         printf("OK!\n");
         int sec = 120;
         do{
            printf("waiting %3d s\r", sec);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            sec --;
         } while(sec > 0);
         printf("\n");
      }
   } else {
      printf("All crates on, proceeding...\n");
   }

   bool skipInit = false;
   bool skipConnect = false;
   if(argc > 2){
      for(int i=2; i<argc; i++){
         if(std::string(argv[i]) == "-n"){
            skipConnect = true;
            skipInit = true;
         }
         if(std::string(argv[i]) == "-s"){
            skipInit = true;
         }
      }
   }
   //connect to boards
   if(!skipConnect)
      sys->Connect();
   else
      printf("System is loaded but was not connected\n");

   if(!skipInit)
      sys->Init();
   else
      printf("System is not inited\n");

   /* main loop on the options */
   do {
      printf("\n  --- options: \n");
      printf("[ 1]: configure system     \t \t  [ 2]: prepare to run       \n");
      printf("[ 3]: system start         \t \t  [ 4]: get busy             \n");
      printf("[ 5]: system stop          \t \t  [ 6]: system sync          \n");
      printf("[ 7]: turn on              \t \t  [ 8]: turn off             \n");
      printf("[ 9]: train serdes         \t \t  [10]: print serdes state   \n");
      printf("[11]: spawn daq            \t \t  [12]: stop daq             \n");
      printf("[13]: Test trigger links   \t \t  [14]: attach debug thread  \n");
      printf("[15]: draw system          \t \t  [16]: print firmware version\n");
      printf("[17]: update firmware      \t \t  [18]: clean buffer         \n");
      printf("[19]: show DAQ status      \t \t  [20]: reboot CMBs          \n");
      printf("[21]: Ascii command        \t \t  [22]: Pedestal scan        \n");
      printf("[23]: Make Sequencer file  \t \t  [24]: flash CMBs           \n");
      printf("[25]: Log temperatures     \t \t  [  ]:                      \n");
      do {
         char opline[256];
         printf("give an option: ");
         scanf("%s",opline);
         option = strtod(opline,NULL);

         if(option == 1)
         {
            printf("configuring system... ");
            sys->Configure();
         }
         if(option == 2)
         {
            printf("prepare for the run... ");
            sys->SpawnDAQ();
            sys->SetSerdesTraining(true);
            printf("Serdes pattern configured\n");
            sys->TrainSerdes(false); // do not wait here, insert print in the middle
            printf("Serdes Train started\n");
            sys->WaitSerdesTrainingFinish();
            printf("Serdes State: ");
            if(sys->IsSerdesGood()){
               printf("OK!\n");
            } else {
               printf("***BAD***!\n");
            }
            printf("Serdes Trained, configuring system\n");
            sys->Configure();
            printf("Boards configured and ready\n");
         }
         if(option == 3)
         {
            printf("starting system...\n");
	    sys->GoRun();
         }
         if(option == 4)
         {
            WDBoard *triggerb = sys->GetTriggerBoard();
            if(triggerb){
               if(triggerb->IsBusy()){
                  printf("System is Busy\n");
               } else {
                  printf("System is Not Busy\n");
               }
            }

            for(auto c : *sys)
               for(auto b :*c)
                  if(b){
                     if(dynamic_cast<WDTCB*>(b) != nullptr){
                        if(b->IsBusy())
                           printf("TCB %s is busy***********\n", b->GetBoardName().c_str());
                        else
                           printf("TCB %s is not busy\n", b->GetBoardName().c_str());
                     } else if(dynamic_cast<WDWDB*>(b) != nullptr){
                        if(b->IsBusy())
                           printf("WDB %s (WD%03u) is busy***********\n", b->GetBoardName().c_str(), b->GetSerialNumber());
                        else
                           printf("WDB %s (WD%03u) is not busy\n", b->GetBoardName().c_str(), b->GetSerialNumber());
                     } else if(dynamic_cast<WDDCB*>(b) != nullptr){
                        if(b->IsBusy())
                           printf("DCB %s (DCB%02u) is busy***********\n", b->GetBoardName().c_str(), b->GetSerialNumber());
                        else
                           printf("DCB %s (DCB%02u) is not busy\n", b->GetBoardName().c_str(), b->GetSerialNumber());
                     }
                  }
         }
         if(option == 5)
         {
            printf("stopping system...\n");
            sys->StopRun();
         }
         if(option == 6)
         {
            printf("generating SYNC...\n");
            sys->Sync();

            for(auto c : *sys)
               for(auto b :*c)
                  if(b){
                     if(dynamic_cast<WDTCB*>(b) != nullptr){
                        u_int32_t val = 0;
                         dynamic_cast<WDTCB*>(b)->GetSyncWaveform(&val);
                         printf("%s %d %04x\n", b->GetBoardName().c_str(), b->GetSlot(), val);
                     }
                  }
         }
         if(option == 7)
         {
            sys->PowerOn();
         }
         if(option == 8)
         {
            sys->PowerOff();
         }
         if(option == 9)
         {
            sys->SetSerdesTraining(true);
            sys->TrainSerdes(true);
            printf("Serdes State: ");
            if(sys->IsSerdesGood()){
               printf("OK!\n");
            } else {
               printf("***BAD***!\n");
            }
         }
         if(option == 10)
         {
            for(auto c : *sys)
               for(auto b :*c)
                  if(b){
                     if(dynamic_cast<WDTCB*>(b) != nullptr){
                        printf("TCB %s\n", b->GetBoardName().c_str());
                        unsigned int val;
                        dynamic_cast<WDTCB*>(b)->GetAutoCalibrateBusy(&val);
                        printf("busy: %08x\n", val);
                        dynamic_cast<WDTCB*>(b)->GetAutoCalibrateFail(&val);
                        printf("fail: %08x\n", val);
                        dynamic_cast<WDTCB*>(b)->GetAutoAlignDlys(&val);
                        printf("dlys: %08x\n", val);
                     }
                     if(dynamic_cast<WDDCB*>(b) != nullptr){
                        printf("DCB %s\n", b->GetBoardName().c_str());
                        std::cout << dynamic_cast<WDDCB*>(b)->SendReceiveUDP("sdstat");
                     }
                  }
         }
         if(option == 11)
         {
            sys->SpawnDAQ();
            //PacketDebug* p =  new PacketDebug(sys->fPacketBuffer);
            //p->Start();
            //p->GoRun();
         }
         if(option == 12)
         {
            sys->StopDAQ();
         }
         if(option == 13)
         {
            unsigned int word0, word1;
            printf("serdesbit 31: 0? (hex)\n");
            scanf("%x",&word0);
            printf("serdesbit 63:32? (hex)\n");
            scanf("%x",&word1);
            //set TestTxMode and FadcMode, then take bus and fill memories
            //finally mask trg and busy, disable triggers and go run
            for(auto c : *sys){
               for(auto b :*c)
                  if(b){
                     if(dynamic_cast<WDTCB*>(b) != nullptr){
                        WDTCB* tcb = static_cast<WDTCB*>(b);
                        printf("Configuring %s\n", tcb->GetBoardName().c_str());
                        sys->SetSerdesTraining(false);
                        tcb->SetPacketizerBus(false);
                        tcb->SetFadcMode(true);
                        tcb->SetTestTxMode(true);
                        tcb->FillMemory(MEMBASEADDR+16*2*MEMDIM, MEMDIM, word0);
                        tcb->FillMemory(MEMBASEADDR+16*2*MEMDIM+MEMDIM, MEMDIM, word1);

                        tcb->SetTRGBusMasks(false, true, false); 
                        unsigned int val = 0;
                        tcb->SetRENA(&val, 0);
                        tcb->SetRENA(&val, 1);
                        tcb->GoRun();
                     }
                  }
            }
            //make another loop to check input memories
            unsigned int mem[MEMDIM*2];
            for(auto c : *sys){
               for(auto b :*c)
                  if(b){
                     if(dynamic_cast<WDTCB*>(b) != nullptr){
                        WDTCB* tcb = static_cast<WDTCB*>(b);
                        printf("TCB %s\n", tcb->GetBoardName().c_str());
                        tcb->SWStop();

                        int nSerdes = tcb->GetNSerdes();
                        if(((tcb->GetIDCode()&0xf000) >> 12) == 1)
                           nSerdes = 0; // skip TCB_1

                        for(int iSerdes=0; iSerdes<nSerdes; iSerdes++){
                           tcb->ReadMemoryBLT(2*iSerdes, mem);
                           tcb->ReadMemoryBLT(2*iSerdes+1, mem+MEMDIM);
                           printf("\tSerdes %d\n", iSerdes);
                           bool correct = true;

                           for(int i=0; i<MEMDIM; i++){
                              if(mem[i] != word0 || mem[i+MEMDIM] != word1){
                                 if(correct) printf("\t\t%08x%08x %08x%08x\n", mem[i+MEMDIM], mem[i], word1, word0);
                                 correct = false;
                              }
                           }

                           if(correct)
                              printf("\tOK!\n");
                           else
                              printf("\tBAD!\n");
                        }
                     }
                  }
            }
         }
         if(option == 14)
         {
            EventDebug* debugger = new EventDebug(sys->fCalibratedBuffer);
            debugger->Start();
            //sleep(10);
            debugger->GoRun();
         }
         if(option == 15)
         {
            int size = sys->GetCrateSize();
            printf("system with %d crates\n", size);
            //for(int icrate=0; icrate<size; icrate++){
            //   wdcrate *c = sys->getcrateat(icrate);
            for(auto c : *sys){
               printf("\t crate name %s",  c->GetMscbName().c_str());
               if(c == sys->GetCrateAt(sys->GetTriggerCrateId())){
                  printf(" trigger crate\n");
               } else printf("\n");

               //for(int iboard=0; iboard<18; iboard++){
               //   printf("\t \t slot %d: ", iboard);
               //   if(c->hasboardin(iboard)){
               //      wdboard *b = c->getboardat(iboard);
               for(auto b : *c){
                  if(b!=0){
                     printf("\t \t slot %d: ", b->GetSlot());
                     if(dynamic_cast<WDWDB*>(b) == nullptr){
                        if(dynamic_cast<WDTCB*>(b) == nullptr)
                           printf("with board in slot %d of crate %s\n", b->GetSlot(), b->GetCrate()->GetMscbName().c_str());
                        else
                           printf("tcb group=%s\n", b->GetGroup().c_str());
                     } else
                        printf("wdb with name %s group=%s\n", dynamic_cast<WDWDB*>(b)->GetName().c_str(), b->GetGroup().c_str());

                     PropertyGroup p = b->GetProperties();
                     //for(std::map<std::string,std::string>::iterator it=p.begin(); it!=p.end(); it++){
                     for(auto prop : p){
                        printf("\t \t \t %s: %s\n", prop.first.c_str(), prop.second.GetStringValue().c_str());
                     }

                     std::string gr = b->GetGroup();
                     PropertyGroup pgr = sys->GetGroupProperties(gr);
                     //for(std::map<std::string,std::string>::iterator it=pgr.begin(); it!=pgr.end(); it++){
                     for(auto prop : pgr){   
                        printf("\t \t \t %s: %s from group %s\n", prop.first.c_str(), prop.second.GetStringValue().c_str(), gr.c_str());
                     }
                  } else {
                     printf("\t \t empty\n");
                  }
               }
            }
            printf("\n");
            printf("board map:\n");
            for(auto i: sys->fBoardMap){
               printf("\t%s crateId:%ld Slot:%d\n", i.first.c_str(), i.second.fCrate, i.second.fSlot);
            }
         }
         if(option == 16)
         {
            bool difference = false;
            unsigned int wdbFwHash = 0;
            unsigned int wdbSwHash = 0;
            unsigned int tcb1Date = 0;
            unsigned int tcb2Date = 0;
            unsigned int tcb3Date = 0;
            for(auto c : *sys)
               for(auto b :*c)
                  if(b){
                     if(dynamic_cast<WDWDB*>(b) != nullptr){
                        WDWDB* wdb = static_cast<WDWDB*>(b);
                        printf("WDB %s: %08x %08x", wdb->GetBoardName().c_str(), wdb->GetFwGitHashTag(), wdb->GetSwGitHashTag());
                        if(wdbFwHash){
                           if(wdbFwHash != wdb->GetFwGitHashTag()){
                              difference = true;
                              printf("******");
                           }
                        } else wdbFwHash = wdb->GetFwGitHashTag();
                        if(wdbSwHash){
                           if(wdbSwHash != wdb->GetSwGitHashTag()){
                              difference = true;
                              printf("******");
                           }
                        } else wdbSwHash = wdb->GetSwGitHashTag();

                        printf("\n");
                     }
                     if(dynamic_cast<WDTCB*>(b) != nullptr){
                        WDTCB* tcb = static_cast<WDTCB*>(b);
                        unsigned int val;
                        tcb->GetCompilDate(&val);
                        
                        unsigned int *p;
                        switch(tcb->GetIDCode()>>12){
                        case 1:
                           printf("TCB1 %s: %08x", tcb->GetBoardName().c_str(), val);
                           p = &tcb1Date;
                           break;
                        case 2:
                           printf("TCB2 %s: %08x", tcb->GetBoardName().c_str(), val);
                           p = &tcb2Date;
                           break;
                        case 3:
                        default:
                           printf("TCB3 %s: %08x", tcb->GetBoardName().c_str(), val);
                           p = &tcb3Date;
                           break;
                        }

                        if(*p){
                           if(*p != val){
                              difference = true;
                              printf("******");
                           }
                        } else {
                           *p = val;
                        }

                        printf("\n");
                     }
                  }

            if(difference) printf("\n\tDifferent firmware version in the system!\n");
         }

         if(option == 17)
         {
            for(auto c : *sys)
               for(auto b :*c)
                  if(b){
                     int ret = MSCB_SUCCESS;

                     if(dynamic_cast<WDWDB*>(b) != nullptr){
                        WDWDB* wdb = static_cast<WDWDB*>(b);
                        char cstr[wdb->GetName().size() + 1];
                        strcpy(cstr, wdb->GetName().c_str());
                        int fd = mscb_init(cstr, 0, "", 0);
                        if(fd>0){
                           ret = mscb_upload(fd, wdb->GetSerialNumber(), 0, "../../firmware/WD2/wd2_sys_ctrl/wd2_xps_hw/implementation/download.bit", 0);
                           if(ret == MSCB_SUCCESS)
                              ret = mscb_upload(fd, wdb->GetSerialNumber(), 0, "../../firmware/WD2/wd2_sys_ctrl/wd2_xsdk_workspace/wd2_app_sw/app_sys_ctrl/Debug/app_sys_ctrl.srec", 0);
                           if(ret == MSCB_SUCCESS)
                              ret = mscb_exit(fd);

                        } else ret = MSCB_NOT_FOUND; 
                     }

                     if(dynamic_cast<WDTCB*>(b) != nullptr){
                        WDTCB* tcb = static_cast<WDTCB*>(b);
                        switch(tcb->GetIDCode()>>12){
                        case 1:
                           ret = mscb_upload(tcb->GetCrate()->GetMscbHandle(), 20, tcb->GetSlot(), "../../firmware/TCB/TCB_1_0/TCB_1_0.runs/impl_1/TCB_TOP.bit", MSCB_UPLOAD_SUBADDR); 
                           break;
                        case 2:
                           ret = mscb_upload(tcb->GetCrate()->GetMscbHandle(), 20, tcb->GetSlot(), "../../firmware/TCB/TCB_2_0/TCB_2_0.runs/impl_1/TCB_TOP.bit", MSCB_UPLOAD_SUBADDR);
                           break;
                        case 3:
                        default:
                           ret = mscb_upload(tcb->GetCrate()->GetMscbHandle(), 20, tcb->GetSlot(), "../../firmware/TCB/TCB_3_0/TCB_3_0.runs/impl_1/TCB_TOP.bit", MSCB_UPLOAD_SUBADDR);
                           break;
                        }
                        if(ret == MSCB_SUCCESS){
                           char val = 3; //Init slot
                           ret = mscb_write(tcb->GetCrate()->GetMscbHandle(), 20, 17+tcb->GetSlot(), &val, sizeof(val));  
                        }
                     }

                     if(ret != MSCB_SUCCESS){
                        printf("Upload failed!");
                     }
                  }
         }
         if(option == 18)
         {
            sys->GetDAQSystem()->CleanBuffers();
         }
         if(option == 19)
         {
            bool done = false;
            int i =0;
            long OldCollectorNPackets=0;
            for (auto t : sys->fCollectorThreads) 
               OldCollectorNPackets+= t->GetReceivedPackets();
            long OldCollectorDroppedPackets=0;
            for(auto t : sys->fCollectorThreads)
               OldCollectorDroppedPackets += t->GetDroppedPackets();
            long OldCollectorCorruptedPackets=0;
            for(auto t : sys->fCollectorThreads)
               OldCollectorCorruptedPackets += t->GetCorruptedPackets();
            for(auto t : sys->fBuilderThreads)
               OldCollectorCorruptedPackets += t->GetBadPackets();
            long OldBuilderBuildedEvent=0;
            for(auto t : sys->fBuilderThreads)
               OldBuilderBuildedEvent += t->GetBuildedEvents();
            long OldBuilderDroppedEvent=0;
            for(auto t : sys->fBuilderThreads)
               OldBuilderDroppedEvent += t->GetDroppedEvents();
            long OldBuilderOldEvent=0;
            for(auto t : sys->fBuilderThreads)
               OldBuilderOldEvent += t->GetOldEvents();

            long AvgCollectorNPackets = 0;
            long AvgCollectorDroppedPackets = 0;
            long AvgCollectorCorruptedPackets = 0;
            long AvgBuilderBuildedEvent = 0;
            long AvgBuilderDroppedEvent = 0;
            long AvgBuilderOldEvent = 0;
            int nAvg = 0;

            long MaxCollectorNPackets = 0;
            long MaxCollectorDroppedPackets = 0;
            long MaxCollectorCorruptedPackets = 0;
            long MaxBuilderBuildedEvent = 0;
            long MaxBuilderDroppedEvent = 0;
            long MaxBuilderOldEvent = 0;

            //long OldWorkerNEvent;
            //long OldWorkerDropped;
            sleep(1);//wait to get events
            while(!done){
               //gather statistics
               long collectorNPackets = 0;
               for (auto t: sys->fCollectorThreads)
                  collectorNPackets += t->GetReceivedPackets();
               long collectorDroppedPackets = 0;
               for (auto t: sys->fCollectorThreads)
                  collectorDroppedPackets += t->GetDroppedPackets();
               long collectorCorruptedPackets = 0;
               for (auto t: sys->fCollectorThreads)
                  collectorCorruptedPackets += t->GetCorruptedPackets();
               for(auto t : sys->fBuilderThreads)
                  collectorCorruptedPackets += t->GetBadPackets();
               int  collectorReceivedMessages = 0;
               for(auto t : sys->fCollectorThreads)
                   collectorReceivedMessages += t->GetReceivedMessages();
               collectorReceivedMessages /= sys->fCollectorThreads.size();

               long builderEventsInQueue = 0;
               for(auto t : sys->fBuilderThreads)
                  builderEventsInQueue += t->GetEventsInQueue();
               long builderBuildedEvent = 0;
               for(auto t : sys->fBuilderThreads)
                  builderBuildedEvent += t->GetBuildedEvents();
               long builderDroppedEvent = 0;
               for(auto t : sys->fBuilderThreads)
                  builderDroppedEvent += t->GetDroppedEvents();
               long builderOldEvent = 0;
               for(auto t : sys->fBuilderThreads)
                  builderOldEvent += t->GetOldEvents();
               bool builderNotBuilding = false;
               for(auto t : sys->fBuilderThreads)
                  builderNotBuilding |= t->GetIsNotBuilding();
               bool builderDropping = false;
               for(auto t : sys->fBuilderThreads)
                  builderDropping |= t->GetIsDropping();

               //sys->fWorkerThread->fNEvent;
               //sys->fWorkerThread->fDropped;
               printf("\033[2J\nprinting monitoring data: press \'q<ENTER>\' to exit\n");
               printf("average being calculated on last %d seconds\n", nAvg);
               printf("----------------------------------------------------------------------------------------------------\n");
               printf("Buffers:\n");
               for(int i=0; i<sys->fPacketBuffer->GetNBuffers(); i++){
                  auto buff = sys->fPacketBuffer->GetBufferAt(i);
                  drawBar("Pkts", buff->GetOccupancy(), 1);
               }
               drawBar("BuildEvts", builderEventsInQueue, 20*sys->fBuilderThreads.size(), true);
               drawBar("Evts", sys->fEventBuffer->GetOccupancy(), 1);
               drawBar("Cals", sys->fCalibratedBuffer->GetOccupancy(), 1);
               printf("----------------------------------------------------------------------------------------------------\n");
               printf("Threads:\n");

               long DeltaCollectorNPackets = collectorNPackets-OldCollectorNPackets;
               long DeltaCollectorCorruptedPackets = collectorCorruptedPackets-OldCollectorCorruptedPackets;
               long DeltaCollectorDroppedPackets = collectorDroppedPackets-OldCollectorDroppedPackets;
               long DeltaBuilderBuildedEvent = builderBuildedEvent-OldBuilderBuildedEvent;
               long DeltaBuilderDroppedEvent = builderDroppedEvent-OldBuilderDroppedEvent;
               long DeltaBuilderOldEvent = builderOldEvent-OldBuilderOldEvent;

               drawBar("Msgs/s", collectorReceivedMessages, 200, true);
               drawBar("Pkts/s", DeltaCollectorNPackets, 1000000, true);
               drawBar("CorrPkts/s", DeltaCollectorCorruptedPackets, 1000, true);
               drawBar("DropPkts/s", DeltaCollectorDroppedPackets, 1000000, true);
               if(builderNotBuilding) printf("builder is not building\n");
               else printf("builder is building\n");
               if(builderDropping) printf("builder is dropping\n");
               else printf("builder is not dropping\n");
               drawBar("BuiltEvt/s", DeltaBuilderBuildedEvent, 2000, true);
               drawBar("DropEvt/s", DeltaBuilderDroppedEvent, 2000, true);
               drawBar("OldEvt/s", DeltaBuilderOldEvent, 2000, true);

               //update
               OldCollectorNPackets = collectorNPackets;
               OldCollectorCorruptedPackets = collectorCorruptedPackets;
               OldCollectorDroppedPackets = collectorDroppedPackets;
               OldBuilderBuildedEvent = builderBuildedEvent;
               OldBuilderDroppedEvent = builderDroppedEvent;
               OldBuilderOldEvent = builderOldEvent;

               //update max
               if(MaxCollectorNPackets < DeltaCollectorNPackets) MaxCollectorNPackets = DeltaCollectorNPackets;
               if(MaxCollectorCorruptedPackets < DeltaCollectorCorruptedPackets) MaxCollectorCorruptedPackets = DeltaCollectorCorruptedPackets;
               if(MaxCollectorDroppedPackets < DeltaCollectorDroppedPackets) MaxCollectorDroppedPackets = DeltaCollectorDroppedPackets;
               if(MaxBuilderBuildedEvent < DeltaBuilderBuildedEvent) MaxBuilderBuildedEvent = DeltaBuilderBuildedEvent;
               if(MaxBuilderDroppedEvent < DeltaBuilderDroppedEvent) MaxBuilderDroppedEvent = DeltaBuilderDroppedEvent;
               if(MaxBuilderOldEvent < DeltaBuilderOldEvent) MaxBuilderOldEvent = DeltaBuilderOldEvent;
               
               //update avgs
               AvgCollectorNPackets = AvgCollectorNPackets + (DeltaCollectorNPackets-AvgCollectorNPackets)*1./(nAvg+1);
               AvgCollectorCorruptedPackets = AvgCollectorCorruptedPackets + (DeltaCollectorCorruptedPackets-AvgCollectorCorruptedPackets)*1./(nAvg+1);
               AvgCollectorDroppedPackets = AvgCollectorDroppedPackets + (DeltaCollectorDroppedPackets-AvgCollectorDroppedPackets)*1./(nAvg+1);
               AvgBuilderBuildedEvent = AvgBuilderBuildedEvent + (DeltaBuilderBuildedEvent-AvgBuilderBuildedEvent)*1./(nAvg+1);
               AvgBuilderDroppedEvent = AvgBuilderDroppedEvent + (DeltaBuilderDroppedEvent-AvgBuilderDroppedEvent)*1./(nAvg+1);
               AvgBuilderOldEvent = AvgBuilderOldEvent + (DeltaBuilderOldEvent-AvgBuilderOldEvent)*1./(nAvg+1);
               nAvg++;

               fd_set fds;
               struct timeval tv;
               int retval;

               FD_ZERO(&fds);
               FD_SET(0, &fds);//stdin

               tv.tv_sec = 1;
               tv.tv_usec = 0;

               retval = select(1, &fds, NULL, NULL, &tv);
               if (retval == -1){
                  printf("error with select()\n");
                  exit(EXIT_FAILURE);
               } else if (retval){
                  //stdin commands
                  char c = getchar();
                  if(c=='q') done = true;
               }
               else{
                  // timeout
               }

            }

            //print averages and max
            printf("averages on %d seconds\n", nAvg);
            printf("Collected packets/s %lu avg %lu max\n", AvgCollectorNPackets, MaxCollectorNPackets);
            printf("Corrupted packets/s %lu avg %lu max\n", AvgCollectorCorruptedPackets, MaxCollectorCorruptedPackets);
            printf("Dropped packets/s %lu avg %lu max\n", AvgCollectorDroppedPackets, MaxCollectorDroppedPackets);
            printf("Received Events/s %lu avg %lu max\n", AvgBuilderBuildedEvent, MaxBuilderBuildedEvent);
            printf("Dropped Events/s %lu avg %lu max\n", AvgBuilderDroppedEvent, MaxBuilderDroppedEvent);
            printf("Old Events/s %lu avg %lu max\n", AvgBuilderOldEvent, MaxBuilderOldEvent);

         }
         if(option == 20)
         {
            for(auto c : *sys){
               int mscbhandle = c->GetMscbHandle();
               int status = mscb_reboot(mscbhandle, 20, 0, 0);
               // print something only in case of error
               if (status != MSCB_SUCCESS)
                  printf("Error: status = %d\n", status);

            }

         }
         if(option == 21)
         {
            int board;
            char cmd[128];

            printf("\nInsert Ascii command:\n");
            scanf("\n%128[^\n]", cmd);

            printf("\nLimit command execution\n0: WDB\n1: DCB\n2: Both\n");
            scanf("%d", &board);


            if(board>=0 && board <3){
               printf("Executing command \"%s\"\n", cmd);

               for(auto c : *sys){
                  for(auto b :*c)
                     if(b){
                        if(dynamic_cast<WDWDB*>(b) != nullptr){
                           if(board==0 || board ==2){
                              printf("on board %s\n", b->GetBoardName().c_str());
                              static_cast<WDWDB*>(b)->SendUDP(std::string(cmd));
                           }
                        }
                        if(dynamic_cast<WDDCB*>(b) != nullptr){
                           if(board==1 || board ==2){
                              printf("on board %s\n", b->GetBoardName().c_str());
                              static_cast<WDDCB*>(b)->SendUDP(std::string(cmd));
                           }
                        }
                     }

               }
            }

         }
         if(option == 22)
         {
            printf("Pedestal scan...\n");
            int n = 60;
            float down = -0.040;
            float up = 0.020;
            char group[256] = "";
            char group_limit;

            printf("number of points: ");
            scanf("%d", &n);
            printf("start threshold (V): ");
            scanf("%f", &down);
            printf("end threshold (V): ");
            scanf("%f", &up);
            printf("Limit to group (y/n): ");
            scanf(" %c", &group_limit);
            if(group_limit == 'y'){
               printf("group (empty for all WDB): ");
               scanf("%s",group);
            }

            printf("Pedestal for group \"%s\"\n", group);

            std::map<short, FILE*> files = CreateScalerFiles(sys, n, down, up, std::string(group));
            for(int i=0; i<n; i++) {
               float v = down + (up-down)*i/n;
               printf("%d/%d at %f V\n", i+1, n, v);
               SetThreshold(sys, v, std::string(group));
               SaveScalers(sys, files, v, std::string(group));
            }
            
            CloseScalerFile(files);
         }
         if(option == 23)
         {
            //list of WDB properties to generate
            std::vector<std::string> wdbProperties{ "FrontendGain",
                                                    "FrontendPzc",
                                                    "FrontendPzcLevel",
                                                    "TriggerLevel",
                                                    "TriggerGain",
                                                    "TriggerTdcMask",
                                                    "TriggerTdcOffset",
                                                    "DRSChannelTxEnable",
                                                    "ADCChannelTxEnable",
                                                    "TDCChannelTxEnable",
                                                    "TRGTxEnable",
                                                    "ZeroSuppressionEnable",
                                                    "SwZeroSuppressionPrescaling",
                                                    "SwZeroSuppressionClkROIStart",
                                                    "SwZeroSuppressionClkROIEnd",
                                                    "SwZeroSuppressionSignalROIStart",
                                                    "SwZeroSuppressionSignalROIEnd",
                                                    "SwZeroSuppressionRegionStart",
                                                    "SwZeroSuppressionRegionEnd",
                                                    "SwZeroSuppressionRebinFactor",
                                                    "SwZeroSuppressionRebinSignalThr",
                                                    "SwZeroSuppressionThr",
                                                    "SwZeroSuppressionRebinThr[0]",
                                                    "SwZeroSuppressionRebinThr[1]"
                                                  };

            //make map of boards belonging to a same property group
            std::map<std::string, std::vector<WDPosition>> groupMap;
            std::vector<WDPosition> wholeSystem;

            GenerateGroupMap(sys, groupMap, wholeSystem, BRD_TYPE_ID_WDB);//limit to WDB

            /*for(auto i: groupMap){
               printf("%s\n", i.first.c_str());
               for(auto j: i.second){
                  printf("\t%d-%d\n", j.fCrate, j.fSlot);
               }
            }*/

            FILE* f = GenerateSequencer(sys, wholeSystem, "System", wdbProperties);

            //helper functions
            std::stringstream s;
            //ApplySettings, trigger a reconfiguration and wait all stuff to be written
            CreateSequencerFunction(s, "ApplySettings");
            s << "ODBSET \"/Equipment/Trigger/Settings/Reload all\", y, 1" << std::endl;
            s << "WAIT seconds, 2" << std::endl;
            s << "WAIT ODBValue, \"/Equipment/Trigger/Variables/Config busy\", ==, y" << std::endl;
            CloseSequencerFunction(s);

            //ReloadAll, Load an ODB file with all WDAQ settings
            CreateSequencerFunction(s, "ReloadAll");
            s << "ODBLOAD \"$lib/WDAQSystem.odb\"" << std::endl;
            CloseSequencerFunction(s);

            WDBoard* trigger = sys->GetTriggerBoard();
            if(trigger){
               //DisableAllTriggers, make sure all TriggerEnable are set to 0
               CreateSequencerFunction(s, "DisableAllTriggers", true);
               CreateSequencerODBSet(s, trigger->GetCrate()->GetCrateName(), trigger->GetBoardName(), "TriggerEnable", "n");
               CloseSequencerFunction(s, true);

               //EnableTrigger, Enable a trigger and sets TriggerPrescaling and TriggerDelay
               CreateSequencerFunction(s, "EnableTrigger", true);
               CreateSequencerODBSet(s, trigger->GetCrate()->GetCrateName(), trigger->GetBoardName(), "TriggerEnable[$1]", "y");
               CreateSequencerODBSet(s, trigger->GetCrate()->GetCrateName(), trigger->GetBoardName(), "TriggerPrescaling[$1]", "$2");
               CreateSequencerODBSet(s, trigger->GetCrate()->GetCrateName(), trigger->GetBoardName(), "TriggerDelay[$1]", "$3");
               CloseSequencerFunction(s, true);
            }

            fputs(s.str().c_str(), f);
            CloseSequencer(f);

            for(auto group: groupMap){
               f = GenerateSequencer(sys, group.second, group.first, wdbProperties);
               CloseSequencer(f);
            }

            printf("Sequencer scripts generated!\n\n");
            printf("Please generate an ODB file for the whole WaveDAQ system:\n");
            printf("$ odbedit\n");
            printf("[local:Exp:S]/> cd Equipment/Trigger/Settings/WaveDAQ/\n");
            printf("[local:Exp:S]/> save WDAQSystem.odb\n\n");
            printf("then copy the files to Sequencer directory, typically:\n");
            printf("$ cp *.odb *.msl ~/online/sequencer/lib\n\n");

         }
         if(option == 24)
         {
            for(auto c : *sys){
               int mscbhandle = c->GetMscbHandle();
               int status = mscb_flash(mscbhandle, 20, 0, 0);
               // print something only in case of error
               if (status != MSCB_SUCCESS)
                  printf("Error: status = %d\n", status);
            }
         }
         if(option == 25)
         {
            FILE* f = fopen("WDAQTemperatures.log", "w");
            fprintf(f, "Time, ");
            for(auto c : *sys){
                  for(auto b :*c)
                     if(b){
                        if(dynamic_cast<WDWDB*>(b) != nullptr){
                           fprintf(f, "WDB%03d, ", b->GetSerialNumber());
                        }
                     }
            }
            fprintf(f, "\n");

            printf("logging temperatures, press 'q' to end\n");
            float min = -1;
            float max = -1;
            int minboard = 0;
            int maxboard = 0;
            int iLog = 0;

            bool done = false;
            while(!done){
               time_t rawtime;
               time (&rawtime);

               fprintf(f, "%.19s, ", ctime(&rawtime));

               for(auto c : *sys){
                     for(auto b :*c)
                        if(b){
                           if(dynamic_cast<WDWDB*>(b) != nullptr){
                              float temp = static_cast<WDWDB*>(b)->GetTemperatureDegree(true);
                              fprintf(f, "%.1f, ", temp);
                              if(min == -1 || min > temp){
                                 min = temp;
                                 minboard = b->GetSerialNumber();
                              }
                              if(max == -1 || max < temp){
                                 max = temp;
                                 maxboard = b->GetSerialNumber();
                              }
                           }
                        }
               }
               fprintf(f, "\n");
               iLog++;

               printf("logged %d entries: min %.1f deg WD%03d, max %.1f deg WD%03d\r", iLog, min, minboard, max, maxboard);

               fd_set fds;
               struct timeval tv;
               int retval;

               FD_ZERO(&fds);
               FD_SET(0, &fds);//stdin

               tv.tv_sec = 1;
               tv.tv_usec = 0;

               retval = select(1, &fds, NULL, NULL, &tv);
               if (retval == -1){
                  printf("error with select()\n");
                  exit(EXIT_FAILURE);
               } else if (retval){
                  //stdin commands
                  char c = getchar();
                  if(c=='q') done = true;
               }
               else{
                  // timeout
               }
            }

            fclose(f);
         }
      } while ( option == 0 ) ;
      /* end of the main loop on the options*/
   } while ( option >= 0);
   
   
   /* normal exit: close the VME crate */
   printf(" exiting ... \n");

}

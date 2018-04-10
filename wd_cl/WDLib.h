#include <string>
#include <vector>
#include <sstream>
#include <map>
#include "mscb.h"
#include "WDBLib.h"
#include "register_map_wd2.h"
#include "TCBLib.h"
#include "WDAQLib.h"

class WDCrate;
class WDSystem;

//convert a string in a vector of values
template <class T> std::vector<T> PropertyToArray(std::string property, std::ios_base::fmtflags f=(std::ios_base::fmtflags )0){
   std::vector<T> vect;
   vect.clear();
   std::stringstream ss;
   ss << property;

   std::string token;

   while(std::getline(ss, token, ',')) {
      std::stringstream token_ss(token);
      if(f) token_ss.setf(f, std::ios_base::basefield);
      T value;
      if(token_ss >> value){
         vect.push_back(value);
      }
      
   }

   return vect;
   
}

// --- WaveDAQ board --- basic wrapper class for wavedaq board
class WDBoard {
   friend class WDCrate;
   private:
      char fSlot;
      WDCrate *fCrate;
      std::map<std::string, std::string> fProperties;
      std::string fGroupName;

      //reserved Methods

   public:
      //Methods
      void AddProperty(std::string name, std::string val);
      std::string GetProperty(std::string name);

      //for derived classes
      virtual void Connect() { };  //called to init connection to the board
      virtual void Configure() { };//called to configure with properties
      virtual void SetSerdesTraining(bool state) { };//called to enable/disable serdes training pattern
      //virtual bool IsSerdesTraining();//check serdes training pattern status
      virtual void TrainSerdes() { };//called to train serdes
      virtual void Sync() { };     //send a synchronization pulse
      virtual void GoRun() { };    //start the board
      virtual void StopRun() { };  //stop the board
      virtual bool IsBusy() { return false; };   //check busy state

      //Setters
      void SetProperties(const std::map<std::string, std::string> &properties);
      void SetGroup(std::string groupname) { fGroupName = groupname; }

      //Getters
      char GetSlot(){ return fSlot; }
      WDCrate *GetCrate(){ return fCrate; }
      std::map<std::string, std::string> &GetProperties(){ return fProperties; }
      std::string GetGroup() { return fGroupName; };

      //Constructor
      //standalone
      WDBoard(){
         fSlot = -1;
      }
      //inside a crate
      WDBoard(WDCrate * crate, char slot);

      //Destructor
      virtual ~WDBoard() {}
};

// --- WaveDAQ crate --- basic crate functionalities 
class WDCrate {
   friend class WDSystem;
   
   private:
      WDBoard *fBoard[18];
      WDSystem *fSystem;
      std::string fMscbName;
      int fMscbHandle;

      //reserved Methods

   public:
      //Methods
      void AddBoard(WDBoard *board, int slot);
      bool HasBoardIn(int slot);
      void PowerOn();
      void PowerOff();
      bool IsPowered();

      //Getters
      WDBoard *GetBoardAt(int slot);
      const std::string GetMscbName(){ return fMscbName; };
      WDSystem *GetSystem() { return fSystem; }
      int GetMscbHandle() { return fMscbHandle; }

      //iterators
      WDBoard **begin() { return fBoard; }
      WDBoard **end() { return fBoard + 18; }

      //Constructor
      WDCrate(std::string mscbname = ""){
         for(int i=0; i<18; i++){
            fBoard[i] = 0;
         }
         if(mscbname.length()){
            fMscbName = mscbname;
            std::vector<char> cstr(fMscbName.c_str(), fMscbName.c_str() + fMscbName.size() + 1);
            fMscbHandle = mscb_init(&cstr[0], 0, "", 0);
            if(fMscbHandle < 0) {
               throw std::runtime_error("mscb exception");
            }
         }
      }

      //Destructor
      ~WDCrate(){
         if(fMscbHandle > 0) mscb_exit(fMscbHandle);
      }

};

// --- WaveDAQ system --- manage multicrate setup
class WDSystem {
   private:
      std::vector<WDCrate *> fCrate;
      int fTrgCrateId;
      std::map<std::string,std::map<std::string, std::string>> fGroupProperties;
      int fDAQServerPort;

      //reserved Methods
      void CreatePropertiesFromXml(WDBoard *board, MXML_NODE *board_node);

   public:
      //DAQ stuff
      DAQBuffer<WDAQPacketData> *fPacketBuffer;
      DAQBuffer<WDAQEvent> *fEventBuffer;
      DAQBuffer<WDAQEvent> *fCalibratedBuffer;
      WDAQPacketCollector *fCollectorThread;
      WDAQEventBuilder *fBuilderThread;
      WDAQWorker *fWorkerThread;
      WDAQEventWriter *fWriterThread;

      //Methods
      void AddCrate(WDCrate *crate);
      void CreateFromXml(std::string filepath);
      void GoRun();
      void StopRun();
      void PowerOn();
      void PowerOff();
      void Configure();
      void SetSerdesTraining(bool state);
      void TrainSerdes();
      void SpawnDAQ();
      void StopDAQ();

      //Iterator on crates
      WDCrate ** begin() { return &fCrate[0]; }
      WDCrate ** end() { return  &(fCrate.back()) + 1; }

      //Getters
      WDCrate *GetCrateAt(int crateid) { return fCrate.at(crateid); }
      WDCrate *GetTriggerCrate(){ return fCrate.at(fTrgCrateId); }
      WDBoard *GetTriggerBoard(){ return fCrate.at(fTrgCrateId)->GetBoardAt(17); }
      int GetTriggerCrateId(){ return fTrgCrateId; }
      unsigned long GetCrateSize() { return fCrate.size(); }
      std::map<std::string, std::string> &GetGroupProperties(std::string groupname){ return fGroupProperties[groupname]; }
      int GetDAQServerPort(){ return fDAQServerPort; }

      //Setters
      void SetTriggerCrateId(int triggercrateid){ fTrgCrateId = triggercrateid; }
      void SetGroupProperties(std::string groupname, std::map<std::string, std::string> &properties){ fGroupProperties[groupname] = properties; }
      void SetDAQServerPort(int port){ fDAQServerPort = port; }

      //Constructor
      WDSystem(){
         fTrgCrateId = -1;
         fPacketBuffer = nullptr;
         fCalibratedBuffer = nullptr;
         fEventBuffer = nullptr;
         fCollectorThread = nullptr;
         fBuilderThread = nullptr;
         fWriterThread = nullptr;
      }

      //Destructor
      ~WDSystem(){
         if(fPacketBuffer != nullptr) delete fPacketBuffer;
         if(fEventBuffer != nullptr) delete fEventBuffer;
         if(fCalibratedBuffer != nullptr) delete fCalibratedBuffer;
         if(fCollectorThread != nullptr) delete fCollectorThread;
         if(fBuilderThread != nullptr) delete fBuilderThread;
         if(fWorkerThread != nullptr) delete fWorkerThread;
         if(fWriterThread != nullptr) delete fWriterThread;
      }
   
};
 
// --- WaveDAQ WDB --- wrapper class for WDB
class WDWDB : public WDBoard, public WDB{
   private:
      void SetInCrate(){
         SetSendBlocked(true);
         SetTriggerEnable(true);
         SetTriggerFallingEdge(true);
         SetTriggerDelayEnable(false);
         SetTriggerCfgExtOr(true);
         SetTriggerCfgOr(0);
         SetTriggerCfgAnd(0);
         SetPatternTriggerSelect(WDB::cTriggerSchemeSimple);
         SetExtClkInSel(0);
         SetDaqClkSrcSel(0);
         SetLmkInputFreq(80);
         SetSendBlocked(false);
         SendControlRegisters();
         SetApplySettingsLmk(1);
         LmkSyncLocal();
         ReceiveStatusRegister(WD2_DRS_SAMPLE_FREQ_OFS);

      }

   
   public:
      void Connect(){

         WDB::Connect();
         ReceiveControlRegisters();
         ReceiveStatusRegisters();
         printf("WD number %d\n", GetSerialNumber());

      }
      void SetSerdesTraining(bool state){
         SetAdvTrgCtrl(0x00000430);
      }
      bool IsSerdesTraining(){
         return (GetAdvTrgCtrl() >>4) == 0x43;
         
      }
      void TrainSerdes(){

      }

      void Sync(){
         LmkSyncLocal();
      }

      void GoRun(){
         SetDaqNormal(true);
      }

      void StopRun(){
         SetDaqNormal(false);
      }

      bool IsBusy(){
         return GetWdbBusy(); 
      }

      void Configure(){
         //stop
         SetDaqSingle(false);
         SetDaqNormal(false);

         SetSendBlocked(true);
         //SetInterPacketDelay(0x80000);
         //SetInterPacketDelay(stoi(GetProperty("IPD")));

         //input
         SetFeMux(-1, WDB::cFeMuxInput);
         //gain
         std::vector<float> gain;
         try{
            gain = PropertyToArray<float>(GetProperty("FrontendGain")); 
         } catch (const std::runtime_error& ex){
            gain.clear();
         }
         if(gain.size() ==1){
            SetFeGain(-1, gain[0]);
         } else if(gain.size() == 16){
            for(int i=0; i<16; i++) SetFeGain(i, gain[i]);
         }
         //PZC
         std::vector<int> pzc;
         try{
            pzc = PropertyToArray<int>(GetProperty("FrontendPzc")); 
         } catch (const std::runtime_error& ex){
            pzc.clear();
         }
         if(pzc.size() ==1){
            if (pzc[0] > 0) {
               SetFePzc(-1, 1);
               SetDacPzcLevelN(pzc[0]-1); // 1...7 -> 0...6
            } else {
               SetFePzc(-1, 0);
               SetDacPzcLevelN(0);
            }
         } else if((pzc.size() - 1) < 16){
            SetDacPzcLevelN(pzc[0]-1);
               for(int i=0; i<16; i++)
                  SetFePzc(i, 0);
               for(unsigned long i=0; i<pzc.size(); i++){
                   SetFePzc(pzc[i+1], 1);
               }
         }
         //trigger discriminator level
         std::vector<float> trigger_level;
         try{
            trigger_level = PropertyToArray<float>(GetProperty("TriggerLevel")); 
         } catch (const std::runtime_error& ex){
            trigger_level.clear();
         }
         if(trigger_level.size() ==1){
            SetDacTriggerLevelV(-1, trigger_level[0]);
            SetTriggerShaperEnable(true);
            SetTriggerOutPulseLength(4);
         } else if(trigger_level.size() == 16){
            for(int i=0; i<16; i++) SetDacTriggerLevelV(i, trigger_level[i]);
            SetTriggerShaperEnable(true);
            SetTriggerOutPulseLength(4);
         }
         //Baseline Shift
         float baseline;
         try{
            baseline = std::stof(GetProperty("BaselineShift"));
         } catch (const std::runtime_error& ex){
            baseline = 1;
         }
         if(abs(baseline)<1) SetDacCalDcV(baseline); 

         //channel transmit
         //SetReadoutSrcSel(WDB::cReadoutSrcDrs);
         unsigned int tx_ena;
         try{
            tx_ena = stoul(GetProperty("ChannelTxEnable"), 0, 16); 
         } catch (const std::runtime_error& ex){
            tx_ena = 0x3FFFF;
         }
         SetDrsChTxEn(tx_ena);
         SetAdcChTxEn(tx_ena);
         SetTdcChTxEn(0);
         SetZeroSuprEn(false);
         SetTrgTxEn(0);
         SetSclTxEn(0);


         //timing reference
         std::string timingreference;
         try{
            timingreference = GetProperty("TimingReference");
         } catch (const std::runtime_error& ex){
            timingreference = "";
         }
         if(timingreference == "Off"){
            SetTimingReferenceSignal(WDB::cTimingReferenceOff);
         } else if (timingreference == "Sine"){
            SetTimingReferenceSignal(WDB::cTimingReferenceSine);
         } else if (timingreference == "Square"){
            SetTimingReferenceSignal(WDB::cTimingReferenceSquare);
         }

         //trigger algorithm
         char algorithm;
         try{
            algorithm = std::stoi(GetProperty("TriggerAlgorithm"));
         } catch (const std::runtime_error& ex){
            algorithm = 0;
         }
         SetAdvTrgCtrl(0x00000203 | ((algorithm & 0xF) << 4) );//TDCPolarity, FADCMODE, RUNMODE

         //trigger gain
         SetAdvTrgPedCfg(0x013E000A);
         std::vector<unsigned short> trigger_gain;
         try{
            trigger_gain = PropertyToArray<unsigned short>(GetProperty("TriggerGain"), std::ios_base::hex); 
         } catch (const std::runtime_error& ex){
            trigger_gain.clear();
         }
         if(trigger_gain.size() ==1){
            //extend to be 16 ch
            for(int i=0; i<15; i++) trigger_gain.push_back(trigger_gain[0]);
         }
         if(trigger_gain.size() == 16){
            for(int i=0; i<4; i++){
               unsigned int calib=0;
               for (int j=0 ; j<4 ; j++){
                  unsigned int temp = trigger_gain[i*4+j];
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

         //sampling frequency
         unsigned int freq;
         try{
            freq = std::stoi(GetProperty("SamplingFrequency"));
         } catch (const std::runtime_error& ex){
            freq = GetDrsSampleFreq();
         }
         SetDrsSampleFreq(freq);

         //set debug outputs
         std::string s_tx;
         std::string s_rx;
         try {
            s_tx = GetProperty("TxDebugSignal");
            s_rx = GetProperty("RxDebugSignal");
         } catch (const std::runtime_error& ex){
            //not defined
         }
         //decode according to missing Sync Local signal
         int tx, rx;
         if(s_tx == "Uart"){
            tx = WDB::cDbgUart; 
         } else if (s_tx == "Trigger"){
            tx = WDB::cDbgTrigger; 
         } else if (s_tx == "SoftTrigger"){
            tx = WDB::cDbgSoftTrigger; 
         } else if (s_tx == "ExtTrigger"){
            tx = WDB::cDbgExtTrigger; 
         } else if (s_tx == "SyncDirect"){
            tx = WDB::cDbgSyncDirect; 
         } else if (s_tx == "SyncSampled"){
            tx = WDB::cDbgSyncSampled; 
         } else if (s_tx == "SyncLogic"){
            tx = WDB::cDbgSyncSampled+1; 
         } else if (s_tx == "BusyLocal"){
            tx = WDB::cDbgBusyLocal+1; 
         } else if (s_tx == "BusyBackplane"){
            tx = WDB::cDbgBusyBackplane+1; 
         } else if (s_tx == "LMKInputClk"){
            tx = WDB::cDbgLMKInputClk+1; 
         } else if (s_tx == "ADCClk"){
            tx = WDB::cDbgADCClk+1; 
         } else if (s_tx == "DataClk"){
            tx = WDB::cDbgDataClk+1; 
         } else {
            tx = WDB::cDbgSyncSampled; 
         }
         if(s_rx == "Uart"){
            rx = WDB::cDbgUart; 
         } else if (s_rx == "Trigger"){
            rx = WDB::cDbgTrigger; 
         } else if (s_rx == "SoftTrigger"){
            rx = WDB::cDbgSoftTrigger; 
         } else if (s_rx == "ExtTrigger"){
            rx = WDB::cDbgExtTrigger; 
         } else if (s_rx == "SyncDirect"){
            rx = WDB::cDbgSyncDirect; 
         } else if (s_rx == "SyncSampled"){
            rx = WDB::cDbgSyncSampled; 
         } else if (s_rx == "SyncLogic"){
            rx = WDB::cDbgSyncSampled+1; 
         } else if (s_rx == "BusyLocal"){
            rx = WDB::cDbgBusyLocal+1; 
         } else if (s_rx == "BusyBackplane"){
            rx = WDB::cDbgBusyBackplane+1; 
         } else if (s_rx == "LMKInputClk"){
            rx = WDB::cDbgLMKInputClk+1; 
         } else if (s_rx == "ADCClk"){
            rx = WDB::cDbgADCClk+1; 
         } else if (s_rx == "DataClk"){
            rx = WDB::cDbgDataClk+1; 
         } else {
            rx = WDB::cDbgSyncSampled; 
         }
         SetMcxTxSigSel(tx);
         SetMcxRxSigSel(rx);

         SetSendBlocked(false);
         SendControlRegisters();

         //LMK and PLL configuration to be in crate
         SetInCrate();

         //Reset everything
         ResetAllPll();
         ResetTcbOserdesIf();
         ResetDrsControlFsm();

         //set destination port
         SetDestinationPort(GetCrate()->GetSystem()->GetDAQServerPort());

         //start
         SetDaqSingle(false);
         SetDaqNormal(true);

         //Read Status
         ReceiveStatusRegisters();

         //Load Calibration file
         if (!LoadVoltageCalibration(GetDrsSampleFreq(), "../wds/")) {
            printf("missing voltege calibration file\n");
         }
         if (!LoadTimeCalibration(GetDrsSampleFreq(), "../wds/")) {
            printf("missing time calibration file\n");
         }

      }

      WDWDB(std::string name, int verbose = 0) : WDBoard(), WDB(name, verbose) { };
      WDWDB(std::string name, WDCrate *crate, int slot, int verbose = 0) : WDBoard(crate, slot), WDB(name, verbose) {
         //try to connect only if the crate is powered
         if(crate->IsPowered()){
            Connect();
         }
      };

      ~WDWDB() { };
};

// --- WaveDAQ TCB --- wrapper class for TCB
class WDTCB : public WDBoard, public TCB{
   
   public:
      void Connect(){
         SetIDCode();
         SetNTRG();
         printf("connected to TCB with IDCode = %04x\n", fidcode);
      }

      void SetSerdesTraining(bool state){
         SetSerdesPattern(true);
      }
      bool IsSerdesTraining(){
         unsigned int val=0;
         GetRRUN( &val );
         return (val >> 9) & 0x1;

      }
      void TrainSerdes(){
         AutoCalibrateSerdes();

      }

      void Sync(){
         SWSync();
      }

      void GoRun(){
         TCB::GoRun();
      }

      void StopRun(){
         SWStop();
      }

      bool IsBusy(){
         return TCB::IsBusy();
      }

      void Configure(){
            //basic RRun
            u_int32_t rrun_config = 0x0000E014;  //masktrg, masksync, maskbusy, fadcmode, enable trg_bus
            //u_int32_t rrun_config = 0x00006014;  //masksync, maskbusy, fadcmode, enable trg_bus
            SetRRUN(&rrun_config);

            u_int32_t syncdly=0x1F;
            u_int32_t trgdly=0x1F;
            u_int32_t sprdly=0x1F;
            SetTRGBusIDLY(&syncdly, &trgdly, &sprdly);
            syncdly=0x10;
            trgdly=0x10;
            sprdly=0x10;
            SetTRGBusODLY(&syncdly, &trgdly, &sprdly);

            //trigger enable
            std::vector<int> trigger_enable;
            bool trg_ena[64];
            try{
               trigger_enable = PropertyToArray<int>(GetProperty("TriggerEnable")); 
            } catch (const std::runtime_error& ex){
               trigger_enable.clear();
            }
            for(int i=0; i<64; i++) trg_ena[i] = false;
            for(unsigned long i=0; i<trigger_enable.size(); i++) if(trigger_enable[i] >= 0 && trigger_enable[i] < 64) trg_ena[trigger_enable[i]] = true;
            SetTriggerEnable(trg_ena);

            //trigger prescaling
            std::vector<unsigned int> trigger_prescaling;
            unsigned int trg_presca[64];
            try{
               trigger_prescaling = PropertyToArray<unsigned int>(GetProperty("TriggerPrescaling")); 
            } catch (const std::runtime_error& ex){
               trigger_enable.clear();
            }
            for(int i=0; i<64; i++) trg_presca[i] = 0;
            if(trigger_enable.size() == trigger_prescaling.size()){
               for(unsigned long i=0; i<trigger_enable.size(); i++) if(trigger_enable[i] >= 0 && trigger_enable[i] < 64) trg_presca[trigger_enable[i]] = trigger_prescaling[i];
               SetPrescaling(trg_presca);
            }
            else printf("TriggerPrescaling field should be same size of TriggerEnable\n");

            //trigger algorithm
            unsigned int algorithm;
            try{
               algorithm = std::stoi(GetProperty("TriggerAlgorithm"));
            } catch (const std::runtime_error& ex){
               algorithm = 0;
            }
            SetRALGSEL(&algorithm);
            
            //Experiment-oriented parameters
            std::vector<unsigned int> parameters;
            try{
               parameters = PropertyToArray<unsigned int>(GetProperty("Parameters"), std::ios_base::hex); 
            } catch (const std::runtime_error& ex){
               parameters.clear();
            }
            //for(int i=0; i<parameters.size()-1; i+=2) SetParameter(parameters[i], parameters.data() + i + 1);
            //unsigned int thr = 0x100;
            //WriteReg(0x600, &thr);

            SetPacketizerCommandAt(0, STOP, 0, 0);
            SetPacketizerAutostart(true);
            SetPacketizerEnable(true);

            if((fidcode >>12) != 3)
               GoRun();

      }

      WDTCB(WDCrate *crate, int slot, int verbose = 0) : WDBoard(crate, slot), TCB(crate->GetMscbName().c_str(), 20, slot, verbose) {
         fh = crate->GetMscbHandle();
         //try to connect only if the crate is powered
         if(crate->IsPowered()){
            Connect();
         }
      };
      ~WDTCB() { };
};



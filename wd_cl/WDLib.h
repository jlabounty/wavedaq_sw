#include <string>
#include <vector>
#include <sstream>
#include <map>
#include "mscb.h"
#include "WDBLib.h"
#include "register_map_wd2.h"
#include "TCBLib.h"
#include "Properties.h"

class WDBoard;
class WDCrate;
class WDSystem;
class WDWDB;
class WDTCB;

#ifndef WDLIB_H
#define WDLIB_H
#include "WDAQLib.h"


// --- WaveDAQ board --- basic wrapper class for wavedaq board
class WDBoard {
   friend class WDCrate;
   private:
      std::string fBoardName;
      char fSlot;
      WDCrate *fCrate;
      PropertyGroup fProperties;
      std::string fGroupName;

      //reserved Methods

   public:
      //Methods
      void AddProperty(std::string name, std::string val);
      Property &GetProperty(std::string name);

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
      void SetProperties(const PropertyGroup &properties);
      void SetGroup(std::string groupname) { fGroupName = groupname; }

      //Getters
      char GetSlot(){ return fSlot; }
      WDCrate *GetCrate(){ return fCrate; }
      PropertyGroup &GetProperties(){ return fProperties; }
      std::string GetGroup() { return fGroupName; }
      std::string GetBoardName() {return fBoardName; }

      //Constructor
      //standalone
      WDBoard(std::string name="standalone"){
         fBoardName = name;
         fSlot = -1;
      }
      //inside a crate
      WDBoard(WDCrate * crate, char slot, std::string name="BoardXXX");

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
      long fCrateNumber;

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
         fCrateNumber = -1;
         fSystem = nullptr;

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

// --- WaveDAQ board position --- utility class to store board position in the system
class WDPosition {
   public:
      char fSlot;
      long fCrate;
   WDPosition (long crate=-1, char slot=-1){
      fSlot = slot;
      fCrate = crate;
   }
   WDPosition (const WDPosition &old_obj){
      fSlot = old_obj.fSlot;
      fCrate = old_obj.fCrate;
   }
   void Set (long crate, char slot){
      fSlot = slot;
      fCrate = crate;
   }
};

// --- WaveDAQ system --- manage multicrate setup
class WDSystem {
   friend class WDCrate;

   private:
      std::vector<WDCrate *> fCrate;
      int fTrgCrateId;
      std::map<std::string,PropertyGroup> fGroupProperties;
      PropertyGroup fDaqProperties;
      int fDAQServerPort;

      //reserved Methods
      void CreatePropertiesFromXml(WDBoard *board, MXML_NODE *board_node);

   public:
      std::map<std::string,WDPosition> fBoardMap;
      //DAQ stuff
      DAQBuffer<WDAQPacketData> *fPacketBuffer;
      DAQBuffer<WDAQEvent> *fEventBuffer;
      DAQBuffer<WDAQEvent> *fCalibratedBuffer;
      WDAQPacketCollector *fCollectorThread;
      WDAQEventBuilder *fBuilderThread;
      WDAQWorker *fWorkerThread;
      WDAQEventWriter *fWriterThread;
      std::vector<WDAQTCBReader*> fTCBReaderThreads;

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
      WDPosition &FindBoard(std::string name);

      //Iterator on crates
      WDCrate ** begin() { return &fCrate[0]; }
      WDCrate ** end() { return  &(fCrate.back()) + 1; }

      //Getters
      Property &GetDaqProperty(std::string name){ return fDaqProperties.at(name); };
      WDCrate *GetCrateAt(int crateid) { return fCrate.at(crateid); }
      WDCrate *GetTriggerCrate(){ return fCrate.at(fTrgCrateId); }
      WDBoard *GetTriggerBoard(){ return GetTriggerCrate()->GetBoardAt(17); }
      WDBoard *GetBoardAt(WDPosition &p) {return fCrate[p.fCrate]->GetBoardAt(p.fSlot);}
      int GetTriggerCrateId(){ return fTrgCrateId; }
      unsigned long GetCrateSize() { return fCrate.size(); }
      PropertyGroup &GetGroupProperties(std::string groupname){ return fGroupProperties.at(groupname); }
      int GetDAQServerPort(){ return fDAQServerPort; }

      //Setters
      void SetTriggerCrateId(int triggercrateid){ fTrgCrateId = triggercrateid; }
      void SetGroupProperties(std::string groupname, PropertyGroup &properties){ fGroupProperties[groupname] = properties; }
      void SetDaqProperties(PropertyGroup &properties){ fDaqProperties = properties; }
      void SetDAQServerPort(int port){ fDAQServerPort = port; }

      //Constructor
      WDSystem(){
         fTrgCrateId = -1;
         fDaqProperties.clear();
         fPacketBuffer = nullptr;
         fCalibratedBuffer = nullptr;
         fEventBuffer = nullptr;
         fCollectorThread = nullptr;
         fBuilderThread = nullptr;
         fWriterThread = nullptr;
         fTCBReaderThreads.clear();
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
         for(auto t: fTCBReaderThreads) delete t;
      }
   
};
 
// --- WaveDAQ WDB --- wrapper class for WDB
class WDWDB : public WDBoard, public WDB{
   private:
      void SetInCrate(){
         SetSendBlocked(true);
         /*SetTriggerEnable(true);
         SetTriggerFallingEdge(true);
         SetTriggerDelayEnable(false);
         SetTriggerCfgExtOr(true);
         SetTriggerCfgOr(0);
         SetTriggerCfgAnd(0);
         SetPatternTriggerSelect(WDB::cTriggerSchemeSimple);*/
         SetPatternTriggerEn(0);
         SetExtAsyncTriggerEn(1);
         SetExtTriggerOutEnable(0);
         SetTriggerOutPulseLength(4);
         SetExtClkInSel(0);
         SetDaqClkSrcSel(0);
         SetLmkInputFreq(80);
         SetSendBlocked(false);
         SendControlRegisters();
         SetApplySettingsLmk(1);
         LmkSyncLocal();
         ReceiveStatusRegister(WD2_DRS_SAMPLE_FREQ_REG);

         //Reset everything
         ResetAllPll();
         ResetTcbOserdesIf();
         ResetDrsControlFsm();

      }

   
   public:
      void Connect(){

         WDB::Connect();
         ReceiveControlRegisters();
         ReceiveStatusRegisters();
         printf("WD number %d\n", GetSerialNumber());

      }
      void SetSerdesTraining(bool state){
         unsigned int regbits = GetAdvTrgCtrl();
         SetAdvTrgCtrl((regbits&0xFFFF7FF) | 0x00000430);//MASKSYNC=0, DEBUG_CTRL=1, ALGSEL=3
         SetInCrate();
      }
      bool IsSerdesTraining(){
         return (((GetAdvTrgCtrl() >>4) ^ 0x43)|0x3C)==0xFF;//require MASKSYNC=0, DEBUG_CTRL=1, ALGSEL=3
         
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
         return GetDrsCtrlBusy(); 
      }

      void Configure(){
         //printf("configuring board %s\n", GetBoardName().c_str());
         //stop
         SetDaqSingle(false);
         SetDaqNormal(false);

         SetSendBlocked(true);
         long arraySize = 0;

         //printf("configuring IPD...\n");
         //interpacket delay
         unsigned int interpacket_delay;
         try{
            //interpacket_delay = stoul(GetProperty("IPD"), 0, 16); 
            interpacket_delay = GetProperty("IPD").GetUHex(); 
         } catch (const std::runtime_error& ex){
            interpacket_delay = 0;
         }
         if(interpacket_delay != 0){
            SetInterPkgDelay(interpacket_delay);
         }

         //printf("configuring FE...\n");
         //input
         SetFeMux(-1, WDB::cFeMuxInput);
         //gain
         //std::vector<float> gain;
         const float* gain;
         try{
            //gain = PropertyToArray<float>(GetProperty("FrontendGain")); 
            gain = GetProperty("FrontendGain").GetFloatVector(&arraySize);
         } catch (const std::runtime_error& ex){
            arraySize = -1;
         }
         if(arraySize == 1){
      if(gain[0] != 0.5 && gain[0] != 1 && gain[0] != 2.5 && gain[0] != 5 && gain[0] != 10 && gain[0] != 25 && gain[0] != 50 && gain[0] != 100)
        std::cout<<" ERROR invalid gain value, won't be applied! Valid gains are 0.5, 1, 2.5, 5, 10 25, 50, 100"<<std::endl;
        else
            SetFeGain(-1, gain[0]);
         } else if(arraySize == 16){
      for(int i=0; i<16; i++) { 
        if(gain[i] != 0.5 || gain[i] != 1 || gain[i] != 2.5 || gain[i] != 5 || gain[i] != 10 || gain[i] != 25 || gain[i] != 50 || gain[i] != 100)
          std::cout<<" ERROR invalid gain value, gain["<<i<<"] won't be applied! Valid gains are 0.5, 1, 2.5, 5, 10 25, 50, 100"<<std::endl;
        else
          SetFeGain(i, gain[i]);
      }// end for
         }
         else if(arraySize != -1)
      std::cout<<"Please provide 1 or 16 channel Frontend Gain values  "<<std::endl;


         //PZC
         const int* pzc;
         try{
            pzc = GetProperty("FrontendPzc").GetIntVector(&arraySize);
         } catch (const std::runtime_error& ex){
            arraySize = -1;
         }
         if(arraySize == 1){
      if (pzc[0] > 0) {
        SetFePzc(-1, 1);
        if(pzc[0] <1 || pzc[0] >7) std::cout<<" ERROR first PZC value must be between 1 and 7 included, the value won't be written"<<std::endl;
        else   SetDacPzcLevelN(pzc[0]-1);
      } else {
        SetFePzc(-1, 0);
        SetDacPzcLevelN(0);
      }
         } else if(arraySize == 17){
      for(unsigned long i=1; i<17; i++){
        if(pzc[i])
          SetFePzc(i-1, 1);
        else
          SetFePzc(i-1, 0);
      }
      if(pzc[0] <1 || pzc[0] >6) std::cout<<" ERROR first PZC value must be between 1 and 7 included, the value won't be written"<<std::endl;
      else   SetDacPzcLevelN(pzc[0]-1);
    }
    else if(arraySize != -1) {
      std::cout<<"Please provide 1 or 17 channel PZC values  "<<std::endl;
      std::cout<<"If 1 value is given then all the inputs have the same PZC levels  "<<std::endl;
      std::cout<<"If 17 then the first value is the level and the other 16 are the individual on/off flags  "<<std::endl;
      }


         //printf("configuring Trigger Level...\n");
         //trigger discriminator level
         const float* trigger_level;
         try{
            //trigger_level = PropertyToArray<float>(GetProperty("TriggerLevel")); 
            trigger_level = GetProperty("TriggerLevel").GetFloatVector(&arraySize); 
         } catch (const std::runtime_error& ex){
            arraySize = -1;
         }
         if(arraySize ==1){
            SetDacTriggerLevelV(-1, trigger_level[0]);
         } else if(arraySize == 16){
            for(int i=0; i<16; i++) SetDacTriggerLevelV(i, trigger_level[i]);
         }
         else if(arraySize != -1)
            std::cout<<"Please provide 1 or 16 trigger level values  "<<std::endl;


         //printf("configuring Polarity...\n");
         //channel trigger polarity
         unsigned int channel_polarity;
         try{
            //channel_polarity = stoul(GetProperty("ChannelPolarity"), 0, 16); 
            channel_polarity = GetProperty("ChannelPolarity").GetUHex();
         } catch (const std::runtime_error& ex){
            channel_polarity = 0xffff;
         }
         if(channel_polarity != -1){
            SetTrgSrcPolarity(channel_polarity);
         }

         //printf("configuring Baseline...\n");
         //Baseline Shift
         float baseline;
         try{
            //baseline = std::stof(GetProperty("BaselineShift"));
            baseline = GetProperty("BaselineShift").GetFloat();
         } catch (const std::runtime_error& ex){
            baseline = 1;
         }
         if(abs(baseline)<1) {
      SetRange(baseline);
    }

         //printf("configuring TX Enable...\n");
         //DRS channel transmit
         unsigned int drstx_ena;
         try{
            drstx_ena = GetProperty("DRSChannelTxEnable").GetUHex();
         } catch (const std::runtime_error& ex){
            drstx_ena = 0x3FFFF;
         }
         SetDrsChTxEn(drstx_ena);
         //ADC channel transmit
         unsigned int adctx_ena;
         try{
            adctx_ena = GetProperty("ADCChannelTxEnable").GetUHex();
         } catch (const std::runtime_error& ex){
            adctx_ena = 0;
         }
         SetAdcChTxEn(adctx_ena);
         //TDC channel transmit
         unsigned int tdctx_ena;
         try{
            tdctx_ena = GetProperty("TDCChannelTxEnable").GetUHex();
         } catch (const std::runtime_error& ex){
            tdctx_ena = 0;
         }
         SetTdcChTxEn(tdctx_ena);
         //TRG channel transmit
         unsigned int trgtx_ena;
         try{
            trgtx_ena = GetProperty("TRGChannelTxEnable").GetUHex();
         } catch (const std::runtime_error& ex){
            trgtx_ena = 0;
         }
    SetTrgTxEn(trgtx_ena);

         //scaler channel transmit
         unsigned int scaler_ena;
         try{
            scaler_ena = GetProperty("ScalerChannelTxEnable").GetUHex();
         } catch (const std::runtime_error& ex){
            scaler_ena = 0;
         }
         SetSclTxEn(scaler_ena);

         //zero suppression enable
    std::string zsuppr_ena;
         try{
            zsuppr_ena = GetProperty("ZeroSuppressionEnable").GetStringValue();
         } catch (const std::runtime_error& ex){
            zsuppr_ena = "false";
         }
    if(zsuppr_ena == "true") 
      SetZeroSuprEn(1);
    else
      SetZeroSuprEn(0);

         //printf("configuring Timing Reference...\n");
         //timing reference
         std::string timingreference;
         try{
            timingreference = GetProperty("TimingReference").GetStringValue();
         } catch (const std::runtime_error& ex){
            timingreference = "Off";
         }
         if(timingreference == "Off"){
            SetTimingReferenceSignal(WDB::cTimingReferenceOff);
         } else if (timingreference == "Sine"){
            SetTimingReferenceSignal(WDB::cTimingReferenceSine);
         } else if (timingreference == "Square"){
            SetTimingReferenceSignal(WDB::cTimingReferenceSquare);
         }

         //printf("configuring ALGSEL...\n");
         //trigger algorithm
         unsigned char algorithm;
         try{
            //algorithm = std::stoi(GetProperty("TriggerAlgorithm"));
            algorithm = GetProperty("TriggerAlgorithm").GetUInt();
         } catch (const std::runtime_error& ex){
            algorithm = 0;
         }
         SetAdvTrgCtrl(0x00000203 | ((algorithm & 0xF) << 4) );//TDCPolarity, FADCMODE, RUNMODE

         //printf("configuring Trigger Gain...\n");
         //trigger gain
         SetAdvTrgPedCfg(0x013E000A);
         //std::vector<unsigned short> trigger_gain;
         const int* trigger_gain;
         int trg_gain[16];
         try{
            //trigger_gain = PropertyToArray<unsigned short>(GetProperty("TriggerGain"), std::ios_base::hex); 
            trigger_gain = GetProperty("TriggerGain").GetIntVector(&arraySize);
         } catch (const std::runtime_error& ex){
            arraySize = -1;
         }
         if(arraySize ==1){
            for(int i=0; i<15; i++) trg_gain[i] = trigger_gain[0];
            arraySize = 16;
         } else if(arraySize ==16) {
            for(int i=0; i<15; i++) trg_gain[i] =  trigger_gain[i];
         }
         if(arraySize == 16){
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

         //printf("configuring TDC Channel Mask...\n");
         //TDC Mask ch
         unsigned int tdcmask;
         try{
            //tdcmask = stoul(GetProperty("TriggerTDCMask"), 0, 16);
            tdcmask = GetProperty("TriggerTDCMask").GetUHex();
         } catch (const std::runtime_error& ex){
            tdcmask = 65536;
         }
         if(tdcmask < 65536){
            SetAdvTrgTdcChMask(tdcmask);
         }

         //printf("configuring Debug...\n");
         //set debug outputs
         std::string s_tx;
         std::string s_rx;
         try {
            //s_tx = GetProperty("TxDebugSignal");
            //s_rx = GetProperty("RxDebugSignal");
            s_tx = GetProperty("TxDebugSignal").GetStringValue();
            s_rx = GetProperty("RxDebugSignal").GetStringValue();
         } catch (const std::runtime_error& ex){
            //not defined
            s_tx="";
            s_rx="";
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
            tx = WDB::cDbgSyncInternal; 
         } else if (s_tx == "BusyLocal"){
            tx = WDB::cDbgBusyLocal; 
         } else if (s_tx == "BusyBackplane"){
            tx = WDB::cDbgBusyBackplane; 
         } else if (s_tx == "LMKInputClk"){
            tx = WDB::cDbgLMKInputClk; 
         } else if (s_tx == "ADCClk"){
            tx = WDB::cDbgADCClk; 
         } else if (s_tx == "DataClk"){
            tx = WDB::cDbgDataClk; 
         } else if (s_tx == "LMK5Clk"){
            tx = WDB::cDbgLMK5Clk; 
         } else if (s_tx == "LMKChipSelect"){
            tx = WDB::cDbgLMKChipSelect; 
         } else {
            tx = WDB::cDbgSyncDirect; 
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
            rx = WDB::cDbgSyncInternal; 
         } else if (s_rx == "BusyLocal"){
            rx = WDB::cDbgBusyLocal; 
         } else if (s_rx == "BusyBackplane"){
            rx = WDB::cDbgBusyBackplane; 
         } else if (s_rx == "LMKInputClk"){
            rx = WDB::cDbgLMKInputClk; 
         } else if (s_rx == "ADCClk"){
            rx = WDB::cDbgADCClk; 
         } else if (s_rx == "DataClk"){
            rx = WDB::cDbgDataClk; 
         } else if (s_rx == "LMK5Clk"){
            rx = WDB::cDbgLMK5Clk; 
         } else if (s_rx == "LMKChipSelect"){
            rx = WDB::cDbgLMKChipSelect; 
         } else {
            rx = WDB::cDbgSyncSampled; 
         }
         SetMcxTxSigSel(tx);
         SetMcxRxSigSel(rx);


         //printf("configuring HV...\n");
         // Set HV if required
         // as a default it is not touched
         const float *cha_hv;
         try{
            cha_hv = GetProperty("ChannelHV").GetFloatVector(&arraySize); 
         } catch (const std::runtime_error& ex){
            arraySize = -1;
         }
         if(arraySize == 1){
            for(int i=0; i<16; i++) {
               SetHVTarget(i, cha_hv[0]);
            }
         }
         else if(arraySize == 16){
            for(int i=0; i<16; i++) {
               SetHVTarget(i, cha_hv[i]);
            }
         }
         else if(arraySize != -1)
            std::cout<<"Please provide 1 or 16 channel HV values  "<<std::endl;



         SetSendBlocked(false);
         SendControlRegisters();

         //printf("resetting PLLs...\n");
         //LMK and PLL configuration to be in crate
         SetInCrate();

         //printf("configuring Destination Port...\n");
         //set destination port
         SetDestinationPort(GetCrate()->GetSystem()->GetDAQServerPort());

         //start
         SetDaqSingle(false);
         SetDaqNormal(true);

         //Read Status
         ReceiveStatusRegisters();

         //printf("configuring Sampling Frequency...\n");
         //sampling frequency
         unsigned int freq;
         try{
            //freq = std::stoi(GetProperty("SamplingFrequency"));
            freq = GetProperty("SamplingFrequency").GetUInt();
         } catch (const std::runtime_error& ex){
            freq = GetDrsSampleFreqMhz();
         }
         SetDrsSampleFreq(freq);


         //Load Calibration file
         if (!LoadVoltageCalibration(GetDrsSampleFreqMhz(), "/home/git/wavedaq/software/wds/")) {
            printf("missing voltage calibration file\n");
         }
         if (!LoadTimeCalibration(GetDrsSampleFreqMhz(), "/home/git/wavedaq/software/wds/")) {
            printf("missing time calibration file\n");
         }

      }

      WDWDB(std::string name="WDXXX", int verbose = 0) : WDBoard(name), WDB(name, verbose) { };
      WDWDB(WDCrate *crate, int slot, std::string name="WDXXX", int verbose = 0) : WDBoard(crate, slot, name), WDB(name, verbose) {
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

         //reset stuff
         ResetIDLYCTRL();
         ResetSyncWaveformSerdes();
         ResetBufferLogic();
      }

      void SetSerdesTraining(bool state){
         //SetSerdesPattern(true);
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
         //printf("configuring board %s\n", GetBoardName().c_str());
         long arraySize = 0;
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

         //configure trigger enable and prescaling only on TCB_3
         if(( GetIDCode()>>12)==3){
            //trigger enable
            const unsigned int* trigger_enable;
            bool trg_ena[64];
            try{
               //trigger_enable = PropertyToArray<int>(GetProperty("TriggerEnable")); 
               trigger_enable = GetProperty("TriggerEnable").GetUIntVector(&arraySize);
            } catch (const std::runtime_error& ex){
               arraySize = 0;
               printf("cannot read enable\n");
            }
            for(int i=0; i<64; i++) trg_ena[i] = false;
            for(unsigned long i=0; i<arraySize; i++) if(trigger_enable[i] < 64) trg_ena[trigger_enable[i]] = true;
            long triggerEnableSize = arraySize;
            SetTriggerEnable(trg_ena);

            //trigger prescaling
            const unsigned int* trigger_prescaling;
            unsigned int trg_presca[64];
            try{
               //trigger_prescaling = PropertyToArray<unsigned int>(GetProperty("TriggerPrescaling")); 
               trigger_prescaling = GetProperty("TriggerPrescaling").GetUIntVector(&arraySize);
            } catch (const std::runtime_error& ex){
               arraySize = 0;
               printf("cannot read prescaling\n");
            }
            for(int i=0; i<64; i++) trg_presca[i] = 0;
            if(triggerEnableSize == arraySize){
               for(unsigned long i=0; i<arraySize; i++) if(trigger_enable[i] < 64) trg_presca[trigger_enable[i]] = trigger_prescaling[i];
               SetPrescaling(trg_presca);
            }
            else printf("TriggerPrescaling field (%ld) should be same size of TriggerEnable (%ld)\n",triggerEnableSize,arraySize);

         } else {
            //trigger algorithm on other TCB_X
            //unsigned int algorithm;
            unsigned int algorithm;
            try{
               //algorithm = std::stoi(GetProperty("TriggerAlgorithm"));
               algorithm = GetProperty("TriggerAlgorithm").GetUInt();
            } catch (const std::runtime_error& ex){
               algorithm = 0;
            }
            SetRALGSEL((unsigned int *)&algorithm);
         }

         //Experiment-oriented parameters
         //std::vector<unsigned int> parameters;
         const unsigned int* parameters;
         try{
            //parameters = PropertyToArray<unsigned int>(GetProperty("Parameters"), std::ios_base::hex); 
            parameters = GetProperty("Parameters").GetUHexVector(&arraySize);
         } catch (const std::runtime_error& ex){
            arraySize = -1;
         }
         for(int i=0; i<arraySize-1; i+=2){
            unsigned int val = parameters[i+1];
            SetParameter(parameters[i], &val);
         }
         //unsigned int thr = 0x100;
         //WriteReg(0x600, &thr);

         /*SetPacketizerCommandAt(0, COPY, REVECOU, BUFFERBASE);
         SetPacketizerCommandAt(1, COPY, RTOTTIME, BUFFERBASE+1);
         SetPacketizerCommandAt(2, COPY, RLIVETIME, BUFFERBASE+2);
         SetPacketizerCommandAt(3, DIRECT_WRITE, 0x00000001, BUFFERBASE+BUFFERSIZE);
         SetPacketizerCommandAt(4, STOP, 0, 0);
   */
         std::string readEnable;
         try{
            readEnable = GetProperty("ReadEnable").GetStringValue();
         } catch (const std::runtime_error& ex){
            readEnable = "false";
         }
         if(readEnable == "true"){
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

         //BUSY mask from external DAQ
         unsigned int extdaqbmask;
         try{
            extdaqbmask = GetProperty("ExtDAQBusyMask").GetUInt();
         } catch (const std::runtime_error& ex){
            extdaqbmask = 0;
         }
         // set the mask
         SetFMask(false, extdaqbmask==1);

         SetPacketizerAutostart(true);
         SetPacketizerEnable(true);

         if((fidcode >>12) != 3)
            GoRun();

    }

      WDTCB(WDCrate *crate, int slot, std::string name="TCBXXX", int verbose = 0) : WDBoard(crate, slot, name), TCB(crate->GetMscbName().c_str(), 20, slot, verbose) {
         fh = crate->GetMscbHandle();
         //try to connect only if the crate is powered
         if(crate->IsPowered()){
            Connect();
         }
      };
      ~WDTCB() { };
};
#endif


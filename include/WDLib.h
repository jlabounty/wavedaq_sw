#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <map>
#include "mscb.h"
#include "WDBLib.h"
#include "WDBReg.h"
#include "TCBLib.h"
#include "DCBLib.h"
#include "Properties.h"

#ifndef WDLIB_H
#define WDLIB_H
#include "WDAQLib.h"

//classes in this file
class WDBoard;
class WDCrate;
class WDSystem;
class WDWDB;
class WDTCB;
class WDDCB;

//forward declarations
class WDAQPacketData;
class WDAQEvent;

class WDAQPacketCollector;
class WDAQTCBReader;
class WDAQEventBuilder;
class WDAQWorker;
class WDAQEventWriter;

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
      void Configure(); //called to configure with properties

      //for derived classes
      virtual void Connect() { };  //called to init connection to the board
      virtual void ConfigurationStarted() { };//called when a configuration starts
      virtual void ConfigurationEnded() { };//called when a vonfiguration ends
      virtual void ConfigureProperty(const std::string &name, Property &property) { }; //called to configure a setting to a property
      virtual void SetSerdesTraining(bool state) { };//called to enable/disable serdes training pattern
      //virtual bool IsSerdesTraining();//check serdes training pattern status
      virtual void WaitClockLock() { };//lock until clock is locked
      virtual void TrainSerdes() { };//called to train serdes
      virtual void WaitSerdesTrainingFinish() { };//lock until serdes calibration is finished
      virtual bool IsSerdesGood() { return true; }; //checks that current serdes are compatible with expected
      virtual void Sync() { };     //send a synchronization pulse
      virtual void GoRun() { };    //start the board
      virtual void StopRun() { };  //stop the board
      virtual bool IsBusy() { return false; };   //check busy state
      virtual unsigned short GetSerialNumber() { return 0; }; //returns serial number used in data stream;
      virtual void WaitReady() { };

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
         fCrate = nullptr;
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
      std::string fCrateName;
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
      const std::string GetCrateName(){ return fCrateName; }
      const std::string GetMscbName(){ return fMscbName; }
      WDSystem *GetSystem() { return fSystem; }
      int GetMscbHandle() { return fMscbHandle; }
      long GetCrateNumber() { return fCrateNumber; }

      //iterators
      WDBoard **begin() { return fBoard; }
      WDBoard **end() { return fBoard + 18; }

      //Constructor
      WDCrate(std::string name="", std::string mscbname = ""){
         fCrateNumber = -1;
         fSystem = nullptr;

         fCrateName = name;

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
         } else {
            fMscbHandle = 0;
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
      long fTrgCrateId;
      long fDistributionCrateId;
      std::map<std::string,PropertyGroup> fGroupProperties;
      PropertyGroup fDaqProperties;
      std::vector<int> fDAQServerPorts;

      //DAQ System
      DAQSystem *fDaqSystem;

      //reserved Methods
      void CreatePropertiesFromXml(WDBoard *board, MXML_NODE *board_node);

   public:
      std::map<std::string,WDPosition> fBoardMap;
      //DAQ stuff TODO: remove in future
      DAQFanoutBuffer<WDAQPacketData> *fPacketBuffer;
      DAQBuffer<WDAQEvent> *fEventBuffer;
      DAQBuffer<WDAQEvent> *fCalibratedBuffer;
      std::vector<WDAQPacketCollector*> fCollectorThreads;
      std::vector<WDAQEventBuilder*> fBuilderThreads;
      std::vector<WDAQWorker*> fWorkerThreads;
      WDAQEventWriter *fWriterThread;
      std::vector<WDAQTCBReader*> fTCBReaderThreads;

      //Methods
      void AddCrate(WDCrate *crate);
      void CreateFromXml(std::string filepath);
      void Sync();
      void GoRun();
      void StopRun();
      void PowerOn();
      void PowerOff();
      void Connect();
      void Configure(bool wait = true);
      void WaitClockLock();
      void WaitReady();
      void SetSerdesTraining(bool state);
      void TrainSerdes(bool wait = true);
      void WaitSerdesTrainingFinish();
      bool IsSerdesGood();
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
      WDCrate *GetDistributionCrate(){ return fCrate.at(fDistributionCrateId); }
      WDBoard *GetDistributionBoard(){ return GetDistributionCrate()->GetBoardAt(16); }
      WDBoard *GetBoardAt(WDPosition &p) {return fCrate[p.fCrate]->GetBoardAt(p.fSlot);}
      long GetTriggerCrateId(){ return fTrgCrateId; }
      long GetDistributionCrateId(){ return fDistributionCrateId; }
      unsigned long GetCrateSize() { return fCrate.size(); }
      PropertyGroup &GetGroupProperties(std::string groupname){ return fGroupProperties.at(groupname); }
      int GetDAQServerPort(){
         static int distrib = 0;
         return fDAQServerPorts[(distrib++)%fDAQServerPorts.size()];
      }
      DAQSystem* GetDAQSystem(){ return fDaqSystem; }

      //Setters
      void SetTriggerCrateId(long crateid){ fTrgCrateId = crateid; }
      void SetDistributionCrateId(long crateid){ fDistributionCrateId = crateid; }
      void SetGroupProperties(std::string groupname, PropertyGroup &properties){ fGroupProperties[groupname] = properties; }
      void SetDaqProperties(PropertyGroup &properties){ fDaqProperties = properties; }
      void SetDaqProperty(std::string propertyname, std::string val){ fDaqProperties[propertyname].SetStringValue(val); }
      void AddDAQServerPort(int port){ fDAQServerPorts.push_back(port); }

      //Constructor
      WDSystem(){
         fTrgCrateId = -1;
         fDistributionCrateId = -1;
         fDaqProperties.clear();

         fDaqSystem = new DAQSystem();
      }

      //Destructor
      ~WDSystem(){
         delete fDaqSystem;
      }
   
};
 
// --- WaveDAQ WDB --- wrapper class for WDB
class WDWDB : public WDB, public WDBoard{
   private:
      void SetInCrate();
      void LoadCalibrationFiles();
   
   public:
      void Connect();
      void SetSerdesTraining(bool state);
      bool IsSerdesTraining();
      void TrainSerdes(){ } //No Serdes to train
      void WaitSerdesTrainingFinish() { };//No Serdes to train
      bool IsSerdesGood() { return true; }; //No Serdes to check
      void WaitClockLock();
      void WaitReady();

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
         ReceiveStatusRegister(GetPackagerBusyLoc());
         return GetPackagerBusy() | GetDrsCtrlBusy();
      }

      unsigned short GetSerialNumber() {
        return WDB::GetSerialNumber();    
      }

      //Configuration handlers
      void ConfigureProperty(const std::string &name, Property &property);
      void ConfigurationStarted();
      void ConfigurationEnded();

      void ConfigureFPD(Property &property);
      void ConfigureIPD(Property &property);
      void ConfigureMTU(Property &property);
      void ConfigureFrontendGain(Property &property);
      void ConfigureFrontendPzc(Property &property);
      void ConfigureFrontendPzcLevel(Property &property);
      void ConfigureTriggerLevel(Property &property);
      void ConfigureChannelPolarity(Property &property);
      void ConfigureChannelHV(Property &property);
      void ConfigureBaselineShift(Property &property);
      void ConfigureDRSChannelTxEnable(Property &property);
      void ConfigureADCChannelTxEnable(Property &property);
      void ConfigureTDCChannelTxEnable(Property &property);
      void ConfigureTRGTxEnable(Property &property);
      void ConfigureScalerTxEnable(Property &property);
      void ConfigureZeroSuppression(Property &property);
      void ConfigureTimingReference(Property &property);
      void ConfigureTriggerAlgorithm(Property &property);
      void ConfigureTriggerGain(Property &property);
      void ConfigureTriggerTdcMask(Property &property);
      void ConfigureTriggerTdcOffset(Property &property);
      void ConfigureTriggerPedestalThreshold(Property &property);
      void ConfigureTriggerPedestalDelay(Property &property);
      void ConfigureTriggerPedestalAddersel(Property &property);
      void ConfigureDebugSignal(int port, Property &property);
      void ConfigureSamplingFrequency(Property &property);
      void ConfigureForceEthernet(Property &property);


      WDWDB(std::string name="WDXXX", std::string netname="WDXXX", bool verbose = false) :  WDB(netname, verbose), WDBoard(name) { };
      WDWDB(WDCrate *crate, int slot, std::string name="WDXXX", std::string netname="WDXXX", bool verbose = false);

      ~WDWDB() { };
};

// --- WaveDAQ TCB --- wrapper class for TCB
class WDTCB : public TCB, public WDBoard {
   
   public:
      void Connect();

      void SetSerdesTraining(bool state);
      bool IsSerdesTraining();
      void TrainSerdes(){
         AutoCalibrateSerdes();
      }
      void WaitSerdesTrainingFinish();
      bool IsSerdesGood();
      void WaitClockLock();
      void WaitReady();

      void Sync(){
         SWSync();

         usleep(500000);//wait sync is applied
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

      unsigned short GetSerialNumber() {
        return (GetCrate()->GetCrateNumber() << 8) | GetSlot();    
      }

      //Configuration handlers
      void ConfigureProperty(const std::string &name, Property &property);
      void ConfigurationStarted();
      void ConfigurationEnded();

      void ConfigureTriggerEnable(Property &property);
      void ConfigureTriggerPrescaling(Property &property);
      void ConfigureTriggerDelay(Property &property);
      void ConfigureTriggerAlgorithm(Property &property);
      void ConfigureParameters(Property &property);
      void ConfigurePacketizer(Property &property);
      void ConfigureExtDAQ(Property &property);
      void ConfigureDetectorDelay(Property &property);
      void ConfigureTimeNarrowThreshold(Property &property);
      void ConfigureTimeWideThreshold(Property &property);
      void ConfigureXecHighThreshold(Property &property);
      void ConfigureXecLowThreshold(Property &property);
      void ConfigureXecVetoThreshold(Property &property);
      void ConfigureXecPatchId(Property &property);
      void ConfigureXecPatchThreshold(Property &property);
      void ConfigureXecPatchDelay(Property &property);
      void ConfigureXecAlfaThreshold(Property &property);
      void ConfigureXecAlfaScale(Property &property);
      void ConfigureXecMovingAverage(Property &property);
      void ConfigureTcMask(Property &property);
      void ConfigureTcMultiplicityThreshold(Property &property);
      void ConfigureTcCrateMergeThreshold(Property &property);
      void ConfigureTcSectorMergeThreshold(Property &property);
      void ConfigureCdchMask(Property &property);
      void ConfigureCdchUSMultiplicityThreshold(Property &property);
      void ConfigureCdchDSMultiplicityThreshold(Property &property);
       void ConfigureBgoThreshold(Property &property);
      void ConfigureBgoVetoThreshold(Property &property);
      void ConfigureBgoHitDelay(Property &property);
      void ConfigureBgoTriggerMask(Property &property);
      void ConfigureRdcThreshold(Property &property);
      void ConfigureRdcVetoThreshold(Property &property);
      void ConfigureRdcHitDelay(Property &property);
      void ConfigureRdcHitMask(Property &property);
      void ConfigureRdcTriggerMask(Property &property);
      void ConfigureCrcHitMask(Property &property);
      void ConfigureCrcPairMask(Property &property);
      void ConfigureNgenDelay(Property &property);
      void ConfigureNgenWidth(Property &property);
      void ConfigureNgenHighThreshold(Property &property);
      void ConfigureNgenLowThreshold(Property &property);
      void ConfigureFHitShaper(Property &property);
      void ConfigureFVetoShaper(Property &property);
      void ConfigureMargaritaMajVal(Property &property);
      void ConfigureMargaritaTrgDly(Property &property);
      void ConfigureMargaritaMask(Property &property);
      void ConfigureTofBarHitLogic(Property &property);
      void ConfigureTofHitLogic(Property &property);
      void ConfigureTofHitLogicAlternative(Property &property);
      void ConfigureTofXMask(Property &property);
      void ConfigureTofYMask(Property &property);
      void ConfigureFCaloMask(Property &property);
      void ConfigureFNeutronMask(Property &property);
      void ConfigureMatrixMask(Property &property);
      void ConfigureInterspillDly(Property &property);

  
      WDTCB(WDCrate *crate, int slot, std::string name="TCBXXX", int verbose = 0);
      ~WDTCB() { };
};

// --- WaveDAQ DCB --- wrapper class for DCB
class WDDCB : public DCB, public WDBoard {
   
   public:
      void Connect();//DCB connection are made in constructor, this only set CrateId and applies resets

      void SetSerdesTraining(bool state);
      bool IsSerdesTraining();
      void TrainSerdes();
      void WaitSerdesTrainingFinish();
      bool IsSerdesGood();
      void WaitClockLock();
      void WaitReady();

      void Sync(){
         //SetLmkSyncDcb(1);
         //SetTrSyncBpl(1);
         SendUDP("sync");

         usleep(500000);//wait sync is applied
      }

      void GoRun(){
      }

      void StopRun(){
      }

      bool IsBusy(){
         //TODO update register
         return GetDcbBusy();
      }

      unsigned short GetSerialNumber() {
        return DCB::GetSerialNumber();    
      }

      //Configuration handlers
      void ConfigureProperty(const std::string &name, Property &property);
      void ConfigureSyncDelay(Property &property);
      void ConfigurationStarted();
      void ConfigurationEnded();

      WDDCB(WDCrate *crate, int slot, std::string name="DCBXX", std::string netname="DCBXX", bool verbose = false);
      ~WDDCB() { };
};
#endif


#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <map>
#include "mscb.h"
#include "WDBLib.h"
#include "WDBReg.h"
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
      void Configure(); //called to configure with properties

      //for derived classes
      virtual void Connect() { };  //called to init connection to the board
      virtual void ConfigurationStarted() { };//called when a configuration starts
      virtual void ConfigurationEnded() { };//called when a vonfiguration ends
      virtual void ConfigureProperty(const std::string &name, Property &property) { }; //called to configure a setting to a property
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
      void SetDaqProperty(std::string propertyname, std::string val){ fDaqProperties[propertyname].SetStringValue(val); }
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
class WDWDB : public WDB, public WDBoard{
   private:
      void SetInCrate();

   
   public:
      void Connect();
      void SetSerdesTraining(bool state);
      bool IsSerdesTraining();
      void TrainSerdes(){ } //No Serdes to train

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

      //Configuration handlers
      void ConfigureProperty(const std::string &name, Property &property);
      void ConfigurationStarted();
      void ConfigurationEnded();

      void ConfigureFPD(Property &property);
      void ConfigureIPD(Property &property);
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


      WDWDB(std::string name="WDXXX", std::string netname="WDXXX", bool verbose = false) :  WDB(netname, verbose), WDBoard(name) { };
      WDWDB(WDCrate *crate, int slot, std::string name="WDXXX", std::string netname="WDXXX", bool verbose = false) : WDB(netname, verbose), WDBoard(crate, slot, name) {
         //try to connect only if the crate is powered
         if(crate->IsPowered()){
            Connect();
         }
      };

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
      void ConfigureTimeNarrowThreshold(Property &property);
      void ConfigureTimeWideThreshold(Property &property);
      void ConfigureXecHighThreshold(Property &property);
      void ConfigureXecLowThreshold(Property &property);
      void ConfigureXecVetoThreshold(Property &property);
      void ConfigureXecPatchId(Property &property);
      void ConfigureXecAlfaThreshold(Property &property);
      void ConfigureXecAlfaScale(Property &property);
      void ConfigureXecMovingAverage(Property &property);
      void ConfigureTcMask(Property &property);
      void ConfigureTcMultiplicityThreshold(Property &property);
      void ConfigureTcCrateMergeThreshold(Property &property);
      void ConfigureTcSectorMergeThreshold(Property &property);
      void ConfigureBgoThreshold(Property &property);
      void ConfigureBgoVetoThreshold(Property &property);
      void ConfigureBgoHitDelay(Property &property);
      void ConfigureBgoTriggerMask(Property &property);
      void ConfigureRdcThreshold(Property &property);
      void ConfigureRdcTriggerMask(Property &property);
      void ConfigureCrcHitMask(Property &property);
      void ConfigureCrcPairMask(Property &property);
      void ConfigureNgenDelay(Property &property);
      void ConfigureNgenWidth(Property &property);
      void ConfigureNgenHighThreshold(Property &property);
      void ConfigureNgenLowThreshold(Property &property);

      WDTCB(WDCrate *crate, int slot, std::string name="TCBXXX", int verbose = 0) : TCB(crate->GetMscbName().c_str(), 20, slot, verbose), WDBoard(crate, slot, name) {
         fh = crate->GetMscbHandle();

         //try to connect only if the crate is powered
         if(crate->IsPowered()){
            Connect();
         }
      };
      ~WDTCB() { };
};
#endif


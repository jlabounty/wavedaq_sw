#include "WDLib.h"
#include <vector>
#include <chrono>
#include <stdlib.h>
//debug - Thread that prints packets
class PacketDebug : public DAQThread{
   DAQBuffer<WDAQPacketData> *fSource;

   void Begin(){ };

   void Loop(){
      WDAQPacketData *ptr = nullptr;
      if(fSource->Try_pop(ptr)){
         printf("received packet\n");
         printf("\t Board:%d\n", ptr->mBoardId);
         printf("\t Crate:%d\n", ptr->mCrateId);
         printf("\t Slot:%d\n", ptr->mSlotId);
         printf("\t ADC:%d\n", ptr->mADC);
         printf("\t Channel:%d\n", ptr->mChannel);
         printf("\t DataType:%d\n", ptr->mDataType);
         printf("\t TxEnable:%x\n", ptr->mTxEnable);
         printf("\t ZeroSuppressionMask:%x\n", ptr->mZeroSuppressionMask);
         printf("\t Flags:%x\n", ptr->mFlags);
         printf("\t TriggerSource:%d\n", ptr->mTriggerSource);
         printf("\t BitsPerSample:%d\n", ptr->mBitsPerSample);
         printf("\t SamplesPerEventPerChannel:%d\n", ptr->mSamplesPerEventPerChannel);
         printf("\t PayloadLenght:%d\n", ptr->mPayloadLenght);
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

         delete ptr;
      }
   }
      

   void End() { };

   public:
   PacketDebug(DAQBuffer<WDAQPacketData> *source){
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
         printf("Got Event %d\n", ptr->mTriggerNumber);

         delete ptr;
      }
   }
   void End() { };

   public:
   EventDebug(DAQBuffer<WDAQEvent> *source){
      fSource = source;
   }
};



int main(int argc, char *argv[])
{
   int option;
   WDSystem *sys;
   if(argc!=2){
      printf("exectute %s wdsystem.xml\n", argv[0]);
      return -1;
   }

   sys = new WDSystem();
   sys->CreateFromXml(std::string(argv[1]));

   /* main loop on the options */
   do {
      printf("\n  --- options: \n");
      printf("[ 1]: configure system     \t \t  [ 2]: prepare to run       \n");
      printf("[ 3]: system start         \t \t  [ 4]: get busy             \n");
      printf("[ 5]: system stop          \t \t  [ 6]: system sync          \n");
      printf("[ 7]: turn on              \t \t  [ 8]: turn off             \n");
      printf("[ 9]: train serdes         \t \t  [10]: print serdes state   \n");
      printf("[11]: spawn daq            \t \t  [12]: stop daq             \n");
      printf("[13]: sync dly scan        \t \t  [14]: attach debug thread  \n");
      printf("[15]: draw system          \t \t   \n");
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
            sys->TrainSerdes();
	    usleep(50000);
            sys->Configure();
         }
         if(option == 3)
         {
            printf("starting system...\n");
            sys->GoRun();
         }
         if(option == 4)
         {
            WDBoard *triggerb = sys->GetTriggerBoard();
            if(triggerb->IsBusy()){
               printf("System is Busy\n");
            } else {
               printf("System is Not Busy\n");
            }
            for(auto c : *sys)
               for(auto b :*c)
                  if(b){
                     if(dynamic_cast<WDTCB*>(b) != nullptr){
                        unsigned int r;
                        dynamic_cast<WDTCB*>(b)->GetRRUN(&r);

                        if(r & 0x2)
                           printf("TCB %s is busy\n", c->GetMscbName().c_str());
                        else
                           printf("TCB %s is not busy\n", c->GetMscbName().c_str());
                     } else if(dynamic_cast<WDWDB*>(b) != nullptr){
                        if(b->IsBusy())
                           printf("WDB %s is busy\n", dynamic_cast<WDWDB*>(b)->GetName().c_str());
                        else
                           printf("WDB %s is not busy\n", dynamic_cast<WDWDB*>(b)->GetName().c_str());

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
            WDBoard *triggerb = sys->GetTriggerBoard();
            triggerb->Sync();
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
            sys->TrainSerdes();
         }
         if(option == 10)
         {
            for(auto c : *sys)
               for(auto b :*c)
                  if(b){
                     if(dynamic_cast<WDTCB*>(b) != nullptr){
                        printf("TCB %s\n", c->GetMscbName().c_str());
                        unsigned int val;
                        dynamic_cast<WDTCB*>(b)->GetAutoCalibrateBusy(&val);
                        printf("busy: %08x\n", val);
                        dynamic_cast<WDTCB*>(b)->GetAutoCalibrateFail(&val);
                        printf("fail: %08x\n", val);
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
            sys->SetSerdesTraining(true);
            unsigned int dly = 0x08;
            dynamic_cast<WDTCB*>(sys->GetTriggerBoard())->SetTRGBusIDLY(&dly, &dly, &dly);
            for(dly=0; dly<32; dly++){
               printf("testing dly %u\n", dly);
               dynamic_cast<WDTCB*>(sys->GetTriggerBoard())->SetTRGBusODLY(&dly, &dly, &dly);
               sys->GetTriggerBoard()->Sync();
               sys->TrainSerdes();
               std::this_thread::sleep_for(std::chrono::seconds(3));
               for(auto c : *sys)
                  for(auto b :*c)
                     if(b){
                        if(dynamic_cast<WDTCB*>(b) != nullptr){
                           unsigned int val;
                           dynamic_cast<WDTCB*>(b)->GetAutoCalibrateFail(&val);
                              unsigned int val1=0;
                              unsigned int val2=0;
                              unsigned int val3=0;
                              dynamic_cast<WDTCB*>(b)->ReadReg(0x355, &val1);
                              dynamic_cast<WDTCB*>(b)->ReadReg(0x356, &val2);
                              dynamic_cast<WDTCB*>(b)->ReadReg(0x357, &val3);
                              printf("%s %08x %08x maxslot=%d ", c->GetMscbName().c_str(), val2, val1, val3);
                           if(val & 0x80000000){
                              printf("fail: %08x", val);
                           }
                           printf("\n");
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
      } while ( option == 0 ) ;
      /* end of the main loop on the options*/
   } while ( option >= 0);
   
   
   /* normal exit: close the VME crate */
   printf(" exiting ... \n");

}

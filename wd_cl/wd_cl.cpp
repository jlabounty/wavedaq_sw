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
      printf("%f:%f|", value, valueMax);
   }
   printf("\n");
}


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
   sys->Connect();

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
      printf("[15]: draw system          \t \t  [16]: print firmware version\n");
      printf("[17]: update firmware      \t \t  [18]: clean buffer         \n");
      printf("[19]: show DAQ status      \t \t  [--]:                      \n");
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
            usleep(50000);
            sys->TrainSerdes();
            usleep(1000000);
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
            sys->Sync();
            WDBoard *triggerb = sys->GetTriggerBoard();
            printf("SYNC generated from board %s\n", triggerb->GetBoardName().c_str());
            for(auto c : *sys)
               for(auto b :*c)
                  if(b){
                     if(dynamic_cast<WDTCB*>(b) != nullptr){
                        u_int32_t val = 0;
                         dynamic_cast<WDTCB*>(b)->GetSyncWaveform(&val);
                         /*val =  val >>8;
                         if(val&0x80){
                            val = 0;
                         } else if(val&0x40){
                            val = 1;
                         } else if(val&0x20){
                            val = 2;
                         } else if(val&0x10){
                            val = 3;
                         } else if(val&0x8){
                            val = 4;
                         } else if(val&0x4){
                            val = 5;
                         } else if(val&0x2){
                            val = 6;
                         } else if(val&0x1){
                            val = 7;
                         }*/
                         printf("%s %d %04x\n", c->GetMscbName().c_str(), b->GetSlot(), val);
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
                        dynamic_cast<WDTCB*>(b)->GetAutoAlignDlys(&val);
                        printf("dlys: %08x\n", val);
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
               sys->Sync();
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
                        printf("WDB %s: %08x %08x\n", wdb->GetBoardName().c_str(), wdb->GetFwGitHashTag(), wdb->GetSwGitHashTag());
                        if(wdbFwHash){
                           if(wdbFwHash != wdb->GetFwGitHashTag())
                              difference = true;
                        } else wdbFwHash = wdb->GetFwGitHashTag();
                        if(wdbSwHash){
                           if(wdbSwHash != wdb->GetFwGitHashTag())
                              difference = true;
                        } else wdbSwHash = wdb->GetSwGitHashTag();
                     }
                     if(dynamic_cast<WDTCB*>(b) != nullptr){
                        WDTCB* tcb = static_cast<WDTCB*>(b);
                        unsigned int val;
                        tcb->GetCompilDate(&val);
                        
                        unsigned int *p;
                        switch(tcb->GetIDCode()>>12){
                        case 1:
                           printf("TCB1 %s: %08x\n", tcb->GetBoardName().c_str(), val);
                           p = &tcb1Date;
                           break;
                        case 2:
                           printf("TCB2 %s: %08x\n", tcb->GetBoardName().c_str(), val);
                           p = &tcb2Date;
                           break;
                        case 3:
                        default:
                           printf("TCB3 %s: %08x\n", tcb->GetBoardName().c_str(), val);
                           p = &tcb3Date;
                           break;
                        }

                        if(*p){
                           if(*p != val)
                              difference = true;
                        } else
                           *p = val;
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
            long OldBuilderBuildedEvent=sys->fBuilderThread->GetBuildedEvents();
            long OldBuilderDroppedEvent=sys->fBuilderThread->GetDroppedEvents();
            long OldBuilderOldEvent=sys->fBuilderThread->GetOldEvents();

            long AvgCollectorNPackets = 0;
            long AvgCollectorDroppedPackets = 0;
            long AvgBuilderBuildedEvent = 0;
            long AvgBuilderDroppedEvent = 0;
            long AvgBuilderOldEvent = 0;
            int nAvg = 0;

            long MaxCollectorNPackets = 0;
            long MaxCollectorDroppedPackets = 0;
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
               int  collectorReceivedMessages = 0;
               for(auto t : sys->fCollectorThreads)
                   collectorReceivedMessages += t->GetReceivedMessages();
               collectorReceivedMessages /= sys->fCollectorThreads.size();

               long builderEventsInQueue = sys->fBuilderThread->GetEventsInQueue();
               long builderBuildedEvent = sys->fBuilderThread->GetBuildedEvents();
               long builderDroppedEvent =  sys->fBuilderThread->GetDroppedEvents();
               long builderOldEvent = sys->fBuilderThread->GetOldEvents();
               bool builderNotBuilding = sys->fBuilderThread->GetIsNotBuilding();
               bool builderDropping = sys->fBuilderThread->GetIsDropping();

               //sys->fWorkerThread->fNEvent;
               //sys->fWorkerThread->fDropped;
               printf("\033[2J\nprinting monitoring data: press \'q<ENTER>\' to exit\n");
               printf("average being calculated on last %d seconds\n", nAvg);
               printf("----------------------------------------------------------------------------------------------------\n");
               printf("Buffers:\n");
               drawBar("Pkts", sys->fPacketBuffer->GetOccupancy(), 1);
               drawBar("BuildEvts", builderEventsInQueue, 20, true);
               drawBar("Evts", sys->fEventBuffer->GetOccupancy(), 1);
               drawBar("Cals", sys->fCalibratedBuffer->GetOccupancy(), 1);
               printf("----------------------------------------------------------------------------------------------------\n");
               printf("Threads:\n");

               long DeltaCollectorNPackets = collectorNPackets-OldCollectorNPackets;
               long DeltaCollectorDroppedPackets = collectorDroppedPackets-OldCollectorDroppedPackets;
               long DeltaBuilderBuildedEvent = builderBuildedEvent-OldBuilderBuildedEvent;
               long DeltaBuilderDroppedEvent = builderDroppedEvent-OldBuilderDroppedEvent;
               long DeltaBuilderOldEvent = builderOldEvent-OldBuilderOldEvent;

               drawBar("Msgs/s", collectorReceivedMessages, 200, true);
               drawBar("Pkts/s", DeltaCollectorNPackets, 1000000, true);
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
               OldCollectorDroppedPackets = collectorDroppedPackets;
               OldBuilderBuildedEvent = builderBuildedEvent;
               OldBuilderDroppedEvent = builderDroppedEvent;
               OldBuilderOldEvent = builderOldEvent;

               //update max
               if(MaxCollectorNPackets < DeltaCollectorNPackets) MaxCollectorNPackets = DeltaCollectorNPackets;
               if(MaxCollectorDroppedPackets < DeltaCollectorDroppedPackets) MaxCollectorDroppedPackets = DeltaCollectorDroppedPackets;
               if(MaxBuilderBuildedEvent < DeltaBuilderBuildedEvent) MaxBuilderBuildedEvent = DeltaBuilderBuildedEvent;
               if(MaxBuilderDroppedEvent < DeltaBuilderDroppedEvent) MaxBuilderDroppedEvent = DeltaBuilderDroppedEvent;
               if(MaxBuilderOldEvent < DeltaBuilderOldEvent) MaxBuilderOldEvent = DeltaBuilderOldEvent;
               
               //update avgs
               AvgCollectorNPackets = AvgCollectorNPackets + (DeltaCollectorNPackets-AvgCollectorNPackets)*1./(nAvg+1);
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
            printf("Dropped packets/s %lu avg %lu max\n", AvgCollectorDroppedPackets, MaxCollectorDroppedPackets);
            printf("Received Events/s %lu avg %lu max\n", AvgBuilderBuildedEvent, MaxBuilderBuildedEvent);
            printf("Dropped Events/s %lu avg %lu max\n", AvgBuilderDroppedEvent, MaxBuilderDroppedEvent);
            printf("Old Events/s %lu avg %lu max\n", AvgBuilderOldEvent, MaxBuilderOldEvent);


         }
      } while ( option == 0 ) ;
      /* end of the main loop on the options*/
   } while ( option >= 0);
   
   
   /* normal exit: close the VME crate */
   printf(" exiting ... \n");

}

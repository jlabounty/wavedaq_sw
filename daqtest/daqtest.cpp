/********************************************************************\

  Name:         daqtest.cpp
  Created by:   Marco Francesconi

  Contents:     Collects events 

\********************************************************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "strlcpy.h"
#include <string>
#include <iostream>
#include <sstream>
#include "mscb.h"
#include "mxml.h"
#include "WDBLib.h"
#include "TCBLib.h"

#include <iostream>
#include <exception>
#include <stdexcept>
#include <set>
#include <vector>
#include <map>

#define VERBOSITY 0
#define FREQUENCY_CHANGE
//#define FREQUENCY 1200

#define DLY 0x10

std::string wdb_list[]={
   "wd084",
   "wd085",
   "wd086",
   "wd087",
   "wd088",
   "wd089",
   "wd090",
   "wd091",
   "wd092",
   "wd093",
   "wd030",
   "wd031",
   "wd032",
   "wd033",
   "wd034",
   "wd035",
   "wd036",
   "wd037",
   "wd038",
   "wd039",
   "wd040",
   "wd041",
   "wd042",
   "wd043",
   "wd044",
   "wd045"
};

char tcb_list[] = "mscb195";


// WD board
std::map<std::string, WDB *> wdb;
WP * wp;
std::vector<WDEvent*> wde;
// TCB board
TCB* tcb;

int main(int argc, char** argv)
{
  int nr_of_events = 20;
  
  srand(time(NULL));
   // check arguments
   if (argc > 2 ) {
     printf("please use %s [event count]", argv[0]);
     return 1;
   }   
   if (argc == 2) {
     nr_of_events = atoi(argv[1]);
   }

   for(auto name : wdb_list)
      wdb[name] = new WDB(name, 3);
   // open mscb connection
   tcb = new TCB(tcb_list, 20, 17, 1);
   tcb->fh = mscb_init(tcb_list, 0, "", 0);
   tcb->SetIDCode();
   if(tcb->fnserdes!=16) {
      printf("Problem in communication with TCB....\n");
      return 1;
   }
   tcb->SetNTRG();

   tcb->fverbose = VERBOSITY;

   //WDB CONFIGURATION BEGIN

#ifdef FREQUENCY_CHANGE
   int freq;
      if (rand()%2){
         freq = 1800;
         printf("running ar 1800\n");
      } else {
         freq = 1200;
         printf("running ar 1200\n");
      }
#endif


   for(auto it: wdb){
      WDB* b= it.second;

      b->Connect();
      b->ReceiveControlRegisters();
      
      b->SetDaqSingle(false);
      b->SetDaqAuto(false);
      b->SetDaqNormal(false);
      
      b->SetSendBlocked(true); // update all control register together
      
      // general board settings
      //b->SetInterPkgDelay(0x60000);//default interpacket delay for 6 crate
      b->SetInterPkgDelay(0x60000);

      // turn on all boards by default, to be changed later in trigger_settings_changed
      b->SetDrsChTxEn(0x3FFFF);
      b->SetAdcChTxEn(0);
      b->SetTdcChTxEn(0);
      b->SetTrgTxEn(0);
      b->SetSclTxEn(0);
      b->SetZeroSuprEn(false);

      //debug ports
      b->SetLmk5ClkoutEn(1);
      b->SetMcxTxSigSel(WDB::cDbgSyncSampled);
      b->SetMcxRxSigSel(WDB::cDbgLMK5Clk);

      
      // b->SetReadoutSrcSel(WDB::cReadoutSrcDrs);
      b->SetFeMux(-1, WDB::cFeMuxInput);
      
      // reference clock settings
      b->SetTimingReferenceSignal(WDB::cTimingReferenceSquare);
      
      // External trigger settings
      b->SetPatternTriggerEn(0);
      b->SetExtAsyncTriggerEn(1);
      b->SetExtTriggerOutEnable(0);
      
      // Set backplane clock source 80 MHz
      b->SetExtClkInSel(0);
      b->SetDaqClkSrcSel(0);
      b->SetLmkInputFreq(80);
      
      // Set training pattern
      b->SetAdvTrgCtrl(0x00000431);
      
      // now send all changed registers in one packet
      b->SetSendBlocked(false);
      b->SendControlRegisters();
      
      // Sync LMK
      b->SetApplySettingsLmk(1);
      b->LmkSyncLocal();


#ifdef FREQUENCY_CHANGE
      b->SetDrsSampleFreq(freq);
#elif defined(FREQUENCY)
       b->SetDrsSampleFreq(FREQUENCY);
#endif

      b->ReceiveStatusRegister(WD2_DRS_SAMPLE_FREQ_REG);
      
      // Reset PLLs
      b->ResetAllPll();
      
      // Check if PLLs locked
      sleep_ms(100);
      b->GetPllLock(true);
      if (!b->GetLmkPllLock() || !b->GetDaqPllLock()) {
        return 1;
      }
      
      //Reset TCB OSerdes
      b->ResetTcbOserdesIf();
      
      // Reset DRS FSM
      b->ResetDrsControlFsm();
      b->ResetPackager();
      
      // start DRS which removes the busy
      b->SetDaqSingle(false);
      b->SetDaqAuto(false);
      b->SetDaqNormal(true);
      
      // read all status registers
      b->ReceiveStatusRegisters();
      
      //WDB CONFIGURATION END
      
      std::cout << std::endl << "========== Board Info ==========" << std::endl;
      b->PrintVersion();
   }

   //CONFIGURE WP
   std::vector<WDB*> wdbvec;
   for(auto it: wdb) wdbvec.push_back(it.second);
   wp = new WP(wdbvec, VERBOSITY, "");
   wp->SetAllCalib(true);
   wp->RequestAllBoards();
   for(auto it: wdb){
      WDB* b = it.second;
      b->SetDestinationPort(wp->GetServerPort());
      WDEvent *e = new WDEvent(b->GetSerialNumber());
      wde.push_back(e);
   }

   //Configure TCB
   //u_int32_t rrun_config = 0x0000C014;  //masktrg, masksync, fadcmode, enable trg_bus
   u_int32_t rrun_config = 0x0000E014;  //masktrg, masksync, maskbusy, fadcmode, enable trg_bus
   tcb->SetRRUN(&rrun_config);
   bool tr_en[64];
   for (int i=0; i<64; i++) tr_en[i]=false;
   tcb->SetTriggerEnable(tr_en);

   unsigned int trgodelay = DLY;
   unsigned int syncodelay = DLY;
   unsigned int sprodelay = DLY;

   tcb->SetTRGBusODLY(&syncodelay, &trgodelay, &sprodelay);

   //Begin of run

   tcb->SWStop();
   tcb->SWSync();
   for(auto it: wdb){
      it.second->ResetEventCounter();
   }
   wp->ResetStatistics();
   tcb->GoRun();   

   std::cout << "OK" << std::endl;
  
   FILE *f = fopen("run.txt", "w");
   fprintf(f, "%3d\n", wde.size());
   
   for( int evnt=0 ; evnt<nr_of_events ; evnt++)
   {
     //GENERATE TRIGGER
     u_int32_t trgforce = rand()%64;
     printf("\n\n===== Generated event %d / %d: generating trigger type %d =====\n", evnt+1, nr_of_events, trgforce);
     tcb->ForceTrigger(trgforce);

     //READ TCB
     u_int32_t evnumber;
     tcb->GetEventCounter(&evnumber);
     printf("TCB Event number %d\n", evnumber);
     u_int32_t trgtype;
     tcb->GetTriggerType(&trgtype);
     printf("TCB Trigger type: %d\n", trgtype&0x3F);

     //delay
     usleep(100000);

     //READ WDB
     bool ret = wp->GetLastEvent(100, wde);
     if(ret){
        printf("got WD event, return val=%d\n", ret);
        fprintf(f, "%4d %4d %2d: ", evnt, evnumber, trgtype&0x3F);
        for(auto e: wde){
           if(e->mTriggerNumber != evnumber) printf("!!!!!!! Problem -> !!!!!!");
           printf("WD %d event number %d  trigger type %d trigger cell0: %d trigger cell1: %d\n", e->mBoardId, e->mTriggerNumber, e->mTriggerType&0x3F, e->mTriggerCellDrs0, e->mTriggerCellDrs1);

           fprintf(f, "%3d %4d %2d %4d %4d, ",  e->mBoardId,  e->mTriggerNumber, e->mTriggerType&0x3F, e->mTriggerCellDrs0, e->mTriggerCellDrs1);
        }
        //fseek(f, -2, SEEK_CUR);
        fprintf(f, "\n");
     }
     
     tcb->GoRun();
     
   }

   fclose(f);

   return 0;
}

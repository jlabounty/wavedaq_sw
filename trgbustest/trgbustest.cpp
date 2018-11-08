/********************************************************************\

  Name:         trgbustest.cpp
  Created by:   Luca Galli

  Contents:     Generate Triggers in TCB and check trgbus comunication

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

#define TESTVALUE0 0xA5A5A5A5
#define TESTVALUE1 0xA5A5A5A5

// WD board
WDB * b;
WP * wp;
std::vector<WDEvent*> wde;
// TCB board
TCB* tcb;

int main(int argc, char** argv)
{
  srand(time(NULL));
   // check arguments
   if (argc != 3) {
     printf("please use %s wdXXX mscbYYY\n", argv[0]);
     return 1;
   }   

   b = new WDB(argv[1], 3);
   // open mscb connection
   tcb = new TCB(argv[2], 20, 17, 1);
   tcb->fh = mscb_init(argv[2], 0, "", 0);
   tcb->SetIDCode();
   if(tcb->fnserdes!=16) {
      printf("Problem in communication with TCB....\n");
      return 1;
   }
   tcb->SetNTRG();

   tcb->fverbose = 1;

   //WDB CONFIGURATION BEGIN

   b->Connect();
   b->ReceiveControlRegisters();
   
   b->SetDaqSingle(false);
   b->SetDaqAuto(false);
   b->SetDaqNormal(false);
   
   b->SetSendBlocked(true); // update all control register together
   
   // general board settings
   b->SetInterPkgDelay(0x60000);//default interpacket delay for 6 crate

   // turn on all boards by default, to be changed later in trigger_settings_changed
   b->SetDrsChTxEn(0x3FFFF);
   b->SetAdcChTxEn(0);
   b->SetTdcChTxEn(0);
   b->SetTrgTxEn(0);
   b->SetSclTxEn(0);
   b->SetZeroSuprEn(false);
   
   // b->SetReadoutSrcSel(WDB::cReadoutSrcDrs);
   b->SetFeMux(-1, WDB::cFeMuxInput);
   
   // reference clock settings
   b->SetTimingReferenceSignal(WDB::cTimingReferenceSquare);
   
   // External trigger settings
   b->SetTriggerTypeSel(1);
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

   //CONFIGURE WP
   std::vector<WDB*> wdbvec;
   wdbvec.push_back(b);
   wp = new WP(wdbvec, 3, "");
   wp->SetAllCalib(true);
   wp->RequestAllBoards();
   b->SetDestinationPort(wp->GetServerPort());
   WDEvent *e = new WDEvent(b->GetSerialNumber());
   wde.push_back(e);

   //Configure TCB
   u_int32_t rrun_config = 0x0000C014;  //masktrg, masksync, fadcmode, enable trg_bus
   tcb->SetRRUN(&rrun_config);
   bool tr_en[64];
   for (int i=0; i<64; i++) tr_en[i]=false;
   tcb->SetTriggerEnable(tr_en);

   //Begin of run

   tcb->SWStop();
   tcb->SWSync();
   b->ResetEventCounter();
   wp->ResetStatistics();
   tcb->GoRun();   

   std::cout << "OK" << std::endl;
   
   //MAIN LOOP
   bool flag=true;
   while(flag){

     //GENERATE TRIGGER
     u_int32_t trgforce = rand()%64;
     printf("generating trigger type %d\n", trgforce);
     tcb->ForceTrigger(trgforce);

     //READ TCB
     u_int32_t evnumber;
     tcb->GetEventCounter(&evnumber);
     printf("Event number %d\n", evnumber);
     u_int32_t trgtype;
     tcb->GetTriggerType(&trgtype);
     printf("Trigger type: %d\n", trgtype&0x3F);

     //delay
     usleep(1000000);

     //READ WDB
     bool ret = wp->GetLastEvent(100, wde);
     printf("got WD event, return val=%d\n", ret);
     printf("WD event number %d\n", wde[0]->mTriggerNumber);
     printf("WD trigger type %d\n", wde[0]->mTriggerType&0x3F);
     for(int icha = 0; icha<18; icha++) 
       printf("Channel %d trigger cell %d\n", icha,wde[0]->mTriggerCell[icha]);

     tcb->GoRun();

      
   }

   delete tcb;
   delete b;

   return 0;
}

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
  int nr_of_events = 20;
  
  srand(time(NULL));
   // check arguments
   if ( (argc < 3) || (argc > 4) ) {
     printf("please use %s wdXXX mscbYYY\n [event count]", argv[0]);
     return 1;
   }   
   if (argc == 4) {
     nr_of_events = atoi(argv[3]);
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
   int trg_cell_drs_a;
   int trg_cell_drs_b;
   int trg_cell_a_errors = 0;
   int trg_cell_b_errors = 0;
   int report_trg_cell_error;
   int offset_count[11] = {0,0,0,0,0,0,0,0,0,0,0};
   int offset_ratio;
   int bar_len;
   
//   bool flag=true;
//   while(flag){
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
     usleep(1000000);

     //READ WDB
     bool ret = wp->GetLastEvent(100, wde);
     printf("got WD event, return val=%d\n", ret);
     printf("WD event number %d\n", wde[0]->mTriggerNumber);
     printf("WD trigger type %d\n", wde[0]->mTriggerType&0x3F);

     //Consistency check
     report_trg_cell_error = 0;
     trg_cell_drs_a = wde[0]->mTriggerCell[16];
     for(int icha = 0; icha<8; icha++)
     {
       if( trg_cell_drs_a != wde[0]->mTriggerCell[icha] )
       {
         report_trg_cell_error = 1;
         trg_cell_a_errors++;
       }
     }
     trg_cell_drs_b = wde[0]->mTriggerCell[17];
     for(int icha = 8; icha<16; icha++)
     {
       if( trg_cell_drs_b != wde[0]->mTriggerCell[icha] )
       {
         report_trg_cell_error = 1;
         trg_cell_b_errors++;
       }
     }

     if( report_trg_cell_error )
     {
       printf("=====> Trigger cell consistency error !!! <=====\n");
//       printf("---------------------------\n");
//       for(int icha = 0; icha<8; icha++) 
//         printf("Channel %2d trigger cell %d\n", icha,wde[0]->mTriggerCell[icha]);
//       printf("Channel 16 trigger cell %d\n", wde[0]->mTriggerCell[16]);
//       printf("---------------------------\n");
//       for(int icha = 8; icha<16; icha++) 
//         printf("Channel %2d trigger cell %d\n", icha,wde[0]->mTriggerCell[icha]);
//       printf("Channel 17 trigger cell %d\n", wde[0]->mTriggerCell[17]);
//       printf("---------------------------\n");
     }
     else
     {
       //Store statistics
       
       //Offset (trg_cell_drs_b - trg_cell_drs_a) array
       //Index     0   1   2   3   4   5   6   7   8   9  10
       //Offset   -5  -4  -3  -2  -1   0   1   2   3   4   5
       offset_count[ trg_cell_drs_b - trg_cell_drs_a + 5 ]++;
     }
     printf("---------------------------\n");
     for(int icha = 0; icha<8; icha++) 
       printf("Channel %2d trigger cell %d\n", icha,wde[0]->mTriggerCell[icha]);
     printf("Channel 16 trigger cell %d\n", wde[0]->mTriggerCell[16]);
     printf("---------------------------\n");
     for(int icha = 8; icha<16; icha++) 
       printf("Channel %2d trigger cell %d\n", icha,wde[0]->mTriggerCell[icha]);
     printf("Channel 17 trigger cell %d\n", wde[0]->mTriggerCell[17]);
     printf("---------------------------\n");
     
     tcb->GoRun();
     
   }

   //Print statistics
   printf("\r\n\r\nTrigger Cell Offsets (DRS B - DRS A)\r\n");
   printf(        "====================================\r\n\r\n");
   printf(        "%d events captured\r\n", nr_of_events);
   if( trg_cell_a_errors || trg_cell_b_errors )
   {
     printf("Events ignored: %d %%   (%d)\r\n", (1000*(trg_cell_a_errors+trg_cell_b_errors)+5)/10, trg_cell_a_errors+trg_cell_b_errors);
     printf("(due to inconsistent stop cell values)\r\n");
   }
   printf("\r\n");
 
   for( int i=0 ; i<11 ; i++)
   {
     offset_ratio = (1000*offset_count[i]/nr_of_events+5)/10;
     //Show bar with 5% per item (max. 20 items)
     bar_len = offset_ratio/5;
     if( (bar_len == 0) && (offset_count[i] > 0) ) bar_len = 1;
     printf("Offset %2d:   ", i-5);
     for( int j=0 ; j<bar_len    ; j++) printf("#");
     for( int j=0 ; j<20-bar_len ; j++) printf(" ");
     printf("   %3d %%   (%d)\r\n", offset_ratio, offset_count[i]);
   }
   printf("\r\n");
   if( trg_cell_a_errors || trg_cell_b_errors )
   {
     printf("DRS A Trigger Cell Consistency Errors: %d\n", trg_cell_a_errors);
     printf("DRS B Trigger Cell Consistency Errors: %d\n", trg_cell_b_errors);
   }
   printf("\r\n");
   
   delete tcb;
   delete b;

   return 0;
}

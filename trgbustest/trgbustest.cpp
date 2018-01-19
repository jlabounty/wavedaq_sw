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
WDB * wdb;
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

   wdb = new WDB(argv[1], 3);
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

   wdb->Connect();

   //Configure WDB
   wdb->ReceiveControlRegisters();
   wdb->SetSendBlocked(true); // update all control register together
   //wdb->SetInterPacketDelay(0x40000);
   wdb->SetInterPacketDelay(0x80000);
   wdb->SetDrs0ChnTxEnable(0x1FF);
   wdb->SetDrs1ChnTxEnable(0x1FF);
   wdb->SetReadoutSrcSel(WDB::cReadoutSrcDrs);
   wdb->SetFeMux(-1, WDB::cFeMuxInput);
   wdb->SetTimingReferenceSignal(WDB::cTimingReferenceSine);
   wdb->SetDrsSampleFreq(1200);
   wdb->SetTriggerEnable(true);
   wdb->SetTriggerFallingEdge(true);
   wdb->SetTriggerDelayEnable(false);
   wdb->SetTriggerExternalOr(true);
   wdb->SetTriggerCfgOr(0);
   wdb->SetTriggerCfgAnd(0);
   wdb->SetTriggerLocalScheme(WDB::cTriggerSchemeSimple);
   wdb->SetExtClkInSel(0);
   wdb->SetDaqClkSrcSel(0);
   wdb->SetLmkInputFreq(80);
   wdb->ResetTcbOserdesIf();
   wdb->ResetTcbOserdesPll();
   wdb->SetTriggerShaperEnable(true);
   wdb->SetTriggerPulseLength(4);
   wdb->SetSendBlocked(false);
   wdb->SendControlRegisters();
   wdb->ResetDrsControlFsm();
   wdb->ResetAllPll();
   wdb->LoadVoltageCalibration(wdb->GetDrsSampleFreq(), "./");
   wdb->LoadTimeCalibration(wdb->GetDrsSampleFreq(), "./");
   wdb->SetDaqNormal(true);
   // read all status registers
   wdb->ReceiveStatusRegisters();
   
   std::cout << std::endl << "========== Board Info ==========" << std::endl;
   wdb->PrintVersion();

   //CONFIGURE WP
   std::vector<WDB*> wdbvec;
   wdbvec.push_back(wdb);
   wp = new WP(wdbvec, 3, "");
   wp->SetAllCalib(true);
   wp->RequestAllBoards();
   wdb->SetDestinationPort(wp->GetServerPort());
   WDEvent *e = new WDEvent(wdb->GetSerialNumber());
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
   wdb->ResetEventCounter();
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
     //usleep(100000);

     //READ WDB
     bool ret = wp->GetLastEvent(100, wde);
     printf("got WD event, return val=%d\n", ret);
     printf("WD event number %d\n", wde[0]->mTriggerNumber);
     printf("WD trigger type %d\n", wde[0]->mTriggerType&0x3F);

     //COMPARE


     tcb->GoRun();

     char c = getchar();
     if(c=='q') flag=false;
      
   }

   delete tcb;
   delete wdb;

   return 0;
}

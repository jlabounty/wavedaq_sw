/********************************************************************\

  Name:         serdestest.cpp
  Created by:   Luca Galli

  Contents:     Measure the serial link eye width between a WD board
                and a TC board. 

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
// TCB board transmitting
TCB* tcb_tx;
// TCB board receiving
TCB* tcb_rx;

int main(int argc, char** argv)
{
   // check arguments
   if (argc != 3) {
      printf("please use %s source destination\n", argv[0]);
      printf("source can be wdXXX or mscbYYY-slot\n");
      printf("destination has to be mscbZZZ-slot\n");
      return 1;
   }   

   if(strstr(argv[1], "wd")){
      printf("WDB as source");
      wdb = new WDB(argv[1], 1);
      wdb->Connect();
      wdb->ReceiveControlRegisters();

      wdb->SetSendBlocked(true); // update all control register together

      // Set backplane clock source 80 MHz
      wdb->SetExtClkInSel(0);
      wdb->SetDaqClkSrcSel(0);
      wdb->SetLmkInputFreq(80);

      // Reset Serdes Interface
      wdb->ResetTcbOserdesIf();
      wdb->ResetTcbOserdesPll();

      // Set training pattern
      wdb->SetAdvTrgCfg(0, 0x00000030);
      wdb->SetAdvTrgCfg(9, TESTVALUE0);
      wdb->SetAdvTrgCfg(10, TESTVALUE1);

      // now send all changed registers in one packet
      wdb->SetSendBlocked(false);
      wdb->SendControlRegisters();

      // Sync LMK
      wdb->ApplyLmkSettings();
      wdb->LmkSyncLocal();
      wdb->ReceiveStatusRegister(WD2_REG_DRS_SAMPLE_FREQ_OFS);

      // read all status registers
      wdb->ReceiveStatusRegisters();

      std::cout << std::endl << "========== Board Info ==========" << std::endl;
      wdb->PrintVersion();
   } else {
      char* nodename = strtok(argv[1], "-");
      if(nodename == NULL){
         printf("source can be wdXXX or mscbYYY-slot\n");
         return 1;
      }
      int slotnum = atoi(strtok(NULL, "-"));
      printf("TCB as source (node=%s slot=%d)\n", nodename, slotnum);

      tcb_tx = new TCB(nodename, 20, slotnum, 1);
      tcb_tx->fh = mscb_init(nodename, 0, "", 0);
      tcb_tx->SetIDCode();
      tcb_tx->fverbose = 1;
      tcb_tx->SetCheckWord(TESTVALUE0, TESTVALUE1);
      tcb_tx->ResetTransmitter();
      u_int32_t RRUNVal = 0x100; //DBGSerdes
      tcb_tx->SetRRUN(&RRUNVal);

   }

   char* nodename = strtok(argv[2], "-");
   if(nodename == NULL){
      printf("destination has to be mscbZZZ-slot\n");
      return 1;
   }
   int slotnum = atoi(strtok(NULL, "-"));

   // open mscb connection
   tcb_rx = new TCB(nodename, 20, slotnum,1);
   tcb_rx->fh = mscb_init(nodename, 0, "", 0);
   tcb_rx->SetIDCode();
   //if(tcb_rx->fnserdes!=16) {
   //   printf("Problem in communication with TCB....\n");
   //   return 1;
   //tcb_rx->fnserdes = 16;
   //}
   tcb_rx->fverbose = 1;

   
   std::cout << "OK" << std::endl;
   
   //perform scan
   u_int32_t dly[32];
   int bit[128];
   tcb_rx->SetCheckWord(TESTVALUE0, TESTVALUE1);
   std::cout << "TEST in progress, please wait...." << std::endl;
   tcb_rx->CalibrateSerdes(dly, bit);
   std::cout << "TEST in progress (with DCB), please wait...." << std::endl;
   tcb_rx->CalibrateDCBSerdes(dly, bit);

   std::cout << "DONE" << std::endl;

   return 0;
}

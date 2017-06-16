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

// WD board
WDB * wdb;
// TCB board
TCB* tcb;

int main(int argc, char** argv)
{
   // check arguments
   if (argc != 3) {
     printf("please use %s wdXXX mscbYYY\n", argv[0]);
     return 1;
   }   

   wdb = new WDB(argv[1], 1);
   // open mscb connection
   tcb = new TCB(argv[2], 20, 17,1);
   tcb->fh = mscb_init(argv[2], 0, "", 0);
   tcb->SetIDCode();
   tcb->fverbose = 1;

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
   
   std::cout << "OK" << std::endl;
   
   //perform scan
   u_int32_t dly[32];
   int bit[128];
   std::cout<<tcb->fverbose<<std::endl;
   tcb->CalibrateSerdes(dly, bit);

   std::cout << "OK" << std::endl;

   return 0;
}

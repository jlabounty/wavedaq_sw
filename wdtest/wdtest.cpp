//
//  wdtest.cpp
//  Test program to demonstrate error of SERDES reset
//
//  Stefan Ritt 04 Feb 2021
//


#include <iostream>
#include <string>

#include "WDBLib.h"
#include "DCBLib.h"

int main(int argc, const char *argv[]) {

   if (argc != 3) {
      std::cout << "Usage: wdtest <dcb> <slot>" << std::endl;
      return 0;
   }

   int slot = std::stod(argv[2]);

   DCB *dcb = new DCB(argv[1], false);
   dcb->Connect();

   WDB *b = new WDB(dcb, slot, false);
   b->Connect();

   // reboot WDB board
//   std::cout << "Rebooting WDB in slot " << slot << " ..." << std::flush;
//   b->ReconfigureFpga();
//   sleep_ms(10000);
//   std::cout << " ok" << std::endl;

   b->ReceiveStatusRegisters();
   b->ReceiveControlRegisters();

   // enable SERDES
   b->SetEthComEn(0);
   b->SetSerdesComEn(1);

   // set clock select to backplane
   b->SetExtClkFreq(80);
   b->SetDaqClkSrcSel(0);

   // wait for clock switch to be finished
   for (int j=0 ; j<40 ; j++) {
      int l = b->GetExtClkActive(true);
      std::cout << j*100 << "ms: " << b->GetAddr() << " Ext_Clk_Active=" << l << std::endl;
      if (l > 0)
         break;

      sleep_ms(100);
   }

   // wait until PLLs have locked
   b->WaitPllLock();

   // issue SYNC pulse on backplane
   dcb->SendReceiveUDP("sync");

   b->ResetAdc();
   std::cout << "Reset ADC of " << b->GetName() << std::endl;

   // reset serdes in DCB
   dcb->ResetSerdes(0);
   std::cout << "Reset serdes of " << dcb->GetName() << std::endl;

   std::cout << dcb->SendReceiveUDP("sdstat");
   sleep_ms(1000);
   std::cout << dcb->SendReceiveUDP("sdstat");

//   // check for PLL lock
//   int l = b->GetPllLock(true);
//   std::cout << "PLL Lock=0x" << std::hex << l << std::endl;
//
//   // reset SERDES on DCB
//   std::cout << "Reset SERDES" << std::endl;
//   dcb->ResetSerdes();
//
//   // print SERDES status
//   auto s = dcb->SendReceiveUDP("sdstat");
//   std::cout << std::endl << s << std::endl;

   return 0;
}

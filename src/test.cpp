//
//  test.cpp
//  Test program for WDBLib2.cpp
//


#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <thread>
#include <random>
#include <execinfo.h>
#include <fstream>

#include "WDBLib2.h"
#include "DCBLib.h"

/*-- Globals -------------------------------------------------------*/

int main(int argc, const char *argv[])
{
   std::vector<WDB *> wdb;

   DCB *dcb = new DCB("DCB01");
   dcb->Connect();
   dcb->PrintVersion();

   /*
   auto d = dcb->GetSyncDelay();
   dcb->SetSyncDelay(3);
   d = dcb->GetSyncDelay();
   */

   dcb->SetDistributorClkSrcSel(0);
   dcb->SetDistributorClkSrcSel(1);

    wdb.push_back(new WDB("WD134"));
   wdb.push_back(new WDB("WD162"));

   // connect to all WDB and retrieve registers
   for (auto &b: wdb) {
      std::cout << "Connect to " << b->GetName() << " ... " << std::flush;
      try {
            b->Connect();
            b->ReceiveStatusRegisters();
            b->ReceiveControlRegisters();
            std::cout << std::endl << "========== Board Info ==========" << std::endl;
            b->PrintVersion();

      } catch (std::runtime_error &e) {
         std::cout << std::endl;
         std::cout << e.what() << std::endl;
         std::cout << "Aborting." << std::endl;
         return 1;
      }
      std::cout << "OK" << std::endl;
      std::cout << std::endl << std::endl;
   }

   return 0;
}

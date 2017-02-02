//
//  wdbtest.cpp
//  Test program for WDBLib.cpp
//
//  Stefan Ritt 31 Jan 2017
//


#include <iostream>
#include <string>
#include <vector>

#include "WDBLib.h"

/*-- Globals -------------------------------------------------------*/

std::vector<std::string> wdbName = { "wd027" };

/*------------------------------------------------------------------*/


int main(int argc, const char * argv[])
{
   std::vector<WDB*> wdb;

   for (auto &s: wdbName) {
      WDB *w = new WDB(s);
      wdb.push_back(w);
      
      std::cout << "Connect to " << w->getName() << " ..." << std::flush;
      try {
         w->Connect();
         w->ReceiveControlRegisters();
         w->ReceiveStatusRegisters();
      } catch (std::runtime_error &e) {
         std::cout << std::endl;
         std::cout << e.what() << std::endl;
         std::cout << "Aborting." << std::endl;
         return -1;
      }
   }

   std::cout << wdb[0]->GetFwBuild() << std::endl;
   std::cout << wdb[0]->GetHwVersion() << std::endl;
   
   return 0;
}

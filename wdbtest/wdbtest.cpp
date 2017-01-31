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

using namespace std;

/*-- Globals -------------------------------------------------------*/

vector<string> wdbName = { "wd027" };

/*------------------------------------------------------------------*/


int main(int argc, const char * argv[])
{
   vector<WDB*> wdb;

   for (auto &s: wdbName) {
      WDB *w = new WDB(s);
      wdb.push_back(w);
      
      cout << "Connect to " << w->getName() << " ..." << std::flush;
      try {
         w->Connect();
      } catch (std::runtime_error &e) {
         cout << endl;
         cout << e.what() << ", aborting." << endl;
         return -1;
      }
   }

   return 0;
}

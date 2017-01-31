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
      wdb.push_back(new WDB(s));
   }

   cout << wdb[0]->getName() << endl;
   return 0;
}

//
//  wdbtest.cpp
//  Test program for WDBLib.cpp
//
//  Stefan Ritt 31 Jan 2017
//


#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>

#include "WDBLib.h"

/*-- Globals -------------------------------------------------------*/

std::vector<std::string> wdbName = { "wd094" };

typedef struct {
   bool demoMode;
   int  serverPort;
   bool verbose;
   std::vector<WDB*> wdb;
} GLOBALS;

/*------------------------------------------------------------------*/

void showUsage(std::string name)
{
   if (name.find("/") != std::string::npos)
      name = name.substr(name.rfind("/")+1); // strip path
      
   std::cerr << "usage: " << name << " [options] [-w <address> [-w <address> ...]]" << std::endl;
   std::cerr << "valud options:" << std::endl;
   std::cerr << "  -h              Show this help" << std::endl;
   std::cerr << "  -d              Demo mode" << std::endl;
   std::cerr << "  -p              HTTP server port" << std::endl;
   std::cerr << "  -w <address>    Internet address(es) of WaveDREAM board(s)" << std::endl;
   std::cerr << "  -v              Print extra debugging information (verbose)" << std::endl;
}

int main(int argc, const char * argv[])
{
   GLOBALS gl;
   
   // parse command line parameters
   if (argc < 2) {
      showUsage(argv[0]);
      return 1;
   }
   
   for (int i=1 ; i<argc ; i++) {
      std::string arg = argv[i];
      if (arg == "-h" || arg == "-help" || arg == "--help") {
         showUsage(argv[0]);
         return 0;
      } else if (arg == "-d")
         gl.demoMode = true;
      
      else if (arg == "-p")
         gl.serverPort = std::stoi(argv[++i]);
      
      else if (arg == "-v")
         gl.verbose = true;
      
      else if (arg == "-w") {
         
         if (i+1 == argc) {
            showUsage(argv[0]);
            return 0;
         }
         std::string b = argv[i+1];
         if (isdigit(b.c_str()[0]) && b.find(".") == std::string::npos) {
            if (b.find("-") != std::string::npos) {
               int i1 = std::stoi(b);
               int i2 = std::stoi(b.substr(b.find("-")+1));
               if (i1 >= 0 && i1 < 1000 && i2>0 && i2<1000) {
                  for (int j=i1 ; j<=i2; j++) {
                     std::ostringstream name;
                     name << "wd" << std::setfill('0') << std::setw(3) << j;
                     gl.wdb.push_back(new WDB(name.str()));
                  }
               } else {
                  std::cerr << "invalid argument \"-w " << b << "\"" << std::endl;
                  return 1;
               }
            } else {
               if (argc > i+1 && isdigit(argv[i+1][0])) {
                  while (argc > i+1 && isdigit(argv[i+1][0])) {
                     std::ostringstream name;
                     name << "wd" << std::setfill('0') << std::setw(3) << atoi(argv[i+1]);
                     gl.wdb.push_back(new WDB(name.str()));
                     i++;
                  }
                  continue;
               }
            }
         } else
            gl.wdb.push_back(new WDB(b));
         i++;
      } else {
         showUsage(argv[0]);
         return 1;
      }
   }
   
   if (gl.demoMode) {
      gl.wdb.clear();
      gl.wdb.push_back(new WDB("demo"));
   }

   if (gl.wdb.size() == 0) {
      std::cerr << "You have to specify at least one WaveDREAM board via the \"-w\" option." << std::endl;
      return 1;
   }
   
   for (auto &b: gl.wdb) {
      std::cout << "Connect to " << b->getName() << " ..." << std::flush;
      try {
         if (!gl.demoMode) {
            b->SetDebug(gl.verbose);
            b->Connect();
            b->ReceiveControlRegisters();
            b->ReceiveStatusRegisters();
            if (gl.verbose)
               b->PrintVersion();
         }
      } catch (std::runtime_error &e) {
         std::cout << std::endl;
         std::cout << e.what() << std::endl;
         std::cout << "Aborting." << std::endl;
         return 1;
      }
   }

   try {
      std::vector<unsigned long> s;
      do {
         gl.wdb[0]->GetScalers(s);
         std::cout << "S: " << s[0] << std::endl;
         
         std::cout << "T: " << gl.wdb[0]->GetTemperature() << std::endl;
         
         sleep(1000);
      } while (1);
      
   } catch  (std::runtime_error &e) {
      std::cout << std::endl;
      std::cout << e.what() << std::endl;
      std::cout << "Aborting." << std::endl;
      return 1;
   }
   
   return 0;
}

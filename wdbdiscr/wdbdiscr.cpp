/********************************************************************\

  Name:         daqtest.cpp
  Created by:   Marco Francesconi

  Contents:     Collects events 

\********************************************************************/

#include <stdexcept>
#include "WDBLib.h"

using namespace std;

std::string wdbs[]={
   //MPPC08
   //"wd100",
   //"wd101",
   //"wd102",
   //"wd103",
   //"wd104",
   //"wd105",
   //"wd106",
   //"wd107",
   //"wd108",
   //"wd109",
   //"wd079",
   //"wd110",
   //"wd111",
   //"wd112",
   //"wd113",
   //"wd114",
   //MPPC09
   //"wd122",
   //"wd123",
   //"wd124",
   //"wd125",
   //"wd115",
   //"wd117",
   //"wd126",
   //"wd127",
   //"wd069",
   //"wd128",
   //"wd129",
   //"wd130",
   //"wd080",
   //"wd081",
   //"wd082",
   //"wd083"
   //DCUS0
   //"wd198",
   //"wd199",
   //"wd211",
   //"wd204",
   //"wd205",
   //"wd206",
   //"wd207",
   //"wd208",
   //DCDS0
   //"wd192",
   //"wd193",
   //"wd194",
   "wd195",
   "wd196",
   //"wd200",
   //"wd201",
   "wd202"
};

int main(int argc, char** argv)
{
   //WD2F
   //const int n = 120;
   //const float down = -0.040;
   //const float up = 0.020;
   //const float gain = 2.5;
   //WD2ADiff
   const int n = 40;
   const float down = -0.005;
   const float up = 0.015;
   const float gain = 1;

   printf("piedistalling %lu WDBs\n", sizeof(wdbs)/sizeof(std::string*));

   for(int b=0; b<sizeof(wdbs)/sizeof(std::string*); b++){
      printf("%s\n", wdbs[b].c_str());
      WDB* wdb= new WDB(wdbs[b].c_str());
      wdb->Connect();
      if(gain > 0) wdb->SetFeGain(-1, gain);
      sleep(3);
      std::vector<uint64_t> s;
      wdb->GetScalers(s);

      char buf[100];
      sprintf(buf, "out-%s.dat", wdbs[b].c_str());
      FILE *f= fopen(buf, "w");

      for(int i=0; i<n; i++) {
         float v = down + (up-down)*i/n;
         wdb->SetDacTriggerLevelV(-1,v);
         float readv = wdb->GetDacTriggerLevelV(0);
         wdb->SetScalerRst(1);
         wdb->SetScalerRst(0);
         sleep(3);
         wdb->GetScalers(s);

         fprintf(f, "%f ", v);
         for(int j=0; j<16; j++) fprintf(f,"%lld ", s[j]);
         fprintf(f, "\n");

         printf("%+5.4f: ", v);
         for(auto sca:s) printf("%6lld ", sca);
         printf("\n");
      }

      delete wdb;
      fclose(f);
   }

   return 0;
}

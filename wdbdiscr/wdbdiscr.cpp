/********************************************************************\

  Name:         daqtest.cpp
  Created by:   Marco Francesconi

  Contents:     Collects events 

\********************************************************************/

#include <stdexcept>
#include "WDBLib.h"

using namespace std;

std::string wdbs[]={
   "wd100",
   "wd101",
   "wd102",
   "wd103",
   "wd104",
   "wd105",
   "wd106",
   "wd107",
   "wd108",
   "wd109",
   "wd026",
   "wd110",
   "wd111",
   "wd112",
   "wd113",
   "wd114",
   "wd122",
   "wd123",
   "wd124",
   "wd125",
   "wd115",
   "wd117",
   "wd126",
   "wd127",
   "wd069",
   "wd128",
   "wd129",
   "wd130",
   "wd048",
   "wd049",
   "wd050",
   "wd051",
   "wd042",
   "wd043",
   "wd044",
   "wd045",
   "wd072",
   "wd073",
   "wd074",
   "wd075",
   "wd118",
   "wd119",
   "wd120",
   "wd121",
   "wd068",
   "wd091",
   "wd092",
   "wd131",
   "wd030",
   "wd031",
   "wd032",
   "wd033",
   "wd034",
   "wd035",
   "wd070",
   "wd071",
   "wd036",
   "wd037",
   "wd038",
   "wd039",
   "wd040",
   "wd041",
   "wd076",
   "wd077",
   "wd078",
   "wd079",
   "wd080",
   "wd081",
   "wd082",
   "wd083",
   "wd090",
   "wd046",
   "wd116",
   "wd093",
   "wd052",
   "wd053",
   "wd054",
   "wd055",
   "wd056",
   "wd057",
   "wd058",
   "wd059",
   "wd060",
   "wd061",
   "wd084",
   "wd085",
   "wd086",
   "wd087",
   "wd088",
   "wd089",
   "wd157",
   "wd158",
   "wd159",
   "wd160",
   "wd161",
   "wd163",
   "wd164",
   "wd165",
   "wd166",
   "wd167",
   "wd168",
   "wd169",
   "wd170",
   "wd172",
   "wd173",
   "wd174",
   "wd192",
   "wd195",
   "wd194",
   "wd196",
   "wd197",
   "wd198",
   "wd209",
   "wd210",
   "wd201",
   "wd202",
   "wd205",
   "wd207"
};

int main(int argc, char** argv)
{
   const int n = 55;
   const float down = -0.035;
   const float up = 0.020;

   printf("piedistalling %d WDBs\n", sizeof(wdbs)/sizeof(std::string*));

   for(int b=0; b<sizeof(wdbs)/sizeof(std::string*); b++){
      printf("%s\n", wdbs[b].c_str());
      WDB* wdb= new WDB(wdbs[b].c_str());
      wdb->Connect();
      //wdb->SetFeGain(-1, gain);
      std::vector<unsigned long long> s;
      wdb->GetScalers(s);

      char buf[100];
      sprintf(buf, "modifiedbyus/out-%s.dat", wdbs[b].c_str());
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

         printf("%f: ", readv);
         for(auto sca:s) printf("%lld ", sca);
         printf("\n");
      }

      delete wdb;
      fclose(f);
   }

   return 0;
}

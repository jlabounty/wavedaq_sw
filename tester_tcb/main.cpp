# include <iostream>
# include "waveform/MEGFADCWaveform.h"
# include "waveform/MEGDiscrWaveform.h"
# include "TApplication.h"
# include "TRandom.h"
# include "TCanvas.h"
# include "TCBTester.h"
# include "TCBTesterWaveform.h"

using namespace std;

TCBTester *tester=nullptr;


void test()
{
   /*MEGFADCWaveform *wfIn = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   MEGFADCWaveform *wfOut = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   TRandom *randgen = new TRandom();
   for(Int_t i=0; i<MEMDIM; i++){
      wfIn->SetAmplitudeAt(i, randgen->Gaus(0, 2));
   }

   TCBTester *tester = new TCBTester("mscb176", 2);
   TCBWaveformWriter *writer = new TCBWaveformWriter(MEMBASEADDR, MEMDIM);
   TCBWaveformReader *reader = new TCBWaveformReader(MEMBASEADDR, MEMDIM);

   writer->SetWaveform(wfIn);
   reader->SetWaveform(wfOut);

   tester->AddMemoryWriter(writer);
   tester->AddMemoryReader(reader);
   tester->ShowMemoryWriters();
   tester->ShowMemoryReaders();

   tester->DoTest();

   delete tester;
   delete randgen;

   TCanvas *c = new TCanvas();
   c->Divide(2);
   c->cd(1);
   wfIn->Draw();
   c->cd(2);
   wfOut->Draw();
   */
}
void testXEC(){
   TRandom *randgen = new TRandom();

   MEGFADCWaveform *wfSum[16];
   MEGFADCWaveform *wfTdcSum[16];
   MEGFADCWaveform *wfTdcNum[16];
   for(int i=0; i<16; i++){
      wfSum[i] = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
      wfTdcNum[i] = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
      wfTdcSum[i] = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   }

   int pos[16];
   for(int i=0; i<16; i++)
      pos[i]= randgen->Integer(MEMDIM);

   for(Int_t i=0; i<MEMDIM; i++){
      for(int j=0; j<16; j++){
         wfSum[j]->SetAmplitudeAt(i, randgen->Gaus(0, 2));
         if(i == pos[j]){
            int ntdc = randgen->Integer(8)+1;
            int sumtdc = randgen->Integer(256);

            printf("slot %d hit at %d with %d tdcs and val=%u\n", j, i, ntdc, sumtdc);

            wfTdcNum[j]->SetAmplitudeAt(i, ntdc);
            wfTdcSum[j]->SetAmplitudeAt(i, sumtdc);
         }
      }
   }
   TCBTester *tester = new TCBTester("mscb176", 2, 0);
   //set parameters
   tester->SetTcbParameter(0, 0x100);//QH
   tester->SetTcbParameter(6, 0x50);//QL
   tester->SetTcbParameter(7, 0x200);//QC
   for(Int_t i=0; i<16; i++){
      TCB1XECWriter *writer = new TCB1XECWriter(i);
      writer->SetWaveforms(wfSum[i], wfTdcSum[i], wfTdcNum[i]);
      tester->AddMemoryWriter(writer);
   }
   MEGFADCWaveform *wfSumOut = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   MEGFADCWaveform *wfMaxOut = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   MEGFADCWaveform *wfTdcSumOut = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   MEGFADCWaveform *wfTdcNumOut = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   TCB1XECReader *reader = new TCB1XECReader();
   tester->AddMemoryReader(reader);
   reader->SetWaveforms(wfSumOut, wfMaxOut, wfTdcSumOut, wfTdcNumOut);

   tester->DoTest();
   TCanvas *c = new TCanvas();
   c->Divide(2);
   c->cd(1);
   wfSum[0]->Draw();
   c->cd(2);
   wfSumOut->Draw();
   for(Int_t i=0; i<MEMDIM; i++){
      if(wfTdcNumOut->GetAmplitudeAt(i) != 0){
         int maxid = wfMaxOut->GetAmplitudeAt(i);
         int tdcsum = wfTdcSumOut->GetAmplitudeAt(i);
         int tdcnum = wfTdcNumOut->GetAmplitudeAt(i);
         printf("got hit at %d with maxid=%d tdcnum=%d and tdcsum=%d\n", i, maxid, tdcnum, tdcsum);
      }
   }
   delete tester;
   delete randgen;
}

typedef struct{
   int rawTime;
   int fineTime;
} chnhit;
typedef struct{
   int id;
   chnhit sx;
   chnhit dx;
} tilehit;
typedef struct{
   std::vector<tilehit> tiles;
   int time;
}trackhit;

void testTC(){
   TRandom *randgen = new TRandom(0);
   std::vector<trackhit> tracks;
   for(int i=0; i<randgen->Integer(3)+1; i++){
      trackhit track;
      track.time= randgen->Integer(MEMDIM*8);
      for(int j=0; j<randgen->Integer(5)+1; j++){
         tilehit tile;
         tile.id = randgen->Integer(16*8);
         int timeOffset = randgen->Integer(8);
         int sxtime = track.time +timeOffset+randgen->Integer(3);
         tile.sx.rawTime = sxtime/8;
         tile.sx.fineTime = 7-sxtime%8;
         int dxtime = track.time +timeOffset+randgen->Integer(3);
         tile.dx.rawTime = dxtime/8;
         tile.dx.fineTime = 7-dxtime%8;
         track.tiles.push_back(tile);
      }
      tracks.push_back(track);
   }

   for(auto t : tracks){
      printf("track with time %d: ", t.time);
      for(auto tile : t.tiles){
         printf("%d[%d,%d](%d,%d)(%d,%d) ", tile.id, 8*tile.sx.rawTime-tile.sx.fineTime, 8*tile.dx.rawTime-tile.dx.fineTime, tile.sx.rawTime, tile.sx.fineTime, tile.dx.rawTime, tile.dx.fineTime);
      }
      printf("\n");
   }

   MEGFADCWaveform *time[16*16];
   MEGDiscrWaveform *hit[16*16];
   for(int i=0; i<16*16; i++){
      time[i] = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
      hit[i] = new MEGDiscrWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   }
         
   for(int j=0; j<MEMDIM; j++){
      for(int i=0; i<16*16; i++){
         hit[i]->SetAmplitudeAt(j, 0);
         time[i]->SetAmplitudeAt(j, 0);
      }
   }
   for(auto t : tracks){
      for(auto tile : t.tiles){
         hit[2*tile.id]->SetAmplitudeAt(tile.sx.rawTime, 1);
         time[2*tile.id]->SetAmplitudeAt(tile.sx.rawTime, tile.sx.fineTime);
         hit[2*tile.id+1]->SetAmplitudeAt(tile.dx.rawTime, 1);
         time[2*tile.id+1]->SetAmplitudeAt(tile.dx.rawTime, tile.dx.fineTime);
      }
   }
   
   TCBTester *tester = new TCBTester("mscb176", 2, 1);
   //set parameters
   tester->SetTcbParameter(1, 0xFFFFFFFF); 
   tester->SetTcbParameter(2, 0xFFFFFFFF); 
   tester->SetTcbParameter(3, 0xFFFFFFFF); 
   tester->SetTcbParameter(4, 0xFFFFFFFF); 
   tester->SetTcbParameter(10, 0x0);//RTCMERGEH1
   tester->SetTcbParameter(11, 0x0);//RTCMERGEL1
   for(Int_t i=0; i<16; i++){
      TCB1TCWriter *writer = new TCB1TCWriter(i);
      writer->SetWaveforms(time+i*16, hit+i*16);
      tester->AddMemoryWriter(writer);
   }

   MEGDiscrWaveform *tcor = new MEGDiscrWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   MEGDiscrWaveform *tchit0 = new MEGDiscrWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   MEGDiscrWaveform *tchit1 = new MEGDiscrWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   MEGFADCWaveform *tctileid0 = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   MEGFADCWaveform *tctileid1 = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   MEGFADCWaveform *tctiletime0 = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   MEGFADCWaveform *tctiletime1 = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   MEGFADCWaveform *tcmult = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);

   TCB1TCReader *reader = new TCB1TCReader();
   tester->AddMemoryReader(reader);
   reader->SetWaveforms(tcor, tchit0, tctileid0, tctiletime0, tchit1, tctileid1, tctiletime1, tcmult);

   tester->DoTest();
   for(int j=0; j<MEMDIM; j++){
      if(tchit0->GetAmplitudeAt(j)){
         printf("track 0, tile %d time %d:%d\n", tctileid0->GetAmplitudeAt(j), j, tctiletime0->GetAmplitudeAt(j));
      }
      if(tchit1->GetAmplitudeAt(j)){
         printf("track 1, tile %d time %d:%d\n", tctileid1->GetAmplitudeAt(j), j, tctiletime1->GetAmplitudeAt(j));
      }
   }
}

# ifndef __CINT__
int main(int argc, char** argv)
{
   TApplication app ("app",&argc,argv);
   if(argc!=3){
      printf("please run with mscbXX slotID\n");
      return 1;
   }
   std::string nodename(argv[1]);
   int slot = atoi(argv[2]);
   printf("connecting to crate %s slot %d\n", nodename.c_str(), slot);
   tester = new TCBTester(nodename.c_str(), slot, 1); //algsel temporarely fixed to 1
   printf("select a test:");
   printf("[ 1] Simple Write-Read test \t [ 2] TCB_1 XEC test");
   printf("[-1] To exit");
   //testTC();
   app.Run();
   return 0;
}
# endif

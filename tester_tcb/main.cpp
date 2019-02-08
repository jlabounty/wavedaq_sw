# include <iostream>
# include "waveform/MEGFADCWaveform.h"
# include "waveform/MEGDiscrWaveform.h"
# include "TApplication.h"
# include "TRandom.h"
# include "TCanvas.h"
# include "TCBTester.h"
# include "TCBTesterWaveform.h"

using namespace std;

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
   //XEC
   /*MEGFADCWaveform *wfSum = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   MEGFADCWaveform *wfMax = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   MEGFADCWaveform *wfMaxVal = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   MEGFADCWaveform *wfTime = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   for(Int_t i=0; i<MEMDIM; i++){
      if(i%2){
         wfSum->SetAmplitudeAt(i, -1);
         wfMax->SetAmplitudeAt(i,0);
         wfMaxVal->SetAmplitudeAt(i, -1);
         wfTime->SetAmplitudeAt(i,0);
      } else {
         wfSum->SetAmplitudeAt(i, 0);
         wfMax->SetAmplitudeAt(i,-1);
         wfMaxVal->SetAmplitudeAt(i, 0);
         wfTime->SetAmplitudeAt(i,-1);
      }
   }
   TCBTester *tester = new TCBTester("mscb176", 2);
   TCBXECWriter *writer = new TCBXECWriter(MEMBASEADDR, MEMDIM*2);
   writer->SetWaveforms(wfSum, wfMax, wfMaxVal, wfTime);
   tester->AddMemoryWriter(writer);

   tester->DoTest();
   delete tester;
   */
   //TC
   /*MEGFADCWaveform *time[16];
   MEGDiscrWaveform *hit[16];
   for(int i=0; i<16; i++){
      time[i] = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
      hit[i] = new MEGDiscrWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   }
   for(Int_t i=0; i<MEMDIM; i++){
      if(i%2){
         for(int j=0; j<16; j++){
            if(j%2){
               time[j]->SetAmplitudeAt(i, 7);
               hit[j]->SetAmplitudeAt(i, 1);
            } else {
               time[j]->SetAmplitudeAt(i, 0);
               hit[j]->SetAmplitudeAt(i, 0);
            }
         }
      } else {
         for(int j=0; j<16; j++){
            if(j%2){
               time[j]->SetAmplitudeAt(i, 0);
               hit[j]->SetAmplitudeAt(i, 0);
            } else {
               time[j]->SetAmplitudeAt(i, 7);
               hit[j]->SetAmplitudeAt(i, 1);
            }
         }
      }
   }
   TCBTester *tester = new TCBTester("mscb176", 2);
   TCBTCWriter *writer = new TCBTCWriter(MEMBASEADDR, MEMDIM*2);
   writer->SetWaveforms(time, hit);
   tester->AddMemoryWriter(writer);

   tester->DoTest();
   delete tester;
   */
}
void testXEC(){
   TRandom *randgen = new TRandom();

   MEGFADCWaveform *wfSum[16];
   for(int i=0; i<16; i++)
      wfSum[i] = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   MEGFADCWaveform *wfMax = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   MEGFADCWaveform *wfMaxVal = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   MEGFADCWaveform *wfTime = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   for(Int_t i=0; i<MEMDIM; i++){
      for(int j=0; j<16; j++)
         wfSum[j]->SetAmplitudeAt(i, randgen->Gaus(0, 2));
      wfMax->SetAmplitudeAt(i,0);
      wfMaxVal->SetAmplitudeAt(i, 0);
      wfTime->SetAmplitudeAt(i,0);
   }
   TCBTester *tester = new TCBTester("mscb176", 2, 0);
   for(Int_t i=0; i<16; i++){
      TCB1XECWriter *writer = new TCB1XECWriter(MEMBASEADDR+i*MEMDIM*2, MEMDIM*2);
      writer->SetWaveforms(wfSum[i], wfMax, wfMaxVal, wfTime);
      tester->AddMemoryWriter(writer);
   }
   MEGFADCWaveform *wfSumOut = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   MEGFADCWaveform *wfMaxOut = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   MEGFADCWaveform *wfMaxValOut = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   MEGFADCWaveform *wfTimeOut = new MEGFADCWaveform(MEMDIM, 12.5e-9, - MEMDIM*12.5e-9);
   TCB1XECReader *reader = new TCB1XECReader(MEMBASEADDR+16*2*MEMDIM, 2*MEMDIM);
   tester->AddMemoryReader(reader);
   reader->SetWaveforms(wfSumOut, wfMaxOut, wfMaxValOut, wfTimeOut);

   tester->DoTest();
   TCanvas *c = new TCanvas();
   c->Divide(2);
   c->cd(1);
   wfSum[0]->Draw();
   c->cd(2);
   wfSumOut->Draw();
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
         
   /*for(int j=0; j<MEMDIM; j++){
      bool hasHit=false;
      int nHit=0;
      if(!randgen->Integer(30)){
         hasHit=true;
         nHit=1+randgen->Integer(10);
         printf("hit at %d: ", j);
      }

      for(int i=0; i<16*8; i++){
         if(hasHit && nHit>0 && !randgen->Integer(2)){
            int timedx=randgen->Integer(2);
            int timesx=timedx;
            hit[2*i]->SetAmplitudeAt(j, 1);
            time[2*i]->SetAmplitudeAt(j, timedx);
            hit[2*i+1]->SetAmplitudeAt(j, 1);
            time[2*i+1]->SetAmplitudeAt(j, timesx);
            printf("%d(%d) ", i, timedx);
            nHit--;
         } else {
            hit[2*i]->SetAmplitudeAt(j, 0);
            time[2*i]->SetAmplitudeAt(j, 0);
            hit[2*i+1]->SetAmplitudeAt(j, 0);
            time[2*i+1]->SetAmplitudeAt(j, 0);
         }

      }
      if(hasHit){
         printf("\n");
      }
   }
   */
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
   for(Int_t i=0; i<16; i++){
      TCB1TCWriter *writer = new TCB1TCWriter(MEMBASEADDR+i*MEMDIM*2, MEMDIM*2);
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

   TCB1TCReader *reader = new TCB1TCReader(MEMBASEADDR+16*2*MEMDIM, 2*MEMDIM);
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
   testTC();
   app.Run();
   return 0;
}
# endif

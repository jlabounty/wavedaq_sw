/*
 
 Name:           read_binary.C
 Created by:     Stefan Ritt <stefan.ritt@psi.ch>
 Date:           December 21st, 2016
 
 Purpose:        Example program under ROOT to read a binary data file written
 by the DRSOsc program. Decode time and voltages from waveforms
 and display them as a graph. Put values into a ROOT Tree for
 further analysis.
 
 To run it, do:
 
 - Crate a file test.dat via the "Save" button in the browser connected
 to the wds server
 - start ROOT
 root [0] .L read_binary.C+
 root [1] decode("test.dat");
 
 */


#include <string.h>
#include <stdio.h>
#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "TString.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "Getline.h"

typedef struct {
   char           tag[3];
   char           version;
} FHEADER;

typedef struct {
   char           time_header[4];
} THEADER;

typedef struct {
   char           bn[2];
   unsigned short board_serial_number;
} BHEADER;

typedef struct {
   char           event_header[4];
   unsigned int   event_serial_number;
   unsigned short year;
   unsigned short month;
   unsigned short day;
   unsigned short hour;
   unsigned short minute;
   unsigned short second;
   unsigned short millisecond;
   unsigned short range;
} EHEADER;

typedef struct {
   char           tc[2];
   unsigned short trigger_cell;
} TCHEADER;

typedef struct {
   char           c[1];
   char           cn[3];
} CHEADER;

/*-----------------------------------------------------------------------------*/

void decode(const char *filename) {
   FHEADER  fh;
   THEADER  th;
   BHEADER  bh;
   EHEADER  eh;
   TCHEADER tch;
   CHEADER  ch;
   
   unsigned int scaler;
   unsigned short voltage[1024];
   unsigned short adc_voltage[2048];
   unsigned char tdc_data[512];
   unsigned long trg_data[512];
   
   typedef struct {
      Double_t waveform[18][1024];
      Double_t time[18][1024];
      UShort_t adc_waveform[16][2048];
      UChar_t tdc_waveform[16][512];
      ULong_t trigger_data[512];
   } WDBDATA;
   std::vector<WDBDATA> data;

   typedef struct{
      float bin_width[18][1024];
   } WDBBIN;
   std::vector<WDBBIN> bins;

   int i, j, b, chn, n, chn_index, n_boards;
   double t1, t2, dt;
   char rootfile[256];
   
   // open the binary waveform file
   FILE *f = fopen(Form("%s", filename), "r");
   if (f == NULL) {
      printf("Cannot find file \'%s\'\n", filename);
      return;
   }
   
   //open the root file
   strcpy(rootfile, filename);
   if (strchr(rootfile, '.'))
      *strchr(rootfile, '.') = 0;
   strcat(rootfile, ".root");
   TFile *outfile = new TFile(rootfile, "RECREATE");
   
   // define the rec tree
   TTree *rec = new TTree("rec","rec");
   
   // create canvas
   TCanvas *c1 = new TCanvas();
   
   // create graph
   TH1D * h = new TH1D("h", "h", 8, -0.5, 7.5);
   
   // read file header
   fread(&fh, sizeof(fh), 1, f);
   if (fh.tag[0] != 'D' || fh.tag[1] != 'R' || fh.tag[2] != 'S') {
      printf("Found invalid file header in file \'%s\', aborting.\n", filename);
      return;
   }
   
   if (fh.version != '8') {
      printf("Found invalid file version \'%c\' in file \'%s\', should be \'8\', aborting.\n", fh.version, filename);
      return;
   }
   
   // read time header
   fread(&th, sizeof(th), 1, f);
   if (memcmp(th.time_header, "TIME", 4) != 0) {
      printf("Invalid time header in file \'%s\', aborting.\n", filename);
      return;
   }
   
   for (b = 0 ; ; b++) {
      data.resize(b+1);
      bins.resize(b+1);

      // read board header
      fread(&bh, sizeof(bh), 1, f);
      if (memcmp(bh.bn, "B#", 2) != 0) {
         // probably event header found
         fseek(f, -4, SEEK_CUR);
         break;
      }
      
      printf("Found data for board #%d\n", bh.board_serial_number);
      
      // read time bin widths
      memset(bins[b].bin_width, sizeof(WDBBIN), 0);
      for (chn=0 ; chn<18 ; chn++) {
         fread(&ch, sizeof(ch), 1, f);
         if (ch.c[0] != 'C') {
            // event header found
            fseek(f, -4, SEEK_CUR);
            break;
         }
         i = (ch.cn[1] - '0')*10 + ch.cn[2] - '0';
         printf("Found timing calibration for channel #%d\n", i);
         fread(bins[b].bin_width[i], sizeof(float), 1024, f);
      }

   }
   n_boards = b;

   for(b = 0 ; b<n_boards; b++)
      rec->Branch(Form("board%02d", b), &data[b] ,"waveform[18][1024]/D:time[18][1024]/D:adc_waveform[16][2048]/s:tdc_waveform[16][512]/b:trigger_data[512]/l");

/*   for(int i=0;i<10; i++){
      for(int c=0; c<18;c++)
         for(int p=0; p<1024;p++){
            data[0].waveform[c][p]=10;
            data[0].time[c][p]=1;
         }
      for(int c=0; c<16;c++)
         for(int p=0; p<2048;p++)
            data[0].adc_waveform[c][p]=2;

      for(int c=0; c<16;c++)
         for(int p=0; p<512;p++)
            data[0].tdc_waveform[c][p]=3;

      for(int p=0; p<512;p++)
         data[0].trigger_data[p]=4;

      rec->Fill();
   }

   rec->Write();
   outfile->Close();
   return ;*/
   
   // loop over all events in data file
   //for (n=0 ; getchar() ; n++) {
   for (n=0 ;  ; n++) {
      // read event header
      i = fread(&eh, sizeof(eh), 1, f);
      if (i < 1)
         break;
      
      printf("Found event #%d, t=%d.%d\n", eh.event_serial_number, eh.second, eh.millisecond);
      
      // loop over all boards in data file
      for (b=0 ; b<n_boards ; b++) {
         
         // read board header
         fread(&bh, sizeof(bh), 1, f);
         if (memcmp(bh.bn, "B#", 2) != 0) {
            printf("Invalid board header in file \'%s\', aborting.\n", filename);
            return;
         }
         
         if (n_boards > 1)
            printf("Found data for board #%d\n", bh.board_serial_number);
         
         // reach channel data
         for (chn=0 ; !feof(f) ; chn++) {
            
            // read channel header
            fread(&ch, sizeof(ch), 1, f);
            if (ch.c[0] != 'C' && ch.c[0] != 'A' && ch.c[0] != 'T') {
               // event header found
               fseek(f, -4, SEEK_CUR);
               break;
            }
            chn_index = (ch.cn[1] - '0')*10 + ch.cn[2] - '0';
            
            if(ch.c[0] == 'C'){
               //printf("found drs for channel %d\n", chn_index);
               //DRS
               fread(&scaler, sizeof(int), 1, f);
               // read trigger cell
               fread(&tch, sizeof(tch), 1, f);
               if (memcmp(tch.tc, "T#", 2) != 0) {
                  printf("Invalid trigger cell header in file \'%s\', aborting.\n", filename);
                  return;
               }

               fread(voltage, sizeof(short), 1024, f);
               for (i=0 ; i<1024 ; i++) {
                  // convert data to volts
                  data[b].waveform[chn_index][i] = (voltage[i] / 65536. + eh.range/1000.0 - 0.5);

                  // calculate time for this cell
                  for (j=0,data[b].time[chn_index][i]=0 ; j<i ; j++)
                     data[b].time[chn_index][i] += bins[b].bin_width[chn_index][(j+tch.trigger_cell) % 1024];
               }
            } else if(ch.c[0] == 'A') {
               //ADC
               //printf("found adc for channel %d\n", chn_index);
               fread(adc_voltage, sizeof(short), 2048, f);
               for (i=0 ; i<2048 ; i++) {
                  data[b].adc_waveform[chn_index][i] = adc_voltage[i];
               }
            } else if(ch.c[0] == 'T') {
               if(ch.cn[0] == '0'){
                  //TDC
                  //printf("found tdc for channel %d\n", chn_index);
                  fread(tdc_data, sizeof(char), 512, f);
                  for (i=0 ; i<512 ; i++) {
                     data[b].tdc_waveform[chn_index][i] = tdc_data[i];
                     //if(i>1){
                     //   if(tdc_data[i] != 0xFF && tdc_data[i-1] == 0xFF){
                     //      int pos = -1;
                     //      for(int bit=0; bit<8; bit++){
                     //         if(! ((tdc_data[i] >>bit) & 0x1)){
                     //            pos = bit;
                     //         }
                     //      }
                     //      h->Fill(pos);
                     //   }
                     //}
                  }
               } else if(ch.cn[0] == 'R'){
                  //TRG
                  //printf("found trg info\n", chn_index);
                  fread(trg_data, sizeof(long), 512, f);
                  for(int i=0; i<512; i++){
                     //int val = trg_data[i]&0xFFFF;
                     //if(val& 0x8000) val -=0x10000;
                     //printf("%02x %02x %016lx\n", data[b].tdc_waveform[0][i], data[b].tdc_waveform[1][i], trg_data[i]);
                     data[b].trigger_data[i] = trg_data[i];
                  }
               }
            }
         }
         
         // align cell #0 of all channels
         t1 = data[b].time[0][(1024-tch.trigger_cell) % 1024];
         for (chn=1 ; chn<4 ; chn++) {
            t2 = data[b].time[chn][(1024-tch.trigger_cell) % 1024];
            dt = t1 - t2;
            for (i=0 ; i<1024 ; i++)
               data[b].time[chn][i] += dt;
         }
         
         // fill root tree
         rec->Fill();
         
         // draw graph and wait for user click
         //h->Draw("");
         //c1->Update();
         //gPad->WaitPrimitive();
      }
   }
   
   // print number of events
   printf("%d events processed, \"%s\" written.\n", n, rootfile);
   //h->Draw("");
   //c1->Update();
   //gPad->WaitPrimitive();
   
   // save and close root file
   rec->Write();
   outfile->Close();
}

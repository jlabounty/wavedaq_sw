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
  float          board_temperature;
  float          board_range;
  unsigned short sampling_frequency;
  unsigned short flags;
} DRSBHEADER;

typedef struct {
   char           event_header[4];
   unsigned short event_serial_number;
   unsigned short trigger_type;
   unsigned int serial_trigger_data;
} EHEADER;

typedef struct {
   char           c[1];
   char           cn[3];
} CHEADER;

typedef struct {
   unsigned short frontendsettings;
   unsigned short trigger_cell;
} DRSCHEADER;

/*-----------------------------------------------------------------------------*/

void decode(const char *filename) {
   FHEADER  fh;
   THEADER  th;
   BHEADER  bh;
   DRSBHEADER  drsbh;
   EHEADER  eh;
   CHEADER  ch;
   DRSCHEADER drsch[18];
   
   unsigned short voltage[1024];
   unsigned short adc_voltage[2048];
   unsigned char tdc_data[512];
   unsigned long trg_data[512];
   unsigned long scaler_data[18], scaler_data_old[18] = {0};
   unsigned long scaler_time, scaler_time_old = 0;
   
   typedef struct {
     Double_t waveform[18][1024];
     Double_t time[18][1024];
     UShort_t adc_waveform[16][2048];
     UChar_t tdc_waveform[16][512];
     ULong_t trigger_data[512];
     Double_t scaler[18];
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
   if (fh.tag[0] != 'W' || fh.tag[1] != 'D' || fh.tag[2] != 'Q') {
      printf("Found invalid file header in file \'%s\', aborting.\n", filename);
      return;
   }
   
   if (fh.version != '0') {
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
      rec->Branch(Form("board%02d", b), &data[b] ,"waveform[18][1024]/D:time[18][1024]/D:adc_waveform[16][2048]/s:tdc_waveform[16][512]/b:trigger_data[512]/l:scaler[18]/D");

   // loop over all events in data file
   for (n=0 ;  ; n++) {
      // read event header
      i = fread(&eh, sizeof(eh), 1, f);
      if (i < 1)
         break;
      
      printf("Found event #%d, type =%d , serial = %d\n", eh.event_serial_number, eh.trigger_type, eh.serial_trigger_data);
      
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

         // read board header
         fread(&drsbh, sizeof(drsbh), 1, f);
                  
         // reach channel data
         for (chn=0 ; !feof(f) ; chn++) {
            
            // read channel header
            fread(&ch, sizeof(ch), 1, f);
            if (ch.c[0] != 'C' && ch.c[0] != 'A' && ch.c[0] != 'T' && ch.c[0] != 'S') {
               // event header found
               fseek(f, -4, SEEK_CUR);
               break;
            }
            chn_index = (ch.cn[1] - '0')*10 + ch.cn[2] - '0';
            
            if(ch.c[0] == 'C'){
	      
	      // read trigger cell and frontend settings
	      fread(drsch+chn_index, sizeof(drsch[0]), 1, f);
	    
	      fread(voltage, sizeof(short), 1024, f);
	      
	      for (i=0 ; i<1024 ; i++) {
		data[b].waveform[chn_index][i] = (voltage[i] / 65536. + drsbh.board_range/1000.0 - 0.5);
		
		// calculate time for this cell
		for (j=0,data[b].time[chn_index][i]=0 ; j<i ; j++)
		  data[b].time[chn_index][i] += bins[b].bin_width[chn_index][(j+drsch[chn_index].trigger_cell) % 1024];
	      }
	      
            } else if(ch.c[0] == 'A') {
               //ADC
               fread(adc_voltage, sizeof(short), 2048, f);
               for (i=0 ; i<2048 ; i++) {
                  data[b].adc_waveform[chn_index][i] = adc_voltage[i];
               }
            } else if(ch.c[0] == 'T') {
               if(ch.cn[0] == '0'){
                  //TDC
                  fread(tdc_data, sizeof(char), 512, f);
                  for (i=0 ; i<512 ; i++) {
                     data[b].tdc_waveform[chn_index][i] = tdc_data[i];
                  }
               } else if(ch.cn[0] == 'R'){
                  //TRG
		 fread(trg_data, sizeof(long), 512, f);
                  for(int i=0; i<512; i++){
		    data[b].trigger_data[i] = trg_data[i];
                  }
               }
            } else if(ch.c[0] == 'S') {
	      //Scaler
	      fread(scaler_data, sizeof(long), 18, f);
	      fread(&scaler_time, sizeof(long), 1, f);
	      for (int i=0 ; i<18 ; i++) {
		data[b].scaler[i] = (Double_t) (scaler_data[i]-scaler_data_old[i])/(scaler_time-scaler_time_old)/12.5e-9;
		scaler_data_old[i] = scaler_data[i];
	      }
	      scaler_time_old = scaler_time;
	    } 
	 }// end for channels
	 
	 // align cell #0 of all channels
	 t1 = data[b].time[0][(1024-drsch[0].trigger_cell) % 1024];
	 for (chn=1 ; chn<18 ; chn++) {
	   t2 = data[b].time[chn][(1024-drsch[chn].trigger_cell) % 1024];
	   dt = t1 - t2;
	   for (i=0 ; i<1024 ; i++)
	     data[b].time[chn][i] += dt;
	 }
	 
	 // fill root tree
	 rec->Fill();
	 
      } //end loop on boards
   }// end loop on events
   
   // print number of events
   printf("%d events processed, \"%s\" written.\n", n, rootfile);
   
   // save and close root file
   rec->Write();
   outfile->Close();
}

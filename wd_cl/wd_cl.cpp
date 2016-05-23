//
//  wds.cpp
//  WaveDAQ Server Application
//
//  Created by Stefan Ritt on 5/8/15.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#ifdef _MSC_VER
#else
#include <getopt.h>
#endif


#include "wds.h"

#define RRUN (0xC7000000>>2)
#define RCAL0 (0xC7000004>>2)
#define RCAL1 (0xC7000008>>2)
#define RCAL2 (0xC700000C>>2)
#define RCAL3 (0xC7000010>>2)
#define RTHR0 (0xC7000014>>2)
#define RTHR1 (0xC7000018>>2)
#define RTHR2 (0xC700001C>>2)
#define RTHR3 (0xC7000020>>2)
#define RMEMADDR (0xC7000024>>2)
#define MEMIN (0xC7100000>>2)
#define MEMOUT (0xC7200000>>2)

#define CMD_OFS_CALIB 1
#define CMD_TIME_CALIB 2

CALIB_PROGRESS ofs_prog;

/*-----------------------------------------------------------------------------------------*/

int main(int argc, char *argv[]) 
{
   int i, j, i1, i2, cmd = 0;
   GLOBALS gl;
   char str[256], *p;
   
   memset(&gl, 0, sizeof(gl));
   gl.http_port          = 8080; // default port
   gl.nominal_sampling_frequency = 5;
   gl.ofs_calib1_flag    = 1;
   gl.ofs_calib2_flag    = 1;
   gl.gain_calib_flag    = 1;
   gl.range_calib_flag   = 1;
   gl.rotate_flag        = 1;
   gl.remove_spikes      = 1;
   gl.trigger_mode       = TM_AUTO;
   gl.osctca_flag        = 0;
   gl.mux_flag           = 0;
   gl.dcv_flag           = 0;
   gl.dcv                = 0;

   for (i=0 ; i<16 ; i++) {
      gl.board[i].trigger_level = 0;
      gl.board[i].gain          = 0;       // gain 1
      gl.board[i].range         = 0;       // range +-0.5V
      gl.board[i].pzc           = 0;       // PZC off
      strlcpy(gl.board[i].trigger_mask, "FFFF0000", sizeof(gl.board[i].trigger_mask)); // or of all 16 channels
   }
   

   gl.n_boards=0;
   
   if(argc <2){
           printf("usage: wd_cl [board number]\n");
	   return FAILURE;
   }

   sprintf(gl.board[gl.n_boards++].name, "wd%03d", atoi(argv[1]));

   
   // initialize ethernet interface to WD board
   if (wd_init(&gl) != SUCCESS)
          return FAILURE;
    
    int option;
    char opline[256];
    do {
        printf("\n --- Options: \n");
        printf("[ 1]: Set Run reg          \t \t  [ 2]: Get Run Reg\n");
        printf("[ 3]: Set Runmode          \t \t  [ 4]: Unset Runmode\n");
        printf("[ 5]: Dump input memory    \t \t  [ 6]: Dump output memory\n");
        printf("[ 7]: Write input memory   \t \t  [ 8]: Set threshold\n");
        printf("[ 9]: Set calibration      \t \t  [-1]: Exit\n");
        
        do {
            printf("Give an option: ");
            scanf("%s",opline);
            option = strtod(opline,NULL);
        } while ( option == 0 ) ;
        //
        if(option == 1) {
            unsigned int data=0;
            int scanfdata;
            wd_read_reg(&gl, 0,RRUN, &data);
	    data &= 0xFFFFFF9;
            printf("FADCMODE? ");
            scanf("%d", &scanfdata);
	    data |= (scanfdata & 0x1)<<1;
            printf("SPYMODE? ");
            scanf("%d", &scanfdata);
	    data |= (scanfdata & 0x1)<<2;
            wd_write_reg(&gl, 0, RRUN, data);
        }
	//
        if(option == 2) {
            unsigned int data;
            wd_read_reg(&gl, 0, RRUN, &data);
	    if(data & 0x00000001) {
	    	printf("STATE RUNMODE\n");
	    } else {
	    	printf("STATE STOP\n");
	    }
	    if(data & 0x00000002) {
	    	printf("FADCMODE on\n");
	    } else {
	    	printf("FADCMODE off\n");
	    }
	    if(data & 0x00000004) {
	    	printf("SPYMODE on\n");
	    } else {
	    	printf("SPYMODE off\n");
	    }

	    printf("RUNREG value: %08x\n", data);

	}
	//
        if(option == 3) {
            unsigned int data;
            wd_read_reg(&gl, 0,RRUN, &data);
            wd_write_reg(&gl, 0, RRUN, data |0x00000001);
        }
        //
        if(option == 4) {
            unsigned int data;
            wd_read_reg(&gl, 0,RRUN, &data);
            wd_write_reg(&gl, 0, RRUN, data &0xFFFFFFFE);
        }
        //
        if(option == 5) {
            int channelID;
            printf("channel: ");
            scanf("%d", &channelID);
            unsigned int memaddr;
            wd_read_reg(&gl, 0,RMEMADDR, &memaddr, 1);
            unsigned int data[512];
            wd_read_reg(&gl, 0,MEMIN + 512*channelID, data, 512);
            FILE* out = fopen("data.dat", "w");
	    fprintf(out, "%x\n", memaddr);
            for (int i=0; i<512; i++) {
                fprintf(out, "%x\n", data[i]);
            }
            fclose(out);
        }
        //
        if(option == 6) {
            int channelID;
            unsigned int memaddr;
            wd_read_reg(&gl, 0,RMEMADDR, &memaddr);
            unsigned int data[2048];
            wd_read_reg(&gl, 0,MEMOUT, data, 2048);
            FILE* out = fopen("data.dat", "w");
	    fprintf(out, "%x\n", memaddr);
            for (int i=0; i<512; i++) {
	        fprintf(out, "%08x", (data[i+1024]) | (data[i+1516]<<16));
                fprintf(out, "%08x\n", data[i] | (data[i+512]<<16) );
            }
            fclose(out);
            
        }
        //
        if(option == 7) {
            FILE* in = fopen("datain.dat", "r");
            for (int i=0; i<512*16; i++) {
		unsigned int data;
                fscanf(in, "%x\n", &data);
            	wd_write_reg(&gl, 0,MEMIN + i, data);
            }
            fclose(in);
        }
        //
	if(option ==  8) {
		unsigned int data;
		unsigned int offset;
		printf("Threshold (0-3): ");
		scanf("%d", &offset);
		printf("Value: ");
		scanf("%x", &data);
		wd_write_reg(&gl, 0,RTHR0+(offset &0x3), data);
	}
        //
	if(option ==  9) {
		unsigned int data;
		unsigned int datain;
		unsigned int channel;
		printf("Input channel (0-15): ");
		scanf("%d", &channel);
		printf("Value (0-255): ");
		scanf("%x", &data);
		data &= 0xFF;
		wd_read_reg(&gl, 0,RCAL0+(channel/4), &datain);
		switch(channel %4){
			case 0: datain &= 0xFFFFFF00;
				datain |= data;
				wd_write_reg(&gl, 0,RCAL0+(channel/4), datain);
				break;
			case 1: datain &= 0xFFFF00FF;
				datain |= data << 8;
				wd_write_reg(&gl, 0,RCAL0+(channel/4), datain);
				break;
			case 2: datain &= 0xFF00FFFF;
				datain |= data << 16;
				wd_write_reg(&gl, 0,RCAL0+(channel/4), datain);
				break;
			case 3: datain &= 0x00FFFFFF;
				datain |= data << 24;
				wd_write_reg(&gl, 0,RCAL0+(channel/4), datain);
				break;
		}
	}
        /* end of the main loop on the options*/
    } while ( option >= 0);
    
    /*wd_write_reg(&gl, 0, (0xC7000000>>2), (0xFFFFFFFF));
    usleep(100);
    wd_write_reg(&gl, 0, (0xC7000000>>2), (0x00000000));
    unsigned int data[512];
    wd_read_reg(&gl, 0,(0xC7108000>>2), data, 512);
    
    for (int j = 0; j<512; j++) {
        printf("%x\n", data[j]);
    }*/
    
   return 0;
}

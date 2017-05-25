#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "mscb.h"
#include "TCBLib.h"
#include <ctime>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>


void MemoryRewind(int ich, u_int32_t last, u_int32_t *mem, u_int32_t *outmem) {
   *outmem = 0;
   for(int i=0;i<32;i++)
      *outmem |= ((mem[(ich/32)*32+i]>>(ich%32))&0x1)<<((32-i+last)%32);  
}

const char *cmb_name = "mscb178";

int main(int argc, char *argv[])
{
   int handle,option;
   char opline[256];
   u_int32_t data, scanfdata;
   u_int32_t trgtype, tpattern;
   FILE *filin, *filout, *filpresca, *filsdly;
   u_int32_t presca[128], counters[128], sdly[5];
   //  clock_t t_before, t_after;
   if(argc != 3) {
      printf("Please indicate the mscb connection ID and node...\n");
      return 0;
   }

   printf("interfacing with TCB_X_0 at %s:%s slot 17....\n", argv[1], argv[2]);

   // open mscb connection
   //  handle = mscb_init("MSCB177", 0, "", 0);
   handle = mscb_init(argv[1], 0, "", 0);
   // create TCB Board

   TCB TCBBoard(argv[1],atoi(argv[2]),17);
   //  TCBBoard.fh = mscb_init(TCBBoard.fmscb_device, 0, "", 0);
   TCBBoard.fh = mscb_init(TCBBoard.fmscb_device, 0, "", 0);
   TCBBoard.SetIDCode();
   TCBBoard.SetNTRG();

   /* main loop on the options */
   do {
      printf("\n  --- Options: \n");
      printf("[ 1]: Set RRUN and RENA    \t \t  [ 2]: Get RRUN and RENA reg\n");
      printf("[ 3]: Activate runmode     \t \t  [ 4]: Remove the busy\n");
      printf("[ 5]: Give a SW stop       \t \t  [ 6]: Give a SW sync \n");
      printf("[ 7]: Set prescaling       \t \t  [ 8]: Board setup\n");
      printf("[ 9]: Read TotalTime       \t \t  [10]: Read Live Time \n");
      printf("[11]: Read Event Counter   \t \t  [12]: Read trigger type\n");
      printf("[13]: Read Trigger Counters\t \t  [14]: Read memory address\n");
      printf("[15]: Select Slot          \t \t  [16]: Set trg bus delay\n");
      printf("[17]: Write SERDES mem     \t \t  [18]: Read SERDES mem\n");
      printf("[19]: Write SERDES Delay   \t \t  [20]: Read SERDES Delay\n");
      printf("[21]: SERDES reset         \t \t  [22]: SERDES bitslip\n");
      printf("[23]: SERDES Scan          \t \t  [24]: SERDES default values\n");
      printf("[25]: Write SERDES Mask    \t \t  [26]: Set Parameter\n");
      printf("[27]: Set check words      \t \t  [28]: Check transmission\n");
      printf("[29]: Force a trigger      \t \t  [-1]: Exit\n");

      do {
         printf("Give an option: ");
         scanf("%s",opline);
         option = strtod(opline,NULL);
      } while ( option == 0 ) ;
      //
      if(option == 1) {
	printf(" opt = 1 : Set RRUN ... \n");
	printf("\nFADCMODE?\n if 0 input RAMs are not written by SERDES data\n if 1 the opposite\n"); 
	scanf("%x",&scanfdata);
	data = scanfdata<<2;
	printf("\nTESTTXMODE?\n if 0 output RAMs are not written by processed data\n if 1 the opposite\n"); 
	scanf("%x",&scanfdata);
	data |= scanfdata<<5;
	if(((TCBBoard.fidcode&0xf000)>>12)==2 || ((TCBBoard.fidcode&0xf000)>>12)==1) {
	  printf("\nDBGSERDES?\n if 1 0xDEADBEEF is set on any SERDES transmission\n");
	  scanf("%x",&scanfdata);
	  data |= scanfdata<<8;
	}
	if( !( (TCBBoard.fidcode&0xf000)>>12==3 && (TCBBoard.fidcode&0xf00)>>8==0xB ) ) {
	  printf("\nENABLE_TRGBUS?\n If 0 then the TRGBus from backplane is not used but internal signals \n if 1 then the backplane signals are used\n");
	  scanf("%x",&scanfdata);
	}
	data |= scanfdata<<4;
	printf("\nMASKS? (hex) \n bit 0 is the EXBUSY \n bit 1 for the SYNC\n bit 2 for the TRG\n");
	scanf("%x",&scanfdata);
	data |= scanfdata<<13; 
	TCBBoard.SetRRUN(&data);
	if(((TCBBoard.fidcode&0xf000)>>12)==3) {
	  int nword = (TCBBoard.fntrg-1)/32 + 1;
	  for(int iword = 0; iword <nword; iword++){
	    printf("\nTRGENA?(hex, bit [%d:%d])\n",(iword+1)*32-1,iword*32);
	    scanf("%x",&scanfdata);
	    data = scanfdata;
	    TCBBoard.SetRENA(&data,iword);
	  }
	}
	if(((TCBBoard.fidcode&0xf000)>>12)!=3) {
	  printf("\nALGSEL?(hex)\n each bit is associated with a trigger ID as in the trigger map \n");
	  scanf("%x",&scanfdata);
	  data = scanfdata;
	  TCBBoard.SetRALGSEL(&data);
	}
      }
      //
      if(option == 2) {
         printf(" opt = 2 : Get RRUN ... \n");
         printf(" FW compilation date: ");
	 TCBBoard.GetCompilDate(&data);
	 printf("%02d/%02d/20%02d %02d:%02d:%02d\n",(data&0xF8000000)>>27,(data&0x7800000)>>23,(data&0x7e0000)>>17,(data&0x1F000)>>12,(data&0xFC0)>>6,(data&0x3F));
         TCBBoard.GetRRUN(&data);
         printf(" RRUN reg content = %08x\n",data);
	 if(((TCBBoard.fidcode&0xf000)>>12)==3) {
	   int nword = (TCBBoard.fntrg-1)/32 + 1;
	   for(int iword = 0; iword <nword; iword++){
	     TCBBoard.GetRENA(&data,iword);
	   }
	 }
	 if(((TCBBoard.fidcode&0xf000)>>12)!=3) {
	   TCBBoard.GetRALGSEL(&data);
	 }
      }
      //
      if(option == 3) {
         printf(" opt = 3 : Activate runmode ... \n");
         TCBBoard.GoRun();
      }
      //
      if(option == 4) {
         printf(" opt = 4 : Remove busy ... \n");
         TCBBoard.RemoveBusy();
      }
      //
      if(option == 5) {
         printf(" opt = 5 : SW stop ... \n");
         TCBBoard.SWStop();
      }
      //
      if(option == 6) {
         printf(" opt = 6 : SW sync ... \n");
         TCBBoard.SWSync();
      }
      //
      if(option == 7) {
         printf(" opt = 7 : Set precaling values (from presca.dat file) ... \n");
         filpresca = fopen("presca.dat","read");
         for(int irow = 0; irow<TCBBoard.fntrg; irow++) {
            fscanf(filpresca,"%x\n",presca+irow);
         }
         TCBBoard.SetPrescaling(presca);
      }
      //
      if(option == 8) {
         printf(" opt = 8 : configuring board ... \n");
         TCB_SETTINGS t;

         //temporarly hardcoded
         t.trgindly = 0;
         t.syncindly = 0;
         t.sprindly = 0;
         t.trgoutdly = 0;
         t.syncoutdly = 0;
         t.sproutdly = 0;
         for(int iTRG =0; iTRG<TCBBoard.fntrg; iTRG++){
            t.triggerenable[iTRG] = 0;
            t.prescaling[iTRG] = 1;
         }
         t.serdesmask = 0x000FFFFF;
         t.algsel = 0;

         TCBBoard.InitBoard(&t, (TCBBoard.GetIDCode()>>12));
      }
      if(option ==  9) {
         printf(" opt = 9 : Get TotalTime ... \n");
         TCBBoard.GetTotalTime(&data);
         printf("\n   Total Time = %f sec\n",(float)data/1e6);
      }
      if(option == 10) {
         printf(" opt = 10 : Get LiveTime ... \n");
         TCBBoard.GetLiveTime(&data);
         printf("\n   Live Time = %f sec\n",(float)data/1e6);
      }
      if(option == 11) {
         printf(" opt = 11 : Get Event Counter ... \n");
         TCBBoard.GetEventCounter(&data);
         printf("\n   Event Counter = %d\n",data);
         TCBBoard.GetSystemEventCounter(&data);
         printf("   System Event Counter = %d\n",data);
      }
      if(option == 12) {
         printf(" opt = 12 : Get trigger type ... \n");
         if((TCBBoard.fidcode >>12)==3){
            TCBBoard.GetTriggerType(&trgtype);
            printf("trigger type = %d\n",trgtype);
            int nword = (TCBBoard.fntrg-1)/32+1;
            for(int iword = 0; iword<nword; iword++) {
               TCBBoard.GetTriggerPattern(&tpattern,iword);
               printf("trigger trgpattern = %08x bit [%d:%d] \n",tpattern,(iword+1)*32-1,iword*32);
            }
         }
         if (TCBBoard.GetSystemTriggerType(&trgtype)){
            printf("system trigger type = %d\n",trgtype);
         } else {
            printf("TRANSMISSION ERROR! reading = %d\n",trgtype);
         }
      }
      if(option == 13) {
         printf(" opt = 13 : Get Trigger Counters ... \n");
         TCBBoard.GetTriggerCounters(counters);
         for(int icou = 0; icou<TCBBoard.fntrg; icou++)
            printf("\n   Trigger Counter %d = %d\n",icou,counters[icou]);
      }
      if(option == 14) {
         printf(" opt = 14 : Get Memory address ... \n");
         TCBBoard.GetMemoryAddress(&data);
         printf("\n   Memory address = %d\n",data);
      }
      //
      if(option == 15) {
         printf(" opt = 15 : Set slot ... \n");
         printf("Slot?\n");
         scanf("%d",&data);
         TCBBoard.fslot = data;
         TCBBoard.SetIDCode();
      }
      if(option == 16) {
         printf(" opt = 16 : Set trigger delay ... \n");
         u_int32_t data1,data2,data3,data4,data5;
         if((TCBBoard.GetIDCode()>>12)==0x3){
            //this is a Master
            printf("Trigger bus delay: SYNC output (0-1f in taps of 80ps)?(hex)\n");
            scanf("%x",&data);
            printf("Trigger bus delay: TRG output (0-1f in taps of 80ps)?(hex)\n");
            scanf("%x",&data1);
            printf("Trigger bus delay: SPARE output (0-1f in taps of 80ps)?(hex)\n");
            scanf("%x",&data2);
            TCBBoard.SetTRGBusODLY(&data,&data1,&data2);
         }
         printf("Trigger bus delay: SYNC input (0-1f in taps of 80ps)?(hex)\n");
         scanf("%x",&data);
         printf("Trigger bus delay: TRG input (0-1f in taps of 80ps)?(hex)\n");
         scanf("%x",&data1);
         printf("Trigger bus delay: SPARE input (0-1f in taps of 80ps)?(hex)\n");
         scanf("%x",&data2);
         TCBBoard.SetTRGBusIDLY(&data,&data1,&data2);
         TCBBoard.GetTRGBusDLY(&data,&data1,&data2,&data3,&data4,&data5);
         printf("I read back ODelay Sync = %x, ODelay Trg = %x, ODelay Spare = %x\n",data,data1,data2);
         printf("            IDelay Sync = %x, IDelay Trg = %x, IDelay Spare = %x\n",data3,data4,data5);
      }
      if(option == 17) {
         printf(" opt 17 = Write SERDES memory ... \n");
         int ichannel, imem, ifil;
         u_int32_t wdata[MEMDIM];
         printf(" serdes channel number? \n");
         scanf("%d",&ichannel);
         printf(" which memory? (0 = LSB, 1 = MSB) \n");
         scanf("%d",&imem);
         printf(" which file? (0 or 1) \n");
         scanf("%d",&ifil);
         if(ifil == 0)
            filin = fopen("writeserdesram.dat","read");
         else
            filin = fopen("writeserdesram2.dat","read");
         for(int irow = 0; irow<MEMDIM; irow++) {
            fscanf(filin,"%x\n",wdata+irow);
         }
         fclose(filin);
         TCBBoard.WriteSERDESMem(ichannel,imem,wdata);
      }
      if(option == 18) {
         printf(" opt 18 = Dump SERDES memory ... \n");
         int ichannel, imem;
         u_int32_t rdata[MEMDIM];
         printf(" serdes channel number? \n");
         scanf("%d",&ichannel);
         printf(" which memory? (0 = LSB, 1 = MSB) \n");
         scanf("%d",&imem);
         TCBBoard.ReadSERDESMem(ichannel,imem,rdata);
         filout = fopen("readserdesram.dat","write");
         for(int irow = 0; irow<MEMDIM; irow++) {
            fprintf(filout,"%08x\n",rdata[irow]);
         }
         fclose(filout);
      }
      if(option == 19) {
         printf(" opt 19 = Write SERDES delay ... \n");
         filsdly = fopen("serdesdly.dat","read");
         for(int irow = 0; irow<5; irow++) {
            fscanf(filsdly,"%x\n",sdly+irow);
         }
         TCBBoard.SetSerdesDelay(sdly);
      }
      if(option == 20) {
         printf(" opt 20 = Read SERDES delay ... \n");

         TCBBoard.GetSerdesDelay(sdly);
         for(int irow = 0; irow<5; irow++) {
            printf("dly%d: %x\n",irow, sdly[irow]);
         }
      }
      if(option == 21) {
         printf(" opt 21 = SERDES reset ... \n");
         TCBBoard.SerdesReset();
      }
      if(option == 22) {
         printf(" opt 22 = SERDES bitslip ... \n");

         u_int32_t icha;
         u_int32_t rdata;
         u_int32_t addr;
         printf("which channel?\n");
         scanf("%d",&icha);
         addr = MEMBASEADDR + 1024*2*icha;
         TCBBoard.SerdesBitslip(icha);
         // now read the word back to check the tx
         TCBBoard.ReadReg(addr,&rdata);
         printf("%08X\n", rdata);
      }
      if(option == 23) {
         printf(" opt 23 = SERDES Scan ... \n");

	 FILE *fout = fopen("tres.dat","w");
         u_int32_t icha;
         u_int32_t patternup, patterndown;
         u_int32_t dly[5];
	 u_int32_t ccounters[17];
	 int howlong;
	 double tres[16][32][8]; //format: channel delay bitslip
	 printf("which channel? (16-19 for FC0-3, 100 all)\n");
         scanf("%d",&icha);
	 printf("How many usec each point? \n");
         scanf("%d",&howlong);
	 patterndown = 0xDEADBEEF;
	 patternup = 0xDEADBEEF;
         if(icha==100) {   //all channels together
	   for(int iDly=0; iDly<32; iDly++){
	     printf("Testing Delay %02X\n",iDly);
	     for(icha = 0; icha<16; icha++){
	       // scan on any possible IDelay 
	       dly[icha/4] = (iDly & 0x1F)<<24 | (iDly & 0x1F)<<16 | (iDly & 0x1F)<<8 | (iDly & 0x1F);
	       TCBBoard.SetSerdesDelay(dly);
	       TCBBoard.SerdesReset(); //also resets the bitslip
	     }
	     for(int iBit=0; iBit<8; iBit++){
	       for(icha = 0; icha<16; icha++){
		 // scan on any possible bitslip
		 TCBBoard.SerdesBitslip(icha);
	       }
	       // disable transmission check
	       TCBBoard.SetEnableTransmissionCheck(0);
	       // reset transmission check
	       TCBBoard.ResetTransmissionCheck();
	       // enable Transmission check
	       TCBBoard.SetEnableTransmissionCheck(1);
	       // wait 1usec
	       usleep(howlong);
	       // disable transmission check
	       TCBBoard.SetEnableTransmissionCheck(0);
	       // read the counters
	       TCBBoard.GetCheckCounters(ccounters);
	       // print the result only if good
	       for(icha = 0; icha<16; icha++){
		 if( ccounters[icha] == 0) 
		   printf(" serdes %d iDly %02X, bitslip %d, number of tests %d \n", icha, iDly, iBit, ccounters[16]);
		 tres[icha][iDly][iBit] = (double) ccounters[icha]/ccounters[16];
	       }
	     }
	   }	   
	   
	   printf("\nDl Bt    0       1       2       3       4       5       6       7       8       9      10       11      12      13      14      15\n");
	   printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	   for(int a=0; a<8; a++) for(int b=0; b<32; b++) {
	       printf("%2x %2X ", b, a);
	       fprintf(fout,"%d %d ", b, a);
	       for(int iSerdes=0; iSerdes<16; iSerdes++) {
		 if(tres[iSerdes][b][a] > 0)
		   printf("%.5f ", tres[iSerdes][b][a]);
		 else 
		   printf("\e[1;34m%.5f \e[0m", tres[iSerdes][b][a]);  
		 fprintf(fout,"%lf ", tres[iSerdes][b][a]);
	       }
	       printf("\n");
	       fprintf(fout,"\n");
	     }
	   fclose(fout);
	 }
	 else {
	   for(int iDly=0; iDly<32; iDly++){
	     printf("Testing Delay %02X\n",iDly);
	     // scan on any possible IDelay 
	     dly[icha/4] = (iDly & 0x1F) << (icha%4)*8;
	     TCBBoard.SetSerdesDelay(dly);
	     TCBBoard.SerdesReset(); //also resets the bitslip
	     for(int iBit=0; iBit<8; iBit++){
	       // scan on any possible bitslip
	       TCBBoard.SerdesBitslip(icha);
	       // disable transmission check
	       TCBBoard.SetEnableTransmissionCheck(0);
	       // reset transmission check
	       TCBBoard.ResetTransmissionCheck();
	       // enable Transmission check
	       TCBBoard.SetEnableTransmissionCheck(1);
	       // wait 1usec
	       usleep(howlong);
	       // disable transmission check
	       TCBBoard.SetEnableTransmissionCheck(0);
	       // read the counters
	       TCBBoard.GetCheckCounters(ccounters);
	       // print the result only if good
	       if( ccounters[icha] == 0) 
		 printf(" serdes %d iDly %02X, bitslip %d, number of tests %d \n", icha, iDly, iBit, ccounters[16]);
	       tres[icha][iDly][iBit] = (double) ccounters[icha]/ccounters[16];
	     }
	   }
	 }
      }
      if(option == 24) {
	printf(" opt 24 = write serdes default value ... \n");
	if((TCBBoard.GetIDCode()>>12)==0x3){
	  filsdly = fopen("serdesmasterdly.dat","read");
	} else {
	  filsdly = fopen("serdesdly.dat","read");
	}
	for(int irow = 0; irow<5; irow++) {
	  fscanf(filsdly,"%x\n",sdly+irow);
	}
	int bitslip[20];
	for(int irow = 0; irow<20; irow++) {
	  fscanf(filsdly,"%d\n",bitslip+irow);
	}
	TCBBoard.SerdesReset();
	TCBBoard.SetSerdesDelay(sdly);
	int flag=1;
	while(flag){
	  flag=0;
	  for(int i=0; i<20; i++){
	    if(bitslip[i]!=0){
	      flag=1;
	      TCBBoard.SerdesBitslip(i);
	      bitslip[i]--;
	    }
	  }
	}
      }
      if(option == 25) {
	printf(" opt = 25 : Set trigger mask ... \n");
	printf("Serdes Mask?(hex) ");
	scanf("%x",&data);
	TCBBoard.SetSerdesMask(&data);
      }
      if(option == 26) {
	u_int32_t offset;
	printf(" opt = 26 : Set Parameter ... \n");
	printf("Parameter offset? ");
	scanf("%d",&offset);
	printf("Value?(hex) ");
	scanf("%x",&data);
	TCBBoard.SetParameter(offset, &data);
      }
      if(option == 27) {
	u_int32_t valdo, valup;
	printf(" opt = 27 : Set control words ... \n");
	printf("Control word [31:0]? (hex)\n");
	scanf("%x",&valdo);
	printf("Control word [63:32]? (hex)\n");
	scanf("%x",&valup);
	TCBBoard.SetCheckWord(valdo,valup);
	TCBBoard.GetCheckWord();
      }
      if(option == 28) {
	printf(" opt = 28 : Get Check Status ... \n");
	TCBBoard.GetCheckStatus();
      }
      if(option == 29) {
	int trgid;
	printf(" opt = 29 : Force a trigger ... \n");
	printf("Trigger Id? from 0 to %d \n",TCBBoard.fntrg-1);
	scanf("%d",&trgid);
	TCBBoard.ForceTrigger(trgid);
      }
      /* end of the main loop on the options*/
   } while ( option >= 0);
   
   
   /* normal exit: close the VME crate */
   printf(" exiting ... \n");

   //
   // close mscb connection
   mscb_exit(TCBBoard.fh);
   return 0;
}


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

int main(int argc, char *argv[])
{
   int handle,option;
   char opline[256];
   u_int32_t data, scanfdata;
   u_int32_t trgtype, tpattern;
   FILE *filin, *filout, *filpresca;
   u_int32_t presca[128], counters[128];
   //  clock_t t_before, t_after;
   if(argc != 3) {
      printf("Please indicate the mscb connection ID and node...\n");
      return 0;
   }

   printf("interfacing with TCB_X_0 at %s:%s slot 17....\n", argv[1], argv[2]);

   // open mscb connection
   handle = mscb_init(argv[1], 0, "", 0);
   // create TCB Board

   TCB TCBBoard(argv[1],atoi(argv[2]),17);
   //  TCBBoard.fh = mscb_init(TCBBoard.fmscb_device, 0, "", 0);
   TCBBoard.fh = mscb_init(TCBBoard.fmscb_device, 0, "", 0);
   TCBBoard.SetIDCode();
   TCBBoard.SetNTRG();
   TCBBoard.fverbose=1;

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
      printf("[19]: Configure Serdes     \t \t  [20]: Serdes Scan\n");
      printf("[21]: Load serdes from file\t \t  [22]: Start Serdes test\n");
      printf("[23]: Write SERDES Mask    \t \t  [24]: Set Parameter\n");
      printf("[25]: Serdes check word    \t \t  [26]: Read serdes status\n");
      printf("[27]: Force a trigger      \t \t  [28]: Reset Transmitter\n");
      printf("[29]: Automatic Serdes cal \t \t  [30]: Dump Data \n");
      printf("[31]: Packetizer Commands  \t \t  [32]: Buffer Commands\n");
      printf("[33]: Reset PLL            \t \t  [34]: Reset PLL unlock cou\n");
      printf("[35]: Read Unlock counter  \t \t  [-1]: Exit\n");

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
        printf("\nTESTTXMODE?\n if 1 output RAMs are not written by processed data\n if 0 the opposite\n"); 
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
      	 if(TCBBoard.GetPacketizerBus()) 
	   printf("WARNING: the local bus is used by the packetizer, some regs are not accessible!\n");
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
         /*for(int iTRG =0; iTRG<TCBBoard.fntrg; iTRG++){
            t.triggerenable[iTRG] = 0;
            t.prescaling[iTRG] = 1;
         }*/
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
            printf("trigger type = %d\n",trgtype&0xFF);
            printf("readout enable = 0x%02x\n",trgtype>>26);
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
         int serdes, link, dly, bitsl;
         printf("serdes id?\n");
         scanf("%d", &serdes);
         printf("serdes link?\n");
         scanf("%d", &link);
         printf("serdes dly?\n");
         scanf("%d", &dly);
         printf("serdes bitslip?\n");
         scanf("%d", &bitsl);
         TCBBoard.ConfigureSingleSerdes(serdes, link, dly, bitsl);
      }
      if(option == 20) {
         printf(" opt 20 = SERDES Scan ... \n");

         int howlong;
         float errors[128][8][32];
         u_int32_t ccounters[129];
         printf("How many usec each point? \n");
         scanf("%d",&howlong);
         FILE *fout = fopen("tres.dat","w");
         fprintf(fout,"%s %d\n", TCBBoard.fmscb_device, TCBBoard.fnserdes);


         for(int idly =0; idly<32; idly++){
            for(int ibit=0; ibit<8; ibit++){
              TCBBoard.ConfigureAllSerdes(idly, ibit);

               TCBBoard.StartSerdesCheck();

               usleep(howlong);

               TCBBoard.StopSerdesCheck();
               TCBBoard.GetSerdesErrorCount(ccounters);
               fprintf(fout,"%d %d ", idly, ibit);
               for(int icounter=0; icounter<TCBBoard.fnserdes*8; icounter++){
                  errors[icounter][ibit][idly] = ccounters[icounter]*1./ccounters[TCBBoard.fnserdes*8];
                  fprintf(fout,"%le ", ccounters[icounter]*1./ccounters[TCBBoard.fnserdes*8]);
               }
               fprintf(fout,"\n");
               printf(" ******************* dly %d/31 ************\r", idly);
               fflush(stdin);
            }
         }

         fclose(fout);

         fout = fopen("serdesconfig.dat","w");
         //search eyes
         const float thr = 1e-20;
         for(int icounter=0; icounter<TCBBoard.fnserdes*8; icounter++){
            float bestCenter=-1;
            int bestWidth=-1;
            int bestBitslip=-1;
            for(int ibit=0; ibit<8; ibit++){
               int state=0;
               int start =-1;
               int stop =-1;
               for(int idly=0; idly<32 && state!=2; idly++){
                  if(errors[icounter][ibit][idly]<thr && state==0){
                     state=1;
                     start=idly;
                     stop=idly;
                  }
                  if (errors[icounter][ibit][idly]<thr && state == 1){
                     stop=idly;
                  } else if(errors[icounter][ibit][idly] >= thr && state == 1){
                     state=2;
                  }
               }

               int width= stop-start;
               if(width > bestWidth){
                  bestWidth = width;
                  bestCenter = (stop+start)/2;
                  bestBitslip = ibit;
               }
            }

            printf("channel %d: dly %f, bit %d width %d\n", icounter, bestCenter, bestBitslip, bestWidth);
            fprintf(fout, "%d %d\n", (int)bestCenter, bestBitslip);
            if(bestWidth > 0) TCBBoard.ConfigureSingleSerdes(icounter/8, icounter%8, (int)(bestCenter), bestBitslip);
         }
         fclose(fout);

      }
      if(option == 21) {
         printf(" opt 21 = load serdes value from file ... \n");
         FILE *fin = fopen("serdesconfig.dat","r");
         for(int iLink=0; iLink<TCBBoard.fnserdes*8; iLink++){
            int dly, bit;
            fscanf(fin, "%d %d\n", &dly, &bit);
            TCBBoard.ConfigureSingleSerdes(iLink/8, iLink%8,  dly, bit);
         }
         fclose(fin);
      }
      if(option == 22) {
        printf(" opt = 22 : Start Serdes check ... \n");
        TCBBoard.StartSerdesCheck();
      }
      if(option == 23) {
        printf(" opt = 23 : Set trigger mask ... \n");
        printf("Serdes Mask?(hex) ");
        scanf("%x",&data);
        TCBBoard.SetSerdesMask(&data);
      }
      if(option == 24) {
        u_int32_t offset;
        printf(" opt = 24 : Set Parameter ... \n");
        printf("Parameter offset? ");
        scanf("%d",&offset);
        printf("Value?(hex) ");
        scanf("%x",&data);
        TCBBoard.SetParameter(offset, &data);
      }
      if(option == 25) {
        u_int32_t valdo, valup;
        printf(" opt = 25 : Set control words ... \n");
        printf("Control word [31:0]? (hex)\n");
        scanf("%x",&valdo);
        printf("Control word [63:32]? (hex)\n");
        scanf("%x",&valup);
        TCBBoard.SetCheckWord(valdo,valup);
        TCBBoard.GetCheckWord();
        /*printf("Control word mask [31:0]? (hex)\n");
        scanf("%x",&valdo);
        printf("Control word mask [63:32]? (hex)\n");
        scanf("%x",&valup);
        TCBBoard.SetCheckWordMask(valdo,valup);
        TCBBoard.GetCheckWordMask();*/
      }
      if(option == 26) {
         printf(" opt = 26 : Get Check Status ... \n");
         //TCBBoard.GetCheckStatus();
         u_int32_t data[4];
         TCBBoard.GetSerdesError(data);
         for (int i=0; i<4; i++){
            printf("Link[%3d:%3d]= %08x\n", (i+1)*32, i*32, data[i]);
         }
      }
      if(option == 27) {
        int trgid;
        printf(" opt = 27 : Force a trigger ... \n");
        printf("Trigger Id? from 0 to %d \n",TCBBoard.fntrg-1);
        scanf("%d",&trgid);
        TCBBoard.ForceTrigger(trgid);
      }
      if(option == 28) {
        printf(" opt = 28 : Reset transmitter ... \n");
        TCBBoard.ResetTransmitter();
      }
      if(option == 29) {
        printf(" opt = 29 : Automatic serdes scan ... \n");
        TCBBoard.CalibrateSerdes();
      }
      if(option == 30) {
        printf(" opt = 30 : Dump Data ... \n");
        int ichannel;
        u_int32_t rdataA[MEMDIM];
        u_int32_t rdataB[MEMDIM];
        u_int32_t address;
        printf(" serdes channel number (0-15 input, 16 output)? \n");
        scanf("%d",&ichannel);
        TCBBoard.ReadSERDESMem(ichannel,0,rdataA);
        TCBBoard.ReadSERDESMem(ichannel,1,rdataB);
        TCBBoard.GetMemoryAddress(&address);
        filout = fopen("dataout.dat","write");
        fprintf(filout,"%04x %d %d %d\n", TCBBoard.fidcode, ichannel, address, MEMDIM);
        for(int irow = 0; irow<MEMDIM; irow++) {
           fprintf(filout,"%08x %08x\n",rdataB[irow], rdataA[irow]);
        }
        fclose(filout);
      }
      if(option == 31) {
        printf(" opt = 31 : Packetizer Commands \n");
        printf("\n  --- Options: \n");
        printf("[ 1]: Enable Packetizer    \t \t  [ 2]: Start Packetizer     \n");
        printf("[ 3]: Set Autostart        \t \t  [ 4]: Assign bus \n");  
        printf("[ 5]: Abort Packetizer     \t \t  [ 6]: Set Packetizer Command\n");
        int sel;
        do {
          printf("Give an option: ");
          scanf("%s",opline);
          sel = strtod(opline,NULL);
        } while ( sel == 0 ) ;
        switch(sel){
          case 1: 
            printf("enable [0/1]? ");
            int ans;
            scanf("%d", &ans);
            TCBBoard.SetPacketizerEnable(ans == 1);
            break;
          case 2: TCBBoard.StartPacketizer(); break;
          case 3:
            printf("enable [0/1]? ");
            scanf("%d", &ans);
            TCBBoard.SetPacketizerAutostart(ans == 1);
            break;
          case 4: 
            printf("assign bus to packetizer [0/1]? ");
            scanf("%d", &ans);
            TCBBoard.SetPacketizerBus(ans == 1);
            break;
          case 5: TCBBoard.AbortPacketizer(); break;
          case 6: 
            int offset, cmd;
            u_int32_t arg0, arg1, opt;
            printf("offset (0-1024) ");
            scanf("%d", &offset);
            printf("command name (0-stop, 1-copy, 2-block_copy, 3-write, 4-jump, 5-jumpIf) ");
            scanf("%d", &cmd);
            printf("argument 0, \"source\" (hex) ");
            scanf("%x", &arg0);
            printf("argument 1, \"destination\" (hex) ");
            scanf("%x", &arg1);
            printf("option (hex) ");
            scanf("%x", &opt);
            TCBBoard.SetPacketizerCommandAt(offset, (PACKETIZER_COMMAND)cmd, arg0, arg1, opt);
            break;
          default: break;
        }
      }
      if(option == 32) {
        printf(" opt = 32 : Buffer Commands \n");
        printf("[ 1]: Read Buffer    \t \t  [ 2]: Increment Pointer\n");
        printf("[ 3]: Reset Logic    \t \t  [ 4]: Get State\n");
        int sel;
        do {
          printf("Give an option: ");
          scanf("%s",opline);
          sel = strtod(opline,NULL);
        } while ( sel == 0 ) ;
        switch(sel){
          case 1: 
            u_int32_t buf[BUFFERSIZE];
            TCBBoard.ReadBuffer(buf);
            for(int i=0; i<BUFFERSIZE; i++) printf("%08x\n", buf[i]);
            break; 
          case 2:
            TCBBoard.IncrementBufferPointer();
            break;
          case 3:
            TCBBoard.ResetBufferLogic();
            break;
          case 4:
            printf ("SPI pointer: %d, Packetizer pointer %d, Memory State %x", TCBBoard.GetSPIBufferPointer(), TCBBoard.GetPacketizerBufferPointer(), TCBBoard.GetBufferState());
            break;
          default: break;
        }
      }
      //reset PLL
      if(option == 33) {
        printf(" opt = 33 : PLL reset ... \n");
        TCBBoard.ResetPLLs();
      }
      // reset PLL unlock counter
      if(option == 34) {
        printf(" opt = 34 : Reset PLL unlock counter ... \n");
        TCBBoard.ResetPLLUnlockCou();
      }
      // get PLL unlock counter
      if(option == 35) {
	u_int32_t *rpcou = 0;
        printf(" opt = 35 : read PLL unlock counter ... \n");
        TCBBoard.GetPLLUnlockCou(rpcou);
	printf(" PLL unlock counter value: %d\n", *rpcou);
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


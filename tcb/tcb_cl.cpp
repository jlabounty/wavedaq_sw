#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mscb.h"
#include "TCBLib.h"
#include <ctime>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>

int main()
{
  int handle,option;
  char opline[256];
  u_int32_t data, scanfdata;
  u_int32_t trgtype, tpattern;
  u_int32_t wdata[128];
  FILE *filin, *filout, *filpresca, *filmasks;
  u_int32_t rdata[32] = {0};
  u_int32_t presca[4], counters[4], masks[4];
  clock_t t_before, t_after;
  // open mscb connection
  handle = mscb_init("212.189.155.62", 0, "", 0);
  // create TCB Board
  TCB TCBBoard(17);
  TCBBoard.SetIDCode(handle);
/* main loop on the options */
 do {
   printf("\n --- Options: \n");
   printf("[ 1]: Set RRUN reg         \t \t  [ 2]: Get RRUN reg\n");
   printf("[ 3]: Activate runmode     \t \t  [ 4]: Remove the busy\n");
   printf("[ 5]: Give a SW stop       \t \t  [ 6]: Give a SW sync \n");
   printf("[ 7]: Set prescaling       \t \t  [ 8]: Set multiplicity thr \n");
   printf("[ 9]: Write RAMs           \t \t  [10]: Read RAMs \n");
   printf("[11]: Read TotalTime       \t \t  [12]: Read Live Time \n");
   printf("[13]: Read Event Counter   \t \t  [14]: Read trigger type\n");
   printf("[15]: Read Trigger Counters\t \t  [16]: Read memory address\n");
   printf("[17]: Set in data masks    \t \t  [18]: Select Slot\n");
   do {
     printf("Give an option: ");
     scanf("%s",opline);
     option = strtod(opline,NULL);
   } while ( option == 0 ) ;
   //
   if(option == 1) {
     printf(" opt = 1 : Set RRUN ... \n");
     printf("FADCMODE?\n");
     scanf("%x",&scanfdata);
     data = scanfdata<<2;
     printf("TRGENA?\n");
     scanf("%x",&scanfdata);
     data |= scanfdata<<8;
     printf("MASKS?\n");
     scanf("%x",&scanfdata);
     data |= scanfdata<<13;
     TCBBoard.SetRRUN(handle,&data);
   }
   //
   if(option == 2) {
     printf(" opt = 2 : Get RRUN ... \n");
     TCBBoard.GetRRUN(handle,&data);
     printf("RRUN reg content = %08x",data);
   }
   //
   if(option == 3) {
     printf(" opt = 3 : Activate runmode ... \n");
     TCBBoard.GoRun(handle);
   }
   //
   if(option == 4) {
     printf(" opt = 4 : Remove busy ... \n");
     TCBBoard.RemoveBusy(handle);
   }
   //
   if(option == 5) {
     printf(" opt = 5 : SW stop ... \n");
     TCBBoard.SWStop(handle);
   }
   //
   if(option == 6) {
     printf(" opt = 6 : SW sync ... \n");
     TCBBoard.SWSync(handle);
   }
   //
   if(option == 7) {
     printf(" opt = 7 : Set precaling values (from presca.dat file) ... \n");
     filpresca = fopen("presca.dat","read");
     for(int irow = 0; irow<4; irow++) {
       fscanf(filpresca,"%x\n",presca+irow);
     }
     TCBBoard.SetPrescaling(handle,presca);
   }
   //
   if(option == 8) {
     printf(" opt = 8 : Set multiplicity ... \n");
     printf("Multiplicity thr?\n");
     scanf("%x",&data);
     TCBBoard.SetTHRMult(handle,&data);
   }
   //
   if(option == 9) {
     printf(" opt = 9 : Write memories (from writeram.dat file) ... \n");
     filin = fopen("writeram.dat","read");
     for(int irow = 0; irow<128; irow++) {
       fscanf(filin,"%x\n",wdata+irow);
     }
     fclose(filin);
     for(int imem = 0; imem<4; imem++)
       TCBBoard.WriteMemory(handle,imem,wdata+imem*32);
   }
   //
   if(option == 10) {
     printf(" opt = 10 : Read memories (to readram.dat file) ... \n");
     t_before = clock();
     filout = fopen("readram.dat","w");
     for(int imem = 0; imem<4; imem++) {
       TCBBoard.ReadMemory(handle,imem,rdata);
       for(int icell = 0; icell<32; icell++) {
       	 fprintf(filout,"%08x\n",rdata[icell]);
       }
     }
     t_after = clock();
     fclose(filout);
     printf ("It took me %d clicks (%f seconds).\n",t_after-t_before,((float)(t_after-t_before))/CLOCKS_PER_SEC);
   }
   if(option == 11) {
     printf(" opt = 1 : Get TotalTime ... \n");
     TCBBoard.GetTotalTime(handle,&data);
     printf("\n   Total Time = %f sec\n",(float)data/1e6);
   }
   if(option == 12) {
     printf(" opt = 12 : Get LiveTime ... \n");
     TCBBoard.GetLiveTime(handle,&data);
     printf("\n   Live Time = %d\n ",data);
   }
   if(option == 13) {
     printf(" opt = 13 : Get Event Counter ... \n");
     TCBBoard.GetEventCounter(handle,&data);
     printf("\n   Event Counter = %d\n",data);
   }
   if(option == 14) {
     printf(" opt = 14 : Get trigger type ... \n");
     TCBBoard.GetTriggerType(handle,&trgtype,&tpattern);
     printf("\n   trigger type = %d, trigger pattern = 0x%x\n",trgtype,tpattern);
   }
   if(option == 15) {
     printf(" opt = 15 : Get Trigger Counters ... \n");
     TCBBoard.GetTriggerCounters(handle,counters);
     for(int icou = 0; icou<4; icou++)
       printf("\n   Trigger Counter %d = %d\n",icou,counters[icou]);
   }
   if(option == 16) {
     printf(" opt = 16 : Get Memory address ... \n");
     TCBBoard.GetMemoryAddress(handle,&data);
     printf("\n   Memory address = %d\n",data);
   }
   if(option == 17) {
     printf(" opt = 17 : Set precaling values (from indatamask.dat file) ... \n");
     filmasks = fopen("indatamask.dat","read");
     for(int imsk = 0; imsk<4; imsk++) {
       fscanf(filmasks,"%x\n",masks+imsk);
     }
     TCBBoard.SetDataMasks(handle,masks);
   }
   if(option == 18) {
     printf(" opt = 18 : Set slot ... \n");
     printf("Slot?\n");
     scanf("%d",&data);
     TCBBoard.fslot = data;
   }


/* end of the main loop on the options*/
 } while ( option >= 0);
  

/* normal exit: close the VME crate */
 printf(" exiting ... \n");

  // close mscb connection
   mscb_exit(handle);
   return 0;
}

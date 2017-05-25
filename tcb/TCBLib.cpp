//
//  TCBLib.cpp
//  Trigger Concentrator Board Library
//
//  Created by Luca Galli and Donato Nicolo' on 12/12/2015
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mscb.h"
#include "TCBLib.h"

u_int32_t kaddrsdly[5]   = {RWDDLY0, RWDDLY1, RWDDLY2, RWDDLY3, RFCDLY};

void TCB::SetBitslip(int *bitslip){
   int nonzero=1;
   while(nonzero){
      nonzero=0;
      u_int32_t bitreg=0;
      for(int iserdes=0; iserdes<20;iserdes++){
         if(bitslip[iserdes]!=0){
            nonzero=1;
            bitreg |= 1 << (iserdes);
            bitslip[iserdes]--;
         }
      }
      WriteReg(RBSLIP, &bitreg);
   }   
}

int TCB::InitType1(TCB_SETTINGS *ts){
   printf("configuring TCB_1_X\n");
   
   u_int32_t fadcmode = 1;
   u_int32_t enable_trgbus = 1;
   u_int32_t testtxmode = 0;
   u_int32_t trgbusmask = 0x7;
   u_int32_t dbgserdes = 0;

   // load RRUN register
   u_int32_t rrundata = (dbgserdes<<8) | (enable_trgbus<<4) | (fadcmode<<2) | (trgbusmask<<13) | (testtxmode <<5);
   SetRRUN(&rrundata);
   u_int32_t ralgsel = (ts->algsel);
   SetRALGSEL(&ralgsel);

   // serdes setup
   u_int32_t sdly[5]={0x0D0B0A09,0x07051511,0x15151905,0x0C0D1313,0x08080808};
   int bitslip[20]={4,4,4,4,4,4,3,3,3,4,4,4,4,4,4,4,1,1,1,1};
   SerdesReset();
   SetSerdesDelay(sdly);
   SetBitslip(bitslip);
   u_int32_t serdesmaskreg = ts->serdesmask;
   SetSerdesMask(&serdesmaskreg);

   //Input TRGBUS
   SetTRGBusIDLY((u_int32_t*) &ts->syncindly, (u_int32_t*) &ts->trgindly, (u_int32_t*) &ts->sprindly);

   RemoveBusy();
   GoRun();   

   return 1;
}

int TCB::InitType2(TCB_SETTINGS *ts){
   printf("configuring TCB_2_X\n");
   
   u_int32_t fadcmode = 1;
   u_int32_t enable_trgbus = 1;
   u_int32_t testtxmode = 0;
   u_int32_t trgbusmask = 0x7;
   u_int32_t dbgserdes = 0;

   // load RRUN register
   u_int32_t rrundata = (dbgserdes<<8) | (enable_trgbus<<4) | (fadcmode<<2) | (trgbusmask<<13) | (testtxmode <<5);
   SetRRUN(&rrundata);
   u_int32_t ralgsel = (ts->algsel);
   SetRALGSEL(&ralgsel);

   // serdes setup
   u_int32_t sdly[5]={0x140F110F,0x0B0E0816,0x19070A0D,0x11141514,0x07070707};
   int bitslip[20]={3,3,3,3,3,2,2,2,2,2,2,3,3,3,3,3,1,1,1,1};
   SerdesReset();
   SetSerdesDelay(sdly);
   SetBitslip(bitslip);
   u_int32_t serdesmaskreg = ts->serdesmask;
   SetSerdesMask(&serdesmaskreg);

   //Input TRGBUS
   SetTRGBusIDLY((u_int32_t*) &ts->syncindly, (u_int32_t*) &ts->trgindly, (u_int32_t*) &ts->sprindly);

   RemoveBusy();
   GoRun();   

   return 1;
}

int TCB::InitType3(TCB_SETTINGS *ts){
   printf("configuring TCB_3_X\n");

   u_int32_t fadcmode = 1;
   u_int32_t enable_trgbus = 1;
   u_int32_t testtxmode = 0;
   u_int32_t trgbusmask = 0x7;

   // set the number of available trigger 
   SetNTRG();
   // load RRUN register
   u_int32_t rrundata = (enable_trgbus<<4) | (fadcmode<<2) | (trgbusmask<<13) | (testtxmode <<5);
   SetRRUN(&rrundata);
   // read the number of trigger available
   
   // load RENA register
   u_int32_t trgenable = 0;
   int nword = fntrg/32 + 1;
   for(int iword = 0; iword <nword; iword++){
     for (int itrg=0; itrg<32; itrg++){
       trgenable |= ts->triggerenable[itrg+iword*32]<<itrg;
     }
     SetRENA(&trgenable,iword);
   }
   
   // serdes setup
   u_int32_t sdly[5]={0x16121211,0x100A0716,0x14080910,0x14151717,0xFFFFFFFF};
   int bitslip[20]={0,0,0,0,0,7,7,7,7,7,7,0,0,0,0,0,0,0,0,0};
   SerdesReset();
   SetSerdesDelay(sdly);
   SetBitslip(bitslip);
   u_int32_t serdesmaskreg = ts->serdesmask;
   SetSerdesMask(&serdesmaskreg);

   //set serdes delay
   SetTRGBusIDLY((u_int32_t*) &ts->syncindly, (u_int32_t*) &ts->trgindly, (u_int32_t*) &ts->sprindly);
   SetTRGBusODLY((u_int32_t*) &ts->syncoutdly, (u_int32_t*) &ts->trgoutdly, (u_int32_t*) &ts->sproutdly);
   
   //set prescaling
   SetPrescaling((u_int32_t*)ts->prescaling);
  
   //remove the busy
   RemoveBusy();
   // give a SW Sync
   SWSync();
   // give a SW stop to go idle
   SWStop();

   return 1;
}

int TCB::InitBoard(TCB_SETTINGS *ts, int iType)
{
   // open MSCB connecttion
   fh = mscb_init(fmscb_device, 0, "", 0);
   if (fh < 0) //there is not MSCB connection
      return 0;

   // check the board ID
   SetIDCode();
   if((fidcode == 0xffff) || (fidcode == 0x0000)) 
     return 0; // there is no TCB in the crate

   if((fidcode>>12)!=(u_int32_t) iType){//check TCB type
      //cm_msg(MERROR, "wd_fe","Wrong TCB Type, read %X, required %X", fidcode>>12, iType);
      printf("Wrong TCB Type, read %X, required %X\n", fidcode>>12, iType);
     return 0;
   }
        
   if ((fidcode>>12)==1){
   //TCB_1
     return InitType1(ts);
   }else if((fidcode>>12)==2) {
   //TCB_2
     return InitType2(ts); 
   } else if((fidcode>>12)==3){
   //TCB_3
     return InitType3(ts);
   } else{
      //unknow TCB
      //cm_msg(MERROR, "wd_fe","Unknown TCB Type");
      printf("Unknown TCB Type\n");
      return 0;
   }
}

// general write register function
void TCB::WriteReg(u_int32_t addr, u_int32_t *data)
{
   int status;

   // before than writing we have to perform a byteswap
   u_int32_t wdata = ((*data&0xff)<<24) | ((*data&0xff00)<<8) | ((*data&0xff0000)>>8) | ((*data&0xff000000)>>24);
   status = mscb_write_mem(fh, fmscb_addr, fslot, addr, &wdata, sizeof(wdata));
   // print something only in case of error
   if (status != 1)
      printf("Error: status = %d\n", status);
}

// general read register function
void TCB::ReadReg(u_int32_t addr, u_int32_t *data)
{
   char dbuf[1024];
   
   *data = 0;
   mscb_read_mem(fh, fmscb_addr, fslot, addr, &dbuf, 4);
   for (int i=0 ; i<4 ; i++)
      *data |= ((u_int32_t) dbuf[3-i]&0xff)<<(i*8); //"(i*8)" as a byte swap
}

// general read register function
void TCB::ReadBLT(u_int32_t addr, u_int32_t *data, int nword)
{
   char dbuf[1024];
   
   mscb_read_mem(fh, fmscb_addr, fslot, addr, &dbuf, nword*4); //4*nword: it is in number of bytes
   for (int iword=0 ; iword<nword ; iword++)  {
      data[iword] = 0;
      for(int ibyte = 0; ibyte<4; ibyte++)
         data[iword] |= ((u_int32_t) dbuf[(iword*4+3)-ibyte]&0xff)<<(ibyte*8); //"(i*8)" as a byte swap
   }
}

// general write register function
void TCB::WriteBLT(u_int32_t addr, u_int32_t *data, int nword)
{
   int status;
   
   // before than writing we have to perform a byteswap
   u_int32_t wdata[1024];

   for(int iWord=0; iWord<(nword&0xFF); iWord++){
       wdata[iWord] = ((data[iWord]&0xff)<<24) | ((data[iWord]&0xff00)<<8) | ((data[iWord]&0xff0000)>>8) | ((data[iWord]&0xff000000)>>24);
       //printf("[%3i] %08x %08x\n", iWord, data[iWord], wdata[iWord]);
   }
   status = mscb_write_mem(fh, fmscb_addr, fslot, addr, wdata, 4*nword);
   // print something only in case of error
   if (status != 1)
      printf("Error: status = %d\n", status);
}
// prescaling values setting
void TCB::SetPrescaling(u_int32_t *presca)
{
  if ((fidcode>>12)!=3) {printf("setting prescaling on TCB %4x!!!!! skipped\n", fidcode); return;}
   for (int ireg=0; ireg<fntrg; ireg++)
      WriteReg(RPRESCA+ireg,presca+ireg);
}

// read prescaling values
void TCB::GetPrescaling(u_int32_t *presca)
{
   //read loop on prescaling registers
  if ((fidcode>>12)!=3) { printf("setting prescaling on TCB %4x!!!!! skipped\n", fidcode); return;}
   for (int ireg = 0; ireg<fntrg; ireg++)
      ReadReg(RPRESCA+ireg,presca+ireg);
}

//Set IDCode by accessing to rrun register
void TCB::SetIDCode()
{
   u_int32_t data;
   u_int32_t addr = RRUN;
   
   // read the RRUN register and take the content
   ReadReg(addr, &data);

   //the IDCode is obtained by parsing the data
   fidcode = ((data&0xffff0000)>>16);
}

//Set NTRG by accessing to rntrg register
void TCB::SetNTRG()
{
   u_int32_t data;
   u_int32_t addr = RNTRG;
   
   // read the RRUN register and take the content
   ReadReg(addr, &data);

   //the IDCode is obtained by parsing the data
   fntrg = data;
}

// Write a memory
void TCB::WriteMemory(int which, u_int32_t *data)
{
   u_int32_t addr;
   
   //check mamory available
   if (which >= MEMNUM) return;

   //calculate base address
   addr = MEMBASEADDR + which*MEMDIM;

   // now loop to write the memory cells
   for (int icell = 0; icell<MEMDIM; icell++) {
      WriteReg(addr+icell,data+icell);
   }
}

//write memories using BLT
void TCB::WriteMemoryBLT(int which, u_int32_t *data)
{

   u_int32_t addr;
   
   //check mamory available
   if (which >= MEMNUM) return;

   //calculate base address
   addr = MEMBASEADDR + which*MEMDIM;

   //calculate number of BLT (each is 64 words)
   int BLTSIZE = 32;
   int NBLT = MEMDIM/BLTSIZE;

   // now loop to write the memory cells
   for (int iblt = 0; iblt<NBLT; iblt++) {
      WriteBLT(addr+(iblt*BLTSIZE),data+(iblt*BLTSIZE), BLTSIZE);
   }
}

// Read a memory
void TCB::ReadMemory(int which, u_int32_t *data)
{
   u_int32_t addr;
   

   //check mamory available
   if (which >= MEMNUM) return;

   //calculate base address
   addr = MEMBASEADDR + which*MEMDIM;

   // now loop to write the memory cells
   for (int icell = 0; icell<MEMDIM; icell++) {
      ReadReg(addr+icell,data+icell);
   }
}

// Read all the memories with BLT
void TCB::ReadMemoryBLT(int which, u_int32_t *data)
{
   u_int32_t addr;
   
   //check mamory available
   if (which >= MEMNUM) return;

   //calculate base address
   addr = MEMBASEADDR + which*MEMDIM;

   //calculate number of BLT (each is 64 words)
   int BLTSIZE = 32;
   int NBLT = MEMDIM/BLTSIZE;

   // now loop to write the memory cells
   for (int iblt = 0; iblt<NBLT; iblt++) {
      ReadBLT(addr+(iblt*BLTSIZE),data+(iblt*BLTSIZE), BLTSIZE);
   }
}

// activate the RUNMODE signal
void TCB::GoRun()
{
   u_int32_t addr = RRUN;
   u_int32_t data;
   // first read the RRUN register to copy the current status
   ReadReg(addr,&data);
   // now set the runmode
   data = (data&0xFFFFFFFC) | 0x1;
   WriteReg(addr,&data);
}

// check the RUNMODE status
int TCB::IsRunning()
{
   u_int32_t addr = RRUN;
   u_int32_t data;
   
   ReadReg(addr,&data);
   data &= 0x1;
   return (data);
}

// check the BUSY status
int TCB::IsBusy()
{
   u_int32_t addr = RRUN;
   u_int32_t data;
   
   ReadReg(addr,&data);
   data &= 0x8;
   return (data);
}

// remove the internal BUSY signal
void TCB::RemoveBusy()
{
   u_int32_t addr = RRUN;
   u_int32_t data;
   // remove the busy until it is not read back
   do {
      // first read the RRUN register to copy the current status
      ReadReg(addr,&data);
      // now remove the busy
      data = (data&0xFFFFFFFC) | 0x2;
      // now set the busy
      WriteReg(addr,&data);
      ReadReg(addr,&data);
   } while(TCB::IsBusy()==1);
}

// activate the internal Sync signal
void TCB::SWSync()
{
   u_int32_t addr = RRUN;
   u_int32_t data;
   
   // first read the RRUN register to copy the current status
   ReadReg(addr,&data);
   
   // now sync
   data = (data&0xFFFFFFFC) | 0x80;
   WriteReg(addr,&data);
}

// activate the internal stop signal
void TCB::SWStop()
{
   u_int32_t addr = RRUN;
   u_int32_t data;

   // first read the RRUN register to copy the current status
   ReadReg(addr,&data);
   
   // now go to stop
   data = (data&0xFFFFFFFC) | 0x40;
   WriteReg(addr,&data);
}

// write the RRUN register
void TCB::SetRRUN(u_int32_t *data)
{
   u_int32_t addr = RRUN;
   WriteReg(addr,data);
}
// write the RENA register
void TCB::SetRENA(u_int32_t *data, int iword)
{
   u_int32_t addr = RENA + iword;
   WriteReg(addr,data);
}
// write the RALGSEL register
void TCB::SetRALGSEL(u_int32_t *data)
{
   u_int32_t addr = RALGSEL;
   WriteReg(addr,data);
}

// read the RRUN register
void TCB::GetRRUN(u_int32_t *data)
{
   u_int32_t addr = RRUN;
   ReadReg(addr,data);
   if((*data&0xF000000)>>24==0xF) {
     printf("\n*********************************************************************************************************************\n");
     printf("** Board configured to drive the trigger bus to the fron panel connector, check the cable to the Ancillary Master! **\n");
     printf("*********************************************************************************************************************\n\n");
   }   
   else if((*data&0xF000000)>>24==0xB) {
     printf("\n****************************************************************\n");
     printf("** Board configured to drive the trigger bus to the backplane **\n");
     printf("****************************************************************\n\n");
   }
   printf(" RUNMODE status %x \n",*data&0x1);
   printf(" FADCMODE status %x \n",(*data&0x4)>>2);
   printf(" TESTTXMODE status %x \n",(*data&0x20)>>5);
   if( (fidcode>>12)==2 || (fidcode>>12)==1 ) 
     printf(" DBGSERDES status %x \n",(*data&0x100)>>5);
   printf(" INBUSY status %x \n",(*data&0x2)>>1);
   printf(" EXBUSY status %x \n",(*data&0x8)>>3);
   printf(" ENABLE TRGBUS status %x \n",(*data&0x10)>>4);
   printf(" MASKBUSY status %x \n",(*data&0x2000)>>13);
   printf(" MASKSYNC status %x \n",(*data&0x4000)>>14);
   printf(" MASKTRG status %x \n",(*data&0x8000)>>15);
   printf(" IDCODE status %x \n",(*data&0xffff0000)>>16);
}
// read the RENA register
void TCB::GetRENA(u_int32_t *data, int iword)
{
  u_int32_t addr = RENA + iword;
  ReadReg(addr,data);
  printf(" TRGENA status %x, bit [%d:%d]\n",*data,(iword+1)*32-1,iword*32);
}

// read the RALGSEL register
void TCB::GetRALGSEL(u_int32_t *data)
{
  u_int32_t addr = RALGSEL;
  ReadReg(addr,data);
  printf(" ALGSEL status %x \n",*data);
}

// read total time
void TCB::GetTotalTime(u_int32_t *data)
{
   u_int32_t addr = RTOTTIME;
   ReadReg(addr,data);
}

// read live time
void TCB::GetLiveTime(u_int32_t *data)
{
   u_int32_t addr = RLIVETIME;
   ReadReg(addr,data);
}

// read event counter
void TCB::GetEventCounter(u_int32_t *data)
{
   u_int32_t addr = REVECOU;
   ReadReg(addr,data);
}

// read trigger type
void TCB::GetTriggerType(u_int32_t *data)
{
   u_int32_t addr = RTRITYPE;
   ReadReg(addr,data);
}
// read trigger type
void TCB::GetTriggerPattern(u_int32_t *data, int iword)
{
   u_int32_t addr = RTRIPATT;
   ReadReg(addr+iword,data);
}

// read system event counter
void TCB::GetSystemEventCounter(u_int32_t *data)
{
   u_int32_t addr = RSYSEVECOU;
   ReadReg(addr,data);
}

// read system trigger type
bool TCB::GetSystemTriggerType(u_int32_t *type)
{
   u_int32_t addr = RSYSTRITYPE;
   u_int32_t data;
   ReadReg(addr,&data);
   //extract trigger type
   *type = data&0xffff;

   if(data&0x80000000) return false;
   else return true;
}
// read trigger counters
void TCB::GetTriggerCounters(u_int32_t *data)
{
    int ncycle = (fntrg-1)/32 + 1;
    for(int icycle = 0; icycle<ncycle; icycle++)
      ReadBLT(RTRGCOU+icycle*32,data+icycle*32,32);
}

// read memory address
void TCB::GetMemoryAddress(u_int32_t *data)
{
   u_int32_t addr = RMEMADDR;
   ReadReg(addr,data);
}

// trg bus delay setting
void TCB::SetTRGBusODLY(u_int32_t *syncdly, u_int32_t *trgdly, u_int32_t *sprdly) {
   if ((fidcode>>12)!=3) printf("setting TRGBus on TCB %4x!!!!!\n", fidcode);
   //   u_int32_t reset = 0x80000000;
   u_int32_t value;
   ReadReg(RBUSDLY, &value);
   value &=0xFFFF;
   value |= (((*syncdly) & 0x1f) | (((*trgdly) & 0x1f)<<5) | (((*sprdly) & 0x1f)<<10))<<16; // the output are from bit 16
   u_int32_t valueload = value | 0x80000000;
   // first reset the delay controller
   //   WriteReg(RBUSDLY,&reset);
   // then load the value
   WriteReg(RBUSDLY,&value);
   // then give a load pulse
   WriteReg(RBUSDLY,&valueload);
   // then restore the delay
   WriteReg(RBUSDLY,&value);
} //end trg bus delay setting

// trg bus delay setting
void TCB::SetTRGBusIDLY(u_int32_t *syncdly, u_int32_t *trgdly, u_int32_t *sprdly) {
   if ((fidcode>>12)!=3) printf("setting TRGBus on TCB %4x!!!!!\n", fidcode);
   //   u_int32_t reset = 0x80000000;
   u_int32_t value;
   ReadReg(RBUSDLY, &value);
   value &=0xFFFF0000;
   value |= ((*syncdly) & 0x1f) | (((*trgdly) & 0x1f)<<5) | (((*sprdly) & 0x1f)<<10);
   u_int32_t valueload = value | 0x8000;
   // first reset the delay controller
   //   WriteReg(RBUSDLY,&reset);
   // then load the value
   WriteReg(RBUSDLY,&value);
   // then give a load pulse
   WriteReg(RBUSDLY,&valueload);
   // then restore the delay
   WriteReg(RBUSDLY,&value);
} //end trg bus delay setting

// trg bus delay readout
void TCB::GetTRGBusDLY(u_int32_t *osyncdly, u_int32_t *otrgdly, u_int32_t *osprdly, u_int32_t *isyncdly, u_int32_t *itrgdly, u_int32_t *isprdly) {
//  int status;
  u_int32_t dly;
  // read trg bus dly reg
  ReadReg(RBUSDLY,&dly);
  *isyncdly = dly&0x1f;
  *itrgdly = (dly>>5)&0x1f;
  *isprdly = (dly>>10)&0x1f;
  *osyncdly = (dly>>16)&0x1f;
  *otrgdly = (dly>>21)&0x1f;
  *osprdly = (dly>>26)&0x1f;
} //end trg bus delay setting

void TCB::WriteSERDESMem(int iserdes, int imem, u_int32_t *data){
  WriteMemoryBLT(2*iserdes+imem, data);
}

void TCB::ReadSERDESMem(int iserdes, int imem, u_int32_t *data){
  ReadMemoryBLT(2*iserdes+imem, data);
}
// serdes delay values setting
void TCB::SetSerdesDelay(u_int32_t *data)
{
   for (int ireg=0; ireg<5; ireg++)
      WriteReg(kaddrsdly[ireg],data+ireg);
}

// read serdes delay values
void TCB::GetSerdesDelay(u_int32_t *data)
{
   //read loop on prescaling registers
   for (int ireg = 0; ireg<5; ireg++)
      ReadReg(kaddrsdly[ireg],data+ireg);
}// reset all serdes 
void TCB::SerdesReset()
{
   // write 0x80000000 on RBLIP 
  u_int32_t wdata = 0x80000000;
  WriteReg(RBSLIP,&wdata);
}
// give a bitslip 
void TCB::SerdesBitslip(u_int32_t icha)
{
  u_int32_t wdata;
  wdata = 1<<icha;
  WriteReg(RBSLIP,&wdata);
}
// serdes mask values setting
void TCB::SetSerdesMask(u_int32_t *data)
{
   WriteReg(RSERDESMSK,data);
}
// set parameter
void TCB::SetParameter(u_int32_t offset, u_int32_t *data)
{
   WriteReg(RPARAM + offset, data);
}
// get FW compilation date
void TCB::GetCompilDate(u_int32_t *data)
{
  ReadReg(USR_ACCESS,data);
}
// serdes mask values setting
void TCB::ForceTrigger(int trg)
{
  u_int32_t data;
  int iword = trg/32;
  data = 1<<trg%32;
   WriteReg(RTRGFORCE+iword,&data);
}
// set the transmission check word
void TCB::SetCheckWord(u_int32_t valuedo,u_int32_t valueup) 
{
  // first write [31:0]
  WriteReg(RCHKWORDDO,&valuedo);
  // then write [63:32]
  WriteReg(RCHKWORDUP,&valueup);
}
// get the transmission check word
void TCB::GetCheckWord() {
  u_int32_t data;
  // first read [31:0]
  ReadReg(RCHKWORDDO,&data);
  printf("Check word [31:0] = %08X\n",data);
  // then read [63:32]
  ReadReg(RCHKWORDUP,&data);
  printf("Check word [63:32] = %08X\n",data);

}
// read the transmission check status
void TCB::GetCheckStatus() {
  u_int32_t data;
  // first read [31:0]
  ReadReg(RCHKSTATUS,&data);
  printf("Transmission Status = %08X\n",data);
}
// enable/disable transmission check
void TCB::SetEnableTransmissionCheck(u_int32_t enable) 
{
  u_int32_t wdata = 0;
  // if enable == 1 then enabled
  wdata |= enable<<31;
  // write corresponding bit
  WriteReg(RCHKSTATUS,&wdata);
}
// reset transmission check
void TCB::ResetTransmissionCheck() 
{
  u_int32_t wdata = 0;
  // if enable == 1 then enabled
  wdata |= 1<<30;
  // first reset
  WriteReg(RCHKSTATUS,&wdata);
  wdata = 0;
  // then release the reset
  WriteReg(RCHKSTATUS,&wdata);
}
// read check counters
void TCB::GetCheckCounters(u_int32_t *rdata) {
  // first read the counters
  //  for(int icou = 0; icou<16; icou++)
    ReadBLT(RCHKCOU,rdata,16);
  //then the normalisation counter
  ReadReg(RCHKTIM,rdata+16);
}



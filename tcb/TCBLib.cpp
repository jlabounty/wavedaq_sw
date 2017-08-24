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
#include "math.h"
#include <unistd.h>

int TCB::InitType1(TCB_SETTINGS *ts){
   if (fverbose)
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
   //crate 181
   //u_int32_t sdly[5]={0x0F0B0D0C,0x0B020613,0x1704080C,0x0B121310,0x08080808};
   //int bitslip[20]={4,4,4,4,4,3,3,3,3,3,3,4,4,4,4,4,1,1,1,1};
   //crate 186
   /*u_int32_t sdly[5]={0x0F0D0F0A,0x07050511,0x1017080B,0x0B0E0F14,0x08080808};
   int bitslip[20]={4,4,4,4,4,3,3,3,3,3,4,4,4,4,4,4,1,1,1,1};
   SerdesReset();
   SetSerdesDelay(sdly);
   SetBitslip(bitslip);
   */
   u_int32_t serdesmaskreg = ts->serdesmask;
   SetSerdesMask(&serdesmaskreg);

   //Input TRGBUS
   SetTRGBusIDLY((u_int32_t*) &ts->syncindly, (u_int32_t*) &ts->trgindly, (u_int32_t*) &ts->sprindly);

   RemoveBusy();
   GoRun();   

   return 1;
}

int TCB::InitType2(TCB_SETTINGS *ts){
   if (fverbose)
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
   /*u_int32_t sdly[5]={0x140F110F,0x0B0E0816,0x19070A0D,0x11141514,0x07070707};
   int bitslip[20]={3,3,3,3,3,2,2,2,2,2,2,3,3,3,3,3,1,1,1,1};
   SerdesReset();
   SetSerdesDelay(sdly);
   SetBitslip(bitslip);
*/
   u_int32_t serdesmaskreg = ts->serdesmask;
   SetSerdesMask(&serdesmaskreg);

   //Input TRGBUS
   SetTRGBusIDLY((u_int32_t*) &ts->syncindly, (u_int32_t*) &ts->trgindly, (u_int32_t*) &ts->sprindly);

   RemoveBusy();
   GoRun();   

   return 1;
}

int TCB::InitType3(TCB_SETTINGS *ts){
   if (fverbose)
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
   /*u_int32_t trgenable = 0;
   int nword = fntrg/32 + 1;
   for(int iword = 0; iword <nword; iword++){
     for (int itrg=0; itrg<32; itrg++){
       trgenable |= ts->triggerenable[itrg+iword*32]<<itrg;
     }
     SetRENA(&trgenable,iword);
   }*/
   
   // serdes setup
/*   u_int32_t sdly[5]={0x16121211,0x100A0716,0x14080910,0x14151717,0xFFFFFFFF};
   int bitslip[20]={0,0,0,0,0,7,7,7,7,7,7,0,0,0,0,0,0,0,0,0};
   SerdesReset();
   SetSerdesDelay(sdly);
   SetBitslip(bitslip);
*/
   u_int32_t serdesmaskreg = ts->serdesmask;
   SetSerdesMask(&serdesmaskreg);

   //set serdes delay
   SetTRGBusIDLY((u_int32_t*) &ts->syncindly, (u_int32_t*) &ts->trgindly, (u_int32_t*) &ts->sprindly);
   SetTRGBusODLY((u_int32_t*) &ts->syncoutdly, (u_int32_t*) &ts->trgoutdly, (u_int32_t*) &ts->sproutdly);
   
   //set prescaling
   //SetPrescaling((u_int32_t*)ts->prescaling);
  
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

   //make sure bus is assegned to SPI
   SetPacketizerBus(false);
   AbortPacketizer();
   ResetBufferLogic();

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
  if ((fidcode>>12)!=3) {
     printf("setting prescaling on TCB %4x!!!!! skipped\n", fidcode);
     return;
  }
   for (int ireg=0; ireg<fntrg; ireg++)
      WriteReg(RPRESCA+ireg,presca+ireg);
}

// read prescaling values
void TCB::GetPrescaling(u_int32_t *presca)
{
   //read loop on prescaling registers
  if ((fidcode>>12)!=3) {
     printf("setting prescaling on TCB %4x!!!!! skipped\n", fidcode);
     return;
  }
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
   if((fidcode>>12)==1) fnserdes = 16;
   else if((fidcode>>12)==2) fnserdes = 4;
   else if((fidcode>>12)==3) fnserdes = 16;
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

// activate the RUNMODE signal (by removing interal busy)
void TCB::GoRun()
{
   u_int32_t addr = RCMD;
   u_int32_t data;
   // now set the runmode
   data = 0x1;
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

// remove the internal BUSY signal: identical to GORUN with runmode state machine
void TCB::RemoveBusy()
{
  u_int32_t addr = RCMD;
   u_int32_t data;
   // now set the runmode
   data = 0x1;
   WriteReg(addr,&data);
}

// activate the internal Sync signal
void TCB::SWSync()
{
   u_int32_t addr = RCMD;
   u_int32_t data;
   data = 0x4;
   WriteReg(addr,&data);
}

// activate the internal stop signal
void TCB::SWStop()
{
   u_int32_t addr = RCMD;
   u_int32_t data;
   data = 0x2;
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
// write the RENA according to bool array
void TCB::SetTriggerEnable(bool *triggerenable)
{
   int nword = fntrg/32 + (((fntrg%32) !=0)?1:0);
   for(int iword = 0; iword <nword; iword++){
     u_int32_t trgenable = 0;
     for (int itrg=0; itrg<32; itrg++){
       if(triggerenable[itrg+iword*32])
          trgenable |= 1<<itrg;
     }
     SetRENA(&trgenable,iword);
     if(fverbose) printf("setting trgena %d/%d to %08x\n", iword, nword, trgenable);
   }
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
   if(fverbose){
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
         printf(" DBGSERDES status %x \n",(*data&0x100)>>9);
      printf(" INBUSY status %x \n",(*data&0x2)>>1);
      printf(" EXBUSY status %x \n",(*data&0x8)>>3);
      printf(" ENABLE TRGBUS status %x \n",(*data&0x10)>>4);
      printf(" MASKBUSY status %x \n",(*data&0x2000)>>13);
      printf(" MASKSYNC status %x \n",(*data&0x4000)>>14);
      printf(" MASKTRG status %x \n",(*data&0x8000)>>15);
      printf(" IDCODE status %x \n",(*data&0xffff0000)>>16);
   }
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
   
   if (fverbose)
      if ((fidcode>>12)!=3)
         printf("setting TRGBus on TCB %4x!!!!!\n", fidcode);
   
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
  WriteReg(RSERDESVAL0,&valuedo);
  // then write [63:32]
  WriteReg(RSERDESVAL1,&valueup);
}
// get the transmission check word
void TCB::GetCheckWord() {
  u_int32_t data;
  // first read [31:0]
  ReadReg(RSERDESVAL0,&data);
  printf("Check word [31:0] = %08X\n",data);
  // then read [63:32]
  ReadReg(RSERDESVAL1,&data);
  printf("Check word [63:32] = %08X\n",data);

}

//configure a single serdes link
void TCB::ConfigureSingleSerdes(int serdes, int link, short dly, int bitslip){
   //evaluate serdes id number
   int linkid = 8*serdes+link;
   //correct configuration offset
   int addr = RSERDESCONF + linkid/4;
   u_int32_t data;

   //read back current config
   ReadReg(addr, &data);

   //reset reset
   data |= 0x80<< (linkid%4)*8;
   //printf("reset: %08x\n", data); //TODO: remove
   WriteReg(addr, &data);

   //reset serdes and write delay
   switch(linkid%4){
      case 0:
         data &= 0xFFFFFF00;
         break;
      case 1:
         data &= 0xFFFF00FF;
         break;
      case 2:
         data &= 0xFF00FFFF;
         break;
      case 3:
         data &= 0x00FFFFFF;
         break;
      default:
         break;
   }
   data |= ((0x20|(dly &0x1F)) << (linkid%4)*8);

   //printf("load config: %08x\n", data); //TODO: remove
   WriteReg(addr, &data);

   //load delay
   u_int32_t loadval;
   ReadReg(RSERDESTX, &loadval);
   loadval |= 0x80000000;
   WriteReg(RSERDESTX, &loadval);
   loadval &= 0x7FFFFFFF;
   WriteReg(RSERDESTX, &loadval);

   //bitslip
   addr = RSERDESBSLP + linkid/32;
   data = 1 << (linkid%32);
   //u_int32_t memval;
   //u_int32_t memaddr = MEMBASEADDR + serdes*2*MEMDIM + MEMDIM*(link/4);
   for (int i=0; i<bitslip; i++) {
      WriteReg(addr, &data);
      //printf("(%3x) %08x \n", addr, data);
      //ReadReg(memaddr, &memval);
      //      printf("current word(dly=%d bitsl=%d): %08x\n", dly, i, memval); //TODO: remove
   }
}
//configure a all serdes link
void TCB::ConfigureAllSerdes(short dly, int bitslip){
   //reset
   u_int32_t conf[32]={0};
   for(int ilink=0; ilink<8*fnserdes; ilink++){
      conf[ilink/4] |= 0x80 << (ilink%4)*8;
   }
   WriteBLT(RSERDESCONF, conf, fnserdes*8/4);

   //write config and enable
   for(int i=0; i<2*fnserdes; i++){
      conf[i] = 0;
   }
   for(int ilink=0; ilink<8*fnserdes; ilink++){
      conf[ilink/4] |= (0x20|(dly &0x1F)) << (ilink%4)*8;
   }
   WriteBLT(RSERDESCONF, conf, fnserdes*8/4);

   //load delay
   u_int32_t loadval;
   ReadReg(RSERDESTX, &loadval);
   loadval |= 0x80000000;
   WriteReg(RSERDESTX, &loadval);
   loadval &= 0x7FFFFFFF;
   WriteReg(RSERDESTX, &loadval);

   //bitslip
   u_int32_t data[4];
   for(int i=0; i<4; i++) data[i]=0xFFFFFFFF;
   //u_int32_t memval;
   //u_int32_t memaddr = MEMBASEADDR + serdes*2*MEMDIM + MEMDIM*(link/4);
   for (int i=0; i<bitslip; i++) {
      WriteBLT(RSERDESBSLP, data, 4);
      //WriteBLT(RSERDESBSLP, data, fnserdes/32 + (fnserdes%32!=0)?1:0);
      //printf("(%3x) %08x \n", addr, data);
      //ReadReg(memaddr, &memval);
      //printf("current word(dly=%d bitsl=%d): %08x\n", dly, i, memval); //TODO: remove
   }
}
//configure a all serdes link
void TCB::SetAllSerdes(u_int32_t *dlys, int *bits){
   u_int32_t conf[32]={0};

   for(int ilink=0; ilink<8*fnserdes; ilink++){
      conf[ilink/4] |= 0x80 << (ilink%4)*8;
   }
   WriteBLT(RSERDESCONF, conf, fnserdes*8/4);

   for(int i=0; i<32; i++)conf[i]=0;
   for(int ilink=0; ilink<2*fnserdes; ilink++){
      conf[ilink] |= (0x20202020|dlys[ilink]);
   }
   WriteBLT(RSERDESCONF, conf, fnserdes*8/4);

   //load delay
   u_int32_t loadval;
   ReadReg(RSERDESTX, &loadval);
   loadval |= 0x80000000;
   WriteReg(RSERDESTX, &loadval);
   loadval &= 0x7FFFFFFF;
   WriteReg(RSERDESTX, &loadval);

   u_int32_t data[4];
   bool morebits = true;
   while(morebits){
      morebits = false;
      for(int i=0; i<4; i++) data[i] = 0;
      for(int ilink=0; ilink<8*fnserdes; ilink++){
         if(bits[ilink]>0){
            bits[ilink]--;
            data[ilink/32] |= 1 << (ilink%32);
            morebits = true;
         }
      }
      WriteBLT(RSERDESBSLP, data, 4);
   }
}
//check errors on serdes
void TCB::ResetTransmitter(){
   u_int32_t val;
   ReadReg(RSERDESTX, &val);
   val |= 0x000000FF;
   WriteReg(RSERDESTX, &val);
   val &= 0xFFFFFF00;
   WriteReg(RSERDESTX, &val);
}
//check errors on serdes
void TCB::GetSerdesError(u_int32_t* data){
   ReadBLT(RSERDESCHECK, data, ceil(fnserdes/4.));
}
//check error count on serdes
void TCB::GetSerdesErrorCount(u_int32_t* data){
   ReadBLT(RSERDESCOU, data, fnserdes*2);
   ReadBLT(RSERDESCOU+fnserdes*2, data+fnserdes*2, fnserdes*2);
   ReadBLT(RSERDESCOU+fnserdes*4, data+fnserdes*4, fnserdes*2);
   ReadBLT(RSERDESCOU+fnserdes*6, data+fnserdes*6, fnserdes*2);

   ReadReg(RSERDESTIME, data + fnserdes*8);
}
//start a serdes check
void TCB::StartSerdesCheck(){
   u_int32_t enablevalue;
   ReadReg(RSERDESTX, &enablevalue);

   //reset
   enablevalue |= 0x40000000;
   WriteReg(RSERDESTX, &enablevalue);

   //enable
   enablevalue &= 0xBFFFFFFF;
   enablevalue |= 0x20000000;
   WriteReg(RSERDESTX, &enablevalue);
}
//stop a serdes check
void TCB::StopSerdesCheck(){
   u_int32_t enablevalue;
   ReadReg(RSERDESTX, &enablevalue);
   //remove counter enable
   enablevalue &= 0xDFFFFFFF;
   WriteReg(RSERDESTX, &enablevalue);
}
//calibrate serdes
void TCB::CalibrateSerdes(u_int32_t *dlyout, int *bitout){
         float errors[128][8][32];
         u_int32_t ccounters[129];

         //SetCheckWord(0xdeadbeef, 0xdeadbeef);

         for(int idly =0; idly<32; idly++){
            for(int ibit=0; ibit<8; ibit++){
               //configure everything
               ConfigureAllSerdes(idly, ibit);

               StartSerdesCheck();

               usleep(100);

               StopSerdesCheck();
               GetSerdesErrorCount(ccounters);
               for(int icounter=0; icounter<fnserdes*8; icounter++){
                  errors[icounter][ibit][idly] = ccounters[icounter]*1./ccounters[fnserdes*8];
               }
            }
         }

         //search eyes
         const float thr = 1e-20;
         u_int32_t dly[32] = {0};
         int bit[128];
         for(int icounter=0; icounter<fnserdes*8; icounter++){
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

            if(bestWidth > 0){
               if(fverbose) printf("Setting Serdes %2d Link %1d at delay %2d bitslip %d (width %3d)\n", icounter/8, icounter%8, (int)(bestCenter), bestBitslip, bestWidth);
               bit[icounter] = bestBitslip;
               dly[icounter/4] |= (((int)(bestCenter))&0x1F)<<(icounter%4)*8;
               //ConfigureSingleSerdes(icounter/8, icounter%8, (int)(bestCenter), bestBitslip);
            }
            else if(fverbose) printf("could not find eye for serdes %d, link%d\n", icounter/8, icounter%8);
         }

         if(dlyout!=0 && bitout!=0){
            memcpy(dlyout, dly, sizeof(u_int32_t)*32);
            memcpy(bitout, bit, sizeof(int)*128);
         }

         SetAllSerdes(dly, bit);

}
//Set/unset DBGSERDES
void TCB::SetDbgserdes(bool enable){
   u_int32_t data;
   ReadReg(RRUN, &data);
   if(enable){
        data |= 0x00000100;
   } else {
        data &= 0xFFFFFEFF;
   }
   WriteReg(RRUN, &data);
}
//Do a serdes Check according to serdesmask
int TCB::CheckSerdes(){
   u_int32_t data;
   ReadReg(RSERDESMSK, &data);

   //build masks
   u_int32_t errormask[4] = { 0 };
   for(int i=0; i<16; i++){
      int mask = 1<<i;
      if( data & mask ){
        //channel enable
        errormask[i/4] |= 0xFF << 8*(i%4);
      }
   }

   //SetCheckWord(0xdeadbeef, 0xdeadbeef);

   StartSerdesCheck();

   usleep(1000000);

   StopSerdesCheck();

   u_int32_t serdesstatus[4];
   GetSerdesError(serdesstatus);

   int ret = 1;

   for(int i=0; i<4; i++){
      if(serdesstatus[i] & errormask[i]){
         ret = 0;
      }
   }

   if(fverbose){
      if(!ret) printf("serdes tx check failed. Got status: %08x %08x %08x %08x\n", serdesstatus[0] & errormask[0], serdesstatus[1] & errormask[1], serdesstatus[2] & errormask[2], serdesstatus[3] & errormask[3]);
      else printf("serdes tx check succeeded\n");
   }

   return ret;
}

//Assign local bus to Packetizer
void TCB::SetPacketizerBus(bool state){
   u_int32_t data;
   ReadReg(RARBITER, &data);

   if(state){
      data |= 0x00000001;
      WriteReg(RARBITER, &data);
   } else {
      data &= 0xFFFFFFFE;
      WriteReg(RARBITER, &data);
   }
}

//Check local bus association 
bool TCB::GetPacketizerBus(){
   u_int32_t data;
   ReadReg(RARBITER, &data);
   // if state is 1 the bus is used by the packetizer
   return( (data & 0x1) == 1 );

}

//Enable Packetizer
void TCB::SetPacketizerEnable(bool state){
   u_int32_t data;
   ReadReg(RARBITER, &data);

   if(state){
      data |= 0x00000002;
      WriteReg(RARBITER, &data);
   } else {
      data &= 0xFFFFFFFD;
      WriteReg(RARBITER, &data);
   }
}

//Enable Packetizer
void TCB::SetPacketizerAutostart(bool state){
   u_int32_t data;
   ReadReg(RARBITER, &data);

   if(state){
      data |= 0x00000010;
      WriteReg(RARBITER, &data);
   } else {
      data &= 0xFFFFFFEF;
      WriteReg(RARBITER, &data);
   }
}

//Software Start for packetizer
void TCB::StartPacketizer(){
   u_int32_t data;
   ReadReg(RARBITER, &data);
   data |= 0x00000004;
   WriteReg(RARBITER, &data);
   data &= 0xFFFFFFF3;
   WriteReg(RARBITER, &data);
}

//force stop for packetizer
void TCB::AbortPacketizer(){
   u_int32_t data;
   ReadReg(RARBITER, &data);
   data |= 0x00000008;
   WriteReg(RARBITER, &data);
   data &= 0xFFFFFFF7;
   WriteReg(RARBITER, &data);
}

//Set Packetizer command
void TCB::SetPacketizerCommandAt(int offset, PACKETIZER_COMMAND cmd, u_int32_t arg0, u_int32_t arg1, u_int32_t opt){
   if(offset > PACKAGERSIZE) return;

   u_int32_t data;

   switch(cmd){
      case STOP:
         data = 0;
         WriteReg(PACKAGERBASE+offset, &data);
        break;
      case COPY:
         data = 0x10000000;
         WriteReg(PACKAGERBASE+offset, &data);
         WriteReg(PACKAGERBASE+offset+PACKAGERSIZE, &arg0);
         WriteReg(PACKAGERBASE+offset+2*PACKAGERSIZE, &arg1);
        break;
      case BLOCK_COPY:
         data = 0x20000000;
         data |= opt & 0xFFFF;
         WriteReg(PACKAGERBASE+offset, &data);
         WriteReg(PACKAGERBASE+offset+PACKAGERSIZE, &arg0);
         WriteReg(PACKAGERBASE+offset+2*PACKAGERSIZE, &arg1);
        break;
      case DIRECT_WRITE:
         data = 0x30000000;
         WriteReg(PACKAGERBASE+offset, &data);
         WriteReg(PACKAGERBASE+offset+PACKAGERSIZE, &arg0);
         WriteReg(PACKAGERBASE+offset+2*PACKAGERSIZE, &arg1);
        break; 
   }
}

//Read current buffer
void TCB::ReadBuffer(u_int32_t* ptr, int size, int offset){
   int read = 0;
   const int BLTSIZE = 32;
   while (read < size){
      if((size-read) > BLTSIZE){
         ReadBLT(BUFFERBASE+read+offset, ptr, BLTSIZE);
         ptr += BLTSIZE;
         read += BLTSIZE;
      } else {
         ReadBLT(BUFFERBASE+read+offset, ptr, (size-read));
         ptr += (size-read);
         read = size;
      }
   }
}

//Increment buffer pointer
void TCB::IncrementBufferPointer(){
   u_int32_t data = 0x00000001;
   WriteReg(BUFFERBASE+BUFFERSIZE, &data);
}

//Reset buffer logic
void TCB::ResetBufferLogic(){
   u_int32_t data = 0x00000002;
   WriteReg(BUFFERBASE+BUFFERSIZE, &data);
}

//Return current SPI buffer pointer
int TCB::GetSPIBufferPointer(){
   u_int32_t data;
   ReadReg(BUFFERBASE+BUFFERSIZE, &data);
   return data & 0xFF;
}

//Return current Packager buffer pointer
int TCB::GetPacketizerBufferPointer(){
   u_int32_t data;
   ReadReg(BUFFERBASE+BUFFERSIZE, &data);
   return (data >> 8) & 0xFF;
}

//Return current buffer busy state (bitmask)
u_int32_t TCB::GetBufferState(){
   u_int32_t data;
   ReadReg(BUFFERBASE+BUFFERSIZE, &data);
   return data >> 16;
}

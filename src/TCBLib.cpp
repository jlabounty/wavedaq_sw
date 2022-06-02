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

// general write register function
void TCB::WriteReg(u_int32_t addr, u_int32_t *data)
{
   if(fDCB != nullptr) {
      std::vector<unsigned int> vec(data, data+1);
      fDCB->WriteUDP(fslot, addr, vec);

   } else if( fh!=-1 ){
      int status;

      // before than writing we have to perform a byteswap
      u_int32_t wdata = ((*data&0xff)<<24) | ((*data&0xff00)<<8) | ((*data&0xff0000)>>8) | ((*data&0xff000000)>>24);
      status = mscb_write_mem(fh, fmscb_addr, fslot, addr, &wdata, sizeof(wdata));
      // print something only in case of error
      if (status != 1)
         printf("Error: status = %d\n", status);
   }
}

// general read register function
void TCB::ReadReg(u_int32_t addr, u_int32_t *data)
{
   if(fDCB != nullptr) {
      std::vector<unsigned int> vec = fDCB->ReadUDP(fslot, addr, 1);
      data[0] = vec[0];

   } else if( fh!=-1 ){
      char dbuf[1024];

      *data = 0;
      mscb_read_mem(fh, fmscb_addr, fslot, addr, &dbuf, 4);
      for (int i=0 ; i<4 ; i++)
         *data |= ((u_int32_t) dbuf[3-i]&0xff)<<(i*8); //"(i*8)" as a byte swap
   }
}

// general read register function
void TCB::ReadBLT(u_int32_t addr, u_int32_t *data, int nword)
{
   if(fDCB != nullptr) {
      std::vector<unsigned int> vec = fDCB->ReadUDP(fslot, addr, nword);
      std::copy(vec.begin(), vec.end(), data);

   } else if( fh!=-1 ){
      char dbuf[1024];

      mscb_read_mem(fh, fmscb_addr, fslot, addr, &dbuf, nword*4); //4*nword: it is in number of bytes
      for (int iword=0 ; iword<nword ; iword++)  {
         data[iword] = 0;
         for(int ibyte = 0; ibyte<4; ibyte++)
            data[iword] |= ((u_int32_t) dbuf[(iword*4+3)-ibyte]&0xff)<<(ibyte*8); //"(i*8)" as a byte swap
      }
   }
}

// general write register function
void TCB::WriteBLT(u_int32_t addr, u_int32_t *data, int nword)
{
   if(fDCB != nullptr) {
      std::vector<unsigned int> vec(data, data+nword);
      fDCB->WriteUDP(fslot, addr, vec);

   } else if( fh!=-1 ){
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
}
// prescaling values setting
void TCB::SetPrescaling(u_int32_t *presca)
{
  int NBLT = (fntrg-1)/BLTSIZE + 1;
  int addr = RPRESCA;
  if ((fidcode>>12)!=3) {
     printf("setting prescaling on TCB %4x!!!!! skipped\n", fidcode);
     return;
  }   // now loop to write prescaling values
  for (int iblt = 0; iblt<NBLT; iblt++) {
    WriteBLT(addr+(iblt*BLTSIZE),presca+(iblt*BLTSIZE), BLTSIZE);
  }
}
// read prescaling values
void TCB::GetPrescaling(u_int32_t *presca)
{
   //read loop on prescaling registers
  int NBLT = (fntrg-1)/BLTSIZE+1;
  int addr = RPRESCA;
  if ((fidcode>>12)!=3) {
     printf("getting prescaling on TCB %4x!!!!! skipped\n", fidcode);
     return;
  }   // now loop to read prescaling values
  for (int iblt = 0; iblt<NBLT; iblt++) {
    ReadBLT(addr+(iblt*BLTSIZE),presca+(iblt*BLTSIZE), BLTSIZE);
  }
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
   else if((fidcode>>12)==3) {
     fnserdes = 16;
     fexpid = fidcode&0xF;
   }
}

//Set IDCode by accessing to rrun register
void TCB::SetBoardId(u_int32_t boardid, u_int32_t crateid, u_int32_t slotid)
{
   u_int32_t data = 0;
   data |= (crateid & 0xFF) << 24;
   data |= (slotid & 0xFF) << 16;
   data |= (boardid & 0xFFFF) << 0;

   WriteReg(RBOARDID, &data);
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
   int NBLT = MEMDIM/BLTSIZE;

   // now loop to write the memory cells
   for (int iblt = 0; iblt<NBLT; iblt++) {
      ReadBLT(addr+(iblt*BLTSIZE),data+(iblt*BLTSIZE), BLTSIZE);
   }
}

// Fill a memory with a given word
void TCB::FillMemory(unsigned int address, unsigned int len, unsigned int val)
{
   // now loop to write the memory cells
   for (unsigned int icell = 0; icell<len; icell++) {
      WriteReg(address+icell, &val);
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
}
// read the RENA register
void TCB::GetRENA(u_int32_t *data, int iword)
{
  u_int32_t addr = RENA + iword;
  ReadReg(addr,data);
}

// read the RALGSEL register
void TCB::GetRALGSEL(u_int32_t *data)
{
  u_int32_t addr = RALGSEL;
  ReadReg(addr,data);
}

// read total time
void TCB::GetTotalTime(u_int32_t *data)
{
   u_int32_t addr = RTOTTIME;
   ReadReg(addr,data);
}

// read total time through SPI
void TCB::GetTotalTimeSPI(u_int32_t *data)
{
  u_int32_t latch = 1;
  WriteReg(RLATCHCOUSPI,&latch);
  u_int32_t addr = RTOTTIMESPI;
  ReadReg(addr,data);
}

// read live time
void TCB::GetLiveTime(u_int32_t *data)
{
   u_int32_t addr = RLIVETIME;
   ReadReg(addr,data);
}

// read live time through SPI
void TCB::GetLiveTimeSPI(u_int32_t *data)
{
  u_int32_t latch = 1;
  WriteReg(RLATCHCOUSPI,&latch);
  u_int32_t addr = RLIVETIMESPI;
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
bool TCB::GetSystemTriggerType(u_int32_t *type, u_int32_t *readoutenable, u_int32_t *adcenable)
{
   u_int32_t addr = RSYSTRITYPE;
   u_int32_t data;
   ReadReg(addr,&data);
   //extract trigger type
   *type = data&0xffff;
   *readoutenable = (data>>24)&0x3F;
   *adcenable = (data>>30)&0x1;

   if(data&0x80000000) return false;
   else return true;
}
// read trigger counters
void TCB::GetTriggerCounters(u_int32_t *data)
{
    int ncycle = (fntrg-1)/BLTSIZE + 1;
    for(int icycle = 0; icycle<ncycle; icycle++)
      ReadBLT(RTRGCOU+icycle*BLTSIZE,data+icycle*BLTSIZE,BLTSIZE);
}
// read trigger counters trhough SPI
void TCB::GetTriggerCountersSPI(u_int32_t *data)
{
  u_int32_t latch = 1;
  WriteReg(RLATCHCOUSPI,&latch);
  int ncycle = (fntrg-1)/BLTSIZE + 1;
  for(int icycle = 0; icycle<ncycle; icycle++)
    ReadBLT(RTRGCOUSPI+icycle*BLTSIZE,data+icycle*BLTSIZE,BLTSIZE);
}
// read trigger counters, total time and live time through SPI
void TCB::ReadCounters(u_int32_t *data)
{
  u_int32_t latch = 1;
  WriteReg(RLATCHCOUSPI,&latch);
  int ncycle = (fntrg-1)/BLTSIZE + 1;
  for(int icycle = 0; icycle<ncycle; icycle++)
    ReadBLT(RTRGCOUSPI+icycle*BLTSIZE,data+icycle*BLTSIZE,BLTSIZE);
  // then totaltime
  ReadReg(RTOTTIMESPI,data+64);
  // finally livetime
  ReadReg(RLIVETIMESPI,data+65);

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
//check errors on serdes
void TCB::ResetIDLYCTRL(){
   u_int32_t val;
   ReadReg(RSERDESTX, &val);
   val |= 0x00000100;
   WriteReg(RSERDESTX, &val);
   val &= 0xFFFFFEFF;
   WriteReg(RSERDESTX, &val);
}
//check errors on serdes
void TCB::ResetTransmitter(){
   u_int32_t val;
   ReadReg(RSERDESTX, &val);
   val |= 0x000100FF;
   WriteReg(RSERDESTX, &val);
   val &= 0xFFFEFF00;
   WriteReg(RSERDESTX, &val);
}
//Set/unset Serdes Pattern
void TCB::SetSerdesPattern(bool enable){
   u_int32_t data;
   ReadReg(RRUN, &data);
   if(enable){
        data |= 0x00000200;
   } else {
        data &= 0xFFFFFDFF;
   }
   WriteReg(RRUN, &data);
}
//Set/unset FadcMode bit
void TCB::SetFadcMode(bool enable){
   u_int32_t data;
   ReadReg(RRUN, &data);
   if(enable){
        data |= 0x00000004;
   } else {
        data &= 0xFFFFFFFB;
   }
   WriteReg(RRUN, &data);
}
//Set/unset TestTx bit
void TCB::SetTestTxMode(bool enable){
   u_int32_t data;
   ReadReg(RRUN, &data);
   if(enable){
        data |= 0x00000020;
   } else {
        data &= 0xFFFFFFDF;
   }
   WriteReg(RRUN, &data);
}
//Set/unset TRGBus Flags
void TCB::SetTRGBusMasks(bool trg, bool sync, bool busy){
   u_int32_t data;
   ReadReg(RRUN, &data);
   if(trg){
        data |= 0x00008000;
   } else {
        data &= 0xFFFF7FFF;
   }
   if(sync){
        data |= 0x00004000;
   } else {
        data &= 0xFFFFBFFF;
   }
   if(sync){
        data |= 0x00002000;
   } else {
        data &= 0xFFFFDFFF;
   }
   WriteReg(RRUN, &data);
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

//Autostart Packetizer
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
      case JUMP:
         data = 0x40000000;
         data |= opt & 0xFFFF;
         WriteReg(PACKAGERBASE+offset, &data);
         WriteReg(PACKAGERBASE+offset+PACKAGERSIZE, &arg0);
         WriteReg(PACKAGERBASE+offset+2*PACKAGERSIZE, &arg1);
        break; 
      case JUMP_IF:
         data = 0x50000000;
         data |= opt & 0xFFFF;
         WriteReg(PACKAGERBASE+offset, &data);
         WriteReg(PACKAGERBASE+offset+PACKAGERSIZE, &arg0);
         WriteReg(PACKAGERBASE+offset+2*PACKAGERSIZE, &arg1);
        break; 
   }
}

//Enable ReadoutFSM
void TCB::SetReadoutEnable(bool state){
   u_int32_t data;
   ReadReg(RARBITER, &data);

   if(state){
      data |= 0x00000020;
      WriteReg(RARBITER, &data);
   } else {
      data &= 0xFFFFFFDF;
      WriteReg(RARBITER, &data);
   }
}

void TCB::SetMaxPayload(u_int32_t *data){
   WriteReg(RPAYLOADMAX, data);
}

//Read current buffer
void TCB::ReadBuffer(u_int32_t* ptr, int size, int offset){
   int read = 0;
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

//Reset PLLs
void TCB::ResetPLLs(){
   u_int32_t data = 0x00000001;
   WriteReg(RPLLRES, &data);
}

//Read the PLL unlock counter PLLs
void TCB::GetPLLUnlockCou(u_int32_t *data){
   ReadReg(RPLLRES, data);
}

//Reset PLLs
void TCB::ResetPLLUnlockCou(){
   u_int32_t data = 0x00000002;
   WriteReg(RPLLRES, &data);
}
// set trigger delay
void TCB::SetTRGDLY(bool* enable, u_int32_t *dly){
  int NBLT = (fntrg-1)/BLTSIZE+1;
  int addr = RTRGDLY;
  if ((fidcode>>12)!=3) {
     printf("setting trigger delays on TCB %4x!!!!! skipped\n", fidcode);
     return;
  }   // now loop to write trigger delay values

  //populate the enable bit
  for(int itrg=0; itrg<fntrg; itrg++){
      if(enable[itrg])
         dly[itrg] |= 0x20;
  }

  for (int iblt = 0; iblt<NBLT; iblt++) {
    WriteBLT(addr+(iblt*BLTSIZE),dly+(iblt*BLTSIZE), BLTSIZE);
  }
}
// get trigger delay
void TCB::GetTRGDLY(u_int32_t *dly){
  int NBLT = (fntrg-1)/BLTSIZE+1;
  int addr = RTRGDLY;
  if ((fidcode>>12)!=3) {
     printf("getting trigger delays on TCB %4x!!!!! skipped\n", fidcode);
     return;
  }   // now loop to read trigger delay values
  for (int iblt = 0; iblt<NBLT; iblt++) {
    ReadBLT(addr+(iblt*BLTSIZE),dly+(iblt*BLTSIZE), BLTSIZE);
  }
}
// set adc prescaling readout
void TCB::SetPrescAdc(u_int32_t *val){
   WriteReg(PRESCADC, val);
  }
// set adc prescaling readout
void TCB::GetPrescAdc(u_int32_t *val){
   ReadReg(PRESCADC, val);
  }
//Start AutoCalibration of Serdes
void TCB::AutoCalibrateSerdes(){
   u_int32_t val = 0x80000000;
   WriteReg(RSERDESCALIBFSM, &val);
}
//Read Current Serdes Configuration
void TCB::ReadCurrentSerdes(u_int32_t *dlyout, int *bitout){
   u_int32_t serdesconf[2*16];

   ReadBLT(RSERDESSTATUS, serdesconf, fnserdes*2);

   for(int iConf=0; iConf< fnserdes*2; iConf++){
      dlyout[iConf] = serdesconf[iConf] & 0x1F1F1F1F;
      bitout[iConf*4] = (serdesconf[iConf] >> 5) & 0x7;
      bitout[iConf*4+1] = (serdesconf[iConf] >> (5+8)) & 0x7;
      bitout[iConf*4+2] = (serdesconf[iConf] >> (5+16)) & 0x7;
      bitout[iConf*4+3] = (serdesconf[iConf] >> (5+24)) & 0x7;
   }
}
//Get AutoLock Fail
void TCB::GetAutoCalibrateFail(u_int32_t* ret){
   ReadReg(RSERDESFAIL, ret);
}
//Get AutoLock Busy
void TCB::GetAutoCalibrateBusy(u_int32_t* ret){
   ReadReg(RSERDESBUSY, ret);
}
void TCB::GetAutoCalibrateEye(u_int32_t* eyes){
   u_int32_t tx_conf =0;
   ReadReg(RSERDESTX, &tx_conf);
   u_int32_t tx_conf_new = tx_conf | 0x00000200; //set CALIBMASK to force full scan
   WriteReg(RSERDESTX, &tx_conf_new);
   
   AutoCalibrateSerdes();
   usleep(1000000);

   ReadBLT(RSERDESDLYSTATE, eyes, fnserdes);
   tx_conf &= 0xFFFFFDFF;
   WriteReg(RSERDESTX, &tx_conf);
}
//Returns enable value for latency compensations of SerDes
void TCB::GetAutoAlignDlys(u_int32_t* ret){
   ReadReg(RSERDESALIGNDLY, ret);
}
void TCB::SetSingleCrateConfiguration(bool useGlobalAnd, short shape, short vetoShape){
   u_int32_t val = 0;
   val |= (shape & 0x1F);
   val |= (vetoShape & 0x1F)<<8;
   val |= (useGlobalAnd & 0x1)<<16;
   
   WriteReg(RSINGLECRATECFG, &val);
}
void TCB::SetSingleCrateChnMask(bool *state){
   u_int32_t val[8] = {0, 0, 0, 0, 0, 0, 0, 0};
   for(int i=0; i<256; i++){
      if(state[i]) val[i/32] |= ( 1 << (i%32));
   }

   WriteBLT(RSINGLEMASK, val, 8);
}
void TCB::SetSingleCrateChnIsVeto(bool *state){
   u_int32_t val[8] = {0, 0, 0, 0, 0, 0, 0, 0};
   for(int i=0; i<256; i++){
      if(state[i]) val[i/32] |= ( 1 << (i%32));
   }

   WriteBLT(RSINGLEISVETO, val, 8);
}
void TCB::SetSingleCrateChnLogic(bool *state){
   u_int32_t val[4] = {0, 0, 0, 0};
   for(int i=0; i<128; i++){
      if(state[i]) val[i/32] |= ( 1 << (i%32));
   }

   WriteBLT(RSINGLELOGIC, val, 4);
}
void TCB::SetSingleCrateTriggerOr(int nChn, int* chn, short shape){
   SetSingleCrateConfiguration(false, shape, shape);
   bool arr[256];
   for(int i=0; i<256; i++) arr[i]=false;
   SetSingleCrateChnIsVeto(arr);
   for(int i=0; i<256; i++) arr[i]=true;
   for(int i=0; i<nChn; i++) arr[chn[i]]=false;
   SetSingleCrateChnMask(arr);
   for(int i=0; i<256; i++) arr[i]=false;
   SetSingleCrateChnLogic(arr);
}
void TCB::SetSingleCrateTriggerAnd(int nChn, int* chn, short shape){
   SetSingleCrateConfiguration(true, shape, shape);
   bool arr[256];
   for(int i=0; i<256; i++) arr[i]=true;
   for(int i=0; i<nChn; i++) arr[chn[i]]=false;
   SetSingleCrateChnIsVeto(arr);
   for(int i=0; i<256; i++) arr[i]=true;
   for(int i=0; i<nChn; i++) arr[chn[i]]=false;
   SetSingleCrateChnMask(arr);
   for(int i=0; i<256; i++) arr[i]=true;
   SetSingleCrateChnLogic(arr);
}
//Set trigger and busy masks from external DAQ system
void TCB::SetFMask(bool trgmask, bool busymask){
   u_int32_t data;
   // first read the register
   ReadReg(RRUN, &data);
   // mask fmasks
   data &= 0xFFFFFF3F;
   // set trigger mask if required
   if(trgmask)
     data |= 1<<6;
   // set busy mask if required
   if(busymask)
     data |= 1<<7;
   // write the reg
   WriteReg(RRUN, &data);
}
//Enables Local trigger
void TCB::SetLocalTrigger(bool ena){
   u_int32_t data;
   // first read the register
   ReadReg(RRUN, &data);
   // mask fmasks
   data &= 0xFFFFF7FF;
   // set trigger mask if required
   if(ena)
     data |= 1<<11;
   // write the reg
   WriteReg(RRUN, &data);
}
//write full Packetizer program
void TCB::WritePacketizerProgram(std::vector<PacketInstruction> &list){
   u_int32_t pack_mem_0[PACKAGERSIZE];
   u_int32_t pack_mem_1[PACKAGERSIZE];
   u_int32_t pack_mem_2[PACKAGERSIZE];
   for(uint64_t i=0; i<PACKAGERSIZE; i++){
      pack_mem_0[i] = 0;
      pack_mem_1[i] = 0;
      pack_mem_2[i] = 0;
   }

   uint64_t max_offset = 0;

   for(uint64_t i=0; i<list.size(); i++){
      if(list[i].offset >= PACKAGERSIZE){
         printf("Packager script out of bundaries!\n");
         return;
      } else if (list[i].offset > max_offset) 
         max_offset = list[i].offset; 
      
      switch(list[i].cmd){
      case STOP:
         pack_mem_0[list[i].offset] = 0;
         break;
      case COPY:
         pack_mem_0[list[i].offset] = 0x10000000;
         pack_mem_1[list[i].offset] = list[i].arg0;
         pack_mem_2[list[i].offset] = list[i].arg1;
         break;
      case BLOCK_COPY:
         pack_mem_0[list[i].offset] = (0x20000000 | (list[i].arg2 & 0xFFFF));
         pack_mem_1[list[i].offset] = list[i].arg0;
         pack_mem_2[list[i].offset] = list[i].arg1;
         break;
      case DIRECT_WRITE:
         pack_mem_0[list[i].offset] = 0x30000000;
         pack_mem_1[list[i].offset] = list[i].arg0;
         pack_mem_2[list[i].offset] = list[i].arg1;
         break; 
      case JUMP:
         pack_mem_0[list[i].offset] = (0x40000000 | (list[i].arg2 & 0xFFFF));
         pack_mem_1[list[i].offset] = 0;
         pack_mem_2[list[i].offset] = 0;
         break; 
      case JUMP_IF:
         pack_mem_0[list[i].offset] = (0x50000000 | (list[i].arg2 & 0xFFFF));
         pack_mem_1[list[i].offset] = list[i].arg0;
         pack_mem_2[list[i].offset] = list[i].arg1;
         break; 
      }
   }

   /*for(int i=0; i<=max_offset; i++){
      printf("%08x %08x %08x\n", pack_mem_0[i], pack_mem_1[i], pack_mem_2[i]);
   }*/
   int NBLT = (max_offset > 0)? (max_offset-1)/BLTSIZE + 1: 1;
   for (int iblt = 0; iblt<NBLT; iblt++) {
      WriteBLT(PACKAGERBASE+(iblt*BLTSIZE), pack_mem_0+(iblt*BLTSIZE), BLTSIZE);
      WriteBLT(PACKAGERBASE+(iblt*BLTSIZE)+PACKAGERSIZE, pack_mem_1+(iblt*BLTSIZE), BLTSIZE);
      WriteBLT(PACKAGERBASE+(iblt*BLTSIZE)+2*PACKAGERSIZE, pack_mem_2+(iblt*BLTSIZE), BLTSIZE);
   }
   
}
//Get Current Buffer Head
u_int32_t TCB::GetBufferHeadSPI(int *nBanks, u_int32_t *evecou, u_int32_t* totaltime, u_int32_t* sys_tritype, u_int32_t* sys_evecou){
   u_int32_t data[5];
   ReadBuffer(data, 5);

   *nBanks = data[0];
   if(evecou) *evecou = data[1];
   if(totaltime) *totaltime = data[2];
   if(sys_tritype) *sys_tritype = data[3];
   if(sys_evecou) *sys_evecou = data[4];

   return 5;
}
//Check current bank
bool TCB::HasBufferBankSPI(u_int32_t ptr, char *bankName, int *length){
   u_int32_t data[2];
   ReadBuffer(data, 2, ptr);
   bankName[3] = data[0]&0xFF;
   bankName[2] = (data[0]>>8)&0xFF;
   bankName[1] = (data[0]>>16)&0xFF;
   bankName[0] = (data[0]>>24)&0xFF;

   *length = data[1];

   return (data[0] != 0);
}
//Skip Bank
u_int32_t TCB::SkipBufferBankSPI(u_int32_t ptr, int length){
   return ptr+2+length;
}
//Read Bank
void TCB::GetBufferBankDataSPI(u_int32_t ptr, u_int32_t *data, int length){
//   int iword;
//   for (iword = 0; iword+BLTSIZE<length; iword+=BLTSIZE) {
//      ReadBLT(ptr+2+iword,data+iword, BLTSIZE);
//   }
//   ReadBLT(ptr+2+iword,data+iword, length-(BLTSIZE*iword));
   ReadBuffer(data, length, ptr+2);
}
//get SYNC waveform
void TCB::GetSyncWaveform(u_int32_t *ptr){
   ReadReg(RSYNCWFM, ptr); 
}
//reset SYNC waveform serdes
void TCB::ResetSyncWaveformSerdes(){
   u_int32_t data = 0x80000000;
   WriteReg(RSYNCWFM, &data); 
}

// detector delays
void TCB::SetDetectorDelay(bool *enable, u_int32_t* value){
   if ((fidcode>>12)!=3) printf("setting Detector delays on TCB %4x!!!!!\n", fidcode);
   else if (!(fexpid&0x1)) printf("TCB not compiled for MEG !!!!!\n");
   
   u_int32_t dly0 = 0;
   u_int32_t dly1 = 0;
   for(int iDly=0; iDly<6; iDly++){
      if(iDly <= 3){
         dly0 |= (value[iDly] & 0x1F) << (8*iDly);
         if(enable[iDly]) dly0 |= 0x1 << (8*iDly+5);
      } else {
         dly1 |= (value[iDly] & 0x1F) << (8*(iDly-4));
         if(enable[iDly]) dly1 |= 0x1 << (8*(iDly-4)+5);
      }
   }
   WriteReg(RDETECTORDLY0, &dly0);
   WriteReg(RDETECTORDLY1, &dly1);
}

// detector tdc delays
void TCB::SetTdcDelay(bool *enable, u_int32_t* value){
   if ((fidcode>>12)!=3) printf("setting Tdc delays on TCB %4x!!!!!\n", fidcode);
   else if (!(fexpid&0x1)) printf("TCB not compiled for MEG !!!!!\n");
   
   u_int32_t dly = 0;
   for(int iDly=0; iDly<2; iDly++){
      dly |= (value[iDly] & 0x1F) << (8*iDly);
      if(enable[iDly]) dly |= 0x1 << (8*iDly+5);
   }
   WriteReg(RTDCDLY, &dly);
}

// detector tdc delays
void TCB::SetCombinedConditionDelay(bool *enable, u_int32_t* value){
   if ((fidcode>>12)!=3) printf("setting Combined Conditon delays on TCB %4x!!!!!\n", fidcode);
   else if (!(fexpid&0x1)) printf("TCB not compiled for MEG !!!!!\n");
   
   u_int32_t dly = 0;
   for(int iDly=0; iDly<2; iDly++){
      dly |= (value[iDly] & 0x1F) << (8*iDly);
      if(enable[iDly]) dly |= 0x1 << (8*iDly+5);
   }
   WriteReg(RCOMBDLY, &dly);
}

// waveform sum threshold
void TCB::SetSumHighThreshold(u_int32_t *data)
{
   if ((fidcode>>12)!=3) printf("setting QSUM High Threshold on TCB %4x!!!!!\n", fidcode);
   else if (!(fexpid&0x1)) printf("TCB not compiled for MEG !!!!!\n");
   WriteReg(RQHTHR,data);
}
void TCB::SetSumLowThreshold(u_int32_t *data)
{
   if ((fidcode>>12)!=3) printf("setting QSUM Low Threshold on TCB %4x!!!!!\n", fidcode);
   else if (!(fexpid&0x1)) printf("TCB not compiled for MEG !!!!!\n");
   WriteReg(RQLTHR,data);
}
void TCB::SetSumVetoThreshold(u_int32_t *data)
{
  if ((fidcode>>12)!=3) printf("setting QSUM Veto Threshold on TCB %4x!!!!!\n", fidcode);
   else if (!(fexpid&0x1)) printf("TCB not compiled for MEG !!!!!\n");
   WriteReg(RQCTHR,data);
}
void TCB::SetPatch(u_int32_t *data)
{
   if ((fidcode>>12)!=3) printf("setting LXe Pacth Value on TCB %4x!!!!!\n", fidcode);
   else if (!(fexpid&0x1)) printf("TCB not compiled for MEG !!!!!\n");
   WriteReg(RLXePATCHID,data);
}
void TCB::SetPatchThreshold(u_int32_t *data)
{
  if ((fidcode>>12)!=3) printf("setting Threshold on TCB %4x!!!!!\n", fidcode);
  else if (!(fexpid&0x1)) printf("TCB not compiled for MEG !!!!!\n");
  WriteReg(RLXeHITTHR,data);
}
void TCB::SetPatchDelay(bool enable, u_int32_t data)
{
  if ((fidcode>>12)!=3) printf("setting Threshold on TCB %4x!!!!!\n", fidcode);
  else if (!(fexpid&0x1)) printf("TCB not compiled for MEG !!!!!\n");

  u_int32_t val = data & 0x1F;
  if(enable){
     val |= 0x20;
  }
  WriteReg(RLXePATCHDLY,&val);
}
// time windows
void TCB::SetTimeNarrow(u_int32_t *data){
   if ((fidcode>>12)!=3) printf("setting Narrow Time Threshold on TCB %4x!!!!!\n", fidcode);
   else if (!(fexpid&0x1)) printf("TCB not compiled for MEG !!!!!\n");
   WriteReg(RTIMEN,data);
}
void TCB::SetTimeWide(u_int32_t *data){
   if ((fidcode>>12)!=3) printf("setting Wide Time Threshold on TCB %4x!!!!!\n", fidcode);
   else if (!(fexpid&0x1)) printf("TCB not compiled for MEG !!!!!\n");
   WriteReg(RTIMEW,data);
}
//Alpha configuration
void TCB::SetAlphaThreshold(u_int32_t *data)
{
   if ((fidcode>>12)!=2) printf("setting Alpha on TCB %4x!!!!!\n", fidcode);
   WriteReg(RALPHATHR,data);
}
void TCB::SetAlphaPeakScale(float value)
{
   u_int32_t data;
   data = static_cast<u_int32_t>(value*(1<<10));
   if ((fidcode>>12)!=2) printf("setting Alpha on TCB %4x!!!!!\n", fidcode);
   
   WriteReg(RALPHAPEAK,&data);
}
void TCB::SetQsumMovingAverage(bool enable)
{
   if ((fidcode>>12)!=3) printf("setting QSUM select on TCB %4x!!!!!\n", fidcode);
   else if (!(fexpid&0x1)) printf("TCB not compiled for MEG !!!!!\n");

   u_int32_t data = 0;
   ReadReg(RQSUMSEL,&data);
   if(enable){
      data |= 1;
   } else {
      data &= 0xFFFFFFFE;
   }
   WriteReg(RQSUMSEL,&data);
}
void TCB::SetQsumPMTMultiplier(int value)
{
   if ((fidcode>>12)!=3) printf("setting QSUM select on TCB %4x!!!!!\n", fidcode);
   else if (!(fexpid&0x1)) printf("TCB not compiled for MEG !!!!!\n");

   u_int32_t data = 0;
   ReadReg(RQSUMSEL,&data);
   data &= 0xFFFFFFCF;
   if(value == 4){
      data |= 1<<5;
   } else if(value == 2) {
      data |= 1<<4;
   }
   WriteReg(RQSUMSEL,&data);
}

// TC Masks
void TCB::SetTCMasks(u_int32_t *data)
{
   if ((fidcode>>12)!=1) printf("setting Tile Masks on TCB %4x!!!!!\n", fidcode);
   WriteReg(RTILEMSK0,data);
   WriteReg(RTILEMSK1,data+1);
   WriteReg(RTILEMSK2,data+2);
   WriteReg(RTILEMSK3,data+3);
}
// TC Multiplicity
void TCB::SetTCMultiplicityThreshold(u_int32_t *data)
{
   if ((fidcode>>12)!=3) printf("setting TC Multiplicity on TCB %4x!!!!!\n", fidcode);
   else if (!(fexpid&0x1)) printf("TCB not compiled for MEG !!!!!\n");
   WriteReg(RTCMULTITHR,data);
}
// TC Crate Hit Merge
void TCB::SetTCCrateMergeThreshold(u_int32_t *low, u_int32_t* high)
{
   if ((fidcode>>12)!=1) printf("setting Crate TC Hit Merge on TCB %4x!!!!!\n", fidcode);
   WriteReg(RTCTRACKMULTTHR,low);
   WriteReg(RTCTARCKTIMETHR,high);
}
// TC Crate Hit Merge
void TCB::SetTCSectorMergeThreshold(u_int32_t *low, u_int32_t* high)
{
   if ((fidcode>>12)!=2) printf("setting Crate TC Hit Merge on TCB %4x!!!!!\n", fidcode);
   WriteReg(RTCTRACKMULTTHR,low);
   WriteReg(RTCTARCKTIMETHR,high);
}
// TC Time offset wrt XEC
void TCB::SetTCTimeOffset(u_int32_t *value)
{
   if ((fidcode>>12)!=3) printf("setting Crate TC Time Offset on TCB %4x!!!!!\n", fidcode);
   WriteReg(RTCOFFSET,value);
}
// TC Track masks
void TCB::SetTCTrackMask(u_int32_t *value)
{
   if ((fidcode>>12)!=3) printf("setting Crate TC Track Mask on TCB %4x!!!!!\n", fidcode);
   WriteReg(RTCTRACKMASK,value);
}
// BGO QSUM Threshold
void TCB::SetBGOThreshold(u_int32_t *data)
{
   if ((fidcode>>12)!=1) printf("setting BGO Threshold on TCB %4x!!!!!\n", fidcode);
   WriteReg(RBGOTHR,data);
}
// Trigger mask enable for BGO  trigger definition
void TCB::SetBGOTriggerMask(u_int32_t *data)
{
   if ((fidcode>>12)!=1) printf("setting BGO Mask on TCB %4x!!!!!\n", fidcode);
   WriteReg(RBGOMASK,data);
}
// BGO QSUM Veto Threshold
void TCB::SetBGOVetoThreshold(u_int32_t *data)
{
   if ((fidcode>>12)!=1) printf("setting BGO Veto Threshold on TCB %4x!!!!!\n", fidcode);
   WriteReg(RBGOVETOTHR,data);
}
// BGO Hit Delay
void TCB::SetBGOHitDelay(u_int32_t data, u_int32_t veto_data)
{
   if ((fidcode>>12)!=1) printf("setting BGO Hit delay on TCB %4x!!!!!\n", fidcode);
   u_int32_t val = data & 0x1F;
   val |= (veto_data & 0x1F) << 8;
   WriteReg(RBGOHITDLY,&val);
}
// RDC QSUM Threshold
void TCB::SetRDCThreshold(u_int32_t *data)
{
   if ((fidcode>>12)!=1) printf("setting RDC Threshold on TCB %4x!!!!!\n", fidcode);
   WriteReg(RRDCLYSOTHR,data);
}
// RDC QSUM Veto Threshold
void TCB::SetRDCVetoThreshold(u_int32_t *data)
{
   if ((fidcode>>12)!=1) printf("setting RDC Veto Threshold on TCB %4x!!!!!\n", fidcode);
   WriteReg(RRDCVETOTHR,data);
}
// RDC Hit Delay
void TCB::SetRDCHitDelay(u_int32_t *data)
{
   if ((fidcode>>12)!=1) printf("setting RDC Hit Delay on TCB %4x!!!!!\n", fidcode);
   WriteReg(RRDCHITDLY,data);
}
// RDC Hit Mask
void TCB::SetRDCHitMask(u_int32_t *data)
{
   if ((fidcode>>12)!=1) printf("setting RDC Hit Mask on TCB %4x!!!!!\n", fidcode);
   WriteReg(RRDCHITMASK0,data);
   WriteReg(RRDCHITMASK1,data+1);
   WriteReg(RRDCHITMASK2,data+2);
}
// Trigger mask enable for RDC  trigger definition
void TCB::SetRDCTriggerMask(u_int32_t *data)
{
   if ((fidcode>>12)!=1) printf("setting RDC Mask on TCB %4x!!!!!\n", fidcode);
   WriteReg(RRDCMASK,data);
}
// set CRC bar masking 
void TCB::SetCRCHitMask(u_int32_t *data)
{
   if ((fidcode>>12)!=1) printf("setting CRC Hit Mask on TCB %4x!!!!!\n", fidcode);
   WriteReg(RCRCHITMASK,data);
}
// set CRC pair enable
void TCB::SetCRCPairEnable(u_int32_t *data)
{
   if ((fidcode>>12)!=1) printf("setting CRC Pair Enable on TCB %4x!!!!!\n", fidcode);
   WriteReg(RCRCPAIRENA,data);
}
// set NGEN widow delay
void TCB::SetNGENDly(u_int32_t *data){
   if ((fidcode>>12)!=1) printf("setting NGEN delay on TCB %4x!!!!!\n", fidcode);
   WriteReg(RNGENDLY,data);
}
// set NGEN widow width
void TCB::SetNGENWidth(u_int32_t *data){
   if ((fidcode>>12)!=1) printf("setting NGEN width on TCB %4x!!!!!\n", fidcode);
   WriteReg(RNGENWIDTH,data);
}
// set NGEN LXe High threshold
void TCB::SetNGENHighThreshold(u_int32_t *data){
   if ((fidcode>>12)!=3) printf("setting NGEN delay on TCB %4x!!!!!\n", fidcode);
   WriteReg(RLXeNGENQH,data);
}
// set NGEN LXe Low threshold
void TCB::SetNGENLowThreshold(u_int32_t *data){
   if ((fidcode>>12)!=3) printf("setting NGEN delay on TCB %4x!!!!!\n", fidcode);
   WriteReg(RLXeNGENQL,data);
}
// set CDCH wire masks
void TCB::SetCDCHMasks(u_int32_t *data){
   if ((fidcode>>12)!=1) printf("setting CDCH masks on TCB %4x!!!!!\n", fidcode);
   for(int iMask = 0; iMask<8; iMask++) {
     WriteReg(RCDCHMASKS0+iMask,data+iMask);
   }
}
// set CDCH trigger mask
void TCB::SetCDCHTriggerMask(u_int32_t *data){
   if ((fidcode>>12)!=3) printf("setting CDCH trigger mask on TCB %4x!!!!!\n", fidcode);
   WriteReg(RCDCHTRGMASK,data);
}
// set CDCH US hits multiplicity threshold
void TCB::SetCDCHUSMultThr(u_int32_t *data){
   if ((fidcode>>12)!=3) printf("setting CDCH masks on TCB %4x!!!!!\n", fidcode);
  // read the register value
  u_int32_t rdata;
  ReadReg(RCDCHMULTTHR,&rdata);
  // mask needed values
  rdata &= 0xFFFF0000;
  // add requested value
  rdata |= (*data)&0xFF;
  WriteReg(RCDCHMULTTHR,&rdata);
}
// set CDCH DS hits multiplicity threshold
void TCB::SetCDCHDSMultThr(u_int32_t *data){
   if ((fidcode>>12)!=3) printf("setting CDCH masks on TCB %4x!!!!!\n", fidcode);
  // read the register value
  u_int32_t rdata;
  ReadReg(RCDCHMULTTHR,&rdata);
  // mask needed values
  rdata &= 0xFFFF;
  // add requested value
  rdata |= (((*data)&0xFF)<<16);
  WriteReg(RCDCHMULTTHR,&rdata);
}
// set LoLX hit masks
void TCB::SetLoLXMasks(u_int32_t *data){
  if ((fidcode>>12)!=3) printf("setting FVetoShaper delay on TCB %4x!!!!!\n", fidcode);
  else if ((fexpid&0xf)!= 0x8) {
    printf("TCB not compiled for LoLX !!!!!\n");
    throw std::runtime_error("Error in TCB board configuration");
  }
  // write register
  WriteReg(RLOLXMASK,data);
}
// set LoLX Scint Maj Val
void TCB::SetLoLXMajScinVal(u_int32_t *data){
  if ((fidcode>>12)!=3) printf("setting FVetoShaper delay on TCB %4x!!!!!\n", fidcode);
  else if ((fexpid&0xf)!= 0x8) {
    printf("TCB not compiled for LoLX !!!!!\n");
    throw std::runtime_error("Error in TCB board configuration");
  }
  // read the register value
  u_int32_t rdata;
  ReadReg(RLOLXMAJVAL,&rdata);
  // mask needed values
  rdata &= 0xFFFFFF00;
  // add requested value
  rdata |= (((*data)&0xFF));
  WriteReg(RLOLXMAJVAL,&rdata);
}
// set LoLX Scint Maj Val
void TCB::SetLoLXMajCherVal(u_int32_t *data){
  if ((fidcode>>12)!=3) printf("setting FVetoShaper delay on TCB %4x!!!!!\n", fidcode);
  else if ((fexpid&0xf)!= 0x8) {
    printf("TCB not compiled for LoLX !!!!!\n");
    throw std::runtime_error("Error in TCB board configuration");
  }
  // read the register value
  u_int32_t rdata;
  ReadReg(RLOLXMAJVAL,&rdata);
  // mask needed values
  rdata &= 0xFFFF00FF;
  // add requested value
  rdata |= (((*data)&0xFF)<<8);
  WriteReg(RLOLXMAJVAL,&rdata);
}
// set LoLX Scint Maj Val
void TCB::SetLoLXMajBareVal(u_int32_t *data){
  if ((fidcode>>12)!=3) printf("setting FVetoShaper delay on TCB %4x!!!!!\n", fidcode);
  else if ((fexpid&0xf)!= 0x8) {
    printf("TCB not compiled for LoLX !!!!!\n");
    throw std::runtime_error("Error in TCB board configuration");
  }
  // read the register value
  u_int32_t rdata;
  ReadReg(RLOLXMAJVAL,&rdata);
  // mask needed values
  rdata &= 0xFF00FFFF;
  // add requested value
  rdata |= (((*data)&0xFF)<<16);
  WriteReg(RLOLXMAJVAL,&rdata);
}
// Get proton current
void TCB::GetPCurr(u_int32_t *data)
{
   if ((fidcode>>12)==2) printf("reading proton current on TCB %4x!!!!!\n", fidcode);
   ReadReg(RPCURR,data);
}
// Get SciFi counters
void TCB::GetSciFICou(u_int32_t *data)
{
  int ncycle = (NSCIFI-1)/BLTSIZE + 1;
  for(int icycle = 0; icycle<ncycle; icycle++)
    ReadBLT(RFIBCOUNTER+icycle*BLTSIZE,data+icycle*BLTSIZE,BLTSIZE);
}
// set FOOT hit shaper values
void TCB::SetFHitShaper(u_int32_t *data){
  if ((fidcode>>12)!=3) printf("setting FHitShaper delay on TCB %4x!!!!!\n", fidcode);
  else if ((fexpid&0x3)!= 0x2) {
    printf("TCB not compiled for FOOT !!!!!\n") ;
    throw std::runtime_error("Error in TCB board configuration");
  }
  // read the register value
  u_int32_t rdata;
  ReadReg(RSINGLECRATECFG,&rdata);
  // mask needed values
  rdata &= 0xFFFFFFE0;
  // add requested value
  rdata |= (*data)&0x1F;
   WriteReg(RSINGLECRATECFG,&rdata);
}
// set FOOT veto shaper values
void TCB::SetFVetoShaper(u_int32_t *data){
  if ((fidcode>>12)!=3) printf("setting FVetoShaper delay on TCB %4x!!!!!\n", fidcode);
  else if ((fexpid&0x3)!= 0x2) {
    printf("TCB not compiled for FOOT !!!!!\n");
    throw std::runtime_error("Error in TCB board configuration");
  }
  // read the register value
  u_int32_t rdata;
  ReadReg(RSINGLECRATECFG,&rdata);
  // mask needed values
  rdata &= 0xFFFFE0FF;
  // add requested value
  rdata |= ((*data)&0x1F)<<8;
   WriteReg(RSINGLECRATECFG,&rdata);
}
// set Margarita Majority
void TCB::SetMargaritaMajVal(u_int32_t *data){
  if ((fidcode>>12)!=3) printf("setting Margarita Majority on TCB %4x!!!!!\n", fidcode);
  else if ((fexpid&0x3)!= 0x2) {
    printf("TCB not compiled for FOOT !!!!!\n");
    throw std::runtime_error("Error in TCB board configuration");
  };
  // read the register value
  u_int32_t rdata;
  ReadReg(RMAJORITYVALUE,&rdata);
  // mask needed values
  rdata &= 0xFFFFFFF0;
  // add requested value
  rdata |= (*data)&0xF;
   WriteReg(RMAJORITYVALUE,&rdata);
}
// set Margarita Majority
void TCB::SetMargaritaTrgDly(u_int32_t *data){
  if ((fidcode>>12)!=3) printf("setting Margarita trigger delay on TCB %4x!!!!!\n", fidcode);
  else if ((fexpid&0x3)!= 0x2) {
    printf("TCB not compiled for FOOT !!!!!\n");
    throw std::runtime_error("Error in TCB board configuration");  
  } 
  if(*data > 32) {
   printf("Margarita delay values allowed [0-31], given %d\n", *data);
    throw std::runtime_error("Error in TCB board configuration");  
  }
  if(*data > 0)
    *data += 32;
  
  // read the register value
  u_int32_t rdata;
  ReadReg(RMAJORITYVALUE,&rdata);
  // mask needed values
  rdata &= 0xFFFFFC0F;
  // add requested value
  rdata |= ((*data)&0x3F)<<4;
   WriteReg(RMAJORITYVALUE,&rdata);
}
// set Margarita Masks
void TCB::SetMargaritaMask(u_int32_t *data){
  if ((fidcode>>12)!=3) printf("setting Margarita Mask on TCB %4x!!!!!\n", fidcode);
  else if ((fexpid&0x3)!= 0x2) {
    printf("TCB not compiled for FOOT !!!!!\n");
    throw std::runtime_error("Error in TCB board configuration");	
  }
  // read the register value
  u_int32_t rdata;
  ReadReg(RMAJORITYVALUE,&rdata);
  // mask needed values
  rdata &= 0xFF00FFFF;
  // add requested value
  rdata |= ((*data)&0xFF)<<16;
   WriteReg(RMAJORITYVALUE,&rdata);
}
// set Tof Bar hit logic
void TCB::SetTofBarHitLogic(u_int32_t *data){
  if ((fidcode>>12)!=3) printf("setting Tof hit bar Logic on TCB %4x!!!!!\n", fidcode);
  else if ((fexpid&0x3)!= 0x2) {
    printf("TCB not compiled for FOOT !!!!!\n");
    throw std::runtime_error("Error in TCB board configuration");	
  }
  // read the register value
  u_int32_t rdata;
  ReadReg(RMAJORITYVALUE,&rdata);
  // mask needed values
  rdata &= 0xBFFFFFFF;
  // add requested value
  rdata |= ((*data)&0x1)<<30;
   WriteReg(RMAJORITYVALUE,&rdata);
}
// set Tof Bar hit logic
void TCB::SetTofHitLogic(u_int32_t *data){
  if ((fidcode>>12)!=3) printf("setting Tof bar Logic on TCB %4x!!!!!\n", fidcode);
  else if ((fexpid&0x3)!= 0x2) {
    printf("TCB not compiled for FOOT !!!!!\n");
    throw std::runtime_error("Error in TCB board configuration");	
  }
  // read the register value
  u_int32_t rdata;
  ReadReg(RMAJORITYVALUE,&rdata);
  // mask needed values
  rdata &= 0x7FFFFFFF;
  // add requested value
  rdata |= ((*data)&0x1)<<31;
   WriteReg(RMAJORITYVALUE,&rdata);
}
// set Tof Bar hit logic
void TCB::SetTofHitLogicAlternative(u_int32_t *data){
  if ((fidcode>>12)!=3) printf("setting Tof bar Logic on TCB %4x!!!!!\n", fidcode);
   else if ((fexpid&0x3)!= 0x2) {
    printf("TCB not compiled for FOOT !!!!!\n");
    throw std::runtime_error("Error in TCB board configuration");
  }
  // read the register value
  u_int32_t rdata;
  ReadReg(RMAJORITYVALUE,&rdata);
  // mask needed values
  rdata &= 0xDFFFFFFF;
  // add requested value
  rdata |= ((*data)&0x1)<<29;
   WriteReg(RMAJORITYVALUE,&rdata);
}
// Tof X Masks
void TCB::SetTofXMask(u_int32_t *data)
{
   if ((fidcode>>12)!=3) printf("setting Tof X Masks on TCB %4x!!!!!\n", fidcode);
   else if ((fexpid&0x3)!= 0x2) {
     printf("TCB not compiled for FOOT !!!!!\n");
     throw std::runtime_error("Error in TCB board configuration");
   }
   WriteReg(RTOFXMASKS,data);
   WriteReg(RTOFXMASKS+1,data+1);
}
// Tof Y Masks
void TCB::SetTofYMask(u_int32_t *data)
{
   if ((fidcode>>12)!=3) printf("setting Tof Y Masks on TCB %4x!!!!!\n", fidcode);
   else if ((fexpid&0x3)!= 0x2) {
     printf("TCB not compiled for FOOT !!!!!\n");
     throw std::runtime_error("Error in TCB board configuration");
   }
   WriteReg(RTOFYMASKS,data);
   WriteReg(RTOFYMASKS+1,data+1);
}
// FOOT Calo Masks
void TCB::SetFCaloMask(u_int32_t *data)
{
   if ((fidcode>>12)!=3) printf("setting FCalo Masks on TCB %4x!!!!!\n", fidcode);
   else if ((fexpid&0x3)!= 0x2) {
     printf("TCB not compiled for FOOT !!!!!\n");
     throw std::runtime_error("Error in TCB board configuration");
   }
   WriteReg(RFCALOMASKS0,data+0);
   WriteReg(RFCALOMASKS1,data+1);
   WriteReg(RFCALOMASKS2,data+2);

}
// FOOT Nutron Masks
void TCB::SetFNeutronMask(u_int32_t *data)
{
   if ((fidcode>>12)!=3) printf("setting FNeutron Masks on TCB %4x!!!!!\n", fidcode);
   else if ((fexpid&0x3)!= 0x2) {
     printf("TCB not compiled for FOOT !!!!!\n");
     throw std::runtime_error("Error in TCB board configuration");
   }
   WriteReg(RFNEUTRONMASKS,data);

}
// Tof Y Masks
void TCB::SetMatrixMask(u_int32_t *data)
{
  if ((fidcode>>12)!=3) printf("setting Tof Y Masks on TCB %4x!!!!!\n", fidcode);
  else if ((fexpid&0x3)!= 0x2) {
    printf("TCB not compiled for FOOT !!!!!\n");
    throw std::runtime_error("Error in TCB board configuration");
  }
  WriteReg(RMATRIXMASKS0,data);
  WriteReg(RMATRIXMASKS1,data+1);
  WriteReg(RMATRIXMASKS2,data+2);
}
// Interspill delay
void TCB::SetInterspillDly(u_int32_t *data)
{
  if ((fidcode>>12)!=3) printf("setting Interspill Dly on TCB %4x!!!!!\n", fidcode);
  else if ((fexpid&0x3)!= 0x2) {
    printf("TCB not compiled for FOOT !!!!!\n");
    throw std::runtime_error("Error in TCB board configuration");
  }
  WriteReg(RINTERSPILLDLY,data);
}

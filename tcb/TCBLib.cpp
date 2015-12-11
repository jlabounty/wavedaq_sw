#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mscb.h"
#include "TCBLib.h"

u_int32_t kaddrpre[5] = {RPRESCA0,RPRESCA1,RPRESCA2,RPRESCA3,RPRESCA4};
u_int32_t kaddrmem[4] = {RMEM0,RMEM1,RMEM2,RMEM3};
u_int32_t kaddrcou[5] = {RTRGCOU0,RTRGCOU1,RTRGCOU2,RTRGCOU3,RTRGCOU4};
u_int32_t kaddrdmask[4] = {RIDMASK0,RIDMASK1,RIDMASK2,RIDMASK3};

//general write register function
void TCB::WriteReg(int handle, u_int32_t addr, u_int32_t *data) {
  int status;
  // before than writing we have to perform a byteswap
  u_int32_t wdata = ((*data&0xff)<<24) | ((*data&0xff00)<<8) | ((*data&0xff0000)>>8) | ((*data&0xff000000)>>24);
  status = mscb_write_mem(handle, 0, fslot, addr&0xff, &wdata, sizeof(data));
  // print something only in case of error
  if (status != 1)
    printf("Error: status = %d\n", status);
}
//
// general read register function
void TCB::ReadReg(int handle, u_int32_t addr, u_int32_t *data) {
  char dbuf[1024];
  *data = 0;
  mscb_read_mem(handle, 0, fslot, addr&0xff, &dbuf, 4);
  for (int i=0 ; i<4 ; i++)  
    *data |= ((u_int32_t) dbuf[3-i]&0xff)<<(i*8); //"(i*8)" as a byte swap
}
//
// general read register function
void TCB::ReadBLT(int handle, u_int32_t addr, u_int32_t *data, int nword) {
  char dbuf[1024];
  mscb_read_mem(handle, 0, fslot, addr&0xff, &dbuf, nword*4); //4*nword: it is in number of bytes
  for (int iword=0 ; iword<nword ; iword++)  {
    data[iword] = 0;
    for(int ibyte = 0; ibyte<4; ibyte++)
      data[iword] |= ((u_int32_t) dbuf[(iword*4+3)-ibyte]&0xff)<<(ibyte*8); //"(i*8)" as a byte swap
  }
}
//
// prescaling values setting
void TCB::SetPrescaling(int handle, u_int32_t *presca) {
  int status;
  //load the prescaling values;
  // loop on prescaling values
  for(int ireg=0; ireg<5; ireg++) {
    WriteReg(handle, kaddrpre[ireg],presca+ireg);
  }   
} //end SetPrescaling
//
// read prescaling values
void TCB::GetPrescaling(int handle, u_int32_t *presca) {
  //load the prescaling values;
  //read loop on prescaling registers
  for(int ireg = 0; ireg<5; ireg++) 
    ReadReg(handle,kaddrpre[ireg],presca+ireg); 
} //end GetPrescaling 
//
//Set IDCode by accessing to rrun register 
void TCB::SetIDCode(int handle) {
  u_int32_t data;
  u_int32_t addr = RRUN;
  // read the RRUN register and take the content
  ReadReg(handle, addr, &data);
  //the IDCode is obtained by parsing the data
  fidcode = ((data&0xff0000)>>16);
}
//
// Write a memory 
void TCB::WriteMemory(int handle, int which, u_int32_t *data) {
  u_int32_t addr;
  // set the address as a function of the addressed memory
  addr = kaddrmem[which];
  // now loop to write the 32 memory cells
  for(int icell = 0; icell<32; icell++) {
    WriteReg(handle,addr+icell,data+icell);
  }
}
//
// Read a memory 
void TCB::ReadMemory(int handle, int which, u_int32_t *data) {
  u_int32_t addr;
  // set the address as a function of the addressed memory
  addr = kaddrmem[which];
  // now loop to write the 32 memory cells
  for(int icell = 0; icell<32; icell++) {
    ReadReg(handle,addr+icell,data+icell);
  }
}
//
// Read all the memories with bly 
void TCB::ReadMemoryBLT(int handle, int which, u_int32_t *data) {
  u_int32_t addr;
  // set the address as a function of the addressed memory
  addr = kaddrmem[which];
  // now loop to write the 32 memory cells
  ReadBLT(handle,addr,data,32);
}
//
// activate the RUNMODE signal
void TCB::GoRun(int handle) {
  u_int32_t addr = RRUN;
  u_int32_t data; 
  // first read the RRUN register to copy the current status
  ReadReg(handle,addr,&data);
  // now set the runmode
  data = (data&0xFFFFFFFC) | 0x1;
  WriteReg(handle,addr,&data);
}
//
// check the RUNMODE status
int TCB::IsRunning(int handle) {
  u_int32_t addr = RRUN;
  u_int32_t data; 
  ReadReg(handle,addr,&data);
  data &= 0x1;
  return (data);
}
//
// check the BUSY status
int TCB::IsBusy(int handle) {
  u_int32_t addr = RRUN;
  u_int32_t data; 
  ReadReg(handle,addr,&data);
  data &= 0x8;
  return (data);
}
//
// remove the internal BUSY signal
void TCB::RemoveBusy(int handle) {
  u_int32_t addr = RRUN;
  u_int32_t data; 
  // first read the RRUN register to copy the current status
  ReadReg(handle,addr,&data);
  // now remove the busy
  data = (data&0xFFFFFFFC) | 0x2;
  // now set the busy
  WriteReg(handle,addr,&data);
}
//
// activate the internal Sync signal
void TCB::SWSync(int handle) {
  u_int32_t addr = RRUN;
  u_int32_t data; 
  // first read the RRUN register to copy the current status
  ReadReg(handle,addr,&data);
  // now sync
  data = (data&0xFFFFFFFC) | 0x80;
  WriteReg(handle,addr,&data);
}
//
// activate the internal stop signal
void TCB::SWStop(int handle) {
  u_int32_t addr = RRUN;
  u_int32_t data; 
  // first read the RRUN register to copy the current status
  ReadReg(handle,addr,&data);
  // now go to stop
  data = (data&0xFFFFFFFC) | 0x40;
  WriteReg(handle,addr,&data);
}
//
// write the RRUN register
void TCB::SetRRUN(int handle, u_int32_t *data) {
  u_int32_t addr = RRUN;
  WriteReg(handle,addr,data);
}
//
// write the THRMult register
void TCB::SetTHRMult(int handle, u_int32_t *data) {
  u_int32_t addr = RTHRMULT;
  WriteReg(handle,addr,data);
}
//
// write the TRGDLY register
void TCB::SetTRGDLY(int handle, u_int32_t *data) {
  u_int32_t addr = RTRGDLY;
  WriteReg(handle,addr,data);
}
//
// read the TRGDLY register
void TCB::GetTRGDLY(int handle, u_int32_t *data) {
  u_int32_t addr = RTRGDLY;
  ReadReg(handle,addr,data);
}
//
// write the RRUN register
void TCB::GetRRUN(int handle, u_int32_t *data) {
  u_int32_t addr = RRUN;
  ReadReg(handle,addr,data);
  printf(" RUNMODE status %x \n",*data&0x1);
  printf(" INBUSY status %x \n",(*data&0x2)>>1);
  printf(" FADCMODE status %x \n",(*data&0x4)>>2);
  printf(" EXBUSY status %x \n",(*data&0x8)>>3);
  printf(" TRGENA status %x \n",(*data&0x1f00)>>8);
  printf(" MASKBUSY status %x \n",(*data&0x2000)>>13);
  printf(" MASKSYNC status %x \n",(*data&0x4000)>>14);
  printf(" MASKTRG status %x \n",(*data&0x8000)>>15);
  printf(" IDCODE status %x \n",(*data&0xff0000)>>16);
}
//
// read total time
void TCB::GetTotalTime(int handle, u_int32_t *data) {
  u_int32_t addr = RTOTTIME;
  ReadReg(handle,addr,data);
}
//
// read total time
void TCB::GetLiveTime(int handle, u_int32_t *data) {
  u_int32_t addr = RLIVETIME;
  ReadReg(handle,addr,data);
}
//
// read total time
void TCB::GetEventCounter(int handle, u_int32_t *data) {
  u_int32_t addr = REVECOU;
  ReadReg(handle,addr,data);
}
//
// read total time
void TCB::GetTriggerType(int handle, u_int32_t *type, u_int32_t *tpattern) {
  u_int32_t addr = RTRITYPE;
  u_int32_t data;
  ReadReg(handle,addr,&data);
  //extract trigger type
  *type = data&0x7;
  *tpattern = (data&0x1f0000)>>16;
}
//
// read total time
void TCB::GetTriggerCounters(int handle, u_int32_t *data) {
    ReadBLT(handle,kaddrcou[0],data,5);
}
//
// write in data masks
void TCB::SetDataMasks(int handle, u_int32_t *data) {
  for(int imsk = 0; imsk<4; imsk++) {
    WriteReg(handle,kaddrdmask[imsk],data+imsk);
  }
}
//
// read memory address
void TCB::GetMemoryAddress(int handle, u_int32_t *data) {
  u_int32_t addr = RMEMADDR;
  ReadReg(handle,addr,data);
}
//
// read time stamps
void TCB::GetTimeStamps(int handle, u_int32_t *data) {
  u_int32_t addr = TIMESTP0;
  ReadBLT(handle,addr,data,32);
}

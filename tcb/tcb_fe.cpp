#include "tcb_fe.h"
// in the init we create a board and give a stop signal to the system, this must
// follow the WD initialisation
// PLEASE CHECK THE MSCB HANDLE DEFINITION
int tcb_init() {
  // open mscb connection CHECK MSCB NODE
  handle = mscb_init("MSCBXXX", 0, "", 0);
  // create TCB Board
  TCBBoard.fslot = 17;
  // check the board ID
  TCBBoard.SetIDCode(handle);
  // open the configuration file
  fadcmode = 1;
  infile = fopen("runconfig.dat","read");
  fscanf(infile,"%*s %x",&trgena);
  fscanf(infile,"%*s %x",&trgbusmask);
  fscanf(infile,"%*s %x",presca);
  fscanf(infile,"%*s %x",presca+1);
  fscanf(infile,"%*s %x",presca+2);
  fscanf(infile,"%*s %x",presca+3);
  fscanf(infile,"%*s %x",&multthr);
  fscanf(infile,"%*s %x %x %x %x",chamask, chamask+1, chamask+2, chamask+3);
  fclose(infile);
  // load RRUN register
  u_int32_t rrundata = (fadcmode<<2) | (trgena<<8) | (trgbusmask<<13);
  TCBBoard.SetRRUN(handle,&rrundata);
  // load prescaling 
  TCBBoard.SetPrescaling(handle,presca);
  // load channel masks
  TCBBoard.SetDataMasks(handle,chamask);
  // load multiplicity threshold
  TCBBoard.SetTHRMult(handle,&multthr);
  // give a SW Sync
  TCBBoard.SWSync(handle);
  // give a SW stop to go idle 
  TCBBoard.SWStop(handle);
  return 0;
}// end of init
// this goes after the WD begin_of_run
int tcb_begin_of_run() {
  // first remove the local busy on the TCB
  TCBBoard.RemoveBusy(handle);
  // endless loop checking the extern busy to be off
  while(TCBBoard.IsBusy(handle));
  //now SYNC
  TCBBoard.SWSync(handle);
  // finally in run
  TCBBoard.GoRun(handle);
  return 0;
}
// poll event, are we doing on TCB??
int tcb_poll_event() {
  while(TCBBoard.IsRunning(handle));
  //check that the system is busy
  if(!TCBBoard.IsBusy(handle)) {
    printf("ERROR the system is NOT busy!!!!\n");
    return -1;
  }
 return 0;
}
//read event
int tcb_read_event(){
  //read memories and address
  TCBBoard.ReadMemory(handle, 0, memdata);
  TCBBoard.ReadMemory(handle, 1, memdata+32);
  TCBBoard.ReadMemory(handle, 2, memdata+64);
  TCBBoard.ReadMemory(handle, 3, memdata+96);
  TCBBoard.GetMemoryAddress(handle,&memaddr);
  // counters and trg type
  TCBBoard.GetTriggerCounters(handle,trgcounters);
  TCBBoard.GetTriggerType(handle,&trgtype,&trgpattern);
  TCBBoard.GetTotalTime(handle,&totaltime);
  TCBBoard.GetLiveTime(handle,&livetime);
  TCBBoard.GetEventCounter(handle,&hwevecou);
  // TDCs...
  TCBBoard.GetTimeStamps(handle,tdc);
  // remove TCB busy
  TCBBoard.RemoveBusy(handle);
  // endless loop checking the extern busy to be off
  while(TCBBoard.IsBusy(handle));
  // finally back in run
  TCBBoard.GoRun(handle);
  return 0;
}
// tcb end of run
int tcb_end_of_run(){
  // give a SW stop
  TCBBoard.SWStop(handle);
  return 0;
}

#define RRUN          0x00                      // run control 
#define RPRESCA0      0x10                      // prescaling0 
#define RPRESCA1      0x11                      // prescaling1 
#define RPRESCA2      0x12                      // prescaling2 
#define RPRESCA3      0x13                      // prescaling3 
#define RIDMASK0      0x14                      // mask indata(31:0)
#define RIDMASK1      0x15                      // mask indata(63:32)
#define RIDMASK2      0x16                      // mask indata(95:64)
#define RIDMASK3      0x17                      // mask indata(127:96)
#define RTOTTIME      0x20                      // total time 
#define RLIVETIME     0x21                      // live time 
#define REVECOU       0x22                      // event counter 
#define RTRITYPE      0x23                      // trigger type 
#define RTRGCOU0      0x40                      // trigger counter0 
#define RTRGCOU1      0x41                      // trigger counter1
#define RTRGCOU2      0x42                      // trigger counter2
#define RTRGCOU3      0x43                      // trigger counter3
#define TIMESTP0      0x50                      // base address of time stamps (32 integers) 
#define RTHRMULT      0x70                      // multiplicity threshold 
#define RMEMADDR      0x7F                      // memory address
#define RMEM0         0x80                      // memory 0 
#define RMEM1         0xA0                      // memory 1 
#define RMEM2         0xC0                      // memory 2 
#define RMEM3         0xE0                      // memory 3 

class TCB {
 public:
  // board info
  u_int32_t   fidcode;      // reg id
  u_int32_t   fslot;      // slot

  // getters
  u_int32_t      GetIDCode() { return fidcode; }
  u_int32_t      GeSlot() { return fslot; }
  // board configuration
  //
  //general write register function
  void WriteReg(int, u_int32_t, u_int32_t*);
  // general read register function
  void ReadReg(int, u_int32_t, u_int32_t*);
  // general read block transfer function
  void ReadBLT(int, u_int32_t, u_int32_t*,int);
  // prescaling values setting
  void SetPrescaling(int, u_int32_t*);
  // read prescaling values
  void GetPrescaling(int, u_int32_t*);
  // set the IDCode
  void SetIDCode(int);
  // write a memory
  void WriteMemory(int,int,u_int32_t*);
  // read a memory
  void ReadMemory(int,int,u_int32_t*);
  // read all memories
  void ReadMemoryBLT(int,int,u_int32_t*);
  // set the runmode
  void GoRun(int);
  // get the runmode status
  int IsRunning(int);
  // remove the busy
  void RemoveBusy(int);
  // software sync
  void SWSync(int);
  // software stop
  void SWStop(int);
  // set rrun register
  void SetRRUN(int,u_int32_t*);
  // set rrun register
  void SetTHRMult(int,u_int32_t*);
  // get rrun register
  void GetRRUN(int,u_int32_t*);
  // read total time 
  void GetTotalTime(int,u_int32_t*);
  // read live time 
  void GetLiveTime(int,u_int32_t*);
  // read event counter
  void GetEventCounter(int,u_int32_t*);
  // read trigger type and pattern
  void GetTriggerType(int,u_int32_t*,u_int32_t*);
  // read trigger counters
  void GetTriggerCounters(int,u_int32_t*);
  // read memory address
  void GetMemoryAddress(int,u_int32_t*);
  // write in data masks
  void SetDataMasks(int,u_int32_t*);
  // read time stamps
  void GetTimeStamps(int,u_int32_t *);
  // check if the system is busy
  int IsBusy(int);
  // Constructor
  TCB(int slot) { 
    fslot = slot;
    fidcode = 0xff;
  }

};



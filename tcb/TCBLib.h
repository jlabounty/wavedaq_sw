//
//  TCBLib.h
//  Trigger Concentrator Board Library Header File
//
//  Created by Luca Galli on 12/12/2015
//

#define RRUN          0x00                      // run control
#define RBUSDLY       0x01                      // trigger bus delay
#define RNTRG         0x02                      // trigger enable bits
#define RALGSEL       0x03                      // algorithm select on TCB1/2_0
#define USR_ACCESS    0x0F                      // FW compilaiton date
#define RFCDLY        0x14                      // frontpanel serdes delay values
#define RSERDESMSK    0x16                      // mask for input serdes
#define RENA          0x20                      // trigger enable (first address)
#define RTRIPATT      0x30                      // trigger pattern (first address)
#define RTRGFORCE     0x40                      // force a trigger (first address)
#define RCHKCOU       0x50                      // serdes counter check (first address)
#define RCHKTIM       0x60                      // serdes cycles counter for normalisation
#define RPRESCA       0x100                     // prescaling value first address
#define RTOTTIME      0x200                     // total time
#define RLIVETIME     0x201                     // live time
#define REVECOU       0x202                     // event counter
#define RTRITYPE      0x203                     // trigger type
#define RSYSEVECOU    0x204                     // system (trgbus) event counter
#define RSYSTRITYPE   0x205                     // system (trgbus) trigger type
#define RSERDESCONF   0x300                     // serdes configuration, reset and check enable (first address)
#define RSERDESBSLP   0x320                     // individual bitslip for each channel (first address)
#define RSERDESCHECK  0x324                     // serdes status (first address)
#define RSERDESVAL0   0x328                     // serdes value to be checked (lower part)
#define RSERDESVAL1   0x329                     // serdes value to be checked (upper part)
#define RSERDESCOU    0x330                     // serdes error counter (first address)
#define RSERDESTIME   0x3B0                     // serdes test time
#define RSERDESTX     0x3C0                     // tx serdes configuration and delay load
#define RTRGCOU       0x400                     // trigger counter (first address)
#define RPARAM        0x600                     // start of parameter space
#define RMEMADDR      0x0FFFF                   // counter stop position
#define MEMBASEADDR   0x10000                   //base address for memories

///////////////////////////////////////////////////////////
// LIBRARY ASSOCIATED TO TCB_X_0
#define MEMNUM             34
#define MEMDIM             1024
///////////////////////////////////////////////////////////

#include "strlcpy.h"

typedef struct {
    unsigned short     trgindly;
    unsigned short     syncindly;
    unsigned short     sprindly;
    unsigned short     trgoutdly;
    unsigned short     syncoutdly;
    unsigned short     sproutdly;
    unsigned short     algsel;
    unsigned int       serdesmask;
} TCB_SETTINGS;


class TCB {
private:
   int            InitType1(TCB_SETTINGS *ts);
   int            InitType2(TCB_SETTINGS *ts);
   int            InitType3(TCB_SETTINGS *ts);

public:
   // board info
   u_int32_t      fidcode;           // reg id
   u_int32_t      fslot;             // slot
   char           fmscb_device[256]; // MSCBxxx node name
   int            fmscb_addr;        // MSCB address of CMB
   int            fh;                // MSCB handle
   int            fntrg;             // number of available trigger
   int            fverbose;          // verbosity level
   int            fnserdes;          // number of available trigger
   // getters
   u_int32_t      GetIDCode() { return fidcode; }
   u_int32_t      GetSlot() { return fslot; }
   
   // Constructor
   TCB(const char *mscb_device, int mscb_addr, int slot, int verbose = 0) {
      strlcpy(fmscb_device, mscb_device, sizeof(fmscb_device));
      fmscb_addr = mscb_addr;
      fslot = slot;
      fidcode = 0xffff;
      fntrg = 0x0;
      fverbose = verbose;
      fnserdes= 0;
   }

   int InitBoard(TCB_SETTINGS *ts, int iType);
   
   //general write register function
   void WriteReg(u_int32_t, u_int32_t*);
   //general write block transfert function
   void WriteBLT(u_int32_t, u_int32_t*,int);
   // general read register function
   void ReadReg(u_int32_t, u_int32_t*);
   // general read block transfer function
   void ReadBLT(u_int32_t, u_int32_t*,int);
   // prescaling values setting
   void SetPrescaling(u_int32_t*);
   // read prescaling values
   void GetPrescaling(u_int32_t*);
   // set the IDCode
   void SetIDCode();
   // set fntrg
   void SetNTRG();
   // write a memory
   void WriteMemory(int,u_int32_t*);
   // write a memory
   void WriteMemoryBLT(int,u_int32_t*);
   // read a memory
   void ReadMemory(int,u_int32_t*);
   // read all memories
   void ReadMemoryBLT(int,u_int32_t*);
   // set the runmode
   void GoRun();
   // get the runmode status
   int IsRunning();
   // remove the busy
   void RemoveBusy();
   // software sync
   void SWSync();
   // software stop
   void SWStop();
   // set rrun register
   void SetRRUN(u_int32_t*);
   // set rena register
   void SetRENA(u_int32_t*,int);
   // set rena register
   void SetTriggerEnable(bool *);
   // set ralgsel register
   void SetRALGSEL(u_int32_t*);
   // get rrun register
   void GetRRUN(u_int32_t*);
   // get rena register
   void GetRENA(u_int32_t*, int);
   // get ralgsel register
   void GetRALGSEL(u_int32_t*);
   // read total time
   void GetTotalTime(u_int32_t*);
   // read live time
   void GetLiveTime(u_int32_t*);
   // read event counter
   void GetEventCounter(u_int32_t*);
   // read trigger type
   void GetTriggerType(u_int32_t*);
   // read trigger pattern
   void GetTriggerPattern(u_int32_t*, int);
   // read system event counter
   void GetSystemEventCounter(u_int32_t*);
   // read system trigger type
   bool GetSystemTriggerType(u_int32_t*);
   // read trigger counters
   void GetTriggerCounters(u_int32_t*);
   // read memory address
   void GetMemoryAddress(u_int32_t*);
   // check if the system is busy
   int IsBusy();
   // write in trg bus Odelay register
   void SetTRGBusODLY(u_int32_t*,u_int32_t*,u_int32_t*);
   // write in trg bus Idelay register
   void SetTRGBusIDLY(u_int32_t*,u_int32_t*,u_int32_t*);
   // write in trg bus I/O delay register
   void GetTRGBusDLY(u_int32_t*,u_int32_t*,u_int32_t*,u_int32_t*,u_int32_t*,u_int32_t*);
   // write serdes memory
   void WriteSERDESMem(int,int,u_int32_t*);
   // read serdes memory
   void ReadSERDESMem(int,int,u_int32_t*);
   // Serdes delay values setting
   void SetSerdesMask(u_int32_t*);
   // set generic trigger parameter (with base address 0x600)
   void SetParameter(u_int32_t, u_int32_t*);
   // get FW compilation date
   void GetCompilDate(u_int32_t*);
   // force the trigger passed by the function call
   void ForceTrigger(int);
   // set the transmission check word
   void SetCheckWord(u_int32_t,u_int32_t);
   //get the transmission check word
   void GetCheckWord();
   //configure a single serdes link
   void ConfigureSingleSerdes(int, int, short, int);
   //configure a all serdes link
   void ConfigureAllSerdes(short, int);
   //reset transmitter
   void ResetTransmitter();
   //check an error on a given serdes link
   void GetSerdesError(u_int32_t*);
   //return the number of errors in the transmission test
   void GetSerdesErrorCount(u_int32_t*);
   //start serdes check
   void StartSerdesCheck();
   //stop serdes check
   void StopSerdesCheck();
   //calibrate serdes
   void CalibrateSerdes();
   //calibrate serdes
   void SetDbgserdes(bool);
};

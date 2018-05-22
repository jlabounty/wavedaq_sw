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
#define RPLLRES       0x04                      // Reset PLLs
#define USR_ACCESS    0x0F                      // FW compilaiton date
#define RENA          0x20                      // trigger enable (first address)
#define RTRIPATT      0x30                      // trigger pattern (first address)
#define RTRGFORCE     0x40                      // force a trigger (first address)
#define RCMD          0xFF                      // daq state machine control
#define RPRESCA       0x100                     // prescaling value first address
#define RTOTTIME      0x200                     // total time
#define RLIVETIME     0x201                     // live time
#define REVECOU       0x202                     // event counter
#define RTRITYPE      0x203                     // trigger type
#define RSYSEVECOU    0x204                     // system (trgbus) event counter
#define RSYSTRITYPE   0x205                     // system (trgbus) trigger type
#define RSERDESCONF   0x300                     // serdes configuration and reset
#define RDCBSERDESCONF 0x320                     // serdes configuration and reset for dcb
#define RSERDESTX     0x321                     // tx serdes configuration and delay load
#define RSERDESBSLP   0x322                     // individual bitslip for each channel (first address)
#define RDCBSERDESBSLP 0x326                     // individual bitslip for dcb
#define RSERDESMSK    0x327                      // mask for input serdes
#define RSERDESVAL0   0x328                     // serdes value to be checked (lower part)
#define RSERDESVAL1   0x329                     // serdes value to be checked (upper part)
#define RSERDESCHECK  0x32A                     // serdes status (first address)
#define RDCBSERDESCHECK 0x32E                    // serdes status DCB
#define RSERDESSTATUS  0x330                    // readout of serdes configuration
#define RDCBSERDESSTATUS 0x350                    // readout of dcb serdes configuration
#define RSERDESBUSY   0x351                     // autolock serdes busy
#define RSERDESFAIL   0x352                     // autolock serdes fail
#define RSERDESDLYSTATE 0x360                     // autolock serdes sate for each delay
#define RDCBSERDESDLYSTATE 0x370                     // autolock serdes sate for each delay
#define RSERDESDLYTEST 0x380                     // autolock serdes tested for each delay
#define RDCBSERDESDLYTEST 0x390                     // autolock serdes tested for each delay

#define RSERDESCOU    0x900                     // serdes error counter (first address)
#define RSERDESTIME   0x980                     // serdes test time
#define RDCBSERDESCOU    0x981                     // serdes error counter dcb
#define RTRGCOU       0x400                     // trigger counter (first address)
#define RTRGDLY       0x500                     // trigger delay (first address)
#define RPARAM        0x600                     // start of parameter space
#define RMEMADDR      0x0FFFF                   // counter stop position
#define MEMBASEADDR   0x10000                   //base address for memories
#define GENTMEMBASE   0x12000                   //base address for trigger generation memories (two memories with size = GENTDIM)
#define PACKAGERBASE  0x01000000                //base address for packager memories
#define RARBITER      0x01001000                //Bus Arbiter register and packager controller
#define BUFFERBASE    0x02000000                //Buffer base address

///////////////////////////////////////////////////////////
// LIBRARY ASSOCIATED TO TCB_X_0
#define MEMNUM             34
#define MEMDIM             128
#define GENTDIM            32
#define BUFFERSIZE         8192
#define BUFFERNUM          4
#define PACKAGERSIZE       1024
#define BLTSIZE            32
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

enum PACKETIZER_COMMAND {STOP, COPY, BLOCK_COPY, DIRECT_WRITE, JUMP, JUMP_IF};

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
   //configure all serdes link
   void ConfigureAllSerdes(short, int);
   //configure all serdes link
   void ConfigureAllDCBSerdes(short, int);
   //configure all serdes delays and bits at once
   void SetAllSerdes(u_int32_t *, int *);
   //configure all serdes delays and bits at once
   void SetAllDCBSerdes(u_int32_t *, int *);
   //reset transmitter
   void ResetTransmitter();
   //reset transmitter
   void ResetIDLYCTRL();
   //check an error on a given serdes link
   void GetSerdesError(u_int32_t*);
   //return the number of errors in the transmission test
   void GetSerdesErrorCount(u_int32_t*);
   //return the number of errors in the transmission test
   void GetDCBSerdesErrorCount(u_int32_t*);
   //start serdes check
   void StartSerdesCheck();
   //stop serdes check
   void StopSerdesCheck();
   //calibrate serdes
   void CalibrateSerdes(u_int32_t *dlyout=0, int *bitout=0);
   //calibrate serdes
   void CalibrateDCBSerdes(u_int32_t *dlyout=0, int *bitout=0);
   //calibrate serdes
   void SetDbgserdes(bool);
   //set variable pattern
   void SetSerdesPattern(bool);
   //do a serdes check
   int CheckSerdes();
   //Assign Bus to Packetizer
   void SetPacketizerBus(bool);
   //Check local bus association
   bool GetPacketizerBus();
   //Set Packetizer enable
   void SetPacketizerEnable(bool);
   //Set Packetizer autostart
   void SetPacketizerAutostart(bool);
   //issue a software start to packetizer
   void StartPacketizer();
   //force stop packetizer
   void AbortPacketizer();
   //write Command to packetizer memories
   void SetPacketizerCommandAt(int offset, PACKETIZER_COMMAND cmd, u_int32_t arg0, u_int32_t arg1, u_int32_t opt=0);
   //read current Buffer content
   void ReadBuffer(u_int32_t* ptr, int size = (BUFFERSIZE-1), int offset = 0);
   //increment Buffer pointer
   void IncrementBufferPointer();
   //reset Buffer busy logic
   void ResetBufferLogic();
   //get current SPI Buffer pointer;
   int GetSPIBufferPointer();
   //get current Packetizer bus pointer;
   int GetPacketizerBufferPointer();
   //get current buffer memory state
   u_int32_t GetBufferState();
   //reset PLLs
   void ResetPLLs();
   //read the PLL unlock counter PLLs
   void GetPLLUnlockCou(u_int32_t *data);
   //reset the PLL unlock counter PLLs
   void ResetPLLUnlockCou();
   //Set trigger delay
   void SetTRGDLY(u_int32_t *);
   //Get trigger delay
   void GetTRGDLY(u_int32_t *);
   //Start AutoLock
   void AutoCalibrateSerdes();
   //Read Current Serdes
   void ReadCurrentSerdes(u_int32_t *dlyout, int *bitout);
   //Get AutoLock Fail
   void GetAutoCalibrateFail(u_int32_t* ret);
   //Get AutoLock Fail
   void GetAutoCalibrateBusy(u_int32_t* ret);
   //perform dummy calibration and retrieve serdes eyes
   void GetAutoCalibrateEye(u_int32_t* eyes);
};

//
//  TCBLib.h
//  Trigger Concentrator Board Library Header File
//
//  Created by Luca Galli on 12/12/2015
//

#define RHW                0x00       // hardware version information required by WaveDAQ
#define RRUN               0x01       // run control
#define RBUSDLY            0x02       // trigger bus delay
#define RNTRG              0x03       // trigger enable bits
#define RALGSEL            0x04       // algorithm select on TCB1/2_0
#define RPLLRES            0x05       // Reset PLLs
#define RUDPHEA            0x06       // UDP Header info register
#define PRESCADC           0x07       // ADC readout prescaling
#define RSYNCWFM           0x08       // SYNC Waveform from serdes
#define USR_ACCESS         0x0F       // FW compilaiton date
#define RENA               0x20       // trigger enable (first address)
#define RTRIPATT           0x30       // trigger pattern (first address)
#define RTRGFORCE          0x40       // force a trigger (first address)
#define RCMD               0xFF       // daq state machine control
#define RPRESCA            0x100      // prescaling value first address
#define RTOTTIME           0x200      // total time
#define RLIVETIME          0x201      // live time
#define REVECOU            0x202      // event counter
#define RTRITYPE           0x203      // trigger type
#define RSYSEVECOU         0x204      // system (trgbus) event counter
#define RSYSTRITYPE        0x205      // system (trgbus) trigger type
#define RPCURR             0x206      //proton current
#define RSERDESCONF        0x300      // serdes configuration and reset
#define RDCBSERDESCONF     0x320      // serdes configuration and reset for dcb
#define RSERDESTX          0x321      // tx serdes configuration and delay load
#define RSERDESBSLP        0x322      // individual bitslip for each channel (first address)
#define RDCBSERDESBSLP     0x326      // individual bitslip for dcb
#define RSERDESMSK         0x327      // mask for input serdes
#define RSERDESVAL0        0x328      // serdes value to be checked (lower part)
#define RSERDESVAL1        0x329      // serdes value to be checked (upper part)
#define RSERDESCHECK       0x32A      // serdes status (first address)
#define RDCBSERDESCHECK    0x32E      // serdes status DCB
#define RSERDESSTATUS      0x330      // readout of serdes configuration
#define RDCBSERDESSTATUS   0x350      // readout of dcb serdes configuration
#define RSERDESBUSY        0x351      // autolock serdes busy
#define RSERDESFAIL        0x352      // autolock serdes fail
#define RDCBDATA           0x353      // Serdes Data From DCB
#define RSERDESALIGNDLY    0x354      // autolock serdes slot delay enable
#define RSERDESALIGNDELTA0 0x355      // autolock serdes measured time offsets
#define RSERDESALIGNDELTA1 0x356      // autolock serdes measured time offsets
#define RSERDESMINLATENCY  0x357      // autolock serdes slot with minimum latency
#define RSERDESDLYSTATE    0x360      // autolock serdes sate for each delay
#define RDCBSERDESDLYSTATE 0x370      // autolock serdes sate for each delay
#define RSERDESDLYTEST     0x380      // autolock serdes tested for each delay
#define RDCBSERDESDLYTEST  0x390      // autolock serdes tested for each delay
#define RTRGCOU            0x400      // trigger counter (first address)
#define RTRGDLY            0x500      // trigger delay (first address)
#define RPARAM             0x600      // start of parameter space
#define RQHTHR             0x600      // sum threshold high
#define RTILEMSK0          0x601      // tile mask 0
#define RTILEMSK1          0x602      // tile mask 1
#define RTILEMSK2          0x603      // tile mask 2
#define RTILEMSK3          0x604      // tile mask 3
#define RQLTHR             0x606      // sum threshold low
#define RQCTHR             0x607      // sum threshold cosmic
#define RLXePATCH          0x608      // LXe sum patch 
#define RTIMEN             0x60A      // Time Difference threshold Narrow
#define RTIMEW             0x60B      // Time Difference threshold Wide
#define RTCMERGEH          0x60C      // TC high threshold for hit merge
#define RTCMERGEL          0x60D      // TC low threshold for hit merge
#define RRDCLYSOTHR        0x60E      // RDC QSUM threshold
#define RBGOTHR            0x60F      // BGO QSUM threshold
#define RBGOMASK           0x611      // BGO trigger definition
#define RRDCMASK           0x610      // RDC trigger definition
#define RALPHATHR          0x612      // threshold alpha
#define RALPHAPEAK         0x613      // alpha peak scale
#define RQSUMSEL           0x614      // selects the qsum as std or running average
#define RBGOVETOTHR        0x615      // BGO QSUM veto threshold
#define RTCMULTITHR        0x616      // TC Multiplicity threshold
#define RNGENDLY           0x617      // Delay of NGEN Window
#define RNGENWIDTH         0x618      // Width of NGEN Window
#define RLXeNGENQH         0x619      // LXe threshold for NGEN TRG
#define RLXeNGENQL         0x61A      // LXe veto threshold for NGEN TRG
#define RBGOHITDLY         0x61B      // Delay of BGO and Preshower hit
#define RCRCHITMASK        0x61C      // Masking bit for CRC counters (7:0)
#define RCRCPAIRENA        0x61D      // Enable bits for CRC top-bottom coincidences
#define RMAJORITYVALUE     0x61E      // Majority trigger parameters
#define RTOFXMASKS         0x61F      // Tof X-view masks
#define RTOFYMASKS         0x621      // Tof Y-view masks
#define RINTERSPILLDLY     0x623      // Interspill delay value
#define RFIBCOUNTER        0x700      // SCIFI fiber event counter address (42 values)
#define RSINGLECRATECFG    0x800      // configurations for single crate trigger logic
#define RSINGLEISVETO      0x801      // veto set for input channels in single crate logic
#define RSINGLEMASK        0x809      // mask for input channels in single crate logic
#define RSINGLELOGIC       0x811      // first stage configuration in single crate logic
#define RSERDESCOU         0x900      // serdes error counter (first address)
#define RSERDESTIME        0x980      // serdes test time
#define RDCBSERDESCOU      0x981      // serdes error counter dcb

#define RALGCLKMEMADDR     0x0FFFE    // counter stop position for ALGCLK memories
#define RMEMADDR           0x0FFFF    // counter stop position
#define MEMBASEADDR        0x10000    //base address for memories
#define GENTMEMBASE        0x12000    //base address for trigger generation memories (two memories with size = GENTDIM)

/// Detector memories (size = MEMDIM)
#define XECMEMBASE    0x11100                   // XEC memories base address (2 memories)
#define BGOMEMBASE    0x13000                   // BGO memories base address (1 memory)
#define RDCMEMBASE    0x14000                   // RDC memories base address (2 memories)
#define TCMEMBASE     0x15000                   // TC memories base address (2 memories)
#define ALFAMEMBASE   0x16000                   // ALFA memories base address (2 memories)

#define SCIFICOINCBASE     0x00800000           //SCIFI fiber coincidence base address (441)

#define PACKAGERBASE       0x01000000 //base address for packager memories
#define RARBITER           0x01001000 //Bus Arbiter register and packager controller
#define BUFFERBASE         0x02000000 //Buffer base address
#define PACKAGERREGS       0x03000000 //PackagerRegs base address

///////////////////////////////////////////////////////////
// LIBRARY ASSOCIATED TO TCB_X_0
#define MEMNUM             34
#define MEMDIM             128
#define GENTDIM            32
#define BUFFERSIZE         8192
#define BUFFERNUM          4
#define PACKAGERSIZE       1024
#define BLTSIZE            32
#define NSCIFI             42
///////////////////////////////////////////////////////////

//derived addresses (should not touch!)
#define PACK_NEXT_BUFFER   BUFFERBASE+BUFFERSIZE
#define PACK_A             PACKAGERREGS
#define PACK_B             PACKAGERREGS+1
#define PACK_C             PACKAGERREGS+2
#define PACK_RADDR         PACKAGERREGS+3
#define PACK_WADDR         PACKAGERREGS+4
#define PACK_FLAGS         PACKAGERREGS+8
#define PACK_SUM           PACKAGERREGS+9
#define PACK_AND           PACKAGERREGS+10
#define PACK_OR            PACKAGERREGS+11
#define PACK_XOR           PACKAGERREGS+12

#include "sys/types.h"
#include "strlcpy.h"
#include <vector>

#include <stdexcept>
#include "DCBLib.h"

#ifndef TCBLIB_H
#define TCBLIB_H


enum PACKETIZER_COMMAND {STOP, COPY, BLOCK_COPY, DIRECT_WRITE, JUMP, JUMP_IF};

typedef struct {
   int offset;
   PACKETIZER_COMMAND cmd;
   unsigned int arg0;
   unsigned int arg1;
   unsigned int arg2;
} PacketInstruction;

class TCB {
private:
   //internal mscb connections
   int            fmscb_addr;        // MSCB address of CMB
   int            fh;                // MSCB handle
   //internal DCB
   DCB*           fDCB;              // DCB interface

public:
   // board info
   u_int32_t      fidcode;           // reg id
   u_int32_t      fslot;             // slot
   int            fntrg;             // number of available trigger
   int            fverbose;          // verbosity level
   int            fnserdes;          // number of available trigger
   // getters
   u_int32_t      GetIDCode() { return fidcode; }
   u_int32_t      GetSlotNum() { return fslot; }
   
   // Constructors
   TCB(int verbose = 0) {
      fh = -1;
      fDCB = nullptr;
   };

   TCB(const char *mscb_device, int mscb_addr, int slot, int verbose = 0) {
      //open mscb connection
      char fmscb_device[128];
      strlcpy(fmscb_device, mscb_device, sizeof(fmscb_device));
      fh = mscb_init(fmscb_device, 0, "", 0);
      fmscb_addr = mscb_addr;

      fslot = slot;

      //dummy stuff
      fDCB = nullptr;
      fidcode = 0xffff;
      fntrg = 0x0;
      fverbose = verbose;
      fnserdes= 0;
   };

   TCB(const std::string &dcb_name, int slot, int verbose = 0) {
      //open mscb connection
      fh = -1;
      fDCB = new DCB(dcb_name, verbose);
      fDCB->Connect();

      fslot = slot;

      //dummy stuff
      fidcode = 0xffff;
      fntrg = 0x0;
      fverbose = verbose;
      fnserdes= 0;
   };


   //set mscb/Dcb access
   void SetMscbHandle(int handle, int slot, int addr=20){
      fh = handle;
      fmscb_addr = addr;
      fslot = slot;
   };

   void SetDcbInterface(DCB* dcb, int slot){
      fDCB = dcb;
      fslot = slot;
   };

   bool HasDcbInterface(){
      return fDCB != nullptr;
   }

   bool HasMscbInterface(){
      return fh != -1;
   }

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
   bool GetSystemTriggerType(u_int32_t*, u_int32_t*, u_int32_t*);
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
   //Set adc prescaling readout value
   void SetPrescAdc(u_int32_t *);
   //Get adc prescaling readout value
   void GetPrescAdc(u_int32_t *);
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
   //Returns enable value for latency compensations of SerDes
   void GetAutoAlignDlys(u_int32_t* ret);
   //single crate configuration
   void SetSingleCrateConfiguration(bool useGlobalAnd, short shape, short vetoShape);
   void SetSingleCrateChnMask(bool *state);
   void SetSingleCrateChnIsVeto(bool *state);
   void SetSingleCrateChnLogic(bool *state);
   void SetSingleCrateTriggerOr(int nChn, int* chn, short shape);
   void SetSingleCrateTriggerAnd(int nChn, int* chn, short shape);
   void SetFMask(bool, bool);
   void SetLocalTrigger(bool ena);
   //write full Packetizer program
   void WritePacketizerProgram(std::vector<PacketInstruction> &list);
   //read buffer head, return buffer read pointer
   u_int32_t GetBufferHeadSPI(int *nBanks, u_int32_t *evecou=0, u_int32_t *totaltime=0, u_int32_t* sys_tritype=0, u_int32_t *sys_evecou=0);
   //check has bank
   bool HasBufferBankSPI(u_int32_t ptr, char *bankName, int *length);
   //skip bank
   u_int32_t SkipBufferBankSPI(u_int32_t ptr, int length);
   //get bank data
   void GetBufferBankDataSPI(u_int32_t ptr, u_int32_t *data, int length);
   //get SYNC waveform
   void GetSyncWaveform(u_int32_t *ptr);
   //reset SYNC waveform serdes
   void ResetSyncWaveformSerdes();

   //trigger-specific calls
   // Set waveform sum trigger threshold
   void SetSumHighThreshold(u_int32_t*);
   void SetSumLowThreshold(u_int32_t*);
   void SetSumVetoThreshold(u_int32_t*);
   void SetSumPatch(u_int32_t*);
   //time thresholds
   void SetTimeNarrow(u_int32_t*);
   void SetTimeWide(u_int32_t*);
   //Alpha configuration
   void SetAlphaThreshold(u_int32_t*);
   void SetAlphaPeakScale(float);
   //qsum std or moving average
   void SetQsumSelect(u_int32_t*);
   // Set TC masks
   void SetTCMasks(u_int32_t*);
   void SetTCMultiplicityThreshold(u_int32_t*);
   void SetTCCrateMergeThreshold(u_int32_t*, u_int32_t*);
   void SetTCSectorMergeThreshold(u_int32_t*, u_int32_t*);
   //Set BGO Stuff
   void SetBGOThreshold(u_int32_t *);
   void SetBGOVetoThreshold(u_int32_t *);
   void SetBGOTriggerMask(u_int32_t *);
   void SetBGOHitDelay(u_int32_t *);
   //Set RDC Stuff
   void SetRDCThreshold(u_int32_t *);
   void SetRDCTriggerMask(u_int32_t *);
   //Set CRC Stuff
   void SetCRCHitMask(u_int32_t *);
   void SetCRCPairEnable(u_int32_t *);
   //Set NGEN Stuff
   void SetNGENDly(u_int32_t *);
   void SetNGENWidth(u_int32_t *);
   void SetNGENHighThreshold(u_int32_t *);
   void SetNGENLowThreshold(u_int32_t *);
   //Get proton current
   void GetPCurr(u_int32_t *);
   //Get SciFi counters
   void GetSciFICou(u_int32_t *);
  // FOOT stuffs
  void SetFHitShaper(u_int32_t *);
  void SetFVetoShaper(u_int32_t *);
  void SetMargaritaMajVal(u_int32_t *);
  void SetMargaritaMask(u_int32_t *);
  void SetTofBarHitLogic(u_int32_t *);
  void SetTofHitLogic(u_int32_t *);
  void SetTofXMask(u_int32_t *);
  void SetTofYMask(u_int32_t *);
  void SetInterspillDly(u_int32_t *);

};

#endif

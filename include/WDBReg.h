//
//  WDBReg.h
//
//  WaveDAQ Register Access Class
//
//  This file is generated automatically, please do not edit!
//
// Created :  09.08.2021 13:11:43
//
// Register Layout Versions :  8, 9
//

#ifndef __wdbreg_h__
#define __wdbreg_h__

//--------------------------------------------------------------------

#define mVersionReg    0x0004
#define mVersionMask   0x0000FFFF
#define mVersionOffs   0

//--------------------------------------------------------------------

class WDBREG {

private:

   unsigned int mVersion;
   // virtual bit functions, must be implemented in derived class
   virtual unsigned int BitExtractStatus(unsigned int reg, unsigned int mask, unsigned int ofs) = 0;
   virtual unsigned int BitExtractControl(unsigned int reg, unsigned int mask, unsigned int ofs) = 0;
   virtual void SetRegMask(unsigned int reg, unsigned int mask, unsigned int ofs, unsigned int v) = 0;
   virtual std::vector<unsigned int> ReadUDP(unsigned int ofs, unsigned int nReg) = 0;

public:

   // constructor
   WDBREG() {
     this->mVersion = 0;
   };

   void SetVersion(unsigned int version) {
      mVersion = version;
   }

   unsigned int GetVersion() {
      return this->mVersion;
   }

   // Number of Control Registers
   unsigned int GetNrOfCtrlRegs()
   {
      switch(this->mVersion)
      {
         case 8:
            return 162;
         case 9:
            return 139;
         default:
            throw std::invalid_argument("Function GetNrOfCtrlRegs() not defined for this board version");
      };
   };

   // Number of Status Registers
   unsigned int GetNrOfStatRegs()
   {
      switch(this->mVersion)
      {
         case 8:
            return 90;
         case 9:
            return 89;
         default:
            throw std::invalid_argument("Function GetNrOfStatRegs() not defined for this board version");
      };
   };

//--------------------------------------------------------------------
// Bit/Register Access and Location Functions
//--------------------------------------------------------------------

   // Bit(s) ADC_0_1458_DCSOFF
   unsigned int GetAdc01458Dcsoff()
   {
      switch(this->mVersion)
      {
         case 9:
            // Clock Duty Cycle Stabilizer (0=ON, 1=OFF)
            return BitExtractControl(0x1114, 0x80000000, 31);
         default:
            throw std::invalid_argument("Function GetAdc01458Dcsoff() not defined for this board version");
      };
   };
   void SetAdc01458Dcsoff(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Clock Duty Cycle Stabilizer (0=ON, 1=OFF)
            return SetRegMask(0x1114, 0x80000000, 31, value);
         default:
            throw std::invalid_argument("Function SetAdc01458Dcsoff() not defined for this board version");
      };
   };
   unsigned int GetAdc01458DcsoffLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Clock Duty Cycle Stabilizer (0=ON, 1=OFF)
            if(BitMask) *BitMask = 0x80000000;
            if(BitOfs) *BitOfs = 31;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdc01458DcsoffLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_1458_ILVDS
   unsigned int GetAdc01458Ilvds()
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Output Current Bits (1.75mA - 4.5mA, 0b111 = 2x1.75mA = 3.5mA) (see datasheet)
            return BitExtractControl(0x1114, 0x00E00000, 21);
         default:
            throw std::invalid_argument("Function GetAdc01458Ilvds() not defined for this board version");
      };
   };
   void SetAdc01458Ilvds(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Output Current Bits (1.75mA - 4.5mA, 0b111 = 2x1.75mA = 3.5mA) (see datasheet)
            return SetRegMask(0x1114, 0x00E00000, 21, value);
         default:
            throw std::invalid_argument("Function SetAdc01458Ilvds() not defined for this board version");
      };
   };
   unsigned int GetAdc01458IlvdsLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Output Current Bits (1.75mA - 4.5mA, 0b111 = 2x1.75mA = 3.5mA) (see datasheet)
            if(BitMask) *BitMask = 0x00E00000;
            if(BitOfs) *BitOfs = 21;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdc01458IlvdsLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_1458_OUTMODE
   unsigned int GetAdc01458Outmode()
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Mode Control Bits (0b110 = 12 Bit, 1 Lane) (see datasheet) 
            return BitExtractControl(0x1114, 0x00070000, 16);
         default:
            throw std::invalid_argument("Function GetAdc01458Outmode() not defined for this board version");
      };
   };
   void SetAdc01458Outmode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Mode Control Bits (0b110 = 12 Bit, 1 Lane) (see datasheet) 
            return SetRegMask(0x1114, 0x00070000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdc01458Outmode() not defined for this board version");
      };
   };
   unsigned int GetAdc01458OutmodeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Mode Control Bits (0b110 = 12 Bit, 1 Lane) (see datasheet) 
            if(BitMask) *BitMask = 0x00070000;
            if(BitOfs) *BitOfs = 16;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdc01458OutmodeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_1458_OUTOFF
   unsigned int GetAdc01458Outoff()
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Disable Bit (0=Enabled, 1=Disabled)
            return BitExtractControl(0x1114, 0x00080000, 19);
         default:
            throw std::invalid_argument("Function GetAdc01458Outoff() not defined for this board version");
      };
   };
   void SetAdc01458Outoff(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Disable Bit (0=Enabled, 1=Disabled)
            return SetRegMask(0x1114, 0x00080000, 19, value);
         default:
            throw std::invalid_argument("Function SetAdc01458Outoff() not defined for this board version");
      };
   };
   unsigned int GetAdc01458OutoffLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Disable Bit (0=Enabled, 1=Disabled)
            if(BitMask) *BitMask = 0x00080000;
            if(BitOfs) *BitOfs = 19;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdc01458OutoffLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_1458_OUTTEST
   unsigned int GetAdc01458Outtest()
   {
      switch(this->mVersion)
      {
         case 9:
            // Output Test Pattern Control Bit (0=Pattern Off, 1=Pattern On)
            return BitExtractControl(0x1114, 0x00008000, 15);
         default:
            throw std::invalid_argument("Function GetAdc01458Outtest() not defined for this board version");
      };
   };
   void SetAdc01458Outtest(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Output Test Pattern Control Bit (0=Pattern Off, 1=Pattern On)
            return SetRegMask(0x1114, 0x00008000, 15, value);
         default:
            throw std::invalid_argument("Function SetAdc01458Outtest() not defined for this board version");
      };
   };
   unsigned int GetAdc01458OuttestLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Output Test Pattern Control Bit (0=Pattern Off, 1=Pattern On)
            if(BitMask) *BitMask = 0x00008000;
            if(BitOfs) *BitOfs = 15;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdc01458OuttestLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_1458_RAND
   unsigned int GetAdc01458Rand()
   {
      switch(this->mVersion)
      {
         case 9:
            // Data Output Randomizer Mode Control Bit (0=OFF, 1=ON)
            return BitExtractControl(0x1114, 0x40000000, 30);
         default:
            throw std::invalid_argument("Function GetAdc01458Rand() not defined for this board version");
      };
   };
   void SetAdc01458Rand(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Data Output Randomizer Mode Control Bit (0=OFF, 1=ON)
            return SetRegMask(0x1114, 0x40000000, 30, value);
         default:
            throw std::invalid_argument("Function SetAdc01458Rand() not defined for this board version");
      };
   };
   unsigned int GetAdc01458RandLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Data Output Randomizer Mode Control Bit (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x40000000;
            if(BitOfs) *BitOfs = 30;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdc01458RandLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_1458_SLEEP
   unsigned int GetAdc01458Sleep()
   {
      switch(this->mVersion)
      {
         case 9:
            // Sleep Mode (1=Channels 1, 4, 5 and 8 are disabled)
            return BitExtractControl(0x1114, 0x10000000, 28);
         default:
            throw std::invalid_argument("Function GetAdc01458Sleep() not defined for this board version");
      };
   };
   void SetAdc01458Sleep(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Sleep Mode (1=Channels 1, 4, 5 and 8 are disabled)
            return SetRegMask(0x1114, 0x10000000, 28, value);
         default:
            throw std::invalid_argument("Function SetAdc01458Sleep() not defined for this board version");
      };
   };
   unsigned int GetAdc01458SleepLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Sleep Mode (1=Channels 1, 4, 5 and 8 are disabled)
            if(BitMask) *BitMask = 0x10000000;
            if(BitOfs) *BitOfs = 28;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdc01458SleepLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_1458_TERMON
   unsigned int GetAdc01458Termon()
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Internal Termination Bit (0=OFF, 1=ON)
            return BitExtractControl(0x1114, 0x00100000, 20);
         default:
            throw std::invalid_argument("Function GetAdc01458Termon() not defined for this board version");
      };
   };
   void SetAdc01458Termon(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Internal Termination Bit (0=OFF, 1=ON)
            return SetRegMask(0x1114, 0x00100000, 20, value);
         default:
            throw std::invalid_argument("Function SetAdc01458Termon() not defined for this board version");
      };
   };
   unsigned int GetAdc01458TermonLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Internal Termination Bit (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdc01458TermonLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_1458_TP
   unsigned int GetAdc01458Tp()
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern MSBs (actual test pattern in 12 bit mode)
            return BitExtractControl(0x1114, 0x00003FFC, 2);
         default:
            throw std::invalid_argument("Function GetAdc01458Tp() not defined for this board version");
      };
   };
   void SetAdc01458Tp(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern MSBs (actual test pattern in 12 bit mode)
            return SetRegMask(0x1114, 0x00003FFC, 2, value);
         default:
            throw std::invalid_argument("Function SetAdc01458Tp() not defined for this board version");
      };
   };
   unsigned int GetAdc01458TpLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern MSBs (actual test pattern in 12 bit mode)
            if(BitMask) *BitMask = 0x00003FFC;
            if(BitOfs) *BitOfs = 2;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdc01458TpLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_1458_TP_LSBS
   unsigned int GetAdc01458TpLsbs()
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern LSBs
            return BitExtractControl(0x1114, 0x00000003, 0);
         default:
            throw std::invalid_argument("Function GetAdc01458TpLsbs() not defined for this board version");
      };
   };
   void SetAdc01458TpLsbs(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern LSBs
            return SetRegMask(0x1114, 0x00000003, 0, value);
         default:
            throw std::invalid_argument("Function SetAdc01458TpLsbs() not defined for this board version");
      };
   };
   unsigned int GetAdc01458TpLsbsLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern LSBs
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdc01458TpLsbsLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_1458_TWOSCOMP
   unsigned int GetAdc01458Twoscomp()
   {
      switch(this->mVersion)
      {
         case 9:
            // Two's Complement Mode Control Bit (0=Offset Binary, 1=Two's Complement)
            return BitExtractControl(0x1114, 0x20000000, 29);
         default:
            throw std::invalid_argument("Function GetAdc01458Twoscomp() not defined for this board version");
      };
   };
   void SetAdc01458Twoscomp(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Two's Complement Mode Control Bit (0=Offset Binary, 1=Two's Complement)
            return SetRegMask(0x1114, 0x20000000, 29, value);
         default:
            throw std::invalid_argument("Function SetAdc01458Twoscomp() not defined for this board version");
      };
   };
   unsigned int GetAdc01458TwoscompLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Two's Complement Mode Control Bit (0=Offset Binary, 1=Two's Complement)
            if(BitMask) *BitMask = 0x20000000;
            if(BitOfs) *BitOfs = 29;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdc01458TwoscompLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_1_NAP_MODE
   unsigned int GetAdc01NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 1 Nap Mode (0=OFF, 1=ON)
            return BitExtractControl(0x1114, 0x01000000, 24);
         default:
            throw std::invalid_argument("Function GetAdc01NapMode() not defined for this board version");
      };
   };
   void SetAdc01NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 1 Nap Mode (0=OFF, 1=ON)
            return SetRegMask(0x1114, 0x01000000, 24, value);
         default:
            throw std::invalid_argument("Function SetAdc01NapMode() not defined for this board version");
      };
   };
   unsigned int GetAdc01NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 1 Nap Mode (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdc01NapModeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_2367_DCSOFF
   unsigned int GetAdc02367Dcsoff()
   {
      switch(this->mVersion)
      {
         case 9:
            // Clock Duty Cycle Stabilizer (0=ON, 1=OFF)
            return BitExtractControl(0x1118, 0x80000000, 31);
         default:
            throw std::invalid_argument("Function GetAdc02367Dcsoff() not defined for this board version");
      };
   };
   void SetAdc02367Dcsoff(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Clock Duty Cycle Stabilizer (0=ON, 1=OFF)
            return SetRegMask(0x1118, 0x80000000, 31, value);
         default:
            throw std::invalid_argument("Function SetAdc02367Dcsoff() not defined for this board version");
      };
   };
   unsigned int GetAdc02367DcsoffLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Clock Duty Cycle Stabilizer (0=ON, 1=OFF)
            if(BitMask) *BitMask = 0x80000000;
            if(BitOfs) *BitOfs = 31;
            return 0x1118;
         default:
            throw std::invalid_argument("Function GetAdc02367DcsoffLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_2367_ILVDS
   unsigned int GetAdc02367Ilvds()
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Output Current Bits (1.75mA - 4.5mA, 0b111 = 2x1.75mA = 3.5mA) (see datasheet)
            return BitExtractControl(0x1118, 0x00E00000, 21);
         default:
            throw std::invalid_argument("Function GetAdc02367Ilvds() not defined for this board version");
      };
   };
   void SetAdc02367Ilvds(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Output Current Bits (1.75mA - 4.5mA, 0b111 = 2x1.75mA = 3.5mA) (see datasheet)
            return SetRegMask(0x1118, 0x00E00000, 21, value);
         default:
            throw std::invalid_argument("Function SetAdc02367Ilvds() not defined for this board version");
      };
   };
   unsigned int GetAdc02367IlvdsLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Output Current Bits (1.75mA - 4.5mA, 0b111 = 2x1.75mA = 3.5mA) (see datasheet)
            if(BitMask) *BitMask = 0x00E00000;
            if(BitOfs) *BitOfs = 21;
            return 0x1118;
         default:
            throw std::invalid_argument("Function GetAdc02367IlvdsLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_2367_OUTMODE
   unsigned int GetAdc02367Outmode()
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Mode Control Bits (0b110 = 12 Bit, 1 Lane) (see datasheet) 
            return BitExtractControl(0x1118, 0x00070000, 16);
         default:
            throw std::invalid_argument("Function GetAdc02367Outmode() not defined for this board version");
      };
   };
   void SetAdc02367Outmode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Mode Control Bits (0b110 = 12 Bit, 1 Lane) (see datasheet) 
            return SetRegMask(0x1118, 0x00070000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdc02367Outmode() not defined for this board version");
      };
   };
   unsigned int GetAdc02367OutmodeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Mode Control Bits (0b110 = 12 Bit, 1 Lane) (see datasheet) 
            if(BitMask) *BitMask = 0x00070000;
            if(BitOfs) *BitOfs = 16;
            return 0x1118;
         default:
            throw std::invalid_argument("Function GetAdc02367OutmodeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_2367_OUTOFF
   unsigned int GetAdc02367Outoff()
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Disable Bit (0=Enabled, 1=Disabled)
            return BitExtractControl(0x1118, 0x00080000, 19);
         default:
            throw std::invalid_argument("Function GetAdc02367Outoff() not defined for this board version");
      };
   };
   void SetAdc02367Outoff(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Disable Bit (0=Enabled, 1=Disabled)
            return SetRegMask(0x1118, 0x00080000, 19, value);
         default:
            throw std::invalid_argument("Function SetAdc02367Outoff() not defined for this board version");
      };
   };
   unsigned int GetAdc02367OutoffLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Disable Bit (0=Enabled, 1=Disabled)
            if(BitMask) *BitMask = 0x00080000;
            if(BitOfs) *BitOfs = 19;
            return 0x1118;
         default:
            throw std::invalid_argument("Function GetAdc02367OutoffLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_2367_OUTTEST
   unsigned int GetAdc02367Outtest()
   {
      switch(this->mVersion)
      {
         case 9:
            // Output Test Pattern Control Bit (0=Pattern Off, 1=Pattern On)
            return BitExtractControl(0x1118, 0x00008000, 15);
         default:
            throw std::invalid_argument("Function GetAdc02367Outtest() not defined for this board version");
      };
   };
   void SetAdc02367Outtest(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Output Test Pattern Control Bit (0=Pattern Off, 1=Pattern On)
            return SetRegMask(0x1118, 0x00008000, 15, value);
         default:
            throw std::invalid_argument("Function SetAdc02367Outtest() not defined for this board version");
      };
   };
   unsigned int GetAdc02367OuttestLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Output Test Pattern Control Bit (0=Pattern Off, 1=Pattern On)
            if(BitMask) *BitMask = 0x00008000;
            if(BitOfs) *BitOfs = 15;
            return 0x1118;
         default:
            throw std::invalid_argument("Function GetAdc02367OuttestLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_2367_RAND
   unsigned int GetAdc02367Rand()
   {
      switch(this->mVersion)
      {
         case 9:
            // Data Output Randomizer Mode Control Bit (0=OFF, 1=ON)
            return BitExtractControl(0x1118, 0x40000000, 30);
         default:
            throw std::invalid_argument("Function GetAdc02367Rand() not defined for this board version");
      };
   };
   void SetAdc02367Rand(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Data Output Randomizer Mode Control Bit (0=OFF, 1=ON)
            return SetRegMask(0x1118, 0x40000000, 30, value);
         default:
            throw std::invalid_argument("Function SetAdc02367Rand() not defined for this board version");
      };
   };
   unsigned int GetAdc02367RandLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Data Output Randomizer Mode Control Bit (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x40000000;
            if(BitOfs) *BitOfs = 30;
            return 0x1118;
         default:
            throw std::invalid_argument("Function GetAdc02367RandLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_2367_SLEEP
   unsigned int GetAdc02367Sleep()
   {
      switch(this->mVersion)
      {
         case 9:
            // Sleep Mode (1=Channels 2, 3, 6 and 7 are disabled)
            return BitExtractControl(0x1118, 0x10000000, 28);
         default:
            throw std::invalid_argument("Function GetAdc02367Sleep() not defined for this board version");
      };
   };
   void SetAdc02367Sleep(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Sleep Mode (1=Channels 2, 3, 6 and 7 are disabled)
            return SetRegMask(0x1118, 0x10000000, 28, value);
         default:
            throw std::invalid_argument("Function SetAdc02367Sleep() not defined for this board version");
      };
   };
   unsigned int GetAdc02367SleepLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Sleep Mode (1=Channels 2, 3, 6 and 7 are disabled)
            if(BitMask) *BitMask = 0x10000000;
            if(BitOfs) *BitOfs = 28;
            return 0x1118;
         default:
            throw std::invalid_argument("Function GetAdc02367SleepLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_2367_TERMON
   unsigned int GetAdc02367Termon()
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Internal Termination Bit (0=OFF, 1=ON)
            return BitExtractControl(0x1118, 0x00100000, 20);
         default:
            throw std::invalid_argument("Function GetAdc02367Termon() not defined for this board version");
      };
   };
   void SetAdc02367Termon(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Internal Termination Bit (0=OFF, 1=ON)
            return SetRegMask(0x1118, 0x00100000, 20, value);
         default:
            throw std::invalid_argument("Function SetAdc02367Termon() not defined for this board version");
      };
   };
   unsigned int GetAdc02367TermonLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Internal Termination Bit (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x1118;
         default:
            throw std::invalid_argument("Function GetAdc02367TermonLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_2367_TP
   unsigned int GetAdc02367Tp()
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern MSBs (actual test pattern in 12 bit mode)
            return BitExtractControl(0x1118, 0x00003FFC, 2);
         default:
            throw std::invalid_argument("Function GetAdc02367Tp() not defined for this board version");
      };
   };
   void SetAdc02367Tp(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern MSBs (actual test pattern in 12 bit mode)
            return SetRegMask(0x1118, 0x00003FFC, 2, value);
         default:
            throw std::invalid_argument("Function SetAdc02367Tp() not defined for this board version");
      };
   };
   unsigned int GetAdc02367TpLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern MSBs (actual test pattern in 12 bit mode)
            if(BitMask) *BitMask = 0x00003FFC;
            if(BitOfs) *BitOfs = 2;
            return 0x1118;
         default:
            throw std::invalid_argument("Function GetAdc02367TpLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_2367_TP_LSBS
   unsigned int GetAdc02367TpLsbs()
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern LSBs
            return BitExtractControl(0x1118, 0x00000003, 0);
         default:
            throw std::invalid_argument("Function GetAdc02367TpLsbs() not defined for this board version");
      };
   };
   void SetAdc02367TpLsbs(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern LSBs
            return SetRegMask(0x1118, 0x00000003, 0, value);
         default:
            throw std::invalid_argument("Function SetAdc02367TpLsbs() not defined for this board version");
      };
   };
   unsigned int GetAdc02367TpLsbsLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern LSBs
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x1118;
         default:
            throw std::invalid_argument("Function GetAdc02367TpLsbsLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_2367_TWOSCOMP
   unsigned int GetAdc02367Twoscomp()
   {
      switch(this->mVersion)
      {
         case 9:
            // Two's Complement Mode Control Bit (0=Offset Binary, 1=Two's Complement)
            return BitExtractControl(0x1118, 0x20000000, 29);
         default:
            throw std::invalid_argument("Function GetAdc02367Twoscomp() not defined for this board version");
      };
   };
   void SetAdc02367Twoscomp(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Two's Complement Mode Control Bit (0=Offset Binary, 1=Two's Complement)
            return SetRegMask(0x1118, 0x20000000, 29, value);
         default:
            throw std::invalid_argument("Function SetAdc02367Twoscomp() not defined for this board version");
      };
   };
   unsigned int GetAdc02367TwoscompLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Two's Complement Mode Control Bit (0=Offset Binary, 1=Two's Complement)
            if(BitMask) *BitMask = 0x20000000;
            if(BitOfs) *BitOfs = 29;
            return 0x1118;
         default:
            throw std::invalid_argument("Function GetAdc02367TwoscompLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_2_NAP_MODE
   unsigned int GetAdc02NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 2 Nap Mode (0=OFF, 1=ON)
            return BitExtractControl(0x1118, 0x01000000, 24);
         default:
            throw std::invalid_argument("Function GetAdc02NapMode() not defined for this board version");
      };
   };
   void SetAdc02NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 2 Nap Mode (0=OFF, 1=ON)
            return SetRegMask(0x1118, 0x01000000, 24, value);
         default:
            throw std::invalid_argument("Function SetAdc02NapMode() not defined for this board version");
      };
   };
   unsigned int GetAdc02NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 2 Nap Mode (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1118;
         default:
            throw std::invalid_argument("Function GetAdc02NapModeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_3_NAP_MODE
   unsigned int GetAdc03NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 3 Nap Mode (0=OFF, 1=ON)
            return BitExtractControl(0x1118, 0x02000000, 25);
         default:
            throw std::invalid_argument("Function GetAdc03NapMode() not defined for this board version");
      };
   };
   void SetAdc03NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 3 Nap Mode (0=OFF, 1=ON)
            return SetRegMask(0x1118, 0x02000000, 25, value);
         default:
            throw std::invalid_argument("Function SetAdc03NapMode() not defined for this board version");
      };
   };
   unsigned int GetAdc03NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 3 Nap Mode (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x02000000;
            if(BitOfs) *BitOfs = 25;
            return 0x1118;
         default:
            throw std::invalid_argument("Function GetAdc03NapModeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_4_NAP_MODE
   unsigned int GetAdc04NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 4 Nap Mode (0=OFF, 1=ON)
            return BitExtractControl(0x1114, 0x02000000, 25);
         default:
            throw std::invalid_argument("Function GetAdc04NapMode() not defined for this board version");
      };
   };
   void SetAdc04NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 4 Nap Mode (0=OFF, 1=ON)
            return SetRegMask(0x1114, 0x02000000, 25, value);
         default:
            throw std::invalid_argument("Function SetAdc04NapMode() not defined for this board version");
      };
   };
   unsigned int GetAdc04NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 4 Nap Mode (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x02000000;
            if(BitOfs) *BitOfs = 25;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdc04NapModeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_5_NAP_MODE
   unsigned int GetAdc05NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 5 Nap Mode (0=OFF, 1=ON)
            return BitExtractControl(0x1114, 0x04000000, 26);
         default:
            throw std::invalid_argument("Function GetAdc05NapMode() not defined for this board version");
      };
   };
   void SetAdc05NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 5 Nap Mode (0=OFF, 1=ON)
            return SetRegMask(0x1114, 0x04000000, 26, value);
         default:
            throw std::invalid_argument("Function SetAdc05NapMode() not defined for this board version");
      };
   };
   unsigned int GetAdc05NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 5 Nap Mode (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x04000000;
            if(BitOfs) *BitOfs = 26;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdc05NapModeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_6_NAP_MODE
   unsigned int GetAdc06NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 6 Nap Mode (0=OFF, 1=ON)
            return BitExtractControl(0x1118, 0x04000000, 26);
         default:
            throw std::invalid_argument("Function GetAdc06NapMode() not defined for this board version");
      };
   };
   void SetAdc06NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 6 Nap Mode (0=OFF, 1=ON)
            return SetRegMask(0x1118, 0x04000000, 26, value);
         default:
            throw std::invalid_argument("Function SetAdc06NapMode() not defined for this board version");
      };
   };
   unsigned int GetAdc06NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 6 Nap Mode (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x04000000;
            if(BitOfs) *BitOfs = 26;
            return 0x1118;
         default:
            throw std::invalid_argument("Function GetAdc06NapModeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_7_NAP_MODE
   unsigned int GetAdc07NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 7 Nap Mode (0=OFF, 1=ON)
            return BitExtractControl(0x1118, 0x08000000, 27);
         default:
            throw std::invalid_argument("Function GetAdc07NapMode() not defined for this board version");
      };
   };
   void SetAdc07NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 7 Nap Mode (0=OFF, 1=ON)
            return SetRegMask(0x1118, 0x08000000, 27, value);
         default:
            throw std::invalid_argument("Function SetAdc07NapMode() not defined for this board version");
      };
   };
   unsigned int GetAdc07NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 7 Nap Mode (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x08000000;
            if(BitOfs) *BitOfs = 27;
            return 0x1118;
         default:
            throw std::invalid_argument("Function GetAdc07NapModeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_8_NAP_MODE
   unsigned int GetAdc08NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 8 Nap Mode (0=OFF, 1=ON)
            return BitExtractControl(0x1114, 0x08000000, 27);
         default:
            throw std::invalid_argument("Function GetAdc08NapMode() not defined for this board version");
      };
   };
   void SetAdc08NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 8 Nap Mode (0=OFF, 1=ON)
            return SetRegMask(0x1114, 0x08000000, 27, value);
         default:
            throw std::invalid_argument("Function SetAdc08NapMode() not defined for this board version");
      };
   };
   unsigned int GetAdc08NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 8 Nap Mode (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x08000000;
            if(BitOfs) *BitOfs = 27;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdc08NapModeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_CHIP_ID
   unsigned int GetAdc0ChipId()
   {
      switch(this->mVersion)
      {
         case 8:
            // Chip ID of ADC 0 (A) (0x93 for AD9637)
            return BitExtractStatus(0x0044, 0xFF000000, 24);
         default:
            throw std::invalid_argument("Function GetAdc0ChipId() not defined for this board version");
      };
   };
   unsigned int GetAdc0ChipIdLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Chip ID of ADC 0 (A) (0x93 for AD9637)
            if(BitMask) *BitMask = 0xFF000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0044;
         default:
            throw std::invalid_argument("Function GetAdc0ChipIdLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_0_SPEED
   unsigned int GetAdc0Speed()
   {
      switch(this->mVersion)
      {
         case 8:
            // Speed Grade of ADC 0 (A) (0=40MS, 1=80MS)
            return BitExtractStatus(0x0044, 0x00700000, 20);
         default:
            throw std::invalid_argument("Function GetAdc0Speed() not defined for this board version");
      };
   };
   unsigned int GetAdc0SpeedLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Speed Grade of ADC 0 (A) (0=40MS, 1=80MS)
            if(BitMask) *BitMask = 0x00700000;
            if(BitOfs) *BitOfs = 20;
            return 0x0044;
         default:
            throw std::invalid_argument("Function GetAdc0SpeedLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_1458_DCSOFF
   unsigned int GetAdc11458Dcsoff()
   {
      switch(this->mVersion)
      {
         case 9:
            // Clock Duty Cycle Stabilizer (0=ON, 1=OFF)
            return BitExtractControl(0x111C, 0x80000000, 31);
         default:
            throw std::invalid_argument("Function GetAdc11458Dcsoff() not defined for this board version");
      };
   };
   void SetAdc11458Dcsoff(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Clock Duty Cycle Stabilizer (0=ON, 1=OFF)
            return SetRegMask(0x111C, 0x80000000, 31, value);
         default:
            throw std::invalid_argument("Function SetAdc11458Dcsoff() not defined for this board version");
      };
   };
   unsigned int GetAdc11458DcsoffLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Clock Duty Cycle Stabilizer (0=ON, 1=OFF)
            if(BitMask) *BitMask = 0x80000000;
            if(BitOfs) *BitOfs = 31;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdc11458DcsoffLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_1458_ILVDS
   unsigned int GetAdc11458Ilvds()
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Output Current Bits (1.75mA - 4.5mA, 0b111 = 2x1.75mA = 3.5mA) (see datasheet)
            return BitExtractControl(0x111C, 0x00E00000, 21);
         default:
            throw std::invalid_argument("Function GetAdc11458Ilvds() not defined for this board version");
      };
   };
   void SetAdc11458Ilvds(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Output Current Bits (1.75mA - 4.5mA, 0b111 = 2x1.75mA = 3.5mA) (see datasheet)
            return SetRegMask(0x111C, 0x00E00000, 21, value);
         default:
            throw std::invalid_argument("Function SetAdc11458Ilvds() not defined for this board version");
      };
   };
   unsigned int GetAdc11458IlvdsLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Output Current Bits (1.75mA - 4.5mA, 0b111 = 2x1.75mA = 3.5mA) (see datasheet)
            if(BitMask) *BitMask = 0x00E00000;
            if(BitOfs) *BitOfs = 21;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdc11458IlvdsLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_1458_OUTMODE
   unsigned int GetAdc11458Outmode()
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Mode Control Bits (0b110 = 12 Bit, 1 Lane) (see datasheet) 
            return BitExtractControl(0x111C, 0x00070000, 16);
         default:
            throw std::invalid_argument("Function GetAdc11458Outmode() not defined for this board version");
      };
   };
   void SetAdc11458Outmode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Mode Control Bits (0b110 = 12 Bit, 1 Lane) (see datasheet) 
            return SetRegMask(0x111C, 0x00070000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdc11458Outmode() not defined for this board version");
      };
   };
   unsigned int GetAdc11458OutmodeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Mode Control Bits (0b110 = 12 Bit, 1 Lane) (see datasheet) 
            if(BitMask) *BitMask = 0x00070000;
            if(BitOfs) *BitOfs = 16;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdc11458OutmodeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_1458_OUTOFF
   unsigned int GetAdc11458Outoff()
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Disable Bit (0=Enabled, 1=Disabled)
            return BitExtractControl(0x111C, 0x00080000, 19);
         default:
            throw std::invalid_argument("Function GetAdc11458Outoff() not defined for this board version");
      };
   };
   void SetAdc11458Outoff(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Disable Bit (0=Enabled, 1=Disabled)
            return SetRegMask(0x111C, 0x00080000, 19, value);
         default:
            throw std::invalid_argument("Function SetAdc11458Outoff() not defined for this board version");
      };
   };
   unsigned int GetAdc11458OutoffLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Disable Bit (0=Enabled, 1=Disabled)
            if(BitMask) *BitMask = 0x00080000;
            if(BitOfs) *BitOfs = 19;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdc11458OutoffLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_1458_OUTTEST
   unsigned int GetAdc11458Outtest()
   {
      switch(this->mVersion)
      {
         case 9:
            // Output Test Pattern Control Bit (0=Pattern Off, 1=Pattern On)
            return BitExtractControl(0x111C, 0x00008000, 15);
         default:
            throw std::invalid_argument("Function GetAdc11458Outtest() not defined for this board version");
      };
   };
   void SetAdc11458Outtest(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Output Test Pattern Control Bit (0=Pattern Off, 1=Pattern On)
            return SetRegMask(0x111C, 0x00008000, 15, value);
         default:
            throw std::invalid_argument("Function SetAdc11458Outtest() not defined for this board version");
      };
   };
   unsigned int GetAdc11458OuttestLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Output Test Pattern Control Bit (0=Pattern Off, 1=Pattern On)
            if(BitMask) *BitMask = 0x00008000;
            if(BitOfs) *BitOfs = 15;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdc11458OuttestLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_1458_RAND
   unsigned int GetAdc11458Rand()
   {
      switch(this->mVersion)
      {
         case 9:
            // Data Output Randomizer Mode Control Bit (0=OFF, 1=ON)
            return BitExtractControl(0x111C, 0x40000000, 30);
         default:
            throw std::invalid_argument("Function GetAdc11458Rand() not defined for this board version");
      };
   };
   void SetAdc11458Rand(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Data Output Randomizer Mode Control Bit (0=OFF, 1=ON)
            return SetRegMask(0x111C, 0x40000000, 30, value);
         default:
            throw std::invalid_argument("Function SetAdc11458Rand() not defined for this board version");
      };
   };
   unsigned int GetAdc11458RandLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Data Output Randomizer Mode Control Bit (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x40000000;
            if(BitOfs) *BitOfs = 30;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdc11458RandLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_1458_SLEEP
   unsigned int GetAdc11458Sleep()
   {
      switch(this->mVersion)
      {
         case 9:
            // Sleep Mode (1=Channels 1, 4, 5 and 8 are disabled)
            return BitExtractControl(0x111C, 0x10000000, 28);
         default:
            throw std::invalid_argument("Function GetAdc11458Sleep() not defined for this board version");
      };
   };
   void SetAdc11458Sleep(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Sleep Mode (1=Channels 1, 4, 5 and 8 are disabled)
            return SetRegMask(0x111C, 0x10000000, 28, value);
         default:
            throw std::invalid_argument("Function SetAdc11458Sleep() not defined for this board version");
      };
   };
   unsigned int GetAdc11458SleepLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Sleep Mode (1=Channels 1, 4, 5 and 8 are disabled)
            if(BitMask) *BitMask = 0x10000000;
            if(BitOfs) *BitOfs = 28;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdc11458SleepLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_1458_TERMON
   unsigned int GetAdc11458Termon()
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Internal Termination Bit (0=OFF, 1=ON)
            return BitExtractControl(0x111C, 0x00100000, 20);
         default:
            throw std::invalid_argument("Function GetAdc11458Termon() not defined for this board version");
      };
   };
   void SetAdc11458Termon(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Internal Termination Bit (0=OFF, 1=ON)
            return SetRegMask(0x111C, 0x00100000, 20, value);
         default:
            throw std::invalid_argument("Function SetAdc11458Termon() not defined for this board version");
      };
   };
   unsigned int GetAdc11458TermonLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Internal Termination Bit (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdc11458TermonLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_1458_TP
   unsigned int GetAdc11458Tp()
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern MSBs (actual test pattern in 12 bit mode)
            return BitExtractControl(0x111C, 0x00003FFC, 2);
         default:
            throw std::invalid_argument("Function GetAdc11458Tp() not defined for this board version");
      };
   };
   void SetAdc11458Tp(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern MSBs (actual test pattern in 12 bit mode)
            return SetRegMask(0x111C, 0x00003FFC, 2, value);
         default:
            throw std::invalid_argument("Function SetAdc11458Tp() not defined for this board version");
      };
   };
   unsigned int GetAdc11458TpLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern MSBs (actual test pattern in 12 bit mode)
            if(BitMask) *BitMask = 0x00003FFC;
            if(BitOfs) *BitOfs = 2;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdc11458TpLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_1458_TP_LSBS
   unsigned int GetAdc11458TpLsbs()
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern LSBs
            return BitExtractControl(0x111C, 0x00000003, 0);
         default:
            throw std::invalid_argument("Function GetAdc11458TpLsbs() not defined for this board version");
      };
   };
   void SetAdc11458TpLsbs(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern LSBs
            return SetRegMask(0x111C, 0x00000003, 0, value);
         default:
            throw std::invalid_argument("Function SetAdc11458TpLsbs() not defined for this board version");
      };
   };
   unsigned int GetAdc11458TpLsbsLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern LSBs
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdc11458TpLsbsLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_1458_TWOSCOMP
   unsigned int GetAdc11458Twoscomp()
   {
      switch(this->mVersion)
      {
         case 9:
            // Two's Complement Mode Control Bit (0=Offset Binary, 1=Two's Complement)
            return BitExtractControl(0x111C, 0x20000000, 29);
         default:
            throw std::invalid_argument("Function GetAdc11458Twoscomp() not defined for this board version");
      };
   };
   void SetAdc11458Twoscomp(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Two's Complement Mode Control Bit (0=Offset Binary, 1=Two's Complement)
            return SetRegMask(0x111C, 0x20000000, 29, value);
         default:
            throw std::invalid_argument("Function SetAdc11458Twoscomp() not defined for this board version");
      };
   };
   unsigned int GetAdc11458TwoscompLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Two's Complement Mode Control Bit (0=Offset Binary, 1=Two's Complement)
            if(BitMask) *BitMask = 0x20000000;
            if(BitOfs) *BitOfs = 29;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdc11458TwoscompLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_1_NAP_MODE
   unsigned int GetAdc11NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 1 Nap Mode (0=OFF, 1=ON)
            return BitExtractControl(0x111C, 0x01000000, 24);
         default:
            throw std::invalid_argument("Function GetAdc11NapMode() not defined for this board version");
      };
   };
   void SetAdc11NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 1 Nap Mode (0=OFF, 1=ON)
            return SetRegMask(0x111C, 0x01000000, 24, value);
         default:
            throw std::invalid_argument("Function SetAdc11NapMode() not defined for this board version");
      };
   };
   unsigned int GetAdc11NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 1 Nap Mode (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdc11NapModeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_2367_DCSOFF
   unsigned int GetAdc12367Dcsoff()
   {
      switch(this->mVersion)
      {
         case 9:
            // Clock Duty Cycle Stabilizer (0=ON, 1=OFF)
            return BitExtractControl(0x1120, 0x80000000, 31);
         default:
            throw std::invalid_argument("Function GetAdc12367Dcsoff() not defined for this board version");
      };
   };
   void SetAdc12367Dcsoff(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Clock Duty Cycle Stabilizer (0=ON, 1=OFF)
            return SetRegMask(0x1120, 0x80000000, 31, value);
         default:
            throw std::invalid_argument("Function SetAdc12367Dcsoff() not defined for this board version");
      };
   };
   unsigned int GetAdc12367DcsoffLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Clock Duty Cycle Stabilizer (0=ON, 1=OFF)
            if(BitMask) *BitMask = 0x80000000;
            if(BitOfs) *BitOfs = 31;
            return 0x1120;
         default:
            throw std::invalid_argument("Function GetAdc12367DcsoffLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_2367_ILVDS
   unsigned int GetAdc12367Ilvds()
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Output Current Bits (1.75mA - 4.5mA, 0b111 = 2x1.75mA = 3.5mA) (see datasheet)
            return BitExtractControl(0x1120, 0x00E00000, 21);
         default:
            throw std::invalid_argument("Function GetAdc12367Ilvds() not defined for this board version");
      };
   };
   void SetAdc12367Ilvds(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Output Current Bits (1.75mA - 4.5mA, 0b111 = 2x1.75mA = 3.5mA) (see datasheet)
            return SetRegMask(0x1120, 0x00E00000, 21, value);
         default:
            throw std::invalid_argument("Function SetAdc12367Ilvds() not defined for this board version");
      };
   };
   unsigned int GetAdc12367IlvdsLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Output Current Bits (1.75mA - 4.5mA, 0b111 = 2x1.75mA = 3.5mA) (see datasheet)
            if(BitMask) *BitMask = 0x00E00000;
            if(BitOfs) *BitOfs = 21;
            return 0x1120;
         default:
            throw std::invalid_argument("Function GetAdc12367IlvdsLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_2367_OUTMODE
   unsigned int GetAdc12367Outmode()
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Mode Control Bits (0b110 = 12 Bit, 1 Lane) (see datasheet) 
            return BitExtractControl(0x1120, 0x00070000, 16);
         default:
            throw std::invalid_argument("Function GetAdc12367Outmode() not defined for this board version");
      };
   };
   void SetAdc12367Outmode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Mode Control Bits (0b110 = 12 Bit, 1 Lane) (see datasheet) 
            return SetRegMask(0x1120, 0x00070000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdc12367Outmode() not defined for this board version");
      };
   };
   unsigned int GetAdc12367OutmodeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Mode Control Bits (0b110 = 12 Bit, 1 Lane) (see datasheet) 
            if(BitMask) *BitMask = 0x00070000;
            if(BitOfs) *BitOfs = 16;
            return 0x1120;
         default:
            throw std::invalid_argument("Function GetAdc12367OutmodeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_2367_OUTOFF
   unsigned int GetAdc12367Outoff()
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Disable Bit (0=Enabled, 1=Disabled)
            return BitExtractControl(0x1120, 0x00080000, 19);
         default:
            throw std::invalid_argument("Function GetAdc12367Outoff() not defined for this board version");
      };
   };
   void SetAdc12367Outoff(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Disable Bit (0=Enabled, 1=Disabled)
            return SetRegMask(0x1120, 0x00080000, 19, value);
         default:
            throw std::invalid_argument("Function SetAdc12367Outoff() not defined for this board version");
      };
   };
   unsigned int GetAdc12367OutoffLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Digital Output Disable Bit (0=Enabled, 1=Disabled)
            if(BitMask) *BitMask = 0x00080000;
            if(BitOfs) *BitOfs = 19;
            return 0x1120;
         default:
            throw std::invalid_argument("Function GetAdc12367OutoffLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_2367_OUTTEST
   unsigned int GetAdc12367Outtest()
   {
      switch(this->mVersion)
      {
         case 9:
            // Output Test Pattern Control Bit (0=Pattern Off, 1=Pattern On)
            return BitExtractControl(0x1120, 0x00008000, 15);
         default:
            throw std::invalid_argument("Function GetAdc12367Outtest() not defined for this board version");
      };
   };
   void SetAdc12367Outtest(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Output Test Pattern Control Bit (0=Pattern Off, 1=Pattern On)
            return SetRegMask(0x1120, 0x00008000, 15, value);
         default:
            throw std::invalid_argument("Function SetAdc12367Outtest() not defined for this board version");
      };
   };
   unsigned int GetAdc12367OuttestLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Output Test Pattern Control Bit (0=Pattern Off, 1=Pattern On)
            if(BitMask) *BitMask = 0x00008000;
            if(BitOfs) *BitOfs = 15;
            return 0x1120;
         default:
            throw std::invalid_argument("Function GetAdc12367OuttestLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_2367_RAND
   unsigned int GetAdc12367Rand()
   {
      switch(this->mVersion)
      {
         case 9:
            // Data Output Randomizer Mode Control Bit (0=OFF, 1=ON)
            return BitExtractControl(0x1120, 0x40000000, 30);
         default:
            throw std::invalid_argument("Function GetAdc12367Rand() not defined for this board version");
      };
   };
   void SetAdc12367Rand(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Data Output Randomizer Mode Control Bit (0=OFF, 1=ON)
            return SetRegMask(0x1120, 0x40000000, 30, value);
         default:
            throw std::invalid_argument("Function SetAdc12367Rand() not defined for this board version");
      };
   };
   unsigned int GetAdc12367RandLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Data Output Randomizer Mode Control Bit (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x40000000;
            if(BitOfs) *BitOfs = 30;
            return 0x1120;
         default:
            throw std::invalid_argument("Function GetAdc12367RandLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_2367_SLEEP
   unsigned int GetAdc12367Sleep()
   {
      switch(this->mVersion)
      {
         case 9:
            // Sleep Mode (1=Channels 2, 3, 6 and 7 are disabled)
            return BitExtractControl(0x1120, 0x10000000, 28);
         default:
            throw std::invalid_argument("Function GetAdc12367Sleep() not defined for this board version");
      };
   };
   void SetAdc12367Sleep(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Sleep Mode (1=Channels 2, 3, 6 and 7 are disabled)
            return SetRegMask(0x1120, 0x10000000, 28, value);
         default:
            throw std::invalid_argument("Function SetAdc12367Sleep() not defined for this board version");
      };
   };
   unsigned int GetAdc12367SleepLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Sleep Mode (1=Channels 2, 3, 6 and 7 are disabled)
            if(BitMask) *BitMask = 0x10000000;
            if(BitOfs) *BitOfs = 28;
            return 0x1120;
         default:
            throw std::invalid_argument("Function GetAdc12367SleepLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_2367_TERMON
   unsigned int GetAdc12367Termon()
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Internal Termination Bit (0=OFF, 1=ON)
            return BitExtractControl(0x1120, 0x00100000, 20);
         default:
            throw std::invalid_argument("Function GetAdc12367Termon() not defined for this board version");
      };
   };
   void SetAdc12367Termon(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Internal Termination Bit (0=OFF, 1=ON)
            return SetRegMask(0x1120, 0x00100000, 20, value);
         default:
            throw std::invalid_argument("Function SetAdc12367Termon() not defined for this board version");
      };
   };
   unsigned int GetAdc12367TermonLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // LVDS Internal Termination Bit (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x1120;
         default:
            throw std::invalid_argument("Function GetAdc12367TermonLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_2367_TP
   unsigned int GetAdc12367Tp()
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern MSBs (actual test pattern in 12 bit mode)
            return BitExtractControl(0x1120, 0x00003FFC, 2);
         default:
            throw std::invalid_argument("Function GetAdc12367Tp() not defined for this board version");
      };
   };
   void SetAdc12367Tp(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern MSBs (actual test pattern in 12 bit mode)
            return SetRegMask(0x1120, 0x00003FFC, 2, value);
         default:
            throw std::invalid_argument("Function SetAdc12367Tp() not defined for this board version");
      };
   };
   unsigned int GetAdc12367TpLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern MSBs (actual test pattern in 12 bit mode)
            if(BitMask) *BitMask = 0x00003FFC;
            if(BitOfs) *BitOfs = 2;
            return 0x1120;
         default:
            throw std::invalid_argument("Function GetAdc12367TpLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_2367_TP_LSBS
   unsigned int GetAdc12367TpLsbs()
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern LSBs
            return BitExtractControl(0x1120, 0x00000003, 0);
         default:
            throw std::invalid_argument("Function GetAdc12367TpLsbs() not defined for this board version");
      };
   };
   void SetAdc12367TpLsbs(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern LSBs
            return SetRegMask(0x1120, 0x00000003, 0, value);
         default:
            throw std::invalid_argument("Function SetAdc12367TpLsbs() not defined for this board version");
      };
   };
   unsigned int GetAdc12367TpLsbsLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Test Pattern LSBs
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x1120;
         default:
            throw std::invalid_argument("Function GetAdc12367TpLsbsLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_2367_TWOSCOMP
   unsigned int GetAdc12367Twoscomp()
   {
      switch(this->mVersion)
      {
         case 9:
            // Two's Complement Mode Control Bit (0=Offset Binary, 1=Two's Complement)
            return BitExtractControl(0x1120, 0x20000000, 29);
         default:
            throw std::invalid_argument("Function GetAdc12367Twoscomp() not defined for this board version");
      };
   };
   void SetAdc12367Twoscomp(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Two's Complement Mode Control Bit (0=Offset Binary, 1=Two's Complement)
            return SetRegMask(0x1120, 0x20000000, 29, value);
         default:
            throw std::invalid_argument("Function SetAdc12367Twoscomp() not defined for this board version");
      };
   };
   unsigned int GetAdc12367TwoscompLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Two's Complement Mode Control Bit (0=Offset Binary, 1=Two's Complement)
            if(BitMask) *BitMask = 0x20000000;
            if(BitOfs) *BitOfs = 29;
            return 0x1120;
         default:
            throw std::invalid_argument("Function GetAdc12367TwoscompLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_2_NAP_MODE
   unsigned int GetAdc12NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 2 Nap Mode (0=OFF, 1=ON)
            return BitExtractControl(0x1120, 0x01000000, 24);
         default:
            throw std::invalid_argument("Function GetAdc12NapMode() not defined for this board version");
      };
   };
   void SetAdc12NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 2 Nap Mode (0=OFF, 1=ON)
            return SetRegMask(0x1120, 0x01000000, 24, value);
         default:
            throw std::invalid_argument("Function SetAdc12NapMode() not defined for this board version");
      };
   };
   unsigned int GetAdc12NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 2 Nap Mode (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1120;
         default:
            throw std::invalid_argument("Function GetAdc12NapModeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_3_NAP_MODE
   unsigned int GetAdc13NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 3 Nap Mode (0=OFF, 1=ON)
            return BitExtractControl(0x1120, 0x02000000, 25);
         default:
            throw std::invalid_argument("Function GetAdc13NapMode() not defined for this board version");
      };
   };
   void SetAdc13NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 3 Nap Mode (0=OFF, 1=ON)
            return SetRegMask(0x1120, 0x02000000, 25, value);
         default:
            throw std::invalid_argument("Function SetAdc13NapMode() not defined for this board version");
      };
   };
   unsigned int GetAdc13NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 3 Nap Mode (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x02000000;
            if(BitOfs) *BitOfs = 25;
            return 0x1120;
         default:
            throw std::invalid_argument("Function GetAdc13NapModeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_4_NAP_MODE
   unsigned int GetAdc14NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 4 Nap Mode (0=OFF, 1=ON)
            return BitExtractControl(0x111C, 0x02000000, 25);
         default:
            throw std::invalid_argument("Function GetAdc14NapMode() not defined for this board version");
      };
   };
   void SetAdc14NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 4 Nap Mode (0=OFF, 1=ON)
            return SetRegMask(0x111C, 0x02000000, 25, value);
         default:
            throw std::invalid_argument("Function SetAdc14NapMode() not defined for this board version");
      };
   };
   unsigned int GetAdc14NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 4 Nap Mode (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x02000000;
            if(BitOfs) *BitOfs = 25;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdc14NapModeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_5_NAP_MODE
   unsigned int GetAdc15NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 5 Nap Mode (0=OFF, 1=ON)
            return BitExtractControl(0x111C, 0x04000000, 26);
         default:
            throw std::invalid_argument("Function GetAdc15NapMode() not defined for this board version");
      };
   };
   void SetAdc15NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 5 Nap Mode (0=OFF, 1=ON)
            return SetRegMask(0x111C, 0x04000000, 26, value);
         default:
            throw std::invalid_argument("Function SetAdc15NapMode() not defined for this board version");
      };
   };
   unsigned int GetAdc15NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 5 Nap Mode (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x04000000;
            if(BitOfs) *BitOfs = 26;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdc15NapModeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_6_NAP_MODE
   unsigned int GetAdc16NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 6 Nap Mode (0=OFF, 1=ON)
            return BitExtractControl(0x1120, 0x04000000, 26);
         default:
            throw std::invalid_argument("Function GetAdc16NapMode() not defined for this board version");
      };
   };
   void SetAdc16NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 6 Nap Mode (0=OFF, 1=ON)
            return SetRegMask(0x1120, 0x04000000, 26, value);
         default:
            throw std::invalid_argument("Function SetAdc16NapMode() not defined for this board version");
      };
   };
   unsigned int GetAdc16NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 6 Nap Mode (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x04000000;
            if(BitOfs) *BitOfs = 26;
            return 0x1120;
         default:
            throw std::invalid_argument("Function GetAdc16NapModeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_7_NAP_MODE
   unsigned int GetAdc17NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 7 Nap Mode (0=OFF, 1=ON)
            return BitExtractControl(0x1120, 0x08000000, 27);
         default:
            throw std::invalid_argument("Function GetAdc17NapMode() not defined for this board version");
      };
   };
   void SetAdc17NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 7 Nap Mode (0=OFF, 1=ON)
            return SetRegMask(0x1120, 0x08000000, 27, value);
         default:
            throw std::invalid_argument("Function SetAdc17NapMode() not defined for this board version");
      };
   };
   unsigned int GetAdc17NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 7 Nap Mode (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x08000000;
            if(BitOfs) *BitOfs = 27;
            return 0x1120;
         default:
            throw std::invalid_argument("Function GetAdc17NapModeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_8_NAP_MODE
   unsigned int GetAdc18NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 8 Nap Mode (0=OFF, 1=ON)
            return BitExtractControl(0x111C, 0x08000000, 27);
         default:
            throw std::invalid_argument("Function GetAdc18NapMode() not defined for this board version");
      };
   };
   void SetAdc18NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 8 Nap Mode (0=OFF, 1=ON)
            return SetRegMask(0x111C, 0x08000000, 27, value);
         default:
            throw std::invalid_argument("Function SetAdc18NapMode() not defined for this board version");
      };
   };
   unsigned int GetAdc18NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Channel 8 Nap Mode (0=OFF, 1=ON)
            if(BitMask) *BitMask = 0x08000000;
            if(BitOfs) *BitOfs = 27;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdc18NapModeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_CHIP_ID
   unsigned int GetAdc1ChipId()
   {
      switch(this->mVersion)
      {
         case 8:
            // Chip ID of ADC 1 (B) (0x93 for AD9637)
            return BitExtractStatus(0x0044, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdc1ChipId() not defined for this board version");
      };
   };
   unsigned int GetAdc1ChipIdLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Chip ID of ADC 1 (B) (0x93 for AD9637)
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x0044;
         default:
            throw std::invalid_argument("Function GetAdc1ChipIdLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_1_SPEED
   unsigned int GetAdc1Speed()
   {
      switch(this->mVersion)
      {
         case 8:
            // Speed Grade of ADC 1 (B) (0=40MS, 1=80MS)
            return BitExtractStatus(0x0044, 0x00000070, 4);
         default:
            throw std::invalid_argument("Function GetAdc1Speed() not defined for this board version");
      };
   };
   unsigned int GetAdc1SpeedLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Speed Grade of ADC 1 (B) (0=40MS, 1=80MS)
            if(BitMask) *BitMask = 0x00000070;
            if(BitOfs) *BitOfs = 4;
            return 0x0044;
         default:
            throw std::invalid_argument("Function GetAdc1SpeedLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_CAL_PATTERN_EN
   unsigned int GetAdcCalPatternEn()
   {
      switch(this->mVersion)
      {
         case 9:
            // Enable ADC calibration pattern
            return BitExtractControl(0x1008, 0x01000000, 24);
         default:
            throw std::invalid_argument("Function GetAdcCalPatternEn() not defined for this board version");
      };
   };
   void SetAdcCalPatternEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Enable ADC calibration pattern
            return SetRegMask(0x1008, 0x01000000, 24, value);
         default:
            throw std::invalid_argument("Function SetAdcCalPatternEn() not defined for this board version");
      };
   };
   unsigned int GetAdcCalPatternEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Enable ADC calibration pattern
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1008;
         default:
            throw std::invalid_argument("Function GetAdcCalPatternEnLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_CFG_16_BIT_ADDR_LSB
   unsigned int GetAdcCfg16BitAddrLsb()
   {
      switch(this->mVersion)
      {
         case 8:
            // ADC Address Mode (to be mirrored to bit28)
            return BitExtractControl(0x1114, 0x08000000, 27);
         default:
            throw std::invalid_argument("Function GetAdcCfg16BitAddrLsb() not defined for this board version");
      };
   };
   void SetAdcCfg16BitAddrLsb(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // ADC Address Mode (to be mirrored to bit28)
            return SetRegMask(0x1114, 0x08000000, 27, value);
         default:
            throw std::invalid_argument("Function SetAdcCfg16BitAddrLsb() not defined for this board version");
      };
   };
   unsigned int GetAdcCfg16BitAddrLsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // ADC Address Mode (to be mirrored to bit28)
            if(BitMask) *BitMask = 0x08000000;
            if(BitOfs) *BitOfs = 27;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdcCfg16BitAddrLsbLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_CFG_16_BIT_ADDR_MSB
   unsigned int GetAdcCfg16BitAddrMsb()
   {
      switch(this->mVersion)
      {
         case 8:
            // ADC Address Mode (to be mirrored to bit27)
            return BitExtractControl(0x1114, 0x10000000, 28);
         default:
            throw std::invalid_argument("Function GetAdcCfg16BitAddrMsb() not defined for this board version");
      };
   };
   void SetAdcCfg16BitAddrMsb(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // ADC Address Mode (to be mirrored to bit27)
            return SetRegMask(0x1114, 0x10000000, 28, value);
         default:
            throw std::invalid_argument("Function SetAdcCfg16BitAddrMsb() not defined for this board version");
      };
   };
   unsigned int GetAdcCfg16BitAddrMsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // ADC Address Mode (to be mirrored to bit27)
            if(BitMask) *BitMask = 0x10000000;
            if(BitOfs) *BitOfs = 28;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdcCfg16BitAddrMsbLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_CFG_LSB_FIRST_LSB
   unsigned int GetAdcCfgLsbFirstLsb()
   {
      switch(this->mVersion)
      {
         case 8:
            // Transmit LSB First (to be mirrored to bit30)
            return BitExtractControl(0x1114, 0x02000000, 25);
         default:
            throw std::invalid_argument("Function GetAdcCfgLsbFirstLsb() not defined for this board version");
      };
   };
   void SetAdcCfgLsbFirstLsb(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Transmit LSB First (to be mirrored to bit30)
            return SetRegMask(0x1114, 0x02000000, 25, value);
         default:
            throw std::invalid_argument("Function SetAdcCfgLsbFirstLsb() not defined for this board version");
      };
   };
   unsigned int GetAdcCfgLsbFirstLsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Transmit LSB First (to be mirrored to bit30)
            if(BitMask) *BitMask = 0x02000000;
            if(BitOfs) *BitOfs = 25;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdcCfgLsbFirstLsbLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_CFG_LSB_FIRST_MSB
   unsigned int GetAdcCfgLsbFirstMsb()
   {
      switch(this->mVersion)
      {
         case 8:
            // Transmit LSB First (to be mirrored to bit25)
            return BitExtractControl(0x1114, 0x40000000, 30);
         default:
            throw std::invalid_argument("Function GetAdcCfgLsbFirstMsb() not defined for this board version");
      };
   };
   void SetAdcCfgLsbFirstMsb(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Transmit LSB First (to be mirrored to bit25)
            return SetRegMask(0x1114, 0x40000000, 30, value);
         default:
            throw std::invalid_argument("Function SetAdcCfgLsbFirstMsb() not defined for this board version");
      };
   };
   unsigned int GetAdcCfgLsbFirstMsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Transmit LSB First (to be mirrored to bit25)
            if(BitMask) *BitMask = 0x40000000;
            if(BitOfs) *BitOfs = 30;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdcCfgLsbFirstMsbLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_CFG_SDO_ACTIVE_LSB
   unsigned int GetAdcCfgSdoActiveLsb()
   {
      switch(this->mVersion)
      {
         case 8:
            // Activate SDO (to be mirrored to bit31)
            return BitExtractControl(0x1114, 0x01000000, 24);
         default:
            throw std::invalid_argument("Function GetAdcCfgSdoActiveLsb() not defined for this board version");
      };
   };
   void SetAdcCfgSdoActiveLsb(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Activate SDO (to be mirrored to bit31)
            return SetRegMask(0x1114, 0x01000000, 24, value);
         default:
            throw std::invalid_argument("Function SetAdcCfgSdoActiveLsb() not defined for this board version");
      };
   };
   unsigned int GetAdcCfgSdoActiveLsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Activate SDO (to be mirrored to bit31)
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdcCfgSdoActiveLsbLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_CFG_SDO_ACTIVE_MSB
   unsigned int GetAdcCfgSdoActiveMsb()
   {
      switch(this->mVersion)
      {
         case 8:
            // Activate SDO (to be mirrored to bit24)
            return BitExtractControl(0x1114, 0x80000000, 31);
         default:
            throw std::invalid_argument("Function GetAdcCfgSdoActiveMsb() not defined for this board version");
      };
   };
   void SetAdcCfgSdoActiveMsb(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Activate SDO (to be mirrored to bit24)
            return SetRegMask(0x1114, 0x80000000, 31, value);
         default:
            throw std::invalid_argument("Function SetAdcCfgSdoActiveMsb() not defined for this board version");
      };
   };
   unsigned int GetAdcCfgSdoActiveMsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Activate SDO (to be mirrored to bit24)
            if(BitMask) *BitMask = 0x80000000;
            if(BitOfs) *BitOfs = 31;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdcCfgSdoActiveMsbLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_CFG_SOFT_RESET_LSB
   unsigned int GetAdcCfgSoftResetLsb()
   {
      switch(this->mVersion)
      {
         case 8:
            // Soft Reset (automatically cleared) (to be mirrored to bit29)
            return BitExtractControl(0x1114, 0x04000000, 26);
         default:
            throw std::invalid_argument("Function GetAdcCfgSoftResetLsb() not defined for this board version");
      };
   };
   void SetAdcCfgSoftResetLsb(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Soft Reset (automatically cleared) (to be mirrored to bit29)
            return SetRegMask(0x1114, 0x04000000, 26, value);
         default:
            throw std::invalid_argument("Function SetAdcCfgSoftResetLsb() not defined for this board version");
      };
   };
   unsigned int GetAdcCfgSoftResetLsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Soft Reset (automatically cleared) (to be mirrored to bit29)
            if(BitMask) *BitMask = 0x04000000;
            if(BitOfs) *BitOfs = 26;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdcCfgSoftResetLsbLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_CFG_SOFT_RESET_MSB
   unsigned int GetAdcCfgSoftResetMsb()
   {
      switch(this->mVersion)
      {
         case 8:
            // Soft Reset (automatically cleared) (to be mirrored to bit26)
            return BitExtractControl(0x1114, 0x20000000, 29);
         default:
            throw std::invalid_argument("Function GetAdcCfgSoftResetMsb() not defined for this board version");
      };
   };
   void SetAdcCfgSoftResetMsb(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Soft Reset (automatically cleared) (to be mirrored to bit26)
            return SetRegMask(0x1114, 0x20000000, 29, value);
         default:
            throw std::invalid_argument("Function SetAdcCfgSoftResetMsb() not defined for this board version");
      };
   };
   unsigned int GetAdcCfgSoftResetMsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Soft Reset (automatically cleared) (to be mirrored to bit26)
            if(BitMask) *BitMask = 0x20000000;
            if(BitOfs) *BitOfs = 29;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdcCfgSoftResetMsbLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_CH_TX_EN
   unsigned int GetAdcChTxEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // ADC channel transmission enable [Ch15:Ch0]
            return BitExtractControl(0x1020, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdcChTxEn() not defined for this board version");
      };
   };
   void SetAdcChTxEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // ADC channel transmission enable [Ch15:Ch0]
            return SetRegMask(0x1020, 0x0000FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdcChTxEn() not defined for this board version");
      };
   };
   unsigned int GetAdcChTxEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // ADC channel transmission enable [Ch15:Ch0]
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1020;
         default:
            throw std::invalid_argument("Function GetAdcChTxEnLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_CLK_DIV_RATIO
   unsigned int GetAdcClkDivRatio()
   {
      switch(this->mVersion)
      {
         case 8:
            // Clock Divide Ratio (value+1)
            return BitExtractControl(0x1118, 0x00000700, 8);
         default:
            throw std::invalid_argument("Function GetAdcClkDivRatio() not defined for this board version");
      };
   };
   void SetAdcClkDivRatio(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Clock Divide Ratio (value+1)
            return SetRegMask(0x1118, 0x00000700, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcClkDivRatio() not defined for this board version");
      };
   };
   unsigned int GetAdcClkDivRatioLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Clock Divide Ratio (value+1)
            if(BitMask) *BitMask = 0x00000700;
            if(BitOfs) *BitOfs = 8;
            return 0x1118;
         default:
            throw std::invalid_argument("Function GetAdcClkDivRatioLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_CLK_DUTY_CYC_STAB
   unsigned int GetAdcClkDutyCycStab()
   {
      switch(this->mVersion)
      {
         case 8:
            // Duty Cycle Stabilizer (0 = off, 1 = on)
            return BitExtractControl(0x1118, 0x00010000, 16);
         default:
            throw std::invalid_argument("Function GetAdcClkDutyCycStab() not defined for this board version");
      };
   };
   void SetAdcClkDutyCycStab(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Duty Cycle Stabilizer (0 = off, 1 = on)
            return SetRegMask(0x1118, 0x00010000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcClkDutyCycStab() not defined for this board version");
      };
   };
   unsigned int GetAdcClkDutyCycStabLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Duty Cycle Stabilizer (0 = off, 1 = on)
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x1118;
         default:
            throw std::invalid_argument("Function GetAdcClkDutyCycStabLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_DI1_C_CHN_DCO
   unsigned int GetAdcDi1CChnDco()
   {
      switch(this->mVersion)
      {
         case 8:
            // Clock Channel DCO Activiation for Writes
            return BitExtractControl(0x1114, 0x00002000, 13);
         default:
            throw std::invalid_argument("Function GetAdcDi1CChnDco() not defined for this board version");
      };
   };
   void SetAdcDi1CChnDco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Clock Channel DCO Activiation for Writes
            return SetRegMask(0x1114, 0x00002000, 13, value);
         default:
            throw std::invalid_argument("Function SetAdcDi1CChnDco() not defined for this board version");
      };
   };
   unsigned int GetAdcDi1CChnDcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Clock Channel DCO Activiation for Writes
            if(BitMask) *BitMask = 0x00002000;
            if(BitOfs) *BitOfs = 13;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdcDi1CChnDcoLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_DI1_C_CHN_FCO
   unsigned int GetAdcDi1CChnFco()
   {
      switch(this->mVersion)
      {
         case 8:
            // Clock Channel FCO Activiation for Writes
            return BitExtractControl(0x1114, 0x00001000, 12);
         default:
            throw std::invalid_argument("Function GetAdcDi1CChnFco() not defined for this board version");
      };
   };
   void SetAdcDi1CChnFco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Clock Channel FCO Activiation for Writes
            return SetRegMask(0x1114, 0x00001000, 12, value);
         default:
            throw std::invalid_argument("Function SetAdcDi1CChnFco() not defined for this board version");
      };
   };
   unsigned int GetAdcDi1CChnFcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Clock Channel FCO Activiation for Writes
            if(BitMask) *BitMask = 0x00001000;
            if(BitOfs) *BitOfs = 12;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdcDi1CChnFcoLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_DI1_D_CHN_A
   unsigned int GetAdcDi1DChnA()
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel A Activiation for Writes
            return BitExtractControl(0x1114, 0x00000100, 8);
         default:
            throw std::invalid_argument("Function GetAdcDi1DChnA() not defined for this board version");
      };
   };
   void SetAdcDi1DChnA(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel A Activiation for Writes
            return SetRegMask(0x1114, 0x00000100, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcDi1DChnA() not defined for this board version");
      };
   };
   unsigned int GetAdcDi1DChnALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel A Activiation for Writes
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdcDi1DChnALoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_DI1_D_CHN_B
   unsigned int GetAdcDi1DChnB()
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel B Activiation for Writes
            return BitExtractControl(0x1114, 0x00000200, 9);
         default:
            throw std::invalid_argument("Function GetAdcDi1DChnB() not defined for this board version");
      };
   };
   void SetAdcDi1DChnB(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel B Activiation for Writes
            return SetRegMask(0x1114, 0x00000200, 9, value);
         default:
            throw std::invalid_argument("Function SetAdcDi1DChnB() not defined for this board version");
      };
   };
   unsigned int GetAdcDi1DChnBLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel B Activiation for Writes
            if(BitMask) *BitMask = 0x00000200;
            if(BitOfs) *BitOfs = 9;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdcDi1DChnBLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_DI1_D_CHN_C
   unsigned int GetAdcDi1DChnC()
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel C Activiation for Writes
            return BitExtractControl(0x1114, 0x00000400, 10);
         default:
            throw std::invalid_argument("Function GetAdcDi1DChnC() not defined for this board version");
      };
   };
   void SetAdcDi1DChnC(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel C Activiation for Writes
            return SetRegMask(0x1114, 0x00000400, 10, value);
         default:
            throw std::invalid_argument("Function SetAdcDi1DChnC() not defined for this board version");
      };
   };
   unsigned int GetAdcDi1DChnCLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel C Activiation for Writes
            if(BitMask) *BitMask = 0x00000400;
            if(BitOfs) *BitOfs = 10;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdcDi1DChnCLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_DI1_D_CHN_D
   unsigned int GetAdcDi1DChnD()
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel D Activiation for Writes
            return BitExtractControl(0x1114, 0x00000800, 11);
         default:
            throw std::invalid_argument("Function GetAdcDi1DChnD() not defined for this board version");
      };
   };
   void SetAdcDi1DChnD(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel D Activiation for Writes
            return SetRegMask(0x1114, 0x00000800, 11, value);
         default:
            throw std::invalid_argument("Function SetAdcDi1DChnD() not defined for this board version");
      };
   };
   unsigned int GetAdcDi1DChnDLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel D Activiation for Writes
            if(BitMask) *BitMask = 0x00000800;
            if(BitOfs) *BitOfs = 11;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdcDi1DChnDLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_DI2_D_CHN_E
   unsigned int GetAdcDi2DChnE()
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel E Activiation for Writes
            return BitExtractControl(0x1114, 0x00010000, 16);
         default:
            throw std::invalid_argument("Function GetAdcDi2DChnE() not defined for this board version");
      };
   };
   void SetAdcDi2DChnE(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel E Activiation for Writes
            return SetRegMask(0x1114, 0x00010000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcDi2DChnE() not defined for this board version");
      };
   };
   unsigned int GetAdcDi2DChnELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel E Activiation for Writes
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdcDi2DChnELoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_DI2_D_CHN_F
   unsigned int GetAdcDi2DChnF()
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel F Activiation for Writes
            return BitExtractControl(0x1114, 0x00020000, 17);
         default:
            throw std::invalid_argument("Function GetAdcDi2DChnF() not defined for this board version");
      };
   };
   void SetAdcDi2DChnF(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel F Activiation for Writes
            return SetRegMask(0x1114, 0x00020000, 17, value);
         default:
            throw std::invalid_argument("Function SetAdcDi2DChnF() not defined for this board version");
      };
   };
   unsigned int GetAdcDi2DChnFLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel F Activiation for Writes
            if(BitMask) *BitMask = 0x00020000;
            if(BitOfs) *BitOfs = 17;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdcDi2DChnFLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_DI2_D_CHN_G
   unsigned int GetAdcDi2DChnG()
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel G Activiation for Writes
            return BitExtractControl(0x1114, 0x00040000, 18);
         default:
            throw std::invalid_argument("Function GetAdcDi2DChnG() not defined for this board version");
      };
   };
   void SetAdcDi2DChnG(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel G Activiation for Writes
            return SetRegMask(0x1114, 0x00040000, 18, value);
         default:
            throw std::invalid_argument("Function SetAdcDi2DChnG() not defined for this board version");
      };
   };
   unsigned int GetAdcDi2DChnGLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel G Activiation for Writes
            if(BitMask) *BitMask = 0x00040000;
            if(BitOfs) *BitOfs = 18;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdcDi2DChnGLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_DI2_D_CHN_H
   unsigned int GetAdcDi2DChnH()
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel H Activiation for Writes
            return BitExtractControl(0x1114, 0x00080000, 19);
         default:
            throw std::invalid_argument("Function GetAdcDi2DChnH() not defined for this board version");
      };
   };
   void SetAdcDi2DChnH(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel H Activiation for Writes
            return SetRegMask(0x1114, 0x00080000, 19, value);
         default:
            throw std::invalid_argument("Function SetAdcDi2DChnH() not defined for this board version");
      };
   };
   unsigned int GetAdcDi2DChnHLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Data Channel H Activiation for Writes
            if(BitMask) *BitMask = 0x00080000;
            if(BitOfs) *BitOfs = 19;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdcDi2DChnHLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_ENH_CHOP_MODE
   unsigned int GetAdcEnhChopMode()
   {
      switch(this->mVersion)
      {
         case 8:
            // Chop Mode (0 = off, 1 = on)
            return BitExtractControl(0x1118, 0x00000010, 4);
         default:
            throw std::invalid_argument("Function GetAdcEnhChopMode() not defined for this board version");
      };
   };
   void SetAdcEnhChopMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Chop Mode (0 = off, 1 = on)
            return SetRegMask(0x1118, 0x00000010, 4, value);
         default:
            throw std::invalid_argument("Function SetAdcEnhChopMode() not defined for this board version");
      };
   };
   unsigned int GetAdcEnhChopModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Chop Mode (0 = off, 1 = on)
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x1118;
         default:
            throw std::invalid_argument("Function GetAdcEnhChopModeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_EN_SYNC
   unsigned int GetAdcEnSync()
   {
      switch(this->mVersion)
      {
         case 8:
            // Enable Sync
            return BitExtractControl(0x112C, 0x00000001, 0);
         default:
            throw std::invalid_argument("Function GetAdcEnSync() not defined for this board version");
      };
   };
   void SetAdcEnSync(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Enable Sync
            return SetRegMask(0x112C, 0x00000001, 0, value);
         default:
            throw std::invalid_argument("Function SetAdcEnSync() not defined for this board version");
      };
   };
   unsigned int GetAdcEnSyncLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Enable Sync
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x112C;
         default:
            throw std::invalid_argument("Function GetAdcEnSyncLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_IF_RST
   unsigned int GetAdcIfRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the ADC interface
            return BitExtractControl(0x1040, 0x00000020, 5);
         default:
            throw std::invalid_argument("Function GetAdcIfRst() not defined for this board version");
      };
   };
   void SetAdcIfRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the ADC interface
            return SetRegMask(0x1040, 0x00000020, 5, value);
         default:
            throw std::invalid_argument("Function SetAdcIfRst() not defined for this board version");
      };
   };
   unsigned int GetAdcIfRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the ADC interface
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x1040;
         default:
            throw std::invalid_argument("Function GetAdcIfRstLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_INT_VREF_ADJ
   unsigned int GetAdcIntVrefAdj()
   {
      switch(this->mVersion)
      {
         case 8:
            // Internal Vref Adjustment Digital Scheme (see datasheet)
            return BitExtractControl(0x1120, 0x00000007, 0);
         default:
            throw std::invalid_argument("Function GetAdcIntVrefAdj() not defined for this board version");
      };
   };
   void SetAdcIntVrefAdj(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Internal Vref Adjustment Digital Scheme (see datasheet)
            return SetRegMask(0x1120, 0x00000007, 0, value);
         default:
            throw std::invalid_argument("Function SetAdcIntVrefAdj() not defined for this board version");
      };
   };
   unsigned int GetAdcIntVrefAdjLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Internal Vref Adjustment Digital Scheme (see datasheet)
            if(BitMask) *BitMask = 0x00000007;
            if(BitOfs) *BitOfs = 0;
            return 0x1120;
         default:
            throw std::invalid_argument("Function GetAdcIntVrefAdjLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OA_OUT_DRIVE
   unsigned int GetAdcOaOutDrive()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Drive (0 = 1x, 1 = 2x)
            return BitExtractControl(0x1120, 0x00010000, 16);
         default:
            throw std::invalid_argument("Function GetAdcOaOutDrive() not defined for this board version");
      };
   };
   void SetAdcOaOutDrive(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Drive (0 = 1x, 1 = 2x)
            return SetRegMask(0x1120, 0x00010000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcOaOutDrive() not defined for this board version");
      };
   };
   unsigned int GetAdcOaOutDriveLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Drive (0 = 1x, 1 = 2x)
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x1120;
         default:
            throw std::invalid_argument("Function GetAdcOaOutDriveLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OA_OUT_DRV_TERM
   unsigned int GetAdcOaOutDrvTerm()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Driver Termination (see datasheet)
            return BitExtractControl(0x1120, 0x00300000, 20);
         default:
            throw std::invalid_argument("Function GetAdcOaOutDrvTerm() not defined for this board version");
      };
   };
   void SetAdcOaOutDrvTerm(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Driver Termination (see datasheet)
            return SetRegMask(0x1120, 0x00300000, 20, value);
         default:
            throw std::invalid_argument("Function SetAdcOaOutDrvTerm() not defined for this board version");
      };
   };
   unsigned int GetAdcOaOutDrvTermLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Driver Termination (see datasheet)
            if(BitMask) *BitMask = 0x00300000;
            if(BitOfs) *BitOfs = 20;
            return 0x1120;
         default:
            throw std::invalid_argument("Function GetAdcOaOutDrvTermLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ
   unsigned int GetAdcOffsAdj()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim (Local)
            return BitExtractControl(0x111C, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj() not defined for this board version");
      };
   };
   void SetAdcOffsAdj(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim (Local)
            return SetRegMask(0x111C, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdjLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim (Local)
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdjLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ_0_A
   unsigned int GetAdcOffsAdj0A()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return BitExtractControl(0x1130, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj0A() not defined for this board version");
      };
   };
   void SetAdcOffsAdj0A(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return SetRegMask(0x1130, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj0A() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdj0ALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1130;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj0ALoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ_0_B
   unsigned int GetAdcOffsAdj0B()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return BitExtractControl(0x1134, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj0B() not defined for this board version");
      };
   };
   void SetAdcOffsAdj0B(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return SetRegMask(0x1134, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj0B() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdj0BLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1134;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj0BLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ_0_C
   unsigned int GetAdcOffsAdj0C()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return BitExtractControl(0x1138, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj0C() not defined for this board version");
      };
   };
   void SetAdcOffsAdj0C(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return SetRegMask(0x1138, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj0C() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdj0CLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1138;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj0CLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ_0_D
   unsigned int GetAdcOffsAdj0D()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return BitExtractControl(0x113C, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj0D() not defined for this board version");
      };
   };
   void SetAdcOffsAdj0D(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return SetRegMask(0x113C, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj0D() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdj0DLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x113C;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj0DLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ_0_DCO
   unsigned int GetAdcOffsAdj0Dco()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return BitExtractControl(0x1150, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj0Dco() not defined for this board version");
      };
   };
   void SetAdcOffsAdj0Dco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return SetRegMask(0x1150, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj0Dco() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdj0DcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1150;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj0DcoLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ_0_E
   unsigned int GetAdcOffsAdj0E()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return BitExtractControl(0x1140, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj0E() not defined for this board version");
      };
   };
   void SetAdcOffsAdj0E(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return SetRegMask(0x1140, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj0E() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdj0ELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1140;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj0ELoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ_0_F
   unsigned int GetAdcOffsAdj0F()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return BitExtractControl(0x1144, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj0F() not defined for this board version");
      };
   };
   void SetAdcOffsAdj0F(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return SetRegMask(0x1144, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj0F() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdj0FLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1144;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj0FLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ_0_FCO
   unsigned int GetAdcOffsAdj0Fco()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return BitExtractControl(0x1154, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj0Fco() not defined for this board version");
      };
   };
   void SetAdcOffsAdj0Fco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return SetRegMask(0x1154, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj0Fco() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdj0FcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1154;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj0FcoLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ_0_G
   unsigned int GetAdcOffsAdj0G()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return BitExtractControl(0x1148, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj0G() not defined for this board version");
      };
   };
   void SetAdcOffsAdj0G(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return SetRegMask(0x1148, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj0G() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdj0GLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1148;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj0GLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ_0_H
   unsigned int GetAdcOffsAdj0H()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return BitExtractControl(0x114C, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj0H() not defined for this board version");
      };
   };
   void SetAdcOffsAdj0H(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return SetRegMask(0x114C, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj0H() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdj0HLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x114C;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj0HLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ_1_A
   unsigned int GetAdcOffsAdj1A()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return BitExtractControl(0x1158, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj1A() not defined for this board version");
      };
   };
   void SetAdcOffsAdj1A(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return SetRegMask(0x1158, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj1A() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdj1ALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1158;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj1ALoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ_1_B
   unsigned int GetAdcOffsAdj1B()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return BitExtractControl(0x115C, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj1B() not defined for this board version");
      };
   };
   void SetAdcOffsAdj1B(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return SetRegMask(0x115C, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj1B() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdj1BLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x115C;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj1BLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ_1_C
   unsigned int GetAdcOffsAdj1C()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return BitExtractControl(0x1160, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj1C() not defined for this board version");
      };
   };
   void SetAdcOffsAdj1C(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return SetRegMask(0x1160, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj1C() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdj1CLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1160;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj1CLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ_1_D
   unsigned int GetAdcOffsAdj1D()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return BitExtractControl(0x1164, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj1D() not defined for this board version");
      };
   };
   void SetAdcOffsAdj1D(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return SetRegMask(0x1164, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj1D() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdj1DLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1164;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj1DLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ_1_DCO
   unsigned int GetAdcOffsAdj1Dco()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return BitExtractControl(0x1178, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj1Dco() not defined for this board version");
      };
   };
   void SetAdcOffsAdj1Dco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return SetRegMask(0x1178, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj1Dco() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdj1DcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1178;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj1DcoLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ_1_E
   unsigned int GetAdcOffsAdj1E()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return BitExtractControl(0x1168, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj1E() not defined for this board version");
      };
   };
   void SetAdcOffsAdj1E(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return SetRegMask(0x1168, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj1E() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdj1ELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1168;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj1ELoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ_1_F
   unsigned int GetAdcOffsAdj1F()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return BitExtractControl(0x116C, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj1F() not defined for this board version");
      };
   };
   void SetAdcOffsAdj1F(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return SetRegMask(0x116C, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj1F() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdj1FLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x116C;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj1FLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ_1_FCO
   unsigned int GetAdcOffsAdj1Fco()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return BitExtractControl(0x117C, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj1Fco() not defined for this board version");
      };
   };
   void SetAdcOffsAdj1Fco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return SetRegMask(0x117C, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj1Fco() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdj1FcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x117C;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj1FcoLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ_1_G
   unsigned int GetAdcOffsAdj1G()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return BitExtractControl(0x1170, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj1G() not defined for this board version");
      };
   };
   void SetAdcOffsAdj1G(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return SetRegMask(0x1170, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj1G() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdj1GLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1170;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj1GLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OFFS_ADJ_1_H
   unsigned int GetAdcOffsAdj1H()
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return BitExtractControl(0x1174, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj1H() not defined for this board version");
      };
   };
   void SetAdcOffsAdj1H(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            return SetRegMask(0x1174, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOffsAdj1H() not defined for this board version");
      };
   };
   unsigned int GetAdcOffsAdj1HLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Device Offset Trim
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1174;
         default:
            throw std::invalid_argument("Function GetAdcOffsAdj1HLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_LVDS_MODE
   unsigned int GetAdcOmLvdsMode()
   {
      switch(this->mVersion)
      {
         case 8:
            // LVDS ANSI/IEEE Option (0 = ANSI, 1 = IEEE) (Global)
            return BitExtractControl(0x111C, 0x00000040, 6);
         default:
            throw std::invalid_argument("Function GetAdcOmLvdsMode() not defined for this board version");
      };
   };
   void SetAdcOmLvdsMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // LVDS ANSI/IEEE Option (0 = ANSI, 1 = IEEE) (Global)
            return SetRegMask(0x111C, 0x00000040, 6, value);
         default:
            throw std::invalid_argument("Function SetAdcOmLvdsMode() not defined for this board version");
      };
   };
   unsigned int GetAdcOmLvdsModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // LVDS ANSI/IEEE Option (0 = ANSI, 1 = IEEE) (Global)
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdcOmLvdsModeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_FORMAT
   unsigned int GetAdcOmOutFormat()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Format (0 = offset binary, 1 = twos complement) (Global)
            return BitExtractControl(0x111C, 0x00000001, 0);
         default:
            throw std::invalid_argument("Function GetAdcOmOutFormat() not defined for this board version");
      };
   };
   void SetAdcOmOutFormat(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Format (0 = offset binary, 1 = twos complement) (Global)
            return SetRegMask(0x111C, 0x00000001, 0, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutFormat() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutFormatLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Format (0 = offset binary, 1 = twos complement) (Global)
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdcOmOutFormatLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT
   unsigned int GetAdcOmOutInvert()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert (Local)
            return BitExtractControl(0x111C, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert (Local)
            return SetRegMask(0x111C, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvertLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert (Local)
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvertLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_0_A
   unsigned int GetAdcOmOutInvert0A()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return BitExtractControl(0x1130, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert0A() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert0A(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return SetRegMask(0x1130, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert0A() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvert0ALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1130;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert0ALoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_0_B
   unsigned int GetAdcOmOutInvert0B()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return BitExtractControl(0x1134, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert0B() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert0B(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return SetRegMask(0x1134, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert0B() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvert0BLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1134;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert0BLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_0_C
   unsigned int GetAdcOmOutInvert0C()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return BitExtractControl(0x1138, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert0C() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert0C(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return SetRegMask(0x1138, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert0C() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvert0CLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1138;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert0CLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_0_D
   unsigned int GetAdcOmOutInvert0D()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return BitExtractControl(0x113C, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert0D() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert0D(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return SetRegMask(0x113C, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert0D() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvert0DLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x113C;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert0DLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_0_DCO
   unsigned int GetAdcOmOutInvert0Dco()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return BitExtractControl(0x1150, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert0Dco() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert0Dco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return SetRegMask(0x1150, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert0Dco() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvert0DcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1150;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert0DcoLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_0_E
   unsigned int GetAdcOmOutInvert0E()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return BitExtractControl(0x1140, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert0E() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert0E(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return SetRegMask(0x1140, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert0E() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvert0ELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1140;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert0ELoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_0_F
   unsigned int GetAdcOmOutInvert0F()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return BitExtractControl(0x1144, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert0F() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert0F(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return SetRegMask(0x1144, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert0F() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvert0FLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1144;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert0FLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_0_FCO
   unsigned int GetAdcOmOutInvert0Fco()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return BitExtractControl(0x1154, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert0Fco() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert0Fco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return SetRegMask(0x1154, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert0Fco() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvert0FcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1154;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert0FcoLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_0_G
   unsigned int GetAdcOmOutInvert0G()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return BitExtractControl(0x1148, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert0G() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert0G(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return SetRegMask(0x1148, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert0G() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvert0GLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1148;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert0GLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_0_H
   unsigned int GetAdcOmOutInvert0H()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return BitExtractControl(0x114C, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert0H() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert0H(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return SetRegMask(0x114C, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert0H() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvert0HLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x114C;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert0HLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_1_A
   unsigned int GetAdcOmOutInvert1A()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return BitExtractControl(0x1158, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert1A() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert1A(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return SetRegMask(0x1158, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert1A() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvert1ALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1158;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert1ALoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_1_B
   unsigned int GetAdcOmOutInvert1B()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return BitExtractControl(0x115C, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert1B() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert1B(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return SetRegMask(0x115C, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert1B() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvert1BLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x115C;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert1BLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_1_C
   unsigned int GetAdcOmOutInvert1C()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return BitExtractControl(0x1160, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert1C() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert1C(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return SetRegMask(0x1160, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert1C() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvert1CLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1160;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert1CLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_1_D
   unsigned int GetAdcOmOutInvert1D()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return BitExtractControl(0x1164, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert1D() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert1D(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return SetRegMask(0x1164, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert1D() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvert1DLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1164;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert1DLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_1_DCO
   unsigned int GetAdcOmOutInvert1Dco()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return BitExtractControl(0x1178, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert1Dco() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert1Dco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return SetRegMask(0x1178, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert1Dco() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvert1DcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1178;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert1DcoLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_1_E
   unsigned int GetAdcOmOutInvert1E()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return BitExtractControl(0x1168, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert1E() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert1E(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return SetRegMask(0x1168, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert1E() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvert1ELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1168;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert1ELoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_1_F
   unsigned int GetAdcOmOutInvert1F()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return BitExtractControl(0x116C, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert1F() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert1F(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return SetRegMask(0x116C, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert1F() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvert1FLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x116C;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert1FLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_1_FCO
   unsigned int GetAdcOmOutInvert1Fco()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return BitExtractControl(0x117C, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert1Fco() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert1Fco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return SetRegMask(0x117C, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert1Fco() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvert1FcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x117C;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert1FcoLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_1_G
   unsigned int GetAdcOmOutInvert1G()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return BitExtractControl(0x1170, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert1G() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert1G(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return SetRegMask(0x1170, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert1G() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvert1GLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1170;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert1GLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_1_H
   unsigned int GetAdcOmOutInvert1H()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return BitExtractControl(0x1174, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert1H() not defined for this board version");
      };
   };
   void SetAdcOmOutInvert1H(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            return SetRegMask(0x1174, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetAdcOmOutInvert1H() not defined for this board version");
      };
   };
   unsigned int GetAdcOmOutInvert1HLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Invert
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1174;
         default:
            throw std::invalid_argument("Function GetAdcOmOutInvert1HLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OP_IN_CLK_PH_ADJ
   unsigned int GetAdcOpInClkPhAdj()
   {
      switch(this->mVersion)
      {
         case 8:
            // Input Clock Phase Adjust (see datasheet)
            return BitExtractControl(0x1120, 0x00007000, 12);
         default:
            throw std::invalid_argument("Function GetAdcOpInClkPhAdj() not defined for this board version");
      };
   };
   void SetAdcOpInClkPhAdj(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Input Clock Phase Adjust (see datasheet)
            return SetRegMask(0x1120, 0x00007000, 12, value);
         default:
            throw std::invalid_argument("Function SetAdcOpInClkPhAdj() not defined for this board version");
      };
   };
   unsigned int GetAdcOpInClkPhAdjLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Input Clock Phase Adjust (see datasheet)
            if(BitMask) *BitMask = 0x00007000;
            if(BitOfs) *BitOfs = 12;
            return 0x1120;
         default:
            throw std::invalid_argument("Function GetAdcOpInClkPhAdjLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_OP_OUT_CLK_PH_ADJ
   unsigned int GetAdcOpOutClkPhAdj()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Clock Phase Adjust (see datasheet)
            return BitExtractControl(0x1120, 0x00000F00, 8);
         default:
            throw std::invalid_argument("Function GetAdcOpOutClkPhAdj() not defined for this board version");
      };
   };
   void SetAdcOpOutClkPhAdj(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Clock Phase Adjust (see datasheet)
            return SetRegMask(0x1120, 0x00000F00, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcOpOutClkPhAdj() not defined for this board version");
      };
   };
   unsigned int GetAdcOpOutClkPhAdjLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Clock Phase Adjust (see datasheet)
            if(BitMask) *BitMask = 0x00000F00;
            if(BitOfs) *BitOfs = 8;
            return 0x1120;
         default:
            throw std::invalid_argument("Function GetAdcOpOutClkPhAdjLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_PM_EXT_PD
   unsigned int GetAdcPmExtPd()
   {
      switch(this->mVersion)
      {
         case 8:
            // Extrenal Power Down Pin Function (0 = full, 1 = standby)
            return BitExtractControl(0x1118, 0x20000000, 29);
         default:
            throw std::invalid_argument("Function GetAdcPmExtPd() not defined for this board version");
      };
   };
   void SetAdcPmExtPd(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Extrenal Power Down Pin Function (0 = full, 1 = standby)
            return SetRegMask(0x1118, 0x20000000, 29, value);
         default:
            throw std::invalid_argument("Function SetAdcPmExtPd() not defined for this board version");
      };
   };
   unsigned int GetAdcPmExtPdLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Extrenal Power Down Pin Function (0 = full, 1 = standby)
            if(BitMask) *BitMask = 0x20000000;
            if(BitOfs) *BitOfs = 29;
            return 0x1118;
         default:
            throw std::invalid_argument("Function GetAdcPmExtPdLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_PM_INT_PD_MODE
   unsigned int GetAdcPmIntPdMode()
   {
      switch(this->mVersion)
      {
         case 8:
            // Internal Power Down Mode (see datasheet)
            return BitExtractControl(0x1118, 0x03000000, 24);
         default:
            throw std::invalid_argument("Function GetAdcPmIntPdMode() not defined for this board version");
      };
   };
   void SetAdcPmIntPdMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Internal Power Down Mode (see datasheet)
            return SetRegMask(0x1118, 0x03000000, 24, value);
         default:
            throw std::invalid_argument("Function SetAdcPmIntPdMode() not defined for this board version");
      };
   };
   unsigned int GetAdcPmIntPdModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Internal Power Down Mode (see datasheet)
            if(BitMask) *BitMask = 0x03000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1118;
         default:
            throw std::invalid_argument("Function GetAdcPmIntPdModeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_RESOLUTION
   unsigned int GetAdcResolution()
   {
      switch(this->mVersion)
      {
         case 8:
            // Resolution (10 = 12bits, 11 = 10bits)
            return BitExtractControl(0x1128, 0x00000030, 4);
         default:
            throw std::invalid_argument("Function GetAdcResolution() not defined for this board version");
      };
   };
   void SetAdcResolution(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Resolution (10 = 12bits, 11 = 10bits)
            return SetRegMask(0x1128, 0x00000030, 4, value);
         default:
            throw std::invalid_argument("Function SetAdcResolution() not defined for this board version");
      };
   };
   unsigned int GetAdcResolutionLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Resolution (10 = 12bits, 11 = 10bits)
            if(BitMask) *BitMask = 0x00000030;
            if(BitOfs) *BitOfs = 4;
            return 0x1128;
         default:
            throw std::invalid_argument("Function GetAdcResolutionLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_RES_SR_OVR
   unsigned int GetAdcResSrOvr()
   {
      switch(this->mVersion)
      {
         case 8:
            // Resolution/Sample Rate Override Enable
            return BitExtractControl(0x1128, 0x00000040, 6);
         default:
            throw std::invalid_argument("Function GetAdcResSrOvr() not defined for this board version");
      };
   };
   void SetAdcResSrOvr(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Resolution/Sample Rate Override Enable
            return SetRegMask(0x1128, 0x00000040, 6, value);
         default:
            throw std::invalid_argument("Function SetAdcResSrOvr() not defined for this board version");
      };
   };
   unsigned int GetAdcResSrOvrLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Resolution/Sample Rate Override Enable
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x1128;
         default:
            throw std::invalid_argument("Function GetAdcResSrOvrLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_RST
   unsigned int GetAdcRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // ADC reset
            return BitExtractControl(0x1040, 0x00000040, 6);
         default:
            throw std::invalid_argument("Function GetAdcRst() not defined for this board version");
      };
   };
   void SetAdcRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // ADC reset
            return SetRegMask(0x1040, 0x00000040, 6, value);
         default:
            throw std::invalid_argument("Function SetAdcRst() not defined for this board version");
      };
   };
   unsigned int GetAdcRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // ADC reset
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x1040;
         default:
            throw std::invalid_argument("Function GetAdcRstLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_RST_MOD
   unsigned int GetAdcRstMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // ADC reset modified flag
            return BitExtractStatus(0x0138, 0x00000008, 3);
         case 9:
            // ADC reset modified flag
            return BitExtractStatus(0x0134, 0x00000008, 3);
         default:
            throw std::invalid_argument("Function GetAdcRstMod() not defined for this board version");
      };
   };
   unsigned int GetAdcRstModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // ADC reset modified flag
            if(BitMask) *BitMask = 0x00000008;
            if(BitOfs) *BitOfs = 3;
            return 0x0138;
         case 9:
            // ADC reset modified flag
            if(BitMask) *BitMask = 0x00000008;
            if(BitOfs) *BitOfs = 3;
            return 0x0134;
         default:
            throw std::invalid_argument("Function GetAdcRstModLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_SAMPLE_DIV
   unsigned int GetAdcSampleDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Only store every n-th sample to buffer
            return BitExtractControl(0x1038, 0x000000FF, 0);
         default:
            throw std::invalid_argument("Function GetAdcSampleDiv() not defined for this board version");
      };
   };
   void SetAdcSampleDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Only store every n-th sample to buffer
            return SetRegMask(0x1038, 0x000000FF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdcSampleDiv() not defined for this board version");
      };
   };
   unsigned int GetAdcSampleDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Only store every n-th sample to buffer
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x1038;
         default:
            throw std::invalid_argument("Function GetAdcSampleDivLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_SAMPLE_DIV_MOD
   unsigned int GetAdcSampleDivMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // ADC downsampling divider modified flags
            return BitExtractStatus(0x0144, 0x0000000F, 0);
         case 9:
            // ADC downsampling divider modified flags
            return BitExtractStatus(0x0140, 0x0000000F, 0);
         default:
            throw std::invalid_argument("Function GetAdcSampleDivMod() not defined for this board version");
      };
   };
   unsigned int GetAdcSampleDivModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // ADC downsampling divider modified flags
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0144;
         case 9:
            // ADC downsampling divider modified flags
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0140;
         default:
            throw std::invalid_argument("Function GetAdcSampleDivModLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_SAMPLE_FREQ
   unsigned int GetAdcSampleFreq()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // ADC Sampling Frequency in kHz
            return BitExtractStatus(0x003C, 0x00FFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdcSampleFreq() not defined for this board version");
      };
   };
   unsigned int GetAdcSampleFreqLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // ADC Sampling Frequency in kHz
            if(BitMask) *BitMask = 0x00FFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x003C;
         default:
            throw std::invalid_argument("Function GetAdcSampleFreqLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_SAMPLE_RATE
   unsigned int GetAdcSampleRate()
   {
      switch(this->mVersion)
      {
         case 8:
            // Sample Rate (see datasheet)
            return BitExtractControl(0x1128, 0x00000007, 0);
         default:
            throw std::invalid_argument("Function GetAdcSampleRate() not defined for this board version");
      };
   };
   void SetAdcSampleRate(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Sample Rate (see datasheet)
            return SetRegMask(0x1128, 0x00000007, 0, value);
         default:
            throw std::invalid_argument("Function SetAdcSampleRate() not defined for this board version");
      };
   };
   unsigned int GetAdcSampleRateLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Sample Rate (see datasheet)
            if(BitMask) *BitMask = 0x00000007;
            if(BitOfs) *BitOfs = 0;
            return 0x1128;
         default:
            throw std::invalid_argument("Function GetAdcSampleRateLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_SC_LVDS_OUT_LSB_FIRST
   unsigned int GetAdcScLvdsOutLsbFirst()
   {
      switch(this->mVersion)
      {
         case 8:
            // LVDS Output LSB First
            return BitExtractControl(0x1128, 0x00800000, 23);
         default:
            throw std::invalid_argument("Function GetAdcScLvdsOutLsbFirst() not defined for this board version");
      };
   };
   void SetAdcScLvdsOutLsbFirst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // LVDS Output LSB First
            return SetRegMask(0x1128, 0x00800000, 23, value);
         default:
            throw std::invalid_argument("Function SetAdcScLvdsOutLsbFirst() not defined for this board version");
      };
   };
   unsigned int GetAdcScLvdsOutLsbFirstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // LVDS Output LSB First
            if(BitMask) *BitMask = 0x00800000;
            if(BitOfs) *BitOfs = 23;
            return 0x1128;
         default:
            throw std::invalid_argument("Function GetAdcScLvdsOutLsbFirstLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_SC_OUT_NR_BITS
   unsigned int GetAdcScOutNrBits()
   {
      switch(this->mVersion)
      {
         case 8:
            // Serial Output Number of Bits (10 = 12bits, 11 = 10bits)
            return BitExtractControl(0x1128, 0x00030000, 16);
         default:
            throw std::invalid_argument("Function GetAdcScOutNrBits() not defined for this board version");
      };
   };
   void SetAdcScOutNrBits(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Serial Output Number of Bits (10 = 12bits, 11 = 10bits)
            return SetRegMask(0x1128, 0x00030000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcScOutNrBits() not defined for this board version");
      };
   };
   unsigned int GetAdcScOutNrBitsLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Serial Output Number of Bits (10 = 12bits, 11 = 10bits)
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x1128;
         default:
            throw std::invalid_argument("Function GetAdcScOutNrBitsLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_SC_OUT_RST
   unsigned int GetAdcScOutRst()
   {
      switch(this->mVersion)
      {
         case 8:
            // Serial Channel Status Output Reset
            return BitExtractControl(0x1128, 0x00000200, 9);
         default:
            throw std::invalid_argument("Function GetAdcScOutRst() not defined for this board version");
      };
   };
   void SetAdcScOutRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Serial Channel Status Output Reset
            return SetRegMask(0x1128, 0x00000200, 9, value);
         default:
            throw std::invalid_argument("Function SetAdcScOutRst() not defined for this board version");
      };
   };
   unsigned int GetAdcScOutRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Serial Channel Status Output Reset
            if(BitMask) *BitMask = 0x00000200;
            if(BitOfs) *BitOfs = 9;
            return 0x1128;
         default:
            throw std::invalid_argument("Function GetAdcScOutRstLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_SC_PWR_DN
   unsigned int GetAdcScPwrDn()
   {
      switch(this->mVersion)
      {
         case 8:
            // Serial Channel Status Power Down
            return BitExtractControl(0x1128, 0x00000100, 8);
         default:
            throw std::invalid_argument("Function GetAdcScPwrDn() not defined for this board version");
      };
   };
   void SetAdcScPwrDn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Serial Channel Status Power Down
            return SetRegMask(0x1128, 0x00000100, 8, value);
         default:
            throw std::invalid_argument("Function SetAdcScPwrDn() not defined for this board version");
      };
   };
   unsigned int GetAdcScPwrDnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Serial Channel Status Power Down
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1128;
         default:
            throw std::invalid_argument("Function GetAdcScPwrDnLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_SC_WORD_WISE_DDR
   unsigned int GetAdcScWordWiseDdr()
   {
      switch(this->mVersion)
      {
         case 8:
            // Word-Wise DDR 1-Lane (see datasheet)
            return BitExtractControl(0x1128, 0x00700000, 20);
         default:
            throw std::invalid_argument("Function GetAdcScWordWiseDdr() not defined for this board version");
      };
   };
   void SetAdcScWordWiseDdr(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Word-Wise DDR 1-Lane (see datasheet)
            return SetRegMask(0x1128, 0x00700000, 20, value);
         default:
            throw std::invalid_argument("Function SetAdcScWordWiseDdr() not defined for this board version");
      };
   };
   unsigned int GetAdcScWordWiseDdrLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Word-Wise DDR 1-Lane (see datasheet)
            if(BitMask) *BitMask = 0x00700000;
            if(BitOfs) *BitOfs = 20;
            return 0x1128;
         default:
            throw std::invalid_argument("Function GetAdcScWordWiseDdrLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_SYNC_NEXT_ONLY
   unsigned int GetAdcSyncNextOnly()
   {
      switch(this->mVersion)
      {
         case 8:
            // Sync Next Only
            return BitExtractControl(0x112C, 0x00000002, 1);
         default:
            throw std::invalid_argument("Function GetAdcSyncNextOnly() not defined for this board version");
      };
   };
   void SetAdcSyncNextOnly(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Sync Next Only
            return SetRegMask(0x112C, 0x00000002, 1, value);
         default:
            throw std::invalid_argument("Function SetAdcSyncNextOnly() not defined for this board version");
      };
   };
   unsigned int GetAdcSyncNextOnlyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Sync Next Only
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x112C;
         default:
            throw std::invalid_argument("Function GetAdcSyncNextOnlyLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT
   unsigned int GetAdcTmOut()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet) (Local)
            return BitExtractControl(0x111C, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut() not defined for this board version");
      };
   };
   void SetAdcTmOut(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet) (Local)
            return SetRegMask(0x111C, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOutLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet) (Local)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdcTmOutLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT_0_A
   unsigned int GetAdcTmOut0A()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return BitExtractControl(0x1130, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut0A() not defined for this board version");
      };
   };
   void SetAdcTmOut0A(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return SetRegMask(0x1130, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut0A() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOut0ALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1130;
         default:
            throw std::invalid_argument("Function GetAdcTmOut0ALoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT_0_B
   unsigned int GetAdcTmOut0B()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return BitExtractControl(0x1134, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut0B() not defined for this board version");
      };
   };
   void SetAdcTmOut0B(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return SetRegMask(0x1134, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut0B() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOut0BLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1134;
         default:
            throw std::invalid_argument("Function GetAdcTmOut0BLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT_0_C
   unsigned int GetAdcTmOut0C()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return BitExtractControl(0x1138, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut0C() not defined for this board version");
      };
   };
   void SetAdcTmOut0C(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return SetRegMask(0x1138, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut0C() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOut0CLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1138;
         default:
            throw std::invalid_argument("Function GetAdcTmOut0CLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT_0_D
   unsigned int GetAdcTmOut0D()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return BitExtractControl(0x113C, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut0D() not defined for this board version");
      };
   };
   void SetAdcTmOut0D(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return SetRegMask(0x113C, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut0D() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOut0DLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x113C;
         default:
            throw std::invalid_argument("Function GetAdcTmOut0DLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT_0_DCO
   unsigned int GetAdcTmOut0Dco()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return BitExtractControl(0x1150, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut0Dco() not defined for this board version");
      };
   };
   void SetAdcTmOut0Dco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return SetRegMask(0x1150, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut0Dco() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOut0DcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1150;
         default:
            throw std::invalid_argument("Function GetAdcTmOut0DcoLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT_0_E
   unsigned int GetAdcTmOut0E()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return BitExtractControl(0x1140, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut0E() not defined for this board version");
      };
   };
   void SetAdcTmOut0E(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return SetRegMask(0x1140, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut0E() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOut0ELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1140;
         default:
            throw std::invalid_argument("Function GetAdcTmOut0ELoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT_0_F
   unsigned int GetAdcTmOut0F()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return BitExtractControl(0x1144, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut0F() not defined for this board version");
      };
   };
   void SetAdcTmOut0F(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return SetRegMask(0x1144, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut0F() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOut0FLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1144;
         default:
            throw std::invalid_argument("Function GetAdcTmOut0FLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT_0_FCO
   unsigned int GetAdcTmOut0Fco()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return BitExtractControl(0x1154, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut0Fco() not defined for this board version");
      };
   };
   void SetAdcTmOut0Fco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return SetRegMask(0x1154, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut0Fco() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOut0FcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1154;
         default:
            throw std::invalid_argument("Function GetAdcTmOut0FcoLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT_0_G
   unsigned int GetAdcTmOut0G()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return BitExtractControl(0x1148, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut0G() not defined for this board version");
      };
   };
   void SetAdcTmOut0G(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return SetRegMask(0x1148, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut0G() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOut0GLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1148;
         default:
            throw std::invalid_argument("Function GetAdcTmOut0GLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT_0_H
   unsigned int GetAdcTmOut0H()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return BitExtractControl(0x114C, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut0H() not defined for this board version");
      };
   };
   void SetAdcTmOut0H(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return SetRegMask(0x114C, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut0H() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOut0HLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x114C;
         default:
            throw std::invalid_argument("Function GetAdcTmOut0HLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT_1_A
   unsigned int GetAdcTmOut1A()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return BitExtractControl(0x1158, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut1A() not defined for this board version");
      };
   };
   void SetAdcTmOut1A(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return SetRegMask(0x1158, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut1A() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOut1ALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1158;
         default:
            throw std::invalid_argument("Function GetAdcTmOut1ALoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT_1_B
   unsigned int GetAdcTmOut1B()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return BitExtractControl(0x115C, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut1B() not defined for this board version");
      };
   };
   void SetAdcTmOut1B(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return SetRegMask(0x115C, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut1B() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOut1BLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x115C;
         default:
            throw std::invalid_argument("Function GetAdcTmOut1BLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT_1_C
   unsigned int GetAdcTmOut1C()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return BitExtractControl(0x1160, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut1C() not defined for this board version");
      };
   };
   void SetAdcTmOut1C(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return SetRegMask(0x1160, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut1C() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOut1CLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1160;
         default:
            throw std::invalid_argument("Function GetAdcTmOut1CLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT_1_D
   unsigned int GetAdcTmOut1D()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return BitExtractControl(0x1164, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut1D() not defined for this board version");
      };
   };
   void SetAdcTmOut1D(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return SetRegMask(0x1164, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut1D() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOut1DLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1164;
         default:
            throw std::invalid_argument("Function GetAdcTmOut1DLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT_1_DCO
   unsigned int GetAdcTmOut1Dco()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return BitExtractControl(0x1178, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut1Dco() not defined for this board version");
      };
   };
   void SetAdcTmOut1Dco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return SetRegMask(0x1178, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut1Dco() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOut1DcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1178;
         default:
            throw std::invalid_argument("Function GetAdcTmOut1DcoLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT_1_E
   unsigned int GetAdcTmOut1E()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return BitExtractControl(0x1168, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut1E() not defined for this board version");
      };
   };
   void SetAdcTmOut1E(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return SetRegMask(0x1168, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut1E() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOut1ELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1168;
         default:
            throw std::invalid_argument("Function GetAdcTmOut1ELoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT_1_F
   unsigned int GetAdcTmOut1F()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return BitExtractControl(0x116C, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut1F() not defined for this board version");
      };
   };
   void SetAdcTmOut1F(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return SetRegMask(0x116C, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut1F() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOut1FLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x116C;
         default:
            throw std::invalid_argument("Function GetAdcTmOut1FLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT_1_FCO
   unsigned int GetAdcTmOut1Fco()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return BitExtractControl(0x117C, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut1Fco() not defined for this board version");
      };
   };
   void SetAdcTmOut1Fco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return SetRegMask(0x117C, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut1Fco() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOut1FcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x117C;
         default:
            throw std::invalid_argument("Function GetAdcTmOut1FcoLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT_1_G
   unsigned int GetAdcTmOut1G()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return BitExtractControl(0x1170, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut1G() not defined for this board version");
      };
   };
   void SetAdcTmOut1G(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return SetRegMask(0x1170, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut1G() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOut1GLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1170;
         default:
            throw std::invalid_argument("Function GetAdcTmOut1GLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_OUT_1_H
   unsigned int GetAdcTmOut1H()
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return BitExtractControl(0x1174, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcTmOut1H() not defined for this board version");
      };
   };
   void SetAdcTmOut1H(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            return SetRegMask(0x1174, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcTmOut1H() not defined for this board version");
      };
   };
   unsigned int GetAdcTmOut1HLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Output Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1174;
         default:
            throw std::invalid_argument("Function GetAdcTmOut1HLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_RST_PN_LONG_GEN
   unsigned int GetAdcTmRstPnLongGen()
   {
      switch(this->mVersion)
      {
         case 8:
            // Reset Pseudo Random Long Generator (Global)
            return BitExtractControl(0x111C, 0x00200000, 21);
         default:
            throw std::invalid_argument("Function GetAdcTmRstPnLongGen() not defined for this board version");
      };
   };
   void SetAdcTmRstPnLongGen(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Reset Pseudo Random Long Generator (Global)
            return SetRegMask(0x111C, 0x00200000, 21, value);
         default:
            throw std::invalid_argument("Function SetAdcTmRstPnLongGen() not defined for this board version");
      };
   };
   unsigned int GetAdcTmRstPnLongGenLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Reset Pseudo Random Long Generator (Global)
            if(BitMask) *BitMask = 0x00200000;
            if(BitOfs) *BitOfs = 21;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdcTmRstPnLongGenLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_RST_PN_SHORT_GEN
   unsigned int GetAdcTmRstPnShortGen()
   {
      switch(this->mVersion)
      {
         case 8:
            // Reset Pseudo Random Short Generator (Global)
            return BitExtractControl(0x111C, 0x00100000, 20);
         default:
            throw std::invalid_argument("Function GetAdcTmRstPnShortGen() not defined for this board version");
      };
   };
   void SetAdcTmRstPnShortGen(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Reset Pseudo Random Short Generator (Global)
            return SetRegMask(0x111C, 0x00100000, 20, value);
         default:
            throw std::invalid_argument("Function SetAdcTmRstPnShortGen() not defined for this board version");
      };
   };
   unsigned int GetAdcTmRstPnShortGenLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Reset Pseudo Random Short Generator (Global)
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdcTmRstPnShortGenLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE
   unsigned int GetAdcTmUsrInMode()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet) (Local)
            return BitExtractControl(0x111C, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet) (Local)
            return SetRegMask(0x111C, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet) (Local)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x111C;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInModeLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_0_A
   unsigned int GetAdcTmUsrInMode0A()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return BitExtractControl(0x1130, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode0A() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode0A(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return SetRegMask(0x1130, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode0A() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInMode0ALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1130;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode0ALoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_0_B
   unsigned int GetAdcTmUsrInMode0B()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return BitExtractControl(0x1134, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode0B() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode0B(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return SetRegMask(0x1134, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode0B() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInMode0BLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1134;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode0BLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_0_C
   unsigned int GetAdcTmUsrInMode0C()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return BitExtractControl(0x1138, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode0C() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode0C(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return SetRegMask(0x1138, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode0C() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInMode0CLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1138;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode0CLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_0_D
   unsigned int GetAdcTmUsrInMode0D()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return BitExtractControl(0x113C, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode0D() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode0D(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return SetRegMask(0x113C, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode0D() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInMode0DLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x113C;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode0DLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_0_DCO
   unsigned int GetAdcTmUsrInMode0Dco()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return BitExtractControl(0x1150, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode0Dco() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode0Dco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return SetRegMask(0x1150, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode0Dco() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInMode0DcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1150;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode0DcoLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_0_E
   unsigned int GetAdcTmUsrInMode0E()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return BitExtractControl(0x1140, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode0E() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode0E(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return SetRegMask(0x1140, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode0E() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInMode0ELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1140;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode0ELoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_0_F
   unsigned int GetAdcTmUsrInMode0F()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return BitExtractControl(0x1144, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode0F() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode0F(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return SetRegMask(0x1144, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode0F() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInMode0FLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1144;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode0FLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_0_FCO
   unsigned int GetAdcTmUsrInMode0Fco()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return BitExtractControl(0x1154, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode0Fco() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode0Fco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return SetRegMask(0x1154, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode0Fco() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInMode0FcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1154;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode0FcoLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_0_G
   unsigned int GetAdcTmUsrInMode0G()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return BitExtractControl(0x1148, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode0G() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode0G(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return SetRegMask(0x1148, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode0G() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInMode0GLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1148;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode0GLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_0_H
   unsigned int GetAdcTmUsrInMode0H()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return BitExtractControl(0x114C, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode0H() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode0H(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return SetRegMask(0x114C, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode0H() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInMode0HLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x114C;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode0HLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_1_A
   unsigned int GetAdcTmUsrInMode1A()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return BitExtractControl(0x1158, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode1A() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode1A(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return SetRegMask(0x1158, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode1A() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInMode1ALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1158;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode1ALoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_1_B
   unsigned int GetAdcTmUsrInMode1B()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return BitExtractControl(0x115C, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode1B() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode1B(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return SetRegMask(0x115C, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode1B() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInMode1BLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x115C;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode1BLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_1_C
   unsigned int GetAdcTmUsrInMode1C()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return BitExtractControl(0x1160, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode1C() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode1C(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return SetRegMask(0x1160, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode1C() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInMode1CLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1160;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode1CLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_1_D
   unsigned int GetAdcTmUsrInMode1D()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return BitExtractControl(0x1164, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode1D() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode1D(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return SetRegMask(0x1164, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode1D() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInMode1DLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1164;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode1DLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_1_DCO
   unsigned int GetAdcTmUsrInMode1Dco()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return BitExtractControl(0x1178, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode1Dco() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode1Dco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return SetRegMask(0x1178, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode1Dco() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInMode1DcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1178;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode1DcoLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_1_E
   unsigned int GetAdcTmUsrInMode1E()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return BitExtractControl(0x1168, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode1E() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode1E(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return SetRegMask(0x1168, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode1E() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInMode1ELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1168;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode1ELoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_1_F
   unsigned int GetAdcTmUsrInMode1F()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return BitExtractControl(0x116C, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode1F() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode1F(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return SetRegMask(0x116C, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode1F() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInMode1FLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x116C;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode1FLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_1_FCO
   unsigned int GetAdcTmUsrInMode1Fco()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return BitExtractControl(0x117C, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode1Fco() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode1Fco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return SetRegMask(0x117C, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode1Fco() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInMode1FcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x117C;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode1FcoLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_1_G
   unsigned int GetAdcTmUsrInMode1G()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return BitExtractControl(0x1170, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode1G() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode1G(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return SetRegMask(0x1170, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode1G() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInMode1GLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1170;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode1GLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_1_H
   unsigned int GetAdcTmUsrInMode1H()
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return BitExtractControl(0x1174, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode1H() not defined for this board version");
      };
   };
   void SetAdcTmUsrInMode1H(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            return SetRegMask(0x1174, 0x00C00000, 22, value);
         default:
            throw std::invalid_argument("Function SetAdcTmUsrInMode1H() not defined for this board version");
      };
   };
   unsigned int GetAdcTmUsrInMode1HLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // User Input Test Mode (see datasheet)
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1174;
         default:
            throw std::invalid_argument("Function GetAdcTmUsrInMode1HLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TX_INIT_OVERRIDE
   unsigned int GetAdcTxInitOverride()
   {
      switch(this->mVersion)
      {
         case 8:
            // Set Resolution/Sample Rate Override
            return BitExtractControl(0x1114, 0x00000001, 0);
         default:
            throw std::invalid_argument("Function GetAdcTxInitOverride() not defined for this board version");
      };
   };
   void SetAdcTxInitOverride(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Set Resolution/Sample Rate Override
            return SetRegMask(0x1114, 0x00000001, 0, value);
         default:
            throw std::invalid_argument("Function SetAdcTxInitOverride() not defined for this board version");
      };
   };
   unsigned int GetAdcTxInitOverrideLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Set Resolution/Sample Rate Override
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdcTxInitOverrideLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_TX_SAMPLES
   unsigned int GetAdcTxSamples()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Number of ADC samples to transmit per channel (must be an even value with range 2 to 2048)
            return BitExtractControl(0x102C, 0x00000FFF, 0);
         default:
            throw std::invalid_argument("Function GetAdcTxSamples() not defined for this board version");
      };
   };
   void SetAdcTxSamples(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Number of ADC samples to transmit per channel (must be an even value with range 2 to 2048)
            return SetRegMask(0x102C, 0x00000FFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdcTxSamples() not defined for this board version");
      };
   };
   unsigned int GetAdcTxSamplesLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Number of ADC samples to transmit per channel (must be an even value with range 2 to 2048)
            if(BitMask) *BitMask = 0x00000FFF;
            if(BitOfs) *BitOfs = 0;
            return 0x102C;
         default:
            throw std::invalid_argument("Function GetAdcTxSamplesLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_UIOC2_SDIO_PD
   unsigned int GetAdcUioc2SdioPd()
   {
      switch(this->mVersion)
      {
         case 8:
            // SDIO Pull-Down Disable
            return BitExtractControl(0x112C, 0x00010000, 16);
         default:
            throw std::invalid_argument("Function GetAdcUioc2SdioPd() not defined for this board version");
      };
   };
   void SetAdcUioc2SdioPd(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // SDIO Pull-Down Disable
            return SetRegMask(0x112C, 0x00010000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcUioc2SdioPd() not defined for this board version");
      };
   };
   unsigned int GetAdcUioc2SdioPdLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // SDIO Pull-Down Disable
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x112C;
         default:
            throw std::invalid_argument("Function GetAdcUioc2SdioPdLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_UIOC3_VCM_PWR_DN
   unsigned int GetAdcUioc3VcmPwrDn()
   {
      switch(this->mVersion)
      {
         case 8:
            // VCM Power Control
            return BitExtractControl(0x112C, 0x00000800, 11);
         default:
            throw std::invalid_argument("Function GetAdcUioc3VcmPwrDn() not defined for this board version");
      };
   };
   void SetAdcUioc3VcmPwrDn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // VCM Power Control
            return SetRegMask(0x112C, 0x00000800, 11, value);
         default:
            throw std::invalid_argument("Function SetAdcUioc3VcmPwrDn() not defined for this board version");
      };
   };
   unsigned int GetAdcUioc3VcmPwrDnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // VCM Power Control
            if(BitMask) *BitMask = 0x00000800;
            if(BitOfs) *BitOfs = 11;
            return 0x112C;
         default:
            throw std::invalid_argument("Function GetAdcUioc3VcmPwrDnLoc() not defined for this board version");
      };
   };

   // Bit(s) ADC_USR_PATT1
   unsigned int GetAdcUsrPatt1()
   {
      switch(this->mVersion)
      {
         case 8:
            // ADC User Pattern 1 (0x1A, 0x19) (Global)
            return BitExtractControl(0x1124, 0xFFFF0000, 16);
         default:
            throw std::invalid_argument("Function GetAdcUsrPatt1() not defined for this board version");
      };
   };
   void SetAdcUsrPatt1(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // ADC User Pattern 1 (0x1A, 0x19) (Global)
            return SetRegMask(0x1124, 0xFFFF0000, 16, value);
         default:
            throw std::invalid_argument("Function SetAdcUsrPatt1() not defined for this board version");
      };
   };
   unsigned int GetAdcUsrPatt1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // ADC User Pattern 1 (0x1A, 0x19) (Global)
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1124;
         default:
            throw std::invalid_argument("Function GetAdcUsrPatt1Loc() not defined for this board version");
      };
   };

   // Bit(s) ADC_USR_PATT2
   unsigned int GetAdcUsrPatt2()
   {
      switch(this->mVersion)
      {
         case 8:
            // ADC User Pattern 2 (0x1C, 0x1B) (Global)
            return BitExtractControl(0x1124, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdcUsrPatt2() not defined for this board version");
      };
   };
   void SetAdcUsrPatt2(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // ADC User Pattern 2 (0x1C, 0x1B) (Global)
            return SetRegMask(0x1124, 0x0000FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdcUsrPatt2() not defined for this board version");
      };
   };
   unsigned int GetAdcUsrPatt2Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // ADC User Pattern 2 (0x1C, 0x1B) (Global)
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1124;
         default:
            throw std::invalid_argument("Function GetAdcUsrPatt2Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_CFG_12
   unsigned int GetAdvTrgCfg12()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 12
            return BitExtractControl(0x1258, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger configuration register 12
            return BitExtractControl(0x11FC, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgCfg12() not defined for this board version");
      };
   };
   void SetAdvTrgCfg12(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 12
            return SetRegMask(0x1258, 0xFFFFFFFF, 0, value);
         case 9:
            // Advanced trigger configuration register 12
            return SetRegMask(0x11FC, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdvTrgCfg12() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgCfg12Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 12
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1258;
         case 9:
            // Advanced trigger configuration register 12
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11FC;
         default:
            throw std::invalid_argument("Function GetAdvTrgCfg12Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_CFG_13
   unsigned int GetAdvTrgCfg13()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 13
            return BitExtractControl(0x125C, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger configuration register 13
            return BitExtractControl(0x1200, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgCfg13() not defined for this board version");
      };
   };
   void SetAdvTrgCfg13(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 13
            return SetRegMask(0x125C, 0xFFFFFFFF, 0, value);
         case 9:
            // Advanced trigger configuration register 13
            return SetRegMask(0x1200, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdvTrgCfg13() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgCfg13Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 13
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x125C;
         case 9:
            // Advanced trigger configuration register 13
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1200;
         default:
            throw std::invalid_argument("Function GetAdvTrgCfg13Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_CFG_14
   unsigned int GetAdvTrgCfg14()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 14
            return BitExtractControl(0x1260, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger configuration register 14
            return BitExtractControl(0x1204, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgCfg14() not defined for this board version");
      };
   };
   void SetAdvTrgCfg14(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 14
            return SetRegMask(0x1260, 0xFFFFFFFF, 0, value);
         case 9:
            // Advanced trigger configuration register 14
            return SetRegMask(0x1204, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdvTrgCfg14() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgCfg14Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 14
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1260;
         case 9:
            // Advanced trigger configuration register 14
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1204;
         default:
            throw std::invalid_argument("Function GetAdvTrgCfg14Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_CFG_15
   unsigned int GetAdvTrgCfg15()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 15
            return BitExtractControl(0x1264, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger configuration register 15
            return BitExtractControl(0x1208, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgCfg15() not defined for this board version");
      };
   };
   void SetAdvTrgCfg15(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 15
            return SetRegMask(0x1264, 0xFFFFFFFF, 0, value);
         case 9:
            // Advanced trigger configuration register 15
            return SetRegMask(0x1208, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdvTrgCfg15() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgCfg15Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 15
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1264;
         case 9:
            // Advanced trigger configuration register 15
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1208;
         default:
            throw std::invalid_argument("Function GetAdvTrgCfg15Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_CFG_16
   unsigned int GetAdvTrgCfg16()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 16
            return BitExtractControl(0x1268, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger configuration register 16
            return BitExtractControl(0x120C, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgCfg16() not defined for this board version");
      };
   };
   void SetAdvTrgCfg16(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 16
            return SetRegMask(0x1268, 0xFFFFFFFF, 0, value);
         case 9:
            // Advanced trigger configuration register 16
            return SetRegMask(0x120C, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdvTrgCfg16() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgCfg16Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 16
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1268;
         case 9:
            // Advanced trigger configuration register 16
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x120C;
         default:
            throw std::invalid_argument("Function GetAdvTrgCfg16Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_CFG_17
   unsigned int GetAdvTrgCfg17()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 17
            return BitExtractControl(0x126C, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger configuration register 17
            return BitExtractControl(0x1210, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgCfg17() not defined for this board version");
      };
   };
   void SetAdvTrgCfg17(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 17
            return SetRegMask(0x126C, 0xFFFFFFFF, 0, value);
         case 9:
            // Advanced trigger configuration register 17
            return SetRegMask(0x1210, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdvTrgCfg17() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgCfg17Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 17
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x126C;
         case 9:
            // Advanced trigger configuration register 17
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1210;
         default:
            throw std::invalid_argument("Function GetAdvTrgCfg17Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_CFG_18
   unsigned int GetAdvTrgCfg18()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 18
            return BitExtractControl(0x1270, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger configuration register 18
            return BitExtractControl(0x1214, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgCfg18() not defined for this board version");
      };
   };
   void SetAdvTrgCfg18(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 18
            return SetRegMask(0x1270, 0xFFFFFFFF, 0, value);
         case 9:
            // Advanced trigger configuration register 18
            return SetRegMask(0x1214, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdvTrgCfg18() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgCfg18Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 18
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1270;
         case 9:
            // Advanced trigger configuration register 18
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1214;
         default:
            throw std::invalid_argument("Function GetAdvTrgCfg18Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_CFG_19
   unsigned int GetAdvTrgCfg19()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 19
            return BitExtractControl(0x1274, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger configuration register 19
            return BitExtractControl(0x1218, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgCfg19() not defined for this board version");
      };
   };
   void SetAdvTrgCfg19(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 19
            return SetRegMask(0x1274, 0xFFFFFFFF, 0, value);
         case 9:
            // Advanced trigger configuration register 19
            return SetRegMask(0x1218, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdvTrgCfg19() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgCfg19Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger configuration register 19
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1274;
         case 9:
            // Advanced trigger configuration register 19
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1218;
         default:
            throw std::invalid_argument("Function GetAdvTrgCfg19Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_CH_CAL0
   unsigned int GetAdvTrgChCal0()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger channel calibration register 0
            return BitExtractControl(0x122C, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger channel calibration register 0
            return BitExtractControl(0x11D0, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgChCal0() not defined for this board version");
      };
   };
   void SetAdvTrgChCal0(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger channel calibration register 0
            return SetRegMask(0x122C, 0xFFFFFFFF, 0, value);
         case 9:
            // Advanced trigger channel calibration register 0
            return SetRegMask(0x11D0, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdvTrgChCal0() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgChCal0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger channel calibration register 0
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x122C;
         case 9:
            // Advanced trigger channel calibration register 0
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11D0;
         default:
            throw std::invalid_argument("Function GetAdvTrgChCal0Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_CH_CAL1
   unsigned int GetAdvTrgChCal1()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger channel calibration register 1
            return BitExtractControl(0x1230, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger channel calibration register 1
            return BitExtractControl(0x11D4, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgChCal1() not defined for this board version");
      };
   };
   void SetAdvTrgChCal1(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger channel calibration register 1
            return SetRegMask(0x1230, 0xFFFFFFFF, 0, value);
         case 9:
            // Advanced trigger channel calibration register 1
            return SetRegMask(0x11D4, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdvTrgChCal1() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgChCal1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger channel calibration register 1
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1230;
         case 9:
            // Advanced trigger channel calibration register 1
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11D4;
         default:
            throw std::invalid_argument("Function GetAdvTrgChCal1Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_CH_CAL2
   unsigned int GetAdvTrgChCal2()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger channel calibration register 2
            return BitExtractControl(0x1234, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger channel calibration register 2
            return BitExtractControl(0x11D8, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgChCal2() not defined for this board version");
      };
   };
   void SetAdvTrgChCal2(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger channel calibration register 2
            return SetRegMask(0x1234, 0xFFFFFFFF, 0, value);
         case 9:
            // Advanced trigger channel calibration register 2
            return SetRegMask(0x11D8, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdvTrgChCal2() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgChCal2Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger channel calibration register 2
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1234;
         case 9:
            // Advanced trigger channel calibration register 2
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11D8;
         default:
            throw std::invalid_argument("Function GetAdvTrgChCal2Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_CH_CAL3
   unsigned int GetAdvTrgChCal3()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger channel calibration register 3
            return BitExtractControl(0x1238, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger channel calibration register 3
            return BitExtractControl(0x11DC, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgChCal3() not defined for this board version");
      };
   };
   void SetAdvTrgChCal3(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger channel calibration register 3
            return SetRegMask(0x1238, 0xFFFFFFFF, 0, value);
         case 9:
            // Advanced trigger channel calibration register 3
            return SetRegMask(0x11DC, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdvTrgChCal3() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgChCal3Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger channel calibration register 3
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1238;
         case 9:
            // Advanced trigger channel calibration register 3
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11DC;
         default:
            throw std::invalid_argument("Function GetAdvTrgChCal3Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_CTRL
   unsigned int GetAdvTrgCtrl()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger control register
            return BitExtractControl(0x1228, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger control register
            return BitExtractControl(0x11CC, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgCtrl() not defined for this board version");
      };
   };
   void SetAdvTrgCtrl(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger control register
            return SetRegMask(0x1228, 0xFFFFFFFF, 0, value);
         case 9:
            // Advanced trigger control register
            return SetRegMask(0x11CC, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdvTrgCtrl() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgCtrlLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger control register
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1228;
         case 9:
            // Advanced trigger control register
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11CC;
         default:
            throw std::invalid_argument("Function GetAdvTrgCtrlLoc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_PED_CFG
   unsigned int GetAdvTrgPedCfg()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger pedestal configuration register
            return BitExtractControl(0x123C, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger pedestal configuration register
            return BitExtractControl(0x11E0, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgPedCfg() not defined for this board version");
      };
   };
   void SetAdvTrgPedCfg(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger pedestal configuration register
            return SetRegMask(0x123C, 0xFFFFFFFF, 0, value);
         case 9:
            // Advanced trigger pedestal configuration register
            return SetRegMask(0x11E0, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdvTrgPedCfg() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgPedCfgLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger pedestal configuration register
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x123C;
         case 9:
            // Advanced trigger pedestal configuration register
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11E0;
         default:
            throw std::invalid_argument("Function GetAdvTrgPedCfgLoc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_STAT_1
   unsigned int GetAdvTrgStat1()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger status register 1
            return BitExtractStatus(0x0118, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger status register 1
            return BitExtractStatus(0x0114, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgStat1() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgStat1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger status register 1
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0118;
         case 9:
            // Advanced trigger status register 1
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0114;
         default:
            throw std::invalid_argument("Function GetAdvTrgStat1Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_STAT_2
   unsigned int GetAdvTrgStat2()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger status register 2
            return BitExtractStatus(0x011C, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger status register 2
            return BitExtractStatus(0x0118, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgStat2() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgStat2Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger status register 2
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x011C;
         case 9:
            // Advanced trigger status register 2
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0118;
         default:
            throw std::invalid_argument("Function GetAdvTrgStat2Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_STAT_3
   unsigned int GetAdvTrgStat3()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger status register 3
            return BitExtractStatus(0x0120, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger status register 3
            return BitExtractStatus(0x011C, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgStat3() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgStat3Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger status register 3
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0120;
         case 9:
            // Advanced trigger status register 3
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x011C;
         default:
            throw std::invalid_argument("Function GetAdvTrgStat3Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_STAT_4
   unsigned int GetAdvTrgStat4()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger status register 4
            return BitExtractStatus(0x0124, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger status register 4
            return BitExtractStatus(0x0120, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgStat4() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgStat4Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger status register 4
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0124;
         case 9:
            // Advanced trigger status register 4
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0120;
         default:
            throw std::invalid_argument("Function GetAdvTrgStat4Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_TDC_CH_MASK
   unsigned int GetAdvTrgTdcChMask()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger TDC channel mask
            return BitExtractControl(0x1254, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger TDC channel mask
            return BitExtractControl(0x11F8, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgTdcChMask() not defined for this board version");
      };
   };
   void SetAdvTrgTdcChMask(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger TDC channel mask
            return SetRegMask(0x1254, 0xFFFFFFFF, 0, value);
         case 9:
            // Advanced trigger TDC channel mask
            return SetRegMask(0x11F8, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdvTrgTdcChMask() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgTdcChMaskLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger TDC channel mask
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1254;
         case 9:
            // Advanced trigger TDC channel mask
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11F8;
         default:
            throw std::invalid_argument("Function GetAdvTrgTdcChMaskLoc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_THR0
   unsigned int GetAdvTrgThr0()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger threshold 0 register
            return BitExtractControl(0x1240, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger threshold 0 register
            return BitExtractControl(0x11E4, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgThr0() not defined for this board version");
      };
   };
   void SetAdvTrgThr0(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger threshold 0 register
            return SetRegMask(0x1240, 0xFFFFFFFF, 0, value);
         case 9:
            // Advanced trigger threshold 0 register
            return SetRegMask(0x11E4, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdvTrgThr0() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgThr0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger threshold 0 register
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1240;
         case 9:
            // Advanced trigger threshold 0 register
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11E4;
         default:
            throw std::invalid_argument("Function GetAdvTrgThr0Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_THR1
   unsigned int GetAdvTrgThr1()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger threshold 1 register
            return BitExtractControl(0x1244, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger threshold 1 register
            return BitExtractControl(0x11E8, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgThr1() not defined for this board version");
      };
   };
   void SetAdvTrgThr1(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger threshold 1 register
            return SetRegMask(0x1244, 0xFFFFFFFF, 0, value);
         case 9:
            // Advanced trigger threshold 1 register
            return SetRegMask(0x11E8, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdvTrgThr1() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgThr1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger threshold 1 register
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1244;
         case 9:
            // Advanced trigger threshold 1 register
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11E8;
         default:
            throw std::invalid_argument("Function GetAdvTrgThr1Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_THR2
   unsigned int GetAdvTrgThr2()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger threshold 2 register
            return BitExtractControl(0x1248, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger threshold 2 register
            return BitExtractControl(0x11EC, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgThr2() not defined for this board version");
      };
   };
   void SetAdvTrgThr2(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger threshold 2 register
            return SetRegMask(0x1248, 0xFFFFFFFF, 0, value);
         case 9:
            // Advanced trigger threshold 2 register
            return SetRegMask(0x11EC, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdvTrgThr2() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgThr2Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger threshold 2 register
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1248;
         case 9:
            // Advanced trigger threshold 2 register
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11EC;
         default:
            throw std::invalid_argument("Function GetAdvTrgThr2Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_TRIG_CELL
   unsigned int GetAdvTrgTrigCell()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger cell register
            return BitExtractStatus(0x0114, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger cell register
            return BitExtractStatus(0x0110, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgTrigCell() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgTrigCellLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger cell register
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0114;
         case 9:
            // Advanced trigger cell register
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0110;
         default:
            throw std::invalid_argument("Function GetAdvTrgTrigCellLoc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_TX_CHK_WORD0
   unsigned int GetAdvTrgTxChkWord0()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger transmition check word 0 register
            return BitExtractControl(0x124C, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger transmition check word 0 register
            return BitExtractControl(0x11F0, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgTxChkWord0() not defined for this board version");
      };
   };
   void SetAdvTrgTxChkWord0(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger transmition check word 0 register
            return SetRegMask(0x124C, 0xFFFFFFFF, 0, value);
         case 9:
            // Advanced trigger transmition check word 0 register
            return SetRegMask(0x11F0, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdvTrgTxChkWord0() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgTxChkWord0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger transmition check word 0 register
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x124C;
         case 9:
            // Advanced trigger transmition check word 0 register
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11F0;
         default:
            throw std::invalid_argument("Function GetAdvTrgTxChkWord0Loc() not defined for this board version");
      };
   };

   // Bit(s) ADV_TRG_TX_CHK_WORD1
   unsigned int GetAdvTrgTxChkWord1()
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger transmition check word 1 register
            return BitExtractControl(0x1250, 0xFFFFFFFF, 0);
         case 9:
            // Advanced trigger transmition check word 1 register
            return BitExtractControl(0x11F4, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAdvTrgTxChkWord1() not defined for this board version");
      };
   };
   void SetAdvTrgTxChkWord1(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger transmition check word 1 register
            return SetRegMask(0x1250, 0xFFFFFFFF, 0, value);
         case 9:
            // Advanced trigger transmition check word 1 register
            return SetRegMask(0x11F4, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAdvTrgTxChkWord1() not defined for this board version");
      };
   };
   unsigned int GetAdvTrgTxChkWord1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Advanced trigger transmition check word 1 register
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1250;
         case 9:
            // Advanced trigger transmition check word 1 register
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11F4;
         default:
            throw std::invalid_argument("Function GetAdvTrgTxChkWord1Loc() not defined for this board version");
      };
   };

   // Bit(s) APPLY_SETTINGS_ADC
   unsigned int GetApplySettingsAdc()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to ADC
            return BitExtractControl(0x1044, 0x00000002, 1);
         default:
            throw std::invalid_argument("Function GetApplySettingsAdc() not defined for this board version");
      };
   };
   void SetApplySettingsAdc(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to ADC
            return SetRegMask(0x1044, 0x00000002, 1, value);
         default:
            throw std::invalid_argument("Function SetApplySettingsAdc() not defined for this board version");
      };
   };
   unsigned int GetApplySettingsAdcLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to ADC
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x1044;
         default:
            throw std::invalid_argument("Function GetApplySettingsAdcLoc() not defined for this board version");
      };
   };

   // Bit(s) APPLY_SETTINGS_ADC_SAMPLE_DIV
   unsigned int GetApplySettingsAdcSampleDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to ADC sampling frequency (auto update)
            return BitExtractControl(0x1044, 0x00000100, 8);
         default:
            throw std::invalid_argument("Function GetApplySettingsAdcSampleDiv() not defined for this board version");
      };
   };
   void SetApplySettingsAdcSampleDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to ADC sampling frequency (auto update)
            return SetRegMask(0x1044, 0x00000100, 8, value);
         default:
            throw std::invalid_argument("Function SetApplySettingsAdcSampleDiv() not defined for this board version");
      };
   };
   unsigned int GetApplySettingsAdcSampleDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to ADC sampling frequency (auto update)
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1044;
         default:
            throw std::invalid_argument("Function GetApplySettingsAdcSampleDivLoc() not defined for this board version");
      };
   };

   // Bit(s) APPLY_SETTINGS_CTRL
   unsigned int GetApplySettingsCtrl()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank control register
            return BitExtractControl(0x1044, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetApplySettingsCtrl() not defined for this board version");
      };
   };
   void SetApplySettingsCtrl(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank control register
            return SetRegMask(0x1044, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetApplySettingsCtrl() not defined for this board version");
      };
   };
   unsigned int GetApplySettingsCtrlLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank control register
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1044;
         default:
            throw std::invalid_argument("Function GetApplySettingsCtrlLoc() not defined for this board version");
      };
   };

   // Bit(s) APPLY_SETTINGS_DAC
   unsigned int GetApplySettingsDac()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to DAC (auto update)
            return BitExtractControl(0x1044, 0x00000010, 4);
         default:
            throw std::invalid_argument("Function GetApplySettingsDac() not defined for this board version");
      };
   };
   void SetApplySettingsDac(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to DAC (auto update)
            return SetRegMask(0x1044, 0x00000010, 4, value);
         default:
            throw std::invalid_argument("Function SetApplySettingsDac() not defined for this board version");
      };
   };
   unsigned int GetApplySettingsDacLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to DAC (auto update)
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x1044;
         default:
            throw std::invalid_argument("Function GetApplySettingsDacLoc() not defined for this board version");
      };
   };

   // Bit(s) APPLY_SETTINGS_DRS
   unsigned int GetApplySettingsDrs()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to DRS chip (auto update)
            return BitExtractControl(0x1044, 0x00000020, 5);
         default:
            throw std::invalid_argument("Function GetApplySettingsDrs() not defined for this board version");
      };
   };
   void SetApplySettingsDrs(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to DRS chip (auto update)
            return SetRegMask(0x1044, 0x00000020, 5, value);
         default:
            throw std::invalid_argument("Function SetApplySettingsDrs() not defined for this board version");
      };
   };
   unsigned int GetApplySettingsDrsLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to DRS chip (auto update)
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x1044;
         default:
            throw std::invalid_argument("Function GetApplySettingsDrsLoc() not defined for this board version");
      };
   };

   // Bit(s) APPLY_SETTINGS_FRONTEND
   unsigned int GetApplySettingsFrontend()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to frontend (auto update)
            return BitExtractControl(0x1044, 0x00000008, 3);
         default:
            throw std::invalid_argument("Function GetApplySettingsFrontend() not defined for this board version");
      };
   };
   void SetApplySettingsFrontend(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to frontend (auto update)
            return SetRegMask(0x1044, 0x00000008, 3, value);
         default:
            throw std::invalid_argument("Function SetApplySettingsFrontend() not defined for this board version");
      };
   };
   unsigned int GetApplySettingsFrontendLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to frontend (auto update)
            if(BitMask) *BitMask = 0x00000008;
            if(BitOfs) *BitOfs = 3;
            return 0x1044;
         default:
            throw std::invalid_argument("Function GetApplySettingsFrontendLoc() not defined for this board version");
      };
   };

   // Bit(s) APPLY_SETTINGS_HV
   unsigned int GetApplySettingsHv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to HV (auto update)
            return BitExtractControl(0x1044, 0x00000040, 6);
         default:
            throw std::invalid_argument("Function GetApplySettingsHv() not defined for this board version");
      };
   };
   void SetApplySettingsHv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to HV (auto update)
            return SetRegMask(0x1044, 0x00000040, 6, value);
         default:
            throw std::invalid_argument("Function SetApplySettingsHv() not defined for this board version");
      };
   };
   unsigned int GetApplySettingsHvLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to HV (auto update)
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x1044;
         default:
            throw std::invalid_argument("Function GetApplySettingsHvLoc() not defined for this board version");
      };
   };

   // Bit(s) APPLY_SETTINGS_LMK
   unsigned int GetApplySettingsLmk()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from regsiter bank to LMK
            return BitExtractControl(0x1044, 0x00000001, 0);
         default:
            throw std::invalid_argument("Function GetApplySettingsLmk() not defined for this board version");
      };
   };
   void SetApplySettingsLmk(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from regsiter bank to LMK
            return SetRegMask(0x1044, 0x00000001, 0, value);
         default:
            throw std::invalid_argument("Function SetApplySettingsLmk() not defined for this board version");
      };
   };
   unsigned int GetApplySettingsLmkLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from regsiter bank to LMK
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x1044;
         default:
            throw std::invalid_argument("Function GetApplySettingsLmkLoc() not defined for this board version");
      };
   };

   // Bit(s) APPLY_SETTINGS_MAX_PLD_SIZE
   unsigned int GetApplySettingsMaxPldSize()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to max samples per packet (auto update)
            return BitExtractControl(0x1044, 0x00000080, 7);
         default:
            throw std::invalid_argument("Function GetApplySettingsMaxPldSize() not defined for this board version");
      };
   };
   void SetApplySettingsMaxPldSize(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to max samples per packet (auto update)
            return SetRegMask(0x1044, 0x00000080, 7, value);
         default:
            throw std::invalid_argument("Function SetApplySettingsMaxPldSize() not defined for this board version");
      };
   };
   unsigned int GetApplySettingsMaxPldSizeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Apply configuration from register bank to max samples per packet (auto update)
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x1044;
         default:
            throw std::invalid_argument("Function GetApplySettingsMaxPldSizeLoc() not defined for this board version");
      };
   };

   // Bit(s) AUTO_TRIGGER_PERIOD
   unsigned int GetAutoTriggerPeriod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Period of automatic trigger in ticks of the DAQ clock
            return BitExtractControl(0x1188, 0xFFFFFFFF, 0);
         case 9:
            // Period of automatic trigger in ticks of the DAQ clock
            return BitExtractControl(0x112C, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetAutoTriggerPeriod() not defined for this board version");
      };
   };
   void SetAutoTriggerPeriod(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Period of automatic trigger in ticks of the DAQ clock
            return SetRegMask(0x1188, 0xFFFFFFFF, 0, value);
         case 9:
            // Period of automatic trigger in ticks of the DAQ clock
            return SetRegMask(0x112C, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetAutoTriggerPeriod() not defined for this board version");
      };
   };
   unsigned int GetAutoTriggerPeriodLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Period of automatic trigger in ticks of the DAQ clock
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1188;
         case 9:
            // Period of automatic trigger in ticks of the DAQ clock
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x112C;
         default:
            throw std::invalid_argument("Function GetAutoTriggerPeriodLoc() not defined for this board version");
      };
   };

   // Bit(s) BACKPLANE_PLUGGED
   unsigned int GetBackplanePlugged()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Backplane is currently plugged (1) or unplugged (0)
            return BitExtractStatus(0x0028, 0x00000001, 0);
         default:
            throw std::invalid_argument("Function GetBackplanePlugged() not defined for this board version");
      };
   };
   unsigned int GetBackplanePluggedLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Backplane is currently plugged (1) or unplugged (0)
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x0028;
         default:
            throw std::invalid_argument("Function GetBackplanePluggedLoc() not defined for this board version");
      };
   };

   // Bit(s) BOARD_MAGIC
   unsigned int GetBoardMagic()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // 0xAC, Magic number for DRS board identification
            return BitExtractStatus(0x0000, 0xFF000000, 24);
         default:
            throw std::invalid_argument("Function GetBoardMagic() not defined for this board version");
      };
   };
   unsigned int GetBoardMagicLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // 0xAC, Magic number for DRS board identification
            if(BitMask) *BitMask = 0xFF000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0000;
         default:
            throw std::invalid_argument("Function GetBoardMagicLoc() not defined for this board version");
      };
   };

   // Bit(s) BOARD_REVISION
   unsigned int GetBoardRevision()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Board revision (A=0x00, C=0x02, D=0x03, E=0x04, F=0x05, G=0x06)
            return BitExtractStatus(0x0000, 0x000000FC, 2);
         default:
            throw std::invalid_argument("Function GetBoardRevision() not defined for this board version");
      };
   };
   unsigned int GetBoardRevisionLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Board revision (A=0x00, C=0x02, D=0x03, E=0x04, F=0x05, G=0x06)
            if(BitMask) *BitMask = 0x000000FC;
            if(BitOfs) *BitOfs = 2;
            return 0x0000;
         default:
            throw std::invalid_argument("Function GetBoardRevisionLoc() not defined for this board version");
      };
   };

   // Bit(s) BOARD_SEL
   unsigned int GetBoardSel()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Board select from backplane (inverted = high active)
            return BitExtractStatus(0x0028, 0x00000100, 8);
         default:
            throw std::invalid_argument("Function GetBoardSel() not defined for this board version");
      };
   };
   unsigned int GetBoardSelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Board select from backplane (inverted = high active)
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x0028;
         default:
            throw std::invalid_argument("Function GetBoardSelLoc() not defined for this board version");
      };
   };

   // Bit(s) BOARD_TYPE
   unsigned int GetBoardType()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // WaveDream Number (0x02 for WD2)
            return BitExtractStatus(0x0000, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetBoardType() not defined for this board version");
      };
   };
   unsigned int GetBoardTypeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // WaveDream Number (0x02 for WD2)
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x0000;
         default:
            throw std::invalid_argument("Function GetBoardTypeLoc() not defined for this board version");
      };
   };

   // Bit(s) BOARD_VARIANT
   unsigned int GetBoardVariant()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Version indicator pins reflecting the variant of the board (Y15,Y10)
            return BitExtractStatus(0x0000, 0x00000003, 0);
         default:
            throw std::invalid_argument("Function GetBoardVariant() not defined for this board version");
      };
   };
   unsigned int GetBoardVariantLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Version indicator pins reflecting the variant of the board (Y15,Y10)
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x0000;
         default:
            throw std::invalid_argument("Function GetBoardVariantLoc() not defined for this board version");
      };
   };

   // Bit(s) CALIB_BUFFER_EN
   unsigned int GetCalibBufferEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable buffers driving the calib. signal to the frontend MUX (BUFFER_CTRL)
            return BitExtractControl(0x1008, 0x00000002, 1);
         default:
            throw std::invalid_argument("Function GetCalibBufferEn() not defined for this board version");
      };
   };
   void SetCalibBufferEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable buffers driving the calib. signal to the frontend MUX (BUFFER_CTRL)
            return SetRegMask(0x1008, 0x00000002, 1, value);
         default:
            throw std::invalid_argument("Function SetCalibBufferEn() not defined for this board version");
      };
   };
   unsigned int GetCalibBufferEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable buffers driving the calib. signal to the frontend MUX (BUFFER_CTRL)
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x1008;
         default:
            throw std::invalid_argument("Function GetCalibBufferEnLoc() not defined for this board version");
      };
   };

   // Bit(s) CLK_SEL_AND_DRS_CLK_DIV_MOD
   unsigned int GetClkSelAndDrsClkDivMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAQ clock select and DRS clock divider modified flags
            return BitExtractStatus(0x0138, 0x00000004, 2);
         case 9:
            // DAQ clock select and DRS clock divider modified flags
            return BitExtractStatus(0x0134, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetClkSelAndDrsClkDivMod() not defined for this board version");
      };
   };
   unsigned int GetClkSelAndDrsClkDivModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAQ clock select and DRS clock divider modified flags
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x0138;
         case 9:
            // DAQ clock select and DRS clock divider modified flags
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x0134;
         default:
            throw std::invalid_argument("Function GetClkSelAndDrsClkDivModLoc() not defined for this board version");
      };
   };

   // Bit(s) COMP_CH_STAT
   unsigned int GetCompChStat()
   {
      switch(this->mVersion)
      {
         case 8:
            // Status of the comparator inputs
            return BitExtractStatus(0x00FC, 0x0000FFFF, 0);
         case 9:
            // Status of the comparator inputs
            return BitExtractStatus(0x00F8, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetCompChStat() not defined for this board version");
      };
   };
   unsigned int GetCompChStatLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Status of the comparator inputs
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00FC;
         case 9:
            // Status of the comparator inputs
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00F8;
         default:
            throw std::invalid_argument("Function GetCompChStatLoc() not defined for this board version");
      };
   };

   // Bit(s) COMP_POWER_EN
   unsigned int GetCompPowerEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Comparator power enable
            return BitExtractControl(0x1004, 0x00000200, 9);
         default:
            throw std::invalid_argument("Function GetCompPowerEn() not defined for this board version");
      };
   };
   void SetCompPowerEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Comparator power enable
            return SetRegMask(0x1004, 0x00000200, 9, value);
         default:
            throw std::invalid_argument("Function SetCompPowerEn() not defined for this board version");
      };
   };
   unsigned int GetCompPowerEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Comparator power enable
            if(BitMask) *BitMask = 0x00000200;
            if(BitOfs) *BitOfs = 9;
            return 0x1004;
         default:
            throw std::invalid_argument("Function GetCompPowerEnLoc() not defined for this board version");
      };
   };

   // Bit(s) COM_PLD_SIZE
   unsigned int GetComPldSize()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Maximum number of UDP payload bytes to transmit (must be a multiple of 6 with range 6 to 8892)
            return BitExtractControl(0x1018, 0x0003FFFF, 0);
         default:
            throw std::invalid_argument("Function GetComPldSize() not defined for this board version");
      };
   };
   void SetComPldSize(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Maximum number of UDP payload bytes to transmit (must be a multiple of 6 with range 6 to 8892)
            return SetRegMask(0x1018, 0x0003FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetComPldSize() not defined for this board version");
      };
   };
   unsigned int GetComPldSizeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Maximum number of UDP payload bytes to transmit (must be a multiple of 6 with range 6 to 8892)
            if(BitMask) *BitMask = 0x0003FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1018;
         default:
            throw std::invalid_argument("Function GetComPldSizeLoc() not defined for this board version");
      };
   };

   // Bit(s) COM_PLD_SIZE_MOD
   unsigned int GetComPldSizeMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Maximum packet payload size modified flag
            return BitExtractStatus(0x0140, 0x0000000F, 0);
         case 9:
            // Maximum packet payload size modified flag
            return BitExtractStatus(0x013C, 0x0000000F, 0);
         default:
            throw std::invalid_argument("Function GetComPldSizeMod() not defined for this board version");
      };
   };
   unsigned int GetComPldSizeModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Maximum packet payload size modified flag
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0140;
         case 9:
            // Maximum packet payload size modified flag
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x013C;
         default:
            throw std::invalid_argument("Function GetComPldSizeModLoc() not defined for this board version");
      };
   };

   // Bit(s) CRATE_ID
   unsigned int GetCrateId()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // ID of the crate where the current board is plugged in
            return BitExtractControl(0x1000, 0x00FF0000, 16);
         default:
            throw std::invalid_argument("Function GetCrateId() not defined for this board version");
      };
   };
   void SetCrateId(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // ID of the crate where the current board is plugged in
            return SetRegMask(0x1000, 0x00FF0000, 16, value);
         default:
            throw std::invalid_argument("Function SetCrateId() not defined for this board version");
      };
   };
   unsigned int GetCrateIdLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // ID of the crate where the current board is plugged in
            if(BitMask) *BitMask = 0x00FF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1000;
         default:
            throw std::invalid_argument("Function GetCrateIdLoc() not defined for this board version");
      };
   };

   // Bit(s) CRC32_REG_BANK
   unsigned int GetCrc32RegBank()
   {
      switch(this->mVersion)
      {
         case 8:
            // Keep at the end of the register bank
            return BitExtractControl(0x1284, 0xFFFFFFFF, 0);
         case 9:
            // Keep at the end of the register bank
            return BitExtractControl(0x1228, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetCrc32RegBank() not defined for this board version");
      };
   };
   void SetCrc32RegBank(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Keep at the end of the register bank
            return SetRegMask(0x1284, 0xFFFFFFFF, 0, value);
         case 9:
            // Keep at the end of the register bank
            return SetRegMask(0x1228, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetCrc32RegBank() not defined for this board version");
      };
   };
   unsigned int GetCrc32RegBankLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Keep at the end of the register bank
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1284;
         case 9:
            // Keep at the end of the register bank
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1228;
         default:
            throw std::invalid_argument("Function GetCrc32RegBankLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC0_A_MOD
   unsigned int GetDac0AMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel a modified flags
            return BitExtractStatus(0x0148, 0xC0000000, 30);
         case 9:
            // DAC channel a modified flags
            return BitExtractStatus(0x0144, 0xC0000000, 30);
         default:
            throw std::invalid_argument("Function GetDac0AMod() not defined for this board version");
      };
   };
   unsigned int GetDac0AModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel a modified flags
            if(BitMask) *BitMask = 0xC0000000;
            if(BitOfs) *BitOfs = 30;
            return 0x0148;
         case 9:
            // DAC channel a modified flags
            if(BitMask) *BitMask = 0xC0000000;
            if(BitOfs) *BitOfs = 30;
            return 0x0144;
         default:
            throw std::invalid_argument("Function GetDac0AModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC0_B_MOD
   unsigned int GetDac0BMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel b modified flags
            return BitExtractStatus(0x0148, 0x30000000, 28);
         case 9:
            // DAC channel b modified flags
            return BitExtractStatus(0x0144, 0x30000000, 28);
         default:
            throw std::invalid_argument("Function GetDac0BMod() not defined for this board version");
      };
   };
   unsigned int GetDac0BModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel b modified flags
            if(BitMask) *BitMask = 0x30000000;
            if(BitOfs) *BitOfs = 28;
            return 0x0148;
         case 9:
            // DAC channel b modified flags
            if(BitMask) *BitMask = 0x30000000;
            if(BitOfs) *BitOfs = 28;
            return 0x0144;
         default:
            throw std::invalid_argument("Function GetDac0BModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC0_CH_A
   unsigned int GetDac0ChA()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel A (ROFS) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x1048, 0xFFFF0000, 16);
         default:
            throw std::invalid_argument("Function GetDac0ChA() not defined for this board version");
      };
   };
   void SetDac0ChA(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel A (ROFS) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x1048, 0xFFFF0000, 16, value);
         default:
            throw std::invalid_argument("Function SetDac0ChA() not defined for this board version");
      };
   };
   unsigned int GetDac0ChALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel A (ROFS) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1048;
         default:
            throw std::invalid_argument("Function GetDac0ChALoc() not defined for this board version");
      };
   };

   // Bit(s) DAC0_CH_B
   unsigned int GetDac0ChB()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel B (OFS) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (+/- 0.625V)
            return BitExtractControl(0x1048, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetDac0ChB() not defined for this board version");
      };
   };
   void SetDac0ChB(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel B (OFS) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (+/- 0.625V)
            return SetRegMask(0x1048, 0x0000FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetDac0ChB() not defined for this board version");
      };
   };
   unsigned int GetDac0ChBLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel B (OFS) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (+/- 0.625V)
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1048;
         default:
            throw std::invalid_argument("Function GetDac0ChBLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC0_CH_C
   unsigned int GetDac0ChC()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel C (CAL_DC) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (+/- 0.625V)
            return BitExtractControl(0x104C, 0xFFFF0000, 16);
         default:
            throw std::invalid_argument("Function GetDac0ChC() not defined for this board version");
      };
   };
   void SetDac0ChC(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel C (CAL_DC) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (+/- 0.625V)
            return SetRegMask(0x104C, 0xFFFF0000, 16, value);
         default:
            throw std::invalid_argument("Function SetDac0ChC() not defined for this board version");
      };
   };
   unsigned int GetDac0ChCLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel C (CAL_DC) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (+/- 0.625V)
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x104C;
         default:
            throw std::invalid_argument("Function GetDac0ChCLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC0_CH_D
   unsigned int GetDac0ChD()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel D (PULSE_AMP) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..1V)
            return BitExtractControl(0x104C, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetDac0ChD() not defined for this board version");
      };
   };
   void SetDac0ChD(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel D (PULSE_AMP) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..1V)
            return SetRegMask(0x104C, 0x0000FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetDac0ChD() not defined for this board version");
      };
   };
   unsigned int GetDac0ChDLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel D (PULSE_AMP) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..1V)
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x104C;
         default:
            throw std::invalid_argument("Function GetDac0ChDLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC0_CH_E
   unsigned int GetDac0ChE()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel E (PZC_LEVEL) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (+/- 2.5V)
            return BitExtractControl(0x1050, 0xFFFF0000, 16);
         default:
            throw std::invalid_argument("Function GetDac0ChE() not defined for this board version");
      };
   };
   void SetDac0ChE(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel E (PZC_LEVEL) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (+/- 2.5V)
            return SetRegMask(0x1050, 0xFFFF0000, 16, value);
         default:
            throw std::invalid_argument("Function SetDac0ChE() not defined for this board version");
      };
   };
   unsigned int GetDac0ChELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel E (PZC_LEVEL) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (+/- 2.5V)
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1050;
         default:
            throw std::invalid_argument("Function GetDac0ChELoc() not defined for this board version");
      };
   };

   // Bit(s) DAC0_CH_F
   unsigned int GetDac0ChF()
   {
      switch(this->mVersion)
      {
         case 8:
            // Set DAC0 channel F (RESERVED) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x1050, 0x0000FFFF, 0);
         case 9:
            // Set DAC0 channel F (DAC_REF_A) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x1050, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetDac0ChF() not defined for this board version");
      };
   };
   void SetDac0ChF(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Set DAC0 channel F (RESERVED) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x1050, 0x0000FFFF, 0, value);
         case 9:
            // Set DAC0 channel F (DAC_REF_A) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x1050, 0x0000FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetDac0ChF() not defined for this board version");
      };
   };
   unsigned int GetDac0ChFLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Set DAC0 channel F (RESERVED) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1050;
         case 9:
            // Set DAC0 channel F (DAC_REF_A) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1050;
         default:
            throw std::invalid_argument("Function GetDac0ChFLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC0_CH_G
   unsigned int GetDac0ChG()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel G (RESERVED) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x1054, 0xFFFF0000, 16);
         default:
            throw std::invalid_argument("Function GetDac0ChG() not defined for this board version");
      };
   };
   void SetDac0ChG(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel G (RESERVED) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x1054, 0xFFFF0000, 16, value);
         default:
            throw std::invalid_argument("Function SetDac0ChG() not defined for this board version");
      };
   };
   unsigned int GetDac0ChGLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel G (RESERVED) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1054;
         default:
            throw std::invalid_argument("Function GetDac0ChGLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC0_CH_H
   unsigned int GetDac0ChH()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel H (BIAS) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x1054, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetDac0ChH() not defined for this board version");
      };
   };
   void SetDac0ChH(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel H (BIAS) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x1054, 0x0000FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetDac0ChH() not defined for this board version");
      };
   };
   unsigned int GetDac0ChHLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC0 channel H (BIAS) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1054;
         default:
            throw std::invalid_argument("Function GetDac0ChHLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC0_C_MOD
   unsigned int GetDac0CMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel c modified flags
            return BitExtractStatus(0x0148, 0x0C000000, 26);
         case 9:
            // DAC channel c modified flags
            return BitExtractStatus(0x0144, 0x0C000000, 26);
         default:
            throw std::invalid_argument("Function GetDac0CMod() not defined for this board version");
      };
   };
   unsigned int GetDac0CModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel c modified flags
            if(BitMask) *BitMask = 0x0C000000;
            if(BitOfs) *BitOfs = 26;
            return 0x0148;
         case 9:
            // DAC channel c modified flags
            if(BitMask) *BitMask = 0x0C000000;
            if(BitOfs) *BitOfs = 26;
            return 0x0144;
         default:
            throw std::invalid_argument("Function GetDac0CModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC0_D_MOD
   unsigned int GetDac0DMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel d modified flags
            return BitExtractStatus(0x0148, 0x03000000, 24);
         case 9:
            // DAC channel d modified flags
            return BitExtractStatus(0x0144, 0x03000000, 24);
         default:
            throw std::invalid_argument("Function GetDac0DMod() not defined for this board version");
      };
   };
   unsigned int GetDac0DModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel d modified flags
            if(BitMask) *BitMask = 0x03000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0148;
         case 9:
            // DAC channel d modified flags
            if(BitMask) *BitMask = 0x03000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0144;
         default:
            throw std::invalid_argument("Function GetDac0DModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC0_E_MOD
   unsigned int GetDac0EMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel e modified flags
            return BitExtractStatus(0x0148, 0x00C00000, 22);
         case 9:
            // DAC channel e modified flags
            return BitExtractStatus(0x0144, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetDac0EMod() not defined for this board version");
      };
   };
   unsigned int GetDac0EModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel e modified flags
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x0148;
         case 9:
            // DAC channel e modified flags
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x0144;
         default:
            throw std::invalid_argument("Function GetDac0EModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC0_F_MOD
   unsigned int GetDac0FMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel f modified flags
            return BitExtractStatus(0x0148, 0x00300000, 20);
         case 9:
            // DAC channel f modified flags
            return BitExtractStatus(0x0144, 0x00300000, 20);
         default:
            throw std::invalid_argument("Function GetDac0FMod() not defined for this board version");
      };
   };
   unsigned int GetDac0FModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel f modified flags
            if(BitMask) *BitMask = 0x00300000;
            if(BitOfs) *BitOfs = 20;
            return 0x0148;
         case 9:
            // DAC channel f modified flags
            if(BitMask) *BitMask = 0x00300000;
            if(BitOfs) *BitOfs = 20;
            return 0x0144;
         default:
            throw std::invalid_argument("Function GetDac0FModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC0_G_MOD
   unsigned int GetDac0GMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel g modified flags
            return BitExtractStatus(0x0148, 0x000C0000, 18);
         case 9:
            // DAC channel g modified flags
            return BitExtractStatus(0x0144, 0x000C0000, 18);
         default:
            throw std::invalid_argument("Function GetDac0GMod() not defined for this board version");
      };
   };
   unsigned int GetDac0GModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel g modified flags
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x0148;
         case 9:
            // DAC channel g modified flags
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x0144;
         default:
            throw std::invalid_argument("Function GetDac0GModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC0_H_MOD
   unsigned int GetDac0HMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel h modified flags
            return BitExtractStatus(0x0148, 0x00030000, 16);
         case 9:
            // DAC channel h modified flags
            return BitExtractStatus(0x0144, 0x00030000, 16);
         default:
            throw std::invalid_argument("Function GetDac0HMod() not defined for this board version");
      };
   };
   unsigned int GetDac0HModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel h modified flags
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x0148;
         case 9:
            // DAC channel h modified flags
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x0144;
         default:
            throw std::invalid_argument("Function GetDac0HModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC1_A_MOD
   unsigned int GetDac1AMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel a modified flags
            return BitExtractStatus(0x0148, 0x0000C000, 14);
         case 9:
            // DAC channel a modified flags
            return BitExtractStatus(0x0144, 0x0000C000, 14);
         default:
            throw std::invalid_argument("Function GetDac1AMod() not defined for this board version");
      };
   };
   unsigned int GetDac1AModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel a modified flags
            if(BitMask) *BitMask = 0x0000C000;
            if(BitOfs) *BitOfs = 14;
            return 0x0148;
         case 9:
            // DAC channel a modified flags
            if(BitMask) *BitMask = 0x0000C000;
            if(BitOfs) *BitOfs = 14;
            return 0x0144;
         default:
            throw std::invalid_argument("Function GetDac1AModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC1_B_MOD
   unsigned int GetDac1BMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel b modified flags
            return BitExtractStatus(0x0148, 0x00003000, 12);
         case 9:
            // DAC channel b modified flags
            return BitExtractStatus(0x0144, 0x00003000, 12);
         default:
            throw std::invalid_argument("Function GetDac1BMod() not defined for this board version");
      };
   };
   unsigned int GetDac1BModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel b modified flags
            if(BitMask) *BitMask = 0x00003000;
            if(BitOfs) *BitOfs = 12;
            return 0x0148;
         case 9:
            // DAC channel b modified flags
            if(BitMask) *BitMask = 0x00003000;
            if(BitOfs) *BitOfs = 12;
            return 0x0144;
         default:
            throw std::invalid_argument("Function GetDac1BModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC1_CH_A
   unsigned int GetDac1ChA()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel A (TLEVEL_0) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x1058, 0xFFFF0000, 16);
         default:
            throw std::invalid_argument("Function GetDac1ChA() not defined for this board version");
      };
   };
   void SetDac1ChA(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel A (TLEVEL_0) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x1058, 0xFFFF0000, 16, value);
         default:
            throw std::invalid_argument("Function SetDac1ChA() not defined for this board version");
      };
   };
   unsigned int GetDac1ChALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel A (TLEVEL_0) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1058;
         default:
            throw std::invalid_argument("Function GetDac1ChALoc() not defined for this board version");
      };
   };

   // Bit(s) DAC1_CH_B
   unsigned int GetDac1ChB()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel B (TLEVEL_1) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x1058, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetDac1ChB() not defined for this board version");
      };
   };
   void SetDac1ChB(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel B (TLEVEL_1) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x1058, 0x0000FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetDac1ChB() not defined for this board version");
      };
   };
   unsigned int GetDac1ChBLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel B (TLEVEL_1) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1058;
         default:
            throw std::invalid_argument("Function GetDac1ChBLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC1_CH_C
   unsigned int GetDac1ChC()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel C (TLEVEL_2) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x105C, 0xFFFF0000, 16);
         default:
            throw std::invalid_argument("Function GetDac1ChC() not defined for this board version");
      };
   };
   void SetDac1ChC(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel C (TLEVEL_2) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x105C, 0xFFFF0000, 16, value);
         default:
            throw std::invalid_argument("Function SetDac1ChC() not defined for this board version");
      };
   };
   unsigned int GetDac1ChCLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel C (TLEVEL_2) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x105C;
         default:
            throw std::invalid_argument("Function GetDac1ChCLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC1_CH_D
   unsigned int GetDac1ChD()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel D (TLEVEL_3) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x105C, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetDac1ChD() not defined for this board version");
      };
   };
   void SetDac1ChD(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel D (TLEVEL_3) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x105C, 0x0000FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetDac1ChD() not defined for this board version");
      };
   };
   unsigned int GetDac1ChDLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel D (TLEVEL_3) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x105C;
         default:
            throw std::invalid_argument("Function GetDac1ChDLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC1_CH_E
   unsigned int GetDac1ChE()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel E (TLEVEL_4) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x1060, 0xFFFF0000, 16);
         default:
            throw std::invalid_argument("Function GetDac1ChE() not defined for this board version");
      };
   };
   void SetDac1ChE(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel E (TLEVEL_4) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x1060, 0xFFFF0000, 16, value);
         default:
            throw std::invalid_argument("Function SetDac1ChE() not defined for this board version");
      };
   };
   unsigned int GetDac1ChELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel E (TLEVEL_4) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1060;
         default:
            throw std::invalid_argument("Function GetDac1ChELoc() not defined for this board version");
      };
   };

   // Bit(s) DAC1_CH_F
   unsigned int GetDac1ChF()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel F (TLEVEL_5) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x1060, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetDac1ChF() not defined for this board version");
      };
   };
   void SetDac1ChF(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel F (TLEVEL_5) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x1060, 0x0000FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetDac1ChF() not defined for this board version");
      };
   };
   unsigned int GetDac1ChFLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel F (TLEVEL_5) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1060;
         default:
            throw std::invalid_argument("Function GetDac1ChFLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC1_CH_G
   unsigned int GetDac1ChG()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel G (TLEVEL_6) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x1064, 0xFFFF0000, 16);
         default:
            throw std::invalid_argument("Function GetDac1ChG() not defined for this board version");
      };
   };
   void SetDac1ChG(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel G (TLEVEL_6) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x1064, 0xFFFF0000, 16, value);
         default:
            throw std::invalid_argument("Function SetDac1ChG() not defined for this board version");
      };
   };
   unsigned int GetDac1ChGLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel G (TLEVEL_6) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1064;
         default:
            throw std::invalid_argument("Function GetDac1ChGLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC1_CH_H
   unsigned int GetDac1ChH()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel H (TLEVEL_7) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x1064, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetDac1ChH() not defined for this board version");
      };
   };
   void SetDac1ChH(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel H (TLEVEL_7) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x1064, 0x0000FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetDac1ChH() not defined for this board version");
      };
   };
   unsigned int GetDac1ChHLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC1 channel H (TLEVEL_7) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1064;
         default:
            throw std::invalid_argument("Function GetDac1ChHLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC1_C_MOD
   unsigned int GetDac1CMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel c modified flags
            return BitExtractStatus(0x0148, 0x00000C00, 10);
         case 9:
            // DAC channel c modified flags
            return BitExtractStatus(0x0144, 0x00000C00, 10);
         default:
            throw std::invalid_argument("Function GetDac1CMod() not defined for this board version");
      };
   };
   unsigned int GetDac1CModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel c modified flags
            if(BitMask) *BitMask = 0x00000C00;
            if(BitOfs) *BitOfs = 10;
            return 0x0148;
         case 9:
            // DAC channel c modified flags
            if(BitMask) *BitMask = 0x00000C00;
            if(BitOfs) *BitOfs = 10;
            return 0x0144;
         default:
            throw std::invalid_argument("Function GetDac1CModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC1_D_MOD
   unsigned int GetDac1DMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel d modified flags
            return BitExtractStatus(0x0148, 0x00000300, 8);
         case 9:
            // DAC channel d modified flags
            return BitExtractStatus(0x0144, 0x00000300, 8);
         default:
            throw std::invalid_argument("Function GetDac1DMod() not defined for this board version");
      };
   };
   unsigned int GetDac1DModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel d modified flags
            if(BitMask) *BitMask = 0x00000300;
            if(BitOfs) *BitOfs = 8;
            return 0x0148;
         case 9:
            // DAC channel d modified flags
            if(BitMask) *BitMask = 0x00000300;
            if(BitOfs) *BitOfs = 8;
            return 0x0144;
         default:
            throw std::invalid_argument("Function GetDac1DModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC1_E_MOD
   unsigned int GetDac1EMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel e modified flags
            return BitExtractStatus(0x0148, 0x000000C0, 6);
         case 9:
            // DAC channel e modified flags
            return BitExtractStatus(0x0144, 0x000000C0, 6);
         default:
            throw std::invalid_argument("Function GetDac1EMod() not defined for this board version");
      };
   };
   unsigned int GetDac1EModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel e modified flags
            if(BitMask) *BitMask = 0x000000C0;
            if(BitOfs) *BitOfs = 6;
            return 0x0148;
         case 9:
            // DAC channel e modified flags
            if(BitMask) *BitMask = 0x000000C0;
            if(BitOfs) *BitOfs = 6;
            return 0x0144;
         default:
            throw std::invalid_argument("Function GetDac1EModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC1_F_MOD
   unsigned int GetDac1FMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel f modified flags
            return BitExtractStatus(0x0148, 0x00000030, 4);
         case 9:
            // DAC channel f modified flags
            return BitExtractStatus(0x0144, 0x00000030, 4);
         default:
            throw std::invalid_argument("Function GetDac1FMod() not defined for this board version");
      };
   };
   unsigned int GetDac1FModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel f modified flags
            if(BitMask) *BitMask = 0x00000030;
            if(BitOfs) *BitOfs = 4;
            return 0x0148;
         case 9:
            // DAC channel f modified flags
            if(BitMask) *BitMask = 0x00000030;
            if(BitOfs) *BitOfs = 4;
            return 0x0144;
         default:
            throw std::invalid_argument("Function GetDac1FModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC1_G_MOD
   unsigned int GetDac1GMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel g modified flags
            return BitExtractStatus(0x0148, 0x0000000C, 2);
         case 9:
            // DAC channel g modified flags
            return BitExtractStatus(0x0144, 0x0000000C, 2);
         default:
            throw std::invalid_argument("Function GetDac1GMod() not defined for this board version");
      };
   };
   unsigned int GetDac1GModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel g modified flags
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x0148;
         case 9:
            // DAC channel g modified flags
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x0144;
         default:
            throw std::invalid_argument("Function GetDac1GModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC1_H_MOD
   unsigned int GetDac1HMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel h modified flags
            return BitExtractStatus(0x0148, 0x00000003, 0);
         case 9:
            // DAC channel h modified flags
            return BitExtractStatus(0x0144, 0x00000003, 0);
         default:
            throw std::invalid_argument("Function GetDac1HMod() not defined for this board version");
      };
   };
   unsigned int GetDac1HModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel h modified flags
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x0148;
         case 9:
            // DAC channel h modified flags
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x0144;
         default:
            throw std::invalid_argument("Function GetDac1HModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC2_A_MOD
   unsigned int GetDac2AMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel a modified flags
            return BitExtractStatus(0x014C, 0xC0000000, 30);
         case 9:
            // DAC channel a modified flags
            return BitExtractStatus(0x0148, 0xC0000000, 30);
         default:
            throw std::invalid_argument("Function GetDac2AMod() not defined for this board version");
      };
   };
   unsigned int GetDac2AModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel a modified flags
            if(BitMask) *BitMask = 0xC0000000;
            if(BitOfs) *BitOfs = 30;
            return 0x014C;
         case 9:
            // DAC channel a modified flags
            if(BitMask) *BitMask = 0xC0000000;
            if(BitOfs) *BitOfs = 30;
            return 0x0148;
         default:
            throw std::invalid_argument("Function GetDac2AModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC2_B_MOD
   unsigned int GetDac2BMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel b modified flags
            return BitExtractStatus(0x014C, 0x30000000, 28);
         case 9:
            // DAC channel b modified flags
            return BitExtractStatus(0x0148, 0x30000000, 28);
         default:
            throw std::invalid_argument("Function GetDac2BMod() not defined for this board version");
      };
   };
   unsigned int GetDac2BModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel b modified flags
            if(BitMask) *BitMask = 0x30000000;
            if(BitOfs) *BitOfs = 28;
            return 0x014C;
         case 9:
            // DAC channel b modified flags
            if(BitMask) *BitMask = 0x30000000;
            if(BitOfs) *BitOfs = 28;
            return 0x0148;
         default:
            throw std::invalid_argument("Function GetDac2BModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC2_CH_A
   unsigned int GetDac2ChA()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel A (TLEVEL_8) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x1068, 0xFFFF0000, 16);
         default:
            throw std::invalid_argument("Function GetDac2ChA() not defined for this board version");
      };
   };
   void SetDac2ChA(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel A (TLEVEL_8) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x1068, 0xFFFF0000, 16, value);
         default:
            throw std::invalid_argument("Function SetDac2ChA() not defined for this board version");
      };
   };
   unsigned int GetDac2ChALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel A (TLEVEL_8) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1068;
         default:
            throw std::invalid_argument("Function GetDac2ChALoc() not defined for this board version");
      };
   };

   // Bit(s) DAC2_CH_B
   unsigned int GetDac2ChB()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel B (TLEVEL_9) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x1068, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetDac2ChB() not defined for this board version");
      };
   };
   void SetDac2ChB(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel B (TLEVEL_9) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x1068, 0x0000FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetDac2ChB() not defined for this board version");
      };
   };
   unsigned int GetDac2ChBLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel B (TLEVEL_9) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1068;
         default:
            throw std::invalid_argument("Function GetDac2ChBLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC2_CH_C
   unsigned int GetDac2ChC()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel C (TLEVEL_10) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x106C, 0xFFFF0000, 16);
         default:
            throw std::invalid_argument("Function GetDac2ChC() not defined for this board version");
      };
   };
   void SetDac2ChC(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel C (TLEVEL_10) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x106C, 0xFFFF0000, 16, value);
         default:
            throw std::invalid_argument("Function SetDac2ChC() not defined for this board version");
      };
   };
   unsigned int GetDac2ChCLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel C (TLEVEL_10) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x106C;
         default:
            throw std::invalid_argument("Function GetDac2ChCLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC2_CH_D
   unsigned int GetDac2ChD()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel D (TLEVEL_11) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x106C, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetDac2ChD() not defined for this board version");
      };
   };
   void SetDac2ChD(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel D (TLEVEL_11) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x106C, 0x0000FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetDac2ChD() not defined for this board version");
      };
   };
   unsigned int GetDac2ChDLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel D (TLEVEL_11) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x106C;
         default:
            throw std::invalid_argument("Function GetDac2ChDLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC2_CH_E
   unsigned int GetDac2ChE()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel E (TLEVEL_12) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x1070, 0xFFFF0000, 16);
         default:
            throw std::invalid_argument("Function GetDac2ChE() not defined for this board version");
      };
   };
   void SetDac2ChE(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel E (TLEVEL_12) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x1070, 0xFFFF0000, 16, value);
         default:
            throw std::invalid_argument("Function SetDac2ChE() not defined for this board version");
      };
   };
   unsigned int GetDac2ChELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel E (TLEVEL_12) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1070;
         default:
            throw std::invalid_argument("Function GetDac2ChELoc() not defined for this board version");
      };
   };

   // Bit(s) DAC2_CH_F
   unsigned int GetDac2ChF()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel F (TLEVEL_13) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x1070, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetDac2ChF() not defined for this board version");
      };
   };
   void SetDac2ChF(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel F (TLEVEL_13) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x1070, 0x0000FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetDac2ChF() not defined for this board version");
      };
   };
   unsigned int GetDac2ChFLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel F (TLEVEL_13) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1070;
         default:
            throw std::invalid_argument("Function GetDac2ChFLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC2_CH_G
   unsigned int GetDac2ChG()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel G (TLEVEL_14) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x1074, 0xFFFF0000, 16);
         default:
            throw std::invalid_argument("Function GetDac2ChG() not defined for this board version");
      };
   };
   void SetDac2ChG(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel G (TLEVEL_14) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x1074, 0xFFFF0000, 16, value);
         default:
            throw std::invalid_argument("Function SetDac2ChG() not defined for this board version");
      };
   };
   unsigned int GetDac2ChGLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel G (TLEVEL_14) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1074;
         default:
            throw std::invalid_argument("Function GetDac2ChGLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC2_CH_H
   unsigned int GetDac2ChH()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel H (TLEVEL_15) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return BitExtractControl(0x1074, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetDac2ChH() not defined for this board version");
      };
   };
   void SetDac2ChH(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel H (TLEVEL_15) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            return SetRegMask(0x1074, 0x0000FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetDac2ChH() not defined for this board version");
      };
   };
   unsigned int GetDac2ChHLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set DAC2 channel H (TLEVEL_15) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1074;
         default:
            throw std::invalid_argument("Function GetDac2ChHLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC2_C_MOD
   unsigned int GetDac2CMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel c modified flags
            return BitExtractStatus(0x014C, 0x0C000000, 26);
         case 9:
            // DAC channel c modified flags
            return BitExtractStatus(0x0148, 0x0C000000, 26);
         default:
            throw std::invalid_argument("Function GetDac2CMod() not defined for this board version");
      };
   };
   unsigned int GetDac2CModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel c modified flags
            if(BitMask) *BitMask = 0x0C000000;
            if(BitOfs) *BitOfs = 26;
            return 0x014C;
         case 9:
            // DAC channel c modified flags
            if(BitMask) *BitMask = 0x0C000000;
            if(BitOfs) *BitOfs = 26;
            return 0x0148;
         default:
            throw std::invalid_argument("Function GetDac2CModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC2_D_MOD
   unsigned int GetDac2DMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel d modified flags
            return BitExtractStatus(0x014C, 0x03000000, 24);
         case 9:
            // DAC channel d modified flags
            return BitExtractStatus(0x0148, 0x03000000, 24);
         default:
            throw std::invalid_argument("Function GetDac2DMod() not defined for this board version");
      };
   };
   unsigned int GetDac2DModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel d modified flags
            if(BitMask) *BitMask = 0x03000000;
            if(BitOfs) *BitOfs = 24;
            return 0x014C;
         case 9:
            // DAC channel d modified flags
            if(BitMask) *BitMask = 0x03000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0148;
         default:
            throw std::invalid_argument("Function GetDac2DModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC2_E_MOD
   unsigned int GetDac2EMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel e modified flags
            return BitExtractStatus(0x014C, 0x00C00000, 22);
         case 9:
            // DAC channel e modified flags
            return BitExtractStatus(0x0148, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetDac2EMod() not defined for this board version");
      };
   };
   unsigned int GetDac2EModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel e modified flags
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x014C;
         case 9:
            // DAC channel e modified flags
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x0148;
         default:
            throw std::invalid_argument("Function GetDac2EModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC2_F_MOD
   unsigned int GetDac2FMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel f modified flags
            return BitExtractStatus(0x014C, 0x00300000, 20);
         case 9:
            // DAC channel f modified flags
            return BitExtractStatus(0x0148, 0x00300000, 20);
         default:
            throw std::invalid_argument("Function GetDac2FMod() not defined for this board version");
      };
   };
   unsigned int GetDac2FModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel f modified flags
            if(BitMask) *BitMask = 0x00300000;
            if(BitOfs) *BitOfs = 20;
            return 0x014C;
         case 9:
            // DAC channel f modified flags
            if(BitMask) *BitMask = 0x00300000;
            if(BitOfs) *BitOfs = 20;
            return 0x0148;
         default:
            throw std::invalid_argument("Function GetDac2FModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC2_G_MOD
   unsigned int GetDac2GMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel g modified flags
            return BitExtractStatus(0x014C, 0x000C0000, 18);
         case 9:
            // DAC channel g modified flags
            return BitExtractStatus(0x0148, 0x000C0000, 18);
         default:
            throw std::invalid_argument("Function GetDac2GMod() not defined for this board version");
      };
   };
   unsigned int GetDac2GModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel g modified flags
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x014C;
         case 9:
            // DAC channel g modified flags
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x0148;
         default:
            throw std::invalid_argument("Function GetDac2GModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAC2_H_MOD
   unsigned int GetDac2HMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel h modified flags
            return BitExtractStatus(0x014C, 0x00030000, 16);
         case 9:
            // DAC channel h modified flags
            return BitExtractStatus(0x0148, 0x00030000, 16);
         default:
            throw std::invalid_argument("Function GetDac2HMod() not defined for this board version");
      };
   };
   unsigned int GetDac2HModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DAC channel h modified flags
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x014C;
         case 9:
            // DAC channel h modified flags
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x0148;
         default:
            throw std::invalid_argument("Function GetDac2HModLoc() not defined for this board version");
      };
   };

   // Bit(s) DAQ_AUTO
   unsigned int GetDaqAuto()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Auto-Trigger readout state machine every 0.5s if no other trigger (like "auto" acquisition on scope)
            return BitExtractControl(0x1004, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetDaqAuto() not defined for this board version");
      };
   };
   void SetDaqAuto(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Auto-Trigger readout state machine every 0.5s if no other trigger (like "auto" acquisition on scope)
            return SetRegMask(0x1004, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetDaqAuto() not defined for this board version");
      };
   };
   unsigned int GetDaqAutoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Auto-Trigger readout state machine every 0.5s if no other trigger (like "auto" acquisition on scope)
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1004;
         default:
            throw std::invalid_argument("Function GetDaqAutoLoc() not defined for this board version");
      };
   };

   // Bit(s) DAQ_CLK_DEF_PHASE_CHKD
   unsigned int GetDaqClkDefPhaseChkd()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DAQ clock default phase setting is checked
            return BitExtractStatus(0x0028, 0x00001000, 12);
         default:
            throw std::invalid_argument("Function GetDaqClkDefPhaseChkd() not defined for this board version");
      };
   };
   unsigned int GetDaqClkDefPhaseChkdLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DAQ clock default phase setting is checked
            if(BitMask) *BitMask = 0x00001000;
            if(BitOfs) *BitOfs = 12;
            return 0x0028;
         default:
            throw std::invalid_argument("Function GetDaqClkDefPhaseChkdLoc() not defined for this board version");
      };
   };

   // Bit(s) DAQ_CLK_DEF_PHASE_OK
   unsigned int GetDaqClkDefPhaseOk()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DAQ clock default phase setting is valid
            return BitExtractStatus(0x0028, 0x00002000, 13);
         default:
            throw std::invalid_argument("Function GetDaqClkDefPhaseOk() not defined for this board version");
      };
   };
   unsigned int GetDaqClkDefPhaseOkLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DAQ clock default phase setting is valid
            if(BitMask) *BitMask = 0x00002000;
            if(BitOfs) *BitOfs = 13;
            return 0x0028;
         default:
            throw std::invalid_argument("Function GetDaqClkDefPhaseOkLoc() not defined for this board version");
      };
   };

   // Bit(s) DAQ_CLK_SRC_SEL
   unsigned int GetDaqClkSrcSel()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DAQ clock source select: 0 = DCB clock / 1 = on board oscillator (CLK_SEL)
            return BitExtractControl(0x100C, 0x00020000, 17);
         default:
            throw std::invalid_argument("Function GetDaqClkSrcSel() not defined for this board version");
      };
   };
   void SetDaqClkSrcSel(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DAQ clock source select: 0 = DCB clock / 1 = on board oscillator (CLK_SEL)
            return SetRegMask(0x100C, 0x00020000, 17, value);
         default:
            throw std::invalid_argument("Function SetDaqClkSrcSel() not defined for this board version");
      };
   };
   unsigned int GetDaqClkSrcSelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DAQ clock source select: 0 = DCB clock / 1 = on board oscillator (CLK_SEL)
            if(BitMask) *BitMask = 0x00020000;
            if(BitOfs) *BitOfs = 17;
            return 0x100C;
         default:
            throw std::invalid_argument("Function GetDaqClkSrcSelLoc() not defined for this board version");
      };
   };

   // Bit(s) DAQ_DATA_PHASE
   unsigned int GetDaqDataPhase()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Phase step setting of the PLL generating the common DAQ clock
            return BitExtractControl(0x1004, 0x00FF0000, 16);
         default:
            throw std::invalid_argument("Function GetDaqDataPhase() not defined for this board version");
      };
   };
   void SetDaqDataPhase(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Phase step setting of the PLL generating the common DAQ clock
            return SetRegMask(0x1004, 0x00FF0000, 16, value);
         default:
            throw std::invalid_argument("Function SetDaqDataPhase() not defined for this board version");
      };
   };
   unsigned int GetDaqDataPhaseLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Phase step setting of the PLL generating the common DAQ clock
            if(BitMask) *BitMask = 0x00FF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1004;
         default:
            throw std::invalid_argument("Function GetDaqDataPhaseLoc() not defined for this board version");
      };
   };

   // Bit(s) DAQ_NORMAL
   unsigned int GetDaqNormal()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Restart readout state machine automatically after readout (like "normal" acquisition on scope)
            return BitExtractControl(0x1004, 0x00000002, 1);
         default:
            throw std::invalid_argument("Function GetDaqNormal() not defined for this board version");
      };
   };
   void SetDaqNormal(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Restart readout state machine automatically after readout (like "normal" acquisition on scope)
            return SetRegMask(0x1004, 0x00000002, 1, value);
         default:
            throw std::invalid_argument("Function SetDaqNormal() not defined for this board version");
      };
   };
   unsigned int GetDaqNormalLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Restart readout state machine automatically after readout (like "normal" acquisition on scope)
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x1004;
         default:
            throw std::invalid_argument("Function GetDaqNormalLoc() not defined for this board version");
      };
   };

   // Bit(s) DAQ_PLL_LOCK
   unsigned int GetDaqPllLock()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Lock of DAQ PLL (FPGA internal)
            return BitExtractStatus(0x002C, 0x00000080, 7);
         default:
            throw std::invalid_argument("Function GetDaqPllLock() not defined for this board version");
      };
   };
   unsigned int GetDaqPllLockLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Lock of DAQ PLL (FPGA internal)
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x002C;
         default:
            throw std::invalid_argument("Function GetDaqPllLockLoc() not defined for this board version");
      };
   };

   // Bit(s) DAQ_PLL_RST
   unsigned int GetDaqPllRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the PLL for the DAQ clock
            return BitExtractControl(0x1040, 0x00004000, 14);
         default:
            throw std::invalid_argument("Function GetDaqPllRst() not defined for this board version");
      };
   };
   void SetDaqPllRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the PLL for the DAQ clock
            return SetRegMask(0x1040, 0x00004000, 14, value);
         default:
            throw std::invalid_argument("Function SetDaqPllRst() not defined for this board version");
      };
   };
   unsigned int GetDaqPllRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the PLL for the DAQ clock
            if(BitMask) *BitMask = 0x00004000;
            if(BitOfs) *BitOfs = 14;
            return 0x1040;
         default:
            throw std::invalid_argument("Function GetDaqPllRstLoc() not defined for this board version");
      };
   };

   // Bit(s) DAQ_SINGLE
   unsigned int GetDaqSingle()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Start readout state machine automatically and stop after readout (like "single" acquisition on scope)
            return BitExtractControl(0x1004, 0x00000001, 0);
         default:
            throw std::invalid_argument("Function GetDaqSingle() not defined for this board version");
      };
   };
   void SetDaqSingle(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Start readout state machine automatically and stop after readout (like "single" acquisition on scope)
            return SetRegMask(0x1004, 0x00000001, 0, value);
         default:
            throw std::invalid_argument("Function SetDaqSingle() not defined for this board version");
      };
   };
   unsigned int GetDaqSingleLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Start readout state machine automatically and stop after readout (like "single" acquisition on scope)
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x1004;
         default:
            throw std::invalid_argument("Function GetDaqSingleLoc() not defined for this board version");
      };
   };

   // Bit(s) DAQ_SOFT_TRIGGER
   unsigned int GetDaqSoftTrigger()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // write a "1" to stop the DRS chip & read the data to RAM
            return BitExtractControl(0x1004, 0x00000020, 5);
         default:
            throw std::invalid_argument("Function GetDaqSoftTrigger() not defined for this board version");
      };
   };
   void SetDaqSoftTrigger(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // write a "1" to stop the DRS chip & read the data to RAM
            return SetRegMask(0x1004, 0x00000020, 5, value);
         default:
            throw std::invalid_argument("Function SetDaqSoftTrigger() not defined for this board version");
      };
   };
   unsigned int GetDaqSoftTriggerLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // write a "1" to stop the DRS chip & read the data to RAM
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x1004;
         default:
            throw std::invalid_argument("Function GetDaqSoftTriggerLoc() not defined for this board version");
      };
   };

   // Bit(s) DATA_LINK_IF_RST
   unsigned int GetDataLinkIfRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset of the interface between packager and Ethernet/SERDES interface
            return BitExtractControl(0x1040, 0x00000010, 4);
         default:
            throw std::invalid_argument("Function GetDataLinkIfRst() not defined for this board version");
      };
   };
   void SetDataLinkIfRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset of the interface between packager and Ethernet/SERDES interface
            return SetRegMask(0x1040, 0x00000010, 4, value);
         default:
            throw std::invalid_argument("Function SetDataLinkIfRst() not defined for this board version");
      };
   };
   unsigned int GetDataLinkIfRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset of the interface between packager and Ethernet/SERDES interface
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x1040;
         default:
            throw std::invalid_argument("Function GetDataLinkIfRstLoc() not defined for this board version");
      };
   };

   // Bit(s) DCB_OSERDES_IF_RST
   unsigned int GetDcbOserdesIfRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the DCB OSERDES interface
            return BitExtractControl(0x1040, 0x00000800, 11);
         default:
            throw std::invalid_argument("Function GetDcbOserdesIfRst() not defined for this board version");
      };
   };
   void SetDcbOserdesIfRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the DCB OSERDES interface
            return SetRegMask(0x1040, 0x00000800, 11, value);
         default:
            throw std::invalid_argument("Function SetDcbOserdesIfRst() not defined for this board version");
      };
   };
   unsigned int GetDcbOserdesIfRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the DCB OSERDES interface
            if(BitMask) *BitMask = 0x00000800;
            if(BitOfs) *BitOfs = 11;
            return 0x1040;
         default:
            throw std::invalid_argument("Function GetDcbOserdesIfRstLoc() not defined for this board version");
      };
   };

   // Bit(s) DCB_OSERDES_PLL_RST
   unsigned int GetDcbOserdesPllRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the PLL of the DCB OSERDES
            return BitExtractControl(0x1040, 0x00002000, 13);
         default:
            throw std::invalid_argument("Function GetDcbOserdesPllRst() not defined for this board version");
      };
   };
   void SetDcbOserdesPllRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the PLL of the DCB OSERDES
            return SetRegMask(0x1040, 0x00002000, 13, value);
         default:
            throw std::invalid_argument("Function SetDcbOserdesPllRst() not defined for this board version");
      };
   };
   unsigned int GetDcbOserdesPllRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the PLL of the DCB OSERDES
            if(BitMask) *BitMask = 0x00002000;
            if(BitOfs) *BitOfs = 13;
            return 0x1040;
         default:
            throw std::invalid_argument("Function GetDcbOserdesPllRstLoc() not defined for this board version");
      };
   };

   // Bit(s) DCB_SERDES_TRAIN
   unsigned int GetDcbSerdesTrain()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable training pattern for DCB SERDES connection
            return BitExtractControl(0x1014, 0x80000000, 31);
         default:
            throw std::invalid_argument("Function GetDcbSerdesTrain() not defined for this board version");
      };
   };
   void SetDcbSerdesTrain(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable training pattern for DCB SERDES connection
            return SetRegMask(0x1014, 0x80000000, 31, value);
         default:
            throw std::invalid_argument("Function SetDcbSerdesTrain() not defined for this board version");
      };
   };
   unsigned int GetDcbSerdesTrainLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable training pattern for DCB SERDES connection
            if(BitMask) *BitMask = 0x80000000;
            if(BitOfs) *BitOfs = 31;
            return 0x1014;
         default:
            throw std::invalid_argument("Function GetDcbSerdesTrainLoc() not defined for this board version");
      };
   };

   // Bit(s) DRS_0_TIMING_REF_SEL
   unsigned int GetDrs0TimingRefSel()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Select timing reference signal for DRS 0: 0 = oscillator / 1 = LMK (CAL_CTRL_A)
            return BitExtractControl(0x1008, 0x00000008, 3);
         default:
            throw std::invalid_argument("Function GetDrs0TimingRefSel() not defined for this board version");
      };
   };
   void SetDrs0TimingRefSel(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Select timing reference signal for DRS 0: 0 = oscillator / 1 = LMK (CAL_CTRL_A)
            return SetRegMask(0x1008, 0x00000008, 3, value);
         default:
            throw std::invalid_argument("Function SetDrs0TimingRefSel() not defined for this board version");
      };
   };
   unsigned int GetDrs0TimingRefSelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Select timing reference signal for DRS 0: 0 = oscillator / 1 = LMK (CAL_CTRL_A)
            if(BitMask) *BitMask = 0x00000008;
            if(BitOfs) *BitOfs = 3;
            return 0x1008;
         default:
            throw std::invalid_argument("Function GetDrs0TimingRefSelLoc() not defined for this board version");
      };
   };

   // Bit(s) DRS_1_TIMING_REF_SEL
   unsigned int GetDrs1TimingRefSel()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Select timing reference signal for DRS 1: 0 = oscillator / 1 = LMK  (CAL_CTRL_B)
            return BitExtractControl(0x1008, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetDrs1TimingRefSel() not defined for this board version");
      };
   };
   void SetDrs1TimingRefSel(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Select timing reference signal for DRS 1: 0 = oscillator / 1 = LMK  (CAL_CTRL_B)
            return SetRegMask(0x1008, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetDrs1TimingRefSel() not defined for this board version");
      };
   };
   unsigned int GetDrs1TimingRefSelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Select timing reference signal for DRS 1: 0 = oscillator / 1 = LMK  (CAL_CTRL_B)
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1008;
         default:
            throw std::invalid_argument("Function GetDrs1TimingRefSelLoc() not defined for this board version");
      };
   };

   // Bit(s) DRS_CH_TX_EN
   unsigned int GetDrsChTxEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DRS channel transmission enable [Ch17:Ch0] - (CH17:CH16 = timing channels)
            return BitExtractControl(0x101C, 0x0003FFFF, 0);
         default:
            throw std::invalid_argument("Function GetDrsChTxEn() not defined for this board version");
      };
   };
   void SetDrsChTxEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DRS channel transmission enable [Ch17:Ch0] - (CH17:CH16 = timing channels)
            return SetRegMask(0x101C, 0x0003FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetDrsChTxEn() not defined for this board version");
      };
   };
   unsigned int GetDrsChTxEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DRS channel transmission enable [Ch17:Ch0] - (CH17:CH16 = timing channels)
            if(BitMask) *BitMask = 0x0003FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x101C;
         default:
            throw std::invalid_argument("Function GetDrsChTxEnLoc() not defined for this board version");
      };
   };

   // Bit(s) DRS_CLR_RSR_AFTER_RO
   unsigned int GetDrsClrRsrAfterRo()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Clear the read shift register (remove the token) after each readout
            return BitExtractControl(0x1004, 0x00000400, 10);
         default:
            throw std::invalid_argument("Function GetDrsClrRsrAfterRo() not defined for this board version");
      };
   };
   void SetDrsClrRsrAfterRo(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Clear the read shift register (remove the token) after each readout
            return SetRegMask(0x1004, 0x00000400, 10, value);
         default:
            throw std::invalid_argument("Function SetDrsClrRsrAfterRo() not defined for this board version");
      };
   };
   unsigned int GetDrsClrRsrAfterRoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Clear the read shift register (remove the token) after each readout
            if(BitMask) *BitMask = 0x00000400;
            if(BitOfs) *BitOfs = 10;
            return 0x1004;
         default:
            throw std::invalid_argument("Function GetDrsClrRsrAfterRoLoc() not defined for this board version");
      };
   };

   // Bit(s) DRS_CONFIGURE
   unsigned int GetDrsConfigure()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // write a "1" to trigger the DRS chip register configuration
            return BitExtractControl(0x1004, 0x00000040, 6);
         default:
            throw std::invalid_argument("Function GetDrsConfigure() not defined for this board version");
      };
   };
   void SetDrsConfigure(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // write a "1" to trigger the DRS chip register configuration
            return SetRegMask(0x1004, 0x00000040, 6, value);
         default:
            throw std::invalid_argument("Function SetDrsConfigure() not defined for this board version");
      };
   };
   unsigned int GetDrsConfigureLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // write a "1" to trigger the DRS chip register configuration
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x1004;
         default:
            throw std::invalid_argument("Function GetDrsConfigureLoc() not defined for this board version");
      };
   };

   // Bit(s) DRS_CONFIG_DONE
   unsigned int GetDrsConfigDone()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DRS configuration done
            return BitExtractStatus(0x0028, 0x00000400, 10);
         default:
            throw std::invalid_argument("Function GetDrsConfigDone() not defined for this board version");
      };
   };
   unsigned int GetDrsConfigDoneLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DRS configuration done
            if(BitMask) *BitMask = 0x00000400;
            if(BitOfs) *BitOfs = 10;
            return 0x0028;
         default:
            throw std::invalid_argument("Function GetDrsConfigDoneLoc() not defined for this board version");
      };
   };

   // Bit(s) DRS_CTRL_BUSY
   unsigned int GetDrsCtrlBusy()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // "1" while domino wave running or readout in progress
            return BitExtractStatus(0x0028, 0x00000020, 5);
         default:
            throw std::invalid_argument("Function GetDrsCtrlBusy() not defined for this board version");
      };
   };
   unsigned int GetDrsCtrlBusyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // "1" while domino wave running or readout in progress
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x0028;
         default:
            throw std::invalid_argument("Function GetDrsCtrlBusyLoc() not defined for this board version");
      };
   };

   // Bit(s) DRS_CTRL_FSM_RST
   unsigned int GetDrsCtrlFsmRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DRS control FSM reset
            return BitExtractControl(0x1040, 0x00000002, 1);
         default:
            throw std::invalid_argument("Function GetDrsCtrlFsmRst() not defined for this board version");
      };
   };
   void SetDrsCtrlFsmRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DRS control FSM reset
            return SetRegMask(0x1040, 0x00000002, 1, value);
         default:
            throw std::invalid_argument("Function SetDrsCtrlFsmRst() not defined for this board version");
      };
   };
   unsigned int GetDrsCtrlFsmRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DRS control FSM reset
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x1040;
         default:
            throw std::invalid_argument("Function GetDrsCtrlFsmRstLoc() not defined for this board version");
      };
   };

   // Bit(s) DRS_CTRL_MOD
   unsigned int GetDrsCtrlMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DRS control bits modified flags
            return BitExtractStatus(0x013C, 0x00000004, 2);
         case 9:
            // DRS control bits modified flags
            return BitExtractStatus(0x0138, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetDrsCtrlMod() not defined for this board version");
      };
   };
   unsigned int GetDrsCtrlModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DRS control bits modified flags
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x013C;
         case 9:
            // DRS control bits modified flags
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x0138;
         default:
            throw std::invalid_argument("Function GetDrsCtrlModLoc() not defined for this board version");
      };
   };

   // Bit(s) DRS_DMODE
   unsigned int GetDrsDmode()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Domino Mode Control (0 = single shot, 1 = continuous)
            return BitExtractControl(0x1010, 0x00010000, 16);
         default:
            throw std::invalid_argument("Function GetDrsDmode() not defined for this board version");
      };
   };
   void SetDrsDmode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Domino Mode Control (0 = single shot, 1 = continuous)
            return SetRegMask(0x1010, 0x00010000, 16, value);
         default:
            throw std::invalid_argument("Function SetDrsDmode() not defined for this board version");
      };
   };
   unsigned int GetDrsDmodeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Domino Mode Control (0 = single shot, 1 = continuous)
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x1010;
         default:
            throw std::invalid_argument("Function GetDrsDmodeLoc() not defined for this board version");
      };
   };

   // Bit(s) DRS_PLLEN
   unsigned int GetDrsPllen()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Internal PLL Enable (0 = disable, 1 = enable)
            return BitExtractControl(0x1010, 0x00020000, 17);
         default:
            throw std::invalid_argument("Function GetDrsPllen() not defined for this board version");
      };
   };
   void SetDrsPllen(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Internal PLL Enable (0 = disable, 1 = enable)
            return SetRegMask(0x1010, 0x00020000, 17, value);
         default:
            throw std::invalid_argument("Function SetDrsPllen() not defined for this board version");
      };
   };
   unsigned int GetDrsPllenLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Internal PLL Enable (0 = disable, 1 = enable)
            if(BitMask) *BitMask = 0x00020000;
            if(BitOfs) *BitOfs = 17;
            return 0x1010;
         default:
            throw std::invalid_argument("Function GetDrsPllenLoc() not defined for this board version");
      };
   };

   // Bit(s) DRS_PLL_LOCK_0
   unsigned int GetDrsPllLock0()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // PLL lock signal of DRS Channel 0 (A) (external)
            return BitExtractStatus(0x002C, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetDrsPllLock0() not defined for this board version");
      };
   };
   unsigned int GetDrsPllLock0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // PLL lock signal of DRS Channel 0 (A) (external)
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x002C;
         default:
            throw std::invalid_argument("Function GetDrsPllLock0Loc() not defined for this board version");
      };
   };

   // Bit(s) DRS_PLL_LOCK_1
   unsigned int GetDrsPllLock1()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // PLL lock signal of DRS Channel 1 (B) (external)
            return BitExtractStatus(0x002C, 0x00000002, 1);
         default:
            throw std::invalid_argument("Function GetDrsPllLock1() not defined for this board version");
      };
   };
   unsigned int GetDrsPllLock1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // PLL lock signal of DRS Channel 1 (B) (external)
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x002C;
         default:
            throw std::invalid_argument("Function GetDrsPllLock1Loc() not defined for this board version");
      };
   };

   // Bit(s) DRS_READOUT_MODE
   unsigned int GetDrsReadoutMode()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // 0:start from first bin, 1:start from domino stop
            return BitExtractControl(0x1004, 0x00000100, 8);
         default:
            throw std::invalid_argument("Function GetDrsReadoutMode() not defined for this board version");
      };
   };
   void SetDrsReadoutMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // 0:start from first bin, 1:start from domino stop
            return SetRegMask(0x1004, 0x00000100, 8, value);
         default:
            throw std::invalid_argument("Function SetDrsReadoutMode() not defined for this board version");
      };
   };
   unsigned int GetDrsReadoutModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // 0:start from first bin, 1:start from domino stop
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1004;
         default:
            throw std::invalid_argument("Function GetDrsReadoutModeLoc() not defined for this board version");
      };
   };

   // Bit(s) DRS_SAMPLE_FREQ
   unsigned int GetDrsSampleFreq()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DRS Sampling frequency in kHz
            return BitExtractStatus(0x0038, 0x00FFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetDrsSampleFreq() not defined for this board version");
      };
   };
   unsigned int GetDrsSampleFreqLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DRS Sampling frequency in kHz
            if(BitMask) *BitMask = 0x00FFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0038;
         default:
            throw std::invalid_argument("Function GetDrsSampleFreqLoc() not defined for this board version");
      };
   };

   // Bit(s) DRS_STOP_CELL_0
   unsigned int GetDrsStopCell0()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Stop position of DRS Channel 0 (A)
            return BitExtractStatus(0x0030, 0x03FF0000, 16);
         default:
            throw std::invalid_argument("Function GetDrsStopCell0() not defined for this board version");
      };
   };
   unsigned int GetDrsStopCell0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Stop position of DRS Channel 0 (A)
            if(BitMask) *BitMask = 0x03FF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0030;
         default:
            throw std::invalid_argument("Function GetDrsStopCell0Loc() not defined for this board version");
      };
   };

   // Bit(s) DRS_STOP_CELL_1
   unsigned int GetDrsStopCell1()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Stop position of DRS Channel 1 (B)
            return BitExtractStatus(0x0030, 0x000003FF, 0);
         default:
            throw std::invalid_argument("Function GetDrsStopCell1() not defined for this board version");
      };
   };
   unsigned int GetDrsStopCell1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Stop position of DRS Channel 1 (B)
            if(BitMask) *BitMask = 0x000003FF;
            if(BitOfs) *BitOfs = 0;
            return 0x0030;
         default:
            throw std::invalid_argument("Function GetDrsStopCell1Loc() not defined for this board version");
      };
   };

   // Bit(s) DRS_STOP_WSR_0
   unsigned int GetDrsStopWsr0()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // WSR contents after stop of DRS Channel 0 (A)
            return BitExtractStatus(0x0034, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetDrsStopWsr0() not defined for this board version");
      };
   };
   unsigned int GetDrsStopWsr0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // WSR contents after stop of DRS Channel 0 (A)
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x0034;
         default:
            throw std::invalid_argument("Function GetDrsStopWsr0Loc() not defined for this board version");
      };
   };

   // Bit(s) DRS_STOP_WSR_1
   unsigned int GetDrsStopWsr1()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // WSR contents after stop of DRS Channel 1 (B)
            return BitExtractStatus(0x0034, 0x000000FF, 0);
         default:
            throw std::invalid_argument("Function GetDrsStopWsr1() not defined for this board version");
      };
   };
   unsigned int GetDrsStopWsr1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // WSR contents after stop of DRS Channel 1 (B)
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x0034;
         default:
            throw std::invalid_argument("Function GetDrsStopWsr1Loc() not defined for this board version");
      };
   };

   // Bit(s) DRS_TX_SAMPLES
   unsigned int GetDrsTxSamples()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Number of DRS samples to transmit per channel (must be an even value with range 2 to 1024)
            return BitExtractControl(0x1028, 0x000007FF, 0);
         default:
            throw std::invalid_argument("Function GetDrsTxSamples() not defined for this board version");
      };
   };
   void SetDrsTxSamples(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Number of DRS samples to transmit per channel (must be an even value with range 2 to 1024)
            return SetRegMask(0x1028, 0x000007FF, 0, value);
         default:
            throw std::invalid_argument("Function SetDrsTxSamples() not defined for this board version");
      };
   };
   unsigned int GetDrsTxSamplesLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Number of DRS samples to transmit per channel (must be an even value with range 2 to 1024)
            if(BitMask) *BitMask = 0x000007FF;
            if(BitOfs) *BitOfs = 0;
            return 0x1028;
         default:
            throw std::invalid_argument("Function GetDrsTxSamplesLoc() not defined for this board version");
      };
   };

   // Bit(s) DRS_WAVE_CONTINUOUS
   unsigned int GetDrsWaveContinuous()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // 0:stop domino wave during readout, 1:keep it running
            return BitExtractControl(0x1004, 0x00000080, 7);
         default:
            throw std::invalid_argument("Function GetDrsWaveContinuous() not defined for this board version");
      };
   };
   void SetDrsWaveContinuous(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // 0:stop domino wave during readout, 1:keep it running
            return SetRegMask(0x1004, 0x00000080, 7, value);
         default:
            throw std::invalid_argument("Function SetDrsWaveContinuous() not defined for this board version");
      };
   };
   unsigned int GetDrsWaveContinuousLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // 0:stop domino wave during readout, 1:keep it running
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x1004;
         default:
            throw std::invalid_argument("Function GetDrsWaveContinuousLoc() not defined for this board version");
      };
   };

   // Bit(s) DRS_WCR
   unsigned int GetDrsWcr()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DRS4 Write Configuration Register (0xE)
            return BitExtractControl(0x1010, 0x000000FF, 0);
         default:
            throw std::invalid_argument("Function GetDrsWcr() not defined for this board version");
      };
   };
   void SetDrsWcr(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DRS4 Write Configuration Register (0xE)
            return SetRegMask(0x1010, 0x000000FF, 0, value);
         default:
            throw std::invalid_argument("Function SetDrsWcr() not defined for this board version");
      };
   };
   unsigned int GetDrsWcrLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DRS4 Write Configuration Register (0xE)
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x1010;
         default:
            throw std::invalid_argument("Function GetDrsWcrLoc() not defined for this board version");
      };
   };

   // Bit(s) DRS_WCR_MOD
   unsigned int GetDrsWcrMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DRS write control register modified flags
            return BitExtractStatus(0x013C, 0x00000001, 0);
         case 9:
            // DRS write control register modified flags
            return BitExtractStatus(0x0138, 0x00000001, 0);
         default:
            throw std::invalid_argument("Function GetDrsWcrMod() not defined for this board version");
      };
   };
   unsigned int GetDrsWcrModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DRS write control register modified flags
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x013C;
         case 9:
            // DRS write control register modified flags
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x0138;
         default:
            throw std::invalid_argument("Function GetDrsWcrModLoc() not defined for this board version");
      };
   };

   // Bit(s) DRS_WSR
   unsigned int GetDrsWsr()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DRS4 Write Shift Register (0xD)
            return BitExtractControl(0x1010, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetDrsWsr() not defined for this board version");
      };
   };
   void SetDrsWsr(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DRS4 Write Shift Register (0xD)
            return SetRegMask(0x1010, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetDrsWsr() not defined for this board version");
      };
   };
   unsigned int GetDrsWsrLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // DRS4 Write Shift Register (0xD)
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1010;
         default:
            throw std::invalid_argument("Function GetDrsWsrLoc() not defined for this board version");
      };
   };

   // Bit(s) DRS_WSRLOOP
   unsigned int GetDrsWsrloop()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Internally Connect WSRIN to WSROUT (if set to 1)
            return BitExtractControl(0x1010, 0x00040000, 18);
         default:
            throw std::invalid_argument("Function GetDrsWsrloop() not defined for this board version");
      };
   };
   void SetDrsWsrloop(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Internally Connect WSRIN to WSROUT (if set to 1)
            return SetRegMask(0x1010, 0x00040000, 18, value);
         default:
            throw std::invalid_argument("Function SetDrsWsrloop() not defined for this board version");
      };
   };
   unsigned int GetDrsWsrloopLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Internally Connect WSRIN to WSROUT (if set to 1)
            if(BitMask) *BitMask = 0x00040000;
            if(BitOfs) *BitOfs = 18;
            return 0x1010;
         default:
            throw std::invalid_argument("Function GetDrsWsrloopLoc() not defined for this board version");
      };
   };

   // Bit(s) DRS_WSR_MOD
   unsigned int GetDrsWsrMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // DRS write shift register modified flags
            return BitExtractStatus(0x013C, 0x00000002, 1);
         case 9:
            // DRS write shift register modified flags
            return BitExtractStatus(0x0138, 0x00000002, 1);
         default:
            throw std::invalid_argument("Function GetDrsWsrMod() not defined for this board version");
      };
   };
   unsigned int GetDrsWsrModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // DRS write shift register modified flags
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x013C;
         case 9:
            // DRS write shift register modified flags
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x0138;
         default:
            throw std::invalid_argument("Function GetDrsWsrModLoc() not defined for this board version");
      };
   };

   // Bit(s) ETH_COM_EN
   unsigned int GetEthComEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable ethernet communication
            return BitExtractControl(0x1014, 0x01000000, 24);
         default:
            throw std::invalid_argument("Function GetEthComEn() not defined for this board version");
      };
   };
   void SetEthComEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable ethernet communication
            return SetRegMask(0x1014, 0x01000000, 24, value);
         default:
            throw std::invalid_argument("Function SetEthComEn() not defined for this board version");
      };
   };
   unsigned int GetEthComEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable ethernet communication
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1014;
         default:
            throw std::invalid_argument("Function GetEthComEnLoc() not defined for this board version");
      };
   };

   // Bit(s) EVENT_COUNTER_RST
   unsigned int GetEventCounterRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Event Counter Reset
            return BitExtractControl(0x1040, 0x00000004, 2);
         default:
            throw std::invalid_argument("Function GetEventCounterRst() not defined for this board version");
      };
   };
   void SetEventCounterRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Event Counter Reset
            return SetRegMask(0x1040, 0x00000004, 2, value);
         default:
            throw std::invalid_argument("Function SetEventCounterRst() not defined for this board version");
      };
   };
   unsigned int GetEventCounterRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Event Counter Reset
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1040;
         default:
            throw std::invalid_argument("Function GetEventCounterRstLoc() not defined for this board version");
      };
   };

   // Bit(s) EVENT_NUMBER
   unsigned int GetEventNumber()
   {
      switch(this->mVersion)
      {
         case 8:
            // Number of latest event
            return BitExtractStatus(0x0104, 0xFFFFFFFF, 0);
         case 9:
            // Number of latest event
            return BitExtractStatus(0x0100, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetEventNumber() not defined for this board version");
      };
   };
   unsigned int GetEventNumberLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Number of latest event
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0104;
         case 9:
            // Number of latest event
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0100;
         default:
            throw std::invalid_argument("Function GetEventNumberLoc() not defined for this board version");
      };
   };

   // Bit(s) EVENT_TX_RATE
   unsigned int GetEventTxRate()
   {
      switch(this->mVersion)
      {
         case 8:
            // Number of events transmitted per second
            return BitExtractStatus(0x0100, 0xFFFFFFFF, 0);
         case 9:
            // Number of events transmitted per second
            return BitExtractStatus(0x00FC, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetEventTxRate() not defined for this board version");
      };
   };
   unsigned int GetEventTxRateLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Number of events transmitted per second
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0100;
         case 9:
            // Number of events transmitted per second
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00FC;
         default:
            throw std::invalid_argument("Function GetEventTxRateLoc() not defined for this board version");
      };
   };

   // Bit(s) EXT_ASYNC_TRIGGER_EN
   unsigned int GetExtAsyncTriggerEn()
   {
      switch(this->mVersion)
      {
         case 8:
            // Enable asynchronous external trigger
            return BitExtractControl(0x1180, 0x00002000, 13);
         case 9:
            // Enable asynchronous external trigger
            return BitExtractControl(0x1124, 0x00002000, 13);
         default:
            throw std::invalid_argument("Function GetExtAsyncTriggerEn() not defined for this board version");
      };
   };
   void SetExtAsyncTriggerEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Enable asynchronous external trigger
            return SetRegMask(0x1180, 0x00002000, 13, value);
         case 9:
            // Enable asynchronous external trigger
            return SetRegMask(0x1124, 0x00002000, 13, value);
         default:
            throw std::invalid_argument("Function SetExtAsyncTriggerEn() not defined for this board version");
      };
   };
   unsigned int GetExtAsyncTriggerEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Enable asynchronous external trigger
            if(BitMask) *BitMask = 0x00002000;
            if(BitOfs) *BitOfs = 13;
            return 0x1180;
         case 9:
            // Enable asynchronous external trigger
            if(BitMask) *BitMask = 0x00002000;
            if(BitOfs) *BitOfs = 13;
            return 0x1124;
         default:
            throw std::invalid_argument("Function GetExtAsyncTriggerEnLoc() not defined for this board version");
      };
   };

   // Bit(s) EXT_CLK_ACTIVE
   unsigned int GetExtClkActive()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Configuration for external clock for DAQ completed
            return BitExtractStatus(0x0028, 0x00004000, 14);
         default:
            throw std::invalid_argument("Function GetExtClkActive() not defined for this board version");
      };
   };
   unsigned int GetExtClkActiveLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Configuration for external clock for DAQ completed
            if(BitMask) *BitMask = 0x00004000;
            if(BitOfs) *BitOfs = 14;
            return 0x0028;
         default:
            throw std::invalid_argument("Function GetExtClkActiveLoc() not defined for this board version");
      };
   };

   // Bit(s) EXT_CLK_FREQ
   unsigned int GetExtClkFreq()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // External clock frequency (MCX or backplane) in MHz
            return BitExtractControl(0x100C, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetExtClkFreq() not defined for this board version");
      };
   };
   void SetExtClkFreq(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // External clock frequency (MCX or backplane) in MHz
            return SetRegMask(0x100C, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetExtClkFreq() not defined for this board version");
      };
   };
   unsigned int GetExtClkFreqLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // External clock frequency (MCX or backplane) in MHz
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x100C;
         default:
            throw std::invalid_argument("Function GetExtClkFreqLoc() not defined for this board version");
      };
   };

   // Bit(s) EXT_CLK_FREQ_MOD
   unsigned int GetExtClkFreqMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // External clock frequency modified flags
            return BitExtractStatus(0x0138, 0x00000002, 1);
         case 9:
            // External clock frequency modified flags
            return BitExtractStatus(0x0134, 0x00000002, 1);
         default:
            throw std::invalid_argument("Function GetExtClkFreqMod() not defined for this board version");
      };
   };
   unsigned int GetExtClkFreqModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // External clock frequency modified flags
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x0138;
         case 9:
            // External clock frequency modified flags
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x0134;
         default:
            throw std::invalid_argument("Function GetExtClkFreqModLoc() not defined for this board version");
      };
   };

   // Bit(s) EXT_CLK_IN_SEL
   unsigned int GetExtClkInSel()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // External clk input select: 0 = backplane / 1 = MCX connector (CLK_SEL_EXT)
            return BitExtractControl(0x100C, 0x00010000, 16);
         default:
            throw std::invalid_argument("Function GetExtClkInSel() not defined for this board version");
      };
   };
   void SetExtClkInSel(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // External clk input select: 0 = backplane / 1 = MCX connector (CLK_SEL_EXT)
            return SetRegMask(0x100C, 0x00010000, 16, value);
         default:
            throw std::invalid_argument("Function SetExtClkInSel() not defined for this board version");
      };
   };
   unsigned int GetExtClkInSelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // External clk input select: 0 = backplane / 1 = MCX connector (CLK_SEL_EXT)
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x100C;
         default:
            throw std::invalid_argument("Function GetExtClkInSelLoc() not defined for this board version");
      };
   };

   // Bit(s) EXT_TRIGGER_OUT_ENABLE
   unsigned int GetExtTriggerOutEnable()
   {
      switch(this->mVersion)
      {
         case 8:
            // Enable output of trigger signal to MCX connector
            return BitExtractControl(0x1180, 0x00008000, 15);
         case 9:
            // Enable output of trigger signal to MCX connector
            return BitExtractControl(0x1124, 0x00008000, 15);
         default:
            throw std::invalid_argument("Function GetExtTriggerOutEnable() not defined for this board version");
      };
   };
   void SetExtTriggerOutEnable(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Enable output of trigger signal to MCX connector
            return SetRegMask(0x1180, 0x00008000, 15, value);
         case 9:
            // Enable output of trigger signal to MCX connector
            return SetRegMask(0x1124, 0x00008000, 15, value);
         default:
            throw std::invalid_argument("Function SetExtTriggerOutEnable() not defined for this board version");
      };
   };
   unsigned int GetExtTriggerOutEnableLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Enable output of trigger signal to MCX connector
            if(BitMask) *BitMask = 0x00008000;
            if(BitOfs) *BitOfs = 15;
            return 0x1180;
         case 9:
            // Enable output of trigger signal to MCX connector
            if(BitMask) *BitMask = 0x00008000;
            if(BitOfs) *BitOfs = 15;
            return 0x1124;
         default:
            throw std::invalid_argument("Function GetExtTriggerOutEnableLoc() not defined for this board version");
      };
   };

   // Bit(s) FE0_AMPLIFIER1_COMP_EN
   unsigned int GetFe0Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 amplifier 1 compensation enable (COMP1)
            return BitExtractControl(0x1078, 0x00200000, 21);
         default:
            throw std::invalid_argument("Function GetFe0Amplifier1CompEn() not defined for this board version");
      };
   };
   void SetFe0Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 amplifier 1 compensation enable (COMP1)
            return SetRegMask(0x1078, 0x00200000, 21, value);
         default:
            throw std::invalid_argument("Function SetFe0Amplifier1CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe0Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 amplifier 1 compensation enable (COMP1)
            if(BitMask) *BitMask = 0x00200000;
            if(BitOfs) *BitOfs = 21;
            return 0x1078;
         default:
            throw std::invalid_argument("Function GetFe0Amplifier1CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE0_AMPLIFIER1_EN
   unsigned int GetFe0Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 amplifier 1 enable (gain: 10) (OP1)
            return BitExtractControl(0x1078, 0x00100000, 20);
         default:
            throw std::invalid_argument("Function GetFe0Amplifier1En() not defined for this board version");
      };
   };
   void SetFe0Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 amplifier 1 enable (gain: 10) (OP1)
            return SetRegMask(0x1078, 0x00100000, 20, value);
         default:
            throw std::invalid_argument("Function SetFe0Amplifier1En() not defined for this board version");
      };
   };
   unsigned int GetFe0Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 amplifier 1 enable (gain: 10) (OP1)
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x1078;
         default:
            throw std::invalid_argument("Function GetFe0Amplifier1EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE0_AMPLIFIER2_COMP_EN
   unsigned int GetFe0Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 amplifier 2 compensation enable (COMP2)
            return BitExtractControl(0x1078, 0x00800000, 23);
         default:
            throw std::invalid_argument("Function GetFe0Amplifier2CompEn() not defined for this board version");
      };
   };
   void SetFe0Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 amplifier 2 compensation enable (COMP2)
            return SetRegMask(0x1078, 0x00800000, 23, value);
         default:
            throw std::invalid_argument("Function SetFe0Amplifier2CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe0Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 amplifier 2 compensation enable (COMP2)
            if(BitMask) *BitMask = 0x00800000;
            if(BitOfs) *BitOfs = 23;
            return 0x1078;
         default:
            throw std::invalid_argument("Function GetFe0Amplifier2CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE0_AMPLIFIER2_EN
   unsigned int GetFe0Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 amplifier 2 enable (gain: 10) (OP2)
            return BitExtractControl(0x1078, 0x00400000, 22);
         default:
            throw std::invalid_argument("Function GetFe0Amplifier2En() not defined for this board version");
      };
   };
   void SetFe0Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 amplifier 2 enable (gain: 10) (OP2)
            return SetRegMask(0x1078, 0x00400000, 22, value);
         default:
            throw std::invalid_argument("Function SetFe0Amplifier2En() not defined for this board version");
      };
   };
   unsigned int GetFe0Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 amplifier 2 enable (gain: 10) (OP2)
            if(BitMask) *BitMask = 0x00400000;
            if(BitOfs) *BitOfs = 22;
            return 0x1078;
         default:
            throw std::invalid_argument("Function GetFe0Amplifier2EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE0_ATTENUATION
   unsigned int GetFe0Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return BitExtractControl(0x1078, 0x000C0000, 18);
         default:
            throw std::invalid_argument("Function GetFe0Attenuation() not defined for this board version");
      };
   };
   void SetFe0Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return SetRegMask(0x1078, 0x000C0000, 18, value);
         default:
            throw std::invalid_argument("Function SetFe0Attenuation() not defined for this board version");
      };
   };
   unsigned int GetFe0AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x1078;
         default:
            throw std::invalid_argument("Function GetFe0AttenuationLoc() not defined for this board version");
      };
   };

   // Bit(s) FE0_MUX
   unsigned int GetFe0Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return BitExtractControl(0x1078, 0x00030000, 16);
         default:
            throw std::invalid_argument("Function GetFe0Mux() not defined for this board version");
      };
   };
   void SetFe0Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return SetRegMask(0x1078, 0x00030000, 16, value);
         default:
            throw std::invalid_argument("Function SetFe0Mux() not defined for this board version");
      };
   };
   unsigned int GetFe0MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x1078;
         default:
            throw std::invalid_argument("Function GetFe0MuxLoc() not defined for this board version");
      };
   };

   // Bit(s) FE0_PZC_EN
   unsigned int GetFe0PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 PZC (pole-zero cancellation) enable (ACDC)
            return BitExtractControl(0x1078, 0x01000000, 24);
         default:
            throw std::invalid_argument("Function GetFe0PzcEn() not defined for this board version");
      };
   };
   void SetFe0PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 PZC (pole-zero cancellation) enable (ACDC)
            return SetRegMask(0x1078, 0x01000000, 24, value);
         default:
            throw std::invalid_argument("Function SetFe0PzcEn() not defined for this board version");
      };
   };
   unsigned int GetFe0PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 0 PZC (pole-zero cancellation) enable (ACDC)
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1078;
         default:
            throw std::invalid_argument("Function GetFe0PzcEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE10_AMPLIFIER1_COMP_EN
   unsigned int GetFe10Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 amplifier 1 compensation enable (COMP1)
            return BitExtractControl(0x108C, 0x00200000, 21);
         default:
            throw std::invalid_argument("Function GetFe10Amplifier1CompEn() not defined for this board version");
      };
   };
   void SetFe10Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 amplifier 1 compensation enable (COMP1)
            return SetRegMask(0x108C, 0x00200000, 21, value);
         default:
            throw std::invalid_argument("Function SetFe10Amplifier1CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe10Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 amplifier 1 compensation enable (COMP1)
            if(BitMask) *BitMask = 0x00200000;
            if(BitOfs) *BitOfs = 21;
            return 0x108C;
         default:
            throw std::invalid_argument("Function GetFe10Amplifier1CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE10_AMPLIFIER1_EN
   unsigned int GetFe10Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 amplifier 1 enable (gain: 10) (OP1)
            return BitExtractControl(0x108C, 0x00100000, 20);
         default:
            throw std::invalid_argument("Function GetFe10Amplifier1En() not defined for this board version");
      };
   };
   void SetFe10Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 amplifier 1 enable (gain: 10) (OP1)
            return SetRegMask(0x108C, 0x00100000, 20, value);
         default:
            throw std::invalid_argument("Function SetFe10Amplifier1En() not defined for this board version");
      };
   };
   unsigned int GetFe10Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 amplifier 1 enable (gain: 10) (OP1)
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x108C;
         default:
            throw std::invalid_argument("Function GetFe10Amplifier1EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE10_AMPLIFIER2_COMP_EN
   unsigned int GetFe10Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 amplifier 2 compensation enable (COMP2)
            return BitExtractControl(0x108C, 0x00800000, 23);
         default:
            throw std::invalid_argument("Function GetFe10Amplifier2CompEn() not defined for this board version");
      };
   };
   void SetFe10Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 amplifier 2 compensation enable (COMP2)
            return SetRegMask(0x108C, 0x00800000, 23, value);
         default:
            throw std::invalid_argument("Function SetFe10Amplifier2CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe10Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 amplifier 2 compensation enable (COMP2)
            if(BitMask) *BitMask = 0x00800000;
            if(BitOfs) *BitOfs = 23;
            return 0x108C;
         default:
            throw std::invalid_argument("Function GetFe10Amplifier2CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE10_AMPLIFIER2_EN
   unsigned int GetFe10Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 amplifier 2 enable (gain: 10) (OP2)
            return BitExtractControl(0x108C, 0x00400000, 22);
         default:
            throw std::invalid_argument("Function GetFe10Amplifier2En() not defined for this board version");
      };
   };
   void SetFe10Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 amplifier 2 enable (gain: 10) (OP2)
            return SetRegMask(0x108C, 0x00400000, 22, value);
         default:
            throw std::invalid_argument("Function SetFe10Amplifier2En() not defined for this board version");
      };
   };
   unsigned int GetFe10Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 amplifier 2 enable (gain: 10) (OP2)
            if(BitMask) *BitMask = 0x00400000;
            if(BitOfs) *BitOfs = 22;
            return 0x108C;
         default:
            throw std::invalid_argument("Function GetFe10Amplifier2EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE10_ATTENUATION
   unsigned int GetFe10Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return BitExtractControl(0x108C, 0x000C0000, 18);
         default:
            throw std::invalid_argument("Function GetFe10Attenuation() not defined for this board version");
      };
   };
   void SetFe10Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return SetRegMask(0x108C, 0x000C0000, 18, value);
         default:
            throw std::invalid_argument("Function SetFe10Attenuation() not defined for this board version");
      };
   };
   unsigned int GetFe10AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x108C;
         default:
            throw std::invalid_argument("Function GetFe10AttenuationLoc() not defined for this board version");
      };
   };

   // Bit(s) FE10_MUX
   unsigned int GetFe10Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return BitExtractControl(0x108C, 0x00030000, 16);
         default:
            throw std::invalid_argument("Function GetFe10Mux() not defined for this board version");
      };
   };
   void SetFe10Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return SetRegMask(0x108C, 0x00030000, 16, value);
         default:
            throw std::invalid_argument("Function SetFe10Mux() not defined for this board version");
      };
   };
   unsigned int GetFe10MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x108C;
         default:
            throw std::invalid_argument("Function GetFe10MuxLoc() not defined for this board version");
      };
   };

   // Bit(s) FE10_PZC_EN
   unsigned int GetFe10PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 PZC (pole-zero cancellation) enable (ACDC)
            return BitExtractControl(0x108C, 0x01000000, 24);
         default:
            throw std::invalid_argument("Function GetFe10PzcEn() not defined for this board version");
      };
   };
   void SetFe10PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 PZC (pole-zero cancellation) enable (ACDC)
            return SetRegMask(0x108C, 0x01000000, 24, value);
         default:
            throw std::invalid_argument("Function SetFe10PzcEn() not defined for this board version");
      };
   };
   unsigned int GetFe10PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 10 PZC (pole-zero cancellation) enable (ACDC)
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x108C;
         default:
            throw std::invalid_argument("Function GetFe10PzcEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE11_AMPLIFIER1_COMP_EN
   unsigned int GetFe11Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 amplifier 1 compensation enable (COMP1)
            return BitExtractControl(0x108C, 0x00000020, 5);
         default:
            throw std::invalid_argument("Function GetFe11Amplifier1CompEn() not defined for this board version");
      };
   };
   void SetFe11Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 amplifier 1 compensation enable (COMP1)
            return SetRegMask(0x108C, 0x00000020, 5, value);
         default:
            throw std::invalid_argument("Function SetFe11Amplifier1CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe11Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 amplifier 1 compensation enable (COMP1)
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x108C;
         default:
            throw std::invalid_argument("Function GetFe11Amplifier1CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE11_AMPLIFIER1_EN
   unsigned int GetFe11Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 amplifier 1 enable (gain: 10) (OP1)
            return BitExtractControl(0x108C, 0x00000010, 4);
         default:
            throw std::invalid_argument("Function GetFe11Amplifier1En() not defined for this board version");
      };
   };
   void SetFe11Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 amplifier 1 enable (gain: 10) (OP1)
            return SetRegMask(0x108C, 0x00000010, 4, value);
         default:
            throw std::invalid_argument("Function SetFe11Amplifier1En() not defined for this board version");
      };
   };
   unsigned int GetFe11Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 amplifier 1 enable (gain: 10) (OP1)
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x108C;
         default:
            throw std::invalid_argument("Function GetFe11Amplifier1EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE11_AMPLIFIER2_COMP_EN
   unsigned int GetFe11Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 amplifier 2 compensation enable (COMP2)
            return BitExtractControl(0x108C, 0x00000080, 7);
         default:
            throw std::invalid_argument("Function GetFe11Amplifier2CompEn() not defined for this board version");
      };
   };
   void SetFe11Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 amplifier 2 compensation enable (COMP2)
            return SetRegMask(0x108C, 0x00000080, 7, value);
         default:
            throw std::invalid_argument("Function SetFe11Amplifier2CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe11Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 amplifier 2 compensation enable (COMP2)
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x108C;
         default:
            throw std::invalid_argument("Function GetFe11Amplifier2CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE11_AMPLIFIER2_EN
   unsigned int GetFe11Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 amplifier 2 enable (gain: 10) (OP2)
            return BitExtractControl(0x108C, 0x00000040, 6);
         default:
            throw std::invalid_argument("Function GetFe11Amplifier2En() not defined for this board version");
      };
   };
   void SetFe11Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 amplifier 2 enable (gain: 10) (OP2)
            return SetRegMask(0x108C, 0x00000040, 6, value);
         default:
            throw std::invalid_argument("Function SetFe11Amplifier2En() not defined for this board version");
      };
   };
   unsigned int GetFe11Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 amplifier 2 enable (gain: 10) (OP2)
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x108C;
         default:
            throw std::invalid_argument("Function GetFe11Amplifier2EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE11_ATTENUATION
   unsigned int GetFe11Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return BitExtractControl(0x108C, 0x0000000C, 2);
         default:
            throw std::invalid_argument("Function GetFe11Attenuation() not defined for this board version");
      };
   };
   void SetFe11Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return SetRegMask(0x108C, 0x0000000C, 2, value);
         default:
            throw std::invalid_argument("Function SetFe11Attenuation() not defined for this board version");
      };
   };
   unsigned int GetFe11AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x108C;
         default:
            throw std::invalid_argument("Function GetFe11AttenuationLoc() not defined for this board version");
      };
   };

   // Bit(s) FE11_MUX
   unsigned int GetFe11Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return BitExtractControl(0x108C, 0x00000003, 0);
         default:
            throw std::invalid_argument("Function GetFe11Mux() not defined for this board version");
      };
   };
   void SetFe11Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return SetRegMask(0x108C, 0x00000003, 0, value);
         default:
            throw std::invalid_argument("Function SetFe11Mux() not defined for this board version");
      };
   };
   unsigned int GetFe11MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x108C;
         default:
            throw std::invalid_argument("Function GetFe11MuxLoc() not defined for this board version");
      };
   };

   // Bit(s) FE11_PZC_EN
   unsigned int GetFe11PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 PZC (pole-zero cancellation) enable (ACDC)
            return BitExtractControl(0x108C, 0x00000100, 8);
         default:
            throw std::invalid_argument("Function GetFe11PzcEn() not defined for this board version");
      };
   };
   void SetFe11PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 PZC (pole-zero cancellation) enable (ACDC)
            return SetRegMask(0x108C, 0x00000100, 8, value);
         default:
            throw std::invalid_argument("Function SetFe11PzcEn() not defined for this board version");
      };
   };
   unsigned int GetFe11PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 11 PZC (pole-zero cancellation) enable (ACDC)
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x108C;
         default:
            throw std::invalid_argument("Function GetFe11PzcEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE12_AMPLIFIER1_COMP_EN
   unsigned int GetFe12Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 amplifier 1 compensation enable (COMP1)
            return BitExtractControl(0x1090, 0x00200000, 21);
         default:
            throw std::invalid_argument("Function GetFe12Amplifier1CompEn() not defined for this board version");
      };
   };
   void SetFe12Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 amplifier 1 compensation enable (COMP1)
            return SetRegMask(0x1090, 0x00200000, 21, value);
         default:
            throw std::invalid_argument("Function SetFe12Amplifier1CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe12Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 amplifier 1 compensation enable (COMP1)
            if(BitMask) *BitMask = 0x00200000;
            if(BitOfs) *BitOfs = 21;
            return 0x1090;
         default:
            throw std::invalid_argument("Function GetFe12Amplifier1CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE12_AMPLIFIER1_EN
   unsigned int GetFe12Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 amplifier 1 enable (gain: 10) (OP1)
            return BitExtractControl(0x1090, 0x00100000, 20);
         default:
            throw std::invalid_argument("Function GetFe12Amplifier1En() not defined for this board version");
      };
   };
   void SetFe12Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 amplifier 1 enable (gain: 10) (OP1)
            return SetRegMask(0x1090, 0x00100000, 20, value);
         default:
            throw std::invalid_argument("Function SetFe12Amplifier1En() not defined for this board version");
      };
   };
   unsigned int GetFe12Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 amplifier 1 enable (gain: 10) (OP1)
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x1090;
         default:
            throw std::invalid_argument("Function GetFe12Amplifier1EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE12_AMPLIFIER2_COMP_EN
   unsigned int GetFe12Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 amplifier 2 compensation enable (COMP2)
            return BitExtractControl(0x1090, 0x00800000, 23);
         default:
            throw std::invalid_argument("Function GetFe12Amplifier2CompEn() not defined for this board version");
      };
   };
   void SetFe12Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 amplifier 2 compensation enable (COMP2)
            return SetRegMask(0x1090, 0x00800000, 23, value);
         default:
            throw std::invalid_argument("Function SetFe12Amplifier2CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe12Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 amplifier 2 compensation enable (COMP2)
            if(BitMask) *BitMask = 0x00800000;
            if(BitOfs) *BitOfs = 23;
            return 0x1090;
         default:
            throw std::invalid_argument("Function GetFe12Amplifier2CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE12_AMPLIFIER2_EN
   unsigned int GetFe12Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 amplifier 2 enable (gain: 10) (OP2)
            return BitExtractControl(0x1090, 0x00400000, 22);
         default:
            throw std::invalid_argument("Function GetFe12Amplifier2En() not defined for this board version");
      };
   };
   void SetFe12Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 amplifier 2 enable (gain: 10) (OP2)
            return SetRegMask(0x1090, 0x00400000, 22, value);
         default:
            throw std::invalid_argument("Function SetFe12Amplifier2En() not defined for this board version");
      };
   };
   unsigned int GetFe12Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 amplifier 2 enable (gain: 10) (OP2)
            if(BitMask) *BitMask = 0x00400000;
            if(BitOfs) *BitOfs = 22;
            return 0x1090;
         default:
            throw std::invalid_argument("Function GetFe12Amplifier2EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE12_ATTENUATION
   unsigned int GetFe12Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return BitExtractControl(0x1090, 0x000C0000, 18);
         default:
            throw std::invalid_argument("Function GetFe12Attenuation() not defined for this board version");
      };
   };
   void SetFe12Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return SetRegMask(0x1090, 0x000C0000, 18, value);
         default:
            throw std::invalid_argument("Function SetFe12Attenuation() not defined for this board version");
      };
   };
   unsigned int GetFe12AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x1090;
         default:
            throw std::invalid_argument("Function GetFe12AttenuationLoc() not defined for this board version");
      };
   };

   // Bit(s) FE12_MUX
   unsigned int GetFe12Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return BitExtractControl(0x1090, 0x00030000, 16);
         default:
            throw std::invalid_argument("Function GetFe12Mux() not defined for this board version");
      };
   };
   void SetFe12Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return SetRegMask(0x1090, 0x00030000, 16, value);
         default:
            throw std::invalid_argument("Function SetFe12Mux() not defined for this board version");
      };
   };
   unsigned int GetFe12MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x1090;
         default:
            throw std::invalid_argument("Function GetFe12MuxLoc() not defined for this board version");
      };
   };

   // Bit(s) FE12_PZC_EN
   unsigned int GetFe12PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 PZC (pole-zero cancellation) enable (ACDC)
            return BitExtractControl(0x1090, 0x01000000, 24);
         default:
            throw std::invalid_argument("Function GetFe12PzcEn() not defined for this board version");
      };
   };
   void SetFe12PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 PZC (pole-zero cancellation) enable (ACDC)
            return SetRegMask(0x1090, 0x01000000, 24, value);
         default:
            throw std::invalid_argument("Function SetFe12PzcEn() not defined for this board version");
      };
   };
   unsigned int GetFe12PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 12 PZC (pole-zero cancellation) enable (ACDC)
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1090;
         default:
            throw std::invalid_argument("Function GetFe12PzcEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE13_AMPLIFIER1_COMP_EN
   unsigned int GetFe13Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 amplifier 1 compensation enable (COMP1)
            return BitExtractControl(0x1090, 0x00000020, 5);
         default:
            throw std::invalid_argument("Function GetFe13Amplifier1CompEn() not defined for this board version");
      };
   };
   void SetFe13Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 amplifier 1 compensation enable (COMP1)
            return SetRegMask(0x1090, 0x00000020, 5, value);
         default:
            throw std::invalid_argument("Function SetFe13Amplifier1CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe13Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 amplifier 1 compensation enable (COMP1)
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x1090;
         default:
            throw std::invalid_argument("Function GetFe13Amplifier1CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE13_AMPLIFIER1_EN
   unsigned int GetFe13Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 amplifier 1 enable (gain: 10) (OP1)
            return BitExtractControl(0x1090, 0x00000010, 4);
         default:
            throw std::invalid_argument("Function GetFe13Amplifier1En() not defined for this board version");
      };
   };
   void SetFe13Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 amplifier 1 enable (gain: 10) (OP1)
            return SetRegMask(0x1090, 0x00000010, 4, value);
         default:
            throw std::invalid_argument("Function SetFe13Amplifier1En() not defined for this board version");
      };
   };
   unsigned int GetFe13Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 amplifier 1 enable (gain: 10) (OP1)
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x1090;
         default:
            throw std::invalid_argument("Function GetFe13Amplifier1EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE13_AMPLIFIER2_COMP_EN
   unsigned int GetFe13Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 amplifier 2 compensation enable (COMP2)
            return BitExtractControl(0x1090, 0x00000080, 7);
         default:
            throw std::invalid_argument("Function GetFe13Amplifier2CompEn() not defined for this board version");
      };
   };
   void SetFe13Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 amplifier 2 compensation enable (COMP2)
            return SetRegMask(0x1090, 0x00000080, 7, value);
         default:
            throw std::invalid_argument("Function SetFe13Amplifier2CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe13Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 amplifier 2 compensation enable (COMP2)
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x1090;
         default:
            throw std::invalid_argument("Function GetFe13Amplifier2CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE13_AMPLIFIER2_EN
   unsigned int GetFe13Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 amplifier 2 enable (gain: 10) (OP2)
            return BitExtractControl(0x1090, 0x00000040, 6);
         default:
            throw std::invalid_argument("Function GetFe13Amplifier2En() not defined for this board version");
      };
   };
   void SetFe13Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 amplifier 2 enable (gain: 10) (OP2)
            return SetRegMask(0x1090, 0x00000040, 6, value);
         default:
            throw std::invalid_argument("Function SetFe13Amplifier2En() not defined for this board version");
      };
   };
   unsigned int GetFe13Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 amplifier 2 enable (gain: 10) (OP2)
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x1090;
         default:
            throw std::invalid_argument("Function GetFe13Amplifier2EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE13_ATTENUATION
   unsigned int GetFe13Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return BitExtractControl(0x1090, 0x0000000C, 2);
         default:
            throw std::invalid_argument("Function GetFe13Attenuation() not defined for this board version");
      };
   };
   void SetFe13Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return SetRegMask(0x1090, 0x0000000C, 2, value);
         default:
            throw std::invalid_argument("Function SetFe13Attenuation() not defined for this board version");
      };
   };
   unsigned int GetFe13AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x1090;
         default:
            throw std::invalid_argument("Function GetFe13AttenuationLoc() not defined for this board version");
      };
   };

   // Bit(s) FE13_MUX
   unsigned int GetFe13Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return BitExtractControl(0x1090, 0x00000003, 0);
         default:
            throw std::invalid_argument("Function GetFe13Mux() not defined for this board version");
      };
   };
   void SetFe13Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return SetRegMask(0x1090, 0x00000003, 0, value);
         default:
            throw std::invalid_argument("Function SetFe13Mux() not defined for this board version");
      };
   };
   unsigned int GetFe13MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x1090;
         default:
            throw std::invalid_argument("Function GetFe13MuxLoc() not defined for this board version");
      };
   };

   // Bit(s) FE13_PZC_EN
   unsigned int GetFe13PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 PZC (pole-zero cancellation) enable (ACDC)
            return BitExtractControl(0x1090, 0x00000100, 8);
         default:
            throw std::invalid_argument("Function GetFe13PzcEn() not defined for this board version");
      };
   };
   void SetFe13PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 PZC (pole-zero cancellation) enable (ACDC)
            return SetRegMask(0x1090, 0x00000100, 8, value);
         default:
            throw std::invalid_argument("Function SetFe13PzcEn() not defined for this board version");
      };
   };
   unsigned int GetFe13PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 13 PZC (pole-zero cancellation) enable (ACDC)
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1090;
         default:
            throw std::invalid_argument("Function GetFe13PzcEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE14_AMPLIFIER1_COMP_EN
   unsigned int GetFe14Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 amplifier 1 compensation enable (COMP1)
            return BitExtractControl(0x1094, 0x00200000, 21);
         default:
            throw std::invalid_argument("Function GetFe14Amplifier1CompEn() not defined for this board version");
      };
   };
   void SetFe14Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 amplifier 1 compensation enable (COMP1)
            return SetRegMask(0x1094, 0x00200000, 21, value);
         default:
            throw std::invalid_argument("Function SetFe14Amplifier1CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe14Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 amplifier 1 compensation enable (COMP1)
            if(BitMask) *BitMask = 0x00200000;
            if(BitOfs) *BitOfs = 21;
            return 0x1094;
         default:
            throw std::invalid_argument("Function GetFe14Amplifier1CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE14_AMPLIFIER1_EN
   unsigned int GetFe14Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 amplifier 1 enable (gain: 10) (OP1)
            return BitExtractControl(0x1094, 0x00100000, 20);
         default:
            throw std::invalid_argument("Function GetFe14Amplifier1En() not defined for this board version");
      };
   };
   void SetFe14Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 amplifier 1 enable (gain: 10) (OP1)
            return SetRegMask(0x1094, 0x00100000, 20, value);
         default:
            throw std::invalid_argument("Function SetFe14Amplifier1En() not defined for this board version");
      };
   };
   unsigned int GetFe14Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 amplifier 1 enable (gain: 10) (OP1)
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x1094;
         default:
            throw std::invalid_argument("Function GetFe14Amplifier1EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE14_AMPLIFIER2_COMP_EN
   unsigned int GetFe14Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 amplifier 2 compensation enable (COMP2)
            return BitExtractControl(0x1094, 0x00800000, 23);
         default:
            throw std::invalid_argument("Function GetFe14Amplifier2CompEn() not defined for this board version");
      };
   };
   void SetFe14Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 amplifier 2 compensation enable (COMP2)
            return SetRegMask(0x1094, 0x00800000, 23, value);
         default:
            throw std::invalid_argument("Function SetFe14Amplifier2CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe14Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 amplifier 2 compensation enable (COMP2)
            if(BitMask) *BitMask = 0x00800000;
            if(BitOfs) *BitOfs = 23;
            return 0x1094;
         default:
            throw std::invalid_argument("Function GetFe14Amplifier2CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE14_AMPLIFIER2_EN
   unsigned int GetFe14Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 amplifier 2 enable (gain: 10) (OP2)
            return BitExtractControl(0x1094, 0x00400000, 22);
         default:
            throw std::invalid_argument("Function GetFe14Amplifier2En() not defined for this board version");
      };
   };
   void SetFe14Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 amplifier 2 enable (gain: 10) (OP2)
            return SetRegMask(0x1094, 0x00400000, 22, value);
         default:
            throw std::invalid_argument("Function SetFe14Amplifier2En() not defined for this board version");
      };
   };
   unsigned int GetFe14Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 amplifier 2 enable (gain: 10) (OP2)
            if(BitMask) *BitMask = 0x00400000;
            if(BitOfs) *BitOfs = 22;
            return 0x1094;
         default:
            throw std::invalid_argument("Function GetFe14Amplifier2EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE14_ATTENUATION
   unsigned int GetFe14Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return BitExtractControl(0x1094, 0x000C0000, 18);
         default:
            throw std::invalid_argument("Function GetFe14Attenuation() not defined for this board version");
      };
   };
   void SetFe14Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return SetRegMask(0x1094, 0x000C0000, 18, value);
         default:
            throw std::invalid_argument("Function SetFe14Attenuation() not defined for this board version");
      };
   };
   unsigned int GetFe14AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x1094;
         default:
            throw std::invalid_argument("Function GetFe14AttenuationLoc() not defined for this board version");
      };
   };

   // Bit(s) FE14_MUX
   unsigned int GetFe14Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return BitExtractControl(0x1094, 0x00030000, 16);
         default:
            throw std::invalid_argument("Function GetFe14Mux() not defined for this board version");
      };
   };
   void SetFe14Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return SetRegMask(0x1094, 0x00030000, 16, value);
         default:
            throw std::invalid_argument("Function SetFe14Mux() not defined for this board version");
      };
   };
   unsigned int GetFe14MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x1094;
         default:
            throw std::invalid_argument("Function GetFe14MuxLoc() not defined for this board version");
      };
   };

   // Bit(s) FE14_PZC_EN
   unsigned int GetFe14PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 PZC (pole-zero cancellation) enable (ACDC)
            return BitExtractControl(0x1094, 0x01000000, 24);
         default:
            throw std::invalid_argument("Function GetFe14PzcEn() not defined for this board version");
      };
   };
   void SetFe14PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 PZC (pole-zero cancellation) enable (ACDC)
            return SetRegMask(0x1094, 0x01000000, 24, value);
         default:
            throw std::invalid_argument("Function SetFe14PzcEn() not defined for this board version");
      };
   };
   unsigned int GetFe14PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 14 PZC (pole-zero cancellation) enable (ACDC)
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1094;
         default:
            throw std::invalid_argument("Function GetFe14PzcEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE15_AMPLIFIER1_COMP_EN
   unsigned int GetFe15Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 amplifier 1 compensation enable (COMP1)
            return BitExtractControl(0x1094, 0x00000020, 5);
         default:
            throw std::invalid_argument("Function GetFe15Amplifier1CompEn() not defined for this board version");
      };
   };
   void SetFe15Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 amplifier 1 compensation enable (COMP1)
            return SetRegMask(0x1094, 0x00000020, 5, value);
         default:
            throw std::invalid_argument("Function SetFe15Amplifier1CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe15Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 amplifier 1 compensation enable (COMP1)
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x1094;
         default:
            throw std::invalid_argument("Function GetFe15Amplifier1CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE15_AMPLIFIER1_EN
   unsigned int GetFe15Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 amplifier 1 enable (gain: 10) (OP1)
            return BitExtractControl(0x1094, 0x00000010, 4);
         default:
            throw std::invalid_argument("Function GetFe15Amplifier1En() not defined for this board version");
      };
   };
   void SetFe15Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 amplifier 1 enable (gain: 10) (OP1)
            return SetRegMask(0x1094, 0x00000010, 4, value);
         default:
            throw std::invalid_argument("Function SetFe15Amplifier1En() not defined for this board version");
      };
   };
   unsigned int GetFe15Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 amplifier 1 enable (gain: 10) (OP1)
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x1094;
         default:
            throw std::invalid_argument("Function GetFe15Amplifier1EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE15_AMPLIFIER2_COMP_EN
   unsigned int GetFe15Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 amplifier 2 compensation enable (COMP2)
            return BitExtractControl(0x1094, 0x00000080, 7);
         default:
            throw std::invalid_argument("Function GetFe15Amplifier2CompEn() not defined for this board version");
      };
   };
   void SetFe15Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 amplifier 2 compensation enable (COMP2)
            return SetRegMask(0x1094, 0x00000080, 7, value);
         default:
            throw std::invalid_argument("Function SetFe15Amplifier2CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe15Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 amplifier 2 compensation enable (COMP2)
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x1094;
         default:
            throw std::invalid_argument("Function GetFe15Amplifier2CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE15_AMPLIFIER2_EN
   unsigned int GetFe15Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 amplifier 2 enable (gain: 10) (OP2)
            return BitExtractControl(0x1094, 0x00000040, 6);
         default:
            throw std::invalid_argument("Function GetFe15Amplifier2En() not defined for this board version");
      };
   };
   void SetFe15Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 amplifier 2 enable (gain: 10) (OP2)
            return SetRegMask(0x1094, 0x00000040, 6, value);
         default:
            throw std::invalid_argument("Function SetFe15Amplifier2En() not defined for this board version");
      };
   };
   unsigned int GetFe15Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 amplifier 2 enable (gain: 10) (OP2)
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x1094;
         default:
            throw std::invalid_argument("Function GetFe15Amplifier2EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE15_ATTENUATION
   unsigned int GetFe15Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return BitExtractControl(0x1094, 0x0000000C, 2);
         default:
            throw std::invalid_argument("Function GetFe15Attenuation() not defined for this board version");
      };
   };
   void SetFe15Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return SetRegMask(0x1094, 0x0000000C, 2, value);
         default:
            throw std::invalid_argument("Function SetFe15Attenuation() not defined for this board version");
      };
   };
   unsigned int GetFe15AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x1094;
         default:
            throw std::invalid_argument("Function GetFe15AttenuationLoc() not defined for this board version");
      };
   };

   // Bit(s) FE15_MUX
   unsigned int GetFe15Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return BitExtractControl(0x1094, 0x00000003, 0);
         default:
            throw std::invalid_argument("Function GetFe15Mux() not defined for this board version");
      };
   };
   void SetFe15Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return SetRegMask(0x1094, 0x00000003, 0, value);
         default:
            throw std::invalid_argument("Function SetFe15Mux() not defined for this board version");
      };
   };
   unsigned int GetFe15MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x1094;
         default:
            throw std::invalid_argument("Function GetFe15MuxLoc() not defined for this board version");
      };
   };

   // Bit(s) FE15_PZC_EN
   unsigned int GetFe15PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 PZC (pole-zero cancellation) enable (ACDC)
            return BitExtractControl(0x1094, 0x00000100, 8);
         default:
            throw std::invalid_argument("Function GetFe15PzcEn() not defined for this board version");
      };
   };
   void SetFe15PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 PZC (pole-zero cancellation) enable (ACDC)
            return SetRegMask(0x1094, 0x00000100, 8, value);
         default:
            throw std::invalid_argument("Function SetFe15PzcEn() not defined for this board version");
      };
   };
   unsigned int GetFe15PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 15 PZC (pole-zero cancellation) enable (ACDC)
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1094;
         default:
            throw std::invalid_argument("Function GetFe15PzcEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE1_AMPLIFIER1_COMP_EN
   unsigned int GetFe1Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 amplifier 1 compensation enable (COMP1)
            return BitExtractControl(0x1078, 0x00000020, 5);
         default:
            throw std::invalid_argument("Function GetFe1Amplifier1CompEn() not defined for this board version");
      };
   };
   void SetFe1Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 amplifier 1 compensation enable (COMP1)
            return SetRegMask(0x1078, 0x00000020, 5, value);
         default:
            throw std::invalid_argument("Function SetFe1Amplifier1CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe1Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 amplifier 1 compensation enable (COMP1)
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x1078;
         default:
            throw std::invalid_argument("Function GetFe1Amplifier1CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE1_AMPLIFIER1_EN
   unsigned int GetFe1Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 amplifier 1 enable (gain: 10) (OP1)
            return BitExtractControl(0x1078, 0x00000010, 4);
         default:
            throw std::invalid_argument("Function GetFe1Amplifier1En() not defined for this board version");
      };
   };
   void SetFe1Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 amplifier 1 enable (gain: 10) (OP1)
            return SetRegMask(0x1078, 0x00000010, 4, value);
         default:
            throw std::invalid_argument("Function SetFe1Amplifier1En() not defined for this board version");
      };
   };
   unsigned int GetFe1Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 amplifier 1 enable (gain: 10) (OP1)
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x1078;
         default:
            throw std::invalid_argument("Function GetFe1Amplifier1EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE1_AMPLIFIER2_COMP_EN
   unsigned int GetFe1Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 amplifier 2 compensation enable (COMP2)
            return BitExtractControl(0x1078, 0x00000080, 7);
         default:
            throw std::invalid_argument("Function GetFe1Amplifier2CompEn() not defined for this board version");
      };
   };
   void SetFe1Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 amplifier 2 compensation enable (COMP2)
            return SetRegMask(0x1078, 0x00000080, 7, value);
         default:
            throw std::invalid_argument("Function SetFe1Amplifier2CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe1Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 amplifier 2 compensation enable (COMP2)
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x1078;
         default:
            throw std::invalid_argument("Function GetFe1Amplifier2CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE1_AMPLIFIER2_EN
   unsigned int GetFe1Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 amplifier 2 enable (gain: 10) (OP2)
            return BitExtractControl(0x1078, 0x00000040, 6);
         default:
            throw std::invalid_argument("Function GetFe1Amplifier2En() not defined for this board version");
      };
   };
   void SetFe1Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 amplifier 2 enable (gain: 10) (OP2)
            return SetRegMask(0x1078, 0x00000040, 6, value);
         default:
            throw std::invalid_argument("Function SetFe1Amplifier2En() not defined for this board version");
      };
   };
   unsigned int GetFe1Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 amplifier 2 enable (gain: 10) (OP2)
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x1078;
         default:
            throw std::invalid_argument("Function GetFe1Amplifier2EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE1_ATTENUATION
   unsigned int GetFe1Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return BitExtractControl(0x1078, 0x0000000C, 2);
         default:
            throw std::invalid_argument("Function GetFe1Attenuation() not defined for this board version");
      };
   };
   void SetFe1Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return SetRegMask(0x1078, 0x0000000C, 2, value);
         default:
            throw std::invalid_argument("Function SetFe1Attenuation() not defined for this board version");
      };
   };
   unsigned int GetFe1AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x1078;
         default:
            throw std::invalid_argument("Function GetFe1AttenuationLoc() not defined for this board version");
      };
   };

   // Bit(s) FE1_MUX
   unsigned int GetFe1Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return BitExtractControl(0x1078, 0x00000003, 0);
         default:
            throw std::invalid_argument("Function GetFe1Mux() not defined for this board version");
      };
   };
   void SetFe1Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return SetRegMask(0x1078, 0x00000003, 0, value);
         default:
            throw std::invalid_argument("Function SetFe1Mux() not defined for this board version");
      };
   };
   unsigned int GetFe1MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x1078;
         default:
            throw std::invalid_argument("Function GetFe1MuxLoc() not defined for this board version");
      };
   };

   // Bit(s) FE1_PZC_EN
   unsigned int GetFe1PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 PZC (pole-zero cancellation) enable (ACDC)
            return BitExtractControl(0x1078, 0x00000100, 8);
         default:
            throw std::invalid_argument("Function GetFe1PzcEn() not defined for this board version");
      };
   };
   void SetFe1PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 PZC (pole-zero cancellation) enable (ACDC)
            return SetRegMask(0x1078, 0x00000100, 8, value);
         default:
            throw std::invalid_argument("Function SetFe1PzcEn() not defined for this board version");
      };
   };
   unsigned int GetFe1PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 1 PZC (pole-zero cancellation) enable (ACDC)
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1078;
         default:
            throw std::invalid_argument("Function GetFe1PzcEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE2_AMPLIFIER1_COMP_EN
   unsigned int GetFe2Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 amplifier 1 compensation enable (COMP1)
            return BitExtractControl(0x107C, 0x00200000, 21);
         default:
            throw std::invalid_argument("Function GetFe2Amplifier1CompEn() not defined for this board version");
      };
   };
   void SetFe2Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 amplifier 1 compensation enable (COMP1)
            return SetRegMask(0x107C, 0x00200000, 21, value);
         default:
            throw std::invalid_argument("Function SetFe2Amplifier1CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe2Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 amplifier 1 compensation enable (COMP1)
            if(BitMask) *BitMask = 0x00200000;
            if(BitOfs) *BitOfs = 21;
            return 0x107C;
         default:
            throw std::invalid_argument("Function GetFe2Amplifier1CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE2_AMPLIFIER1_EN
   unsigned int GetFe2Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 amplifier 1 enable (gain: 10) (OP1)
            return BitExtractControl(0x107C, 0x00100000, 20);
         default:
            throw std::invalid_argument("Function GetFe2Amplifier1En() not defined for this board version");
      };
   };
   void SetFe2Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 amplifier 1 enable (gain: 10) (OP1)
            return SetRegMask(0x107C, 0x00100000, 20, value);
         default:
            throw std::invalid_argument("Function SetFe2Amplifier1En() not defined for this board version");
      };
   };
   unsigned int GetFe2Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 amplifier 1 enable (gain: 10) (OP1)
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x107C;
         default:
            throw std::invalid_argument("Function GetFe2Amplifier1EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE2_AMPLIFIER2_COMP_EN
   unsigned int GetFe2Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 amplifier 2 compensation enable (COMP2)
            return BitExtractControl(0x107C, 0x00800000, 23);
         default:
            throw std::invalid_argument("Function GetFe2Amplifier2CompEn() not defined for this board version");
      };
   };
   void SetFe2Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 amplifier 2 compensation enable (COMP2)
            return SetRegMask(0x107C, 0x00800000, 23, value);
         default:
            throw std::invalid_argument("Function SetFe2Amplifier2CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe2Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 amplifier 2 compensation enable (COMP2)
            if(BitMask) *BitMask = 0x00800000;
            if(BitOfs) *BitOfs = 23;
            return 0x107C;
         default:
            throw std::invalid_argument("Function GetFe2Amplifier2CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE2_AMPLIFIER2_EN
   unsigned int GetFe2Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 amplifier 2 enable (gain: 10) (OP2)
            return BitExtractControl(0x107C, 0x00400000, 22);
         default:
            throw std::invalid_argument("Function GetFe2Amplifier2En() not defined for this board version");
      };
   };
   void SetFe2Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 amplifier 2 enable (gain: 10) (OP2)
            return SetRegMask(0x107C, 0x00400000, 22, value);
         default:
            throw std::invalid_argument("Function SetFe2Amplifier2En() not defined for this board version");
      };
   };
   unsigned int GetFe2Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 amplifier 2 enable (gain: 10) (OP2)
            if(BitMask) *BitMask = 0x00400000;
            if(BitOfs) *BitOfs = 22;
            return 0x107C;
         default:
            throw std::invalid_argument("Function GetFe2Amplifier2EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE2_ATTENUATION
   unsigned int GetFe2Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return BitExtractControl(0x107C, 0x000C0000, 18);
         default:
            throw std::invalid_argument("Function GetFe2Attenuation() not defined for this board version");
      };
   };
   void SetFe2Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return SetRegMask(0x107C, 0x000C0000, 18, value);
         default:
            throw std::invalid_argument("Function SetFe2Attenuation() not defined for this board version");
      };
   };
   unsigned int GetFe2AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x107C;
         default:
            throw std::invalid_argument("Function GetFe2AttenuationLoc() not defined for this board version");
      };
   };

   // Bit(s) FE2_MUX
   unsigned int GetFe2Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return BitExtractControl(0x107C, 0x00030000, 16);
         default:
            throw std::invalid_argument("Function GetFe2Mux() not defined for this board version");
      };
   };
   void SetFe2Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return SetRegMask(0x107C, 0x00030000, 16, value);
         default:
            throw std::invalid_argument("Function SetFe2Mux() not defined for this board version");
      };
   };
   unsigned int GetFe2MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x107C;
         default:
            throw std::invalid_argument("Function GetFe2MuxLoc() not defined for this board version");
      };
   };

   // Bit(s) FE2_PZC_EN
   unsigned int GetFe2PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 PZC (pole-zero cancellation) enable (ACDC)
            return BitExtractControl(0x107C, 0x01000000, 24);
         default:
            throw std::invalid_argument("Function GetFe2PzcEn() not defined for this board version");
      };
   };
   void SetFe2PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 PZC (pole-zero cancellation) enable (ACDC)
            return SetRegMask(0x107C, 0x01000000, 24, value);
         default:
            throw std::invalid_argument("Function SetFe2PzcEn() not defined for this board version");
      };
   };
   unsigned int GetFe2PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 2 PZC (pole-zero cancellation) enable (ACDC)
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x107C;
         default:
            throw std::invalid_argument("Function GetFe2PzcEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE3_AMPLIFIER1_COMP_EN
   unsigned int GetFe3Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 amplifier 1 compensation enable (COMP1)
            return BitExtractControl(0x107C, 0x00000020, 5);
         default:
            throw std::invalid_argument("Function GetFe3Amplifier1CompEn() not defined for this board version");
      };
   };
   void SetFe3Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 amplifier 1 compensation enable (COMP1)
            return SetRegMask(0x107C, 0x00000020, 5, value);
         default:
            throw std::invalid_argument("Function SetFe3Amplifier1CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe3Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 amplifier 1 compensation enable (COMP1)
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x107C;
         default:
            throw std::invalid_argument("Function GetFe3Amplifier1CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE3_AMPLIFIER1_EN
   unsigned int GetFe3Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 amplifier 1 enable (gain: 10) (OP1)
            return BitExtractControl(0x107C, 0x00000010, 4);
         default:
            throw std::invalid_argument("Function GetFe3Amplifier1En() not defined for this board version");
      };
   };
   void SetFe3Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 amplifier 1 enable (gain: 10) (OP1)
            return SetRegMask(0x107C, 0x00000010, 4, value);
         default:
            throw std::invalid_argument("Function SetFe3Amplifier1En() not defined for this board version");
      };
   };
   unsigned int GetFe3Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 amplifier 1 enable (gain: 10) (OP1)
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x107C;
         default:
            throw std::invalid_argument("Function GetFe3Amplifier1EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE3_AMPLIFIER2_COMP_EN
   unsigned int GetFe3Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 amplifier 2 compensation enable (COMP2)
            return BitExtractControl(0x107C, 0x00000080, 7);
         default:
            throw std::invalid_argument("Function GetFe3Amplifier2CompEn() not defined for this board version");
      };
   };
   void SetFe3Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 amplifier 2 compensation enable (COMP2)
            return SetRegMask(0x107C, 0x00000080, 7, value);
         default:
            throw std::invalid_argument("Function SetFe3Amplifier2CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe3Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 amplifier 2 compensation enable (COMP2)
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x107C;
         default:
            throw std::invalid_argument("Function GetFe3Amplifier2CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE3_AMPLIFIER2_EN
   unsigned int GetFe3Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 amplifier 2 enable (gain: 10) (OP2)
            return BitExtractControl(0x107C, 0x00000040, 6);
         default:
            throw std::invalid_argument("Function GetFe3Amplifier2En() not defined for this board version");
      };
   };
   void SetFe3Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 amplifier 2 enable (gain: 10) (OP2)
            return SetRegMask(0x107C, 0x00000040, 6, value);
         default:
            throw std::invalid_argument("Function SetFe3Amplifier2En() not defined for this board version");
      };
   };
   unsigned int GetFe3Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 amplifier 2 enable (gain: 10) (OP2)
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x107C;
         default:
            throw std::invalid_argument("Function GetFe3Amplifier2EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE3_ATTENUATION
   unsigned int GetFe3Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return BitExtractControl(0x107C, 0x0000000C, 2);
         default:
            throw std::invalid_argument("Function GetFe3Attenuation() not defined for this board version");
      };
   };
   void SetFe3Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return SetRegMask(0x107C, 0x0000000C, 2, value);
         default:
            throw std::invalid_argument("Function SetFe3Attenuation() not defined for this board version");
      };
   };
   unsigned int GetFe3AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x107C;
         default:
            throw std::invalid_argument("Function GetFe3AttenuationLoc() not defined for this board version");
      };
   };

   // Bit(s) FE3_MUX
   unsigned int GetFe3Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return BitExtractControl(0x107C, 0x00000003, 0);
         default:
            throw std::invalid_argument("Function GetFe3Mux() not defined for this board version");
      };
   };
   void SetFe3Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return SetRegMask(0x107C, 0x00000003, 0, value);
         default:
            throw std::invalid_argument("Function SetFe3Mux() not defined for this board version");
      };
   };
   unsigned int GetFe3MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x107C;
         default:
            throw std::invalid_argument("Function GetFe3MuxLoc() not defined for this board version");
      };
   };

   // Bit(s) FE3_PZC_EN
   unsigned int GetFe3PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 PZC (pole-zero cancellation) enable (ACDC)
            return BitExtractControl(0x107C, 0x00000100, 8);
         default:
            throw std::invalid_argument("Function GetFe3PzcEn() not defined for this board version");
      };
   };
   void SetFe3PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 PZC (pole-zero cancellation) enable (ACDC)
            return SetRegMask(0x107C, 0x00000100, 8, value);
         default:
            throw std::invalid_argument("Function SetFe3PzcEn() not defined for this board version");
      };
   };
   unsigned int GetFe3PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 3 PZC (pole-zero cancellation) enable (ACDC)
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x107C;
         default:
            throw std::invalid_argument("Function GetFe3PzcEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE4_AMPLIFIER1_COMP_EN
   unsigned int GetFe4Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 amplifier 1 compensation enable (COMP1)
            return BitExtractControl(0x1080, 0x00200000, 21);
         default:
            throw std::invalid_argument("Function GetFe4Amplifier1CompEn() not defined for this board version");
      };
   };
   void SetFe4Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 amplifier 1 compensation enable (COMP1)
            return SetRegMask(0x1080, 0x00200000, 21, value);
         default:
            throw std::invalid_argument("Function SetFe4Amplifier1CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe4Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 amplifier 1 compensation enable (COMP1)
            if(BitMask) *BitMask = 0x00200000;
            if(BitOfs) *BitOfs = 21;
            return 0x1080;
         default:
            throw std::invalid_argument("Function GetFe4Amplifier1CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE4_AMPLIFIER1_EN
   unsigned int GetFe4Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 amplifier 1 enable (gain: 10) (OP1)
            return BitExtractControl(0x1080, 0x00100000, 20);
         default:
            throw std::invalid_argument("Function GetFe4Amplifier1En() not defined for this board version");
      };
   };
   void SetFe4Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 amplifier 1 enable (gain: 10) (OP1)
            return SetRegMask(0x1080, 0x00100000, 20, value);
         default:
            throw std::invalid_argument("Function SetFe4Amplifier1En() not defined for this board version");
      };
   };
   unsigned int GetFe4Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 amplifier 1 enable (gain: 10) (OP1)
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x1080;
         default:
            throw std::invalid_argument("Function GetFe4Amplifier1EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE4_AMPLIFIER2_COMP_EN
   unsigned int GetFe4Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 amplifier 2 compensation enable (COMP2)
            return BitExtractControl(0x1080, 0x00800000, 23);
         default:
            throw std::invalid_argument("Function GetFe4Amplifier2CompEn() not defined for this board version");
      };
   };
   void SetFe4Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 amplifier 2 compensation enable (COMP2)
            return SetRegMask(0x1080, 0x00800000, 23, value);
         default:
            throw std::invalid_argument("Function SetFe4Amplifier2CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe4Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 amplifier 2 compensation enable (COMP2)
            if(BitMask) *BitMask = 0x00800000;
            if(BitOfs) *BitOfs = 23;
            return 0x1080;
         default:
            throw std::invalid_argument("Function GetFe4Amplifier2CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE4_AMPLIFIER2_EN
   unsigned int GetFe4Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 amplifier 2 enable (gain: 10) (OP2)
            return BitExtractControl(0x1080, 0x00400000, 22);
         default:
            throw std::invalid_argument("Function GetFe4Amplifier2En() not defined for this board version");
      };
   };
   void SetFe4Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 amplifier 2 enable (gain: 10) (OP2)
            return SetRegMask(0x1080, 0x00400000, 22, value);
         default:
            throw std::invalid_argument("Function SetFe4Amplifier2En() not defined for this board version");
      };
   };
   unsigned int GetFe4Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 amplifier 2 enable (gain: 10) (OP2)
            if(BitMask) *BitMask = 0x00400000;
            if(BitOfs) *BitOfs = 22;
            return 0x1080;
         default:
            throw std::invalid_argument("Function GetFe4Amplifier2EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE4_ATTENUATION
   unsigned int GetFe4Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return BitExtractControl(0x1080, 0x000C0000, 18);
         default:
            throw std::invalid_argument("Function GetFe4Attenuation() not defined for this board version");
      };
   };
   void SetFe4Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return SetRegMask(0x1080, 0x000C0000, 18, value);
         default:
            throw std::invalid_argument("Function SetFe4Attenuation() not defined for this board version");
      };
   };
   unsigned int GetFe4AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x1080;
         default:
            throw std::invalid_argument("Function GetFe4AttenuationLoc() not defined for this board version");
      };
   };

   // Bit(s) FE4_MUX
   unsigned int GetFe4Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return BitExtractControl(0x1080, 0x00030000, 16);
         default:
            throw std::invalid_argument("Function GetFe4Mux() not defined for this board version");
      };
   };
   void SetFe4Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return SetRegMask(0x1080, 0x00030000, 16, value);
         default:
            throw std::invalid_argument("Function SetFe4Mux() not defined for this board version");
      };
   };
   unsigned int GetFe4MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x1080;
         default:
            throw std::invalid_argument("Function GetFe4MuxLoc() not defined for this board version");
      };
   };

   // Bit(s) FE4_PZC_EN
   unsigned int GetFe4PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 PZC (pole-zero cancellation) enable (ACDC)
            return BitExtractControl(0x1080, 0x01000000, 24);
         default:
            throw std::invalid_argument("Function GetFe4PzcEn() not defined for this board version");
      };
   };
   void SetFe4PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 PZC (pole-zero cancellation) enable (ACDC)
            return SetRegMask(0x1080, 0x01000000, 24, value);
         default:
            throw std::invalid_argument("Function SetFe4PzcEn() not defined for this board version");
      };
   };
   unsigned int GetFe4PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 4 PZC (pole-zero cancellation) enable (ACDC)
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1080;
         default:
            throw std::invalid_argument("Function GetFe4PzcEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE5_AMPLIFIER1_COMP_EN
   unsigned int GetFe5Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 amplifier 1 compensation enable (COMP1)
            return BitExtractControl(0x1080, 0x00000020, 5);
         default:
            throw std::invalid_argument("Function GetFe5Amplifier1CompEn() not defined for this board version");
      };
   };
   void SetFe5Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 amplifier 1 compensation enable (COMP1)
            return SetRegMask(0x1080, 0x00000020, 5, value);
         default:
            throw std::invalid_argument("Function SetFe5Amplifier1CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe5Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 amplifier 1 compensation enable (COMP1)
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x1080;
         default:
            throw std::invalid_argument("Function GetFe5Amplifier1CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE5_AMPLIFIER1_EN
   unsigned int GetFe5Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 amplifier 1 enable (gain: 10) (OP1)
            return BitExtractControl(0x1080, 0x00000010, 4);
         default:
            throw std::invalid_argument("Function GetFe5Amplifier1En() not defined for this board version");
      };
   };
   void SetFe5Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 amplifier 1 enable (gain: 10) (OP1)
            return SetRegMask(0x1080, 0x00000010, 4, value);
         default:
            throw std::invalid_argument("Function SetFe5Amplifier1En() not defined for this board version");
      };
   };
   unsigned int GetFe5Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 amplifier 1 enable (gain: 10) (OP1)
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x1080;
         default:
            throw std::invalid_argument("Function GetFe5Amplifier1EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE5_AMPLIFIER2_COMP_EN
   unsigned int GetFe5Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 amplifier 2 compensation enable (COMP2)
            return BitExtractControl(0x1080, 0x00000080, 7);
         default:
            throw std::invalid_argument("Function GetFe5Amplifier2CompEn() not defined for this board version");
      };
   };
   void SetFe5Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 amplifier 2 compensation enable (COMP2)
            return SetRegMask(0x1080, 0x00000080, 7, value);
         default:
            throw std::invalid_argument("Function SetFe5Amplifier2CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe5Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 amplifier 2 compensation enable (COMP2)
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x1080;
         default:
            throw std::invalid_argument("Function GetFe5Amplifier2CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE5_AMPLIFIER2_EN
   unsigned int GetFe5Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 amplifier 2 enable (gain: 10) (OP2)
            return BitExtractControl(0x1080, 0x00000040, 6);
         default:
            throw std::invalid_argument("Function GetFe5Amplifier2En() not defined for this board version");
      };
   };
   void SetFe5Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 amplifier 2 enable (gain: 10) (OP2)
            return SetRegMask(0x1080, 0x00000040, 6, value);
         default:
            throw std::invalid_argument("Function SetFe5Amplifier2En() not defined for this board version");
      };
   };
   unsigned int GetFe5Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 amplifier 2 enable (gain: 10) (OP2)
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x1080;
         default:
            throw std::invalid_argument("Function GetFe5Amplifier2EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE5_ATTENUATION
   unsigned int GetFe5Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return BitExtractControl(0x1080, 0x0000000C, 2);
         default:
            throw std::invalid_argument("Function GetFe5Attenuation() not defined for this board version");
      };
   };
   void SetFe5Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return SetRegMask(0x1080, 0x0000000C, 2, value);
         default:
            throw std::invalid_argument("Function SetFe5Attenuation() not defined for this board version");
      };
   };
   unsigned int GetFe5AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x1080;
         default:
            throw std::invalid_argument("Function GetFe5AttenuationLoc() not defined for this board version");
      };
   };

   // Bit(s) FE5_MUX
   unsigned int GetFe5Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return BitExtractControl(0x1080, 0x00000003, 0);
         default:
            throw std::invalid_argument("Function GetFe5Mux() not defined for this board version");
      };
   };
   void SetFe5Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return SetRegMask(0x1080, 0x00000003, 0, value);
         default:
            throw std::invalid_argument("Function SetFe5Mux() not defined for this board version");
      };
   };
   unsigned int GetFe5MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x1080;
         default:
            throw std::invalid_argument("Function GetFe5MuxLoc() not defined for this board version");
      };
   };

   // Bit(s) FE5_PZC_EN
   unsigned int GetFe5PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 PZC (pole-zero cancellation) enable (ACDC)
            return BitExtractControl(0x1080, 0x00000100, 8);
         default:
            throw std::invalid_argument("Function GetFe5PzcEn() not defined for this board version");
      };
   };
   void SetFe5PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 PZC (pole-zero cancellation) enable (ACDC)
            return SetRegMask(0x1080, 0x00000100, 8, value);
         default:
            throw std::invalid_argument("Function SetFe5PzcEn() not defined for this board version");
      };
   };
   unsigned int GetFe5PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 5 PZC (pole-zero cancellation) enable (ACDC)
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1080;
         default:
            throw std::invalid_argument("Function GetFe5PzcEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE6_AMPLIFIER1_COMP_EN
   unsigned int GetFe6Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 amplifier 1 compensation enable (COMP1)
            return BitExtractControl(0x1084, 0x00200000, 21);
         default:
            throw std::invalid_argument("Function GetFe6Amplifier1CompEn() not defined for this board version");
      };
   };
   void SetFe6Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 amplifier 1 compensation enable (COMP1)
            return SetRegMask(0x1084, 0x00200000, 21, value);
         default:
            throw std::invalid_argument("Function SetFe6Amplifier1CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe6Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 amplifier 1 compensation enable (COMP1)
            if(BitMask) *BitMask = 0x00200000;
            if(BitOfs) *BitOfs = 21;
            return 0x1084;
         default:
            throw std::invalid_argument("Function GetFe6Amplifier1CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE6_AMPLIFIER1_EN
   unsigned int GetFe6Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 amplifier 1 enable (gain: 10) (OP1)
            return BitExtractControl(0x1084, 0x00100000, 20);
         default:
            throw std::invalid_argument("Function GetFe6Amplifier1En() not defined for this board version");
      };
   };
   void SetFe6Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 amplifier 1 enable (gain: 10) (OP1)
            return SetRegMask(0x1084, 0x00100000, 20, value);
         default:
            throw std::invalid_argument("Function SetFe6Amplifier1En() not defined for this board version");
      };
   };
   unsigned int GetFe6Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 amplifier 1 enable (gain: 10) (OP1)
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x1084;
         default:
            throw std::invalid_argument("Function GetFe6Amplifier1EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE6_AMPLIFIER2_COMP_EN
   unsigned int GetFe6Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 amplifier 2 compensation enable (COMP2)
            return BitExtractControl(0x1084, 0x00800000, 23);
         default:
            throw std::invalid_argument("Function GetFe6Amplifier2CompEn() not defined for this board version");
      };
   };
   void SetFe6Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 amplifier 2 compensation enable (COMP2)
            return SetRegMask(0x1084, 0x00800000, 23, value);
         default:
            throw std::invalid_argument("Function SetFe6Amplifier2CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe6Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 amplifier 2 compensation enable (COMP2)
            if(BitMask) *BitMask = 0x00800000;
            if(BitOfs) *BitOfs = 23;
            return 0x1084;
         default:
            throw std::invalid_argument("Function GetFe6Amplifier2CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE6_AMPLIFIER2_EN
   unsigned int GetFe6Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 amplifier 2 enable (gain: 10) (OP2)
            return BitExtractControl(0x1084, 0x00400000, 22);
         default:
            throw std::invalid_argument("Function GetFe6Amplifier2En() not defined for this board version");
      };
   };
   void SetFe6Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 amplifier 2 enable (gain: 10) (OP2)
            return SetRegMask(0x1084, 0x00400000, 22, value);
         default:
            throw std::invalid_argument("Function SetFe6Amplifier2En() not defined for this board version");
      };
   };
   unsigned int GetFe6Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 amplifier 2 enable (gain: 10) (OP2)
            if(BitMask) *BitMask = 0x00400000;
            if(BitOfs) *BitOfs = 22;
            return 0x1084;
         default:
            throw std::invalid_argument("Function GetFe6Amplifier2EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE6_ATTENUATION
   unsigned int GetFe6Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return BitExtractControl(0x1084, 0x000C0000, 18);
         default:
            throw std::invalid_argument("Function GetFe6Attenuation() not defined for this board version");
      };
   };
   void SetFe6Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return SetRegMask(0x1084, 0x000C0000, 18, value);
         default:
            throw std::invalid_argument("Function SetFe6Attenuation() not defined for this board version");
      };
   };
   unsigned int GetFe6AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x1084;
         default:
            throw std::invalid_argument("Function GetFe6AttenuationLoc() not defined for this board version");
      };
   };

   // Bit(s) FE6_MUX
   unsigned int GetFe6Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return BitExtractControl(0x1084, 0x00030000, 16);
         default:
            throw std::invalid_argument("Function GetFe6Mux() not defined for this board version");
      };
   };
   void SetFe6Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return SetRegMask(0x1084, 0x00030000, 16, value);
         default:
            throw std::invalid_argument("Function SetFe6Mux() not defined for this board version");
      };
   };
   unsigned int GetFe6MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x1084;
         default:
            throw std::invalid_argument("Function GetFe6MuxLoc() not defined for this board version");
      };
   };

   // Bit(s) FE6_PZC_EN
   unsigned int GetFe6PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 PZC (pole-zero cancellation) enable (ACDC)
            return BitExtractControl(0x1084, 0x01000000, 24);
         default:
            throw std::invalid_argument("Function GetFe6PzcEn() not defined for this board version");
      };
   };
   void SetFe6PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 PZC (pole-zero cancellation) enable (ACDC)
            return SetRegMask(0x1084, 0x01000000, 24, value);
         default:
            throw std::invalid_argument("Function SetFe6PzcEn() not defined for this board version");
      };
   };
   unsigned int GetFe6PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 6 PZC (pole-zero cancellation) enable (ACDC)
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1084;
         default:
            throw std::invalid_argument("Function GetFe6PzcEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE7_AMPLIFIER1_COMP_EN
   unsigned int GetFe7Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 amplifier 1 compensation enable (COMP1)
            return BitExtractControl(0x1084, 0x00000020, 5);
         default:
            throw std::invalid_argument("Function GetFe7Amplifier1CompEn() not defined for this board version");
      };
   };
   void SetFe7Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 amplifier 1 compensation enable (COMP1)
            return SetRegMask(0x1084, 0x00000020, 5, value);
         default:
            throw std::invalid_argument("Function SetFe7Amplifier1CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe7Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 amplifier 1 compensation enable (COMP1)
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x1084;
         default:
            throw std::invalid_argument("Function GetFe7Amplifier1CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE7_AMPLIFIER1_EN
   unsigned int GetFe7Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 amplifier 1 enable (gain: 10) (OP1)
            return BitExtractControl(0x1084, 0x00000010, 4);
         default:
            throw std::invalid_argument("Function GetFe7Amplifier1En() not defined for this board version");
      };
   };
   void SetFe7Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 amplifier 1 enable (gain: 10) (OP1)
            return SetRegMask(0x1084, 0x00000010, 4, value);
         default:
            throw std::invalid_argument("Function SetFe7Amplifier1En() not defined for this board version");
      };
   };
   unsigned int GetFe7Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 amplifier 1 enable (gain: 10) (OP1)
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x1084;
         default:
            throw std::invalid_argument("Function GetFe7Amplifier1EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE7_AMPLIFIER2_COMP_EN
   unsigned int GetFe7Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 amplifier 2 compensation enable (COMP2)
            return BitExtractControl(0x1084, 0x00000080, 7);
         default:
            throw std::invalid_argument("Function GetFe7Amplifier2CompEn() not defined for this board version");
      };
   };
   void SetFe7Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 amplifier 2 compensation enable (COMP2)
            return SetRegMask(0x1084, 0x00000080, 7, value);
         default:
            throw std::invalid_argument("Function SetFe7Amplifier2CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe7Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 amplifier 2 compensation enable (COMP2)
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x1084;
         default:
            throw std::invalid_argument("Function GetFe7Amplifier2CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE7_AMPLIFIER2_EN
   unsigned int GetFe7Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 amplifier 2 enable (gain: 10) (OP2)
            return BitExtractControl(0x1084, 0x00000040, 6);
         default:
            throw std::invalid_argument("Function GetFe7Amplifier2En() not defined for this board version");
      };
   };
   void SetFe7Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 amplifier 2 enable (gain: 10) (OP2)
            return SetRegMask(0x1084, 0x00000040, 6, value);
         default:
            throw std::invalid_argument("Function SetFe7Amplifier2En() not defined for this board version");
      };
   };
   unsigned int GetFe7Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 amplifier 2 enable (gain: 10) (OP2)
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x1084;
         default:
            throw std::invalid_argument("Function GetFe7Amplifier2EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE7_ATTENUATION
   unsigned int GetFe7Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return BitExtractControl(0x1084, 0x0000000C, 2);
         default:
            throw std::invalid_argument("Function GetFe7Attenuation() not defined for this board version");
      };
   };
   void SetFe7Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return SetRegMask(0x1084, 0x0000000C, 2, value);
         default:
            throw std::invalid_argument("Function SetFe7Attenuation() not defined for this board version");
      };
   };
   unsigned int GetFe7AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x1084;
         default:
            throw std::invalid_argument("Function GetFe7AttenuationLoc() not defined for this board version");
      };
   };

   // Bit(s) FE7_MUX
   unsigned int GetFe7Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return BitExtractControl(0x1084, 0x00000003, 0);
         default:
            throw std::invalid_argument("Function GetFe7Mux() not defined for this board version");
      };
   };
   void SetFe7Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return SetRegMask(0x1084, 0x00000003, 0, value);
         default:
            throw std::invalid_argument("Function SetFe7Mux() not defined for this board version");
      };
   };
   unsigned int GetFe7MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x1084;
         default:
            throw std::invalid_argument("Function GetFe7MuxLoc() not defined for this board version");
      };
   };

   // Bit(s) FE7_PZC_EN
   unsigned int GetFe7PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 PZC (pole-zero cancellation) enable (ACDC)
            return BitExtractControl(0x1084, 0x00000100, 8);
         default:
            throw std::invalid_argument("Function GetFe7PzcEn() not defined for this board version");
      };
   };
   void SetFe7PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 PZC (pole-zero cancellation) enable (ACDC)
            return SetRegMask(0x1084, 0x00000100, 8, value);
         default:
            throw std::invalid_argument("Function SetFe7PzcEn() not defined for this board version");
      };
   };
   unsigned int GetFe7PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 7 PZC (pole-zero cancellation) enable (ACDC)
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1084;
         default:
            throw std::invalid_argument("Function GetFe7PzcEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE8_AMPLIFIER1_COMP_EN
   unsigned int GetFe8Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 amplifier 1 compensation enable (COMP1)
            return BitExtractControl(0x1088, 0x00200000, 21);
         default:
            throw std::invalid_argument("Function GetFe8Amplifier1CompEn() not defined for this board version");
      };
   };
   void SetFe8Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 amplifier 1 compensation enable (COMP1)
            return SetRegMask(0x1088, 0x00200000, 21, value);
         default:
            throw std::invalid_argument("Function SetFe8Amplifier1CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe8Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 amplifier 1 compensation enable (COMP1)
            if(BitMask) *BitMask = 0x00200000;
            if(BitOfs) *BitOfs = 21;
            return 0x1088;
         default:
            throw std::invalid_argument("Function GetFe8Amplifier1CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE8_AMPLIFIER1_EN
   unsigned int GetFe8Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 amplifier 1 enable (gain: 10) (OP1)
            return BitExtractControl(0x1088, 0x00100000, 20);
         default:
            throw std::invalid_argument("Function GetFe8Amplifier1En() not defined for this board version");
      };
   };
   void SetFe8Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 amplifier 1 enable (gain: 10) (OP1)
            return SetRegMask(0x1088, 0x00100000, 20, value);
         default:
            throw std::invalid_argument("Function SetFe8Amplifier1En() not defined for this board version");
      };
   };
   unsigned int GetFe8Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 amplifier 1 enable (gain: 10) (OP1)
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x1088;
         default:
            throw std::invalid_argument("Function GetFe8Amplifier1EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE8_AMPLIFIER2_COMP_EN
   unsigned int GetFe8Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 amplifier 2 compensation enable (COMP2)
            return BitExtractControl(0x1088, 0x00800000, 23);
         default:
            throw std::invalid_argument("Function GetFe8Amplifier2CompEn() not defined for this board version");
      };
   };
   void SetFe8Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 amplifier 2 compensation enable (COMP2)
            return SetRegMask(0x1088, 0x00800000, 23, value);
         default:
            throw std::invalid_argument("Function SetFe8Amplifier2CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe8Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 amplifier 2 compensation enable (COMP2)
            if(BitMask) *BitMask = 0x00800000;
            if(BitOfs) *BitOfs = 23;
            return 0x1088;
         default:
            throw std::invalid_argument("Function GetFe8Amplifier2CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE8_AMPLIFIER2_EN
   unsigned int GetFe8Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 amplifier 2 enable (gain: 10) (OP2)
            return BitExtractControl(0x1088, 0x00400000, 22);
         default:
            throw std::invalid_argument("Function GetFe8Amplifier2En() not defined for this board version");
      };
   };
   void SetFe8Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 amplifier 2 enable (gain: 10) (OP2)
            return SetRegMask(0x1088, 0x00400000, 22, value);
         default:
            throw std::invalid_argument("Function SetFe8Amplifier2En() not defined for this board version");
      };
   };
   unsigned int GetFe8Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 amplifier 2 enable (gain: 10) (OP2)
            if(BitMask) *BitMask = 0x00400000;
            if(BitOfs) *BitOfs = 22;
            return 0x1088;
         default:
            throw std::invalid_argument("Function GetFe8Amplifier2EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE8_ATTENUATION
   unsigned int GetFe8Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return BitExtractControl(0x1088, 0x000C0000, 18);
         default:
            throw std::invalid_argument("Function GetFe8Attenuation() not defined for this board version");
      };
   };
   void SetFe8Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return SetRegMask(0x1088, 0x000C0000, 18, value);
         default:
            throw std::invalid_argument("Function SetFe8Attenuation() not defined for this board version");
      };
   };
   unsigned int GetFe8AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x1088;
         default:
            throw std::invalid_argument("Function GetFe8AttenuationLoc() not defined for this board version");
      };
   };

   // Bit(s) FE8_MUX
   unsigned int GetFe8Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return BitExtractControl(0x1088, 0x00030000, 16);
         default:
            throw std::invalid_argument("Function GetFe8Mux() not defined for this board version");
      };
   };
   void SetFe8Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return SetRegMask(0x1088, 0x00030000, 16, value);
         default:
            throw std::invalid_argument("Function SetFe8Mux() not defined for this board version");
      };
   };
   unsigned int GetFe8MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x1088;
         default:
            throw std::invalid_argument("Function GetFe8MuxLoc() not defined for this board version");
      };
   };

   // Bit(s) FE8_PZC_EN
   unsigned int GetFe8PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 PZC (pole-zero cancellation) enable (ACDC)
            return BitExtractControl(0x1088, 0x01000000, 24);
         default:
            throw std::invalid_argument("Function GetFe8PzcEn() not defined for this board version");
      };
   };
   void SetFe8PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 PZC (pole-zero cancellation) enable (ACDC)
            return SetRegMask(0x1088, 0x01000000, 24, value);
         default:
            throw std::invalid_argument("Function SetFe8PzcEn() not defined for this board version");
      };
   };
   unsigned int GetFe8PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 8 PZC (pole-zero cancellation) enable (ACDC)
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1088;
         default:
            throw std::invalid_argument("Function GetFe8PzcEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE9_AMPLIFIER1_COMP_EN
   unsigned int GetFe9Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 amplifier 1 compensation enable (COMP1)
            return BitExtractControl(0x1088, 0x00000020, 5);
         default:
            throw std::invalid_argument("Function GetFe9Amplifier1CompEn() not defined for this board version");
      };
   };
   void SetFe9Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 amplifier 1 compensation enable (COMP1)
            return SetRegMask(0x1088, 0x00000020, 5, value);
         default:
            throw std::invalid_argument("Function SetFe9Amplifier1CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe9Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 amplifier 1 compensation enable (COMP1)
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x1088;
         default:
            throw std::invalid_argument("Function GetFe9Amplifier1CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE9_AMPLIFIER1_EN
   unsigned int GetFe9Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 amplifier 1 enable (gain: 10) (OP1)
            return BitExtractControl(0x1088, 0x00000010, 4);
         default:
            throw std::invalid_argument("Function GetFe9Amplifier1En() not defined for this board version");
      };
   };
   void SetFe9Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 amplifier 1 enable (gain: 10) (OP1)
            return SetRegMask(0x1088, 0x00000010, 4, value);
         default:
            throw std::invalid_argument("Function SetFe9Amplifier1En() not defined for this board version");
      };
   };
   unsigned int GetFe9Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 amplifier 1 enable (gain: 10) (OP1)
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x1088;
         default:
            throw std::invalid_argument("Function GetFe9Amplifier1EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE9_AMPLIFIER2_COMP_EN
   unsigned int GetFe9Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 amplifier 2 compensation enable (COMP2)
            return BitExtractControl(0x1088, 0x00000080, 7);
         default:
            throw std::invalid_argument("Function GetFe9Amplifier2CompEn() not defined for this board version");
      };
   };
   void SetFe9Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 amplifier 2 compensation enable (COMP2)
            return SetRegMask(0x1088, 0x00000080, 7, value);
         default:
            throw std::invalid_argument("Function SetFe9Amplifier2CompEn() not defined for this board version");
      };
   };
   unsigned int GetFe9Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 amplifier 2 compensation enable (COMP2)
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x1088;
         default:
            throw std::invalid_argument("Function GetFe9Amplifier2CompEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE9_AMPLIFIER2_EN
   unsigned int GetFe9Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 amplifier 2 enable (gain: 10) (OP2)
            return BitExtractControl(0x1088, 0x00000040, 6);
         default:
            throw std::invalid_argument("Function GetFe9Amplifier2En() not defined for this board version");
      };
   };
   void SetFe9Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 amplifier 2 enable (gain: 10) (OP2)
            return SetRegMask(0x1088, 0x00000040, 6, value);
         default:
            throw std::invalid_argument("Function SetFe9Amplifier2En() not defined for this board version");
      };
   };
   unsigned int GetFe9Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 amplifier 2 enable (gain: 10) (OP2)
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x1088;
         default:
            throw std::invalid_argument("Function GetFe9Amplifier2EnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE9_ATTENUATION
   unsigned int GetFe9Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return BitExtractControl(0x1088, 0x0000000C, 2);
         default:
            throw std::invalid_argument("Function GetFe9Attenuation() not defined for this board version");
      };
   };
   void SetFe9Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            return SetRegMask(0x1088, 0x0000000C, 2, value);
         default:
            throw std::invalid_argument("Function SetFe9Attenuation() not defined for this board version");
      };
   };
   unsigned int GetFe9AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x1088;
         default:
            throw std::invalid_argument("Function GetFe9AttenuationLoc() not defined for this board version");
      };
   };

   // Bit(s) FE9_MUX
   unsigned int GetFe9Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return BitExtractControl(0x1088, 0x00000003, 0);
         default:
            throw std::invalid_argument("Function GetFe9Mux() not defined for this board version");
      };
   };
   void SetFe9Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            return SetRegMask(0x1088, 0x00000003, 0, value);
         default:
            throw std::invalid_argument("Function SetFe9Mux() not defined for this board version");
      };
   };
   unsigned int GetFe9MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x1088;
         default:
            throw std::invalid_argument("Function GetFe9MuxLoc() not defined for this board version");
      };
   };

   // Bit(s) FE9_PZC_EN
   unsigned int GetFe9PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 PZC (pole-zero cancellation) enable (ACDC)
            return BitExtractControl(0x1088, 0x00000100, 8);
         default:
            throw std::invalid_argument("Function GetFe9PzcEn() not defined for this board version");
      };
   };
   void SetFe9PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 PZC (pole-zero cancellation) enable (ACDC)
            return SetRegMask(0x1088, 0x00000100, 8, value);
         default:
            throw std::invalid_argument("Function SetFe9PzcEn() not defined for this board version");
      };
   };
   unsigned int GetFe9PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Frontend channel 9 PZC (pole-zero cancellation) enable (ACDC)
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1088;
         default:
            throw std::invalid_argument("Function GetFe9PzcEnLoc() not defined for this board version");
      };
   };

   // Bit(s) FE_0_MOD
   unsigned int GetFe0Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 0 register modified flags
            return BitExtractStatus(0x0150, 0xC0000000, 30);
         case 9:
            // Frontend channel 0 register modified flags
            return BitExtractStatus(0x014C, 0xC0000000, 30);
         default:
            throw std::invalid_argument("Function GetFe0Mod() not defined for this board version");
      };
   };
   unsigned int GetFe0ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 0 register modified flags
            if(BitMask) *BitMask = 0xC0000000;
            if(BitOfs) *BitOfs = 30;
            return 0x0150;
         case 9:
            // Frontend channel 0 register modified flags
            if(BitMask) *BitMask = 0xC0000000;
            if(BitOfs) *BitOfs = 30;
            return 0x014C;
         default:
            throw std::invalid_argument("Function GetFe0ModLoc() not defined for this board version");
      };
   };

   // Bit(s) FE_10_MOD
   unsigned int GetFe10Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 10 register modified flags
            return BitExtractStatus(0x0150, 0x00000C00, 10);
         case 9:
            // Frontend channel 10 register modified flags
            return BitExtractStatus(0x014C, 0x00000C00, 10);
         default:
            throw std::invalid_argument("Function GetFe10Mod() not defined for this board version");
      };
   };
   unsigned int GetFe10ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 10 register modified flags
            if(BitMask) *BitMask = 0x00000C00;
            if(BitOfs) *BitOfs = 10;
            return 0x0150;
         case 9:
            // Frontend channel 10 register modified flags
            if(BitMask) *BitMask = 0x00000C00;
            if(BitOfs) *BitOfs = 10;
            return 0x014C;
         default:
            throw std::invalid_argument("Function GetFe10ModLoc() not defined for this board version");
      };
   };

   // Bit(s) FE_11_MOD
   unsigned int GetFe11Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 11 register modified flags
            return BitExtractStatus(0x0150, 0x00000300, 8);
         case 9:
            // Frontend channel 11 register modified flags
            return BitExtractStatus(0x014C, 0x00000300, 8);
         default:
            throw std::invalid_argument("Function GetFe11Mod() not defined for this board version");
      };
   };
   unsigned int GetFe11ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 11 register modified flags
            if(BitMask) *BitMask = 0x00000300;
            if(BitOfs) *BitOfs = 8;
            return 0x0150;
         case 9:
            // Frontend channel 11 register modified flags
            if(BitMask) *BitMask = 0x00000300;
            if(BitOfs) *BitOfs = 8;
            return 0x014C;
         default:
            throw std::invalid_argument("Function GetFe11ModLoc() not defined for this board version");
      };
   };

   // Bit(s) FE_12_MOD
   unsigned int GetFe12Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 12 register modified flags
            return BitExtractStatus(0x0150, 0x000000C0, 6);
         case 9:
            // Frontend channel 12 register modified flags
            return BitExtractStatus(0x014C, 0x000000C0, 6);
         default:
            throw std::invalid_argument("Function GetFe12Mod() not defined for this board version");
      };
   };
   unsigned int GetFe12ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 12 register modified flags
            if(BitMask) *BitMask = 0x000000C0;
            if(BitOfs) *BitOfs = 6;
            return 0x0150;
         case 9:
            // Frontend channel 12 register modified flags
            if(BitMask) *BitMask = 0x000000C0;
            if(BitOfs) *BitOfs = 6;
            return 0x014C;
         default:
            throw std::invalid_argument("Function GetFe12ModLoc() not defined for this board version");
      };
   };

   // Bit(s) FE_13_MOD
   unsigned int GetFe13Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 13 register modified flags
            return BitExtractStatus(0x0150, 0x00000030, 4);
         case 9:
            // Frontend channel 13 register modified flags
            return BitExtractStatus(0x014C, 0x00000030, 4);
         default:
            throw std::invalid_argument("Function GetFe13Mod() not defined for this board version");
      };
   };
   unsigned int GetFe13ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 13 register modified flags
            if(BitMask) *BitMask = 0x00000030;
            if(BitOfs) *BitOfs = 4;
            return 0x0150;
         case 9:
            // Frontend channel 13 register modified flags
            if(BitMask) *BitMask = 0x00000030;
            if(BitOfs) *BitOfs = 4;
            return 0x014C;
         default:
            throw std::invalid_argument("Function GetFe13ModLoc() not defined for this board version");
      };
   };

   // Bit(s) FE_14_MOD
   unsigned int GetFe14Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 14 register modified flags
            return BitExtractStatus(0x0150, 0x0000000C, 2);
         case 9:
            // Frontend channel 14 register modified flags
            return BitExtractStatus(0x014C, 0x0000000C, 2);
         default:
            throw std::invalid_argument("Function GetFe14Mod() not defined for this board version");
      };
   };
   unsigned int GetFe14ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 14 register modified flags
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x0150;
         case 9:
            // Frontend channel 14 register modified flags
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x014C;
         default:
            throw std::invalid_argument("Function GetFe14ModLoc() not defined for this board version");
      };
   };

   // Bit(s) FE_15_MOD
   unsigned int GetFe15Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 15 register modified flags
            return BitExtractStatus(0x0150, 0x00000003, 0);
         case 9:
            // Frontend channel 15 register modified flags
            return BitExtractStatus(0x014C, 0x00000003, 0);
         default:
            throw std::invalid_argument("Function GetFe15Mod() not defined for this board version");
      };
   };
   unsigned int GetFe15ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 15 register modified flags
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x0150;
         case 9:
            // Frontend channel 15 register modified flags
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x014C;
         default:
            throw std::invalid_argument("Function GetFe15ModLoc() not defined for this board version");
      };
   };

   // Bit(s) FE_1_MOD
   unsigned int GetFe1Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 1 register modified flags
            return BitExtractStatus(0x0150, 0x30000000, 28);
         case 9:
            // Frontend channel 1 register modified flags
            return BitExtractStatus(0x014C, 0x30000000, 28);
         default:
            throw std::invalid_argument("Function GetFe1Mod() not defined for this board version");
      };
   };
   unsigned int GetFe1ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 1 register modified flags
            if(BitMask) *BitMask = 0x30000000;
            if(BitOfs) *BitOfs = 28;
            return 0x0150;
         case 9:
            // Frontend channel 1 register modified flags
            if(BitMask) *BitMask = 0x30000000;
            if(BitOfs) *BitOfs = 28;
            return 0x014C;
         default:
            throw std::invalid_argument("Function GetFe1ModLoc() not defined for this board version");
      };
   };

   // Bit(s) FE_2_MOD
   unsigned int GetFe2Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 2 register modified flags
            return BitExtractStatus(0x0150, 0x0C000000, 26);
         case 9:
            // Frontend channel 2 register modified flags
            return BitExtractStatus(0x014C, 0x0C000000, 26);
         default:
            throw std::invalid_argument("Function GetFe2Mod() not defined for this board version");
      };
   };
   unsigned int GetFe2ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 2 register modified flags
            if(BitMask) *BitMask = 0x0C000000;
            if(BitOfs) *BitOfs = 26;
            return 0x0150;
         case 9:
            // Frontend channel 2 register modified flags
            if(BitMask) *BitMask = 0x0C000000;
            if(BitOfs) *BitOfs = 26;
            return 0x014C;
         default:
            throw std::invalid_argument("Function GetFe2ModLoc() not defined for this board version");
      };
   };

   // Bit(s) FE_3_MOD
   unsigned int GetFe3Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 3 register modified flags
            return BitExtractStatus(0x0150, 0x03000000, 24);
         case 9:
            // Frontend channel 3 register modified flags
            return BitExtractStatus(0x014C, 0x03000000, 24);
         default:
            throw std::invalid_argument("Function GetFe3Mod() not defined for this board version");
      };
   };
   unsigned int GetFe3ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 3 register modified flags
            if(BitMask) *BitMask = 0x03000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0150;
         case 9:
            // Frontend channel 3 register modified flags
            if(BitMask) *BitMask = 0x03000000;
            if(BitOfs) *BitOfs = 24;
            return 0x014C;
         default:
            throw std::invalid_argument("Function GetFe3ModLoc() not defined for this board version");
      };
   };

   // Bit(s) FE_4_MOD
   unsigned int GetFe4Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 4 register modified flags
            return BitExtractStatus(0x0150, 0x00C00000, 22);
         case 9:
            // Frontend channel 4 register modified flags
            return BitExtractStatus(0x014C, 0x00C00000, 22);
         default:
            throw std::invalid_argument("Function GetFe4Mod() not defined for this board version");
      };
   };
   unsigned int GetFe4ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 4 register modified flags
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x0150;
         case 9:
            // Frontend channel 4 register modified flags
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x014C;
         default:
            throw std::invalid_argument("Function GetFe4ModLoc() not defined for this board version");
      };
   };

   // Bit(s) FE_5_MOD
   unsigned int GetFe5Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 5 register modified flags
            return BitExtractStatus(0x0150, 0x00300000, 20);
         case 9:
            // Frontend channel 5 register modified flags
            return BitExtractStatus(0x014C, 0x00300000, 20);
         default:
            throw std::invalid_argument("Function GetFe5Mod() not defined for this board version");
      };
   };
   unsigned int GetFe5ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 5 register modified flags
            if(BitMask) *BitMask = 0x00300000;
            if(BitOfs) *BitOfs = 20;
            return 0x0150;
         case 9:
            // Frontend channel 5 register modified flags
            if(BitMask) *BitMask = 0x00300000;
            if(BitOfs) *BitOfs = 20;
            return 0x014C;
         default:
            throw std::invalid_argument("Function GetFe5ModLoc() not defined for this board version");
      };
   };

   // Bit(s) FE_6_MOD
   unsigned int GetFe6Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 6 register modified flags
            return BitExtractStatus(0x0150, 0x000C0000, 18);
         case 9:
            // Frontend channel 6 register modified flags
            return BitExtractStatus(0x014C, 0x000C0000, 18);
         default:
            throw std::invalid_argument("Function GetFe6Mod() not defined for this board version");
      };
   };
   unsigned int GetFe6ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 6 register modified flags
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x0150;
         case 9:
            // Frontend channel 6 register modified flags
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x014C;
         default:
            throw std::invalid_argument("Function GetFe6ModLoc() not defined for this board version");
      };
   };

   // Bit(s) FE_7_MOD
   unsigned int GetFe7Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 7 register modified flags
            return BitExtractStatus(0x0150, 0x00030000, 16);
         case 9:
            // Frontend channel 7 register modified flags
            return BitExtractStatus(0x014C, 0x00030000, 16);
         default:
            throw std::invalid_argument("Function GetFe7Mod() not defined for this board version");
      };
   };
   unsigned int GetFe7ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 7 register modified flags
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x0150;
         case 9:
            // Frontend channel 7 register modified flags
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x014C;
         default:
            throw std::invalid_argument("Function GetFe7ModLoc() not defined for this board version");
      };
   };

   // Bit(s) FE_8_MOD
   unsigned int GetFe8Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 8 register modified flags
            return BitExtractStatus(0x0150, 0x0000C000, 14);
         case 9:
            // Frontend channel 8 register modified flags
            return BitExtractStatus(0x014C, 0x0000C000, 14);
         default:
            throw std::invalid_argument("Function GetFe8Mod() not defined for this board version");
      };
   };
   unsigned int GetFe8ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 8 register modified flags
            if(BitMask) *BitMask = 0x0000C000;
            if(BitOfs) *BitOfs = 14;
            return 0x0150;
         case 9:
            // Frontend channel 8 register modified flags
            if(BitMask) *BitMask = 0x0000C000;
            if(BitOfs) *BitOfs = 14;
            return 0x014C;
         default:
            throw std::invalid_argument("Function GetFe8ModLoc() not defined for this board version");
      };
   };

   // Bit(s) FE_9_MOD
   unsigned int GetFe9Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 9 register modified flags
            return BitExtractStatus(0x0150, 0x00003000, 12);
         case 9:
            // Frontend channel 9 register modified flags
            return BitExtractStatus(0x014C, 0x00003000, 12);
         default:
            throw std::invalid_argument("Function GetFe9Mod() not defined for this board version");
      };
   };
   unsigned int GetFe9ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Frontend channel 9 register modified flags
            if(BitMask) *BitMask = 0x00003000;
            if(BitOfs) *BitOfs = 12;
            return 0x0150;
         case 9:
            // Frontend channel 9 register modified flags
            if(BitMask) *BitMask = 0x00003000;
            if(BitOfs) *BitOfs = 12;
            return 0x014C;
         default:
            throw std::invalid_argument("Function GetFe9ModLoc() not defined for this board version");
      };
   };

   // Bit(s) FE_POWER
   unsigned int GetFePower()
   {
      switch(this->mVersion)
      {
         case 9:
            // Frontend Power (0=Power OFF, 1=Power ON)
            return BitExtractControl(0x1004, 0x00000800, 11);
         default:
            throw std::invalid_argument("Function GetFePower() not defined for this board version");
      };
   };
   void SetFePower(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            // Frontend Power (0=Power OFF, 1=Power ON)
            return SetRegMask(0x1004, 0x00000800, 11, value);
         default:
            throw std::invalid_argument("Function SetFePower() not defined for this board version");
      };
   };
   unsigned int GetFePowerLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Frontend Power (0=Power OFF, 1=Power ON)
            if(BitMask) *BitMask = 0x00000800;
            if(BitOfs) *BitOfs = 11;
            return 0x1004;
         default:
            throw std::invalid_argument("Function GetFePowerLoc() not defined for this board version");
      };
   };

   // Bit(s) FIRST_PKG_DLY
   unsigned int GetFirstPkgDly()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Delay of first data packet of an event (resolution 1.6us)
            return BitExtractControl(0x1018, 0xFFFC0000, 18);
         default:
            throw std::invalid_argument("Function GetFirstPkgDly() not defined for this board version");
      };
   };
   void SetFirstPkgDly(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Delay of first data packet of an event (resolution 1.6us)
            return SetRegMask(0x1018, 0xFFFC0000, 18, value);
         default:
            throw std::invalid_argument("Function SetFirstPkgDly() not defined for this board version");
      };
   };
   unsigned int GetFirstPkgDlyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Delay of first data packet of an event (resolution 1.6us)
            if(BitMask) *BitMask = 0xFFFC0000;
            if(BitOfs) *BitOfs = 18;
            return 0x1018;
         default:
            throw std::invalid_argument("Function GetFirstPkgDlyLoc() not defined for this board version");
      };
   };

   // Bit(s) FLASH_SEL
   unsigned int GetFlashSel()
   {
      switch(this->mVersion)
      {
         case 8:
            // SPI Flash select from backplane (inverted = high active)
            return BitExtractStatus(0x0028, 0x00000200, 9);
         default:
            throw std::invalid_argument("Function GetFlashSel() not defined for this board version");
      };
   };
   unsigned int GetFlashSelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // SPI Flash select from backplane (inverted = high active)
            if(BitMask) *BitMask = 0x00000200;
            if(BitOfs) *BitOfs = 9;
            return 0x0028;
         default:
            throw std::invalid_argument("Function GetFlashSelLoc() not defined for this board version");
      };
   };

   // Bit(s) FW_BUILD_DAY
   unsigned int GetFwBuildDay()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Day of the firmware build
            return BitExtractStatus(0x0008, 0x000000FF, 0);
         default:
            throw std::invalid_argument("Function GetFwBuildDay() not defined for this board version");
      };
   };
   unsigned int GetFwBuildDayLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Day of the firmware build
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x0008;
         default:
            throw std::invalid_argument("Function GetFwBuildDayLoc() not defined for this board version");
      };
   };

   // Bit(s) FW_BUILD_HOUR
   unsigned int GetFwBuildHour()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Hour of the firmware build
            return BitExtractStatus(0x000C, 0x00FF0000, 16);
         default:
            throw std::invalid_argument("Function GetFwBuildHour() not defined for this board version");
      };
   };
   unsigned int GetFwBuildHourLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Hour of the firmware build
            if(BitMask) *BitMask = 0x00FF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x000C;
         default:
            throw std::invalid_argument("Function GetFwBuildHourLoc() not defined for this board version");
      };
   };

   // Bit(s) FW_BUILD_MINUTE
   unsigned int GetFwBuildMinute()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Minute of the firmware build
            return BitExtractStatus(0x000C, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetFwBuildMinute() not defined for this board version");
      };
   };
   unsigned int GetFwBuildMinuteLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Minute of the firmware build
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x000C;
         default:
            throw std::invalid_argument("Function GetFwBuildMinuteLoc() not defined for this board version");
      };
   };

   // Bit(s) FW_BUILD_MONTH
   unsigned int GetFwBuildMonth()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Month of the firmware build
            return BitExtractStatus(0x0008, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetFwBuildMonth() not defined for this board version");
      };
   };
   unsigned int GetFwBuildMonthLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Month of the firmware build
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x0008;
         default:
            throw std::invalid_argument("Function GetFwBuildMonthLoc() not defined for this board version");
      };
   };

   // Bit(s) FW_BUILD_SECOND
   unsigned int GetFwBuildSecond()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Second of the firmware build
            return BitExtractStatus(0x000C, 0x000000FF, 0);
         default:
            throw std::invalid_argument("Function GetFwBuildSecond() not defined for this board version");
      };
   };
   unsigned int GetFwBuildSecondLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Second of the firmware build
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x000C;
         default:
            throw std::invalid_argument("Function GetFwBuildSecondLoc() not defined for this board version");
      };
   };

   // Bit(s) FW_BUILD_YEAR
   unsigned int GetFwBuildYear()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Year of the firmware build
            return BitExtractStatus(0x0008, 0xFFFF0000, 16);
         default:
            throw std::invalid_argument("Function GetFwBuildYear() not defined for this board version");
      };
   };
   unsigned int GetFwBuildYearLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Year of the firmware build
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0008;
         default:
            throw std::invalid_argument("Function GetFwBuildYearLoc() not defined for this board version");
      };
   };

   // Bit(s) FW_COMPAT_LEVEL
   unsigned int GetFwCompatLevel()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Firmware compatibility level
            return BitExtractStatus(0x000C, 0xFF000000, 24);
         default:
            throw std::invalid_argument("Function GetFwCompatLevel() not defined for this board version");
      };
   };
   unsigned int GetFwCompatLevelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Firmware compatibility level
            if(BitMask) *BitMask = 0xFF000000;
            if(BitOfs) *BitOfs = 24;
            return 0x000C;
         default:
            throw std::invalid_argument("Function GetFwCompatLevelLoc() not defined for this board version");
      };
   };

   // Bit(s) FW_GIT_HASH_TAG
   unsigned int GetFwGitHashTag()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Hash tag of the firmware commit in the GIT repository
            return BitExtractStatus(0x0018, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetFwGitHashTag() not defined for this board version");
      };
   };
   unsigned int GetFwGitHashTagLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Hash tag of the firmware commit in the GIT repository
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0018;
         default:
            throw std::invalid_argument("Function GetFwGitHashTagLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_BOARD_PLUGGED
   unsigned int GetHvBoardPlugged()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // HV board is currently plugged (1) or unplugged (0)
            return BitExtractStatus(0x0028, 0x00000002, 1);
         default:
            throw std::invalid_argument("Function GetHvBoardPlugged() not defined for this board version");
      };
   };
   unsigned int GetHvBoardPluggedLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // HV board is currently plugged (1) or unplugged (0)
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x0028;
         default:
            throw std::invalid_argument("Function GetHvBoardPluggedLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_I_MEAS_0
   unsigned int GetHvIMeas0()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            return BitExtractStatus(0x004C, 0xFFFFFFFF, 0);
         case 9:
            // Float value (i_meas)
            return BitExtractStatus(0x0048, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvIMeas0() not defined for this board version");
      };
   };
   unsigned int GetHvIMeas0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x004C;
         case 9:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0048;
         default:
            throw std::invalid_argument("Function GetHvIMeas0Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_I_MEAS_1
   unsigned int GetHvIMeas1()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            return BitExtractStatus(0x0050, 0xFFFFFFFF, 0);
         case 9:
            // Float value (i_meas)
            return BitExtractStatus(0x004C, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvIMeas1() not defined for this board version");
      };
   };
   unsigned int GetHvIMeas1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0050;
         case 9:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x004C;
         default:
            throw std::invalid_argument("Function GetHvIMeas1Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_I_MEAS_10
   unsigned int GetHvIMeas10()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            return BitExtractStatus(0x0074, 0xFFFFFFFF, 0);
         case 9:
            // Float value (i_meas)
            return BitExtractStatus(0x0070, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvIMeas10() not defined for this board version");
      };
   };
   unsigned int GetHvIMeas10Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0074;
         case 9:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0070;
         default:
            throw std::invalid_argument("Function GetHvIMeas10Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_I_MEAS_11
   unsigned int GetHvIMeas11()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            return BitExtractStatus(0x0078, 0xFFFFFFFF, 0);
         case 9:
            // Float value (i_meas)
            return BitExtractStatus(0x0074, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvIMeas11() not defined for this board version");
      };
   };
   unsigned int GetHvIMeas11Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0078;
         case 9:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0074;
         default:
            throw std::invalid_argument("Function GetHvIMeas11Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_I_MEAS_12
   unsigned int GetHvIMeas12()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            return BitExtractStatus(0x007C, 0xFFFFFFFF, 0);
         case 9:
            // Float value (i_meas)
            return BitExtractStatus(0x0078, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvIMeas12() not defined for this board version");
      };
   };
   unsigned int GetHvIMeas12Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x007C;
         case 9:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0078;
         default:
            throw std::invalid_argument("Function GetHvIMeas12Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_I_MEAS_13
   unsigned int GetHvIMeas13()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            return BitExtractStatus(0x0080, 0xFFFFFFFF, 0);
         case 9:
            // Float value (i_meas)
            return BitExtractStatus(0x007C, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvIMeas13() not defined for this board version");
      };
   };
   unsigned int GetHvIMeas13Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0080;
         case 9:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x007C;
         default:
            throw std::invalid_argument("Function GetHvIMeas13Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_I_MEAS_14
   unsigned int GetHvIMeas14()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            return BitExtractStatus(0x0084, 0xFFFFFFFF, 0);
         case 9:
            // Float value (i_meas)
            return BitExtractStatus(0x0080, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvIMeas14() not defined for this board version");
      };
   };
   unsigned int GetHvIMeas14Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0084;
         case 9:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0080;
         default:
            throw std::invalid_argument("Function GetHvIMeas14Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_I_MEAS_15
   unsigned int GetHvIMeas15()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            return BitExtractStatus(0x0088, 0xFFFFFFFF, 0);
         case 9:
            // Float value (i_meas)
            return BitExtractStatus(0x0084, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvIMeas15() not defined for this board version");
      };
   };
   unsigned int GetHvIMeas15Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0088;
         case 9:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0084;
         default:
            throw std::invalid_argument("Function GetHvIMeas15Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_I_MEAS_2
   unsigned int GetHvIMeas2()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            return BitExtractStatus(0x0054, 0xFFFFFFFF, 0);
         case 9:
            // Float value (i_meas)
            return BitExtractStatus(0x0050, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvIMeas2() not defined for this board version");
      };
   };
   unsigned int GetHvIMeas2Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0054;
         case 9:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0050;
         default:
            throw std::invalid_argument("Function GetHvIMeas2Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_I_MEAS_3
   unsigned int GetHvIMeas3()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            return BitExtractStatus(0x0058, 0xFFFFFFFF, 0);
         case 9:
            // Float value (i_meas)
            return BitExtractStatus(0x0054, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvIMeas3() not defined for this board version");
      };
   };
   unsigned int GetHvIMeas3Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0058;
         case 9:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0054;
         default:
            throw std::invalid_argument("Function GetHvIMeas3Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_I_MEAS_4
   unsigned int GetHvIMeas4()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            return BitExtractStatus(0x005C, 0xFFFFFFFF, 0);
         case 9:
            // Float value (i_meas)
            return BitExtractStatus(0x0058, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvIMeas4() not defined for this board version");
      };
   };
   unsigned int GetHvIMeas4Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x005C;
         case 9:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0058;
         default:
            throw std::invalid_argument("Function GetHvIMeas4Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_I_MEAS_5
   unsigned int GetHvIMeas5()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            return BitExtractStatus(0x0060, 0xFFFFFFFF, 0);
         case 9:
            // Float value (i_meas)
            return BitExtractStatus(0x005C, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvIMeas5() not defined for this board version");
      };
   };
   unsigned int GetHvIMeas5Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0060;
         case 9:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x005C;
         default:
            throw std::invalid_argument("Function GetHvIMeas5Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_I_MEAS_6
   unsigned int GetHvIMeas6()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            return BitExtractStatus(0x0064, 0xFFFFFFFF, 0);
         case 9:
            // Float value (i_meas)
            return BitExtractStatus(0x0060, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvIMeas6() not defined for this board version");
      };
   };
   unsigned int GetHvIMeas6Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0064;
         case 9:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0060;
         default:
            throw std::invalid_argument("Function GetHvIMeas6Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_I_MEAS_7
   unsigned int GetHvIMeas7()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            return BitExtractStatus(0x0068, 0xFFFFFFFF, 0);
         case 9:
            // Float value (i_meas)
            return BitExtractStatus(0x0064, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvIMeas7() not defined for this board version");
      };
   };
   unsigned int GetHvIMeas7Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0068;
         case 9:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0064;
         default:
            throw std::invalid_argument("Function GetHvIMeas7Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_I_MEAS_8
   unsigned int GetHvIMeas8()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            return BitExtractStatus(0x006C, 0xFFFFFFFF, 0);
         case 9:
            // Float value (i_meas)
            return BitExtractStatus(0x0068, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvIMeas8() not defined for this board version");
      };
   };
   unsigned int GetHvIMeas8Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x006C;
         case 9:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0068;
         default:
            throw std::invalid_argument("Function GetHvIMeas8Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_I_MEAS_9
   unsigned int GetHvIMeas9()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            return BitExtractStatus(0x0070, 0xFFFFFFFF, 0);
         case 9:
            // Float value (i_meas)
            return BitExtractStatus(0x006C, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvIMeas9() not defined for this board version");
      };
   };
   unsigned int GetHvIMeas9Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0070;
         case 9:
            // Float value (i_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x006C;
         default:
            throw std::invalid_argument("Function GetHvIMeas9Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_R_SHUNT
   unsigned int GetHvRShunt()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Resistor value in Ohm (r_current)
            return BitExtractControl(0x10D8, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvRShunt() not defined for this board version");
      };
   };
   void SetHvRShunt(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Resistor value in Ohm (r_current)
            return SetRegMask(0x10D8, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetHvRShunt() not defined for this board version");
      };
   };
   unsigned int GetHvRShuntLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Resistor value in Ohm (r_current)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10D8;
         default:
            throw std::invalid_argument("Function GetHvRShuntLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_R_SHUNT_MOD
   unsigned int GetHvRShuntMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // HV supply shunt resistor register modified flags
            return BitExtractStatus(0x015C, 0x0000000F, 0);
         case 9:
            // HV supply shunt resistor register modified flags
            return BitExtractStatus(0x0158, 0x0000000F, 0);
         default:
            throw std::invalid_argument("Function GetHvRShuntMod() not defined for this board version");
      };
   };
   unsigned int GetHvRShuntModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // HV supply shunt resistor register modified flags
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x015C;
         case 9:
            // HV supply shunt resistor register modified flags
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0158;
         default:
            throw std::invalid_argument("Function GetHvRShuntModLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_TEMP_0
   unsigned int GetHvTemp0()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (temp)
            return BitExtractStatus(0x0090, 0xFFFFFFFF, 0);
         case 9:
            // Float value (temp)
            return BitExtractStatus(0x008C, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvTemp0() not defined for this board version");
      };
   };
   unsigned int GetHvTemp0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (temp)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0090;
         case 9:
            // Float value (temp)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x008C;
         default:
            throw std::invalid_argument("Function GetHvTemp0Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_TEMP_1
   unsigned int GetHvTemp1()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (temp)
            return BitExtractStatus(0x0094, 0xFFFFFFFF, 0);
         case 9:
            // Float value (temp)
            return BitExtractStatus(0x0090, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvTemp1() not defined for this board version");
      };
   };
   unsigned int GetHvTemp1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (temp)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0094;
         case 9:
            // Float value (temp)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0090;
         default:
            throw std::invalid_argument("Function GetHvTemp1Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_TEMP_2
   unsigned int GetHvTemp2()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (temp)
            return BitExtractStatus(0x0098, 0xFFFFFFFF, 0);
         case 9:
            // Float value (temp)
            return BitExtractStatus(0x0094, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvTemp2() not defined for this board version");
      };
   };
   unsigned int GetHvTemp2Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (temp)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0098;
         case 9:
            // Float value (temp)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0094;
         default:
            throw std::invalid_argument("Function GetHvTemp2Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_TEMP_3
   unsigned int GetHvTemp3()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (temp)
            return BitExtractStatus(0x009C, 0xFFFFFFFF, 0);
         case 9:
            // Float value (temp)
            return BitExtractStatus(0x0098, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvTemp3() not defined for this board version");
      };
   };
   unsigned int GetHvTemp3Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (temp)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x009C;
         case 9:
            // Float value (temp)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0098;
         default:
            throw std::invalid_argument("Function GetHvTemp3Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_BASE_MEAS
   unsigned int GetHvUBaseMeas()
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (ub_meas)
            return BitExtractStatus(0x008C, 0xFFFFFFFF, 0);
         case 9:
            // Float value (ub_meas)
            return BitExtractStatus(0x0088, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvUBaseMeas() not defined for this board version");
      };
   };
   unsigned int GetHvUBaseMeasLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Float value (ub_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x008C;
         case 9:
            // Float value (ub_meas)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0088;
         default:
            throw std::invalid_argument("Function GetHvUBaseMeasLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_0
   unsigned int GetHvUTarget0()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return BitExtractControl(0x1098, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvUTarget0() not defined for this board version");
      };
   };
   void SetHvUTarget0(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return SetRegMask(0x1098, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetHvUTarget0() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1098;
         default:
            throw std::invalid_argument("Function GetHvUTarget0Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_0_MOD
   unsigned int GetHvUTarget0Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 0 register modified flags
            return BitExtractStatus(0x0154, 0xF0000000, 28);
         case 9:
            // Target high voltage channel 0 register modified flags
            return BitExtractStatus(0x0150, 0xF0000000, 28);
         default:
            throw std::invalid_argument("Function GetHvUTarget0Mod() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget0ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 0 register modified flags
            if(BitMask) *BitMask = 0xF0000000;
            if(BitOfs) *BitOfs = 28;
            return 0x0154;
         case 9:
            // Target high voltage channel 0 register modified flags
            if(BitMask) *BitMask = 0xF0000000;
            if(BitOfs) *BitOfs = 28;
            return 0x0150;
         default:
            throw std::invalid_argument("Function GetHvUTarget0ModLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_1
   unsigned int GetHvUTarget1()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return BitExtractControl(0x109C, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvUTarget1() not defined for this board version");
      };
   };
   void SetHvUTarget1(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return SetRegMask(0x109C, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetHvUTarget1() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x109C;
         default:
            throw std::invalid_argument("Function GetHvUTarget1Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_10
   unsigned int GetHvUTarget10()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return BitExtractControl(0x10C0, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvUTarget10() not defined for this board version");
      };
   };
   void SetHvUTarget10(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return SetRegMask(0x10C0, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetHvUTarget10() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget10Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10C0;
         default:
            throw std::invalid_argument("Function GetHvUTarget10Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_10_MOD
   unsigned int GetHvUTarget10Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 10 register modified flags
            return BitExtractStatus(0x0158, 0x00F00000, 20);
         case 9:
            // Target high voltage channel 10 register modified flags
            return BitExtractStatus(0x0154, 0x00F00000, 20);
         default:
            throw std::invalid_argument("Function GetHvUTarget10Mod() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget10ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 10 register modified flags
            if(BitMask) *BitMask = 0x00F00000;
            if(BitOfs) *BitOfs = 20;
            return 0x0158;
         case 9:
            // Target high voltage channel 10 register modified flags
            if(BitMask) *BitMask = 0x00F00000;
            if(BitOfs) *BitOfs = 20;
            return 0x0154;
         default:
            throw std::invalid_argument("Function GetHvUTarget10ModLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_11
   unsigned int GetHvUTarget11()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return BitExtractControl(0x10C4, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvUTarget11() not defined for this board version");
      };
   };
   void SetHvUTarget11(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return SetRegMask(0x10C4, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetHvUTarget11() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget11Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10C4;
         default:
            throw std::invalid_argument("Function GetHvUTarget11Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_11_MOD
   unsigned int GetHvUTarget11Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 11 register modified flags
            return BitExtractStatus(0x0158, 0x000F0000, 16);
         case 9:
            // Target high voltage channel 11 register modified flags
            return BitExtractStatus(0x0154, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetHvUTarget11Mod() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget11ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 11 register modified flags
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0158;
         case 9:
            // Target high voltage channel 11 register modified flags
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0154;
         default:
            throw std::invalid_argument("Function GetHvUTarget11ModLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_12
   unsigned int GetHvUTarget12()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return BitExtractControl(0x10C8, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvUTarget12() not defined for this board version");
      };
   };
   void SetHvUTarget12(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return SetRegMask(0x10C8, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetHvUTarget12() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget12Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10C8;
         default:
            throw std::invalid_argument("Function GetHvUTarget12Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_12_MOD
   unsigned int GetHvUTarget12Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 12 register modified flags
            return BitExtractStatus(0x0158, 0x0000F000, 12);
         case 9:
            // Target high voltage channel 12 register modified flags
            return BitExtractStatus(0x0154, 0x0000F000, 12);
         default:
            throw std::invalid_argument("Function GetHvUTarget12Mod() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget12ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 12 register modified flags
            if(BitMask) *BitMask = 0x0000F000;
            if(BitOfs) *BitOfs = 12;
            return 0x0158;
         case 9:
            // Target high voltage channel 12 register modified flags
            if(BitMask) *BitMask = 0x0000F000;
            if(BitOfs) *BitOfs = 12;
            return 0x0154;
         default:
            throw std::invalid_argument("Function GetHvUTarget12ModLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_13
   unsigned int GetHvUTarget13()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return BitExtractControl(0x10CC, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvUTarget13() not defined for this board version");
      };
   };
   void SetHvUTarget13(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return SetRegMask(0x10CC, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetHvUTarget13() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget13Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10CC;
         default:
            throw std::invalid_argument("Function GetHvUTarget13Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_13_MOD
   unsigned int GetHvUTarget13Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 13 register modified flags
            return BitExtractStatus(0x0158, 0x00000F00, 8);
         case 9:
            // Target high voltage channel 13 register modified flags
            return BitExtractStatus(0x0154, 0x00000F00, 8);
         default:
            throw std::invalid_argument("Function GetHvUTarget13Mod() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget13ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 13 register modified flags
            if(BitMask) *BitMask = 0x00000F00;
            if(BitOfs) *BitOfs = 8;
            return 0x0158;
         case 9:
            // Target high voltage channel 13 register modified flags
            if(BitMask) *BitMask = 0x00000F00;
            if(BitOfs) *BitOfs = 8;
            return 0x0154;
         default:
            throw std::invalid_argument("Function GetHvUTarget13ModLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_14
   unsigned int GetHvUTarget14()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return BitExtractControl(0x10D0, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvUTarget14() not defined for this board version");
      };
   };
   void SetHvUTarget14(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return SetRegMask(0x10D0, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetHvUTarget14() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget14Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10D0;
         default:
            throw std::invalid_argument("Function GetHvUTarget14Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_14_MOD
   unsigned int GetHvUTarget14Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 14 register modified flags
            return BitExtractStatus(0x0158, 0x000000F0, 4);
         case 9:
            // Target high voltage channel 14 register modified flags
            return BitExtractStatus(0x0154, 0x000000F0, 4);
         default:
            throw std::invalid_argument("Function GetHvUTarget14Mod() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget14ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 14 register modified flags
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x0158;
         case 9:
            // Target high voltage channel 14 register modified flags
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x0154;
         default:
            throw std::invalid_argument("Function GetHvUTarget14ModLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_15
   unsigned int GetHvUTarget15()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return BitExtractControl(0x10D4, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvUTarget15() not defined for this board version");
      };
   };
   void SetHvUTarget15(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return SetRegMask(0x10D4, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetHvUTarget15() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget15Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10D4;
         default:
            throw std::invalid_argument("Function GetHvUTarget15Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_15_MOD
   unsigned int GetHvUTarget15Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 15 register modified flags
            return BitExtractStatus(0x0158, 0x0000000F, 0);
         case 9:
            // Target high voltage channel 15 register modified flags
            return BitExtractStatus(0x0154, 0x0000000F, 0);
         default:
            throw std::invalid_argument("Function GetHvUTarget15Mod() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget15ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 15 register modified flags
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0158;
         case 9:
            // Target high voltage channel 15 register modified flags
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0154;
         default:
            throw std::invalid_argument("Function GetHvUTarget15ModLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_1_MOD
   unsigned int GetHvUTarget1Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 1 register modified flags
            return BitExtractStatus(0x0154, 0x0F000000, 24);
         case 9:
            // Target high voltage channel 1 register modified flags
            return BitExtractStatus(0x0150, 0x0F000000, 24);
         default:
            throw std::invalid_argument("Function GetHvUTarget1Mod() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget1ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 1 register modified flags
            if(BitMask) *BitMask = 0x0F000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0154;
         case 9:
            // Target high voltage channel 1 register modified flags
            if(BitMask) *BitMask = 0x0F000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0150;
         default:
            throw std::invalid_argument("Function GetHvUTarget1ModLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_2
   unsigned int GetHvUTarget2()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return BitExtractControl(0x10A0, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvUTarget2() not defined for this board version");
      };
   };
   void SetHvUTarget2(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return SetRegMask(0x10A0, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetHvUTarget2() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget2Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10A0;
         default:
            throw std::invalid_argument("Function GetHvUTarget2Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_2_MOD
   unsigned int GetHvUTarget2Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 2 register modified flags
            return BitExtractStatus(0x0154, 0x00F00000, 20);
         case 9:
            // Target high voltage channel 2 register modified flags
            return BitExtractStatus(0x0150, 0x00F00000, 20);
         default:
            throw std::invalid_argument("Function GetHvUTarget2Mod() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget2ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 2 register modified flags
            if(BitMask) *BitMask = 0x00F00000;
            if(BitOfs) *BitOfs = 20;
            return 0x0154;
         case 9:
            // Target high voltage channel 2 register modified flags
            if(BitMask) *BitMask = 0x00F00000;
            if(BitOfs) *BitOfs = 20;
            return 0x0150;
         default:
            throw std::invalid_argument("Function GetHvUTarget2ModLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_3
   unsigned int GetHvUTarget3()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return BitExtractControl(0x10A4, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvUTarget3() not defined for this board version");
      };
   };
   void SetHvUTarget3(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return SetRegMask(0x10A4, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetHvUTarget3() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget3Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10A4;
         default:
            throw std::invalid_argument("Function GetHvUTarget3Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_3_MOD
   unsigned int GetHvUTarget3Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 3 register modified flags
            return BitExtractStatus(0x0154, 0x000F0000, 16);
         case 9:
            // Target high voltage channel 3 register modified flags
            return BitExtractStatus(0x0150, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetHvUTarget3Mod() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget3ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 3 register modified flags
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0154;
         case 9:
            // Target high voltage channel 3 register modified flags
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0150;
         default:
            throw std::invalid_argument("Function GetHvUTarget3ModLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_4
   unsigned int GetHvUTarget4()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return BitExtractControl(0x10A8, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvUTarget4() not defined for this board version");
      };
   };
   void SetHvUTarget4(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return SetRegMask(0x10A8, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetHvUTarget4() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget4Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10A8;
         default:
            throw std::invalid_argument("Function GetHvUTarget4Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_4_MOD
   unsigned int GetHvUTarget4Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 4 register modified flags
            return BitExtractStatus(0x0154, 0x0000F000, 12);
         case 9:
            // Target high voltage channel 4 register modified flags
            return BitExtractStatus(0x0150, 0x0000F000, 12);
         default:
            throw std::invalid_argument("Function GetHvUTarget4Mod() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget4ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 4 register modified flags
            if(BitMask) *BitMask = 0x0000F000;
            if(BitOfs) *BitOfs = 12;
            return 0x0154;
         case 9:
            // Target high voltage channel 4 register modified flags
            if(BitMask) *BitMask = 0x0000F000;
            if(BitOfs) *BitOfs = 12;
            return 0x0150;
         default:
            throw std::invalid_argument("Function GetHvUTarget4ModLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_5
   unsigned int GetHvUTarget5()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return BitExtractControl(0x10AC, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvUTarget5() not defined for this board version");
      };
   };
   void SetHvUTarget5(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return SetRegMask(0x10AC, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetHvUTarget5() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget5Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10AC;
         default:
            throw std::invalid_argument("Function GetHvUTarget5Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_5_MOD
   unsigned int GetHvUTarget5Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 5 register modified flags
            return BitExtractStatus(0x0154, 0x00000F00, 8);
         case 9:
            // Target high voltage channel 5 register modified flags
            return BitExtractStatus(0x0150, 0x00000F00, 8);
         default:
            throw std::invalid_argument("Function GetHvUTarget5Mod() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget5ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 5 register modified flags
            if(BitMask) *BitMask = 0x00000F00;
            if(BitOfs) *BitOfs = 8;
            return 0x0154;
         case 9:
            // Target high voltage channel 5 register modified flags
            if(BitMask) *BitMask = 0x00000F00;
            if(BitOfs) *BitOfs = 8;
            return 0x0150;
         default:
            throw std::invalid_argument("Function GetHvUTarget5ModLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_6
   unsigned int GetHvUTarget6()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return BitExtractControl(0x10B0, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvUTarget6() not defined for this board version");
      };
   };
   void SetHvUTarget6(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return SetRegMask(0x10B0, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetHvUTarget6() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget6Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10B0;
         default:
            throw std::invalid_argument("Function GetHvUTarget6Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_6_MOD
   unsigned int GetHvUTarget6Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 6 register modified flags
            return BitExtractStatus(0x0154, 0x000000F0, 4);
         case 9:
            // Target high voltage channel 6 register modified flags
            return BitExtractStatus(0x0150, 0x000000F0, 4);
         default:
            throw std::invalid_argument("Function GetHvUTarget6Mod() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget6ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 6 register modified flags
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x0154;
         case 9:
            // Target high voltage channel 6 register modified flags
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x0150;
         default:
            throw std::invalid_argument("Function GetHvUTarget6ModLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_7
   unsigned int GetHvUTarget7()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return BitExtractControl(0x10B4, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvUTarget7() not defined for this board version");
      };
   };
   void SetHvUTarget7(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return SetRegMask(0x10B4, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetHvUTarget7() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget7Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10B4;
         default:
            throw std::invalid_argument("Function GetHvUTarget7Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_7_MOD
   unsigned int GetHvUTarget7Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 7 register modified flags
            return BitExtractStatus(0x0154, 0x0000000F, 0);
         case 9:
            // Target high voltage channel 7 register modified flags
            return BitExtractStatus(0x0150, 0x0000000F, 0);
         default:
            throw std::invalid_argument("Function GetHvUTarget7Mod() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget7ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 7 register modified flags
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0154;
         case 9:
            // Target high voltage channel 7 register modified flags
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0150;
         default:
            throw std::invalid_argument("Function GetHvUTarget7ModLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_8
   unsigned int GetHvUTarget8()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return BitExtractControl(0x10B8, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvUTarget8() not defined for this board version");
      };
   };
   void SetHvUTarget8(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return SetRegMask(0x10B8, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetHvUTarget8() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget8Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10B8;
         default:
            throw std::invalid_argument("Function GetHvUTarget8Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_8_MOD
   unsigned int GetHvUTarget8Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 8 register modified flags
            return BitExtractStatus(0x0158, 0xF0000000, 28);
         case 9:
            // Target high voltage channel 8 register modified flags
            return BitExtractStatus(0x0154, 0xF0000000, 28);
         default:
            throw std::invalid_argument("Function GetHvUTarget8Mod() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget8ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 8 register modified flags
            if(BitMask) *BitMask = 0xF0000000;
            if(BitOfs) *BitOfs = 28;
            return 0x0158;
         case 9:
            // Target high voltage channel 8 register modified flags
            if(BitMask) *BitMask = 0xF0000000;
            if(BitOfs) *BitOfs = 28;
            return 0x0154;
         default:
            throw std::invalid_argument("Function GetHvUTarget8ModLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_9
   unsigned int GetHvUTarget9()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return BitExtractControl(0x10BC, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvUTarget9() not defined for this board version");
      };
   };
   void SetHvUTarget9(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            return SetRegMask(0x10BC, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetHvUTarget9() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget9Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Float value (u_demand)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10BC;
         default:
            throw std::invalid_argument("Function GetHvUTarget9Loc() not defined for this board version");
      };
   };

   // Bit(s) HV_U_TARGET_9_MOD
   unsigned int GetHvUTarget9Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 9 register modified flags
            return BitExtractStatus(0x0158, 0x0F000000, 24);
         case 9:
            // Target high voltage channel 9 register modified flags
            return BitExtractStatus(0x0154, 0x0F000000, 24);
         default:
            throw std::invalid_argument("Function GetHvUTarget9Mod() not defined for this board version");
      };
   };
   unsigned int GetHvUTarget9ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Target high voltage channel 9 register modified flags
            if(BitMask) *BitMask = 0x0F000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0158;
         case 9:
            // Target high voltage channel 9 register modified flags
            if(BitMask) *BitMask = 0x0F000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0154;
         default:
            throw std::invalid_argument("Function GetHvUTarget9ModLoc() not defined for this board version");
      };
   };

   // Bit(s) HV_VER
   unsigned int GetHvVer()
   {
      switch(this->mVersion)
      {
         case 8:
            // HV board version (16bit Voltage in V, 16bit Current in mA)
            return BitExtractStatus(0x0048, 0xFFFFFFFF, 0);
         case 9:
            // HV board version (16bit Voltage in V, 16bit Current in mA)
            return BitExtractStatus(0x0044, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetHvVer() not defined for this board version");
      };
   };
   unsigned int GetHvVerLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // HV board version (16bit Voltage in V, 16bit Current in mA)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0048;
         case 9:
            // HV board version (16bit Voltage in V, 16bit Current in mA)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0044;
         default:
            throw std::invalid_argument("Function GetHvVerLoc() not defined for this board version");
      };
   };

   // Bit(s) INTER_PKG_DELAY
   unsigned int GetInterPkgDelay()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Delay between transmission of two UDP packages in 8ns steps
            return BitExtractControl(0x1014, 0x00FFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetInterPkgDelay() not defined for this board version");
      };
   };
   void SetInterPkgDelay(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Delay between transmission of two UDP packages in 8ns steps
            return SetRegMask(0x1014, 0x00FFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetInterPkgDelay() not defined for this board version");
      };
   };
   unsigned int GetInterPkgDelayLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Delay between transmission of two UDP packages in 8ns steps
            if(BitMask) *BitMask = 0x00FFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1014;
         default:
            throw std::invalid_argument("Function GetInterPkgDelayLoc() not defined for this board version");
      };
   };

   // Bit(s) ISERDES_PLL_LOCK_0
   unsigned int GetIserdesPllLock0()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Lock of PLL for ISERDES from ADC 0 (A) (FPGA internal)
            return BitExtractStatus(0x002C, 0x00000010, 4);
         default:
            throw std::invalid_argument("Function GetIserdesPllLock0() not defined for this board version");
      };
   };
   unsigned int GetIserdesPllLock0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Lock of PLL for ISERDES from ADC 0 (A) (FPGA internal)
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x002C;
         default:
            throw std::invalid_argument("Function GetIserdesPllLock0Loc() not defined for this board version");
      };
   };

   // Bit(s) ISERDES_PLL_LOCK_1
   unsigned int GetIserdesPllLock1()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Lock of PLL for ISERDES from ADC 1 (B) (FPGA internal)
            return BitExtractStatus(0x002C, 0x00000008, 3);
         default:
            throw std::invalid_argument("Function GetIserdesPllLock1() not defined for this board version");
      };
   };
   unsigned int GetIserdesPllLock1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Lock of PLL for ISERDES from ADC 1 (B) (FPGA internal)
            if(BitMask) *BitMask = 0x00000008;
            if(BitOfs) *BitOfs = 3;
            return 0x002C;
         default:
            throw std::invalid_argument("Function GetIserdesPllLock1Loc() not defined for this board version");
      };
   };

   // Bit(s) LEAD_TRAIL_EDGE_SEL
   unsigned int GetLeadTrailEdgeSel()
   {
      switch(this->mVersion)
      {
         case 8:
            // 0 = trigger on leading edge, 1 = trigger on trailing edge
            return BitExtractControl(0x1180, 0x00010000, 16);
         case 9:
            // 0 = trigger on leading edge, 1 = trigger on trailing edge
            return BitExtractControl(0x1124, 0x00010000, 16);
         default:
            throw std::invalid_argument("Function GetLeadTrailEdgeSel() not defined for this board version");
      };
   };
   void SetLeadTrailEdgeSel(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // 0 = trigger on leading edge, 1 = trigger on trailing edge
            return SetRegMask(0x1180, 0x00010000, 16, value);
         case 9:
            // 0 = trigger on leading edge, 1 = trigger on trailing edge
            return SetRegMask(0x1124, 0x00010000, 16, value);
         default:
            throw std::invalid_argument("Function SetLeadTrailEdgeSel() not defined for this board version");
      };
   };
   unsigned int GetLeadTrailEdgeSelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // 0 = trigger on leading edge, 1 = trigger on trailing edge
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x1180;
         case 9:
            // 0 = trigger on leading edge, 1 = trigger on trailing edge
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x1124;
         default:
            throw std::invalid_argument("Function GetLeadTrailEdgeSelLoc() not defined for this board version");
      };
   };

   // Bit(s) LED_STATE
   unsigned int GetLedState()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // State of the front panel LED (on-beat-color RGB, off-beat-color RGB)
            return BitExtractStatus(0x0024, 0x3F000000, 24);
         default:
            throw std::invalid_argument("Function GetLedState() not defined for this board version");
      };
   };
   unsigned int GetLedStateLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // State of the front panel LED (on-beat-color RGB, off-beat-color RGB)
            if(BitMask) *BitMask = 0x3F000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0024;
         default:
            throw std::invalid_argument("Function GetLedStateLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK0_CLKOUT_DIV
   unsigned int GetLmk0ClkoutDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 0 Clock Output Divider (value x 2) (1..255)
            return BitExtractControl(0x10DC, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetLmk0ClkoutDiv() not defined for this board version");
      };
   };
   void SetLmk0ClkoutDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 0 Clock Output Divider (value x 2) (1..255)
            return SetRegMask(0x10DC, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetLmk0ClkoutDiv() not defined for this board version");
      };
   };
   unsigned int GetLmk0ClkoutDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 0 Clock Output Divider (value x 2) (1..255)
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x10DC;
         default:
            throw std::invalid_argument("Function GetLmk0ClkoutDivLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK0_CLKOUT_DLY
   unsigned int GetLmk0ClkoutDly()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 0 Clock Output Delay (value x 150ps)
            return BitExtractControl(0x10DC, 0x000000F0, 4);
         default:
            throw std::invalid_argument("Function GetLmk0ClkoutDly() not defined for this board version");
      };
   };
   void SetLmk0ClkoutDly(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 0 Clock Output Delay (value x 150ps)
            return SetRegMask(0x10DC, 0x000000F0, 4, value);
         default:
            throw std::invalid_argument("Function SetLmk0ClkoutDly() not defined for this board version");
      };
   };
   unsigned int GetLmk0ClkoutDlyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 0 Clock Output Delay (value x 150ps)
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x10DC;
         default:
            throw std::invalid_argument("Function GetLmk0ClkoutDlyLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK0_CLKOUT_EN
   unsigned int GetLmk0ClkoutEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 0 Clock Output Enable (0 = Disabled, 1 = Enabled)
            return BitExtractControl(0x10DC, 0x00010000, 16);
         default:
            throw std::invalid_argument("Function GetLmk0ClkoutEn() not defined for this board version");
      };
   };
   void SetLmk0ClkoutEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 0 Clock Output Enable (0 = Disabled, 1 = Enabled)
            return SetRegMask(0x10DC, 0x00010000, 16, value);
         default:
            throw std::invalid_argument("Function SetLmk0ClkoutEn() not defined for this board version");
      };
   };
   unsigned int GetLmk0ClkoutEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 0 Clock Output Enable (0 = Disabled, 1 = Enabled)
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x10DC;
         default:
            throw std::invalid_argument("Function GetLmk0ClkoutEnLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK0_CLKOUT_MUX
   unsigned int GetLmk0ClkoutMux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 0 Clock Output Multiplexer (see datasheet)
            return BitExtractControl(0x10DC, 0x00060000, 17);
         default:
            throw std::invalid_argument("Function GetLmk0ClkoutMux() not defined for this board version");
      };
   };
   void SetLmk0ClkoutMux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 0 Clock Output Multiplexer (see datasheet)
            return SetRegMask(0x10DC, 0x00060000, 17, value);
         default:
            throw std::invalid_argument("Function SetLmk0ClkoutMux() not defined for this board version");
      };
   };
   unsigned int GetLmk0ClkoutMuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 0 Clock Output Multiplexer (see datasheet)
            if(BitMask) *BitMask = 0x00060000;
            if(BitOfs) *BitOfs = 17;
            return 0x10DC;
         default:
            throw std::invalid_argument("Function GetLmk0ClkoutMuxLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK0_RESET
   unsigned int GetLmk0Reset()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Resets LMK Registers to Their Power-On State
            return BitExtractControl(0x10DC, 0x80000000, 31);
         default:
            throw std::invalid_argument("Function GetLmk0Reset() not defined for this board version");
      };
   };
   void SetLmk0Reset(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Resets LMK Registers to Their Power-On State
            return SetRegMask(0x10DC, 0x80000000, 31, value);
         default:
            throw std::invalid_argument("Function SetLmk0Reset() not defined for this board version");
      };
   };
   unsigned int GetLmk0ResetLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Resets LMK Registers to Their Power-On State
            if(BitMask) *BitMask = 0x80000000;
            if(BitOfs) *BitOfs = 31;
            return 0x10DC;
         default:
            throw std::invalid_argument("Function GetLmk0ResetLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK11_DIV4
   unsigned int GetLmk11Div4()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Divider Enable for Digital Lock Detect Circuit
            return BitExtractControl(0x1104, 0x00008000, 15);
         default:
            throw std::invalid_argument("Function GetLmk11Div4() not defined for this board version");
      };
   };
   void SetLmk11Div4(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Divider Enable for Digital Lock Detect Circuit
            return SetRegMask(0x1104, 0x00008000, 15, value);
         default:
            throw std::invalid_argument("Function SetLmk11Div4() not defined for this board version");
      };
   };
   unsigned int GetLmk11Div4Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Divider Enable for Digital Lock Detect Circuit
            if(BitMask) *BitMask = 0x00008000;
            if(BitOfs) *BitOfs = 15;
            return 0x1104;
         default:
            throw std::invalid_argument("Function GetLmk11Div4Loc() not defined for this board version");
      };
   };

   // Bit(s) LMK13_OSCIN_FREQ
   unsigned int GetLmk13OscinFreq()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Oscillator Input Calibration Adjustment in MHz (1..200)
            return BitExtractControl(0x1108, 0x003FC000, 14);
         default:
            throw std::invalid_argument("Function GetLmk13OscinFreq() not defined for this board version");
      };
   };
   void SetLmk13OscinFreq(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Oscillator Input Calibration Adjustment in MHz (1..200)
            return SetRegMask(0x1108, 0x003FC000, 14, value);
         default:
            throw std::invalid_argument("Function SetLmk13OscinFreq() not defined for this board version");
      };
   };
   unsigned int GetLmk13OscinFreqLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Oscillator Input Calibration Adjustment in MHz (1..200)
            if(BitMask) *BitMask = 0x003FC000;
            if(BitOfs) *BitOfs = 14;
            return 0x1108;
         default:
            throw std::invalid_argument("Function GetLmk13OscinFreqLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK13_VCO_C3_C4_LF
   unsigned int GetLmk13VcoC3C4Lf()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Value for Internal Loop Filter Capacitors C3/C4 (0..11) (see ds)
            return BitExtractControl(0x1108, 0x000000F0, 4);
         default:
            throw std::invalid_argument("Function GetLmk13VcoC3C4Lf() not defined for this board version");
      };
   };
   void SetLmk13VcoC3C4Lf(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Value for Internal Loop Filter Capacitors C3/C4 (0..11) (see ds)
            return SetRegMask(0x1108, 0x000000F0, 4, value);
         default:
            throw std::invalid_argument("Function SetLmk13VcoC3C4Lf() not defined for this board version");
      };
   };
   unsigned int GetLmk13VcoC3C4LfLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Value for Internal Loop Filter Capacitors C3/C4 (0..11) (see ds)
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x1108;
         default:
            throw std::invalid_argument("Function GetLmk13VcoC3C4LfLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK13_VCO_R3_LF
   unsigned int GetLmk13VcoR3Lf()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Value for Internal Loop Filter Resistor R3 (0..4) (see datasheet)
            return BitExtractControl(0x1108, 0x00000700, 8);
         default:
            throw std::invalid_argument("Function GetLmk13VcoR3Lf() not defined for this board version");
      };
   };
   void SetLmk13VcoR3Lf(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Value for Internal Loop Filter Resistor R3 (0..4) (see datasheet)
            return SetRegMask(0x1108, 0x00000700, 8, value);
         default:
            throw std::invalid_argument("Function SetLmk13VcoR3Lf() not defined for this board version");
      };
   };
   unsigned int GetLmk13VcoR3LfLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Value for Internal Loop Filter Resistor R3 (0..4) (see datasheet)
            if(BitMask) *BitMask = 0x00000700;
            if(BitOfs) *BitOfs = 8;
            return 0x1108;
         default:
            throw std::invalid_argument("Function GetLmk13VcoR3LfLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK13_VCO_R4_LF
   unsigned int GetLmk13VcoR4Lf()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Value for Internal Loop Filter Resistor R4 (0..4) (see datasheet)
            return BitExtractControl(0x1108, 0x00003800, 11);
         default:
            throw std::invalid_argument("Function GetLmk13VcoR4Lf() not defined for this board version");
      };
   };
   void SetLmk13VcoR4Lf(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Value for Internal Loop Filter Resistor R4 (0..4) (see datasheet)
            return SetRegMask(0x1108, 0x00003800, 11, value);
         default:
            throw std::invalid_argument("Function SetLmk13VcoR4Lf() not defined for this board version");
      };
   };
   unsigned int GetLmk13VcoR4LfLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Value for Internal Loop Filter Resistor R4 (0..4) (see datasheet)
            if(BitMask) *BitMask = 0x00003800;
            if(BitOfs) *BitOfs = 11;
            return 0x1108;
         default:
            throw std::invalid_argument("Function GetLmk13VcoR4LfLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK14_EN_CLKOUT_GLOBAL
   unsigned int GetLmk14EnClkoutGlobal()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Global Clock Output Enable (0 = All Off, 1 = Normal Operation)
            return BitExtractControl(0x110C, 0x08000000, 27);
         default:
            throw std::invalid_argument("Function GetLmk14EnClkoutGlobal() not defined for this board version");
      };
   };
   void SetLmk14EnClkoutGlobal(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Global Clock Output Enable (0 = All Off, 1 = Normal Operation)
            return SetRegMask(0x110C, 0x08000000, 27, value);
         default:
            throw std::invalid_argument("Function SetLmk14EnClkoutGlobal() not defined for this board version");
      };
   };
   unsigned int GetLmk14EnClkoutGlobalLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Global Clock Output Enable (0 = All Off, 1 = Normal Operation)
            if(BitMask) *BitMask = 0x08000000;
            if(BitOfs) *BitOfs = 27;
            return 0x110C;
         default:
            throw std::invalid_argument("Function GetLmk14EnClkoutGlobalLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK14_EN_FOUT
   unsigned int GetLmk14EnFout()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable for the Fout Pin (0 = Disabled, 1 = Enabled)
            return BitExtractControl(0x110C, 0x10000000, 28);
         default:
            throw std::invalid_argument("Function GetLmk14EnFout() not defined for this board version");
      };
   };
   void SetLmk14EnFout(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable for the Fout Pin (0 = Disabled, 1 = Enabled)
            return SetRegMask(0x110C, 0x10000000, 28, value);
         default:
            throw std::invalid_argument("Function SetLmk14EnFout() not defined for this board version");
      };
   };
   unsigned int GetLmk14EnFoutLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable for the Fout Pin (0 = Disabled, 1 = Enabled)
            if(BitMask) *BitMask = 0x10000000;
            if(BitOfs) *BitOfs = 28;
            return 0x110C;
         default:
            throw std::invalid_argument("Function GetLmk14EnFoutLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK14_PLL_MUX
   unsigned int GetLmk14PllMux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Output Mode of  LD Pin (0..7,9,11)
            return BitExtractControl(0x110C, 0x00F00000, 20);
         default:
            throw std::invalid_argument("Function GetLmk14PllMux() not defined for this board version");
      };
   };
   void SetLmk14PllMux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Output Mode of  LD Pin (0..7,9,11)
            return SetRegMask(0x110C, 0x00F00000, 20, value);
         default:
            throw std::invalid_argument("Function SetLmk14PllMux() not defined for this board version");
      };
   };
   unsigned int GetLmk14PllMuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Output Mode of  LD Pin (0..7,9,11)
            if(BitMask) *BitMask = 0x00F00000;
            if(BitOfs) *BitOfs = 20;
            return 0x110C;
         default:
            throw std::invalid_argument("Function GetLmk14PllMuxLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK14_PLL_R
   unsigned int GetLmk14PllR()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // PLL R Divider Value (1..4095)
            return BitExtractControl(0x110C, 0x000FFF00, 8);
         default:
            throw std::invalid_argument("Function GetLmk14PllR() not defined for this board version");
      };
   };
   void SetLmk14PllR(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // PLL R Divider Value (1..4095)
            return SetRegMask(0x110C, 0x000FFF00, 8, value);
         default:
            throw std::invalid_argument("Function SetLmk14PllR() not defined for this board version");
      };
   };
   unsigned int GetLmk14PllRLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // PLL R Divider Value (1..4095)
            if(BitMask) *BitMask = 0x000FFF00;
            if(BitOfs) *BitOfs = 8;
            return 0x110C;
         default:
            throw std::invalid_argument("Function GetLmk14PllRLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK14_POWERDOWN
   unsigned int GetLmk14Powerdown()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Powerdown (0 = Normal Operation, 1 = Device Powered Down)
            return BitExtractControl(0x110C, 0x04000000, 26);
         default:
            throw std::invalid_argument("Function GetLmk14Powerdown() not defined for this board version");
      };
   };
   void SetLmk14Powerdown(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Powerdown (0 = Normal Operation, 1 = Device Powered Down)
            return SetRegMask(0x110C, 0x04000000, 26, value);
         default:
            throw std::invalid_argument("Function SetLmk14Powerdown() not defined for this board version");
      };
   };
   unsigned int GetLmk14PowerdownLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Powerdown (0 = Normal Operation, 1 = Device Powered Down)
            if(BitMask) *BitMask = 0x04000000;
            if(BitOfs) *BitOfs = 26;
            return 0x110C;
         default:
            throw std::invalid_argument("Function GetLmk14PowerdownLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK15_PLL_CP_GAIN
   unsigned int GetLmk15PllCpGain()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // PLL Charge Pump Gain (see datasheet) (0..4)
            return BitExtractControl(0x1110, 0xC0000000, 30);
         default:
            throw std::invalid_argument("Function GetLmk15PllCpGain() not defined for this board version");
      };
   };
   void SetLmk15PllCpGain(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // PLL Charge Pump Gain (see datasheet) (0..4)
            return SetRegMask(0x1110, 0xC0000000, 30, value);
         default:
            throw std::invalid_argument("Function SetLmk15PllCpGain() not defined for this board version");
      };
   };
   unsigned int GetLmk15PllCpGainLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // PLL Charge Pump Gain (see datasheet) (0..4)
            if(BitMask) *BitMask = 0xC0000000;
            if(BitOfs) *BitOfs = 30;
            return 0x1110;
         default:
            throw std::invalid_argument("Function GetLmk15PllCpGainLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK15_PLL_N
   unsigned int GetLmk15PllN()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // PLL N Divider Value (1..0x3FFFF)
            return BitExtractControl(0x1110, 0x03FFFF00, 8);
         default:
            throw std::invalid_argument("Function GetLmk15PllN() not defined for this board version");
      };
   };
   void SetLmk15PllN(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // PLL N Divider Value (1..0x3FFFF)
            return SetRegMask(0x1110, 0x03FFFF00, 8, value);
         default:
            throw std::invalid_argument("Function SetLmk15PllN() not defined for this board version");
      };
   };
   unsigned int GetLmk15PllNLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // PLL N Divider Value (1..0x3FFFF)
            if(BitMask) *BitMask = 0x03FFFF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1110;
         default:
            throw std::invalid_argument("Function GetLmk15PllNLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK15_VCO_DIV
   unsigned int GetLmk15VcoDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // VCO Divider Value (2..8)
            return BitExtractControl(0x1110, 0x3C000000, 26);
         default:
            throw std::invalid_argument("Function GetLmk15VcoDiv() not defined for this board version");
      };
   };
   void SetLmk15VcoDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // VCO Divider Value (2..8)
            return SetRegMask(0x1110, 0x3C000000, 26, value);
         default:
            throw std::invalid_argument("Function SetLmk15VcoDiv() not defined for this board version");
      };
   };
   unsigned int GetLmk15VcoDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // VCO Divider Value (2..8)
            if(BitMask) *BitMask = 0x3C000000;
            if(BitOfs) *BitOfs = 26;
            return 0x1110;
         default:
            throw std::invalid_argument("Function GetLmk15VcoDivLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK1_CLKOUT_DIV
   unsigned int GetLmk1ClkoutDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 1 Clock Output Divider (value x 2) (1..255)
            return BitExtractControl(0x10E0, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetLmk1ClkoutDiv() not defined for this board version");
      };
   };
   void SetLmk1ClkoutDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 1 Clock Output Divider (value x 2) (1..255)
            return SetRegMask(0x10E0, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetLmk1ClkoutDiv() not defined for this board version");
      };
   };
   unsigned int GetLmk1ClkoutDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 1 Clock Output Divider (value x 2) (1..255)
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x10E0;
         default:
            throw std::invalid_argument("Function GetLmk1ClkoutDivLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK1_CLKOUT_DLY
   unsigned int GetLmk1ClkoutDly()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 1 Clock Output Delay (value x 150ps)
            return BitExtractControl(0x10E0, 0x000000F0, 4);
         default:
            throw std::invalid_argument("Function GetLmk1ClkoutDly() not defined for this board version");
      };
   };
   void SetLmk1ClkoutDly(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 1 Clock Output Delay (value x 150ps)
            return SetRegMask(0x10E0, 0x000000F0, 4, value);
         default:
            throw std::invalid_argument("Function SetLmk1ClkoutDly() not defined for this board version");
      };
   };
   unsigned int GetLmk1ClkoutDlyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 1 Clock Output Delay (value x 150ps)
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x10E0;
         default:
            throw std::invalid_argument("Function GetLmk1ClkoutDlyLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK1_CLKOUT_EN
   unsigned int GetLmk1ClkoutEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 1 Clock Output Enable (0 = Disabled, 1 = Enabled)
            return BitExtractControl(0x10E0, 0x00010000, 16);
         default:
            throw std::invalid_argument("Function GetLmk1ClkoutEn() not defined for this board version");
      };
   };
   void SetLmk1ClkoutEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 1 Clock Output Enable (0 = Disabled, 1 = Enabled)
            return SetRegMask(0x10E0, 0x00010000, 16, value);
         default:
            throw std::invalid_argument("Function SetLmk1ClkoutEn() not defined for this board version");
      };
   };
   unsigned int GetLmk1ClkoutEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 1 Clock Output Enable (0 = Disabled, 1 = Enabled)
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x10E0;
         default:
            throw std::invalid_argument("Function GetLmk1ClkoutEnLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK1_CLKOUT_MUX
   unsigned int GetLmk1ClkoutMux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 1 Clock Output Multiplexer (see datasheet)
            return BitExtractControl(0x10E0, 0x00060000, 17);
         default:
            throw std::invalid_argument("Function GetLmk1ClkoutMux() not defined for this board version");
      };
   };
   void SetLmk1ClkoutMux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 1 Clock Output Multiplexer (see datasheet)
            return SetRegMask(0x10E0, 0x00060000, 17, value);
         default:
            throw std::invalid_argument("Function SetLmk1ClkoutMux() not defined for this board version");
      };
   };
   unsigned int GetLmk1ClkoutMuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 1 Clock Output Multiplexer (see datasheet)
            if(BitMask) *BitMask = 0x00060000;
            if(BitOfs) *BitOfs = 17;
            return 0x10E0;
         default:
            throw std::invalid_argument("Function GetLmk1ClkoutMuxLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK2_CLKOUT_DIV
   unsigned int GetLmk2ClkoutDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 2 Clock Output Divider (value x 2) (1..255)
            return BitExtractControl(0x10E4, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetLmk2ClkoutDiv() not defined for this board version");
      };
   };
   void SetLmk2ClkoutDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 2 Clock Output Divider (value x 2) (1..255)
            return SetRegMask(0x10E4, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetLmk2ClkoutDiv() not defined for this board version");
      };
   };
   unsigned int GetLmk2ClkoutDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 2 Clock Output Divider (value x 2) (1..255)
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x10E4;
         default:
            throw std::invalid_argument("Function GetLmk2ClkoutDivLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK2_CLKOUT_DLY
   unsigned int GetLmk2ClkoutDly()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 2 Clock Output Delay (value x 150ps)
            return BitExtractControl(0x10E4, 0x000000F0, 4);
         default:
            throw std::invalid_argument("Function GetLmk2ClkoutDly() not defined for this board version");
      };
   };
   void SetLmk2ClkoutDly(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 2 Clock Output Delay (value x 150ps)
            return SetRegMask(0x10E4, 0x000000F0, 4, value);
         default:
            throw std::invalid_argument("Function SetLmk2ClkoutDly() not defined for this board version");
      };
   };
   unsigned int GetLmk2ClkoutDlyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 2 Clock Output Delay (value x 150ps)
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x10E4;
         default:
            throw std::invalid_argument("Function GetLmk2ClkoutDlyLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK2_CLKOUT_EN
   unsigned int GetLmk2ClkoutEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 2 Clock Output Enable (0 = Disabled, 1 = Enabled)
            return BitExtractControl(0x10E4, 0x00010000, 16);
         default:
            throw std::invalid_argument("Function GetLmk2ClkoutEn() not defined for this board version");
      };
   };
   void SetLmk2ClkoutEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 2 Clock Output Enable (0 = Disabled, 1 = Enabled)
            return SetRegMask(0x10E4, 0x00010000, 16, value);
         default:
            throw std::invalid_argument("Function SetLmk2ClkoutEn() not defined for this board version");
      };
   };
   unsigned int GetLmk2ClkoutEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 2 Clock Output Enable (0 = Disabled, 1 = Enabled)
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x10E4;
         default:
            throw std::invalid_argument("Function GetLmk2ClkoutEnLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK2_CLKOUT_MUX
   unsigned int GetLmk2ClkoutMux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 2 Clock Output Multiplexer (see datasheet)
            return BitExtractControl(0x10E4, 0x00060000, 17);
         default:
            throw std::invalid_argument("Function GetLmk2ClkoutMux() not defined for this board version");
      };
   };
   void SetLmk2ClkoutMux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 2 Clock Output Multiplexer (see datasheet)
            return SetRegMask(0x10E4, 0x00060000, 17, value);
         default:
            throw std::invalid_argument("Function SetLmk2ClkoutMux() not defined for this board version");
      };
   };
   unsigned int GetLmk2ClkoutMuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 2 Clock Output Multiplexer (see datasheet)
            if(BitMask) *BitMask = 0x00060000;
            if(BitOfs) *BitOfs = 17;
            return 0x10E4;
         default:
            throw std::invalid_argument("Function GetLmk2ClkoutMuxLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK3_CLKOUT_DIV
   unsigned int GetLmk3ClkoutDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 3 Clock Output Divider (value x 2) (1..255)
            return BitExtractControl(0x10E8, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetLmk3ClkoutDiv() not defined for this board version");
      };
   };
   void SetLmk3ClkoutDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 3 Clock Output Divider (value x 2) (1..255)
            return SetRegMask(0x10E8, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetLmk3ClkoutDiv() not defined for this board version");
      };
   };
   unsigned int GetLmk3ClkoutDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 3 Clock Output Divider (value x 2) (1..255)
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x10E8;
         default:
            throw std::invalid_argument("Function GetLmk3ClkoutDivLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK3_CLKOUT_DLY
   unsigned int GetLmk3ClkoutDly()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 3 Clock Output Delay (value x 150ps)
            return BitExtractControl(0x10E8, 0x000000F0, 4);
         default:
            throw std::invalid_argument("Function GetLmk3ClkoutDly() not defined for this board version");
      };
   };
   void SetLmk3ClkoutDly(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 3 Clock Output Delay (value x 150ps)
            return SetRegMask(0x10E8, 0x000000F0, 4, value);
         default:
            throw std::invalid_argument("Function SetLmk3ClkoutDly() not defined for this board version");
      };
   };
   unsigned int GetLmk3ClkoutDlyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 3 Clock Output Delay (value x 150ps)
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x10E8;
         default:
            throw std::invalid_argument("Function GetLmk3ClkoutDlyLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK3_CLKOUT_EN
   unsigned int GetLmk3ClkoutEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 3 Clock Output Enable (0 = Disabled, 1 = Enabled)
            return BitExtractControl(0x10E8, 0x00010000, 16);
         default:
            throw std::invalid_argument("Function GetLmk3ClkoutEn() not defined for this board version");
      };
   };
   void SetLmk3ClkoutEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 3 Clock Output Enable (0 = Disabled, 1 = Enabled)
            return SetRegMask(0x10E8, 0x00010000, 16, value);
         default:
            throw std::invalid_argument("Function SetLmk3ClkoutEn() not defined for this board version");
      };
   };
   unsigned int GetLmk3ClkoutEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 3 Clock Output Enable (0 = Disabled, 1 = Enabled)
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x10E8;
         default:
            throw std::invalid_argument("Function GetLmk3ClkoutEnLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK3_CLKOUT_MUX
   unsigned int GetLmk3ClkoutMux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 3 Clock Output Multiplexer (see datasheet)
            return BitExtractControl(0x10E8, 0x00060000, 17);
         default:
            throw std::invalid_argument("Function GetLmk3ClkoutMux() not defined for this board version");
      };
   };
   void SetLmk3ClkoutMux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 3 Clock Output Multiplexer (see datasheet)
            return SetRegMask(0x10E8, 0x00060000, 17, value);
         default:
            throw std::invalid_argument("Function SetLmk3ClkoutMux() not defined for this board version");
      };
   };
   unsigned int GetLmk3ClkoutMuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 3 Clock Output Multiplexer (see datasheet)
            if(BitMask) *BitMask = 0x00060000;
            if(BitOfs) *BitOfs = 17;
            return 0x10E8;
         default:
            throw std::invalid_argument("Function GetLmk3ClkoutMuxLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK4_CLKOUT_DIV
   unsigned int GetLmk4ClkoutDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 4 Clock Output Divider (value x 2) (1..255)
            return BitExtractControl(0x10EC, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetLmk4ClkoutDiv() not defined for this board version");
      };
   };
   void SetLmk4ClkoutDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 4 Clock Output Divider (value x 2) (1..255)
            return SetRegMask(0x10EC, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetLmk4ClkoutDiv() not defined for this board version");
      };
   };
   unsigned int GetLmk4ClkoutDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 4 Clock Output Divider (value x 2) (1..255)
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x10EC;
         default:
            throw std::invalid_argument("Function GetLmk4ClkoutDivLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK4_CLKOUT_DLY
   unsigned int GetLmk4ClkoutDly()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 4 Clock Output Delay (value x 150ps)
            return BitExtractControl(0x10EC, 0x000000F0, 4);
         default:
            throw std::invalid_argument("Function GetLmk4ClkoutDly() not defined for this board version");
      };
   };
   void SetLmk4ClkoutDly(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 4 Clock Output Delay (value x 150ps)
            return SetRegMask(0x10EC, 0x000000F0, 4, value);
         default:
            throw std::invalid_argument("Function SetLmk4ClkoutDly() not defined for this board version");
      };
   };
   unsigned int GetLmk4ClkoutDlyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 4 Clock Output Delay (value x 150ps)
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x10EC;
         default:
            throw std::invalid_argument("Function GetLmk4ClkoutDlyLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK4_CLKOUT_EN
   unsigned int GetLmk4ClkoutEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 4 Clock Output Enable (0 = Disabled, 1 = Enabled)
            return BitExtractControl(0x10EC, 0x00010000, 16);
         default:
            throw std::invalid_argument("Function GetLmk4ClkoutEn() not defined for this board version");
      };
   };
   void SetLmk4ClkoutEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 4 Clock Output Enable (0 = Disabled, 1 = Enabled)
            return SetRegMask(0x10EC, 0x00010000, 16, value);
         default:
            throw std::invalid_argument("Function SetLmk4ClkoutEn() not defined for this board version");
      };
   };
   unsigned int GetLmk4ClkoutEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 4 Clock Output Enable (0 = Disabled, 1 = Enabled)
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x10EC;
         default:
            throw std::invalid_argument("Function GetLmk4ClkoutEnLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK4_CLKOUT_MUX
   unsigned int GetLmk4ClkoutMux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 4 Clock Output Multiplexer (see datasheet)
            return BitExtractControl(0x10EC, 0x00060000, 17);
         default:
            throw std::invalid_argument("Function GetLmk4ClkoutMux() not defined for this board version");
      };
   };
   void SetLmk4ClkoutMux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 4 Clock Output Multiplexer (see datasheet)
            return SetRegMask(0x10EC, 0x00060000, 17, value);
         default:
            throw std::invalid_argument("Function SetLmk4ClkoutMux() not defined for this board version");
      };
   };
   unsigned int GetLmk4ClkoutMuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 4 Clock Output Multiplexer (see datasheet)
            if(BitMask) *BitMask = 0x00060000;
            if(BitOfs) *BitOfs = 17;
            return 0x10EC;
         default:
            throw std::invalid_argument("Function GetLmk4ClkoutMuxLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK5_CLKOUT_DIV
   unsigned int GetLmk5ClkoutDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 5 Clock Output Divider (value x 2) (1..255)
            return BitExtractControl(0x10F0, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetLmk5ClkoutDiv() not defined for this board version");
      };
   };
   void SetLmk5ClkoutDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 5 Clock Output Divider (value x 2) (1..255)
            return SetRegMask(0x10F0, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetLmk5ClkoutDiv() not defined for this board version");
      };
   };
   unsigned int GetLmk5ClkoutDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 5 Clock Output Divider (value x 2) (1..255)
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x10F0;
         default:
            throw std::invalid_argument("Function GetLmk5ClkoutDivLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK5_CLKOUT_DLY
   unsigned int GetLmk5ClkoutDly()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 5 Clock Output Delay (value x 150ps)
            return BitExtractControl(0x10F0, 0x000000F0, 4);
         default:
            throw std::invalid_argument("Function GetLmk5ClkoutDly() not defined for this board version");
      };
   };
   void SetLmk5ClkoutDly(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 5 Clock Output Delay (value x 150ps)
            return SetRegMask(0x10F0, 0x000000F0, 4, value);
         default:
            throw std::invalid_argument("Function SetLmk5ClkoutDly() not defined for this board version");
      };
   };
   unsigned int GetLmk5ClkoutDlyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 5 Clock Output Delay (value x 150ps)
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x10F0;
         default:
            throw std::invalid_argument("Function GetLmk5ClkoutDlyLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK5_CLKOUT_EN
   unsigned int GetLmk5ClkoutEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 5 Clock Output Enable (0 = Disabled, 1 = Enabled)
            return BitExtractControl(0x10F0, 0x00010000, 16);
         default:
            throw std::invalid_argument("Function GetLmk5ClkoutEn() not defined for this board version");
      };
   };
   void SetLmk5ClkoutEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 5 Clock Output Enable (0 = Disabled, 1 = Enabled)
            return SetRegMask(0x10F0, 0x00010000, 16, value);
         default:
            throw std::invalid_argument("Function SetLmk5ClkoutEn() not defined for this board version");
      };
   };
   unsigned int GetLmk5ClkoutEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 5 Clock Output Enable (0 = Disabled, 1 = Enabled)
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x10F0;
         default:
            throw std::invalid_argument("Function GetLmk5ClkoutEnLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK5_CLKOUT_MUX
   unsigned int GetLmk5ClkoutMux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 5 Clock Output Multiplexer (see datasheet)
            return BitExtractControl(0x10F0, 0x00060000, 17);
         default:
            throw std::invalid_argument("Function GetLmk5ClkoutMux() not defined for this board version");
      };
   };
   void SetLmk5ClkoutMux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 5 Clock Output Multiplexer (see datasheet)
            return SetRegMask(0x10F0, 0x00060000, 17, value);
         default:
            throw std::invalid_argument("Function SetLmk5ClkoutMux() not defined for this board version");
      };
   };
   unsigned int GetLmk5ClkoutMuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 5 Clock Output Multiplexer (see datasheet)
            if(BitMask) *BitMask = 0x00060000;
            if(BitOfs) *BitOfs = 17;
            return 0x10F0;
         default:
            throw std::invalid_argument("Function GetLmk5ClkoutMuxLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK6_CLKOUT_DIV
   unsigned int GetLmk6ClkoutDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 6 Clock Output Divider (value x 2) (1..255)
            return BitExtractControl(0x10F4, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetLmk6ClkoutDiv() not defined for this board version");
      };
   };
   void SetLmk6ClkoutDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 6 Clock Output Divider (value x 2) (1..255)
            return SetRegMask(0x10F4, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetLmk6ClkoutDiv() not defined for this board version");
      };
   };
   unsigned int GetLmk6ClkoutDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 6 Clock Output Divider (value x 2) (1..255)
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x10F4;
         default:
            throw std::invalid_argument("Function GetLmk6ClkoutDivLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK6_CLKOUT_DLY
   unsigned int GetLmk6ClkoutDly()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 6 Clock Output Delay (value x 150ps)
            return BitExtractControl(0x10F4, 0x000000F0, 4);
         default:
            throw std::invalid_argument("Function GetLmk6ClkoutDly() not defined for this board version");
      };
   };
   void SetLmk6ClkoutDly(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 6 Clock Output Delay (value x 150ps)
            return SetRegMask(0x10F4, 0x000000F0, 4, value);
         default:
            throw std::invalid_argument("Function SetLmk6ClkoutDly() not defined for this board version");
      };
   };
   unsigned int GetLmk6ClkoutDlyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 6 Clock Output Delay (value x 150ps)
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x10F4;
         default:
            throw std::invalid_argument("Function GetLmk6ClkoutDlyLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK6_CLKOUT_EN
   unsigned int GetLmk6ClkoutEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 6 Clock Output Enable (0 = Disabled, 1 = Enabled)
            return BitExtractControl(0x10F4, 0x00010000, 16);
         default:
            throw std::invalid_argument("Function GetLmk6ClkoutEn() not defined for this board version");
      };
   };
   void SetLmk6ClkoutEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 6 Clock Output Enable (0 = Disabled, 1 = Enabled)
            return SetRegMask(0x10F4, 0x00010000, 16, value);
         default:
            throw std::invalid_argument("Function SetLmk6ClkoutEn() not defined for this board version");
      };
   };
   unsigned int GetLmk6ClkoutEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 6 Clock Output Enable (0 = Disabled, 1 = Enabled)
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x10F4;
         default:
            throw std::invalid_argument("Function GetLmk6ClkoutEnLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK6_CLKOUT_MUX
   unsigned int GetLmk6ClkoutMux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 6 Clock Output Multiplexer (see datasheet)
            return BitExtractControl(0x10F4, 0x00060000, 17);
         default:
            throw std::invalid_argument("Function GetLmk6ClkoutMux() not defined for this board version");
      };
   };
   void SetLmk6ClkoutMux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 6 Clock Output Multiplexer (see datasheet)
            return SetRegMask(0x10F4, 0x00060000, 17, value);
         default:
            throw std::invalid_argument("Function SetLmk6ClkoutMux() not defined for this board version");
      };
   };
   unsigned int GetLmk6ClkoutMuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 6 Clock Output Multiplexer (see datasheet)
            if(BitMask) *BitMask = 0x00060000;
            if(BitOfs) *BitOfs = 17;
            return 0x10F4;
         default:
            throw std::invalid_argument("Function GetLmk6ClkoutMuxLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK7_CLKOUT_DIV
   unsigned int GetLmk7ClkoutDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 7 Clock Output Divider (value x 2) (1..255)
            return BitExtractControl(0x10F8, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetLmk7ClkoutDiv() not defined for this board version");
      };
   };
   void SetLmk7ClkoutDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 7 Clock Output Divider (value x 2) (1..255)
            return SetRegMask(0x10F8, 0x0000FF00, 8, value);
         default:
            throw std::invalid_argument("Function SetLmk7ClkoutDiv() not defined for this board version");
      };
   };
   unsigned int GetLmk7ClkoutDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 7 Clock Output Divider (value x 2) (1..255)
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x10F8;
         default:
            throw std::invalid_argument("Function GetLmk7ClkoutDivLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK7_CLKOUT_DLY
   unsigned int GetLmk7ClkoutDly()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 7 Clock Output Delay (value x 150ps)
            return BitExtractControl(0x10F8, 0x000000F0, 4);
         default:
            throw std::invalid_argument("Function GetLmk7ClkoutDly() not defined for this board version");
      };
   };
   void SetLmk7ClkoutDly(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 7 Clock Output Delay (value x 150ps)
            return SetRegMask(0x10F8, 0x000000F0, 4, value);
         default:
            throw std::invalid_argument("Function SetLmk7ClkoutDly() not defined for this board version");
      };
   };
   unsigned int GetLmk7ClkoutDlyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 7 Clock Output Delay (value x 150ps)
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x10F8;
         default:
            throw std::invalid_argument("Function GetLmk7ClkoutDlyLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK7_CLKOUT_EN
   unsigned int GetLmk7ClkoutEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 7 Clock Output Enable (0 = Disabled, 1 = Enabled)
            return BitExtractControl(0x10F8, 0x00010000, 16);
         default:
            throw std::invalid_argument("Function GetLmk7ClkoutEn() not defined for this board version");
      };
   };
   void SetLmk7ClkoutEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 7 Clock Output Enable (0 = Disabled, 1 = Enabled)
            return SetRegMask(0x10F8, 0x00010000, 16, value);
         default:
            throw std::invalid_argument("Function SetLmk7ClkoutEn() not defined for this board version");
      };
   };
   unsigned int GetLmk7ClkoutEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 7 Clock Output Enable (0 = Disabled, 1 = Enabled)
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x10F8;
         default:
            throw std::invalid_argument("Function GetLmk7ClkoutEnLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK7_CLKOUT_MUX
   unsigned int GetLmk7ClkoutMux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 7 Clock Output Multiplexer (see datasheet)
            return BitExtractControl(0x10F8, 0x00060000, 17);
         default:
            throw std::invalid_argument("Function GetLmk7ClkoutMux() not defined for this board version");
      };
   };
   void SetLmk7ClkoutMux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 7 Clock Output Multiplexer (see datasheet)
            return SetRegMask(0x10F8, 0x00060000, 17, value);
         default:
            throw std::invalid_argument("Function SetLmk7ClkoutMux() not defined for this board version");
      };
   };
   unsigned int GetLmk7ClkoutMuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Channel 7 Clock Output Multiplexer (see datasheet)
            if(BitMask) *BitMask = 0x00060000;
            if(BitOfs) *BitOfs = 17;
            return 0x10F8;
         default:
            throw std::invalid_argument("Function GetLmk7ClkoutMuxLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK8_PHASE_NOISE_OPT
   unsigned int GetLmk8PhaseNoiseOpt()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set LMK Register 8 (Phase Noise Optimization)
            return BitExtractControl(0x10FC, 0xFFFFFFF0, 4);
         default:
            throw std::invalid_argument("Function GetLmk8PhaseNoiseOpt() not defined for this board version");
      };
   };
   void SetLmk8PhaseNoiseOpt(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set LMK Register 8 (Phase Noise Optimization)
            return SetRegMask(0x10FC, 0xFFFFFFF0, 4, value);
         default:
            throw std::invalid_argument("Function SetLmk8PhaseNoiseOpt() not defined for this board version");
      };
   };
   unsigned int GetLmk8PhaseNoiseOptLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Set LMK Register 8 (Phase Noise Optimization)
            if(BitMask) *BitMask = 0xFFFFFFF0;
            if(BitOfs) *BitOfs = 4;
            return 0x10FC;
         default:
            throw std::invalid_argument("Function GetLmk8PhaseNoiseOptLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK9_VBOOST
   unsigned int GetLmk9Vboost()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Voltage Level Boost for Clock Outputs
            return BitExtractControl(0x1100, 0x00010000, 16);
         default:
            throw std::invalid_argument("Function GetLmk9Vboost() not defined for this board version");
      };
   };
   void SetLmk9Vboost(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Voltage Level Boost for Clock Outputs
            return SetRegMask(0x1100, 0x00010000, 16, value);
         default:
            throw std::invalid_argument("Function SetLmk9Vboost() not defined for this board version");
      };
   };
   unsigned int GetLmk9VboostLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Voltage Level Boost for Clock Outputs
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x1100;
         default:
            throw std::invalid_argument("Function GetLmk9VboostLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK_0_MOD
   unsigned int GetLmk0Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK channel 0 register modified flags
            return BitExtractStatus(0x0160, 0xF0000000, 28);
         case 9:
            // LMK channel 0 register modified flags
            return BitExtractStatus(0x015C, 0xF0000000, 28);
         default:
            throw std::invalid_argument("Function GetLmk0Mod() not defined for this board version");
      };
   };
   unsigned int GetLmk0ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK channel 0 register modified flags
            if(BitMask) *BitMask = 0xF0000000;
            if(BitOfs) *BitOfs = 28;
            return 0x0160;
         case 9:
            // LMK channel 0 register modified flags
            if(BitMask) *BitMask = 0xF0000000;
            if(BitOfs) *BitOfs = 28;
            return 0x015C;
         default:
            throw std::invalid_argument("Function GetLmk0ModLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK_11_MOD
   unsigned int GetLmk11Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK Register 11 modified flags
            return BitExtractStatus(0x0164, 0x0000F000, 12);
         case 9:
            // LMK Register 11 modified flags
            return BitExtractStatus(0x0160, 0x0000F000, 12);
         default:
            throw std::invalid_argument("Function GetLmk11Mod() not defined for this board version");
      };
   };
   unsigned int GetLmk11ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK Register 11 modified flags
            if(BitMask) *BitMask = 0x0000F000;
            if(BitOfs) *BitOfs = 12;
            return 0x0164;
         case 9:
            // LMK Register 11 modified flags
            if(BitMask) *BitMask = 0x0000F000;
            if(BitOfs) *BitOfs = 12;
            return 0x0160;
         default:
            throw std::invalid_argument("Function GetLmk11ModLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK_13_MOD
   unsigned int GetLmk13Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK Register 13 modified flags
            return BitExtractStatus(0x0164, 0x00000F00, 8);
         case 9:
            // LMK Register 13 modified flags
            return BitExtractStatus(0x0160, 0x00000F00, 8);
         default:
            throw std::invalid_argument("Function GetLmk13Mod() not defined for this board version");
      };
   };
   unsigned int GetLmk13ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK Register 13 modified flags
            if(BitMask) *BitMask = 0x00000F00;
            if(BitOfs) *BitOfs = 8;
            return 0x0164;
         case 9:
            // LMK Register 13 modified flags
            if(BitMask) *BitMask = 0x00000F00;
            if(BitOfs) *BitOfs = 8;
            return 0x0160;
         default:
            throw std::invalid_argument("Function GetLmk13ModLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK_14_MOD
   unsigned int GetLmk14Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK Register 14 modified flags
            return BitExtractStatus(0x0164, 0x000000F0, 4);
         case 9:
            // LMK Register 14 modified flags
            return BitExtractStatus(0x0160, 0x000000F0, 4);
         default:
            throw std::invalid_argument("Function GetLmk14Mod() not defined for this board version");
      };
   };
   unsigned int GetLmk14ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK Register 14 modified flags
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x0164;
         case 9:
            // LMK Register 14 modified flags
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x0160;
         default:
            throw std::invalid_argument("Function GetLmk14ModLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK_15_MOD
   unsigned int GetLmk15Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK Register 15 modified flags
            return BitExtractStatus(0x0164, 0x0000000F, 0);
         case 9:
            // LMK Register 15 modified flags
            return BitExtractStatus(0x0160, 0x0000000F, 0);
         default:
            throw std::invalid_argument("Function GetLmk15Mod() not defined for this board version");
      };
   };
   unsigned int GetLmk15ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK Register 15 modified flags
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0164;
         case 9:
            // LMK Register 15 modified flags
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0160;
         default:
            throw std::invalid_argument("Function GetLmk15ModLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK_1_MOD
   unsigned int GetLmk1Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK channel 1 register modified flags
            return BitExtractStatus(0x0160, 0x0F000000, 24);
         case 9:
            // LMK channel 1 register modified flags
            return BitExtractStatus(0x015C, 0x0F000000, 24);
         default:
            throw std::invalid_argument("Function GetLmk1Mod() not defined for this board version");
      };
   };
   unsigned int GetLmk1ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK channel 1 register modified flags
            if(BitMask) *BitMask = 0x0F000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0160;
         case 9:
            // LMK channel 1 register modified flags
            if(BitMask) *BitMask = 0x0F000000;
            if(BitOfs) *BitOfs = 24;
            return 0x015C;
         default:
            throw std::invalid_argument("Function GetLmk1ModLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK_2_MOD
   unsigned int GetLmk2Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK channel 2 register modified flags
            return BitExtractStatus(0x0160, 0x00F00000, 20);
         case 9:
            // LMK channel 2 register modified flags
            return BitExtractStatus(0x015C, 0x00F00000, 20);
         default:
            throw std::invalid_argument("Function GetLmk2Mod() not defined for this board version");
      };
   };
   unsigned int GetLmk2ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK channel 2 register modified flags
            if(BitMask) *BitMask = 0x00F00000;
            if(BitOfs) *BitOfs = 20;
            return 0x0160;
         case 9:
            // LMK channel 2 register modified flags
            if(BitMask) *BitMask = 0x00F00000;
            if(BitOfs) *BitOfs = 20;
            return 0x015C;
         default:
            throw std::invalid_argument("Function GetLmk2ModLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK_3_MOD
   unsigned int GetLmk3Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK channel 3 register modified flags
            return BitExtractStatus(0x0160, 0x000F0000, 16);
         case 9:
            // LMK channel 3 register modified flags
            return BitExtractStatus(0x015C, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetLmk3Mod() not defined for this board version");
      };
   };
   unsigned int GetLmk3ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK channel 3 register modified flags
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0160;
         case 9:
            // LMK channel 3 register modified flags
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x015C;
         default:
            throw std::invalid_argument("Function GetLmk3ModLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK_4_MOD
   unsigned int GetLmk4Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK channel 4 register modified flags
            return BitExtractStatus(0x0160, 0x0000F000, 12);
         case 9:
            // LMK channel 4 register modified flags
            return BitExtractStatus(0x015C, 0x0000F000, 12);
         default:
            throw std::invalid_argument("Function GetLmk4Mod() not defined for this board version");
      };
   };
   unsigned int GetLmk4ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK channel 4 register modified flags
            if(BitMask) *BitMask = 0x0000F000;
            if(BitOfs) *BitOfs = 12;
            return 0x0160;
         case 9:
            // LMK channel 4 register modified flags
            if(BitMask) *BitMask = 0x0000F000;
            if(BitOfs) *BitOfs = 12;
            return 0x015C;
         default:
            throw std::invalid_argument("Function GetLmk4ModLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK_5_MOD
   unsigned int GetLmk5Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK channel 5 register modified flags
            return BitExtractStatus(0x0160, 0x00000F00, 8);
         case 9:
            // LMK channel 5 register modified flags
            return BitExtractStatus(0x015C, 0x00000F00, 8);
         default:
            throw std::invalid_argument("Function GetLmk5Mod() not defined for this board version");
      };
   };
   unsigned int GetLmk5ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK channel 5 register modified flags
            if(BitMask) *BitMask = 0x00000F00;
            if(BitOfs) *BitOfs = 8;
            return 0x0160;
         case 9:
            // LMK channel 5 register modified flags
            if(BitMask) *BitMask = 0x00000F00;
            if(BitOfs) *BitOfs = 8;
            return 0x015C;
         default:
            throw std::invalid_argument("Function GetLmk5ModLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK_6_MOD
   unsigned int GetLmk6Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK channel 6 register modified flags
            return BitExtractStatus(0x0160, 0x000000F0, 4);
         case 9:
            // LMK channel 6 register modified flags
            return BitExtractStatus(0x015C, 0x000000F0, 4);
         default:
            throw std::invalid_argument("Function GetLmk6Mod() not defined for this board version");
      };
   };
   unsigned int GetLmk6ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK channel 6 register modified flags
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x0160;
         case 9:
            // LMK channel 6 register modified flags
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x015C;
         default:
            throw std::invalid_argument("Function GetLmk6ModLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK_7_MOD
   unsigned int GetLmk7Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK channel 7 register modified flags
            return BitExtractStatus(0x0160, 0x0000000F, 0);
         case 9:
            // LMK channel 7 register modified flags
            return BitExtractStatus(0x015C, 0x0000000F, 0);
         default:
            throw std::invalid_argument("Function GetLmk7Mod() not defined for this board version");
      };
   };
   unsigned int GetLmk7ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK channel 7 register modified flags
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0160;
         case 9:
            // LMK channel 7 register modified flags
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x015C;
         default:
            throw std::invalid_argument("Function GetLmk7ModLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK_8_MOD
   unsigned int GetLmk8Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK Register 8 modified flags
            return BitExtractStatus(0x0164, 0x00F00000, 20);
         case 9:
            // LMK Register 8 modified flags
            return BitExtractStatus(0x0160, 0x00F00000, 20);
         default:
            throw std::invalid_argument("Function GetLmk8Mod() not defined for this board version");
      };
   };
   unsigned int GetLmk8ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK Register 8 modified flags
            if(BitMask) *BitMask = 0x00F00000;
            if(BitOfs) *BitOfs = 20;
            return 0x0164;
         case 9:
            // LMK Register 8 modified flags
            if(BitMask) *BitMask = 0x00F00000;
            if(BitOfs) *BitOfs = 20;
            return 0x0160;
         default:
            throw std::invalid_argument("Function GetLmk8ModLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK_9_MOD
   unsigned int GetLmk9Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK Register 9 modified flags
            return BitExtractStatus(0x0164, 0x000F0000, 16);
         case 9:
            // LMK Register 9 modified flags
            return BitExtractStatus(0x0160, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetLmk9Mod() not defined for this board version");
      };
   };
   unsigned int GetLmk9ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // LMK Register 9 modified flags
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0164;
         case 9:
            // LMK Register 9 modified flags
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0160;
         default:
            throw std::invalid_argument("Function GetLmk9ModLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK_PLL_LOCK
   unsigned int GetLmkPllLock()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // PLL lock signal of LMK (external)
            return BitExtractStatus(0x002C, 0x00000001, 0);
         default:
            throw std::invalid_argument("Function GetLmkPllLock() not defined for this board version");
      };
   };
   unsigned int GetLmkPllLockLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // PLL lock signal of LMK (external)
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x002C;
         default:
            throw std::invalid_argument("Function GetLmkPllLockLoc() not defined for this board version");
      };
   };

   // Bit(s) LMK_SYNC_LOCAL
   unsigned int GetLmkSyncLocal()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Control LMK SYNC signal from FPGA: 0 = run / 1 = sync
            return BitExtractControl(0x1040, 0x00000080, 7);
         default:
            throw std::invalid_argument("Function GetLmkSyncLocal() not defined for this board version");
      };
   };
   void SetLmkSyncLocal(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Control LMK SYNC signal from FPGA: 0 = run / 1 = sync
            return SetRegMask(0x1040, 0x00000080, 7, value);
         default:
            throw std::invalid_argument("Function SetLmkSyncLocal() not defined for this board version");
      };
   };
   unsigned int GetLmkSyncLocalLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Control LMK SYNC signal from FPGA: 0 = run / 1 = sync
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x1040;
         default:
            throw std::invalid_argument("Function GetLmkSyncLocalLoc() not defined for this board version");
      };
   };

   // Bit(s) LOCAL_CLK_FREQ
   unsigned int GetLocalClkFreq()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Local (on board) oscillator frequency in MHz
            return BitExtractControl(0x100C, 0x000000FF, 0);
         default:
            throw std::invalid_argument("Function GetLocalClkFreq() not defined for this board version");
      };
   };
   void SetLocalClkFreq(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Local (on board) oscillator frequency in MHz
            return SetRegMask(0x100C, 0x000000FF, 0, value);
         default:
            throw std::invalid_argument("Function SetLocalClkFreq() not defined for this board version");
      };
   };
   unsigned int GetLocalClkFreqLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Local (on board) oscillator frequency in MHz
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x100C;
         default:
            throw std::invalid_argument("Function GetLocalClkFreqLoc() not defined for this board version");
      };
   };

   // Bit(s) LOCAL_CLK_FREQ_MOD
   unsigned int GetLocalClkFreqMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Local clock frequency modified flags
            return BitExtractStatus(0x0138, 0x00000001, 0);
         case 9:
            // Local clock frequency modified flags
            return BitExtractStatus(0x0134, 0x00000001, 0);
         default:
            throw std::invalid_argument("Function GetLocalClkFreqMod() not defined for this board version");
      };
   };
   unsigned int GetLocalClkFreqModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Local clock frequency modified flags
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x0138;
         case 9:
            // Local clock frequency modified flags
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x0134;
         default:
            throw std::invalid_argument("Function GetLocalClkFreqModLoc() not defined for this board version");
      };
   };

   // Bit(s) MAX_DRS_ADC_PKT_SAMPLES
   unsigned int GetMaxDrsAdcPktSamples()
   {
      switch(this->mVersion)
      {
         case 8:
            // Maximum number of DRS/ADC samples per packet
            return BitExtractStatus(0x0128, 0x0000FFFF, 0);
         case 9:
            // Maximum number of DRS/ADC samples per packet
            return BitExtractStatus(0x0124, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetMaxDrsAdcPktSamples() not defined for this board version");
      };
   };
   unsigned int GetMaxDrsAdcPktSamplesLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Maximum number of DRS/ADC samples per packet
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0128;
         case 9:
            // Maximum number of DRS/ADC samples per packet
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0124;
         default:
            throw std::invalid_argument("Function GetMaxDrsAdcPktSamplesLoc() not defined for this board version");
      };
   };

   // Bit(s) MAX_SCL_PKT_SAMPLES
   unsigned int GetMaxSclPktSamples()
   {
      switch(this->mVersion)
      {
         case 8:
            // Maximum number of scaler values per packet
            return BitExtractStatus(0x0134, 0x0000FFFF, 0);
         case 9:
            // Maximum number of scaler values per packet
            return BitExtractStatus(0x0130, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetMaxSclPktSamples() not defined for this board version");
      };
   };
   unsigned int GetMaxSclPktSamplesLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Maximum number of scaler values per packet
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0134;
         case 9:
            // Maximum number of scaler values per packet
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0130;
         default:
            throw std::invalid_argument("Function GetMaxSclPktSamplesLoc() not defined for this board version");
      };
   };

   // Bit(s) MAX_TDC_PKT_SAMPLES
   unsigned int GetMaxTdcPktSamples()
   {
      switch(this->mVersion)
      {
         case 8:
            // Maximum number of TDC samples per packet
            return BitExtractStatus(0x012C, 0x0003FFFF, 0);
         case 9:
            // Maximum number of TDC samples per packet
            return BitExtractStatus(0x0128, 0x0003FFFF, 0);
         default:
            throw std::invalid_argument("Function GetMaxTdcPktSamples() not defined for this board version");
      };
   };
   unsigned int GetMaxTdcPktSamplesLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Maximum number of TDC samples per packet
            if(BitMask) *BitMask = 0x0003FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x012C;
         case 9:
            // Maximum number of TDC samples per packet
            if(BitMask) *BitMask = 0x0003FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0128;
         default:
            throw std::invalid_argument("Function GetMaxTdcPktSamplesLoc() not defined for this board version");
      };
   };

   // Bit(s) MAX_TRG_PKT_SAMPLES
   unsigned int GetMaxTrgPktSamples()
   {
      switch(this->mVersion)
      {
         case 8:
            // Maximum number of advanced trigger output samples per packet
            return BitExtractStatus(0x0130, 0x0000FFFF, 0);
         case 9:
            // Maximum number of advanced trigger output samples per packet
            return BitExtractStatus(0x012C, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetMaxTrgPktSamples() not defined for this board version");
      };
   };
   unsigned int GetMaxTrgPktSamplesLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Maximum number of advanced trigger output samples per packet
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0130;
         case 9:
            // Maximum number of advanced trigger output samples per packet
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x012C;
         default:
            throw std::invalid_argument("Function GetMaxTrgPktSamplesLoc() not defined for this board version");
      };
   };

   // Bit(s) MCX_RX_SIG_SEL
   unsigned int GetMcxRxSigSel()
   {
      switch(this->mVersion)
      {
         case 8:
            // Select for RX connector: / 0x0 = UART (communication to MicroBlaze) / 0x1 = Trigger (internal hardware trigger signal to DRS control FSM) / 0x2 = Soft Trigger (trigger signal from MicroBlaze) / 0x3 = External Trigger (OR connection of external trigger from MCX and Backplane) / 0x4 = Sync Signal from Backplane (direct, active high) / 0x5 = Sync Signal from Backplane (sampled, output to LMK, active low) / 0x6 = Sync Signal from Backplane (sampled, used for internal logic, active high) / 0x7 = Busy Local (active high) / 0x8 = Busy from Backplane (active high) / 0x9 = LMK Reference Clock (LMK input clock)  / 0xA = ADC Sampling Clock  / 0xB = Divided Data Clock (phase shifted) / 0xC = LMK5 clock (directly routed from corresponding input) / 0xD = SPI CS of LMK (active low)
            return BitExtractControl(0x1280, 0x0000000F, 0);
         case 9:
            // Select for RX connector: / 0x0 = UART (communication to MicroBlaze) / 0x1 = Trigger (internal hardware trigger signal to DRS control FSM) / 0x2 = Soft Trigger (trigger signal from MicroBlaze) / 0x3 = External Trigger (OR connection of external trigger from MCX and Backplane) / 0x4 = Sync Signal from Backplane (direct, active high) / 0x5 = Sync Signal from Backplane (sampled, output to LMK, active low) / 0x6 = Sync Signal from Backplane (sampled, used for internal logic, active high) / 0x7 = Busy Local (active high) / 0x8 = Busy from Backplane (active high) / 0x9 = LMK Reference Clock (LMK input clock)  / 0xA = ADC Sampling Clock  / 0xB = Divided Data Clock (phase shifted) / 0xC = LMK5 clock (directly routed from corresponding input) / 0xD = SPI CS of LMK (active low)
            return BitExtractControl(0x1224, 0x0000000F, 0);
         default:
            throw std::invalid_argument("Function GetMcxRxSigSel() not defined for this board version");
      };
   };
   void SetMcxRxSigSel(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Select for RX connector: / 0x0 = UART (communication to MicroBlaze) / 0x1 = Trigger (internal hardware trigger signal to DRS control FSM) / 0x2 = Soft Trigger (trigger signal from MicroBlaze) / 0x3 = External Trigger (OR connection of external trigger from MCX and Backplane) / 0x4 = Sync Signal from Backplane (direct, active high) / 0x5 = Sync Signal from Backplane (sampled, output to LMK, active low) / 0x6 = Sync Signal from Backplane (sampled, used for internal logic, active high) / 0x7 = Busy Local (active high) / 0x8 = Busy from Backplane (active high) / 0x9 = LMK Reference Clock (LMK input clock)  / 0xA = ADC Sampling Clock  / 0xB = Divided Data Clock (phase shifted) / 0xC = LMK5 clock (directly routed from corresponding input) / 0xD = SPI CS of LMK (active low)
            return SetRegMask(0x1280, 0x0000000F, 0, value);
         case 9:
            // Select for RX connector: / 0x0 = UART (communication to MicroBlaze) / 0x1 = Trigger (internal hardware trigger signal to DRS control FSM) / 0x2 = Soft Trigger (trigger signal from MicroBlaze) / 0x3 = External Trigger (OR connection of external trigger from MCX and Backplane) / 0x4 = Sync Signal from Backplane (direct, active high) / 0x5 = Sync Signal from Backplane (sampled, output to LMK, active low) / 0x6 = Sync Signal from Backplane (sampled, used for internal logic, active high) / 0x7 = Busy Local (active high) / 0x8 = Busy from Backplane (active high) / 0x9 = LMK Reference Clock (LMK input clock)  / 0xA = ADC Sampling Clock  / 0xB = Divided Data Clock (phase shifted) / 0xC = LMK5 clock (directly routed from corresponding input) / 0xD = SPI CS of LMK (active low)
            return SetRegMask(0x1224, 0x0000000F, 0, value);
         default:
            throw std::invalid_argument("Function SetMcxRxSigSel() not defined for this board version");
      };
   };
   unsigned int GetMcxRxSigSelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Select for RX connector: / 0x0 = UART (communication to MicroBlaze) / 0x1 = Trigger (internal hardware trigger signal to DRS control FSM) / 0x2 = Soft Trigger (trigger signal from MicroBlaze) / 0x3 = External Trigger (OR connection of external trigger from MCX and Backplane) / 0x4 = Sync Signal from Backplane (direct, active high) / 0x5 = Sync Signal from Backplane (sampled, output to LMK, active low) / 0x6 = Sync Signal from Backplane (sampled, used for internal logic, active high) / 0x7 = Busy Local (active high) / 0x8 = Busy from Backplane (active high) / 0x9 = LMK Reference Clock (LMK input clock)  / 0xA = ADC Sampling Clock  / 0xB = Divided Data Clock (phase shifted) / 0xC = LMK5 clock (directly routed from corresponding input) / 0xD = SPI CS of LMK (active low)
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x1280;
         case 9:
            // Select for RX connector: / 0x0 = UART (communication to MicroBlaze) / 0x1 = Trigger (internal hardware trigger signal to DRS control FSM) / 0x2 = Soft Trigger (trigger signal from MicroBlaze) / 0x3 = External Trigger (OR connection of external trigger from MCX and Backplane) / 0x4 = Sync Signal from Backplane (direct, active high) / 0x5 = Sync Signal from Backplane (sampled, output to LMK, active low) / 0x6 = Sync Signal from Backplane (sampled, used for internal logic, active high) / 0x7 = Busy Local (active high) / 0x8 = Busy from Backplane (active high) / 0x9 = LMK Reference Clock (LMK input clock)  / 0xA = ADC Sampling Clock  / 0xB = Divided Data Clock (phase shifted) / 0xC = LMK5 clock (directly routed from corresponding input) / 0xD = SPI CS of LMK (active low)
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x1224;
         default:
            throw std::invalid_argument("Function GetMcxRxSigSelLoc() not defined for this board version");
      };
   };

   // Bit(s) MCX_TX_SIG_SEL
   unsigned int GetMcxTxSigSel()
   {
      switch(this->mVersion)
      {
         case 8:
            // Select for TX connector (see RX connector for mapping)
            return BitExtractControl(0x1280, 0x000F0000, 16);
         case 9:
            // Select for TX connector (see RX connector for mapping)
            return BitExtractControl(0x1224, 0x000F0000, 16);
         default:
            throw std::invalid_argument("Function GetMcxTxSigSel() not defined for this board version");
      };
   };
   void SetMcxTxSigSel(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Select for TX connector (see RX connector for mapping)
            return SetRegMask(0x1280, 0x000F0000, 16, value);
         case 9:
            // Select for TX connector (see RX connector for mapping)
            return SetRegMask(0x1224, 0x000F0000, 16, value);
         default:
            throw std::invalid_argument("Function SetMcxTxSigSel() not defined for this board version");
      };
   };
   unsigned int GetMcxTxSigSelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Select for TX connector (see RX connector for mapping)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1280;
         case 9:
            // Select for TX connector (see RX connector for mapping)
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1224;
         default:
            throw std::invalid_argument("Function GetMcxTxSigSelLoc() not defined for this board version");
      };
   };

   // Bit(s) OSERDES_PLL_LOCK_DCB
   unsigned int GetOserdesPllLockDcb()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Lock of PLL for OSERDES to DCB (FPGA internal)
            return BitExtractStatus(0x002C, 0x00000040, 6);
         default:
            throw std::invalid_argument("Function GetOserdesPllLockDcb() not defined for this board version");
      };
   };
   unsigned int GetOserdesPllLockDcbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Lock of PLL for OSERDES to DCB (FPGA internal)
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x002C;
         default:
            throw std::invalid_argument("Function GetOserdesPllLockDcbLoc() not defined for this board version");
      };
   };

   // Bit(s) OSERDES_PLL_LOCK_TCB
   unsigned int GetOserdesPllLockTcb()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Lock of PLL for OSERDES to TCB (FPGA internal)
            return BitExtractStatus(0x002C, 0x00000020, 5);
         default:
            throw std::invalid_argument("Function GetOserdesPllLockTcb() not defined for this board version");
      };
   };
   unsigned int GetOserdesPllLockTcbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Lock of PLL for OSERDES to TCB (FPGA internal)
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x002C;
         default:
            throw std::invalid_argument("Function GetOserdesPllLockTcbLoc() not defined for this board version");
      };
   };

   // Bit(s) OVERTEMP
   unsigned int GetOvertemp()
   {
      switch(this->mVersion)
      {
         case 9:
            // Overtemperature from external sensor
            return BitExtractStatus(0x0028, 0x00008000, 15);
         default:
            throw std::invalid_argument("Function GetOvertemp() not defined for this board version");
      };
   };
   unsigned int GetOvertempLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            // Overtemperature from external sensor
            if(BitMask) *BitMask = 0x00008000;
            if(BitOfs) *BitOfs = 15;
            return 0x0028;
         default:
            throw std::invalid_argument("Function GetOvertempLoc() not defined for this board version");
      };
   };

   // Bit(s) PACKAGER_BUSY
   unsigned int GetPackagerBusy()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // "1" while packager is not ready to process data (buffers are full or ethernet destination not configured)
            return BitExtractStatus(0x0028, 0x00000040, 6);
         default:
            throw std::invalid_argument("Function GetPackagerBusy() not defined for this board version");
      };
   };
   unsigned int GetPackagerBusyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // "1" while packager is not ready to process data (buffers are full or ethernet destination not configured)
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x0028;
         default:
            throw std::invalid_argument("Function GetPackagerBusyLoc() not defined for this board version");
      };
   };

   // Bit(s) PATTERN_TRIGGER_EN
   unsigned int GetPatternTriggerEn()
   {
      switch(this->mVersion)
      {
         case 8:
            // Enable internal (synchronous) pattern trigger
            return BitExtractControl(0x1180, 0x00001000, 12);
         case 9:
            // Enable internal (synchronous) pattern trigger
            return BitExtractControl(0x1124, 0x00001000, 12);
         default:
            throw std::invalid_argument("Function GetPatternTriggerEn() not defined for this board version");
      };
   };
   void SetPatternTriggerEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Enable internal (synchronous) pattern trigger
            return SetRegMask(0x1180, 0x00001000, 12, value);
         case 9:
            // Enable internal (synchronous) pattern trigger
            return SetRegMask(0x1124, 0x00001000, 12, value);
         default:
            throw std::invalid_argument("Function SetPatternTriggerEn() not defined for this board version");
      };
   };
   unsigned int GetPatternTriggerEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Enable internal (synchronous) pattern trigger
            if(BitMask) *BitMask = 0x00001000;
            if(BitOfs) *BitOfs = 12;
            return 0x1180;
         case 9:
            // Enable internal (synchronous) pattern trigger
            if(BitMask) *BitMask = 0x00001000;
            if(BitOfs) *BitOfs = 12;
            return 0x1124;
         default:
            throw std::invalid_argument("Function GetPatternTriggerEnLoc() not defined for this board version");
      };
   };

   // Bit(s) PROTOCOL_VERSION
   unsigned int GetProtocolVersion()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Version of the WaveDream2 protocol
            return BitExtractStatus(0x0020, 0x000000FF, 0);
         default:
            throw std::invalid_argument("Function GetProtocolVersion() not defined for this board version");
      };
   };
   unsigned int GetProtocolVersionLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Version of the WaveDream2 protocol
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x0020;
         default:
            throw std::invalid_argument("Function GetProtocolVersionLoc() not defined for this board version");
      };
   };

   // Bit(s) RECONFIGURE_FPGA
   unsigned int GetReconfigureFpga()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Initiate FPGA Reconfiguration
            return BitExtractControl(0x1040, 0x00000001, 0);
         default:
            throw std::invalid_argument("Function GetReconfigureFpga() not defined for this board version");
      };
   };
   void SetReconfigureFpga(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Initiate FPGA Reconfiguration
            return SetRegMask(0x1040, 0x00000001, 0, value);
         default:
            throw std::invalid_argument("Function SetReconfigureFpga() not defined for this board version");
      };
   };
   unsigned int GetReconfigureFpgaLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Initiate FPGA Reconfiguration
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x1040;
         default:
            throw std::invalid_argument("Function GetReconfigureFpgaLoc() not defined for this board version");
      };
   };

   // Bit(s) REG_LAYOUT_COMP_LEVEL
   unsigned int GetRegLayoutCompLevel()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Register map layout compatibility level
            return BitExtractStatus(0x0004, 0xFFFF0000, 16);
         default:
            throw std::invalid_argument("Function GetRegLayoutCompLevel() not defined for this board version");
      };
   };
   unsigned int GetRegLayoutCompLevelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Register map layout compatibility level
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0004;
         default:
            throw std::invalid_argument("Function GetRegLayoutCompLevelLoc() not defined for this board version");
      };
   };

   // Bit(s) REG_LAYOUT_VERSION
   unsigned int GetRegLayoutVersion()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Register map layout version
            return BitExtractStatus(0x0004, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetRegLayoutVersion() not defined for this board version");
      };
   };
   unsigned int GetRegLayoutVersionLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Register map layout version
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0004;
         default:
            throw std::invalid_argument("Function GetRegLayoutVersionLoc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_0
   unsigned int GetScaler0()
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 0 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00A0, 0xFFFFFFFF, 0);
         case 9:
            // Count rate value of channel 0 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x009C, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScaler0() not defined for this board version");
      };
   };
   unsigned int GetScaler0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 0 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00A0;
         case 9:
            // Count rate value of channel 0 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x009C;
         default:
            throw std::invalid_argument("Function GetScaler0Loc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_1
   unsigned int GetScaler1()
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 1 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00A4, 0xFFFFFFFF, 0);
         case 9:
            // Count rate value of channel 1 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00A0, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScaler1() not defined for this board version");
      };
   };
   unsigned int GetScaler1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 1 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00A4;
         case 9:
            // Count rate value of channel 1 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00A0;
         default:
            throw std::invalid_argument("Function GetScaler1Loc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_10
   unsigned int GetScaler10()
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 10 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00C8, 0xFFFFFFFF, 0);
         case 9:
            // Count rate value of channel 10 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00C4, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScaler10() not defined for this board version");
      };
   };
   unsigned int GetScaler10Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 10 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00C8;
         case 9:
            // Count rate value of channel 10 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00C4;
         default:
            throw std::invalid_argument("Function GetScaler10Loc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_11
   unsigned int GetScaler11()
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 11 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00CC, 0xFFFFFFFF, 0);
         case 9:
            // Count rate value of channel 11 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00C8, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScaler11() not defined for this board version");
      };
   };
   unsigned int GetScaler11Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 11 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00CC;
         case 9:
            // Count rate value of channel 11 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00C8;
         default:
            throw std::invalid_argument("Function GetScaler11Loc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_12
   unsigned int GetScaler12()
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 12 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00D0, 0xFFFFFFFF, 0);
         case 9:
            // Count rate value of channel 12 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00CC, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScaler12() not defined for this board version");
      };
   };
   unsigned int GetScaler12Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 12 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00D0;
         case 9:
            // Count rate value of channel 12 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00CC;
         default:
            throw std::invalid_argument("Function GetScaler12Loc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_13
   unsigned int GetScaler13()
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 13 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00D4, 0xFFFFFFFF, 0);
         case 9:
            // Count rate value of channel 13 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00D0, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScaler13() not defined for this board version");
      };
   };
   unsigned int GetScaler13Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 13 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00D4;
         case 9:
            // Count rate value of channel 13 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00D0;
         default:
            throw std::invalid_argument("Function GetScaler13Loc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_14
   unsigned int GetScaler14()
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 14 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00D8, 0xFFFFFFFF, 0);
         case 9:
            // Count rate value of channel 14 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00D4, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScaler14() not defined for this board version");
      };
   };
   unsigned int GetScaler14Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 14 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00D8;
         case 9:
            // Count rate value of channel 14 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00D4;
         default:
            throw std::invalid_argument("Function GetScaler14Loc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_15
   unsigned int GetScaler15()
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 15 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00DC, 0xFFFFFFFF, 0);
         case 9:
            // Count rate value of channel 15 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00D8, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScaler15() not defined for this board version");
      };
   };
   unsigned int GetScaler15Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 15 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00DC;
         case 9:
            // Count rate value of channel 15 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00D8;
         default:
            throw std::invalid_argument("Function GetScaler15Loc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_2
   unsigned int GetScaler2()
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 2 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00A8, 0xFFFFFFFF, 0);
         case 9:
            // Count rate value of channel 2 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00A4, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScaler2() not defined for this board version");
      };
   };
   unsigned int GetScaler2Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 2 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00A8;
         case 9:
            // Count rate value of channel 2 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00A4;
         default:
            throw std::invalid_argument("Function GetScaler2Loc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_3
   unsigned int GetScaler3()
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 3 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00AC, 0xFFFFFFFF, 0);
         case 9:
            // Count rate value of channel 3 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00A8, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScaler3() not defined for this board version");
      };
   };
   unsigned int GetScaler3Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 3 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00AC;
         case 9:
            // Count rate value of channel 3 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00A8;
         default:
            throw std::invalid_argument("Function GetScaler3Loc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_4
   unsigned int GetScaler4()
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 4 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00B0, 0xFFFFFFFF, 0);
         case 9:
            // Count rate value of channel 4 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00AC, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScaler4() not defined for this board version");
      };
   };
   unsigned int GetScaler4Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 4 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00B0;
         case 9:
            // Count rate value of channel 4 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00AC;
         default:
            throw std::invalid_argument("Function GetScaler4Loc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_5
   unsigned int GetScaler5()
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 5 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00B4, 0xFFFFFFFF, 0);
         case 9:
            // Count rate value of channel 5 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00B0, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScaler5() not defined for this board version");
      };
   };
   unsigned int GetScaler5Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 5 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00B4;
         case 9:
            // Count rate value of channel 5 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00B0;
         default:
            throw std::invalid_argument("Function GetScaler5Loc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_6
   unsigned int GetScaler6()
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 6 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00B8, 0xFFFFFFFF, 0);
         case 9:
            // Count rate value of channel 6 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00B4, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScaler6() not defined for this board version");
      };
   };
   unsigned int GetScaler6Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 6 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00B8;
         case 9:
            // Count rate value of channel 6 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00B4;
         default:
            throw std::invalid_argument("Function GetScaler6Loc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_7
   unsigned int GetScaler7()
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 7 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00BC, 0xFFFFFFFF, 0);
         case 9:
            // Count rate value of channel 7 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00B8, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScaler7() not defined for this board version");
      };
   };
   unsigned int GetScaler7Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 7 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00BC;
         case 9:
            // Count rate value of channel 7 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00B8;
         default:
            throw std::invalid_argument("Function GetScaler7Loc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_8
   unsigned int GetScaler8()
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 8 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00C0, 0xFFFFFFFF, 0);
         case 9:
            // Count rate value of channel 8 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00BC, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScaler8() not defined for this board version");
      };
   };
   unsigned int GetScaler8Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 8 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00C0;
         case 9:
            // Count rate value of channel 8 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00BC;
         default:
            throw std::invalid_argument("Function GetScaler8Loc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_9
   unsigned int GetScaler9()
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 9 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00C4, 0xFFFFFFFF, 0);
         case 9:
            // Count rate value of channel 9 (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00C0, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScaler9() not defined for this board version");
      };
   };
   unsigned int GetScaler9Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate value of channel 9 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00C4;
         case 9:
            // Count rate value of channel 9 (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00C0;
         default:
            throw std::invalid_argument("Function GetScaler9Loc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_EXT_CLK
   unsigned int GetScalerExtClk()
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate for external clock input (GLOB_CLK)
            return BitExtractStatus(0x00E8, 0xFFFFFFFF, 0);
         case 9:
            // Count rate for external clock input (GLOB_CLK)
            return BitExtractStatus(0x00E4, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScalerExtClk() not defined for this board version");
      };
   };
   unsigned int GetScalerExtClkLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate for external clock input (GLOB_CLK)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00E8;
         case 9:
            // Count rate for external clock input (GLOB_CLK)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00E4;
         default:
            throw std::invalid_argument("Function GetScalerExtClkLoc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_EXT_TRG
   unsigned int GetScalerExtTrg()
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate for trigger signal
            return BitExtractStatus(0x00E4, 0xFFFFFFFF, 0);
         case 9:
            // Count rate for trigger signal
            return BitExtractStatus(0x00E0, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScalerExtTrg() not defined for this board version");
      };
   };
   unsigned int GetScalerExtTrgLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate for trigger signal
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00E4;
         case 9:
            // Count rate for trigger signal
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00E0;
         default:
            throw std::invalid_argument("Function GetScalerExtTrgLoc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_PTRN_TRG
   unsigned int GetScalerPtrnTrg()
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate for pattern trigger signal
            return BitExtractStatus(0x00E0, 0xFFFFFFFF, 0);
         case 9:
            // Count rate for pattern trigger signal
            return BitExtractStatus(0x00DC, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScalerPtrnTrg() not defined for this board version");
      };
   };
   unsigned int GetScalerPtrnTrgLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Count rate for pattern trigger signal
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00E0;
         case 9:
            // Count rate for pattern trigger signal
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00DC;
         default:
            throw std::invalid_argument("Function GetScalerPtrnTrgLoc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_RST
   unsigned int GetScalerRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset all scalers
            return BitExtractControl(0x1040, 0x00000200, 9);
         default:
            throw std::invalid_argument("Function GetScalerRst() not defined for this board version");
      };
   };
   void SetScalerRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset all scalers
            return SetRegMask(0x1040, 0x00000200, 9, value);
         default:
            throw std::invalid_argument("Function SetScalerRst() not defined for this board version");
      };
   };
   unsigned int GetScalerRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset all scalers
            if(BitMask) *BitMask = 0x00000200;
            if(BitOfs) *BitOfs = 9;
            return 0x1040;
         default:
            throw std::invalid_argument("Function GetScalerRstLoc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_TIME_STAMP_LSB
   unsigned int GetScalerTimeStampLsb()
   {
      switch(this->mVersion)
      {
         case 8:
            // LSBs of 64bit scaler time stamp (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00EC, 0xFFFFFFFF, 0);
         case 9:
            // LSBs of 64bit scaler time stamp (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00E8, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScalerTimeStampLsb() not defined for this board version");
      };
   };
   unsigned int GetScalerTimeStampLsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // LSBs of 64bit scaler time stamp (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00EC;
         case 9:
            // LSBs of 64bit scaler time stamp (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00E8;
         default:
            throw std::invalid_argument("Function GetScalerTimeStampLsbLoc() not defined for this board version");
      };
   };

   // Bit(s) SCALER_TIME_STAMP_MSB
   unsigned int GetScalerTimeStampMsb()
   {
      switch(this->mVersion)
      {
         case 8:
            // MSBs of 64bit scaler time stamp (latched upon read of LSB register)
            return BitExtractStatus(0x00F0, 0xFFFFFFFF, 0);
         case 9:
            // MSBs of 64bit scaler time stamp (latched upon read of LSB register)
            return BitExtractStatus(0x00EC, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetScalerTimeStampMsb() not defined for this board version");
      };
   };
   unsigned int GetScalerTimeStampMsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // MSBs of 64bit scaler time stamp (latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00F0;
         case 9:
            // MSBs of 64bit scaler time stamp (latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00EC;
         default:
            throw std::invalid_argument("Function GetScalerTimeStampMsbLoc() not defined for this board version");
      };
   };

   // Bit(s) SCL_TX_EN
   unsigned int GetSclTxEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable transmission of scaler data
            return BitExtractControl(0x1014, 0x04000000, 26);
         default:
            throw std::invalid_argument("Function GetSclTxEn() not defined for this board version");
      };
   };
   void SetSclTxEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable transmission of scaler data
            return SetRegMask(0x1014, 0x04000000, 26, value);
         default:
            throw std::invalid_argument("Function SetSclTxEn() not defined for this board version");
      };
   };
   unsigned int GetSclTxEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable transmission of scaler data
            if(BitMask) *BitMask = 0x04000000;
            if(BitOfs) *BitOfs = 26;
            return 0x1014;
         default:
            throw std::invalid_argument("Function GetSclTxEnLoc() not defined for this board version");
      };
   };

   // Bit(s) SERDES_COM_EN
   unsigned int GetSerdesComEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable SERDES communication to backplane
            return BitExtractControl(0x1014, 0x02000000, 25);
         default:
            throw std::invalid_argument("Function GetSerdesComEn() not defined for this board version");
      };
   };
   void SetSerdesComEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable SERDES communication to backplane
            return SetRegMask(0x1014, 0x02000000, 25, value);
         default:
            throw std::invalid_argument("Function SetSerdesComEn() not defined for this board version");
      };
   };
   unsigned int GetSerdesComEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable SERDES communication to backplane
            if(BitMask) *BitMask = 0x02000000;
            if(BitOfs) *BitOfs = 25;
            return 0x1014;
         default:
            throw std::invalid_argument("Function GetSerdesComEnLoc() not defined for this board version");
      };
   };

   // Bit(s) SERIAL_BUSY
   unsigned int GetSerialBusy()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // "1" during serial activity like FLASH read/write
            return BitExtractStatus(0x0028, 0x00000080, 7);
         default:
            throw std::invalid_argument("Function GetSerialBusy() not defined for this board version");
      };
   };
   unsigned int GetSerialBusyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // "1" during serial activity like FLASH read/write
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x0028;
         default:
            throw std::invalid_argument("Function GetSerialBusyLoc() not defined for this board version");
      };
   };

   // Bit(s) SERIAL_NUMBER
   unsigned int GetSerialNumber()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Serial Number of the WD2 Board (Board ID)
            return BitExtractStatus(0x0024, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetSerialNumber() not defined for this board version");
      };
   };
   unsigned int GetSerialNumberLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Serial Number of the WD2 Board (Board ID)
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0024;
         default:
            throw std::invalid_argument("Function GetSerialNumberLoc() not defined for this board version");
      };
   };

   // Bit(s) SET_TIME_LSB
   unsigned int GetSetTimeLsb()
   {
      switch(this->mVersion)
      {
         case 8:
            // LSBs of 64bit system time counter set value  (time is updated when MSBs are written)
            return BitExtractControl(0x1278, 0xFFFFFFFF, 0);
         case 9:
            // LSBs of 64bit system time counter set value  (time is updated when MSBs are written)
            return BitExtractControl(0x121C, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetSetTimeLsb() not defined for this board version");
      };
   };
   void SetSetTimeLsb(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // LSBs of 64bit system time counter set value  (time is updated when MSBs are written)
            return SetRegMask(0x1278, 0xFFFFFFFF, 0, value);
         case 9:
            // LSBs of 64bit system time counter set value  (time is updated when MSBs are written)
            return SetRegMask(0x121C, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetSetTimeLsb() not defined for this board version");
      };
   };
   unsigned int GetSetTimeLsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // LSBs of 64bit system time counter set value  (time is updated when MSBs are written)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1278;
         case 9:
            // LSBs of 64bit system time counter set value  (time is updated when MSBs are written)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x121C;
         default:
            throw std::invalid_argument("Function GetSetTimeLsbLoc() not defined for this board version");
      };
   };

   // Bit(s) SET_TIME_MSB
   unsigned int GetSetTimeMsb()
   {
      switch(this->mVersion)
      {
         case 8:
            // MSBs of 64bit system time counter set value  (time is updated when MSBs are written)
            return BitExtractControl(0x127C, 0xFFFFFFFF, 0);
         case 9:
            // MSBs of 64bit system time counter set value  (time is updated when MSBs are written)
            return BitExtractControl(0x1220, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetSetTimeMsb() not defined for this board version");
      };
   };
   void SetSetTimeMsb(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // MSBs of 64bit system time counter set value  (time is updated when MSBs are written)
            return SetRegMask(0x127C, 0xFFFFFFFF, 0, value);
         case 9:
            // MSBs of 64bit system time counter set value  (time is updated when MSBs are written)
            return SetRegMask(0x1220, 0xFFFFFFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetSetTimeMsb() not defined for this board version");
      };
   };
   unsigned int GetSetTimeMsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // MSBs of 64bit system time counter set value  (time is updated when MSBs are written)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x127C;
         case 9:
            // MSBs of 64bit system time counter set value  (time is updated when MSBs are written)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1220;
         default:
            throw std::invalid_argument("Function GetSetTimeMsbLoc() not defined for this board version");
      };
   };

   // Bit(s) SLOT_ID
   unsigned int GetSlotId()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // ID of the slot where the current board is plugged in
            return BitExtractControl(0x1000, 0x000000FF, 0);
         default:
            throw std::invalid_argument("Function GetSlotId() not defined for this board version");
      };
   };
   void SetSlotId(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // ID of the slot where the current board is plugged in
            return SetRegMask(0x1000, 0x000000FF, 0, value);
         default:
            throw std::invalid_argument("Function SetSlotId() not defined for this board version");
      };
   };
   unsigned int GetSlotIdLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // ID of the slot where the current board is plugged in
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x1000;
         default:
            throw std::invalid_argument("Function GetSlotIdLoc() not defined for this board version");
      };
   };

   // Bit(s) SW_BUILD_DAY
   unsigned int GetSwBuildDay()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Day of the software build
            return BitExtractStatus(0x0010, 0x000000FF, 0);
         default:
            throw std::invalid_argument("Function GetSwBuildDay() not defined for this board version");
      };
   };
   unsigned int GetSwBuildDayLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Day of the software build
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x0010;
         default:
            throw std::invalid_argument("Function GetSwBuildDayLoc() not defined for this board version");
      };
   };

   // Bit(s) SW_BUILD_HOUR
   unsigned int GetSwBuildHour()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Hour of the software build
            return BitExtractStatus(0x0014, 0x00FF0000, 16);
         default:
            throw std::invalid_argument("Function GetSwBuildHour() not defined for this board version");
      };
   };
   unsigned int GetSwBuildHourLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Hour of the software build
            if(BitMask) *BitMask = 0x00FF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0014;
         default:
            throw std::invalid_argument("Function GetSwBuildHourLoc() not defined for this board version");
      };
   };

   // Bit(s) SW_BUILD_MINUTE
   unsigned int GetSwBuildMinute()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Minute of the software build
            return BitExtractStatus(0x0014, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetSwBuildMinute() not defined for this board version");
      };
   };
   unsigned int GetSwBuildMinuteLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Minute of the software build
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x0014;
         default:
            throw std::invalid_argument("Function GetSwBuildMinuteLoc() not defined for this board version");
      };
   };

   // Bit(s) SW_BUILD_MONTH
   unsigned int GetSwBuildMonth()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Month of the software build
            return BitExtractStatus(0x0010, 0x0000FF00, 8);
         default:
            throw std::invalid_argument("Function GetSwBuildMonth() not defined for this board version");
      };
   };
   unsigned int GetSwBuildMonthLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Month of the software build
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x0010;
         default:
            throw std::invalid_argument("Function GetSwBuildMonthLoc() not defined for this board version");
      };
   };

   // Bit(s) SW_BUILD_SECOND
   unsigned int GetSwBuildSecond()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Second of the software build
            return BitExtractStatus(0x0014, 0x000000FF, 0);
         default:
            throw std::invalid_argument("Function GetSwBuildSecond() not defined for this board version");
      };
   };
   unsigned int GetSwBuildSecondLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Second of the software build
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x0014;
         default:
            throw std::invalid_argument("Function GetSwBuildSecondLoc() not defined for this board version");
      };
   };

   // Bit(s) SW_BUILD_YEAR
   unsigned int GetSwBuildYear()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Year of the software build
            return BitExtractStatus(0x0010, 0xFFFF0000, 16);
         default:
            throw std::invalid_argument("Function GetSwBuildYear() not defined for this board version");
      };
   };
   unsigned int GetSwBuildYearLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Year of the software build
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0010;
         default:
            throw std::invalid_argument("Function GetSwBuildYearLoc() not defined for this board version");
      };
   };

   // Bit(s) SW_GIT_HASH_TAG
   unsigned int GetSwGitHashTag()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Hash tag of the software commit in the GIT repository
            return BitExtractStatus(0x001C, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetSwGitHashTag() not defined for this board version");
      };
   };
   unsigned int GetSwGitHashTagLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Hash tag of the software commit in the GIT repository
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x001C;
         default:
            throw std::invalid_argument("Function GetSwGitHashTagLoc() not defined for this board version");
      };
   };

   // Bit(s) SYS_BUSY
   unsigned int GetSysBusy()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Inverted busy signal from backplane (high active, not available until hardware revision G)
            return BitExtractStatus(0x0028, 0x00000010, 4);
         default:
            throw std::invalid_argument("Function GetSysBusy() not defined for this board version");
      };
   };
   unsigned int GetSysBusyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Inverted busy signal from backplane (high active, not available until hardware revision G)
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x0028;
         default:
            throw std::invalid_argument("Function GetSysBusyLoc() not defined for this board version");
      };
   };

   // Bit(s) SYS_DCM_LOCK
   unsigned int GetSysDcmLock()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Lock of system DCM (FPGA internal)
            return BitExtractStatus(0x002C, 0x00000100, 8);
         default:
            throw std::invalid_argument("Function GetSysDcmLock() not defined for this board version");
      };
   };
   unsigned int GetSysDcmLockLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Lock of system DCM (FPGA internal)
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x002C;
         default:
            throw std::invalid_argument("Function GetSysDcmLockLoc() not defined for this board version");
      };
   };

   // Bit(s) TCB_OSERDES_IF_RST
   unsigned int GetTcbOserdesIfRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the TCB OSERDES interface
            return BitExtractControl(0x1040, 0x00000400, 10);
         default:
            throw std::invalid_argument("Function GetTcbOserdesIfRst() not defined for this board version");
      };
   };
   void SetTcbOserdesIfRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the TCB OSERDES interface
            return SetRegMask(0x1040, 0x00000400, 10, value);
         default:
            throw std::invalid_argument("Function SetTcbOserdesIfRst() not defined for this board version");
      };
   };
   unsigned int GetTcbOserdesIfRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the TCB OSERDES interface
            if(BitMask) *BitMask = 0x00000400;
            if(BitOfs) *BitOfs = 10;
            return 0x1040;
         default:
            throw std::invalid_argument("Function GetTcbOserdesIfRstLoc() not defined for this board version");
      };
   };

   // Bit(s) TCB_OSERDES_PLL_RST
   unsigned int GetTcbOserdesPllRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the PLL of the TCB OSERDES
            return BitExtractControl(0x1040, 0x00001000, 12);
         default:
            throw std::invalid_argument("Function GetTcbOserdesPllRst() not defined for this board version");
      };
   };
   void SetTcbOserdesPllRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the PLL of the TCB OSERDES
            return SetRegMask(0x1040, 0x00001000, 12, value);
         default:
            throw std::invalid_argument("Function SetTcbOserdesPllRst() not defined for this board version");
      };
   };
   unsigned int GetTcbOserdesPllRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the PLL of the TCB OSERDES
            if(BitMask) *BitMask = 0x00001000;
            if(BitOfs) *BitOfs = 12;
            return 0x1040;
         default:
            throw std::invalid_argument("Function GetTcbOserdesPllRstLoc() not defined for this board version");
      };
   };

   // Bit(s) TCB_SERDES_TRAIN
   unsigned int GetTcbSerdesTrain()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable training pattern for TCB SERDES connection
            return BitExtractControl(0x1014, 0x40000000, 30);
         default:
            throw std::invalid_argument("Function GetTcbSerdesTrain() not defined for this board version");
      };
   };
   void SetTcbSerdesTrain(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable training pattern for TCB SERDES connection
            return SetRegMask(0x1014, 0x40000000, 30, value);
         default:
            throw std::invalid_argument("Function SetTcbSerdesTrain() not defined for this board version");
      };
   };
   unsigned int GetTcbSerdesTrainLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable training pattern for TCB SERDES connection
            if(BitMask) *BitMask = 0x40000000;
            if(BitOfs) *BitOfs = 30;
            return 0x1014;
         default:
            throw std::invalid_argument("Function GetTcbSerdesTrainLoc() not defined for this board version");
      };
   };

   // Bit(s) TDC_CH_TX_EN
   unsigned int GetTdcChTxEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // TDC channel transmission enable [Ch15:Ch0]
            return BitExtractControl(0x1024, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTdcChTxEn() not defined for this board version");
      };
   };
   void SetTdcChTxEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // TDC channel transmission enable [Ch15:Ch0]
            return SetRegMask(0x1024, 0x0000FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTdcChTxEn() not defined for this board version");
      };
   };
   unsigned int GetTdcChTxEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // TDC channel transmission enable [Ch15:Ch0]
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1024;
         default:
            throw std::invalid_argument("Function GetTdcChTxEnLoc() not defined for this board version");
      };
   };

   // Bit(s) TDC_SAMPLE_FREQ
   unsigned int GetTdcSampleFreq()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // TDC Sampling Frequency in kHz
            return BitExtractStatus(0x0040, 0x00FFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetTdcSampleFreq() not defined for this board version");
      };
   };
   unsigned int GetTdcSampleFreqLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // TDC Sampling Frequency in kHz
            if(BitMask) *BitMask = 0x00FFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0040;
         default:
            throw std::invalid_argument("Function GetTdcSampleFreqLoc() not defined for this board version");
      };
   };

   // Bit(s) TDC_TX_SAMPLES
   unsigned int GetTdcTxSamples()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Number of TDC samples to transmit per channel (must be a multiple of 8 with range 16 to 4096)
            return BitExtractControl(0x1030, 0x00001FFF, 0);
         default:
            throw std::invalid_argument("Function GetTdcTxSamples() not defined for this board version");
      };
   };
   void SetTdcTxSamples(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Number of TDC samples to transmit per channel (must be a multiple of 8 with range 16 to 4096)
            return SetRegMask(0x1030, 0x00001FFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTdcTxSamples() not defined for this board version");
      };
   };
   unsigned int GetTdcTxSamplesLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Number of TDC samples to transmit per channel (must be a multiple of 8 with range 16 to 4096)
            if(BitMask) *BitMask = 0x00001FFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1030;
         default:
            throw std::invalid_argument("Function GetTdcTxSamplesLoc() not defined for this board version");
      };
   };

   // Bit(s) TEMPERATURE
   unsigned int GetTemperature()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // temperature in 0.0625 deg. C units
            return BitExtractStatus(0x0028, 0xFFFF0000, 16);
         default:
            throw std::invalid_argument("Function GetTemperature() not defined for this board version");
      };
   };
   unsigned int GetTemperatureLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // temperature in 0.0625 deg. C units
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0028;
         default:
            throw std::invalid_argument("Function GetTemperatureLoc() not defined for this board version");
      };
   };

   // Bit(s) TIME_LSB
   unsigned int GetTimeLsb()
   {
      switch(this->mVersion)
      {
         case 8:
            // LSBs of 64bit system time counter (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00F4, 0xFFFFFFFF, 0);
         case 9:
            // LSBs of 64bit system time counter (MSBs are latched upon read of LSB register)
            return BitExtractStatus(0x00F0, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetTimeLsb() not defined for this board version");
      };
   };
   unsigned int GetTimeLsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // LSBs of 64bit system time counter (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00F4;
         case 9:
            // LSBs of 64bit system time counter (MSBs are latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00F0;
         default:
            throw std::invalid_argument("Function GetTimeLsbLoc() not defined for this board version");
      };
   };

   // Bit(s) TIME_MSB
   unsigned int GetTimeMsb()
   {
      switch(this->mVersion)
      {
         case 8:
            // MSBs of 64bit system time counter (latched upon read of LSB register)
            return BitExtractStatus(0x00F8, 0xFFFFFFFF, 0);
         case 9:
            // MSBs of 64bit system time counter (latched upon read of LSB register)
            return BitExtractStatus(0x00F4, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetTimeMsb() not defined for this board version");
      };
   };
   unsigned int GetTimeMsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // MSBs of 64bit system time counter (latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00F8;
         case 9:
            // MSBs of 64bit system time counter (latched upon read of LSB register)
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00F4;
         default:
            throw std::invalid_argument("Function GetTimeMsbLoc() not defined for this board version");
      };
   };

   // Bit(s) TIMING_CALIB_SIGNAL_EN
   unsigned int GetTimingCalibSignalEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // switch on (1) / off (0) 100 MHz calibration signal for DRS chip (TCA_CTRL)
            return BitExtractControl(0x1008, 0x00000001, 0);
         default:
            throw std::invalid_argument("Function GetTimingCalibSignalEn() not defined for this board version");
      };
   };
   void SetTimingCalibSignalEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // switch on (1) / off (0) 100 MHz calibration signal for DRS chip (TCA_CTRL)
            return SetRegMask(0x1008, 0x00000001, 0, value);
         default:
            throw std::invalid_argument("Function SetTimingCalibSignalEn() not defined for this board version");
      };
   };
   unsigned int GetTimingCalibSignalEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // switch on (1) / off (0) 100 MHz calibration signal for DRS chip (TCA_CTRL)
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x1008;
         default:
            throw std::invalid_argument("Function GetTimingCalibSignalEnLoc() not defined for this board version");
      };
   };

   // Bit(s) TRB_FLAG_NEW
   unsigned int GetTrbFlagNew()
   {
      switch(this->mVersion)
      {
         case 8:
            // Flag signalling that the current trigger information belongs to the latest trigger received
            return BitExtractStatus(0x0108, 0x80000000, 31);
         case 9:
            // Flag signalling that the current trigger information belongs to the latest trigger received
            return BitExtractStatus(0x0104, 0x80000000, 31);
         default:
            throw std::invalid_argument("Function GetTrbFlagNew() not defined for this board version");
      };
   };
   unsigned int GetTrbFlagNewLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Flag signalling that the current trigger information belongs to the latest trigger received
            if(BitMask) *BitMask = 0x80000000;
            if(BitOfs) *BitOfs = 31;
            return 0x0108;
         case 9:
            // Flag signalling that the current trigger information belongs to the latest trigger received
            if(BitMask) *BitMask = 0x80000000;
            if(BitOfs) *BitOfs = 31;
            return 0x0104;
         default:
            throw std::invalid_argument("Function GetTrbFlagNewLoc() not defined for this board version");
      };
   };

   // Bit(s) TRB_FLAG_PARITY_ERROR
   unsigned int GetTrbFlagParityError()
   {
      switch(this->mVersion)
      {
         case 8:
            // Parity error flag of the current trigger information
            return BitExtractStatus(0x0108, 0x40000000, 30);
         case 9:
            // Parity error flag of the current trigger information
            return BitExtractStatus(0x0104, 0x40000000, 30);
         default:
            throw std::invalid_argument("Function GetTrbFlagParityError() not defined for this board version");
      };
   };
   unsigned int GetTrbFlagParityErrorLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Parity error flag of the current trigger information
            if(BitMask) *BitMask = 0x40000000;
            if(BitOfs) *BitOfs = 30;
            return 0x0108;
         case 9:
            // Parity error flag of the current trigger information
            if(BitMask) *BitMask = 0x40000000;
            if(BitOfs) *BitOfs = 30;
            return 0x0104;
         default:
            throw std::invalid_argument("Function GetTrbFlagParityErrorLoc() not defined for this board version");
      };
   };

   // Bit(s) TRB_INFO_LSB
   unsigned int GetTrbInfoLsb()
   {
      switch(this->mVersion)
      {
         case 8:
            // Trigger information LSBs
            return BitExtractStatus(0x010C, 0xFFFFFFFF, 0);
         case 9:
            // Trigger information LSBs
            return BitExtractStatus(0x0108, 0xFFFFFFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrbInfoLsb() not defined for this board version");
      };
   };
   unsigned int GetTrbInfoLsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Trigger information LSBs
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x010C;
         case 9:
            // Trigger information LSBs
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0108;
         default:
            throw std::invalid_argument("Function GetTrbInfoLsbLoc() not defined for this board version");
      };
   };

   // Bit(s) TRB_INFO_MSB
   unsigned int GetTrbInfoMsb()
   {
      switch(this->mVersion)
      {
         case 8:
            // Trigger information MSBs
            return BitExtractStatus(0x0110, 0x0000FFFF, 0);
         case 9:
            // Trigger information MSBs
            return BitExtractStatus(0x010C, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrbInfoMsb() not defined for this board version");
      };
   };
   unsigned int GetTrbInfoMsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Trigger information MSBs
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0110;
         case 9:
            // Trigger information MSBs
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x010C;
         default:
            throw std::invalid_argument("Function GetTrbInfoMsbLoc() not defined for this board version");
      };
   };

   // Bit(s) TRB_PARITY_ERROR_COUNT
   unsigned int GetTrbParityErrorCount()
   {
      switch(this->mVersion)
      {
         case 8:
            // Parity error count of the serial transmission
            return BitExtractStatus(0x0108, 0x0000FFFF, 0);
         case 9:
            // Parity error count of the serial transmission
            return BitExtractStatus(0x0104, 0x0000FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrbParityErrorCount() not defined for this board version");
      };
   };
   unsigned int GetTrbParityErrorCountLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Parity error count of the serial transmission
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0108;
         case 9:
            // Parity error count of the serial transmission
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0104;
         default:
            throw std::invalid_argument("Function GetTrbParityErrorCountLoc() not defined for this board version");
      };
   };

   // Bit(s) TRB_PARITY_ERROR_COUNT_RST
   unsigned int GetTrbParityErrorCountRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the parity error counter of the trigger info serial connection
            return BitExtractControl(0x1040, 0x00000100, 8);
         default:
            throw std::invalid_argument("Function GetTrbParityErrorCountRst() not defined for this board version");
      };
   };
   void SetTrbParityErrorCountRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the parity error counter of the trigger info serial connection
            return SetRegMask(0x1040, 0x00000100, 8, value);
         default:
            throw std::invalid_argument("Function SetTrbParityErrorCountRst() not defined for this board version");
      };
   };
   unsigned int GetTrbParityErrorCountRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Reset the parity error counter of the trigger info serial connection
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1040;
         default:
            throw std::invalid_argument("Function GetTrbParityErrorCountRstLoc() not defined for this board version");
      };
   };

   // Bit(s) TRG_PTRN_EN
   unsigned int GetTrgPtrnEn()
   {
      switch(this->mVersion)
      {
         case 8:
            // 1 enables the corresponding trigger patterns for the local trigger
            return BitExtractControl(0x118C, 0x0007FFFF, 0);
         case 9:
            // 1 enables the corresponding trigger patterns for the local trigger
            return BitExtractControl(0x1130, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgPtrnEn() not defined for this board version");
      };
   };
   void SetTrgPtrnEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // 1 enables the corresponding trigger patterns for the local trigger
            return SetRegMask(0x118C, 0x0007FFFF, 0, value);
         case 9:
            // 1 enables the corresponding trigger patterns for the local trigger
            return SetRegMask(0x1130, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgPtrnEn() not defined for this board version");
      };
   };
   unsigned int GetTrgPtrnEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // 1 enables the corresponding trigger patterns for the local trigger
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x118C;
         case 9:
            // 1 enables the corresponding trigger patterns for the local trigger
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1130;
         default:
            throw std::invalid_argument("Function GetTrgPtrnEnLoc() not defined for this board version");
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN0
   unsigned int GetTrgSrcEnPtrn0()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x1190, 0x0007FFFF, 0);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x1134, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn0() not defined for this board version");
      };
   };
   void SetTrgSrcEnPtrn0(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x1190, 0x0007FFFF, 0, value);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x1134, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgSrcEnPtrn0() not defined for this board version");
      };
   };
   unsigned int GetTrgSrcEnPtrn0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1190;
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1134;
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn0Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN1
   unsigned int GetTrgSrcEnPtrn1()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x1198, 0x0007FFFF, 0);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x113C, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn1() not defined for this board version");
      };
   };
   void SetTrgSrcEnPtrn1(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x1198, 0x0007FFFF, 0, value);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x113C, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgSrcEnPtrn1() not defined for this board version");
      };
   };
   unsigned int GetTrgSrcEnPtrn1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1198;
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x113C;
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn1Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN10
   unsigned int GetTrgSrcEnPtrn10()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x11E0, 0x0007FFFF, 0);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x1184, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn10() not defined for this board version");
      };
   };
   void SetTrgSrcEnPtrn10(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x11E0, 0x0007FFFF, 0, value);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x1184, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgSrcEnPtrn10() not defined for this board version");
      };
   };
   unsigned int GetTrgSrcEnPtrn10Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11E0;
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1184;
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn10Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN11
   unsigned int GetTrgSrcEnPtrn11()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x11E8, 0x0007FFFF, 0);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x118C, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn11() not defined for this board version");
      };
   };
   void SetTrgSrcEnPtrn11(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x11E8, 0x0007FFFF, 0, value);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x118C, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgSrcEnPtrn11() not defined for this board version");
      };
   };
   unsigned int GetTrgSrcEnPtrn11Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11E8;
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x118C;
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn11Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN12
   unsigned int GetTrgSrcEnPtrn12()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x11F0, 0x0007FFFF, 0);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x1194, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn12() not defined for this board version");
      };
   };
   void SetTrgSrcEnPtrn12(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x11F0, 0x0007FFFF, 0, value);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x1194, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgSrcEnPtrn12() not defined for this board version");
      };
   };
   unsigned int GetTrgSrcEnPtrn12Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11F0;
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1194;
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn12Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN13
   unsigned int GetTrgSrcEnPtrn13()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x11F8, 0x0007FFFF, 0);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x119C, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn13() not defined for this board version");
      };
   };
   void SetTrgSrcEnPtrn13(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x11F8, 0x0007FFFF, 0, value);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x119C, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgSrcEnPtrn13() not defined for this board version");
      };
   };
   unsigned int GetTrgSrcEnPtrn13Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11F8;
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x119C;
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn13Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN14
   unsigned int GetTrgSrcEnPtrn14()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x1200, 0x0007FFFF, 0);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x11A4, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn14() not defined for this board version");
      };
   };
   void SetTrgSrcEnPtrn14(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x1200, 0x0007FFFF, 0, value);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x11A4, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgSrcEnPtrn14() not defined for this board version");
      };
   };
   unsigned int GetTrgSrcEnPtrn14Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1200;
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11A4;
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn14Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN15
   unsigned int GetTrgSrcEnPtrn15()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x1208, 0x0007FFFF, 0);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x11AC, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn15() not defined for this board version");
      };
   };
   void SetTrgSrcEnPtrn15(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x1208, 0x0007FFFF, 0, value);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x11AC, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgSrcEnPtrn15() not defined for this board version");
      };
   };
   unsigned int GetTrgSrcEnPtrn15Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1208;
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11AC;
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn15Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN16
   unsigned int GetTrgSrcEnPtrn16()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x1210, 0x0007FFFF, 0);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x11B4, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn16() not defined for this board version");
      };
   };
   void SetTrgSrcEnPtrn16(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x1210, 0x0007FFFF, 0, value);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x11B4, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgSrcEnPtrn16() not defined for this board version");
      };
   };
   unsigned int GetTrgSrcEnPtrn16Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1210;
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11B4;
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn16Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN17
   unsigned int GetTrgSrcEnPtrn17()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x1218, 0x0007FFFF, 0);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x11BC, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn17() not defined for this board version");
      };
   };
   void SetTrgSrcEnPtrn17(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x1218, 0x0007FFFF, 0, value);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x11BC, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgSrcEnPtrn17() not defined for this board version");
      };
   };
   unsigned int GetTrgSrcEnPtrn17Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1218;
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11BC;
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn17Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN18
   unsigned int GetTrgSrcEnPtrn18()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x1220, 0x0007FFFF, 0);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x11C4, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn18() not defined for this board version");
      };
   };
   void SetTrgSrcEnPtrn18(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x1220, 0x0007FFFF, 0, value);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x11C4, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgSrcEnPtrn18() not defined for this board version");
      };
   };
   unsigned int GetTrgSrcEnPtrn18Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1220;
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11C4;
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn18Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN2
   unsigned int GetTrgSrcEnPtrn2()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x11A0, 0x0007FFFF, 0);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x1144, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn2() not defined for this board version");
      };
   };
   void SetTrgSrcEnPtrn2(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x11A0, 0x0007FFFF, 0, value);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x1144, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgSrcEnPtrn2() not defined for this board version");
      };
   };
   unsigned int GetTrgSrcEnPtrn2Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11A0;
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1144;
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn2Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN3
   unsigned int GetTrgSrcEnPtrn3()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x11A8, 0x0007FFFF, 0);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x114C, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn3() not defined for this board version");
      };
   };
   void SetTrgSrcEnPtrn3(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x11A8, 0x0007FFFF, 0, value);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x114C, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgSrcEnPtrn3() not defined for this board version");
      };
   };
   unsigned int GetTrgSrcEnPtrn3Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11A8;
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x114C;
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn3Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN4
   unsigned int GetTrgSrcEnPtrn4()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x11B0, 0x0007FFFF, 0);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x1154, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn4() not defined for this board version");
      };
   };
   void SetTrgSrcEnPtrn4(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x11B0, 0x0007FFFF, 0, value);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x1154, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgSrcEnPtrn4() not defined for this board version");
      };
   };
   unsigned int GetTrgSrcEnPtrn4Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11B0;
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1154;
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn4Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN5
   unsigned int GetTrgSrcEnPtrn5()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x11B8, 0x0007FFFF, 0);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x115C, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn5() not defined for this board version");
      };
   };
   void SetTrgSrcEnPtrn5(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x11B8, 0x0007FFFF, 0, value);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x115C, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgSrcEnPtrn5() not defined for this board version");
      };
   };
   unsigned int GetTrgSrcEnPtrn5Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11B8;
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x115C;
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn5Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN6
   unsigned int GetTrgSrcEnPtrn6()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x11C0, 0x0007FFFF, 0);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x1164, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn6() not defined for this board version");
      };
   };
   void SetTrgSrcEnPtrn6(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x11C0, 0x0007FFFF, 0, value);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x1164, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgSrcEnPtrn6() not defined for this board version");
      };
   };
   unsigned int GetTrgSrcEnPtrn6Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11C0;
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1164;
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn6Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN7
   unsigned int GetTrgSrcEnPtrn7()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x11C8, 0x0007FFFF, 0);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x116C, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn7() not defined for this board version");
      };
   };
   void SetTrgSrcEnPtrn7(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x11C8, 0x0007FFFF, 0, value);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x116C, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgSrcEnPtrn7() not defined for this board version");
      };
   };
   unsigned int GetTrgSrcEnPtrn7Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11C8;
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x116C;
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn7Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN8
   unsigned int GetTrgSrcEnPtrn8()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x11D0, 0x0007FFFF, 0);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x1174, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn8() not defined for this board version");
      };
   };
   void SetTrgSrcEnPtrn8(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x11D0, 0x0007FFFF, 0, value);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x1174, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgSrcEnPtrn8() not defined for this board version");
      };
   };
   unsigned int GetTrgSrcEnPtrn8Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11D0;
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1174;
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn8Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN9
   unsigned int GetTrgSrcEnPtrn9()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x11D8, 0x0007FFFF, 0);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x117C, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn9() not defined for this board version");
      };
   };
   void SetTrgSrcEnPtrn9(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x11D8, 0x0007FFFF, 0, value);
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x117C, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgSrcEnPtrn9() not defined for this board version");
      };
   };
   unsigned int GetTrgSrcEnPtrn9Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11D8;
         case 9:
            // trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x117C;
         default:
            throw std::invalid_argument("Function GetTrgSrcEnPtrn9Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_SRC_POLARITY
   unsigned int GetTrgSrcPolarity()
   {
      switch(this->mVersion)
      {
         case 8:
            // Polarity of trigger source (0 = normal, 1 = inverted) (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x1184, 0x0007FFFF, 0);
         case 9:
            // Polarity of trigger source (0 = normal, 1 = inverted) (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return BitExtractControl(0x1128, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgSrcPolarity() not defined for this board version");
      };
   };
   void SetTrgSrcPolarity(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Polarity of trigger source (0 = normal, 1 = inverted) (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x1184, 0x0007FFFF, 0, value);
         case 9:
            // Polarity of trigger source (0 = normal, 1 = inverted) (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            return SetRegMask(0x1128, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgSrcPolarity() not defined for this board version");
      };
   };
   unsigned int GetTrgSrcPolarityLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Polarity of trigger source (0 = normal, 1 = inverted) (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1184;
         case 9:
            // Polarity of trigger source (0 = normal, 1 = inverted) (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1128;
         default:
            throw std::invalid_argument("Function GetTrgSrcPolarityLoc() not defined for this board version");
      };
   };

   // Bit(s) TRG_STATE_PTRN0
   unsigned int GetTrgStatePtrn0()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x1194, 0x0007FFFF, 0);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x1138, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn0() not defined for this board version");
      };
   };
   void SetTrgStatePtrn0(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x1194, 0x0007FFFF, 0, value);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x1138, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgStatePtrn0() not defined for this board version");
      };
   };
   unsigned int GetTrgStatePtrn0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1194;
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1138;
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn0Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_STATE_PTRN1
   unsigned int GetTrgStatePtrn1()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x119C, 0x0007FFFF, 0);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x1140, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn1() not defined for this board version");
      };
   };
   void SetTrgStatePtrn1(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x119C, 0x0007FFFF, 0, value);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x1140, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgStatePtrn1() not defined for this board version");
      };
   };
   unsigned int GetTrgStatePtrn1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x119C;
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1140;
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn1Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_STATE_PTRN10
   unsigned int GetTrgStatePtrn10()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x11E4, 0x0007FFFF, 0);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x1188, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn10() not defined for this board version");
      };
   };
   void SetTrgStatePtrn10(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x11E4, 0x0007FFFF, 0, value);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x1188, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgStatePtrn10() not defined for this board version");
      };
   };
   unsigned int GetTrgStatePtrn10Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11E4;
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1188;
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn10Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_STATE_PTRN11
   unsigned int GetTrgStatePtrn11()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x11EC, 0x0007FFFF, 0);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x1190, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn11() not defined for this board version");
      };
   };
   void SetTrgStatePtrn11(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x11EC, 0x0007FFFF, 0, value);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x1190, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgStatePtrn11() not defined for this board version");
      };
   };
   unsigned int GetTrgStatePtrn11Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11EC;
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1190;
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn11Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_STATE_PTRN12
   unsigned int GetTrgStatePtrn12()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x11F4, 0x0007FFFF, 0);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x1198, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn12() not defined for this board version");
      };
   };
   void SetTrgStatePtrn12(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x11F4, 0x0007FFFF, 0, value);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x1198, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgStatePtrn12() not defined for this board version");
      };
   };
   unsigned int GetTrgStatePtrn12Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11F4;
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1198;
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn12Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_STATE_PTRN13
   unsigned int GetTrgStatePtrn13()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x11FC, 0x0007FFFF, 0);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x11A0, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn13() not defined for this board version");
      };
   };
   void SetTrgStatePtrn13(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x11FC, 0x0007FFFF, 0, value);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x11A0, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgStatePtrn13() not defined for this board version");
      };
   };
   unsigned int GetTrgStatePtrn13Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11FC;
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11A0;
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn13Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_STATE_PTRN14
   unsigned int GetTrgStatePtrn14()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x1204, 0x0007FFFF, 0);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x11A8, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn14() not defined for this board version");
      };
   };
   void SetTrgStatePtrn14(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x1204, 0x0007FFFF, 0, value);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x11A8, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgStatePtrn14() not defined for this board version");
      };
   };
   unsigned int GetTrgStatePtrn14Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1204;
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11A8;
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn14Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_STATE_PTRN15
   unsigned int GetTrgStatePtrn15()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x120C, 0x0007FFFF, 0);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x11B0, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn15() not defined for this board version");
      };
   };
   void SetTrgStatePtrn15(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x120C, 0x0007FFFF, 0, value);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x11B0, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgStatePtrn15() not defined for this board version");
      };
   };
   unsigned int GetTrgStatePtrn15Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x120C;
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11B0;
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn15Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_STATE_PTRN16
   unsigned int GetTrgStatePtrn16()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x1214, 0x0007FFFF, 0);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x11B8, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn16() not defined for this board version");
      };
   };
   void SetTrgStatePtrn16(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x1214, 0x0007FFFF, 0, value);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x11B8, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgStatePtrn16() not defined for this board version");
      };
   };
   unsigned int GetTrgStatePtrn16Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1214;
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11B8;
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn16Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_STATE_PTRN17
   unsigned int GetTrgStatePtrn17()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x121C, 0x0007FFFF, 0);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x11C0, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn17() not defined for this board version");
      };
   };
   void SetTrgStatePtrn17(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x121C, 0x0007FFFF, 0, value);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x11C0, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgStatePtrn17() not defined for this board version");
      };
   };
   unsigned int GetTrgStatePtrn17Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x121C;
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11C0;
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn17Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_STATE_PTRN18
   unsigned int GetTrgStatePtrn18()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x1224, 0x0007FFFF, 0);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x11C8, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn18() not defined for this board version");
      };
   };
   void SetTrgStatePtrn18(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x1224, 0x0007FFFF, 0, value);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x11C8, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgStatePtrn18() not defined for this board version");
      };
   };
   unsigned int GetTrgStatePtrn18Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1224;
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11C8;
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn18Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_STATE_PTRN2
   unsigned int GetTrgStatePtrn2()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x11A4, 0x0007FFFF, 0);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x1148, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn2() not defined for this board version");
      };
   };
   void SetTrgStatePtrn2(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x11A4, 0x0007FFFF, 0, value);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x1148, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgStatePtrn2() not defined for this board version");
      };
   };
   unsigned int GetTrgStatePtrn2Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11A4;
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1148;
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn2Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_STATE_PTRN3
   unsigned int GetTrgStatePtrn3()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x11AC, 0x0007FFFF, 0);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x1150, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn3() not defined for this board version");
      };
   };
   void SetTrgStatePtrn3(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x11AC, 0x0007FFFF, 0, value);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x1150, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgStatePtrn3() not defined for this board version");
      };
   };
   unsigned int GetTrgStatePtrn3Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11AC;
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1150;
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn3Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_STATE_PTRN4
   unsigned int GetTrgStatePtrn4()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x11B4, 0x0007FFFF, 0);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x1158, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn4() not defined for this board version");
      };
   };
   void SetTrgStatePtrn4(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x11B4, 0x0007FFFF, 0, value);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x1158, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgStatePtrn4() not defined for this board version");
      };
   };
   unsigned int GetTrgStatePtrn4Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11B4;
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1158;
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn4Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_STATE_PTRN5
   unsigned int GetTrgStatePtrn5()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x11BC, 0x0007FFFF, 0);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x1160, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn5() not defined for this board version");
      };
   };
   void SetTrgStatePtrn5(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x11BC, 0x0007FFFF, 0, value);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x1160, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgStatePtrn5() not defined for this board version");
      };
   };
   unsigned int GetTrgStatePtrn5Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11BC;
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1160;
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn5Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_STATE_PTRN6
   unsigned int GetTrgStatePtrn6()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x11C4, 0x0007FFFF, 0);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x1168, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn6() not defined for this board version");
      };
   };
   void SetTrgStatePtrn6(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x11C4, 0x0007FFFF, 0, value);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x1168, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgStatePtrn6() not defined for this board version");
      };
   };
   unsigned int GetTrgStatePtrn6Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11C4;
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1168;
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn6Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_STATE_PTRN7
   unsigned int GetTrgStatePtrn7()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x11CC, 0x0007FFFF, 0);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x1170, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn7() not defined for this board version");
      };
   };
   void SetTrgStatePtrn7(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x11CC, 0x0007FFFF, 0, value);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x1170, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgStatePtrn7() not defined for this board version");
      };
   };
   unsigned int GetTrgStatePtrn7Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11CC;
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1170;
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn7Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_STATE_PTRN8
   unsigned int GetTrgStatePtrn8()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x11D4, 0x0007FFFF, 0);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x1178, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn8() not defined for this board version");
      };
   };
   void SetTrgStatePtrn8(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x11D4, 0x0007FFFF, 0, value);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x1178, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgStatePtrn8() not defined for this board version");
      };
   };
   unsigned int GetTrgStatePtrn8Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11D4;
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1178;
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn8Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_STATE_PTRN9
   unsigned int GetTrgStatePtrn9()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x11DC, 0x0007FFFF, 0);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return BitExtractControl(0x1180, 0x0007FFFF, 0);
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn9() not defined for this board version");
      };
   };
   void SetTrgStatePtrn9(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x11DC, 0x0007FFFF, 0, value);
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            return SetRegMask(0x1180, 0x0007FFFF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgStatePtrn9() not defined for this board version");
      };
   };
   unsigned int GetTrgStatePtrn9Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11DC;
         case 9:
            // trigger source state pattern (0 = Inhibit, 1 = Coincidence)
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1180;
         default:
            throw std::invalid_argument("Function GetTrgStatePtrn9Loc() not defined for this board version");
      };
   };

   // Bit(s) TRG_TX_EN
   unsigned int GetTrgTxEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // enable transmission of advanced trigger output data
            return BitExtractControl(0x1014, 0x08000000, 27);
         default:
            throw std::invalid_argument("Function GetTrgTxEn() not defined for this board version");
      };
   };
   void SetTrgTxEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // enable transmission of advanced trigger output data
            return SetRegMask(0x1014, 0x08000000, 27, value);
         default:
            throw std::invalid_argument("Function SetTrgTxEn() not defined for this board version");
      };
   };
   unsigned int GetTrgTxEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // enable transmission of advanced trigger output data
            if(BitMask) *BitMask = 0x08000000;
            if(BitOfs) *BitOfs = 27;
            return 0x1014;
         default:
            throw std::invalid_argument("Function GetTrgTxEnLoc() not defined for this board version");
      };
   };

   // Bit(s) TRG_TX_SAMPLES
   unsigned int GetTrgTxSamples()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Number of advanced trigger output samples to transmit (range 1 to 512)
            return BitExtractControl(0x1034, 0x000003FF, 0);
         default:
            throw std::invalid_argument("Function GetTrgTxSamples() not defined for this board version");
      };
   };
   void SetTrgTxSamples(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Number of advanced trigger output samples to transmit (range 1 to 512)
            return SetRegMask(0x1034, 0x000003FF, 0, value);
         default:
            throw std::invalid_argument("Function SetTrgTxSamples() not defined for this board version");
      };
   };
   unsigned int GetTrgTxSamplesLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Number of advanced trigger output samples to transmit (range 1 to 512)
            if(BitMask) *BitMask = 0x000003FF;
            if(BitOfs) *BitOfs = 0;
            return 0x1034;
         default:
            throw std::invalid_argument("Function GetTrgTxSamplesLoc() not defined for this board version");
      };
   };

   // Bit(s) TRIGGER_DAQ_CLK_CAL_MOD
   unsigned int GetTriggerDaqClkCalMod()
   {
      switch(this->mVersion)
      {
         case 8:
            // Trigger DAQ clock calibration modified flag
            return BitExtractStatus(0x0138, 0x00000010, 4);
         case 9:
            // Trigger DAQ clock calibration modified flag
            return BitExtractStatus(0x0134, 0x00000010, 4);
         default:
            throw std::invalid_argument("Function GetTriggerDaqClkCalMod() not defined for this board version");
      };
   };
   unsigned int GetTriggerDaqClkCalModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Trigger DAQ clock calibration modified flag
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x0138;
         case 9:
            // Trigger DAQ clock calibration modified flag
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x0134;
         default:
            throw std::invalid_argument("Function GetTriggerDaqClkCalModLoc() not defined for this board version");
      };
   };

   // Bit(s) TRIGGER_DELAY
   unsigned int GetTriggerDelay()
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger delay in ticks of 6.25 ns
            return BitExtractControl(0x1180, 0x000000FF, 0);
         case 9:
            // trigger delay in ticks of 6.25 ns
            return BitExtractControl(0x1124, 0x000000FF, 0);
         default:
            throw std::invalid_argument("Function GetTriggerDelay() not defined for this board version");
      };
   };
   void SetTriggerDelay(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger delay in ticks of 6.25 ns
            return SetRegMask(0x1180, 0x000000FF, 0, value);
         case 9:
            // trigger delay in ticks of 6.25 ns
            return SetRegMask(0x1124, 0x000000FF, 0, value);
         default:
            throw std::invalid_argument("Function SetTriggerDelay() not defined for this board version");
      };
   };
   unsigned int GetTriggerDelayLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // trigger delay in ticks of 6.25 ns
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x1180;
         case 9:
            // trigger delay in ticks of 6.25 ns
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x1124;
         default:
            throw std::invalid_argument("Function GetTriggerDelayLoc() not defined for this board version");
      };
   };

   // Bit(s) TRIGGER_OUT_PULSE_LENGTH
   unsigned int GetTriggerOutPulseLength()
   {
      switch(this->mVersion)
      {
         case 8:
            // Length of the trigger output pulse in cycles
            return BitExtractControl(0x1180, 0x1F000000, 24);
         case 9:
            // Length of the trigger output pulse in cycles
            return BitExtractControl(0x1124, 0x1F000000, 24);
         default:
            throw std::invalid_argument("Function GetTriggerOutPulseLength() not defined for this board version");
      };
   };
   void SetTriggerOutPulseLength(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            // Length of the trigger output pulse in cycles
            return SetRegMask(0x1180, 0x1F000000, 24, value);
         case 9:
            // Length of the trigger output pulse in cycles
            return SetRegMask(0x1124, 0x1F000000, 24, value);
         default:
            throw std::invalid_argument("Function SetTriggerOutPulseLength() not defined for this board version");
      };
   };
   unsigned int GetTriggerOutPulseLengthLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            // Length of the trigger output pulse in cycles
            if(BitMask) *BitMask = 0x1F000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1180;
         case 9:
            // Length of the trigger output pulse in cycles
            if(BitMask) *BitMask = 0x1F000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1124;
         default:
            throw std::invalid_argument("Function GetTriggerOutPulseLengthLoc() not defined for this board version");
      };
   };

   // Bit(s) TRIG_DAQ_CLK_CAL_CHK
   unsigned int GetTrigDaqClkCalChk()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Trigger DAQ clock calibration check
            return BitExtractControl(0x100C, 0x01000000, 24);
         default:
            throw std::invalid_argument("Function GetTrigDaqClkCalChk() not defined for this board version");
      };
   };
   void SetTrigDaqClkCalChk(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Trigger DAQ clock calibration check
            return SetRegMask(0x100C, 0x01000000, 24, value);
         default:
            throw std::invalid_argument("Function SetTrigDaqClkCalChk() not defined for this board version");
      };
   };
   unsigned int GetTrigDaqClkCalChkLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Trigger DAQ clock calibration check
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x100C;
         default:
            throw std::invalid_argument("Function GetTrigDaqClkCalChkLoc() not defined for this board version");
      };
   };

   // Bit(s) VALID_DELAY_ADC
   unsigned int GetValidDelayAdc()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Delay of the data valid at the ISERDES of the ADCs (delay = value + 1)
            return BitExtractControl(0x1004, 0x3F000000, 24);
         default:
            throw std::invalid_argument("Function GetValidDelayAdc() not defined for this board version");
      };
   };
   void SetValidDelayAdc(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Delay of the data valid at the ISERDES of the ADCs (delay = value + 1)
            return SetRegMask(0x1004, 0x3F000000, 24, value);
         default:
            throw std::invalid_argument("Function SetValidDelayAdc() not defined for this board version");
      };
   };
   unsigned int GetValidDelayAdcLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Delay of the data valid at the ISERDES of the ADCs (delay = value + 1)
            if(BitMask) *BitMask = 0x3F000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1004;
         default:
            throw std::invalid_argument("Function GetValidDelayAdcLoc() not defined for this board version");
      };
   };

   // Bit(s) VENDOR_ID
   unsigned int GetVendorId()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // ID of the board vendor (0x01 for PSI)
            return BitExtractStatus(0x0000, 0x00FF0000, 16);
         default:
            throw std::invalid_argument("Function GetVendorId() not defined for this board version");
      };
   };
   unsigned int GetVendorIdLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // ID of the board vendor (0x01 for PSI)
            if(BitMask) *BitMask = 0x00FF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0000;
         default:
            throw std::invalid_argument("Function GetVendorIdLoc() not defined for this board version");
      };
   };

   // Bit(s) WD_PKGR_RST
   unsigned int GetWdPkgrRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // WaveDream packager reset
            return BitExtractControl(0x1040, 0x00000008, 3);
         default:
            throw std::invalid_argument("Function GetWdPkgrRst() not defined for this board version");
      };
   };
   void SetWdPkgrRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // WaveDream packager reset
            return SetRegMask(0x1040, 0x00000008, 3, value);
         default:
            throw std::invalid_argument("Function SetWdPkgrRst() not defined for this board version");
      };
   };
   unsigned int GetWdPkgrRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // WaveDream packager reset
            if(BitMask) *BitMask = 0x00000008;
            if(BitOfs) *BitOfs = 3;
            return 0x1040;
         default:
            throw std::invalid_argument("Function GetWdPkgrRstLoc() not defined for this board version");
      };
   };

   // Bit(s) ZERO_SUPR_EN
   unsigned int GetZeroSuprEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable zero suppression for data transmission (only transmit channels that triggered)
            return BitExtractControl(0x103C, 0x00000100, 8);
         default:
            throw std::invalid_argument("Function GetZeroSuprEn() not defined for this board version");
      };
   };
   void SetZeroSuprEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable zero suppression for data transmission (only transmit channels that triggered)
            return SetRegMask(0x103C, 0x00000100, 8, value);
         default:
            throw std::invalid_argument("Function SetZeroSuprEn() not defined for this board version");
      };
   };
   unsigned int GetZeroSuprEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Enable zero suppression for data transmission (only transmit channels that triggered)
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x103C;
         default:
            throw std::invalid_argument("Function GetZeroSuprEnLoc() not defined for this board version");
      };
   };

   // Bit(s) ZERO_SUPR_WINDOW
   unsigned int GetZeroSuprWindow()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Zero suppression time window in DAQ clock ticks (channel polarity defined in TRG_SRC_POL)
            return BitExtractControl(0x103C, 0x000000FF, 0);
         default:
            throw std::invalid_argument("Function GetZeroSuprWindow() not defined for this board version");
      };
   };
   void SetZeroSuprWindow(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Zero suppression time window in DAQ clock ticks (channel polarity defined in TRG_SRC_POL)
            return SetRegMask(0x103C, 0x000000FF, 0, value);
         default:
            throw std::invalid_argument("Function SetZeroSuprWindow() not defined for this board version");
      };
   };
   unsigned int GetZeroSuprWindowLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            // Zero suppression time window in DAQ clock ticks (channel polarity defined in TRG_SRC_POL)
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x103C;
         default:
            throw std::invalid_argument("Function GetZeroSuprWindowLoc() not defined for this board version");
      };
   };

//--------------------------------------------------------------------
// Register Group Functions
//--------------------------------------------------------------------

   // Register Group ADC
   unsigned int GetAdcGroupParam(unsigned int *GrpLen)
   {
      switch(this->mVersion)
      {
         case 8:
            if(GrpLen) *GrpLen = 27;
            return 0x1114;
         case 9:
            if(GrpLen) *GrpLen = 4;
            return 0x1114;
         default:
            throw std::invalid_argument("Function GetAdcGroupParam() not defined for this board version");
      };
   };

   // Register Group ADV_TRG_CTRL
   unsigned int GetAdvTrgCtrlGroupParam(unsigned int *GrpLen)
   {
      switch(this->mVersion)
      {
         case 8:
            if(GrpLen) *GrpLen = 20;
            return 0x1228;
         case 9:
            if(GrpLen) *GrpLen = 20;
            return 0x11CC;
         default:
            throw std::invalid_argument("Function GetAdvTrgCtrlGroupParam() not defined for this board version");
      };
   };

   // Register Group ADV_TRG_STAT
   unsigned int GetAdvTrgStatGroupParam(unsigned int *GrpLen)
   {
      switch(this->mVersion)
      {
         case 8:
            if(GrpLen) *GrpLen = 5;
            return 0x0114;
         case 9:
            if(GrpLen) *GrpLen = 5;
            return 0x0110;
         default:
            throw std::invalid_argument("Function GetAdvTrgStatGroupParam() not defined for this board version");
      };
   };

   // Register Group DAC
   unsigned int GetDacGroupParam(unsigned int *GrpLen)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(GrpLen) *GrpLen = 12;
            return 0x1048;
         default:
            throw std::invalid_argument("Function GetDacGroupParam() not defined for this board version");
      };
   };

   // Register Group FE_CFG
   unsigned int GetFeCfgGroupParam(unsigned int *GrpLen)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(GrpLen) *GrpLen = 8;
            return 0x1078;
         default:
            throw std::invalid_argument("Function GetFeCfgGroupParam() not defined for this board version");
      };
   };

   // Register Group HF_TEMP
   unsigned int GetHfTempGroupParam(unsigned int *GrpLen)
   {
      switch(this->mVersion)
      {
         case 8:
            if(GrpLen) *GrpLen = 4;
            return 0x0090;
         case 9:
            if(GrpLen) *GrpLen = 4;
            return 0x008C;
         default:
            throw std::invalid_argument("Function GetHfTempGroupParam() not defined for this board version");
      };
   };

   // Register Group HV_I_MEAS
   unsigned int GetHvIMeasGroupParam(unsigned int *GrpLen)
   {
      switch(this->mVersion)
      {
         case 8:
            if(GrpLen) *GrpLen = 16;
            return 0x004C;
         case 9:
            if(GrpLen) *GrpLen = 16;
            return 0x0048;
         default:
            throw std::invalid_argument("Function GetHvIMeasGroupParam() not defined for this board version");
      };
   };

   // Register Group HV_U_TARGET
   unsigned int GetHvUTargetGroupParam(unsigned int *GrpLen)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(GrpLen) *GrpLen = 16;
            return 0x1098;
         default:
            throw std::invalid_argument("Function GetHvUTargetGroupParam() not defined for this board version");
      };
   };

   // Register Group LMK
   unsigned int GetLmkGroupParam(unsigned int *GrpLen)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(GrpLen) *GrpLen = 14;
            return 0x10DC;
         default:
            throw std::invalid_argument("Function GetLmkGroupParam() not defined for this board version");
      };
   };

   // Register Group SCALER
   unsigned int GetScalerGroupParam(unsigned int *GrpLen)
   {
      switch(this->mVersion)
      {
         case 8:
            if(GrpLen) *GrpLen = 19;
            return 0x00A0;
         case 9:
            if(GrpLen) *GrpLen = 19;
            return 0x009C;
         default:
            throw std::invalid_argument("Function GetScalerGroupParam() not defined for this board version");
      };
   };

   // Register Group TRIGGER
   unsigned int GetTriggerGroupParam(unsigned int *GrpLen)
   {
      switch(this->mVersion)
      {
         case 8:
            if(GrpLen) *GrpLen = 42;
            return 0x1180;
         case 9:
            if(GrpLen) *GrpLen = 42;
            return 0x1124;
         default:
            throw std::invalid_argument("Function GetTriggerGroupParam() not defined for this board version");
      };
   };


};

//--------------------------------------------------------------------

#endif /* defined(__wdbreg_h__) */

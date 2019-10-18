//
//  WDBReg.h
//
//  WaveDAQ Register Access Class
//
//  This file is generated automatically, please do not edit!
//
// Created :  18.10.2019 09:41:58
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

public:

   // constructor
   unsigned int WDBREG()
   {
      this->mVersion = BitExtractStatus(mVersionReg, mVersionMask, mVersionOffs);
      retur this->mVersion;
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
            return BitExtractControl(0x1114, 0x80000000, 31);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc01458Dcsoff(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1114, 0x80000000, 31, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc01458DcsoffLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x80000000;
            if(BitOfs) *BitOfs = 31;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_1458_ILVDS
   unsigned int GetAdc01458Ilvds()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1114, 0x00E00000, 21);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc01458Ilvds(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1114, 0x00E00000, 21, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc01458IlvdsLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00E00000;
            if(BitOfs) *BitOfs = 21;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_1458_OUTMODE
   unsigned int GetAdc01458Outmode()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1114, 0x00070000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc01458Outmode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1114, 0x00070000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc01458OutmodeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00070000;
            if(BitOfs) *BitOfs = 16;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_1458_OUTOFF
   unsigned int GetAdc01458Outoff()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1114, 0x00080000, 19);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc01458Outoff(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1114, 0x00080000, 19, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc01458OutoffLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00080000;
            if(BitOfs) *BitOfs = 19;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_1458_OUTTEST
   unsigned int GetAdc01458Outtest()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1114, 0x00008000, 15);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc01458Outtest(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1114, 0x00008000, 15, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc01458OuttestLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00008000;
            if(BitOfs) *BitOfs = 15;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_1458_RAND
   unsigned int GetAdc01458Rand()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1114, 0x40000000, 30);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc01458Rand(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1114, 0x40000000, 30, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc01458RandLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x40000000;
            if(BitOfs) *BitOfs = 30;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_1458_SLEEP
   unsigned int GetAdc01458Sleep()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1114, 0x10000000, 28);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc01458Sleep(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1114, 0x10000000, 28, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc01458SleepLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x10000000;
            if(BitOfs) *BitOfs = 28;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_1458_TERMON
   unsigned int GetAdc01458Termon()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1114, 0x00100000, 20);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc01458Termon(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1114, 0x00100000, 20, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc01458TermonLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_1458_TP
   unsigned int GetAdc01458Tp()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1114, 0x00003FFC, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc01458Tp(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1114, 0x00003FFC, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc01458TpLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00003FFC;
            if(BitOfs) *BitOfs = 2;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_1458_TP_LSBS
   unsigned int GetAdc01458TpLsbs()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1114, 0x00000003, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc01458TpLsbs(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1114, 0x00000003, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc01458TpLsbsLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_1458_TWOSCOMP
   unsigned int GetAdc01458Twoscomp()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1114, 0x20000000, 29);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc01458Twoscomp(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1114, 0x20000000, 29, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc01458TwoscompLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x20000000;
            if(BitOfs) *BitOfs = 29;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_1_NAP_MODE
   unsigned int GetAdc01NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1114, 0x01000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc01NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1114, 0x01000000, 24, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc01NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_2367_DCSOFF
   unsigned int GetAdc02367Dcsoff()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1118, 0x80000000, 31);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc02367Dcsoff(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1118, 0x80000000, 31, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc02367DcsoffLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x80000000;
            if(BitOfs) *BitOfs = 31;
            return 0x1118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_2367_ILVDS
   unsigned int GetAdc02367Ilvds()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1118, 0x00E00000, 21);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc02367Ilvds(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1118, 0x00E00000, 21, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc02367IlvdsLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00E00000;
            if(BitOfs) *BitOfs = 21;
            return 0x1118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_2367_OUTMODE
   unsigned int GetAdc02367Outmode()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1118, 0x00070000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc02367Outmode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1118, 0x00070000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc02367OutmodeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00070000;
            if(BitOfs) *BitOfs = 16;
            return 0x1118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_2367_OUTOFF
   unsigned int GetAdc02367Outoff()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1118, 0x00080000, 19);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc02367Outoff(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1118, 0x00080000, 19, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc02367OutoffLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00080000;
            if(BitOfs) *BitOfs = 19;
            return 0x1118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_2367_OUTTEST
   unsigned int GetAdc02367Outtest()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1118, 0x00008000, 15);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc02367Outtest(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1118, 0x00008000, 15, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc02367OuttestLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00008000;
            if(BitOfs) *BitOfs = 15;
            return 0x1118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_2367_RAND
   unsigned int GetAdc02367Rand()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1118, 0x40000000, 30);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc02367Rand(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1118, 0x40000000, 30, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc02367RandLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x40000000;
            if(BitOfs) *BitOfs = 30;
            return 0x1118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_2367_SLEEP
   unsigned int GetAdc02367Sleep()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1118, 0x10000000, 28);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc02367Sleep(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1118, 0x10000000, 28, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc02367SleepLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x10000000;
            if(BitOfs) *BitOfs = 28;
            return 0x1118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_2367_TERMON
   unsigned int GetAdc02367Termon()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1118, 0x00100000, 20);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc02367Termon(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1118, 0x00100000, 20, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc02367TermonLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x1118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_2367_TP
   unsigned int GetAdc02367Tp()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1118, 0x00003FFC, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc02367Tp(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1118, 0x00003FFC, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc02367TpLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00003FFC;
            if(BitOfs) *BitOfs = 2;
            return 0x1118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_2367_TP_LSBS
   unsigned int GetAdc02367TpLsbs()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1118, 0x00000003, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc02367TpLsbs(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1118, 0x00000003, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc02367TpLsbsLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x1118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_2367_TWOSCOMP
   unsigned int GetAdc02367Twoscomp()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1118, 0x20000000, 29);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc02367Twoscomp(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1118, 0x20000000, 29, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc02367TwoscompLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x20000000;
            if(BitOfs) *BitOfs = 29;
            return 0x1118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_2_NAP_MODE
   unsigned int GetAdc02NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1118, 0x01000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc02NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1118, 0x01000000, 24, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc02NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_3_NAP_MODE
   unsigned int GetAdc03NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1118, 0x02000000, 25);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc03NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1118, 0x02000000, 25, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc03NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x02000000;
            if(BitOfs) *BitOfs = 25;
            return 0x1118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_4_NAP_MODE
   unsigned int GetAdc04NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1114, 0x02000000, 25);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc04NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1114, 0x02000000, 25, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc04NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x02000000;
            if(BitOfs) *BitOfs = 25;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_5_NAP_MODE
   unsigned int GetAdc05NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1114, 0x04000000, 26);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc05NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1114, 0x04000000, 26, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc05NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x04000000;
            if(BitOfs) *BitOfs = 26;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_6_NAP_MODE
   unsigned int GetAdc06NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1118, 0x04000000, 26);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc06NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1118, 0x04000000, 26, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc06NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x04000000;
            if(BitOfs) *BitOfs = 26;
            return 0x1118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_7_NAP_MODE
   unsigned int GetAdc07NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1118, 0x08000000, 27);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc07NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1118, 0x08000000, 27, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc07NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x08000000;
            if(BitOfs) *BitOfs = 27;
            return 0x1118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_8_NAP_MODE
   unsigned int GetAdc08NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1114, 0x08000000, 27);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc08NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1114, 0x08000000, 27, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc08NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x08000000;
            if(BitOfs) *BitOfs = 27;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_CHIP_ID
   unsigned int GetAdc0ChipId()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0044, 0xFF000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc0ChipIdLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFF000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0044;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_0_SPEED
   unsigned int GetAdc0Speed()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0044, 0x00700000, 20);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc0SpeedLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00700000;
            if(BitOfs) *BitOfs = 20;
            return 0x0044;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_1458_DCSOFF
   unsigned int GetAdc11458Dcsoff()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x111C, 0x80000000, 31);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc11458Dcsoff(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x111C, 0x80000000, 31, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc11458DcsoffLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x80000000;
            if(BitOfs) *BitOfs = 31;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_1458_ILVDS
   unsigned int GetAdc11458Ilvds()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x111C, 0x00E00000, 21);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc11458Ilvds(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x111C, 0x00E00000, 21, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc11458IlvdsLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00E00000;
            if(BitOfs) *BitOfs = 21;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_1458_OUTMODE
   unsigned int GetAdc11458Outmode()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x111C, 0x00070000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc11458Outmode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x111C, 0x00070000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc11458OutmodeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00070000;
            if(BitOfs) *BitOfs = 16;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_1458_OUTOFF
   unsigned int GetAdc11458Outoff()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x111C, 0x00080000, 19);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc11458Outoff(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x111C, 0x00080000, 19, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc11458OutoffLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00080000;
            if(BitOfs) *BitOfs = 19;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_1458_OUTTEST
   unsigned int GetAdc11458Outtest()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x111C, 0x00008000, 15);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc11458Outtest(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x111C, 0x00008000, 15, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc11458OuttestLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00008000;
            if(BitOfs) *BitOfs = 15;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_1458_RAND
   unsigned int GetAdc11458Rand()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x111C, 0x40000000, 30);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc11458Rand(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x111C, 0x40000000, 30, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc11458RandLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x40000000;
            if(BitOfs) *BitOfs = 30;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_1458_SLEEP
   unsigned int GetAdc11458Sleep()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x111C, 0x10000000, 28);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc11458Sleep(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x111C, 0x10000000, 28, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc11458SleepLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x10000000;
            if(BitOfs) *BitOfs = 28;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_1458_TERMON
   unsigned int GetAdc11458Termon()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x111C, 0x00100000, 20);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc11458Termon(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x111C, 0x00100000, 20, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc11458TermonLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_1458_TP
   unsigned int GetAdc11458Tp()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x111C, 0x00003FFC, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc11458Tp(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x111C, 0x00003FFC, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc11458TpLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00003FFC;
            if(BitOfs) *BitOfs = 2;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_1458_TP_LSBS
   unsigned int GetAdc11458TpLsbs()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x111C, 0x00000003, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc11458TpLsbs(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x111C, 0x00000003, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc11458TpLsbsLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_1458_TWOSCOMP
   unsigned int GetAdc11458Twoscomp()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x111C, 0x20000000, 29);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc11458Twoscomp(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x111C, 0x20000000, 29, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc11458TwoscompLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x20000000;
            if(BitOfs) *BitOfs = 29;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_1_NAP_MODE
   unsigned int GetAdc11NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x111C, 0x01000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc11NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x111C, 0x01000000, 24, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc11NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_2367_DCSOFF
   unsigned int GetAdc12367Dcsoff()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1120, 0x80000000, 31);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc12367Dcsoff(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1120, 0x80000000, 31, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc12367DcsoffLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x80000000;
            if(BitOfs) *BitOfs = 31;
            return 0x1120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_2367_ILVDS
   unsigned int GetAdc12367Ilvds()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1120, 0x00E00000, 21);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc12367Ilvds(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1120, 0x00E00000, 21, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc12367IlvdsLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00E00000;
            if(BitOfs) *BitOfs = 21;
            return 0x1120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_2367_OUTMODE
   unsigned int GetAdc12367Outmode()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1120, 0x00070000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc12367Outmode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1120, 0x00070000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc12367OutmodeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00070000;
            if(BitOfs) *BitOfs = 16;
            return 0x1120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_2367_OUTOFF
   unsigned int GetAdc12367Outoff()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1120, 0x00080000, 19);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc12367Outoff(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1120, 0x00080000, 19, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc12367OutoffLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00080000;
            if(BitOfs) *BitOfs = 19;
            return 0x1120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_2367_OUTTEST
   unsigned int GetAdc12367Outtest()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1120, 0x00008000, 15);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc12367Outtest(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1120, 0x00008000, 15, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc12367OuttestLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00008000;
            if(BitOfs) *BitOfs = 15;
            return 0x1120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_2367_RAND
   unsigned int GetAdc12367Rand()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1120, 0x40000000, 30);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc12367Rand(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1120, 0x40000000, 30, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc12367RandLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x40000000;
            if(BitOfs) *BitOfs = 30;
            return 0x1120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_2367_SLEEP
   unsigned int GetAdc12367Sleep()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1120, 0x10000000, 28);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc12367Sleep(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1120, 0x10000000, 28, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc12367SleepLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x10000000;
            if(BitOfs) *BitOfs = 28;
            return 0x1120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_2367_TERMON
   unsigned int GetAdc12367Termon()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1120, 0x00100000, 20);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc12367Termon(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1120, 0x00100000, 20, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc12367TermonLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x1120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_2367_TP
   unsigned int GetAdc12367Tp()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1120, 0x00003FFC, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc12367Tp(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1120, 0x00003FFC, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc12367TpLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00003FFC;
            if(BitOfs) *BitOfs = 2;
            return 0x1120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_2367_TP_LSBS
   unsigned int GetAdc12367TpLsbs()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1120, 0x00000003, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc12367TpLsbs(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1120, 0x00000003, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc12367TpLsbsLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x1120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_2367_TWOSCOMP
   unsigned int GetAdc12367Twoscomp()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1120, 0x20000000, 29);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc12367Twoscomp(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1120, 0x20000000, 29, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc12367TwoscompLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x20000000;
            if(BitOfs) *BitOfs = 29;
            return 0x1120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_2_NAP_MODE
   unsigned int GetAdc12NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1120, 0x01000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc12NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1120, 0x01000000, 24, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc12NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_3_NAP_MODE
   unsigned int GetAdc13NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1120, 0x02000000, 25);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc13NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1120, 0x02000000, 25, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc13NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x02000000;
            if(BitOfs) *BitOfs = 25;
            return 0x1120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_4_NAP_MODE
   unsigned int GetAdc14NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x111C, 0x02000000, 25);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc14NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x111C, 0x02000000, 25, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc14NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x02000000;
            if(BitOfs) *BitOfs = 25;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_5_NAP_MODE
   unsigned int GetAdc15NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x111C, 0x04000000, 26);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc15NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x111C, 0x04000000, 26, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc15NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x04000000;
            if(BitOfs) *BitOfs = 26;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_6_NAP_MODE
   unsigned int GetAdc16NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1120, 0x04000000, 26);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc16NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1120, 0x04000000, 26, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc16NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x04000000;
            if(BitOfs) *BitOfs = 26;
            return 0x1120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_7_NAP_MODE
   unsigned int GetAdc17NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1120, 0x08000000, 27);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc17NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1120, 0x08000000, 27, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc17NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x08000000;
            if(BitOfs) *BitOfs = 27;
            return 0x1120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_8_NAP_MODE
   unsigned int GetAdc18NapMode()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x111C, 0x08000000, 27);
         default:
            throw 20;
      };
   };
   unsigned int SetAdc18NapMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x111C, 0x08000000, 27, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc18NapModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x08000000;
            if(BitOfs) *BitOfs = 27;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_CHIP_ID
   unsigned int GetAdc1ChipId()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0044, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc1ChipIdLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x0044;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_1_SPEED
   unsigned int GetAdc1Speed()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0044, 0x00000070, 4);
         default:
            throw 20;
      };
   };
   unsigned int GetAdc1SpeedLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000070;
            if(BitOfs) *BitOfs = 4;
            return 0x0044;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_CFG_16_BIT_ADDR_LSB
   unsigned int GetAdcCfg16BitAddrLsb()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1114, 0x08000000, 27);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcCfg16BitAddrLsb(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1114, 0x08000000, 27, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcCfg16BitAddrLsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x08000000;
            if(BitOfs) *BitOfs = 27;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_CFG_16_BIT_ADDR_MSB
   unsigned int GetAdcCfg16BitAddrMsb()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1114, 0x10000000, 28);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcCfg16BitAddrMsb(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1114, 0x10000000, 28, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcCfg16BitAddrMsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x10000000;
            if(BitOfs) *BitOfs = 28;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_CFG_LSB_FIRST_LSB
   unsigned int GetAdcCfgLsbFirstLsb()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1114, 0x02000000, 25);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcCfgLsbFirstLsb(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1114, 0x02000000, 25, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcCfgLsbFirstLsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x02000000;
            if(BitOfs) *BitOfs = 25;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_CFG_LSB_FIRST_MSB
   unsigned int GetAdcCfgLsbFirstMsb()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1114, 0x40000000, 30);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcCfgLsbFirstMsb(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1114, 0x40000000, 30, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcCfgLsbFirstMsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x40000000;
            if(BitOfs) *BitOfs = 30;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_CFG_SDO_ACTIVE_LSB
   unsigned int GetAdcCfgSdoActiveLsb()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1114, 0x01000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcCfgSdoActiveLsb(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1114, 0x01000000, 24, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcCfgSdoActiveLsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_CFG_SDO_ACTIVE_MSB
   unsigned int GetAdcCfgSdoActiveMsb()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1114, 0x80000000, 31);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcCfgSdoActiveMsb(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1114, 0x80000000, 31, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcCfgSdoActiveMsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x80000000;
            if(BitOfs) *BitOfs = 31;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_CFG_SOFT_RESET_LSB
   unsigned int GetAdcCfgSoftResetLsb()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1114, 0x04000000, 26);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcCfgSoftResetLsb(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1114, 0x04000000, 26, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcCfgSoftResetLsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x04000000;
            if(BitOfs) *BitOfs = 26;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_CFG_SOFT_RESET_MSB
   unsigned int GetAdcCfgSoftResetMsb()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1114, 0x20000000, 29);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcCfgSoftResetMsb(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1114, 0x20000000, 29, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcCfgSoftResetMsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x20000000;
            if(BitOfs) *BitOfs = 29;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_CH_TX_EN
   unsigned int GetAdcChTxEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1020, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcChTxEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1020, 0x0000FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcChTxEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1020;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_CLK_DIV_RATIO
   unsigned int GetAdcClkDivRatio()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1118, 0x00000700, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcClkDivRatio(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1118, 0x00000700, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcClkDivRatioLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000700;
            if(BitOfs) *BitOfs = 8;
            return 0x1118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_CLK_DUTY_CYC_STAB
   unsigned int GetAdcClkDutyCycStab()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1118, 0x00010000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcClkDutyCycStab(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1118, 0x00010000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcClkDutyCycStabLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x1118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_DI1_C_CHN_DCO
   unsigned int GetAdcDi1CChnDco()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1114, 0x00002000, 13);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcDi1CChnDco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1114, 0x00002000, 13, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcDi1CChnDcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00002000;
            if(BitOfs) *BitOfs = 13;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_DI1_C_CHN_FCO
   unsigned int GetAdcDi1CChnFco()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1114, 0x00001000, 12);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcDi1CChnFco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1114, 0x00001000, 12, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcDi1CChnFcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00001000;
            if(BitOfs) *BitOfs = 12;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_DI1_D_CHN_A
   unsigned int GetAdcDi1DChnA()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1114, 0x00000100, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcDi1DChnA(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1114, 0x00000100, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcDi1DChnALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_DI1_D_CHN_B
   unsigned int GetAdcDi1DChnB()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1114, 0x00000200, 9);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcDi1DChnB(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1114, 0x00000200, 9, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcDi1DChnBLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000200;
            if(BitOfs) *BitOfs = 9;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_DI1_D_CHN_C
   unsigned int GetAdcDi1DChnC()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1114, 0x00000400, 10);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcDi1DChnC(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1114, 0x00000400, 10, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcDi1DChnCLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000400;
            if(BitOfs) *BitOfs = 10;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_DI1_D_CHN_D
   unsigned int GetAdcDi1DChnD()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1114, 0x00000800, 11);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcDi1DChnD(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1114, 0x00000800, 11, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcDi1DChnDLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000800;
            if(BitOfs) *BitOfs = 11;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_DI2_D_CHN_E
   unsigned int GetAdcDi2DChnE()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1114, 0x00010000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcDi2DChnE(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1114, 0x00010000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcDi2DChnELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_DI2_D_CHN_F
   unsigned int GetAdcDi2DChnF()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1114, 0x00020000, 17);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcDi2DChnF(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1114, 0x00020000, 17, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcDi2DChnFLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00020000;
            if(BitOfs) *BitOfs = 17;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_DI2_D_CHN_G
   unsigned int GetAdcDi2DChnG()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1114, 0x00040000, 18);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcDi2DChnG(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1114, 0x00040000, 18, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcDi2DChnGLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00040000;
            if(BitOfs) *BitOfs = 18;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_DI2_D_CHN_H
   unsigned int GetAdcDi2DChnH()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1114, 0x00080000, 19);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcDi2DChnH(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1114, 0x00080000, 19, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcDi2DChnHLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00080000;
            if(BitOfs) *BitOfs = 19;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_ENH_CHOP_MODE
   unsigned int GetAdcEnhChopMode()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1118, 0x00000010, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcEnhChopMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1118, 0x00000010, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcEnhChopModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x1118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_EN_SYNC
   unsigned int GetAdcEnSync()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x112C, 0x00000001, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcEnSync(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x112C, 0x00000001, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcEnSyncLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x112C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_IF_RST
   unsigned int GetAdcIfRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1040, 0x00000020, 5);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcIfRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1040, 0x00000020, 5, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcIfRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x1040;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_INT_VREF_ADJ
   unsigned int GetAdcIntVrefAdj()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1120, 0x00000007, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcIntVrefAdj(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1120, 0x00000007, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcIntVrefAdjLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000007;
            if(BitOfs) *BitOfs = 0;
            return 0x1120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OA_OUT_DRIVE
   unsigned int GetAdcOaOutDrive()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1120, 0x00010000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOaOutDrive(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1120, 0x00010000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOaOutDriveLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x1120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OA_OUT_DRV_TERM
   unsigned int GetAdcOaOutDrvTerm()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1120, 0x00300000, 20);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOaOutDrvTerm(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1120, 0x00300000, 20, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOaOutDrvTermLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00300000;
            if(BitOfs) *BitOfs = 20;
            return 0x1120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ
   unsigned int GetAdcOffsAdj()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x111C, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x111C, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdjLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ_0_A
   unsigned int GetAdcOffsAdj0A()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1130, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj0A(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1130, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdj0ALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1130;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ_0_B
   unsigned int GetAdcOffsAdj0B()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1134, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj0B(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1134, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdj0BLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1134;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ_0_C
   unsigned int GetAdcOffsAdj0C()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1138, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj0C(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1138, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdj0CLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1138;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ_0_D
   unsigned int GetAdcOffsAdj0D()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x113C, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj0D(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x113C, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdj0DLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x113C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ_0_DCO
   unsigned int GetAdcOffsAdj0Dco()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1150, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj0Dco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1150, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdj0DcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1150;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ_0_E
   unsigned int GetAdcOffsAdj0E()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1140, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj0E(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1140, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdj0ELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1140;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ_0_F
   unsigned int GetAdcOffsAdj0F()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1144, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj0F(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1144, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdj0FLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1144;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ_0_FCO
   unsigned int GetAdcOffsAdj0Fco()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1154, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj0Fco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1154, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdj0FcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1154;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ_0_G
   unsigned int GetAdcOffsAdj0G()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1148, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj0G(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1148, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdj0GLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1148;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ_0_H
   unsigned int GetAdcOffsAdj0H()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x114C, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj0H(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x114C, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdj0HLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x114C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ_1_A
   unsigned int GetAdcOffsAdj1A()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1158, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj1A(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1158, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdj1ALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1158;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ_1_B
   unsigned int GetAdcOffsAdj1B()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x115C, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj1B(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x115C, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdj1BLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x115C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ_1_C
   unsigned int GetAdcOffsAdj1C()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1160, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj1C(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1160, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdj1CLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1160;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ_1_D
   unsigned int GetAdcOffsAdj1D()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1164, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj1D(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1164, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdj1DLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1164;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ_1_DCO
   unsigned int GetAdcOffsAdj1Dco()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1178, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj1Dco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1178, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdj1DcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1178;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ_1_E
   unsigned int GetAdcOffsAdj1E()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1168, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj1E(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1168, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdj1ELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1168;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ_1_F
   unsigned int GetAdcOffsAdj1F()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x116C, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj1F(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x116C, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdj1FLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x116C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ_1_FCO
   unsigned int GetAdcOffsAdj1Fco()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x117C, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj1Fco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x117C, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdj1FcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x117C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ_1_G
   unsigned int GetAdcOffsAdj1G()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1170, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj1G(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1170, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdj1GLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1170;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OFFS_ADJ_1_H
   unsigned int GetAdcOffsAdj1H()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1174, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOffsAdj1H(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1174, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOffsAdj1HLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1174;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_LVDS_MODE
   unsigned int GetAdcOmLvdsMode()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x111C, 0x00000040, 6);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmLvdsMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x111C, 0x00000040, 6, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmLvdsModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_FORMAT
   unsigned int GetAdcOmOutFormat()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x111C, 0x00000001, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutFormat(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x111C, 0x00000001, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutFormatLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT
   unsigned int GetAdcOmOutInvert()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x111C, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x111C, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvertLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_0_A
   unsigned int GetAdcOmOutInvert0A()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1130, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert0A(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1130, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvert0ALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1130;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_0_B
   unsigned int GetAdcOmOutInvert0B()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1134, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert0B(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1134, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvert0BLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1134;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_0_C
   unsigned int GetAdcOmOutInvert0C()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1138, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert0C(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1138, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvert0CLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1138;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_0_D
   unsigned int GetAdcOmOutInvert0D()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x113C, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert0D(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x113C, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvert0DLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x113C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_0_DCO
   unsigned int GetAdcOmOutInvert0Dco()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1150, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert0Dco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1150, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvert0DcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1150;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_0_E
   unsigned int GetAdcOmOutInvert0E()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1140, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert0E(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1140, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvert0ELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1140;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_0_F
   unsigned int GetAdcOmOutInvert0F()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1144, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert0F(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1144, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvert0FLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1144;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_0_FCO
   unsigned int GetAdcOmOutInvert0Fco()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1154, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert0Fco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1154, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvert0FcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1154;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_0_G
   unsigned int GetAdcOmOutInvert0G()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1148, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert0G(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1148, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvert0GLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1148;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_0_H
   unsigned int GetAdcOmOutInvert0H()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x114C, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert0H(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x114C, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvert0HLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x114C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_1_A
   unsigned int GetAdcOmOutInvert1A()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1158, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert1A(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1158, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvert1ALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1158;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_1_B
   unsigned int GetAdcOmOutInvert1B()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x115C, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert1B(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x115C, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvert1BLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x115C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_1_C
   unsigned int GetAdcOmOutInvert1C()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1160, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert1C(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1160, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvert1CLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1160;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_1_D
   unsigned int GetAdcOmOutInvert1D()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1164, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert1D(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1164, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvert1DLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1164;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_1_DCO
   unsigned int GetAdcOmOutInvert1Dco()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1178, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert1Dco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1178, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvert1DcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1178;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_1_E
   unsigned int GetAdcOmOutInvert1E()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1168, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert1E(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1168, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvert1ELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1168;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_1_F
   unsigned int GetAdcOmOutInvert1F()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x116C, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert1F(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x116C, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvert1FLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x116C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_1_FCO
   unsigned int GetAdcOmOutInvert1Fco()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x117C, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert1Fco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x117C, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvert1FcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x117C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_1_G
   unsigned int GetAdcOmOutInvert1G()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1170, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert1G(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1170, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvert1GLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1170;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OM_OUT_INVERT_1_H
   unsigned int GetAdcOmOutInvert1H()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1174, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOmOutInvert1H(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1174, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOmOutInvert1HLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1174;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OP_IN_CLK_PH_ADJ
   unsigned int GetAdcOpInClkPhAdj()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1120, 0x00007000, 12);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOpInClkPhAdj(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1120, 0x00007000, 12, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOpInClkPhAdjLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00007000;
            if(BitOfs) *BitOfs = 12;
            return 0x1120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_OP_OUT_CLK_PH_ADJ
   unsigned int GetAdcOpOutClkPhAdj()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1120, 0x00000F00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcOpOutClkPhAdj(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1120, 0x00000F00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcOpOutClkPhAdjLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000F00;
            if(BitOfs) *BitOfs = 8;
            return 0x1120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_PM_EXT_PD
   unsigned int GetAdcPmExtPd()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1118, 0x20000000, 29);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcPmExtPd(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1118, 0x20000000, 29, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcPmExtPdLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x20000000;
            if(BitOfs) *BitOfs = 29;
            return 0x1118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_PM_INT_PD_MODE
   unsigned int GetAdcPmIntPdMode()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1118, 0x03000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcPmIntPdMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1118, 0x03000000, 24, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcPmIntPdModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x03000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_RESOLUTION
   unsigned int GetAdcResolution()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1128, 0x00000030, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcResolution(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1128, 0x00000030, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcResolutionLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000030;
            if(BitOfs) *BitOfs = 4;
            return 0x1128;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_RES_SR_OVR
   unsigned int GetAdcResSrOvr()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1128, 0x00000040, 6);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcResSrOvr(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1128, 0x00000040, 6, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcResSrOvrLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x1128;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_RST
   unsigned int GetAdcRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1040, 0x00000040, 6);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1040, 0x00000040, 6, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x1040;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_RST_MOD
   unsigned int GetAdcRstMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0138, 0x00000008, 3);
         case 9:
            return BitExtractStatus(0x0134, 0x00000008, 3);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcRstModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000008;
            if(BitOfs) *BitOfs = 3;
            return 0x0138;
         case 9:
            if(BitMask) *BitMask = 0x00000008;
            if(BitOfs) *BitOfs = 3;
            return 0x0134;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_SAMPLE_DIV
   unsigned int GetAdcSampleDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1038, 0x000000FF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcSampleDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1038, 0x000000FF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcSampleDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x1038;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_SAMPLE_DIV_MOD
   unsigned int GetAdcSampleDivMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0144, 0x0000000F, 0);
         case 9:
            return BitExtractStatus(0x0140, 0x0000000F, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcSampleDivModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0144;
         case 9:
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0140;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_SAMPLE_FREQ
   unsigned int GetAdcSampleFreq()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x003C, 0x00FFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcSampleFreqLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00FFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x003C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_SAMPLE_RATE
   unsigned int GetAdcSampleRate()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1128, 0x00000007, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcSampleRate(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1128, 0x00000007, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcSampleRateLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000007;
            if(BitOfs) *BitOfs = 0;
            return 0x1128;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_SC_LVDS_OUT_LSB_FIRST
   unsigned int GetAdcScLvdsOutLsbFirst()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1128, 0x00800000, 23);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcScLvdsOutLsbFirst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1128, 0x00800000, 23, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcScLvdsOutLsbFirstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00800000;
            if(BitOfs) *BitOfs = 23;
            return 0x1128;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_SC_OUT_NR_BITS
   unsigned int GetAdcScOutNrBits()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1128, 0x00030000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcScOutNrBits(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1128, 0x00030000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcScOutNrBitsLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x1128;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_SC_OUT_RST
   unsigned int GetAdcScOutRst()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1128, 0x00000200, 9);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcScOutRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1128, 0x00000200, 9, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcScOutRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000200;
            if(BitOfs) *BitOfs = 9;
            return 0x1128;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_SC_PWR_DN
   unsigned int GetAdcScPwrDn()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1128, 0x00000100, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcScPwrDn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1128, 0x00000100, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcScPwrDnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1128;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_SC_WORD_WISE_DDR
   unsigned int GetAdcScWordWiseDdr()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1128, 0x00700000, 20);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcScWordWiseDdr(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1128, 0x00700000, 20, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcScWordWiseDdrLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00700000;
            if(BitOfs) *BitOfs = 20;
            return 0x1128;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_SYNC_NEXT_ONLY
   unsigned int GetAdcSyncNextOnly()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x112C, 0x00000002, 1);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcSyncNextOnly(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x112C, 0x00000002, 1, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcSyncNextOnlyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x112C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT
   unsigned int GetAdcTmOut()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x111C, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x111C, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOutLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT_0_A
   unsigned int GetAdcTmOut0A()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1130, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut0A(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1130, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOut0ALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1130;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT_0_B
   unsigned int GetAdcTmOut0B()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1134, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut0B(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1134, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOut0BLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1134;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT_0_C
   unsigned int GetAdcTmOut0C()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1138, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut0C(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1138, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOut0CLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1138;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT_0_D
   unsigned int GetAdcTmOut0D()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x113C, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut0D(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x113C, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOut0DLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x113C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT_0_DCO
   unsigned int GetAdcTmOut0Dco()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1150, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut0Dco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1150, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOut0DcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1150;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT_0_E
   unsigned int GetAdcTmOut0E()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1140, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut0E(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1140, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOut0ELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1140;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT_0_F
   unsigned int GetAdcTmOut0F()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1144, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut0F(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1144, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOut0FLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1144;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT_0_FCO
   unsigned int GetAdcTmOut0Fco()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1154, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut0Fco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1154, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOut0FcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1154;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT_0_G
   unsigned int GetAdcTmOut0G()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1148, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut0G(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1148, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOut0GLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1148;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT_0_H
   unsigned int GetAdcTmOut0H()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x114C, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut0H(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x114C, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOut0HLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x114C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT_1_A
   unsigned int GetAdcTmOut1A()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1158, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut1A(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1158, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOut1ALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1158;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT_1_B
   unsigned int GetAdcTmOut1B()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x115C, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut1B(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x115C, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOut1BLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x115C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT_1_C
   unsigned int GetAdcTmOut1C()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1160, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut1C(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1160, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOut1CLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1160;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT_1_D
   unsigned int GetAdcTmOut1D()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1164, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut1D(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1164, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOut1DLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1164;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT_1_DCO
   unsigned int GetAdcTmOut1Dco()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1178, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut1Dco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1178, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOut1DcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1178;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT_1_E
   unsigned int GetAdcTmOut1E()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1168, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut1E(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1168, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOut1ELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1168;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT_1_F
   unsigned int GetAdcTmOut1F()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x116C, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut1F(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x116C, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOut1FLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x116C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT_1_FCO
   unsigned int GetAdcTmOut1Fco()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x117C, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut1Fco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x117C, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOut1FcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x117C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT_1_G
   unsigned int GetAdcTmOut1G()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1170, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut1G(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1170, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOut1GLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1170;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_OUT_1_H
   unsigned int GetAdcTmOut1H()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1174, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmOut1H(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1174, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmOut1HLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1174;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_RST_PN_LONG_GEN
   unsigned int GetAdcTmRstPnLongGen()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x111C, 0x00200000, 21);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmRstPnLongGen(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x111C, 0x00200000, 21, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmRstPnLongGenLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00200000;
            if(BitOfs) *BitOfs = 21;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_RST_PN_SHORT_GEN
   unsigned int GetAdcTmRstPnShortGen()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x111C, 0x00100000, 20);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmRstPnShortGen(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x111C, 0x00100000, 20, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmRstPnShortGenLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE
   unsigned int GetAdcTmUsrInMode()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x111C, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x111C, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x111C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_0_A
   unsigned int GetAdcTmUsrInMode0A()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1130, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode0A(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1130, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInMode0ALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1130;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_0_B
   unsigned int GetAdcTmUsrInMode0B()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1134, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode0B(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1134, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInMode0BLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1134;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_0_C
   unsigned int GetAdcTmUsrInMode0C()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1138, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode0C(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1138, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInMode0CLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1138;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_0_D
   unsigned int GetAdcTmUsrInMode0D()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x113C, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode0D(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x113C, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInMode0DLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x113C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_0_DCO
   unsigned int GetAdcTmUsrInMode0Dco()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1150, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode0Dco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1150, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInMode0DcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1150;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_0_E
   unsigned int GetAdcTmUsrInMode0E()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1140, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode0E(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1140, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInMode0ELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1140;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_0_F
   unsigned int GetAdcTmUsrInMode0F()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1144, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode0F(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1144, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInMode0FLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1144;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_0_FCO
   unsigned int GetAdcTmUsrInMode0Fco()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1154, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode0Fco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1154, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInMode0FcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1154;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_0_G
   unsigned int GetAdcTmUsrInMode0G()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1148, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode0G(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1148, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInMode0GLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1148;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_0_H
   unsigned int GetAdcTmUsrInMode0H()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x114C, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode0H(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x114C, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInMode0HLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x114C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_1_A
   unsigned int GetAdcTmUsrInMode1A()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1158, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode1A(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1158, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInMode1ALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1158;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_1_B
   unsigned int GetAdcTmUsrInMode1B()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x115C, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode1B(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x115C, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInMode1BLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x115C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_1_C
   unsigned int GetAdcTmUsrInMode1C()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1160, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode1C(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1160, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInMode1CLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1160;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_1_D
   unsigned int GetAdcTmUsrInMode1D()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1164, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode1D(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1164, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInMode1DLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1164;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_1_DCO
   unsigned int GetAdcTmUsrInMode1Dco()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1178, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode1Dco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1178, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInMode1DcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1178;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_1_E
   unsigned int GetAdcTmUsrInMode1E()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1168, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode1E(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1168, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInMode1ELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1168;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_1_F
   unsigned int GetAdcTmUsrInMode1F()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x116C, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode1F(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x116C, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInMode1FLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x116C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_1_FCO
   unsigned int GetAdcTmUsrInMode1Fco()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x117C, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode1Fco(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x117C, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInMode1FcoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x117C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_1_G
   unsigned int GetAdcTmUsrInMode1G()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1170, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode1G(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1170, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInMode1GLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1170;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TM_USR_IN_MODE_1_H
   unsigned int GetAdcTmUsrInMode1H()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1174, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTmUsrInMode1H(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1174, 0x00C00000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTmUsrInMode1HLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x1174;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TX_INIT_OVERRIDE
   unsigned int GetAdcTxInitOverride()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1114, 0x00000001, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTxInitOverride(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1114, 0x00000001, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTxInitOverrideLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x1114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_TX_SAMPLES
   unsigned int GetAdcTxSamples()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x102C, 0x00000FFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcTxSamples(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x102C, 0x00000FFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcTxSamplesLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000FFF;
            if(BitOfs) *BitOfs = 0;
            return 0x102C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_UIOC2_SDIO_PD
   unsigned int GetAdcUioc2SdioPd()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x112C, 0x00010000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcUioc2SdioPd(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x112C, 0x00010000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcUioc2SdioPdLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x112C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_UIOC3_VCM_PWR_DN
   unsigned int GetAdcUioc3VcmPwrDn()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x112C, 0x00000800, 11);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcUioc3VcmPwrDn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x112C, 0x00000800, 11, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcUioc3VcmPwrDnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000800;
            if(BitOfs) *BitOfs = 11;
            return 0x112C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_USR_PATT1
   unsigned int GetAdcUsrPatt1()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1124, 0xFFFF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcUsrPatt1(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1124, 0xFFFF0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcUsrPatt1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1124;
         default:
            throw 20;
      };
   };

   // Bit(s) ADC_USR_PATT2
   unsigned int GetAdcUsrPatt2()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1124, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdcUsrPatt2(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1124, 0x0000FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdcUsrPatt2Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1124;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_CFG_12
   unsigned int GetAdvTrgCfg12()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1258, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x11FC, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdvTrgCfg12(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1258, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x11FC, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgCfg12Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1258;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11FC;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_CFG_13
   unsigned int GetAdvTrgCfg13()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x125C, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x1200, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdvTrgCfg13(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x125C, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x1200, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgCfg13Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x125C;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1200;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_CFG_14
   unsigned int GetAdvTrgCfg14()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1260, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x1204, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdvTrgCfg14(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1260, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x1204, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgCfg14Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1260;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1204;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_CFG_15
   unsigned int GetAdvTrgCfg15()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1264, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x1208, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdvTrgCfg15(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1264, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x1208, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgCfg15Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1264;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1208;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_CFG_16
   unsigned int GetAdvTrgCfg16()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1268, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x120C, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdvTrgCfg16(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1268, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x120C, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgCfg16Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1268;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x120C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_CFG_17
   unsigned int GetAdvTrgCfg17()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x126C, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x1210, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdvTrgCfg17(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x126C, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x1210, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgCfg17Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x126C;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1210;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_CFG_18
   unsigned int GetAdvTrgCfg18()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1270, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x1214, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdvTrgCfg18(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1270, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x1214, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgCfg18Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1270;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1214;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_CFG_19
   unsigned int GetAdvTrgCfg19()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1274, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x1218, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdvTrgCfg19(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1274, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x1218, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgCfg19Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1274;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1218;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_CH_CAL0
   unsigned int GetAdvTrgChCal0()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x122C, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x11D0, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdvTrgChCal0(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x122C, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x11D0, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgChCal0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x122C;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11D0;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_CH_CAL1
   unsigned int GetAdvTrgChCal1()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1230, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x11D4, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdvTrgChCal1(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1230, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x11D4, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgChCal1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1230;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11D4;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_CH_CAL2
   unsigned int GetAdvTrgChCal2()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1234, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x11D8, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdvTrgChCal2(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1234, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x11D8, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgChCal2Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1234;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11D8;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_CH_CAL3
   unsigned int GetAdvTrgChCal3()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1238, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x11DC, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdvTrgChCal3(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1238, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x11DC, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgChCal3Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1238;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11DC;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_CTRL
   unsigned int GetAdvTrgCtrl()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1228, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x11CC, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdvTrgCtrl(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1228, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x11CC, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgCtrlLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1228;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11CC;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_PED_CFG
   unsigned int GetAdvTrgPedCfg()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x123C, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x11E0, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdvTrgPedCfg(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x123C, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x11E0, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgPedCfgLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x123C;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11E0;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_STAT_1
   unsigned int GetAdvTrgStat1()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0118, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0114, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgStat1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0118;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0114;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_STAT_2
   unsigned int GetAdvTrgStat2()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x011C, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0118, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgStat2Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x011C;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0118;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_STAT_3
   unsigned int GetAdvTrgStat3()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0120, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x011C, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgStat3Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0120;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x011C;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_STAT_4
   unsigned int GetAdvTrgStat4()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0124, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0120, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgStat4Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0124;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0120;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_TDC_CH_MASK
   unsigned int GetAdvTrgTdcChMask()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1254, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x11F8, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdvTrgTdcChMask(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1254, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x11F8, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgTdcChMaskLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1254;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11F8;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_THR0
   unsigned int GetAdvTrgThr0()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1240, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x11E4, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdvTrgThr0(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1240, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x11E4, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgThr0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1240;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11E4;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_THR1
   unsigned int GetAdvTrgThr1()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1244, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x11E8, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdvTrgThr1(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1244, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x11E8, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgThr1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1244;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11E8;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_THR2
   unsigned int GetAdvTrgThr2()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1248, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x11EC, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdvTrgThr2(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1248, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x11EC, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgThr2Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1248;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11EC;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_TRIG_CELL
   unsigned int GetAdvTrgTrigCell()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0114, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0110, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgTrigCellLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0114;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0110;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_TX_CHK_WORD0
   unsigned int GetAdvTrgTxChkWord0()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x124C, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x11F0, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdvTrgTxChkWord0(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x124C, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x11F0, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgTxChkWord0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x124C;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11F0;
         default:
            throw 20;
      };
   };

   // Bit(s) ADV_TRG_TX_CHK_WORD1
   unsigned int GetAdvTrgTxChkWord1()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1250, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x11F4, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAdvTrgTxChkWord1(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1250, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x11F4, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAdvTrgTxChkWord1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1250;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11F4;
         default:
            throw 20;
      };
   };

   // Bit(s) APPLY_SETTINGS_ADC
   unsigned int GetApplySettingsAdc()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1044, 0x00000002, 1);
         default:
            throw 20;
      };
   };
   unsigned int SetApplySettingsAdc(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1044, 0x00000002, 1, value);
         default:
            throw 20;
      };
   };
   unsigned int GetApplySettingsAdcLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x1044;
         default:
            throw 20;
      };
   };

   // Bit(s) APPLY_SETTINGS_ADC_SAMPLE_DIV
   unsigned int GetApplySettingsAdcSampleDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1044, 0x00000100, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetApplySettingsAdcSampleDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1044, 0x00000100, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetApplySettingsAdcSampleDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1044;
         default:
            throw 20;
      };
   };

   // Bit(s) APPLY_SETTINGS_CTRL
   unsigned int GetApplySettingsCtrl()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1044, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetApplySettingsCtrl(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1044, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetApplySettingsCtrlLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1044;
         default:
            throw 20;
      };
   };

   // Bit(s) APPLY_SETTINGS_DAC
   unsigned int GetApplySettingsDac()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1044, 0x00000010, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetApplySettingsDac(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1044, 0x00000010, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetApplySettingsDacLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x1044;
         default:
            throw 20;
      };
   };

   // Bit(s) APPLY_SETTINGS_DRS
   unsigned int GetApplySettingsDrs()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1044, 0x00000020, 5);
         default:
            throw 20;
      };
   };
   unsigned int SetApplySettingsDrs(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1044, 0x00000020, 5, value);
         default:
            throw 20;
      };
   };
   unsigned int GetApplySettingsDrsLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x1044;
         default:
            throw 20;
      };
   };

   // Bit(s) APPLY_SETTINGS_FRONTEND
   unsigned int GetApplySettingsFrontend()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1044, 0x00000008, 3);
         default:
            throw 20;
      };
   };
   unsigned int SetApplySettingsFrontend(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1044, 0x00000008, 3, value);
         default:
            throw 20;
      };
   };
   unsigned int GetApplySettingsFrontendLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000008;
            if(BitOfs) *BitOfs = 3;
            return 0x1044;
         default:
            throw 20;
      };
   };

   // Bit(s) APPLY_SETTINGS_HV
   unsigned int GetApplySettingsHv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1044, 0x00000040, 6);
         default:
            throw 20;
      };
   };
   unsigned int SetApplySettingsHv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1044, 0x00000040, 6, value);
         default:
            throw 20;
      };
   };
   unsigned int GetApplySettingsHvLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x1044;
         default:
            throw 20;
      };
   };

   // Bit(s) APPLY_SETTINGS_LMK
   unsigned int GetApplySettingsLmk()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1044, 0x00000001, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetApplySettingsLmk(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1044, 0x00000001, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetApplySettingsLmkLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x1044;
         default:
            throw 20;
      };
   };

   // Bit(s) APPLY_SETTINGS_MAX_PLD_SIZE
   unsigned int GetApplySettingsMaxPldSize()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1044, 0x00000080, 7);
         default:
            throw 20;
      };
   };
   unsigned int SetApplySettingsMaxPldSize(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1044, 0x00000080, 7, value);
         default:
            throw 20;
      };
   };
   unsigned int GetApplySettingsMaxPldSizeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x1044;
         default:
            throw 20;
      };
   };

   // Bit(s) AUTO_TRIGGER_PERIOD
   unsigned int GetAutoTriggerPeriod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1188, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x112C, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetAutoTriggerPeriod(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1188, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x112C, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetAutoTriggerPeriodLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1188;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x112C;
         default:
            throw 20;
      };
   };

   // Bit(s) BACKPLANE_PLUGGED
   unsigned int GetBackplanePlugged()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0028, 0x00000001, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetBackplanePluggedLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x0028;
         default:
            throw 20;
      };
   };

   // Bit(s) BOARD_MAGIC
   unsigned int GetBoardMagic()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0000, 0xFF000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int GetBoardMagicLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFF000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0000;
         default:
            throw 20;
      };
   };

   // Bit(s) BOARD_REVISION
   unsigned int GetBoardRevision()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0000, 0x000000FC, 2);
         default:
            throw 20;
      };
   };
   unsigned int GetBoardRevisionLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000FC;
            if(BitOfs) *BitOfs = 2;
            return 0x0000;
         default:
            throw 20;
      };
   };

   // Bit(s) BOARD_SEL
   unsigned int GetBoardSel()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0028, 0x00000100, 8);
         default:
            throw 20;
      };
   };
   unsigned int GetBoardSelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x0028;
         default:
            throw 20;
      };
   };

   // Bit(s) BOARD_TYPE
   unsigned int GetBoardType()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0000, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int GetBoardTypeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x0000;
         default:
            throw 20;
      };
   };

   // Bit(s) BOARD_VARIANT
   unsigned int GetBoardVariant()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0000, 0x00000003, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetBoardVariantLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x0000;
         default:
            throw 20;
      };
   };

   // Bit(s) CALIB_BUFFER_EN
   unsigned int GetCalibBufferEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1008, 0x00000002, 1);
         default:
            throw 20;
      };
   };
   unsigned int SetCalibBufferEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1008, 0x00000002, 1, value);
         default:
            throw 20;
      };
   };
   unsigned int GetCalibBufferEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x1008;
         default:
            throw 20;
      };
   };

   // Bit(s) CLK_SEL_AND_DRS_CLK_DIV_MOD
   unsigned int GetClkSelAndDrsClkDivMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0138, 0x00000004, 2);
         case 9:
            return BitExtractStatus(0x0134, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int GetClkSelAndDrsClkDivModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x0138;
         case 9:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x0134;
         default:
            throw 20;
      };
   };

   // Bit(s) COMP_CH_STAT
   unsigned int GetCompChStat()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00FC, 0x0000FFFF, 0);
         case 9:
            return BitExtractStatus(0x00F8, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetCompChStatLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00FC;
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00F8;
         default:
            throw 20;
      };
   };

   // Bit(s) COMP_POWER_EN
   unsigned int GetCompPowerEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1004, 0x00000200, 9);
         default:
            throw 20;
      };
   };
   unsigned int SetCompPowerEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1004, 0x00000200, 9, value);
         default:
            throw 20;
      };
   };
   unsigned int GetCompPowerEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000200;
            if(BitOfs) *BitOfs = 9;
            return 0x1004;
         default:
            throw 20;
      };
   };

   // Bit(s) COM_PLD_SIZE
   unsigned int GetComPldSize()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1018, 0x0003FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetComPldSize(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1018, 0x0003FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetComPldSizeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0003FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1018;
         default:
            throw 20;
      };
   };

   // Bit(s) COM_PLD_SIZE_MOD
   unsigned int GetComPldSizeMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0140, 0x0000000F, 0);
         case 9:
            return BitExtractStatus(0x013C, 0x0000000F, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetComPldSizeModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0140;
         case 9:
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x013C;
         default:
            throw 20;
      };
   };

   // Bit(s) CRATE_ID
   unsigned int GetCrateId()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1000, 0x00FF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetCrateId(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1000, 0x00FF0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetCrateIdLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00FF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1000;
         default:
            throw 20;
      };
   };

   // Bit(s) CRC32_REG_BANK
   unsigned int GetCrc32RegBank()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1284, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x1228, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetCrc32RegBank(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1284, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x1228, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetCrc32RegBankLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1284;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1228;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC0_A_MOD
   unsigned int GetDac0AMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0148, 0xC0000000, 30);
         case 9:
            return BitExtractStatus(0x0144, 0xC0000000, 30);
         default:
            throw 20;
      };
   };
   unsigned int GetDac0AModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xC0000000;
            if(BitOfs) *BitOfs = 30;
            return 0x0148;
         case 9:
            if(BitMask) *BitMask = 0xC0000000;
            if(BitOfs) *BitOfs = 30;
            return 0x0144;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC0_B_MOD
   unsigned int GetDac0BMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0148, 0x30000000, 28);
         case 9:
            return BitExtractStatus(0x0144, 0x30000000, 28);
         default:
            throw 20;
      };
   };
   unsigned int GetDac0BModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x30000000;
            if(BitOfs) *BitOfs = 28;
            return 0x0148;
         case 9:
            if(BitMask) *BitMask = 0x30000000;
            if(BitOfs) *BitOfs = 28;
            return 0x0144;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC0_CH_A
   unsigned int GetDac0ChA()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1048, 0xFFFF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetDac0ChA(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1048, 0xFFFF0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac0ChALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1048;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC0_CH_B
   unsigned int GetDac0ChB()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1048, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetDac0ChB(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1048, 0x0000FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac0ChBLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1048;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC0_CH_C
   unsigned int GetDac0ChC()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x104C, 0xFFFF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetDac0ChC(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x104C, 0xFFFF0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac0ChCLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x104C;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC0_CH_D
   unsigned int GetDac0ChD()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x104C, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetDac0ChD(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x104C, 0x0000FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac0ChDLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x104C;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC0_CH_E
   unsigned int GetDac0ChE()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1050, 0xFFFF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetDac0ChE(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1050, 0xFFFF0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac0ChELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1050;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC0_CH_F
   unsigned int GetDac0ChF()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1050, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetDac0ChF(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1050, 0x0000FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac0ChFLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1050;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC0_CH_G
   unsigned int GetDac0ChG()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1054, 0xFFFF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetDac0ChG(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1054, 0xFFFF0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac0ChGLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1054;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC0_CH_H
   unsigned int GetDac0ChH()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1054, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetDac0ChH(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1054, 0x0000FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac0ChHLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1054;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC0_C_MOD
   unsigned int GetDac0CMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0148, 0x0C000000, 26);
         case 9:
            return BitExtractStatus(0x0144, 0x0C000000, 26);
         default:
            throw 20;
      };
   };
   unsigned int GetDac0CModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0C000000;
            if(BitOfs) *BitOfs = 26;
            return 0x0148;
         case 9:
            if(BitMask) *BitMask = 0x0C000000;
            if(BitOfs) *BitOfs = 26;
            return 0x0144;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC0_D_MOD
   unsigned int GetDac0DMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0148, 0x03000000, 24);
         case 9:
            return BitExtractStatus(0x0144, 0x03000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int GetDac0DModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x03000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0148;
         case 9:
            if(BitMask) *BitMask = 0x03000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0144;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC0_E_MOD
   unsigned int GetDac0EMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0148, 0x00C00000, 22);
         case 9:
            return BitExtractStatus(0x0144, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int GetDac0EModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x0148;
         case 9:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x0144;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC0_F_MOD
   unsigned int GetDac0FMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0148, 0x00300000, 20);
         case 9:
            return BitExtractStatus(0x0144, 0x00300000, 20);
         default:
            throw 20;
      };
   };
   unsigned int GetDac0FModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00300000;
            if(BitOfs) *BitOfs = 20;
            return 0x0148;
         case 9:
            if(BitMask) *BitMask = 0x00300000;
            if(BitOfs) *BitOfs = 20;
            return 0x0144;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC0_G_MOD
   unsigned int GetDac0GMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0148, 0x000C0000, 18);
         case 9:
            return BitExtractStatus(0x0144, 0x000C0000, 18);
         default:
            throw 20;
      };
   };
   unsigned int GetDac0GModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x0148;
         case 9:
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x0144;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC0_H_MOD
   unsigned int GetDac0HMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0148, 0x00030000, 16);
         case 9:
            return BitExtractStatus(0x0144, 0x00030000, 16);
         default:
            throw 20;
      };
   };
   unsigned int GetDac0HModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x0148;
         case 9:
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x0144;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC1_A_MOD
   unsigned int GetDac1AMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0148, 0x0000C000, 14);
         case 9:
            return BitExtractStatus(0x0144, 0x0000C000, 14);
         default:
            throw 20;
      };
   };
   unsigned int GetDac1AModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000C000;
            if(BitOfs) *BitOfs = 14;
            return 0x0148;
         case 9:
            if(BitMask) *BitMask = 0x0000C000;
            if(BitOfs) *BitOfs = 14;
            return 0x0144;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC1_B_MOD
   unsigned int GetDac1BMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0148, 0x00003000, 12);
         case 9:
            return BitExtractStatus(0x0144, 0x00003000, 12);
         default:
            throw 20;
      };
   };
   unsigned int GetDac1BModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00003000;
            if(BitOfs) *BitOfs = 12;
            return 0x0148;
         case 9:
            if(BitMask) *BitMask = 0x00003000;
            if(BitOfs) *BitOfs = 12;
            return 0x0144;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC1_CH_A
   unsigned int GetDac1ChA()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1058, 0xFFFF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetDac1ChA(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1058, 0xFFFF0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac1ChALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1058;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC1_CH_B
   unsigned int GetDac1ChB()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1058, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetDac1ChB(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1058, 0x0000FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac1ChBLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1058;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC1_CH_C
   unsigned int GetDac1ChC()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x105C, 0xFFFF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetDac1ChC(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x105C, 0xFFFF0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac1ChCLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x105C;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC1_CH_D
   unsigned int GetDac1ChD()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x105C, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetDac1ChD(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x105C, 0x0000FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac1ChDLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x105C;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC1_CH_E
   unsigned int GetDac1ChE()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1060, 0xFFFF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetDac1ChE(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1060, 0xFFFF0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac1ChELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1060;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC1_CH_F
   unsigned int GetDac1ChF()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1060, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetDac1ChF(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1060, 0x0000FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac1ChFLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1060;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC1_CH_G
   unsigned int GetDac1ChG()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1064, 0xFFFF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetDac1ChG(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1064, 0xFFFF0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac1ChGLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1064;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC1_CH_H
   unsigned int GetDac1ChH()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1064, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetDac1ChH(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1064, 0x0000FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac1ChHLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1064;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC1_C_MOD
   unsigned int GetDac1CMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0148, 0x00000C00, 10);
         case 9:
            return BitExtractStatus(0x0144, 0x00000C00, 10);
         default:
            throw 20;
      };
   };
   unsigned int GetDac1CModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000C00;
            if(BitOfs) *BitOfs = 10;
            return 0x0148;
         case 9:
            if(BitMask) *BitMask = 0x00000C00;
            if(BitOfs) *BitOfs = 10;
            return 0x0144;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC1_D_MOD
   unsigned int GetDac1DMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0148, 0x00000300, 8);
         case 9:
            return BitExtractStatus(0x0144, 0x00000300, 8);
         default:
            throw 20;
      };
   };
   unsigned int GetDac1DModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000300;
            if(BitOfs) *BitOfs = 8;
            return 0x0148;
         case 9:
            if(BitMask) *BitMask = 0x00000300;
            if(BitOfs) *BitOfs = 8;
            return 0x0144;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC1_E_MOD
   unsigned int GetDac1EMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0148, 0x000000C0, 6);
         case 9:
            return BitExtractStatus(0x0144, 0x000000C0, 6);
         default:
            throw 20;
      };
   };
   unsigned int GetDac1EModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000000C0;
            if(BitOfs) *BitOfs = 6;
            return 0x0148;
         case 9:
            if(BitMask) *BitMask = 0x000000C0;
            if(BitOfs) *BitOfs = 6;
            return 0x0144;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC1_F_MOD
   unsigned int GetDac1FMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0148, 0x00000030, 4);
         case 9:
            return BitExtractStatus(0x0144, 0x00000030, 4);
         default:
            throw 20;
      };
   };
   unsigned int GetDac1FModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000030;
            if(BitOfs) *BitOfs = 4;
            return 0x0148;
         case 9:
            if(BitMask) *BitMask = 0x00000030;
            if(BitOfs) *BitOfs = 4;
            return 0x0144;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC1_G_MOD
   unsigned int GetDac1GMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0148, 0x0000000C, 2);
         case 9:
            return BitExtractStatus(0x0144, 0x0000000C, 2);
         default:
            throw 20;
      };
   };
   unsigned int GetDac1GModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x0148;
         case 9:
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x0144;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC1_H_MOD
   unsigned int GetDac1HMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0148, 0x00000003, 0);
         case 9:
            return BitExtractStatus(0x0144, 0x00000003, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetDac1HModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x0148;
         case 9:
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x0144;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC2_A_MOD
   unsigned int GetDac2AMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x014C, 0xC0000000, 30);
         case 9:
            return BitExtractStatus(0x0148, 0xC0000000, 30);
         default:
            throw 20;
      };
   };
   unsigned int GetDac2AModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xC0000000;
            if(BitOfs) *BitOfs = 30;
            return 0x014C;
         case 9:
            if(BitMask) *BitMask = 0xC0000000;
            if(BitOfs) *BitOfs = 30;
            return 0x0148;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC2_B_MOD
   unsigned int GetDac2BMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x014C, 0x30000000, 28);
         case 9:
            return BitExtractStatus(0x0148, 0x30000000, 28);
         default:
            throw 20;
      };
   };
   unsigned int GetDac2BModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x30000000;
            if(BitOfs) *BitOfs = 28;
            return 0x014C;
         case 9:
            if(BitMask) *BitMask = 0x30000000;
            if(BitOfs) *BitOfs = 28;
            return 0x0148;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC2_CH_A
   unsigned int GetDac2ChA()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1068, 0xFFFF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetDac2ChA(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1068, 0xFFFF0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac2ChALoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1068;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC2_CH_B
   unsigned int GetDac2ChB()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1068, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetDac2ChB(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1068, 0x0000FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac2ChBLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1068;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC2_CH_C
   unsigned int GetDac2ChC()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x106C, 0xFFFF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetDac2ChC(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x106C, 0xFFFF0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac2ChCLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x106C;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC2_CH_D
   unsigned int GetDac2ChD()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x106C, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetDac2ChD(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x106C, 0x0000FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac2ChDLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x106C;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC2_CH_E
   unsigned int GetDac2ChE()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1070, 0xFFFF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetDac2ChE(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1070, 0xFFFF0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac2ChELoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1070;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC2_CH_F
   unsigned int GetDac2ChF()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1070, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetDac2ChF(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1070, 0x0000FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac2ChFLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1070;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC2_CH_G
   unsigned int GetDac2ChG()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1074, 0xFFFF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetDac2ChG(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1074, 0xFFFF0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac2ChGLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1074;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC2_CH_H
   unsigned int GetDac2ChH()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1074, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetDac2ChH(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1074, 0x0000FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDac2ChHLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1074;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC2_C_MOD
   unsigned int GetDac2CMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x014C, 0x0C000000, 26);
         case 9:
            return BitExtractStatus(0x0148, 0x0C000000, 26);
         default:
            throw 20;
      };
   };
   unsigned int GetDac2CModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0C000000;
            if(BitOfs) *BitOfs = 26;
            return 0x014C;
         case 9:
            if(BitMask) *BitMask = 0x0C000000;
            if(BitOfs) *BitOfs = 26;
            return 0x0148;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC2_D_MOD
   unsigned int GetDac2DMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x014C, 0x03000000, 24);
         case 9:
            return BitExtractStatus(0x0148, 0x03000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int GetDac2DModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x03000000;
            if(BitOfs) *BitOfs = 24;
            return 0x014C;
         case 9:
            if(BitMask) *BitMask = 0x03000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0148;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC2_E_MOD
   unsigned int GetDac2EMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x014C, 0x00C00000, 22);
         case 9:
            return BitExtractStatus(0x0148, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int GetDac2EModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x014C;
         case 9:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x0148;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC2_F_MOD
   unsigned int GetDac2FMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x014C, 0x00300000, 20);
         case 9:
            return BitExtractStatus(0x0148, 0x00300000, 20);
         default:
            throw 20;
      };
   };
   unsigned int GetDac2FModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00300000;
            if(BitOfs) *BitOfs = 20;
            return 0x014C;
         case 9:
            if(BitMask) *BitMask = 0x00300000;
            if(BitOfs) *BitOfs = 20;
            return 0x0148;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC2_G_MOD
   unsigned int GetDac2GMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x014C, 0x000C0000, 18);
         case 9:
            return BitExtractStatus(0x0148, 0x000C0000, 18);
         default:
            throw 20;
      };
   };
   unsigned int GetDac2GModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x014C;
         case 9:
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x0148;
         default:
            throw 20;
      };
   };

   // Bit(s) DAC2_H_MOD
   unsigned int GetDac2HMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x014C, 0x00030000, 16);
         case 9:
            return BitExtractStatus(0x0148, 0x00030000, 16);
         default:
            throw 20;
      };
   };
   unsigned int GetDac2HModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x014C;
         case 9:
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x0148;
         default:
            throw 20;
      };
   };

   // Bit(s) DAQ_AUTO
   unsigned int GetDaqAuto()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1004, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetDaqAuto(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1004, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDaqAutoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1004;
         default:
            throw 20;
      };
   };

   // Bit(s) DAQ_CLK_DEF_PHASE_CHKD
   unsigned int GetDaqClkDefPhaseChkd()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0028, 0x00001000, 12);
         case 9:
            return BitExtractStatus(0x0028, 0x00000800, 11);
         default:
            throw 20;
      };
   };
   unsigned int GetDaqClkDefPhaseChkdLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00001000;
            if(BitOfs) *BitOfs = 12;
            return 0x0028;
         case 9:
            if(BitMask) *BitMask = 0x00000800;
            if(BitOfs) *BitOfs = 11;
            return 0x0028;
         default:
            throw 20;
      };
   };

   // Bit(s) DAQ_CLK_DEF_PHASE_OK
   unsigned int GetDaqClkDefPhaseOk()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0028, 0x00002000, 13);
         case 9:
            return BitExtractStatus(0x0028, 0x00001000, 12);
         default:
            throw 20;
      };
   };
   unsigned int GetDaqClkDefPhaseOkLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00002000;
            if(BitOfs) *BitOfs = 13;
            return 0x0028;
         case 9:
            if(BitMask) *BitMask = 0x00001000;
            if(BitOfs) *BitOfs = 12;
            return 0x0028;
         default:
            throw 20;
      };
   };

   // Bit(s) DAQ_CLK_SRC_SEL
   unsigned int GetDaqClkSrcSel()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x100C, 0x00020000, 17);
         default:
            throw 20;
      };
   };
   unsigned int SetDaqClkSrcSel(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x100C, 0x00020000, 17, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDaqClkSrcSelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00020000;
            if(BitOfs) *BitOfs = 17;
            return 0x100C;
         default:
            throw 20;
      };
   };

   // Bit(s) DAQ_DATA_PHASE
   unsigned int GetDaqDataPhase()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1004, 0x00FF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetDaqDataPhase(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1004, 0x00FF0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDaqDataPhaseLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00FF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1004;
         default:
            throw 20;
      };
   };

   // Bit(s) DAQ_NORMAL
   unsigned int GetDaqNormal()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1004, 0x00000002, 1);
         default:
            throw 20;
      };
   };
   unsigned int SetDaqNormal(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1004, 0x00000002, 1, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDaqNormalLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x1004;
         default:
            throw 20;
      };
   };

   // Bit(s) DAQ_PLL_LOCK
   unsigned int GetDaqPllLock()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x002C, 0x00000080, 7);
         default:
            throw 20;
      };
   };
   unsigned int GetDaqPllLockLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x002C;
         default:
            throw 20;
      };
   };

   // Bit(s) DAQ_PLL_RST
   unsigned int GetDaqPllRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1040, 0x00004000, 14);
         default:
            throw 20;
      };
   };
   unsigned int SetDaqPllRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1040, 0x00004000, 14, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDaqPllRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00004000;
            if(BitOfs) *BitOfs = 14;
            return 0x1040;
         default:
            throw 20;
      };
   };

   // Bit(s) DAQ_SINGLE
   unsigned int GetDaqSingle()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1004, 0x00000001, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetDaqSingle(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1004, 0x00000001, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDaqSingleLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x1004;
         default:
            throw 20;
      };
   };

   // Bit(s) DAQ_SOFT_TRIGGER
   unsigned int GetDaqSoftTrigger()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1004, 0x00000020, 5);
         default:
            throw 20;
      };
   };
   unsigned int SetDaqSoftTrigger(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1004, 0x00000020, 5, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDaqSoftTriggerLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x1004;
         default:
            throw 20;
      };
   };

   // Bit(s) DATA_LINK_IF_RST
   unsigned int GetDataLinkIfRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1040, 0x00000010, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetDataLinkIfRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1040, 0x00000010, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDataLinkIfRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x1040;
         default:
            throw 20;
      };
   };

   // Bit(s) DCB_OSERDES_IF_RST
   unsigned int GetDcbOserdesIfRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1040, 0x00000800, 11);
         default:
            throw 20;
      };
   };
   unsigned int SetDcbOserdesIfRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1040, 0x00000800, 11, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDcbOserdesIfRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000800;
            if(BitOfs) *BitOfs = 11;
            return 0x1040;
         default:
            throw 20;
      };
   };

   // Bit(s) DCB_OSERDES_PLL_RST
   unsigned int GetDcbOserdesPllRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1040, 0x00002000, 13);
         default:
            throw 20;
      };
   };
   unsigned int SetDcbOserdesPllRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1040, 0x00002000, 13, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDcbOserdesPllRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00002000;
            if(BitOfs) *BitOfs = 13;
            return 0x1040;
         default:
            throw 20;
      };
   };

   // Bit(s) DCB_SERDES_TRAIN
   unsigned int GetDcbSerdesTrain()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1014, 0x80000000, 31);
         default:
            throw 20;
      };
   };
   unsigned int SetDcbSerdesTrain(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1014, 0x80000000, 31, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDcbSerdesTrainLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x80000000;
            if(BitOfs) *BitOfs = 31;
            return 0x1014;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_0_TIMING_REF_SEL
   unsigned int GetDrs0TimingRefSel()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1008, 0x00000008, 3);
         default:
            throw 20;
      };
   };
   unsigned int SetDrs0TimingRefSel(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1008, 0x00000008, 3, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDrs0TimingRefSelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000008;
            if(BitOfs) *BitOfs = 3;
            return 0x1008;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_1_TIMING_REF_SEL
   unsigned int GetDrs1TimingRefSel()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1008, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetDrs1TimingRefSel(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1008, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDrs1TimingRefSelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1008;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_CH_TX_EN
   unsigned int GetDrsChTxEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x101C, 0x0003FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetDrsChTxEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x101C, 0x0003FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsChTxEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0003FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x101C;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_CLR_RSR_AFTER_RO
   unsigned int GetDrsClrRsrAfterRo()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1004, 0x00000400, 10);
         default:
            throw 20;
      };
   };
   unsigned int SetDrsClrRsrAfterRo(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1004, 0x00000400, 10, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsClrRsrAfterRoLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000400;
            if(BitOfs) *BitOfs = 10;
            return 0x1004;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_CONFIGURE
   unsigned int GetDrsConfigure()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1004, 0x00000040, 6);
         default:
            throw 20;
      };
   };
   unsigned int SetDrsConfigure(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1004, 0x00000040, 6, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsConfigureLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x1004;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_CONFIG_DONE
   unsigned int GetDrsConfigDone()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0028, 0x00000400, 10);
         case 9:
            return BitExtractStatus(0x0028, 0x00000200, 9);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsConfigDoneLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000400;
            if(BitOfs) *BitOfs = 10;
            return 0x0028;
         case 9:
            if(BitMask) *BitMask = 0x00000200;
            if(BitOfs) *BitOfs = 9;
            return 0x0028;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_CTRL_BUSY
   unsigned int GetDrsCtrlBusy()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0028, 0x00000020, 5);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsCtrlBusyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x0028;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_CTRL_FSM_RST
   unsigned int GetDrsCtrlFsmRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1040, 0x00000002, 1);
         default:
            throw 20;
      };
   };
   unsigned int SetDrsCtrlFsmRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1040, 0x00000002, 1, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsCtrlFsmRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x1040;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_CTRL_MOD
   unsigned int GetDrsCtrlMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x013C, 0x00000004, 2);
         case 9:
            return BitExtractStatus(0x0138, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsCtrlModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x013C;
         case 9:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x0138;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_DMODE
   unsigned int GetDrsDmode()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1010, 0x00010000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetDrsDmode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1010, 0x00010000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsDmodeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x1010;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_PLLEN
   unsigned int GetDrsPllen()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1010, 0x00020000, 17);
         default:
            throw 20;
      };
   };
   unsigned int SetDrsPllen(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1010, 0x00020000, 17, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsPllenLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00020000;
            if(BitOfs) *BitOfs = 17;
            return 0x1010;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_PLL_LOCK_0
   unsigned int GetDrsPllLock0()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x002C, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsPllLock0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x002C;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_PLL_LOCK_1
   unsigned int GetDrsPllLock1()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x002C, 0x00000002, 1);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsPllLock1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x002C;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_READOUT_MODE
   unsigned int GetDrsReadoutMode()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1004, 0x00000100, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetDrsReadoutMode(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1004, 0x00000100, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsReadoutModeLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1004;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_SAMPLE_FREQ
   unsigned int GetDrsSampleFreq()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0038, 0x00FFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsSampleFreqLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00FFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0038;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_STOP_CELL_0
   unsigned int GetDrsStopCell0()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0030, 0x03FF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsStopCell0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x03FF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0030;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_STOP_CELL_1
   unsigned int GetDrsStopCell1()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0030, 0x000003FF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsStopCell1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000003FF;
            if(BitOfs) *BitOfs = 0;
            return 0x0030;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_STOP_WSR_0
   unsigned int GetDrsStopWsr0()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0034, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsStopWsr0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x0034;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_STOP_WSR_1
   unsigned int GetDrsStopWsr1()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0034, 0x000000FF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsStopWsr1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x0034;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_TX_SAMPLES
   unsigned int GetDrsTxSamples()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1028, 0x000007FF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetDrsTxSamples(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1028, 0x000007FF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsTxSamplesLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000007FF;
            if(BitOfs) *BitOfs = 0;
            return 0x1028;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_WAVE_CONTINUOUS
   unsigned int GetDrsWaveContinuous()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1004, 0x00000080, 7);
         default:
            throw 20;
      };
   };
   unsigned int SetDrsWaveContinuous(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1004, 0x00000080, 7, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsWaveContinuousLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x1004;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_WCR
   unsigned int GetDrsWcr()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1010, 0x000000FF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetDrsWcr(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1010, 0x000000FF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsWcrLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x1010;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_WCR_MOD
   unsigned int GetDrsWcrMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x013C, 0x00000001, 0);
         case 9:
            return BitExtractStatus(0x0138, 0x00000001, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsWcrModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x013C;
         case 9:
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x0138;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_WSR
   unsigned int GetDrsWsr()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1010, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetDrsWsr(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1010, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsWsrLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1010;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_WSRLOOP
   unsigned int GetDrsWsrloop()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1010, 0x00040000, 18);
         default:
            throw 20;
      };
   };
   unsigned int SetDrsWsrloop(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1010, 0x00040000, 18, value);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsWsrloopLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00040000;
            if(BitOfs) *BitOfs = 18;
            return 0x1010;
         default:
            throw 20;
      };
   };

   // Bit(s) DRS_WSR_MOD
   unsigned int GetDrsWsrMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x013C, 0x00000002, 1);
         case 9:
            return BitExtractStatus(0x0138, 0x00000002, 1);
         default:
            throw 20;
      };
   };
   unsigned int GetDrsWsrModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x013C;
         case 9:
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x0138;
         default:
            throw 20;
      };
   };

   // Bit(s) ETH_COM_EN
   unsigned int GetEthComEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1014, 0x01000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int SetEthComEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1014, 0x01000000, 24, value);
         default:
            throw 20;
      };
   };
   unsigned int GetEthComEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1014;
         default:
            throw 20;
      };
   };

   // Bit(s) EVENT_COUNTER_RST
   unsigned int GetEventCounterRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1040, 0x00000004, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetEventCounterRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1040, 0x00000004, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetEventCounterRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000004;
            if(BitOfs) *BitOfs = 2;
            return 0x1040;
         default:
            throw 20;
      };
   };

   // Bit(s) EVENT_NUMBER
   unsigned int GetEventNumber()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0104, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0100, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetEventNumberLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0104;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0100;
         default:
            throw 20;
      };
   };

   // Bit(s) EVENT_TX_RATE
   unsigned int GetEventTxRate()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0100, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00FC, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetEventTxRateLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0100;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00FC;
         default:
            throw 20;
      };
   };

   // Bit(s) EXT_ASYNC_TRIGGER_EN
   unsigned int GetExtAsyncTriggerEn()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1180, 0x00002000, 13);
         case 9:
            return BitExtractControl(0x1124, 0x00002000, 13);
         default:
            throw 20;
      };
   };
   unsigned int SetExtAsyncTriggerEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1180, 0x00002000, 13, value);
         case 9:
            return SetRegMask(0x1124, 0x00002000, 13, value);
         default:
            throw 20;
      };
   };
   unsigned int GetExtAsyncTriggerEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00002000;
            if(BitOfs) *BitOfs = 13;
            return 0x1180;
         case 9:
            if(BitMask) *BitMask = 0x00002000;
            if(BitOfs) *BitOfs = 13;
            return 0x1124;
         default:
            throw 20;
      };
   };

   // Bit(s) EXT_CLK_FREQ
   unsigned int GetExtClkFreq()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x100C, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetExtClkFreq(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x100C, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetExtClkFreqLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x100C;
         default:
            throw 20;
      };
   };

   // Bit(s) EXT_CLK_FREQ_MOD
   unsigned int GetExtClkFreqMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0138, 0x00000002, 1);
         case 9:
            return BitExtractStatus(0x0134, 0x00000002, 1);
         default:
            throw 20;
      };
   };
   unsigned int GetExtClkFreqModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x0138;
         case 9:
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x0134;
         default:
            throw 20;
      };
   };

   // Bit(s) EXT_CLK_IN_SEL
   unsigned int GetExtClkInSel()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x100C, 0x00010000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetExtClkInSel(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x100C, 0x00010000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetExtClkInSelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x100C;
         default:
            throw 20;
      };
   };

   // Bit(s) EXT_TRIGGER_OUT_ENABLE
   unsigned int GetExtTriggerOutEnable()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1180, 0x00008000, 15);
         case 9:
            return BitExtractControl(0x1124, 0x00008000, 15);
         default:
            throw 20;
      };
   };
   unsigned int SetExtTriggerOutEnable(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1180, 0x00008000, 15, value);
         case 9:
            return SetRegMask(0x1124, 0x00008000, 15, value);
         default:
            throw 20;
      };
   };
   unsigned int GetExtTriggerOutEnableLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00008000;
            if(BitOfs) *BitOfs = 15;
            return 0x1180;
         case 9:
            if(BitMask) *BitMask = 0x00008000;
            if(BitOfs) *BitOfs = 15;
            return 0x1124;
         default:
            throw 20;
      };
   };

   // Bit(s) FE0_AMPLIFIER1_COMP_EN
   unsigned int GetFe0Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1078, 0x00200000, 21);
         default:
            throw 20;
      };
   };
   unsigned int SetFe0Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1078, 0x00200000, 21, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe0Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00200000;
            if(BitOfs) *BitOfs = 21;
            return 0x1078;
         default:
            throw 20;
      };
   };

   // Bit(s) FE0_AMPLIFIER1_EN
   unsigned int GetFe0Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1078, 0x00100000, 20);
         default:
            throw 20;
      };
   };
   unsigned int SetFe0Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1078, 0x00100000, 20, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe0Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x1078;
         default:
            throw 20;
      };
   };

   // Bit(s) FE0_AMPLIFIER2_COMP_EN
   unsigned int GetFe0Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1078, 0x00800000, 23);
         default:
            throw 20;
      };
   };
   unsigned int SetFe0Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1078, 0x00800000, 23, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe0Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00800000;
            if(BitOfs) *BitOfs = 23;
            return 0x1078;
         default:
            throw 20;
      };
   };

   // Bit(s) FE0_AMPLIFIER2_EN
   unsigned int GetFe0Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1078, 0x00400000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetFe0Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1078, 0x00400000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe0Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00400000;
            if(BitOfs) *BitOfs = 22;
            return 0x1078;
         default:
            throw 20;
      };
   };

   // Bit(s) FE0_ATTENUATION
   unsigned int GetFe0Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1078, 0x000C0000, 18);
         default:
            throw 20;
      };
   };
   unsigned int SetFe0Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1078, 0x000C0000, 18, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe0AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x1078;
         default:
            throw 20;
      };
   };

   // Bit(s) FE0_MUX
   unsigned int GetFe0Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1078, 0x00030000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetFe0Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1078, 0x00030000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe0MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x1078;
         default:
            throw 20;
      };
   };

   // Bit(s) FE0_PZC_EN
   unsigned int GetFe0PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1078, 0x01000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int SetFe0PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1078, 0x01000000, 24, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe0PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1078;
         default:
            throw 20;
      };
   };

   // Bit(s) FE10_AMPLIFIER1_COMP_EN
   unsigned int GetFe10Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x108C, 0x00200000, 21);
         default:
            throw 20;
      };
   };
   unsigned int SetFe10Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x108C, 0x00200000, 21, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe10Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00200000;
            if(BitOfs) *BitOfs = 21;
            return 0x108C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE10_AMPLIFIER1_EN
   unsigned int GetFe10Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x108C, 0x00100000, 20);
         default:
            throw 20;
      };
   };
   unsigned int SetFe10Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x108C, 0x00100000, 20, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe10Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x108C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE10_AMPLIFIER2_COMP_EN
   unsigned int GetFe10Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x108C, 0x00800000, 23);
         default:
            throw 20;
      };
   };
   unsigned int SetFe10Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x108C, 0x00800000, 23, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe10Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00800000;
            if(BitOfs) *BitOfs = 23;
            return 0x108C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE10_AMPLIFIER2_EN
   unsigned int GetFe10Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x108C, 0x00400000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetFe10Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x108C, 0x00400000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe10Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00400000;
            if(BitOfs) *BitOfs = 22;
            return 0x108C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE10_ATTENUATION
   unsigned int GetFe10Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x108C, 0x000C0000, 18);
         default:
            throw 20;
      };
   };
   unsigned int SetFe10Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x108C, 0x000C0000, 18, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe10AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x108C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE10_MUX
   unsigned int GetFe10Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x108C, 0x00030000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetFe10Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x108C, 0x00030000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe10MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x108C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE10_PZC_EN
   unsigned int GetFe10PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x108C, 0x01000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int SetFe10PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x108C, 0x01000000, 24, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe10PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x108C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE11_AMPLIFIER1_COMP_EN
   unsigned int GetFe11Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x108C, 0x00000020, 5);
         default:
            throw 20;
      };
   };
   unsigned int SetFe11Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x108C, 0x00000020, 5, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe11Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x108C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE11_AMPLIFIER1_EN
   unsigned int GetFe11Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x108C, 0x00000010, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetFe11Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x108C, 0x00000010, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe11Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x108C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE11_AMPLIFIER2_COMP_EN
   unsigned int GetFe11Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x108C, 0x00000080, 7);
         default:
            throw 20;
      };
   };
   unsigned int SetFe11Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x108C, 0x00000080, 7, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe11Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x108C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE11_AMPLIFIER2_EN
   unsigned int GetFe11Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x108C, 0x00000040, 6);
         default:
            throw 20;
      };
   };
   unsigned int SetFe11Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x108C, 0x00000040, 6, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe11Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x108C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE11_ATTENUATION
   unsigned int GetFe11Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x108C, 0x0000000C, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetFe11Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x108C, 0x0000000C, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe11AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x108C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE11_MUX
   unsigned int GetFe11Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x108C, 0x00000003, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetFe11Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x108C, 0x00000003, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe11MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x108C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE11_PZC_EN
   unsigned int GetFe11PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x108C, 0x00000100, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetFe11PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x108C, 0x00000100, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe11PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x108C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE12_AMPLIFIER1_COMP_EN
   unsigned int GetFe12Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1090, 0x00200000, 21);
         default:
            throw 20;
      };
   };
   unsigned int SetFe12Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1090, 0x00200000, 21, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe12Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00200000;
            if(BitOfs) *BitOfs = 21;
            return 0x1090;
         default:
            throw 20;
      };
   };

   // Bit(s) FE12_AMPLIFIER1_EN
   unsigned int GetFe12Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1090, 0x00100000, 20);
         default:
            throw 20;
      };
   };
   unsigned int SetFe12Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1090, 0x00100000, 20, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe12Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x1090;
         default:
            throw 20;
      };
   };

   // Bit(s) FE12_AMPLIFIER2_COMP_EN
   unsigned int GetFe12Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1090, 0x00800000, 23);
         default:
            throw 20;
      };
   };
   unsigned int SetFe12Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1090, 0x00800000, 23, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe12Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00800000;
            if(BitOfs) *BitOfs = 23;
            return 0x1090;
         default:
            throw 20;
      };
   };

   // Bit(s) FE12_AMPLIFIER2_EN
   unsigned int GetFe12Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1090, 0x00400000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetFe12Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1090, 0x00400000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe12Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00400000;
            if(BitOfs) *BitOfs = 22;
            return 0x1090;
         default:
            throw 20;
      };
   };

   // Bit(s) FE12_ATTENUATION
   unsigned int GetFe12Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1090, 0x000C0000, 18);
         default:
            throw 20;
      };
   };
   unsigned int SetFe12Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1090, 0x000C0000, 18, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe12AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x1090;
         default:
            throw 20;
      };
   };

   // Bit(s) FE12_MUX
   unsigned int GetFe12Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1090, 0x00030000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetFe12Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1090, 0x00030000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe12MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x1090;
         default:
            throw 20;
      };
   };

   // Bit(s) FE12_PZC_EN
   unsigned int GetFe12PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1090, 0x01000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int SetFe12PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1090, 0x01000000, 24, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe12PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1090;
         default:
            throw 20;
      };
   };

   // Bit(s) FE13_AMPLIFIER1_COMP_EN
   unsigned int GetFe13Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1090, 0x00000020, 5);
         default:
            throw 20;
      };
   };
   unsigned int SetFe13Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1090, 0x00000020, 5, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe13Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x1090;
         default:
            throw 20;
      };
   };

   // Bit(s) FE13_AMPLIFIER1_EN
   unsigned int GetFe13Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1090, 0x00000010, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetFe13Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1090, 0x00000010, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe13Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x1090;
         default:
            throw 20;
      };
   };

   // Bit(s) FE13_AMPLIFIER2_COMP_EN
   unsigned int GetFe13Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1090, 0x00000080, 7);
         default:
            throw 20;
      };
   };
   unsigned int SetFe13Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1090, 0x00000080, 7, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe13Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x1090;
         default:
            throw 20;
      };
   };

   // Bit(s) FE13_AMPLIFIER2_EN
   unsigned int GetFe13Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1090, 0x00000040, 6);
         default:
            throw 20;
      };
   };
   unsigned int SetFe13Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1090, 0x00000040, 6, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe13Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x1090;
         default:
            throw 20;
      };
   };

   // Bit(s) FE13_ATTENUATION
   unsigned int GetFe13Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1090, 0x0000000C, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetFe13Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1090, 0x0000000C, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe13AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x1090;
         default:
            throw 20;
      };
   };

   // Bit(s) FE13_MUX
   unsigned int GetFe13Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1090, 0x00000003, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetFe13Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1090, 0x00000003, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe13MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x1090;
         default:
            throw 20;
      };
   };

   // Bit(s) FE13_PZC_EN
   unsigned int GetFe13PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1090, 0x00000100, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetFe13PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1090, 0x00000100, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe13PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1090;
         default:
            throw 20;
      };
   };

   // Bit(s) FE14_AMPLIFIER1_COMP_EN
   unsigned int GetFe14Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1094, 0x00200000, 21);
         default:
            throw 20;
      };
   };
   unsigned int SetFe14Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1094, 0x00200000, 21, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe14Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00200000;
            if(BitOfs) *BitOfs = 21;
            return 0x1094;
         default:
            throw 20;
      };
   };

   // Bit(s) FE14_AMPLIFIER1_EN
   unsigned int GetFe14Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1094, 0x00100000, 20);
         default:
            throw 20;
      };
   };
   unsigned int SetFe14Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1094, 0x00100000, 20, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe14Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x1094;
         default:
            throw 20;
      };
   };

   // Bit(s) FE14_AMPLIFIER2_COMP_EN
   unsigned int GetFe14Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1094, 0x00800000, 23);
         default:
            throw 20;
      };
   };
   unsigned int SetFe14Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1094, 0x00800000, 23, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe14Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00800000;
            if(BitOfs) *BitOfs = 23;
            return 0x1094;
         default:
            throw 20;
      };
   };

   // Bit(s) FE14_AMPLIFIER2_EN
   unsigned int GetFe14Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1094, 0x00400000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetFe14Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1094, 0x00400000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe14Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00400000;
            if(BitOfs) *BitOfs = 22;
            return 0x1094;
         default:
            throw 20;
      };
   };

   // Bit(s) FE14_ATTENUATION
   unsigned int GetFe14Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1094, 0x000C0000, 18);
         default:
            throw 20;
      };
   };
   unsigned int SetFe14Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1094, 0x000C0000, 18, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe14AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x1094;
         default:
            throw 20;
      };
   };

   // Bit(s) FE14_MUX
   unsigned int GetFe14Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1094, 0x00030000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetFe14Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1094, 0x00030000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe14MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x1094;
         default:
            throw 20;
      };
   };

   // Bit(s) FE14_PZC_EN
   unsigned int GetFe14PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1094, 0x01000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int SetFe14PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1094, 0x01000000, 24, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe14PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1094;
         default:
            throw 20;
      };
   };

   // Bit(s) FE15_AMPLIFIER1_COMP_EN
   unsigned int GetFe15Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1094, 0x00000020, 5);
         default:
            throw 20;
      };
   };
   unsigned int SetFe15Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1094, 0x00000020, 5, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe15Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x1094;
         default:
            throw 20;
      };
   };

   // Bit(s) FE15_AMPLIFIER1_EN
   unsigned int GetFe15Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1094, 0x00000010, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetFe15Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1094, 0x00000010, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe15Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x1094;
         default:
            throw 20;
      };
   };

   // Bit(s) FE15_AMPLIFIER2_COMP_EN
   unsigned int GetFe15Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1094, 0x00000080, 7);
         default:
            throw 20;
      };
   };
   unsigned int SetFe15Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1094, 0x00000080, 7, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe15Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x1094;
         default:
            throw 20;
      };
   };

   // Bit(s) FE15_AMPLIFIER2_EN
   unsigned int GetFe15Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1094, 0x00000040, 6);
         default:
            throw 20;
      };
   };
   unsigned int SetFe15Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1094, 0x00000040, 6, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe15Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x1094;
         default:
            throw 20;
      };
   };

   // Bit(s) FE15_ATTENUATION
   unsigned int GetFe15Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1094, 0x0000000C, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetFe15Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1094, 0x0000000C, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe15AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x1094;
         default:
            throw 20;
      };
   };

   // Bit(s) FE15_MUX
   unsigned int GetFe15Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1094, 0x00000003, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetFe15Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1094, 0x00000003, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe15MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x1094;
         default:
            throw 20;
      };
   };

   // Bit(s) FE15_PZC_EN
   unsigned int GetFe15PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1094, 0x00000100, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetFe15PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1094, 0x00000100, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe15PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1094;
         default:
            throw 20;
      };
   };

   // Bit(s) FE1_AMPLIFIER1_COMP_EN
   unsigned int GetFe1Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1078, 0x00000020, 5);
         default:
            throw 20;
      };
   };
   unsigned int SetFe1Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1078, 0x00000020, 5, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe1Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x1078;
         default:
            throw 20;
      };
   };

   // Bit(s) FE1_AMPLIFIER1_EN
   unsigned int GetFe1Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1078, 0x00000010, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetFe1Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1078, 0x00000010, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe1Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x1078;
         default:
            throw 20;
      };
   };

   // Bit(s) FE1_AMPLIFIER2_COMP_EN
   unsigned int GetFe1Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1078, 0x00000080, 7);
         default:
            throw 20;
      };
   };
   unsigned int SetFe1Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1078, 0x00000080, 7, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe1Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x1078;
         default:
            throw 20;
      };
   };

   // Bit(s) FE1_AMPLIFIER2_EN
   unsigned int GetFe1Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1078, 0x00000040, 6);
         default:
            throw 20;
      };
   };
   unsigned int SetFe1Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1078, 0x00000040, 6, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe1Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x1078;
         default:
            throw 20;
      };
   };

   // Bit(s) FE1_ATTENUATION
   unsigned int GetFe1Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1078, 0x0000000C, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetFe1Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1078, 0x0000000C, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe1AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x1078;
         default:
            throw 20;
      };
   };

   // Bit(s) FE1_MUX
   unsigned int GetFe1Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1078, 0x00000003, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetFe1Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1078, 0x00000003, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe1MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x1078;
         default:
            throw 20;
      };
   };

   // Bit(s) FE1_PZC_EN
   unsigned int GetFe1PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1078, 0x00000100, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetFe1PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1078, 0x00000100, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe1PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1078;
         default:
            throw 20;
      };
   };

   // Bit(s) FE2_AMPLIFIER1_COMP_EN
   unsigned int GetFe2Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x107C, 0x00200000, 21);
         default:
            throw 20;
      };
   };
   unsigned int SetFe2Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x107C, 0x00200000, 21, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe2Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00200000;
            if(BitOfs) *BitOfs = 21;
            return 0x107C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE2_AMPLIFIER1_EN
   unsigned int GetFe2Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x107C, 0x00100000, 20);
         default:
            throw 20;
      };
   };
   unsigned int SetFe2Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x107C, 0x00100000, 20, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe2Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x107C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE2_AMPLIFIER2_COMP_EN
   unsigned int GetFe2Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x107C, 0x00800000, 23);
         default:
            throw 20;
      };
   };
   unsigned int SetFe2Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x107C, 0x00800000, 23, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe2Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00800000;
            if(BitOfs) *BitOfs = 23;
            return 0x107C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE2_AMPLIFIER2_EN
   unsigned int GetFe2Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x107C, 0x00400000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetFe2Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x107C, 0x00400000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe2Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00400000;
            if(BitOfs) *BitOfs = 22;
            return 0x107C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE2_ATTENUATION
   unsigned int GetFe2Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x107C, 0x000C0000, 18);
         default:
            throw 20;
      };
   };
   unsigned int SetFe2Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x107C, 0x000C0000, 18, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe2AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x107C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE2_MUX
   unsigned int GetFe2Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x107C, 0x00030000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetFe2Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x107C, 0x00030000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe2MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x107C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE2_PZC_EN
   unsigned int GetFe2PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x107C, 0x01000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int SetFe2PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x107C, 0x01000000, 24, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe2PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x107C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE3_AMPLIFIER1_COMP_EN
   unsigned int GetFe3Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x107C, 0x00000020, 5);
         default:
            throw 20;
      };
   };
   unsigned int SetFe3Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x107C, 0x00000020, 5, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe3Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x107C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE3_AMPLIFIER1_EN
   unsigned int GetFe3Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x107C, 0x00000010, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetFe3Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x107C, 0x00000010, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe3Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x107C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE3_AMPLIFIER2_COMP_EN
   unsigned int GetFe3Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x107C, 0x00000080, 7);
         default:
            throw 20;
      };
   };
   unsigned int SetFe3Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x107C, 0x00000080, 7, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe3Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x107C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE3_AMPLIFIER2_EN
   unsigned int GetFe3Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x107C, 0x00000040, 6);
         default:
            throw 20;
      };
   };
   unsigned int SetFe3Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x107C, 0x00000040, 6, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe3Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x107C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE3_ATTENUATION
   unsigned int GetFe3Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x107C, 0x0000000C, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetFe3Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x107C, 0x0000000C, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe3AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x107C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE3_MUX
   unsigned int GetFe3Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x107C, 0x00000003, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetFe3Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x107C, 0x00000003, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe3MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x107C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE3_PZC_EN
   unsigned int GetFe3PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x107C, 0x00000100, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetFe3PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x107C, 0x00000100, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe3PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x107C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE4_AMPLIFIER1_COMP_EN
   unsigned int GetFe4Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1080, 0x00200000, 21);
         default:
            throw 20;
      };
   };
   unsigned int SetFe4Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1080, 0x00200000, 21, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe4Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00200000;
            if(BitOfs) *BitOfs = 21;
            return 0x1080;
         default:
            throw 20;
      };
   };

   // Bit(s) FE4_AMPLIFIER1_EN
   unsigned int GetFe4Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1080, 0x00100000, 20);
         default:
            throw 20;
      };
   };
   unsigned int SetFe4Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1080, 0x00100000, 20, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe4Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x1080;
         default:
            throw 20;
      };
   };

   // Bit(s) FE4_AMPLIFIER2_COMP_EN
   unsigned int GetFe4Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1080, 0x00800000, 23);
         default:
            throw 20;
      };
   };
   unsigned int SetFe4Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1080, 0x00800000, 23, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe4Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00800000;
            if(BitOfs) *BitOfs = 23;
            return 0x1080;
         default:
            throw 20;
      };
   };

   // Bit(s) FE4_AMPLIFIER2_EN
   unsigned int GetFe4Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1080, 0x00400000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetFe4Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1080, 0x00400000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe4Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00400000;
            if(BitOfs) *BitOfs = 22;
            return 0x1080;
         default:
            throw 20;
      };
   };

   // Bit(s) FE4_ATTENUATION
   unsigned int GetFe4Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1080, 0x000C0000, 18);
         default:
            throw 20;
      };
   };
   unsigned int SetFe4Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1080, 0x000C0000, 18, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe4AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x1080;
         default:
            throw 20;
      };
   };

   // Bit(s) FE4_MUX
   unsigned int GetFe4Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1080, 0x00030000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetFe4Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1080, 0x00030000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe4MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x1080;
         default:
            throw 20;
      };
   };

   // Bit(s) FE4_PZC_EN
   unsigned int GetFe4PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1080, 0x01000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int SetFe4PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1080, 0x01000000, 24, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe4PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1080;
         default:
            throw 20;
      };
   };

   // Bit(s) FE5_AMPLIFIER1_COMP_EN
   unsigned int GetFe5Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1080, 0x00000020, 5);
         default:
            throw 20;
      };
   };
   unsigned int SetFe5Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1080, 0x00000020, 5, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe5Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x1080;
         default:
            throw 20;
      };
   };

   // Bit(s) FE5_AMPLIFIER1_EN
   unsigned int GetFe5Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1080, 0x00000010, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetFe5Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1080, 0x00000010, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe5Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x1080;
         default:
            throw 20;
      };
   };

   // Bit(s) FE5_AMPLIFIER2_COMP_EN
   unsigned int GetFe5Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1080, 0x00000080, 7);
         default:
            throw 20;
      };
   };
   unsigned int SetFe5Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1080, 0x00000080, 7, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe5Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x1080;
         default:
            throw 20;
      };
   };

   // Bit(s) FE5_AMPLIFIER2_EN
   unsigned int GetFe5Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1080, 0x00000040, 6);
         default:
            throw 20;
      };
   };
   unsigned int SetFe5Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1080, 0x00000040, 6, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe5Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x1080;
         default:
            throw 20;
      };
   };

   // Bit(s) FE5_ATTENUATION
   unsigned int GetFe5Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1080, 0x0000000C, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetFe5Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1080, 0x0000000C, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe5AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x1080;
         default:
            throw 20;
      };
   };

   // Bit(s) FE5_MUX
   unsigned int GetFe5Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1080, 0x00000003, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetFe5Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1080, 0x00000003, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe5MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x1080;
         default:
            throw 20;
      };
   };

   // Bit(s) FE5_PZC_EN
   unsigned int GetFe5PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1080, 0x00000100, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetFe5PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1080, 0x00000100, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe5PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1080;
         default:
            throw 20;
      };
   };

   // Bit(s) FE6_AMPLIFIER1_COMP_EN
   unsigned int GetFe6Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1084, 0x00200000, 21);
         default:
            throw 20;
      };
   };
   unsigned int SetFe6Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1084, 0x00200000, 21, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe6Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00200000;
            if(BitOfs) *BitOfs = 21;
            return 0x1084;
         default:
            throw 20;
      };
   };

   // Bit(s) FE6_AMPLIFIER1_EN
   unsigned int GetFe6Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1084, 0x00100000, 20);
         default:
            throw 20;
      };
   };
   unsigned int SetFe6Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1084, 0x00100000, 20, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe6Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x1084;
         default:
            throw 20;
      };
   };

   // Bit(s) FE6_AMPLIFIER2_COMP_EN
   unsigned int GetFe6Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1084, 0x00800000, 23);
         default:
            throw 20;
      };
   };
   unsigned int SetFe6Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1084, 0x00800000, 23, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe6Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00800000;
            if(BitOfs) *BitOfs = 23;
            return 0x1084;
         default:
            throw 20;
      };
   };

   // Bit(s) FE6_AMPLIFIER2_EN
   unsigned int GetFe6Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1084, 0x00400000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetFe6Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1084, 0x00400000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe6Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00400000;
            if(BitOfs) *BitOfs = 22;
            return 0x1084;
         default:
            throw 20;
      };
   };

   // Bit(s) FE6_ATTENUATION
   unsigned int GetFe6Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1084, 0x000C0000, 18);
         default:
            throw 20;
      };
   };
   unsigned int SetFe6Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1084, 0x000C0000, 18, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe6AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x1084;
         default:
            throw 20;
      };
   };

   // Bit(s) FE6_MUX
   unsigned int GetFe6Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1084, 0x00030000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetFe6Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1084, 0x00030000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe6MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x1084;
         default:
            throw 20;
      };
   };

   // Bit(s) FE6_PZC_EN
   unsigned int GetFe6PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1084, 0x01000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int SetFe6PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1084, 0x01000000, 24, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe6PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1084;
         default:
            throw 20;
      };
   };

   // Bit(s) FE7_AMPLIFIER1_COMP_EN
   unsigned int GetFe7Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1084, 0x00000020, 5);
         default:
            throw 20;
      };
   };
   unsigned int SetFe7Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1084, 0x00000020, 5, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe7Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x1084;
         default:
            throw 20;
      };
   };

   // Bit(s) FE7_AMPLIFIER1_EN
   unsigned int GetFe7Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1084, 0x00000010, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetFe7Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1084, 0x00000010, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe7Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x1084;
         default:
            throw 20;
      };
   };

   // Bit(s) FE7_AMPLIFIER2_COMP_EN
   unsigned int GetFe7Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1084, 0x00000080, 7);
         default:
            throw 20;
      };
   };
   unsigned int SetFe7Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1084, 0x00000080, 7, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe7Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x1084;
         default:
            throw 20;
      };
   };

   // Bit(s) FE7_AMPLIFIER2_EN
   unsigned int GetFe7Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1084, 0x00000040, 6);
         default:
            throw 20;
      };
   };
   unsigned int SetFe7Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1084, 0x00000040, 6, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe7Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x1084;
         default:
            throw 20;
      };
   };

   // Bit(s) FE7_ATTENUATION
   unsigned int GetFe7Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1084, 0x0000000C, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetFe7Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1084, 0x0000000C, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe7AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x1084;
         default:
            throw 20;
      };
   };

   // Bit(s) FE7_MUX
   unsigned int GetFe7Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1084, 0x00000003, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetFe7Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1084, 0x00000003, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe7MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x1084;
         default:
            throw 20;
      };
   };

   // Bit(s) FE7_PZC_EN
   unsigned int GetFe7PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1084, 0x00000100, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetFe7PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1084, 0x00000100, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe7PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1084;
         default:
            throw 20;
      };
   };

   // Bit(s) FE8_AMPLIFIER1_COMP_EN
   unsigned int GetFe8Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1088, 0x00200000, 21);
         default:
            throw 20;
      };
   };
   unsigned int SetFe8Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1088, 0x00200000, 21, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe8Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00200000;
            if(BitOfs) *BitOfs = 21;
            return 0x1088;
         default:
            throw 20;
      };
   };

   // Bit(s) FE8_AMPLIFIER1_EN
   unsigned int GetFe8Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1088, 0x00100000, 20);
         default:
            throw 20;
      };
   };
   unsigned int SetFe8Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1088, 0x00100000, 20, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe8Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00100000;
            if(BitOfs) *BitOfs = 20;
            return 0x1088;
         default:
            throw 20;
      };
   };

   // Bit(s) FE8_AMPLIFIER2_COMP_EN
   unsigned int GetFe8Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1088, 0x00800000, 23);
         default:
            throw 20;
      };
   };
   unsigned int SetFe8Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1088, 0x00800000, 23, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe8Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00800000;
            if(BitOfs) *BitOfs = 23;
            return 0x1088;
         default:
            throw 20;
      };
   };

   // Bit(s) FE8_AMPLIFIER2_EN
   unsigned int GetFe8Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1088, 0x00400000, 22);
         default:
            throw 20;
      };
   };
   unsigned int SetFe8Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1088, 0x00400000, 22, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe8Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00400000;
            if(BitOfs) *BitOfs = 22;
            return 0x1088;
         default:
            throw 20;
      };
   };

   // Bit(s) FE8_ATTENUATION
   unsigned int GetFe8Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1088, 0x000C0000, 18);
         default:
            throw 20;
      };
   };
   unsigned int SetFe8Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1088, 0x000C0000, 18, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe8AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x1088;
         default:
            throw 20;
      };
   };

   // Bit(s) FE8_MUX
   unsigned int GetFe8Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1088, 0x00030000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetFe8Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1088, 0x00030000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe8MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x1088;
         default:
            throw 20;
      };
   };

   // Bit(s) FE8_PZC_EN
   unsigned int GetFe8PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1088, 0x01000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int SetFe8PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1088, 0x01000000, 24, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe8PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1088;
         default:
            throw 20;
      };
   };

   // Bit(s) FE9_AMPLIFIER1_COMP_EN
   unsigned int GetFe9Amplifier1CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1088, 0x00000020, 5);
         default:
            throw 20;
      };
   };
   unsigned int SetFe9Amplifier1CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1088, 0x00000020, 5, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe9Amplifier1CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x1088;
         default:
            throw 20;
      };
   };

   // Bit(s) FE9_AMPLIFIER1_EN
   unsigned int GetFe9Amplifier1En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1088, 0x00000010, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetFe9Amplifier1En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1088, 0x00000010, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe9Amplifier1EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x1088;
         default:
            throw 20;
      };
   };

   // Bit(s) FE9_AMPLIFIER2_COMP_EN
   unsigned int GetFe9Amplifier2CompEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1088, 0x00000080, 7);
         default:
            throw 20;
      };
   };
   unsigned int SetFe9Amplifier2CompEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1088, 0x00000080, 7, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe9Amplifier2CompEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x1088;
         default:
            throw 20;
      };
   };

   // Bit(s) FE9_AMPLIFIER2_EN
   unsigned int GetFe9Amplifier2En()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1088, 0x00000040, 6);
         default:
            throw 20;
      };
   };
   unsigned int SetFe9Amplifier2En(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1088, 0x00000040, 6, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe9Amplifier2EnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x1088;
         default:
            throw 20;
      };
   };

   // Bit(s) FE9_ATTENUATION
   unsigned int GetFe9Attenuation()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1088, 0x0000000C, 2);
         default:
            throw 20;
      };
   };
   unsigned int SetFe9Attenuation(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1088, 0x0000000C, 2, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe9AttenuationLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x1088;
         default:
            throw 20;
      };
   };

   // Bit(s) FE9_MUX
   unsigned int GetFe9Mux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1088, 0x00000003, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetFe9Mux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1088, 0x00000003, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe9MuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x1088;
         default:
            throw 20;
      };
   };

   // Bit(s) FE9_PZC_EN
   unsigned int GetFe9PzcEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1088, 0x00000100, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetFe9PzcEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1088, 0x00000100, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFe9PzcEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1088;
         default:
            throw 20;
      };
   };

   // Bit(s) FE_0_MOD
   unsigned int GetFe0Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0150, 0xC0000000, 30);
         case 9:
            return BitExtractStatus(0x014C, 0xC0000000, 30);
         default:
            throw 20;
      };
   };
   unsigned int GetFe0ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xC0000000;
            if(BitOfs) *BitOfs = 30;
            return 0x0150;
         case 9:
            if(BitMask) *BitMask = 0xC0000000;
            if(BitOfs) *BitOfs = 30;
            return 0x014C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE_10_MOD
   unsigned int GetFe10Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0150, 0x00000C00, 10);
         case 9:
            return BitExtractStatus(0x014C, 0x00000C00, 10);
         default:
            throw 20;
      };
   };
   unsigned int GetFe10ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000C00;
            if(BitOfs) *BitOfs = 10;
            return 0x0150;
         case 9:
            if(BitMask) *BitMask = 0x00000C00;
            if(BitOfs) *BitOfs = 10;
            return 0x014C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE_11_MOD
   unsigned int GetFe11Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0150, 0x00000300, 8);
         case 9:
            return BitExtractStatus(0x014C, 0x00000300, 8);
         default:
            throw 20;
      };
   };
   unsigned int GetFe11ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000300;
            if(BitOfs) *BitOfs = 8;
            return 0x0150;
         case 9:
            if(BitMask) *BitMask = 0x00000300;
            if(BitOfs) *BitOfs = 8;
            return 0x014C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE_12_MOD
   unsigned int GetFe12Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0150, 0x000000C0, 6);
         case 9:
            return BitExtractStatus(0x014C, 0x000000C0, 6);
         default:
            throw 20;
      };
   };
   unsigned int GetFe12ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000000C0;
            if(BitOfs) *BitOfs = 6;
            return 0x0150;
         case 9:
            if(BitMask) *BitMask = 0x000000C0;
            if(BitOfs) *BitOfs = 6;
            return 0x014C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE_13_MOD
   unsigned int GetFe13Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0150, 0x00000030, 4);
         case 9:
            return BitExtractStatus(0x014C, 0x00000030, 4);
         default:
            throw 20;
      };
   };
   unsigned int GetFe13ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000030;
            if(BitOfs) *BitOfs = 4;
            return 0x0150;
         case 9:
            if(BitMask) *BitMask = 0x00000030;
            if(BitOfs) *BitOfs = 4;
            return 0x014C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE_14_MOD
   unsigned int GetFe14Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0150, 0x0000000C, 2);
         case 9:
            return BitExtractStatus(0x014C, 0x0000000C, 2);
         default:
            throw 20;
      };
   };
   unsigned int GetFe14ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x0150;
         case 9:
            if(BitMask) *BitMask = 0x0000000C;
            if(BitOfs) *BitOfs = 2;
            return 0x014C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE_15_MOD
   unsigned int GetFe15Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0150, 0x00000003, 0);
         case 9:
            return BitExtractStatus(0x014C, 0x00000003, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetFe15ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x0150;
         case 9:
            if(BitMask) *BitMask = 0x00000003;
            if(BitOfs) *BitOfs = 0;
            return 0x014C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE_1_MOD
   unsigned int GetFe1Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0150, 0x30000000, 28);
         case 9:
            return BitExtractStatus(0x014C, 0x30000000, 28);
         default:
            throw 20;
      };
   };
   unsigned int GetFe1ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x30000000;
            if(BitOfs) *BitOfs = 28;
            return 0x0150;
         case 9:
            if(BitMask) *BitMask = 0x30000000;
            if(BitOfs) *BitOfs = 28;
            return 0x014C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE_2_MOD
   unsigned int GetFe2Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0150, 0x0C000000, 26);
         case 9:
            return BitExtractStatus(0x014C, 0x0C000000, 26);
         default:
            throw 20;
      };
   };
   unsigned int GetFe2ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0C000000;
            if(BitOfs) *BitOfs = 26;
            return 0x0150;
         case 9:
            if(BitMask) *BitMask = 0x0C000000;
            if(BitOfs) *BitOfs = 26;
            return 0x014C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE_3_MOD
   unsigned int GetFe3Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0150, 0x03000000, 24);
         case 9:
            return BitExtractStatus(0x014C, 0x03000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int GetFe3ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x03000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0150;
         case 9:
            if(BitMask) *BitMask = 0x03000000;
            if(BitOfs) *BitOfs = 24;
            return 0x014C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE_4_MOD
   unsigned int GetFe4Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0150, 0x00C00000, 22);
         case 9:
            return BitExtractStatus(0x014C, 0x00C00000, 22);
         default:
            throw 20;
      };
   };
   unsigned int GetFe4ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x0150;
         case 9:
            if(BitMask) *BitMask = 0x00C00000;
            if(BitOfs) *BitOfs = 22;
            return 0x014C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE_5_MOD
   unsigned int GetFe5Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0150, 0x00300000, 20);
         case 9:
            return BitExtractStatus(0x014C, 0x00300000, 20);
         default:
            throw 20;
      };
   };
   unsigned int GetFe5ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00300000;
            if(BitOfs) *BitOfs = 20;
            return 0x0150;
         case 9:
            if(BitMask) *BitMask = 0x00300000;
            if(BitOfs) *BitOfs = 20;
            return 0x014C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE_6_MOD
   unsigned int GetFe6Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0150, 0x000C0000, 18);
         case 9:
            return BitExtractStatus(0x014C, 0x000C0000, 18);
         default:
            throw 20;
      };
   };
   unsigned int GetFe6ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x0150;
         case 9:
            if(BitMask) *BitMask = 0x000C0000;
            if(BitOfs) *BitOfs = 18;
            return 0x014C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE_7_MOD
   unsigned int GetFe7Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0150, 0x00030000, 16);
         case 9:
            return BitExtractStatus(0x014C, 0x00030000, 16);
         default:
            throw 20;
      };
   };
   unsigned int GetFe7ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x0150;
         case 9:
            if(BitMask) *BitMask = 0x00030000;
            if(BitOfs) *BitOfs = 16;
            return 0x014C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE_8_MOD
   unsigned int GetFe8Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0150, 0x0000C000, 14);
         case 9:
            return BitExtractStatus(0x014C, 0x0000C000, 14);
         default:
            throw 20;
      };
   };
   unsigned int GetFe8ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000C000;
            if(BitOfs) *BitOfs = 14;
            return 0x0150;
         case 9:
            if(BitMask) *BitMask = 0x0000C000;
            if(BitOfs) *BitOfs = 14;
            return 0x014C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE_9_MOD
   unsigned int GetFe9Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0150, 0x00003000, 12);
         case 9:
            return BitExtractStatus(0x014C, 0x00003000, 12);
         default:
            throw 20;
      };
   };
   unsigned int GetFe9ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00003000;
            if(BitOfs) *BitOfs = 12;
            return 0x0150;
         case 9:
            if(BitMask) *BitMask = 0x00003000;
            if(BitOfs) *BitOfs = 12;
            return 0x014C;
         default:
            throw 20;
      };
   };

   // Bit(s) FE_POWER
   unsigned int GetFePower()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractControl(0x1004, 0x00000800, 11);
         default:
            throw 20;
      };
   };
   unsigned int SetFePower(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 9:
            return SetRegMask(0x1004, 0x00000800, 11, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFePowerLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00000800;
            if(BitOfs) *BitOfs = 11;
            return 0x1004;
         default:
            throw 20;
      };
   };

   // Bit(s) FIRST_PKG_DLY
   unsigned int GetFirstPkgDly()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1018, 0xFFFC0000, 18);
         default:
            throw 20;
      };
   };
   unsigned int SetFirstPkgDly(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1018, 0xFFFC0000, 18, value);
         default:
            throw 20;
      };
   };
   unsigned int GetFirstPkgDlyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFC0000;
            if(BitOfs) *BitOfs = 18;
            return 0x1018;
         default:
            throw 20;
      };
   };

   // Bit(s) FLASH_SEL
   unsigned int GetFlashSel()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0028, 0x00000200, 9);
         default:
            throw 20;
      };
   };
   unsigned int GetFlashSelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000200;
            if(BitOfs) *BitOfs = 9;
            return 0x0028;
         default:
            throw 20;
      };
   };

   // Bit(s) FW_BUILD_DAY
   unsigned int GetFwBuildDay()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0008, 0x000000FF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetFwBuildDayLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x0008;
         default:
            throw 20;
      };
   };

   // Bit(s) FW_BUILD_HOUR
   unsigned int GetFwBuildHour()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x000C, 0x00FF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int GetFwBuildHourLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00FF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x000C;
         default:
            throw 20;
      };
   };

   // Bit(s) FW_BUILD_MINUTE
   unsigned int GetFwBuildMinute()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x000C, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int GetFwBuildMinuteLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x000C;
         default:
            throw 20;
      };
   };

   // Bit(s) FW_BUILD_MONTH
   unsigned int GetFwBuildMonth()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0008, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int GetFwBuildMonthLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x0008;
         default:
            throw 20;
      };
   };

   // Bit(s) FW_BUILD_SECOND
   unsigned int GetFwBuildSecond()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x000C, 0x000000FF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetFwBuildSecondLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x000C;
         default:
            throw 20;
      };
   };

   // Bit(s) FW_BUILD_YEAR
   unsigned int GetFwBuildYear()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0008, 0xFFFF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int GetFwBuildYearLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0008;
         default:
            throw 20;
      };
   };

   // Bit(s) FW_COMPAT_LEVEL
   unsigned int GetFwCompatLevel()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x000C, 0xFF000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int GetFwCompatLevelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFF000000;
            if(BitOfs) *BitOfs = 24;
            return 0x000C;
         default:
            throw 20;
      };
   };

   // Bit(s) FW_GIT_HASH_TAG
   unsigned int GetFwGitHashTag()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0018, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetFwGitHashTagLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0018;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_BOARD_PLUGGED
   unsigned int GetHvBoardPlugged()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0028, 0x00000002, 1);
         default:
            throw 20;
      };
   };
   unsigned int GetHvBoardPluggedLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000002;
            if(BitOfs) *BitOfs = 1;
            return 0x0028;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_I_MEAS_0
   unsigned int GetHvIMeas0()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x004C, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0048, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvIMeas0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x004C;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0048;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_I_MEAS_1
   unsigned int GetHvIMeas1()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0050, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x004C, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvIMeas1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0050;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x004C;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_I_MEAS_10
   unsigned int GetHvIMeas10()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0074, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0070, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvIMeas10Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0074;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0070;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_I_MEAS_11
   unsigned int GetHvIMeas11()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0078, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0074, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvIMeas11Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0078;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0074;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_I_MEAS_12
   unsigned int GetHvIMeas12()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x007C, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0078, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvIMeas12Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x007C;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0078;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_I_MEAS_13
   unsigned int GetHvIMeas13()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0080, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x007C, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvIMeas13Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0080;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x007C;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_I_MEAS_14
   unsigned int GetHvIMeas14()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0084, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0080, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvIMeas14Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0084;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0080;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_I_MEAS_15
   unsigned int GetHvIMeas15()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0088, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0084, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvIMeas15Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0088;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0084;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_I_MEAS_2
   unsigned int GetHvIMeas2()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0054, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0050, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvIMeas2Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0054;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0050;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_I_MEAS_3
   unsigned int GetHvIMeas3()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0058, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0054, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvIMeas3Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0058;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0054;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_I_MEAS_4
   unsigned int GetHvIMeas4()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x005C, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0058, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvIMeas4Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x005C;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0058;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_I_MEAS_5
   unsigned int GetHvIMeas5()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0060, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x005C, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvIMeas5Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0060;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x005C;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_I_MEAS_6
   unsigned int GetHvIMeas6()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0064, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0060, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvIMeas6Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0064;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0060;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_I_MEAS_7
   unsigned int GetHvIMeas7()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0068, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0064, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvIMeas7Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0068;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0064;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_I_MEAS_8
   unsigned int GetHvIMeas8()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x006C, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0068, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvIMeas8Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x006C;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0068;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_I_MEAS_9
   unsigned int GetHvIMeas9()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0070, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x006C, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvIMeas9Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0070;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x006C;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_R_SHUNT
   unsigned int GetHvRShunt()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10D8, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetHvRShunt(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10D8, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetHvRShuntLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10D8;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_R_SHUNT_MOD
   unsigned int GetHvRShuntMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x015C, 0x0000000F, 0);
         case 9:
            return BitExtractStatus(0x0158, 0x0000000F, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvRShuntModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x015C;
         case 9:
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0158;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_TEMP_0
   unsigned int GetHvTemp0()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0090, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x008C, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvTemp0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0090;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x008C;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_TEMP_1
   unsigned int GetHvTemp1()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0094, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0090, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvTemp1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0094;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0090;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_TEMP_2
   unsigned int GetHvTemp2()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0098, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0094, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvTemp2Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0098;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0094;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_TEMP_3
   unsigned int GetHvTemp3()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x009C, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0098, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvTemp3Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x009C;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0098;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_BASE_MEAS
   unsigned int GetHvUBaseMeas()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x008C, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0088, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUBaseMeasLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x008C;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0088;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_0
   unsigned int GetHvUTarget0()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1098, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetHvUTarget0(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1098, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1098;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_0_MOD
   unsigned int GetHvUTarget0Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0154, 0xF0000000, 28);
         case 9:
            return BitExtractStatus(0x0150, 0xF0000000, 28);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget0ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xF0000000;
            if(BitOfs) *BitOfs = 28;
            return 0x0154;
         case 9:
            if(BitMask) *BitMask = 0xF0000000;
            if(BitOfs) *BitOfs = 28;
            return 0x0150;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_1
   unsigned int GetHvUTarget1()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x109C, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetHvUTarget1(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x109C, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x109C;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_10
   unsigned int GetHvUTarget10()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10C0, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetHvUTarget10(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10C0, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget10Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10C0;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_10_MOD
   unsigned int GetHvUTarget10Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0158, 0x00F00000, 20);
         case 9:
            return BitExtractStatus(0x0154, 0x00F00000, 20);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget10ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00F00000;
            if(BitOfs) *BitOfs = 20;
            return 0x0158;
         case 9:
            if(BitMask) *BitMask = 0x00F00000;
            if(BitOfs) *BitOfs = 20;
            return 0x0154;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_11
   unsigned int GetHvUTarget11()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10C4, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetHvUTarget11(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10C4, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget11Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10C4;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_11_MOD
   unsigned int GetHvUTarget11Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0158, 0x000F0000, 16);
         case 9:
            return BitExtractStatus(0x0154, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget11ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0158;
         case 9:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0154;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_12
   unsigned int GetHvUTarget12()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10C8, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetHvUTarget12(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10C8, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget12Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10C8;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_12_MOD
   unsigned int GetHvUTarget12Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0158, 0x0000F000, 12);
         case 9:
            return BitExtractStatus(0x0154, 0x0000F000, 12);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget12ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000F000;
            if(BitOfs) *BitOfs = 12;
            return 0x0158;
         case 9:
            if(BitMask) *BitMask = 0x0000F000;
            if(BitOfs) *BitOfs = 12;
            return 0x0154;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_13
   unsigned int GetHvUTarget13()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10CC, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetHvUTarget13(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10CC, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget13Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10CC;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_13_MOD
   unsigned int GetHvUTarget13Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0158, 0x00000F00, 8);
         case 9:
            return BitExtractStatus(0x0154, 0x00000F00, 8);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget13ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000F00;
            if(BitOfs) *BitOfs = 8;
            return 0x0158;
         case 9:
            if(BitMask) *BitMask = 0x00000F00;
            if(BitOfs) *BitOfs = 8;
            return 0x0154;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_14
   unsigned int GetHvUTarget14()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10D0, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetHvUTarget14(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10D0, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget14Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10D0;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_14_MOD
   unsigned int GetHvUTarget14Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0158, 0x000000F0, 4);
         case 9:
            return BitExtractStatus(0x0154, 0x000000F0, 4);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget14ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x0158;
         case 9:
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x0154;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_15
   unsigned int GetHvUTarget15()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10D4, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetHvUTarget15(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10D4, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget15Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10D4;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_15_MOD
   unsigned int GetHvUTarget15Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0158, 0x0000000F, 0);
         case 9:
            return BitExtractStatus(0x0154, 0x0000000F, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget15ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0158;
         case 9:
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0154;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_1_MOD
   unsigned int GetHvUTarget1Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0154, 0x0F000000, 24);
         case 9:
            return BitExtractStatus(0x0150, 0x0F000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget1ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0F000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0154;
         case 9:
            if(BitMask) *BitMask = 0x0F000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0150;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_2
   unsigned int GetHvUTarget2()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10A0, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetHvUTarget2(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10A0, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget2Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10A0;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_2_MOD
   unsigned int GetHvUTarget2Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0154, 0x00F00000, 20);
         case 9:
            return BitExtractStatus(0x0150, 0x00F00000, 20);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget2ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00F00000;
            if(BitOfs) *BitOfs = 20;
            return 0x0154;
         case 9:
            if(BitMask) *BitMask = 0x00F00000;
            if(BitOfs) *BitOfs = 20;
            return 0x0150;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_3
   unsigned int GetHvUTarget3()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10A4, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetHvUTarget3(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10A4, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget3Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10A4;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_3_MOD
   unsigned int GetHvUTarget3Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0154, 0x000F0000, 16);
         case 9:
            return BitExtractStatus(0x0150, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget3ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0154;
         case 9:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0150;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_4
   unsigned int GetHvUTarget4()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10A8, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetHvUTarget4(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10A8, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget4Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10A8;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_4_MOD
   unsigned int GetHvUTarget4Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0154, 0x0000F000, 12);
         case 9:
            return BitExtractStatus(0x0150, 0x0000F000, 12);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget4ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000F000;
            if(BitOfs) *BitOfs = 12;
            return 0x0154;
         case 9:
            if(BitMask) *BitMask = 0x0000F000;
            if(BitOfs) *BitOfs = 12;
            return 0x0150;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_5
   unsigned int GetHvUTarget5()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10AC, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetHvUTarget5(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10AC, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget5Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10AC;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_5_MOD
   unsigned int GetHvUTarget5Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0154, 0x00000F00, 8);
         case 9:
            return BitExtractStatus(0x0150, 0x00000F00, 8);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget5ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000F00;
            if(BitOfs) *BitOfs = 8;
            return 0x0154;
         case 9:
            if(BitMask) *BitMask = 0x00000F00;
            if(BitOfs) *BitOfs = 8;
            return 0x0150;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_6
   unsigned int GetHvUTarget6()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10B0, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetHvUTarget6(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10B0, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget6Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10B0;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_6_MOD
   unsigned int GetHvUTarget6Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0154, 0x000000F0, 4);
         case 9:
            return BitExtractStatus(0x0150, 0x000000F0, 4);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget6ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x0154;
         case 9:
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x0150;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_7
   unsigned int GetHvUTarget7()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10B4, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetHvUTarget7(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10B4, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget7Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10B4;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_7_MOD
   unsigned int GetHvUTarget7Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0154, 0x0000000F, 0);
         case 9:
            return BitExtractStatus(0x0150, 0x0000000F, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget7ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0154;
         case 9:
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0150;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_8
   unsigned int GetHvUTarget8()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10B8, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetHvUTarget8(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10B8, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget8Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10B8;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_8_MOD
   unsigned int GetHvUTarget8Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0158, 0xF0000000, 28);
         case 9:
            return BitExtractStatus(0x0154, 0xF0000000, 28);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget8ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xF0000000;
            if(BitOfs) *BitOfs = 28;
            return 0x0158;
         case 9:
            if(BitMask) *BitMask = 0xF0000000;
            if(BitOfs) *BitOfs = 28;
            return 0x0154;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_9
   unsigned int GetHvUTarget9()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10BC, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetHvUTarget9(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10BC, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget9Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x10BC;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_U_TARGET_9_MOD
   unsigned int GetHvUTarget9Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0158, 0x0F000000, 24);
         case 9:
            return BitExtractStatus(0x0154, 0x0F000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int GetHvUTarget9ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0F000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0158;
         case 9:
            if(BitMask) *BitMask = 0x0F000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0154;
         default:
            throw 20;
      };
   };

   // Bit(s) HV_VER
   unsigned int GetHvVer()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0048, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0044, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetHvVerLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0048;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0044;
         default:
            throw 20;
      };
   };

   // Bit(s) INTER_PKG_DELAY
   unsigned int GetInterPkgDelay()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1014, 0x00FFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetInterPkgDelay(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1014, 0x00FFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetInterPkgDelayLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00FFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1014;
         default:
            throw 20;
      };
   };

   // Bit(s) ISERDES_PLL_LOCK_0
   unsigned int GetIserdesPllLock0()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x002C, 0x00000010, 4);
         default:
            throw 20;
      };
   };
   unsigned int GetIserdesPllLock0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x002C;
         default:
            throw 20;
      };
   };

   // Bit(s) ISERDES_PLL_LOCK_1
   unsigned int GetIserdesPllLock1()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x002C, 0x00000008, 3);
         default:
            throw 20;
      };
   };
   unsigned int GetIserdesPllLock1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000008;
            if(BitOfs) *BitOfs = 3;
            return 0x002C;
         default:
            throw 20;
      };
   };

   // Bit(s) LEAD_TRAIL_EDGE_SEL
   unsigned int GetLeadTrailEdgeSel()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1180, 0x00010000, 16);
         case 9:
            return BitExtractControl(0x1124, 0x00010000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetLeadTrailEdgeSel(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1180, 0x00010000, 16, value);
         case 9:
            return SetRegMask(0x1124, 0x00010000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLeadTrailEdgeSelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x1180;
         case 9:
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x1124;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK0_CLKOUT_DIV
   unsigned int GetLmk0ClkoutDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10DC, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk0ClkoutDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10DC, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk0ClkoutDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x10DC;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK0_CLKOUT_DLY
   unsigned int GetLmk0ClkoutDly()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10DC, 0x000000F0, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk0ClkoutDly(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10DC, 0x000000F0, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk0ClkoutDlyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x10DC;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK0_CLKOUT_EN
   unsigned int GetLmk0ClkoutEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10DC, 0x00010000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk0ClkoutEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10DC, 0x00010000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk0ClkoutEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x10DC;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK0_CLKOUT_MUX
   unsigned int GetLmk0ClkoutMux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10DC, 0x00060000, 17);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk0ClkoutMux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10DC, 0x00060000, 17, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk0ClkoutMuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00060000;
            if(BitOfs) *BitOfs = 17;
            return 0x10DC;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK0_RESET
   unsigned int GetLmk0Reset()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10DC, 0x80000000, 31);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk0Reset(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10DC, 0x80000000, 31, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk0ResetLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x80000000;
            if(BitOfs) *BitOfs = 31;
            return 0x10DC;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK11_DIV4
   unsigned int GetLmk11Div4()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1104, 0x00008000, 15);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk11Div4(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1104, 0x00008000, 15, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk11Div4Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00008000;
            if(BitOfs) *BitOfs = 15;
            return 0x1104;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK13_OSCIN_FREQ
   unsigned int GetLmk13OscinFreq()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1108, 0x003FC000, 14);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk13OscinFreq(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1108, 0x003FC000, 14, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk13OscinFreqLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x003FC000;
            if(BitOfs) *BitOfs = 14;
            return 0x1108;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK13_VCO_C3_C4_LF
   unsigned int GetLmk13VcoC3C4Lf()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1108, 0x000000F0, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk13VcoC3C4Lf(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1108, 0x000000F0, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk13VcoC3C4LfLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x1108;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK13_VCO_R3_LF
   unsigned int GetLmk13VcoR3Lf()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1108, 0x00000700, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk13VcoR3Lf(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1108, 0x00000700, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk13VcoR3LfLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000700;
            if(BitOfs) *BitOfs = 8;
            return 0x1108;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK13_VCO_R4_LF
   unsigned int GetLmk13VcoR4Lf()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1108, 0x00003800, 11);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk13VcoR4Lf(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1108, 0x00003800, 11, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk13VcoR4LfLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00003800;
            if(BitOfs) *BitOfs = 11;
            return 0x1108;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK14_EN_CLKOUT_GLOBAL
   unsigned int GetLmk14EnClkoutGlobal()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x110C, 0x08000000, 27);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk14EnClkoutGlobal(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x110C, 0x08000000, 27, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk14EnClkoutGlobalLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x08000000;
            if(BitOfs) *BitOfs = 27;
            return 0x110C;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK14_EN_FOUT
   unsigned int GetLmk14EnFout()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x110C, 0x10000000, 28);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk14EnFout(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x110C, 0x10000000, 28, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk14EnFoutLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x10000000;
            if(BitOfs) *BitOfs = 28;
            return 0x110C;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK14_PLL_MUX
   unsigned int GetLmk14PllMux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x110C, 0x00F00000, 20);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk14PllMux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x110C, 0x00F00000, 20, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk14PllMuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00F00000;
            if(BitOfs) *BitOfs = 20;
            return 0x110C;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK14_PLL_R
   unsigned int GetLmk14PllR()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x110C, 0x000FFF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk14PllR(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x110C, 0x000FFF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk14PllRLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000FFF00;
            if(BitOfs) *BitOfs = 8;
            return 0x110C;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK14_POWERDOWN
   unsigned int GetLmk14Powerdown()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x110C, 0x04000000, 26);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk14Powerdown(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x110C, 0x04000000, 26, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk14PowerdownLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x04000000;
            if(BitOfs) *BitOfs = 26;
            return 0x110C;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK15_PLL_CP_GAIN
   unsigned int GetLmk15PllCpGain()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1110, 0xC0000000, 30);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk15PllCpGain(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1110, 0xC0000000, 30, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk15PllCpGainLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xC0000000;
            if(BitOfs) *BitOfs = 30;
            return 0x1110;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK15_PLL_N
   unsigned int GetLmk15PllN()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1110, 0x03FFFF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk15PllN(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1110, 0x03FFFF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk15PllNLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x03FFFF00;
            if(BitOfs) *BitOfs = 8;
            return 0x1110;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK15_VCO_DIV
   unsigned int GetLmk15VcoDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1110, 0x3C000000, 26);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk15VcoDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1110, 0x3C000000, 26, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk15VcoDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x3C000000;
            if(BitOfs) *BitOfs = 26;
            return 0x1110;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK1_CLKOUT_DIV
   unsigned int GetLmk1ClkoutDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10E0, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk1ClkoutDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10E0, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk1ClkoutDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x10E0;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK1_CLKOUT_DLY
   unsigned int GetLmk1ClkoutDly()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10E0, 0x000000F0, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk1ClkoutDly(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10E0, 0x000000F0, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk1ClkoutDlyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x10E0;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK1_CLKOUT_EN
   unsigned int GetLmk1ClkoutEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10E0, 0x00010000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk1ClkoutEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10E0, 0x00010000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk1ClkoutEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x10E0;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK1_CLKOUT_MUX
   unsigned int GetLmk1ClkoutMux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10E0, 0x00060000, 17);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk1ClkoutMux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10E0, 0x00060000, 17, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk1ClkoutMuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00060000;
            if(BitOfs) *BitOfs = 17;
            return 0x10E0;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK2_CLKOUT_DIV
   unsigned int GetLmk2ClkoutDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10E4, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk2ClkoutDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10E4, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk2ClkoutDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x10E4;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK2_CLKOUT_DLY
   unsigned int GetLmk2ClkoutDly()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10E4, 0x000000F0, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk2ClkoutDly(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10E4, 0x000000F0, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk2ClkoutDlyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x10E4;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK2_CLKOUT_EN
   unsigned int GetLmk2ClkoutEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10E4, 0x00010000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk2ClkoutEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10E4, 0x00010000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk2ClkoutEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x10E4;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK2_CLKOUT_MUX
   unsigned int GetLmk2ClkoutMux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10E4, 0x00060000, 17);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk2ClkoutMux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10E4, 0x00060000, 17, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk2ClkoutMuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00060000;
            if(BitOfs) *BitOfs = 17;
            return 0x10E4;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK3_CLKOUT_DIV
   unsigned int GetLmk3ClkoutDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10E8, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk3ClkoutDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10E8, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk3ClkoutDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x10E8;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK3_CLKOUT_DLY
   unsigned int GetLmk3ClkoutDly()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10E8, 0x000000F0, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk3ClkoutDly(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10E8, 0x000000F0, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk3ClkoutDlyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x10E8;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK3_CLKOUT_EN
   unsigned int GetLmk3ClkoutEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10E8, 0x00010000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk3ClkoutEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10E8, 0x00010000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk3ClkoutEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x10E8;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK3_CLKOUT_MUX
   unsigned int GetLmk3ClkoutMux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10E8, 0x00060000, 17);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk3ClkoutMux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10E8, 0x00060000, 17, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk3ClkoutMuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00060000;
            if(BitOfs) *BitOfs = 17;
            return 0x10E8;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK4_CLKOUT_DIV
   unsigned int GetLmk4ClkoutDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10EC, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk4ClkoutDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10EC, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk4ClkoutDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x10EC;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK4_CLKOUT_DLY
   unsigned int GetLmk4ClkoutDly()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10EC, 0x000000F0, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk4ClkoutDly(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10EC, 0x000000F0, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk4ClkoutDlyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x10EC;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK4_CLKOUT_EN
   unsigned int GetLmk4ClkoutEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10EC, 0x00010000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk4ClkoutEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10EC, 0x00010000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk4ClkoutEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x10EC;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK4_CLKOUT_MUX
   unsigned int GetLmk4ClkoutMux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10EC, 0x00060000, 17);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk4ClkoutMux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10EC, 0x00060000, 17, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk4ClkoutMuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00060000;
            if(BitOfs) *BitOfs = 17;
            return 0x10EC;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK5_CLKOUT_DIV
   unsigned int GetLmk5ClkoutDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10F0, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk5ClkoutDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10F0, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk5ClkoutDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x10F0;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK5_CLKOUT_DLY
   unsigned int GetLmk5ClkoutDly()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10F0, 0x000000F0, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk5ClkoutDly(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10F0, 0x000000F0, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk5ClkoutDlyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x10F0;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK5_CLKOUT_EN
   unsigned int GetLmk5ClkoutEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10F0, 0x00010000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk5ClkoutEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10F0, 0x00010000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk5ClkoutEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x10F0;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK5_CLKOUT_MUX
   unsigned int GetLmk5ClkoutMux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10F0, 0x00060000, 17);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk5ClkoutMux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10F0, 0x00060000, 17, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk5ClkoutMuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00060000;
            if(BitOfs) *BitOfs = 17;
            return 0x10F0;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK6_CLKOUT_DIV
   unsigned int GetLmk6ClkoutDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10F4, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk6ClkoutDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10F4, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk6ClkoutDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x10F4;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK6_CLKOUT_DLY
   unsigned int GetLmk6ClkoutDly()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10F4, 0x000000F0, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk6ClkoutDly(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10F4, 0x000000F0, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk6ClkoutDlyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x10F4;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK6_CLKOUT_EN
   unsigned int GetLmk6ClkoutEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10F4, 0x00010000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk6ClkoutEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10F4, 0x00010000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk6ClkoutEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x10F4;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK6_CLKOUT_MUX
   unsigned int GetLmk6ClkoutMux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10F4, 0x00060000, 17);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk6ClkoutMux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10F4, 0x00060000, 17, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk6ClkoutMuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00060000;
            if(BitOfs) *BitOfs = 17;
            return 0x10F4;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK7_CLKOUT_DIV
   unsigned int GetLmk7ClkoutDiv()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10F8, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk7ClkoutDiv(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10F8, 0x0000FF00, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk7ClkoutDivLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x10F8;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK7_CLKOUT_DLY
   unsigned int GetLmk7ClkoutDly()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10F8, 0x000000F0, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk7ClkoutDly(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10F8, 0x000000F0, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk7ClkoutDlyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x10F8;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK7_CLKOUT_EN
   unsigned int GetLmk7ClkoutEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10F8, 0x00010000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk7ClkoutEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10F8, 0x00010000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk7ClkoutEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x10F8;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK7_CLKOUT_MUX
   unsigned int GetLmk7ClkoutMux()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10F8, 0x00060000, 17);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk7ClkoutMux(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10F8, 0x00060000, 17, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk7ClkoutMuxLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00060000;
            if(BitOfs) *BitOfs = 17;
            return 0x10F8;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK8_PHASE_NOISE_OPT
   unsigned int GetLmk8PhaseNoiseOpt()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x10FC, 0xFFFFFFF0, 4);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk8PhaseNoiseOpt(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x10FC, 0xFFFFFFF0, 4, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk8PhaseNoiseOptLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFF0;
            if(BitOfs) *BitOfs = 4;
            return 0x10FC;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK9_VBOOST
   unsigned int GetLmk9Vboost()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1100, 0x00010000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetLmk9Vboost(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1100, 0x00010000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk9VboostLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00010000;
            if(BitOfs) *BitOfs = 16;
            return 0x1100;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK_0_MOD
   unsigned int GetLmk0Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0160, 0xF0000000, 28);
         case 9:
            return BitExtractStatus(0x015C, 0xF0000000, 28);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk0ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xF0000000;
            if(BitOfs) *BitOfs = 28;
            return 0x0160;
         case 9:
            if(BitMask) *BitMask = 0xF0000000;
            if(BitOfs) *BitOfs = 28;
            return 0x015C;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK_11_MOD
   unsigned int GetLmk11Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0164, 0x0000F000, 12);
         case 9:
            return BitExtractStatus(0x0160, 0x0000F000, 12);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk11ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000F000;
            if(BitOfs) *BitOfs = 12;
            return 0x0164;
         case 9:
            if(BitMask) *BitMask = 0x0000F000;
            if(BitOfs) *BitOfs = 12;
            return 0x0160;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK_13_MOD
   unsigned int GetLmk13Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0164, 0x00000F00, 8);
         case 9:
            return BitExtractStatus(0x0160, 0x00000F00, 8);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk13ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000F00;
            if(BitOfs) *BitOfs = 8;
            return 0x0164;
         case 9:
            if(BitMask) *BitMask = 0x00000F00;
            if(BitOfs) *BitOfs = 8;
            return 0x0160;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK_14_MOD
   unsigned int GetLmk14Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0164, 0x000000F0, 4);
         case 9:
            return BitExtractStatus(0x0160, 0x000000F0, 4);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk14ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x0164;
         case 9:
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x0160;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK_15_MOD
   unsigned int GetLmk15Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0164, 0x0000000F, 0);
         case 9:
            return BitExtractStatus(0x0160, 0x0000000F, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk15ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0164;
         case 9:
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0160;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK_1_MOD
   unsigned int GetLmk1Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0160, 0x0F000000, 24);
         case 9:
            return BitExtractStatus(0x015C, 0x0F000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk1ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0F000000;
            if(BitOfs) *BitOfs = 24;
            return 0x0160;
         case 9:
            if(BitMask) *BitMask = 0x0F000000;
            if(BitOfs) *BitOfs = 24;
            return 0x015C;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK_2_MOD
   unsigned int GetLmk2Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0160, 0x00F00000, 20);
         case 9:
            return BitExtractStatus(0x015C, 0x00F00000, 20);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk2ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00F00000;
            if(BitOfs) *BitOfs = 20;
            return 0x0160;
         case 9:
            if(BitMask) *BitMask = 0x00F00000;
            if(BitOfs) *BitOfs = 20;
            return 0x015C;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK_3_MOD
   unsigned int GetLmk3Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0160, 0x000F0000, 16);
         case 9:
            return BitExtractStatus(0x015C, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk3ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0160;
         case 9:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x015C;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK_4_MOD
   unsigned int GetLmk4Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0160, 0x0000F000, 12);
         case 9:
            return BitExtractStatus(0x015C, 0x0000F000, 12);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk4ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000F000;
            if(BitOfs) *BitOfs = 12;
            return 0x0160;
         case 9:
            if(BitMask) *BitMask = 0x0000F000;
            if(BitOfs) *BitOfs = 12;
            return 0x015C;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK_5_MOD
   unsigned int GetLmk5Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0160, 0x00000F00, 8);
         case 9:
            return BitExtractStatus(0x015C, 0x00000F00, 8);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk5ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000F00;
            if(BitOfs) *BitOfs = 8;
            return 0x0160;
         case 9:
            if(BitMask) *BitMask = 0x00000F00;
            if(BitOfs) *BitOfs = 8;
            return 0x015C;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK_6_MOD
   unsigned int GetLmk6Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0160, 0x000000F0, 4);
         case 9:
            return BitExtractStatus(0x015C, 0x000000F0, 4);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk6ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x0160;
         case 9:
            if(BitMask) *BitMask = 0x000000F0;
            if(BitOfs) *BitOfs = 4;
            return 0x015C;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK_7_MOD
   unsigned int GetLmk7Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0160, 0x0000000F, 0);
         case 9:
            return BitExtractStatus(0x015C, 0x0000000F, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk7ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x0160;
         case 9:
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x015C;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK_8_MOD
   unsigned int GetLmk8Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0164, 0x00F00000, 20);
         case 9:
            return BitExtractStatus(0x0160, 0x00F00000, 20);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk8ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00F00000;
            if(BitOfs) *BitOfs = 20;
            return 0x0164;
         case 9:
            if(BitMask) *BitMask = 0x00F00000;
            if(BitOfs) *BitOfs = 20;
            return 0x0160;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK_9_MOD
   unsigned int GetLmk9Mod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0164, 0x000F0000, 16);
         case 9:
            return BitExtractStatus(0x0160, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int GetLmk9ModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0164;
         case 9:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0160;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK_PLL_LOCK
   unsigned int GetLmkPllLock()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x002C, 0x00000001, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetLmkPllLockLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x002C;
         default:
            throw 20;
      };
   };

   // Bit(s) LMK_SYNC_LOCAL
   unsigned int GetLmkSyncLocal()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1040, 0x00000080, 7);
         default:
            throw 20;
      };
   };
   unsigned int SetLmkSyncLocal(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1040, 0x00000080, 7, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLmkSyncLocalLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x1040;
         default:
            throw 20;
      };
   };

   // Bit(s) LOCAL_CLK_FREQ
   unsigned int GetLocalClkFreq()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x100C, 0x000000FF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetLocalClkFreq(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x100C, 0x000000FF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetLocalClkFreqLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x100C;
         default:
            throw 20;
      };
   };

   // Bit(s) LOCAL_CLK_FREQ_MOD
   unsigned int GetLocalClkFreqMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0138, 0x00000001, 0);
         case 9:
            return BitExtractStatus(0x0134, 0x00000001, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetLocalClkFreqModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x0138;
         case 9:
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x0134;
         default:
            throw 20;
      };
   };

   // Bit(s) MAX_DRS_ADC_PKT_SAMPLES
   unsigned int GetMaxDrsAdcPktSamples()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0128, 0x0000FFFF, 0);
         case 9:
            return BitExtractStatus(0x0124, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetMaxDrsAdcPktSamplesLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0128;
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0124;
         default:
            throw 20;
      };
   };

   // Bit(s) MAX_SCL_PKT_SAMPLES
   unsigned int GetMaxSclPktSamples()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0134, 0x0000FFFF, 0);
         case 9:
            return BitExtractStatus(0x0130, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetMaxSclPktSamplesLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0134;
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0130;
         default:
            throw 20;
      };
   };

   // Bit(s) MAX_TDC_PKT_SAMPLES
   unsigned int GetMaxTdcPktSamples()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x012C, 0x0003FFFF, 0);
         case 9:
            return BitExtractStatus(0x0128, 0x0003FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetMaxTdcPktSamplesLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0003FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x012C;
         case 9:
            if(BitMask) *BitMask = 0x0003FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0128;
         default:
            throw 20;
      };
   };

   // Bit(s) MAX_TRG_PKT_SAMPLES
   unsigned int GetMaxTrgPktSamples()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0130, 0x0000FFFF, 0);
         case 9:
            return BitExtractStatus(0x012C, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetMaxTrgPktSamplesLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0130;
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x012C;
         default:
            throw 20;
      };
   };

   // Bit(s) MCX_RX_SIG_SEL
   unsigned int GetMcxRxSigSel()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1280, 0x0000000F, 0);
         case 9:
            return BitExtractControl(0x1224, 0x0000000F, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetMcxRxSigSel(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1280, 0x0000000F, 0, value);
         case 9:
            return SetRegMask(0x1224, 0x0000000F, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetMcxRxSigSelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x1280;
         case 9:
            if(BitMask) *BitMask = 0x0000000F;
            if(BitOfs) *BitOfs = 0;
            return 0x1224;
         default:
            throw 20;
      };
   };

   // Bit(s) MCX_TX_SIG_SEL
   unsigned int GetMcxTxSigSel()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1280, 0x000F0000, 16);
         case 9:
            return BitExtractControl(0x1224, 0x000F0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int SetMcxTxSigSel(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1280, 0x000F0000, 16, value);
         case 9:
            return SetRegMask(0x1224, 0x000F0000, 16, value);
         default:
            throw 20;
      };
   };
   unsigned int GetMcxTxSigSelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1280;
         case 9:
            if(BitMask) *BitMask = 0x000F0000;
            if(BitOfs) *BitOfs = 16;
            return 0x1224;
         default:
            throw 20;
      };
   };

   // Bit(s) OSERDES_PLL_LOCK_DCB
   unsigned int GetOserdesPllLockDcb()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x002C, 0x00000040, 6);
         default:
            throw 20;
      };
   };
   unsigned int GetOserdesPllLockDcbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x002C;
         default:
            throw 20;
      };
   };

   // Bit(s) OSERDES_PLL_LOCK_TCB
   unsigned int GetOserdesPllLockTcb()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x002C, 0x00000020, 5);
         default:
            throw 20;
      };
   };
   unsigned int GetOserdesPllLockTcbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000020;
            if(BitOfs) *BitOfs = 5;
            return 0x002C;
         default:
            throw 20;
      };
   };

   // Bit(s) OVERTEMP
   unsigned int GetOvertemp()
   {
      switch(this->mVersion)
      {
         case 9:
            return BitExtractStatus(0x0028, 0x00008000, 15);
         default:
            throw 20;
      };
   };
   unsigned int GetOvertempLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 9:
            if(BitMask) *BitMask = 0x00008000;
            if(BitOfs) *BitOfs = 15;
            return 0x0028;
         default:
            throw 20;
      };
   };

   // Bit(s) PACKAGER_BUSY
   unsigned int GetPackagerBusy()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0028, 0x00000040, 6);
         default:
            throw 20;
      };
   };
   unsigned int GetPackagerBusyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000040;
            if(BitOfs) *BitOfs = 6;
            return 0x0028;
         default:
            throw 20;
      };
   };

   // Bit(s) PATTERN_TRIGGER_EN
   unsigned int GetPatternTriggerEn()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1180, 0x00001000, 12);
         case 9:
            return BitExtractControl(0x1124, 0x00001000, 12);
         default:
            throw 20;
      };
   };
   unsigned int SetPatternTriggerEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1180, 0x00001000, 12, value);
         case 9:
            return SetRegMask(0x1124, 0x00001000, 12, value);
         default:
            throw 20;
      };
   };
   unsigned int GetPatternTriggerEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00001000;
            if(BitOfs) *BitOfs = 12;
            return 0x1180;
         case 9:
            if(BitMask) *BitMask = 0x00001000;
            if(BitOfs) *BitOfs = 12;
            return 0x1124;
         default:
            throw 20;
      };
   };

   // Bit(s) PROTOCOL_VERSION
   unsigned int GetProtocolVersion()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0020, 0x000000FF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetProtocolVersionLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x0020;
         default:
            throw 20;
      };
   };

   // Bit(s) RECONFIGURE_FPGA
   unsigned int GetReconfigureFpga()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1040, 0x00000001, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetReconfigureFpga(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1040, 0x00000001, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetReconfigureFpgaLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x1040;
         default:
            throw 20;
      };
   };

   // Bit(s) REG_LAYOUT_COMP_LEVEL
   unsigned int GetRegLayoutCompLevel()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0004, 0xFFFF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int GetRegLayoutCompLevelLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0004;
         default:
            throw 20;
      };
   };

   // Bit(s) REG_LAYOUT_VERSION
   unsigned int GetRegLayoutVersion()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0004, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetRegLayoutVersionLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0004;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_0
   unsigned int GetScaler0()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00A0, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x009C, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScaler0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00A0;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x009C;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_1
   unsigned int GetScaler1()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00A4, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00A0, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScaler1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00A4;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00A0;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_10
   unsigned int GetScaler10()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00C8, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00C4, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScaler10Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00C8;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00C4;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_11
   unsigned int GetScaler11()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00CC, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00C8, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScaler11Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00CC;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00C8;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_12
   unsigned int GetScaler12()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00D0, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00CC, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScaler12Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00D0;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00CC;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_13
   unsigned int GetScaler13()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00D4, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00D0, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScaler13Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00D4;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00D0;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_14
   unsigned int GetScaler14()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00D8, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00D4, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScaler14Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00D8;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00D4;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_15
   unsigned int GetScaler15()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00DC, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00D8, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScaler15Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00DC;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00D8;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_2
   unsigned int GetScaler2()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00A8, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00A4, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScaler2Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00A8;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00A4;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_3
   unsigned int GetScaler3()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00AC, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00A8, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScaler3Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00AC;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00A8;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_4
   unsigned int GetScaler4()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00B0, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00AC, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScaler4Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00B0;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00AC;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_5
   unsigned int GetScaler5()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00B4, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00B0, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScaler5Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00B4;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00B0;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_6
   unsigned int GetScaler6()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00B8, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00B4, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScaler6Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00B8;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00B4;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_7
   unsigned int GetScaler7()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00BC, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00B8, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScaler7Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00BC;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00B8;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_8
   unsigned int GetScaler8()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00C0, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00BC, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScaler8Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00C0;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00BC;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_9
   unsigned int GetScaler9()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00C4, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00C0, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScaler9Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00C4;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00C0;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_EXT_CLK
   unsigned int GetScalerExtClk()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00E8, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00E4, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScalerExtClkLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00E8;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00E4;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_EXT_TRG
   unsigned int GetScalerExtTrg()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00E4, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00E0, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScalerExtTrgLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00E4;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00E0;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_PTRN_TRG
   unsigned int GetScalerPtrnTrg()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00E0, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00DC, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScalerPtrnTrgLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00E0;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00DC;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_RST
   unsigned int GetScalerRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1040, 0x00000200, 9);
         default:
            throw 20;
      };
   };
   unsigned int SetScalerRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1040, 0x00000200, 9, value);
         default:
            throw 20;
      };
   };
   unsigned int GetScalerRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000200;
            if(BitOfs) *BitOfs = 9;
            return 0x1040;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_TIME_STAMP_LSB
   unsigned int GetScalerTimeStampLsb()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00EC, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00E8, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScalerTimeStampLsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00EC;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00E8;
         default:
            throw 20;
      };
   };

   // Bit(s) SCALER_TIME_STAMP_MSB
   unsigned int GetScalerTimeStampMsb()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00F0, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00EC, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetScalerTimeStampMsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00F0;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00EC;
         default:
            throw 20;
      };
   };

   // Bit(s) SCL_TX_EN
   unsigned int GetSclTxEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1014, 0x04000000, 26);
         default:
            throw 20;
      };
   };
   unsigned int SetSclTxEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1014, 0x04000000, 26, value);
         default:
            throw 20;
      };
   };
   unsigned int GetSclTxEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x04000000;
            if(BitOfs) *BitOfs = 26;
            return 0x1014;
         default:
            throw 20;
      };
   };

   // Bit(s) SERDES_COM_EN
   unsigned int GetSerdesComEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1014, 0x02000000, 25);
         default:
            throw 20;
      };
   };
   unsigned int SetSerdesComEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1014, 0x02000000, 25, value);
         default:
            throw 20;
      };
   };
   unsigned int GetSerdesComEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x02000000;
            if(BitOfs) *BitOfs = 25;
            return 0x1014;
         default:
            throw 20;
      };
   };

   // Bit(s) SERIAL_BUSY
   unsigned int GetSerialBusy()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0028, 0x00000080, 7);
         default:
            throw 20;
      };
   };
   unsigned int GetSerialBusyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000080;
            if(BitOfs) *BitOfs = 7;
            return 0x0028;
         default:
            throw 20;
      };
   };

   // Bit(s) SERIAL_NUMBER
   unsigned int GetSerialNumber()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0024, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetSerialNumberLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0024;
         default:
            throw 20;
      };
   };

   // Bit(s) SET_TIME_LSB
   unsigned int GetSetTimeLsb()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1278, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x121C, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetSetTimeLsb(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1278, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x121C, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetSetTimeLsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1278;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x121C;
         default:
            throw 20;
      };
   };

   // Bit(s) SET_TIME_MSB
   unsigned int GetSetTimeMsb()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x127C, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractControl(0x1220, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetSetTimeMsb(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x127C, 0xFFFFFFFF, 0, value);
         case 9:
            return SetRegMask(0x1220, 0xFFFFFFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetSetTimeMsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x127C;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1220;
         default:
            throw 20;
      };
   };

   // Bit(s) SLOT_ID
   unsigned int GetSlotId()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1000, 0x000000FF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetSlotId(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1000, 0x000000FF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetSlotIdLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x1000;
         default:
            throw 20;
      };
   };

   // Bit(s) SW_BUILD_DAY
   unsigned int GetSwBuildDay()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0010, 0x000000FF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetSwBuildDayLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x0010;
         default:
            throw 20;
      };
   };

   // Bit(s) SW_BUILD_HOUR
   unsigned int GetSwBuildHour()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0014, 0x00FF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int GetSwBuildHourLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00FF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0014;
         default:
            throw 20;
      };
   };

   // Bit(s) SW_BUILD_MINUTE
   unsigned int GetSwBuildMinute()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0014, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int GetSwBuildMinuteLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x0014;
         default:
            throw 20;
      };
   };

   // Bit(s) SW_BUILD_MONTH
   unsigned int GetSwBuildMonth()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0010, 0x0000FF00, 8);
         default:
            throw 20;
      };
   };
   unsigned int GetSwBuildMonthLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FF00;
            if(BitOfs) *BitOfs = 8;
            return 0x0010;
         default:
            throw 20;
      };
   };

   // Bit(s) SW_BUILD_SECOND
   unsigned int GetSwBuildSecond()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0014, 0x000000FF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetSwBuildSecondLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x0014;
         default:
            throw 20;
      };
   };

   // Bit(s) SW_BUILD_YEAR
   unsigned int GetSwBuildYear()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0010, 0xFFFF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int GetSwBuildYearLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0010;
         default:
            throw 20;
      };
   };

   // Bit(s) SW_GIT_HASH_TAG
   unsigned int GetSwGitHashTag()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x001C, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetSwGitHashTagLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x001C;
         default:
            throw 20;
      };
   };

   // Bit(s) SYS_BUSY
   unsigned int GetSysBusy()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0028, 0x00000010, 4);
         default:
            throw 20;
      };
   };
   unsigned int GetSysBusyLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x0028;
         default:
            throw 20;
      };
   };

   // Bit(s) SYS_DCM_LOCK
   unsigned int GetSysDcmLock()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x002C, 0x00000100, 8);
         default:
            throw 20;
      };
   };
   unsigned int GetSysDcmLockLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x002C;
         default:
            throw 20;
      };
   };

   // Bit(s) TCB_OSERDES_IF_RST
   unsigned int GetTcbOserdesIfRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1040, 0x00000400, 10);
         default:
            throw 20;
      };
   };
   unsigned int SetTcbOserdesIfRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1040, 0x00000400, 10, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTcbOserdesIfRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000400;
            if(BitOfs) *BitOfs = 10;
            return 0x1040;
         default:
            throw 20;
      };
   };

   // Bit(s) TCB_OSERDES_PLL_RST
   unsigned int GetTcbOserdesPllRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1040, 0x00001000, 12);
         default:
            throw 20;
      };
   };
   unsigned int SetTcbOserdesPllRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1040, 0x00001000, 12, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTcbOserdesPllRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00001000;
            if(BitOfs) *BitOfs = 12;
            return 0x1040;
         default:
            throw 20;
      };
   };

   // Bit(s) TCB_SERDES_TRAIN
   unsigned int GetTcbSerdesTrain()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1014, 0x40000000, 30);
         default:
            throw 20;
      };
   };
   unsigned int SetTcbSerdesTrain(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1014, 0x40000000, 30, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTcbSerdesTrainLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x40000000;
            if(BitOfs) *BitOfs = 30;
            return 0x1014;
         default:
            throw 20;
      };
   };

   // Bit(s) TDC_CH_TX_EN
   unsigned int GetTdcChTxEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1024, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTdcChTxEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1024, 0x0000FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTdcChTxEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1024;
         default:
            throw 20;
      };
   };

   // Bit(s) TDC_SAMPLE_FREQ
   unsigned int GetTdcSampleFreq()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0040, 0x00FFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetTdcSampleFreqLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00FFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0040;
         default:
            throw 20;
      };
   };

   // Bit(s) TDC_TX_SAMPLES
   unsigned int GetTdcTxSamples()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1030, 0x00001FFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTdcTxSamples(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1030, 0x00001FFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTdcTxSamplesLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00001FFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1030;
         default:
            throw 20;
      };
   };

   // Bit(s) TEMPERATURE
   unsigned int GetTemperature()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0028, 0xFFFF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int GetTemperatureLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0xFFFF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0028;
         default:
            throw 20;
      };
   };

   // Bit(s) TIME_LSB
   unsigned int GetTimeLsb()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00F4, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00F0, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetTimeLsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00F4;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00F0;
         default:
            throw 20;
      };
   };

   // Bit(s) TIME_MSB
   unsigned int GetTimeMsb()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x00F8, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x00F4, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetTimeMsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00F8;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x00F4;
         default:
            throw 20;
      };
   };

   // Bit(s) TIMING_CALIB_SIGNAL_EN
   unsigned int GetTimingCalibSignalEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1008, 0x00000001, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTimingCalibSignalEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1008, 0x00000001, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTimingCalibSignalEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000001;
            if(BitOfs) *BitOfs = 0;
            return 0x1008;
         default:
            throw 20;
      };
   };

   // Bit(s) TRB_FLAG_NEW
   unsigned int GetTrbFlagNew()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0108, 0x80000000, 31);
         case 9:
            return BitExtractStatus(0x0104, 0x80000000, 31);
         default:
            throw 20;
      };
   };
   unsigned int GetTrbFlagNewLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x80000000;
            if(BitOfs) *BitOfs = 31;
            return 0x0108;
         case 9:
            if(BitMask) *BitMask = 0x80000000;
            if(BitOfs) *BitOfs = 31;
            return 0x0104;
         default:
            throw 20;
      };
   };

   // Bit(s) TRB_FLAG_PARITY_ERROR
   unsigned int GetTrbFlagParityError()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0108, 0x40000000, 30);
         case 9:
            return BitExtractStatus(0x0104, 0x40000000, 30);
         default:
            throw 20;
      };
   };
   unsigned int GetTrbFlagParityErrorLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x40000000;
            if(BitOfs) *BitOfs = 30;
            return 0x0108;
         case 9:
            if(BitMask) *BitMask = 0x40000000;
            if(BitOfs) *BitOfs = 30;
            return 0x0104;
         default:
            throw 20;
      };
   };

   // Bit(s) TRB_INFO_LSB
   unsigned int GetTrbInfoLsb()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x010C, 0xFFFFFFFF, 0);
         case 9:
            return BitExtractStatus(0x0108, 0xFFFFFFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetTrbInfoLsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x010C;
         case 9:
            if(BitMask) *BitMask = 0xFFFFFFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0108;
         default:
            throw 20;
      };
   };

   // Bit(s) TRB_INFO_MSB
   unsigned int GetTrbInfoMsb()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0110, 0x0000FFFF, 0);
         case 9:
            return BitExtractStatus(0x010C, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetTrbInfoMsbLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0110;
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x010C;
         default:
            throw 20;
      };
   };

   // Bit(s) TRB_PARITY_ERROR_COUNT
   unsigned int GetTrbParityErrorCount()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0108, 0x0000FFFF, 0);
         case 9:
            return BitExtractStatus(0x0104, 0x0000FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int GetTrbParityErrorCountLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0108;
         case 9:
            if(BitMask) *BitMask = 0x0000FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x0104;
         default:
            throw 20;
      };
   };

   // Bit(s) TRB_PARITY_ERROR_COUNT_RST
   unsigned int GetTrbParityErrorCountRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1040, 0x00000100, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetTrbParityErrorCountRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1040, 0x00000100, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrbParityErrorCountRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x1040;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_PTRN_EN
   unsigned int GetTrgPtrnEn()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x118C, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1130, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgPtrnEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x118C, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1130, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgPtrnEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x118C;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1130;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN0
   unsigned int GetTrgSrcEnPtrn0()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1190, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1134, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgSrcEnPtrn0(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1190, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1134, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgSrcEnPtrn0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1190;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1134;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN1
   unsigned int GetTrgSrcEnPtrn1()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1198, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x113C, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgSrcEnPtrn1(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1198, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x113C, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgSrcEnPtrn1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1198;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x113C;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN10
   unsigned int GetTrgSrcEnPtrn10()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11E0, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1184, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgSrcEnPtrn10(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11E0, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1184, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgSrcEnPtrn10Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11E0;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1184;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN11
   unsigned int GetTrgSrcEnPtrn11()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11E8, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x118C, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgSrcEnPtrn11(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11E8, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x118C, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgSrcEnPtrn11Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11E8;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x118C;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN12
   unsigned int GetTrgSrcEnPtrn12()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11F0, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1194, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgSrcEnPtrn12(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11F0, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1194, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgSrcEnPtrn12Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11F0;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1194;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN13
   unsigned int GetTrgSrcEnPtrn13()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11F8, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x119C, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgSrcEnPtrn13(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11F8, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x119C, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgSrcEnPtrn13Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11F8;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x119C;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN14
   unsigned int GetTrgSrcEnPtrn14()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1200, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x11A4, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgSrcEnPtrn14(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1200, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x11A4, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgSrcEnPtrn14Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1200;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11A4;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN15
   unsigned int GetTrgSrcEnPtrn15()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1208, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x11AC, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgSrcEnPtrn15(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1208, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x11AC, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgSrcEnPtrn15Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1208;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11AC;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN16
   unsigned int GetTrgSrcEnPtrn16()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1210, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x11B4, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgSrcEnPtrn16(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1210, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x11B4, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgSrcEnPtrn16Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1210;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11B4;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN17
   unsigned int GetTrgSrcEnPtrn17()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1218, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x11BC, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgSrcEnPtrn17(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1218, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x11BC, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgSrcEnPtrn17Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1218;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11BC;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN18
   unsigned int GetTrgSrcEnPtrn18()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1220, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x11C4, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgSrcEnPtrn18(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1220, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x11C4, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgSrcEnPtrn18Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1220;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11C4;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN2
   unsigned int GetTrgSrcEnPtrn2()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11A0, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1144, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgSrcEnPtrn2(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11A0, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1144, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgSrcEnPtrn2Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11A0;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1144;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN3
   unsigned int GetTrgSrcEnPtrn3()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11A8, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x114C, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgSrcEnPtrn3(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11A8, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x114C, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgSrcEnPtrn3Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11A8;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x114C;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN4
   unsigned int GetTrgSrcEnPtrn4()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11B0, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1154, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgSrcEnPtrn4(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11B0, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1154, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgSrcEnPtrn4Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11B0;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1154;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN5
   unsigned int GetTrgSrcEnPtrn5()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11B8, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x115C, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgSrcEnPtrn5(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11B8, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x115C, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgSrcEnPtrn5Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11B8;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x115C;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN6
   unsigned int GetTrgSrcEnPtrn6()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11C0, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1164, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgSrcEnPtrn6(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11C0, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1164, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgSrcEnPtrn6Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11C0;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1164;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN7
   unsigned int GetTrgSrcEnPtrn7()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11C8, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x116C, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgSrcEnPtrn7(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11C8, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x116C, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgSrcEnPtrn7Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11C8;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x116C;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN8
   unsigned int GetTrgSrcEnPtrn8()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11D0, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1174, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgSrcEnPtrn8(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11D0, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1174, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgSrcEnPtrn8Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11D0;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1174;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_SRC_EN_PTRN9
   unsigned int GetTrgSrcEnPtrn9()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11D8, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x117C, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgSrcEnPtrn9(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11D8, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x117C, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgSrcEnPtrn9Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11D8;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x117C;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_SRC_POLARITY
   unsigned int GetTrgSrcPolarity()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1184, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1128, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgSrcPolarity(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1184, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1128, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgSrcPolarityLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1184;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1128;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_STATE_PTRN0
   unsigned int GetTrgStatePtrn0()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1194, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1138, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgStatePtrn0(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1194, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1138, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgStatePtrn0Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1194;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1138;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_STATE_PTRN1
   unsigned int GetTrgStatePtrn1()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x119C, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1140, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgStatePtrn1(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x119C, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1140, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgStatePtrn1Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x119C;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1140;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_STATE_PTRN10
   unsigned int GetTrgStatePtrn10()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11E4, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1188, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgStatePtrn10(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11E4, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1188, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgStatePtrn10Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11E4;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1188;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_STATE_PTRN11
   unsigned int GetTrgStatePtrn11()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11EC, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1190, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgStatePtrn11(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11EC, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1190, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgStatePtrn11Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11EC;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1190;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_STATE_PTRN12
   unsigned int GetTrgStatePtrn12()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11F4, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1198, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgStatePtrn12(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11F4, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1198, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgStatePtrn12Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11F4;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1198;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_STATE_PTRN13
   unsigned int GetTrgStatePtrn13()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11FC, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x11A0, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgStatePtrn13(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11FC, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x11A0, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgStatePtrn13Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11FC;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11A0;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_STATE_PTRN14
   unsigned int GetTrgStatePtrn14()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1204, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x11A8, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgStatePtrn14(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1204, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x11A8, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgStatePtrn14Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1204;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11A8;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_STATE_PTRN15
   unsigned int GetTrgStatePtrn15()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x120C, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x11B0, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgStatePtrn15(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x120C, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x11B0, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgStatePtrn15Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x120C;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11B0;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_STATE_PTRN16
   unsigned int GetTrgStatePtrn16()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1214, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x11B8, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgStatePtrn16(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1214, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x11B8, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgStatePtrn16Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1214;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11B8;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_STATE_PTRN17
   unsigned int GetTrgStatePtrn17()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x121C, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x11C0, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgStatePtrn17(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x121C, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x11C0, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgStatePtrn17Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x121C;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11C0;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_STATE_PTRN18
   unsigned int GetTrgStatePtrn18()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1224, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x11C8, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgStatePtrn18(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1224, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x11C8, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgStatePtrn18Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1224;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11C8;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_STATE_PTRN2
   unsigned int GetTrgStatePtrn2()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11A4, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1148, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgStatePtrn2(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11A4, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1148, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgStatePtrn2Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11A4;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1148;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_STATE_PTRN3
   unsigned int GetTrgStatePtrn3()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11AC, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1150, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgStatePtrn3(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11AC, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1150, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgStatePtrn3Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11AC;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1150;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_STATE_PTRN4
   unsigned int GetTrgStatePtrn4()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11B4, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1158, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgStatePtrn4(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11B4, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1158, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgStatePtrn4Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11B4;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1158;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_STATE_PTRN5
   unsigned int GetTrgStatePtrn5()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11BC, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1160, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgStatePtrn5(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11BC, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1160, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgStatePtrn5Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11BC;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1160;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_STATE_PTRN6
   unsigned int GetTrgStatePtrn6()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11C4, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1168, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgStatePtrn6(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11C4, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1168, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgStatePtrn6Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11C4;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1168;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_STATE_PTRN7
   unsigned int GetTrgStatePtrn7()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11CC, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1170, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgStatePtrn7(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11CC, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1170, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgStatePtrn7Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11CC;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1170;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_STATE_PTRN8
   unsigned int GetTrgStatePtrn8()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11D4, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1178, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgStatePtrn8(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11D4, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1178, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgStatePtrn8Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11D4;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1178;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_STATE_PTRN9
   unsigned int GetTrgStatePtrn9()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x11DC, 0x0007FFFF, 0);
         case 9:
            return BitExtractControl(0x1180, 0x0007FFFF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgStatePtrn9(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x11DC, 0x0007FFFF, 0, value);
         case 9:
            return SetRegMask(0x1180, 0x0007FFFF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgStatePtrn9Loc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x11DC;
         case 9:
            if(BitMask) *BitMask = 0x0007FFFF;
            if(BitOfs) *BitOfs = 0;
            return 0x1180;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_TX_EN
   unsigned int GetTrgTxEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1014, 0x08000000, 27);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgTxEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1014, 0x08000000, 27, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgTxEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x08000000;
            if(BitOfs) *BitOfs = 27;
            return 0x1014;
         default:
            throw 20;
      };
   };

   // Bit(s) TRG_TX_SAMPLES
   unsigned int GetTrgTxSamples()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1034, 0x000003FF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTrgTxSamples(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1034, 0x000003FF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrgTxSamplesLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000003FF;
            if(BitOfs) *BitOfs = 0;
            return 0x1034;
         default:
            throw 20;
      };
   };

   // Bit(s) TRIGGER_DAQ_CLK_CAL_MOD
   unsigned int GetTriggerDaqClkCalMod()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractStatus(0x0138, 0x00000010, 4);
         case 9:
            return BitExtractStatus(0x0134, 0x00000010, 4);
         default:
            throw 20;
      };
   };
   unsigned int GetTriggerDaqClkCalModLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x0138;
         case 9:
            if(BitMask) *BitMask = 0x00000010;
            if(BitOfs) *BitOfs = 4;
            return 0x0134;
         default:
            throw 20;
      };
   };

   // Bit(s) TRIGGER_DELAY
   unsigned int GetTriggerDelay()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1180, 0x000000FF, 0);
         case 9:
            return BitExtractControl(0x1124, 0x000000FF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetTriggerDelay(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1180, 0x000000FF, 0, value);
         case 9:
            return SetRegMask(0x1124, 0x000000FF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTriggerDelayLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x1180;
         case 9:
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x1124;
         default:
            throw 20;
      };
   };

   // Bit(s) TRIGGER_OUT_PULSE_LENGTH
   unsigned int GetTriggerOutPulseLength()
   {
      switch(this->mVersion)
      {
         case 8:
            return BitExtractControl(0x1180, 0x00000700, 8);
         case 9:
            return BitExtractControl(0x1124, 0x00000700, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetTriggerOutPulseLength(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
            return SetRegMask(0x1180, 0x00000700, 8, value);
         case 9:
            return SetRegMask(0x1124, 0x00000700, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTriggerOutPulseLengthLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
            if(BitMask) *BitMask = 0x00000700;
            if(BitOfs) *BitOfs = 8;
            return 0x1180;
         case 9:
            if(BitMask) *BitMask = 0x00000700;
            if(BitOfs) *BitOfs = 8;
            return 0x1124;
         default:
            throw 20;
      };
   };

   // Bit(s) TRIG_DAQ_CLK_CAL_CHK
   unsigned int GetTrigDaqClkCalChk()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x100C, 0x01000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int SetTrigDaqClkCalChk(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x100C, 0x01000000, 24, value);
         default:
            throw 20;
      };
   };
   unsigned int GetTrigDaqClkCalChkLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x01000000;
            if(BitOfs) *BitOfs = 24;
            return 0x100C;
         default:
            throw 20;
      };
   };

   // Bit(s) VALID_DELAY_ADC
   unsigned int GetValidDelayAdc()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1004, 0x3F000000, 24);
         default:
            throw 20;
      };
   };
   unsigned int SetValidDelayAdc(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1004, 0x3F000000, 24, value);
         default:
            throw 20;
      };
   };
   unsigned int GetValidDelayAdcLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x3F000000;
            if(BitOfs) *BitOfs = 24;
            return 0x1004;
         default:
            throw 20;
      };
   };

   // Bit(s) VENDOR_ID
   unsigned int GetVendorId()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractStatus(0x0000, 0x00FF0000, 16);
         default:
            throw 20;
      };
   };
   unsigned int GetVendorIdLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00FF0000;
            if(BitOfs) *BitOfs = 16;
            return 0x0000;
         default:
            throw 20;
      };
   };

   // Bit(s) WD_PKGR_RST
   unsigned int GetWdPkgrRst()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x1040, 0x00000008, 3);
         default:
            throw 20;
      };
   };
   unsigned int SetWdPkgrRst(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x1040, 0x00000008, 3, value);
         default:
            throw 20;
      };
   };
   unsigned int GetWdPkgrRstLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000008;
            if(BitOfs) *BitOfs = 3;
            return 0x1040;
         default:
            throw 20;
      };
   };

   // Bit(s) ZERO_SUPR_EN
   unsigned int GetZeroSuprEn()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x103C, 0x00000100, 8);
         default:
            throw 20;
      };
   };
   unsigned int SetZeroSuprEn(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x103C, 0x00000100, 8, value);
         default:
            throw 20;
      };
   };
   unsigned int GetZeroSuprEnLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x00000100;
            if(BitOfs) *BitOfs = 8;
            return 0x103C;
         default:
            throw 20;
      };
   };

   // Bit(s) ZERO_SUPR_WINDOW
   unsigned int GetZeroSuprWindow()
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return BitExtractControl(0x103C, 0x000000FF, 0);
         default:
            throw 20;
      };
   };
   unsigned int SetZeroSuprWindow(unsigned int value)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            return SetRegMask(0x103C, 0x000000FF, 0, value);
         default:
            throw 20;
      };
   };
   unsigned int GetZeroSuprWindowLoc(unsigned int *BitMask=0, unsigned int *BitOfs=0)
   {
      switch(this->mVersion)
      {
         case 8:
         case 9:
            if(BitMask) *BitMask = 0x000000FF;
            if(BitOfs) *BitOfs = 0;
            return 0x103C;
         default:
            throw 20;
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
            throw 20;
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
            throw 20;
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
            throw 20;
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
            throw 20;
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
            throw 20;
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
            throw 20;
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
            throw 20;
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
            throw 20;
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
            throw 20;
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
            throw 20;
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
            throw 20;
      };
   };


};

//--------------------------------------------------------------------

#endif /* defined(__wdbreg_h__) */

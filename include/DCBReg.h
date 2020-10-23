//
//  DCBReg.h
//
//  MEGII - DCB Register Access Class
//
//  This file is generated automatically, please do not edit!
//
<<<<<<< Updated upstream
// Created :  25.09.2020 14:38:00
=======
// Created :  23.10.2020 09:16:10
>>>>>>> Stashed changes
//


#ifndef __DCBREG_H__
#define __DCBREG_H__

#include "register_map_dcb.h"

//--------------------------------------------------------------------

class DCBREG {

private:
   // virtual bit functions, must be implemented in derived class
   virtual unsigned int BitExtract(unsigned int reg, unsigned int mask, unsigned int ofs) = 0;
   virtual void SetRegMask(unsigned int reg, unsigned int mask, unsigned int ofs, unsigned int v) = 0;

public:

   // constructor
   DCBREG(){};



   ////// ------ Register 0 [0x0000]: HW_VER - Hardware version information of the PCB (Default: 0xAC010307) ------ //////

   // 0xFF000000: BOARD_MAGIC - 0xAC, Magic number for board identification
   unsigned int GetBoardMagic() { return BitExtract(DCB_BOARD_MAGIC_REG, DCB_BOARD_MAGIC_MASK, DCB_BOARD_MAGIC_OFS); };
   // 0x00FF0000: VENDOR_ID - ID of the board vendor (0x01 for PSI)
   unsigned int GetVendorId() { return BitExtract(DCB_VENDOR_ID_REG, DCB_VENDOR_ID_MASK, DCB_VENDOR_ID_OFS); };
   // 0x0000FF00: BOARD_TYPE - DCB Number (0x03 for DCB ???)
   unsigned int GetBoardType() { return BitExtract(DCB_BOARD_TYPE_REG, DCB_BOARD_TYPE_MASK, DCB_BOARD_TYPE_OFS); };
   // 0x000000FC: BOARD_REVISION - Board revision (A=0x00, B=0x01, C=0x02, D=0x03, E=0x04)
   unsigned int GetBoardRevision() { return BitExtract(DCB_BOARD_REVISION_REG, DCB_BOARD_REVISION_MASK, DCB_BOARD_REVISION_OFS); };
   // 0x00000003: BOARD_VARIANT - Version indicator pins reflecting the variant of the board (XXX,YYY)
   unsigned int GetBoardVariant() { return BitExtract(DCB_BOARD_VARIANT_REG, DCB_BOARD_VARIANT_MASK, DCB_BOARD_VARIANT_OFS); };


   ////// ------ Register 1 [0x0004]: REG_LAYOUT_VER - Register map layout version information (Default: 0x00000000) ------ //////

   // 0xFFFF0000: REG_LAYOUT_COMP_LEVEL - Register map layout compatibility level
   unsigned int GetRegLayoutCompLevel() { return BitExtract(DCB_REG_LAYOUT_COMP_LEVEL_REG, DCB_REG_LAYOUT_COMP_LEVEL_MASK, DCB_REG_LAYOUT_COMP_LEVEL_OFS); };
   // 0x0000FFFF: REG_LAYOUT_VERSION - Register map layout version
   unsigned int GetRegLayoutVersion() { return BitExtract(DCB_REG_LAYOUT_VERSION_REG, DCB_REG_LAYOUT_VERSION_MASK, DCB_REG_LAYOUT_VERSION_OFS); };


   ////// ------ Register 2 [0x0008]: FW_BUILD_DATE - Date when the firmware was built (Default: 0x00000000) ------ //////

   // 0xFFFF0000: FW_BUILD_YEAR - Year of the firmware build
   unsigned int GetFwBuildYear() { return BitExtract(DCB_FW_BUILD_YEAR_REG, DCB_FW_BUILD_YEAR_MASK, DCB_FW_BUILD_YEAR_OFS); };
   // 0x0000FF00: FW_BUILD_MONTH - Month of the firmware build
   unsigned int GetFwBuildMonth() { return BitExtract(DCB_FW_BUILD_MONTH_REG, DCB_FW_BUILD_MONTH_MASK, DCB_FW_BUILD_MONTH_OFS); };
   // 0x000000FF: FW_BUILD_DAY - Day of the firmware build
   unsigned int GetFwBuildDay() { return BitExtract(DCB_FW_BUILD_DAY_REG, DCB_FW_BUILD_DAY_MASK, DCB_FW_BUILD_DAY_OFS); };


   ////// ------ Register 3 [0x000C]: FW_BUILD_TIME - Time when the firmware was built and compatibility level (Default: 0x00000000) ------ //////

   // 0xFF000000: FW_COMPAT_LEVEL - Firmware compatibility level
   unsigned int GetFwCompatLevel() { return BitExtract(DCB_FW_COMPAT_LEVEL_REG, DCB_FW_COMPAT_LEVEL_MASK, DCB_FW_COMPAT_LEVEL_OFS); };
   // 0x00FF0000: FW_BUILD_HOUR - Hour of the firmware build
   unsigned int GetFwBuildHour() { return BitExtract(DCB_FW_BUILD_HOUR_REG, DCB_FW_BUILD_HOUR_MASK, DCB_FW_BUILD_HOUR_OFS); };
   // 0x0000FF00: FW_BUILD_MINUTE - Minute of the firmware build
   unsigned int GetFwBuildMinute() { return BitExtract(DCB_FW_BUILD_MINUTE_REG, DCB_FW_BUILD_MINUTE_MASK, DCB_FW_BUILD_MINUTE_OFS); };
   // 0x000000FF: FW_BUILD_SECOND - Second of the firmware build
   unsigned int GetFwBuildSecond() { return BitExtract(DCB_FW_BUILD_SECOND_REG, DCB_FW_BUILD_SECOND_MASK, DCB_FW_BUILD_SECOND_OFS); };


   ////// ------ Register 4 [0x0010]: SW_BUILD_DATE - Date when the software was built (Default: 0x00000000) ------ //////

   // 0xFFFF0000: SW_BUILD_YEAR - Year of the software build
   unsigned int GetSwBuildYear() { return BitExtract(DCB_SW_BUILD_YEAR_REG, DCB_SW_BUILD_YEAR_MASK, DCB_SW_BUILD_YEAR_OFS); };
   void         SetSwBuildYear(unsigned int value) { SetRegMask(DCB_SW_BUILD_YEAR_REG, DCB_SW_BUILD_YEAR_MASK, DCB_SW_BUILD_YEAR_OFS, value); };

   // 0x0000FF00: SW_BUILD_MONTH - Month of the software build
   unsigned int GetSwBuildMonth() { return BitExtract(DCB_SW_BUILD_MONTH_REG, DCB_SW_BUILD_MONTH_MASK, DCB_SW_BUILD_MONTH_OFS); };
   void         SetSwBuildMonth(unsigned int value) { SetRegMask(DCB_SW_BUILD_MONTH_REG, DCB_SW_BUILD_MONTH_MASK, DCB_SW_BUILD_MONTH_OFS, value); };

   // 0x000000FF: SW_BUILD_DAY - Day of the software build
   unsigned int GetSwBuildDay() { return BitExtract(DCB_SW_BUILD_DAY_REG, DCB_SW_BUILD_DAY_MASK, DCB_SW_BUILD_DAY_OFS); };
   void         SetSwBuildDay(unsigned int value) { SetRegMask(DCB_SW_BUILD_DAY_REG, DCB_SW_BUILD_DAY_MASK, DCB_SW_BUILD_DAY_OFS, value); };



   ////// ------ Register 5 [0x0014]: SW_BUILD_TIME - Time when the software was built and compatibility level (Default: 0x00000000) ------ //////

   // 0x00FF0000: SW_BUILD_HOUR - Hour of the software build
   unsigned int GetSwBuildHour() { return BitExtract(DCB_SW_BUILD_HOUR_REG, DCB_SW_BUILD_HOUR_MASK, DCB_SW_BUILD_HOUR_OFS); };
   void         SetSwBuildHour(unsigned int value) { SetRegMask(DCB_SW_BUILD_HOUR_REG, DCB_SW_BUILD_HOUR_MASK, DCB_SW_BUILD_HOUR_OFS, value); };

   // 0x0000FF00: SW_BUILD_MINUTE - Minute of the software build
   unsigned int GetSwBuildMinute() { return BitExtract(DCB_SW_BUILD_MINUTE_REG, DCB_SW_BUILD_MINUTE_MASK, DCB_SW_BUILD_MINUTE_OFS); };
   void         SetSwBuildMinute(unsigned int value) { SetRegMask(DCB_SW_BUILD_MINUTE_REG, DCB_SW_BUILD_MINUTE_MASK, DCB_SW_BUILD_MINUTE_OFS, value); };

   // 0x000000FF: SW_BUILD_SECOND - Second of the software build
   unsigned int GetSwBuildSecond() { return BitExtract(DCB_SW_BUILD_SECOND_REG, DCB_SW_BUILD_SECOND_MASK, DCB_SW_BUILD_SECOND_OFS); };
   void         SetSwBuildSecond(unsigned int value) { SetRegMask(DCB_SW_BUILD_SECOND_REG, DCB_SW_BUILD_SECOND_MASK, DCB_SW_BUILD_SECOND_OFS, value); };



   ////// ------ Register 6 [0x0018]: FW_GIT_HASH_TAG - Hash tag of the firmware commit in the GIT repository (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: FW_GIT_HASH_TAG - Hash tag of the firmware commit in the GIT repository
   unsigned int GetFwGitHashTag() { return BitExtract(DCB_FW_GIT_HASH_TAG_REG, DCB_FW_GIT_HASH_TAG_MASK, DCB_FW_GIT_HASH_TAG_OFS); };


   ////// ------ Register 7 [0x001C]: SW_GIT_HASH_TAG - Hash tag of the software commit in the GIT repository (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SW_GIT_HASH_TAG - Hash tag of the software commit in the GIT repository
   unsigned int GetSwGitHashTag() { return BitExtract(DCB_SW_GIT_HASH_TAG_REG, DCB_SW_GIT_HASH_TAG_MASK, DCB_SW_GIT_HASH_TAG_OFS); };
   void         SetSwGitHashTag(unsigned int value) { SetRegMask(DCB_SW_GIT_HASH_TAG_REG, DCB_SW_GIT_HASH_TAG_MASK, DCB_SW_GIT_HASH_TAG_OFS, value); };



   ////// ------ Register 8 [0x0020]: PROT_VER - Vesion of the WaveDream2 protocol (Default: 0x00000000) ------ //////

   // 0x000000FF: PROTOCOL_VERSION - Version of the WaveDream2 protocol
   unsigned int GetProtocolVersion() { return BitExtract(DCB_PROTOCOL_VERSION_REG, DCB_PROTOCOL_VERSION_MASK, DCB_PROTOCOL_VERSION_OFS); };
   void         SetProtocolVersion(unsigned int value) { SetRegMask(DCB_PROTOCOL_VERSION_REG, DCB_PROTOCOL_VERSION_MASK, DCB_PROTOCOL_VERSION_OFS, value); };



   ////// ------ Register 9 [0x0024]: SN - Serial Number of the WD2 Board (Board ID) (Default: 0x00000000) ------ //////

   // 0x0000FFFF: SERIAL_NUMBER - Serial Number of the WD2 Board (Board ID)
   unsigned int GetSerialNumber() { return BitExtract(DCB_SERIAL_NUMBER_REG, DCB_SERIAL_NUMBER_MASK, DCB_SERIAL_NUMBER_OFS); };
   void         SetSerialNumber(unsigned int value) { SetRegMask(DCB_SERIAL_NUMBER_REG, DCB_SERIAL_NUMBER_MASK, DCB_SERIAL_NUMBER_OFS, value); };



   ////// ------ Register 10 [0x0028]: STATUS - Status Register (Default: 0x00000000) ------ //////

   // 0x00000020: FLASH_SEL - SPI Flash select from backplane (inverted = high active)
   unsigned int GetFlashSel() { return BitExtract(DCB_FLASH_SEL_REG, DCB_FLASH_SEL_MASK, DCB_FLASH_SEL_OFS); };
   // 0x00000010: BOARD_SEL - Board select from backplane (inverted = high active)
   unsigned int GetBoardSel() { return BitExtract(DCB_BOARD_SEL_REG, DCB_BOARD_SEL_MASK, DCB_BOARD_SEL_OFS); };
   // 0x00000004: SERIAL_BUSY - "1" during serial activity like FLASH read/write
   unsigned int GetSerialBusy() { return BitExtract(DCB_SERIAL_BUSY_REG, DCB_SERIAL_BUSY_MASK, DCB_SERIAL_BUSY_OFS); };
   // 0x00000002: DCB_BUSY - "1" while dcb is busy
   unsigned int GetDcbBusy() { return BitExtract(DCB_DCB_BUSY_REG, DCB_DCB_BUSY_MASK, DCB_DCB_BUSY_OFS); };
   // 0x00000001: SYS_BUSY - Inverted busy signal from backplane (active low)
   unsigned int GetSysBusy() { return BitExtract(DCB_SYS_BUSY_REG, DCB_SYS_BUSY_MASK, DCB_SYS_BUSY_OFS); };


   ////// ------ Register 11 [0x002C]: TEMP - Status Register (Default: 0x00000000) ------ //////

   // 0x0000FFFF: TEMPERATURE - temperature in 0.0625 deg. C units
   unsigned int GetTemperature() { return BitExtract(DCB_TEMPERATURE_REG, DCB_TEMPERATURE_MASK, DCB_TEMPERATURE_OFS); };
   void         SetTemperature(unsigned int value) { SetRegMask(DCB_TEMPERATURE_REG, DCB_TEMPERATURE_MASK, DCB_TEMPERATURE_OFS, value); };



   ////// ------ Register 12 [0x0030]: PLL_LOCK - Lock Status of PLLs (Default: 0x00000000) ------ //////

   // 0x00000008: SERDES_CLK_MGR_LOCK - Lock of the clock manager deriving clocks for serdes from the WDB clock
   unsigned int GetSerdesClkMgrLock() { return BitExtract(DCB_SERDES_CLK_MGR_LOCK_REG, DCB_SERDES_CLK_MGR_LOCK_MASK, DCB_SERDES_CLK_MGR_LOCK_OFS); };
   // 0x00000004: WDB_CLK_MGR_LOCK - Lock of the clock manager deriving clocks from the WDB clock (e.g. refclk for SYNC output delay)
   unsigned int GetWdbClkMgrLock() { return BitExtract(DCB_WDB_CLK_MGR_LOCK_REG, DCB_WDB_CLK_MGR_LOCK_MASK, DCB_WDB_CLK_MGR_LOCK_OFS); };
   // 0x00000002: SYS_DCM_LOCK - Lock of system DCM (FPGA internal)
   unsigned int GetSysDcmLock() { return BitExtract(DCB_SYS_DCM_LOCK_REG, DCB_SYS_DCM_LOCK_MASK, DCB_SYS_DCM_LOCK_OFS); };
   // 0x00000001: LMK_PLL_LOCK - PLL lock signal of LMK (external)
   unsigned int GetLmkPllLock() { return BitExtract(DCB_LMK_PLL_LOCK_REG, DCB_LMK_PLL_LOCK_MASK, DCB_LMK_PLL_LOCK_OFS); };


   ////// ------ Register 13 [0x0034]: DCB_LOC - Location where the WD2 is plugged in (Default: 0xFFFFFFFF) ------ //////

   // 0x00FF0000: CRATE_ID - ID of the crate where the current board is plugged in
   unsigned int GetCrateId() { return BitExtract(DCB_CRATE_ID_REG, DCB_CRATE_ID_MASK, DCB_CRATE_ID_OFS); };
   void         SetCrateId(unsigned int value) { SetRegMask(DCB_CRATE_ID_REG, DCB_CRATE_ID_MASK, DCB_CRATE_ID_OFS, value); };

   // 0x000000FF: SLOT_ID - ID of the slot where the current board is plugged in
   unsigned int GetSlotId() { return BitExtract(DCB_SLOT_ID_REG, DCB_SLOT_ID_MASK, DCB_SLOT_ID_OFS); };
   void         SetSlotId(unsigned int value) { SetRegMask(DCB_SLOT_ID_REG, DCB_SLOT_ID_MASK, DCB_SLOT_ID_OFS, value); };



   ////// ------ Register 14 [0x0038]: CTRL - DCB control register (Default: 0x00000000) ------ //////

   // 0x001F0000: SYNC_DELAY - Output delay of SYNC output to backplane
   unsigned int GetSyncDelay() { return BitExtract(DCB_SYNC_DELAY_REG, DCB_SYNC_DELAY_MASK, DCB_SYNC_DELAY_OFS); };
   void         SetSyncDelay(unsigned int value) { SetRegMask(DCB_SYNC_DELAY_REG, DCB_SYNC_DELAY_MASK, DCB_SYNC_DELAY_OFS, value); };

   // 0x00000001: DAQ_SOFT_TRIGGER - config 0
   unsigned int GetDaqSoftTrigger() { return BitExtract(DCB_DAQ_SOFT_TRIGGER_REG, DCB_DAQ_SOFT_TRIGGER_MASK, DCB_DAQ_SOFT_TRIGGER_OFS); };
   void         SetDaqSoftTrigger(unsigned int value) { SetRegMask(DCB_DAQ_SOFT_TRIGGER_REG, DCB_DAQ_SOFT_TRIGGER_MASK, DCB_DAQ_SOFT_TRIGGER_OFS, value); };



   ////// ------ Register 15 [0x003C]: SET_CTRL - SET bit register for DCB control register (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SET_BIT_CTRL - See CTRL register
   unsigned int GetSetBitCtrl() { return BitExtract(DCB_SET_BIT_CTRL_REG, DCB_SET_BIT_CTRL_MASK, DCB_SET_BIT_CTRL_OFS); };
   void         SetSetBitCtrl(unsigned int value) { SetRegMask(DCB_SET_BIT_CTRL_REG, DCB_SET_BIT_CTRL_MASK, DCB_SET_BIT_CTRL_OFS, value); };



   ////// ------ Register 16 [0x0040]: CLR_CTRL - CLR bit register for DCB control register (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: CLR_BIT_CTRL - See CTRL register
   unsigned int GetClrBitCtrl() { return BitExtract(DCB_CLR_BIT_CTRL_REG, DCB_CLR_BIT_CTRL_MASK, DCB_CLR_BIT_CTRL_OFS); };
   void         SetClrBitCtrl(unsigned int value) { SetRegMask(DCB_CLR_BIT_CTRL_REG, DCB_CLR_BIT_CTRL_MASK, DCB_CLR_BIT_CTRL_OFS, value); };



   ////// ------ Register 17 [0x0044]: CLK_CTRL - Clock Control (Default: 0xFFFFC00E) ------ //////

   // 0xFFFFF000: DISTRIBUTOR_CLK_OUT_EN - Clock distributor output enable (31:16 = LSK15:0, 15 = TCB, 14 = FPGA, 13:12 = spare)
   unsigned int GetDistributorClkOutEn() { return BitExtract(DCB_DISTRIBUTOR_CLK_OUT_EN_REG, DCB_DISTRIBUTOR_CLK_OUT_EN_MASK, DCB_DISTRIBUTOR_CLK_OUT_EN_OFS); };
   void         SetDistributorClkOutEn(unsigned int value) { SetRegMask(DCB_DISTRIBUTOR_CLK_OUT_EN_REG, DCB_DISTRIBUTOR_CLK_OUT_EN_MASK, DCB_DISTRIBUTOR_CLK_OUT_EN_OFS, value); };

   // 0x00000008: DISTRIBUTOR_CLK_SRC_SEL - Backplane clock distributor source select: 0 = external clock / 1 = LMK
   unsigned int GetDistributorClkSrcSel() { return BitExtract(DCB_DISTRIBUTOR_CLK_SRC_SEL_REG, DCB_DISTRIBUTOR_CLK_SRC_SEL_MASK, DCB_DISTRIBUTOR_CLK_SRC_SEL_OFS); };
   void         SetDistributorClkSrcSel(unsigned int value) { SetRegMask(DCB_DISTRIBUTOR_CLK_SRC_SEL_REG, DCB_DISTRIBUTOR_CLK_SRC_SEL_MASK, DCB_DISTRIBUTOR_CLK_SRC_SEL_OFS, value); };

   // 0x00000004: BUS_CLK_SRC_SEL - BUS (backplane) clock source select: 0 = LMK output 2 / 1 = AUX_OUT from FPGA (BUS_CLK_SEL)
   unsigned int GetBusClkSrcSel() { return BitExtract(DCB_BUS_CLK_SRC_SEL_REG, DCB_BUS_CLK_SRC_SEL_MASK, DCB_BUS_CLK_SRC_SEL_OFS); };
   void         SetBusClkSrcSel(unsigned int value) { SetRegMask(DCB_BUS_CLK_SRC_SEL_REG, DCB_BUS_CLK_SRC_SEL_MASK, DCB_BUS_CLK_SRC_SEL_OFS, value); };

   // 0x00000002: LMK_CLK_SRC_SEL - LMK clock source select: 0 = external clock / 1 = on board oscillator (CLK_SEL)
   unsigned int GetLmkClkSrcSel() { return BitExtract(DCB_LMK_CLK_SRC_SEL_REG, DCB_LMK_CLK_SRC_SEL_MASK, DCB_LMK_CLK_SRC_SEL_OFS); };
   void         SetLmkClkSrcSel(unsigned int value) { SetRegMask(DCB_LMK_CLK_SRC_SEL_REG, DCB_LMK_CLK_SRC_SEL_MASK, DCB_LMK_CLK_SRC_SEL_OFS, value); };

   // 0x00000001: EXT_CLK_IN_SEL - External clk input select: 0 = FCI / 1 = MCX connector (CLK_SEL_EXT)
   unsigned int GetExtClkInSel() { return BitExtract(DCB_EXT_CLK_IN_SEL_REG, DCB_EXT_CLK_IN_SEL_MASK, DCB_EXT_CLK_IN_SEL_OFS); };
   void         SetExtClkInSel(unsigned int value) { SetRegMask(DCB_EXT_CLK_IN_SEL_REG, DCB_EXT_CLK_IN_SEL_MASK, DCB_EXT_CLK_IN_SEL_OFS, value); };



   ////// ------ Register 18 [0x0048]: SET_CLK_CTRL - SET bit register for Clock control register (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SET_BIT_CLK_CTRL - See CLK_CTRL register
   unsigned int GetSetBitClkCtrl() { return BitExtract(DCB_SET_BIT_CLK_CTRL_REG, DCB_SET_BIT_CLK_CTRL_MASK, DCB_SET_BIT_CLK_CTRL_OFS); };
   void         SetSetBitClkCtrl(unsigned int value) { SetRegMask(DCB_SET_BIT_CLK_CTRL_REG, DCB_SET_BIT_CLK_CTRL_MASK, DCB_SET_BIT_CLK_CTRL_OFS, value); };



   ////// ------ Register 19 [0x004C]: CLR_CLK_CTRL - CLR bit register for Clock control register (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: CLR_BIT_CLK_CTRL - See CLK_CTRL register
   unsigned int GetClrBitClkCtrl() { return BitExtract(DCB_CLR_BIT_CLK_CTRL_REG, DCB_CLR_BIT_CLK_CTRL_MASK, DCB_CLR_BIT_CLK_CTRL_OFS); };
   void         SetClrBitClkCtrl(unsigned int value) { SetRegMask(DCB_CLR_BIT_CLK_CTRL_REG, DCB_CLR_BIT_CLK_CTRL_MASK, DCB_CLR_BIT_CLK_CTRL_OFS, value); };



   ////// ------ Register 20 [0x0050]: COM_CTRL - Communication Control Register (Default: 0x00000753) ------ //////

   // 0x00FFFFFF: INTER_PKG_DELAY - Delay between transmission of two UDP packages in 8ns steps
   unsigned int GetInterPkgDelay() { return BitExtract(DCB_INTER_PKG_DELAY_REG, DCB_INTER_PKG_DELAY_MASK, DCB_INTER_PKG_DELAY_OFS); };
   void         SetInterPkgDelay(unsigned int value) { SetRegMask(DCB_INTER_PKG_DELAY_REG, DCB_INTER_PKG_DELAY_MASK, DCB_INTER_PKG_DELAY_OFS, value); };



   ////// ------ Register 21 [0x0054]: RST - Reset bits for specific firmwar units (Default: 0x00000000) ------ //////

<<<<<<< Updated upstream
   // 0x00000100: WDB_SERDES_CLK_MGR_RST - Reset for clock manager deriving serdes clocks from the WDB clock
=======
   // 0x00000100: WDB_SERDES_CLK_MGR_RST - Reset for clock manager deriving clocks from the WDB clock (e.g. refclk for SYNC output delay)
>>>>>>> Stashed changes
   unsigned int GetWdbSerdesClkMgrRst() { return BitExtract(DCB_WDB_SERDES_CLK_MGR_RST_REG, DCB_WDB_SERDES_CLK_MGR_RST_MASK, DCB_WDB_SERDES_CLK_MGR_RST_OFS); };
   void         SetWdbSerdesClkMgrRst(unsigned int value) { SetRegMask(DCB_WDB_SERDES_CLK_MGR_RST_REG, DCB_WDB_SERDES_CLK_MGR_RST_MASK, DCB_WDB_SERDES_CLK_MGR_RST_OFS, value); };

   // 0x00000080: WDB_REFCLK_MGR_RST - Reset for clock manager deriving clocks from the WDB clock (e.g. refclk for SYNC output delay)
   unsigned int GetWdbRefclkMgrRst() { return BitExtract(DCB_WDB_REFCLK_MGR_RST_REG, DCB_WDB_REFCLK_MGR_RST_MASK, DCB_WDB_REFCLK_MGR_RST_OFS); };
   void         SetWdbRefclkMgrRst(unsigned int value) { SetRegMask(DCB_WDB_REFCLK_MGR_RST_REG, DCB_WDB_REFCLK_MGR_RST_MASK, DCB_WDB_REFCLK_MGR_RST_OFS, value); };

   // 0x00000040: TRIGGER_MGR_RST - Trigger manager reset
   unsigned int GetTriggerMgrRst() { return BitExtract(DCB_TRIGGER_MGR_RST_REG, DCB_TRIGGER_MGR_RST_MASK, DCB_TRIGGER_MGR_RST_OFS); };
   void         SetTriggerMgrRst(unsigned int value) { SetRegMask(DCB_TRIGGER_MGR_RST_REG, DCB_TRIGGER_MGR_RST_MASK, DCB_TRIGGER_MGR_RST_OFS, value); };

   // 0x00000020: TR_SYNC_BPL - Trigger SYNC signal on the backplane
   unsigned int GetTrSyncBpl() { return BitExtract(DCB_TR_SYNC_BPL_REG, DCB_TR_SYNC_BPL_MASK, DCB_TR_SYNC_BPL_OFS); };
   void         SetTrSyncBpl(unsigned int value) { SetRegMask(DCB_TR_SYNC_BPL_REG, DCB_TR_SYNC_BPL_MASK, DCB_TR_SYNC_BPL_OFS, value); };

   // 0x00000010: LMK_SYNC_DCB - Trigger SYNC signal of the LMK on the DCB
   unsigned int GetLmkSyncDcb() { return BitExtract(DCB_LMK_SYNC_DCB_REG, DCB_LMK_SYNC_DCB_MASK, DCB_LMK_SYNC_DCB_OFS); };
   void         SetLmkSyncDcb(unsigned int value) { SetRegMask(DCB_LMK_SYNC_DCB_REG, DCB_LMK_SYNC_DCB_MASK, DCB_LMK_SYNC_DCB_OFS, value); };

   // 0x00000008: ISERDES_RCVR_ERROR_COUNT_RST - Reset of the input SERDES packet receiver
   unsigned int GetIserdesRcvrErrorCountRst() { return BitExtract(DCB_ISERDES_RCVR_ERROR_COUNT_RST_REG, DCB_ISERDES_RCVR_ERROR_COUNT_RST_MASK, DCB_ISERDES_RCVR_ERROR_COUNT_RST_OFS); };
   void         SetIserdesRcvrErrorCountRst(unsigned int value) { SetRegMask(DCB_ISERDES_RCVR_ERROR_COUNT_RST_REG, DCB_ISERDES_RCVR_ERROR_COUNT_RST_MASK, DCB_ISERDES_RCVR_ERROR_COUNT_RST_OFS, value); };

   // 0x00000004: ISERDES_RECEIVER_RESYNC - Resynchronization of the input SERDES packet receiver
   unsigned int GetIserdesReceiverResync() { return BitExtract(DCB_ISERDES_RECEIVER_RESYNC_REG, DCB_ISERDES_RECEIVER_RESYNC_MASK, DCB_ISERDES_RECEIVER_RESYNC_OFS); };
   void         SetIserdesReceiverResync(unsigned int value) { SetRegMask(DCB_ISERDES_RECEIVER_RESYNC_REG, DCB_ISERDES_RECEIVER_RESYNC_MASK, DCB_ISERDES_RECEIVER_RESYNC_OFS, value); };

   // 0x00000002: ISERDES_RECEIVER_RST - Reset of the input SERDES packet receiver
   unsigned int GetIserdesReceiverRst() { return BitExtract(DCB_ISERDES_RECEIVER_RST_REG, DCB_ISERDES_RECEIVER_RST_MASK, DCB_ISERDES_RECEIVER_RST_OFS); };
   void         SetIserdesReceiverRst(unsigned int value) { SetRegMask(DCB_ISERDES_RECEIVER_RST_REG, DCB_ISERDES_RECEIVER_RST_MASK, DCB_ISERDES_RECEIVER_RST_OFS, value); };

   // 0x00000001: RECONFIGURE_FPGA - Initiate FPGA Reconfiguration
   unsigned int GetReconfigureFpga() { return BitExtract(DCB_RECONFIGURE_FPGA_REG, DCB_RECONFIGURE_FPGA_MASK, DCB_RECONFIGURE_FPGA_OFS); };
   void         SetReconfigureFpga(unsigned int value) { SetRegMask(DCB_RECONFIGURE_FPGA_REG, DCB_RECONFIGURE_FPGA_MASK, DCB_RECONFIGURE_FPGA_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 22 [0x0058]: SERDES_STATUS_00_04 - Input Serdes status for slot 0 to 4 (Default: 0x00000000) ------ //////

=======
   ////// ------ Register 22 [0x0058]: SERDES_STATUS_00_07 - Input Serdes status for slot 0 to 7 (Default: 0x00000000) ------ //////

   // 0x40000000: IDLE_PATTERN_DETECT_07 - Idle pattern detected on slot 7
   unsigned int GetIdlePatternDetect07() { return BitExtract(DCB_IDLE_PATTERN_DETECT_07_REG, DCB_IDLE_PATTERN_DETECT_07_MASK, DCB_IDLE_PATTERN_DETECT_07_OFS); };
   // 0x20000000: DELAY_SYNC_DONE_07 - Delay syncronization procedure completed for slot 7
   unsigned int GetDelaySyncDone07() { return BitExtract(DCB_DELAY_SYNC_DONE_07_REG, DCB_DELAY_SYNC_DONE_07_MASK, DCB_DELAY_SYNC_DONE_07_OFS); };
   // 0x10000000: SYNC_DONE_07 - Overall syncronization procedure completed for slot 7
   unsigned int GetSyncDone07() { return BitExtract(DCB_SYNC_DONE_07_REG, DCB_SYNC_DONE_07_MASK, DCB_SYNC_DONE_07_OFS); };
   // 0x04000000: IDLE_PATTERN_DETECT_06 - Idle pattern detected on slot 6
   unsigned int GetIdlePatternDetect06() { return BitExtract(DCB_IDLE_PATTERN_DETECT_06_REG, DCB_IDLE_PATTERN_DETECT_06_MASK, DCB_IDLE_PATTERN_DETECT_06_OFS); };
   // 0x02000000: DELAY_SYNC_DONE_06 - Delay syncronization procedure completed for slot 6
   unsigned int GetDelaySyncDone06() { return BitExtract(DCB_DELAY_SYNC_DONE_06_REG, DCB_DELAY_SYNC_DONE_06_MASK, DCB_DELAY_SYNC_DONE_06_OFS); };
   // 0x01000000: SYNC_DONE_06 - Overall syncronization procedure completed for slot 6
   unsigned int GetSyncDone06() { return BitExtract(DCB_SYNC_DONE_06_REG, DCB_SYNC_DONE_06_MASK, DCB_SYNC_DONE_06_OFS); };
   // 0x00400000: IDLE_PATTERN_DETECT_05 - Idle pattern detected on slot 5
   unsigned int GetIdlePatternDetect05() { return BitExtract(DCB_IDLE_PATTERN_DETECT_05_REG, DCB_IDLE_PATTERN_DETECT_05_MASK, DCB_IDLE_PATTERN_DETECT_05_OFS); };
   // 0x00200000: DELAY_SYNC_DONE_05 - Delay syncronization procedure completed for slot 5
   unsigned int GetDelaySyncDone05() { return BitExtract(DCB_DELAY_SYNC_DONE_05_REG, DCB_DELAY_SYNC_DONE_05_MASK, DCB_DELAY_SYNC_DONE_05_OFS); };
   // 0x00100000: SYNC_DONE_05 - Overall syncronization procedure completed for slot 5
   unsigned int GetSyncDone05() { return BitExtract(DCB_SYNC_DONE_05_REG, DCB_SYNC_DONE_05_MASK, DCB_SYNC_DONE_05_OFS); };
   // 0x00040000: IDLE_PATTERN_DETECT_04 - Idle pattern detected on slot 4
   unsigned int GetIdlePatternDetect04() { return BitExtract(DCB_IDLE_PATTERN_DETECT_04_REG, DCB_IDLE_PATTERN_DETECT_04_MASK, DCB_IDLE_PATTERN_DETECT_04_OFS); };
   // 0x00020000: DELAY_SYNC_DONE_04 - Delay syncronization procedure completed for slot 4
   unsigned int GetDelaySyncDone04() { return BitExtract(DCB_DELAY_SYNC_DONE_04_REG, DCB_DELAY_SYNC_DONE_04_MASK, DCB_DELAY_SYNC_DONE_04_OFS); };
   // 0x00010000: SYNC_DONE_04 - Overall syncronization procedure completed for slot 4
   unsigned int GetSyncDone04() { return BitExtract(DCB_SYNC_DONE_04_REG, DCB_SYNC_DONE_04_MASK, DCB_SYNC_DONE_04_OFS); };
   // 0x00004000: IDLE_PATTERN_DETECT_03 - Idle pattern detected on slot 3
   unsigned int GetIdlePatternDetect03() { return BitExtract(DCB_IDLE_PATTERN_DETECT_03_REG, DCB_IDLE_PATTERN_DETECT_03_MASK, DCB_IDLE_PATTERN_DETECT_03_OFS); };
   // 0x00002000: DELAY_SYNC_DONE_03 - Delay syncronization procedure completed for slot 3
   unsigned int GetDelaySyncDone03() { return BitExtract(DCB_DELAY_SYNC_DONE_03_REG, DCB_DELAY_SYNC_DONE_03_MASK, DCB_DELAY_SYNC_DONE_03_OFS); };
   // 0x00001000: SYNC_DONE_03 - Overall syncronization procedure completed for slot 3
   unsigned int GetSyncDone03() { return BitExtract(DCB_SYNC_DONE_03_REG, DCB_SYNC_DONE_03_MASK, DCB_SYNC_DONE_03_OFS); };
   // 0x00000400: IDLE_PATTERN_DETECT_02 - Idle pattern detected on slot 2
   unsigned int GetIdlePatternDetect02() { return BitExtract(DCB_IDLE_PATTERN_DETECT_02_REG, DCB_IDLE_PATTERN_DETECT_02_MASK, DCB_IDLE_PATTERN_DETECT_02_OFS); };
   // 0x00000200: DELAY_SYNC_DONE_02 - Delay syncronization procedure completed for slot 2
   unsigned int GetDelaySyncDone02() { return BitExtract(DCB_DELAY_SYNC_DONE_02_REG, DCB_DELAY_SYNC_DONE_02_MASK, DCB_DELAY_SYNC_DONE_02_OFS); };
   // 0x00000100: SYNC_DONE_02 - Overall syncronization procedure completed for slot 2
   unsigned int GetSyncDone02() { return BitExtract(DCB_SYNC_DONE_02_REG, DCB_SYNC_DONE_02_MASK, DCB_SYNC_DONE_02_OFS); };
   // 0x00000040: IDLE_PATTERN_DETECT_01 - Idle pattern detected on slot 1
   unsigned int GetIdlePatternDetect01() { return BitExtract(DCB_IDLE_PATTERN_DETECT_01_REG, DCB_IDLE_PATTERN_DETECT_01_MASK, DCB_IDLE_PATTERN_DETECT_01_OFS); };
   // 0x00000020: DELAY_SYNC_DONE_01 - Delay syncronization procedure completed for slot 1
   unsigned int GetDelaySyncDone01() { return BitExtract(DCB_DELAY_SYNC_DONE_01_REG, DCB_DELAY_SYNC_DONE_01_MASK, DCB_DELAY_SYNC_DONE_01_OFS); };
   // 0x00000010: SYNC_DONE_01 - Overall syncronization procedure completed for slot 1
   unsigned int GetSyncDone01() { return BitExtract(DCB_SYNC_DONE_01_REG, DCB_SYNC_DONE_01_MASK, DCB_SYNC_DONE_01_OFS); };
>>>>>>> Stashed changes
   // 0x00000004: IDLE_PATTERN_DETECT_00 - Idle pattern detected on slot 0
   unsigned int GetIdlePatternDetect00() { return BitExtract(DCB_IDLE_PATTERN_DETECT_00_REG, DCB_IDLE_PATTERN_DETECT_00_MASK, DCB_IDLE_PATTERN_DETECT_00_OFS); };
   // 0x00000002: DELAY_SYNC_DONE_00 - Delay syncronization procedure completed for slot 0
   unsigned int GetDelaySyncDone00() { return BitExtract(DCB_DELAY_SYNC_DONE_00_REG, DCB_DELAY_SYNC_DONE_00_MASK, DCB_DELAY_SYNC_DONE_00_OFS); };
   // 0x00000001: SYNC_DONE_00 - Overall syncronization procedure completed for slot 0
   unsigned int GetSyncDone00() { return BitExtract(DCB_SYNC_DONE_00_REG, DCB_SYNC_DONE_00_MASK, DCB_SYNC_DONE_00_OFS); };


<<<<<<< Updated upstream
   ////// ------ Register 23 [0x005C]: SERDES_ERR_CNT_00 - Input Serdes error count for slot 0 (Default: 0x00000000) ------ //////
=======
   ////// ------ Register 23 [0x005C]: SERDES_STATUS_08_15 - Input Serdes status for slot 8 to 15 (Default: 0x00000000) ------ //////

   // 0x40000000: IDLE_PATTERN_DETECT_15 - Idle pattern detected on slot 15
   unsigned int GetIdlePatternDetect15() { return BitExtract(DCB_IDLE_PATTERN_DETECT_15_REG, DCB_IDLE_PATTERN_DETECT_15_MASK, DCB_IDLE_PATTERN_DETECT_15_OFS); };
   // 0x20000000: DELAY_SYNC_DONE_15 - Delay syncronization procedure completed for slot 15
   unsigned int GetDelaySyncDone15() { return BitExtract(DCB_DELAY_SYNC_DONE_15_REG, DCB_DELAY_SYNC_DONE_15_MASK, DCB_DELAY_SYNC_DONE_15_OFS); };
   // 0x10000000: SYNC_DONE_15 - Overall syncronization procedure completed for slot 15
   unsigned int GetSyncDone15() { return BitExtract(DCB_SYNC_DONE_15_REG, DCB_SYNC_DONE_15_MASK, DCB_SYNC_DONE_15_OFS); };
   // 0x04000000: IDLE_PATTERN_DETECT_14 - Idle pattern detected on slot 14
   unsigned int GetIdlePatternDetect14() { return BitExtract(DCB_IDLE_PATTERN_DETECT_14_REG, DCB_IDLE_PATTERN_DETECT_14_MASK, DCB_IDLE_PATTERN_DETECT_14_OFS); };
   // 0x02000000: DELAY_SYNC_DONE_14 - Delay syncronization procedure completed for slot 14
   unsigned int GetDelaySyncDone14() { return BitExtract(DCB_DELAY_SYNC_DONE_14_REG, DCB_DELAY_SYNC_DONE_14_MASK, DCB_DELAY_SYNC_DONE_14_OFS); };
   // 0x01000000: SYNC_DONE_14 - Overall syncronization procedure completed for slot 14
   unsigned int GetSyncDone14() { return BitExtract(DCB_SYNC_DONE_14_REG, DCB_SYNC_DONE_14_MASK, DCB_SYNC_DONE_14_OFS); };
   // 0x00400000: IDLE_PATTERN_DETECT_13 - Idle pattern detected on slot 13
   unsigned int GetIdlePatternDetect13() { return BitExtract(DCB_IDLE_PATTERN_DETECT_13_REG, DCB_IDLE_PATTERN_DETECT_13_MASK, DCB_IDLE_PATTERN_DETECT_13_OFS); };
   // 0x00200000: DELAY_SYNC_DONE_13 - Delay syncronization procedure completed for slot 13
   unsigned int GetDelaySyncDone13() { return BitExtract(DCB_DELAY_SYNC_DONE_13_REG, DCB_DELAY_SYNC_DONE_13_MASK, DCB_DELAY_SYNC_DONE_13_OFS); };
   // 0x00100000: SYNC_DONE_13 - Overall syncronization procedure completed for slot 13
   unsigned int GetSyncDone13() { return BitExtract(DCB_SYNC_DONE_13_REG, DCB_SYNC_DONE_13_MASK, DCB_SYNC_DONE_13_OFS); };
   // 0x00040000: IDLE_PATTERN_DETECT_12 - Idle pattern detected on slot 12
   unsigned int GetIdlePatternDetect12() { return BitExtract(DCB_IDLE_PATTERN_DETECT_12_REG, DCB_IDLE_PATTERN_DETECT_12_MASK, DCB_IDLE_PATTERN_DETECT_12_OFS); };
   // 0x00020000: DELAY_SYNC_DONE_12 - Delay syncronization procedure completed for slot 12
   unsigned int GetDelaySyncDone12() { return BitExtract(DCB_DELAY_SYNC_DONE_12_REG, DCB_DELAY_SYNC_DONE_12_MASK, DCB_DELAY_SYNC_DONE_12_OFS); };
   // 0x00010000: SYNC_DONE_12 - Overall syncronization procedure completed for slot 12
   unsigned int GetSyncDone12() { return BitExtract(DCB_SYNC_DONE_12_REG, DCB_SYNC_DONE_12_MASK, DCB_SYNC_DONE_12_OFS); };
   // 0x00004000: IDLE_PATTERN_DETECT_11 - Idle pattern detected on slot 11
   unsigned int GetIdlePatternDetect11() { return BitExtract(DCB_IDLE_PATTERN_DETECT_11_REG, DCB_IDLE_PATTERN_DETECT_11_MASK, DCB_IDLE_PATTERN_DETECT_11_OFS); };
   // 0x00002000: DELAY_SYNC_DONE_11 - Delay syncronization procedure completed for slot 11
   unsigned int GetDelaySyncDone11() { return BitExtract(DCB_DELAY_SYNC_DONE_11_REG, DCB_DELAY_SYNC_DONE_11_MASK, DCB_DELAY_SYNC_DONE_11_OFS); };
   // 0x00001000: SYNC_DONE_11 - Overall syncronization procedure completed for slot 11
   unsigned int GetSyncDone11() { return BitExtract(DCB_SYNC_DONE_11_REG, DCB_SYNC_DONE_11_MASK, DCB_SYNC_DONE_11_OFS); };
   // 0x00000400: IDLE_PATTERN_DETECT_10 - Idle pattern detected on slot 10
   unsigned int GetIdlePatternDetect10() { return BitExtract(DCB_IDLE_PATTERN_DETECT_10_REG, DCB_IDLE_PATTERN_DETECT_10_MASK, DCB_IDLE_PATTERN_DETECT_10_OFS); };
   // 0x00000200: DELAY_SYNC_DONE_10 - Delay syncronization procedure completed for slot 10
   unsigned int GetDelaySyncDone10() { return BitExtract(DCB_DELAY_SYNC_DONE_10_REG, DCB_DELAY_SYNC_DONE_10_MASK, DCB_DELAY_SYNC_DONE_10_OFS); };
   // 0x00000100: SYNC_DONE_10 - Overall syncronization procedure completed for slot 10
   unsigned int GetSyncDone10() { return BitExtract(DCB_SYNC_DONE_10_REG, DCB_SYNC_DONE_10_MASK, DCB_SYNC_DONE_10_OFS); };
   // 0x00000040: IDLE_PATTERN_DETECT_09 - Idle pattern detected on slot 9
   unsigned int GetIdlePatternDetect09() { return BitExtract(DCB_IDLE_PATTERN_DETECT_09_REG, DCB_IDLE_PATTERN_DETECT_09_MASK, DCB_IDLE_PATTERN_DETECT_09_OFS); };
   // 0x00000020: DELAY_SYNC_DONE_09 - Delay syncronization procedure completed for slot 9
   unsigned int GetDelaySyncDone09() { return BitExtract(DCB_DELAY_SYNC_DONE_09_REG, DCB_DELAY_SYNC_DONE_09_MASK, DCB_DELAY_SYNC_DONE_09_OFS); };
   // 0x00000010: SYNC_DONE_09 - Overall syncronization procedure completed for slot 9
   unsigned int GetSyncDone09() { return BitExtract(DCB_SYNC_DONE_09_REG, DCB_SYNC_DONE_09_MASK, DCB_SYNC_DONE_09_OFS); };
   // 0x00000004: IDLE_PATTERN_DETECT_08 - Idle pattern detected on slot 8
   unsigned int GetIdlePatternDetect08() { return BitExtract(DCB_IDLE_PATTERN_DETECT_08_REG, DCB_IDLE_PATTERN_DETECT_08_MASK, DCB_IDLE_PATTERN_DETECT_08_OFS); };
   // 0x00000002: DELAY_SYNC_DONE_08 - Delay syncronization procedure completed for slot 8
   unsigned int GetDelaySyncDone08() { return BitExtract(DCB_DELAY_SYNC_DONE_08_REG, DCB_DELAY_SYNC_DONE_08_MASK, DCB_DELAY_SYNC_DONE_08_OFS); };
   // 0x00000001: SYNC_DONE_08 - Overall syncronization procedure completed for slot 8
   unsigned int GetSyncDone08() { return BitExtract(DCB_SYNC_DONE_08_REG, DCB_SYNC_DONE_08_MASK, DCB_SYNC_DONE_08_OFS); };


   ////// ------ Register 24 [0x0060]: SERDES_STATUS_17 - Input Serdes status for slot 17 (TCB slot) (Default: 0x00000000) ------ //////

   // 0x00000004: IDLE_PATTERN_DETECT_17 - Idle pattern detected on slot 17
   unsigned int GetIdlePatternDetect17() { return BitExtract(DCB_IDLE_PATTERN_DETECT_17_REG, DCB_IDLE_PATTERN_DETECT_17_MASK, DCB_IDLE_PATTERN_DETECT_17_OFS); };
   // 0x00000002: DELAY_SYNC_DONE_17 - Delay syncronization procedure completed for slot 17
   unsigned int GetDelaySyncDone17() { return BitExtract(DCB_DELAY_SYNC_DONE_17_REG, DCB_DELAY_SYNC_DONE_17_MASK, DCB_DELAY_SYNC_DONE_17_OFS); };
   // 0x00000001: SYNC_DONE_17 - Overall syncronization procedure completed for slot 17
   unsigned int GetSyncDone17() { return BitExtract(DCB_SYNC_DONE_17_REG, DCB_SYNC_DONE_17_MASK, DCB_SYNC_DONE_17_OFS); };


   ////// ------ Register 25 [0x0064]: SERDES_ERR_CNT_00 - Input Serdes error count for slot 0 (Default: 0x00000000) ------ //////
>>>>>>> Stashed changes

   // 0xFF000000: CRC_ERRORS_00 - CRC error count of input serdes on slot 0 (255 = overflow)
   unsigned int GetCrcErrors00() { return BitExtract(DCB_CRC_ERRORS_00_REG, DCB_CRC_ERRORS_00_MASK, DCB_CRC_ERRORS_00_OFS); };
   // 0x00FF0000: FRAME_ERRORS_00 - Frame error count of input serdes on slot 0 (255 = overflow)
   unsigned int GetFrameErrors00() { return BitExtract(DCB_FRAME_ERRORS_00_REG, DCB_FRAME_ERRORS_00_MASK, DCB_FRAME_ERRORS_00_OFS); };
   // 0x0000FF00: DATAGRAM_ERRORS_00 - Datagram error count of input serdes on slot 0 (255 = overflow)
   unsigned int GetDatagramErrors00() { return BitExtract(DCB_DATAGRAM_ERRORS_00_REG, DCB_DATAGRAM_ERRORS_00_MASK, DCB_DATAGRAM_ERRORS_00_OFS); };
   // 0x000000FF: SYNC_ERRORS_00 - Sync error count of input serdes on slot 0 (255 = overflow)
   unsigned int GetSyncErrors00() { return BitExtract(DCB_SYNC_ERRORS_00_REG, DCB_SYNC_ERRORS_00_MASK, DCB_SYNC_ERRORS_00_OFS); };


<<<<<<< Updated upstream
   ////// ------ Register 24 [0x0060]: APLY_CFG - Apply settings from regsiter bank to hardware units (Default: 0x00000000) ------ //////
=======
   ////// ------ Register 26 [0x0068]: SERDES_ERR_CNT_01 - Input Serdes error count for slot 1 (Default: 0x00000000) ------ //////

   // 0xFF000000: CRC_ERRORS_01 - CRC error count of input serdes on slot 1 (255 = overflow)
   unsigned int GetCrcErrors01() { return BitExtract(DCB_CRC_ERRORS_01_REG, DCB_CRC_ERRORS_01_MASK, DCB_CRC_ERRORS_01_OFS); };
   // 0x00FF0000: FRAME_ERRORS_01 - Frame error count of input serdes on slot 1 (255 = overflow)
   unsigned int GetFrameErrors01() { return BitExtract(DCB_FRAME_ERRORS_01_REG, DCB_FRAME_ERRORS_01_MASK, DCB_FRAME_ERRORS_01_OFS); };
   // 0x0000FF00: DATAGRAM_ERRORS_01 - Datagram error count of input serdes on slot 1 (255 = overflow)
   unsigned int GetDatagramErrors01() { return BitExtract(DCB_DATAGRAM_ERRORS_01_REG, DCB_DATAGRAM_ERRORS_01_MASK, DCB_DATAGRAM_ERRORS_01_OFS); };
   // 0x000000FF: SYNC_ERRORS_01 - Sync error count of input serdes on slot 1 (255 = overflow)
   unsigned int GetSyncErrors01() { return BitExtract(DCB_SYNC_ERRORS_01_REG, DCB_SYNC_ERRORS_01_MASK, DCB_SYNC_ERRORS_01_OFS); };


   ////// ------ Register 27 [0x006C]: SERDES_ERR_CNT_02 - Input Serdes error count for slot 2 (Default: 0x00000000) ------ //////

   // 0xFF000000: CRC_ERRORS_02 - CRC error count of input serdes on slot 2 (255 = overflow)
   unsigned int GetCrcErrors02() { return BitExtract(DCB_CRC_ERRORS_02_REG, DCB_CRC_ERRORS_02_MASK, DCB_CRC_ERRORS_02_OFS); };
   // 0x00FF0000: FRAME_ERRORS_02 - Frame error count of input serdes on slot 2 (255 = overflow)
   unsigned int GetFrameErrors02() { return BitExtract(DCB_FRAME_ERRORS_02_REG, DCB_FRAME_ERRORS_02_MASK, DCB_FRAME_ERRORS_02_OFS); };
   // 0x0000FF00: DATAGRAM_ERRORS_02 - Datagram error count of input serdes on slot 2 (255 = overflow)
   unsigned int GetDatagramErrors02() { return BitExtract(DCB_DATAGRAM_ERRORS_02_REG, DCB_DATAGRAM_ERRORS_02_MASK, DCB_DATAGRAM_ERRORS_02_OFS); };
   // 0x000000FF: SYNC_ERRORS_02 - Sync error count of input serdes on slot 2 (255 = overflow)
   unsigned int GetSyncErrors02() { return BitExtract(DCB_SYNC_ERRORS_02_REG, DCB_SYNC_ERRORS_02_MASK, DCB_SYNC_ERRORS_02_OFS); };


   ////// ------ Register 28 [0x0070]: SERDES_ERR_CNT_03 - Input Serdes error count for slot 3 (Default: 0x00000000) ------ //////

   // 0xFF000000: CRC_ERRORS_03 - CRC error count of input serdes on slot 3 (255 = overflow)
   unsigned int GetCrcErrors03() { return BitExtract(DCB_CRC_ERRORS_03_REG, DCB_CRC_ERRORS_03_MASK, DCB_CRC_ERRORS_03_OFS); };
   // 0x00FF0000: FRAME_ERRORS_03 - Frame error count of input serdes on slot 3 (255 = overflow)
   unsigned int GetFrameErrors03() { return BitExtract(DCB_FRAME_ERRORS_03_REG, DCB_FRAME_ERRORS_03_MASK, DCB_FRAME_ERRORS_03_OFS); };
   // 0x0000FF00: DATAGRAM_ERRORS_03 - Datagram error count of input serdes on slot 3 (255 = overflow)
   unsigned int GetDatagramErrors03() { return BitExtract(DCB_DATAGRAM_ERRORS_03_REG, DCB_DATAGRAM_ERRORS_03_MASK, DCB_DATAGRAM_ERRORS_03_OFS); };
   // 0x000000FF: SYNC_ERRORS_03 - Sync error count of input serdes on slot 3 (255 = overflow)
   unsigned int GetSyncErrors03() { return BitExtract(DCB_SYNC_ERRORS_03_REG, DCB_SYNC_ERRORS_03_MASK, DCB_SYNC_ERRORS_03_OFS); };


   ////// ------ Register 29 [0x0074]: SERDES_ERR_CNT_04 - Input Serdes error count for slot 4 (Default: 0x00000000) ------ //////

   // 0xFF000000: CRC_ERRORS_04 - CRC error count of input serdes on slot 4 (255 = overflow)
   unsigned int GetCrcErrors04() { return BitExtract(DCB_CRC_ERRORS_04_REG, DCB_CRC_ERRORS_04_MASK, DCB_CRC_ERRORS_04_OFS); };
   // 0x00FF0000: FRAME_ERRORS_04 - Frame error count of input serdes on slot 4 (255 = overflow)
   unsigned int GetFrameErrors04() { return BitExtract(DCB_FRAME_ERRORS_04_REG, DCB_FRAME_ERRORS_04_MASK, DCB_FRAME_ERRORS_04_OFS); };
   // 0x0000FF00: DATAGRAM_ERRORS_04 - Datagram error count of input serdes on slot 4 (255 = overflow)
   unsigned int GetDatagramErrors04() { return BitExtract(DCB_DATAGRAM_ERRORS_04_REG, DCB_DATAGRAM_ERRORS_04_MASK, DCB_DATAGRAM_ERRORS_04_OFS); };
   // 0x000000FF: SYNC_ERRORS_04 - Sync error count of input serdes on slot 4 (255 = overflow)
   unsigned int GetSyncErrors04() { return BitExtract(DCB_SYNC_ERRORS_04_REG, DCB_SYNC_ERRORS_04_MASK, DCB_SYNC_ERRORS_04_OFS); };


   ////// ------ Register 30 [0x0078]: SERDES_ERR_CNT_05 - Input Serdes error count for slot 5 (Default: 0x00000000) ------ //////

   // 0xFF000000: CRC_ERRORS_05 - CRC error count of input serdes on slot 5 (255 = overflow)
   unsigned int GetCrcErrors05() { return BitExtract(DCB_CRC_ERRORS_05_REG, DCB_CRC_ERRORS_05_MASK, DCB_CRC_ERRORS_05_OFS); };
   // 0x00FF0000: FRAME_ERRORS_05 - Frame error count of input serdes on slot 5 (255 = overflow)
   unsigned int GetFrameErrors05() { return BitExtract(DCB_FRAME_ERRORS_05_REG, DCB_FRAME_ERRORS_05_MASK, DCB_FRAME_ERRORS_05_OFS); };
   // 0x0000FF00: DATAGRAM_ERRORS_05 - Datagram error count of input serdes on slot 5 (255 = overflow)
   unsigned int GetDatagramErrors05() { return BitExtract(DCB_DATAGRAM_ERRORS_05_REG, DCB_DATAGRAM_ERRORS_05_MASK, DCB_DATAGRAM_ERRORS_05_OFS); };
   // 0x000000FF: SYNC_ERRORS_05 - Sync error count of input serdes on slot 5 (255 = overflow)
   unsigned int GetSyncErrors05() { return BitExtract(DCB_SYNC_ERRORS_05_REG, DCB_SYNC_ERRORS_05_MASK, DCB_SYNC_ERRORS_05_OFS); };


   ////// ------ Register 31 [0x007C]: SERDES_ERR_CNT_06 - Input Serdes error count for slot 6 (Default: 0x00000000) ------ //////

   // 0xFF000000: CRC_ERRORS_06 - CRC error count of input serdes on slot 6 (255 = overflow)
   unsigned int GetCrcErrors06() { return BitExtract(DCB_CRC_ERRORS_06_REG, DCB_CRC_ERRORS_06_MASK, DCB_CRC_ERRORS_06_OFS); };
   // 0x00FF0000: FRAME_ERRORS_06 - Frame error count of input serdes on slot 6 (255 = overflow)
   unsigned int GetFrameErrors06() { return BitExtract(DCB_FRAME_ERRORS_06_REG, DCB_FRAME_ERRORS_06_MASK, DCB_FRAME_ERRORS_06_OFS); };
   // 0x0000FF00: DATAGRAM_ERRORS_06 - Datagram error count of input serdes on slot 6 (255 = overflow)
   unsigned int GetDatagramErrors06() { return BitExtract(DCB_DATAGRAM_ERRORS_06_REG, DCB_DATAGRAM_ERRORS_06_MASK, DCB_DATAGRAM_ERRORS_06_OFS); };
   // 0x000000FF: SYNC_ERRORS_06 - Sync error count of input serdes on slot 6 (255 = overflow)
   unsigned int GetSyncErrors06() { return BitExtract(DCB_SYNC_ERRORS_06_REG, DCB_SYNC_ERRORS_06_MASK, DCB_SYNC_ERRORS_06_OFS); };


   ////// ------ Register 32 [0x0080]: SERDES_ERR_CNT_07 - Input Serdes error count for slot 7 (Default: 0x00000000) ------ //////

   // 0xFF000000: CRC_ERRORS_07 - CRC error count of input serdes on slot 7 (255 = overflow)
   unsigned int GetCrcErrors07() { return BitExtract(DCB_CRC_ERRORS_07_REG, DCB_CRC_ERRORS_07_MASK, DCB_CRC_ERRORS_07_OFS); };
   // 0x00FF0000: FRAME_ERRORS_07 - Frame error count of input serdes on slot 7 (255 = overflow)
   unsigned int GetFrameErrors07() { return BitExtract(DCB_FRAME_ERRORS_07_REG, DCB_FRAME_ERRORS_07_MASK, DCB_FRAME_ERRORS_07_OFS); };
   // 0x0000FF00: DATAGRAM_ERRORS_07 - Datagram error count of input serdes on slot 7 (255 = overflow)
   unsigned int GetDatagramErrors07() { return BitExtract(DCB_DATAGRAM_ERRORS_07_REG, DCB_DATAGRAM_ERRORS_07_MASK, DCB_DATAGRAM_ERRORS_07_OFS); };
   // 0x000000FF: SYNC_ERRORS_07 - Sync error count of input serdes on slot 7 (255 = overflow)
   unsigned int GetSyncErrors07() { return BitExtract(DCB_SYNC_ERRORS_07_REG, DCB_SYNC_ERRORS_07_MASK, DCB_SYNC_ERRORS_07_OFS); };


   ////// ------ Register 33 [0x0084]: SERDES_ERR_CNT_08 - Input Serdes error count for slot 8 (Default: 0x00000000) ------ //////

   // 0xFF000000: CRC_ERRORS_08 - CRC error count of input serdes on slot 8 (255 = overflow)
   unsigned int GetCrcErrors08() { return BitExtract(DCB_CRC_ERRORS_08_REG, DCB_CRC_ERRORS_08_MASK, DCB_CRC_ERRORS_08_OFS); };
   // 0x00FF0000: FRAME_ERRORS_08 - Frame error count of input serdes on slot 8 (255 = overflow)
   unsigned int GetFrameErrors08() { return BitExtract(DCB_FRAME_ERRORS_08_REG, DCB_FRAME_ERRORS_08_MASK, DCB_FRAME_ERRORS_08_OFS); };
   // 0x0000FF00: DATAGRAM_ERRORS_08 - Datagram error count of input serdes on slot 8 (255 = overflow)
   unsigned int GetDatagramErrors08() { return BitExtract(DCB_DATAGRAM_ERRORS_08_REG, DCB_DATAGRAM_ERRORS_08_MASK, DCB_DATAGRAM_ERRORS_08_OFS); };
   // 0x000000FF: SYNC_ERRORS_08 - Sync error count of input serdes on slot 8 (255 = overflow)
   unsigned int GetSyncErrors08() { return BitExtract(DCB_SYNC_ERRORS_08_REG, DCB_SYNC_ERRORS_08_MASK, DCB_SYNC_ERRORS_08_OFS); };


   ////// ------ Register 34 [0x0088]: SERDES_ERR_CNT_09 - Input Serdes error count for slot 9 (Default: 0x00000000) ------ //////

   // 0xFF000000: CRC_ERRORS_09 - CRC error count of input serdes on slot 9 (255 = overflow)
   unsigned int GetCrcErrors09() { return BitExtract(DCB_CRC_ERRORS_09_REG, DCB_CRC_ERRORS_09_MASK, DCB_CRC_ERRORS_09_OFS); };
   // 0x00FF0000: FRAME_ERRORS_09 - Frame error count of input serdes on slot 9 (255 = overflow)
   unsigned int GetFrameErrors09() { return BitExtract(DCB_FRAME_ERRORS_09_REG, DCB_FRAME_ERRORS_09_MASK, DCB_FRAME_ERRORS_09_OFS); };
   // 0x0000FF00: DATAGRAM_ERRORS_09 - Datagram error count of input serdes on slot 9 (255 = overflow)
   unsigned int GetDatagramErrors09() { return BitExtract(DCB_DATAGRAM_ERRORS_09_REG, DCB_DATAGRAM_ERRORS_09_MASK, DCB_DATAGRAM_ERRORS_09_OFS); };
   // 0x000000FF: SYNC_ERRORS_09 - Sync error count of input serdes on slot 9 (255 = overflow)
   unsigned int GetSyncErrors09() { return BitExtract(DCB_SYNC_ERRORS_09_REG, DCB_SYNC_ERRORS_09_MASK, DCB_SYNC_ERRORS_09_OFS); };


   ////// ------ Register 35 [0x008C]: SERDES_ERR_CNT_10 - Input Serdes error count for slot 10 (Default: 0x00000000) ------ //////

   // 0xFF000000: CRC_ERRORS_10 - CRC error count of input serdes on slot 10 (255 = overflow)
   unsigned int GetCrcErrors10() { return BitExtract(DCB_CRC_ERRORS_10_REG, DCB_CRC_ERRORS_10_MASK, DCB_CRC_ERRORS_10_OFS); };
   // 0x00FF0000: FRAME_ERRORS_10 - Frame error count of input serdes on slot 10 (255 = overflow)
   unsigned int GetFrameErrors10() { return BitExtract(DCB_FRAME_ERRORS_10_REG, DCB_FRAME_ERRORS_10_MASK, DCB_FRAME_ERRORS_10_OFS); };
   // 0x0000FF00: DATAGRAM_ERRORS_10 - Datagram error count of input serdes on slot 10 (255 = overflow)
   unsigned int GetDatagramErrors10() { return BitExtract(DCB_DATAGRAM_ERRORS_10_REG, DCB_DATAGRAM_ERRORS_10_MASK, DCB_DATAGRAM_ERRORS_10_OFS); };
   // 0x000000FF: SYNC_ERRORS_10 - Sync error count of input serdes on slot 10 (255 = overflow)
   unsigned int GetSyncErrors10() { return BitExtract(DCB_SYNC_ERRORS_10_REG, DCB_SYNC_ERRORS_10_MASK, DCB_SYNC_ERRORS_10_OFS); };


   ////// ------ Register 36 [0x0090]: SERDES_ERR_CNT_11 - Input Serdes error count for slot 11 (Default: 0x00000000) ------ //////

   // 0xFF000000: CRC_ERRORS_11 - CRC error count of input serdes on slot 11 (255 = overflow)
   unsigned int GetCrcErrors11() { return BitExtract(DCB_CRC_ERRORS_11_REG, DCB_CRC_ERRORS_11_MASK, DCB_CRC_ERRORS_11_OFS); };
   // 0x00FF0000: FRAME_ERRORS_11 - Frame error count of input serdes on slot 11 (255 = overflow)
   unsigned int GetFrameErrors11() { return BitExtract(DCB_FRAME_ERRORS_11_REG, DCB_FRAME_ERRORS_11_MASK, DCB_FRAME_ERRORS_11_OFS); };
   // 0x0000FF00: DATAGRAM_ERRORS_11 - Datagram error count of input serdes on slot 11 (255 = overflow)
   unsigned int GetDatagramErrors11() { return BitExtract(DCB_DATAGRAM_ERRORS_11_REG, DCB_DATAGRAM_ERRORS_11_MASK, DCB_DATAGRAM_ERRORS_11_OFS); };
   // 0x000000FF: SYNC_ERRORS_11 - Sync error count of input serdes on slot 11 (255 = overflow)
   unsigned int GetSyncErrors11() { return BitExtract(DCB_SYNC_ERRORS_11_REG, DCB_SYNC_ERRORS_11_MASK, DCB_SYNC_ERRORS_11_OFS); };


   ////// ------ Register 37 [0x0094]: SERDES_ERR_CNT_12 - Input Serdes error count for slot 12 (Default: 0x00000000) ------ //////

   // 0xFF000000: CRC_ERRORS_12 - CRC error count of input serdes on slot 12 (255 = overflow)
   unsigned int GetCrcErrors12() { return BitExtract(DCB_CRC_ERRORS_12_REG, DCB_CRC_ERRORS_12_MASK, DCB_CRC_ERRORS_12_OFS); };
   // 0x00FF0000: FRAME_ERRORS_12 - Frame error count of input serdes on slot 12 (255 = overflow)
   unsigned int GetFrameErrors12() { return BitExtract(DCB_FRAME_ERRORS_12_REG, DCB_FRAME_ERRORS_12_MASK, DCB_FRAME_ERRORS_12_OFS); };
   // 0x0000FF00: DATAGRAM_ERRORS_12 - Datagram error count of input serdes on slot 12 (255 = overflow)
   unsigned int GetDatagramErrors12() { return BitExtract(DCB_DATAGRAM_ERRORS_12_REG, DCB_DATAGRAM_ERRORS_12_MASK, DCB_DATAGRAM_ERRORS_12_OFS); };
   // 0x000000FF: SYNC_ERRORS_12 - Sync error count of input serdes on slot 12 (255 = overflow)
   unsigned int GetSyncErrors12() { return BitExtract(DCB_SYNC_ERRORS_12_REG, DCB_SYNC_ERRORS_12_MASK, DCB_SYNC_ERRORS_12_OFS); };


   ////// ------ Register 38 [0x0098]: SERDES_ERR_CNT_13 - Input Serdes error count for slot 13 (Default: 0x00000000) ------ //////

   // 0xFF000000: CRC_ERRORS_13 - CRC error count of input serdes on slot 13 (255 = overflow)
   unsigned int GetCrcErrors13() { return BitExtract(DCB_CRC_ERRORS_13_REG, DCB_CRC_ERRORS_13_MASK, DCB_CRC_ERRORS_13_OFS); };
   // 0x00FF0000: FRAME_ERRORS_13 - Frame error count of input serdes on slot 13 (255 = overflow)
   unsigned int GetFrameErrors13() { return BitExtract(DCB_FRAME_ERRORS_13_REG, DCB_FRAME_ERRORS_13_MASK, DCB_FRAME_ERRORS_13_OFS); };
   // 0x0000FF00: DATAGRAM_ERRORS_13 - Datagram error count of input serdes on slot 13 (255 = overflow)
   unsigned int GetDatagramErrors13() { return BitExtract(DCB_DATAGRAM_ERRORS_13_REG, DCB_DATAGRAM_ERRORS_13_MASK, DCB_DATAGRAM_ERRORS_13_OFS); };
   // 0x000000FF: SYNC_ERRORS_13 - Sync error count of input serdes on slot 13 (255 = overflow)
   unsigned int GetSyncErrors13() { return BitExtract(DCB_SYNC_ERRORS_13_REG, DCB_SYNC_ERRORS_13_MASK, DCB_SYNC_ERRORS_13_OFS); };


   ////// ------ Register 39 [0x009C]: SERDES_ERR_CNT_14 - Input Serdes error count for slot 14 (Default: 0x00000000) ------ //////

   // 0xFF000000: CRC_ERRORS_14 - CRC error count of input serdes on slot 14 (255 = overflow)
   unsigned int GetCrcErrors14() { return BitExtract(DCB_CRC_ERRORS_14_REG, DCB_CRC_ERRORS_14_MASK, DCB_CRC_ERRORS_14_OFS); };
   // 0x00FF0000: FRAME_ERRORS_14 - Frame error count of input serdes on slot 14 (255 = overflow)
   unsigned int GetFrameErrors14() { return BitExtract(DCB_FRAME_ERRORS_14_REG, DCB_FRAME_ERRORS_14_MASK, DCB_FRAME_ERRORS_14_OFS); };
   // 0x0000FF00: DATAGRAM_ERRORS_14 - Datagram error count of input serdes on slot 14 (255 = overflow)
   unsigned int GetDatagramErrors14() { return BitExtract(DCB_DATAGRAM_ERRORS_14_REG, DCB_DATAGRAM_ERRORS_14_MASK, DCB_DATAGRAM_ERRORS_14_OFS); };
   // 0x000000FF: SYNC_ERRORS_14 - Sync error count of input serdes on slot 14 (255 = overflow)
   unsigned int GetSyncErrors14() { return BitExtract(DCB_SYNC_ERRORS_14_REG, DCB_SYNC_ERRORS_14_MASK, DCB_SYNC_ERRORS_14_OFS); };


   ////// ------ Register 40 [0x00A0]: SERDES_ERR_CNT_15 - Input Serdes error count for slot 15 (Default: 0x00000000) ------ //////

   // 0xFF000000: CRC_ERRORS_15 - CRC error count of input serdes on slot 15 (255 = overflow)
   unsigned int GetCrcErrors15() { return BitExtract(DCB_CRC_ERRORS_15_REG, DCB_CRC_ERRORS_15_MASK, DCB_CRC_ERRORS_15_OFS); };
   // 0x00FF0000: FRAME_ERRORS_15 - Frame error count of input serdes on slot 15 (255 = overflow)
   unsigned int GetFrameErrors15() { return BitExtract(DCB_FRAME_ERRORS_15_REG, DCB_FRAME_ERRORS_15_MASK, DCB_FRAME_ERRORS_15_OFS); };
   // 0x0000FF00: DATAGRAM_ERRORS_15 - Datagram error count of input serdes on slot 15 (255 = overflow)
   unsigned int GetDatagramErrors15() { return BitExtract(DCB_DATAGRAM_ERRORS_15_REG, DCB_DATAGRAM_ERRORS_15_MASK, DCB_DATAGRAM_ERRORS_15_OFS); };
   // 0x000000FF: SYNC_ERRORS_15 - Sync error count of input serdes on slot 15 (255 = overflow)
   unsigned int GetSyncErrors15() { return BitExtract(DCB_SYNC_ERRORS_15_REG, DCB_SYNC_ERRORS_15_MASK, DCB_SYNC_ERRORS_15_OFS); };


   ////// ------ Register 41 [0x00A4]: SERDES_ERR_CNT_17 - Input Serdes error count for slot 17 (TCB slot) (Default: 0x00000000) ------ //////

   // 0xFF000000: CRC_ERRORS_17 - CRC error count of input serdes on slot 17 (255 = overflow)
   unsigned int GetCrcErrors17() { return BitExtract(DCB_CRC_ERRORS_17_REG, DCB_CRC_ERRORS_17_MASK, DCB_CRC_ERRORS_17_OFS); };
   // 0x00FF0000: FRAME_ERRORS_17 - Frame error count of input serdes on slot 17 (255 = overflow)
   unsigned int GetFrameErrors17() { return BitExtract(DCB_FRAME_ERRORS_17_REG, DCB_FRAME_ERRORS_17_MASK, DCB_FRAME_ERRORS_17_OFS); };
   // 0x0000FF00: DATAGRAM_ERRORS_17 - Datagram error count of input serdes on slot 17 (255 = overflow)
   unsigned int GetDatagramErrors17() { return BitExtract(DCB_DATAGRAM_ERRORS_17_REG, DCB_DATAGRAM_ERRORS_17_MASK, DCB_DATAGRAM_ERRORS_17_OFS); };
   // 0x000000FF: SYNC_ERRORS_17 - Sync error count of input serdes on slot 17 (255 = overflow)
   unsigned int GetSyncErrors17() { return BitExtract(DCB_SYNC_ERRORS_17_REG, DCB_SYNC_ERRORS_17_MASK, DCB_SYNC_ERRORS_17_OFS); };


   ////// ------ Register 42 [0x00A8]: APLY_CFG - Apply settings from regsiter bank to hardware units (Default: 0x00000000) ------ //////
>>>>>>> Stashed changes

   // 0x00000001: APPLY_SETTINGS_LMK - Apply configuration from regsiter bank to LMK
   unsigned int GetApplySettingsLmk() { return BitExtract(DCB_APPLY_SETTINGS_LMK_REG, DCB_APPLY_SETTINGS_LMK_MASK, DCB_APPLY_SETTINGS_LMK_OFS); };
   void         SetApplySettingsLmk(unsigned int value) { SetRegMask(DCB_APPLY_SETTINGS_LMK_REG, DCB_APPLY_SETTINGS_LMK_MASK, DCB_APPLY_SETTINGS_LMK_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 25 [0x0064]: LMK_0 - LMK Register 0 (Default: 0x00020100) ------ //////
=======
   ////// ------ Register 43 [0x00AC]: LMK_0 - LMK Register 0 (Default: 0x00020100) ------ //////
>>>>>>> Stashed changes

   // 0x80000000: LMK0_RESET - Resets LMK Registers to Their Power-On State
   unsigned int GetLmk0Reset() { return BitExtract(DCB_LMK0_RESET_REG, DCB_LMK0_RESET_MASK, DCB_LMK0_RESET_OFS); };
   void         SetLmk0Reset(unsigned int value) { SetRegMask(DCB_LMK0_RESET_REG, DCB_LMK0_RESET_MASK, DCB_LMK0_RESET_OFS, value); };

   // 0x00060000: LMK0_CLKOUT_MUX - Channel 0 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed)
   unsigned int GetLmk0ClkoutMux() { return BitExtract(DCB_LMK0_CLKOUT_MUX_REG, DCB_LMK0_CLKOUT_MUX_MASK, DCB_LMK0_CLKOUT_MUX_OFS); };
   void         SetLmk0ClkoutMux(unsigned int value) { SetRegMask(DCB_LMK0_CLKOUT_MUX_REG, DCB_LMK0_CLKOUT_MUX_MASK, DCB_LMK0_CLKOUT_MUX_OFS, value); };

   // 0x00010000: LMK0_CLKOUT_EN - Channel 0 Clock Output Enable (0 = Disabled, 1 = Enabled)
   unsigned int GetLmk0ClkoutEn() { return BitExtract(DCB_LMK0_CLKOUT_EN_REG, DCB_LMK0_CLKOUT_EN_MASK, DCB_LMK0_CLKOUT_EN_OFS); };
   void         SetLmk0ClkoutEn(unsigned int value) { SetRegMask(DCB_LMK0_CLKOUT_EN_REG, DCB_LMK0_CLKOUT_EN_MASK, DCB_LMK0_CLKOUT_EN_OFS, value); };

   // 0x0000FF00: LMK0_CLKOUT_DIV - Channel 0 Clock Output Divider (value x 2) (1..255)
   unsigned int GetLmk0ClkoutDiv() { return BitExtract(DCB_LMK0_CLKOUT_DIV_REG, DCB_LMK0_CLKOUT_DIV_MASK, DCB_LMK0_CLKOUT_DIV_OFS); };
   void         SetLmk0ClkoutDiv(unsigned int value) { SetRegMask(DCB_LMK0_CLKOUT_DIV_REG, DCB_LMK0_CLKOUT_DIV_MASK, DCB_LMK0_CLKOUT_DIV_OFS, value); };

   // 0x000000F0: LMK0_CLKOUT_DLY - Channel 0 Clock Output Delay (value x 150ps)
   unsigned int GetLmk0ClkoutDly() { return BitExtract(DCB_LMK0_CLKOUT_DLY_REG, DCB_LMK0_CLKOUT_DLY_MASK, DCB_LMK0_CLKOUT_DLY_OFS); };
   void         SetLmk0ClkoutDly(unsigned int value) { SetRegMask(DCB_LMK0_CLKOUT_DLY_REG, DCB_LMK0_CLKOUT_DLY_MASK, DCB_LMK0_CLKOUT_DLY_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 26 [0x0068]: LMK_1 - LMK Register 1 (Default: 0x00030101) ------ //////
=======
   ////// ------ Register 44 [0x00B0]: LMK_1 - LMK Register 1 (Default: 0x00030101) ------ //////
>>>>>>> Stashed changes

   // 0x00060000: LMK1_CLKOUT_MUX - Channel 1 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed)
   unsigned int GetLmk1ClkoutMux() { return BitExtract(DCB_LMK1_CLKOUT_MUX_REG, DCB_LMK1_CLKOUT_MUX_MASK, DCB_LMK1_CLKOUT_MUX_OFS); };
   void         SetLmk1ClkoutMux(unsigned int value) { SetRegMask(DCB_LMK1_CLKOUT_MUX_REG, DCB_LMK1_CLKOUT_MUX_MASK, DCB_LMK1_CLKOUT_MUX_OFS, value); };

   // 0x00010000: LMK1_CLKOUT_EN - Channel 1 Clock Output Enable (0 = Disabled, 1 = Enabled)
   unsigned int GetLmk1ClkoutEn() { return BitExtract(DCB_LMK1_CLKOUT_EN_REG, DCB_LMK1_CLKOUT_EN_MASK, DCB_LMK1_CLKOUT_EN_OFS); };
   void         SetLmk1ClkoutEn(unsigned int value) { SetRegMask(DCB_LMK1_CLKOUT_EN_REG, DCB_LMK1_CLKOUT_EN_MASK, DCB_LMK1_CLKOUT_EN_OFS, value); };

   // 0x0000FF00: LMK1_CLKOUT_DIV - Channel 1 Clock Output Divider (value x 2) (1..255)
   unsigned int GetLmk1ClkoutDiv() { return BitExtract(DCB_LMK1_CLKOUT_DIV_REG, DCB_LMK1_CLKOUT_DIV_MASK, DCB_LMK1_CLKOUT_DIV_OFS); };
   void         SetLmk1ClkoutDiv(unsigned int value) { SetRegMask(DCB_LMK1_CLKOUT_DIV_REG, DCB_LMK1_CLKOUT_DIV_MASK, DCB_LMK1_CLKOUT_DIV_OFS, value); };

   // 0x000000F0: LMK1_CLKOUT_DLY - Channel 1 Clock Output Delay (value x 150ps)
   unsigned int GetLmk1ClkoutDly() { return BitExtract(DCB_LMK1_CLKOUT_DLY_REG, DCB_LMK1_CLKOUT_DLY_MASK, DCB_LMK1_CLKOUT_DLY_OFS); };
   void         SetLmk1ClkoutDly(unsigned int value) { SetRegMask(DCB_LMK1_CLKOUT_DLY_REG, DCB_LMK1_CLKOUT_DLY_MASK, DCB_LMK1_CLKOUT_DLY_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 27 [0x006C]: LMK_2 - LMK Register 2 (Default: 0x00020102) ------ //////
=======
   ////// ------ Register 45 [0x00B4]: LMK_2 - LMK Register 2 (Default: 0x00020102) ------ //////
>>>>>>> Stashed changes

   // 0x00060000: LMK2_CLKOUT_MUX - Channel 2 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed)
   unsigned int GetLmk2ClkoutMux() { return BitExtract(DCB_LMK2_CLKOUT_MUX_REG, DCB_LMK2_CLKOUT_MUX_MASK, DCB_LMK2_CLKOUT_MUX_OFS); };
   void         SetLmk2ClkoutMux(unsigned int value) { SetRegMask(DCB_LMK2_CLKOUT_MUX_REG, DCB_LMK2_CLKOUT_MUX_MASK, DCB_LMK2_CLKOUT_MUX_OFS, value); };

   // 0x00010000: LMK2_CLKOUT_EN - Channel 2 Clock Output Enable (0 = Disabled, 1 = Enabled)
   unsigned int GetLmk2ClkoutEn() { return BitExtract(DCB_LMK2_CLKOUT_EN_REG, DCB_LMK2_CLKOUT_EN_MASK, DCB_LMK2_CLKOUT_EN_OFS); };
   void         SetLmk2ClkoutEn(unsigned int value) { SetRegMask(DCB_LMK2_CLKOUT_EN_REG, DCB_LMK2_CLKOUT_EN_MASK, DCB_LMK2_CLKOUT_EN_OFS, value); };

   // 0x0000FF00: LMK2_CLKOUT_DIV - Channel 2 Clock Output Divider (value x 2) (1..255)
   unsigned int GetLmk2ClkoutDiv() { return BitExtract(DCB_LMK2_CLKOUT_DIV_REG, DCB_LMK2_CLKOUT_DIV_MASK, DCB_LMK2_CLKOUT_DIV_OFS); };
   void         SetLmk2ClkoutDiv(unsigned int value) { SetRegMask(DCB_LMK2_CLKOUT_DIV_REG, DCB_LMK2_CLKOUT_DIV_MASK, DCB_LMK2_CLKOUT_DIV_OFS, value); };

   // 0x000000F0: LMK2_CLKOUT_DLY - Channel 2 Clock Output Delay (value x 150ps)
   unsigned int GetLmk2ClkoutDly() { return BitExtract(DCB_LMK2_CLKOUT_DLY_REG, DCB_LMK2_CLKOUT_DLY_MASK, DCB_LMK2_CLKOUT_DLY_OFS); };
   void         SetLmk2ClkoutDly(unsigned int value) { SetRegMask(DCB_LMK2_CLKOUT_DLY_REG, DCB_LMK2_CLKOUT_DLY_MASK, DCB_LMK2_CLKOUT_DLY_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 28 [0x0070]: LMK_3 - LMK Register 3 (Default: 0x00020103) ------ //////
=======
   ////// ------ Register 46 [0x00B8]: LMK_3 - LMK Register 3 (Default: 0x00020103) ------ //////
>>>>>>> Stashed changes

   // 0x00060000: LMK3_CLKOUT_MUX - Channel 3 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed)
   unsigned int GetLmk3ClkoutMux() { return BitExtract(DCB_LMK3_CLKOUT_MUX_REG, DCB_LMK3_CLKOUT_MUX_MASK, DCB_LMK3_CLKOUT_MUX_OFS); };
   void         SetLmk3ClkoutMux(unsigned int value) { SetRegMask(DCB_LMK3_CLKOUT_MUX_REG, DCB_LMK3_CLKOUT_MUX_MASK, DCB_LMK3_CLKOUT_MUX_OFS, value); };

   // 0x00010000: LMK3_CLKOUT_EN - Channel 3 Clock Output Enable (0 = Disabled, 1 = Enabled)
   unsigned int GetLmk3ClkoutEn() { return BitExtract(DCB_LMK3_CLKOUT_EN_REG, DCB_LMK3_CLKOUT_EN_MASK, DCB_LMK3_CLKOUT_EN_OFS); };
   void         SetLmk3ClkoutEn(unsigned int value) { SetRegMask(DCB_LMK3_CLKOUT_EN_REG, DCB_LMK3_CLKOUT_EN_MASK, DCB_LMK3_CLKOUT_EN_OFS, value); };

   // 0x0000FF00: LMK3_CLKOUT_DIV - Channel 3 Clock Output Divider (value x 2) (1..255)
   unsigned int GetLmk3ClkoutDiv() { return BitExtract(DCB_LMK3_CLKOUT_DIV_REG, DCB_LMK3_CLKOUT_DIV_MASK, DCB_LMK3_CLKOUT_DIV_OFS); };
   void         SetLmk3ClkoutDiv(unsigned int value) { SetRegMask(DCB_LMK3_CLKOUT_DIV_REG, DCB_LMK3_CLKOUT_DIV_MASK, DCB_LMK3_CLKOUT_DIV_OFS, value); };

   // 0x000000F0: LMK3_CLKOUT_DLY - Channel 3 Clock Output Delay (value x 150ps)
   unsigned int GetLmk3ClkoutDly() { return BitExtract(DCB_LMK3_CLKOUT_DLY_REG, DCB_LMK3_CLKOUT_DLY_MASK, DCB_LMK3_CLKOUT_DLY_OFS); };
   void         SetLmk3ClkoutDly(unsigned int value) { SetRegMask(DCB_LMK3_CLKOUT_DLY_REG, DCB_LMK3_CLKOUT_DLY_MASK, DCB_LMK3_CLKOUT_DLY_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 29 [0x0074]: LMK_4 - LMK Register 4 (Default: 0x00000104) ------ //////
=======
   ////// ------ Register 47 [0x00BC]: LMK_4 - LMK Register 4 (Default: 0x00000104) ------ //////
>>>>>>> Stashed changes

   // 0x00060000: LMK4_CLKOUT_MUX - Channel 4 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed)
   unsigned int GetLmk4ClkoutMux() { return BitExtract(DCB_LMK4_CLKOUT_MUX_REG, DCB_LMK4_CLKOUT_MUX_MASK, DCB_LMK4_CLKOUT_MUX_OFS); };
   void         SetLmk4ClkoutMux(unsigned int value) { SetRegMask(DCB_LMK4_CLKOUT_MUX_REG, DCB_LMK4_CLKOUT_MUX_MASK, DCB_LMK4_CLKOUT_MUX_OFS, value); };

   // 0x00010000: LMK4_CLKOUT_EN - Channel 4 Clock Output Enable (0 = Disabled, 1 = Enabled)
   unsigned int GetLmk4ClkoutEn() { return BitExtract(DCB_LMK4_CLKOUT_EN_REG, DCB_LMK4_CLKOUT_EN_MASK, DCB_LMK4_CLKOUT_EN_OFS); };
   void         SetLmk4ClkoutEn(unsigned int value) { SetRegMask(DCB_LMK4_CLKOUT_EN_REG, DCB_LMK4_CLKOUT_EN_MASK, DCB_LMK4_CLKOUT_EN_OFS, value); };

   // 0x0000FF00: LMK4_CLKOUT_DIV - Channel 4 Clock Output Divider (value x 2) (1..255)
   unsigned int GetLmk4ClkoutDiv() { return BitExtract(DCB_LMK4_CLKOUT_DIV_REG, DCB_LMK4_CLKOUT_DIV_MASK, DCB_LMK4_CLKOUT_DIV_OFS); };
   void         SetLmk4ClkoutDiv(unsigned int value) { SetRegMask(DCB_LMK4_CLKOUT_DIV_REG, DCB_LMK4_CLKOUT_DIV_MASK, DCB_LMK4_CLKOUT_DIV_OFS, value); };

   // 0x000000F0: LMK4_CLKOUT_DLY - Channel 4 Clock Output Delay (value x 150ps)
   unsigned int GetLmk4ClkoutDly() { return BitExtract(DCB_LMK4_CLKOUT_DLY_REG, DCB_LMK4_CLKOUT_DLY_MASK, DCB_LMK4_CLKOUT_DLY_OFS); };
   void         SetLmk4ClkoutDly(unsigned int value) { SetRegMask(DCB_LMK4_CLKOUT_DLY_REG, DCB_LMK4_CLKOUT_DLY_MASK, DCB_LMK4_CLKOUT_DLY_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 30 [0x0078]: LMK_5 - LMK Register 5 (Default: 0x00000105) ------ //////
=======
   ////// ------ Register 48 [0x00C0]: LMK_5 - LMK Register 5 (Default: 0x00000105) ------ //////
>>>>>>> Stashed changes

   // 0x00060000: LMK5_CLKOUT_MUX - Channel 5 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed)
   unsigned int GetLmk5ClkoutMux() { return BitExtract(DCB_LMK5_CLKOUT_MUX_REG, DCB_LMK5_CLKOUT_MUX_MASK, DCB_LMK5_CLKOUT_MUX_OFS); };
   void         SetLmk5ClkoutMux(unsigned int value) { SetRegMask(DCB_LMK5_CLKOUT_MUX_REG, DCB_LMK5_CLKOUT_MUX_MASK, DCB_LMK5_CLKOUT_MUX_OFS, value); };

   // 0x00010000: LMK5_CLKOUT_EN - Channel 5 Clock Output Enable (0 = Disabled, 1 = Enabled)
   unsigned int GetLmk5ClkoutEn() { return BitExtract(DCB_LMK5_CLKOUT_EN_REG, DCB_LMK5_CLKOUT_EN_MASK, DCB_LMK5_CLKOUT_EN_OFS); };
   void         SetLmk5ClkoutEn(unsigned int value) { SetRegMask(DCB_LMK5_CLKOUT_EN_REG, DCB_LMK5_CLKOUT_EN_MASK, DCB_LMK5_CLKOUT_EN_OFS, value); };

   // 0x0000FF00: LMK5_CLKOUT_DIV - Channel 5 Clock Output Divider (value x 2) (1..255)
   unsigned int GetLmk5ClkoutDiv() { return BitExtract(DCB_LMK5_CLKOUT_DIV_REG, DCB_LMK5_CLKOUT_DIV_MASK, DCB_LMK5_CLKOUT_DIV_OFS); };
   void         SetLmk5ClkoutDiv(unsigned int value) { SetRegMask(DCB_LMK5_CLKOUT_DIV_REG, DCB_LMK5_CLKOUT_DIV_MASK, DCB_LMK5_CLKOUT_DIV_OFS, value); };

   // 0x000000F0: LMK5_CLKOUT_DLY - Channel 5 Clock Output Delay (value x 150ps)
   unsigned int GetLmk5ClkoutDly() { return BitExtract(DCB_LMK5_CLKOUT_DLY_REG, DCB_LMK5_CLKOUT_DLY_MASK, DCB_LMK5_CLKOUT_DLY_OFS); };
   void         SetLmk5ClkoutDly(unsigned int value) { SetRegMask(DCB_LMK5_CLKOUT_DLY_REG, DCB_LMK5_CLKOUT_DLY_MASK, DCB_LMK5_CLKOUT_DLY_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 31 [0x007C]: LMK_6 - LMK Register 6 (Default: 0x00000106) ------ //////
=======
   ////// ------ Register 49 [0x00C4]: LMK_6 - LMK Register 6 (Default: 0x00000106) ------ //////
>>>>>>> Stashed changes

   // 0x00060000: LMK6_CLKOUT_MUX - Channel 6 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed)
   unsigned int GetLmk6ClkoutMux() { return BitExtract(DCB_LMK6_CLKOUT_MUX_REG, DCB_LMK6_CLKOUT_MUX_MASK, DCB_LMK6_CLKOUT_MUX_OFS); };
   void         SetLmk6ClkoutMux(unsigned int value) { SetRegMask(DCB_LMK6_CLKOUT_MUX_REG, DCB_LMK6_CLKOUT_MUX_MASK, DCB_LMK6_CLKOUT_MUX_OFS, value); };

   // 0x00010000: LMK6_CLKOUT_EN - Channel 6 Clock Output Enable (0 = Disabled, 1 = Enabled)
   unsigned int GetLmk6ClkoutEn() { return BitExtract(DCB_LMK6_CLKOUT_EN_REG, DCB_LMK6_CLKOUT_EN_MASK, DCB_LMK6_CLKOUT_EN_OFS); };
   void         SetLmk6ClkoutEn(unsigned int value) { SetRegMask(DCB_LMK6_CLKOUT_EN_REG, DCB_LMK6_CLKOUT_EN_MASK, DCB_LMK6_CLKOUT_EN_OFS, value); };

   // 0x0000FF00: LMK6_CLKOUT_DIV - Channel 6 Clock Output Divider (value x 2) (1..255)
   unsigned int GetLmk6ClkoutDiv() { return BitExtract(DCB_LMK6_CLKOUT_DIV_REG, DCB_LMK6_CLKOUT_DIV_MASK, DCB_LMK6_CLKOUT_DIV_OFS); };
   void         SetLmk6ClkoutDiv(unsigned int value) { SetRegMask(DCB_LMK6_CLKOUT_DIV_REG, DCB_LMK6_CLKOUT_DIV_MASK, DCB_LMK6_CLKOUT_DIV_OFS, value); };

   // 0x000000F0: LMK6_CLKOUT_DLY - Channel 6 Clock Output Delay (value x 150ps)
   unsigned int GetLmk6ClkoutDly() { return BitExtract(DCB_LMK6_CLKOUT_DLY_REG, DCB_LMK6_CLKOUT_DLY_MASK, DCB_LMK6_CLKOUT_DLY_OFS); };
   void         SetLmk6ClkoutDly(unsigned int value) { SetRegMask(DCB_LMK6_CLKOUT_DLY_REG, DCB_LMK6_CLKOUT_DLY_MASK, DCB_LMK6_CLKOUT_DLY_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 32 [0x0080]: LMK_7 - LMK Register 7 (Default: 0x00000107) ------ //////
=======
   ////// ------ Register 50 [0x00C8]: LMK_7 - LMK Register 7 (Default: 0x00000107) ------ //////
>>>>>>> Stashed changes

   // 0x00060000: LMK7_CLKOUT_MUX - Channel 7 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed)
   unsigned int GetLmk7ClkoutMux() { return BitExtract(DCB_LMK7_CLKOUT_MUX_REG, DCB_LMK7_CLKOUT_MUX_MASK, DCB_LMK7_CLKOUT_MUX_OFS); };
   void         SetLmk7ClkoutMux(unsigned int value) { SetRegMask(DCB_LMK7_CLKOUT_MUX_REG, DCB_LMK7_CLKOUT_MUX_MASK, DCB_LMK7_CLKOUT_MUX_OFS, value); };

   // 0x00010000: LMK7_CLKOUT_EN - Channel 7 Clock Output Enable (0 = Disabled, 1 = Enabled)
   unsigned int GetLmk7ClkoutEn() { return BitExtract(DCB_LMK7_CLKOUT_EN_REG, DCB_LMK7_CLKOUT_EN_MASK, DCB_LMK7_CLKOUT_EN_OFS); };
   void         SetLmk7ClkoutEn(unsigned int value) { SetRegMask(DCB_LMK7_CLKOUT_EN_REG, DCB_LMK7_CLKOUT_EN_MASK, DCB_LMK7_CLKOUT_EN_OFS, value); };

   // 0x0000FF00: LMK7_CLKOUT_DIV - Channel 7 Clock Output Divider (value x 2) (1..255)
   unsigned int GetLmk7ClkoutDiv() { return BitExtract(DCB_LMK7_CLKOUT_DIV_REG, DCB_LMK7_CLKOUT_DIV_MASK, DCB_LMK7_CLKOUT_DIV_OFS); };
   void         SetLmk7ClkoutDiv(unsigned int value) { SetRegMask(DCB_LMK7_CLKOUT_DIV_REG, DCB_LMK7_CLKOUT_DIV_MASK, DCB_LMK7_CLKOUT_DIV_OFS, value); };

   // 0x000000F0: LMK7_CLKOUT_DLY - Channel 7 Clock Output Delay (value x 150ps)
   unsigned int GetLmk7ClkoutDly() { return BitExtract(DCB_LMK7_CLKOUT_DLY_REG, DCB_LMK7_CLKOUT_DLY_MASK, DCB_LMK7_CLKOUT_DLY_OFS); };
   void         SetLmk7ClkoutDly(unsigned int value) { SetRegMask(DCB_LMK7_CLKOUT_DLY_REG, DCB_LMK7_CLKOUT_DLY_MASK, DCB_LMK7_CLKOUT_DLY_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 33 [0x0084]: LMK_8 - LMK Register 8 (Default: 0x10000908) ------ //////
=======
   ////// ------ Register 51 [0x00CC]: LMK_8 - LMK Register 8 (Default: 0x10000908) ------ //////
>>>>>>> Stashed changes

   // 0xFFFFFFF0: LMK8_PHASE_NOISE_OPT - Set LMK Register 8 (Phase Noise Optimization)
   unsigned int GetLmk8PhaseNoiseOpt() { return BitExtract(DCB_LMK8_PHASE_NOISE_OPT_REG, DCB_LMK8_PHASE_NOISE_OPT_MASK, DCB_LMK8_PHASE_NOISE_OPT_OFS); };
   void         SetLmk8PhaseNoiseOpt(unsigned int value) { SetRegMask(DCB_LMK8_PHASE_NOISE_OPT_REG, DCB_LMK8_PHASE_NOISE_OPT_MASK, DCB_LMK8_PHASE_NOISE_OPT_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 34 [0x0088]: LMK_9 - LMK Register 9 (Default: 0xA0022A09) ------ //////
=======
   ////// ------ Register 52 [0x00D0]: LMK_9 - LMK Register 9 (Default: 0xA0022A09) ------ //////
>>>>>>> Stashed changes

   // 0x00010000: LMK9_VBOOST - Voltage Level Boost for Clock Outputs
   unsigned int GetLmk9Vboost() { return BitExtract(DCB_LMK9_VBOOST_REG, DCB_LMK9_VBOOST_MASK, DCB_LMK9_VBOOST_OFS); };
   void         SetLmk9Vboost(unsigned int value) { SetRegMask(DCB_LMK9_VBOOST_REG, DCB_LMK9_VBOOST_MASK, DCB_LMK9_VBOOST_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 35 [0x008C]: LMK_11 - LMK Register 11 (Default: 0x0082000B) ------ //////
=======
   ////// ------ Register 53 [0x00D4]: LMK_11 - LMK Register 11 (Default: 0x0082000B) ------ //////
>>>>>>> Stashed changes

   // 0x00008000: LMK11_DIV4 - Divider Enable for Digital Lock Detect Circuit
   unsigned int GetLmk11Div4() { return BitExtract(DCB_LMK11_DIV4_REG, DCB_LMK11_DIV4_MASK, DCB_LMK11_DIV4_OFS); };
   void         SetLmk11Div4(unsigned int value) { SetRegMask(DCB_LMK11_DIV4_REG, DCB_LMK11_DIV4_MASK, DCB_LMK11_DIV4_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 36 [0x0090]: LMK_13 - LMK Register 13 (Default: 0x029400AD) ------ //////
=======
   ////// ------ Register 54 [0x00D8]: LMK_13 - LMK Register 13 (Default: 0x029400AD) ------ //////
>>>>>>> Stashed changes

   // 0x003FC000: LMK13_OSCIN_FREQ - Oscillator Input Calibration Adjustment in MHz (1..200)
   unsigned int GetLmk13OscinFreq() { return BitExtract(DCB_LMK13_OSCIN_FREQ_REG, DCB_LMK13_OSCIN_FREQ_MASK, DCB_LMK13_OSCIN_FREQ_OFS); };
   void         SetLmk13OscinFreq(unsigned int value) { SetRegMask(DCB_LMK13_OSCIN_FREQ_REG, DCB_LMK13_OSCIN_FREQ_MASK, DCB_LMK13_OSCIN_FREQ_OFS, value); };

   // 0x00003800: LMK13_VCO_R4_LF - Value for Internal Loop Filter Resistor R4 (0..4) (see datasheet)
   unsigned int GetLmk13VcoR4Lf() { return BitExtract(DCB_LMK13_VCO_R4_LF_REG, DCB_LMK13_VCO_R4_LF_MASK, DCB_LMK13_VCO_R4_LF_OFS); };
   void         SetLmk13VcoR4Lf(unsigned int value) { SetRegMask(DCB_LMK13_VCO_R4_LF_REG, DCB_LMK13_VCO_R4_LF_MASK, DCB_LMK13_VCO_R4_LF_OFS, value); };

   // 0x00000700: LMK13_VCO_R3_LF - Value for Internal Loop Filter Resistor R3 (0..4) (see datasheet)
   unsigned int GetLmk13VcoR3Lf() { return BitExtract(DCB_LMK13_VCO_R3_LF_REG, DCB_LMK13_VCO_R3_LF_MASK, DCB_LMK13_VCO_R3_LF_OFS); };
   void         SetLmk13VcoR3Lf(unsigned int value) { SetRegMask(DCB_LMK13_VCO_R3_LF_REG, DCB_LMK13_VCO_R3_LF_MASK, DCB_LMK13_VCO_R3_LF_OFS, value); };

   // 0x000000F0: LMK13_VCO_C3_C4_LF - Value for Internal Loop Filter Capacitors C3/C4 (0..11) (see ds)
   unsigned int GetLmk13VcoC3C4Lf() { return BitExtract(DCB_LMK13_VCO_C3_C4_LF_REG, DCB_LMK13_VCO_C3_C4_LF_MASK, DCB_LMK13_VCO_C3_C4_LF_OFS); };
   void         SetLmk13VcoC3C4Lf(unsigned int value) { SetRegMask(DCB_LMK13_VCO_C3_C4_LF_REG, DCB_LMK13_VCO_C3_C4_LF_MASK, DCB_LMK13_VCO_C3_C4_LF_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 37 [0x0094]: LMK_14 - LMK Register 14 (Default: 0x0830140E) ------ //////
=======
   ////// ------ Register 55 [0x00DC]: LMK_14 - LMK Register 14 (Default: 0x0830140E) ------ //////
>>>>>>> Stashed changes

   // 0x10000000: LMK14_EN_FOUT - Enable for the Fout Pin (0 = Disabled, 1 = Enabled)
   unsigned int GetLmk14EnFout() { return BitExtract(DCB_LMK14_EN_FOUT_REG, DCB_LMK14_EN_FOUT_MASK, DCB_LMK14_EN_FOUT_OFS); };
   void         SetLmk14EnFout(unsigned int value) { SetRegMask(DCB_LMK14_EN_FOUT_REG, DCB_LMK14_EN_FOUT_MASK, DCB_LMK14_EN_FOUT_OFS, value); };

   // 0x08000000: LMK14_EN_CLKOUT_GLOBAL - Global Clock Output Enable (0 = All Off, 1 = Normal Operation)
   unsigned int GetLmk14EnClkoutGlobal() { return BitExtract(DCB_LMK14_EN_CLKOUT_GLOBAL_REG, DCB_LMK14_EN_CLKOUT_GLOBAL_MASK, DCB_LMK14_EN_CLKOUT_GLOBAL_OFS); };
   void         SetLmk14EnClkoutGlobal(unsigned int value) { SetRegMask(DCB_LMK14_EN_CLKOUT_GLOBAL_REG, DCB_LMK14_EN_CLKOUT_GLOBAL_MASK, DCB_LMK14_EN_CLKOUT_GLOBAL_OFS, value); };

   // 0x04000000: LMK14_POWERDOWN - Powerdown (0 = Normal Operation, 1 = Device Powered Down)
   unsigned int GetLmk14Powerdown() { return BitExtract(DCB_LMK14_POWERDOWN_REG, DCB_LMK14_POWERDOWN_MASK, DCB_LMK14_POWERDOWN_OFS); };
   void         SetLmk14Powerdown(unsigned int value) { SetRegMask(DCB_LMK14_POWERDOWN_REG, DCB_LMK14_POWERDOWN_MASK, DCB_LMK14_POWERDOWN_OFS, value); };

   // 0x00F00000: LMK14_PLL_MUX - Output Mode of  LD Pin (0..7,9,11)
   unsigned int GetLmk14PllMux() { return BitExtract(DCB_LMK14_PLL_MUX_REG, DCB_LMK14_PLL_MUX_MASK, DCB_LMK14_PLL_MUX_OFS); };
   void         SetLmk14PllMux(unsigned int value) { SetRegMask(DCB_LMK14_PLL_MUX_REG, DCB_LMK14_PLL_MUX_MASK, DCB_LMK14_PLL_MUX_OFS, value); };

   // 0x000FFF00: LMK14_PLL_R - PLL R Divider Value (1..4095)
   unsigned int GetLmk14PllR() { return BitExtract(DCB_LMK14_PLL_R_REG, DCB_LMK14_PLL_R_MASK, DCB_LMK14_PLL_R_OFS); };
   void         SetLmk14PllR(unsigned int value) { SetRegMask(DCB_LMK14_PLL_R_REG, DCB_LMK14_PLL_R_MASK, DCB_LMK14_PLL_R_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 38 [0x0098]: LMK_15 - LMK Register 15 (Default: 0xE000280F) ------ //////
=======
   ////// ------ Register 56 [0x00E0]: LMK_15 - LMK Register 15 (Default: 0xE000280F) ------ //////
>>>>>>> Stashed changes

   // 0xC0000000: LMK15_PLL_CP_GAIN - PLL Charge Pump Gain (see datasheet) (0..4)
   unsigned int GetLmk15PllCpGain() { return BitExtract(DCB_LMK15_PLL_CP_GAIN_REG, DCB_LMK15_PLL_CP_GAIN_MASK, DCB_LMK15_PLL_CP_GAIN_OFS); };
   void         SetLmk15PllCpGain(unsigned int value) { SetRegMask(DCB_LMK15_PLL_CP_GAIN_REG, DCB_LMK15_PLL_CP_GAIN_MASK, DCB_LMK15_PLL_CP_GAIN_OFS, value); };

   // 0x3C000000: LMK15_VCO_DIV - VCO Divider Value (2..8)
   unsigned int GetLmk15VcoDiv() { return BitExtract(DCB_LMK15_VCO_DIV_REG, DCB_LMK15_VCO_DIV_MASK, DCB_LMK15_VCO_DIV_OFS); };
   void         SetLmk15VcoDiv(unsigned int value) { SetRegMask(DCB_LMK15_VCO_DIV_REG, DCB_LMK15_VCO_DIV_MASK, DCB_LMK15_VCO_DIV_OFS, value); };

   // 0x03FFFF00: LMK15_PLL_N - PLL N Divider Value (1..0x3FFFF)
   unsigned int GetLmk15PllN() { return BitExtract(DCB_LMK15_PLL_N_REG, DCB_LMK15_PLL_N_MASK, DCB_LMK15_PLL_N_OFS); };
   void         SetLmk15PllN(unsigned int value) { SetRegMask(DCB_LMK15_PLL_N_REG, DCB_LMK15_PLL_N_MASK, DCB_LMK15_PLL_N_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 39 [0x009C]: TIME_LSB - Current System Time (Default: 0x00000000) ------ //////
=======
   ////// ------ Register 57 [0x00E4]: TIME_LSB - Current System Time (Default: 0x00000000) ------ //////
>>>>>>> Stashed changes

   // 0xFFFFFFFF: TIME_LSB - LSBs of 64bit system time counter (MSBs are latched upon read of LSB register)
   unsigned int GetTimeLsb() { return BitExtract(DCB_TIME_LSB_REG, DCB_TIME_LSB_MASK, DCB_TIME_LSB_OFS); };


<<<<<<< Updated upstream
   ////// ------ Register 40 [0x00A0]: TIME_MSB - Current System Time (Default: 0x00000000) ------ //////
=======
   ////// ------ Register 58 [0x00E8]: TIME_MSB - Current System Time (Default: 0x00000000) ------ //////
>>>>>>> Stashed changes

   // 0xFFFFFFFF: TIME_MSB - MSBs of 64bit system time counter (latched upon read of LSB register)
   unsigned int GetTimeMsb() { return BitExtract(DCB_TIME_MSB_REG, DCB_TIME_MSB_MASK, DCB_TIME_MSB_OFS); };


<<<<<<< Updated upstream
   ////// ------ Register 41 [0x00A4]: TIME_LSB_SET - Set System Time (Default: 0x00000000) ------ //////
=======
   ////// ------ Register 59 [0x00EC]: TIME_LSB_SET - Set System Time (Default: 0x00000000) ------ //////
>>>>>>> Stashed changes

   // 0xFFFFFFFF: TIME_LSB_SET - LSBs of 64bit system time counter set value  (time is updated when MSBs are written)
   unsigned int GetTimeLsbSet() { return BitExtract(DCB_TIME_LSB_SET_REG, DCB_TIME_LSB_SET_MASK, DCB_TIME_LSB_SET_OFS); };
   void         SetTimeLsbSet(unsigned int value) { SetRegMask(DCB_TIME_LSB_SET_REG, DCB_TIME_LSB_SET_MASK, DCB_TIME_LSB_SET_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 42 [0x00A8]: TIME_MSB_SET - Set System Time (Default: 0x00000000) ------ //////
=======
   ////// ------ Register 60 [0x00F0]: TIME_MSB_SET - Set System Time (Default: 0x00000000) ------ //////
>>>>>>> Stashed changes

   // 0xFFFFFFFF: TIME_MSB_SET - MSBs of 64bit system time counter set value  (time is updated when MSBs are written)
   unsigned int GetTimeMsbSet() { return BitExtract(DCB_TIME_MSB_SET_REG, DCB_TIME_MSB_SET_MASK, DCB_TIME_MSB_SET_OFS); };
   void         SetTimeMsbSet(unsigned int value) { SetRegMask(DCB_TIME_MSB_SET_REG, DCB_TIME_MSB_SET_MASK, DCB_TIME_MSB_SET_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 43 [0x00AC]: EVENT_TX_RATE - Event Transmission Rate (Default: 0x00000000) ------ //////
=======
   ////// ------ Register 61 [0x00F4]: EVENT_TX_RATE - Event Transmission Rate (Default: 0x00000000) ------ //////
>>>>>>> Stashed changes

   // 0xFFFFFFFF: EVENT_TX_RATE - Number of events transmitted per second
   unsigned int GetEventTxRate() { return BitExtract(DCB_EVENT_TX_RATE_REG, DCB_EVENT_TX_RATE_MASK, DCB_EVENT_TX_RATE_OFS); };


<<<<<<< Updated upstream
   ////// ------ Register 44 [0x00B0]: EVENT_NR - Number of latest event (Default: 0x00000000) ------ //////
=======
   ////// ------ Register 62 [0x00F8]: EVENT_NR - Number of latest event (Default: 0x00000000) ------ //////
>>>>>>> Stashed changes

   // 0xFFFFFFFF: EVENT_NUMBER - Number of latest event
   unsigned int GetEventNumber() { return BitExtract(DCB_EVENT_NUMBER_REG, DCB_EVENT_NUMBER_MASK, DCB_EVENT_NUMBER_OFS); };


<<<<<<< Updated upstream
   ////// ------ Register 45 [0x00B4]: TRG_CFG - Trigger Configuration (Default: 0x00000000) ------ //////
=======
   ////// ------ Register 63 [0x00FC]: TRG_CFG - Trigger Configuration (Default: 0x00000000) ------ //////
>>>>>>> Stashed changes

   // 0x00000004: EXT_TRIGGER_OUT_ENABLE - Enable output of trigger signal to MCX connector
   unsigned int GetExtTriggerOutEnable() { return BitExtract(DCB_EXT_TRIGGER_OUT_ENABLE_REG, DCB_EXT_TRIGGER_OUT_ENABLE_MASK, DCB_EXT_TRIGGER_OUT_ENABLE_OFS); };
   void         SetExtTriggerOutEnable(unsigned int value) { SetRegMask(DCB_EXT_TRIGGER_OUT_ENABLE_REG, DCB_EXT_TRIGGER_OUT_ENABLE_MASK, DCB_EXT_TRIGGER_OUT_ENABLE_OFS, value); };

   // 0x00000002: ENABLE_AUTO_TRIGGER - Enable generation of automatic periodic trigger to backplane
   unsigned int GetEnableAutoTrigger() { return BitExtract(DCB_ENABLE_AUTO_TRIGGER_REG, DCB_ENABLE_AUTO_TRIGGER_MASK, DCB_ENABLE_AUTO_TRIGGER_OFS); };
   void         SetEnableAutoTrigger(unsigned int value) { SetRegMask(DCB_ENABLE_AUTO_TRIGGER_REG, DCB_ENABLE_AUTO_TRIGGER_MASK, DCB_ENABLE_AUTO_TRIGGER_OFS, value); };

   // 0x00000001: MANUAL_TRIGGER - Generate trigger pulse on backplane
   unsigned int GetManualTrigger() { return BitExtract(DCB_MANUAL_TRIGGER_REG, DCB_MANUAL_TRIGGER_MASK, DCB_MANUAL_TRIGGER_OFS); };
   void         SetManualTrigger(unsigned int value) { SetRegMask(DCB_MANUAL_TRIGGER_REG, DCB_MANUAL_TRIGGER_MASK, DCB_MANUAL_TRIGGER_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 46 [0x00B8]: SET_TRG_CFG - SET bit register for Trigger configuration register (Default: 0x00000000) ------ //////
=======
   ////// ------ Register 64 [0x0100]: SET_TRG_CFG - SET bit register for Trigger configuration register (Default: 0x00000000) ------ //////
>>>>>>> Stashed changes

   // 0xFFFFFFFF: SET_BIT_TRG_CFG - See TRG_CFG register
   unsigned int GetSetBitTrgCfg() { return BitExtract(DCB_SET_BIT_TRG_CFG_REG, DCB_SET_BIT_TRG_CFG_MASK, DCB_SET_BIT_TRG_CFG_OFS); };
   void         SetSetBitTrgCfg(unsigned int value) { SetRegMask(DCB_SET_BIT_TRG_CFG_REG, DCB_SET_BIT_TRG_CFG_MASK, DCB_SET_BIT_TRG_CFG_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 47 [0x00BC]: CLR_TRG_CFG - CLR bit register for Trigger configuration register (Default: 0x00000000) ------ //////
=======
   ////// ------ Register 65 [0x0104]: CLR_TRG_CFG - CLR bit register for Trigger configuration register (Default: 0x00000000) ------ //////
>>>>>>> Stashed changes

   // 0xFFFFFFFF: CLR_BIT_TRG_CFG - See TRG_CFG register
   unsigned int GetClrBitTrgCfg() { return BitExtract(DCB_CLR_BIT_TRG_CFG_REG, DCB_CLR_BIT_TRG_CFG_MASK, DCB_CLR_BIT_TRG_CFG_OFS); };
   void         SetClrBitTrgCfg(unsigned int value) { SetRegMask(DCB_CLR_BIT_TRG_CFG_REG, DCB_CLR_BIT_TRG_CFG_MASK, DCB_CLR_BIT_TRG_CFG_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 48 [0x00C0]: TRG_AUTO_PERIOD - Automatic Trigger Period (Default: 0x04C4B400) ------ //////
=======
   ////// ------ Register 66 [0x0108]: TRG_AUTO_PERIOD - Automatic Trigger Period (Default: 0x04C4B400) ------ //////
>>>>>>> Stashed changes

   // 0xFFFFFFFF: AUTO_TRIGGER_PERIOD - Period of automatic trigger in ticks of the DAQ clock
   unsigned int GetAutoTriggerPeriod() { return BitExtract(DCB_AUTO_TRIGGER_PERIOD_REG, DCB_AUTO_TRIGGER_PERIOD_MASK, DCB_AUTO_TRIGGER_PERIOD_OFS); };
   void         SetAutoTriggerPeriod(unsigned int value) { SetRegMask(DCB_AUTO_TRIGGER_PERIOD_REG, DCB_AUTO_TRIGGER_PERIOD_MASK, DCB_AUTO_TRIGGER_PERIOD_OFS, value); };



<<<<<<< Updated upstream
   ////// ------ Register 49 [0x00C4]: TRB_INFO_STAT - Trigger Information via Serial Trigger Bus Status (Default: 0x00000000) ------ //////
=======
   ////// ------ Register 67 [0x010C]: TRB_INFO_STAT - Trigger Information via Serial Trigger Bus Status (Default: 0x00000000) ------ //////
>>>>>>> Stashed changes

   // 0x80000000: TRB_FLAG_NEW - Flag signalling that the current trigger information belongs to the latest trigger received
   unsigned int GetTrbFlagNew() { return BitExtract(DCB_TRB_FLAG_NEW_REG, DCB_TRB_FLAG_NEW_MASK, DCB_TRB_FLAG_NEW_OFS); };
   // 0x40000000: TRB_FLAG_PARITY_ERROR - Parity error flag of the current trigger information
   unsigned int GetTrbFlagParityError() { return BitExtract(DCB_TRB_FLAG_PARITY_ERROR_REG, DCB_TRB_FLAG_PARITY_ERROR_MASK, DCB_TRB_FLAG_PARITY_ERROR_OFS); };
   // 0x0000FFFF: TRB_PARITY_ERROR_COUNT - Parity error count of the serial transmission
   unsigned int GetTrbParityErrorCount() { return BitExtract(DCB_TRB_PARITY_ERROR_COUNT_REG, DCB_TRB_PARITY_ERROR_COUNT_MASK, DCB_TRB_PARITY_ERROR_COUNT_OFS); };


<<<<<<< Updated upstream
   ////// ------ Register 50 [0x00C8]: TRB_INFO_LSB - Trigger Information via Serial Trigger Bus LSBs (Default: 0x00000000) ------ //////
=======
   ////// ------ Register 68 [0x0110]: TRB_INFO_LSB - Trigger Information via Serial Trigger Bus LSBs (Default: 0x00000000) ------ //////
>>>>>>> Stashed changes

   // 0xFFFFFFFF: TRB_INFO_LSB - Trigger information LSBs
   unsigned int GetTrbInfoLsb() { return BitExtract(DCB_TRB_INFO_LSB_REG, DCB_TRB_INFO_LSB_MASK, DCB_TRB_INFO_LSB_OFS); };


<<<<<<< Updated upstream
   ////// ------ Register 51 [0x00CC]: TRB_INFO_MSB - Trigger Information via Serial Trigger Bus MSBs (Default: 0x00000000) ------ //////
=======
   ////// ------ Register 69 [0x0114]: TRB_INFO_MSB - Trigger Information via Serial Trigger Bus MSBs (Default: 0x00000000) ------ //////
>>>>>>> Stashed changes

   // 0x0000FFFF: TRB_INFO_MSB - Trigger information MSBs
   unsigned int GetTrbInfoMsb() { return BitExtract(DCB_TRB_INFO_MSB_REG, DCB_TRB_INFO_MSB_MASK, DCB_TRB_INFO_MSB_OFS); };


<<<<<<< Updated upstream
   ////// ------ Register 52 [0x00D0]: LMK_MOD_FLAG - Set if LMK configuraiton registers are modified (Default: 0x00000000) ------ //////
=======
   ////// ------ Register 70 [0x0118]: LMK_MOD_FLAG - Set if LMK configuraiton registers are modified (Default: 0x00000000) ------ //////
>>>>>>> Stashed changes

   // 0x00000080: LMK_7_MOD - LMK channel 7 register modified flags
   unsigned int GetLmk7Mod() { return BitExtract(DCB_LMK_7_MOD_REG, DCB_LMK_7_MOD_MASK, DCB_LMK_7_MOD_OFS); };
   // 0x00000040: LMK_6_MOD - LMK channel 6 register modified flags
   unsigned int GetLmk6Mod() { return BitExtract(DCB_LMK_6_MOD_REG, DCB_LMK_6_MOD_MASK, DCB_LMK_6_MOD_OFS); };
   // 0x00000020: LMK_5_MOD - LMK channel 5 register modified flags
   unsigned int GetLmk5Mod() { return BitExtract(DCB_LMK_5_MOD_REG, DCB_LMK_5_MOD_MASK, DCB_LMK_5_MOD_OFS); };
   // 0x00000010: LMK_4_MOD - LMK channel 4 register modified flags
   unsigned int GetLmk4Mod() { return BitExtract(DCB_LMK_4_MOD_REG, DCB_LMK_4_MOD_MASK, DCB_LMK_4_MOD_OFS); };
   // 0x00000008: LMK_3_MOD - LMK channel 3 register modified flags
   unsigned int GetLmk3Mod() { return BitExtract(DCB_LMK_3_MOD_REG, DCB_LMK_3_MOD_MASK, DCB_LMK_3_MOD_OFS); };
   // 0x00000004: LMK_2_MOD - LMK channel 2 register modified flags
   unsigned int GetLmk2Mod() { return BitExtract(DCB_LMK_2_MOD_REG, DCB_LMK_2_MOD_MASK, DCB_LMK_2_MOD_OFS); };
   // 0x00000002: LMK_1_MOD - LMK channel 1 register modified flags
   unsigned int GetLmk1Mod() { return BitExtract(DCB_LMK_1_MOD_REG, DCB_LMK_1_MOD_MASK, DCB_LMK_1_MOD_OFS); };
   // 0x00000001: LMK_0_MOD - LMK Register 0 modified flags
   unsigned int GetLmk0Mod() { return BitExtract(DCB_LMK_0_MOD_REG, DCB_LMK_0_MOD_MASK, DCB_LMK_0_MOD_OFS); };


<<<<<<< Updated upstream
   ////// ------ Register 53 [0x00D4]: CRC32_REG_BANK - CRC32 Checksum of Register Bank Content (Default: 0x00000000) ------ //////
=======
   ////// ------ Register 71 [0x011C]: CRC32_REG_BANK - CRC32 Checksum of Register Bank Content (Default: 0x00000000) ------ //////
>>>>>>> Stashed changes

   // 0xFFFFFFFF: CRC32_REG_BANK - Keep at the end of the register bank
   unsigned int GetCrc32RegBank() { return BitExtract(DCB_CRC32_REG_BANK_REG, DCB_CRC32_REG_BANK_MASK, DCB_CRC32_REG_BANK_OFS); };
   void         SetCrc32RegBank(unsigned int value) { SetRegMask(DCB_CRC32_REG_BANK_REG, DCB_CRC32_REG_BANK_MASK, DCB_CRC32_REG_BANK_OFS, value); };


};

//--------------------------------------------------------------------

#endif /* defined(__DCBREG_H__) */

//
//  WDBReg.h
//
//  WaveDAQ Register Access Class
//
//  This file is generated automatically, please do not edit!
//
// Created :  13.09.2018 13:26:49
//


#ifndef __wdbreg_h__
#define __wdbreg_h__

#include "register_map_wd2.h"

//--------------------------------------------------------------------

class WDBREG {

private:
   // virtual bit functions, must be implemented in derived class
   virtual unsigned int BitExtractStatus(unsigned int reg, unsigned int mask, unsigned int ofs) = 0;
   virtual unsigned int BitExtractControl(unsigned int reg, unsigned int mask, unsigned int ofs) = 0;
   virtual void SetRegMask(unsigned int reg, unsigned int mask, unsigned int ofs, unsigned int v) = 0;

public:
   
   // constructor
   WDBREG(){};



   ////// ------ Control Register 0 [0x1000]: WDB_LOC - Location where the WD2 is plugged in (Default: 0xFFFFFFFF) ------ //////

   // 0x00FF0000: CRATE_ID - ID of the crate where the current board is plugged in
   unsigned int GetCrateId() { return BitExtractControl(WD2_CRATE_ID_REG, WD2_CRATE_ID_MASK, WD2_CRATE_ID_OFS); };
   void         SetCrateId(unsigned int value) { SetRegMask(WD2_CRATE_ID_REG, WD2_CRATE_ID_MASK, WD2_CRATE_ID_OFS, value); };

   // 0x000000FF: SLOT_ID - ID of the slot where the current board is plugged in
   unsigned int GetSlotId() { return BitExtractControl(WD2_SLOT_ID_REG, WD2_SLOT_ID_MASK, WD2_SLOT_ID_OFS); };
   void         SetSlotId(unsigned int value) { SetRegMask(WD2_SLOT_ID_REG, WD2_SLOT_ID_MASK, WD2_SLOT_ID_OFS, value); };



   ////// ------ Control Register 1 [0x1004]: CTRL - DAQ control register (Default: 0x19200780) ------ //////

   // 0x3F000000: VALID_DELAY_ADC - Delay of the data valid at the ISERDES of the ADCs (delay = value + 1)
   unsigned int GetValidDelayAdc() { return BitExtractControl(WD2_VALID_DELAY_ADC_REG, WD2_VALID_DELAY_ADC_MASK, WD2_VALID_DELAY_ADC_OFS); };
   void         SetValidDelayAdc(unsigned int value) { SetRegMask(WD2_VALID_DELAY_ADC_REG, WD2_VALID_DELAY_ADC_MASK, WD2_VALID_DELAY_ADC_OFS, value); };

   // 0x00FF0000: DAQ_DATA_PHASE - Phase step setting of the PLL generating the common DAQ clock
   unsigned int GetDaqDataPhase() { return BitExtractControl(WD2_DAQ_DATA_PHASE_REG, WD2_DAQ_DATA_PHASE_MASK, WD2_DAQ_DATA_PHASE_OFS); };
   void         SetDaqDataPhase(unsigned int value) { SetRegMask(WD2_DAQ_DATA_PHASE_REG, WD2_DAQ_DATA_PHASE_MASK, WD2_DAQ_DATA_PHASE_OFS, value); };

   // 0x00000400: DRS_CLR_RSR_AFTER_RO - Clear the read shift register (remove the token) after each readout
   unsigned int GetDrsClrRsrAfterRo() { return BitExtractControl(WD2_DRS_CLR_RSR_AFTER_RO_REG, WD2_DRS_CLR_RSR_AFTER_RO_MASK, WD2_DRS_CLR_RSR_AFTER_RO_OFS); };
   void         SetDrsClrRsrAfterRo(unsigned int value) { SetRegMask(WD2_DRS_CLR_RSR_AFTER_RO_REG, WD2_DRS_CLR_RSR_AFTER_RO_MASK, WD2_DRS_CLR_RSR_AFTER_RO_OFS, value); };

   // 0x00000200: COMP_POWER_EN - Comparator power enable
   unsigned int GetCompPowerEn() { return BitExtractControl(WD2_COMP_POWER_EN_REG, WD2_COMP_POWER_EN_MASK, WD2_COMP_POWER_EN_OFS); };
   void         SetCompPowerEn(unsigned int value) { SetRegMask(WD2_COMP_POWER_EN_REG, WD2_COMP_POWER_EN_MASK, WD2_COMP_POWER_EN_OFS, value); };

   // 0x00000100: DRS_READOUT_MODE - 0:start from first bin, 1:start from domino stop
   unsigned int GetDrsReadoutMode() { return BitExtractControl(WD2_DRS_READOUT_MODE_REG, WD2_DRS_READOUT_MODE_MASK, WD2_DRS_READOUT_MODE_OFS); };
   void         SetDrsReadoutMode(unsigned int value) { SetRegMask(WD2_DRS_READOUT_MODE_REG, WD2_DRS_READOUT_MODE_MASK, WD2_DRS_READOUT_MODE_OFS, value); };

   // 0x00000080: DRS_WAVE_CONTINUOUS - 0:stop domino wave during readout, 1:keep it running
   unsigned int GetDrsWaveContinuous() { return BitExtractControl(WD2_DRS_WAVE_CONTINUOUS_REG, WD2_DRS_WAVE_CONTINUOUS_MASK, WD2_DRS_WAVE_CONTINUOUS_OFS); };
   void         SetDrsWaveContinuous(unsigned int value) { SetRegMask(WD2_DRS_WAVE_CONTINUOUS_REG, WD2_DRS_WAVE_CONTINUOUS_MASK, WD2_DRS_WAVE_CONTINUOUS_OFS, value); };

   // 0x00000040: DRS_CONFIGURE - write a "1" to trigger the DRS chip register configuration
   unsigned int GetDrsConfigure() { return BitExtractControl(WD2_DRS_CONFIGURE_REG, WD2_DRS_CONFIGURE_MASK, WD2_DRS_CONFIGURE_OFS); };
   void         SetDrsConfigure(unsigned int value) { SetRegMask(WD2_DRS_CONFIGURE_REG, WD2_DRS_CONFIGURE_MASK, WD2_DRS_CONFIGURE_OFS, value); };

   // 0x00000020: DAQ_SOFT_TRIGGER - write a "1" to stop the DRS chip & read the data to RAM
   unsigned int GetDaqSoftTrigger() { return BitExtractControl(WD2_DAQ_SOFT_TRIGGER_REG, WD2_DAQ_SOFT_TRIGGER_MASK, WD2_DAQ_SOFT_TRIGGER_OFS); };
   void         SetDaqSoftTrigger(unsigned int value) { SetRegMask(WD2_DAQ_SOFT_TRIGGER_REG, WD2_DAQ_SOFT_TRIGGER_MASK, WD2_DAQ_SOFT_TRIGGER_OFS, value); };

   // 0x00000004: DAQ_AUTO - Auto-Trigger readout state machine every 0.5s if no other trigger (like "auto" acquisition on scope)
   unsigned int GetDaqAuto() { return BitExtractControl(WD2_DAQ_AUTO_REG, WD2_DAQ_AUTO_MASK, WD2_DAQ_AUTO_OFS); };
   void         SetDaqAuto(unsigned int value) { SetRegMask(WD2_DAQ_AUTO_REG, WD2_DAQ_AUTO_MASK, WD2_DAQ_AUTO_OFS, value); };

   // 0x00000002: DAQ_NORMAL - Restart readout state machine automatically after readout (like "normal" acquisition on scope)
   unsigned int GetDaqNormal() { return BitExtractControl(WD2_DAQ_NORMAL_REG, WD2_DAQ_NORMAL_MASK, WD2_DAQ_NORMAL_OFS); };
   void         SetDaqNormal(unsigned int value) { SetRegMask(WD2_DAQ_NORMAL_REG, WD2_DAQ_NORMAL_MASK, WD2_DAQ_NORMAL_OFS, value); };

   // 0x00000001: DAQ_SINGLE - Start readout state machine automatically and stop after readout (like "single" acquisition on scope)
   unsigned int GetDaqSingle() { return BitExtractControl(WD2_DAQ_SINGLE_REG, WD2_DAQ_SINGLE_MASK, WD2_DAQ_SINGLE_OFS); };
   void         SetDaqSingle(unsigned int value) { SetRegMask(WD2_DAQ_SINGLE_REG, WD2_DAQ_SINGLE_MASK, WD2_DAQ_SINGLE_OFS, value); };



   ////// ------ Control Register 2 [0x1008]: CAL_CTRL - Clock and Calibration Control (Default: 0x00000000) ------ //////

   // 0x00000008: DRS_0_TIMING_REF_SEL - Select timing reference signal for DRS 0: 0 = oscillator / 1 = LMK (CAL_CTRL_A)
   unsigned int GetDrs0TimingRefSel() { return BitExtractControl(WD2_DRS_0_TIMING_REF_SEL_REG, WD2_DRS_0_TIMING_REF_SEL_MASK, WD2_DRS_0_TIMING_REF_SEL_OFS); };
   void         SetDrs0TimingRefSel(unsigned int value) { SetRegMask(WD2_DRS_0_TIMING_REF_SEL_REG, WD2_DRS_0_TIMING_REF_SEL_MASK, WD2_DRS_0_TIMING_REF_SEL_OFS, value); };

   // 0x00000004: DRS_1_TIMING_REF_SEL - Select timing reference signal for DRS 1: 0 = oscillator / 1 = LMK  (CAL_CTRL_B)
   unsigned int GetDrs1TimingRefSel() { return BitExtractControl(WD2_DRS_1_TIMING_REF_SEL_REG, WD2_DRS_1_TIMING_REF_SEL_MASK, WD2_DRS_1_TIMING_REF_SEL_OFS); };
   void         SetDrs1TimingRefSel(unsigned int value) { SetRegMask(WD2_DRS_1_TIMING_REF_SEL_REG, WD2_DRS_1_TIMING_REF_SEL_MASK, WD2_DRS_1_TIMING_REF_SEL_OFS, value); };

   // 0x00000002: CALIB_BUFFER_EN - Enable buffers driving the calib. signal to the frontend MUX (BUFFER_CTRL)
   unsigned int GetCalibBufferEn() { return BitExtractControl(WD2_CALIB_BUFFER_EN_REG, WD2_CALIB_BUFFER_EN_MASK, WD2_CALIB_BUFFER_EN_OFS); };
   void         SetCalibBufferEn(unsigned int value) { SetRegMask(WD2_CALIB_BUFFER_EN_REG, WD2_CALIB_BUFFER_EN_MASK, WD2_CALIB_BUFFER_EN_OFS, value); };

   // 0x00000001: TIMING_CALIB_SIGNAL_EN - switch on (1) / off (0) 100 MHz calibration signal for DRS chip (TCA_CTRL)
   unsigned int GetTimingCalibSignalEn() { return BitExtractControl(WD2_TIMING_CALIB_SIGNAL_EN_REG, WD2_TIMING_CALIB_SIGNAL_EN_MASK, WD2_TIMING_CALIB_SIGNAL_EN_OFS); };
   void         SetTimingCalibSignalEn(unsigned int value) { SetRegMask(WD2_TIMING_CALIB_SIGNAL_EN_REG, WD2_TIMING_CALIB_SIGNAL_EN_MASK, WD2_TIMING_CALIB_SIGNAL_EN_OFS, value); };



   ////// ------ Control Register 3 [0x100C]: CLK_CTRL - Clock Control (Default: 0x00026464) ------ //////

   // 0x00020000: DAQ_CLK_SRC_SEL - DAQ clock source select: 0 = DCB clock / 1 = on board oscillator (CLK_SEL)
   unsigned int GetDaqClkSrcSel() { return BitExtractControl(WD2_DAQ_CLK_SRC_SEL_REG, WD2_DAQ_CLK_SRC_SEL_MASK, WD2_DAQ_CLK_SRC_SEL_OFS); };
   void         SetDaqClkSrcSel(unsigned int value) { SetRegMask(WD2_DAQ_CLK_SRC_SEL_REG, WD2_DAQ_CLK_SRC_SEL_MASK, WD2_DAQ_CLK_SRC_SEL_OFS, value); };

   // 0x00010000: EXT_CLK_IN_SEL - External clk input select: 0 = backplane / 1 = MCX connector (CLK_SEL_EXT)
   unsigned int GetExtClkInSel() { return BitExtractControl(WD2_EXT_CLK_IN_SEL_REG, WD2_EXT_CLK_IN_SEL_MASK, WD2_EXT_CLK_IN_SEL_OFS); };
   void         SetExtClkInSel(unsigned int value) { SetRegMask(WD2_EXT_CLK_IN_SEL_REG, WD2_EXT_CLK_IN_SEL_MASK, WD2_EXT_CLK_IN_SEL_OFS, value); };

   // 0x0000FF00: EXT_CLK_FREQ - External clock frequency (MCX or backplane) in MHz
   unsigned int GetExtClkFreq() { return BitExtractControl(WD2_EXT_CLK_FREQ_REG, WD2_EXT_CLK_FREQ_MASK, WD2_EXT_CLK_FREQ_OFS); };
   void         SetExtClkFreq(unsigned int value) { SetRegMask(WD2_EXT_CLK_FREQ_REG, WD2_EXT_CLK_FREQ_MASK, WD2_EXT_CLK_FREQ_OFS, value); };

   // 0x000000FF: LOCAL_CLK_FREQ - Local (on board) oscillator frequency in MHz
   unsigned int GetLocalClkFreq() { return BitExtractControl(WD2_LOCAL_CLK_FREQ_REG, WD2_LOCAL_CLK_FREQ_MASK, WD2_LOCAL_CLK_FREQ_OFS); };
   void         SetLocalClkFreq(unsigned int value) { SetRegMask(WD2_LOCAL_CLK_FREQ_REG, WD2_LOCAL_CLK_FREQ_MASK, WD2_LOCAL_CLK_FREQ_OFS, value); };



   ////// ------ Control Register 4 [0x1010]: DRS_CTRL - DRS4 Control and Configuration Registers (Default: 0x00FFFFFF) ------ //////

   // 0x00040000: DRS_WSRLOOP - Internally Connect WSRIN to WSROUT (if set to 1)
   unsigned int GetDrsWsrloop() { return BitExtractControl(WD2_DRS_WSRLOOP_REG, WD2_DRS_WSRLOOP_MASK, WD2_DRS_WSRLOOP_OFS); };
   void         SetDrsWsrloop(unsigned int value) { SetRegMask(WD2_DRS_WSRLOOP_REG, WD2_DRS_WSRLOOP_MASK, WD2_DRS_WSRLOOP_OFS, value); };

   // 0x00020000: DRS_PLLEN - Internal PLL Enable (0 = disable, 1 = enable)
   unsigned int GetDrsPllen() { return BitExtractControl(WD2_DRS_PLLEN_REG, WD2_DRS_PLLEN_MASK, WD2_DRS_PLLEN_OFS); };
   void         SetDrsPllen(unsigned int value) { SetRegMask(WD2_DRS_PLLEN_REG, WD2_DRS_PLLEN_MASK, WD2_DRS_PLLEN_OFS, value); };

   // 0x00010000: DRS_DMODE - Domino Mode Control (0 = single shot, 1 = continuous)
   unsigned int GetDrsDmode() { return BitExtractControl(WD2_DRS_DMODE_REG, WD2_DRS_DMODE_MASK, WD2_DRS_DMODE_OFS); };
   void         SetDrsDmode(unsigned int value) { SetRegMask(WD2_DRS_DMODE_REG, WD2_DRS_DMODE_MASK, WD2_DRS_DMODE_OFS, value); };

   // 0x0000FF00: DRS_WSR - DRS4 Write Shift Register (0xD)
   unsigned int GetDrsWsr() { return BitExtractControl(WD2_DRS_WSR_REG, WD2_DRS_WSR_MASK, WD2_DRS_WSR_OFS); };
   void         SetDrsWsr(unsigned int value) { SetRegMask(WD2_DRS_WSR_REG, WD2_DRS_WSR_MASK, WD2_DRS_WSR_OFS, value); };

   // 0x000000FF: DRS_WCR - DRS4 Write Configuration Register (0xE)
   unsigned int GetDrsWcr() { return BitExtractControl(WD2_DRS_WCR_REG, WD2_DRS_WCR_MASK, WD2_DRS_WCR_OFS); };
   void         SetDrsWcr(unsigned int value) { SetRegMask(WD2_DRS_WCR_REG, WD2_DRS_WCR_MASK, WD2_DRS_WCR_OFS, value); };



   ////// ------ Control Register 5 [0x1014]: COM_CTRL - Communication Control Register (Default: 0x01000753) ------ //////

   // 0x80000000: DCB_SERDES_TRAIN - Enable training pattern for DCB SERDES connection
   unsigned int GetDcbSerdesTrain() { return BitExtractControl(WD2_DCB_SERDES_TRAIN_REG, WD2_DCB_SERDES_TRAIN_MASK, WD2_DCB_SERDES_TRAIN_OFS); };
   void         SetDcbSerdesTrain(unsigned int value) { SetRegMask(WD2_DCB_SERDES_TRAIN_REG, WD2_DCB_SERDES_TRAIN_MASK, WD2_DCB_SERDES_TRAIN_OFS, value); };

   // 0x40000000: TCB_SERDES_TRAIN - Enable training pattern for TCB SERDES connection
   unsigned int GetTcbSerdesTrain() { return BitExtractControl(WD2_TCB_SERDES_TRAIN_REG, WD2_TCB_SERDES_TRAIN_MASK, WD2_TCB_SERDES_TRAIN_OFS); };
   void         SetTcbSerdesTrain(unsigned int value) { SetRegMask(WD2_TCB_SERDES_TRAIN_REG, WD2_TCB_SERDES_TRAIN_MASK, WD2_TCB_SERDES_TRAIN_OFS, value); };

   // 0x08000000: TRG_TX_EN - enable transmission of advanced trigger output data
   unsigned int GetTrgTxEn() { return BitExtractControl(WD2_TRG_TX_EN_REG, WD2_TRG_TX_EN_MASK, WD2_TRG_TX_EN_OFS); };
   void         SetTrgTxEn(unsigned int value) { SetRegMask(WD2_TRG_TX_EN_REG, WD2_TRG_TX_EN_MASK, WD2_TRG_TX_EN_OFS, value); };

   // 0x04000000: SCL_TX_EN - Enable transmission of scaler data
   unsigned int GetSclTxEn() { return BitExtractControl(WD2_SCL_TX_EN_REG, WD2_SCL_TX_EN_MASK, WD2_SCL_TX_EN_OFS); };
   void         SetSclTxEn(unsigned int value) { SetRegMask(WD2_SCL_TX_EN_REG, WD2_SCL_TX_EN_MASK, WD2_SCL_TX_EN_OFS, value); };

   // 0x02000000: SERDES_COM_EN - Enable SERDES communication to backplane
   unsigned int GetSerdesComEn() { return BitExtractControl(WD2_SERDES_COM_EN_REG, WD2_SERDES_COM_EN_MASK, WD2_SERDES_COM_EN_OFS); };
   void         SetSerdesComEn(unsigned int value) { SetRegMask(WD2_SERDES_COM_EN_REG, WD2_SERDES_COM_EN_MASK, WD2_SERDES_COM_EN_OFS, value); };

   // 0x01000000: ETH_COM_EN - Enable ethernet communication
   unsigned int GetEthComEn() { return BitExtractControl(WD2_ETH_COM_EN_REG, WD2_ETH_COM_EN_MASK, WD2_ETH_COM_EN_OFS); };
   void         SetEthComEn(unsigned int value) { SetRegMask(WD2_ETH_COM_EN_REG, WD2_ETH_COM_EN_MASK, WD2_ETH_COM_EN_OFS, value); };

   // 0x00FFFFFF: INTER_PKG_DELAY - Delay between transmission of two UDP packages in 8ns steps
   unsigned int GetInterPkgDelay() { return BitExtractControl(WD2_INTER_PKG_DELAY_REG, WD2_INTER_PKG_DELAY_MASK, WD2_INTER_PKG_DELAY_OFS); };
   void         SetInterPkgDelay(unsigned int value) { SetRegMask(WD2_INTER_PKG_DELAY_REG, WD2_INTER_PKG_DELAY_MASK, WD2_INTER_PKG_DELAY_OFS, value); };



   ////// ------ Control Register 6 [0x1018]: COM_PLD_SIZE - Maximum Payload Size (Default: 0x000005C0) ------ //////

   // 0x0003FFFF: COM_PLD_SIZE - Maximum number of UDP payload bytes to transmit (must be a multiple of 6 with range 6 to 8892)
   unsigned int GetComPldSize() { return BitExtractControl(WD2_COM_PLD_SIZE_REG, WD2_COM_PLD_SIZE_MASK, WD2_COM_PLD_SIZE_OFS); };
   void         SetComPldSize(unsigned int value) { SetRegMask(WD2_COM_PLD_SIZE_REG, WD2_COM_PLD_SIZE_MASK, WD2_COM_PLD_SIZE_OFS, value); };



   ////// ------ Control Register 7 [0x101C]: DRS_CH_TX_EN - DRS Channel Transmission Enable Register (Default: 0x0000FFFF) ------ //////

   // 0x0003FFFF: DRS_CH_TX_EN - DRS channel transmission enable [Ch17:Ch0] - (CH17:CH16 = timing channels)
   unsigned int GetDrsChTxEn() { return BitExtractControl(WD2_DRS_CH_TX_EN_REG, WD2_DRS_CH_TX_EN_MASK, WD2_DRS_CH_TX_EN_OFS); };
   void         SetDrsChTxEn(unsigned int value) { SetRegMask(WD2_DRS_CH_TX_EN_REG, WD2_DRS_CH_TX_EN_MASK, WD2_DRS_CH_TX_EN_OFS, value); };



   ////// ------ Control Register 8 [0x1020]: ADC_CH_TX_EN - ADC Channel Transmission Enable Register (Default: 0x00000000) ------ //////

   // 0x0000FFFF: ADC_CH_TX_EN - ADC channel transmission enable [Ch15:Ch0]
   unsigned int GetAdcChTxEn() { return BitExtractControl(WD2_ADC_CH_TX_EN_REG, WD2_ADC_CH_TX_EN_MASK, WD2_ADC_CH_TX_EN_OFS); };
   void         SetAdcChTxEn(unsigned int value) { SetRegMask(WD2_ADC_CH_TX_EN_REG, WD2_ADC_CH_TX_EN_MASK, WD2_ADC_CH_TX_EN_OFS, value); };



   ////// ------ Control Register 9 [0x1024]: TDC_CH_TX_EN - TDC Channel Transmission Enable Register (Default: 0x00000000) ------ //////

   // 0x0000FFFF: TDC_CH_TX_EN - TDC channel transmission enable [Ch15:Ch0]
   unsigned int GetTdcChTxEn() { return BitExtractControl(WD2_TDC_CH_TX_EN_REG, WD2_TDC_CH_TX_EN_MASK, WD2_TDC_CH_TX_EN_OFS); };
   void         SetTdcChTxEn(unsigned int value) { SetRegMask(WD2_TDC_CH_TX_EN_REG, WD2_TDC_CH_TX_EN_MASK, WD2_TDC_CH_TX_EN_OFS, value); };



   ////// ------ Control Register 10 [0x1028]: DRS_TX_SAMPLES - DRS Samples to transmit (Default: 0x00000400) ------ //////

   // 0x000007FF: DRS_TX_SAMPLES - Number of DRS samples to transmit per channel (must be an even value with range 2 to 1024)
   unsigned int GetDrsTxSamples() { return BitExtractControl(WD2_DRS_TX_SAMPLES_REG, WD2_DRS_TX_SAMPLES_MASK, WD2_DRS_TX_SAMPLES_OFS); };
   void         SetDrsTxSamples(unsigned int value) { SetRegMask(WD2_DRS_TX_SAMPLES_REG, WD2_DRS_TX_SAMPLES_MASK, WD2_DRS_TX_SAMPLES_OFS, value); };



   ////// ------ Control Register 11 [0x102C]: ADC_TX_SAMPLES - ADC Samples to transmit (Default: 0x00000800) ------ //////

   // 0x00000FFF: ADC_TX_SAMPLES - Number of ADC samples to transmit per channel (must be an even value with range 2 to 2048)
   unsigned int GetAdcTxSamples() { return BitExtractControl(WD2_ADC_TX_SAMPLES_REG, WD2_ADC_TX_SAMPLES_MASK, WD2_ADC_TX_SAMPLES_OFS); };
   void         SetAdcTxSamples(unsigned int value) { SetRegMask(WD2_ADC_TX_SAMPLES_REG, WD2_ADC_TX_SAMPLES_MASK, WD2_ADC_TX_SAMPLES_OFS, value); };



   ////// ------ Control Register 12 [0x1030]: TDC_TX_SAMPLES - TDC Samples to transmit (Default: 0x00001000) ------ //////

   // 0x00001FFF: TDC_TX_SAMPLES - Number of TDC samples to transmit per channel (must be a multiple of 8 with range 16 to 4096)
   unsigned int GetTdcTxSamples() { return BitExtractControl(WD2_TDC_TX_SAMPLES_REG, WD2_TDC_TX_SAMPLES_MASK, WD2_TDC_TX_SAMPLES_OFS); };
   void         SetTdcTxSamples(unsigned int value) { SetRegMask(WD2_TDC_TX_SAMPLES_REG, WD2_TDC_TX_SAMPLES_MASK, WD2_TDC_TX_SAMPLES_OFS, value); };



   ////// ------ Control Register 13 [0x1034]: TRG_TX_SAMPLES - TRG Samples to transmit (Default: 0x00000200) ------ //////

   // 0x000003FF: TRG_TX_SAMPLES - Number of advanced trigger output samples to transmit (range 1 to 512)
   unsigned int GetTrgTxSamples() { return BitExtractControl(WD2_TRG_TX_SAMPLES_REG, WD2_TRG_TX_SAMPLES_MASK, WD2_TRG_TX_SAMPLES_OFS); };
   void         SetTrgTxSamples(unsigned int value) { SetRegMask(WD2_TRG_TX_SAMPLES_REG, WD2_TRG_TX_SAMPLES_MASK, WD2_TRG_TX_SAMPLES_OFS, value); };



   ////// ------ Control Register 14 [0x1038]: ADC_SAMPLE_DIV - ADC Downsampling Divider (Default: 0x00000001) ------ //////

   // 0x000000FF: ADC_SAMPLE_DIV - Only store every n-th sample to buffer
   unsigned int GetAdcSampleDiv() { return BitExtractControl(WD2_ADC_SAMPLE_DIV_REG, WD2_ADC_SAMPLE_DIV_MASK, WD2_ADC_SAMPLE_DIV_OFS); };
   void         SetAdcSampleDiv(unsigned int value) { SetRegMask(WD2_ADC_SAMPLE_DIV_REG, WD2_ADC_SAMPLE_DIV_MASK, WD2_ADC_SAMPLE_DIV_OFS, value); };



   ////// ------ Control Register 15 [0x103C]: ZERO_SUPR - Zero Suppression Configuration Register (Default: 0x00000080) ------ //////

   // 0x00000100: ZERO_SUPR_EN - Enable zero suppression for data transmission (only transmit channels that triggered)
   unsigned int GetZeroSuprEn() { return BitExtractControl(WD2_ZERO_SUPR_EN_REG, WD2_ZERO_SUPR_EN_MASK, WD2_ZERO_SUPR_EN_OFS); };
   void         SetZeroSuprEn(unsigned int value) { SetRegMask(WD2_ZERO_SUPR_EN_REG, WD2_ZERO_SUPR_EN_MASK, WD2_ZERO_SUPR_EN_OFS, value); };

   // 0x000000FF: ZERO_SUPR_WINDOW - Zero suppression time window in DAQ clock ticks (channel polarity defined in TRG_SRC_POL)
   unsigned int GetZeroSuprWindow() { return BitExtractControl(WD2_ZERO_SUPR_WINDOW_REG, WD2_ZERO_SUPR_WINDOW_MASK, WD2_ZERO_SUPR_WINDOW_OFS); };
   void         SetZeroSuprWindow(unsigned int value) { SetRegMask(WD2_ZERO_SUPR_WINDOW_REG, WD2_ZERO_SUPR_WINDOW_MASK, WD2_ZERO_SUPR_WINDOW_OFS, value); };



   ////// ------ Control Register 16 [0x1040]: RST - Reset bits for specific firmwar units (Default: 0x00000000) ------ //////

   // 0x00004000: DAQ_PLL_RST - Reset the PLL for the DAQ clock
   unsigned int GetDaqPllRst() { return BitExtractControl(WD2_DAQ_PLL_RST_REG, WD2_DAQ_PLL_RST_MASK, WD2_DAQ_PLL_RST_OFS); };
   void         SetDaqPllRst(unsigned int value) { SetRegMask(WD2_DAQ_PLL_RST_REG, WD2_DAQ_PLL_RST_MASK, WD2_DAQ_PLL_RST_OFS, value); };

   // 0x00002000: DCB_OSERDES_PLL_RST - Reset the PLL of the DCB OSERDES
   unsigned int GetDcbOserdesPllRst() { return BitExtractControl(WD2_DCB_OSERDES_PLL_RST_REG, WD2_DCB_OSERDES_PLL_RST_MASK, WD2_DCB_OSERDES_PLL_RST_OFS); };
   void         SetDcbOserdesPllRst(unsigned int value) { SetRegMask(WD2_DCB_OSERDES_PLL_RST_REG, WD2_DCB_OSERDES_PLL_RST_MASK, WD2_DCB_OSERDES_PLL_RST_OFS, value); };

   // 0x00001000: TCB_OSERDES_PLL_RST - Reset the PLL of the TCB OSERDES
   unsigned int GetTcbOserdesPllRst() { return BitExtractControl(WD2_TCB_OSERDES_PLL_RST_REG, WD2_TCB_OSERDES_PLL_RST_MASK, WD2_TCB_OSERDES_PLL_RST_OFS); };
   void         SetTcbOserdesPllRst(unsigned int value) { SetRegMask(WD2_TCB_OSERDES_PLL_RST_REG, WD2_TCB_OSERDES_PLL_RST_MASK, WD2_TCB_OSERDES_PLL_RST_OFS, value); };

   // 0x00000800: DCB_OSERDES_IF_RST - Reset the DCB OSERDES interface
   unsigned int GetDcbOserdesIfRst() { return BitExtractControl(WD2_DCB_OSERDES_IF_RST_REG, WD2_DCB_OSERDES_IF_RST_MASK, WD2_DCB_OSERDES_IF_RST_OFS); };
   void         SetDcbOserdesIfRst(unsigned int value) { SetRegMask(WD2_DCB_OSERDES_IF_RST_REG, WD2_DCB_OSERDES_IF_RST_MASK, WD2_DCB_OSERDES_IF_RST_OFS, value); };

   // 0x00000400: TCB_OSERDES_IF_RST - Reset the TCB OSERDES interface
   unsigned int GetTcbOserdesIfRst() { return BitExtractControl(WD2_TCB_OSERDES_IF_RST_REG, WD2_TCB_OSERDES_IF_RST_MASK, WD2_TCB_OSERDES_IF_RST_OFS); };
   void         SetTcbOserdesIfRst(unsigned int value) { SetRegMask(WD2_TCB_OSERDES_IF_RST_REG, WD2_TCB_OSERDES_IF_RST_MASK, WD2_TCB_OSERDES_IF_RST_OFS, value); };

   // 0x00000200: SCALER_RST - Reset all scalers
   unsigned int GetScalerRst() { return BitExtractControl(WD2_SCALER_RST_REG, WD2_SCALER_RST_MASK, WD2_SCALER_RST_OFS); };
   void         SetScalerRst(unsigned int value) { SetRegMask(WD2_SCALER_RST_REG, WD2_SCALER_RST_MASK, WD2_SCALER_RST_OFS, value); };

   // 0x00000100: TRB_PARITY_ERROR_COUNT_RST - Reset the parity error counter of the trigger info serial connection
   unsigned int GetTrbParityErrorCountRst() { return BitExtractControl(WD2_TRB_PARITY_ERROR_COUNT_RST_REG, WD2_TRB_PARITY_ERROR_COUNT_RST_MASK, WD2_TRB_PARITY_ERROR_COUNT_RST_OFS); };
   void         SetTrbParityErrorCountRst(unsigned int value) { SetRegMask(WD2_TRB_PARITY_ERROR_COUNT_RST_REG, WD2_TRB_PARITY_ERROR_COUNT_RST_MASK, WD2_TRB_PARITY_ERROR_COUNT_RST_OFS, value); };

   // 0x00000080: LMK_SYNC_LOCAL - Control LMK SYNC signal from FPGA: 0 = run / 1 = sync
   unsigned int GetLmkSyncLocal() { return BitExtractControl(WD2_LMK_SYNC_LOCAL_REG, WD2_LMK_SYNC_LOCAL_MASK, WD2_LMK_SYNC_LOCAL_OFS); };
   void         SetLmkSyncLocal(unsigned int value) { SetRegMask(WD2_LMK_SYNC_LOCAL_REG, WD2_LMK_SYNC_LOCAL_MASK, WD2_LMK_SYNC_LOCAL_OFS, value); };

   // 0x00000040: ADC_RST - ADC reset
   unsigned int GetAdcRst() { return BitExtractControl(WD2_ADC_RST_REG, WD2_ADC_RST_MASK, WD2_ADC_RST_OFS); };
   void         SetAdcRst(unsigned int value) { SetRegMask(WD2_ADC_RST_REG, WD2_ADC_RST_MASK, WD2_ADC_RST_OFS, value); };

   // 0x00000020: ADC_IF_RST - Reset the ADC interface
   unsigned int GetAdcIfRst() { return BitExtractControl(WD2_ADC_IF_RST_REG, WD2_ADC_IF_RST_MASK, WD2_ADC_IF_RST_OFS); };
   void         SetAdcIfRst(unsigned int value) { SetRegMask(WD2_ADC_IF_RST_REG, WD2_ADC_IF_RST_MASK, WD2_ADC_IF_RST_OFS, value); };

   // 0x00000010: DATA_LINK_IF_RST - Reset of the interface between packager and Ethernet/SERDES interface
   unsigned int GetDataLinkIfRst() { return BitExtractControl(WD2_DATA_LINK_IF_RST_REG, WD2_DATA_LINK_IF_RST_MASK, WD2_DATA_LINK_IF_RST_OFS); };
   void         SetDataLinkIfRst(unsigned int value) { SetRegMask(WD2_DATA_LINK_IF_RST_REG, WD2_DATA_LINK_IF_RST_MASK, WD2_DATA_LINK_IF_RST_OFS, value); };

   // 0x00000008: WD_PKGR_RST - WaveDream packager reset
   unsigned int GetWdPkgrRst() { return BitExtractControl(WD2_WD_PKGR_RST_REG, WD2_WD_PKGR_RST_MASK, WD2_WD_PKGR_RST_OFS); };
   void         SetWdPkgrRst(unsigned int value) { SetRegMask(WD2_WD_PKGR_RST_REG, WD2_WD_PKGR_RST_MASK, WD2_WD_PKGR_RST_OFS, value); };

   // 0x00000004: EVENT_COUNTER_RST - Event Counter Reset
   unsigned int GetEventCounterRst() { return BitExtractControl(WD2_EVENT_COUNTER_RST_REG, WD2_EVENT_COUNTER_RST_MASK, WD2_EVENT_COUNTER_RST_OFS); };
   void         SetEventCounterRst(unsigned int value) { SetRegMask(WD2_EVENT_COUNTER_RST_REG, WD2_EVENT_COUNTER_RST_MASK, WD2_EVENT_COUNTER_RST_OFS, value); };

   // 0x00000002: DRS_CTRL_FSM_RST - DRS control FSM reset
   unsigned int GetDrsCtrlFsmRst() { return BitExtractControl(WD2_DRS_CTRL_FSM_RST_REG, WD2_DRS_CTRL_FSM_RST_MASK, WD2_DRS_CTRL_FSM_RST_OFS); };
   void         SetDrsCtrlFsmRst(unsigned int value) { SetRegMask(WD2_DRS_CTRL_FSM_RST_REG, WD2_DRS_CTRL_FSM_RST_MASK, WD2_DRS_CTRL_FSM_RST_OFS, value); };

   // 0x00000001: RECONFIGURE_FPGA - Initiate FPGA Reconfiguration
   unsigned int GetReconfigureFpga() { return BitExtractControl(WD2_RECONFIGURE_FPGA_REG, WD2_RECONFIGURE_FPGA_MASK, WD2_RECONFIGURE_FPGA_OFS); };
   void         SetReconfigureFpga(unsigned int value) { SetRegMask(WD2_RECONFIGURE_FPGA_REG, WD2_RECONFIGURE_FPGA_MASK, WD2_RECONFIGURE_FPGA_OFS, value); };



   ////// ------ Control Register 17 [0x1044]: APLY_CFG - Apply settings from regsiter bank to hardware units (Default: 0x00000000) ------ //////

   // 0x00000100: APPLY_SETTINGS_ADC_SAMPLE_DIV - Apply configuration from register bank to ADC sampling frequency (auto update)
   unsigned int GetApplySettingsAdcSampleDiv() { return BitExtractControl(WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_REG, WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_MASK, WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_OFS); };
   void         SetApplySettingsAdcSampleDiv(unsigned int value) { SetRegMask(WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_REG, WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_MASK, WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_OFS, value); };

   // 0x00000080: APPLY_SETTINGS_MAX_PLD_SIZE - Apply configuration from register bank to max samples per packet (auto update)
   unsigned int GetApplySettingsMaxPldSize() { return BitExtractControl(WD2_APPLY_SETTINGS_MAX_PLD_SIZE_REG, WD2_APPLY_SETTINGS_MAX_PLD_SIZE_MASK, WD2_APPLY_SETTINGS_MAX_PLD_SIZE_OFS); };
   void         SetApplySettingsMaxPldSize(unsigned int value) { SetRegMask(WD2_APPLY_SETTINGS_MAX_PLD_SIZE_REG, WD2_APPLY_SETTINGS_MAX_PLD_SIZE_MASK, WD2_APPLY_SETTINGS_MAX_PLD_SIZE_OFS, value); };

   // 0x00000040: APPLY_SETTINGS_HV - Apply configuration from register bank to HV (auto update)
   unsigned int GetApplySettingsHv() { return BitExtractControl(WD2_APPLY_SETTINGS_HV_REG, WD2_APPLY_SETTINGS_HV_MASK, WD2_APPLY_SETTINGS_HV_OFS); };
   void         SetApplySettingsHv(unsigned int value) { SetRegMask(WD2_APPLY_SETTINGS_HV_REG, WD2_APPLY_SETTINGS_HV_MASK, WD2_APPLY_SETTINGS_HV_OFS, value); };

   // 0x00000020: APPLY_SETTINGS_DRS - Apply configuration from register bank to DRS chip (auto update)
   unsigned int GetApplySettingsDrs() { return BitExtractControl(WD2_APPLY_SETTINGS_DRS_REG, WD2_APPLY_SETTINGS_DRS_MASK, WD2_APPLY_SETTINGS_DRS_OFS); };
   void         SetApplySettingsDrs(unsigned int value) { SetRegMask(WD2_APPLY_SETTINGS_DRS_REG, WD2_APPLY_SETTINGS_DRS_MASK, WD2_APPLY_SETTINGS_DRS_OFS, value); };

   // 0x00000010: APPLY_SETTINGS_DAC - Apply configuration from register bank to DAC (auto update)
   unsigned int GetApplySettingsDac() { return BitExtractControl(WD2_APPLY_SETTINGS_DAC_REG, WD2_APPLY_SETTINGS_DAC_MASK, WD2_APPLY_SETTINGS_DAC_OFS); };
   void         SetApplySettingsDac(unsigned int value) { SetRegMask(WD2_APPLY_SETTINGS_DAC_REG, WD2_APPLY_SETTINGS_DAC_MASK, WD2_APPLY_SETTINGS_DAC_OFS, value); };

   // 0x00000008: APPLY_SETTINGS_FRONTEND - Apply configuration from register bank to frontend (auto update)
   unsigned int GetApplySettingsFrontend() { return BitExtractControl(WD2_APPLY_SETTINGS_FRONTEND_REG, WD2_APPLY_SETTINGS_FRONTEND_MASK, WD2_APPLY_SETTINGS_FRONTEND_OFS); };
   void         SetApplySettingsFrontend(unsigned int value) { SetRegMask(WD2_APPLY_SETTINGS_FRONTEND_REG, WD2_APPLY_SETTINGS_FRONTEND_MASK, WD2_APPLY_SETTINGS_FRONTEND_OFS, value); };

   // 0x00000004: APPLY_SETTINGS_CTRL - Apply configuration from register bank control register
   unsigned int GetApplySettingsCtrl() { return BitExtractControl(WD2_APPLY_SETTINGS_CTRL_REG, WD2_APPLY_SETTINGS_CTRL_MASK, WD2_APPLY_SETTINGS_CTRL_OFS); };
   void         SetApplySettingsCtrl(unsigned int value) { SetRegMask(WD2_APPLY_SETTINGS_CTRL_REG, WD2_APPLY_SETTINGS_CTRL_MASK, WD2_APPLY_SETTINGS_CTRL_OFS, value); };

   // 0x00000002: APPLY_SETTINGS_ADC - Apply configuration from register bank to ADC
   unsigned int GetApplySettingsAdc() { return BitExtractControl(WD2_APPLY_SETTINGS_ADC_REG, WD2_APPLY_SETTINGS_ADC_MASK, WD2_APPLY_SETTINGS_ADC_OFS); };
   void         SetApplySettingsAdc(unsigned int value) { SetRegMask(WD2_APPLY_SETTINGS_ADC_REG, WD2_APPLY_SETTINGS_ADC_MASK, WD2_APPLY_SETTINGS_ADC_OFS, value); };

   // 0x00000001: APPLY_SETTINGS_LMK - Apply configuration from regsiter bank to LMK
   unsigned int GetApplySettingsLmk() { return BitExtractControl(WD2_APPLY_SETTINGS_LMK_REG, WD2_APPLY_SETTINGS_LMK_MASK, WD2_APPLY_SETTINGS_LMK_OFS); };
   void         SetApplySettingsLmk(unsigned int value) { SetRegMask(WD2_APPLY_SETTINGS_LMK_REG, WD2_APPLY_SETTINGS_LMK_MASK, WD2_APPLY_SETTINGS_LMK_OFS, value); };



   ////// ------ Control Register 18 [0x1048]: DAC0_A_B - DAC0 values for Channel A and B (Default: 0x9EC045A0) ------ //////

   // 0xFFFF0000: DAC0_CH_A - Set DAC0 channel A (ROFS) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
   unsigned int GetDac0ChA() { return BitExtractControl(WD2_DAC0_CH_A_REG, WD2_DAC0_CH_A_MASK, WD2_DAC0_CH_A_OFS); };
   void         SetDac0ChA(unsigned int value) { SetRegMask(WD2_DAC0_CH_A_REG, WD2_DAC0_CH_A_MASK, WD2_DAC0_CH_A_OFS, value); };

   // 0x0000FFFF: DAC0_CH_B - Set DAC0 channel B (OFS) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (+/- 0.625V)
   unsigned int GetDac0ChB() { return BitExtractControl(WD2_DAC0_CH_B_REG, WD2_DAC0_CH_B_MASK, WD2_DAC0_CH_B_OFS); };
   void         SetDac0ChB(unsigned int value) { SetRegMask(WD2_DAC0_CH_B_REG, WD2_DAC0_CH_B_MASK, WD2_DAC0_CH_B_OFS, value); };



   ////// ------ Control Register 19 [0x104C]: DAC0_C_D - DAC0 values for Channel C and D (Default: 0x00000000) ------ //////

   // 0xFFFF0000: DAC0_CH_C - Set DAC0 channel C (CAL_DC) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (+/- 0.625V)
   unsigned int GetDac0ChC() { return BitExtractControl(WD2_DAC0_CH_C_REG, WD2_DAC0_CH_C_MASK, WD2_DAC0_CH_C_OFS); };
   void         SetDac0ChC(unsigned int value) { SetRegMask(WD2_DAC0_CH_C_REG, WD2_DAC0_CH_C_MASK, WD2_DAC0_CH_C_OFS, value); };

   // 0x0000FFFF: DAC0_CH_D - Set DAC0 channel D (PULSE_AMP) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..1V)
   unsigned int GetDac0ChD() { return BitExtractControl(WD2_DAC0_CH_D_REG, WD2_DAC0_CH_D_MASK, WD2_DAC0_CH_D_OFS); };
   void         SetDac0ChD(unsigned int value) { SetRegMask(WD2_DAC0_CH_D_REG, WD2_DAC0_CH_D_MASK, WD2_DAC0_CH_D_OFS, value); };



   ////// ------ Control Register 20 [0x1050]: DAC0_E_F - DAC0 values for Channel E and F (Default: 0x00000000) ------ //////

   // 0xFFFF0000: DAC0_CH_E - Set DAC0 channel E (PZC_LEVEL) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (+/- 2.5V)
   unsigned int GetDac0ChE() { return BitExtractControl(WD2_DAC0_CH_E_REG, WD2_DAC0_CH_E_MASK, WD2_DAC0_CH_E_OFS); };
   void         SetDac0ChE(unsigned int value) { SetRegMask(WD2_DAC0_CH_E_REG, WD2_DAC0_CH_E_MASK, WD2_DAC0_CH_E_OFS, value); };

   // 0x0000FFFF: DAC0_CH_F - Set DAC0 channel F (RESERVED) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
   unsigned int GetDac0ChF() { return BitExtractControl(WD2_DAC0_CH_F_REG, WD2_DAC0_CH_F_MASK, WD2_DAC0_CH_F_OFS); };
   void         SetDac0ChF(unsigned int value) { SetRegMask(WD2_DAC0_CH_F_REG, WD2_DAC0_CH_F_MASK, WD2_DAC0_CH_F_OFS, value); };



   ////// ------ Control Register 21 [0x1054]: DAC0_G_H - DAC0 values for Channel G and H (Default: 0x000047B0) ------ //////

   // 0xFFFF0000: DAC0_CH_G - Set DAC0 channel G (RESERVED) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
   unsigned int GetDac0ChG() { return BitExtractControl(WD2_DAC0_CH_G_REG, WD2_DAC0_CH_G_MASK, WD2_DAC0_CH_G_OFS); };
   void         SetDac0ChG(unsigned int value) { SetRegMask(WD2_DAC0_CH_G_REG, WD2_DAC0_CH_G_MASK, WD2_DAC0_CH_G_OFS, value); };

   // 0x0000FFFF: DAC0_CH_H - Set DAC0 channel H (BIAS) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
   unsigned int GetDac0ChH() { return BitExtractControl(WD2_DAC0_CH_H_REG, WD2_DAC0_CH_H_MASK, WD2_DAC0_CH_H_OFS); };
   void         SetDac0ChH(unsigned int value) { SetRegMask(WD2_DAC0_CH_H_REG, WD2_DAC0_CH_H_MASK, WD2_DAC0_CH_H_OFS, value); };



   ////// ------ Control Register 22 [0x1058]: DAC1_A_B - DAC1 values for Channel A and B (Default: 0x57105710) ------ //////

   // 0xFFFF0000: DAC1_CH_A - Set DAC1 channel A (TLEVEL_0) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
   unsigned int GetDac1ChA() { return BitExtractControl(WD2_DAC1_CH_A_REG, WD2_DAC1_CH_A_MASK, WD2_DAC1_CH_A_OFS); };
   void         SetDac1ChA(unsigned int value) { SetRegMask(WD2_DAC1_CH_A_REG, WD2_DAC1_CH_A_MASK, WD2_DAC1_CH_A_OFS, value); };

   // 0x0000FFFF: DAC1_CH_B - Set DAC1 channel B (TLEVEL_1) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
   unsigned int GetDac1ChB() { return BitExtractControl(WD2_DAC1_CH_B_REG, WD2_DAC1_CH_B_MASK, WD2_DAC1_CH_B_OFS); };
   void         SetDac1ChB(unsigned int value) { SetRegMask(WD2_DAC1_CH_B_REG, WD2_DAC1_CH_B_MASK, WD2_DAC1_CH_B_OFS, value); };



   ////// ------ Control Register 23 [0x105C]: DAC1_C_D - DAC1 values for Channel C and D (Default: 0x57105710) ------ //////

   // 0xFFFF0000: DAC1_CH_C - Set DAC1 channel C (TLEVEL_2) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
   unsigned int GetDac1ChC() { return BitExtractControl(WD2_DAC1_CH_C_REG, WD2_DAC1_CH_C_MASK, WD2_DAC1_CH_C_OFS); };
   void         SetDac1ChC(unsigned int value) { SetRegMask(WD2_DAC1_CH_C_REG, WD2_DAC1_CH_C_MASK, WD2_DAC1_CH_C_OFS, value); };

   // 0x0000FFFF: DAC1_CH_D - Set DAC1 channel D (TLEVEL_3) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
   unsigned int GetDac1ChD() { return BitExtractControl(WD2_DAC1_CH_D_REG, WD2_DAC1_CH_D_MASK, WD2_DAC1_CH_D_OFS); };
   void         SetDac1ChD(unsigned int value) { SetRegMask(WD2_DAC1_CH_D_REG, WD2_DAC1_CH_D_MASK, WD2_DAC1_CH_D_OFS, value); };



   ////// ------ Control Register 24 [0x1060]: DAC1_E_F - DAC1 values for Channel E and F (Default: 0x57105710) ------ //////

   // 0xFFFF0000: DAC1_CH_E - Set DAC1 channel E (TLEVEL_4) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
   unsigned int GetDac1ChE() { return BitExtractControl(WD2_DAC1_CH_E_REG, WD2_DAC1_CH_E_MASK, WD2_DAC1_CH_E_OFS); };
   void         SetDac1ChE(unsigned int value) { SetRegMask(WD2_DAC1_CH_E_REG, WD2_DAC1_CH_E_MASK, WD2_DAC1_CH_E_OFS, value); };

   // 0x0000FFFF: DAC1_CH_F - Set DAC1 channel F (TLEVEL_5) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
   unsigned int GetDac1ChF() { return BitExtractControl(WD2_DAC1_CH_F_REG, WD2_DAC1_CH_F_MASK, WD2_DAC1_CH_F_OFS); };
   void         SetDac1ChF(unsigned int value) { SetRegMask(WD2_DAC1_CH_F_REG, WD2_DAC1_CH_F_MASK, WD2_DAC1_CH_F_OFS, value); };



   ////// ------ Control Register 25 [0x1064]: DAC1_G_H - DAC1 values for Channel G and H (Default: 0x57105710) ------ //////

   // 0xFFFF0000: DAC1_CH_G - Set DAC1 channel G (TLEVEL_6) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
   unsigned int GetDac1ChG() { return BitExtractControl(WD2_DAC1_CH_G_REG, WD2_DAC1_CH_G_MASK, WD2_DAC1_CH_G_OFS); };
   void         SetDac1ChG(unsigned int value) { SetRegMask(WD2_DAC1_CH_G_REG, WD2_DAC1_CH_G_MASK, WD2_DAC1_CH_G_OFS, value); };

   // 0x0000FFFF: DAC1_CH_H - Set DAC1 channel H (TLEVEL_7) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
   unsigned int GetDac1ChH() { return BitExtractControl(WD2_DAC1_CH_H_REG, WD2_DAC1_CH_H_MASK, WD2_DAC1_CH_H_OFS); };
   void         SetDac1ChH(unsigned int value) { SetRegMask(WD2_DAC1_CH_H_REG, WD2_DAC1_CH_H_MASK, WD2_DAC1_CH_H_OFS, value); };



   ////// ------ Control Register 26 [0x1068]: DAC2_A_B - DAC2 values for Channel A and B (Default: 0x57105710) ------ //////

   // 0xFFFF0000: DAC2_CH_A - Set DAC2 channel A (TLEVEL_8) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
   unsigned int GetDac2ChA() { return BitExtractControl(WD2_DAC2_CH_A_REG, WD2_DAC2_CH_A_MASK, WD2_DAC2_CH_A_OFS); };
   void         SetDac2ChA(unsigned int value) { SetRegMask(WD2_DAC2_CH_A_REG, WD2_DAC2_CH_A_MASK, WD2_DAC2_CH_A_OFS, value); };

   // 0x0000FFFF: DAC2_CH_B - Set DAC2 channel B (TLEVEL_9) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
   unsigned int GetDac2ChB() { return BitExtractControl(WD2_DAC2_CH_B_REG, WD2_DAC2_CH_B_MASK, WD2_DAC2_CH_B_OFS); };
   void         SetDac2ChB(unsigned int value) { SetRegMask(WD2_DAC2_CH_B_REG, WD2_DAC2_CH_B_MASK, WD2_DAC2_CH_B_OFS, value); };



   ////// ------ Control Register 27 [0x106C]: DAC2_C_D - DAC2 values for Channel C and D (Default: 0x57105710) ------ //////

   // 0xFFFF0000: DAC2_CH_C - Set DAC2 channel C (TLEVEL_10) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
   unsigned int GetDac2ChC() { return BitExtractControl(WD2_DAC2_CH_C_REG, WD2_DAC2_CH_C_MASK, WD2_DAC2_CH_C_OFS); };
   void         SetDac2ChC(unsigned int value) { SetRegMask(WD2_DAC2_CH_C_REG, WD2_DAC2_CH_C_MASK, WD2_DAC2_CH_C_OFS, value); };

   // 0x0000FFFF: DAC2_CH_D - Set DAC2 channel D (TLEVEL_11) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
   unsigned int GetDac2ChD() { return BitExtractControl(WD2_DAC2_CH_D_REG, WD2_DAC2_CH_D_MASK, WD2_DAC2_CH_D_OFS); };
   void         SetDac2ChD(unsigned int value) { SetRegMask(WD2_DAC2_CH_D_REG, WD2_DAC2_CH_D_MASK, WD2_DAC2_CH_D_OFS, value); };



   ////// ------ Control Register 28 [0x1070]: DAC2_E_F - DAC2 values for Channel E and F (Default: 0x57105710) ------ //////

   // 0xFFFF0000: DAC2_CH_E - Set DAC2 channel E (TLEVEL_12) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
   unsigned int GetDac2ChE() { return BitExtractControl(WD2_DAC2_CH_E_REG, WD2_DAC2_CH_E_MASK, WD2_DAC2_CH_E_OFS); };
   void         SetDac2ChE(unsigned int value) { SetRegMask(WD2_DAC2_CH_E_REG, WD2_DAC2_CH_E_MASK, WD2_DAC2_CH_E_OFS, value); };

   // 0x0000FFFF: DAC2_CH_F - Set DAC2 channel F (TLEVEL_13) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
   unsigned int GetDac2ChF() { return BitExtractControl(WD2_DAC2_CH_F_REG, WD2_DAC2_CH_F_MASK, WD2_DAC2_CH_F_OFS); };
   void         SetDac2ChF(unsigned int value) { SetRegMask(WD2_DAC2_CH_F_REG, WD2_DAC2_CH_F_MASK, WD2_DAC2_CH_F_OFS, value); };



   ////// ------ Control Register 29 [0x1074]: DAC2_G_H - DAC2 values for Channel G and H (Default: 0x57105710) ------ //////

   // 0xFFFF0000: DAC2_CH_G - Set DAC2 channel G (TLEVEL_14) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
   unsigned int GetDac2ChG() { return BitExtractControl(WD2_DAC2_CH_G_REG, WD2_DAC2_CH_G_MASK, WD2_DAC2_CH_G_OFS); };
   void         SetDac2ChG(unsigned int value) { SetRegMask(WD2_DAC2_CH_G_REG, WD2_DAC2_CH_G_MASK, WD2_DAC2_CH_G_OFS, value); };

   // 0x0000FFFF: DAC2_CH_H - Set DAC2 channel H (TLEVEL_15) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
   unsigned int GetDac2ChH() { return BitExtractControl(WD2_DAC2_CH_H_REG, WD2_DAC2_CH_H_MASK, WD2_DAC2_CH_H_OFS); };
   void         SetDac2ChH(unsigned int value) { SetRegMask(WD2_DAC2_CH_H_REG, WD2_DAC2_CH_H_MASK, WD2_DAC2_CH_H_OFS, value); };



   ////// ------ Control Register 30 [0x1078]: FE_CFG_0_1 - Frontend Settings for Channel 0 and 1 (Default: 0x00020002) ------ //////

   // 0x01000000: FE0_PZC_EN - Frontend channel 0 PZC (pole-zero cancellation) enable (ACDC)
   unsigned int GetFe0PzcEn() { return BitExtractControl(WD2_FE0_PZC_EN_REG, WD2_FE0_PZC_EN_MASK, WD2_FE0_PZC_EN_OFS); };
   void         SetFe0PzcEn(unsigned int value) { SetRegMask(WD2_FE0_PZC_EN_REG, WD2_FE0_PZC_EN_MASK, WD2_FE0_PZC_EN_OFS, value); };

   // 0x00800000: FE0_AMPLIFIER2_COMP_EN - Frontend channel 0 amplifier 2 compensation enable (COMP2)
   unsigned int GetFe0Amplifier2CompEn() { return BitExtractControl(WD2_FE0_AMPLIFIER2_COMP_EN_REG, WD2_FE0_AMPLIFIER2_COMP_EN_MASK, WD2_FE0_AMPLIFIER2_COMP_EN_OFS); };
   void         SetFe0Amplifier2CompEn(unsigned int value) { SetRegMask(WD2_FE0_AMPLIFIER2_COMP_EN_REG, WD2_FE0_AMPLIFIER2_COMP_EN_MASK, WD2_FE0_AMPLIFIER2_COMP_EN_OFS, value); };

   // 0x00400000: FE0_AMPLIFIER2_EN - Frontend channel 0 amplifier 2 enable (gain: 10) (OP2)
   unsigned int GetFe0Amplifier2En() { return BitExtractControl(WD2_FE0_AMPLIFIER2_EN_REG, WD2_FE0_AMPLIFIER2_EN_MASK, WD2_FE0_AMPLIFIER2_EN_OFS); };
   void         SetFe0Amplifier2En(unsigned int value) { SetRegMask(WD2_FE0_AMPLIFIER2_EN_REG, WD2_FE0_AMPLIFIER2_EN_MASK, WD2_FE0_AMPLIFIER2_EN_OFS, value); };

   // 0x00200000: FE0_AMPLIFIER1_COMP_EN - Frontend channel 0 amplifier 1 compensation enable (COMP1)
   unsigned int GetFe0Amplifier1CompEn() { return BitExtractControl(WD2_FE0_AMPLIFIER1_COMP_EN_REG, WD2_FE0_AMPLIFIER1_COMP_EN_MASK, WD2_FE0_AMPLIFIER1_COMP_EN_OFS); };
   void         SetFe0Amplifier1CompEn(unsigned int value) { SetRegMask(WD2_FE0_AMPLIFIER1_COMP_EN_REG, WD2_FE0_AMPLIFIER1_COMP_EN_MASK, WD2_FE0_AMPLIFIER1_COMP_EN_OFS, value); };

   // 0x00100000: FE0_AMPLIFIER1_EN - Frontend channel 0 amplifier 1 enable (gain: 10) (OP1)
   unsigned int GetFe0Amplifier1En() { return BitExtractControl(WD2_FE0_AMPLIFIER1_EN_REG, WD2_FE0_AMPLIFIER1_EN_MASK, WD2_FE0_AMPLIFIER1_EN_OFS); };
   void         SetFe0Amplifier1En(unsigned int value) { SetRegMask(WD2_FE0_AMPLIFIER1_EN_REG, WD2_FE0_AMPLIFIER1_EN_MASK, WD2_FE0_AMPLIFIER1_EN_OFS, value); };

   // 0x000C0000: FE0_ATTENUATION - Frontend channel 0 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
   unsigned int GetFe0Attenuation() { return BitExtractControl(WD2_FE0_ATTENUATION_REG, WD2_FE0_ATTENUATION_MASK, WD2_FE0_ATTENUATION_OFS); };
   void         SetFe0Attenuation(unsigned int value) { SetRegMask(WD2_FE0_ATTENUATION_REG, WD2_FE0_ATTENUATION_MASK, WD2_FE0_ATTENUATION_OFS, value); };

   // 0x00030000: FE0_MUX - Frontend channel 0 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
   unsigned int GetFe0Mux() { return BitExtractControl(WD2_FE0_MUX_REG, WD2_FE0_MUX_MASK, WD2_FE0_MUX_OFS); };
   void         SetFe0Mux(unsigned int value) { SetRegMask(WD2_FE0_MUX_REG, WD2_FE0_MUX_MASK, WD2_FE0_MUX_OFS, value); };

   // 0x00000100: FE1_PZC_EN - Frontend channel 1 PZC (pole-zero cancellation) enable (ACDC)
   unsigned int GetFe1PzcEn() { return BitExtractControl(WD2_FE1_PZC_EN_REG, WD2_FE1_PZC_EN_MASK, WD2_FE1_PZC_EN_OFS); };
   void         SetFe1PzcEn(unsigned int value) { SetRegMask(WD2_FE1_PZC_EN_REG, WD2_FE1_PZC_EN_MASK, WD2_FE1_PZC_EN_OFS, value); };

   // 0x00000080: FE1_AMPLIFIER2_COMP_EN - Frontend channel 1 amplifier 2 compensation enable (COMP2)
   unsigned int GetFe1Amplifier2CompEn() { return BitExtractControl(WD2_FE1_AMPLIFIER2_COMP_EN_REG, WD2_FE1_AMPLIFIER2_COMP_EN_MASK, WD2_FE1_AMPLIFIER2_COMP_EN_OFS); };
   void         SetFe1Amplifier2CompEn(unsigned int value) { SetRegMask(WD2_FE1_AMPLIFIER2_COMP_EN_REG, WD2_FE1_AMPLIFIER2_COMP_EN_MASK, WD2_FE1_AMPLIFIER2_COMP_EN_OFS, value); };

   // 0x00000040: FE1_AMPLIFIER2_EN - Frontend channel 1 amplifier 2 enable (gain: 10) (OP2)
   unsigned int GetFe1Amplifier2En() { return BitExtractControl(WD2_FE1_AMPLIFIER2_EN_REG, WD2_FE1_AMPLIFIER2_EN_MASK, WD2_FE1_AMPLIFIER2_EN_OFS); };
   void         SetFe1Amplifier2En(unsigned int value) { SetRegMask(WD2_FE1_AMPLIFIER2_EN_REG, WD2_FE1_AMPLIFIER2_EN_MASK, WD2_FE1_AMPLIFIER2_EN_OFS, value); };

   // 0x00000020: FE1_AMPLIFIER1_COMP_EN - Frontend channel 1 amplifier 1 compensation enable (COMP1)
   unsigned int GetFe1Amplifier1CompEn() { return BitExtractControl(WD2_FE1_AMPLIFIER1_COMP_EN_REG, WD2_FE1_AMPLIFIER1_COMP_EN_MASK, WD2_FE1_AMPLIFIER1_COMP_EN_OFS); };
   void         SetFe1Amplifier1CompEn(unsigned int value) { SetRegMask(WD2_FE1_AMPLIFIER1_COMP_EN_REG, WD2_FE1_AMPLIFIER1_COMP_EN_MASK, WD2_FE1_AMPLIFIER1_COMP_EN_OFS, value); };

   // 0x00000010: FE1_AMPLIFIER1_EN - Frontend channel 1 amplifier 1 enable (gain: 10) (OP1)
   unsigned int GetFe1Amplifier1En() { return BitExtractControl(WD2_FE1_AMPLIFIER1_EN_REG, WD2_FE1_AMPLIFIER1_EN_MASK, WD2_FE1_AMPLIFIER1_EN_OFS); };
   void         SetFe1Amplifier1En(unsigned int value) { SetRegMask(WD2_FE1_AMPLIFIER1_EN_REG, WD2_FE1_AMPLIFIER1_EN_MASK, WD2_FE1_AMPLIFIER1_EN_OFS, value); };

   // 0x0000000C: FE1_ATTENUATION - Frontend channel 1 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
   unsigned int GetFe1Attenuation() { return BitExtractControl(WD2_FE1_ATTENUATION_REG, WD2_FE1_ATTENUATION_MASK, WD2_FE1_ATTENUATION_OFS); };
   void         SetFe1Attenuation(unsigned int value) { SetRegMask(WD2_FE1_ATTENUATION_REG, WD2_FE1_ATTENUATION_MASK, WD2_FE1_ATTENUATION_OFS, value); };

   // 0x00000003: FE1_MUX - Frontend channel 1 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
   unsigned int GetFe1Mux() { return BitExtractControl(WD2_FE1_MUX_REG, WD2_FE1_MUX_MASK, WD2_FE1_MUX_OFS); };
   void         SetFe1Mux(unsigned int value) { SetRegMask(WD2_FE1_MUX_REG, WD2_FE1_MUX_MASK, WD2_FE1_MUX_OFS, value); };



   ////// ------ Control Register 31 [0x107C]: FE_CFG_2_3 - Frontend Settings for Channel 2 and 3 (Default: 0x00020002) ------ //////

   // 0x01000000: FE2_PZC_EN - Frontend channel 2 PZC (pole-zero cancellation) enable (ACDC)
   unsigned int GetFe2PzcEn() { return BitExtractControl(WD2_FE2_PZC_EN_REG, WD2_FE2_PZC_EN_MASK, WD2_FE2_PZC_EN_OFS); };
   void         SetFe2PzcEn(unsigned int value) { SetRegMask(WD2_FE2_PZC_EN_REG, WD2_FE2_PZC_EN_MASK, WD2_FE2_PZC_EN_OFS, value); };

   // 0x00800000: FE2_AMPLIFIER2_COMP_EN - Frontend channel 2 amplifier 2 compensation enable (COMP2)
   unsigned int GetFe2Amplifier2CompEn() { return BitExtractControl(WD2_FE2_AMPLIFIER2_COMP_EN_REG, WD2_FE2_AMPLIFIER2_COMP_EN_MASK, WD2_FE2_AMPLIFIER2_COMP_EN_OFS); };
   void         SetFe2Amplifier2CompEn(unsigned int value) { SetRegMask(WD2_FE2_AMPLIFIER2_COMP_EN_REG, WD2_FE2_AMPLIFIER2_COMP_EN_MASK, WD2_FE2_AMPLIFIER2_COMP_EN_OFS, value); };

   // 0x00400000: FE2_AMPLIFIER2_EN - Frontend channel 2 amplifier 2 enable (gain: 10) (OP2)
   unsigned int GetFe2Amplifier2En() { return BitExtractControl(WD2_FE2_AMPLIFIER2_EN_REG, WD2_FE2_AMPLIFIER2_EN_MASK, WD2_FE2_AMPLIFIER2_EN_OFS); };
   void         SetFe2Amplifier2En(unsigned int value) { SetRegMask(WD2_FE2_AMPLIFIER2_EN_REG, WD2_FE2_AMPLIFIER2_EN_MASK, WD2_FE2_AMPLIFIER2_EN_OFS, value); };

   // 0x00200000: FE2_AMPLIFIER1_COMP_EN - Frontend channel 2 amplifier 1 compensation enable (COMP1)
   unsigned int GetFe2Amplifier1CompEn() { return BitExtractControl(WD2_FE2_AMPLIFIER1_COMP_EN_REG, WD2_FE2_AMPLIFIER1_COMP_EN_MASK, WD2_FE2_AMPLIFIER1_COMP_EN_OFS); };
   void         SetFe2Amplifier1CompEn(unsigned int value) { SetRegMask(WD2_FE2_AMPLIFIER1_COMP_EN_REG, WD2_FE2_AMPLIFIER1_COMP_EN_MASK, WD2_FE2_AMPLIFIER1_COMP_EN_OFS, value); };

   // 0x00100000: FE2_AMPLIFIER1_EN - Frontend channel 2 amplifier 1 enable (gain: 10) (OP1)
   unsigned int GetFe2Amplifier1En() { return BitExtractControl(WD2_FE2_AMPLIFIER1_EN_REG, WD2_FE2_AMPLIFIER1_EN_MASK, WD2_FE2_AMPLIFIER1_EN_OFS); };
   void         SetFe2Amplifier1En(unsigned int value) { SetRegMask(WD2_FE2_AMPLIFIER1_EN_REG, WD2_FE2_AMPLIFIER1_EN_MASK, WD2_FE2_AMPLIFIER1_EN_OFS, value); };

   // 0x000C0000: FE2_ATTENUATION - Frontend channel 2 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
   unsigned int GetFe2Attenuation() { return BitExtractControl(WD2_FE2_ATTENUATION_REG, WD2_FE2_ATTENUATION_MASK, WD2_FE2_ATTENUATION_OFS); };
   void         SetFe2Attenuation(unsigned int value) { SetRegMask(WD2_FE2_ATTENUATION_REG, WD2_FE2_ATTENUATION_MASK, WD2_FE2_ATTENUATION_OFS, value); };

   // 0x00030000: FE2_MUX - Frontend channel 2 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
   unsigned int GetFe2Mux() { return BitExtractControl(WD2_FE2_MUX_REG, WD2_FE2_MUX_MASK, WD2_FE2_MUX_OFS); };
   void         SetFe2Mux(unsigned int value) { SetRegMask(WD2_FE2_MUX_REG, WD2_FE2_MUX_MASK, WD2_FE2_MUX_OFS, value); };

   // 0x00000100: FE3_PZC_EN - Frontend channel 3 PZC (pole-zero cancellation) enable (ACDC)
   unsigned int GetFe3PzcEn() { return BitExtractControl(WD2_FE3_PZC_EN_REG, WD2_FE3_PZC_EN_MASK, WD2_FE3_PZC_EN_OFS); };
   void         SetFe3PzcEn(unsigned int value) { SetRegMask(WD2_FE3_PZC_EN_REG, WD2_FE3_PZC_EN_MASK, WD2_FE3_PZC_EN_OFS, value); };

   // 0x00000080: FE3_AMPLIFIER2_COMP_EN - Frontend channel 3 amplifier 2 compensation enable (COMP2)
   unsigned int GetFe3Amplifier2CompEn() { return BitExtractControl(WD2_FE3_AMPLIFIER2_COMP_EN_REG, WD2_FE3_AMPLIFIER2_COMP_EN_MASK, WD2_FE3_AMPLIFIER2_COMP_EN_OFS); };
   void         SetFe3Amplifier2CompEn(unsigned int value) { SetRegMask(WD2_FE3_AMPLIFIER2_COMP_EN_REG, WD2_FE3_AMPLIFIER2_COMP_EN_MASK, WD2_FE3_AMPLIFIER2_COMP_EN_OFS, value); };

   // 0x00000040: FE3_AMPLIFIER2_EN - Frontend channel 3 amplifier 2 enable (gain: 10) (OP2)
   unsigned int GetFe3Amplifier2En() { return BitExtractControl(WD2_FE3_AMPLIFIER2_EN_REG, WD2_FE3_AMPLIFIER2_EN_MASK, WD2_FE3_AMPLIFIER2_EN_OFS); };
   void         SetFe3Amplifier2En(unsigned int value) { SetRegMask(WD2_FE3_AMPLIFIER2_EN_REG, WD2_FE3_AMPLIFIER2_EN_MASK, WD2_FE3_AMPLIFIER2_EN_OFS, value); };

   // 0x00000020: FE3_AMPLIFIER1_COMP_EN - Frontend channel 3 amplifier 1 compensation enable (COMP1)
   unsigned int GetFe3Amplifier1CompEn() { return BitExtractControl(WD2_FE3_AMPLIFIER1_COMP_EN_REG, WD2_FE3_AMPLIFIER1_COMP_EN_MASK, WD2_FE3_AMPLIFIER1_COMP_EN_OFS); };
   void         SetFe3Amplifier1CompEn(unsigned int value) { SetRegMask(WD2_FE3_AMPLIFIER1_COMP_EN_REG, WD2_FE3_AMPLIFIER1_COMP_EN_MASK, WD2_FE3_AMPLIFIER1_COMP_EN_OFS, value); };

   // 0x00000010: FE3_AMPLIFIER1_EN - Frontend channel 3 amplifier 1 enable (gain: 10) (OP1)
   unsigned int GetFe3Amplifier1En() { return BitExtractControl(WD2_FE3_AMPLIFIER1_EN_REG, WD2_FE3_AMPLIFIER1_EN_MASK, WD2_FE3_AMPLIFIER1_EN_OFS); };
   void         SetFe3Amplifier1En(unsigned int value) { SetRegMask(WD2_FE3_AMPLIFIER1_EN_REG, WD2_FE3_AMPLIFIER1_EN_MASK, WD2_FE3_AMPLIFIER1_EN_OFS, value); };

   // 0x0000000C: FE3_ATTENUATION - Frontend channel 3 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
   unsigned int GetFe3Attenuation() { return BitExtractControl(WD2_FE3_ATTENUATION_REG, WD2_FE3_ATTENUATION_MASK, WD2_FE3_ATTENUATION_OFS); };
   void         SetFe3Attenuation(unsigned int value) { SetRegMask(WD2_FE3_ATTENUATION_REG, WD2_FE3_ATTENUATION_MASK, WD2_FE3_ATTENUATION_OFS, value); };

   // 0x00000003: FE3_MUX - Frontend channel 3 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
   unsigned int GetFe3Mux() { return BitExtractControl(WD2_FE3_MUX_REG, WD2_FE3_MUX_MASK, WD2_FE3_MUX_OFS); };
   void         SetFe3Mux(unsigned int value) { SetRegMask(WD2_FE3_MUX_REG, WD2_FE3_MUX_MASK, WD2_FE3_MUX_OFS, value); };



   ////// ------ Control Register 32 [0x1080]: FE_CFG_4_5 - Frontend Settings for Channel 4 and 5 (Default: 0x00020002) ------ //////

   // 0x01000000: FE4_PZC_EN - Frontend channel 4 PZC (pole-zero cancellation) enable (ACDC)
   unsigned int GetFe4PzcEn() { return BitExtractControl(WD2_FE4_PZC_EN_REG, WD2_FE4_PZC_EN_MASK, WD2_FE4_PZC_EN_OFS); };
   void         SetFe4PzcEn(unsigned int value) { SetRegMask(WD2_FE4_PZC_EN_REG, WD2_FE4_PZC_EN_MASK, WD2_FE4_PZC_EN_OFS, value); };

   // 0x00800000: FE4_AMPLIFIER2_COMP_EN - Frontend channel 4 amplifier 2 compensation enable (COMP2)
   unsigned int GetFe4Amplifier2CompEn() { return BitExtractControl(WD2_FE4_AMPLIFIER2_COMP_EN_REG, WD2_FE4_AMPLIFIER2_COMP_EN_MASK, WD2_FE4_AMPLIFIER2_COMP_EN_OFS); };
   void         SetFe4Amplifier2CompEn(unsigned int value) { SetRegMask(WD2_FE4_AMPLIFIER2_COMP_EN_REG, WD2_FE4_AMPLIFIER2_COMP_EN_MASK, WD2_FE4_AMPLIFIER2_COMP_EN_OFS, value); };

   // 0x00400000: FE4_AMPLIFIER2_EN - Frontend channel 4 amplifier 2 enable (gain: 10) (OP2)
   unsigned int GetFe4Amplifier2En() { return BitExtractControl(WD2_FE4_AMPLIFIER2_EN_REG, WD2_FE4_AMPLIFIER2_EN_MASK, WD2_FE4_AMPLIFIER2_EN_OFS); };
   void         SetFe4Amplifier2En(unsigned int value) { SetRegMask(WD2_FE4_AMPLIFIER2_EN_REG, WD2_FE4_AMPLIFIER2_EN_MASK, WD2_FE4_AMPLIFIER2_EN_OFS, value); };

   // 0x00200000: FE4_AMPLIFIER1_COMP_EN - Frontend channel 4 amplifier 1 compensation enable (COMP1)
   unsigned int GetFe4Amplifier1CompEn() { return BitExtractControl(WD2_FE4_AMPLIFIER1_COMP_EN_REG, WD2_FE4_AMPLIFIER1_COMP_EN_MASK, WD2_FE4_AMPLIFIER1_COMP_EN_OFS); };
   void         SetFe4Amplifier1CompEn(unsigned int value) { SetRegMask(WD2_FE4_AMPLIFIER1_COMP_EN_REG, WD2_FE4_AMPLIFIER1_COMP_EN_MASK, WD2_FE4_AMPLIFIER1_COMP_EN_OFS, value); };

   // 0x00100000: FE4_AMPLIFIER1_EN - Frontend channel 4 amplifier 1 enable (gain: 10) (OP1)
   unsigned int GetFe4Amplifier1En() { return BitExtractControl(WD2_FE4_AMPLIFIER1_EN_REG, WD2_FE4_AMPLIFIER1_EN_MASK, WD2_FE4_AMPLIFIER1_EN_OFS); };
   void         SetFe4Amplifier1En(unsigned int value) { SetRegMask(WD2_FE4_AMPLIFIER1_EN_REG, WD2_FE4_AMPLIFIER1_EN_MASK, WD2_FE4_AMPLIFIER1_EN_OFS, value); };

   // 0x000C0000: FE4_ATTENUATION - Frontend channel 4 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
   unsigned int GetFe4Attenuation() { return BitExtractControl(WD2_FE4_ATTENUATION_REG, WD2_FE4_ATTENUATION_MASK, WD2_FE4_ATTENUATION_OFS); };
   void         SetFe4Attenuation(unsigned int value) { SetRegMask(WD2_FE4_ATTENUATION_REG, WD2_FE4_ATTENUATION_MASK, WD2_FE4_ATTENUATION_OFS, value); };

   // 0x00030000: FE4_MUX - Frontend channel 4 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
   unsigned int GetFe4Mux() { return BitExtractControl(WD2_FE4_MUX_REG, WD2_FE4_MUX_MASK, WD2_FE4_MUX_OFS); };
   void         SetFe4Mux(unsigned int value) { SetRegMask(WD2_FE4_MUX_REG, WD2_FE4_MUX_MASK, WD2_FE4_MUX_OFS, value); };

   // 0x00000100: FE5_PZC_EN - Frontend channel 5 PZC (pole-zero cancellation) enable (ACDC)
   unsigned int GetFe5PzcEn() { return BitExtractControl(WD2_FE5_PZC_EN_REG, WD2_FE5_PZC_EN_MASK, WD2_FE5_PZC_EN_OFS); };
   void         SetFe5PzcEn(unsigned int value) { SetRegMask(WD2_FE5_PZC_EN_REG, WD2_FE5_PZC_EN_MASK, WD2_FE5_PZC_EN_OFS, value); };

   // 0x00000080: FE5_AMPLIFIER2_COMP_EN - Frontend channel 5 amplifier 2 compensation enable (COMP2)
   unsigned int GetFe5Amplifier2CompEn() { return BitExtractControl(WD2_FE5_AMPLIFIER2_COMP_EN_REG, WD2_FE5_AMPLIFIER2_COMP_EN_MASK, WD2_FE5_AMPLIFIER2_COMP_EN_OFS); };
   void         SetFe5Amplifier2CompEn(unsigned int value) { SetRegMask(WD2_FE5_AMPLIFIER2_COMP_EN_REG, WD2_FE5_AMPLIFIER2_COMP_EN_MASK, WD2_FE5_AMPLIFIER2_COMP_EN_OFS, value); };

   // 0x00000040: FE5_AMPLIFIER2_EN - Frontend channel 5 amplifier 2 enable (gain: 10) (OP2)
   unsigned int GetFe5Amplifier2En() { return BitExtractControl(WD2_FE5_AMPLIFIER2_EN_REG, WD2_FE5_AMPLIFIER2_EN_MASK, WD2_FE5_AMPLIFIER2_EN_OFS); };
   void         SetFe5Amplifier2En(unsigned int value) { SetRegMask(WD2_FE5_AMPLIFIER2_EN_REG, WD2_FE5_AMPLIFIER2_EN_MASK, WD2_FE5_AMPLIFIER2_EN_OFS, value); };

   // 0x00000020: FE5_AMPLIFIER1_COMP_EN - Frontend channel 5 amplifier 1 compensation enable (COMP1)
   unsigned int GetFe5Amplifier1CompEn() { return BitExtractControl(WD2_FE5_AMPLIFIER1_COMP_EN_REG, WD2_FE5_AMPLIFIER1_COMP_EN_MASK, WD2_FE5_AMPLIFIER1_COMP_EN_OFS); };
   void         SetFe5Amplifier1CompEn(unsigned int value) { SetRegMask(WD2_FE5_AMPLIFIER1_COMP_EN_REG, WD2_FE5_AMPLIFIER1_COMP_EN_MASK, WD2_FE5_AMPLIFIER1_COMP_EN_OFS, value); };

   // 0x00000010: FE5_AMPLIFIER1_EN - Frontend channel 5 amplifier 1 enable (gain: 10) (OP1)
   unsigned int GetFe5Amplifier1En() { return BitExtractControl(WD2_FE5_AMPLIFIER1_EN_REG, WD2_FE5_AMPLIFIER1_EN_MASK, WD2_FE5_AMPLIFIER1_EN_OFS); };
   void         SetFe5Amplifier1En(unsigned int value) { SetRegMask(WD2_FE5_AMPLIFIER1_EN_REG, WD2_FE5_AMPLIFIER1_EN_MASK, WD2_FE5_AMPLIFIER1_EN_OFS, value); };

   // 0x0000000C: FE5_ATTENUATION - Frontend channel 5 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
   unsigned int GetFe5Attenuation() { return BitExtractControl(WD2_FE5_ATTENUATION_REG, WD2_FE5_ATTENUATION_MASK, WD2_FE5_ATTENUATION_OFS); };
   void         SetFe5Attenuation(unsigned int value) { SetRegMask(WD2_FE5_ATTENUATION_REG, WD2_FE5_ATTENUATION_MASK, WD2_FE5_ATTENUATION_OFS, value); };

   // 0x00000003: FE5_MUX - Frontend channel 5 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
   unsigned int GetFe5Mux() { return BitExtractControl(WD2_FE5_MUX_REG, WD2_FE5_MUX_MASK, WD2_FE5_MUX_OFS); };
   void         SetFe5Mux(unsigned int value) { SetRegMask(WD2_FE5_MUX_REG, WD2_FE5_MUX_MASK, WD2_FE5_MUX_OFS, value); };



   ////// ------ Control Register 33 [0x1084]: FE_CFG_6_7 - Frontend Settings for Channel 6 and 7 (Default: 0x00020002) ------ //////

   // 0x01000000: FE6_PZC_EN - Frontend channel 6 PZC (pole-zero cancellation) enable (ACDC)
   unsigned int GetFe6PzcEn() { return BitExtractControl(WD2_FE6_PZC_EN_REG, WD2_FE6_PZC_EN_MASK, WD2_FE6_PZC_EN_OFS); };
   void         SetFe6PzcEn(unsigned int value) { SetRegMask(WD2_FE6_PZC_EN_REG, WD2_FE6_PZC_EN_MASK, WD2_FE6_PZC_EN_OFS, value); };

   // 0x00800000: FE6_AMPLIFIER2_COMP_EN - Frontend channel 6 amplifier 2 compensation enable (COMP2)
   unsigned int GetFe6Amplifier2CompEn() { return BitExtractControl(WD2_FE6_AMPLIFIER2_COMP_EN_REG, WD2_FE6_AMPLIFIER2_COMP_EN_MASK, WD2_FE6_AMPLIFIER2_COMP_EN_OFS); };
   void         SetFe6Amplifier2CompEn(unsigned int value) { SetRegMask(WD2_FE6_AMPLIFIER2_COMP_EN_REG, WD2_FE6_AMPLIFIER2_COMP_EN_MASK, WD2_FE6_AMPLIFIER2_COMP_EN_OFS, value); };

   // 0x00400000: FE6_AMPLIFIER2_EN - Frontend channel 6 amplifier 2 enable (gain: 10) (OP2)
   unsigned int GetFe6Amplifier2En() { return BitExtractControl(WD2_FE6_AMPLIFIER2_EN_REG, WD2_FE6_AMPLIFIER2_EN_MASK, WD2_FE6_AMPLIFIER2_EN_OFS); };
   void         SetFe6Amplifier2En(unsigned int value) { SetRegMask(WD2_FE6_AMPLIFIER2_EN_REG, WD2_FE6_AMPLIFIER2_EN_MASK, WD2_FE6_AMPLIFIER2_EN_OFS, value); };

   // 0x00200000: FE6_AMPLIFIER1_COMP_EN - Frontend channel 6 amplifier 1 compensation enable (COMP1)
   unsigned int GetFe6Amplifier1CompEn() { return BitExtractControl(WD2_FE6_AMPLIFIER1_COMP_EN_REG, WD2_FE6_AMPLIFIER1_COMP_EN_MASK, WD2_FE6_AMPLIFIER1_COMP_EN_OFS); };
   void         SetFe6Amplifier1CompEn(unsigned int value) { SetRegMask(WD2_FE6_AMPLIFIER1_COMP_EN_REG, WD2_FE6_AMPLIFIER1_COMP_EN_MASK, WD2_FE6_AMPLIFIER1_COMP_EN_OFS, value); };

   // 0x00100000: FE6_AMPLIFIER1_EN - Frontend channel 6 amplifier 1 enable (gain: 10) (OP1)
   unsigned int GetFe6Amplifier1En() { return BitExtractControl(WD2_FE6_AMPLIFIER1_EN_REG, WD2_FE6_AMPLIFIER1_EN_MASK, WD2_FE6_AMPLIFIER1_EN_OFS); };
   void         SetFe6Amplifier1En(unsigned int value) { SetRegMask(WD2_FE6_AMPLIFIER1_EN_REG, WD2_FE6_AMPLIFIER1_EN_MASK, WD2_FE6_AMPLIFIER1_EN_OFS, value); };

   // 0x000C0000: FE6_ATTENUATION - Frontend channel 6 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
   unsigned int GetFe6Attenuation() { return BitExtractControl(WD2_FE6_ATTENUATION_REG, WD2_FE6_ATTENUATION_MASK, WD2_FE6_ATTENUATION_OFS); };
   void         SetFe6Attenuation(unsigned int value) { SetRegMask(WD2_FE6_ATTENUATION_REG, WD2_FE6_ATTENUATION_MASK, WD2_FE6_ATTENUATION_OFS, value); };

   // 0x00030000: FE6_MUX - Frontend channel 6 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
   unsigned int GetFe6Mux() { return BitExtractControl(WD2_FE6_MUX_REG, WD2_FE6_MUX_MASK, WD2_FE6_MUX_OFS); };
   void         SetFe6Mux(unsigned int value) { SetRegMask(WD2_FE6_MUX_REG, WD2_FE6_MUX_MASK, WD2_FE6_MUX_OFS, value); };

   // 0x00000100: FE7_PZC_EN - Frontend channel 7 PZC (pole-zero cancellation) enable (ACDC)
   unsigned int GetFe7PzcEn() { return BitExtractControl(WD2_FE7_PZC_EN_REG, WD2_FE7_PZC_EN_MASK, WD2_FE7_PZC_EN_OFS); };
   void         SetFe7PzcEn(unsigned int value) { SetRegMask(WD2_FE7_PZC_EN_REG, WD2_FE7_PZC_EN_MASK, WD2_FE7_PZC_EN_OFS, value); };

   // 0x00000080: FE7_AMPLIFIER2_COMP_EN - Frontend channel 7 amplifier 2 compensation enable (COMP2)
   unsigned int GetFe7Amplifier2CompEn() { return BitExtractControl(WD2_FE7_AMPLIFIER2_COMP_EN_REG, WD2_FE7_AMPLIFIER2_COMP_EN_MASK, WD2_FE7_AMPLIFIER2_COMP_EN_OFS); };
   void         SetFe7Amplifier2CompEn(unsigned int value) { SetRegMask(WD2_FE7_AMPLIFIER2_COMP_EN_REG, WD2_FE7_AMPLIFIER2_COMP_EN_MASK, WD2_FE7_AMPLIFIER2_COMP_EN_OFS, value); };

   // 0x00000040: FE7_AMPLIFIER2_EN - Frontend channel 7 amplifier 2 enable (gain: 10) (OP2)
   unsigned int GetFe7Amplifier2En() { return BitExtractControl(WD2_FE7_AMPLIFIER2_EN_REG, WD2_FE7_AMPLIFIER2_EN_MASK, WD2_FE7_AMPLIFIER2_EN_OFS); };
   void         SetFe7Amplifier2En(unsigned int value) { SetRegMask(WD2_FE7_AMPLIFIER2_EN_REG, WD2_FE7_AMPLIFIER2_EN_MASK, WD2_FE7_AMPLIFIER2_EN_OFS, value); };

   // 0x00000020: FE7_AMPLIFIER1_COMP_EN - Frontend channel 7 amplifier 1 compensation enable (COMP1)
   unsigned int GetFe7Amplifier1CompEn() { return BitExtractControl(WD2_FE7_AMPLIFIER1_COMP_EN_REG, WD2_FE7_AMPLIFIER1_COMP_EN_MASK, WD2_FE7_AMPLIFIER1_COMP_EN_OFS); };
   void         SetFe7Amplifier1CompEn(unsigned int value) { SetRegMask(WD2_FE7_AMPLIFIER1_COMP_EN_REG, WD2_FE7_AMPLIFIER1_COMP_EN_MASK, WD2_FE7_AMPLIFIER1_COMP_EN_OFS, value); };

   // 0x00000010: FE7_AMPLIFIER1_EN - Frontend channel 7 amplifier 1 enable (gain: 10) (OP1)
   unsigned int GetFe7Amplifier1En() { return BitExtractControl(WD2_FE7_AMPLIFIER1_EN_REG, WD2_FE7_AMPLIFIER1_EN_MASK, WD2_FE7_AMPLIFIER1_EN_OFS); };
   void         SetFe7Amplifier1En(unsigned int value) { SetRegMask(WD2_FE7_AMPLIFIER1_EN_REG, WD2_FE7_AMPLIFIER1_EN_MASK, WD2_FE7_AMPLIFIER1_EN_OFS, value); };

   // 0x0000000C: FE7_ATTENUATION - Frontend channel 7 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
   unsigned int GetFe7Attenuation() { return BitExtractControl(WD2_FE7_ATTENUATION_REG, WD2_FE7_ATTENUATION_MASK, WD2_FE7_ATTENUATION_OFS); };
   void         SetFe7Attenuation(unsigned int value) { SetRegMask(WD2_FE7_ATTENUATION_REG, WD2_FE7_ATTENUATION_MASK, WD2_FE7_ATTENUATION_OFS, value); };

   // 0x00000003: FE7_MUX - Frontend channel 7 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
   unsigned int GetFe7Mux() { return BitExtractControl(WD2_FE7_MUX_REG, WD2_FE7_MUX_MASK, WD2_FE7_MUX_OFS); };
   void         SetFe7Mux(unsigned int value) { SetRegMask(WD2_FE7_MUX_REG, WD2_FE7_MUX_MASK, WD2_FE7_MUX_OFS, value); };



   ////// ------ Control Register 34 [0x1088]: FE_CFG_8_9 - Frontend Settings for Channel 8 and 9 (Default: 0x00020002) ------ //////

   // 0x01000000: FE8_PZC_EN - Frontend channel 8 PZC (pole-zero cancellation) enable (ACDC)
   unsigned int GetFe8PzcEn() { return BitExtractControl(WD2_FE8_PZC_EN_REG, WD2_FE8_PZC_EN_MASK, WD2_FE8_PZC_EN_OFS); };
   void         SetFe8PzcEn(unsigned int value) { SetRegMask(WD2_FE8_PZC_EN_REG, WD2_FE8_PZC_EN_MASK, WD2_FE8_PZC_EN_OFS, value); };

   // 0x00800000: FE8_AMPLIFIER2_COMP_EN - Frontend channel 8 amplifier 2 compensation enable (COMP2)
   unsigned int GetFe8Amplifier2CompEn() { return BitExtractControl(WD2_FE8_AMPLIFIER2_COMP_EN_REG, WD2_FE8_AMPLIFIER2_COMP_EN_MASK, WD2_FE8_AMPLIFIER2_COMP_EN_OFS); };
   void         SetFe8Amplifier2CompEn(unsigned int value) { SetRegMask(WD2_FE8_AMPLIFIER2_COMP_EN_REG, WD2_FE8_AMPLIFIER2_COMP_EN_MASK, WD2_FE8_AMPLIFIER2_COMP_EN_OFS, value); };

   // 0x00400000: FE8_AMPLIFIER2_EN - Frontend channel 8 amplifier 2 enable (gain: 10) (OP2)
   unsigned int GetFe8Amplifier2En() { return BitExtractControl(WD2_FE8_AMPLIFIER2_EN_REG, WD2_FE8_AMPLIFIER2_EN_MASK, WD2_FE8_AMPLIFIER2_EN_OFS); };
   void         SetFe8Amplifier2En(unsigned int value) { SetRegMask(WD2_FE8_AMPLIFIER2_EN_REG, WD2_FE8_AMPLIFIER2_EN_MASK, WD2_FE8_AMPLIFIER2_EN_OFS, value); };

   // 0x00200000: FE8_AMPLIFIER1_COMP_EN - Frontend channel 8 amplifier 1 compensation enable (COMP1)
   unsigned int GetFe8Amplifier1CompEn() { return BitExtractControl(WD2_FE8_AMPLIFIER1_COMP_EN_REG, WD2_FE8_AMPLIFIER1_COMP_EN_MASK, WD2_FE8_AMPLIFIER1_COMP_EN_OFS); };
   void         SetFe8Amplifier1CompEn(unsigned int value) { SetRegMask(WD2_FE8_AMPLIFIER1_COMP_EN_REG, WD2_FE8_AMPLIFIER1_COMP_EN_MASK, WD2_FE8_AMPLIFIER1_COMP_EN_OFS, value); };

   // 0x00100000: FE8_AMPLIFIER1_EN - Frontend channel 8 amplifier 1 enable (gain: 10) (OP1)
   unsigned int GetFe8Amplifier1En() { return BitExtractControl(WD2_FE8_AMPLIFIER1_EN_REG, WD2_FE8_AMPLIFIER1_EN_MASK, WD2_FE8_AMPLIFIER1_EN_OFS); };
   void         SetFe8Amplifier1En(unsigned int value) { SetRegMask(WD2_FE8_AMPLIFIER1_EN_REG, WD2_FE8_AMPLIFIER1_EN_MASK, WD2_FE8_AMPLIFIER1_EN_OFS, value); };

   // 0x000C0000: FE8_ATTENUATION - Frontend channel 8 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
   unsigned int GetFe8Attenuation() { return BitExtractControl(WD2_FE8_ATTENUATION_REG, WD2_FE8_ATTENUATION_MASK, WD2_FE8_ATTENUATION_OFS); };
   void         SetFe8Attenuation(unsigned int value) { SetRegMask(WD2_FE8_ATTENUATION_REG, WD2_FE8_ATTENUATION_MASK, WD2_FE8_ATTENUATION_OFS, value); };

   // 0x00030000: FE8_MUX - Frontend channel 8 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
   unsigned int GetFe8Mux() { return BitExtractControl(WD2_FE8_MUX_REG, WD2_FE8_MUX_MASK, WD2_FE8_MUX_OFS); };
   void         SetFe8Mux(unsigned int value) { SetRegMask(WD2_FE8_MUX_REG, WD2_FE8_MUX_MASK, WD2_FE8_MUX_OFS, value); };

   // 0x00000100: FE9_PZC_EN - Frontend channel 9 PZC (pole-zero cancellation) enable (ACDC)
   unsigned int GetFe9PzcEn() { return BitExtractControl(WD2_FE9_PZC_EN_REG, WD2_FE9_PZC_EN_MASK, WD2_FE9_PZC_EN_OFS); };
   void         SetFe9PzcEn(unsigned int value) { SetRegMask(WD2_FE9_PZC_EN_REG, WD2_FE9_PZC_EN_MASK, WD2_FE9_PZC_EN_OFS, value); };

   // 0x00000080: FE9_AMPLIFIER2_COMP_EN - Frontend channel 9 amplifier 2 compensation enable (COMP2)
   unsigned int GetFe9Amplifier2CompEn() { return BitExtractControl(WD2_FE9_AMPLIFIER2_COMP_EN_REG, WD2_FE9_AMPLIFIER2_COMP_EN_MASK, WD2_FE9_AMPLIFIER2_COMP_EN_OFS); };
   void         SetFe9Amplifier2CompEn(unsigned int value) { SetRegMask(WD2_FE9_AMPLIFIER2_COMP_EN_REG, WD2_FE9_AMPLIFIER2_COMP_EN_MASK, WD2_FE9_AMPLIFIER2_COMP_EN_OFS, value); };

   // 0x00000040: FE9_AMPLIFIER2_EN - Frontend channel 9 amplifier 2 enable (gain: 10) (OP2)
   unsigned int GetFe9Amplifier2En() { return BitExtractControl(WD2_FE9_AMPLIFIER2_EN_REG, WD2_FE9_AMPLIFIER2_EN_MASK, WD2_FE9_AMPLIFIER2_EN_OFS); };
   void         SetFe9Amplifier2En(unsigned int value) { SetRegMask(WD2_FE9_AMPLIFIER2_EN_REG, WD2_FE9_AMPLIFIER2_EN_MASK, WD2_FE9_AMPLIFIER2_EN_OFS, value); };

   // 0x00000020: FE9_AMPLIFIER1_COMP_EN - Frontend channel 9 amplifier 1 compensation enable (COMP1)
   unsigned int GetFe9Amplifier1CompEn() { return BitExtractControl(WD2_FE9_AMPLIFIER1_COMP_EN_REG, WD2_FE9_AMPLIFIER1_COMP_EN_MASK, WD2_FE9_AMPLIFIER1_COMP_EN_OFS); };
   void         SetFe9Amplifier1CompEn(unsigned int value) { SetRegMask(WD2_FE9_AMPLIFIER1_COMP_EN_REG, WD2_FE9_AMPLIFIER1_COMP_EN_MASK, WD2_FE9_AMPLIFIER1_COMP_EN_OFS, value); };

   // 0x00000010: FE9_AMPLIFIER1_EN - Frontend channel 9 amplifier 1 enable (gain: 10) (OP1)
   unsigned int GetFe9Amplifier1En() { return BitExtractControl(WD2_FE9_AMPLIFIER1_EN_REG, WD2_FE9_AMPLIFIER1_EN_MASK, WD2_FE9_AMPLIFIER1_EN_OFS); };
   void         SetFe9Amplifier1En(unsigned int value) { SetRegMask(WD2_FE9_AMPLIFIER1_EN_REG, WD2_FE9_AMPLIFIER1_EN_MASK, WD2_FE9_AMPLIFIER1_EN_OFS, value); };

   // 0x0000000C: FE9_ATTENUATION - Frontend channel 9 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
   unsigned int GetFe9Attenuation() { return BitExtractControl(WD2_FE9_ATTENUATION_REG, WD2_FE9_ATTENUATION_MASK, WD2_FE9_ATTENUATION_OFS); };
   void         SetFe9Attenuation(unsigned int value) { SetRegMask(WD2_FE9_ATTENUATION_REG, WD2_FE9_ATTENUATION_MASK, WD2_FE9_ATTENUATION_OFS, value); };

   // 0x00000003: FE9_MUX - Frontend channel 9 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
   unsigned int GetFe9Mux() { return BitExtractControl(WD2_FE9_MUX_REG, WD2_FE9_MUX_MASK, WD2_FE9_MUX_OFS); };
   void         SetFe9Mux(unsigned int value) { SetRegMask(WD2_FE9_MUX_REG, WD2_FE9_MUX_MASK, WD2_FE9_MUX_OFS, value); };



   ////// ------ Control Register 35 [0x108C]: FE_CFG_10_11 - Frontend Settings for Channel 10 and 11 (Default: 0x00020002) ------ //////

   // 0x01000000: FE10_PZC_EN - Frontend channel 10 PZC (pole-zero cancellation) enable (ACDC)
   unsigned int GetFe10PzcEn() { return BitExtractControl(WD2_FE10_PZC_EN_REG, WD2_FE10_PZC_EN_MASK, WD2_FE10_PZC_EN_OFS); };
   void         SetFe10PzcEn(unsigned int value) { SetRegMask(WD2_FE10_PZC_EN_REG, WD2_FE10_PZC_EN_MASK, WD2_FE10_PZC_EN_OFS, value); };

   // 0x00800000: FE10_AMPLIFIER2_COMP_EN - Frontend channel 10 amplifier 2 compensation enable (COMP2)
   unsigned int GetFe10Amplifier2CompEn() { return BitExtractControl(WD2_FE10_AMPLIFIER2_COMP_EN_REG, WD2_FE10_AMPLIFIER2_COMP_EN_MASK, WD2_FE10_AMPLIFIER2_COMP_EN_OFS); };
   void         SetFe10Amplifier2CompEn(unsigned int value) { SetRegMask(WD2_FE10_AMPLIFIER2_COMP_EN_REG, WD2_FE10_AMPLIFIER2_COMP_EN_MASK, WD2_FE10_AMPLIFIER2_COMP_EN_OFS, value); };

   // 0x00400000: FE10_AMPLIFIER2_EN - Frontend channel 10 amplifier 2 enable (gain: 10) (OP2)
   unsigned int GetFe10Amplifier2En() { return BitExtractControl(WD2_FE10_AMPLIFIER2_EN_REG, WD2_FE10_AMPLIFIER2_EN_MASK, WD2_FE10_AMPLIFIER2_EN_OFS); };
   void         SetFe10Amplifier2En(unsigned int value) { SetRegMask(WD2_FE10_AMPLIFIER2_EN_REG, WD2_FE10_AMPLIFIER2_EN_MASK, WD2_FE10_AMPLIFIER2_EN_OFS, value); };

   // 0x00200000: FE10_AMPLIFIER1_COMP_EN - Frontend channel 10 amplifier 1 compensation enable (COMP1)
   unsigned int GetFe10Amplifier1CompEn() { return BitExtractControl(WD2_FE10_AMPLIFIER1_COMP_EN_REG, WD2_FE10_AMPLIFIER1_COMP_EN_MASK, WD2_FE10_AMPLIFIER1_COMP_EN_OFS); };
   void         SetFe10Amplifier1CompEn(unsigned int value) { SetRegMask(WD2_FE10_AMPLIFIER1_COMP_EN_REG, WD2_FE10_AMPLIFIER1_COMP_EN_MASK, WD2_FE10_AMPLIFIER1_COMP_EN_OFS, value); };

   // 0x00100000: FE10_AMPLIFIER1_EN - Frontend channel 10 amplifier 1 enable (gain: 10) (OP1)
   unsigned int GetFe10Amplifier1En() { return BitExtractControl(WD2_FE10_AMPLIFIER1_EN_REG, WD2_FE10_AMPLIFIER1_EN_MASK, WD2_FE10_AMPLIFIER1_EN_OFS); };
   void         SetFe10Amplifier1En(unsigned int value) { SetRegMask(WD2_FE10_AMPLIFIER1_EN_REG, WD2_FE10_AMPLIFIER1_EN_MASK, WD2_FE10_AMPLIFIER1_EN_OFS, value); };

   // 0x000C0000: FE10_ATTENUATION - Frontend channel 10 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
   unsigned int GetFe10Attenuation() { return BitExtractControl(WD2_FE10_ATTENUATION_REG, WD2_FE10_ATTENUATION_MASK, WD2_FE10_ATTENUATION_OFS); };
   void         SetFe10Attenuation(unsigned int value) { SetRegMask(WD2_FE10_ATTENUATION_REG, WD2_FE10_ATTENUATION_MASK, WD2_FE10_ATTENUATION_OFS, value); };

   // 0x00030000: FE10_MUX - Frontend channel 10 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
   unsigned int GetFe10Mux() { return BitExtractControl(WD2_FE10_MUX_REG, WD2_FE10_MUX_MASK, WD2_FE10_MUX_OFS); };
   void         SetFe10Mux(unsigned int value) { SetRegMask(WD2_FE10_MUX_REG, WD2_FE10_MUX_MASK, WD2_FE10_MUX_OFS, value); };

   // 0x00000100: FE11_PZC_EN - Frontend channel 11 PZC (pole-zero cancellation) enable (ACDC)
   unsigned int GetFe11PzcEn() { return BitExtractControl(WD2_FE11_PZC_EN_REG, WD2_FE11_PZC_EN_MASK, WD2_FE11_PZC_EN_OFS); };
   void         SetFe11PzcEn(unsigned int value) { SetRegMask(WD2_FE11_PZC_EN_REG, WD2_FE11_PZC_EN_MASK, WD2_FE11_PZC_EN_OFS, value); };

   // 0x00000080: FE11_AMPLIFIER2_COMP_EN - Frontend channel 11 amplifier 2 compensation enable (COMP2)
   unsigned int GetFe11Amplifier2CompEn() { return BitExtractControl(WD2_FE11_AMPLIFIER2_COMP_EN_REG, WD2_FE11_AMPLIFIER2_COMP_EN_MASK, WD2_FE11_AMPLIFIER2_COMP_EN_OFS); };
   void         SetFe11Amplifier2CompEn(unsigned int value) { SetRegMask(WD2_FE11_AMPLIFIER2_COMP_EN_REG, WD2_FE11_AMPLIFIER2_COMP_EN_MASK, WD2_FE11_AMPLIFIER2_COMP_EN_OFS, value); };

   // 0x00000040: FE11_AMPLIFIER2_EN - Frontend channel 11 amplifier 2 enable (gain: 10) (OP2)
   unsigned int GetFe11Amplifier2En() { return BitExtractControl(WD2_FE11_AMPLIFIER2_EN_REG, WD2_FE11_AMPLIFIER2_EN_MASK, WD2_FE11_AMPLIFIER2_EN_OFS); };
   void         SetFe11Amplifier2En(unsigned int value) { SetRegMask(WD2_FE11_AMPLIFIER2_EN_REG, WD2_FE11_AMPLIFIER2_EN_MASK, WD2_FE11_AMPLIFIER2_EN_OFS, value); };

   // 0x00000020: FE11_AMPLIFIER1_COMP_EN - Frontend channel 11 amplifier 1 compensation enable (COMP1)
   unsigned int GetFe11Amplifier1CompEn() { return BitExtractControl(WD2_FE11_AMPLIFIER1_COMP_EN_REG, WD2_FE11_AMPLIFIER1_COMP_EN_MASK, WD2_FE11_AMPLIFIER1_COMP_EN_OFS); };
   void         SetFe11Amplifier1CompEn(unsigned int value) { SetRegMask(WD2_FE11_AMPLIFIER1_COMP_EN_REG, WD2_FE11_AMPLIFIER1_COMP_EN_MASK, WD2_FE11_AMPLIFIER1_COMP_EN_OFS, value); };

   // 0x00000010: FE11_AMPLIFIER1_EN - Frontend channel 11 amplifier 1 enable (gain: 10) (OP1)
   unsigned int GetFe11Amplifier1En() { return BitExtractControl(WD2_FE11_AMPLIFIER1_EN_REG, WD2_FE11_AMPLIFIER1_EN_MASK, WD2_FE11_AMPLIFIER1_EN_OFS); };
   void         SetFe11Amplifier1En(unsigned int value) { SetRegMask(WD2_FE11_AMPLIFIER1_EN_REG, WD2_FE11_AMPLIFIER1_EN_MASK, WD2_FE11_AMPLIFIER1_EN_OFS, value); };

   // 0x0000000C: FE11_ATTENUATION - Frontend channel 11 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
   unsigned int GetFe11Attenuation() { return BitExtractControl(WD2_FE11_ATTENUATION_REG, WD2_FE11_ATTENUATION_MASK, WD2_FE11_ATTENUATION_OFS); };
   void         SetFe11Attenuation(unsigned int value) { SetRegMask(WD2_FE11_ATTENUATION_REG, WD2_FE11_ATTENUATION_MASK, WD2_FE11_ATTENUATION_OFS, value); };

   // 0x00000003: FE11_MUX - Frontend channel 11 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
   unsigned int GetFe11Mux() { return BitExtractControl(WD2_FE11_MUX_REG, WD2_FE11_MUX_MASK, WD2_FE11_MUX_OFS); };
   void         SetFe11Mux(unsigned int value) { SetRegMask(WD2_FE11_MUX_REG, WD2_FE11_MUX_MASK, WD2_FE11_MUX_OFS, value); };



   ////// ------ Control Register 36 [0x1090]: FE_CFG_12_13 - Frontend Settings for Channel 12 and 13 (Default: 0x00020002) ------ //////

   // 0x01000000: FE12_PZC_EN - Frontend channel 12 PZC (pole-zero cancellation) enable (ACDC)
   unsigned int GetFe12PzcEn() { return BitExtractControl(WD2_FE12_PZC_EN_REG, WD2_FE12_PZC_EN_MASK, WD2_FE12_PZC_EN_OFS); };
   void         SetFe12PzcEn(unsigned int value) { SetRegMask(WD2_FE12_PZC_EN_REG, WD2_FE12_PZC_EN_MASK, WD2_FE12_PZC_EN_OFS, value); };

   // 0x00800000: FE12_AMPLIFIER2_COMP_EN - Frontend channel 12 amplifier 2 compensation enable (COMP2)
   unsigned int GetFe12Amplifier2CompEn() { return BitExtractControl(WD2_FE12_AMPLIFIER2_COMP_EN_REG, WD2_FE12_AMPLIFIER2_COMP_EN_MASK, WD2_FE12_AMPLIFIER2_COMP_EN_OFS); };
   void         SetFe12Amplifier2CompEn(unsigned int value) { SetRegMask(WD2_FE12_AMPLIFIER2_COMP_EN_REG, WD2_FE12_AMPLIFIER2_COMP_EN_MASK, WD2_FE12_AMPLIFIER2_COMP_EN_OFS, value); };

   // 0x00400000: FE12_AMPLIFIER2_EN - Frontend channel 12 amplifier 2 enable (gain: 10) (OP2)
   unsigned int GetFe12Amplifier2En() { return BitExtractControl(WD2_FE12_AMPLIFIER2_EN_REG, WD2_FE12_AMPLIFIER2_EN_MASK, WD2_FE12_AMPLIFIER2_EN_OFS); };
   void         SetFe12Amplifier2En(unsigned int value) { SetRegMask(WD2_FE12_AMPLIFIER2_EN_REG, WD2_FE12_AMPLIFIER2_EN_MASK, WD2_FE12_AMPLIFIER2_EN_OFS, value); };

   // 0x00200000: FE12_AMPLIFIER1_COMP_EN - Frontend channel 12 amplifier 1 compensation enable (COMP1)
   unsigned int GetFe12Amplifier1CompEn() { return BitExtractControl(WD2_FE12_AMPLIFIER1_COMP_EN_REG, WD2_FE12_AMPLIFIER1_COMP_EN_MASK, WD2_FE12_AMPLIFIER1_COMP_EN_OFS); };
   void         SetFe12Amplifier1CompEn(unsigned int value) { SetRegMask(WD2_FE12_AMPLIFIER1_COMP_EN_REG, WD2_FE12_AMPLIFIER1_COMP_EN_MASK, WD2_FE12_AMPLIFIER1_COMP_EN_OFS, value); };

   // 0x00100000: FE12_AMPLIFIER1_EN - Frontend channel 12 amplifier 1 enable (gain: 10) (OP1)
   unsigned int GetFe12Amplifier1En() { return BitExtractControl(WD2_FE12_AMPLIFIER1_EN_REG, WD2_FE12_AMPLIFIER1_EN_MASK, WD2_FE12_AMPLIFIER1_EN_OFS); };
   void         SetFe12Amplifier1En(unsigned int value) { SetRegMask(WD2_FE12_AMPLIFIER1_EN_REG, WD2_FE12_AMPLIFIER1_EN_MASK, WD2_FE12_AMPLIFIER1_EN_OFS, value); };

   // 0x000C0000: FE12_ATTENUATION - Frontend channel 12 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
   unsigned int GetFe12Attenuation() { return BitExtractControl(WD2_FE12_ATTENUATION_REG, WD2_FE12_ATTENUATION_MASK, WD2_FE12_ATTENUATION_OFS); };
   void         SetFe12Attenuation(unsigned int value) { SetRegMask(WD2_FE12_ATTENUATION_REG, WD2_FE12_ATTENUATION_MASK, WD2_FE12_ATTENUATION_OFS, value); };

   // 0x00030000: FE12_MUX - Frontend channel 12 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
   unsigned int GetFe12Mux() { return BitExtractControl(WD2_FE12_MUX_REG, WD2_FE12_MUX_MASK, WD2_FE12_MUX_OFS); };
   void         SetFe12Mux(unsigned int value) { SetRegMask(WD2_FE12_MUX_REG, WD2_FE12_MUX_MASK, WD2_FE12_MUX_OFS, value); };

   // 0x00000100: FE13_PZC_EN - Frontend channel 13 PZC (pole-zero cancellation) enable (ACDC)
   unsigned int GetFe13PzcEn() { return BitExtractControl(WD2_FE13_PZC_EN_REG, WD2_FE13_PZC_EN_MASK, WD2_FE13_PZC_EN_OFS); };
   void         SetFe13PzcEn(unsigned int value) { SetRegMask(WD2_FE13_PZC_EN_REG, WD2_FE13_PZC_EN_MASK, WD2_FE13_PZC_EN_OFS, value); };

   // 0x00000080: FE13_AMPLIFIER2_COMP_EN - Frontend channel 13 amplifier 2 compensation enable (COMP2)
   unsigned int GetFe13Amplifier2CompEn() { return BitExtractControl(WD2_FE13_AMPLIFIER2_COMP_EN_REG, WD2_FE13_AMPLIFIER2_COMP_EN_MASK, WD2_FE13_AMPLIFIER2_COMP_EN_OFS); };
   void         SetFe13Amplifier2CompEn(unsigned int value) { SetRegMask(WD2_FE13_AMPLIFIER2_COMP_EN_REG, WD2_FE13_AMPLIFIER2_COMP_EN_MASK, WD2_FE13_AMPLIFIER2_COMP_EN_OFS, value); };

   // 0x00000040: FE13_AMPLIFIER2_EN - Frontend channel 13 amplifier 2 enable (gain: 10) (OP2)
   unsigned int GetFe13Amplifier2En() { return BitExtractControl(WD2_FE13_AMPLIFIER2_EN_REG, WD2_FE13_AMPLIFIER2_EN_MASK, WD2_FE13_AMPLIFIER2_EN_OFS); };
   void         SetFe13Amplifier2En(unsigned int value) { SetRegMask(WD2_FE13_AMPLIFIER2_EN_REG, WD2_FE13_AMPLIFIER2_EN_MASK, WD2_FE13_AMPLIFIER2_EN_OFS, value); };

   // 0x00000020: FE13_AMPLIFIER1_COMP_EN - Frontend channel 13 amplifier 1 compensation enable (COMP1)
   unsigned int GetFe13Amplifier1CompEn() { return BitExtractControl(WD2_FE13_AMPLIFIER1_COMP_EN_REG, WD2_FE13_AMPLIFIER1_COMP_EN_MASK, WD2_FE13_AMPLIFIER1_COMP_EN_OFS); };
   void         SetFe13Amplifier1CompEn(unsigned int value) { SetRegMask(WD2_FE13_AMPLIFIER1_COMP_EN_REG, WD2_FE13_AMPLIFIER1_COMP_EN_MASK, WD2_FE13_AMPLIFIER1_COMP_EN_OFS, value); };

   // 0x00000010: FE13_AMPLIFIER1_EN - Frontend channel 13 amplifier 1 enable (gain: 10) (OP1)
   unsigned int GetFe13Amplifier1En() { return BitExtractControl(WD2_FE13_AMPLIFIER1_EN_REG, WD2_FE13_AMPLIFIER1_EN_MASK, WD2_FE13_AMPLIFIER1_EN_OFS); };
   void         SetFe13Amplifier1En(unsigned int value) { SetRegMask(WD2_FE13_AMPLIFIER1_EN_REG, WD2_FE13_AMPLIFIER1_EN_MASK, WD2_FE13_AMPLIFIER1_EN_OFS, value); };

   // 0x0000000C: FE13_ATTENUATION - Frontend channel 13 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
   unsigned int GetFe13Attenuation() { return BitExtractControl(WD2_FE13_ATTENUATION_REG, WD2_FE13_ATTENUATION_MASK, WD2_FE13_ATTENUATION_OFS); };
   void         SetFe13Attenuation(unsigned int value) { SetRegMask(WD2_FE13_ATTENUATION_REG, WD2_FE13_ATTENUATION_MASK, WD2_FE13_ATTENUATION_OFS, value); };

   // 0x00000003: FE13_MUX - Frontend channel 13 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
   unsigned int GetFe13Mux() { return BitExtractControl(WD2_FE13_MUX_REG, WD2_FE13_MUX_MASK, WD2_FE13_MUX_OFS); };
   void         SetFe13Mux(unsigned int value) { SetRegMask(WD2_FE13_MUX_REG, WD2_FE13_MUX_MASK, WD2_FE13_MUX_OFS, value); };



   ////// ------ Control Register 37 [0x1094]: FE_CFG_14_15 - Frontend Settings for Channel 14 and 15 (Default: 0x00020002) ------ //////

   // 0x01000000: FE14_PZC_EN - Frontend channel 14 PZC (pole-zero cancellation) enable (ACDC)
   unsigned int GetFe14PzcEn() { return BitExtractControl(WD2_FE14_PZC_EN_REG, WD2_FE14_PZC_EN_MASK, WD2_FE14_PZC_EN_OFS); };
   void         SetFe14PzcEn(unsigned int value) { SetRegMask(WD2_FE14_PZC_EN_REG, WD2_FE14_PZC_EN_MASK, WD2_FE14_PZC_EN_OFS, value); };

   // 0x00800000: FE14_AMPLIFIER2_COMP_EN - Frontend channel 14 amplifier 2 compensation enable (COMP2)
   unsigned int GetFe14Amplifier2CompEn() { return BitExtractControl(WD2_FE14_AMPLIFIER2_COMP_EN_REG, WD2_FE14_AMPLIFIER2_COMP_EN_MASK, WD2_FE14_AMPLIFIER2_COMP_EN_OFS); };
   void         SetFe14Amplifier2CompEn(unsigned int value) { SetRegMask(WD2_FE14_AMPLIFIER2_COMP_EN_REG, WD2_FE14_AMPLIFIER2_COMP_EN_MASK, WD2_FE14_AMPLIFIER2_COMP_EN_OFS, value); };

   // 0x00400000: FE14_AMPLIFIER2_EN - Frontend channel 14 amplifier 2 enable (gain: 10) (OP2)
   unsigned int GetFe14Amplifier2En() { return BitExtractControl(WD2_FE14_AMPLIFIER2_EN_REG, WD2_FE14_AMPLIFIER2_EN_MASK, WD2_FE14_AMPLIFIER2_EN_OFS); };
   void         SetFe14Amplifier2En(unsigned int value) { SetRegMask(WD2_FE14_AMPLIFIER2_EN_REG, WD2_FE14_AMPLIFIER2_EN_MASK, WD2_FE14_AMPLIFIER2_EN_OFS, value); };

   // 0x00200000: FE14_AMPLIFIER1_COMP_EN - Frontend channel 14 amplifier 1 compensation enable (COMP1)
   unsigned int GetFe14Amplifier1CompEn() { return BitExtractControl(WD2_FE14_AMPLIFIER1_COMP_EN_REG, WD2_FE14_AMPLIFIER1_COMP_EN_MASK, WD2_FE14_AMPLIFIER1_COMP_EN_OFS); };
   void         SetFe14Amplifier1CompEn(unsigned int value) { SetRegMask(WD2_FE14_AMPLIFIER1_COMP_EN_REG, WD2_FE14_AMPLIFIER1_COMP_EN_MASK, WD2_FE14_AMPLIFIER1_COMP_EN_OFS, value); };

   // 0x00100000: FE14_AMPLIFIER1_EN - Frontend channel 14 amplifier 1 enable (gain: 10) (OP1)
   unsigned int GetFe14Amplifier1En() { return BitExtractControl(WD2_FE14_AMPLIFIER1_EN_REG, WD2_FE14_AMPLIFIER1_EN_MASK, WD2_FE14_AMPLIFIER1_EN_OFS); };
   void         SetFe14Amplifier1En(unsigned int value) { SetRegMask(WD2_FE14_AMPLIFIER1_EN_REG, WD2_FE14_AMPLIFIER1_EN_MASK, WD2_FE14_AMPLIFIER1_EN_OFS, value); };

   // 0x000C0000: FE14_ATTENUATION - Frontend channel 14 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
   unsigned int GetFe14Attenuation() { return BitExtractControl(WD2_FE14_ATTENUATION_REG, WD2_FE14_ATTENUATION_MASK, WD2_FE14_ATTENUATION_OFS); };
   void         SetFe14Attenuation(unsigned int value) { SetRegMask(WD2_FE14_ATTENUATION_REG, WD2_FE14_ATTENUATION_MASK, WD2_FE14_ATTENUATION_OFS, value); };

   // 0x00030000: FE14_MUX - Frontend channel 14 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
   unsigned int GetFe14Mux() { return BitExtractControl(WD2_FE14_MUX_REG, WD2_FE14_MUX_MASK, WD2_FE14_MUX_OFS); };
   void         SetFe14Mux(unsigned int value) { SetRegMask(WD2_FE14_MUX_REG, WD2_FE14_MUX_MASK, WD2_FE14_MUX_OFS, value); };

   // 0x00000100: FE15_PZC_EN - Frontend channel 15 PZC (pole-zero cancellation) enable (ACDC)
   unsigned int GetFe15PzcEn() { return BitExtractControl(WD2_FE15_PZC_EN_REG, WD2_FE15_PZC_EN_MASK, WD2_FE15_PZC_EN_OFS); };
   void         SetFe15PzcEn(unsigned int value) { SetRegMask(WD2_FE15_PZC_EN_REG, WD2_FE15_PZC_EN_MASK, WD2_FE15_PZC_EN_OFS, value); };

   // 0x00000080: FE15_AMPLIFIER2_COMP_EN - Frontend channel 15 amplifier 2 compensation enable (COMP2)
   unsigned int GetFe15Amplifier2CompEn() { return BitExtractControl(WD2_FE15_AMPLIFIER2_COMP_EN_REG, WD2_FE15_AMPLIFIER2_COMP_EN_MASK, WD2_FE15_AMPLIFIER2_COMP_EN_OFS); };
   void         SetFe15Amplifier2CompEn(unsigned int value) { SetRegMask(WD2_FE15_AMPLIFIER2_COMP_EN_REG, WD2_FE15_AMPLIFIER2_COMP_EN_MASK, WD2_FE15_AMPLIFIER2_COMP_EN_OFS, value); };

   // 0x00000040: FE15_AMPLIFIER2_EN - Frontend channel 15 amplifier 2 enable (gain: 10) (OP2)
   unsigned int GetFe15Amplifier2En() { return BitExtractControl(WD2_FE15_AMPLIFIER2_EN_REG, WD2_FE15_AMPLIFIER2_EN_MASK, WD2_FE15_AMPLIFIER2_EN_OFS); };
   void         SetFe15Amplifier2En(unsigned int value) { SetRegMask(WD2_FE15_AMPLIFIER2_EN_REG, WD2_FE15_AMPLIFIER2_EN_MASK, WD2_FE15_AMPLIFIER2_EN_OFS, value); };

   // 0x00000020: FE15_AMPLIFIER1_COMP_EN - Frontend channel 15 amplifier 1 compensation enable (COMP1)
   unsigned int GetFe15Amplifier1CompEn() { return BitExtractControl(WD2_FE15_AMPLIFIER1_COMP_EN_REG, WD2_FE15_AMPLIFIER1_COMP_EN_MASK, WD2_FE15_AMPLIFIER1_COMP_EN_OFS); };
   void         SetFe15Amplifier1CompEn(unsigned int value) { SetRegMask(WD2_FE15_AMPLIFIER1_COMP_EN_REG, WD2_FE15_AMPLIFIER1_COMP_EN_MASK, WD2_FE15_AMPLIFIER1_COMP_EN_OFS, value); };

   // 0x00000010: FE15_AMPLIFIER1_EN - Frontend channel 15 amplifier 1 enable (gain: 10) (OP1)
   unsigned int GetFe15Amplifier1En() { return BitExtractControl(WD2_FE15_AMPLIFIER1_EN_REG, WD2_FE15_AMPLIFIER1_EN_MASK, WD2_FE15_AMPLIFIER1_EN_OFS); };
   void         SetFe15Amplifier1En(unsigned int value) { SetRegMask(WD2_FE15_AMPLIFIER1_EN_REG, WD2_FE15_AMPLIFIER1_EN_MASK, WD2_FE15_AMPLIFIER1_EN_OFS, value); };

   // 0x0000000C: FE15_ATTENUATION - Frontend channel 15 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
   unsigned int GetFe15Attenuation() { return BitExtractControl(WD2_FE15_ATTENUATION_REG, WD2_FE15_ATTENUATION_MASK, WD2_FE15_ATTENUATION_OFS); };
   void         SetFe15Attenuation(unsigned int value) { SetRegMask(WD2_FE15_ATTENUATION_REG, WD2_FE15_ATTENUATION_MASK, WD2_FE15_ATTENUATION_OFS, value); };

   // 0x00000003: FE15_MUX - Frontend channel 15 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
   unsigned int GetFe15Mux() { return BitExtractControl(WD2_FE15_MUX_REG, WD2_FE15_MUX_MASK, WD2_FE15_MUX_OFS); };
   void         SetFe15Mux(unsigned int value) { SetRegMask(WD2_FE15_MUX_REG, WD2_FE15_MUX_MASK, WD2_FE15_MUX_OFS, value); };



   ////// ------ Control Register 38 [0x1098]: HV_U_TARGET_0 - Target HV Supply Voltage for Channel 0 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_U_TARGET_0 - Float value (u_demand)
   unsigned int GetHvUTarget0() { return BitExtractControl(WD2_HV_U_TARGET_0_REG, WD2_HV_U_TARGET_0_MASK, WD2_HV_U_TARGET_0_OFS); };
   void         SetHvUTarget0(unsigned int value) { SetRegMask(WD2_HV_U_TARGET_0_REG, WD2_HV_U_TARGET_0_MASK, WD2_HV_U_TARGET_0_OFS, value); };



   ////// ------ Control Register 39 [0x109C]: HV_U_TARGET_1 - Target HV Supply Voltage for Channel 1 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_U_TARGET_1 - Float value (u_demand)
   unsigned int GetHvUTarget1() { return BitExtractControl(WD2_HV_U_TARGET_1_REG, WD2_HV_U_TARGET_1_MASK, WD2_HV_U_TARGET_1_OFS); };
   void         SetHvUTarget1(unsigned int value) { SetRegMask(WD2_HV_U_TARGET_1_REG, WD2_HV_U_TARGET_1_MASK, WD2_HV_U_TARGET_1_OFS, value); };



   ////// ------ Control Register 40 [0x10A0]: HV_U_TARGET_2 - Target HV Supply Voltage for Channel 2 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_U_TARGET_2 - Float value (u_demand)
   unsigned int GetHvUTarget2() { return BitExtractControl(WD2_HV_U_TARGET_2_REG, WD2_HV_U_TARGET_2_MASK, WD2_HV_U_TARGET_2_OFS); };
   void         SetHvUTarget2(unsigned int value) { SetRegMask(WD2_HV_U_TARGET_2_REG, WD2_HV_U_TARGET_2_MASK, WD2_HV_U_TARGET_2_OFS, value); };



   ////// ------ Control Register 41 [0x10A4]: HV_U_TARGET_3 - Target HV Supply Voltage for Channel 3 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_U_TARGET_3 - Float value (u_demand)
   unsigned int GetHvUTarget3() { return BitExtractControl(WD2_HV_U_TARGET_3_REG, WD2_HV_U_TARGET_3_MASK, WD2_HV_U_TARGET_3_OFS); };
   void         SetHvUTarget3(unsigned int value) { SetRegMask(WD2_HV_U_TARGET_3_REG, WD2_HV_U_TARGET_3_MASK, WD2_HV_U_TARGET_3_OFS, value); };



   ////// ------ Control Register 42 [0x10A8]: HV_U_TARGET_4 - Target HV Supply Voltage for Channel 4 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_U_TARGET_4 - Float value (u_demand)
   unsigned int GetHvUTarget4() { return BitExtractControl(WD2_HV_U_TARGET_4_REG, WD2_HV_U_TARGET_4_MASK, WD2_HV_U_TARGET_4_OFS); };
   void         SetHvUTarget4(unsigned int value) { SetRegMask(WD2_HV_U_TARGET_4_REG, WD2_HV_U_TARGET_4_MASK, WD2_HV_U_TARGET_4_OFS, value); };



   ////// ------ Control Register 43 [0x10AC]: HV_U_TARGET_5 - Target HV Supply Voltage for Channel 5 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_U_TARGET_5 - Float value (u_demand)
   unsigned int GetHvUTarget5() { return BitExtractControl(WD2_HV_U_TARGET_5_REG, WD2_HV_U_TARGET_5_MASK, WD2_HV_U_TARGET_5_OFS); };
   void         SetHvUTarget5(unsigned int value) { SetRegMask(WD2_HV_U_TARGET_5_REG, WD2_HV_U_TARGET_5_MASK, WD2_HV_U_TARGET_5_OFS, value); };



   ////// ------ Control Register 44 [0x10B0]: HV_U_TARGET_6 - Target HV Supply Voltage for Channel 6 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_U_TARGET_6 - Float value (u_demand)
   unsigned int GetHvUTarget6() { return BitExtractControl(WD2_HV_U_TARGET_6_REG, WD2_HV_U_TARGET_6_MASK, WD2_HV_U_TARGET_6_OFS); };
   void         SetHvUTarget6(unsigned int value) { SetRegMask(WD2_HV_U_TARGET_6_REG, WD2_HV_U_TARGET_6_MASK, WD2_HV_U_TARGET_6_OFS, value); };



   ////// ------ Control Register 45 [0x10B4]: HV_U_TARGET_7 - Target HV Supply Voltage for Channel 7 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_U_TARGET_7 - Float value (u_demand)
   unsigned int GetHvUTarget7() { return BitExtractControl(WD2_HV_U_TARGET_7_REG, WD2_HV_U_TARGET_7_MASK, WD2_HV_U_TARGET_7_OFS); };
   void         SetHvUTarget7(unsigned int value) { SetRegMask(WD2_HV_U_TARGET_7_REG, WD2_HV_U_TARGET_7_MASK, WD2_HV_U_TARGET_7_OFS, value); };



   ////// ------ Control Register 46 [0x10B8]: HV_U_TARGET_8 - Target HV Supply Voltage for Channel 8 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_U_TARGET_8 - Float value (u_demand)
   unsigned int GetHvUTarget8() { return BitExtractControl(WD2_HV_U_TARGET_8_REG, WD2_HV_U_TARGET_8_MASK, WD2_HV_U_TARGET_8_OFS); };
   void         SetHvUTarget8(unsigned int value) { SetRegMask(WD2_HV_U_TARGET_8_REG, WD2_HV_U_TARGET_8_MASK, WD2_HV_U_TARGET_8_OFS, value); };



   ////// ------ Control Register 47 [0x10BC]: HV_U_TARGET_9 - Target HV Supply Voltage for Channel 9 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_U_TARGET_9 - Float value (u_demand)
   unsigned int GetHvUTarget9() { return BitExtractControl(WD2_HV_U_TARGET_9_REG, WD2_HV_U_TARGET_9_MASK, WD2_HV_U_TARGET_9_OFS); };
   void         SetHvUTarget9(unsigned int value) { SetRegMask(WD2_HV_U_TARGET_9_REG, WD2_HV_U_TARGET_9_MASK, WD2_HV_U_TARGET_9_OFS, value); };



   ////// ------ Control Register 48 [0x10C0]: HV_U_TARGET_10 - Target HV Supply Voltage for Channel 10 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_U_TARGET_10 - Float value (u_demand)
   unsigned int GetHvUTarget10() { return BitExtractControl(WD2_HV_U_TARGET_10_REG, WD2_HV_U_TARGET_10_MASK, WD2_HV_U_TARGET_10_OFS); };
   void         SetHvUTarget10(unsigned int value) { SetRegMask(WD2_HV_U_TARGET_10_REG, WD2_HV_U_TARGET_10_MASK, WD2_HV_U_TARGET_10_OFS, value); };



   ////// ------ Control Register 49 [0x10C4]: HV_U_TARGET_11 - Target HV Supply Voltage for Channel 11 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_U_TARGET_11 - Float value (u_demand)
   unsigned int GetHvUTarget11() { return BitExtractControl(WD2_HV_U_TARGET_11_REG, WD2_HV_U_TARGET_11_MASK, WD2_HV_U_TARGET_11_OFS); };
   void         SetHvUTarget11(unsigned int value) { SetRegMask(WD2_HV_U_TARGET_11_REG, WD2_HV_U_TARGET_11_MASK, WD2_HV_U_TARGET_11_OFS, value); };



   ////// ------ Control Register 50 [0x10C8]: HV_U_TARGET_12 - Target HV Supply Voltage for Channel 12 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_U_TARGET_12 - Float value (u_demand)
   unsigned int GetHvUTarget12() { return BitExtractControl(WD2_HV_U_TARGET_12_REG, WD2_HV_U_TARGET_12_MASK, WD2_HV_U_TARGET_12_OFS); };
   void         SetHvUTarget12(unsigned int value) { SetRegMask(WD2_HV_U_TARGET_12_REG, WD2_HV_U_TARGET_12_MASK, WD2_HV_U_TARGET_12_OFS, value); };



   ////// ------ Control Register 51 [0x10CC]: HV_U_TARGET_13 - Target HV Supply Voltage for Channel 13 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_U_TARGET_13 - Float value (u_demand)
   unsigned int GetHvUTarget13() { return BitExtractControl(WD2_HV_U_TARGET_13_REG, WD2_HV_U_TARGET_13_MASK, WD2_HV_U_TARGET_13_OFS); };
   void         SetHvUTarget13(unsigned int value) { SetRegMask(WD2_HV_U_TARGET_13_REG, WD2_HV_U_TARGET_13_MASK, WD2_HV_U_TARGET_13_OFS, value); };



   ////// ------ Control Register 52 [0x10D0]: HV_U_TARGET_14 - Target HV Supply Voltage for Channel 14 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_U_TARGET_14 - Float value (u_demand)
   unsigned int GetHvUTarget14() { return BitExtractControl(WD2_HV_U_TARGET_14_REG, WD2_HV_U_TARGET_14_MASK, WD2_HV_U_TARGET_14_OFS); };
   void         SetHvUTarget14(unsigned int value) { SetRegMask(WD2_HV_U_TARGET_14_REG, WD2_HV_U_TARGET_14_MASK, WD2_HV_U_TARGET_14_OFS, value); };



   ////// ------ Control Register 53 [0x10D4]: HV_U_TARGET_15 - Target HV Supply Voltage for Channel 15 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_U_TARGET_15 - Float value (u_demand)
   unsigned int GetHvUTarget15() { return BitExtractControl(WD2_HV_U_TARGET_15_REG, WD2_HV_U_TARGET_15_MASK, WD2_HV_U_TARGET_15_OFS); };
   void         SetHvUTarget15(unsigned int value) { SetRegMask(WD2_HV_U_TARGET_15_REG, WD2_HV_U_TARGET_15_MASK, WD2_HV_U_TARGET_15_OFS, value); };



   ////// ------ Control Register 54 [0x10D8]: HV_R_SHUNT - Value of the HV Supply Shunt Resistor (Default: 0x00002710) ------ //////

   // 0xFFFFFFFF: HV_R_SHUNT - Resistor value in Ohm (r_current)
   unsigned int GetHvRShunt() { return BitExtractControl(WD2_HV_R_SHUNT_REG, WD2_HV_R_SHUNT_MASK, WD2_HV_R_SHUNT_OFS); };
   void         SetHvRShunt(unsigned int value) { SetRegMask(WD2_HV_R_SHUNT_REG, WD2_HV_R_SHUNT_MASK, WD2_HV_R_SHUNT_OFS, value); };



   ////// ------ Control Register 55 [0x10DC]: LMK_0 - LMK Register 0 (Default: 0x00032100) ------ //////

   // 0x80000000: LMK0_RESET - Resets LMK Registers to Their Power-On State
   unsigned int GetLmk0Reset() { return BitExtractControl(WD2_LMK0_RESET_REG, WD2_LMK0_RESET_MASK, WD2_LMK0_RESET_OFS); };
   void         SetLmk0Reset(unsigned int value) { SetRegMask(WD2_LMK0_RESET_REG, WD2_LMK0_RESET_MASK, WD2_LMK0_RESET_OFS, value); };

   // 0x00060000: LMK0_CLKOUT_MUX - Channel 0 Clock Output Multiplexer (see datasheet)
   unsigned int GetLmk0ClkoutMux() { return BitExtractControl(WD2_LMK0_CLKOUT_MUX_REG, WD2_LMK0_CLKOUT_MUX_MASK, WD2_LMK0_CLKOUT_MUX_OFS); };
   void         SetLmk0ClkoutMux(unsigned int value) { SetRegMask(WD2_LMK0_CLKOUT_MUX_REG, WD2_LMK0_CLKOUT_MUX_MASK, WD2_LMK0_CLKOUT_MUX_OFS, value); };

   // 0x00010000: LMK0_CLKOUT_EN - Channel 0 Clock Output Enable (0 = Disabled, 1 = Enabled)
   unsigned int GetLmk0ClkoutEn() { return BitExtractControl(WD2_LMK0_CLKOUT_EN_REG, WD2_LMK0_CLKOUT_EN_MASK, WD2_LMK0_CLKOUT_EN_OFS); };
   void         SetLmk0ClkoutEn(unsigned int value) { SetRegMask(WD2_LMK0_CLKOUT_EN_REG, WD2_LMK0_CLKOUT_EN_MASK, WD2_LMK0_CLKOUT_EN_OFS, value); };

   // 0x0000FF00: LMK0_CLKOUT_DIV - Channel 0 Clock Output Divider (value x 2) (1..255)
   unsigned int GetLmk0ClkoutDiv() { return BitExtractControl(WD2_LMK0_CLKOUT_DIV_REG, WD2_LMK0_CLKOUT_DIV_MASK, WD2_LMK0_CLKOUT_DIV_OFS); };
   void         SetLmk0ClkoutDiv(unsigned int value) { SetRegMask(WD2_LMK0_CLKOUT_DIV_REG, WD2_LMK0_CLKOUT_DIV_MASK, WD2_LMK0_CLKOUT_DIV_OFS, value); };

   // 0x000000F0: LMK0_CLKOUT_DLY - Channel 0 Clock Output Delay (value x 150ps)
   unsigned int GetLmk0ClkoutDly() { return BitExtractControl(WD2_LMK0_CLKOUT_DLY_REG, WD2_LMK0_CLKOUT_DLY_MASK, WD2_LMK0_CLKOUT_DLY_OFS); };
   void         SetLmk0ClkoutDly(unsigned int value) { SetRegMask(WD2_LMK0_CLKOUT_DLY_REG, WD2_LMK0_CLKOUT_DLY_MASK, WD2_LMK0_CLKOUT_DLY_OFS, value); };



   ////// ------ Control Register 56 [0x10E0]: LMK_1 - LMK Register 1 (Default: 0x00020101) ------ //////

   // 0x00060000: LMK1_CLKOUT_MUX - Channel 1 Clock Output Multiplexer (see datasheet)
   unsigned int GetLmk1ClkoutMux() { return BitExtractControl(WD2_LMK1_CLKOUT_MUX_REG, WD2_LMK1_CLKOUT_MUX_MASK, WD2_LMK1_CLKOUT_MUX_OFS); };
   void         SetLmk1ClkoutMux(unsigned int value) { SetRegMask(WD2_LMK1_CLKOUT_MUX_REG, WD2_LMK1_CLKOUT_MUX_MASK, WD2_LMK1_CLKOUT_MUX_OFS, value); };

   // 0x00010000: LMK1_CLKOUT_EN - Channel 1 Clock Output Enable (0 = Disabled, 1 = Enabled)
   unsigned int GetLmk1ClkoutEn() { return BitExtractControl(WD2_LMK1_CLKOUT_EN_REG, WD2_LMK1_CLKOUT_EN_MASK, WD2_LMK1_CLKOUT_EN_OFS); };
   void         SetLmk1ClkoutEn(unsigned int value) { SetRegMask(WD2_LMK1_CLKOUT_EN_REG, WD2_LMK1_CLKOUT_EN_MASK, WD2_LMK1_CLKOUT_EN_OFS, value); };

   // 0x0000FF00: LMK1_CLKOUT_DIV - Channel 1 Clock Output Divider (value x 2) (1..255)
   unsigned int GetLmk1ClkoutDiv() { return BitExtractControl(WD2_LMK1_CLKOUT_DIV_REG, WD2_LMK1_CLKOUT_DIV_MASK, WD2_LMK1_CLKOUT_DIV_OFS); };
   void         SetLmk1ClkoutDiv(unsigned int value) { SetRegMask(WD2_LMK1_CLKOUT_DIV_REG, WD2_LMK1_CLKOUT_DIV_MASK, WD2_LMK1_CLKOUT_DIV_OFS, value); };

   // 0x000000F0: LMK1_CLKOUT_DLY - Channel 1 Clock Output Delay (value x 150ps)
   unsigned int GetLmk1ClkoutDly() { return BitExtractControl(WD2_LMK1_CLKOUT_DLY_REG, WD2_LMK1_CLKOUT_DLY_MASK, WD2_LMK1_CLKOUT_DLY_OFS); };
   void         SetLmk1ClkoutDly(unsigned int value) { SetRegMask(WD2_LMK1_CLKOUT_DLY_REG, WD2_LMK1_CLKOUT_DLY_MASK, WD2_LMK1_CLKOUT_DLY_OFS, value); };



   ////// ------ Control Register 57 [0x10E4]: LMK_2 - LMK Register 2 (Default: 0x00020102) ------ //////

   // 0x00060000: LMK2_CLKOUT_MUX - Channel 2 Clock Output Multiplexer (see datasheet)
   unsigned int GetLmk2ClkoutMux() { return BitExtractControl(WD2_LMK2_CLKOUT_MUX_REG, WD2_LMK2_CLKOUT_MUX_MASK, WD2_LMK2_CLKOUT_MUX_OFS); };
   void         SetLmk2ClkoutMux(unsigned int value) { SetRegMask(WD2_LMK2_CLKOUT_MUX_REG, WD2_LMK2_CLKOUT_MUX_MASK, WD2_LMK2_CLKOUT_MUX_OFS, value); };

   // 0x00010000: LMK2_CLKOUT_EN - Channel 2 Clock Output Enable (0 = Disabled, 1 = Enabled)
   unsigned int GetLmk2ClkoutEn() { return BitExtractControl(WD2_LMK2_CLKOUT_EN_REG, WD2_LMK2_CLKOUT_EN_MASK, WD2_LMK2_CLKOUT_EN_OFS); };
   void         SetLmk2ClkoutEn(unsigned int value) { SetRegMask(WD2_LMK2_CLKOUT_EN_REG, WD2_LMK2_CLKOUT_EN_MASK, WD2_LMK2_CLKOUT_EN_OFS, value); };

   // 0x0000FF00: LMK2_CLKOUT_DIV - Channel 2 Clock Output Divider (value x 2) (1..255)
   unsigned int GetLmk2ClkoutDiv() { return BitExtractControl(WD2_LMK2_CLKOUT_DIV_REG, WD2_LMK2_CLKOUT_DIV_MASK, WD2_LMK2_CLKOUT_DIV_OFS); };
   void         SetLmk2ClkoutDiv(unsigned int value) { SetRegMask(WD2_LMK2_CLKOUT_DIV_REG, WD2_LMK2_CLKOUT_DIV_MASK, WD2_LMK2_CLKOUT_DIV_OFS, value); };

   // 0x000000F0: LMK2_CLKOUT_DLY - Channel 2 Clock Output Delay (value x 150ps)
   unsigned int GetLmk2ClkoutDly() { return BitExtractControl(WD2_LMK2_CLKOUT_DLY_REG, WD2_LMK2_CLKOUT_DLY_MASK, WD2_LMK2_CLKOUT_DLY_OFS); };
   void         SetLmk2ClkoutDly(unsigned int value) { SetRegMask(WD2_LMK2_CLKOUT_DLY_REG, WD2_LMK2_CLKOUT_DLY_MASK, WD2_LMK2_CLKOUT_DLY_OFS, value); };



   ////// ------ Control Register 58 [0x10E8]: LMK_3 - LMK Register 3 (Default: 0x00000103) ------ //////

   // 0x00060000: LMK3_CLKOUT_MUX - Channel 3 Clock Output Multiplexer (see datasheet)
   unsigned int GetLmk3ClkoutMux() { return BitExtractControl(WD2_LMK3_CLKOUT_MUX_REG, WD2_LMK3_CLKOUT_MUX_MASK, WD2_LMK3_CLKOUT_MUX_OFS); };
   void         SetLmk3ClkoutMux(unsigned int value) { SetRegMask(WD2_LMK3_CLKOUT_MUX_REG, WD2_LMK3_CLKOUT_MUX_MASK, WD2_LMK3_CLKOUT_MUX_OFS, value); };

   // 0x00010000: LMK3_CLKOUT_EN - Channel 3 Clock Output Enable (0 = Disabled, 1 = Enabled)
   unsigned int GetLmk3ClkoutEn() { return BitExtractControl(WD2_LMK3_CLKOUT_EN_REG, WD2_LMK3_CLKOUT_EN_MASK, WD2_LMK3_CLKOUT_EN_OFS); };
   void         SetLmk3ClkoutEn(unsigned int value) { SetRegMask(WD2_LMK3_CLKOUT_EN_REG, WD2_LMK3_CLKOUT_EN_MASK, WD2_LMK3_CLKOUT_EN_OFS, value); };

   // 0x0000FF00: LMK3_CLKOUT_DIV - Channel 3 Clock Output Divider (value x 2) (1..255)
   unsigned int GetLmk3ClkoutDiv() { return BitExtractControl(WD2_LMK3_CLKOUT_DIV_REG, WD2_LMK3_CLKOUT_DIV_MASK, WD2_LMK3_CLKOUT_DIV_OFS); };
   void         SetLmk3ClkoutDiv(unsigned int value) { SetRegMask(WD2_LMK3_CLKOUT_DIV_REG, WD2_LMK3_CLKOUT_DIV_MASK, WD2_LMK3_CLKOUT_DIV_OFS, value); };

   // 0x000000F0: LMK3_CLKOUT_DLY - Channel 3 Clock Output Delay (value x 150ps)
   unsigned int GetLmk3ClkoutDly() { return BitExtractControl(WD2_LMK3_CLKOUT_DLY_REG, WD2_LMK3_CLKOUT_DLY_MASK, WD2_LMK3_CLKOUT_DLY_OFS); };
   void         SetLmk3ClkoutDly(unsigned int value) { SetRegMask(WD2_LMK3_CLKOUT_DLY_REG, WD2_LMK3_CLKOUT_DLY_MASK, WD2_LMK3_CLKOUT_DLY_OFS, value); };



   ////// ------ Control Register 59 [0x10EC]: LMK_4 - LMK Register 4 (Default: 0x00030104) ------ //////

   // 0x00060000: LMK4_CLKOUT_MUX - Channel 4 Clock Output Multiplexer (see datasheet)
   unsigned int GetLmk4ClkoutMux() { return BitExtractControl(WD2_LMK4_CLKOUT_MUX_REG, WD2_LMK4_CLKOUT_MUX_MASK, WD2_LMK4_CLKOUT_MUX_OFS); };
   void         SetLmk4ClkoutMux(unsigned int value) { SetRegMask(WD2_LMK4_CLKOUT_MUX_REG, WD2_LMK4_CLKOUT_MUX_MASK, WD2_LMK4_CLKOUT_MUX_OFS, value); };

   // 0x00010000: LMK4_CLKOUT_EN - Channel 4 Clock Output Enable (0 = Disabled, 1 = Enabled)
   unsigned int GetLmk4ClkoutEn() { return BitExtractControl(WD2_LMK4_CLKOUT_EN_REG, WD2_LMK4_CLKOUT_EN_MASK, WD2_LMK4_CLKOUT_EN_OFS); };
   void         SetLmk4ClkoutEn(unsigned int value) { SetRegMask(WD2_LMK4_CLKOUT_EN_REG, WD2_LMK4_CLKOUT_EN_MASK, WD2_LMK4_CLKOUT_EN_OFS, value); };

   // 0x0000FF00: LMK4_CLKOUT_DIV - Channel 4 Clock Output Divider (value x 2) (1..255)
   unsigned int GetLmk4ClkoutDiv() { return BitExtractControl(WD2_LMK4_CLKOUT_DIV_REG, WD2_LMK4_CLKOUT_DIV_MASK, WD2_LMK4_CLKOUT_DIV_OFS); };
   void         SetLmk4ClkoutDiv(unsigned int value) { SetRegMask(WD2_LMK4_CLKOUT_DIV_REG, WD2_LMK4_CLKOUT_DIV_MASK, WD2_LMK4_CLKOUT_DIV_OFS, value); };

   // 0x000000F0: LMK4_CLKOUT_DLY - Channel 4 Clock Output Delay (value x 150ps)
   unsigned int GetLmk4ClkoutDly() { return BitExtractControl(WD2_LMK4_CLKOUT_DLY_REG, WD2_LMK4_CLKOUT_DLY_MASK, WD2_LMK4_CLKOUT_DLY_OFS); };
   void         SetLmk4ClkoutDly(unsigned int value) { SetRegMask(WD2_LMK4_CLKOUT_DLY_REG, WD2_LMK4_CLKOUT_DLY_MASK, WD2_LMK4_CLKOUT_DLY_OFS, value); };



   ////// ------ Control Register 60 [0x10F0]: LMK_5 - LMK Register 5 (Default: 0x00020105) ------ //////

   // 0x00060000: LMK5_CLKOUT_MUX - Channel 5 Clock Output Multiplexer (see datasheet)
   unsigned int GetLmk5ClkoutMux() { return BitExtractControl(WD2_LMK5_CLKOUT_MUX_REG, WD2_LMK5_CLKOUT_MUX_MASK, WD2_LMK5_CLKOUT_MUX_OFS); };
   void         SetLmk5ClkoutMux(unsigned int value) { SetRegMask(WD2_LMK5_CLKOUT_MUX_REG, WD2_LMK5_CLKOUT_MUX_MASK, WD2_LMK5_CLKOUT_MUX_OFS, value); };

   // 0x00010000: LMK5_CLKOUT_EN - Channel 5 Clock Output Enable (0 = Disabled, 1 = Enabled)
   unsigned int GetLmk5ClkoutEn() { return BitExtractControl(WD2_LMK5_CLKOUT_EN_REG, WD2_LMK5_CLKOUT_EN_MASK, WD2_LMK5_CLKOUT_EN_OFS); };
   void         SetLmk5ClkoutEn(unsigned int value) { SetRegMask(WD2_LMK5_CLKOUT_EN_REG, WD2_LMK5_CLKOUT_EN_MASK, WD2_LMK5_CLKOUT_EN_OFS, value); };

   // 0x0000FF00: LMK5_CLKOUT_DIV - Channel 5 Clock Output Divider (value x 2) (1..255)
   unsigned int GetLmk5ClkoutDiv() { return BitExtractControl(WD2_LMK5_CLKOUT_DIV_REG, WD2_LMK5_CLKOUT_DIV_MASK, WD2_LMK5_CLKOUT_DIV_OFS); };
   void         SetLmk5ClkoutDiv(unsigned int value) { SetRegMask(WD2_LMK5_CLKOUT_DIV_REG, WD2_LMK5_CLKOUT_DIV_MASK, WD2_LMK5_CLKOUT_DIV_OFS, value); };

   // 0x000000F0: LMK5_CLKOUT_DLY - Channel 5 Clock Output Delay (value x 150ps)
   unsigned int GetLmk5ClkoutDly() { return BitExtractControl(WD2_LMK5_CLKOUT_DLY_REG, WD2_LMK5_CLKOUT_DLY_MASK, WD2_LMK5_CLKOUT_DLY_OFS); };
   void         SetLmk5ClkoutDly(unsigned int value) { SetRegMask(WD2_LMK5_CLKOUT_DLY_REG, WD2_LMK5_CLKOUT_DLY_MASK, WD2_LMK5_CLKOUT_DLY_OFS, value); };



   ////// ------ Control Register 61 [0x10F4]: LMK_6 - LMK Register 6 (Default: 0x00000106) ------ //////

   // 0x00060000: LMK6_CLKOUT_MUX - Channel 6 Clock Output Multiplexer (see datasheet)
   unsigned int GetLmk6ClkoutMux() { return BitExtractControl(WD2_LMK6_CLKOUT_MUX_REG, WD2_LMK6_CLKOUT_MUX_MASK, WD2_LMK6_CLKOUT_MUX_OFS); };
   void         SetLmk6ClkoutMux(unsigned int value) { SetRegMask(WD2_LMK6_CLKOUT_MUX_REG, WD2_LMK6_CLKOUT_MUX_MASK, WD2_LMK6_CLKOUT_MUX_OFS, value); };

   // 0x00010000: LMK6_CLKOUT_EN - Channel 6 Clock Output Enable (0 = Disabled, 1 = Enabled)
   unsigned int GetLmk6ClkoutEn() { return BitExtractControl(WD2_LMK6_CLKOUT_EN_REG, WD2_LMK6_CLKOUT_EN_MASK, WD2_LMK6_CLKOUT_EN_OFS); };
   void         SetLmk6ClkoutEn(unsigned int value) { SetRegMask(WD2_LMK6_CLKOUT_EN_REG, WD2_LMK6_CLKOUT_EN_MASK, WD2_LMK6_CLKOUT_EN_OFS, value); };

   // 0x0000FF00: LMK6_CLKOUT_DIV - Channel 6 Clock Output Divider (value x 2) (1..255)
   unsigned int GetLmk6ClkoutDiv() { return BitExtractControl(WD2_LMK6_CLKOUT_DIV_REG, WD2_LMK6_CLKOUT_DIV_MASK, WD2_LMK6_CLKOUT_DIV_OFS); };
   void         SetLmk6ClkoutDiv(unsigned int value) { SetRegMask(WD2_LMK6_CLKOUT_DIV_REG, WD2_LMK6_CLKOUT_DIV_MASK, WD2_LMK6_CLKOUT_DIV_OFS, value); };

   // 0x000000F0: LMK6_CLKOUT_DLY - Channel 6 Clock Output Delay (value x 150ps)
   unsigned int GetLmk6ClkoutDly() { return BitExtractControl(WD2_LMK6_CLKOUT_DLY_REG, WD2_LMK6_CLKOUT_DLY_MASK, WD2_LMK6_CLKOUT_DLY_OFS); };
   void         SetLmk6ClkoutDly(unsigned int value) { SetRegMask(WD2_LMK6_CLKOUT_DLY_REG, WD2_LMK6_CLKOUT_DLY_MASK, WD2_LMK6_CLKOUT_DLY_OFS, value); };



   ////// ------ Control Register 62 [0x10F8]: LMK_7 - LMK Register 7 (Default: 0x00026407) ------ //////

   // 0x00060000: LMK7_CLKOUT_MUX - Channel 7 Clock Output Multiplexer (see datasheet)
   unsigned int GetLmk7ClkoutMux() { return BitExtractControl(WD2_LMK7_CLKOUT_MUX_REG, WD2_LMK7_CLKOUT_MUX_MASK, WD2_LMK7_CLKOUT_MUX_OFS); };
   void         SetLmk7ClkoutMux(unsigned int value) { SetRegMask(WD2_LMK7_CLKOUT_MUX_REG, WD2_LMK7_CLKOUT_MUX_MASK, WD2_LMK7_CLKOUT_MUX_OFS, value); };

   // 0x00010000: LMK7_CLKOUT_EN - Channel 7 Clock Output Enable (0 = Disabled, 1 = Enabled)
   unsigned int GetLmk7ClkoutEn() { return BitExtractControl(WD2_LMK7_CLKOUT_EN_REG, WD2_LMK7_CLKOUT_EN_MASK, WD2_LMK7_CLKOUT_EN_OFS); };
   void         SetLmk7ClkoutEn(unsigned int value) { SetRegMask(WD2_LMK7_CLKOUT_EN_REG, WD2_LMK7_CLKOUT_EN_MASK, WD2_LMK7_CLKOUT_EN_OFS, value); };

   // 0x0000FF00: LMK7_CLKOUT_DIV - Channel 7 Clock Output Divider (value x 2) (1..255)
   unsigned int GetLmk7ClkoutDiv() { return BitExtractControl(WD2_LMK7_CLKOUT_DIV_REG, WD2_LMK7_CLKOUT_DIV_MASK, WD2_LMK7_CLKOUT_DIV_OFS); };
   void         SetLmk7ClkoutDiv(unsigned int value) { SetRegMask(WD2_LMK7_CLKOUT_DIV_REG, WD2_LMK7_CLKOUT_DIV_MASK, WD2_LMK7_CLKOUT_DIV_OFS, value); };

   // 0x000000F0: LMK7_CLKOUT_DLY - Channel 7 Clock Output Delay (value x 150ps)
   unsigned int GetLmk7ClkoutDly() { return BitExtractControl(WD2_LMK7_CLKOUT_DLY_REG, WD2_LMK7_CLKOUT_DLY_MASK, WD2_LMK7_CLKOUT_DLY_OFS); };
   void         SetLmk7ClkoutDly(unsigned int value) { SetRegMask(WD2_LMK7_CLKOUT_DLY_REG, WD2_LMK7_CLKOUT_DLY_MASK, WD2_LMK7_CLKOUT_DLY_OFS, value); };



   ////// ------ Control Register 63 [0x10FC]: LMK_8 - LMK Register 8 (Default: 0x10000908) ------ //////

   // 0xFFFFFFF0: LMK8_PHASE_NOISE_OPT - Set LMK Register 8 (Phase Noise Optimization)
   unsigned int GetLmk8PhaseNoiseOpt() { return BitExtractControl(WD2_LMK8_PHASE_NOISE_OPT_REG, WD2_LMK8_PHASE_NOISE_OPT_MASK, WD2_LMK8_PHASE_NOISE_OPT_OFS); };
   void         SetLmk8PhaseNoiseOpt(unsigned int value) { SetRegMask(WD2_LMK8_PHASE_NOISE_OPT_REG, WD2_LMK8_PHASE_NOISE_OPT_MASK, WD2_LMK8_PHASE_NOISE_OPT_OFS, value); };



   ////// ------ Control Register 64 [0x1100]: LMK_9 - LMK Register 9 (Default: 0xA0022A09) ------ //////

   // 0x00010000: LMK9_VBOOST - Voltage Level Boost for Clock Outputs
   unsigned int GetLmk9Vboost() { return BitExtractControl(WD2_LMK9_VBOOST_REG, WD2_LMK9_VBOOST_MASK, WD2_LMK9_VBOOST_OFS); };
   void         SetLmk9Vboost(unsigned int value) { SetRegMask(WD2_LMK9_VBOOST_REG, WD2_LMK9_VBOOST_MASK, WD2_LMK9_VBOOST_OFS, value); };



   ////// ------ Control Register 65 [0x1104]: LMK_11 - LMK Register 11 (Default: 0x0082000B) ------ //////

   // 0x00008000: LMK11_DIV4 - Divider Enable for Digital Lock Detect Circuit
   unsigned int GetLmk11Div4() { return BitExtractControl(WD2_LMK11_DIV4_REG, WD2_LMK11_DIV4_MASK, WD2_LMK11_DIV4_OFS); };
   void         SetLmk11Div4(unsigned int value) { SetRegMask(WD2_LMK11_DIV4_REG, WD2_LMK11_DIV4_MASK, WD2_LMK11_DIV4_OFS, value); };



   ////// ------ Control Register 66 [0x1108]: LMK_13 - LMK Register 13 (Default: 0x029900AD) ------ //////

   // 0x003FC000: LMK13_OSCIN_FREQ - Oscillator Input Calibration Adjustment in MHz (1..200)
   unsigned int GetLmk13OscinFreq() { return BitExtractControl(WD2_LMK13_OSCIN_FREQ_REG, WD2_LMK13_OSCIN_FREQ_MASK, WD2_LMK13_OSCIN_FREQ_OFS); };
   void         SetLmk13OscinFreq(unsigned int value) { SetRegMask(WD2_LMK13_OSCIN_FREQ_REG, WD2_LMK13_OSCIN_FREQ_MASK, WD2_LMK13_OSCIN_FREQ_OFS, value); };

   // 0x00003800: LMK13_VCO_R4_LF - Value for Internal Loop Filter Resistor R4 (0..4) (see datasheet)
   unsigned int GetLmk13VcoR4Lf() { return BitExtractControl(WD2_LMK13_VCO_R4_LF_REG, WD2_LMK13_VCO_R4_LF_MASK, WD2_LMK13_VCO_R4_LF_OFS); };
   void         SetLmk13VcoR4Lf(unsigned int value) { SetRegMask(WD2_LMK13_VCO_R4_LF_REG, WD2_LMK13_VCO_R4_LF_MASK, WD2_LMK13_VCO_R4_LF_OFS, value); };

   // 0x00000700: LMK13_VCO_R3_LF - Value for Internal Loop Filter Resistor R3 (0..4) (see datasheet)
   unsigned int GetLmk13VcoR3Lf() { return BitExtractControl(WD2_LMK13_VCO_R3_LF_REG, WD2_LMK13_VCO_R3_LF_MASK, WD2_LMK13_VCO_R3_LF_OFS); };
   void         SetLmk13VcoR3Lf(unsigned int value) { SetRegMask(WD2_LMK13_VCO_R3_LF_REG, WD2_LMK13_VCO_R3_LF_MASK, WD2_LMK13_VCO_R3_LF_OFS, value); };

   // 0x000000F0: LMK13_VCO_C3_C4_LF - Value for Internal Loop Filter Capacitors C3/C4 (0..11) (see ds)
   unsigned int GetLmk13VcoC3C4Lf() { return BitExtractControl(WD2_LMK13_VCO_C3_C4_LF_REG, WD2_LMK13_VCO_C3_C4_LF_MASK, WD2_LMK13_VCO_C3_C4_LF_OFS); };
   void         SetLmk13VcoC3C4Lf(unsigned int value) { SetRegMask(WD2_LMK13_VCO_C3_C4_LF_REG, WD2_LMK13_VCO_C3_C4_LF_MASK, WD2_LMK13_VCO_C3_C4_LF_OFS, value); };



   ////// ------ Control Register 67 [0x110C]: LMK_14 - LMK Register 14 (Default: 0x0830140E) ------ //////

   // 0x10000000: LMK14_EN_FOUT - Enable for the Fout Pin (0 = Disabled, 1 = Enabled)
   unsigned int GetLmk14EnFout() { return BitExtractControl(WD2_LMK14_EN_FOUT_REG, WD2_LMK14_EN_FOUT_MASK, WD2_LMK14_EN_FOUT_OFS); };
   void         SetLmk14EnFout(unsigned int value) { SetRegMask(WD2_LMK14_EN_FOUT_REG, WD2_LMK14_EN_FOUT_MASK, WD2_LMK14_EN_FOUT_OFS, value); };

   // 0x08000000: LMK14_EN_CLKOUT_GLOBAL - Global Clock Output Enable (0 = All Off, 1 = Normal Operation)
   unsigned int GetLmk14EnClkoutGlobal() { return BitExtractControl(WD2_LMK14_EN_CLKOUT_GLOBAL_REG, WD2_LMK14_EN_CLKOUT_GLOBAL_MASK, WD2_LMK14_EN_CLKOUT_GLOBAL_OFS); };
   void         SetLmk14EnClkoutGlobal(unsigned int value) { SetRegMask(WD2_LMK14_EN_CLKOUT_GLOBAL_REG, WD2_LMK14_EN_CLKOUT_GLOBAL_MASK, WD2_LMK14_EN_CLKOUT_GLOBAL_OFS, value); };

   // 0x04000000: LMK14_POWERDOWN - Powerdown (0 = Normal Operation, 1 = Device Powered Down)
   unsigned int GetLmk14Powerdown() { return BitExtractControl(WD2_LMK14_POWERDOWN_REG, WD2_LMK14_POWERDOWN_MASK, WD2_LMK14_POWERDOWN_OFS); };
   void         SetLmk14Powerdown(unsigned int value) { SetRegMask(WD2_LMK14_POWERDOWN_REG, WD2_LMK14_POWERDOWN_MASK, WD2_LMK14_POWERDOWN_OFS, value); };

   // 0x00F00000: LMK14_PLL_MUX - Output Mode of  LD Pin (0..7,9,11)
   unsigned int GetLmk14PllMux() { return BitExtractControl(WD2_LMK14_PLL_MUX_REG, WD2_LMK14_PLL_MUX_MASK, WD2_LMK14_PLL_MUX_OFS); };
   void         SetLmk14PllMux(unsigned int value) { SetRegMask(WD2_LMK14_PLL_MUX_REG, WD2_LMK14_PLL_MUX_MASK, WD2_LMK14_PLL_MUX_OFS, value); };

   // 0x000FFF00: LMK14_PLL_R - PLL R Divider Value (1..4095)
   unsigned int GetLmk14PllR() { return BitExtractControl(WD2_LMK14_PLL_R_REG, WD2_LMK14_PLL_R_MASK, WD2_LMK14_PLL_R_OFS); };
   void         SetLmk14PllR(unsigned int value) { SetRegMask(WD2_LMK14_PLL_R_REG, WD2_LMK14_PLL_R_MASK, WD2_LMK14_PLL_R_OFS, value); };



   ////// ------ Control Register 68 [0x1110]: LMK_15 - LMK Register 15 (Default: 0xE000200F) ------ //////

   // 0xC0000000: LMK15_PLL_CP_GAIN - PLL Charge Pump Gain (see datasheet) (0..4)
   unsigned int GetLmk15PllCpGain() { return BitExtractControl(WD2_LMK15_PLL_CP_GAIN_REG, WD2_LMK15_PLL_CP_GAIN_MASK, WD2_LMK15_PLL_CP_GAIN_OFS); };
   void         SetLmk15PllCpGain(unsigned int value) { SetRegMask(WD2_LMK15_PLL_CP_GAIN_REG, WD2_LMK15_PLL_CP_GAIN_MASK, WD2_LMK15_PLL_CP_GAIN_OFS, value); };

   // 0x3C000000: LMK15_VCO_DIV - VCO Divider Value (2..8)
   unsigned int GetLmk15VcoDiv() { return BitExtractControl(WD2_LMK15_VCO_DIV_REG, WD2_LMK15_VCO_DIV_MASK, WD2_LMK15_VCO_DIV_OFS); };
   void         SetLmk15VcoDiv(unsigned int value) { SetRegMask(WD2_LMK15_VCO_DIV_REG, WD2_LMK15_VCO_DIV_MASK, WD2_LMK15_VCO_DIV_OFS, value); };

   // 0x03FFFF00: LMK15_PLL_N - PLL N Divider Value (1..0x3FFFF)
   unsigned int GetLmk15PllN() { return BitExtractControl(WD2_LMK15_PLL_N_REG, WD2_LMK15_PLL_N_MASK, WD2_LMK15_PLL_N_OFS); };
   void         SetLmk15PllN(unsigned int value) { SetRegMask(WD2_LMK15_PLL_N_REG, WD2_LMK15_PLL_N_MASK, WD2_LMK15_PLL_N_OFS, value); };



   ////// ------ Control Register 69 [0x1114]: ADC_CFG_IND_TX - ADC Chip Configuration, Index and Transfer Register (Default: 0x180F3F00) ------ //////

   // 0x80000000: ADC_CFG_SDO_ACTIVE_MSB - Activate SDO (to be mirrored to bit24)
   unsigned int GetAdcCfgSdoActiveMsb() { return BitExtractControl(WD2_ADC_CFG_SDO_ACTIVE_MSB_REG, WD2_ADC_CFG_SDO_ACTIVE_MSB_MASK, WD2_ADC_CFG_SDO_ACTIVE_MSB_OFS); };
   void         SetAdcCfgSdoActiveMsb(unsigned int value) { SetRegMask(WD2_ADC_CFG_SDO_ACTIVE_MSB_REG, WD2_ADC_CFG_SDO_ACTIVE_MSB_MASK, WD2_ADC_CFG_SDO_ACTIVE_MSB_OFS, value); };

   // 0x40000000: ADC_CFG_LSB_FIRST_MSB - Transmit LSB First (to be mirrored to bit25)
   unsigned int GetAdcCfgLsbFirstMsb() { return BitExtractControl(WD2_ADC_CFG_LSB_FIRST_MSB_REG, WD2_ADC_CFG_LSB_FIRST_MSB_MASK, WD2_ADC_CFG_LSB_FIRST_MSB_OFS); };
   void         SetAdcCfgLsbFirstMsb(unsigned int value) { SetRegMask(WD2_ADC_CFG_LSB_FIRST_MSB_REG, WD2_ADC_CFG_LSB_FIRST_MSB_MASK, WD2_ADC_CFG_LSB_FIRST_MSB_OFS, value); };

   // 0x20000000: ADC_CFG_SOFT_RESET_MSB - Soft Reset (automatically cleared) (to be mirrored to bit26)
   unsigned int GetAdcCfgSoftResetMsb() { return BitExtractControl(WD2_ADC_CFG_SOFT_RESET_MSB_REG, WD2_ADC_CFG_SOFT_RESET_MSB_MASK, WD2_ADC_CFG_SOFT_RESET_MSB_OFS); };
   void         SetAdcCfgSoftResetMsb(unsigned int value) { SetRegMask(WD2_ADC_CFG_SOFT_RESET_MSB_REG, WD2_ADC_CFG_SOFT_RESET_MSB_MASK, WD2_ADC_CFG_SOFT_RESET_MSB_OFS, value); };

   // 0x10000000: ADC_CFG_16_BIT_ADDR_MSB - ADC Address Mode (to be mirrored to bit27)
   unsigned int GetAdcCfg16BitAddrMsb() { return BitExtractControl(WD2_ADC_CFG_16_BIT_ADDR_MSB_REG, WD2_ADC_CFG_16_BIT_ADDR_MSB_MASK, WD2_ADC_CFG_16_BIT_ADDR_MSB_OFS); };
   void         SetAdcCfg16BitAddrMsb(unsigned int value) { SetRegMask(WD2_ADC_CFG_16_BIT_ADDR_MSB_REG, WD2_ADC_CFG_16_BIT_ADDR_MSB_MASK, WD2_ADC_CFG_16_BIT_ADDR_MSB_OFS, value); };

   // 0x08000000: ADC_CFG_16_BIT_ADDR_LSB - ADC Address Mode (to be mirrored to bit28)
   unsigned int GetAdcCfg16BitAddrLsb() { return BitExtractControl(WD2_ADC_CFG_16_BIT_ADDR_LSB_REG, WD2_ADC_CFG_16_BIT_ADDR_LSB_MASK, WD2_ADC_CFG_16_BIT_ADDR_LSB_OFS); };
   void         SetAdcCfg16BitAddrLsb(unsigned int value) { SetRegMask(WD2_ADC_CFG_16_BIT_ADDR_LSB_REG, WD2_ADC_CFG_16_BIT_ADDR_LSB_MASK, WD2_ADC_CFG_16_BIT_ADDR_LSB_OFS, value); };

   // 0x04000000: ADC_CFG_SOFT_RESET_LSB - Soft Reset (automatically cleared) (to be mirrored to bit29)
   unsigned int GetAdcCfgSoftResetLsb() { return BitExtractControl(WD2_ADC_CFG_SOFT_RESET_LSB_REG, WD2_ADC_CFG_SOFT_RESET_LSB_MASK, WD2_ADC_CFG_SOFT_RESET_LSB_OFS); };
   void         SetAdcCfgSoftResetLsb(unsigned int value) { SetRegMask(WD2_ADC_CFG_SOFT_RESET_LSB_REG, WD2_ADC_CFG_SOFT_RESET_LSB_MASK, WD2_ADC_CFG_SOFT_RESET_LSB_OFS, value); };

   // 0x02000000: ADC_CFG_LSB_FIRST_LSB - Transmit LSB First (to be mirrored to bit30)
   unsigned int GetAdcCfgLsbFirstLsb() { return BitExtractControl(WD2_ADC_CFG_LSB_FIRST_LSB_REG, WD2_ADC_CFG_LSB_FIRST_LSB_MASK, WD2_ADC_CFG_LSB_FIRST_LSB_OFS); };
   void         SetAdcCfgLsbFirstLsb(unsigned int value) { SetRegMask(WD2_ADC_CFG_LSB_FIRST_LSB_REG, WD2_ADC_CFG_LSB_FIRST_LSB_MASK, WD2_ADC_CFG_LSB_FIRST_LSB_OFS, value); };

   // 0x01000000: ADC_CFG_SDO_ACTIVE_LSB - Activate SDO (to be mirrored to bit31)
   unsigned int GetAdcCfgSdoActiveLsb() { return BitExtractControl(WD2_ADC_CFG_SDO_ACTIVE_LSB_REG, WD2_ADC_CFG_SDO_ACTIVE_LSB_MASK, WD2_ADC_CFG_SDO_ACTIVE_LSB_OFS); };
   void         SetAdcCfgSdoActiveLsb(unsigned int value) { SetRegMask(WD2_ADC_CFG_SDO_ACTIVE_LSB_REG, WD2_ADC_CFG_SDO_ACTIVE_LSB_MASK, WD2_ADC_CFG_SDO_ACTIVE_LSB_OFS, value); };

   // 0x00080000: ADC_DI2_D_CHN_H - Data Channel H Activiation for Writes
   unsigned int GetAdcDi2DChnH() { return BitExtractControl(WD2_ADC_DI2_D_CHN_H_REG, WD2_ADC_DI2_D_CHN_H_MASK, WD2_ADC_DI2_D_CHN_H_OFS); };
   void         SetAdcDi2DChnH(unsigned int value) { SetRegMask(WD2_ADC_DI2_D_CHN_H_REG, WD2_ADC_DI2_D_CHN_H_MASK, WD2_ADC_DI2_D_CHN_H_OFS, value); };

   // 0x00040000: ADC_DI2_D_CHN_G - Data Channel G Activiation for Writes
   unsigned int GetAdcDi2DChnG() { return BitExtractControl(WD2_ADC_DI2_D_CHN_G_REG, WD2_ADC_DI2_D_CHN_G_MASK, WD2_ADC_DI2_D_CHN_G_OFS); };
   void         SetAdcDi2DChnG(unsigned int value) { SetRegMask(WD2_ADC_DI2_D_CHN_G_REG, WD2_ADC_DI2_D_CHN_G_MASK, WD2_ADC_DI2_D_CHN_G_OFS, value); };

   // 0x00020000: ADC_DI2_D_CHN_F - Data Channel F Activiation for Writes
   unsigned int GetAdcDi2DChnF() { return BitExtractControl(WD2_ADC_DI2_D_CHN_F_REG, WD2_ADC_DI2_D_CHN_F_MASK, WD2_ADC_DI2_D_CHN_F_OFS); };
   void         SetAdcDi2DChnF(unsigned int value) { SetRegMask(WD2_ADC_DI2_D_CHN_F_REG, WD2_ADC_DI2_D_CHN_F_MASK, WD2_ADC_DI2_D_CHN_F_OFS, value); };

   // 0x00010000: ADC_DI2_D_CHN_E - Data Channel E Activiation for Writes
   unsigned int GetAdcDi2DChnE() { return BitExtractControl(WD2_ADC_DI2_D_CHN_E_REG, WD2_ADC_DI2_D_CHN_E_MASK, WD2_ADC_DI2_D_CHN_E_OFS); };
   void         SetAdcDi2DChnE(unsigned int value) { SetRegMask(WD2_ADC_DI2_D_CHN_E_REG, WD2_ADC_DI2_D_CHN_E_MASK, WD2_ADC_DI2_D_CHN_E_OFS, value); };

   // 0x00002000: ADC_DI1_C_CHN_DCO - Clock Channel DCO Activiation for Writes
   unsigned int GetAdcDi1CChnDco() { return BitExtractControl(WD2_ADC_DI1_C_CHN_DCO_REG, WD2_ADC_DI1_C_CHN_DCO_MASK, WD2_ADC_DI1_C_CHN_DCO_OFS); };
   void         SetAdcDi1CChnDco(unsigned int value) { SetRegMask(WD2_ADC_DI1_C_CHN_DCO_REG, WD2_ADC_DI1_C_CHN_DCO_MASK, WD2_ADC_DI1_C_CHN_DCO_OFS, value); };

   // 0x00001000: ADC_DI1_C_CHN_FCO - Clock Channel FCO Activiation for Writes
   unsigned int GetAdcDi1CChnFco() { return BitExtractControl(WD2_ADC_DI1_C_CHN_FCO_REG, WD2_ADC_DI1_C_CHN_FCO_MASK, WD2_ADC_DI1_C_CHN_FCO_OFS); };
   void         SetAdcDi1CChnFco(unsigned int value) { SetRegMask(WD2_ADC_DI1_C_CHN_FCO_REG, WD2_ADC_DI1_C_CHN_FCO_MASK, WD2_ADC_DI1_C_CHN_FCO_OFS, value); };

   // 0x00000800: ADC_DI1_D_CHN_D - Data Channel D Activiation for Writes
   unsigned int GetAdcDi1DChnD() { return BitExtractControl(WD2_ADC_DI1_D_CHN_D_REG, WD2_ADC_DI1_D_CHN_D_MASK, WD2_ADC_DI1_D_CHN_D_OFS); };
   void         SetAdcDi1DChnD(unsigned int value) { SetRegMask(WD2_ADC_DI1_D_CHN_D_REG, WD2_ADC_DI1_D_CHN_D_MASK, WD2_ADC_DI1_D_CHN_D_OFS, value); };

   // 0x00000400: ADC_DI1_D_CHN_C - Data Channel C Activiation for Writes
   unsigned int GetAdcDi1DChnC() { return BitExtractControl(WD2_ADC_DI1_D_CHN_C_REG, WD2_ADC_DI1_D_CHN_C_MASK, WD2_ADC_DI1_D_CHN_C_OFS); };
   void         SetAdcDi1DChnC(unsigned int value) { SetRegMask(WD2_ADC_DI1_D_CHN_C_REG, WD2_ADC_DI1_D_CHN_C_MASK, WD2_ADC_DI1_D_CHN_C_OFS, value); };

   // 0x00000200: ADC_DI1_D_CHN_B - Data Channel B Activiation for Writes
   unsigned int GetAdcDi1DChnB() { return BitExtractControl(WD2_ADC_DI1_D_CHN_B_REG, WD2_ADC_DI1_D_CHN_B_MASK, WD2_ADC_DI1_D_CHN_B_OFS); };
   void         SetAdcDi1DChnB(unsigned int value) { SetRegMask(WD2_ADC_DI1_D_CHN_B_REG, WD2_ADC_DI1_D_CHN_B_MASK, WD2_ADC_DI1_D_CHN_B_OFS, value); };

   // 0x00000100: ADC_DI1_D_CHN_A - Data Channel A Activiation for Writes
   unsigned int GetAdcDi1DChnA() { return BitExtractControl(WD2_ADC_DI1_D_CHN_A_REG, WD2_ADC_DI1_D_CHN_A_MASK, WD2_ADC_DI1_D_CHN_A_OFS); };
   void         SetAdcDi1DChnA(unsigned int value) { SetRegMask(WD2_ADC_DI1_D_CHN_A_REG, WD2_ADC_DI1_D_CHN_A_MASK, WD2_ADC_DI1_D_CHN_A_OFS, value); };

   // 0x00000001: ADC_TX_INIT_OVERRIDE - Set Resolution/Sample Rate Override
   unsigned int GetAdcTxInitOverride() { return BitExtractControl(WD2_ADC_TX_INIT_OVERRIDE_REG, WD2_ADC_TX_INIT_OVERRIDE_MASK, WD2_ADC_TX_INIT_OVERRIDE_OFS); };
   void         SetAdcTxInitOverride(unsigned int value) { SetRegMask(WD2_ADC_TX_INIT_OVERRIDE_REG, WD2_ADC_TX_INIT_OVERRIDE_MASK, WD2_ADC_TX_INIT_OVERRIDE_OFS, value); };



   ////// ------ Control Register 70 [0x1118]: ADC_PM_CLK_ENH - ADC Power Modes, Clock, Enhancement (Default: 0x00010000) ------ //////

   // 0x20000000: ADC_PM_EXT_PD - Extrenal Power Down Pin Function (0 = full, 1 = standby)
   unsigned int GetAdcPmExtPd() { return BitExtractControl(WD2_ADC_PM_EXT_PD_REG, WD2_ADC_PM_EXT_PD_MASK, WD2_ADC_PM_EXT_PD_OFS); };
   void         SetAdcPmExtPd(unsigned int value) { SetRegMask(WD2_ADC_PM_EXT_PD_REG, WD2_ADC_PM_EXT_PD_MASK, WD2_ADC_PM_EXT_PD_OFS, value); };

   // 0x03000000: ADC_PM_INT_PD_MODE - Internal Power Down Mode (see datasheet)
   unsigned int GetAdcPmIntPdMode() { return BitExtractControl(WD2_ADC_PM_INT_PD_MODE_REG, WD2_ADC_PM_INT_PD_MODE_MASK, WD2_ADC_PM_INT_PD_MODE_OFS); };
   void         SetAdcPmIntPdMode(unsigned int value) { SetRegMask(WD2_ADC_PM_INT_PD_MODE_REG, WD2_ADC_PM_INT_PD_MODE_MASK, WD2_ADC_PM_INT_PD_MODE_OFS, value); };

   // 0x00010000: ADC_CLK_DUTY_CYC_STAB - Duty Cycle Stabilizer (0 = off, 1 = on)
   unsigned int GetAdcClkDutyCycStab() { return BitExtractControl(WD2_ADC_CLK_DUTY_CYC_STAB_REG, WD2_ADC_CLK_DUTY_CYC_STAB_MASK, WD2_ADC_CLK_DUTY_CYC_STAB_OFS); };
   void         SetAdcClkDutyCycStab(unsigned int value) { SetRegMask(WD2_ADC_CLK_DUTY_CYC_STAB_REG, WD2_ADC_CLK_DUTY_CYC_STAB_MASK, WD2_ADC_CLK_DUTY_CYC_STAB_OFS, value); };

   // 0x00000700: ADC_CLK_DIV_RATIO - Clock Divide Ratio (value+1)
   unsigned int GetAdcClkDivRatio() { return BitExtractControl(WD2_ADC_CLK_DIV_RATIO_REG, WD2_ADC_CLK_DIV_RATIO_MASK, WD2_ADC_CLK_DIV_RATIO_OFS); };
   void         SetAdcClkDivRatio(unsigned int value) { SetRegMask(WD2_ADC_CLK_DIV_RATIO_REG, WD2_ADC_CLK_DIV_RATIO_MASK, WD2_ADC_CLK_DIV_RATIO_OFS, value); };

   // 0x00000010: ADC_ENH_CHOP_MODE - Chop Mode (0 = off, 1 = on)
   unsigned int GetAdcEnhChopMode() { return BitExtractControl(WD2_ADC_ENH_CHOP_MODE_REG, WD2_ADC_ENH_CHOP_MODE_MASK, WD2_ADC_ENH_CHOP_MODE_OFS); };
   void         SetAdcEnhChopMode(unsigned int value) { SetRegMask(WD2_ADC_ENH_CHOP_MODE_REG, WD2_ADC_ENH_CHOP_MODE_MASK, WD2_ADC_ENH_CHOP_MODE_OFS, value); };



   ////// ------ Control Register 71 [0x111C]: ADC_TEST_OFFS_OM - ADC Test Mode, Offset Adjust and Output Mode (Default: 0x00000044) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE - User Input Test Mode (see datasheet) (Local)
   unsigned int GetAdcTmUsrInMode() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_REG, WD2_ADC_TM_USR_IN_MODE_MASK, WD2_ADC_TM_USR_IN_MODE_OFS); };
   void         SetAdcTmUsrInMode(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_REG, WD2_ADC_TM_USR_IN_MODE_MASK, WD2_ADC_TM_USR_IN_MODE_OFS, value); };

   // 0x00200000: ADC_TM_RST_PN_LONG_GEN - Reset Pseudo Random Long Generator (Global)
   unsigned int GetAdcTmRstPnLongGen() { return BitExtractControl(WD2_ADC_TM_RST_PN_LONG_GEN_REG, WD2_ADC_TM_RST_PN_LONG_GEN_MASK, WD2_ADC_TM_RST_PN_LONG_GEN_OFS); };
   void         SetAdcTmRstPnLongGen(unsigned int value) { SetRegMask(WD2_ADC_TM_RST_PN_LONG_GEN_REG, WD2_ADC_TM_RST_PN_LONG_GEN_MASK, WD2_ADC_TM_RST_PN_LONG_GEN_OFS, value); };

   // 0x00100000: ADC_TM_RST_PN_SHORT_GEN - Reset Pseudo Random Short Generator (Global)
   unsigned int GetAdcTmRstPnShortGen() { return BitExtractControl(WD2_ADC_TM_RST_PN_SHORT_GEN_REG, WD2_ADC_TM_RST_PN_SHORT_GEN_MASK, WD2_ADC_TM_RST_PN_SHORT_GEN_OFS); };
   void         SetAdcTmRstPnShortGen(unsigned int value) { SetRegMask(WD2_ADC_TM_RST_PN_SHORT_GEN_REG, WD2_ADC_TM_RST_PN_SHORT_GEN_MASK, WD2_ADC_TM_RST_PN_SHORT_GEN_OFS, value); };

   // 0x000F0000: ADC_TM_OUT - Output Test Mode (see datasheet) (Local)
   unsigned int GetAdcTmOut() { return BitExtractControl(WD2_ADC_TM_OUT_REG, WD2_ADC_TM_OUT_MASK, WD2_ADC_TM_OUT_OFS); };
   void         SetAdcTmOut(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_REG, WD2_ADC_TM_OUT_MASK, WD2_ADC_TM_OUT_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ - Device Offset Trim (Local)
   unsigned int GetAdcOffsAdj() { return BitExtractControl(WD2_ADC_OFFS_ADJ_REG, WD2_ADC_OFFS_ADJ_MASK, WD2_ADC_OFFS_ADJ_OFS); };
   void         SetAdcOffsAdj(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_REG, WD2_ADC_OFFS_ADJ_MASK, WD2_ADC_OFFS_ADJ_OFS, value); };

   // 0x00000040: ADC_OM_LVDS_MODE - LVDS ANSI/IEEE Option (0 = ANSI, 1 = IEEE) (Global)
   unsigned int GetAdcOmLvdsMode() { return BitExtractControl(WD2_ADC_OM_LVDS_MODE_REG, WD2_ADC_OM_LVDS_MODE_MASK, WD2_ADC_OM_LVDS_MODE_OFS); };
   void         SetAdcOmLvdsMode(unsigned int value) { SetRegMask(WD2_ADC_OM_LVDS_MODE_REG, WD2_ADC_OM_LVDS_MODE_MASK, WD2_ADC_OM_LVDS_MODE_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT - Output Invert (Local)
   unsigned int GetAdcOmOutInvert() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_REG, WD2_ADC_OM_OUT_INVERT_MASK, WD2_ADC_OM_OUT_INVERT_OFS); };
   void         SetAdcOmOutInvert(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_REG, WD2_ADC_OM_OUT_INVERT_MASK, WD2_ADC_OM_OUT_INVERT_OFS, value); };

   // 0x00000001: ADC_OM_OUT_FORMAT - Output Format (0 = offset binary, 1 = twos complement) (Global)
   unsigned int GetAdcOmOutFormat() { return BitExtractControl(WD2_ADC_OM_OUT_FORMAT_REG, WD2_ADC_OM_OUT_FORMAT_MASK, WD2_ADC_OM_OUT_FORMAT_OFS); };
   void         SetAdcOmOutFormat(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_FORMAT_REG, WD2_ADC_OM_OUT_FORMAT_MASK, WD2_ADC_OM_OUT_FORMAT_OFS, value); };



   ////// ------ Control Register 72 [0x1120]: ADC_OUT_VREF - ADC Output and Vref Settings (Default: 0x00300304) ------ //////

   // 0x00300000: ADC_OA_OUT_DRV_TERM - Output Driver Termination (see datasheet)
   unsigned int GetAdcOaOutDrvTerm() { return BitExtractControl(WD2_ADC_OA_OUT_DRV_TERM_REG, WD2_ADC_OA_OUT_DRV_TERM_MASK, WD2_ADC_OA_OUT_DRV_TERM_OFS); };
   void         SetAdcOaOutDrvTerm(unsigned int value) { SetRegMask(WD2_ADC_OA_OUT_DRV_TERM_REG, WD2_ADC_OA_OUT_DRV_TERM_MASK, WD2_ADC_OA_OUT_DRV_TERM_OFS, value); };

   // 0x00010000: ADC_OA_OUT_DRIVE - Output Drive (0 = 1x, 1 = 2x)
   unsigned int GetAdcOaOutDrive() { return BitExtractControl(WD2_ADC_OA_OUT_DRIVE_REG, WD2_ADC_OA_OUT_DRIVE_MASK, WD2_ADC_OA_OUT_DRIVE_OFS); };
   void         SetAdcOaOutDrive(unsigned int value) { SetRegMask(WD2_ADC_OA_OUT_DRIVE_REG, WD2_ADC_OA_OUT_DRIVE_MASK, WD2_ADC_OA_OUT_DRIVE_OFS, value); };

   // 0x00007000: ADC_OP_IN_CLK_PH_ADJ - Input Clock Phase Adjust (see datasheet)
   unsigned int GetAdcOpInClkPhAdj() { return BitExtractControl(WD2_ADC_OP_IN_CLK_PH_ADJ_REG, WD2_ADC_OP_IN_CLK_PH_ADJ_MASK, WD2_ADC_OP_IN_CLK_PH_ADJ_OFS); };
   void         SetAdcOpInClkPhAdj(unsigned int value) { SetRegMask(WD2_ADC_OP_IN_CLK_PH_ADJ_REG, WD2_ADC_OP_IN_CLK_PH_ADJ_MASK, WD2_ADC_OP_IN_CLK_PH_ADJ_OFS, value); };

   // 0x00000F00: ADC_OP_OUT_CLK_PH_ADJ - Output Clock Phase Adjust (see datasheet)
   unsigned int GetAdcOpOutClkPhAdj() { return BitExtractControl(WD2_ADC_OP_OUT_CLK_PH_ADJ_REG, WD2_ADC_OP_OUT_CLK_PH_ADJ_MASK, WD2_ADC_OP_OUT_CLK_PH_ADJ_OFS); };
   void         SetAdcOpOutClkPhAdj(unsigned int value) { SetRegMask(WD2_ADC_OP_OUT_CLK_PH_ADJ_REG, WD2_ADC_OP_OUT_CLK_PH_ADJ_MASK, WD2_ADC_OP_OUT_CLK_PH_ADJ_OFS, value); };

   // 0x00000007: ADC_INT_VREF_ADJ - Internal Vref Adjustment Digital Scheme (see datasheet)
   unsigned int GetAdcIntVrefAdj() { return BitExtractControl(WD2_ADC_INT_VREF_ADJ_REG, WD2_ADC_INT_VREF_ADJ_MASK, WD2_ADC_INT_VREF_ADJ_OFS); };
   void         SetAdcIntVrefAdj(unsigned int value) { SetRegMask(WD2_ADC_INT_VREF_ADJ_REG, WD2_ADC_INT_VREF_ADJ_MASK, WD2_ADC_INT_VREF_ADJ_OFS, value); };



   ////// ------ Control Register 73 [0x1124]: ADC_USR_PATT - ADC User Patterns (Default: 0xFC00FC00) ------ //////

   // 0xFFFF0000: ADC_USR_PATT1 - ADC User Pattern 1 (0x1A, 0x19) (Global)
   unsigned int GetAdcUsrPatt1() { return BitExtractControl(WD2_ADC_USR_PATT1_REG, WD2_ADC_USR_PATT1_MASK, WD2_ADC_USR_PATT1_OFS); };
   void         SetAdcUsrPatt1(unsigned int value) { SetRegMask(WD2_ADC_USR_PATT1_REG, WD2_ADC_USR_PATT1_MASK, WD2_ADC_USR_PATT1_OFS, value); };

   // 0x0000FFFF: ADC_USR_PATT2 - ADC User Pattern 2 (0x1C, 0x1B) (Global)
   unsigned int GetAdcUsrPatt2() { return BitExtractControl(WD2_ADC_USR_PATT2_REG, WD2_ADC_USR_PATT2_MASK, WD2_ADC_USR_PATT2_OFS); };
   void         SetAdcUsrPatt2(unsigned int value) { SetRegMask(WD2_ADC_USR_PATT2_REG, WD2_ADC_USR_PATT2_MASK, WD2_ADC_USR_PATT2_OFS, value); };



   ////// ------ Control Register 74 [0x1128]: ADC_SER_RES_SR - ADC Serial Control and Resolution/Sample Rate Override (Default: 0x00420000) ------ //////

   // 0x00800000: ADC_SC_LVDS_OUT_LSB_FIRST - LVDS Output LSB First
   unsigned int GetAdcScLvdsOutLsbFirst() { return BitExtractControl(WD2_ADC_SC_LVDS_OUT_LSB_FIRST_REG, WD2_ADC_SC_LVDS_OUT_LSB_FIRST_MASK, WD2_ADC_SC_LVDS_OUT_LSB_FIRST_OFS); };
   void         SetAdcScLvdsOutLsbFirst(unsigned int value) { SetRegMask(WD2_ADC_SC_LVDS_OUT_LSB_FIRST_REG, WD2_ADC_SC_LVDS_OUT_LSB_FIRST_MASK, WD2_ADC_SC_LVDS_OUT_LSB_FIRST_OFS, value); };

   // 0x00700000: ADC_SC_WORD_WISE_DDR - Word-Wise DDR 1-Lane (see datasheet)
   unsigned int GetAdcScWordWiseDdr() { return BitExtractControl(WD2_ADC_SC_WORD_WISE_DDR_REG, WD2_ADC_SC_WORD_WISE_DDR_MASK, WD2_ADC_SC_WORD_WISE_DDR_OFS); };
   void         SetAdcScWordWiseDdr(unsigned int value) { SetRegMask(WD2_ADC_SC_WORD_WISE_DDR_REG, WD2_ADC_SC_WORD_WISE_DDR_MASK, WD2_ADC_SC_WORD_WISE_DDR_OFS, value); };

   // 0x00030000: ADC_SC_OUT_NR_BITS - Serial Output Number of Bits (10 = 12bits, 11 = 10bits)
   unsigned int GetAdcScOutNrBits() { return BitExtractControl(WD2_ADC_SC_OUT_NR_BITS_REG, WD2_ADC_SC_OUT_NR_BITS_MASK, WD2_ADC_SC_OUT_NR_BITS_OFS); };
   void         SetAdcScOutNrBits(unsigned int value) { SetRegMask(WD2_ADC_SC_OUT_NR_BITS_REG, WD2_ADC_SC_OUT_NR_BITS_MASK, WD2_ADC_SC_OUT_NR_BITS_OFS, value); };

   // 0x00000200: ADC_SC_OUT_RST - Serial Channel Status Output Reset
   unsigned int GetAdcScOutRst() { return BitExtractControl(WD2_ADC_SC_OUT_RST_REG, WD2_ADC_SC_OUT_RST_MASK, WD2_ADC_SC_OUT_RST_OFS); };
   void         SetAdcScOutRst(unsigned int value) { SetRegMask(WD2_ADC_SC_OUT_RST_REG, WD2_ADC_SC_OUT_RST_MASK, WD2_ADC_SC_OUT_RST_OFS, value); };

   // 0x00000100: ADC_SC_PWR_DN - Serial Channel Status Power Down
   unsigned int GetAdcScPwrDn() { return BitExtractControl(WD2_ADC_SC_PWR_DN_REG, WD2_ADC_SC_PWR_DN_MASK, WD2_ADC_SC_PWR_DN_OFS); };
   void         SetAdcScPwrDn(unsigned int value) { SetRegMask(WD2_ADC_SC_PWR_DN_REG, WD2_ADC_SC_PWR_DN_MASK, WD2_ADC_SC_PWR_DN_OFS, value); };

   // 0x00000040: ADC_RES_SR_OVR - Resolution/Sample Rate Override Enable
   unsigned int GetAdcResSrOvr() { return BitExtractControl(WD2_ADC_RES_SR_OVR_REG, WD2_ADC_RES_SR_OVR_MASK, WD2_ADC_RES_SR_OVR_OFS); };
   void         SetAdcResSrOvr(unsigned int value) { SetRegMask(WD2_ADC_RES_SR_OVR_REG, WD2_ADC_RES_SR_OVR_MASK, WD2_ADC_RES_SR_OVR_OFS, value); };

   // 0x00000030: ADC_RESOLUTION - Resolution (10 = 12bits, 11 = 10bits)
   unsigned int GetAdcResolution() { return BitExtractControl(WD2_ADC_RESOLUTION_REG, WD2_ADC_RESOLUTION_MASK, WD2_ADC_RESOLUTION_OFS); };
   void         SetAdcResolution(unsigned int value) { SetRegMask(WD2_ADC_RESOLUTION_REG, WD2_ADC_RESOLUTION_MASK, WD2_ADC_RESOLUTION_OFS, value); };

   // 0x00000007: ADC_SAMPLE_RATE - Sample Rate (see datasheet)
   unsigned int GetAdcSampleRate() { return BitExtractControl(WD2_ADC_SAMPLE_RATE_REG, WD2_ADC_SAMPLE_RATE_MASK, WD2_ADC_SAMPLE_RATE_OFS); };
   void         SetAdcSampleRate(unsigned int value) { SetRegMask(WD2_ADC_SAMPLE_RATE_REG, WD2_ADC_SAMPLE_RATE_MASK, WD2_ADC_SAMPLE_RATE_OFS, value); };



   ////// ------ Control Register 75 [0x112C]: ADC_USR_IO_SYNC - ADC User I/O Control and Sync (Default: 0x00000000) ------ //////

   // 0x00010000: ADC_UIOC2_SDIO_PD - SDIO Pull-Down Disable
   unsigned int GetAdcUioc2SdioPd() { return BitExtractControl(WD2_ADC_UIOC2_SDIO_PD_REG, WD2_ADC_UIOC2_SDIO_PD_MASK, WD2_ADC_UIOC2_SDIO_PD_OFS); };
   void         SetAdcUioc2SdioPd(unsigned int value) { SetRegMask(WD2_ADC_UIOC2_SDIO_PD_REG, WD2_ADC_UIOC2_SDIO_PD_MASK, WD2_ADC_UIOC2_SDIO_PD_OFS, value); };

   // 0x00000800: ADC_UIOC3_VCM_PWR_DN - VCM Power Control
   unsigned int GetAdcUioc3VcmPwrDn() { return BitExtractControl(WD2_ADC_UIOC3_VCM_PWR_DN_REG, WD2_ADC_UIOC3_VCM_PWR_DN_MASK, WD2_ADC_UIOC3_VCM_PWR_DN_OFS); };
   void         SetAdcUioc3VcmPwrDn(unsigned int value) { SetRegMask(WD2_ADC_UIOC3_VCM_PWR_DN_REG, WD2_ADC_UIOC3_VCM_PWR_DN_MASK, WD2_ADC_UIOC3_VCM_PWR_DN_OFS, value); };

   // 0x00000002: ADC_SYNC_NEXT_ONLY - Sync Next Only
   unsigned int GetAdcSyncNextOnly() { return BitExtractControl(WD2_ADC_SYNC_NEXT_ONLY_REG, WD2_ADC_SYNC_NEXT_ONLY_MASK, WD2_ADC_SYNC_NEXT_ONLY_OFS); };
   void         SetAdcSyncNextOnly(unsigned int value) { SetRegMask(WD2_ADC_SYNC_NEXT_ONLY_REG, WD2_ADC_SYNC_NEXT_ONLY_MASK, WD2_ADC_SYNC_NEXT_ONLY_OFS, value); };

   // 0x00000001: ADC_EN_SYNC - Enable Sync
   unsigned int GetAdcEnSync() { return BitExtractControl(WD2_ADC_EN_SYNC_REG, WD2_ADC_EN_SYNC_MASK, WD2_ADC_EN_SYNC_OFS); };
   void         SetAdcEnSync(unsigned int value) { SetRegMask(WD2_ADC_EN_SYNC_REG, WD2_ADC_EN_SYNC_MASK, WD2_ADC_EN_SYNC_OFS, value); };



   ////// ------ Control Register 76 [0x1130]: ADC_0_CH_A_CFG - ADC 0 (A) Channel A Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE_0_A - User Input Test Mode (see datasheet)
   unsigned int GetAdcTmUsrInMode0A() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_0_A_REG, WD2_ADC_TM_USR_IN_MODE_0_A_MASK, WD2_ADC_TM_USR_IN_MODE_0_A_OFS); };
   void         SetAdcTmUsrInMode0A(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_0_A_REG, WD2_ADC_TM_USR_IN_MODE_0_A_MASK, WD2_ADC_TM_USR_IN_MODE_0_A_OFS, value); };

   // 0x000F0000: ADC_TM_OUT_0_A - Output Test Mode (see datasheet)
   unsigned int GetAdcTmOut0A() { return BitExtractControl(WD2_ADC_TM_OUT_0_A_REG, WD2_ADC_TM_OUT_0_A_MASK, WD2_ADC_TM_OUT_0_A_OFS); };
   void         SetAdcTmOut0A(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_0_A_REG, WD2_ADC_TM_OUT_0_A_MASK, WD2_ADC_TM_OUT_0_A_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ_0_A - Device Offset Trim
   unsigned int GetAdcOffsAdj0A() { return BitExtractControl(WD2_ADC_OFFS_ADJ_0_A_REG, WD2_ADC_OFFS_ADJ_0_A_MASK, WD2_ADC_OFFS_ADJ_0_A_OFS); };
   void         SetAdcOffsAdj0A(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_0_A_REG, WD2_ADC_OFFS_ADJ_0_A_MASK, WD2_ADC_OFFS_ADJ_0_A_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT_0_A - Output Invert
   unsigned int GetAdcOmOutInvert0A() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_0_A_REG, WD2_ADC_OM_OUT_INVERT_0_A_MASK, WD2_ADC_OM_OUT_INVERT_0_A_OFS); };
   void         SetAdcOmOutInvert0A(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_0_A_REG, WD2_ADC_OM_OUT_INVERT_0_A_MASK, WD2_ADC_OM_OUT_INVERT_0_A_OFS, value); };



   ////// ------ Control Register 77 [0x1134]: ADC_0_CH_B_CFG - ADC 0 (A) Channel B Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE_0_B - User Input Test Mode (see datasheet)
   unsigned int GetAdcTmUsrInMode0B() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_0_B_REG, WD2_ADC_TM_USR_IN_MODE_0_B_MASK, WD2_ADC_TM_USR_IN_MODE_0_B_OFS); };
   void         SetAdcTmUsrInMode0B(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_0_B_REG, WD2_ADC_TM_USR_IN_MODE_0_B_MASK, WD2_ADC_TM_USR_IN_MODE_0_B_OFS, value); };

   // 0x000F0000: ADC_TM_OUT_0_B - Output Test Mode (see datasheet)
   unsigned int GetAdcTmOut0B() { return BitExtractControl(WD2_ADC_TM_OUT_0_B_REG, WD2_ADC_TM_OUT_0_B_MASK, WD2_ADC_TM_OUT_0_B_OFS); };
   void         SetAdcTmOut0B(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_0_B_REG, WD2_ADC_TM_OUT_0_B_MASK, WD2_ADC_TM_OUT_0_B_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ_0_B - Device Offset Trim
   unsigned int GetAdcOffsAdj0B() { return BitExtractControl(WD2_ADC_OFFS_ADJ_0_B_REG, WD2_ADC_OFFS_ADJ_0_B_MASK, WD2_ADC_OFFS_ADJ_0_B_OFS); };
   void         SetAdcOffsAdj0B(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_0_B_REG, WD2_ADC_OFFS_ADJ_0_B_MASK, WD2_ADC_OFFS_ADJ_0_B_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT_0_B - Output Invert
   unsigned int GetAdcOmOutInvert0B() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_0_B_REG, WD2_ADC_OM_OUT_INVERT_0_B_MASK, WD2_ADC_OM_OUT_INVERT_0_B_OFS); };
   void         SetAdcOmOutInvert0B(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_0_B_REG, WD2_ADC_OM_OUT_INVERT_0_B_MASK, WD2_ADC_OM_OUT_INVERT_0_B_OFS, value); };



   ////// ------ Control Register 78 [0x1138]: ADC_0_CH_C_CFG - ADC 0 (A) Channel C Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE_0_C - User Input Test Mode (see datasheet)
   unsigned int GetAdcTmUsrInMode0C() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_0_C_REG, WD2_ADC_TM_USR_IN_MODE_0_C_MASK, WD2_ADC_TM_USR_IN_MODE_0_C_OFS); };
   void         SetAdcTmUsrInMode0C(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_0_C_REG, WD2_ADC_TM_USR_IN_MODE_0_C_MASK, WD2_ADC_TM_USR_IN_MODE_0_C_OFS, value); };

   // 0x000F0000: ADC_TM_OUT_0_C - Output Test Mode (see datasheet)
   unsigned int GetAdcTmOut0C() { return BitExtractControl(WD2_ADC_TM_OUT_0_C_REG, WD2_ADC_TM_OUT_0_C_MASK, WD2_ADC_TM_OUT_0_C_OFS); };
   void         SetAdcTmOut0C(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_0_C_REG, WD2_ADC_TM_OUT_0_C_MASK, WD2_ADC_TM_OUT_0_C_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ_0_C - Device Offset Trim
   unsigned int GetAdcOffsAdj0C() { return BitExtractControl(WD2_ADC_OFFS_ADJ_0_C_REG, WD2_ADC_OFFS_ADJ_0_C_MASK, WD2_ADC_OFFS_ADJ_0_C_OFS); };
   void         SetAdcOffsAdj0C(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_0_C_REG, WD2_ADC_OFFS_ADJ_0_C_MASK, WD2_ADC_OFFS_ADJ_0_C_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT_0_C - Output Invert
   unsigned int GetAdcOmOutInvert0C() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_0_C_REG, WD2_ADC_OM_OUT_INVERT_0_C_MASK, WD2_ADC_OM_OUT_INVERT_0_C_OFS); };
   void         SetAdcOmOutInvert0C(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_0_C_REG, WD2_ADC_OM_OUT_INVERT_0_C_MASK, WD2_ADC_OM_OUT_INVERT_0_C_OFS, value); };



   ////// ------ Control Register 79 [0x113C]: ADC_0_CH_D_CFG - ADC 0 (A) Channel D Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE_0_D - User Input Test Mode (see datasheet)
   unsigned int GetAdcTmUsrInMode0D() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_0_D_REG, WD2_ADC_TM_USR_IN_MODE_0_D_MASK, WD2_ADC_TM_USR_IN_MODE_0_D_OFS); };
   void         SetAdcTmUsrInMode0D(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_0_D_REG, WD2_ADC_TM_USR_IN_MODE_0_D_MASK, WD2_ADC_TM_USR_IN_MODE_0_D_OFS, value); };

   // 0x000F0000: ADC_TM_OUT_0_D - Output Test Mode (see datasheet)
   unsigned int GetAdcTmOut0D() { return BitExtractControl(WD2_ADC_TM_OUT_0_D_REG, WD2_ADC_TM_OUT_0_D_MASK, WD2_ADC_TM_OUT_0_D_OFS); };
   void         SetAdcTmOut0D(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_0_D_REG, WD2_ADC_TM_OUT_0_D_MASK, WD2_ADC_TM_OUT_0_D_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ_0_D - Device Offset Trim
   unsigned int GetAdcOffsAdj0D() { return BitExtractControl(WD2_ADC_OFFS_ADJ_0_D_REG, WD2_ADC_OFFS_ADJ_0_D_MASK, WD2_ADC_OFFS_ADJ_0_D_OFS); };
   void         SetAdcOffsAdj0D(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_0_D_REG, WD2_ADC_OFFS_ADJ_0_D_MASK, WD2_ADC_OFFS_ADJ_0_D_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT_0_D - Output Invert
   unsigned int GetAdcOmOutInvert0D() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_0_D_REG, WD2_ADC_OM_OUT_INVERT_0_D_MASK, WD2_ADC_OM_OUT_INVERT_0_D_OFS); };
   void         SetAdcOmOutInvert0D(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_0_D_REG, WD2_ADC_OM_OUT_INVERT_0_D_MASK, WD2_ADC_OM_OUT_INVERT_0_D_OFS, value); };



   ////// ------ Control Register 80 [0x1140]: ADC_0_CH_E_CFG - ADC 0 (A) Channel E Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE_0_E - User Input Test Mode (see datasheet)
   unsigned int GetAdcTmUsrInMode0E() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_0_E_REG, WD2_ADC_TM_USR_IN_MODE_0_E_MASK, WD2_ADC_TM_USR_IN_MODE_0_E_OFS); };
   void         SetAdcTmUsrInMode0E(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_0_E_REG, WD2_ADC_TM_USR_IN_MODE_0_E_MASK, WD2_ADC_TM_USR_IN_MODE_0_E_OFS, value); };

   // 0x000F0000: ADC_TM_OUT_0_E - Output Test Mode (see datasheet)
   unsigned int GetAdcTmOut0E() { return BitExtractControl(WD2_ADC_TM_OUT_0_E_REG, WD2_ADC_TM_OUT_0_E_MASK, WD2_ADC_TM_OUT_0_E_OFS); };
   void         SetAdcTmOut0E(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_0_E_REG, WD2_ADC_TM_OUT_0_E_MASK, WD2_ADC_TM_OUT_0_E_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ_0_E - Device Offset Trim
   unsigned int GetAdcOffsAdj0E() { return BitExtractControl(WD2_ADC_OFFS_ADJ_0_E_REG, WD2_ADC_OFFS_ADJ_0_E_MASK, WD2_ADC_OFFS_ADJ_0_E_OFS); };
   void         SetAdcOffsAdj0E(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_0_E_REG, WD2_ADC_OFFS_ADJ_0_E_MASK, WD2_ADC_OFFS_ADJ_0_E_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT_0_E - Output Invert
   unsigned int GetAdcOmOutInvert0E() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_0_E_REG, WD2_ADC_OM_OUT_INVERT_0_E_MASK, WD2_ADC_OM_OUT_INVERT_0_E_OFS); };
   void         SetAdcOmOutInvert0E(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_0_E_REG, WD2_ADC_OM_OUT_INVERT_0_E_MASK, WD2_ADC_OM_OUT_INVERT_0_E_OFS, value); };



   ////// ------ Control Register 81 [0x1144]: ADC_0_CH_F_CFG - ADC 0 (A) Channel F Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE_0_F - User Input Test Mode (see datasheet)
   unsigned int GetAdcTmUsrInMode0F() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_0_F_REG, WD2_ADC_TM_USR_IN_MODE_0_F_MASK, WD2_ADC_TM_USR_IN_MODE_0_F_OFS); };
   void         SetAdcTmUsrInMode0F(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_0_F_REG, WD2_ADC_TM_USR_IN_MODE_0_F_MASK, WD2_ADC_TM_USR_IN_MODE_0_F_OFS, value); };

   // 0x000F0000: ADC_TM_OUT_0_F - Output Test Mode (see datasheet)
   unsigned int GetAdcTmOut0F() { return BitExtractControl(WD2_ADC_TM_OUT_0_F_REG, WD2_ADC_TM_OUT_0_F_MASK, WD2_ADC_TM_OUT_0_F_OFS); };
   void         SetAdcTmOut0F(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_0_F_REG, WD2_ADC_TM_OUT_0_F_MASK, WD2_ADC_TM_OUT_0_F_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ_0_F - Device Offset Trim
   unsigned int GetAdcOffsAdj0F() { return BitExtractControl(WD2_ADC_OFFS_ADJ_0_F_REG, WD2_ADC_OFFS_ADJ_0_F_MASK, WD2_ADC_OFFS_ADJ_0_F_OFS); };
   void         SetAdcOffsAdj0F(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_0_F_REG, WD2_ADC_OFFS_ADJ_0_F_MASK, WD2_ADC_OFFS_ADJ_0_F_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT_0_F - Output Invert
   unsigned int GetAdcOmOutInvert0F() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_0_F_REG, WD2_ADC_OM_OUT_INVERT_0_F_MASK, WD2_ADC_OM_OUT_INVERT_0_F_OFS); };
   void         SetAdcOmOutInvert0F(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_0_F_REG, WD2_ADC_OM_OUT_INVERT_0_F_MASK, WD2_ADC_OM_OUT_INVERT_0_F_OFS, value); };



   ////// ------ Control Register 82 [0x1148]: ADC_0_CH_G_CFG - ADC 0 (A) Channel G Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE_0_G - User Input Test Mode (see datasheet)
   unsigned int GetAdcTmUsrInMode0G() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_0_G_REG, WD2_ADC_TM_USR_IN_MODE_0_G_MASK, WD2_ADC_TM_USR_IN_MODE_0_G_OFS); };
   void         SetAdcTmUsrInMode0G(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_0_G_REG, WD2_ADC_TM_USR_IN_MODE_0_G_MASK, WD2_ADC_TM_USR_IN_MODE_0_G_OFS, value); };

   // 0x000F0000: ADC_TM_OUT_0_G - Output Test Mode (see datasheet)
   unsigned int GetAdcTmOut0G() { return BitExtractControl(WD2_ADC_TM_OUT_0_G_REG, WD2_ADC_TM_OUT_0_G_MASK, WD2_ADC_TM_OUT_0_G_OFS); };
   void         SetAdcTmOut0G(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_0_G_REG, WD2_ADC_TM_OUT_0_G_MASK, WD2_ADC_TM_OUT_0_G_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ_0_G - Device Offset Trim
   unsigned int GetAdcOffsAdj0G() { return BitExtractControl(WD2_ADC_OFFS_ADJ_0_G_REG, WD2_ADC_OFFS_ADJ_0_G_MASK, WD2_ADC_OFFS_ADJ_0_G_OFS); };
   void         SetAdcOffsAdj0G(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_0_G_REG, WD2_ADC_OFFS_ADJ_0_G_MASK, WD2_ADC_OFFS_ADJ_0_G_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT_0_G - Output Invert
   unsigned int GetAdcOmOutInvert0G() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_0_G_REG, WD2_ADC_OM_OUT_INVERT_0_G_MASK, WD2_ADC_OM_OUT_INVERT_0_G_OFS); };
   void         SetAdcOmOutInvert0G(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_0_G_REG, WD2_ADC_OM_OUT_INVERT_0_G_MASK, WD2_ADC_OM_OUT_INVERT_0_G_OFS, value); };



   ////// ------ Control Register 83 [0x114C]: ADC_0_CH_H_CFG - ADC 0 (A) Channel H Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000000) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE_0_H - User Input Test Mode (see datasheet)
   unsigned int GetAdcTmUsrInMode0H() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_0_H_REG, WD2_ADC_TM_USR_IN_MODE_0_H_MASK, WD2_ADC_TM_USR_IN_MODE_0_H_OFS); };
   void         SetAdcTmUsrInMode0H(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_0_H_REG, WD2_ADC_TM_USR_IN_MODE_0_H_MASK, WD2_ADC_TM_USR_IN_MODE_0_H_OFS, value); };

   // 0x000F0000: ADC_TM_OUT_0_H - Output Test Mode (see datasheet)
   unsigned int GetAdcTmOut0H() { return BitExtractControl(WD2_ADC_TM_OUT_0_H_REG, WD2_ADC_TM_OUT_0_H_MASK, WD2_ADC_TM_OUT_0_H_OFS); };
   void         SetAdcTmOut0H(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_0_H_REG, WD2_ADC_TM_OUT_0_H_MASK, WD2_ADC_TM_OUT_0_H_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ_0_H - Device Offset Trim
   unsigned int GetAdcOffsAdj0H() { return BitExtractControl(WD2_ADC_OFFS_ADJ_0_H_REG, WD2_ADC_OFFS_ADJ_0_H_MASK, WD2_ADC_OFFS_ADJ_0_H_OFS); };
   void         SetAdcOffsAdj0H(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_0_H_REG, WD2_ADC_OFFS_ADJ_0_H_MASK, WD2_ADC_OFFS_ADJ_0_H_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT_0_H - Output Invert
   unsigned int GetAdcOmOutInvert0H() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_0_H_REG, WD2_ADC_OM_OUT_INVERT_0_H_MASK, WD2_ADC_OM_OUT_INVERT_0_H_OFS); };
   void         SetAdcOmOutInvert0H(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_0_H_REG, WD2_ADC_OM_OUT_INVERT_0_H_MASK, WD2_ADC_OM_OUT_INVERT_0_H_OFS, value); };



   ////// ------ Control Register 84 [0x1150]: ADC_0_CH_DCO_CFG - ADC 0 (A) Channel DCO Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000000) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE_0_DCO - User Input Test Mode (see datasheet)
   unsigned int GetAdcTmUsrInMode0Dco() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_0_DCO_REG, WD2_ADC_TM_USR_IN_MODE_0_DCO_MASK, WD2_ADC_TM_USR_IN_MODE_0_DCO_OFS); };
   void         SetAdcTmUsrInMode0Dco(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_0_DCO_REG, WD2_ADC_TM_USR_IN_MODE_0_DCO_MASK, WD2_ADC_TM_USR_IN_MODE_0_DCO_OFS, value); };

   // 0x000F0000: ADC_TM_OUT_0_DCO - Output Test Mode (see datasheet)
   unsigned int GetAdcTmOut0Dco() { return BitExtractControl(WD2_ADC_TM_OUT_0_DCO_REG, WD2_ADC_TM_OUT_0_DCO_MASK, WD2_ADC_TM_OUT_0_DCO_OFS); };
   void         SetAdcTmOut0Dco(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_0_DCO_REG, WD2_ADC_TM_OUT_0_DCO_MASK, WD2_ADC_TM_OUT_0_DCO_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ_0_DCO - Device Offset Trim
   unsigned int GetAdcOffsAdj0Dco() { return BitExtractControl(WD2_ADC_OFFS_ADJ_0_DCO_REG, WD2_ADC_OFFS_ADJ_0_DCO_MASK, WD2_ADC_OFFS_ADJ_0_DCO_OFS); };
   void         SetAdcOffsAdj0Dco(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_0_DCO_REG, WD2_ADC_OFFS_ADJ_0_DCO_MASK, WD2_ADC_OFFS_ADJ_0_DCO_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT_0_DCO - Output Invert
   unsigned int GetAdcOmOutInvert0Dco() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_0_DCO_REG, WD2_ADC_OM_OUT_INVERT_0_DCO_MASK, WD2_ADC_OM_OUT_INVERT_0_DCO_OFS); };
   void         SetAdcOmOutInvert0Dco(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_0_DCO_REG, WD2_ADC_OM_OUT_INVERT_0_DCO_MASK, WD2_ADC_OM_OUT_INVERT_0_DCO_OFS, value); };



   ////// ------ Control Register 85 [0x1154]: ADC_0_CH_FCO_CFG - ADC 0 (A) Channel FCO Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000000) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE_0_FCO - User Input Test Mode (see datasheet)
   unsigned int GetAdcTmUsrInMode0Fco() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_0_FCO_REG, WD2_ADC_TM_USR_IN_MODE_0_FCO_MASK, WD2_ADC_TM_USR_IN_MODE_0_FCO_OFS); };
   void         SetAdcTmUsrInMode0Fco(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_0_FCO_REG, WD2_ADC_TM_USR_IN_MODE_0_FCO_MASK, WD2_ADC_TM_USR_IN_MODE_0_FCO_OFS, value); };

   // 0x000F0000: ADC_TM_OUT_0_FCO - Output Test Mode (see datasheet)
   unsigned int GetAdcTmOut0Fco() { return BitExtractControl(WD2_ADC_TM_OUT_0_FCO_REG, WD2_ADC_TM_OUT_0_FCO_MASK, WD2_ADC_TM_OUT_0_FCO_OFS); };
   void         SetAdcTmOut0Fco(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_0_FCO_REG, WD2_ADC_TM_OUT_0_FCO_MASK, WD2_ADC_TM_OUT_0_FCO_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ_0_FCO - Device Offset Trim
   unsigned int GetAdcOffsAdj0Fco() { return BitExtractControl(WD2_ADC_OFFS_ADJ_0_FCO_REG, WD2_ADC_OFFS_ADJ_0_FCO_MASK, WD2_ADC_OFFS_ADJ_0_FCO_OFS); };
   void         SetAdcOffsAdj0Fco(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_0_FCO_REG, WD2_ADC_OFFS_ADJ_0_FCO_MASK, WD2_ADC_OFFS_ADJ_0_FCO_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT_0_FCO - Output Invert
   unsigned int GetAdcOmOutInvert0Fco() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_0_FCO_REG, WD2_ADC_OM_OUT_INVERT_0_FCO_MASK, WD2_ADC_OM_OUT_INVERT_0_FCO_OFS); };
   void         SetAdcOmOutInvert0Fco(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_0_FCO_REG, WD2_ADC_OM_OUT_INVERT_0_FCO_MASK, WD2_ADC_OM_OUT_INVERT_0_FCO_OFS, value); };



   ////// ------ Control Register 86 [0x1158]: ADC_1_CH_A_CFG - ADC 1 (B) Channel A Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE_1_A - User Input Test Mode (see datasheet)
   unsigned int GetAdcTmUsrInMode1A() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_1_A_REG, WD2_ADC_TM_USR_IN_MODE_1_A_MASK, WD2_ADC_TM_USR_IN_MODE_1_A_OFS); };
   void         SetAdcTmUsrInMode1A(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_1_A_REG, WD2_ADC_TM_USR_IN_MODE_1_A_MASK, WD2_ADC_TM_USR_IN_MODE_1_A_OFS, value); };

   // 0x000F0000: ADC_TM_OUT_1_A - Output Test Mode (see datasheet)
   unsigned int GetAdcTmOut1A() { return BitExtractControl(WD2_ADC_TM_OUT_1_A_REG, WD2_ADC_TM_OUT_1_A_MASK, WD2_ADC_TM_OUT_1_A_OFS); };
   void         SetAdcTmOut1A(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_1_A_REG, WD2_ADC_TM_OUT_1_A_MASK, WD2_ADC_TM_OUT_1_A_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ_1_A - Device Offset Trim
   unsigned int GetAdcOffsAdj1A() { return BitExtractControl(WD2_ADC_OFFS_ADJ_1_A_REG, WD2_ADC_OFFS_ADJ_1_A_MASK, WD2_ADC_OFFS_ADJ_1_A_OFS); };
   void         SetAdcOffsAdj1A(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_1_A_REG, WD2_ADC_OFFS_ADJ_1_A_MASK, WD2_ADC_OFFS_ADJ_1_A_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT_1_A - Output Invert
   unsigned int GetAdcOmOutInvert1A() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_1_A_REG, WD2_ADC_OM_OUT_INVERT_1_A_MASK, WD2_ADC_OM_OUT_INVERT_1_A_OFS); };
   void         SetAdcOmOutInvert1A(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_1_A_REG, WD2_ADC_OM_OUT_INVERT_1_A_MASK, WD2_ADC_OM_OUT_INVERT_1_A_OFS, value); };



   ////// ------ Control Register 87 [0x115C]: ADC_1_CH_B_CFG - ADC 1 (B) Channel B Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE_1_B - User Input Test Mode (see datasheet)
   unsigned int GetAdcTmUsrInMode1B() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_1_B_REG, WD2_ADC_TM_USR_IN_MODE_1_B_MASK, WD2_ADC_TM_USR_IN_MODE_1_B_OFS); };
   void         SetAdcTmUsrInMode1B(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_1_B_REG, WD2_ADC_TM_USR_IN_MODE_1_B_MASK, WD2_ADC_TM_USR_IN_MODE_1_B_OFS, value); };

   // 0x000F0000: ADC_TM_OUT_1_B - Output Test Mode (see datasheet)
   unsigned int GetAdcTmOut1B() { return BitExtractControl(WD2_ADC_TM_OUT_1_B_REG, WD2_ADC_TM_OUT_1_B_MASK, WD2_ADC_TM_OUT_1_B_OFS); };
   void         SetAdcTmOut1B(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_1_B_REG, WD2_ADC_TM_OUT_1_B_MASK, WD2_ADC_TM_OUT_1_B_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ_1_B - Device Offset Trim
   unsigned int GetAdcOffsAdj1B() { return BitExtractControl(WD2_ADC_OFFS_ADJ_1_B_REG, WD2_ADC_OFFS_ADJ_1_B_MASK, WD2_ADC_OFFS_ADJ_1_B_OFS); };
   void         SetAdcOffsAdj1B(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_1_B_REG, WD2_ADC_OFFS_ADJ_1_B_MASK, WD2_ADC_OFFS_ADJ_1_B_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT_1_B - Output Invert
   unsigned int GetAdcOmOutInvert1B() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_1_B_REG, WD2_ADC_OM_OUT_INVERT_1_B_MASK, WD2_ADC_OM_OUT_INVERT_1_B_OFS); };
   void         SetAdcOmOutInvert1B(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_1_B_REG, WD2_ADC_OM_OUT_INVERT_1_B_MASK, WD2_ADC_OM_OUT_INVERT_1_B_OFS, value); };



   ////// ------ Control Register 88 [0x1160]: ADC_1_CH_C_CFG - ADC 1 (B) Channel C Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE_1_C - User Input Test Mode (see datasheet)
   unsigned int GetAdcTmUsrInMode1C() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_1_C_REG, WD2_ADC_TM_USR_IN_MODE_1_C_MASK, WD2_ADC_TM_USR_IN_MODE_1_C_OFS); };
   void         SetAdcTmUsrInMode1C(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_1_C_REG, WD2_ADC_TM_USR_IN_MODE_1_C_MASK, WD2_ADC_TM_USR_IN_MODE_1_C_OFS, value); };

   // 0x000F0000: ADC_TM_OUT_1_C - Output Test Mode (see datasheet)
   unsigned int GetAdcTmOut1C() { return BitExtractControl(WD2_ADC_TM_OUT_1_C_REG, WD2_ADC_TM_OUT_1_C_MASK, WD2_ADC_TM_OUT_1_C_OFS); };
   void         SetAdcTmOut1C(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_1_C_REG, WD2_ADC_TM_OUT_1_C_MASK, WD2_ADC_TM_OUT_1_C_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ_1_C - Device Offset Trim
   unsigned int GetAdcOffsAdj1C() { return BitExtractControl(WD2_ADC_OFFS_ADJ_1_C_REG, WD2_ADC_OFFS_ADJ_1_C_MASK, WD2_ADC_OFFS_ADJ_1_C_OFS); };
   void         SetAdcOffsAdj1C(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_1_C_REG, WD2_ADC_OFFS_ADJ_1_C_MASK, WD2_ADC_OFFS_ADJ_1_C_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT_1_C - Output Invert
   unsigned int GetAdcOmOutInvert1C() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_1_C_REG, WD2_ADC_OM_OUT_INVERT_1_C_MASK, WD2_ADC_OM_OUT_INVERT_1_C_OFS); };
   void         SetAdcOmOutInvert1C(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_1_C_REG, WD2_ADC_OM_OUT_INVERT_1_C_MASK, WD2_ADC_OM_OUT_INVERT_1_C_OFS, value); };



   ////// ------ Control Register 89 [0x1164]: ADC_1_CH_D_CFG - ADC 1 (B) Channel D Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE_1_D - User Input Test Mode (see datasheet)
   unsigned int GetAdcTmUsrInMode1D() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_1_D_REG, WD2_ADC_TM_USR_IN_MODE_1_D_MASK, WD2_ADC_TM_USR_IN_MODE_1_D_OFS); };
   void         SetAdcTmUsrInMode1D(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_1_D_REG, WD2_ADC_TM_USR_IN_MODE_1_D_MASK, WD2_ADC_TM_USR_IN_MODE_1_D_OFS, value); };

   // 0x000F0000: ADC_TM_OUT_1_D - Output Test Mode (see datasheet)
   unsigned int GetAdcTmOut1D() { return BitExtractControl(WD2_ADC_TM_OUT_1_D_REG, WD2_ADC_TM_OUT_1_D_MASK, WD2_ADC_TM_OUT_1_D_OFS); };
   void         SetAdcTmOut1D(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_1_D_REG, WD2_ADC_TM_OUT_1_D_MASK, WD2_ADC_TM_OUT_1_D_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ_1_D - Device Offset Trim
   unsigned int GetAdcOffsAdj1D() { return BitExtractControl(WD2_ADC_OFFS_ADJ_1_D_REG, WD2_ADC_OFFS_ADJ_1_D_MASK, WD2_ADC_OFFS_ADJ_1_D_OFS); };
   void         SetAdcOffsAdj1D(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_1_D_REG, WD2_ADC_OFFS_ADJ_1_D_MASK, WD2_ADC_OFFS_ADJ_1_D_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT_1_D - Output Invert
   unsigned int GetAdcOmOutInvert1D() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_1_D_REG, WD2_ADC_OM_OUT_INVERT_1_D_MASK, WD2_ADC_OM_OUT_INVERT_1_D_OFS); };
   void         SetAdcOmOutInvert1D(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_1_D_REG, WD2_ADC_OM_OUT_INVERT_1_D_MASK, WD2_ADC_OM_OUT_INVERT_1_D_OFS, value); };



   ////// ------ Control Register 90 [0x1168]: ADC_1_CH_E_CFG - ADC 1 (B) Channel E Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE_1_E - User Input Test Mode (see datasheet)
   unsigned int GetAdcTmUsrInMode1E() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_1_E_REG, WD2_ADC_TM_USR_IN_MODE_1_E_MASK, WD2_ADC_TM_USR_IN_MODE_1_E_OFS); };
   void         SetAdcTmUsrInMode1E(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_1_E_REG, WD2_ADC_TM_USR_IN_MODE_1_E_MASK, WD2_ADC_TM_USR_IN_MODE_1_E_OFS, value); };

   // 0x000F0000: ADC_TM_OUT_1_E - Output Test Mode (see datasheet)
   unsigned int GetAdcTmOut1E() { return BitExtractControl(WD2_ADC_TM_OUT_1_E_REG, WD2_ADC_TM_OUT_1_E_MASK, WD2_ADC_TM_OUT_1_E_OFS); };
   void         SetAdcTmOut1E(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_1_E_REG, WD2_ADC_TM_OUT_1_E_MASK, WD2_ADC_TM_OUT_1_E_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ_1_E - Device Offset Trim
   unsigned int GetAdcOffsAdj1E() { return BitExtractControl(WD2_ADC_OFFS_ADJ_1_E_REG, WD2_ADC_OFFS_ADJ_1_E_MASK, WD2_ADC_OFFS_ADJ_1_E_OFS); };
   void         SetAdcOffsAdj1E(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_1_E_REG, WD2_ADC_OFFS_ADJ_1_E_MASK, WD2_ADC_OFFS_ADJ_1_E_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT_1_E - Output Invert
   unsigned int GetAdcOmOutInvert1E() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_1_E_REG, WD2_ADC_OM_OUT_INVERT_1_E_MASK, WD2_ADC_OM_OUT_INVERT_1_E_OFS); };
   void         SetAdcOmOutInvert1E(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_1_E_REG, WD2_ADC_OM_OUT_INVERT_1_E_MASK, WD2_ADC_OM_OUT_INVERT_1_E_OFS, value); };



   ////// ------ Control Register 91 [0x116C]: ADC_1_CH_F_CFG - ADC 1 (B) Channel F Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE_1_F - User Input Test Mode (see datasheet)
   unsigned int GetAdcTmUsrInMode1F() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_1_F_REG, WD2_ADC_TM_USR_IN_MODE_1_F_MASK, WD2_ADC_TM_USR_IN_MODE_1_F_OFS); };
   void         SetAdcTmUsrInMode1F(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_1_F_REG, WD2_ADC_TM_USR_IN_MODE_1_F_MASK, WD2_ADC_TM_USR_IN_MODE_1_F_OFS, value); };

   // 0x000F0000: ADC_TM_OUT_1_F - Output Test Mode (see datasheet)
   unsigned int GetAdcTmOut1F() { return BitExtractControl(WD2_ADC_TM_OUT_1_F_REG, WD2_ADC_TM_OUT_1_F_MASK, WD2_ADC_TM_OUT_1_F_OFS); };
   void         SetAdcTmOut1F(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_1_F_REG, WD2_ADC_TM_OUT_1_F_MASK, WD2_ADC_TM_OUT_1_F_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ_1_F - Device Offset Trim
   unsigned int GetAdcOffsAdj1F() { return BitExtractControl(WD2_ADC_OFFS_ADJ_1_F_REG, WD2_ADC_OFFS_ADJ_1_F_MASK, WD2_ADC_OFFS_ADJ_1_F_OFS); };
   void         SetAdcOffsAdj1F(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_1_F_REG, WD2_ADC_OFFS_ADJ_1_F_MASK, WD2_ADC_OFFS_ADJ_1_F_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT_1_F - Output Invert
   unsigned int GetAdcOmOutInvert1F() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_1_F_REG, WD2_ADC_OM_OUT_INVERT_1_F_MASK, WD2_ADC_OM_OUT_INVERT_1_F_OFS); };
   void         SetAdcOmOutInvert1F(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_1_F_REG, WD2_ADC_OM_OUT_INVERT_1_F_MASK, WD2_ADC_OM_OUT_INVERT_1_F_OFS, value); };



   ////// ------ Control Register 92 [0x1170]: ADC_1_CH_G_CFG - ADC 1 (B) Channel G Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE_1_G - User Input Test Mode (see datasheet)
   unsigned int GetAdcTmUsrInMode1G() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_1_G_REG, WD2_ADC_TM_USR_IN_MODE_1_G_MASK, WD2_ADC_TM_USR_IN_MODE_1_G_OFS); };
   void         SetAdcTmUsrInMode1G(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_1_G_REG, WD2_ADC_TM_USR_IN_MODE_1_G_MASK, WD2_ADC_TM_USR_IN_MODE_1_G_OFS, value); };

   // 0x000F0000: ADC_TM_OUT_1_G - Output Test Mode (see datasheet)
   unsigned int GetAdcTmOut1G() { return BitExtractControl(WD2_ADC_TM_OUT_1_G_REG, WD2_ADC_TM_OUT_1_G_MASK, WD2_ADC_TM_OUT_1_G_OFS); };
   void         SetAdcTmOut1G(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_1_G_REG, WD2_ADC_TM_OUT_1_G_MASK, WD2_ADC_TM_OUT_1_G_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ_1_G - Device Offset Trim
   unsigned int GetAdcOffsAdj1G() { return BitExtractControl(WD2_ADC_OFFS_ADJ_1_G_REG, WD2_ADC_OFFS_ADJ_1_G_MASK, WD2_ADC_OFFS_ADJ_1_G_OFS); };
   void         SetAdcOffsAdj1G(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_1_G_REG, WD2_ADC_OFFS_ADJ_1_G_MASK, WD2_ADC_OFFS_ADJ_1_G_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT_1_G - Output Invert
   unsigned int GetAdcOmOutInvert1G() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_1_G_REG, WD2_ADC_OM_OUT_INVERT_1_G_MASK, WD2_ADC_OM_OUT_INVERT_1_G_OFS); };
   void         SetAdcOmOutInvert1G(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_1_G_REG, WD2_ADC_OM_OUT_INVERT_1_G_MASK, WD2_ADC_OM_OUT_INVERT_1_G_OFS, value); };



   ////// ------ Control Register 93 [0x1174]: ADC_1_CH_H_CFG - ADC 1 (B) Channel H Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000000) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE_1_H - User Input Test Mode (see datasheet)
   unsigned int GetAdcTmUsrInMode1H() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_1_H_REG, WD2_ADC_TM_USR_IN_MODE_1_H_MASK, WD2_ADC_TM_USR_IN_MODE_1_H_OFS); };
   void         SetAdcTmUsrInMode1H(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_1_H_REG, WD2_ADC_TM_USR_IN_MODE_1_H_MASK, WD2_ADC_TM_USR_IN_MODE_1_H_OFS, value); };

   // 0x000F0000: ADC_TM_OUT_1_H - Output Test Mode (see datasheet)
   unsigned int GetAdcTmOut1H() { return BitExtractControl(WD2_ADC_TM_OUT_1_H_REG, WD2_ADC_TM_OUT_1_H_MASK, WD2_ADC_TM_OUT_1_H_OFS); };
   void         SetAdcTmOut1H(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_1_H_REG, WD2_ADC_TM_OUT_1_H_MASK, WD2_ADC_TM_OUT_1_H_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ_1_H - Device Offset Trim
   unsigned int GetAdcOffsAdj1H() { return BitExtractControl(WD2_ADC_OFFS_ADJ_1_H_REG, WD2_ADC_OFFS_ADJ_1_H_MASK, WD2_ADC_OFFS_ADJ_1_H_OFS); };
   void         SetAdcOffsAdj1H(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_1_H_REG, WD2_ADC_OFFS_ADJ_1_H_MASK, WD2_ADC_OFFS_ADJ_1_H_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT_1_H - Output Invert
   unsigned int GetAdcOmOutInvert1H() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_1_H_REG, WD2_ADC_OM_OUT_INVERT_1_H_MASK, WD2_ADC_OM_OUT_INVERT_1_H_OFS); };
   void         SetAdcOmOutInvert1H(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_1_H_REG, WD2_ADC_OM_OUT_INVERT_1_H_MASK, WD2_ADC_OM_OUT_INVERT_1_H_OFS, value); };



   ////// ------ Control Register 94 [0x1178]: ADC_1_CH_DCO_CFG - ADC 1 (B) Channel DCO Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000000) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE_1_DCO - User Input Test Mode (see datasheet)
   unsigned int GetAdcTmUsrInMode1Dco() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_1_DCO_REG, WD2_ADC_TM_USR_IN_MODE_1_DCO_MASK, WD2_ADC_TM_USR_IN_MODE_1_DCO_OFS); };
   void         SetAdcTmUsrInMode1Dco(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_1_DCO_REG, WD2_ADC_TM_USR_IN_MODE_1_DCO_MASK, WD2_ADC_TM_USR_IN_MODE_1_DCO_OFS, value); };

   // 0x000F0000: ADC_TM_OUT_1_DCO - Output Test Mode (see datasheet)
   unsigned int GetAdcTmOut1Dco() { return BitExtractControl(WD2_ADC_TM_OUT_1_DCO_REG, WD2_ADC_TM_OUT_1_DCO_MASK, WD2_ADC_TM_OUT_1_DCO_OFS); };
   void         SetAdcTmOut1Dco(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_1_DCO_REG, WD2_ADC_TM_OUT_1_DCO_MASK, WD2_ADC_TM_OUT_1_DCO_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ_1_DCO - Device Offset Trim
   unsigned int GetAdcOffsAdj1Dco() { return BitExtractControl(WD2_ADC_OFFS_ADJ_1_DCO_REG, WD2_ADC_OFFS_ADJ_1_DCO_MASK, WD2_ADC_OFFS_ADJ_1_DCO_OFS); };
   void         SetAdcOffsAdj1Dco(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_1_DCO_REG, WD2_ADC_OFFS_ADJ_1_DCO_MASK, WD2_ADC_OFFS_ADJ_1_DCO_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT_1_DCO - Output Invert
   unsigned int GetAdcOmOutInvert1Dco() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_1_DCO_REG, WD2_ADC_OM_OUT_INVERT_1_DCO_MASK, WD2_ADC_OM_OUT_INVERT_1_DCO_OFS); };
   void         SetAdcOmOutInvert1Dco(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_1_DCO_REG, WD2_ADC_OM_OUT_INVERT_1_DCO_MASK, WD2_ADC_OM_OUT_INVERT_1_DCO_OFS, value); };



   ////// ------ Control Register 95 [0x117C]: ADC_1_CH_FCO_CFG - ADC 1 (B) Channel FCO Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000000) ------ //////

   // 0x00C00000: ADC_TM_USR_IN_MODE_1_FCO - User Input Test Mode (see datasheet)
   unsigned int GetAdcTmUsrInMode1Fco() { return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_1_FCO_REG, WD2_ADC_TM_USR_IN_MODE_1_FCO_MASK, WD2_ADC_TM_USR_IN_MODE_1_FCO_OFS); };
   void         SetAdcTmUsrInMode1Fco(unsigned int value) { SetRegMask(WD2_ADC_TM_USR_IN_MODE_1_FCO_REG, WD2_ADC_TM_USR_IN_MODE_1_FCO_MASK, WD2_ADC_TM_USR_IN_MODE_1_FCO_OFS, value); };

   // 0x000F0000: ADC_TM_OUT_1_FCO - Output Test Mode (see datasheet)
   unsigned int GetAdcTmOut1Fco() { return BitExtractControl(WD2_ADC_TM_OUT_1_FCO_REG, WD2_ADC_TM_OUT_1_FCO_MASK, WD2_ADC_TM_OUT_1_FCO_OFS); };
   void         SetAdcTmOut1Fco(unsigned int value) { SetRegMask(WD2_ADC_TM_OUT_1_FCO_REG, WD2_ADC_TM_OUT_1_FCO_MASK, WD2_ADC_TM_OUT_1_FCO_OFS, value); };

   // 0x0000FF00: ADC_OFFS_ADJ_1_FCO - Device Offset Trim
   unsigned int GetAdcOffsAdj1Fco() { return BitExtractControl(WD2_ADC_OFFS_ADJ_1_FCO_REG, WD2_ADC_OFFS_ADJ_1_FCO_MASK, WD2_ADC_OFFS_ADJ_1_FCO_OFS); };
   void         SetAdcOffsAdj1Fco(unsigned int value) { SetRegMask(WD2_ADC_OFFS_ADJ_1_FCO_REG, WD2_ADC_OFFS_ADJ_1_FCO_MASK, WD2_ADC_OFFS_ADJ_1_FCO_OFS, value); };

   // 0x00000004: ADC_OM_OUT_INVERT_1_FCO - Output Invert
   unsigned int GetAdcOmOutInvert1Fco() { return BitExtractControl(WD2_ADC_OM_OUT_INVERT_1_FCO_REG, WD2_ADC_OM_OUT_INVERT_1_FCO_MASK, WD2_ADC_OM_OUT_INVERT_1_FCO_OFS); };
   void         SetAdcOmOutInvert1Fco(unsigned int value) { SetRegMask(WD2_ADC_OM_OUT_INVERT_1_FCO_REG, WD2_ADC_OM_OUT_INVERT_1_FCO_MASK, WD2_ADC_OM_OUT_INVERT_1_FCO_OFS, value); };



   ////// ------ Control Register 96 [0x1180]: TRG_CFG - Trigger Configuration (Default: 0x00000000) ------ //////

   // 0x00010000: LEAD_TRAIL_EDGE_SEL - 0 = trigger on leading edge, 1 = trigger on trailing edge
   unsigned int GetLeadTrailEdgeSel() { return BitExtractControl(WD2_LEAD_TRAIL_EDGE_SEL_REG, WD2_LEAD_TRAIL_EDGE_SEL_MASK, WD2_LEAD_TRAIL_EDGE_SEL_OFS); };
   void         SetLeadTrailEdgeSel(unsigned int value) { SetRegMask(WD2_LEAD_TRAIL_EDGE_SEL_REG, WD2_LEAD_TRAIL_EDGE_SEL_MASK, WD2_LEAD_TRAIL_EDGE_SEL_OFS, value); };

   // 0x00002000: EXT_TRIGGER_OUT_ENABLE - Enable output of trigger signal to MCX connector
   unsigned int GetExtTriggerOutEnable() { return BitExtractControl(WD2_EXT_TRIGGER_OUT_ENABLE_REG, WD2_EXT_TRIGGER_OUT_ENABLE_MASK, WD2_EXT_TRIGGER_OUT_ENABLE_OFS); };
   void         SetExtTriggerOutEnable(unsigned int value) { SetRegMask(WD2_EXT_TRIGGER_OUT_ENABLE_REG, WD2_EXT_TRIGGER_OUT_ENABLE_MASK, WD2_EXT_TRIGGER_OUT_ENABLE_OFS, value); };

   // 0x00001000: TRIGGER_TYPE_SEL - 0 = use local hardware trigger and external tirgger (synchronized), 1 = use asynchronous external trigger
   unsigned int GetTriggerTypeSel() { return BitExtractControl(WD2_TRIGGER_TYPE_SEL_REG, WD2_TRIGGER_TYPE_SEL_MASK, WD2_TRIGGER_TYPE_SEL_OFS); };
   void         SetTriggerTypeSel(unsigned int value) { SetRegMask(WD2_TRIGGER_TYPE_SEL_REG, WD2_TRIGGER_TYPE_SEL_MASK, WD2_TRIGGER_TYPE_SEL_OFS, value); };

   // 0x00000700: TRIGGER_OUT_PULSE_LENGTH - Length of the trigger output pulse in cycles
   unsigned int GetTriggerOutPulseLength() { return BitExtractControl(WD2_TRIGGER_OUT_PULSE_LENGTH_REG, WD2_TRIGGER_OUT_PULSE_LENGTH_MASK, WD2_TRIGGER_OUT_PULSE_LENGTH_OFS); };
   void         SetTriggerOutPulseLength(unsigned int value) { SetRegMask(WD2_TRIGGER_OUT_PULSE_LENGTH_REG, WD2_TRIGGER_OUT_PULSE_LENGTH_MASK, WD2_TRIGGER_OUT_PULSE_LENGTH_OFS, value); };

   // 0x000000FF: TRIGGER_DELAY - trigger delay in ticks of 6.25 ns
   unsigned int GetTriggerDelay() { return BitExtractControl(WD2_TRIGGER_DELAY_REG, WD2_TRIGGER_DELAY_MASK, WD2_TRIGGER_DELAY_OFS); };
   void         SetTriggerDelay(unsigned int value) { SetRegMask(WD2_TRIGGER_DELAY_REG, WD2_TRIGGER_DELAY_MASK, WD2_TRIGGER_DELAY_OFS, value); };



   ////// ------ Control Register 97 [0x1184]: TRG_SRC_POL - Trigger Source Polarity (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_SRC_POLARITY - Polarity of trigger source (0 = normal, 1 = inverted) (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
   unsigned int GetTrgSrcPolarity() { return BitExtractControl(WD2_TRG_SRC_POLARITY_REG, WD2_TRG_SRC_POLARITY_MASK, WD2_TRG_SRC_POLARITY_OFS); };
   void         SetTrgSrcPolarity(unsigned int value) { SetRegMask(WD2_TRG_SRC_POLARITY_REG, WD2_TRG_SRC_POLARITY_MASK, WD2_TRG_SRC_POLARITY_OFS, value); };



   ////// ------ Control Register 98 [0x1188]: TRG_AUTO_PERIOD - Automatic Trigger Period (Default: 0x04C4B400) ------ //////

   // 0xFFFFFFFF: AUTO_TRIGGER_PERIOD - Period of automatic trigger in ticks of the DAQ clock
   unsigned int GetAutoTriggerPeriod() { return BitExtractControl(WD2_AUTO_TRIGGER_PERIOD_REG, WD2_AUTO_TRIGGER_PERIOD_MASK, WD2_AUTO_TRIGGER_PERIOD_OFS); };
   void         SetAutoTriggerPeriod(unsigned int value) { SetRegMask(WD2_AUTO_TRIGGER_PERIOD_REG, WD2_AUTO_TRIGGER_PERIOD_MASK, WD2_AUTO_TRIGGER_PERIOD_OFS, value); };



   ////// ------ Control Register 99 [0x118C]: TRG_PTRN_EN - Enable for trigger patterns (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_PTRN_EN - 1 enables the corresponding trigger patterns for the local trigger
   unsigned int GetTrgPtrnEn() { return BitExtractControl(WD2_TRG_PTRN_EN_REG, WD2_TRG_PTRN_EN_MASK, WD2_TRG_PTRN_EN_OFS); };
   void         SetTrgPtrnEn(unsigned int value) { SetRegMask(WD2_TRG_PTRN_EN_REG, WD2_TRG_PTRN_EN_MASK, WD2_TRG_PTRN_EN_OFS, value); };



   ////// ------ Control Register 100 [0x1190]: TRG_SRC_EN_PTRN0 - Trigger Source Enable Pattern 0 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_SRC_EN_PTRN0 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
   unsigned int GetTrgSrcEnPtrn0() { return BitExtractControl(WD2_TRG_SRC_EN_PTRN0_REG, WD2_TRG_SRC_EN_PTRN0_MASK, WD2_TRG_SRC_EN_PTRN0_OFS); };
   void         SetTrgSrcEnPtrn0(unsigned int value) { SetRegMask(WD2_TRG_SRC_EN_PTRN0_REG, WD2_TRG_SRC_EN_PTRN0_MASK, WD2_TRG_SRC_EN_PTRN0_OFS, value); };



   ////// ------ Control Register 101 [0x1194]: TRG_STATE_PTRN0 - Trigger State Pattern 0 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_STATE_PTRN0 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
   unsigned int GetTrgStatePtrn0() { return BitExtractControl(WD2_TRG_STATE_PTRN0_REG, WD2_TRG_STATE_PTRN0_MASK, WD2_TRG_STATE_PTRN0_OFS); };
   void         SetTrgStatePtrn0(unsigned int value) { SetRegMask(WD2_TRG_STATE_PTRN0_REG, WD2_TRG_STATE_PTRN0_MASK, WD2_TRG_STATE_PTRN0_OFS, value); };



   ////// ------ Control Register 102 [0x1198]: TRG_SRC_EN_PTRN1 - Trigger Source Enable Pattern 1 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_SRC_EN_PTRN1 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
   unsigned int GetTrgSrcEnPtrn1() { return BitExtractControl(WD2_TRG_SRC_EN_PTRN1_REG, WD2_TRG_SRC_EN_PTRN1_MASK, WD2_TRG_SRC_EN_PTRN1_OFS); };
   void         SetTrgSrcEnPtrn1(unsigned int value) { SetRegMask(WD2_TRG_SRC_EN_PTRN1_REG, WD2_TRG_SRC_EN_PTRN1_MASK, WD2_TRG_SRC_EN_PTRN1_OFS, value); };



   ////// ------ Control Register 103 [0x119C]: TRG_STATE_PTRN1 - Trigger State Pattern 1 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_STATE_PTRN1 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
   unsigned int GetTrgStatePtrn1() { return BitExtractControl(WD2_TRG_STATE_PTRN1_REG, WD2_TRG_STATE_PTRN1_MASK, WD2_TRG_STATE_PTRN1_OFS); };
   void         SetTrgStatePtrn1(unsigned int value) { SetRegMask(WD2_TRG_STATE_PTRN1_REG, WD2_TRG_STATE_PTRN1_MASK, WD2_TRG_STATE_PTRN1_OFS, value); };



   ////// ------ Control Register 104 [0x11A0]: TRG_SRC_EN_PTRN2 - Trigger Source Enable Pattern 2 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_SRC_EN_PTRN2 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
   unsigned int GetTrgSrcEnPtrn2() { return BitExtractControl(WD2_TRG_SRC_EN_PTRN2_REG, WD2_TRG_SRC_EN_PTRN2_MASK, WD2_TRG_SRC_EN_PTRN2_OFS); };
   void         SetTrgSrcEnPtrn2(unsigned int value) { SetRegMask(WD2_TRG_SRC_EN_PTRN2_REG, WD2_TRG_SRC_EN_PTRN2_MASK, WD2_TRG_SRC_EN_PTRN2_OFS, value); };



   ////// ------ Control Register 105 [0x11A4]: TRG_STATE_PTRN2 - Trigger State Pattern 2 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_STATE_PTRN2 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
   unsigned int GetTrgStatePtrn2() { return BitExtractControl(WD2_TRG_STATE_PTRN2_REG, WD2_TRG_STATE_PTRN2_MASK, WD2_TRG_STATE_PTRN2_OFS); };
   void         SetTrgStatePtrn2(unsigned int value) { SetRegMask(WD2_TRG_STATE_PTRN2_REG, WD2_TRG_STATE_PTRN2_MASK, WD2_TRG_STATE_PTRN2_OFS, value); };



   ////// ------ Control Register 106 [0x11A8]: TRG_SRC_EN_PTRN3 - Trigger Source Enable Pattern 3 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_SRC_EN_PTRN3 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
   unsigned int GetTrgSrcEnPtrn3() { return BitExtractControl(WD2_TRG_SRC_EN_PTRN3_REG, WD2_TRG_SRC_EN_PTRN3_MASK, WD2_TRG_SRC_EN_PTRN3_OFS); };
   void         SetTrgSrcEnPtrn3(unsigned int value) { SetRegMask(WD2_TRG_SRC_EN_PTRN3_REG, WD2_TRG_SRC_EN_PTRN3_MASK, WD2_TRG_SRC_EN_PTRN3_OFS, value); };



   ////// ------ Control Register 107 [0x11AC]: TRG_STATE_PTRN3 - Trigger State Pattern 3 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_STATE_PTRN3 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
   unsigned int GetTrgStatePtrn3() { return BitExtractControl(WD2_TRG_STATE_PTRN3_REG, WD2_TRG_STATE_PTRN3_MASK, WD2_TRG_STATE_PTRN3_OFS); };
   void         SetTrgStatePtrn3(unsigned int value) { SetRegMask(WD2_TRG_STATE_PTRN3_REG, WD2_TRG_STATE_PTRN3_MASK, WD2_TRG_STATE_PTRN3_OFS, value); };



   ////// ------ Control Register 108 [0x11B0]: TRG_SRC_EN_PTRN4 - Trigger Source Enable Pattern 4 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_SRC_EN_PTRN4 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
   unsigned int GetTrgSrcEnPtrn4() { return BitExtractControl(WD2_TRG_SRC_EN_PTRN4_REG, WD2_TRG_SRC_EN_PTRN4_MASK, WD2_TRG_SRC_EN_PTRN4_OFS); };
   void         SetTrgSrcEnPtrn4(unsigned int value) { SetRegMask(WD2_TRG_SRC_EN_PTRN4_REG, WD2_TRG_SRC_EN_PTRN4_MASK, WD2_TRG_SRC_EN_PTRN4_OFS, value); };



   ////// ------ Control Register 109 [0x11B4]: TRG_STATE_PTRN4 - Trigger State Pattern 4 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_STATE_PTRN4 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
   unsigned int GetTrgStatePtrn4() { return BitExtractControl(WD2_TRG_STATE_PTRN4_REG, WD2_TRG_STATE_PTRN4_MASK, WD2_TRG_STATE_PTRN4_OFS); };
   void         SetTrgStatePtrn4(unsigned int value) { SetRegMask(WD2_TRG_STATE_PTRN4_REG, WD2_TRG_STATE_PTRN4_MASK, WD2_TRG_STATE_PTRN4_OFS, value); };



   ////// ------ Control Register 110 [0x11B8]: TRG_SRC_EN_PTRN5 - Trigger Source Enable Pattern 5 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_SRC_EN_PTRN5 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
   unsigned int GetTrgSrcEnPtrn5() { return BitExtractControl(WD2_TRG_SRC_EN_PTRN5_REG, WD2_TRG_SRC_EN_PTRN5_MASK, WD2_TRG_SRC_EN_PTRN5_OFS); };
   void         SetTrgSrcEnPtrn5(unsigned int value) { SetRegMask(WD2_TRG_SRC_EN_PTRN5_REG, WD2_TRG_SRC_EN_PTRN5_MASK, WD2_TRG_SRC_EN_PTRN5_OFS, value); };



   ////// ------ Control Register 111 [0x11BC]: TRG_STATE_PTRN5 - Trigger State Pattern 5 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_STATE_PTRN5 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
   unsigned int GetTrgStatePtrn5() { return BitExtractControl(WD2_TRG_STATE_PTRN5_REG, WD2_TRG_STATE_PTRN5_MASK, WD2_TRG_STATE_PTRN5_OFS); };
   void         SetTrgStatePtrn5(unsigned int value) { SetRegMask(WD2_TRG_STATE_PTRN5_REG, WD2_TRG_STATE_PTRN5_MASK, WD2_TRG_STATE_PTRN5_OFS, value); };



   ////// ------ Control Register 112 [0x11C0]: TRG_SRC_EN_PTRN6 - Trigger Source Enable Pattern 6 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_SRC_EN_PTRN6 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
   unsigned int GetTrgSrcEnPtrn6() { return BitExtractControl(WD2_TRG_SRC_EN_PTRN6_REG, WD2_TRG_SRC_EN_PTRN6_MASK, WD2_TRG_SRC_EN_PTRN6_OFS); };
   void         SetTrgSrcEnPtrn6(unsigned int value) { SetRegMask(WD2_TRG_SRC_EN_PTRN6_REG, WD2_TRG_SRC_EN_PTRN6_MASK, WD2_TRG_SRC_EN_PTRN6_OFS, value); };



   ////// ------ Control Register 113 [0x11C4]: TRG_STATE_PTRN6 - Trigger State Pattern 6 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_STATE_PTRN6 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
   unsigned int GetTrgStatePtrn6() { return BitExtractControl(WD2_TRG_STATE_PTRN6_REG, WD2_TRG_STATE_PTRN6_MASK, WD2_TRG_STATE_PTRN6_OFS); };
   void         SetTrgStatePtrn6(unsigned int value) { SetRegMask(WD2_TRG_STATE_PTRN6_REG, WD2_TRG_STATE_PTRN6_MASK, WD2_TRG_STATE_PTRN6_OFS, value); };



   ////// ------ Control Register 114 [0x11C8]: TRG_SRC_EN_PTRN7 - Trigger Source Enable Pattern 7 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_SRC_EN_PTRN7 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
   unsigned int GetTrgSrcEnPtrn7() { return BitExtractControl(WD2_TRG_SRC_EN_PTRN7_REG, WD2_TRG_SRC_EN_PTRN7_MASK, WD2_TRG_SRC_EN_PTRN7_OFS); };
   void         SetTrgSrcEnPtrn7(unsigned int value) { SetRegMask(WD2_TRG_SRC_EN_PTRN7_REG, WD2_TRG_SRC_EN_PTRN7_MASK, WD2_TRG_SRC_EN_PTRN7_OFS, value); };



   ////// ------ Control Register 115 [0x11CC]: TRG_STATE_PTRN7 - Trigger State Pattern 7 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_STATE_PTRN7 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
   unsigned int GetTrgStatePtrn7() { return BitExtractControl(WD2_TRG_STATE_PTRN7_REG, WD2_TRG_STATE_PTRN7_MASK, WD2_TRG_STATE_PTRN7_OFS); };
   void         SetTrgStatePtrn7(unsigned int value) { SetRegMask(WD2_TRG_STATE_PTRN7_REG, WD2_TRG_STATE_PTRN7_MASK, WD2_TRG_STATE_PTRN7_OFS, value); };



   ////// ------ Control Register 116 [0x11D0]: TRG_SRC_EN_PTRN8 - Trigger Source Enable Pattern 8 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_SRC_EN_PTRN8 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
   unsigned int GetTrgSrcEnPtrn8() { return BitExtractControl(WD2_TRG_SRC_EN_PTRN8_REG, WD2_TRG_SRC_EN_PTRN8_MASK, WD2_TRG_SRC_EN_PTRN8_OFS); };
   void         SetTrgSrcEnPtrn8(unsigned int value) { SetRegMask(WD2_TRG_SRC_EN_PTRN8_REG, WD2_TRG_SRC_EN_PTRN8_MASK, WD2_TRG_SRC_EN_PTRN8_OFS, value); };



   ////// ------ Control Register 117 [0x11D4]: TRG_STATE_PTRN8 - Trigger State Pattern 8 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_STATE_PTRN8 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
   unsigned int GetTrgStatePtrn8() { return BitExtractControl(WD2_TRG_STATE_PTRN8_REG, WD2_TRG_STATE_PTRN8_MASK, WD2_TRG_STATE_PTRN8_OFS); };
   void         SetTrgStatePtrn8(unsigned int value) { SetRegMask(WD2_TRG_STATE_PTRN8_REG, WD2_TRG_STATE_PTRN8_MASK, WD2_TRG_STATE_PTRN8_OFS, value); };



   ////// ------ Control Register 118 [0x11D8]: TRG_SRC_EN_PTRN9 - Trigger Source Enable Pattern 9 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_SRC_EN_PTRN9 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
   unsigned int GetTrgSrcEnPtrn9() { return BitExtractControl(WD2_TRG_SRC_EN_PTRN9_REG, WD2_TRG_SRC_EN_PTRN9_MASK, WD2_TRG_SRC_EN_PTRN9_OFS); };
   void         SetTrgSrcEnPtrn9(unsigned int value) { SetRegMask(WD2_TRG_SRC_EN_PTRN9_REG, WD2_TRG_SRC_EN_PTRN9_MASK, WD2_TRG_SRC_EN_PTRN9_OFS, value); };



   ////// ------ Control Register 119 [0x11DC]: TRG_STATE_PTRN9 - Trigger State Pattern 9 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_STATE_PTRN9 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
   unsigned int GetTrgStatePtrn9() { return BitExtractControl(WD2_TRG_STATE_PTRN9_REG, WD2_TRG_STATE_PTRN9_MASK, WD2_TRG_STATE_PTRN9_OFS); };
   void         SetTrgStatePtrn9(unsigned int value) { SetRegMask(WD2_TRG_STATE_PTRN9_REG, WD2_TRG_STATE_PTRN9_MASK, WD2_TRG_STATE_PTRN9_OFS, value); };



   ////// ------ Control Register 120 [0x11E0]: TRG_SRC_EN_PTRN10 - Trigger Source Enable Pattern 10 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_SRC_EN_PTRN10 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
   unsigned int GetTrgSrcEnPtrn10() { return BitExtractControl(WD2_TRG_SRC_EN_PTRN10_REG, WD2_TRG_SRC_EN_PTRN10_MASK, WD2_TRG_SRC_EN_PTRN10_OFS); };
   void         SetTrgSrcEnPtrn10(unsigned int value) { SetRegMask(WD2_TRG_SRC_EN_PTRN10_REG, WD2_TRG_SRC_EN_PTRN10_MASK, WD2_TRG_SRC_EN_PTRN10_OFS, value); };



   ////// ------ Control Register 121 [0x11E4]: TRG_STATE_PTRN10 - Trigger State Pattern 10 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_STATE_PTRN10 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
   unsigned int GetTrgStatePtrn10() { return BitExtractControl(WD2_TRG_STATE_PTRN10_REG, WD2_TRG_STATE_PTRN10_MASK, WD2_TRG_STATE_PTRN10_OFS); };
   void         SetTrgStatePtrn10(unsigned int value) { SetRegMask(WD2_TRG_STATE_PTRN10_REG, WD2_TRG_STATE_PTRN10_MASK, WD2_TRG_STATE_PTRN10_OFS, value); };



   ////// ------ Control Register 122 [0x11E8]: TRG_SRC_EN_PTRN11 - Trigger Source Enable Pattern 11 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_SRC_EN_PTRN11 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
   unsigned int GetTrgSrcEnPtrn11() { return BitExtractControl(WD2_TRG_SRC_EN_PTRN11_REG, WD2_TRG_SRC_EN_PTRN11_MASK, WD2_TRG_SRC_EN_PTRN11_OFS); };
   void         SetTrgSrcEnPtrn11(unsigned int value) { SetRegMask(WD2_TRG_SRC_EN_PTRN11_REG, WD2_TRG_SRC_EN_PTRN11_MASK, WD2_TRG_SRC_EN_PTRN11_OFS, value); };



   ////// ------ Control Register 123 [0x11EC]: TRG_STATE_PTRN11 - Trigger State Pattern 11 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_STATE_PTRN11 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
   unsigned int GetTrgStatePtrn11() { return BitExtractControl(WD2_TRG_STATE_PTRN11_REG, WD2_TRG_STATE_PTRN11_MASK, WD2_TRG_STATE_PTRN11_OFS); };
   void         SetTrgStatePtrn11(unsigned int value) { SetRegMask(WD2_TRG_STATE_PTRN11_REG, WD2_TRG_STATE_PTRN11_MASK, WD2_TRG_STATE_PTRN11_OFS, value); };



   ////// ------ Control Register 124 [0x11F0]: TRG_SRC_EN_PTRN12 - Trigger Source Enable Pattern 12 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_SRC_EN_PTRN12 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
   unsigned int GetTrgSrcEnPtrn12() { return BitExtractControl(WD2_TRG_SRC_EN_PTRN12_REG, WD2_TRG_SRC_EN_PTRN12_MASK, WD2_TRG_SRC_EN_PTRN12_OFS); };
   void         SetTrgSrcEnPtrn12(unsigned int value) { SetRegMask(WD2_TRG_SRC_EN_PTRN12_REG, WD2_TRG_SRC_EN_PTRN12_MASK, WD2_TRG_SRC_EN_PTRN12_OFS, value); };



   ////// ------ Control Register 125 [0x11F4]: TRG_STATE_PTRN12 - Trigger State Pattern 12 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_STATE_PTRN12 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
   unsigned int GetTrgStatePtrn12() { return BitExtractControl(WD2_TRG_STATE_PTRN12_REG, WD2_TRG_STATE_PTRN12_MASK, WD2_TRG_STATE_PTRN12_OFS); };
   void         SetTrgStatePtrn12(unsigned int value) { SetRegMask(WD2_TRG_STATE_PTRN12_REG, WD2_TRG_STATE_PTRN12_MASK, WD2_TRG_STATE_PTRN12_OFS, value); };



   ////// ------ Control Register 126 [0x11F8]: TRG_SRC_EN_PTRN13 - Trigger Source Enable Pattern 13 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_SRC_EN_PTRN13 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
   unsigned int GetTrgSrcEnPtrn13() { return BitExtractControl(WD2_TRG_SRC_EN_PTRN13_REG, WD2_TRG_SRC_EN_PTRN13_MASK, WD2_TRG_SRC_EN_PTRN13_OFS); };
   void         SetTrgSrcEnPtrn13(unsigned int value) { SetRegMask(WD2_TRG_SRC_EN_PTRN13_REG, WD2_TRG_SRC_EN_PTRN13_MASK, WD2_TRG_SRC_EN_PTRN13_OFS, value); };



   ////// ------ Control Register 127 [0x11FC]: TRG_STATE_PTRN13 - Trigger State Pattern 13 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_STATE_PTRN13 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
   unsigned int GetTrgStatePtrn13() { return BitExtractControl(WD2_TRG_STATE_PTRN13_REG, WD2_TRG_STATE_PTRN13_MASK, WD2_TRG_STATE_PTRN13_OFS); };
   void         SetTrgStatePtrn13(unsigned int value) { SetRegMask(WD2_TRG_STATE_PTRN13_REG, WD2_TRG_STATE_PTRN13_MASK, WD2_TRG_STATE_PTRN13_OFS, value); };



   ////// ------ Control Register 128 [0x1200]: TRG_SRC_EN_PTRN14 - Trigger Source Enable Pattern 14 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_SRC_EN_PTRN14 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
   unsigned int GetTrgSrcEnPtrn14() { return BitExtractControl(WD2_TRG_SRC_EN_PTRN14_REG, WD2_TRG_SRC_EN_PTRN14_MASK, WD2_TRG_SRC_EN_PTRN14_OFS); };
   void         SetTrgSrcEnPtrn14(unsigned int value) { SetRegMask(WD2_TRG_SRC_EN_PTRN14_REG, WD2_TRG_SRC_EN_PTRN14_MASK, WD2_TRG_SRC_EN_PTRN14_OFS, value); };



   ////// ------ Control Register 129 [0x1204]: TRG_STATE_PTRN14 - Trigger State Pattern 14 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_STATE_PTRN14 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
   unsigned int GetTrgStatePtrn14() { return BitExtractControl(WD2_TRG_STATE_PTRN14_REG, WD2_TRG_STATE_PTRN14_MASK, WD2_TRG_STATE_PTRN14_OFS); };
   void         SetTrgStatePtrn14(unsigned int value) { SetRegMask(WD2_TRG_STATE_PTRN14_REG, WD2_TRG_STATE_PTRN14_MASK, WD2_TRG_STATE_PTRN14_OFS, value); };



   ////// ------ Control Register 130 [0x1208]: TRG_SRC_EN_PTRN15 - Trigger Source Enable Pattern 15 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_SRC_EN_PTRN15 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
   unsigned int GetTrgSrcEnPtrn15() { return BitExtractControl(WD2_TRG_SRC_EN_PTRN15_REG, WD2_TRG_SRC_EN_PTRN15_MASK, WD2_TRG_SRC_EN_PTRN15_OFS); };
   void         SetTrgSrcEnPtrn15(unsigned int value) { SetRegMask(WD2_TRG_SRC_EN_PTRN15_REG, WD2_TRG_SRC_EN_PTRN15_MASK, WD2_TRG_SRC_EN_PTRN15_OFS, value); };



   ////// ------ Control Register 131 [0x120C]: TRG_STATE_PTRN15 - Trigger State Pattern 15 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_STATE_PTRN15 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
   unsigned int GetTrgStatePtrn15() { return BitExtractControl(WD2_TRG_STATE_PTRN15_REG, WD2_TRG_STATE_PTRN15_MASK, WD2_TRG_STATE_PTRN15_OFS); };
   void         SetTrgStatePtrn15(unsigned int value) { SetRegMask(WD2_TRG_STATE_PTRN15_REG, WD2_TRG_STATE_PTRN15_MASK, WD2_TRG_STATE_PTRN15_OFS, value); };



   ////// ------ Control Register 132 [0x1210]: TRG_SRC_EN_PTRN16 - Trigger Source Enable Pattern 16 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_SRC_EN_PTRN16 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
   unsigned int GetTrgSrcEnPtrn16() { return BitExtractControl(WD2_TRG_SRC_EN_PTRN16_REG, WD2_TRG_SRC_EN_PTRN16_MASK, WD2_TRG_SRC_EN_PTRN16_OFS); };
   void         SetTrgSrcEnPtrn16(unsigned int value) { SetRegMask(WD2_TRG_SRC_EN_PTRN16_REG, WD2_TRG_SRC_EN_PTRN16_MASK, WD2_TRG_SRC_EN_PTRN16_OFS, value); };



   ////// ------ Control Register 133 [0x1214]: TRG_STATE_PTRN16 - Trigger State Pattern 16 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_STATE_PTRN16 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
   unsigned int GetTrgStatePtrn16() { return BitExtractControl(WD2_TRG_STATE_PTRN16_REG, WD2_TRG_STATE_PTRN16_MASK, WD2_TRG_STATE_PTRN16_OFS); };
   void         SetTrgStatePtrn16(unsigned int value) { SetRegMask(WD2_TRG_STATE_PTRN16_REG, WD2_TRG_STATE_PTRN16_MASK, WD2_TRG_STATE_PTRN16_OFS, value); };



   ////// ------ Control Register 134 [0x1218]: TRG_SRC_EN_PTRN17 - Trigger Source Enable Pattern 17 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_SRC_EN_PTRN17 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
   unsigned int GetTrgSrcEnPtrn17() { return BitExtractControl(WD2_TRG_SRC_EN_PTRN17_REG, WD2_TRG_SRC_EN_PTRN17_MASK, WD2_TRG_SRC_EN_PTRN17_OFS); };
   void         SetTrgSrcEnPtrn17(unsigned int value) { SetRegMask(WD2_TRG_SRC_EN_PTRN17_REG, WD2_TRG_SRC_EN_PTRN17_MASK, WD2_TRG_SRC_EN_PTRN17_OFS, value); };



   ////// ------ Control Register 135 [0x121C]: TRG_STATE_PTRN17 - Trigger State Pattern 17 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_STATE_PTRN17 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
   unsigned int GetTrgStatePtrn17() { return BitExtractControl(WD2_TRG_STATE_PTRN17_REG, WD2_TRG_STATE_PTRN17_MASK, WD2_TRG_STATE_PTRN17_OFS); };
   void         SetTrgStatePtrn17(unsigned int value) { SetRegMask(WD2_TRG_STATE_PTRN17_REG, WD2_TRG_STATE_PTRN17_MASK, WD2_TRG_STATE_PTRN17_OFS, value); };



   ////// ------ Control Register 136 [0x1220]: TRG_SRC_EN_PTRN18 - Trigger Source Enable Pattern 18 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_SRC_EN_PTRN18 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
   unsigned int GetTrgSrcEnPtrn18() { return BitExtractControl(WD2_TRG_SRC_EN_PTRN18_REG, WD2_TRG_SRC_EN_PTRN18_MASK, WD2_TRG_SRC_EN_PTRN18_OFS); };
   void         SetTrgSrcEnPtrn18(unsigned int value) { SetRegMask(WD2_TRG_SRC_EN_PTRN18_REG, WD2_TRG_SRC_EN_PTRN18_MASK, WD2_TRG_SRC_EN_PTRN18_OFS, value); };



   ////// ------ Control Register 137 [0x1224]: TRG_STATE_PTRN18 - Trigger State Pattern 18 (Default: 0x00000000) ------ //////

   // 0x0007FFFF: TRG_STATE_PTRN18 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
   unsigned int GetTrgStatePtrn18() { return BitExtractControl(WD2_TRG_STATE_PTRN18_REG, WD2_TRG_STATE_PTRN18_MASK, WD2_TRG_STATE_PTRN18_OFS); };
   void         SetTrgStatePtrn18(unsigned int value) { SetRegMask(WD2_TRG_STATE_PTRN18_REG, WD2_TRG_STATE_PTRN18_MASK, WD2_TRG_STATE_PTRN18_OFS, value); };



   ////// ------ Control Register 138 [0x1228]: ADV_TRG_CTRL - Advanced Trigger Control Register (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_CTRL - Advanced trigger control register
   unsigned int GetAdvTrgCtrl() { return BitExtractControl(WD2_ADV_TRG_CTRL_REG, WD2_ADV_TRG_CTRL_MASK, WD2_ADV_TRG_CTRL_OFS); };
   void         SetAdvTrgCtrl(unsigned int value) { SetRegMask(WD2_ADV_TRG_CTRL_REG, WD2_ADV_TRG_CTRL_MASK, WD2_ADV_TRG_CTRL_OFS, value); };



   ////// ------ Control Register 139 [0x122C]: ADV_TRG_CH_CAL0 - Advanced Trigger Channel Calibration Register 0 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_CH_CAL0 - Advanced trigger channel calibration register 0
   unsigned int GetAdvTrgChCal0() { return BitExtractControl(WD2_ADV_TRG_CH_CAL0_REG, WD2_ADV_TRG_CH_CAL0_MASK, WD2_ADV_TRG_CH_CAL0_OFS); };
   void         SetAdvTrgChCal0(unsigned int value) { SetRegMask(WD2_ADV_TRG_CH_CAL0_REG, WD2_ADV_TRG_CH_CAL0_MASK, WD2_ADV_TRG_CH_CAL0_OFS, value); };



   ////// ------ Control Register 140 [0x1230]: ADV_TRG_CH_CAL1 - Advanced Trigger Channel Calibration Register 1 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_CH_CAL1 - Advanced trigger channel calibration register 1
   unsigned int GetAdvTrgChCal1() { return BitExtractControl(WD2_ADV_TRG_CH_CAL1_REG, WD2_ADV_TRG_CH_CAL1_MASK, WD2_ADV_TRG_CH_CAL1_OFS); };
   void         SetAdvTrgChCal1(unsigned int value) { SetRegMask(WD2_ADV_TRG_CH_CAL1_REG, WD2_ADV_TRG_CH_CAL1_MASK, WD2_ADV_TRG_CH_CAL1_OFS, value); };



   ////// ------ Control Register 141 [0x1234]: ADV_TRG_CH_CAL2 - Advanced Trigger Channel Calibration Register 2 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_CH_CAL2 - Advanced trigger channel calibration register 2
   unsigned int GetAdvTrgChCal2() { return BitExtractControl(WD2_ADV_TRG_CH_CAL2_REG, WD2_ADV_TRG_CH_CAL2_MASK, WD2_ADV_TRG_CH_CAL2_OFS); };
   void         SetAdvTrgChCal2(unsigned int value) { SetRegMask(WD2_ADV_TRG_CH_CAL2_REG, WD2_ADV_TRG_CH_CAL2_MASK, WD2_ADV_TRG_CH_CAL2_OFS, value); };



   ////// ------ Control Register 142 [0x1238]: ADV_TRG_CH_CAL3 - Advanced Trigger Channel Calibration Register 3 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_CH_CAL3 - Advanced trigger channel calibration register 3
   unsigned int GetAdvTrgChCal3() { return BitExtractControl(WD2_ADV_TRG_CH_CAL3_REG, WD2_ADV_TRG_CH_CAL3_MASK, WD2_ADV_TRG_CH_CAL3_OFS); };
   void         SetAdvTrgChCal3(unsigned int value) { SetRegMask(WD2_ADV_TRG_CH_CAL3_REG, WD2_ADV_TRG_CH_CAL3_MASK, WD2_ADV_TRG_CH_CAL3_OFS, value); };



   ////// ------ Control Register 143 [0x123C]: ADV_TRG_PED_CFG - Advanced Trigger Pedestal Configuration Register (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_PED_CFG - Advanced trigger pedestal configuration register
   unsigned int GetAdvTrgPedCfg() { return BitExtractControl(WD2_ADV_TRG_PED_CFG_REG, WD2_ADV_TRG_PED_CFG_MASK, WD2_ADV_TRG_PED_CFG_OFS); };
   void         SetAdvTrgPedCfg(unsigned int value) { SetRegMask(WD2_ADV_TRG_PED_CFG_REG, WD2_ADV_TRG_PED_CFG_MASK, WD2_ADV_TRG_PED_CFG_OFS, value); };



   ////// ------ Control Register 144 [0x1240]: ADV_TRG_THR0 - Advanced Trigger Threshold 0 Register (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_THR0 - Advanced trigger threshold 0 register
   unsigned int GetAdvTrgThr0() { return BitExtractControl(WD2_ADV_TRG_THR0_REG, WD2_ADV_TRG_THR0_MASK, WD2_ADV_TRG_THR0_OFS); };
   void         SetAdvTrgThr0(unsigned int value) { SetRegMask(WD2_ADV_TRG_THR0_REG, WD2_ADV_TRG_THR0_MASK, WD2_ADV_TRG_THR0_OFS, value); };



   ////// ------ Control Register 145 [0x1244]: ADV_TRG_THR1 - Advanced Trigger Threshold 1 Register (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_THR1 - Advanced trigger threshold 1 register
   unsigned int GetAdvTrgThr1() { return BitExtractControl(WD2_ADV_TRG_THR1_REG, WD2_ADV_TRG_THR1_MASK, WD2_ADV_TRG_THR1_OFS); };
   void         SetAdvTrgThr1(unsigned int value) { SetRegMask(WD2_ADV_TRG_THR1_REG, WD2_ADV_TRG_THR1_MASK, WD2_ADV_TRG_THR1_OFS, value); };



   ////// ------ Control Register 146 [0x1248]: ADV_TRG_THR2 - Advanced Trigger Threshold 2 Register (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_THR2 - Advanced trigger threshold 2 register
   unsigned int GetAdvTrgThr2() { return BitExtractControl(WD2_ADV_TRG_THR2_REG, WD2_ADV_TRG_THR2_MASK, WD2_ADV_TRG_THR2_OFS); };
   void         SetAdvTrgThr2(unsigned int value) { SetRegMask(WD2_ADV_TRG_THR2_REG, WD2_ADV_TRG_THR2_MASK, WD2_ADV_TRG_THR2_OFS, value); };



   ////// ------ Control Register 147 [0x124C]: ADV_TRG_TX_CHK_WORD0 - Advanced Trigger Transmition Check Word 0 Register (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_TX_CHK_WORD0 - Advanced trigger transmition check word 0 register
   unsigned int GetAdvTrgTxChkWord0() { return BitExtractControl(WD2_ADV_TRG_TX_CHK_WORD0_REG, WD2_ADV_TRG_TX_CHK_WORD0_MASK, WD2_ADV_TRG_TX_CHK_WORD0_OFS); };
   void         SetAdvTrgTxChkWord0(unsigned int value) { SetRegMask(WD2_ADV_TRG_TX_CHK_WORD0_REG, WD2_ADV_TRG_TX_CHK_WORD0_MASK, WD2_ADV_TRG_TX_CHK_WORD0_OFS, value); };



   ////// ------ Control Register 148 [0x1250]: ADV_TRG_TX_CHK_WORD1 - Advanced Trigger Transmition Check Word 1 Register (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_TX_CHK_WORD1 - Advanced trigger transmition check word 1 register
   unsigned int GetAdvTrgTxChkWord1() { return BitExtractControl(WD2_ADV_TRG_TX_CHK_WORD1_REG, WD2_ADV_TRG_TX_CHK_WORD1_MASK, WD2_ADV_TRG_TX_CHK_WORD1_OFS); };
   void         SetAdvTrgTxChkWord1(unsigned int value) { SetRegMask(WD2_ADV_TRG_TX_CHK_WORD1_REG, WD2_ADV_TRG_TX_CHK_WORD1_MASK, WD2_ADV_TRG_TX_CHK_WORD1_OFS, value); };



   ////// ------ Control Register 149 [0x1254]: ADV_TRG_TDC_CH_MASK - Advanced Trigger TDC Channel Mask (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_TDC_CH_MASK - Advanced trigger TDC channel mask
   unsigned int GetAdvTrgTdcChMask() { return BitExtractControl(WD2_ADV_TRG_TDC_CH_MASK_REG, WD2_ADV_TRG_TDC_CH_MASK_MASK, WD2_ADV_TRG_TDC_CH_MASK_OFS); };
   void         SetAdvTrgTdcChMask(unsigned int value) { SetRegMask(WD2_ADV_TRG_TDC_CH_MASK_REG, WD2_ADV_TRG_TDC_CH_MASK_MASK, WD2_ADV_TRG_TDC_CH_MASK_OFS, value); };



   ////// ------ Control Register 150 [0x1258]: ADV_TRG_CFG12 - Advanced Trigger Configuration Register 12 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_CFG_12 - Advanced trigger configuration register 12
   unsigned int GetAdvTrgCfg12() { return BitExtractControl(WD2_ADV_TRG_CFG_12_REG, WD2_ADV_TRG_CFG_12_MASK, WD2_ADV_TRG_CFG_12_OFS); };
   void         SetAdvTrgCfg12(unsigned int value) { SetRegMask(WD2_ADV_TRG_CFG_12_REG, WD2_ADV_TRG_CFG_12_MASK, WD2_ADV_TRG_CFG_12_OFS, value); };



   ////// ------ Control Register 151 [0x125C]: ADV_TRG_CFG13 - Advanced Trigger Configuration Register 13 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_CFG_13 - Advanced trigger configuration register 13
   unsigned int GetAdvTrgCfg13() { return BitExtractControl(WD2_ADV_TRG_CFG_13_REG, WD2_ADV_TRG_CFG_13_MASK, WD2_ADV_TRG_CFG_13_OFS); };
   void         SetAdvTrgCfg13(unsigned int value) { SetRegMask(WD2_ADV_TRG_CFG_13_REG, WD2_ADV_TRG_CFG_13_MASK, WD2_ADV_TRG_CFG_13_OFS, value); };



   ////// ------ Control Register 152 [0x1260]: ADV_TRG_CFG14 - Advanced Trigger Configuration Register 14 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_CFG_14 - Advanced trigger configuration register 14
   unsigned int GetAdvTrgCfg14() { return BitExtractControl(WD2_ADV_TRG_CFG_14_REG, WD2_ADV_TRG_CFG_14_MASK, WD2_ADV_TRG_CFG_14_OFS); };
   void         SetAdvTrgCfg14(unsigned int value) { SetRegMask(WD2_ADV_TRG_CFG_14_REG, WD2_ADV_TRG_CFG_14_MASK, WD2_ADV_TRG_CFG_14_OFS, value); };



   ////// ------ Control Register 153 [0x1264]: ADV_TRG_CFG15 - Advanced Trigger Configuration Register 15 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_CFG_15 - Advanced trigger configuration register 15
   unsigned int GetAdvTrgCfg15() { return BitExtractControl(WD2_ADV_TRG_CFG_15_REG, WD2_ADV_TRG_CFG_15_MASK, WD2_ADV_TRG_CFG_15_OFS); };
   void         SetAdvTrgCfg15(unsigned int value) { SetRegMask(WD2_ADV_TRG_CFG_15_REG, WD2_ADV_TRG_CFG_15_MASK, WD2_ADV_TRG_CFG_15_OFS, value); };



   ////// ------ Control Register 154 [0x1268]: ADV_TRG_CFG16 - Advanced Trigger Configuration Register 16 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_CFG_16 - Advanced trigger configuration register 16
   unsigned int GetAdvTrgCfg16() { return BitExtractControl(WD2_ADV_TRG_CFG_16_REG, WD2_ADV_TRG_CFG_16_MASK, WD2_ADV_TRG_CFG_16_OFS); };
   void         SetAdvTrgCfg16(unsigned int value) { SetRegMask(WD2_ADV_TRG_CFG_16_REG, WD2_ADV_TRG_CFG_16_MASK, WD2_ADV_TRG_CFG_16_OFS, value); };



   ////// ------ Control Register 155 [0x126C]: ADV_TRG_CFG17 - Advanced Trigger Configuration Register 17 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_CFG_17 - Advanced trigger configuration register 17
   unsigned int GetAdvTrgCfg17() { return BitExtractControl(WD2_ADV_TRG_CFG_17_REG, WD2_ADV_TRG_CFG_17_MASK, WD2_ADV_TRG_CFG_17_OFS); };
   void         SetAdvTrgCfg17(unsigned int value) { SetRegMask(WD2_ADV_TRG_CFG_17_REG, WD2_ADV_TRG_CFG_17_MASK, WD2_ADV_TRG_CFG_17_OFS, value); };



   ////// ------ Control Register 156 [0x1270]: ADV_TRG_CFG18 - Advanced Trigger Configuration Register 18 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_CFG_18 - Advanced trigger configuration register 18
   unsigned int GetAdvTrgCfg18() { return BitExtractControl(WD2_ADV_TRG_CFG_18_REG, WD2_ADV_TRG_CFG_18_MASK, WD2_ADV_TRG_CFG_18_OFS); };
   void         SetAdvTrgCfg18(unsigned int value) { SetRegMask(WD2_ADV_TRG_CFG_18_REG, WD2_ADV_TRG_CFG_18_MASK, WD2_ADV_TRG_CFG_18_OFS, value); };



   ////// ------ Control Register 157 [0x1274]: ADV_TRG_CFG19 - Advanced Trigger Configuration Register 19 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_CFG_19 - Advanced trigger configuration register 19
   unsigned int GetAdvTrgCfg19() { return BitExtractControl(WD2_ADV_TRG_CFG_19_REG, WD2_ADV_TRG_CFG_19_MASK, WD2_ADV_TRG_CFG_19_OFS); };
   void         SetAdvTrgCfg19(unsigned int value) { SetRegMask(WD2_ADV_TRG_CFG_19_REG, WD2_ADV_TRG_CFG_19_MASK, WD2_ADV_TRG_CFG_19_OFS, value); };



   ////// ------ Control Register 158 [0x1278]: SET_TIME_LSB - Set System Time (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SET_TIME_LSB - LSBs of 64bit system time counter set value  (time is updated when MSBs are written)
   unsigned int GetSetTimeLsb() { return BitExtractControl(WD2_SET_TIME_LSB_REG, WD2_SET_TIME_LSB_MASK, WD2_SET_TIME_LSB_OFS); };
   void         SetSetTimeLsb(unsigned int value) { SetRegMask(WD2_SET_TIME_LSB_REG, WD2_SET_TIME_LSB_MASK, WD2_SET_TIME_LSB_OFS, value); };



   ////// ------ Control Register 159 [0x127C]: SET_TIME_MSB - Set System Time (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SET_TIME_MSB - MSBs of 64bit system time counter set value  (time is updated when MSBs are written)
   unsigned int GetSetTimeMsb() { return BitExtractControl(WD2_SET_TIME_MSB_REG, WD2_SET_TIME_MSB_MASK, WD2_SET_TIME_MSB_OFS); };
   void         SetSetTimeMsb(unsigned int value) { SetRegMask(WD2_SET_TIME_MSB_REG, WD2_SET_TIME_MSB_MASK, WD2_SET_TIME_MSB_OFS, value); };



   ////// ------ Control Register 160 [0x1280]: DBG_SIG_SEL - Debug Signal Select for MCX Connectors on HV Board (Default: 0x00000000) ------ //////

   // 0x000F0000: MCX_TX_SIG_SEL - Select for TX connector (see RX connector for mapping)
   unsigned int GetMcxTxSigSel() { return BitExtractControl(WD2_MCX_TX_SIG_SEL_REG, WD2_MCX_TX_SIG_SEL_MASK, WD2_MCX_TX_SIG_SEL_OFS); };
   void         SetMcxTxSigSel(unsigned int value) { SetRegMask(WD2_MCX_TX_SIG_SEL_REG, WD2_MCX_TX_SIG_SEL_MASK, WD2_MCX_TX_SIG_SEL_OFS, value); };

   // 0x0000000F: MCX_RX_SIG_SEL - Select for RX connector:
   // 0x0 = UART (communication to MicroBlaze)
   // 0x1 = Trigger (internal hardware trigger signal to DRS control FSM)
   // 0x2 = Soft Trigger (trigger signal from MicroBlaze)
   // 0x3 = External Trigger (OR connection of external trigger from MCX and Backplane)
   // 0x4 = Sync Signal from Backplane (direct, active high)
   // 0x5 = Sync Signal from Backplane (sampled, output to LMK, active low)
   // 0x6 = Sync Signal from Backplane (sampled, used for internal logic, active high)
   // 0x7 = Busy Local (active high)
   // 0x8 = Busy from Backplane (active high)
   // 0x9 = LMK Reference Clock (LMK input clock) 
   // 0xA = ADC Sampling Clock 
   // 0xB = Divided Data Clock (phase shifted)
   unsigned int GetMcxRxSigSel() { return BitExtractControl(WD2_MCX_RX_SIG_SEL_REG, WD2_MCX_RX_SIG_SEL_MASK, WD2_MCX_RX_SIG_SEL_OFS); };
   void         SetMcxRxSigSel(unsigned int value) { SetRegMask(WD2_MCX_RX_SIG_SEL_REG, WD2_MCX_RX_SIG_SEL_MASK, WD2_MCX_RX_SIG_SEL_OFS, value); };



   ////// ------ Control Register 161 [0x1284]: CRC32_REG_BANK - CRC32 Checksum of Register Bank Content (Default: None) ------ //////

   // 0xFFFFFFFF: CRC32_REG_BANK - Keep at the end of the register bank
   unsigned int GetCrc32RegBank() { return BitExtractControl(WD2_CRC32_REG_BANK_REG, WD2_CRC32_REG_BANK_MASK, WD2_CRC32_REG_BANK_OFS); };
   void         SetCrc32RegBank(unsigned int value) { SetRegMask(WD2_CRC32_REG_BANK_REG, WD2_CRC32_REG_BANK_MASK, WD2_CRC32_REG_BANK_OFS, value); };



   ////// ------ Status Register 0 [0x0000]: HW_VER - Hardware version information of the PCB (Default: 0xAC010213) ------ //////

   // 0xFF000000: BOARD_MAGIC - 0xAC, Magic number for DRS board identification
   unsigned int GetBoardMagic() { return BitExtractStatus(WD2_BOARD_MAGIC_REG, WD2_BOARD_MAGIC_MASK, WD2_BOARD_MAGIC_OFS); };

   // 0x00FF0000: VENDOR_ID - ID of the board vendor (0x01 for PSI)
   unsigned int GetVendorId() { return BitExtractStatus(WD2_VENDOR_ID_REG, WD2_VENDOR_ID_MASK, WD2_VENDOR_ID_OFS); };

   // 0x0000FF00: BOARD_TYPE - WaveDream Number (0x02 for WD2)
   unsigned int GetBoardType() { return BitExtractStatus(WD2_BOARD_TYPE_REG, WD2_BOARD_TYPE_MASK, WD2_BOARD_TYPE_OFS); };

   // 0x000000FC: BOARD_REVISION - Board revision (A=0x00, C=0x02, D=0x03, E=0x04)
   unsigned int GetBoardRevision() { return BitExtractStatus(WD2_BOARD_REVISION_REG, WD2_BOARD_REVISION_MASK, WD2_BOARD_REVISION_OFS); };

   // 0x00000003: BOARD_VARIANT - Version indicator pins reflecting the variant of the board (Y15,Y10)
   unsigned int GetBoardVariant() { return BitExtractStatus(WD2_BOARD_VARIANT_REG, WD2_BOARD_VARIANT_MASK, WD2_BOARD_VARIANT_OFS); };



   ////// ------ Status Register 1 [0x0004]: REG_LAYOUT_VER - Register map layout version information (Default: 0x00080008) ------ //////

   // 0xFFFF0000: REG_LAYOUT_COMP_LEVEL - Register map layout compatibility level
   unsigned int GetRegLayoutCompLevel() { return BitExtractStatus(WD2_REG_LAYOUT_COMP_LEVEL_REG, WD2_REG_LAYOUT_COMP_LEVEL_MASK, WD2_REG_LAYOUT_COMP_LEVEL_OFS); };

   // 0x0000FFFF: REG_LAYOUT_VERSION - Register map layout version
   unsigned int GetRegLayoutVersion() { return BitExtractStatus(WD2_REG_LAYOUT_VERSION_REG, WD2_REG_LAYOUT_VERSION_MASK, WD2_REG_LAYOUT_VERSION_OFS); };



   ////// ------ Status Register 2 [0x0008]: FW_BUILD_DATE - Date when the firmware was built (Default: 0x00000000) ------ //////

   // 0xFFFF0000: FW_BUILD_YEAR - Year of the firmware build
   unsigned int GetFwBuildYear() { return BitExtractStatus(WD2_FW_BUILD_YEAR_REG, WD2_FW_BUILD_YEAR_MASK, WD2_FW_BUILD_YEAR_OFS); };

   // 0x0000FF00: FW_BUILD_MONTH - Month of the firmware build
   unsigned int GetFwBuildMonth() { return BitExtractStatus(WD2_FW_BUILD_MONTH_REG, WD2_FW_BUILD_MONTH_MASK, WD2_FW_BUILD_MONTH_OFS); };

   // 0x000000FF: FW_BUILD_DAY - Day of the firmware build
   unsigned int GetFwBuildDay() { return BitExtractStatus(WD2_FW_BUILD_DAY_REG, WD2_FW_BUILD_DAY_MASK, WD2_FW_BUILD_DAY_OFS); };



   ////// ------ Status Register 3 [0x000C]: FW_BUILD_TIME - Time when the firmware was built and compatibility level (Default: 0x04000000) ------ //////

   // 0xFF000000: FW_COMPAT_LEVEL - Firmware compatibility level
   unsigned int GetFwCompatLevel() { return BitExtractStatus(WD2_FW_COMPAT_LEVEL_REG, WD2_FW_COMPAT_LEVEL_MASK, WD2_FW_COMPAT_LEVEL_OFS); };

   // 0x00FF0000: FW_BUILD_HOUR - Hour of the firmware build
   unsigned int GetFwBuildHour() { return BitExtractStatus(WD2_FW_BUILD_HOUR_REG, WD2_FW_BUILD_HOUR_MASK, WD2_FW_BUILD_HOUR_OFS); };

   // 0x0000FF00: FW_BUILD_MINUTE - Minute of the firmware build
   unsigned int GetFwBuildMinute() { return BitExtractStatus(WD2_FW_BUILD_MINUTE_REG, WD2_FW_BUILD_MINUTE_MASK, WD2_FW_BUILD_MINUTE_OFS); };

   // 0x000000FF: FW_BUILD_SECOND - Second of the firmware build
   unsigned int GetFwBuildSecond() { return BitExtractStatus(WD2_FW_BUILD_SECOND_REG, WD2_FW_BUILD_SECOND_MASK, WD2_FW_BUILD_SECOND_OFS); };



   ////// ------ Status Register 4 [0x0010]: SW_BUILD_DATE - Date when the software was built (Default: 0x00000000) ------ //////

   // 0xFFFF0000: SW_BUILD_YEAR - Year of the software build
   unsigned int GetSwBuildYear() { return BitExtractStatus(WD2_SW_BUILD_YEAR_REG, WD2_SW_BUILD_YEAR_MASK, WD2_SW_BUILD_YEAR_OFS); };

   // 0x0000FF00: SW_BUILD_MONTH - Month of the software build
   unsigned int GetSwBuildMonth() { return BitExtractStatus(WD2_SW_BUILD_MONTH_REG, WD2_SW_BUILD_MONTH_MASK, WD2_SW_BUILD_MONTH_OFS); };

   // 0x000000FF: SW_BUILD_DAY - Day of the software build
   unsigned int GetSwBuildDay() { return BitExtractStatus(WD2_SW_BUILD_DAY_REG, WD2_SW_BUILD_DAY_MASK, WD2_SW_BUILD_DAY_OFS); };



   ////// ------ Status Register 5 [0x0014]: SW_BUILD_TIME - Time when the software was built and compatibility level (Default: 0x00000000) ------ //////

   // 0x00FF0000: SW_BUILD_HOUR - Hour of the software build
   unsigned int GetSwBuildHour() { return BitExtractStatus(WD2_SW_BUILD_HOUR_REG, WD2_SW_BUILD_HOUR_MASK, WD2_SW_BUILD_HOUR_OFS); };

   // 0x0000FF00: SW_BUILD_MINUTE - Minute of the software build
   unsigned int GetSwBuildMinute() { return BitExtractStatus(WD2_SW_BUILD_MINUTE_REG, WD2_SW_BUILD_MINUTE_MASK, WD2_SW_BUILD_MINUTE_OFS); };

   // 0x000000FF: SW_BUILD_SECOND - Second of the software build
   unsigned int GetSwBuildSecond() { return BitExtractStatus(WD2_SW_BUILD_SECOND_REG, WD2_SW_BUILD_SECOND_MASK, WD2_SW_BUILD_SECOND_OFS); };



   ////// ------ Status Register 6 [0x0018]: FW_GIT_HASH_TAG - Hash tag of the firmware commit in the GIT repository (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: FW_GIT_HASH_TAG - Hash tag of the firmware commit in the GIT repository
   unsigned int GetFwGitHashTag() { return BitExtractStatus(WD2_FW_GIT_HASH_TAG_REG, WD2_FW_GIT_HASH_TAG_MASK, WD2_FW_GIT_HASH_TAG_OFS); };



   ////// ------ Status Register 7 [0x001C]: SW_GIT_HASH_TAG - Hash tag of the software commit in the GIT repository (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SW_GIT_HASH_TAG - Hash tag of the software commit in the GIT repository
   unsigned int GetSwGitHashTag() { return BitExtractStatus(WD2_SW_GIT_HASH_TAG_REG, WD2_SW_GIT_HASH_TAG_MASK, WD2_SW_GIT_HASH_TAG_OFS); };



   ////// ------ Status Register 8 [0x0020]: PROT_VER - Vesion of the WaveDream2 protocol (Default: 0x00000005) ------ //////

   // 0x000000FF: PROTOCOL_VERSION - Version of the WaveDream2 protocol
   unsigned int GetProtocolVersion() { return BitExtractStatus(WD2_PROTOCOL_VERSION_REG, WD2_PROTOCOL_VERSION_MASK, WD2_PROTOCOL_VERSION_OFS); };



   ////// ------ Status Register 9 [0x0024]: SN - Serial Number of the WD2 Board (Board ID) (Default: 0x00000000) ------ //////

   // 0x0000FFFF: SERIAL_NUMBER - Serial Number of the WD2 Board (Board ID)
   unsigned int GetSerialNumber() { return BitExtractStatus(WD2_SERIAL_NUMBER_REG, WD2_SERIAL_NUMBER_MASK, WD2_SERIAL_NUMBER_OFS); };



   ////// ------ Status Register 10 [0x0028]: STATUS - Status Register (Default: 0x00000000) ------ //////

   // 0xFFFF0000: TEMPERATURE - temperature in 0.0625 deg. C units
   unsigned int GetTemperature() { return BitExtractStatus(WD2_TEMPERATURE_REG, WD2_TEMPERATURE_MASK, WD2_TEMPERATURE_OFS); };

   // 0x00000200: FLASH_SEL - SPI Flash select from backplane (inverted = high active)
   unsigned int GetFlashSel() { return BitExtractStatus(WD2_FLASH_SEL_REG, WD2_FLASH_SEL_MASK, WD2_FLASH_SEL_OFS); };

   // 0x00000100: BOARD_SEL - Board select from backplane (inverted = high active)
   unsigned int GetBoardSel() { return BitExtractStatus(WD2_BOARD_SEL_REG, WD2_BOARD_SEL_MASK, WD2_BOARD_SEL_OFS); };

   // 0x00000080: DRS_CONFIG_DONE - DRS configuration done
   unsigned int GetDrsConfigDone() { return BitExtractStatus(WD2_DRS_CONFIG_DONE_REG, WD2_DRS_CONFIG_DONE_MASK, WD2_DRS_CONFIG_DONE_OFS); };

   // 0x00000040: SERIAL_BUSY - "1" during serial activity like FLASH read/write
   unsigned int GetSerialBusy() { return BitExtractStatus(WD2_SERIAL_BUSY_REG, WD2_SERIAL_BUSY_MASK, WD2_SERIAL_BUSY_OFS); };

   // 0x00000020: SYS_BUSY - Inverted busy signal from backplane (high active)
   unsigned int GetSysBusy() { return BitExtractStatus(WD2_SYS_BUSY_REG, WD2_SYS_BUSY_MASK, WD2_SYS_BUSY_OFS); };

   // 0x00000010: WDB_BUSY - "1" while domino wave running or readout in progress
   unsigned int GetWdbBusy() { return BitExtractStatus(WD2_WDB_BUSY_REG, WD2_WDB_BUSY_MASK, WD2_WDB_BUSY_OFS); };

   // 0x00000002: HV_BOARD_PLUGGED - HV board is currently plugged (1) or unplugged (0)
   unsigned int GetHvBoardPlugged() { return BitExtractStatus(WD2_HV_BOARD_PLUGGED_REG, WD2_HV_BOARD_PLUGGED_MASK, WD2_HV_BOARD_PLUGGED_OFS); };

   // 0x00000001: BACKPLANE_PLUGGED - Backplane is currently plugged (1) or unplugged (0)
   unsigned int GetBackplanePlugged() { return BitExtractStatus(WD2_BACKPLANE_PLUGGED_REG, WD2_BACKPLANE_PLUGGED_MASK, WD2_BACKPLANE_PLUGGED_OFS); };



   ////// ------ Status Register 11 [0x002C]: PLL_LOCK - Lock Status of PLLs (Default: 0x00000000) ------ //////

   // 0x00000100: SYS_DCM_LOCK - Lock of system DCM (FPGA internal)
   unsigned int GetSysDcmLock() { return BitExtractStatus(WD2_SYS_DCM_LOCK_REG, WD2_SYS_DCM_LOCK_MASK, WD2_SYS_DCM_LOCK_OFS); };

   // 0x00000080: DAQ_PLL_LOCK - Lock of DAQ PLL (FPGA internal)
   unsigned int GetDaqPllLock() { return BitExtractStatus(WD2_DAQ_PLL_LOCK_REG, WD2_DAQ_PLL_LOCK_MASK, WD2_DAQ_PLL_LOCK_OFS); };

   // 0x00000040: OSERDES_PLL_LOCK_DCB - Lock of PLL for OSERDES to DCB (FPGA internal)
   unsigned int GetOserdesPllLockDcb() { return BitExtractStatus(WD2_OSERDES_PLL_LOCK_DCB_REG, WD2_OSERDES_PLL_LOCK_DCB_MASK, WD2_OSERDES_PLL_LOCK_DCB_OFS); };

   // 0x00000020: OSERDES_PLL_LOCK_TCB - Lock of PLL for OSERDES to TCB (FPGA internal)
   unsigned int GetOserdesPllLockTcb() { return BitExtractStatus(WD2_OSERDES_PLL_LOCK_TCB_REG, WD2_OSERDES_PLL_LOCK_TCB_MASK, WD2_OSERDES_PLL_LOCK_TCB_OFS); };

   // 0x00000010: ISERDES_PLL_LOCK_0 - Lock of PLL for ISERDES from ADC 0 (A) (FPGA internal)
   unsigned int GetIserdesPllLock0() { return BitExtractStatus(WD2_ISERDES_PLL_LOCK_0_REG, WD2_ISERDES_PLL_LOCK_0_MASK, WD2_ISERDES_PLL_LOCK_0_OFS); };

   // 0x00000008: ISERDES_PLL_LOCK_1 - Lock of PLL for ISERDES from ADC 1 (B) (FPGA internal)
   unsigned int GetIserdesPllLock1() { return BitExtractStatus(WD2_ISERDES_PLL_LOCK_1_REG, WD2_ISERDES_PLL_LOCK_1_MASK, WD2_ISERDES_PLL_LOCK_1_OFS); };

   // 0x00000004: DRS_PLL_LOCK_0 - PLL lock signal of DRS Channel 0 (A) (external)
   unsigned int GetDrsPllLock0() { return BitExtractStatus(WD2_DRS_PLL_LOCK_0_REG, WD2_DRS_PLL_LOCK_0_MASK, WD2_DRS_PLL_LOCK_0_OFS); };

   // 0x00000002: DRS_PLL_LOCK_1 - PLL lock signal of DRS Channel 1 (B) (external)
   unsigned int GetDrsPllLock1() { return BitExtractStatus(WD2_DRS_PLL_LOCK_1_REG, WD2_DRS_PLL_LOCK_1_MASK, WD2_DRS_PLL_LOCK_1_OFS); };

   // 0x00000001: LMK_PLL_LOCK - PLL lock signal of LMK (external)
   unsigned int GetLmkPllLock() { return BitExtractStatus(WD2_LMK_PLL_LOCK_REG, WD2_LMK_PLL_LOCK_MASK, WD2_LMK_PLL_LOCK_OFS); };



   ////// ------ Status Register 12 [0x0030]: DRS_STOP_CELL - Position where sampling stopped at last trigger in DRS (Default: 0x00000000) ------ //////

   // 0x03FF0000: DRS_STOP_CELL_0 - Stop position of DRS Channel 0 (A)
   unsigned int GetDrsStopCell0() { return BitExtractStatus(WD2_DRS_STOP_CELL_0_REG, WD2_DRS_STOP_CELL_0_MASK, WD2_DRS_STOP_CELL_0_OFS); };

   // 0x000003FF: DRS_STOP_CELL_1 - Stop position of DRS Channel 1 (B)
   unsigned int GetDrsStopCell1() { return BitExtractStatus(WD2_DRS_STOP_CELL_1_REG, WD2_DRS_STOP_CELL_1_MASK, WD2_DRS_STOP_CELL_1_OFS); };



   ////// ------ Status Register 13 [0x0034]: DRS_STOP_WSR - Write shift register contents when sampling stopped in DRS (Default: 0x00000000) ------ //////

   // 0x0000FF00: DRS_STOP_WSR_0 - WSR contents after stop of DRS Channel 0 (A)
   unsigned int GetDrsStopWsr0() { return BitExtractStatus(WD2_DRS_STOP_WSR_0_REG, WD2_DRS_STOP_WSR_0_MASK, WD2_DRS_STOP_WSR_0_OFS); };

   // 0x000000FF: DRS_STOP_WSR_1 - WSR contents after stop of DRS Channel 1 (B)
   unsigned int GetDrsStopWsr1() { return BitExtractStatus(WD2_DRS_STOP_WSR_1_REG, WD2_DRS_STOP_WSR_1_MASK, WD2_DRS_STOP_WSR_1_OFS); };



   ////// ------ Status Register 14 [0x0038]: DRS_SAMPLE_FREQ - DRS Sampling frequency (Default: 0x00000000) ------ //////

   // 0x00FFFFFF: DRS_SAMPLE_FREQ - DRS Sampling frequency in kHz
   unsigned int GetDrsSampleFreq() { return BitExtractStatus(WD2_DRS_SAMPLE_FREQ_REG, WD2_DRS_SAMPLE_FREQ_MASK, WD2_DRS_SAMPLE_FREQ_OFS); };



   ////// ------ Status Register 15 [0x003C]: ADC_SAMPLE_FREQ - ADC Sampling Frequency in MHz (Default: 0x00013880) ------ //////

   // 0x00FFFFFF: ADC_SAMPLE_FREQ - ADC Sampling Frequency in kHz
   unsigned int GetAdcSampleFreq() { return BitExtractStatus(WD2_ADC_SAMPLE_FREQ_REG, WD2_ADC_SAMPLE_FREQ_MASK, WD2_ADC_SAMPLE_FREQ_OFS); };



   ////// ------ Status Register 16 [0x0040]: TDC_SAMPLE_FREQ - TDC Sampling Frequency in MHz (Default: 0x0009C400) ------ //////

   // 0x00FFFFFF: TDC_SAMPLE_FREQ - TDC Sampling Frequency in kHz
   unsigned int GetTdcSampleFreq() { return BitExtractStatus(WD2_TDC_SAMPLE_FREQ_REG, WD2_TDC_SAMPLE_FREQ_MASK, WD2_TDC_SAMPLE_FREQ_OFS); };



   ////// ------ Status Register 17 [0x0044]: ADC_INFO - Chip ID and Grade of the ADCs (Default: 0x00000000) ------ //////

   // 0xFF000000: ADC_0_CHIP_ID - Chip ID of ADC 0 (A) (0x93 for AD9637)
   unsigned int GetAdc0ChipId() { return BitExtractStatus(WD2_ADC_0_CHIP_ID_REG, WD2_ADC_0_CHIP_ID_MASK, WD2_ADC_0_CHIP_ID_OFS); };

   // 0x00700000: ADC_0_SPEED - Speed Grade of ADC 0 (A) (0=40MS, 1=80MS)
   unsigned int GetAdc0Speed() { return BitExtractStatus(WD2_ADC_0_SPEED_REG, WD2_ADC_0_SPEED_MASK, WD2_ADC_0_SPEED_OFS); };

   // 0x0000FF00: ADC_1_CHIP_ID - Chip ID of ADC 1 (B) (0x93 for AD9637)
   unsigned int GetAdc1ChipId() { return BitExtractStatus(WD2_ADC_1_CHIP_ID_REG, WD2_ADC_1_CHIP_ID_MASK, WD2_ADC_1_CHIP_ID_OFS); };

   // 0x00000070: ADC_1_SPEED - Speed Grade of ADC 1 (B) (0=40MS, 1=80MS)
   unsigned int GetAdc1Speed() { return BitExtractStatus(WD2_ADC_1_SPEED_REG, WD2_ADC_1_SPEED_MASK, WD2_ADC_1_SPEED_OFS); };



   ////// ------ Status Register 18 [0x0048]: HV_VER - HV Board Version (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_VER - HV board version (16bit Voltage in V, 16bit Current in mA)
   unsigned int GetHvVer() { return BitExtractStatus(WD2_HV_VER_REG, WD2_HV_VER_MASK, WD2_HV_VER_OFS); };



   ////// ------ Status Register 19 [0x004C]: HV_I_MEAS_0 - Measured actual current of the HV supply on channel 0 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_I_MEAS_0 - Float value (i_meas)
   unsigned int GetHvIMeas0() { return BitExtractStatus(WD2_HV_I_MEAS_0_REG, WD2_HV_I_MEAS_0_MASK, WD2_HV_I_MEAS_0_OFS); };



   ////// ------ Status Register 20 [0x0050]: HV_I_MEAS_1 - Measured actual current of the HV supply on channel 1 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_I_MEAS_1 - Float value (i_meas)
   unsigned int GetHvIMeas1() { return BitExtractStatus(WD2_HV_I_MEAS_1_REG, WD2_HV_I_MEAS_1_MASK, WD2_HV_I_MEAS_1_OFS); };



   ////// ------ Status Register 21 [0x0054]: HV_I_MEAS_2 - Measured actual current of the HV supply on channel 2 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_I_MEAS_2 - Float value (i_meas)
   unsigned int GetHvIMeas2() { return BitExtractStatus(WD2_HV_I_MEAS_2_REG, WD2_HV_I_MEAS_2_MASK, WD2_HV_I_MEAS_2_OFS); };



   ////// ------ Status Register 22 [0x0058]: HV_I_MEAS_3 - Measured actual current of the HV supply on channel 3 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_I_MEAS_3 - Float value (i_meas)
   unsigned int GetHvIMeas3() { return BitExtractStatus(WD2_HV_I_MEAS_3_REG, WD2_HV_I_MEAS_3_MASK, WD2_HV_I_MEAS_3_OFS); };



   ////// ------ Status Register 23 [0x005C]: HV_I_MEAS_4 - Measured actual current of the HV supply on channel 4 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_I_MEAS_4 - Float value (i_meas)
   unsigned int GetHvIMeas4() { return BitExtractStatus(WD2_HV_I_MEAS_4_REG, WD2_HV_I_MEAS_4_MASK, WD2_HV_I_MEAS_4_OFS); };



   ////// ------ Status Register 24 [0x0060]: HV_I_MEAS_5 - Measured actual current of the HV supply on channel 5 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_I_MEAS_5 - Float value (i_meas)
   unsigned int GetHvIMeas5() { return BitExtractStatus(WD2_HV_I_MEAS_5_REG, WD2_HV_I_MEAS_5_MASK, WD2_HV_I_MEAS_5_OFS); };



   ////// ------ Status Register 25 [0x0064]: HV_I_MEAS_6 - Measured actual current of the HV supply on channel 6 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_I_MEAS_6 - Float value (i_meas)
   unsigned int GetHvIMeas6() { return BitExtractStatus(WD2_HV_I_MEAS_6_REG, WD2_HV_I_MEAS_6_MASK, WD2_HV_I_MEAS_6_OFS); };



   ////// ------ Status Register 26 [0x0068]: HV_I_MEAS_7 - Measured actual current of the HV supply on channel 7 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_I_MEAS_7 - Float value (i_meas)
   unsigned int GetHvIMeas7() { return BitExtractStatus(WD2_HV_I_MEAS_7_REG, WD2_HV_I_MEAS_7_MASK, WD2_HV_I_MEAS_7_OFS); };



   ////// ------ Status Register 27 [0x006C]: HV_I_MEAS_8 - Measured actual current of the HV supply on channel 8 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_I_MEAS_8 - Float value (i_meas)
   unsigned int GetHvIMeas8() { return BitExtractStatus(WD2_HV_I_MEAS_8_REG, WD2_HV_I_MEAS_8_MASK, WD2_HV_I_MEAS_8_OFS); };



   ////// ------ Status Register 28 [0x0070]: HV_I_MEAS_9 - Measured actual current of the HV supply on channel 9 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_I_MEAS_9 - Float value (i_meas)
   unsigned int GetHvIMeas9() { return BitExtractStatus(WD2_HV_I_MEAS_9_REG, WD2_HV_I_MEAS_9_MASK, WD2_HV_I_MEAS_9_OFS); };



   ////// ------ Status Register 29 [0x0074]: HV_I_MEAS_10 - Measured actual current of the HV supply on channel 10 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_I_MEAS_10 - Float value (i_meas)
   unsigned int GetHvIMeas10() { return BitExtractStatus(WD2_HV_I_MEAS_10_REG, WD2_HV_I_MEAS_10_MASK, WD2_HV_I_MEAS_10_OFS); };



   ////// ------ Status Register 30 [0x0078]: HV_I_MEAS_11 - Measured actual current of the HV supply on channel 11 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_I_MEAS_11 - Float value (i_meas)
   unsigned int GetHvIMeas11() { return BitExtractStatus(WD2_HV_I_MEAS_11_REG, WD2_HV_I_MEAS_11_MASK, WD2_HV_I_MEAS_11_OFS); };



   ////// ------ Status Register 31 [0x007C]: HV_I_MEAS_12 - Measured actual current of the HV supply on channel 12 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_I_MEAS_12 - Float value (i_meas)
   unsigned int GetHvIMeas12() { return BitExtractStatus(WD2_HV_I_MEAS_12_REG, WD2_HV_I_MEAS_12_MASK, WD2_HV_I_MEAS_12_OFS); };



   ////// ------ Status Register 32 [0x0080]: HV_I_MEAS_13 - Measured actual current of the HV supply on channel 13 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_I_MEAS_13 - Float value (i_meas)
   unsigned int GetHvIMeas13() { return BitExtractStatus(WD2_HV_I_MEAS_13_REG, WD2_HV_I_MEAS_13_MASK, WD2_HV_I_MEAS_13_OFS); };



   ////// ------ Status Register 33 [0x0084]: HV_I_MEAS_14 - Measured actual current of the HV supply on channel 14 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_I_MEAS_14 - Float value (i_meas)
   unsigned int GetHvIMeas14() { return BitExtractStatus(WD2_HV_I_MEAS_14_REG, WD2_HV_I_MEAS_14_MASK, WD2_HV_I_MEAS_14_OFS); };



   ////// ------ Status Register 34 [0x0088]: HV_I_MEAS_15 - Measured actual current of the HV supply on channel 15 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_I_MEAS_15 - Float value (i_meas)
   unsigned int GetHvIMeas15() { return BitExtractStatus(WD2_HV_I_MEAS_15_REG, WD2_HV_I_MEAS_15_MASK, WD2_HV_I_MEAS_15_OFS); };



   ////// ------ Status Register 35 [0x008C]: HV_U_BASE_MEAS - Measured actual HV base voltage (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_U_BASE_MEAS - Float value (ub_meas)
   unsigned int GetHvUBaseMeas() { return BitExtractStatus(WD2_HV_U_BASE_MEAS_REG, WD2_HV_U_BASE_MEAS_MASK, WD2_HV_U_BASE_MEAS_OFS); };



   ////// ------ Status Register 36 [0x0090]: HV_TEMP_0 - Measured actual temperature of sensor 0 connected to the HV board (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_TEMP_0 - Float value (temp)
   unsigned int GetHvTemp0() { return BitExtractStatus(WD2_HV_TEMP_0_REG, WD2_HV_TEMP_0_MASK, WD2_HV_TEMP_0_OFS); };



   ////// ------ Status Register 37 [0x0094]: HV_TEMP_1 - Measured actual temperature of sensor 1 connected to the HV board (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_TEMP_1 - Float value (temp)
   unsigned int GetHvTemp1() { return BitExtractStatus(WD2_HV_TEMP_1_REG, WD2_HV_TEMP_1_MASK, WD2_HV_TEMP_1_OFS); };



   ////// ------ Status Register 38 [0x0098]: HV_TEMP_2 - Measured actual temperature of sensor 2 connected to the HV board (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_TEMP_2 - Float value (temp)
   unsigned int GetHvTemp2() { return BitExtractStatus(WD2_HV_TEMP_2_REG, WD2_HV_TEMP_2_MASK, WD2_HV_TEMP_2_OFS); };



   ////// ------ Status Register 39 [0x009C]: HV_TEMP_3 - Measured actual temperature of sensor 3 connected to the HV board (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: HV_TEMP_3 - Float value (temp)
   unsigned int GetHvTemp3() { return BitExtractStatus(WD2_HV_TEMP_3_REG, WD2_HV_TEMP_3_MASK, WD2_HV_TEMP_3_OFS); };



   ////// ------ Status Register 40 [0x00A0]: SCALER_0 - Scaler for input #0 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SCALER_0 - Count rate value of channel 0 (MSBs are latched upon read of LSB register)
   unsigned int GetScaler0() { return BitExtractStatus(WD2_SCALER_0_REG, WD2_SCALER_0_MASK, WD2_SCALER_0_OFS); };



   ////// ------ Status Register 41 [0x00A4]: SCALER_1 - Scaler for input #1 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SCALER_1 - Count rate value of channel 1 (MSBs are latched upon read of LSB register)
   unsigned int GetScaler1() { return BitExtractStatus(WD2_SCALER_1_REG, WD2_SCALER_1_MASK, WD2_SCALER_1_OFS); };



   ////// ------ Status Register 42 [0x00A8]: SCALER_2 - Scaler for input #2 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SCALER_2 - Count rate value of channel 2 (MSBs are latched upon read of LSB register)
   unsigned int GetScaler2() { return BitExtractStatus(WD2_SCALER_2_REG, WD2_SCALER_2_MASK, WD2_SCALER_2_OFS); };



   ////// ------ Status Register 43 [0x00AC]: SCALER_3 - Scaler for input #3 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SCALER_3 - Count rate value of channel 3 (MSBs are latched upon read of LSB register)
   unsigned int GetScaler3() { return BitExtractStatus(WD2_SCALER_3_REG, WD2_SCALER_3_MASK, WD2_SCALER_3_OFS); };



   ////// ------ Status Register 44 [0x00B0]: SCALER_4 - Scaler for input #4 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SCALER_4 - Count rate value of channel 4 (MSBs are latched upon read of LSB register)
   unsigned int GetScaler4() { return BitExtractStatus(WD2_SCALER_4_REG, WD2_SCALER_4_MASK, WD2_SCALER_4_OFS); };



   ////// ------ Status Register 45 [0x00B4]: SCALER_5 - Scaler for input #5 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SCALER_5 - Count rate value of channel 5 (MSBs are latched upon read of LSB register)
   unsigned int GetScaler5() { return BitExtractStatus(WD2_SCALER_5_REG, WD2_SCALER_5_MASK, WD2_SCALER_5_OFS); };



   ////// ------ Status Register 46 [0x00B8]: SCALER_6 - Scaler for input #6 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SCALER_6 - Count rate value of channel 6 (MSBs are latched upon read of LSB register)
   unsigned int GetScaler6() { return BitExtractStatus(WD2_SCALER_6_REG, WD2_SCALER_6_MASK, WD2_SCALER_6_OFS); };



   ////// ------ Status Register 47 [0x00BC]: SCALER_7 - Scaler for input #7 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SCALER_7 - Count rate value of channel 7 (MSBs are latched upon read of LSB register)
   unsigned int GetScaler7() { return BitExtractStatus(WD2_SCALER_7_REG, WD2_SCALER_7_MASK, WD2_SCALER_7_OFS); };



   ////// ------ Status Register 48 [0x00C0]: SCALER_8 - Scaler for input #8 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SCALER_8 - Count rate value of channel 8 (MSBs are latched upon read of LSB register)
   unsigned int GetScaler8() { return BitExtractStatus(WD2_SCALER_8_REG, WD2_SCALER_8_MASK, WD2_SCALER_8_OFS); };



   ////// ------ Status Register 49 [0x00C4]: SCALER_9 - Scaler for input #9 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SCALER_9 - Count rate value of channel 9 (MSBs are latched upon read of LSB register)
   unsigned int GetScaler9() { return BitExtractStatus(WD2_SCALER_9_REG, WD2_SCALER_9_MASK, WD2_SCALER_9_OFS); };



   ////// ------ Status Register 50 [0x00C8]: SCALER_10 - Scaler for input #10 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SCALER_10 - Count rate value of channel 10 (MSBs are latched upon read of LSB register)
   unsigned int GetScaler10() { return BitExtractStatus(WD2_SCALER_10_REG, WD2_SCALER_10_MASK, WD2_SCALER_10_OFS); };



   ////// ------ Status Register 51 [0x00CC]: SCALER_11 - Scaler for input #11 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SCALER_11 - Count rate value of channel 11 (MSBs are latched upon read of LSB register)
   unsigned int GetScaler11() { return BitExtractStatus(WD2_SCALER_11_REG, WD2_SCALER_11_MASK, WD2_SCALER_11_OFS); };



   ////// ------ Status Register 52 [0x00D0]: SCALER_12 - Scaler for input #12 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SCALER_12 - Count rate value of channel 12 (MSBs are latched upon read of LSB register)
   unsigned int GetScaler12() { return BitExtractStatus(WD2_SCALER_12_REG, WD2_SCALER_12_MASK, WD2_SCALER_12_OFS); };



   ////// ------ Status Register 53 [0x00D4]: SCALER_13 - Scaler for input #13 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SCALER_13 - Count rate value of channel 13 (MSBs are latched upon read of LSB register)
   unsigned int GetScaler13() { return BitExtractStatus(WD2_SCALER_13_REG, WD2_SCALER_13_MASK, WD2_SCALER_13_OFS); };



   ////// ------ Status Register 54 [0x00D8]: SCALER_14 - Scaler for input #14 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SCALER_14 - Count rate value of channel 14 (MSBs are latched upon read of LSB register)
   unsigned int GetScaler14() { return BitExtractStatus(WD2_SCALER_14_REG, WD2_SCALER_14_MASK, WD2_SCALER_14_OFS); };



   ////// ------ Status Register 55 [0x00DC]: SCALER_15 - Scaler for input #15 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SCALER_15 - Count rate value of channel 15 (MSBs are latched upon read of LSB register)
   unsigned int GetScaler15() { return BitExtractStatus(WD2_SCALER_15_REG, WD2_SCALER_15_MASK, WD2_SCALER_15_OFS); };



   ////// ------ Status Register 56 [0x00E0]: SCALER_TRG - Scaler for trigger (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SCALER_TRG - Count rate for trigger signal
   unsigned int GetScalerTrg() { return BitExtractStatus(WD2_SCALER_TRG_REG, WD2_SCALER_TRG_MASK, WD2_SCALER_TRG_OFS); };



   ////// ------ Status Register 57 [0x00E4]: SCALER_EXT_CLK - Scaler for ext. clock input (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SCALER_EXT_CLK - Count rate for external clock input (GLOB_CLK)
   unsigned int GetScalerExtClk() { return BitExtractStatus(WD2_SCALER_EXT_CLK_REG, WD2_SCALER_EXT_CLK_MASK, WD2_SCALER_EXT_CLK_OFS); };



   ////// ------ Status Register 58 [0x00E8]: SCALER_TIME_STAMP_LSB - Time Stamp for Scaler Values (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SCALER_TIME_STAMP_LSB - LSBs of 64bit scaler time stamp (MSBs are latched upon read of LSB register)
   unsigned int GetScalerTimeStampLsb() { return BitExtractStatus(WD2_SCALER_TIME_STAMP_LSB_REG, WD2_SCALER_TIME_STAMP_LSB_MASK, WD2_SCALER_TIME_STAMP_LSB_OFS); };



   ////// ------ Status Register 59 [0x00EC]: SCALER_TIME_STAMP_MSB - Time Stamp for Scaler Values (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: SCALER_TIME_STAMP_MSB - MSBs of 64bit scaler time stamp (latched upon read of LSB register)
   unsigned int GetScalerTimeStampMsb() { return BitExtractStatus(WD2_SCALER_TIME_STAMP_MSB_REG, WD2_SCALER_TIME_STAMP_MSB_MASK, WD2_SCALER_TIME_STAMP_MSB_OFS); };



   ////// ------ Status Register 60 [0x00F0]: TIME_LSB - Current System Time (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: TIME_LSB - LSBs of 64bit system time counter (MSBs are latched upon read of LSB register)
   unsigned int GetTimeLsb() { return BitExtractStatus(WD2_TIME_LSB_REG, WD2_TIME_LSB_MASK, WD2_TIME_LSB_OFS); };



   ////// ------ Status Register 61 [0x00F4]: TIME_MSB - Current System Time (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: TIME_MSB - MSBs of 64bit system time counter (latched upon read of LSB register)
   unsigned int GetTimeMsb() { return BitExtractStatus(WD2_TIME_MSB_REG, WD2_TIME_MSB_MASK, WD2_TIME_MSB_OFS); };



   ////// ------ Status Register 62 [0x00F8]: COMP_CH_STAT - Comparator channel status (Default: 0x00000000) ------ //////

   // 0x0000FFFF: COMP_CH_STAT - Status of the comparator inputs
   unsigned int GetCompChStat() { return BitExtractStatus(WD2_COMP_CH_STAT_REG, WD2_COMP_CH_STAT_MASK, WD2_COMP_CH_STAT_OFS); };



   ////// ------ Status Register 63 [0x00FC]: EVENT_TX_RATE - Event Transmission Rate (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: EVENT_TX_RATE - Number of events transmitted per second
   unsigned int GetEventTxRate() { return BitExtractStatus(WD2_EVENT_TX_RATE_REG, WD2_EVENT_TX_RATE_MASK, WD2_EVENT_TX_RATE_OFS); };



   ////// ------ Status Register 64 [0x0100]: EVENT_NR - Number of latest event (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: EVENT_NUMBER - Number of latest event
   unsigned int GetEventNumber() { return BitExtractStatus(WD2_EVENT_NUMBER_REG, WD2_EVENT_NUMBER_MASK, WD2_EVENT_NUMBER_OFS); };



   ////// ------ Status Register 65 [0x0104]: TRB_INFO_STAT - Trigger Information via Serial Trigger Bus Status (Default: 0x00000000) ------ //////

   // 0x80000000: TRB_FLAG_NEW - Flag signalling that the current trigger information belongs to the latest trigger received
   unsigned int GetTrbFlagNew() { return BitExtractStatus(WD2_TRB_FLAG_NEW_REG, WD2_TRB_FLAG_NEW_MASK, WD2_TRB_FLAG_NEW_OFS); };

   // 0x40000000: TRB_FLAG_PARITY_ERROR - Parity error flag of the current trigger information
   unsigned int GetTrbFlagParityError() { return BitExtractStatus(WD2_TRB_FLAG_PARITY_ERROR_REG, WD2_TRB_FLAG_PARITY_ERROR_MASK, WD2_TRB_FLAG_PARITY_ERROR_OFS); };

   // 0x0000FFFF: TRB_PARITY_ERROR_COUNT - Parity error count of the serial transmission
   unsigned int GetTrbParityErrorCount() { return BitExtractStatus(WD2_TRB_PARITY_ERROR_COUNT_REG, WD2_TRB_PARITY_ERROR_COUNT_MASK, WD2_TRB_PARITY_ERROR_COUNT_OFS); };



   ////// ------ Status Register 66 [0x0108]: TRB_INFO_LSB - Trigger Information via Serial Trigger Bus LSBs (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: TRB_INFO_LSB - Trigger information LSBs
   unsigned int GetTrbInfoLsb() { return BitExtractStatus(WD2_TRB_INFO_LSB_REG, WD2_TRB_INFO_LSB_MASK, WD2_TRB_INFO_LSB_OFS); };



   ////// ------ Status Register 67 [0x010C]: TRB_INFO_MSB - Trigger Information via Serial Trigger Bus MSBs (Default: 0x00000000) ------ //////

   // 0x0000FFFF: TRB_INFO_MSB - Trigger information MSBs
   unsigned int GetTrbInfoMsb() { return BitExtractStatus(WD2_TRB_INFO_MSB_REG, WD2_TRB_INFO_MSB_MASK, WD2_TRB_INFO_MSB_OFS); };



   ////// ------ Status Register 68 [0x0110]: ADV_TRG_TRIG_CELL - Advanced Trigger Cell Register (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_TRIG_CELL - Advanced trigger cell register
   unsigned int GetAdvTrgTrigCell() { return BitExtractStatus(WD2_ADV_TRG_TRIG_CELL_REG, WD2_ADV_TRG_TRIG_CELL_MASK, WD2_ADV_TRG_TRIG_CELL_OFS); };



   ////// ------ Status Register 69 [0x0114]: ADV_TRG_STAT1 - Advanced Trigger Status Register 1 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_STAT_1 - Advanced trigger status register 1
   unsigned int GetAdvTrgStat1() { return BitExtractStatus(WD2_ADV_TRG_STAT_1_REG, WD2_ADV_TRG_STAT_1_MASK, WD2_ADV_TRG_STAT_1_OFS); };



   ////// ------ Status Register 70 [0x0118]: ADV_TRG_STAT2 - Advanced Trigger Status Register 2 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_STAT_2 - Advanced trigger status register 2
   unsigned int GetAdvTrgStat2() { return BitExtractStatus(WD2_ADV_TRG_STAT_2_REG, WD2_ADV_TRG_STAT_2_MASK, WD2_ADV_TRG_STAT_2_OFS); };



   ////// ------ Status Register 71 [0x011C]: ADV_TRG_STAT3 - Advanced Trigger Status Register 3 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_STAT_3 - Advanced trigger status register 3
   unsigned int GetAdvTrgStat3() { return BitExtractStatus(WD2_ADV_TRG_STAT_3_REG, WD2_ADV_TRG_STAT_3_MASK, WD2_ADV_TRG_STAT_3_OFS); };



   ////// ------ Status Register 72 [0x0120]: ADV_TRG_STAT4 - Advanced Trigger Status Register 4 (Default: 0x00000000) ------ //////

   // 0xFFFFFFFF: ADV_TRG_STAT_4 - Advanced trigger status register 4
   unsigned int GetAdvTrgStat4() { return BitExtractStatus(WD2_ADV_TRG_STAT_4_REG, WD2_ADV_TRG_STAT_4_MASK, WD2_ADV_TRG_STAT_4_OFS); };



   ////// ------ Status Register 73 [0x0124]: MAX_DRS_ADC_PKT_SAMPLES - Maximum DRS/ADC samples per Packet (Default: 0x00000000) ------ //////

   // 0x0000FFFF: MAX_DRS_ADC_PKT_SAMPLES - Maximum number of DRS/ADC samples per packet
   unsigned int GetMaxDrsAdcPktSamples() { return BitExtractStatus(WD2_MAX_DRS_ADC_PKT_SAMPLES_REG, WD2_MAX_DRS_ADC_PKT_SAMPLES_MASK, WD2_MAX_DRS_ADC_PKT_SAMPLES_OFS); };



   ////// ------ Status Register 74 [0x0128]: MAX_TDC_PKT_SAMPLES - Maximum TDC samples per Packet (Default: 0x00000000) ------ //////

   // 0x0003FFFF: MAX_TDC_PKT_SAMPLES - Maximum number of TDC samples per packet
   unsigned int GetMaxTdcPktSamples() { return BitExtractStatus(WD2_MAX_TDC_PKT_SAMPLES_REG, WD2_MAX_TDC_PKT_SAMPLES_MASK, WD2_MAX_TDC_PKT_SAMPLES_OFS); };



   ////// ------ Status Register 75 [0x012C]: MAX_TRG_PKT_SAMPLES - Maximum advanced trigger output samples per Packet (Default: 0x00000000) ------ //////

   // 0x0000FFFF: MAX_TRG_PKT_SAMPLES - Maximum number of advanced trigger output samples per packet
   unsigned int GetMaxTrgPktSamples() { return BitExtractStatus(WD2_MAX_TRG_PKT_SAMPLES_REG, WD2_MAX_TRG_PKT_SAMPLES_MASK, WD2_MAX_TRG_PKT_SAMPLES_OFS); };



   ////// ------ Status Register 76 [0x0130]: MAX_SCL_PKT_SAMPLES - Maximum scaler values per Packet (Default: 0x00000000) ------ //////

   // 0x0000FFFF: MAX_SCL_PKT_SAMPLES - Maximum number of scaler values per packet
   unsigned int GetMaxSclPktSamples() { return BitExtractStatus(WD2_MAX_SCL_PKT_SAMPLES_REG, WD2_MAX_SCL_PKT_SAMPLES_MASK, WD2_MAX_SCL_PKT_SAMPLES_OFS); };



   ////// ------ Status Register 77 [0x0134]: CLK_CTRL_MOD_FLAG - Set if WD2 configuration registers are modified (Default: 0x00000000) ------ //////

   // 0x00000008: ADC_RST_MOD - ADC reset modified flag
   unsigned int GetAdcRstMod() { return BitExtractStatus(WD2_ADC_RST_MOD_REG, WD2_ADC_RST_MOD_MASK, WD2_ADC_RST_MOD_OFS); };

   // 0x00000004: CLK_SEL_AND_DRS_CLK_DIV_MOD - DAQ clock select and DRS clock divider modified flags
   unsigned int GetClkSelAndDrsClkDivMod() { return BitExtractStatus(WD2_CLK_SEL_AND_DRS_CLK_DIV_MOD_REG, WD2_CLK_SEL_AND_DRS_CLK_DIV_MOD_MASK, WD2_CLK_SEL_AND_DRS_CLK_DIV_MOD_OFS); };

   // 0x00000002: EXT_CLK_FREQ_MOD - External clock frequency modified flags
   unsigned int GetExtClkFreqMod() { return BitExtractStatus(WD2_EXT_CLK_FREQ_MOD_REG, WD2_EXT_CLK_FREQ_MOD_MASK, WD2_EXT_CLK_FREQ_MOD_OFS); };

   // 0x00000001: LOCAL_CLK_FREQ_MOD - Local clock frequency modified flags
   unsigned int GetLocalClkFreqMod() { return BitExtractStatus(WD2_LOCAL_CLK_FREQ_MOD_REG, WD2_LOCAL_CLK_FREQ_MOD_MASK, WD2_LOCAL_CLK_FREQ_MOD_OFS); };



   ////// ------ Status Register 78 [0x0138]: DRS_MOD_FLAG - Set if DRS configuration registers are modified (Default: 0x00000000) ------ //////

   // 0x00000004: DRS_CTRL_MOD - DRS control bits modified flags
   unsigned int GetDrsCtrlMod() { return BitExtractStatus(WD2_DRS_CTRL_MOD_REG, WD2_DRS_CTRL_MOD_MASK, WD2_DRS_CTRL_MOD_OFS); };

   // 0x00000002: DRS_WSR_MOD - DRS write shift register modified flags
   unsigned int GetDrsWsrMod() { return BitExtractStatus(WD2_DRS_WSR_MOD_REG, WD2_DRS_WSR_MOD_MASK, WD2_DRS_WSR_MOD_OFS); };

   // 0x00000001: DRS_WCR_MOD - DRS write control register modified flags
   unsigned int GetDrsWcrMod() { return BitExtractStatus(WD2_DRS_WCR_MOD_REG, WD2_DRS_WCR_MOD_MASK, WD2_DRS_WCR_MOD_OFS); };



   ////// ------ Status Register 79 [0x013C]: COM_PLD_SIZE_MOD_FLAG - Set if maximum packet payload size register is modified (Default: 0x00000000) ------ //////

   // 0x0000000F: COM_PLD_SIZE_MOD - Maximum packet payload size modified flag
   unsigned int GetComPldSizeMod() { return BitExtractStatus(WD2_COM_PLD_SIZE_MOD_REG, WD2_COM_PLD_SIZE_MOD_MASK, WD2_COM_PLD_SIZE_MOD_OFS); };



   ////// ------ Status Register 80 [0x0140]: ADC_SAMPLE_DIV_MOD_FLAG - Set if ADC downsampling divider register is modified (Default: 0x00000000) ------ //////

   // 0x0000000F: ADC_SAMPLE_DIV_MOD - ADC downsampling divider modified flags
   unsigned int GetAdcSampleDivMod() { return BitExtractStatus(WD2_ADC_SAMPLE_DIV_MOD_REG, WD2_ADC_SAMPLE_DIV_MOD_MASK, WD2_ADC_SAMPLE_DIV_MOD_OFS); };



   ////// ------ Status Register 81 [0x0144]: DAC_0_1_MOD_FLAG - Set if DAC 0 and 1 configuration registers are modified (Default: 0x00000000) ------ //////

   // 0xC0000000: DAC0_A_MOD - DAC channel a modified flags
   unsigned int GetDac0AMod() { return BitExtractStatus(WD2_DAC0_A_MOD_REG, WD2_DAC0_A_MOD_MASK, WD2_DAC0_A_MOD_OFS); };

   // 0x30000000: DAC0_B_MOD - DAC channel b modified flags
   unsigned int GetDac0BMod() { return BitExtractStatus(WD2_DAC0_B_MOD_REG, WD2_DAC0_B_MOD_MASK, WD2_DAC0_B_MOD_OFS); };

   // 0x0C000000: DAC0_C_MOD - DAC channel c modified flags
   unsigned int GetDac0CMod() { return BitExtractStatus(WD2_DAC0_C_MOD_REG, WD2_DAC0_C_MOD_MASK, WD2_DAC0_C_MOD_OFS); };

   // 0x03000000: DAC0_D_MOD - DAC channel d modified flags
   unsigned int GetDac0DMod() { return BitExtractStatus(WD2_DAC0_D_MOD_REG, WD2_DAC0_D_MOD_MASK, WD2_DAC0_D_MOD_OFS); };

   // 0x00C00000: DAC0_E_MOD - DAC channel e modified flags
   unsigned int GetDac0EMod() { return BitExtractStatus(WD2_DAC0_E_MOD_REG, WD2_DAC0_E_MOD_MASK, WD2_DAC0_E_MOD_OFS); };

   // 0x00300000: DAC0_F_MOD - DAC channel f modified flags
   unsigned int GetDac0FMod() { return BitExtractStatus(WD2_DAC0_F_MOD_REG, WD2_DAC0_F_MOD_MASK, WD2_DAC0_F_MOD_OFS); };

   // 0x000C0000: DAC0_G_MOD - DAC channel g modified flags
   unsigned int GetDac0GMod() { return BitExtractStatus(WD2_DAC0_G_MOD_REG, WD2_DAC0_G_MOD_MASK, WD2_DAC0_G_MOD_OFS); };

   // 0x00030000: DAC0_H_MOD - DAC channel h modified flags
   unsigned int GetDac0HMod() { return BitExtractStatus(WD2_DAC0_H_MOD_REG, WD2_DAC0_H_MOD_MASK, WD2_DAC0_H_MOD_OFS); };

   // 0x0000C000: DAC1_A_MOD - DAC channel a modified flags
   unsigned int GetDac1AMod() { return BitExtractStatus(WD2_DAC1_A_MOD_REG, WD2_DAC1_A_MOD_MASK, WD2_DAC1_A_MOD_OFS); };

   // 0x00003000: DAC1_B_MOD - DAC channel b modified flags
   unsigned int GetDac1BMod() { return BitExtractStatus(WD2_DAC1_B_MOD_REG, WD2_DAC1_B_MOD_MASK, WD2_DAC1_B_MOD_OFS); };

   // 0x00000C00: DAC1_C_MOD - DAC channel c modified flags
   unsigned int GetDac1CMod() { return BitExtractStatus(WD2_DAC1_C_MOD_REG, WD2_DAC1_C_MOD_MASK, WD2_DAC1_C_MOD_OFS); };

   // 0x00000300: DAC1_D_MOD - DAC channel d modified flags
   unsigned int GetDac1DMod() { return BitExtractStatus(WD2_DAC1_D_MOD_REG, WD2_DAC1_D_MOD_MASK, WD2_DAC1_D_MOD_OFS); };

   // 0x000000C0: DAC1_E_MOD - DAC channel e modified flags
   unsigned int GetDac1EMod() { return BitExtractStatus(WD2_DAC1_E_MOD_REG, WD2_DAC1_E_MOD_MASK, WD2_DAC1_E_MOD_OFS); };

   // 0x00000030: DAC1_F_MOD - DAC channel f modified flags
   unsigned int GetDac1FMod() { return BitExtractStatus(WD2_DAC1_F_MOD_REG, WD2_DAC1_F_MOD_MASK, WD2_DAC1_F_MOD_OFS); };

   // 0x0000000C: DAC1_G_MOD - DAC channel g modified flags
   unsigned int GetDac1GMod() { return BitExtractStatus(WD2_DAC1_G_MOD_REG, WD2_DAC1_G_MOD_MASK, WD2_DAC1_G_MOD_OFS); };

   // 0x00000003: DAC1_H_MOD - DAC channel h modified flags
   unsigned int GetDac1HMod() { return BitExtractStatus(WD2_DAC1_H_MOD_REG, WD2_DAC1_H_MOD_MASK, WD2_DAC1_H_MOD_OFS); };



   ////// ------ Status Register 82 [0x0148]: DAC_2_MOD_FLAG - Set if DAC 2 configuration registers are modified (Default: 0x00000000) ------ //////

   // 0xC0000000: DAC2_A_MOD - DAC channel a modified flags
   unsigned int GetDac2AMod() { return BitExtractStatus(WD2_DAC2_A_MOD_REG, WD2_DAC2_A_MOD_MASK, WD2_DAC2_A_MOD_OFS); };

   // 0x30000000: DAC2_B_MOD - DAC channel b modified flags
   unsigned int GetDac2BMod() { return BitExtractStatus(WD2_DAC2_B_MOD_REG, WD2_DAC2_B_MOD_MASK, WD2_DAC2_B_MOD_OFS); };

   // 0x0C000000: DAC2_C_MOD - DAC channel c modified flags
   unsigned int GetDac2CMod() { return BitExtractStatus(WD2_DAC2_C_MOD_REG, WD2_DAC2_C_MOD_MASK, WD2_DAC2_C_MOD_OFS); };

   // 0x03000000: DAC2_D_MOD - DAC channel d modified flags
   unsigned int GetDac2DMod() { return BitExtractStatus(WD2_DAC2_D_MOD_REG, WD2_DAC2_D_MOD_MASK, WD2_DAC2_D_MOD_OFS); };

   // 0x00C00000: DAC2_E_MOD - DAC channel e modified flags
   unsigned int GetDac2EMod() { return BitExtractStatus(WD2_DAC2_E_MOD_REG, WD2_DAC2_E_MOD_MASK, WD2_DAC2_E_MOD_OFS); };

   // 0x00300000: DAC2_F_MOD - DAC channel f modified flags
   unsigned int GetDac2FMod() { return BitExtractStatus(WD2_DAC2_F_MOD_REG, WD2_DAC2_F_MOD_MASK, WD2_DAC2_F_MOD_OFS); };

   // 0x000C0000: DAC2_G_MOD - DAC channel g modified flags
   unsigned int GetDac2GMod() { return BitExtractStatus(WD2_DAC2_G_MOD_REG, WD2_DAC2_G_MOD_MASK, WD2_DAC2_G_MOD_OFS); };

   // 0x00030000: DAC2_H_MOD - DAC channel h modified flags
   unsigned int GetDac2HMod() { return BitExtractStatus(WD2_DAC2_H_MOD_REG, WD2_DAC2_H_MOD_MASK, WD2_DAC2_H_MOD_OFS); };



   ////// ------ Status Register 83 [0x014C]: FE_0_15_MOD_FLAG - Set if frontend configuraiton registers are modified (Default: 0x00000000) ------ //////

   // 0xC0000000: FE_0_MOD - Frontend channel 0 register modified flags
   unsigned int GetFe0Mod() { return BitExtractStatus(WD2_FE_0_MOD_REG, WD2_FE_0_MOD_MASK, WD2_FE_0_MOD_OFS); };

   // 0x30000000: FE_1_MOD - Frontend channel 1 register modified flags
   unsigned int GetFe1Mod() { return BitExtractStatus(WD2_FE_1_MOD_REG, WD2_FE_1_MOD_MASK, WD2_FE_1_MOD_OFS); };

   // 0x0C000000: FE_2_MOD - Frontend channel 2 register modified flags
   unsigned int GetFe2Mod() { return BitExtractStatus(WD2_FE_2_MOD_REG, WD2_FE_2_MOD_MASK, WD2_FE_2_MOD_OFS); };

   // 0x03000000: FE_3_MOD - Frontend channel 3 register modified flags
   unsigned int GetFe3Mod() { return BitExtractStatus(WD2_FE_3_MOD_REG, WD2_FE_3_MOD_MASK, WD2_FE_3_MOD_OFS); };

   // 0x00C00000: FE_4_MOD - Frontend channel 4 register modified flags
   unsigned int GetFe4Mod() { return BitExtractStatus(WD2_FE_4_MOD_REG, WD2_FE_4_MOD_MASK, WD2_FE_4_MOD_OFS); };

   // 0x00300000: FE_5_MOD - Frontend channel 5 register modified flags
   unsigned int GetFe5Mod() { return BitExtractStatus(WD2_FE_5_MOD_REG, WD2_FE_5_MOD_MASK, WD2_FE_5_MOD_OFS); };

   // 0x000C0000: FE_6_MOD - Frontend channel 6 register modified flags
   unsigned int GetFe6Mod() { return BitExtractStatus(WD2_FE_6_MOD_REG, WD2_FE_6_MOD_MASK, WD2_FE_6_MOD_OFS); };

   // 0x00030000: FE_7_MOD - Frontend channel 7 register modified flags
   unsigned int GetFe7Mod() { return BitExtractStatus(WD2_FE_7_MOD_REG, WD2_FE_7_MOD_MASK, WD2_FE_7_MOD_OFS); };

   // 0x0000C000: FE_8_MOD - Frontend channel 8 register modified flags
   unsigned int GetFe8Mod() { return BitExtractStatus(WD2_FE_8_MOD_REG, WD2_FE_8_MOD_MASK, WD2_FE_8_MOD_OFS); };

   // 0x00003000: FE_9_MOD - Frontend channel 9 register modified flags
   unsigned int GetFe9Mod() { return BitExtractStatus(WD2_FE_9_MOD_REG, WD2_FE_9_MOD_MASK, WD2_FE_9_MOD_OFS); };

   // 0x00000C00: FE_10_MOD - Frontend channel 10 register modified flags
   unsigned int GetFe10Mod() { return BitExtractStatus(WD2_FE_10_MOD_REG, WD2_FE_10_MOD_MASK, WD2_FE_10_MOD_OFS); };

   // 0x00000300: FE_11_MOD - Frontend channel 11 register modified flags
   unsigned int GetFe11Mod() { return BitExtractStatus(WD2_FE_11_MOD_REG, WD2_FE_11_MOD_MASK, WD2_FE_11_MOD_OFS); };

   // 0x000000C0: FE_12_MOD - Frontend channel 12 register modified flags
   unsigned int GetFe12Mod() { return BitExtractStatus(WD2_FE_12_MOD_REG, WD2_FE_12_MOD_MASK, WD2_FE_12_MOD_OFS); };

   // 0x00000030: FE_13_MOD - Frontend channel 13 register modified flags
   unsigned int GetFe13Mod() { return BitExtractStatus(WD2_FE_13_MOD_REG, WD2_FE_13_MOD_MASK, WD2_FE_13_MOD_OFS); };

   // 0x0000000C: FE_14_MOD - Frontend channel 14 register modified flags
   unsigned int GetFe14Mod() { return BitExtractStatus(WD2_FE_14_MOD_REG, WD2_FE_14_MOD_MASK, WD2_FE_14_MOD_OFS); };

   // 0x00000003: FE_15_MOD - Frontend channel 15 register modified flags
   unsigned int GetFe15Mod() { return BitExtractStatus(WD2_FE_15_MOD_REG, WD2_FE_15_MOD_MASK, WD2_FE_15_MOD_OFS); };



   ////// ------ Status Register 84 [0x0150]: HV_U_TARGET_0_7_MOD_FLAG - Set if HV target voltage configuraiton of channel 0 to 7 registers are modified (Default: 0x00000000) ------ //////

   // 0xF0000000: HV_U_TARGET_0_MOD - Target high voltage channel 0 register modified flags
   unsigned int GetHvUTarget0Mod() { return BitExtractStatus(WD2_HV_U_TARGET_0_MOD_REG, WD2_HV_U_TARGET_0_MOD_MASK, WD2_HV_U_TARGET_0_MOD_OFS); };

   // 0x0F000000: HV_U_TARGET_1_MOD - Target high voltage channel 1 register modified flags
   unsigned int GetHvUTarget1Mod() { return BitExtractStatus(WD2_HV_U_TARGET_1_MOD_REG, WD2_HV_U_TARGET_1_MOD_MASK, WD2_HV_U_TARGET_1_MOD_OFS); };

   // 0x00F00000: HV_U_TARGET_2_MOD - Target high voltage channel 2 register modified flags
   unsigned int GetHvUTarget2Mod() { return BitExtractStatus(WD2_HV_U_TARGET_2_MOD_REG, WD2_HV_U_TARGET_2_MOD_MASK, WD2_HV_U_TARGET_2_MOD_OFS); };

   // 0x000F0000: HV_U_TARGET_3_MOD - Target high voltage channel 3 register modified flags
   unsigned int GetHvUTarget3Mod() { return BitExtractStatus(WD2_HV_U_TARGET_3_MOD_REG, WD2_HV_U_TARGET_3_MOD_MASK, WD2_HV_U_TARGET_3_MOD_OFS); };

   // 0x0000F000: HV_U_TARGET_4_MOD - Target high voltage channel 4 register modified flags
   unsigned int GetHvUTarget4Mod() { return BitExtractStatus(WD2_HV_U_TARGET_4_MOD_REG, WD2_HV_U_TARGET_4_MOD_MASK, WD2_HV_U_TARGET_4_MOD_OFS); };

   // 0x00000F00: HV_U_TARGET_5_MOD - Target high voltage channel 5 register modified flags
   unsigned int GetHvUTarget5Mod() { return BitExtractStatus(WD2_HV_U_TARGET_5_MOD_REG, WD2_HV_U_TARGET_5_MOD_MASK, WD2_HV_U_TARGET_5_MOD_OFS); };

   // 0x000000F0: HV_U_TARGET_6_MOD - Target high voltage channel 6 register modified flags
   unsigned int GetHvUTarget6Mod() { return BitExtractStatus(WD2_HV_U_TARGET_6_MOD_REG, WD2_HV_U_TARGET_6_MOD_MASK, WD2_HV_U_TARGET_6_MOD_OFS); };

   // 0x0000000F: HV_U_TARGET_7_MOD - Target high voltage channel 7 register modified flags
   unsigned int GetHvUTarget7Mod() { return BitExtractStatus(WD2_HV_U_TARGET_7_MOD_REG, WD2_HV_U_TARGET_7_MOD_MASK, WD2_HV_U_TARGET_7_MOD_OFS); };



   ////// ------ Status Register 85 [0x0154]: HV_U_TARGET_8_15_MOD_FLAG - Set if HV target voltage configuraiton of channel 8 to 15 registers are modified (Default: 0x00000000) ------ //////

   // 0xF0000000: HV_U_TARGET_8_MOD - Target high voltage channel 8 register modified flags
   unsigned int GetHvUTarget8Mod() { return BitExtractStatus(WD2_HV_U_TARGET_8_MOD_REG, WD2_HV_U_TARGET_8_MOD_MASK, WD2_HV_U_TARGET_8_MOD_OFS); };

   // 0x0F000000: HV_U_TARGET_9_MOD - Target high voltage channel 9 register modified flags
   unsigned int GetHvUTarget9Mod() { return BitExtractStatus(WD2_HV_U_TARGET_9_MOD_REG, WD2_HV_U_TARGET_9_MOD_MASK, WD2_HV_U_TARGET_9_MOD_OFS); };

   // 0x00F00000: HV_U_TARGET_10_MOD - Target high voltage channel 10 register modified flags
   unsigned int GetHvUTarget10Mod() { return BitExtractStatus(WD2_HV_U_TARGET_10_MOD_REG, WD2_HV_U_TARGET_10_MOD_MASK, WD2_HV_U_TARGET_10_MOD_OFS); };

   // 0x000F0000: HV_U_TARGET_11_MOD - Target high voltage channel 11 register modified flags
   unsigned int GetHvUTarget11Mod() { return BitExtractStatus(WD2_HV_U_TARGET_11_MOD_REG, WD2_HV_U_TARGET_11_MOD_MASK, WD2_HV_U_TARGET_11_MOD_OFS); };

   // 0x0000F000: HV_U_TARGET_12_MOD - Target high voltage channel 12 register modified flags
   unsigned int GetHvUTarget12Mod() { return BitExtractStatus(WD2_HV_U_TARGET_12_MOD_REG, WD2_HV_U_TARGET_12_MOD_MASK, WD2_HV_U_TARGET_12_MOD_OFS); };

   // 0x00000F00: HV_U_TARGET_13_MOD - Target high voltage channel 13 register modified flags
   unsigned int GetHvUTarget13Mod() { return BitExtractStatus(WD2_HV_U_TARGET_13_MOD_REG, WD2_HV_U_TARGET_13_MOD_MASK, WD2_HV_U_TARGET_13_MOD_OFS); };

   // 0x000000F0: HV_U_TARGET_14_MOD - Target high voltage channel 14 register modified flags
   unsigned int GetHvUTarget14Mod() { return BitExtractStatus(WD2_HV_U_TARGET_14_MOD_REG, WD2_HV_U_TARGET_14_MOD_MASK, WD2_HV_U_TARGET_14_MOD_OFS); };

   // 0x0000000F: HV_U_TARGET_15_MOD - Target high voltage channel 15 register modified flags
   unsigned int GetHvUTarget15Mod() { return BitExtractStatus(WD2_HV_U_TARGET_15_MOD_REG, WD2_HV_U_TARGET_15_MOD_MASK, WD2_HV_U_TARGET_15_MOD_OFS); };



   ////// ------ Status Register 86 [0x0158]: HV_MOD_FLAG - Set if single HV configuraiton registers are modified (Default: 0x00000000) ------ //////

   // 0x0000000F: HV_R_SHUNT_MOD - HV supply shunt resistor register modified flags
   unsigned int GetHvRShuntMod() { return BitExtractStatus(WD2_HV_R_SHUNT_MOD_REG, WD2_HV_R_SHUNT_MOD_MASK, WD2_HV_R_SHUNT_MOD_OFS); };



   ////// ------ Status Register 87 [0x015C]: LMK_0_7_MOD_FLAG - Set if LMK configuraiton registers are modified (Default: 0x00000000) ------ //////

   // 0xF0000000: LMK_0_MOD - LMK channel 0 register modified flags
   unsigned int GetLmk0Mod() { return BitExtractStatus(WD2_LMK_0_MOD_REG, WD2_LMK_0_MOD_MASK, WD2_LMK_0_MOD_OFS); };

   // 0x0F000000: LMK_1_MOD - LMK channel 1 register modified flags
   unsigned int GetLmk1Mod() { return BitExtractStatus(WD2_LMK_1_MOD_REG, WD2_LMK_1_MOD_MASK, WD2_LMK_1_MOD_OFS); };

   // 0x00F00000: LMK_2_MOD - LMK channel 2 register modified flags
   unsigned int GetLmk2Mod() { return BitExtractStatus(WD2_LMK_2_MOD_REG, WD2_LMK_2_MOD_MASK, WD2_LMK_2_MOD_OFS); };

   // 0x000F0000: LMK_3_MOD - LMK channel 3 register modified flags
   unsigned int GetLmk3Mod() { return BitExtractStatus(WD2_LMK_3_MOD_REG, WD2_LMK_3_MOD_MASK, WD2_LMK_3_MOD_OFS); };

   // 0x0000F000: LMK_4_MOD - LMK channel 4 register modified flags
   unsigned int GetLmk4Mod() { return BitExtractStatus(WD2_LMK_4_MOD_REG, WD2_LMK_4_MOD_MASK, WD2_LMK_4_MOD_OFS); };

   // 0x00000F00: LMK_5_MOD - LMK channel 5 register modified flags
   unsigned int GetLmk5Mod() { return BitExtractStatus(WD2_LMK_5_MOD_REG, WD2_LMK_5_MOD_MASK, WD2_LMK_5_MOD_OFS); };

   // 0x000000F0: LMK_6_MOD - LMK channel 6 register modified flags
   unsigned int GetLmk6Mod() { return BitExtractStatus(WD2_LMK_6_MOD_REG, WD2_LMK_6_MOD_MASK, WD2_LMK_6_MOD_OFS); };

   // 0x0000000F: LMK_7_MOD - LMK channel 7 register modified flags
   unsigned int GetLmk7Mod() { return BitExtractStatus(WD2_LMK_7_MOD_REG, WD2_LMK_7_MOD_MASK, WD2_LMK_7_MOD_OFS); };



   ////// ------ Status Register 88 [0x0160]: LMK_8_15_MOD_FLAG - Set if LMK configuraiton registers are modified (Default: 0x00000000) ------ //////

   // 0x00F00000: LMK_8_MOD - LMK Register 8 modified flags
   unsigned int GetLmk8Mod() { return BitExtractStatus(WD2_LMK_8_MOD_REG, WD2_LMK_8_MOD_MASK, WD2_LMK_8_MOD_OFS); };

   // 0x000F0000: LMK_9_MOD - LMK Register 9 modified flags
   unsigned int GetLmk9Mod() { return BitExtractStatus(WD2_LMK_9_MOD_REG, WD2_LMK_9_MOD_MASK, WD2_LMK_9_MOD_OFS); };

   // 0x0000F000: LMK_11_MOD - LMK Register 11 modified flags
   unsigned int GetLmk11Mod() { return BitExtractStatus(WD2_LMK_11_MOD_REG, WD2_LMK_11_MOD_MASK, WD2_LMK_11_MOD_OFS); };

   // 0x00000F00: LMK_13_MOD - LMK Register 13 modified flags
   unsigned int GetLmk13Mod() { return BitExtractStatus(WD2_LMK_13_MOD_REG, WD2_LMK_13_MOD_MASK, WD2_LMK_13_MOD_OFS); };

   // 0x000000F0: LMK_14_MOD - LMK Register 14 modified flags
   unsigned int GetLmk14Mod() { return BitExtractStatus(WD2_LMK_14_MOD_REG, WD2_LMK_14_MOD_MASK, WD2_LMK_14_MOD_OFS); };

   // 0x0000000F: LMK_15_MOD - LMK Register 15 modified flags
   unsigned int GetLmk15Mod() { return BitExtractStatus(WD2_LMK_15_MOD_REG, WD2_LMK_15_MOD_MASK, WD2_LMK_15_MOD_OFS); };


};

//--------------------------------------------------------------------

#endif /* defined(__wdbreg_h__) */

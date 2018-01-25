//
//  WDBReg.h
//
//  WaveDAQ Register Access Class
//
//  This file is generated automatically, please do not edit!
//
// Created :  24.01.2018 16:52:02//


#ifndef __wdbreg_h__
#define __wdbreg_h__

#include "register_map_wd2.h"

//--------------------------------------------------------------------

class WDBREG {

private:
   // virtual bit functions, must be implemented in derived class
   virtual unsigned int BitExtractStatus(unsigned int rofs, unsigned int mask, unsigned int ofs) = 0;
   virtual unsigned int BitExtractControl(unsigned int rofs, unsigned int mask, unsigned int ofs) = 0;
   virtual void SetRegMask(unsigned int rofs, unsigned int mask, unsigned int ofs, unsigned int v) = 0;

public:
   
   // constructor
   WDBREG(){};


   // Control Register 0: WDB_LOC (offset 0x1000) 
   unsigned int GetCrateId() {
      return BitExtractControl(WD2_CRATE_ID_REG, WD2_CRATE_ID_MASK, WD2_CRATE_ID_OFS);
   };

   void SetCrateId(unsigned int value) {
      SetRegMask(WD2_CRATE_ID_REG, WD2_CRATE_ID_MASK, WD2_CRATE_ID_OFS, value);
   };

   unsigned int GetSlotId() {
      return BitExtractControl(WD2_SLOT_ID_REG, WD2_SLOT_ID_MASK, WD2_SLOT_ID_OFS);
   };

   void SetSlotId(unsigned int value) {
      SetRegMask(WD2_SLOT_ID_REG, WD2_SLOT_ID_MASK, WD2_SLOT_ID_OFS, value);
   };


   // Control Register 1: CTRL (offset 0x1004) 
   unsigned int GetValidDelayAdc() {
      return BitExtractControl(WD2_VALID_DELAY_ADC_REG, WD2_VALID_DELAY_ADC_MASK, WD2_VALID_DELAY_ADC_OFS);
   };

   void SetValidDelayAdc(unsigned int value) {
      SetRegMask(WD2_VALID_DELAY_ADC_REG, WD2_VALID_DELAY_ADC_MASK, WD2_VALID_DELAY_ADC_OFS, value);
   };

   unsigned int GetDaqDataPhase() {
      return BitExtractControl(WD2_DAQ_DATA_PHASE_REG, WD2_DAQ_DATA_PHASE_MASK, WD2_DAQ_DATA_PHASE_OFS);
   };

   void SetDaqDataPhase(unsigned int value) {
      SetRegMask(WD2_DAQ_DATA_PHASE_REG, WD2_DAQ_DATA_PHASE_MASK, WD2_DAQ_DATA_PHASE_OFS, value);
   };

   unsigned int GetCompPowerEn() {
      return BitExtractControl(WD2_COMP_POWER_EN_REG, WD2_COMP_POWER_EN_MASK, WD2_COMP_POWER_EN_OFS);
   };

   void SetCompPowerEn(unsigned int value) {
      SetRegMask(WD2_COMP_POWER_EN_REG, WD2_COMP_POWER_EN_MASK, WD2_COMP_POWER_EN_OFS, value);
   };

   unsigned int GetDrsReadoutMode() {
      return BitExtractControl(WD2_DRS_READOUT_MODE_REG, WD2_DRS_READOUT_MODE_MASK, WD2_DRS_READOUT_MODE_OFS);
   };

   void SetDrsReadoutMode(unsigned int value) {
      SetRegMask(WD2_DRS_READOUT_MODE_REG, WD2_DRS_READOUT_MODE_MASK, WD2_DRS_READOUT_MODE_OFS, value);
   };

   unsigned int GetDrsWaveContinuous() {
      return BitExtractControl(WD2_DRS_WAVE_CONTINUOUS_REG, WD2_DRS_WAVE_CONTINUOUS_MASK, WD2_DRS_WAVE_CONTINUOUS_OFS);
   };

   void SetDrsWaveContinuous(unsigned int value) {
      SetRegMask(WD2_DRS_WAVE_CONTINUOUS_REG, WD2_DRS_WAVE_CONTINUOUS_MASK, WD2_DRS_WAVE_CONTINUOUS_OFS, value);
   };

   unsigned int GetDrsConfigure() {
      return BitExtractControl(WD2_DRS_CONFIGURE_REG, WD2_DRS_CONFIGURE_MASK, WD2_DRS_CONFIGURE_OFS);
   };

   void SetDrsConfigure(unsigned int value) {
      SetRegMask(WD2_DRS_CONFIGURE_REG, WD2_DRS_CONFIGURE_MASK, WD2_DRS_CONFIGURE_OFS, value);
   };

   unsigned int GetDaqSoftTrigger() {
      return BitExtractControl(WD2_DAQ_SOFT_TRIGGER_REG, WD2_DAQ_SOFT_TRIGGER_MASK, WD2_DAQ_SOFT_TRIGGER_OFS);
   };

   void SetDaqSoftTrigger(unsigned int value) {
      SetRegMask(WD2_DAQ_SOFT_TRIGGER_REG, WD2_DAQ_SOFT_TRIGGER_MASK, WD2_DAQ_SOFT_TRIGGER_OFS, value);
   };

   unsigned int GetDaqAuto() {
      return BitExtractControl(WD2_DAQ_AUTO_REG, WD2_DAQ_AUTO_MASK, WD2_DAQ_AUTO_OFS);
   };

   void SetDaqAuto(unsigned int value) {
      SetRegMask(WD2_DAQ_AUTO_REG, WD2_DAQ_AUTO_MASK, WD2_DAQ_AUTO_OFS, value);
   };

   unsigned int GetDaqNormal() {
      return BitExtractControl(WD2_DAQ_NORMAL_REG, WD2_DAQ_NORMAL_MASK, WD2_DAQ_NORMAL_OFS);
   };

   void SetDaqNormal(unsigned int value) {
      SetRegMask(WD2_DAQ_NORMAL_REG, WD2_DAQ_NORMAL_MASK, WD2_DAQ_NORMAL_OFS, value);
   };

   unsigned int GetDaqSingle() {
      return BitExtractControl(WD2_DAQ_SINGLE_REG, WD2_DAQ_SINGLE_MASK, WD2_DAQ_SINGLE_OFS);
   };

   void SetDaqSingle(unsigned int value) {
      SetRegMask(WD2_DAQ_SINGLE_REG, WD2_DAQ_SINGLE_MASK, WD2_DAQ_SINGLE_OFS, value);
   };


   // Control Register 2: CAL_CTRL (offset 0x1008) 
   unsigned int GetDrs0TimingRefSel() {
      return BitExtractControl(WD2_DRS_0_TIMING_REF_SEL_REG, WD2_DRS_0_TIMING_REF_SEL_MASK, WD2_DRS_0_TIMING_REF_SEL_OFS);
   };

   void SetDrs0TimingRefSel(unsigned int value) {
      SetRegMask(WD2_DRS_0_TIMING_REF_SEL_REG, WD2_DRS_0_TIMING_REF_SEL_MASK, WD2_DRS_0_TIMING_REF_SEL_OFS, value);
   };

   unsigned int GetDrs1TimingRefSel() {
      return BitExtractControl(WD2_DRS_1_TIMING_REF_SEL_REG, WD2_DRS_1_TIMING_REF_SEL_MASK, WD2_DRS_1_TIMING_REF_SEL_OFS);
   };

   void SetDrs1TimingRefSel(unsigned int value) {
      SetRegMask(WD2_DRS_1_TIMING_REF_SEL_REG, WD2_DRS_1_TIMING_REF_SEL_MASK, WD2_DRS_1_TIMING_REF_SEL_OFS, value);
   };

   unsigned int GetCalibBufferEn() {
      return BitExtractControl(WD2_CALIB_BUFFER_EN_REG, WD2_CALIB_BUFFER_EN_MASK, WD2_CALIB_BUFFER_EN_OFS);
   };

   void SetCalibBufferEn(unsigned int value) {
      SetRegMask(WD2_CALIB_BUFFER_EN_REG, WD2_CALIB_BUFFER_EN_MASK, WD2_CALIB_BUFFER_EN_OFS, value);
   };

   unsigned int GetTimingCalibSignalEn() {
      return BitExtractControl(WD2_TIMING_CALIB_SIGNAL_EN_REG, WD2_TIMING_CALIB_SIGNAL_EN_MASK, WD2_TIMING_CALIB_SIGNAL_EN_OFS);
   };

   void SetTimingCalibSignalEn(unsigned int value) {
      SetRegMask(WD2_TIMING_CALIB_SIGNAL_EN_REG, WD2_TIMING_CALIB_SIGNAL_EN_MASK, WD2_TIMING_CALIB_SIGNAL_EN_OFS, value);
   };


   // Control Register 3: CLK_CTRL (offset 0x100C) 
   unsigned int GetDaqClkSrcSel() {
      return BitExtractControl(WD2_DAQ_CLK_SRC_SEL_REG, WD2_DAQ_CLK_SRC_SEL_MASK, WD2_DAQ_CLK_SRC_SEL_OFS);
   };

   void SetDaqClkSrcSel(unsigned int value) {
      SetRegMask(WD2_DAQ_CLK_SRC_SEL_REG, WD2_DAQ_CLK_SRC_SEL_MASK, WD2_DAQ_CLK_SRC_SEL_OFS, value);
   };

   unsigned int GetExtClkInSel() {
      return BitExtractControl(WD2_EXT_CLK_IN_SEL_REG, WD2_EXT_CLK_IN_SEL_MASK, WD2_EXT_CLK_IN_SEL_OFS);
   };

   void SetExtClkInSel(unsigned int value) {
      SetRegMask(WD2_EXT_CLK_IN_SEL_REG, WD2_EXT_CLK_IN_SEL_MASK, WD2_EXT_CLK_IN_SEL_OFS, value);
   };

   unsigned int GetExtClkFreq() {
      return BitExtractControl(WD2_EXT_CLK_FREQ_REG, WD2_EXT_CLK_FREQ_MASK, WD2_EXT_CLK_FREQ_OFS);
   };

   void SetExtClkFreq(unsigned int value) {
      SetRegMask(WD2_EXT_CLK_FREQ_REG, WD2_EXT_CLK_FREQ_MASK, WD2_EXT_CLK_FREQ_OFS, value);
   };

   unsigned int GetLocalClkFreq() {
      return BitExtractControl(WD2_LOCAL_CLK_FREQ_REG, WD2_LOCAL_CLK_FREQ_MASK, WD2_LOCAL_CLK_FREQ_OFS);
   };

   void SetLocalClkFreq(unsigned int value) {
      SetRegMask(WD2_LOCAL_CLK_FREQ_REG, WD2_LOCAL_CLK_FREQ_MASK, WD2_LOCAL_CLK_FREQ_OFS, value);
   };


   // Control Register 4: DRS_CTRL (offset 0x1010) 
   unsigned int GetDrsWsrloop() {
      return BitExtractControl(WD2_DRS_WSRLOOP_REG, WD2_DRS_WSRLOOP_MASK, WD2_DRS_WSRLOOP_OFS);
   };

   void SetDrsWsrloop(unsigned int value) {
      SetRegMask(WD2_DRS_WSRLOOP_REG, WD2_DRS_WSRLOOP_MASK, WD2_DRS_WSRLOOP_OFS, value);
   };

   unsigned int GetDrsPllen() {
      return BitExtractControl(WD2_DRS_PLLEN_REG, WD2_DRS_PLLEN_MASK, WD2_DRS_PLLEN_OFS);
   };

   void SetDrsPllen(unsigned int value) {
      SetRegMask(WD2_DRS_PLLEN_REG, WD2_DRS_PLLEN_MASK, WD2_DRS_PLLEN_OFS, value);
   };

   unsigned int GetDrsDmode() {
      return BitExtractControl(WD2_DRS_DMODE_REG, WD2_DRS_DMODE_MASK, WD2_DRS_DMODE_OFS);
   };

   void SetDrsDmode(unsigned int value) {
      SetRegMask(WD2_DRS_DMODE_REG, WD2_DRS_DMODE_MASK, WD2_DRS_DMODE_OFS, value);
   };

   unsigned int GetDrsWsr() {
      return BitExtractControl(WD2_DRS_WSR_REG, WD2_DRS_WSR_MASK, WD2_DRS_WSR_OFS);
   };

   void SetDrsWsr(unsigned int value) {
      SetRegMask(WD2_DRS_WSR_REG, WD2_DRS_WSR_MASK, WD2_DRS_WSR_OFS, value);
   };

   unsigned int GetDrsWcr() {
      return BitExtractControl(WD2_DRS_WCR_REG, WD2_DRS_WCR_MASK, WD2_DRS_WCR_OFS);
   };

   void SetDrsWcr(unsigned int value) {
      SetRegMask(WD2_DRS_WCR_REG, WD2_DRS_WCR_MASK, WD2_DRS_WCR_OFS, value);
   };


   // Control Register 5: COM_CTRL (offset 0x1014) 
   unsigned int GetDcbSerdesTrain() {
      return BitExtractControl(WD2_DCB_SERDES_TRAIN_REG, WD2_DCB_SERDES_TRAIN_MASK, WD2_DCB_SERDES_TRAIN_OFS);
   };

   void SetDcbSerdesTrain(unsigned int value) {
      SetRegMask(WD2_DCB_SERDES_TRAIN_REG, WD2_DCB_SERDES_TRAIN_MASK, WD2_DCB_SERDES_TRAIN_OFS, value);
   };

   unsigned int GetTcbSerdesTrain() {
      return BitExtractControl(WD2_TCB_SERDES_TRAIN_REG, WD2_TCB_SERDES_TRAIN_MASK, WD2_TCB_SERDES_TRAIN_OFS);
   };

   void SetTcbSerdesTrain(unsigned int value) {
      SetRegMask(WD2_TCB_SERDES_TRAIN_REG, WD2_TCB_SERDES_TRAIN_MASK, WD2_TCB_SERDES_TRAIN_OFS, value);
   };

   unsigned int GetTrgTxEn() {
      return BitExtractControl(WD2_TRG_TX_EN_REG, WD2_TRG_TX_EN_MASK, WD2_TRG_TX_EN_OFS);
   };

   void SetTrgTxEn(unsigned int value) {
      SetRegMask(WD2_TRG_TX_EN_REG, WD2_TRG_TX_EN_MASK, WD2_TRG_TX_EN_OFS, value);
   };

   unsigned int GetSclTxEn() {
      return BitExtractControl(WD2_SCL_TX_EN_REG, WD2_SCL_TX_EN_MASK, WD2_SCL_TX_EN_OFS);
   };

   void SetSclTxEn(unsigned int value) {
      SetRegMask(WD2_SCL_TX_EN_REG, WD2_SCL_TX_EN_MASK, WD2_SCL_TX_EN_OFS, value);
   };

   unsigned int GetSerdesComEn() {
      return BitExtractControl(WD2_SERDES_COM_EN_REG, WD2_SERDES_COM_EN_MASK, WD2_SERDES_COM_EN_OFS);
   };

   void SetSerdesComEn(unsigned int value) {
      SetRegMask(WD2_SERDES_COM_EN_REG, WD2_SERDES_COM_EN_MASK, WD2_SERDES_COM_EN_OFS, value);
   };

   unsigned int GetEthComEn() {
      return BitExtractControl(WD2_ETH_COM_EN_REG, WD2_ETH_COM_EN_MASK, WD2_ETH_COM_EN_OFS);
   };

   void SetEthComEn(unsigned int value) {
      SetRegMask(WD2_ETH_COM_EN_REG, WD2_ETH_COM_EN_MASK, WD2_ETH_COM_EN_OFS, value);
   };

   unsigned int GetInterPkgDelay() {
      return BitExtractControl(WD2_INTER_PKG_DELAY_REG, WD2_INTER_PKG_DELAY_MASK, WD2_INTER_PKG_DELAY_OFS);
   };

   void SetInterPkgDelay(unsigned int value) {
      SetRegMask(WD2_INTER_PKG_DELAY_REG, WD2_INTER_PKG_DELAY_MASK, WD2_INTER_PKG_DELAY_OFS, value);
   };


   // Control Register 6: COM_PLD_SIZE (offset 0x1018) 
   unsigned int GetComPldSize() {
      return BitExtractControl(WD2_COM_PLD_SIZE_REG, WD2_COM_PLD_SIZE_MASK, WD2_COM_PLD_SIZE_OFS);
   };

   void SetComPldSize(unsigned int value) {
      SetRegMask(WD2_COM_PLD_SIZE_REG, WD2_COM_PLD_SIZE_MASK, WD2_COM_PLD_SIZE_OFS, value);
   };


   // Control Register 7: DRS_CH_TX_EN (offset 0x101C) 
   unsigned int GetDrsChTxEn() {
      return BitExtractControl(WD2_DRS_CH_TX_EN_REG, WD2_DRS_CH_TX_EN_MASK, WD2_DRS_CH_TX_EN_OFS);
   };

   void SetDrsChTxEn(unsigned int value) {
      SetRegMask(WD2_DRS_CH_TX_EN_REG, WD2_DRS_CH_TX_EN_MASK, WD2_DRS_CH_TX_EN_OFS, value);
   };


   // Control Register 8: ADC_CH_TX_EN (offset 0x1020) 
   unsigned int GetAdcChTxEn() {
      return BitExtractControl(WD2_ADC_CH_TX_EN_REG, WD2_ADC_CH_TX_EN_MASK, WD2_ADC_CH_TX_EN_OFS);
   };

   void SetAdcChTxEn(unsigned int value) {
      SetRegMask(WD2_ADC_CH_TX_EN_REG, WD2_ADC_CH_TX_EN_MASK, WD2_ADC_CH_TX_EN_OFS, value);
   };


   // Control Register 9: TDC_CH_TX_EN (offset 0x1024) 
   unsigned int GetTdcChTxEn() {
      return BitExtractControl(WD2_TDC_CH_TX_EN_REG, WD2_TDC_CH_TX_EN_MASK, WD2_TDC_CH_TX_EN_OFS);
   };

   void SetTdcChTxEn(unsigned int value) {
      SetRegMask(WD2_TDC_CH_TX_EN_REG, WD2_TDC_CH_TX_EN_MASK, WD2_TDC_CH_TX_EN_OFS, value);
   };


   // Control Register 10: DRS_TX_SAMPLES (offset 0x1028) 
   unsigned int GetDrsTxSamples() {
      return BitExtractControl(WD2_DRS_TX_SAMPLES_REG, WD2_DRS_TX_SAMPLES_MASK, WD2_DRS_TX_SAMPLES_OFS);
   };

   void SetDrsTxSamples(unsigned int value) {
      SetRegMask(WD2_DRS_TX_SAMPLES_REG, WD2_DRS_TX_SAMPLES_MASK, WD2_DRS_TX_SAMPLES_OFS, value);
   };


   // Control Register 11: ADC_TX_SAMPLES (offset 0x102C) 
   unsigned int GetAdcTxSamples() {
      return BitExtractControl(WD2_ADC_TX_SAMPLES_REG, WD2_ADC_TX_SAMPLES_MASK, WD2_ADC_TX_SAMPLES_OFS);
   };

   void SetAdcTxSamples(unsigned int value) {
      SetRegMask(WD2_ADC_TX_SAMPLES_REG, WD2_ADC_TX_SAMPLES_MASK, WD2_ADC_TX_SAMPLES_OFS, value);
   };


   // Control Register 12: TDC_TX_SAMPLES (offset 0x1030) 
   unsigned int GetTdcTxSamples() {
      return BitExtractControl(WD2_TDC_TX_SAMPLES_REG, WD2_TDC_TX_SAMPLES_MASK, WD2_TDC_TX_SAMPLES_OFS);
   };

   void SetTdcTxSamples(unsigned int value) {
      SetRegMask(WD2_TDC_TX_SAMPLES_REG, WD2_TDC_TX_SAMPLES_MASK, WD2_TDC_TX_SAMPLES_OFS, value);
   };


   // Control Register 13: TRG_TX_SAMPLES (offset 0x1034) 
   unsigned int GetTrgTxSamples() {
      return BitExtractControl(WD2_TRG_TX_SAMPLES_REG, WD2_TRG_TX_SAMPLES_MASK, WD2_TRG_TX_SAMPLES_OFS);
   };

   void SetTrgTxSamples(unsigned int value) {
      SetRegMask(WD2_TRG_TX_SAMPLES_REG, WD2_TRG_TX_SAMPLES_MASK, WD2_TRG_TX_SAMPLES_OFS, value);
   };


   // Control Register 14: ADC_SAMPLE_DIV (offset 0x1038) 
   unsigned int GetAdcSampleDiv() {
      return BitExtractControl(WD2_ADC_SAMPLE_DIV_REG, WD2_ADC_SAMPLE_DIV_MASK, WD2_ADC_SAMPLE_DIV_OFS);
   };

   void SetAdcSampleDiv(unsigned int value) {
      SetRegMask(WD2_ADC_SAMPLE_DIV_REG, WD2_ADC_SAMPLE_DIV_MASK, WD2_ADC_SAMPLE_DIV_OFS, value);
   };


   // Control Register 15: ZERO_SUPR (offset 0x103C) 
   unsigned int GetZeroSuprPolarity() {
      return BitExtractControl(WD2_ZERO_SUPR_POLARITY_REG, WD2_ZERO_SUPR_POLARITY_MASK, WD2_ZERO_SUPR_POLARITY_OFS);
   };

   void SetZeroSuprPolarity(unsigned int value) {
      SetRegMask(WD2_ZERO_SUPR_POLARITY_REG, WD2_ZERO_SUPR_POLARITY_MASK, WD2_ZERO_SUPR_POLARITY_OFS, value);
   };

   unsigned int GetZeroSuprEn() {
      return BitExtractControl(WD2_ZERO_SUPR_EN_REG, WD2_ZERO_SUPR_EN_MASK, WD2_ZERO_SUPR_EN_OFS);
   };

   void SetZeroSuprEn(unsigned int value) {
      SetRegMask(WD2_ZERO_SUPR_EN_REG, WD2_ZERO_SUPR_EN_MASK, WD2_ZERO_SUPR_EN_OFS, value);
   };

   unsigned int GetZeroSuprWindow() {
      return BitExtractControl(WD2_ZERO_SUPR_WINDOW_REG, WD2_ZERO_SUPR_WINDOW_MASK, WD2_ZERO_SUPR_WINDOW_OFS);
   };

   void SetZeroSuprWindow(unsigned int value) {
      SetRegMask(WD2_ZERO_SUPR_WINDOW_REG, WD2_ZERO_SUPR_WINDOW_MASK, WD2_ZERO_SUPR_WINDOW_OFS, value);
   };


   // Control Register 16: RST (offset 0x1040) 
   unsigned int GetDaqPllRst() {
      return BitExtractControl(WD2_DAQ_PLL_RST_REG, WD2_DAQ_PLL_RST_MASK, WD2_DAQ_PLL_RST_OFS);
   };

   void SetDaqPllRst(unsigned int value) {
      SetRegMask(WD2_DAQ_PLL_RST_REG, WD2_DAQ_PLL_RST_MASK, WD2_DAQ_PLL_RST_OFS, value);
   };

   unsigned int GetDcbOserdesPllRst() {
      return BitExtractControl(WD2_DCB_OSERDES_PLL_RST_REG, WD2_DCB_OSERDES_PLL_RST_MASK, WD2_DCB_OSERDES_PLL_RST_OFS);
   };

   void SetDcbOserdesPllRst(unsigned int value) {
      SetRegMask(WD2_DCB_OSERDES_PLL_RST_REG, WD2_DCB_OSERDES_PLL_RST_MASK, WD2_DCB_OSERDES_PLL_RST_OFS, value);
   };

   unsigned int GetTcbOserdesPllRst() {
      return BitExtractControl(WD2_TCB_OSERDES_PLL_RST_REG, WD2_TCB_OSERDES_PLL_RST_MASK, WD2_TCB_OSERDES_PLL_RST_OFS);
   };

   void SetTcbOserdesPllRst(unsigned int value) {
      SetRegMask(WD2_TCB_OSERDES_PLL_RST_REG, WD2_TCB_OSERDES_PLL_RST_MASK, WD2_TCB_OSERDES_PLL_RST_OFS, value);
   };

   unsigned int GetDcbOserdesIfRst() {
      return BitExtractControl(WD2_DCB_OSERDES_IF_RST_REG, WD2_DCB_OSERDES_IF_RST_MASK, WD2_DCB_OSERDES_IF_RST_OFS);
   };

   void SetDcbOserdesIfRst(unsigned int value) {
      SetRegMask(WD2_DCB_OSERDES_IF_RST_REG, WD2_DCB_OSERDES_IF_RST_MASK, WD2_DCB_OSERDES_IF_RST_OFS, value);
   };

   unsigned int GetTcbOserdesIfRst() {
      return BitExtractControl(WD2_TCB_OSERDES_IF_RST_REG, WD2_TCB_OSERDES_IF_RST_MASK, WD2_TCB_OSERDES_IF_RST_OFS);
   };

   void SetTcbOserdesIfRst(unsigned int value) {
      SetRegMask(WD2_TCB_OSERDES_IF_RST_REG, WD2_TCB_OSERDES_IF_RST_MASK, WD2_TCB_OSERDES_IF_RST_OFS, value);
   };

   unsigned int GetScalerRst() {
      return BitExtractControl(WD2_SCALER_RST_REG, WD2_SCALER_RST_MASK, WD2_SCALER_RST_OFS);
   };

   void SetScalerRst(unsigned int value) {
      SetRegMask(WD2_SCALER_RST_REG, WD2_SCALER_RST_MASK, WD2_SCALER_RST_OFS, value);
   };

   unsigned int GetTrbParityErrorCountRst() {
      return BitExtractControl(WD2_TRB_PARITY_ERROR_COUNT_RST_REG, WD2_TRB_PARITY_ERROR_COUNT_RST_MASK, WD2_TRB_PARITY_ERROR_COUNT_RST_OFS);
   };

   void SetTrbParityErrorCountRst(unsigned int value) {
      SetRegMask(WD2_TRB_PARITY_ERROR_COUNT_RST_REG, WD2_TRB_PARITY_ERROR_COUNT_RST_MASK, WD2_TRB_PARITY_ERROR_COUNT_RST_OFS, value);
   };

   unsigned int GetLmkSyncLocal() {
      return BitExtractControl(WD2_LMK_SYNC_LOCAL_REG, WD2_LMK_SYNC_LOCAL_MASK, WD2_LMK_SYNC_LOCAL_OFS);
   };

   void SetLmkSyncLocal(unsigned int value) {
      SetRegMask(WD2_LMK_SYNC_LOCAL_REG, WD2_LMK_SYNC_LOCAL_MASK, WD2_LMK_SYNC_LOCAL_OFS, value);
   };

   unsigned int GetAdcIfRst() {
      return BitExtractControl(WD2_ADC_IF_RST_REG, WD2_ADC_IF_RST_MASK, WD2_ADC_IF_RST_OFS);
   };

   void SetAdcIfRst(unsigned int value) {
      SetRegMask(WD2_ADC_IF_RST_REG, WD2_ADC_IF_RST_MASK, WD2_ADC_IF_RST_OFS, value);
   };

   unsigned int GetDataLinkIfRst() {
      return BitExtractControl(WD2_DATA_LINK_IF_RST_REG, WD2_DATA_LINK_IF_RST_MASK, WD2_DATA_LINK_IF_RST_OFS);
   };

   void SetDataLinkIfRst(unsigned int value) {
      SetRegMask(WD2_DATA_LINK_IF_RST_REG, WD2_DATA_LINK_IF_RST_MASK, WD2_DATA_LINK_IF_RST_OFS, value);
   };

   unsigned int GetWdPkgrRst() {
      return BitExtractControl(WD2_WD_PKGR_RST_REG, WD2_WD_PKGR_RST_MASK, WD2_WD_PKGR_RST_OFS);
   };

   void SetWdPkgrRst(unsigned int value) {
      SetRegMask(WD2_WD_PKGR_RST_REG, WD2_WD_PKGR_RST_MASK, WD2_WD_PKGR_RST_OFS, value);
   };

   unsigned int GetEventCounterRst() {
      return BitExtractControl(WD2_EVENT_COUNTER_RST_REG, WD2_EVENT_COUNTER_RST_MASK, WD2_EVENT_COUNTER_RST_OFS);
   };

   void SetEventCounterRst(unsigned int value) {
      SetRegMask(WD2_EVENT_COUNTER_RST_REG, WD2_EVENT_COUNTER_RST_MASK, WD2_EVENT_COUNTER_RST_OFS, value);
   };

   unsigned int GetDrsCtrlFsmRst() {
      return BitExtractControl(WD2_DRS_CTRL_FSM_RST_REG, WD2_DRS_CTRL_FSM_RST_MASK, WD2_DRS_CTRL_FSM_RST_OFS);
   };

   void SetDrsCtrlFsmRst(unsigned int value) {
      SetRegMask(WD2_DRS_CTRL_FSM_RST_REG, WD2_DRS_CTRL_FSM_RST_MASK, WD2_DRS_CTRL_FSM_RST_OFS, value);
   };

   unsigned int GetReconfigureFpga() {
      return BitExtractControl(WD2_RECONFIGURE_FPGA_REG, WD2_RECONFIGURE_FPGA_MASK, WD2_RECONFIGURE_FPGA_OFS);
   };

   void SetReconfigureFpga(unsigned int value) {
      SetRegMask(WD2_RECONFIGURE_FPGA_REG, WD2_RECONFIGURE_FPGA_MASK, WD2_RECONFIGURE_FPGA_OFS, value);
   };


   // Control Register 17: APLY_CFG (offset 0x1044) 
   unsigned int GetApplySettingsAdcSampleDiv() {
      return BitExtractControl(WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_REG, WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_MASK, WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_OFS);
   };

   void SetApplySettingsAdcSampleDiv(unsigned int value) {
      SetRegMask(WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_REG, WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_MASK, WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_OFS, value);
   };

   unsigned int GetApplySettingsMaxPldSize() {
      return BitExtractControl(WD2_APPLY_SETTINGS_MAX_PLD_SIZE_REG, WD2_APPLY_SETTINGS_MAX_PLD_SIZE_MASK, WD2_APPLY_SETTINGS_MAX_PLD_SIZE_OFS);
   };

   void SetApplySettingsMaxPldSize(unsigned int value) {
      SetRegMask(WD2_APPLY_SETTINGS_MAX_PLD_SIZE_REG, WD2_APPLY_SETTINGS_MAX_PLD_SIZE_MASK, WD2_APPLY_SETTINGS_MAX_PLD_SIZE_OFS, value);
   };

   unsigned int GetApplySettingsHv() {
      return BitExtractControl(WD2_APPLY_SETTINGS_HV_REG, WD2_APPLY_SETTINGS_HV_MASK, WD2_APPLY_SETTINGS_HV_OFS);
   };

   void SetApplySettingsHv(unsigned int value) {
      SetRegMask(WD2_APPLY_SETTINGS_HV_REG, WD2_APPLY_SETTINGS_HV_MASK, WD2_APPLY_SETTINGS_HV_OFS, value);
   };

   unsigned int GetApplySettingsDrs() {
      return BitExtractControl(WD2_APPLY_SETTINGS_DRS_REG, WD2_APPLY_SETTINGS_DRS_MASK, WD2_APPLY_SETTINGS_DRS_OFS);
   };

   void SetApplySettingsDrs(unsigned int value) {
      SetRegMask(WD2_APPLY_SETTINGS_DRS_REG, WD2_APPLY_SETTINGS_DRS_MASK, WD2_APPLY_SETTINGS_DRS_OFS, value);
   };

   unsigned int GetApplySettingsDac() {
      return BitExtractControl(WD2_APPLY_SETTINGS_DAC_REG, WD2_APPLY_SETTINGS_DAC_MASK, WD2_APPLY_SETTINGS_DAC_OFS);
   };

   void SetApplySettingsDac(unsigned int value) {
      SetRegMask(WD2_APPLY_SETTINGS_DAC_REG, WD2_APPLY_SETTINGS_DAC_MASK, WD2_APPLY_SETTINGS_DAC_OFS, value);
   };

   unsigned int GetApplySettingsFrontend() {
      return BitExtractControl(WD2_APPLY_SETTINGS_FRONTEND_REG, WD2_APPLY_SETTINGS_FRONTEND_MASK, WD2_APPLY_SETTINGS_FRONTEND_OFS);
   };

   void SetApplySettingsFrontend(unsigned int value) {
      SetRegMask(WD2_APPLY_SETTINGS_FRONTEND_REG, WD2_APPLY_SETTINGS_FRONTEND_MASK, WD2_APPLY_SETTINGS_FRONTEND_OFS, value);
   };

   unsigned int GetApplySettingsCtrl() {
      return BitExtractControl(WD2_APPLY_SETTINGS_CTRL_REG, WD2_APPLY_SETTINGS_CTRL_MASK, WD2_APPLY_SETTINGS_CTRL_OFS);
   };

   void SetApplySettingsCtrl(unsigned int value) {
      SetRegMask(WD2_APPLY_SETTINGS_CTRL_REG, WD2_APPLY_SETTINGS_CTRL_MASK, WD2_APPLY_SETTINGS_CTRL_OFS, value);
   };

   unsigned int GetApplySettingsAdc() {
      return BitExtractControl(WD2_APPLY_SETTINGS_ADC_REG, WD2_APPLY_SETTINGS_ADC_MASK, WD2_APPLY_SETTINGS_ADC_OFS);
   };

   void SetApplySettingsAdc(unsigned int value) {
      SetRegMask(WD2_APPLY_SETTINGS_ADC_REG, WD2_APPLY_SETTINGS_ADC_MASK, WD2_APPLY_SETTINGS_ADC_OFS, value);
   };

   unsigned int GetApplySettingsLmk() {
      return BitExtractControl(WD2_APPLY_SETTINGS_LMK_REG, WD2_APPLY_SETTINGS_LMK_MASK, WD2_APPLY_SETTINGS_LMK_OFS);
   };

   void SetApplySettingsLmk(unsigned int value) {
      SetRegMask(WD2_APPLY_SETTINGS_LMK_REG, WD2_APPLY_SETTINGS_LMK_MASK, WD2_APPLY_SETTINGS_LMK_OFS, value);
   };


   // Control Register 18: DAC0_A_B (offset 0x1048) 
   unsigned int GetDac0ChA() {
      return BitExtractControl(WD2_DAC0_CH_A_REG, WD2_DAC0_CH_A_MASK, WD2_DAC0_CH_A_OFS);
   };

   void SetDac0ChA(unsigned int value) {
      SetRegMask(WD2_DAC0_CH_A_REG, WD2_DAC0_CH_A_MASK, WD2_DAC0_CH_A_OFS, value);
   };

   unsigned int GetDac0ChB() {
      return BitExtractControl(WD2_DAC0_CH_B_REG, WD2_DAC0_CH_B_MASK, WD2_DAC0_CH_B_OFS);
   };

   void SetDac0ChB(unsigned int value) {
      SetRegMask(WD2_DAC0_CH_B_REG, WD2_DAC0_CH_B_MASK, WD2_DAC0_CH_B_OFS, value);
   };


   // Control Register 19: DAC0_C_D (offset 0x104C) 
   unsigned int GetDac0ChC() {
      return BitExtractControl(WD2_DAC0_CH_C_REG, WD2_DAC0_CH_C_MASK, WD2_DAC0_CH_C_OFS);
   };

   void SetDac0ChC(unsigned int value) {
      SetRegMask(WD2_DAC0_CH_C_REG, WD2_DAC0_CH_C_MASK, WD2_DAC0_CH_C_OFS, value);
   };

   unsigned int GetDac0ChD() {
      return BitExtractControl(WD2_DAC0_CH_D_REG, WD2_DAC0_CH_D_MASK, WD2_DAC0_CH_D_OFS);
   };

   void SetDac0ChD(unsigned int value) {
      SetRegMask(WD2_DAC0_CH_D_REG, WD2_DAC0_CH_D_MASK, WD2_DAC0_CH_D_OFS, value);
   };


   // Control Register 20: DAC0_E_F (offset 0x1050) 
   unsigned int GetDac0ChE() {
      return BitExtractControl(WD2_DAC0_CH_E_REG, WD2_DAC0_CH_E_MASK, WD2_DAC0_CH_E_OFS);
   };

   void SetDac0ChE(unsigned int value) {
      SetRegMask(WD2_DAC0_CH_E_REG, WD2_DAC0_CH_E_MASK, WD2_DAC0_CH_E_OFS, value);
   };

   unsigned int GetDac0ChF() {
      return BitExtractControl(WD2_DAC0_CH_F_REG, WD2_DAC0_CH_F_MASK, WD2_DAC0_CH_F_OFS);
   };

   void SetDac0ChF(unsigned int value) {
      SetRegMask(WD2_DAC0_CH_F_REG, WD2_DAC0_CH_F_MASK, WD2_DAC0_CH_F_OFS, value);
   };


   // Control Register 21: DAC0_G_H (offset 0x1054) 
   unsigned int GetDac0ChG() {
      return BitExtractControl(WD2_DAC0_CH_G_REG, WD2_DAC0_CH_G_MASK, WD2_DAC0_CH_G_OFS);
   };

   void SetDac0ChG(unsigned int value) {
      SetRegMask(WD2_DAC0_CH_G_REG, WD2_DAC0_CH_G_MASK, WD2_DAC0_CH_G_OFS, value);
   };

   unsigned int GetDac0ChH() {
      return BitExtractControl(WD2_DAC0_CH_H_REG, WD2_DAC0_CH_H_MASK, WD2_DAC0_CH_H_OFS);
   };

   void SetDac0ChH(unsigned int value) {
      SetRegMask(WD2_DAC0_CH_H_REG, WD2_DAC0_CH_H_MASK, WD2_DAC0_CH_H_OFS, value);
   };


   // Control Register 22: DAC1_A_B (offset 0x1058) 
   unsigned int GetDac1ChA() {
      return BitExtractControl(WD2_DAC1_CH_A_REG, WD2_DAC1_CH_A_MASK, WD2_DAC1_CH_A_OFS);
   };

   void SetDac1ChA(unsigned int value) {
      SetRegMask(WD2_DAC1_CH_A_REG, WD2_DAC1_CH_A_MASK, WD2_DAC1_CH_A_OFS, value);
   };

   unsigned int GetDac1ChB() {
      return BitExtractControl(WD2_DAC1_CH_B_REG, WD2_DAC1_CH_B_MASK, WD2_DAC1_CH_B_OFS);
   };

   void SetDac1ChB(unsigned int value) {
      SetRegMask(WD2_DAC1_CH_B_REG, WD2_DAC1_CH_B_MASK, WD2_DAC1_CH_B_OFS, value);
   };


   // Control Register 23: DAC1_C_D (offset 0x105C) 
   unsigned int GetDac1ChC() {
      return BitExtractControl(WD2_DAC1_CH_C_REG, WD2_DAC1_CH_C_MASK, WD2_DAC1_CH_C_OFS);
   };

   void SetDac1ChC(unsigned int value) {
      SetRegMask(WD2_DAC1_CH_C_REG, WD2_DAC1_CH_C_MASK, WD2_DAC1_CH_C_OFS, value);
   };

   unsigned int GetDac1ChD() {
      return BitExtractControl(WD2_DAC1_CH_D_REG, WD2_DAC1_CH_D_MASK, WD2_DAC1_CH_D_OFS);
   };

   void SetDac1ChD(unsigned int value) {
      SetRegMask(WD2_DAC1_CH_D_REG, WD2_DAC1_CH_D_MASK, WD2_DAC1_CH_D_OFS, value);
   };


   // Control Register 24: DAC1_E_F (offset 0x1060) 
   unsigned int GetDac1ChE() {
      return BitExtractControl(WD2_DAC1_CH_E_REG, WD2_DAC1_CH_E_MASK, WD2_DAC1_CH_E_OFS);
   };

   void SetDac1ChE(unsigned int value) {
      SetRegMask(WD2_DAC1_CH_E_REG, WD2_DAC1_CH_E_MASK, WD2_DAC1_CH_E_OFS, value);
   };

   unsigned int GetDac1ChF() {
      return BitExtractControl(WD2_DAC1_CH_F_REG, WD2_DAC1_CH_F_MASK, WD2_DAC1_CH_F_OFS);
   };

   void SetDac1ChF(unsigned int value) {
      SetRegMask(WD2_DAC1_CH_F_REG, WD2_DAC1_CH_F_MASK, WD2_DAC1_CH_F_OFS, value);
   };


   // Control Register 25: DAC1_G_H (offset 0x1064) 
   unsigned int GetDac1ChG() {
      return BitExtractControl(WD2_DAC1_CH_G_REG, WD2_DAC1_CH_G_MASK, WD2_DAC1_CH_G_OFS);
   };

   void SetDac1ChG(unsigned int value) {
      SetRegMask(WD2_DAC1_CH_G_REG, WD2_DAC1_CH_G_MASK, WD2_DAC1_CH_G_OFS, value);
   };

   unsigned int GetDac1ChH() {
      return BitExtractControl(WD2_DAC1_CH_H_REG, WD2_DAC1_CH_H_MASK, WD2_DAC1_CH_H_OFS);
   };

   void SetDac1ChH(unsigned int value) {
      SetRegMask(WD2_DAC1_CH_H_REG, WD2_DAC1_CH_H_MASK, WD2_DAC1_CH_H_OFS, value);
   };


   // Control Register 26: DAC2_A_B (offset 0x1068) 
   unsigned int GetDac2ChA() {
      return BitExtractControl(WD2_DAC2_CH_A_REG, WD2_DAC2_CH_A_MASK, WD2_DAC2_CH_A_OFS);
   };

   void SetDac2ChA(unsigned int value) {
      SetRegMask(WD2_DAC2_CH_A_REG, WD2_DAC2_CH_A_MASK, WD2_DAC2_CH_A_OFS, value);
   };

   unsigned int GetDac2ChB() {
      return BitExtractControl(WD2_DAC2_CH_B_REG, WD2_DAC2_CH_B_MASK, WD2_DAC2_CH_B_OFS);
   };

   void SetDac2ChB(unsigned int value) {
      SetRegMask(WD2_DAC2_CH_B_REG, WD2_DAC2_CH_B_MASK, WD2_DAC2_CH_B_OFS, value);
   };


   // Control Register 27: DAC2_C_D (offset 0x106C) 
   unsigned int GetDac2ChC() {
      return BitExtractControl(WD2_DAC2_CH_C_REG, WD2_DAC2_CH_C_MASK, WD2_DAC2_CH_C_OFS);
   };

   void SetDac2ChC(unsigned int value) {
      SetRegMask(WD2_DAC2_CH_C_REG, WD2_DAC2_CH_C_MASK, WD2_DAC2_CH_C_OFS, value);
   };

   unsigned int GetDac2ChD() {
      return BitExtractControl(WD2_DAC2_CH_D_REG, WD2_DAC2_CH_D_MASK, WD2_DAC2_CH_D_OFS);
   };

   void SetDac2ChD(unsigned int value) {
      SetRegMask(WD2_DAC2_CH_D_REG, WD2_DAC2_CH_D_MASK, WD2_DAC2_CH_D_OFS, value);
   };


   // Control Register 28: DAC2_E_F (offset 0x1070) 
   unsigned int GetDac2ChE() {
      return BitExtractControl(WD2_DAC2_CH_E_REG, WD2_DAC2_CH_E_MASK, WD2_DAC2_CH_E_OFS);
   };

   void SetDac2ChE(unsigned int value) {
      SetRegMask(WD2_DAC2_CH_E_REG, WD2_DAC2_CH_E_MASK, WD2_DAC2_CH_E_OFS, value);
   };

   unsigned int GetDac2ChF() {
      return BitExtractControl(WD2_DAC2_CH_F_REG, WD2_DAC2_CH_F_MASK, WD2_DAC2_CH_F_OFS);
   };

   void SetDac2ChF(unsigned int value) {
      SetRegMask(WD2_DAC2_CH_F_REG, WD2_DAC2_CH_F_MASK, WD2_DAC2_CH_F_OFS, value);
   };


   // Control Register 29: DAC2_G_H (offset 0x1074) 
   unsigned int GetDac2ChG() {
      return BitExtractControl(WD2_DAC2_CH_G_REG, WD2_DAC2_CH_G_MASK, WD2_DAC2_CH_G_OFS);
   };

   void SetDac2ChG(unsigned int value) {
      SetRegMask(WD2_DAC2_CH_G_REG, WD2_DAC2_CH_G_MASK, WD2_DAC2_CH_G_OFS, value);
   };

   unsigned int GetDac2ChH() {
      return BitExtractControl(WD2_DAC2_CH_H_REG, WD2_DAC2_CH_H_MASK, WD2_DAC2_CH_H_OFS);
   };

   void SetDac2ChH(unsigned int value) {
      SetRegMask(WD2_DAC2_CH_H_REG, WD2_DAC2_CH_H_MASK, WD2_DAC2_CH_H_OFS, value);
   };


   // Control Register 30: FE_CFG_0_1 (offset 0x1078) 
   unsigned int GetFe0PzcEn() {
      return BitExtractControl(WD2_FE0_PZC_EN_REG, WD2_FE0_PZC_EN_MASK, WD2_FE0_PZC_EN_OFS);
   };

   void SetFe0PzcEn(unsigned int value) {
      SetRegMask(WD2_FE0_PZC_EN_REG, WD2_FE0_PZC_EN_MASK, WD2_FE0_PZC_EN_OFS, value);
   };

   unsigned int GetFe0Amplifier2CompEn() {
      return BitExtractControl(WD2_FE0_AMPLIFIER2_COMP_EN_REG, WD2_FE0_AMPLIFIER2_COMP_EN_MASK, WD2_FE0_AMPLIFIER2_COMP_EN_OFS);
   };

   void SetFe0Amplifier2CompEn(unsigned int value) {
      SetRegMask(WD2_FE0_AMPLIFIER2_COMP_EN_REG, WD2_FE0_AMPLIFIER2_COMP_EN_MASK, WD2_FE0_AMPLIFIER2_COMP_EN_OFS, value);
   };

   unsigned int GetFe0Amplifier2En() {
      return BitExtractControl(WD2_FE0_AMPLIFIER2_EN_REG, WD2_FE0_AMPLIFIER2_EN_MASK, WD2_FE0_AMPLIFIER2_EN_OFS);
   };

   void SetFe0Amplifier2En(unsigned int value) {
      SetRegMask(WD2_FE0_AMPLIFIER2_EN_REG, WD2_FE0_AMPLIFIER2_EN_MASK, WD2_FE0_AMPLIFIER2_EN_OFS, value);
   };

   unsigned int GetFe0Amplifier1CompEn() {
      return BitExtractControl(WD2_FE0_AMPLIFIER1_COMP_EN_REG, WD2_FE0_AMPLIFIER1_COMP_EN_MASK, WD2_FE0_AMPLIFIER1_COMP_EN_OFS);
   };

   void SetFe0Amplifier1CompEn(unsigned int value) {
      SetRegMask(WD2_FE0_AMPLIFIER1_COMP_EN_REG, WD2_FE0_AMPLIFIER1_COMP_EN_MASK, WD2_FE0_AMPLIFIER1_COMP_EN_OFS, value);
   };

   unsigned int GetFe0Amplifier1En() {
      return BitExtractControl(WD2_FE0_AMPLIFIER1_EN_REG, WD2_FE0_AMPLIFIER1_EN_MASK, WD2_FE0_AMPLIFIER1_EN_OFS);
   };

   void SetFe0Amplifier1En(unsigned int value) {
      SetRegMask(WD2_FE0_AMPLIFIER1_EN_REG, WD2_FE0_AMPLIFIER1_EN_MASK, WD2_FE0_AMPLIFIER1_EN_OFS, value);
   };

   unsigned int GetFe0Attenuation() {
      return BitExtractControl(WD2_FE0_ATTENUATION_REG, WD2_FE0_ATTENUATION_MASK, WD2_FE0_ATTENUATION_OFS);
   };

   void SetFe0Attenuation(unsigned int value) {
      SetRegMask(WD2_FE0_ATTENUATION_REG, WD2_FE0_ATTENUATION_MASK, WD2_FE0_ATTENUATION_OFS, value);
   };

   unsigned int GetFe0Mux() {
      return BitExtractControl(WD2_FE0_MUX_REG, WD2_FE0_MUX_MASK, WD2_FE0_MUX_OFS);
   };

   void SetFe0Mux(unsigned int value) {
      SetRegMask(WD2_FE0_MUX_REG, WD2_FE0_MUX_MASK, WD2_FE0_MUX_OFS, value);
   };

   unsigned int GetFe1PzcEn() {
      return BitExtractControl(WD2_FE1_PZC_EN_REG, WD2_FE1_PZC_EN_MASK, WD2_FE1_PZC_EN_OFS);
   };

   void SetFe1PzcEn(unsigned int value) {
      SetRegMask(WD2_FE1_PZC_EN_REG, WD2_FE1_PZC_EN_MASK, WD2_FE1_PZC_EN_OFS, value);
   };

   unsigned int GetFe1Amplifier2CompEn() {
      return BitExtractControl(WD2_FE1_AMPLIFIER2_COMP_EN_REG, WD2_FE1_AMPLIFIER2_COMP_EN_MASK, WD2_FE1_AMPLIFIER2_COMP_EN_OFS);
   };

   void SetFe1Amplifier2CompEn(unsigned int value) {
      SetRegMask(WD2_FE1_AMPLIFIER2_COMP_EN_REG, WD2_FE1_AMPLIFIER2_COMP_EN_MASK, WD2_FE1_AMPLIFIER2_COMP_EN_OFS, value);
   };

   unsigned int GetFe1Amplifier2En() {
      return BitExtractControl(WD2_FE1_AMPLIFIER2_EN_REG, WD2_FE1_AMPLIFIER2_EN_MASK, WD2_FE1_AMPLIFIER2_EN_OFS);
   };

   void SetFe1Amplifier2En(unsigned int value) {
      SetRegMask(WD2_FE1_AMPLIFIER2_EN_REG, WD2_FE1_AMPLIFIER2_EN_MASK, WD2_FE1_AMPLIFIER2_EN_OFS, value);
   };

   unsigned int GetFe1Amplifier1CompEn() {
      return BitExtractControl(WD2_FE1_AMPLIFIER1_COMP_EN_REG, WD2_FE1_AMPLIFIER1_COMP_EN_MASK, WD2_FE1_AMPLIFIER1_COMP_EN_OFS);
   };

   void SetFe1Amplifier1CompEn(unsigned int value) {
      SetRegMask(WD2_FE1_AMPLIFIER1_COMP_EN_REG, WD2_FE1_AMPLIFIER1_COMP_EN_MASK, WD2_FE1_AMPLIFIER1_COMP_EN_OFS, value);
   };

   unsigned int GetFe1Amplifier1En() {
      return BitExtractControl(WD2_FE1_AMPLIFIER1_EN_REG, WD2_FE1_AMPLIFIER1_EN_MASK, WD2_FE1_AMPLIFIER1_EN_OFS);
   };

   void SetFe1Amplifier1En(unsigned int value) {
      SetRegMask(WD2_FE1_AMPLIFIER1_EN_REG, WD2_FE1_AMPLIFIER1_EN_MASK, WD2_FE1_AMPLIFIER1_EN_OFS, value);
   };

   unsigned int GetFe1Attenuation() {
      return BitExtractControl(WD2_FE1_ATTENUATION_REG, WD2_FE1_ATTENUATION_MASK, WD2_FE1_ATTENUATION_OFS);
   };

   void SetFe1Attenuation(unsigned int value) {
      SetRegMask(WD2_FE1_ATTENUATION_REG, WD2_FE1_ATTENUATION_MASK, WD2_FE1_ATTENUATION_OFS, value);
   };

   unsigned int GetFe1Mux() {
      return BitExtractControl(WD2_FE1_MUX_REG, WD2_FE1_MUX_MASK, WD2_FE1_MUX_OFS);
   };

   void SetFe1Mux(unsigned int value) {
      SetRegMask(WD2_FE1_MUX_REG, WD2_FE1_MUX_MASK, WD2_FE1_MUX_OFS, value);
   };


   // Control Register 31: FE_CFG_2_3 (offset 0x107C) 
   unsigned int GetFe2PzcEn() {
      return BitExtractControl(WD2_FE2_PZC_EN_REG, WD2_FE2_PZC_EN_MASK, WD2_FE2_PZC_EN_OFS);
   };

   void SetFe2PzcEn(unsigned int value) {
      SetRegMask(WD2_FE2_PZC_EN_REG, WD2_FE2_PZC_EN_MASK, WD2_FE2_PZC_EN_OFS, value);
   };

   unsigned int GetFe2Amplifier2CompEn() {
      return BitExtractControl(WD2_FE2_AMPLIFIER2_COMP_EN_REG, WD2_FE2_AMPLIFIER2_COMP_EN_MASK, WD2_FE2_AMPLIFIER2_COMP_EN_OFS);
   };

   void SetFe2Amplifier2CompEn(unsigned int value) {
      SetRegMask(WD2_FE2_AMPLIFIER2_COMP_EN_REG, WD2_FE2_AMPLIFIER2_COMP_EN_MASK, WD2_FE2_AMPLIFIER2_COMP_EN_OFS, value);
   };

   unsigned int GetFe2Amplifier2En() {
      return BitExtractControl(WD2_FE2_AMPLIFIER2_EN_REG, WD2_FE2_AMPLIFIER2_EN_MASK, WD2_FE2_AMPLIFIER2_EN_OFS);
   };

   void SetFe2Amplifier2En(unsigned int value) {
      SetRegMask(WD2_FE2_AMPLIFIER2_EN_REG, WD2_FE2_AMPLIFIER2_EN_MASK, WD2_FE2_AMPLIFIER2_EN_OFS, value);
   };

   unsigned int GetFe2Amplifier1CompEn() {
      return BitExtractControl(WD2_FE2_AMPLIFIER1_COMP_EN_REG, WD2_FE2_AMPLIFIER1_COMP_EN_MASK, WD2_FE2_AMPLIFIER1_COMP_EN_OFS);
   };

   void SetFe2Amplifier1CompEn(unsigned int value) {
      SetRegMask(WD2_FE2_AMPLIFIER1_COMP_EN_REG, WD2_FE2_AMPLIFIER1_COMP_EN_MASK, WD2_FE2_AMPLIFIER1_COMP_EN_OFS, value);
   };

   unsigned int GetFe2Amplifier1En() {
      return BitExtractControl(WD2_FE2_AMPLIFIER1_EN_REG, WD2_FE2_AMPLIFIER1_EN_MASK, WD2_FE2_AMPLIFIER1_EN_OFS);
   };

   void SetFe2Amplifier1En(unsigned int value) {
      SetRegMask(WD2_FE2_AMPLIFIER1_EN_REG, WD2_FE2_AMPLIFIER1_EN_MASK, WD2_FE2_AMPLIFIER1_EN_OFS, value);
   };

   unsigned int GetFe2Attenuation() {
      return BitExtractControl(WD2_FE2_ATTENUATION_REG, WD2_FE2_ATTENUATION_MASK, WD2_FE2_ATTENUATION_OFS);
   };

   void SetFe2Attenuation(unsigned int value) {
      SetRegMask(WD2_FE2_ATTENUATION_REG, WD2_FE2_ATTENUATION_MASK, WD2_FE2_ATTENUATION_OFS, value);
   };

   unsigned int GetFe2Mux() {
      return BitExtractControl(WD2_FE2_MUX_REG, WD2_FE2_MUX_MASK, WD2_FE2_MUX_OFS);
   };

   void SetFe2Mux(unsigned int value) {
      SetRegMask(WD2_FE2_MUX_REG, WD2_FE2_MUX_MASK, WD2_FE2_MUX_OFS, value);
   };

   unsigned int GetFe3PzcEn() {
      return BitExtractControl(WD2_FE3_PZC_EN_REG, WD2_FE3_PZC_EN_MASK, WD2_FE3_PZC_EN_OFS);
   };

   void SetFe3PzcEn(unsigned int value) {
      SetRegMask(WD2_FE3_PZC_EN_REG, WD2_FE3_PZC_EN_MASK, WD2_FE3_PZC_EN_OFS, value);
   };

   unsigned int GetFe3Amplifier2CompEn() {
      return BitExtractControl(WD2_FE3_AMPLIFIER2_COMP_EN_REG, WD2_FE3_AMPLIFIER2_COMP_EN_MASK, WD2_FE3_AMPLIFIER2_COMP_EN_OFS);
   };

   void SetFe3Amplifier2CompEn(unsigned int value) {
      SetRegMask(WD2_FE3_AMPLIFIER2_COMP_EN_REG, WD2_FE3_AMPLIFIER2_COMP_EN_MASK, WD2_FE3_AMPLIFIER2_COMP_EN_OFS, value);
   };

   unsigned int GetFe3Amplifier2En() {
      return BitExtractControl(WD2_FE3_AMPLIFIER2_EN_REG, WD2_FE3_AMPLIFIER2_EN_MASK, WD2_FE3_AMPLIFIER2_EN_OFS);
   };

   void SetFe3Amplifier2En(unsigned int value) {
      SetRegMask(WD2_FE3_AMPLIFIER2_EN_REG, WD2_FE3_AMPLIFIER2_EN_MASK, WD2_FE3_AMPLIFIER2_EN_OFS, value);
   };

   unsigned int GetFe3Amplifier1CompEn() {
      return BitExtractControl(WD2_FE3_AMPLIFIER1_COMP_EN_REG, WD2_FE3_AMPLIFIER1_COMP_EN_MASK, WD2_FE3_AMPLIFIER1_COMP_EN_OFS);
   };

   void SetFe3Amplifier1CompEn(unsigned int value) {
      SetRegMask(WD2_FE3_AMPLIFIER1_COMP_EN_REG, WD2_FE3_AMPLIFIER1_COMP_EN_MASK, WD2_FE3_AMPLIFIER1_COMP_EN_OFS, value);
   };

   unsigned int GetFe3Amplifier1En() {
      return BitExtractControl(WD2_FE3_AMPLIFIER1_EN_REG, WD2_FE3_AMPLIFIER1_EN_MASK, WD2_FE3_AMPLIFIER1_EN_OFS);
   };

   void SetFe3Amplifier1En(unsigned int value) {
      SetRegMask(WD2_FE3_AMPLIFIER1_EN_REG, WD2_FE3_AMPLIFIER1_EN_MASK, WD2_FE3_AMPLIFIER1_EN_OFS, value);
   };

   unsigned int GetFe3Attenuation() {
      return BitExtractControl(WD2_FE3_ATTENUATION_REG, WD2_FE3_ATTENUATION_MASK, WD2_FE3_ATTENUATION_OFS);
   };

   void SetFe3Attenuation(unsigned int value) {
      SetRegMask(WD2_FE3_ATTENUATION_REG, WD2_FE3_ATTENUATION_MASK, WD2_FE3_ATTENUATION_OFS, value);
   };

   unsigned int GetFe3Mux() {
      return BitExtractControl(WD2_FE3_MUX_REG, WD2_FE3_MUX_MASK, WD2_FE3_MUX_OFS);
   };

   void SetFe3Mux(unsigned int value) {
      SetRegMask(WD2_FE3_MUX_REG, WD2_FE3_MUX_MASK, WD2_FE3_MUX_OFS, value);
   };


   // Control Register 32: FE_CFG_4_5 (offset 0x1080) 
   unsigned int GetFe4PzcEn() {
      return BitExtractControl(WD2_FE4_PZC_EN_REG, WD2_FE4_PZC_EN_MASK, WD2_FE4_PZC_EN_OFS);
   };

   void SetFe4PzcEn(unsigned int value) {
      SetRegMask(WD2_FE4_PZC_EN_REG, WD2_FE4_PZC_EN_MASK, WD2_FE4_PZC_EN_OFS, value);
   };

   unsigned int GetFe4Amplifier2CompEn() {
      return BitExtractControl(WD2_FE4_AMPLIFIER2_COMP_EN_REG, WD2_FE4_AMPLIFIER2_COMP_EN_MASK, WD2_FE4_AMPLIFIER2_COMP_EN_OFS);
   };

   void SetFe4Amplifier2CompEn(unsigned int value) {
      SetRegMask(WD2_FE4_AMPLIFIER2_COMP_EN_REG, WD2_FE4_AMPLIFIER2_COMP_EN_MASK, WD2_FE4_AMPLIFIER2_COMP_EN_OFS, value);
   };

   unsigned int GetFe4Amplifier2En() {
      return BitExtractControl(WD2_FE4_AMPLIFIER2_EN_REG, WD2_FE4_AMPLIFIER2_EN_MASK, WD2_FE4_AMPLIFIER2_EN_OFS);
   };

   void SetFe4Amplifier2En(unsigned int value) {
      SetRegMask(WD2_FE4_AMPLIFIER2_EN_REG, WD2_FE4_AMPLIFIER2_EN_MASK, WD2_FE4_AMPLIFIER2_EN_OFS, value);
   };

   unsigned int GetFe4Amplifier1CompEn() {
      return BitExtractControl(WD2_FE4_AMPLIFIER1_COMP_EN_REG, WD2_FE4_AMPLIFIER1_COMP_EN_MASK, WD2_FE4_AMPLIFIER1_COMP_EN_OFS);
   };

   void SetFe4Amplifier1CompEn(unsigned int value) {
      SetRegMask(WD2_FE4_AMPLIFIER1_COMP_EN_REG, WD2_FE4_AMPLIFIER1_COMP_EN_MASK, WD2_FE4_AMPLIFIER1_COMP_EN_OFS, value);
   };

   unsigned int GetFe4Amplifier1En() {
      return BitExtractControl(WD2_FE4_AMPLIFIER1_EN_REG, WD2_FE4_AMPLIFIER1_EN_MASK, WD2_FE4_AMPLIFIER1_EN_OFS);
   };

   void SetFe4Amplifier1En(unsigned int value) {
      SetRegMask(WD2_FE4_AMPLIFIER1_EN_REG, WD2_FE4_AMPLIFIER1_EN_MASK, WD2_FE4_AMPLIFIER1_EN_OFS, value);
   };

   unsigned int GetFe4Attenuation() {
      return BitExtractControl(WD2_FE4_ATTENUATION_REG, WD2_FE4_ATTENUATION_MASK, WD2_FE4_ATTENUATION_OFS);
   };

   void SetFe4Attenuation(unsigned int value) {
      SetRegMask(WD2_FE4_ATTENUATION_REG, WD2_FE4_ATTENUATION_MASK, WD2_FE4_ATTENUATION_OFS, value);
   };

   unsigned int GetFe4Mux() {
      return BitExtractControl(WD2_FE4_MUX_REG, WD2_FE4_MUX_MASK, WD2_FE4_MUX_OFS);
   };

   void SetFe4Mux(unsigned int value) {
      SetRegMask(WD2_FE4_MUX_REG, WD2_FE4_MUX_MASK, WD2_FE4_MUX_OFS, value);
   };

   unsigned int GetFe5PzcEn() {
      return BitExtractControl(WD2_FE5_PZC_EN_REG, WD2_FE5_PZC_EN_MASK, WD2_FE5_PZC_EN_OFS);
   };

   void SetFe5PzcEn(unsigned int value) {
      SetRegMask(WD2_FE5_PZC_EN_REG, WD2_FE5_PZC_EN_MASK, WD2_FE5_PZC_EN_OFS, value);
   };

   unsigned int GetFe5Amplifier2CompEn() {
      return BitExtractControl(WD2_FE5_AMPLIFIER2_COMP_EN_REG, WD2_FE5_AMPLIFIER2_COMP_EN_MASK, WD2_FE5_AMPLIFIER2_COMP_EN_OFS);
   };

   void SetFe5Amplifier2CompEn(unsigned int value) {
      SetRegMask(WD2_FE5_AMPLIFIER2_COMP_EN_REG, WD2_FE5_AMPLIFIER2_COMP_EN_MASK, WD2_FE5_AMPLIFIER2_COMP_EN_OFS, value);
   };

   unsigned int GetFe5Amplifier2En() {
      return BitExtractControl(WD2_FE5_AMPLIFIER2_EN_REG, WD2_FE5_AMPLIFIER2_EN_MASK, WD2_FE5_AMPLIFIER2_EN_OFS);
   };

   void SetFe5Amplifier2En(unsigned int value) {
      SetRegMask(WD2_FE5_AMPLIFIER2_EN_REG, WD2_FE5_AMPLIFIER2_EN_MASK, WD2_FE5_AMPLIFIER2_EN_OFS, value);
   };

   unsigned int GetFe5Amplifier1CompEn() {
      return BitExtractControl(WD2_FE5_AMPLIFIER1_COMP_EN_REG, WD2_FE5_AMPLIFIER1_COMP_EN_MASK, WD2_FE5_AMPLIFIER1_COMP_EN_OFS);
   };

   void SetFe5Amplifier1CompEn(unsigned int value) {
      SetRegMask(WD2_FE5_AMPLIFIER1_COMP_EN_REG, WD2_FE5_AMPLIFIER1_COMP_EN_MASK, WD2_FE5_AMPLIFIER1_COMP_EN_OFS, value);
   };

   unsigned int GetFe5Amplifier1En() {
      return BitExtractControl(WD2_FE5_AMPLIFIER1_EN_REG, WD2_FE5_AMPLIFIER1_EN_MASK, WD2_FE5_AMPLIFIER1_EN_OFS);
   };

   void SetFe5Amplifier1En(unsigned int value) {
      SetRegMask(WD2_FE5_AMPLIFIER1_EN_REG, WD2_FE5_AMPLIFIER1_EN_MASK, WD2_FE5_AMPLIFIER1_EN_OFS, value);
   };

   unsigned int GetFe5Attenuation() {
      return BitExtractControl(WD2_FE5_ATTENUATION_REG, WD2_FE5_ATTENUATION_MASK, WD2_FE5_ATTENUATION_OFS);
   };

   void SetFe5Attenuation(unsigned int value) {
      SetRegMask(WD2_FE5_ATTENUATION_REG, WD2_FE5_ATTENUATION_MASK, WD2_FE5_ATTENUATION_OFS, value);
   };

   unsigned int GetFe5Mux() {
      return BitExtractControl(WD2_FE5_MUX_REG, WD2_FE5_MUX_MASK, WD2_FE5_MUX_OFS);
   };

   void SetFe5Mux(unsigned int value) {
      SetRegMask(WD2_FE5_MUX_REG, WD2_FE5_MUX_MASK, WD2_FE5_MUX_OFS, value);
   };


   // Control Register 33: FE_CFG_6_7 (offset 0x1084) 
   unsigned int GetFe6PzcEn() {
      return BitExtractControl(WD2_FE6_PZC_EN_REG, WD2_FE6_PZC_EN_MASK, WD2_FE6_PZC_EN_OFS);
   };

   void SetFe6PzcEn(unsigned int value) {
      SetRegMask(WD2_FE6_PZC_EN_REG, WD2_FE6_PZC_EN_MASK, WD2_FE6_PZC_EN_OFS, value);
   };

   unsigned int GetFe6Amplifier2CompEn() {
      return BitExtractControl(WD2_FE6_AMPLIFIER2_COMP_EN_REG, WD2_FE6_AMPLIFIER2_COMP_EN_MASK, WD2_FE6_AMPLIFIER2_COMP_EN_OFS);
   };

   void SetFe6Amplifier2CompEn(unsigned int value) {
      SetRegMask(WD2_FE6_AMPLIFIER2_COMP_EN_REG, WD2_FE6_AMPLIFIER2_COMP_EN_MASK, WD2_FE6_AMPLIFIER2_COMP_EN_OFS, value);
   };

   unsigned int GetFe6Amplifier2En() {
      return BitExtractControl(WD2_FE6_AMPLIFIER2_EN_REG, WD2_FE6_AMPLIFIER2_EN_MASK, WD2_FE6_AMPLIFIER2_EN_OFS);
   };

   void SetFe6Amplifier2En(unsigned int value) {
      SetRegMask(WD2_FE6_AMPLIFIER2_EN_REG, WD2_FE6_AMPLIFIER2_EN_MASK, WD2_FE6_AMPLIFIER2_EN_OFS, value);
   };

   unsigned int GetFe6Amplifier1CompEn() {
      return BitExtractControl(WD2_FE6_AMPLIFIER1_COMP_EN_REG, WD2_FE6_AMPLIFIER1_COMP_EN_MASK, WD2_FE6_AMPLIFIER1_COMP_EN_OFS);
   };

   void SetFe6Amplifier1CompEn(unsigned int value) {
      SetRegMask(WD2_FE6_AMPLIFIER1_COMP_EN_REG, WD2_FE6_AMPLIFIER1_COMP_EN_MASK, WD2_FE6_AMPLIFIER1_COMP_EN_OFS, value);
   };

   unsigned int GetFe6Amplifier1En() {
      return BitExtractControl(WD2_FE6_AMPLIFIER1_EN_REG, WD2_FE6_AMPLIFIER1_EN_MASK, WD2_FE6_AMPLIFIER1_EN_OFS);
   };

   void SetFe6Amplifier1En(unsigned int value) {
      SetRegMask(WD2_FE6_AMPLIFIER1_EN_REG, WD2_FE6_AMPLIFIER1_EN_MASK, WD2_FE6_AMPLIFIER1_EN_OFS, value);
   };

   unsigned int GetFe6Attenuation() {
      return BitExtractControl(WD2_FE6_ATTENUATION_REG, WD2_FE6_ATTENUATION_MASK, WD2_FE6_ATTENUATION_OFS);
   };

   void SetFe6Attenuation(unsigned int value) {
      SetRegMask(WD2_FE6_ATTENUATION_REG, WD2_FE6_ATTENUATION_MASK, WD2_FE6_ATTENUATION_OFS, value);
   };

   unsigned int GetFe6Mux() {
      return BitExtractControl(WD2_FE6_MUX_REG, WD2_FE6_MUX_MASK, WD2_FE6_MUX_OFS);
   };

   void SetFe6Mux(unsigned int value) {
      SetRegMask(WD2_FE6_MUX_REG, WD2_FE6_MUX_MASK, WD2_FE6_MUX_OFS, value);
   };

   unsigned int GetFe7PzcEn() {
      return BitExtractControl(WD2_FE7_PZC_EN_REG, WD2_FE7_PZC_EN_MASK, WD2_FE7_PZC_EN_OFS);
   };

   void SetFe7PzcEn(unsigned int value) {
      SetRegMask(WD2_FE7_PZC_EN_REG, WD2_FE7_PZC_EN_MASK, WD2_FE7_PZC_EN_OFS, value);
   };

   unsigned int GetFe7Amplifier2CompEn() {
      return BitExtractControl(WD2_FE7_AMPLIFIER2_COMP_EN_REG, WD2_FE7_AMPLIFIER2_COMP_EN_MASK, WD2_FE7_AMPLIFIER2_COMP_EN_OFS);
   };

   void SetFe7Amplifier2CompEn(unsigned int value) {
      SetRegMask(WD2_FE7_AMPLIFIER2_COMP_EN_REG, WD2_FE7_AMPLIFIER2_COMP_EN_MASK, WD2_FE7_AMPLIFIER2_COMP_EN_OFS, value);
   };

   unsigned int GetFe7Amplifier2En() {
      return BitExtractControl(WD2_FE7_AMPLIFIER2_EN_REG, WD2_FE7_AMPLIFIER2_EN_MASK, WD2_FE7_AMPLIFIER2_EN_OFS);
   };

   void SetFe7Amplifier2En(unsigned int value) {
      SetRegMask(WD2_FE7_AMPLIFIER2_EN_REG, WD2_FE7_AMPLIFIER2_EN_MASK, WD2_FE7_AMPLIFIER2_EN_OFS, value);
   };

   unsigned int GetFe7Amplifier1CompEn() {
      return BitExtractControl(WD2_FE7_AMPLIFIER1_COMP_EN_REG, WD2_FE7_AMPLIFIER1_COMP_EN_MASK, WD2_FE7_AMPLIFIER1_COMP_EN_OFS);
   };

   void SetFe7Amplifier1CompEn(unsigned int value) {
      SetRegMask(WD2_FE7_AMPLIFIER1_COMP_EN_REG, WD2_FE7_AMPLIFIER1_COMP_EN_MASK, WD2_FE7_AMPLIFIER1_COMP_EN_OFS, value);
   };

   unsigned int GetFe7Amplifier1En() {
      return BitExtractControl(WD2_FE7_AMPLIFIER1_EN_REG, WD2_FE7_AMPLIFIER1_EN_MASK, WD2_FE7_AMPLIFIER1_EN_OFS);
   };

   void SetFe7Amplifier1En(unsigned int value) {
      SetRegMask(WD2_FE7_AMPLIFIER1_EN_REG, WD2_FE7_AMPLIFIER1_EN_MASK, WD2_FE7_AMPLIFIER1_EN_OFS, value);
   };

   unsigned int GetFe7Attenuation() {
      return BitExtractControl(WD2_FE7_ATTENUATION_REG, WD2_FE7_ATTENUATION_MASK, WD2_FE7_ATTENUATION_OFS);
   };

   void SetFe7Attenuation(unsigned int value) {
      SetRegMask(WD2_FE7_ATTENUATION_REG, WD2_FE7_ATTENUATION_MASK, WD2_FE7_ATTENUATION_OFS, value);
   };

   unsigned int GetFe7Mux() {
      return BitExtractControl(WD2_FE7_MUX_REG, WD2_FE7_MUX_MASK, WD2_FE7_MUX_OFS);
   };

   void SetFe7Mux(unsigned int value) {
      SetRegMask(WD2_FE7_MUX_REG, WD2_FE7_MUX_MASK, WD2_FE7_MUX_OFS, value);
   };


   // Control Register 34: FE_CFG_8_9 (offset 0x1088) 
   unsigned int GetFe8PzcEn() {
      return BitExtractControl(WD2_FE8_PZC_EN_REG, WD2_FE8_PZC_EN_MASK, WD2_FE8_PZC_EN_OFS);
   };

   void SetFe8PzcEn(unsigned int value) {
      SetRegMask(WD2_FE8_PZC_EN_REG, WD2_FE8_PZC_EN_MASK, WD2_FE8_PZC_EN_OFS, value);
   };

   unsigned int GetFe8Amplifier2CompEn() {
      return BitExtractControl(WD2_FE8_AMPLIFIER2_COMP_EN_REG, WD2_FE8_AMPLIFIER2_COMP_EN_MASK, WD2_FE8_AMPLIFIER2_COMP_EN_OFS);
   };

   void SetFe8Amplifier2CompEn(unsigned int value) {
      SetRegMask(WD2_FE8_AMPLIFIER2_COMP_EN_REG, WD2_FE8_AMPLIFIER2_COMP_EN_MASK, WD2_FE8_AMPLIFIER2_COMP_EN_OFS, value);
   };

   unsigned int GetFe8Amplifier2En() {
      return BitExtractControl(WD2_FE8_AMPLIFIER2_EN_REG, WD2_FE8_AMPLIFIER2_EN_MASK, WD2_FE8_AMPLIFIER2_EN_OFS);
   };

   void SetFe8Amplifier2En(unsigned int value) {
      SetRegMask(WD2_FE8_AMPLIFIER2_EN_REG, WD2_FE8_AMPLIFIER2_EN_MASK, WD2_FE8_AMPLIFIER2_EN_OFS, value);
   };

   unsigned int GetFe8Amplifier1CompEn() {
      return BitExtractControl(WD2_FE8_AMPLIFIER1_COMP_EN_REG, WD2_FE8_AMPLIFIER1_COMP_EN_MASK, WD2_FE8_AMPLIFIER1_COMP_EN_OFS);
   };

   void SetFe8Amplifier1CompEn(unsigned int value) {
      SetRegMask(WD2_FE8_AMPLIFIER1_COMP_EN_REG, WD2_FE8_AMPLIFIER1_COMP_EN_MASK, WD2_FE8_AMPLIFIER1_COMP_EN_OFS, value);
   };

   unsigned int GetFe8Amplifier1En() {
      return BitExtractControl(WD2_FE8_AMPLIFIER1_EN_REG, WD2_FE8_AMPLIFIER1_EN_MASK, WD2_FE8_AMPLIFIER1_EN_OFS);
   };

   void SetFe8Amplifier1En(unsigned int value) {
      SetRegMask(WD2_FE8_AMPLIFIER1_EN_REG, WD2_FE8_AMPLIFIER1_EN_MASK, WD2_FE8_AMPLIFIER1_EN_OFS, value);
   };

   unsigned int GetFe8Attenuation() {
      return BitExtractControl(WD2_FE8_ATTENUATION_REG, WD2_FE8_ATTENUATION_MASK, WD2_FE8_ATTENUATION_OFS);
   };

   void SetFe8Attenuation(unsigned int value) {
      SetRegMask(WD2_FE8_ATTENUATION_REG, WD2_FE8_ATTENUATION_MASK, WD2_FE8_ATTENUATION_OFS, value);
   };

   unsigned int GetFe8Mux() {
      return BitExtractControl(WD2_FE8_MUX_REG, WD2_FE8_MUX_MASK, WD2_FE8_MUX_OFS);
   };

   void SetFe8Mux(unsigned int value) {
      SetRegMask(WD2_FE8_MUX_REG, WD2_FE8_MUX_MASK, WD2_FE8_MUX_OFS, value);
   };

   unsigned int GetFe9PzcEn() {
      return BitExtractControl(WD2_FE9_PZC_EN_REG, WD2_FE9_PZC_EN_MASK, WD2_FE9_PZC_EN_OFS);
   };

   void SetFe9PzcEn(unsigned int value) {
      SetRegMask(WD2_FE9_PZC_EN_REG, WD2_FE9_PZC_EN_MASK, WD2_FE9_PZC_EN_OFS, value);
   };

   unsigned int GetFe9Amplifier2CompEn() {
      return BitExtractControl(WD2_FE9_AMPLIFIER2_COMP_EN_REG, WD2_FE9_AMPLIFIER2_COMP_EN_MASK, WD2_FE9_AMPLIFIER2_COMP_EN_OFS);
   };

   void SetFe9Amplifier2CompEn(unsigned int value) {
      SetRegMask(WD2_FE9_AMPLIFIER2_COMP_EN_REG, WD2_FE9_AMPLIFIER2_COMP_EN_MASK, WD2_FE9_AMPLIFIER2_COMP_EN_OFS, value);
   };

   unsigned int GetFe9Amplifier2En() {
      return BitExtractControl(WD2_FE9_AMPLIFIER2_EN_REG, WD2_FE9_AMPLIFIER2_EN_MASK, WD2_FE9_AMPLIFIER2_EN_OFS);
   };

   void SetFe9Amplifier2En(unsigned int value) {
      SetRegMask(WD2_FE9_AMPLIFIER2_EN_REG, WD2_FE9_AMPLIFIER2_EN_MASK, WD2_FE9_AMPLIFIER2_EN_OFS, value);
   };

   unsigned int GetFe9Amplifier1CompEn() {
      return BitExtractControl(WD2_FE9_AMPLIFIER1_COMP_EN_REG, WD2_FE9_AMPLIFIER1_COMP_EN_MASK, WD2_FE9_AMPLIFIER1_COMP_EN_OFS);
   };

   void SetFe9Amplifier1CompEn(unsigned int value) {
      SetRegMask(WD2_FE9_AMPLIFIER1_COMP_EN_REG, WD2_FE9_AMPLIFIER1_COMP_EN_MASK, WD2_FE9_AMPLIFIER1_COMP_EN_OFS, value);
   };

   unsigned int GetFe9Amplifier1En() {
      return BitExtractControl(WD2_FE9_AMPLIFIER1_EN_REG, WD2_FE9_AMPLIFIER1_EN_MASK, WD2_FE9_AMPLIFIER1_EN_OFS);
   };

   void SetFe9Amplifier1En(unsigned int value) {
      SetRegMask(WD2_FE9_AMPLIFIER1_EN_REG, WD2_FE9_AMPLIFIER1_EN_MASK, WD2_FE9_AMPLIFIER1_EN_OFS, value);
   };

   unsigned int GetFe9Attenuation() {
      return BitExtractControl(WD2_FE9_ATTENUATION_REG, WD2_FE9_ATTENUATION_MASK, WD2_FE9_ATTENUATION_OFS);
   };

   void SetFe9Attenuation(unsigned int value) {
      SetRegMask(WD2_FE9_ATTENUATION_REG, WD2_FE9_ATTENUATION_MASK, WD2_FE9_ATTENUATION_OFS, value);
   };

   unsigned int GetFe9Mux() {
      return BitExtractControl(WD2_FE9_MUX_REG, WD2_FE9_MUX_MASK, WD2_FE9_MUX_OFS);
   };

   void SetFe9Mux(unsigned int value) {
      SetRegMask(WD2_FE9_MUX_REG, WD2_FE9_MUX_MASK, WD2_FE9_MUX_OFS, value);
   };


   // Control Register 35: FE_CFG_10_11 (offset 0x108C) 
   unsigned int GetFe10PzcEn() {
      return BitExtractControl(WD2_FE10_PZC_EN_REG, WD2_FE10_PZC_EN_MASK, WD2_FE10_PZC_EN_OFS);
   };

   void SetFe10PzcEn(unsigned int value) {
      SetRegMask(WD2_FE10_PZC_EN_REG, WD2_FE10_PZC_EN_MASK, WD2_FE10_PZC_EN_OFS, value);
   };

   unsigned int GetFe10Amplifier2CompEn() {
      return BitExtractControl(WD2_FE10_AMPLIFIER2_COMP_EN_REG, WD2_FE10_AMPLIFIER2_COMP_EN_MASK, WD2_FE10_AMPLIFIER2_COMP_EN_OFS);
   };

   void SetFe10Amplifier2CompEn(unsigned int value) {
      SetRegMask(WD2_FE10_AMPLIFIER2_COMP_EN_REG, WD2_FE10_AMPLIFIER2_COMP_EN_MASK, WD2_FE10_AMPLIFIER2_COMP_EN_OFS, value);
   };

   unsigned int GetFe10Amplifier2En() {
      return BitExtractControl(WD2_FE10_AMPLIFIER2_EN_REG, WD2_FE10_AMPLIFIER2_EN_MASK, WD2_FE10_AMPLIFIER2_EN_OFS);
   };

   void SetFe10Amplifier2En(unsigned int value) {
      SetRegMask(WD2_FE10_AMPLIFIER2_EN_REG, WD2_FE10_AMPLIFIER2_EN_MASK, WD2_FE10_AMPLIFIER2_EN_OFS, value);
   };

   unsigned int GetFe10Amplifier1CompEn() {
      return BitExtractControl(WD2_FE10_AMPLIFIER1_COMP_EN_REG, WD2_FE10_AMPLIFIER1_COMP_EN_MASK, WD2_FE10_AMPLIFIER1_COMP_EN_OFS);
   };

   void SetFe10Amplifier1CompEn(unsigned int value) {
      SetRegMask(WD2_FE10_AMPLIFIER1_COMP_EN_REG, WD2_FE10_AMPLIFIER1_COMP_EN_MASK, WD2_FE10_AMPLIFIER1_COMP_EN_OFS, value);
   };

   unsigned int GetFe10Amplifier1En() {
      return BitExtractControl(WD2_FE10_AMPLIFIER1_EN_REG, WD2_FE10_AMPLIFIER1_EN_MASK, WD2_FE10_AMPLIFIER1_EN_OFS);
   };

   void SetFe10Amplifier1En(unsigned int value) {
      SetRegMask(WD2_FE10_AMPLIFIER1_EN_REG, WD2_FE10_AMPLIFIER1_EN_MASK, WD2_FE10_AMPLIFIER1_EN_OFS, value);
   };

   unsigned int GetFe10Attenuation() {
      return BitExtractControl(WD2_FE10_ATTENUATION_REG, WD2_FE10_ATTENUATION_MASK, WD2_FE10_ATTENUATION_OFS);
   };

   void SetFe10Attenuation(unsigned int value) {
      SetRegMask(WD2_FE10_ATTENUATION_REG, WD2_FE10_ATTENUATION_MASK, WD2_FE10_ATTENUATION_OFS, value);
   };

   unsigned int GetFe10Mux() {
      return BitExtractControl(WD2_FE10_MUX_REG, WD2_FE10_MUX_MASK, WD2_FE10_MUX_OFS);
   };

   void SetFe10Mux(unsigned int value) {
      SetRegMask(WD2_FE10_MUX_REG, WD2_FE10_MUX_MASK, WD2_FE10_MUX_OFS, value);
   };

   unsigned int GetFe11PzcEn() {
      return BitExtractControl(WD2_FE11_PZC_EN_REG, WD2_FE11_PZC_EN_MASK, WD2_FE11_PZC_EN_OFS);
   };

   void SetFe11PzcEn(unsigned int value) {
      SetRegMask(WD2_FE11_PZC_EN_REG, WD2_FE11_PZC_EN_MASK, WD2_FE11_PZC_EN_OFS, value);
   };

   unsigned int GetFe11Amplifier2CompEn() {
      return BitExtractControl(WD2_FE11_AMPLIFIER2_COMP_EN_REG, WD2_FE11_AMPLIFIER2_COMP_EN_MASK, WD2_FE11_AMPLIFIER2_COMP_EN_OFS);
   };

   void SetFe11Amplifier2CompEn(unsigned int value) {
      SetRegMask(WD2_FE11_AMPLIFIER2_COMP_EN_REG, WD2_FE11_AMPLIFIER2_COMP_EN_MASK, WD2_FE11_AMPLIFIER2_COMP_EN_OFS, value);
   };

   unsigned int GetFe11Amplifier2En() {
      return BitExtractControl(WD2_FE11_AMPLIFIER2_EN_REG, WD2_FE11_AMPLIFIER2_EN_MASK, WD2_FE11_AMPLIFIER2_EN_OFS);
   };

   void SetFe11Amplifier2En(unsigned int value) {
      SetRegMask(WD2_FE11_AMPLIFIER2_EN_REG, WD2_FE11_AMPLIFIER2_EN_MASK, WD2_FE11_AMPLIFIER2_EN_OFS, value);
   };

   unsigned int GetFe11Amplifier1CompEn() {
      return BitExtractControl(WD2_FE11_AMPLIFIER1_COMP_EN_REG, WD2_FE11_AMPLIFIER1_COMP_EN_MASK, WD2_FE11_AMPLIFIER1_COMP_EN_OFS);
   };

   void SetFe11Amplifier1CompEn(unsigned int value) {
      SetRegMask(WD2_FE11_AMPLIFIER1_COMP_EN_REG, WD2_FE11_AMPLIFIER1_COMP_EN_MASK, WD2_FE11_AMPLIFIER1_COMP_EN_OFS, value);
   };

   unsigned int GetFe11Amplifier1En() {
      return BitExtractControl(WD2_FE11_AMPLIFIER1_EN_REG, WD2_FE11_AMPLIFIER1_EN_MASK, WD2_FE11_AMPLIFIER1_EN_OFS);
   };

   void SetFe11Amplifier1En(unsigned int value) {
      SetRegMask(WD2_FE11_AMPLIFIER1_EN_REG, WD2_FE11_AMPLIFIER1_EN_MASK, WD2_FE11_AMPLIFIER1_EN_OFS, value);
   };

   unsigned int GetFe11Attenuation() {
      return BitExtractControl(WD2_FE11_ATTENUATION_REG, WD2_FE11_ATTENUATION_MASK, WD2_FE11_ATTENUATION_OFS);
   };

   void SetFe11Attenuation(unsigned int value) {
      SetRegMask(WD2_FE11_ATTENUATION_REG, WD2_FE11_ATTENUATION_MASK, WD2_FE11_ATTENUATION_OFS, value);
   };

   unsigned int GetFe11Mux() {
      return BitExtractControl(WD2_FE11_MUX_REG, WD2_FE11_MUX_MASK, WD2_FE11_MUX_OFS);
   };

   void SetFe11Mux(unsigned int value) {
      SetRegMask(WD2_FE11_MUX_REG, WD2_FE11_MUX_MASK, WD2_FE11_MUX_OFS, value);
   };


   // Control Register 36: FE_CFG_12_13 (offset 0x1090) 
   unsigned int GetFe12PzcEn() {
      return BitExtractControl(WD2_FE12_PZC_EN_REG, WD2_FE12_PZC_EN_MASK, WD2_FE12_PZC_EN_OFS);
   };

   void SetFe12PzcEn(unsigned int value) {
      SetRegMask(WD2_FE12_PZC_EN_REG, WD2_FE12_PZC_EN_MASK, WD2_FE12_PZC_EN_OFS, value);
   };

   unsigned int GetFe12Amplifier2CompEn() {
      return BitExtractControl(WD2_FE12_AMPLIFIER2_COMP_EN_REG, WD2_FE12_AMPLIFIER2_COMP_EN_MASK, WD2_FE12_AMPLIFIER2_COMP_EN_OFS);
   };

   void SetFe12Amplifier2CompEn(unsigned int value) {
      SetRegMask(WD2_FE12_AMPLIFIER2_COMP_EN_REG, WD2_FE12_AMPLIFIER2_COMP_EN_MASK, WD2_FE12_AMPLIFIER2_COMP_EN_OFS, value);
   };

   unsigned int GetFe12Amplifier2En() {
      return BitExtractControl(WD2_FE12_AMPLIFIER2_EN_REG, WD2_FE12_AMPLIFIER2_EN_MASK, WD2_FE12_AMPLIFIER2_EN_OFS);
   };

   void SetFe12Amplifier2En(unsigned int value) {
      SetRegMask(WD2_FE12_AMPLIFIER2_EN_REG, WD2_FE12_AMPLIFIER2_EN_MASK, WD2_FE12_AMPLIFIER2_EN_OFS, value);
   };

   unsigned int GetFe12Amplifier1CompEn() {
      return BitExtractControl(WD2_FE12_AMPLIFIER1_COMP_EN_REG, WD2_FE12_AMPLIFIER1_COMP_EN_MASK, WD2_FE12_AMPLIFIER1_COMP_EN_OFS);
   };

   void SetFe12Amplifier1CompEn(unsigned int value) {
      SetRegMask(WD2_FE12_AMPLIFIER1_COMP_EN_REG, WD2_FE12_AMPLIFIER1_COMP_EN_MASK, WD2_FE12_AMPLIFIER1_COMP_EN_OFS, value);
   };

   unsigned int GetFe12Amplifier1En() {
      return BitExtractControl(WD2_FE12_AMPLIFIER1_EN_REG, WD2_FE12_AMPLIFIER1_EN_MASK, WD2_FE12_AMPLIFIER1_EN_OFS);
   };

   void SetFe12Amplifier1En(unsigned int value) {
      SetRegMask(WD2_FE12_AMPLIFIER1_EN_REG, WD2_FE12_AMPLIFIER1_EN_MASK, WD2_FE12_AMPLIFIER1_EN_OFS, value);
   };

   unsigned int GetFe12Attenuation() {
      return BitExtractControl(WD2_FE12_ATTENUATION_REG, WD2_FE12_ATTENUATION_MASK, WD2_FE12_ATTENUATION_OFS);
   };

   void SetFe12Attenuation(unsigned int value) {
      SetRegMask(WD2_FE12_ATTENUATION_REG, WD2_FE12_ATTENUATION_MASK, WD2_FE12_ATTENUATION_OFS, value);
   };

   unsigned int GetFe12Mux() {
      return BitExtractControl(WD2_FE12_MUX_REG, WD2_FE12_MUX_MASK, WD2_FE12_MUX_OFS);
   };

   void SetFe12Mux(unsigned int value) {
      SetRegMask(WD2_FE12_MUX_REG, WD2_FE12_MUX_MASK, WD2_FE12_MUX_OFS, value);
   };

   unsigned int GetFe13PzcEn() {
      return BitExtractControl(WD2_FE13_PZC_EN_REG, WD2_FE13_PZC_EN_MASK, WD2_FE13_PZC_EN_OFS);
   };

   void SetFe13PzcEn(unsigned int value) {
      SetRegMask(WD2_FE13_PZC_EN_REG, WD2_FE13_PZC_EN_MASK, WD2_FE13_PZC_EN_OFS, value);
   };

   unsigned int GetFe13Amplifier2CompEn() {
      return BitExtractControl(WD2_FE13_AMPLIFIER2_COMP_EN_REG, WD2_FE13_AMPLIFIER2_COMP_EN_MASK, WD2_FE13_AMPLIFIER2_COMP_EN_OFS);
   };

   void SetFe13Amplifier2CompEn(unsigned int value) {
      SetRegMask(WD2_FE13_AMPLIFIER2_COMP_EN_REG, WD2_FE13_AMPLIFIER2_COMP_EN_MASK, WD2_FE13_AMPLIFIER2_COMP_EN_OFS, value);
   };

   unsigned int GetFe13Amplifier2En() {
      return BitExtractControl(WD2_FE13_AMPLIFIER2_EN_REG, WD2_FE13_AMPLIFIER2_EN_MASK, WD2_FE13_AMPLIFIER2_EN_OFS);
   };

   void SetFe13Amplifier2En(unsigned int value) {
      SetRegMask(WD2_FE13_AMPLIFIER2_EN_REG, WD2_FE13_AMPLIFIER2_EN_MASK, WD2_FE13_AMPLIFIER2_EN_OFS, value);
   };

   unsigned int GetFe13Amplifier1CompEn() {
      return BitExtractControl(WD2_FE13_AMPLIFIER1_COMP_EN_REG, WD2_FE13_AMPLIFIER1_COMP_EN_MASK, WD2_FE13_AMPLIFIER1_COMP_EN_OFS);
   };

   void SetFe13Amplifier1CompEn(unsigned int value) {
      SetRegMask(WD2_FE13_AMPLIFIER1_COMP_EN_REG, WD2_FE13_AMPLIFIER1_COMP_EN_MASK, WD2_FE13_AMPLIFIER1_COMP_EN_OFS, value);
   };

   unsigned int GetFe13Amplifier1En() {
      return BitExtractControl(WD2_FE13_AMPLIFIER1_EN_REG, WD2_FE13_AMPLIFIER1_EN_MASK, WD2_FE13_AMPLIFIER1_EN_OFS);
   };

   void SetFe13Amplifier1En(unsigned int value) {
      SetRegMask(WD2_FE13_AMPLIFIER1_EN_REG, WD2_FE13_AMPLIFIER1_EN_MASK, WD2_FE13_AMPLIFIER1_EN_OFS, value);
   };

   unsigned int GetFe13Attenuation() {
      return BitExtractControl(WD2_FE13_ATTENUATION_REG, WD2_FE13_ATTENUATION_MASK, WD2_FE13_ATTENUATION_OFS);
   };

   void SetFe13Attenuation(unsigned int value) {
      SetRegMask(WD2_FE13_ATTENUATION_REG, WD2_FE13_ATTENUATION_MASK, WD2_FE13_ATTENUATION_OFS, value);
   };

   unsigned int GetFe13Mux() {
      return BitExtractControl(WD2_FE13_MUX_REG, WD2_FE13_MUX_MASK, WD2_FE13_MUX_OFS);
   };

   void SetFe13Mux(unsigned int value) {
      SetRegMask(WD2_FE13_MUX_REG, WD2_FE13_MUX_MASK, WD2_FE13_MUX_OFS, value);
   };


   // Control Register 37: FE_CFG_14_15 (offset 0x1094) 
   unsigned int GetFe14PzcEn() {
      return BitExtractControl(WD2_FE14_PZC_EN_REG, WD2_FE14_PZC_EN_MASK, WD2_FE14_PZC_EN_OFS);
   };

   void SetFe14PzcEn(unsigned int value) {
      SetRegMask(WD2_FE14_PZC_EN_REG, WD2_FE14_PZC_EN_MASK, WD2_FE14_PZC_EN_OFS, value);
   };

   unsigned int GetFe14Amplifier2CompEn() {
      return BitExtractControl(WD2_FE14_AMPLIFIER2_COMP_EN_REG, WD2_FE14_AMPLIFIER2_COMP_EN_MASK, WD2_FE14_AMPLIFIER2_COMP_EN_OFS);
   };

   void SetFe14Amplifier2CompEn(unsigned int value) {
      SetRegMask(WD2_FE14_AMPLIFIER2_COMP_EN_REG, WD2_FE14_AMPLIFIER2_COMP_EN_MASK, WD2_FE14_AMPLIFIER2_COMP_EN_OFS, value);
   };

   unsigned int GetFe14Amplifier2En() {
      return BitExtractControl(WD2_FE14_AMPLIFIER2_EN_REG, WD2_FE14_AMPLIFIER2_EN_MASK, WD2_FE14_AMPLIFIER2_EN_OFS);
   };

   void SetFe14Amplifier2En(unsigned int value) {
      SetRegMask(WD2_FE14_AMPLIFIER2_EN_REG, WD2_FE14_AMPLIFIER2_EN_MASK, WD2_FE14_AMPLIFIER2_EN_OFS, value);
   };

   unsigned int GetFe14Amplifier1CompEn() {
      return BitExtractControl(WD2_FE14_AMPLIFIER1_COMP_EN_REG, WD2_FE14_AMPLIFIER1_COMP_EN_MASK, WD2_FE14_AMPLIFIER1_COMP_EN_OFS);
   };

   void SetFe14Amplifier1CompEn(unsigned int value) {
      SetRegMask(WD2_FE14_AMPLIFIER1_COMP_EN_REG, WD2_FE14_AMPLIFIER1_COMP_EN_MASK, WD2_FE14_AMPLIFIER1_COMP_EN_OFS, value);
   };

   unsigned int GetFe14Amplifier1En() {
      return BitExtractControl(WD2_FE14_AMPLIFIER1_EN_REG, WD2_FE14_AMPLIFIER1_EN_MASK, WD2_FE14_AMPLIFIER1_EN_OFS);
   };

   void SetFe14Amplifier1En(unsigned int value) {
      SetRegMask(WD2_FE14_AMPLIFIER1_EN_REG, WD2_FE14_AMPLIFIER1_EN_MASK, WD2_FE14_AMPLIFIER1_EN_OFS, value);
   };

   unsigned int GetFe14Attenuation() {
      return BitExtractControl(WD2_FE14_ATTENUATION_REG, WD2_FE14_ATTENUATION_MASK, WD2_FE14_ATTENUATION_OFS);
   };

   void SetFe14Attenuation(unsigned int value) {
      SetRegMask(WD2_FE14_ATTENUATION_REG, WD2_FE14_ATTENUATION_MASK, WD2_FE14_ATTENUATION_OFS, value);
   };

   unsigned int GetFe14Mux() {
      return BitExtractControl(WD2_FE14_MUX_REG, WD2_FE14_MUX_MASK, WD2_FE14_MUX_OFS);
   };

   void SetFe14Mux(unsigned int value) {
      SetRegMask(WD2_FE14_MUX_REG, WD2_FE14_MUX_MASK, WD2_FE14_MUX_OFS, value);
   };

   unsigned int GetFe15PzcEn() {
      return BitExtractControl(WD2_FE15_PZC_EN_REG, WD2_FE15_PZC_EN_MASK, WD2_FE15_PZC_EN_OFS);
   };

   void SetFe15PzcEn(unsigned int value) {
      SetRegMask(WD2_FE15_PZC_EN_REG, WD2_FE15_PZC_EN_MASK, WD2_FE15_PZC_EN_OFS, value);
   };

   unsigned int GetFe15Amplifier2CompEn() {
      return BitExtractControl(WD2_FE15_AMPLIFIER2_COMP_EN_REG, WD2_FE15_AMPLIFIER2_COMP_EN_MASK, WD2_FE15_AMPLIFIER2_COMP_EN_OFS);
   };

   void SetFe15Amplifier2CompEn(unsigned int value) {
      SetRegMask(WD2_FE15_AMPLIFIER2_COMP_EN_REG, WD2_FE15_AMPLIFIER2_COMP_EN_MASK, WD2_FE15_AMPLIFIER2_COMP_EN_OFS, value);
   };

   unsigned int GetFe15Amplifier2En() {
      return BitExtractControl(WD2_FE15_AMPLIFIER2_EN_REG, WD2_FE15_AMPLIFIER2_EN_MASK, WD2_FE15_AMPLIFIER2_EN_OFS);
   };

   void SetFe15Amplifier2En(unsigned int value) {
      SetRegMask(WD2_FE15_AMPLIFIER2_EN_REG, WD2_FE15_AMPLIFIER2_EN_MASK, WD2_FE15_AMPLIFIER2_EN_OFS, value);
   };

   unsigned int GetFe15Amplifier1CompEn() {
      return BitExtractControl(WD2_FE15_AMPLIFIER1_COMP_EN_REG, WD2_FE15_AMPLIFIER1_COMP_EN_MASK, WD2_FE15_AMPLIFIER1_COMP_EN_OFS);
   };

   void SetFe15Amplifier1CompEn(unsigned int value) {
      SetRegMask(WD2_FE15_AMPLIFIER1_COMP_EN_REG, WD2_FE15_AMPLIFIER1_COMP_EN_MASK, WD2_FE15_AMPLIFIER1_COMP_EN_OFS, value);
   };

   unsigned int GetFe15Amplifier1En() {
      return BitExtractControl(WD2_FE15_AMPLIFIER1_EN_REG, WD2_FE15_AMPLIFIER1_EN_MASK, WD2_FE15_AMPLIFIER1_EN_OFS);
   };

   void SetFe15Amplifier1En(unsigned int value) {
      SetRegMask(WD2_FE15_AMPLIFIER1_EN_REG, WD2_FE15_AMPLIFIER1_EN_MASK, WD2_FE15_AMPLIFIER1_EN_OFS, value);
   };

   unsigned int GetFe15Attenuation() {
      return BitExtractControl(WD2_FE15_ATTENUATION_REG, WD2_FE15_ATTENUATION_MASK, WD2_FE15_ATTENUATION_OFS);
   };

   void SetFe15Attenuation(unsigned int value) {
      SetRegMask(WD2_FE15_ATTENUATION_REG, WD2_FE15_ATTENUATION_MASK, WD2_FE15_ATTENUATION_OFS, value);
   };

   unsigned int GetFe15Mux() {
      return BitExtractControl(WD2_FE15_MUX_REG, WD2_FE15_MUX_MASK, WD2_FE15_MUX_OFS);
   };

   void SetFe15Mux(unsigned int value) {
      SetRegMask(WD2_FE15_MUX_REG, WD2_FE15_MUX_MASK, WD2_FE15_MUX_OFS, value);
   };


   // Control Register 38: HV_U_TARGET_0 (offset 0x1098) 
   unsigned int GetHvUTarget0() {
      return BitExtractControl(WD2_HV_U_TARGET_0_REG, WD2_HV_U_TARGET_0_MASK, WD2_HV_U_TARGET_0_OFS);
   };

   void SetHvUTarget0(unsigned int value) {
      SetRegMask(WD2_HV_U_TARGET_0_REG, WD2_HV_U_TARGET_0_MASK, WD2_HV_U_TARGET_0_OFS, value);
   };


   // Control Register 39: HV_U_TARGET_1 (offset 0x109C) 
   unsigned int GetHvUTarget1() {
      return BitExtractControl(WD2_HV_U_TARGET_1_REG, WD2_HV_U_TARGET_1_MASK, WD2_HV_U_TARGET_1_OFS);
   };

   void SetHvUTarget1(unsigned int value) {
      SetRegMask(WD2_HV_U_TARGET_1_REG, WD2_HV_U_TARGET_1_MASK, WD2_HV_U_TARGET_1_OFS, value);
   };


   // Control Register 40: HV_U_TARGET_2 (offset 0x10A0) 
   unsigned int GetHvUTarget2() {
      return BitExtractControl(WD2_HV_U_TARGET_2_REG, WD2_HV_U_TARGET_2_MASK, WD2_HV_U_TARGET_2_OFS);
   };

   void SetHvUTarget2(unsigned int value) {
      SetRegMask(WD2_HV_U_TARGET_2_REG, WD2_HV_U_TARGET_2_MASK, WD2_HV_U_TARGET_2_OFS, value);
   };


   // Control Register 41: HV_U_TARGET_3 (offset 0x10A4) 
   unsigned int GetHvUTarget3() {
      return BitExtractControl(WD2_HV_U_TARGET_3_REG, WD2_HV_U_TARGET_3_MASK, WD2_HV_U_TARGET_3_OFS);
   };

   void SetHvUTarget3(unsigned int value) {
      SetRegMask(WD2_HV_U_TARGET_3_REG, WD2_HV_U_TARGET_3_MASK, WD2_HV_U_TARGET_3_OFS, value);
   };


   // Control Register 42: HV_U_TARGET_4 (offset 0x10A8) 
   unsigned int GetHvUTarget4() {
      return BitExtractControl(WD2_HV_U_TARGET_4_REG, WD2_HV_U_TARGET_4_MASK, WD2_HV_U_TARGET_4_OFS);
   };

   void SetHvUTarget4(unsigned int value) {
      SetRegMask(WD2_HV_U_TARGET_4_REG, WD2_HV_U_TARGET_4_MASK, WD2_HV_U_TARGET_4_OFS, value);
   };


   // Control Register 43: HV_U_TARGET_5 (offset 0x10AC) 
   unsigned int GetHvUTarget5() {
      return BitExtractControl(WD2_HV_U_TARGET_5_REG, WD2_HV_U_TARGET_5_MASK, WD2_HV_U_TARGET_5_OFS);
   };

   void SetHvUTarget5(unsigned int value) {
      SetRegMask(WD2_HV_U_TARGET_5_REG, WD2_HV_U_TARGET_5_MASK, WD2_HV_U_TARGET_5_OFS, value);
   };


   // Control Register 44: HV_U_TARGET_6 (offset 0x10B0) 
   unsigned int GetHvUTarget6() {
      return BitExtractControl(WD2_HV_U_TARGET_6_REG, WD2_HV_U_TARGET_6_MASK, WD2_HV_U_TARGET_6_OFS);
   };

   void SetHvUTarget6(unsigned int value) {
      SetRegMask(WD2_HV_U_TARGET_6_REG, WD2_HV_U_TARGET_6_MASK, WD2_HV_U_TARGET_6_OFS, value);
   };


   // Control Register 45: HV_U_TARGET_7 (offset 0x10B4) 
   unsigned int GetHvUTarget7() {
      return BitExtractControl(WD2_HV_U_TARGET_7_REG, WD2_HV_U_TARGET_7_MASK, WD2_HV_U_TARGET_7_OFS);
   };

   void SetHvUTarget7(unsigned int value) {
      SetRegMask(WD2_HV_U_TARGET_7_REG, WD2_HV_U_TARGET_7_MASK, WD2_HV_U_TARGET_7_OFS, value);
   };


   // Control Register 46: HV_U_TARGET_8 (offset 0x10B8) 
   unsigned int GetHvUTarget8() {
      return BitExtractControl(WD2_HV_U_TARGET_8_REG, WD2_HV_U_TARGET_8_MASK, WD2_HV_U_TARGET_8_OFS);
   };

   void SetHvUTarget8(unsigned int value) {
      SetRegMask(WD2_HV_U_TARGET_8_REG, WD2_HV_U_TARGET_8_MASK, WD2_HV_U_TARGET_8_OFS, value);
   };


   // Control Register 47: HV_U_TARGET_9 (offset 0x10BC) 
   unsigned int GetHvUTarget9() {
      return BitExtractControl(WD2_HV_U_TARGET_9_REG, WD2_HV_U_TARGET_9_MASK, WD2_HV_U_TARGET_9_OFS);
   };

   void SetHvUTarget9(unsigned int value) {
      SetRegMask(WD2_HV_U_TARGET_9_REG, WD2_HV_U_TARGET_9_MASK, WD2_HV_U_TARGET_9_OFS, value);
   };


   // Control Register 48: HV_U_TARGET_10 (offset 0x10C0) 
   unsigned int GetHvUTarget10() {
      return BitExtractControl(WD2_HV_U_TARGET_10_REG, WD2_HV_U_TARGET_10_MASK, WD2_HV_U_TARGET_10_OFS);
   };

   void SetHvUTarget10(unsigned int value) {
      SetRegMask(WD2_HV_U_TARGET_10_REG, WD2_HV_U_TARGET_10_MASK, WD2_HV_U_TARGET_10_OFS, value);
   };


   // Control Register 49: HV_U_TARGET_11 (offset 0x10C4) 
   unsigned int GetHvUTarget11() {
      return BitExtractControl(WD2_HV_U_TARGET_11_REG, WD2_HV_U_TARGET_11_MASK, WD2_HV_U_TARGET_11_OFS);
   };

   void SetHvUTarget11(unsigned int value) {
      SetRegMask(WD2_HV_U_TARGET_11_REG, WD2_HV_U_TARGET_11_MASK, WD2_HV_U_TARGET_11_OFS, value);
   };


   // Control Register 50: HV_U_TARGET_12 (offset 0x10C8) 
   unsigned int GetHvUTarget12() {
      return BitExtractControl(WD2_HV_U_TARGET_12_REG, WD2_HV_U_TARGET_12_MASK, WD2_HV_U_TARGET_12_OFS);
   };

   void SetHvUTarget12(unsigned int value) {
      SetRegMask(WD2_HV_U_TARGET_12_REG, WD2_HV_U_TARGET_12_MASK, WD2_HV_U_TARGET_12_OFS, value);
   };


   // Control Register 51: HV_U_TARGET_13 (offset 0x10CC) 
   unsigned int GetHvUTarget13() {
      return BitExtractControl(WD2_HV_U_TARGET_13_REG, WD2_HV_U_TARGET_13_MASK, WD2_HV_U_TARGET_13_OFS);
   };

   void SetHvUTarget13(unsigned int value) {
      SetRegMask(WD2_HV_U_TARGET_13_REG, WD2_HV_U_TARGET_13_MASK, WD2_HV_U_TARGET_13_OFS, value);
   };


   // Control Register 52: HV_U_TARGET_14 (offset 0x10D0) 
   unsigned int GetHvUTarget14() {
      return BitExtractControl(WD2_HV_U_TARGET_14_REG, WD2_HV_U_TARGET_14_MASK, WD2_HV_U_TARGET_14_OFS);
   };

   void SetHvUTarget14(unsigned int value) {
      SetRegMask(WD2_HV_U_TARGET_14_REG, WD2_HV_U_TARGET_14_MASK, WD2_HV_U_TARGET_14_OFS, value);
   };


   // Control Register 53: HV_U_TARGET_15 (offset 0x10D4) 
   unsigned int GetHvUTarget15() {
      return BitExtractControl(WD2_HV_U_TARGET_15_REG, WD2_HV_U_TARGET_15_MASK, WD2_HV_U_TARGET_15_OFS);
   };

   void SetHvUTarget15(unsigned int value) {
      SetRegMask(WD2_HV_U_TARGET_15_REG, WD2_HV_U_TARGET_15_MASK, WD2_HV_U_TARGET_15_OFS, value);
   };


   // Control Register 54: HV_R_SHUNT (offset 0x10D8) 
   unsigned int GetHvRShunt() {
      return BitExtractControl(WD2_HV_R_SHUNT_REG, WD2_HV_R_SHUNT_MASK, WD2_HV_R_SHUNT_OFS);
   };

   void SetHvRShunt(unsigned int value) {
      SetRegMask(WD2_HV_R_SHUNT_REG, WD2_HV_R_SHUNT_MASK, WD2_HV_R_SHUNT_OFS, value);
   };


   // Control Register 55: LMK_0 (offset 0x10DC) 
   unsigned int GetLmk0Reset() {
      return BitExtractControl(WD2_LMK0_RESET_REG, WD2_LMK0_RESET_MASK, WD2_LMK0_RESET_OFS);
   };

   void SetLmk0Reset(unsigned int value) {
      SetRegMask(WD2_LMK0_RESET_REG, WD2_LMK0_RESET_MASK, WD2_LMK0_RESET_OFS, value);
   };

   unsigned int GetLmk0Clkout0Mux() {
      return BitExtractControl(WD2_LMK0_CLKOUT0_MUX_REG, WD2_LMK0_CLKOUT0_MUX_MASK, WD2_LMK0_CLKOUT0_MUX_OFS);
   };

   void SetLmk0Clkout0Mux(unsigned int value) {
      SetRegMask(WD2_LMK0_CLKOUT0_MUX_REG, WD2_LMK0_CLKOUT0_MUX_MASK, WD2_LMK0_CLKOUT0_MUX_OFS, value);
   };

   unsigned int GetLmk0Clkout0En() {
      return BitExtractControl(WD2_LMK0_CLKOUT0_EN_REG, WD2_LMK0_CLKOUT0_EN_MASK, WD2_LMK0_CLKOUT0_EN_OFS);
   };

   void SetLmk0Clkout0En(unsigned int value) {
      SetRegMask(WD2_LMK0_CLKOUT0_EN_REG, WD2_LMK0_CLKOUT0_EN_MASK, WD2_LMK0_CLKOUT0_EN_OFS, value);
   };

   unsigned int GetLmk0Clkout0Div() {
      return BitExtractControl(WD2_LMK0_CLKOUT0_DIV_REG, WD2_LMK0_CLKOUT0_DIV_MASK, WD2_LMK0_CLKOUT0_DIV_OFS);
   };

   void SetLmk0Clkout0Div(unsigned int value) {
      SetRegMask(WD2_LMK0_CLKOUT0_DIV_REG, WD2_LMK0_CLKOUT0_DIV_MASK, WD2_LMK0_CLKOUT0_DIV_OFS, value);
   };

   unsigned int GetLmk0Clkout0Dly() {
      return BitExtractControl(WD2_LMK0_CLKOUT0_DLY_REG, WD2_LMK0_CLKOUT0_DLY_MASK, WD2_LMK0_CLKOUT0_DLY_OFS);
   };

   void SetLmk0Clkout0Dly(unsigned int value) {
      SetRegMask(WD2_LMK0_CLKOUT0_DLY_REG, WD2_LMK0_CLKOUT0_DLY_MASK, WD2_LMK0_CLKOUT0_DLY_OFS, value);
   };


   // Control Register 56: LMK_1 (offset 0x10E0) 
   unsigned int GetLmk1Clkout1Mux() {
      return BitExtractControl(WD2_LMK1_CLKOUT1_MUX_REG, WD2_LMK1_CLKOUT1_MUX_MASK, WD2_LMK1_CLKOUT1_MUX_OFS);
   };

   void SetLmk1Clkout1Mux(unsigned int value) {
      SetRegMask(WD2_LMK1_CLKOUT1_MUX_REG, WD2_LMK1_CLKOUT1_MUX_MASK, WD2_LMK1_CLKOUT1_MUX_OFS, value);
   };

   unsigned int GetLmk1Clkout1En() {
      return BitExtractControl(WD2_LMK1_CLKOUT1_EN_REG, WD2_LMK1_CLKOUT1_EN_MASK, WD2_LMK1_CLKOUT1_EN_OFS);
   };

   void SetLmk1Clkout1En(unsigned int value) {
      SetRegMask(WD2_LMK1_CLKOUT1_EN_REG, WD2_LMK1_CLKOUT1_EN_MASK, WD2_LMK1_CLKOUT1_EN_OFS, value);
   };

   unsigned int GetLmk1Clkout1Div() {
      return BitExtractControl(WD2_LMK1_CLKOUT1_DIV_REG, WD2_LMK1_CLKOUT1_DIV_MASK, WD2_LMK1_CLKOUT1_DIV_OFS);
   };

   void SetLmk1Clkout1Div(unsigned int value) {
      SetRegMask(WD2_LMK1_CLKOUT1_DIV_REG, WD2_LMK1_CLKOUT1_DIV_MASK, WD2_LMK1_CLKOUT1_DIV_OFS, value);
   };

   unsigned int GetLmk1Clkout1Dly() {
      return BitExtractControl(WD2_LMK1_CLKOUT1_DLY_REG, WD2_LMK1_CLKOUT1_DLY_MASK, WD2_LMK1_CLKOUT1_DLY_OFS);
   };

   void SetLmk1Clkout1Dly(unsigned int value) {
      SetRegMask(WD2_LMK1_CLKOUT1_DLY_REG, WD2_LMK1_CLKOUT1_DLY_MASK, WD2_LMK1_CLKOUT1_DLY_OFS, value);
   };


   // Control Register 57: LMK_2 (offset 0x10E4) 
   unsigned int GetLmk2Clkout2Mux() {
      return BitExtractControl(WD2_LMK2_CLKOUT2_MUX_REG, WD2_LMK2_CLKOUT2_MUX_MASK, WD2_LMK2_CLKOUT2_MUX_OFS);
   };

   void SetLmk2Clkout2Mux(unsigned int value) {
      SetRegMask(WD2_LMK2_CLKOUT2_MUX_REG, WD2_LMK2_CLKOUT2_MUX_MASK, WD2_LMK2_CLKOUT2_MUX_OFS, value);
   };

   unsigned int GetLmk2Clkout2En() {
      return BitExtractControl(WD2_LMK2_CLKOUT2_EN_REG, WD2_LMK2_CLKOUT2_EN_MASK, WD2_LMK2_CLKOUT2_EN_OFS);
   };

   void SetLmk2Clkout2En(unsigned int value) {
      SetRegMask(WD2_LMK2_CLKOUT2_EN_REG, WD2_LMK2_CLKOUT2_EN_MASK, WD2_LMK2_CLKOUT2_EN_OFS, value);
   };

   unsigned int GetLmk2Clkout2Div() {
      return BitExtractControl(WD2_LMK2_CLKOUT2_DIV_REG, WD2_LMK2_CLKOUT2_DIV_MASK, WD2_LMK2_CLKOUT2_DIV_OFS);
   };

   void SetLmk2Clkout2Div(unsigned int value) {
      SetRegMask(WD2_LMK2_CLKOUT2_DIV_REG, WD2_LMK2_CLKOUT2_DIV_MASK, WD2_LMK2_CLKOUT2_DIV_OFS, value);
   };

   unsigned int GetLmk2Clkout2Dly() {
      return BitExtractControl(WD2_LMK2_CLKOUT2_DLY_REG, WD2_LMK2_CLKOUT2_DLY_MASK, WD2_LMK2_CLKOUT2_DLY_OFS);
   };

   void SetLmk2Clkout2Dly(unsigned int value) {
      SetRegMask(WD2_LMK2_CLKOUT2_DLY_REG, WD2_LMK2_CLKOUT2_DLY_MASK, WD2_LMK2_CLKOUT2_DLY_OFS, value);
   };


   // Control Register 58: LMK_3 (offset 0x10E8) 
   unsigned int GetLmk3Clkout3Mux() {
      return BitExtractControl(WD2_LMK3_CLKOUT3_MUX_REG, WD2_LMK3_CLKOUT3_MUX_MASK, WD2_LMK3_CLKOUT3_MUX_OFS);
   };

   void SetLmk3Clkout3Mux(unsigned int value) {
      SetRegMask(WD2_LMK3_CLKOUT3_MUX_REG, WD2_LMK3_CLKOUT3_MUX_MASK, WD2_LMK3_CLKOUT3_MUX_OFS, value);
   };

   unsigned int GetLmk3Clkout3En() {
      return BitExtractControl(WD2_LMK3_CLKOUT3_EN_REG, WD2_LMK3_CLKOUT3_EN_MASK, WD2_LMK3_CLKOUT3_EN_OFS);
   };

   void SetLmk3Clkout3En(unsigned int value) {
      SetRegMask(WD2_LMK3_CLKOUT3_EN_REG, WD2_LMK3_CLKOUT3_EN_MASK, WD2_LMK3_CLKOUT3_EN_OFS, value);
   };

   unsigned int GetLmk3Clkout3Div() {
      return BitExtractControl(WD2_LMK3_CLKOUT3_DIV_REG, WD2_LMK3_CLKOUT3_DIV_MASK, WD2_LMK3_CLKOUT3_DIV_OFS);
   };

   void SetLmk3Clkout3Div(unsigned int value) {
      SetRegMask(WD2_LMK3_CLKOUT3_DIV_REG, WD2_LMK3_CLKOUT3_DIV_MASK, WD2_LMK3_CLKOUT3_DIV_OFS, value);
   };

   unsigned int GetLmk3Clkout3Dly() {
      return BitExtractControl(WD2_LMK3_CLKOUT3_DLY_REG, WD2_LMK3_CLKOUT3_DLY_MASK, WD2_LMK3_CLKOUT3_DLY_OFS);
   };

   void SetLmk3Clkout3Dly(unsigned int value) {
      SetRegMask(WD2_LMK3_CLKOUT3_DLY_REG, WD2_LMK3_CLKOUT3_DLY_MASK, WD2_LMK3_CLKOUT3_DLY_OFS, value);
   };


   // Control Register 59: LMK_4 (offset 0x10EC) 
   unsigned int GetLmk4Clkout4Mux() {
      return BitExtractControl(WD2_LMK4_CLKOUT4_MUX_REG, WD2_LMK4_CLKOUT4_MUX_MASK, WD2_LMK4_CLKOUT4_MUX_OFS);
   };

   void SetLmk4Clkout4Mux(unsigned int value) {
      SetRegMask(WD2_LMK4_CLKOUT4_MUX_REG, WD2_LMK4_CLKOUT4_MUX_MASK, WD2_LMK4_CLKOUT4_MUX_OFS, value);
   };

   unsigned int GetLmk4Clkout4En() {
      return BitExtractControl(WD2_LMK4_CLKOUT4_EN_REG, WD2_LMK4_CLKOUT4_EN_MASK, WD2_LMK4_CLKOUT4_EN_OFS);
   };

   void SetLmk4Clkout4En(unsigned int value) {
      SetRegMask(WD2_LMK4_CLKOUT4_EN_REG, WD2_LMK4_CLKOUT4_EN_MASK, WD2_LMK4_CLKOUT4_EN_OFS, value);
   };

   unsigned int GetLmk4Clkout4Div() {
      return BitExtractControl(WD2_LMK4_CLKOUT4_DIV_REG, WD2_LMK4_CLKOUT4_DIV_MASK, WD2_LMK4_CLKOUT4_DIV_OFS);
   };

   void SetLmk4Clkout4Div(unsigned int value) {
      SetRegMask(WD2_LMK4_CLKOUT4_DIV_REG, WD2_LMK4_CLKOUT4_DIV_MASK, WD2_LMK4_CLKOUT4_DIV_OFS, value);
   };

   unsigned int GetLmk4Clkout4Dly() {
      return BitExtractControl(WD2_LMK4_CLKOUT4_DLY_REG, WD2_LMK4_CLKOUT4_DLY_MASK, WD2_LMK4_CLKOUT4_DLY_OFS);
   };

   void SetLmk4Clkout4Dly(unsigned int value) {
      SetRegMask(WD2_LMK4_CLKOUT4_DLY_REG, WD2_LMK4_CLKOUT4_DLY_MASK, WD2_LMK4_CLKOUT4_DLY_OFS, value);
   };


   // Control Register 60: LMK_5 (offset 0x10F0) 
   unsigned int GetLmk5Clkout5Mux() {
      return BitExtractControl(WD2_LMK5_CLKOUT5_MUX_REG, WD2_LMK5_CLKOUT5_MUX_MASK, WD2_LMK5_CLKOUT5_MUX_OFS);
   };

   void SetLmk5Clkout5Mux(unsigned int value) {
      SetRegMask(WD2_LMK5_CLKOUT5_MUX_REG, WD2_LMK5_CLKOUT5_MUX_MASK, WD2_LMK5_CLKOUT5_MUX_OFS, value);
   };

   unsigned int GetLmk5Clkout5En() {
      return BitExtractControl(WD2_LMK5_CLKOUT5_EN_REG, WD2_LMK5_CLKOUT5_EN_MASK, WD2_LMK5_CLKOUT5_EN_OFS);
   };

   void SetLmk5Clkout5En(unsigned int value) {
      SetRegMask(WD2_LMK5_CLKOUT5_EN_REG, WD2_LMK5_CLKOUT5_EN_MASK, WD2_LMK5_CLKOUT5_EN_OFS, value);
   };

   unsigned int GetLmk5Clkout5Div() {
      return BitExtractControl(WD2_LMK5_CLKOUT5_DIV_REG, WD2_LMK5_CLKOUT5_DIV_MASK, WD2_LMK5_CLKOUT5_DIV_OFS);
   };

   void SetLmk5Clkout5Div(unsigned int value) {
      SetRegMask(WD2_LMK5_CLKOUT5_DIV_REG, WD2_LMK5_CLKOUT5_DIV_MASK, WD2_LMK5_CLKOUT5_DIV_OFS, value);
   };

   unsigned int GetLmk5Clkout5Dly() {
      return BitExtractControl(WD2_LMK5_CLKOUT5_DLY_REG, WD2_LMK5_CLKOUT5_DLY_MASK, WD2_LMK5_CLKOUT5_DLY_OFS);
   };

   void SetLmk5Clkout5Dly(unsigned int value) {
      SetRegMask(WD2_LMK5_CLKOUT5_DLY_REG, WD2_LMK5_CLKOUT5_DLY_MASK, WD2_LMK5_CLKOUT5_DLY_OFS, value);
   };


   // Control Register 61: LMK_6 (offset 0x10F4) 
   unsigned int GetLmk6Clkout6Mux() {
      return BitExtractControl(WD2_LMK6_CLKOUT6_MUX_REG, WD2_LMK6_CLKOUT6_MUX_MASK, WD2_LMK6_CLKOUT6_MUX_OFS);
   };

   void SetLmk6Clkout6Mux(unsigned int value) {
      SetRegMask(WD2_LMK6_CLKOUT6_MUX_REG, WD2_LMK6_CLKOUT6_MUX_MASK, WD2_LMK6_CLKOUT6_MUX_OFS, value);
   };

   unsigned int GetLmk6Clkout6En() {
      return BitExtractControl(WD2_LMK6_CLKOUT6_EN_REG, WD2_LMK6_CLKOUT6_EN_MASK, WD2_LMK6_CLKOUT6_EN_OFS);
   };

   void SetLmk6Clkout6En(unsigned int value) {
      SetRegMask(WD2_LMK6_CLKOUT6_EN_REG, WD2_LMK6_CLKOUT6_EN_MASK, WD2_LMK6_CLKOUT6_EN_OFS, value);
   };

   unsigned int GetLmk6Clkout6Div() {
      return BitExtractControl(WD2_LMK6_CLKOUT6_DIV_REG, WD2_LMK6_CLKOUT6_DIV_MASK, WD2_LMK6_CLKOUT6_DIV_OFS);
   };

   void SetLmk6Clkout6Div(unsigned int value) {
      SetRegMask(WD2_LMK6_CLKOUT6_DIV_REG, WD2_LMK6_CLKOUT6_DIV_MASK, WD2_LMK6_CLKOUT6_DIV_OFS, value);
   };

   unsigned int GetLmk6Clkout6Dly() {
      return BitExtractControl(WD2_LMK6_CLKOUT6_DLY_REG, WD2_LMK6_CLKOUT6_DLY_MASK, WD2_LMK6_CLKOUT6_DLY_OFS);
   };

   void SetLmk6Clkout6Dly(unsigned int value) {
      SetRegMask(WD2_LMK6_CLKOUT6_DLY_REG, WD2_LMK6_CLKOUT6_DLY_MASK, WD2_LMK6_CLKOUT6_DLY_OFS, value);
   };


   // Control Register 62: LMK_7 (offset 0x10F8) 
   unsigned int GetLmk7Clkout7Mux() {
      return BitExtractControl(WD2_LMK7_CLKOUT7_MUX_REG, WD2_LMK7_CLKOUT7_MUX_MASK, WD2_LMK7_CLKOUT7_MUX_OFS);
   };

   void SetLmk7Clkout7Mux(unsigned int value) {
      SetRegMask(WD2_LMK7_CLKOUT7_MUX_REG, WD2_LMK7_CLKOUT7_MUX_MASK, WD2_LMK7_CLKOUT7_MUX_OFS, value);
   };

   unsigned int GetLmk7Clkout7En() {
      return BitExtractControl(WD2_LMK7_CLKOUT7_EN_REG, WD2_LMK7_CLKOUT7_EN_MASK, WD2_LMK7_CLKOUT7_EN_OFS);
   };

   void SetLmk7Clkout7En(unsigned int value) {
      SetRegMask(WD2_LMK7_CLKOUT7_EN_REG, WD2_LMK7_CLKOUT7_EN_MASK, WD2_LMK7_CLKOUT7_EN_OFS, value);
   };

   unsigned int GetLmk7Clkout7Div() {
      return BitExtractControl(WD2_LMK7_CLKOUT7_DIV_REG, WD2_LMK7_CLKOUT7_DIV_MASK, WD2_LMK7_CLKOUT7_DIV_OFS);
   };

   void SetLmk7Clkout7Div(unsigned int value) {
      SetRegMask(WD2_LMK7_CLKOUT7_DIV_REG, WD2_LMK7_CLKOUT7_DIV_MASK, WD2_LMK7_CLKOUT7_DIV_OFS, value);
   };

   unsigned int GetLmk7Clkout7Dly() {
      return BitExtractControl(WD2_LMK7_CLKOUT7_DLY_REG, WD2_LMK7_CLKOUT7_DLY_MASK, WD2_LMK7_CLKOUT7_DLY_OFS);
   };

   void SetLmk7Clkout7Dly(unsigned int value) {
      SetRegMask(WD2_LMK7_CLKOUT7_DLY_REG, WD2_LMK7_CLKOUT7_DLY_MASK, WD2_LMK7_CLKOUT7_DLY_OFS, value);
   };


   // Control Register 63: LMK_8 (offset 0x10FC) 
   unsigned int GetLmk8PhaseNoiseOpt() {
      return BitExtractControl(WD2_LMK8_PHASE_NOISE_OPT_REG, WD2_LMK8_PHASE_NOISE_OPT_MASK, WD2_LMK8_PHASE_NOISE_OPT_OFS);
   };

   void SetLmk8PhaseNoiseOpt(unsigned int value) {
      SetRegMask(WD2_LMK8_PHASE_NOISE_OPT_REG, WD2_LMK8_PHASE_NOISE_OPT_MASK, WD2_LMK8_PHASE_NOISE_OPT_OFS, value);
   };


   // Control Register 64: LMK_9 (offset 0x1100) 
   unsigned int GetLmk9Vboost() {
      return BitExtractControl(WD2_LMK9_VBOOST_REG, WD2_LMK9_VBOOST_MASK, WD2_LMK9_VBOOST_OFS);
   };

   void SetLmk9Vboost(unsigned int value) {
      SetRegMask(WD2_LMK9_VBOOST_REG, WD2_LMK9_VBOOST_MASK, WD2_LMK9_VBOOST_OFS, value);
   };


   // Control Register 65: LMK_11 (offset 0x1104) 
   unsigned int GetLmk11Div4() {
      return BitExtractControl(WD2_LMK11_DIV4_REG, WD2_LMK11_DIV4_MASK, WD2_LMK11_DIV4_OFS);
   };

   void SetLmk11Div4(unsigned int value) {
      SetRegMask(WD2_LMK11_DIV4_REG, WD2_LMK11_DIV4_MASK, WD2_LMK11_DIV4_OFS, value);
   };


   // Control Register 66: LMK_13 (offset 0x1108) 
   unsigned int GetLmk13OscinFreq() {
      return BitExtractControl(WD2_LMK13_OSCIN_FREQ_REG, WD2_LMK13_OSCIN_FREQ_MASK, WD2_LMK13_OSCIN_FREQ_OFS);
   };

   void SetLmk13OscinFreq(unsigned int value) {
      SetRegMask(WD2_LMK13_OSCIN_FREQ_REG, WD2_LMK13_OSCIN_FREQ_MASK, WD2_LMK13_OSCIN_FREQ_OFS, value);
   };

   unsigned int GetLmk13VcoR4Lf() {
      return BitExtractControl(WD2_LMK13_VCO_R4_LF_REG, WD2_LMK13_VCO_R4_LF_MASK, WD2_LMK13_VCO_R4_LF_OFS);
   };

   void SetLmk13VcoR4Lf(unsigned int value) {
      SetRegMask(WD2_LMK13_VCO_R4_LF_REG, WD2_LMK13_VCO_R4_LF_MASK, WD2_LMK13_VCO_R4_LF_OFS, value);
   };

   unsigned int GetLmk13VcoR3Lf() {
      return BitExtractControl(WD2_LMK13_VCO_R3_LF_REG, WD2_LMK13_VCO_R3_LF_MASK, WD2_LMK13_VCO_R3_LF_OFS);
   };

   void SetLmk13VcoR3Lf(unsigned int value) {
      SetRegMask(WD2_LMK13_VCO_R3_LF_REG, WD2_LMK13_VCO_R3_LF_MASK, WD2_LMK13_VCO_R3_LF_OFS, value);
   };

   unsigned int GetLmk13VcoC3C4Lf() {
      return BitExtractControl(WD2_LMK13_VCO_C3_C4_LF_REG, WD2_LMK13_VCO_C3_C4_LF_MASK, WD2_LMK13_VCO_C3_C4_LF_OFS);
   };

   void SetLmk13VcoC3C4Lf(unsigned int value) {
      SetRegMask(WD2_LMK13_VCO_C3_C4_LF_REG, WD2_LMK13_VCO_C3_C4_LF_MASK, WD2_LMK13_VCO_C3_C4_LF_OFS, value);
   };


   // Control Register 67: LMK_14 (offset 0x110C) 
   unsigned int GetLmk14EnFout() {
      return BitExtractControl(WD2_LMK14_EN_FOUT_REG, WD2_LMK14_EN_FOUT_MASK, WD2_LMK14_EN_FOUT_OFS);
   };

   void SetLmk14EnFout(unsigned int value) {
      SetRegMask(WD2_LMK14_EN_FOUT_REG, WD2_LMK14_EN_FOUT_MASK, WD2_LMK14_EN_FOUT_OFS, value);
   };

   unsigned int GetLmk14EnClkoutGlobal() {
      return BitExtractControl(WD2_LMK14_EN_CLKOUT_GLOBAL_REG, WD2_LMK14_EN_CLKOUT_GLOBAL_MASK, WD2_LMK14_EN_CLKOUT_GLOBAL_OFS);
   };

   void SetLmk14EnClkoutGlobal(unsigned int value) {
      SetRegMask(WD2_LMK14_EN_CLKOUT_GLOBAL_REG, WD2_LMK14_EN_CLKOUT_GLOBAL_MASK, WD2_LMK14_EN_CLKOUT_GLOBAL_OFS, value);
   };

   unsigned int GetLmk14Powerdown() {
      return BitExtractControl(WD2_LMK14_POWERDOWN_REG, WD2_LMK14_POWERDOWN_MASK, WD2_LMK14_POWERDOWN_OFS);
   };

   void SetLmk14Powerdown(unsigned int value) {
      SetRegMask(WD2_LMK14_POWERDOWN_REG, WD2_LMK14_POWERDOWN_MASK, WD2_LMK14_POWERDOWN_OFS, value);
   };

   unsigned int GetLmk14PllMux() {
      return BitExtractControl(WD2_LMK14_PLL_MUX_REG, WD2_LMK14_PLL_MUX_MASK, WD2_LMK14_PLL_MUX_OFS);
   };

   void SetLmk14PllMux(unsigned int value) {
      SetRegMask(WD2_LMK14_PLL_MUX_REG, WD2_LMK14_PLL_MUX_MASK, WD2_LMK14_PLL_MUX_OFS, value);
   };

   unsigned int GetLmk14PllR() {
      return BitExtractControl(WD2_LMK14_PLL_R_REG, WD2_LMK14_PLL_R_MASK, WD2_LMK14_PLL_R_OFS);
   };

   void SetLmk14PllR(unsigned int value) {
      SetRegMask(WD2_LMK14_PLL_R_REG, WD2_LMK14_PLL_R_MASK, WD2_LMK14_PLL_R_OFS, value);
   };


   // Control Register 68: LMK_15 (offset 0x1110) 
   unsigned int GetLmk15PllCpGain() {
      return BitExtractControl(WD2_LMK15_PLL_CP_GAIN_REG, WD2_LMK15_PLL_CP_GAIN_MASK, WD2_LMK15_PLL_CP_GAIN_OFS);
   };

   void SetLmk15PllCpGain(unsigned int value) {
      SetRegMask(WD2_LMK15_PLL_CP_GAIN_REG, WD2_LMK15_PLL_CP_GAIN_MASK, WD2_LMK15_PLL_CP_GAIN_OFS, value);
   };

   unsigned int GetLmk15VcoDiv() {
      return BitExtractControl(WD2_LMK15_VCO_DIV_REG, WD2_LMK15_VCO_DIV_MASK, WD2_LMK15_VCO_DIV_OFS);
   };

   void SetLmk15VcoDiv(unsigned int value) {
      SetRegMask(WD2_LMK15_VCO_DIV_REG, WD2_LMK15_VCO_DIV_MASK, WD2_LMK15_VCO_DIV_OFS, value);
   };

   unsigned int GetLmk15PllN() {
      return BitExtractControl(WD2_LMK15_PLL_N_REG, WD2_LMK15_PLL_N_MASK, WD2_LMK15_PLL_N_OFS);
   };

   void SetLmk15PllN(unsigned int value) {
      SetRegMask(WD2_LMK15_PLL_N_REG, WD2_LMK15_PLL_N_MASK, WD2_LMK15_PLL_N_OFS, value);
   };


   // Control Register 69: ADC_CFG_IND_TX (offset 0x1114) 
   unsigned int GetAdcCfgSdoActiveMsb() {
      return BitExtractControl(WD2_ADC_CFG_SDO_ACTIVE_MSB_REG, WD2_ADC_CFG_SDO_ACTIVE_MSB_MASK, WD2_ADC_CFG_SDO_ACTIVE_MSB_OFS);
   };

   void SetAdcCfgSdoActiveMsb(unsigned int value) {
      SetRegMask(WD2_ADC_CFG_SDO_ACTIVE_MSB_REG, WD2_ADC_CFG_SDO_ACTIVE_MSB_MASK, WD2_ADC_CFG_SDO_ACTIVE_MSB_OFS, value);
   };

   unsigned int GetAdcCfgLsbFirstMsb() {
      return BitExtractControl(WD2_ADC_CFG_LSB_FIRST_MSB_REG, WD2_ADC_CFG_LSB_FIRST_MSB_MASK, WD2_ADC_CFG_LSB_FIRST_MSB_OFS);
   };

   void SetAdcCfgLsbFirstMsb(unsigned int value) {
      SetRegMask(WD2_ADC_CFG_LSB_FIRST_MSB_REG, WD2_ADC_CFG_LSB_FIRST_MSB_MASK, WD2_ADC_CFG_LSB_FIRST_MSB_OFS, value);
   };

   unsigned int GetAdcCfgSoftResetMsb() {
      return BitExtractControl(WD2_ADC_CFG_SOFT_RESET_MSB_REG, WD2_ADC_CFG_SOFT_RESET_MSB_MASK, WD2_ADC_CFG_SOFT_RESET_MSB_OFS);
   };

   void SetAdcCfgSoftResetMsb(unsigned int value) {
      SetRegMask(WD2_ADC_CFG_SOFT_RESET_MSB_REG, WD2_ADC_CFG_SOFT_RESET_MSB_MASK, WD2_ADC_CFG_SOFT_RESET_MSB_OFS, value);
   };

   unsigned int GetAdcCfg16BitAddrMsb() {
      return BitExtractControl(WD2_ADC_CFG_16_BIT_ADDR_MSB_REG, WD2_ADC_CFG_16_BIT_ADDR_MSB_MASK, WD2_ADC_CFG_16_BIT_ADDR_MSB_OFS);
   };

   void SetAdcCfg16BitAddrMsb(unsigned int value) {
      SetRegMask(WD2_ADC_CFG_16_BIT_ADDR_MSB_REG, WD2_ADC_CFG_16_BIT_ADDR_MSB_MASK, WD2_ADC_CFG_16_BIT_ADDR_MSB_OFS, value);
   };

   unsigned int GetAdcCfg16BitAddrLsb() {
      return BitExtractControl(WD2_ADC_CFG_16_BIT_ADDR_LSB_REG, WD2_ADC_CFG_16_BIT_ADDR_LSB_MASK, WD2_ADC_CFG_16_BIT_ADDR_LSB_OFS);
   };

   void SetAdcCfg16BitAddrLsb(unsigned int value) {
      SetRegMask(WD2_ADC_CFG_16_BIT_ADDR_LSB_REG, WD2_ADC_CFG_16_BIT_ADDR_LSB_MASK, WD2_ADC_CFG_16_BIT_ADDR_LSB_OFS, value);
   };

   unsigned int GetAdcCfgSoftResetLsb() {
      return BitExtractControl(WD2_ADC_CFG_SOFT_RESET_LSB_REG, WD2_ADC_CFG_SOFT_RESET_LSB_MASK, WD2_ADC_CFG_SOFT_RESET_LSB_OFS);
   };

   void SetAdcCfgSoftResetLsb(unsigned int value) {
      SetRegMask(WD2_ADC_CFG_SOFT_RESET_LSB_REG, WD2_ADC_CFG_SOFT_RESET_LSB_MASK, WD2_ADC_CFG_SOFT_RESET_LSB_OFS, value);
   };

   unsigned int GetAdcCfgLsbFirstLsb() {
      return BitExtractControl(WD2_ADC_CFG_LSB_FIRST_LSB_REG, WD2_ADC_CFG_LSB_FIRST_LSB_MASK, WD2_ADC_CFG_LSB_FIRST_LSB_OFS);
   };

   void SetAdcCfgLsbFirstLsb(unsigned int value) {
      SetRegMask(WD2_ADC_CFG_LSB_FIRST_LSB_REG, WD2_ADC_CFG_LSB_FIRST_LSB_MASK, WD2_ADC_CFG_LSB_FIRST_LSB_OFS, value);
   };

   unsigned int GetAdcCfgSdoActiveLsb() {
      return BitExtractControl(WD2_ADC_CFG_SDO_ACTIVE_LSB_REG, WD2_ADC_CFG_SDO_ACTIVE_LSB_MASK, WD2_ADC_CFG_SDO_ACTIVE_LSB_OFS);
   };

   void SetAdcCfgSdoActiveLsb(unsigned int value) {
      SetRegMask(WD2_ADC_CFG_SDO_ACTIVE_LSB_REG, WD2_ADC_CFG_SDO_ACTIVE_LSB_MASK, WD2_ADC_CFG_SDO_ACTIVE_LSB_OFS, value);
   };

   unsigned int GetAdcDi2DChnH() {
      return BitExtractControl(WD2_ADC_DI2_D_CHN_H_REG, WD2_ADC_DI2_D_CHN_H_MASK, WD2_ADC_DI2_D_CHN_H_OFS);
   };

   void SetAdcDi2DChnH(unsigned int value) {
      SetRegMask(WD2_ADC_DI2_D_CHN_H_REG, WD2_ADC_DI2_D_CHN_H_MASK, WD2_ADC_DI2_D_CHN_H_OFS, value);
   };

   unsigned int GetAdcDi2DChnG() {
      return BitExtractControl(WD2_ADC_DI2_D_CHN_G_REG, WD2_ADC_DI2_D_CHN_G_MASK, WD2_ADC_DI2_D_CHN_G_OFS);
   };

   void SetAdcDi2DChnG(unsigned int value) {
      SetRegMask(WD2_ADC_DI2_D_CHN_G_REG, WD2_ADC_DI2_D_CHN_G_MASK, WD2_ADC_DI2_D_CHN_G_OFS, value);
   };

   unsigned int GetAdcDi2DChnF() {
      return BitExtractControl(WD2_ADC_DI2_D_CHN_F_REG, WD2_ADC_DI2_D_CHN_F_MASK, WD2_ADC_DI2_D_CHN_F_OFS);
   };

   void SetAdcDi2DChnF(unsigned int value) {
      SetRegMask(WD2_ADC_DI2_D_CHN_F_REG, WD2_ADC_DI2_D_CHN_F_MASK, WD2_ADC_DI2_D_CHN_F_OFS, value);
   };

   unsigned int GetAdcDi2DChnE() {
      return BitExtractControl(WD2_ADC_DI2_D_CHN_E_REG, WD2_ADC_DI2_D_CHN_E_MASK, WD2_ADC_DI2_D_CHN_E_OFS);
   };

   void SetAdcDi2DChnE(unsigned int value) {
      SetRegMask(WD2_ADC_DI2_D_CHN_E_REG, WD2_ADC_DI2_D_CHN_E_MASK, WD2_ADC_DI2_D_CHN_E_OFS, value);
   };

   unsigned int GetAdcDi1CChnDco() {
      return BitExtractControl(WD2_ADC_DI1_C_CHN_DCO_REG, WD2_ADC_DI1_C_CHN_DCO_MASK, WD2_ADC_DI1_C_CHN_DCO_OFS);
   };

   void SetAdcDi1CChnDco(unsigned int value) {
      SetRegMask(WD2_ADC_DI1_C_CHN_DCO_REG, WD2_ADC_DI1_C_CHN_DCO_MASK, WD2_ADC_DI1_C_CHN_DCO_OFS, value);
   };

   unsigned int GetAdcDi1CChnFco() {
      return BitExtractControl(WD2_ADC_DI1_C_CHN_FCO_REG, WD2_ADC_DI1_C_CHN_FCO_MASK, WD2_ADC_DI1_C_CHN_FCO_OFS);
   };

   void SetAdcDi1CChnFco(unsigned int value) {
      SetRegMask(WD2_ADC_DI1_C_CHN_FCO_REG, WD2_ADC_DI1_C_CHN_FCO_MASK, WD2_ADC_DI1_C_CHN_FCO_OFS, value);
   };

   unsigned int GetAdcDi1DChnD() {
      return BitExtractControl(WD2_ADC_DI1_D_CHN_D_REG, WD2_ADC_DI1_D_CHN_D_MASK, WD2_ADC_DI1_D_CHN_D_OFS);
   };

   void SetAdcDi1DChnD(unsigned int value) {
      SetRegMask(WD2_ADC_DI1_D_CHN_D_REG, WD2_ADC_DI1_D_CHN_D_MASK, WD2_ADC_DI1_D_CHN_D_OFS, value);
   };

   unsigned int GetAdcDi1DChnC() {
      return BitExtractControl(WD2_ADC_DI1_D_CHN_C_REG, WD2_ADC_DI1_D_CHN_C_MASK, WD2_ADC_DI1_D_CHN_C_OFS);
   };

   void SetAdcDi1DChnC(unsigned int value) {
      SetRegMask(WD2_ADC_DI1_D_CHN_C_REG, WD2_ADC_DI1_D_CHN_C_MASK, WD2_ADC_DI1_D_CHN_C_OFS, value);
   };

   unsigned int GetAdcDi1DChnB() {
      return BitExtractControl(WD2_ADC_DI1_D_CHN_B_REG, WD2_ADC_DI1_D_CHN_B_MASK, WD2_ADC_DI1_D_CHN_B_OFS);
   };

   void SetAdcDi1DChnB(unsigned int value) {
      SetRegMask(WD2_ADC_DI1_D_CHN_B_REG, WD2_ADC_DI1_D_CHN_B_MASK, WD2_ADC_DI1_D_CHN_B_OFS, value);
   };

   unsigned int GetAdcDi1DChnA() {
      return BitExtractControl(WD2_ADC_DI1_D_CHN_A_REG, WD2_ADC_DI1_D_CHN_A_MASK, WD2_ADC_DI1_D_CHN_A_OFS);
   };

   void SetAdcDi1DChnA(unsigned int value) {
      SetRegMask(WD2_ADC_DI1_D_CHN_A_REG, WD2_ADC_DI1_D_CHN_A_MASK, WD2_ADC_DI1_D_CHN_A_OFS, value);
   };

   unsigned int GetAdcTxInitOverride() {
      return BitExtractControl(WD2_ADC_TX_INIT_OVERRIDE_REG, WD2_ADC_TX_INIT_OVERRIDE_MASK, WD2_ADC_TX_INIT_OVERRIDE_OFS);
   };

   void SetAdcTxInitOverride(unsigned int value) {
      SetRegMask(WD2_ADC_TX_INIT_OVERRIDE_REG, WD2_ADC_TX_INIT_OVERRIDE_MASK, WD2_ADC_TX_INIT_OVERRIDE_OFS, value);
   };


   // Control Register 70: ADC_PM_CLK_ENH (offset 0x1118) 
   unsigned int GetAdcPmExtPd() {
      return BitExtractControl(WD2_ADC_PM_EXT_PD_REG, WD2_ADC_PM_EXT_PD_MASK, WD2_ADC_PM_EXT_PD_OFS);
   };

   void SetAdcPmExtPd(unsigned int value) {
      SetRegMask(WD2_ADC_PM_EXT_PD_REG, WD2_ADC_PM_EXT_PD_MASK, WD2_ADC_PM_EXT_PD_OFS, value);
   };

   unsigned int GetAdcPmIntPdMode() {
      return BitExtractControl(WD2_ADC_PM_INT_PD_MODE_REG, WD2_ADC_PM_INT_PD_MODE_MASK, WD2_ADC_PM_INT_PD_MODE_OFS);
   };

   void SetAdcPmIntPdMode(unsigned int value) {
      SetRegMask(WD2_ADC_PM_INT_PD_MODE_REG, WD2_ADC_PM_INT_PD_MODE_MASK, WD2_ADC_PM_INT_PD_MODE_OFS, value);
   };

   unsigned int GetAdcClkDutyCycStab() {
      return BitExtractControl(WD2_ADC_CLK_DUTY_CYC_STAB_REG, WD2_ADC_CLK_DUTY_CYC_STAB_MASK, WD2_ADC_CLK_DUTY_CYC_STAB_OFS);
   };

   void SetAdcClkDutyCycStab(unsigned int value) {
      SetRegMask(WD2_ADC_CLK_DUTY_CYC_STAB_REG, WD2_ADC_CLK_DUTY_CYC_STAB_MASK, WD2_ADC_CLK_DUTY_CYC_STAB_OFS, value);
   };

   unsigned int GetAdcClkDivRatio() {
      return BitExtractControl(WD2_ADC_CLK_DIV_RATIO_REG, WD2_ADC_CLK_DIV_RATIO_MASK, WD2_ADC_CLK_DIV_RATIO_OFS);
   };

   void SetAdcClkDivRatio(unsigned int value) {
      SetRegMask(WD2_ADC_CLK_DIV_RATIO_REG, WD2_ADC_CLK_DIV_RATIO_MASK, WD2_ADC_CLK_DIV_RATIO_OFS, value);
   };

   unsigned int GetAdcEnhChopMode() {
      return BitExtractControl(WD2_ADC_ENH_CHOP_MODE_REG, WD2_ADC_ENH_CHOP_MODE_MASK, WD2_ADC_ENH_CHOP_MODE_OFS);
   };

   void SetAdcEnhChopMode(unsigned int value) {
      SetRegMask(WD2_ADC_ENH_CHOP_MODE_REG, WD2_ADC_ENH_CHOP_MODE_MASK, WD2_ADC_ENH_CHOP_MODE_OFS, value);
   };


   // Control Register 71: ADC_TEST_OFFS_OM (offset 0x111C) 
   unsigned int GetAdcTmUsrInMode() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_REG, WD2_ADC_TM_USR_IN_MODE_MASK, WD2_ADC_TM_USR_IN_MODE_OFS);
   };

   void SetAdcTmUsrInMode(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_REG, WD2_ADC_TM_USR_IN_MODE_MASK, WD2_ADC_TM_USR_IN_MODE_OFS, value);
   };

   unsigned int GetAdcTmRstPnLongGen() {
      return BitExtractControl(WD2_ADC_TM_RST_PN_LONG_GEN_REG, WD2_ADC_TM_RST_PN_LONG_GEN_MASK, WD2_ADC_TM_RST_PN_LONG_GEN_OFS);
   };

   void SetAdcTmRstPnLongGen(unsigned int value) {
      SetRegMask(WD2_ADC_TM_RST_PN_LONG_GEN_REG, WD2_ADC_TM_RST_PN_LONG_GEN_MASK, WD2_ADC_TM_RST_PN_LONG_GEN_OFS, value);
   };

   unsigned int GetAdcTmRstPnShortGen() {
      return BitExtractControl(WD2_ADC_TM_RST_PN_SHORT_GEN_REG, WD2_ADC_TM_RST_PN_SHORT_GEN_MASK, WD2_ADC_TM_RST_PN_SHORT_GEN_OFS);
   };

   void SetAdcTmRstPnShortGen(unsigned int value) {
      SetRegMask(WD2_ADC_TM_RST_PN_SHORT_GEN_REG, WD2_ADC_TM_RST_PN_SHORT_GEN_MASK, WD2_ADC_TM_RST_PN_SHORT_GEN_OFS, value);
   };

   unsigned int GetAdcTmOut() {
      return BitExtractControl(WD2_ADC_TM_OUT_REG, WD2_ADC_TM_OUT_MASK, WD2_ADC_TM_OUT_OFS);
   };

   void SetAdcTmOut(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_REG, WD2_ADC_TM_OUT_MASK, WD2_ADC_TM_OUT_OFS, value);
   };

   unsigned int GetAdcOffsAdj() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_REG, WD2_ADC_OFFS_ADJ_MASK, WD2_ADC_OFFS_ADJ_OFS);
   };

   void SetAdcOffsAdj(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_REG, WD2_ADC_OFFS_ADJ_MASK, WD2_ADC_OFFS_ADJ_OFS, value);
   };

   unsigned int GetAdcOmLvdsMode() {
      return BitExtractControl(WD2_ADC_OM_LVDS_MODE_REG, WD2_ADC_OM_LVDS_MODE_MASK, WD2_ADC_OM_LVDS_MODE_OFS);
   };

   void SetAdcOmLvdsMode(unsigned int value) {
      SetRegMask(WD2_ADC_OM_LVDS_MODE_REG, WD2_ADC_OM_LVDS_MODE_MASK, WD2_ADC_OM_LVDS_MODE_OFS, value);
   };

   unsigned int GetAdcOmOutInvert() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_REG, WD2_ADC_OM_OUT_INVERT_MASK, WD2_ADC_OM_OUT_INVERT_OFS);
   };

   void SetAdcOmOutInvert(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_REG, WD2_ADC_OM_OUT_INVERT_MASK, WD2_ADC_OM_OUT_INVERT_OFS, value);
   };

   unsigned int GetAdcOmOutFormat() {
      return BitExtractControl(WD2_ADC_OM_OUT_FORMAT_REG, WD2_ADC_OM_OUT_FORMAT_MASK, WD2_ADC_OM_OUT_FORMAT_OFS);
   };

   void SetAdcOmOutFormat(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_FORMAT_REG, WD2_ADC_OM_OUT_FORMAT_MASK, WD2_ADC_OM_OUT_FORMAT_OFS, value);
   };


   // Control Register 72: ADC_OUT_VREF (offset 0x1120) 
   unsigned int GetAdcOaOutDrvTerm() {
      return BitExtractControl(WD2_ADC_OA_OUT_DRV_TERM_REG, WD2_ADC_OA_OUT_DRV_TERM_MASK, WD2_ADC_OA_OUT_DRV_TERM_OFS);
   };

   void SetAdcOaOutDrvTerm(unsigned int value) {
      SetRegMask(WD2_ADC_OA_OUT_DRV_TERM_REG, WD2_ADC_OA_OUT_DRV_TERM_MASK, WD2_ADC_OA_OUT_DRV_TERM_OFS, value);
   };

   unsigned int GetAdcOaOutDrive() {
      return BitExtractControl(WD2_ADC_OA_OUT_DRIVE_REG, WD2_ADC_OA_OUT_DRIVE_MASK, WD2_ADC_OA_OUT_DRIVE_OFS);
   };

   void SetAdcOaOutDrive(unsigned int value) {
      SetRegMask(WD2_ADC_OA_OUT_DRIVE_REG, WD2_ADC_OA_OUT_DRIVE_MASK, WD2_ADC_OA_OUT_DRIVE_OFS, value);
   };

   unsigned int GetAdcOpInClkPhAdj() {
      return BitExtractControl(WD2_ADC_OP_IN_CLK_PH_ADJ_REG, WD2_ADC_OP_IN_CLK_PH_ADJ_MASK, WD2_ADC_OP_IN_CLK_PH_ADJ_OFS);
   };

   void SetAdcOpInClkPhAdj(unsigned int value) {
      SetRegMask(WD2_ADC_OP_IN_CLK_PH_ADJ_REG, WD2_ADC_OP_IN_CLK_PH_ADJ_MASK, WD2_ADC_OP_IN_CLK_PH_ADJ_OFS, value);
   };

   unsigned int GetAdcOpOutClkPhAdj() {
      return BitExtractControl(WD2_ADC_OP_OUT_CLK_PH_ADJ_REG, WD2_ADC_OP_OUT_CLK_PH_ADJ_MASK, WD2_ADC_OP_OUT_CLK_PH_ADJ_OFS);
   };

   void SetAdcOpOutClkPhAdj(unsigned int value) {
      SetRegMask(WD2_ADC_OP_OUT_CLK_PH_ADJ_REG, WD2_ADC_OP_OUT_CLK_PH_ADJ_MASK, WD2_ADC_OP_OUT_CLK_PH_ADJ_OFS, value);
   };

   unsigned int GetAdcIntVrefAdj() {
      return BitExtractControl(WD2_ADC_INT_VREF_ADJ_REG, WD2_ADC_INT_VREF_ADJ_MASK, WD2_ADC_INT_VREF_ADJ_OFS);
   };

   void SetAdcIntVrefAdj(unsigned int value) {
      SetRegMask(WD2_ADC_INT_VREF_ADJ_REG, WD2_ADC_INT_VREF_ADJ_MASK, WD2_ADC_INT_VREF_ADJ_OFS, value);
   };


   // Control Register 73: ADC_USR_PATT (offset 0x1124) 
   unsigned int GetAdcUsrPatt1() {
      return BitExtractControl(WD2_ADC_USR_PATT1_REG, WD2_ADC_USR_PATT1_MASK, WD2_ADC_USR_PATT1_OFS);
   };

   void SetAdcUsrPatt1(unsigned int value) {
      SetRegMask(WD2_ADC_USR_PATT1_REG, WD2_ADC_USR_PATT1_MASK, WD2_ADC_USR_PATT1_OFS, value);
   };

   unsigned int GetAdcUsrPatt2() {
      return BitExtractControl(WD2_ADC_USR_PATT2_REG, WD2_ADC_USR_PATT2_MASK, WD2_ADC_USR_PATT2_OFS);
   };

   void SetAdcUsrPatt2(unsigned int value) {
      SetRegMask(WD2_ADC_USR_PATT2_REG, WD2_ADC_USR_PATT2_MASK, WD2_ADC_USR_PATT2_OFS, value);
   };


   // Control Register 74: ADC_SER_RES_SR (offset 0x1128) 
   unsigned int GetAdcScLvdsOutLsbFirst() {
      return BitExtractControl(WD2_ADC_SC_LVDS_OUT_LSB_FIRST_REG, WD2_ADC_SC_LVDS_OUT_LSB_FIRST_MASK, WD2_ADC_SC_LVDS_OUT_LSB_FIRST_OFS);
   };

   void SetAdcScLvdsOutLsbFirst(unsigned int value) {
      SetRegMask(WD2_ADC_SC_LVDS_OUT_LSB_FIRST_REG, WD2_ADC_SC_LVDS_OUT_LSB_FIRST_MASK, WD2_ADC_SC_LVDS_OUT_LSB_FIRST_OFS, value);
   };

   unsigned int GetAdcScWordWiseDdr() {
      return BitExtractControl(WD2_ADC_SC_WORD_WISE_DDR_REG, WD2_ADC_SC_WORD_WISE_DDR_MASK, WD2_ADC_SC_WORD_WISE_DDR_OFS);
   };

   void SetAdcScWordWiseDdr(unsigned int value) {
      SetRegMask(WD2_ADC_SC_WORD_WISE_DDR_REG, WD2_ADC_SC_WORD_WISE_DDR_MASK, WD2_ADC_SC_WORD_WISE_DDR_OFS, value);
   };

   unsigned int GetAdcScOutNrBits() {
      return BitExtractControl(WD2_ADC_SC_OUT_NR_BITS_REG, WD2_ADC_SC_OUT_NR_BITS_MASK, WD2_ADC_SC_OUT_NR_BITS_OFS);
   };

   void SetAdcScOutNrBits(unsigned int value) {
      SetRegMask(WD2_ADC_SC_OUT_NR_BITS_REG, WD2_ADC_SC_OUT_NR_BITS_MASK, WD2_ADC_SC_OUT_NR_BITS_OFS, value);
   };

   unsigned int GetAdcScOutRst() {
      return BitExtractControl(WD2_ADC_SC_OUT_RST_REG, WD2_ADC_SC_OUT_RST_MASK, WD2_ADC_SC_OUT_RST_OFS);
   };

   void SetAdcScOutRst(unsigned int value) {
      SetRegMask(WD2_ADC_SC_OUT_RST_REG, WD2_ADC_SC_OUT_RST_MASK, WD2_ADC_SC_OUT_RST_OFS, value);
   };

   unsigned int GetAdcScPwrDn() {
      return BitExtractControl(WD2_ADC_SC_PWR_DN_REG, WD2_ADC_SC_PWR_DN_MASK, WD2_ADC_SC_PWR_DN_OFS);
   };

   void SetAdcScPwrDn(unsigned int value) {
      SetRegMask(WD2_ADC_SC_PWR_DN_REG, WD2_ADC_SC_PWR_DN_MASK, WD2_ADC_SC_PWR_DN_OFS, value);
   };

   unsigned int GetAdcResSrOvr() {
      return BitExtractControl(WD2_ADC_RES_SR_OVR_REG, WD2_ADC_RES_SR_OVR_MASK, WD2_ADC_RES_SR_OVR_OFS);
   };

   void SetAdcResSrOvr(unsigned int value) {
      SetRegMask(WD2_ADC_RES_SR_OVR_REG, WD2_ADC_RES_SR_OVR_MASK, WD2_ADC_RES_SR_OVR_OFS, value);
   };

   unsigned int GetAdcResolution() {
      return BitExtractControl(WD2_ADC_RESOLUTION_REG, WD2_ADC_RESOLUTION_MASK, WD2_ADC_RESOLUTION_OFS);
   };

   void SetAdcResolution(unsigned int value) {
      SetRegMask(WD2_ADC_RESOLUTION_REG, WD2_ADC_RESOLUTION_MASK, WD2_ADC_RESOLUTION_OFS, value);
   };

   unsigned int GetAdcSampleRate() {
      return BitExtractControl(WD2_ADC_SAMPLE_RATE_REG, WD2_ADC_SAMPLE_RATE_MASK, WD2_ADC_SAMPLE_RATE_OFS);
   };

   void SetAdcSampleRate(unsigned int value) {
      SetRegMask(WD2_ADC_SAMPLE_RATE_REG, WD2_ADC_SAMPLE_RATE_MASK, WD2_ADC_SAMPLE_RATE_OFS, value);
   };


   // Control Register 75: ADC_USR_IO_SYNC (offset 0x112C) 
   unsigned int GetAdcUioc2SdioPd() {
      return BitExtractControl(WD2_ADC_UIOC2_SDIO_PD_REG, WD2_ADC_UIOC2_SDIO_PD_MASK, WD2_ADC_UIOC2_SDIO_PD_OFS);
   };

   void SetAdcUioc2SdioPd(unsigned int value) {
      SetRegMask(WD2_ADC_UIOC2_SDIO_PD_REG, WD2_ADC_UIOC2_SDIO_PD_MASK, WD2_ADC_UIOC2_SDIO_PD_OFS, value);
   };

   unsigned int GetAdcUioc3VcmPwrDn() {
      return BitExtractControl(WD2_ADC_UIOC3_VCM_PWR_DN_REG, WD2_ADC_UIOC3_VCM_PWR_DN_MASK, WD2_ADC_UIOC3_VCM_PWR_DN_OFS);
   };

   void SetAdcUioc3VcmPwrDn(unsigned int value) {
      SetRegMask(WD2_ADC_UIOC3_VCM_PWR_DN_REG, WD2_ADC_UIOC3_VCM_PWR_DN_MASK, WD2_ADC_UIOC3_VCM_PWR_DN_OFS, value);
   };

   unsigned int GetAdcSyncNextOnly() {
      return BitExtractControl(WD2_ADC_SYNC_NEXT_ONLY_REG, WD2_ADC_SYNC_NEXT_ONLY_MASK, WD2_ADC_SYNC_NEXT_ONLY_OFS);
   };

   void SetAdcSyncNextOnly(unsigned int value) {
      SetRegMask(WD2_ADC_SYNC_NEXT_ONLY_REG, WD2_ADC_SYNC_NEXT_ONLY_MASK, WD2_ADC_SYNC_NEXT_ONLY_OFS, value);
   };

   unsigned int GetAdcEnSync() {
      return BitExtractControl(WD2_ADC_EN_SYNC_REG, WD2_ADC_EN_SYNC_MASK, WD2_ADC_EN_SYNC_OFS);
   };

   void SetAdcEnSync(unsigned int value) {
      SetRegMask(WD2_ADC_EN_SYNC_REG, WD2_ADC_EN_SYNC_MASK, WD2_ADC_EN_SYNC_OFS, value);
   };


   // Control Register 76: ADC_0_CH_A_CFG (offset 0x1130) 
   unsigned int GetAdcTmUsrInMode0A() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_0_A_REG, WD2_ADC_TM_USR_IN_MODE_0_A_MASK, WD2_ADC_TM_USR_IN_MODE_0_A_OFS);
   };

   void SetAdcTmUsrInMode0A(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_0_A_REG, WD2_ADC_TM_USR_IN_MODE_0_A_MASK, WD2_ADC_TM_USR_IN_MODE_0_A_OFS, value);
   };

   unsigned int GetAdcTmOut0A() {
      return BitExtractControl(WD2_ADC_TM_OUT_0_A_REG, WD2_ADC_TM_OUT_0_A_MASK, WD2_ADC_TM_OUT_0_A_OFS);
   };

   void SetAdcTmOut0A(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_0_A_REG, WD2_ADC_TM_OUT_0_A_MASK, WD2_ADC_TM_OUT_0_A_OFS, value);
   };

   unsigned int GetAdcOffsAdj0A() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_0_A_REG, WD2_ADC_OFFS_ADJ_0_A_MASK, WD2_ADC_OFFS_ADJ_0_A_OFS);
   };

   void SetAdcOffsAdj0A(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_0_A_REG, WD2_ADC_OFFS_ADJ_0_A_MASK, WD2_ADC_OFFS_ADJ_0_A_OFS, value);
   };

   unsigned int GetAdcOmOutInvert0A() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_0_A_REG, WD2_ADC_OM_OUT_INVERT_0_A_MASK, WD2_ADC_OM_OUT_INVERT_0_A_OFS);
   };

   void SetAdcOmOutInvert0A(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_0_A_REG, WD2_ADC_OM_OUT_INVERT_0_A_MASK, WD2_ADC_OM_OUT_INVERT_0_A_OFS, value);
   };


   // Control Register 77: ADC_0_CH_B_CFG (offset 0x1134) 
   unsigned int GetAdcTmUsrInMode0B() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_0_B_REG, WD2_ADC_TM_USR_IN_MODE_0_B_MASK, WD2_ADC_TM_USR_IN_MODE_0_B_OFS);
   };

   void SetAdcTmUsrInMode0B(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_0_B_REG, WD2_ADC_TM_USR_IN_MODE_0_B_MASK, WD2_ADC_TM_USR_IN_MODE_0_B_OFS, value);
   };

   unsigned int GetAdcTmOut0B() {
      return BitExtractControl(WD2_ADC_TM_OUT_0_B_REG, WD2_ADC_TM_OUT_0_B_MASK, WD2_ADC_TM_OUT_0_B_OFS);
   };

   void SetAdcTmOut0B(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_0_B_REG, WD2_ADC_TM_OUT_0_B_MASK, WD2_ADC_TM_OUT_0_B_OFS, value);
   };

   unsigned int GetAdcOffsAdj0B() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_0_B_REG, WD2_ADC_OFFS_ADJ_0_B_MASK, WD2_ADC_OFFS_ADJ_0_B_OFS);
   };

   void SetAdcOffsAdj0B(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_0_B_REG, WD2_ADC_OFFS_ADJ_0_B_MASK, WD2_ADC_OFFS_ADJ_0_B_OFS, value);
   };

   unsigned int GetAdcOmOutInvert0B() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_0_B_REG, WD2_ADC_OM_OUT_INVERT_0_B_MASK, WD2_ADC_OM_OUT_INVERT_0_B_OFS);
   };

   void SetAdcOmOutInvert0B(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_0_B_REG, WD2_ADC_OM_OUT_INVERT_0_B_MASK, WD2_ADC_OM_OUT_INVERT_0_B_OFS, value);
   };


   // Control Register 78: ADC_0_CH_C_CFG (offset 0x1138) 
   unsigned int GetAdcTmUsrInMode0C() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_0_C_REG, WD2_ADC_TM_USR_IN_MODE_0_C_MASK, WD2_ADC_TM_USR_IN_MODE_0_C_OFS);
   };

   void SetAdcTmUsrInMode0C(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_0_C_REG, WD2_ADC_TM_USR_IN_MODE_0_C_MASK, WD2_ADC_TM_USR_IN_MODE_0_C_OFS, value);
   };

   unsigned int GetAdcTmOut0C() {
      return BitExtractControl(WD2_ADC_TM_OUT_0_C_REG, WD2_ADC_TM_OUT_0_C_MASK, WD2_ADC_TM_OUT_0_C_OFS);
   };

   void SetAdcTmOut0C(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_0_C_REG, WD2_ADC_TM_OUT_0_C_MASK, WD2_ADC_TM_OUT_0_C_OFS, value);
   };

   unsigned int GetAdcOffsAdj0C() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_0_C_REG, WD2_ADC_OFFS_ADJ_0_C_MASK, WD2_ADC_OFFS_ADJ_0_C_OFS);
   };

   void SetAdcOffsAdj0C(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_0_C_REG, WD2_ADC_OFFS_ADJ_0_C_MASK, WD2_ADC_OFFS_ADJ_0_C_OFS, value);
   };

   unsigned int GetAdcOmOutInvert0C() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_0_C_REG, WD2_ADC_OM_OUT_INVERT_0_C_MASK, WD2_ADC_OM_OUT_INVERT_0_C_OFS);
   };

   void SetAdcOmOutInvert0C(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_0_C_REG, WD2_ADC_OM_OUT_INVERT_0_C_MASK, WD2_ADC_OM_OUT_INVERT_0_C_OFS, value);
   };


   // Control Register 79: ADC_0_CH_D_CFG (offset 0x113C) 
   unsigned int GetAdcTmUsrInMode0D() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_0_D_REG, WD2_ADC_TM_USR_IN_MODE_0_D_MASK, WD2_ADC_TM_USR_IN_MODE_0_D_OFS);
   };

   void SetAdcTmUsrInMode0D(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_0_D_REG, WD2_ADC_TM_USR_IN_MODE_0_D_MASK, WD2_ADC_TM_USR_IN_MODE_0_D_OFS, value);
   };

   unsigned int GetAdcTmOut0D() {
      return BitExtractControl(WD2_ADC_TM_OUT_0_D_REG, WD2_ADC_TM_OUT_0_D_MASK, WD2_ADC_TM_OUT_0_D_OFS);
   };

   void SetAdcTmOut0D(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_0_D_REG, WD2_ADC_TM_OUT_0_D_MASK, WD2_ADC_TM_OUT_0_D_OFS, value);
   };

   unsigned int GetAdcOffsAdj0D() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_0_D_REG, WD2_ADC_OFFS_ADJ_0_D_MASK, WD2_ADC_OFFS_ADJ_0_D_OFS);
   };

   void SetAdcOffsAdj0D(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_0_D_REG, WD2_ADC_OFFS_ADJ_0_D_MASK, WD2_ADC_OFFS_ADJ_0_D_OFS, value);
   };

   unsigned int GetAdcOmOutInvert0D() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_0_D_REG, WD2_ADC_OM_OUT_INVERT_0_D_MASK, WD2_ADC_OM_OUT_INVERT_0_D_OFS);
   };

   void SetAdcOmOutInvert0D(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_0_D_REG, WD2_ADC_OM_OUT_INVERT_0_D_MASK, WD2_ADC_OM_OUT_INVERT_0_D_OFS, value);
   };


   // Control Register 80: ADC_0_CH_E_CFG (offset 0x1140) 
   unsigned int GetAdcTmUsrInMode0E() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_0_E_REG, WD2_ADC_TM_USR_IN_MODE_0_E_MASK, WD2_ADC_TM_USR_IN_MODE_0_E_OFS);
   };

   void SetAdcTmUsrInMode0E(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_0_E_REG, WD2_ADC_TM_USR_IN_MODE_0_E_MASK, WD2_ADC_TM_USR_IN_MODE_0_E_OFS, value);
   };

   unsigned int GetAdcTmOut0E() {
      return BitExtractControl(WD2_ADC_TM_OUT_0_E_REG, WD2_ADC_TM_OUT_0_E_MASK, WD2_ADC_TM_OUT_0_E_OFS);
   };

   void SetAdcTmOut0E(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_0_E_REG, WD2_ADC_TM_OUT_0_E_MASK, WD2_ADC_TM_OUT_0_E_OFS, value);
   };

   unsigned int GetAdcOffsAdj0E() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_0_E_REG, WD2_ADC_OFFS_ADJ_0_E_MASK, WD2_ADC_OFFS_ADJ_0_E_OFS);
   };

   void SetAdcOffsAdj0E(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_0_E_REG, WD2_ADC_OFFS_ADJ_0_E_MASK, WD2_ADC_OFFS_ADJ_0_E_OFS, value);
   };

   unsigned int GetAdcOmOutInvert0E() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_0_E_REG, WD2_ADC_OM_OUT_INVERT_0_E_MASK, WD2_ADC_OM_OUT_INVERT_0_E_OFS);
   };

   void SetAdcOmOutInvert0E(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_0_E_REG, WD2_ADC_OM_OUT_INVERT_0_E_MASK, WD2_ADC_OM_OUT_INVERT_0_E_OFS, value);
   };


   // Control Register 81: ADC_0_CH_F_CFG (offset 0x1144) 
   unsigned int GetAdcTmUsrInMode0F() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_0_F_REG, WD2_ADC_TM_USR_IN_MODE_0_F_MASK, WD2_ADC_TM_USR_IN_MODE_0_F_OFS);
   };

   void SetAdcTmUsrInMode0F(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_0_F_REG, WD2_ADC_TM_USR_IN_MODE_0_F_MASK, WD2_ADC_TM_USR_IN_MODE_0_F_OFS, value);
   };

   unsigned int GetAdcTmOut0F() {
      return BitExtractControl(WD2_ADC_TM_OUT_0_F_REG, WD2_ADC_TM_OUT_0_F_MASK, WD2_ADC_TM_OUT_0_F_OFS);
   };

   void SetAdcTmOut0F(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_0_F_REG, WD2_ADC_TM_OUT_0_F_MASK, WD2_ADC_TM_OUT_0_F_OFS, value);
   };

   unsigned int GetAdcOffsAdj0F() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_0_F_REG, WD2_ADC_OFFS_ADJ_0_F_MASK, WD2_ADC_OFFS_ADJ_0_F_OFS);
   };

   void SetAdcOffsAdj0F(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_0_F_REG, WD2_ADC_OFFS_ADJ_0_F_MASK, WD2_ADC_OFFS_ADJ_0_F_OFS, value);
   };

   unsigned int GetAdcOmOutInvert0F() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_0_F_REG, WD2_ADC_OM_OUT_INVERT_0_F_MASK, WD2_ADC_OM_OUT_INVERT_0_F_OFS);
   };

   void SetAdcOmOutInvert0F(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_0_F_REG, WD2_ADC_OM_OUT_INVERT_0_F_MASK, WD2_ADC_OM_OUT_INVERT_0_F_OFS, value);
   };


   // Control Register 82: ADC_0_CH_G_CFG (offset 0x1148) 
   unsigned int GetAdcTmUsrInMode0G() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_0_G_REG, WD2_ADC_TM_USR_IN_MODE_0_G_MASK, WD2_ADC_TM_USR_IN_MODE_0_G_OFS);
   };

   void SetAdcTmUsrInMode0G(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_0_G_REG, WD2_ADC_TM_USR_IN_MODE_0_G_MASK, WD2_ADC_TM_USR_IN_MODE_0_G_OFS, value);
   };

   unsigned int GetAdcTmOut0G() {
      return BitExtractControl(WD2_ADC_TM_OUT_0_G_REG, WD2_ADC_TM_OUT_0_G_MASK, WD2_ADC_TM_OUT_0_G_OFS);
   };

   void SetAdcTmOut0G(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_0_G_REG, WD2_ADC_TM_OUT_0_G_MASK, WD2_ADC_TM_OUT_0_G_OFS, value);
   };

   unsigned int GetAdcOffsAdj0G() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_0_G_REG, WD2_ADC_OFFS_ADJ_0_G_MASK, WD2_ADC_OFFS_ADJ_0_G_OFS);
   };

   void SetAdcOffsAdj0G(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_0_G_REG, WD2_ADC_OFFS_ADJ_0_G_MASK, WD2_ADC_OFFS_ADJ_0_G_OFS, value);
   };

   unsigned int GetAdcOmOutInvert0G() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_0_G_REG, WD2_ADC_OM_OUT_INVERT_0_G_MASK, WD2_ADC_OM_OUT_INVERT_0_G_OFS);
   };

   void SetAdcOmOutInvert0G(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_0_G_REG, WD2_ADC_OM_OUT_INVERT_0_G_MASK, WD2_ADC_OM_OUT_INVERT_0_G_OFS, value);
   };


   // Control Register 83: ADC_0_CH_H_CFG (offset 0x114C) 
   unsigned int GetAdcTmUsrInMode0H() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_0_H_REG, WD2_ADC_TM_USR_IN_MODE_0_H_MASK, WD2_ADC_TM_USR_IN_MODE_0_H_OFS);
   };

   void SetAdcTmUsrInMode0H(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_0_H_REG, WD2_ADC_TM_USR_IN_MODE_0_H_MASK, WD2_ADC_TM_USR_IN_MODE_0_H_OFS, value);
   };

   unsigned int GetAdcTmOut0H() {
      return BitExtractControl(WD2_ADC_TM_OUT_0_H_REG, WD2_ADC_TM_OUT_0_H_MASK, WD2_ADC_TM_OUT_0_H_OFS);
   };

   void SetAdcTmOut0H(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_0_H_REG, WD2_ADC_TM_OUT_0_H_MASK, WD2_ADC_TM_OUT_0_H_OFS, value);
   };

   unsigned int GetAdcOffsAdj0H() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_0_H_REG, WD2_ADC_OFFS_ADJ_0_H_MASK, WD2_ADC_OFFS_ADJ_0_H_OFS);
   };

   void SetAdcOffsAdj0H(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_0_H_REG, WD2_ADC_OFFS_ADJ_0_H_MASK, WD2_ADC_OFFS_ADJ_0_H_OFS, value);
   };

   unsigned int GetAdcOmOutInvert0H() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_0_H_REG, WD2_ADC_OM_OUT_INVERT_0_H_MASK, WD2_ADC_OM_OUT_INVERT_0_H_OFS);
   };

   void SetAdcOmOutInvert0H(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_0_H_REG, WD2_ADC_OM_OUT_INVERT_0_H_MASK, WD2_ADC_OM_OUT_INVERT_0_H_OFS, value);
   };


   // Control Register 84: ADC_0_CH_DCO_CFG (offset 0x1150) 
   unsigned int GetAdcTmUsrInMode0Dco() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_0_DCO_REG, WD2_ADC_TM_USR_IN_MODE_0_DCO_MASK, WD2_ADC_TM_USR_IN_MODE_0_DCO_OFS);
   };

   void SetAdcTmUsrInMode0Dco(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_0_DCO_REG, WD2_ADC_TM_USR_IN_MODE_0_DCO_MASK, WD2_ADC_TM_USR_IN_MODE_0_DCO_OFS, value);
   };

   unsigned int GetAdcTmOut0Dco() {
      return BitExtractControl(WD2_ADC_TM_OUT_0_DCO_REG, WD2_ADC_TM_OUT_0_DCO_MASK, WD2_ADC_TM_OUT_0_DCO_OFS);
   };

   void SetAdcTmOut0Dco(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_0_DCO_REG, WD2_ADC_TM_OUT_0_DCO_MASK, WD2_ADC_TM_OUT_0_DCO_OFS, value);
   };

   unsigned int GetAdcOffsAdj0Dco() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_0_DCO_REG, WD2_ADC_OFFS_ADJ_0_DCO_MASK, WD2_ADC_OFFS_ADJ_0_DCO_OFS);
   };

   void SetAdcOffsAdj0Dco(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_0_DCO_REG, WD2_ADC_OFFS_ADJ_0_DCO_MASK, WD2_ADC_OFFS_ADJ_0_DCO_OFS, value);
   };

   unsigned int GetAdcOmOutInvert0Dco() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_0_DCO_REG, WD2_ADC_OM_OUT_INVERT_0_DCO_MASK, WD2_ADC_OM_OUT_INVERT_0_DCO_OFS);
   };

   void SetAdcOmOutInvert0Dco(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_0_DCO_REG, WD2_ADC_OM_OUT_INVERT_0_DCO_MASK, WD2_ADC_OM_OUT_INVERT_0_DCO_OFS, value);
   };


   // Control Register 85: ADC_0_CH_FCO_CFG (offset 0x1154) 
   unsigned int GetAdcTmUsrInMode0Fco() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_0_FCO_REG, WD2_ADC_TM_USR_IN_MODE_0_FCO_MASK, WD2_ADC_TM_USR_IN_MODE_0_FCO_OFS);
   };

   void SetAdcTmUsrInMode0Fco(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_0_FCO_REG, WD2_ADC_TM_USR_IN_MODE_0_FCO_MASK, WD2_ADC_TM_USR_IN_MODE_0_FCO_OFS, value);
   };

   unsigned int GetAdcTmOut0Fco() {
      return BitExtractControl(WD2_ADC_TM_OUT_0_FCO_REG, WD2_ADC_TM_OUT_0_FCO_MASK, WD2_ADC_TM_OUT_0_FCO_OFS);
   };

   void SetAdcTmOut0Fco(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_0_FCO_REG, WD2_ADC_TM_OUT_0_FCO_MASK, WD2_ADC_TM_OUT_0_FCO_OFS, value);
   };

   unsigned int GetAdcOffsAdj0Fco() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_0_FCO_REG, WD2_ADC_OFFS_ADJ_0_FCO_MASK, WD2_ADC_OFFS_ADJ_0_FCO_OFS);
   };

   void SetAdcOffsAdj0Fco(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_0_FCO_REG, WD2_ADC_OFFS_ADJ_0_FCO_MASK, WD2_ADC_OFFS_ADJ_0_FCO_OFS, value);
   };

   unsigned int GetAdcOmOutInvert0Fco() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_0_FCO_REG, WD2_ADC_OM_OUT_INVERT_0_FCO_MASK, WD2_ADC_OM_OUT_INVERT_0_FCO_OFS);
   };

   void SetAdcOmOutInvert0Fco(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_0_FCO_REG, WD2_ADC_OM_OUT_INVERT_0_FCO_MASK, WD2_ADC_OM_OUT_INVERT_0_FCO_OFS, value);
   };


   // Control Register 86: ADC_1_CH_A_CFG (offset 0x1158) 
   unsigned int GetAdcTmUsrInMode1A() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_1_A_REG, WD2_ADC_TM_USR_IN_MODE_1_A_MASK, WD2_ADC_TM_USR_IN_MODE_1_A_OFS);
   };

   void SetAdcTmUsrInMode1A(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_1_A_REG, WD2_ADC_TM_USR_IN_MODE_1_A_MASK, WD2_ADC_TM_USR_IN_MODE_1_A_OFS, value);
   };

   unsigned int GetAdcTmOut1A() {
      return BitExtractControl(WD2_ADC_TM_OUT_1_A_REG, WD2_ADC_TM_OUT_1_A_MASK, WD2_ADC_TM_OUT_1_A_OFS);
   };

   void SetAdcTmOut1A(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_1_A_REG, WD2_ADC_TM_OUT_1_A_MASK, WD2_ADC_TM_OUT_1_A_OFS, value);
   };

   unsigned int GetAdcOffsAdj1A() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_1_A_REG, WD2_ADC_OFFS_ADJ_1_A_MASK, WD2_ADC_OFFS_ADJ_1_A_OFS);
   };

   void SetAdcOffsAdj1A(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_1_A_REG, WD2_ADC_OFFS_ADJ_1_A_MASK, WD2_ADC_OFFS_ADJ_1_A_OFS, value);
   };

   unsigned int GetAdcOmOutInvert1A() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_1_A_REG, WD2_ADC_OM_OUT_INVERT_1_A_MASK, WD2_ADC_OM_OUT_INVERT_1_A_OFS);
   };

   void SetAdcOmOutInvert1A(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_1_A_REG, WD2_ADC_OM_OUT_INVERT_1_A_MASK, WD2_ADC_OM_OUT_INVERT_1_A_OFS, value);
   };


   // Control Register 87: ADC_1_CH_B_CFG (offset 0x115C) 
   unsigned int GetAdcTmUsrInMode1B() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_1_B_REG, WD2_ADC_TM_USR_IN_MODE_1_B_MASK, WD2_ADC_TM_USR_IN_MODE_1_B_OFS);
   };

   void SetAdcTmUsrInMode1B(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_1_B_REG, WD2_ADC_TM_USR_IN_MODE_1_B_MASK, WD2_ADC_TM_USR_IN_MODE_1_B_OFS, value);
   };

   unsigned int GetAdcTmOut1B() {
      return BitExtractControl(WD2_ADC_TM_OUT_1_B_REG, WD2_ADC_TM_OUT_1_B_MASK, WD2_ADC_TM_OUT_1_B_OFS);
   };

   void SetAdcTmOut1B(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_1_B_REG, WD2_ADC_TM_OUT_1_B_MASK, WD2_ADC_TM_OUT_1_B_OFS, value);
   };

   unsigned int GetAdcOffsAdj1B() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_1_B_REG, WD2_ADC_OFFS_ADJ_1_B_MASK, WD2_ADC_OFFS_ADJ_1_B_OFS);
   };

   void SetAdcOffsAdj1B(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_1_B_REG, WD2_ADC_OFFS_ADJ_1_B_MASK, WD2_ADC_OFFS_ADJ_1_B_OFS, value);
   };

   unsigned int GetAdcOmOutInvert1B() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_1_B_REG, WD2_ADC_OM_OUT_INVERT_1_B_MASK, WD2_ADC_OM_OUT_INVERT_1_B_OFS);
   };

   void SetAdcOmOutInvert1B(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_1_B_REG, WD2_ADC_OM_OUT_INVERT_1_B_MASK, WD2_ADC_OM_OUT_INVERT_1_B_OFS, value);
   };


   // Control Register 88: ADC_1_CH_C_CFG (offset 0x1160) 
   unsigned int GetAdcTmUsrInMode1C() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_1_C_REG, WD2_ADC_TM_USR_IN_MODE_1_C_MASK, WD2_ADC_TM_USR_IN_MODE_1_C_OFS);
   };

   void SetAdcTmUsrInMode1C(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_1_C_REG, WD2_ADC_TM_USR_IN_MODE_1_C_MASK, WD2_ADC_TM_USR_IN_MODE_1_C_OFS, value);
   };

   unsigned int GetAdcTmOut1C() {
      return BitExtractControl(WD2_ADC_TM_OUT_1_C_REG, WD2_ADC_TM_OUT_1_C_MASK, WD2_ADC_TM_OUT_1_C_OFS);
   };

   void SetAdcTmOut1C(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_1_C_REG, WD2_ADC_TM_OUT_1_C_MASK, WD2_ADC_TM_OUT_1_C_OFS, value);
   };

   unsigned int GetAdcOffsAdj1C() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_1_C_REG, WD2_ADC_OFFS_ADJ_1_C_MASK, WD2_ADC_OFFS_ADJ_1_C_OFS);
   };

   void SetAdcOffsAdj1C(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_1_C_REG, WD2_ADC_OFFS_ADJ_1_C_MASK, WD2_ADC_OFFS_ADJ_1_C_OFS, value);
   };

   unsigned int GetAdcOmOutInvert1C() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_1_C_REG, WD2_ADC_OM_OUT_INVERT_1_C_MASK, WD2_ADC_OM_OUT_INVERT_1_C_OFS);
   };

   void SetAdcOmOutInvert1C(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_1_C_REG, WD2_ADC_OM_OUT_INVERT_1_C_MASK, WD2_ADC_OM_OUT_INVERT_1_C_OFS, value);
   };


   // Control Register 89: ADC_1_CH_D_CFG (offset 0x1164) 
   unsigned int GetAdcTmUsrInMode1D() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_1_D_REG, WD2_ADC_TM_USR_IN_MODE_1_D_MASK, WD2_ADC_TM_USR_IN_MODE_1_D_OFS);
   };

   void SetAdcTmUsrInMode1D(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_1_D_REG, WD2_ADC_TM_USR_IN_MODE_1_D_MASK, WD2_ADC_TM_USR_IN_MODE_1_D_OFS, value);
   };

   unsigned int GetAdcTmOut1D() {
      return BitExtractControl(WD2_ADC_TM_OUT_1_D_REG, WD2_ADC_TM_OUT_1_D_MASK, WD2_ADC_TM_OUT_1_D_OFS);
   };

   void SetAdcTmOut1D(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_1_D_REG, WD2_ADC_TM_OUT_1_D_MASK, WD2_ADC_TM_OUT_1_D_OFS, value);
   };

   unsigned int GetAdcOffsAdj1D() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_1_D_REG, WD2_ADC_OFFS_ADJ_1_D_MASK, WD2_ADC_OFFS_ADJ_1_D_OFS);
   };

   void SetAdcOffsAdj1D(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_1_D_REG, WD2_ADC_OFFS_ADJ_1_D_MASK, WD2_ADC_OFFS_ADJ_1_D_OFS, value);
   };

   unsigned int GetAdcOmOutInvert1D() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_1_D_REG, WD2_ADC_OM_OUT_INVERT_1_D_MASK, WD2_ADC_OM_OUT_INVERT_1_D_OFS);
   };

   void SetAdcOmOutInvert1D(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_1_D_REG, WD2_ADC_OM_OUT_INVERT_1_D_MASK, WD2_ADC_OM_OUT_INVERT_1_D_OFS, value);
   };


   // Control Register 90: ADC_1_CH_E_CFG (offset 0x1168) 
   unsigned int GetAdcTmUsrInMode1E() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_1_E_REG, WD2_ADC_TM_USR_IN_MODE_1_E_MASK, WD2_ADC_TM_USR_IN_MODE_1_E_OFS);
   };

   void SetAdcTmUsrInMode1E(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_1_E_REG, WD2_ADC_TM_USR_IN_MODE_1_E_MASK, WD2_ADC_TM_USR_IN_MODE_1_E_OFS, value);
   };

   unsigned int GetAdcTmOut1E() {
      return BitExtractControl(WD2_ADC_TM_OUT_1_E_REG, WD2_ADC_TM_OUT_1_E_MASK, WD2_ADC_TM_OUT_1_E_OFS);
   };

   void SetAdcTmOut1E(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_1_E_REG, WD2_ADC_TM_OUT_1_E_MASK, WD2_ADC_TM_OUT_1_E_OFS, value);
   };

   unsigned int GetAdcOffsAdj1E() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_1_E_REG, WD2_ADC_OFFS_ADJ_1_E_MASK, WD2_ADC_OFFS_ADJ_1_E_OFS);
   };

   void SetAdcOffsAdj1E(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_1_E_REG, WD2_ADC_OFFS_ADJ_1_E_MASK, WD2_ADC_OFFS_ADJ_1_E_OFS, value);
   };

   unsigned int GetAdcOmOutInvert1E() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_1_E_REG, WD2_ADC_OM_OUT_INVERT_1_E_MASK, WD2_ADC_OM_OUT_INVERT_1_E_OFS);
   };

   void SetAdcOmOutInvert1E(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_1_E_REG, WD2_ADC_OM_OUT_INVERT_1_E_MASK, WD2_ADC_OM_OUT_INVERT_1_E_OFS, value);
   };


   // Control Register 91: ADC_1_CH_F_CFG (offset 0x116C) 
   unsigned int GetAdcTmUsrInMode1F() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_1_F_REG, WD2_ADC_TM_USR_IN_MODE_1_F_MASK, WD2_ADC_TM_USR_IN_MODE_1_F_OFS);
   };

   void SetAdcTmUsrInMode1F(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_1_F_REG, WD2_ADC_TM_USR_IN_MODE_1_F_MASK, WD2_ADC_TM_USR_IN_MODE_1_F_OFS, value);
   };

   unsigned int GetAdcTmOut1F() {
      return BitExtractControl(WD2_ADC_TM_OUT_1_F_REG, WD2_ADC_TM_OUT_1_F_MASK, WD2_ADC_TM_OUT_1_F_OFS);
   };

   void SetAdcTmOut1F(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_1_F_REG, WD2_ADC_TM_OUT_1_F_MASK, WD2_ADC_TM_OUT_1_F_OFS, value);
   };

   unsigned int GetAdcOffsAdj1F() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_1_F_REG, WD2_ADC_OFFS_ADJ_1_F_MASK, WD2_ADC_OFFS_ADJ_1_F_OFS);
   };

   void SetAdcOffsAdj1F(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_1_F_REG, WD2_ADC_OFFS_ADJ_1_F_MASK, WD2_ADC_OFFS_ADJ_1_F_OFS, value);
   };

   unsigned int GetAdcOmOutInvert1F() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_1_F_REG, WD2_ADC_OM_OUT_INVERT_1_F_MASK, WD2_ADC_OM_OUT_INVERT_1_F_OFS);
   };

   void SetAdcOmOutInvert1F(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_1_F_REG, WD2_ADC_OM_OUT_INVERT_1_F_MASK, WD2_ADC_OM_OUT_INVERT_1_F_OFS, value);
   };


   // Control Register 92: ADC_1_CH_G_CFG (offset 0x1170) 
   unsigned int GetAdcTmUsrInMode1G() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_1_G_REG, WD2_ADC_TM_USR_IN_MODE_1_G_MASK, WD2_ADC_TM_USR_IN_MODE_1_G_OFS);
   };

   void SetAdcTmUsrInMode1G(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_1_G_REG, WD2_ADC_TM_USR_IN_MODE_1_G_MASK, WD2_ADC_TM_USR_IN_MODE_1_G_OFS, value);
   };

   unsigned int GetAdcTmOut1G() {
      return BitExtractControl(WD2_ADC_TM_OUT_1_G_REG, WD2_ADC_TM_OUT_1_G_MASK, WD2_ADC_TM_OUT_1_G_OFS);
   };

   void SetAdcTmOut1G(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_1_G_REG, WD2_ADC_TM_OUT_1_G_MASK, WD2_ADC_TM_OUT_1_G_OFS, value);
   };

   unsigned int GetAdcOffsAdj1G() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_1_G_REG, WD2_ADC_OFFS_ADJ_1_G_MASK, WD2_ADC_OFFS_ADJ_1_G_OFS);
   };

   void SetAdcOffsAdj1G(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_1_G_REG, WD2_ADC_OFFS_ADJ_1_G_MASK, WD2_ADC_OFFS_ADJ_1_G_OFS, value);
   };

   unsigned int GetAdcOmOutInvert1G() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_1_G_REG, WD2_ADC_OM_OUT_INVERT_1_G_MASK, WD2_ADC_OM_OUT_INVERT_1_G_OFS);
   };

   void SetAdcOmOutInvert1G(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_1_G_REG, WD2_ADC_OM_OUT_INVERT_1_G_MASK, WD2_ADC_OM_OUT_INVERT_1_G_OFS, value);
   };


   // Control Register 93: ADC_1_CH_H_CFG (offset 0x1174) 
   unsigned int GetAdcTmUsrInMode1H() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_1_H_REG, WD2_ADC_TM_USR_IN_MODE_1_H_MASK, WD2_ADC_TM_USR_IN_MODE_1_H_OFS);
   };

   void SetAdcTmUsrInMode1H(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_1_H_REG, WD2_ADC_TM_USR_IN_MODE_1_H_MASK, WD2_ADC_TM_USR_IN_MODE_1_H_OFS, value);
   };

   unsigned int GetAdcTmOut1H() {
      return BitExtractControl(WD2_ADC_TM_OUT_1_H_REG, WD2_ADC_TM_OUT_1_H_MASK, WD2_ADC_TM_OUT_1_H_OFS);
   };

   void SetAdcTmOut1H(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_1_H_REG, WD2_ADC_TM_OUT_1_H_MASK, WD2_ADC_TM_OUT_1_H_OFS, value);
   };

   unsigned int GetAdcOffsAdj1H() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_1_H_REG, WD2_ADC_OFFS_ADJ_1_H_MASK, WD2_ADC_OFFS_ADJ_1_H_OFS);
   };

   void SetAdcOffsAdj1H(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_1_H_REG, WD2_ADC_OFFS_ADJ_1_H_MASK, WD2_ADC_OFFS_ADJ_1_H_OFS, value);
   };

   unsigned int GetAdcOmOutInvert1H() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_1_H_REG, WD2_ADC_OM_OUT_INVERT_1_H_MASK, WD2_ADC_OM_OUT_INVERT_1_H_OFS);
   };

   void SetAdcOmOutInvert1H(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_1_H_REG, WD2_ADC_OM_OUT_INVERT_1_H_MASK, WD2_ADC_OM_OUT_INVERT_1_H_OFS, value);
   };


   // Control Register 94: ADC_1_CH_DCO_CFG (offset 0x1178) 
   unsigned int GetAdcTmUsrInMode1Dco() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_1_DCO_REG, WD2_ADC_TM_USR_IN_MODE_1_DCO_MASK, WD2_ADC_TM_USR_IN_MODE_1_DCO_OFS);
   };

   void SetAdcTmUsrInMode1Dco(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_1_DCO_REG, WD2_ADC_TM_USR_IN_MODE_1_DCO_MASK, WD2_ADC_TM_USR_IN_MODE_1_DCO_OFS, value);
   };

   unsigned int GetAdcTmOut1Dco() {
      return BitExtractControl(WD2_ADC_TM_OUT_1_DCO_REG, WD2_ADC_TM_OUT_1_DCO_MASK, WD2_ADC_TM_OUT_1_DCO_OFS);
   };

   void SetAdcTmOut1Dco(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_1_DCO_REG, WD2_ADC_TM_OUT_1_DCO_MASK, WD2_ADC_TM_OUT_1_DCO_OFS, value);
   };

   unsigned int GetAdcOffsAdj1Dco() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_1_DCO_REG, WD2_ADC_OFFS_ADJ_1_DCO_MASK, WD2_ADC_OFFS_ADJ_1_DCO_OFS);
   };

   void SetAdcOffsAdj1Dco(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_1_DCO_REG, WD2_ADC_OFFS_ADJ_1_DCO_MASK, WD2_ADC_OFFS_ADJ_1_DCO_OFS, value);
   };

   unsigned int GetAdcOmOutInvert1Dco() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_1_DCO_REG, WD2_ADC_OM_OUT_INVERT_1_DCO_MASK, WD2_ADC_OM_OUT_INVERT_1_DCO_OFS);
   };

   void SetAdcOmOutInvert1Dco(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_1_DCO_REG, WD2_ADC_OM_OUT_INVERT_1_DCO_MASK, WD2_ADC_OM_OUT_INVERT_1_DCO_OFS, value);
   };


   // Control Register 95: ADC_1_CH_FCO_CFG (offset 0x117C) 
   unsigned int GetAdcTmUsrInMode1Fco() {
      return BitExtractControl(WD2_ADC_TM_USR_IN_MODE_1_FCO_REG, WD2_ADC_TM_USR_IN_MODE_1_FCO_MASK, WD2_ADC_TM_USR_IN_MODE_1_FCO_OFS);
   };

   void SetAdcTmUsrInMode1Fco(unsigned int value) {
      SetRegMask(WD2_ADC_TM_USR_IN_MODE_1_FCO_REG, WD2_ADC_TM_USR_IN_MODE_1_FCO_MASK, WD2_ADC_TM_USR_IN_MODE_1_FCO_OFS, value);
   };

   unsigned int GetAdcTmOut1Fco() {
      return BitExtractControl(WD2_ADC_TM_OUT_1_FCO_REG, WD2_ADC_TM_OUT_1_FCO_MASK, WD2_ADC_TM_OUT_1_FCO_OFS);
   };

   void SetAdcTmOut1Fco(unsigned int value) {
      SetRegMask(WD2_ADC_TM_OUT_1_FCO_REG, WD2_ADC_TM_OUT_1_FCO_MASK, WD2_ADC_TM_OUT_1_FCO_OFS, value);
   };

   unsigned int GetAdcOffsAdj1Fco() {
      return BitExtractControl(WD2_ADC_OFFS_ADJ_1_FCO_REG, WD2_ADC_OFFS_ADJ_1_FCO_MASK, WD2_ADC_OFFS_ADJ_1_FCO_OFS);
   };

   void SetAdcOffsAdj1Fco(unsigned int value) {
      SetRegMask(WD2_ADC_OFFS_ADJ_1_FCO_REG, WD2_ADC_OFFS_ADJ_1_FCO_MASK, WD2_ADC_OFFS_ADJ_1_FCO_OFS, value);
   };

   unsigned int GetAdcOmOutInvert1Fco() {
      return BitExtractControl(WD2_ADC_OM_OUT_INVERT_1_FCO_REG, WD2_ADC_OM_OUT_INVERT_1_FCO_MASK, WD2_ADC_OM_OUT_INVERT_1_FCO_OFS);
   };

   void SetAdcOmOutInvert1Fco(unsigned int value) {
      SetRegMask(WD2_ADC_OM_OUT_INVERT_1_FCO_REG, WD2_ADC_OM_OUT_INVERT_1_FCO_MASK, WD2_ADC_OM_OUT_INVERT_1_FCO_OFS, value);
   };


   // Control Register 96: TRG_CFG (offset 0x1180) 
   unsigned int GetTriggerShaperEnable() {
      return BitExtractControl(WD2_TRIGGER_SHAPER_ENABLE_REG, WD2_TRIGGER_SHAPER_ENABLE_MASK, WD2_TRIGGER_SHAPER_ENABLE_OFS);
   };

   void SetTriggerShaperEnable(unsigned int value) {
      SetRegMask(WD2_TRIGGER_SHAPER_ENABLE_REG, WD2_TRIGGER_SHAPER_ENABLE_MASK, WD2_TRIGGER_SHAPER_ENABLE_OFS, value);
   };

   unsigned int GetTriggerOutPulseLength() {
      return BitExtractControl(WD2_TRIGGER_OUT_PULSE_LENGTH_REG, WD2_TRIGGER_OUT_PULSE_LENGTH_MASK, WD2_TRIGGER_OUT_PULSE_LENGTH_OFS);
   };

   void SetTriggerOutPulseLength(unsigned int value) {
      SetRegMask(WD2_TRIGGER_OUT_PULSE_LENGTH_REG, WD2_TRIGGER_OUT_PULSE_LENGTH_MASK, WD2_TRIGGER_OUT_PULSE_LENGTH_OFS, value);
   };

   unsigned int GetTriggerEnable() {
      return BitExtractControl(WD2_TRIGGER_ENABLE_REG, WD2_TRIGGER_ENABLE_MASK, WD2_TRIGGER_ENABLE_OFS);
   };

   void SetTriggerEnable(unsigned int value) {
      SetRegMask(WD2_TRIGGER_ENABLE_REG, WD2_TRIGGER_ENABLE_MASK, WD2_TRIGGER_ENABLE_OFS, value);
   };

   unsigned int GetTriggerFallingEdge() {
      return BitExtractControl(WD2_TRIGGER_FALLING_EDGE_REG, WD2_TRIGGER_FALLING_EDGE_MASK, WD2_TRIGGER_FALLING_EDGE_OFS);
   };

   void SetTriggerFallingEdge(unsigned int value) {
      SetRegMask(WD2_TRIGGER_FALLING_EDGE_REG, WD2_TRIGGER_FALLING_EDGE_MASK, WD2_TRIGGER_FALLING_EDGE_OFS, value);
   };

   unsigned int GetTriggerCfgExtOr() {
      return BitExtractControl(WD2_TRIGGER_CFG_EXT_OR_REG, WD2_TRIGGER_CFG_EXT_OR_MASK, WD2_TRIGGER_CFG_EXT_OR_OFS);
   };

   void SetTriggerCfgExtOr(unsigned int value) {
      SetRegMask(WD2_TRIGGER_CFG_EXT_OR_REG, WD2_TRIGGER_CFG_EXT_OR_MASK, WD2_TRIGGER_CFG_EXT_OR_OFS, value);
   };

   unsigned int GetTriggerCfgExtAnd() {
      return BitExtractControl(WD2_TRIGGER_CFG_EXT_AND_REG, WD2_TRIGGER_CFG_EXT_AND_MASK, WD2_TRIGGER_CFG_EXT_AND_OFS);
   };

   void SetTriggerCfgExtAnd(unsigned int value) {
      SetRegMask(WD2_TRIGGER_CFG_EXT_AND_REG, WD2_TRIGGER_CFG_EXT_AND_MASK, WD2_TRIGGER_CFG_EXT_AND_OFS, value);
   };

   unsigned int GetTriggerDelayEnable() {
      return BitExtractControl(WD2_TRIGGER_DELAY_ENABLE_REG, WD2_TRIGGER_DELAY_ENABLE_MASK, WD2_TRIGGER_DELAY_ENABLE_OFS);
   };

   void SetTriggerDelayEnable(unsigned int value) {
      SetRegMask(WD2_TRIGGER_DELAY_ENABLE_REG, WD2_TRIGGER_DELAY_ENABLE_MASK, WD2_TRIGGER_DELAY_ENABLE_OFS, value);
   };

   unsigned int GetTriggerDelay() {
      return BitExtractControl(WD2_TRIGGER_DELAY_REG, WD2_TRIGGER_DELAY_MASK, WD2_TRIGGER_DELAY_OFS);
   };

   void SetTriggerDelay(unsigned int value) {
      SetRegMask(WD2_TRIGGER_DELAY_REG, WD2_TRIGGER_DELAY_MASK, WD2_TRIGGER_DELAY_OFS, value);
   };


   // Control Register 97: TRG_COMP_MASK (offset 0x1184) 
   unsigned int GetTriggerCompMask() {
      return BitExtractControl(WD2_TRIGGER_COMP_MASK_REG, WD2_TRIGGER_COMP_MASK_MASK, WD2_TRIGGER_COMP_MASK_OFS);
   };

   void SetTriggerCompMask(unsigned int value) {
      SetRegMask(WD2_TRIGGER_COMP_MASK_REG, WD2_TRIGGER_COMP_MASK_MASK, WD2_TRIGGER_COMP_MASK_OFS, value);
   };


   // Control Register 98: TRG_CH_CMB (offset 0x1188) 
   unsigned int GetTriggerCfgOr() {
      return BitExtractControl(WD2_TRIGGER_CFG_OR_REG, WD2_TRIGGER_CFG_OR_MASK, WD2_TRIGGER_CFG_OR_OFS);
   };

   void SetTriggerCfgOr(unsigned int value) {
      SetRegMask(WD2_TRIGGER_CFG_OR_REG, WD2_TRIGGER_CFG_OR_MASK, WD2_TRIGGER_CFG_OR_OFS, value);
   };

   unsigned int GetTriggerCfgAnd() {
      return BitExtractControl(WD2_TRIGGER_CFG_AND_REG, WD2_TRIGGER_CFG_AND_MASK, WD2_TRIGGER_CFG_AND_OFS);
   };

   void SetTriggerCfgAnd(unsigned int value) {
      SetRegMask(WD2_TRIGGER_CFG_AND_REG, WD2_TRIGGER_CFG_AND_MASK, WD2_TRIGGER_CFG_AND_OFS, value);
   };


   // Control Register 99: TRG_AUTO_PERIOD (offset 0x118C) 
   unsigned int GetAutoTriggerPeriod() {
      return BitExtractControl(WD2_AUTO_TRIGGER_PERIOD_REG, WD2_AUTO_TRIGGER_PERIOD_MASK, WD2_AUTO_TRIGGER_PERIOD_OFS);
   };

   void SetAutoTriggerPeriod(unsigned int value) {
      SetRegMask(WD2_AUTO_TRIGGER_PERIOD_REG, WD2_AUTO_TRIGGER_PERIOD_MASK, WD2_AUTO_TRIGGER_PERIOD_OFS, value);
   };


   // Control Register 100: TRG_SCH_SEL (offset 0x1190) 
   unsigned int GetPatternTriggerSelect() {
      return BitExtractControl(WD2_PATTERN_TRIGGER_SELECT_REG, WD2_PATTERN_TRIGGER_SELECT_MASK, WD2_PATTERN_TRIGGER_SELECT_OFS);
   };

   void SetPatternTriggerSelect(unsigned int value) {
      SetRegMask(WD2_PATTERN_TRIGGER_SELECT_REG, WD2_PATTERN_TRIGGER_SELECT_MASK, WD2_PATTERN_TRIGGER_SELECT_OFS, value);
   };


   // Control Register 101: TRG_PTRN_EN_LOCAL (offset 0x1194) 
   unsigned int GetTrgPtrnEnLocal() {
      return BitExtractControl(WD2_TRG_PTRN_EN_LOCAL_REG, WD2_TRG_PTRN_EN_LOCAL_MASK, WD2_TRG_PTRN_EN_LOCAL_OFS);
   };

   void SetTrgPtrnEnLocal(unsigned int value) {
      SetRegMask(WD2_TRG_PTRN_EN_LOCAL_REG, WD2_TRG_PTRN_EN_LOCAL_MASK, WD2_TRG_PTRN_EN_LOCAL_OFS, value);
   };


   // Control Register 102: TRG_PTRN0 (offset 0x1198) 
   unsigned int GetTrgPtrn0() {
      return BitExtractControl(WD2_TRG_PTRN0_REG, WD2_TRG_PTRN0_MASK, WD2_TRG_PTRN0_OFS);
   };

   void SetTrgPtrn0(unsigned int value) {
      SetRegMask(WD2_TRG_PTRN0_REG, WD2_TRG_PTRN0_MASK, WD2_TRG_PTRN0_OFS, value);
   };


   // Control Register 103: TRG_PTRN1 (offset 0x119C) 
   unsigned int GetTrgPtrn1() {
      return BitExtractControl(WD2_TRG_PTRN1_REG, WD2_TRG_PTRN1_MASK, WD2_TRG_PTRN1_OFS);
   };

   void SetTrgPtrn1(unsigned int value) {
      SetRegMask(WD2_TRG_PTRN1_REG, WD2_TRG_PTRN1_MASK, WD2_TRG_PTRN1_OFS, value);
   };


   // Control Register 104: TRG_PTRN2 (offset 0x11A0) 
   unsigned int GetTrgPtrn2() {
      return BitExtractControl(WD2_TRG_PTRN2_REG, WD2_TRG_PTRN2_MASK, WD2_TRG_PTRN2_OFS);
   };

   void SetTrgPtrn2(unsigned int value) {
      SetRegMask(WD2_TRG_PTRN2_REG, WD2_TRG_PTRN2_MASK, WD2_TRG_PTRN2_OFS, value);
   };


   // Control Register 105: TRG_PTRN3 (offset 0x11A4) 
   unsigned int GetTrgPtrn3() {
      return BitExtractControl(WD2_TRG_PTRN3_REG, WD2_TRG_PTRN3_MASK, WD2_TRG_PTRN3_OFS);
   };

   void SetTrgPtrn3(unsigned int value) {
      SetRegMask(WD2_TRG_PTRN3_REG, WD2_TRG_PTRN3_MASK, WD2_TRG_PTRN3_OFS, value);
   };


   // Control Register 106: TRG_PTRN4 (offset 0x11A8) 
   unsigned int GetTrgPtrn4() {
      return BitExtractControl(WD2_TRG_PTRN4_REG, WD2_TRG_PTRN4_MASK, WD2_TRG_PTRN4_OFS);
   };

   void SetTrgPtrn4(unsigned int value) {
      SetRegMask(WD2_TRG_PTRN4_REG, WD2_TRG_PTRN4_MASK, WD2_TRG_PTRN4_OFS, value);
   };


   // Control Register 107: TRG_PTRN5 (offset 0x11AC) 
   unsigned int GetTrgPtrn5() {
      return BitExtractControl(WD2_TRG_PTRN5_REG, WD2_TRG_PTRN5_MASK, WD2_TRG_PTRN5_OFS);
   };

   void SetTrgPtrn5(unsigned int value) {
      SetRegMask(WD2_TRG_PTRN5_REG, WD2_TRG_PTRN5_MASK, WD2_TRG_PTRN5_OFS, value);
   };


   // Control Register 108: TRG_PTRN6 (offset 0x11B0) 
   unsigned int GetTrgPtrn6() {
      return BitExtractControl(WD2_TRG_PTRN6_REG, WD2_TRG_PTRN6_MASK, WD2_TRG_PTRN6_OFS);
   };

   void SetTrgPtrn6(unsigned int value) {
      SetRegMask(WD2_TRG_PTRN6_REG, WD2_TRG_PTRN6_MASK, WD2_TRG_PTRN6_OFS, value);
   };


   // Control Register 109: TRG_PTRN7 (offset 0x11B4) 
   unsigned int GetTrgPtrn7() {
      return BitExtractControl(WD2_TRG_PTRN7_REG, WD2_TRG_PTRN7_MASK, WD2_TRG_PTRN7_OFS);
   };

   void SetTrgPtrn7(unsigned int value) {
      SetRegMask(WD2_TRG_PTRN7_REG, WD2_TRG_PTRN7_MASK, WD2_TRG_PTRN7_OFS, value);
   };


   // Control Register 110: TRG_PTRN8 (offset 0x11B8) 
   unsigned int GetTrgPtrn8() {
      return BitExtractControl(WD2_TRG_PTRN8_REG, WD2_TRG_PTRN8_MASK, WD2_TRG_PTRN8_OFS);
   };

   void SetTrgPtrn8(unsigned int value) {
      SetRegMask(WD2_TRG_PTRN8_REG, WD2_TRG_PTRN8_MASK, WD2_TRG_PTRN8_OFS, value);
   };


   // Control Register 111: TRG_PTRN9 (offset 0x11BC) 
   unsigned int GetTrgPtrn9() {
      return BitExtractControl(WD2_TRG_PTRN9_REG, WD2_TRG_PTRN9_MASK, WD2_TRG_PTRN9_OFS);
   };

   void SetTrgPtrn9(unsigned int value) {
      SetRegMask(WD2_TRG_PTRN9_REG, WD2_TRG_PTRN9_MASK, WD2_TRG_PTRN9_OFS, value);
   };


   // Control Register 112: TRG_PTRN10 (offset 0x11C0) 
   unsigned int GetTrgPtrn10() {
      return BitExtractControl(WD2_TRG_PTRN10_REG, WD2_TRG_PTRN10_MASK, WD2_TRG_PTRN10_OFS);
   };

   void SetTrgPtrn10(unsigned int value) {
      SetRegMask(WD2_TRG_PTRN10_REG, WD2_TRG_PTRN10_MASK, WD2_TRG_PTRN10_OFS, value);
   };


   // Control Register 113: TRG_PTRN11 (offset 0x11C4) 
   unsigned int GetTrgPtrn11() {
      return BitExtractControl(WD2_TRG_PTRN11_REG, WD2_TRG_PTRN11_MASK, WD2_TRG_PTRN11_OFS);
   };

   void SetTrgPtrn11(unsigned int value) {
      SetRegMask(WD2_TRG_PTRN11_REG, WD2_TRG_PTRN11_MASK, WD2_TRG_PTRN11_OFS, value);
   };


   // Control Register 114: TRG_PTRN12 (offset 0x11C8) 
   unsigned int GetTrgPtrn12() {
      return BitExtractControl(WD2_TRG_PTRN12_REG, WD2_TRG_PTRN12_MASK, WD2_TRG_PTRN12_OFS);
   };

   void SetTrgPtrn12(unsigned int value) {
      SetRegMask(WD2_TRG_PTRN12_REG, WD2_TRG_PTRN12_MASK, WD2_TRG_PTRN12_OFS, value);
   };


   // Control Register 115: TRG_PTRN13 (offset 0x11CC) 
   unsigned int GetTrgPtrn13() {
      return BitExtractControl(WD2_TRG_PTRN13_REG, WD2_TRG_PTRN13_MASK, WD2_TRG_PTRN13_OFS);
   };

   void SetTrgPtrn13(unsigned int value) {
      SetRegMask(WD2_TRG_PTRN13_REG, WD2_TRG_PTRN13_MASK, WD2_TRG_PTRN13_OFS, value);
   };


   // Control Register 116: TRG_PTRN14 (offset 0x11D0) 
   unsigned int GetTrgPtrn14() {
      return BitExtractControl(WD2_TRG_PTRN14_REG, WD2_TRG_PTRN14_MASK, WD2_TRG_PTRN14_OFS);
   };

   void SetTrgPtrn14(unsigned int value) {
      SetRegMask(WD2_TRG_PTRN14_REG, WD2_TRG_PTRN14_MASK, WD2_TRG_PTRN14_OFS, value);
   };


   // Control Register 117: TRG_PTRN15 (offset 0x11D4) 
   unsigned int GetTrgPtrn15() {
      return BitExtractControl(WD2_TRG_PTRN15_REG, WD2_TRG_PTRN15_MASK, WD2_TRG_PTRN15_OFS);
   };

   void SetTrgPtrn15(unsigned int value) {
      SetRegMask(WD2_TRG_PTRN15_REG, WD2_TRG_PTRN15_MASK, WD2_TRG_PTRN15_OFS, value);
   };


   // Control Register 118: TRG_PTRN16 (offset 0x11D8) 
   unsigned int GetTrgPtrn16() {
      return BitExtractControl(WD2_TRG_PTRN16_REG, WD2_TRG_PTRN16_MASK, WD2_TRG_PTRN16_OFS);
   };

   void SetTrgPtrn16(unsigned int value) {
      SetRegMask(WD2_TRG_PTRN16_REG, WD2_TRG_PTRN16_MASK, WD2_TRG_PTRN16_OFS, value);
   };


   // Control Register 119: TRG_PTRN17 (offset 0x11DC) 
   unsigned int GetTrgPtrn17() {
      return BitExtractControl(WD2_TRG_PTRN17_REG, WD2_TRG_PTRN17_MASK, WD2_TRG_PTRN17_OFS);
   };

   void SetTrgPtrn17(unsigned int value) {
      SetRegMask(WD2_TRG_PTRN17_REG, WD2_TRG_PTRN17_MASK, WD2_TRG_PTRN17_OFS, value);
   };


   // Control Register 120: ADV_TRG_CTRL (offset 0x11E0) 
   unsigned int GetAdvTrgCtrl() {
      return BitExtractControl(WD2_ADV_TRG_CTRL_REG, WD2_ADV_TRG_CTRL_MASK, WD2_ADV_TRG_CTRL_OFS);
   };

   void SetAdvTrgCtrl(unsigned int value) {
      SetRegMask(WD2_ADV_TRG_CTRL_REG, WD2_ADV_TRG_CTRL_MASK, WD2_ADV_TRG_CTRL_OFS, value);
   };


   // Control Register 121: ADV_TRG_CH_CAL0 (offset 0x11E4) 
   unsigned int GetAdvTrgChCal0() {
      return BitExtractControl(WD2_ADV_TRG_CH_CAL0_REG, WD2_ADV_TRG_CH_CAL0_MASK, WD2_ADV_TRG_CH_CAL0_OFS);
   };

   void SetAdvTrgChCal0(unsigned int value) {
      SetRegMask(WD2_ADV_TRG_CH_CAL0_REG, WD2_ADV_TRG_CH_CAL0_MASK, WD2_ADV_TRG_CH_CAL0_OFS, value);
   };


   // Control Register 122: ADV_TRG_CH_CAL1 (offset 0x11E8) 
   unsigned int GetAdvTrgChCal1() {
      return BitExtractControl(WD2_ADV_TRG_CH_CAL1_REG, WD2_ADV_TRG_CH_CAL1_MASK, WD2_ADV_TRG_CH_CAL1_OFS);
   };

   void SetAdvTrgChCal1(unsigned int value) {
      SetRegMask(WD2_ADV_TRG_CH_CAL1_REG, WD2_ADV_TRG_CH_CAL1_MASK, WD2_ADV_TRG_CH_CAL1_OFS, value);
   };


   // Control Register 123: ADV_TRG_CH_CAL2 (offset 0x11EC) 
   unsigned int GetAdvTrgChCal2() {
      return BitExtractControl(WD2_ADV_TRG_CH_CAL2_REG, WD2_ADV_TRG_CH_CAL2_MASK, WD2_ADV_TRG_CH_CAL2_OFS);
   };

   void SetAdvTrgChCal2(unsigned int value) {
      SetRegMask(WD2_ADV_TRG_CH_CAL2_REG, WD2_ADV_TRG_CH_CAL2_MASK, WD2_ADV_TRG_CH_CAL2_OFS, value);
   };


   // Control Register 124: ADV_TRG_CH_CAL3 (offset 0x11F0) 
   unsigned int GetAdvTrgChCal3() {
      return BitExtractControl(WD2_ADV_TRG_CH_CAL3_REG, WD2_ADV_TRG_CH_CAL3_MASK, WD2_ADV_TRG_CH_CAL3_OFS);
   };

   void SetAdvTrgChCal3(unsigned int value) {
      SetRegMask(WD2_ADV_TRG_CH_CAL3_REG, WD2_ADV_TRG_CH_CAL3_MASK, WD2_ADV_TRG_CH_CAL3_OFS, value);
   };


   // Control Register 125: ADV_TRG_PED_CFG (offset 0x11F4) 
   unsigned int GetAdvTrgPedCfg() {
      return BitExtractControl(WD2_ADV_TRG_PED_CFG_REG, WD2_ADV_TRG_PED_CFG_MASK, WD2_ADV_TRG_PED_CFG_OFS);
   };

   void SetAdvTrgPedCfg(unsigned int value) {
      SetRegMask(WD2_ADV_TRG_PED_CFG_REG, WD2_ADV_TRG_PED_CFG_MASK, WD2_ADV_TRG_PED_CFG_OFS, value);
   };


   // Control Register 126: ADV_TRG_THR0 (offset 0x11F8) 
   unsigned int GetAdvTrgThr0() {
      return BitExtractControl(WD2_ADV_TRG_THR0_REG, WD2_ADV_TRG_THR0_MASK, WD2_ADV_TRG_THR0_OFS);
   };

   void SetAdvTrgThr0(unsigned int value) {
      SetRegMask(WD2_ADV_TRG_THR0_REG, WD2_ADV_TRG_THR0_MASK, WD2_ADV_TRG_THR0_OFS, value);
   };


   // Control Register 127: ADV_TRG_THR1 (offset 0x11FC) 
   unsigned int GetAdvTrgThr1() {
      return BitExtractControl(WD2_ADV_TRG_THR1_REG, WD2_ADV_TRG_THR1_MASK, WD2_ADV_TRG_THR1_OFS);
   };

   void SetAdvTrgThr1(unsigned int value) {
      SetRegMask(WD2_ADV_TRG_THR1_REG, WD2_ADV_TRG_THR1_MASK, WD2_ADV_TRG_THR1_OFS, value);
   };


   // Control Register 128: ADV_TRG_THR2 (offset 0x1200) 
   unsigned int GetAdvTrgThr2() {
      return BitExtractControl(WD2_ADV_TRG_THR2_REG, WD2_ADV_TRG_THR2_MASK, WD2_ADV_TRG_THR2_OFS);
   };

   void SetAdvTrgThr2(unsigned int value) {
      SetRegMask(WD2_ADV_TRG_THR2_REG, WD2_ADV_TRG_THR2_MASK, WD2_ADV_TRG_THR2_OFS, value);
   };


   // Control Register 129: ADV_TRG_TX_CHK_WORD0 (offset 0x1204) 
   unsigned int GetAdvTrgTxChkWord0() {
      return BitExtractControl(WD2_ADV_TRG_TX_CHK_WORD0_REG, WD2_ADV_TRG_TX_CHK_WORD0_MASK, WD2_ADV_TRG_TX_CHK_WORD0_OFS);
   };

   void SetAdvTrgTxChkWord0(unsigned int value) {
      SetRegMask(WD2_ADV_TRG_TX_CHK_WORD0_REG, WD2_ADV_TRG_TX_CHK_WORD0_MASK, WD2_ADV_TRG_TX_CHK_WORD0_OFS, value);
   };


   // Control Register 130: ADV_TRG_TX_CHK_WORD1 (offset 0x1208) 
   unsigned int GetAdvTrgTxChkWord1() {
      return BitExtractControl(WD2_ADV_TRG_TX_CHK_WORD1_REG, WD2_ADV_TRG_TX_CHK_WORD1_MASK, WD2_ADV_TRG_TX_CHK_WORD1_OFS);
   };

   void SetAdvTrgTxChkWord1(unsigned int value) {
      SetRegMask(WD2_ADV_TRG_TX_CHK_WORD1_REG, WD2_ADV_TRG_TX_CHK_WORD1_MASK, WD2_ADV_TRG_TX_CHK_WORD1_OFS, value);
   };


   // Control Register 131: ADV_TRG_TDC_CH_MASK (offset 0x120C) 
   unsigned int GetAdvTrgTdcChMask() {
      return BitExtractControl(WD2_ADV_TRG_TDC_CH_MASK_REG, WD2_ADV_TRG_TDC_CH_MASK_MASK, WD2_ADV_TRG_TDC_CH_MASK_OFS);
   };

   void SetAdvTrgTdcChMask(unsigned int value) {
      SetRegMask(WD2_ADV_TRG_TDC_CH_MASK_REG, WD2_ADV_TRG_TDC_CH_MASK_MASK, WD2_ADV_TRG_TDC_CH_MASK_OFS, value);
   };


   // Control Register 132: ADV_TRG_CFG12 (offset 0x1210) 
   unsigned int GetAdvTrgCfg12() {
      return BitExtractControl(WD2_ADV_TRG_CFG_12_REG, WD2_ADV_TRG_CFG_12_MASK, WD2_ADV_TRG_CFG_12_OFS);
   };

   void SetAdvTrgCfg12(unsigned int value) {
      SetRegMask(WD2_ADV_TRG_CFG_12_REG, WD2_ADV_TRG_CFG_12_MASK, WD2_ADV_TRG_CFG_12_OFS, value);
   };


   // Control Register 133: ADV_TRG_CFG13 (offset 0x1214) 
   unsigned int GetAdvTrgCfg13() {
      return BitExtractControl(WD2_ADV_TRG_CFG_13_REG, WD2_ADV_TRG_CFG_13_MASK, WD2_ADV_TRG_CFG_13_OFS);
   };

   void SetAdvTrgCfg13(unsigned int value) {
      SetRegMask(WD2_ADV_TRG_CFG_13_REG, WD2_ADV_TRG_CFG_13_MASK, WD2_ADV_TRG_CFG_13_OFS, value);
   };


   // Control Register 134: ADV_TRG_CFG14 (offset 0x1218) 
   unsigned int GetAdvTrgCfg14() {
      return BitExtractControl(WD2_ADV_TRG_CFG_14_REG, WD2_ADV_TRG_CFG_14_MASK, WD2_ADV_TRG_CFG_14_OFS);
   };

   void SetAdvTrgCfg14(unsigned int value) {
      SetRegMask(WD2_ADV_TRG_CFG_14_REG, WD2_ADV_TRG_CFG_14_MASK, WD2_ADV_TRG_CFG_14_OFS, value);
   };


   // Control Register 135: ADV_TRG_CFG15 (offset 0x121C) 
   unsigned int GetAdvTrgCfg15() {
      return BitExtractControl(WD2_ADV_TRG_CFG_15_REG, WD2_ADV_TRG_CFG_15_MASK, WD2_ADV_TRG_CFG_15_OFS);
   };

   void SetAdvTrgCfg15(unsigned int value) {
      SetRegMask(WD2_ADV_TRG_CFG_15_REG, WD2_ADV_TRG_CFG_15_MASK, WD2_ADV_TRG_CFG_15_OFS, value);
   };


   // Control Register 136: ADV_TRG_CFG16 (offset 0x1220) 
   unsigned int GetAdvTrgCfg16() {
      return BitExtractControl(WD2_ADV_TRG_CFG_16_REG, WD2_ADV_TRG_CFG_16_MASK, WD2_ADV_TRG_CFG_16_OFS);
   };

   void SetAdvTrgCfg16(unsigned int value) {
      SetRegMask(WD2_ADV_TRG_CFG_16_REG, WD2_ADV_TRG_CFG_16_MASK, WD2_ADV_TRG_CFG_16_OFS, value);
   };


   // Control Register 137: ADV_TRG_CFG17 (offset 0x1224) 
   unsigned int GetAdvTrgCfg17() {
      return BitExtractControl(WD2_ADV_TRG_CFG_17_REG, WD2_ADV_TRG_CFG_17_MASK, WD2_ADV_TRG_CFG_17_OFS);
   };

   void SetAdvTrgCfg17(unsigned int value) {
      SetRegMask(WD2_ADV_TRG_CFG_17_REG, WD2_ADV_TRG_CFG_17_MASK, WD2_ADV_TRG_CFG_17_OFS, value);
   };


   // Control Register 138: ADV_TRG_CFG18 (offset 0x1228) 
   unsigned int GetAdvTrgCfg18() {
      return BitExtractControl(WD2_ADV_TRG_CFG_18_REG, WD2_ADV_TRG_CFG_18_MASK, WD2_ADV_TRG_CFG_18_OFS);
   };

   void SetAdvTrgCfg18(unsigned int value) {
      SetRegMask(WD2_ADV_TRG_CFG_18_REG, WD2_ADV_TRG_CFG_18_MASK, WD2_ADV_TRG_CFG_18_OFS, value);
   };


   // Control Register 139: ADV_TRG_CFG19 (offset 0x122C) 
   unsigned int GetAdvTrgCfg19() {
      return BitExtractControl(WD2_ADV_TRG_CFG_19_REG, WD2_ADV_TRG_CFG_19_MASK, WD2_ADV_TRG_CFG_19_OFS);
   };

   void SetAdvTrgCfg19(unsigned int value) {
      SetRegMask(WD2_ADV_TRG_CFG_19_REG, WD2_ADV_TRG_CFG_19_MASK, WD2_ADV_TRG_CFG_19_OFS, value);
   };


   // Control Register 140: SET_TIME_LSB (offset 0x1230) 
   unsigned int GetSetTimeLsb() {
      return BitExtractControl(WD2_SET_TIME_LSB_REG, WD2_SET_TIME_LSB_MASK, WD2_SET_TIME_LSB_OFS);
   };

   void SetSetTimeLsb(unsigned int value) {
      SetRegMask(WD2_SET_TIME_LSB_REG, WD2_SET_TIME_LSB_MASK, WD2_SET_TIME_LSB_OFS, value);
   };


   // Control Register 141: SET_TIME_MSB (offset 0x1234) 
   unsigned int GetSetTimeMsb() {
      return BitExtractControl(WD2_SET_TIME_MSB_REG, WD2_SET_TIME_MSB_MASK, WD2_SET_TIME_MSB_OFS);
   };

   void SetSetTimeMsb(unsigned int value) {
      SetRegMask(WD2_SET_TIME_MSB_REG, WD2_SET_TIME_MSB_MASK, WD2_SET_TIME_MSB_OFS, value);
   };


   // Control Register 142: DBG_SIG_SEL (offset 0x1238) 
   unsigned int GetMcxTxSigSel() {
      return BitExtractControl(WD2_MCX_TX_SIG_SEL_REG, WD2_MCX_TX_SIG_SEL_MASK, WD2_MCX_TX_SIG_SEL_OFS);
   };

   void SetMcxTxSigSel(unsigned int value) {
      SetRegMask(WD2_MCX_TX_SIG_SEL_REG, WD2_MCX_TX_SIG_SEL_MASK, WD2_MCX_TX_SIG_SEL_OFS, value);
   };

   unsigned int GetMcxRxSigSel() {
      return BitExtractControl(WD2_MCX_RX_SIG_SEL_REG, WD2_MCX_RX_SIG_SEL_MASK, WD2_MCX_RX_SIG_SEL_OFS);
   };

   void SetMcxRxSigSel(unsigned int value) {
      SetRegMask(WD2_MCX_RX_SIG_SEL_REG, WD2_MCX_RX_SIG_SEL_MASK, WD2_MCX_RX_SIG_SEL_OFS, value);
   };


   // Control Register 143: CRC32_REG_BANK (offset 0x123C) 
   unsigned int GetCrc32RegBank() {
      return BitExtractControl(WD2_CRC32_REG_BANK_REG, WD2_CRC32_REG_BANK_MASK, WD2_CRC32_REG_BANK_OFS);
   };

   void SetCrc32RegBank(unsigned int value) {
      SetRegMask(WD2_CRC32_REG_BANK_REG, WD2_CRC32_REG_BANK_MASK, WD2_CRC32_REG_BANK_OFS, value);
   };


   // Status Register 0: HW_VER (offset 0x0000) 
   unsigned int GetBoardMagic() {
      return BitExtractStatus(WD2_BOARD_MAGIC_REG, WD2_BOARD_MAGIC_MASK, WD2_BOARD_MAGIC_OFS);
   };

   unsigned int GetVendorId() {
      return BitExtractStatus(WD2_VENDOR_ID_REG, WD2_VENDOR_ID_MASK, WD2_VENDOR_ID_OFS);
   };

   unsigned int GetBoardType() {
      return BitExtractStatus(WD2_BOARD_TYPE_REG, WD2_BOARD_TYPE_MASK, WD2_BOARD_TYPE_OFS);
   };

   unsigned int GetBoardRevision() {
      return BitExtractStatus(WD2_BOARD_REVISION_REG, WD2_BOARD_REVISION_MASK, WD2_BOARD_REVISION_OFS);
   };

   unsigned int GetBoardVariant() {
      return BitExtractStatus(WD2_BOARD_VARIANT_REG, WD2_BOARD_VARIANT_MASK, WD2_BOARD_VARIANT_OFS);
   };


   // Status Register 1: REG_LAYOUT_VER (offset 0x0004) 
   unsigned int GetRegLayoutCompLevel() {
      return BitExtractStatus(WD2_REG_LAYOUT_COMP_LEVEL_REG, WD2_REG_LAYOUT_COMP_LEVEL_MASK, WD2_REG_LAYOUT_COMP_LEVEL_OFS);
   };

   unsigned int GetRegLayoutVersion() {
      return BitExtractStatus(WD2_REG_LAYOUT_VERSION_REG, WD2_REG_LAYOUT_VERSION_MASK, WD2_REG_LAYOUT_VERSION_OFS);
   };


   // Status Register 2: FW_BUILD_DATE (offset 0x0008) 
   unsigned int GetFwBuildYear() {
      return BitExtractStatus(WD2_FW_BUILD_YEAR_REG, WD2_FW_BUILD_YEAR_MASK, WD2_FW_BUILD_YEAR_OFS);
   };

   unsigned int GetFwBuildMonth() {
      return BitExtractStatus(WD2_FW_BUILD_MONTH_REG, WD2_FW_BUILD_MONTH_MASK, WD2_FW_BUILD_MONTH_OFS);
   };

   unsigned int GetFwBuildDay() {
      return BitExtractStatus(WD2_FW_BUILD_DAY_REG, WD2_FW_BUILD_DAY_MASK, WD2_FW_BUILD_DAY_OFS);
   };


   // Status Register 3: FW_BUILD_TIME (offset 0x000C) 
   unsigned int GetFwCompatLevel() {
      return BitExtractStatus(WD2_FW_COMPAT_LEVEL_REG, WD2_FW_COMPAT_LEVEL_MASK, WD2_FW_COMPAT_LEVEL_OFS);
   };

   unsigned int GetFwBuildHour() {
      return BitExtractStatus(WD2_FW_BUILD_HOUR_REG, WD2_FW_BUILD_HOUR_MASK, WD2_FW_BUILD_HOUR_OFS);
   };

   unsigned int GetFwBuildMinute() {
      return BitExtractStatus(WD2_FW_BUILD_MINUTE_REG, WD2_FW_BUILD_MINUTE_MASK, WD2_FW_BUILD_MINUTE_OFS);
   };

   unsigned int GetFwBuildSecond() {
      return BitExtractStatus(WD2_FW_BUILD_SECOND_REG, WD2_FW_BUILD_SECOND_MASK, WD2_FW_BUILD_SECOND_OFS);
   };


   // Status Register 4: SW_BUILD_DATE (offset 0x0010) 
   unsigned int GetSwBuildYear() {
      return BitExtractStatus(WD2_SW_BUILD_YEAR_REG, WD2_SW_BUILD_YEAR_MASK, WD2_SW_BUILD_YEAR_OFS);
   };

   unsigned int GetSwBuildMonth() {
      return BitExtractStatus(WD2_SW_BUILD_MONTH_REG, WD2_SW_BUILD_MONTH_MASK, WD2_SW_BUILD_MONTH_OFS);
   };

   unsigned int GetSwBuildDay() {
      return BitExtractStatus(WD2_SW_BUILD_DAY_REG, WD2_SW_BUILD_DAY_MASK, WD2_SW_BUILD_DAY_OFS);
   };


   // Status Register 5: SW_BUILD_TIME (offset 0x0014) 
   unsigned int GetSwBuildHour() {
      return BitExtractStatus(WD2_SW_BUILD_HOUR_REG, WD2_SW_BUILD_HOUR_MASK, WD2_SW_BUILD_HOUR_OFS);
   };

   unsigned int GetSwBuildMinute() {
      return BitExtractStatus(WD2_SW_BUILD_MINUTE_REG, WD2_SW_BUILD_MINUTE_MASK, WD2_SW_BUILD_MINUTE_OFS);
   };

   unsigned int GetSwBuildSecond() {
      return BitExtractStatus(WD2_SW_BUILD_SECOND_REG, WD2_SW_BUILD_SECOND_MASK, WD2_SW_BUILD_SECOND_OFS);
   };


   // Status Register 6: GIT_HASH_TAG (offset 0x0018) 
   unsigned int GetGitHashTag() {
      return BitExtractStatus(WD2_GIT_HASH_TAG_REG, WD2_GIT_HASH_TAG_MASK, WD2_GIT_HASH_TAG_OFS);
   };


   // Status Register 7: PROT_VER (offset 0x001C) 
   unsigned int GetProtocolVersion() {
      return BitExtractStatus(WD2_PROTOCOL_VERSION_REG, WD2_PROTOCOL_VERSION_MASK, WD2_PROTOCOL_VERSION_OFS);
   };


   // Status Register 8: SN (offset 0x0020) 
   unsigned int GetSerialNumber() {
      return BitExtractStatus(WD2_SERIAL_NUMBER_REG, WD2_SERIAL_NUMBER_MASK, WD2_SERIAL_NUMBER_OFS);
   };


   // Status Register 9: STATUS (offset 0x0024) 
   unsigned int GetTemperature() {
      return BitExtractStatus(WD2_TEMPERATURE_REG, WD2_TEMPERATURE_MASK, WD2_TEMPERATURE_OFS);
   };

   unsigned int GetFlashSel() {
      return BitExtractStatus(WD2_FLASH_SEL_REG, WD2_FLASH_SEL_MASK, WD2_FLASH_SEL_OFS);
   };

   unsigned int GetBoardSel() {
      return BitExtractStatus(WD2_BOARD_SEL_REG, WD2_BOARD_SEL_MASK, WD2_BOARD_SEL_OFS);
   };

   unsigned int GetDrsConfigDone() {
      return BitExtractStatus(WD2_DRS_CONFIG_DONE_REG, WD2_DRS_CONFIG_DONE_MASK, WD2_DRS_CONFIG_DONE_OFS);
   };

   unsigned int GetSerialBusy() {
      return BitExtractStatus(WD2_SERIAL_BUSY_REG, WD2_SERIAL_BUSY_MASK, WD2_SERIAL_BUSY_OFS);
   };

   unsigned int GetSysBusy() {
      return BitExtractStatus(WD2_SYS_BUSY_REG, WD2_SYS_BUSY_MASK, WD2_SYS_BUSY_OFS);
   };

   unsigned int GetWdbBusy() {
      return BitExtractStatus(WD2_WDB_BUSY_REG, WD2_WDB_BUSY_MASK, WD2_WDB_BUSY_OFS);
   };

   unsigned int GetHvBoardPlugged() {
      return BitExtractStatus(WD2_HV_BOARD_PLUGGED_REG, WD2_HV_BOARD_PLUGGED_MASK, WD2_HV_BOARD_PLUGGED_OFS);
   };

   unsigned int GetBackplanePlugged() {
      return BitExtractStatus(WD2_BACKPLANE_PLUGGED_REG, WD2_BACKPLANE_PLUGGED_MASK, WD2_BACKPLANE_PLUGGED_OFS);
   };


   // Status Register 10: PLL_LOCK (offset 0x0028) 
   unsigned int GetSysDcmLock() {
      return BitExtractStatus(WD2_SYS_DCM_LOCK_REG, WD2_SYS_DCM_LOCK_MASK, WD2_SYS_DCM_LOCK_OFS);
   };

   unsigned int GetDaqPllLock() {
      return BitExtractStatus(WD2_DAQ_PLL_LOCK_REG, WD2_DAQ_PLL_LOCK_MASK, WD2_DAQ_PLL_LOCK_OFS);
   };

   unsigned int GetOserdesPllLockDcb() {
      return BitExtractStatus(WD2_OSERDES_PLL_LOCK_DCB_REG, WD2_OSERDES_PLL_LOCK_DCB_MASK, WD2_OSERDES_PLL_LOCK_DCB_OFS);
   };

   unsigned int GetOserdesPllLockTcb() {
      return BitExtractStatus(WD2_OSERDES_PLL_LOCK_TCB_REG, WD2_OSERDES_PLL_LOCK_TCB_MASK, WD2_OSERDES_PLL_LOCK_TCB_OFS);
   };

   unsigned int GetIserdesPllLock0() {
      return BitExtractStatus(WD2_ISERDES_PLL_LOCK_0_REG, WD2_ISERDES_PLL_LOCK_0_MASK, WD2_ISERDES_PLL_LOCK_0_OFS);
   };

   unsigned int GetIserdesPllLock1() {
      return BitExtractStatus(WD2_ISERDES_PLL_LOCK_1_REG, WD2_ISERDES_PLL_LOCK_1_MASK, WD2_ISERDES_PLL_LOCK_1_OFS);
   };

   unsigned int GetDrsPllLock0() {
      return BitExtractStatus(WD2_DRS_PLL_LOCK_0_REG, WD2_DRS_PLL_LOCK_0_MASK, WD2_DRS_PLL_LOCK_0_OFS);
   };

   unsigned int GetDrsPllLock1() {
      return BitExtractStatus(WD2_DRS_PLL_LOCK_1_REG, WD2_DRS_PLL_LOCK_1_MASK, WD2_DRS_PLL_LOCK_1_OFS);
   };

   unsigned int GetLmkPllLock() {
      return BitExtractStatus(WD2_LMK_PLL_LOCK_REG, WD2_LMK_PLL_LOCK_MASK, WD2_LMK_PLL_LOCK_OFS);
   };


   // Status Register 11: DRS_STOP_CELL (offset 0x002C) 
   unsigned int GetDrsStopCell0() {
      return BitExtractStatus(WD2_DRS_STOP_CELL_0_REG, WD2_DRS_STOP_CELL_0_MASK, WD2_DRS_STOP_CELL_0_OFS);
   };

   unsigned int GetDrsStopCell1() {
      return BitExtractStatus(WD2_DRS_STOP_CELL_1_REG, WD2_DRS_STOP_CELL_1_MASK, WD2_DRS_STOP_CELL_1_OFS);
   };


   // Status Register 12: DRS_STOP_WSR (offset 0x0030) 
   unsigned int GetDrsStopWsr0() {
      return BitExtractStatus(WD2_DRS_STOP_WSR_0_REG, WD2_DRS_STOP_WSR_0_MASK, WD2_DRS_STOP_WSR_0_OFS);
   };

   unsigned int GetDrsStopWsr1() {
      return BitExtractStatus(WD2_DRS_STOP_WSR_1_REG, WD2_DRS_STOP_WSR_1_MASK, WD2_DRS_STOP_WSR_1_OFS);
   };


   // Status Register 13: DRS_SAMPLE_FREQ (offset 0x0034) 
   unsigned int GetDrsSampleFreq() {
      return BitExtractStatus(WD2_DRS_SAMPLE_FREQ_REG, WD2_DRS_SAMPLE_FREQ_MASK, WD2_DRS_SAMPLE_FREQ_OFS);
   };


   // Status Register 14: ADC_SAMPLE_FREQ (offset 0x0038) 
   unsigned int GetAdcSampleFreq() {
      return BitExtractStatus(WD2_ADC_SAMPLE_FREQ_REG, WD2_ADC_SAMPLE_FREQ_MASK, WD2_ADC_SAMPLE_FREQ_OFS);
   };


   // Status Register 15: TDC_SAMPLE_FREQ (offset 0x003C) 
   unsigned int GetTdcSampleFreq() {
      return BitExtractStatus(WD2_TDC_SAMPLE_FREQ_REG, WD2_TDC_SAMPLE_FREQ_MASK, WD2_TDC_SAMPLE_FREQ_OFS);
   };


   // Status Register 16: ADC_INFO (offset 0x0040) 
   unsigned int GetAdc0ChipId() {
      return BitExtractStatus(WD2_ADC_0_CHIP_ID_REG, WD2_ADC_0_CHIP_ID_MASK, WD2_ADC_0_CHIP_ID_OFS);
   };

   unsigned int GetAdc0Speed() {
      return BitExtractStatus(WD2_ADC_0_SPEED_REG, WD2_ADC_0_SPEED_MASK, WD2_ADC_0_SPEED_OFS);
   };

   unsigned int GetAdc1ChipId() {
      return BitExtractStatus(WD2_ADC_1_CHIP_ID_REG, WD2_ADC_1_CHIP_ID_MASK, WD2_ADC_1_CHIP_ID_OFS);
   };

   unsigned int GetAdc1Speed() {
      return BitExtractStatus(WD2_ADC_1_SPEED_REG, WD2_ADC_1_SPEED_MASK, WD2_ADC_1_SPEED_OFS);
   };


   // Status Register 17: HV_VER (offset 0x0044) 
   unsigned int GetHvVer() {
      return BitExtractStatus(WD2_HV_VER_REG, WD2_HV_VER_MASK, WD2_HV_VER_OFS);
   };


   // Status Register 18: HV_I_MEAS_0 (offset 0x0048) 
   unsigned int GetHvIMeas0() {
      return BitExtractStatus(WD2_HV_I_MEAS_0_REG, WD2_HV_I_MEAS_0_MASK, WD2_HV_I_MEAS_0_OFS);
   };


   // Status Register 19: HV_I_MEAS_1 (offset 0x004C) 
   unsigned int GetHvIMeas1() {
      return BitExtractStatus(WD2_HV_I_MEAS_1_REG, WD2_HV_I_MEAS_1_MASK, WD2_HV_I_MEAS_1_OFS);
   };


   // Status Register 20: HV_I_MEAS_2 (offset 0x0050) 
   unsigned int GetHvIMeas2() {
      return BitExtractStatus(WD2_HV_I_MEAS_2_REG, WD2_HV_I_MEAS_2_MASK, WD2_HV_I_MEAS_2_OFS);
   };


   // Status Register 21: HV_I_MEAS_3 (offset 0x0054) 
   unsigned int GetHvIMeas3() {
      return BitExtractStatus(WD2_HV_I_MEAS_3_REG, WD2_HV_I_MEAS_3_MASK, WD2_HV_I_MEAS_3_OFS);
   };


   // Status Register 22: HV_I_MEAS_4 (offset 0x0058) 
   unsigned int GetHvIMeas4() {
      return BitExtractStatus(WD2_HV_I_MEAS_4_REG, WD2_HV_I_MEAS_4_MASK, WD2_HV_I_MEAS_4_OFS);
   };


   // Status Register 23: HV_I_MEAS_5 (offset 0x005C) 
   unsigned int GetHvIMeas5() {
      return BitExtractStatus(WD2_HV_I_MEAS_5_REG, WD2_HV_I_MEAS_5_MASK, WD2_HV_I_MEAS_5_OFS);
   };


   // Status Register 24: HV_I_MEAS_6 (offset 0x0060) 
   unsigned int GetHvIMeas6() {
      return BitExtractStatus(WD2_HV_I_MEAS_6_REG, WD2_HV_I_MEAS_6_MASK, WD2_HV_I_MEAS_6_OFS);
   };


   // Status Register 25: HV_I_MEAS_7 (offset 0x0064) 
   unsigned int GetHvIMeas7() {
      return BitExtractStatus(WD2_HV_I_MEAS_7_REG, WD2_HV_I_MEAS_7_MASK, WD2_HV_I_MEAS_7_OFS);
   };


   // Status Register 26: HV_I_MEAS_8 (offset 0x0068) 
   unsigned int GetHvIMeas8() {
      return BitExtractStatus(WD2_HV_I_MEAS_8_REG, WD2_HV_I_MEAS_8_MASK, WD2_HV_I_MEAS_8_OFS);
   };


   // Status Register 27: HV_I_MEAS_9 (offset 0x006C) 
   unsigned int GetHvIMeas9() {
      return BitExtractStatus(WD2_HV_I_MEAS_9_REG, WD2_HV_I_MEAS_9_MASK, WD2_HV_I_MEAS_9_OFS);
   };


   // Status Register 28: HV_I_MEAS_10 (offset 0x0070) 
   unsigned int GetHvIMeas10() {
      return BitExtractStatus(WD2_HV_I_MEAS_10_REG, WD2_HV_I_MEAS_10_MASK, WD2_HV_I_MEAS_10_OFS);
   };


   // Status Register 29: HV_I_MEAS_11 (offset 0x0074) 
   unsigned int GetHvIMeas11() {
      return BitExtractStatus(WD2_HV_I_MEAS_11_REG, WD2_HV_I_MEAS_11_MASK, WD2_HV_I_MEAS_11_OFS);
   };


   // Status Register 30: HV_I_MEAS_12 (offset 0x0078) 
   unsigned int GetHvIMeas12() {
      return BitExtractStatus(WD2_HV_I_MEAS_12_REG, WD2_HV_I_MEAS_12_MASK, WD2_HV_I_MEAS_12_OFS);
   };


   // Status Register 31: HV_I_MEAS_13 (offset 0x007C) 
   unsigned int GetHvIMeas13() {
      return BitExtractStatus(WD2_HV_I_MEAS_13_REG, WD2_HV_I_MEAS_13_MASK, WD2_HV_I_MEAS_13_OFS);
   };


   // Status Register 32: HV_I_MEAS_14 (offset 0x0080) 
   unsigned int GetHvIMeas14() {
      return BitExtractStatus(WD2_HV_I_MEAS_14_REG, WD2_HV_I_MEAS_14_MASK, WD2_HV_I_MEAS_14_OFS);
   };


   // Status Register 33: HV_I_MEAS_15 (offset 0x0084) 
   unsigned int GetHvIMeas15() {
      return BitExtractStatus(WD2_HV_I_MEAS_15_REG, WD2_HV_I_MEAS_15_MASK, WD2_HV_I_MEAS_15_OFS);
   };


   // Status Register 34: HV_U_BASE_MEAS (offset 0x0088) 
   unsigned int GetHvUBaseMeas() {
      return BitExtractStatus(WD2_HV_U_BASE_MEAS_REG, WD2_HV_U_BASE_MEAS_MASK, WD2_HV_U_BASE_MEAS_OFS);
   };


   // Status Register 35: HV_TEMP_0 (offset 0x008C) 
   unsigned int GetHvTemp0() {
      return BitExtractStatus(WD2_HV_TEMP_0_REG, WD2_HV_TEMP_0_MASK, WD2_HV_TEMP_0_OFS);
   };


   // Status Register 36: HV_TEMP_1 (offset 0x0090) 
   unsigned int GetHvTemp1() {
      return BitExtractStatus(WD2_HV_TEMP_1_REG, WD2_HV_TEMP_1_MASK, WD2_HV_TEMP_1_OFS);
   };


   // Status Register 37: HV_TEMP_2 (offset 0x0094) 
   unsigned int GetHvTemp2() {
      return BitExtractStatus(WD2_HV_TEMP_2_REG, WD2_HV_TEMP_2_MASK, WD2_HV_TEMP_2_OFS);
   };


   // Status Register 38: HV_TEMP_3 (offset 0x0098) 
   unsigned int GetHvTemp3() {
      return BitExtractStatus(WD2_HV_TEMP_3_REG, WD2_HV_TEMP_3_MASK, WD2_HV_TEMP_3_OFS);
   };


   // Status Register 39: SCALER_0_LSB (offset 0x009C) 
   unsigned int GetScaler0Lsb() {
      return BitExtractStatus(WD2_SCALER_0_LSB_REG, WD2_SCALER_0_LSB_MASK, WD2_SCALER_0_LSB_OFS);
   };


   // Status Register 40: SCALER_0_MSB (offset 0x00A0) 
   unsigned int GetScaler0Msb() {
      return BitExtractStatus(WD2_SCALER_0_MSB_REG, WD2_SCALER_0_MSB_MASK, WD2_SCALER_0_MSB_OFS);
   };


   // Status Register 41: SCALER_1_LSB (offset 0x00A4) 
   unsigned int GetScaler1Lsb() {
      return BitExtractStatus(WD2_SCALER_1_LSB_REG, WD2_SCALER_1_LSB_MASK, WD2_SCALER_1_LSB_OFS);
   };


   // Status Register 42: SCALER_1_MSB (offset 0x00A8) 
   unsigned int GetScaler1Msb() {
      return BitExtractStatus(WD2_SCALER_1_MSB_REG, WD2_SCALER_1_MSB_MASK, WD2_SCALER_1_MSB_OFS);
   };


   // Status Register 43: SCALER_2_LSB (offset 0x00AC) 
   unsigned int GetScaler2Lsb() {
      return BitExtractStatus(WD2_SCALER_2_LSB_REG, WD2_SCALER_2_LSB_MASK, WD2_SCALER_2_LSB_OFS);
   };


   // Status Register 44: SCALER_2_MSB (offset 0x00B0) 
   unsigned int GetScaler2Msb() {
      return BitExtractStatus(WD2_SCALER_2_MSB_REG, WD2_SCALER_2_MSB_MASK, WD2_SCALER_2_MSB_OFS);
   };


   // Status Register 45: SCALER_3_LSB (offset 0x00B4) 
   unsigned int GetScaler3Lsb() {
      return BitExtractStatus(WD2_SCALER_3_LSB_REG, WD2_SCALER_3_LSB_MASK, WD2_SCALER_3_LSB_OFS);
   };


   // Status Register 46: SCALER_3_MSB (offset 0x00B8) 
   unsigned int GetScaler3Msb() {
      return BitExtractStatus(WD2_SCALER_3_MSB_REG, WD2_SCALER_3_MSB_MASK, WD2_SCALER_3_MSB_OFS);
   };


   // Status Register 47: SCALER_4_LSB (offset 0x00BC) 
   unsigned int GetScaler4Lsb() {
      return BitExtractStatus(WD2_SCALER_4_LSB_REG, WD2_SCALER_4_LSB_MASK, WD2_SCALER_4_LSB_OFS);
   };


   // Status Register 48: SCALER_4_MSB (offset 0x00C0) 
   unsigned int GetScaler4Msb() {
      return BitExtractStatus(WD2_SCALER_4_MSB_REG, WD2_SCALER_4_MSB_MASK, WD2_SCALER_4_MSB_OFS);
   };


   // Status Register 49: SCALER_5_LSB (offset 0x00C4) 
   unsigned int GetScaler5Lsb() {
      return BitExtractStatus(WD2_SCALER_5_LSB_REG, WD2_SCALER_5_LSB_MASK, WD2_SCALER_5_LSB_OFS);
   };


   // Status Register 50: SCALER_5_MSB (offset 0x00C8) 
   unsigned int GetScaler5Msb() {
      return BitExtractStatus(WD2_SCALER_5_MSB_REG, WD2_SCALER_5_MSB_MASK, WD2_SCALER_5_MSB_OFS);
   };


   // Status Register 51: SCALER_6_LSB (offset 0x00CC) 
   unsigned int GetScaler6Lsb() {
      return BitExtractStatus(WD2_SCALER_6_LSB_REG, WD2_SCALER_6_LSB_MASK, WD2_SCALER_6_LSB_OFS);
   };


   // Status Register 52: SCALER_6_MSB (offset 0x00D0) 
   unsigned int GetScaler6Msb() {
      return BitExtractStatus(WD2_SCALER_6_MSB_REG, WD2_SCALER_6_MSB_MASK, WD2_SCALER_6_MSB_OFS);
   };


   // Status Register 53: SCALER_7_LSB (offset 0x00D4) 
   unsigned int GetScaler7Lsb() {
      return BitExtractStatus(WD2_SCALER_7_LSB_REG, WD2_SCALER_7_LSB_MASK, WD2_SCALER_7_LSB_OFS);
   };


   // Status Register 54: SCALER_7_MSB (offset 0x00D8) 
   unsigned int GetScaler7Msb() {
      return BitExtractStatus(WD2_SCALER_7_MSB_REG, WD2_SCALER_7_MSB_MASK, WD2_SCALER_7_MSB_OFS);
   };


   // Status Register 55: SCALER_8_LSB (offset 0x00DC) 
   unsigned int GetScaler8Lsb() {
      return BitExtractStatus(WD2_SCALER_8_LSB_REG, WD2_SCALER_8_LSB_MASK, WD2_SCALER_8_LSB_OFS);
   };


   // Status Register 56: SCALER_8_MSB (offset 0x00E0) 
   unsigned int GetScaler8Msb() {
      return BitExtractStatus(WD2_SCALER_8_MSB_REG, WD2_SCALER_8_MSB_MASK, WD2_SCALER_8_MSB_OFS);
   };


   // Status Register 57: SCALER_9_LSB (offset 0x00E4) 
   unsigned int GetScaler9Lsb() {
      return BitExtractStatus(WD2_SCALER_9_LSB_REG, WD2_SCALER_9_LSB_MASK, WD2_SCALER_9_LSB_OFS);
   };


   // Status Register 58: SCALER_9_MSB (offset 0x00E8) 
   unsigned int GetScaler9Msb() {
      return BitExtractStatus(WD2_SCALER_9_MSB_REG, WD2_SCALER_9_MSB_MASK, WD2_SCALER_9_MSB_OFS);
   };


   // Status Register 59: SCALER_10_LSB (offset 0x00EC) 
   unsigned int GetScaler10Lsb() {
      return BitExtractStatus(WD2_SCALER_10_LSB_REG, WD2_SCALER_10_LSB_MASK, WD2_SCALER_10_LSB_OFS);
   };


   // Status Register 60: SCALER_10_MSB (offset 0x00F0) 
   unsigned int GetScaler10Msb() {
      return BitExtractStatus(WD2_SCALER_10_MSB_REG, WD2_SCALER_10_MSB_MASK, WD2_SCALER_10_MSB_OFS);
   };


   // Status Register 61: SCALER_11_LSB (offset 0x00F4) 
   unsigned int GetScaler11Lsb() {
      return BitExtractStatus(WD2_SCALER_11_LSB_REG, WD2_SCALER_11_LSB_MASK, WD2_SCALER_11_LSB_OFS);
   };


   // Status Register 62: SCALER_11_MSB (offset 0x00F8) 
   unsigned int GetScaler11Msb() {
      return BitExtractStatus(WD2_SCALER_11_MSB_REG, WD2_SCALER_11_MSB_MASK, WD2_SCALER_11_MSB_OFS);
   };


   // Status Register 63: SCALER_12_LSB (offset 0x00FC) 
   unsigned int GetScaler12Lsb() {
      return BitExtractStatus(WD2_SCALER_12_LSB_REG, WD2_SCALER_12_LSB_MASK, WD2_SCALER_12_LSB_OFS);
   };


   // Status Register 64: SCALER_12_MSB (offset 0x0100) 
   unsigned int GetScaler12Msb() {
      return BitExtractStatus(WD2_SCALER_12_MSB_REG, WD2_SCALER_12_MSB_MASK, WD2_SCALER_12_MSB_OFS);
   };


   // Status Register 65: SCALER_13_LSB (offset 0x0104) 
   unsigned int GetScaler13Lsb() {
      return BitExtractStatus(WD2_SCALER_13_LSB_REG, WD2_SCALER_13_LSB_MASK, WD2_SCALER_13_LSB_OFS);
   };


   // Status Register 66: SCALER_13_MSB (offset 0x0108) 
   unsigned int GetScaler13Msb() {
      return BitExtractStatus(WD2_SCALER_13_MSB_REG, WD2_SCALER_13_MSB_MASK, WD2_SCALER_13_MSB_OFS);
   };


   // Status Register 67: SCALER_14_LSB (offset 0x010C) 
   unsigned int GetScaler14Lsb() {
      return BitExtractStatus(WD2_SCALER_14_LSB_REG, WD2_SCALER_14_LSB_MASK, WD2_SCALER_14_LSB_OFS);
   };


   // Status Register 68: SCALER_14_MSB (offset 0x0110) 
   unsigned int GetScaler14Msb() {
      return BitExtractStatus(WD2_SCALER_14_MSB_REG, WD2_SCALER_14_MSB_MASK, WD2_SCALER_14_MSB_OFS);
   };


   // Status Register 69: SCALER_15_LSB (offset 0x0114) 
   unsigned int GetScaler15Lsb() {
      return BitExtractStatus(WD2_SCALER_15_LSB_REG, WD2_SCALER_15_LSB_MASK, WD2_SCALER_15_LSB_OFS);
   };


   // Status Register 70: SCALER_15_MSB (offset 0x0118) 
   unsigned int GetScaler15Msb() {
      return BitExtractStatus(WD2_SCALER_15_MSB_REG, WD2_SCALER_15_MSB_MASK, WD2_SCALER_15_MSB_OFS);
   };


   // Status Register 71: SCALER_TRG_LSB (offset 0x011C) 
   unsigned int GetScalerTrgLsb() {
      return BitExtractStatus(WD2_SCALER_TRG_LSB_REG, WD2_SCALER_TRG_LSB_MASK, WD2_SCALER_TRG_LSB_OFS);
   };


   // Status Register 72: SCALER_TRG_MSB (offset 0x0120) 
   unsigned int GetScalerTrgMsb() {
      return BitExtractStatus(WD2_SCALER_TRG_MSB_REG, WD2_SCALER_TRG_MSB_MASK, WD2_SCALER_TRG_MSB_OFS);
   };


   // Status Register 73: SCALER_EXT_CLK (offset 0x0124) 
   unsigned int GetScalerExtClk() {
      return BitExtractStatus(WD2_SCALER_EXT_CLK_REG, WD2_SCALER_EXT_CLK_MASK, WD2_SCALER_EXT_CLK_OFS);
   };


   // Status Register 74: EVENT_TX_RATE (offset 0x0128) 
   unsigned int GetEventTxRate() {
      return BitExtractStatus(WD2_EVENT_TX_RATE_REG, WD2_EVENT_TX_RATE_MASK, WD2_EVENT_TX_RATE_OFS);
   };


   // Status Register 75: TIME_LSB (offset 0x012C) 
   unsigned int GetTimeLsb() {
      return BitExtractStatus(WD2_TIME_LSB_REG, WD2_TIME_LSB_MASK, WD2_TIME_LSB_OFS);
   };


   // Status Register 76: TIME_MSB (offset 0x0130) 
   unsigned int GetTimeMsb() {
      return BitExtractStatus(WD2_TIME_MSB_REG, WD2_TIME_MSB_MASK, WD2_TIME_MSB_OFS);
   };


   // Status Register 77: COMP_CH_STAT (offset 0x0134) 
   unsigned int GetCompChStat() {
      return BitExtractStatus(WD2_COMP_CH_STAT_REG, WD2_COMP_CH_STAT_MASK, WD2_COMP_CH_STAT_OFS);
   };


   // Status Register 78: EVENT_NR (offset 0x0138) 
   unsigned int GetEventNumber() {
      return BitExtractStatus(WD2_EVENT_NUMBER_REG, WD2_EVENT_NUMBER_MASK, WD2_EVENT_NUMBER_OFS);
   };


   // Status Register 79: TRB_INFO_STAT (offset 0x013C) 
   unsigned int GetTrbFlagNew() {
      return BitExtractStatus(WD2_TRB_FLAG_NEW_REG, WD2_TRB_FLAG_NEW_MASK, WD2_TRB_FLAG_NEW_OFS);
   };

   unsigned int GetTrbFlagParityError() {
      return BitExtractStatus(WD2_TRB_FLAG_PARITY_ERROR_REG, WD2_TRB_FLAG_PARITY_ERROR_MASK, WD2_TRB_FLAG_PARITY_ERROR_OFS);
   };

   unsigned int GetTrbParityErrorCount() {
      return BitExtractStatus(WD2_TRB_PARITY_ERROR_COUNT_REG, WD2_TRB_PARITY_ERROR_COUNT_MASK, WD2_TRB_PARITY_ERROR_COUNT_OFS);
   };


   // Status Register 80: TRB_INFO_LSB (offset 0x0140) 
   unsigned int GetTrbInfoLsb() {
      return BitExtractStatus(WD2_TRB_INFO_LSB_REG, WD2_TRB_INFO_LSB_MASK, WD2_TRB_INFO_LSB_OFS);
   };


   // Status Register 81: TRB_INFO_MSB (offset 0x0144) 
   unsigned int GetTrbInfoMsb() {
      return BitExtractStatus(WD2_TRB_INFO_MSB_REG, WD2_TRB_INFO_MSB_MASK, WD2_TRB_INFO_MSB_OFS);
   };


   // Status Register 82: ADV_TRG_TRIG_CELL (offset 0x0148) 
   unsigned int GetAdvTrgTrigCell() {
      return BitExtractStatus(WD2_ADV_TRG_TRIG_CELL_REG, WD2_ADV_TRG_TRIG_CELL_MASK, WD2_ADV_TRG_TRIG_CELL_OFS);
   };


   // Status Register 83: ADV_TRG_STAT1 (offset 0x014C) 
   unsigned int GetAdvTrgStat1() {
      return BitExtractStatus(WD2_ADV_TRG_STAT_1_REG, WD2_ADV_TRG_STAT_1_MASK, WD2_ADV_TRG_STAT_1_OFS);
   };


   // Status Register 84: ADV_TRG_STAT2 (offset 0x0150) 
   unsigned int GetAdvTrgStat2() {
      return BitExtractStatus(WD2_ADV_TRG_STAT_2_REG, WD2_ADV_TRG_STAT_2_MASK, WD2_ADV_TRG_STAT_2_OFS);
   };


   // Status Register 85: ADV_TRG_STAT3 (offset 0x0154) 
   unsigned int GetAdvTrgStat3() {
      return BitExtractStatus(WD2_ADV_TRG_STAT_3_REG, WD2_ADV_TRG_STAT_3_MASK, WD2_ADV_TRG_STAT_3_OFS);
   };


   // Status Register 86: ADV_TRG_STAT4 (offset 0x0158) 
   unsigned int GetAdvTrgStat4() {
      return BitExtractStatus(WD2_ADV_TRG_STAT_4_REG, WD2_ADV_TRG_STAT_4_MASK, WD2_ADV_TRG_STAT_4_OFS);
   };


   // Status Register 87: MAX_DRS_ADC_PKT_SAMPLES (offset 0x015C) 
   unsigned int GetMaxDrsAdcPktSamples() {
      return BitExtractStatus(WD2_MAX_DRS_ADC_PKT_SAMPLES_REG, WD2_MAX_DRS_ADC_PKT_SAMPLES_MASK, WD2_MAX_DRS_ADC_PKT_SAMPLES_OFS);
   };


   // Status Register 88: MAX_TDC_PKT_SAMPLES (offset 0x0160) 
   unsigned int GetMaxTdcPktSamples() {
      return BitExtractStatus(WD2_MAX_TDC_PKT_SAMPLES_REG, WD2_MAX_TDC_PKT_SAMPLES_MASK, WD2_MAX_TDC_PKT_SAMPLES_OFS);
   };


   // Status Register 89: MAX_TRG_PKT_SAMPLES (offset 0x0164) 
   unsigned int GetMaxTrgPktSamples() {
      return BitExtractStatus(WD2_MAX_TRG_PKT_SAMPLES_REG, WD2_MAX_TRG_PKT_SAMPLES_MASK, WD2_MAX_TRG_PKT_SAMPLES_OFS);
   };


   // Status Register 90: MAX_SCL_PKT_SAMPLES (offset 0x0168) 
   unsigned int GetMaxSclPktSamples() {
      return BitExtractStatus(WD2_MAX_SCL_PKT_SAMPLES_REG, WD2_MAX_SCL_PKT_SAMPLES_MASK, WD2_MAX_SCL_PKT_SAMPLES_OFS);
   };


   // Status Register 91: CLK_CTRL_MOD_FLAG (offset 0x016C) 
   unsigned int GetClkSelAndDrsClkDivMod() {
      return BitExtractStatus(WD2_CLK_SEL_AND_DRS_CLK_DIV_MOD_REG, WD2_CLK_SEL_AND_DRS_CLK_DIV_MOD_MASK, WD2_CLK_SEL_AND_DRS_CLK_DIV_MOD_OFS);
   };

   unsigned int GetExtClkFreqMod() {
      return BitExtractStatus(WD2_EXT_CLK_FREQ_MOD_REG, WD2_EXT_CLK_FREQ_MOD_MASK, WD2_EXT_CLK_FREQ_MOD_OFS);
   };

   unsigned int GetLocalClkFreqMod() {
      return BitExtractStatus(WD2_LOCAL_CLK_FREQ_MOD_REG, WD2_LOCAL_CLK_FREQ_MOD_MASK, WD2_LOCAL_CLK_FREQ_MOD_OFS);
   };


   // Status Register 92: DRS_MOD_FLAG (offset 0x0170) 
   unsigned int GetDrsCtrlMod() {
      return BitExtractStatus(WD2_DRS_CTRL_MOD_REG, WD2_DRS_CTRL_MOD_MASK, WD2_DRS_CTRL_MOD_OFS);
   };

   unsigned int GetDrsWsrMod() {
      return BitExtractStatus(WD2_DRS_WSR_MOD_REG, WD2_DRS_WSR_MOD_MASK, WD2_DRS_WSR_MOD_OFS);
   };

   unsigned int GetDrsWcrMod() {
      return BitExtractStatus(WD2_DRS_WCR_MOD_REG, WD2_DRS_WCR_MOD_MASK, WD2_DRS_WCR_MOD_OFS);
   };


   // Status Register 93: COM_PLD_SIZE_MOD_FLAG (offset 0x0174) 
   unsigned int GetComPldSizeMod() {
      return BitExtractStatus(WD2_COM_PLD_SIZE_MOD_REG, WD2_COM_PLD_SIZE_MOD_MASK, WD2_COM_PLD_SIZE_MOD_OFS);
   };


   // Status Register 94: ADC_SAMPLE_DIV_MOD_FLAG (offset 0x0178) 
   unsigned int GetAdcSampleDivMod() {
      return BitExtractStatus(WD2_ADC_SAMPLE_DIV_MOD_REG, WD2_ADC_SAMPLE_DIV_MOD_MASK, WD2_ADC_SAMPLE_DIV_MOD_OFS);
   };


   // Status Register 95: DAC_0_1_MOD_FLAG (offset 0x017C) 
   unsigned int GetDac0AMod() {
      return BitExtractStatus(WD2_DAC0_A_MOD_REG, WD2_DAC0_A_MOD_MASK, WD2_DAC0_A_MOD_OFS);
   };

   unsigned int GetDac0BMod() {
      return BitExtractStatus(WD2_DAC0_B_MOD_REG, WD2_DAC0_B_MOD_MASK, WD2_DAC0_B_MOD_OFS);
   };

   unsigned int GetDac0CMod() {
      return BitExtractStatus(WD2_DAC0_C_MOD_REG, WD2_DAC0_C_MOD_MASK, WD2_DAC0_C_MOD_OFS);
   };

   unsigned int GetDac0DMod() {
      return BitExtractStatus(WD2_DAC0_D_MOD_REG, WD2_DAC0_D_MOD_MASK, WD2_DAC0_D_MOD_OFS);
   };

   unsigned int GetDac0EMod() {
      return BitExtractStatus(WD2_DAC0_E_MOD_REG, WD2_DAC0_E_MOD_MASK, WD2_DAC0_E_MOD_OFS);
   };

   unsigned int GetDac0FMod() {
      return BitExtractStatus(WD2_DAC0_F_MOD_REG, WD2_DAC0_F_MOD_MASK, WD2_DAC0_F_MOD_OFS);
   };

   unsigned int GetDac0GMod() {
      return BitExtractStatus(WD2_DAC0_G_MOD_REG, WD2_DAC0_G_MOD_MASK, WD2_DAC0_G_MOD_OFS);
   };

   unsigned int GetDac0HMod() {
      return BitExtractStatus(WD2_DAC0_H_MOD_REG, WD2_DAC0_H_MOD_MASK, WD2_DAC0_H_MOD_OFS);
   };

   unsigned int GetDac1AMod() {
      return BitExtractStatus(WD2_DAC1_A_MOD_REG, WD2_DAC1_A_MOD_MASK, WD2_DAC1_A_MOD_OFS);
   };

   unsigned int GetDac1BMod() {
      return BitExtractStatus(WD2_DAC1_B_MOD_REG, WD2_DAC1_B_MOD_MASK, WD2_DAC1_B_MOD_OFS);
   };

   unsigned int GetDac1CMod() {
      return BitExtractStatus(WD2_DAC1_C_MOD_REG, WD2_DAC1_C_MOD_MASK, WD2_DAC1_C_MOD_OFS);
   };

   unsigned int GetDac1DMod() {
      return BitExtractStatus(WD2_DAC1_D_MOD_REG, WD2_DAC1_D_MOD_MASK, WD2_DAC1_D_MOD_OFS);
   };

   unsigned int GetDac1EMod() {
      return BitExtractStatus(WD2_DAC1_E_MOD_REG, WD2_DAC1_E_MOD_MASK, WD2_DAC1_E_MOD_OFS);
   };

   unsigned int GetDac1FMod() {
      return BitExtractStatus(WD2_DAC1_F_MOD_REG, WD2_DAC1_F_MOD_MASK, WD2_DAC1_F_MOD_OFS);
   };

   unsigned int GetDac1GMod() {
      return BitExtractStatus(WD2_DAC1_G_MOD_REG, WD2_DAC1_G_MOD_MASK, WD2_DAC1_G_MOD_OFS);
   };

   unsigned int GetDac1HMod() {
      return BitExtractStatus(WD2_DAC1_H_MOD_REG, WD2_DAC1_H_MOD_MASK, WD2_DAC1_H_MOD_OFS);
   };


   // Status Register 96: DAC_2_MOD_FLAG (offset 0x0180) 
   unsigned int GetDac2AMod() {
      return BitExtractStatus(WD2_DAC2_A_MOD_REG, WD2_DAC2_A_MOD_MASK, WD2_DAC2_A_MOD_OFS);
   };

   unsigned int GetDac2BMod() {
      return BitExtractStatus(WD2_DAC2_B_MOD_REG, WD2_DAC2_B_MOD_MASK, WD2_DAC2_B_MOD_OFS);
   };

   unsigned int GetDac2CMod() {
      return BitExtractStatus(WD2_DAC2_C_MOD_REG, WD2_DAC2_C_MOD_MASK, WD2_DAC2_C_MOD_OFS);
   };

   unsigned int GetDac2DMod() {
      return BitExtractStatus(WD2_DAC2_D_MOD_REG, WD2_DAC2_D_MOD_MASK, WD2_DAC2_D_MOD_OFS);
   };

   unsigned int GetDac2EMod() {
      return BitExtractStatus(WD2_DAC2_E_MOD_REG, WD2_DAC2_E_MOD_MASK, WD2_DAC2_E_MOD_OFS);
   };

   unsigned int GetDac2FMod() {
      return BitExtractStatus(WD2_DAC2_F_MOD_REG, WD2_DAC2_F_MOD_MASK, WD2_DAC2_F_MOD_OFS);
   };

   unsigned int GetDac2GMod() {
      return BitExtractStatus(WD2_DAC2_G_MOD_REG, WD2_DAC2_G_MOD_MASK, WD2_DAC2_G_MOD_OFS);
   };

   unsigned int GetDac2HMod() {
      return BitExtractStatus(WD2_DAC2_H_MOD_REG, WD2_DAC2_H_MOD_MASK, WD2_DAC2_H_MOD_OFS);
   };


   // Status Register 97: FE_0_15_MOD_FLAG (offset 0x0184) 
   unsigned int GetFe0Mod() {
      return BitExtractStatus(WD2_FE_0_MOD_REG, WD2_FE_0_MOD_MASK, WD2_FE_0_MOD_OFS);
   };

   unsigned int GetFe1Mod() {
      return BitExtractStatus(WD2_FE_1_MOD_REG, WD2_FE_1_MOD_MASK, WD2_FE_1_MOD_OFS);
   };

   unsigned int GetFe2Mod() {
      return BitExtractStatus(WD2_FE_2_MOD_REG, WD2_FE_2_MOD_MASK, WD2_FE_2_MOD_OFS);
   };

   unsigned int GetFe3Mod() {
      return BitExtractStatus(WD2_FE_3_MOD_REG, WD2_FE_3_MOD_MASK, WD2_FE_3_MOD_OFS);
   };

   unsigned int GetFe4Mod() {
      return BitExtractStatus(WD2_FE_4_MOD_REG, WD2_FE_4_MOD_MASK, WD2_FE_4_MOD_OFS);
   };

   unsigned int GetFe5Mod() {
      return BitExtractStatus(WD2_FE_5_MOD_REG, WD2_FE_5_MOD_MASK, WD2_FE_5_MOD_OFS);
   };

   unsigned int GetFe6Mod() {
      return BitExtractStatus(WD2_FE_6_MOD_REG, WD2_FE_6_MOD_MASK, WD2_FE_6_MOD_OFS);
   };

   unsigned int GetFe7Mod() {
      return BitExtractStatus(WD2_FE_7_MOD_REG, WD2_FE_7_MOD_MASK, WD2_FE_7_MOD_OFS);
   };

   unsigned int GetFe8Mod() {
      return BitExtractStatus(WD2_FE_8_MOD_REG, WD2_FE_8_MOD_MASK, WD2_FE_8_MOD_OFS);
   };

   unsigned int GetFe9Mod() {
      return BitExtractStatus(WD2_FE_9_MOD_REG, WD2_FE_9_MOD_MASK, WD2_FE_9_MOD_OFS);
   };

   unsigned int GetFe10Mod() {
      return BitExtractStatus(WD2_FE_10_MOD_REG, WD2_FE_10_MOD_MASK, WD2_FE_10_MOD_OFS);
   };

   unsigned int GetFe11Mod() {
      return BitExtractStatus(WD2_FE_11_MOD_REG, WD2_FE_11_MOD_MASK, WD2_FE_11_MOD_OFS);
   };

   unsigned int GetFe12Mod() {
      return BitExtractStatus(WD2_FE_12_MOD_REG, WD2_FE_12_MOD_MASK, WD2_FE_12_MOD_OFS);
   };

   unsigned int GetFe13Mod() {
      return BitExtractStatus(WD2_FE_13_MOD_REG, WD2_FE_13_MOD_MASK, WD2_FE_13_MOD_OFS);
   };

   unsigned int GetFe14Mod() {
      return BitExtractStatus(WD2_FE_14_MOD_REG, WD2_FE_14_MOD_MASK, WD2_FE_14_MOD_OFS);
   };

   unsigned int GetFe15Mod() {
      return BitExtractStatus(WD2_FE_15_MOD_REG, WD2_FE_15_MOD_MASK, WD2_FE_15_MOD_OFS);
   };


   // Status Register 98: HV_U_TARGET_0_7_MOD_FLAG (offset 0x0188) 
   unsigned int GetHvUTarget0Mod() {
      return BitExtractStatus(WD2_HV_U_TARGET_0_MOD_REG, WD2_HV_U_TARGET_0_MOD_MASK, WD2_HV_U_TARGET_0_MOD_OFS);
   };

   unsigned int GetHvUTarget1Mod() {
      return BitExtractStatus(WD2_HV_U_TARGET_1_MOD_REG, WD2_HV_U_TARGET_1_MOD_MASK, WD2_HV_U_TARGET_1_MOD_OFS);
   };

   unsigned int GetHvUTarget2Mod() {
      return BitExtractStatus(WD2_HV_U_TARGET_2_MOD_REG, WD2_HV_U_TARGET_2_MOD_MASK, WD2_HV_U_TARGET_2_MOD_OFS);
   };

   unsigned int GetHvUTarget3Mod() {
      return BitExtractStatus(WD2_HV_U_TARGET_3_MOD_REG, WD2_HV_U_TARGET_3_MOD_MASK, WD2_HV_U_TARGET_3_MOD_OFS);
   };

   unsigned int GetHvUTarget4Mod() {
      return BitExtractStatus(WD2_HV_U_TARGET_4_MOD_REG, WD2_HV_U_TARGET_4_MOD_MASK, WD2_HV_U_TARGET_4_MOD_OFS);
   };

   unsigned int GetHvUTarget5Mod() {
      return BitExtractStatus(WD2_HV_U_TARGET_5_MOD_REG, WD2_HV_U_TARGET_5_MOD_MASK, WD2_HV_U_TARGET_5_MOD_OFS);
   };

   unsigned int GetHvUTarget6Mod() {
      return BitExtractStatus(WD2_HV_U_TARGET_6_MOD_REG, WD2_HV_U_TARGET_6_MOD_MASK, WD2_HV_U_TARGET_6_MOD_OFS);
   };

   unsigned int GetHvUTarget7Mod() {
      return BitExtractStatus(WD2_HV_U_TARGET_7_MOD_REG, WD2_HV_U_TARGET_7_MOD_MASK, WD2_HV_U_TARGET_7_MOD_OFS);
   };


   // Status Register 99: HV_U_TARGET_8_15_MOD_FLAG (offset 0x018C) 
   unsigned int GetHvUTarget8Mod() {
      return BitExtractStatus(WD2_HV_U_TARGET_8_MOD_REG, WD2_HV_U_TARGET_8_MOD_MASK, WD2_HV_U_TARGET_8_MOD_OFS);
   };

   unsigned int GetHvUTarget9Mod() {
      return BitExtractStatus(WD2_HV_U_TARGET_9_MOD_REG, WD2_HV_U_TARGET_9_MOD_MASK, WD2_HV_U_TARGET_9_MOD_OFS);
   };

   unsigned int GetHvUTarget10Mod() {
      return BitExtractStatus(WD2_HV_U_TARGET_10_MOD_REG, WD2_HV_U_TARGET_10_MOD_MASK, WD2_HV_U_TARGET_10_MOD_OFS);
   };

   unsigned int GetHvUTarget11Mod() {
      return BitExtractStatus(WD2_HV_U_TARGET_11_MOD_REG, WD2_HV_U_TARGET_11_MOD_MASK, WD2_HV_U_TARGET_11_MOD_OFS);
   };

   unsigned int GetHvUTarget12Mod() {
      return BitExtractStatus(WD2_HV_U_TARGET_12_MOD_REG, WD2_HV_U_TARGET_12_MOD_MASK, WD2_HV_U_TARGET_12_MOD_OFS);
   };

   unsigned int GetHvUTarget13Mod() {
      return BitExtractStatus(WD2_HV_U_TARGET_13_MOD_REG, WD2_HV_U_TARGET_13_MOD_MASK, WD2_HV_U_TARGET_13_MOD_OFS);
   };

   unsigned int GetHvUTarget14Mod() {
      return BitExtractStatus(WD2_HV_U_TARGET_14_MOD_REG, WD2_HV_U_TARGET_14_MOD_MASK, WD2_HV_U_TARGET_14_MOD_OFS);
   };

   unsigned int GetHvUTarget15Mod() {
      return BitExtractStatus(WD2_HV_U_TARGET_15_MOD_REG, WD2_HV_U_TARGET_15_MOD_MASK, WD2_HV_U_TARGET_15_MOD_OFS);
   };


   // Status Register 100: HV_MOD_FLAG (offset 0x0190) 
   unsigned int GetHvRShuntMod() {
      return BitExtractStatus(WD2_HV_R_SHUNT_MOD_REG, WD2_HV_R_SHUNT_MOD_MASK, WD2_HV_R_SHUNT_MOD_OFS);
   };


   // Status Register 101: LMK_0_7_MOD_FLAG (offset 0x0194) 
   unsigned int GetLmk0Mod() {
      return BitExtractStatus(WD2_LMK_0_MOD_REG, WD2_LMK_0_MOD_MASK, WD2_LMK_0_MOD_OFS);
   };

   unsigned int GetLmk1Mod() {
      return BitExtractStatus(WD2_LMK_1_MOD_REG, WD2_LMK_1_MOD_MASK, WD2_LMK_1_MOD_OFS);
   };

   unsigned int GetLmk2Mod() {
      return BitExtractStatus(WD2_LMK_2_MOD_REG, WD2_LMK_2_MOD_MASK, WD2_LMK_2_MOD_OFS);
   };

   unsigned int GetLmk3Mod() {
      return BitExtractStatus(WD2_LMK_3_MOD_REG, WD2_LMK_3_MOD_MASK, WD2_LMK_3_MOD_OFS);
   };

   unsigned int GetLmk4Mod() {
      return BitExtractStatus(WD2_LMK_4_MOD_REG, WD2_LMK_4_MOD_MASK, WD2_LMK_4_MOD_OFS);
   };

   unsigned int GetLmk5Mod() {
      return BitExtractStatus(WD2_LMK_5_MOD_REG, WD2_LMK_5_MOD_MASK, WD2_LMK_5_MOD_OFS);
   };

   unsigned int GetLmk6Mod() {
      return BitExtractStatus(WD2_LMK_6_MOD_REG, WD2_LMK_6_MOD_MASK, WD2_LMK_6_MOD_OFS);
   };

   unsigned int GetLmk7Mod() {
      return BitExtractStatus(WD2_LMK_7_MOD_REG, WD2_LMK_7_MOD_MASK, WD2_LMK_7_MOD_OFS);
   };


   // Status Register 102: LMK_8_15_MOD_FLAG (offset 0x0198) 
   unsigned int GetLmk8Mod() {
      return BitExtractStatus(WD2_LMK_8_MOD_REG, WD2_LMK_8_MOD_MASK, WD2_LMK_8_MOD_OFS);
   };

   unsigned int GetLmk9Mod() {
      return BitExtractStatus(WD2_LMK_9_MOD_REG, WD2_LMK_9_MOD_MASK, WD2_LMK_9_MOD_OFS);
   };

   unsigned int GetLmk11Mod() {
      return BitExtractStatus(WD2_LMK_11_MOD_REG, WD2_LMK_11_MOD_MASK, WD2_LMK_11_MOD_OFS);
   };

   unsigned int GetLmk13Mod() {
      return BitExtractStatus(WD2_LMK_13_MOD_REG, WD2_LMK_13_MOD_MASK, WD2_LMK_13_MOD_OFS);
   };

   unsigned int GetLmk14Mod() {
      return BitExtractStatus(WD2_LMK_14_MOD_REG, WD2_LMK_14_MOD_MASK, WD2_LMK_14_MOD_OFS);
   };

   unsigned int GetLmk15Mod() {
      return BitExtractStatus(WD2_LMK_15_MOD_REG, WD2_LMK_15_MOD_MASK, WD2_LMK_15_MOD_OFS);
   };


   // Status Register 103: ADC_MOD_FLAG (offset 0x019C) 
   unsigned int GetAdcCfgIndTxMod() {
      return BitExtractStatus(WD2_ADC_CFG_IND_TX_MOD_REG, WD2_ADC_CFG_IND_TX_MOD_MASK, WD2_ADC_CFG_IND_TX_MOD_OFS);
   };

   unsigned int GetAdcPmClkEnhMod() {
      return BitExtractStatus(WD2_ADC_PM_CLK_ENH_MOD_REG, WD2_ADC_PM_CLK_ENH_MOD_MASK, WD2_ADC_PM_CLK_ENH_MOD_OFS);
   };

   unsigned int GetAdcTestOffsOmMod() {
      return BitExtractStatus(WD2_ADC_TEST_OFFS_OM_MOD_REG, WD2_ADC_TEST_OFFS_OM_MOD_MASK, WD2_ADC_TEST_OFFS_OM_MOD_OFS);
   };

   unsigned int GetAdcOutVrefMod() {
      return BitExtractStatus(WD2_ADC_OUT_VREF_MOD_REG, WD2_ADC_OUT_VREF_MOD_MASK, WD2_ADC_OUT_VREF_MOD_OFS);
   };

   unsigned int GetAdcUsrPattMod() {
      return BitExtractStatus(WD2_ADC_USR_PATT_MOD_REG, WD2_ADC_USR_PATT_MOD_MASK, WD2_ADC_USR_PATT_MOD_OFS);
   };

   unsigned int GetAdcSerResSrMod() {
      return BitExtractStatus(WD2_ADC_SER_RES_SR_MOD_REG, WD2_ADC_SER_RES_SR_MOD_MASK, WD2_ADC_SER_RES_SR_MOD_OFS);
   };

   unsigned int GetAdcUsrIoSyncMod() {
      return BitExtractStatus(WD2_ADC_USR_IO_SYNC_MOD_REG, WD2_ADC_USR_IO_SYNC_MOD_MASK, WD2_ADC_USR_IO_SYNC_MOD_OFS);
   };


   // Status Register 104: ADC_0_CH_MOD_FLAG (offset 0x01A0) 
   unsigned int GetAdc0ChAMod() {
      return BitExtractStatus(WD2_ADC_0_CH_A_MOD_REG, WD2_ADC_0_CH_A_MOD_MASK, WD2_ADC_0_CH_A_MOD_OFS);
   };

   unsigned int GetAdc0ChBMod() {
      return BitExtractStatus(WD2_ADC_0_CH_B_MOD_REG, WD2_ADC_0_CH_B_MOD_MASK, WD2_ADC_0_CH_B_MOD_OFS);
   };

   unsigned int GetAdc0ChCMod() {
      return BitExtractStatus(WD2_ADC_0_CH_C_MOD_REG, WD2_ADC_0_CH_C_MOD_MASK, WD2_ADC_0_CH_C_MOD_OFS);
   };

   unsigned int GetAdc0ChDMod() {
      return BitExtractStatus(WD2_ADC_0_CH_D_MOD_REG, WD2_ADC_0_CH_D_MOD_MASK, WD2_ADC_0_CH_D_MOD_OFS);
   };

   unsigned int GetAdc0ChEMod() {
      return BitExtractStatus(WD2_ADC_0_CH_E_MOD_REG, WD2_ADC_0_CH_E_MOD_MASK, WD2_ADC_0_CH_E_MOD_OFS);
   };

   unsigned int GetAdc0ChFMod() {
      return BitExtractStatus(WD2_ADC_0_CH_F_MOD_REG, WD2_ADC_0_CH_F_MOD_MASK, WD2_ADC_0_CH_F_MOD_OFS);
   };

   unsigned int GetAdc0ChGMod() {
      return BitExtractStatus(WD2_ADC_0_CH_G_MOD_REG, WD2_ADC_0_CH_G_MOD_MASK, WD2_ADC_0_CH_G_MOD_OFS);
   };

   unsigned int GetAdc0ChHMod() {
      return BitExtractStatus(WD2_ADC_0_CH_H_MOD_REG, WD2_ADC_0_CH_H_MOD_MASK, WD2_ADC_0_CH_H_MOD_OFS);
   };


   // Status Register 105: ADC_1_CH_MOD_FLAG (offset 0x01A4) 
   unsigned int GetAdc1ChAMod() {
      return BitExtractStatus(WD2_ADC_1_CH_A_MOD_REG, WD2_ADC_1_CH_A_MOD_MASK, WD2_ADC_1_CH_A_MOD_OFS);
   };

   unsigned int GetAdc1ChBMod() {
      return BitExtractStatus(WD2_ADC_1_CH_B_MOD_REG, WD2_ADC_1_CH_B_MOD_MASK, WD2_ADC_1_CH_B_MOD_OFS);
   };

   unsigned int GetAdc1ChCMod() {
      return BitExtractStatus(WD2_ADC_1_CH_C_MOD_REG, WD2_ADC_1_CH_C_MOD_MASK, WD2_ADC_1_CH_C_MOD_OFS);
   };

   unsigned int GetAdc1ChDMod() {
      return BitExtractStatus(WD2_ADC_1_CH_D_MOD_REG, WD2_ADC_1_CH_D_MOD_MASK, WD2_ADC_1_CH_D_MOD_OFS);
   };

   unsigned int GetAdc1ChEMod() {
      return BitExtractStatus(WD2_ADC_1_CH_E_MOD_REG, WD2_ADC_1_CH_E_MOD_MASK, WD2_ADC_1_CH_E_MOD_OFS);
   };

   unsigned int GetAdc1ChFMod() {
      return BitExtractStatus(WD2_ADC_1_CH_F_MOD_REG, WD2_ADC_1_CH_F_MOD_MASK, WD2_ADC_1_CH_F_MOD_OFS);
   };

   unsigned int GetAdc1ChGMod() {
      return BitExtractStatus(WD2_ADC_1_CH_G_MOD_REG, WD2_ADC_1_CH_G_MOD_MASK, WD2_ADC_1_CH_G_MOD_OFS);
   };

   unsigned int GetAdc1ChHMod() {
      return BitExtractStatus(WD2_ADC_1_CH_H_MOD_REG, WD2_ADC_1_CH_H_MOD_MASK, WD2_ADC_1_CH_H_MOD_OFS);
   };


   // Status Register 106: ADC_01_CLK_MOD_FLAG (offset 0x01A8) 
   unsigned int GetAdc1DcoMod() {
      return BitExtractStatus(WD2_ADC_1_DCO_MOD_REG, WD2_ADC_1_DCO_MOD_MASK, WD2_ADC_1_DCO_MOD_OFS);
   };

   unsigned int GetAdc0DcoMod() {
      return BitExtractStatus(WD2_ADC_0_DCO_MOD_REG, WD2_ADC_0_DCO_MOD_MASK, WD2_ADC_0_DCO_MOD_OFS);
   };

   unsigned int GetAdc1FcoMod() {
      return BitExtractStatus(WD2_ADC_1_FCO_MOD_REG, WD2_ADC_1_FCO_MOD_MASK, WD2_ADC_1_FCO_MOD_OFS);
   };

   unsigned int GetAdc0FcoMod() {
      return BitExtractStatus(WD2_ADC_0_FCO_MOD_REG, WD2_ADC_0_FCO_MOD_MASK, WD2_ADC_0_FCO_MOD_OFS);
   };


};

//--------------------------------------------------------------------

#endif /* defined(__wdbreg_h__) */

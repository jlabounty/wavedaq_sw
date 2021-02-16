/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WaveDream2
 *
 *  Author  :  schmid_e (Author of generation script)
 *  Created :  16.02.2021 14:30:28
 *
 *  Register Layout Version :  9
 *
 *  Description :  Register map definitions.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#include "register_map_wd2_v9.h"

#ifdef WD2_REGISTER_MAP_V9

#ifndef WD2_DONT_INCLUDE_REG_ACCESS_VARS

const wd2_reg_func_type  wd2_ctrl_reg_func_list[] = {
  { wd2_hw_reg         , 0 },   /* ctrl register 0: WDB_LOC */
  { wd2_hw_reg         , 0 },   /* ctrl register 1: CTRL */
  { wd2_hw_reg         , 0 },   /* ctrl register 2: CAL_CTRL */
  { wd2_hw_reg         , 0 },   /* ctrl register 3: CLK_CTRL */
  { wd2_hw_reg         , 0 },   /* ctrl register 4: DRS_CTRL */
  { wd2_hw_reg         , 0 },   /* ctrl register 5: COM_CTRL */
  { wd2_hw_reg         , 0 },   /* ctrl register 6: COM_PLD_SIZE */
  { wd2_hw_reg         , 0 },   /* ctrl register 7: DRS_CH_TX_EN */
  { wd2_hw_reg         , 0 },   /* ctrl register 8: ADC_CH_TX_EN */
  { wd2_hw_reg         , 0 },   /* ctrl register 9: TDC_CH_TX_EN */
  { wd2_hw_reg         , 0 },   /* ctrl register 10: DRS_TX_SAMPLES */
  { wd2_hw_reg         , 0 },   /* ctrl register 11: ADC_TX_SAMPLES */
  { wd2_hw_reg         , 0 },   /* ctrl register 12: TDC_TX_SAMPLES */
  { wd2_hw_reg         , 0 },   /* ctrl register 13: TRG_TX_SAMPLES */
  { wd2_hw_reg         , 0 },   /* ctrl register 14: ADC_SAMPLE_DIV */
  { wd2_hw_reg         , 0 },   /* ctrl register 15: ZERO_SUPR */
  { wd2_hw_reg         , 0 },   /* ctrl register 16: RST */
  { wd2_hw_reg         , 0 },   /* ctrl register 17: APLY_CFG */
  { wd2_hw_reg         , 0 },   /* ctrl register 18: DAC0_A_B */
  { wd2_hw_reg         , 0 },   /* ctrl register 19: DAC0_C_D */
  { wd2_hw_reg         , 0 },   /* ctrl register 20: DAC0_E_F */
  { wd2_hw_reg         , 0 },   /* ctrl register 21: DAC0_G_H */
  { wd2_hw_reg         , 0 },   /* ctrl register 22: DAC1_A_B */
  { wd2_hw_reg         , 0 },   /* ctrl register 23: DAC1_C_D */
  { wd2_hw_reg         , 0 },   /* ctrl register 24: DAC1_E_F */
  { wd2_hw_reg         , 0 },   /* ctrl register 25: DAC1_G_H */
  { wd2_hw_reg         , 0 },   /* ctrl register 26: DAC2_A_B */
  { wd2_hw_reg         , 0 },   /* ctrl register 27: DAC2_C_D */
  { wd2_hw_reg         , 0 },   /* ctrl register 28: DAC2_E_F */
  { wd2_hw_reg         , 0 },   /* ctrl register 29: DAC2_G_H */
  { wd2_hw_reg         , 0 },   /* ctrl register 30: FE_CFG_0_1 */
  { wd2_hw_reg         , 0 },   /* ctrl register 31: FE_CFG_2_3 */
  { wd2_hw_reg         , 0 },   /* ctrl register 32: FE_CFG_4_5 */
  { wd2_hw_reg         , 0 },   /* ctrl register 33: FE_CFG_6_7 */
  { wd2_hw_reg         , 0 },   /* ctrl register 34: FE_CFG_8_9 */
  { wd2_hw_reg         , 0 },   /* ctrl register 35: FE_CFG_10_11 */
  { wd2_hw_reg         , 0 },   /* ctrl register 36: FE_CFG_12_13 */
  { wd2_hw_reg         , 0 },   /* ctrl register 37: FE_CFG_14_15 */
  { wd2_hw_reg         , 0 },   /* ctrl register 38: HV_U_TARGET_0 */
  { wd2_hw_reg         , 0 },   /* ctrl register 39: HV_U_TARGET_1 */
  { wd2_hw_reg         , 0 },   /* ctrl register 40: HV_U_TARGET_2 */
  { wd2_hw_reg         , 0 },   /* ctrl register 41: HV_U_TARGET_3 */
  { wd2_hw_reg         , 0 },   /* ctrl register 42: HV_U_TARGET_4 */
  { wd2_hw_reg         , 0 },   /* ctrl register 43: HV_U_TARGET_5 */
  { wd2_hw_reg         , 0 },   /* ctrl register 44: HV_U_TARGET_6 */
  { wd2_hw_reg         , 0 },   /* ctrl register 45: HV_U_TARGET_7 */
  { wd2_hw_reg         , 0 },   /* ctrl register 46: HV_U_TARGET_8 */
  { wd2_hw_reg         , 0 },   /* ctrl register 47: HV_U_TARGET_9 */
  { wd2_hw_reg         , 0 },   /* ctrl register 48: HV_U_TARGET_10 */
  { wd2_hw_reg         , 0 },   /* ctrl register 49: HV_U_TARGET_11 */
  { wd2_hw_reg         , 0 },   /* ctrl register 50: HV_U_TARGET_12 */
  { wd2_hw_reg         , 0 },   /* ctrl register 51: HV_U_TARGET_13 */
  { wd2_hw_reg         , 0 },   /* ctrl register 52: HV_U_TARGET_14 */
  { wd2_hw_reg         , 0 },   /* ctrl register 53: HV_U_TARGET_15 */
  { wd2_hw_reg         , 0 },   /* ctrl register 54: HV_R_SHUNT */
  { wd2_hw_reg         , 0 },   /* ctrl register 55: LMK_0 */
  { wd2_hw_reg         , 0 },   /* ctrl register 56: LMK_1 */
  { wd2_hw_reg         , 0 },   /* ctrl register 57: LMK_2 */
  { wd2_hw_reg         , 0 },   /* ctrl register 58: LMK_3 */
  { wd2_hw_reg         , 0 },   /* ctrl register 59: LMK_4 */
  { wd2_hw_reg         , 0 },   /* ctrl register 60: LMK_5 */
  { wd2_hw_reg         , 0 },   /* ctrl register 61: LMK_6 */
  { wd2_hw_reg         , 0 },   /* ctrl register 62: LMK_7 */
  { wd2_hw_reg         , 0 },   /* ctrl register 63: LMK_8 */
  { wd2_hw_reg         , 0 },   /* ctrl register 64: LMK_9 */
  { wd2_hw_reg         , 0 },   /* ctrl register 65: LMK_11 */
  { wd2_hw_reg         , 0 },   /* ctrl register 66: LMK_13 */
  { wd2_hw_reg         , 0 },   /* ctrl register 67: LMK_14 */
  { wd2_hw_reg         , 0 },   /* ctrl register 68: LMK_15 */
  { wd2_reg_adc_0_1458 , 0 },   /* ctrl register 69: ADC_0_CFG_1458 */
  { wd2_reg_adc_0_2367 , 0 },   /* ctrl register 70: ADC_0_CFG_2367 */
  { wd2_reg_adc_1_1458 , 0 },   /* ctrl register 71: ADC_1_CFG_1458 */
  { wd2_reg_adc_1_2367 , 0 },   /* ctrl register 72: ADC_1_CFG_2367 */
  { wd2_hw_reg         , 0 },   /* ctrl register 73: TRG_CFG */
  { wd2_hw_reg         , 0 },   /* ctrl register 74: TRG_SRC_POL */
  { wd2_hw_reg         , 0 },   /* ctrl register 75: TRG_AUTO_PERIOD */
  { wd2_hw_reg         , 0 },   /* ctrl register 76: TRG_PTRN_EN */
  { wd2_hw_reg         , 0 },   /* ctrl register 77: TRG_SRC_EN_PTRN0 */
  { wd2_hw_reg         , 0 },   /* ctrl register 78: TRG_STATE_PTRN0 */
  { wd2_hw_reg         , 0 },   /* ctrl register 79: TRG_SRC_EN_PTRN1 */
  { wd2_hw_reg         , 0 },   /* ctrl register 80: TRG_STATE_PTRN1 */
  { wd2_hw_reg         , 0 },   /* ctrl register 81: TRG_SRC_EN_PTRN2 */
  { wd2_hw_reg         , 0 },   /* ctrl register 82: TRG_STATE_PTRN2 */
  { wd2_hw_reg         , 0 },   /* ctrl register 83: TRG_SRC_EN_PTRN3 */
  { wd2_hw_reg         , 0 },   /* ctrl register 84: TRG_STATE_PTRN3 */
  { wd2_hw_reg         , 0 },   /* ctrl register 85: TRG_SRC_EN_PTRN4 */
  { wd2_hw_reg         , 0 },   /* ctrl register 86: TRG_STATE_PTRN4 */
  { wd2_hw_reg         , 0 },   /* ctrl register 87: TRG_SRC_EN_PTRN5 */
  { wd2_hw_reg         , 0 },   /* ctrl register 88: TRG_STATE_PTRN5 */
  { wd2_hw_reg         , 0 },   /* ctrl register 89: TRG_SRC_EN_PTRN6 */
  { wd2_hw_reg         , 0 },   /* ctrl register 90: TRG_STATE_PTRN6 */
  { wd2_hw_reg         , 0 },   /* ctrl register 91: TRG_SRC_EN_PTRN7 */
  { wd2_hw_reg         , 0 },   /* ctrl register 92: TRG_STATE_PTRN7 */
  { wd2_hw_reg         , 0 },   /* ctrl register 93: TRG_SRC_EN_PTRN8 */
  { wd2_hw_reg         , 0 },   /* ctrl register 94: TRG_STATE_PTRN8 */
  { wd2_hw_reg         , 0 },   /* ctrl register 95: TRG_SRC_EN_PTRN9 */
  { wd2_hw_reg         , 0 },   /* ctrl register 96: TRG_STATE_PTRN9 */
  { wd2_hw_reg         , 0 },   /* ctrl register 97: TRG_SRC_EN_PTRN10 */
  { wd2_hw_reg         , 0 },   /* ctrl register 98: TRG_STATE_PTRN10 */
  { wd2_hw_reg         , 0 },   /* ctrl register 99: TRG_SRC_EN_PTRN11 */
  { wd2_hw_reg         , 0 },   /* ctrl register 100: TRG_STATE_PTRN11 */
  { wd2_hw_reg         , 0 },   /* ctrl register 101: TRG_SRC_EN_PTRN12 */
  { wd2_hw_reg         , 0 },   /* ctrl register 102: TRG_STATE_PTRN12 */
  { wd2_hw_reg         , 0 },   /* ctrl register 103: TRG_SRC_EN_PTRN13 */
  { wd2_hw_reg         , 0 },   /* ctrl register 104: TRG_STATE_PTRN13 */
  { wd2_hw_reg         , 0 },   /* ctrl register 105: TRG_SRC_EN_PTRN14 */
  { wd2_hw_reg         , 0 },   /* ctrl register 106: TRG_STATE_PTRN14 */
  { wd2_hw_reg         , 0 },   /* ctrl register 107: TRG_SRC_EN_PTRN15 */
  { wd2_hw_reg         , 0 },   /* ctrl register 108: TRG_STATE_PTRN15 */
  { wd2_hw_reg         , 0 },   /* ctrl register 109: TRG_SRC_EN_PTRN16 */
  { wd2_hw_reg         , 0 },   /* ctrl register 110: TRG_STATE_PTRN16 */
  { wd2_hw_reg         , 0 },   /* ctrl register 111: TRG_SRC_EN_PTRN17 */
  { wd2_hw_reg         , 0 },   /* ctrl register 112: TRG_STATE_PTRN17 */
  { wd2_hw_reg         , 0 },   /* ctrl register 113: TRG_SRC_EN_PTRN18 */
  { wd2_hw_reg         , 0 },   /* ctrl register 114: TRG_STATE_PTRN18 */
  { wd2_hw_reg         , 0 },   /* ctrl register 115: ADV_TRG_CTRL */
  { wd2_hw_reg         , 0 },   /* ctrl register 116: ADV_TRG_CH_CAL0 */
  { wd2_hw_reg         , 0 },   /* ctrl register 117: ADV_TRG_CH_CAL1 */
  { wd2_hw_reg         , 0 },   /* ctrl register 118: ADV_TRG_CH_CAL2 */
  { wd2_hw_reg         , 0 },   /* ctrl register 119: ADV_TRG_CH_CAL3 */
  { wd2_hw_reg         , 0 },   /* ctrl register 120: ADV_TRG_PED_CFG */
  { wd2_hw_reg         , 0 },   /* ctrl register 121: ADV_TRG_THR0 */
  { wd2_hw_reg         , 0 },   /* ctrl register 122: ADV_TRG_THR1 */
  { wd2_hw_reg         , 0 },   /* ctrl register 123: ADV_TRG_THR2 */
  { wd2_hw_reg         , 0 },   /* ctrl register 124: ADV_TRG_TX_CHK_WORD0 */
  { wd2_hw_reg         , 0 },   /* ctrl register 125: ADV_TRG_TX_CHK_WORD1 */
  { wd2_hw_reg         , 0 },   /* ctrl register 126: ADV_TRG_TDC_CH_MASK */
  { wd2_hw_reg         , 0 },   /* ctrl register 127: ADV_TRG_CFG12 */
  { wd2_hw_reg         , 0 },   /* ctrl register 128: ADV_TRG_CFG13 */
  { wd2_hw_reg         , 0 },   /* ctrl register 129: ADV_TRG_CFG14 */
  { wd2_hw_reg         , 0 },   /* ctrl register 130: ADV_TRG_CFG15 */
  { wd2_hw_reg         , 0 },   /* ctrl register 131: ADV_TRG_CFG16 */
  { wd2_hw_reg         , 0 },   /* ctrl register 132: ADV_TRG_CFG17 */
  { wd2_hw_reg         , 0 },   /* ctrl register 133: ADV_TRG_CFG18 */
  { wd2_hw_reg         , 0 },   /* ctrl register 134: ADV_TRG_CFG19 */
  { wd2_hw_reg         , 0 },   /* ctrl register 135: SET_TIME_LSB */
  { wd2_hw_reg         , 0 },   /* ctrl register 136: SET_TIME_MSB */
  { wd2_hw_reg         , 0 },   /* ctrl register 137: DBG_SIG_SEL */
  { wd2_hw_reg         , 0 }    /* stat register 88: LMK_8_15_MOD_FLAG */
};

const wd2_reg_func_type  wd2_stat_reg_func_list[] = {
  { wd2_hw_reg         , 0 },   /* ctrl register 0: WDB_LOC */
  { wd2_hw_reg         , 0 },   /* ctrl register 1: CTRL */
  { wd2_hw_reg         , 0 },   /* ctrl register 2: CAL_CTRL */
  { wd2_hw_reg         , 0 },   /* ctrl register 3: CLK_CTRL */
  { wd2_hw_reg         , 0 },   /* ctrl register 4: DRS_CTRL */
  { wd2_hw_reg         , 0 },   /* ctrl register 5: COM_CTRL */
  { wd2_hw_reg         , 0 },   /* ctrl register 6: COM_PLD_SIZE */
  { wd2_hw_reg         , 0 },   /* ctrl register 7: DRS_CH_TX_EN */
  { wd2_hw_reg         , 0 },   /* ctrl register 8: ADC_CH_TX_EN */
  { wd2_hw_reg         , 0 },   /* ctrl register 9: TDC_CH_TX_EN */
  { wd2_hw_reg         , 0 },   /* ctrl register 10: DRS_TX_SAMPLES */
  { wd2_hw_reg         , 0 },   /* ctrl register 11: ADC_TX_SAMPLES */
  { wd2_hw_reg         , 0 },   /* ctrl register 12: TDC_TX_SAMPLES */
  { wd2_hw_reg         , 0 },   /* ctrl register 13: TRG_TX_SAMPLES */
  { wd2_hw_reg         , 0 },   /* ctrl register 14: ADC_SAMPLE_DIV */
  { wd2_hw_reg         , 0 },   /* ctrl register 15: ZERO_SUPR */
  { wd2_hw_reg         , 0 },   /* ctrl register 16: RST */
  { wd2_hw_reg         , 0 },   /* ctrl register 17: APLY_CFG */
  { wd2_hw_reg         , 0 },   /* ctrl register 18: DAC0_A_B */
  { wd2_hw_reg         , 0 },   /* ctrl register 19: DAC0_C_D */
  { wd2_hw_reg         , 0 },   /* ctrl register 20: DAC0_E_F */
  { wd2_hw_reg         , 0 },   /* ctrl register 21: DAC0_G_H */
  { wd2_hw_reg         , 0 },   /* ctrl register 22: DAC1_A_B */
  { wd2_hw_reg         , 0 },   /* ctrl register 23: DAC1_C_D */
  { wd2_hw_reg         , 0 },   /* ctrl register 24: DAC1_E_F */
  { wd2_hw_reg         , 0 },   /* ctrl register 25: DAC1_G_H */
  { wd2_hw_reg         , 0 },   /* ctrl register 26: DAC2_A_B */
  { wd2_hw_reg         , 0 },   /* ctrl register 27: DAC2_C_D */
  { wd2_hw_reg         , 0 },   /* ctrl register 28: DAC2_E_F */
  { wd2_hw_reg         , 0 },   /* ctrl register 29: DAC2_G_H */
  { wd2_hw_reg         , 0 },   /* ctrl register 30: FE_CFG_0_1 */
  { wd2_hw_reg         , 0 },   /* ctrl register 31: FE_CFG_2_3 */
  { wd2_hw_reg         , 0 },   /* ctrl register 32: FE_CFG_4_5 */
  { wd2_hw_reg         , 0 },   /* ctrl register 33: FE_CFG_6_7 */
  { wd2_hw_reg         , 0 },   /* ctrl register 34: FE_CFG_8_9 */
  { wd2_hw_reg         , 0 },   /* ctrl register 35: FE_CFG_10_11 */
  { wd2_hw_reg         , 0 },   /* ctrl register 36: FE_CFG_12_13 */
  { wd2_hw_reg         , 0 },   /* ctrl register 37: FE_CFG_14_15 */
  { wd2_hw_reg         , 0 },   /* ctrl register 38: HV_U_TARGET_0 */
  { wd2_hw_reg         , 0 },   /* ctrl register 39: HV_U_TARGET_1 */
  { wd2_hw_reg         , 0 },   /* ctrl register 40: HV_U_TARGET_2 */
  { wd2_hw_reg         , 0 },   /* ctrl register 41: HV_U_TARGET_3 */
  { wd2_hw_reg         , 0 },   /* ctrl register 42: HV_U_TARGET_4 */
  { wd2_hw_reg         , 0 },   /* ctrl register 43: HV_U_TARGET_5 */
  { wd2_hw_reg         , 0 },   /* ctrl register 44: HV_U_TARGET_6 */
  { wd2_hw_reg         , 0 },   /* ctrl register 45: HV_U_TARGET_7 */
  { wd2_hw_reg         , 0 },   /* ctrl register 46: HV_U_TARGET_8 */
  { wd2_hw_reg         , 0 },   /* ctrl register 47: HV_U_TARGET_9 */
  { wd2_hw_reg         , 0 },   /* ctrl register 48: HV_U_TARGET_10 */
  { wd2_hw_reg         , 0 },   /* ctrl register 49: HV_U_TARGET_11 */
  { wd2_hw_reg         , 0 },   /* ctrl register 50: HV_U_TARGET_12 */
  { wd2_hw_reg         , 0 },   /* ctrl register 51: HV_U_TARGET_13 */
  { wd2_hw_reg         , 0 },   /* ctrl register 52: HV_U_TARGET_14 */
  { wd2_hw_reg         , 0 },   /* ctrl register 53: HV_U_TARGET_15 */
  { wd2_hw_reg         , 0 },   /* ctrl register 54: HV_R_SHUNT */
  { wd2_hw_reg         , 0 },   /* ctrl register 55: LMK_0 */
  { wd2_hw_reg         , 0 },   /* ctrl register 56: LMK_1 */
  { wd2_hw_reg         , 0 },   /* ctrl register 57: LMK_2 */
  { wd2_hw_reg         , 0 },   /* ctrl register 58: LMK_3 */
  { wd2_hw_reg         , 0 },   /* ctrl register 59: LMK_4 */
  { wd2_hw_reg         , 0 },   /* ctrl register 60: LMK_5 */
  { wd2_hw_reg         , 0 },   /* ctrl register 61: LMK_6 */
  { wd2_hw_reg         , 0 },   /* ctrl register 62: LMK_7 */
  { wd2_hw_reg         , 0 },   /* ctrl register 63: LMK_8 */
  { wd2_hw_reg         , 0 },   /* ctrl register 64: LMK_9 */
  { wd2_hw_reg         , 0 },   /* ctrl register 65: LMK_11 */
  { wd2_hw_reg         , 0 },   /* ctrl register 66: LMK_13 */
  { wd2_hw_reg         , 0 },   /* ctrl register 67: LMK_14 */
  { wd2_hw_reg         , 0 },   /* ctrl register 68: LMK_15 */
  { wd2_hw_reg         , 0 },   /* ctrl register 69: ADC_0_CFG_1458 */
  { wd2_hw_reg         , 0 },   /* ctrl register 70: ADC_0_CFG_2367 */
  { wd2_hw_reg         , 0 },   /* ctrl register 71: ADC_1_CFG_1458 */
  { wd2_hw_reg         , 0 },   /* ctrl register 72: ADC_1_CFG_2367 */
  { wd2_hw_reg         , 0 },   /* ctrl register 73: TRG_CFG */
  { wd2_hw_reg         , 0 },   /* ctrl register 74: TRG_SRC_POL */
  { wd2_hw_reg         , 0 },   /* ctrl register 75: TRG_AUTO_PERIOD */
  { wd2_hw_reg         , 0 },   /* ctrl register 76: TRG_PTRN_EN */
  { wd2_hw_reg         , 0 },   /* ctrl register 77: TRG_SRC_EN_PTRN0 */
  { wd2_hw_reg         , 0 },   /* ctrl register 78: TRG_STATE_PTRN0 */
  { wd2_hw_reg         , 0 },   /* ctrl register 79: TRG_SRC_EN_PTRN1 */
  { wd2_hw_reg         , 0 },   /* ctrl register 80: TRG_STATE_PTRN1 */
  { wd2_hw_reg         , 0 },   /* ctrl register 81: TRG_SRC_EN_PTRN2 */
  { wd2_hw_reg         , 0 },   /* ctrl register 82: TRG_STATE_PTRN2 */
  { wd2_hw_reg         , 0 },   /* ctrl register 83: TRG_SRC_EN_PTRN3 */
  { wd2_hw_reg         , 0 },   /* ctrl register 84: TRG_STATE_PTRN3 */
  { wd2_hw_reg         , 0 },   /* ctrl register 85: TRG_SRC_EN_PTRN4 */
  { wd2_hw_reg         , 0 },   /* ctrl register 86: TRG_STATE_PTRN4 */
  { wd2_hw_reg         , 0 },   /* ctrl register 87: TRG_SRC_EN_PTRN5 */
  { wd2_hw_reg         , 0 }    /* stat register 88: LMK_8_15_MOD_FLAG */
};

#endif /* WD2_DONT_INCLUDE_REG_ACCESS_VARS */

#ifndef WD2_DONT_INCLUDE_VARS

/******************************************************************************/
/* Register Mapping                                                           */
/******************************************************************************/

const wd2_reg_name_entry_type  wd2_reg_list[] = {
  { "WDB_LOC"                   , WD2_REG_WDB_LOC                   },
  { "CTRL"                      , WD2_REG_CTRL                      },
  { "CAL_CTRL"                  , WD2_REG_CAL_CTRL                  },
  { "CLK_CTRL"                  , WD2_REG_CLK_CTRL                  },
  { "DRS_CTRL"                  , WD2_REG_DRS_CTRL                  },
  { "COM_CTRL"                  , WD2_REG_COM_CTRL                  },
  { "COM_PLD_SIZE"              , WD2_REG_COM_PLD_SIZE              },
  { "DRS_CH_TX_EN"              , WD2_REG_DRS_CH_TX_EN              },
  { "ADC_CH_TX_EN"              , WD2_REG_ADC_CH_TX_EN              },
  { "TDC_CH_TX_EN"              , WD2_REG_TDC_CH_TX_EN              },
  { "DRS_TX_SAMPLES"            , WD2_REG_DRS_TX_SAMPLES            },
  { "ADC_TX_SAMPLES"            , WD2_REG_ADC_TX_SAMPLES            },
  { "TDC_TX_SAMPLES"            , WD2_REG_TDC_TX_SAMPLES            },
  { "TRG_TX_SAMPLES"            , WD2_REG_TRG_TX_SAMPLES            },
  { "ADC_SAMPLE_DIV"            , WD2_REG_ADC_SAMPLE_DIV            },
  { "ZERO_SUPR"                 , WD2_REG_ZERO_SUPR                 },
  { "RST"                       , WD2_REG_RST                       },
  { "APLY_CFG"                  , WD2_REG_APLY_CFG                  },
  { "DAC0_A_B"                  , WD2_REG_DAC0_A_B                  },
  { "DAC0_C_D"                  , WD2_REG_DAC0_C_D                  },
  { "DAC0_E_F"                  , WD2_REG_DAC0_E_F                  },
  { "DAC0_G_H"                  , WD2_REG_DAC0_G_H                  },
  { "DAC1_A_B"                  , WD2_REG_DAC1_A_B                  },
  { "DAC1_C_D"                  , WD2_REG_DAC1_C_D                  },
  { "DAC1_E_F"                  , WD2_REG_DAC1_E_F                  },
  { "DAC1_G_H"                  , WD2_REG_DAC1_G_H                  },
  { "DAC2_A_B"                  , WD2_REG_DAC2_A_B                  },
  { "DAC2_C_D"                  , WD2_REG_DAC2_C_D                  },
  { "DAC2_E_F"                  , WD2_REG_DAC2_E_F                  },
  { "DAC2_G_H"                  , WD2_REG_DAC2_G_H                  },
  { "FE_CFG_0_1"                , WD2_REG_FE_CFG_0_1                },
  { "FE_CFG_2_3"                , WD2_REG_FE_CFG_2_3                },
  { "FE_CFG_4_5"                , WD2_REG_FE_CFG_4_5                },
  { "FE_CFG_6_7"                , WD2_REG_FE_CFG_6_7                },
  { "FE_CFG_8_9"                , WD2_REG_FE_CFG_8_9                },
  { "FE_CFG_10_11"              , WD2_REG_FE_CFG_10_11              },
  { "FE_CFG_12_13"              , WD2_REG_FE_CFG_12_13              },
  { "FE_CFG_14_15"              , WD2_REG_FE_CFG_14_15              },
  { "HV_U_TARGET_0"             , WD2_REG_HV_U_TARGET_0             },
  { "HV_U_TARGET_1"             , WD2_REG_HV_U_TARGET_1             },
  { "HV_U_TARGET_2"             , WD2_REG_HV_U_TARGET_2             },
  { "HV_U_TARGET_3"             , WD2_REG_HV_U_TARGET_3             },
  { "HV_U_TARGET_4"             , WD2_REG_HV_U_TARGET_4             },
  { "HV_U_TARGET_5"             , WD2_REG_HV_U_TARGET_5             },
  { "HV_U_TARGET_6"             , WD2_REG_HV_U_TARGET_6             },
  { "HV_U_TARGET_7"             , WD2_REG_HV_U_TARGET_7             },
  { "HV_U_TARGET_8"             , WD2_REG_HV_U_TARGET_8             },
  { "HV_U_TARGET_9"             , WD2_REG_HV_U_TARGET_9             },
  { "HV_U_TARGET_10"            , WD2_REG_HV_U_TARGET_10            },
  { "HV_U_TARGET_11"            , WD2_REG_HV_U_TARGET_11            },
  { "HV_U_TARGET_12"            , WD2_REG_HV_U_TARGET_12            },
  { "HV_U_TARGET_13"            , WD2_REG_HV_U_TARGET_13            },
  { "HV_U_TARGET_14"            , WD2_REG_HV_U_TARGET_14            },
  { "HV_U_TARGET_15"            , WD2_REG_HV_U_TARGET_15            },
  { "HV_R_SHUNT"                , WD2_REG_HV_R_SHUNT                },
  { "LMK_0"                     , WD2_REG_LMK_0                     },
  { "LMK_1"                     , WD2_REG_LMK_1                     },
  { "LMK_2"                     , WD2_REG_LMK_2                     },
  { "LMK_3"                     , WD2_REG_LMK_3                     },
  { "LMK_4"                     , WD2_REG_LMK_4                     },
  { "LMK_5"                     , WD2_REG_LMK_5                     },
  { "LMK_6"                     , WD2_REG_LMK_6                     },
  { "LMK_7"                     , WD2_REG_LMK_7                     },
  { "LMK_8"                     , WD2_REG_LMK_8                     },
  { "LMK_9"                     , WD2_REG_LMK_9                     },
  { "LMK_11"                    , WD2_REG_LMK_11                    },
  { "LMK_13"                    , WD2_REG_LMK_13                    },
  { "LMK_14"                    , WD2_REG_LMK_14                    },
  { "LMK_15"                    , WD2_REG_LMK_15                    },
  { "ADC_0_CFG_1458"            , WD2_REG_ADC_0_CFG_1458            },
  { "ADC_0_CFG_2367"            , WD2_REG_ADC_0_CFG_2367            },
  { "ADC_1_CFG_1458"            , WD2_REG_ADC_1_CFG_1458            },
  { "ADC_1_CFG_2367"            , WD2_REG_ADC_1_CFG_2367            },
  { "TRG_CFG"                   , WD2_REG_TRG_CFG                   },
  { "TRG_SRC_POL"               , WD2_REG_TRG_SRC_POL               },
  { "TRG_AUTO_PERIOD"           , WD2_REG_TRG_AUTO_PERIOD           },
  { "TRG_PTRN_EN"               , WD2_REG_TRG_PTRN_EN               },
  { "TRG_SRC_EN_PTRN0"          , WD2_REG_TRG_SRC_EN_PTRN0          },
  { "TRG_STATE_PTRN0"           , WD2_REG_TRG_STATE_PTRN0           },
  { "TRG_SRC_EN_PTRN1"          , WD2_REG_TRG_SRC_EN_PTRN1          },
  { "TRG_STATE_PTRN1"           , WD2_REG_TRG_STATE_PTRN1           },
  { "TRG_SRC_EN_PTRN2"          , WD2_REG_TRG_SRC_EN_PTRN2          },
  { "TRG_STATE_PTRN2"           , WD2_REG_TRG_STATE_PTRN2           },
  { "TRG_SRC_EN_PTRN3"          , WD2_REG_TRG_SRC_EN_PTRN3          },
  { "TRG_STATE_PTRN3"           , WD2_REG_TRG_STATE_PTRN3           },
  { "TRG_SRC_EN_PTRN4"          , WD2_REG_TRG_SRC_EN_PTRN4          },
  { "TRG_STATE_PTRN4"           , WD2_REG_TRG_STATE_PTRN4           },
  { "TRG_SRC_EN_PTRN5"          , WD2_REG_TRG_SRC_EN_PTRN5          },
  { "TRG_STATE_PTRN5"           , WD2_REG_TRG_STATE_PTRN5           },
  { "TRG_SRC_EN_PTRN6"          , WD2_REG_TRG_SRC_EN_PTRN6          },
  { "TRG_STATE_PTRN6"           , WD2_REG_TRG_STATE_PTRN6           },
  { "TRG_SRC_EN_PTRN7"          , WD2_REG_TRG_SRC_EN_PTRN7          },
  { "TRG_STATE_PTRN7"           , WD2_REG_TRG_STATE_PTRN7           },
  { "TRG_SRC_EN_PTRN8"          , WD2_REG_TRG_SRC_EN_PTRN8          },
  { "TRG_STATE_PTRN8"           , WD2_REG_TRG_STATE_PTRN8           },
  { "TRG_SRC_EN_PTRN9"          , WD2_REG_TRG_SRC_EN_PTRN9          },
  { "TRG_STATE_PTRN9"           , WD2_REG_TRG_STATE_PTRN9           },
  { "TRG_SRC_EN_PTRN10"         , WD2_REG_TRG_SRC_EN_PTRN10         },
  { "TRG_STATE_PTRN10"          , WD2_REG_TRG_STATE_PTRN10          },
  { "TRG_SRC_EN_PTRN11"         , WD2_REG_TRG_SRC_EN_PTRN11         },
  { "TRG_STATE_PTRN11"          , WD2_REG_TRG_STATE_PTRN11          },
  { "TRG_SRC_EN_PTRN12"         , WD2_REG_TRG_SRC_EN_PTRN12         },
  { "TRG_STATE_PTRN12"          , WD2_REG_TRG_STATE_PTRN12          },
  { "TRG_SRC_EN_PTRN13"         , WD2_REG_TRG_SRC_EN_PTRN13         },
  { "TRG_STATE_PTRN13"          , WD2_REG_TRG_STATE_PTRN13          },
  { "TRG_SRC_EN_PTRN14"         , WD2_REG_TRG_SRC_EN_PTRN14         },
  { "TRG_STATE_PTRN14"          , WD2_REG_TRG_STATE_PTRN14          },
  { "TRG_SRC_EN_PTRN15"         , WD2_REG_TRG_SRC_EN_PTRN15         },
  { "TRG_STATE_PTRN15"          , WD2_REG_TRG_STATE_PTRN15          },
  { "TRG_SRC_EN_PTRN16"         , WD2_REG_TRG_SRC_EN_PTRN16         },
  { "TRG_STATE_PTRN16"          , WD2_REG_TRG_STATE_PTRN16          },
  { "TRG_SRC_EN_PTRN17"         , WD2_REG_TRG_SRC_EN_PTRN17         },
  { "TRG_STATE_PTRN17"          , WD2_REG_TRG_STATE_PTRN17          },
  { "TRG_SRC_EN_PTRN18"         , WD2_REG_TRG_SRC_EN_PTRN18         },
  { "TRG_STATE_PTRN18"          , WD2_REG_TRG_STATE_PTRN18          },
  { "ADV_TRG_CTRL"              , WD2_REG_ADV_TRG_CTRL              },
  { "ADV_TRG_CH_CAL0"           , WD2_REG_ADV_TRG_CH_CAL0           },
  { "ADV_TRG_CH_CAL1"           , WD2_REG_ADV_TRG_CH_CAL1           },
  { "ADV_TRG_CH_CAL2"           , WD2_REG_ADV_TRG_CH_CAL2           },
  { "ADV_TRG_CH_CAL3"           , WD2_REG_ADV_TRG_CH_CAL3           },
  { "ADV_TRG_PED_CFG"           , WD2_REG_ADV_TRG_PED_CFG           },
  { "ADV_TRG_THR0"              , WD2_REG_ADV_TRG_THR0              },
  { "ADV_TRG_THR1"              , WD2_REG_ADV_TRG_THR1              },
  { "ADV_TRG_THR2"              , WD2_REG_ADV_TRG_THR2              },
  { "ADV_TRG_TX_CHK_WORD0"      , WD2_REG_ADV_TRG_TX_CHK_WORD0      },
  { "ADV_TRG_TX_CHK_WORD1"      , WD2_REG_ADV_TRG_TX_CHK_WORD1      },
  { "ADV_TRG_TDC_CH_MASK"       , WD2_REG_ADV_TRG_TDC_CH_MASK       },
  { "ADV_TRG_CFG12"             , WD2_REG_ADV_TRG_CFG12             },
  { "ADV_TRG_CFG13"             , WD2_REG_ADV_TRG_CFG13             },
  { "ADV_TRG_CFG14"             , WD2_REG_ADV_TRG_CFG14             },
  { "ADV_TRG_CFG15"             , WD2_REG_ADV_TRG_CFG15             },
  { "ADV_TRG_CFG16"             , WD2_REG_ADV_TRG_CFG16             },
  { "ADV_TRG_CFG17"             , WD2_REG_ADV_TRG_CFG17             },
  { "ADV_TRG_CFG18"             , WD2_REG_ADV_TRG_CFG18             },
  { "ADV_TRG_CFG19"             , WD2_REG_ADV_TRG_CFG19             },
  { "SET_TIME_LSB"              , WD2_REG_SET_TIME_LSB              },
  { "SET_TIME_MSB"              , WD2_REG_SET_TIME_MSB              },
  { "DBG_SIG_SEL"               , WD2_REG_DBG_SIG_SEL               },
  { "CRC32_REG_BANK"            , WD2_REG_CRC32_REG_BANK            },
  { "HW_VER"                    , WD2_REG_HW_VER                    },
  { "REG_LAYOUT_VER"            , WD2_REG_REG_LAYOUT_VER            },
  { "FW_BUILD_DATE"             , WD2_REG_FW_BUILD_DATE             },
  { "FW_BUILD_TIME"             , WD2_REG_FW_BUILD_TIME             },
  { "SW_BUILD_DATE"             , WD2_REG_SW_BUILD_DATE             },
  { "SW_BUILD_TIME"             , WD2_REG_SW_BUILD_TIME             },
  { "FW_GIT_HASH_TAG"           , WD2_REG_FW_GIT_HASH_TAG           },
  { "SW_GIT_HASH_TAG"           , WD2_REG_SW_GIT_HASH_TAG           },
  { "PROT_VER"                  , WD2_REG_PROT_VER                  },
  { "SN"                        , WD2_REG_SN                        },
  { "STATUS"                    , WD2_REG_STATUS                    },
  { "PLL_LOCK"                  , WD2_REG_PLL_LOCK                  },
  { "DRS_STOP_CELL"             , WD2_REG_DRS_STOP_CELL             },
  { "DRS_STOP_WSR"              , WD2_REG_DRS_STOP_WSR              },
  { "DRS_SAMPLE_FREQ"           , WD2_REG_DRS_SAMPLE_FREQ           },
  { "ADC_SAMPLE_FREQ"           , WD2_REG_ADC_SAMPLE_FREQ           },
  { "TDC_SAMPLE_FREQ"           , WD2_REG_TDC_SAMPLE_FREQ           },
  { "HV_VER"                    , WD2_REG_HV_VER                    },
  { "HV_I_MEAS_0"               , WD2_REG_HV_I_MEAS_0               },
  { "HV_I_MEAS_1"               , WD2_REG_HV_I_MEAS_1               },
  { "HV_I_MEAS_2"               , WD2_REG_HV_I_MEAS_2               },
  { "HV_I_MEAS_3"               , WD2_REG_HV_I_MEAS_3               },
  { "HV_I_MEAS_4"               , WD2_REG_HV_I_MEAS_4               },
  { "HV_I_MEAS_5"               , WD2_REG_HV_I_MEAS_5               },
  { "HV_I_MEAS_6"               , WD2_REG_HV_I_MEAS_6               },
  { "HV_I_MEAS_7"               , WD2_REG_HV_I_MEAS_7               },
  { "HV_I_MEAS_8"               , WD2_REG_HV_I_MEAS_8               },
  { "HV_I_MEAS_9"               , WD2_REG_HV_I_MEAS_9               },
  { "HV_I_MEAS_10"              , WD2_REG_HV_I_MEAS_10              },
  { "HV_I_MEAS_11"              , WD2_REG_HV_I_MEAS_11              },
  { "HV_I_MEAS_12"              , WD2_REG_HV_I_MEAS_12              },
  { "HV_I_MEAS_13"              , WD2_REG_HV_I_MEAS_13              },
  { "HV_I_MEAS_14"              , WD2_REG_HV_I_MEAS_14              },
  { "HV_I_MEAS_15"              , WD2_REG_HV_I_MEAS_15              },
  { "HV_U_BASE_MEAS"            , WD2_REG_HV_U_BASE_MEAS            },
  { "HV_TEMP_0"                 , WD2_REG_HV_TEMP_0                 },
  { "HV_TEMP_1"                 , WD2_REG_HV_TEMP_1                 },
  { "HV_TEMP_2"                 , WD2_REG_HV_TEMP_2                 },
  { "HV_TEMP_3"                 , WD2_REG_HV_TEMP_3                 },
  { "SCALER_0"                  , WD2_REG_SCALER_0                  },
  { "SCALER_1"                  , WD2_REG_SCALER_1                  },
  { "SCALER_2"                  , WD2_REG_SCALER_2                  },
  { "SCALER_3"                  , WD2_REG_SCALER_3                  },
  { "SCALER_4"                  , WD2_REG_SCALER_4                  },
  { "SCALER_5"                  , WD2_REG_SCALER_5                  },
  { "SCALER_6"                  , WD2_REG_SCALER_6                  },
  { "SCALER_7"                  , WD2_REG_SCALER_7                  },
  { "SCALER_8"                  , WD2_REG_SCALER_8                  },
  { "SCALER_9"                  , WD2_REG_SCALER_9                  },
  { "SCALER_10"                 , WD2_REG_SCALER_10                 },
  { "SCALER_11"                 , WD2_REG_SCALER_11                 },
  { "SCALER_12"                 , WD2_REG_SCALER_12                 },
  { "SCALER_13"                 , WD2_REG_SCALER_13                 },
  { "SCALER_14"                 , WD2_REG_SCALER_14                 },
  { "SCALER_15"                 , WD2_REG_SCALER_15                 },
  { "SCALER_PTRN_TRG"           , WD2_REG_SCALER_PTRN_TRG           },
  { "SCALER_EXT_TRG"            , WD2_REG_SCALER_EXT_TRG            },
  { "SCALER_EXT_CLK"            , WD2_REG_SCALER_EXT_CLK            },
  { "SCALER_TIME_STAMP_LSB"     , WD2_REG_SCALER_TIME_STAMP_LSB     },
  { "SCALER_TIME_STAMP_MSB"     , WD2_REG_SCALER_TIME_STAMP_MSB     },
  { "TIME_LSB"                  , WD2_REG_TIME_LSB                  },
  { "TIME_MSB"                  , WD2_REG_TIME_MSB                  },
  { "COMP_CH_STAT"              , WD2_REG_COMP_CH_STAT              },
  { "EVENT_TX_RATE"             , WD2_REG_EVENT_TX_RATE             },
  { "EVENT_NR"                  , WD2_REG_EVENT_NR                  },
  { "TRB_INFO_STAT"             , WD2_REG_TRB_INFO_STAT             },
  { "TRB_INFO_LSB"              , WD2_REG_TRB_INFO_LSB              },
  { "TRB_INFO_MSB"              , WD2_REG_TRB_INFO_MSB              },
  { "ADV_TRG_TRIG_CELL"         , WD2_REG_ADV_TRG_TRIG_CELL         },
  { "ADV_TRG_STAT1"             , WD2_REG_ADV_TRG_STAT1             },
  { "ADV_TRG_STAT2"             , WD2_REG_ADV_TRG_STAT2             },
  { "ADV_TRG_STAT3"             , WD2_REG_ADV_TRG_STAT3             },
  { "ADV_TRG_STAT4"             , WD2_REG_ADV_TRG_STAT4             },
  { "MAX_DRS_ADC_PKT_SAMPLES"   , WD2_REG_MAX_DRS_ADC_PKT_SAMPLES   },
  { "MAX_TDC_PKT_SAMPLES"       , WD2_REG_MAX_TDC_PKT_SAMPLES       },
  { "MAX_TRG_PKT_SAMPLES"       , WD2_REG_MAX_TRG_PKT_SAMPLES       },
  { "MAX_SCL_PKT_SAMPLES"       , WD2_REG_MAX_SCL_PKT_SAMPLES       },
  { "CLK_CTRL_MOD_FLAG"         , WD2_REG_CLK_CTRL_MOD_FLAG         },
  { "DRS_MOD_FLAG"              , WD2_REG_DRS_MOD_FLAG              },
  { "COM_PLD_SIZE_MOD_FLAG"     , WD2_REG_COM_PLD_SIZE_MOD_FLAG     },
  { "ADC_SAMPLE_DIV_MOD_FLAG"   , WD2_REG_ADC_SAMPLE_DIV_MOD_FLAG   },
  { "DAC_0_1_MOD_FLAG"          , WD2_REG_DAC_0_1_MOD_FLAG          },
  { "DAC_2_MOD_FLAG"            , WD2_REG_DAC_2_MOD_FLAG            },
  { "FE_0_15_MOD_FLAG"          , WD2_REG_FE_0_15_MOD_FLAG          },
  { "HV_U_TARGET_0_7_MOD_FLAG"  , WD2_REG_HV_U_TARGET_0_7_MOD_FLAG  },
  { "HV_U_TARGET_8_15_MOD_FLAG" , WD2_REG_HV_U_TARGET_8_15_MOD_FLAG },
  { "HV_MOD_FLAG"               , WD2_REG_HV_MOD_FLAG               },
  { "LMK_0_7_MOD_FLAG"          , WD2_REG_LMK_0_7_MOD_FLAG          },
  { "LMK_8_15_MOD_FLAG"         , WD2_REG_LMK_8_15_MOD_FLAG         },
  { (const char*)0              , 0                                 }
};

/******************************************************************************/
/* Bit Mapping                                                                */
/******************************************************************************/

const wd2_bit_group_entry_type  wd2_bit_group_list[] = {
  { "CRATE_ID"                      , WD2_CRATE_ID_REG                      , WD2_CRATE_ID_MASK                      , WD2_CRATE_ID_OFS                      },
  { "SLOT_ID"                       , WD2_SLOT_ID_REG                       , WD2_SLOT_ID_MASK                       , WD2_SLOT_ID_OFS                       },
  { "VALID_DELAY_ADC"               , WD2_VALID_DELAY_ADC_REG               , WD2_VALID_DELAY_ADC_MASK               , WD2_VALID_DELAY_ADC_OFS               },
  { "DAQ_DATA_PHASE"                , WD2_DAQ_DATA_PHASE_REG                , WD2_DAQ_DATA_PHASE_MASK                , WD2_DAQ_DATA_PHASE_OFS                },
  { "FE_POWER"                      , WD2_FE_POWER_REG                      , WD2_FE_POWER_MASK                      , WD2_FE_POWER_OFS                      },
  { "DRS_CLR_RSR_AFTER_RO"          , WD2_DRS_CLR_RSR_AFTER_RO_REG          , WD2_DRS_CLR_RSR_AFTER_RO_MASK          , WD2_DRS_CLR_RSR_AFTER_RO_OFS          },
  { "COMP_POWER_EN"                 , WD2_COMP_POWER_EN_REG                 , WD2_COMP_POWER_EN_MASK                 , WD2_COMP_POWER_EN_OFS                 },
  { "DRS_READOUT_MODE"              , WD2_DRS_READOUT_MODE_REG              , WD2_DRS_READOUT_MODE_MASK              , WD2_DRS_READOUT_MODE_OFS              },
  { "DRS_WAVE_CONTINUOUS"           , WD2_DRS_WAVE_CONTINUOUS_REG           , WD2_DRS_WAVE_CONTINUOUS_MASK           , WD2_DRS_WAVE_CONTINUOUS_OFS           },
  { "DRS_CONFIGURE"                 , WD2_DRS_CONFIGURE_REG                 , WD2_DRS_CONFIGURE_MASK                 , WD2_DRS_CONFIGURE_OFS                 },
  { "DAQ_SOFT_TRIGGER"              , WD2_DAQ_SOFT_TRIGGER_REG              , WD2_DAQ_SOFT_TRIGGER_MASK              , WD2_DAQ_SOFT_TRIGGER_OFS              },
  { "DAQ_AUTO"                      , WD2_DAQ_AUTO_REG                      , WD2_DAQ_AUTO_MASK                      , WD2_DAQ_AUTO_OFS                      },
  { "DAQ_NORMAL"                    , WD2_DAQ_NORMAL_REG                    , WD2_DAQ_NORMAL_MASK                    , WD2_DAQ_NORMAL_OFS                    },
  { "DAQ_SINGLE"                    , WD2_DAQ_SINGLE_REG                    , WD2_DAQ_SINGLE_MASK                    , WD2_DAQ_SINGLE_OFS                    },
  { "DRS_0_TIMING_REF_SEL"          , WD2_DRS_0_TIMING_REF_SEL_REG          , WD2_DRS_0_TIMING_REF_SEL_MASK          , WD2_DRS_0_TIMING_REF_SEL_OFS          },
  { "DRS_1_TIMING_REF_SEL"          , WD2_DRS_1_TIMING_REF_SEL_REG          , WD2_DRS_1_TIMING_REF_SEL_MASK          , WD2_DRS_1_TIMING_REF_SEL_OFS          },
  { "CALIB_BUFFER_EN"               , WD2_CALIB_BUFFER_EN_REG               , WD2_CALIB_BUFFER_EN_MASK               , WD2_CALIB_BUFFER_EN_OFS               },
  { "TIMING_CALIB_SIGNAL_EN"        , WD2_TIMING_CALIB_SIGNAL_EN_REG        , WD2_TIMING_CALIB_SIGNAL_EN_MASK        , WD2_TIMING_CALIB_SIGNAL_EN_OFS        },
  { "TRIG_DAQ_CLK_CAL_CHK"          , WD2_TRIG_DAQ_CLK_CAL_CHK_REG          , WD2_TRIG_DAQ_CLK_CAL_CHK_MASK          , WD2_TRIG_DAQ_CLK_CAL_CHK_OFS          },
  { "DAQ_CLK_SRC_SEL"               , WD2_DAQ_CLK_SRC_SEL_REG               , WD2_DAQ_CLK_SRC_SEL_MASK               , WD2_DAQ_CLK_SRC_SEL_OFS               },
  { "EXT_CLK_IN_SEL"                , WD2_EXT_CLK_IN_SEL_REG                , WD2_EXT_CLK_IN_SEL_MASK                , WD2_EXT_CLK_IN_SEL_OFS                },
  { "EXT_CLK_FREQ"                  , WD2_EXT_CLK_FREQ_REG                  , WD2_EXT_CLK_FREQ_MASK                  , WD2_EXT_CLK_FREQ_OFS                  },
  { "LOCAL_CLK_FREQ"                , WD2_LOCAL_CLK_FREQ_REG                , WD2_LOCAL_CLK_FREQ_MASK                , WD2_LOCAL_CLK_FREQ_OFS                },
  { "DRS_WSRLOOP"                   , WD2_DRS_WSRLOOP_REG                   , WD2_DRS_WSRLOOP_MASK                   , WD2_DRS_WSRLOOP_OFS                   },
  { "DRS_PLLEN"                     , WD2_DRS_PLLEN_REG                     , WD2_DRS_PLLEN_MASK                     , WD2_DRS_PLLEN_OFS                     },
  { "DRS_DMODE"                     , WD2_DRS_DMODE_REG                     , WD2_DRS_DMODE_MASK                     , WD2_DRS_DMODE_OFS                     },
  { "DRS_WSR"                       , WD2_DRS_WSR_REG                       , WD2_DRS_WSR_MASK                       , WD2_DRS_WSR_OFS                       },
  { "DRS_WCR"                       , WD2_DRS_WCR_REG                       , WD2_DRS_WCR_MASK                       , WD2_DRS_WCR_OFS                       },
  { "DCB_SERDES_TRAIN"              , WD2_DCB_SERDES_TRAIN_REG              , WD2_DCB_SERDES_TRAIN_MASK              , WD2_DCB_SERDES_TRAIN_OFS              },
  { "TCB_SERDES_TRAIN"              , WD2_TCB_SERDES_TRAIN_REG              , WD2_TCB_SERDES_TRAIN_MASK              , WD2_TCB_SERDES_TRAIN_OFS              },
  { "TRG_TX_EN"                     , WD2_TRG_TX_EN_REG                     , WD2_TRG_TX_EN_MASK                     , WD2_TRG_TX_EN_OFS                     },
  { "SCL_TX_EN"                     , WD2_SCL_TX_EN_REG                     , WD2_SCL_TX_EN_MASK                     , WD2_SCL_TX_EN_OFS                     },
  { "SERDES_COM_EN"                 , WD2_SERDES_COM_EN_REG                 , WD2_SERDES_COM_EN_MASK                 , WD2_SERDES_COM_EN_OFS                 },
  { "ETH_COM_EN"                    , WD2_ETH_COM_EN_REG                    , WD2_ETH_COM_EN_MASK                    , WD2_ETH_COM_EN_OFS                    },
  { "INTER_PKG_DELAY"               , WD2_INTER_PKG_DELAY_REG               , WD2_INTER_PKG_DELAY_MASK               , WD2_INTER_PKG_DELAY_OFS               },
  { "FIRST_PKG_DLY"                 , WD2_FIRST_PKG_DLY_REG                 , WD2_FIRST_PKG_DLY_MASK                 , WD2_FIRST_PKG_DLY_OFS                 },
  { "COM_PLD_SIZE"                  , WD2_COM_PLD_SIZE_REG                  , WD2_COM_PLD_SIZE_MASK                  , WD2_COM_PLD_SIZE_OFS                  },
  { "DRS_CH_TX_EN"                  , WD2_DRS_CH_TX_EN_REG                  , WD2_DRS_CH_TX_EN_MASK                  , WD2_DRS_CH_TX_EN_OFS                  },
  { "ADC_CH_TX_EN"                  , WD2_ADC_CH_TX_EN_REG                  , WD2_ADC_CH_TX_EN_MASK                  , WD2_ADC_CH_TX_EN_OFS                  },
  { "TDC_CH_TX_EN"                  , WD2_TDC_CH_TX_EN_REG                  , WD2_TDC_CH_TX_EN_MASK                  , WD2_TDC_CH_TX_EN_OFS                  },
  { "DRS_TX_SAMPLES"                , WD2_DRS_TX_SAMPLES_REG                , WD2_DRS_TX_SAMPLES_MASK                , WD2_DRS_TX_SAMPLES_OFS                },
  { "ADC_TX_SAMPLES"                , WD2_ADC_TX_SAMPLES_REG                , WD2_ADC_TX_SAMPLES_MASK                , WD2_ADC_TX_SAMPLES_OFS                },
  { "TDC_TX_SAMPLES"                , WD2_TDC_TX_SAMPLES_REG                , WD2_TDC_TX_SAMPLES_MASK                , WD2_TDC_TX_SAMPLES_OFS                },
  { "TRG_TX_SAMPLES"                , WD2_TRG_TX_SAMPLES_REG                , WD2_TRG_TX_SAMPLES_MASK                , WD2_TRG_TX_SAMPLES_OFS                },
  { "ADC_SAMPLE_DIV"                , WD2_ADC_SAMPLE_DIV_REG                , WD2_ADC_SAMPLE_DIV_MASK                , WD2_ADC_SAMPLE_DIV_OFS                },
  { "ZERO_SUPR_EN"                  , WD2_ZERO_SUPR_EN_REG                  , WD2_ZERO_SUPR_EN_MASK                  , WD2_ZERO_SUPR_EN_OFS                  },
  { "ZERO_SUPR_WINDOW"              , WD2_ZERO_SUPR_WINDOW_REG              , WD2_ZERO_SUPR_WINDOW_MASK              , WD2_ZERO_SUPR_WINDOW_OFS              },
  { "DAQ_PLL_RST"                   , WD2_DAQ_PLL_RST_REG                   , WD2_DAQ_PLL_RST_MASK                   , WD2_DAQ_PLL_RST_OFS                   },
  { "DCB_OSERDES_PLL_RST"           , WD2_DCB_OSERDES_PLL_RST_REG           , WD2_DCB_OSERDES_PLL_RST_MASK           , WD2_DCB_OSERDES_PLL_RST_OFS           },
  { "TCB_OSERDES_PLL_RST"           , WD2_TCB_OSERDES_PLL_RST_REG           , WD2_TCB_OSERDES_PLL_RST_MASK           , WD2_TCB_OSERDES_PLL_RST_OFS           },
  { "DCB_OSERDES_IF_RST"            , WD2_DCB_OSERDES_IF_RST_REG            , WD2_DCB_OSERDES_IF_RST_MASK            , WD2_DCB_OSERDES_IF_RST_OFS            },
  { "TCB_OSERDES_IF_RST"            , WD2_TCB_OSERDES_IF_RST_REG            , WD2_TCB_OSERDES_IF_RST_MASK            , WD2_TCB_OSERDES_IF_RST_OFS            },
  { "SCALER_RST"                    , WD2_SCALER_RST_REG                    , WD2_SCALER_RST_MASK                    , WD2_SCALER_RST_OFS                    },
  { "TRB_PARITY_ERROR_COUNT_RST"    , WD2_TRB_PARITY_ERROR_COUNT_RST_REG    , WD2_TRB_PARITY_ERROR_COUNT_RST_MASK    , WD2_TRB_PARITY_ERROR_COUNT_RST_OFS    },
  { "LMK_SYNC_LOCAL"                , WD2_LMK_SYNC_LOCAL_REG                , WD2_LMK_SYNC_LOCAL_MASK                , WD2_LMK_SYNC_LOCAL_OFS                },
  { "ADC_RST"                       , WD2_ADC_RST_REG                       , WD2_ADC_RST_MASK                       , WD2_ADC_RST_OFS                       },
  { "ADC_IF_RST"                    , WD2_ADC_IF_RST_REG                    , WD2_ADC_IF_RST_MASK                    , WD2_ADC_IF_RST_OFS                    },
  { "DATA_LINK_IF_RST"              , WD2_DATA_LINK_IF_RST_REG              , WD2_DATA_LINK_IF_RST_MASK              , WD2_DATA_LINK_IF_RST_OFS              },
  { "WD_PKGR_RST"                   , WD2_WD_PKGR_RST_REG                   , WD2_WD_PKGR_RST_MASK                   , WD2_WD_PKGR_RST_OFS                   },
  { "EVENT_COUNTER_RST"             , WD2_EVENT_COUNTER_RST_REG             , WD2_EVENT_COUNTER_RST_MASK             , WD2_EVENT_COUNTER_RST_OFS             },
  { "DRS_CTRL_FSM_RST"              , WD2_DRS_CTRL_FSM_RST_REG              , WD2_DRS_CTRL_FSM_RST_MASK              , WD2_DRS_CTRL_FSM_RST_OFS              },
  { "RECONFIGURE_FPGA"              , WD2_RECONFIGURE_FPGA_REG              , WD2_RECONFIGURE_FPGA_MASK              , WD2_RECONFIGURE_FPGA_OFS              },
  { "APPLY_SETTINGS_ADC_SAMPLE_DIV" , WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_REG , WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_MASK , WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_OFS },
  { "APPLY_SETTINGS_MAX_PLD_SIZE"   , WD2_APPLY_SETTINGS_MAX_PLD_SIZE_REG   , WD2_APPLY_SETTINGS_MAX_PLD_SIZE_MASK   , WD2_APPLY_SETTINGS_MAX_PLD_SIZE_OFS   },
  { "APPLY_SETTINGS_HV"             , WD2_APPLY_SETTINGS_HV_REG             , WD2_APPLY_SETTINGS_HV_MASK             , WD2_APPLY_SETTINGS_HV_OFS             },
  { "APPLY_SETTINGS_DRS"            , WD2_APPLY_SETTINGS_DRS_REG            , WD2_APPLY_SETTINGS_DRS_MASK            , WD2_APPLY_SETTINGS_DRS_OFS            },
  { "APPLY_SETTINGS_DAC"            , WD2_APPLY_SETTINGS_DAC_REG            , WD2_APPLY_SETTINGS_DAC_MASK            , WD2_APPLY_SETTINGS_DAC_OFS            },
  { "APPLY_SETTINGS_FRONTEND"       , WD2_APPLY_SETTINGS_FRONTEND_REG       , WD2_APPLY_SETTINGS_FRONTEND_MASK       , WD2_APPLY_SETTINGS_FRONTEND_OFS       },
  { "APPLY_SETTINGS_CTRL"           , WD2_APPLY_SETTINGS_CTRL_REG           , WD2_APPLY_SETTINGS_CTRL_MASK           , WD2_APPLY_SETTINGS_CTRL_OFS           },
  { "APPLY_SETTINGS_ADC"            , WD2_APPLY_SETTINGS_ADC_REG            , WD2_APPLY_SETTINGS_ADC_MASK            , WD2_APPLY_SETTINGS_ADC_OFS            },
  { "APPLY_SETTINGS_LMK"            , WD2_APPLY_SETTINGS_LMK_REG            , WD2_APPLY_SETTINGS_LMK_MASK            , WD2_APPLY_SETTINGS_LMK_OFS            },
  { "DAC0_CH_A"                     , WD2_DAC0_CH_A_REG                     , WD2_DAC0_CH_A_MASK                     , WD2_DAC0_CH_A_OFS                     },
  { "DAC0_CH_B"                     , WD2_DAC0_CH_B_REG                     , WD2_DAC0_CH_B_MASK                     , WD2_DAC0_CH_B_OFS                     },
  { "DAC0_CH_C"                     , WD2_DAC0_CH_C_REG                     , WD2_DAC0_CH_C_MASK                     , WD2_DAC0_CH_C_OFS                     },
  { "DAC0_CH_D"                     , WD2_DAC0_CH_D_REG                     , WD2_DAC0_CH_D_MASK                     , WD2_DAC0_CH_D_OFS                     },
  { "DAC0_CH_E"                     , WD2_DAC0_CH_E_REG                     , WD2_DAC0_CH_E_MASK                     , WD2_DAC0_CH_E_OFS                     },
  { "DAC0_CH_F"                     , WD2_DAC0_CH_F_REG                     , WD2_DAC0_CH_F_MASK                     , WD2_DAC0_CH_F_OFS                     },
  { "DAC0_CH_G"                     , WD2_DAC0_CH_G_REG                     , WD2_DAC0_CH_G_MASK                     , WD2_DAC0_CH_G_OFS                     },
  { "DAC0_CH_H"                     , WD2_DAC0_CH_H_REG                     , WD2_DAC0_CH_H_MASK                     , WD2_DAC0_CH_H_OFS                     },
  { "DAC1_CH_A"                     , WD2_DAC1_CH_A_REG                     , WD2_DAC1_CH_A_MASK                     , WD2_DAC1_CH_A_OFS                     },
  { "DAC1_CH_B"                     , WD2_DAC1_CH_B_REG                     , WD2_DAC1_CH_B_MASK                     , WD2_DAC1_CH_B_OFS                     },
  { "DAC1_CH_C"                     , WD2_DAC1_CH_C_REG                     , WD2_DAC1_CH_C_MASK                     , WD2_DAC1_CH_C_OFS                     },
  { "DAC1_CH_D"                     , WD2_DAC1_CH_D_REG                     , WD2_DAC1_CH_D_MASK                     , WD2_DAC1_CH_D_OFS                     },
  { "DAC1_CH_E"                     , WD2_DAC1_CH_E_REG                     , WD2_DAC1_CH_E_MASK                     , WD2_DAC1_CH_E_OFS                     },
  { "DAC1_CH_F"                     , WD2_DAC1_CH_F_REG                     , WD2_DAC1_CH_F_MASK                     , WD2_DAC1_CH_F_OFS                     },
  { "DAC1_CH_G"                     , WD2_DAC1_CH_G_REG                     , WD2_DAC1_CH_G_MASK                     , WD2_DAC1_CH_G_OFS                     },
  { "DAC1_CH_H"                     , WD2_DAC1_CH_H_REG                     , WD2_DAC1_CH_H_MASK                     , WD2_DAC1_CH_H_OFS                     },
  { "DAC2_CH_A"                     , WD2_DAC2_CH_A_REG                     , WD2_DAC2_CH_A_MASK                     , WD2_DAC2_CH_A_OFS                     },
  { "DAC2_CH_B"                     , WD2_DAC2_CH_B_REG                     , WD2_DAC2_CH_B_MASK                     , WD2_DAC2_CH_B_OFS                     },
  { "DAC2_CH_C"                     , WD2_DAC2_CH_C_REG                     , WD2_DAC2_CH_C_MASK                     , WD2_DAC2_CH_C_OFS                     },
  { "DAC2_CH_D"                     , WD2_DAC2_CH_D_REG                     , WD2_DAC2_CH_D_MASK                     , WD2_DAC2_CH_D_OFS                     },
  { "DAC2_CH_E"                     , WD2_DAC2_CH_E_REG                     , WD2_DAC2_CH_E_MASK                     , WD2_DAC2_CH_E_OFS                     },
  { "DAC2_CH_F"                     , WD2_DAC2_CH_F_REG                     , WD2_DAC2_CH_F_MASK                     , WD2_DAC2_CH_F_OFS                     },
  { "DAC2_CH_G"                     , WD2_DAC2_CH_G_REG                     , WD2_DAC2_CH_G_MASK                     , WD2_DAC2_CH_G_OFS                     },
  { "DAC2_CH_H"                     , WD2_DAC2_CH_H_REG                     , WD2_DAC2_CH_H_MASK                     , WD2_DAC2_CH_H_OFS                     },
  { "FE0_PZC_EN"                    , WD2_FE0_PZC_EN_REG                    , WD2_FE0_PZC_EN_MASK                    , WD2_FE0_PZC_EN_OFS                    },
  { "FE0_AMPLIFIER2_COMP_EN"        , WD2_FE0_AMPLIFIER2_COMP_EN_REG        , WD2_FE0_AMPLIFIER2_COMP_EN_MASK        , WD2_FE0_AMPLIFIER2_COMP_EN_OFS        },
  { "FE0_AMPLIFIER2_EN"             , WD2_FE0_AMPLIFIER2_EN_REG             , WD2_FE0_AMPLIFIER2_EN_MASK             , WD2_FE0_AMPLIFIER2_EN_OFS             },
  { "FE0_AMPLIFIER1_COMP_EN"        , WD2_FE0_AMPLIFIER1_COMP_EN_REG        , WD2_FE0_AMPLIFIER1_COMP_EN_MASK        , WD2_FE0_AMPLIFIER1_COMP_EN_OFS        },
  { "FE0_AMPLIFIER1_EN"             , WD2_FE0_AMPLIFIER1_EN_REG             , WD2_FE0_AMPLIFIER1_EN_MASK             , WD2_FE0_AMPLIFIER1_EN_OFS             },
  { "FE0_ATTENUATION"               , WD2_FE0_ATTENUATION_REG               , WD2_FE0_ATTENUATION_MASK               , WD2_FE0_ATTENUATION_OFS               },
  { "FE0_MUX"                       , WD2_FE0_MUX_REG                       , WD2_FE0_MUX_MASK                       , WD2_FE0_MUX_OFS                       },
  { "FE1_PZC_EN"                    , WD2_FE1_PZC_EN_REG                    , WD2_FE1_PZC_EN_MASK                    , WD2_FE1_PZC_EN_OFS                    },
  { "FE1_AMPLIFIER2_COMP_EN"        , WD2_FE1_AMPLIFIER2_COMP_EN_REG        , WD2_FE1_AMPLIFIER2_COMP_EN_MASK        , WD2_FE1_AMPLIFIER2_COMP_EN_OFS        },
  { "FE1_AMPLIFIER2_EN"             , WD2_FE1_AMPLIFIER2_EN_REG             , WD2_FE1_AMPLIFIER2_EN_MASK             , WD2_FE1_AMPLIFIER2_EN_OFS             },
  { "FE1_AMPLIFIER1_COMP_EN"        , WD2_FE1_AMPLIFIER1_COMP_EN_REG        , WD2_FE1_AMPLIFIER1_COMP_EN_MASK        , WD2_FE1_AMPLIFIER1_COMP_EN_OFS        },
  { "FE1_AMPLIFIER1_EN"             , WD2_FE1_AMPLIFIER1_EN_REG             , WD2_FE1_AMPLIFIER1_EN_MASK             , WD2_FE1_AMPLIFIER1_EN_OFS             },
  { "FE1_ATTENUATION"               , WD2_FE1_ATTENUATION_REG               , WD2_FE1_ATTENUATION_MASK               , WD2_FE1_ATTENUATION_OFS               },
  { "FE1_MUX"                       , WD2_FE1_MUX_REG                       , WD2_FE1_MUX_MASK                       , WD2_FE1_MUX_OFS                       },
  { "FE2_PZC_EN"                    , WD2_FE2_PZC_EN_REG                    , WD2_FE2_PZC_EN_MASK                    , WD2_FE2_PZC_EN_OFS                    },
  { "FE2_AMPLIFIER2_COMP_EN"        , WD2_FE2_AMPLIFIER2_COMP_EN_REG        , WD2_FE2_AMPLIFIER2_COMP_EN_MASK        , WD2_FE2_AMPLIFIER2_COMP_EN_OFS        },
  { "FE2_AMPLIFIER2_EN"             , WD2_FE2_AMPLIFIER2_EN_REG             , WD2_FE2_AMPLIFIER2_EN_MASK             , WD2_FE2_AMPLIFIER2_EN_OFS             },
  { "FE2_AMPLIFIER1_COMP_EN"        , WD2_FE2_AMPLIFIER1_COMP_EN_REG        , WD2_FE2_AMPLIFIER1_COMP_EN_MASK        , WD2_FE2_AMPLIFIER1_COMP_EN_OFS        },
  { "FE2_AMPLIFIER1_EN"             , WD2_FE2_AMPLIFIER1_EN_REG             , WD2_FE2_AMPLIFIER1_EN_MASK             , WD2_FE2_AMPLIFIER1_EN_OFS             },
  { "FE2_ATTENUATION"               , WD2_FE2_ATTENUATION_REG               , WD2_FE2_ATTENUATION_MASK               , WD2_FE2_ATTENUATION_OFS               },
  { "FE2_MUX"                       , WD2_FE2_MUX_REG                       , WD2_FE2_MUX_MASK                       , WD2_FE2_MUX_OFS                       },
  { "FE3_PZC_EN"                    , WD2_FE3_PZC_EN_REG                    , WD2_FE3_PZC_EN_MASK                    , WD2_FE3_PZC_EN_OFS                    },
  { "FE3_AMPLIFIER2_COMP_EN"        , WD2_FE3_AMPLIFIER2_COMP_EN_REG        , WD2_FE3_AMPLIFIER2_COMP_EN_MASK        , WD2_FE3_AMPLIFIER2_COMP_EN_OFS        },
  { "FE3_AMPLIFIER2_EN"             , WD2_FE3_AMPLIFIER2_EN_REG             , WD2_FE3_AMPLIFIER2_EN_MASK             , WD2_FE3_AMPLIFIER2_EN_OFS             },
  { "FE3_AMPLIFIER1_COMP_EN"        , WD2_FE3_AMPLIFIER1_COMP_EN_REG        , WD2_FE3_AMPLIFIER1_COMP_EN_MASK        , WD2_FE3_AMPLIFIER1_COMP_EN_OFS        },
  { "FE3_AMPLIFIER1_EN"             , WD2_FE3_AMPLIFIER1_EN_REG             , WD2_FE3_AMPLIFIER1_EN_MASK             , WD2_FE3_AMPLIFIER1_EN_OFS             },
  { "FE3_ATTENUATION"               , WD2_FE3_ATTENUATION_REG               , WD2_FE3_ATTENUATION_MASK               , WD2_FE3_ATTENUATION_OFS               },
  { "FE3_MUX"                       , WD2_FE3_MUX_REG                       , WD2_FE3_MUX_MASK                       , WD2_FE3_MUX_OFS                       },
  { "FE4_PZC_EN"                    , WD2_FE4_PZC_EN_REG                    , WD2_FE4_PZC_EN_MASK                    , WD2_FE4_PZC_EN_OFS                    },
  { "FE4_AMPLIFIER2_COMP_EN"        , WD2_FE4_AMPLIFIER2_COMP_EN_REG        , WD2_FE4_AMPLIFIER2_COMP_EN_MASK        , WD2_FE4_AMPLIFIER2_COMP_EN_OFS        },
  { "FE4_AMPLIFIER2_EN"             , WD2_FE4_AMPLIFIER2_EN_REG             , WD2_FE4_AMPLIFIER2_EN_MASK             , WD2_FE4_AMPLIFIER2_EN_OFS             },
  { "FE4_AMPLIFIER1_COMP_EN"        , WD2_FE4_AMPLIFIER1_COMP_EN_REG        , WD2_FE4_AMPLIFIER1_COMP_EN_MASK        , WD2_FE4_AMPLIFIER1_COMP_EN_OFS        },
  { "FE4_AMPLIFIER1_EN"             , WD2_FE4_AMPLIFIER1_EN_REG             , WD2_FE4_AMPLIFIER1_EN_MASK             , WD2_FE4_AMPLIFIER1_EN_OFS             },
  { "FE4_ATTENUATION"               , WD2_FE4_ATTENUATION_REG               , WD2_FE4_ATTENUATION_MASK               , WD2_FE4_ATTENUATION_OFS               },
  { "FE4_MUX"                       , WD2_FE4_MUX_REG                       , WD2_FE4_MUX_MASK                       , WD2_FE4_MUX_OFS                       },
  { "FE5_PZC_EN"                    , WD2_FE5_PZC_EN_REG                    , WD2_FE5_PZC_EN_MASK                    , WD2_FE5_PZC_EN_OFS                    },
  { "FE5_AMPLIFIER2_COMP_EN"        , WD2_FE5_AMPLIFIER2_COMP_EN_REG        , WD2_FE5_AMPLIFIER2_COMP_EN_MASK        , WD2_FE5_AMPLIFIER2_COMP_EN_OFS        },
  { "FE5_AMPLIFIER2_EN"             , WD2_FE5_AMPLIFIER2_EN_REG             , WD2_FE5_AMPLIFIER2_EN_MASK             , WD2_FE5_AMPLIFIER2_EN_OFS             },
  { "FE5_AMPLIFIER1_COMP_EN"        , WD2_FE5_AMPLIFIER1_COMP_EN_REG        , WD2_FE5_AMPLIFIER1_COMP_EN_MASK        , WD2_FE5_AMPLIFIER1_COMP_EN_OFS        },
  { "FE5_AMPLIFIER1_EN"             , WD2_FE5_AMPLIFIER1_EN_REG             , WD2_FE5_AMPLIFIER1_EN_MASK             , WD2_FE5_AMPLIFIER1_EN_OFS             },
  { "FE5_ATTENUATION"               , WD2_FE5_ATTENUATION_REG               , WD2_FE5_ATTENUATION_MASK               , WD2_FE5_ATTENUATION_OFS               },
  { "FE5_MUX"                       , WD2_FE5_MUX_REG                       , WD2_FE5_MUX_MASK                       , WD2_FE5_MUX_OFS                       },
  { "FE6_PZC_EN"                    , WD2_FE6_PZC_EN_REG                    , WD2_FE6_PZC_EN_MASK                    , WD2_FE6_PZC_EN_OFS                    },
  { "FE6_AMPLIFIER2_COMP_EN"        , WD2_FE6_AMPLIFIER2_COMP_EN_REG        , WD2_FE6_AMPLIFIER2_COMP_EN_MASK        , WD2_FE6_AMPLIFIER2_COMP_EN_OFS        },
  { "FE6_AMPLIFIER2_EN"             , WD2_FE6_AMPLIFIER2_EN_REG             , WD2_FE6_AMPLIFIER2_EN_MASK             , WD2_FE6_AMPLIFIER2_EN_OFS             },
  { "FE6_AMPLIFIER1_COMP_EN"        , WD2_FE6_AMPLIFIER1_COMP_EN_REG        , WD2_FE6_AMPLIFIER1_COMP_EN_MASK        , WD2_FE6_AMPLIFIER1_COMP_EN_OFS        },
  { "FE6_AMPLIFIER1_EN"             , WD2_FE6_AMPLIFIER1_EN_REG             , WD2_FE6_AMPLIFIER1_EN_MASK             , WD2_FE6_AMPLIFIER1_EN_OFS             },
  { "FE6_ATTENUATION"               , WD2_FE6_ATTENUATION_REG               , WD2_FE6_ATTENUATION_MASK               , WD2_FE6_ATTENUATION_OFS               },
  { "FE6_MUX"                       , WD2_FE6_MUX_REG                       , WD2_FE6_MUX_MASK                       , WD2_FE6_MUX_OFS                       },
  { "FE7_PZC_EN"                    , WD2_FE7_PZC_EN_REG                    , WD2_FE7_PZC_EN_MASK                    , WD2_FE7_PZC_EN_OFS                    },
  { "FE7_AMPLIFIER2_COMP_EN"        , WD2_FE7_AMPLIFIER2_COMP_EN_REG        , WD2_FE7_AMPLIFIER2_COMP_EN_MASK        , WD2_FE7_AMPLIFIER2_COMP_EN_OFS        },
  { "FE7_AMPLIFIER2_EN"             , WD2_FE7_AMPLIFIER2_EN_REG             , WD2_FE7_AMPLIFIER2_EN_MASK             , WD2_FE7_AMPLIFIER2_EN_OFS             },
  { "FE7_AMPLIFIER1_COMP_EN"        , WD2_FE7_AMPLIFIER1_COMP_EN_REG        , WD2_FE7_AMPLIFIER1_COMP_EN_MASK        , WD2_FE7_AMPLIFIER1_COMP_EN_OFS        },
  { "FE7_AMPLIFIER1_EN"             , WD2_FE7_AMPLIFIER1_EN_REG             , WD2_FE7_AMPLIFIER1_EN_MASK             , WD2_FE7_AMPLIFIER1_EN_OFS             },
  { "FE7_ATTENUATION"               , WD2_FE7_ATTENUATION_REG               , WD2_FE7_ATTENUATION_MASK               , WD2_FE7_ATTENUATION_OFS               },
  { "FE7_MUX"                       , WD2_FE7_MUX_REG                       , WD2_FE7_MUX_MASK                       , WD2_FE7_MUX_OFS                       },
  { "FE8_PZC_EN"                    , WD2_FE8_PZC_EN_REG                    , WD2_FE8_PZC_EN_MASK                    , WD2_FE8_PZC_EN_OFS                    },
  { "FE8_AMPLIFIER2_COMP_EN"        , WD2_FE8_AMPLIFIER2_COMP_EN_REG        , WD2_FE8_AMPLIFIER2_COMP_EN_MASK        , WD2_FE8_AMPLIFIER2_COMP_EN_OFS        },
  { "FE8_AMPLIFIER2_EN"             , WD2_FE8_AMPLIFIER2_EN_REG             , WD2_FE8_AMPLIFIER2_EN_MASK             , WD2_FE8_AMPLIFIER2_EN_OFS             },
  { "FE8_AMPLIFIER1_COMP_EN"        , WD2_FE8_AMPLIFIER1_COMP_EN_REG        , WD2_FE8_AMPLIFIER1_COMP_EN_MASK        , WD2_FE8_AMPLIFIER1_COMP_EN_OFS        },
  { "FE8_AMPLIFIER1_EN"             , WD2_FE8_AMPLIFIER1_EN_REG             , WD2_FE8_AMPLIFIER1_EN_MASK             , WD2_FE8_AMPLIFIER1_EN_OFS             },
  { "FE8_ATTENUATION"               , WD2_FE8_ATTENUATION_REG               , WD2_FE8_ATTENUATION_MASK               , WD2_FE8_ATTENUATION_OFS               },
  { "FE8_MUX"                       , WD2_FE8_MUX_REG                       , WD2_FE8_MUX_MASK                       , WD2_FE8_MUX_OFS                       },
  { "FE9_PZC_EN"                    , WD2_FE9_PZC_EN_REG                    , WD2_FE9_PZC_EN_MASK                    , WD2_FE9_PZC_EN_OFS                    },
  { "FE9_AMPLIFIER2_COMP_EN"        , WD2_FE9_AMPLIFIER2_COMP_EN_REG        , WD2_FE9_AMPLIFIER2_COMP_EN_MASK        , WD2_FE9_AMPLIFIER2_COMP_EN_OFS        },
  { "FE9_AMPLIFIER2_EN"             , WD2_FE9_AMPLIFIER2_EN_REG             , WD2_FE9_AMPLIFIER2_EN_MASK             , WD2_FE9_AMPLIFIER2_EN_OFS             },
  { "FE9_AMPLIFIER1_COMP_EN"        , WD2_FE9_AMPLIFIER1_COMP_EN_REG        , WD2_FE9_AMPLIFIER1_COMP_EN_MASK        , WD2_FE9_AMPLIFIER1_COMP_EN_OFS        },
  { "FE9_AMPLIFIER1_EN"             , WD2_FE9_AMPLIFIER1_EN_REG             , WD2_FE9_AMPLIFIER1_EN_MASK             , WD2_FE9_AMPLIFIER1_EN_OFS             },
  { "FE9_ATTENUATION"               , WD2_FE9_ATTENUATION_REG               , WD2_FE9_ATTENUATION_MASK               , WD2_FE9_ATTENUATION_OFS               },
  { "FE9_MUX"                       , WD2_FE9_MUX_REG                       , WD2_FE9_MUX_MASK                       , WD2_FE9_MUX_OFS                       },
  { "FE10_PZC_EN"                   , WD2_FE10_PZC_EN_REG                   , WD2_FE10_PZC_EN_MASK                   , WD2_FE10_PZC_EN_OFS                   },
  { "FE10_AMPLIFIER2_COMP_EN"       , WD2_FE10_AMPLIFIER2_COMP_EN_REG       , WD2_FE10_AMPLIFIER2_COMP_EN_MASK       , WD2_FE10_AMPLIFIER2_COMP_EN_OFS       },
  { "FE10_AMPLIFIER2_EN"            , WD2_FE10_AMPLIFIER2_EN_REG            , WD2_FE10_AMPLIFIER2_EN_MASK            , WD2_FE10_AMPLIFIER2_EN_OFS            },
  { "FE10_AMPLIFIER1_COMP_EN"       , WD2_FE10_AMPLIFIER1_COMP_EN_REG       , WD2_FE10_AMPLIFIER1_COMP_EN_MASK       , WD2_FE10_AMPLIFIER1_COMP_EN_OFS       },
  { "FE10_AMPLIFIER1_EN"            , WD2_FE10_AMPLIFIER1_EN_REG            , WD2_FE10_AMPLIFIER1_EN_MASK            , WD2_FE10_AMPLIFIER1_EN_OFS            },
  { "FE10_ATTENUATION"              , WD2_FE10_ATTENUATION_REG              , WD2_FE10_ATTENUATION_MASK              , WD2_FE10_ATTENUATION_OFS              },
  { "FE10_MUX"                      , WD2_FE10_MUX_REG                      , WD2_FE10_MUX_MASK                      , WD2_FE10_MUX_OFS                      },
  { "FE11_PZC_EN"                   , WD2_FE11_PZC_EN_REG                   , WD2_FE11_PZC_EN_MASK                   , WD2_FE11_PZC_EN_OFS                   },
  { "FE11_AMPLIFIER2_COMP_EN"       , WD2_FE11_AMPLIFIER2_COMP_EN_REG       , WD2_FE11_AMPLIFIER2_COMP_EN_MASK       , WD2_FE11_AMPLIFIER2_COMP_EN_OFS       },
  { "FE11_AMPLIFIER2_EN"            , WD2_FE11_AMPLIFIER2_EN_REG            , WD2_FE11_AMPLIFIER2_EN_MASK            , WD2_FE11_AMPLIFIER2_EN_OFS            },
  { "FE11_AMPLIFIER1_COMP_EN"       , WD2_FE11_AMPLIFIER1_COMP_EN_REG       , WD2_FE11_AMPLIFIER1_COMP_EN_MASK       , WD2_FE11_AMPLIFIER1_COMP_EN_OFS       },
  { "FE11_AMPLIFIER1_EN"            , WD2_FE11_AMPLIFIER1_EN_REG            , WD2_FE11_AMPLIFIER1_EN_MASK            , WD2_FE11_AMPLIFIER1_EN_OFS            },
  { "FE11_ATTENUATION"              , WD2_FE11_ATTENUATION_REG              , WD2_FE11_ATTENUATION_MASK              , WD2_FE11_ATTENUATION_OFS              },
  { "FE11_MUX"                      , WD2_FE11_MUX_REG                      , WD2_FE11_MUX_MASK                      , WD2_FE11_MUX_OFS                      },
  { "FE12_PZC_EN"                   , WD2_FE12_PZC_EN_REG                   , WD2_FE12_PZC_EN_MASK                   , WD2_FE12_PZC_EN_OFS                   },
  { "FE12_AMPLIFIER2_COMP_EN"       , WD2_FE12_AMPLIFIER2_COMP_EN_REG       , WD2_FE12_AMPLIFIER2_COMP_EN_MASK       , WD2_FE12_AMPLIFIER2_COMP_EN_OFS       },
  { "FE12_AMPLIFIER2_EN"            , WD2_FE12_AMPLIFIER2_EN_REG            , WD2_FE12_AMPLIFIER2_EN_MASK            , WD2_FE12_AMPLIFIER2_EN_OFS            },
  { "FE12_AMPLIFIER1_COMP_EN"       , WD2_FE12_AMPLIFIER1_COMP_EN_REG       , WD2_FE12_AMPLIFIER1_COMP_EN_MASK       , WD2_FE12_AMPLIFIER1_COMP_EN_OFS       },
  { "FE12_AMPLIFIER1_EN"            , WD2_FE12_AMPLIFIER1_EN_REG            , WD2_FE12_AMPLIFIER1_EN_MASK            , WD2_FE12_AMPLIFIER1_EN_OFS            },
  { "FE12_ATTENUATION"              , WD2_FE12_ATTENUATION_REG              , WD2_FE12_ATTENUATION_MASK              , WD2_FE12_ATTENUATION_OFS              },
  { "FE12_MUX"                      , WD2_FE12_MUX_REG                      , WD2_FE12_MUX_MASK                      , WD2_FE12_MUX_OFS                      },
  { "FE13_PZC_EN"                   , WD2_FE13_PZC_EN_REG                   , WD2_FE13_PZC_EN_MASK                   , WD2_FE13_PZC_EN_OFS                   },
  { "FE13_AMPLIFIER2_COMP_EN"       , WD2_FE13_AMPLIFIER2_COMP_EN_REG       , WD2_FE13_AMPLIFIER2_COMP_EN_MASK       , WD2_FE13_AMPLIFIER2_COMP_EN_OFS       },
  { "FE13_AMPLIFIER2_EN"            , WD2_FE13_AMPLIFIER2_EN_REG            , WD2_FE13_AMPLIFIER2_EN_MASK            , WD2_FE13_AMPLIFIER2_EN_OFS            },
  { "FE13_AMPLIFIER1_COMP_EN"       , WD2_FE13_AMPLIFIER1_COMP_EN_REG       , WD2_FE13_AMPLIFIER1_COMP_EN_MASK       , WD2_FE13_AMPLIFIER1_COMP_EN_OFS       },
  { "FE13_AMPLIFIER1_EN"            , WD2_FE13_AMPLIFIER1_EN_REG            , WD2_FE13_AMPLIFIER1_EN_MASK            , WD2_FE13_AMPLIFIER1_EN_OFS            },
  { "FE13_ATTENUATION"              , WD2_FE13_ATTENUATION_REG              , WD2_FE13_ATTENUATION_MASK              , WD2_FE13_ATTENUATION_OFS              },
  { "FE13_MUX"                      , WD2_FE13_MUX_REG                      , WD2_FE13_MUX_MASK                      , WD2_FE13_MUX_OFS                      },
  { "FE14_PZC_EN"                   , WD2_FE14_PZC_EN_REG                   , WD2_FE14_PZC_EN_MASK                   , WD2_FE14_PZC_EN_OFS                   },
  { "FE14_AMPLIFIER2_COMP_EN"       , WD2_FE14_AMPLIFIER2_COMP_EN_REG       , WD2_FE14_AMPLIFIER2_COMP_EN_MASK       , WD2_FE14_AMPLIFIER2_COMP_EN_OFS       },
  { "FE14_AMPLIFIER2_EN"            , WD2_FE14_AMPLIFIER2_EN_REG            , WD2_FE14_AMPLIFIER2_EN_MASK            , WD2_FE14_AMPLIFIER2_EN_OFS            },
  { "FE14_AMPLIFIER1_COMP_EN"       , WD2_FE14_AMPLIFIER1_COMP_EN_REG       , WD2_FE14_AMPLIFIER1_COMP_EN_MASK       , WD2_FE14_AMPLIFIER1_COMP_EN_OFS       },
  { "FE14_AMPLIFIER1_EN"            , WD2_FE14_AMPLIFIER1_EN_REG            , WD2_FE14_AMPLIFIER1_EN_MASK            , WD2_FE14_AMPLIFIER1_EN_OFS            },
  { "FE14_ATTENUATION"              , WD2_FE14_ATTENUATION_REG              , WD2_FE14_ATTENUATION_MASK              , WD2_FE14_ATTENUATION_OFS              },
  { "FE14_MUX"                      , WD2_FE14_MUX_REG                      , WD2_FE14_MUX_MASK                      , WD2_FE14_MUX_OFS                      },
  { "FE15_PZC_EN"                   , WD2_FE15_PZC_EN_REG                   , WD2_FE15_PZC_EN_MASK                   , WD2_FE15_PZC_EN_OFS                   },
  { "FE15_AMPLIFIER2_COMP_EN"       , WD2_FE15_AMPLIFIER2_COMP_EN_REG       , WD2_FE15_AMPLIFIER2_COMP_EN_MASK       , WD2_FE15_AMPLIFIER2_COMP_EN_OFS       },
  { "FE15_AMPLIFIER2_EN"            , WD2_FE15_AMPLIFIER2_EN_REG            , WD2_FE15_AMPLIFIER2_EN_MASK            , WD2_FE15_AMPLIFIER2_EN_OFS            },
  { "FE15_AMPLIFIER1_COMP_EN"       , WD2_FE15_AMPLIFIER1_COMP_EN_REG       , WD2_FE15_AMPLIFIER1_COMP_EN_MASK       , WD2_FE15_AMPLIFIER1_COMP_EN_OFS       },
  { "FE15_AMPLIFIER1_EN"            , WD2_FE15_AMPLIFIER1_EN_REG            , WD2_FE15_AMPLIFIER1_EN_MASK            , WD2_FE15_AMPLIFIER1_EN_OFS            },
  { "FE15_ATTENUATION"              , WD2_FE15_ATTENUATION_REG              , WD2_FE15_ATTENUATION_MASK              , WD2_FE15_ATTENUATION_OFS              },
  { "FE15_MUX"                      , WD2_FE15_MUX_REG                      , WD2_FE15_MUX_MASK                      , WD2_FE15_MUX_OFS                      },
  { "HV_U_TARGET_0"                 , WD2_HV_U_TARGET_0_REG                 , WD2_HV_U_TARGET_0_MASK                 , WD2_HV_U_TARGET_0_OFS                 },
  { "HV_U_TARGET_1"                 , WD2_HV_U_TARGET_1_REG                 , WD2_HV_U_TARGET_1_MASK                 , WD2_HV_U_TARGET_1_OFS                 },
  { "HV_U_TARGET_2"                 , WD2_HV_U_TARGET_2_REG                 , WD2_HV_U_TARGET_2_MASK                 , WD2_HV_U_TARGET_2_OFS                 },
  { "HV_U_TARGET_3"                 , WD2_HV_U_TARGET_3_REG                 , WD2_HV_U_TARGET_3_MASK                 , WD2_HV_U_TARGET_3_OFS                 },
  { "HV_U_TARGET_4"                 , WD2_HV_U_TARGET_4_REG                 , WD2_HV_U_TARGET_4_MASK                 , WD2_HV_U_TARGET_4_OFS                 },
  { "HV_U_TARGET_5"                 , WD2_HV_U_TARGET_5_REG                 , WD2_HV_U_TARGET_5_MASK                 , WD2_HV_U_TARGET_5_OFS                 },
  { "HV_U_TARGET_6"                 , WD2_HV_U_TARGET_6_REG                 , WD2_HV_U_TARGET_6_MASK                 , WD2_HV_U_TARGET_6_OFS                 },
  { "HV_U_TARGET_7"                 , WD2_HV_U_TARGET_7_REG                 , WD2_HV_U_TARGET_7_MASK                 , WD2_HV_U_TARGET_7_OFS                 },
  { "HV_U_TARGET_8"                 , WD2_HV_U_TARGET_8_REG                 , WD2_HV_U_TARGET_8_MASK                 , WD2_HV_U_TARGET_8_OFS                 },
  { "HV_U_TARGET_9"                 , WD2_HV_U_TARGET_9_REG                 , WD2_HV_U_TARGET_9_MASK                 , WD2_HV_U_TARGET_9_OFS                 },
  { "HV_U_TARGET_10"                , WD2_HV_U_TARGET_10_REG                , WD2_HV_U_TARGET_10_MASK                , WD2_HV_U_TARGET_10_OFS                },
  { "HV_U_TARGET_11"                , WD2_HV_U_TARGET_11_REG                , WD2_HV_U_TARGET_11_MASK                , WD2_HV_U_TARGET_11_OFS                },
  { "HV_U_TARGET_12"                , WD2_HV_U_TARGET_12_REG                , WD2_HV_U_TARGET_12_MASK                , WD2_HV_U_TARGET_12_OFS                },
  { "HV_U_TARGET_13"                , WD2_HV_U_TARGET_13_REG                , WD2_HV_U_TARGET_13_MASK                , WD2_HV_U_TARGET_13_OFS                },
  { "HV_U_TARGET_14"                , WD2_HV_U_TARGET_14_REG                , WD2_HV_U_TARGET_14_MASK                , WD2_HV_U_TARGET_14_OFS                },
  { "HV_U_TARGET_15"                , WD2_HV_U_TARGET_15_REG                , WD2_HV_U_TARGET_15_MASK                , WD2_HV_U_TARGET_15_OFS                },
  { "HV_R_SHUNT"                    , WD2_HV_R_SHUNT_REG                    , WD2_HV_R_SHUNT_MASK                    , WD2_HV_R_SHUNT_OFS                    },
  { "LMK0_RESET"                    , WD2_LMK0_RESET_REG                    , WD2_LMK0_RESET_MASK                    , WD2_LMK0_RESET_OFS                    },
  { "LMK0_CLKOUT_MUX"               , WD2_LMK0_CLKOUT_MUX_REG               , WD2_LMK0_CLKOUT_MUX_MASK               , WD2_LMK0_CLKOUT_MUX_OFS               },
  { "LMK0_CLKOUT_EN"                , WD2_LMK0_CLKOUT_EN_REG                , WD2_LMK0_CLKOUT_EN_MASK                , WD2_LMK0_CLKOUT_EN_OFS                },
  { "LMK0_CLKOUT_DIV"               , WD2_LMK0_CLKOUT_DIV_REG               , WD2_LMK0_CLKOUT_DIV_MASK               , WD2_LMK0_CLKOUT_DIV_OFS               },
  { "LMK0_CLKOUT_DLY"               , WD2_LMK0_CLKOUT_DLY_REG               , WD2_LMK0_CLKOUT_DLY_MASK               , WD2_LMK0_CLKOUT_DLY_OFS               },
  { "LMK1_CLKOUT_MUX"               , WD2_LMK1_CLKOUT_MUX_REG               , WD2_LMK1_CLKOUT_MUX_MASK               , WD2_LMK1_CLKOUT_MUX_OFS               },
  { "LMK1_CLKOUT_EN"                , WD2_LMK1_CLKOUT_EN_REG                , WD2_LMK1_CLKOUT_EN_MASK                , WD2_LMK1_CLKOUT_EN_OFS                },
  { "LMK1_CLKOUT_DIV"               , WD2_LMK1_CLKOUT_DIV_REG               , WD2_LMK1_CLKOUT_DIV_MASK               , WD2_LMK1_CLKOUT_DIV_OFS               },
  { "LMK1_CLKOUT_DLY"               , WD2_LMK1_CLKOUT_DLY_REG               , WD2_LMK1_CLKOUT_DLY_MASK               , WD2_LMK1_CLKOUT_DLY_OFS               },
  { "LMK2_CLKOUT_MUX"               , WD2_LMK2_CLKOUT_MUX_REG               , WD2_LMK2_CLKOUT_MUX_MASK               , WD2_LMK2_CLKOUT_MUX_OFS               },
  { "LMK2_CLKOUT_EN"                , WD2_LMK2_CLKOUT_EN_REG                , WD2_LMK2_CLKOUT_EN_MASK                , WD2_LMK2_CLKOUT_EN_OFS                },
  { "LMK2_CLKOUT_DIV"               , WD2_LMK2_CLKOUT_DIV_REG               , WD2_LMK2_CLKOUT_DIV_MASK               , WD2_LMK2_CLKOUT_DIV_OFS               },
  { "LMK2_CLKOUT_DLY"               , WD2_LMK2_CLKOUT_DLY_REG               , WD2_LMK2_CLKOUT_DLY_MASK               , WD2_LMK2_CLKOUT_DLY_OFS               },
  { "LMK3_CLKOUT_MUX"               , WD2_LMK3_CLKOUT_MUX_REG               , WD2_LMK3_CLKOUT_MUX_MASK               , WD2_LMK3_CLKOUT_MUX_OFS               },
  { "LMK3_CLKOUT_EN"                , WD2_LMK3_CLKOUT_EN_REG                , WD2_LMK3_CLKOUT_EN_MASK                , WD2_LMK3_CLKOUT_EN_OFS                },
  { "LMK3_CLKOUT_DIV"               , WD2_LMK3_CLKOUT_DIV_REG               , WD2_LMK3_CLKOUT_DIV_MASK               , WD2_LMK3_CLKOUT_DIV_OFS               },
  { "LMK3_CLKOUT_DLY"               , WD2_LMK3_CLKOUT_DLY_REG               , WD2_LMK3_CLKOUT_DLY_MASK               , WD2_LMK3_CLKOUT_DLY_OFS               },
  { "LMK4_CLKOUT_MUX"               , WD2_LMK4_CLKOUT_MUX_REG               , WD2_LMK4_CLKOUT_MUX_MASK               , WD2_LMK4_CLKOUT_MUX_OFS               },
  { "LMK4_CLKOUT_EN"                , WD2_LMK4_CLKOUT_EN_REG                , WD2_LMK4_CLKOUT_EN_MASK                , WD2_LMK4_CLKOUT_EN_OFS                },
  { "LMK4_CLKOUT_DIV"               , WD2_LMK4_CLKOUT_DIV_REG               , WD2_LMK4_CLKOUT_DIV_MASK               , WD2_LMK4_CLKOUT_DIV_OFS               },
  { "LMK4_CLKOUT_DLY"               , WD2_LMK4_CLKOUT_DLY_REG               , WD2_LMK4_CLKOUT_DLY_MASK               , WD2_LMK4_CLKOUT_DLY_OFS               },
  { "LMK5_CLKOUT_MUX"               , WD2_LMK5_CLKOUT_MUX_REG               , WD2_LMK5_CLKOUT_MUX_MASK               , WD2_LMK5_CLKOUT_MUX_OFS               },
  { "LMK5_CLKOUT_EN"                , WD2_LMK5_CLKOUT_EN_REG                , WD2_LMK5_CLKOUT_EN_MASK                , WD2_LMK5_CLKOUT_EN_OFS                },
  { "LMK5_CLKOUT_DIV"               , WD2_LMK5_CLKOUT_DIV_REG               , WD2_LMK5_CLKOUT_DIV_MASK               , WD2_LMK5_CLKOUT_DIV_OFS               },
  { "LMK5_CLKOUT_DLY"               , WD2_LMK5_CLKOUT_DLY_REG               , WD2_LMK5_CLKOUT_DLY_MASK               , WD2_LMK5_CLKOUT_DLY_OFS               },
  { "LMK6_CLKOUT_MUX"               , WD2_LMK6_CLKOUT_MUX_REG               , WD2_LMK6_CLKOUT_MUX_MASK               , WD2_LMK6_CLKOUT_MUX_OFS               },
  { "LMK6_CLKOUT_EN"                , WD2_LMK6_CLKOUT_EN_REG                , WD2_LMK6_CLKOUT_EN_MASK                , WD2_LMK6_CLKOUT_EN_OFS                },
  { "LMK6_CLKOUT_DIV"               , WD2_LMK6_CLKOUT_DIV_REG               , WD2_LMK6_CLKOUT_DIV_MASK               , WD2_LMK6_CLKOUT_DIV_OFS               },
  { "LMK6_CLKOUT_DLY"               , WD2_LMK6_CLKOUT_DLY_REG               , WD2_LMK6_CLKOUT_DLY_MASK               , WD2_LMK6_CLKOUT_DLY_OFS               },
  { "LMK7_CLKOUT_MUX"               , WD2_LMK7_CLKOUT_MUX_REG               , WD2_LMK7_CLKOUT_MUX_MASK               , WD2_LMK7_CLKOUT_MUX_OFS               },
  { "LMK7_CLKOUT_EN"                , WD2_LMK7_CLKOUT_EN_REG                , WD2_LMK7_CLKOUT_EN_MASK                , WD2_LMK7_CLKOUT_EN_OFS                },
  { "LMK7_CLKOUT_DIV"               , WD2_LMK7_CLKOUT_DIV_REG               , WD2_LMK7_CLKOUT_DIV_MASK               , WD2_LMK7_CLKOUT_DIV_OFS               },
  { "LMK7_CLKOUT_DLY"               , WD2_LMK7_CLKOUT_DLY_REG               , WD2_LMK7_CLKOUT_DLY_MASK               , WD2_LMK7_CLKOUT_DLY_OFS               },
  { "LMK8_PHASE_NOISE_OPT"          , WD2_LMK8_PHASE_NOISE_OPT_REG          , WD2_LMK8_PHASE_NOISE_OPT_MASK          , WD2_LMK8_PHASE_NOISE_OPT_OFS          },
  { "LMK9_VBOOST"                   , WD2_LMK9_VBOOST_REG                   , WD2_LMK9_VBOOST_MASK                   , WD2_LMK9_VBOOST_OFS                   },
  { "LMK11_DIV4"                    , WD2_LMK11_DIV4_REG                    , WD2_LMK11_DIV4_MASK                    , WD2_LMK11_DIV4_OFS                    },
  { "LMK13_OSCIN_FREQ"              , WD2_LMK13_OSCIN_FREQ_REG              , WD2_LMK13_OSCIN_FREQ_MASK              , WD2_LMK13_OSCIN_FREQ_OFS              },
  { "LMK13_VCO_R4_LF"               , WD2_LMK13_VCO_R4_LF_REG               , WD2_LMK13_VCO_R4_LF_MASK               , WD2_LMK13_VCO_R4_LF_OFS               },
  { "LMK13_VCO_R3_LF"               , WD2_LMK13_VCO_R3_LF_REG               , WD2_LMK13_VCO_R3_LF_MASK               , WD2_LMK13_VCO_R3_LF_OFS               },
  { "LMK13_VCO_C3_C4_LF"            , WD2_LMK13_VCO_C3_C4_LF_REG            , WD2_LMK13_VCO_C3_C4_LF_MASK            , WD2_LMK13_VCO_C3_C4_LF_OFS            },
  { "LMK14_EN_FOUT"                 , WD2_LMK14_EN_FOUT_REG                 , WD2_LMK14_EN_FOUT_MASK                 , WD2_LMK14_EN_FOUT_OFS                 },
  { "LMK14_EN_CLKOUT_GLOBAL"        , WD2_LMK14_EN_CLKOUT_GLOBAL_REG        , WD2_LMK14_EN_CLKOUT_GLOBAL_MASK        , WD2_LMK14_EN_CLKOUT_GLOBAL_OFS        },
  { "LMK14_POWERDOWN"               , WD2_LMK14_POWERDOWN_REG               , WD2_LMK14_POWERDOWN_MASK               , WD2_LMK14_POWERDOWN_OFS               },
  { "LMK14_PLL_MUX"                 , WD2_LMK14_PLL_MUX_REG                 , WD2_LMK14_PLL_MUX_MASK                 , WD2_LMK14_PLL_MUX_OFS                 },
  { "LMK14_PLL_R"                   , WD2_LMK14_PLL_R_REG                   , WD2_LMK14_PLL_R_MASK                   , WD2_LMK14_PLL_R_OFS                   },
  { "LMK15_PLL_CP_GAIN"             , WD2_LMK15_PLL_CP_GAIN_REG             , WD2_LMK15_PLL_CP_GAIN_MASK             , WD2_LMK15_PLL_CP_GAIN_OFS             },
  { "LMK15_VCO_DIV"                 , WD2_LMK15_VCO_DIV_REG                 , WD2_LMK15_VCO_DIV_MASK                 , WD2_LMK15_VCO_DIV_OFS                 },
  { "LMK15_PLL_N"                   , WD2_LMK15_PLL_N_REG                   , WD2_LMK15_PLL_N_MASK                   , WD2_LMK15_PLL_N_OFS                   },
  { "ADC_0_1458_DCSOFF"             , WD2_ADC_0_1458_DCSOFF_REG             , WD2_ADC_0_1458_DCSOFF_MASK             , WD2_ADC_0_1458_DCSOFF_OFS             },
  { "ADC_0_1458_RAND"               , WD2_ADC_0_1458_RAND_REG               , WD2_ADC_0_1458_RAND_MASK               , WD2_ADC_0_1458_RAND_OFS               },
  { "ADC_0_1458_TWOSCOMP"           , WD2_ADC_0_1458_TWOSCOMP_REG           , WD2_ADC_0_1458_TWOSCOMP_MASK           , WD2_ADC_0_1458_TWOSCOMP_OFS           },
  { "ADC_0_1458_SLEEP"              , WD2_ADC_0_1458_SLEEP_REG              , WD2_ADC_0_1458_SLEEP_MASK              , WD2_ADC_0_1458_SLEEP_OFS              },
  { "ADC_0_8_NAP_MODE"              , WD2_ADC_0_8_NAP_MODE_REG              , WD2_ADC_0_8_NAP_MODE_MASK              , WD2_ADC_0_8_NAP_MODE_OFS              },
  { "ADC_0_5_NAP_MODE"              , WD2_ADC_0_5_NAP_MODE_REG              , WD2_ADC_0_5_NAP_MODE_MASK              , WD2_ADC_0_5_NAP_MODE_OFS              },
  { "ADC_0_4_NAP_MODE"              , WD2_ADC_0_4_NAP_MODE_REG              , WD2_ADC_0_4_NAP_MODE_MASK              , WD2_ADC_0_4_NAP_MODE_OFS              },
  { "ADC_0_1_NAP_MODE"              , WD2_ADC_0_1_NAP_MODE_REG              , WD2_ADC_0_1_NAP_MODE_MASK              , WD2_ADC_0_1_NAP_MODE_OFS              },
  { "ADC_0_1458_ILVDS"              , WD2_ADC_0_1458_ILVDS_REG              , WD2_ADC_0_1458_ILVDS_MASK              , WD2_ADC_0_1458_ILVDS_OFS              },
  { "ADC_0_1458_TERMON"             , WD2_ADC_0_1458_TERMON_REG             , WD2_ADC_0_1458_TERMON_MASK             , WD2_ADC_0_1458_TERMON_OFS             },
  { "ADC_0_1458_OUTOFF"             , WD2_ADC_0_1458_OUTOFF_REG             , WD2_ADC_0_1458_OUTOFF_MASK             , WD2_ADC_0_1458_OUTOFF_OFS             },
  { "ADC_0_1458_OUTMODE"            , WD2_ADC_0_1458_OUTMODE_REG            , WD2_ADC_0_1458_OUTMODE_MASK            , WD2_ADC_0_1458_OUTMODE_OFS            },
  { "ADC_0_1458_OUTTEST"            , WD2_ADC_0_1458_OUTTEST_REG            , WD2_ADC_0_1458_OUTTEST_MASK            , WD2_ADC_0_1458_OUTTEST_OFS            },
  { "ADC_0_1458_TP"                 , WD2_ADC_0_1458_TP_REG                 , WD2_ADC_0_1458_TP_MASK                 , WD2_ADC_0_1458_TP_OFS                 },
  { "ADC_0_1458_TP_LSBS"            , WD2_ADC_0_1458_TP_LSBS_REG            , WD2_ADC_0_1458_TP_LSBS_MASK            , WD2_ADC_0_1458_TP_LSBS_OFS            },
  { "ADC_0_2367_DCSOFF"             , WD2_ADC_0_2367_DCSOFF_REG             , WD2_ADC_0_2367_DCSOFF_MASK             , WD2_ADC_0_2367_DCSOFF_OFS             },
  { "ADC_0_2367_RAND"               , WD2_ADC_0_2367_RAND_REG               , WD2_ADC_0_2367_RAND_MASK               , WD2_ADC_0_2367_RAND_OFS               },
  { "ADC_0_2367_TWOSCOMP"           , WD2_ADC_0_2367_TWOSCOMP_REG           , WD2_ADC_0_2367_TWOSCOMP_MASK           , WD2_ADC_0_2367_TWOSCOMP_OFS           },
  { "ADC_0_2367_SLEEP"              , WD2_ADC_0_2367_SLEEP_REG              , WD2_ADC_0_2367_SLEEP_MASK              , WD2_ADC_0_2367_SLEEP_OFS              },
  { "ADC_0_7_NAP_MODE"              , WD2_ADC_0_7_NAP_MODE_REG              , WD2_ADC_0_7_NAP_MODE_MASK              , WD2_ADC_0_7_NAP_MODE_OFS              },
  { "ADC_0_6_NAP_MODE"              , WD2_ADC_0_6_NAP_MODE_REG              , WD2_ADC_0_6_NAP_MODE_MASK              , WD2_ADC_0_6_NAP_MODE_OFS              },
  { "ADC_0_3_NAP_MODE"              , WD2_ADC_0_3_NAP_MODE_REG              , WD2_ADC_0_3_NAP_MODE_MASK              , WD2_ADC_0_3_NAP_MODE_OFS              },
  { "ADC_0_2_NAP_MODE"              , WD2_ADC_0_2_NAP_MODE_REG              , WD2_ADC_0_2_NAP_MODE_MASK              , WD2_ADC_0_2_NAP_MODE_OFS              },
  { "ADC_0_2367_ILVDS"              , WD2_ADC_0_2367_ILVDS_REG              , WD2_ADC_0_2367_ILVDS_MASK              , WD2_ADC_0_2367_ILVDS_OFS              },
  { "ADC_0_2367_TERMON"             , WD2_ADC_0_2367_TERMON_REG             , WD2_ADC_0_2367_TERMON_MASK             , WD2_ADC_0_2367_TERMON_OFS             },
  { "ADC_0_2367_OUTOFF"             , WD2_ADC_0_2367_OUTOFF_REG             , WD2_ADC_0_2367_OUTOFF_MASK             , WD2_ADC_0_2367_OUTOFF_OFS             },
  { "ADC_0_2367_OUTMODE"            , WD2_ADC_0_2367_OUTMODE_REG            , WD2_ADC_0_2367_OUTMODE_MASK            , WD2_ADC_0_2367_OUTMODE_OFS            },
  { "ADC_0_2367_OUTTEST"            , WD2_ADC_0_2367_OUTTEST_REG            , WD2_ADC_0_2367_OUTTEST_MASK            , WD2_ADC_0_2367_OUTTEST_OFS            },
  { "ADC_0_2367_TP"                 , WD2_ADC_0_2367_TP_REG                 , WD2_ADC_0_2367_TP_MASK                 , WD2_ADC_0_2367_TP_OFS                 },
  { "ADC_0_2367_TP_LSBS"            , WD2_ADC_0_2367_TP_LSBS_REG            , WD2_ADC_0_2367_TP_LSBS_MASK            , WD2_ADC_0_2367_TP_LSBS_OFS            },
  { "ADC_1_1458_DCSOFF"             , WD2_ADC_1_1458_DCSOFF_REG             , WD2_ADC_1_1458_DCSOFF_MASK             , WD2_ADC_1_1458_DCSOFF_OFS             },
  { "ADC_1_1458_RAND"               , WD2_ADC_1_1458_RAND_REG               , WD2_ADC_1_1458_RAND_MASK               , WD2_ADC_1_1458_RAND_OFS               },
  { "ADC_1_1458_TWOSCOMP"           , WD2_ADC_1_1458_TWOSCOMP_REG           , WD2_ADC_1_1458_TWOSCOMP_MASK           , WD2_ADC_1_1458_TWOSCOMP_OFS           },
  { "ADC_1_1458_SLEEP"              , WD2_ADC_1_1458_SLEEP_REG              , WD2_ADC_1_1458_SLEEP_MASK              , WD2_ADC_1_1458_SLEEP_OFS              },
  { "ADC_1_8_NAP_MODE"              , WD2_ADC_1_8_NAP_MODE_REG              , WD2_ADC_1_8_NAP_MODE_MASK              , WD2_ADC_1_8_NAP_MODE_OFS              },
  { "ADC_1_5_NAP_MODE"              , WD2_ADC_1_5_NAP_MODE_REG              , WD2_ADC_1_5_NAP_MODE_MASK              , WD2_ADC_1_5_NAP_MODE_OFS              },
  { "ADC_1_4_NAP_MODE"              , WD2_ADC_1_4_NAP_MODE_REG              , WD2_ADC_1_4_NAP_MODE_MASK              , WD2_ADC_1_4_NAP_MODE_OFS              },
  { "ADC_1_1_NAP_MODE"              , WD2_ADC_1_1_NAP_MODE_REG              , WD2_ADC_1_1_NAP_MODE_MASK              , WD2_ADC_1_1_NAP_MODE_OFS              },
  { "ADC_1_1458_ILVDS"              , WD2_ADC_1_1458_ILVDS_REG              , WD2_ADC_1_1458_ILVDS_MASK              , WD2_ADC_1_1458_ILVDS_OFS              },
  { "ADC_1_1458_TERMON"             , WD2_ADC_1_1458_TERMON_REG             , WD2_ADC_1_1458_TERMON_MASK             , WD2_ADC_1_1458_TERMON_OFS             },
  { "ADC_1_1458_OUTOFF"             , WD2_ADC_1_1458_OUTOFF_REG             , WD2_ADC_1_1458_OUTOFF_MASK             , WD2_ADC_1_1458_OUTOFF_OFS             },
  { "ADC_1_1458_OUTMODE"            , WD2_ADC_1_1458_OUTMODE_REG            , WD2_ADC_1_1458_OUTMODE_MASK            , WD2_ADC_1_1458_OUTMODE_OFS            },
  { "ADC_1_1458_OUTTEST"            , WD2_ADC_1_1458_OUTTEST_REG            , WD2_ADC_1_1458_OUTTEST_MASK            , WD2_ADC_1_1458_OUTTEST_OFS            },
  { "ADC_1_1458_TP"                 , WD2_ADC_1_1458_TP_REG                 , WD2_ADC_1_1458_TP_MASK                 , WD2_ADC_1_1458_TP_OFS                 },
  { "ADC_1_1458_TP_LSBS"            , WD2_ADC_1_1458_TP_LSBS_REG            , WD2_ADC_1_1458_TP_LSBS_MASK            , WD2_ADC_1_1458_TP_LSBS_OFS            },
  { "ADC_1_2367_DCSOFF"             , WD2_ADC_1_2367_DCSOFF_REG             , WD2_ADC_1_2367_DCSOFF_MASK             , WD2_ADC_1_2367_DCSOFF_OFS             },
  { "ADC_1_2367_RAND"               , WD2_ADC_1_2367_RAND_REG               , WD2_ADC_1_2367_RAND_MASK               , WD2_ADC_1_2367_RAND_OFS               },
  { "ADC_1_2367_TWOSCOMP"           , WD2_ADC_1_2367_TWOSCOMP_REG           , WD2_ADC_1_2367_TWOSCOMP_MASK           , WD2_ADC_1_2367_TWOSCOMP_OFS           },
  { "ADC_1_2367_SLEEP"              , WD2_ADC_1_2367_SLEEP_REG              , WD2_ADC_1_2367_SLEEP_MASK              , WD2_ADC_1_2367_SLEEP_OFS              },
  { "ADC_1_7_NAP_MODE"              , WD2_ADC_1_7_NAP_MODE_REG              , WD2_ADC_1_7_NAP_MODE_MASK              , WD2_ADC_1_7_NAP_MODE_OFS              },
  { "ADC_1_6_NAP_MODE"              , WD2_ADC_1_6_NAP_MODE_REG              , WD2_ADC_1_6_NAP_MODE_MASK              , WD2_ADC_1_6_NAP_MODE_OFS              },
  { "ADC_1_3_NAP_MODE"              , WD2_ADC_1_3_NAP_MODE_REG              , WD2_ADC_1_3_NAP_MODE_MASK              , WD2_ADC_1_3_NAP_MODE_OFS              },
  { "ADC_1_2_NAP_MODE"              , WD2_ADC_1_2_NAP_MODE_REG              , WD2_ADC_1_2_NAP_MODE_MASK              , WD2_ADC_1_2_NAP_MODE_OFS              },
  { "ADC_1_2367_ILVDS"              , WD2_ADC_1_2367_ILVDS_REG              , WD2_ADC_1_2367_ILVDS_MASK              , WD2_ADC_1_2367_ILVDS_OFS              },
  { "ADC_1_2367_TERMON"             , WD2_ADC_1_2367_TERMON_REG             , WD2_ADC_1_2367_TERMON_MASK             , WD2_ADC_1_2367_TERMON_OFS             },
  { "ADC_1_2367_OUTOFF"             , WD2_ADC_1_2367_OUTOFF_REG             , WD2_ADC_1_2367_OUTOFF_MASK             , WD2_ADC_1_2367_OUTOFF_OFS             },
  { "ADC_1_2367_OUTMODE"            , WD2_ADC_1_2367_OUTMODE_REG            , WD2_ADC_1_2367_OUTMODE_MASK            , WD2_ADC_1_2367_OUTMODE_OFS            },
  { "ADC_1_2367_OUTTEST"            , WD2_ADC_1_2367_OUTTEST_REG            , WD2_ADC_1_2367_OUTTEST_MASK            , WD2_ADC_1_2367_OUTTEST_OFS            },
  { "ADC_1_2367_TP"                 , WD2_ADC_1_2367_TP_REG                 , WD2_ADC_1_2367_TP_MASK                 , WD2_ADC_1_2367_TP_OFS                 },
  { "ADC_1_2367_TP_LSBS"            , WD2_ADC_1_2367_TP_LSBS_REG            , WD2_ADC_1_2367_TP_LSBS_MASK            , WD2_ADC_1_2367_TP_LSBS_OFS            },
  { "LEAD_TRAIL_EDGE_SEL"           , WD2_LEAD_TRAIL_EDGE_SEL_REG           , WD2_LEAD_TRAIL_EDGE_SEL_MASK           , WD2_LEAD_TRAIL_EDGE_SEL_OFS           },
  { "EXT_TRIGGER_OUT_ENABLE"        , WD2_EXT_TRIGGER_OUT_ENABLE_REG        , WD2_EXT_TRIGGER_OUT_ENABLE_MASK        , WD2_EXT_TRIGGER_OUT_ENABLE_OFS        },
  { "EXT_ASYNC_TRIGGER_EN"          , WD2_EXT_ASYNC_TRIGGER_EN_REG          , WD2_EXT_ASYNC_TRIGGER_EN_MASK          , WD2_EXT_ASYNC_TRIGGER_EN_OFS          },
  { "PATTERN_TRIGGER_EN"            , WD2_PATTERN_TRIGGER_EN_REG            , WD2_PATTERN_TRIGGER_EN_MASK            , WD2_PATTERN_TRIGGER_EN_OFS            },
  { "TRIGGER_OUT_PULSE_LENGTH"      , WD2_TRIGGER_OUT_PULSE_LENGTH_REG      , WD2_TRIGGER_OUT_PULSE_LENGTH_MASK      , WD2_TRIGGER_OUT_PULSE_LENGTH_OFS      },
  { "TRIGGER_DELAY"                 , WD2_TRIGGER_DELAY_REG                 , WD2_TRIGGER_DELAY_MASK                 , WD2_TRIGGER_DELAY_OFS                 },
  { "TRG_SRC_POLARITY"              , WD2_TRG_SRC_POLARITY_REG              , WD2_TRG_SRC_POLARITY_MASK              , WD2_TRG_SRC_POLARITY_OFS              },
  { "AUTO_TRIGGER_PERIOD"           , WD2_AUTO_TRIGGER_PERIOD_REG           , WD2_AUTO_TRIGGER_PERIOD_MASK           , WD2_AUTO_TRIGGER_PERIOD_OFS           },
  { "TRG_PTRN_EN"                   , WD2_TRG_PTRN_EN_REG                   , WD2_TRG_PTRN_EN_MASK                   , WD2_TRG_PTRN_EN_OFS                   },
  { "TRG_SRC_EN_PTRN0"              , WD2_TRG_SRC_EN_PTRN0_REG              , WD2_TRG_SRC_EN_PTRN0_MASK              , WD2_TRG_SRC_EN_PTRN0_OFS              },
  { "TRG_STATE_PTRN0"               , WD2_TRG_STATE_PTRN0_REG               , WD2_TRG_STATE_PTRN0_MASK               , WD2_TRG_STATE_PTRN0_OFS               },
  { "TRG_SRC_EN_PTRN1"              , WD2_TRG_SRC_EN_PTRN1_REG              , WD2_TRG_SRC_EN_PTRN1_MASK              , WD2_TRG_SRC_EN_PTRN1_OFS              },
  { "TRG_STATE_PTRN1"               , WD2_TRG_STATE_PTRN1_REG               , WD2_TRG_STATE_PTRN1_MASK               , WD2_TRG_STATE_PTRN1_OFS               },
  { "TRG_SRC_EN_PTRN2"              , WD2_TRG_SRC_EN_PTRN2_REG              , WD2_TRG_SRC_EN_PTRN2_MASK              , WD2_TRG_SRC_EN_PTRN2_OFS              },
  { "TRG_STATE_PTRN2"               , WD2_TRG_STATE_PTRN2_REG               , WD2_TRG_STATE_PTRN2_MASK               , WD2_TRG_STATE_PTRN2_OFS               },
  { "TRG_SRC_EN_PTRN3"              , WD2_TRG_SRC_EN_PTRN3_REG              , WD2_TRG_SRC_EN_PTRN3_MASK              , WD2_TRG_SRC_EN_PTRN3_OFS              },
  { "TRG_STATE_PTRN3"               , WD2_TRG_STATE_PTRN3_REG               , WD2_TRG_STATE_PTRN3_MASK               , WD2_TRG_STATE_PTRN3_OFS               },
  { "TRG_SRC_EN_PTRN4"              , WD2_TRG_SRC_EN_PTRN4_REG              , WD2_TRG_SRC_EN_PTRN4_MASK              , WD2_TRG_SRC_EN_PTRN4_OFS              },
  { "TRG_STATE_PTRN4"               , WD2_TRG_STATE_PTRN4_REG               , WD2_TRG_STATE_PTRN4_MASK               , WD2_TRG_STATE_PTRN4_OFS               },
  { "TRG_SRC_EN_PTRN5"              , WD2_TRG_SRC_EN_PTRN5_REG              , WD2_TRG_SRC_EN_PTRN5_MASK              , WD2_TRG_SRC_EN_PTRN5_OFS              },
  { "TRG_STATE_PTRN5"               , WD2_TRG_STATE_PTRN5_REG               , WD2_TRG_STATE_PTRN5_MASK               , WD2_TRG_STATE_PTRN5_OFS               },
  { "TRG_SRC_EN_PTRN6"              , WD2_TRG_SRC_EN_PTRN6_REG              , WD2_TRG_SRC_EN_PTRN6_MASK              , WD2_TRG_SRC_EN_PTRN6_OFS              },
  { "TRG_STATE_PTRN6"               , WD2_TRG_STATE_PTRN6_REG               , WD2_TRG_STATE_PTRN6_MASK               , WD2_TRG_STATE_PTRN6_OFS               },
  { "TRG_SRC_EN_PTRN7"              , WD2_TRG_SRC_EN_PTRN7_REG              , WD2_TRG_SRC_EN_PTRN7_MASK              , WD2_TRG_SRC_EN_PTRN7_OFS              },
  { "TRG_STATE_PTRN7"               , WD2_TRG_STATE_PTRN7_REG               , WD2_TRG_STATE_PTRN7_MASK               , WD2_TRG_STATE_PTRN7_OFS               },
  { "TRG_SRC_EN_PTRN8"              , WD2_TRG_SRC_EN_PTRN8_REG              , WD2_TRG_SRC_EN_PTRN8_MASK              , WD2_TRG_SRC_EN_PTRN8_OFS              },
  { "TRG_STATE_PTRN8"               , WD2_TRG_STATE_PTRN8_REG               , WD2_TRG_STATE_PTRN8_MASK               , WD2_TRG_STATE_PTRN8_OFS               },
  { "TRG_SRC_EN_PTRN9"              , WD2_TRG_SRC_EN_PTRN9_REG              , WD2_TRG_SRC_EN_PTRN9_MASK              , WD2_TRG_SRC_EN_PTRN9_OFS              },
  { "TRG_STATE_PTRN9"               , WD2_TRG_STATE_PTRN9_REG               , WD2_TRG_STATE_PTRN9_MASK               , WD2_TRG_STATE_PTRN9_OFS               },
  { "TRG_SRC_EN_PTRN10"             , WD2_TRG_SRC_EN_PTRN10_REG             , WD2_TRG_SRC_EN_PTRN10_MASK             , WD2_TRG_SRC_EN_PTRN10_OFS             },
  { "TRG_STATE_PTRN10"              , WD2_TRG_STATE_PTRN10_REG              , WD2_TRG_STATE_PTRN10_MASK              , WD2_TRG_STATE_PTRN10_OFS              },
  { "TRG_SRC_EN_PTRN11"             , WD2_TRG_SRC_EN_PTRN11_REG             , WD2_TRG_SRC_EN_PTRN11_MASK             , WD2_TRG_SRC_EN_PTRN11_OFS             },
  { "TRG_STATE_PTRN11"              , WD2_TRG_STATE_PTRN11_REG              , WD2_TRG_STATE_PTRN11_MASK              , WD2_TRG_STATE_PTRN11_OFS              },
  { "TRG_SRC_EN_PTRN12"             , WD2_TRG_SRC_EN_PTRN12_REG             , WD2_TRG_SRC_EN_PTRN12_MASK             , WD2_TRG_SRC_EN_PTRN12_OFS             },
  { "TRG_STATE_PTRN12"              , WD2_TRG_STATE_PTRN12_REG              , WD2_TRG_STATE_PTRN12_MASK              , WD2_TRG_STATE_PTRN12_OFS              },
  { "TRG_SRC_EN_PTRN13"             , WD2_TRG_SRC_EN_PTRN13_REG             , WD2_TRG_SRC_EN_PTRN13_MASK             , WD2_TRG_SRC_EN_PTRN13_OFS             },
  { "TRG_STATE_PTRN13"              , WD2_TRG_STATE_PTRN13_REG              , WD2_TRG_STATE_PTRN13_MASK              , WD2_TRG_STATE_PTRN13_OFS              },
  { "TRG_SRC_EN_PTRN14"             , WD2_TRG_SRC_EN_PTRN14_REG             , WD2_TRG_SRC_EN_PTRN14_MASK             , WD2_TRG_SRC_EN_PTRN14_OFS             },
  { "TRG_STATE_PTRN14"              , WD2_TRG_STATE_PTRN14_REG              , WD2_TRG_STATE_PTRN14_MASK              , WD2_TRG_STATE_PTRN14_OFS              },
  { "TRG_SRC_EN_PTRN15"             , WD2_TRG_SRC_EN_PTRN15_REG             , WD2_TRG_SRC_EN_PTRN15_MASK             , WD2_TRG_SRC_EN_PTRN15_OFS             },
  { "TRG_STATE_PTRN15"              , WD2_TRG_STATE_PTRN15_REG              , WD2_TRG_STATE_PTRN15_MASK              , WD2_TRG_STATE_PTRN15_OFS              },
  { "TRG_SRC_EN_PTRN16"             , WD2_TRG_SRC_EN_PTRN16_REG             , WD2_TRG_SRC_EN_PTRN16_MASK             , WD2_TRG_SRC_EN_PTRN16_OFS             },
  { "TRG_STATE_PTRN16"              , WD2_TRG_STATE_PTRN16_REG              , WD2_TRG_STATE_PTRN16_MASK              , WD2_TRG_STATE_PTRN16_OFS              },
  { "TRG_SRC_EN_PTRN17"             , WD2_TRG_SRC_EN_PTRN17_REG             , WD2_TRG_SRC_EN_PTRN17_MASK             , WD2_TRG_SRC_EN_PTRN17_OFS             },
  { "TRG_STATE_PTRN17"              , WD2_TRG_STATE_PTRN17_REG              , WD2_TRG_STATE_PTRN17_MASK              , WD2_TRG_STATE_PTRN17_OFS              },
  { "TRG_SRC_EN_PTRN18"             , WD2_TRG_SRC_EN_PTRN18_REG             , WD2_TRG_SRC_EN_PTRN18_MASK             , WD2_TRG_SRC_EN_PTRN18_OFS             },
  { "TRG_STATE_PTRN18"              , WD2_TRG_STATE_PTRN18_REG              , WD2_TRG_STATE_PTRN18_MASK              , WD2_TRG_STATE_PTRN18_OFS              },
  { "ADV_TRG_CTRL"                  , WD2_ADV_TRG_CTRL_REG                  , WD2_ADV_TRG_CTRL_MASK                  , WD2_ADV_TRG_CTRL_OFS                  },
  { "ADV_TRG_CH_CAL0"               , WD2_ADV_TRG_CH_CAL0_REG               , WD2_ADV_TRG_CH_CAL0_MASK               , WD2_ADV_TRG_CH_CAL0_OFS               },
  { "ADV_TRG_CH_CAL1"               , WD2_ADV_TRG_CH_CAL1_REG               , WD2_ADV_TRG_CH_CAL1_MASK               , WD2_ADV_TRG_CH_CAL1_OFS               },
  { "ADV_TRG_CH_CAL2"               , WD2_ADV_TRG_CH_CAL2_REG               , WD2_ADV_TRG_CH_CAL2_MASK               , WD2_ADV_TRG_CH_CAL2_OFS               },
  { "ADV_TRG_CH_CAL3"               , WD2_ADV_TRG_CH_CAL3_REG               , WD2_ADV_TRG_CH_CAL3_MASK               , WD2_ADV_TRG_CH_CAL3_OFS               },
  { "ADV_TRG_PED_CFG"               , WD2_ADV_TRG_PED_CFG_REG               , WD2_ADV_TRG_PED_CFG_MASK               , WD2_ADV_TRG_PED_CFG_OFS               },
  { "ADV_TRG_THR0"                  , WD2_ADV_TRG_THR0_REG                  , WD2_ADV_TRG_THR0_MASK                  , WD2_ADV_TRG_THR0_OFS                  },
  { "ADV_TRG_THR1"                  , WD2_ADV_TRG_THR1_REG                  , WD2_ADV_TRG_THR1_MASK                  , WD2_ADV_TRG_THR1_OFS                  },
  { "ADV_TRG_THR2"                  , WD2_ADV_TRG_THR2_REG                  , WD2_ADV_TRG_THR2_MASK                  , WD2_ADV_TRG_THR2_OFS                  },
  { "ADV_TRG_TX_CHK_WORD0"          , WD2_ADV_TRG_TX_CHK_WORD0_REG          , WD2_ADV_TRG_TX_CHK_WORD0_MASK          , WD2_ADV_TRG_TX_CHK_WORD0_OFS          },
  { "ADV_TRG_TX_CHK_WORD1"          , WD2_ADV_TRG_TX_CHK_WORD1_REG          , WD2_ADV_TRG_TX_CHK_WORD1_MASK          , WD2_ADV_TRG_TX_CHK_WORD1_OFS          },
  { "ADV_TRG_TDC_CH_MASK"           , WD2_ADV_TRG_TDC_CH_MASK_REG           , WD2_ADV_TRG_TDC_CH_MASK_MASK           , WD2_ADV_TRG_TDC_CH_MASK_OFS           },
  { "ADV_TRG_CFG_12"                , WD2_ADV_TRG_CFG_12_REG                , WD2_ADV_TRG_CFG_12_MASK                , WD2_ADV_TRG_CFG_12_OFS                },
  { "ADV_TRG_CFG_13"                , WD2_ADV_TRG_CFG_13_REG                , WD2_ADV_TRG_CFG_13_MASK                , WD2_ADV_TRG_CFG_13_OFS                },
  { "ADV_TRG_CFG_14"                , WD2_ADV_TRG_CFG_14_REG                , WD2_ADV_TRG_CFG_14_MASK                , WD2_ADV_TRG_CFG_14_OFS                },
  { "ADV_TRG_CFG_15"                , WD2_ADV_TRG_CFG_15_REG                , WD2_ADV_TRG_CFG_15_MASK                , WD2_ADV_TRG_CFG_15_OFS                },
  { "ADV_TRG_CFG_16"                , WD2_ADV_TRG_CFG_16_REG                , WD2_ADV_TRG_CFG_16_MASK                , WD2_ADV_TRG_CFG_16_OFS                },
  { "ADV_TRG_CFG_17"                , WD2_ADV_TRG_CFG_17_REG                , WD2_ADV_TRG_CFG_17_MASK                , WD2_ADV_TRG_CFG_17_OFS                },
  { "ADV_TRG_CFG_18"                , WD2_ADV_TRG_CFG_18_REG                , WD2_ADV_TRG_CFG_18_MASK                , WD2_ADV_TRG_CFG_18_OFS                },
  { "ADV_TRG_CFG_19"                , WD2_ADV_TRG_CFG_19_REG                , WD2_ADV_TRG_CFG_19_MASK                , WD2_ADV_TRG_CFG_19_OFS                },
  { "SET_TIME_LSB"                  , WD2_SET_TIME_LSB_REG                  , WD2_SET_TIME_LSB_MASK                  , WD2_SET_TIME_LSB_OFS                  },
  { "SET_TIME_MSB"                  , WD2_SET_TIME_MSB_REG                  , WD2_SET_TIME_MSB_MASK                  , WD2_SET_TIME_MSB_OFS                  },
  { "MCX_TX_SIG_SEL"                , WD2_MCX_TX_SIG_SEL_REG                , WD2_MCX_TX_SIG_SEL_MASK                , WD2_MCX_TX_SIG_SEL_OFS                },
  { "MCX_RX_SIG_SEL"                , WD2_MCX_RX_SIG_SEL_REG                , WD2_MCX_RX_SIG_SEL_MASK                , WD2_MCX_RX_SIG_SEL_OFS                },
  { "CRC32_REG_BANK"                , WD2_CRC32_REG_BANK_REG                , WD2_CRC32_REG_BANK_MASK                , WD2_CRC32_REG_BANK_OFS                },
  { "BOARD_MAGIC"                   , WD2_BOARD_MAGIC_REG                   , WD2_BOARD_MAGIC_MASK                   , WD2_BOARD_MAGIC_OFS                   },
  { "VENDOR_ID"                     , WD2_VENDOR_ID_REG                     , WD2_VENDOR_ID_MASK                     , WD2_VENDOR_ID_OFS                     },
  { "BOARD_TYPE"                    , WD2_BOARD_TYPE_REG                    , WD2_BOARD_TYPE_MASK                    , WD2_BOARD_TYPE_OFS                    },
  { "BOARD_REVISION"                , WD2_BOARD_REVISION_REG                , WD2_BOARD_REVISION_MASK                , WD2_BOARD_REVISION_OFS                },
  { "BOARD_VARIANT"                 , WD2_BOARD_VARIANT_REG                 , WD2_BOARD_VARIANT_MASK                 , WD2_BOARD_VARIANT_OFS                 },
  { "REG_LAYOUT_COMP_LEVEL"         , WD2_REG_LAYOUT_COMP_LEVEL_REG         , WD2_REG_LAYOUT_COMP_LEVEL_MASK         , WD2_REG_LAYOUT_COMP_LEVEL_OFS         },
  { "REG_LAYOUT_VERSION"            , WD2_REG_LAYOUT_VERSION_REG            , WD2_REG_LAYOUT_VERSION_MASK            , WD2_REG_LAYOUT_VERSION_OFS            },
  { "FW_BUILD_YEAR"                 , WD2_FW_BUILD_YEAR_REG                 , WD2_FW_BUILD_YEAR_MASK                 , WD2_FW_BUILD_YEAR_OFS                 },
  { "FW_BUILD_MONTH"                , WD2_FW_BUILD_MONTH_REG                , WD2_FW_BUILD_MONTH_MASK                , WD2_FW_BUILD_MONTH_OFS                },
  { "FW_BUILD_DAY"                  , WD2_FW_BUILD_DAY_REG                  , WD2_FW_BUILD_DAY_MASK                  , WD2_FW_BUILD_DAY_OFS                  },
  { "FW_COMPAT_LEVEL"               , WD2_FW_COMPAT_LEVEL_REG               , WD2_FW_COMPAT_LEVEL_MASK               , WD2_FW_COMPAT_LEVEL_OFS               },
  { "FW_BUILD_HOUR"                 , WD2_FW_BUILD_HOUR_REG                 , WD2_FW_BUILD_HOUR_MASK                 , WD2_FW_BUILD_HOUR_OFS                 },
  { "FW_BUILD_MINUTE"               , WD2_FW_BUILD_MINUTE_REG               , WD2_FW_BUILD_MINUTE_MASK               , WD2_FW_BUILD_MINUTE_OFS               },
  { "FW_BUILD_SECOND"               , WD2_FW_BUILD_SECOND_REG               , WD2_FW_BUILD_SECOND_MASK               , WD2_FW_BUILD_SECOND_OFS               },
  { "SW_BUILD_YEAR"                 , WD2_SW_BUILD_YEAR_REG                 , WD2_SW_BUILD_YEAR_MASK                 , WD2_SW_BUILD_YEAR_OFS                 },
  { "SW_BUILD_MONTH"                , WD2_SW_BUILD_MONTH_REG                , WD2_SW_BUILD_MONTH_MASK                , WD2_SW_BUILD_MONTH_OFS                },
  { "SW_BUILD_DAY"                  , WD2_SW_BUILD_DAY_REG                  , WD2_SW_BUILD_DAY_MASK                  , WD2_SW_BUILD_DAY_OFS                  },
  { "SW_BUILD_HOUR"                 , WD2_SW_BUILD_HOUR_REG                 , WD2_SW_BUILD_HOUR_MASK                 , WD2_SW_BUILD_HOUR_OFS                 },
  { "SW_BUILD_MINUTE"               , WD2_SW_BUILD_MINUTE_REG               , WD2_SW_BUILD_MINUTE_MASK               , WD2_SW_BUILD_MINUTE_OFS               },
  { "SW_BUILD_SECOND"               , WD2_SW_BUILD_SECOND_REG               , WD2_SW_BUILD_SECOND_MASK               , WD2_SW_BUILD_SECOND_OFS               },
  { "FW_GIT_HASH_TAG"               , WD2_FW_GIT_HASH_TAG_REG               , WD2_FW_GIT_HASH_TAG_MASK               , WD2_FW_GIT_HASH_TAG_OFS               },
  { "SW_GIT_HASH_TAG"               , WD2_SW_GIT_HASH_TAG_REG               , WD2_SW_GIT_HASH_TAG_MASK               , WD2_SW_GIT_HASH_TAG_OFS               },
  { "PROTOCOL_VERSION"              , WD2_PROTOCOL_VERSION_REG              , WD2_PROTOCOL_VERSION_MASK              , WD2_PROTOCOL_VERSION_OFS              },
  { "SERIAL_NUMBER"                 , WD2_SERIAL_NUMBER_REG                 , WD2_SERIAL_NUMBER_MASK                 , WD2_SERIAL_NUMBER_OFS                 },
  { "TEMPERATURE"                   , WD2_TEMPERATURE_REG                   , WD2_TEMPERATURE_MASK                   , WD2_TEMPERATURE_OFS                   },
  { "OVERTEMP"                      , WD2_OVERTEMP_REG                      , WD2_OVERTEMP_MASK                      , WD2_OVERTEMP_OFS                      },
  { "EXT_CLK_ACTIVE"                , WD2_EXT_CLK_ACTIVE_REG                , WD2_EXT_CLK_ACTIVE_MASK                , WD2_EXT_CLK_ACTIVE_OFS                },
  { "DAQ_CLK_DEF_PHASE_OK"          , WD2_DAQ_CLK_DEF_PHASE_OK_REG          , WD2_DAQ_CLK_DEF_PHASE_OK_MASK          , WD2_DAQ_CLK_DEF_PHASE_OK_OFS          },
  { "DAQ_CLK_DEF_PHASE_CHKD"        , WD2_DAQ_CLK_DEF_PHASE_CHKD_REG        , WD2_DAQ_CLK_DEF_PHASE_CHKD_MASK        , WD2_DAQ_CLK_DEF_PHASE_CHKD_OFS        },
  { "DRS_CONFIG_DONE"               , WD2_DRS_CONFIG_DONE_REG               , WD2_DRS_CONFIG_DONE_MASK               , WD2_DRS_CONFIG_DONE_OFS               },
  { "BOARD_SEL"                     , WD2_BOARD_SEL_REG                     , WD2_BOARD_SEL_MASK                     , WD2_BOARD_SEL_OFS                     },
  { "SERIAL_BUSY"                   , WD2_SERIAL_BUSY_REG                   , WD2_SERIAL_BUSY_MASK                   , WD2_SERIAL_BUSY_OFS                   },
  { "PACKAGER_BUSY"                 , WD2_PACKAGER_BUSY_REG                 , WD2_PACKAGER_BUSY_MASK                 , WD2_PACKAGER_BUSY_OFS                 },
  { "DRS_CTRL_BUSY"                 , WD2_DRS_CTRL_BUSY_REG                 , WD2_DRS_CTRL_BUSY_MASK                 , WD2_DRS_CTRL_BUSY_OFS                 },
  { "SYS_BUSY"                      , WD2_SYS_BUSY_REG                      , WD2_SYS_BUSY_MASK                      , WD2_SYS_BUSY_OFS                      },
  { "HV_BOARD_PLUGGED"              , WD2_HV_BOARD_PLUGGED_REG              , WD2_HV_BOARD_PLUGGED_MASK              , WD2_HV_BOARD_PLUGGED_OFS              },
  { "BACKPLANE_PLUGGED"             , WD2_BACKPLANE_PLUGGED_REG             , WD2_BACKPLANE_PLUGGED_MASK             , WD2_BACKPLANE_PLUGGED_OFS             },
  { "SYS_DCM_LOCK"                  , WD2_SYS_DCM_LOCK_REG                  , WD2_SYS_DCM_LOCK_MASK                  , WD2_SYS_DCM_LOCK_OFS                  },
  { "DAQ_PLL_LOCK"                  , WD2_DAQ_PLL_LOCK_REG                  , WD2_DAQ_PLL_LOCK_MASK                  , WD2_DAQ_PLL_LOCK_OFS                  },
  { "OSERDES_PLL_LOCK_DCB"          , WD2_OSERDES_PLL_LOCK_DCB_REG          , WD2_OSERDES_PLL_LOCK_DCB_MASK          , WD2_OSERDES_PLL_LOCK_DCB_OFS          },
  { "OSERDES_PLL_LOCK_TCB"          , WD2_OSERDES_PLL_LOCK_TCB_REG          , WD2_OSERDES_PLL_LOCK_TCB_MASK          , WD2_OSERDES_PLL_LOCK_TCB_OFS          },
  { "ISERDES_PLL_LOCK_0"            , WD2_ISERDES_PLL_LOCK_0_REG            , WD2_ISERDES_PLL_LOCK_0_MASK            , WD2_ISERDES_PLL_LOCK_0_OFS            },
  { "ISERDES_PLL_LOCK_1"            , WD2_ISERDES_PLL_LOCK_1_REG            , WD2_ISERDES_PLL_LOCK_1_MASK            , WD2_ISERDES_PLL_LOCK_1_OFS            },
  { "DRS_PLL_LOCK_0"                , WD2_DRS_PLL_LOCK_0_REG                , WD2_DRS_PLL_LOCK_0_MASK                , WD2_DRS_PLL_LOCK_0_OFS                },
  { "DRS_PLL_LOCK_1"                , WD2_DRS_PLL_LOCK_1_REG                , WD2_DRS_PLL_LOCK_1_MASK                , WD2_DRS_PLL_LOCK_1_OFS                },
  { "LMK_PLL_LOCK"                  , WD2_LMK_PLL_LOCK_REG                  , WD2_LMK_PLL_LOCK_MASK                  , WD2_LMK_PLL_LOCK_OFS                  },
  { "DRS_STOP_CELL_0"               , WD2_DRS_STOP_CELL_0_REG               , WD2_DRS_STOP_CELL_0_MASK               , WD2_DRS_STOP_CELL_0_OFS               },
  { "DRS_STOP_CELL_1"               , WD2_DRS_STOP_CELL_1_REG               , WD2_DRS_STOP_CELL_1_MASK               , WD2_DRS_STOP_CELL_1_OFS               },
  { "DRS_STOP_WSR_0"                , WD2_DRS_STOP_WSR_0_REG                , WD2_DRS_STOP_WSR_0_MASK                , WD2_DRS_STOP_WSR_0_OFS                },
  { "DRS_STOP_WSR_1"                , WD2_DRS_STOP_WSR_1_REG                , WD2_DRS_STOP_WSR_1_MASK                , WD2_DRS_STOP_WSR_1_OFS                },
  { "DRS_SAMPLE_FREQ"               , WD2_DRS_SAMPLE_FREQ_REG               , WD2_DRS_SAMPLE_FREQ_MASK               , WD2_DRS_SAMPLE_FREQ_OFS               },
  { "ADC_SAMPLE_FREQ"               , WD2_ADC_SAMPLE_FREQ_REG               , WD2_ADC_SAMPLE_FREQ_MASK               , WD2_ADC_SAMPLE_FREQ_OFS               },
  { "TDC_SAMPLE_FREQ"               , WD2_TDC_SAMPLE_FREQ_REG               , WD2_TDC_SAMPLE_FREQ_MASK               , WD2_TDC_SAMPLE_FREQ_OFS               },
  { "HV_VER"                        , WD2_HV_VER_REG                        , WD2_HV_VER_MASK                        , WD2_HV_VER_OFS                        },
  { "HV_I_MEAS_0"                   , WD2_HV_I_MEAS_0_REG                   , WD2_HV_I_MEAS_0_MASK                   , WD2_HV_I_MEAS_0_OFS                   },
  { "HV_I_MEAS_1"                   , WD2_HV_I_MEAS_1_REG                   , WD2_HV_I_MEAS_1_MASK                   , WD2_HV_I_MEAS_1_OFS                   },
  { "HV_I_MEAS_2"                   , WD2_HV_I_MEAS_2_REG                   , WD2_HV_I_MEAS_2_MASK                   , WD2_HV_I_MEAS_2_OFS                   },
  { "HV_I_MEAS_3"                   , WD2_HV_I_MEAS_3_REG                   , WD2_HV_I_MEAS_3_MASK                   , WD2_HV_I_MEAS_3_OFS                   },
  { "HV_I_MEAS_4"                   , WD2_HV_I_MEAS_4_REG                   , WD2_HV_I_MEAS_4_MASK                   , WD2_HV_I_MEAS_4_OFS                   },
  { "HV_I_MEAS_5"                   , WD2_HV_I_MEAS_5_REG                   , WD2_HV_I_MEAS_5_MASK                   , WD2_HV_I_MEAS_5_OFS                   },
  { "HV_I_MEAS_6"                   , WD2_HV_I_MEAS_6_REG                   , WD2_HV_I_MEAS_6_MASK                   , WD2_HV_I_MEAS_6_OFS                   },
  { "HV_I_MEAS_7"                   , WD2_HV_I_MEAS_7_REG                   , WD2_HV_I_MEAS_7_MASK                   , WD2_HV_I_MEAS_7_OFS                   },
  { "HV_I_MEAS_8"                   , WD2_HV_I_MEAS_8_REG                   , WD2_HV_I_MEAS_8_MASK                   , WD2_HV_I_MEAS_8_OFS                   },
  { "HV_I_MEAS_9"                   , WD2_HV_I_MEAS_9_REG                   , WD2_HV_I_MEAS_9_MASK                   , WD2_HV_I_MEAS_9_OFS                   },
  { "HV_I_MEAS_10"                  , WD2_HV_I_MEAS_10_REG                  , WD2_HV_I_MEAS_10_MASK                  , WD2_HV_I_MEAS_10_OFS                  },
  { "HV_I_MEAS_11"                  , WD2_HV_I_MEAS_11_REG                  , WD2_HV_I_MEAS_11_MASK                  , WD2_HV_I_MEAS_11_OFS                  },
  { "HV_I_MEAS_12"                  , WD2_HV_I_MEAS_12_REG                  , WD2_HV_I_MEAS_12_MASK                  , WD2_HV_I_MEAS_12_OFS                  },
  { "HV_I_MEAS_13"                  , WD2_HV_I_MEAS_13_REG                  , WD2_HV_I_MEAS_13_MASK                  , WD2_HV_I_MEAS_13_OFS                  },
  { "HV_I_MEAS_14"                  , WD2_HV_I_MEAS_14_REG                  , WD2_HV_I_MEAS_14_MASK                  , WD2_HV_I_MEAS_14_OFS                  },
  { "HV_I_MEAS_15"                  , WD2_HV_I_MEAS_15_REG                  , WD2_HV_I_MEAS_15_MASK                  , WD2_HV_I_MEAS_15_OFS                  },
  { "HV_U_BASE_MEAS"                , WD2_HV_U_BASE_MEAS_REG                , WD2_HV_U_BASE_MEAS_MASK                , WD2_HV_U_BASE_MEAS_OFS                },
  { "HV_TEMP_0"                     , WD2_HV_TEMP_0_REG                     , WD2_HV_TEMP_0_MASK                     , WD2_HV_TEMP_0_OFS                     },
  { "HV_TEMP_1"                     , WD2_HV_TEMP_1_REG                     , WD2_HV_TEMP_1_MASK                     , WD2_HV_TEMP_1_OFS                     },
  { "HV_TEMP_2"                     , WD2_HV_TEMP_2_REG                     , WD2_HV_TEMP_2_MASK                     , WD2_HV_TEMP_2_OFS                     },
  { "HV_TEMP_3"                     , WD2_HV_TEMP_3_REG                     , WD2_HV_TEMP_3_MASK                     , WD2_HV_TEMP_3_OFS                     },
  { "SCALER_0"                      , WD2_SCALER_0_REG                      , WD2_SCALER_0_MASK                      , WD2_SCALER_0_OFS                      },
  { "SCALER_1"                      , WD2_SCALER_1_REG                      , WD2_SCALER_1_MASK                      , WD2_SCALER_1_OFS                      },
  { "SCALER_2"                      , WD2_SCALER_2_REG                      , WD2_SCALER_2_MASK                      , WD2_SCALER_2_OFS                      },
  { "SCALER_3"                      , WD2_SCALER_3_REG                      , WD2_SCALER_3_MASK                      , WD2_SCALER_3_OFS                      },
  { "SCALER_4"                      , WD2_SCALER_4_REG                      , WD2_SCALER_4_MASK                      , WD2_SCALER_4_OFS                      },
  { "SCALER_5"                      , WD2_SCALER_5_REG                      , WD2_SCALER_5_MASK                      , WD2_SCALER_5_OFS                      },
  { "SCALER_6"                      , WD2_SCALER_6_REG                      , WD2_SCALER_6_MASK                      , WD2_SCALER_6_OFS                      },
  { "SCALER_7"                      , WD2_SCALER_7_REG                      , WD2_SCALER_7_MASK                      , WD2_SCALER_7_OFS                      },
  { "SCALER_8"                      , WD2_SCALER_8_REG                      , WD2_SCALER_8_MASK                      , WD2_SCALER_8_OFS                      },
  { "SCALER_9"                      , WD2_SCALER_9_REG                      , WD2_SCALER_9_MASK                      , WD2_SCALER_9_OFS                      },
  { "SCALER_10"                     , WD2_SCALER_10_REG                     , WD2_SCALER_10_MASK                     , WD2_SCALER_10_OFS                     },
  { "SCALER_11"                     , WD2_SCALER_11_REG                     , WD2_SCALER_11_MASK                     , WD2_SCALER_11_OFS                     },
  { "SCALER_12"                     , WD2_SCALER_12_REG                     , WD2_SCALER_12_MASK                     , WD2_SCALER_12_OFS                     },
  { "SCALER_13"                     , WD2_SCALER_13_REG                     , WD2_SCALER_13_MASK                     , WD2_SCALER_13_OFS                     },
  { "SCALER_14"                     , WD2_SCALER_14_REG                     , WD2_SCALER_14_MASK                     , WD2_SCALER_14_OFS                     },
  { "SCALER_15"                     , WD2_SCALER_15_REG                     , WD2_SCALER_15_MASK                     , WD2_SCALER_15_OFS                     },
  { "SCALER_PTRN_TRG"               , WD2_SCALER_PTRN_TRG_REG               , WD2_SCALER_PTRN_TRG_MASK               , WD2_SCALER_PTRN_TRG_OFS               },
  { "SCALER_EXT_TRG"                , WD2_SCALER_EXT_TRG_REG                , WD2_SCALER_EXT_TRG_MASK                , WD2_SCALER_EXT_TRG_OFS                },
  { "SCALER_EXT_CLK"                , WD2_SCALER_EXT_CLK_REG                , WD2_SCALER_EXT_CLK_MASK                , WD2_SCALER_EXT_CLK_OFS                },
  { "SCALER_TIME_STAMP_LSB"         , WD2_SCALER_TIME_STAMP_LSB_REG         , WD2_SCALER_TIME_STAMP_LSB_MASK         , WD2_SCALER_TIME_STAMP_LSB_OFS         },
  { "SCALER_TIME_STAMP_MSB"         , WD2_SCALER_TIME_STAMP_MSB_REG         , WD2_SCALER_TIME_STAMP_MSB_MASK         , WD2_SCALER_TIME_STAMP_MSB_OFS         },
  { "TIME_LSB"                      , WD2_TIME_LSB_REG                      , WD2_TIME_LSB_MASK                      , WD2_TIME_LSB_OFS                      },
  { "TIME_MSB"                      , WD2_TIME_MSB_REG                      , WD2_TIME_MSB_MASK                      , WD2_TIME_MSB_OFS                      },
  { "COMP_CH_STAT"                  , WD2_COMP_CH_STAT_REG                  , WD2_COMP_CH_STAT_MASK                  , WD2_COMP_CH_STAT_OFS                  },
  { "EVENT_TX_RATE"                 , WD2_EVENT_TX_RATE_REG                 , WD2_EVENT_TX_RATE_MASK                 , WD2_EVENT_TX_RATE_OFS                 },
  { "EVENT_NUMBER"                  , WD2_EVENT_NUMBER_REG                  , WD2_EVENT_NUMBER_MASK                  , WD2_EVENT_NUMBER_OFS                  },
  { "TRB_FLAG_NEW"                  , WD2_TRB_FLAG_NEW_REG                  , WD2_TRB_FLAG_NEW_MASK                  , WD2_TRB_FLAG_NEW_OFS                  },
  { "TRB_FLAG_PARITY_ERROR"         , WD2_TRB_FLAG_PARITY_ERROR_REG         , WD2_TRB_FLAG_PARITY_ERROR_MASK         , WD2_TRB_FLAG_PARITY_ERROR_OFS         },
  { "TRB_PARITY_ERROR_COUNT"        , WD2_TRB_PARITY_ERROR_COUNT_REG        , WD2_TRB_PARITY_ERROR_COUNT_MASK        , WD2_TRB_PARITY_ERROR_COUNT_OFS        },
  { "TRB_INFO_LSB"                  , WD2_TRB_INFO_LSB_REG                  , WD2_TRB_INFO_LSB_MASK                  , WD2_TRB_INFO_LSB_OFS                  },
  { "TRB_INFO_MSB"                  , WD2_TRB_INFO_MSB_REG                  , WD2_TRB_INFO_MSB_MASK                  , WD2_TRB_INFO_MSB_OFS                  },
  { "ADV_TRG_TRIG_CELL"             , WD2_ADV_TRG_TRIG_CELL_REG             , WD2_ADV_TRG_TRIG_CELL_MASK             , WD2_ADV_TRG_TRIG_CELL_OFS             },
  { "ADV_TRG_STAT_1"                , WD2_ADV_TRG_STAT_1_REG                , WD2_ADV_TRG_STAT_1_MASK                , WD2_ADV_TRG_STAT_1_OFS                },
  { "ADV_TRG_STAT_2"                , WD2_ADV_TRG_STAT_2_REG                , WD2_ADV_TRG_STAT_2_MASK                , WD2_ADV_TRG_STAT_2_OFS                },
  { "ADV_TRG_STAT_3"                , WD2_ADV_TRG_STAT_3_REG                , WD2_ADV_TRG_STAT_3_MASK                , WD2_ADV_TRG_STAT_3_OFS                },
  { "ADV_TRG_STAT_4"                , WD2_ADV_TRG_STAT_4_REG                , WD2_ADV_TRG_STAT_4_MASK                , WD2_ADV_TRG_STAT_4_OFS                },
  { "MAX_DRS_ADC_PKT_SAMPLES"       , WD2_MAX_DRS_ADC_PKT_SAMPLES_REG       , WD2_MAX_DRS_ADC_PKT_SAMPLES_MASK       , WD2_MAX_DRS_ADC_PKT_SAMPLES_OFS       },
  { "MAX_TDC_PKT_SAMPLES"           , WD2_MAX_TDC_PKT_SAMPLES_REG           , WD2_MAX_TDC_PKT_SAMPLES_MASK           , WD2_MAX_TDC_PKT_SAMPLES_OFS           },
  { "MAX_TRG_PKT_SAMPLES"           , WD2_MAX_TRG_PKT_SAMPLES_REG           , WD2_MAX_TRG_PKT_SAMPLES_MASK           , WD2_MAX_TRG_PKT_SAMPLES_OFS           },
  { "MAX_SCL_PKT_SAMPLES"           , WD2_MAX_SCL_PKT_SAMPLES_REG           , WD2_MAX_SCL_PKT_SAMPLES_MASK           , WD2_MAX_SCL_PKT_SAMPLES_OFS           },
  { "TRIGGER_DAQ_CLK_CAL_MOD"       , WD2_TRIGGER_DAQ_CLK_CAL_MOD_REG       , WD2_TRIGGER_DAQ_CLK_CAL_MOD_MASK       , WD2_TRIGGER_DAQ_CLK_CAL_MOD_OFS       },
  { "ADC_RST_MOD"                   , WD2_ADC_RST_MOD_REG                   , WD2_ADC_RST_MOD_MASK                   , WD2_ADC_RST_MOD_OFS                   },
  { "CLK_SEL_AND_DRS_CLK_DIV_MOD"   , WD2_CLK_SEL_AND_DRS_CLK_DIV_MOD_REG   , WD2_CLK_SEL_AND_DRS_CLK_DIV_MOD_MASK   , WD2_CLK_SEL_AND_DRS_CLK_DIV_MOD_OFS   },
  { "EXT_CLK_FREQ_MOD"              , WD2_EXT_CLK_FREQ_MOD_REG              , WD2_EXT_CLK_FREQ_MOD_MASK              , WD2_EXT_CLK_FREQ_MOD_OFS              },
  { "LOCAL_CLK_FREQ_MOD"            , WD2_LOCAL_CLK_FREQ_MOD_REG            , WD2_LOCAL_CLK_FREQ_MOD_MASK            , WD2_LOCAL_CLK_FREQ_MOD_OFS            },
  { "DRS_CTRL_MOD"                  , WD2_DRS_CTRL_MOD_REG                  , WD2_DRS_CTRL_MOD_MASK                  , WD2_DRS_CTRL_MOD_OFS                  },
  { "DRS_WSR_MOD"                   , WD2_DRS_WSR_MOD_REG                   , WD2_DRS_WSR_MOD_MASK                   , WD2_DRS_WSR_MOD_OFS                   },
  { "DRS_WCR_MOD"                   , WD2_DRS_WCR_MOD_REG                   , WD2_DRS_WCR_MOD_MASK                   , WD2_DRS_WCR_MOD_OFS                   },
  { "COM_PLD_SIZE_MOD"              , WD2_COM_PLD_SIZE_MOD_REG              , WD2_COM_PLD_SIZE_MOD_MASK              , WD2_COM_PLD_SIZE_MOD_OFS              },
  { "ADC_SAMPLE_DIV_MOD"            , WD2_ADC_SAMPLE_DIV_MOD_REG            , WD2_ADC_SAMPLE_DIV_MOD_MASK            , WD2_ADC_SAMPLE_DIV_MOD_OFS            },
  { "DAC0_A_MOD"                    , WD2_DAC0_A_MOD_REG                    , WD2_DAC0_A_MOD_MASK                    , WD2_DAC0_A_MOD_OFS                    },
  { "DAC0_B_MOD"                    , WD2_DAC0_B_MOD_REG                    , WD2_DAC0_B_MOD_MASK                    , WD2_DAC0_B_MOD_OFS                    },
  { "DAC0_C_MOD"                    , WD2_DAC0_C_MOD_REG                    , WD2_DAC0_C_MOD_MASK                    , WD2_DAC0_C_MOD_OFS                    },
  { "DAC0_D_MOD"                    , WD2_DAC0_D_MOD_REG                    , WD2_DAC0_D_MOD_MASK                    , WD2_DAC0_D_MOD_OFS                    },
  { "DAC0_E_MOD"                    , WD2_DAC0_E_MOD_REG                    , WD2_DAC0_E_MOD_MASK                    , WD2_DAC0_E_MOD_OFS                    },
  { "DAC0_F_MOD"                    , WD2_DAC0_F_MOD_REG                    , WD2_DAC0_F_MOD_MASK                    , WD2_DAC0_F_MOD_OFS                    },
  { "DAC0_G_MOD"                    , WD2_DAC0_G_MOD_REG                    , WD2_DAC0_G_MOD_MASK                    , WD2_DAC0_G_MOD_OFS                    },
  { "DAC0_H_MOD"                    , WD2_DAC0_H_MOD_REG                    , WD2_DAC0_H_MOD_MASK                    , WD2_DAC0_H_MOD_OFS                    },
  { "DAC1_A_MOD"                    , WD2_DAC1_A_MOD_REG                    , WD2_DAC1_A_MOD_MASK                    , WD2_DAC1_A_MOD_OFS                    },
  { "DAC1_B_MOD"                    , WD2_DAC1_B_MOD_REG                    , WD2_DAC1_B_MOD_MASK                    , WD2_DAC1_B_MOD_OFS                    },
  { "DAC1_C_MOD"                    , WD2_DAC1_C_MOD_REG                    , WD2_DAC1_C_MOD_MASK                    , WD2_DAC1_C_MOD_OFS                    },
  { "DAC1_D_MOD"                    , WD2_DAC1_D_MOD_REG                    , WD2_DAC1_D_MOD_MASK                    , WD2_DAC1_D_MOD_OFS                    },
  { "DAC1_E_MOD"                    , WD2_DAC1_E_MOD_REG                    , WD2_DAC1_E_MOD_MASK                    , WD2_DAC1_E_MOD_OFS                    },
  { "DAC1_F_MOD"                    , WD2_DAC1_F_MOD_REG                    , WD2_DAC1_F_MOD_MASK                    , WD2_DAC1_F_MOD_OFS                    },
  { "DAC1_G_MOD"                    , WD2_DAC1_G_MOD_REG                    , WD2_DAC1_G_MOD_MASK                    , WD2_DAC1_G_MOD_OFS                    },
  { "DAC1_H_MOD"                    , WD2_DAC1_H_MOD_REG                    , WD2_DAC1_H_MOD_MASK                    , WD2_DAC1_H_MOD_OFS                    },
  { "DAC2_A_MOD"                    , WD2_DAC2_A_MOD_REG                    , WD2_DAC2_A_MOD_MASK                    , WD2_DAC2_A_MOD_OFS                    },
  { "DAC2_B_MOD"                    , WD2_DAC2_B_MOD_REG                    , WD2_DAC2_B_MOD_MASK                    , WD2_DAC2_B_MOD_OFS                    },
  { "DAC2_C_MOD"                    , WD2_DAC2_C_MOD_REG                    , WD2_DAC2_C_MOD_MASK                    , WD2_DAC2_C_MOD_OFS                    },
  { "DAC2_D_MOD"                    , WD2_DAC2_D_MOD_REG                    , WD2_DAC2_D_MOD_MASK                    , WD2_DAC2_D_MOD_OFS                    },
  { "DAC2_E_MOD"                    , WD2_DAC2_E_MOD_REG                    , WD2_DAC2_E_MOD_MASK                    , WD2_DAC2_E_MOD_OFS                    },
  { "DAC2_F_MOD"                    , WD2_DAC2_F_MOD_REG                    , WD2_DAC2_F_MOD_MASK                    , WD2_DAC2_F_MOD_OFS                    },
  { "DAC2_G_MOD"                    , WD2_DAC2_G_MOD_REG                    , WD2_DAC2_G_MOD_MASK                    , WD2_DAC2_G_MOD_OFS                    },
  { "DAC2_H_MOD"                    , WD2_DAC2_H_MOD_REG                    , WD2_DAC2_H_MOD_MASK                    , WD2_DAC2_H_MOD_OFS                    },
  { "FE_0_MOD"                      , WD2_FE_0_MOD_REG                      , WD2_FE_0_MOD_MASK                      , WD2_FE_0_MOD_OFS                      },
  { "FE_1_MOD"                      , WD2_FE_1_MOD_REG                      , WD2_FE_1_MOD_MASK                      , WD2_FE_1_MOD_OFS                      },
  { "FE_2_MOD"                      , WD2_FE_2_MOD_REG                      , WD2_FE_2_MOD_MASK                      , WD2_FE_2_MOD_OFS                      },
  { "FE_3_MOD"                      , WD2_FE_3_MOD_REG                      , WD2_FE_3_MOD_MASK                      , WD2_FE_3_MOD_OFS                      },
  { "FE_4_MOD"                      , WD2_FE_4_MOD_REG                      , WD2_FE_4_MOD_MASK                      , WD2_FE_4_MOD_OFS                      },
  { "FE_5_MOD"                      , WD2_FE_5_MOD_REG                      , WD2_FE_5_MOD_MASK                      , WD2_FE_5_MOD_OFS                      },
  { "FE_6_MOD"                      , WD2_FE_6_MOD_REG                      , WD2_FE_6_MOD_MASK                      , WD2_FE_6_MOD_OFS                      },
  { "FE_7_MOD"                      , WD2_FE_7_MOD_REG                      , WD2_FE_7_MOD_MASK                      , WD2_FE_7_MOD_OFS                      },
  { "FE_8_MOD"                      , WD2_FE_8_MOD_REG                      , WD2_FE_8_MOD_MASK                      , WD2_FE_8_MOD_OFS                      },
  { "FE_9_MOD"                      , WD2_FE_9_MOD_REG                      , WD2_FE_9_MOD_MASK                      , WD2_FE_9_MOD_OFS                      },
  { "FE_10_MOD"                     , WD2_FE_10_MOD_REG                     , WD2_FE_10_MOD_MASK                     , WD2_FE_10_MOD_OFS                     },
  { "FE_11_MOD"                     , WD2_FE_11_MOD_REG                     , WD2_FE_11_MOD_MASK                     , WD2_FE_11_MOD_OFS                     },
  { "FE_12_MOD"                     , WD2_FE_12_MOD_REG                     , WD2_FE_12_MOD_MASK                     , WD2_FE_12_MOD_OFS                     },
  { "FE_13_MOD"                     , WD2_FE_13_MOD_REG                     , WD2_FE_13_MOD_MASK                     , WD2_FE_13_MOD_OFS                     },
  { "FE_14_MOD"                     , WD2_FE_14_MOD_REG                     , WD2_FE_14_MOD_MASK                     , WD2_FE_14_MOD_OFS                     },
  { "FE_15_MOD"                     , WD2_FE_15_MOD_REG                     , WD2_FE_15_MOD_MASK                     , WD2_FE_15_MOD_OFS                     },
  { "HV_U_TARGET_0_MOD"             , WD2_HV_U_TARGET_0_MOD_REG             , WD2_HV_U_TARGET_0_MOD_MASK             , WD2_HV_U_TARGET_0_MOD_OFS             },
  { "HV_U_TARGET_1_MOD"             , WD2_HV_U_TARGET_1_MOD_REG             , WD2_HV_U_TARGET_1_MOD_MASK             , WD2_HV_U_TARGET_1_MOD_OFS             },
  { "HV_U_TARGET_2_MOD"             , WD2_HV_U_TARGET_2_MOD_REG             , WD2_HV_U_TARGET_2_MOD_MASK             , WD2_HV_U_TARGET_2_MOD_OFS             },
  { "HV_U_TARGET_3_MOD"             , WD2_HV_U_TARGET_3_MOD_REG             , WD2_HV_U_TARGET_3_MOD_MASK             , WD2_HV_U_TARGET_3_MOD_OFS             },
  { "HV_U_TARGET_4_MOD"             , WD2_HV_U_TARGET_4_MOD_REG             , WD2_HV_U_TARGET_4_MOD_MASK             , WD2_HV_U_TARGET_4_MOD_OFS             },
  { "HV_U_TARGET_5_MOD"             , WD2_HV_U_TARGET_5_MOD_REG             , WD2_HV_U_TARGET_5_MOD_MASK             , WD2_HV_U_TARGET_5_MOD_OFS             },
  { "HV_U_TARGET_6_MOD"             , WD2_HV_U_TARGET_6_MOD_REG             , WD2_HV_U_TARGET_6_MOD_MASK             , WD2_HV_U_TARGET_6_MOD_OFS             },
  { "HV_U_TARGET_7_MOD"             , WD2_HV_U_TARGET_7_MOD_REG             , WD2_HV_U_TARGET_7_MOD_MASK             , WD2_HV_U_TARGET_7_MOD_OFS             },
  { "HV_U_TARGET_8_MOD"             , WD2_HV_U_TARGET_8_MOD_REG             , WD2_HV_U_TARGET_8_MOD_MASK             , WD2_HV_U_TARGET_8_MOD_OFS             },
  { "HV_U_TARGET_9_MOD"             , WD2_HV_U_TARGET_9_MOD_REG             , WD2_HV_U_TARGET_9_MOD_MASK             , WD2_HV_U_TARGET_9_MOD_OFS             },
  { "HV_U_TARGET_10_MOD"            , WD2_HV_U_TARGET_10_MOD_REG            , WD2_HV_U_TARGET_10_MOD_MASK            , WD2_HV_U_TARGET_10_MOD_OFS            },
  { "HV_U_TARGET_11_MOD"            , WD2_HV_U_TARGET_11_MOD_REG            , WD2_HV_U_TARGET_11_MOD_MASK            , WD2_HV_U_TARGET_11_MOD_OFS            },
  { "HV_U_TARGET_12_MOD"            , WD2_HV_U_TARGET_12_MOD_REG            , WD2_HV_U_TARGET_12_MOD_MASK            , WD2_HV_U_TARGET_12_MOD_OFS            },
  { "HV_U_TARGET_13_MOD"            , WD2_HV_U_TARGET_13_MOD_REG            , WD2_HV_U_TARGET_13_MOD_MASK            , WD2_HV_U_TARGET_13_MOD_OFS            },
  { "HV_U_TARGET_14_MOD"            , WD2_HV_U_TARGET_14_MOD_REG            , WD2_HV_U_TARGET_14_MOD_MASK            , WD2_HV_U_TARGET_14_MOD_OFS            },
  { "HV_U_TARGET_15_MOD"            , WD2_HV_U_TARGET_15_MOD_REG            , WD2_HV_U_TARGET_15_MOD_MASK            , WD2_HV_U_TARGET_15_MOD_OFS            },
  { "HV_R_SHUNT_MOD"                , WD2_HV_R_SHUNT_MOD_REG                , WD2_HV_R_SHUNT_MOD_MASK                , WD2_HV_R_SHUNT_MOD_OFS                },
  { "LMK_0_MOD"                     , WD2_LMK_0_MOD_REG                     , WD2_LMK_0_MOD_MASK                     , WD2_LMK_0_MOD_OFS                     },
  { "LMK_1_MOD"                     , WD2_LMK_1_MOD_REG                     , WD2_LMK_1_MOD_MASK                     , WD2_LMK_1_MOD_OFS                     },
  { "LMK_2_MOD"                     , WD2_LMK_2_MOD_REG                     , WD2_LMK_2_MOD_MASK                     , WD2_LMK_2_MOD_OFS                     },
  { "LMK_3_MOD"                     , WD2_LMK_3_MOD_REG                     , WD2_LMK_3_MOD_MASK                     , WD2_LMK_3_MOD_OFS                     },
  { "LMK_4_MOD"                     , WD2_LMK_4_MOD_REG                     , WD2_LMK_4_MOD_MASK                     , WD2_LMK_4_MOD_OFS                     },
  { "LMK_5_MOD"                     , WD2_LMK_5_MOD_REG                     , WD2_LMK_5_MOD_MASK                     , WD2_LMK_5_MOD_OFS                     },
  { "LMK_6_MOD"                     , WD2_LMK_6_MOD_REG                     , WD2_LMK_6_MOD_MASK                     , WD2_LMK_6_MOD_OFS                     },
  { "LMK_7_MOD"                     , WD2_LMK_7_MOD_REG                     , WD2_LMK_7_MOD_MASK                     , WD2_LMK_7_MOD_OFS                     },
  { "LMK_8_MOD"                     , WD2_LMK_8_MOD_REG                     , WD2_LMK_8_MOD_MASK                     , WD2_LMK_8_MOD_OFS                     },
  { "LMK_9_MOD"                     , WD2_LMK_9_MOD_REG                     , WD2_LMK_9_MOD_MASK                     , WD2_LMK_9_MOD_OFS                     },
  { "LMK_11_MOD"                    , WD2_LMK_11_MOD_REG                    , WD2_LMK_11_MOD_MASK                    , WD2_LMK_11_MOD_OFS                    },
  { "LMK_13_MOD"                    , WD2_LMK_13_MOD_REG                    , WD2_LMK_13_MOD_MASK                    , WD2_LMK_13_MOD_OFS                    },
  { "LMK_14_MOD"                    , WD2_LMK_14_MOD_REG                    , WD2_LMK_14_MOD_MASK                    , WD2_LMK_14_MOD_OFS                    },
  { "LMK_15_MOD"                    , WD2_LMK_15_MOD_REG                    , WD2_LMK_15_MOD_MASK                    , WD2_LMK_15_MOD_OFS                    },
  { (const char*)0                  , 0                                     , 0                                      , 0                                     }
};

/******************************************************************************/
/* Control Register Defaults                                                  */
/******************************************************************************/

const unsigned int ctrl_reg_default[] = {
  0xFFFFFFFF,   /* Offset 0x1000 */
  0x14200780,   /* Offset 0x1004 */
  0x00000000,   /* Offset 0x1008 */
  0x00025050,   /* Offset 0x100C */
  0x00FFFFFF,   /* Offset 0x1010 */
  0x02000753,   /* Offset 0x1014 */
  0x000005C0,   /* Offset 0x1018 */
  0x0000FFFF,   /* Offset 0x101C */
  0x00000000,   /* Offset 0x1020 */
  0x00000000,   /* Offset 0x1024 */
  0x00000400,   /* Offset 0x1028 */
  0x00000800,   /* Offset 0x102C */
  0x00001000,   /* Offset 0x1030 */
  0x00000200,   /* Offset 0x1034 */
  0x00000001,   /* Offset 0x1038 */
  0x00000080,   /* Offset 0x103C */
  0x00000000,   /* Offset 0x1040 */
  0x00000000,   /* Offset 0x1044 */
  0x9EC045A0,   /* Offset 0x1048 */
  0x828F0000,   /* Offset 0x104C */
  0x0000FFFF,   /* Offset 0x1050 */
  0x000047B0,   /* Offset 0x1054 */
  0x57105710,   /* Offset 0x1058 */
  0x57105710,   /* Offset 0x105C */
  0x57105710,   /* Offset 0x1060 */
  0x57105710,   /* Offset 0x1064 */
  0x57105710,   /* Offset 0x1068 */
  0x57105710,   /* Offset 0x106C */
  0x57105710,   /* Offset 0x1070 */
  0x57105710,   /* Offset 0x1074 */
  0x00020002,   /* Offset 0x1078 */
  0x00020002,   /* Offset 0x107C */
  0x00020002,   /* Offset 0x1080 */
  0x00020002,   /* Offset 0x1084 */
  0x00020002,   /* Offset 0x1088 */
  0x00020002,   /* Offset 0x108C */
  0x00020002,   /* Offset 0x1090 */
  0x00020002,   /* Offset 0x1094 */
  0x00000000,   /* Offset 0x1098 */
  0x00000000,   /* Offset 0x109C */
  0x00000000,   /* Offset 0x10A0 */
  0x00000000,   /* Offset 0x10A4 */
  0x00000000,   /* Offset 0x10A8 */
  0x00000000,   /* Offset 0x10AC */
  0x00000000,   /* Offset 0x10B0 */
  0x00000000,   /* Offset 0x10B4 */
  0x00000000,   /* Offset 0x10B8 */
  0x00000000,   /* Offset 0x10BC */
  0x00000000,   /* Offset 0x10C0 */
  0x00000000,   /* Offset 0x10C4 */
  0x00000000,   /* Offset 0x10C8 */
  0x00000000,   /* Offset 0x10CC */
  0x00000000,   /* Offset 0x10D0 */
  0x00000000,   /* Offset 0x10D4 */
  0x00002710,   /* Offset 0x10D8 */
  0x00032100,   /* Offset 0x10DC */
  0x00020101,   /* Offset 0x10E0 */
  0x00020102,   /* Offset 0x10E4 */
  0x00000103,   /* Offset 0x10E8 */
  0x00030104,   /* Offset 0x10EC */
  0x00020105,   /* Offset 0x10F0 */
  0x00000106,   /* Offset 0x10F4 */
  0x00026407,   /* Offset 0x10F8 */
  0x10000908,   /* Offset 0x10FC */
  0xA0022A09,   /* Offset 0x1100 */
  0x0082000B,   /* Offset 0x1104 */
  0x029400AD,   /* Offset 0x1108 */
  0x0830100E,   /* Offset 0x110C */
  0xE000200F,   /* Offset 0x1110 */
  0x00A63F00,   /* Offset 0x1114 */
  0x00A63F00,   /* Offset 0x1118 */
  0x00A63F00,   /* Offset 0x111C */
  0x00A63F00,   /* Offset 0x1120 */
  0x00000000,   /* Offset 0x1124 */
  0x00000000,   /* Offset 0x1128 */
  0x04C4B400,   /* Offset 0x112C */
  0x00000000,   /* Offset 0x1130 */
  0x00000000,   /* Offset 0x1134 */
  0x00000000,   /* Offset 0x1138 */
  0x00000000,   /* Offset 0x113C */
  0x00000000,   /* Offset 0x1140 */
  0x00000000,   /* Offset 0x1144 */
  0x00000000,   /* Offset 0x1148 */
  0x00000000,   /* Offset 0x114C */
  0x00000000,   /* Offset 0x1150 */
  0x00000000,   /* Offset 0x1154 */
  0x00000000,   /* Offset 0x1158 */
  0x00000000,   /* Offset 0x115C */
  0x00000000,   /* Offset 0x1160 */
  0x00000000,   /* Offset 0x1164 */
  0x00000000,   /* Offset 0x1168 */
  0x00000000,   /* Offset 0x116C */
  0x00000000,   /* Offset 0x1170 */
  0x00000000,   /* Offset 0x1174 */
  0x00000000,   /* Offset 0x1178 */
  0x00000000,   /* Offset 0x117C */
  0x00000000,   /* Offset 0x1180 */
  0x00000000,   /* Offset 0x1184 */
  0x00000000,   /* Offset 0x1188 */
  0x00000000,   /* Offset 0x118C */
  0x00000000,   /* Offset 0x1190 */
  0x00000000,   /* Offset 0x1194 */
  0x00000000,   /* Offset 0x1198 */
  0x00000000,   /* Offset 0x119C */
  0x00000000,   /* Offset 0x11A0 */
  0x00000000,   /* Offset 0x11A4 */
  0x00000000,   /* Offset 0x11A8 */
  0x00000000,   /* Offset 0x11AC */
  0x00000000,   /* Offset 0x11B0 */
  0x00000000,   /* Offset 0x11B4 */
  0x00000000,   /* Offset 0x11B8 */
  0x00000000,   /* Offset 0x11BC */
  0x00000000,   /* Offset 0x11C0 */
  0x00000000,   /* Offset 0x11C4 */
  0x00000000,   /* Offset 0x11C8 */
  0x00000000,   /* Offset 0x11CC */
  0x00000000,   /* Offset 0x11D0 */
  0x00000000,   /* Offset 0x11D4 */
  0x00000000,   /* Offset 0x11D8 */
  0x00000000,   /* Offset 0x11DC */
  0x00000000,   /* Offset 0x11E0 */
  0x00000000,   /* Offset 0x11E4 */
  0x00000000,   /* Offset 0x11E8 */
  0x00000000,   /* Offset 0x11EC */
  0x00000000,   /* Offset 0x11F0 */
  0x00000000,   /* Offset 0x11F4 */
  0x00000000,   /* Offset 0x11F8 */
  0x00000000,   /* Offset 0x11FC */
  0x00000000,   /* Offset 0x1200 */
  0x00000000,   /* Offset 0x1204 */
  0x00000000,   /* Offset 0x1208 */
  0x00000000,   /* Offset 0x120C */
  0x00000000,   /* Offset 0x1210 */
  0x00000000,   /* Offset 0x1214 */
  0x00000000,   /* Offset 0x1218 */
  0x00000000,   /* Offset 0x121C */
  0x00000000,   /* Offset 0x1220 */
  0x00000000    /* Offset 0x1224 */
};

#endif /* WD2_DONT_INCLUDE_VARS */

#endif /* WD2_REGISTER_MAP_V9 */

/******************************************************************************/

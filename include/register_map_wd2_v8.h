/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WaveDream2
 *
 *  Author  :  schmid_e (Author of generation script)
 *  Created :  28.02.2022 07:19:28
 *
 *  Register Layout Version :  8
 *
 *  Description :  Register map definitions.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#ifndef __REGISTER_MAP_V8_H__
#define __REGISTER_MAP_V8_H__

#include "register_map_wd2.h"

#ifdef WD2_REGISTER_MAP_V8

#ifndef WD2_DONT_INCLUDE_REG_ACCESS_VARS
#include "drv_plb_wd2_reg_bank.h"
#endif

/******************************************************************************/
/* definitions                                                                */
/******************************************************************************/

/*
 * Register Offsets
 */

#define WD2_CTRL_REG_BASE_OFS   0x1000
#define WD2_STAT_REG_BASE_OFS   0x0000

/* *** Control Registers *** */
#define WD2_REG_WDB_LOC                                 0x1000
#define WD2_REG_CTRL                                    0x1004
#define WD2_REG_CAL_CTRL                                0x1008
#define WD2_REG_CLK_CTRL                                0x100C
#define WD2_REG_DRS_CTRL                                0x1010
#define WD2_REG_COM_CTRL                                0x1014
#define WD2_REG_COM_PLD_SIZE                            0x1018
#define WD2_REG_DRS_CH_TX_EN                            0x101C
#define WD2_REG_ADC_CH_TX_EN                            0x1020
#define WD2_REG_TDC_CH_TX_EN                            0x1024
#define WD2_REG_DRS_TX_SAMPLES                          0x1028
#define WD2_REG_ADC_TX_SAMPLES                          0x102C
#define WD2_REG_TDC_TX_SAMPLES                          0x1030
#define WD2_REG_TRG_TX_SAMPLES                          0x1034
#define WD2_REG_ADC_SAMPLE_DIV                          0x1038
#define WD2_REG_ZERO_SUPR                               0x103C
#define WD2_REG_RST                                     0x1040
#define WD2_REG_APLY_CFG                                0x1044
#define WD2_REG_DAC0_A_B                                0x1048
#define WD2_REG_DAC0_C_D                                0x104C
#define WD2_REG_DAC0_E_F                                0x1050
#define WD2_REG_DAC0_G_H                                0x1054
#define WD2_REG_DAC1_A_B                                0x1058
#define WD2_REG_DAC1_C_D                                0x105C
#define WD2_REG_DAC1_E_F                                0x1060
#define WD2_REG_DAC1_G_H                                0x1064
#define WD2_REG_DAC2_A_B                                0x1068
#define WD2_REG_DAC2_C_D                                0x106C
#define WD2_REG_DAC2_E_F                                0x1070
#define WD2_REG_DAC2_G_H                                0x1074
#define WD2_REG_FE_CFG_0_1                              0x1078
#define WD2_REG_FE_CFG_2_3                              0x107C
#define WD2_REG_FE_CFG_4_5                              0x1080
#define WD2_REG_FE_CFG_6_7                              0x1084
#define WD2_REG_FE_CFG_8_9                              0x1088
#define WD2_REG_FE_CFG_10_11                            0x108C
#define WD2_REG_FE_CFG_12_13                            0x1090
#define WD2_REG_FE_CFG_14_15                            0x1094
#define WD2_REG_HV_U_TARGET_0                           0x1098
#define WD2_REG_HV_U_TARGET_1                           0x109C
#define WD2_REG_HV_U_TARGET_2                           0x10A0
#define WD2_REG_HV_U_TARGET_3                           0x10A4
#define WD2_REG_HV_U_TARGET_4                           0x10A8
#define WD2_REG_HV_U_TARGET_5                           0x10AC
#define WD2_REG_HV_U_TARGET_6                           0x10B0
#define WD2_REG_HV_U_TARGET_7                           0x10B4
#define WD2_REG_HV_U_TARGET_8                           0x10B8
#define WD2_REG_HV_U_TARGET_9                           0x10BC
#define WD2_REG_HV_U_TARGET_10                          0x10C0
#define WD2_REG_HV_U_TARGET_11                          0x10C4
#define WD2_REG_HV_U_TARGET_12                          0x10C8
#define WD2_REG_HV_U_TARGET_13                          0x10CC
#define WD2_REG_HV_U_TARGET_14                          0x10D0
#define WD2_REG_HV_U_TARGET_15                          0x10D4
#define WD2_REG_HV_R_SHUNT                              0x10D8
#define WD2_REG_LMK_0                                   0x10DC
#define WD2_REG_LMK_1                                   0x10E0
#define WD2_REG_LMK_2                                   0x10E4
#define WD2_REG_LMK_3                                   0x10E8
#define WD2_REG_LMK_4                                   0x10EC
#define WD2_REG_LMK_5                                   0x10F0
#define WD2_REG_LMK_6                                   0x10F4
#define WD2_REG_LMK_7                                   0x10F8
#define WD2_REG_LMK_8                                   0x10FC
#define WD2_REG_LMK_9                                   0x1100
#define WD2_REG_LMK_11                                  0x1104
#define WD2_REG_LMK_13                                  0x1108
#define WD2_REG_LMK_14                                  0x110C
#define WD2_REG_LMK_15                                  0x1110
#define WD2_REG_ADC_CFG_IND_TX                          0x1114
#define WD2_REG_ADC_PM_CLK_ENH                          0x1118
#define WD2_REG_ADC_TEST_OFFS_OM                        0x111C
#define WD2_REG_ADC_OUT_VREF                            0x1120
#define WD2_REG_ADC_USR_PATT                            0x1124
#define WD2_REG_ADC_SER_RES_SR                          0x1128
#define WD2_REG_ADC_USR_IO_SYNC                         0x112C
#define WD2_REG_ADC_0_CH_A_CFG                          0x1130
#define WD2_REG_ADC_0_CH_B_CFG                          0x1134
#define WD2_REG_ADC_0_CH_C_CFG                          0x1138
#define WD2_REG_ADC_0_CH_D_CFG                          0x113C
#define WD2_REG_ADC_0_CH_E_CFG                          0x1140
#define WD2_REG_ADC_0_CH_F_CFG                          0x1144
#define WD2_REG_ADC_0_CH_G_CFG                          0x1148
#define WD2_REG_ADC_0_CH_H_CFG                          0x114C
#define WD2_REG_ADC_0_CH_DCO_CFG                        0x1150
#define WD2_REG_ADC_0_CH_FCO_CFG                        0x1154
#define WD2_REG_ADC_1_CH_A_CFG                          0x1158
#define WD2_REG_ADC_1_CH_B_CFG                          0x115C
#define WD2_REG_ADC_1_CH_C_CFG                          0x1160
#define WD2_REG_ADC_1_CH_D_CFG                          0x1164
#define WD2_REG_ADC_1_CH_E_CFG                          0x1168
#define WD2_REG_ADC_1_CH_F_CFG                          0x116C
#define WD2_REG_ADC_1_CH_G_CFG                          0x1170
#define WD2_REG_ADC_1_CH_H_CFG                          0x1174
#define WD2_REG_ADC_1_CH_DCO_CFG                        0x1178
#define WD2_REG_ADC_1_CH_FCO_CFG                        0x117C
#define WD2_REG_TRG_CFG                                 0x1180
#define WD2_REG_TRG_SRC_POL                             0x1184
#define WD2_REG_TRG_AUTO_PERIOD                         0x1188
#define WD2_REG_TRG_PTRN_EN                             0x118C
#define WD2_REG_TRG_SRC_EN_PTRN0                        0x1190
#define WD2_REG_TRG_STATE_PTRN0                         0x1194
#define WD2_REG_TRG_SRC_EN_PTRN1                        0x1198
#define WD2_REG_TRG_STATE_PTRN1                         0x119C
#define WD2_REG_TRG_SRC_EN_PTRN2                        0x11A0
#define WD2_REG_TRG_STATE_PTRN2                         0x11A4
#define WD2_REG_TRG_SRC_EN_PTRN3                        0x11A8
#define WD2_REG_TRG_STATE_PTRN3                         0x11AC
#define WD2_REG_TRG_SRC_EN_PTRN4                        0x11B0
#define WD2_REG_TRG_STATE_PTRN4                         0x11B4
#define WD2_REG_TRG_SRC_EN_PTRN5                        0x11B8
#define WD2_REG_TRG_STATE_PTRN5                         0x11BC
#define WD2_REG_TRG_SRC_EN_PTRN6                        0x11C0
#define WD2_REG_TRG_STATE_PTRN6                         0x11C4
#define WD2_REG_TRG_SRC_EN_PTRN7                        0x11C8
#define WD2_REG_TRG_STATE_PTRN7                         0x11CC
#define WD2_REG_TRG_SRC_EN_PTRN8                        0x11D0
#define WD2_REG_TRG_STATE_PTRN8                         0x11D4
#define WD2_REG_TRG_SRC_EN_PTRN9                        0x11D8
#define WD2_REG_TRG_STATE_PTRN9                         0x11DC
#define WD2_REG_TRG_SRC_EN_PTRN10                       0x11E0
#define WD2_REG_TRG_STATE_PTRN10                        0x11E4
#define WD2_REG_TRG_SRC_EN_PTRN11                       0x11E8
#define WD2_REG_TRG_STATE_PTRN11                        0x11EC
#define WD2_REG_TRG_SRC_EN_PTRN12                       0x11F0
#define WD2_REG_TRG_STATE_PTRN12                        0x11F4
#define WD2_REG_TRG_SRC_EN_PTRN13                       0x11F8
#define WD2_REG_TRG_STATE_PTRN13                        0x11FC
#define WD2_REG_TRG_SRC_EN_PTRN14                       0x1200
#define WD2_REG_TRG_STATE_PTRN14                        0x1204
#define WD2_REG_TRG_SRC_EN_PTRN15                       0x1208
#define WD2_REG_TRG_STATE_PTRN15                        0x120C
#define WD2_REG_TRG_SRC_EN_PTRN16                       0x1210
#define WD2_REG_TRG_STATE_PTRN16                        0x1214
#define WD2_REG_TRG_SRC_EN_PTRN17                       0x1218
#define WD2_REG_TRG_STATE_PTRN17                        0x121C
#define WD2_REG_TRG_SRC_EN_PTRN18                       0x1220
#define WD2_REG_TRG_STATE_PTRN18                        0x1224
#define WD2_REG_ADV_TRG_CTRL                            0x1228
#define WD2_REG_ADV_TRG_CH_CAL0                         0x122C
#define WD2_REG_ADV_TRG_CH_CAL1                         0x1230
#define WD2_REG_ADV_TRG_CH_CAL2                         0x1234
#define WD2_REG_ADV_TRG_CH_CAL3                         0x1238
#define WD2_REG_ADV_TRG_PED_CFG                         0x123C
#define WD2_REG_ADV_TRG_THR0                            0x1240
#define WD2_REG_ADV_TRG_THR1                            0x1244
#define WD2_REG_ADV_TRG_THR2                            0x1248
#define WD2_REG_ADV_TRG_TX_CHK_WORD0                    0x124C
#define WD2_REG_ADV_TRG_TX_CHK_WORD1                    0x1250
#define WD2_REG_ADV_TRG_TDC_CH_MASK                     0x1254
#define WD2_REG_ADV_TRG_CFG12                           0x1258
#define WD2_REG_ADV_TRG_CFG13                           0x125C
#define WD2_REG_ADV_TRG_CFG14                           0x1260
#define WD2_REG_ADV_TRG_CFG15                           0x1264
#define WD2_REG_ADV_TRG_CFG16                           0x1268
#define WD2_REG_ADV_TRG_CFG17                           0x126C
#define WD2_REG_ADV_TRG_CFG18                           0x1270
#define WD2_REG_ADV_TRG_CFG19                           0x1274
#define WD2_REG_DBG_SIG_SEL                             0x1278
#define WD2_REG_DRS_TRG_RO_DLY                          0x127C
#define WD2_REG_CRC32_REG_BANK                          0x1280

/* *** Status Registers *** */
#define WD2_REG_HW_VER                                  0x0000
#define WD2_REG_REG_LAYOUT_VER                          0x0004
#define WD2_REG_FW_BUILD_DATE                           0x0008
#define WD2_REG_FW_BUILD_TIME                           0x000C
#define WD2_REG_SW_BUILD_DATE                           0x0010
#define WD2_REG_SW_BUILD_TIME                           0x0014
#define WD2_REG_FW_GIT_HASH_TAG                         0x0018
#define WD2_REG_SW_GIT_HASH_TAG                         0x001C
#define WD2_REG_PROT_VER                                0x0020
#define WD2_REG_SN                                      0x0024
#define WD2_REG_STATUS                                  0x0028
#define WD2_REG_PLL_LOCK                                0x002C
#define WD2_REG_DRS_STOP_CELL                           0x0030
#define WD2_REG_DRS_STOP_WSR                            0x0034
#define WD2_REG_DRS_SAMPLE_FREQ                         0x0038
#define WD2_REG_ADC_SAMPLE_FREQ                         0x003C
#define WD2_REG_TDC_SAMPLE_FREQ                         0x0040
#define WD2_REG_ADC_INFO                                0x0044
#define WD2_REG_HV_VER                                  0x0048
#define WD2_REG_HV_I_MEAS_0                             0x004C
#define WD2_REG_HV_I_MEAS_1                             0x0050
#define WD2_REG_HV_I_MEAS_2                             0x0054
#define WD2_REG_HV_I_MEAS_3                             0x0058
#define WD2_REG_HV_I_MEAS_4                             0x005C
#define WD2_REG_HV_I_MEAS_5                             0x0060
#define WD2_REG_HV_I_MEAS_6                             0x0064
#define WD2_REG_HV_I_MEAS_7                             0x0068
#define WD2_REG_HV_I_MEAS_8                             0x006C
#define WD2_REG_HV_I_MEAS_9                             0x0070
#define WD2_REG_HV_I_MEAS_10                            0x0074
#define WD2_REG_HV_I_MEAS_11                            0x0078
#define WD2_REG_HV_I_MEAS_12                            0x007C
#define WD2_REG_HV_I_MEAS_13                            0x0080
#define WD2_REG_HV_I_MEAS_14                            0x0084
#define WD2_REG_HV_I_MEAS_15                            0x0088
#define WD2_REG_HV_U_BASE_MEAS                          0x008C
#define WD2_REG_HV_TEMP_0                               0x0090
#define WD2_REG_HV_TEMP_1                               0x0094
#define WD2_REG_HV_TEMP_2                               0x0098
#define WD2_REG_HV_TEMP_3                               0x009C
#define WD2_REG_SCALER_0                                0x00A0
#define WD2_REG_SCALER_1                                0x00A4
#define WD2_REG_SCALER_2                                0x00A8
#define WD2_REG_SCALER_3                                0x00AC
#define WD2_REG_SCALER_4                                0x00B0
#define WD2_REG_SCALER_5                                0x00B4
#define WD2_REG_SCALER_6                                0x00B8
#define WD2_REG_SCALER_7                                0x00BC
#define WD2_REG_SCALER_8                                0x00C0
#define WD2_REG_SCALER_9                                0x00C4
#define WD2_REG_SCALER_10                               0x00C8
#define WD2_REG_SCALER_11                               0x00CC
#define WD2_REG_SCALER_12                               0x00D0
#define WD2_REG_SCALER_13                               0x00D4
#define WD2_REG_SCALER_14                               0x00D8
#define WD2_REG_SCALER_15                               0x00DC
#define WD2_REG_SCALER_PTRN_TRG                         0x00E0
#define WD2_REG_SCALER_EXT_TRG                          0x00E4
#define WD2_REG_SCALER_EXT_CLK                          0x00E8
#define WD2_REG_SCALER_TIME_STAMP_LSB                   0x00EC
#define WD2_REG_SCALER_TIME_STAMP_MSB                   0x00F0
#define WD2_REG_SYS_TIME                                0x00F4
#define WD2_REG_COMP_CH_STAT                            0x00F8
#define WD2_REG_EVENT_TX_RATE                           0x00FC
#define WD2_REG_EVENT_NR                                0x0100
#define WD2_REG_TRB_INFO_STAT                           0x0104
#define WD2_REG_TRB_INFO_LSB                            0x0108
#define WD2_REG_TRB_INFO_MSB                            0x010C
#define WD2_REG_ADV_TRG_TRIG_CELL                       0x0110
#define WD2_REG_ADV_TRG_STAT1                           0x0114
#define WD2_REG_ADV_TRG_STAT2                           0x0118
#define WD2_REG_ADV_TRG_STAT3                           0x011C
#define WD2_REG_ADV_TRG_STAT4                           0x0120
#define WD2_REG_MAX_DRS_ADC_PKT_SAMPLES                 0x0124
#define WD2_REG_MAX_TDC_PKT_SAMPLES                     0x0128
#define WD2_REG_MAX_TRG_PKT_SAMPLES                     0x012C
#define WD2_REG_MAX_SCL_PKT_SAMPLES                     0x0130
#define WD2_REG_CLK_CTRL_MOD_FLAG                       0x0134
#define WD2_REG_DRS_MOD_FLAG                            0x0138
#define WD2_REG_COM_PLD_SIZE_MOD_FLAG                   0x013C
#define WD2_REG_ADC_SAMPLE_DIV_MOD_FLAG                 0x0140
#define WD2_REG_DAC_0_1_MOD_FLAG                        0x0144
#define WD2_REG_DAC_2_MOD_FLAG                          0x0148
#define WD2_REG_FE_0_15_MOD_FLAG                        0x014C
#define WD2_REG_HV_U_TARGET_0_7_MOD_FLAG                0x0150
#define WD2_REG_HV_U_TARGET_8_15_MOD_FLAG               0x0154
#define WD2_REG_HV_MOD_FLAG                             0x0158
#define WD2_REG_LMK_0_7_MOD_FLAG                        0x015C
#define WD2_REG_LMK_8_15_MOD_FLAG                       0x0160

/*
 * Bit Positions
 */

/* ****** Control Register 0 [0x1000]: WDB_LOC - Location where the WD2 is plugged in (Default: 0xFFFFFFFF) ****** */

/* CRATE_ID - ID of the crate where the current board is plugged in */
#define WD2_CRATE_ID_REG                                           WD2_REG_WDB_LOC
#define WD2_CRATE_ID_MASK                                               0x00FF0000
#define WD2_CRATE_ID_OFS                                                        16

/* SLOT_ID - ID of the slot where the current board is plugged in */
#define WD2_SLOT_ID_REG                                            WD2_REG_WDB_LOC
#define WD2_SLOT_ID_MASK                                                0x000000FF
#define WD2_SLOT_ID_OFS                                                          0



/* ****** Control Register 1 [0x1004]: CTRL - DAQ control register (Default: 0x14200780) ****** */

/* VALID_DELAY_ADC - Delay of the data valid at the ISERDES of the ADCs (delay = value + 1) */
#define WD2_VALID_DELAY_ADC_REG                                       WD2_REG_CTRL
#define WD2_VALID_DELAY_ADC_MASK                                        0x3F000000
#define WD2_VALID_DELAY_ADC_OFS                                                 24

/* DAQ_DATA_PHASE - Phase step setting of the PLL generating the common DAQ clock */
#define WD2_DAQ_DATA_PHASE_REG                                        WD2_REG_CTRL
#define WD2_DAQ_DATA_PHASE_MASK                                         0x00FF0000
#define WD2_DAQ_DATA_PHASE_OFS                                                  16

/* DRS_CLR_RSR_AFTER_RO - Clear the read shift register (remove the token) after each readout */
#define WD2_DRS_CLR_RSR_AFTER_RO_REG                                  WD2_REG_CTRL
#define WD2_DRS_CLR_RSR_AFTER_RO_MASK                                   0x00000400
#define WD2_DRS_CLR_RSR_AFTER_RO_OFS                                            10

/* COMP_POWER_EN - Comparator power enable */
#define WD2_COMP_POWER_EN_REG                                         WD2_REG_CTRL
#define WD2_COMP_POWER_EN_MASK                                          0x00000200
#define WD2_COMP_POWER_EN_OFS                                                    9

/* DRS_READOUT_MODE - 0:start from first bin, 1:start from domino stop */
#define WD2_DRS_READOUT_MODE_REG                                      WD2_REG_CTRL
#define WD2_DRS_READOUT_MODE_MASK                                       0x00000100
#define WD2_DRS_READOUT_MODE_OFS                                                 8

/* DRS_WAVE_CONTINUOUS - 0:stop domino wave during readout, 1:keep it running */
#define WD2_DRS_WAVE_CONTINUOUS_REG                                   WD2_REG_CTRL
#define WD2_DRS_WAVE_CONTINUOUS_MASK                                    0x00000080
#define WD2_DRS_WAVE_CONTINUOUS_OFS                                              7

/* DRS_CONFIGURE - write a "1" to trigger the DRS chip register configuration */
#define WD2_DRS_CONFIGURE_REG                                         WD2_REG_CTRL
#define WD2_DRS_CONFIGURE_MASK                                          0x00000040
#define WD2_DRS_CONFIGURE_OFS                                                    6

/* DAQ_SOFT_TRIGGER - write a "1" to stop the DRS chip & read the data to RAM */
#define WD2_DAQ_SOFT_TRIGGER_REG                                      WD2_REG_CTRL
#define WD2_DAQ_SOFT_TRIGGER_MASK                                       0x00000020
#define WD2_DAQ_SOFT_TRIGGER_OFS                                                 5

/* DAQ_AUTO - Auto-Trigger readout state machine every 0.5s if no other trigger (like "auto" acquisition on scope) */
#define WD2_DAQ_AUTO_REG                                              WD2_REG_CTRL
#define WD2_DAQ_AUTO_MASK                                               0x00000004
#define WD2_DAQ_AUTO_OFS                                                         2

/* DAQ_NORMAL - Restart readout state machine automatically after readout (like "normal" acquisition on scope) */
#define WD2_DAQ_NORMAL_REG                                            WD2_REG_CTRL
#define WD2_DAQ_NORMAL_MASK                                             0x00000002
#define WD2_DAQ_NORMAL_OFS                                                       1

/* DAQ_SINGLE - Start readout state machine automatically and stop after readout (like "single" acquisition on scope) */
#define WD2_DAQ_SINGLE_REG                                            WD2_REG_CTRL
#define WD2_DAQ_SINGLE_MASK                                             0x00000001
#define WD2_DAQ_SINGLE_OFS                                                       0



/* ****** Control Register 2 [0x1008]: CAL_CTRL - Clock and Calibration Control (Default: 0x00000000) ****** */

/* DRS_0_TIMING_REF_SEL - Select timing reference signal for DRS 0: 0 = oscillator / 1 = LMK (CAL_CTRL_A) */
#define WD2_DRS_0_TIMING_REF_SEL_REG                              WD2_REG_CAL_CTRL
#define WD2_DRS_0_TIMING_REF_SEL_MASK                                   0x00000008
#define WD2_DRS_0_TIMING_REF_SEL_OFS                                             3

/* DRS_1_TIMING_REF_SEL - Select timing reference signal for DRS 1: 0 = oscillator / 1 = LMK  (CAL_CTRL_B) */
#define WD2_DRS_1_TIMING_REF_SEL_REG                              WD2_REG_CAL_CTRL
#define WD2_DRS_1_TIMING_REF_SEL_MASK                                   0x00000004
#define WD2_DRS_1_TIMING_REF_SEL_OFS                                             2

/* CALIB_BUFFER_EN - Enable buffers driving the calib. signal to the frontend MUX (BUFFER_CTRL) */
#define WD2_CALIB_BUFFER_EN_REG                                   WD2_REG_CAL_CTRL
#define WD2_CALIB_BUFFER_EN_MASK                                        0x00000002
#define WD2_CALIB_BUFFER_EN_OFS                                                  1

/* TIMING_CALIB_SIGNAL_EN - switch on (1) / off (0) 100 MHz calibration signal for DRS chip (TCA_CTRL) */
#define WD2_TIMING_CALIB_SIGNAL_EN_REG                            WD2_REG_CAL_CTRL
#define WD2_TIMING_CALIB_SIGNAL_EN_MASK                                 0x00000001
#define WD2_TIMING_CALIB_SIGNAL_EN_OFS                                           0



/* ****** Control Register 3 [0x100C]: CLK_CTRL - Clock Control (Default: 0x00025064) ****** */

/* TRIG_DAQ_CLK_CAL_CHK - Trigger DAQ clock calibration check */
#define WD2_TRIG_DAQ_CLK_CAL_CHK_REG                              WD2_REG_CLK_CTRL
#define WD2_TRIG_DAQ_CLK_CAL_CHK_MASK                                   0x01000000
#define WD2_TRIG_DAQ_CLK_CAL_CHK_OFS                                            24

/* DAQ_CLK_SRC_SEL - DAQ clock source select: 0 = DCB clock / 1 = on board oscillator (CLK_SEL) */
#define WD2_DAQ_CLK_SRC_SEL_REG                                   WD2_REG_CLK_CTRL
#define WD2_DAQ_CLK_SRC_SEL_MASK                                        0x00020000
#define WD2_DAQ_CLK_SRC_SEL_OFS                                                 17

/* EXT_CLK_IN_SEL - External clk input select: 0 = backplane / 1 = MCX connector (CLK_SEL_EXT) */
#define WD2_EXT_CLK_IN_SEL_REG                                    WD2_REG_CLK_CTRL
#define WD2_EXT_CLK_IN_SEL_MASK                                         0x00010000
#define WD2_EXT_CLK_IN_SEL_OFS                                                  16

/* EXT_CLK_FREQ - External clock frequency (MCX or backplane) in MHz */
#define WD2_EXT_CLK_FREQ_REG                                      WD2_REG_CLK_CTRL
#define WD2_EXT_CLK_FREQ_MASK                                           0x0000FF00
#define WD2_EXT_CLK_FREQ_OFS                                                     8

/* LOCAL_CLK_FREQ - Local (on board) oscillator frequency in MHz */
#define WD2_LOCAL_CLK_FREQ_REG                                    WD2_REG_CLK_CTRL
#define WD2_LOCAL_CLK_FREQ_MASK                                         0x000000FF
#define WD2_LOCAL_CLK_FREQ_OFS                                                   0



/* ****** Control Register 4 [0x1010]: DRS_CTRL - DRS4 Control and Configuration Registers (Default: 0x00FFFFFF) ****** */

/* DRS_WSRLOOP - Internally Connect WSRIN to WSROUT (if set to 1) */
#define WD2_DRS_WSRLOOP_REG                                       WD2_REG_DRS_CTRL
#define WD2_DRS_WSRLOOP_MASK                                            0x00040000
#define WD2_DRS_WSRLOOP_OFS                                                     18

/* DRS_PLLEN - Internal PLL Enable (0 = disable, 1 = enable) */
#define WD2_DRS_PLLEN_REG                                         WD2_REG_DRS_CTRL
#define WD2_DRS_PLLEN_MASK                                              0x00020000
#define WD2_DRS_PLLEN_OFS                                                       17

/* DRS_DMODE - Domino Mode Control (0 = single shot, 1 = continuous) */
#define WD2_DRS_DMODE_REG                                         WD2_REG_DRS_CTRL
#define WD2_DRS_DMODE_MASK                                              0x00010000
#define WD2_DRS_DMODE_OFS                                                       16

/* DRS_WSR - DRS4 Write Shift Register (0xD) */
#define WD2_DRS_WSR_REG                                           WD2_REG_DRS_CTRL
#define WD2_DRS_WSR_MASK                                                0x0000FF00
#define WD2_DRS_WSR_OFS                                                          8

/* DRS_WCR - DRS4 Write Configuration Register (0xE) */
#define WD2_DRS_WCR_REG                                           WD2_REG_DRS_CTRL
#define WD2_DRS_WCR_MASK                                                0x000000FF
#define WD2_DRS_WCR_OFS                                                          0



/* ****** Control Register 5 [0x1014]: COM_CTRL - Communication Control Register (Default: 0x02000753) ****** */

/* DCB_SERDES_TRAIN - Enable training pattern for DCB SERDES connection */
#define WD2_DCB_SERDES_TRAIN_REG                                  WD2_REG_COM_CTRL
#define WD2_DCB_SERDES_TRAIN_MASK                                       0x80000000
#define WD2_DCB_SERDES_TRAIN_OFS                                                31

/* TCB_SERDES_TRAIN - Enable training pattern for TCB SERDES connection */
#define WD2_TCB_SERDES_TRAIN_REG                                  WD2_REG_COM_CTRL
#define WD2_TCB_SERDES_TRAIN_MASK                                       0x40000000
#define WD2_TCB_SERDES_TRAIN_OFS                                                30

/* TRG_TX_EN - enable transmission of advanced trigger output data */
#define WD2_TRG_TX_EN_REG                                         WD2_REG_COM_CTRL
#define WD2_TRG_TX_EN_MASK                                              0x08000000
#define WD2_TRG_TX_EN_OFS                                                       27

/* SCL_TX_EN - Enable transmission of scaler data */
#define WD2_SCL_TX_EN_REG                                         WD2_REG_COM_CTRL
#define WD2_SCL_TX_EN_MASK                                              0x04000000
#define WD2_SCL_TX_EN_OFS                                                       26

/* SERDES_COM_EN - Enable SERDES communication to backplane */
#define WD2_SERDES_COM_EN_REG                                     WD2_REG_COM_CTRL
#define WD2_SERDES_COM_EN_MASK                                          0x02000000
#define WD2_SERDES_COM_EN_OFS                                                   25

/* ETH_COM_EN - Enable ethernet communication */
#define WD2_ETH_COM_EN_REG                                        WD2_REG_COM_CTRL
#define WD2_ETH_COM_EN_MASK                                             0x01000000
#define WD2_ETH_COM_EN_OFS                                                      24

/* INTER_PKG_DELAY - Delay between transmission of two UDP packages in 8ns steps */
#define WD2_INTER_PKG_DELAY_REG                                   WD2_REG_COM_CTRL
#define WD2_INTER_PKG_DELAY_MASK                                        0x00FFFFFF
#define WD2_INTER_PKG_DELAY_OFS                                                  0



/* ****** Control Register 6 [0x1018]: COM_PLD_SIZE - Maximum Payload Size (Default: 0x000005C0) ****** */

/* FIRST_PKG_DLY - Delay of first data packet of an event (resolution 1.6us) */
#define WD2_FIRST_PKG_DLY_REG                                 WD2_REG_COM_PLD_SIZE
#define WD2_FIRST_PKG_DLY_MASK                                          0xFFFC0000
#define WD2_FIRST_PKG_DLY_OFS                                                   18

/* COM_PLD_SIZE - Maximum number of UDP payload bytes to transmit (must be a multiple of 6 with range 6 to 8892) */
#define WD2_COM_PLD_SIZE_REG                                  WD2_REG_COM_PLD_SIZE
#define WD2_COM_PLD_SIZE_MASK                                           0x0003FFFF
#define WD2_COM_PLD_SIZE_OFS                                                     0



/* ****** Control Register 7 [0x101C]: DRS_CH_TX_EN - DRS Channel Transmission Enable Register (Default: 0x0000FFFF) ****** */

/* DRS_CH_TX_EN - DRS channel transmission enable [Ch17:Ch0] - (CH17:CH16 = timing channels) */
#define WD2_DRS_CH_TX_EN_REG                                  WD2_REG_DRS_CH_TX_EN
#define WD2_DRS_CH_TX_EN_MASK                                           0x0003FFFF
#define WD2_DRS_CH_TX_EN_OFS                                                     0



/* ****** Control Register 8 [0x1020]: ADC_CH_TX_EN - ADC Channel Transmission Enable Register (Default: 0x00000000) ****** */

/* ADC_CH_TX_EN - ADC channel transmission enable [Ch15:Ch0] */
#define WD2_ADC_CH_TX_EN_REG                                  WD2_REG_ADC_CH_TX_EN
#define WD2_ADC_CH_TX_EN_MASK                                           0x0000FFFF
#define WD2_ADC_CH_TX_EN_OFS                                                     0



/* ****** Control Register 9 [0x1024]: TDC_CH_TX_EN - TDC Channel Transmission Enable Register (Default: 0x00000000) ****** */

/* TDC_CH_TX_EN - TDC channel transmission enable [Ch15:Ch0] */
#define WD2_TDC_CH_TX_EN_REG                                  WD2_REG_TDC_CH_TX_EN
#define WD2_TDC_CH_TX_EN_MASK                                           0x0000FFFF
#define WD2_TDC_CH_TX_EN_OFS                                                     0



/* ****** Control Register 10 [0x1028]: DRS_TX_SAMPLES - DRS Samples to transmit (Default: 0x00000400) ****** */

/* DRS_TX_SAMPLES - Number of DRS samples to transmit per channel (must be an even value with range 2 to 1024) */
#define WD2_DRS_TX_SAMPLES_REG                              WD2_REG_DRS_TX_SAMPLES
#define WD2_DRS_TX_SAMPLES_MASK                                         0x000007FF
#define WD2_DRS_TX_SAMPLES_OFS                                                   0



/* ****** Control Register 11 [0x102C]: ADC_TX_SAMPLES - ADC Samples to transmit (Default: 0x00000800) ****** */

/* ADC_TX_SAMPLES - Number of ADC samples to transmit per channel (must be an even value with range 2 to 2048) */
#define WD2_ADC_TX_SAMPLES_REG                              WD2_REG_ADC_TX_SAMPLES
#define WD2_ADC_TX_SAMPLES_MASK                                         0x00000FFF
#define WD2_ADC_TX_SAMPLES_OFS                                                   0



/* ****** Control Register 12 [0x1030]: TDC_TX_SAMPLES - TDC Samples to transmit (Default: 0x00001000) ****** */

/* TDC_TX_SAMPLES - Number of TDC samples to transmit per channel (must be a multiple of 8 with range 16 to 4096) */
#define WD2_TDC_TX_SAMPLES_REG                              WD2_REG_TDC_TX_SAMPLES
#define WD2_TDC_TX_SAMPLES_MASK                                         0x00001FFF
#define WD2_TDC_TX_SAMPLES_OFS                                                   0



/* ****** Control Register 13 [0x1034]: TRG_TX_SAMPLES - TRG Samples to transmit (Default: 0x00000200) ****** */

/* TRG_TX_SAMPLES - Number of advanced trigger output samples to transmit (range 1 to 512) */
#define WD2_TRG_TX_SAMPLES_REG                              WD2_REG_TRG_TX_SAMPLES
#define WD2_TRG_TX_SAMPLES_MASK                                         0x000003FF
#define WD2_TRG_TX_SAMPLES_OFS                                                   0



/* ****** Control Register 14 [0x1038]: ADC_SAMPLE_DIV - ADC Downsampling Divider (Default: 0x00000001) ****** */

/* ADC_SAMPLE_DIV - Only store every n-th sample to buffer */
#define WD2_ADC_SAMPLE_DIV_REG                              WD2_REG_ADC_SAMPLE_DIV
#define WD2_ADC_SAMPLE_DIV_MASK                                         0x000000FF
#define WD2_ADC_SAMPLE_DIV_OFS                                                   0



/* ****** Control Register 15 [0x103C]: ZERO_SUPR - Zero Suppression Configuration Register (Default: 0x00000080) ****** */

/* ZERO_SUPR_EN - Enable zero suppression for data transmission (only transmit channels that triggered) */
#define WD2_ZERO_SUPR_EN_REG                                     WD2_REG_ZERO_SUPR
#define WD2_ZERO_SUPR_EN_MASK                                           0x00000100
#define WD2_ZERO_SUPR_EN_OFS                                                     8

/* ZERO_SUPR_WINDOW - Zero suppression time window in DAQ clock ticks (channel polarity defined in TRG_SRC_POL) */
#define WD2_ZERO_SUPR_WINDOW_REG                                 WD2_REG_ZERO_SUPR
#define WD2_ZERO_SUPR_WINDOW_MASK                                       0x000000FF
#define WD2_ZERO_SUPR_WINDOW_OFS                                                 0



/* ****** Control Register 16 [0x1040]: RST - Reset bits for specific firmwar units (Default: 0x00000000) ****** */

/* DAQ_PLL_RST - Reset the PLL for the DAQ clock */
#define WD2_DAQ_PLL_RST_REG                                            WD2_REG_RST
#define WD2_DAQ_PLL_RST_MASK                                            0x00004000
#define WD2_DAQ_PLL_RST_OFS                                                     14

/* DCB_OSERDES_PLL_RST - Reset the PLL of the DCB OSERDES */
#define WD2_DCB_OSERDES_PLL_RST_REG                                    WD2_REG_RST
#define WD2_DCB_OSERDES_PLL_RST_MASK                                    0x00002000
#define WD2_DCB_OSERDES_PLL_RST_OFS                                             13

/* TCB_OSERDES_PLL_RST - Reset the PLL of the TCB OSERDES */
#define WD2_TCB_OSERDES_PLL_RST_REG                                    WD2_REG_RST
#define WD2_TCB_OSERDES_PLL_RST_MASK                                    0x00001000
#define WD2_TCB_OSERDES_PLL_RST_OFS                                             12

/* DCB_OSERDES_IF_RST - Reset the DCB OSERDES interface */
#define WD2_DCB_OSERDES_IF_RST_REG                                     WD2_REG_RST
#define WD2_DCB_OSERDES_IF_RST_MASK                                     0x00000800
#define WD2_DCB_OSERDES_IF_RST_OFS                                              11

/* TCB_OSERDES_IF_RST - Reset the TCB OSERDES interface */
#define WD2_TCB_OSERDES_IF_RST_REG                                     WD2_REG_RST
#define WD2_TCB_OSERDES_IF_RST_MASK                                     0x00000400
#define WD2_TCB_OSERDES_IF_RST_OFS                                              10

/* SCALER_RST - Reset all scalers */
#define WD2_SCALER_RST_REG                                             WD2_REG_RST
#define WD2_SCALER_RST_MASK                                             0x00000200
#define WD2_SCALER_RST_OFS                                                       9

/* TRB_PARITY_ERROR_COUNT_RST - Reset the parity error counter of the trigger info serial connection */
#define WD2_TRB_PARITY_ERROR_COUNT_RST_REG                             WD2_REG_RST
#define WD2_TRB_PARITY_ERROR_COUNT_RST_MASK                             0x00000100
#define WD2_TRB_PARITY_ERROR_COUNT_RST_OFS                                       8

/* LMK_SYNC_LOCAL - Control LMK SYNC signal from FPGA: 0 = run / 1 = sync */
#define WD2_LMK_SYNC_LOCAL_REG                                         WD2_REG_RST
#define WD2_LMK_SYNC_LOCAL_MASK                                         0x00000080
#define WD2_LMK_SYNC_LOCAL_OFS                                                   7

/* ADC_RST - ADC reset */
#define WD2_ADC_RST_REG                                                WD2_REG_RST
#define WD2_ADC_RST_MASK                                                0x00000040
#define WD2_ADC_RST_OFS                                                          6

/* ADC_IF_RST - Reset the ADC interface */
#define WD2_ADC_IF_RST_REG                                             WD2_REG_RST
#define WD2_ADC_IF_RST_MASK                                             0x00000020
#define WD2_ADC_IF_RST_OFS                                                       5

/* DATA_LINK_IF_RST - Reset of the interface between packager and Ethernet/SERDES interface */
#define WD2_DATA_LINK_IF_RST_REG                                       WD2_REG_RST
#define WD2_DATA_LINK_IF_RST_MASK                                       0x00000010
#define WD2_DATA_LINK_IF_RST_OFS                                                 4

/* WD_PKGR_RST - WaveDream packager reset */
#define WD2_WD_PKGR_RST_REG                                            WD2_REG_RST
#define WD2_WD_PKGR_RST_MASK                                            0x00000008
#define WD2_WD_PKGR_RST_OFS                                                      3

/* EVENT_COUNTER_RST - Event Counter Reset */
#define WD2_EVENT_COUNTER_RST_REG                                      WD2_REG_RST
#define WD2_EVENT_COUNTER_RST_MASK                                      0x00000004
#define WD2_EVENT_COUNTER_RST_OFS                                                2

/* DRS_CTRL_FSM_RST - DRS control FSM reset */
#define WD2_DRS_CTRL_FSM_RST_REG                                       WD2_REG_RST
#define WD2_DRS_CTRL_FSM_RST_MASK                                       0x00000002
#define WD2_DRS_CTRL_FSM_RST_OFS                                                 1

/* RECONFIGURE_FPGA - Initiate FPGA Reconfiguration */
#define WD2_RECONFIGURE_FPGA_REG                                       WD2_REG_RST
#define WD2_RECONFIGURE_FPGA_MASK                                       0x00000001
#define WD2_RECONFIGURE_FPGA_OFS                                                 0



/* ****** Control Register 17 [0x1044]: APLY_CFG - Apply settings from regsiter bank to hardware units (Default: 0x00000000) ****** */

/* APPLY_SETTINGS_ADC_SAMPLE_DIV - Apply configuration from register bank to ADC sampling frequency (auto update) */
#define WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_REG                     WD2_REG_APLY_CFG
#define WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_MASK                          0x00000100
#define WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_OFS                                    8

/* APPLY_SETTINGS_MAX_PLD_SIZE - Apply configuration from register bank to max samples per packet (auto update) */
#define WD2_APPLY_SETTINGS_MAX_PLD_SIZE_REG                       WD2_REG_APLY_CFG
#define WD2_APPLY_SETTINGS_MAX_PLD_SIZE_MASK                            0x00000080
#define WD2_APPLY_SETTINGS_MAX_PLD_SIZE_OFS                                      7

/* APPLY_SETTINGS_HV - Apply configuration from register bank to HV (auto update) */
#define WD2_APPLY_SETTINGS_HV_REG                                 WD2_REG_APLY_CFG
#define WD2_APPLY_SETTINGS_HV_MASK                                      0x00000040
#define WD2_APPLY_SETTINGS_HV_OFS                                                6

/* APPLY_SETTINGS_DRS - Apply configuration from register bank to DRS chip (auto update) */
#define WD2_APPLY_SETTINGS_DRS_REG                                WD2_REG_APLY_CFG
#define WD2_APPLY_SETTINGS_DRS_MASK                                     0x00000020
#define WD2_APPLY_SETTINGS_DRS_OFS                                               5

/* APPLY_SETTINGS_DAC - Apply configuration from register bank to DAC (auto update) */
#define WD2_APPLY_SETTINGS_DAC_REG                                WD2_REG_APLY_CFG
#define WD2_APPLY_SETTINGS_DAC_MASK                                     0x00000010
#define WD2_APPLY_SETTINGS_DAC_OFS                                               4

/* APPLY_SETTINGS_FRONTEND - Apply configuration from register bank to frontend (auto update) */
#define WD2_APPLY_SETTINGS_FRONTEND_REG                           WD2_REG_APLY_CFG
#define WD2_APPLY_SETTINGS_FRONTEND_MASK                                0x00000008
#define WD2_APPLY_SETTINGS_FRONTEND_OFS                                          3

/* APPLY_SETTINGS_CTRL - Apply configuration from register bank control register */
#define WD2_APPLY_SETTINGS_CTRL_REG                               WD2_REG_APLY_CFG
#define WD2_APPLY_SETTINGS_CTRL_MASK                                    0x00000004
#define WD2_APPLY_SETTINGS_CTRL_OFS                                              2

/* APPLY_SETTINGS_ADC - Apply configuration from register bank to ADC */
#define WD2_APPLY_SETTINGS_ADC_REG                                WD2_REG_APLY_CFG
#define WD2_APPLY_SETTINGS_ADC_MASK                                     0x00000002
#define WD2_APPLY_SETTINGS_ADC_OFS                                               1

/* APPLY_SETTINGS_LMK - Apply configuration from regsiter bank to LMK */
#define WD2_APPLY_SETTINGS_LMK_REG                                WD2_REG_APLY_CFG
#define WD2_APPLY_SETTINGS_LMK_MASK                                     0x00000001
#define WD2_APPLY_SETTINGS_LMK_OFS                                               0



/* ****** Control Register 18 [0x1048]: DAC0_A_B - DAC0 values for Channel A and B (Default: 0x9EC045A0) ****** */

/* DAC0_CH_A - Set DAC0 channel A (ROFS) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V) */
#define WD2_DAC0_CH_A_REG                                         WD2_REG_DAC0_A_B
#define WD2_DAC0_CH_A_MASK                                              0xFFFF0000
#define WD2_DAC0_CH_A_OFS                                                       16

/* DAC0_CH_B - Set DAC0 channel B (OFS) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (+/- 0.625V) */
#define WD2_DAC0_CH_B_REG                                         WD2_REG_DAC0_A_B
#define WD2_DAC0_CH_B_MASK                                              0x0000FFFF
#define WD2_DAC0_CH_B_OFS                                                        0



/* ****** Control Register 19 [0x104C]: DAC0_C_D - DAC0 values for Channel C and D (Default: 0x00000000) ****** */

/* DAC0_CH_C - Set DAC0 channel C (CAL_DC) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (+/- 0.625V) */
#define WD2_DAC0_CH_C_REG                                         WD2_REG_DAC0_C_D
#define WD2_DAC0_CH_C_MASK                                              0xFFFF0000
#define WD2_DAC0_CH_C_OFS                                                       16

/* DAC0_CH_D - Set DAC0 channel D (PULSE_AMP) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..1V) */
#define WD2_DAC0_CH_D_REG                                         WD2_REG_DAC0_C_D
#define WD2_DAC0_CH_D_MASK                                              0x0000FFFF
#define WD2_DAC0_CH_D_OFS                                                        0



/* ****** Control Register 20 [0x1050]: DAC0_E_F - DAC0 values for Channel E and F (Default: 0x00000000) ****** */

/* DAC0_CH_E - Set DAC0 channel E (PZC_LEVEL) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (+/- 2.5V) */
#define WD2_DAC0_CH_E_REG                                         WD2_REG_DAC0_E_F
#define WD2_DAC0_CH_E_MASK                                              0xFFFF0000
#define WD2_DAC0_CH_E_OFS                                                       16

/* DAC0_CH_F - Set DAC0 channel F (RESERVED) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V) */
#define WD2_DAC0_CH_F_REG                                         WD2_REG_DAC0_E_F
#define WD2_DAC0_CH_F_MASK                                              0x0000FFFF
#define WD2_DAC0_CH_F_OFS                                                        0



/* ****** Control Register 21 [0x1054]: DAC0_G_H - DAC0 values for Channel G and H (Default: 0x000047B0) ****** */

/* DAC0_CH_G - Set DAC0 channel G (RESERVED) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V) */
#define WD2_DAC0_CH_G_REG                                         WD2_REG_DAC0_G_H
#define WD2_DAC0_CH_G_MASK                                              0xFFFF0000
#define WD2_DAC0_CH_G_OFS                                                       16

/* DAC0_CH_H - Set DAC0 channel H (BIAS) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V) */
#define WD2_DAC0_CH_H_REG                                         WD2_REG_DAC0_G_H
#define WD2_DAC0_CH_H_MASK                                              0x0000FFFF
#define WD2_DAC0_CH_H_OFS                                                        0



/* ****** Control Register 22 [0x1058]: DAC1_A_B - DAC1 values for Channel A and B (Default: 0x57105710) ****** */

/* DAC1_CH_A - Set DAC1 channel A (TLEVEL_0) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V) */
#define WD2_DAC1_CH_A_REG                                         WD2_REG_DAC1_A_B
#define WD2_DAC1_CH_A_MASK                                              0xFFFF0000
#define WD2_DAC1_CH_A_OFS                                                       16

/* DAC1_CH_B - Set DAC1 channel B (TLEVEL_1) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V) */
#define WD2_DAC1_CH_B_REG                                         WD2_REG_DAC1_A_B
#define WD2_DAC1_CH_B_MASK                                              0x0000FFFF
#define WD2_DAC1_CH_B_OFS                                                        0



/* ****** Control Register 23 [0x105C]: DAC1_C_D - DAC1 values for Channel C and D (Default: 0x57105710) ****** */

/* DAC1_CH_C - Set DAC1 channel C (TLEVEL_2) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V) */
#define WD2_DAC1_CH_C_REG                                         WD2_REG_DAC1_C_D
#define WD2_DAC1_CH_C_MASK                                              0xFFFF0000
#define WD2_DAC1_CH_C_OFS                                                       16

/* DAC1_CH_D - Set DAC1 channel D (TLEVEL_3) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V) */
#define WD2_DAC1_CH_D_REG                                         WD2_REG_DAC1_C_D
#define WD2_DAC1_CH_D_MASK                                              0x0000FFFF
#define WD2_DAC1_CH_D_OFS                                                        0



/* ****** Control Register 24 [0x1060]: DAC1_E_F - DAC1 values for Channel E and F (Default: 0x57105710) ****** */

/* DAC1_CH_E - Set DAC1 channel E (TLEVEL_4) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V) */
#define WD2_DAC1_CH_E_REG                                         WD2_REG_DAC1_E_F
#define WD2_DAC1_CH_E_MASK                                              0xFFFF0000
#define WD2_DAC1_CH_E_OFS                                                       16

/* DAC1_CH_F - Set DAC1 channel F (TLEVEL_5) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V) */
#define WD2_DAC1_CH_F_REG                                         WD2_REG_DAC1_E_F
#define WD2_DAC1_CH_F_MASK                                              0x0000FFFF
#define WD2_DAC1_CH_F_OFS                                                        0



/* ****** Control Register 25 [0x1064]: DAC1_G_H - DAC1 values for Channel G and H (Default: 0x57105710) ****** */

/* DAC1_CH_G - Set DAC1 channel G (TLEVEL_6) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V) */
#define WD2_DAC1_CH_G_REG                                         WD2_REG_DAC1_G_H
#define WD2_DAC1_CH_G_MASK                                              0xFFFF0000
#define WD2_DAC1_CH_G_OFS                                                       16

/* DAC1_CH_H - Set DAC1 channel H (TLEVEL_7) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V) */
#define WD2_DAC1_CH_H_REG                                         WD2_REG_DAC1_G_H
#define WD2_DAC1_CH_H_MASK                                              0x0000FFFF
#define WD2_DAC1_CH_H_OFS                                                        0



/* ****** Control Register 26 [0x1068]: DAC2_A_B - DAC2 values for Channel A and B (Default: 0x57105710) ****** */

/* DAC2_CH_A - Set DAC2 channel A (TLEVEL_8) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V) */
#define WD2_DAC2_CH_A_REG                                         WD2_REG_DAC2_A_B
#define WD2_DAC2_CH_A_MASK                                              0xFFFF0000
#define WD2_DAC2_CH_A_OFS                                                       16

/* DAC2_CH_B - Set DAC2 channel B (TLEVEL_9) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V) */
#define WD2_DAC2_CH_B_REG                                         WD2_REG_DAC2_A_B
#define WD2_DAC2_CH_B_MASK                                              0x0000FFFF
#define WD2_DAC2_CH_B_OFS                                                        0



/* ****** Control Register 27 [0x106C]: DAC2_C_D - DAC2 values for Channel C and D (Default: 0x57105710) ****** */

/* DAC2_CH_C - Set DAC2 channel C (TLEVEL_10) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V) */
#define WD2_DAC2_CH_C_REG                                         WD2_REG_DAC2_C_D
#define WD2_DAC2_CH_C_MASK                                              0xFFFF0000
#define WD2_DAC2_CH_C_OFS                                                       16

/* DAC2_CH_D - Set DAC2 channel D (TLEVEL_11) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V) */
#define WD2_DAC2_CH_D_REG                                         WD2_REG_DAC2_C_D
#define WD2_DAC2_CH_D_MASK                                              0x0000FFFF
#define WD2_DAC2_CH_D_OFS                                                        0



/* ****** Control Register 28 [0x1070]: DAC2_E_F - DAC2 values for Channel E and F (Default: 0x57105710) ****** */

/* DAC2_CH_E - Set DAC2 channel E (TLEVEL_12) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V) */
#define WD2_DAC2_CH_E_REG                                         WD2_REG_DAC2_E_F
#define WD2_DAC2_CH_E_MASK                                              0xFFFF0000
#define WD2_DAC2_CH_E_OFS                                                       16

/* DAC2_CH_F - Set DAC2 channel F (TLEVEL_13) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V) */
#define WD2_DAC2_CH_F_REG                                         WD2_REG_DAC2_E_F
#define WD2_DAC2_CH_F_MASK                                              0x0000FFFF
#define WD2_DAC2_CH_F_OFS                                                        0



/* ****** Control Register 29 [0x1074]: DAC2_G_H - DAC2 values for Channel G and H (Default: 0x57105710) ****** */

/* DAC2_CH_G - Set DAC2 channel G (TLEVEL_14) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V) */
#define WD2_DAC2_CH_G_REG                                         WD2_REG_DAC2_G_H
#define WD2_DAC2_CH_G_MASK                                              0xFFFF0000
#define WD2_DAC2_CH_G_OFS                                                       16

/* DAC2_CH_H - Set DAC2 channel H (TLEVEL_15) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V) */
#define WD2_DAC2_CH_H_REG                                         WD2_REG_DAC2_G_H
#define WD2_DAC2_CH_H_MASK                                              0x0000FFFF
#define WD2_DAC2_CH_H_OFS                                                        0



/* ****** Control Register 30 [0x1078]: FE_CFG_0_1 - Frontend Settings for Channel 0 and 1 (Default: 0x00020002) ****** */

/* FE0_PZC_EN - Frontend channel 0 PZC (pole-zero cancellation) enable (ACDC) */
#define WD2_FE0_PZC_EN_REG                                      WD2_REG_FE_CFG_0_1
#define WD2_FE0_PZC_EN_MASK                                             0x01000000
#define WD2_FE0_PZC_EN_OFS                                                      24

/* FE0_AMPLIFIER2_COMP_EN - Frontend channel 0 amplifier 2 compensation enable (COMP2) */
#define WD2_FE0_AMPLIFIER2_COMP_EN_REG                          WD2_REG_FE_CFG_0_1
#define WD2_FE0_AMPLIFIER2_COMP_EN_MASK                                 0x00800000
#define WD2_FE0_AMPLIFIER2_COMP_EN_OFS                                          23

/* FE0_AMPLIFIER2_EN - Frontend channel 0 amplifier 2 enable (gain: 10) (OP2) */
#define WD2_FE0_AMPLIFIER2_EN_REG                               WD2_REG_FE_CFG_0_1
#define WD2_FE0_AMPLIFIER2_EN_MASK                                      0x00400000
#define WD2_FE0_AMPLIFIER2_EN_OFS                                               22

/* FE0_AMPLIFIER1_COMP_EN - Frontend channel 0 amplifier 1 compensation enable (COMP1) */
#define WD2_FE0_AMPLIFIER1_COMP_EN_REG                          WD2_REG_FE_CFG_0_1
#define WD2_FE0_AMPLIFIER1_COMP_EN_MASK                                 0x00200000
#define WD2_FE0_AMPLIFIER1_COMP_EN_OFS                                          21

/* FE0_AMPLIFIER1_EN - Frontend channel 0 amplifier 1 enable (gain: 10) (OP1) */
#define WD2_FE0_AMPLIFIER1_EN_REG                               WD2_REG_FE_CFG_0_1
#define WD2_FE0_AMPLIFIER1_EN_MASK                                      0x00100000
#define WD2_FE0_AMPLIFIER1_EN_OFS                                               20

/* FE0_ATTENUATION - Frontend channel 0 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0) */
#define WD2_FE0_ATTENUATION_REG                                 WD2_REG_FE_CFG_0_1
#define WD2_FE0_ATTENUATION_MASK                                        0x000C0000
#define WD2_FE0_ATTENUATION_OFS                                                 18

/* FE0_MUX - Frontend channel 0 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0) */
#define WD2_FE0_MUX_REG                                         WD2_REG_FE_CFG_0_1
#define WD2_FE0_MUX_MASK                                                0x00030000
#define WD2_FE0_MUX_OFS                                                         16

/* FE1_PZC_EN - Frontend channel 1 PZC (pole-zero cancellation) enable (ACDC) */
#define WD2_FE1_PZC_EN_REG                                      WD2_REG_FE_CFG_0_1
#define WD2_FE1_PZC_EN_MASK                                             0x00000100
#define WD2_FE1_PZC_EN_OFS                                                       8

/* FE1_AMPLIFIER2_COMP_EN - Frontend channel 1 amplifier 2 compensation enable (COMP2) */
#define WD2_FE1_AMPLIFIER2_COMP_EN_REG                          WD2_REG_FE_CFG_0_1
#define WD2_FE1_AMPLIFIER2_COMP_EN_MASK                                 0x00000080
#define WD2_FE1_AMPLIFIER2_COMP_EN_OFS                                           7

/* FE1_AMPLIFIER2_EN - Frontend channel 1 amplifier 2 enable (gain: 10) (OP2) */
#define WD2_FE1_AMPLIFIER2_EN_REG                               WD2_REG_FE_CFG_0_1
#define WD2_FE1_AMPLIFIER2_EN_MASK                                      0x00000040
#define WD2_FE1_AMPLIFIER2_EN_OFS                                                6

/* FE1_AMPLIFIER1_COMP_EN - Frontend channel 1 amplifier 1 compensation enable (COMP1) */
#define WD2_FE1_AMPLIFIER1_COMP_EN_REG                          WD2_REG_FE_CFG_0_1
#define WD2_FE1_AMPLIFIER1_COMP_EN_MASK                                 0x00000020
#define WD2_FE1_AMPLIFIER1_COMP_EN_OFS                                           5

/* FE1_AMPLIFIER1_EN - Frontend channel 1 amplifier 1 enable (gain: 10) (OP1) */
#define WD2_FE1_AMPLIFIER1_EN_REG                               WD2_REG_FE_CFG_0_1
#define WD2_FE1_AMPLIFIER1_EN_MASK                                      0x00000010
#define WD2_FE1_AMPLIFIER1_EN_OFS                                                4

/* FE1_ATTENUATION - Frontend channel 1 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0) */
#define WD2_FE1_ATTENUATION_REG                                 WD2_REG_FE_CFG_0_1
#define WD2_FE1_ATTENUATION_MASK                                        0x0000000C
#define WD2_FE1_ATTENUATION_OFS                                                  2

/* FE1_MUX - Frontend channel 1 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0) */
#define WD2_FE1_MUX_REG                                         WD2_REG_FE_CFG_0_1
#define WD2_FE1_MUX_MASK                                                0x00000003
#define WD2_FE1_MUX_OFS                                                          0



/* ****** Control Register 31 [0x107C]: FE_CFG_2_3 - Frontend Settings for Channel 2 and 3 (Default: 0x00020002) ****** */

/* FE2_PZC_EN - Frontend channel 2 PZC (pole-zero cancellation) enable (ACDC) */
#define WD2_FE2_PZC_EN_REG                                      WD2_REG_FE_CFG_2_3
#define WD2_FE2_PZC_EN_MASK                                             0x01000000
#define WD2_FE2_PZC_EN_OFS                                                      24

/* FE2_AMPLIFIER2_COMP_EN - Frontend channel 2 amplifier 2 compensation enable (COMP2) */
#define WD2_FE2_AMPLIFIER2_COMP_EN_REG                          WD2_REG_FE_CFG_2_3
#define WD2_FE2_AMPLIFIER2_COMP_EN_MASK                                 0x00800000
#define WD2_FE2_AMPLIFIER2_COMP_EN_OFS                                          23

/* FE2_AMPLIFIER2_EN - Frontend channel 2 amplifier 2 enable (gain: 10) (OP2) */
#define WD2_FE2_AMPLIFIER2_EN_REG                               WD2_REG_FE_CFG_2_3
#define WD2_FE2_AMPLIFIER2_EN_MASK                                      0x00400000
#define WD2_FE2_AMPLIFIER2_EN_OFS                                               22

/* FE2_AMPLIFIER1_COMP_EN - Frontend channel 2 amplifier 1 compensation enable (COMP1) */
#define WD2_FE2_AMPLIFIER1_COMP_EN_REG                          WD2_REG_FE_CFG_2_3
#define WD2_FE2_AMPLIFIER1_COMP_EN_MASK                                 0x00200000
#define WD2_FE2_AMPLIFIER1_COMP_EN_OFS                                          21

/* FE2_AMPLIFIER1_EN - Frontend channel 2 amplifier 1 enable (gain: 10) (OP1) */
#define WD2_FE2_AMPLIFIER1_EN_REG                               WD2_REG_FE_CFG_2_3
#define WD2_FE2_AMPLIFIER1_EN_MASK                                      0x00100000
#define WD2_FE2_AMPLIFIER1_EN_OFS                                               20

/* FE2_ATTENUATION - Frontend channel 2 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0) */
#define WD2_FE2_ATTENUATION_REG                                 WD2_REG_FE_CFG_2_3
#define WD2_FE2_ATTENUATION_MASK                                        0x000C0000
#define WD2_FE2_ATTENUATION_OFS                                                 18

/* FE2_MUX - Frontend channel 2 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0) */
#define WD2_FE2_MUX_REG                                         WD2_REG_FE_CFG_2_3
#define WD2_FE2_MUX_MASK                                                0x00030000
#define WD2_FE2_MUX_OFS                                                         16

/* FE3_PZC_EN - Frontend channel 3 PZC (pole-zero cancellation) enable (ACDC) */
#define WD2_FE3_PZC_EN_REG                                      WD2_REG_FE_CFG_2_3
#define WD2_FE3_PZC_EN_MASK                                             0x00000100
#define WD2_FE3_PZC_EN_OFS                                                       8

/* FE3_AMPLIFIER2_COMP_EN - Frontend channel 3 amplifier 2 compensation enable (COMP2) */
#define WD2_FE3_AMPLIFIER2_COMP_EN_REG                          WD2_REG_FE_CFG_2_3
#define WD2_FE3_AMPLIFIER2_COMP_EN_MASK                                 0x00000080
#define WD2_FE3_AMPLIFIER2_COMP_EN_OFS                                           7

/* FE3_AMPLIFIER2_EN - Frontend channel 3 amplifier 2 enable (gain: 10) (OP2) */
#define WD2_FE3_AMPLIFIER2_EN_REG                               WD2_REG_FE_CFG_2_3
#define WD2_FE3_AMPLIFIER2_EN_MASK                                      0x00000040
#define WD2_FE3_AMPLIFIER2_EN_OFS                                                6

/* FE3_AMPLIFIER1_COMP_EN - Frontend channel 3 amplifier 1 compensation enable (COMP1) */
#define WD2_FE3_AMPLIFIER1_COMP_EN_REG                          WD2_REG_FE_CFG_2_3
#define WD2_FE3_AMPLIFIER1_COMP_EN_MASK                                 0x00000020
#define WD2_FE3_AMPLIFIER1_COMP_EN_OFS                                           5

/* FE3_AMPLIFIER1_EN - Frontend channel 3 amplifier 1 enable (gain: 10) (OP1) */
#define WD2_FE3_AMPLIFIER1_EN_REG                               WD2_REG_FE_CFG_2_3
#define WD2_FE3_AMPLIFIER1_EN_MASK                                      0x00000010
#define WD2_FE3_AMPLIFIER1_EN_OFS                                                4

/* FE3_ATTENUATION - Frontend channel 3 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0) */
#define WD2_FE3_ATTENUATION_REG                                 WD2_REG_FE_CFG_2_3
#define WD2_FE3_ATTENUATION_MASK                                        0x0000000C
#define WD2_FE3_ATTENUATION_OFS                                                  2

/* FE3_MUX - Frontend channel 3 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0) */
#define WD2_FE3_MUX_REG                                         WD2_REG_FE_CFG_2_3
#define WD2_FE3_MUX_MASK                                                0x00000003
#define WD2_FE3_MUX_OFS                                                          0



/* ****** Control Register 32 [0x1080]: FE_CFG_4_5 - Frontend Settings for Channel 4 and 5 (Default: 0x00020002) ****** */

/* FE4_PZC_EN - Frontend channel 4 PZC (pole-zero cancellation) enable (ACDC) */
#define WD2_FE4_PZC_EN_REG                                      WD2_REG_FE_CFG_4_5
#define WD2_FE4_PZC_EN_MASK                                             0x01000000
#define WD2_FE4_PZC_EN_OFS                                                      24

/* FE4_AMPLIFIER2_COMP_EN - Frontend channel 4 amplifier 2 compensation enable (COMP2) */
#define WD2_FE4_AMPLIFIER2_COMP_EN_REG                          WD2_REG_FE_CFG_4_5
#define WD2_FE4_AMPLIFIER2_COMP_EN_MASK                                 0x00800000
#define WD2_FE4_AMPLIFIER2_COMP_EN_OFS                                          23

/* FE4_AMPLIFIER2_EN - Frontend channel 4 amplifier 2 enable (gain: 10) (OP2) */
#define WD2_FE4_AMPLIFIER2_EN_REG                               WD2_REG_FE_CFG_4_5
#define WD2_FE4_AMPLIFIER2_EN_MASK                                      0x00400000
#define WD2_FE4_AMPLIFIER2_EN_OFS                                               22

/* FE4_AMPLIFIER1_COMP_EN - Frontend channel 4 amplifier 1 compensation enable (COMP1) */
#define WD2_FE4_AMPLIFIER1_COMP_EN_REG                          WD2_REG_FE_CFG_4_5
#define WD2_FE4_AMPLIFIER1_COMP_EN_MASK                                 0x00200000
#define WD2_FE4_AMPLIFIER1_COMP_EN_OFS                                          21

/* FE4_AMPLIFIER1_EN - Frontend channel 4 amplifier 1 enable (gain: 10) (OP1) */
#define WD2_FE4_AMPLIFIER1_EN_REG                               WD2_REG_FE_CFG_4_5
#define WD2_FE4_AMPLIFIER1_EN_MASK                                      0x00100000
#define WD2_FE4_AMPLIFIER1_EN_OFS                                               20

/* FE4_ATTENUATION - Frontend channel 4 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0) */
#define WD2_FE4_ATTENUATION_REG                                 WD2_REG_FE_CFG_4_5
#define WD2_FE4_ATTENUATION_MASK                                        0x000C0000
#define WD2_FE4_ATTENUATION_OFS                                                 18

/* FE4_MUX - Frontend channel 4 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0) */
#define WD2_FE4_MUX_REG                                         WD2_REG_FE_CFG_4_5
#define WD2_FE4_MUX_MASK                                                0x00030000
#define WD2_FE4_MUX_OFS                                                         16

/* FE5_PZC_EN - Frontend channel 5 PZC (pole-zero cancellation) enable (ACDC) */
#define WD2_FE5_PZC_EN_REG                                      WD2_REG_FE_CFG_4_5
#define WD2_FE5_PZC_EN_MASK                                             0x00000100
#define WD2_FE5_PZC_EN_OFS                                                       8

/* FE5_AMPLIFIER2_COMP_EN - Frontend channel 5 amplifier 2 compensation enable (COMP2) */
#define WD2_FE5_AMPLIFIER2_COMP_EN_REG                          WD2_REG_FE_CFG_4_5
#define WD2_FE5_AMPLIFIER2_COMP_EN_MASK                                 0x00000080
#define WD2_FE5_AMPLIFIER2_COMP_EN_OFS                                           7

/* FE5_AMPLIFIER2_EN - Frontend channel 5 amplifier 2 enable (gain: 10) (OP2) */
#define WD2_FE5_AMPLIFIER2_EN_REG                               WD2_REG_FE_CFG_4_5
#define WD2_FE5_AMPLIFIER2_EN_MASK                                      0x00000040
#define WD2_FE5_AMPLIFIER2_EN_OFS                                                6

/* FE5_AMPLIFIER1_COMP_EN - Frontend channel 5 amplifier 1 compensation enable (COMP1) */
#define WD2_FE5_AMPLIFIER1_COMP_EN_REG                          WD2_REG_FE_CFG_4_5
#define WD2_FE5_AMPLIFIER1_COMP_EN_MASK                                 0x00000020
#define WD2_FE5_AMPLIFIER1_COMP_EN_OFS                                           5

/* FE5_AMPLIFIER1_EN - Frontend channel 5 amplifier 1 enable (gain: 10) (OP1) */
#define WD2_FE5_AMPLIFIER1_EN_REG                               WD2_REG_FE_CFG_4_5
#define WD2_FE5_AMPLIFIER1_EN_MASK                                      0x00000010
#define WD2_FE5_AMPLIFIER1_EN_OFS                                                4

/* FE5_ATTENUATION - Frontend channel 5 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0) */
#define WD2_FE5_ATTENUATION_REG                                 WD2_REG_FE_CFG_4_5
#define WD2_FE5_ATTENUATION_MASK                                        0x0000000C
#define WD2_FE5_ATTENUATION_OFS                                                  2

/* FE5_MUX - Frontend channel 5 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0) */
#define WD2_FE5_MUX_REG                                         WD2_REG_FE_CFG_4_5
#define WD2_FE5_MUX_MASK                                                0x00000003
#define WD2_FE5_MUX_OFS                                                          0



/* ****** Control Register 33 [0x1084]: FE_CFG_6_7 - Frontend Settings for Channel 6 and 7 (Default: 0x00020002) ****** */

/* FE6_PZC_EN - Frontend channel 6 PZC (pole-zero cancellation) enable (ACDC) */
#define WD2_FE6_PZC_EN_REG                                      WD2_REG_FE_CFG_6_7
#define WD2_FE6_PZC_EN_MASK                                             0x01000000
#define WD2_FE6_PZC_EN_OFS                                                      24

/* FE6_AMPLIFIER2_COMP_EN - Frontend channel 6 amplifier 2 compensation enable (COMP2) */
#define WD2_FE6_AMPLIFIER2_COMP_EN_REG                          WD2_REG_FE_CFG_6_7
#define WD2_FE6_AMPLIFIER2_COMP_EN_MASK                                 0x00800000
#define WD2_FE6_AMPLIFIER2_COMP_EN_OFS                                          23

/* FE6_AMPLIFIER2_EN - Frontend channel 6 amplifier 2 enable (gain: 10) (OP2) */
#define WD2_FE6_AMPLIFIER2_EN_REG                               WD2_REG_FE_CFG_6_7
#define WD2_FE6_AMPLIFIER2_EN_MASK                                      0x00400000
#define WD2_FE6_AMPLIFIER2_EN_OFS                                               22

/* FE6_AMPLIFIER1_COMP_EN - Frontend channel 6 amplifier 1 compensation enable (COMP1) */
#define WD2_FE6_AMPLIFIER1_COMP_EN_REG                          WD2_REG_FE_CFG_6_7
#define WD2_FE6_AMPLIFIER1_COMP_EN_MASK                                 0x00200000
#define WD2_FE6_AMPLIFIER1_COMP_EN_OFS                                          21

/* FE6_AMPLIFIER1_EN - Frontend channel 6 amplifier 1 enable (gain: 10) (OP1) */
#define WD2_FE6_AMPLIFIER1_EN_REG                               WD2_REG_FE_CFG_6_7
#define WD2_FE6_AMPLIFIER1_EN_MASK                                      0x00100000
#define WD2_FE6_AMPLIFIER1_EN_OFS                                               20

/* FE6_ATTENUATION - Frontend channel 6 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0) */
#define WD2_FE6_ATTENUATION_REG                                 WD2_REG_FE_CFG_6_7
#define WD2_FE6_ATTENUATION_MASK                                        0x000C0000
#define WD2_FE6_ATTENUATION_OFS                                                 18

/* FE6_MUX - Frontend channel 6 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0) */
#define WD2_FE6_MUX_REG                                         WD2_REG_FE_CFG_6_7
#define WD2_FE6_MUX_MASK                                                0x00030000
#define WD2_FE6_MUX_OFS                                                         16

/* FE7_PZC_EN - Frontend channel 7 PZC (pole-zero cancellation) enable (ACDC) */
#define WD2_FE7_PZC_EN_REG                                      WD2_REG_FE_CFG_6_7
#define WD2_FE7_PZC_EN_MASK                                             0x00000100
#define WD2_FE7_PZC_EN_OFS                                                       8

/* FE7_AMPLIFIER2_COMP_EN - Frontend channel 7 amplifier 2 compensation enable (COMP2) */
#define WD2_FE7_AMPLIFIER2_COMP_EN_REG                          WD2_REG_FE_CFG_6_7
#define WD2_FE7_AMPLIFIER2_COMP_EN_MASK                                 0x00000080
#define WD2_FE7_AMPLIFIER2_COMP_EN_OFS                                           7

/* FE7_AMPLIFIER2_EN - Frontend channel 7 amplifier 2 enable (gain: 10) (OP2) */
#define WD2_FE7_AMPLIFIER2_EN_REG                               WD2_REG_FE_CFG_6_7
#define WD2_FE7_AMPLIFIER2_EN_MASK                                      0x00000040
#define WD2_FE7_AMPLIFIER2_EN_OFS                                                6

/* FE7_AMPLIFIER1_COMP_EN - Frontend channel 7 amplifier 1 compensation enable (COMP1) */
#define WD2_FE7_AMPLIFIER1_COMP_EN_REG                          WD2_REG_FE_CFG_6_7
#define WD2_FE7_AMPLIFIER1_COMP_EN_MASK                                 0x00000020
#define WD2_FE7_AMPLIFIER1_COMP_EN_OFS                                           5

/* FE7_AMPLIFIER1_EN - Frontend channel 7 amplifier 1 enable (gain: 10) (OP1) */
#define WD2_FE7_AMPLIFIER1_EN_REG                               WD2_REG_FE_CFG_6_7
#define WD2_FE7_AMPLIFIER1_EN_MASK                                      0x00000010
#define WD2_FE7_AMPLIFIER1_EN_OFS                                                4

/* FE7_ATTENUATION - Frontend channel 7 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0) */
#define WD2_FE7_ATTENUATION_REG                                 WD2_REG_FE_CFG_6_7
#define WD2_FE7_ATTENUATION_MASK                                        0x0000000C
#define WD2_FE7_ATTENUATION_OFS                                                  2

/* FE7_MUX - Frontend channel 7 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0) */
#define WD2_FE7_MUX_REG                                         WD2_REG_FE_CFG_6_7
#define WD2_FE7_MUX_MASK                                                0x00000003
#define WD2_FE7_MUX_OFS                                                          0



/* ****** Control Register 34 [0x1088]: FE_CFG_8_9 - Frontend Settings for Channel 8 and 9 (Default: 0x00020002) ****** */

/* FE8_PZC_EN - Frontend channel 8 PZC (pole-zero cancellation) enable (ACDC) */
#define WD2_FE8_PZC_EN_REG                                      WD2_REG_FE_CFG_8_9
#define WD2_FE8_PZC_EN_MASK                                             0x01000000
#define WD2_FE8_PZC_EN_OFS                                                      24

/* FE8_AMPLIFIER2_COMP_EN - Frontend channel 8 amplifier 2 compensation enable (COMP2) */
#define WD2_FE8_AMPLIFIER2_COMP_EN_REG                          WD2_REG_FE_CFG_8_9
#define WD2_FE8_AMPLIFIER2_COMP_EN_MASK                                 0x00800000
#define WD2_FE8_AMPLIFIER2_COMP_EN_OFS                                          23

/* FE8_AMPLIFIER2_EN - Frontend channel 8 amplifier 2 enable (gain: 10) (OP2) */
#define WD2_FE8_AMPLIFIER2_EN_REG                               WD2_REG_FE_CFG_8_9
#define WD2_FE8_AMPLIFIER2_EN_MASK                                      0x00400000
#define WD2_FE8_AMPLIFIER2_EN_OFS                                               22

/* FE8_AMPLIFIER1_COMP_EN - Frontend channel 8 amplifier 1 compensation enable (COMP1) */
#define WD2_FE8_AMPLIFIER1_COMP_EN_REG                          WD2_REG_FE_CFG_8_9
#define WD2_FE8_AMPLIFIER1_COMP_EN_MASK                                 0x00200000
#define WD2_FE8_AMPLIFIER1_COMP_EN_OFS                                          21

/* FE8_AMPLIFIER1_EN - Frontend channel 8 amplifier 1 enable (gain: 10) (OP1) */
#define WD2_FE8_AMPLIFIER1_EN_REG                               WD2_REG_FE_CFG_8_9
#define WD2_FE8_AMPLIFIER1_EN_MASK                                      0x00100000
#define WD2_FE8_AMPLIFIER1_EN_OFS                                               20

/* FE8_ATTENUATION - Frontend channel 8 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0) */
#define WD2_FE8_ATTENUATION_REG                                 WD2_REG_FE_CFG_8_9
#define WD2_FE8_ATTENUATION_MASK                                        0x000C0000
#define WD2_FE8_ATTENUATION_OFS                                                 18

/* FE8_MUX - Frontend channel 8 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0) */
#define WD2_FE8_MUX_REG                                         WD2_REG_FE_CFG_8_9
#define WD2_FE8_MUX_MASK                                                0x00030000
#define WD2_FE8_MUX_OFS                                                         16

/* FE9_PZC_EN - Frontend channel 9 PZC (pole-zero cancellation) enable (ACDC) */
#define WD2_FE9_PZC_EN_REG                                      WD2_REG_FE_CFG_8_9
#define WD2_FE9_PZC_EN_MASK                                             0x00000100
#define WD2_FE9_PZC_EN_OFS                                                       8

/* FE9_AMPLIFIER2_COMP_EN - Frontend channel 9 amplifier 2 compensation enable (COMP2) */
#define WD2_FE9_AMPLIFIER2_COMP_EN_REG                          WD2_REG_FE_CFG_8_9
#define WD2_FE9_AMPLIFIER2_COMP_EN_MASK                                 0x00000080
#define WD2_FE9_AMPLIFIER2_COMP_EN_OFS                                           7

/* FE9_AMPLIFIER2_EN - Frontend channel 9 amplifier 2 enable (gain: 10) (OP2) */
#define WD2_FE9_AMPLIFIER2_EN_REG                               WD2_REG_FE_CFG_8_9
#define WD2_FE9_AMPLIFIER2_EN_MASK                                      0x00000040
#define WD2_FE9_AMPLIFIER2_EN_OFS                                                6

/* FE9_AMPLIFIER1_COMP_EN - Frontend channel 9 amplifier 1 compensation enable (COMP1) */
#define WD2_FE9_AMPLIFIER1_COMP_EN_REG                          WD2_REG_FE_CFG_8_9
#define WD2_FE9_AMPLIFIER1_COMP_EN_MASK                                 0x00000020
#define WD2_FE9_AMPLIFIER1_COMP_EN_OFS                                           5

/* FE9_AMPLIFIER1_EN - Frontend channel 9 amplifier 1 enable (gain: 10) (OP1) */
#define WD2_FE9_AMPLIFIER1_EN_REG                               WD2_REG_FE_CFG_8_9
#define WD2_FE9_AMPLIFIER1_EN_MASK                                      0x00000010
#define WD2_FE9_AMPLIFIER1_EN_OFS                                                4

/* FE9_ATTENUATION - Frontend channel 9 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0) */
#define WD2_FE9_ATTENUATION_REG                                 WD2_REG_FE_CFG_8_9
#define WD2_FE9_ATTENUATION_MASK                                        0x0000000C
#define WD2_FE9_ATTENUATION_OFS                                                  2

/* FE9_MUX - Frontend channel 9 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0) */
#define WD2_FE9_MUX_REG                                         WD2_REG_FE_CFG_8_9
#define WD2_FE9_MUX_MASK                                                0x00000003
#define WD2_FE9_MUX_OFS                                                          0



/* ****** Control Register 35 [0x108C]: FE_CFG_10_11 - Frontend Settings for Channel 10 and 11 (Default: 0x00020002) ****** */

/* FE10_PZC_EN - Frontend channel 10 PZC (pole-zero cancellation) enable (ACDC) */
#define WD2_FE10_PZC_EN_REG                                   WD2_REG_FE_CFG_10_11
#define WD2_FE10_PZC_EN_MASK                                            0x01000000
#define WD2_FE10_PZC_EN_OFS                                                     24

/* FE10_AMPLIFIER2_COMP_EN - Frontend channel 10 amplifier 2 compensation enable (COMP2) */
#define WD2_FE10_AMPLIFIER2_COMP_EN_REG                       WD2_REG_FE_CFG_10_11
#define WD2_FE10_AMPLIFIER2_COMP_EN_MASK                                0x00800000
#define WD2_FE10_AMPLIFIER2_COMP_EN_OFS                                         23

/* FE10_AMPLIFIER2_EN - Frontend channel 10 amplifier 2 enable (gain: 10) (OP2) */
#define WD2_FE10_AMPLIFIER2_EN_REG                            WD2_REG_FE_CFG_10_11
#define WD2_FE10_AMPLIFIER2_EN_MASK                                     0x00400000
#define WD2_FE10_AMPLIFIER2_EN_OFS                                              22

/* FE10_AMPLIFIER1_COMP_EN - Frontend channel 10 amplifier 1 compensation enable (COMP1) */
#define WD2_FE10_AMPLIFIER1_COMP_EN_REG                       WD2_REG_FE_CFG_10_11
#define WD2_FE10_AMPLIFIER1_COMP_EN_MASK                                0x00200000
#define WD2_FE10_AMPLIFIER1_COMP_EN_OFS                                         21

/* FE10_AMPLIFIER1_EN - Frontend channel 10 amplifier 1 enable (gain: 10) (OP1) */
#define WD2_FE10_AMPLIFIER1_EN_REG                            WD2_REG_FE_CFG_10_11
#define WD2_FE10_AMPLIFIER1_EN_MASK                                     0x00100000
#define WD2_FE10_AMPLIFIER1_EN_OFS                                              20

/* FE10_ATTENUATION - Frontend channel 10 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0) */
#define WD2_FE10_ATTENUATION_REG                              WD2_REG_FE_CFG_10_11
#define WD2_FE10_ATTENUATION_MASK                                       0x000C0000
#define WD2_FE10_ATTENUATION_OFS                                                18

/* FE10_MUX - Frontend channel 10 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0) */
#define WD2_FE10_MUX_REG                                      WD2_REG_FE_CFG_10_11
#define WD2_FE10_MUX_MASK                                               0x00030000
#define WD2_FE10_MUX_OFS                                                        16

/* FE11_PZC_EN - Frontend channel 11 PZC (pole-zero cancellation) enable (ACDC) */
#define WD2_FE11_PZC_EN_REG                                   WD2_REG_FE_CFG_10_11
#define WD2_FE11_PZC_EN_MASK                                            0x00000100
#define WD2_FE11_PZC_EN_OFS                                                      8

/* FE11_AMPLIFIER2_COMP_EN - Frontend channel 11 amplifier 2 compensation enable (COMP2) */
#define WD2_FE11_AMPLIFIER2_COMP_EN_REG                       WD2_REG_FE_CFG_10_11
#define WD2_FE11_AMPLIFIER2_COMP_EN_MASK                                0x00000080
#define WD2_FE11_AMPLIFIER2_COMP_EN_OFS                                          7

/* FE11_AMPLIFIER2_EN - Frontend channel 11 amplifier 2 enable (gain: 10) (OP2) */
#define WD2_FE11_AMPLIFIER2_EN_REG                            WD2_REG_FE_CFG_10_11
#define WD2_FE11_AMPLIFIER2_EN_MASK                                     0x00000040
#define WD2_FE11_AMPLIFIER2_EN_OFS                                               6

/* FE11_AMPLIFIER1_COMP_EN - Frontend channel 11 amplifier 1 compensation enable (COMP1) */
#define WD2_FE11_AMPLIFIER1_COMP_EN_REG                       WD2_REG_FE_CFG_10_11
#define WD2_FE11_AMPLIFIER1_COMP_EN_MASK                                0x00000020
#define WD2_FE11_AMPLIFIER1_COMP_EN_OFS                                          5

/* FE11_AMPLIFIER1_EN - Frontend channel 11 amplifier 1 enable (gain: 10) (OP1) */
#define WD2_FE11_AMPLIFIER1_EN_REG                            WD2_REG_FE_CFG_10_11
#define WD2_FE11_AMPLIFIER1_EN_MASK                                     0x00000010
#define WD2_FE11_AMPLIFIER1_EN_OFS                                               4

/* FE11_ATTENUATION - Frontend channel 11 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0) */
#define WD2_FE11_ATTENUATION_REG                              WD2_REG_FE_CFG_10_11
#define WD2_FE11_ATTENUATION_MASK                                       0x0000000C
#define WD2_FE11_ATTENUATION_OFS                                                 2

/* FE11_MUX - Frontend channel 11 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0) */
#define WD2_FE11_MUX_REG                                      WD2_REG_FE_CFG_10_11
#define WD2_FE11_MUX_MASK                                               0x00000003
#define WD2_FE11_MUX_OFS                                                         0



/* ****** Control Register 36 [0x1090]: FE_CFG_12_13 - Frontend Settings for Channel 12 and 13 (Default: 0x00020002) ****** */

/* FE12_PZC_EN - Frontend channel 12 PZC (pole-zero cancellation) enable (ACDC) */
#define WD2_FE12_PZC_EN_REG                                   WD2_REG_FE_CFG_12_13
#define WD2_FE12_PZC_EN_MASK                                            0x01000000
#define WD2_FE12_PZC_EN_OFS                                                     24

/* FE12_AMPLIFIER2_COMP_EN - Frontend channel 12 amplifier 2 compensation enable (COMP2) */
#define WD2_FE12_AMPLIFIER2_COMP_EN_REG                       WD2_REG_FE_CFG_12_13
#define WD2_FE12_AMPLIFIER2_COMP_EN_MASK                                0x00800000
#define WD2_FE12_AMPLIFIER2_COMP_EN_OFS                                         23

/* FE12_AMPLIFIER2_EN - Frontend channel 12 amplifier 2 enable (gain: 10) (OP2) */
#define WD2_FE12_AMPLIFIER2_EN_REG                            WD2_REG_FE_CFG_12_13
#define WD2_FE12_AMPLIFIER2_EN_MASK                                     0x00400000
#define WD2_FE12_AMPLIFIER2_EN_OFS                                              22

/* FE12_AMPLIFIER1_COMP_EN - Frontend channel 12 amplifier 1 compensation enable (COMP1) */
#define WD2_FE12_AMPLIFIER1_COMP_EN_REG                       WD2_REG_FE_CFG_12_13
#define WD2_FE12_AMPLIFIER1_COMP_EN_MASK                                0x00200000
#define WD2_FE12_AMPLIFIER1_COMP_EN_OFS                                         21

/* FE12_AMPLIFIER1_EN - Frontend channel 12 amplifier 1 enable (gain: 10) (OP1) */
#define WD2_FE12_AMPLIFIER1_EN_REG                            WD2_REG_FE_CFG_12_13
#define WD2_FE12_AMPLIFIER1_EN_MASK                                     0x00100000
#define WD2_FE12_AMPLIFIER1_EN_OFS                                              20

/* FE12_ATTENUATION - Frontend channel 12 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0) */
#define WD2_FE12_ATTENUATION_REG                              WD2_REG_FE_CFG_12_13
#define WD2_FE12_ATTENUATION_MASK                                       0x000C0000
#define WD2_FE12_ATTENUATION_OFS                                                18

/* FE12_MUX - Frontend channel 12 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0) */
#define WD2_FE12_MUX_REG                                      WD2_REG_FE_CFG_12_13
#define WD2_FE12_MUX_MASK                                               0x00030000
#define WD2_FE12_MUX_OFS                                                        16

/* FE13_PZC_EN - Frontend channel 13 PZC (pole-zero cancellation) enable (ACDC) */
#define WD2_FE13_PZC_EN_REG                                   WD2_REG_FE_CFG_12_13
#define WD2_FE13_PZC_EN_MASK                                            0x00000100
#define WD2_FE13_PZC_EN_OFS                                                      8

/* FE13_AMPLIFIER2_COMP_EN - Frontend channel 13 amplifier 2 compensation enable (COMP2) */
#define WD2_FE13_AMPLIFIER2_COMP_EN_REG                       WD2_REG_FE_CFG_12_13
#define WD2_FE13_AMPLIFIER2_COMP_EN_MASK                                0x00000080
#define WD2_FE13_AMPLIFIER2_COMP_EN_OFS                                          7

/* FE13_AMPLIFIER2_EN - Frontend channel 13 amplifier 2 enable (gain: 10) (OP2) */
#define WD2_FE13_AMPLIFIER2_EN_REG                            WD2_REG_FE_CFG_12_13
#define WD2_FE13_AMPLIFIER2_EN_MASK                                     0x00000040
#define WD2_FE13_AMPLIFIER2_EN_OFS                                               6

/* FE13_AMPLIFIER1_COMP_EN - Frontend channel 13 amplifier 1 compensation enable (COMP1) */
#define WD2_FE13_AMPLIFIER1_COMP_EN_REG                       WD2_REG_FE_CFG_12_13
#define WD2_FE13_AMPLIFIER1_COMP_EN_MASK                                0x00000020
#define WD2_FE13_AMPLIFIER1_COMP_EN_OFS                                          5

/* FE13_AMPLIFIER1_EN - Frontend channel 13 amplifier 1 enable (gain: 10) (OP1) */
#define WD2_FE13_AMPLIFIER1_EN_REG                            WD2_REG_FE_CFG_12_13
#define WD2_FE13_AMPLIFIER1_EN_MASK                                     0x00000010
#define WD2_FE13_AMPLIFIER1_EN_OFS                                               4

/* FE13_ATTENUATION - Frontend channel 13 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0) */
#define WD2_FE13_ATTENUATION_REG                              WD2_REG_FE_CFG_12_13
#define WD2_FE13_ATTENUATION_MASK                                       0x0000000C
#define WD2_FE13_ATTENUATION_OFS                                                 2

/* FE13_MUX - Frontend channel 13 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0) */
#define WD2_FE13_MUX_REG                                      WD2_REG_FE_CFG_12_13
#define WD2_FE13_MUX_MASK                                               0x00000003
#define WD2_FE13_MUX_OFS                                                         0



/* ****** Control Register 37 [0x1094]: FE_CFG_14_15 - Frontend Settings for Channel 14 and 15 (Default: 0x00020002) ****** */

/* FE14_PZC_EN - Frontend channel 14 PZC (pole-zero cancellation) enable (ACDC) */
#define WD2_FE14_PZC_EN_REG                                   WD2_REG_FE_CFG_14_15
#define WD2_FE14_PZC_EN_MASK                                            0x01000000
#define WD2_FE14_PZC_EN_OFS                                                     24

/* FE14_AMPLIFIER2_COMP_EN - Frontend channel 14 amplifier 2 compensation enable (COMP2) */
#define WD2_FE14_AMPLIFIER2_COMP_EN_REG                       WD2_REG_FE_CFG_14_15
#define WD2_FE14_AMPLIFIER2_COMP_EN_MASK                                0x00800000
#define WD2_FE14_AMPLIFIER2_COMP_EN_OFS                                         23

/* FE14_AMPLIFIER2_EN - Frontend channel 14 amplifier 2 enable (gain: 10) (OP2) */
#define WD2_FE14_AMPLIFIER2_EN_REG                            WD2_REG_FE_CFG_14_15
#define WD2_FE14_AMPLIFIER2_EN_MASK                                     0x00400000
#define WD2_FE14_AMPLIFIER2_EN_OFS                                              22

/* FE14_AMPLIFIER1_COMP_EN - Frontend channel 14 amplifier 1 compensation enable (COMP1) */
#define WD2_FE14_AMPLIFIER1_COMP_EN_REG                       WD2_REG_FE_CFG_14_15
#define WD2_FE14_AMPLIFIER1_COMP_EN_MASK                                0x00200000
#define WD2_FE14_AMPLIFIER1_COMP_EN_OFS                                         21

/* FE14_AMPLIFIER1_EN - Frontend channel 14 amplifier 1 enable (gain: 10) (OP1) */
#define WD2_FE14_AMPLIFIER1_EN_REG                            WD2_REG_FE_CFG_14_15
#define WD2_FE14_AMPLIFIER1_EN_MASK                                     0x00100000
#define WD2_FE14_AMPLIFIER1_EN_OFS                                              20

/* FE14_ATTENUATION - Frontend channel 14 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0) */
#define WD2_FE14_ATTENUATION_REG                              WD2_REG_FE_CFG_14_15
#define WD2_FE14_ATTENUATION_MASK                                       0x000C0000
#define WD2_FE14_ATTENUATION_OFS                                                18

/* FE14_MUX - Frontend channel 14 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0) */
#define WD2_FE14_MUX_REG                                      WD2_REG_FE_CFG_14_15
#define WD2_FE14_MUX_MASK                                               0x00030000
#define WD2_FE14_MUX_OFS                                                        16

/* FE15_PZC_EN - Frontend channel 15 PZC (pole-zero cancellation) enable (ACDC) */
#define WD2_FE15_PZC_EN_REG                                   WD2_REG_FE_CFG_14_15
#define WD2_FE15_PZC_EN_MASK                                            0x00000100
#define WD2_FE15_PZC_EN_OFS                                                      8

/* FE15_AMPLIFIER2_COMP_EN - Frontend channel 15 amplifier 2 compensation enable (COMP2) */
#define WD2_FE15_AMPLIFIER2_COMP_EN_REG                       WD2_REG_FE_CFG_14_15
#define WD2_FE15_AMPLIFIER2_COMP_EN_MASK                                0x00000080
#define WD2_FE15_AMPLIFIER2_COMP_EN_OFS                                          7

/* FE15_AMPLIFIER2_EN - Frontend channel 15 amplifier 2 enable (gain: 10) (OP2) */
#define WD2_FE15_AMPLIFIER2_EN_REG                            WD2_REG_FE_CFG_14_15
#define WD2_FE15_AMPLIFIER2_EN_MASK                                     0x00000040
#define WD2_FE15_AMPLIFIER2_EN_OFS                                               6

/* FE15_AMPLIFIER1_COMP_EN - Frontend channel 15 amplifier 1 compensation enable (COMP1) */
#define WD2_FE15_AMPLIFIER1_COMP_EN_REG                       WD2_REG_FE_CFG_14_15
#define WD2_FE15_AMPLIFIER1_COMP_EN_MASK                                0x00000020
#define WD2_FE15_AMPLIFIER1_COMP_EN_OFS                                          5

/* FE15_AMPLIFIER1_EN - Frontend channel 15 amplifier 1 enable (gain: 10) (OP1) */
#define WD2_FE15_AMPLIFIER1_EN_REG                            WD2_REG_FE_CFG_14_15
#define WD2_FE15_AMPLIFIER1_EN_MASK                                     0x00000010
#define WD2_FE15_AMPLIFIER1_EN_OFS                                               4

/* FE15_ATTENUATION - Frontend channel 15 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0) */
#define WD2_FE15_ATTENUATION_REG                              WD2_REG_FE_CFG_14_15
#define WD2_FE15_ATTENUATION_MASK                                       0x0000000C
#define WD2_FE15_ATTENUATION_OFS                                                 2

/* FE15_MUX - Frontend channel 15 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0) */
#define WD2_FE15_MUX_REG                                      WD2_REG_FE_CFG_14_15
#define WD2_FE15_MUX_MASK                                               0x00000003
#define WD2_FE15_MUX_OFS                                                         0



/* ****** Control Register 38 [0x1098]: HV_U_TARGET_0 - Target HV Supply Voltage for Channel 0 (Default: 0x00000000) ****** */

/* HV_U_TARGET_0 - Float value (u_demand) */
#define WD2_HV_U_TARGET_0_REG                                WD2_REG_HV_U_TARGET_0
#define WD2_HV_U_TARGET_0_MASK                                          0xFFFFFFFF
#define WD2_HV_U_TARGET_0_OFS                                                    0



/* ****** Control Register 39 [0x109C]: HV_U_TARGET_1 - Target HV Supply Voltage for Channel 1 (Default: 0x00000000) ****** */

/* HV_U_TARGET_1 - Float value (u_demand) */
#define WD2_HV_U_TARGET_1_REG                                WD2_REG_HV_U_TARGET_1
#define WD2_HV_U_TARGET_1_MASK                                          0xFFFFFFFF
#define WD2_HV_U_TARGET_1_OFS                                                    0



/* ****** Control Register 40 [0x10A0]: HV_U_TARGET_2 - Target HV Supply Voltage for Channel 2 (Default: 0x00000000) ****** */

/* HV_U_TARGET_2 - Float value (u_demand) */
#define WD2_HV_U_TARGET_2_REG                                WD2_REG_HV_U_TARGET_2
#define WD2_HV_U_TARGET_2_MASK                                          0xFFFFFFFF
#define WD2_HV_U_TARGET_2_OFS                                                    0



/* ****** Control Register 41 [0x10A4]: HV_U_TARGET_3 - Target HV Supply Voltage for Channel 3 (Default: 0x00000000) ****** */

/* HV_U_TARGET_3 - Float value (u_demand) */
#define WD2_HV_U_TARGET_3_REG                                WD2_REG_HV_U_TARGET_3
#define WD2_HV_U_TARGET_3_MASK                                          0xFFFFFFFF
#define WD2_HV_U_TARGET_3_OFS                                                    0



/* ****** Control Register 42 [0x10A8]: HV_U_TARGET_4 - Target HV Supply Voltage for Channel 4 (Default: 0x00000000) ****** */

/* HV_U_TARGET_4 - Float value (u_demand) */
#define WD2_HV_U_TARGET_4_REG                                WD2_REG_HV_U_TARGET_4
#define WD2_HV_U_TARGET_4_MASK                                          0xFFFFFFFF
#define WD2_HV_U_TARGET_4_OFS                                                    0



/* ****** Control Register 43 [0x10AC]: HV_U_TARGET_5 - Target HV Supply Voltage for Channel 5 (Default: 0x00000000) ****** */

/* HV_U_TARGET_5 - Float value (u_demand) */
#define WD2_HV_U_TARGET_5_REG                                WD2_REG_HV_U_TARGET_5
#define WD2_HV_U_TARGET_5_MASK                                          0xFFFFFFFF
#define WD2_HV_U_TARGET_5_OFS                                                    0



/* ****** Control Register 44 [0x10B0]: HV_U_TARGET_6 - Target HV Supply Voltage for Channel 6 (Default: 0x00000000) ****** */

/* HV_U_TARGET_6 - Float value (u_demand) */
#define WD2_HV_U_TARGET_6_REG                                WD2_REG_HV_U_TARGET_6
#define WD2_HV_U_TARGET_6_MASK                                          0xFFFFFFFF
#define WD2_HV_U_TARGET_6_OFS                                                    0



/* ****** Control Register 45 [0x10B4]: HV_U_TARGET_7 - Target HV Supply Voltage for Channel 7 (Default: 0x00000000) ****** */

/* HV_U_TARGET_7 - Float value (u_demand) */
#define WD2_HV_U_TARGET_7_REG                                WD2_REG_HV_U_TARGET_7
#define WD2_HV_U_TARGET_7_MASK                                          0xFFFFFFFF
#define WD2_HV_U_TARGET_7_OFS                                                    0



/* ****** Control Register 46 [0x10B8]: HV_U_TARGET_8 - Target HV Supply Voltage for Channel 8 (Default: 0x00000000) ****** */

/* HV_U_TARGET_8 - Float value (u_demand) */
#define WD2_HV_U_TARGET_8_REG                                WD2_REG_HV_U_TARGET_8
#define WD2_HV_U_TARGET_8_MASK                                          0xFFFFFFFF
#define WD2_HV_U_TARGET_8_OFS                                                    0



/* ****** Control Register 47 [0x10BC]: HV_U_TARGET_9 - Target HV Supply Voltage for Channel 9 (Default: 0x00000000) ****** */

/* HV_U_TARGET_9 - Float value (u_demand) */
#define WD2_HV_U_TARGET_9_REG                                WD2_REG_HV_U_TARGET_9
#define WD2_HV_U_TARGET_9_MASK                                          0xFFFFFFFF
#define WD2_HV_U_TARGET_9_OFS                                                    0



/* ****** Control Register 48 [0x10C0]: HV_U_TARGET_10 - Target HV Supply Voltage for Channel 10 (Default: 0x00000000) ****** */

/* HV_U_TARGET_10 - Float value (u_demand) */
#define WD2_HV_U_TARGET_10_REG                              WD2_REG_HV_U_TARGET_10
#define WD2_HV_U_TARGET_10_MASK                                         0xFFFFFFFF
#define WD2_HV_U_TARGET_10_OFS                                                   0



/* ****** Control Register 49 [0x10C4]: HV_U_TARGET_11 - Target HV Supply Voltage for Channel 11 (Default: 0x00000000) ****** */

/* HV_U_TARGET_11 - Float value (u_demand) */
#define WD2_HV_U_TARGET_11_REG                              WD2_REG_HV_U_TARGET_11
#define WD2_HV_U_TARGET_11_MASK                                         0xFFFFFFFF
#define WD2_HV_U_TARGET_11_OFS                                                   0



/* ****** Control Register 50 [0x10C8]: HV_U_TARGET_12 - Target HV Supply Voltage for Channel 12 (Default: 0x00000000) ****** */

/* HV_U_TARGET_12 - Float value (u_demand) */
#define WD2_HV_U_TARGET_12_REG                              WD2_REG_HV_U_TARGET_12
#define WD2_HV_U_TARGET_12_MASK                                         0xFFFFFFFF
#define WD2_HV_U_TARGET_12_OFS                                                   0



/* ****** Control Register 51 [0x10CC]: HV_U_TARGET_13 - Target HV Supply Voltage for Channel 13 (Default: 0x00000000) ****** */

/* HV_U_TARGET_13 - Float value (u_demand) */
#define WD2_HV_U_TARGET_13_REG                              WD2_REG_HV_U_TARGET_13
#define WD2_HV_U_TARGET_13_MASK                                         0xFFFFFFFF
#define WD2_HV_U_TARGET_13_OFS                                                   0



/* ****** Control Register 52 [0x10D0]: HV_U_TARGET_14 - Target HV Supply Voltage for Channel 14 (Default: 0x00000000) ****** */

/* HV_U_TARGET_14 - Float value (u_demand) */
#define WD2_HV_U_TARGET_14_REG                              WD2_REG_HV_U_TARGET_14
#define WD2_HV_U_TARGET_14_MASK                                         0xFFFFFFFF
#define WD2_HV_U_TARGET_14_OFS                                                   0



/* ****** Control Register 53 [0x10D4]: HV_U_TARGET_15 - Target HV Supply Voltage for Channel 15 (Default: 0x00000000) ****** */

/* HV_U_TARGET_15 - Float value (u_demand) */
#define WD2_HV_U_TARGET_15_REG                              WD2_REG_HV_U_TARGET_15
#define WD2_HV_U_TARGET_15_MASK                                         0xFFFFFFFF
#define WD2_HV_U_TARGET_15_OFS                                                   0



/* ****** Control Register 54 [0x10D8]: HV_R_SHUNT - Value of the HV Supply Shunt Resistor (Default: 0x00002710) ****** */

/* HV_R_SHUNT - Resistor value in Ohm (r_current) */
#define WD2_HV_R_SHUNT_REG                                      WD2_REG_HV_R_SHUNT
#define WD2_HV_R_SHUNT_MASK                                             0xFFFFFFFF
#define WD2_HV_R_SHUNT_OFS                                                       0



/* ****** Control Register 55 [0x10DC]: LMK_0 - LMK Register 0 (Default: 0x00032900) ****** */

/* LMK0_RESET - Resets LMK Registers to Their Power-On State */
#define WD2_LMK0_RESET_REG                                           WD2_REG_LMK_0
#define WD2_LMK0_RESET_MASK                                             0x80000000
#define WD2_LMK0_RESET_OFS                                                      31

/* LMK0_CLKOUT_MUX - Channel 0 Clock Output Multiplexer (see datasheet) */
#define WD2_LMK0_CLKOUT_MUX_REG                                      WD2_REG_LMK_0
#define WD2_LMK0_CLKOUT_MUX_MASK                                        0x00060000
#define WD2_LMK0_CLKOUT_MUX_OFS                                                 17

/* LMK0_CLKOUT_EN - Channel 0 Clock Output Enable (0 = Disabled, 1 = Enabled) */
#define WD2_LMK0_CLKOUT_EN_REG                                       WD2_REG_LMK_0
#define WD2_LMK0_CLKOUT_EN_MASK                                         0x00010000
#define WD2_LMK0_CLKOUT_EN_OFS                                                  16

/* LMK0_CLKOUT_DIV - Channel 0 Clock Output Divider (value x 2) (1..255) */
#define WD2_LMK0_CLKOUT_DIV_REG                                      WD2_REG_LMK_0
#define WD2_LMK0_CLKOUT_DIV_MASK                                        0x0000FF00
#define WD2_LMK0_CLKOUT_DIV_OFS                                                  8

/* LMK0_CLKOUT_DLY - Channel 0 Clock Output Delay (value x 150ps) */
#define WD2_LMK0_CLKOUT_DLY_REG                                      WD2_REG_LMK_0
#define WD2_LMK0_CLKOUT_DLY_MASK                                        0x000000F0
#define WD2_LMK0_CLKOUT_DLY_OFS                                                  4



/* ****** Control Register 56 [0x10E0]: LMK_1 - LMK Register 1 (Default: 0x00020101) ****** */

/* LMK1_CLKOUT_MUX - Channel 1 Clock Output Multiplexer (see datasheet) */
#define WD2_LMK1_CLKOUT_MUX_REG                                      WD2_REG_LMK_1
#define WD2_LMK1_CLKOUT_MUX_MASK                                        0x00060000
#define WD2_LMK1_CLKOUT_MUX_OFS                                                 17

/* LMK1_CLKOUT_EN - Channel 1 Clock Output Enable (0 = Disabled, 1 = Enabled) */
#define WD2_LMK1_CLKOUT_EN_REG                                       WD2_REG_LMK_1
#define WD2_LMK1_CLKOUT_EN_MASK                                         0x00010000
#define WD2_LMK1_CLKOUT_EN_OFS                                                  16

/* LMK1_CLKOUT_DIV - Channel 1 Clock Output Divider (value x 2) (1..255) */
#define WD2_LMK1_CLKOUT_DIV_REG                                      WD2_REG_LMK_1
#define WD2_LMK1_CLKOUT_DIV_MASK                                        0x0000FF00
#define WD2_LMK1_CLKOUT_DIV_OFS                                                  8

/* LMK1_CLKOUT_DLY - Channel 1 Clock Output Delay (value x 150ps) */
#define WD2_LMK1_CLKOUT_DLY_REG                                      WD2_REG_LMK_1
#define WD2_LMK1_CLKOUT_DLY_MASK                                        0x000000F0
#define WD2_LMK1_CLKOUT_DLY_OFS                                                  4



/* ****** Control Register 57 [0x10E4]: LMK_2 - LMK Register 2 (Default: 0x00020102) ****** */

/* LMK2_CLKOUT_MUX - Channel 2 Clock Output Multiplexer (see datasheet) */
#define WD2_LMK2_CLKOUT_MUX_REG                                      WD2_REG_LMK_2
#define WD2_LMK2_CLKOUT_MUX_MASK                                        0x00060000
#define WD2_LMK2_CLKOUT_MUX_OFS                                                 17

/* LMK2_CLKOUT_EN - Channel 2 Clock Output Enable (0 = Disabled, 1 = Enabled) */
#define WD2_LMK2_CLKOUT_EN_REG                                       WD2_REG_LMK_2
#define WD2_LMK2_CLKOUT_EN_MASK                                         0x00010000
#define WD2_LMK2_CLKOUT_EN_OFS                                                  16

/* LMK2_CLKOUT_DIV - Channel 2 Clock Output Divider (value x 2) (1..255) */
#define WD2_LMK2_CLKOUT_DIV_REG                                      WD2_REG_LMK_2
#define WD2_LMK2_CLKOUT_DIV_MASK                                        0x0000FF00
#define WD2_LMK2_CLKOUT_DIV_OFS                                                  8

/* LMK2_CLKOUT_DLY - Channel 2 Clock Output Delay (value x 150ps) */
#define WD2_LMK2_CLKOUT_DLY_REG                                      WD2_REG_LMK_2
#define WD2_LMK2_CLKOUT_DLY_MASK                                        0x000000F0
#define WD2_LMK2_CLKOUT_DLY_OFS                                                  4



/* ****** Control Register 58 [0x10E8]: LMK_3 - LMK Register 3 (Default: 0x00000103) ****** */

/* LMK3_CLKOUT_MUX - Channel 3 Clock Output Multiplexer (see datasheet) */
#define WD2_LMK3_CLKOUT_MUX_REG                                      WD2_REG_LMK_3
#define WD2_LMK3_CLKOUT_MUX_MASK                                        0x00060000
#define WD2_LMK3_CLKOUT_MUX_OFS                                                 17

/* LMK3_CLKOUT_EN - Channel 3 Clock Output Enable (0 = Disabled, 1 = Enabled) */
#define WD2_LMK3_CLKOUT_EN_REG                                       WD2_REG_LMK_3
#define WD2_LMK3_CLKOUT_EN_MASK                                         0x00010000
#define WD2_LMK3_CLKOUT_EN_OFS                                                  16

/* LMK3_CLKOUT_DIV - Channel 3 Clock Output Divider (value x 2) (1..255) */
#define WD2_LMK3_CLKOUT_DIV_REG                                      WD2_REG_LMK_3
#define WD2_LMK3_CLKOUT_DIV_MASK                                        0x0000FF00
#define WD2_LMK3_CLKOUT_DIV_OFS                                                  8

/* LMK3_CLKOUT_DLY - Channel 3 Clock Output Delay (value x 150ps) */
#define WD2_LMK3_CLKOUT_DLY_REG                                      WD2_REG_LMK_3
#define WD2_LMK3_CLKOUT_DLY_MASK                                        0x000000F0
#define WD2_LMK3_CLKOUT_DLY_OFS                                                  4



/* ****** Control Register 59 [0x10EC]: LMK_4 - LMK Register 4 (Default: 0x00030104) ****** */

/* LMK4_CLKOUT_MUX - Channel 4 Clock Output Multiplexer (see datasheet) */
#define WD2_LMK4_CLKOUT_MUX_REG                                      WD2_REG_LMK_4
#define WD2_LMK4_CLKOUT_MUX_MASK                                        0x00060000
#define WD2_LMK4_CLKOUT_MUX_OFS                                                 17

/* LMK4_CLKOUT_EN - Channel 4 Clock Output Enable (0 = Disabled, 1 = Enabled) */
#define WD2_LMK4_CLKOUT_EN_REG                                       WD2_REG_LMK_4
#define WD2_LMK4_CLKOUT_EN_MASK                                         0x00010000
#define WD2_LMK4_CLKOUT_EN_OFS                                                  16

/* LMK4_CLKOUT_DIV - Channel 4 Clock Output Divider (value x 2) (1..255) */
#define WD2_LMK4_CLKOUT_DIV_REG                                      WD2_REG_LMK_4
#define WD2_LMK4_CLKOUT_DIV_MASK                                        0x0000FF00
#define WD2_LMK4_CLKOUT_DIV_OFS                                                  8

/* LMK4_CLKOUT_DLY - Channel 4 Clock Output Delay (value x 150ps) */
#define WD2_LMK4_CLKOUT_DLY_REG                                      WD2_REG_LMK_4
#define WD2_LMK4_CLKOUT_DLY_MASK                                        0x000000F0
#define WD2_LMK4_CLKOUT_DLY_OFS                                                  4



/* ****** Control Register 60 [0x10F0]: LMK_5 - LMK Register 5 (Default: 0x00020105) ****** */

/* LMK5_CLKOUT_MUX - Channel 5 Clock Output Multiplexer (see datasheet) */
#define WD2_LMK5_CLKOUT_MUX_REG                                      WD2_REG_LMK_5
#define WD2_LMK5_CLKOUT_MUX_MASK                                        0x00060000
#define WD2_LMK5_CLKOUT_MUX_OFS                                                 17

/* LMK5_CLKOUT_EN - Channel 5 Clock Output Enable (0 = Disabled, 1 = Enabled) */
#define WD2_LMK5_CLKOUT_EN_REG                                       WD2_REG_LMK_5
#define WD2_LMK5_CLKOUT_EN_MASK                                         0x00010000
#define WD2_LMK5_CLKOUT_EN_OFS                                                  16

/* LMK5_CLKOUT_DIV - Channel 5 Clock Output Divider (value x 2) (1..255) */
#define WD2_LMK5_CLKOUT_DIV_REG                                      WD2_REG_LMK_5
#define WD2_LMK5_CLKOUT_DIV_MASK                                        0x0000FF00
#define WD2_LMK5_CLKOUT_DIV_OFS                                                  8

/* LMK5_CLKOUT_DLY - Channel 5 Clock Output Delay (value x 150ps) */
#define WD2_LMK5_CLKOUT_DLY_REG                                      WD2_REG_LMK_5
#define WD2_LMK5_CLKOUT_DLY_MASK                                        0x000000F0
#define WD2_LMK5_CLKOUT_DLY_OFS                                                  4



/* ****** Control Register 61 [0x10F4]: LMK_6 - LMK Register 6 (Default: 0x00000106) ****** */

/* LMK6_CLKOUT_MUX - Channel 6 Clock Output Multiplexer (see datasheet) */
#define WD2_LMK6_CLKOUT_MUX_REG                                      WD2_REG_LMK_6
#define WD2_LMK6_CLKOUT_MUX_MASK                                        0x00060000
#define WD2_LMK6_CLKOUT_MUX_OFS                                                 17

/* LMK6_CLKOUT_EN - Channel 6 Clock Output Enable (0 = Disabled, 1 = Enabled) */
#define WD2_LMK6_CLKOUT_EN_REG                                       WD2_REG_LMK_6
#define WD2_LMK6_CLKOUT_EN_MASK                                         0x00010000
#define WD2_LMK6_CLKOUT_EN_OFS                                                  16

/* LMK6_CLKOUT_DIV - Channel 6 Clock Output Divider (value x 2) (1..255) */
#define WD2_LMK6_CLKOUT_DIV_REG                                      WD2_REG_LMK_6
#define WD2_LMK6_CLKOUT_DIV_MASK                                        0x0000FF00
#define WD2_LMK6_CLKOUT_DIV_OFS                                                  8

/* LMK6_CLKOUT_DLY - Channel 6 Clock Output Delay (value x 150ps) */
#define WD2_LMK6_CLKOUT_DLY_REG                                      WD2_REG_LMK_6
#define WD2_LMK6_CLKOUT_DLY_MASK                                        0x000000F0
#define WD2_LMK6_CLKOUT_DLY_OFS                                                  4



/* ****** Control Register 62 [0x10F8]: LMK_7 - LMK Register 7 (Default: 0x00026407) ****** */

/* LMK7_CLKOUT_MUX - Channel 7 Clock Output Multiplexer (see datasheet) */
#define WD2_LMK7_CLKOUT_MUX_REG                                      WD2_REG_LMK_7
#define WD2_LMK7_CLKOUT_MUX_MASK                                        0x00060000
#define WD2_LMK7_CLKOUT_MUX_OFS                                                 17

/* LMK7_CLKOUT_EN - Channel 7 Clock Output Enable (0 = Disabled, 1 = Enabled) */
#define WD2_LMK7_CLKOUT_EN_REG                                       WD2_REG_LMK_7
#define WD2_LMK7_CLKOUT_EN_MASK                                         0x00010000
#define WD2_LMK7_CLKOUT_EN_OFS                                                  16

/* LMK7_CLKOUT_DIV - Channel 7 Clock Output Divider (value x 2) (1..255) */
#define WD2_LMK7_CLKOUT_DIV_REG                                      WD2_REG_LMK_7
#define WD2_LMK7_CLKOUT_DIV_MASK                                        0x0000FF00
#define WD2_LMK7_CLKOUT_DIV_OFS                                                  8

/* LMK7_CLKOUT_DLY - Channel 7 Clock Output Delay (value x 150ps) */
#define WD2_LMK7_CLKOUT_DLY_REG                                      WD2_REG_LMK_7
#define WD2_LMK7_CLKOUT_DLY_MASK                                        0x000000F0
#define WD2_LMK7_CLKOUT_DLY_OFS                                                  4



/* ****** Control Register 63 [0x10FC]: LMK_8 - LMK Register 8 (Default: 0x10000908) ****** */

/* LMK8_PHASE_NOISE_OPT - Set LMK Register 8 (Phase Noise Optimization) */
#define WD2_LMK8_PHASE_NOISE_OPT_REG                                 WD2_REG_LMK_8
#define WD2_LMK8_PHASE_NOISE_OPT_MASK                                   0xFFFFFFF0
#define WD2_LMK8_PHASE_NOISE_OPT_OFS                                             4



/* ****** Control Register 64 [0x1100]: LMK_9 - LMK Register 9 (Default: 0xA0022A09) ****** */

/* LMK9_VBOOST - Voltage Level Boost for Clock Outputs */
#define WD2_LMK9_VBOOST_REG                                          WD2_REG_LMK_9
#define WD2_LMK9_VBOOST_MASK                                            0x00010000
#define WD2_LMK9_VBOOST_OFS                                                     16



/* ****** Control Register 65 [0x1104]: LMK_11 - LMK Register 11 (Default: 0x0082000B) ****** */

/* LMK11_DIV4 - Divider Enable for Digital Lock Detect Circuit */
#define WD2_LMK11_DIV4_REG                                          WD2_REG_LMK_11
#define WD2_LMK11_DIV4_MASK                                             0x00008000
#define WD2_LMK11_DIV4_OFS                                                      15



/* ****** Control Register 66 [0x1108]: LMK_13 - LMK Register 13 (Default: 0x029900AD) ****** */

/* LMK13_OSCIN_FREQ - Oscillator Input Calibration Adjustment in MHz (1..200) */
#define WD2_LMK13_OSCIN_FREQ_REG                                    WD2_REG_LMK_13
#define WD2_LMK13_OSCIN_FREQ_MASK                                       0x003FC000
#define WD2_LMK13_OSCIN_FREQ_OFS                                                14

/* LMK13_VCO_R4_LF - Value for Internal Loop Filter Resistor R4 (0..4) (see datasheet) */
#define WD2_LMK13_VCO_R4_LF_REG                                     WD2_REG_LMK_13
#define WD2_LMK13_VCO_R4_LF_MASK                                        0x00003800
#define WD2_LMK13_VCO_R4_LF_OFS                                                 11

/* LMK13_VCO_R3_LF - Value for Internal Loop Filter Resistor R3 (0..4) (see datasheet) */
#define WD2_LMK13_VCO_R3_LF_REG                                     WD2_REG_LMK_13
#define WD2_LMK13_VCO_R3_LF_MASK                                        0x00000700
#define WD2_LMK13_VCO_R3_LF_OFS                                                  8

/* LMK13_VCO_C3_C4_LF - Value for Internal Loop Filter Capacitors C3/C4 (0..11) (see ds) */
#define WD2_LMK13_VCO_C3_C4_LF_REG                                  WD2_REG_LMK_13
#define WD2_LMK13_VCO_C3_C4_LF_MASK                                     0x000000F0
#define WD2_LMK13_VCO_C3_C4_LF_OFS                                               4



/* ****** Control Register 67 [0x110C]: LMK_14 - LMK Register 14 (Default: 0x0830140E) ****** */

/* LMK14_EN_FOUT - Enable for the Fout Pin (0 = Disabled, 1 = Enabled) */
#define WD2_LMK14_EN_FOUT_REG                                       WD2_REG_LMK_14
#define WD2_LMK14_EN_FOUT_MASK                                          0x10000000
#define WD2_LMK14_EN_FOUT_OFS                                                   28

/* LMK14_EN_CLKOUT_GLOBAL - Global Clock Output Enable (0 = All Off, 1 = Normal Operation) */
#define WD2_LMK14_EN_CLKOUT_GLOBAL_REG                              WD2_REG_LMK_14
#define WD2_LMK14_EN_CLKOUT_GLOBAL_MASK                                 0x08000000
#define WD2_LMK14_EN_CLKOUT_GLOBAL_OFS                                          27

/* LMK14_POWERDOWN - Powerdown (0 = Normal Operation, 1 = Device Powered Down) */
#define WD2_LMK14_POWERDOWN_REG                                     WD2_REG_LMK_14
#define WD2_LMK14_POWERDOWN_MASK                                        0x04000000
#define WD2_LMK14_POWERDOWN_OFS                                                 26

/* LMK14_PLL_MUX - Output Mode of  LD Pin (0..7,9,11) */
#define WD2_LMK14_PLL_MUX_REG                                       WD2_REG_LMK_14
#define WD2_LMK14_PLL_MUX_MASK                                          0x00F00000
#define WD2_LMK14_PLL_MUX_OFS                                                   20

/* LMK14_PLL_R - PLL R Divider Value (1..4095) */
#define WD2_LMK14_PLL_R_REG                                         WD2_REG_LMK_14
#define WD2_LMK14_PLL_R_MASK                                            0x000FFF00
#define WD2_LMK14_PLL_R_OFS                                                      8



/* ****** Control Register 68 [0x1110]: LMK_15 - LMK Register 15 (Default: 0xE000200F) ****** */

/* LMK15_PLL_CP_GAIN - PLL Charge Pump Gain (see datasheet) (0..4) */
#define WD2_LMK15_PLL_CP_GAIN_REG                                   WD2_REG_LMK_15
#define WD2_LMK15_PLL_CP_GAIN_MASK                                      0xC0000000
#define WD2_LMK15_PLL_CP_GAIN_OFS                                               30

/* LMK15_VCO_DIV - VCO Divider Value (2..8) */
#define WD2_LMK15_VCO_DIV_REG                                       WD2_REG_LMK_15
#define WD2_LMK15_VCO_DIV_MASK                                          0x3C000000
#define WD2_LMK15_VCO_DIV_OFS                                                   26

/* LMK15_PLL_N - PLL N Divider Value (1..0x3FFFF) */
#define WD2_LMK15_PLL_N_REG                                         WD2_REG_LMK_15
#define WD2_LMK15_PLL_N_MASK                                            0x03FFFF00
#define WD2_LMK15_PLL_N_OFS                                                      8



/* ****** Control Register 69 [0x1114]: ADC_CFG_IND_TX - ADC Chip Configuration, Index and Transfer Register (Default: 0x180F3F00) ****** */

/* ADC_CFG_SDO_ACTIVE_MSB - Activate SDO (to be mirrored to bit24) */
#define WD2_ADC_CFG_SDO_ACTIVE_MSB_REG                      WD2_REG_ADC_CFG_IND_TX
#define WD2_ADC_CFG_SDO_ACTIVE_MSB_MASK                                 0x80000000
#define WD2_ADC_CFG_SDO_ACTIVE_MSB_OFS                                          31

/* ADC_CFG_LSB_FIRST_MSB - Transmit LSB First (to be mirrored to bit25) */
#define WD2_ADC_CFG_LSB_FIRST_MSB_REG                       WD2_REG_ADC_CFG_IND_TX
#define WD2_ADC_CFG_LSB_FIRST_MSB_MASK                                  0x40000000
#define WD2_ADC_CFG_LSB_FIRST_MSB_OFS                                           30

/* ADC_CFG_SOFT_RESET_MSB - Soft Reset (automatically cleared) (to be mirrored to bit26) */
#define WD2_ADC_CFG_SOFT_RESET_MSB_REG                      WD2_REG_ADC_CFG_IND_TX
#define WD2_ADC_CFG_SOFT_RESET_MSB_MASK                                 0x20000000
#define WD2_ADC_CFG_SOFT_RESET_MSB_OFS                                          29

/* ADC_CFG_16_BIT_ADDR_MSB - ADC Address Mode (to be mirrored to bit27) */
#define WD2_ADC_CFG_16_BIT_ADDR_MSB_REG                     WD2_REG_ADC_CFG_IND_TX
#define WD2_ADC_CFG_16_BIT_ADDR_MSB_MASK                                0x10000000
#define WD2_ADC_CFG_16_BIT_ADDR_MSB_OFS                                         28

/* ADC_CFG_16_BIT_ADDR_LSB - ADC Address Mode (to be mirrored to bit28) */
#define WD2_ADC_CFG_16_BIT_ADDR_LSB_REG                     WD2_REG_ADC_CFG_IND_TX
#define WD2_ADC_CFG_16_BIT_ADDR_LSB_MASK                                0x08000000
#define WD2_ADC_CFG_16_BIT_ADDR_LSB_OFS                                         27

/* ADC_CFG_SOFT_RESET_LSB - Soft Reset (automatically cleared) (to be mirrored to bit29) */
#define WD2_ADC_CFG_SOFT_RESET_LSB_REG                      WD2_REG_ADC_CFG_IND_TX
#define WD2_ADC_CFG_SOFT_RESET_LSB_MASK                                 0x04000000
#define WD2_ADC_CFG_SOFT_RESET_LSB_OFS                                          26

/* ADC_CFG_LSB_FIRST_LSB - Transmit LSB First (to be mirrored to bit30) */
#define WD2_ADC_CFG_LSB_FIRST_LSB_REG                       WD2_REG_ADC_CFG_IND_TX
#define WD2_ADC_CFG_LSB_FIRST_LSB_MASK                                  0x02000000
#define WD2_ADC_CFG_LSB_FIRST_LSB_OFS                                           25

/* ADC_CFG_SDO_ACTIVE_LSB - Activate SDO (to be mirrored to bit31) */
#define WD2_ADC_CFG_SDO_ACTIVE_LSB_REG                      WD2_REG_ADC_CFG_IND_TX
#define WD2_ADC_CFG_SDO_ACTIVE_LSB_MASK                                 0x01000000
#define WD2_ADC_CFG_SDO_ACTIVE_LSB_OFS                                          24

/* ADC_DI2_D_CHN_H - Data Channel H Activiation for Writes */
#define WD2_ADC_DI2_D_CHN_H_REG                             WD2_REG_ADC_CFG_IND_TX
#define WD2_ADC_DI2_D_CHN_H_MASK                                        0x00080000
#define WD2_ADC_DI2_D_CHN_H_OFS                                                 19

/* ADC_DI2_D_CHN_G - Data Channel G Activiation for Writes */
#define WD2_ADC_DI2_D_CHN_G_REG                             WD2_REG_ADC_CFG_IND_TX
#define WD2_ADC_DI2_D_CHN_G_MASK                                        0x00040000
#define WD2_ADC_DI2_D_CHN_G_OFS                                                 18

/* ADC_DI2_D_CHN_F - Data Channel F Activiation for Writes */
#define WD2_ADC_DI2_D_CHN_F_REG                             WD2_REG_ADC_CFG_IND_TX
#define WD2_ADC_DI2_D_CHN_F_MASK                                        0x00020000
#define WD2_ADC_DI2_D_CHN_F_OFS                                                 17

/* ADC_DI2_D_CHN_E - Data Channel E Activiation for Writes */
#define WD2_ADC_DI2_D_CHN_E_REG                             WD2_REG_ADC_CFG_IND_TX
#define WD2_ADC_DI2_D_CHN_E_MASK                                        0x00010000
#define WD2_ADC_DI2_D_CHN_E_OFS                                                 16

/* ADC_DI1_C_CHN_DCO - Clock Channel DCO Activiation for Writes */
#define WD2_ADC_DI1_C_CHN_DCO_REG                           WD2_REG_ADC_CFG_IND_TX
#define WD2_ADC_DI1_C_CHN_DCO_MASK                                      0x00002000
#define WD2_ADC_DI1_C_CHN_DCO_OFS                                               13

/* ADC_DI1_C_CHN_FCO - Clock Channel FCO Activiation for Writes */
#define WD2_ADC_DI1_C_CHN_FCO_REG                           WD2_REG_ADC_CFG_IND_TX
#define WD2_ADC_DI1_C_CHN_FCO_MASK                                      0x00001000
#define WD2_ADC_DI1_C_CHN_FCO_OFS                                               12

/* ADC_DI1_D_CHN_D - Data Channel D Activiation for Writes */
#define WD2_ADC_DI1_D_CHN_D_REG                             WD2_REG_ADC_CFG_IND_TX
#define WD2_ADC_DI1_D_CHN_D_MASK                                        0x00000800
#define WD2_ADC_DI1_D_CHN_D_OFS                                                 11

/* ADC_DI1_D_CHN_C - Data Channel C Activiation for Writes */
#define WD2_ADC_DI1_D_CHN_C_REG                             WD2_REG_ADC_CFG_IND_TX
#define WD2_ADC_DI1_D_CHN_C_MASK                                        0x00000400
#define WD2_ADC_DI1_D_CHN_C_OFS                                                 10

/* ADC_DI1_D_CHN_B - Data Channel B Activiation for Writes */
#define WD2_ADC_DI1_D_CHN_B_REG                             WD2_REG_ADC_CFG_IND_TX
#define WD2_ADC_DI1_D_CHN_B_MASK                                        0x00000200
#define WD2_ADC_DI1_D_CHN_B_OFS                                                  9

/* ADC_DI1_D_CHN_A - Data Channel A Activiation for Writes */
#define WD2_ADC_DI1_D_CHN_A_REG                             WD2_REG_ADC_CFG_IND_TX
#define WD2_ADC_DI1_D_CHN_A_MASK                                        0x00000100
#define WD2_ADC_DI1_D_CHN_A_OFS                                                  8

/* ADC_TX_INIT_OVERRIDE - Set Resolution/Sample Rate Override */
#define WD2_ADC_TX_INIT_OVERRIDE_REG                        WD2_REG_ADC_CFG_IND_TX
#define WD2_ADC_TX_INIT_OVERRIDE_MASK                                   0x00000001
#define WD2_ADC_TX_INIT_OVERRIDE_OFS                                             0



/* ****** Control Register 70 [0x1118]: ADC_PM_CLK_ENH - ADC Power Modes, Clock, Enhancement (Default: 0x00010000) ****** */

/* ADC_PM_EXT_PD - Extrenal Power Down Pin Function (0 = full, 1 = standby) */
#define WD2_ADC_PM_EXT_PD_REG                               WD2_REG_ADC_PM_CLK_ENH
#define WD2_ADC_PM_EXT_PD_MASK                                          0x20000000
#define WD2_ADC_PM_EXT_PD_OFS                                                   29

/* ADC_PM_INT_PD_MODE - Internal Power Down Mode (see datasheet) */
#define WD2_ADC_PM_INT_PD_MODE_REG                          WD2_REG_ADC_PM_CLK_ENH
#define WD2_ADC_PM_INT_PD_MODE_MASK                                     0x03000000
#define WD2_ADC_PM_INT_PD_MODE_OFS                                              24

/* ADC_CLK_DUTY_CYC_STAB - Duty Cycle Stabilizer (0 = off, 1 = on) */
#define WD2_ADC_CLK_DUTY_CYC_STAB_REG                       WD2_REG_ADC_PM_CLK_ENH
#define WD2_ADC_CLK_DUTY_CYC_STAB_MASK                                  0x00010000
#define WD2_ADC_CLK_DUTY_CYC_STAB_OFS                                           16

/* ADC_CLK_DIV_RATIO - Clock Divide Ratio (value+1) */
#define WD2_ADC_CLK_DIV_RATIO_REG                           WD2_REG_ADC_PM_CLK_ENH
#define WD2_ADC_CLK_DIV_RATIO_MASK                                      0x00000700
#define WD2_ADC_CLK_DIV_RATIO_OFS                                                8

/* ADC_ENH_CHOP_MODE - Chop Mode (0 = off, 1 = on) */
#define WD2_ADC_ENH_CHOP_MODE_REG                           WD2_REG_ADC_PM_CLK_ENH
#define WD2_ADC_ENH_CHOP_MODE_MASK                                      0x00000010
#define WD2_ADC_ENH_CHOP_MODE_OFS                                                4



/* ****** Control Register 71 [0x111C]: ADC_TEST_OFFS_OM - ADC Test Mode, Offset Adjust and Output Mode (Default: 0x00000044) ****** */

/* ADC_TM_USR_IN_MODE - User Input Test Mode (see datasheet) (Local) */
#define WD2_ADC_TM_USR_IN_MODE_REG                        WD2_REG_ADC_TEST_OFFS_OM
#define WD2_ADC_TM_USR_IN_MODE_MASK                                     0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_OFS                                              22

/* ADC_TM_RST_PN_LONG_GEN - Reset Pseudo Random Long Generator (Global) */
#define WD2_ADC_TM_RST_PN_LONG_GEN_REG                    WD2_REG_ADC_TEST_OFFS_OM
#define WD2_ADC_TM_RST_PN_LONG_GEN_MASK                                 0x00200000
#define WD2_ADC_TM_RST_PN_LONG_GEN_OFS                                          21

/* ADC_TM_RST_PN_SHORT_GEN - Reset Pseudo Random Short Generator (Global) */
#define WD2_ADC_TM_RST_PN_SHORT_GEN_REG                   WD2_REG_ADC_TEST_OFFS_OM
#define WD2_ADC_TM_RST_PN_SHORT_GEN_MASK                                0x00100000
#define WD2_ADC_TM_RST_PN_SHORT_GEN_OFS                                         20

/* ADC_TM_OUT - Output Test Mode (see datasheet) (Local) */
#define WD2_ADC_TM_OUT_REG                                WD2_REG_ADC_TEST_OFFS_OM
#define WD2_ADC_TM_OUT_MASK                                             0x000F0000
#define WD2_ADC_TM_OUT_OFS                                                      16

/* ADC_OFFS_ADJ - Device Offset Trim (Local) */
#define WD2_ADC_OFFS_ADJ_REG                              WD2_REG_ADC_TEST_OFFS_OM
#define WD2_ADC_OFFS_ADJ_MASK                                           0x0000FF00
#define WD2_ADC_OFFS_ADJ_OFS                                                     8

/* ADC_OM_LVDS_MODE - LVDS ANSI/IEEE Option (0 = ANSI, 1 = IEEE) (Global) */
#define WD2_ADC_OM_LVDS_MODE_REG                          WD2_REG_ADC_TEST_OFFS_OM
#define WD2_ADC_OM_LVDS_MODE_MASK                                       0x00000040
#define WD2_ADC_OM_LVDS_MODE_OFS                                                 6

/* ADC_OM_OUT_INVERT - Output Invert (Local) */
#define WD2_ADC_OM_OUT_INVERT_REG                         WD2_REG_ADC_TEST_OFFS_OM
#define WD2_ADC_OM_OUT_INVERT_MASK                                      0x00000004
#define WD2_ADC_OM_OUT_INVERT_OFS                                                2

/* ADC_OM_OUT_FORMAT - Output Format (0 = offset binary, 1 = twos complement) (Global) */
#define WD2_ADC_OM_OUT_FORMAT_REG                         WD2_REG_ADC_TEST_OFFS_OM
#define WD2_ADC_OM_OUT_FORMAT_MASK                                      0x00000001
#define WD2_ADC_OM_OUT_FORMAT_OFS                                                0



/* ****** Control Register 72 [0x1120]: ADC_OUT_VREF - ADC Output and Vref Settings (Default: 0x00300304) ****** */

/* ADC_OA_OUT_DRV_TERM - Output Driver Termination (see datasheet) */
#define WD2_ADC_OA_OUT_DRV_TERM_REG                           WD2_REG_ADC_OUT_VREF
#define WD2_ADC_OA_OUT_DRV_TERM_MASK                                    0x00300000
#define WD2_ADC_OA_OUT_DRV_TERM_OFS                                             20

/* ADC_OA_OUT_DRIVE - Output Drive (0 = 1x, 1 = 2x) */
#define WD2_ADC_OA_OUT_DRIVE_REG                              WD2_REG_ADC_OUT_VREF
#define WD2_ADC_OA_OUT_DRIVE_MASK                                       0x00010000
#define WD2_ADC_OA_OUT_DRIVE_OFS                                                16

/* ADC_OP_IN_CLK_PH_ADJ - Input Clock Phase Adjust (see datasheet) */
#define WD2_ADC_OP_IN_CLK_PH_ADJ_REG                          WD2_REG_ADC_OUT_VREF
#define WD2_ADC_OP_IN_CLK_PH_ADJ_MASK                                   0x00007000
#define WD2_ADC_OP_IN_CLK_PH_ADJ_OFS                                            12

/* ADC_OP_OUT_CLK_PH_ADJ - Output Clock Phase Adjust (see datasheet) */
#define WD2_ADC_OP_OUT_CLK_PH_ADJ_REG                         WD2_REG_ADC_OUT_VREF
#define WD2_ADC_OP_OUT_CLK_PH_ADJ_MASK                                  0x00000F00
#define WD2_ADC_OP_OUT_CLK_PH_ADJ_OFS                                            8

/* ADC_INT_VREF_ADJ - Internal Vref Adjustment Digital Scheme (see datasheet) */
#define WD2_ADC_INT_VREF_ADJ_REG                              WD2_REG_ADC_OUT_VREF
#define WD2_ADC_INT_VREF_ADJ_MASK                                       0x00000007
#define WD2_ADC_INT_VREF_ADJ_OFS                                                 0



/* ****** Control Register 73 [0x1124]: ADC_USR_PATT - ADC User Patterns (Default: 0xFC00FC00) ****** */

/* ADC_USR_PATT1 - ADC User Pattern 1 (0x1A, 0x19) (Global) */
#define WD2_ADC_USR_PATT1_REG                                 WD2_REG_ADC_USR_PATT
#define WD2_ADC_USR_PATT1_MASK                                          0xFFFF0000
#define WD2_ADC_USR_PATT1_OFS                                                   16

/* ADC_USR_PATT2 - ADC User Pattern 2 (0x1C, 0x1B) (Global) */
#define WD2_ADC_USR_PATT2_REG                                 WD2_REG_ADC_USR_PATT
#define WD2_ADC_USR_PATT2_MASK                                          0x0000FFFF
#define WD2_ADC_USR_PATT2_OFS                                                    0



/* ****** Control Register 74 [0x1128]: ADC_SER_RES_SR - ADC Serial Control and Resolution/Sample Rate Override (Default: 0x00420000) ****** */

/* ADC_SC_LVDS_OUT_LSB_FIRST - LVDS Output LSB First */
#define WD2_ADC_SC_LVDS_OUT_LSB_FIRST_REG                   WD2_REG_ADC_SER_RES_SR
#define WD2_ADC_SC_LVDS_OUT_LSB_FIRST_MASK                              0x00800000
#define WD2_ADC_SC_LVDS_OUT_LSB_FIRST_OFS                                       23

/* ADC_SC_WORD_WISE_DDR - Word-Wise DDR 1-Lane (see datasheet) */
#define WD2_ADC_SC_WORD_WISE_DDR_REG                        WD2_REG_ADC_SER_RES_SR
#define WD2_ADC_SC_WORD_WISE_DDR_MASK                                   0x00700000
#define WD2_ADC_SC_WORD_WISE_DDR_OFS                                            20

/* ADC_SC_OUT_NR_BITS - Serial Output Number of Bits (10 = 12bits, 11 = 10bits) */
#define WD2_ADC_SC_OUT_NR_BITS_REG                          WD2_REG_ADC_SER_RES_SR
#define WD2_ADC_SC_OUT_NR_BITS_MASK                                     0x00030000
#define WD2_ADC_SC_OUT_NR_BITS_OFS                                              16

/* ADC_SC_OUT_RST - Serial Channel Status Output Reset */
#define WD2_ADC_SC_OUT_RST_REG                              WD2_REG_ADC_SER_RES_SR
#define WD2_ADC_SC_OUT_RST_MASK                                         0x00000200
#define WD2_ADC_SC_OUT_RST_OFS                                                   9

/* ADC_SC_PWR_DN - Serial Channel Status Power Down */
#define WD2_ADC_SC_PWR_DN_REG                               WD2_REG_ADC_SER_RES_SR
#define WD2_ADC_SC_PWR_DN_MASK                                          0x00000100
#define WD2_ADC_SC_PWR_DN_OFS                                                    8

/* ADC_RES_SR_OVR - Resolution/Sample Rate Override Enable */
#define WD2_ADC_RES_SR_OVR_REG                              WD2_REG_ADC_SER_RES_SR
#define WD2_ADC_RES_SR_OVR_MASK                                         0x00000040
#define WD2_ADC_RES_SR_OVR_OFS                                                   6

/* ADC_RESOLUTION - Resolution (10 = 12bits, 11 = 10bits) */
#define WD2_ADC_RESOLUTION_REG                              WD2_REG_ADC_SER_RES_SR
#define WD2_ADC_RESOLUTION_MASK                                         0x00000030
#define WD2_ADC_RESOLUTION_OFS                                                   4

/* ADC_SAMPLE_RATE - Sample Rate (see datasheet) */
#define WD2_ADC_SAMPLE_RATE_REG                             WD2_REG_ADC_SER_RES_SR
#define WD2_ADC_SAMPLE_RATE_MASK                                        0x00000007
#define WD2_ADC_SAMPLE_RATE_OFS                                                  0



/* ****** Control Register 75 [0x112C]: ADC_USR_IO_SYNC - ADC User I/O Control and Sync (Default: 0x00000000) ****** */

/* ADC_UIOC2_SDIO_PD - SDIO Pull-Down Disable */
#define WD2_ADC_UIOC2_SDIO_PD_REG                          WD2_REG_ADC_USR_IO_SYNC
#define WD2_ADC_UIOC2_SDIO_PD_MASK                                      0x00010000
#define WD2_ADC_UIOC2_SDIO_PD_OFS                                               16

/* ADC_UIOC3_VCM_PWR_DN - VCM Power Control */
#define WD2_ADC_UIOC3_VCM_PWR_DN_REG                       WD2_REG_ADC_USR_IO_SYNC
#define WD2_ADC_UIOC3_VCM_PWR_DN_MASK                                   0x00000800
#define WD2_ADC_UIOC3_VCM_PWR_DN_OFS                                            11

/* ADC_SYNC_NEXT_ONLY - Sync Next Only */
#define WD2_ADC_SYNC_NEXT_ONLY_REG                         WD2_REG_ADC_USR_IO_SYNC
#define WD2_ADC_SYNC_NEXT_ONLY_MASK                                     0x00000002
#define WD2_ADC_SYNC_NEXT_ONLY_OFS                                               1

/* ADC_EN_SYNC - Enable Sync */
#define WD2_ADC_EN_SYNC_REG                                WD2_REG_ADC_USR_IO_SYNC
#define WD2_ADC_EN_SYNC_MASK                                            0x00000001
#define WD2_ADC_EN_SYNC_OFS                                                      0



/* ****** Control Register 76 [0x1130]: ADC_0_CH_A_CFG - ADC 0 (A) Channel A Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ****** */

/* ADC_TM_USR_IN_MODE_0_A - User Input Test Mode (see datasheet) */
#define WD2_ADC_TM_USR_IN_MODE_0_A_REG                      WD2_REG_ADC_0_CH_A_CFG
#define WD2_ADC_TM_USR_IN_MODE_0_A_MASK                                 0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_0_A_OFS                                          22

/* ADC_TM_OUT_0_A - Output Test Mode (see datasheet) */
#define WD2_ADC_TM_OUT_0_A_REG                              WD2_REG_ADC_0_CH_A_CFG
#define WD2_ADC_TM_OUT_0_A_MASK                                         0x000F0000
#define WD2_ADC_TM_OUT_0_A_OFS                                                  16

/* ADC_OFFS_ADJ_0_A - Device Offset Trim */
#define WD2_ADC_OFFS_ADJ_0_A_REG                            WD2_REG_ADC_0_CH_A_CFG
#define WD2_ADC_OFFS_ADJ_0_A_MASK                                       0x0000FF00
#define WD2_ADC_OFFS_ADJ_0_A_OFS                                                 8

/* ADC_OM_OUT_INVERT_0_A - Output Invert */
#define WD2_ADC_OM_OUT_INVERT_0_A_REG                       WD2_REG_ADC_0_CH_A_CFG
#define WD2_ADC_OM_OUT_INVERT_0_A_MASK                                  0x00000004
#define WD2_ADC_OM_OUT_INVERT_0_A_OFS                                            2



/* ****** Control Register 77 [0x1134]: ADC_0_CH_B_CFG - ADC 0 (A) Channel B Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ****** */

/* ADC_TM_USR_IN_MODE_0_B - User Input Test Mode (see datasheet) */
#define WD2_ADC_TM_USR_IN_MODE_0_B_REG                      WD2_REG_ADC_0_CH_B_CFG
#define WD2_ADC_TM_USR_IN_MODE_0_B_MASK                                 0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_0_B_OFS                                          22

/* ADC_TM_OUT_0_B - Output Test Mode (see datasheet) */
#define WD2_ADC_TM_OUT_0_B_REG                              WD2_REG_ADC_0_CH_B_CFG
#define WD2_ADC_TM_OUT_0_B_MASK                                         0x000F0000
#define WD2_ADC_TM_OUT_0_B_OFS                                                  16

/* ADC_OFFS_ADJ_0_B - Device Offset Trim */
#define WD2_ADC_OFFS_ADJ_0_B_REG                            WD2_REG_ADC_0_CH_B_CFG
#define WD2_ADC_OFFS_ADJ_0_B_MASK                                       0x0000FF00
#define WD2_ADC_OFFS_ADJ_0_B_OFS                                                 8

/* ADC_OM_OUT_INVERT_0_B - Output Invert */
#define WD2_ADC_OM_OUT_INVERT_0_B_REG                       WD2_REG_ADC_0_CH_B_CFG
#define WD2_ADC_OM_OUT_INVERT_0_B_MASK                                  0x00000004
#define WD2_ADC_OM_OUT_INVERT_0_B_OFS                                            2



/* ****** Control Register 78 [0x1138]: ADC_0_CH_C_CFG - ADC 0 (A) Channel C Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ****** */

/* ADC_TM_USR_IN_MODE_0_C - User Input Test Mode (see datasheet) */
#define WD2_ADC_TM_USR_IN_MODE_0_C_REG                      WD2_REG_ADC_0_CH_C_CFG
#define WD2_ADC_TM_USR_IN_MODE_0_C_MASK                                 0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_0_C_OFS                                          22

/* ADC_TM_OUT_0_C - Output Test Mode (see datasheet) */
#define WD2_ADC_TM_OUT_0_C_REG                              WD2_REG_ADC_0_CH_C_CFG
#define WD2_ADC_TM_OUT_0_C_MASK                                         0x000F0000
#define WD2_ADC_TM_OUT_0_C_OFS                                                  16

/* ADC_OFFS_ADJ_0_C - Device Offset Trim */
#define WD2_ADC_OFFS_ADJ_0_C_REG                            WD2_REG_ADC_0_CH_C_CFG
#define WD2_ADC_OFFS_ADJ_0_C_MASK                                       0x0000FF00
#define WD2_ADC_OFFS_ADJ_0_C_OFS                                                 8

/* ADC_OM_OUT_INVERT_0_C - Output Invert */
#define WD2_ADC_OM_OUT_INVERT_0_C_REG                       WD2_REG_ADC_0_CH_C_CFG
#define WD2_ADC_OM_OUT_INVERT_0_C_MASK                                  0x00000004
#define WD2_ADC_OM_OUT_INVERT_0_C_OFS                                            2



/* ****** Control Register 79 [0x113C]: ADC_0_CH_D_CFG - ADC 0 (A) Channel D Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ****** */

/* ADC_TM_USR_IN_MODE_0_D - User Input Test Mode (see datasheet) */
#define WD2_ADC_TM_USR_IN_MODE_0_D_REG                      WD2_REG_ADC_0_CH_D_CFG
#define WD2_ADC_TM_USR_IN_MODE_0_D_MASK                                 0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_0_D_OFS                                          22

/* ADC_TM_OUT_0_D - Output Test Mode (see datasheet) */
#define WD2_ADC_TM_OUT_0_D_REG                              WD2_REG_ADC_0_CH_D_CFG
#define WD2_ADC_TM_OUT_0_D_MASK                                         0x000F0000
#define WD2_ADC_TM_OUT_0_D_OFS                                                  16

/* ADC_OFFS_ADJ_0_D - Device Offset Trim */
#define WD2_ADC_OFFS_ADJ_0_D_REG                            WD2_REG_ADC_0_CH_D_CFG
#define WD2_ADC_OFFS_ADJ_0_D_MASK                                       0x0000FF00
#define WD2_ADC_OFFS_ADJ_0_D_OFS                                                 8

/* ADC_OM_OUT_INVERT_0_D - Output Invert */
#define WD2_ADC_OM_OUT_INVERT_0_D_REG                       WD2_REG_ADC_0_CH_D_CFG
#define WD2_ADC_OM_OUT_INVERT_0_D_MASK                                  0x00000004
#define WD2_ADC_OM_OUT_INVERT_0_D_OFS                                            2



/* ****** Control Register 80 [0x1140]: ADC_0_CH_E_CFG - ADC 0 (A) Channel E Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ****** */

/* ADC_TM_USR_IN_MODE_0_E - User Input Test Mode (see datasheet) */
#define WD2_ADC_TM_USR_IN_MODE_0_E_REG                      WD2_REG_ADC_0_CH_E_CFG
#define WD2_ADC_TM_USR_IN_MODE_0_E_MASK                                 0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_0_E_OFS                                          22

/* ADC_TM_OUT_0_E - Output Test Mode (see datasheet) */
#define WD2_ADC_TM_OUT_0_E_REG                              WD2_REG_ADC_0_CH_E_CFG
#define WD2_ADC_TM_OUT_0_E_MASK                                         0x000F0000
#define WD2_ADC_TM_OUT_0_E_OFS                                                  16

/* ADC_OFFS_ADJ_0_E - Device Offset Trim */
#define WD2_ADC_OFFS_ADJ_0_E_REG                            WD2_REG_ADC_0_CH_E_CFG
#define WD2_ADC_OFFS_ADJ_0_E_MASK                                       0x0000FF00
#define WD2_ADC_OFFS_ADJ_0_E_OFS                                                 8

/* ADC_OM_OUT_INVERT_0_E - Output Invert */
#define WD2_ADC_OM_OUT_INVERT_0_E_REG                       WD2_REG_ADC_0_CH_E_CFG
#define WD2_ADC_OM_OUT_INVERT_0_E_MASK                                  0x00000004
#define WD2_ADC_OM_OUT_INVERT_0_E_OFS                                            2



/* ****** Control Register 81 [0x1144]: ADC_0_CH_F_CFG - ADC 0 (A) Channel F Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ****** */

/* ADC_TM_USR_IN_MODE_0_F - User Input Test Mode (see datasheet) */
#define WD2_ADC_TM_USR_IN_MODE_0_F_REG                      WD2_REG_ADC_0_CH_F_CFG
#define WD2_ADC_TM_USR_IN_MODE_0_F_MASK                                 0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_0_F_OFS                                          22

/* ADC_TM_OUT_0_F - Output Test Mode (see datasheet) */
#define WD2_ADC_TM_OUT_0_F_REG                              WD2_REG_ADC_0_CH_F_CFG
#define WD2_ADC_TM_OUT_0_F_MASK                                         0x000F0000
#define WD2_ADC_TM_OUT_0_F_OFS                                                  16

/* ADC_OFFS_ADJ_0_F - Device Offset Trim */
#define WD2_ADC_OFFS_ADJ_0_F_REG                            WD2_REG_ADC_0_CH_F_CFG
#define WD2_ADC_OFFS_ADJ_0_F_MASK                                       0x0000FF00
#define WD2_ADC_OFFS_ADJ_0_F_OFS                                                 8

/* ADC_OM_OUT_INVERT_0_F - Output Invert */
#define WD2_ADC_OM_OUT_INVERT_0_F_REG                       WD2_REG_ADC_0_CH_F_CFG
#define WD2_ADC_OM_OUT_INVERT_0_F_MASK                                  0x00000004
#define WD2_ADC_OM_OUT_INVERT_0_F_OFS                                            2



/* ****** Control Register 82 [0x1148]: ADC_0_CH_G_CFG - ADC 0 (A) Channel G Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ****** */

/* ADC_TM_USR_IN_MODE_0_G - User Input Test Mode (see datasheet) */
#define WD2_ADC_TM_USR_IN_MODE_0_G_REG                      WD2_REG_ADC_0_CH_G_CFG
#define WD2_ADC_TM_USR_IN_MODE_0_G_MASK                                 0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_0_G_OFS                                          22

/* ADC_TM_OUT_0_G - Output Test Mode (see datasheet) */
#define WD2_ADC_TM_OUT_0_G_REG                              WD2_REG_ADC_0_CH_G_CFG
#define WD2_ADC_TM_OUT_0_G_MASK                                         0x000F0000
#define WD2_ADC_TM_OUT_0_G_OFS                                                  16

/* ADC_OFFS_ADJ_0_G - Device Offset Trim */
#define WD2_ADC_OFFS_ADJ_0_G_REG                            WD2_REG_ADC_0_CH_G_CFG
#define WD2_ADC_OFFS_ADJ_0_G_MASK                                       0x0000FF00
#define WD2_ADC_OFFS_ADJ_0_G_OFS                                                 8

/* ADC_OM_OUT_INVERT_0_G - Output Invert */
#define WD2_ADC_OM_OUT_INVERT_0_G_REG                       WD2_REG_ADC_0_CH_G_CFG
#define WD2_ADC_OM_OUT_INVERT_0_G_MASK                                  0x00000004
#define WD2_ADC_OM_OUT_INVERT_0_G_OFS                                            2



/* ****** Control Register 83 [0x114C]: ADC_0_CH_H_CFG - ADC 0 (A) Channel H Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000000) ****** */

/* ADC_TM_USR_IN_MODE_0_H - User Input Test Mode (see datasheet) */
#define WD2_ADC_TM_USR_IN_MODE_0_H_REG                      WD2_REG_ADC_0_CH_H_CFG
#define WD2_ADC_TM_USR_IN_MODE_0_H_MASK                                 0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_0_H_OFS                                          22

/* ADC_TM_OUT_0_H - Output Test Mode (see datasheet) */
#define WD2_ADC_TM_OUT_0_H_REG                              WD2_REG_ADC_0_CH_H_CFG
#define WD2_ADC_TM_OUT_0_H_MASK                                         0x000F0000
#define WD2_ADC_TM_OUT_0_H_OFS                                                  16

/* ADC_OFFS_ADJ_0_H - Device Offset Trim */
#define WD2_ADC_OFFS_ADJ_0_H_REG                            WD2_REG_ADC_0_CH_H_CFG
#define WD2_ADC_OFFS_ADJ_0_H_MASK                                       0x0000FF00
#define WD2_ADC_OFFS_ADJ_0_H_OFS                                                 8

/* ADC_OM_OUT_INVERT_0_H - Output Invert */
#define WD2_ADC_OM_OUT_INVERT_0_H_REG                       WD2_REG_ADC_0_CH_H_CFG
#define WD2_ADC_OM_OUT_INVERT_0_H_MASK                                  0x00000004
#define WD2_ADC_OM_OUT_INVERT_0_H_OFS                                            2



/* ****** Control Register 84 [0x1150]: ADC_0_CH_DCO_CFG - ADC 0 (A) Channel DCO Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000000) ****** */

/* ADC_TM_USR_IN_MODE_0_DCO - User Input Test Mode (see datasheet) */
#define WD2_ADC_TM_USR_IN_MODE_0_DCO_REG                  WD2_REG_ADC_0_CH_DCO_CFG
#define WD2_ADC_TM_USR_IN_MODE_0_DCO_MASK                               0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_0_DCO_OFS                                        22

/* ADC_TM_OUT_0_DCO - Output Test Mode (see datasheet) */
#define WD2_ADC_TM_OUT_0_DCO_REG                          WD2_REG_ADC_0_CH_DCO_CFG
#define WD2_ADC_TM_OUT_0_DCO_MASK                                       0x000F0000
#define WD2_ADC_TM_OUT_0_DCO_OFS                                                16

/* ADC_OFFS_ADJ_0_DCO - Device Offset Trim */
#define WD2_ADC_OFFS_ADJ_0_DCO_REG                        WD2_REG_ADC_0_CH_DCO_CFG
#define WD2_ADC_OFFS_ADJ_0_DCO_MASK                                     0x0000FF00
#define WD2_ADC_OFFS_ADJ_0_DCO_OFS                                               8

/* ADC_OM_OUT_INVERT_0_DCO - Output Invert */
#define WD2_ADC_OM_OUT_INVERT_0_DCO_REG                   WD2_REG_ADC_0_CH_DCO_CFG
#define WD2_ADC_OM_OUT_INVERT_0_DCO_MASK                                0x00000004
#define WD2_ADC_OM_OUT_INVERT_0_DCO_OFS                                          2



/* ****** Control Register 85 [0x1154]: ADC_0_CH_FCO_CFG - ADC 0 (A) Channel FCO Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000000) ****** */

/* ADC_TM_USR_IN_MODE_0_FCO - User Input Test Mode (see datasheet) */
#define WD2_ADC_TM_USR_IN_MODE_0_FCO_REG                  WD2_REG_ADC_0_CH_FCO_CFG
#define WD2_ADC_TM_USR_IN_MODE_0_FCO_MASK                               0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_0_FCO_OFS                                        22

/* ADC_TM_OUT_0_FCO - Output Test Mode (see datasheet) */
#define WD2_ADC_TM_OUT_0_FCO_REG                          WD2_REG_ADC_0_CH_FCO_CFG
#define WD2_ADC_TM_OUT_0_FCO_MASK                                       0x000F0000
#define WD2_ADC_TM_OUT_0_FCO_OFS                                                16

/* ADC_OFFS_ADJ_0_FCO - Device Offset Trim */
#define WD2_ADC_OFFS_ADJ_0_FCO_REG                        WD2_REG_ADC_0_CH_FCO_CFG
#define WD2_ADC_OFFS_ADJ_0_FCO_MASK                                     0x0000FF00
#define WD2_ADC_OFFS_ADJ_0_FCO_OFS                                               8

/* ADC_OM_OUT_INVERT_0_FCO - Output Invert */
#define WD2_ADC_OM_OUT_INVERT_0_FCO_REG                   WD2_REG_ADC_0_CH_FCO_CFG
#define WD2_ADC_OM_OUT_INVERT_0_FCO_MASK                                0x00000004
#define WD2_ADC_OM_OUT_INVERT_0_FCO_OFS                                          2



/* ****** Control Register 86 [0x1158]: ADC_1_CH_A_CFG - ADC 1 (B) Channel A Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ****** */

/* ADC_TM_USR_IN_MODE_1_A - User Input Test Mode (see datasheet) */
#define WD2_ADC_TM_USR_IN_MODE_1_A_REG                      WD2_REG_ADC_1_CH_A_CFG
#define WD2_ADC_TM_USR_IN_MODE_1_A_MASK                                 0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_1_A_OFS                                          22

/* ADC_TM_OUT_1_A - Output Test Mode (see datasheet) */
#define WD2_ADC_TM_OUT_1_A_REG                              WD2_REG_ADC_1_CH_A_CFG
#define WD2_ADC_TM_OUT_1_A_MASK                                         0x000F0000
#define WD2_ADC_TM_OUT_1_A_OFS                                                  16

/* ADC_OFFS_ADJ_1_A - Device Offset Trim */
#define WD2_ADC_OFFS_ADJ_1_A_REG                            WD2_REG_ADC_1_CH_A_CFG
#define WD2_ADC_OFFS_ADJ_1_A_MASK                                       0x0000FF00
#define WD2_ADC_OFFS_ADJ_1_A_OFS                                                 8

/* ADC_OM_OUT_INVERT_1_A - Output Invert */
#define WD2_ADC_OM_OUT_INVERT_1_A_REG                       WD2_REG_ADC_1_CH_A_CFG
#define WD2_ADC_OM_OUT_INVERT_1_A_MASK                                  0x00000004
#define WD2_ADC_OM_OUT_INVERT_1_A_OFS                                            2



/* ****** Control Register 87 [0x115C]: ADC_1_CH_B_CFG - ADC 1 (B) Channel B Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ****** */

/* ADC_TM_USR_IN_MODE_1_B - User Input Test Mode (see datasheet) */
#define WD2_ADC_TM_USR_IN_MODE_1_B_REG                      WD2_REG_ADC_1_CH_B_CFG
#define WD2_ADC_TM_USR_IN_MODE_1_B_MASK                                 0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_1_B_OFS                                          22

/* ADC_TM_OUT_1_B - Output Test Mode (see datasheet) */
#define WD2_ADC_TM_OUT_1_B_REG                              WD2_REG_ADC_1_CH_B_CFG
#define WD2_ADC_TM_OUT_1_B_MASK                                         0x000F0000
#define WD2_ADC_TM_OUT_1_B_OFS                                                  16

/* ADC_OFFS_ADJ_1_B - Device Offset Trim */
#define WD2_ADC_OFFS_ADJ_1_B_REG                            WD2_REG_ADC_1_CH_B_CFG
#define WD2_ADC_OFFS_ADJ_1_B_MASK                                       0x0000FF00
#define WD2_ADC_OFFS_ADJ_1_B_OFS                                                 8

/* ADC_OM_OUT_INVERT_1_B - Output Invert */
#define WD2_ADC_OM_OUT_INVERT_1_B_REG                       WD2_REG_ADC_1_CH_B_CFG
#define WD2_ADC_OM_OUT_INVERT_1_B_MASK                                  0x00000004
#define WD2_ADC_OM_OUT_INVERT_1_B_OFS                                            2



/* ****** Control Register 88 [0x1160]: ADC_1_CH_C_CFG - ADC 1 (B) Channel C Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ****** */

/* ADC_TM_USR_IN_MODE_1_C - User Input Test Mode (see datasheet) */
#define WD2_ADC_TM_USR_IN_MODE_1_C_REG                      WD2_REG_ADC_1_CH_C_CFG
#define WD2_ADC_TM_USR_IN_MODE_1_C_MASK                                 0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_1_C_OFS                                          22

/* ADC_TM_OUT_1_C - Output Test Mode (see datasheet) */
#define WD2_ADC_TM_OUT_1_C_REG                              WD2_REG_ADC_1_CH_C_CFG
#define WD2_ADC_TM_OUT_1_C_MASK                                         0x000F0000
#define WD2_ADC_TM_OUT_1_C_OFS                                                  16

/* ADC_OFFS_ADJ_1_C - Device Offset Trim */
#define WD2_ADC_OFFS_ADJ_1_C_REG                            WD2_REG_ADC_1_CH_C_CFG
#define WD2_ADC_OFFS_ADJ_1_C_MASK                                       0x0000FF00
#define WD2_ADC_OFFS_ADJ_1_C_OFS                                                 8

/* ADC_OM_OUT_INVERT_1_C - Output Invert */
#define WD2_ADC_OM_OUT_INVERT_1_C_REG                       WD2_REG_ADC_1_CH_C_CFG
#define WD2_ADC_OM_OUT_INVERT_1_C_MASK                                  0x00000004
#define WD2_ADC_OM_OUT_INVERT_1_C_OFS                                            2



/* ****** Control Register 89 [0x1164]: ADC_1_CH_D_CFG - ADC 1 (B) Channel D Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ****** */

/* ADC_TM_USR_IN_MODE_1_D - User Input Test Mode (see datasheet) */
#define WD2_ADC_TM_USR_IN_MODE_1_D_REG                      WD2_REG_ADC_1_CH_D_CFG
#define WD2_ADC_TM_USR_IN_MODE_1_D_MASK                                 0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_1_D_OFS                                          22

/* ADC_TM_OUT_1_D - Output Test Mode (see datasheet) */
#define WD2_ADC_TM_OUT_1_D_REG                              WD2_REG_ADC_1_CH_D_CFG
#define WD2_ADC_TM_OUT_1_D_MASK                                         0x000F0000
#define WD2_ADC_TM_OUT_1_D_OFS                                                  16

/* ADC_OFFS_ADJ_1_D - Device Offset Trim */
#define WD2_ADC_OFFS_ADJ_1_D_REG                            WD2_REG_ADC_1_CH_D_CFG
#define WD2_ADC_OFFS_ADJ_1_D_MASK                                       0x0000FF00
#define WD2_ADC_OFFS_ADJ_1_D_OFS                                                 8

/* ADC_OM_OUT_INVERT_1_D - Output Invert */
#define WD2_ADC_OM_OUT_INVERT_1_D_REG                       WD2_REG_ADC_1_CH_D_CFG
#define WD2_ADC_OM_OUT_INVERT_1_D_MASK                                  0x00000004
#define WD2_ADC_OM_OUT_INVERT_1_D_OFS                                            2



/* ****** Control Register 90 [0x1168]: ADC_1_CH_E_CFG - ADC 1 (B) Channel E Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ****** */

/* ADC_TM_USR_IN_MODE_1_E - User Input Test Mode (see datasheet) */
#define WD2_ADC_TM_USR_IN_MODE_1_E_REG                      WD2_REG_ADC_1_CH_E_CFG
#define WD2_ADC_TM_USR_IN_MODE_1_E_MASK                                 0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_1_E_OFS                                          22

/* ADC_TM_OUT_1_E - Output Test Mode (see datasheet) */
#define WD2_ADC_TM_OUT_1_E_REG                              WD2_REG_ADC_1_CH_E_CFG
#define WD2_ADC_TM_OUT_1_E_MASK                                         0x000F0000
#define WD2_ADC_TM_OUT_1_E_OFS                                                  16

/* ADC_OFFS_ADJ_1_E - Device Offset Trim */
#define WD2_ADC_OFFS_ADJ_1_E_REG                            WD2_REG_ADC_1_CH_E_CFG
#define WD2_ADC_OFFS_ADJ_1_E_MASK                                       0x0000FF00
#define WD2_ADC_OFFS_ADJ_1_E_OFS                                                 8

/* ADC_OM_OUT_INVERT_1_E - Output Invert */
#define WD2_ADC_OM_OUT_INVERT_1_E_REG                       WD2_REG_ADC_1_CH_E_CFG
#define WD2_ADC_OM_OUT_INVERT_1_E_MASK                                  0x00000004
#define WD2_ADC_OM_OUT_INVERT_1_E_OFS                                            2



/* ****** Control Register 91 [0x116C]: ADC_1_CH_F_CFG - ADC 1 (B) Channel F Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ****** */

/* ADC_TM_USR_IN_MODE_1_F - User Input Test Mode (see datasheet) */
#define WD2_ADC_TM_USR_IN_MODE_1_F_REG                      WD2_REG_ADC_1_CH_F_CFG
#define WD2_ADC_TM_USR_IN_MODE_1_F_MASK                                 0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_1_F_OFS                                          22

/* ADC_TM_OUT_1_F - Output Test Mode (see datasheet) */
#define WD2_ADC_TM_OUT_1_F_REG                              WD2_REG_ADC_1_CH_F_CFG
#define WD2_ADC_TM_OUT_1_F_MASK                                         0x000F0000
#define WD2_ADC_TM_OUT_1_F_OFS                                                  16

/* ADC_OFFS_ADJ_1_F - Device Offset Trim */
#define WD2_ADC_OFFS_ADJ_1_F_REG                            WD2_REG_ADC_1_CH_F_CFG
#define WD2_ADC_OFFS_ADJ_1_F_MASK                                       0x0000FF00
#define WD2_ADC_OFFS_ADJ_1_F_OFS                                                 8

/* ADC_OM_OUT_INVERT_1_F - Output Invert */
#define WD2_ADC_OM_OUT_INVERT_1_F_REG                       WD2_REG_ADC_1_CH_F_CFG
#define WD2_ADC_OM_OUT_INVERT_1_F_MASK                                  0x00000004
#define WD2_ADC_OM_OUT_INVERT_1_F_OFS                                            2



/* ****** Control Register 92 [0x1170]: ADC_1_CH_G_CFG - ADC 1 (B) Channel G Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000004) ****** */

/* ADC_TM_USR_IN_MODE_1_G - User Input Test Mode (see datasheet) */
#define WD2_ADC_TM_USR_IN_MODE_1_G_REG                      WD2_REG_ADC_1_CH_G_CFG
#define WD2_ADC_TM_USR_IN_MODE_1_G_MASK                                 0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_1_G_OFS                                          22

/* ADC_TM_OUT_1_G - Output Test Mode (see datasheet) */
#define WD2_ADC_TM_OUT_1_G_REG                              WD2_REG_ADC_1_CH_G_CFG
#define WD2_ADC_TM_OUT_1_G_MASK                                         0x000F0000
#define WD2_ADC_TM_OUT_1_G_OFS                                                  16

/* ADC_OFFS_ADJ_1_G - Device Offset Trim */
#define WD2_ADC_OFFS_ADJ_1_G_REG                            WD2_REG_ADC_1_CH_G_CFG
#define WD2_ADC_OFFS_ADJ_1_G_MASK                                       0x0000FF00
#define WD2_ADC_OFFS_ADJ_1_G_OFS                                                 8

/* ADC_OM_OUT_INVERT_1_G - Output Invert */
#define WD2_ADC_OM_OUT_INVERT_1_G_REG                       WD2_REG_ADC_1_CH_G_CFG
#define WD2_ADC_OM_OUT_INVERT_1_G_MASK                                  0x00000004
#define WD2_ADC_OM_OUT_INVERT_1_G_OFS                                            2



/* ****** Control Register 93 [0x1174]: ADC_1_CH_H_CFG - ADC 1 (B) Channel H Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000000) ****** */

/* ADC_TM_USR_IN_MODE_1_H - User Input Test Mode (see datasheet) */
#define WD2_ADC_TM_USR_IN_MODE_1_H_REG                      WD2_REG_ADC_1_CH_H_CFG
#define WD2_ADC_TM_USR_IN_MODE_1_H_MASK                                 0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_1_H_OFS                                          22

/* ADC_TM_OUT_1_H - Output Test Mode (see datasheet) */
#define WD2_ADC_TM_OUT_1_H_REG                              WD2_REG_ADC_1_CH_H_CFG
#define WD2_ADC_TM_OUT_1_H_MASK                                         0x000F0000
#define WD2_ADC_TM_OUT_1_H_OFS                                                  16

/* ADC_OFFS_ADJ_1_H - Device Offset Trim */
#define WD2_ADC_OFFS_ADJ_1_H_REG                            WD2_REG_ADC_1_CH_H_CFG
#define WD2_ADC_OFFS_ADJ_1_H_MASK                                       0x0000FF00
#define WD2_ADC_OFFS_ADJ_1_H_OFS                                                 8

/* ADC_OM_OUT_INVERT_1_H - Output Invert */
#define WD2_ADC_OM_OUT_INVERT_1_H_REG                       WD2_REG_ADC_1_CH_H_CFG
#define WD2_ADC_OM_OUT_INVERT_1_H_MASK                                  0x00000004
#define WD2_ADC_OM_OUT_INVERT_1_H_OFS                                            2



/* ****** Control Register 94 [0x1178]: ADC_1_CH_DCO_CFG - ADC 1 (B) Channel DCO Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000000) ****** */

/* ADC_TM_USR_IN_MODE_1_DCO - User Input Test Mode (see datasheet) */
#define WD2_ADC_TM_USR_IN_MODE_1_DCO_REG                  WD2_REG_ADC_1_CH_DCO_CFG
#define WD2_ADC_TM_USR_IN_MODE_1_DCO_MASK                               0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_1_DCO_OFS                                        22

/* ADC_TM_OUT_1_DCO - Output Test Mode (see datasheet) */
#define WD2_ADC_TM_OUT_1_DCO_REG                          WD2_REG_ADC_1_CH_DCO_CFG
#define WD2_ADC_TM_OUT_1_DCO_MASK                                       0x000F0000
#define WD2_ADC_TM_OUT_1_DCO_OFS                                                16

/* ADC_OFFS_ADJ_1_DCO - Device Offset Trim */
#define WD2_ADC_OFFS_ADJ_1_DCO_REG                        WD2_REG_ADC_1_CH_DCO_CFG
#define WD2_ADC_OFFS_ADJ_1_DCO_MASK                                     0x0000FF00
#define WD2_ADC_OFFS_ADJ_1_DCO_OFS                                               8

/* ADC_OM_OUT_INVERT_1_DCO - Output Invert */
#define WD2_ADC_OM_OUT_INVERT_1_DCO_REG                   WD2_REG_ADC_1_CH_DCO_CFG
#define WD2_ADC_OM_OUT_INVERT_1_DCO_MASK                                0x00000004
#define WD2_ADC_OM_OUT_INVERT_1_DCO_OFS                                          2



/* ****** Control Register 95 [0x117C]: ADC_1_CH_FCO_CFG - ADC 1 (B) Channel FCO Specific Configuration (ADC_CFG_IND_TX) (Default: 0x00000000) ****** */

/* ADC_TM_USR_IN_MODE_1_FCO - User Input Test Mode (see datasheet) */
#define WD2_ADC_TM_USR_IN_MODE_1_FCO_REG                  WD2_REG_ADC_1_CH_FCO_CFG
#define WD2_ADC_TM_USR_IN_MODE_1_FCO_MASK                               0x00C00000
#define WD2_ADC_TM_USR_IN_MODE_1_FCO_OFS                                        22

/* ADC_TM_OUT_1_FCO - Output Test Mode (see datasheet) */
#define WD2_ADC_TM_OUT_1_FCO_REG                          WD2_REG_ADC_1_CH_FCO_CFG
#define WD2_ADC_TM_OUT_1_FCO_MASK                                       0x000F0000
#define WD2_ADC_TM_OUT_1_FCO_OFS                                                16

/* ADC_OFFS_ADJ_1_FCO - Device Offset Trim */
#define WD2_ADC_OFFS_ADJ_1_FCO_REG                        WD2_REG_ADC_1_CH_FCO_CFG
#define WD2_ADC_OFFS_ADJ_1_FCO_MASK                                     0x0000FF00
#define WD2_ADC_OFFS_ADJ_1_FCO_OFS                                               8

/* ADC_OM_OUT_INVERT_1_FCO - Output Invert */
#define WD2_ADC_OM_OUT_INVERT_1_FCO_REG                   WD2_REG_ADC_1_CH_FCO_CFG
#define WD2_ADC_OM_OUT_INVERT_1_FCO_MASK                                0x00000004
#define WD2_ADC_OM_OUT_INVERT_1_FCO_OFS                                          2



/* ****** Control Register 96 [0x1180]: TRG_CFG - Trigger Configuration (Default: 0x00000000) ****** */

/* TRIGGER_OUT_PULSE_LENGTH - Length of the trigger output pulse in cycles */
#define WD2_TRIGGER_OUT_PULSE_LENGTH_REG                           WD2_REG_TRG_CFG
#define WD2_TRIGGER_OUT_PULSE_LENGTH_MASK                               0x1F000000
#define WD2_TRIGGER_OUT_PULSE_LENGTH_OFS                                        24

/* LEAD_TRAIL_EDGE_SEL - 0 = trigger on leading edge, 1 = trigger on trailing edge */
#define WD2_LEAD_TRAIL_EDGE_SEL_REG                                WD2_REG_TRG_CFG
#define WD2_LEAD_TRAIL_EDGE_SEL_MASK                                    0x00010000
#define WD2_LEAD_TRAIL_EDGE_SEL_OFS                                             16

/* EXT_TRIGGER_OUT_ENABLE - Enable output of trigger signal to MCX connector */
#define WD2_EXT_TRIGGER_OUT_ENABLE_REG                             WD2_REG_TRG_CFG
#define WD2_EXT_TRIGGER_OUT_ENABLE_MASK                                 0x00008000
#define WD2_EXT_TRIGGER_OUT_ENABLE_OFS                                          15

/* EXT_ASYNC_TRIGGER_EN - Enable asynchronous external trigger */
#define WD2_EXT_ASYNC_TRIGGER_EN_REG                               WD2_REG_TRG_CFG
#define WD2_EXT_ASYNC_TRIGGER_EN_MASK                                   0x00002000
#define WD2_EXT_ASYNC_TRIGGER_EN_OFS                                            13

/* PATTERN_TRIGGER_EN - Enable internal (synchronous) pattern trigger */
#define WD2_PATTERN_TRIGGER_EN_REG                                 WD2_REG_TRG_CFG
#define WD2_PATTERN_TRIGGER_EN_MASK                                     0x00001000
#define WD2_PATTERN_TRIGGER_EN_OFS                                              12

/* TRIGGER_DELAY - trigger delay in ticks of 6.25 ns */
#define WD2_TRIGGER_DELAY_REG                                      WD2_REG_TRG_CFG
#define WD2_TRIGGER_DELAY_MASK                                          0x000000FF
#define WD2_TRIGGER_DELAY_OFS                                                    0



/* ****** Control Register 97 [0x1184]: TRG_SRC_POL - Trigger Source Polarity (Default: 0x00000000) ****** */

/* TRG_SRC_POLARITY - Polarity of trigger source (0 = normal, 1 = inverted) (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch) */
#define WD2_TRG_SRC_POLARITY_REG                               WD2_REG_TRG_SRC_POL
#define WD2_TRG_SRC_POLARITY_MASK                                       0x0007FFFF
#define WD2_TRG_SRC_POLARITY_OFS                                                 0



/* ****** Control Register 98 [0x1188]: TRG_AUTO_PERIOD - Automatic Trigger Period (Default: 0x04C4B400) ****** */

/* AUTO_TRIGGER_PERIOD - Period of automatic trigger in ticks of the DAQ clock */
#define WD2_AUTO_TRIGGER_PERIOD_REG                        WD2_REG_TRG_AUTO_PERIOD
#define WD2_AUTO_TRIGGER_PERIOD_MASK                                    0xFFFFFFFF
#define WD2_AUTO_TRIGGER_PERIOD_OFS                                              0



/* ****** Control Register 99 [0x118C]: TRG_PTRN_EN - Enable for trigger patterns (Default: 0x00000000) ****** */

/* TRG_PTRN_EN - 1 enables the corresponding trigger patterns for the local trigger */
#define WD2_TRG_PTRN_EN_REG                                    WD2_REG_TRG_PTRN_EN
#define WD2_TRG_PTRN_EN_MASK                                            0x0007FFFF
#define WD2_TRG_PTRN_EN_OFS                                                      0



/* ****** Control Register 100 [0x1190]: TRG_SRC_EN_PTRN0 - Trigger Source Enable Pattern 0 (Default: 0x00000000) ****** */

/* TRG_SRC_EN_PTRN0 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch) */
#define WD2_TRG_SRC_EN_PTRN0_REG                          WD2_REG_TRG_SRC_EN_PTRN0
#define WD2_TRG_SRC_EN_PTRN0_MASK                                       0x0007FFFF
#define WD2_TRG_SRC_EN_PTRN0_OFS                                                 0



/* ****** Control Register 101 [0x1194]: TRG_STATE_PTRN0 - Trigger State Pattern 0 (Default: 0x00000000) ****** */

/* TRG_STATE_PTRN0 - trigger source state pattern (0 = Inhibit, 1 = Coincidence) */
#define WD2_TRG_STATE_PTRN0_REG                            WD2_REG_TRG_STATE_PTRN0
#define WD2_TRG_STATE_PTRN0_MASK                                        0x0007FFFF
#define WD2_TRG_STATE_PTRN0_OFS                                                  0



/* ****** Control Register 102 [0x1198]: TRG_SRC_EN_PTRN1 - Trigger Source Enable Pattern 1 (Default: 0x00000000) ****** */

/* TRG_SRC_EN_PTRN1 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch) */
#define WD2_TRG_SRC_EN_PTRN1_REG                          WD2_REG_TRG_SRC_EN_PTRN1
#define WD2_TRG_SRC_EN_PTRN1_MASK                                       0x0007FFFF
#define WD2_TRG_SRC_EN_PTRN1_OFS                                                 0



/* ****** Control Register 103 [0x119C]: TRG_STATE_PTRN1 - Trigger State Pattern 1 (Default: 0x00000000) ****** */

/* TRG_STATE_PTRN1 - trigger source state pattern (0 = Inhibit, 1 = Coincidence) */
#define WD2_TRG_STATE_PTRN1_REG                            WD2_REG_TRG_STATE_PTRN1
#define WD2_TRG_STATE_PTRN1_MASK                                        0x0007FFFF
#define WD2_TRG_STATE_PTRN1_OFS                                                  0



/* ****** Control Register 104 [0x11A0]: TRG_SRC_EN_PTRN2 - Trigger Source Enable Pattern 2 (Default: 0x00000000) ****** */

/* TRG_SRC_EN_PTRN2 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch) */
#define WD2_TRG_SRC_EN_PTRN2_REG                          WD2_REG_TRG_SRC_EN_PTRN2
#define WD2_TRG_SRC_EN_PTRN2_MASK                                       0x0007FFFF
#define WD2_TRG_SRC_EN_PTRN2_OFS                                                 0



/* ****** Control Register 105 [0x11A4]: TRG_STATE_PTRN2 - Trigger State Pattern 2 (Default: 0x00000000) ****** */

/* TRG_STATE_PTRN2 - trigger source state pattern (0 = Inhibit, 1 = Coincidence) */
#define WD2_TRG_STATE_PTRN2_REG                            WD2_REG_TRG_STATE_PTRN2
#define WD2_TRG_STATE_PTRN2_MASK                                        0x0007FFFF
#define WD2_TRG_STATE_PTRN2_OFS                                                  0



/* ****** Control Register 106 [0x11A8]: TRG_SRC_EN_PTRN3 - Trigger Source Enable Pattern 3 (Default: 0x00000000) ****** */

/* TRG_SRC_EN_PTRN3 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch) */
#define WD2_TRG_SRC_EN_PTRN3_REG                          WD2_REG_TRG_SRC_EN_PTRN3
#define WD2_TRG_SRC_EN_PTRN3_MASK                                       0x0007FFFF
#define WD2_TRG_SRC_EN_PTRN3_OFS                                                 0



/* ****** Control Register 107 [0x11AC]: TRG_STATE_PTRN3 - Trigger State Pattern 3 (Default: 0x00000000) ****** */

/* TRG_STATE_PTRN3 - trigger source state pattern (0 = Inhibit, 1 = Coincidence) */
#define WD2_TRG_STATE_PTRN3_REG                            WD2_REG_TRG_STATE_PTRN3
#define WD2_TRG_STATE_PTRN3_MASK                                        0x0007FFFF
#define WD2_TRG_STATE_PTRN3_OFS                                                  0



/* ****** Control Register 108 [0x11B0]: TRG_SRC_EN_PTRN4 - Trigger Source Enable Pattern 4 (Default: 0x00000000) ****** */

/* TRG_SRC_EN_PTRN4 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch) */
#define WD2_TRG_SRC_EN_PTRN4_REG                          WD2_REG_TRG_SRC_EN_PTRN4
#define WD2_TRG_SRC_EN_PTRN4_MASK                                       0x0007FFFF
#define WD2_TRG_SRC_EN_PTRN4_OFS                                                 0



/* ****** Control Register 109 [0x11B4]: TRG_STATE_PTRN4 - Trigger State Pattern 4 (Default: 0x00000000) ****** */

/* TRG_STATE_PTRN4 - trigger source state pattern (0 = Inhibit, 1 = Coincidence) */
#define WD2_TRG_STATE_PTRN4_REG                            WD2_REG_TRG_STATE_PTRN4
#define WD2_TRG_STATE_PTRN4_MASK                                        0x0007FFFF
#define WD2_TRG_STATE_PTRN4_OFS                                                  0



/* ****** Control Register 110 [0x11B8]: TRG_SRC_EN_PTRN5 - Trigger Source Enable Pattern 5 (Default: 0x00000000) ****** */

/* TRG_SRC_EN_PTRN5 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch) */
#define WD2_TRG_SRC_EN_PTRN5_REG                          WD2_REG_TRG_SRC_EN_PTRN5
#define WD2_TRG_SRC_EN_PTRN5_MASK                                       0x0007FFFF
#define WD2_TRG_SRC_EN_PTRN5_OFS                                                 0



/* ****** Control Register 111 [0x11BC]: TRG_STATE_PTRN5 - Trigger State Pattern 5 (Default: 0x00000000) ****** */

/* TRG_STATE_PTRN5 - trigger source state pattern (0 = Inhibit, 1 = Coincidence) */
#define WD2_TRG_STATE_PTRN5_REG                            WD2_REG_TRG_STATE_PTRN5
#define WD2_TRG_STATE_PTRN5_MASK                                        0x0007FFFF
#define WD2_TRG_STATE_PTRN5_OFS                                                  0



/* ****** Control Register 112 [0x11C0]: TRG_SRC_EN_PTRN6 - Trigger Source Enable Pattern 6 (Default: 0x00000000) ****** */

/* TRG_SRC_EN_PTRN6 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch) */
#define WD2_TRG_SRC_EN_PTRN6_REG                          WD2_REG_TRG_SRC_EN_PTRN6
#define WD2_TRG_SRC_EN_PTRN6_MASK                                       0x0007FFFF
#define WD2_TRG_SRC_EN_PTRN6_OFS                                                 0



/* ****** Control Register 113 [0x11C4]: TRG_STATE_PTRN6 - Trigger State Pattern 6 (Default: 0x00000000) ****** */

/* TRG_STATE_PTRN6 - trigger source state pattern (0 = Inhibit, 1 = Coincidence) */
#define WD2_TRG_STATE_PTRN6_REG                            WD2_REG_TRG_STATE_PTRN6
#define WD2_TRG_STATE_PTRN6_MASK                                        0x0007FFFF
#define WD2_TRG_STATE_PTRN6_OFS                                                  0



/* ****** Control Register 114 [0x11C8]: TRG_SRC_EN_PTRN7 - Trigger Source Enable Pattern 7 (Default: 0x00000000) ****** */

/* TRG_SRC_EN_PTRN7 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch) */
#define WD2_TRG_SRC_EN_PTRN7_REG                          WD2_REG_TRG_SRC_EN_PTRN7
#define WD2_TRG_SRC_EN_PTRN7_MASK                                       0x0007FFFF
#define WD2_TRG_SRC_EN_PTRN7_OFS                                                 0



/* ****** Control Register 115 [0x11CC]: TRG_STATE_PTRN7 - Trigger State Pattern 7 (Default: 0x00000000) ****** */

/* TRG_STATE_PTRN7 - trigger source state pattern (0 = Inhibit, 1 = Coincidence) */
#define WD2_TRG_STATE_PTRN7_REG                            WD2_REG_TRG_STATE_PTRN7
#define WD2_TRG_STATE_PTRN7_MASK                                        0x0007FFFF
#define WD2_TRG_STATE_PTRN7_OFS                                                  0



/* ****** Control Register 116 [0x11D0]: TRG_SRC_EN_PTRN8 - Trigger Source Enable Pattern 8 (Default: 0x00000000) ****** */

/* TRG_SRC_EN_PTRN8 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch) */
#define WD2_TRG_SRC_EN_PTRN8_REG                          WD2_REG_TRG_SRC_EN_PTRN8
#define WD2_TRG_SRC_EN_PTRN8_MASK                                       0x0007FFFF
#define WD2_TRG_SRC_EN_PTRN8_OFS                                                 0



/* ****** Control Register 117 [0x11D4]: TRG_STATE_PTRN8 - Trigger State Pattern 8 (Default: 0x00000000) ****** */

/* TRG_STATE_PTRN8 - trigger source state pattern (0 = Inhibit, 1 = Coincidence) */
#define WD2_TRG_STATE_PTRN8_REG                            WD2_REG_TRG_STATE_PTRN8
#define WD2_TRG_STATE_PTRN8_MASK                                        0x0007FFFF
#define WD2_TRG_STATE_PTRN8_OFS                                                  0



/* ****** Control Register 118 [0x11D8]: TRG_SRC_EN_PTRN9 - Trigger Source Enable Pattern 9 (Default: 0x00000000) ****** */

/* TRG_SRC_EN_PTRN9 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch) */
#define WD2_TRG_SRC_EN_PTRN9_REG                          WD2_REG_TRG_SRC_EN_PTRN9
#define WD2_TRG_SRC_EN_PTRN9_MASK                                       0x0007FFFF
#define WD2_TRG_SRC_EN_PTRN9_OFS                                                 0



/* ****** Control Register 119 [0x11DC]: TRG_STATE_PTRN9 - Trigger State Pattern 9 (Default: 0x00000000) ****** */

/* TRG_STATE_PTRN9 - trigger source state pattern (0 = Inhibit, 1 = Coincidence) */
#define WD2_TRG_STATE_PTRN9_REG                            WD2_REG_TRG_STATE_PTRN9
#define WD2_TRG_STATE_PTRN9_MASK                                        0x0007FFFF
#define WD2_TRG_STATE_PTRN9_OFS                                                  0



/* ****** Control Register 120 [0x11E0]: TRG_SRC_EN_PTRN10 - Trigger Source Enable Pattern 10 (Default: 0x00000000) ****** */

/* TRG_SRC_EN_PTRN10 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch) */
#define WD2_TRG_SRC_EN_PTRN10_REG                        WD2_REG_TRG_SRC_EN_PTRN10
#define WD2_TRG_SRC_EN_PTRN10_MASK                                      0x0007FFFF
#define WD2_TRG_SRC_EN_PTRN10_OFS                                                0



/* ****** Control Register 121 [0x11E4]: TRG_STATE_PTRN10 - Trigger State Pattern 10 (Default: 0x00000000) ****** */

/* TRG_STATE_PTRN10 - trigger source state pattern (0 = Inhibit, 1 = Coincidence) */
#define WD2_TRG_STATE_PTRN10_REG                          WD2_REG_TRG_STATE_PTRN10
#define WD2_TRG_STATE_PTRN10_MASK                                       0x0007FFFF
#define WD2_TRG_STATE_PTRN10_OFS                                                 0



/* ****** Control Register 122 [0x11E8]: TRG_SRC_EN_PTRN11 - Trigger Source Enable Pattern 11 (Default: 0x00000000) ****** */

/* TRG_SRC_EN_PTRN11 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch) */
#define WD2_TRG_SRC_EN_PTRN11_REG                        WD2_REG_TRG_SRC_EN_PTRN11
#define WD2_TRG_SRC_EN_PTRN11_MASK                                      0x0007FFFF
#define WD2_TRG_SRC_EN_PTRN11_OFS                                                0



/* ****** Control Register 123 [0x11EC]: TRG_STATE_PTRN11 - Trigger State Pattern 11 (Default: 0x00000000) ****** */

/* TRG_STATE_PTRN11 - trigger source state pattern (0 = Inhibit, 1 = Coincidence) */
#define WD2_TRG_STATE_PTRN11_REG                          WD2_REG_TRG_STATE_PTRN11
#define WD2_TRG_STATE_PTRN11_MASK                                       0x0007FFFF
#define WD2_TRG_STATE_PTRN11_OFS                                                 0



/* ****** Control Register 124 [0x11F0]: TRG_SRC_EN_PTRN12 - Trigger Source Enable Pattern 12 (Default: 0x00000000) ****** */

/* TRG_SRC_EN_PTRN12 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch) */
#define WD2_TRG_SRC_EN_PTRN12_REG                        WD2_REG_TRG_SRC_EN_PTRN12
#define WD2_TRG_SRC_EN_PTRN12_MASK                                      0x0007FFFF
#define WD2_TRG_SRC_EN_PTRN12_OFS                                                0



/* ****** Control Register 125 [0x11F4]: TRG_STATE_PTRN12 - Trigger State Pattern 12 (Default: 0x00000000) ****** */

/* TRG_STATE_PTRN12 - trigger source state pattern (0 = Inhibit, 1 = Coincidence) */
#define WD2_TRG_STATE_PTRN12_REG                          WD2_REG_TRG_STATE_PTRN12
#define WD2_TRG_STATE_PTRN12_MASK                                       0x0007FFFF
#define WD2_TRG_STATE_PTRN12_OFS                                                 0



/* ****** Control Register 126 [0x11F8]: TRG_SRC_EN_PTRN13 - Trigger Source Enable Pattern 13 (Default: 0x00000000) ****** */

/* TRG_SRC_EN_PTRN13 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch) */
#define WD2_TRG_SRC_EN_PTRN13_REG                        WD2_REG_TRG_SRC_EN_PTRN13
#define WD2_TRG_SRC_EN_PTRN13_MASK                                      0x0007FFFF
#define WD2_TRG_SRC_EN_PTRN13_OFS                                                0



/* ****** Control Register 127 [0x11FC]: TRG_STATE_PTRN13 - Trigger State Pattern 13 (Default: 0x00000000) ****** */

/* TRG_STATE_PTRN13 - trigger source state pattern (0 = Inhibit, 1 = Coincidence) */
#define WD2_TRG_STATE_PTRN13_REG                          WD2_REG_TRG_STATE_PTRN13
#define WD2_TRG_STATE_PTRN13_MASK                                       0x0007FFFF
#define WD2_TRG_STATE_PTRN13_OFS                                                 0



/* ****** Control Register 128 [0x1200]: TRG_SRC_EN_PTRN14 - Trigger Source Enable Pattern 14 (Default: 0x00000000) ****** */

/* TRG_SRC_EN_PTRN14 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch) */
#define WD2_TRG_SRC_EN_PTRN14_REG                        WD2_REG_TRG_SRC_EN_PTRN14
#define WD2_TRG_SRC_EN_PTRN14_MASK                                      0x0007FFFF
#define WD2_TRG_SRC_EN_PTRN14_OFS                                                0



/* ****** Control Register 129 [0x1204]: TRG_STATE_PTRN14 - Trigger State Pattern 14 (Default: 0x00000000) ****** */

/* TRG_STATE_PTRN14 - trigger source state pattern (0 = Inhibit, 1 = Coincidence) */
#define WD2_TRG_STATE_PTRN14_REG                          WD2_REG_TRG_STATE_PTRN14
#define WD2_TRG_STATE_PTRN14_MASK                                       0x0007FFFF
#define WD2_TRG_STATE_PTRN14_OFS                                                 0



/* ****** Control Register 130 [0x1208]: TRG_SRC_EN_PTRN15 - Trigger Source Enable Pattern 15 (Default: 0x00000000) ****** */

/* TRG_SRC_EN_PTRN15 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch) */
#define WD2_TRG_SRC_EN_PTRN15_REG                        WD2_REG_TRG_SRC_EN_PTRN15
#define WD2_TRG_SRC_EN_PTRN15_MASK                                      0x0007FFFF
#define WD2_TRG_SRC_EN_PTRN15_OFS                                                0



/* ****** Control Register 131 [0x120C]: TRG_STATE_PTRN15 - Trigger State Pattern 15 (Default: 0x00000000) ****** */

/* TRG_STATE_PTRN15 - trigger source state pattern (0 = Inhibit, 1 = Coincidence) */
#define WD2_TRG_STATE_PTRN15_REG                          WD2_REG_TRG_STATE_PTRN15
#define WD2_TRG_STATE_PTRN15_MASK                                       0x0007FFFF
#define WD2_TRG_STATE_PTRN15_OFS                                                 0



/* ****** Control Register 132 [0x1210]: TRG_SRC_EN_PTRN16 - Trigger Source Enable Pattern 16 (Default: 0x00000000) ****** */

/* TRG_SRC_EN_PTRN16 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch) */
#define WD2_TRG_SRC_EN_PTRN16_REG                        WD2_REG_TRG_SRC_EN_PTRN16
#define WD2_TRG_SRC_EN_PTRN16_MASK                                      0x0007FFFF
#define WD2_TRG_SRC_EN_PTRN16_OFS                                                0



/* ****** Control Register 133 [0x1214]: TRG_STATE_PTRN16 - Trigger State Pattern 16 (Default: 0x00000000) ****** */

/* TRG_STATE_PTRN16 - trigger source state pattern (0 = Inhibit, 1 = Coincidence) */
#define WD2_TRG_STATE_PTRN16_REG                          WD2_REG_TRG_STATE_PTRN16
#define WD2_TRG_STATE_PTRN16_MASK                                       0x0007FFFF
#define WD2_TRG_STATE_PTRN16_OFS                                                 0



/* ****** Control Register 134 [0x1218]: TRG_SRC_EN_PTRN17 - Trigger Source Enable Pattern 17 (Default: 0x00000000) ****** */

/* TRG_SRC_EN_PTRN17 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch) */
#define WD2_TRG_SRC_EN_PTRN17_REG                        WD2_REG_TRG_SRC_EN_PTRN17
#define WD2_TRG_SRC_EN_PTRN17_MASK                                      0x0007FFFF
#define WD2_TRG_SRC_EN_PTRN17_OFS                                                0



/* ****** Control Register 135 [0x121C]: TRG_STATE_PTRN17 - Trigger State Pattern 17 (Default: 0x00000000) ****** */

/* TRG_STATE_PTRN17 - trigger source state pattern (0 = Inhibit, 1 = Coincidence) */
#define WD2_TRG_STATE_PTRN17_REG                          WD2_REG_TRG_STATE_PTRN17
#define WD2_TRG_STATE_PTRN17_MASK                                       0x0007FFFF
#define WD2_TRG_STATE_PTRN17_OFS                                                 0



/* ****** Control Register 136 [0x1220]: TRG_SRC_EN_PTRN18 - Trigger Source Enable Pattern 18 (Default: 0x00000000) ****** */

/* TRG_SRC_EN_PTRN18 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch) */
#define WD2_TRG_SRC_EN_PTRN18_REG                        WD2_REG_TRG_SRC_EN_PTRN18
#define WD2_TRG_SRC_EN_PTRN18_MASK                                      0x0007FFFF
#define WD2_TRG_SRC_EN_PTRN18_OFS                                                0



/* ****** Control Register 137 [0x1224]: TRG_STATE_PTRN18 - Trigger State Pattern 18 (Default: 0x00000000) ****** */

/* TRG_STATE_PTRN18 - trigger source state pattern (0 = Inhibit, 1 = Coincidence) */
#define WD2_TRG_STATE_PTRN18_REG                          WD2_REG_TRG_STATE_PTRN18
#define WD2_TRG_STATE_PTRN18_MASK                                       0x0007FFFF
#define WD2_TRG_STATE_PTRN18_OFS                                                 0



/* ****** Control Register 138 [0x1228]: ADV_TRG_CTRL - Advanced Trigger Control Register (Default: 0x00000000) ****** */

/* ADV_TRG_CTRL - Advanced trigger control register */
#define WD2_ADV_TRG_CTRL_REG                                  WD2_REG_ADV_TRG_CTRL
#define WD2_ADV_TRG_CTRL_MASK                                           0xFFFFFFFF
#define WD2_ADV_TRG_CTRL_OFS                                                     0



/* ****** Control Register 139 [0x122C]: ADV_TRG_CH_CAL0 - Advanced Trigger Channel Calibration Register 0 (Default: 0x00000000) ****** */

/* ADV_TRG_CH_CAL0 - Advanced trigger channel calibration register 0 */
#define WD2_ADV_TRG_CH_CAL0_REG                            WD2_REG_ADV_TRG_CH_CAL0
#define WD2_ADV_TRG_CH_CAL0_MASK                                        0xFFFFFFFF
#define WD2_ADV_TRG_CH_CAL0_OFS                                                  0



/* ****** Control Register 140 [0x1230]: ADV_TRG_CH_CAL1 - Advanced Trigger Channel Calibration Register 1 (Default: 0x00000000) ****** */

/* ADV_TRG_CH_CAL1 - Advanced trigger channel calibration register 1 */
#define WD2_ADV_TRG_CH_CAL1_REG                            WD2_REG_ADV_TRG_CH_CAL1
#define WD2_ADV_TRG_CH_CAL1_MASK                                        0xFFFFFFFF
#define WD2_ADV_TRG_CH_CAL1_OFS                                                  0



/* ****** Control Register 141 [0x1234]: ADV_TRG_CH_CAL2 - Advanced Trigger Channel Calibration Register 2 (Default: 0x00000000) ****** */

/* ADV_TRG_CH_CAL2 - Advanced trigger channel calibration register 2 */
#define WD2_ADV_TRG_CH_CAL2_REG                            WD2_REG_ADV_TRG_CH_CAL2
#define WD2_ADV_TRG_CH_CAL2_MASK                                        0xFFFFFFFF
#define WD2_ADV_TRG_CH_CAL2_OFS                                                  0



/* ****** Control Register 142 [0x1238]: ADV_TRG_CH_CAL3 - Advanced Trigger Channel Calibration Register 3 (Default: 0x00000000) ****** */

/* ADV_TRG_CH_CAL3 - Advanced trigger channel calibration register 3 */
#define WD2_ADV_TRG_CH_CAL3_REG                            WD2_REG_ADV_TRG_CH_CAL3
#define WD2_ADV_TRG_CH_CAL3_MASK                                        0xFFFFFFFF
#define WD2_ADV_TRG_CH_CAL3_OFS                                                  0



/* ****** Control Register 143 [0x123C]: ADV_TRG_PED_CFG - Advanced Trigger Pedestal Configuration Register (Default: 0x00000000) ****** */

/* ADV_TRG_PED_CFG - Advanced trigger pedestal configuration register */
#define WD2_ADV_TRG_PED_CFG_REG                            WD2_REG_ADV_TRG_PED_CFG
#define WD2_ADV_TRG_PED_CFG_MASK                                        0xFFFFFFFF
#define WD2_ADV_TRG_PED_CFG_OFS                                                  0



/* ****** Control Register 144 [0x1240]: ADV_TRG_THR0 - Advanced Trigger Threshold 0 Register (Default: 0x00000000) ****** */

/* ADV_TRG_THR0 - Advanced trigger threshold 0 register */
#define WD2_ADV_TRG_THR0_REG                                  WD2_REG_ADV_TRG_THR0
#define WD2_ADV_TRG_THR0_MASK                                           0xFFFFFFFF
#define WD2_ADV_TRG_THR0_OFS                                                     0



/* ****** Control Register 145 [0x1244]: ADV_TRG_THR1 - Advanced Trigger Threshold 1 Register (Default: 0x00000000) ****** */

/* ADV_TRG_THR1 - Advanced trigger threshold 1 register */
#define WD2_ADV_TRG_THR1_REG                                  WD2_REG_ADV_TRG_THR1
#define WD2_ADV_TRG_THR1_MASK                                           0xFFFFFFFF
#define WD2_ADV_TRG_THR1_OFS                                                     0



/* ****** Control Register 146 [0x1248]: ADV_TRG_THR2 - Advanced Trigger Threshold 2 Register (Default: 0x00000000) ****** */

/* ADV_TRG_THR2 - Advanced trigger threshold 2 register */
#define WD2_ADV_TRG_THR2_REG                                  WD2_REG_ADV_TRG_THR2
#define WD2_ADV_TRG_THR2_MASK                                           0xFFFFFFFF
#define WD2_ADV_TRG_THR2_OFS                                                     0



/* ****** Control Register 147 [0x124C]: ADV_TRG_TX_CHK_WORD0 - Advanced Trigger Transmition Check Word 0 Register (Default: 0x00000000) ****** */

/* ADV_TRG_TX_CHK_WORD0 - Advanced trigger transmition check word 0 register */
#define WD2_ADV_TRG_TX_CHK_WORD0_REG                  WD2_REG_ADV_TRG_TX_CHK_WORD0
#define WD2_ADV_TRG_TX_CHK_WORD0_MASK                                   0xFFFFFFFF
#define WD2_ADV_TRG_TX_CHK_WORD0_OFS                                             0



/* ****** Control Register 148 [0x1250]: ADV_TRG_TX_CHK_WORD1 - Advanced Trigger Transmition Check Word 1 Register (Default: 0x00000000) ****** */

/* ADV_TRG_TX_CHK_WORD1 - Advanced trigger transmition check word 1 register */
#define WD2_ADV_TRG_TX_CHK_WORD1_REG                  WD2_REG_ADV_TRG_TX_CHK_WORD1
#define WD2_ADV_TRG_TX_CHK_WORD1_MASK                                   0xFFFFFFFF
#define WD2_ADV_TRG_TX_CHK_WORD1_OFS                                             0



/* ****** Control Register 149 [0x1254]: ADV_TRG_TDC_CH_MASK - Advanced Trigger TDC Channel Mask (Default: 0x00000000) ****** */

/* ADV_TRG_TDC_CH_MASK - Advanced trigger TDC channel mask */
#define WD2_ADV_TRG_TDC_CH_MASK_REG                    WD2_REG_ADV_TRG_TDC_CH_MASK
#define WD2_ADV_TRG_TDC_CH_MASK_MASK                                    0xFFFFFFFF
#define WD2_ADV_TRG_TDC_CH_MASK_OFS                                              0



/* ****** Control Register 150 [0x1258]: ADV_TRG_CFG12 - Advanced Trigger Configuration Register 12 (Default: 0x00000000) ****** */

/* ADV_TRG_CFG_12 - Advanced trigger configuration register 12 */
#define WD2_ADV_TRG_CFG_12_REG                               WD2_REG_ADV_TRG_CFG12
#define WD2_ADV_TRG_CFG_12_MASK                                         0xFFFFFFFF
#define WD2_ADV_TRG_CFG_12_OFS                                                   0



/* ****** Control Register 151 [0x125C]: ADV_TRG_CFG13 - Advanced Trigger Configuration Register 13 (Default: 0x00000000) ****** */

/* ADV_TRG_CFG_13 - Advanced trigger configuration register 13 */
#define WD2_ADV_TRG_CFG_13_REG                               WD2_REG_ADV_TRG_CFG13
#define WD2_ADV_TRG_CFG_13_MASK                                         0xFFFFFFFF
#define WD2_ADV_TRG_CFG_13_OFS                                                   0



/* ****** Control Register 152 [0x1260]: ADV_TRG_CFG14 - Advanced Trigger Configuration Register 14 (Default: 0x00000000) ****** */

/* ADV_TRG_CFG_14 - Advanced trigger configuration register 14 */
#define WD2_ADV_TRG_CFG_14_REG                               WD2_REG_ADV_TRG_CFG14
#define WD2_ADV_TRG_CFG_14_MASK                                         0xFFFFFFFF
#define WD2_ADV_TRG_CFG_14_OFS                                                   0



/* ****** Control Register 153 [0x1264]: ADV_TRG_CFG15 - Advanced Trigger Configuration Register 15 (Default: 0x00000000) ****** */

/* ADV_TRG_CFG_15 - Advanced trigger configuration register 15 */
#define WD2_ADV_TRG_CFG_15_REG                               WD2_REG_ADV_TRG_CFG15
#define WD2_ADV_TRG_CFG_15_MASK                                         0xFFFFFFFF
#define WD2_ADV_TRG_CFG_15_OFS                                                   0



/* ****** Control Register 154 [0x1268]: ADV_TRG_CFG16 - Advanced Trigger Configuration Register 16 (Default: 0x00000000) ****** */

/* ADV_TRG_CFG_16 - Advanced trigger configuration register 16 */
#define WD2_ADV_TRG_CFG_16_REG                               WD2_REG_ADV_TRG_CFG16
#define WD2_ADV_TRG_CFG_16_MASK                                         0xFFFFFFFF
#define WD2_ADV_TRG_CFG_16_OFS                                                   0



/* ****** Control Register 155 [0x126C]: ADV_TRG_CFG17 - Advanced Trigger Configuration Register 17 (Default: 0x00000000) ****** */

/* ADV_TRG_CFG_17 - Advanced trigger configuration register 17 */
#define WD2_ADV_TRG_CFG_17_REG                               WD2_REG_ADV_TRG_CFG17
#define WD2_ADV_TRG_CFG_17_MASK                                         0xFFFFFFFF
#define WD2_ADV_TRG_CFG_17_OFS                                                   0



/* ****** Control Register 156 [0x1270]: ADV_TRG_CFG18 - Advanced Trigger Configuration Register 18 (Default: 0x00000000) ****** */

/* ADV_TRG_CFG_18 - Advanced trigger configuration register 18 */
#define WD2_ADV_TRG_CFG_18_REG                               WD2_REG_ADV_TRG_CFG18
#define WD2_ADV_TRG_CFG_18_MASK                                         0xFFFFFFFF
#define WD2_ADV_TRG_CFG_18_OFS                                                   0



/* ****** Control Register 157 [0x1274]: ADV_TRG_CFG19 - Advanced Trigger Configuration Register 19 (Default: 0x00000000) ****** */

/* ADV_TRG_CFG_19 - Advanced trigger configuration register 19 */
#define WD2_ADV_TRG_CFG_19_REG                               WD2_REG_ADV_TRG_CFG19
#define WD2_ADV_TRG_CFG_19_MASK                                         0xFFFFFFFF
#define WD2_ADV_TRG_CFG_19_OFS                                                   0



/* ****** Control Register 158 [0x1278]: DBG_SIG_SEL - Debug Signal Select for MCX Connectors on HV Board (Default: 0x00000000) ****** */

/* MCX_TX_SIG_SEL - Select for TX connector (see RX connector for mapping) */
#define WD2_MCX_TX_SIG_SEL_REG                                 WD2_REG_DBG_SIG_SEL
#define WD2_MCX_TX_SIG_SEL_MASK                                         0x000F0000
#define WD2_MCX_TX_SIG_SEL_OFS                                                  16

/* MCX_RX_SIG_SEL - Select for RX connector:
0x0 = UART (communication to MicroBlaze)
0x1 = Trigger (internal hardware trigger signal to DRS control FSM)
0x2 = Soft Trigger (trigger signal from MicroBlaze)
0x3 = External Trigger (OR connection of external trigger from MCX and Backplane)
0x4 = Sync Signal from Backplane (direct, active high)
0x5 = Sync Signal from Backplane (sampled, output to LMK, active low)
0x6 = Sync Signal from Backplane (sampled, used for internal logic, active high)
0x7 = Busy Local (active high)
0x8 = Busy from Backplane (active high)
0x9 = LMK Reference Clock (LMK input clock) 
0xA = ADC Sampling Clock 
0xB = Divided Data Clock (phase shifted)
0xC = LMK5 clock (directly routed from corresponding input)
0xD = SPI CS of LMK (active low) */
#define WD2_MCX_RX_SIG_SEL_REG                                 WD2_REG_DBG_SIG_SEL
#define WD2_MCX_RX_SIG_SEL_MASK                                         0x0000000F
#define WD2_MCX_RX_SIG_SEL_OFS                                                   0



/* ****** Control Register 159 [0x127C]: DRS_TRG_RO_DLY - Trigger to DRS Readout Delay (Default: 0x00000008) ****** */

/* DRS_TRG_RO_DLY - Delay from trigger to DRS readout in number of 12.5ns clock cycles (default is 8) */
#define WD2_DRS_TRG_RO_DLY_REG                              WD2_REG_DRS_TRG_RO_DLY
#define WD2_DRS_TRG_RO_DLY_MASK                                         0xFFFFFFFF
#define WD2_DRS_TRG_RO_DLY_OFS                                                   0



/* ****** Control Register 160 [0x1280]: CRC32_REG_BANK - CRC32 Checksum of Register Bank Content (Default: None) ****** */

/* CRC32_REG_BANK - Keep at the end of the register bank */
#define WD2_CRC32_REG_BANK_REG                              WD2_REG_CRC32_REG_BANK
#define WD2_CRC32_REG_BANK_MASK                                         0xFFFFFFFF
#define WD2_CRC32_REG_BANK_OFS                                                   0



/* ****** Status Register 0 [0x0000]: HW_VER - Hardware version information of the PCB (Default: 0xAC010217) ****** */

/* BOARD_MAGIC - 0xAC, Magic number for DRS board identification */
#define WD2_BOARD_MAGIC_REG                                         WD2_REG_HW_VER
#define WD2_BOARD_MAGIC_MASK                                            0xFF000000
#define WD2_BOARD_MAGIC_OFS                                                     24
#define WD2_BOARD_MAGIC_CONST                                                 0xAC

/* VENDOR_ID - ID of the board vendor (0x01 for PSI) */
#define WD2_VENDOR_ID_REG                                           WD2_REG_HW_VER
#define WD2_VENDOR_ID_MASK                                              0x00FF0000
#define WD2_VENDOR_ID_OFS                                                       16
#define WD2_VENDOR_ID_CONST                                                   0x01

/* BOARD_TYPE - WaveDream Number (0x02 for WD2) */
#define WD2_BOARD_TYPE_REG                                          WD2_REG_HW_VER
#define WD2_BOARD_TYPE_MASK                                             0x0000FF00
#define WD2_BOARD_TYPE_OFS                                                       8
#define WD2_BOARD_TYPE_CONST                                                  0x02

/* BOARD_REVISION - Board revision (A=0x00, C=0x02, D=0x03, E=0x04, F=0x05, G=0x06) */
#define WD2_BOARD_REVISION_REG                                      WD2_REG_HW_VER
#define WD2_BOARD_REVISION_MASK                                         0x000000FC
#define WD2_BOARD_REVISION_OFS                                                   2
#define WD2_BOARD_REVISION_CONST                                              0x05

/* BOARD_VARIANT - Version indicator pins reflecting the variant of the board (Y15,Y10) */
#define WD2_BOARD_VARIANT_REG                                       WD2_REG_HW_VER
#define WD2_BOARD_VARIANT_MASK                                          0x00000003
#define WD2_BOARD_VARIANT_OFS                                                    0



/* ****** Status Register 1 [0x0004]: REG_LAYOUT_VER - Register map layout version information (Default: 0x00080008) ****** */

/* REG_LAYOUT_COMP_LEVEL - Register map layout compatibility level */
#define WD2_REG_LAYOUT_COMP_LEVEL_REG                       WD2_REG_REG_LAYOUT_VER
#define WD2_REG_LAYOUT_COMP_LEVEL_MASK                                  0xFFFF0000
#define WD2_REG_LAYOUT_COMP_LEVEL_OFS                                           16
#define WD2_REG_LAYOUT_COMP_LEVEL_CONST                                     0x0008

/* REG_LAYOUT_VERSION - Register map layout version */
#define WD2_REG_LAYOUT_VERSION_REG                          WD2_REG_REG_LAYOUT_VER
#define WD2_REG_LAYOUT_VERSION_MASK                                     0x0000FFFF
#define WD2_REG_LAYOUT_VERSION_OFS                                               0
#define WD2_REG_LAYOUT_VERSION_CONST                                        0x0008



/* ****** Status Register 2 [0x0008]: FW_BUILD_DATE - Date when the firmware was built (Default: 0x00000000) ****** */

/* FW_BUILD_YEAR - Year of the firmware build */
#define WD2_FW_BUILD_YEAR_REG                                WD2_REG_FW_BUILD_DATE
#define WD2_FW_BUILD_YEAR_MASK                                          0xFFFF0000
#define WD2_FW_BUILD_YEAR_OFS                                                   16

/* FW_BUILD_MONTH - Month of the firmware build */
#define WD2_FW_BUILD_MONTH_REG                               WD2_REG_FW_BUILD_DATE
#define WD2_FW_BUILD_MONTH_MASK                                         0x0000FF00
#define WD2_FW_BUILD_MONTH_OFS                                                   8

/* FW_BUILD_DAY - Day of the firmware build */
#define WD2_FW_BUILD_DAY_REG                                 WD2_REG_FW_BUILD_DATE
#define WD2_FW_BUILD_DAY_MASK                                           0x000000FF
#define WD2_FW_BUILD_DAY_OFS                                                     0



/* ****** Status Register 3 [0x000C]: FW_BUILD_TIME - Time when the firmware was built and compatibility level (Default: 0x04000000) ****** */

/* FW_COMPAT_LEVEL - Firmware compatibility level */
#define WD2_FW_COMPAT_LEVEL_REG                              WD2_REG_FW_BUILD_TIME
#define WD2_FW_COMPAT_LEVEL_MASK                                        0xFF000000
#define WD2_FW_COMPAT_LEVEL_OFS                                                 24
#define WD2_FW_COMPAT_LEVEL_CONST                                             0x04

/* FW_BUILD_HOUR - Hour of the firmware build */
#define WD2_FW_BUILD_HOUR_REG                                WD2_REG_FW_BUILD_TIME
#define WD2_FW_BUILD_HOUR_MASK                                          0x00FF0000
#define WD2_FW_BUILD_HOUR_OFS                                                   16

/* FW_BUILD_MINUTE - Minute of the firmware build */
#define WD2_FW_BUILD_MINUTE_REG                              WD2_REG_FW_BUILD_TIME
#define WD2_FW_BUILD_MINUTE_MASK                                        0x0000FF00
#define WD2_FW_BUILD_MINUTE_OFS                                                  8

/* FW_BUILD_SECOND - Second of the firmware build */
#define WD2_FW_BUILD_SECOND_REG                              WD2_REG_FW_BUILD_TIME
#define WD2_FW_BUILD_SECOND_MASK                                        0x000000FF
#define WD2_FW_BUILD_SECOND_OFS                                                  0



/* ****** Status Register 4 [0x0010]: SW_BUILD_DATE - Date when the software was built (Default: 0x00000000) ****** */

/* SW_BUILD_YEAR - Year of the software build */
#define WD2_SW_BUILD_YEAR_REG                                WD2_REG_SW_BUILD_DATE
#define WD2_SW_BUILD_YEAR_MASK                                          0xFFFF0000
#define WD2_SW_BUILD_YEAR_OFS                                                   16

/* SW_BUILD_MONTH - Month of the software build */
#define WD2_SW_BUILD_MONTH_REG                               WD2_REG_SW_BUILD_DATE
#define WD2_SW_BUILD_MONTH_MASK                                         0x0000FF00
#define WD2_SW_BUILD_MONTH_OFS                                                   8

/* SW_BUILD_DAY - Day of the software build */
#define WD2_SW_BUILD_DAY_REG                                 WD2_REG_SW_BUILD_DATE
#define WD2_SW_BUILD_DAY_MASK                                           0x000000FF
#define WD2_SW_BUILD_DAY_OFS                                                     0



/* ****** Status Register 5 [0x0014]: SW_BUILD_TIME - Time when the software was built and compatibility level (Default: 0x00000000) ****** */

/* SW_BUILD_HOUR - Hour of the software build */
#define WD2_SW_BUILD_HOUR_REG                                WD2_REG_SW_BUILD_TIME
#define WD2_SW_BUILD_HOUR_MASK                                          0x00FF0000
#define WD2_SW_BUILD_HOUR_OFS                                                   16

/* SW_BUILD_MINUTE - Minute of the software build */
#define WD2_SW_BUILD_MINUTE_REG                              WD2_REG_SW_BUILD_TIME
#define WD2_SW_BUILD_MINUTE_MASK                                        0x0000FF00
#define WD2_SW_BUILD_MINUTE_OFS                                                  8

/* SW_BUILD_SECOND - Second of the software build */
#define WD2_SW_BUILD_SECOND_REG                              WD2_REG_SW_BUILD_TIME
#define WD2_SW_BUILD_SECOND_MASK                                        0x000000FF
#define WD2_SW_BUILD_SECOND_OFS                                                  0



/* ****** Status Register 6 [0x0018]: FW_GIT_HASH_TAG - Hash tag of the firmware commit in the GIT repository (Default: 0x00000000) ****** */

/* FW_GIT_HASH_TAG - Hash tag of the firmware commit in the GIT repository */
#define WD2_FW_GIT_HASH_TAG_REG                            WD2_REG_FW_GIT_HASH_TAG
#define WD2_FW_GIT_HASH_TAG_MASK                                        0xFFFFFFFF
#define WD2_FW_GIT_HASH_TAG_OFS                                                  0



/* ****** Status Register 7 [0x001C]: SW_GIT_HASH_TAG - Hash tag of the software commit in the GIT repository (Default: 0x00000000) ****** */

/* SW_GIT_HASH_TAG - Hash tag of the software commit in the GIT repository */
#define WD2_SW_GIT_HASH_TAG_REG                            WD2_REG_SW_GIT_HASH_TAG
#define WD2_SW_GIT_HASH_TAG_MASK                                        0xFFFFFFFF
#define WD2_SW_GIT_HASH_TAG_OFS                                                  0



/* ****** Status Register 8 [0x0020]: PROT_VER - Vesion of the WaveDream2 protocol (Default: 0x00000006) ****** */

/* PROTOCOL_VERSION - Version of the WaveDream2 protocol */
#define WD2_PROTOCOL_VERSION_REG                                  WD2_REG_PROT_VER
#define WD2_PROTOCOL_VERSION_MASK                                       0x000000FF
#define WD2_PROTOCOL_VERSION_OFS                                                 0



/* ****** Status Register 9 [0x0024]: SN - Serial Number of the WD2 Board (Board ID) (Default: 0x00000000) ****** */

/* LED_STATE - State of the front panel LED (on-beat-color RGB, off-beat-color RGB) */
#define WD2_LED_STATE_REG                                               WD2_REG_SN
#define WD2_LED_STATE_MASK                                              0x3F000000
#define WD2_LED_STATE_OFS                                                       24

/* SERIAL_NUMBER - Serial Number of the WD2 Board (Board ID) */
#define WD2_SERIAL_NUMBER_REG                                           WD2_REG_SN
#define WD2_SERIAL_NUMBER_MASK                                          0x0000FFFF
#define WD2_SERIAL_NUMBER_OFS                                                    0



/* ****** Status Register 10 [0x0028]: STATUS - Status Register (Default: 0x00000000) ****** */

/* TEMPERATURE - temperature in 0.0625 deg. C units */
#define WD2_TEMPERATURE_REG                                         WD2_REG_STATUS
#define WD2_TEMPERATURE_MASK                                            0xFFFF0000
#define WD2_TEMPERATURE_OFS                                                     16

/* EXT_CLK_ACTIVE - Configuration for external clock for DAQ completed */
#define WD2_EXT_CLK_ACTIVE_REG                                      WD2_REG_STATUS
#define WD2_EXT_CLK_ACTIVE_MASK                                         0x00004000
#define WD2_EXT_CLK_ACTIVE_OFS                                                  14

/* DAQ_CLK_DEF_PHASE_OK - DAQ clock default phase setting is valid */
#define WD2_DAQ_CLK_DEF_PHASE_OK_REG                                WD2_REG_STATUS
#define WD2_DAQ_CLK_DEF_PHASE_OK_MASK                                   0x00002000
#define WD2_DAQ_CLK_DEF_PHASE_OK_OFS                                            13

/* DAQ_CLK_DEF_PHASE_CHKD - DAQ clock default phase setting is checked */
#define WD2_DAQ_CLK_DEF_PHASE_CHKD_REG                              WD2_REG_STATUS
#define WD2_DAQ_CLK_DEF_PHASE_CHKD_MASK                                 0x00001000
#define WD2_DAQ_CLK_DEF_PHASE_CHKD_OFS                                          12

/* DRS_CONFIG_DONE - DRS configuration done */
#define WD2_DRS_CONFIG_DONE_REG                                     WD2_REG_STATUS
#define WD2_DRS_CONFIG_DONE_MASK                                        0x00000400
#define WD2_DRS_CONFIG_DONE_OFS                                                 10

/* FLASH_SEL - SPI Flash select from backplane (inverted = high active) */
#define WD2_FLASH_SEL_REG                                           WD2_REG_STATUS
#define WD2_FLASH_SEL_MASK                                              0x00000200
#define WD2_FLASH_SEL_OFS                                                        9

/* BOARD_SEL - Board select from backplane (inverted = high active) */
#define WD2_BOARD_SEL_REG                                           WD2_REG_STATUS
#define WD2_BOARD_SEL_MASK                                              0x00000100
#define WD2_BOARD_SEL_OFS                                                        8

/* ADV_TRIG_BUSY - "1" while advanced trigger unit is busy */
#define WD2_ADV_TRIG_BUSY_REG                                       WD2_REG_STATUS
#define WD2_ADV_TRIG_BUSY_MASK                                          0x00000080
#define WD2_ADV_TRIG_BUSY_OFS                                                    7

/* PACKAGER_BUSY - "1" while packager is not ready to process data (buffers are full or ethernet destination not configured) */
#define WD2_PACKAGER_BUSY_REG                                       WD2_REG_STATUS
#define WD2_PACKAGER_BUSY_MASK                                          0x00000040
#define WD2_PACKAGER_BUSY_OFS                                                    6

/* DRS_CTRL_BUSY - "1" while domino wave running or readout in progress */
#define WD2_DRS_CTRL_BUSY_REG                                       WD2_REG_STATUS
#define WD2_DRS_CTRL_BUSY_MASK                                          0x00000020
#define WD2_DRS_CTRL_BUSY_OFS                                                    5

/* SYS_BUSY - Inverted busy signal from backplane (high active, not available until hardware revision G) */
#define WD2_SYS_BUSY_REG                                            WD2_REG_STATUS
#define WD2_SYS_BUSY_MASK                                               0x00000010
#define WD2_SYS_BUSY_OFS                                                         4

/* HV_BOARD_PLUGGED - HV board is currently plugged (1) or unplugged (0) */
#define WD2_HV_BOARD_PLUGGED_REG                                    WD2_REG_STATUS
#define WD2_HV_BOARD_PLUGGED_MASK                                       0x00000002
#define WD2_HV_BOARD_PLUGGED_OFS                                                 1

/* BACKPLANE_PLUGGED - Backplane is currently plugged (1) or unplugged (0) */
#define WD2_BACKPLANE_PLUGGED_REG                                   WD2_REG_STATUS
#define WD2_BACKPLANE_PLUGGED_MASK                                      0x00000001
#define WD2_BACKPLANE_PLUGGED_OFS                                                0



/* ****** Status Register 11 [0x002C]: PLL_LOCK - Lock Status of PLLs (Default: 0x00000000) ****** */

/* SYS_DCM_LOCK - Lock of system DCM (FPGA internal) */
#define WD2_SYS_DCM_LOCK_REG                                      WD2_REG_PLL_LOCK
#define WD2_SYS_DCM_LOCK_MASK                                           0x00000100
#define WD2_SYS_DCM_LOCK_OFS                                                     8

/* DAQ_PLL_LOCK - Lock of DAQ PLL (FPGA internal) */
#define WD2_DAQ_PLL_LOCK_REG                                      WD2_REG_PLL_LOCK
#define WD2_DAQ_PLL_LOCK_MASK                                           0x00000080
#define WD2_DAQ_PLL_LOCK_OFS                                                     7

/* OSERDES_PLL_LOCK_DCB - Lock of PLL for OSERDES to DCB (FPGA internal) */
#define WD2_OSERDES_PLL_LOCK_DCB_REG                              WD2_REG_PLL_LOCK
#define WD2_OSERDES_PLL_LOCK_DCB_MASK                                   0x00000040
#define WD2_OSERDES_PLL_LOCK_DCB_OFS                                             6

/* OSERDES_PLL_LOCK_TCB - Lock of PLL for OSERDES to TCB (FPGA internal) */
#define WD2_OSERDES_PLL_LOCK_TCB_REG                              WD2_REG_PLL_LOCK
#define WD2_OSERDES_PLL_LOCK_TCB_MASK                                   0x00000020
#define WD2_OSERDES_PLL_LOCK_TCB_OFS                                             5

/* ISERDES_PLL_LOCK_0 - Lock of PLL for ISERDES from ADC 0 (A) (FPGA internal) */
#define WD2_ISERDES_PLL_LOCK_0_REG                                WD2_REG_PLL_LOCK
#define WD2_ISERDES_PLL_LOCK_0_MASK                                     0x00000010
#define WD2_ISERDES_PLL_LOCK_0_OFS                                               4

/* ISERDES_PLL_LOCK_1 - Lock of PLL for ISERDES from ADC 1 (B) (FPGA internal) */
#define WD2_ISERDES_PLL_LOCK_1_REG                                WD2_REG_PLL_LOCK
#define WD2_ISERDES_PLL_LOCK_1_MASK                                     0x00000008
#define WD2_ISERDES_PLL_LOCK_1_OFS                                               3

/* DRS_PLL_LOCK_0 - PLL lock signal of DRS Channel 0 (A) (external) */
#define WD2_DRS_PLL_LOCK_0_REG                                    WD2_REG_PLL_LOCK
#define WD2_DRS_PLL_LOCK_0_MASK                                         0x00000004
#define WD2_DRS_PLL_LOCK_0_OFS                                                   2

/* DRS_PLL_LOCK_1 - PLL lock signal of DRS Channel 1 (B) (external) */
#define WD2_DRS_PLL_LOCK_1_REG                                    WD2_REG_PLL_LOCK
#define WD2_DRS_PLL_LOCK_1_MASK                                         0x00000002
#define WD2_DRS_PLL_LOCK_1_OFS                                                   1

/* LMK_PLL_LOCK - PLL lock signal of LMK (external) */
#define WD2_LMK_PLL_LOCK_REG                                      WD2_REG_PLL_LOCK
#define WD2_LMK_PLL_LOCK_MASK                                           0x00000001
#define WD2_LMK_PLL_LOCK_OFS                                                     0



/* ****** Status Register 12 [0x0030]: DRS_STOP_CELL - Position where sampling stopped at last trigger in DRS (Default: 0x00000000) ****** */

/* DRS_STOP_CELL_0 - Stop position of DRS Channel 0 (A) */
#define WD2_DRS_STOP_CELL_0_REG                              WD2_REG_DRS_STOP_CELL
#define WD2_DRS_STOP_CELL_0_MASK                                        0x03FF0000
#define WD2_DRS_STOP_CELL_0_OFS                                                 16

/* DRS_STOP_CELL_1 - Stop position of DRS Channel 1 (B) */
#define WD2_DRS_STOP_CELL_1_REG                              WD2_REG_DRS_STOP_CELL
#define WD2_DRS_STOP_CELL_1_MASK                                        0x000003FF
#define WD2_DRS_STOP_CELL_1_OFS                                                  0



/* ****** Status Register 13 [0x0034]: DRS_STOP_WSR - Write shift register contents when sampling stopped in DRS (Default: 0x00000000) ****** */

/* DRS_STOP_WSR_0 - WSR contents after stop of DRS Channel 0 (A) */
#define WD2_DRS_STOP_WSR_0_REG                                WD2_REG_DRS_STOP_WSR
#define WD2_DRS_STOP_WSR_0_MASK                                         0x0000FF00
#define WD2_DRS_STOP_WSR_0_OFS                                                   8

/* DRS_STOP_WSR_1 - WSR contents after stop of DRS Channel 1 (B) */
#define WD2_DRS_STOP_WSR_1_REG                                WD2_REG_DRS_STOP_WSR
#define WD2_DRS_STOP_WSR_1_MASK                                         0x000000FF
#define WD2_DRS_STOP_WSR_1_OFS                                                   0



/* ****** Status Register 14 [0x0038]: DRS_SAMPLE_FREQ - DRS Sampling frequency (Default: 0x00000000) ****** */

/* DRS_SAMPLE_FREQ - DRS Sampling frequency in kHz */
#define WD2_DRS_SAMPLE_FREQ_REG                            WD2_REG_DRS_SAMPLE_FREQ
#define WD2_DRS_SAMPLE_FREQ_MASK                                        0x00FFFFFF
#define WD2_DRS_SAMPLE_FREQ_OFS                                                  0



/* ****** Status Register 15 [0x003C]: ADC_SAMPLE_FREQ - ADC Sampling Frequency in MHz (Default: 0x00013880) ****** */

/* ADC_SAMPLE_FREQ - ADC Sampling Frequency in kHz */
#define WD2_ADC_SAMPLE_FREQ_REG                            WD2_REG_ADC_SAMPLE_FREQ
#define WD2_ADC_SAMPLE_FREQ_MASK                                        0x00FFFFFF
#define WD2_ADC_SAMPLE_FREQ_OFS                                                  0



/* ****** Status Register 16 [0x0040]: TDC_SAMPLE_FREQ - TDC Sampling Frequency in MHz (Default: 0x0009C400) ****** */

/* TDC_SAMPLE_FREQ - TDC Sampling Frequency in kHz */
#define WD2_TDC_SAMPLE_FREQ_REG                            WD2_REG_TDC_SAMPLE_FREQ
#define WD2_TDC_SAMPLE_FREQ_MASK                                        0x00FFFFFF
#define WD2_TDC_SAMPLE_FREQ_OFS                                                  0



/* ****** Status Register 17 [0x0044]: ADC_INFO - Chip ID and Grade of the ADCs (Default: 0x00000000) ****** */

/* ADC_0_CHIP_ID - Chip ID of ADC 0 (A) (0x93 for AD9637) */
#define WD2_ADC_0_CHIP_ID_REG                                     WD2_REG_ADC_INFO
#define WD2_ADC_0_CHIP_ID_MASK                                          0xFF000000
#define WD2_ADC_0_CHIP_ID_OFS                                                   24

/* ADC_0_SPEED - Speed Grade of ADC 0 (A) (0=40MS, 1=80MS) */
#define WD2_ADC_0_SPEED_REG                                       WD2_REG_ADC_INFO
#define WD2_ADC_0_SPEED_MASK                                            0x00700000
#define WD2_ADC_0_SPEED_OFS                                                     20

/* ADC_1_CHIP_ID - Chip ID of ADC 1 (B) (0x93 for AD9637) */
#define WD2_ADC_1_CHIP_ID_REG                                     WD2_REG_ADC_INFO
#define WD2_ADC_1_CHIP_ID_MASK                                          0x0000FF00
#define WD2_ADC_1_CHIP_ID_OFS                                                    8

/* ADC_1_SPEED - Speed Grade of ADC 1 (B) (0=40MS, 1=80MS) */
#define WD2_ADC_1_SPEED_REG                                       WD2_REG_ADC_INFO
#define WD2_ADC_1_SPEED_MASK                                            0x00000070
#define WD2_ADC_1_SPEED_OFS                                                      4



/* ****** Status Register 18 [0x0048]: HV_VER - HV Board Version (Default: 0x00000000) ****** */

/* HV_VER - HV board version (16bit Voltage in V, 16bit Current in mA) */
#define WD2_HV_VER_REG                                              WD2_REG_HV_VER
#define WD2_HV_VER_MASK                                                 0xFFFFFFFF
#define WD2_HV_VER_OFS                                                           0



/* ****** Status Register 19 [0x004C]: HV_I_MEAS_0 - Measured actual current of the HV supply on channel 0 (Default: 0x00000000) ****** */

/* HV_I_MEAS_0 - Float value (i_meas) */
#define WD2_HV_I_MEAS_0_REG                                    WD2_REG_HV_I_MEAS_0
#define WD2_HV_I_MEAS_0_MASK                                            0xFFFFFFFF
#define WD2_HV_I_MEAS_0_OFS                                                      0



/* ****** Status Register 20 [0x0050]: HV_I_MEAS_1 - Measured actual current of the HV supply on channel 1 (Default: 0x00000000) ****** */

/* HV_I_MEAS_1 - Float value (i_meas) */
#define WD2_HV_I_MEAS_1_REG                                    WD2_REG_HV_I_MEAS_1
#define WD2_HV_I_MEAS_1_MASK                                            0xFFFFFFFF
#define WD2_HV_I_MEAS_1_OFS                                                      0



/* ****** Status Register 21 [0x0054]: HV_I_MEAS_2 - Measured actual current of the HV supply on channel 2 (Default: 0x00000000) ****** */

/* HV_I_MEAS_2 - Float value (i_meas) */
#define WD2_HV_I_MEAS_2_REG                                    WD2_REG_HV_I_MEAS_2
#define WD2_HV_I_MEAS_2_MASK                                            0xFFFFFFFF
#define WD2_HV_I_MEAS_2_OFS                                                      0



/* ****** Status Register 22 [0x0058]: HV_I_MEAS_3 - Measured actual current of the HV supply on channel 3 (Default: 0x00000000) ****** */

/* HV_I_MEAS_3 - Float value (i_meas) */
#define WD2_HV_I_MEAS_3_REG                                    WD2_REG_HV_I_MEAS_3
#define WD2_HV_I_MEAS_3_MASK                                            0xFFFFFFFF
#define WD2_HV_I_MEAS_3_OFS                                                      0



/* ****** Status Register 23 [0x005C]: HV_I_MEAS_4 - Measured actual current of the HV supply on channel 4 (Default: 0x00000000) ****** */

/* HV_I_MEAS_4 - Float value (i_meas) */
#define WD2_HV_I_MEAS_4_REG                                    WD2_REG_HV_I_MEAS_4
#define WD2_HV_I_MEAS_4_MASK                                            0xFFFFFFFF
#define WD2_HV_I_MEAS_4_OFS                                                      0



/* ****** Status Register 24 [0x0060]: HV_I_MEAS_5 - Measured actual current of the HV supply on channel 5 (Default: 0x00000000) ****** */

/* HV_I_MEAS_5 - Float value (i_meas) */
#define WD2_HV_I_MEAS_5_REG                                    WD2_REG_HV_I_MEAS_5
#define WD2_HV_I_MEAS_5_MASK                                            0xFFFFFFFF
#define WD2_HV_I_MEAS_5_OFS                                                      0



/* ****** Status Register 25 [0x0064]: HV_I_MEAS_6 - Measured actual current of the HV supply on channel 6 (Default: 0x00000000) ****** */

/* HV_I_MEAS_6 - Float value (i_meas) */
#define WD2_HV_I_MEAS_6_REG                                    WD2_REG_HV_I_MEAS_6
#define WD2_HV_I_MEAS_6_MASK                                            0xFFFFFFFF
#define WD2_HV_I_MEAS_6_OFS                                                      0



/* ****** Status Register 26 [0x0068]: HV_I_MEAS_7 - Measured actual current of the HV supply on channel 7 (Default: 0x00000000) ****** */

/* HV_I_MEAS_7 - Float value (i_meas) */
#define WD2_HV_I_MEAS_7_REG                                    WD2_REG_HV_I_MEAS_7
#define WD2_HV_I_MEAS_7_MASK                                            0xFFFFFFFF
#define WD2_HV_I_MEAS_7_OFS                                                      0



/* ****** Status Register 27 [0x006C]: HV_I_MEAS_8 - Measured actual current of the HV supply on channel 8 (Default: 0x00000000) ****** */

/* HV_I_MEAS_8 - Float value (i_meas) */
#define WD2_HV_I_MEAS_8_REG                                    WD2_REG_HV_I_MEAS_8
#define WD2_HV_I_MEAS_8_MASK                                            0xFFFFFFFF
#define WD2_HV_I_MEAS_8_OFS                                                      0



/* ****** Status Register 28 [0x0070]: HV_I_MEAS_9 - Measured actual current of the HV supply on channel 9 (Default: 0x00000000) ****** */

/* HV_I_MEAS_9 - Float value (i_meas) */
#define WD2_HV_I_MEAS_9_REG                                    WD2_REG_HV_I_MEAS_9
#define WD2_HV_I_MEAS_9_MASK                                            0xFFFFFFFF
#define WD2_HV_I_MEAS_9_OFS                                                      0



/* ****** Status Register 29 [0x0074]: HV_I_MEAS_10 - Measured actual current of the HV supply on channel 10 (Default: 0x00000000) ****** */

/* HV_I_MEAS_10 - Float value (i_meas) */
#define WD2_HV_I_MEAS_10_REG                                  WD2_REG_HV_I_MEAS_10
#define WD2_HV_I_MEAS_10_MASK                                           0xFFFFFFFF
#define WD2_HV_I_MEAS_10_OFS                                                     0



/* ****** Status Register 30 [0x0078]: HV_I_MEAS_11 - Measured actual current of the HV supply on channel 11 (Default: 0x00000000) ****** */

/* HV_I_MEAS_11 - Float value (i_meas) */
#define WD2_HV_I_MEAS_11_REG                                  WD2_REG_HV_I_MEAS_11
#define WD2_HV_I_MEAS_11_MASK                                           0xFFFFFFFF
#define WD2_HV_I_MEAS_11_OFS                                                     0



/* ****** Status Register 31 [0x007C]: HV_I_MEAS_12 - Measured actual current of the HV supply on channel 12 (Default: 0x00000000) ****** */

/* HV_I_MEAS_12 - Float value (i_meas) */
#define WD2_HV_I_MEAS_12_REG                                  WD2_REG_HV_I_MEAS_12
#define WD2_HV_I_MEAS_12_MASK                                           0xFFFFFFFF
#define WD2_HV_I_MEAS_12_OFS                                                     0



/* ****** Status Register 32 [0x0080]: HV_I_MEAS_13 - Measured actual current of the HV supply on channel 13 (Default: 0x00000000) ****** */

/* HV_I_MEAS_13 - Float value (i_meas) */
#define WD2_HV_I_MEAS_13_REG                                  WD2_REG_HV_I_MEAS_13
#define WD2_HV_I_MEAS_13_MASK                                           0xFFFFFFFF
#define WD2_HV_I_MEAS_13_OFS                                                     0



/* ****** Status Register 33 [0x0084]: HV_I_MEAS_14 - Measured actual current of the HV supply on channel 14 (Default: 0x00000000) ****** */

/* HV_I_MEAS_14 - Float value (i_meas) */
#define WD2_HV_I_MEAS_14_REG                                  WD2_REG_HV_I_MEAS_14
#define WD2_HV_I_MEAS_14_MASK                                           0xFFFFFFFF
#define WD2_HV_I_MEAS_14_OFS                                                     0



/* ****** Status Register 34 [0x0088]: HV_I_MEAS_15 - Measured actual current of the HV supply on channel 15 (Default: 0x00000000) ****** */

/* HV_I_MEAS_15 - Float value (i_meas) */
#define WD2_HV_I_MEAS_15_REG                                  WD2_REG_HV_I_MEAS_15
#define WD2_HV_I_MEAS_15_MASK                                           0xFFFFFFFF
#define WD2_HV_I_MEAS_15_OFS                                                     0



/* ****** Status Register 35 [0x008C]: HV_U_BASE_MEAS - Measured actual HV base voltage (Default: 0x00000000) ****** */

/* HV_U_BASE_MEAS - Float value (ub_meas) */
#define WD2_HV_U_BASE_MEAS_REG                              WD2_REG_HV_U_BASE_MEAS
#define WD2_HV_U_BASE_MEAS_MASK                                         0xFFFFFFFF
#define WD2_HV_U_BASE_MEAS_OFS                                                   0



/* ****** Status Register 36 [0x0090]: HV_TEMP_0 - Measured actual temperature of sensor 0 connected to the HV board (Default: 0x00000000) ****** */

/* HV_TEMP_0 - Float value (temp) */
#define WD2_HV_TEMP_0_REG                                        WD2_REG_HV_TEMP_0
#define WD2_HV_TEMP_0_MASK                                              0xFFFFFFFF
#define WD2_HV_TEMP_0_OFS                                                        0



/* ****** Status Register 37 [0x0094]: HV_TEMP_1 - Measured actual temperature of sensor 1 connected to the HV board (Default: 0x00000000) ****** */

/* HV_TEMP_1 - Float value (temp) */
#define WD2_HV_TEMP_1_REG                                        WD2_REG_HV_TEMP_1
#define WD2_HV_TEMP_1_MASK                                              0xFFFFFFFF
#define WD2_HV_TEMP_1_OFS                                                        0



/* ****** Status Register 38 [0x0098]: HV_TEMP_2 - Measured actual temperature of sensor 2 connected to the HV board (Default: 0x00000000) ****** */

/* HV_TEMP_2 - Float value (temp) */
#define WD2_HV_TEMP_2_REG                                        WD2_REG_HV_TEMP_2
#define WD2_HV_TEMP_2_MASK                                              0xFFFFFFFF
#define WD2_HV_TEMP_2_OFS                                                        0



/* ****** Status Register 39 [0x009C]: HV_TEMP_3 - Measured actual temperature of sensor 3 connected to the HV board (Default: 0x00000000) ****** */

/* HV_TEMP_3 - Float value (temp) */
#define WD2_HV_TEMP_3_REG                                        WD2_REG_HV_TEMP_3
#define WD2_HV_TEMP_3_MASK                                              0xFFFFFFFF
#define WD2_HV_TEMP_3_OFS                                                        0



/* ****** Status Register 40 [0x00A0]: SCALER_0 - Scaler for input #0 (Default: 0x00000000) ****** */

/* SCALER_0 - Count rate value of channel 0 (MSBs are latched upon read of LSB register) */
#define WD2_SCALER_0_REG                                          WD2_REG_SCALER_0
#define WD2_SCALER_0_MASK                                               0xFFFFFFFF
#define WD2_SCALER_0_OFS                                                         0



/* ****** Status Register 41 [0x00A4]: SCALER_1 - Scaler for input #1 (Default: 0x00000000) ****** */

/* SCALER_1 - Count rate value of channel 1 (MSBs are latched upon read of LSB register) */
#define WD2_SCALER_1_REG                                          WD2_REG_SCALER_1
#define WD2_SCALER_1_MASK                                               0xFFFFFFFF
#define WD2_SCALER_1_OFS                                                         0



/* ****** Status Register 42 [0x00A8]: SCALER_2 - Scaler for input #2 (Default: 0x00000000) ****** */

/* SCALER_2 - Count rate value of channel 2 (MSBs are latched upon read of LSB register) */
#define WD2_SCALER_2_REG                                          WD2_REG_SCALER_2
#define WD2_SCALER_2_MASK                                               0xFFFFFFFF
#define WD2_SCALER_2_OFS                                                         0



/* ****** Status Register 43 [0x00AC]: SCALER_3 - Scaler for input #3 (Default: 0x00000000) ****** */

/* SCALER_3 - Count rate value of channel 3 (MSBs are latched upon read of LSB register) */
#define WD2_SCALER_3_REG                                          WD2_REG_SCALER_3
#define WD2_SCALER_3_MASK                                               0xFFFFFFFF
#define WD2_SCALER_3_OFS                                                         0



/* ****** Status Register 44 [0x00B0]: SCALER_4 - Scaler for input #4 (Default: 0x00000000) ****** */

/* SCALER_4 - Count rate value of channel 4 (MSBs are latched upon read of LSB register) */
#define WD2_SCALER_4_REG                                          WD2_REG_SCALER_4
#define WD2_SCALER_4_MASK                                               0xFFFFFFFF
#define WD2_SCALER_4_OFS                                                         0



/* ****** Status Register 45 [0x00B4]: SCALER_5 - Scaler for input #5 (Default: 0x00000000) ****** */

/* SCALER_5 - Count rate value of channel 5 (MSBs are latched upon read of LSB register) */
#define WD2_SCALER_5_REG                                          WD2_REG_SCALER_5
#define WD2_SCALER_5_MASK                                               0xFFFFFFFF
#define WD2_SCALER_5_OFS                                                         0



/* ****** Status Register 46 [0x00B8]: SCALER_6 - Scaler for input #6 (Default: 0x00000000) ****** */

/* SCALER_6 - Count rate value of channel 6 (MSBs are latched upon read of LSB register) */
#define WD2_SCALER_6_REG                                          WD2_REG_SCALER_6
#define WD2_SCALER_6_MASK                                               0xFFFFFFFF
#define WD2_SCALER_6_OFS                                                         0



/* ****** Status Register 47 [0x00BC]: SCALER_7 - Scaler for input #7 (Default: 0x00000000) ****** */

/* SCALER_7 - Count rate value of channel 7 (MSBs are latched upon read of LSB register) */
#define WD2_SCALER_7_REG                                          WD2_REG_SCALER_7
#define WD2_SCALER_7_MASK                                               0xFFFFFFFF
#define WD2_SCALER_7_OFS                                                         0



/* ****** Status Register 48 [0x00C0]: SCALER_8 - Scaler for input #8 (Default: 0x00000000) ****** */

/* SCALER_8 - Count rate value of channel 8 (MSBs are latched upon read of LSB register) */
#define WD2_SCALER_8_REG                                          WD2_REG_SCALER_8
#define WD2_SCALER_8_MASK                                               0xFFFFFFFF
#define WD2_SCALER_8_OFS                                                         0



/* ****** Status Register 49 [0x00C4]: SCALER_9 - Scaler for input #9 (Default: 0x00000000) ****** */

/* SCALER_9 - Count rate value of channel 9 (MSBs are latched upon read of LSB register) */
#define WD2_SCALER_9_REG                                          WD2_REG_SCALER_9
#define WD2_SCALER_9_MASK                                               0xFFFFFFFF
#define WD2_SCALER_9_OFS                                                         0



/* ****** Status Register 50 [0x00C8]: SCALER_10 - Scaler for input #10 (Default: 0x00000000) ****** */

/* SCALER_10 - Count rate value of channel 10 (MSBs are latched upon read of LSB register) */
#define WD2_SCALER_10_REG                                        WD2_REG_SCALER_10
#define WD2_SCALER_10_MASK                                              0xFFFFFFFF
#define WD2_SCALER_10_OFS                                                        0



/* ****** Status Register 51 [0x00CC]: SCALER_11 - Scaler for input #11 (Default: 0x00000000) ****** */

/* SCALER_11 - Count rate value of channel 11 (MSBs are latched upon read of LSB register) */
#define WD2_SCALER_11_REG                                        WD2_REG_SCALER_11
#define WD2_SCALER_11_MASK                                              0xFFFFFFFF
#define WD2_SCALER_11_OFS                                                        0



/* ****** Status Register 52 [0x00D0]: SCALER_12 - Scaler for input #12 (Default: 0x00000000) ****** */

/* SCALER_12 - Count rate value of channel 12 (MSBs are latched upon read of LSB register) */
#define WD2_SCALER_12_REG                                        WD2_REG_SCALER_12
#define WD2_SCALER_12_MASK                                              0xFFFFFFFF
#define WD2_SCALER_12_OFS                                                        0



/* ****** Status Register 53 [0x00D4]: SCALER_13 - Scaler for input #13 (Default: 0x00000000) ****** */

/* SCALER_13 - Count rate value of channel 13 (MSBs are latched upon read of LSB register) */
#define WD2_SCALER_13_REG                                        WD2_REG_SCALER_13
#define WD2_SCALER_13_MASK                                              0xFFFFFFFF
#define WD2_SCALER_13_OFS                                                        0



/* ****** Status Register 54 [0x00D8]: SCALER_14 - Scaler for input #14 (Default: 0x00000000) ****** */

/* SCALER_14 - Count rate value of channel 14 (MSBs are latched upon read of LSB register) */
#define WD2_SCALER_14_REG                                        WD2_REG_SCALER_14
#define WD2_SCALER_14_MASK                                              0xFFFFFFFF
#define WD2_SCALER_14_OFS                                                        0



/* ****** Status Register 55 [0x00DC]: SCALER_15 - Scaler for input #15 (Default: 0x00000000) ****** */

/* SCALER_15 - Count rate value of channel 15 (MSBs are latched upon read of LSB register) */
#define WD2_SCALER_15_REG                                        WD2_REG_SCALER_15
#define WD2_SCALER_15_MASK                                              0xFFFFFFFF
#define WD2_SCALER_15_OFS                                                        0



/* ****** Status Register 56 [0x00E0]: SCALER_PTRN_TRG - Scaler for pattern trigger (Default: 0x00000000) ****** */

/* SCALER_PTRN_TRG - Count rate for pattern trigger signal */
#define WD2_SCALER_PTRN_TRG_REG                            WD2_REG_SCALER_PTRN_TRG
#define WD2_SCALER_PTRN_TRG_MASK                                        0xFFFFFFFF
#define WD2_SCALER_PTRN_TRG_OFS                                                  0



/* ****** Status Register 57 [0x00E4]: SCALER_EXT_TRG - Scaler for external trigger (Default: 0x00000000) ****** */

/* SCALER_EXT_TRG - Count rate for trigger signal */
#define WD2_SCALER_EXT_TRG_REG                              WD2_REG_SCALER_EXT_TRG
#define WD2_SCALER_EXT_TRG_MASK                                         0xFFFFFFFF
#define WD2_SCALER_EXT_TRG_OFS                                                   0



/* ****** Status Register 58 [0x00E8]: SCALER_EXT_CLK - Scaler for ext. clock input (Default: 0x00000000) ****** */

/* SCALER_EXT_CLK - Count rate for external clock input (GLOB_CLK) */
#define WD2_SCALER_EXT_CLK_REG                              WD2_REG_SCALER_EXT_CLK
#define WD2_SCALER_EXT_CLK_MASK                                         0xFFFFFFFF
#define WD2_SCALER_EXT_CLK_OFS                                                   0



/* ****** Status Register 59 [0x00EC]: SCALER_TIME_STAMP_LSB - Time Stamp for Scaler Values (Default: 0x00000000) ****** */

/* SCALER_TIME_STAMP_LSB - LSBs of 64bit scaler time stamp (MSBs are latched upon read of LSB register) */
#define WD2_SCALER_TIME_STAMP_LSB_REG                WD2_REG_SCALER_TIME_STAMP_LSB
#define WD2_SCALER_TIME_STAMP_LSB_MASK                                  0xFFFFFFFF
#define WD2_SCALER_TIME_STAMP_LSB_OFS                                            0



/* ****** Status Register 60 [0x00F0]: SCALER_TIME_STAMP_MSB - Time Stamp for Scaler Values (Default: 0x00000000) ****** */

/* SCALER_TIME_STAMP_MSB - MSBs of 64bit scaler time stamp (latched upon read of LSB register) */
#define WD2_SCALER_TIME_STAMP_MSB_REG                WD2_REG_SCALER_TIME_STAMP_MSB
#define WD2_SCALER_TIME_STAMP_MSB_MASK                                  0xFFFFFFFF
#define WD2_SCALER_TIME_STAMP_MSB_OFS                                            0



/* ****** Status Register 61 [0x00F4]: SYS_TIME - Current System Time (Default: 0x00000000) ****** */

/* SYS_TIME - System uptime in 10ms steps (no overflow protection) */
#define WD2_SYS_TIME_REG                                          WD2_REG_SYS_TIME
#define WD2_SYS_TIME_MASK                                               0xFFFFFFFF
#define WD2_SYS_TIME_OFS                                                         0



/* ****** Status Register 62 [0x00F8]: COMP_CH_STAT - Comparator channel status (Default: 0x00000000) ****** */

/* COMP_CH_STAT - Status of the comparator inputs */
#define WD2_COMP_CH_STAT_REG                                  WD2_REG_COMP_CH_STAT
#define WD2_COMP_CH_STAT_MASK                                           0x0000FFFF
#define WD2_COMP_CH_STAT_OFS                                                     0



/* ****** Status Register 63 [0x00FC]: EVENT_TX_RATE - Event Transmission Rate (Default: 0x00000000) ****** */

/* EVENT_TX_RATE - Number of events transmitted per second */
#define WD2_EVENT_TX_RATE_REG                                WD2_REG_EVENT_TX_RATE
#define WD2_EVENT_TX_RATE_MASK                                          0xFFFFFFFF
#define WD2_EVENT_TX_RATE_OFS                                                    0



/* ****** Status Register 64 [0x0100]: EVENT_NR - Number of latest event (Default: 0x00000000) ****** */

/* EVENT_NUMBER - Number of latest event */
#define WD2_EVENT_NUMBER_REG                                      WD2_REG_EVENT_NR
#define WD2_EVENT_NUMBER_MASK                                           0xFFFFFFFF
#define WD2_EVENT_NUMBER_OFS                                                     0



/* ****** Status Register 65 [0x0104]: TRB_INFO_STAT - Trigger Information via Serial Trigger Bus Status (Default: 0x00000000) ****** */

/* TRB_FLAG_NEW - Flag signalling that the current trigger information belongs to the latest trigger received */
#define WD2_TRB_FLAG_NEW_REG                                 WD2_REG_TRB_INFO_STAT
#define WD2_TRB_FLAG_NEW_MASK                                           0x80000000
#define WD2_TRB_FLAG_NEW_OFS                                                    31

/* TRB_FLAG_PARITY_ERROR - Parity error flag of the current trigger information */
#define WD2_TRB_FLAG_PARITY_ERROR_REG                        WD2_REG_TRB_INFO_STAT
#define WD2_TRB_FLAG_PARITY_ERROR_MASK                                  0x40000000
#define WD2_TRB_FLAG_PARITY_ERROR_OFS                                           30

/* TRB_PARITY_ERROR_COUNT - Parity error count of the serial transmission */
#define WD2_TRB_PARITY_ERROR_COUNT_REG                       WD2_REG_TRB_INFO_STAT
#define WD2_TRB_PARITY_ERROR_COUNT_MASK                                 0x0000FFFF
#define WD2_TRB_PARITY_ERROR_COUNT_OFS                                           0



/* ****** Status Register 66 [0x0108]: TRB_INFO_LSB - Trigger Information via Serial Trigger Bus LSBs (Default: 0x00000000) ****** */

/* TRB_INFO_LSB - Trigger information LSBs */
#define WD2_TRB_INFO_LSB_REG                                  WD2_REG_TRB_INFO_LSB
#define WD2_TRB_INFO_LSB_MASK                                           0xFFFFFFFF
#define WD2_TRB_INFO_LSB_OFS                                                     0



/* ****** Status Register 67 [0x010C]: TRB_INFO_MSB - Trigger Information via Serial Trigger Bus MSBs (Default: 0x00000000) ****** */

/* TRB_INFO_MSB - Trigger information MSBs */
#define WD2_TRB_INFO_MSB_REG                                  WD2_REG_TRB_INFO_MSB
#define WD2_TRB_INFO_MSB_MASK                                           0x0000FFFF
#define WD2_TRB_INFO_MSB_OFS                                                     0



/* ****** Status Register 68 [0x0110]: ADV_TRG_TRIG_CELL - Advanced Trigger Cell Register (Default: 0x00000000) ****** */

/* ADV_TRG_TRIG_CELL - Advanced trigger cell register */
#define WD2_ADV_TRG_TRIG_CELL_REG                        WD2_REG_ADV_TRG_TRIG_CELL
#define WD2_ADV_TRG_TRIG_CELL_MASK                                      0xFFFFFFFF
#define WD2_ADV_TRG_TRIG_CELL_OFS                                                0



/* ****** Status Register 69 [0x0114]: ADV_TRG_STAT1 - Advanced Trigger Status Register 1 (Default: 0x00000000) ****** */

/* ADV_TRG_STAT_1 - Advanced trigger status register 1 */
#define WD2_ADV_TRG_STAT_1_REG                               WD2_REG_ADV_TRG_STAT1
#define WD2_ADV_TRG_STAT_1_MASK                                         0xFFFFFFFF
#define WD2_ADV_TRG_STAT_1_OFS                                                   0



/* ****** Status Register 70 [0x0118]: ADV_TRG_STAT2 - Advanced Trigger Status Register 2 (Default: 0x00000000) ****** */

/* ADV_TRG_STAT_2 - Advanced trigger status register 2 */
#define WD2_ADV_TRG_STAT_2_REG                               WD2_REG_ADV_TRG_STAT2
#define WD2_ADV_TRG_STAT_2_MASK                                         0xFFFFFFFF
#define WD2_ADV_TRG_STAT_2_OFS                                                   0



/* ****** Status Register 71 [0x011C]: ADV_TRG_STAT3 - Advanced Trigger Status Register 3 (Default: 0x00000000) ****** */

/* ADV_TRG_STAT_3 - Advanced trigger status register 3 */
#define WD2_ADV_TRG_STAT_3_REG                               WD2_REG_ADV_TRG_STAT3
#define WD2_ADV_TRG_STAT_3_MASK                                         0xFFFFFFFF
#define WD2_ADV_TRG_STAT_3_OFS                                                   0



/* ****** Status Register 72 [0x0120]: ADV_TRG_STAT4 - Advanced Trigger Status Register 4 (Default: 0x00000000) ****** */

/* ADV_TRG_STAT_4 - Advanced trigger status register 4 */
#define WD2_ADV_TRG_STAT_4_REG                               WD2_REG_ADV_TRG_STAT4
#define WD2_ADV_TRG_STAT_4_MASK                                         0xFFFFFFFF
#define WD2_ADV_TRG_STAT_4_OFS                                                   0



/* ****** Status Register 73 [0x0124]: MAX_DRS_ADC_PKT_SAMPLES - Maximum DRS/ADC samples per Packet (Default: 0x00000000) ****** */

/* MAX_DRS_ADC_PKT_SAMPLES - Maximum number of DRS/ADC samples per packet */
#define WD2_MAX_DRS_ADC_PKT_SAMPLES_REG            WD2_REG_MAX_DRS_ADC_PKT_SAMPLES
#define WD2_MAX_DRS_ADC_PKT_SAMPLES_MASK                                0x0000FFFF
#define WD2_MAX_DRS_ADC_PKT_SAMPLES_OFS                                          0



/* ****** Status Register 74 [0x0128]: MAX_TDC_PKT_SAMPLES - Maximum TDC samples per Packet (Default: 0x00000000) ****** */

/* MAX_TDC_PKT_SAMPLES - Maximum number of TDC samples per packet */
#define WD2_MAX_TDC_PKT_SAMPLES_REG                    WD2_REG_MAX_TDC_PKT_SAMPLES
#define WD2_MAX_TDC_PKT_SAMPLES_MASK                                    0x0003FFFF
#define WD2_MAX_TDC_PKT_SAMPLES_OFS                                              0



/* ****** Status Register 75 [0x012C]: MAX_TRG_PKT_SAMPLES - Maximum advanced trigger output samples per Packet (Default: 0x00000000) ****** */

/* MAX_TRG_PKT_SAMPLES - Maximum number of advanced trigger output samples per packet */
#define WD2_MAX_TRG_PKT_SAMPLES_REG                    WD2_REG_MAX_TRG_PKT_SAMPLES
#define WD2_MAX_TRG_PKT_SAMPLES_MASK                                    0x0000FFFF
#define WD2_MAX_TRG_PKT_SAMPLES_OFS                                              0



/* ****** Status Register 76 [0x0130]: MAX_SCL_PKT_SAMPLES - Maximum scaler values per Packet (Default: 0x00000000) ****** */

/* MAX_SCL_PKT_SAMPLES - Maximum number of scaler values per packet */
#define WD2_MAX_SCL_PKT_SAMPLES_REG                    WD2_REG_MAX_SCL_PKT_SAMPLES
#define WD2_MAX_SCL_PKT_SAMPLES_MASK                                    0x0000FFFF
#define WD2_MAX_SCL_PKT_SAMPLES_OFS                                              0



/* ****** Status Register 77 [0x0134]: CLK_CTRL_MOD_FLAG - Set if WD2 configuration registers are modified (Default: 0x00000000) ****** */

/* TRIGGER_DAQ_CLK_CAL_MOD - Trigger DAQ clock calibration modified flag */
#define WD2_TRIGGER_DAQ_CLK_CAL_MOD_REG                  WD2_REG_CLK_CTRL_MOD_FLAG
#define WD2_TRIGGER_DAQ_CLK_CAL_MOD_MASK                                0x00000010
#define WD2_TRIGGER_DAQ_CLK_CAL_MOD_OFS                                          4

/* ADC_RST_MOD - ADC reset modified flag */
#define WD2_ADC_RST_MOD_REG                              WD2_REG_CLK_CTRL_MOD_FLAG
#define WD2_ADC_RST_MOD_MASK                                            0x00000008
#define WD2_ADC_RST_MOD_OFS                                                      3

/* CLK_SEL_AND_DRS_CLK_DIV_MOD - DAQ clock select and DRS clock divider modified flags */
#define WD2_CLK_SEL_AND_DRS_CLK_DIV_MOD_REG              WD2_REG_CLK_CTRL_MOD_FLAG
#define WD2_CLK_SEL_AND_DRS_CLK_DIV_MOD_MASK                            0x00000004
#define WD2_CLK_SEL_AND_DRS_CLK_DIV_MOD_OFS                                      2

/* EXT_CLK_FREQ_MOD - External clock frequency modified flags */
#define WD2_EXT_CLK_FREQ_MOD_REG                         WD2_REG_CLK_CTRL_MOD_FLAG
#define WD2_EXT_CLK_FREQ_MOD_MASK                                       0x00000002
#define WD2_EXT_CLK_FREQ_MOD_OFS                                                 1

/* LOCAL_CLK_FREQ_MOD - Local clock frequency modified flags */
#define WD2_LOCAL_CLK_FREQ_MOD_REG                       WD2_REG_CLK_CTRL_MOD_FLAG
#define WD2_LOCAL_CLK_FREQ_MOD_MASK                                     0x00000001
#define WD2_LOCAL_CLK_FREQ_MOD_OFS                                               0



/* ****** Status Register 78 [0x0138]: DRS_MOD_FLAG - Set if DRS configuration registers are modified (Default: 0x00000000) ****** */

/* DRS_CTRL_MOD - DRS control bits modified flags */
#define WD2_DRS_CTRL_MOD_REG                                  WD2_REG_DRS_MOD_FLAG
#define WD2_DRS_CTRL_MOD_MASK                                           0x00000004
#define WD2_DRS_CTRL_MOD_OFS                                                     2

/* DRS_WSR_MOD - DRS write shift register modified flags */
#define WD2_DRS_WSR_MOD_REG                                   WD2_REG_DRS_MOD_FLAG
#define WD2_DRS_WSR_MOD_MASK                                            0x00000002
#define WD2_DRS_WSR_MOD_OFS                                                      1

/* DRS_WCR_MOD - DRS write control register modified flags */
#define WD2_DRS_WCR_MOD_REG                                   WD2_REG_DRS_MOD_FLAG
#define WD2_DRS_WCR_MOD_MASK                                            0x00000001
#define WD2_DRS_WCR_MOD_OFS                                                      0



/* ****** Status Register 79 [0x013C]: COM_PLD_SIZE_MOD_FLAG - Set if maximum packet payload size register is modified (Default: 0x00000000) ****** */

/* COM_PLD_SIZE_MOD - Maximum packet payload size modified flag */
#define WD2_COM_PLD_SIZE_MOD_REG                     WD2_REG_COM_PLD_SIZE_MOD_FLAG
#define WD2_COM_PLD_SIZE_MOD_MASK                                       0x0000000F
#define WD2_COM_PLD_SIZE_MOD_OFS                                                 0



/* ****** Status Register 80 [0x0140]: ADC_SAMPLE_DIV_MOD_FLAG - Set if ADC downsampling divider register is modified (Default: 0x00000000) ****** */

/* ADC_SAMPLE_DIV_MOD - ADC downsampling divider modified flags */
#define WD2_ADC_SAMPLE_DIV_MOD_REG                 WD2_REG_ADC_SAMPLE_DIV_MOD_FLAG
#define WD2_ADC_SAMPLE_DIV_MOD_MASK                                     0x0000000F
#define WD2_ADC_SAMPLE_DIV_MOD_OFS                                               0



/* ****** Status Register 81 [0x0144]: DAC_0_1_MOD_FLAG - Set if DAC 0 and 1 configuration registers are modified (Default: 0x00000000) ****** */

/* DAC0_A_MOD - DAC channel a modified flags */
#define WD2_DAC0_A_MOD_REG                                WD2_REG_DAC_0_1_MOD_FLAG
#define WD2_DAC0_A_MOD_MASK                                             0xC0000000
#define WD2_DAC0_A_MOD_OFS                                                      30

/* DAC0_B_MOD - DAC channel b modified flags */
#define WD2_DAC0_B_MOD_REG                                WD2_REG_DAC_0_1_MOD_FLAG
#define WD2_DAC0_B_MOD_MASK                                             0x30000000
#define WD2_DAC0_B_MOD_OFS                                                      28

/* DAC0_C_MOD - DAC channel c modified flags */
#define WD2_DAC0_C_MOD_REG                                WD2_REG_DAC_0_1_MOD_FLAG
#define WD2_DAC0_C_MOD_MASK                                             0x0C000000
#define WD2_DAC0_C_MOD_OFS                                                      26

/* DAC0_D_MOD - DAC channel d modified flags */
#define WD2_DAC0_D_MOD_REG                                WD2_REG_DAC_0_1_MOD_FLAG
#define WD2_DAC0_D_MOD_MASK                                             0x03000000
#define WD2_DAC0_D_MOD_OFS                                                      24

/* DAC0_E_MOD - DAC channel e modified flags */
#define WD2_DAC0_E_MOD_REG                                WD2_REG_DAC_0_1_MOD_FLAG
#define WD2_DAC0_E_MOD_MASK                                             0x00C00000
#define WD2_DAC0_E_MOD_OFS                                                      22

/* DAC0_F_MOD - DAC channel f modified flags */
#define WD2_DAC0_F_MOD_REG                                WD2_REG_DAC_0_1_MOD_FLAG
#define WD2_DAC0_F_MOD_MASK                                             0x00300000
#define WD2_DAC0_F_MOD_OFS                                                      20

/* DAC0_G_MOD - DAC channel g modified flags */
#define WD2_DAC0_G_MOD_REG                                WD2_REG_DAC_0_1_MOD_FLAG
#define WD2_DAC0_G_MOD_MASK                                             0x000C0000
#define WD2_DAC0_G_MOD_OFS                                                      18

/* DAC0_H_MOD - DAC channel h modified flags */
#define WD2_DAC0_H_MOD_REG                                WD2_REG_DAC_0_1_MOD_FLAG
#define WD2_DAC0_H_MOD_MASK                                             0x00030000
#define WD2_DAC0_H_MOD_OFS                                                      16

/* DAC1_A_MOD - DAC channel a modified flags */
#define WD2_DAC1_A_MOD_REG                                WD2_REG_DAC_0_1_MOD_FLAG
#define WD2_DAC1_A_MOD_MASK                                             0x0000C000
#define WD2_DAC1_A_MOD_OFS                                                      14

/* DAC1_B_MOD - DAC channel b modified flags */
#define WD2_DAC1_B_MOD_REG                                WD2_REG_DAC_0_1_MOD_FLAG
#define WD2_DAC1_B_MOD_MASK                                             0x00003000
#define WD2_DAC1_B_MOD_OFS                                                      12

/* DAC1_C_MOD - DAC channel c modified flags */
#define WD2_DAC1_C_MOD_REG                                WD2_REG_DAC_0_1_MOD_FLAG
#define WD2_DAC1_C_MOD_MASK                                             0x00000C00
#define WD2_DAC1_C_MOD_OFS                                                      10

/* DAC1_D_MOD - DAC channel d modified flags */
#define WD2_DAC1_D_MOD_REG                                WD2_REG_DAC_0_1_MOD_FLAG
#define WD2_DAC1_D_MOD_MASK                                             0x00000300
#define WD2_DAC1_D_MOD_OFS                                                       8

/* DAC1_E_MOD - DAC channel e modified flags */
#define WD2_DAC1_E_MOD_REG                                WD2_REG_DAC_0_1_MOD_FLAG
#define WD2_DAC1_E_MOD_MASK                                             0x000000C0
#define WD2_DAC1_E_MOD_OFS                                                       6

/* DAC1_F_MOD - DAC channel f modified flags */
#define WD2_DAC1_F_MOD_REG                                WD2_REG_DAC_0_1_MOD_FLAG
#define WD2_DAC1_F_MOD_MASK                                             0x00000030
#define WD2_DAC1_F_MOD_OFS                                                       4

/* DAC1_G_MOD - DAC channel g modified flags */
#define WD2_DAC1_G_MOD_REG                                WD2_REG_DAC_0_1_MOD_FLAG
#define WD2_DAC1_G_MOD_MASK                                             0x0000000C
#define WD2_DAC1_G_MOD_OFS                                                       2

/* DAC1_H_MOD - DAC channel h modified flags */
#define WD2_DAC1_H_MOD_REG                                WD2_REG_DAC_0_1_MOD_FLAG
#define WD2_DAC1_H_MOD_MASK                                             0x00000003
#define WD2_DAC1_H_MOD_OFS                                                       0



/* ****** Status Register 82 [0x0148]: DAC_2_MOD_FLAG - Set if DAC 2 configuration registers are modified (Default: 0x00000000) ****** */

/* DAC2_A_MOD - DAC channel a modified flags */
#define WD2_DAC2_A_MOD_REG                                  WD2_REG_DAC_2_MOD_FLAG
#define WD2_DAC2_A_MOD_MASK                                             0xC0000000
#define WD2_DAC2_A_MOD_OFS                                                      30

/* DAC2_B_MOD - DAC channel b modified flags */
#define WD2_DAC2_B_MOD_REG                                  WD2_REG_DAC_2_MOD_FLAG
#define WD2_DAC2_B_MOD_MASK                                             0x30000000
#define WD2_DAC2_B_MOD_OFS                                                      28

/* DAC2_C_MOD - DAC channel c modified flags */
#define WD2_DAC2_C_MOD_REG                                  WD2_REG_DAC_2_MOD_FLAG
#define WD2_DAC2_C_MOD_MASK                                             0x0C000000
#define WD2_DAC2_C_MOD_OFS                                                      26

/* DAC2_D_MOD - DAC channel d modified flags */
#define WD2_DAC2_D_MOD_REG                                  WD2_REG_DAC_2_MOD_FLAG
#define WD2_DAC2_D_MOD_MASK                                             0x03000000
#define WD2_DAC2_D_MOD_OFS                                                      24

/* DAC2_E_MOD - DAC channel e modified flags */
#define WD2_DAC2_E_MOD_REG                                  WD2_REG_DAC_2_MOD_FLAG
#define WD2_DAC2_E_MOD_MASK                                             0x00C00000
#define WD2_DAC2_E_MOD_OFS                                                      22

/* DAC2_F_MOD - DAC channel f modified flags */
#define WD2_DAC2_F_MOD_REG                                  WD2_REG_DAC_2_MOD_FLAG
#define WD2_DAC2_F_MOD_MASK                                             0x00300000
#define WD2_DAC2_F_MOD_OFS                                                      20

/* DAC2_G_MOD - DAC channel g modified flags */
#define WD2_DAC2_G_MOD_REG                                  WD2_REG_DAC_2_MOD_FLAG
#define WD2_DAC2_G_MOD_MASK                                             0x000C0000
#define WD2_DAC2_G_MOD_OFS                                                      18

/* DAC2_H_MOD - DAC channel h modified flags */
#define WD2_DAC2_H_MOD_REG                                  WD2_REG_DAC_2_MOD_FLAG
#define WD2_DAC2_H_MOD_MASK                                             0x00030000
#define WD2_DAC2_H_MOD_OFS                                                      16



/* ****** Status Register 83 [0x014C]: FE_0_15_MOD_FLAG - Set if frontend configuraiton registers are modified (Default: 0x00000000) ****** */

/* FE_0_MOD - Frontend channel 0 register modified flags */
#define WD2_FE_0_MOD_REG                                  WD2_REG_FE_0_15_MOD_FLAG
#define WD2_FE_0_MOD_MASK                                               0xC0000000
#define WD2_FE_0_MOD_OFS                                                        30

/* FE_1_MOD - Frontend channel 1 register modified flags */
#define WD2_FE_1_MOD_REG                                  WD2_REG_FE_0_15_MOD_FLAG
#define WD2_FE_1_MOD_MASK                                               0x30000000
#define WD2_FE_1_MOD_OFS                                                        28

/* FE_2_MOD - Frontend channel 2 register modified flags */
#define WD2_FE_2_MOD_REG                                  WD2_REG_FE_0_15_MOD_FLAG
#define WD2_FE_2_MOD_MASK                                               0x0C000000
#define WD2_FE_2_MOD_OFS                                                        26

/* FE_3_MOD - Frontend channel 3 register modified flags */
#define WD2_FE_3_MOD_REG                                  WD2_REG_FE_0_15_MOD_FLAG
#define WD2_FE_3_MOD_MASK                                               0x03000000
#define WD2_FE_3_MOD_OFS                                                        24

/* FE_4_MOD - Frontend channel 4 register modified flags */
#define WD2_FE_4_MOD_REG                                  WD2_REG_FE_0_15_MOD_FLAG
#define WD2_FE_4_MOD_MASK                                               0x00C00000
#define WD2_FE_4_MOD_OFS                                                        22

/* FE_5_MOD - Frontend channel 5 register modified flags */
#define WD2_FE_5_MOD_REG                                  WD2_REG_FE_0_15_MOD_FLAG
#define WD2_FE_5_MOD_MASK                                               0x00300000
#define WD2_FE_5_MOD_OFS                                                        20

/* FE_6_MOD - Frontend channel 6 register modified flags */
#define WD2_FE_6_MOD_REG                                  WD2_REG_FE_0_15_MOD_FLAG
#define WD2_FE_6_MOD_MASK                                               0x000C0000
#define WD2_FE_6_MOD_OFS                                                        18

/* FE_7_MOD - Frontend channel 7 register modified flags */
#define WD2_FE_7_MOD_REG                                  WD2_REG_FE_0_15_MOD_FLAG
#define WD2_FE_7_MOD_MASK                                               0x00030000
#define WD2_FE_7_MOD_OFS                                                        16

/* FE_8_MOD - Frontend channel 8 register modified flags */
#define WD2_FE_8_MOD_REG                                  WD2_REG_FE_0_15_MOD_FLAG
#define WD2_FE_8_MOD_MASK                                               0x0000C000
#define WD2_FE_8_MOD_OFS                                                        14

/* FE_9_MOD - Frontend channel 9 register modified flags */
#define WD2_FE_9_MOD_REG                                  WD2_REG_FE_0_15_MOD_FLAG
#define WD2_FE_9_MOD_MASK                                               0x00003000
#define WD2_FE_9_MOD_OFS                                                        12

/* FE_10_MOD - Frontend channel 10 register modified flags */
#define WD2_FE_10_MOD_REG                                 WD2_REG_FE_0_15_MOD_FLAG
#define WD2_FE_10_MOD_MASK                                              0x00000C00
#define WD2_FE_10_MOD_OFS                                                       10

/* FE_11_MOD - Frontend channel 11 register modified flags */
#define WD2_FE_11_MOD_REG                                 WD2_REG_FE_0_15_MOD_FLAG
#define WD2_FE_11_MOD_MASK                                              0x00000300
#define WD2_FE_11_MOD_OFS                                                        8

/* FE_12_MOD - Frontend channel 12 register modified flags */
#define WD2_FE_12_MOD_REG                                 WD2_REG_FE_0_15_MOD_FLAG
#define WD2_FE_12_MOD_MASK                                              0x000000C0
#define WD2_FE_12_MOD_OFS                                                        6

/* FE_13_MOD - Frontend channel 13 register modified flags */
#define WD2_FE_13_MOD_REG                                 WD2_REG_FE_0_15_MOD_FLAG
#define WD2_FE_13_MOD_MASK                                              0x00000030
#define WD2_FE_13_MOD_OFS                                                        4

/* FE_14_MOD - Frontend channel 14 register modified flags */
#define WD2_FE_14_MOD_REG                                 WD2_REG_FE_0_15_MOD_FLAG
#define WD2_FE_14_MOD_MASK                                              0x0000000C
#define WD2_FE_14_MOD_OFS                                                        2

/* FE_15_MOD - Frontend channel 15 register modified flags */
#define WD2_FE_15_MOD_REG                                 WD2_REG_FE_0_15_MOD_FLAG
#define WD2_FE_15_MOD_MASK                                              0x00000003
#define WD2_FE_15_MOD_OFS                                                        0



/* ****** Status Register 84 [0x0150]: HV_U_TARGET_0_7_MOD_FLAG - Set if HV target voltage configuraiton of channel 0 to 7 registers are modified (Default: 0x00000000) ****** */

/* HV_U_TARGET_0_MOD - Target high voltage channel 0 register modified flags */
#define WD2_HV_U_TARGET_0_MOD_REG                 WD2_REG_HV_U_TARGET_0_7_MOD_FLAG
#define WD2_HV_U_TARGET_0_MOD_MASK                                      0xF0000000
#define WD2_HV_U_TARGET_0_MOD_OFS                                               28

/* HV_U_TARGET_1_MOD - Target high voltage channel 1 register modified flags */
#define WD2_HV_U_TARGET_1_MOD_REG                 WD2_REG_HV_U_TARGET_0_7_MOD_FLAG
#define WD2_HV_U_TARGET_1_MOD_MASK                                      0x0F000000
#define WD2_HV_U_TARGET_1_MOD_OFS                                               24

/* HV_U_TARGET_2_MOD - Target high voltage channel 2 register modified flags */
#define WD2_HV_U_TARGET_2_MOD_REG                 WD2_REG_HV_U_TARGET_0_7_MOD_FLAG
#define WD2_HV_U_TARGET_2_MOD_MASK                                      0x00F00000
#define WD2_HV_U_TARGET_2_MOD_OFS                                               20

/* HV_U_TARGET_3_MOD - Target high voltage channel 3 register modified flags */
#define WD2_HV_U_TARGET_3_MOD_REG                 WD2_REG_HV_U_TARGET_0_7_MOD_FLAG
#define WD2_HV_U_TARGET_3_MOD_MASK                                      0x000F0000
#define WD2_HV_U_TARGET_3_MOD_OFS                                               16

/* HV_U_TARGET_4_MOD - Target high voltage channel 4 register modified flags */
#define WD2_HV_U_TARGET_4_MOD_REG                 WD2_REG_HV_U_TARGET_0_7_MOD_FLAG
#define WD2_HV_U_TARGET_4_MOD_MASK                                      0x0000F000
#define WD2_HV_U_TARGET_4_MOD_OFS                                               12

/* HV_U_TARGET_5_MOD - Target high voltage channel 5 register modified flags */
#define WD2_HV_U_TARGET_5_MOD_REG                 WD2_REG_HV_U_TARGET_0_7_MOD_FLAG
#define WD2_HV_U_TARGET_5_MOD_MASK                                      0x00000F00
#define WD2_HV_U_TARGET_5_MOD_OFS                                                8

/* HV_U_TARGET_6_MOD - Target high voltage channel 6 register modified flags */
#define WD2_HV_U_TARGET_6_MOD_REG                 WD2_REG_HV_U_TARGET_0_7_MOD_FLAG
#define WD2_HV_U_TARGET_6_MOD_MASK                                      0x000000F0
#define WD2_HV_U_TARGET_6_MOD_OFS                                                4

/* HV_U_TARGET_7_MOD - Target high voltage channel 7 register modified flags */
#define WD2_HV_U_TARGET_7_MOD_REG                 WD2_REG_HV_U_TARGET_0_7_MOD_FLAG
#define WD2_HV_U_TARGET_7_MOD_MASK                                      0x0000000F
#define WD2_HV_U_TARGET_7_MOD_OFS                                                0



/* ****** Status Register 85 [0x0154]: HV_U_TARGET_8_15_MOD_FLAG - Set if HV target voltage configuraiton of channel 8 to 15 registers are modified (Default: 0x00000000) ****** */

/* HV_U_TARGET_8_MOD - Target high voltage channel 8 register modified flags */
#define WD2_HV_U_TARGET_8_MOD_REG                WD2_REG_HV_U_TARGET_8_15_MOD_FLAG
#define WD2_HV_U_TARGET_8_MOD_MASK                                      0xF0000000
#define WD2_HV_U_TARGET_8_MOD_OFS                                               28

/* HV_U_TARGET_9_MOD - Target high voltage channel 9 register modified flags */
#define WD2_HV_U_TARGET_9_MOD_REG                WD2_REG_HV_U_TARGET_8_15_MOD_FLAG
#define WD2_HV_U_TARGET_9_MOD_MASK                                      0x0F000000
#define WD2_HV_U_TARGET_9_MOD_OFS                                               24

/* HV_U_TARGET_10_MOD - Target high voltage channel 10 register modified flags */
#define WD2_HV_U_TARGET_10_MOD_REG               WD2_REG_HV_U_TARGET_8_15_MOD_FLAG
#define WD2_HV_U_TARGET_10_MOD_MASK                                     0x00F00000
#define WD2_HV_U_TARGET_10_MOD_OFS                                              20

/* HV_U_TARGET_11_MOD - Target high voltage channel 11 register modified flags */
#define WD2_HV_U_TARGET_11_MOD_REG               WD2_REG_HV_U_TARGET_8_15_MOD_FLAG
#define WD2_HV_U_TARGET_11_MOD_MASK                                     0x000F0000
#define WD2_HV_U_TARGET_11_MOD_OFS                                              16

/* HV_U_TARGET_12_MOD - Target high voltage channel 12 register modified flags */
#define WD2_HV_U_TARGET_12_MOD_REG               WD2_REG_HV_U_TARGET_8_15_MOD_FLAG
#define WD2_HV_U_TARGET_12_MOD_MASK                                     0x0000F000
#define WD2_HV_U_TARGET_12_MOD_OFS                                              12

/* HV_U_TARGET_13_MOD - Target high voltage channel 13 register modified flags */
#define WD2_HV_U_TARGET_13_MOD_REG               WD2_REG_HV_U_TARGET_8_15_MOD_FLAG
#define WD2_HV_U_TARGET_13_MOD_MASK                                     0x00000F00
#define WD2_HV_U_TARGET_13_MOD_OFS                                               8

/* HV_U_TARGET_14_MOD - Target high voltage channel 14 register modified flags */
#define WD2_HV_U_TARGET_14_MOD_REG               WD2_REG_HV_U_TARGET_8_15_MOD_FLAG
#define WD2_HV_U_TARGET_14_MOD_MASK                                     0x000000F0
#define WD2_HV_U_TARGET_14_MOD_OFS                                               4

/* HV_U_TARGET_15_MOD - Target high voltage channel 15 register modified flags */
#define WD2_HV_U_TARGET_15_MOD_REG               WD2_REG_HV_U_TARGET_8_15_MOD_FLAG
#define WD2_HV_U_TARGET_15_MOD_MASK                                     0x0000000F
#define WD2_HV_U_TARGET_15_MOD_OFS                                               0



/* ****** Status Register 86 [0x0158]: HV_MOD_FLAG - Set if single HV configuraiton registers are modified (Default: 0x00000000) ****** */

/* HV_R_SHUNT_MOD - HV supply shunt resistor register modified flags */
#define WD2_HV_R_SHUNT_MOD_REG                                 WD2_REG_HV_MOD_FLAG
#define WD2_HV_R_SHUNT_MOD_MASK                                         0x0000000F
#define WD2_HV_R_SHUNT_MOD_OFS                                                   0



/* ****** Status Register 87 [0x015C]: LMK_0_7_MOD_FLAG - Set if LMK configuraiton registers are modified (Default: 0x00000000) ****** */

/* LMK_0_MOD - LMK channel 0 register modified flags */
#define WD2_LMK_0_MOD_REG                                 WD2_REG_LMK_0_7_MOD_FLAG
#define WD2_LMK_0_MOD_MASK                                              0xF0000000
#define WD2_LMK_0_MOD_OFS                                                       28

/* LMK_1_MOD - LMK channel 1 register modified flags */
#define WD2_LMK_1_MOD_REG                                 WD2_REG_LMK_0_7_MOD_FLAG
#define WD2_LMK_1_MOD_MASK                                              0x0F000000
#define WD2_LMK_1_MOD_OFS                                                       24

/* LMK_2_MOD - LMK channel 2 register modified flags */
#define WD2_LMK_2_MOD_REG                                 WD2_REG_LMK_0_7_MOD_FLAG
#define WD2_LMK_2_MOD_MASK                                              0x00F00000
#define WD2_LMK_2_MOD_OFS                                                       20

/* LMK_3_MOD - LMK channel 3 register modified flags */
#define WD2_LMK_3_MOD_REG                                 WD2_REG_LMK_0_7_MOD_FLAG
#define WD2_LMK_3_MOD_MASK                                              0x000F0000
#define WD2_LMK_3_MOD_OFS                                                       16

/* LMK_4_MOD - LMK channel 4 register modified flags */
#define WD2_LMK_4_MOD_REG                                 WD2_REG_LMK_0_7_MOD_FLAG
#define WD2_LMK_4_MOD_MASK                                              0x0000F000
#define WD2_LMK_4_MOD_OFS                                                       12

/* LMK_5_MOD - LMK channel 5 register modified flags */
#define WD2_LMK_5_MOD_REG                                 WD2_REG_LMK_0_7_MOD_FLAG
#define WD2_LMK_5_MOD_MASK                                              0x00000F00
#define WD2_LMK_5_MOD_OFS                                                        8

/* LMK_6_MOD - LMK channel 6 register modified flags */
#define WD2_LMK_6_MOD_REG                                 WD2_REG_LMK_0_7_MOD_FLAG
#define WD2_LMK_6_MOD_MASK                                              0x000000F0
#define WD2_LMK_6_MOD_OFS                                                        4

/* LMK_7_MOD - LMK channel 7 register modified flags */
#define WD2_LMK_7_MOD_REG                                 WD2_REG_LMK_0_7_MOD_FLAG
#define WD2_LMK_7_MOD_MASK                                              0x0000000F
#define WD2_LMK_7_MOD_OFS                                                        0



/* ****** Status Register 88 [0x0160]: LMK_8_15_MOD_FLAG - Set if LMK configuraiton registers are modified (Default: 0x00000000) ****** */

/* LMK_8_MOD - LMK Register 8 modified flags */
#define WD2_LMK_8_MOD_REG                                WD2_REG_LMK_8_15_MOD_FLAG
#define WD2_LMK_8_MOD_MASK                                              0x00F00000
#define WD2_LMK_8_MOD_OFS                                                       20

/* LMK_9_MOD - LMK Register 9 modified flags */
#define WD2_LMK_9_MOD_REG                                WD2_REG_LMK_8_15_MOD_FLAG
#define WD2_LMK_9_MOD_MASK                                              0x000F0000
#define WD2_LMK_9_MOD_OFS                                                       16

/* LMK_11_MOD - LMK Register 11 modified flags */
#define WD2_LMK_11_MOD_REG                               WD2_REG_LMK_8_15_MOD_FLAG
#define WD2_LMK_11_MOD_MASK                                             0x0000F000
#define WD2_LMK_11_MOD_OFS                                                      12

/* LMK_13_MOD - LMK Register 13 modified flags */
#define WD2_LMK_13_MOD_REG                               WD2_REG_LMK_8_15_MOD_FLAG
#define WD2_LMK_13_MOD_MASK                                             0x00000F00
#define WD2_LMK_13_MOD_OFS                                                       8

/* LMK_14_MOD - LMK Register 14 modified flags */
#define WD2_LMK_14_MOD_REG                               WD2_REG_LMK_8_15_MOD_FLAG
#define WD2_LMK_14_MOD_MASK                                             0x000000F0
#define WD2_LMK_14_MOD_OFS                                                       4

/* LMK_15_MOD - LMK Register 15 modified flags */
#define WD2_LMK_15_MOD_REG                               WD2_REG_LMK_8_15_MOD_FLAG
#define WD2_LMK_15_MOD_MASK                                             0x0000000F
#define WD2_LMK_15_MOD_OFS                                                       0


/*
 * Number of Registers
 */

#define REG_NR_OF_CTRL_REGS          161
#define REG_NR_OF_STAT_REGS          89

#ifndef WD2_DONT_INCLUDE_REG_ACCESS_VARS

typedef unsigned int (*wd2_reg_func)(unsigned int, unsigned int, unsigned int, unsigned int);

typedef struct
{
  wd2_reg_func  func;
  unsigned int par;
} wd2_reg_func_type;

extern const wd2_reg_func_type  wd2_ctrl_reg_func_list[];
extern const wd2_reg_func_type  wd2_stat_reg_func_list[];

#endif /* WD2_DONT_INCLUDE_REG_ACCESS_VARS */

#ifndef WD2_DONT_INCLUDE_VARS

typedef struct {
  const char * name;
  const unsigned int reg;
} wd2_reg_name_entry_type;

extern const wd2_reg_name_entry_type  wd2_reg_list[];

typedef struct {
  const char * name;
  const unsigned int reg;
  const unsigned int mask;
  const unsigned int ofs;
} wd2_bit_group_entry_type;

extern const wd2_bit_group_entry_type  wd2_bit_group_list[];

extern const unsigned int ctrl_reg_default[];

#endif /* WD2_DONT_INCLUDE_VARS */

#endif /* WD2_REGISTER_MAP_V8 */

/******************************************************************************/

#endif /* __REGISTER_MAP_V8_H__ */

/******************************************************************************/

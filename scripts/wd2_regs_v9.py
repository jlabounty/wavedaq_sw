# #####################################################################################
#  Paul Scherrer Institut
# #####################################################################################
#
#  Project :  WaveDream2
#
#  Author  :  schmid_e (Author of generation script)
#  Created :  09.08.2021 13:10:56
#
#  Register Layout Version :  9
#
#  Description :  Register map definitions.
#
# #####################################################################################
# #####################################################################################

# ###############################################################################
# # definitions                                                                ##
# ###############################################################################

#
# Register Offsets
#

WD2_CTRL_REG_BASE_OFS = 0x1000
WD2_STAT_REG_BASE_OFS = 0x0000

# Control Registers ***
WD2_REG_WDB_LOC                                 = 0x1000
WD2_REG_CTRL                                    = 0x1004
WD2_REG_CAL_CTRL                                = 0x1008
WD2_REG_CLK_CTRL                                = 0x100C
WD2_REG_DRS_CTRL                                = 0x1010
WD2_REG_COM_CTRL                                = 0x1014
WD2_REG_COM_PLD_SIZE                            = 0x1018
WD2_REG_DRS_CH_TX_EN                            = 0x101C
WD2_REG_ADC_CH_TX_EN                            = 0x1020
WD2_REG_TDC_CH_TX_EN                            = 0x1024
WD2_REG_DRS_TX_SAMPLES                          = 0x1028
WD2_REG_ADC_TX_SAMPLES                          = 0x102C
WD2_REG_TDC_TX_SAMPLES                          = 0x1030
WD2_REG_TRG_TX_SAMPLES                          = 0x1034
WD2_REG_ADC_SAMPLE_DIV                          = 0x1038
WD2_REG_ZERO_SUPR                               = 0x103C
WD2_REG_RST                                     = 0x1040
WD2_REG_APLY_CFG                                = 0x1044
WD2_REG_DAC0_A_B                                = 0x1048
WD2_REG_DAC0_C_D                                = 0x104C
WD2_REG_DAC0_E_F                                = 0x1050
WD2_REG_DAC0_G_H                                = 0x1054
WD2_REG_DAC1_A_B                                = 0x1058
WD2_REG_DAC1_C_D                                = 0x105C
WD2_REG_DAC1_E_F                                = 0x1060
WD2_REG_DAC1_G_H                                = 0x1064
WD2_REG_DAC2_A_B                                = 0x1068
WD2_REG_DAC2_C_D                                = 0x106C
WD2_REG_DAC2_E_F                                = 0x1070
WD2_REG_DAC2_G_H                                = 0x1074
WD2_REG_FE_CFG_0_1                              = 0x1078
WD2_REG_FE_CFG_2_3                              = 0x107C
WD2_REG_FE_CFG_4_5                              = 0x1080
WD2_REG_FE_CFG_6_7                              = 0x1084
WD2_REG_FE_CFG_8_9                              = 0x1088
WD2_REG_FE_CFG_10_11                            = 0x108C
WD2_REG_FE_CFG_12_13                            = 0x1090
WD2_REG_FE_CFG_14_15                            = 0x1094
WD2_REG_HV_U_TARGET_0                           = 0x1098
WD2_REG_HV_U_TARGET_1                           = 0x109C
WD2_REG_HV_U_TARGET_2                           = 0x10A0
WD2_REG_HV_U_TARGET_3                           = 0x10A4
WD2_REG_HV_U_TARGET_4                           = 0x10A8
WD2_REG_HV_U_TARGET_5                           = 0x10AC
WD2_REG_HV_U_TARGET_6                           = 0x10B0
WD2_REG_HV_U_TARGET_7                           = 0x10B4
WD2_REG_HV_U_TARGET_8                           = 0x10B8
WD2_REG_HV_U_TARGET_9                           = 0x10BC
WD2_REG_HV_U_TARGET_10                          = 0x10C0
WD2_REG_HV_U_TARGET_11                          = 0x10C4
WD2_REG_HV_U_TARGET_12                          = 0x10C8
WD2_REG_HV_U_TARGET_13                          = 0x10CC
WD2_REG_HV_U_TARGET_14                          = 0x10D0
WD2_REG_HV_U_TARGET_15                          = 0x10D4
WD2_REG_HV_R_SHUNT                              = 0x10D8
WD2_REG_LMK_0                                   = 0x10DC
WD2_REG_LMK_1                                   = 0x10E0
WD2_REG_LMK_2                                   = 0x10E4
WD2_REG_LMK_3                                   = 0x10E8
WD2_REG_LMK_4                                   = 0x10EC
WD2_REG_LMK_5                                   = 0x10F0
WD2_REG_LMK_6                                   = 0x10F4
WD2_REG_LMK_7                                   = 0x10F8
WD2_REG_LMK_8                                   = 0x10FC
WD2_REG_LMK_9                                   = 0x1100
WD2_REG_LMK_11                                  = 0x1104
WD2_REG_LMK_13                                  = 0x1108
WD2_REG_LMK_14                                  = 0x110C
WD2_REG_LMK_15                                  = 0x1110
WD2_REG_ADC_0_CFG_1458                          = 0x1114
WD2_REG_ADC_0_CFG_2367                          = 0x1118
WD2_REG_ADC_1_CFG_1458                          = 0x111C
WD2_REG_ADC_1_CFG_2367                          = 0x1120
WD2_REG_TRG_CFG                                 = 0x1124
WD2_REG_TRG_SRC_POL                             = 0x1128
WD2_REG_TRG_AUTO_PERIOD                         = 0x112C
WD2_REG_TRG_PTRN_EN                             = 0x1130
WD2_REG_TRG_SRC_EN_PTRN0                        = 0x1134
WD2_REG_TRG_STATE_PTRN0                         = 0x1138
WD2_REG_TRG_SRC_EN_PTRN1                        = 0x113C
WD2_REG_TRG_STATE_PTRN1                         = 0x1140
WD2_REG_TRG_SRC_EN_PTRN2                        = 0x1144
WD2_REG_TRG_STATE_PTRN2                         = 0x1148
WD2_REG_TRG_SRC_EN_PTRN3                        = 0x114C
WD2_REG_TRG_STATE_PTRN3                         = 0x1150
WD2_REG_TRG_SRC_EN_PTRN4                        = 0x1154
WD2_REG_TRG_STATE_PTRN4                         = 0x1158
WD2_REG_TRG_SRC_EN_PTRN5                        = 0x115C
WD2_REG_TRG_STATE_PTRN5                         = 0x1160
WD2_REG_TRG_SRC_EN_PTRN6                        = 0x1164
WD2_REG_TRG_STATE_PTRN6                         = 0x1168
WD2_REG_TRG_SRC_EN_PTRN7                        = 0x116C
WD2_REG_TRG_STATE_PTRN7                         = 0x1170
WD2_REG_TRG_SRC_EN_PTRN8                        = 0x1174
WD2_REG_TRG_STATE_PTRN8                         = 0x1178
WD2_REG_TRG_SRC_EN_PTRN9                        = 0x117C
WD2_REG_TRG_STATE_PTRN9                         = 0x1180
WD2_REG_TRG_SRC_EN_PTRN10                       = 0x1184
WD2_REG_TRG_STATE_PTRN10                        = 0x1188
WD2_REG_TRG_SRC_EN_PTRN11                       = 0x118C
WD2_REG_TRG_STATE_PTRN11                        = 0x1190
WD2_REG_TRG_SRC_EN_PTRN12                       = 0x1194
WD2_REG_TRG_STATE_PTRN12                        = 0x1198
WD2_REG_TRG_SRC_EN_PTRN13                       = 0x119C
WD2_REG_TRG_STATE_PTRN13                        = 0x11A0
WD2_REG_TRG_SRC_EN_PTRN14                       = 0x11A4
WD2_REG_TRG_STATE_PTRN14                        = 0x11A8
WD2_REG_TRG_SRC_EN_PTRN15                       = 0x11AC
WD2_REG_TRG_STATE_PTRN15                        = 0x11B0
WD2_REG_TRG_SRC_EN_PTRN16                       = 0x11B4
WD2_REG_TRG_STATE_PTRN16                        = 0x11B8
WD2_REG_TRG_SRC_EN_PTRN17                       = 0x11BC
WD2_REG_TRG_STATE_PTRN17                        = 0x11C0
WD2_REG_TRG_SRC_EN_PTRN18                       = 0x11C4
WD2_REG_TRG_STATE_PTRN18                        = 0x11C8
WD2_REG_ADV_TRG_CTRL                            = 0x11CC
WD2_REG_ADV_TRG_CH_CAL0                         = 0x11D0
WD2_REG_ADV_TRG_CH_CAL1                         = 0x11D4
WD2_REG_ADV_TRG_CH_CAL2                         = 0x11D8
WD2_REG_ADV_TRG_CH_CAL3                         = 0x11DC
WD2_REG_ADV_TRG_PED_CFG                         = 0x11E0
WD2_REG_ADV_TRG_THR0                            = 0x11E4
WD2_REG_ADV_TRG_THR1                            = 0x11E8
WD2_REG_ADV_TRG_THR2                            = 0x11EC
WD2_REG_ADV_TRG_TX_CHK_WORD0                    = 0x11F0
WD2_REG_ADV_TRG_TX_CHK_WORD1                    = 0x11F4
WD2_REG_ADV_TRG_TDC_CH_MASK                     = 0x11F8
WD2_REG_ADV_TRG_CFG12                           = 0x11FC
WD2_REG_ADV_TRG_CFG13                           = 0x1200
WD2_REG_ADV_TRG_CFG14                           = 0x1204
WD2_REG_ADV_TRG_CFG15                           = 0x1208
WD2_REG_ADV_TRG_CFG16                           = 0x120C
WD2_REG_ADV_TRG_CFG17                           = 0x1210
WD2_REG_ADV_TRG_CFG18                           = 0x1214
WD2_REG_ADV_TRG_CFG19                           = 0x1218
WD2_REG_SET_TIME_LSB                            = 0x121C
WD2_REG_SET_TIME_MSB                            = 0x1220
WD2_REG_DBG_SIG_SEL                             = 0x1224
WD2_REG_CRC32_REG_BANK                          = 0x1228

# Status Registers 
WD2_REG_HW_VER                                  = 0x0000
WD2_REG_REG_LAYOUT_VER                          = 0x0004
WD2_REG_FW_BUILD_DATE                           = 0x0008
WD2_REG_FW_BUILD_TIME                           = 0x000C
WD2_REG_SW_BUILD_DATE                           = 0x0010
WD2_REG_SW_BUILD_TIME                           = 0x0014
WD2_REG_FW_GIT_HASH_TAG                         = 0x0018
WD2_REG_SW_GIT_HASH_TAG                         = 0x001C
WD2_REG_PROT_VER                                = 0x0020
WD2_REG_SN                                      = 0x0024
WD2_REG_STATUS                                  = 0x0028
WD2_REG_PLL_LOCK                                = 0x002C
WD2_REG_DRS_STOP_CELL                           = 0x0030
WD2_REG_DRS_STOP_WSR                            = 0x0034
WD2_REG_DRS_SAMPLE_FREQ                         = 0x0038
WD2_REG_ADC_SAMPLE_FREQ                         = 0x003C
WD2_REG_TDC_SAMPLE_FREQ                         = 0x0040
WD2_REG_HV_VER                                  = 0x0044
WD2_REG_HV_I_MEAS_0                             = 0x0048
WD2_REG_HV_I_MEAS_1                             = 0x004C
WD2_REG_HV_I_MEAS_2                             = 0x0050
WD2_REG_HV_I_MEAS_3                             = 0x0054
WD2_REG_HV_I_MEAS_4                             = 0x0058
WD2_REG_HV_I_MEAS_5                             = 0x005C
WD2_REG_HV_I_MEAS_6                             = 0x0060
WD2_REG_HV_I_MEAS_7                             = 0x0064
WD2_REG_HV_I_MEAS_8                             = 0x0068
WD2_REG_HV_I_MEAS_9                             = 0x006C
WD2_REG_HV_I_MEAS_10                            = 0x0070
WD2_REG_HV_I_MEAS_11                            = 0x0074
WD2_REG_HV_I_MEAS_12                            = 0x0078
WD2_REG_HV_I_MEAS_13                            = 0x007C
WD2_REG_HV_I_MEAS_14                            = 0x0080
WD2_REG_HV_I_MEAS_15                            = 0x0084
WD2_REG_HV_U_BASE_MEAS                          = 0x0088
WD2_REG_HV_TEMP_0                               = 0x008C
WD2_REG_HV_TEMP_1                               = 0x0090
WD2_REG_HV_TEMP_2                               = 0x0094
WD2_REG_HV_TEMP_3                               = 0x0098
WD2_REG_SCALER_0                                = 0x009C
WD2_REG_SCALER_1                                = 0x00A0
WD2_REG_SCALER_2                                = 0x00A4
WD2_REG_SCALER_3                                = 0x00A8
WD2_REG_SCALER_4                                = 0x00AC
WD2_REG_SCALER_5                                = 0x00B0
WD2_REG_SCALER_6                                = 0x00B4
WD2_REG_SCALER_7                                = 0x00B8
WD2_REG_SCALER_8                                = 0x00BC
WD2_REG_SCALER_9                                = 0x00C0
WD2_REG_SCALER_10                               = 0x00C4
WD2_REG_SCALER_11                               = 0x00C8
WD2_REG_SCALER_12                               = 0x00CC
WD2_REG_SCALER_13                               = 0x00D0
WD2_REG_SCALER_14                               = 0x00D4
WD2_REG_SCALER_15                               = 0x00D8
WD2_REG_SCALER_PTRN_TRG                         = 0x00DC
WD2_REG_SCALER_EXT_TRG                          = 0x00E0
WD2_REG_SCALER_EXT_CLK                          = 0x00E4
WD2_REG_SCALER_TIME_STAMP_LSB                   = 0x00E8
WD2_REG_SCALER_TIME_STAMP_MSB                   = 0x00EC
WD2_REG_TIME_LSB                                = 0x00F0
WD2_REG_TIME_MSB                                = 0x00F4
WD2_REG_COMP_CH_STAT                            = 0x00F8
WD2_REG_EVENT_TX_RATE                           = 0x00FC
WD2_REG_EVENT_NR                                = 0x0100
WD2_REG_TRB_INFO_STAT                           = 0x0104
WD2_REG_TRB_INFO_LSB                            = 0x0108
WD2_REG_TRB_INFO_MSB                            = 0x010C
WD2_REG_ADV_TRG_TRIG_CELL                       = 0x0110
WD2_REG_ADV_TRG_STAT1                           = 0x0114
WD2_REG_ADV_TRG_STAT2                           = 0x0118
WD2_REG_ADV_TRG_STAT3                           = 0x011C
WD2_REG_ADV_TRG_STAT4                           = 0x0120
WD2_REG_MAX_DRS_ADC_PKT_SAMPLES                 = 0x0124
WD2_REG_MAX_TDC_PKT_SAMPLES                     = 0x0128
WD2_REG_MAX_TRG_PKT_SAMPLES                     = 0x012C
WD2_REG_MAX_SCL_PKT_SAMPLES                     = 0x0130
WD2_REG_CLK_CTRL_MOD_FLAG                       = 0x0134
WD2_REG_DRS_MOD_FLAG                            = 0x0138
WD2_REG_COM_PLD_SIZE_MOD_FLAG                   = 0x013C
WD2_REG_ADC_SAMPLE_DIV_MOD_FLAG                 = 0x0140
WD2_REG_DAC_0_1_MOD_FLAG                        = 0x0144
WD2_REG_DAC_2_MOD_FLAG                          = 0x0148
WD2_REG_FE_0_15_MOD_FLAG                        = 0x014C
WD2_REG_HV_U_TARGET_0_7_MOD_FLAG                = 0x0150
WD2_REG_HV_U_TARGET_8_15_MOD_FLAG               = 0x0154
WD2_REG_HV_MOD_FLAG                             = 0x0158
WD2_REG_LMK_0_7_MOD_FLAG                        = 0x015C
WD2_REG_LMK_8_15_MOD_FLAG                       = 0x0160

#
# Bit Positions
#

# ****** Control Register 0 [0x1000]: WDB_LOC - Location where the WD2 is plugged in (Default: 0xFFFFFFFF) ******

# CRATE_ID - ID of the crate where the current board is plugged in
WD2_CRATE_ID_REG                         =                   WD2_REG_WDB_LOC
WD2_CRATE_ID_MASK                        =                        0x00FF0000
WD2_CRATE_ID_OFS                         =                                16

# SLOT_ID - ID of the slot where the current board is plugged in
WD2_SLOT_ID_REG                          =                   WD2_REG_WDB_LOC
WD2_SLOT_ID_MASK                         =                        0x000000FF
WD2_SLOT_ID_OFS                          =                                 0



# ****** Control Register 1 [0x1004]: CTRL - DAQ control register (Default: 0x122D0780) ******

# VALID_DELAY_ADC - Delay of the data valid at the ISERDES of the ADCs (delay = value + 1)
WD2_VALID_DELAY_ADC_REG                  =                      WD2_REG_CTRL
WD2_VALID_DELAY_ADC_MASK                 =                        0x3F000000
WD2_VALID_DELAY_ADC_OFS                  =                                24

# DAQ_DATA_PHASE - Phase step setting of the PLL generating the common DAQ clock
WD2_DAQ_DATA_PHASE_REG                   =                      WD2_REG_CTRL
WD2_DAQ_DATA_PHASE_MASK                  =                        0x00FF0000
WD2_DAQ_DATA_PHASE_OFS                   =                                16

# FE_POWER - Frontend Power (0=Power OFF, 1=Power ON)
WD2_FE_POWER_REG                         =                      WD2_REG_CTRL
WD2_FE_POWER_MASK                        =                        0x00000800
WD2_FE_POWER_OFS                         =                                11

# DRS_CLR_RSR_AFTER_RO - Clear the read shift register (remove the token) after each readout
WD2_DRS_CLR_RSR_AFTER_RO_REG             =                      WD2_REG_CTRL
WD2_DRS_CLR_RSR_AFTER_RO_MASK            =                        0x00000400
WD2_DRS_CLR_RSR_AFTER_RO_OFS             =                                10

# COMP_POWER_EN - Comparator power enable
WD2_COMP_POWER_EN_REG                    =                      WD2_REG_CTRL
WD2_COMP_POWER_EN_MASK                   =                        0x00000200
WD2_COMP_POWER_EN_OFS                    =                                 9

# DRS_READOUT_MODE - 0:start from first bin, 1:start from domino stop
WD2_DRS_READOUT_MODE_REG                 =                      WD2_REG_CTRL
WD2_DRS_READOUT_MODE_MASK                =                        0x00000100
WD2_DRS_READOUT_MODE_OFS                 =                                 8

# DRS_WAVE_CONTINUOUS - 0:stop domino wave during readout, 1:keep it running
WD2_DRS_WAVE_CONTINUOUS_REG              =                      WD2_REG_CTRL
WD2_DRS_WAVE_CONTINUOUS_MASK             =                        0x00000080
WD2_DRS_WAVE_CONTINUOUS_OFS              =                                 7

# DRS_CONFIGURE - write a "1" to trigger the DRS chip register configuration
WD2_DRS_CONFIGURE_REG                    =                      WD2_REG_CTRL
WD2_DRS_CONFIGURE_MASK                   =                        0x00000040
WD2_DRS_CONFIGURE_OFS                    =                                 6

# DAQ_SOFT_TRIGGER - write a "1" to stop the DRS chip & read the data to RAM
WD2_DAQ_SOFT_TRIGGER_REG                 =                      WD2_REG_CTRL
WD2_DAQ_SOFT_TRIGGER_MASK                =                        0x00000020
WD2_DAQ_SOFT_TRIGGER_OFS                 =                                 5

# DAQ_AUTO - Auto-Trigger readout state machine every 0.5s if no other trigger (like "auto" acquisition on scope)
WD2_DAQ_AUTO_REG                         =                      WD2_REG_CTRL
WD2_DAQ_AUTO_MASK                        =                        0x00000004
WD2_DAQ_AUTO_OFS                         =                                 2

# DAQ_NORMAL - Restart readout state machine automatically after readout (like "normal" acquisition on scope)
WD2_DAQ_NORMAL_REG                       =                      WD2_REG_CTRL
WD2_DAQ_NORMAL_MASK                      =                        0x00000002
WD2_DAQ_NORMAL_OFS                       =                                 1

# DAQ_SINGLE - Start readout state machine automatically and stop after readout (like "single" acquisition on scope)
WD2_DAQ_SINGLE_REG                       =                      WD2_REG_CTRL
WD2_DAQ_SINGLE_MASK                      =                        0x00000001
WD2_DAQ_SINGLE_OFS                       =                                 0



# ****** Control Register 2 [0x1008]: CAL_CTRL - Clock and Calibration Control (Default: 0x00000000) ******

# ADC_CAL_PATTERN_EN - Enable ADC calibration pattern
WD2_ADC_CAL_PATTERN_EN_REG               =                  WD2_REG_CAL_CTRL
WD2_ADC_CAL_PATTERN_EN_MASK              =                        0x01000000
WD2_ADC_CAL_PATTERN_EN_OFS               =                                24

# DRS_0_TIMING_REF_SEL - Select timing reference signal for DRS 0: 0 = oscillator / 1 = LMK (CAL_CTRL_A)
WD2_DRS_0_TIMING_REF_SEL_REG             =                  WD2_REG_CAL_CTRL
WD2_DRS_0_TIMING_REF_SEL_MASK            =                        0x00000008
WD2_DRS_0_TIMING_REF_SEL_OFS             =                                 3

# DRS_1_TIMING_REF_SEL - Select timing reference signal for DRS 1: 0 = oscillator / 1 = LMK  (CAL_CTRL_B)
WD2_DRS_1_TIMING_REF_SEL_REG             =                  WD2_REG_CAL_CTRL
WD2_DRS_1_TIMING_REF_SEL_MASK            =                        0x00000004
WD2_DRS_1_TIMING_REF_SEL_OFS             =                                 2

# CALIB_BUFFER_EN - Enable buffers driving the calib. signal to the frontend MUX (BUFFER_CTRL)
WD2_CALIB_BUFFER_EN_REG                  =                  WD2_REG_CAL_CTRL
WD2_CALIB_BUFFER_EN_MASK                 =                        0x00000002
WD2_CALIB_BUFFER_EN_OFS                  =                                 1

# TIMING_CALIB_SIGNAL_EN - switch on (1) / off (0) 100 MHz calibration signal for DRS chip (TCA_CTRL)
WD2_TIMING_CALIB_SIGNAL_EN_REG           =                  WD2_REG_CAL_CTRL
WD2_TIMING_CALIB_SIGNAL_EN_MASK          =                        0x00000001
WD2_TIMING_CALIB_SIGNAL_EN_OFS           =                                 0



# ****** Control Register 3 [0x100C]: CLK_CTRL - Clock Control (Default: 0x00025050) ******

# TRIG_DAQ_CLK_CAL_CHK - Trigger DAQ clock calibration check
WD2_TRIG_DAQ_CLK_CAL_CHK_REG             =                  WD2_REG_CLK_CTRL
WD2_TRIG_DAQ_CLK_CAL_CHK_MASK            =                        0x01000000
WD2_TRIG_DAQ_CLK_CAL_CHK_OFS             =                                24

# DAQ_CLK_SRC_SEL - DAQ clock source select: 0 = DCB clock / 1 = on board oscillator (CLK_SEL)
WD2_DAQ_CLK_SRC_SEL_REG                  =                  WD2_REG_CLK_CTRL
WD2_DAQ_CLK_SRC_SEL_MASK                 =                        0x00020000
WD2_DAQ_CLK_SRC_SEL_OFS                  =                                17

# EXT_CLK_IN_SEL - External clk input select: 0 = backplane / 1 = MCX connector (CLK_SEL_EXT)
WD2_EXT_CLK_IN_SEL_REG                   =                  WD2_REG_CLK_CTRL
WD2_EXT_CLK_IN_SEL_MASK                  =                        0x00010000
WD2_EXT_CLK_IN_SEL_OFS                   =                                16

# EXT_CLK_FREQ - External clock frequency (MCX or backplane) in MHz
WD2_EXT_CLK_FREQ_REG                     =                  WD2_REG_CLK_CTRL
WD2_EXT_CLK_FREQ_MASK                    =                        0x0000FF00
WD2_EXT_CLK_FREQ_OFS                     =                                 8

# LOCAL_CLK_FREQ - Local (on board) oscillator frequency in MHz
WD2_LOCAL_CLK_FREQ_REG                   =                  WD2_REG_CLK_CTRL
WD2_LOCAL_CLK_FREQ_MASK                  =                        0x000000FF
WD2_LOCAL_CLK_FREQ_OFS                   =                                 0



# ****** Control Register 4 [0x1010]: DRS_CTRL - DRS4 Control and Configuration Registers (Default: 0x00FFFFFF) ******

# DRS_WSRLOOP - Internally Connect WSRIN to WSROUT (if set to 1)
WD2_DRS_WSRLOOP_REG                      =                  WD2_REG_DRS_CTRL
WD2_DRS_WSRLOOP_MASK                     =                        0x00040000
WD2_DRS_WSRLOOP_OFS                      =                                18

# DRS_PLLEN - Internal PLL Enable (0 = disable, 1 = enable)
WD2_DRS_PLLEN_REG                        =                  WD2_REG_DRS_CTRL
WD2_DRS_PLLEN_MASK                       =                        0x00020000
WD2_DRS_PLLEN_OFS                        =                                17

# DRS_DMODE - Domino Mode Control (0 = single shot, 1 = continuous)
WD2_DRS_DMODE_REG                        =                  WD2_REG_DRS_CTRL
WD2_DRS_DMODE_MASK                       =                        0x00010000
WD2_DRS_DMODE_OFS                        =                                16

# DRS_WSR - DRS4 Write Shift Register (0xD)
WD2_DRS_WSR_REG                          =                  WD2_REG_DRS_CTRL
WD2_DRS_WSR_MASK                         =                        0x0000FF00
WD2_DRS_WSR_OFS                          =                                 8

# DRS_WCR - DRS4 Write Configuration Register (0xE)
WD2_DRS_WCR_REG                          =                  WD2_REG_DRS_CTRL
WD2_DRS_WCR_MASK                         =                        0x000000FF
WD2_DRS_WCR_OFS                          =                                 0



# ****** Control Register 5 [0x1014]: COM_CTRL - Communication Control Register (Default: 0x02000753) ******

# DCB_SERDES_TRAIN - Enable training pattern for DCB SERDES connection
WD2_DCB_SERDES_TRAIN_REG                 =                  WD2_REG_COM_CTRL
WD2_DCB_SERDES_TRAIN_MASK                =                        0x80000000
WD2_DCB_SERDES_TRAIN_OFS                 =                                31

# TCB_SERDES_TRAIN - Enable training pattern for TCB SERDES connection
WD2_TCB_SERDES_TRAIN_REG                 =                  WD2_REG_COM_CTRL
WD2_TCB_SERDES_TRAIN_MASK                =                        0x40000000
WD2_TCB_SERDES_TRAIN_OFS                 =                                30

# TRG_TX_EN - enable transmission of advanced trigger output data
WD2_TRG_TX_EN_REG                        =                  WD2_REG_COM_CTRL
WD2_TRG_TX_EN_MASK                       =                        0x08000000
WD2_TRG_TX_EN_OFS                        =                                27

# SCL_TX_EN - Enable transmission of scaler data
WD2_SCL_TX_EN_REG                        =                  WD2_REG_COM_CTRL
WD2_SCL_TX_EN_MASK                       =                        0x04000000
WD2_SCL_TX_EN_OFS                        =                                26

# SERDES_COM_EN - Enable SERDES communication to backplane
WD2_SERDES_COM_EN_REG                    =                  WD2_REG_COM_CTRL
WD2_SERDES_COM_EN_MASK                   =                        0x02000000
WD2_SERDES_COM_EN_OFS                    =                                25

# ETH_COM_EN - Enable ethernet communication
WD2_ETH_COM_EN_REG                       =                  WD2_REG_COM_CTRL
WD2_ETH_COM_EN_MASK                      =                        0x01000000
WD2_ETH_COM_EN_OFS                       =                                24

# INTER_PKG_DELAY - Delay between transmission of two UDP packages in 8ns steps
WD2_INTER_PKG_DELAY_REG                  =                  WD2_REG_COM_CTRL
WD2_INTER_PKG_DELAY_MASK                 =                        0x00FFFFFF
WD2_INTER_PKG_DELAY_OFS                  =                                 0



# ****** Control Register 6 [0x1018]: COM_PLD_SIZE - Maximum Payload Size (Default: 0x000005C0) ******

# FIRST_PKG_DLY - Delay of first data packet of an event (resolution 1.6us)
WD2_FIRST_PKG_DLY_REG                    =              WD2_REG_COM_PLD_SIZE
WD2_FIRST_PKG_DLY_MASK                   =                        0xFFFC0000
WD2_FIRST_PKG_DLY_OFS                    =                                18

# COM_PLD_SIZE - Maximum number of UDP payload bytes to transmit (must be a multiple of 6 with range 6 to 8892)
WD2_COM_PLD_SIZE_REG                     =              WD2_REG_COM_PLD_SIZE
WD2_COM_PLD_SIZE_MASK                    =                        0x0003FFFF
WD2_COM_PLD_SIZE_OFS                     =                                 0



# ****** Control Register 7 [0x101C]: DRS_CH_TX_EN - DRS Channel Transmission Enable Register (Default: 0x0000FFFF) ******

# DRS_CH_TX_EN - DRS channel transmission enable [Ch17:Ch0] - (CH17:CH16 = timing channels)
WD2_DRS_CH_TX_EN_REG                     =              WD2_REG_DRS_CH_TX_EN
WD2_DRS_CH_TX_EN_MASK                    =                        0x0003FFFF
WD2_DRS_CH_TX_EN_OFS                     =                                 0



# ****** Control Register 8 [0x1020]: ADC_CH_TX_EN - ADC Channel Transmission Enable Register (Default: 0x00000000) ******

# ADC_CH_TX_EN - ADC channel transmission enable [Ch15:Ch0]
WD2_ADC_CH_TX_EN_REG                     =              WD2_REG_ADC_CH_TX_EN
WD2_ADC_CH_TX_EN_MASK                    =                        0x0000FFFF
WD2_ADC_CH_TX_EN_OFS                     =                                 0



# ****** Control Register 9 [0x1024]: TDC_CH_TX_EN - TDC Channel Transmission Enable Register (Default: 0x00000000) ******

# TDC_CH_TX_EN - TDC channel transmission enable [Ch15:Ch0]
WD2_TDC_CH_TX_EN_REG                     =              WD2_REG_TDC_CH_TX_EN
WD2_TDC_CH_TX_EN_MASK                    =                        0x0000FFFF
WD2_TDC_CH_TX_EN_OFS                     =                                 0



# ****** Control Register 10 [0x1028]: DRS_TX_SAMPLES - DRS Samples to transmit (Default: 0x00000400) ******

# DRS_TX_SAMPLES - Number of DRS samples to transmit per channel (must be an even value with range 2 to 1024)
WD2_DRS_TX_SAMPLES_REG                   =            WD2_REG_DRS_TX_SAMPLES
WD2_DRS_TX_SAMPLES_MASK                  =                        0x000007FF
WD2_DRS_TX_SAMPLES_OFS                   =                                 0



# ****** Control Register 11 [0x102C]: ADC_TX_SAMPLES - ADC Samples to transmit (Default: 0x00000800) ******

# ADC_TX_SAMPLES - Number of ADC samples to transmit per channel (must be an even value with range 2 to 2048)
WD2_ADC_TX_SAMPLES_REG                   =            WD2_REG_ADC_TX_SAMPLES
WD2_ADC_TX_SAMPLES_MASK                  =                        0x00000FFF
WD2_ADC_TX_SAMPLES_OFS                   =                                 0



# ****** Control Register 12 [0x1030]: TDC_TX_SAMPLES - TDC Samples to transmit (Default: 0x00001000) ******

# TDC_TX_SAMPLES - Number of TDC samples to transmit per channel (must be a multiple of 8 with range 16 to 4096)
WD2_TDC_TX_SAMPLES_REG                   =            WD2_REG_TDC_TX_SAMPLES
WD2_TDC_TX_SAMPLES_MASK                  =                        0x00001FFF
WD2_TDC_TX_SAMPLES_OFS                   =                                 0



# ****** Control Register 13 [0x1034]: TRG_TX_SAMPLES - TRG Samples to transmit (Default: 0x00000200) ******

# TRG_TX_SAMPLES - Number of advanced trigger output samples to transmit (range 1 to 512)
WD2_TRG_TX_SAMPLES_REG                   =            WD2_REG_TRG_TX_SAMPLES
WD2_TRG_TX_SAMPLES_MASK                  =                        0x000003FF
WD2_TRG_TX_SAMPLES_OFS                   =                                 0



# ****** Control Register 14 [0x1038]: ADC_SAMPLE_DIV - ADC Downsampling Divider (Default: 0x00000001) ******

# ADC_SAMPLE_DIV - Only store every n-th sample to buffer
WD2_ADC_SAMPLE_DIV_REG                   =            WD2_REG_ADC_SAMPLE_DIV
WD2_ADC_SAMPLE_DIV_MASK                  =                        0x000000FF
WD2_ADC_SAMPLE_DIV_OFS                   =                                 0



# ****** Control Register 15 [0x103C]: ZERO_SUPR - Zero Suppression Configuration Register (Default: 0x00000080) ******

# ZERO_SUPR_EN - Enable zero suppression for data transmission (only transmit channels that triggered)
WD2_ZERO_SUPR_EN_REG                     =                 WD2_REG_ZERO_SUPR
WD2_ZERO_SUPR_EN_MASK                    =                        0x00000100
WD2_ZERO_SUPR_EN_OFS                     =                                 8

# ZERO_SUPR_WINDOW - Zero suppression time window in DAQ clock ticks (channel polarity defined in TRG_SRC_POL)
WD2_ZERO_SUPR_WINDOW_REG                 =                 WD2_REG_ZERO_SUPR
WD2_ZERO_SUPR_WINDOW_MASK                =                        0x000000FF
WD2_ZERO_SUPR_WINDOW_OFS                 =                                 0



# ****** Control Register 16 [0x1040]: RST - Reset bits for specific firmwar units (Default: 0x00000000) ******

# DAQ_PLL_RST - Reset the PLL for the DAQ clock
WD2_DAQ_PLL_RST_REG                      =                       WD2_REG_RST
WD2_DAQ_PLL_RST_MASK                     =                        0x00004000
WD2_DAQ_PLL_RST_OFS                      =                                14

# DCB_OSERDES_PLL_RST - Reset the PLL of the DCB OSERDES
WD2_DCB_OSERDES_PLL_RST_REG              =                       WD2_REG_RST
WD2_DCB_OSERDES_PLL_RST_MASK             =                        0x00002000
WD2_DCB_OSERDES_PLL_RST_OFS              =                                13

# TCB_OSERDES_PLL_RST - Reset the PLL of the TCB OSERDES
WD2_TCB_OSERDES_PLL_RST_REG              =                       WD2_REG_RST
WD2_TCB_OSERDES_PLL_RST_MASK             =                        0x00001000
WD2_TCB_OSERDES_PLL_RST_OFS              =                                12

# DCB_OSERDES_IF_RST - Reset the DCB OSERDES interface
WD2_DCB_OSERDES_IF_RST_REG               =                       WD2_REG_RST
WD2_DCB_OSERDES_IF_RST_MASK              =                        0x00000800
WD2_DCB_OSERDES_IF_RST_OFS               =                                11

# TCB_OSERDES_IF_RST - Reset the TCB OSERDES interface
WD2_TCB_OSERDES_IF_RST_REG               =                       WD2_REG_RST
WD2_TCB_OSERDES_IF_RST_MASK              =                        0x00000400
WD2_TCB_OSERDES_IF_RST_OFS               =                                10

# SCALER_RST - Reset all scalers
WD2_SCALER_RST_REG                       =                       WD2_REG_RST
WD2_SCALER_RST_MASK                      =                        0x00000200
WD2_SCALER_RST_OFS                       =                                 9

# TRB_PARITY_ERROR_COUNT_RST - Reset the parity error counter of the trigger info serial connection
WD2_TRB_PARITY_ERROR_COUNT_RST_REG       =                       WD2_REG_RST
WD2_TRB_PARITY_ERROR_COUNT_RST_MASK      =                        0x00000100
WD2_TRB_PARITY_ERROR_COUNT_RST_OFS       =                                 8

# LMK_SYNC_LOCAL - Control LMK SYNC signal from FPGA: 0 = run / 1 = sync
WD2_LMK_SYNC_LOCAL_REG                   =                       WD2_REG_RST
WD2_LMK_SYNC_LOCAL_MASK                  =                        0x00000080
WD2_LMK_SYNC_LOCAL_OFS                   =                                 7

# ADC_RST - ADC reset
WD2_ADC_RST_REG                          =                       WD2_REG_RST
WD2_ADC_RST_MASK                         =                        0x00000040
WD2_ADC_RST_OFS                          =                                 6

# ADC_IF_RST - Reset the ADC interface
WD2_ADC_IF_RST_REG                       =                       WD2_REG_RST
WD2_ADC_IF_RST_MASK                      =                        0x00000020
WD2_ADC_IF_RST_OFS                       =                                 5

# DATA_LINK_IF_RST - Reset of the interface between packager and Ethernet/SERDES interface
WD2_DATA_LINK_IF_RST_REG                 =                       WD2_REG_RST
WD2_DATA_LINK_IF_RST_MASK                =                        0x00000010
WD2_DATA_LINK_IF_RST_OFS                 =                                 4

# WD_PKGR_RST - WaveDream packager reset
WD2_WD_PKGR_RST_REG                      =                       WD2_REG_RST
WD2_WD_PKGR_RST_MASK                     =                        0x00000008
WD2_WD_PKGR_RST_OFS                      =                                 3

# EVENT_COUNTER_RST - Event Counter Reset
WD2_EVENT_COUNTER_RST_REG                =                       WD2_REG_RST
WD2_EVENT_COUNTER_RST_MASK               =                        0x00000004
WD2_EVENT_COUNTER_RST_OFS                =                                 2

# DRS_CTRL_FSM_RST - DRS control FSM reset
WD2_DRS_CTRL_FSM_RST_REG                 =                       WD2_REG_RST
WD2_DRS_CTRL_FSM_RST_MASK                =                        0x00000002
WD2_DRS_CTRL_FSM_RST_OFS                 =                                 1

# RECONFIGURE_FPGA - Initiate FPGA Reconfiguration
WD2_RECONFIGURE_FPGA_REG                 =                       WD2_REG_RST
WD2_RECONFIGURE_FPGA_MASK                =                        0x00000001
WD2_RECONFIGURE_FPGA_OFS                 =                                 0



# ****** Control Register 17 [0x1044]: APLY_CFG - Apply settings from regsiter bank to hardware units (Default: 0x00000000) ******

# APPLY_SETTINGS_ADC_SAMPLE_DIV - Apply configuration from register bank to ADC sampling frequency (auto update)
WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_REG    =                  WD2_REG_APLY_CFG
WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_MASK   =                        0x00000100
WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_OFS    =                                 8

# APPLY_SETTINGS_MAX_PLD_SIZE - Apply configuration from register bank to max samples per packet (auto update)
WD2_APPLY_SETTINGS_MAX_PLD_SIZE_REG      =                  WD2_REG_APLY_CFG
WD2_APPLY_SETTINGS_MAX_PLD_SIZE_MASK     =                        0x00000080
WD2_APPLY_SETTINGS_MAX_PLD_SIZE_OFS      =                                 7

# APPLY_SETTINGS_HV - Apply configuration from register bank to HV (auto update)
WD2_APPLY_SETTINGS_HV_REG                =                  WD2_REG_APLY_CFG
WD2_APPLY_SETTINGS_HV_MASK               =                        0x00000040
WD2_APPLY_SETTINGS_HV_OFS                =                                 6

# APPLY_SETTINGS_DRS - Apply configuration from register bank to DRS chip (auto update)
WD2_APPLY_SETTINGS_DRS_REG               =                  WD2_REG_APLY_CFG
WD2_APPLY_SETTINGS_DRS_MASK              =                        0x00000020
WD2_APPLY_SETTINGS_DRS_OFS               =                                 5

# APPLY_SETTINGS_DAC - Apply configuration from register bank to DAC (auto update)
WD2_APPLY_SETTINGS_DAC_REG               =                  WD2_REG_APLY_CFG
WD2_APPLY_SETTINGS_DAC_MASK              =                        0x00000010
WD2_APPLY_SETTINGS_DAC_OFS               =                                 4

# APPLY_SETTINGS_FRONTEND - Apply configuration from register bank to frontend (auto update)
WD2_APPLY_SETTINGS_FRONTEND_REG          =                  WD2_REG_APLY_CFG
WD2_APPLY_SETTINGS_FRONTEND_MASK         =                        0x00000008
WD2_APPLY_SETTINGS_FRONTEND_OFS          =                                 3

# APPLY_SETTINGS_CTRL - Apply configuration from register bank control register
WD2_APPLY_SETTINGS_CTRL_REG              =                  WD2_REG_APLY_CFG
WD2_APPLY_SETTINGS_CTRL_MASK             =                        0x00000004
WD2_APPLY_SETTINGS_CTRL_OFS              =                                 2

# APPLY_SETTINGS_ADC - Apply configuration from register bank to ADC
WD2_APPLY_SETTINGS_ADC_REG               =                  WD2_REG_APLY_CFG
WD2_APPLY_SETTINGS_ADC_MASK              =                        0x00000002
WD2_APPLY_SETTINGS_ADC_OFS               =                                 1

# APPLY_SETTINGS_LMK - Apply configuration from regsiter bank to LMK
WD2_APPLY_SETTINGS_LMK_REG               =                  WD2_REG_APLY_CFG
WD2_APPLY_SETTINGS_LMK_MASK              =                        0x00000001
WD2_APPLY_SETTINGS_LMK_OFS               =                                 0



# ****** Control Register 18 [0x1048]: DAC0_A_B - DAC0 values for Channel A and B (Default: 0x9EC045A0) ******

# DAC0_CH_A - Set DAC0 channel A (ROFS) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
WD2_DAC0_CH_A_REG                        =                  WD2_REG_DAC0_A_B
WD2_DAC0_CH_A_MASK                       =                        0xFFFF0000
WD2_DAC0_CH_A_OFS                        =                                16

# DAC0_CH_B - Set DAC0 channel B (OFS) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (+/- 0.625V)
WD2_DAC0_CH_B_REG                        =                  WD2_REG_DAC0_A_B
WD2_DAC0_CH_B_MASK                       =                        0x0000FFFF
WD2_DAC0_CH_B_OFS                        =                                 0



# ****** Control Register 19 [0x104C]: DAC0_C_D - DAC0 values for Channel C and D (Default: 0x828F0000) ******

# DAC0_CH_C - Set DAC0 channel C (CAL_DC) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (+/- 0.625V)
WD2_DAC0_CH_C_REG                        =                  WD2_REG_DAC0_C_D
WD2_DAC0_CH_C_MASK                       =                        0xFFFF0000
WD2_DAC0_CH_C_OFS                        =                                16

# DAC0_CH_D - Set DAC0 channel D (PULSE_AMP) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..1V)
WD2_DAC0_CH_D_REG                        =                  WD2_REG_DAC0_C_D
WD2_DAC0_CH_D_MASK                       =                        0x0000FFFF
WD2_DAC0_CH_D_OFS                        =                                 0



# ****** Control Register 20 [0x1050]: DAC0_E_F - DAC0 values for Channel E and F (Default: 0x0000FFFF) ******

# DAC0_CH_E - Set DAC0 channel E (PZC_LEVEL) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (+/- 2.5V)
WD2_DAC0_CH_E_REG                        =                  WD2_REG_DAC0_E_F
WD2_DAC0_CH_E_MASK                       =                        0xFFFF0000
WD2_DAC0_CH_E_OFS                        =                                16

# DAC0_CH_F - Set DAC0 channel F (DAC_REF_A) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
WD2_DAC0_CH_F_REG                        =                  WD2_REG_DAC0_E_F
WD2_DAC0_CH_F_MASK                       =                        0x0000FFFF
WD2_DAC0_CH_F_OFS                        =                                 0



# ****** Control Register 21 [0x1054]: DAC0_G_H - DAC0 values for Channel G and H (Default: 0x000047B0) ******

# DAC0_CH_G - Set DAC0 channel G (RESERVED) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
WD2_DAC0_CH_G_REG                        =                  WD2_REG_DAC0_G_H
WD2_DAC0_CH_G_MASK                       =                        0xFFFF0000
WD2_DAC0_CH_G_OFS                        =                                16

# DAC0_CH_H - Set DAC0 channel H (BIAS) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
WD2_DAC0_CH_H_REG                        =                  WD2_REG_DAC0_G_H
WD2_DAC0_CH_H_MASK                       =                        0x0000FFFF
WD2_DAC0_CH_H_OFS                        =                                 0



# ****** Control Register 22 [0x1058]: DAC1_A_B - DAC1 values for Channel A and B (Default: 0x57105710) ******

# DAC1_CH_A - Set DAC1 channel A (TLEVEL_0) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
WD2_DAC1_CH_A_REG                        =                  WD2_REG_DAC1_A_B
WD2_DAC1_CH_A_MASK                       =                        0xFFFF0000
WD2_DAC1_CH_A_OFS                        =                                16

# DAC1_CH_B - Set DAC1 channel B (TLEVEL_1) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
WD2_DAC1_CH_B_REG                        =                  WD2_REG_DAC1_A_B
WD2_DAC1_CH_B_MASK                       =                        0x0000FFFF
WD2_DAC1_CH_B_OFS                        =                                 0



# ****** Control Register 23 [0x105C]: DAC1_C_D - DAC1 values for Channel C and D (Default: 0x57105710) ******

# DAC1_CH_C - Set DAC1 channel C (TLEVEL_2) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
WD2_DAC1_CH_C_REG                        =                  WD2_REG_DAC1_C_D
WD2_DAC1_CH_C_MASK                       =                        0xFFFF0000
WD2_DAC1_CH_C_OFS                        =                                16

# DAC1_CH_D - Set DAC1 channel D (TLEVEL_3) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
WD2_DAC1_CH_D_REG                        =                  WD2_REG_DAC1_C_D
WD2_DAC1_CH_D_MASK                       =                        0x0000FFFF
WD2_DAC1_CH_D_OFS                        =                                 0



# ****** Control Register 24 [0x1060]: DAC1_E_F - DAC1 values for Channel E and F (Default: 0x57105710) ******

# DAC1_CH_E - Set DAC1 channel E (TLEVEL_4) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
WD2_DAC1_CH_E_REG                        =                  WD2_REG_DAC1_E_F
WD2_DAC1_CH_E_MASK                       =                        0xFFFF0000
WD2_DAC1_CH_E_OFS                        =                                16

# DAC1_CH_F - Set DAC1 channel F (TLEVEL_5) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
WD2_DAC1_CH_F_REG                        =                  WD2_REG_DAC1_E_F
WD2_DAC1_CH_F_MASK                       =                        0x0000FFFF
WD2_DAC1_CH_F_OFS                        =                                 0



# ****** Control Register 25 [0x1064]: DAC1_G_H - DAC1 values for Channel G and H (Default: 0x57105710) ******

# DAC1_CH_G - Set DAC1 channel G (TLEVEL_6) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
WD2_DAC1_CH_G_REG                        =                  WD2_REG_DAC1_G_H
WD2_DAC1_CH_G_MASK                       =                        0xFFFF0000
WD2_DAC1_CH_G_OFS                        =                                16

# DAC1_CH_H - Set DAC1 channel H (TLEVEL_7) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
WD2_DAC1_CH_H_REG                        =                  WD2_REG_DAC1_G_H
WD2_DAC1_CH_H_MASK                       =                        0x0000FFFF
WD2_DAC1_CH_H_OFS                        =                                 0



# ****** Control Register 26 [0x1068]: DAC2_A_B - DAC2 values for Channel A and B (Default: 0x57105710) ******

# DAC2_CH_A - Set DAC2 channel A (TLEVEL_8) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
WD2_DAC2_CH_A_REG                        =                  WD2_REG_DAC2_A_B
WD2_DAC2_CH_A_MASK                       =                        0xFFFF0000
WD2_DAC2_CH_A_OFS                        =                                16

# DAC2_CH_B - Set DAC2 channel B (TLEVEL_9) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
WD2_DAC2_CH_B_REG                        =                  WD2_REG_DAC2_A_B
WD2_DAC2_CH_B_MASK                       =                        0x0000FFFF
WD2_DAC2_CH_B_OFS                        =                                 0



# ****** Control Register 27 [0x106C]: DAC2_C_D - DAC2 values for Channel C and D (Default: 0x57105710) ******

# DAC2_CH_C - Set DAC2 channel C (TLEVEL_10) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
WD2_DAC2_CH_C_REG                        =                  WD2_REG_DAC2_C_D
WD2_DAC2_CH_C_MASK                       =                        0xFFFF0000
WD2_DAC2_CH_C_OFS                        =                                16

# DAC2_CH_D - Set DAC2 channel D (TLEVEL_11) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
WD2_DAC2_CH_D_REG                        =                  WD2_REG_DAC2_C_D
WD2_DAC2_CH_D_MASK                       =                        0x0000FFFF
WD2_DAC2_CH_D_OFS                        =                                 0



# ****** Control Register 28 [0x1070]: DAC2_E_F - DAC2 values for Channel E and F (Default: 0x57105710) ******

# DAC2_CH_E - Set DAC2 channel E (TLEVEL_12) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
WD2_DAC2_CH_E_REG                        =                  WD2_REG_DAC2_E_F
WD2_DAC2_CH_E_MASK                       =                        0xFFFF0000
WD2_DAC2_CH_E_OFS                        =                                16

# DAC2_CH_F - Set DAC2 channel F (TLEVEL_13) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
WD2_DAC2_CH_F_REG                        =                  WD2_REG_DAC2_E_F
WD2_DAC2_CH_F_MASK                       =                        0x0000FFFF
WD2_DAC2_CH_F_OFS                        =                                 0



# ****** Control Register 29 [0x1074]: DAC2_G_H - DAC2 values for Channel G and H (Default: 0x57105710) ******

# DAC2_CH_G - Set DAC2 channel G (TLEVEL_14) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
WD2_DAC2_CH_G_REG                        =                  WD2_REG_DAC2_G_H
WD2_DAC2_CH_G_MASK                       =                        0xFFFF0000
WD2_DAC2_CH_G_OFS                        =                                16

# DAC2_CH_H - Set DAC2 channel H (TLEVEL_15) (12 bit MSBs: DAC value, 4 bit LSBs: don't care) (0..2.5V)
WD2_DAC2_CH_H_REG                        =                  WD2_REG_DAC2_G_H
WD2_DAC2_CH_H_MASK                       =                        0x0000FFFF
WD2_DAC2_CH_H_OFS                        =                                 0



# ****** Control Register 30 [0x1078]: FE_CFG_0_1 - Frontend Settings for Channel 0 and 1 (Default: 0x00020002) ******

# FE0_PZC_EN - Frontend channel 0 PZC (pole-zero cancellation) enable (ACDC)
WD2_FE0_PZC_EN_REG                       =                WD2_REG_FE_CFG_0_1
WD2_FE0_PZC_EN_MASK                      =                        0x01000000
WD2_FE0_PZC_EN_OFS                       =                                24

# FE0_AMPLIFIER2_COMP_EN - Frontend channel 0 amplifier 2 compensation enable (COMP2)
WD2_FE0_AMPLIFIER2_COMP_EN_REG           =                WD2_REG_FE_CFG_0_1
WD2_FE0_AMPLIFIER2_COMP_EN_MASK          =                        0x00800000
WD2_FE0_AMPLIFIER2_COMP_EN_OFS           =                                23

# FE0_AMPLIFIER2_EN - Frontend channel 0 amplifier 2 enable (gain: 10) (OP2)
WD2_FE0_AMPLIFIER2_EN_REG                =                WD2_REG_FE_CFG_0_1
WD2_FE0_AMPLIFIER2_EN_MASK               =                        0x00400000
WD2_FE0_AMPLIFIER2_EN_OFS                =                                22

# FE0_AMPLIFIER1_COMP_EN - Frontend channel 0 amplifier 1 compensation enable (COMP1)
WD2_FE0_AMPLIFIER1_COMP_EN_REG           =                WD2_REG_FE_CFG_0_1
WD2_FE0_AMPLIFIER1_COMP_EN_MASK          =                        0x00200000
WD2_FE0_AMPLIFIER1_COMP_EN_OFS           =                                21

# FE0_AMPLIFIER1_EN - Frontend channel 0 amplifier 1 enable (gain: 10) (OP1)
WD2_FE0_AMPLIFIER1_EN_REG                =                WD2_REG_FE_CFG_0_1
WD2_FE0_AMPLIFIER1_EN_MASK               =                        0x00100000
WD2_FE0_AMPLIFIER1_EN_OFS                =                                20

# FE0_ATTENUATION - Frontend channel 0 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
WD2_FE0_ATTENUATION_REG                  =                WD2_REG_FE_CFG_0_1
WD2_FE0_ATTENUATION_MASK                 =                        0x000C0000
WD2_FE0_ATTENUATION_OFS                  =                                18

# FE0_MUX - Frontend channel 0 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
WD2_FE0_MUX_REG                          =                WD2_REG_FE_CFG_0_1
WD2_FE0_MUX_MASK                         =                        0x00030000
WD2_FE0_MUX_OFS                          =                                16

# FE1_PZC_EN - Frontend channel 1 PZC (pole-zero cancellation) enable (ACDC)
WD2_FE1_PZC_EN_REG                       =                WD2_REG_FE_CFG_0_1
WD2_FE1_PZC_EN_MASK                      =                        0x00000100
WD2_FE1_PZC_EN_OFS                       =                                 8

# FE1_AMPLIFIER2_COMP_EN - Frontend channel 1 amplifier 2 compensation enable (COMP2)
WD2_FE1_AMPLIFIER2_COMP_EN_REG           =                WD2_REG_FE_CFG_0_1
WD2_FE1_AMPLIFIER2_COMP_EN_MASK          =                        0x00000080
WD2_FE1_AMPLIFIER2_COMP_EN_OFS           =                                 7

# FE1_AMPLIFIER2_EN - Frontend channel 1 amplifier 2 enable (gain: 10) (OP2)
WD2_FE1_AMPLIFIER2_EN_REG                =                WD2_REG_FE_CFG_0_1
WD2_FE1_AMPLIFIER2_EN_MASK               =                        0x00000040
WD2_FE1_AMPLIFIER2_EN_OFS                =                                 6

# FE1_AMPLIFIER1_COMP_EN - Frontend channel 1 amplifier 1 compensation enable (COMP1)
WD2_FE1_AMPLIFIER1_COMP_EN_REG           =                WD2_REG_FE_CFG_0_1
WD2_FE1_AMPLIFIER1_COMP_EN_MASK          =                        0x00000020
WD2_FE1_AMPLIFIER1_COMP_EN_OFS           =                                 5

# FE1_AMPLIFIER1_EN - Frontend channel 1 amplifier 1 enable (gain: 10) (OP1)
WD2_FE1_AMPLIFIER1_EN_REG                =                WD2_REG_FE_CFG_0_1
WD2_FE1_AMPLIFIER1_EN_MASK               =                        0x00000010
WD2_FE1_AMPLIFIER1_EN_OFS                =                                 4

# FE1_ATTENUATION - Frontend channel 1 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
WD2_FE1_ATTENUATION_REG                  =                WD2_REG_FE_CFG_0_1
WD2_FE1_ATTENUATION_MASK                 =                        0x0000000C
WD2_FE1_ATTENUATION_OFS                  =                                 2

# FE1_MUX - Frontend channel 1 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
WD2_FE1_MUX_REG                          =                WD2_REG_FE_CFG_0_1
WD2_FE1_MUX_MASK                         =                        0x00000003
WD2_FE1_MUX_OFS                          =                                 0



# ****** Control Register 31 [0x107C]: FE_CFG_2_3 - Frontend Settings for Channel 2 and 3 (Default: 0x00020002) ******

# FE2_PZC_EN - Frontend channel 2 PZC (pole-zero cancellation) enable (ACDC)
WD2_FE2_PZC_EN_REG                       =                WD2_REG_FE_CFG_2_3
WD2_FE2_PZC_EN_MASK                      =                        0x01000000
WD2_FE2_PZC_EN_OFS                       =                                24

# FE2_AMPLIFIER2_COMP_EN - Frontend channel 2 amplifier 2 compensation enable (COMP2)
WD2_FE2_AMPLIFIER2_COMP_EN_REG           =                WD2_REG_FE_CFG_2_3
WD2_FE2_AMPLIFIER2_COMP_EN_MASK          =                        0x00800000
WD2_FE2_AMPLIFIER2_COMP_EN_OFS           =                                23

# FE2_AMPLIFIER2_EN - Frontend channel 2 amplifier 2 enable (gain: 10) (OP2)
WD2_FE2_AMPLIFIER2_EN_REG                =                WD2_REG_FE_CFG_2_3
WD2_FE2_AMPLIFIER2_EN_MASK               =                        0x00400000
WD2_FE2_AMPLIFIER2_EN_OFS                =                                22

# FE2_AMPLIFIER1_COMP_EN - Frontend channel 2 amplifier 1 compensation enable (COMP1)
WD2_FE2_AMPLIFIER1_COMP_EN_REG           =                WD2_REG_FE_CFG_2_3
WD2_FE2_AMPLIFIER1_COMP_EN_MASK          =                        0x00200000
WD2_FE2_AMPLIFIER1_COMP_EN_OFS           =                                21

# FE2_AMPLIFIER1_EN - Frontend channel 2 amplifier 1 enable (gain: 10) (OP1)
WD2_FE2_AMPLIFIER1_EN_REG                =                WD2_REG_FE_CFG_2_3
WD2_FE2_AMPLIFIER1_EN_MASK               =                        0x00100000
WD2_FE2_AMPLIFIER1_EN_OFS                =                                20

# FE2_ATTENUATION - Frontend channel 2 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
WD2_FE2_ATTENUATION_REG                  =                WD2_REG_FE_CFG_2_3
WD2_FE2_ATTENUATION_MASK                 =                        0x000C0000
WD2_FE2_ATTENUATION_OFS                  =                                18

# FE2_MUX - Frontend channel 2 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
WD2_FE2_MUX_REG                          =                WD2_REG_FE_CFG_2_3
WD2_FE2_MUX_MASK                         =                        0x00030000
WD2_FE2_MUX_OFS                          =                                16

# FE3_PZC_EN - Frontend channel 3 PZC (pole-zero cancellation) enable (ACDC)
WD2_FE3_PZC_EN_REG                       =                WD2_REG_FE_CFG_2_3
WD2_FE3_PZC_EN_MASK                      =                        0x00000100
WD2_FE3_PZC_EN_OFS                       =                                 8

# FE3_AMPLIFIER2_COMP_EN - Frontend channel 3 amplifier 2 compensation enable (COMP2)
WD2_FE3_AMPLIFIER2_COMP_EN_REG           =                WD2_REG_FE_CFG_2_3
WD2_FE3_AMPLIFIER2_COMP_EN_MASK          =                        0x00000080
WD2_FE3_AMPLIFIER2_COMP_EN_OFS           =                                 7

# FE3_AMPLIFIER2_EN - Frontend channel 3 amplifier 2 enable (gain: 10) (OP2)
WD2_FE3_AMPLIFIER2_EN_REG                =                WD2_REG_FE_CFG_2_3
WD2_FE3_AMPLIFIER2_EN_MASK               =                        0x00000040
WD2_FE3_AMPLIFIER2_EN_OFS                =                                 6

# FE3_AMPLIFIER1_COMP_EN - Frontend channel 3 amplifier 1 compensation enable (COMP1)
WD2_FE3_AMPLIFIER1_COMP_EN_REG           =                WD2_REG_FE_CFG_2_3
WD2_FE3_AMPLIFIER1_COMP_EN_MASK          =                        0x00000020
WD2_FE3_AMPLIFIER1_COMP_EN_OFS           =                                 5

# FE3_AMPLIFIER1_EN - Frontend channel 3 amplifier 1 enable (gain: 10) (OP1)
WD2_FE3_AMPLIFIER1_EN_REG                =                WD2_REG_FE_CFG_2_3
WD2_FE3_AMPLIFIER1_EN_MASK               =                        0x00000010
WD2_FE3_AMPLIFIER1_EN_OFS                =                                 4

# FE3_ATTENUATION - Frontend channel 3 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
WD2_FE3_ATTENUATION_REG                  =                WD2_REG_FE_CFG_2_3
WD2_FE3_ATTENUATION_MASK                 =                        0x0000000C
WD2_FE3_ATTENUATION_OFS                  =                                 2

# FE3_MUX - Frontend channel 3 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
WD2_FE3_MUX_REG                          =                WD2_REG_FE_CFG_2_3
WD2_FE3_MUX_MASK                         =                        0x00000003
WD2_FE3_MUX_OFS                          =                                 0



# ****** Control Register 32 [0x1080]: FE_CFG_4_5 - Frontend Settings for Channel 4 and 5 (Default: 0x00020002) ******

# FE4_PZC_EN - Frontend channel 4 PZC (pole-zero cancellation) enable (ACDC)
WD2_FE4_PZC_EN_REG                       =                WD2_REG_FE_CFG_4_5
WD2_FE4_PZC_EN_MASK                      =                        0x01000000
WD2_FE4_PZC_EN_OFS                       =                                24

# FE4_AMPLIFIER2_COMP_EN - Frontend channel 4 amplifier 2 compensation enable (COMP2)
WD2_FE4_AMPLIFIER2_COMP_EN_REG           =                WD2_REG_FE_CFG_4_5
WD2_FE4_AMPLIFIER2_COMP_EN_MASK          =                        0x00800000
WD2_FE4_AMPLIFIER2_COMP_EN_OFS           =                                23

# FE4_AMPLIFIER2_EN - Frontend channel 4 amplifier 2 enable (gain: 10) (OP2)
WD2_FE4_AMPLIFIER2_EN_REG                =                WD2_REG_FE_CFG_4_5
WD2_FE4_AMPLIFIER2_EN_MASK               =                        0x00400000
WD2_FE4_AMPLIFIER2_EN_OFS                =                                22

# FE4_AMPLIFIER1_COMP_EN - Frontend channel 4 amplifier 1 compensation enable (COMP1)
WD2_FE4_AMPLIFIER1_COMP_EN_REG           =                WD2_REG_FE_CFG_4_5
WD2_FE4_AMPLIFIER1_COMP_EN_MASK          =                        0x00200000
WD2_FE4_AMPLIFIER1_COMP_EN_OFS           =                                21

# FE4_AMPLIFIER1_EN - Frontend channel 4 amplifier 1 enable (gain: 10) (OP1)
WD2_FE4_AMPLIFIER1_EN_REG                =                WD2_REG_FE_CFG_4_5
WD2_FE4_AMPLIFIER1_EN_MASK               =                        0x00100000
WD2_FE4_AMPLIFIER1_EN_OFS                =                                20

# FE4_ATTENUATION - Frontend channel 4 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
WD2_FE4_ATTENUATION_REG                  =                WD2_REG_FE_CFG_4_5
WD2_FE4_ATTENUATION_MASK                 =                        0x000C0000
WD2_FE4_ATTENUATION_OFS                  =                                18

# FE4_MUX - Frontend channel 4 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
WD2_FE4_MUX_REG                          =                WD2_REG_FE_CFG_4_5
WD2_FE4_MUX_MASK                         =                        0x00030000
WD2_FE4_MUX_OFS                          =                                16

# FE5_PZC_EN - Frontend channel 5 PZC (pole-zero cancellation) enable (ACDC)
WD2_FE5_PZC_EN_REG                       =                WD2_REG_FE_CFG_4_5
WD2_FE5_PZC_EN_MASK                      =                        0x00000100
WD2_FE5_PZC_EN_OFS                       =                                 8

# FE5_AMPLIFIER2_COMP_EN - Frontend channel 5 amplifier 2 compensation enable (COMP2)
WD2_FE5_AMPLIFIER2_COMP_EN_REG           =                WD2_REG_FE_CFG_4_5
WD2_FE5_AMPLIFIER2_COMP_EN_MASK          =                        0x00000080
WD2_FE5_AMPLIFIER2_COMP_EN_OFS           =                                 7

# FE5_AMPLIFIER2_EN - Frontend channel 5 amplifier 2 enable (gain: 10) (OP2)
WD2_FE5_AMPLIFIER2_EN_REG                =                WD2_REG_FE_CFG_4_5
WD2_FE5_AMPLIFIER2_EN_MASK               =                        0x00000040
WD2_FE5_AMPLIFIER2_EN_OFS                =                                 6

# FE5_AMPLIFIER1_COMP_EN - Frontend channel 5 amplifier 1 compensation enable (COMP1)
WD2_FE5_AMPLIFIER1_COMP_EN_REG           =                WD2_REG_FE_CFG_4_5
WD2_FE5_AMPLIFIER1_COMP_EN_MASK          =                        0x00000020
WD2_FE5_AMPLIFIER1_COMP_EN_OFS           =                                 5

# FE5_AMPLIFIER1_EN - Frontend channel 5 amplifier 1 enable (gain: 10) (OP1)
WD2_FE5_AMPLIFIER1_EN_REG                =                WD2_REG_FE_CFG_4_5
WD2_FE5_AMPLIFIER1_EN_MASK               =                        0x00000010
WD2_FE5_AMPLIFIER1_EN_OFS                =                                 4

# FE5_ATTENUATION - Frontend channel 5 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
WD2_FE5_ATTENUATION_REG                  =                WD2_REG_FE_CFG_4_5
WD2_FE5_ATTENUATION_MASK                 =                        0x0000000C
WD2_FE5_ATTENUATION_OFS                  =                                 2

# FE5_MUX - Frontend channel 5 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
WD2_FE5_MUX_REG                          =                WD2_REG_FE_CFG_4_5
WD2_FE5_MUX_MASK                         =                        0x00000003
WD2_FE5_MUX_OFS                          =                                 0



# ****** Control Register 33 [0x1084]: FE_CFG_6_7 - Frontend Settings for Channel 6 and 7 (Default: 0x00020002) ******

# FE6_PZC_EN - Frontend channel 6 PZC (pole-zero cancellation) enable (ACDC)
WD2_FE6_PZC_EN_REG                       =                WD2_REG_FE_CFG_6_7
WD2_FE6_PZC_EN_MASK                      =                        0x01000000
WD2_FE6_PZC_EN_OFS                       =                                24

# FE6_AMPLIFIER2_COMP_EN - Frontend channel 6 amplifier 2 compensation enable (COMP2)
WD2_FE6_AMPLIFIER2_COMP_EN_REG           =                WD2_REG_FE_CFG_6_7
WD2_FE6_AMPLIFIER2_COMP_EN_MASK          =                        0x00800000
WD2_FE6_AMPLIFIER2_COMP_EN_OFS           =                                23

# FE6_AMPLIFIER2_EN - Frontend channel 6 amplifier 2 enable (gain: 10) (OP2)
WD2_FE6_AMPLIFIER2_EN_REG                =                WD2_REG_FE_CFG_6_7
WD2_FE6_AMPLIFIER2_EN_MASK               =                        0x00400000
WD2_FE6_AMPLIFIER2_EN_OFS                =                                22

# FE6_AMPLIFIER1_COMP_EN - Frontend channel 6 amplifier 1 compensation enable (COMP1)
WD2_FE6_AMPLIFIER1_COMP_EN_REG           =                WD2_REG_FE_CFG_6_7
WD2_FE6_AMPLIFIER1_COMP_EN_MASK          =                        0x00200000
WD2_FE6_AMPLIFIER1_COMP_EN_OFS           =                                21

# FE6_AMPLIFIER1_EN - Frontend channel 6 amplifier 1 enable (gain: 10) (OP1)
WD2_FE6_AMPLIFIER1_EN_REG                =                WD2_REG_FE_CFG_6_7
WD2_FE6_AMPLIFIER1_EN_MASK               =                        0x00100000
WD2_FE6_AMPLIFIER1_EN_OFS                =                                20

# FE6_ATTENUATION - Frontend channel 6 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
WD2_FE6_ATTENUATION_REG                  =                WD2_REG_FE_CFG_6_7
WD2_FE6_ATTENUATION_MASK                 =                        0x000C0000
WD2_FE6_ATTENUATION_OFS                  =                                18

# FE6_MUX - Frontend channel 6 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
WD2_FE6_MUX_REG                          =                WD2_REG_FE_CFG_6_7
WD2_FE6_MUX_MASK                         =                        0x00030000
WD2_FE6_MUX_OFS                          =                                16

# FE7_PZC_EN - Frontend channel 7 PZC (pole-zero cancellation) enable (ACDC)
WD2_FE7_PZC_EN_REG                       =                WD2_REG_FE_CFG_6_7
WD2_FE7_PZC_EN_MASK                      =                        0x00000100
WD2_FE7_PZC_EN_OFS                       =                                 8

# FE7_AMPLIFIER2_COMP_EN - Frontend channel 7 amplifier 2 compensation enable (COMP2)
WD2_FE7_AMPLIFIER2_COMP_EN_REG           =                WD2_REG_FE_CFG_6_7
WD2_FE7_AMPLIFIER2_COMP_EN_MASK          =                        0x00000080
WD2_FE7_AMPLIFIER2_COMP_EN_OFS           =                                 7

# FE7_AMPLIFIER2_EN - Frontend channel 7 amplifier 2 enable (gain: 10) (OP2)
WD2_FE7_AMPLIFIER2_EN_REG                =                WD2_REG_FE_CFG_6_7
WD2_FE7_AMPLIFIER2_EN_MASK               =                        0x00000040
WD2_FE7_AMPLIFIER2_EN_OFS                =                                 6

# FE7_AMPLIFIER1_COMP_EN - Frontend channel 7 amplifier 1 compensation enable (COMP1)
WD2_FE7_AMPLIFIER1_COMP_EN_REG           =                WD2_REG_FE_CFG_6_7
WD2_FE7_AMPLIFIER1_COMP_EN_MASK          =                        0x00000020
WD2_FE7_AMPLIFIER1_COMP_EN_OFS           =                                 5

# FE7_AMPLIFIER1_EN - Frontend channel 7 amplifier 1 enable (gain: 10) (OP1)
WD2_FE7_AMPLIFIER1_EN_REG                =                WD2_REG_FE_CFG_6_7
WD2_FE7_AMPLIFIER1_EN_MASK               =                        0x00000010
WD2_FE7_AMPLIFIER1_EN_OFS                =                                 4

# FE7_ATTENUATION - Frontend channel 7 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
WD2_FE7_ATTENUATION_REG                  =                WD2_REG_FE_CFG_6_7
WD2_FE7_ATTENUATION_MASK                 =                        0x0000000C
WD2_FE7_ATTENUATION_OFS                  =                                 2

# FE7_MUX - Frontend channel 7 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
WD2_FE7_MUX_REG                          =                WD2_REG_FE_CFG_6_7
WD2_FE7_MUX_MASK                         =                        0x00000003
WD2_FE7_MUX_OFS                          =                                 0



# ****** Control Register 34 [0x1088]: FE_CFG_8_9 - Frontend Settings for Channel 8 and 9 (Default: 0x00020002) ******

# FE8_PZC_EN - Frontend channel 8 PZC (pole-zero cancellation) enable (ACDC)
WD2_FE8_PZC_EN_REG                       =                WD2_REG_FE_CFG_8_9
WD2_FE8_PZC_EN_MASK                      =                        0x01000000
WD2_FE8_PZC_EN_OFS                       =                                24

# FE8_AMPLIFIER2_COMP_EN - Frontend channel 8 amplifier 2 compensation enable (COMP2)
WD2_FE8_AMPLIFIER2_COMP_EN_REG           =                WD2_REG_FE_CFG_8_9
WD2_FE8_AMPLIFIER2_COMP_EN_MASK          =                        0x00800000
WD2_FE8_AMPLIFIER2_COMP_EN_OFS           =                                23

# FE8_AMPLIFIER2_EN - Frontend channel 8 amplifier 2 enable (gain: 10) (OP2)
WD2_FE8_AMPLIFIER2_EN_REG                =                WD2_REG_FE_CFG_8_9
WD2_FE8_AMPLIFIER2_EN_MASK               =                        0x00400000
WD2_FE8_AMPLIFIER2_EN_OFS                =                                22

# FE8_AMPLIFIER1_COMP_EN - Frontend channel 8 amplifier 1 compensation enable (COMP1)
WD2_FE8_AMPLIFIER1_COMP_EN_REG           =                WD2_REG_FE_CFG_8_9
WD2_FE8_AMPLIFIER1_COMP_EN_MASK          =                        0x00200000
WD2_FE8_AMPLIFIER1_COMP_EN_OFS           =                                21

# FE8_AMPLIFIER1_EN - Frontend channel 8 amplifier 1 enable (gain: 10) (OP1)
WD2_FE8_AMPLIFIER1_EN_REG                =                WD2_REG_FE_CFG_8_9
WD2_FE8_AMPLIFIER1_EN_MASK               =                        0x00100000
WD2_FE8_AMPLIFIER1_EN_OFS                =                                20

# FE8_ATTENUATION - Frontend channel 8 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
WD2_FE8_ATTENUATION_REG                  =                WD2_REG_FE_CFG_8_9
WD2_FE8_ATTENUATION_MASK                 =                        0x000C0000
WD2_FE8_ATTENUATION_OFS                  =                                18

# FE8_MUX - Frontend channel 8 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
WD2_FE8_MUX_REG                          =                WD2_REG_FE_CFG_8_9
WD2_FE8_MUX_MASK                         =                        0x00030000
WD2_FE8_MUX_OFS                          =                                16

# FE9_PZC_EN - Frontend channel 9 PZC (pole-zero cancellation) enable (ACDC)
WD2_FE9_PZC_EN_REG                       =                WD2_REG_FE_CFG_8_9
WD2_FE9_PZC_EN_MASK                      =                        0x00000100
WD2_FE9_PZC_EN_OFS                       =                                 8

# FE9_AMPLIFIER2_COMP_EN - Frontend channel 9 amplifier 2 compensation enable (COMP2)
WD2_FE9_AMPLIFIER2_COMP_EN_REG           =                WD2_REG_FE_CFG_8_9
WD2_FE9_AMPLIFIER2_COMP_EN_MASK          =                        0x00000080
WD2_FE9_AMPLIFIER2_COMP_EN_OFS           =                                 7

# FE9_AMPLIFIER2_EN - Frontend channel 9 amplifier 2 enable (gain: 10) (OP2)
WD2_FE9_AMPLIFIER2_EN_REG                =                WD2_REG_FE_CFG_8_9
WD2_FE9_AMPLIFIER2_EN_MASK               =                        0x00000040
WD2_FE9_AMPLIFIER2_EN_OFS                =                                 6

# FE9_AMPLIFIER1_COMP_EN - Frontend channel 9 amplifier 1 compensation enable (COMP1)
WD2_FE9_AMPLIFIER1_COMP_EN_REG           =                WD2_REG_FE_CFG_8_9
WD2_FE9_AMPLIFIER1_COMP_EN_MASK          =                        0x00000020
WD2_FE9_AMPLIFIER1_COMP_EN_OFS           =                                 5

# FE9_AMPLIFIER1_EN - Frontend channel 9 amplifier 1 enable (gain: 10) (OP1)
WD2_FE9_AMPLIFIER1_EN_REG                =                WD2_REG_FE_CFG_8_9
WD2_FE9_AMPLIFIER1_EN_MASK               =                        0x00000010
WD2_FE9_AMPLIFIER1_EN_OFS                =                                 4

# FE9_ATTENUATION - Frontend channel 9 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
WD2_FE9_ATTENUATION_REG                  =                WD2_REG_FE_CFG_8_9
WD2_FE9_ATTENUATION_MASK                 =                        0x0000000C
WD2_FE9_ATTENUATION_OFS                  =                                 2

# FE9_MUX - Frontend channel 9 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
WD2_FE9_MUX_REG                          =                WD2_REG_FE_CFG_8_9
WD2_FE9_MUX_MASK                         =                        0x00000003
WD2_FE9_MUX_OFS                          =                                 0



# ****** Control Register 35 [0x108C]: FE_CFG_10_11 - Frontend Settings for Channel 10 and 11 (Default: 0x00020002) ******

# FE10_PZC_EN - Frontend channel 10 PZC (pole-zero cancellation) enable (ACDC)
WD2_FE10_PZC_EN_REG                      =              WD2_REG_FE_CFG_10_11
WD2_FE10_PZC_EN_MASK                     =                        0x01000000
WD2_FE10_PZC_EN_OFS                      =                                24

# FE10_AMPLIFIER2_COMP_EN - Frontend channel 10 amplifier 2 compensation enable (COMP2)
WD2_FE10_AMPLIFIER2_COMP_EN_REG          =              WD2_REG_FE_CFG_10_11
WD2_FE10_AMPLIFIER2_COMP_EN_MASK         =                        0x00800000
WD2_FE10_AMPLIFIER2_COMP_EN_OFS          =                                23

# FE10_AMPLIFIER2_EN - Frontend channel 10 amplifier 2 enable (gain: 10) (OP2)
WD2_FE10_AMPLIFIER2_EN_REG               =              WD2_REG_FE_CFG_10_11
WD2_FE10_AMPLIFIER2_EN_MASK              =                        0x00400000
WD2_FE10_AMPLIFIER2_EN_OFS               =                                22

# FE10_AMPLIFIER1_COMP_EN - Frontend channel 10 amplifier 1 compensation enable (COMP1)
WD2_FE10_AMPLIFIER1_COMP_EN_REG          =              WD2_REG_FE_CFG_10_11
WD2_FE10_AMPLIFIER1_COMP_EN_MASK         =                        0x00200000
WD2_FE10_AMPLIFIER1_COMP_EN_OFS          =                                21

# FE10_AMPLIFIER1_EN - Frontend channel 10 amplifier 1 enable (gain: 10) (OP1)
WD2_FE10_AMPLIFIER1_EN_REG               =              WD2_REG_FE_CFG_10_11
WD2_FE10_AMPLIFIER1_EN_MASK              =                        0x00100000
WD2_FE10_AMPLIFIER1_EN_OFS               =                                20

# FE10_ATTENUATION - Frontend channel 10 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
WD2_FE10_ATTENUATION_REG                 =              WD2_REG_FE_CFG_10_11
WD2_FE10_ATTENUATION_MASK                =                        0x000C0000
WD2_FE10_ATTENUATION_OFS                 =                                18

# FE10_MUX - Frontend channel 10 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
WD2_FE10_MUX_REG                         =              WD2_REG_FE_CFG_10_11
WD2_FE10_MUX_MASK                        =                        0x00030000
WD2_FE10_MUX_OFS                         =                                16

# FE11_PZC_EN - Frontend channel 11 PZC (pole-zero cancellation) enable (ACDC)
WD2_FE11_PZC_EN_REG                      =              WD2_REG_FE_CFG_10_11
WD2_FE11_PZC_EN_MASK                     =                        0x00000100
WD2_FE11_PZC_EN_OFS                      =                                 8

# FE11_AMPLIFIER2_COMP_EN - Frontend channel 11 amplifier 2 compensation enable (COMP2)
WD2_FE11_AMPLIFIER2_COMP_EN_REG          =              WD2_REG_FE_CFG_10_11
WD2_FE11_AMPLIFIER2_COMP_EN_MASK         =                        0x00000080
WD2_FE11_AMPLIFIER2_COMP_EN_OFS          =                                 7

# FE11_AMPLIFIER2_EN - Frontend channel 11 amplifier 2 enable (gain: 10) (OP2)
WD2_FE11_AMPLIFIER2_EN_REG               =              WD2_REG_FE_CFG_10_11
WD2_FE11_AMPLIFIER2_EN_MASK              =                        0x00000040
WD2_FE11_AMPLIFIER2_EN_OFS               =                                 6

# FE11_AMPLIFIER1_COMP_EN - Frontend channel 11 amplifier 1 compensation enable (COMP1)
WD2_FE11_AMPLIFIER1_COMP_EN_REG          =              WD2_REG_FE_CFG_10_11
WD2_FE11_AMPLIFIER1_COMP_EN_MASK         =                        0x00000020
WD2_FE11_AMPLIFIER1_COMP_EN_OFS          =                                 5

# FE11_AMPLIFIER1_EN - Frontend channel 11 amplifier 1 enable (gain: 10) (OP1)
WD2_FE11_AMPLIFIER1_EN_REG               =              WD2_REG_FE_CFG_10_11
WD2_FE11_AMPLIFIER1_EN_MASK              =                        0x00000010
WD2_FE11_AMPLIFIER1_EN_OFS               =                                 4

# FE11_ATTENUATION - Frontend channel 11 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
WD2_FE11_ATTENUATION_REG                 =              WD2_REG_FE_CFG_10_11
WD2_FE11_ATTENUATION_MASK                =                        0x0000000C
WD2_FE11_ATTENUATION_OFS                 =                                 2

# FE11_MUX - Frontend channel 11 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
WD2_FE11_MUX_REG                         =              WD2_REG_FE_CFG_10_11
WD2_FE11_MUX_MASK                        =                        0x00000003
WD2_FE11_MUX_OFS                         =                                 0



# ****** Control Register 36 [0x1090]: FE_CFG_12_13 - Frontend Settings for Channel 12 and 13 (Default: 0x00020002) ******

# FE12_PZC_EN - Frontend channel 12 PZC (pole-zero cancellation) enable (ACDC)
WD2_FE12_PZC_EN_REG                      =              WD2_REG_FE_CFG_12_13
WD2_FE12_PZC_EN_MASK                     =                        0x01000000
WD2_FE12_PZC_EN_OFS                      =                                24

# FE12_AMPLIFIER2_COMP_EN - Frontend channel 12 amplifier 2 compensation enable (COMP2)
WD2_FE12_AMPLIFIER2_COMP_EN_REG          =              WD2_REG_FE_CFG_12_13
WD2_FE12_AMPLIFIER2_COMP_EN_MASK         =                        0x00800000
WD2_FE12_AMPLIFIER2_COMP_EN_OFS          =                                23

# FE12_AMPLIFIER2_EN - Frontend channel 12 amplifier 2 enable (gain: 10) (OP2)
WD2_FE12_AMPLIFIER2_EN_REG               =              WD2_REG_FE_CFG_12_13
WD2_FE12_AMPLIFIER2_EN_MASK              =                        0x00400000
WD2_FE12_AMPLIFIER2_EN_OFS               =                                22

# FE12_AMPLIFIER1_COMP_EN - Frontend channel 12 amplifier 1 compensation enable (COMP1)
WD2_FE12_AMPLIFIER1_COMP_EN_REG          =              WD2_REG_FE_CFG_12_13
WD2_FE12_AMPLIFIER1_COMP_EN_MASK         =                        0x00200000
WD2_FE12_AMPLIFIER1_COMP_EN_OFS          =                                21

# FE12_AMPLIFIER1_EN - Frontend channel 12 amplifier 1 enable (gain: 10) (OP1)
WD2_FE12_AMPLIFIER1_EN_REG               =              WD2_REG_FE_CFG_12_13
WD2_FE12_AMPLIFIER1_EN_MASK              =                        0x00100000
WD2_FE12_AMPLIFIER1_EN_OFS               =                                20

# FE12_ATTENUATION - Frontend channel 12 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
WD2_FE12_ATTENUATION_REG                 =              WD2_REG_FE_CFG_12_13
WD2_FE12_ATTENUATION_MASK                =                        0x000C0000
WD2_FE12_ATTENUATION_OFS                 =                                18

# FE12_MUX - Frontend channel 12 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
WD2_FE12_MUX_REG                         =              WD2_REG_FE_CFG_12_13
WD2_FE12_MUX_MASK                        =                        0x00030000
WD2_FE12_MUX_OFS                         =                                16

# FE13_PZC_EN - Frontend channel 13 PZC (pole-zero cancellation) enable (ACDC)
WD2_FE13_PZC_EN_REG                      =              WD2_REG_FE_CFG_12_13
WD2_FE13_PZC_EN_MASK                     =                        0x00000100
WD2_FE13_PZC_EN_OFS                      =                                 8

# FE13_AMPLIFIER2_COMP_EN - Frontend channel 13 amplifier 2 compensation enable (COMP2)
WD2_FE13_AMPLIFIER2_COMP_EN_REG          =              WD2_REG_FE_CFG_12_13
WD2_FE13_AMPLIFIER2_COMP_EN_MASK         =                        0x00000080
WD2_FE13_AMPLIFIER2_COMP_EN_OFS          =                                 7

# FE13_AMPLIFIER2_EN - Frontend channel 13 amplifier 2 enable (gain: 10) (OP2)
WD2_FE13_AMPLIFIER2_EN_REG               =              WD2_REG_FE_CFG_12_13
WD2_FE13_AMPLIFIER2_EN_MASK              =                        0x00000040
WD2_FE13_AMPLIFIER2_EN_OFS               =                                 6

# FE13_AMPLIFIER1_COMP_EN - Frontend channel 13 amplifier 1 compensation enable (COMP1)
WD2_FE13_AMPLIFIER1_COMP_EN_REG          =              WD2_REG_FE_CFG_12_13
WD2_FE13_AMPLIFIER1_COMP_EN_MASK         =                        0x00000020
WD2_FE13_AMPLIFIER1_COMP_EN_OFS          =                                 5

# FE13_AMPLIFIER1_EN - Frontend channel 13 amplifier 1 enable (gain: 10) (OP1)
WD2_FE13_AMPLIFIER1_EN_REG               =              WD2_REG_FE_CFG_12_13
WD2_FE13_AMPLIFIER1_EN_MASK              =                        0x00000010
WD2_FE13_AMPLIFIER1_EN_OFS               =                                 4

# FE13_ATTENUATION - Frontend channel 13 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
WD2_FE13_ATTENUATION_REG                 =              WD2_REG_FE_CFG_12_13
WD2_FE13_ATTENUATION_MASK                =                        0x0000000C
WD2_FE13_ATTENUATION_OFS                 =                                 2

# FE13_MUX - Frontend channel 13 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
WD2_FE13_MUX_REG                         =              WD2_REG_FE_CFG_12_13
WD2_FE13_MUX_MASK                        =                        0x00000003
WD2_FE13_MUX_OFS                         =                                 0



# ****** Control Register 37 [0x1094]: FE_CFG_14_15 - Frontend Settings for Channel 14 and 15 (Default: 0x00020002) ******

# FE14_PZC_EN - Frontend channel 14 PZC (pole-zero cancellation) enable (ACDC)
WD2_FE14_PZC_EN_REG                      =              WD2_REG_FE_CFG_14_15
WD2_FE14_PZC_EN_MASK                     =                        0x01000000
WD2_FE14_PZC_EN_OFS                      =                                24

# FE14_AMPLIFIER2_COMP_EN - Frontend channel 14 amplifier 2 compensation enable (COMP2)
WD2_FE14_AMPLIFIER2_COMP_EN_REG          =              WD2_REG_FE_CFG_14_15
WD2_FE14_AMPLIFIER2_COMP_EN_MASK         =                        0x00800000
WD2_FE14_AMPLIFIER2_COMP_EN_OFS          =                                23

# FE14_AMPLIFIER2_EN - Frontend channel 14 amplifier 2 enable (gain: 10) (OP2)
WD2_FE14_AMPLIFIER2_EN_REG               =              WD2_REG_FE_CFG_14_15
WD2_FE14_AMPLIFIER2_EN_MASK              =                        0x00400000
WD2_FE14_AMPLIFIER2_EN_OFS               =                                22

# FE14_AMPLIFIER1_COMP_EN - Frontend channel 14 amplifier 1 compensation enable (COMP1)
WD2_FE14_AMPLIFIER1_COMP_EN_REG          =              WD2_REG_FE_CFG_14_15
WD2_FE14_AMPLIFIER1_COMP_EN_MASK         =                        0x00200000
WD2_FE14_AMPLIFIER1_COMP_EN_OFS          =                                21

# FE14_AMPLIFIER1_EN - Frontend channel 14 amplifier 1 enable (gain: 10) (OP1)
WD2_FE14_AMPLIFIER1_EN_REG               =              WD2_REG_FE_CFG_14_15
WD2_FE14_AMPLIFIER1_EN_MASK              =                        0x00100000
WD2_FE14_AMPLIFIER1_EN_OFS               =                                20

# FE14_ATTENUATION - Frontend channel 14 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
WD2_FE14_ATTENUATION_REG                 =              WD2_REG_FE_CFG_14_15
WD2_FE14_ATTENUATION_MASK                =                        0x000C0000
WD2_FE14_ATTENUATION_OFS                 =                                18

# FE14_MUX - Frontend channel 14 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
WD2_FE14_MUX_REG                         =              WD2_REG_FE_CFG_14_15
WD2_FE14_MUX_MASK                        =                        0x00030000
WD2_FE14_MUX_OFS                         =                                16

# FE15_PZC_EN - Frontend channel 15 PZC (pole-zero cancellation) enable (ACDC)
WD2_FE15_PZC_EN_REG                      =              WD2_REG_FE_CFG_14_15
WD2_FE15_PZC_EN_MASK                     =                        0x00000100
WD2_FE15_PZC_EN_OFS                      =                                 8

# FE15_AMPLIFIER2_COMP_EN - Frontend channel 15 amplifier 2 compensation enable (COMP2)
WD2_FE15_AMPLIFIER2_COMP_EN_REG          =              WD2_REG_FE_CFG_14_15
WD2_FE15_AMPLIFIER2_COMP_EN_MASK         =                        0x00000080
WD2_FE15_AMPLIFIER2_COMP_EN_OFS          =                                 7

# FE15_AMPLIFIER2_EN - Frontend channel 15 amplifier 2 enable (gain: 10) (OP2)
WD2_FE15_AMPLIFIER2_EN_REG               =              WD2_REG_FE_CFG_14_15
WD2_FE15_AMPLIFIER2_EN_MASK              =                        0x00000040
WD2_FE15_AMPLIFIER2_EN_OFS               =                                 6

# FE15_AMPLIFIER1_COMP_EN - Frontend channel 15 amplifier 1 compensation enable (COMP1)
WD2_FE15_AMPLIFIER1_COMP_EN_REG          =              WD2_REG_FE_CFG_14_15
WD2_FE15_AMPLIFIER1_COMP_EN_MASK         =                        0x00000020
WD2_FE15_AMPLIFIER1_COMP_EN_OFS          =                                 5

# FE15_AMPLIFIER1_EN - Frontend channel 15 amplifier 1 enable (gain: 10) (OP1)
WD2_FE15_AMPLIFIER1_EN_REG               =              WD2_REG_FE_CFG_14_15
WD2_FE15_AMPLIFIER1_EN_MASK              =                        0x00000010
WD2_FE15_AMPLIFIER1_EN_OFS               =                                 4

# FE15_ATTENUATION - Frontend channel 15 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)
WD2_FE15_ATTENUATION_REG                 =              WD2_REG_FE_CFG_14_15
WD2_FE15_ATTENUATION_MASK                =                        0x0000000C
WD2_FE15_ATTENUATION_OFS                 =                                 2

# FE15_MUX - Frontend channel 15 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)
WD2_FE15_MUX_REG                         =              WD2_REG_FE_CFG_14_15
WD2_FE15_MUX_MASK                        =                        0x00000003
WD2_FE15_MUX_OFS                         =                                 0



# ****** Control Register 38 [0x1098]: HV_U_TARGET_0 - Target HV Supply Voltage for Channel 0 (Default: 0x00000000) ******

# HV_U_TARGET_0 - Float value (u_demand)
WD2_HV_U_TARGET_0_REG                    =             WD2_REG_HV_U_TARGET_0
WD2_HV_U_TARGET_0_MASK                   =                        0xFFFFFFFF
WD2_HV_U_TARGET_0_OFS                    =                                 0



# ****** Control Register 39 [0x109C]: HV_U_TARGET_1 - Target HV Supply Voltage for Channel 1 (Default: 0x00000000) ******

# HV_U_TARGET_1 - Float value (u_demand)
WD2_HV_U_TARGET_1_REG                    =             WD2_REG_HV_U_TARGET_1
WD2_HV_U_TARGET_1_MASK                   =                        0xFFFFFFFF
WD2_HV_U_TARGET_1_OFS                    =                                 0



# ****** Control Register 40 [0x10A0]: HV_U_TARGET_2 - Target HV Supply Voltage for Channel 2 (Default: 0x00000000) ******

# HV_U_TARGET_2 - Float value (u_demand)
WD2_HV_U_TARGET_2_REG                    =             WD2_REG_HV_U_TARGET_2
WD2_HV_U_TARGET_2_MASK                   =                        0xFFFFFFFF
WD2_HV_U_TARGET_2_OFS                    =                                 0



# ****** Control Register 41 [0x10A4]: HV_U_TARGET_3 - Target HV Supply Voltage for Channel 3 (Default: 0x00000000) ******

# HV_U_TARGET_3 - Float value (u_demand)
WD2_HV_U_TARGET_3_REG                    =             WD2_REG_HV_U_TARGET_3
WD2_HV_U_TARGET_3_MASK                   =                        0xFFFFFFFF
WD2_HV_U_TARGET_3_OFS                    =                                 0



# ****** Control Register 42 [0x10A8]: HV_U_TARGET_4 - Target HV Supply Voltage for Channel 4 (Default: 0x00000000) ******

# HV_U_TARGET_4 - Float value (u_demand)
WD2_HV_U_TARGET_4_REG                    =             WD2_REG_HV_U_TARGET_4
WD2_HV_U_TARGET_4_MASK                   =                        0xFFFFFFFF
WD2_HV_U_TARGET_4_OFS                    =                                 0



# ****** Control Register 43 [0x10AC]: HV_U_TARGET_5 - Target HV Supply Voltage for Channel 5 (Default: 0x00000000) ******

# HV_U_TARGET_5 - Float value (u_demand)
WD2_HV_U_TARGET_5_REG                    =             WD2_REG_HV_U_TARGET_5
WD2_HV_U_TARGET_5_MASK                   =                        0xFFFFFFFF
WD2_HV_U_TARGET_5_OFS                    =                                 0



# ****** Control Register 44 [0x10B0]: HV_U_TARGET_6 - Target HV Supply Voltage for Channel 6 (Default: 0x00000000) ******

# HV_U_TARGET_6 - Float value (u_demand)
WD2_HV_U_TARGET_6_REG                    =             WD2_REG_HV_U_TARGET_6
WD2_HV_U_TARGET_6_MASK                   =                        0xFFFFFFFF
WD2_HV_U_TARGET_6_OFS                    =                                 0



# ****** Control Register 45 [0x10B4]: HV_U_TARGET_7 - Target HV Supply Voltage for Channel 7 (Default: 0x00000000) ******

# HV_U_TARGET_7 - Float value (u_demand)
WD2_HV_U_TARGET_7_REG                    =             WD2_REG_HV_U_TARGET_7
WD2_HV_U_TARGET_7_MASK                   =                        0xFFFFFFFF
WD2_HV_U_TARGET_7_OFS                    =                                 0



# ****** Control Register 46 [0x10B8]: HV_U_TARGET_8 - Target HV Supply Voltage for Channel 8 (Default: 0x00000000) ******

# HV_U_TARGET_8 - Float value (u_demand)
WD2_HV_U_TARGET_8_REG                    =             WD2_REG_HV_U_TARGET_8
WD2_HV_U_TARGET_8_MASK                   =                        0xFFFFFFFF
WD2_HV_U_TARGET_8_OFS                    =                                 0



# ****** Control Register 47 [0x10BC]: HV_U_TARGET_9 - Target HV Supply Voltage for Channel 9 (Default: 0x00000000) ******

# HV_U_TARGET_9 - Float value (u_demand)
WD2_HV_U_TARGET_9_REG                    =             WD2_REG_HV_U_TARGET_9
WD2_HV_U_TARGET_9_MASK                   =                        0xFFFFFFFF
WD2_HV_U_TARGET_9_OFS                    =                                 0



# ****** Control Register 48 [0x10C0]: HV_U_TARGET_10 - Target HV Supply Voltage for Channel 10 (Default: 0x00000000) ******

# HV_U_TARGET_10 - Float value (u_demand)
WD2_HV_U_TARGET_10_REG                   =            WD2_REG_HV_U_TARGET_10
WD2_HV_U_TARGET_10_MASK                  =                        0xFFFFFFFF
WD2_HV_U_TARGET_10_OFS                   =                                 0



# ****** Control Register 49 [0x10C4]: HV_U_TARGET_11 - Target HV Supply Voltage for Channel 11 (Default: 0x00000000) ******

# HV_U_TARGET_11 - Float value (u_demand)
WD2_HV_U_TARGET_11_REG                   =            WD2_REG_HV_U_TARGET_11
WD2_HV_U_TARGET_11_MASK                  =                        0xFFFFFFFF
WD2_HV_U_TARGET_11_OFS                   =                                 0



# ****** Control Register 50 [0x10C8]: HV_U_TARGET_12 - Target HV Supply Voltage for Channel 12 (Default: 0x00000000) ******

# HV_U_TARGET_12 - Float value (u_demand)
WD2_HV_U_TARGET_12_REG                   =            WD2_REG_HV_U_TARGET_12
WD2_HV_U_TARGET_12_MASK                  =                        0xFFFFFFFF
WD2_HV_U_TARGET_12_OFS                   =                                 0



# ****** Control Register 51 [0x10CC]: HV_U_TARGET_13 - Target HV Supply Voltage for Channel 13 (Default: 0x00000000) ******

# HV_U_TARGET_13 - Float value (u_demand)
WD2_HV_U_TARGET_13_REG                   =            WD2_REG_HV_U_TARGET_13
WD2_HV_U_TARGET_13_MASK                  =                        0xFFFFFFFF
WD2_HV_U_TARGET_13_OFS                   =                                 0



# ****** Control Register 52 [0x10D0]: HV_U_TARGET_14 - Target HV Supply Voltage for Channel 14 (Default: 0x00000000) ******

# HV_U_TARGET_14 - Float value (u_demand)
WD2_HV_U_TARGET_14_REG                   =            WD2_REG_HV_U_TARGET_14
WD2_HV_U_TARGET_14_MASK                  =                        0xFFFFFFFF
WD2_HV_U_TARGET_14_OFS                   =                                 0



# ****** Control Register 53 [0x10D4]: HV_U_TARGET_15 - Target HV Supply Voltage for Channel 15 (Default: 0x00000000) ******

# HV_U_TARGET_15 - Float value (u_demand)
WD2_HV_U_TARGET_15_REG                   =            WD2_REG_HV_U_TARGET_15
WD2_HV_U_TARGET_15_MASK                  =                        0xFFFFFFFF
WD2_HV_U_TARGET_15_OFS                   =                                 0



# ****** Control Register 54 [0x10D8]: HV_R_SHUNT - Value of the HV Supply Shunt Resistor (Default: 0x00002710) ******

# HV_R_SHUNT - Resistor value in Ohm (r_current)
WD2_HV_R_SHUNT_REG                       =                WD2_REG_HV_R_SHUNT
WD2_HV_R_SHUNT_MASK                      =                        0xFFFFFFFF
WD2_HV_R_SHUNT_OFS                       =                                 0



# ****** Control Register 55 [0x10DC]: LMK_0 - LMK Register 0 (Default: 0x00032100) ******

# LMK0_RESET - Resets LMK Registers to Their Power-On State
WD2_LMK0_RESET_REG                       =                     WD2_REG_LMK_0
WD2_LMK0_RESET_MASK                      =                        0x80000000
WD2_LMK0_RESET_OFS                       =                                31

# LMK0_CLKOUT_MUX - Channel 0 Clock Output Multiplexer (see datasheet)
WD2_LMK0_CLKOUT_MUX_REG                  =                     WD2_REG_LMK_0
WD2_LMK0_CLKOUT_MUX_MASK                 =                        0x00060000
WD2_LMK0_CLKOUT_MUX_OFS                  =                                17

# LMK0_CLKOUT_EN - Channel 0 Clock Output Enable (0 = Disabled, 1 = Enabled)
WD2_LMK0_CLKOUT_EN_REG                   =                     WD2_REG_LMK_0
WD2_LMK0_CLKOUT_EN_MASK                  =                        0x00010000
WD2_LMK0_CLKOUT_EN_OFS                   =                                16

# LMK0_CLKOUT_DIV - Channel 0 Clock Output Divider (value x 2) (1..255)
WD2_LMK0_CLKOUT_DIV_REG                  =                     WD2_REG_LMK_0
WD2_LMK0_CLKOUT_DIV_MASK                 =                        0x0000FF00
WD2_LMK0_CLKOUT_DIV_OFS                  =                                 8

# LMK0_CLKOUT_DLY - Channel 0 Clock Output Delay (value x 150ps)
WD2_LMK0_CLKOUT_DLY_REG                  =                     WD2_REG_LMK_0
WD2_LMK0_CLKOUT_DLY_MASK                 =                        0x000000F0
WD2_LMK0_CLKOUT_DLY_OFS                  =                                 4



# ****** Control Register 56 [0x10E0]: LMK_1 - LMK Register 1 (Default: 0x00020101) ******

# LMK1_CLKOUT_MUX - Channel 1 Clock Output Multiplexer (see datasheet)
WD2_LMK1_CLKOUT_MUX_REG                  =                     WD2_REG_LMK_1
WD2_LMK1_CLKOUT_MUX_MASK                 =                        0x00060000
WD2_LMK1_CLKOUT_MUX_OFS                  =                                17

# LMK1_CLKOUT_EN - Channel 1 Clock Output Enable (0 = Disabled, 1 = Enabled)
WD2_LMK1_CLKOUT_EN_REG                   =                     WD2_REG_LMK_1
WD2_LMK1_CLKOUT_EN_MASK                  =                        0x00010000
WD2_LMK1_CLKOUT_EN_OFS                   =                                16

# LMK1_CLKOUT_DIV - Channel 1 Clock Output Divider (value x 2) (1..255)
WD2_LMK1_CLKOUT_DIV_REG                  =                     WD2_REG_LMK_1
WD2_LMK1_CLKOUT_DIV_MASK                 =                        0x0000FF00
WD2_LMK1_CLKOUT_DIV_OFS                  =                                 8

# LMK1_CLKOUT_DLY - Channel 1 Clock Output Delay (value x 150ps)
WD2_LMK1_CLKOUT_DLY_REG                  =                     WD2_REG_LMK_1
WD2_LMK1_CLKOUT_DLY_MASK                 =                        0x000000F0
WD2_LMK1_CLKOUT_DLY_OFS                  =                                 4



# ****** Control Register 57 [0x10E4]: LMK_2 - LMK Register 2 (Default: 0x00020102) ******

# LMK2_CLKOUT_MUX - Channel 2 Clock Output Multiplexer (see datasheet)
WD2_LMK2_CLKOUT_MUX_REG                  =                     WD2_REG_LMK_2
WD2_LMK2_CLKOUT_MUX_MASK                 =                        0x00060000
WD2_LMK2_CLKOUT_MUX_OFS                  =                                17

# LMK2_CLKOUT_EN - Channel 2 Clock Output Enable (0 = Disabled, 1 = Enabled)
WD2_LMK2_CLKOUT_EN_REG                   =                     WD2_REG_LMK_2
WD2_LMK2_CLKOUT_EN_MASK                  =                        0x00010000
WD2_LMK2_CLKOUT_EN_OFS                   =                                16

# LMK2_CLKOUT_DIV - Channel 2 Clock Output Divider (value x 2) (1..255)
WD2_LMK2_CLKOUT_DIV_REG                  =                     WD2_REG_LMK_2
WD2_LMK2_CLKOUT_DIV_MASK                 =                        0x0000FF00
WD2_LMK2_CLKOUT_DIV_OFS                  =                                 8

# LMK2_CLKOUT_DLY - Channel 2 Clock Output Delay (value x 150ps)
WD2_LMK2_CLKOUT_DLY_REG                  =                     WD2_REG_LMK_2
WD2_LMK2_CLKOUT_DLY_MASK                 =                        0x000000F0
WD2_LMK2_CLKOUT_DLY_OFS                  =                                 4



# ****** Control Register 58 [0x10E8]: LMK_3 - LMK Register 3 (Default: 0x00000103) ******

# LMK3_CLKOUT_MUX - Channel 3 Clock Output Multiplexer (see datasheet)
WD2_LMK3_CLKOUT_MUX_REG                  =                     WD2_REG_LMK_3
WD2_LMK3_CLKOUT_MUX_MASK                 =                        0x00060000
WD2_LMK3_CLKOUT_MUX_OFS                  =                                17

# LMK3_CLKOUT_EN - Channel 3 Clock Output Enable (0 = Disabled, 1 = Enabled)
WD2_LMK3_CLKOUT_EN_REG                   =                     WD2_REG_LMK_3
WD2_LMK3_CLKOUT_EN_MASK                  =                        0x00010000
WD2_LMK3_CLKOUT_EN_OFS                   =                                16

# LMK3_CLKOUT_DIV - Channel 3 Clock Output Divider (value x 2) (1..255)
WD2_LMK3_CLKOUT_DIV_REG                  =                     WD2_REG_LMK_3
WD2_LMK3_CLKOUT_DIV_MASK                 =                        0x0000FF00
WD2_LMK3_CLKOUT_DIV_OFS                  =                                 8

# LMK3_CLKOUT_DLY - Channel 3 Clock Output Delay (value x 150ps)
WD2_LMK3_CLKOUT_DLY_REG                  =                     WD2_REG_LMK_3
WD2_LMK3_CLKOUT_DLY_MASK                 =                        0x000000F0
WD2_LMK3_CLKOUT_DLY_OFS                  =                                 4



# ****** Control Register 59 [0x10EC]: LMK_4 - LMK Register 4 (Default: 0x00030104) ******

# LMK4_CLKOUT_MUX - Channel 4 Clock Output Multiplexer (see datasheet)
WD2_LMK4_CLKOUT_MUX_REG                  =                     WD2_REG_LMK_4
WD2_LMK4_CLKOUT_MUX_MASK                 =                        0x00060000
WD2_LMK4_CLKOUT_MUX_OFS                  =                                17

# LMK4_CLKOUT_EN - Channel 4 Clock Output Enable (0 = Disabled, 1 = Enabled)
WD2_LMK4_CLKOUT_EN_REG                   =                     WD2_REG_LMK_4
WD2_LMK4_CLKOUT_EN_MASK                  =                        0x00010000
WD2_LMK4_CLKOUT_EN_OFS                   =                                16

# LMK4_CLKOUT_DIV - Channel 4 Clock Output Divider (value x 2) (1..255)
WD2_LMK4_CLKOUT_DIV_REG                  =                     WD2_REG_LMK_4
WD2_LMK4_CLKOUT_DIV_MASK                 =                        0x0000FF00
WD2_LMK4_CLKOUT_DIV_OFS                  =                                 8

# LMK4_CLKOUT_DLY - Channel 4 Clock Output Delay (value x 150ps)
WD2_LMK4_CLKOUT_DLY_REG                  =                     WD2_REG_LMK_4
WD2_LMK4_CLKOUT_DLY_MASK                 =                        0x000000F0
WD2_LMK4_CLKOUT_DLY_OFS                  =                                 4



# ****** Control Register 60 [0x10F0]: LMK_5 - LMK Register 5 (Default: 0x00020105) ******

# LMK5_CLKOUT_MUX - Channel 5 Clock Output Multiplexer (see datasheet)
WD2_LMK5_CLKOUT_MUX_REG                  =                     WD2_REG_LMK_5
WD2_LMK5_CLKOUT_MUX_MASK                 =                        0x00060000
WD2_LMK5_CLKOUT_MUX_OFS                  =                                17

# LMK5_CLKOUT_EN - Channel 5 Clock Output Enable (0 = Disabled, 1 = Enabled)
WD2_LMK5_CLKOUT_EN_REG                   =                     WD2_REG_LMK_5
WD2_LMK5_CLKOUT_EN_MASK                  =                        0x00010000
WD2_LMK5_CLKOUT_EN_OFS                   =                                16

# LMK5_CLKOUT_DIV - Channel 5 Clock Output Divider (value x 2) (1..255)
WD2_LMK5_CLKOUT_DIV_REG                  =                     WD2_REG_LMK_5
WD2_LMK5_CLKOUT_DIV_MASK                 =                        0x0000FF00
WD2_LMK5_CLKOUT_DIV_OFS                  =                                 8

# LMK5_CLKOUT_DLY - Channel 5 Clock Output Delay (value x 150ps)
WD2_LMK5_CLKOUT_DLY_REG                  =                     WD2_REG_LMK_5
WD2_LMK5_CLKOUT_DLY_MASK                 =                        0x000000F0
WD2_LMK5_CLKOUT_DLY_OFS                  =                                 4



# ****** Control Register 61 [0x10F4]: LMK_6 - LMK Register 6 (Default: 0x00000106) ******

# LMK6_CLKOUT_MUX - Channel 6 Clock Output Multiplexer (see datasheet)
WD2_LMK6_CLKOUT_MUX_REG                  =                     WD2_REG_LMK_6
WD2_LMK6_CLKOUT_MUX_MASK                 =                        0x00060000
WD2_LMK6_CLKOUT_MUX_OFS                  =                                17

# LMK6_CLKOUT_EN - Channel 6 Clock Output Enable (0 = Disabled, 1 = Enabled)
WD2_LMK6_CLKOUT_EN_REG                   =                     WD2_REG_LMK_6
WD2_LMK6_CLKOUT_EN_MASK                  =                        0x00010000
WD2_LMK6_CLKOUT_EN_OFS                   =                                16

# LMK6_CLKOUT_DIV - Channel 6 Clock Output Divider (value x 2) (1..255)
WD2_LMK6_CLKOUT_DIV_REG                  =                     WD2_REG_LMK_6
WD2_LMK6_CLKOUT_DIV_MASK                 =                        0x0000FF00
WD2_LMK6_CLKOUT_DIV_OFS                  =                                 8

# LMK6_CLKOUT_DLY - Channel 6 Clock Output Delay (value x 150ps)
WD2_LMK6_CLKOUT_DLY_REG                  =                     WD2_REG_LMK_6
WD2_LMK6_CLKOUT_DLY_MASK                 =                        0x000000F0
WD2_LMK6_CLKOUT_DLY_OFS                  =                                 4



# ****** Control Register 62 [0x10F8]: LMK_7 - LMK Register 7 (Default: 0x00026407) ******

# LMK7_CLKOUT_MUX - Channel 7 Clock Output Multiplexer (see datasheet)
WD2_LMK7_CLKOUT_MUX_REG                  =                     WD2_REG_LMK_7
WD2_LMK7_CLKOUT_MUX_MASK                 =                        0x00060000
WD2_LMK7_CLKOUT_MUX_OFS                  =                                17

# LMK7_CLKOUT_EN - Channel 7 Clock Output Enable (0 = Disabled, 1 = Enabled)
WD2_LMK7_CLKOUT_EN_REG                   =                     WD2_REG_LMK_7
WD2_LMK7_CLKOUT_EN_MASK                  =                        0x00010000
WD2_LMK7_CLKOUT_EN_OFS                   =                                16

# LMK7_CLKOUT_DIV - Channel 7 Clock Output Divider (value x 2) (1..255)
WD2_LMK7_CLKOUT_DIV_REG                  =                     WD2_REG_LMK_7
WD2_LMK7_CLKOUT_DIV_MASK                 =                        0x0000FF00
WD2_LMK7_CLKOUT_DIV_OFS                  =                                 8

# LMK7_CLKOUT_DLY - Channel 7 Clock Output Delay (value x 150ps)
WD2_LMK7_CLKOUT_DLY_REG                  =                     WD2_REG_LMK_7
WD2_LMK7_CLKOUT_DLY_MASK                 =                        0x000000F0
WD2_LMK7_CLKOUT_DLY_OFS                  =                                 4



# ****** Control Register 63 [0x10FC]: LMK_8 - LMK Register 8 (Default: 0x10000908) ******

# LMK8_PHASE_NOISE_OPT - Set LMK Register 8 (Phase Noise Optimization)
WD2_LMK8_PHASE_NOISE_OPT_REG             =                     WD2_REG_LMK_8
WD2_LMK8_PHASE_NOISE_OPT_MASK            =                        0xFFFFFFF0
WD2_LMK8_PHASE_NOISE_OPT_OFS             =                                 4



# ****** Control Register 64 [0x1100]: LMK_9 - LMK Register 9 (Default: 0xA0022A09) ******

# LMK9_VBOOST - Voltage Level Boost for Clock Outputs
WD2_LMK9_VBOOST_REG                      =                     WD2_REG_LMK_9
WD2_LMK9_VBOOST_MASK                     =                        0x00010000
WD2_LMK9_VBOOST_OFS                      =                                16



# ****** Control Register 65 [0x1104]: LMK_11 - LMK Register 11 (Default: 0x0082000B) ******

# LMK11_DIV4 - Divider Enable for Digital Lock Detect Circuit
WD2_LMK11_DIV4_REG                       =                    WD2_REG_LMK_11
WD2_LMK11_DIV4_MASK                      =                        0x00008000
WD2_LMK11_DIV4_OFS                       =                                15



# ****** Control Register 66 [0x1108]: LMK_13 - LMK Register 13 (Default: 0x029400AD) ******

# LMK13_OSCIN_FREQ - Oscillator Input Calibration Adjustment in MHz (1..200)
WD2_LMK13_OSCIN_FREQ_REG                 =                    WD2_REG_LMK_13
WD2_LMK13_OSCIN_FREQ_MASK                =                        0x003FC000
WD2_LMK13_OSCIN_FREQ_OFS                 =                                14

# LMK13_VCO_R4_LF - Value for Internal Loop Filter Resistor R4 (0..4) (see datasheet)
WD2_LMK13_VCO_R4_LF_REG                  =                    WD2_REG_LMK_13
WD2_LMK13_VCO_R4_LF_MASK                 =                        0x00003800
WD2_LMK13_VCO_R4_LF_OFS                  =                                11

# LMK13_VCO_R3_LF - Value for Internal Loop Filter Resistor R3 (0..4) (see datasheet)
WD2_LMK13_VCO_R3_LF_REG                  =                    WD2_REG_LMK_13
WD2_LMK13_VCO_R3_LF_MASK                 =                        0x00000700
WD2_LMK13_VCO_R3_LF_OFS                  =                                 8

# LMK13_VCO_C3_C4_LF - Value for Internal Loop Filter Capacitors C3/C4 (0..11) (see ds)
WD2_LMK13_VCO_C3_C4_LF_REG               =                    WD2_REG_LMK_13
WD2_LMK13_VCO_C3_C4_LF_MASK              =                        0x000000F0
WD2_LMK13_VCO_C3_C4_LF_OFS               =                                 4



# ****** Control Register 67 [0x110C]: LMK_14 - LMK Register 14 (Default: 0x0830100E) ******

# LMK14_EN_FOUT - Enable for the Fout Pin (0 = Disabled, 1 = Enabled)
WD2_LMK14_EN_FOUT_REG                    =                    WD2_REG_LMK_14
WD2_LMK14_EN_FOUT_MASK                   =                        0x10000000
WD2_LMK14_EN_FOUT_OFS                    =                                28

# LMK14_EN_CLKOUT_GLOBAL - Global Clock Output Enable (0 = All Off, 1 = Normal Operation)
WD2_LMK14_EN_CLKOUT_GLOBAL_REG           =                    WD2_REG_LMK_14
WD2_LMK14_EN_CLKOUT_GLOBAL_MASK          =                        0x08000000
WD2_LMK14_EN_CLKOUT_GLOBAL_OFS           =                                27

# LMK14_POWERDOWN - Powerdown (0 = Normal Operation, 1 = Device Powered Down)
WD2_LMK14_POWERDOWN_REG                  =                    WD2_REG_LMK_14
WD2_LMK14_POWERDOWN_MASK                 =                        0x04000000
WD2_LMK14_POWERDOWN_OFS                  =                                26

# LMK14_PLL_MUX - Output Mode of  LD Pin (0..7,9,11)
WD2_LMK14_PLL_MUX_REG                    =                    WD2_REG_LMK_14
WD2_LMK14_PLL_MUX_MASK                   =                        0x00F00000
WD2_LMK14_PLL_MUX_OFS                    =                                20

# LMK14_PLL_R - PLL R Divider Value (1..4095)
WD2_LMK14_PLL_R_REG                      =                    WD2_REG_LMK_14
WD2_LMK14_PLL_R_MASK                     =                        0x000FFF00
WD2_LMK14_PLL_R_OFS                      =                                 8



# ****** Control Register 68 [0x1110]: LMK_15 - LMK Register 15 (Default: 0xE000200F) ******

# LMK15_PLL_CP_GAIN - PLL Charge Pump Gain (see datasheet) (0..4)
WD2_LMK15_PLL_CP_GAIN_REG                =                    WD2_REG_LMK_15
WD2_LMK15_PLL_CP_GAIN_MASK               =                        0xC0000000
WD2_LMK15_PLL_CP_GAIN_OFS                =                                30

# LMK15_VCO_DIV - VCO Divider Value (2..8)
WD2_LMK15_VCO_DIV_REG                    =                    WD2_REG_LMK_15
WD2_LMK15_VCO_DIV_MASK                   =                        0x3C000000
WD2_LMK15_VCO_DIV_OFS                    =                                26

# LMK15_PLL_N - PLL N Divider Value (1..0x3FFFF)
WD2_LMK15_PLL_N_REG                      =                    WD2_REG_LMK_15
WD2_LMK15_PLL_N_MASK                     =                        0x03FFFF00
WD2_LMK15_PLL_N_OFS                      =                                 8



# ****** Control Register 69 [0x1114]: ADC_0_CFG_1458 - ADC 0 (A) Chip Configuration for channels 1, 4, 5 and 8 (Default: 0x00F63F00) ******

# ADC_0_1458_DCSOFF - Clock Duty Cycle Stabilizer (0=ON, 1=OFF)
WD2_ADC_0_1458_DCSOFF_REG                =            WD2_REG_ADC_0_CFG_1458
WD2_ADC_0_1458_DCSOFF_MASK               =                        0x80000000
WD2_ADC_0_1458_DCSOFF_OFS                =                                31

# ADC_0_1458_RAND - Data Output Randomizer Mode Control Bit (0=OFF, 1=ON)
WD2_ADC_0_1458_RAND_REG                  =            WD2_REG_ADC_0_CFG_1458
WD2_ADC_0_1458_RAND_MASK                 =                        0x40000000
WD2_ADC_0_1458_RAND_OFS                  =                                30

# ADC_0_1458_TWOSCOMP - Two's Complement Mode Control Bit (0=Offset Binary, 1=Two's Complement)
WD2_ADC_0_1458_TWOSCOMP_REG              =            WD2_REG_ADC_0_CFG_1458
WD2_ADC_0_1458_TWOSCOMP_MASK             =                        0x20000000
WD2_ADC_0_1458_TWOSCOMP_OFS              =                                29

# ADC_0_1458_SLEEP - Sleep Mode (1=Channels 1, 4, 5 and 8 are disabled)
WD2_ADC_0_1458_SLEEP_REG                 =            WD2_REG_ADC_0_CFG_1458
WD2_ADC_0_1458_SLEEP_MASK                =                        0x10000000
WD2_ADC_0_1458_SLEEP_OFS                 =                                28

# ADC_0_8_NAP_MODE - Channel 8 Nap Mode (0=OFF, 1=ON)
WD2_ADC_0_8_NAP_MODE_REG                 =            WD2_REG_ADC_0_CFG_1458
WD2_ADC_0_8_NAP_MODE_MASK                =                        0x08000000
WD2_ADC_0_8_NAP_MODE_OFS                 =                                27

# ADC_0_5_NAP_MODE - Channel 5 Nap Mode (0=OFF, 1=ON)
WD2_ADC_0_5_NAP_MODE_REG                 =            WD2_REG_ADC_0_CFG_1458
WD2_ADC_0_5_NAP_MODE_MASK                =                        0x04000000
WD2_ADC_0_5_NAP_MODE_OFS                 =                                26

# ADC_0_4_NAP_MODE - Channel 4 Nap Mode (0=OFF, 1=ON)
WD2_ADC_0_4_NAP_MODE_REG                 =            WD2_REG_ADC_0_CFG_1458
WD2_ADC_0_4_NAP_MODE_MASK                =                        0x02000000
WD2_ADC_0_4_NAP_MODE_OFS                 =                                25

# ADC_0_1_NAP_MODE - Channel 1 Nap Mode (0=OFF, 1=ON)
WD2_ADC_0_1_NAP_MODE_REG                 =            WD2_REG_ADC_0_CFG_1458
WD2_ADC_0_1_NAP_MODE_MASK                =                        0x01000000
WD2_ADC_0_1_NAP_MODE_OFS                 =                                24

# ADC_0_1458_ILVDS - LVDS Output Current Bits (1.75mA - 4.5mA, 0b111 = 2x1.75mA = 3.5mA) (see datasheet)
WD2_ADC_0_1458_ILVDS_REG                 =            WD2_REG_ADC_0_CFG_1458
WD2_ADC_0_1458_ILVDS_MASK                =                        0x00E00000
WD2_ADC_0_1458_ILVDS_OFS                 =                                21

# ADC_0_1458_TERMON - LVDS Internal Termination Bit (0=OFF, 1=ON)
WD2_ADC_0_1458_TERMON_REG                =            WD2_REG_ADC_0_CFG_1458
WD2_ADC_0_1458_TERMON_MASK               =                        0x00100000
WD2_ADC_0_1458_TERMON_OFS                =                                20

# ADC_0_1458_OUTOFF - Digital Output Disable Bit (0=Enabled, 1=Disabled)
WD2_ADC_0_1458_OUTOFF_REG                =            WD2_REG_ADC_0_CFG_1458
WD2_ADC_0_1458_OUTOFF_MASK               =                        0x00080000
WD2_ADC_0_1458_OUTOFF_OFS                =                                19

# ADC_0_1458_OUTMODE - Digital Output Mode Control Bits (0b110 = 12 Bit, 1 Lane) (see datasheet) 
WD2_ADC_0_1458_OUTMODE_REG               =            WD2_REG_ADC_0_CFG_1458
WD2_ADC_0_1458_OUTMODE_MASK              =                        0x00070000
WD2_ADC_0_1458_OUTMODE_OFS               =                                16

# ADC_0_1458_OUTTEST - Output Test Pattern Control Bit (0=Pattern Off, 1=Pattern On)
WD2_ADC_0_1458_OUTTEST_REG               =            WD2_REG_ADC_0_CFG_1458
WD2_ADC_0_1458_OUTTEST_MASK              =                        0x00008000
WD2_ADC_0_1458_OUTTEST_OFS               =                                15

# ADC_0_1458_TP - Test Pattern MSBs (actual test pattern in 12 bit mode)
WD2_ADC_0_1458_TP_REG                    =            WD2_REG_ADC_0_CFG_1458
WD2_ADC_0_1458_TP_MASK                   =                        0x00003FFC
WD2_ADC_0_1458_TP_OFS                    =                                 2

# ADC_0_1458_TP_LSBS - Test Pattern LSBs
WD2_ADC_0_1458_TP_LSBS_REG               =            WD2_REG_ADC_0_CFG_1458
WD2_ADC_0_1458_TP_LSBS_MASK              =                        0x00000003
WD2_ADC_0_1458_TP_LSBS_OFS               =                                 0



# ****** Control Register 70 [0x1118]: ADC_0_CFG_2367 - ADC 0 (A) Chip Configuration for channels 2, 3, 6 and 7 (Default: 0x00F63F00) ******

# ADC_0_2367_DCSOFF - Clock Duty Cycle Stabilizer (0=ON, 1=OFF)
WD2_ADC_0_2367_DCSOFF_REG                =            WD2_REG_ADC_0_CFG_2367
WD2_ADC_0_2367_DCSOFF_MASK               =                        0x80000000
WD2_ADC_0_2367_DCSOFF_OFS                =                                31

# ADC_0_2367_RAND - Data Output Randomizer Mode Control Bit (0=OFF, 1=ON)
WD2_ADC_0_2367_RAND_REG                  =            WD2_REG_ADC_0_CFG_2367
WD2_ADC_0_2367_RAND_MASK                 =                        0x40000000
WD2_ADC_0_2367_RAND_OFS                  =                                30

# ADC_0_2367_TWOSCOMP - Two's Complement Mode Control Bit (0=Offset Binary, 1=Two's Complement)
WD2_ADC_0_2367_TWOSCOMP_REG              =            WD2_REG_ADC_0_CFG_2367
WD2_ADC_0_2367_TWOSCOMP_MASK             =                        0x20000000
WD2_ADC_0_2367_TWOSCOMP_OFS              =                                29

# ADC_0_2367_SLEEP - Sleep Mode (1=Channels 2, 3, 6 and 7 are disabled)
WD2_ADC_0_2367_SLEEP_REG                 =            WD2_REG_ADC_0_CFG_2367
WD2_ADC_0_2367_SLEEP_MASK                =                        0x10000000
WD2_ADC_0_2367_SLEEP_OFS                 =                                28

# ADC_0_7_NAP_MODE - Channel 7 Nap Mode (0=OFF, 1=ON)
WD2_ADC_0_7_NAP_MODE_REG                 =            WD2_REG_ADC_0_CFG_2367
WD2_ADC_0_7_NAP_MODE_MASK                =                        0x08000000
WD2_ADC_0_7_NAP_MODE_OFS                 =                                27

# ADC_0_6_NAP_MODE - Channel 6 Nap Mode (0=OFF, 1=ON)
WD2_ADC_0_6_NAP_MODE_REG                 =            WD2_REG_ADC_0_CFG_2367
WD2_ADC_0_6_NAP_MODE_MASK                =                        0x04000000
WD2_ADC_0_6_NAP_MODE_OFS                 =                                26

# ADC_0_3_NAP_MODE - Channel 3 Nap Mode (0=OFF, 1=ON)
WD2_ADC_0_3_NAP_MODE_REG                 =            WD2_REG_ADC_0_CFG_2367
WD2_ADC_0_3_NAP_MODE_MASK                =                        0x02000000
WD2_ADC_0_3_NAP_MODE_OFS                 =                                25

# ADC_0_2_NAP_MODE - Channel 2 Nap Mode (0=OFF, 1=ON)
WD2_ADC_0_2_NAP_MODE_REG                 =            WD2_REG_ADC_0_CFG_2367
WD2_ADC_0_2_NAP_MODE_MASK                =                        0x01000000
WD2_ADC_0_2_NAP_MODE_OFS                 =                                24

# ADC_0_2367_ILVDS - LVDS Output Current Bits (1.75mA - 4.5mA, 0b111 = 2x1.75mA = 3.5mA) (see datasheet)
WD2_ADC_0_2367_ILVDS_REG                 =            WD2_REG_ADC_0_CFG_2367
WD2_ADC_0_2367_ILVDS_MASK                =                        0x00E00000
WD2_ADC_0_2367_ILVDS_OFS                 =                                21

# ADC_0_2367_TERMON - LVDS Internal Termination Bit (0=OFF, 1=ON)
WD2_ADC_0_2367_TERMON_REG                =            WD2_REG_ADC_0_CFG_2367
WD2_ADC_0_2367_TERMON_MASK               =                        0x00100000
WD2_ADC_0_2367_TERMON_OFS                =                                20

# ADC_0_2367_OUTOFF - Digital Output Disable Bit (0=Enabled, 1=Disabled)
WD2_ADC_0_2367_OUTOFF_REG                =            WD2_REG_ADC_0_CFG_2367
WD2_ADC_0_2367_OUTOFF_MASK               =                        0x00080000
WD2_ADC_0_2367_OUTOFF_OFS                =                                19

# ADC_0_2367_OUTMODE - Digital Output Mode Control Bits (0b110 = 12 Bit, 1 Lane) (see datasheet) 
WD2_ADC_0_2367_OUTMODE_REG               =            WD2_REG_ADC_0_CFG_2367
WD2_ADC_0_2367_OUTMODE_MASK              =                        0x00070000
WD2_ADC_0_2367_OUTMODE_OFS               =                                16

# ADC_0_2367_OUTTEST - Output Test Pattern Control Bit (0=Pattern Off, 1=Pattern On)
WD2_ADC_0_2367_OUTTEST_REG               =            WD2_REG_ADC_0_CFG_2367
WD2_ADC_0_2367_OUTTEST_MASK              =                        0x00008000
WD2_ADC_0_2367_OUTTEST_OFS               =                                15

# ADC_0_2367_TP - Test Pattern MSBs (actual test pattern in 12 bit mode)
WD2_ADC_0_2367_TP_REG                    =            WD2_REG_ADC_0_CFG_2367
WD2_ADC_0_2367_TP_MASK                   =                        0x00003FFC
WD2_ADC_0_2367_TP_OFS                    =                                 2

# ADC_0_2367_TP_LSBS - Test Pattern LSBs
WD2_ADC_0_2367_TP_LSBS_REG               =            WD2_REG_ADC_0_CFG_2367
WD2_ADC_0_2367_TP_LSBS_MASK              =                        0x00000003
WD2_ADC_0_2367_TP_LSBS_OFS               =                                 0



# ****** Control Register 71 [0x111C]: ADC_1_CFG_1458 - ADC 1 (B) Chip Configuration for channels 1, 4, 5 and 8 (Default: 0x00F63F00) ******

# ADC_1_1458_DCSOFF - Clock Duty Cycle Stabilizer (0=ON, 1=OFF)
WD2_ADC_1_1458_DCSOFF_REG                =            WD2_REG_ADC_1_CFG_1458
WD2_ADC_1_1458_DCSOFF_MASK               =                        0x80000000
WD2_ADC_1_1458_DCSOFF_OFS                =                                31

# ADC_1_1458_RAND - Data Output Randomizer Mode Control Bit (0=OFF, 1=ON)
WD2_ADC_1_1458_RAND_REG                  =            WD2_REG_ADC_1_CFG_1458
WD2_ADC_1_1458_RAND_MASK                 =                        0x40000000
WD2_ADC_1_1458_RAND_OFS                  =                                30

# ADC_1_1458_TWOSCOMP - Two's Complement Mode Control Bit (0=Offset Binary, 1=Two's Complement)
WD2_ADC_1_1458_TWOSCOMP_REG              =            WD2_REG_ADC_1_CFG_1458
WD2_ADC_1_1458_TWOSCOMP_MASK             =                        0x20000000
WD2_ADC_1_1458_TWOSCOMP_OFS              =                                29

# ADC_1_1458_SLEEP - Sleep Mode (1=Channels 1, 4, 5 and 8 are disabled)
WD2_ADC_1_1458_SLEEP_REG                 =            WD2_REG_ADC_1_CFG_1458
WD2_ADC_1_1458_SLEEP_MASK                =                        0x10000000
WD2_ADC_1_1458_SLEEP_OFS                 =                                28

# ADC_1_8_NAP_MODE - Channel 8 Nap Mode (0=OFF, 1=ON)
WD2_ADC_1_8_NAP_MODE_REG                 =            WD2_REG_ADC_1_CFG_1458
WD2_ADC_1_8_NAP_MODE_MASK                =                        0x08000000
WD2_ADC_1_8_NAP_MODE_OFS                 =                                27

# ADC_1_5_NAP_MODE - Channel 5 Nap Mode (0=OFF, 1=ON)
WD2_ADC_1_5_NAP_MODE_REG                 =            WD2_REG_ADC_1_CFG_1458
WD2_ADC_1_5_NAP_MODE_MASK                =                        0x04000000
WD2_ADC_1_5_NAP_MODE_OFS                 =                                26

# ADC_1_4_NAP_MODE - Channel 4 Nap Mode (0=OFF, 1=ON)
WD2_ADC_1_4_NAP_MODE_REG                 =            WD2_REG_ADC_1_CFG_1458
WD2_ADC_1_4_NAP_MODE_MASK                =                        0x02000000
WD2_ADC_1_4_NAP_MODE_OFS                 =                                25

# ADC_1_1_NAP_MODE - Channel 1 Nap Mode (0=OFF, 1=ON)
WD2_ADC_1_1_NAP_MODE_REG                 =            WD2_REG_ADC_1_CFG_1458
WD2_ADC_1_1_NAP_MODE_MASK                =                        0x01000000
WD2_ADC_1_1_NAP_MODE_OFS                 =                                24

# ADC_1_1458_ILVDS - LVDS Output Current Bits (1.75mA - 4.5mA, 0b111 = 2x1.75mA = 3.5mA) (see datasheet)
WD2_ADC_1_1458_ILVDS_REG                 =            WD2_REG_ADC_1_CFG_1458
WD2_ADC_1_1458_ILVDS_MASK                =                        0x00E00000
WD2_ADC_1_1458_ILVDS_OFS                 =                                21

# ADC_1_1458_TERMON - LVDS Internal Termination Bit (0=OFF, 1=ON)
WD2_ADC_1_1458_TERMON_REG                =            WD2_REG_ADC_1_CFG_1458
WD2_ADC_1_1458_TERMON_MASK               =                        0x00100000
WD2_ADC_1_1458_TERMON_OFS                =                                20

# ADC_1_1458_OUTOFF - Digital Output Disable Bit (0=Enabled, 1=Disabled)
WD2_ADC_1_1458_OUTOFF_REG                =            WD2_REG_ADC_1_CFG_1458
WD2_ADC_1_1458_OUTOFF_MASK               =                        0x00080000
WD2_ADC_1_1458_OUTOFF_OFS                =                                19

# ADC_1_1458_OUTMODE - Digital Output Mode Control Bits (0b110 = 12 Bit, 1 Lane) (see datasheet) 
WD2_ADC_1_1458_OUTMODE_REG               =            WD2_REG_ADC_1_CFG_1458
WD2_ADC_1_1458_OUTMODE_MASK              =                        0x00070000
WD2_ADC_1_1458_OUTMODE_OFS               =                                16

# ADC_1_1458_OUTTEST - Output Test Pattern Control Bit (0=Pattern Off, 1=Pattern On)
WD2_ADC_1_1458_OUTTEST_REG               =            WD2_REG_ADC_1_CFG_1458
WD2_ADC_1_1458_OUTTEST_MASK              =                        0x00008000
WD2_ADC_1_1458_OUTTEST_OFS               =                                15

# ADC_1_1458_TP - Test Pattern MSBs (actual test pattern in 12 bit mode)
WD2_ADC_1_1458_TP_REG                    =            WD2_REG_ADC_1_CFG_1458
WD2_ADC_1_1458_TP_MASK                   =                        0x00003FFC
WD2_ADC_1_1458_TP_OFS                    =                                 2

# ADC_1_1458_TP_LSBS - Test Pattern LSBs
WD2_ADC_1_1458_TP_LSBS_REG               =            WD2_REG_ADC_1_CFG_1458
WD2_ADC_1_1458_TP_LSBS_MASK              =                        0x00000003
WD2_ADC_1_1458_TP_LSBS_OFS               =                                 0



# ****** Control Register 72 [0x1120]: ADC_1_CFG_2367 - ADC 1 (B) Chip Configuration for channels 2, 3, 6 and 7 (Default: 0x00F63F00) ******

# ADC_1_2367_DCSOFF - Clock Duty Cycle Stabilizer (0=ON, 1=OFF)
WD2_ADC_1_2367_DCSOFF_REG                =            WD2_REG_ADC_1_CFG_2367
WD2_ADC_1_2367_DCSOFF_MASK               =                        0x80000000
WD2_ADC_1_2367_DCSOFF_OFS                =                                31

# ADC_1_2367_RAND - Data Output Randomizer Mode Control Bit (0=OFF, 1=ON)
WD2_ADC_1_2367_RAND_REG                  =            WD2_REG_ADC_1_CFG_2367
WD2_ADC_1_2367_RAND_MASK                 =                        0x40000000
WD2_ADC_1_2367_RAND_OFS                  =                                30

# ADC_1_2367_TWOSCOMP - Two's Complement Mode Control Bit (0=Offset Binary, 1=Two's Complement)
WD2_ADC_1_2367_TWOSCOMP_REG              =            WD2_REG_ADC_1_CFG_2367
WD2_ADC_1_2367_TWOSCOMP_MASK             =                        0x20000000
WD2_ADC_1_2367_TWOSCOMP_OFS              =                                29

# ADC_1_2367_SLEEP - Sleep Mode (1=Channels 2, 3, 6 and 7 are disabled)
WD2_ADC_1_2367_SLEEP_REG                 =            WD2_REG_ADC_1_CFG_2367
WD2_ADC_1_2367_SLEEP_MASK                =                        0x10000000
WD2_ADC_1_2367_SLEEP_OFS                 =                                28

# ADC_1_7_NAP_MODE - Channel 7 Nap Mode (0=OFF, 1=ON)
WD2_ADC_1_7_NAP_MODE_REG                 =            WD2_REG_ADC_1_CFG_2367
WD2_ADC_1_7_NAP_MODE_MASK                =                        0x08000000
WD2_ADC_1_7_NAP_MODE_OFS                 =                                27

# ADC_1_6_NAP_MODE - Channel 6 Nap Mode (0=OFF, 1=ON)
WD2_ADC_1_6_NAP_MODE_REG                 =            WD2_REG_ADC_1_CFG_2367
WD2_ADC_1_6_NAP_MODE_MASK                =                        0x04000000
WD2_ADC_1_6_NAP_MODE_OFS                 =                                26

# ADC_1_3_NAP_MODE - Channel 3 Nap Mode (0=OFF, 1=ON)
WD2_ADC_1_3_NAP_MODE_REG                 =            WD2_REG_ADC_1_CFG_2367
WD2_ADC_1_3_NAP_MODE_MASK                =                        0x02000000
WD2_ADC_1_3_NAP_MODE_OFS                 =                                25

# ADC_1_2_NAP_MODE - Channel 2 Nap Mode (0=OFF, 1=ON)
WD2_ADC_1_2_NAP_MODE_REG                 =            WD2_REG_ADC_1_CFG_2367
WD2_ADC_1_2_NAP_MODE_MASK                =                        0x01000000
WD2_ADC_1_2_NAP_MODE_OFS                 =                                24

# ADC_1_2367_ILVDS - LVDS Output Current Bits (1.75mA - 4.5mA, 0b111 = 2x1.75mA = 3.5mA) (see datasheet)
WD2_ADC_1_2367_ILVDS_REG                 =            WD2_REG_ADC_1_CFG_2367
WD2_ADC_1_2367_ILVDS_MASK                =                        0x00E00000
WD2_ADC_1_2367_ILVDS_OFS                 =                                21

# ADC_1_2367_TERMON - LVDS Internal Termination Bit (0=OFF, 1=ON)
WD2_ADC_1_2367_TERMON_REG                =            WD2_REG_ADC_1_CFG_2367
WD2_ADC_1_2367_TERMON_MASK               =                        0x00100000
WD2_ADC_1_2367_TERMON_OFS                =                                20

# ADC_1_2367_OUTOFF - Digital Output Disable Bit (0=Enabled, 1=Disabled)
WD2_ADC_1_2367_OUTOFF_REG                =            WD2_REG_ADC_1_CFG_2367
WD2_ADC_1_2367_OUTOFF_MASK               =                        0x00080000
WD2_ADC_1_2367_OUTOFF_OFS                =                                19

# ADC_1_2367_OUTMODE - Digital Output Mode Control Bits (0b110 = 12 Bit, 1 Lane) (see datasheet) 
WD2_ADC_1_2367_OUTMODE_REG               =            WD2_REG_ADC_1_CFG_2367
WD2_ADC_1_2367_OUTMODE_MASK              =                        0x00070000
WD2_ADC_1_2367_OUTMODE_OFS               =                                16

# ADC_1_2367_OUTTEST - Output Test Pattern Control Bit (0=Pattern Off, 1=Pattern On)
WD2_ADC_1_2367_OUTTEST_REG               =            WD2_REG_ADC_1_CFG_2367
WD2_ADC_1_2367_OUTTEST_MASK              =                        0x00008000
WD2_ADC_1_2367_OUTTEST_OFS               =                                15

# ADC_1_2367_TP - Test Pattern MSBs (actual test pattern in 12 bit mode)
WD2_ADC_1_2367_TP_REG                    =            WD2_REG_ADC_1_CFG_2367
WD2_ADC_1_2367_TP_MASK                   =                        0x00003FFC
WD2_ADC_1_2367_TP_OFS                    =                                 2

# ADC_1_2367_TP_LSBS - Test Pattern LSBs
WD2_ADC_1_2367_TP_LSBS_REG               =            WD2_REG_ADC_1_CFG_2367
WD2_ADC_1_2367_TP_LSBS_MASK              =                        0x00000003
WD2_ADC_1_2367_TP_LSBS_OFS               =                                 0



# ****** Control Register 73 [0x1124]: TRG_CFG - Trigger Configuration (Default: 0x00000000) ******

# TRIGGER_OUT_PULSE_LENGTH - Length of the trigger output pulse in cycles
WD2_TRIGGER_OUT_PULSE_LENGTH_REG         =                   WD2_REG_TRG_CFG
WD2_TRIGGER_OUT_PULSE_LENGTH_MASK        =                        0x1F000000
WD2_TRIGGER_OUT_PULSE_LENGTH_OFS         =                                24

# LEAD_TRAIL_EDGE_SEL - 0 = trigger on leading edge, 1 = trigger on trailing edge
WD2_LEAD_TRAIL_EDGE_SEL_REG              =                   WD2_REG_TRG_CFG
WD2_LEAD_TRAIL_EDGE_SEL_MASK             =                        0x00010000
WD2_LEAD_TRAIL_EDGE_SEL_OFS              =                                16

# EXT_TRIGGER_OUT_ENABLE - Enable output of trigger signal to MCX connector
WD2_EXT_TRIGGER_OUT_ENABLE_REG           =                   WD2_REG_TRG_CFG
WD2_EXT_TRIGGER_OUT_ENABLE_MASK          =                        0x00008000
WD2_EXT_TRIGGER_OUT_ENABLE_OFS           =                                15

# EXT_ASYNC_TRIGGER_EN - Enable asynchronous external trigger
WD2_EXT_ASYNC_TRIGGER_EN_REG             =                   WD2_REG_TRG_CFG
WD2_EXT_ASYNC_TRIGGER_EN_MASK            =                        0x00002000
WD2_EXT_ASYNC_TRIGGER_EN_OFS             =                                13

# PATTERN_TRIGGER_EN - Enable internal (synchronous) pattern trigger
WD2_PATTERN_TRIGGER_EN_REG               =                   WD2_REG_TRG_CFG
WD2_PATTERN_TRIGGER_EN_MASK              =                        0x00001000
WD2_PATTERN_TRIGGER_EN_OFS               =                                12

# TRIGGER_DELAY - trigger delay in ticks of 6.25 ns
WD2_TRIGGER_DELAY_REG                    =                   WD2_REG_TRG_CFG
WD2_TRIGGER_DELAY_MASK                   =                        0x000000FF
WD2_TRIGGER_DELAY_OFS                    =                                 0



# ****** Control Register 74 [0x1128]: TRG_SRC_POL - Trigger Source Polarity (Default: 0x00000000) ******

# TRG_SRC_POLARITY - Polarity of trigger source (0 = normal, 1 = inverted) (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
WD2_TRG_SRC_POLARITY_REG                 =               WD2_REG_TRG_SRC_POL
WD2_TRG_SRC_POLARITY_MASK                =                        0x0007FFFF
WD2_TRG_SRC_POLARITY_OFS                 =                                 0



# ****** Control Register 75 [0x112C]: TRG_AUTO_PERIOD - Automatic Trigger Period (Default: 0x04C4B400) ******

# AUTO_TRIGGER_PERIOD - Period of automatic trigger in ticks of the DAQ clock
WD2_AUTO_TRIGGER_PERIOD_REG              =           WD2_REG_TRG_AUTO_PERIOD
WD2_AUTO_TRIGGER_PERIOD_MASK             =                        0xFFFFFFFF
WD2_AUTO_TRIGGER_PERIOD_OFS              =                                 0



# ****** Control Register 76 [0x1130]: TRG_PTRN_EN - Enable for trigger patterns (Default: 0x00000000) ******

# TRG_PTRN_EN - 1 enables the corresponding trigger patterns for the local trigger
WD2_TRG_PTRN_EN_REG                      =               WD2_REG_TRG_PTRN_EN
WD2_TRG_PTRN_EN_MASK                     =                        0x0007FFFF
WD2_TRG_PTRN_EN_OFS                      =                                 0



# ****** Control Register 77 [0x1134]: TRG_SRC_EN_PTRN0 - Trigger Source Enable Pattern 0 (Default: 0x00000000) ******

# TRG_SRC_EN_PTRN0 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
WD2_TRG_SRC_EN_PTRN0_REG                 =          WD2_REG_TRG_SRC_EN_PTRN0
WD2_TRG_SRC_EN_PTRN0_MASK                =                        0x0007FFFF
WD2_TRG_SRC_EN_PTRN0_OFS                 =                                 0



# ****** Control Register 78 [0x1138]: TRG_STATE_PTRN0 - Trigger State Pattern 0 (Default: 0x00000000) ******

# TRG_STATE_PTRN0 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
WD2_TRG_STATE_PTRN0_REG                  =           WD2_REG_TRG_STATE_PTRN0
WD2_TRG_STATE_PTRN0_MASK                 =                        0x0007FFFF
WD2_TRG_STATE_PTRN0_OFS                  =                                 0



# ****** Control Register 79 [0x113C]: TRG_SRC_EN_PTRN1 - Trigger Source Enable Pattern 1 (Default: 0x00000000) ******

# TRG_SRC_EN_PTRN1 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
WD2_TRG_SRC_EN_PTRN1_REG                 =          WD2_REG_TRG_SRC_EN_PTRN1
WD2_TRG_SRC_EN_PTRN1_MASK                =                        0x0007FFFF
WD2_TRG_SRC_EN_PTRN1_OFS                 =                                 0



# ****** Control Register 80 [0x1140]: TRG_STATE_PTRN1 - Trigger State Pattern 1 (Default: 0x00000000) ******

# TRG_STATE_PTRN1 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
WD2_TRG_STATE_PTRN1_REG                  =           WD2_REG_TRG_STATE_PTRN1
WD2_TRG_STATE_PTRN1_MASK                 =                        0x0007FFFF
WD2_TRG_STATE_PTRN1_OFS                  =                                 0



# ****** Control Register 81 [0x1144]: TRG_SRC_EN_PTRN2 - Trigger Source Enable Pattern 2 (Default: 0x00000000) ******

# TRG_SRC_EN_PTRN2 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
WD2_TRG_SRC_EN_PTRN2_REG                 =          WD2_REG_TRG_SRC_EN_PTRN2
WD2_TRG_SRC_EN_PTRN2_MASK                =                        0x0007FFFF
WD2_TRG_SRC_EN_PTRN2_OFS                 =                                 0



# ****** Control Register 82 [0x1148]: TRG_STATE_PTRN2 - Trigger State Pattern 2 (Default: 0x00000000) ******

# TRG_STATE_PTRN2 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
WD2_TRG_STATE_PTRN2_REG                  =           WD2_REG_TRG_STATE_PTRN2
WD2_TRG_STATE_PTRN2_MASK                 =                        0x0007FFFF
WD2_TRG_STATE_PTRN2_OFS                  =                                 0



# ****** Control Register 83 [0x114C]: TRG_SRC_EN_PTRN3 - Trigger Source Enable Pattern 3 (Default: 0x00000000) ******

# TRG_SRC_EN_PTRN3 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
WD2_TRG_SRC_EN_PTRN3_REG                 =          WD2_REG_TRG_SRC_EN_PTRN3
WD2_TRG_SRC_EN_PTRN3_MASK                =                        0x0007FFFF
WD2_TRG_SRC_EN_PTRN3_OFS                 =                                 0



# ****** Control Register 84 [0x1150]: TRG_STATE_PTRN3 - Trigger State Pattern 3 (Default: 0x00000000) ******

# TRG_STATE_PTRN3 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
WD2_TRG_STATE_PTRN3_REG                  =           WD2_REG_TRG_STATE_PTRN3
WD2_TRG_STATE_PTRN3_MASK                 =                        0x0007FFFF
WD2_TRG_STATE_PTRN3_OFS                  =                                 0



# ****** Control Register 85 [0x1154]: TRG_SRC_EN_PTRN4 - Trigger Source Enable Pattern 4 (Default: 0x00000000) ******

# TRG_SRC_EN_PTRN4 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
WD2_TRG_SRC_EN_PTRN4_REG                 =          WD2_REG_TRG_SRC_EN_PTRN4
WD2_TRG_SRC_EN_PTRN4_MASK                =                        0x0007FFFF
WD2_TRG_SRC_EN_PTRN4_OFS                 =                                 0



# ****** Control Register 86 [0x1158]: TRG_STATE_PTRN4 - Trigger State Pattern 4 (Default: 0x00000000) ******

# TRG_STATE_PTRN4 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
WD2_TRG_STATE_PTRN4_REG                  =           WD2_REG_TRG_STATE_PTRN4
WD2_TRG_STATE_PTRN4_MASK                 =                        0x0007FFFF
WD2_TRG_STATE_PTRN4_OFS                  =                                 0



# ****** Control Register 87 [0x115C]: TRG_SRC_EN_PTRN5 - Trigger Source Enable Pattern 5 (Default: 0x00000000) ******

# TRG_SRC_EN_PTRN5 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
WD2_TRG_SRC_EN_PTRN5_REG                 =          WD2_REG_TRG_SRC_EN_PTRN5
WD2_TRG_SRC_EN_PTRN5_MASK                =                        0x0007FFFF
WD2_TRG_SRC_EN_PTRN5_OFS                 =                                 0



# ****** Control Register 88 [0x1160]: TRG_STATE_PTRN5 - Trigger State Pattern 5 (Default: 0x00000000) ******

# TRG_STATE_PTRN5 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
WD2_TRG_STATE_PTRN5_REG                  =           WD2_REG_TRG_STATE_PTRN5
WD2_TRG_STATE_PTRN5_MASK                 =                        0x0007FFFF
WD2_TRG_STATE_PTRN5_OFS                  =                                 0



# ****** Control Register 89 [0x1164]: TRG_SRC_EN_PTRN6 - Trigger Source Enable Pattern 6 (Default: 0x00000000) ******

# TRG_SRC_EN_PTRN6 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
WD2_TRG_SRC_EN_PTRN6_REG                 =          WD2_REG_TRG_SRC_EN_PTRN6
WD2_TRG_SRC_EN_PTRN6_MASK                =                        0x0007FFFF
WD2_TRG_SRC_EN_PTRN6_OFS                 =                                 0



# ****** Control Register 90 [0x1168]: TRG_STATE_PTRN6 - Trigger State Pattern 6 (Default: 0x00000000) ******

# TRG_STATE_PTRN6 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
WD2_TRG_STATE_PTRN6_REG                  =           WD2_REG_TRG_STATE_PTRN6
WD2_TRG_STATE_PTRN6_MASK                 =                        0x0007FFFF
WD2_TRG_STATE_PTRN6_OFS                  =                                 0



# ****** Control Register 91 [0x116C]: TRG_SRC_EN_PTRN7 - Trigger Source Enable Pattern 7 (Default: 0x00000000) ******

# TRG_SRC_EN_PTRN7 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
WD2_TRG_SRC_EN_PTRN7_REG                 =          WD2_REG_TRG_SRC_EN_PTRN7
WD2_TRG_SRC_EN_PTRN7_MASK                =                        0x0007FFFF
WD2_TRG_SRC_EN_PTRN7_OFS                 =                                 0



# ****** Control Register 92 [0x1170]: TRG_STATE_PTRN7 - Trigger State Pattern 7 (Default: 0x00000000) ******

# TRG_STATE_PTRN7 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
WD2_TRG_STATE_PTRN7_REG                  =           WD2_REG_TRG_STATE_PTRN7
WD2_TRG_STATE_PTRN7_MASK                 =                        0x0007FFFF
WD2_TRG_STATE_PTRN7_OFS                  =                                 0



# ****** Control Register 93 [0x1174]: TRG_SRC_EN_PTRN8 - Trigger Source Enable Pattern 8 (Default: 0x00000000) ******

# TRG_SRC_EN_PTRN8 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
WD2_TRG_SRC_EN_PTRN8_REG                 =          WD2_REG_TRG_SRC_EN_PTRN8
WD2_TRG_SRC_EN_PTRN8_MASK                =                        0x0007FFFF
WD2_TRG_SRC_EN_PTRN8_OFS                 =                                 0



# ****** Control Register 94 [0x1178]: TRG_STATE_PTRN8 - Trigger State Pattern 8 (Default: 0x00000000) ******

# TRG_STATE_PTRN8 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
WD2_TRG_STATE_PTRN8_REG                  =           WD2_REG_TRG_STATE_PTRN8
WD2_TRG_STATE_PTRN8_MASK                 =                        0x0007FFFF
WD2_TRG_STATE_PTRN8_OFS                  =                                 0



# ****** Control Register 95 [0x117C]: TRG_SRC_EN_PTRN9 - Trigger Source Enable Pattern 9 (Default: 0x00000000) ******

# TRG_SRC_EN_PTRN9 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
WD2_TRG_SRC_EN_PTRN9_REG                 =          WD2_REG_TRG_SRC_EN_PTRN9
WD2_TRG_SRC_EN_PTRN9_MASK                =                        0x0007FFFF
WD2_TRG_SRC_EN_PTRN9_OFS                 =                                 0



# ****** Control Register 96 [0x1180]: TRG_STATE_PTRN9 - Trigger State Pattern 9 (Default: 0x00000000) ******

# TRG_STATE_PTRN9 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
WD2_TRG_STATE_PTRN9_REG                  =           WD2_REG_TRG_STATE_PTRN9
WD2_TRG_STATE_PTRN9_MASK                 =                        0x0007FFFF
WD2_TRG_STATE_PTRN9_OFS                  =                                 0



# ****** Control Register 97 [0x1184]: TRG_SRC_EN_PTRN10 - Trigger Source Enable Pattern 10 (Default: 0x00000000) ******

# TRG_SRC_EN_PTRN10 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
WD2_TRG_SRC_EN_PTRN10_REG                =         WD2_REG_TRG_SRC_EN_PTRN10
WD2_TRG_SRC_EN_PTRN10_MASK               =                        0x0007FFFF
WD2_TRG_SRC_EN_PTRN10_OFS                =                                 0



# ****** Control Register 98 [0x1188]: TRG_STATE_PTRN10 - Trigger State Pattern 10 (Default: 0x00000000) ******

# TRG_STATE_PTRN10 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
WD2_TRG_STATE_PTRN10_REG                 =          WD2_REG_TRG_STATE_PTRN10
WD2_TRG_STATE_PTRN10_MASK                =                        0x0007FFFF
WD2_TRG_STATE_PTRN10_OFS                 =                                 0



# ****** Control Register 99 [0x118C]: TRG_SRC_EN_PTRN11 - Trigger Source Enable Pattern 11 (Default: 0x00000000) ******

# TRG_SRC_EN_PTRN11 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
WD2_TRG_SRC_EN_PTRN11_REG                =         WD2_REG_TRG_SRC_EN_PTRN11
WD2_TRG_SRC_EN_PTRN11_MASK               =                        0x0007FFFF
WD2_TRG_SRC_EN_PTRN11_OFS                =                                 0



# ****** Control Register 100 [0x1190]: TRG_STATE_PTRN11 - Trigger State Pattern 11 (Default: 0x00000000) ******

# TRG_STATE_PTRN11 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
WD2_TRG_STATE_PTRN11_REG                 =          WD2_REG_TRG_STATE_PTRN11
WD2_TRG_STATE_PTRN11_MASK                =                        0x0007FFFF
WD2_TRG_STATE_PTRN11_OFS                 =                                 0



# ****** Control Register 101 [0x1194]: TRG_SRC_EN_PTRN12 - Trigger Source Enable Pattern 12 (Default: 0x00000000) ******

# TRG_SRC_EN_PTRN12 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
WD2_TRG_SRC_EN_PTRN12_REG                =         WD2_REG_TRG_SRC_EN_PTRN12
WD2_TRG_SRC_EN_PTRN12_MASK               =                        0x0007FFFF
WD2_TRG_SRC_EN_PTRN12_OFS                =                                 0



# ****** Control Register 102 [0x1198]: TRG_STATE_PTRN12 - Trigger State Pattern 12 (Default: 0x00000000) ******

# TRG_STATE_PTRN12 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
WD2_TRG_STATE_PTRN12_REG                 =          WD2_REG_TRG_STATE_PTRN12
WD2_TRG_STATE_PTRN12_MASK                =                        0x0007FFFF
WD2_TRG_STATE_PTRN12_OFS                 =                                 0



# ****** Control Register 103 [0x119C]: TRG_SRC_EN_PTRN13 - Trigger Source Enable Pattern 13 (Default: 0x00000000) ******

# TRG_SRC_EN_PTRN13 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
WD2_TRG_SRC_EN_PTRN13_REG                =         WD2_REG_TRG_SRC_EN_PTRN13
WD2_TRG_SRC_EN_PTRN13_MASK               =                        0x0007FFFF
WD2_TRG_SRC_EN_PTRN13_OFS                =                                 0



# ****** Control Register 104 [0x11A0]: TRG_STATE_PTRN13 - Trigger State Pattern 13 (Default: 0x00000000) ******

# TRG_STATE_PTRN13 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
WD2_TRG_STATE_PTRN13_REG                 =          WD2_REG_TRG_STATE_PTRN13
WD2_TRG_STATE_PTRN13_MASK                =                        0x0007FFFF
WD2_TRG_STATE_PTRN13_OFS                 =                                 0



# ****** Control Register 105 [0x11A4]: TRG_SRC_EN_PTRN14 - Trigger Source Enable Pattern 14 (Default: 0x00000000) ******

# TRG_SRC_EN_PTRN14 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
WD2_TRG_SRC_EN_PTRN14_REG                =         WD2_REG_TRG_SRC_EN_PTRN14
WD2_TRG_SRC_EN_PTRN14_MASK               =                        0x0007FFFF
WD2_TRG_SRC_EN_PTRN14_OFS                =                                 0



# ****** Control Register 106 [0x11A8]: TRG_STATE_PTRN14 - Trigger State Pattern 14 (Default: 0x00000000) ******

# TRG_STATE_PTRN14 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
WD2_TRG_STATE_PTRN14_REG                 =          WD2_REG_TRG_STATE_PTRN14
WD2_TRG_STATE_PTRN14_MASK                =                        0x0007FFFF
WD2_TRG_STATE_PTRN14_OFS                 =                                 0



# ****** Control Register 107 [0x11AC]: TRG_SRC_EN_PTRN15 - Trigger Source Enable Pattern 15 (Default: 0x00000000) ******

# TRG_SRC_EN_PTRN15 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
WD2_TRG_SRC_EN_PTRN15_REG                =         WD2_REG_TRG_SRC_EN_PTRN15
WD2_TRG_SRC_EN_PTRN15_MASK               =                        0x0007FFFF
WD2_TRG_SRC_EN_PTRN15_OFS                =                                 0



# ****** Control Register 108 [0x11B0]: TRG_STATE_PTRN15 - Trigger State Pattern 15 (Default: 0x00000000) ******

# TRG_STATE_PTRN15 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
WD2_TRG_STATE_PTRN15_REG                 =          WD2_REG_TRG_STATE_PTRN15
WD2_TRG_STATE_PTRN15_MASK                =                        0x0007FFFF
WD2_TRG_STATE_PTRN15_OFS                 =                                 0



# ****** Control Register 109 [0x11B4]: TRG_SRC_EN_PTRN16 - Trigger Source Enable Pattern 16 (Default: 0x00000000) ******

# TRG_SRC_EN_PTRN16 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
WD2_TRG_SRC_EN_PTRN16_REG                =         WD2_REG_TRG_SRC_EN_PTRN16
WD2_TRG_SRC_EN_PTRN16_MASK               =                        0x0007FFFF
WD2_TRG_SRC_EN_PTRN16_OFS                =                                 0



# ****** Control Register 110 [0x11B8]: TRG_STATE_PTRN16 - Trigger State Pattern 16 (Default: 0x00000000) ******

# TRG_STATE_PTRN16 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
WD2_TRG_STATE_PTRN16_REG                 =          WD2_REG_TRG_STATE_PTRN16
WD2_TRG_STATE_PTRN16_MASK                =                        0x0007FFFF
WD2_TRG_STATE_PTRN16_OFS                 =                                 0



# ****** Control Register 111 [0x11BC]: TRG_SRC_EN_PTRN17 - Trigger Source Enable Pattern 17 (Default: 0x00000000) ******

# TRG_SRC_EN_PTRN17 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
WD2_TRG_SRC_EN_PTRN17_REG                =         WD2_REG_TRG_SRC_EN_PTRN17
WD2_TRG_SRC_EN_PTRN17_MASK               =                        0x0007FFFF
WD2_TRG_SRC_EN_PTRN17_OFS                =                                 0



# ****** Control Register 112 [0x11C0]: TRG_STATE_PTRN17 - Trigger State Pattern 17 (Default: 0x00000000) ******

# TRG_STATE_PTRN17 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
WD2_TRG_STATE_PTRN17_REG                 =          WD2_REG_TRG_STATE_PTRN17
WD2_TRG_STATE_PTRN17_MASK                =                        0x0007FFFF
WD2_TRG_STATE_PTRN17_OFS                 =                                 0



# ****** Control Register 113 [0x11C4]: TRG_SRC_EN_PTRN18 - Trigger Source Enable Pattern 18 (Default: 0x00000000) ******

# TRG_SRC_EN_PTRN18 - trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)
WD2_TRG_SRC_EN_PTRN18_REG                =         WD2_REG_TRG_SRC_EN_PTRN18
WD2_TRG_SRC_EN_PTRN18_MASK               =                        0x0007FFFF
WD2_TRG_SRC_EN_PTRN18_OFS                =                                 0



# ****** Control Register 114 [0x11C8]: TRG_STATE_PTRN18 - Trigger State Pattern 18 (Default: 0x00000000) ******

# TRG_STATE_PTRN18 - trigger source state pattern (0 = Inhibit, 1 = Coincidence)
WD2_TRG_STATE_PTRN18_REG                 =          WD2_REG_TRG_STATE_PTRN18
WD2_TRG_STATE_PTRN18_MASK                =                        0x0007FFFF
WD2_TRG_STATE_PTRN18_OFS                 =                                 0



# ****** Control Register 115 [0x11CC]: ADV_TRG_CTRL - Advanced Trigger Control Register (Default: 0x00000000) ******

# ADV_TRG_CTRL - Advanced trigger control register
WD2_ADV_TRG_CTRL_REG                     =              WD2_REG_ADV_TRG_CTRL
WD2_ADV_TRG_CTRL_MASK                    =                        0xFFFFFFFF
WD2_ADV_TRG_CTRL_OFS                     =                                 0



# ****** Control Register 116 [0x11D0]: ADV_TRG_CH_CAL0 - Advanced Trigger Channel Calibration Register 0 (Default: 0x00000000) ******

# ADV_TRG_CH_CAL0 - Advanced trigger channel calibration register 0
WD2_ADV_TRG_CH_CAL0_REG                  =           WD2_REG_ADV_TRG_CH_CAL0
WD2_ADV_TRG_CH_CAL0_MASK                 =                        0xFFFFFFFF
WD2_ADV_TRG_CH_CAL0_OFS                  =                                 0



# ****** Control Register 117 [0x11D4]: ADV_TRG_CH_CAL1 - Advanced Trigger Channel Calibration Register 1 (Default: 0x00000000) ******

# ADV_TRG_CH_CAL1 - Advanced trigger channel calibration register 1
WD2_ADV_TRG_CH_CAL1_REG                  =           WD2_REG_ADV_TRG_CH_CAL1
WD2_ADV_TRG_CH_CAL1_MASK                 =                        0xFFFFFFFF
WD2_ADV_TRG_CH_CAL1_OFS                  =                                 0



# ****** Control Register 118 [0x11D8]: ADV_TRG_CH_CAL2 - Advanced Trigger Channel Calibration Register 2 (Default: 0x00000000) ******

# ADV_TRG_CH_CAL2 - Advanced trigger channel calibration register 2
WD2_ADV_TRG_CH_CAL2_REG                  =           WD2_REG_ADV_TRG_CH_CAL2
WD2_ADV_TRG_CH_CAL2_MASK                 =                        0xFFFFFFFF
WD2_ADV_TRG_CH_CAL2_OFS                  =                                 0



# ****** Control Register 119 [0x11DC]: ADV_TRG_CH_CAL3 - Advanced Trigger Channel Calibration Register 3 (Default: 0x00000000) ******

# ADV_TRG_CH_CAL3 - Advanced trigger channel calibration register 3
WD2_ADV_TRG_CH_CAL3_REG                  =           WD2_REG_ADV_TRG_CH_CAL3
WD2_ADV_TRG_CH_CAL3_MASK                 =                        0xFFFFFFFF
WD2_ADV_TRG_CH_CAL3_OFS                  =                                 0



# ****** Control Register 120 [0x11E0]: ADV_TRG_PED_CFG - Advanced Trigger Pedestal Configuration Register (Default: 0x00000000) ******

# ADV_TRG_PED_CFG - Advanced trigger pedestal configuration register
WD2_ADV_TRG_PED_CFG_REG                  =           WD2_REG_ADV_TRG_PED_CFG
WD2_ADV_TRG_PED_CFG_MASK                 =                        0xFFFFFFFF
WD2_ADV_TRG_PED_CFG_OFS                  =                                 0



# ****** Control Register 121 [0x11E4]: ADV_TRG_THR0 - Advanced Trigger Threshold 0 Register (Default: 0x00000000) ******

# ADV_TRG_THR0 - Advanced trigger threshold 0 register
WD2_ADV_TRG_THR0_REG                     =              WD2_REG_ADV_TRG_THR0
WD2_ADV_TRG_THR0_MASK                    =                        0xFFFFFFFF
WD2_ADV_TRG_THR0_OFS                     =                                 0



# ****** Control Register 122 [0x11E8]: ADV_TRG_THR1 - Advanced Trigger Threshold 1 Register (Default: 0x00000000) ******

# ADV_TRG_THR1 - Advanced trigger threshold 1 register
WD2_ADV_TRG_THR1_REG                     =              WD2_REG_ADV_TRG_THR1
WD2_ADV_TRG_THR1_MASK                    =                        0xFFFFFFFF
WD2_ADV_TRG_THR1_OFS                     =                                 0



# ****** Control Register 123 [0x11EC]: ADV_TRG_THR2 - Advanced Trigger Threshold 2 Register (Default: 0x00000000) ******

# ADV_TRG_THR2 - Advanced trigger threshold 2 register
WD2_ADV_TRG_THR2_REG                     =              WD2_REG_ADV_TRG_THR2
WD2_ADV_TRG_THR2_MASK                    =                        0xFFFFFFFF
WD2_ADV_TRG_THR2_OFS                     =                                 0



# ****** Control Register 124 [0x11F0]: ADV_TRG_TX_CHK_WORD0 - Advanced Trigger Transmition Check Word 0 Register (Default: 0x00000000) ******

# ADV_TRG_TX_CHK_WORD0 - Advanced trigger transmition check word 0 register
WD2_ADV_TRG_TX_CHK_WORD0_REG             =      WD2_REG_ADV_TRG_TX_CHK_WORD0
WD2_ADV_TRG_TX_CHK_WORD0_MASK            =                        0xFFFFFFFF
WD2_ADV_TRG_TX_CHK_WORD0_OFS             =                                 0



# ****** Control Register 125 [0x11F4]: ADV_TRG_TX_CHK_WORD1 - Advanced Trigger Transmition Check Word 1 Register (Default: 0x00000000) ******

# ADV_TRG_TX_CHK_WORD1 - Advanced trigger transmition check word 1 register
WD2_ADV_TRG_TX_CHK_WORD1_REG             =      WD2_REG_ADV_TRG_TX_CHK_WORD1
WD2_ADV_TRG_TX_CHK_WORD1_MASK            =                        0xFFFFFFFF
WD2_ADV_TRG_TX_CHK_WORD1_OFS             =                                 0



# ****** Control Register 126 [0x11F8]: ADV_TRG_TDC_CH_MASK - Advanced Trigger TDC Channel Mask (Default: 0x00000000) ******

# ADV_TRG_TDC_CH_MASK - Advanced trigger TDC channel mask
WD2_ADV_TRG_TDC_CH_MASK_REG              =       WD2_REG_ADV_TRG_TDC_CH_MASK
WD2_ADV_TRG_TDC_CH_MASK_MASK             =                        0xFFFFFFFF
WD2_ADV_TRG_TDC_CH_MASK_OFS              =                                 0



# ****** Control Register 127 [0x11FC]: ADV_TRG_CFG12 - Advanced Trigger Configuration Register 12 (Default: 0x00000000) ******

# ADV_TRG_CFG_12 - Advanced trigger configuration register 12
WD2_ADV_TRG_CFG_12_REG                   =             WD2_REG_ADV_TRG_CFG12
WD2_ADV_TRG_CFG_12_MASK                  =                        0xFFFFFFFF
WD2_ADV_TRG_CFG_12_OFS                   =                                 0



# ****** Control Register 128 [0x1200]: ADV_TRG_CFG13 - Advanced Trigger Configuration Register 13 (Default: 0x00000000) ******

# ADV_TRG_CFG_13 - Advanced trigger configuration register 13
WD2_ADV_TRG_CFG_13_REG                   =             WD2_REG_ADV_TRG_CFG13
WD2_ADV_TRG_CFG_13_MASK                  =                        0xFFFFFFFF
WD2_ADV_TRG_CFG_13_OFS                   =                                 0



# ****** Control Register 129 [0x1204]: ADV_TRG_CFG14 - Advanced Trigger Configuration Register 14 (Default: 0x00000000) ******

# ADV_TRG_CFG_14 - Advanced trigger configuration register 14
WD2_ADV_TRG_CFG_14_REG                   =             WD2_REG_ADV_TRG_CFG14
WD2_ADV_TRG_CFG_14_MASK                  =                        0xFFFFFFFF
WD2_ADV_TRG_CFG_14_OFS                   =                                 0



# ****** Control Register 130 [0x1208]: ADV_TRG_CFG15 - Advanced Trigger Configuration Register 15 (Default: 0x00000000) ******

# ADV_TRG_CFG_15 - Advanced trigger configuration register 15
WD2_ADV_TRG_CFG_15_REG                   =             WD2_REG_ADV_TRG_CFG15
WD2_ADV_TRG_CFG_15_MASK                  =                        0xFFFFFFFF
WD2_ADV_TRG_CFG_15_OFS                   =                                 0



# ****** Control Register 131 [0x120C]: ADV_TRG_CFG16 - Advanced Trigger Configuration Register 16 (Default: 0x00000000) ******

# ADV_TRG_CFG_16 - Advanced trigger configuration register 16
WD2_ADV_TRG_CFG_16_REG                   =             WD2_REG_ADV_TRG_CFG16
WD2_ADV_TRG_CFG_16_MASK                  =                        0xFFFFFFFF
WD2_ADV_TRG_CFG_16_OFS                   =                                 0



# ****** Control Register 132 [0x1210]: ADV_TRG_CFG17 - Advanced Trigger Configuration Register 17 (Default: 0x00000000) ******

# ADV_TRG_CFG_17 - Advanced trigger configuration register 17
WD2_ADV_TRG_CFG_17_REG                   =             WD2_REG_ADV_TRG_CFG17
WD2_ADV_TRG_CFG_17_MASK                  =                        0xFFFFFFFF
WD2_ADV_TRG_CFG_17_OFS                   =                                 0



# ****** Control Register 133 [0x1214]: ADV_TRG_CFG18 - Advanced Trigger Configuration Register 18 (Default: 0x00000000) ******

# ADV_TRG_CFG_18 - Advanced trigger configuration register 18
WD2_ADV_TRG_CFG_18_REG                   =             WD2_REG_ADV_TRG_CFG18
WD2_ADV_TRG_CFG_18_MASK                  =                        0xFFFFFFFF
WD2_ADV_TRG_CFG_18_OFS                   =                                 0



# ****** Control Register 134 [0x1218]: ADV_TRG_CFG19 - Advanced Trigger Configuration Register 19 (Default: 0x00000000) ******

# ADV_TRG_CFG_19 - Advanced trigger configuration register 19
WD2_ADV_TRG_CFG_19_REG                   =             WD2_REG_ADV_TRG_CFG19
WD2_ADV_TRG_CFG_19_MASK                  =                        0xFFFFFFFF
WD2_ADV_TRG_CFG_19_OFS                   =                                 0



# ****** Control Register 135 [0x121C]: SET_TIME_LSB - Set System Time (Default: 0x00000000) ******

# SET_TIME_LSB - LSBs of 64bit system time counter set value  (time is updated when MSBs are written)
WD2_SET_TIME_LSB_REG                     =              WD2_REG_SET_TIME_LSB
WD2_SET_TIME_LSB_MASK                    =                        0xFFFFFFFF
WD2_SET_TIME_LSB_OFS                     =                                 0



# ****** Control Register 136 [0x1220]: SET_TIME_MSB - Set System Time (Default: 0x00000000) ******

# SET_TIME_MSB - MSBs of 64bit system time counter set value  (time is updated when MSBs are written)
WD2_SET_TIME_MSB_REG                     =              WD2_REG_SET_TIME_MSB
WD2_SET_TIME_MSB_MASK                    =                        0xFFFFFFFF
WD2_SET_TIME_MSB_OFS                     =                                 0



# ****** Control Register 137 [0x1224]: DBG_SIG_SEL - Debug Signal Select for MCX Connectors on HV Board (Default: 0x00000000) ******

# MCX_TX_SIG_SEL - Select for TX connector (see RX connector for mapping)
WD2_MCX_TX_SIG_SEL_REG                   =               WD2_REG_DBG_SIG_SEL
WD2_MCX_TX_SIG_SEL_MASK                  =                        0x000F0000
WD2_MCX_TX_SIG_SEL_OFS                   =                                16

# MCX_RX_SIG_SEL - Select for RX connector:
# 0x0 = UART (communication to MicroBlaze)
# 0x1 = Trigger (internal hardware trigger signal to DRS control FSM)
# 0x2 = Soft Trigger (trigger signal from MicroBlaze)
# 0x3 = External Trigger (OR connection of external trigger from MCX and Backplane)
# 0x4 = Sync Signal from Backplane (direct, active high)
# 0x5 = Sync Signal from Backplane (sampled, output to LMK, active low)
# 0x6 = Sync Signal from Backplane (sampled, used for internal logic, active high)
# 0x7 = Busy Local (active high)
# 0x8 = Busy from Backplane (active high)
# 0x9 = LMK Reference Clock (LMK input clock) 
# 0xA = ADC Sampling Clock 
# 0xB = Divided Data Clock (phase shifted)
# 0xC = LMK5 clock (directly routed from corresponding input)
# 0xD = SPI CS of LMK (active low)
WD2_MCX_RX_SIG_SEL_REG                   =               WD2_REG_DBG_SIG_SEL
WD2_MCX_RX_SIG_SEL_MASK                  =                        0x0000000F
WD2_MCX_RX_SIG_SEL_OFS                   =                                 0



# ****** Control Register 138 [0x1228]: CRC32_REG_BANK - CRC32 Checksum of Register Bank Content (Default: None) ******

# CRC32_REG_BANK - Keep at the end of the register bank
WD2_CRC32_REG_BANK_REG                   =            WD2_REG_CRC32_REG_BANK
WD2_CRC32_REG_BANK_MASK                  =                        0xFFFFFFFF
WD2_CRC32_REG_BANK_OFS                   =                                 0



# ****** Status Register 0 [0x0000]: HW_VER - Hardware version information of the PCB (Default: 0xAC01021B) ******

# BOARD_MAGIC - 0xAC, Magic number for DRS board identification
WD2_BOARD_MAGIC_REG                      =                    WD2_REG_HW_VER
WD2_BOARD_MAGIC_MASK                     =                        0xFF000000
WD2_BOARD_MAGIC_OFS                      =                                24
WD2_BOARD_MAGIC_CONST                    =                              0xAC

# VENDOR_ID - ID of the board vendor (0x01 for PSI)
WD2_VENDOR_ID_REG                        =                    WD2_REG_HW_VER
WD2_VENDOR_ID_MASK                       =                        0x00FF0000
WD2_VENDOR_ID_OFS                        =                                16
WD2_VENDOR_ID_CONST                      =                              0x01

# BOARD_TYPE - WaveDream Number (0x02 for WD2)
WD2_BOARD_TYPE_REG                       =                    WD2_REG_HW_VER
WD2_BOARD_TYPE_MASK                      =                        0x0000FF00
WD2_BOARD_TYPE_OFS                       =                                 8
WD2_BOARD_TYPE_CONST                     =                              0x02

# BOARD_REVISION - Board revision (A=0x00, C=0x02, D=0x03, E=0x04, F=0x05, G=0x06)
WD2_BOARD_REVISION_REG                   =                    WD2_REG_HW_VER
WD2_BOARD_REVISION_MASK                  =                        0x000000FC
WD2_BOARD_REVISION_OFS                   =                                 2
WD2_BOARD_REVISION_CONST                 =                              0x06

# BOARD_VARIANT - Version indicator pins reflecting the variant of the board (Y15,Y10)
WD2_BOARD_VARIANT_REG                    =                    WD2_REG_HW_VER
WD2_BOARD_VARIANT_MASK                   =                        0x00000003
WD2_BOARD_VARIANT_OFS                    =                                 0
WD2_BOARD_VARIANT_CONST                  =                               0x3



# ****** Status Register 1 [0x0004]: REG_LAYOUT_VER - Register map layout version information (Default: 0x00090009) ******

# REG_LAYOUT_COMP_LEVEL - Register map layout compatibility level
WD2_REG_LAYOUT_COMP_LEVEL_REG            =            WD2_REG_REG_LAYOUT_VER
WD2_REG_LAYOUT_COMP_LEVEL_MASK           =                        0xFFFF0000
WD2_REG_LAYOUT_COMP_LEVEL_OFS            =                                16
WD2_REG_LAYOUT_COMP_LEVEL_CONST          =                            0x0009

# REG_LAYOUT_VERSION - Register map layout version
WD2_REG_LAYOUT_VERSION_REG               =            WD2_REG_REG_LAYOUT_VER
WD2_REG_LAYOUT_VERSION_MASK              =                        0x0000FFFF
WD2_REG_LAYOUT_VERSION_OFS               =                                 0
WD2_REG_LAYOUT_VERSION_CONST             =                            0x0009



# ****** Status Register 2 [0x0008]: FW_BUILD_DATE - Date when the firmware was built (Default: 0x00000000) ******

# FW_BUILD_YEAR - Year of the firmware build
WD2_FW_BUILD_YEAR_REG                    =             WD2_REG_FW_BUILD_DATE
WD2_FW_BUILD_YEAR_MASK                   =                        0xFFFF0000
WD2_FW_BUILD_YEAR_OFS                    =                                16

# FW_BUILD_MONTH - Month of the firmware build
WD2_FW_BUILD_MONTH_REG                   =             WD2_REG_FW_BUILD_DATE
WD2_FW_BUILD_MONTH_MASK                  =                        0x0000FF00
WD2_FW_BUILD_MONTH_OFS                   =                                 8

# FW_BUILD_DAY - Day of the firmware build
WD2_FW_BUILD_DAY_REG                     =             WD2_REG_FW_BUILD_DATE
WD2_FW_BUILD_DAY_MASK                    =                        0x000000FF
WD2_FW_BUILD_DAY_OFS                     =                                 0



# ****** Status Register 3 [0x000C]: FW_BUILD_TIME - Time when the firmware was built and compatibility level (Default: 0x05000000) ******

# FW_COMPAT_LEVEL - Firmware compatibility level
WD2_FW_COMPAT_LEVEL_REG                  =             WD2_REG_FW_BUILD_TIME
WD2_FW_COMPAT_LEVEL_MASK                 =                        0xFF000000
WD2_FW_COMPAT_LEVEL_OFS                  =                                24
WD2_FW_COMPAT_LEVEL_CONST                =                              0x05

# FW_BUILD_HOUR - Hour of the firmware build
WD2_FW_BUILD_HOUR_REG                    =             WD2_REG_FW_BUILD_TIME
WD2_FW_BUILD_HOUR_MASK                   =                        0x00FF0000
WD2_FW_BUILD_HOUR_OFS                    =                                16

# FW_BUILD_MINUTE - Minute of the firmware build
WD2_FW_BUILD_MINUTE_REG                  =             WD2_REG_FW_BUILD_TIME
WD2_FW_BUILD_MINUTE_MASK                 =                        0x0000FF00
WD2_FW_BUILD_MINUTE_OFS                  =                                 8

# FW_BUILD_SECOND - Second of the firmware build
WD2_FW_BUILD_SECOND_REG                  =             WD2_REG_FW_BUILD_TIME
WD2_FW_BUILD_SECOND_MASK                 =                        0x000000FF
WD2_FW_BUILD_SECOND_OFS                  =                                 0



# ****** Status Register 4 [0x0010]: SW_BUILD_DATE - Date when the software was built (Default: 0x00000000) ******

# SW_BUILD_YEAR - Year of the software build
WD2_SW_BUILD_YEAR_REG                    =             WD2_REG_SW_BUILD_DATE
WD2_SW_BUILD_YEAR_MASK                   =                        0xFFFF0000
WD2_SW_BUILD_YEAR_OFS                    =                                16

# SW_BUILD_MONTH - Month of the software build
WD2_SW_BUILD_MONTH_REG                   =             WD2_REG_SW_BUILD_DATE
WD2_SW_BUILD_MONTH_MASK                  =                        0x0000FF00
WD2_SW_BUILD_MONTH_OFS                   =                                 8

# SW_BUILD_DAY - Day of the software build
WD2_SW_BUILD_DAY_REG                     =             WD2_REG_SW_BUILD_DATE
WD2_SW_BUILD_DAY_MASK                    =                        0x000000FF
WD2_SW_BUILD_DAY_OFS                     =                                 0



# ****** Status Register 5 [0x0014]: SW_BUILD_TIME - Time when the software was built and compatibility level (Default: 0x00000000) ******

# SW_BUILD_HOUR - Hour of the software build
WD2_SW_BUILD_HOUR_REG                    =             WD2_REG_SW_BUILD_TIME
WD2_SW_BUILD_HOUR_MASK                   =                        0x00FF0000
WD2_SW_BUILD_HOUR_OFS                    =                                16

# SW_BUILD_MINUTE - Minute of the software build
WD2_SW_BUILD_MINUTE_REG                  =             WD2_REG_SW_BUILD_TIME
WD2_SW_BUILD_MINUTE_MASK                 =                        0x0000FF00
WD2_SW_BUILD_MINUTE_OFS                  =                                 8

# SW_BUILD_SECOND - Second of the software build
WD2_SW_BUILD_SECOND_REG                  =             WD2_REG_SW_BUILD_TIME
WD2_SW_BUILD_SECOND_MASK                 =                        0x000000FF
WD2_SW_BUILD_SECOND_OFS                  =                                 0



# ****** Status Register 6 [0x0018]: FW_GIT_HASH_TAG - Hash tag of the firmware commit in the GIT repository (Default: 0x00000000) ******

# FW_GIT_HASH_TAG - Hash tag of the firmware commit in the GIT repository
WD2_FW_GIT_HASH_TAG_REG                  =           WD2_REG_FW_GIT_HASH_TAG
WD2_FW_GIT_HASH_TAG_MASK                 =                        0xFFFFFFFF
WD2_FW_GIT_HASH_TAG_OFS                  =                                 0



# ****** Status Register 7 [0x001C]: SW_GIT_HASH_TAG - Hash tag of the software commit in the GIT repository (Default: 0x00000000) ******

# SW_GIT_HASH_TAG - Hash tag of the software commit in the GIT repository
WD2_SW_GIT_HASH_TAG_REG                  =           WD2_REG_SW_GIT_HASH_TAG
WD2_SW_GIT_HASH_TAG_MASK                 =                        0xFFFFFFFF
WD2_SW_GIT_HASH_TAG_OFS                  =                                 0



# ****** Status Register 8 [0x0020]: PROT_VER - Vesion of the WaveDream2 protocol (Default: 0x00000006) ******

# PROTOCOL_VERSION - Version of the WaveDream2 protocol
WD2_PROTOCOL_VERSION_REG                 =                  WD2_REG_PROT_VER
WD2_PROTOCOL_VERSION_MASK                =                        0x000000FF
WD2_PROTOCOL_VERSION_OFS                 =                                 0



# ****** Status Register 9 [0x0024]: SN - Serial Number of the WD2 Board (Board ID) (Default: 0x00000000) ******

# LED_STATE - State of the front panel LED (on-beat-color RGB, off-beat-color RGB)
WD2_LED_STATE_REG                        =                        WD2_REG_SN
WD2_LED_STATE_MASK                       =                        0x3F000000
WD2_LED_STATE_OFS                        =                                24

# SERIAL_NUMBER - Serial Number of the WD2 Board (Board ID)
WD2_SERIAL_NUMBER_REG                    =                        WD2_REG_SN
WD2_SERIAL_NUMBER_MASK                   =                        0x0000FFFF
WD2_SERIAL_NUMBER_OFS                    =                                 0



# ****** Status Register 10 [0x0028]: STATUS - Status Register (Default: 0x00000000) ******

# TEMPERATURE - temperature in 0.0625 deg. C units
WD2_TEMPERATURE_REG                      =                    WD2_REG_STATUS
WD2_TEMPERATURE_MASK                     =                        0xFFFF0000
WD2_TEMPERATURE_OFS                      =                                16

# OVERTEMP - Overtemperature from external sensor
WD2_OVERTEMP_REG                         =                    WD2_REG_STATUS
WD2_OVERTEMP_MASK                        =                        0x00008000
WD2_OVERTEMP_OFS                         =                                15

# EXT_CLK_ACTIVE - Configuration for external clock for DAQ completed
WD2_EXT_CLK_ACTIVE_REG                   =                    WD2_REG_STATUS
WD2_EXT_CLK_ACTIVE_MASK                  =                        0x00004000
WD2_EXT_CLK_ACTIVE_OFS                   =                                14

# DAQ_CLK_DEF_PHASE_OK - DAQ clock default phase setting is valid
WD2_DAQ_CLK_DEF_PHASE_OK_REG             =                    WD2_REG_STATUS
WD2_DAQ_CLK_DEF_PHASE_OK_MASK            =                        0x00002000
WD2_DAQ_CLK_DEF_PHASE_OK_OFS             =                                13

# DAQ_CLK_DEF_PHASE_CHKD - DAQ clock default phase setting is checked
WD2_DAQ_CLK_DEF_PHASE_CHKD_REG           =                    WD2_REG_STATUS
WD2_DAQ_CLK_DEF_PHASE_CHKD_MASK          =                        0x00001000
WD2_DAQ_CLK_DEF_PHASE_CHKD_OFS           =                                12

# DRS_CONFIG_DONE - DRS configuration done
WD2_DRS_CONFIG_DONE_REG                  =                    WD2_REG_STATUS
WD2_DRS_CONFIG_DONE_MASK                 =                        0x00000400
WD2_DRS_CONFIG_DONE_OFS                  =                                10

# BOARD_SEL - Board select from backplane (inverted = high active)
WD2_BOARD_SEL_REG                        =                    WD2_REG_STATUS
WD2_BOARD_SEL_MASK                       =                        0x00000100
WD2_BOARD_SEL_OFS                        =                                 8

# SERIAL_BUSY - "1" during serial activity like FLASH read/write
WD2_SERIAL_BUSY_REG                      =                    WD2_REG_STATUS
WD2_SERIAL_BUSY_MASK                     =                        0x00000080
WD2_SERIAL_BUSY_OFS                      =                                 7

# PACKAGER_BUSY - "1" while packager is not ready to process data (buffers are full or ethernet destination not configured)
WD2_PACKAGER_BUSY_REG                    =                    WD2_REG_STATUS
WD2_PACKAGER_BUSY_MASK                   =                        0x00000040
WD2_PACKAGER_BUSY_OFS                    =                                 6

# DRS_CTRL_BUSY - "1" while domino wave running or readout in progress
WD2_DRS_CTRL_BUSY_REG                    =                    WD2_REG_STATUS
WD2_DRS_CTRL_BUSY_MASK                   =                        0x00000020
WD2_DRS_CTRL_BUSY_OFS                    =                                 5

# SYS_BUSY - Inverted busy signal from backplane (high active, not available until hardware revision G)
WD2_SYS_BUSY_REG                         =                    WD2_REG_STATUS
WD2_SYS_BUSY_MASK                        =                        0x00000010
WD2_SYS_BUSY_OFS                         =                                 4

# HV_BOARD_PLUGGED - HV board is currently plugged (1) or unplugged (0)
WD2_HV_BOARD_PLUGGED_REG                 =                    WD2_REG_STATUS
WD2_HV_BOARD_PLUGGED_MASK                =                        0x00000002
WD2_HV_BOARD_PLUGGED_OFS                 =                                 1

# BACKPLANE_PLUGGED - Backplane is currently plugged (1) or unplugged (0)
WD2_BACKPLANE_PLUGGED_REG                =                    WD2_REG_STATUS
WD2_BACKPLANE_PLUGGED_MASK               =                        0x00000001
WD2_BACKPLANE_PLUGGED_OFS                =                                 0



# ****** Status Register 11 [0x002C]: PLL_LOCK - Lock Status of PLLs (Default: 0x00000000) ******

# SYS_DCM_LOCK - Lock of system DCM (FPGA internal)
WD2_SYS_DCM_LOCK_REG                     =                  WD2_REG_PLL_LOCK
WD2_SYS_DCM_LOCK_MASK                    =                        0x00000100
WD2_SYS_DCM_LOCK_OFS                     =                                 8

# DAQ_PLL_LOCK - Lock of DAQ PLL (FPGA internal)
WD2_DAQ_PLL_LOCK_REG                     =                  WD2_REG_PLL_LOCK
WD2_DAQ_PLL_LOCK_MASK                    =                        0x00000080
WD2_DAQ_PLL_LOCK_OFS                     =                                 7

# OSERDES_PLL_LOCK_DCB - Lock of PLL for OSERDES to DCB (FPGA internal)
WD2_OSERDES_PLL_LOCK_DCB_REG             =                  WD2_REG_PLL_LOCK
WD2_OSERDES_PLL_LOCK_DCB_MASK            =                        0x00000040
WD2_OSERDES_PLL_LOCK_DCB_OFS             =                                 6

# OSERDES_PLL_LOCK_TCB - Lock of PLL for OSERDES to TCB (FPGA internal)
WD2_OSERDES_PLL_LOCK_TCB_REG             =                  WD2_REG_PLL_LOCK
WD2_OSERDES_PLL_LOCK_TCB_MASK            =                        0x00000020
WD2_OSERDES_PLL_LOCK_TCB_OFS             =                                 5

# ISERDES_PLL_LOCK_0 - Lock of PLL for ISERDES from ADC 0 (A) (FPGA internal)
WD2_ISERDES_PLL_LOCK_0_REG               =                  WD2_REG_PLL_LOCK
WD2_ISERDES_PLL_LOCK_0_MASK              =                        0x00000010
WD2_ISERDES_PLL_LOCK_0_OFS               =                                 4

# ISERDES_PLL_LOCK_1 - Lock of PLL for ISERDES from ADC 1 (B) (FPGA internal)
WD2_ISERDES_PLL_LOCK_1_REG               =                  WD2_REG_PLL_LOCK
WD2_ISERDES_PLL_LOCK_1_MASK              =                        0x00000008
WD2_ISERDES_PLL_LOCK_1_OFS               =                                 3

# DRS_PLL_LOCK_0 - PLL lock signal of DRS Channel 0 (A) (external)
WD2_DRS_PLL_LOCK_0_REG                   =                  WD2_REG_PLL_LOCK
WD2_DRS_PLL_LOCK_0_MASK                  =                        0x00000004
WD2_DRS_PLL_LOCK_0_OFS                   =                                 2

# DRS_PLL_LOCK_1 - PLL lock signal of DRS Channel 1 (B) (external)
WD2_DRS_PLL_LOCK_1_REG                   =                  WD2_REG_PLL_LOCK
WD2_DRS_PLL_LOCK_1_MASK                  =                        0x00000002
WD2_DRS_PLL_LOCK_1_OFS                   =                                 1

# LMK_PLL_LOCK - PLL lock signal of LMK (external)
WD2_LMK_PLL_LOCK_REG                     =                  WD2_REG_PLL_LOCK
WD2_LMK_PLL_LOCK_MASK                    =                        0x00000001
WD2_LMK_PLL_LOCK_OFS                     =                                 0



# ****** Status Register 12 [0x0030]: DRS_STOP_CELL - Position where sampling stopped at last trigger in DRS (Default: 0x00000000) ******

# DRS_STOP_CELL_0 - Stop position of DRS Channel 0 (A)
WD2_DRS_STOP_CELL_0_REG                  =             WD2_REG_DRS_STOP_CELL
WD2_DRS_STOP_CELL_0_MASK                 =                        0x03FF0000
WD2_DRS_STOP_CELL_0_OFS                  =                                16

# DRS_STOP_CELL_1 - Stop position of DRS Channel 1 (B)
WD2_DRS_STOP_CELL_1_REG                  =             WD2_REG_DRS_STOP_CELL
WD2_DRS_STOP_CELL_1_MASK                 =                        0x000003FF
WD2_DRS_STOP_CELL_1_OFS                  =                                 0



# ****** Status Register 13 [0x0034]: DRS_STOP_WSR - Write shift register contents when sampling stopped in DRS (Default: 0x00000000) ******

# DRS_STOP_WSR_0 - WSR contents after stop of DRS Channel 0 (A)
WD2_DRS_STOP_WSR_0_REG                   =              WD2_REG_DRS_STOP_WSR
WD2_DRS_STOP_WSR_0_MASK                  =                        0x0000FF00
WD2_DRS_STOP_WSR_0_OFS                   =                                 8

# DRS_STOP_WSR_1 - WSR contents after stop of DRS Channel 1 (B)
WD2_DRS_STOP_WSR_1_REG                   =              WD2_REG_DRS_STOP_WSR
WD2_DRS_STOP_WSR_1_MASK                  =                        0x000000FF
WD2_DRS_STOP_WSR_1_OFS                   =                                 0



# ****** Status Register 14 [0x0038]: DRS_SAMPLE_FREQ - DRS Sampling frequency (Default: 0x00000000) ******

# DRS_SAMPLE_FREQ - DRS Sampling frequency in kHz
WD2_DRS_SAMPLE_FREQ_REG                  =           WD2_REG_DRS_SAMPLE_FREQ
WD2_DRS_SAMPLE_FREQ_MASK                 =                        0x00FFFFFF
WD2_DRS_SAMPLE_FREQ_OFS                  =                                 0



# ****** Status Register 15 [0x003C]: ADC_SAMPLE_FREQ - ADC Sampling Frequency in MHz (Default: 0x00013880) ******

# ADC_SAMPLE_FREQ - ADC Sampling Frequency in kHz
WD2_ADC_SAMPLE_FREQ_REG                  =           WD2_REG_ADC_SAMPLE_FREQ
WD2_ADC_SAMPLE_FREQ_MASK                 =                        0x00FFFFFF
WD2_ADC_SAMPLE_FREQ_OFS                  =                                 0



# ****** Status Register 16 [0x0040]: TDC_SAMPLE_FREQ - TDC Sampling Frequency in MHz (Default: 0x0009C400) ******

# TDC_SAMPLE_FREQ - TDC Sampling Frequency in kHz
WD2_TDC_SAMPLE_FREQ_REG                  =           WD2_REG_TDC_SAMPLE_FREQ
WD2_TDC_SAMPLE_FREQ_MASK                 =                        0x00FFFFFF
WD2_TDC_SAMPLE_FREQ_OFS                  =                                 0



# ****** Status Register 17 [0x0044]: HV_VER - HV Board Version (Default: 0x00000000) ******

# HV_VER - HV board version (16bit Voltage in V, 16bit Current in mA)
WD2_HV_VER_REG                           =                    WD2_REG_HV_VER
WD2_HV_VER_MASK                          =                        0xFFFFFFFF
WD2_HV_VER_OFS                           =                                 0



# ****** Status Register 18 [0x0048]: HV_I_MEAS_0 - Measured actual current of the HV supply on channel 0 (Default: 0x00000000) ******

# HV_I_MEAS_0 - Float value (i_meas)
WD2_HV_I_MEAS_0_REG                      =               WD2_REG_HV_I_MEAS_0
WD2_HV_I_MEAS_0_MASK                     =                        0xFFFFFFFF
WD2_HV_I_MEAS_0_OFS                      =                                 0



# ****** Status Register 19 [0x004C]: HV_I_MEAS_1 - Measured actual current of the HV supply on channel 1 (Default: 0x00000000) ******

# HV_I_MEAS_1 - Float value (i_meas)
WD2_HV_I_MEAS_1_REG                      =               WD2_REG_HV_I_MEAS_1
WD2_HV_I_MEAS_1_MASK                     =                        0xFFFFFFFF
WD2_HV_I_MEAS_1_OFS                      =                                 0



# ****** Status Register 20 [0x0050]: HV_I_MEAS_2 - Measured actual current of the HV supply on channel 2 (Default: 0x00000000) ******

# HV_I_MEAS_2 - Float value (i_meas)
WD2_HV_I_MEAS_2_REG                      =               WD2_REG_HV_I_MEAS_2
WD2_HV_I_MEAS_2_MASK                     =                        0xFFFFFFFF
WD2_HV_I_MEAS_2_OFS                      =                                 0



# ****** Status Register 21 [0x0054]: HV_I_MEAS_3 - Measured actual current of the HV supply on channel 3 (Default: 0x00000000) ******

# HV_I_MEAS_3 - Float value (i_meas)
WD2_HV_I_MEAS_3_REG                      =               WD2_REG_HV_I_MEAS_3
WD2_HV_I_MEAS_3_MASK                     =                        0xFFFFFFFF
WD2_HV_I_MEAS_3_OFS                      =                                 0



# ****** Status Register 22 [0x0058]: HV_I_MEAS_4 - Measured actual current of the HV supply on channel 4 (Default: 0x00000000) ******

# HV_I_MEAS_4 - Float value (i_meas)
WD2_HV_I_MEAS_4_REG                      =               WD2_REG_HV_I_MEAS_4
WD2_HV_I_MEAS_4_MASK                     =                        0xFFFFFFFF
WD2_HV_I_MEAS_4_OFS                      =                                 0



# ****** Status Register 23 [0x005C]: HV_I_MEAS_5 - Measured actual current of the HV supply on channel 5 (Default: 0x00000000) ******

# HV_I_MEAS_5 - Float value (i_meas)
WD2_HV_I_MEAS_5_REG                      =               WD2_REG_HV_I_MEAS_5
WD2_HV_I_MEAS_5_MASK                     =                        0xFFFFFFFF
WD2_HV_I_MEAS_5_OFS                      =                                 0



# ****** Status Register 24 [0x0060]: HV_I_MEAS_6 - Measured actual current of the HV supply on channel 6 (Default: 0x00000000) ******

# HV_I_MEAS_6 - Float value (i_meas)
WD2_HV_I_MEAS_6_REG                      =               WD2_REG_HV_I_MEAS_6
WD2_HV_I_MEAS_6_MASK                     =                        0xFFFFFFFF
WD2_HV_I_MEAS_6_OFS                      =                                 0



# ****** Status Register 25 [0x0064]: HV_I_MEAS_7 - Measured actual current of the HV supply on channel 7 (Default: 0x00000000) ******

# HV_I_MEAS_7 - Float value (i_meas)
WD2_HV_I_MEAS_7_REG                      =               WD2_REG_HV_I_MEAS_7
WD2_HV_I_MEAS_7_MASK                     =                        0xFFFFFFFF
WD2_HV_I_MEAS_7_OFS                      =                                 0



# ****** Status Register 26 [0x0068]: HV_I_MEAS_8 - Measured actual current of the HV supply on channel 8 (Default: 0x00000000) ******

# HV_I_MEAS_8 - Float value (i_meas)
WD2_HV_I_MEAS_8_REG                      =               WD2_REG_HV_I_MEAS_8
WD2_HV_I_MEAS_8_MASK                     =                        0xFFFFFFFF
WD2_HV_I_MEAS_8_OFS                      =                                 0



# ****** Status Register 27 [0x006C]: HV_I_MEAS_9 - Measured actual current of the HV supply on channel 9 (Default: 0x00000000) ******

# HV_I_MEAS_9 - Float value (i_meas)
WD2_HV_I_MEAS_9_REG                      =               WD2_REG_HV_I_MEAS_9
WD2_HV_I_MEAS_9_MASK                     =                        0xFFFFFFFF
WD2_HV_I_MEAS_9_OFS                      =                                 0



# ****** Status Register 28 [0x0070]: HV_I_MEAS_10 - Measured actual current of the HV supply on channel 10 (Default: 0x00000000) ******

# HV_I_MEAS_10 - Float value (i_meas)
WD2_HV_I_MEAS_10_REG                     =              WD2_REG_HV_I_MEAS_10
WD2_HV_I_MEAS_10_MASK                    =                        0xFFFFFFFF
WD2_HV_I_MEAS_10_OFS                     =                                 0



# ****** Status Register 29 [0x0074]: HV_I_MEAS_11 - Measured actual current of the HV supply on channel 11 (Default: 0x00000000) ******

# HV_I_MEAS_11 - Float value (i_meas)
WD2_HV_I_MEAS_11_REG                     =              WD2_REG_HV_I_MEAS_11
WD2_HV_I_MEAS_11_MASK                    =                        0xFFFFFFFF
WD2_HV_I_MEAS_11_OFS                     =                                 0



# ****** Status Register 30 [0x0078]: HV_I_MEAS_12 - Measured actual current of the HV supply on channel 12 (Default: 0x00000000) ******

# HV_I_MEAS_12 - Float value (i_meas)
WD2_HV_I_MEAS_12_REG                     =              WD2_REG_HV_I_MEAS_12
WD2_HV_I_MEAS_12_MASK                    =                        0xFFFFFFFF
WD2_HV_I_MEAS_12_OFS                     =                                 0



# ****** Status Register 31 [0x007C]: HV_I_MEAS_13 - Measured actual current of the HV supply on channel 13 (Default: 0x00000000) ******

# HV_I_MEAS_13 - Float value (i_meas)
WD2_HV_I_MEAS_13_REG                     =              WD2_REG_HV_I_MEAS_13
WD2_HV_I_MEAS_13_MASK                    =                        0xFFFFFFFF
WD2_HV_I_MEAS_13_OFS                     =                                 0



# ****** Status Register 32 [0x0080]: HV_I_MEAS_14 - Measured actual current of the HV supply on channel 14 (Default: 0x00000000) ******

# HV_I_MEAS_14 - Float value (i_meas)
WD2_HV_I_MEAS_14_REG                     =              WD2_REG_HV_I_MEAS_14
WD2_HV_I_MEAS_14_MASK                    =                        0xFFFFFFFF
WD2_HV_I_MEAS_14_OFS                     =                                 0



# ****** Status Register 33 [0x0084]: HV_I_MEAS_15 - Measured actual current of the HV supply on channel 15 (Default: 0x00000000) ******

# HV_I_MEAS_15 - Float value (i_meas)
WD2_HV_I_MEAS_15_REG                     =              WD2_REG_HV_I_MEAS_15
WD2_HV_I_MEAS_15_MASK                    =                        0xFFFFFFFF
WD2_HV_I_MEAS_15_OFS                     =                                 0



# ****** Status Register 34 [0x0088]: HV_U_BASE_MEAS - Measured actual HV base voltage (Default: 0x00000000) ******

# HV_U_BASE_MEAS - Float value (ub_meas)
WD2_HV_U_BASE_MEAS_REG                   =            WD2_REG_HV_U_BASE_MEAS
WD2_HV_U_BASE_MEAS_MASK                  =                        0xFFFFFFFF
WD2_HV_U_BASE_MEAS_OFS                   =                                 0



# ****** Status Register 35 [0x008C]: HV_TEMP_0 - Measured actual temperature of sensor 0 connected to the HV board (Default: 0x00000000) ******

# HV_TEMP_0 - Float value (temp)
WD2_HV_TEMP_0_REG                        =                 WD2_REG_HV_TEMP_0
WD2_HV_TEMP_0_MASK                       =                        0xFFFFFFFF
WD2_HV_TEMP_0_OFS                        =                                 0



# ****** Status Register 36 [0x0090]: HV_TEMP_1 - Measured actual temperature of sensor 1 connected to the HV board (Default: 0x00000000) ******

# HV_TEMP_1 - Float value (temp)
WD2_HV_TEMP_1_REG                        =                 WD2_REG_HV_TEMP_1
WD2_HV_TEMP_1_MASK                       =                        0xFFFFFFFF
WD2_HV_TEMP_1_OFS                        =                                 0



# ****** Status Register 37 [0x0094]: HV_TEMP_2 - Measured actual temperature of sensor 2 connected to the HV board (Default: 0x00000000) ******

# HV_TEMP_2 - Float value (temp)
WD2_HV_TEMP_2_REG                        =                 WD2_REG_HV_TEMP_2
WD2_HV_TEMP_2_MASK                       =                        0xFFFFFFFF
WD2_HV_TEMP_2_OFS                        =                                 0



# ****** Status Register 38 [0x0098]: HV_TEMP_3 - Measured actual temperature of sensor 3 connected to the HV board (Default: 0x00000000) ******

# HV_TEMP_3 - Float value (temp)
WD2_HV_TEMP_3_REG                        =                 WD2_REG_HV_TEMP_3
WD2_HV_TEMP_3_MASK                       =                        0xFFFFFFFF
WD2_HV_TEMP_3_OFS                        =                                 0



# ****** Status Register 39 [0x009C]: SCALER_0 - Scaler for input #0 (Default: 0x00000000) ******

# SCALER_0 - Count rate value of channel 0 (MSBs are latched upon read of LSB register)
WD2_SCALER_0_REG                         =                  WD2_REG_SCALER_0
WD2_SCALER_0_MASK                        =                        0xFFFFFFFF
WD2_SCALER_0_OFS                         =                                 0



# ****** Status Register 40 [0x00A0]: SCALER_1 - Scaler for input #1 (Default: 0x00000000) ******

# SCALER_1 - Count rate value of channel 1 (MSBs are latched upon read of LSB register)
WD2_SCALER_1_REG                         =                  WD2_REG_SCALER_1
WD2_SCALER_1_MASK                        =                        0xFFFFFFFF
WD2_SCALER_1_OFS                         =                                 0



# ****** Status Register 41 [0x00A4]: SCALER_2 - Scaler for input #2 (Default: 0x00000000) ******

# SCALER_2 - Count rate value of channel 2 (MSBs are latched upon read of LSB register)
WD2_SCALER_2_REG                         =                  WD2_REG_SCALER_2
WD2_SCALER_2_MASK                        =                        0xFFFFFFFF
WD2_SCALER_2_OFS                         =                                 0



# ****** Status Register 42 [0x00A8]: SCALER_3 - Scaler for input #3 (Default: 0x00000000) ******

# SCALER_3 - Count rate value of channel 3 (MSBs are latched upon read of LSB register)
WD2_SCALER_3_REG                         =                  WD2_REG_SCALER_3
WD2_SCALER_3_MASK                        =                        0xFFFFFFFF
WD2_SCALER_3_OFS                         =                                 0



# ****** Status Register 43 [0x00AC]: SCALER_4 - Scaler for input #4 (Default: 0x00000000) ******

# SCALER_4 - Count rate value of channel 4 (MSBs are latched upon read of LSB register)
WD2_SCALER_4_REG                         =                  WD2_REG_SCALER_4
WD2_SCALER_4_MASK                        =                        0xFFFFFFFF
WD2_SCALER_4_OFS                         =                                 0



# ****** Status Register 44 [0x00B0]: SCALER_5 - Scaler for input #5 (Default: 0x00000000) ******

# SCALER_5 - Count rate value of channel 5 (MSBs are latched upon read of LSB register)
WD2_SCALER_5_REG                         =                  WD2_REG_SCALER_5
WD2_SCALER_5_MASK                        =                        0xFFFFFFFF
WD2_SCALER_5_OFS                         =                                 0



# ****** Status Register 45 [0x00B4]: SCALER_6 - Scaler for input #6 (Default: 0x00000000) ******

# SCALER_6 - Count rate value of channel 6 (MSBs are latched upon read of LSB register)
WD2_SCALER_6_REG                         =                  WD2_REG_SCALER_6
WD2_SCALER_6_MASK                        =                        0xFFFFFFFF
WD2_SCALER_6_OFS                         =                                 0



# ****** Status Register 46 [0x00B8]: SCALER_7 - Scaler for input #7 (Default: 0x00000000) ******

# SCALER_7 - Count rate value of channel 7 (MSBs are latched upon read of LSB register)
WD2_SCALER_7_REG                         =                  WD2_REG_SCALER_7
WD2_SCALER_7_MASK                        =                        0xFFFFFFFF
WD2_SCALER_7_OFS                         =                                 0



# ****** Status Register 47 [0x00BC]: SCALER_8 - Scaler for input #8 (Default: 0x00000000) ******

# SCALER_8 - Count rate value of channel 8 (MSBs are latched upon read of LSB register)
WD2_SCALER_8_REG                         =                  WD2_REG_SCALER_8
WD2_SCALER_8_MASK                        =                        0xFFFFFFFF
WD2_SCALER_8_OFS                         =                                 0



# ****** Status Register 48 [0x00C0]: SCALER_9 - Scaler for input #9 (Default: 0x00000000) ******

# SCALER_9 - Count rate value of channel 9 (MSBs are latched upon read of LSB register)
WD2_SCALER_9_REG                         =                  WD2_REG_SCALER_9
WD2_SCALER_9_MASK                        =                        0xFFFFFFFF
WD2_SCALER_9_OFS                         =                                 0



# ****** Status Register 49 [0x00C4]: SCALER_10 - Scaler for input #10 (Default: 0x00000000) ******

# SCALER_10 - Count rate value of channel 10 (MSBs are latched upon read of LSB register)
WD2_SCALER_10_REG                        =                 WD2_REG_SCALER_10
WD2_SCALER_10_MASK                       =                        0xFFFFFFFF
WD2_SCALER_10_OFS                        =                                 0



# ****** Status Register 50 [0x00C8]: SCALER_11 - Scaler for input #11 (Default: 0x00000000) ******

# SCALER_11 - Count rate value of channel 11 (MSBs are latched upon read of LSB register)
WD2_SCALER_11_REG                        =                 WD2_REG_SCALER_11
WD2_SCALER_11_MASK                       =                        0xFFFFFFFF
WD2_SCALER_11_OFS                        =                                 0



# ****** Status Register 51 [0x00CC]: SCALER_12 - Scaler for input #12 (Default: 0x00000000) ******

# SCALER_12 - Count rate value of channel 12 (MSBs are latched upon read of LSB register)
WD2_SCALER_12_REG                        =                 WD2_REG_SCALER_12
WD2_SCALER_12_MASK                       =                        0xFFFFFFFF
WD2_SCALER_12_OFS                        =                                 0



# ****** Status Register 52 [0x00D0]: SCALER_13 - Scaler for input #13 (Default: 0x00000000) ******

# SCALER_13 - Count rate value of channel 13 (MSBs are latched upon read of LSB register)
WD2_SCALER_13_REG                        =                 WD2_REG_SCALER_13
WD2_SCALER_13_MASK                       =                        0xFFFFFFFF
WD2_SCALER_13_OFS                        =                                 0



# ****** Status Register 53 [0x00D4]: SCALER_14 - Scaler for input #14 (Default: 0x00000000) ******

# SCALER_14 - Count rate value of channel 14 (MSBs are latched upon read of LSB register)
WD2_SCALER_14_REG                        =                 WD2_REG_SCALER_14
WD2_SCALER_14_MASK                       =                        0xFFFFFFFF
WD2_SCALER_14_OFS                        =                                 0



# ****** Status Register 54 [0x00D8]: SCALER_15 - Scaler for input #15 (Default: 0x00000000) ******

# SCALER_15 - Count rate value of channel 15 (MSBs are latched upon read of LSB register)
WD2_SCALER_15_REG                        =                 WD2_REG_SCALER_15
WD2_SCALER_15_MASK                       =                        0xFFFFFFFF
WD2_SCALER_15_OFS                        =                                 0



# ****** Status Register 55 [0x00DC]: SCALER_PTRN_TRG - Scaler for pattern trigger (Default: 0x00000000) ******

# SCALER_PTRN_TRG - Count rate for pattern trigger signal
WD2_SCALER_PTRN_TRG_REG                  =           WD2_REG_SCALER_PTRN_TRG
WD2_SCALER_PTRN_TRG_MASK                 =                        0xFFFFFFFF
WD2_SCALER_PTRN_TRG_OFS                  =                                 0



# ****** Status Register 56 [0x00E0]: SCALER_EXT_TRG - Scaler for external trigger (Default: 0x00000000) ******

# SCALER_EXT_TRG - Count rate for trigger signal
WD2_SCALER_EXT_TRG_REG                   =            WD2_REG_SCALER_EXT_TRG
WD2_SCALER_EXT_TRG_MASK                  =                        0xFFFFFFFF
WD2_SCALER_EXT_TRG_OFS                   =                                 0



# ****** Status Register 57 [0x00E4]: SCALER_EXT_CLK - Scaler for ext. clock input (Default: 0x00000000) ******

# SCALER_EXT_CLK - Count rate for external clock input (GLOB_CLK)
WD2_SCALER_EXT_CLK_REG                   =            WD2_REG_SCALER_EXT_CLK
WD2_SCALER_EXT_CLK_MASK                  =                        0xFFFFFFFF
WD2_SCALER_EXT_CLK_OFS                   =                                 0



# ****** Status Register 58 [0x00E8]: SCALER_TIME_STAMP_LSB - Time Stamp for Scaler Values (Default: 0x00000000) ******

# SCALER_TIME_STAMP_LSB - LSBs of 64bit scaler time stamp (MSBs are latched upon read of LSB register)
WD2_SCALER_TIME_STAMP_LSB_REG            =     WD2_REG_SCALER_TIME_STAMP_LSB
WD2_SCALER_TIME_STAMP_LSB_MASK           =                        0xFFFFFFFF
WD2_SCALER_TIME_STAMP_LSB_OFS            =                                 0



# ****** Status Register 59 [0x00EC]: SCALER_TIME_STAMP_MSB - Time Stamp for Scaler Values (Default: 0x00000000) ******

# SCALER_TIME_STAMP_MSB - MSBs of 64bit scaler time stamp (latched upon read of LSB register)
WD2_SCALER_TIME_STAMP_MSB_REG            =     WD2_REG_SCALER_TIME_STAMP_MSB
WD2_SCALER_TIME_STAMP_MSB_MASK           =                        0xFFFFFFFF
WD2_SCALER_TIME_STAMP_MSB_OFS            =                                 0



# ****** Status Register 60 [0x00F0]: TIME_LSB - Current System Time (Default: 0x00000000) ******

# TIME_LSB - LSBs of 64bit system time counter (MSBs are latched upon read of LSB register)
WD2_TIME_LSB_REG                         =                  WD2_REG_TIME_LSB
WD2_TIME_LSB_MASK                        =                        0xFFFFFFFF
WD2_TIME_LSB_OFS                         =                                 0



# ****** Status Register 61 [0x00F4]: TIME_MSB - Current System Time (Default: 0x00000000) ******

# TIME_MSB - MSBs of 64bit system time counter (latched upon read of LSB register)
WD2_TIME_MSB_REG                         =                  WD2_REG_TIME_MSB
WD2_TIME_MSB_MASK                        =                        0xFFFFFFFF
WD2_TIME_MSB_OFS                         =                                 0



# ****** Status Register 62 [0x00F8]: COMP_CH_STAT - Comparator channel status (Default: 0x00000000) ******

# COMP_CH_STAT - Status of the comparator inputs
WD2_COMP_CH_STAT_REG                     =              WD2_REG_COMP_CH_STAT
WD2_COMP_CH_STAT_MASK                    =                        0x0000FFFF
WD2_COMP_CH_STAT_OFS                     =                                 0



# ****** Status Register 63 [0x00FC]: EVENT_TX_RATE - Event Transmission Rate (Default: 0x00000000) ******

# EVENT_TX_RATE - Number of events transmitted per second
WD2_EVENT_TX_RATE_REG                    =             WD2_REG_EVENT_TX_RATE
WD2_EVENT_TX_RATE_MASK                   =                        0xFFFFFFFF
WD2_EVENT_TX_RATE_OFS                    =                                 0



# ****** Status Register 64 [0x0100]: EVENT_NR - Number of latest event (Default: 0x00000000) ******

# EVENT_NUMBER - Number of latest event
WD2_EVENT_NUMBER_REG                     =                  WD2_REG_EVENT_NR
WD2_EVENT_NUMBER_MASK                    =                        0xFFFFFFFF
WD2_EVENT_NUMBER_OFS                     =                                 0



# ****** Status Register 65 [0x0104]: TRB_INFO_STAT - Trigger Information via Serial Trigger Bus Status (Default: 0x00000000) ******

# TRB_FLAG_NEW - Flag signalling that the current trigger information belongs to the latest trigger received
WD2_TRB_FLAG_NEW_REG                     =             WD2_REG_TRB_INFO_STAT
WD2_TRB_FLAG_NEW_MASK                    =                        0x80000000
WD2_TRB_FLAG_NEW_OFS                     =                                31

# TRB_FLAG_PARITY_ERROR - Parity error flag of the current trigger information
WD2_TRB_FLAG_PARITY_ERROR_REG            =             WD2_REG_TRB_INFO_STAT
WD2_TRB_FLAG_PARITY_ERROR_MASK           =                        0x40000000
WD2_TRB_FLAG_PARITY_ERROR_OFS            =                                30

# TRB_PARITY_ERROR_COUNT - Parity error count of the serial transmission
WD2_TRB_PARITY_ERROR_COUNT_REG           =             WD2_REG_TRB_INFO_STAT
WD2_TRB_PARITY_ERROR_COUNT_MASK          =                        0x0000FFFF
WD2_TRB_PARITY_ERROR_COUNT_OFS           =                                 0



# ****** Status Register 66 [0x0108]: TRB_INFO_LSB - Trigger Information via Serial Trigger Bus LSBs (Default: 0x00000000) ******

# TRB_INFO_LSB - Trigger information LSBs
WD2_TRB_INFO_LSB_REG                     =              WD2_REG_TRB_INFO_LSB
WD2_TRB_INFO_LSB_MASK                    =                        0xFFFFFFFF
WD2_TRB_INFO_LSB_OFS                     =                                 0



# ****** Status Register 67 [0x010C]: TRB_INFO_MSB - Trigger Information via Serial Trigger Bus MSBs (Default: 0x00000000) ******

# TRB_INFO_MSB - Trigger information MSBs
WD2_TRB_INFO_MSB_REG                     =              WD2_REG_TRB_INFO_MSB
WD2_TRB_INFO_MSB_MASK                    =                        0x0000FFFF
WD2_TRB_INFO_MSB_OFS                     =                                 0



# ****** Status Register 68 [0x0110]: ADV_TRG_TRIG_CELL - Advanced Trigger Cell Register (Default: 0x00000000) ******

# ADV_TRG_TRIG_CELL - Advanced trigger cell register
WD2_ADV_TRG_TRIG_CELL_REG                =         WD2_REG_ADV_TRG_TRIG_CELL
WD2_ADV_TRG_TRIG_CELL_MASK               =                        0xFFFFFFFF
WD2_ADV_TRG_TRIG_CELL_OFS                =                                 0



# ****** Status Register 69 [0x0114]: ADV_TRG_STAT1 - Advanced Trigger Status Register 1 (Default: 0x00000000) ******

# ADV_TRG_STAT_1 - Advanced trigger status register 1
WD2_ADV_TRG_STAT_1_REG                   =             WD2_REG_ADV_TRG_STAT1
WD2_ADV_TRG_STAT_1_MASK                  =                        0xFFFFFFFF
WD2_ADV_TRG_STAT_1_OFS                   =                                 0



# ****** Status Register 70 [0x0118]: ADV_TRG_STAT2 - Advanced Trigger Status Register 2 (Default: 0x00000000) ******

# ADV_TRG_STAT_2 - Advanced trigger status register 2
WD2_ADV_TRG_STAT_2_REG                   =             WD2_REG_ADV_TRG_STAT2
WD2_ADV_TRG_STAT_2_MASK                  =                        0xFFFFFFFF
WD2_ADV_TRG_STAT_2_OFS                   =                                 0



# ****** Status Register 71 [0x011C]: ADV_TRG_STAT3 - Advanced Trigger Status Register 3 (Default: 0x00000000) ******

# ADV_TRG_STAT_3 - Advanced trigger status register 3
WD2_ADV_TRG_STAT_3_REG                   =             WD2_REG_ADV_TRG_STAT3
WD2_ADV_TRG_STAT_3_MASK                  =                        0xFFFFFFFF
WD2_ADV_TRG_STAT_3_OFS                   =                                 0



# ****** Status Register 72 [0x0120]: ADV_TRG_STAT4 - Advanced Trigger Status Register 4 (Default: 0x00000000) ******

# ADV_TRG_STAT_4 - Advanced trigger status register 4
WD2_ADV_TRG_STAT_4_REG                   =             WD2_REG_ADV_TRG_STAT4
WD2_ADV_TRG_STAT_4_MASK                  =                        0xFFFFFFFF
WD2_ADV_TRG_STAT_4_OFS                   =                                 0



# ****** Status Register 73 [0x0124]: MAX_DRS_ADC_PKT_SAMPLES - Maximum DRS/ADC samples per Packet (Default: 0x00000000) ******

# MAX_DRS_ADC_PKT_SAMPLES - Maximum number of DRS/ADC samples per packet
WD2_MAX_DRS_ADC_PKT_SAMPLES_REG          =   WD2_REG_MAX_DRS_ADC_PKT_SAMPLES
WD2_MAX_DRS_ADC_PKT_SAMPLES_MASK         =                        0x0000FFFF
WD2_MAX_DRS_ADC_PKT_SAMPLES_OFS          =                                 0



# ****** Status Register 74 [0x0128]: MAX_TDC_PKT_SAMPLES - Maximum TDC samples per Packet (Default: 0x00000000) ******

# MAX_TDC_PKT_SAMPLES - Maximum number of TDC samples per packet
WD2_MAX_TDC_PKT_SAMPLES_REG              =       WD2_REG_MAX_TDC_PKT_SAMPLES
WD2_MAX_TDC_PKT_SAMPLES_MASK             =                        0x0003FFFF
WD2_MAX_TDC_PKT_SAMPLES_OFS              =                                 0



# ****** Status Register 75 [0x012C]: MAX_TRG_PKT_SAMPLES - Maximum advanced trigger output samples per Packet (Default: 0x00000000) ******

# MAX_TRG_PKT_SAMPLES - Maximum number of advanced trigger output samples per packet
WD2_MAX_TRG_PKT_SAMPLES_REG              =       WD2_REG_MAX_TRG_PKT_SAMPLES
WD2_MAX_TRG_PKT_SAMPLES_MASK             =                        0x0000FFFF
WD2_MAX_TRG_PKT_SAMPLES_OFS              =                                 0



# ****** Status Register 76 [0x0130]: MAX_SCL_PKT_SAMPLES - Maximum scaler values per Packet (Default: 0x00000000) ******

# MAX_SCL_PKT_SAMPLES - Maximum number of scaler values per packet
WD2_MAX_SCL_PKT_SAMPLES_REG              =       WD2_REG_MAX_SCL_PKT_SAMPLES
WD2_MAX_SCL_PKT_SAMPLES_MASK             =                        0x0000FFFF
WD2_MAX_SCL_PKT_SAMPLES_OFS              =                                 0



# ****** Status Register 77 [0x0134]: CLK_CTRL_MOD_FLAG - Set if WD2 configuration registers are modified (Default: 0x00000000) ******

# TRIGGER_DAQ_CLK_CAL_MOD - Trigger DAQ clock calibration modified flag
WD2_TRIGGER_DAQ_CLK_CAL_MOD_REG          =         WD2_REG_CLK_CTRL_MOD_FLAG
WD2_TRIGGER_DAQ_CLK_CAL_MOD_MASK         =                        0x00000010
WD2_TRIGGER_DAQ_CLK_CAL_MOD_OFS          =                                 4

# ADC_RST_MOD - ADC reset modified flag
WD2_ADC_RST_MOD_REG                      =         WD2_REG_CLK_CTRL_MOD_FLAG
WD2_ADC_RST_MOD_MASK                     =                        0x00000008
WD2_ADC_RST_MOD_OFS                      =                                 3

# CLK_SEL_AND_DRS_CLK_DIV_MOD - DAQ clock select and DRS clock divider modified flags
WD2_CLK_SEL_AND_DRS_CLK_DIV_MOD_REG      =         WD2_REG_CLK_CTRL_MOD_FLAG
WD2_CLK_SEL_AND_DRS_CLK_DIV_MOD_MASK     =                        0x00000004
WD2_CLK_SEL_AND_DRS_CLK_DIV_MOD_OFS      =                                 2

# EXT_CLK_FREQ_MOD - External clock frequency modified flags
WD2_EXT_CLK_FREQ_MOD_REG                 =         WD2_REG_CLK_CTRL_MOD_FLAG
WD2_EXT_CLK_FREQ_MOD_MASK                =                        0x00000002
WD2_EXT_CLK_FREQ_MOD_OFS                 =                                 1

# LOCAL_CLK_FREQ_MOD - Local clock frequency modified flags
WD2_LOCAL_CLK_FREQ_MOD_REG               =         WD2_REG_CLK_CTRL_MOD_FLAG
WD2_LOCAL_CLK_FREQ_MOD_MASK              =                        0x00000001
WD2_LOCAL_CLK_FREQ_MOD_OFS               =                                 0



# ****** Status Register 78 [0x0138]: DRS_MOD_FLAG - Set if DRS configuration registers are modified (Default: 0x00000000) ******

# DRS_CTRL_MOD - DRS control bits modified flags
WD2_DRS_CTRL_MOD_REG                     =              WD2_REG_DRS_MOD_FLAG
WD2_DRS_CTRL_MOD_MASK                    =                        0x00000004
WD2_DRS_CTRL_MOD_OFS                     =                                 2

# DRS_WSR_MOD - DRS write shift register modified flags
WD2_DRS_WSR_MOD_REG                      =              WD2_REG_DRS_MOD_FLAG
WD2_DRS_WSR_MOD_MASK                     =                        0x00000002
WD2_DRS_WSR_MOD_OFS                      =                                 1

# DRS_WCR_MOD - DRS write control register modified flags
WD2_DRS_WCR_MOD_REG                      =              WD2_REG_DRS_MOD_FLAG
WD2_DRS_WCR_MOD_MASK                     =                        0x00000001
WD2_DRS_WCR_MOD_OFS                      =                                 0



# ****** Status Register 79 [0x013C]: COM_PLD_SIZE_MOD_FLAG - Set if maximum packet payload size register is modified (Default: 0x00000000) ******

# COM_PLD_SIZE_MOD - Maximum packet payload size modified flag
WD2_COM_PLD_SIZE_MOD_REG                 =     WD2_REG_COM_PLD_SIZE_MOD_FLAG
WD2_COM_PLD_SIZE_MOD_MASK                =                        0x0000000F
WD2_COM_PLD_SIZE_MOD_OFS                 =                                 0



# ****** Status Register 80 [0x0140]: ADC_SAMPLE_DIV_MOD_FLAG - Set if ADC downsampling divider register is modified (Default: 0x00000000) ******

# ADC_SAMPLE_DIV_MOD - ADC downsampling divider modified flags
WD2_ADC_SAMPLE_DIV_MOD_REG               =   WD2_REG_ADC_SAMPLE_DIV_MOD_FLAG
WD2_ADC_SAMPLE_DIV_MOD_MASK              =                        0x0000000F
WD2_ADC_SAMPLE_DIV_MOD_OFS               =                                 0



# ****** Status Register 81 [0x0144]: DAC_0_1_MOD_FLAG - Set if DAC 0 and 1 configuration registers are modified (Default: 0x00000000) ******

# DAC0_A_MOD - DAC channel a modified flags
WD2_DAC0_A_MOD_REG                       =          WD2_REG_DAC_0_1_MOD_FLAG
WD2_DAC0_A_MOD_MASK                      =                        0xC0000000
WD2_DAC0_A_MOD_OFS                       =                                30

# DAC0_B_MOD - DAC channel b modified flags
WD2_DAC0_B_MOD_REG                       =          WD2_REG_DAC_0_1_MOD_FLAG
WD2_DAC0_B_MOD_MASK                      =                        0x30000000
WD2_DAC0_B_MOD_OFS                       =                                28

# DAC0_C_MOD - DAC channel c modified flags
WD2_DAC0_C_MOD_REG                       =          WD2_REG_DAC_0_1_MOD_FLAG
WD2_DAC0_C_MOD_MASK                      =                        0x0C000000
WD2_DAC0_C_MOD_OFS                       =                                26

# DAC0_D_MOD - DAC channel d modified flags
WD2_DAC0_D_MOD_REG                       =          WD2_REG_DAC_0_1_MOD_FLAG
WD2_DAC0_D_MOD_MASK                      =                        0x03000000
WD2_DAC0_D_MOD_OFS                       =                                24

# DAC0_E_MOD - DAC channel e modified flags
WD2_DAC0_E_MOD_REG                       =          WD2_REG_DAC_0_1_MOD_FLAG
WD2_DAC0_E_MOD_MASK                      =                        0x00C00000
WD2_DAC0_E_MOD_OFS                       =                                22

# DAC0_F_MOD - DAC channel f modified flags
WD2_DAC0_F_MOD_REG                       =          WD2_REG_DAC_0_1_MOD_FLAG
WD2_DAC0_F_MOD_MASK                      =                        0x00300000
WD2_DAC0_F_MOD_OFS                       =                                20

# DAC0_G_MOD - DAC channel g modified flags
WD2_DAC0_G_MOD_REG                       =          WD2_REG_DAC_0_1_MOD_FLAG
WD2_DAC0_G_MOD_MASK                      =                        0x000C0000
WD2_DAC0_G_MOD_OFS                       =                                18

# DAC0_H_MOD - DAC channel h modified flags
WD2_DAC0_H_MOD_REG                       =          WD2_REG_DAC_0_1_MOD_FLAG
WD2_DAC0_H_MOD_MASK                      =                        0x00030000
WD2_DAC0_H_MOD_OFS                       =                                16

# DAC1_A_MOD - DAC channel a modified flags
WD2_DAC1_A_MOD_REG                       =          WD2_REG_DAC_0_1_MOD_FLAG
WD2_DAC1_A_MOD_MASK                      =                        0x0000C000
WD2_DAC1_A_MOD_OFS                       =                                14

# DAC1_B_MOD - DAC channel b modified flags
WD2_DAC1_B_MOD_REG                       =          WD2_REG_DAC_0_1_MOD_FLAG
WD2_DAC1_B_MOD_MASK                      =                        0x00003000
WD2_DAC1_B_MOD_OFS                       =                                12

# DAC1_C_MOD - DAC channel c modified flags
WD2_DAC1_C_MOD_REG                       =          WD2_REG_DAC_0_1_MOD_FLAG
WD2_DAC1_C_MOD_MASK                      =                        0x00000C00
WD2_DAC1_C_MOD_OFS                       =                                10

# DAC1_D_MOD - DAC channel d modified flags
WD2_DAC1_D_MOD_REG                       =          WD2_REG_DAC_0_1_MOD_FLAG
WD2_DAC1_D_MOD_MASK                      =                        0x00000300
WD2_DAC1_D_MOD_OFS                       =                                 8

# DAC1_E_MOD - DAC channel e modified flags
WD2_DAC1_E_MOD_REG                       =          WD2_REG_DAC_0_1_MOD_FLAG
WD2_DAC1_E_MOD_MASK                      =                        0x000000C0
WD2_DAC1_E_MOD_OFS                       =                                 6

# DAC1_F_MOD - DAC channel f modified flags
WD2_DAC1_F_MOD_REG                       =          WD2_REG_DAC_0_1_MOD_FLAG
WD2_DAC1_F_MOD_MASK                      =                        0x00000030
WD2_DAC1_F_MOD_OFS                       =                                 4

# DAC1_G_MOD - DAC channel g modified flags
WD2_DAC1_G_MOD_REG                       =          WD2_REG_DAC_0_1_MOD_FLAG
WD2_DAC1_G_MOD_MASK                      =                        0x0000000C
WD2_DAC1_G_MOD_OFS                       =                                 2

# DAC1_H_MOD - DAC channel h modified flags
WD2_DAC1_H_MOD_REG                       =          WD2_REG_DAC_0_1_MOD_FLAG
WD2_DAC1_H_MOD_MASK                      =                        0x00000003
WD2_DAC1_H_MOD_OFS                       =                                 0



# ****** Status Register 82 [0x0148]: DAC_2_MOD_FLAG - Set if DAC 2 configuration registers are modified (Default: 0x00000000) ******

# DAC2_A_MOD - DAC channel a modified flags
WD2_DAC2_A_MOD_REG                       =            WD2_REG_DAC_2_MOD_FLAG
WD2_DAC2_A_MOD_MASK                      =                        0xC0000000
WD2_DAC2_A_MOD_OFS                       =                                30

# DAC2_B_MOD - DAC channel b modified flags
WD2_DAC2_B_MOD_REG                       =            WD2_REG_DAC_2_MOD_FLAG
WD2_DAC2_B_MOD_MASK                      =                        0x30000000
WD2_DAC2_B_MOD_OFS                       =                                28

# DAC2_C_MOD - DAC channel c modified flags
WD2_DAC2_C_MOD_REG                       =            WD2_REG_DAC_2_MOD_FLAG
WD2_DAC2_C_MOD_MASK                      =                        0x0C000000
WD2_DAC2_C_MOD_OFS                       =                                26

# DAC2_D_MOD - DAC channel d modified flags
WD2_DAC2_D_MOD_REG                       =            WD2_REG_DAC_2_MOD_FLAG
WD2_DAC2_D_MOD_MASK                      =                        0x03000000
WD2_DAC2_D_MOD_OFS                       =                                24

# DAC2_E_MOD - DAC channel e modified flags
WD2_DAC2_E_MOD_REG                       =            WD2_REG_DAC_2_MOD_FLAG
WD2_DAC2_E_MOD_MASK                      =                        0x00C00000
WD2_DAC2_E_MOD_OFS                       =                                22

# DAC2_F_MOD - DAC channel f modified flags
WD2_DAC2_F_MOD_REG                       =            WD2_REG_DAC_2_MOD_FLAG
WD2_DAC2_F_MOD_MASK                      =                        0x00300000
WD2_DAC2_F_MOD_OFS                       =                                20

# DAC2_G_MOD - DAC channel g modified flags
WD2_DAC2_G_MOD_REG                       =            WD2_REG_DAC_2_MOD_FLAG
WD2_DAC2_G_MOD_MASK                      =                        0x000C0000
WD2_DAC2_G_MOD_OFS                       =                                18

# DAC2_H_MOD - DAC channel h modified flags
WD2_DAC2_H_MOD_REG                       =            WD2_REG_DAC_2_MOD_FLAG
WD2_DAC2_H_MOD_MASK                      =                        0x00030000
WD2_DAC2_H_MOD_OFS                       =                                16



# ****** Status Register 83 [0x014C]: FE_0_15_MOD_FLAG - Set if frontend configuraiton registers are modified (Default: 0x00000000) ******

# FE_0_MOD - Frontend channel 0 register modified flags
WD2_FE_0_MOD_REG                         =          WD2_REG_FE_0_15_MOD_FLAG
WD2_FE_0_MOD_MASK                        =                        0xC0000000
WD2_FE_0_MOD_OFS                         =                                30

# FE_1_MOD - Frontend channel 1 register modified flags
WD2_FE_1_MOD_REG                         =          WD2_REG_FE_0_15_MOD_FLAG
WD2_FE_1_MOD_MASK                        =                        0x30000000
WD2_FE_1_MOD_OFS                         =                                28

# FE_2_MOD - Frontend channel 2 register modified flags
WD2_FE_2_MOD_REG                         =          WD2_REG_FE_0_15_MOD_FLAG
WD2_FE_2_MOD_MASK                        =                        0x0C000000
WD2_FE_2_MOD_OFS                         =                                26

# FE_3_MOD - Frontend channel 3 register modified flags
WD2_FE_3_MOD_REG                         =          WD2_REG_FE_0_15_MOD_FLAG
WD2_FE_3_MOD_MASK                        =                        0x03000000
WD2_FE_3_MOD_OFS                         =                                24

# FE_4_MOD - Frontend channel 4 register modified flags
WD2_FE_4_MOD_REG                         =          WD2_REG_FE_0_15_MOD_FLAG
WD2_FE_4_MOD_MASK                        =                        0x00C00000
WD2_FE_4_MOD_OFS                         =                                22

# FE_5_MOD - Frontend channel 5 register modified flags
WD2_FE_5_MOD_REG                         =          WD2_REG_FE_0_15_MOD_FLAG
WD2_FE_5_MOD_MASK                        =                        0x00300000
WD2_FE_5_MOD_OFS                         =                                20

# FE_6_MOD - Frontend channel 6 register modified flags
WD2_FE_6_MOD_REG                         =          WD2_REG_FE_0_15_MOD_FLAG
WD2_FE_6_MOD_MASK                        =                        0x000C0000
WD2_FE_6_MOD_OFS                         =                                18

# FE_7_MOD - Frontend channel 7 register modified flags
WD2_FE_7_MOD_REG                         =          WD2_REG_FE_0_15_MOD_FLAG
WD2_FE_7_MOD_MASK                        =                        0x00030000
WD2_FE_7_MOD_OFS                         =                                16

# FE_8_MOD - Frontend channel 8 register modified flags
WD2_FE_8_MOD_REG                         =          WD2_REG_FE_0_15_MOD_FLAG
WD2_FE_8_MOD_MASK                        =                        0x0000C000
WD2_FE_8_MOD_OFS                         =                                14

# FE_9_MOD - Frontend channel 9 register modified flags
WD2_FE_9_MOD_REG                         =          WD2_REG_FE_0_15_MOD_FLAG
WD2_FE_9_MOD_MASK                        =                        0x00003000
WD2_FE_9_MOD_OFS                         =                                12

# FE_10_MOD - Frontend channel 10 register modified flags
WD2_FE_10_MOD_REG                        =          WD2_REG_FE_0_15_MOD_FLAG
WD2_FE_10_MOD_MASK                       =                        0x00000C00
WD2_FE_10_MOD_OFS                        =                                10

# FE_11_MOD - Frontend channel 11 register modified flags
WD2_FE_11_MOD_REG                        =          WD2_REG_FE_0_15_MOD_FLAG
WD2_FE_11_MOD_MASK                       =                        0x00000300
WD2_FE_11_MOD_OFS                        =                                 8

# FE_12_MOD - Frontend channel 12 register modified flags
WD2_FE_12_MOD_REG                        =          WD2_REG_FE_0_15_MOD_FLAG
WD2_FE_12_MOD_MASK                       =                        0x000000C0
WD2_FE_12_MOD_OFS                        =                                 6

# FE_13_MOD - Frontend channel 13 register modified flags
WD2_FE_13_MOD_REG                        =          WD2_REG_FE_0_15_MOD_FLAG
WD2_FE_13_MOD_MASK                       =                        0x00000030
WD2_FE_13_MOD_OFS                        =                                 4

# FE_14_MOD - Frontend channel 14 register modified flags
WD2_FE_14_MOD_REG                        =          WD2_REG_FE_0_15_MOD_FLAG
WD2_FE_14_MOD_MASK                       =                        0x0000000C
WD2_FE_14_MOD_OFS                        =                                 2

# FE_15_MOD - Frontend channel 15 register modified flags
WD2_FE_15_MOD_REG                        =          WD2_REG_FE_0_15_MOD_FLAG
WD2_FE_15_MOD_MASK                       =                        0x00000003
WD2_FE_15_MOD_OFS                        =                                 0



# ****** Status Register 84 [0x0150]: HV_U_TARGET_0_7_MOD_FLAG - Set if HV target voltage configuraiton of channel 0 to 7 registers are modified (Default: 0x00000000) ******

# HV_U_TARGET_0_MOD - Target high voltage channel 0 register modified flags
WD2_HV_U_TARGET_0_MOD_REG                =  WD2_REG_HV_U_TARGET_0_7_MOD_FLAG
WD2_HV_U_TARGET_0_MOD_MASK               =                        0xF0000000
WD2_HV_U_TARGET_0_MOD_OFS                =                                28

# HV_U_TARGET_1_MOD - Target high voltage channel 1 register modified flags
WD2_HV_U_TARGET_1_MOD_REG                =  WD2_REG_HV_U_TARGET_0_7_MOD_FLAG
WD2_HV_U_TARGET_1_MOD_MASK               =                        0x0F000000
WD2_HV_U_TARGET_1_MOD_OFS                =                                24

# HV_U_TARGET_2_MOD - Target high voltage channel 2 register modified flags
WD2_HV_U_TARGET_2_MOD_REG                =  WD2_REG_HV_U_TARGET_0_7_MOD_FLAG
WD2_HV_U_TARGET_2_MOD_MASK               =                        0x00F00000
WD2_HV_U_TARGET_2_MOD_OFS                =                                20

# HV_U_TARGET_3_MOD - Target high voltage channel 3 register modified flags
WD2_HV_U_TARGET_3_MOD_REG                =  WD2_REG_HV_U_TARGET_0_7_MOD_FLAG
WD2_HV_U_TARGET_3_MOD_MASK               =                        0x000F0000
WD2_HV_U_TARGET_3_MOD_OFS                =                                16

# HV_U_TARGET_4_MOD - Target high voltage channel 4 register modified flags
WD2_HV_U_TARGET_4_MOD_REG                =  WD2_REG_HV_U_TARGET_0_7_MOD_FLAG
WD2_HV_U_TARGET_4_MOD_MASK               =                        0x0000F000
WD2_HV_U_TARGET_4_MOD_OFS                =                                12

# HV_U_TARGET_5_MOD - Target high voltage channel 5 register modified flags
WD2_HV_U_TARGET_5_MOD_REG                =  WD2_REG_HV_U_TARGET_0_7_MOD_FLAG
WD2_HV_U_TARGET_5_MOD_MASK               =                        0x00000F00
WD2_HV_U_TARGET_5_MOD_OFS                =                                 8

# HV_U_TARGET_6_MOD - Target high voltage channel 6 register modified flags
WD2_HV_U_TARGET_6_MOD_REG                =  WD2_REG_HV_U_TARGET_0_7_MOD_FLAG
WD2_HV_U_TARGET_6_MOD_MASK               =                        0x000000F0
WD2_HV_U_TARGET_6_MOD_OFS                =                                 4

# HV_U_TARGET_7_MOD - Target high voltage channel 7 register modified flags
WD2_HV_U_TARGET_7_MOD_REG                =  WD2_REG_HV_U_TARGET_0_7_MOD_FLAG
WD2_HV_U_TARGET_7_MOD_MASK               =                        0x0000000F
WD2_HV_U_TARGET_7_MOD_OFS                =                                 0



# ****** Status Register 85 [0x0154]: HV_U_TARGET_8_15_MOD_FLAG - Set if HV target voltage configuraiton of channel 8 to 15 registers are modified (Default: 0x00000000) ******

# HV_U_TARGET_8_MOD - Target high voltage channel 8 register modified flags
WD2_HV_U_TARGET_8_MOD_REG                = WD2_REG_HV_U_TARGET_8_15_MOD_FLAG
WD2_HV_U_TARGET_8_MOD_MASK               =                        0xF0000000
WD2_HV_U_TARGET_8_MOD_OFS                =                                28

# HV_U_TARGET_9_MOD - Target high voltage channel 9 register modified flags
WD2_HV_U_TARGET_9_MOD_REG                = WD2_REG_HV_U_TARGET_8_15_MOD_FLAG
WD2_HV_U_TARGET_9_MOD_MASK               =                        0x0F000000
WD2_HV_U_TARGET_9_MOD_OFS                =                                24

# HV_U_TARGET_10_MOD - Target high voltage channel 10 register modified flags
WD2_HV_U_TARGET_10_MOD_REG               = WD2_REG_HV_U_TARGET_8_15_MOD_FLAG
WD2_HV_U_TARGET_10_MOD_MASK              =                        0x00F00000
WD2_HV_U_TARGET_10_MOD_OFS               =                                20

# HV_U_TARGET_11_MOD - Target high voltage channel 11 register modified flags
WD2_HV_U_TARGET_11_MOD_REG               = WD2_REG_HV_U_TARGET_8_15_MOD_FLAG
WD2_HV_U_TARGET_11_MOD_MASK              =                        0x000F0000
WD2_HV_U_TARGET_11_MOD_OFS               =                                16

# HV_U_TARGET_12_MOD - Target high voltage channel 12 register modified flags
WD2_HV_U_TARGET_12_MOD_REG               = WD2_REG_HV_U_TARGET_8_15_MOD_FLAG
WD2_HV_U_TARGET_12_MOD_MASK              =                        0x0000F000
WD2_HV_U_TARGET_12_MOD_OFS               =                                12

# HV_U_TARGET_13_MOD - Target high voltage channel 13 register modified flags
WD2_HV_U_TARGET_13_MOD_REG               = WD2_REG_HV_U_TARGET_8_15_MOD_FLAG
WD2_HV_U_TARGET_13_MOD_MASK              =                        0x00000F00
WD2_HV_U_TARGET_13_MOD_OFS               =                                 8

# HV_U_TARGET_14_MOD - Target high voltage channel 14 register modified flags
WD2_HV_U_TARGET_14_MOD_REG               = WD2_REG_HV_U_TARGET_8_15_MOD_FLAG
WD2_HV_U_TARGET_14_MOD_MASK              =                        0x000000F0
WD2_HV_U_TARGET_14_MOD_OFS               =                                 4

# HV_U_TARGET_15_MOD - Target high voltage channel 15 register modified flags
WD2_HV_U_TARGET_15_MOD_REG               = WD2_REG_HV_U_TARGET_8_15_MOD_FLAG
WD2_HV_U_TARGET_15_MOD_MASK              =                        0x0000000F
WD2_HV_U_TARGET_15_MOD_OFS               =                                 0



# ****** Status Register 86 [0x0158]: HV_MOD_FLAG - Set if single HV configuraiton registers are modified (Default: 0x00000000) ******

# HV_R_SHUNT_MOD - HV supply shunt resistor register modified flags
WD2_HV_R_SHUNT_MOD_REG                   =               WD2_REG_HV_MOD_FLAG
WD2_HV_R_SHUNT_MOD_MASK                  =                        0x0000000F
WD2_HV_R_SHUNT_MOD_OFS                   =                                 0



# ****** Status Register 87 [0x015C]: LMK_0_7_MOD_FLAG - Set if LMK configuraiton registers are modified (Default: 0x00000000) ******

# LMK_0_MOD - LMK channel 0 register modified flags
WD2_LMK_0_MOD_REG                        =          WD2_REG_LMK_0_7_MOD_FLAG
WD2_LMK_0_MOD_MASK                       =                        0xF0000000
WD2_LMK_0_MOD_OFS                        =                                28

# LMK_1_MOD - LMK channel 1 register modified flags
WD2_LMK_1_MOD_REG                        =          WD2_REG_LMK_0_7_MOD_FLAG
WD2_LMK_1_MOD_MASK                       =                        0x0F000000
WD2_LMK_1_MOD_OFS                        =                                24

# LMK_2_MOD - LMK channel 2 register modified flags
WD2_LMK_2_MOD_REG                        =          WD2_REG_LMK_0_7_MOD_FLAG
WD2_LMK_2_MOD_MASK                       =                        0x00F00000
WD2_LMK_2_MOD_OFS                        =                                20

# LMK_3_MOD - LMK channel 3 register modified flags
WD2_LMK_3_MOD_REG                        =          WD2_REG_LMK_0_7_MOD_FLAG
WD2_LMK_3_MOD_MASK                       =                        0x000F0000
WD2_LMK_3_MOD_OFS                        =                                16

# LMK_4_MOD - LMK channel 4 register modified flags
WD2_LMK_4_MOD_REG                        =          WD2_REG_LMK_0_7_MOD_FLAG
WD2_LMK_4_MOD_MASK                       =                        0x0000F000
WD2_LMK_4_MOD_OFS                        =                                12

# LMK_5_MOD - LMK channel 5 register modified flags
WD2_LMK_5_MOD_REG                        =          WD2_REG_LMK_0_7_MOD_FLAG
WD2_LMK_5_MOD_MASK                       =                        0x00000F00
WD2_LMK_5_MOD_OFS                        =                                 8

# LMK_6_MOD - LMK channel 6 register modified flags
WD2_LMK_6_MOD_REG                        =          WD2_REG_LMK_0_7_MOD_FLAG
WD2_LMK_6_MOD_MASK                       =                        0x000000F0
WD2_LMK_6_MOD_OFS                        =                                 4

# LMK_7_MOD - LMK channel 7 register modified flags
WD2_LMK_7_MOD_REG                        =          WD2_REG_LMK_0_7_MOD_FLAG
WD2_LMK_7_MOD_MASK                       =                        0x0000000F
WD2_LMK_7_MOD_OFS                        =                                 0



# ****** Status Register 88 [0x0160]: LMK_8_15_MOD_FLAG - Set if LMK configuraiton registers are modified (Default: 0x00000000) ******

# LMK_8_MOD - LMK Register 8 modified flags
WD2_LMK_8_MOD_REG                        =         WD2_REG_LMK_8_15_MOD_FLAG
WD2_LMK_8_MOD_MASK                       =                        0x00F00000
WD2_LMK_8_MOD_OFS                        =                                20

# LMK_9_MOD - LMK Register 9 modified flags
WD2_LMK_9_MOD_REG                        =         WD2_REG_LMK_8_15_MOD_FLAG
WD2_LMK_9_MOD_MASK                       =                        0x000F0000
WD2_LMK_9_MOD_OFS                        =                                16

# LMK_11_MOD - LMK Register 11 modified flags
WD2_LMK_11_MOD_REG                       =         WD2_REG_LMK_8_15_MOD_FLAG
WD2_LMK_11_MOD_MASK                      =                        0x0000F000
WD2_LMK_11_MOD_OFS                       =                                12

# LMK_13_MOD - LMK Register 13 modified flags
WD2_LMK_13_MOD_REG                       =         WD2_REG_LMK_8_15_MOD_FLAG
WD2_LMK_13_MOD_MASK                      =                        0x00000F00
WD2_LMK_13_MOD_OFS                       =                                 8

# LMK_14_MOD - LMK Register 14 modified flags
WD2_LMK_14_MOD_REG                       =         WD2_REG_LMK_8_15_MOD_FLAG
WD2_LMK_14_MOD_MASK                      =                        0x000000F0
WD2_LMK_14_MOD_OFS                       =                                 4

# LMK_15_MOD - LMK Register 15 modified flags
WD2_LMK_15_MOD_REG                       =         WD2_REG_LMK_8_15_MOD_FLAG
WD2_LMK_15_MOD_MASK                      =                        0x0000000F
WD2_LMK_15_MOD_OFS                       =                                 0



# Number of Registers
 

REG_NR_OF_CTRL_REGS          = 139
REG_NR_OF_STAT_REGS          = 89



# List of register names and offsets
 


wd2_reg_list = [
  [ "WDB_LOC"                   , WD2_REG_WDB_LOC                   , "None"                           , "Location where the WD2 is plugged in" ],
  [ "CTRL"                      , WD2_REG_CTRL                      , "None"                           , "DAQ control register" ],
  [ "CAL_CTRL"                  , WD2_REG_CAL_CTRL                  , "None"                           , "Clock and Calibration Control" ],
  [ "CLK_CTRL"                  , WD2_REG_CLK_CTRL                  , "None"                           , "Clock Control" ],
  [ "DRS_CTRL"                  , WD2_REG_DRS_CTRL                  , "None"                           , "DRS4 Control and Configuration Registers" ],
  [ "COM_CTRL"                  , WD2_REG_COM_CTRL                  , "None"                           , "Communication Control Register" ],
  [ "COM_PLD_SIZE"              , WD2_REG_COM_PLD_SIZE              , "None"                           , "Maximum Payload Size" ],
  [ "DRS_CH_TX_EN"              , WD2_REG_DRS_CH_TX_EN              , "None"                           , "DRS Channel Transmission Enable Register" ],
  [ "ADC_CH_TX_EN"              , WD2_REG_ADC_CH_TX_EN              , "None"                           , "ADC Channel Transmission Enable Register" ],
  [ "TDC_CH_TX_EN"              , WD2_REG_TDC_CH_TX_EN              , "None"                           , "TDC Channel Transmission Enable Register" ],
  [ "DRS_TX_SAMPLES"            , WD2_REG_DRS_TX_SAMPLES            , "None"                           , "DRS Samples to transmit" ],
  [ "ADC_TX_SAMPLES"            , WD2_REG_ADC_TX_SAMPLES            , "None"                           , "ADC Samples to transmit" ],
  [ "TDC_TX_SAMPLES"            , WD2_REG_TDC_TX_SAMPLES            , "None"                           , "TDC Samples to transmit" ],
  [ "TRG_TX_SAMPLES"            , WD2_REG_TRG_TX_SAMPLES            , "None"                           , "TRG Samples to transmit" ],
  [ "ADC_SAMPLE_DIV"            , WD2_REG_ADC_SAMPLE_DIV            , "None"                           , "ADC Downsampling Divider" ],
  [ "ZERO_SUPR"                 , WD2_REG_ZERO_SUPR                 , "None"                           , "Zero Suppression Configuration Register" ],
  [ "RST"                       , WD2_REG_RST                       , "None"                           , "Reset bits for specific firmwar units" ],
  [ "APLY_CFG"                  , WD2_REG_APLY_CFG                  , "None"                           , "Apply settings from regsiter bank to hardware units" ],
  [ "DAC0_A_B"                  , WD2_REG_DAC0_A_B                  , "DAC"                            , "DAC0 values for Channel A and B" ],
  [ "DAC0_C_D"                  , WD2_REG_DAC0_C_D                  , "DAC"                            , "DAC0 values for Channel C and D" ],
  [ "DAC0_E_F"                  , WD2_REG_DAC0_E_F                  , "DAC"                            , "DAC0 values for Channel E and F" ],
  [ "DAC0_G_H"                  , WD2_REG_DAC0_G_H                  , "DAC"                            , "DAC0 values for Channel G and H" ],
  [ "DAC1_A_B"                  , WD2_REG_DAC1_A_B                  , "DAC"                            , "DAC1 values for Channel A and B" ],
  [ "DAC1_C_D"                  , WD2_REG_DAC1_C_D                  , "DAC"                            , "DAC1 values for Channel C and D" ],
  [ "DAC1_E_F"                  , WD2_REG_DAC1_E_F                  , "DAC"                            , "DAC1 values for Channel E and F" ],
  [ "DAC1_G_H"                  , WD2_REG_DAC1_G_H                  , "DAC"                            , "DAC1 values for Channel G and H" ],
  [ "DAC2_A_B"                  , WD2_REG_DAC2_A_B                  , "DAC"                            , "DAC2 values for Channel A and B" ],
  [ "DAC2_C_D"                  , WD2_REG_DAC2_C_D                  , "DAC"                            , "DAC2 values for Channel C and D" ],
  [ "DAC2_E_F"                  , WD2_REG_DAC2_E_F                  , "DAC"                            , "DAC2 values for Channel E and F" ],
  [ "DAC2_G_H"                  , WD2_REG_DAC2_G_H                  , "DAC"                            , "DAC2 values for Channel G and H" ],
  [ "FE_CFG_0_1"                , WD2_REG_FE_CFG_0_1                , "FE_CFG"                         , "Frontend Settings for Channel 0 and 1" ],
  [ "FE_CFG_2_3"                , WD2_REG_FE_CFG_2_3                , "FE_CFG"                         , "Frontend Settings for Channel 2 and 3" ],
  [ "FE_CFG_4_5"                , WD2_REG_FE_CFG_4_5                , "FE_CFG"                         , "Frontend Settings for Channel 4 and 5" ],
  [ "FE_CFG_6_7"                , WD2_REG_FE_CFG_6_7                , "FE_CFG"                         , "Frontend Settings for Channel 6 and 7" ],
  [ "FE_CFG_8_9"                , WD2_REG_FE_CFG_8_9                , "FE_CFG"                         , "Frontend Settings for Channel 8 and 9" ],
  [ "FE_CFG_10_11"              , WD2_REG_FE_CFG_10_11              , "FE_CFG"                         , "Frontend Settings for Channel 10 and 11" ],
  [ "FE_CFG_12_13"              , WD2_REG_FE_CFG_12_13              , "FE_CFG"                         , "Frontend Settings for Channel 12 and 13" ],
  [ "FE_CFG_14_15"              , WD2_REG_FE_CFG_14_15              , "FE_CFG"                         , "Frontend Settings for Channel 14 and 15" ],
  [ "HV_U_TARGET_0"             , WD2_REG_HV_U_TARGET_0             , "HV_U_TARGET"                    , "Target HV Supply Voltage for Channel 0" ],
  [ "HV_U_TARGET_1"             , WD2_REG_HV_U_TARGET_1             , "HV_U_TARGET"                    , "Target HV Supply Voltage for Channel 1" ],
  [ "HV_U_TARGET_2"             , WD2_REG_HV_U_TARGET_2             , "HV_U_TARGET"                    , "Target HV Supply Voltage for Channel 2" ],
  [ "HV_U_TARGET_3"             , WD2_REG_HV_U_TARGET_3             , "HV_U_TARGET"                    , "Target HV Supply Voltage for Channel 3" ],
  [ "HV_U_TARGET_4"             , WD2_REG_HV_U_TARGET_4             , "HV_U_TARGET"                    , "Target HV Supply Voltage for Channel 4" ],
  [ "HV_U_TARGET_5"             , WD2_REG_HV_U_TARGET_5             , "HV_U_TARGET"                    , "Target HV Supply Voltage for Channel 5" ],
  [ "HV_U_TARGET_6"             , WD2_REG_HV_U_TARGET_6             , "HV_U_TARGET"                    , "Target HV Supply Voltage for Channel 6" ],
  [ "HV_U_TARGET_7"             , WD2_REG_HV_U_TARGET_7             , "HV_U_TARGET"                    , "Target HV Supply Voltage for Channel 7" ],
  [ "HV_U_TARGET_8"             , WD2_REG_HV_U_TARGET_8             , "HV_U_TARGET"                    , "Target HV Supply Voltage for Channel 8" ],
  [ "HV_U_TARGET_9"             , WD2_REG_HV_U_TARGET_9             , "HV_U_TARGET"                    , "Target HV Supply Voltage for Channel 9" ],
  [ "HV_U_TARGET_10"            , WD2_REG_HV_U_TARGET_10            , "HV_U_TARGET"                    , "Target HV Supply Voltage for Channel 10" ],
  [ "HV_U_TARGET_11"            , WD2_REG_HV_U_TARGET_11            , "HV_U_TARGET"                    , "Target HV Supply Voltage for Channel 11" ],
  [ "HV_U_TARGET_12"            , WD2_REG_HV_U_TARGET_12            , "HV_U_TARGET"                    , "Target HV Supply Voltage for Channel 12" ],
  [ "HV_U_TARGET_13"            , WD2_REG_HV_U_TARGET_13            , "HV_U_TARGET"                    , "Target HV Supply Voltage for Channel 13" ],
  [ "HV_U_TARGET_14"            , WD2_REG_HV_U_TARGET_14            , "HV_U_TARGET"                    , "Target HV Supply Voltage for Channel 14" ],
  [ "HV_U_TARGET_15"            , WD2_REG_HV_U_TARGET_15            , "HV_U_TARGET"                    , "Target HV Supply Voltage for Channel 15" ],
  [ "HV_R_SHUNT"                , WD2_REG_HV_R_SHUNT                , "None"                           , "Value of the HV Supply Shunt Resistor" ],
  [ "LMK_0"                     , WD2_REG_LMK_0                     , "LMK"                            , "LMK Register 0" ],
  [ "LMK_1"                     , WD2_REG_LMK_1                     , "LMK"                            , "LMK Register 1" ],
  [ "LMK_2"                     , WD2_REG_LMK_2                     , "LMK"                            , "LMK Register 2" ],
  [ "LMK_3"                     , WD2_REG_LMK_3                     , "LMK"                            , "LMK Register 3" ],
  [ "LMK_4"                     , WD2_REG_LMK_4                     , "LMK"                            , "LMK Register 4" ],
  [ "LMK_5"                     , WD2_REG_LMK_5                     , "LMK"                            , "LMK Register 5" ],
  [ "LMK_6"                     , WD2_REG_LMK_6                     , "LMK"                            , "LMK Register 6" ],
  [ "LMK_7"                     , WD2_REG_LMK_7                     , "LMK"                            , "LMK Register 7" ],
  [ "LMK_8"                     , WD2_REG_LMK_8                     , "LMK"                            , "LMK Register 8" ],
  [ "LMK_9"                     , WD2_REG_LMK_9                     , "LMK"                            , "LMK Register 9" ],
  [ "LMK_11"                    , WD2_REG_LMK_11                    , "LMK"                            , "LMK Register 11" ],
  [ "LMK_13"                    , WD2_REG_LMK_13                    , "LMK"                            , "LMK Register 13" ],
  [ "LMK_14"                    , WD2_REG_LMK_14                    , "LMK"                            , "LMK Register 14" ],
  [ "LMK_15"                    , WD2_REG_LMK_15                    , "LMK"                            , "LMK Register 15" ],
  [ "ADC_0_CFG_1458"            , WD2_REG_ADC_0_CFG_1458            , "ADC"                            , "ADC 0 (A) Chip Configuration for channels 1, 4, 5 and 8" ],
  [ "ADC_0_CFG_2367"            , WD2_REG_ADC_0_CFG_2367            , "ADC"                            , "ADC 0 (A) Chip Configuration for channels 2, 3, 6 and 7" ],
  [ "ADC_1_CFG_1458"            , WD2_REG_ADC_1_CFG_1458            , "ADC"                            , "ADC 1 (B) Chip Configuration for channels 1, 4, 5 and 8" ],
  [ "ADC_1_CFG_2367"            , WD2_REG_ADC_1_CFG_2367            , "ADC"                            , "ADC 1 (B) Chip Configuration for channels 2, 3, 6 and 7" ],
  [ "TRG_CFG"                   , WD2_REG_TRG_CFG                   , "TRIGGER"                        , "Trigger Configuration" ],
  [ "TRG_SRC_POL"               , WD2_REG_TRG_SRC_POL               , "TRIGGER"                        , "Trigger Source Polarity" ],
  [ "TRG_AUTO_PERIOD"           , WD2_REG_TRG_AUTO_PERIOD           , "TRIGGER"                        , "Automatic Trigger Period" ],
  [ "TRG_PTRN_EN"               , WD2_REG_TRG_PTRN_EN               , "TRIGGER"                        , "Enable for trigger patterns" ],
  [ "TRG_SRC_EN_PTRN0"          , WD2_REG_TRG_SRC_EN_PTRN0          , "TRIGGER"                        , "Trigger Source Enable Pattern 0" ],
  [ "TRG_STATE_PTRN0"           , WD2_REG_TRG_STATE_PTRN0           , "TRIGGER"                        , "Trigger State Pattern 0" ],
  [ "TRG_SRC_EN_PTRN1"          , WD2_REG_TRG_SRC_EN_PTRN1          , "TRIGGER"                        , "Trigger Source Enable Pattern 1" ],
  [ "TRG_STATE_PTRN1"           , WD2_REG_TRG_STATE_PTRN1           , "TRIGGER"                        , "Trigger State Pattern 1" ],
  [ "TRG_SRC_EN_PTRN2"          , WD2_REG_TRG_SRC_EN_PTRN2          , "TRIGGER"                        , "Trigger Source Enable Pattern 2" ],
  [ "TRG_STATE_PTRN2"           , WD2_REG_TRG_STATE_PTRN2           , "TRIGGER"                        , "Trigger State Pattern 2" ],
  [ "TRG_SRC_EN_PTRN3"          , WD2_REG_TRG_SRC_EN_PTRN3          , "TRIGGER"                        , "Trigger Source Enable Pattern 3" ],
  [ "TRG_STATE_PTRN3"           , WD2_REG_TRG_STATE_PTRN3           , "TRIGGER"                        , "Trigger State Pattern 3" ],
  [ "TRG_SRC_EN_PTRN4"          , WD2_REG_TRG_SRC_EN_PTRN4          , "TRIGGER"                        , "Trigger Source Enable Pattern 4" ],
  [ "TRG_STATE_PTRN4"           , WD2_REG_TRG_STATE_PTRN4           , "TRIGGER"                        , "Trigger State Pattern 4" ],
  [ "TRG_SRC_EN_PTRN5"          , WD2_REG_TRG_SRC_EN_PTRN5          , "TRIGGER"                        , "Trigger Source Enable Pattern 5" ],
  [ "TRG_STATE_PTRN5"           , WD2_REG_TRG_STATE_PTRN5           , "TRIGGER"                        , "Trigger State Pattern 5" ],
  [ "TRG_SRC_EN_PTRN6"          , WD2_REG_TRG_SRC_EN_PTRN6          , "TRIGGER"                        , "Trigger Source Enable Pattern 6" ],
  [ "TRG_STATE_PTRN6"           , WD2_REG_TRG_STATE_PTRN6           , "TRIGGER"                        , "Trigger State Pattern 6" ],
  [ "TRG_SRC_EN_PTRN7"          , WD2_REG_TRG_SRC_EN_PTRN7          , "TRIGGER"                        , "Trigger Source Enable Pattern 7" ],
  [ "TRG_STATE_PTRN7"           , WD2_REG_TRG_STATE_PTRN7           , "TRIGGER"                        , "Trigger State Pattern 7" ],
  [ "TRG_SRC_EN_PTRN8"          , WD2_REG_TRG_SRC_EN_PTRN8          , "TRIGGER"                        , "Trigger Source Enable Pattern 8" ],
  [ "TRG_STATE_PTRN8"           , WD2_REG_TRG_STATE_PTRN8           , "TRIGGER"                        , "Trigger State Pattern 8" ],
  [ "TRG_SRC_EN_PTRN9"          , WD2_REG_TRG_SRC_EN_PTRN9          , "TRIGGER"                        , "Trigger Source Enable Pattern 9" ],
  [ "TRG_STATE_PTRN9"           , WD2_REG_TRG_STATE_PTRN9           , "TRIGGER"                        , "Trigger State Pattern 9" ],
  [ "TRG_SRC_EN_PTRN10"         , WD2_REG_TRG_SRC_EN_PTRN10         , "TRIGGER"                        , "Trigger Source Enable Pattern 10" ],
  [ "TRG_STATE_PTRN10"          , WD2_REG_TRG_STATE_PTRN10          , "TRIGGER"                        , "Trigger State Pattern 10" ],
  [ "TRG_SRC_EN_PTRN11"         , WD2_REG_TRG_SRC_EN_PTRN11         , "TRIGGER"                        , "Trigger Source Enable Pattern 11" ],
  [ "TRG_STATE_PTRN11"          , WD2_REG_TRG_STATE_PTRN11          , "TRIGGER"                        , "Trigger State Pattern 11" ],
  [ "TRG_SRC_EN_PTRN12"         , WD2_REG_TRG_SRC_EN_PTRN12         , "TRIGGER"                        , "Trigger Source Enable Pattern 12" ],
  [ "TRG_STATE_PTRN12"          , WD2_REG_TRG_STATE_PTRN12          , "TRIGGER"                        , "Trigger State Pattern 12" ],
  [ "TRG_SRC_EN_PTRN13"         , WD2_REG_TRG_SRC_EN_PTRN13         , "TRIGGER"                        , "Trigger Source Enable Pattern 13" ],
  [ "TRG_STATE_PTRN13"          , WD2_REG_TRG_STATE_PTRN13          , "TRIGGER"                        , "Trigger State Pattern 13" ],
  [ "TRG_SRC_EN_PTRN14"         , WD2_REG_TRG_SRC_EN_PTRN14         , "TRIGGER"                        , "Trigger Source Enable Pattern 14" ],
  [ "TRG_STATE_PTRN14"          , WD2_REG_TRG_STATE_PTRN14          , "TRIGGER"                        , "Trigger State Pattern 14" ],
  [ "TRG_SRC_EN_PTRN15"         , WD2_REG_TRG_SRC_EN_PTRN15         , "TRIGGER"                        , "Trigger Source Enable Pattern 15" ],
  [ "TRG_STATE_PTRN15"          , WD2_REG_TRG_STATE_PTRN15          , "TRIGGER"                        , "Trigger State Pattern 15" ],
  [ "TRG_SRC_EN_PTRN16"         , WD2_REG_TRG_SRC_EN_PTRN16         , "TRIGGER"                        , "Trigger Source Enable Pattern 16" ],
  [ "TRG_STATE_PTRN16"          , WD2_REG_TRG_STATE_PTRN16          , "TRIGGER"                        , "Trigger State Pattern 16" ],
  [ "TRG_SRC_EN_PTRN17"         , WD2_REG_TRG_SRC_EN_PTRN17         , "TRIGGER"                        , "Trigger Source Enable Pattern 17" ],
  [ "TRG_STATE_PTRN17"          , WD2_REG_TRG_STATE_PTRN17          , "TRIGGER"                        , "Trigger State Pattern 17" ],
  [ "TRG_SRC_EN_PTRN18"         , WD2_REG_TRG_SRC_EN_PTRN18         , "TRIGGER"                        , "Trigger Source Enable Pattern 18" ],
  [ "TRG_STATE_PTRN18"          , WD2_REG_TRG_STATE_PTRN18          , "TRIGGER"                        , "Trigger State Pattern 18" ],
  [ "ADV_TRG_CTRL"              , WD2_REG_ADV_TRG_CTRL              , "ADV_TRG_CTRL"                   , "Advanced Trigger Control Register" ],
  [ "ADV_TRG_CH_CAL0"           , WD2_REG_ADV_TRG_CH_CAL0           , "ADV_TRG_CTRL"                   , "Advanced Trigger Channel Calibration Register 0" ],
  [ "ADV_TRG_CH_CAL1"           , WD2_REG_ADV_TRG_CH_CAL1           , "ADV_TRG_CTRL"                   , "Advanced Trigger Channel Calibration Register 1" ],
  [ "ADV_TRG_CH_CAL2"           , WD2_REG_ADV_TRG_CH_CAL2           , "ADV_TRG_CTRL"                   , "Advanced Trigger Channel Calibration Register 2" ],
  [ "ADV_TRG_CH_CAL3"           , WD2_REG_ADV_TRG_CH_CAL3           , "ADV_TRG_CTRL"                   , "Advanced Trigger Channel Calibration Register 3" ],
  [ "ADV_TRG_PED_CFG"           , WD2_REG_ADV_TRG_PED_CFG           , "ADV_TRG_CTRL"                   , "Advanced Trigger Pedestal Configuration Register" ],
  [ "ADV_TRG_THR0"              , WD2_REG_ADV_TRG_THR0              , "ADV_TRG_CTRL"                   , "Advanced Trigger Threshold 0 Register" ],
  [ "ADV_TRG_THR1"              , WD2_REG_ADV_TRG_THR1              , "ADV_TRG_CTRL"                   , "Advanced Trigger Threshold 1 Register" ],
  [ "ADV_TRG_THR2"              , WD2_REG_ADV_TRG_THR2              , "ADV_TRG_CTRL"                   , "Advanced Trigger Threshold 2 Register" ],
  [ "ADV_TRG_TX_CHK_WORD0"      , WD2_REG_ADV_TRG_TX_CHK_WORD0      , "ADV_TRG_CTRL"                   , "Advanced Trigger Transmition Check Word 0 Register" ],
  [ "ADV_TRG_TX_CHK_WORD1"      , WD2_REG_ADV_TRG_TX_CHK_WORD1      , "ADV_TRG_CTRL"                   , "Advanced Trigger Transmition Check Word 1 Register" ],
  [ "ADV_TRG_TDC_CH_MASK"       , WD2_REG_ADV_TRG_TDC_CH_MASK       , "ADV_TRG_CTRL"                   , "Advanced Trigger TDC Channel Mask" ],
  [ "ADV_TRG_CFG12"             , WD2_REG_ADV_TRG_CFG12             , "ADV_TRG_CTRL"                   , "Advanced Trigger Configuration Register 12" ],
  [ "ADV_TRG_CFG13"             , WD2_REG_ADV_TRG_CFG13             , "ADV_TRG_CTRL"                   , "Advanced Trigger Configuration Register 13" ],
  [ "ADV_TRG_CFG14"             , WD2_REG_ADV_TRG_CFG14             , "ADV_TRG_CTRL"                   , "Advanced Trigger Configuration Register 14" ],
  [ "ADV_TRG_CFG15"             , WD2_REG_ADV_TRG_CFG15             , "ADV_TRG_CTRL"                   , "Advanced Trigger Configuration Register 15" ],
  [ "ADV_TRG_CFG16"             , WD2_REG_ADV_TRG_CFG16             , "ADV_TRG_CTRL"                   , "Advanced Trigger Configuration Register 16" ],
  [ "ADV_TRG_CFG17"             , WD2_REG_ADV_TRG_CFG17             , "ADV_TRG_CTRL"                   , "Advanced Trigger Configuration Register 17" ],
  [ "ADV_TRG_CFG18"             , WD2_REG_ADV_TRG_CFG18             , "ADV_TRG_CTRL"                   , "Advanced Trigger Configuration Register 18" ],
  [ "ADV_TRG_CFG19"             , WD2_REG_ADV_TRG_CFG19             , "ADV_TRG_CTRL"                   , "Advanced Trigger Configuration Register 19" ],
  [ "SET_TIME_LSB"              , WD2_REG_SET_TIME_LSB              , "None"                           , "Set System Time" ],
  [ "SET_TIME_MSB"              , WD2_REG_SET_TIME_MSB              , "None"                           , "Set System Time" ],
  [ "DBG_SIG_SEL"               , WD2_REG_DBG_SIG_SEL               , "None"                           , "Debug Signal Select for MCX Connectors on HV Board" ],
  [ "CRC32_REG_BANK"            , WD2_REG_CRC32_REG_BANK            , "None"                           , "CRC32 Checksum of Register Bank Content" ],
  [ "HW_VER"                    , WD2_REG_HW_VER                    , "None"                           , "Hardware version information of the PCB" ],
  [ "REG_LAYOUT_VER"            , WD2_REG_REG_LAYOUT_VER            , "None"                           , "Register map layout version information" ],
  [ "FW_BUILD_DATE"             , WD2_REG_FW_BUILD_DATE             , "None"                           , "Date when the firmware was built" ],
  [ "FW_BUILD_TIME"             , WD2_REG_FW_BUILD_TIME             , "None"                           , "Time when the firmware was built and compatibility level" ],
  [ "SW_BUILD_DATE"             , WD2_REG_SW_BUILD_DATE             , "None"                           , "Date when the software was built" ],
  [ "SW_BUILD_TIME"             , WD2_REG_SW_BUILD_TIME             , "None"                           , "Time when the software was built and compatibility level" ],
  [ "FW_GIT_HASH_TAG"           , WD2_REG_FW_GIT_HASH_TAG           , "None"                           , "Hash tag of the firmware commit in the GIT repository" ],
  [ "SW_GIT_HASH_TAG"           , WD2_REG_SW_GIT_HASH_TAG           , "None"                           , "Hash tag of the software commit in the GIT repository" ],
  [ "PROT_VER"                  , WD2_REG_PROT_VER                  , "None"                           , "Vesion of the WaveDream2 protocol" ],
  [ "SN"                        , WD2_REG_SN                        , "None"                           , "Serial Number of the WD2 Board (Board ID)" ],
  [ "STATUS"                    , WD2_REG_STATUS                    , "None"                           , "Status Register" ],
  [ "PLL_LOCK"                  , WD2_REG_PLL_LOCK                  , "None"                           , "Lock Status of PLLs" ],
  [ "DRS_STOP_CELL"             , WD2_REG_DRS_STOP_CELL             , "None"                           , "Position where sampling stopped at last trigger in DRS" ],
  [ "DRS_STOP_WSR"              , WD2_REG_DRS_STOP_WSR              , "None"                           , "Write shift register contents when sampling stopped in DRS" ],
  [ "DRS_SAMPLE_FREQ"           , WD2_REG_DRS_SAMPLE_FREQ           , "None"                           , "DRS Sampling frequency" ],
  [ "ADC_SAMPLE_FREQ"           , WD2_REG_ADC_SAMPLE_FREQ           , "None"                           , "ADC Sampling Frequency in MHz" ],
  [ "TDC_SAMPLE_FREQ"           , WD2_REG_TDC_SAMPLE_FREQ           , "None"                           , "TDC Sampling Frequency in MHz" ],
  [ "HV_VER"                    , WD2_REG_HV_VER                    , "None"                           , "HV Board Version" ],
  [ "HV_I_MEAS_0"               , WD2_REG_HV_I_MEAS_0               , "HV_I_MEAS"                      , "Measured actual current of the HV supply on channel 0" ],
  [ "HV_I_MEAS_1"               , WD2_REG_HV_I_MEAS_1               , "HV_I_MEAS"                      , "Measured actual current of the HV supply on channel 1" ],
  [ "HV_I_MEAS_2"               , WD2_REG_HV_I_MEAS_2               , "HV_I_MEAS"                      , "Measured actual current of the HV supply on channel 2" ],
  [ "HV_I_MEAS_3"               , WD2_REG_HV_I_MEAS_3               , "HV_I_MEAS"                      , "Measured actual current of the HV supply on channel 3" ],
  [ "HV_I_MEAS_4"               , WD2_REG_HV_I_MEAS_4               , "HV_I_MEAS"                      , "Measured actual current of the HV supply on channel 4" ],
  [ "HV_I_MEAS_5"               , WD2_REG_HV_I_MEAS_5               , "HV_I_MEAS"                      , "Measured actual current of the HV supply on channel 5" ],
  [ "HV_I_MEAS_6"               , WD2_REG_HV_I_MEAS_6               , "HV_I_MEAS"                      , "Measured actual current of the HV supply on channel 6" ],
  [ "HV_I_MEAS_7"               , WD2_REG_HV_I_MEAS_7               , "HV_I_MEAS"                      , "Measured actual current of the HV supply on channel 7" ],
  [ "HV_I_MEAS_8"               , WD2_REG_HV_I_MEAS_8               , "HV_I_MEAS"                      , "Measured actual current of the HV supply on channel 8" ],
  [ "HV_I_MEAS_9"               , WD2_REG_HV_I_MEAS_9               , "HV_I_MEAS"                      , "Measured actual current of the HV supply on channel 9" ],
  [ "HV_I_MEAS_10"              , WD2_REG_HV_I_MEAS_10              , "HV_I_MEAS"                      , "Measured actual current of the HV supply on channel 10" ],
  [ "HV_I_MEAS_11"              , WD2_REG_HV_I_MEAS_11              , "HV_I_MEAS"                      , "Measured actual current of the HV supply on channel 11" ],
  [ "HV_I_MEAS_12"              , WD2_REG_HV_I_MEAS_12              , "HV_I_MEAS"                      , "Measured actual current of the HV supply on channel 12" ],
  [ "HV_I_MEAS_13"              , WD2_REG_HV_I_MEAS_13              , "HV_I_MEAS"                      , "Measured actual current of the HV supply on channel 13" ],
  [ "HV_I_MEAS_14"              , WD2_REG_HV_I_MEAS_14              , "HV_I_MEAS"                      , "Measured actual current of the HV supply on channel 14" ],
  [ "HV_I_MEAS_15"              , WD2_REG_HV_I_MEAS_15              , "HV_I_MEAS"                      , "Measured actual current of the HV supply on channel 15" ],
  [ "HV_U_BASE_MEAS"            , WD2_REG_HV_U_BASE_MEAS            , "None"                           , "Measured actual HV base voltage" ],
  [ "HV_TEMP_0"                 , WD2_REG_HV_TEMP_0                 , "HF_TEMP"                        , "Measured actual temperature of sensor 0 connected to the HV board" ],
  [ "HV_TEMP_1"                 , WD2_REG_HV_TEMP_1                 , "HF_TEMP"                        , "Measured actual temperature of sensor 1 connected to the HV board" ],
  [ "HV_TEMP_2"                 , WD2_REG_HV_TEMP_2                 , "HF_TEMP"                        , "Measured actual temperature of sensor 2 connected to the HV board" ],
  [ "HV_TEMP_3"                 , WD2_REG_HV_TEMP_3                 , "HF_TEMP"                        , "Measured actual temperature of sensor 3 connected to the HV board" ],
  [ "SCALER_0"                  , WD2_REG_SCALER_0                  , "SCALER"                         , "Scaler for input #0" ],
  [ "SCALER_1"                  , WD2_REG_SCALER_1                  , "SCALER"                         , "Scaler for input #1" ],
  [ "SCALER_2"                  , WD2_REG_SCALER_2                  , "SCALER"                         , "Scaler for input #2" ],
  [ "SCALER_3"                  , WD2_REG_SCALER_3                  , "SCALER"                         , "Scaler for input #3" ],
  [ "SCALER_4"                  , WD2_REG_SCALER_4                  , "SCALER"                         , "Scaler for input #4" ],
  [ "SCALER_5"                  , WD2_REG_SCALER_5                  , "SCALER"                         , "Scaler for input #5" ],
  [ "SCALER_6"                  , WD2_REG_SCALER_6                  , "SCALER"                         , "Scaler for input #6" ],
  [ "SCALER_7"                  , WD2_REG_SCALER_7                  , "SCALER"                         , "Scaler for input #7" ],
  [ "SCALER_8"                  , WD2_REG_SCALER_8                  , "SCALER"                         , "Scaler for input #8" ],
  [ "SCALER_9"                  , WD2_REG_SCALER_9                  , "SCALER"                         , "Scaler for input #9" ],
  [ "SCALER_10"                 , WD2_REG_SCALER_10                 , "SCALER"                         , "Scaler for input #10" ],
  [ "SCALER_11"                 , WD2_REG_SCALER_11                 , "SCALER"                         , "Scaler for input #11" ],
  [ "SCALER_12"                 , WD2_REG_SCALER_12                 , "SCALER"                         , "Scaler for input #12" ],
  [ "SCALER_13"                 , WD2_REG_SCALER_13                 , "SCALER"                         , "Scaler for input #13" ],
  [ "SCALER_14"                 , WD2_REG_SCALER_14                 , "SCALER"                         , "Scaler for input #14" ],
  [ "SCALER_15"                 , WD2_REG_SCALER_15                 , "SCALER"                         , "Scaler for input #15" ],
  [ "SCALER_PTRN_TRG"           , WD2_REG_SCALER_PTRN_TRG           , "SCALER"                         , "Scaler for pattern trigger" ],
  [ "SCALER_EXT_TRG"            , WD2_REG_SCALER_EXT_TRG            , "SCALER"                         , "Scaler for external trigger" ],
  [ "SCALER_EXT_CLK"            , WD2_REG_SCALER_EXT_CLK            , "SCALER"                         , "Scaler for ext. clock input" ],
  [ "SCALER_TIME_STAMP_LSB"     , WD2_REG_SCALER_TIME_STAMP_LSB     , "None"                           , "Time Stamp for Scaler Values" ],
  [ "SCALER_TIME_STAMP_MSB"     , WD2_REG_SCALER_TIME_STAMP_MSB     , "None"                           , "Time Stamp for Scaler Values" ],
  [ "TIME_LSB"                  , WD2_REG_TIME_LSB                  , "None"                           , "Current System Time" ],
  [ "TIME_MSB"                  , WD2_REG_TIME_MSB                  , "None"                           , "Current System Time" ],
  [ "COMP_CH_STAT"              , WD2_REG_COMP_CH_STAT              , "None"                           , "Comparator channel status" ],
  [ "EVENT_TX_RATE"             , WD2_REG_EVENT_TX_RATE             , "None"                           , "Event Transmission Rate" ],
  [ "EVENT_NR"                  , WD2_REG_EVENT_NR                  , "None"                           , "Number of latest event" ],
  [ "TRB_INFO_STAT"             , WD2_REG_TRB_INFO_STAT             , "None"                           , "Trigger Information via Serial Trigger Bus Status" ],
  [ "TRB_INFO_LSB"              , WD2_REG_TRB_INFO_LSB              , "None"                           , "Trigger Information via Serial Trigger Bus LSBs" ],
  [ "TRB_INFO_MSB"              , WD2_REG_TRB_INFO_MSB              , "None"                           , "Trigger Information via Serial Trigger Bus MSBs" ],
  [ "ADV_TRG_TRIG_CELL"         , WD2_REG_ADV_TRG_TRIG_CELL         , "ADV_TRG_STAT"                   , "Advanced Trigger Cell Register" ],
  [ "ADV_TRG_STAT1"             , WD2_REG_ADV_TRG_STAT1             , "ADV_TRG_STAT"                   , "Advanced Trigger Status Register 1" ],
  [ "ADV_TRG_STAT2"             , WD2_REG_ADV_TRG_STAT2             , "ADV_TRG_STAT"                   , "Advanced Trigger Status Register 2" ],
  [ "ADV_TRG_STAT3"             , WD2_REG_ADV_TRG_STAT3             , "ADV_TRG_STAT"                   , "Advanced Trigger Status Register 3" ],
  [ "ADV_TRG_STAT4"             , WD2_REG_ADV_TRG_STAT4             , "ADV_TRG_STAT"                   , "Advanced Trigger Status Register 4" ],
  [ "MAX_DRS_ADC_PKT_SAMPLES"   , WD2_REG_MAX_DRS_ADC_PKT_SAMPLES   , "None"                           , "Maximum DRS/ADC samples per Packet" ],
  [ "MAX_TDC_PKT_SAMPLES"       , WD2_REG_MAX_TDC_PKT_SAMPLES       , "None"                           , "Maximum TDC samples per Packet" ],
  [ "MAX_TRG_PKT_SAMPLES"       , WD2_REG_MAX_TRG_PKT_SAMPLES       , "None"                           , "Maximum advanced trigger output samples per Packet" ],
  [ "MAX_SCL_PKT_SAMPLES"       , WD2_REG_MAX_SCL_PKT_SAMPLES       , "None"                           , "Maximum scaler values per Packet" ],
  [ "CLK_CTRL_MOD_FLAG"         , WD2_REG_CLK_CTRL_MOD_FLAG         , "None"                           , "Set if WD2 configuration registers are modified" ],
  [ "DRS_MOD_FLAG"              , WD2_REG_DRS_MOD_FLAG              , "None"                           , "Set if DRS configuration registers are modified" ],
  [ "COM_PLD_SIZE_MOD_FLAG"     , WD2_REG_COM_PLD_SIZE_MOD_FLAG     , "None"                           , "Set if maximum packet payload size register is modified" ],
  [ "ADC_SAMPLE_DIV_MOD_FLAG"   , WD2_REG_ADC_SAMPLE_DIV_MOD_FLAG   , "None"                           , "Set if ADC downsampling divider register is modified" ],
  [ "DAC_0_1_MOD_FLAG"          , WD2_REG_DAC_0_1_MOD_FLAG          , "None"                           , "Set if DAC 0 and 1 configuration registers are modified" ],
  [ "DAC_2_MOD_FLAG"            , WD2_REG_DAC_2_MOD_FLAG            , "None"                           , "Set if DAC 2 configuration registers are modified" ],
  [ "FE_0_15_MOD_FLAG"          , WD2_REG_FE_0_15_MOD_FLAG          , "None"                           , "Set if frontend configuraiton registers are modified" ],
  [ "HV_U_TARGET_0_7_MOD_FLAG"  , WD2_REG_HV_U_TARGET_0_7_MOD_FLAG  , "None"                           , "Set if HV target voltage configuraiton of channel 0 to 7 registers are modified" ],
  [ "HV_U_TARGET_8_15_MOD_FLAG" , WD2_REG_HV_U_TARGET_8_15_MOD_FLAG , "None"                           , "Set if HV target voltage configuraiton of channel 8 to 15 registers are modified" ],
  [ "HV_MOD_FLAG"               , WD2_REG_HV_MOD_FLAG               , "None"                           , "Set if single HV configuraiton registers are modified" ],
  [ "LMK_0_7_MOD_FLAG"          , WD2_REG_LMK_0_7_MOD_FLAG          , "None"                           , "Set if LMK configuraiton registers are modified" ],
  [ "LMK_8_15_MOD_FLAG"         , WD2_REG_LMK_8_15_MOD_FLAG         , "None"                           , "Set if LMK configuraiton registers are modified" ],
]


# List of bit names and parameters
 


wd2_bit_group_list = [
  [ "CRATE_ID"                      , WD2_CRATE_ID_REG                      , WD2_CRATE_ID_MASK                      , WD2_CRATE_ID_OFS                     , "ID of the crate where the current board is plugged in" ],
  [ "SLOT_ID"                       , WD2_SLOT_ID_REG                       , WD2_SLOT_ID_MASK                       , WD2_SLOT_ID_OFS                      , "ID of the slot where the current board is plugged in" ],
  [ "VALID_DELAY_ADC"               , WD2_VALID_DELAY_ADC_REG               , WD2_VALID_DELAY_ADC_MASK               , WD2_VALID_DELAY_ADC_OFS              , "Delay of the data valid at the ISERDES of the ADCs (delay = value + 1)" ],
  [ "DAQ_DATA_PHASE"                , WD2_DAQ_DATA_PHASE_REG                , WD2_DAQ_DATA_PHASE_MASK                , WD2_DAQ_DATA_PHASE_OFS               , "Phase step setting of the PLL generating the common DAQ clock" ],
  [ "FE_POWER"                      , WD2_FE_POWER_REG                      , WD2_FE_POWER_MASK                      , WD2_FE_POWER_OFS                     , "Frontend Power (0=Power OFF, 1=Power ON)" ],
  [ "DRS_CLR_RSR_AFTER_RO"          , WD2_DRS_CLR_RSR_AFTER_RO_REG          , WD2_DRS_CLR_RSR_AFTER_RO_MASK          , WD2_DRS_CLR_RSR_AFTER_RO_OFS         , "Clear the read shift register (remove the token) after each readout" ],
  [ "COMP_POWER_EN"                 , WD2_COMP_POWER_EN_REG                 , WD2_COMP_POWER_EN_MASK                 , WD2_COMP_POWER_EN_OFS                , "Comparator power enable" ],
  [ "DRS_READOUT_MODE"              , WD2_DRS_READOUT_MODE_REG              , WD2_DRS_READOUT_MODE_MASK              , WD2_DRS_READOUT_MODE_OFS             , "0:start from first bin, 1:start from domino stop" ],
  [ "DRS_WAVE_CONTINUOUS"           , WD2_DRS_WAVE_CONTINUOUS_REG           , WD2_DRS_WAVE_CONTINUOUS_MASK           , WD2_DRS_WAVE_CONTINUOUS_OFS          , "0:stop domino wave during readout, 1:keep it running" ],
  [ "DRS_CONFIGURE"                 , WD2_DRS_CONFIGURE_REG                 , WD2_DRS_CONFIGURE_MASK                 , WD2_DRS_CONFIGURE_OFS                , "write a \"1\" to trigger the DRS chip register configuration" ],
  [ "DAQ_SOFT_TRIGGER"              , WD2_DAQ_SOFT_TRIGGER_REG              , WD2_DAQ_SOFT_TRIGGER_MASK              , WD2_DAQ_SOFT_TRIGGER_OFS             , "write a \"1\" to stop the DRS chip & read the data to RAM" ],
  [ "DAQ_AUTO"                      , WD2_DAQ_AUTO_REG                      , WD2_DAQ_AUTO_MASK                      , WD2_DAQ_AUTO_OFS                     , "Auto-Trigger readout state machine every 0.5s if no other trigger (like \"auto\" acquisition on scope)" ],
  [ "DAQ_NORMAL"                    , WD2_DAQ_NORMAL_REG                    , WD2_DAQ_NORMAL_MASK                    , WD2_DAQ_NORMAL_OFS                   , "Restart readout state machine automatically after readout (like \"normal\" acquisition on scope)" ],
  [ "DAQ_SINGLE"                    , WD2_DAQ_SINGLE_REG                    , WD2_DAQ_SINGLE_MASK                    , WD2_DAQ_SINGLE_OFS                   , "Start readout state machine automatically and stop after readout (like \"single\" acquisition on scope)" ],
  [ "ADC_CAL_PATTERN_EN"            , WD2_ADC_CAL_PATTERN_EN_REG            , WD2_ADC_CAL_PATTERN_EN_MASK            , WD2_ADC_CAL_PATTERN_EN_OFS           , "Enable ADC calibration pattern" ],
  [ "DRS_0_TIMING_REF_SEL"          , WD2_DRS_0_TIMING_REF_SEL_REG          , WD2_DRS_0_TIMING_REF_SEL_MASK          , WD2_DRS_0_TIMING_REF_SEL_OFS         , "Select timing reference signal for DRS 0: 0 = oscillator / 1 = LMK (CAL_CTRL_A)" ],
  [ "DRS_1_TIMING_REF_SEL"          , WD2_DRS_1_TIMING_REF_SEL_REG          , WD2_DRS_1_TIMING_REF_SEL_MASK          , WD2_DRS_1_TIMING_REF_SEL_OFS         , "Select timing reference signal for DRS 1: 0 = oscillator / 1 = LMK  (CAL_CTRL_B)" ],
  [ "CALIB_BUFFER_EN"               , WD2_CALIB_BUFFER_EN_REG               , WD2_CALIB_BUFFER_EN_MASK               , WD2_CALIB_BUFFER_EN_OFS              , "Enable buffers driving the calib. signal to the frontend MUX (BUFFER_CTRL)" ],
  [ "TIMING_CALIB_SIGNAL_EN"        , WD2_TIMING_CALIB_SIGNAL_EN_REG        , WD2_TIMING_CALIB_SIGNAL_EN_MASK        , WD2_TIMING_CALIB_SIGNAL_EN_OFS       , "switch on (1) / off (0) 100 MHz calibration signal for DRS chip (TCA_CTRL)" ],
  [ "TRIG_DAQ_CLK_CAL_CHK"          , WD2_TRIG_DAQ_CLK_CAL_CHK_REG          , WD2_TRIG_DAQ_CLK_CAL_CHK_MASK          , WD2_TRIG_DAQ_CLK_CAL_CHK_OFS         , "Trigger DAQ clock calibration check" ],
  [ "DAQ_CLK_SRC_SEL"               , WD2_DAQ_CLK_SRC_SEL_REG               , WD2_DAQ_CLK_SRC_SEL_MASK               , WD2_DAQ_CLK_SRC_SEL_OFS              , "DAQ clock source select: 0 = DCB clock / 1 = on board oscillator (CLK_SEL)" ],
  [ "EXT_CLK_IN_SEL"                , WD2_EXT_CLK_IN_SEL_REG                , WD2_EXT_CLK_IN_SEL_MASK                , WD2_EXT_CLK_IN_SEL_OFS               , "External clk input select: 0 = backplane / 1 = MCX connector (CLK_SEL_EXT)" ],
  [ "EXT_CLK_FREQ"                  , WD2_EXT_CLK_FREQ_REG                  , WD2_EXT_CLK_FREQ_MASK                  , WD2_EXT_CLK_FREQ_OFS                 , "External clock frequency (MCX or backplane) in MHz" ],
  [ "LOCAL_CLK_FREQ"                , WD2_LOCAL_CLK_FREQ_REG                , WD2_LOCAL_CLK_FREQ_MASK                , WD2_LOCAL_CLK_FREQ_OFS               , "Local (on board) oscillator frequency in MHz" ],
  [ "DRS_WSRLOOP"                   , WD2_DRS_WSRLOOP_REG                   , WD2_DRS_WSRLOOP_MASK                   , WD2_DRS_WSRLOOP_OFS                  , "Internally Connect WSRIN to WSROUT (if set to 1)" ],
  [ "DRS_PLLEN"                     , WD2_DRS_PLLEN_REG                     , WD2_DRS_PLLEN_MASK                     , WD2_DRS_PLLEN_OFS                    , "Internal PLL Enable (0 = disable, 1 = enable)" ],
  [ "DRS_DMODE"                     , WD2_DRS_DMODE_REG                     , WD2_DRS_DMODE_MASK                     , WD2_DRS_DMODE_OFS                    , "Domino Mode Control (0 = single shot, 1 = continuous)" ],
  [ "DRS_WSR"                       , WD2_DRS_WSR_REG                       , WD2_DRS_WSR_MASK                       , WD2_DRS_WSR_OFS                      , "DRS4 Write Shift Register (0xD)" ],
  [ "DRS_WCR"                       , WD2_DRS_WCR_REG                       , WD2_DRS_WCR_MASK                       , WD2_DRS_WCR_OFS                      , "DRS4 Write Configuration Register (0xE)" ],
  [ "DCB_SERDES_TRAIN"              , WD2_DCB_SERDES_TRAIN_REG              , WD2_DCB_SERDES_TRAIN_MASK              , WD2_DCB_SERDES_TRAIN_OFS             , "Enable training pattern for DCB SERDES connection" ],
  [ "TCB_SERDES_TRAIN"              , WD2_TCB_SERDES_TRAIN_REG              , WD2_TCB_SERDES_TRAIN_MASK              , WD2_TCB_SERDES_TRAIN_OFS             , "Enable training pattern for TCB SERDES connection" ],
  [ "TRG_TX_EN"                     , WD2_TRG_TX_EN_REG                     , WD2_TRG_TX_EN_MASK                     , WD2_TRG_TX_EN_OFS                    , "enable transmission of advanced trigger output data" ],
  [ "SCL_TX_EN"                     , WD2_SCL_TX_EN_REG                     , WD2_SCL_TX_EN_MASK                     , WD2_SCL_TX_EN_OFS                    , "Enable transmission of scaler data" ],
  [ "SERDES_COM_EN"                 , WD2_SERDES_COM_EN_REG                 , WD2_SERDES_COM_EN_MASK                 , WD2_SERDES_COM_EN_OFS                , "Enable SERDES communication to backplane" ],
  [ "ETH_COM_EN"                    , WD2_ETH_COM_EN_REG                    , WD2_ETH_COM_EN_MASK                    , WD2_ETH_COM_EN_OFS                   , "Enable ethernet communication" ],
  [ "INTER_PKG_DELAY"               , WD2_INTER_PKG_DELAY_REG               , WD2_INTER_PKG_DELAY_MASK               , WD2_INTER_PKG_DELAY_OFS              , "Delay between transmission of two UDP packages in 8ns steps" ],
  [ "FIRST_PKG_DLY"                 , WD2_FIRST_PKG_DLY_REG                 , WD2_FIRST_PKG_DLY_MASK                 , WD2_FIRST_PKG_DLY_OFS                , "Delay of first data packet of an event (resolution 1.6us)" ],
  [ "COM_PLD_SIZE"                  , WD2_COM_PLD_SIZE_REG                  , WD2_COM_PLD_SIZE_MASK                  , WD2_COM_PLD_SIZE_OFS                 , "Maximum number of UDP payload bytes to transmit (must be a multiple of 6 with range 6 to 8892)" ],
  [ "DRS_CH_TX_EN"                  , WD2_DRS_CH_TX_EN_REG                  , WD2_DRS_CH_TX_EN_MASK                  , WD2_DRS_CH_TX_EN_OFS                 , "DRS channel transmission enable [Ch17:Ch0] - (CH17:CH16 = timing channels)" ],
  [ "ADC_CH_TX_EN"                  , WD2_ADC_CH_TX_EN_REG                  , WD2_ADC_CH_TX_EN_MASK                  , WD2_ADC_CH_TX_EN_OFS                 , "ADC channel transmission enable [Ch15:Ch0]" ],
  [ "TDC_CH_TX_EN"                  , WD2_TDC_CH_TX_EN_REG                  , WD2_TDC_CH_TX_EN_MASK                  , WD2_TDC_CH_TX_EN_OFS                 , "TDC channel transmission enable [Ch15:Ch0]" ],
  [ "DRS_TX_SAMPLES"                , WD2_DRS_TX_SAMPLES_REG                , WD2_DRS_TX_SAMPLES_MASK                , WD2_DRS_TX_SAMPLES_OFS               , "Number of DRS samples to transmit per channel (must be an even value with range 2 to 1024)" ],
  [ "ADC_TX_SAMPLES"                , WD2_ADC_TX_SAMPLES_REG                , WD2_ADC_TX_SAMPLES_MASK                , WD2_ADC_TX_SAMPLES_OFS               , "Number of ADC samples to transmit per channel (must be an even value with range 2 to 2048)" ],
  [ "TDC_TX_SAMPLES"                , WD2_TDC_TX_SAMPLES_REG                , WD2_TDC_TX_SAMPLES_MASK                , WD2_TDC_TX_SAMPLES_OFS               , "Number of TDC samples to transmit per channel (must be a multiple of 8 with range 16 to 4096)" ],
  [ "TRG_TX_SAMPLES"                , WD2_TRG_TX_SAMPLES_REG                , WD2_TRG_TX_SAMPLES_MASK                , WD2_TRG_TX_SAMPLES_OFS               , "Number of advanced trigger output samples to transmit (range 1 to 512)" ],
  [ "ADC_SAMPLE_DIV"                , WD2_ADC_SAMPLE_DIV_REG                , WD2_ADC_SAMPLE_DIV_MASK                , WD2_ADC_SAMPLE_DIV_OFS               , "Only store every n-th sample to buffer" ],
  [ "ZERO_SUPR_EN"                  , WD2_ZERO_SUPR_EN_REG                  , WD2_ZERO_SUPR_EN_MASK                  , WD2_ZERO_SUPR_EN_OFS                 , "Enable zero suppression for data transmission (only transmit channels that triggered)" ],
  [ "ZERO_SUPR_WINDOW"              , WD2_ZERO_SUPR_WINDOW_REG              , WD2_ZERO_SUPR_WINDOW_MASK              , WD2_ZERO_SUPR_WINDOW_OFS             , "Zero suppression time window in DAQ clock ticks (channel polarity defined in TRG_SRC_POL)" ],
  [ "DAQ_PLL_RST"                   , WD2_DAQ_PLL_RST_REG                   , WD2_DAQ_PLL_RST_MASK                   , WD2_DAQ_PLL_RST_OFS                  , "Reset the PLL for the DAQ clock" ],
  [ "DCB_OSERDES_PLL_RST"           , WD2_DCB_OSERDES_PLL_RST_REG           , WD2_DCB_OSERDES_PLL_RST_MASK           , WD2_DCB_OSERDES_PLL_RST_OFS          , "Reset the PLL of the DCB OSERDES" ],
  [ "TCB_OSERDES_PLL_RST"           , WD2_TCB_OSERDES_PLL_RST_REG           , WD2_TCB_OSERDES_PLL_RST_MASK           , WD2_TCB_OSERDES_PLL_RST_OFS          , "Reset the PLL of the TCB OSERDES" ],
  [ "DCB_OSERDES_IF_RST"            , WD2_DCB_OSERDES_IF_RST_REG            , WD2_DCB_OSERDES_IF_RST_MASK            , WD2_DCB_OSERDES_IF_RST_OFS           , "Reset the DCB OSERDES interface" ],
  [ "TCB_OSERDES_IF_RST"            , WD2_TCB_OSERDES_IF_RST_REG            , WD2_TCB_OSERDES_IF_RST_MASK            , WD2_TCB_OSERDES_IF_RST_OFS           , "Reset the TCB OSERDES interface" ],
  [ "SCALER_RST"                    , WD2_SCALER_RST_REG                    , WD2_SCALER_RST_MASK                    , WD2_SCALER_RST_OFS                   , "Reset all scalers" ],
  [ "TRB_PARITY_ERROR_COUNT_RST"    , WD2_TRB_PARITY_ERROR_COUNT_RST_REG    , WD2_TRB_PARITY_ERROR_COUNT_RST_MASK    , WD2_TRB_PARITY_ERROR_COUNT_RST_OFS   , "Reset the parity error counter of the trigger info serial connection" ],
  [ "LMK_SYNC_LOCAL"                , WD2_LMK_SYNC_LOCAL_REG                , WD2_LMK_SYNC_LOCAL_MASK                , WD2_LMK_SYNC_LOCAL_OFS               , "Control LMK SYNC signal from FPGA: 0 = run / 1 = sync" ],
  [ "ADC_RST"                       , WD2_ADC_RST_REG                       , WD2_ADC_RST_MASK                       , WD2_ADC_RST_OFS                      , "ADC reset" ],
  [ "ADC_IF_RST"                    , WD2_ADC_IF_RST_REG                    , WD2_ADC_IF_RST_MASK                    , WD2_ADC_IF_RST_OFS                   , "Reset the ADC interface" ],
  [ "DATA_LINK_IF_RST"              , WD2_DATA_LINK_IF_RST_REG              , WD2_DATA_LINK_IF_RST_MASK              , WD2_DATA_LINK_IF_RST_OFS             , "Reset of the interface between packager and Ethernet/SERDES interface" ],
  [ "WD_PKGR_RST"                   , WD2_WD_PKGR_RST_REG                   , WD2_WD_PKGR_RST_MASK                   , WD2_WD_PKGR_RST_OFS                  , "WaveDream packager reset" ],
  [ "EVENT_COUNTER_RST"             , WD2_EVENT_COUNTER_RST_REG             , WD2_EVENT_COUNTER_RST_MASK             , WD2_EVENT_COUNTER_RST_OFS            , "Event Counter Reset" ],
  [ "DRS_CTRL_FSM_RST"              , WD2_DRS_CTRL_FSM_RST_REG              , WD2_DRS_CTRL_FSM_RST_MASK              , WD2_DRS_CTRL_FSM_RST_OFS             , "DRS control FSM reset" ],
  [ "RECONFIGURE_FPGA"              , WD2_RECONFIGURE_FPGA_REG              , WD2_RECONFIGURE_FPGA_MASK              , WD2_RECONFIGURE_FPGA_OFS             , "Initiate FPGA Reconfiguration" ],
  [ "APPLY_SETTINGS_ADC_SAMPLE_DIV" , WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_REG , WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_MASK , WD2_APPLY_SETTINGS_ADC_SAMPLE_DIV_OFS, "Apply configuration from register bank to ADC sampling frequency (auto update)" ],
  [ "APPLY_SETTINGS_MAX_PLD_SIZE"   , WD2_APPLY_SETTINGS_MAX_PLD_SIZE_REG   , WD2_APPLY_SETTINGS_MAX_PLD_SIZE_MASK   , WD2_APPLY_SETTINGS_MAX_PLD_SIZE_OFS  , "Apply configuration from register bank to max samples per packet (auto update)" ],
  [ "APPLY_SETTINGS_HV"             , WD2_APPLY_SETTINGS_HV_REG             , WD2_APPLY_SETTINGS_HV_MASK             , WD2_APPLY_SETTINGS_HV_OFS            , "Apply configuration from register bank to HV (auto update)" ],
  [ "APPLY_SETTINGS_DRS"            , WD2_APPLY_SETTINGS_DRS_REG            , WD2_APPLY_SETTINGS_DRS_MASK            , WD2_APPLY_SETTINGS_DRS_OFS           , "Apply configuration from register bank to DRS chip (auto update)" ],
  [ "APPLY_SETTINGS_DAC"            , WD2_APPLY_SETTINGS_DAC_REG            , WD2_APPLY_SETTINGS_DAC_MASK            , WD2_APPLY_SETTINGS_DAC_OFS           , "Apply configuration from register bank to DAC (auto update)" ],
  [ "APPLY_SETTINGS_FRONTEND"       , WD2_APPLY_SETTINGS_FRONTEND_REG       , WD2_APPLY_SETTINGS_FRONTEND_MASK       , WD2_APPLY_SETTINGS_FRONTEND_OFS      , "Apply configuration from register bank to frontend (auto update)" ],
  [ "APPLY_SETTINGS_CTRL"           , WD2_APPLY_SETTINGS_CTRL_REG           , WD2_APPLY_SETTINGS_CTRL_MASK           , WD2_APPLY_SETTINGS_CTRL_OFS          , "Apply configuration from register bank control register" ],
  [ "APPLY_SETTINGS_ADC"            , WD2_APPLY_SETTINGS_ADC_REG            , WD2_APPLY_SETTINGS_ADC_MASK            , WD2_APPLY_SETTINGS_ADC_OFS           , "Apply configuration from register bank to ADC" ],
  [ "APPLY_SETTINGS_LMK"            , WD2_APPLY_SETTINGS_LMK_REG            , WD2_APPLY_SETTINGS_LMK_MASK            , WD2_APPLY_SETTINGS_LMK_OFS           , "Apply configuration from regsiter bank to LMK" ],
  [ "DAC0_CH_A"                     , WD2_DAC0_CH_A_REG                     , WD2_DAC0_CH_A_MASK                     , WD2_DAC0_CH_A_OFS                    , "Set DAC0 channel A (ROFS) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..2.5V)" ],
  [ "DAC0_CH_B"                     , WD2_DAC0_CH_B_REG                     , WD2_DAC0_CH_B_MASK                     , WD2_DAC0_CH_B_OFS                    , "Set DAC0 channel B (OFS) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (+/- 0.625V)" ],
  [ "DAC0_CH_C"                     , WD2_DAC0_CH_C_REG                     , WD2_DAC0_CH_C_MASK                     , WD2_DAC0_CH_C_OFS                    , "Set DAC0 channel C (CAL_DC) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (+/- 0.625V)" ],
  [ "DAC0_CH_D"                     , WD2_DAC0_CH_D_REG                     , WD2_DAC0_CH_D_MASK                     , WD2_DAC0_CH_D_OFS                    , "Set DAC0 channel D (PULSE_AMP) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..1V)" ],
  [ "DAC0_CH_E"                     , WD2_DAC0_CH_E_REG                     , WD2_DAC0_CH_E_MASK                     , WD2_DAC0_CH_E_OFS                    , "Set DAC0 channel E (PZC_LEVEL) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (+/- 2.5V)" ],
  [ "DAC0_CH_F"                     , WD2_DAC0_CH_F_REG                     , WD2_DAC0_CH_F_MASK                     , WD2_DAC0_CH_F_OFS                    , "Set DAC0 channel F (DAC_REF_A) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..2.5V)" ],
  [ "DAC0_CH_G"                     , WD2_DAC0_CH_G_REG                     , WD2_DAC0_CH_G_MASK                     , WD2_DAC0_CH_G_OFS                    , "Set DAC0 channel G (RESERVED) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..2.5V)" ],
  [ "DAC0_CH_H"                     , WD2_DAC0_CH_H_REG                     , WD2_DAC0_CH_H_MASK                     , WD2_DAC0_CH_H_OFS                    , "Set DAC0 channel H (BIAS) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..2.5V)" ],
  [ "DAC1_CH_A"                     , WD2_DAC1_CH_A_REG                     , WD2_DAC1_CH_A_MASK                     , WD2_DAC1_CH_A_OFS                    , "Set DAC1 channel A (TLEVEL_0) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..2.5V)" ],
  [ "DAC1_CH_B"                     , WD2_DAC1_CH_B_REG                     , WD2_DAC1_CH_B_MASK                     , WD2_DAC1_CH_B_OFS                    , "Set DAC1 channel B (TLEVEL_1) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..2.5V)" ],
  [ "DAC1_CH_C"                     , WD2_DAC1_CH_C_REG                     , WD2_DAC1_CH_C_MASK                     , WD2_DAC1_CH_C_OFS                    , "Set DAC1 channel C (TLEVEL_2) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..2.5V)" ],
  [ "DAC1_CH_D"                     , WD2_DAC1_CH_D_REG                     , WD2_DAC1_CH_D_MASK                     , WD2_DAC1_CH_D_OFS                    , "Set DAC1 channel D (TLEVEL_3) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..2.5V)" ],
  [ "DAC1_CH_E"                     , WD2_DAC1_CH_E_REG                     , WD2_DAC1_CH_E_MASK                     , WD2_DAC1_CH_E_OFS                    , "Set DAC1 channel E (TLEVEL_4) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..2.5V)" ],
  [ "DAC1_CH_F"                     , WD2_DAC1_CH_F_REG                     , WD2_DAC1_CH_F_MASK                     , WD2_DAC1_CH_F_OFS                    , "Set DAC1 channel F (TLEVEL_5) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..2.5V)" ],
  [ "DAC1_CH_G"                     , WD2_DAC1_CH_G_REG                     , WD2_DAC1_CH_G_MASK                     , WD2_DAC1_CH_G_OFS                    , "Set DAC1 channel G (TLEVEL_6) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..2.5V)" ],
  [ "DAC1_CH_H"                     , WD2_DAC1_CH_H_REG                     , WD2_DAC1_CH_H_MASK                     , WD2_DAC1_CH_H_OFS                    , "Set DAC1 channel H (TLEVEL_7) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..2.5V)" ],
  [ "DAC2_CH_A"                     , WD2_DAC2_CH_A_REG                     , WD2_DAC2_CH_A_MASK                     , WD2_DAC2_CH_A_OFS                    , "Set DAC2 channel A (TLEVEL_8) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..2.5V)" ],
  [ "DAC2_CH_B"                     , WD2_DAC2_CH_B_REG                     , WD2_DAC2_CH_B_MASK                     , WD2_DAC2_CH_B_OFS                    , "Set DAC2 channel B (TLEVEL_9) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..2.5V)" ],
  [ "DAC2_CH_C"                     , WD2_DAC2_CH_C_REG                     , WD2_DAC2_CH_C_MASK                     , WD2_DAC2_CH_C_OFS                    , "Set DAC2 channel C (TLEVEL_10) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..2.5V)" ],
  [ "DAC2_CH_D"                     , WD2_DAC2_CH_D_REG                     , WD2_DAC2_CH_D_MASK                     , WD2_DAC2_CH_D_OFS                    , "Set DAC2 channel D (TLEVEL_11) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..2.5V)" ],
  [ "DAC2_CH_E"                     , WD2_DAC2_CH_E_REG                     , WD2_DAC2_CH_E_MASK                     , WD2_DAC2_CH_E_OFS                    , "Set DAC2 channel E (TLEVEL_12) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..2.5V)" ],
  [ "DAC2_CH_F"                     , WD2_DAC2_CH_F_REG                     , WD2_DAC2_CH_F_MASK                     , WD2_DAC2_CH_F_OFS                    , "Set DAC2 channel F (TLEVEL_13) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..2.5V)" ],
  [ "DAC2_CH_G"                     , WD2_DAC2_CH_G_REG                     , WD2_DAC2_CH_G_MASK                     , WD2_DAC2_CH_G_OFS                    , "Set DAC2 channel G (TLEVEL_14) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..2.5V)" ],
  [ "DAC2_CH_H"                     , WD2_DAC2_CH_H_REG                     , WD2_DAC2_CH_H_MASK                     , WD2_DAC2_CH_H_OFS                    , "Set DAC2 channel H (TLEVEL_15) (12 bit MSBs: DAC value, 4 bit LSBs: don\'t care) (0..2.5V)" ],
  [ "FE0_PZC_EN"                    , WD2_FE0_PZC_EN_REG                    , WD2_FE0_PZC_EN_MASK                    , WD2_FE0_PZC_EN_OFS                   , "Frontend channel 0 PZC (pole-zero cancellation) enable (ACDC)" ],
  [ "FE0_AMPLIFIER2_COMP_EN"        , WD2_FE0_AMPLIFIER2_COMP_EN_REG        , WD2_FE0_AMPLIFIER2_COMP_EN_MASK        , WD2_FE0_AMPLIFIER2_COMP_EN_OFS       , "Frontend channel 0 amplifier 2 compensation enable (COMP2)" ],
  [ "FE0_AMPLIFIER2_EN"             , WD2_FE0_AMPLIFIER2_EN_REG             , WD2_FE0_AMPLIFIER2_EN_MASK             , WD2_FE0_AMPLIFIER2_EN_OFS            , "Frontend channel 0 amplifier 2 enable (gain: 10) (OP2)" ],
  [ "FE0_AMPLIFIER1_COMP_EN"        , WD2_FE0_AMPLIFIER1_COMP_EN_REG        , WD2_FE0_AMPLIFIER1_COMP_EN_MASK        , WD2_FE0_AMPLIFIER1_COMP_EN_OFS       , "Frontend channel 0 amplifier 1 compensation enable (COMP1)" ],
  [ "FE0_AMPLIFIER1_EN"             , WD2_FE0_AMPLIFIER1_EN_REG             , WD2_FE0_AMPLIFIER1_EN_MASK             , WD2_FE0_AMPLIFIER1_EN_OFS            , "Frontend channel 0 amplifier 1 enable (gain: 10) (OP1)" ],
  [ "FE0_ATTENUATION"               , WD2_FE0_ATTENUATION_REG               , WD2_FE0_ATTENUATION_MASK               , WD2_FE0_ATTENUATION_OFS              , "Frontend channel 0 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)" ],
  [ "FE0_MUX"                       , WD2_FE0_MUX_REG                       , WD2_FE0_MUX_MASK                       , WD2_FE0_MUX_OFS                      , "Frontend channel 0 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)" ],
  [ "FE1_PZC_EN"                    , WD2_FE1_PZC_EN_REG                    , WD2_FE1_PZC_EN_MASK                    , WD2_FE1_PZC_EN_OFS                   , "Frontend channel 1 PZC (pole-zero cancellation) enable (ACDC)" ],
  [ "FE1_AMPLIFIER2_COMP_EN"        , WD2_FE1_AMPLIFIER2_COMP_EN_REG        , WD2_FE1_AMPLIFIER2_COMP_EN_MASK        , WD2_FE1_AMPLIFIER2_COMP_EN_OFS       , "Frontend channel 1 amplifier 2 compensation enable (COMP2)" ],
  [ "FE1_AMPLIFIER2_EN"             , WD2_FE1_AMPLIFIER2_EN_REG             , WD2_FE1_AMPLIFIER2_EN_MASK             , WD2_FE1_AMPLIFIER2_EN_OFS            , "Frontend channel 1 amplifier 2 enable (gain: 10) (OP2)" ],
  [ "FE1_AMPLIFIER1_COMP_EN"        , WD2_FE1_AMPLIFIER1_COMP_EN_REG        , WD2_FE1_AMPLIFIER1_COMP_EN_MASK        , WD2_FE1_AMPLIFIER1_COMP_EN_OFS       , "Frontend channel 1 amplifier 1 compensation enable (COMP1)" ],
  [ "FE1_AMPLIFIER1_EN"             , WD2_FE1_AMPLIFIER1_EN_REG             , WD2_FE1_AMPLIFIER1_EN_MASK             , WD2_FE1_AMPLIFIER1_EN_OFS            , "Frontend channel 1 amplifier 1 enable (gain: 10) (OP1)" ],
  [ "FE1_ATTENUATION"               , WD2_FE1_ATTENUATION_REG               , WD2_FE1_ATTENUATION_MASK               , WD2_FE1_ATTENUATION_OFS              , "Frontend channel 1 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)" ],
  [ "FE1_MUX"                       , WD2_FE1_MUX_REG                       , WD2_FE1_MUX_MASK                       , WD2_FE1_MUX_OFS                      , "Frontend channel 1 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)" ],
  [ "FE2_PZC_EN"                    , WD2_FE2_PZC_EN_REG                    , WD2_FE2_PZC_EN_MASK                    , WD2_FE2_PZC_EN_OFS                   , "Frontend channel 2 PZC (pole-zero cancellation) enable (ACDC)" ],
  [ "FE2_AMPLIFIER2_COMP_EN"        , WD2_FE2_AMPLIFIER2_COMP_EN_REG        , WD2_FE2_AMPLIFIER2_COMP_EN_MASK        , WD2_FE2_AMPLIFIER2_COMP_EN_OFS       , "Frontend channel 2 amplifier 2 compensation enable (COMP2)" ],
  [ "FE2_AMPLIFIER2_EN"             , WD2_FE2_AMPLIFIER2_EN_REG             , WD2_FE2_AMPLIFIER2_EN_MASK             , WD2_FE2_AMPLIFIER2_EN_OFS            , "Frontend channel 2 amplifier 2 enable (gain: 10) (OP2)" ],
  [ "FE2_AMPLIFIER1_COMP_EN"        , WD2_FE2_AMPLIFIER1_COMP_EN_REG        , WD2_FE2_AMPLIFIER1_COMP_EN_MASK        , WD2_FE2_AMPLIFIER1_COMP_EN_OFS       , "Frontend channel 2 amplifier 1 compensation enable (COMP1)" ],
  [ "FE2_AMPLIFIER1_EN"             , WD2_FE2_AMPLIFIER1_EN_REG             , WD2_FE2_AMPLIFIER1_EN_MASK             , WD2_FE2_AMPLIFIER1_EN_OFS            , "Frontend channel 2 amplifier 1 enable (gain: 10) (OP1)" ],
  [ "FE2_ATTENUATION"               , WD2_FE2_ATTENUATION_REG               , WD2_FE2_ATTENUATION_MASK               , WD2_FE2_ATTENUATION_OFS              , "Frontend channel 2 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)" ],
  [ "FE2_MUX"                       , WD2_FE2_MUX_REG                       , WD2_FE2_MUX_MASK                       , WD2_FE2_MUX_OFS                      , "Frontend channel 2 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)" ],
  [ "FE3_PZC_EN"                    , WD2_FE3_PZC_EN_REG                    , WD2_FE3_PZC_EN_MASK                    , WD2_FE3_PZC_EN_OFS                   , "Frontend channel 3 PZC (pole-zero cancellation) enable (ACDC)" ],
  [ "FE3_AMPLIFIER2_COMP_EN"        , WD2_FE3_AMPLIFIER2_COMP_EN_REG        , WD2_FE3_AMPLIFIER2_COMP_EN_MASK        , WD2_FE3_AMPLIFIER2_COMP_EN_OFS       , "Frontend channel 3 amplifier 2 compensation enable (COMP2)" ],
  [ "FE3_AMPLIFIER2_EN"             , WD2_FE3_AMPLIFIER2_EN_REG             , WD2_FE3_AMPLIFIER2_EN_MASK             , WD2_FE3_AMPLIFIER2_EN_OFS            , "Frontend channel 3 amplifier 2 enable (gain: 10) (OP2)" ],
  [ "FE3_AMPLIFIER1_COMP_EN"        , WD2_FE3_AMPLIFIER1_COMP_EN_REG        , WD2_FE3_AMPLIFIER1_COMP_EN_MASK        , WD2_FE3_AMPLIFIER1_COMP_EN_OFS       , "Frontend channel 3 amplifier 1 compensation enable (COMP1)" ],
  [ "FE3_AMPLIFIER1_EN"             , WD2_FE3_AMPLIFIER1_EN_REG             , WD2_FE3_AMPLIFIER1_EN_MASK             , WD2_FE3_AMPLIFIER1_EN_OFS            , "Frontend channel 3 amplifier 1 enable (gain: 10) (OP1)" ],
  [ "FE3_ATTENUATION"               , WD2_FE3_ATTENUATION_REG               , WD2_FE3_ATTENUATION_MASK               , WD2_FE3_ATTENUATION_OFS              , "Frontend channel 3 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)" ],
  [ "FE3_MUX"                       , WD2_FE3_MUX_REG                       , WD2_FE3_MUX_MASK                       , WD2_FE3_MUX_OFS                      , "Frontend channel 3 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)" ],
  [ "FE4_PZC_EN"                    , WD2_FE4_PZC_EN_REG                    , WD2_FE4_PZC_EN_MASK                    , WD2_FE4_PZC_EN_OFS                   , "Frontend channel 4 PZC (pole-zero cancellation) enable (ACDC)" ],
  [ "FE4_AMPLIFIER2_COMP_EN"        , WD2_FE4_AMPLIFIER2_COMP_EN_REG        , WD2_FE4_AMPLIFIER2_COMP_EN_MASK        , WD2_FE4_AMPLIFIER2_COMP_EN_OFS       , "Frontend channel 4 amplifier 2 compensation enable (COMP2)" ],
  [ "FE4_AMPLIFIER2_EN"             , WD2_FE4_AMPLIFIER2_EN_REG             , WD2_FE4_AMPLIFIER2_EN_MASK             , WD2_FE4_AMPLIFIER2_EN_OFS            , "Frontend channel 4 amplifier 2 enable (gain: 10) (OP2)" ],
  [ "FE4_AMPLIFIER1_COMP_EN"        , WD2_FE4_AMPLIFIER1_COMP_EN_REG        , WD2_FE4_AMPLIFIER1_COMP_EN_MASK        , WD2_FE4_AMPLIFIER1_COMP_EN_OFS       , "Frontend channel 4 amplifier 1 compensation enable (COMP1)" ],
  [ "FE4_AMPLIFIER1_EN"             , WD2_FE4_AMPLIFIER1_EN_REG             , WD2_FE4_AMPLIFIER1_EN_MASK             , WD2_FE4_AMPLIFIER1_EN_OFS            , "Frontend channel 4 amplifier 1 enable (gain: 10) (OP1)" ],
  [ "FE4_ATTENUATION"               , WD2_FE4_ATTENUATION_REG               , WD2_FE4_ATTENUATION_MASK               , WD2_FE4_ATTENUATION_OFS              , "Frontend channel 4 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)" ],
  [ "FE4_MUX"                       , WD2_FE4_MUX_REG                       , WD2_FE4_MUX_MASK                       , WD2_FE4_MUX_OFS                      , "Frontend channel 4 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)" ],
  [ "FE5_PZC_EN"                    , WD2_FE5_PZC_EN_REG                    , WD2_FE5_PZC_EN_MASK                    , WD2_FE5_PZC_EN_OFS                   , "Frontend channel 5 PZC (pole-zero cancellation) enable (ACDC)" ],
  [ "FE5_AMPLIFIER2_COMP_EN"        , WD2_FE5_AMPLIFIER2_COMP_EN_REG        , WD2_FE5_AMPLIFIER2_COMP_EN_MASK        , WD2_FE5_AMPLIFIER2_COMP_EN_OFS       , "Frontend channel 5 amplifier 2 compensation enable (COMP2)" ],
  [ "FE5_AMPLIFIER2_EN"             , WD2_FE5_AMPLIFIER2_EN_REG             , WD2_FE5_AMPLIFIER2_EN_MASK             , WD2_FE5_AMPLIFIER2_EN_OFS            , "Frontend channel 5 amplifier 2 enable (gain: 10) (OP2)" ],
  [ "FE5_AMPLIFIER1_COMP_EN"        , WD2_FE5_AMPLIFIER1_COMP_EN_REG        , WD2_FE5_AMPLIFIER1_COMP_EN_MASK        , WD2_FE5_AMPLIFIER1_COMP_EN_OFS       , "Frontend channel 5 amplifier 1 compensation enable (COMP1)" ],
  [ "FE5_AMPLIFIER1_EN"             , WD2_FE5_AMPLIFIER1_EN_REG             , WD2_FE5_AMPLIFIER1_EN_MASK             , WD2_FE5_AMPLIFIER1_EN_OFS            , "Frontend channel 5 amplifier 1 enable (gain: 10) (OP1)" ],
  [ "FE5_ATTENUATION"               , WD2_FE5_ATTENUATION_REG               , WD2_FE5_ATTENUATION_MASK               , WD2_FE5_ATTENUATION_OFS              , "Frontend channel 5 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)" ],
  [ "FE5_MUX"                       , WD2_FE5_MUX_REG                       , WD2_FE5_MUX_MASK                       , WD2_FE5_MUX_OFS                      , "Frontend channel 5 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)" ],
  [ "FE6_PZC_EN"                    , WD2_FE6_PZC_EN_REG                    , WD2_FE6_PZC_EN_MASK                    , WD2_FE6_PZC_EN_OFS                   , "Frontend channel 6 PZC (pole-zero cancellation) enable (ACDC)" ],
  [ "FE6_AMPLIFIER2_COMP_EN"        , WD2_FE6_AMPLIFIER2_COMP_EN_REG        , WD2_FE6_AMPLIFIER2_COMP_EN_MASK        , WD2_FE6_AMPLIFIER2_COMP_EN_OFS       , "Frontend channel 6 amplifier 2 compensation enable (COMP2)" ],
  [ "FE6_AMPLIFIER2_EN"             , WD2_FE6_AMPLIFIER2_EN_REG             , WD2_FE6_AMPLIFIER2_EN_MASK             , WD2_FE6_AMPLIFIER2_EN_OFS            , "Frontend channel 6 amplifier 2 enable (gain: 10) (OP2)" ],
  [ "FE6_AMPLIFIER1_COMP_EN"        , WD2_FE6_AMPLIFIER1_COMP_EN_REG        , WD2_FE6_AMPLIFIER1_COMP_EN_MASK        , WD2_FE6_AMPLIFIER1_COMP_EN_OFS       , "Frontend channel 6 amplifier 1 compensation enable (COMP1)" ],
  [ "FE6_AMPLIFIER1_EN"             , WD2_FE6_AMPLIFIER1_EN_REG             , WD2_FE6_AMPLIFIER1_EN_MASK             , WD2_FE6_AMPLIFIER1_EN_OFS            , "Frontend channel 6 amplifier 1 enable (gain: 10) (OP1)" ],
  [ "FE6_ATTENUATION"               , WD2_FE6_ATTENUATION_REG               , WD2_FE6_ATTENUATION_MASK               , WD2_FE6_ATTENUATION_OFS              , "Frontend channel 6 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)" ],
  [ "FE6_MUX"                       , WD2_FE6_MUX_REG                       , WD2_FE6_MUX_MASK                       , WD2_FE6_MUX_OFS                      , "Frontend channel 6 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)" ],
  [ "FE7_PZC_EN"                    , WD2_FE7_PZC_EN_REG                    , WD2_FE7_PZC_EN_MASK                    , WD2_FE7_PZC_EN_OFS                   , "Frontend channel 7 PZC (pole-zero cancellation) enable (ACDC)" ],
  [ "FE7_AMPLIFIER2_COMP_EN"        , WD2_FE7_AMPLIFIER2_COMP_EN_REG        , WD2_FE7_AMPLIFIER2_COMP_EN_MASK        , WD2_FE7_AMPLIFIER2_COMP_EN_OFS       , "Frontend channel 7 amplifier 2 compensation enable (COMP2)" ],
  [ "FE7_AMPLIFIER2_EN"             , WD2_FE7_AMPLIFIER2_EN_REG             , WD2_FE7_AMPLIFIER2_EN_MASK             , WD2_FE7_AMPLIFIER2_EN_OFS            , "Frontend channel 7 amplifier 2 enable (gain: 10) (OP2)" ],
  [ "FE7_AMPLIFIER1_COMP_EN"        , WD2_FE7_AMPLIFIER1_COMP_EN_REG        , WD2_FE7_AMPLIFIER1_COMP_EN_MASK        , WD2_FE7_AMPLIFIER1_COMP_EN_OFS       , "Frontend channel 7 amplifier 1 compensation enable (COMP1)" ],
  [ "FE7_AMPLIFIER1_EN"             , WD2_FE7_AMPLIFIER1_EN_REG             , WD2_FE7_AMPLIFIER1_EN_MASK             , WD2_FE7_AMPLIFIER1_EN_OFS            , "Frontend channel 7 amplifier 1 enable (gain: 10) (OP1)" ],
  [ "FE7_ATTENUATION"               , WD2_FE7_ATTENUATION_REG               , WD2_FE7_ATTENUATION_MASK               , WD2_FE7_ATTENUATION_OFS              , "Frontend channel 7 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)" ],
  [ "FE7_MUX"                       , WD2_FE7_MUX_REG                       , WD2_FE7_MUX_MASK                       , WD2_FE7_MUX_OFS                      , "Frontend channel 7 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)" ],
  [ "FE8_PZC_EN"                    , WD2_FE8_PZC_EN_REG                    , WD2_FE8_PZC_EN_MASK                    , WD2_FE8_PZC_EN_OFS                   , "Frontend channel 8 PZC (pole-zero cancellation) enable (ACDC)" ],
  [ "FE8_AMPLIFIER2_COMP_EN"        , WD2_FE8_AMPLIFIER2_COMP_EN_REG        , WD2_FE8_AMPLIFIER2_COMP_EN_MASK        , WD2_FE8_AMPLIFIER2_COMP_EN_OFS       , "Frontend channel 8 amplifier 2 compensation enable (COMP2)" ],
  [ "FE8_AMPLIFIER2_EN"             , WD2_FE8_AMPLIFIER2_EN_REG             , WD2_FE8_AMPLIFIER2_EN_MASK             , WD2_FE8_AMPLIFIER2_EN_OFS            , "Frontend channel 8 amplifier 2 enable (gain: 10) (OP2)" ],
  [ "FE8_AMPLIFIER1_COMP_EN"        , WD2_FE8_AMPLIFIER1_COMP_EN_REG        , WD2_FE8_AMPLIFIER1_COMP_EN_MASK        , WD2_FE8_AMPLIFIER1_COMP_EN_OFS       , "Frontend channel 8 amplifier 1 compensation enable (COMP1)" ],
  [ "FE8_AMPLIFIER1_EN"             , WD2_FE8_AMPLIFIER1_EN_REG             , WD2_FE8_AMPLIFIER1_EN_MASK             , WD2_FE8_AMPLIFIER1_EN_OFS            , "Frontend channel 8 amplifier 1 enable (gain: 10) (OP1)" ],
  [ "FE8_ATTENUATION"               , WD2_FE8_ATTENUATION_REG               , WD2_FE8_ATTENUATION_MASK               , WD2_FE8_ATTENUATION_OFS              , "Frontend channel 8 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)" ],
  [ "FE8_MUX"                       , WD2_FE8_MUX_REG                       , WD2_FE8_MUX_MASK                       , WD2_FE8_MUX_OFS                      , "Frontend channel 8 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)" ],
  [ "FE9_PZC_EN"                    , WD2_FE9_PZC_EN_REG                    , WD2_FE9_PZC_EN_MASK                    , WD2_FE9_PZC_EN_OFS                   , "Frontend channel 9 PZC (pole-zero cancellation) enable (ACDC)" ],
  [ "FE9_AMPLIFIER2_COMP_EN"        , WD2_FE9_AMPLIFIER2_COMP_EN_REG        , WD2_FE9_AMPLIFIER2_COMP_EN_MASK        , WD2_FE9_AMPLIFIER2_COMP_EN_OFS       , "Frontend channel 9 amplifier 2 compensation enable (COMP2)" ],
  [ "FE9_AMPLIFIER2_EN"             , WD2_FE9_AMPLIFIER2_EN_REG             , WD2_FE9_AMPLIFIER2_EN_MASK             , WD2_FE9_AMPLIFIER2_EN_OFS            , "Frontend channel 9 amplifier 2 enable (gain: 10) (OP2)" ],
  [ "FE9_AMPLIFIER1_COMP_EN"        , WD2_FE9_AMPLIFIER1_COMP_EN_REG        , WD2_FE9_AMPLIFIER1_COMP_EN_MASK        , WD2_FE9_AMPLIFIER1_COMP_EN_OFS       , "Frontend channel 9 amplifier 1 compensation enable (COMP1)" ],
  [ "FE9_AMPLIFIER1_EN"             , WD2_FE9_AMPLIFIER1_EN_REG             , WD2_FE9_AMPLIFIER1_EN_MASK             , WD2_FE9_AMPLIFIER1_EN_OFS            , "Frontend channel 9 amplifier 1 enable (gain: 10) (OP1)" ],
  [ "FE9_ATTENUATION"               , WD2_FE9_ATTENUATION_REG               , WD2_FE9_ATTENUATION_MASK               , WD2_FE9_ATTENUATION_OFS              , "Frontend channel 9 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)" ],
  [ "FE9_MUX"                       , WD2_FE9_MUX_REG                       , WD2_FE9_MUX_MASK                       , WD2_FE9_MUX_OFS                      , "Frontend channel 9 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)" ],
  [ "FE10_PZC_EN"                   , WD2_FE10_PZC_EN_REG                   , WD2_FE10_PZC_EN_MASK                   , WD2_FE10_PZC_EN_OFS                  , "Frontend channel 10 PZC (pole-zero cancellation) enable (ACDC)" ],
  [ "FE10_AMPLIFIER2_COMP_EN"       , WD2_FE10_AMPLIFIER2_COMP_EN_REG       , WD2_FE10_AMPLIFIER2_COMP_EN_MASK       , WD2_FE10_AMPLIFIER2_COMP_EN_OFS      , "Frontend channel 10 amplifier 2 compensation enable (COMP2)" ],
  [ "FE10_AMPLIFIER2_EN"            , WD2_FE10_AMPLIFIER2_EN_REG            , WD2_FE10_AMPLIFIER2_EN_MASK            , WD2_FE10_AMPLIFIER2_EN_OFS           , "Frontend channel 10 amplifier 2 enable (gain: 10) (OP2)" ],
  [ "FE10_AMPLIFIER1_COMP_EN"       , WD2_FE10_AMPLIFIER1_COMP_EN_REG       , WD2_FE10_AMPLIFIER1_COMP_EN_MASK       , WD2_FE10_AMPLIFIER1_COMP_EN_OFS      , "Frontend channel 10 amplifier 1 compensation enable (COMP1)" ],
  [ "FE10_AMPLIFIER1_EN"            , WD2_FE10_AMPLIFIER1_EN_REG            , WD2_FE10_AMPLIFIER1_EN_MASK            , WD2_FE10_AMPLIFIER1_EN_OFS           , "Frontend channel 10 amplifier 1 enable (gain: 10) (OP1)" ],
  [ "FE10_ATTENUATION"              , WD2_FE10_ATTENUATION_REG              , WD2_FE10_ATTENUATION_MASK              , WD2_FE10_ATTENUATION_OFS             , "Frontend channel 10 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)" ],
  [ "FE10_MUX"                      , WD2_FE10_MUX_REG                      , WD2_FE10_MUX_MASK                      , WD2_FE10_MUX_OFS                     , "Frontend channel 10 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)" ],
  [ "FE11_PZC_EN"                   , WD2_FE11_PZC_EN_REG                   , WD2_FE11_PZC_EN_MASK                   , WD2_FE11_PZC_EN_OFS                  , "Frontend channel 11 PZC (pole-zero cancellation) enable (ACDC)" ],
  [ "FE11_AMPLIFIER2_COMP_EN"       , WD2_FE11_AMPLIFIER2_COMP_EN_REG       , WD2_FE11_AMPLIFIER2_COMP_EN_MASK       , WD2_FE11_AMPLIFIER2_COMP_EN_OFS      , "Frontend channel 11 amplifier 2 compensation enable (COMP2)" ],
  [ "FE11_AMPLIFIER2_EN"            , WD2_FE11_AMPLIFIER2_EN_REG            , WD2_FE11_AMPLIFIER2_EN_MASK            , WD2_FE11_AMPLIFIER2_EN_OFS           , "Frontend channel 11 amplifier 2 enable (gain: 10) (OP2)" ],
  [ "FE11_AMPLIFIER1_COMP_EN"       , WD2_FE11_AMPLIFIER1_COMP_EN_REG       , WD2_FE11_AMPLIFIER1_COMP_EN_MASK       , WD2_FE11_AMPLIFIER1_COMP_EN_OFS      , "Frontend channel 11 amplifier 1 compensation enable (COMP1)" ],
  [ "FE11_AMPLIFIER1_EN"            , WD2_FE11_AMPLIFIER1_EN_REG            , WD2_FE11_AMPLIFIER1_EN_MASK            , WD2_FE11_AMPLIFIER1_EN_OFS           , "Frontend channel 11 amplifier 1 enable (gain: 10) (OP1)" ],
  [ "FE11_ATTENUATION"              , WD2_FE11_ATTENUATION_REG              , WD2_FE11_ATTENUATION_MASK              , WD2_FE11_ATTENUATION_OFS             , "Frontend channel 11 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)" ],
  [ "FE11_MUX"                      , WD2_FE11_MUX_REG                      , WD2_FE11_MUX_MASK                      , WD2_FE11_MUX_OFS                     , "Frontend channel 11 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)" ],
  [ "FE12_PZC_EN"                   , WD2_FE12_PZC_EN_REG                   , WD2_FE12_PZC_EN_MASK                   , WD2_FE12_PZC_EN_OFS                  , "Frontend channel 12 PZC (pole-zero cancellation) enable (ACDC)" ],
  [ "FE12_AMPLIFIER2_COMP_EN"       , WD2_FE12_AMPLIFIER2_COMP_EN_REG       , WD2_FE12_AMPLIFIER2_COMP_EN_MASK       , WD2_FE12_AMPLIFIER2_COMP_EN_OFS      , "Frontend channel 12 amplifier 2 compensation enable (COMP2)" ],
  [ "FE12_AMPLIFIER2_EN"            , WD2_FE12_AMPLIFIER2_EN_REG            , WD2_FE12_AMPLIFIER2_EN_MASK            , WD2_FE12_AMPLIFIER2_EN_OFS           , "Frontend channel 12 amplifier 2 enable (gain: 10) (OP2)" ],
  [ "FE12_AMPLIFIER1_COMP_EN"       , WD2_FE12_AMPLIFIER1_COMP_EN_REG       , WD2_FE12_AMPLIFIER1_COMP_EN_MASK       , WD2_FE12_AMPLIFIER1_COMP_EN_OFS      , "Frontend channel 12 amplifier 1 compensation enable (COMP1)" ],
  [ "FE12_AMPLIFIER1_EN"            , WD2_FE12_AMPLIFIER1_EN_REG            , WD2_FE12_AMPLIFIER1_EN_MASK            , WD2_FE12_AMPLIFIER1_EN_OFS           , "Frontend channel 12 amplifier 1 enable (gain: 10) (OP1)" ],
  [ "FE12_ATTENUATION"              , WD2_FE12_ATTENUATION_REG              , WD2_FE12_ATTENUATION_MASK              , WD2_FE12_ATTENUATION_OFS             , "Frontend channel 12 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)" ],
  [ "FE12_MUX"                      , WD2_FE12_MUX_REG                      , WD2_FE12_MUX_MASK                      , WD2_FE12_MUX_OFS                     , "Frontend channel 12 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)" ],
  [ "FE13_PZC_EN"                   , WD2_FE13_PZC_EN_REG                   , WD2_FE13_PZC_EN_MASK                   , WD2_FE13_PZC_EN_OFS                  , "Frontend channel 13 PZC (pole-zero cancellation) enable (ACDC)" ],
  [ "FE13_AMPLIFIER2_COMP_EN"       , WD2_FE13_AMPLIFIER2_COMP_EN_REG       , WD2_FE13_AMPLIFIER2_COMP_EN_MASK       , WD2_FE13_AMPLIFIER2_COMP_EN_OFS      , "Frontend channel 13 amplifier 2 compensation enable (COMP2)" ],
  [ "FE13_AMPLIFIER2_EN"            , WD2_FE13_AMPLIFIER2_EN_REG            , WD2_FE13_AMPLIFIER2_EN_MASK            , WD2_FE13_AMPLIFIER2_EN_OFS           , "Frontend channel 13 amplifier 2 enable (gain: 10) (OP2)" ],
  [ "FE13_AMPLIFIER1_COMP_EN"       , WD2_FE13_AMPLIFIER1_COMP_EN_REG       , WD2_FE13_AMPLIFIER1_COMP_EN_MASK       , WD2_FE13_AMPLIFIER1_COMP_EN_OFS      , "Frontend channel 13 amplifier 1 compensation enable (COMP1)" ],
  [ "FE13_AMPLIFIER1_EN"            , WD2_FE13_AMPLIFIER1_EN_REG            , WD2_FE13_AMPLIFIER1_EN_MASK            , WD2_FE13_AMPLIFIER1_EN_OFS           , "Frontend channel 13 amplifier 1 enable (gain: 10) (OP1)" ],
  [ "FE13_ATTENUATION"              , WD2_FE13_ATTENUATION_REG              , WD2_FE13_ATTENUATION_MASK              , WD2_FE13_ATTENUATION_OFS             , "Frontend channel 13 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)" ],
  [ "FE13_MUX"                      , WD2_FE13_MUX_REG                      , WD2_FE13_MUX_MASK                      , WD2_FE13_MUX_OFS                     , "Frontend channel 13 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)" ],
  [ "FE14_PZC_EN"                   , WD2_FE14_PZC_EN_REG                   , WD2_FE14_PZC_EN_MASK                   , WD2_FE14_PZC_EN_OFS                  , "Frontend channel 14 PZC (pole-zero cancellation) enable (ACDC)" ],
  [ "FE14_AMPLIFIER2_COMP_EN"       , WD2_FE14_AMPLIFIER2_COMP_EN_REG       , WD2_FE14_AMPLIFIER2_COMP_EN_MASK       , WD2_FE14_AMPLIFIER2_COMP_EN_OFS      , "Frontend channel 14 amplifier 2 compensation enable (COMP2)" ],
  [ "FE14_AMPLIFIER2_EN"            , WD2_FE14_AMPLIFIER2_EN_REG            , WD2_FE14_AMPLIFIER2_EN_MASK            , WD2_FE14_AMPLIFIER2_EN_OFS           , "Frontend channel 14 amplifier 2 enable (gain: 10) (OP2)" ],
  [ "FE14_AMPLIFIER1_COMP_EN"       , WD2_FE14_AMPLIFIER1_COMP_EN_REG       , WD2_FE14_AMPLIFIER1_COMP_EN_MASK       , WD2_FE14_AMPLIFIER1_COMP_EN_OFS      , "Frontend channel 14 amplifier 1 compensation enable (COMP1)" ],
  [ "FE14_AMPLIFIER1_EN"            , WD2_FE14_AMPLIFIER1_EN_REG            , WD2_FE14_AMPLIFIER1_EN_MASK            , WD2_FE14_AMPLIFIER1_EN_OFS           , "Frontend channel 14 amplifier 1 enable (gain: 10) (OP1)" ],
  [ "FE14_ATTENUATION"              , WD2_FE14_ATTENUATION_REG              , WD2_FE14_ATTENUATION_MASK              , WD2_FE14_ATTENUATION_OFS             , "Frontend channel 14 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)" ],
  [ "FE14_MUX"                      , WD2_FE14_MUX_REG                      , WD2_FE14_MUX_MASK                      , WD2_FE14_MUX_OFS                     , "Frontend channel 14 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)" ],
  [ "FE15_PZC_EN"                   , WD2_FE15_PZC_EN_REG                   , WD2_FE15_PZC_EN_MASK                   , WD2_FE15_PZC_EN_OFS                  , "Frontend channel 15 PZC (pole-zero cancellation) enable (ACDC)" ],
  [ "FE15_AMPLIFIER2_COMP_EN"       , WD2_FE15_AMPLIFIER2_COMP_EN_REG       , WD2_FE15_AMPLIFIER2_COMP_EN_MASK       , WD2_FE15_AMPLIFIER2_COMP_EN_OFS      , "Frontend channel 15 amplifier 2 compensation enable (COMP2)" ],
  [ "FE15_AMPLIFIER2_EN"            , WD2_FE15_AMPLIFIER2_EN_REG            , WD2_FE15_AMPLIFIER2_EN_MASK            , WD2_FE15_AMPLIFIER2_EN_OFS           , "Frontend channel 15 amplifier 2 enable (gain: 10) (OP2)" ],
  [ "FE15_AMPLIFIER1_COMP_EN"       , WD2_FE15_AMPLIFIER1_COMP_EN_REG       , WD2_FE15_AMPLIFIER1_COMP_EN_MASK       , WD2_FE15_AMPLIFIER1_COMP_EN_OFS      , "Frontend channel 15 amplifier 1 compensation enable (COMP1)" ],
  [ "FE15_AMPLIFIER1_EN"            , WD2_FE15_AMPLIFIER1_EN_REG            , WD2_FE15_AMPLIFIER1_EN_MASK            , WD2_FE15_AMPLIFIER1_EN_OFS           , "Frontend channel 15 amplifier 1 enable (gain: 10) (OP1)" ],
  [ "FE15_ATTENUATION"              , WD2_FE15_ATTENUATION_REG              , WD2_FE15_ATTENUATION_MASK              , WD2_FE15_ATTENUATION_OFS             , "Frontend channel 15 attenuation (0: 0dB, 1: 6dB, 2: 12dB, 3: 18dB) (ATT_1,ATT_0)" ],
  [ "FE15_MUX"                      , WD2_FE15_MUX_REG                      , WD2_FE15_MUX_MASK                      , WD2_FE15_MUX_OFS                     , "Frontend channel 15 input MUX (0: next ch, 1: prev ch, 2: input, 3: cal src) (CAL_1,CAL_0)" ],
  [ "HV_U_TARGET_0"                 , WD2_HV_U_TARGET_0_REG                 , WD2_HV_U_TARGET_0_MASK                 , WD2_HV_U_TARGET_0_OFS                , "Float value (u_demand)" ],
  [ "HV_U_TARGET_1"                 , WD2_HV_U_TARGET_1_REG                 , WD2_HV_U_TARGET_1_MASK                 , WD2_HV_U_TARGET_1_OFS                , "Float value (u_demand)" ],
  [ "HV_U_TARGET_2"                 , WD2_HV_U_TARGET_2_REG                 , WD2_HV_U_TARGET_2_MASK                 , WD2_HV_U_TARGET_2_OFS                , "Float value (u_demand)" ],
  [ "HV_U_TARGET_3"                 , WD2_HV_U_TARGET_3_REG                 , WD2_HV_U_TARGET_3_MASK                 , WD2_HV_U_TARGET_3_OFS                , "Float value (u_demand)" ],
  [ "HV_U_TARGET_4"                 , WD2_HV_U_TARGET_4_REG                 , WD2_HV_U_TARGET_4_MASK                 , WD2_HV_U_TARGET_4_OFS                , "Float value (u_demand)" ],
  [ "HV_U_TARGET_5"                 , WD2_HV_U_TARGET_5_REG                 , WD2_HV_U_TARGET_5_MASK                 , WD2_HV_U_TARGET_5_OFS                , "Float value (u_demand)" ],
  [ "HV_U_TARGET_6"                 , WD2_HV_U_TARGET_6_REG                 , WD2_HV_U_TARGET_6_MASK                 , WD2_HV_U_TARGET_6_OFS                , "Float value (u_demand)" ],
  [ "HV_U_TARGET_7"                 , WD2_HV_U_TARGET_7_REG                 , WD2_HV_U_TARGET_7_MASK                 , WD2_HV_U_TARGET_7_OFS                , "Float value (u_demand)" ],
  [ "HV_U_TARGET_8"                 , WD2_HV_U_TARGET_8_REG                 , WD2_HV_U_TARGET_8_MASK                 , WD2_HV_U_TARGET_8_OFS                , "Float value (u_demand)" ],
  [ "HV_U_TARGET_9"                 , WD2_HV_U_TARGET_9_REG                 , WD2_HV_U_TARGET_9_MASK                 , WD2_HV_U_TARGET_9_OFS                , "Float value (u_demand)" ],
  [ "HV_U_TARGET_10"                , WD2_HV_U_TARGET_10_REG                , WD2_HV_U_TARGET_10_MASK                , WD2_HV_U_TARGET_10_OFS               , "Float value (u_demand)" ],
  [ "HV_U_TARGET_11"                , WD2_HV_U_TARGET_11_REG                , WD2_HV_U_TARGET_11_MASK                , WD2_HV_U_TARGET_11_OFS               , "Float value (u_demand)" ],
  [ "HV_U_TARGET_12"                , WD2_HV_U_TARGET_12_REG                , WD2_HV_U_TARGET_12_MASK                , WD2_HV_U_TARGET_12_OFS               , "Float value (u_demand)" ],
  [ "HV_U_TARGET_13"                , WD2_HV_U_TARGET_13_REG                , WD2_HV_U_TARGET_13_MASK                , WD2_HV_U_TARGET_13_OFS               , "Float value (u_demand)" ],
  [ "HV_U_TARGET_14"                , WD2_HV_U_TARGET_14_REG                , WD2_HV_U_TARGET_14_MASK                , WD2_HV_U_TARGET_14_OFS               , "Float value (u_demand)" ],
  [ "HV_U_TARGET_15"                , WD2_HV_U_TARGET_15_REG                , WD2_HV_U_TARGET_15_MASK                , WD2_HV_U_TARGET_15_OFS               , "Float value (u_demand)" ],
  [ "HV_R_SHUNT"                    , WD2_HV_R_SHUNT_REG                    , WD2_HV_R_SHUNT_MASK                    , WD2_HV_R_SHUNT_OFS                   , "Resistor value in Ohm (r_current)" ],
  [ "LMK0_RESET"                    , WD2_LMK0_RESET_REG                    , WD2_LMK0_RESET_MASK                    , WD2_LMK0_RESET_OFS                   , "Resets LMK Registers to Their Power-On State" ],
  [ "LMK0_CLKOUT_MUX"               , WD2_LMK0_CLKOUT_MUX_REG               , WD2_LMK0_CLKOUT_MUX_MASK               , WD2_LMK0_CLKOUT_MUX_OFS              , "Channel 0 Clock Output Multiplexer (see datasheet)" ],
  [ "LMK0_CLKOUT_EN"                , WD2_LMK0_CLKOUT_EN_REG                , WD2_LMK0_CLKOUT_EN_MASK                , WD2_LMK0_CLKOUT_EN_OFS               , "Channel 0 Clock Output Enable (0 = Disabled, 1 = Enabled)" ],
  [ "LMK0_CLKOUT_DIV"               , WD2_LMK0_CLKOUT_DIV_REG               , WD2_LMK0_CLKOUT_DIV_MASK               , WD2_LMK0_CLKOUT_DIV_OFS              , "Channel 0 Clock Output Divider (value x 2) (1..255)" ],
  [ "LMK0_CLKOUT_DLY"               , WD2_LMK0_CLKOUT_DLY_REG               , WD2_LMK0_CLKOUT_DLY_MASK               , WD2_LMK0_CLKOUT_DLY_OFS              , "Channel 0 Clock Output Delay (value x 150ps)" ],
  [ "LMK1_CLKOUT_MUX"               , WD2_LMK1_CLKOUT_MUX_REG               , WD2_LMK1_CLKOUT_MUX_MASK               , WD2_LMK1_CLKOUT_MUX_OFS              , "Channel 1 Clock Output Multiplexer (see datasheet)" ],
  [ "LMK1_CLKOUT_EN"                , WD2_LMK1_CLKOUT_EN_REG                , WD2_LMK1_CLKOUT_EN_MASK                , WD2_LMK1_CLKOUT_EN_OFS               , "Channel 1 Clock Output Enable (0 = Disabled, 1 = Enabled)" ],
  [ "LMK1_CLKOUT_DIV"               , WD2_LMK1_CLKOUT_DIV_REG               , WD2_LMK1_CLKOUT_DIV_MASK               , WD2_LMK1_CLKOUT_DIV_OFS              , "Channel 1 Clock Output Divider (value x 2) (1..255)" ],
  [ "LMK1_CLKOUT_DLY"               , WD2_LMK1_CLKOUT_DLY_REG               , WD2_LMK1_CLKOUT_DLY_MASK               , WD2_LMK1_CLKOUT_DLY_OFS              , "Channel 1 Clock Output Delay (value x 150ps)" ],
  [ "LMK2_CLKOUT_MUX"               , WD2_LMK2_CLKOUT_MUX_REG               , WD2_LMK2_CLKOUT_MUX_MASK               , WD2_LMK2_CLKOUT_MUX_OFS              , "Channel 2 Clock Output Multiplexer (see datasheet)" ],
  [ "LMK2_CLKOUT_EN"                , WD2_LMK2_CLKOUT_EN_REG                , WD2_LMK2_CLKOUT_EN_MASK                , WD2_LMK2_CLKOUT_EN_OFS               , "Channel 2 Clock Output Enable (0 = Disabled, 1 = Enabled)" ],
  [ "LMK2_CLKOUT_DIV"               , WD2_LMK2_CLKOUT_DIV_REG               , WD2_LMK2_CLKOUT_DIV_MASK               , WD2_LMK2_CLKOUT_DIV_OFS              , "Channel 2 Clock Output Divider (value x 2) (1..255)" ],
  [ "LMK2_CLKOUT_DLY"               , WD2_LMK2_CLKOUT_DLY_REG               , WD2_LMK2_CLKOUT_DLY_MASK               , WD2_LMK2_CLKOUT_DLY_OFS              , "Channel 2 Clock Output Delay (value x 150ps)" ],
  [ "LMK3_CLKOUT_MUX"               , WD2_LMK3_CLKOUT_MUX_REG               , WD2_LMK3_CLKOUT_MUX_MASK               , WD2_LMK3_CLKOUT_MUX_OFS              , "Channel 3 Clock Output Multiplexer (see datasheet)" ],
  [ "LMK3_CLKOUT_EN"                , WD2_LMK3_CLKOUT_EN_REG                , WD2_LMK3_CLKOUT_EN_MASK                , WD2_LMK3_CLKOUT_EN_OFS               , "Channel 3 Clock Output Enable (0 = Disabled, 1 = Enabled)" ],
  [ "LMK3_CLKOUT_DIV"               , WD2_LMK3_CLKOUT_DIV_REG               , WD2_LMK3_CLKOUT_DIV_MASK               , WD2_LMK3_CLKOUT_DIV_OFS              , "Channel 3 Clock Output Divider (value x 2) (1..255)" ],
  [ "LMK3_CLKOUT_DLY"               , WD2_LMK3_CLKOUT_DLY_REG               , WD2_LMK3_CLKOUT_DLY_MASK               , WD2_LMK3_CLKOUT_DLY_OFS              , "Channel 3 Clock Output Delay (value x 150ps)" ],
  [ "LMK4_CLKOUT_MUX"               , WD2_LMK4_CLKOUT_MUX_REG               , WD2_LMK4_CLKOUT_MUX_MASK               , WD2_LMK4_CLKOUT_MUX_OFS              , "Channel 4 Clock Output Multiplexer (see datasheet)" ],
  [ "LMK4_CLKOUT_EN"                , WD2_LMK4_CLKOUT_EN_REG                , WD2_LMK4_CLKOUT_EN_MASK                , WD2_LMK4_CLKOUT_EN_OFS               , "Channel 4 Clock Output Enable (0 = Disabled, 1 = Enabled)" ],
  [ "LMK4_CLKOUT_DIV"               , WD2_LMK4_CLKOUT_DIV_REG               , WD2_LMK4_CLKOUT_DIV_MASK               , WD2_LMK4_CLKOUT_DIV_OFS              , "Channel 4 Clock Output Divider (value x 2) (1..255)" ],
  [ "LMK4_CLKOUT_DLY"               , WD2_LMK4_CLKOUT_DLY_REG               , WD2_LMK4_CLKOUT_DLY_MASK               , WD2_LMK4_CLKOUT_DLY_OFS              , "Channel 4 Clock Output Delay (value x 150ps)" ],
  [ "LMK5_CLKOUT_MUX"               , WD2_LMK5_CLKOUT_MUX_REG               , WD2_LMK5_CLKOUT_MUX_MASK               , WD2_LMK5_CLKOUT_MUX_OFS              , "Channel 5 Clock Output Multiplexer (see datasheet)" ],
  [ "LMK5_CLKOUT_EN"                , WD2_LMK5_CLKOUT_EN_REG                , WD2_LMK5_CLKOUT_EN_MASK                , WD2_LMK5_CLKOUT_EN_OFS               , "Channel 5 Clock Output Enable (0 = Disabled, 1 = Enabled)" ],
  [ "LMK5_CLKOUT_DIV"               , WD2_LMK5_CLKOUT_DIV_REG               , WD2_LMK5_CLKOUT_DIV_MASK               , WD2_LMK5_CLKOUT_DIV_OFS              , "Channel 5 Clock Output Divider (value x 2) (1..255)" ],
  [ "LMK5_CLKOUT_DLY"               , WD2_LMK5_CLKOUT_DLY_REG               , WD2_LMK5_CLKOUT_DLY_MASK               , WD2_LMK5_CLKOUT_DLY_OFS              , "Channel 5 Clock Output Delay (value x 150ps)" ],
  [ "LMK6_CLKOUT_MUX"               , WD2_LMK6_CLKOUT_MUX_REG               , WD2_LMK6_CLKOUT_MUX_MASK               , WD2_LMK6_CLKOUT_MUX_OFS              , "Channel 6 Clock Output Multiplexer (see datasheet)" ],
  [ "LMK6_CLKOUT_EN"                , WD2_LMK6_CLKOUT_EN_REG                , WD2_LMK6_CLKOUT_EN_MASK                , WD2_LMK6_CLKOUT_EN_OFS               , "Channel 6 Clock Output Enable (0 = Disabled, 1 = Enabled)" ],
  [ "LMK6_CLKOUT_DIV"               , WD2_LMK6_CLKOUT_DIV_REG               , WD2_LMK6_CLKOUT_DIV_MASK               , WD2_LMK6_CLKOUT_DIV_OFS              , "Channel 6 Clock Output Divider (value x 2) (1..255)" ],
  [ "LMK6_CLKOUT_DLY"               , WD2_LMK6_CLKOUT_DLY_REG               , WD2_LMK6_CLKOUT_DLY_MASK               , WD2_LMK6_CLKOUT_DLY_OFS              , "Channel 6 Clock Output Delay (value x 150ps)" ],
  [ "LMK7_CLKOUT_MUX"               , WD2_LMK7_CLKOUT_MUX_REG               , WD2_LMK7_CLKOUT_MUX_MASK               , WD2_LMK7_CLKOUT_MUX_OFS              , "Channel 7 Clock Output Multiplexer (see datasheet)" ],
  [ "LMK7_CLKOUT_EN"                , WD2_LMK7_CLKOUT_EN_REG                , WD2_LMK7_CLKOUT_EN_MASK                , WD2_LMK7_CLKOUT_EN_OFS               , "Channel 7 Clock Output Enable (0 = Disabled, 1 = Enabled)" ],
  [ "LMK7_CLKOUT_DIV"               , WD2_LMK7_CLKOUT_DIV_REG               , WD2_LMK7_CLKOUT_DIV_MASK               , WD2_LMK7_CLKOUT_DIV_OFS              , "Channel 7 Clock Output Divider (value x 2) (1..255)" ],
  [ "LMK7_CLKOUT_DLY"               , WD2_LMK7_CLKOUT_DLY_REG               , WD2_LMK7_CLKOUT_DLY_MASK               , WD2_LMK7_CLKOUT_DLY_OFS              , "Channel 7 Clock Output Delay (value x 150ps)" ],
  [ "LMK8_PHASE_NOISE_OPT"          , WD2_LMK8_PHASE_NOISE_OPT_REG          , WD2_LMK8_PHASE_NOISE_OPT_MASK          , WD2_LMK8_PHASE_NOISE_OPT_OFS         , "Set LMK Register 8 (Phase Noise Optimization)" ],
  [ "LMK9_VBOOST"                   , WD2_LMK9_VBOOST_REG                   , WD2_LMK9_VBOOST_MASK                   , WD2_LMK9_VBOOST_OFS                  , "Voltage Level Boost for Clock Outputs" ],
  [ "LMK11_DIV4"                    , WD2_LMK11_DIV4_REG                    , WD2_LMK11_DIV4_MASK                    , WD2_LMK11_DIV4_OFS                   , "Divider Enable for Digital Lock Detect Circuit" ],
  [ "LMK13_OSCIN_FREQ"              , WD2_LMK13_OSCIN_FREQ_REG              , WD2_LMK13_OSCIN_FREQ_MASK              , WD2_LMK13_OSCIN_FREQ_OFS             , "Oscillator Input Calibration Adjustment in MHz (1..200)" ],
  [ "LMK13_VCO_R4_LF"               , WD2_LMK13_VCO_R4_LF_REG               , WD2_LMK13_VCO_R4_LF_MASK               , WD2_LMK13_VCO_R4_LF_OFS              , "Value for Internal Loop Filter Resistor R4 (0..4) (see datasheet)" ],
  [ "LMK13_VCO_R3_LF"               , WD2_LMK13_VCO_R3_LF_REG               , WD2_LMK13_VCO_R3_LF_MASK               , WD2_LMK13_VCO_R3_LF_OFS              , "Value for Internal Loop Filter Resistor R3 (0..4) (see datasheet)" ],
  [ "LMK13_VCO_C3_C4_LF"            , WD2_LMK13_VCO_C3_C4_LF_REG            , WD2_LMK13_VCO_C3_C4_LF_MASK            , WD2_LMK13_VCO_C3_C4_LF_OFS           , "Value for Internal Loop Filter Capacitors C3/C4 (0..11) (see ds)" ],
  [ "LMK14_EN_FOUT"                 , WD2_LMK14_EN_FOUT_REG                 , WD2_LMK14_EN_FOUT_MASK                 , WD2_LMK14_EN_FOUT_OFS                , "Enable for the Fout Pin (0 = Disabled, 1 = Enabled)" ],
  [ "LMK14_EN_CLKOUT_GLOBAL"        , WD2_LMK14_EN_CLKOUT_GLOBAL_REG        , WD2_LMK14_EN_CLKOUT_GLOBAL_MASK        , WD2_LMK14_EN_CLKOUT_GLOBAL_OFS       , "Global Clock Output Enable (0 = All Off, 1 = Normal Operation)" ],
  [ "LMK14_POWERDOWN"               , WD2_LMK14_POWERDOWN_REG               , WD2_LMK14_POWERDOWN_MASK               , WD2_LMK14_POWERDOWN_OFS              , "Powerdown (0 = Normal Operation, 1 = Device Powered Down)" ],
  [ "LMK14_PLL_MUX"                 , WD2_LMK14_PLL_MUX_REG                 , WD2_LMK14_PLL_MUX_MASK                 , WD2_LMK14_PLL_MUX_OFS                , "Output Mode of  LD Pin (0..7,9,11)" ],
  [ "LMK14_PLL_R"                   , WD2_LMK14_PLL_R_REG                   , WD2_LMK14_PLL_R_MASK                   , WD2_LMK14_PLL_R_OFS                  , "PLL R Divider Value (1..4095)" ],
  [ "LMK15_PLL_CP_GAIN"             , WD2_LMK15_PLL_CP_GAIN_REG             , WD2_LMK15_PLL_CP_GAIN_MASK             , WD2_LMK15_PLL_CP_GAIN_OFS            , "PLL Charge Pump Gain (see datasheet) (0..4)" ],
  [ "LMK15_VCO_DIV"                 , WD2_LMK15_VCO_DIV_REG                 , WD2_LMK15_VCO_DIV_MASK                 , WD2_LMK15_VCO_DIV_OFS                , "VCO Divider Value (2..8)" ],
  [ "LMK15_PLL_N"                   , WD2_LMK15_PLL_N_REG                   , WD2_LMK15_PLL_N_MASK                   , WD2_LMK15_PLL_N_OFS                  , "PLL N Divider Value (1..0x3FFFF)" ],
  [ "ADC_0_1458_DCSOFF"             , WD2_ADC_0_1458_DCSOFF_REG             , WD2_ADC_0_1458_DCSOFF_MASK             , WD2_ADC_0_1458_DCSOFF_OFS            , "Clock Duty Cycle Stabilizer (0=ON, 1=OFF)" ],
  [ "ADC_0_1458_RAND"               , WD2_ADC_0_1458_RAND_REG               , WD2_ADC_0_1458_RAND_MASK               , WD2_ADC_0_1458_RAND_OFS              , "Data Output Randomizer Mode Control Bit (0=OFF, 1=ON)" ],
  [ "ADC_0_1458_TWOSCOMP"           , WD2_ADC_0_1458_TWOSCOMP_REG           , WD2_ADC_0_1458_TWOSCOMP_MASK           , WD2_ADC_0_1458_TWOSCOMP_OFS          , "Two\'s Complement Mode Control Bit (0=Offset Binary, 1=Two\'s Complement)" ],
  [ "ADC_0_1458_SLEEP"              , WD2_ADC_0_1458_SLEEP_REG              , WD2_ADC_0_1458_SLEEP_MASK              , WD2_ADC_0_1458_SLEEP_OFS             , "Sleep Mode (1=Channels 1, 4, 5 and 8 are disabled)" ],
  [ "ADC_0_8_NAP_MODE"              , WD2_ADC_0_8_NAP_MODE_REG              , WD2_ADC_0_8_NAP_MODE_MASK              , WD2_ADC_0_8_NAP_MODE_OFS             , "Channel 8 Nap Mode (0=OFF, 1=ON)" ],
  [ "ADC_0_5_NAP_MODE"              , WD2_ADC_0_5_NAP_MODE_REG              , WD2_ADC_0_5_NAP_MODE_MASK              , WD2_ADC_0_5_NAP_MODE_OFS             , "Channel 5 Nap Mode (0=OFF, 1=ON)" ],
  [ "ADC_0_4_NAP_MODE"              , WD2_ADC_0_4_NAP_MODE_REG              , WD2_ADC_0_4_NAP_MODE_MASK              , WD2_ADC_0_4_NAP_MODE_OFS             , "Channel 4 Nap Mode (0=OFF, 1=ON)" ],
  [ "ADC_0_1_NAP_MODE"              , WD2_ADC_0_1_NAP_MODE_REG              , WD2_ADC_0_1_NAP_MODE_MASK              , WD2_ADC_0_1_NAP_MODE_OFS             , "Channel 1 Nap Mode (0=OFF, 1=ON)" ],
  [ "ADC_0_1458_ILVDS"              , WD2_ADC_0_1458_ILVDS_REG              , WD2_ADC_0_1458_ILVDS_MASK              , WD2_ADC_0_1458_ILVDS_OFS             , "LVDS Output Current Bits (1.75mA - 4.5mA, 0b111 = 2x1.75mA = 3.5mA) (see datasheet)" ],
  [ "ADC_0_1458_TERMON"             , WD2_ADC_0_1458_TERMON_REG             , WD2_ADC_0_1458_TERMON_MASK             , WD2_ADC_0_1458_TERMON_OFS            , "LVDS Internal Termination Bit (0=OFF, 1=ON)" ],
  [ "ADC_0_1458_OUTOFF"             , WD2_ADC_0_1458_OUTOFF_REG             , WD2_ADC_0_1458_OUTOFF_MASK             , WD2_ADC_0_1458_OUTOFF_OFS            , "Digital Output Disable Bit (0=Enabled, 1=Disabled)" ],
  [ "ADC_0_1458_OUTMODE"            , WD2_ADC_0_1458_OUTMODE_REG            , WD2_ADC_0_1458_OUTMODE_MASK            , WD2_ADC_0_1458_OUTMODE_OFS           , "Digital Output Mode Control Bits (0b110 = 12 Bit, 1 Lane) (see datasheet) " ],
  [ "ADC_0_1458_OUTTEST"            , WD2_ADC_0_1458_OUTTEST_REG            , WD2_ADC_0_1458_OUTTEST_MASK            , WD2_ADC_0_1458_OUTTEST_OFS           , "Output Test Pattern Control Bit (0=Pattern Off, 1=Pattern On)" ],
  [ "ADC_0_1458_TP"                 , WD2_ADC_0_1458_TP_REG                 , WD2_ADC_0_1458_TP_MASK                 , WD2_ADC_0_1458_TP_OFS                , "Test Pattern MSBs (actual test pattern in 12 bit mode)" ],
  [ "ADC_0_1458_TP_LSBS"            , WD2_ADC_0_1458_TP_LSBS_REG            , WD2_ADC_0_1458_TP_LSBS_MASK            , WD2_ADC_0_1458_TP_LSBS_OFS           , "Test Pattern LSBs" ],
  [ "ADC_0_2367_DCSOFF"             , WD2_ADC_0_2367_DCSOFF_REG             , WD2_ADC_0_2367_DCSOFF_MASK             , WD2_ADC_0_2367_DCSOFF_OFS            , "Clock Duty Cycle Stabilizer (0=ON, 1=OFF)" ],
  [ "ADC_0_2367_RAND"               , WD2_ADC_0_2367_RAND_REG               , WD2_ADC_0_2367_RAND_MASK               , WD2_ADC_0_2367_RAND_OFS              , "Data Output Randomizer Mode Control Bit (0=OFF, 1=ON)" ],
  [ "ADC_0_2367_TWOSCOMP"           , WD2_ADC_0_2367_TWOSCOMP_REG           , WD2_ADC_0_2367_TWOSCOMP_MASK           , WD2_ADC_0_2367_TWOSCOMP_OFS          , "Two\'s Complement Mode Control Bit (0=Offset Binary, 1=Two\'s Complement)" ],
  [ "ADC_0_2367_SLEEP"              , WD2_ADC_0_2367_SLEEP_REG              , WD2_ADC_0_2367_SLEEP_MASK              , WD2_ADC_0_2367_SLEEP_OFS             , "Sleep Mode (1=Channels 2, 3, 6 and 7 are disabled)" ],
  [ "ADC_0_7_NAP_MODE"              , WD2_ADC_0_7_NAP_MODE_REG              , WD2_ADC_0_7_NAP_MODE_MASK              , WD2_ADC_0_7_NAP_MODE_OFS             , "Channel 7 Nap Mode (0=OFF, 1=ON)" ],
  [ "ADC_0_6_NAP_MODE"              , WD2_ADC_0_6_NAP_MODE_REG              , WD2_ADC_0_6_NAP_MODE_MASK              , WD2_ADC_0_6_NAP_MODE_OFS             , "Channel 6 Nap Mode (0=OFF, 1=ON)" ],
  [ "ADC_0_3_NAP_MODE"              , WD2_ADC_0_3_NAP_MODE_REG              , WD2_ADC_0_3_NAP_MODE_MASK              , WD2_ADC_0_3_NAP_MODE_OFS             , "Channel 3 Nap Mode (0=OFF, 1=ON)" ],
  [ "ADC_0_2_NAP_MODE"              , WD2_ADC_0_2_NAP_MODE_REG              , WD2_ADC_0_2_NAP_MODE_MASK              , WD2_ADC_0_2_NAP_MODE_OFS             , "Channel 2 Nap Mode (0=OFF, 1=ON)" ],
  [ "ADC_0_2367_ILVDS"              , WD2_ADC_0_2367_ILVDS_REG              , WD2_ADC_0_2367_ILVDS_MASK              , WD2_ADC_0_2367_ILVDS_OFS             , "LVDS Output Current Bits (1.75mA - 4.5mA, 0b111 = 2x1.75mA = 3.5mA) (see datasheet)" ],
  [ "ADC_0_2367_TERMON"             , WD2_ADC_0_2367_TERMON_REG             , WD2_ADC_0_2367_TERMON_MASK             , WD2_ADC_0_2367_TERMON_OFS            , "LVDS Internal Termination Bit (0=OFF, 1=ON)" ],
  [ "ADC_0_2367_OUTOFF"             , WD2_ADC_0_2367_OUTOFF_REG             , WD2_ADC_0_2367_OUTOFF_MASK             , WD2_ADC_0_2367_OUTOFF_OFS            , "Digital Output Disable Bit (0=Enabled, 1=Disabled)" ],
  [ "ADC_0_2367_OUTMODE"            , WD2_ADC_0_2367_OUTMODE_REG            , WD2_ADC_0_2367_OUTMODE_MASK            , WD2_ADC_0_2367_OUTMODE_OFS           , "Digital Output Mode Control Bits (0b110 = 12 Bit, 1 Lane) (see datasheet) " ],
  [ "ADC_0_2367_OUTTEST"            , WD2_ADC_0_2367_OUTTEST_REG            , WD2_ADC_0_2367_OUTTEST_MASK            , WD2_ADC_0_2367_OUTTEST_OFS           , "Output Test Pattern Control Bit (0=Pattern Off, 1=Pattern On)" ],
  [ "ADC_0_2367_TP"                 , WD2_ADC_0_2367_TP_REG                 , WD2_ADC_0_2367_TP_MASK                 , WD2_ADC_0_2367_TP_OFS                , "Test Pattern MSBs (actual test pattern in 12 bit mode)" ],
  [ "ADC_0_2367_TP_LSBS"            , WD2_ADC_0_2367_TP_LSBS_REG            , WD2_ADC_0_2367_TP_LSBS_MASK            , WD2_ADC_0_2367_TP_LSBS_OFS           , "Test Pattern LSBs" ],
  [ "ADC_1_1458_DCSOFF"             , WD2_ADC_1_1458_DCSOFF_REG             , WD2_ADC_1_1458_DCSOFF_MASK             , WD2_ADC_1_1458_DCSOFF_OFS            , "Clock Duty Cycle Stabilizer (0=ON, 1=OFF)" ],
  [ "ADC_1_1458_RAND"               , WD2_ADC_1_1458_RAND_REG               , WD2_ADC_1_1458_RAND_MASK               , WD2_ADC_1_1458_RAND_OFS              , "Data Output Randomizer Mode Control Bit (0=OFF, 1=ON)" ],
  [ "ADC_1_1458_TWOSCOMP"           , WD2_ADC_1_1458_TWOSCOMP_REG           , WD2_ADC_1_1458_TWOSCOMP_MASK           , WD2_ADC_1_1458_TWOSCOMP_OFS          , "Two\'s Complement Mode Control Bit (0=Offset Binary, 1=Two\'s Complement)" ],
  [ "ADC_1_1458_SLEEP"              , WD2_ADC_1_1458_SLEEP_REG              , WD2_ADC_1_1458_SLEEP_MASK              , WD2_ADC_1_1458_SLEEP_OFS             , "Sleep Mode (1=Channels 1, 4, 5 and 8 are disabled)" ],
  [ "ADC_1_8_NAP_MODE"              , WD2_ADC_1_8_NAP_MODE_REG              , WD2_ADC_1_8_NAP_MODE_MASK              , WD2_ADC_1_8_NAP_MODE_OFS             , "Channel 8 Nap Mode (0=OFF, 1=ON)" ],
  [ "ADC_1_5_NAP_MODE"              , WD2_ADC_1_5_NAP_MODE_REG              , WD2_ADC_1_5_NAP_MODE_MASK              , WD2_ADC_1_5_NAP_MODE_OFS             , "Channel 5 Nap Mode (0=OFF, 1=ON)" ],
  [ "ADC_1_4_NAP_MODE"              , WD2_ADC_1_4_NAP_MODE_REG              , WD2_ADC_1_4_NAP_MODE_MASK              , WD2_ADC_1_4_NAP_MODE_OFS             , "Channel 4 Nap Mode (0=OFF, 1=ON)" ],
  [ "ADC_1_1_NAP_MODE"              , WD2_ADC_1_1_NAP_MODE_REG              , WD2_ADC_1_1_NAP_MODE_MASK              , WD2_ADC_1_1_NAP_MODE_OFS             , "Channel 1 Nap Mode (0=OFF, 1=ON)" ],
  [ "ADC_1_1458_ILVDS"              , WD2_ADC_1_1458_ILVDS_REG              , WD2_ADC_1_1458_ILVDS_MASK              , WD2_ADC_1_1458_ILVDS_OFS             , "LVDS Output Current Bits (1.75mA - 4.5mA, 0b111 = 2x1.75mA = 3.5mA) (see datasheet)" ],
  [ "ADC_1_1458_TERMON"             , WD2_ADC_1_1458_TERMON_REG             , WD2_ADC_1_1458_TERMON_MASK             , WD2_ADC_1_1458_TERMON_OFS            , "LVDS Internal Termination Bit (0=OFF, 1=ON)" ],
  [ "ADC_1_1458_OUTOFF"             , WD2_ADC_1_1458_OUTOFF_REG             , WD2_ADC_1_1458_OUTOFF_MASK             , WD2_ADC_1_1458_OUTOFF_OFS            , "Digital Output Disable Bit (0=Enabled, 1=Disabled)" ],
  [ "ADC_1_1458_OUTMODE"            , WD2_ADC_1_1458_OUTMODE_REG            , WD2_ADC_1_1458_OUTMODE_MASK            , WD2_ADC_1_1458_OUTMODE_OFS           , "Digital Output Mode Control Bits (0b110 = 12 Bit, 1 Lane) (see datasheet) " ],
  [ "ADC_1_1458_OUTTEST"            , WD2_ADC_1_1458_OUTTEST_REG            , WD2_ADC_1_1458_OUTTEST_MASK            , WD2_ADC_1_1458_OUTTEST_OFS           , "Output Test Pattern Control Bit (0=Pattern Off, 1=Pattern On)" ],
  [ "ADC_1_1458_TP"                 , WD2_ADC_1_1458_TP_REG                 , WD2_ADC_1_1458_TP_MASK                 , WD2_ADC_1_1458_TP_OFS                , "Test Pattern MSBs (actual test pattern in 12 bit mode)" ],
  [ "ADC_1_1458_TP_LSBS"            , WD2_ADC_1_1458_TP_LSBS_REG            , WD2_ADC_1_1458_TP_LSBS_MASK            , WD2_ADC_1_1458_TP_LSBS_OFS           , "Test Pattern LSBs" ],
  [ "ADC_1_2367_DCSOFF"             , WD2_ADC_1_2367_DCSOFF_REG             , WD2_ADC_1_2367_DCSOFF_MASK             , WD2_ADC_1_2367_DCSOFF_OFS            , "Clock Duty Cycle Stabilizer (0=ON, 1=OFF)" ],
  [ "ADC_1_2367_RAND"               , WD2_ADC_1_2367_RAND_REG               , WD2_ADC_1_2367_RAND_MASK               , WD2_ADC_1_2367_RAND_OFS              , "Data Output Randomizer Mode Control Bit (0=OFF, 1=ON)" ],
  [ "ADC_1_2367_TWOSCOMP"           , WD2_ADC_1_2367_TWOSCOMP_REG           , WD2_ADC_1_2367_TWOSCOMP_MASK           , WD2_ADC_1_2367_TWOSCOMP_OFS          , "Two\'s Complement Mode Control Bit (0=Offset Binary, 1=Two\'s Complement)" ],
  [ "ADC_1_2367_SLEEP"              , WD2_ADC_1_2367_SLEEP_REG              , WD2_ADC_1_2367_SLEEP_MASK              , WD2_ADC_1_2367_SLEEP_OFS             , "Sleep Mode (1=Channels 2, 3, 6 and 7 are disabled)" ],
  [ "ADC_1_7_NAP_MODE"              , WD2_ADC_1_7_NAP_MODE_REG              , WD2_ADC_1_7_NAP_MODE_MASK              , WD2_ADC_1_7_NAP_MODE_OFS             , "Channel 7 Nap Mode (0=OFF, 1=ON)" ],
  [ "ADC_1_6_NAP_MODE"              , WD2_ADC_1_6_NAP_MODE_REG              , WD2_ADC_1_6_NAP_MODE_MASK              , WD2_ADC_1_6_NAP_MODE_OFS             , "Channel 6 Nap Mode (0=OFF, 1=ON)" ],
  [ "ADC_1_3_NAP_MODE"              , WD2_ADC_1_3_NAP_MODE_REG              , WD2_ADC_1_3_NAP_MODE_MASK              , WD2_ADC_1_3_NAP_MODE_OFS             , "Channel 3 Nap Mode (0=OFF, 1=ON)" ],
  [ "ADC_1_2_NAP_MODE"              , WD2_ADC_1_2_NAP_MODE_REG              , WD2_ADC_1_2_NAP_MODE_MASK              , WD2_ADC_1_2_NAP_MODE_OFS             , "Channel 2 Nap Mode (0=OFF, 1=ON)" ],
  [ "ADC_1_2367_ILVDS"              , WD2_ADC_1_2367_ILVDS_REG              , WD2_ADC_1_2367_ILVDS_MASK              , WD2_ADC_1_2367_ILVDS_OFS             , "LVDS Output Current Bits (1.75mA - 4.5mA, 0b111 = 2x1.75mA = 3.5mA) (see datasheet)" ],
  [ "ADC_1_2367_TERMON"             , WD2_ADC_1_2367_TERMON_REG             , WD2_ADC_1_2367_TERMON_MASK             , WD2_ADC_1_2367_TERMON_OFS            , "LVDS Internal Termination Bit (0=OFF, 1=ON)" ],
  [ "ADC_1_2367_OUTOFF"             , WD2_ADC_1_2367_OUTOFF_REG             , WD2_ADC_1_2367_OUTOFF_MASK             , WD2_ADC_1_2367_OUTOFF_OFS            , "Digital Output Disable Bit (0=Enabled, 1=Disabled)" ],
  [ "ADC_1_2367_OUTMODE"            , WD2_ADC_1_2367_OUTMODE_REG            , WD2_ADC_1_2367_OUTMODE_MASK            , WD2_ADC_1_2367_OUTMODE_OFS           , "Digital Output Mode Control Bits (0b110 = 12 Bit, 1 Lane) (see datasheet) " ],
  [ "ADC_1_2367_OUTTEST"            , WD2_ADC_1_2367_OUTTEST_REG            , WD2_ADC_1_2367_OUTTEST_MASK            , WD2_ADC_1_2367_OUTTEST_OFS           , "Output Test Pattern Control Bit (0=Pattern Off, 1=Pattern On)" ],
  [ "ADC_1_2367_TP"                 , WD2_ADC_1_2367_TP_REG                 , WD2_ADC_1_2367_TP_MASK                 , WD2_ADC_1_2367_TP_OFS                , "Test Pattern MSBs (actual test pattern in 12 bit mode)" ],
  [ "ADC_1_2367_TP_LSBS"            , WD2_ADC_1_2367_TP_LSBS_REG            , WD2_ADC_1_2367_TP_LSBS_MASK            , WD2_ADC_1_2367_TP_LSBS_OFS           , "Test Pattern LSBs" ],
  [ "TRIGGER_OUT_PULSE_LENGTH"      , WD2_TRIGGER_OUT_PULSE_LENGTH_REG      , WD2_TRIGGER_OUT_PULSE_LENGTH_MASK      , WD2_TRIGGER_OUT_PULSE_LENGTH_OFS     , "Length of the trigger output pulse in cycles" ],
  [ "LEAD_TRAIL_EDGE_SEL"           , WD2_LEAD_TRAIL_EDGE_SEL_REG           , WD2_LEAD_TRAIL_EDGE_SEL_MASK           , WD2_LEAD_TRAIL_EDGE_SEL_OFS          , "0 = trigger on leading edge, 1 = trigger on trailing edge" ],
  [ "EXT_TRIGGER_OUT_ENABLE"        , WD2_EXT_TRIGGER_OUT_ENABLE_REG        , WD2_EXT_TRIGGER_OUT_ENABLE_MASK        , WD2_EXT_TRIGGER_OUT_ENABLE_OFS       , "Enable output of trigger signal to MCX connector" ],
  [ "EXT_ASYNC_TRIGGER_EN"          , WD2_EXT_ASYNC_TRIGGER_EN_REG          , WD2_EXT_ASYNC_TRIGGER_EN_MASK          , WD2_EXT_ASYNC_TRIGGER_EN_OFS         , "Enable asynchronous external trigger" ],
  [ "PATTERN_TRIGGER_EN"            , WD2_PATTERN_TRIGGER_EN_REG            , WD2_PATTERN_TRIGGER_EN_MASK            , WD2_PATTERN_TRIGGER_EN_OFS           , "Enable internal (synchronous) pattern trigger" ],
  [ "TRIGGER_DELAY"                 , WD2_TRIGGER_DELAY_REG                 , WD2_TRIGGER_DELAY_MASK                 , WD2_TRIGGER_DELAY_OFS                , "trigger delay in ticks of 6.25 ns" ],
  [ "TRG_SRC_POLARITY"              , WD2_TRG_SRC_POLARITY_REG              , WD2_TRG_SRC_POLARITY_MASK              , WD2_TRG_SRC_POLARITY_OFS             , "Polarity of trigger source (0 = normal, 1 = inverted) (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)" ],
  [ "AUTO_TRIGGER_PERIOD"           , WD2_AUTO_TRIGGER_PERIOD_REG           , WD2_AUTO_TRIGGER_PERIOD_MASK           , WD2_AUTO_TRIGGER_PERIOD_OFS          , "Period of automatic trigger in ticks of the DAQ clock" ],
  [ "TRG_PTRN_EN"                   , WD2_TRG_PTRN_EN_REG                   , WD2_TRG_PTRN_EN_MASK                   , WD2_TRG_PTRN_EN_OFS                  , "1 enables the corresponding trigger patterns for the local trigger" ],
  [ "TRG_SRC_EN_PTRN0"              , WD2_TRG_SRC_EN_PTRN0_REG              , WD2_TRG_SRC_EN_PTRN0_MASK              , WD2_TRG_SRC_EN_PTRN0_OFS             , "trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)" ],
  [ "TRG_STATE_PTRN0"               , WD2_TRG_STATE_PTRN0_REG               , WD2_TRG_STATE_PTRN0_MASK               , WD2_TRG_STATE_PTRN0_OFS              , "trigger source state pattern (0 = Inhibit, 1 = Coincidence)" ],
  [ "TRG_SRC_EN_PTRN1"              , WD2_TRG_SRC_EN_PTRN1_REG              , WD2_TRG_SRC_EN_PTRN1_MASK              , WD2_TRG_SRC_EN_PTRN1_OFS             , "trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)" ],
  [ "TRG_STATE_PTRN1"               , WD2_TRG_STATE_PTRN1_REG               , WD2_TRG_STATE_PTRN1_MASK               , WD2_TRG_STATE_PTRN1_OFS              , "trigger source state pattern (0 = Inhibit, 1 = Coincidence)" ],
  [ "TRG_SRC_EN_PTRN2"              , WD2_TRG_SRC_EN_PTRN2_REG              , WD2_TRG_SRC_EN_PTRN2_MASK              , WD2_TRG_SRC_EN_PTRN2_OFS             , "trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)" ],
  [ "TRG_STATE_PTRN2"               , WD2_TRG_STATE_PTRN2_REG               , WD2_TRG_STATE_PTRN2_MASK               , WD2_TRG_STATE_PTRN2_OFS              , "trigger source state pattern (0 = Inhibit, 1 = Coincidence)" ],
  [ "TRG_SRC_EN_PTRN3"              , WD2_TRG_SRC_EN_PTRN3_REG              , WD2_TRG_SRC_EN_PTRN3_MASK              , WD2_TRG_SRC_EN_PTRN3_OFS             , "trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)" ],
  [ "TRG_STATE_PTRN3"               , WD2_TRG_STATE_PTRN3_REG               , WD2_TRG_STATE_PTRN3_MASK               , WD2_TRG_STATE_PTRN3_OFS              , "trigger source state pattern (0 = Inhibit, 1 = Coincidence)" ],
  [ "TRG_SRC_EN_PTRN4"              , WD2_TRG_SRC_EN_PTRN4_REG              , WD2_TRG_SRC_EN_PTRN4_MASK              , WD2_TRG_SRC_EN_PTRN4_OFS             , "trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)" ],
  [ "TRG_STATE_PTRN4"               , WD2_TRG_STATE_PTRN4_REG               , WD2_TRG_STATE_PTRN4_MASK               , WD2_TRG_STATE_PTRN4_OFS              , "trigger source state pattern (0 = Inhibit, 1 = Coincidence)" ],
  [ "TRG_SRC_EN_PTRN5"              , WD2_TRG_SRC_EN_PTRN5_REG              , WD2_TRG_SRC_EN_PTRN5_MASK              , WD2_TRG_SRC_EN_PTRN5_OFS             , "trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)" ],
  [ "TRG_STATE_PTRN5"               , WD2_TRG_STATE_PTRN5_REG               , WD2_TRG_STATE_PTRN5_MASK               , WD2_TRG_STATE_PTRN5_OFS              , "trigger source state pattern (0 = Inhibit, 1 = Coincidence)" ],
  [ "TRG_SRC_EN_PTRN6"              , WD2_TRG_SRC_EN_PTRN6_REG              , WD2_TRG_SRC_EN_PTRN6_MASK              , WD2_TRG_SRC_EN_PTRN6_OFS             , "trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)" ],
  [ "TRG_STATE_PTRN6"               , WD2_TRG_STATE_PTRN6_REG               , WD2_TRG_STATE_PTRN6_MASK               , WD2_TRG_STATE_PTRN6_OFS              , "trigger source state pattern (0 = Inhibit, 1 = Coincidence)" ],
  [ "TRG_SRC_EN_PTRN7"              , WD2_TRG_SRC_EN_PTRN7_REG              , WD2_TRG_SRC_EN_PTRN7_MASK              , WD2_TRG_SRC_EN_PTRN7_OFS             , "trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)" ],
  [ "TRG_STATE_PTRN7"               , WD2_TRG_STATE_PTRN7_REG               , WD2_TRG_STATE_PTRN7_MASK               , WD2_TRG_STATE_PTRN7_OFS              , "trigger source state pattern (0 = Inhibit, 1 = Coincidence)" ],
  [ "TRG_SRC_EN_PTRN8"              , WD2_TRG_SRC_EN_PTRN8_REG              , WD2_TRG_SRC_EN_PTRN8_MASK              , WD2_TRG_SRC_EN_PTRN8_OFS             , "trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)" ],
  [ "TRG_STATE_PTRN8"               , WD2_TRG_STATE_PTRN8_REG               , WD2_TRG_STATE_PTRN8_MASK               , WD2_TRG_STATE_PTRN8_OFS              , "trigger source state pattern (0 = Inhibit, 1 = Coincidence)" ],
  [ "TRG_SRC_EN_PTRN9"              , WD2_TRG_SRC_EN_PTRN9_REG              , WD2_TRG_SRC_EN_PTRN9_MASK              , WD2_TRG_SRC_EN_PTRN9_OFS             , "trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)" ],
  [ "TRG_STATE_PTRN9"               , WD2_TRG_STATE_PTRN9_REG               , WD2_TRG_STATE_PTRN9_MASK               , WD2_TRG_STATE_PTRN9_OFS              , "trigger source state pattern (0 = Inhibit, 1 = Coincidence)" ],
  [ "TRG_SRC_EN_PTRN10"             , WD2_TRG_SRC_EN_PTRN10_REG             , WD2_TRG_SRC_EN_PTRN10_MASK             , WD2_TRG_SRC_EN_PTRN10_OFS            , "trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)" ],
  [ "TRG_STATE_PTRN10"              , WD2_TRG_STATE_PTRN10_REG              , WD2_TRG_STATE_PTRN10_MASK              , WD2_TRG_STATE_PTRN10_OFS             , "trigger source state pattern (0 = Inhibit, 1 = Coincidence)" ],
  [ "TRG_SRC_EN_PTRN11"             , WD2_TRG_SRC_EN_PTRN11_REG             , WD2_TRG_SRC_EN_PTRN11_MASK             , WD2_TRG_SRC_EN_PTRN11_OFS            , "trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)" ],
  [ "TRG_STATE_PTRN11"              , WD2_TRG_STATE_PTRN11_REG              , WD2_TRG_STATE_PTRN11_MASK              , WD2_TRG_STATE_PTRN11_OFS             , "trigger source state pattern (0 = Inhibit, 1 = Coincidence)" ],
  [ "TRG_SRC_EN_PTRN12"             , WD2_TRG_SRC_EN_PTRN12_REG             , WD2_TRG_SRC_EN_PTRN12_MASK             , WD2_TRG_SRC_EN_PTRN12_OFS            , "trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)" ],
  [ "TRG_STATE_PTRN12"              , WD2_TRG_STATE_PTRN12_REG              , WD2_TRG_STATE_PTRN12_MASK              , WD2_TRG_STATE_PTRN12_OFS             , "trigger source state pattern (0 = Inhibit, 1 = Coincidence)" ],
  [ "TRG_SRC_EN_PTRN13"             , WD2_TRG_SRC_EN_PTRN13_REG             , WD2_TRG_SRC_EN_PTRN13_MASK             , WD2_TRG_SRC_EN_PTRN13_OFS            , "trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)" ],
  [ "TRG_STATE_PTRN13"              , WD2_TRG_STATE_PTRN13_REG              , WD2_TRG_STATE_PTRN13_MASK              , WD2_TRG_STATE_PTRN13_OFS             , "trigger source state pattern (0 = Inhibit, 1 = Coincidence)" ],
  [ "TRG_SRC_EN_PTRN14"             , WD2_TRG_SRC_EN_PTRN14_REG             , WD2_TRG_SRC_EN_PTRN14_MASK             , WD2_TRG_SRC_EN_PTRN14_OFS            , "trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)" ],
  [ "TRG_STATE_PTRN14"              , WD2_TRG_STATE_PTRN14_REG              , WD2_TRG_STATE_PTRN14_MASK              , WD2_TRG_STATE_PTRN14_OFS             , "trigger source state pattern (0 = Inhibit, 1 = Coincidence)" ],
  [ "TRG_SRC_EN_PTRN15"             , WD2_TRG_SRC_EN_PTRN15_REG             , WD2_TRG_SRC_EN_PTRN15_MASK             , WD2_TRG_SRC_EN_PTRN15_OFS            , "trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)" ],
  [ "TRG_STATE_PTRN15"              , WD2_TRG_STATE_PTRN15_REG              , WD2_TRG_STATE_PTRN15_MASK              , WD2_TRG_STATE_PTRN15_OFS             , "trigger source state pattern (0 = Inhibit, 1 = Coincidence)" ],
  [ "TRG_SRC_EN_PTRN16"             , WD2_TRG_SRC_EN_PTRN16_REG             , WD2_TRG_SRC_EN_PTRN16_MASK             , WD2_TRG_SRC_EN_PTRN16_OFS            , "trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)" ],
  [ "TRG_STATE_PTRN16"              , WD2_TRG_STATE_PTRN16_REG              , WD2_TRG_STATE_PTRN16_MASK              , WD2_TRG_STATE_PTRN16_OFS             , "trigger source state pattern (0 = Inhibit, 1 = Coincidence)" ],
  [ "TRG_SRC_EN_PTRN17"             , WD2_TRG_SRC_EN_PTRN17_REG             , WD2_TRG_SRC_EN_PTRN17_MASK             , WD2_TRG_SRC_EN_PTRN17_OFS            , "trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)" ],
  [ "TRG_STATE_PTRN17"              , WD2_TRG_STATE_PTRN17_REG              , WD2_TRG_STATE_PTRN17_MASK              , WD2_TRG_STATE_PTRN17_OFS             , "trigger source state pattern (0 = Inhibit, 1 = Coincidence)" ],
  [ "TRG_SRC_EN_PTRN18"             , WD2_TRG_SRC_EN_PTRN18_REG             , WD2_TRG_SRC_EN_PTRN18_MASK             , WD2_TRG_SRC_EN_PTRN18_OFS            , "trigger source enables for pattern (sources: 18=adv, 17=adv_veto, 16=ext, 15:0=drs ch)" ],
  [ "TRG_STATE_PTRN18"              , WD2_TRG_STATE_PTRN18_REG              , WD2_TRG_STATE_PTRN18_MASK              , WD2_TRG_STATE_PTRN18_OFS             , "trigger source state pattern (0 = Inhibit, 1 = Coincidence)" ],
  [ "ADV_TRG_CTRL"                  , WD2_ADV_TRG_CTRL_REG                  , WD2_ADV_TRG_CTRL_MASK                  , WD2_ADV_TRG_CTRL_OFS                 , "Advanced trigger control register" ],
  [ "ADV_TRG_CH_CAL0"               , WD2_ADV_TRG_CH_CAL0_REG               , WD2_ADV_TRG_CH_CAL0_MASK               , WD2_ADV_TRG_CH_CAL0_OFS              , "Advanced trigger channel calibration register 0" ],
  [ "ADV_TRG_CH_CAL1"               , WD2_ADV_TRG_CH_CAL1_REG               , WD2_ADV_TRG_CH_CAL1_MASK               , WD2_ADV_TRG_CH_CAL1_OFS              , "Advanced trigger channel calibration register 1" ],
  [ "ADV_TRG_CH_CAL2"               , WD2_ADV_TRG_CH_CAL2_REG               , WD2_ADV_TRG_CH_CAL2_MASK               , WD2_ADV_TRG_CH_CAL2_OFS              , "Advanced trigger channel calibration register 2" ],
  [ "ADV_TRG_CH_CAL3"               , WD2_ADV_TRG_CH_CAL3_REG               , WD2_ADV_TRG_CH_CAL3_MASK               , WD2_ADV_TRG_CH_CAL3_OFS              , "Advanced trigger channel calibration register 3" ],
  [ "ADV_TRG_PED_CFG"               , WD2_ADV_TRG_PED_CFG_REG               , WD2_ADV_TRG_PED_CFG_MASK               , WD2_ADV_TRG_PED_CFG_OFS              , "Advanced trigger pedestal configuration register" ],
  [ "ADV_TRG_THR0"                  , WD2_ADV_TRG_THR0_REG                  , WD2_ADV_TRG_THR0_MASK                  , WD2_ADV_TRG_THR0_OFS                 , "Advanced trigger threshold 0 register" ],
  [ "ADV_TRG_THR1"                  , WD2_ADV_TRG_THR1_REG                  , WD2_ADV_TRG_THR1_MASK                  , WD2_ADV_TRG_THR1_OFS                 , "Advanced trigger threshold 1 register" ],
  [ "ADV_TRG_THR2"                  , WD2_ADV_TRG_THR2_REG                  , WD2_ADV_TRG_THR2_MASK                  , WD2_ADV_TRG_THR2_OFS                 , "Advanced trigger threshold 2 register" ],
  [ "ADV_TRG_TX_CHK_WORD0"          , WD2_ADV_TRG_TX_CHK_WORD0_REG          , WD2_ADV_TRG_TX_CHK_WORD0_MASK          , WD2_ADV_TRG_TX_CHK_WORD0_OFS         , "Advanced trigger transmition check word 0 register" ],
  [ "ADV_TRG_TX_CHK_WORD1"          , WD2_ADV_TRG_TX_CHK_WORD1_REG          , WD2_ADV_TRG_TX_CHK_WORD1_MASK          , WD2_ADV_TRG_TX_CHK_WORD1_OFS         , "Advanced trigger transmition check word 1 register" ],
  [ "ADV_TRG_TDC_CH_MASK"           , WD2_ADV_TRG_TDC_CH_MASK_REG           , WD2_ADV_TRG_TDC_CH_MASK_MASK           , WD2_ADV_TRG_TDC_CH_MASK_OFS          , "Advanced trigger TDC channel mask" ],
  [ "ADV_TRG_CFG_12"                , WD2_ADV_TRG_CFG_12_REG                , WD2_ADV_TRG_CFG_12_MASK                , WD2_ADV_TRG_CFG_12_OFS               , "Advanced trigger configuration register 12" ],
  [ "ADV_TRG_CFG_13"                , WD2_ADV_TRG_CFG_13_REG                , WD2_ADV_TRG_CFG_13_MASK                , WD2_ADV_TRG_CFG_13_OFS               , "Advanced trigger configuration register 13" ],
  [ "ADV_TRG_CFG_14"                , WD2_ADV_TRG_CFG_14_REG                , WD2_ADV_TRG_CFG_14_MASK                , WD2_ADV_TRG_CFG_14_OFS               , "Advanced trigger configuration register 14" ],
  [ "ADV_TRG_CFG_15"                , WD2_ADV_TRG_CFG_15_REG                , WD2_ADV_TRG_CFG_15_MASK                , WD2_ADV_TRG_CFG_15_OFS               , "Advanced trigger configuration register 15" ],
  [ "ADV_TRG_CFG_16"                , WD2_ADV_TRG_CFG_16_REG                , WD2_ADV_TRG_CFG_16_MASK                , WD2_ADV_TRG_CFG_16_OFS               , "Advanced trigger configuration register 16" ],
  [ "ADV_TRG_CFG_17"                , WD2_ADV_TRG_CFG_17_REG                , WD2_ADV_TRG_CFG_17_MASK                , WD2_ADV_TRG_CFG_17_OFS               , "Advanced trigger configuration register 17" ],
  [ "ADV_TRG_CFG_18"                , WD2_ADV_TRG_CFG_18_REG                , WD2_ADV_TRG_CFG_18_MASK                , WD2_ADV_TRG_CFG_18_OFS               , "Advanced trigger configuration register 18" ],
  [ "ADV_TRG_CFG_19"                , WD2_ADV_TRG_CFG_19_REG                , WD2_ADV_TRG_CFG_19_MASK                , WD2_ADV_TRG_CFG_19_OFS               , "Advanced trigger configuration register 19" ],
  [ "SET_TIME_LSB"                  , WD2_SET_TIME_LSB_REG                  , WD2_SET_TIME_LSB_MASK                  , WD2_SET_TIME_LSB_OFS                 , "LSBs of 64bit system time counter set value  (time is updated when MSBs are written)" ],
  [ "SET_TIME_MSB"                  , WD2_SET_TIME_MSB_REG                  , WD2_SET_TIME_MSB_MASK                  , WD2_SET_TIME_MSB_OFS                 , "MSBs of 64bit system time counter set value  (time is updated when MSBs are written)" ],
  [ "MCX_TX_SIG_SEL"                , WD2_MCX_TX_SIG_SEL_REG                , WD2_MCX_TX_SIG_SEL_MASK                , WD2_MCX_TX_SIG_SEL_OFS               , "Select for TX connector (see RX connector for mapping)" ],
  [ "MCX_RX_SIG_SEL"                , WD2_MCX_RX_SIG_SEL_REG                , WD2_MCX_RX_SIG_SEL_MASK                , WD2_MCX_RX_SIG_SEL_OFS               , "Select for RX connector: / 0x0 = UART (communication to MicroBlaze) / 0x1 = Trigger (internal hardware trigger signal to DRS control FSM) / 0x2 = Soft Trigger (trigger signal from MicroBlaze) / 0x3 = External Trigger (OR connection of external trigger from MCX and Backplane) / 0x4 = Sync Signal from Backplane (direct, active high) / 0x5 = Sync Signal from Backplane (sampled, output to LMK, active low) / 0x6 = Sync Signal from Backplane (sampled, used for internal logic, active high) / 0x7 = Busy Local (active high) / 0x8 = Busy from Backplane (active high) / 0x9 = LMK Reference Clock (LMK input clock)  / 0xA = ADC Sampling Clock  / 0xB = Divided Data Clock (phase shifted) / 0xC = LMK5 clock (directly routed from corresponding input) / 0xD = SPI CS of LMK (active low)" ],
  [ "CRC32_REG_BANK"                , WD2_CRC32_REG_BANK_REG                , WD2_CRC32_REG_BANK_MASK                , WD2_CRC32_REG_BANK_OFS               , "Keep at the end of the register bank" ],
  [ "BOARD_MAGIC"                   , WD2_BOARD_MAGIC_REG                   , WD2_BOARD_MAGIC_MASK                   , WD2_BOARD_MAGIC_OFS                  , "0xAC, Magic number for DRS board identification" ],
  [ "VENDOR_ID"                     , WD2_VENDOR_ID_REG                     , WD2_VENDOR_ID_MASK                     , WD2_VENDOR_ID_OFS                    , "ID of the board vendor (0x01 for PSI)" ],
  [ "BOARD_TYPE"                    , WD2_BOARD_TYPE_REG                    , WD2_BOARD_TYPE_MASK                    , WD2_BOARD_TYPE_OFS                   , "WaveDream Number (0x02 for WD2)" ],
  [ "BOARD_REVISION"                , WD2_BOARD_REVISION_REG                , WD2_BOARD_REVISION_MASK                , WD2_BOARD_REVISION_OFS               , "Board revision (A=0x00, C=0x02, D=0x03, E=0x04, F=0x05, G=0x06)" ],
  [ "BOARD_VARIANT"                 , WD2_BOARD_VARIANT_REG                 , WD2_BOARD_VARIANT_MASK                 , WD2_BOARD_VARIANT_OFS                , "Version indicator pins reflecting the variant of the board (Y15,Y10)" ],
  [ "REG_LAYOUT_COMP_LEVEL"         , WD2_REG_LAYOUT_COMP_LEVEL_REG         , WD2_REG_LAYOUT_COMP_LEVEL_MASK         , WD2_REG_LAYOUT_COMP_LEVEL_OFS        , "Register map layout compatibility level" ],
  [ "REG_LAYOUT_VERSION"            , WD2_REG_LAYOUT_VERSION_REG            , WD2_REG_LAYOUT_VERSION_MASK            , WD2_REG_LAYOUT_VERSION_OFS           , "Register map layout version" ],
  [ "FW_BUILD_YEAR"                 , WD2_FW_BUILD_YEAR_REG                 , WD2_FW_BUILD_YEAR_MASK                 , WD2_FW_BUILD_YEAR_OFS                , "Year of the firmware build" ],
  [ "FW_BUILD_MONTH"                , WD2_FW_BUILD_MONTH_REG                , WD2_FW_BUILD_MONTH_MASK                , WD2_FW_BUILD_MONTH_OFS               , "Month of the firmware build" ],
  [ "FW_BUILD_DAY"                  , WD2_FW_BUILD_DAY_REG                  , WD2_FW_BUILD_DAY_MASK                  , WD2_FW_BUILD_DAY_OFS                 , "Day of the firmware build" ],
  [ "FW_COMPAT_LEVEL"               , WD2_FW_COMPAT_LEVEL_REG               , WD2_FW_COMPAT_LEVEL_MASK               , WD2_FW_COMPAT_LEVEL_OFS              , "Firmware compatibility level" ],
  [ "FW_BUILD_HOUR"                 , WD2_FW_BUILD_HOUR_REG                 , WD2_FW_BUILD_HOUR_MASK                 , WD2_FW_BUILD_HOUR_OFS                , "Hour of the firmware build" ],
  [ "FW_BUILD_MINUTE"               , WD2_FW_BUILD_MINUTE_REG               , WD2_FW_BUILD_MINUTE_MASK               , WD2_FW_BUILD_MINUTE_OFS              , "Minute of the firmware build" ],
  [ "FW_BUILD_SECOND"               , WD2_FW_BUILD_SECOND_REG               , WD2_FW_BUILD_SECOND_MASK               , WD2_FW_BUILD_SECOND_OFS              , "Second of the firmware build" ],
  [ "SW_BUILD_YEAR"                 , WD2_SW_BUILD_YEAR_REG                 , WD2_SW_BUILD_YEAR_MASK                 , WD2_SW_BUILD_YEAR_OFS                , "Year of the software build" ],
  [ "SW_BUILD_MONTH"                , WD2_SW_BUILD_MONTH_REG                , WD2_SW_BUILD_MONTH_MASK                , WD2_SW_BUILD_MONTH_OFS               , "Month of the software build" ],
  [ "SW_BUILD_DAY"                  , WD2_SW_BUILD_DAY_REG                  , WD2_SW_BUILD_DAY_MASK                  , WD2_SW_BUILD_DAY_OFS                 , "Day of the software build" ],
  [ "SW_BUILD_HOUR"                 , WD2_SW_BUILD_HOUR_REG                 , WD2_SW_BUILD_HOUR_MASK                 , WD2_SW_BUILD_HOUR_OFS                , "Hour of the software build" ],
  [ "SW_BUILD_MINUTE"               , WD2_SW_BUILD_MINUTE_REG               , WD2_SW_BUILD_MINUTE_MASK               , WD2_SW_BUILD_MINUTE_OFS              , "Minute of the software build" ],
  [ "SW_BUILD_SECOND"               , WD2_SW_BUILD_SECOND_REG               , WD2_SW_BUILD_SECOND_MASK               , WD2_SW_BUILD_SECOND_OFS              , "Second of the software build" ],
  [ "FW_GIT_HASH_TAG"               , WD2_FW_GIT_HASH_TAG_REG               , WD2_FW_GIT_HASH_TAG_MASK               , WD2_FW_GIT_HASH_TAG_OFS              , "Hash tag of the firmware commit in the GIT repository" ],
  [ "SW_GIT_HASH_TAG"               , WD2_SW_GIT_HASH_TAG_REG               , WD2_SW_GIT_HASH_TAG_MASK               , WD2_SW_GIT_HASH_TAG_OFS              , "Hash tag of the software commit in the GIT repository" ],
  [ "PROTOCOL_VERSION"              , WD2_PROTOCOL_VERSION_REG              , WD2_PROTOCOL_VERSION_MASK              , WD2_PROTOCOL_VERSION_OFS             , "Version of the WaveDream2 protocol" ],
  [ "LED_STATE"                     , WD2_LED_STATE_REG                     , WD2_LED_STATE_MASK                     , WD2_LED_STATE_OFS                    , "State of the front panel LED (on-beat-color RGB, off-beat-color RGB)" ],
  [ "SERIAL_NUMBER"                 , WD2_SERIAL_NUMBER_REG                 , WD2_SERIAL_NUMBER_MASK                 , WD2_SERIAL_NUMBER_OFS                , "Serial Number of the WD2 Board (Board ID)" ],
  [ "TEMPERATURE"                   , WD2_TEMPERATURE_REG                   , WD2_TEMPERATURE_MASK                   , WD2_TEMPERATURE_OFS                  , "temperature in 0.0625 deg. C units" ],
  [ "OVERTEMP"                      , WD2_OVERTEMP_REG                      , WD2_OVERTEMP_MASK                      , WD2_OVERTEMP_OFS                     , "Overtemperature from external sensor" ],
  [ "EXT_CLK_ACTIVE"                , WD2_EXT_CLK_ACTIVE_REG                , WD2_EXT_CLK_ACTIVE_MASK                , WD2_EXT_CLK_ACTIVE_OFS               , "Configuration for external clock for DAQ completed" ],
  [ "DAQ_CLK_DEF_PHASE_OK"          , WD2_DAQ_CLK_DEF_PHASE_OK_REG          , WD2_DAQ_CLK_DEF_PHASE_OK_MASK          , WD2_DAQ_CLK_DEF_PHASE_OK_OFS         , "DAQ clock default phase setting is valid" ],
  [ "DAQ_CLK_DEF_PHASE_CHKD"        , WD2_DAQ_CLK_DEF_PHASE_CHKD_REG        , WD2_DAQ_CLK_DEF_PHASE_CHKD_MASK        , WD2_DAQ_CLK_DEF_PHASE_CHKD_OFS       , "DAQ clock default phase setting is checked" ],
  [ "DRS_CONFIG_DONE"               , WD2_DRS_CONFIG_DONE_REG               , WD2_DRS_CONFIG_DONE_MASK               , WD2_DRS_CONFIG_DONE_OFS              , "DRS configuration done" ],
  [ "BOARD_SEL"                     , WD2_BOARD_SEL_REG                     , WD2_BOARD_SEL_MASK                     , WD2_BOARD_SEL_OFS                    , "Board select from backplane (inverted = high active)" ],
  [ "SERIAL_BUSY"                   , WD2_SERIAL_BUSY_REG                   , WD2_SERIAL_BUSY_MASK                   , WD2_SERIAL_BUSY_OFS                  , "\"1\" during serial activity like FLASH read/write" ],
  [ "PACKAGER_BUSY"                 , WD2_PACKAGER_BUSY_REG                 , WD2_PACKAGER_BUSY_MASK                 , WD2_PACKAGER_BUSY_OFS                , "\"1\" while packager is not ready to process data (buffers are full or ethernet destination not configured)" ],
  [ "DRS_CTRL_BUSY"                 , WD2_DRS_CTRL_BUSY_REG                 , WD2_DRS_CTRL_BUSY_MASK                 , WD2_DRS_CTRL_BUSY_OFS                , "\"1\" while domino wave running or readout in progress" ],
  [ "SYS_BUSY"                      , WD2_SYS_BUSY_REG                      , WD2_SYS_BUSY_MASK                      , WD2_SYS_BUSY_OFS                     , "Inverted busy signal from backplane (high active, not available until hardware revision G)" ],
  [ "HV_BOARD_PLUGGED"              , WD2_HV_BOARD_PLUGGED_REG              , WD2_HV_BOARD_PLUGGED_MASK              , WD2_HV_BOARD_PLUGGED_OFS             , "HV board is currently plugged (1) or unplugged (0)" ],
  [ "BACKPLANE_PLUGGED"             , WD2_BACKPLANE_PLUGGED_REG             , WD2_BACKPLANE_PLUGGED_MASK             , WD2_BACKPLANE_PLUGGED_OFS            , "Backplane is currently plugged (1) or unplugged (0)" ],
  [ "SYS_DCM_LOCK"                  , WD2_SYS_DCM_LOCK_REG                  , WD2_SYS_DCM_LOCK_MASK                  , WD2_SYS_DCM_LOCK_OFS                 , "Lock of system DCM (FPGA internal)" ],
  [ "DAQ_PLL_LOCK"                  , WD2_DAQ_PLL_LOCK_REG                  , WD2_DAQ_PLL_LOCK_MASK                  , WD2_DAQ_PLL_LOCK_OFS                 , "Lock of DAQ PLL (FPGA internal)" ],
  [ "OSERDES_PLL_LOCK_DCB"          , WD2_OSERDES_PLL_LOCK_DCB_REG          , WD2_OSERDES_PLL_LOCK_DCB_MASK          , WD2_OSERDES_PLL_LOCK_DCB_OFS         , "Lock of PLL for OSERDES to DCB (FPGA internal)" ],
  [ "OSERDES_PLL_LOCK_TCB"          , WD2_OSERDES_PLL_LOCK_TCB_REG          , WD2_OSERDES_PLL_LOCK_TCB_MASK          , WD2_OSERDES_PLL_LOCK_TCB_OFS         , "Lock of PLL for OSERDES to TCB (FPGA internal)" ],
  [ "ISERDES_PLL_LOCK_0"            , WD2_ISERDES_PLL_LOCK_0_REG            , WD2_ISERDES_PLL_LOCK_0_MASK            , WD2_ISERDES_PLL_LOCK_0_OFS           , "Lock of PLL for ISERDES from ADC 0 (A) (FPGA internal)" ],
  [ "ISERDES_PLL_LOCK_1"            , WD2_ISERDES_PLL_LOCK_1_REG            , WD2_ISERDES_PLL_LOCK_1_MASK            , WD2_ISERDES_PLL_LOCK_1_OFS           , "Lock of PLL for ISERDES from ADC 1 (B) (FPGA internal)" ],
  [ "DRS_PLL_LOCK_0"                , WD2_DRS_PLL_LOCK_0_REG                , WD2_DRS_PLL_LOCK_0_MASK                , WD2_DRS_PLL_LOCK_0_OFS               , "PLL lock signal of DRS Channel 0 (A) (external)" ],
  [ "DRS_PLL_LOCK_1"                , WD2_DRS_PLL_LOCK_1_REG                , WD2_DRS_PLL_LOCK_1_MASK                , WD2_DRS_PLL_LOCK_1_OFS               , "PLL lock signal of DRS Channel 1 (B) (external)" ],
  [ "LMK_PLL_LOCK"                  , WD2_LMK_PLL_LOCK_REG                  , WD2_LMK_PLL_LOCK_MASK                  , WD2_LMK_PLL_LOCK_OFS                 , "PLL lock signal of LMK (external)" ],
  [ "DRS_STOP_CELL_0"               , WD2_DRS_STOP_CELL_0_REG               , WD2_DRS_STOP_CELL_0_MASK               , WD2_DRS_STOP_CELL_0_OFS              , "Stop position of DRS Channel 0 (A)" ],
  [ "DRS_STOP_CELL_1"               , WD2_DRS_STOP_CELL_1_REG               , WD2_DRS_STOP_CELL_1_MASK               , WD2_DRS_STOP_CELL_1_OFS              , "Stop position of DRS Channel 1 (B)" ],
  [ "DRS_STOP_WSR_0"                , WD2_DRS_STOP_WSR_0_REG                , WD2_DRS_STOP_WSR_0_MASK                , WD2_DRS_STOP_WSR_0_OFS               , "WSR contents after stop of DRS Channel 0 (A)" ],
  [ "DRS_STOP_WSR_1"                , WD2_DRS_STOP_WSR_1_REG                , WD2_DRS_STOP_WSR_1_MASK                , WD2_DRS_STOP_WSR_1_OFS               , "WSR contents after stop of DRS Channel 1 (B)" ],
  [ "DRS_SAMPLE_FREQ"               , WD2_DRS_SAMPLE_FREQ_REG               , WD2_DRS_SAMPLE_FREQ_MASK               , WD2_DRS_SAMPLE_FREQ_OFS              , "DRS Sampling frequency in kHz" ],
  [ "ADC_SAMPLE_FREQ"               , WD2_ADC_SAMPLE_FREQ_REG               , WD2_ADC_SAMPLE_FREQ_MASK               , WD2_ADC_SAMPLE_FREQ_OFS              , "ADC Sampling Frequency in kHz" ],
  [ "TDC_SAMPLE_FREQ"               , WD2_TDC_SAMPLE_FREQ_REG               , WD2_TDC_SAMPLE_FREQ_MASK               , WD2_TDC_SAMPLE_FREQ_OFS              , "TDC Sampling Frequency in kHz" ],
  [ "HV_VER"                        , WD2_HV_VER_REG                        , WD2_HV_VER_MASK                        , WD2_HV_VER_OFS                       , "HV board version (16bit Voltage in V, 16bit Current in mA)" ],
  [ "HV_I_MEAS_0"                   , WD2_HV_I_MEAS_0_REG                   , WD2_HV_I_MEAS_0_MASK                   , WD2_HV_I_MEAS_0_OFS                  , "Float value (i_meas)" ],
  [ "HV_I_MEAS_1"                   , WD2_HV_I_MEAS_1_REG                   , WD2_HV_I_MEAS_1_MASK                   , WD2_HV_I_MEAS_1_OFS                  , "Float value (i_meas)" ],
  [ "HV_I_MEAS_2"                   , WD2_HV_I_MEAS_2_REG                   , WD2_HV_I_MEAS_2_MASK                   , WD2_HV_I_MEAS_2_OFS                  , "Float value (i_meas)" ],
  [ "HV_I_MEAS_3"                   , WD2_HV_I_MEAS_3_REG                   , WD2_HV_I_MEAS_3_MASK                   , WD2_HV_I_MEAS_3_OFS                  , "Float value (i_meas)" ],
  [ "HV_I_MEAS_4"                   , WD2_HV_I_MEAS_4_REG                   , WD2_HV_I_MEAS_4_MASK                   , WD2_HV_I_MEAS_4_OFS                  , "Float value (i_meas)" ],
  [ "HV_I_MEAS_5"                   , WD2_HV_I_MEAS_5_REG                   , WD2_HV_I_MEAS_5_MASK                   , WD2_HV_I_MEAS_5_OFS                  , "Float value (i_meas)" ],
  [ "HV_I_MEAS_6"                   , WD2_HV_I_MEAS_6_REG                   , WD2_HV_I_MEAS_6_MASK                   , WD2_HV_I_MEAS_6_OFS                  , "Float value (i_meas)" ],
  [ "HV_I_MEAS_7"                   , WD2_HV_I_MEAS_7_REG                   , WD2_HV_I_MEAS_7_MASK                   , WD2_HV_I_MEAS_7_OFS                  , "Float value (i_meas)" ],
  [ "HV_I_MEAS_8"                   , WD2_HV_I_MEAS_8_REG                   , WD2_HV_I_MEAS_8_MASK                   , WD2_HV_I_MEAS_8_OFS                  , "Float value (i_meas)" ],
  [ "HV_I_MEAS_9"                   , WD2_HV_I_MEAS_9_REG                   , WD2_HV_I_MEAS_9_MASK                   , WD2_HV_I_MEAS_9_OFS                  , "Float value (i_meas)" ],
  [ "HV_I_MEAS_10"                  , WD2_HV_I_MEAS_10_REG                  , WD2_HV_I_MEAS_10_MASK                  , WD2_HV_I_MEAS_10_OFS                 , "Float value (i_meas)" ],
  [ "HV_I_MEAS_11"                  , WD2_HV_I_MEAS_11_REG                  , WD2_HV_I_MEAS_11_MASK                  , WD2_HV_I_MEAS_11_OFS                 , "Float value (i_meas)" ],
  [ "HV_I_MEAS_12"                  , WD2_HV_I_MEAS_12_REG                  , WD2_HV_I_MEAS_12_MASK                  , WD2_HV_I_MEAS_12_OFS                 , "Float value (i_meas)" ],
  [ "HV_I_MEAS_13"                  , WD2_HV_I_MEAS_13_REG                  , WD2_HV_I_MEAS_13_MASK                  , WD2_HV_I_MEAS_13_OFS                 , "Float value (i_meas)" ],
  [ "HV_I_MEAS_14"                  , WD2_HV_I_MEAS_14_REG                  , WD2_HV_I_MEAS_14_MASK                  , WD2_HV_I_MEAS_14_OFS                 , "Float value (i_meas)" ],
  [ "HV_I_MEAS_15"                  , WD2_HV_I_MEAS_15_REG                  , WD2_HV_I_MEAS_15_MASK                  , WD2_HV_I_MEAS_15_OFS                 , "Float value (i_meas)" ],
  [ "HV_U_BASE_MEAS"                , WD2_HV_U_BASE_MEAS_REG                , WD2_HV_U_BASE_MEAS_MASK                , WD2_HV_U_BASE_MEAS_OFS               , "Float value (ub_meas)" ],
  [ "HV_TEMP_0"                     , WD2_HV_TEMP_0_REG                     , WD2_HV_TEMP_0_MASK                     , WD2_HV_TEMP_0_OFS                    , "Float value (temp)" ],
  [ "HV_TEMP_1"                     , WD2_HV_TEMP_1_REG                     , WD2_HV_TEMP_1_MASK                     , WD2_HV_TEMP_1_OFS                    , "Float value (temp)" ],
  [ "HV_TEMP_2"                     , WD2_HV_TEMP_2_REG                     , WD2_HV_TEMP_2_MASK                     , WD2_HV_TEMP_2_OFS                    , "Float value (temp)" ],
  [ "HV_TEMP_3"                     , WD2_HV_TEMP_3_REG                     , WD2_HV_TEMP_3_MASK                     , WD2_HV_TEMP_3_OFS                    , "Float value (temp)" ],
  [ "SCALER_0"                      , WD2_SCALER_0_REG                      , WD2_SCALER_0_MASK                      , WD2_SCALER_0_OFS                     , "Count rate value of channel 0 (MSBs are latched upon read of LSB register)" ],
  [ "SCALER_1"                      , WD2_SCALER_1_REG                      , WD2_SCALER_1_MASK                      , WD2_SCALER_1_OFS                     , "Count rate value of channel 1 (MSBs are latched upon read of LSB register)" ],
  [ "SCALER_2"                      , WD2_SCALER_2_REG                      , WD2_SCALER_2_MASK                      , WD2_SCALER_2_OFS                     , "Count rate value of channel 2 (MSBs are latched upon read of LSB register)" ],
  [ "SCALER_3"                      , WD2_SCALER_3_REG                      , WD2_SCALER_3_MASK                      , WD2_SCALER_3_OFS                     , "Count rate value of channel 3 (MSBs are latched upon read of LSB register)" ],
  [ "SCALER_4"                      , WD2_SCALER_4_REG                      , WD2_SCALER_4_MASK                      , WD2_SCALER_4_OFS                     , "Count rate value of channel 4 (MSBs are latched upon read of LSB register)" ],
  [ "SCALER_5"                      , WD2_SCALER_5_REG                      , WD2_SCALER_5_MASK                      , WD2_SCALER_5_OFS                     , "Count rate value of channel 5 (MSBs are latched upon read of LSB register)" ],
  [ "SCALER_6"                      , WD2_SCALER_6_REG                      , WD2_SCALER_6_MASK                      , WD2_SCALER_6_OFS                     , "Count rate value of channel 6 (MSBs are latched upon read of LSB register)" ],
  [ "SCALER_7"                      , WD2_SCALER_7_REG                      , WD2_SCALER_7_MASK                      , WD2_SCALER_7_OFS                     , "Count rate value of channel 7 (MSBs are latched upon read of LSB register)" ],
  [ "SCALER_8"                      , WD2_SCALER_8_REG                      , WD2_SCALER_8_MASK                      , WD2_SCALER_8_OFS                     , "Count rate value of channel 8 (MSBs are latched upon read of LSB register)" ],
  [ "SCALER_9"                      , WD2_SCALER_9_REG                      , WD2_SCALER_9_MASK                      , WD2_SCALER_9_OFS                     , "Count rate value of channel 9 (MSBs are latched upon read of LSB register)" ],
  [ "SCALER_10"                     , WD2_SCALER_10_REG                     , WD2_SCALER_10_MASK                     , WD2_SCALER_10_OFS                    , "Count rate value of channel 10 (MSBs are latched upon read of LSB register)" ],
  [ "SCALER_11"                     , WD2_SCALER_11_REG                     , WD2_SCALER_11_MASK                     , WD2_SCALER_11_OFS                    , "Count rate value of channel 11 (MSBs are latched upon read of LSB register)" ],
  [ "SCALER_12"                     , WD2_SCALER_12_REG                     , WD2_SCALER_12_MASK                     , WD2_SCALER_12_OFS                    , "Count rate value of channel 12 (MSBs are latched upon read of LSB register)" ],
  [ "SCALER_13"                     , WD2_SCALER_13_REG                     , WD2_SCALER_13_MASK                     , WD2_SCALER_13_OFS                    , "Count rate value of channel 13 (MSBs are latched upon read of LSB register)" ],
  [ "SCALER_14"                     , WD2_SCALER_14_REG                     , WD2_SCALER_14_MASK                     , WD2_SCALER_14_OFS                    , "Count rate value of channel 14 (MSBs are latched upon read of LSB register)" ],
  [ "SCALER_15"                     , WD2_SCALER_15_REG                     , WD2_SCALER_15_MASK                     , WD2_SCALER_15_OFS                    , "Count rate value of channel 15 (MSBs are latched upon read of LSB register)" ],
  [ "SCALER_PTRN_TRG"               , WD2_SCALER_PTRN_TRG_REG               , WD2_SCALER_PTRN_TRG_MASK               , WD2_SCALER_PTRN_TRG_OFS              , "Count rate for pattern trigger signal" ],
  [ "SCALER_EXT_TRG"                , WD2_SCALER_EXT_TRG_REG                , WD2_SCALER_EXT_TRG_MASK                , WD2_SCALER_EXT_TRG_OFS               , "Count rate for trigger signal" ],
  [ "SCALER_EXT_CLK"                , WD2_SCALER_EXT_CLK_REG                , WD2_SCALER_EXT_CLK_MASK                , WD2_SCALER_EXT_CLK_OFS               , "Count rate for external clock input (GLOB_CLK)" ],
  [ "SCALER_TIME_STAMP_LSB"         , WD2_SCALER_TIME_STAMP_LSB_REG         , WD2_SCALER_TIME_STAMP_LSB_MASK         , WD2_SCALER_TIME_STAMP_LSB_OFS        , "LSBs of 64bit scaler time stamp (MSBs are latched upon read of LSB register)" ],
  [ "SCALER_TIME_STAMP_MSB"         , WD2_SCALER_TIME_STAMP_MSB_REG         , WD2_SCALER_TIME_STAMP_MSB_MASK         , WD2_SCALER_TIME_STAMP_MSB_OFS        , "MSBs of 64bit scaler time stamp (latched upon read of LSB register)" ],
  [ "TIME_LSB"                      , WD2_TIME_LSB_REG                      , WD2_TIME_LSB_MASK                      , WD2_TIME_LSB_OFS                     , "LSBs of 64bit system time counter (MSBs are latched upon read of LSB register)" ],
  [ "TIME_MSB"                      , WD2_TIME_MSB_REG                      , WD2_TIME_MSB_MASK                      , WD2_TIME_MSB_OFS                     , "MSBs of 64bit system time counter (latched upon read of LSB register)" ],
  [ "COMP_CH_STAT"                  , WD2_COMP_CH_STAT_REG                  , WD2_COMP_CH_STAT_MASK                  , WD2_COMP_CH_STAT_OFS                 , "Status of the comparator inputs" ],
  [ "EVENT_TX_RATE"                 , WD2_EVENT_TX_RATE_REG                 , WD2_EVENT_TX_RATE_MASK                 , WD2_EVENT_TX_RATE_OFS                , "Number of events transmitted per second" ],
  [ "EVENT_NUMBER"                  , WD2_EVENT_NUMBER_REG                  , WD2_EVENT_NUMBER_MASK                  , WD2_EVENT_NUMBER_OFS                 , "Number of latest event" ],
  [ "TRB_FLAG_NEW"                  , WD2_TRB_FLAG_NEW_REG                  , WD2_TRB_FLAG_NEW_MASK                  , WD2_TRB_FLAG_NEW_OFS                 , "Flag signalling that the current trigger information belongs to the latest trigger received" ],
  [ "TRB_FLAG_PARITY_ERROR"         , WD2_TRB_FLAG_PARITY_ERROR_REG         , WD2_TRB_FLAG_PARITY_ERROR_MASK         , WD2_TRB_FLAG_PARITY_ERROR_OFS        , "Parity error flag of the current trigger information" ],
  [ "TRB_PARITY_ERROR_COUNT"        , WD2_TRB_PARITY_ERROR_COUNT_REG        , WD2_TRB_PARITY_ERROR_COUNT_MASK        , WD2_TRB_PARITY_ERROR_COUNT_OFS       , "Parity error count of the serial transmission" ],
  [ "TRB_INFO_LSB"                  , WD2_TRB_INFO_LSB_REG                  , WD2_TRB_INFO_LSB_MASK                  , WD2_TRB_INFO_LSB_OFS                 , "Trigger information LSBs" ],
  [ "TRB_INFO_MSB"                  , WD2_TRB_INFO_MSB_REG                  , WD2_TRB_INFO_MSB_MASK                  , WD2_TRB_INFO_MSB_OFS                 , "Trigger information MSBs" ],
  [ "ADV_TRG_TRIG_CELL"             , WD2_ADV_TRG_TRIG_CELL_REG             , WD2_ADV_TRG_TRIG_CELL_MASK             , WD2_ADV_TRG_TRIG_CELL_OFS            , "Advanced trigger cell register" ],
  [ "ADV_TRG_STAT_1"                , WD2_ADV_TRG_STAT_1_REG                , WD2_ADV_TRG_STAT_1_MASK                , WD2_ADV_TRG_STAT_1_OFS               , "Advanced trigger status register 1" ],
  [ "ADV_TRG_STAT_2"                , WD2_ADV_TRG_STAT_2_REG                , WD2_ADV_TRG_STAT_2_MASK                , WD2_ADV_TRG_STAT_2_OFS               , "Advanced trigger status register 2" ],
  [ "ADV_TRG_STAT_3"                , WD2_ADV_TRG_STAT_3_REG                , WD2_ADV_TRG_STAT_3_MASK                , WD2_ADV_TRG_STAT_3_OFS               , "Advanced trigger status register 3" ],
  [ "ADV_TRG_STAT_4"                , WD2_ADV_TRG_STAT_4_REG                , WD2_ADV_TRG_STAT_4_MASK                , WD2_ADV_TRG_STAT_4_OFS               , "Advanced trigger status register 4" ],
  [ "MAX_DRS_ADC_PKT_SAMPLES"       , WD2_MAX_DRS_ADC_PKT_SAMPLES_REG       , WD2_MAX_DRS_ADC_PKT_SAMPLES_MASK       , WD2_MAX_DRS_ADC_PKT_SAMPLES_OFS      , "Maximum number of DRS/ADC samples per packet" ],
  [ "MAX_TDC_PKT_SAMPLES"           , WD2_MAX_TDC_PKT_SAMPLES_REG           , WD2_MAX_TDC_PKT_SAMPLES_MASK           , WD2_MAX_TDC_PKT_SAMPLES_OFS          , "Maximum number of TDC samples per packet" ],
  [ "MAX_TRG_PKT_SAMPLES"           , WD2_MAX_TRG_PKT_SAMPLES_REG           , WD2_MAX_TRG_PKT_SAMPLES_MASK           , WD2_MAX_TRG_PKT_SAMPLES_OFS          , "Maximum number of advanced trigger output samples per packet" ],
  [ "MAX_SCL_PKT_SAMPLES"           , WD2_MAX_SCL_PKT_SAMPLES_REG           , WD2_MAX_SCL_PKT_SAMPLES_MASK           , WD2_MAX_SCL_PKT_SAMPLES_OFS          , "Maximum number of scaler values per packet" ],
  [ "TRIGGER_DAQ_CLK_CAL_MOD"       , WD2_TRIGGER_DAQ_CLK_CAL_MOD_REG       , WD2_TRIGGER_DAQ_CLK_CAL_MOD_MASK       , WD2_TRIGGER_DAQ_CLK_CAL_MOD_OFS      , "Trigger DAQ clock calibration modified flag" ],
  [ "ADC_RST_MOD"                   , WD2_ADC_RST_MOD_REG                   , WD2_ADC_RST_MOD_MASK                   , WD2_ADC_RST_MOD_OFS                  , "ADC reset modified flag" ],
  [ "CLK_SEL_AND_DRS_CLK_DIV_MOD"   , WD2_CLK_SEL_AND_DRS_CLK_DIV_MOD_REG   , WD2_CLK_SEL_AND_DRS_CLK_DIV_MOD_MASK   , WD2_CLK_SEL_AND_DRS_CLK_DIV_MOD_OFS  , "DAQ clock select and DRS clock divider modified flags" ],
  [ "EXT_CLK_FREQ_MOD"              , WD2_EXT_CLK_FREQ_MOD_REG              , WD2_EXT_CLK_FREQ_MOD_MASK              , WD2_EXT_CLK_FREQ_MOD_OFS             , "External clock frequency modified flags" ],
  [ "LOCAL_CLK_FREQ_MOD"            , WD2_LOCAL_CLK_FREQ_MOD_REG            , WD2_LOCAL_CLK_FREQ_MOD_MASK            , WD2_LOCAL_CLK_FREQ_MOD_OFS           , "Local clock frequency modified flags" ],
  [ "DRS_CTRL_MOD"                  , WD2_DRS_CTRL_MOD_REG                  , WD2_DRS_CTRL_MOD_MASK                  , WD2_DRS_CTRL_MOD_OFS                 , "DRS control bits modified flags" ],
  [ "DRS_WSR_MOD"                   , WD2_DRS_WSR_MOD_REG                   , WD2_DRS_WSR_MOD_MASK                   , WD2_DRS_WSR_MOD_OFS                  , "DRS write shift register modified flags" ],
  [ "DRS_WCR_MOD"                   , WD2_DRS_WCR_MOD_REG                   , WD2_DRS_WCR_MOD_MASK                   , WD2_DRS_WCR_MOD_OFS                  , "DRS write control register modified flags" ],
  [ "COM_PLD_SIZE_MOD"              , WD2_COM_PLD_SIZE_MOD_REG              , WD2_COM_PLD_SIZE_MOD_MASK              , WD2_COM_PLD_SIZE_MOD_OFS             , "Maximum packet payload size modified flag" ],
  [ "ADC_SAMPLE_DIV_MOD"            , WD2_ADC_SAMPLE_DIV_MOD_REG            , WD2_ADC_SAMPLE_DIV_MOD_MASK            , WD2_ADC_SAMPLE_DIV_MOD_OFS           , "ADC downsampling divider modified flags" ],
  [ "DAC0_A_MOD"                    , WD2_DAC0_A_MOD_REG                    , WD2_DAC0_A_MOD_MASK                    , WD2_DAC0_A_MOD_OFS                   , "DAC channel a modified flags" ],
  [ "DAC0_B_MOD"                    , WD2_DAC0_B_MOD_REG                    , WD2_DAC0_B_MOD_MASK                    , WD2_DAC0_B_MOD_OFS                   , "DAC channel b modified flags" ],
  [ "DAC0_C_MOD"                    , WD2_DAC0_C_MOD_REG                    , WD2_DAC0_C_MOD_MASK                    , WD2_DAC0_C_MOD_OFS                   , "DAC channel c modified flags" ],
  [ "DAC0_D_MOD"                    , WD2_DAC0_D_MOD_REG                    , WD2_DAC0_D_MOD_MASK                    , WD2_DAC0_D_MOD_OFS                   , "DAC channel d modified flags" ],
  [ "DAC0_E_MOD"                    , WD2_DAC0_E_MOD_REG                    , WD2_DAC0_E_MOD_MASK                    , WD2_DAC0_E_MOD_OFS                   , "DAC channel e modified flags" ],
  [ "DAC0_F_MOD"                    , WD2_DAC0_F_MOD_REG                    , WD2_DAC0_F_MOD_MASK                    , WD2_DAC0_F_MOD_OFS                   , "DAC channel f modified flags" ],
  [ "DAC0_G_MOD"                    , WD2_DAC0_G_MOD_REG                    , WD2_DAC0_G_MOD_MASK                    , WD2_DAC0_G_MOD_OFS                   , "DAC channel g modified flags" ],
  [ "DAC0_H_MOD"                    , WD2_DAC0_H_MOD_REG                    , WD2_DAC0_H_MOD_MASK                    , WD2_DAC0_H_MOD_OFS                   , "DAC channel h modified flags" ],
  [ "DAC1_A_MOD"                    , WD2_DAC1_A_MOD_REG                    , WD2_DAC1_A_MOD_MASK                    , WD2_DAC1_A_MOD_OFS                   , "DAC channel a modified flags" ],
  [ "DAC1_B_MOD"                    , WD2_DAC1_B_MOD_REG                    , WD2_DAC1_B_MOD_MASK                    , WD2_DAC1_B_MOD_OFS                   , "DAC channel b modified flags" ],
  [ "DAC1_C_MOD"                    , WD2_DAC1_C_MOD_REG                    , WD2_DAC1_C_MOD_MASK                    , WD2_DAC1_C_MOD_OFS                   , "DAC channel c modified flags" ],
  [ "DAC1_D_MOD"                    , WD2_DAC1_D_MOD_REG                    , WD2_DAC1_D_MOD_MASK                    , WD2_DAC1_D_MOD_OFS                   , "DAC channel d modified flags" ],
  [ "DAC1_E_MOD"                    , WD2_DAC1_E_MOD_REG                    , WD2_DAC1_E_MOD_MASK                    , WD2_DAC1_E_MOD_OFS                   , "DAC channel e modified flags" ],
  [ "DAC1_F_MOD"                    , WD2_DAC1_F_MOD_REG                    , WD2_DAC1_F_MOD_MASK                    , WD2_DAC1_F_MOD_OFS                   , "DAC channel f modified flags" ],
  [ "DAC1_G_MOD"                    , WD2_DAC1_G_MOD_REG                    , WD2_DAC1_G_MOD_MASK                    , WD2_DAC1_G_MOD_OFS                   , "DAC channel g modified flags" ],
  [ "DAC1_H_MOD"                    , WD2_DAC1_H_MOD_REG                    , WD2_DAC1_H_MOD_MASK                    , WD2_DAC1_H_MOD_OFS                   , "DAC channel h modified flags" ],
  [ "DAC2_A_MOD"                    , WD2_DAC2_A_MOD_REG                    , WD2_DAC2_A_MOD_MASK                    , WD2_DAC2_A_MOD_OFS                   , "DAC channel a modified flags" ],
  [ "DAC2_B_MOD"                    , WD2_DAC2_B_MOD_REG                    , WD2_DAC2_B_MOD_MASK                    , WD2_DAC2_B_MOD_OFS                   , "DAC channel b modified flags" ],
  [ "DAC2_C_MOD"                    , WD2_DAC2_C_MOD_REG                    , WD2_DAC2_C_MOD_MASK                    , WD2_DAC2_C_MOD_OFS                   , "DAC channel c modified flags" ],
  [ "DAC2_D_MOD"                    , WD2_DAC2_D_MOD_REG                    , WD2_DAC2_D_MOD_MASK                    , WD2_DAC2_D_MOD_OFS                   , "DAC channel d modified flags" ],
  [ "DAC2_E_MOD"                    , WD2_DAC2_E_MOD_REG                    , WD2_DAC2_E_MOD_MASK                    , WD2_DAC2_E_MOD_OFS                   , "DAC channel e modified flags" ],
  [ "DAC2_F_MOD"                    , WD2_DAC2_F_MOD_REG                    , WD2_DAC2_F_MOD_MASK                    , WD2_DAC2_F_MOD_OFS                   , "DAC channel f modified flags" ],
  [ "DAC2_G_MOD"                    , WD2_DAC2_G_MOD_REG                    , WD2_DAC2_G_MOD_MASK                    , WD2_DAC2_G_MOD_OFS                   , "DAC channel g modified flags" ],
  [ "DAC2_H_MOD"                    , WD2_DAC2_H_MOD_REG                    , WD2_DAC2_H_MOD_MASK                    , WD2_DAC2_H_MOD_OFS                   , "DAC channel h modified flags" ],
  [ "FE_0_MOD"                      , WD2_FE_0_MOD_REG                      , WD2_FE_0_MOD_MASK                      , WD2_FE_0_MOD_OFS                     , "Frontend channel 0 register modified flags" ],
  [ "FE_1_MOD"                      , WD2_FE_1_MOD_REG                      , WD2_FE_1_MOD_MASK                      , WD2_FE_1_MOD_OFS                     , "Frontend channel 1 register modified flags" ],
  [ "FE_2_MOD"                      , WD2_FE_2_MOD_REG                      , WD2_FE_2_MOD_MASK                      , WD2_FE_2_MOD_OFS                     , "Frontend channel 2 register modified flags" ],
  [ "FE_3_MOD"                      , WD2_FE_3_MOD_REG                      , WD2_FE_3_MOD_MASK                      , WD2_FE_3_MOD_OFS                     , "Frontend channel 3 register modified flags" ],
  [ "FE_4_MOD"                      , WD2_FE_4_MOD_REG                      , WD2_FE_4_MOD_MASK                      , WD2_FE_4_MOD_OFS                     , "Frontend channel 4 register modified flags" ],
  [ "FE_5_MOD"                      , WD2_FE_5_MOD_REG                      , WD2_FE_5_MOD_MASK                      , WD2_FE_5_MOD_OFS                     , "Frontend channel 5 register modified flags" ],
  [ "FE_6_MOD"                      , WD2_FE_6_MOD_REG                      , WD2_FE_6_MOD_MASK                      , WD2_FE_6_MOD_OFS                     , "Frontend channel 6 register modified flags" ],
  [ "FE_7_MOD"                      , WD2_FE_7_MOD_REG                      , WD2_FE_7_MOD_MASK                      , WD2_FE_7_MOD_OFS                     , "Frontend channel 7 register modified flags" ],
  [ "FE_8_MOD"                      , WD2_FE_8_MOD_REG                      , WD2_FE_8_MOD_MASK                      , WD2_FE_8_MOD_OFS                     , "Frontend channel 8 register modified flags" ],
  [ "FE_9_MOD"                      , WD2_FE_9_MOD_REG                      , WD2_FE_9_MOD_MASK                      , WD2_FE_9_MOD_OFS                     , "Frontend channel 9 register modified flags" ],
  [ "FE_10_MOD"                     , WD2_FE_10_MOD_REG                     , WD2_FE_10_MOD_MASK                     , WD2_FE_10_MOD_OFS                    , "Frontend channel 10 register modified flags" ],
  [ "FE_11_MOD"                     , WD2_FE_11_MOD_REG                     , WD2_FE_11_MOD_MASK                     , WD2_FE_11_MOD_OFS                    , "Frontend channel 11 register modified flags" ],
  [ "FE_12_MOD"                     , WD2_FE_12_MOD_REG                     , WD2_FE_12_MOD_MASK                     , WD2_FE_12_MOD_OFS                    , "Frontend channel 12 register modified flags" ],
  [ "FE_13_MOD"                     , WD2_FE_13_MOD_REG                     , WD2_FE_13_MOD_MASK                     , WD2_FE_13_MOD_OFS                    , "Frontend channel 13 register modified flags" ],
  [ "FE_14_MOD"                     , WD2_FE_14_MOD_REG                     , WD2_FE_14_MOD_MASK                     , WD2_FE_14_MOD_OFS                    , "Frontend channel 14 register modified flags" ],
  [ "FE_15_MOD"                     , WD2_FE_15_MOD_REG                     , WD2_FE_15_MOD_MASK                     , WD2_FE_15_MOD_OFS                    , "Frontend channel 15 register modified flags" ],
  [ "HV_U_TARGET_0_MOD"             , WD2_HV_U_TARGET_0_MOD_REG             , WD2_HV_U_TARGET_0_MOD_MASK             , WD2_HV_U_TARGET_0_MOD_OFS            , "Target high voltage channel 0 register modified flags" ],
  [ "HV_U_TARGET_1_MOD"             , WD2_HV_U_TARGET_1_MOD_REG             , WD2_HV_U_TARGET_1_MOD_MASK             , WD2_HV_U_TARGET_1_MOD_OFS            , "Target high voltage channel 1 register modified flags" ],
  [ "HV_U_TARGET_2_MOD"             , WD2_HV_U_TARGET_2_MOD_REG             , WD2_HV_U_TARGET_2_MOD_MASK             , WD2_HV_U_TARGET_2_MOD_OFS            , "Target high voltage channel 2 register modified flags" ],
  [ "HV_U_TARGET_3_MOD"             , WD2_HV_U_TARGET_3_MOD_REG             , WD2_HV_U_TARGET_3_MOD_MASK             , WD2_HV_U_TARGET_3_MOD_OFS            , "Target high voltage channel 3 register modified flags" ],
  [ "HV_U_TARGET_4_MOD"             , WD2_HV_U_TARGET_4_MOD_REG             , WD2_HV_U_TARGET_4_MOD_MASK             , WD2_HV_U_TARGET_4_MOD_OFS            , "Target high voltage channel 4 register modified flags" ],
  [ "HV_U_TARGET_5_MOD"             , WD2_HV_U_TARGET_5_MOD_REG             , WD2_HV_U_TARGET_5_MOD_MASK             , WD2_HV_U_TARGET_5_MOD_OFS            , "Target high voltage channel 5 register modified flags" ],
  [ "HV_U_TARGET_6_MOD"             , WD2_HV_U_TARGET_6_MOD_REG             , WD2_HV_U_TARGET_6_MOD_MASK             , WD2_HV_U_TARGET_6_MOD_OFS            , "Target high voltage channel 6 register modified flags" ],
  [ "HV_U_TARGET_7_MOD"             , WD2_HV_U_TARGET_7_MOD_REG             , WD2_HV_U_TARGET_7_MOD_MASK             , WD2_HV_U_TARGET_7_MOD_OFS            , "Target high voltage channel 7 register modified flags" ],
  [ "HV_U_TARGET_8_MOD"             , WD2_HV_U_TARGET_8_MOD_REG             , WD2_HV_U_TARGET_8_MOD_MASK             , WD2_HV_U_TARGET_8_MOD_OFS            , "Target high voltage channel 8 register modified flags" ],
  [ "HV_U_TARGET_9_MOD"             , WD2_HV_U_TARGET_9_MOD_REG             , WD2_HV_U_TARGET_9_MOD_MASK             , WD2_HV_U_TARGET_9_MOD_OFS            , "Target high voltage channel 9 register modified flags" ],
  [ "HV_U_TARGET_10_MOD"            , WD2_HV_U_TARGET_10_MOD_REG            , WD2_HV_U_TARGET_10_MOD_MASK            , WD2_HV_U_TARGET_10_MOD_OFS           , "Target high voltage channel 10 register modified flags" ],
  [ "HV_U_TARGET_11_MOD"            , WD2_HV_U_TARGET_11_MOD_REG            , WD2_HV_U_TARGET_11_MOD_MASK            , WD2_HV_U_TARGET_11_MOD_OFS           , "Target high voltage channel 11 register modified flags" ],
  [ "HV_U_TARGET_12_MOD"            , WD2_HV_U_TARGET_12_MOD_REG            , WD2_HV_U_TARGET_12_MOD_MASK            , WD2_HV_U_TARGET_12_MOD_OFS           , "Target high voltage channel 12 register modified flags" ],
  [ "HV_U_TARGET_13_MOD"            , WD2_HV_U_TARGET_13_MOD_REG            , WD2_HV_U_TARGET_13_MOD_MASK            , WD2_HV_U_TARGET_13_MOD_OFS           , "Target high voltage channel 13 register modified flags" ],
  [ "HV_U_TARGET_14_MOD"            , WD2_HV_U_TARGET_14_MOD_REG            , WD2_HV_U_TARGET_14_MOD_MASK            , WD2_HV_U_TARGET_14_MOD_OFS           , "Target high voltage channel 14 register modified flags" ],
  [ "HV_U_TARGET_15_MOD"            , WD2_HV_U_TARGET_15_MOD_REG            , WD2_HV_U_TARGET_15_MOD_MASK            , WD2_HV_U_TARGET_15_MOD_OFS           , "Target high voltage channel 15 register modified flags" ],
  [ "HV_R_SHUNT_MOD"                , WD2_HV_R_SHUNT_MOD_REG                , WD2_HV_R_SHUNT_MOD_MASK                , WD2_HV_R_SHUNT_MOD_OFS               , "HV supply shunt resistor register modified flags" ],
  [ "LMK_0_MOD"                     , WD2_LMK_0_MOD_REG                     , WD2_LMK_0_MOD_MASK                     , WD2_LMK_0_MOD_OFS                    , "LMK channel 0 register modified flags" ],
  [ "LMK_1_MOD"                     , WD2_LMK_1_MOD_REG                     , WD2_LMK_1_MOD_MASK                     , WD2_LMK_1_MOD_OFS                    , "LMK channel 1 register modified flags" ],
  [ "LMK_2_MOD"                     , WD2_LMK_2_MOD_REG                     , WD2_LMK_2_MOD_MASK                     , WD2_LMK_2_MOD_OFS                    , "LMK channel 2 register modified flags" ],
  [ "LMK_3_MOD"                     , WD2_LMK_3_MOD_REG                     , WD2_LMK_3_MOD_MASK                     , WD2_LMK_3_MOD_OFS                    , "LMK channel 3 register modified flags" ],
  [ "LMK_4_MOD"                     , WD2_LMK_4_MOD_REG                     , WD2_LMK_4_MOD_MASK                     , WD2_LMK_4_MOD_OFS                    , "LMK channel 4 register modified flags" ],
  [ "LMK_5_MOD"                     , WD2_LMK_5_MOD_REG                     , WD2_LMK_5_MOD_MASK                     , WD2_LMK_5_MOD_OFS                    , "LMK channel 5 register modified flags" ],
  [ "LMK_6_MOD"                     , WD2_LMK_6_MOD_REG                     , WD2_LMK_6_MOD_MASK                     , WD2_LMK_6_MOD_OFS                    , "LMK channel 6 register modified flags" ],
  [ "LMK_7_MOD"                     , WD2_LMK_7_MOD_REG                     , WD2_LMK_7_MOD_MASK                     , WD2_LMK_7_MOD_OFS                    , "LMK channel 7 register modified flags" ],
  [ "LMK_8_MOD"                     , WD2_LMK_8_MOD_REG                     , WD2_LMK_8_MOD_MASK                     , WD2_LMK_8_MOD_OFS                    , "LMK Register 8 modified flags" ],
  [ "LMK_9_MOD"                     , WD2_LMK_9_MOD_REG                     , WD2_LMK_9_MOD_MASK                     , WD2_LMK_9_MOD_OFS                    , "LMK Register 9 modified flags" ],
  [ "LMK_11_MOD"                    , WD2_LMK_11_MOD_REG                    , WD2_LMK_11_MOD_MASK                    , WD2_LMK_11_MOD_OFS                   , "LMK Register 11 modified flags" ],
  [ "LMK_13_MOD"                    , WD2_LMK_13_MOD_REG                    , WD2_LMK_13_MOD_MASK                    , WD2_LMK_13_MOD_OFS                   , "LMK Register 13 modified flags" ],
  [ "LMK_14_MOD"                    , WD2_LMK_14_MOD_REG                    , WD2_LMK_14_MOD_MASK                    , WD2_LMK_14_MOD_OFS                   , "LMK Register 14 modified flags" ],
  [ "LMK_15_MOD"                    , WD2_LMK_15_MOD_REG                    , WD2_LMK_15_MOD_MASK                    , WD2_LMK_15_MOD_OFS                   , "LMK Register 15 modified flags" ],
]

#
# Control Register Defaults
#

ctrl_reg_default = [0xFFFFFFFF,   # Offset 0x1000 
                    0x122D0780,   # Offset 0x1004 
                    0x00000000,   # Offset 0x1008 
                    0x00025050,   # Offset 0x100C 
                    0x00FFFFFF,   # Offset 0x1010 
                    0x02000753,   # Offset 0x1014 
                    0x000005C0,   # Offset 0x1018 
                    0x0000FFFF,   # Offset 0x101C 
                    0x00000000,   # Offset 0x1020 
                    0x00000000,   # Offset 0x1024 
                    0x00000400,   # Offset 0x1028 
                    0x00000800,   # Offset 0x102C 
                    0x00001000,   # Offset 0x1030 
                    0x00000200,   # Offset 0x1034 
                    0x00000001,   # Offset 0x1038 
                    0x00000080,   # Offset 0x103C 
                    0x00000000,   # Offset 0x1040 
                    0x00000000,   # Offset 0x1044 
                    0x9EC045A0,   # Offset 0x1048 
                    0x828F0000,   # Offset 0x104C 
                    0x0000FFFF,   # Offset 0x1050 
                    0x000047B0,   # Offset 0x1054 
                    0x57105710,   # Offset 0x1058 
                    0x57105710,   # Offset 0x105C 
                    0x57105710,   # Offset 0x1060 
                    0x57105710,   # Offset 0x1064 
                    0x57105710,   # Offset 0x1068 
                    0x57105710,   # Offset 0x106C 
                    0x57105710,   # Offset 0x1070 
                    0x57105710,   # Offset 0x1074 
                    0x00020002,   # Offset 0x1078 
                    0x00020002,   # Offset 0x107C 
                    0x00020002,   # Offset 0x1080 
                    0x00020002,   # Offset 0x1084 
                    0x00020002,   # Offset 0x1088 
                    0x00020002,   # Offset 0x108C 
                    0x00020002,   # Offset 0x1090 
                    0x00020002,   # Offset 0x1094 
                    0x00000000,   # Offset 0x1098 
                    0x00000000,   # Offset 0x109C 
                    0x00000000,   # Offset 0x10A0 
                    0x00000000,   # Offset 0x10A4 
                    0x00000000,   # Offset 0x10A8 
                    0x00000000,   # Offset 0x10AC 
                    0x00000000,   # Offset 0x10B0 
                    0x00000000,   # Offset 0x10B4 
                    0x00000000,   # Offset 0x10B8 
                    0x00000000,   # Offset 0x10BC 
                    0x00000000,   # Offset 0x10C0 
                    0x00000000,   # Offset 0x10C4 
                    0x00000000,   # Offset 0x10C8 
                    0x00000000,   # Offset 0x10CC 
                    0x00000000,   # Offset 0x10D0 
                    0x00000000,   # Offset 0x10D4 
                    0x00002710,   # Offset 0x10D8 
                    0x00032100,   # Offset 0x10DC 
                    0x00020101,   # Offset 0x10E0 
                    0x00020102,   # Offset 0x10E4 
                    0x00000103,   # Offset 0x10E8 
                    0x00030104,   # Offset 0x10EC 
                    0x00020105,   # Offset 0x10F0 
                    0x00000106,   # Offset 0x10F4 
                    0x00026407,   # Offset 0x10F8 
                    0x10000908,   # Offset 0x10FC 
                    0xA0022A09,   # Offset 0x1100 
                    0x0082000B,   # Offset 0x1104 
                    0x029400AD,   # Offset 0x1108 
                    0x0830100E,   # Offset 0x110C 
                    0xE000200F,   # Offset 0x1110 
                    0x00F63F00,   # Offset 0x1114 
                    0x00F63F00,   # Offset 0x1118 
                    0x00F63F00,   # Offset 0x111C 
                    0x00F63F00,   # Offset 0x1120 
                    0x00000000,   # Offset 0x1124 
                    0x00000000,   # Offset 0x1128 
                    0x04C4B400,   # Offset 0x112C 
                    0x00000000,   # Offset 0x1130 
                    0x00000000,   # Offset 0x1134 
                    0x00000000,   # Offset 0x1138 
                    0x00000000,   # Offset 0x113C 
                    0x00000000,   # Offset 0x1140 
                    0x00000000,   # Offset 0x1144 
                    0x00000000,   # Offset 0x1148 
                    0x00000000,   # Offset 0x114C 
                    0x00000000,   # Offset 0x1150 
                    0x00000000,   # Offset 0x1154 
                    0x00000000,   # Offset 0x1158 
                    0x00000000,   # Offset 0x115C 
                    0x00000000,   # Offset 0x1160 
                    0x00000000,   # Offset 0x1164 
                    0x00000000,   # Offset 0x1168 
                    0x00000000,   # Offset 0x116C 
                    0x00000000,   # Offset 0x1170 
                    0x00000000,   # Offset 0x1174 
                    0x00000000,   # Offset 0x1178 
                    0x00000000,   # Offset 0x117C 
                    0x00000000,   # Offset 0x1180 
                    0x00000000,   # Offset 0x1184 
                    0x00000000,   # Offset 0x1188 
                    0x00000000,   # Offset 0x118C 
                    0x00000000,   # Offset 0x1190 
                    0x00000000,   # Offset 0x1194 
                    0x00000000,   # Offset 0x1198 
                    0x00000000,   # Offset 0x119C 
                    0x00000000,   # Offset 0x11A0 
                    0x00000000,   # Offset 0x11A4 
                    0x00000000,   # Offset 0x11A8 
                    0x00000000,   # Offset 0x11AC 
                    0x00000000,   # Offset 0x11B0 
                    0x00000000,   # Offset 0x11B4 
                    0x00000000,   # Offset 0x11B8 
                    0x00000000,   # Offset 0x11BC 
                    0x00000000,   # Offset 0x11C0 
                    0x00000000,   # Offset 0x11C4 
                    0x00000000,   # Offset 0x11C8 
                    0x00000000,   # Offset 0x11CC 
                    0x00000000,   # Offset 0x11D0 
                    0x00000000,   # Offset 0x11D4 
                    0x00000000,   # Offset 0x11D8 
                    0x00000000,   # Offset 0x11DC 
                    0x00000000,   # Offset 0x11E0 
                    0x00000000,   # Offset 0x11E4 
                    0x00000000,   # Offset 0x11E8 
                    0x00000000,   # Offset 0x11EC 
                    0x00000000,   # Offset 0x11F0 
                    0x00000000,   # Offset 0x11F4 
                    0x00000000,   # Offset 0x11F8 
                    0x00000000,   # Offset 0x11FC 
                    0x00000000,   # Offset 0x1200 
                    0x00000000,   # Offset 0x1204 
                    0x00000000,   # Offset 0x1208 
                    0x00000000,   # Offset 0x120C 
                    0x00000000,   # Offset 0x1210 
                    0x00000000,   # Offset 0x1214 
                    0x00000000,   # Offset 0x1218 
                    0x00000000,   # Offset 0x121C 
                    0x00000000,   # Offset 0x1220 
                    0x00000000]   # Offset 0x1224 


# #############################################################################
# #############################################################################

# #####################################################################################
#  Paul Scherrer Institut
# #####################################################################################
#
#  Project :  WaveDream2
#
#  Author  :  schmid_e (Author of generation script)
#  Created :  14.11.2017 11:51:48
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

# Control Registers ***
WD2_REG_WDB_LOC_OFS                       = 0x1000
WD2_REG_CTRL_OFS                          = 0x1004
WD2_REG_CAL_CTRL_OFS                      = 0x1008
WD2_REG_CLK_CTRL_OFS                      = 0x100C
WD2_REG_DRS_CTRL_OFS                      = 0x1010
WD2_REG_COM_CTRL_OFS                      = 0x1014
WD2_REG_COM_PLD_SIZE_OFS                  = 0x1018
WD2_REG_DRS_CH_TX_EN_OFS                  = 0x101C
WD2_REG_ADC_CH_TX_EN_OFS                  = 0x1020
WD2_REG_TDC_CH_TX_EN_OFS                  = 0x1024
WD2_REG_DRS_TX_SAMPLES_OFS                = 0x1028
WD2_REG_ADC_TX_SAMPLES_OFS                = 0x102C
WD2_REG_TDC_TX_SAMPLES_OFS                = 0x1030
WD2_REG_TRG_TX_SAMPLES_OFS                = 0x1034
WD2_REG_ADC_SAMPLE_DIV_OFS                = 0x1038
WD2_REG_RST_OFS                           = 0x103C
WD2_REG_APLY_CFG_OFS                      = 0x1040
WD2_REG_DAC0_A_B_OFS                      = 0x1044
WD2_REG_DAC0_C_D_OFS                      = 0x1048
WD2_REG_DAC0_E_F_OFS                      = 0x104C
WD2_REG_DAC0_G_H_OFS                      = 0x1050
WD2_REG_DAC1_A_B_OFS                      = 0x1054
WD2_REG_DAC1_C_D_OFS                      = 0x1058
WD2_REG_DAC1_E_F_OFS                      = 0x105C
WD2_REG_DAC1_G_H_OFS                      = 0x1060
WD2_REG_DAC2_A_B_OFS                      = 0x1064
WD2_REG_DAC2_C_D_OFS                      = 0x1068
WD2_REG_DAC2_E_F_OFS                      = 0x106C
WD2_REG_DAC2_G_H_OFS                      = 0x1070
WD2_REG_FE_CFG_0_1_OFS                    = 0x1074
WD2_REG_FE_CFG_2_3_OFS                    = 0x1078
WD2_REG_FE_CFG_4_5_OFS                    = 0x107C
WD2_REG_FE_CFG_6_7_OFS                    = 0x1080
WD2_REG_FE_CFG_8_9_OFS                    = 0x1084
WD2_REG_FE_CFG_10_11_OFS                  = 0x1088
WD2_REG_FE_CFG_12_13_OFS                  = 0x108C
WD2_REG_FE_CFG_14_15_OFS                  = 0x1090
WD2_REG_HV_U_TARGET_0_OFS                 = 0x1094
WD2_REG_HV_U_TARGET_1_OFS                 = 0x1098
WD2_REG_HV_U_TARGET_2_OFS                 = 0x109C
WD2_REG_HV_U_TARGET_3_OFS                 = 0x10A0
WD2_REG_HV_U_TARGET_4_OFS                 = 0x10A4
WD2_REG_HV_U_TARGET_5_OFS                 = 0x10A8
WD2_REG_HV_U_TARGET_6_OFS                 = 0x10AC
WD2_REG_HV_U_TARGET_7_OFS                 = 0x10B0
WD2_REG_HV_U_TARGET_8_OFS                 = 0x10B4
WD2_REG_HV_U_TARGET_9_OFS                 = 0x10B8
WD2_REG_HV_U_TARGET_10_OFS                = 0x10BC
WD2_REG_HV_U_TARGET_11_OFS                = 0x10C0
WD2_REG_HV_U_TARGET_12_OFS                = 0x10C4
WD2_REG_HV_U_TARGET_13_OFS                = 0x10C8
WD2_REG_HV_U_TARGET_14_OFS                = 0x10CC
WD2_REG_HV_U_TARGET_15_OFS                = 0x10D0
WD2_REG_HV_R_SHUNT_OFS                    = 0x10D4
WD2_REG_LMK_0_OFS                         = 0x10D8
WD2_REG_LMK_1_OFS                         = 0x10DC
WD2_REG_LMK_2_OFS                         = 0x10E0
WD2_REG_LMK_3_OFS                         = 0x10E4
WD2_REG_LMK_4_OFS                         = 0x10E8
WD2_REG_LMK_5_OFS                         = 0x10EC
WD2_REG_LMK_6_OFS                         = 0x10F0
WD2_REG_LMK_7_OFS                         = 0x10F4
WD2_REG_LMK_8_OFS                         = 0x10F8
WD2_REG_LMK_9_OFS                         = 0x10FC
WD2_REG_LMK_11_OFS                        = 0x1100
WD2_REG_LMK_13_OFS                        = 0x1104
WD2_REG_LMK_14_OFS                        = 0x1108
WD2_REG_LMK_15_OFS                        = 0x110C
WD2_REG_ADC_CFG_IND_TX_OFS                = 0x1110
WD2_REG_ADC_PM_CLK_ENH_OFS                = 0x1114
WD2_REG_ADC_TEST_OFFS_OM_OFS              = 0x1118
WD2_REG_ADC_OUT_VREF_OFS                  = 0x111C
WD2_REG_ADC_USR_PATT_OFS                  = 0x1120
WD2_REG_ADC_SER_RES_SR_OFS                = 0x1124
WD2_REG_ADC_USR_IO_SYNC_OFS               = 0x1128
WD2_REG_ADC_0_CH_A_CFG_OFS                = 0x112C
WD2_REG_ADC_0_CH_B_CFG_OFS                = 0x1130
WD2_REG_ADC_0_CH_C_CFG_OFS                = 0x1134
WD2_REG_ADC_0_CH_D_CFG_OFS                = 0x1138
WD2_REG_ADC_0_CH_E_CFG_OFS                = 0x113C
WD2_REG_ADC_0_CH_F_CFG_OFS                = 0x1140
WD2_REG_ADC_0_CH_G_CFG_OFS                = 0x1144
WD2_REG_ADC_0_CH_H_CFG_OFS                = 0x1148
WD2_REG_ADC_0_CH_DCO_CFG_OFS              = 0x114C
WD2_REG_ADC_0_CH_FCO_CFG_OFS              = 0x1150
WD2_REG_ADC_1_CH_A_CFG_OFS                = 0x1154
WD2_REG_ADC_1_CH_B_CFG_OFS                = 0x1158
WD2_REG_ADC_1_CH_C_CFG_OFS                = 0x115C
WD2_REG_ADC_1_CH_D_CFG_OFS                = 0x1160
WD2_REG_ADC_1_CH_E_CFG_OFS                = 0x1164
WD2_REG_ADC_1_CH_F_CFG_OFS                = 0x1168
WD2_REG_ADC_1_CH_G_CFG_OFS                = 0x116C
WD2_REG_ADC_1_CH_H_CFG_OFS                = 0x1170
WD2_REG_ADC_1_CH_DCO_CFG_OFS              = 0x1174
WD2_REG_ADC_1_CH_FCO_CFG_OFS              = 0x1178
WD2_REG_TRG_CFG_OFS                       = 0x117C
WD2_REG_TRG_COMP_MASK_OFS                 = 0x1180
WD2_REG_TRG_CH_CMB_OFS                    = 0x1184
WD2_REG_TRG_SCH_SEL_OFS                   = 0x1188
WD2_REG_TRG_PTRN_EN_LOCAL_OFS             = 0x118C
WD2_REG_TRG_PTRN_EN_BPL0_OFS              = 0x1190
WD2_REG_TRG_PTRN_EN_BPL1_OFS              = 0x1194
WD2_REG_TRG_PTRN_EN_BPL2_OFS              = 0x1198
WD2_REG_TRG_PTRN_EN_BPL3_OFS              = 0x119C
WD2_REG_TRG_PTRN_EN_BPL4_OFS              = 0x11A0
WD2_REG_TRG_PTRN_EN_BPL5_OFS              = 0x11A4
WD2_REG_TRG_PTRN_EN_BPL6_OFS              = 0x11A8
WD2_REG_TRG_PTRN_EN_BPL7_OFS              = 0x11AC
WD2_REG_TRG_PTRN0_OFS                     = 0x11B0
WD2_REG_TRG_PTRN1_OFS                     = 0x11B4
WD2_REG_TRG_PTRN2_OFS                     = 0x11B8
WD2_REG_TRG_PTRN3_OFS                     = 0x11BC
WD2_REG_TRG_PTRN4_OFS                     = 0x11C0
WD2_REG_TRG_PTRN5_OFS                     = 0x11C4
WD2_REG_TRG_PTRN6_OFS                     = 0x11C8
WD2_REG_TRG_PTRN7_OFS                     = 0x11CC
WD2_REG_TRG_PTRN8_OFS                     = 0x11D0
WD2_REG_TRG_PTRN9_OFS                     = 0x11D4
WD2_REG_TRG_PTRN10_OFS                    = 0x11D8
WD2_REG_TRG_PTRN11_OFS                    = 0x11DC
WD2_REG_TRG_PTRN12_OFS                    = 0x11E0
WD2_REG_TRG_PTRN13_OFS                    = 0x11E4
WD2_REG_TRG_PTRN14_OFS                    = 0x11E8
WD2_REG_TRG_PTRN15_OFS                    = 0x11EC
WD2_REG_TRG_PTRN16_OFS                    = 0x11F0
WD2_REG_TRG_PTRN17_OFS                    = 0x11F4
WD2_REG_TRG_PTRN18_OFS                    = 0x11F8
WD2_REG_TRG_PTRN19_OFS                    = 0x11FC
WD2_REG_TRG_PTRN20_OFS                    = 0x1200
WD2_REG_TRG_PTRN21_OFS                    = 0x1204
WD2_REG_TRG_PTRN22_OFS                    = 0x1208
WD2_REG_TRG_PTRN23_OFS                    = 0x120C
WD2_REG_TRG_PTRN24_OFS                    = 0x1210
WD2_REG_TRG_PTRN25_OFS                    = 0x1214
WD2_REG_TRG_PTRN26_OFS                    = 0x1218
WD2_REG_TRG_PTRN27_OFS                    = 0x121C
WD2_REG_TRG_PTRN28_OFS                    = 0x1220
WD2_REG_TRG_PTRN29_OFS                    = 0x1224
WD2_REG_TRG_PTRN30_OFS                    = 0x1228
WD2_REG_TRG_PTRN31_OFS                    = 0x122C
WD2_REG_ADV_TRG_CFG0_OFS                  = 0x1230
WD2_REG_ADV_TRG_CFG1_OFS                  = 0x1234
WD2_REG_ADV_TRG_CFG2_OFS                  = 0x1238
WD2_REG_ADV_TRG_CFG3_OFS                  = 0x123C
WD2_REG_ADV_TRG_CFG4_OFS                  = 0x1240
WD2_REG_ADV_TRG_CFG5_OFS                  = 0x1244
WD2_REG_ADV_TRG_CFG6_OFS                  = 0x1248
WD2_REG_ADV_TRG_CFG7_OFS                  = 0x124C
WD2_REG_ADV_TRG_CFG8_OFS                  = 0x1250
WD2_REG_ADV_TRG_CFG9_OFS                  = 0x1254
WD2_REG_ADV_TRG_CFG10_OFS                 = 0x1258
WD2_REG_ADV_TRG_CFG11_OFS                 = 0x125C
WD2_REG_ADV_TRG_CFG12_OFS                 = 0x1260
WD2_REG_ADV_TRG_CFG13_OFS                 = 0x1264
WD2_REG_ADV_TRG_CFG14_OFS                 = 0x1268
WD2_REG_ADV_TRG_CFG15_OFS                 = 0x126C
WD2_REG_ADV_TRG_CFG16_OFS                 = 0x1270
WD2_REG_ADV_TRG_CFG17_OFS                 = 0x1274
WD2_REG_ADV_TRG_CFG18_OFS                 = 0x1278
WD2_REG_ADV_TRG_CFG19_OFS                 = 0x127C
WD2_REG_ADV_TRG_CFG20_OFS                 = 0x1280
WD2_REG_ADV_TRG_CFG21_OFS                 = 0x1284
WD2_REG_ADV_TRG_CFG22_OFS                 = 0x1288
WD2_REG_ADV_TRG_CFG23_OFS                 = 0x128C
WD2_REG_ADV_TRG_CFG24_OFS                 = 0x1290
WD2_REG_ADV_TRG_CFG25_OFS                 = 0x1294
WD2_REG_ADV_TRG_CFG26_OFS                 = 0x1298
WD2_REG_ADV_TRG_CFG27_OFS                 = 0x129C
WD2_REG_ADV_TRG_CFG28_OFS                 = 0x12A0
WD2_REG_ADV_TRG_CFG29_OFS                 = 0x12A4
WD2_REG_SET_TIME_LSB_OFS                  = 0x12A8
WD2_REG_SET_TIME_MSB_OFS                  = 0x12AC
WD2_REG_DBG_SIG_SEL_OFS                   = 0x12B0
WD2_REG_CRC32_REG_BANK_OFS                = 0x12B4

# Status Registers 
WD2_REG_HW_VER_OFS                        = 0x0000
WD2_REG_REG_LAYOUT_VER_OFS                = 0x0004
WD2_REG_FW_BUILD_DATE_OFS                 = 0x0008
WD2_REG_FW_BUILD_TIME_OFS                 = 0x000C
WD2_REG_SW_BUILD_DATE_OFS                 = 0x0010
WD2_REG_SW_BUILD_TIME_OFS                 = 0x0014
WD2_REG_GIT_HASH_TAG_OFS                  = 0x0018
WD2_REG_PROT_VER_OFS                      = 0x001C
WD2_REG_SN_OFS                            = 0x0020
WD2_REG_STATUS_OFS                        = 0x0024
WD2_REG_PLL_LOCK_OFS                      = 0x0028
WD2_REG_DRS_STOP_CELL_OFS                 = 0x002C
WD2_REG_DRS_STOP_WSR_OFS                  = 0x0030
WD2_REG_DRS_SAMPLE_FREQ_OFS               = 0x0034
WD2_REG_ADC_SAMPLE_FREQ_OFS               = 0x0038
WD2_REG_TDC_SAMPLE_FREQ_OFS               = 0x003C
WD2_REG_ADC_INFO_OFS                      = 0x0040
WD2_REG_HV_VER_OFS                        = 0x0044
WD2_REG_HV_I_MEAS_0_OFS                   = 0x0048
WD2_REG_HV_I_MEAS_1_OFS                   = 0x004C
WD2_REG_HV_I_MEAS_2_OFS                   = 0x0050
WD2_REG_HV_I_MEAS_3_OFS                   = 0x0054
WD2_REG_HV_I_MEAS_4_OFS                   = 0x0058
WD2_REG_HV_I_MEAS_5_OFS                   = 0x005C
WD2_REG_HV_I_MEAS_6_OFS                   = 0x0060
WD2_REG_HV_I_MEAS_7_OFS                   = 0x0064
WD2_REG_HV_I_MEAS_8_OFS                   = 0x0068
WD2_REG_HV_I_MEAS_9_OFS                   = 0x006C
WD2_REG_HV_I_MEAS_10_OFS                  = 0x0070
WD2_REG_HV_I_MEAS_11_OFS                  = 0x0074
WD2_REG_HV_I_MEAS_12_OFS                  = 0x0078
WD2_REG_HV_I_MEAS_13_OFS                  = 0x007C
WD2_REG_HV_I_MEAS_14_OFS                  = 0x0080
WD2_REG_HV_I_MEAS_15_OFS                  = 0x0084
WD2_REG_HV_U_BASE_MEAS_OFS                = 0x0088
WD2_REG_HV_TEMP_0_OFS                     = 0x008C
WD2_REG_HV_TEMP_1_OFS                     = 0x0090
WD2_REG_HV_TEMP_2_OFS                     = 0x0094
WD2_REG_HV_TEMP_3_OFS                     = 0x0098
WD2_REG_SCALER_0_LSB_OFS                  = 0x009C
WD2_REG_SCALER_0_MSB_OFS                  = 0x00A0
WD2_REG_SCALER_1_LSB_OFS                  = 0x00A4
WD2_REG_SCALER_1_MSB_OFS                  = 0x00A8
WD2_REG_SCALER_2_LSB_OFS                  = 0x00AC
WD2_REG_SCALER_2_MSB_OFS                  = 0x00B0
WD2_REG_SCALER_3_LSB_OFS                  = 0x00B4
WD2_REG_SCALER_3_MSB_OFS                  = 0x00B8
WD2_REG_SCALER_4_LSB_OFS                  = 0x00BC
WD2_REG_SCALER_4_MSB_OFS                  = 0x00C0
WD2_REG_SCALER_5_LSB_OFS                  = 0x00C4
WD2_REG_SCALER_5_MSB_OFS                  = 0x00C8
WD2_REG_SCALER_6_LSB_OFS                  = 0x00CC
WD2_REG_SCALER_6_MSB_OFS                  = 0x00D0
WD2_REG_SCALER_7_LSB_OFS                  = 0x00D4
WD2_REG_SCALER_7_MSB_OFS                  = 0x00D8
WD2_REG_SCALER_8_LSB_OFS                  = 0x00DC
WD2_REG_SCALER_8_MSB_OFS                  = 0x00E0
WD2_REG_SCALER_9_LSB_OFS                  = 0x00E4
WD2_REG_SCALER_9_MSB_OFS                  = 0x00E8
WD2_REG_SCALER_10_LSB_OFS                 = 0x00EC
WD2_REG_SCALER_10_MSB_OFS                 = 0x00F0
WD2_REG_SCALER_11_LSB_OFS                 = 0x00F4
WD2_REG_SCALER_11_MSB_OFS                 = 0x00F8
WD2_REG_SCALER_12_LSB_OFS                 = 0x00FC
WD2_REG_SCALER_12_MSB_OFS                 = 0x0100
WD2_REG_SCALER_13_LSB_OFS                 = 0x0104
WD2_REG_SCALER_13_MSB_OFS                 = 0x0108
WD2_REG_SCALER_14_LSB_OFS                 = 0x010C
WD2_REG_SCALER_14_MSB_OFS                 = 0x0110
WD2_REG_SCALER_15_LSB_OFS                 = 0x0114
WD2_REG_SCALER_15_MSB_OFS                 = 0x0118
WD2_REG_SCALER_TRG_OFS                    = 0x011C
WD2_REG_SCALER_EXT_CLK_OFS                = 0x0120
WD2_REG_TIME_LSB_OFS                      = 0x0124
WD2_REG_TIME_MSB_OFS                      = 0x0128
WD2_REG_COMP_CH_STAT_OFS                  = 0x012C
WD2_REG_EVENT_NR_OFS                      = 0x0130
WD2_REG_TRB_PARITY_ERR_OFS                = 0x0134
WD2_REG_TRB_INFO_OFS                      = 0x0138
WD2_REG_ADV_TRG_STAT0_OFS                 = 0x013C
WD2_REG_ADV_TRG_STAT1_OFS                 = 0x0140
WD2_REG_ADV_TRG_STAT2_OFS                 = 0x0144
WD2_REG_ADV_TRG_STAT3_OFS                 = 0x0148
WD2_REG_ADV_TRG_STAT4_OFS                 = 0x014C
WD2_REG_ADV_TRG_STAT5_OFS                 = 0x0150
WD2_REG_ADV_TRG_STAT6_OFS                 = 0x0154
WD2_REG_ADV_TRG_STAT7_OFS                 = 0x0158
WD2_REG_ADV_TRG_STAT8_OFS                 = 0x015C
WD2_REG_ADV_TRG_STAT9_OFS                 = 0x0160
WD2_REG_MAX_DRS_ADC_PKT_SAMPLES_OFS       = 0x0164
WD2_REG_MAX_TDC_PKT_SAMPLES_OFS           = 0x0168
WD2_REG_MAX_TRG_PKT_SAMPLES_OFS           = 0x016C
WD2_REG_MAX_SCL_PKT_SAMPLES_OFS           = 0x0170
WD2_REG_CLK_CTRL_MOD_FLAG_OFS             = 0x0174
WD2_REG_DRS_MOD_FLAG_OFS                  = 0x0178
WD2_REG_COM_PLD_SIZE_MOD_FLAG_OFS         = 0x017C
WD2_REG_ADC_SAMPLE_DIV_MOD_FLAG_OFS       = 0x0180
WD2_REG_DAC_0_1_MOD_FLAG_OFS              = 0x0184
WD2_REG_DAC_2_MOD_FLAG_OFS                = 0x0188
WD2_REG_FE_0_15_MOD_FLAG_OFS              = 0x018C
WD2_REG_HV_U_TARGET_0_7_MOD_FLAG_OFS      = 0x0190
WD2_REG_HV_U_TARGET_8_15_MOD_FLAG_OFS     = 0x0194
WD2_REG_HV_MOD_FLAG_OFS                   = 0x0198
WD2_REG_LMK_0_7_MOD_FLAG_OFS              = 0x019C
WD2_REG_LMK_8_15_MOD_FLAG_OFS             = 0x01A0
WD2_REG_ADC_MOD_FLAG_OFS                  = 0x01A4
WD2_REG_ADC_0_CH_MOD_FLAG_OFS             = 0x01A8
WD2_REG_ADC_1_CH_MOD_FLAG_OFS             = 0x01AC
WD2_REG_ADC_01_CLK_MOD_FLAG_OFS           = 0x01B0


# Bit Positions
 

# Control Register 0: WDB_LOC (offset 0x1000) 
WD2_BIT_CRATE_ID_MASK                        = 0x00FF0000
WD2_BIT_CRATE_ID_OFS                         =         16
WD2_BIT_SLOT_ID_MASK                         = 0x000000FF
WD2_BIT_SLOT_ID_OFS                          =          0

# Control Register 1: CTRL (offset 0x1004) 
WD2_BIT_VALID_DELAY_ADC_MASK                 = 0x3F000000
WD2_BIT_VALID_DELAY_ADC_OFS                  =         24
WD2_BIT_DAQ_DATA_PHASE_MASK                  = 0x00FF0000
WD2_BIT_DAQ_DATA_PHASE_OFS                   =         16
WD2_BIT_COMP_POWER_EN_MASK                   = 0x00000200
WD2_BIT_COMP_POWER_EN_OFS                    =          9
WD2_BIT_DRS_READOUT_MODE_MASK                = 0x00000100
WD2_BIT_DRS_READOUT_MODE_OFS                 =          8
WD2_BIT_DRS_WAVE_CONTINUOUS_MASK             = 0x00000080
WD2_BIT_DRS_WAVE_CONTINUOUS_OFS              =          7
WD2_BIT_DRS_CONFIGURE_MASK                   = 0x00000040
WD2_BIT_DRS_CONFIGURE_OFS                    =          6
WD2_BIT_DAQ_SOFT_TRIGGER_MASK                = 0x00000020
WD2_BIT_DAQ_SOFT_TRIGGER_OFS                 =          5
WD2_BIT_DAQ_AUTO_MASK                        = 0x00000004
WD2_BIT_DAQ_AUTO_OFS                         =          2
WD2_BIT_DAQ_NORMAL_MASK                      = 0x00000002
WD2_BIT_DAQ_NORMAL_OFS                       =          1
WD2_BIT_DAQ_SINGLE_MASK                      = 0x00000001
WD2_BIT_DAQ_SINGLE_OFS                       =          0

# Control Register 2: CAL_CTRL (offset 0x1008) 
WD2_BIT_DRS_0_TIMING_REF_SEL_MASK            = 0x00000008
WD2_BIT_DRS_0_TIMING_REF_SEL_OFS             =          3
WD2_BIT_DRS_1_TIMING_REF_SEL_MASK            = 0x00000004
WD2_BIT_DRS_1_TIMING_REF_SEL_OFS             =          2
WD2_BIT_CALIB_BUFFER_EN_MASK                 = 0x00000002
WD2_BIT_CALIB_BUFFER_EN_OFS                  =          1
WD2_BIT_TIMING_CALIB_SIGNAL_EN_MASK          = 0x00000001
WD2_BIT_TIMING_CALIB_SIGNAL_EN_OFS           =          0

# Control Register 3: CLK_CTRL (offset 0x100C) 
WD2_BIT_DAQ_CLK_SRC_SEL_MASK                 = 0x00020000
WD2_BIT_DAQ_CLK_SRC_SEL_OFS                  =         17
WD2_BIT_EXT_CLK_IN_SEL_MASK                  = 0x00010000
WD2_BIT_EXT_CLK_IN_SEL_OFS                   =         16
WD2_BIT_EXT_CLK_FREQ_MASK                    = 0x0000FF00
WD2_BIT_EXT_CLK_FREQ_OFS                     =          8
WD2_BIT_LOCAL_CLK_FREQ_MASK                  = 0x000000FF
WD2_BIT_LOCAL_CLK_FREQ_OFS                   =          0

# Control Register 4: DRS_CTRL (offset 0x1010) 
WD2_BIT_DRS_WSRLOOP_MASK                     = 0x00040000
WD2_BIT_DRS_WSRLOOP_OFS                      =         18
WD2_BIT_DRS_PLLEN_MASK                       = 0x00020000
WD2_BIT_DRS_PLLEN_OFS                        =         17
WD2_BIT_DRS_DMODE_MASK                       = 0x00010000
WD2_BIT_DRS_DMODE_OFS                        =         16
WD2_BIT_DRS_WSR_MASK                         = 0x0000FF00
WD2_BIT_DRS_WSR_OFS                          =          8
WD2_BIT_DRS_WCR_MASK                         = 0x000000FF
WD2_BIT_DRS_WCR_OFS                          =          0

# Control Register 5: COM_CTRL (offset 0x1014) 
WD2_BIT_DCB_SERDES_TRAIN_MASK                = 0x80000000
WD2_BIT_DCB_SERDES_TRAIN_OFS                 =         31
WD2_BIT_TCB_SERDES_TRAIN_MASK                = 0x40000000
WD2_BIT_TCB_SERDES_TRAIN_OFS                 =         30
WD2_BIT_ZERO_SUPR_EN_MASK                    = 0x10000000
WD2_BIT_ZERO_SUPR_EN_OFS                     =         28
WD2_BIT_TRG_TX_EN_MASK                       = 0x08000000
WD2_BIT_TRG_TX_EN_OFS                        =         27
WD2_BIT_SCL_TX_EN_MASK                       = 0x04000000
WD2_BIT_SCL_TX_EN_OFS                        =         26
WD2_BIT_SERDES_COM_EN_MASK                   = 0x02000000
WD2_BIT_SERDES_COM_EN_OFS                    =         25
WD2_BIT_ETH_COM_EN_MASK                      = 0x01000000
WD2_BIT_ETH_COM_EN_OFS                       =         24
WD2_BIT_INTER_PKG_DELAY_MASK                 = 0x00FFFFFF
WD2_BIT_INTER_PKG_DELAY_OFS                  =          0

# Control Register 6: COM_PLD_SIZE (offset 0x1018) 
WD2_BIT_COM_PLD_SIZE_MASK                    = 0x0003FFFF
WD2_BIT_COM_PLD_SIZE_OFS                     =          0

# Control Register 7: DRS_CH_TX_EN (offset 0x101C) 
WD2_BIT_DRS_CH_TX_EN_MASK                    = 0x0003FFFF
WD2_BIT_DRS_CH_TX_EN_OFS                     =          0

# Control Register 8: ADC_CH_TX_EN (offset 0x1020) 
WD2_BIT_ADC_CH_TX_EN_MASK                    = 0x0000FFFF
WD2_BIT_ADC_CH_TX_EN_OFS                     =          0

# Control Register 9: TDC_CH_TX_EN (offset 0x1024) 
WD2_BIT_TDC_CH_TX_EN_MASK                    = 0x0000FFFF
WD2_BIT_TDC_CH_TX_EN_OFS                     =          0

# Control Register 10: DRS_TX_SAMPLES (offset 0x1028) 
WD2_BIT_DRS_TX_SAMPLES_MASK                  = 0x000007FF
WD2_BIT_DRS_TX_SAMPLES_OFS                   =          0

# Control Register 11: ADC_TX_SAMPLES (offset 0x102C) 
WD2_BIT_ADC_TX_SAMPLES_MASK                  = 0x00000FFF
WD2_BIT_ADC_TX_SAMPLES_OFS                   =          0

# Control Register 12: TDC_TX_SAMPLES (offset 0x1030) 
WD2_BIT_TDC_TX_SAMPLES_MASK                  = 0x00001FFF
WD2_BIT_TDC_TX_SAMPLES_OFS                   =          0

# Control Register 13: TRG_TX_SAMPLES (offset 0x1034) 
WD2_BIT_TRG_TX_SAMPLES_MASK                  = 0x000003FF
WD2_BIT_TRG_TX_SAMPLES_OFS                   =          0

# Control Register 14: ADC_SAMPLE_DIV (offset 0x1038) 
WD2_BIT_ADC_SAMPLE_DIV_MASK                  = 0x000000FF
WD2_BIT_ADC_SAMPLE_DIV_OFS                   =          0

# Control Register 15: RST (offset 0x103C) 
WD2_BIT_DAQ_PLL_RST_MASK                     = 0x00001000
WD2_BIT_DAQ_PLL_RST_OFS                      =         12
WD2_BIT_DCB_OSERDES_PLL_RST_MASK             = 0x00000800
WD2_BIT_DCB_OSERDES_PLL_RST_OFS              =         11
WD2_BIT_TCB_OSERDES_PLL_RST_MASK             = 0x00000400
WD2_BIT_TCB_OSERDES_PLL_RST_OFS              =         10
WD2_BIT_DCB_OSERDES_IF_RST_MASK              = 0x00000200
WD2_BIT_DCB_OSERDES_IF_RST_OFS               =          9
WD2_BIT_TCB_OSERDES_IF_RST_MASK              = 0x00000100
WD2_BIT_TCB_OSERDES_IF_RST_OFS               =          8
WD2_BIT_SCALER_RST_MASK                      = 0x00000080
WD2_BIT_SCALER_RST_OFS                       =          7
WD2_BIT_TRB_PARITY_ERROR_COUNT_RST_MASK      = 0x00000040
WD2_BIT_TRB_PARITY_ERROR_COUNT_RST_OFS       =          6
WD2_BIT_LMK_SYNC_LOCAL_MASK                  = 0x00000020
WD2_BIT_LMK_SYNC_LOCAL_OFS                   =          5
WD2_BIT_ADC_IF_RST_MASK                      = 0x00000010
WD2_BIT_ADC_IF_RST_OFS                       =          4
WD2_BIT_WD_PKGR_RST_MASK                     = 0x00000008
WD2_BIT_WD_PKGR_RST_OFS                      =          3
WD2_BIT_EVENT_COUNTER_RST_MASK               = 0x00000004
WD2_BIT_EVENT_COUNTER_RST_OFS                =          2
WD2_BIT_DRS_CTRL_FSM_RST_MASK                = 0x00000002
WD2_BIT_DRS_CTRL_FSM_RST_OFS                 =          1
WD2_BIT_RECONFIGURE_FPGA_MASK                = 0x00000001
WD2_BIT_RECONFIGURE_FPGA_OFS                 =          0

# Control Register 16: APLY_CFG (offset 0x1040) 
WD2_BIT_APPLY_SETTINGS_HV_MASK               = 0x00000040
WD2_BIT_APPLY_SETTINGS_HV_OFS                =          6
WD2_BIT_APPLY_SETTINGS_DRS_MASK              = 0x00000020
WD2_BIT_APPLY_SETTINGS_DRS_OFS               =          5
WD2_BIT_APPLY_SETTINGS_DAC_MASK              = 0x00000010
WD2_BIT_APPLY_SETTINGS_DAC_OFS               =          4
WD2_BIT_APPLY_SETTINGS_FRONTEND_MASK         = 0x00000008
WD2_BIT_APPLY_SETTINGS_FRONTEND_OFS          =          3
WD2_BIT_APPLY_SETTINGS_CTRL_MASK             = 0x00000004
WD2_BIT_APPLY_SETTINGS_CTRL_OFS              =          2
WD2_BIT_APPLY_SETTINGS_ADC_MASK              = 0x00000002
WD2_BIT_APPLY_SETTINGS_ADC_OFS               =          1
WD2_BIT_APPLY_SETTINGS_LMK_MASK              = 0x00000001
WD2_BIT_APPLY_SETTINGS_LMK_OFS               =          0

# Control Register 17: DAC0_A_B (offset 0x1044) 
WD2_BIT_DAC0_CH_A_MASK                       = 0xFFFF0000
WD2_BIT_DAC0_CH_A_OFS                        =         16
WD2_BIT_DAC0_CH_B_MASK                       = 0x0000FFFF
WD2_BIT_DAC0_CH_B_OFS                        =          0

# Control Register 18: DAC0_C_D (offset 0x1048) 
WD2_BIT_DAC0_CH_C_MASK                       = 0xFFFF0000
WD2_BIT_DAC0_CH_C_OFS                        =         16
WD2_BIT_DAC0_CH_D_MASK                       = 0x0000FFFF
WD2_BIT_DAC0_CH_D_OFS                        =          0

# Control Register 19: DAC0_E_F (offset 0x104C) 
WD2_BIT_DAC0_CH_E_MASK                       = 0xFFFF0000
WD2_BIT_DAC0_CH_E_OFS                        =         16
WD2_BIT_DAC0_CH_F_MASK                       = 0x0000FFFF
WD2_BIT_DAC0_CH_F_OFS                        =          0

# Control Register 20: DAC0_G_H (offset 0x1050) 
WD2_BIT_DAC0_CH_G_MASK                       = 0xFFFF0000
WD2_BIT_DAC0_CH_G_OFS                        =         16
WD2_BIT_DAC0_CH_H_MASK                       = 0x0000FFFF
WD2_BIT_DAC0_CH_H_OFS                        =          0

# Control Register 21: DAC1_A_B (offset 0x1054) 
WD2_BIT_DAC1_CH_A_MASK                       = 0xFFFF0000
WD2_BIT_DAC1_CH_A_OFS                        =         16
WD2_BIT_DAC1_CH_B_MASK                       = 0x0000FFFF
WD2_BIT_DAC1_CH_B_OFS                        =          0

# Control Register 22: DAC1_C_D (offset 0x1058) 
WD2_BIT_DAC1_CH_C_MASK                       = 0xFFFF0000
WD2_BIT_DAC1_CH_C_OFS                        =         16
WD2_BIT_DAC1_CH_D_MASK                       = 0x0000FFFF
WD2_BIT_DAC1_CH_D_OFS                        =          0

# Control Register 23: DAC1_E_F (offset 0x105C) 
WD2_BIT_DAC1_CH_E_MASK                       = 0xFFFF0000
WD2_BIT_DAC1_CH_E_OFS                        =         16
WD2_BIT_DAC1_CH_F_MASK                       = 0x0000FFFF
WD2_BIT_DAC1_CH_F_OFS                        =          0

# Control Register 24: DAC1_G_H (offset 0x1060) 
WD2_BIT_DAC1_CH_G_MASK                       = 0xFFFF0000
WD2_BIT_DAC1_CH_G_OFS                        =         16
WD2_BIT_DAC1_CH_H_MASK                       = 0x0000FFFF
WD2_BIT_DAC1_CH_H_OFS                        =          0

# Control Register 25: DAC2_A_B (offset 0x1064) 
WD2_BIT_DAC2_CH_A_MASK                       = 0xFFFF0000
WD2_BIT_DAC2_CH_A_OFS                        =         16
WD2_BIT_DAC2_CH_B_MASK                       = 0x0000FFFF
WD2_BIT_DAC2_CH_B_OFS                        =          0

# Control Register 26: DAC2_C_D (offset 0x1068) 
WD2_BIT_DAC2_CH_C_MASK                       = 0xFFFF0000
WD2_BIT_DAC2_CH_C_OFS                        =         16
WD2_BIT_DAC2_CH_D_MASK                       = 0x0000FFFF
WD2_BIT_DAC2_CH_D_OFS                        =          0

# Control Register 27: DAC2_E_F (offset 0x106C) 
WD2_BIT_DAC2_CH_E_MASK                       = 0xFFFF0000
WD2_BIT_DAC2_CH_E_OFS                        =         16
WD2_BIT_DAC2_CH_F_MASK                       = 0x0000FFFF
WD2_BIT_DAC2_CH_F_OFS                        =          0

# Control Register 28: DAC2_G_H (offset 0x1070) 
WD2_BIT_DAC2_CH_G_MASK                       = 0xFFFF0000
WD2_BIT_DAC2_CH_G_OFS                        =         16
WD2_BIT_DAC2_CH_H_MASK                       = 0x0000FFFF
WD2_BIT_DAC2_CH_H_OFS                        =          0

# Control Register 29: FE_CFG_0_1 (offset 0x1074) 
WD2_BIT_FE0_PZC_EN_MASK                      = 0x01000000
WD2_BIT_FE0_PZC_EN_OFS                       =         24
WD2_BIT_FE0_AMPLIFIER2_COMP_EN_MASK          = 0x00800000
WD2_BIT_FE0_AMPLIFIER2_COMP_EN_OFS           =         23
WD2_BIT_FE0_AMPLIFIER2_EN_MASK               = 0x00400000
WD2_BIT_FE0_AMPLIFIER2_EN_OFS                =         22
WD2_BIT_FE0_AMPLIFIER1_COMP_EN_MASK          = 0x00200000
WD2_BIT_FE0_AMPLIFIER1_COMP_EN_OFS           =         21
WD2_BIT_FE0_AMPLIFIER1_EN_MASK               = 0x00100000
WD2_BIT_FE0_AMPLIFIER1_EN_OFS                =         20
WD2_BIT_FE0_ATTENUATION_MASK                 = 0x000C0000
WD2_BIT_FE0_ATTENUATION_OFS                  =         18
WD2_BIT_FE0_MUX_MASK                         = 0x00030000
WD2_BIT_FE0_MUX_OFS                          =         16
WD2_BIT_FE1_PZC_EN_MASK                      = 0x00000100
WD2_BIT_FE1_PZC_EN_OFS                       =          8
WD2_BIT_FE1_AMPLIFIER2_COMP_EN_MASK          = 0x00000080
WD2_BIT_FE1_AMPLIFIER2_COMP_EN_OFS           =          7
WD2_BIT_FE1_AMPLIFIER2_EN_MASK               = 0x00000040
WD2_BIT_FE1_AMPLIFIER2_EN_OFS                =          6
WD2_BIT_FE1_AMPLIFIER1_COMP_EN_MASK          = 0x00000020
WD2_BIT_FE1_AMPLIFIER1_COMP_EN_OFS           =          5
WD2_BIT_FE1_AMPLIFIER1_EN_MASK               = 0x00000010
WD2_BIT_FE1_AMPLIFIER1_EN_OFS                =          4
WD2_BIT_FE1_ATTENUATION_MASK                 = 0x0000000C
WD2_BIT_FE1_ATTENUATION_OFS                  =          2
WD2_BIT_FE1_MUX_MASK                         = 0x00000003
WD2_BIT_FE1_MUX_OFS                          =          0

# Control Register 30: FE_CFG_2_3 (offset 0x1078) 
WD2_BIT_FE2_PZC_EN_MASK                      = 0x01000000
WD2_BIT_FE2_PZC_EN_OFS                       =         24
WD2_BIT_FE2_AMPLIFIER2_COMP_EN_MASK          = 0x00800000
WD2_BIT_FE2_AMPLIFIER2_COMP_EN_OFS           =         23
WD2_BIT_FE2_AMPLIFIER2_EN_MASK               = 0x00400000
WD2_BIT_FE2_AMPLIFIER2_EN_OFS                =         22
WD2_BIT_FE2_AMPLIFIER1_COMP_EN_MASK          = 0x00200000
WD2_BIT_FE2_AMPLIFIER1_COMP_EN_OFS           =         21
WD2_BIT_FE2_AMPLIFIER1_EN_MASK               = 0x00100000
WD2_BIT_FE2_AMPLIFIER1_EN_OFS                =         20
WD2_BIT_FE2_ATTENUATION_MASK                 = 0x000C0000
WD2_BIT_FE2_ATTENUATION_OFS                  =         18
WD2_BIT_FE2_MUX_MASK                         = 0x00030000
WD2_BIT_FE2_MUX_OFS                          =         16
WD2_BIT_FE3_PZC_EN_MASK                      = 0x00000100
WD2_BIT_FE3_PZC_EN_OFS                       =          8
WD2_BIT_FE3_AMPLIFIER2_COMP_EN_MASK          = 0x00000080
WD2_BIT_FE3_AMPLIFIER2_COMP_EN_OFS           =          7
WD2_BIT_FE3_AMPLIFIER2_EN_MASK               = 0x00000040
WD2_BIT_FE3_AMPLIFIER2_EN_OFS                =          6
WD2_BIT_FE3_AMPLIFIER1_COMP_EN_MASK          = 0x00000020
WD2_BIT_FE3_AMPLIFIER1_COMP_EN_OFS           =          5
WD2_BIT_FE3_AMPLIFIER1_EN_MASK               = 0x00000010
WD2_BIT_FE3_AMPLIFIER1_EN_OFS                =          4
WD2_BIT_FE3_ATTENUATION_MASK                 = 0x0000000C
WD2_BIT_FE3_ATTENUATION_OFS                  =          2
WD2_BIT_FE3_MUX_MASK                         = 0x00000003
WD2_BIT_FE3_MUX_OFS                          =          0

# Control Register 31: FE_CFG_4_5 (offset 0x107C) 
WD2_BIT_FE4_PZC_EN_MASK                      = 0x01000000
WD2_BIT_FE4_PZC_EN_OFS                       =         24
WD2_BIT_FE4_AMPLIFIER2_COMP_EN_MASK          = 0x00800000
WD2_BIT_FE4_AMPLIFIER2_COMP_EN_OFS           =         23
WD2_BIT_FE4_AMPLIFIER2_EN_MASK               = 0x00400000
WD2_BIT_FE4_AMPLIFIER2_EN_OFS                =         22
WD2_BIT_FE4_AMPLIFIER1_COMP_EN_MASK          = 0x00200000
WD2_BIT_FE4_AMPLIFIER1_COMP_EN_OFS           =         21
WD2_BIT_FE4_AMPLIFIER1_EN_MASK               = 0x00100000
WD2_BIT_FE4_AMPLIFIER1_EN_OFS                =         20
WD2_BIT_FE4_ATTENUATION_MASK                 = 0x000C0000
WD2_BIT_FE4_ATTENUATION_OFS                  =         18
WD2_BIT_FE4_MUX_MASK                         = 0x00030000
WD2_BIT_FE4_MUX_OFS                          =         16
WD2_BIT_FE5_PZC_EN_MASK                      = 0x00000100
WD2_BIT_FE5_PZC_EN_OFS                       =          8
WD2_BIT_FE5_AMPLIFIER2_COMP_EN_MASK          = 0x00000080
WD2_BIT_FE5_AMPLIFIER2_COMP_EN_OFS           =          7
WD2_BIT_FE5_AMPLIFIER2_EN_MASK               = 0x00000040
WD2_BIT_FE5_AMPLIFIER2_EN_OFS                =          6
WD2_BIT_FE5_AMPLIFIER1_COMP_EN_MASK          = 0x00000020
WD2_BIT_FE5_AMPLIFIER1_COMP_EN_OFS           =          5
WD2_BIT_FE5_AMPLIFIER1_EN_MASK               = 0x00000010
WD2_BIT_FE5_AMPLIFIER1_EN_OFS                =          4
WD2_BIT_FE5_ATTENUATION_MASK                 = 0x0000000C
WD2_BIT_FE5_ATTENUATION_OFS                  =          2
WD2_BIT_FE5_MUX_MASK                         = 0x00000003
WD2_BIT_FE5_MUX_OFS                          =          0

# Control Register 32: FE_CFG_6_7 (offset 0x1080) 
WD2_BIT_FE6_PZC_EN_MASK                      = 0x01000000
WD2_BIT_FE6_PZC_EN_OFS                       =         24
WD2_BIT_FE6_AMPLIFIER2_COMP_EN_MASK          = 0x00800000
WD2_BIT_FE6_AMPLIFIER2_COMP_EN_OFS           =         23
WD2_BIT_FE6_AMPLIFIER2_EN_MASK               = 0x00400000
WD2_BIT_FE6_AMPLIFIER2_EN_OFS                =         22
WD2_BIT_FE6_AMPLIFIER1_COMP_EN_MASK          = 0x00200000
WD2_BIT_FE6_AMPLIFIER1_COMP_EN_OFS           =         21
WD2_BIT_FE6_AMPLIFIER1_EN_MASK               = 0x00100000
WD2_BIT_FE6_AMPLIFIER1_EN_OFS                =         20
WD2_BIT_FE6_ATTENUATION_MASK                 = 0x000C0000
WD2_BIT_FE6_ATTENUATION_OFS                  =         18
WD2_BIT_FE6_MUX_MASK                         = 0x00030000
WD2_BIT_FE6_MUX_OFS                          =         16
WD2_BIT_FE7_PZC_EN_MASK                      = 0x00000100
WD2_BIT_FE7_PZC_EN_OFS                       =          8
WD2_BIT_FE7_AMPLIFIER2_COMP_EN_MASK          = 0x00000080
WD2_BIT_FE7_AMPLIFIER2_COMP_EN_OFS           =          7
WD2_BIT_FE7_AMPLIFIER2_EN_MASK               = 0x00000040
WD2_BIT_FE7_AMPLIFIER2_EN_OFS                =          6
WD2_BIT_FE7_AMPLIFIER1_COMP_EN_MASK          = 0x00000020
WD2_BIT_FE7_AMPLIFIER1_COMP_EN_OFS           =          5
WD2_BIT_FE7_AMPLIFIER1_EN_MASK               = 0x00000010
WD2_BIT_FE7_AMPLIFIER1_EN_OFS                =          4
WD2_BIT_FE7_ATTENUATION_MASK                 = 0x0000000C
WD2_BIT_FE7_ATTENUATION_OFS                  =          2
WD2_BIT_FE7_MUX_MASK                         = 0x00000003
WD2_BIT_FE7_MUX_OFS                          =          0

# Control Register 33: FE_CFG_8_9 (offset 0x1084) 
WD2_BIT_FE8_PZC_EN_MASK                      = 0x01000000
WD2_BIT_FE8_PZC_EN_OFS                       =         24
WD2_BIT_FE8_AMPLIFIER2_COMP_EN_MASK          = 0x00800000
WD2_BIT_FE8_AMPLIFIER2_COMP_EN_OFS           =         23
WD2_BIT_FE8_AMPLIFIER2_EN_MASK               = 0x00400000
WD2_BIT_FE8_AMPLIFIER2_EN_OFS                =         22
WD2_BIT_FE8_AMPLIFIER1_COMP_EN_MASK          = 0x00200000
WD2_BIT_FE8_AMPLIFIER1_COMP_EN_OFS           =         21
WD2_BIT_FE8_AMPLIFIER1_EN_MASK               = 0x00100000
WD2_BIT_FE8_AMPLIFIER1_EN_OFS                =         20
WD2_BIT_FE8_ATTENUATION_MASK                 = 0x000C0000
WD2_BIT_FE8_ATTENUATION_OFS                  =         18
WD2_BIT_FE8_MUX_MASK                         = 0x00030000
WD2_BIT_FE8_MUX_OFS                          =         16
WD2_BIT_FE9_PZC_EN_MASK                      = 0x00000100
WD2_BIT_FE9_PZC_EN_OFS                       =          8
WD2_BIT_FE9_AMPLIFIER2_COMP_EN_MASK          = 0x00000080
WD2_BIT_FE9_AMPLIFIER2_COMP_EN_OFS           =          7
WD2_BIT_FE9_AMPLIFIER2_EN_MASK               = 0x00000040
WD2_BIT_FE9_AMPLIFIER2_EN_OFS                =          6
WD2_BIT_FE9_AMPLIFIER1_COMP_EN_MASK          = 0x00000020
WD2_BIT_FE9_AMPLIFIER1_COMP_EN_OFS           =          5
WD2_BIT_FE9_AMPLIFIER1_EN_MASK               = 0x00000010
WD2_BIT_FE9_AMPLIFIER1_EN_OFS                =          4
WD2_BIT_FE9_ATTENUATION_MASK                 = 0x0000000C
WD2_BIT_FE9_ATTENUATION_OFS                  =          2
WD2_BIT_FE9_MUX_MASK                         = 0x00000003
WD2_BIT_FE9_MUX_OFS                          =          0

# Control Register 34: FE_CFG_10_11 (offset 0x1088) 
WD2_BIT_FE10_PZC_EN_MASK                     = 0x01000000
WD2_BIT_FE10_PZC_EN_OFS                      =         24
WD2_BIT_FE10_AMPLIFIER2_COMP_EN_MASK         = 0x00800000
WD2_BIT_FE10_AMPLIFIER2_COMP_EN_OFS          =         23
WD2_BIT_FE10_AMPLIFIER2_EN_MASK              = 0x00400000
WD2_BIT_FE10_AMPLIFIER2_EN_OFS               =         22
WD2_BIT_FE10_AMPLIFIER1_COMP_EN_MASK         = 0x00200000
WD2_BIT_FE10_AMPLIFIER1_COMP_EN_OFS          =         21
WD2_BIT_FE10_AMPLIFIER1_EN_MASK              = 0x00100000
WD2_BIT_FE10_AMPLIFIER1_EN_OFS               =         20
WD2_BIT_FE10_ATTENUATION_MASK                = 0x000C0000
WD2_BIT_FE10_ATTENUATION_OFS                 =         18
WD2_BIT_FE10_MUX_MASK                        = 0x00030000
WD2_BIT_FE10_MUX_OFS                         =         16
WD2_BIT_FE11_PZC_EN_MASK                     = 0x00000100
WD2_BIT_FE11_PZC_EN_OFS                      =          8
WD2_BIT_FE11_AMPLIFIER2_COMP_EN_MASK         = 0x00000080
WD2_BIT_FE11_AMPLIFIER2_COMP_EN_OFS          =          7
WD2_BIT_FE11_AMPLIFIER2_EN_MASK              = 0x00000040
WD2_BIT_FE11_AMPLIFIER2_EN_OFS               =          6
WD2_BIT_FE11_AMPLIFIER1_COMP_EN_MASK         = 0x00000020
WD2_BIT_FE11_AMPLIFIER1_COMP_EN_OFS          =          5
WD2_BIT_FE11_AMPLIFIER1_EN_MASK              = 0x00000010
WD2_BIT_FE11_AMPLIFIER1_EN_OFS               =          4
WD2_BIT_FE11_ATTENUATION_MASK                = 0x0000000C
WD2_BIT_FE11_ATTENUATION_OFS                 =          2
WD2_BIT_FE11_MUX_MASK                        = 0x00000003
WD2_BIT_FE11_MUX_OFS                         =          0

# Control Register 35: FE_CFG_12_13 (offset 0x108C) 
WD2_BIT_FE12_PZC_EN_MASK                     = 0x01000000
WD2_BIT_FE12_PZC_EN_OFS                      =         24
WD2_BIT_FE12_AMPLIFIER2_COMP_EN_MASK         = 0x00800000
WD2_BIT_FE12_AMPLIFIER2_COMP_EN_OFS          =         23
WD2_BIT_FE12_AMPLIFIER2_EN_MASK              = 0x00400000
WD2_BIT_FE12_AMPLIFIER2_EN_OFS               =         22
WD2_BIT_FE12_AMPLIFIER1_COMP_EN_MASK         = 0x00200000
WD2_BIT_FE12_AMPLIFIER1_COMP_EN_OFS          =         21
WD2_BIT_FE12_AMPLIFIER1_EN_MASK              = 0x00100000
WD2_BIT_FE12_AMPLIFIER1_EN_OFS               =         20
WD2_BIT_FE12_ATTENUATION_MASK                = 0x000C0000
WD2_BIT_FE12_ATTENUATION_OFS                 =         18
WD2_BIT_FE12_MUX_MASK                        = 0x00030000
WD2_BIT_FE12_MUX_OFS                         =         16
WD2_BIT_FE13_PZC_EN_MASK                     = 0x00000100
WD2_BIT_FE13_PZC_EN_OFS                      =          8
WD2_BIT_FE13_AMPLIFIER2_COMP_EN_MASK         = 0x00000080
WD2_BIT_FE13_AMPLIFIER2_COMP_EN_OFS          =          7
WD2_BIT_FE13_AMPLIFIER2_EN_MASK              = 0x00000040
WD2_BIT_FE13_AMPLIFIER2_EN_OFS               =          6
WD2_BIT_FE13_AMPLIFIER1_COMP_EN_MASK         = 0x00000020
WD2_BIT_FE13_AMPLIFIER1_COMP_EN_OFS          =          5
WD2_BIT_FE13_AMPLIFIER1_EN_MASK              = 0x00000010
WD2_BIT_FE13_AMPLIFIER1_EN_OFS               =          4
WD2_BIT_FE13_ATTENUATION_MASK                = 0x0000000C
WD2_BIT_FE13_ATTENUATION_OFS                 =          2
WD2_BIT_FE13_MUX_MASK                        = 0x00000003
WD2_BIT_FE13_MUX_OFS                         =          0

# Control Register 36: FE_CFG_14_15 (offset 0x1090) 
WD2_BIT_FE14_PZC_EN_MASK                     = 0x01000000
WD2_BIT_FE14_PZC_EN_OFS                      =         24
WD2_BIT_FE14_AMPLIFIER2_COMP_EN_MASK         = 0x00800000
WD2_BIT_FE14_AMPLIFIER2_COMP_EN_OFS          =         23
WD2_BIT_FE14_AMPLIFIER2_EN_MASK              = 0x00400000
WD2_BIT_FE14_AMPLIFIER2_EN_OFS               =         22
WD2_BIT_FE14_AMPLIFIER1_COMP_EN_MASK         = 0x00200000
WD2_BIT_FE14_AMPLIFIER1_COMP_EN_OFS          =         21
WD2_BIT_FE14_AMPLIFIER1_EN_MASK              = 0x00100000
WD2_BIT_FE14_AMPLIFIER1_EN_OFS               =         20
WD2_BIT_FE14_ATTENUATION_MASK                = 0x000C0000
WD2_BIT_FE14_ATTENUATION_OFS                 =         18
WD2_BIT_FE14_MUX_MASK                        = 0x00030000
WD2_BIT_FE14_MUX_OFS                         =         16
WD2_BIT_FE15_PZC_EN_MASK                     = 0x00000100
WD2_BIT_FE15_PZC_EN_OFS                      =          8
WD2_BIT_FE15_AMPLIFIER2_COMP_EN_MASK         = 0x00000080
WD2_BIT_FE15_AMPLIFIER2_COMP_EN_OFS          =          7
WD2_BIT_FE15_AMPLIFIER2_EN_MASK              = 0x00000040
WD2_BIT_FE15_AMPLIFIER2_EN_OFS               =          6
WD2_BIT_FE15_AMPLIFIER1_COMP_EN_MASK         = 0x00000020
WD2_BIT_FE15_AMPLIFIER1_COMP_EN_OFS          =          5
WD2_BIT_FE15_AMPLIFIER1_EN_MASK              = 0x00000010
WD2_BIT_FE15_AMPLIFIER1_EN_OFS               =          4
WD2_BIT_FE15_ATTENUATION_MASK                = 0x0000000C
WD2_BIT_FE15_ATTENUATION_OFS                 =          2
WD2_BIT_FE15_MUX_MASK                        = 0x00000003
WD2_BIT_FE15_MUX_OFS                         =          0

# Control Register 37: HV_U_TARGET_0 (offset 0x1094) 
WD2_BIT_HV_U_TARGET_0_MASK                   = 0xFFFFFFFF
WD2_BIT_HV_U_TARGET_0_OFS                    =          0

# Control Register 38: HV_U_TARGET_1 (offset 0x1098) 
WD2_BIT_HV_U_TARGET_1_MASK                   = 0xFFFFFFFF
WD2_BIT_HV_U_TARGET_1_OFS                    =          0

# Control Register 39: HV_U_TARGET_2 (offset 0x109C) 
WD2_BIT_HV_U_TARGET_2_MASK                   = 0xFFFFFFFF
WD2_BIT_HV_U_TARGET_2_OFS                    =          0

# Control Register 40: HV_U_TARGET_3 (offset 0x10A0) 
WD2_BIT_HV_U_TARGET_3_MASK                   = 0xFFFFFFFF
WD2_BIT_HV_U_TARGET_3_OFS                    =          0

# Control Register 41: HV_U_TARGET_4 (offset 0x10A4) 
WD2_BIT_HV_U_TARGET_4_MASK                   = 0xFFFFFFFF
WD2_BIT_HV_U_TARGET_4_OFS                    =          0

# Control Register 42: HV_U_TARGET_5 (offset 0x10A8) 
WD2_BIT_HV_U_TARGET_5_MASK                   = 0xFFFFFFFF
WD2_BIT_HV_U_TARGET_5_OFS                    =          0

# Control Register 43: HV_U_TARGET_6 (offset 0x10AC) 
WD2_BIT_HV_U_TARGET_6_MASK                   = 0xFFFFFFFF
WD2_BIT_HV_U_TARGET_6_OFS                    =          0

# Control Register 44: HV_U_TARGET_7 (offset 0x10B0) 
WD2_BIT_HV_U_TARGET_7_MASK                   = 0xFFFFFFFF
WD2_BIT_HV_U_TARGET_7_OFS                    =          0

# Control Register 45: HV_U_TARGET_8 (offset 0x10B4) 
WD2_BIT_HV_U_TARGET_8_MASK                   = 0xFFFFFFFF
WD2_BIT_HV_U_TARGET_8_OFS                    =          0

# Control Register 46: HV_U_TARGET_9 (offset 0x10B8) 
WD2_BIT_HV_U_TARGET_9_MASK                   = 0xFFFFFFFF
WD2_BIT_HV_U_TARGET_9_OFS                    =          0

# Control Register 47: HV_U_TARGET_10 (offset 0x10BC) 
WD2_BIT_HV_U_TARGET_10_MASK                  = 0xFFFFFFFF
WD2_BIT_HV_U_TARGET_10_OFS                   =          0

# Control Register 48: HV_U_TARGET_11 (offset 0x10C0) 
WD2_BIT_HV_U_TARGET_11_MASK                  = 0xFFFFFFFF
WD2_BIT_HV_U_TARGET_11_OFS                   =          0

# Control Register 49: HV_U_TARGET_12 (offset 0x10C4) 
WD2_BIT_HV_U_TARGET_12_MASK                  = 0xFFFFFFFF
WD2_BIT_HV_U_TARGET_12_OFS                   =          0

# Control Register 50: HV_U_TARGET_13 (offset 0x10C8) 
WD2_BIT_HV_U_TARGET_13_MASK                  = 0xFFFFFFFF
WD2_BIT_HV_U_TARGET_13_OFS                   =          0

# Control Register 51: HV_U_TARGET_14 (offset 0x10CC) 
WD2_BIT_HV_U_TARGET_14_MASK                  = 0xFFFFFFFF
WD2_BIT_HV_U_TARGET_14_OFS                   =          0

# Control Register 52: HV_U_TARGET_15 (offset 0x10D0) 
WD2_BIT_HV_U_TARGET_15_MASK                  = 0xFFFFFFFF
WD2_BIT_HV_U_TARGET_15_OFS                   =          0

# Control Register 53: HV_R_SHUNT (offset 0x10D4) 
WD2_BIT_HV_R_SHUNT_MASK                      = 0xFFFFFFFF
WD2_BIT_HV_R_SHUNT_OFS                       =          0

# Control Register 54: LMK_0 (offset 0x10D8) 
WD2_BIT_LMK0_RESET_MASK                      = 0x80000000
WD2_BIT_LMK0_RESET_OFS                       =         31
WD2_BIT_LMK0_CLKOUT0_MUX_MASK                = 0x00060000
WD2_BIT_LMK0_CLKOUT0_MUX_OFS                 =         17
WD2_BIT_LMK0_CLKOUT0_EN_MASK                 = 0x00010000
WD2_BIT_LMK0_CLKOUT0_EN_OFS                  =         16
WD2_BIT_LMK0_CLKOUT0_DIV_MASK                = 0x0000FF00
WD2_BIT_LMK0_CLKOUT0_DIV_OFS                 =          8
WD2_BIT_LMK0_CLKOUT0_DLY_MASK                = 0x000000F0
WD2_BIT_LMK0_CLKOUT0_DLY_OFS                 =          4

# Control Register 55: LMK_1 (offset 0x10DC) 
WD2_BIT_LMK1_CLKOUT1_MUX_MASK                = 0x00060000
WD2_BIT_LMK1_CLKOUT1_MUX_OFS                 =         17
WD2_BIT_LMK1_CLKOUT1_EN_MASK                 = 0x00010000
WD2_BIT_LMK1_CLKOUT1_EN_OFS                  =         16
WD2_BIT_LMK1_CLKOUT1_DIV_MASK                = 0x0000FF00
WD2_BIT_LMK1_CLKOUT1_DIV_OFS                 =          8
WD2_BIT_LMK1_CLKOUT1_DLY_MASK                = 0x000000F0
WD2_BIT_LMK1_CLKOUT1_DLY_OFS                 =          4

# Control Register 56: LMK_2 (offset 0x10E0) 
WD2_BIT_LMK2_CLKOUT2_MUX_MASK                = 0x00060000
WD2_BIT_LMK2_CLKOUT2_MUX_OFS                 =         17
WD2_BIT_LMK2_CLKOUT2_EN_MASK                 = 0x00010000
WD2_BIT_LMK2_CLKOUT2_EN_OFS                  =         16
WD2_BIT_LMK2_CLKOUT2_DIV_MASK                = 0x0000FF00
WD2_BIT_LMK2_CLKOUT2_DIV_OFS                 =          8
WD2_BIT_LMK2_CLKOUT2_DLY_MASK                = 0x000000F0
WD2_BIT_LMK2_CLKOUT2_DLY_OFS                 =          4

# Control Register 57: LMK_3 (offset 0x10E4) 
WD2_BIT_LMK3_CLKOUT3_MUX_MASK                = 0x00060000
WD2_BIT_LMK3_CLKOUT3_MUX_OFS                 =         17
WD2_BIT_LMK3_CLKOUT3_EN_MASK                 = 0x00010000
WD2_BIT_LMK3_CLKOUT3_EN_OFS                  =         16
WD2_BIT_LMK3_CLKOUT3_DIV_MASK                = 0x0000FF00
WD2_BIT_LMK3_CLKOUT3_DIV_OFS                 =          8
WD2_BIT_LMK3_CLKOUT3_DLY_MASK                = 0x000000F0
WD2_BIT_LMK3_CLKOUT3_DLY_OFS                 =          4

# Control Register 58: LMK_4 (offset 0x10E8) 
WD2_BIT_LMK4_CLKOUT4_MUX_MASK                = 0x00060000
WD2_BIT_LMK4_CLKOUT4_MUX_OFS                 =         17
WD2_BIT_LMK4_CLKOUT4_EN_MASK                 = 0x00010000
WD2_BIT_LMK4_CLKOUT4_EN_OFS                  =         16
WD2_BIT_LMK4_CLKOUT4_DIV_MASK                = 0x0000FF00
WD2_BIT_LMK4_CLKOUT4_DIV_OFS                 =          8
WD2_BIT_LMK4_CLKOUT4_DLY_MASK                = 0x000000F0
WD2_BIT_LMK4_CLKOUT4_DLY_OFS                 =          4

# Control Register 59: LMK_5 (offset 0x10EC) 
WD2_BIT_LMK5_CLKOUT5_MUX_MASK                = 0x00060000
WD2_BIT_LMK5_CLKOUT5_MUX_OFS                 =         17
WD2_BIT_LMK5_CLKOUT5_EN_MASK                 = 0x00010000
WD2_BIT_LMK5_CLKOUT5_EN_OFS                  =         16
WD2_BIT_LMK5_CLKOUT5_DIV_MASK                = 0x0000FF00
WD2_BIT_LMK5_CLKOUT5_DIV_OFS                 =          8
WD2_BIT_LMK5_CLKOUT5_DLY_MASK                = 0x000000F0
WD2_BIT_LMK5_CLKOUT5_DLY_OFS                 =          4

# Control Register 60: LMK_6 (offset 0x10F0) 
WD2_BIT_LMK6_CLKOUT6_MUX_MASK                = 0x00060000
WD2_BIT_LMK6_CLKOUT6_MUX_OFS                 =         17
WD2_BIT_LMK6_CLKOUT6_EN_MASK                 = 0x00010000
WD2_BIT_LMK6_CLKOUT6_EN_OFS                  =         16
WD2_BIT_LMK6_CLKOUT6_DIV_MASK                = 0x0000FF00
WD2_BIT_LMK6_CLKOUT6_DIV_OFS                 =          8
WD2_BIT_LMK6_CLKOUT6_DLY_MASK                = 0x000000F0
WD2_BIT_LMK6_CLKOUT6_DLY_OFS                 =          4

# Control Register 61: LMK_7 (offset 0x10F4) 
WD2_BIT_LMK7_CLKOUT7_MUX_MASK                = 0x00060000
WD2_BIT_LMK7_CLKOUT7_MUX_OFS                 =         17
WD2_BIT_LMK7_CLKOUT7_EN_MASK                 = 0x00010000
WD2_BIT_LMK7_CLKOUT7_EN_OFS                  =         16
WD2_BIT_LMK7_CLKOUT7_DIV_MASK                = 0x0000FF00
WD2_BIT_LMK7_CLKOUT7_DIV_OFS                 =          8
WD2_BIT_LMK7_CLKOUT7_DLY_MASK                = 0x000000F0
WD2_BIT_LMK7_CLKOUT7_DLY_OFS                 =          4

# Control Register 62: LMK_8 (offset 0x10F8) 
WD2_BIT_LMK8_PHASE_NOISE_OPT_MASK            = 0xFFFFFFF0
WD2_BIT_LMK8_PHASE_NOISE_OPT_OFS             =          4

# Control Register 63: LMK_9 (offset 0x10FC) 
WD2_BIT_LMK9_VBOOST_MASK                     = 0x00010000
WD2_BIT_LMK9_VBOOST_OFS                      =         16

# Control Register 64: LMK_11 (offset 0x1100) 
WD2_BIT_LMK11_DIV4_MASK                      = 0x00008000
WD2_BIT_LMK11_DIV4_OFS                       =         15

# Control Register 65: LMK_13 (offset 0x1104) 
WD2_BIT_LMK13_OSCIN_FREQ_MASK                = 0x003FC000
WD2_BIT_LMK13_OSCIN_FREQ_OFS                 =         14
WD2_BIT_LMK13_VCO_R4_LF_MASK                 = 0x00003800
WD2_BIT_LMK13_VCO_R4_LF_OFS                  =         11
WD2_BIT_LMK13_VCO_R3_LF_MASK                 = 0x00000700
WD2_BIT_LMK13_VCO_R3_LF_OFS                  =          8
WD2_BIT_LMK13_VCO_C3_C4_LF_MASK              = 0x000000F0
WD2_BIT_LMK13_VCO_C3_C4_LF_OFS               =          4

# Control Register 66: LMK_14 (offset 0x1108) 
WD2_BIT_LMK14_EN_FOUT_MASK                   = 0x10000000
WD2_BIT_LMK14_EN_FOUT_OFS                    =         28
WD2_BIT_LMK14_EN_CLKOUT_GLOBAL_MASK          = 0x08000000
WD2_BIT_LMK14_EN_CLKOUT_GLOBAL_OFS           =         27
WD2_BIT_LMK14_POWERDOWN_MASK                 = 0x04000000
WD2_BIT_LMK14_POWERDOWN_OFS                  =         26
WD2_BIT_LMK14_PLL_MUX_MASK                   = 0x00F00000
WD2_BIT_LMK14_PLL_MUX_OFS                    =         20
WD2_BIT_LMK14_PLL_R_MASK                     = 0x000FFF00
WD2_BIT_LMK14_PLL_R_OFS                      =          8

# Control Register 67: LMK_15 (offset 0x110C) 
WD2_BIT_LMK15_PLL_CP_GAIN_MASK               = 0xC0000000
WD2_BIT_LMK15_PLL_CP_GAIN_OFS                =         30
WD2_BIT_LMK15_VCO_DIV_MASK                   = 0x3C000000
WD2_BIT_LMK15_VCO_DIV_OFS                    =         26
WD2_BIT_LMK15_PLL_N_MASK                     = 0x03FFFF00
WD2_BIT_LMK15_PLL_N_OFS                      =          8

# Control Register 68: ADC_CFG_IND_TX (offset 0x1110) 
WD2_BIT_ADC_CFG_SDO_ACTIVE_MSB_MASK          = 0x80000000
WD2_BIT_ADC_CFG_SDO_ACTIVE_MSB_OFS           =         31
WD2_BIT_ADC_CFG_LSB_FIRST_MSB_MASK           = 0x40000000
WD2_BIT_ADC_CFG_LSB_FIRST_MSB_OFS            =         30
WD2_BIT_ADC_CFG_SOFT_RESET_MSB_MASK          = 0x20000000
WD2_BIT_ADC_CFG_SOFT_RESET_MSB_OFS           =         29
WD2_BIT_ADC_CFG_16_BIT_ADDR_MSB_MASK         = 0x10000000
WD2_BIT_ADC_CFG_16_BIT_ADDR_MSB_OFS          =         28
WD2_BIT_ADC_CFG_16_BIT_ADDR_LSB_MASK         = 0x08000000
WD2_BIT_ADC_CFG_16_BIT_ADDR_LSB_OFS          =         27
WD2_BIT_ADC_CFG_SOFT_RESET_LSB_MASK          = 0x04000000
WD2_BIT_ADC_CFG_SOFT_RESET_LSB_OFS           =         26
WD2_BIT_ADC_CFG_LSB_FIRST_LSB_MASK           = 0x02000000
WD2_BIT_ADC_CFG_LSB_FIRST_LSB_OFS            =         25
WD2_BIT_ADC_CFG_SDO_ACTIVE_LSB_MASK          = 0x01000000
WD2_BIT_ADC_CFG_SDO_ACTIVE_LSB_OFS           =         24
WD2_BIT_ADC_DI2_D_CHN_H_MASK                 = 0x00080000
WD2_BIT_ADC_DI2_D_CHN_H_OFS                  =         19
WD2_BIT_ADC_DI2_D_CHN_G_MASK                 = 0x00040000
WD2_BIT_ADC_DI2_D_CHN_G_OFS                  =         18
WD2_BIT_ADC_DI2_D_CHN_F_MASK                 = 0x00020000
WD2_BIT_ADC_DI2_D_CHN_F_OFS                  =         17
WD2_BIT_ADC_DI2_D_CHN_E_MASK                 = 0x00010000
WD2_BIT_ADC_DI2_D_CHN_E_OFS                  =         16
WD2_BIT_ADC_DI1_C_CHN_DCO_MASK               = 0x00002000
WD2_BIT_ADC_DI1_C_CHN_DCO_OFS                =         13
WD2_BIT_ADC_DI1_C_CHN_FCO_MASK               = 0x00001000
WD2_BIT_ADC_DI1_C_CHN_FCO_OFS                =         12
WD2_BIT_ADC_DI1_D_CHN_D_MASK                 = 0x00000800
WD2_BIT_ADC_DI1_D_CHN_D_OFS                  =         11
WD2_BIT_ADC_DI1_D_CHN_C_MASK                 = 0x00000400
WD2_BIT_ADC_DI1_D_CHN_C_OFS                  =         10
WD2_BIT_ADC_DI1_D_CHN_B_MASK                 = 0x00000200
WD2_BIT_ADC_DI1_D_CHN_B_OFS                  =          9
WD2_BIT_ADC_DI1_D_CHN_A_MASK                 = 0x00000100
WD2_BIT_ADC_DI1_D_CHN_A_OFS                  =          8
WD2_BIT_ADC_TX_INIT_OVERRIDE_MASK            = 0x00000001
WD2_BIT_ADC_TX_INIT_OVERRIDE_OFS             =          0

# Control Register 69: ADC_PM_CLK_ENH (offset 0x1114) 
WD2_BIT_ADC_PM_EXT_PD_MASK                   = 0x20000000
WD2_BIT_ADC_PM_EXT_PD_OFS                    =         29
WD2_BIT_ADC_PM_INT_PD_MODE_MASK              = 0x03000000
WD2_BIT_ADC_PM_INT_PD_MODE_OFS               =         24
WD2_BIT_ADC_CLK_DUTY_CYC_STAB_MASK           = 0x00010000
WD2_BIT_ADC_CLK_DUTY_CYC_STAB_OFS            =         16
WD2_BIT_ADC_CLK_DIV_RATIO_MASK               = 0x00000700
WD2_BIT_ADC_CLK_DIV_RATIO_OFS                =          8
WD2_BIT_ADC_ENH_CHOP_MODE_MASK               = 0x00000010
WD2_BIT_ADC_ENH_CHOP_MODE_OFS                =          4

# Control Register 70: ADC_TEST_OFFS_OM (offset 0x1118) 
WD2_BIT_ADC_TM_USR_IN_MODE_MASK              = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_OFS               =         22
WD2_BIT_ADC_TM_RST_PN_LONG_GEN_MASK          = 0x00200000
WD2_BIT_ADC_TM_RST_PN_LONG_GEN_OFS           =         21
WD2_BIT_ADC_TM_RST_PN_SHORT_GEN_MASK         = 0x00100000
WD2_BIT_ADC_TM_RST_PN_SHORT_GEN_OFS          =         20
WD2_BIT_ADC_TM_OUT_MASK                      = 0x000F0000
WD2_BIT_ADC_TM_OUT_OFS                       =         16
WD2_BIT_ADC_OFFS_ADJ_MASK                    = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_OFS                     =          8
WD2_BIT_ADC_OM_LVDS_MODE_MASK                = 0x00000040
WD2_BIT_ADC_OM_LVDS_MODE_OFS                 =          6
WD2_BIT_ADC_OM_OUT_INVERT_MASK               = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_OFS                =          2
WD2_BIT_ADC_OM_OUT_FORMAT_MASK               = 0x00000001
WD2_BIT_ADC_OM_OUT_FORMAT_OFS                =          0

# Control Register 71: ADC_OUT_VREF (offset 0x111C) 
WD2_BIT_ADC_OA_OUT_DRV_TERM_MASK             = 0x00300000
WD2_BIT_ADC_OA_OUT_DRV_TERM_OFS              =         20
WD2_BIT_ADC_OA_OUT_DRIVE_MASK                = 0x00010000
WD2_BIT_ADC_OA_OUT_DRIVE_OFS                 =         16
WD2_BIT_ADC_OP_IN_CLK_PH_ADJ_MASK            = 0x00007000
WD2_BIT_ADC_OP_IN_CLK_PH_ADJ_OFS             =         12
WD2_BIT_ADC_OP_OUT_CLK_PH_ADJ_MASK           = 0x00000F00
WD2_BIT_ADC_OP_OUT_CLK_PH_ADJ_OFS            =          8
WD2_BIT_ADC_INT_VREF_ADJ_MASK                = 0x00000007
WD2_BIT_ADC_INT_VREF_ADJ_OFS                 =          0

# Control Register 72: ADC_USR_PATT (offset 0x1120) 
WD2_BIT_ADC_USR_PATT1_MASK                   = 0xFFFF0000
WD2_BIT_ADC_USR_PATT1_OFS                    =         16
WD2_BIT_ADC_USR_PATT2_MASK                   = 0x0000FFFF
WD2_BIT_ADC_USR_PATT2_OFS                    =          0

# Control Register 73: ADC_SER_RES_SR (offset 0x1124) 
WD2_BIT_ADC_SC_LVDS_OUT_LSB_FIRST_MASK       = 0x00800000
WD2_BIT_ADC_SC_LVDS_OUT_LSB_FIRST_OFS        =         23
WD2_BIT_ADC_SC_WORD_WISE_DDR_MASK            = 0x00700000
WD2_BIT_ADC_SC_WORD_WISE_DDR_OFS             =         20
WD2_BIT_ADC_SC_OUT_NR_BITS_MASK              = 0x00030000
WD2_BIT_ADC_SC_OUT_NR_BITS_OFS               =         16
WD2_BIT_ADC_SC_OUT_RST_MASK                  = 0x00000200
WD2_BIT_ADC_SC_OUT_RST_OFS                   =          9
WD2_BIT_ADC_SC_PWR_DN_MASK                   = 0x00000100
WD2_BIT_ADC_SC_PWR_DN_OFS                    =          8
WD2_BIT_ADC_RES_SR_OVR_MASK                  = 0x00000040
WD2_BIT_ADC_RES_SR_OVR_OFS                   =          6
WD2_BIT_ADC_RESOLUTION_MASK                  = 0x00000030
WD2_BIT_ADC_RESOLUTION_OFS                   =          4
WD2_BIT_ADC_SAMPLE_RATE_MASK                 = 0x00000007
WD2_BIT_ADC_SAMPLE_RATE_OFS                  =          0

# Control Register 74: ADC_USR_IO_SYNC (offset 0x1128) 
WD2_BIT_ADC_UIOC2_SDIO_PD_MASK               = 0x00010000
WD2_BIT_ADC_UIOC2_SDIO_PD_OFS                =         16
WD2_BIT_ADC_UIOC3_VCM_PWR_DN_MASK            = 0x00000800
WD2_BIT_ADC_UIOC3_VCM_PWR_DN_OFS             =         11
WD2_BIT_ADC_SYNC_NEXT_ONLY_MASK              = 0x00000002
WD2_BIT_ADC_SYNC_NEXT_ONLY_OFS               =          1
WD2_BIT_ADC_EN_SYNC_MASK                     = 0x00000001
WD2_BIT_ADC_EN_SYNC_OFS                      =          0

# Control Register 75: ADC_0_CH_A_CFG (offset 0x112C) 
WD2_BIT_ADC_TM_USR_IN_MODE_0_A_MASK          = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_0_A_OFS           =         22
WD2_BIT_ADC_TM_OUT_0_A_MASK                  = 0x000F0000
WD2_BIT_ADC_TM_OUT_0_A_OFS                   =         16
WD2_BIT_ADC_OFFS_ADJ_0_A_MASK                = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_0_A_OFS                 =          8
WD2_BIT_ADC_OM_OUT_INVERT_0_A_MASK           = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_0_A_OFS            =          2

# Control Register 76: ADC_0_CH_B_CFG (offset 0x1130) 
WD2_BIT_ADC_TM_USR_IN_MODE_0_B_MASK          = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_0_B_OFS           =         22
WD2_BIT_ADC_TM_OUT_0_B_MASK                  = 0x000F0000
WD2_BIT_ADC_TM_OUT_0_B_OFS                   =         16
WD2_BIT_ADC_OFFS_ADJ_0_B_MASK                = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_0_B_OFS                 =          8
WD2_BIT_ADC_OM_OUT_INVERT_0_B_MASK           = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_0_B_OFS            =          2

# Control Register 77: ADC_0_CH_C_CFG (offset 0x1134) 
WD2_BIT_ADC_TM_USR_IN_MODE_0_C_MASK          = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_0_C_OFS           =         22
WD2_BIT_ADC_TM_OUT_0_C_MASK                  = 0x000F0000
WD2_BIT_ADC_TM_OUT_0_C_OFS                   =         16
WD2_BIT_ADC_OFFS_ADJ_0_C_MASK                = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_0_C_OFS                 =          8
WD2_BIT_ADC_OM_OUT_INVERT_0_C_MASK           = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_0_C_OFS            =          2

# Control Register 78: ADC_0_CH_D_CFG (offset 0x1138) 
WD2_BIT_ADC_TM_USR_IN_MODE_0_D_MASK          = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_0_D_OFS           =         22
WD2_BIT_ADC_TM_OUT_0_D_MASK                  = 0x000F0000
WD2_BIT_ADC_TM_OUT_0_D_OFS                   =         16
WD2_BIT_ADC_OFFS_ADJ_0_D_MASK                = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_0_D_OFS                 =          8
WD2_BIT_ADC_OM_OUT_INVERT_0_D_MASK           = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_0_D_OFS            =          2

# Control Register 79: ADC_0_CH_E_CFG (offset 0x113C) 
WD2_BIT_ADC_TM_USR_IN_MODE_0_E_MASK          = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_0_E_OFS           =         22
WD2_BIT_ADC_TM_OUT_0_E_MASK                  = 0x000F0000
WD2_BIT_ADC_TM_OUT_0_E_OFS                   =         16
WD2_BIT_ADC_OFFS_ADJ_0_E_MASK                = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_0_E_OFS                 =          8
WD2_BIT_ADC_OM_OUT_INVERT_0_E_MASK           = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_0_E_OFS            =          2

# Control Register 80: ADC_0_CH_F_CFG (offset 0x1140) 
WD2_BIT_ADC_TM_USR_IN_MODE_0_F_MASK          = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_0_F_OFS           =         22
WD2_BIT_ADC_TM_OUT_0_F_MASK                  = 0x000F0000
WD2_BIT_ADC_TM_OUT_0_F_OFS                   =         16
WD2_BIT_ADC_OFFS_ADJ_0_F_MASK                = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_0_F_OFS                 =          8
WD2_BIT_ADC_OM_OUT_INVERT_0_F_MASK           = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_0_F_OFS            =          2

# Control Register 81: ADC_0_CH_G_CFG (offset 0x1144) 
WD2_BIT_ADC_TM_USR_IN_MODE_0_G_MASK          = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_0_G_OFS           =         22
WD2_BIT_ADC_TM_OUT_0_G_MASK                  = 0x000F0000
WD2_BIT_ADC_TM_OUT_0_G_OFS                   =         16
WD2_BIT_ADC_OFFS_ADJ_0_G_MASK                = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_0_G_OFS                 =          8
WD2_BIT_ADC_OM_OUT_INVERT_0_G_MASK           = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_0_G_OFS            =          2

# Control Register 82: ADC_0_CH_H_CFG (offset 0x1148) 
WD2_BIT_ADC_TM_USR_IN_MODE_0_H_MASK          = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_0_H_OFS           =         22
WD2_BIT_ADC_TM_OUT_0_H_MASK                  = 0x000F0000
WD2_BIT_ADC_TM_OUT_0_H_OFS                   =         16
WD2_BIT_ADC_OFFS_ADJ_0_H_MASK                = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_0_H_OFS                 =          8
WD2_BIT_ADC_OM_OUT_INVERT_0_H_MASK           = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_0_H_OFS            =          2

# Control Register 83: ADC_0_CH_DCO_CFG (offset 0x114C) 
WD2_BIT_ADC_TM_USR_IN_MODE_0_DCO_MASK        = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_0_DCO_OFS         =         22
WD2_BIT_ADC_TM_OUT_0_DCO_MASK                = 0x000F0000
WD2_BIT_ADC_TM_OUT_0_DCO_OFS                 =         16
WD2_BIT_ADC_OFFS_ADJ_0_DCO_MASK              = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_0_DCO_OFS               =          8
WD2_BIT_ADC_OM_OUT_INVERT_0_DCO_MASK         = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_0_DCO_OFS          =          2

# Control Register 84: ADC_0_CH_FCO_CFG (offset 0x1150) 
WD2_BIT_ADC_TM_USR_IN_MODE_0_FCO_MASK        = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_0_FCO_OFS         =         22
WD2_BIT_ADC_TM_OUT_0_FCO_MASK                = 0x000F0000
WD2_BIT_ADC_TM_OUT_0_FCO_OFS                 =         16
WD2_BIT_ADC_OFFS_ADJ_0_FCO_MASK              = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_0_FCO_OFS               =          8
WD2_BIT_ADC_OM_OUT_INVERT_0_FCO_MASK         = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_0_FCO_OFS          =          2

# Control Register 85: ADC_1_CH_A_CFG (offset 0x1154) 
WD2_BIT_ADC_TM_USR_IN_MODE_1_A_MASK          = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_1_A_OFS           =         22
WD2_BIT_ADC_TM_OUT_1_A_MASK                  = 0x000F0000
WD2_BIT_ADC_TM_OUT_1_A_OFS                   =         16
WD2_BIT_ADC_OFFS_ADJ_1_A_MASK                = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_1_A_OFS                 =          8
WD2_BIT_ADC_OM_OUT_INVERT_1_A_MASK           = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_1_A_OFS            =          2

# Control Register 86: ADC_1_CH_B_CFG (offset 0x1158) 
WD2_BIT_ADC_TM_USR_IN_MODE_1_B_MASK          = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_1_B_OFS           =         22
WD2_BIT_ADC_TM_OUT_1_B_MASK                  = 0x000F0000
WD2_BIT_ADC_TM_OUT_1_B_OFS                   =         16
WD2_BIT_ADC_OFFS_ADJ_1_B_MASK                = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_1_B_OFS                 =          8
WD2_BIT_ADC_OM_OUT_INVERT_1_B_MASK           = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_1_B_OFS            =          2

# Control Register 87: ADC_1_CH_C_CFG (offset 0x115C) 
WD2_BIT_ADC_TM_USR_IN_MODE_1_C_MASK          = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_1_C_OFS           =         22
WD2_BIT_ADC_TM_OUT_1_C_MASK                  = 0x000F0000
WD2_BIT_ADC_TM_OUT_1_C_OFS                   =         16
WD2_BIT_ADC_OFFS_ADJ_1_C_MASK                = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_1_C_OFS                 =          8
WD2_BIT_ADC_OM_OUT_INVERT_1_C_MASK           = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_1_C_OFS            =          2

# Control Register 88: ADC_1_CH_D_CFG (offset 0x1160) 
WD2_BIT_ADC_TM_USR_IN_MODE_1_D_MASK          = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_1_D_OFS           =         22
WD2_BIT_ADC_TM_OUT_1_D_MASK                  = 0x000F0000
WD2_BIT_ADC_TM_OUT_1_D_OFS                   =         16
WD2_BIT_ADC_OFFS_ADJ_1_D_MASK                = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_1_D_OFS                 =          8
WD2_BIT_ADC_OM_OUT_INVERT_1_D_MASK           = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_1_D_OFS            =          2

# Control Register 89: ADC_1_CH_E_CFG (offset 0x1164) 
WD2_BIT_ADC_TM_USR_IN_MODE_1_E_MASK          = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_1_E_OFS           =         22
WD2_BIT_ADC_TM_OUT_1_E_MASK                  = 0x000F0000
WD2_BIT_ADC_TM_OUT_1_E_OFS                   =         16
WD2_BIT_ADC_OFFS_ADJ_1_E_MASK                = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_1_E_OFS                 =          8
WD2_BIT_ADC_OM_OUT_INVERT_1_E_MASK           = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_1_E_OFS            =          2

# Control Register 90: ADC_1_CH_F_CFG (offset 0x1168) 
WD2_BIT_ADC_TM_USR_IN_MODE_1_F_MASK          = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_1_F_OFS           =         22
WD2_BIT_ADC_TM_OUT_1_F_MASK                  = 0x000F0000
WD2_BIT_ADC_TM_OUT_1_F_OFS                   =         16
WD2_BIT_ADC_OFFS_ADJ_1_F_MASK                = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_1_F_OFS                 =          8
WD2_BIT_ADC_OM_OUT_INVERT_1_F_MASK           = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_1_F_OFS            =          2

# Control Register 91: ADC_1_CH_G_CFG (offset 0x116C) 
WD2_BIT_ADC_TM_USR_IN_MODE_1_G_MASK          = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_1_G_OFS           =         22
WD2_BIT_ADC_TM_OUT_1_G_MASK                  = 0x000F0000
WD2_BIT_ADC_TM_OUT_1_G_OFS                   =         16
WD2_BIT_ADC_OFFS_ADJ_1_G_MASK                = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_1_G_OFS                 =          8
WD2_BIT_ADC_OM_OUT_INVERT_1_G_MASK           = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_1_G_OFS            =          2

# Control Register 92: ADC_1_CH_H_CFG (offset 0x1170) 
WD2_BIT_ADC_TM_USR_IN_MODE_1_H_MASK          = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_1_H_OFS           =         22
WD2_BIT_ADC_TM_OUT_1_H_MASK                  = 0x000F0000
WD2_BIT_ADC_TM_OUT_1_H_OFS                   =         16
WD2_BIT_ADC_OFFS_ADJ_1_H_MASK                = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_1_H_OFS                 =          8
WD2_BIT_ADC_OM_OUT_INVERT_1_H_MASK           = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_1_H_OFS            =          2

# Control Register 93: ADC_1_CH_DCO_CFG (offset 0x1174) 
WD2_BIT_ADC_TM_USR_IN_MODE_1_DCO_MASK        = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_1_DCO_OFS         =         22
WD2_BIT_ADC_TM_OUT_1_DCO_MASK                = 0x000F0000
WD2_BIT_ADC_TM_OUT_1_DCO_OFS                 =         16
WD2_BIT_ADC_OFFS_ADJ_1_DCO_MASK              = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_1_DCO_OFS               =          8
WD2_BIT_ADC_OM_OUT_INVERT_1_DCO_MASK         = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_1_DCO_OFS          =          2

# Control Register 94: ADC_1_CH_FCO_CFG (offset 0x1178) 
WD2_BIT_ADC_TM_USR_IN_MODE_1_FCO_MASK        = 0x00C00000
WD2_BIT_ADC_TM_USR_IN_MODE_1_FCO_OFS         =         22
WD2_BIT_ADC_TM_OUT_1_FCO_MASK                = 0x000F0000
WD2_BIT_ADC_TM_OUT_1_FCO_OFS                 =         16
WD2_BIT_ADC_OFFS_ADJ_1_FCO_MASK              = 0x0000FF00
WD2_BIT_ADC_OFFS_ADJ_1_FCO_OFS               =          8
WD2_BIT_ADC_OM_OUT_INVERT_1_FCO_MASK         = 0x00000004
WD2_BIT_ADC_OM_OUT_INVERT_1_FCO_OFS          =          2

# Control Register 95: TRG_CFG (offset 0x117C) 
WD2_BIT_TRIGGER_SHAPER_ENABLE_MASK           = 0x08000000
WD2_BIT_TRIGGER_SHAPER_ENABLE_OFS            =         27
WD2_BIT_TRIGGER_OUT_PULSE_LENGTH_MASK        = 0x07000000
WD2_BIT_TRIGGER_OUT_PULSE_LENGTH_OFS         =         24
WD2_BIT_TRIGGER_ENABLE_MASK                  = 0x00080000
WD2_BIT_TRIGGER_ENABLE_OFS                   =         19
WD2_BIT_TRIGGER_FALLING_EDGE_MASK            = 0x00040000
WD2_BIT_TRIGGER_FALLING_EDGE_OFS             =         18
WD2_BIT_TRIGGER_CFG_EXT_OR_MASK              = 0x00020000
WD2_BIT_TRIGGER_CFG_EXT_OR_OFS               =         17
WD2_BIT_TRIGGER_CFG_EXT_AND_MASK             = 0x00010000
WD2_BIT_TRIGGER_CFG_EXT_AND_OFS              =         16
WD2_BIT_TRIGGER_DELAY_ENABLE_MASK            = 0x00000100
WD2_BIT_TRIGGER_DELAY_ENABLE_OFS             =          8
WD2_BIT_TRIGGER_DELAY_MASK                   = 0x000000FF
WD2_BIT_TRIGGER_DELAY_OFS                    =          0

# Control Register 96: TRG_COMP_MASK (offset 0x1180) 
WD2_BIT_TRIGGER_COMP_MASK_MASK               = 0x0000FFFF
WD2_BIT_TRIGGER_COMP_MASK_OFS                =          0

# Control Register 97: TRG_CH_CMB (offset 0x1184) 
WD2_BIT_TRIGGER_CFG_OR_MASK                  = 0xFFFF0000
WD2_BIT_TRIGGER_CFG_OR_OFS                   =         16
WD2_BIT_TRIGGER_CFG_AND_MASK                 = 0x0000FFFF
WD2_BIT_TRIGGER_CFG_AND_OFS                  =          0

# Control Register 98: TRG_SCH_SEL (offset 0x1188) 
WD2_BIT_PATTERN_TRIGGER_SELECT_MASK          = 0x00030000
WD2_BIT_PATTERN_TRIGGER_SELECT_OFS           =         16
WD2_BIT_BACKPLANE_TRIGGER0_MASK              = 0x0000C000
WD2_BIT_BACKPLANE_TRIGGER0_OFS               =         14
WD2_BIT_BACKPLANE_TRIGGER1_MASK              = 0x00003000
WD2_BIT_BACKPLANE_TRIGGER1_OFS               =         12
WD2_BIT_BACKPLANE_TRIGGER2_MASK              = 0x00000C00
WD2_BIT_BACKPLANE_TRIGGER2_OFS               =         10
WD2_BIT_BACKPLANE_TRIGGER3_MASK              = 0x00000300
WD2_BIT_BACKPLANE_TRIGGER3_OFS               =          8
WD2_BIT_BACKPLANE_TRIGGER4_MASK              = 0x000000C0
WD2_BIT_BACKPLANE_TRIGGER4_OFS               =          6
WD2_BIT_BACKPLANE_TRIGGER5_MASK              = 0x00000030
WD2_BIT_BACKPLANE_TRIGGER5_OFS               =          4
WD2_BIT_BACKPLANE_TRIGGER6_MASK              = 0x0000000C
WD2_BIT_BACKPLANE_TRIGGER6_OFS               =          2
WD2_BIT_BACKPLANE_TRIGGER7_MASK              = 0x00000003
WD2_BIT_BACKPLANE_TRIGGER7_OFS               =          0

# Control Register 99: TRG_PTRN_EN_LOCAL (offset 0x118C) 
WD2_BIT_TRG_PTRN_EN_LOCAL_MASK               = 0xFFFFFFFF
WD2_BIT_TRG_PTRN_EN_LOCAL_OFS                =          0

# Control Register 100: TRG_PTRN_EN_BPL0 (offset 0x1190) 
WD2_BIT_TRG_PTRN_EN_BPL0_MASK                = 0xFFFFFFFF
WD2_BIT_TRG_PTRN_EN_BPL0_OFS                 =          0

# Control Register 101: TRG_PTRN_EN_BPL1 (offset 0x1194) 
WD2_BIT_TRG_PTRN_EN_BPL1_MASK                = 0xFFFFFFFF
WD2_BIT_TRG_PTRN_EN_BPL1_OFS                 =          0

# Control Register 102: TRG_PTRN_EN_BPL2 (offset 0x1198) 
WD2_BIT_TRG_PTRN_EN_BPL2_MASK                = 0xFFFFFFFF
WD2_BIT_TRG_PTRN_EN_BPL2_OFS                 =          0

# Control Register 103: TRG_PTRN_EN_BPL3 (offset 0x119C) 
WD2_BIT_TRG_PTRN_EN_BPL3_MASK                = 0xFFFFFFFF
WD2_BIT_TRG_PTRN_EN_BPL3_OFS                 =          0

# Control Register 104: TRG_PTRN_EN_BPL4 (offset 0x11A0) 
WD2_BIT_TRG_PTRN_EN_BPL4_MASK                = 0xFFFFFFFF
WD2_BIT_TRG_PTRN_EN_BPL4_OFS                 =          0

# Control Register 105: TRG_PTRN_EN_BPL5 (offset 0x11A4) 
WD2_BIT_TRG_PTRN_EN_BPL5_MASK                = 0xFFFFFFFF
WD2_BIT_TRG_PTRN_EN_BPL5_OFS                 =          0

# Control Register 106: TRG_PTRN_EN_BPL6 (offset 0x11A8) 
WD2_BIT_TRG_PTRN_EN_BPL6_MASK                = 0xFFFFFFFF
WD2_BIT_TRG_PTRN_EN_BPL6_OFS                 =          0

# Control Register 107: TRG_PTRN_EN_BPL7 (offset 0x11AC) 
WD2_BIT_TRG_PTRN_EN_BPL7_MASK                = 0xFFFFFFFF
WD2_BIT_TRG_PTRN_EN_BPL7_OFS                 =          0

# Control Register 108: TRG_PTRN0 (offset 0x11B0) 
WD2_BIT_TRG_PTRN0_MASK                       = 0xFFFFFFFF
WD2_BIT_TRG_PTRN0_OFS                        =          0

# Control Register 109: TRG_PTRN1 (offset 0x11B4) 
WD2_BIT_TRG_PTRN1_MASK                       = 0xFFFFFFFF
WD2_BIT_TRG_PTRN1_OFS                        =          0

# Control Register 110: TRG_PTRN2 (offset 0x11B8) 
WD2_BIT_TRG_PTRN2_MASK                       = 0xFFFFFFFF
WD2_BIT_TRG_PTRN2_OFS                        =          0

# Control Register 111: TRG_PTRN3 (offset 0x11BC) 
WD2_BIT_TRG_PTRN3_MASK                       = 0xFFFFFFFF
WD2_BIT_TRG_PTRN3_OFS                        =          0

# Control Register 112: TRG_PTRN4 (offset 0x11C0) 
WD2_BIT_TRG_PTRN4_MASK                       = 0xFFFFFFFF
WD2_BIT_TRG_PTRN4_OFS                        =          0

# Control Register 113: TRG_PTRN5 (offset 0x11C4) 
WD2_BIT_TRG_PTRN5_MASK                       = 0xFFFFFFFF
WD2_BIT_TRG_PTRN5_OFS                        =          0

# Control Register 114: TRG_PTRN6 (offset 0x11C8) 
WD2_BIT_TRG_PTRN6_MASK                       = 0xFFFFFFFF
WD2_BIT_TRG_PTRN6_OFS                        =          0

# Control Register 115: TRG_PTRN7 (offset 0x11CC) 
WD2_BIT_TRG_PTRN7_MASK                       = 0xFFFFFFFF
WD2_BIT_TRG_PTRN7_OFS                        =          0

# Control Register 116: TRG_PTRN8 (offset 0x11D0) 
WD2_BIT_TRG_PTRN8_MASK                       = 0xFFFFFFFF
WD2_BIT_TRG_PTRN8_OFS                        =          0

# Control Register 117: TRG_PTRN9 (offset 0x11D4) 
WD2_BIT_TRG_PTRN9_MASK                       = 0xFFFFFFFF
WD2_BIT_TRG_PTRN9_OFS                        =          0

# Control Register 118: TRG_PTRN10 (offset 0x11D8) 
WD2_BIT_TRG_PTRN10_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN10_OFS                       =          0

# Control Register 119: TRG_PTRN11 (offset 0x11DC) 
WD2_BIT_TRG_PTRN11_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN11_OFS                       =          0

# Control Register 120: TRG_PTRN12 (offset 0x11E0) 
WD2_BIT_TRG_PTRN12_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN12_OFS                       =          0

# Control Register 121: TRG_PTRN13 (offset 0x11E4) 
WD2_BIT_TRG_PTRN13_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN13_OFS                       =          0

# Control Register 122: TRG_PTRN14 (offset 0x11E8) 
WD2_BIT_TRG_PTRN14_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN14_OFS                       =          0

# Control Register 123: TRG_PTRN15 (offset 0x11EC) 
WD2_BIT_TRG_PTRN15_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN15_OFS                       =          0

# Control Register 124: TRG_PTRN16 (offset 0x11F0) 
WD2_BIT_TRG_PTRN16_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN16_OFS                       =          0

# Control Register 125: TRG_PTRN17 (offset 0x11F4) 
WD2_BIT_TRG_PTRN17_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN17_OFS                       =          0

# Control Register 126: TRG_PTRN18 (offset 0x11F8) 
WD2_BIT_TRG_PTRN18_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN18_OFS                       =          0

# Control Register 127: TRG_PTRN19 (offset 0x11FC) 
WD2_BIT_TRG_PTRN19_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN19_OFS                       =          0

# Control Register 128: TRG_PTRN20 (offset 0x1200) 
WD2_BIT_TRG_PTRN20_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN20_OFS                       =          0

# Control Register 129: TRG_PTRN21 (offset 0x1204) 
WD2_BIT_TRG_PTRN21_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN21_OFS                       =          0

# Control Register 130: TRG_PTRN22 (offset 0x1208) 
WD2_BIT_TRG_PTRN22_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN22_OFS                       =          0

# Control Register 131: TRG_PTRN23 (offset 0x120C) 
WD2_BIT_TRG_PTRN23_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN23_OFS                       =          0

# Control Register 132: TRG_PTRN24 (offset 0x1210) 
WD2_BIT_TRG_PTRN24_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN24_OFS                       =          0

# Control Register 133: TRG_PTRN25 (offset 0x1214) 
WD2_BIT_TRG_PTRN25_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN25_OFS                       =          0

# Control Register 134: TRG_PTRN26 (offset 0x1218) 
WD2_BIT_TRG_PTRN26_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN26_OFS                       =          0

# Control Register 135: TRG_PTRN27 (offset 0x121C) 
WD2_BIT_TRG_PTRN27_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN27_OFS                       =          0

# Control Register 136: TRG_PTRN28 (offset 0x1220) 
WD2_BIT_TRG_PTRN28_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN28_OFS                       =          0

# Control Register 137: TRG_PTRN29 (offset 0x1224) 
WD2_BIT_TRG_PTRN29_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN29_OFS                       =          0

# Control Register 138: TRG_PTRN30 (offset 0x1228) 
WD2_BIT_TRG_PTRN30_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN30_OFS                       =          0

# Control Register 139: TRG_PTRN31 (offset 0x122C) 
WD2_BIT_TRG_PTRN31_MASK                      = 0xFFFFFFFF
WD2_BIT_TRG_PTRN31_OFS                       =          0

# Control Register 140: ADV_TRG_CFG0 (offset 0x1230) 
WD2_BIT_ADV_TRG_CFG_0_MASK                   = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_0_OFS                    =          0

# Control Register 141: ADV_TRG_CFG1 (offset 0x1234) 
WD2_BIT_ADV_TRG_CFG_1_MASK                   = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_1_OFS                    =          0

# Control Register 142: ADV_TRG_CFG2 (offset 0x1238) 
WD2_BIT_ADV_TRG_CFG_2_MASK                   = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_2_OFS                    =          0

# Control Register 143: ADV_TRG_CFG3 (offset 0x123C) 
WD2_BIT_ADV_TRG_CFG_3_MASK                   = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_3_OFS                    =          0

# Control Register 144: ADV_TRG_CFG4 (offset 0x1240) 
WD2_BIT_ADV_TRG_CFG_4_MASK                   = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_4_OFS                    =          0

# Control Register 145: ADV_TRG_CFG5 (offset 0x1244) 
WD2_BIT_ADV_TRG_CFG_5_MASK                   = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_5_OFS                    =          0

# Control Register 146: ADV_TRG_CFG6 (offset 0x1248) 
WD2_BIT_ADV_TRG_CFG_6_MASK                   = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_6_OFS                    =          0

# Control Register 147: ADV_TRG_CFG7 (offset 0x124C) 
WD2_BIT_ADV_TRG_CFG_7_MASK                   = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_7_OFS                    =          0

# Control Register 148: ADV_TRG_CFG8 (offset 0x1250) 
WD2_BIT_ADV_TRG_CFG_8_MASK                   = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_8_OFS                    =          0

# Control Register 149: ADV_TRG_CFG9 (offset 0x1254) 
WD2_BIT_ADV_TRG_CFG_9_MASK                   = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_9_OFS                    =          0

# Control Register 150: ADV_TRG_CFG10 (offset 0x1258) 
WD2_BIT_ADV_TRG_CFG_10_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_10_OFS                   =          0

# Control Register 151: ADV_TRG_CFG11 (offset 0x125C) 
WD2_BIT_ADV_TRG_CFG_11_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_11_OFS                   =          0

# Control Register 152: ADV_TRG_CFG12 (offset 0x1260) 
WD2_BIT_ADV_TRG_CFG_12_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_12_OFS                   =          0

# Control Register 153: ADV_TRG_CFG13 (offset 0x1264) 
WD2_BIT_ADV_TRG_CFG_13_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_13_OFS                   =          0

# Control Register 154: ADV_TRG_CFG14 (offset 0x1268) 
WD2_BIT_ADV_TRG_CFG_14_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_14_OFS                   =          0

# Control Register 155: ADV_TRG_CFG15 (offset 0x126C) 
WD2_BIT_ADV_TRG_CFG_15_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_15_OFS                   =          0

# Control Register 156: ADV_TRG_CFG16 (offset 0x1270) 
WD2_BIT_ADV_TRG_CFG_16_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_16_OFS                   =          0

# Control Register 157: ADV_TRG_CFG17 (offset 0x1274) 
WD2_BIT_ADV_TRG_CFG_17_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_17_OFS                   =          0

# Control Register 158: ADV_TRG_CFG18 (offset 0x1278) 
WD2_BIT_ADV_TRG_CFG_18_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_18_OFS                   =          0

# Control Register 159: ADV_TRG_CFG19 (offset 0x127C) 
WD2_BIT_ADV_TRG_CFG_19_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_19_OFS                   =          0

# Control Register 160: ADV_TRG_CFG20 (offset 0x1280) 
WD2_BIT_ADV_TRG_CFG_20_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_20_OFS                   =          0

# Control Register 161: ADV_TRG_CFG21 (offset 0x1284) 
WD2_BIT_ADV_TRG_CFG_21_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_21_OFS                   =          0

# Control Register 162: ADV_TRG_CFG22 (offset 0x1288) 
WD2_BIT_ADV_TRG_CFG_22_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_22_OFS                   =          0

# Control Register 163: ADV_TRG_CFG23 (offset 0x128C) 
WD2_BIT_ADV_TRG_CFG_23_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_23_OFS                   =          0

# Control Register 164: ADV_TRG_CFG24 (offset 0x1290) 
WD2_BIT_ADV_TRG_CFG_24_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_24_OFS                   =          0

# Control Register 165: ADV_TRG_CFG25 (offset 0x1294) 
WD2_BIT_ADV_TRG_CFG_25_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_25_OFS                   =          0

# Control Register 166: ADV_TRG_CFG26 (offset 0x1298) 
WD2_BIT_ADV_TRG_CFG_26_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_26_OFS                   =          0

# Control Register 167: ADV_TRG_CFG27 (offset 0x129C) 
WD2_BIT_ADV_TRG_CFG_27_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_27_OFS                   =          0

# Control Register 168: ADV_TRG_CFG28 (offset 0x12A0) 
WD2_BIT_ADV_TRG_CFG_28_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_28_OFS                   =          0

# Control Register 169: ADV_TRG_CFG29 (offset 0x12A4) 
WD2_BIT_ADV_TRG_CFG_29_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_CFG_29_OFS                   =          0

# Control Register 170: SET_TIME_LSB (offset 0x12A8) 
WD2_BIT_SET_TIME_LSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SET_TIME_LSB_OFS                     =          0

# Control Register 171: SET_TIME_MSB (offset 0x12AC) 
WD2_BIT_SET_TIME_MSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SET_TIME_MSB_OFS                     =          0

# Control Register 172: DBG_SIG_SEL (offset 0x12B0) 
WD2_BIT_MCX_TX_SIG_SEL_MASK                  = 0x000F0000
WD2_BIT_MCX_TX_SIG_SEL_OFS                   =         16
WD2_BIT_MCX_RX_SIG_SEL_MASK                  = 0x0000000F
WD2_BIT_MCX_RX_SIG_SEL_OFS                   =          0

# Control Register 173: CRC32_REG_BANK (offset 0x12B4) 
WD2_BIT_CRC32_REG_BANK_MASK                  = 0xFFFFFFFF
WD2_BIT_CRC32_REG_BANK_OFS                   =          0

# Status Register 0: HW_VER (offset 0x0000) 
WD2_BIT_BOARD_MAGIC_MASK                     = 0xFF000000
WD2_BIT_BOARD_MAGIC_OFS                      =         24
WD2_BIT_VENDOR_ID_MASK                       = 0x00FF0000
WD2_BIT_VENDOR_ID_OFS                        =         16
WD2_BIT_BOARD_TYPE_MASK                      = 0x0000FF00
WD2_BIT_BOARD_TYPE_OFS                       =          8
WD2_BIT_BOARD_REVISION_MASK                  = 0x000000FC
WD2_BIT_BOARD_REVISION_OFS                   =          2
WD2_BIT_BOARD_VARIANT_MASK                   = 0x00000003
WD2_BIT_BOARD_VARIANT_OFS                    =          0

# Status Register 1: REG_LAYOUT_VER (offset 0x0004) 
WD2_BIT_REG_LAYOUT_COMP_LEVEL_MASK           = 0xFFFF0000
WD2_BIT_REG_LAYOUT_COMP_LEVEL_OFS            =         16
WD2_BIT_REG_LAYOUT_VERSION_MASK              = 0x0000FFFF
WD2_BIT_REG_LAYOUT_VERSION_OFS               =          0

# Status Register 2: FW_BUILD_DATE (offset 0x0008) 
WD2_BIT_FW_BUILD_YEAR_MASK                   = 0xFFFF0000
WD2_BIT_FW_BUILD_YEAR_OFS                    =         16
WD2_BIT_FW_BUILD_MONTH_MASK                  = 0x0000FF00
WD2_BIT_FW_BUILD_MONTH_OFS                   =          8
WD2_BIT_FW_BUILD_DAY_MASK                    = 0x000000FF
WD2_BIT_FW_BUILD_DAY_OFS                     =          0

# Status Register 3: FW_BUILD_TIME (offset 0x000C) 
WD2_BIT_FW_COMPAT_LEVEL_MASK                 = 0xFF000000
WD2_BIT_FW_COMPAT_LEVEL_OFS                  =         24
WD2_BIT_FW_BUILD_HOUR_MASK                   = 0x00FF0000
WD2_BIT_FW_BUILD_HOUR_OFS                    =         16
WD2_BIT_FW_BUILD_MINUTE_MASK                 = 0x0000FF00
WD2_BIT_FW_BUILD_MINUTE_OFS                  =          8
WD2_BIT_FW_BUILD_SECOND_MASK                 = 0x000000FF
WD2_BIT_FW_BUILD_SECOND_OFS                  =          0

# Status Register 4: SW_BUILD_DATE (offset 0x0010) 
WD2_BIT_SW_BUILD_YEAR_MASK                   = 0xFFFF0000
WD2_BIT_SW_BUILD_YEAR_OFS                    =         16
WD2_BIT_SW_BUILD_MONTH_MASK                  = 0x0000FF00
WD2_BIT_SW_BUILD_MONTH_OFS                   =          8
WD2_BIT_SW_BUILD_DAY_MASK                    = 0x000000FF
WD2_BIT_SW_BUILD_DAY_OFS                     =          0

# Status Register 5: SW_BUILD_TIME (offset 0x0014) 
WD2_BIT_SW_BUILD_HOUR_MASK                   = 0x00FF0000
WD2_BIT_SW_BUILD_HOUR_OFS                    =         16
WD2_BIT_SW_BUILD_MINUTE_MASK                 = 0x0000FF00
WD2_BIT_SW_BUILD_MINUTE_OFS                  =          8
WD2_BIT_SW_BUILD_SECOND_MASK                 = 0x000000FF
WD2_BIT_SW_BUILD_SECOND_OFS                  =          0

# Status Register 6: GIT_HASH_TAG (offset 0x0018) 
WD2_BIT_GIT_HASH_TAG_MASK                    = 0xFFFFFFFF
WD2_BIT_GIT_HASH_TAG_OFS                     =          0

# Status Register 7: PROT_VER (offset 0x001C) 
WD2_BIT_PROTOCOL_VERSION_MASK                = 0x000000FF
WD2_BIT_PROTOCOL_VERSION_OFS                 =          0

# Status Register 8: SN (offset 0x0020) 
WD2_BIT_SERIAL_NUMBER_MASK                   = 0x0000FFFF
WD2_BIT_SERIAL_NUMBER_OFS                    =          0

# Status Register 9: STATUS (offset 0x0024) 
WD2_BIT_TEMPERATURE_MASK                     = 0xFFFF0000
WD2_BIT_TEMPERATURE_OFS                      =         16
WD2_BIT_FLASH_SEL_MASK                       = 0x00000200
WD2_BIT_FLASH_SEL_OFS                        =          9
WD2_BIT_BOARD_SEL_MASK                       = 0x00000100
WD2_BIT_BOARD_SEL_OFS                        =          8
WD2_BIT_DRS_CONFIG_DONE_MASK                 = 0x00000080
WD2_BIT_DRS_CONFIG_DONE_OFS                  =          7
WD2_BIT_SERIAL_BUSY_MASK                     = 0x00000040
WD2_BIT_SERIAL_BUSY_OFS                      =          6
WD2_BIT_SYS_BUSY_MASK                        = 0x00000020
WD2_BIT_SYS_BUSY_OFS                         =          5
WD2_BIT_WDB_BUSY_MASK                        = 0x00000010
WD2_BIT_WDB_BUSY_OFS                         =          4
WD2_BIT_HV_BOARD_PLUGGED_MASK                = 0x00000002
WD2_BIT_HV_BOARD_PLUGGED_OFS                 =          1
WD2_BIT_BACKPLANE_PLUGGED_MASK               = 0x00000001
WD2_BIT_BACKPLANE_PLUGGED_OFS                =          0

# Status Register 10: PLL_LOCK (offset 0x0028) 
WD2_BIT_SYS_DCM_LOCK_MASK                    = 0x00000100
WD2_BIT_SYS_DCM_LOCK_OFS                     =          8
WD2_BIT_DAQ_PLL_LOCK_MASK                    = 0x00000080
WD2_BIT_DAQ_PLL_LOCK_OFS                     =          7
WD2_BIT_OSERDES_PLL_LOCK_DCB_MASK            = 0x00000040
WD2_BIT_OSERDES_PLL_LOCK_DCB_OFS             =          6
WD2_BIT_OSERDES_PLL_LOCK_TCB_MASK            = 0x00000020
WD2_BIT_OSERDES_PLL_LOCK_TCB_OFS             =          5
WD2_BIT_ISERDES_PLL_LOCK_0_MASK              = 0x00000010
WD2_BIT_ISERDES_PLL_LOCK_0_OFS               =          4
WD2_BIT_ISERDES_PLL_LOCK_1_MASK              = 0x00000008
WD2_BIT_ISERDES_PLL_LOCK_1_OFS               =          3
WD2_BIT_DRS_PLL_LOCK_0_MASK                  = 0x00000004
WD2_BIT_DRS_PLL_LOCK_0_OFS                   =          2
WD2_BIT_DRS_PLL_LOCK_1_MASK                  = 0x00000002
WD2_BIT_DRS_PLL_LOCK_1_OFS                   =          1
WD2_BIT_LMK_PLL_LOCK_MASK                    = 0x00000001
WD2_BIT_LMK_PLL_LOCK_OFS                     =          0

# Status Register 11: DRS_STOP_CELL (offset 0x002C) 
WD2_BIT_DRS_STOP_CELL_0_MASK                 = 0x03FF0000
WD2_BIT_DRS_STOP_CELL_0_OFS                  =         16
WD2_BIT_DRS_STOP_CELL_1_MASK                 = 0x000003FF
WD2_BIT_DRS_STOP_CELL_1_OFS                  =          0

# Status Register 12: DRS_STOP_WSR (offset 0x0030) 
WD2_BIT_DRS_STOP_WSR_0_MASK                  = 0x0000FF00
WD2_BIT_DRS_STOP_WSR_0_OFS                   =          8
WD2_BIT_DRS_STOP_WSR_1_MASK                  = 0x000000FF
WD2_BIT_DRS_STOP_WSR_1_OFS                   =          0

# Status Register 13: DRS_SAMPLE_FREQ (offset 0x0034) 
WD2_BIT_DRS_SAMPLE_FREQ_MASK                 = 0x00FFFFFF
WD2_BIT_DRS_SAMPLE_FREQ_OFS                  =          0

# Status Register 14: ADC_SAMPLE_FREQ (offset 0x0038) 
WD2_BIT_ADC_SAMPLE_FREQ_MASK                 = 0x00FFFFFF
WD2_BIT_ADC_SAMPLE_FREQ_OFS                  =          0

# Status Register 15: TDC_SAMPLE_FREQ (offset 0x003C) 
WD2_BIT_TDC_SAMPLE_FREQ_MASK                 = 0x00FFFFFF
WD2_BIT_TDC_SAMPLE_FREQ_OFS                  =          0

# Status Register 16: ADC_INFO (offset 0x0040) 
WD2_BIT_ADC_0_CHIP_ID_MASK                   = 0xFF000000
WD2_BIT_ADC_0_CHIP_ID_OFS                    =         24
WD2_BIT_ADC_0_SPEED_MASK                     = 0x00700000
WD2_BIT_ADC_0_SPEED_OFS                      =         20
WD2_BIT_ADC_1_CHIP_ID_MASK                   = 0x0000FF00
WD2_BIT_ADC_1_CHIP_ID_OFS                    =          8
WD2_BIT_ADC_1_SPEED_MASK                     = 0x00000070
WD2_BIT_ADC_1_SPEED_OFS                      =          4

# Status Register 17: HV_VER (offset 0x0044) 
WD2_BIT_HV_VER_MASK                          = 0xFFFFFFFF
WD2_BIT_HV_VER_OFS                           =          0

# Status Register 18: HV_I_MEAS_0 (offset 0x0048) 
WD2_BIT_HV_I_MEAS_0_MASK                     = 0xFFFFFFFF
WD2_BIT_HV_I_MEAS_0_OFS                      =          0

# Status Register 19: HV_I_MEAS_1 (offset 0x004C) 
WD2_BIT_HV_I_MEAS_1_MASK                     = 0xFFFFFFFF
WD2_BIT_HV_I_MEAS_1_OFS                      =          0

# Status Register 20: HV_I_MEAS_2 (offset 0x0050) 
WD2_BIT_HV_I_MEAS_2_MASK                     = 0xFFFFFFFF
WD2_BIT_HV_I_MEAS_2_OFS                      =          0

# Status Register 21: HV_I_MEAS_3 (offset 0x0054) 
WD2_BIT_HV_I_MEAS_3_MASK                     = 0xFFFFFFFF
WD2_BIT_HV_I_MEAS_3_OFS                      =          0

# Status Register 22: HV_I_MEAS_4 (offset 0x0058) 
WD2_BIT_HV_I_MEAS_4_MASK                     = 0xFFFFFFFF
WD2_BIT_HV_I_MEAS_4_OFS                      =          0

# Status Register 23: HV_I_MEAS_5 (offset 0x005C) 
WD2_BIT_HV_I_MEAS_5_MASK                     = 0xFFFFFFFF
WD2_BIT_HV_I_MEAS_5_OFS                      =          0

# Status Register 24: HV_I_MEAS_6 (offset 0x0060) 
WD2_BIT_HV_I_MEAS_6_MASK                     = 0xFFFFFFFF
WD2_BIT_HV_I_MEAS_6_OFS                      =          0

# Status Register 25: HV_I_MEAS_7 (offset 0x0064) 
WD2_BIT_HV_I_MEAS_7_MASK                     = 0xFFFFFFFF
WD2_BIT_HV_I_MEAS_7_OFS                      =          0

# Status Register 26: HV_I_MEAS_8 (offset 0x0068) 
WD2_BIT_HV_I_MEAS_8_MASK                     = 0xFFFFFFFF
WD2_BIT_HV_I_MEAS_8_OFS                      =          0

# Status Register 27: HV_I_MEAS_9 (offset 0x006C) 
WD2_BIT_HV_I_MEAS_9_MASK                     = 0xFFFFFFFF
WD2_BIT_HV_I_MEAS_9_OFS                      =          0

# Status Register 28: HV_I_MEAS_10 (offset 0x0070) 
WD2_BIT_HV_I_MEAS_10_MASK                    = 0xFFFFFFFF
WD2_BIT_HV_I_MEAS_10_OFS                     =          0

# Status Register 29: HV_I_MEAS_11 (offset 0x0074) 
WD2_BIT_HV_I_MEAS_11_MASK                    = 0xFFFFFFFF
WD2_BIT_HV_I_MEAS_11_OFS                     =          0

# Status Register 30: HV_I_MEAS_12 (offset 0x0078) 
WD2_BIT_HV_I_MEAS_12_MASK                    = 0xFFFFFFFF
WD2_BIT_HV_I_MEAS_12_OFS                     =          0

# Status Register 31: HV_I_MEAS_13 (offset 0x007C) 
WD2_BIT_HV_I_MEAS_13_MASK                    = 0xFFFFFFFF
WD2_BIT_HV_I_MEAS_13_OFS                     =          0

# Status Register 32: HV_I_MEAS_14 (offset 0x0080) 
WD2_BIT_HV_I_MEAS_14_MASK                    = 0xFFFFFFFF
WD2_BIT_HV_I_MEAS_14_OFS                     =          0

# Status Register 33: HV_I_MEAS_15 (offset 0x0084) 
WD2_BIT_HV_I_MEAS_15_MASK                    = 0xFFFFFFFF
WD2_BIT_HV_I_MEAS_15_OFS                     =          0

# Status Register 34: HV_U_BASE_MEAS (offset 0x0088) 
WD2_BIT_HV_U_BASE_MEAS_MASK                  = 0xFFFFFFFF
WD2_BIT_HV_U_BASE_MEAS_OFS                   =          0

# Status Register 35: HV_TEMP_0 (offset 0x008C) 
WD2_BIT_HV_TEMP_0_MASK                       = 0xFFFFFFFF
WD2_BIT_HV_TEMP_0_OFS                        =          0

# Status Register 36: HV_TEMP_1 (offset 0x0090) 
WD2_BIT_HV_TEMP_1_MASK                       = 0xFFFFFFFF
WD2_BIT_HV_TEMP_1_OFS                        =          0

# Status Register 37: HV_TEMP_2 (offset 0x0094) 
WD2_BIT_HV_TEMP_2_MASK                       = 0xFFFFFFFF
WD2_BIT_HV_TEMP_2_OFS                        =          0

# Status Register 38: HV_TEMP_3 (offset 0x0098) 
WD2_BIT_HV_TEMP_3_MASK                       = 0xFFFFFFFF
WD2_BIT_HV_TEMP_3_OFS                        =          0

# Status Register 39: SCALER_0_LSB (offset 0x009C) 
WD2_BIT_SCALER_0_LSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SCALER_0_LSB_OFS                     =          0

# Status Register 40: SCALER_0_MSB (offset 0x00A0) 
WD2_BIT_SCALER_0_MSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SCALER_0_MSB_OFS                     =          0

# Status Register 41: SCALER_1_LSB (offset 0x00A4) 
WD2_BIT_SCALER_1_LSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SCALER_1_LSB_OFS                     =          0

# Status Register 42: SCALER_1_MSB (offset 0x00A8) 
WD2_BIT_SCALER_1_MSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SCALER_1_MSB_OFS                     =          0

# Status Register 43: SCALER_2_LSB (offset 0x00AC) 
WD2_BIT_SCALER_2_LSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SCALER_2_LSB_OFS                     =          0

# Status Register 44: SCALER_2_MSB (offset 0x00B0) 
WD2_BIT_SCALER_2_MSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SCALER_2_MSB_OFS                     =          0

# Status Register 45: SCALER_3_LSB (offset 0x00B4) 
WD2_BIT_SCALER_3_LSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SCALER_3_LSB_OFS                     =          0

# Status Register 46: SCALER_3_MSB (offset 0x00B8) 
WD2_BIT_SCALER_3_MSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SCALER_3_MSB_OFS                     =          0

# Status Register 47: SCALER_4_LSB (offset 0x00BC) 
WD2_BIT_SCALER_4_LSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SCALER_4_LSB_OFS                     =          0

# Status Register 48: SCALER_4_MSB (offset 0x00C0) 
WD2_BIT_SCALER_4_MSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SCALER_4_MSB_OFS                     =          0

# Status Register 49: SCALER_5_LSB (offset 0x00C4) 
WD2_BIT_SCALER_5_LSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SCALER_5_LSB_OFS                     =          0

# Status Register 50: SCALER_5_MSB (offset 0x00C8) 
WD2_BIT_SCALER_5_MSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SCALER_5_MSB_OFS                     =          0

# Status Register 51: SCALER_6_LSB (offset 0x00CC) 
WD2_BIT_SCALER_6_LSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SCALER_6_LSB_OFS                     =          0

# Status Register 52: SCALER_6_MSB (offset 0x00D0) 
WD2_BIT_SCALER_6_MSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SCALER_6_MSB_OFS                     =          0

# Status Register 53: SCALER_7_LSB (offset 0x00D4) 
WD2_BIT_SCALER_7_LSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SCALER_7_LSB_OFS                     =          0

# Status Register 54: SCALER_7_MSB (offset 0x00D8) 
WD2_BIT_SCALER_7_MSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SCALER_7_MSB_OFS                     =          0

# Status Register 55: SCALER_8_LSB (offset 0x00DC) 
WD2_BIT_SCALER_8_LSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SCALER_8_LSB_OFS                     =          0

# Status Register 56: SCALER_8_MSB (offset 0x00E0) 
WD2_BIT_SCALER_8_MSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SCALER_8_MSB_OFS                     =          0

# Status Register 57: SCALER_9_LSB (offset 0x00E4) 
WD2_BIT_SCALER_9_LSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SCALER_9_LSB_OFS                     =          0

# Status Register 58: SCALER_9_MSB (offset 0x00E8) 
WD2_BIT_SCALER_9_MSB_MASK                    = 0xFFFFFFFF
WD2_BIT_SCALER_9_MSB_OFS                     =          0

# Status Register 59: SCALER_10_LSB (offset 0x00EC) 
WD2_BIT_SCALER_10_LSB_MASK                   = 0xFFFFFFFF
WD2_BIT_SCALER_10_LSB_OFS                    =          0

# Status Register 60: SCALER_10_MSB (offset 0x00F0) 
WD2_BIT_SCALER_10_MSB_MASK                   = 0xFFFFFFFF
WD2_BIT_SCALER_10_MSB_OFS                    =          0

# Status Register 61: SCALER_11_LSB (offset 0x00F4) 
WD2_BIT_SCALER_11_LSB_MASK                   = 0xFFFFFFFF
WD2_BIT_SCALER_11_LSB_OFS                    =          0

# Status Register 62: SCALER_11_MSB (offset 0x00F8) 
WD2_BIT_SCALER_11_MSB_MASK                   = 0xFFFFFFFF
WD2_BIT_SCALER_11_MSB_OFS                    =          0

# Status Register 63: SCALER_12_LSB (offset 0x00FC) 
WD2_BIT_SCALER_12_LSB_MASK                   = 0xFFFFFFFF
WD2_BIT_SCALER_12_LSB_OFS                    =          0

# Status Register 64: SCALER_12_MSB (offset 0x0100) 
WD2_BIT_SCALER_12_MSB_MASK                   = 0xFFFFFFFF
WD2_BIT_SCALER_12_MSB_OFS                    =          0

# Status Register 65: SCALER_13_LSB (offset 0x0104) 
WD2_BIT_SCALER_13_LSB_MASK                   = 0xFFFFFFFF
WD2_BIT_SCALER_13_LSB_OFS                    =          0

# Status Register 66: SCALER_13_MSB (offset 0x0108) 
WD2_BIT_SCALER_13_MSB_MASK                   = 0xFFFFFFFF
WD2_BIT_SCALER_13_MSB_OFS                    =          0

# Status Register 67: SCALER_14_LSB (offset 0x010C) 
WD2_BIT_SCALER_14_LSB_MASK                   = 0xFFFFFFFF
WD2_BIT_SCALER_14_LSB_OFS                    =          0

# Status Register 68: SCALER_14_MSB (offset 0x0110) 
WD2_BIT_SCALER_14_MSB_MASK                   = 0xFFFFFFFF
WD2_BIT_SCALER_14_MSB_OFS                    =          0

# Status Register 69: SCALER_15_LSB (offset 0x0114) 
WD2_BIT_SCALER_15_LSB_MASK                   = 0xFFFFFFFF
WD2_BIT_SCALER_15_LSB_OFS                    =          0

# Status Register 70: SCALER_15_MSB (offset 0x0118) 
WD2_BIT_SCALER_15_MSB_MASK                   = 0xFFFFFFFF
WD2_BIT_SCALER_15_MSB_OFS                    =          0

# Status Register 71: SCALER_TRG (offset 0x011C) 
WD2_BIT_SCALER_TRG_MASK                      = 0xFFFFFFFF
WD2_BIT_SCALER_TRG_OFS                       =          0

# Status Register 72: SCALER_EXT_CLK (offset 0x0120) 
WD2_BIT_SCALER_EXT_CLK_MASK                  = 0xFFFFFFFF
WD2_BIT_SCALER_EXT_CLK_OFS                   =          0

# Status Register 73: TIME_LSB (offset 0x0124) 
WD2_BIT_TIME_LSB_MASK                        = 0xFFFFFFFF
WD2_BIT_TIME_LSB_OFS                         =          0

# Status Register 74: TIME_MSB (offset 0x0128) 
WD2_BIT_TIME_MSB_MASK                        = 0xFFFFFFFF
WD2_BIT_TIME_MSB_OFS                         =          0

# Status Register 75: COMP_CH_STAT (offset 0x012C) 
WD2_BIT_COMP_CH_STAT_MASK                    = 0x0000FFFF
WD2_BIT_COMP_CH_STAT_OFS                     =          0

# Status Register 76: EVENT_NR (offset 0x0130) 
WD2_BIT_EVENT_NUMBER_MASK                    = 0xFFFFFFFF
WD2_BIT_EVENT_NUMBER_OFS                     =          0

# Status Register 77: TRB_PARITY_ERR (offset 0x0134) 
WD2_BIT_TRB_PARITY_ERROR_COUNT_MASK          = 0x0000FFFF
WD2_BIT_TRB_PARITY_ERROR_COUNT_OFS           =          0

# Status Register 78: TRB_INFO (offset 0x0138) 
WD2_BIT_TRB_TYPE_MASK                        = 0xFFFF0000
WD2_BIT_TRB_TYPE_OFS                         =         16
WD2_BIT_TRB_NUMBER_MASK                      = 0x0000FFFF
WD2_BIT_TRB_NUMBER_OFS                       =          0

# Status Register 79: ADV_TRG_STAT0 (offset 0x013C) 
WD2_BIT_ADV_TRG_STAT_0_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_STAT_0_OFS                   =          0

# Status Register 80: ADV_TRG_STAT1 (offset 0x0140) 
WD2_BIT_ADV_TRG_STAT_1_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_STAT_1_OFS                   =          0

# Status Register 81: ADV_TRG_STAT2 (offset 0x0144) 
WD2_BIT_ADV_TRG_STAT_2_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_STAT_2_OFS                   =          0

# Status Register 82: ADV_TRG_STAT3 (offset 0x0148) 
WD2_BIT_ADV_TRG_STAT_3_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_STAT_3_OFS                   =          0

# Status Register 83: ADV_TRG_STAT4 (offset 0x014C) 
WD2_BIT_ADV_TRG_STAT_4_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_STAT_4_OFS                   =          0

# Status Register 84: ADV_TRG_STAT5 (offset 0x0150) 
WD2_BIT_ADV_TRG_STAT_5_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_STAT_5_OFS                   =          0

# Status Register 85: ADV_TRG_STAT6 (offset 0x0154) 
WD2_BIT_ADV_TRG_STAT_6_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_STAT_6_OFS                   =          0

# Status Register 86: ADV_TRG_STAT7 (offset 0x0158) 
WD2_BIT_ADV_TRG_STAT_7_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_STAT_7_OFS                   =          0

# Status Register 87: ADV_TRG_STAT8 (offset 0x015C) 
WD2_BIT_ADV_TRG_STAT_8_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_STAT_8_OFS                   =          0

# Status Register 88: ADV_TRG_STAT9 (offset 0x0160) 
WD2_BIT_ADV_TRG_STAT_9_MASK                  = 0xFFFFFFFF
WD2_BIT_ADV_TRG_STAT_9_OFS                   =          0

# Status Register 89: MAX_DRS_ADC_PKT_SAMPLES (offset 0x0164) 
WD2_BIT_MAX_DRS_ADC_PKT_SAMPLES_MASK         = 0x0000FFFF
WD2_BIT_MAX_DRS_ADC_PKT_SAMPLES_OFS          =          0

# Status Register 90: MAX_TDC_PKT_SAMPLES (offset 0x0168) 
WD2_BIT_MAX_TDC_PKT_SAMPLES_MASK             = 0x0003FFFF
WD2_BIT_MAX_TDC_PKT_SAMPLES_OFS              =          0

# Status Register 91: MAX_TRG_PKT_SAMPLES (offset 0x016C) 
WD2_BIT_MAX_TRG_PKT_SAMPLES_MASK             = 0x0000FFFF
WD2_BIT_MAX_TRG_PKT_SAMPLES_OFS              =          0

# Status Register 92: MAX_SCL_PKT_SAMPLES (offset 0x0170) 
WD2_BIT_MAX_SCL_PKT_SAMPLES_MASK             = 0x0000FFFF
WD2_BIT_MAX_SCL_PKT_SAMPLES_OFS              =          0

# Status Register 93: CLK_CTRL_MOD_FLAG (offset 0x0174) 
WD2_BIT_CLK_SEL_AND_DRS_CLK_DIV_MOD_MASK     = 0x00000004
WD2_BIT_CLK_SEL_AND_DRS_CLK_DIV_MOD_OFS      =          2
WD2_BIT_EXT_CLK_FREQ_MOD_MASK                = 0x00000002
WD2_BIT_EXT_CLK_FREQ_MOD_OFS                 =          1
WD2_BIT_LOCAL_CLK_FREQ_MOD_MASK              = 0x00000001
WD2_BIT_LOCAL_CLK_FREQ_MOD_OFS               =          0

# Status Register 94: DRS_MOD_FLAG (offset 0x0178) 
WD2_BIT_DRS_CTRL_MOD_MASK                    = 0x00000004
WD2_BIT_DRS_CTRL_MOD_OFS                     =          2
WD2_BIT_DRS_WSR_MOD_MASK                     = 0x00000002
WD2_BIT_DRS_WSR_MOD_OFS                      =          1
WD2_BIT_DRS_WCR_MOD_MASK                     = 0x00000001
WD2_BIT_DRS_WCR_MOD_OFS                      =          0

# Status Register 95: COM_PLD_SIZE_MOD_FLAG (offset 0x017C) 
WD2_BIT_COM_PLD_SIZE_MOD_MASK                = 0x0000000F
WD2_BIT_COM_PLD_SIZE_MOD_OFS                 =          0

# Status Register 96: ADC_SAMPLE_DIV_MOD_FLAG (offset 0x0180) 
WD2_BIT_ADC_SAMPLE_DIV_MOD_MASK              = 0x0000000F
WD2_BIT_ADC_SAMPLE_DIV_MOD_OFS               =          0

# Status Register 97: DAC_0_1_MOD_FLAG (offset 0x0184) 
WD2_BIT_DAC0_A_MOD_MASK                      = 0xC0000000
WD2_BIT_DAC0_A_MOD_OFS                       =         30
WD2_BIT_DAC0_B_MOD_MASK                      = 0x30000000
WD2_BIT_DAC0_B_MOD_OFS                       =         28
WD2_BIT_DAC0_C_MOD_MASK                      = 0x0C000000
WD2_BIT_DAC0_C_MOD_OFS                       =         26
WD2_BIT_DAC0_D_MOD_MASK                      = 0x03000000
WD2_BIT_DAC0_D_MOD_OFS                       =         24
WD2_BIT_DAC0_E_MOD_MASK                      = 0x00C00000
WD2_BIT_DAC0_E_MOD_OFS                       =         22
WD2_BIT_DAC0_F_MOD_MASK                      = 0x00300000
WD2_BIT_DAC0_F_MOD_OFS                       =         20
WD2_BIT_DAC0_G_MOD_MASK                      = 0x000C0000
WD2_BIT_DAC0_G_MOD_OFS                       =         18
WD2_BIT_DAC0_H_MOD_MASK                      = 0x00030000
WD2_BIT_DAC0_H_MOD_OFS                       =         16
WD2_BIT_DAC1_A_MOD_MASK                      = 0x0000C000
WD2_BIT_DAC1_A_MOD_OFS                       =         14
WD2_BIT_DAC1_B_MOD_MASK                      = 0x00003000
WD2_BIT_DAC1_B_MOD_OFS                       =         12
WD2_BIT_DAC1_C_MOD_MASK                      = 0x00000C00
WD2_BIT_DAC1_C_MOD_OFS                       =         10
WD2_BIT_DAC1_D_MOD_MASK                      = 0x00000300
WD2_BIT_DAC1_D_MOD_OFS                       =          8
WD2_BIT_DAC1_E_MOD_MASK                      = 0x000000C0
WD2_BIT_DAC1_E_MOD_OFS                       =          6
WD2_BIT_DAC1_F_MOD_MASK                      = 0x00000030
WD2_BIT_DAC1_F_MOD_OFS                       =          4
WD2_BIT_DAC1_G_MOD_MASK                      = 0x0000000C
WD2_BIT_DAC1_G_MOD_OFS                       =          2
WD2_BIT_DAC1_H_MOD_MASK                      = 0x00000003
WD2_BIT_DAC1_H_MOD_OFS                       =          0

# Status Register 98: DAC_2_MOD_FLAG (offset 0x0188) 
WD2_BIT_DAC2_A_MOD_MASK                      = 0xC0000000
WD2_BIT_DAC2_A_MOD_OFS                       =         30
WD2_BIT_DAC2_B_MOD_MASK                      = 0x30000000
WD2_BIT_DAC2_B_MOD_OFS                       =         28
WD2_BIT_DAC2_C_MOD_MASK                      = 0x0C000000
WD2_BIT_DAC2_C_MOD_OFS                       =         26
WD2_BIT_DAC2_D_MOD_MASK                      = 0x03000000
WD2_BIT_DAC2_D_MOD_OFS                       =         24
WD2_BIT_DAC2_E_MOD_MASK                      = 0x00C00000
WD2_BIT_DAC2_E_MOD_OFS                       =         22
WD2_BIT_DAC2_F_MOD_MASK                      = 0x00300000
WD2_BIT_DAC2_F_MOD_OFS                       =         20
WD2_BIT_DAC2_G_MOD_MASK                      = 0x000C0000
WD2_BIT_DAC2_G_MOD_OFS                       =         18
WD2_BIT_DAC2_H_MOD_MASK                      = 0x00030000
WD2_BIT_DAC2_H_MOD_OFS                       =         16

# Status Register 99: FE_0_15_MOD_FLAG (offset 0x018C) 
WD2_BIT_FE_0_MOD_MASK                        = 0xC0000000
WD2_BIT_FE_0_MOD_OFS                         =         30
WD2_BIT_FE_1_MOD_MASK                        = 0x30000000
WD2_BIT_FE_1_MOD_OFS                         =         28
WD2_BIT_FE_2_MOD_MASK                        = 0x0C000000
WD2_BIT_FE_2_MOD_OFS                         =         26
WD2_BIT_FE_3_MOD_MASK                        = 0x03000000
WD2_BIT_FE_3_MOD_OFS                         =         24
WD2_BIT_FE_4_MOD_MASK                        = 0x00C00000
WD2_BIT_FE_4_MOD_OFS                         =         22
WD2_BIT_FE_5_MOD_MASK                        = 0x00300000
WD2_BIT_FE_5_MOD_OFS                         =         20
WD2_BIT_FE_6_MOD_MASK                        = 0x000C0000
WD2_BIT_FE_6_MOD_OFS                         =         18
WD2_BIT_FE_7_MOD_MASK                        = 0x00030000
WD2_BIT_FE_7_MOD_OFS                         =         16
WD2_BIT_FE_8_MOD_MASK                        = 0x0000C000
WD2_BIT_FE_8_MOD_OFS                         =         14
WD2_BIT_FE_9_MOD_MASK                        = 0x00003000
WD2_BIT_FE_9_MOD_OFS                         =         12
WD2_BIT_FE_10_MOD_MASK                       = 0x00000C00
WD2_BIT_FE_10_MOD_OFS                        =         10
WD2_BIT_FE_11_MOD_MASK                       = 0x00000300
WD2_BIT_FE_11_MOD_OFS                        =          8
WD2_BIT_FE_12_MOD_MASK                       = 0x000000C0
WD2_BIT_FE_12_MOD_OFS                        =          6
WD2_BIT_FE_13_MOD_MASK                       = 0x00000030
WD2_BIT_FE_13_MOD_OFS                        =          4
WD2_BIT_FE_14_MOD_MASK                       = 0x0000000C
WD2_BIT_FE_14_MOD_OFS                        =          2
WD2_BIT_FE_15_MOD_MASK                       = 0x00000003
WD2_BIT_FE_15_MOD_OFS                        =          0

# Status Register 100: HV_U_TARGET_0_7_MOD_FLAG (offset 0x0190) 
WD2_BIT_HV_U_TARGET_0_MOD_MASK               = 0xF0000000
WD2_BIT_HV_U_TARGET_0_MOD_OFS                =         28
WD2_BIT_HV_U_TARGET_1_MOD_MASK               = 0x0F000000
WD2_BIT_HV_U_TARGET_1_MOD_OFS                =         24
WD2_BIT_HV_U_TARGET_2_MOD_MASK               = 0x00F00000
WD2_BIT_HV_U_TARGET_2_MOD_OFS                =         20
WD2_BIT_HV_U_TARGET_3_MOD_MASK               = 0x000F0000
WD2_BIT_HV_U_TARGET_3_MOD_OFS                =         16
WD2_BIT_HV_U_TARGET_4_MOD_MASK               = 0x0000F000
WD2_BIT_HV_U_TARGET_4_MOD_OFS                =         12
WD2_BIT_HV_U_TARGET_5_MOD_MASK               = 0x00000F00
WD2_BIT_HV_U_TARGET_5_MOD_OFS                =          8
WD2_BIT_HV_U_TARGET_6_MOD_MASK               = 0x000000F0
WD2_BIT_HV_U_TARGET_6_MOD_OFS                =          4
WD2_BIT_HV_U_TARGET_7_MOD_MASK               = 0x0000000F
WD2_BIT_HV_U_TARGET_7_MOD_OFS                =          0

# Status Register 101: HV_U_TARGET_8_15_MOD_FLAG (offset 0x0194) 
WD2_BIT_HV_U_TARGET_8_MOD_MASK               = 0xF0000000
WD2_BIT_HV_U_TARGET_8_MOD_OFS                =         28
WD2_BIT_HV_U_TARGET_9_MOD_MASK               = 0x0F000000
WD2_BIT_HV_U_TARGET_9_MOD_OFS                =         24
WD2_BIT_HV_U_TARGET_10_MOD_MASK              = 0x00F00000
WD2_BIT_HV_U_TARGET_10_MOD_OFS               =         20
WD2_BIT_HV_U_TARGET_11_MOD_MASK              = 0x000F0000
WD2_BIT_HV_U_TARGET_11_MOD_OFS               =         16
WD2_BIT_HV_U_TARGET_12_MOD_MASK              = 0x0000F000
WD2_BIT_HV_U_TARGET_12_MOD_OFS               =         12
WD2_BIT_HV_U_TARGET_13_MOD_MASK              = 0x00000F00
WD2_BIT_HV_U_TARGET_13_MOD_OFS               =          8
WD2_BIT_HV_U_TARGET_14_MOD_MASK              = 0x000000F0
WD2_BIT_HV_U_TARGET_14_MOD_OFS               =          4
WD2_BIT_HV_U_TARGET_15_MOD_MASK              = 0x0000000F
WD2_BIT_HV_U_TARGET_15_MOD_OFS               =          0

# Status Register 102: HV_MOD_FLAG (offset 0x0198) 
WD2_BIT_HV_R_SHUNT_MOD_MASK                  = 0x0000000F
WD2_BIT_HV_R_SHUNT_MOD_OFS                   =          0

# Status Register 103: LMK_0_7_MOD_FLAG (offset 0x019C) 
WD2_BIT_LMK_0_MOD_MASK                       = 0xF0000000
WD2_BIT_LMK_0_MOD_OFS                        =         28
WD2_BIT_LMK_1_MOD_MASK                       = 0x0F000000
WD2_BIT_LMK_1_MOD_OFS                        =         24
WD2_BIT_LMK_2_MOD_MASK                       = 0x00F00000
WD2_BIT_LMK_2_MOD_OFS                        =         20
WD2_BIT_LMK_3_MOD_MASK                       = 0x000F0000
WD2_BIT_LMK_3_MOD_OFS                        =         16
WD2_BIT_LMK_4_MOD_MASK                       = 0x0000F000
WD2_BIT_LMK_4_MOD_OFS                        =         12
WD2_BIT_LMK_5_MOD_MASK                       = 0x00000F00
WD2_BIT_LMK_5_MOD_OFS                        =          8
WD2_BIT_LMK_6_MOD_MASK                       = 0x000000F0
WD2_BIT_LMK_6_MOD_OFS                        =          4
WD2_BIT_LMK_7_MOD_MASK                       = 0x0000000F
WD2_BIT_LMK_7_MOD_OFS                        =          0

# Status Register 104: LMK_8_15_MOD_FLAG (offset 0x01A0) 
WD2_BIT_LMK_8_MOD_MASK                       = 0x00F00000
WD2_BIT_LMK_8_MOD_OFS                        =         20
WD2_BIT_LMK_9_MOD_MASK                       = 0x000F0000
WD2_BIT_LMK_9_MOD_OFS                        =         16
WD2_BIT_LMK_11_MOD_MASK                      = 0x0000F000
WD2_BIT_LMK_11_MOD_OFS                       =         12
WD2_BIT_LMK_13_MOD_MASK                      = 0x00000F00
WD2_BIT_LMK_13_MOD_OFS                       =          8
WD2_BIT_LMK_14_MOD_MASK                      = 0x000000F0
WD2_BIT_LMK_14_MOD_OFS                       =          4
WD2_BIT_LMK_15_MOD_MASK                      = 0x0000000F
WD2_BIT_LMK_15_MOD_OFS                       =          0

# Status Register 105: ADC_MOD_FLAG (offset 0x01A4) 
WD2_BIT_ADC_CFG_IND_TX_MOD_MASK              = 0x0F000000
WD2_BIT_ADC_CFG_IND_TX_MOD_OFS               =         24
WD2_BIT_ADC_PM_CLK_ENH_MOD_MASK              = 0x00F00000
WD2_BIT_ADC_PM_CLK_ENH_MOD_OFS               =         20
WD2_BIT_ADC_TEST_OFFS_OM_MOD_MASK            = 0x000F0000
WD2_BIT_ADC_TEST_OFFS_OM_MOD_OFS             =         16
WD2_BIT_ADC_OUT_VREF_MOD_MASK                = 0x0000F000
WD2_BIT_ADC_OUT_VREF_MOD_OFS                 =         12
WD2_BIT_ADC_USR_PATT_MOD_MASK                = 0x00000F00
WD2_BIT_ADC_USR_PATT_MOD_OFS                 =          8
WD2_BIT_ADC_SER_RES_SR_MOD_MASK              = 0x000000F0
WD2_BIT_ADC_SER_RES_SR_MOD_OFS               =          4
WD2_BIT_ADC_USR_IO_SYNC_MOD_MASK             = 0x0000000F
WD2_BIT_ADC_USR_IO_SYNC_MOD_OFS              =          0

# Status Register 106: ADC_0_CH_MOD_FLAG (offset 0x01A8) 
WD2_BIT_ADC_0_CH_A_MOD_MASK                  = 0xF0000000
WD2_BIT_ADC_0_CH_A_MOD_OFS                   =         28
WD2_BIT_ADC_0_CH_B_MOD_MASK                  = 0x0F000000
WD2_BIT_ADC_0_CH_B_MOD_OFS                   =         24
WD2_BIT_ADC_0_CH_C_MOD_MASK                  = 0x00F00000
WD2_BIT_ADC_0_CH_C_MOD_OFS                   =         20
WD2_BIT_ADC_0_CH_D_MOD_MASK                  = 0x000F0000
WD2_BIT_ADC_0_CH_D_MOD_OFS                   =         16
WD2_BIT_ADC_0_CH_E_MOD_MASK                  = 0x0000F000
WD2_BIT_ADC_0_CH_E_MOD_OFS                   =         12
WD2_BIT_ADC_0_CH_F_MOD_MASK                  = 0x00000F00
WD2_BIT_ADC_0_CH_F_MOD_OFS                   =          8
WD2_BIT_ADC_0_CH_G_MOD_MASK                  = 0x000000F0
WD2_BIT_ADC_0_CH_G_MOD_OFS                   =          4
WD2_BIT_ADC_0_CH_H_MOD_MASK                  = 0x0000000F
WD2_BIT_ADC_0_CH_H_MOD_OFS                   =          0

# Status Register 107: ADC_1_CH_MOD_FLAG (offset 0x01AC) 
WD2_BIT_ADC_1_CH_A_MOD_MASK                  = 0xF0000000
WD2_BIT_ADC_1_CH_A_MOD_OFS                   =         28
WD2_BIT_ADC_1_CH_B_MOD_MASK                  = 0x0F000000
WD2_BIT_ADC_1_CH_B_MOD_OFS                   =         24
WD2_BIT_ADC_1_CH_C_MOD_MASK                  = 0x00F00000
WD2_BIT_ADC_1_CH_C_MOD_OFS                   =         20
WD2_BIT_ADC_1_CH_D_MOD_MASK                  = 0x000F0000
WD2_BIT_ADC_1_CH_D_MOD_OFS                   =         16
WD2_BIT_ADC_1_CH_E_MOD_MASK                  = 0x0000F000
WD2_BIT_ADC_1_CH_E_MOD_OFS                   =         12
WD2_BIT_ADC_1_CH_F_MOD_MASK                  = 0x00000F00
WD2_BIT_ADC_1_CH_F_MOD_OFS                   =          8
WD2_BIT_ADC_1_CH_G_MOD_MASK                  = 0x000000F0
WD2_BIT_ADC_1_CH_G_MOD_OFS                   =          4
WD2_BIT_ADC_1_CH_H_MOD_MASK                  = 0x0000000F
WD2_BIT_ADC_1_CH_H_MOD_OFS                   =          0

# Status Register 108: ADC_01_CLK_MOD_FLAG (offset 0x01B0) 
WD2_BIT_ADC_1_DCO_MOD_MASK                   = 0x0000F000
WD2_BIT_ADC_1_DCO_MOD_OFS                    =         12
WD2_BIT_ADC_0_DCO_MOD_MASK                   = 0x00000F00
WD2_BIT_ADC_0_DCO_MOD_OFS                    =          8
WD2_BIT_ADC_1_FCO_MOD_MASK                   = 0x000000F0
WD2_BIT_ADC_1_FCO_MOD_OFS                    =          4
WD2_BIT_ADC_0_FCO_MOD_MASK                   = 0x0000000F
WD2_BIT_ADC_0_FCO_MOD_OFS                    =          0


# Number of Registers
 

REG_NR_OF_CTRL_REGS          = 174
REG_NR_OF_STAT_REGS          = 109


# #############################################################################
# Control Register Defaults                                                   #
# #############################################################################
ctrl_reg_default = (0xFFFFFFFF,   # Offset 0x1000 
                    0x1F100380,   # Offset 0x1004 
                    0x00000000,   # Offset 0x1008 
                    0x00026464,   # Offset 0x100C 
                    0x00FFFFFF,   # Offset 0x1010 
                    0x01000753,   # Offset 0x1014 
                    0x0000FFFF,   # Offset 0x1018 
                    0x0000FFFF,   # Offset 0x101C 
                    0x0100FFFF,   # Offset 0x1020 
                    0x0000FFFF,   # Offset 0x1024 
                    0x00000400,   # Offset 0x1028 
                    0x00000800,   # Offset 0x102C 
                    0x00001000,   # Offset 0x1030 
                    0x00000200,   # Offset 0x1034 
                    0x00000001,   # Offset 0x1038 
                    0x00000000,   # Offset 0x103C 
                    0x00000000,   # Offset 0x1040 
                    0x9EC045A0,   # Offset 0x1044 
                    0x00000000,   # Offset 0x1048 
                    0x00000000,   # Offset 0x104C 
                    0x000047B0,   # Offset 0x1050 
                    0x57105710,   # Offset 0x1054 
                    0x57105710,   # Offset 0x1058 
                    0x57105710,   # Offset 0x105C 
                    0x57105710,   # Offset 0x1060 
                    0x57105710,   # Offset 0x1064 
                    0x57105710,   # Offset 0x1068 
                    0x57105710,   # Offset 0x106C 
                    0x57105710,   # Offset 0x1070 
                    0x00020002,   # Offset 0x1074 
                    0x00020002,   # Offset 0x1078 
                    0x00020002,   # Offset 0x107C 
                    0x00020002,   # Offset 0x1080 
                    0x00020002,   # Offset 0x1084 
                    0x00020002,   # Offset 0x1088 
                    0x00020002,   # Offset 0x108C 
                    0x00020002,   # Offset 0x1090 
                    0x00000000,   # Offset 0x1094 
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
                    0x00002710,   # Offset 0x10D4 
                    0x00033100,   # Offset 0x10D8 
                    0x00020101,   # Offset 0x10DC 
                    0x00020102,   # Offset 0x10E0 
                    0x00000103,   # Offset 0x10E4 
                    0x00020104,   # Offset 0x10E8 
                    0x00020105,   # Offset 0x10EC 
                    0x00000106,   # Offset 0x10F0 
                    0x00026407,   # Offset 0x10F4 
                    0x10000908,   # Offset 0x10F8 
                    0xA0022A09,   # Offset 0x10FC 
                    0x0082000B,   # Offset 0x1100 
                    0x029900AD,   # Offset 0x1104 
                    0x0830140E,   # Offset 0x1108 
                    0xD400300F,   # Offset 0x110C 
                    0x180F3F00,   # Offset 0x1110 
                    0x00010000,   # Offset 0x1114 
                    0x00000044,   # Offset 0x1118 
                    0x00300304,   # Offset 0x111C 
                    0xFC00FC00,   # Offset 0x1120 
                    0x00420000,   # Offset 0x1124 
                    0x00000000,   # Offset 0x1128 
                    0x00000004,   # Offset 0x112C 
                    0x00000004,   # Offset 0x1130 
                    0x00000004,   # Offset 0x1134 
                    0x00000004,   # Offset 0x1138 
                    0x00000004,   # Offset 0x113C 
                    0x00000004,   # Offset 0x1140 
                    0x00000004,   # Offset 0x1144 
                    0x00000000,   # Offset 0x1148 
                    0x00000000,   # Offset 0x114C 
                    0x00000000,   # Offset 0x1150 
                    0x00000004,   # Offset 0x1154 
                    0x00000004,   # Offset 0x1158 
                    0x00000004,   # Offset 0x115C 
                    0x00000004,   # Offset 0x1160 
                    0x00000004,   # Offset 0x1164 
                    0x00000004,   # Offset 0x1168 
                    0x00000004,   # Offset 0x116C 
                    0x00000000,   # Offset 0x1170 
                    0x00000000,   # Offset 0x1174 
                    0x00000000,   # Offset 0x1178 
                    0x00000000,   # Offset 0x117C 
                    0x0000FFFF,   # Offset 0x1180 
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
                    0x00000000,   # Offset 0x1224 
                    0x00000000,   # Offset 0x1228 
                    0x00000000,   # Offset 0x122C 
                    0x00000000,   # Offset 0x1230 
                    0x00000000,   # Offset 0x1234 
                    0x00000000,   # Offset 0x1238 
                    0x00000000,   # Offset 0x123C 
                    0x00000000,   # Offset 0x1240 
                    0x00000000,   # Offset 0x1244 
                    0x00000000,   # Offset 0x1248 
                    0x00000000,   # Offset 0x124C 
                    0x00000000,   # Offset 0x1250 
                    0x00000000,   # Offset 0x1254 
                    0x00000000,   # Offset 0x1258 
                    0x00000000,   # Offset 0x125C 
                    0x00000000,   # Offset 0x1260 
                    0x00000000,   # Offset 0x1264 
                    0x00000000,   # Offset 0x1268 
                    0x00000000,   # Offset 0x126C 
                    0x00000000,   # Offset 0x1270 
                    0x00000000,   # Offset 0x1274 
                    0x00000000,   # Offset 0x1278 
                    0x00000000,   # Offset 0x127C 
                    0x00000000,   # Offset 0x1280 
                    0x00000000,   # Offset 0x1284 
                    0x00000000,   # Offset 0x1288 
                    0x00000000,   # Offset 0x128C 
                    0x00000000,   # Offset 0x1290 
                    0x00000000,   # Offset 0x1294 
                    0x00000000,   # Offset 0x1298 
                    0x00000000,   # Offset 0x129C 
                    0x00000000,   # Offset 0x12A0 
                    0x00000000,   # Offset 0x12A4 
                    0x00000000,   # Offset 0x12A8 
                    0x00000000,   # Offset 0x12AC 
                    0x00000000)   # Offset 0x12B0 


# #############################################################################

WD2_DAC_REG  = 0
WD2_DAC_MASK = 1
WD2_DAC_OFS  = 2

WD2_DAC0_CH_A = (WD2_REG_DAC0_A_B_OFS, WD2_BIT_DAC0_CH_A_MASK, WD2_BIT_DAC0_CH_A_OFS)
WD2_DAC0_CH_B = (WD2_REG_DAC0_A_B_OFS, WD2_BIT_DAC0_CH_B_MASK, WD2_BIT_DAC0_CH_B_OFS)
WD2_DAC0_CH_C = (WD2_REG_DAC0_C_D_OFS, WD2_BIT_DAC0_CH_C_MASK, WD2_BIT_DAC0_CH_C_OFS)
WD2_DAC0_CH_D = (WD2_REG_DAC0_C_D_OFS, WD2_BIT_DAC0_CH_D_MASK, WD2_BIT_DAC0_CH_D_OFS)
WD2_DAC0_CH_E = (WD2_REG_DAC0_E_F_OFS, WD2_BIT_DAC0_CH_E_MASK, WD2_BIT_DAC0_CH_E_OFS)
WD2_DAC0_CH_F = (WD2_REG_DAC0_E_F_OFS, WD2_BIT_DAC0_CH_F_MASK, WD2_BIT_DAC0_CH_F_OFS)
WD2_DAC0_CH_G = (WD2_REG_DAC0_G_H_OFS, WD2_BIT_DAC0_CH_G_MASK, WD2_BIT_DAC0_CH_G_OFS)
WD2_DAC0_CH_H = (WD2_REG_DAC0_G_H_OFS, WD2_BIT_DAC0_CH_H_MASK, WD2_BIT_DAC0_CH_H_OFS)
WD2_DAC1_CH_A = (WD2_REG_DAC1_A_B_OFS, WD2_BIT_DAC1_CH_A_MASK, WD2_BIT_DAC1_CH_A_OFS)
WD2_DAC1_CH_B = (WD2_REG_DAC1_A_B_OFS, WD2_BIT_DAC1_CH_B_MASK, WD2_BIT_DAC1_CH_B_OFS)
WD2_DAC1_CH_C = (WD2_REG_DAC1_C_D_OFS, WD2_BIT_DAC1_CH_C_MASK, WD2_BIT_DAC1_CH_C_OFS)
WD2_DAC1_CH_D = (WD2_REG_DAC1_C_D_OFS, WD2_BIT_DAC1_CH_D_MASK, WD2_BIT_DAC1_CH_D_OFS)
WD2_DAC1_CH_E = (WD2_REG_DAC1_E_F_OFS, WD2_BIT_DAC1_CH_E_MASK, WD2_BIT_DAC1_CH_E_OFS)
WD2_DAC1_CH_F = (WD2_REG_DAC1_E_F_OFS, WD2_BIT_DAC1_CH_F_MASK, WD2_BIT_DAC1_CH_F_OFS)
WD2_DAC1_CH_G = (WD2_REG_DAC1_G_H_OFS, WD2_BIT_DAC1_CH_G_MASK, WD2_BIT_DAC1_CH_G_OFS)
WD2_DAC1_CH_H = (WD2_REG_DAC1_G_H_OFS, WD2_BIT_DAC1_CH_H_MASK, WD2_BIT_DAC1_CH_H_OFS)
WD2_DAC2_CH_A = (WD2_REG_DAC2_A_B_OFS, WD2_BIT_DAC2_CH_A_MASK, WD2_BIT_DAC2_CH_A_OFS)
WD2_DAC2_CH_B = (WD2_REG_DAC2_A_B_OFS, WD2_BIT_DAC2_CH_B_MASK, WD2_BIT_DAC2_CH_B_OFS)
WD2_DAC2_CH_C = (WD2_REG_DAC2_C_D_OFS, WD2_BIT_DAC2_CH_C_MASK, WD2_BIT_DAC2_CH_C_OFS)
WD2_DAC2_CH_D = (WD2_REG_DAC2_C_D_OFS, WD2_BIT_DAC2_CH_D_MASK, WD2_BIT_DAC2_CH_D_OFS)
WD2_DAC2_CH_E = (WD2_REG_DAC2_E_F_OFS, WD2_BIT_DAC2_CH_E_MASK, WD2_BIT_DAC2_CH_E_OFS)
WD2_DAC2_CH_F = (WD2_REG_DAC2_E_F_OFS, WD2_BIT_DAC2_CH_F_MASK, WD2_BIT_DAC2_CH_F_OFS)
WD2_DAC2_CH_G = (WD2_REG_DAC2_G_H_OFS, WD2_BIT_DAC2_CH_G_MASK, WD2_BIT_DAC2_CH_G_OFS)
WD2_DAC2_CH_H = (WD2_REG_DAC2_G_H_OFS, WD2_BIT_DAC2_CH_H_MASK, WD2_BIT_DAC2_CH_H_OFS)

# ##############################################################################

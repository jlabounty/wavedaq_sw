# #####################################################################################
#  Paul Scherrer Institut
# #####################################################################################
#
#  Project :  MEGII - DCB
#
#  Author  :  schmid_e (Author of generation script)
#  Created :  01.04.2022 10:50:56
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

DCB_REG_HW_VER                            = 0x0000
DCB_REG_REG_LAYOUT_VER                    = 0x0004
DCB_REG_FW_BUILD_DATE                     = 0x0008
DCB_REG_FW_BUILD_TIME                     = 0x000C
DCB_REG_SW_BUILD_DATE                     = 0x0010
DCB_REG_SW_BUILD_TIME                     = 0x0014
DCB_REG_FW_GIT_HASH_TAG                   = 0x0018
DCB_REG_SW_GIT_HASH_TAG                   = 0x001C
DCB_REG_PROT_VER                          = 0x0020
DCB_REG_SN                                = 0x0024
DCB_REG_STATUS                            = 0x0028
DCB_REG_TEMP                              = 0x002C
DCB_REG_PLL_LOCK                          = 0x0030
DCB_REG_DCB_LOC                           = 0x0034
DCB_REG_CTRL                              = 0x0038
DCB_REG_SET_CTRL                          = 0x003C
DCB_REG_CLR_CTRL                          = 0x0040
DCB_REG_CLK_CTRL                          = 0x0044
DCB_REG_SET_CLK_CTRL                      = 0x0048
DCB_REG_CLR_CLK_CTRL                      = 0x004C
DCB_REG_COM_CTRL                          = 0x0050
DCB_REG_DPS_CTRL                          = 0x0054
DCB_REG_RST                               = 0x0058
DCB_REG_SERDES_STATUS_00_07               = 0x005C
DCB_REG_SERDES_STATUS_08_15               = 0x0060
DCB_REG_SERDES_STATUS_17                  = 0x0064
DCB_REG_SERDES_ERR_CNT_00                 = 0x0068
DCB_REG_SERDES_ERR_CNT_01                 = 0x006C
DCB_REG_SERDES_ERR_CNT_02                 = 0x0070
DCB_REG_SERDES_ERR_CNT_03                 = 0x0074
DCB_REG_SERDES_ERR_CNT_04                 = 0x0078
DCB_REG_SERDES_ERR_CNT_05                 = 0x007C
DCB_REG_SERDES_ERR_CNT_06                 = 0x0080
DCB_REG_SERDES_ERR_CNT_07                 = 0x0084
DCB_REG_SERDES_ERR_CNT_08                 = 0x0088
DCB_REG_SERDES_ERR_CNT_09                 = 0x008C
DCB_REG_SERDES_ERR_CNT_10                 = 0x0090
DCB_REG_SERDES_ERR_CNT_11                 = 0x0094
DCB_REG_SERDES_ERR_CNT_12                 = 0x0098
DCB_REG_SERDES_ERR_CNT_13                 = 0x009C
DCB_REG_SERDES_ERR_CNT_14                 = 0x00A0
DCB_REG_SERDES_ERR_CNT_15                 = 0x00A4
DCB_REG_SERDES_ERR_CNT_17                 = 0x00A8
DCB_REG_APLY_CFG                          = 0x00AC
DCB_REG_LMK_0                             = 0x00B0
DCB_REG_LMK_1                             = 0x00B4
DCB_REG_LMK_2                             = 0x00B8
DCB_REG_LMK_3                             = 0x00BC
DCB_REG_LMK_4                             = 0x00C0
DCB_REG_LMK_5                             = 0x00C4
DCB_REG_LMK_6                             = 0x00C8
DCB_REG_LMK_7                             = 0x00CC
DCB_REG_LMK_8                             = 0x00D0
DCB_REG_LMK_9                             = 0x00D4
DCB_REG_LMK_11                            = 0x00D8
DCB_REG_LMK_13                            = 0x00DC
DCB_REG_LMK_14                            = 0x00E0
DCB_REG_LMK_15                            = 0x00E4
DCB_REG_TIME_LSB                          = 0x00E8
DCB_REG_TIME_MSB                          = 0x00EC
DCB_REG_TIME_LSB_SET                      = 0x00F0
DCB_REG_TIME_MSB_SET                      = 0x00F4
DCB_REG_EVENT_TX_RATE                     = 0x00F8
DCB_REG_EVENT_NR                          = 0x00FC
DCB_REG_TRG_CFG                           = 0x0100
DCB_REG_SET_TRG_CFG                       = 0x0104
DCB_REG_CLR_TRG_CFG                       = 0x0108
DCB_REG_TRG_AUTO_PERIOD                   = 0x010C
DCB_REG_TRB_INFO_STAT                     = 0x0110
DCB_REG_TRB_INFO_LSB                      = 0x0114
DCB_REG_TRB_INFO_MSB                      = 0x0118
DCB_REG_LMK_MOD_FLAG                      = 0x011C
DCB_REG_CMB_MSCB_ADR                      = 0x0120
DCB_REG_SD_PKT_CNT_0                      = 0x0124
DCB_REG_SD_PKT_CNT_1                      = 0x0128
DCB_REG_SD_PKT_CNT_2                      = 0x012C
DCB_REG_SD_PKT_CNT_3                      = 0x0130
DCB_REG_SD_PKT_CNT_4                      = 0x0134
DCB_REG_SD_PKT_CNT_5                      = 0x0138
DCB_REG_SD_PKT_CNT_6                      = 0x013C
DCB_REG_SD_PKT_CNT_7                      = 0x0140
DCB_REG_SD_PKT_CNT_8                      = 0x0144
DCB_REG_SD_PKT_CNT_9                      = 0x0148
DCB_REG_SD_PKT_CNT_10                     = 0x014C
DCB_REG_SD_PKT_CNT_11                     = 0x0150
DCB_REG_SD_PKT_CNT_12                     = 0x0154
DCB_REG_SD_PKT_CNT_13                     = 0x0158
DCB_REG_SD_PKT_CNT_14                     = 0x015C
DCB_REG_SD_PKT_CNT_15                     = 0x0160
DCB_REG_SD_PKT_CNT_17                     = 0x0164
DCB_REG_SD_EYE_STATUS_0                   = 0x0168
DCB_REG_SD_EYE_STATUS_1                   = 0x016C
DCB_REG_SD_EYE_STATUS_2                   = 0x0170
DCB_REG_SD_EYE_STATUS_3                   = 0x0174
DCB_REG_SD_EYE_STATUS_4                   = 0x0178
DCB_REG_SD_EYE_STATUS_5                   = 0x017C
DCB_REG_SD_EYE_STATUS_6                   = 0x0180
DCB_REG_SD_EYE_STATUS_7                   = 0x0184
DCB_REG_SD_EYE_STATUS_8                   = 0x0188
DCB_REG_SD_EYE_STATUS_9                   = 0x018C
DCB_REG_SD_EYE_STATUS_10                  = 0x0190
DCB_REG_SD_EYE_STATUS_11                  = 0x0194
DCB_REG_SD_EYE_STATUS_12                  = 0x0198
DCB_REG_SD_EYE_STATUS_13                  = 0x019C
DCB_REG_SD_EYE_STATUS_14                  = 0x01A0
DCB_REG_SD_EYE_STATUS_15                  = 0x01A4
DCB_REG_SD_EYE_STATUS_17                  = 0x01A8
DCB_REG_CRC32_REG_BANK                    = 0x01AC

#
# Bit Positions
#
#
# Bit Positions
#
# ****** Register 0 [0x0000]: HW_VER - Hardware version information of the PCB (Default: 0xAC010307) ******

# BOARD_MAGIC - 0xAC, Magic number for board identification
DCB_BOARD_MAGIC_REG                      =              DCB_REG_HW_VER
DCB_BOARD_MAGIC_MASK                     =                      0xFF000000
DCB_BOARD_MAGIC_OFS                      =                              24
DCB_BOARD_MAGIC_CONST                                             0xAC

# VENDOR_ID - ID of the board vendor (0x01 for PSI)
DCB_VENDOR_ID_REG                        =              DCB_REG_HW_VER
DCB_VENDOR_ID_MASK                       =                      0x00FF0000
DCB_VENDOR_ID_OFS                        =                              16
DCB_VENDOR_ID_CONST                                               0x01

# BOARD_TYPE - DCB Number (0x03 for DCB ???)
DCB_BOARD_TYPE_REG                       =              DCB_REG_HW_VER
DCB_BOARD_TYPE_MASK                      =                      0x0000FF00
DCB_BOARD_TYPE_OFS                       =                               8
DCB_BOARD_TYPE_CONST                                              0x03

# BOARD_REVISION - Board revision (A=0x00, B=0x01, C=0x02, D=0x03, E=0x04)
DCB_BOARD_REVISION_REG                   =              DCB_REG_HW_VER
DCB_BOARD_REVISION_MASK                  =                      0x000000FC
DCB_BOARD_REVISION_OFS                   =                               2
DCB_BOARD_REVISION_CONST                                          0x01

# BOARD_VARIANT - Version indicator pins reflecting the variant of the board (XXX,YYY)
DCB_BOARD_VARIANT_REG                    =              DCB_REG_HW_VER
DCB_BOARD_VARIANT_MASK                   =                      0x00000003
DCB_BOARD_VARIANT_OFS                    =                               0
DCB_BOARD_VARIANT_CONST                                            0x3



# ****** Register 1 [0x0004]: REG_LAYOUT_VER - Register map layout version information (Default: 0x00000000) ******

# REG_LAYOUT_COMP_LEVEL - Register map layout compatibility level
DCB_REG_LAYOUT_COMP_LEVEL_REG            =      DCB_REG_REG_LAYOUT_VER
DCB_REG_LAYOUT_COMP_LEVEL_MASK           =                      0xFFFF0000
DCB_REG_LAYOUT_COMP_LEVEL_OFS            =                              16
DCB_REG_LAYOUT_COMP_LEVEL_CONST                                 0x0000

# REG_LAYOUT_VERSION - Register map layout version
DCB_REG_LAYOUT_VERSION_REG               =      DCB_REG_REG_LAYOUT_VER
DCB_REG_LAYOUT_VERSION_MASK              =                      0x0000FFFF
DCB_REG_LAYOUT_VERSION_OFS               =                               0
DCB_REG_LAYOUT_VERSION_CONST                                    0x0000



# ****** Register 2 [0x0008]: FW_BUILD_DATE - Date when the firmware was built (Default: 0x00000000) ******

# FW_BUILD_YEAR - Year of the firmware build
DCB_FW_BUILD_YEAR_REG                    =       DCB_REG_FW_BUILD_DATE
DCB_FW_BUILD_YEAR_MASK                   =                      0xFFFF0000
DCB_FW_BUILD_YEAR_OFS                    =                              16

# FW_BUILD_MONTH - Month of the firmware build
DCB_FW_BUILD_MONTH_REG                   =       DCB_REG_FW_BUILD_DATE
DCB_FW_BUILD_MONTH_MASK                  =                      0x0000FF00
DCB_FW_BUILD_MONTH_OFS                   =                               8

# FW_BUILD_DAY - Day of the firmware build
DCB_FW_BUILD_DAY_REG                     =       DCB_REG_FW_BUILD_DATE
DCB_FW_BUILD_DAY_MASK                    =                      0x000000FF
DCB_FW_BUILD_DAY_OFS                     =                               0



# ****** Register 3 [0x000C]: FW_BUILD_TIME - Time when the firmware was built and compatibility level (Default: 0x00000000) ******

# FW_COMPAT_LEVEL - Firmware compatibility level
DCB_FW_COMPAT_LEVEL_REG                  =       DCB_REG_FW_BUILD_TIME
DCB_FW_COMPAT_LEVEL_MASK                 =                      0xFF000000
DCB_FW_COMPAT_LEVEL_OFS                  =                              24
DCB_FW_COMPAT_LEVEL_CONST                                         0x00

# FW_BUILD_HOUR - Hour of the firmware build
DCB_FW_BUILD_HOUR_REG                    =       DCB_REG_FW_BUILD_TIME
DCB_FW_BUILD_HOUR_MASK                   =                      0x00FF0000
DCB_FW_BUILD_HOUR_OFS                    =                              16

# FW_BUILD_MINUTE - Minute of the firmware build
DCB_FW_BUILD_MINUTE_REG                  =       DCB_REG_FW_BUILD_TIME
DCB_FW_BUILD_MINUTE_MASK                 =                      0x0000FF00
DCB_FW_BUILD_MINUTE_OFS                  =                               8

# FW_BUILD_SECOND - Second of the firmware build
DCB_FW_BUILD_SECOND_REG                  =       DCB_REG_FW_BUILD_TIME
DCB_FW_BUILD_SECOND_MASK                 =                      0x000000FF
DCB_FW_BUILD_SECOND_OFS                  =                               0



# ****** Register 4 [0x0010]: SW_BUILD_DATE - Date when the software was built (Default: 0x00000000) ******

# SW_BUILD_YEAR - Year of the software build
DCB_SW_BUILD_YEAR_REG                    =       DCB_REG_SW_BUILD_DATE
DCB_SW_BUILD_YEAR_MASK                   =                      0xFFFF0000
DCB_SW_BUILD_YEAR_OFS                    =                              16

# SW_BUILD_MONTH - Month of the software build
DCB_SW_BUILD_MONTH_REG                   =       DCB_REG_SW_BUILD_DATE
DCB_SW_BUILD_MONTH_MASK                  =                      0x0000FF00
DCB_SW_BUILD_MONTH_OFS                   =                               8

# SW_BUILD_DAY - Day of the software build
DCB_SW_BUILD_DAY_REG                     =       DCB_REG_SW_BUILD_DATE
DCB_SW_BUILD_DAY_MASK                    =                      0x000000FF
DCB_SW_BUILD_DAY_OFS                     =                               0



# ****** Register 5 [0x0014]: SW_BUILD_TIME - Time when the software was built and compatibility level (Default: 0x00000000) ******

# SW_BUILD_HOUR - Hour of the software build
DCB_SW_BUILD_HOUR_REG                    =       DCB_REG_SW_BUILD_TIME
DCB_SW_BUILD_HOUR_MASK                   =                      0x00FF0000
DCB_SW_BUILD_HOUR_OFS                    =                              16

# SW_BUILD_MINUTE - Minute of the software build
DCB_SW_BUILD_MINUTE_REG                  =       DCB_REG_SW_BUILD_TIME
DCB_SW_BUILD_MINUTE_MASK                 =                      0x0000FF00
DCB_SW_BUILD_MINUTE_OFS                  =                               8

# SW_BUILD_SECOND - Second of the software build
DCB_SW_BUILD_SECOND_REG                  =       DCB_REG_SW_BUILD_TIME
DCB_SW_BUILD_SECOND_MASK                 =                      0x000000FF
DCB_SW_BUILD_SECOND_OFS                  =                               0



# ****** Register 6 [0x0018]: FW_GIT_HASH_TAG - Hash tag of the firmware commit in the GIT repository (Default: 0x00000000) ******

# FW_GIT_HASH_TAG - Hash tag of the firmware commit in the GIT repository
DCB_FW_GIT_HASH_TAG_REG                  =     DCB_REG_FW_GIT_HASH_TAG
DCB_FW_GIT_HASH_TAG_MASK                 =                      0xFFFFFFFF
DCB_FW_GIT_HASH_TAG_OFS                  =                               0



# ****** Register 7 [0x001C]: SW_GIT_HASH_TAG - Hash tag of the software commit in the GIT repository (Default: 0x00000000) ******

# SW_GIT_HASH_TAG - Hash tag of the software commit in the GIT repository
DCB_SW_GIT_HASH_TAG_REG                  =     DCB_REG_SW_GIT_HASH_TAG
DCB_SW_GIT_HASH_TAG_MASK                 =                      0xFFFFFFFF
DCB_SW_GIT_HASH_TAG_OFS                  =                               0



# ****** Register 8 [0x0020]: PROT_VER - Vesion of the WaveDAQ protocol (Default: 0x00000000) ******

# PROTOCOL_VERSION - Version of the WaveDAQ protocol
DCB_PROTOCOL_VERSION_REG                 =            DCB_REG_PROT_VER
DCB_PROTOCOL_VERSION_MASK                =                      0x000000FF
DCB_PROTOCOL_VERSION_OFS                 =                               0



# ****** Register 9 [0x0024]: SN - Serial Number of the DCB Board (Board ID) (Default: 0x00000000) ******

# SERIAL_NUMBER - Serial Number of the Data Concentrator Board (Board ID)
DCB_SERIAL_NUMBER_REG                    =                  DCB_REG_SN
DCB_SERIAL_NUMBER_MASK                   =                      0x0000FFFF
DCB_SERIAL_NUMBER_OFS                    =                               0



# ****** Register 10 [0x0028]: STATUS - Status Register (Default: 0x00000000) ******

# FLASH_SEL - SPI Flash select from backplane (inverted = high active)
DCB_FLASH_SEL_REG                        =              DCB_REG_STATUS
DCB_FLASH_SEL_MASK                       =                      0x00000020
DCB_FLASH_SEL_OFS                        =                               5

# BOARD_SEL - Board select from backplane (inverted = high active)
DCB_BOARD_SEL_REG                        =              DCB_REG_STATUS
DCB_BOARD_SEL_MASK                       =                      0x00000010
DCB_BOARD_SEL_OFS                        =                               4

# SERIAL_BUSY - "1" during serial activity like FLASH read/write
DCB_SERIAL_BUSY_REG                      =              DCB_REG_STATUS
DCB_SERIAL_BUSY_MASK                     =                      0x00000004
DCB_SERIAL_BUSY_OFS                      =                               2

# DCB_BUSY - "1" while dcb is busy
DCB_DCB_BUSY_REG                         =              DCB_REG_STATUS
DCB_DCB_BUSY_MASK                        =                      0x00000002
DCB_DCB_BUSY_OFS                         =                               1

# SYS_BUSY - Inverted busy signal from backplane (active low)
DCB_SYS_BUSY_REG                         =              DCB_REG_STATUS
DCB_SYS_BUSY_MASK                        =                      0x00000001
DCB_SYS_BUSY_OFS                         =                               0



# ****** Register 11 [0x002C]: TEMP - Status Register (Default: 0x00000000) ******

# TEMPERATURE - temperature in 0.0625 deg. C units
DCB_TEMPERATURE_REG                      =                DCB_REG_TEMP
DCB_TEMPERATURE_MASK                     =                      0x0000FFFF
DCB_TEMPERATURE_OFS                      =                               0



# ****** Register 12 [0x0030]: PLL_LOCK - Lock Status of PLLs (Default: 0x00000000) ******

# SERDES_CLK_MGR_LOCK - Lock of the clock manager deriving clocks for serdes from the WDB clock
DCB_SERDES_CLK_MGR_LOCK_REG              =            DCB_REG_PLL_LOCK
DCB_SERDES_CLK_MGR_LOCK_MASK             =                      0x00000008
DCB_SERDES_CLK_MGR_LOCK_OFS              =                               3

# WDB_CLK_MGR_LOCK - Lock of the clock manager deriving clocks from the WDB clock (e.g. refclk for SYNC output delay)
DCB_WDB_CLK_MGR_LOCK_REG                 =            DCB_REG_PLL_LOCK
DCB_WDB_CLK_MGR_LOCK_MASK                =                      0x00000004
DCB_WDB_CLK_MGR_LOCK_OFS                 =                               2

# SYS_DCM_LOCK - Lock of system DCM (FPGA internal)
DCB_SYS_DCM_LOCK_REG                     =            DCB_REG_PLL_LOCK
DCB_SYS_DCM_LOCK_MASK                    =                      0x00000002
DCB_SYS_DCM_LOCK_OFS                     =                               1

# LMK_PLL_LOCK - PLL lock signal of LMK (external)
DCB_LMK_PLL_LOCK_REG                     =            DCB_REG_PLL_LOCK
DCB_LMK_PLL_LOCK_MASK                    =                      0x00000001
DCB_LMK_PLL_LOCK_OFS                     =                               0



# ****** Register 13 [0x0034]: DCB_LOC - Location where the WD2 is plugged in (Default: 0xFFFFFFFF) ******

# CRATE_ID - ID of the crate where the current board is plugged in
DCB_CRATE_ID_REG                         =             DCB_REG_DCB_LOC
DCB_CRATE_ID_MASK                        =                      0x00FF0000
DCB_CRATE_ID_OFS                         =                              16

# SLOT_ID - ID of the slot where the current board is plugged in
DCB_SLOT_ID_REG                          =             DCB_REG_DCB_LOC
DCB_SLOT_ID_MASK                         =                      0x000000FF
DCB_SLOT_ID_OFS                          =                               0



# ****** Register 14 [0x0038]: CTRL - DCB control register (Default: 0x00000000) ******

# SYNC_DELAY - Output delay of SYNC output to backplane
DCB_SYNC_DELAY_REG                       =                DCB_REG_CTRL
DCB_SYNC_DELAY_MASK                      =                      0x001F0000
DCB_SYNC_DELAY_OFS                       =                              16

# DAQ_SOFT_TRIGGER - Send trigger pulse to all slots via the backplane
DCB_DAQ_SOFT_TRIGGER_REG                 =                DCB_REG_CTRL
DCB_DAQ_SOFT_TRIGGER_MASK                =                      0x00000020
DCB_DAQ_SOFT_TRIGGER_OFS                 =                               5

# DAQ_AUTO - Auto-Trigger readout state machine every 0.5s if no other trigger (like "auto" acquisition on scope)
DCB_DAQ_AUTO_REG                         =                DCB_REG_CTRL
DCB_DAQ_AUTO_MASK                        =                      0x00000004
DCB_DAQ_AUTO_OFS                         =                               2

# DAQ_NORMAL - Continuous data acquisition input trigger if system is not busy (like "normal" acquisition on scope)
DCB_DAQ_NORMAL_REG                       =                DCB_REG_CTRL
DCB_DAQ_NORMAL_MASK                      =                      0x00000002
DCB_DAQ_NORMAL_OFS                       =                               1

# DAQ_SINGLE - Single data acquisiton on input trigger (like "single" acquisition on scope)
DCB_DAQ_SINGLE_REG                       =                DCB_REG_CTRL
DCB_DAQ_SINGLE_MASK                      =                      0x00000001
DCB_DAQ_SINGLE_OFS                       =                               0



# ****** Register 15 [0x003C]: SET_CTRL - SET bit register for DCB control register (Default: 0x00000000) ******

# SET_BIT_CTRL - See CTRL register
DCB_SET_BIT_CTRL_REG                     =            DCB_REG_SET_CTRL
DCB_SET_BIT_CTRL_MASK                    =                      0xFFFFFFFF
DCB_SET_BIT_CTRL_OFS                     =                               0



# ****** Register 16 [0x0040]: CLR_CTRL - CLR bit register for DCB control register (Default: 0x00000000) ******

# CLR_BIT_CTRL - See CTRL register
DCB_CLR_BIT_CTRL_REG                     =            DCB_REG_CLR_CTRL
DCB_CLR_BIT_CTRL_MASK                    =                      0xFFFFFFFF
DCB_CLR_BIT_CTRL_OFS                     =                               0



# ****** Register 17 [0x0044]: CLK_CTRL - Clock Control (Default: 0xFFFFC00E) ******

# DISTRIBUTOR_CLK_OUT_EN - Clock distributor output enable (31:16 = LSK15:0, 15 = TCB, 14 = FPGA, 13:12 = spare)
DCB_DISTRIBUTOR_CLK_OUT_EN_REG           =            DCB_REG_CLK_CTRL
DCB_DISTRIBUTOR_CLK_OUT_EN_MASK          =                      0xFFFFF000
DCB_DISTRIBUTOR_CLK_OUT_EN_OFS           =                              12

# DISTRIBUTOR_CLK_SRC_SEL - Backplane clock distributor source select: 0 = external clock / 1 = LMK
DCB_DISTRIBUTOR_CLK_SRC_SEL_REG          =            DCB_REG_CLK_CTRL
DCB_DISTRIBUTOR_CLK_SRC_SEL_MASK         =                      0x00000008
DCB_DISTRIBUTOR_CLK_SRC_SEL_OFS          =                               3

# BUS_CLK_SRC_SEL - BUS (backplane) clock source select: 0 = LMK output 2 / 1 = AUX_OUT from FPGA (BUS_CLK_SEL)
DCB_BUS_CLK_SRC_SEL_REG                  =            DCB_REG_CLK_CTRL
DCB_BUS_CLK_SRC_SEL_MASK                 =                      0x00000004
DCB_BUS_CLK_SRC_SEL_OFS                  =                               2

# LMK_CLK_SRC_SEL - LMK clock source select: 0 = external clock / 1 = on board oscillator (CLK_SEL)
DCB_LMK_CLK_SRC_SEL_REG                  =            DCB_REG_CLK_CTRL
DCB_LMK_CLK_SRC_SEL_MASK                 =                      0x00000002
DCB_LMK_CLK_SRC_SEL_OFS                  =                               1

# EXT_CLK_IN_SEL - External clk input select: 0 = FCI / 1 = MCX connector (CLK_SEL_EXT)
DCB_EXT_CLK_IN_SEL_REG                   =            DCB_REG_CLK_CTRL
DCB_EXT_CLK_IN_SEL_MASK                  =                      0x00000001
DCB_EXT_CLK_IN_SEL_OFS                   =                               0



# ****** Register 18 [0x0048]: SET_CLK_CTRL - SET bit register for Clock control register (Default: 0x00000000) ******

# SET_BIT_CLK_CTRL - See CLK_CTRL register
DCB_SET_BIT_CLK_CTRL_REG                 =        DCB_REG_SET_CLK_CTRL
DCB_SET_BIT_CLK_CTRL_MASK                =                      0xFFFFFFFF
DCB_SET_BIT_CLK_CTRL_OFS                 =                               0



# ****** Register 19 [0x004C]: CLR_CLK_CTRL - CLR bit register for Clock control register (Default: 0x00000000) ******

# CLR_BIT_CLK_CTRL - See CLK_CTRL register
DCB_CLR_BIT_CLK_CTRL_REG                 =        DCB_REG_CLR_CLK_CTRL
DCB_CLR_BIT_CLK_CTRL_MASK                =                      0xFFFFFFFF
DCB_CLR_BIT_CLK_CTRL_OFS                 =                               0



# ****** Register 20 [0x0050]: COM_CTRL - Communication Control Register (Default: 0x00000753) ******

# INTER_PKG_DELAY - Delay between transmission of two UDP packages in 8ns steps
DCB_INTER_PKG_DELAY_REG                  =            DCB_REG_COM_CTRL
DCB_INTER_PKG_DELAY_MASK                 =                      0x00FFFFFF
DCB_INTER_PKG_DELAY_OFS                  =                               0



# ****** Register 21 [0x0054]: DPS_CTRL - DMA Packet Scheduler Control (Default: 0x0001FFFF) ******

# DPS_EVENT_MODE - Event Mode of the DMA packet scheduler: 0 = Freerun, 1 = Coordinate Events on Slots
DCB_DPS_EVENT_MODE_REG                   =            DCB_REG_DPS_CTRL
DCB_DPS_EVENT_MODE_MASK                  =                      0x00100000
DCB_DPS_EVENT_MODE_OFS                   =                              20

# DPS_SLOT_ENABLE - Data transmission enable bits for the crate slots (TCB slot = 16)
DCB_DPS_SLOT_ENABLE_REG                  =            DCB_REG_DPS_CTRL
DCB_DPS_SLOT_ENABLE_MASK                 =                      0x0001FFFF
DCB_DPS_SLOT_ENABLE_OFS                  =                               0



# ****** Register 22 [0x0058]: RST - Reset bits for specific firmwar units (Default: 0x00000000) ******

# ISERDES_RCVR_PACKET_COUNT_RST - Reset of all input SERDES packet counters
DCB_ISERDES_RCVR_PACKET_COUNT_RST_REG    =                 DCB_REG_RST
DCB_ISERDES_RCVR_PACKET_COUNT_RST_MASK   =                      0x00000200
DCB_ISERDES_RCVR_PACKET_COUNT_RST_OFS    =                               9

# WDB_SERDES_CLK_MGR_RST - Reset for clock manager deriving clocks from the WDB clock (e.g. refclk for SYNC output delay)
DCB_WDB_SERDES_CLK_MGR_RST_REG           =                 DCB_REG_RST
DCB_WDB_SERDES_CLK_MGR_RST_MASK          =                      0x00000100
DCB_WDB_SERDES_CLK_MGR_RST_OFS           =                               8

# WDB_REFCLK_MGR_RST - Reset for clock manager deriving clocks from the WDB clock (e.g. refclk for SYNC output delay)
DCB_WDB_REFCLK_MGR_RST_REG               =                 DCB_REG_RST
DCB_WDB_REFCLK_MGR_RST_MASK              =                      0x00000080
DCB_WDB_REFCLK_MGR_RST_OFS               =                               7

# TRIGGER_MGR_RST - Trigger manager reset
DCB_TRIGGER_MGR_RST_REG                  =                 DCB_REG_RST
DCB_TRIGGER_MGR_RST_MASK                 =                      0x00000040
DCB_TRIGGER_MGR_RST_OFS                  =                               6

# TR_SYNC_BPL - Trigger SYNC signal on the backplane
DCB_TR_SYNC_BPL_REG                      =                 DCB_REG_RST
DCB_TR_SYNC_BPL_MASK                     =                      0x00000020
DCB_TR_SYNC_BPL_OFS                      =                               5

# LMK_SYNC_DCB - Trigger SYNC signal of the LMK on the DCB
DCB_LMK_SYNC_DCB_REG                     =                 DCB_REG_RST
DCB_LMK_SYNC_DCB_MASK                    =                      0x00000010
DCB_LMK_SYNC_DCB_OFS                     =                               4

# ISERDES_RCVR_ERROR_COUNT_RST - Reset of all input SERDES error counters
DCB_ISERDES_RCVR_ERROR_COUNT_RST_REG     =                 DCB_REG_RST
DCB_ISERDES_RCVR_ERROR_COUNT_RST_MASK    =                      0x00000008
DCB_ISERDES_RCVR_ERROR_COUNT_RST_OFS     =                               3

# ISERDES_RECEIVER_RESYNC - Resynchronization of the input SERDES packet receiver
DCB_ISERDES_RECEIVER_RESYNC_REG          =                 DCB_REG_RST
DCB_ISERDES_RECEIVER_RESYNC_MASK         =                      0x00000004
DCB_ISERDES_RECEIVER_RESYNC_OFS          =                               2

# ISERDES_RECEIVER_RST - Reset of the input SERDES packet receiver
DCB_ISERDES_RECEIVER_RST_REG             =                 DCB_REG_RST
DCB_ISERDES_RECEIVER_RST_MASK            =                      0x00000002
DCB_ISERDES_RECEIVER_RST_OFS             =                               1

# RECONFIGURE_FPGA - Initiate FPGA Reconfiguration
DCB_RECONFIGURE_FPGA_REG                 =                 DCB_REG_RST
DCB_RECONFIGURE_FPGA_MASK                =                      0x00000001
DCB_RECONFIGURE_FPGA_OFS                 =                               0



# ****** Register 23 [0x005C]: SERDES_STATUS_00_07 - Input Serdes status for slot 0 to 7 (Default: 0x00000000) ******

# IDLE_PATTERN_DETECT_07 - Idle pattern detected on slot 7
DCB_IDLE_PATTERN_DETECT_07_REG           = DCB_REG_SERDES_STATUS_00_07
DCB_IDLE_PATTERN_DETECT_07_MASK          =                      0x80000000
DCB_IDLE_PATTERN_DETECT_07_OFS           =                              31

# BITSLIP_OK_07 - Bitslip successful on slot 7
DCB_BITSLIP_OK_07_REG                    = DCB_REG_SERDES_STATUS_00_07
DCB_BITSLIP_OK_07_MASK                   =                      0x40000000
DCB_BITSLIP_OK_07_OFS                    =                              30

# DELAY_OK_07 - Tap delay successfully set (min. 1 valid eye position found) on slot 7
DCB_DELAY_OK_07_REG                      = DCB_REG_SERDES_STATUS_00_07
DCB_DELAY_OK_07_MASK                     =                      0x20000000
DCB_DELAY_OK_07_OFS                      =                              29

# SYNC_DONE_07 - Overall syncronization procedure completed for slot 7
DCB_SYNC_DONE_07_REG                     = DCB_REG_SERDES_STATUS_00_07
DCB_SYNC_DONE_07_MASK                    =                      0x10000000
DCB_SYNC_DONE_07_OFS                     =                              28

# IDLE_PATTERN_DETECT_06 - Idle pattern detected on slot 6
DCB_IDLE_PATTERN_DETECT_06_REG           = DCB_REG_SERDES_STATUS_00_07
DCB_IDLE_PATTERN_DETECT_06_MASK          =                      0x08000000
DCB_IDLE_PATTERN_DETECT_06_OFS           =                              27

# BITSLIP_OK_06 - Bitslip successful on slot 6
DCB_BITSLIP_OK_06_REG                    = DCB_REG_SERDES_STATUS_00_07
DCB_BITSLIP_OK_06_MASK                   =                      0x04000000
DCB_BITSLIP_OK_06_OFS                    =                              26

# DELAY_OK_06 - Tap delay successfully set (min. 1 valid eye position found) on slot 6
DCB_DELAY_OK_06_REG                      = DCB_REG_SERDES_STATUS_00_07
DCB_DELAY_OK_06_MASK                     =                      0x02000000
DCB_DELAY_OK_06_OFS                      =                              25

# SYNC_DONE_06 - Overall syncronization procedure completed for slot 6
DCB_SYNC_DONE_06_REG                     = DCB_REG_SERDES_STATUS_00_07
DCB_SYNC_DONE_06_MASK                    =                      0x01000000
DCB_SYNC_DONE_06_OFS                     =                              24

# IDLE_PATTERN_DETECT_05 - Idle pattern detected on slot 5
DCB_IDLE_PATTERN_DETECT_05_REG           = DCB_REG_SERDES_STATUS_00_07
DCB_IDLE_PATTERN_DETECT_05_MASK          =                      0x00800000
DCB_IDLE_PATTERN_DETECT_05_OFS           =                              23

# BITSLIP_OK_05 - Bitslip successful on slot 5
DCB_BITSLIP_OK_05_REG                    = DCB_REG_SERDES_STATUS_00_07
DCB_BITSLIP_OK_05_MASK                   =                      0x00400000
DCB_BITSLIP_OK_05_OFS                    =                              22

# DELAY_OK_05 - Tap delay successfully set (min. 1 valid eye position found) on slot 5
DCB_DELAY_OK_05_REG                      = DCB_REG_SERDES_STATUS_00_07
DCB_DELAY_OK_05_MASK                     =                      0x00200000
DCB_DELAY_OK_05_OFS                      =                              21

# SYNC_DONE_05 - Overall syncronization procedure completed for slot 5
DCB_SYNC_DONE_05_REG                     = DCB_REG_SERDES_STATUS_00_07
DCB_SYNC_DONE_05_MASK                    =                      0x00100000
DCB_SYNC_DONE_05_OFS                     =                              20

# IDLE_PATTERN_DETECT_04 - Idle pattern detected on slot 4
DCB_IDLE_PATTERN_DETECT_04_REG           = DCB_REG_SERDES_STATUS_00_07
DCB_IDLE_PATTERN_DETECT_04_MASK          =                      0x00080000
DCB_IDLE_PATTERN_DETECT_04_OFS           =                              19

# BITSLIP_OK_04 - Bitslip successful on slot 4
DCB_BITSLIP_OK_04_REG                    = DCB_REG_SERDES_STATUS_00_07
DCB_BITSLIP_OK_04_MASK                   =                      0x00040000
DCB_BITSLIP_OK_04_OFS                    =                              18

# DELAY_OK_04 - Tap delay successfully set (min. 1 valid eye position found) on slot 4
DCB_DELAY_OK_04_REG                      = DCB_REG_SERDES_STATUS_00_07
DCB_DELAY_OK_04_MASK                     =                      0x00020000
DCB_DELAY_OK_04_OFS                      =                              17

# SYNC_DONE_04 - Overall syncronization procedure completed for slot 4
DCB_SYNC_DONE_04_REG                     = DCB_REG_SERDES_STATUS_00_07
DCB_SYNC_DONE_04_MASK                    =                      0x00010000
DCB_SYNC_DONE_04_OFS                     =                              16

# IDLE_PATTERN_DETECT_03 - Idle pattern detected on slot 3
DCB_IDLE_PATTERN_DETECT_03_REG           = DCB_REG_SERDES_STATUS_00_07
DCB_IDLE_PATTERN_DETECT_03_MASK          =                      0x00008000
DCB_IDLE_PATTERN_DETECT_03_OFS           =                              15

# BITSLIP_OK_03 - Bitslip successful on slot 3
DCB_BITSLIP_OK_03_REG                    = DCB_REG_SERDES_STATUS_00_07
DCB_BITSLIP_OK_03_MASK                   =                      0x00004000
DCB_BITSLIP_OK_03_OFS                    =                              14

# DELAY_OK_03 - Tap delay successfully set (min. 1 valid eye position found) on slot 3
DCB_DELAY_OK_03_REG                      = DCB_REG_SERDES_STATUS_00_07
DCB_DELAY_OK_03_MASK                     =                      0x00002000
DCB_DELAY_OK_03_OFS                      =                              13

# SYNC_DONE_03 - Overall syncronization procedure completed for slot 3
DCB_SYNC_DONE_03_REG                     = DCB_REG_SERDES_STATUS_00_07
DCB_SYNC_DONE_03_MASK                    =                      0x00001000
DCB_SYNC_DONE_03_OFS                     =                              12

# IDLE_PATTERN_DETECT_02 - Idle pattern detected on slot 2
DCB_IDLE_PATTERN_DETECT_02_REG           = DCB_REG_SERDES_STATUS_00_07
DCB_IDLE_PATTERN_DETECT_02_MASK          =                      0x00000800
DCB_IDLE_PATTERN_DETECT_02_OFS           =                              11

# BITSLIP_OK_02 - Bitslip successful on slot 2
DCB_BITSLIP_OK_02_REG                    = DCB_REG_SERDES_STATUS_00_07
DCB_BITSLIP_OK_02_MASK                   =                      0x00000400
DCB_BITSLIP_OK_02_OFS                    =                              10

# DELAY_OK_02 - Tap delay successfully set (min. 1 valid eye position found) on slot 2
DCB_DELAY_OK_02_REG                      = DCB_REG_SERDES_STATUS_00_07
DCB_DELAY_OK_02_MASK                     =                      0x00000200
DCB_DELAY_OK_02_OFS                      =                               9

# SYNC_DONE_02 - Overall syncronization procedure completed for slot 2
DCB_SYNC_DONE_02_REG                     = DCB_REG_SERDES_STATUS_00_07
DCB_SYNC_DONE_02_MASK                    =                      0x00000100
DCB_SYNC_DONE_02_OFS                     =                               8

# IDLE_PATTERN_DETECT_01 - Idle pattern detected on slot 17
DCB_IDLE_PATTERN_DETECT_01_REG           = DCB_REG_SERDES_STATUS_00_07
DCB_IDLE_PATTERN_DETECT_01_MASK          =                      0x00000080
DCB_IDLE_PATTERN_DETECT_01_OFS           =                               7

# BITSLIP_OK_01 - Bitslip successful on slot 1
DCB_BITSLIP_OK_01_REG                    = DCB_REG_SERDES_STATUS_00_07
DCB_BITSLIP_OK_01_MASK                   =                      0x00000040
DCB_BITSLIP_OK_01_OFS                    =                               6

# DELAY_OK_01 - Tap delay successfully set (min. 1 valid eye position found) on slot 1
DCB_DELAY_OK_01_REG                      = DCB_REG_SERDES_STATUS_00_07
DCB_DELAY_OK_01_MASK                     =                      0x00000020
DCB_DELAY_OK_01_OFS                      =                               5

# SYNC_DONE_01 - Overall syncronization procedure completed for slot 1
DCB_SYNC_DONE_01_REG                     = DCB_REG_SERDES_STATUS_00_07
DCB_SYNC_DONE_01_MASK                    =                      0x00000010
DCB_SYNC_DONE_01_OFS                     =                               4

# IDLE_PATTERN_DETECT_00 - Idle pattern detected on slot 0
DCB_IDLE_PATTERN_DETECT_00_REG           = DCB_REG_SERDES_STATUS_00_07
DCB_IDLE_PATTERN_DETECT_00_MASK          =                      0x00000008
DCB_IDLE_PATTERN_DETECT_00_OFS           =                               3

# BITSLIP_OK_00 - Bitslip successful on slot 0
DCB_BITSLIP_OK_00_REG                    = DCB_REG_SERDES_STATUS_00_07
DCB_BITSLIP_OK_00_MASK                   =                      0x00000004
DCB_BITSLIP_OK_00_OFS                    =                               2

# DELAY_OK_00 - Tap delay successfully set (min. 1 valid eye position found) on slot 0
DCB_DELAY_OK_00_REG                      = DCB_REG_SERDES_STATUS_00_07
DCB_DELAY_OK_00_MASK                     =                      0x00000002
DCB_DELAY_OK_00_OFS                      =                               1

# SYNC_DONE_00 - Overall syncronization procedure completed for slot 0
DCB_SYNC_DONE_00_REG                     = DCB_REG_SERDES_STATUS_00_07
DCB_SYNC_DONE_00_MASK                    =                      0x00000001
DCB_SYNC_DONE_00_OFS                     =                               0



# ****** Register 24 [0x0060]: SERDES_STATUS_08_15 - Input Serdes status for slot 8 to 15 (Default: 0x00000000) ******

# IDLE_PATTERN_DETECT_15 - Idle pattern detected on slot 15
DCB_IDLE_PATTERN_DETECT_15_REG           = DCB_REG_SERDES_STATUS_08_15
DCB_IDLE_PATTERN_DETECT_15_MASK          =                      0x80000000
DCB_IDLE_PATTERN_DETECT_15_OFS           =                              31

# BITSLIP_OK_15 - Bitslip successful on slot 15
DCB_BITSLIP_OK_15_REG                    = DCB_REG_SERDES_STATUS_08_15
DCB_BITSLIP_OK_15_MASK                   =                      0x40000000
DCB_BITSLIP_OK_15_OFS                    =                              30

# DELAY_OK_15 - Tap delay successfully set (min. 1 valid eye position found) on slot 15
DCB_DELAY_OK_15_REG                      = DCB_REG_SERDES_STATUS_08_15
DCB_DELAY_OK_15_MASK                     =                      0x20000000
DCB_DELAY_OK_15_OFS                      =                              29

# SYNC_DONE_15 - Overall syncronization procedure completed for slot 15
DCB_SYNC_DONE_15_REG                     = DCB_REG_SERDES_STATUS_08_15
DCB_SYNC_DONE_15_MASK                    =                      0x10000000
DCB_SYNC_DONE_15_OFS                     =                              28

# IDLE_PATTERN_DETECT_14 - Idle pattern detected on slot 14
DCB_IDLE_PATTERN_DETECT_14_REG           = DCB_REG_SERDES_STATUS_08_15
DCB_IDLE_PATTERN_DETECT_14_MASK          =                      0x08000000
DCB_IDLE_PATTERN_DETECT_14_OFS           =                              27

# BITSLIP_OK_14 - Bitslip successful on slot 14
DCB_BITSLIP_OK_14_REG                    = DCB_REG_SERDES_STATUS_08_15
DCB_BITSLIP_OK_14_MASK                   =                      0x04000000
DCB_BITSLIP_OK_14_OFS                    =                              26

# DELAY_OK_14 - Tap delay successfully set (min. 1 valid eye position found) on slot 14
DCB_DELAY_OK_14_REG                      = DCB_REG_SERDES_STATUS_08_15
DCB_DELAY_OK_14_MASK                     =                      0x02000000
DCB_DELAY_OK_14_OFS                      =                              25

# SYNC_DONE_14 - Overall syncronization procedure completed for slot 14
DCB_SYNC_DONE_14_REG                     = DCB_REG_SERDES_STATUS_08_15
DCB_SYNC_DONE_14_MASK                    =                      0x01000000
DCB_SYNC_DONE_14_OFS                     =                              24

# IDLE_PATTERN_DETECT_13 - Idle pattern detected on slot 13
DCB_IDLE_PATTERN_DETECT_13_REG           = DCB_REG_SERDES_STATUS_08_15
DCB_IDLE_PATTERN_DETECT_13_MASK          =                      0x00800000
DCB_IDLE_PATTERN_DETECT_13_OFS           =                              23

# BITSLIP_OK_13 - Bitslip successful on slot 13
DCB_BITSLIP_OK_13_REG                    = DCB_REG_SERDES_STATUS_08_15
DCB_BITSLIP_OK_13_MASK                   =                      0x00400000
DCB_BITSLIP_OK_13_OFS                    =                              22

# DELAY_OK_13 - Tap delay successfully set (min. 1 valid eye position found) on slot 13
DCB_DELAY_OK_13_REG                      = DCB_REG_SERDES_STATUS_08_15
DCB_DELAY_OK_13_MASK                     =                      0x00200000
DCB_DELAY_OK_13_OFS                      =                              21

# SYNC_DONE_13 - Overall syncronization procedure completed for slot 13
DCB_SYNC_DONE_13_REG                     = DCB_REG_SERDES_STATUS_08_15
DCB_SYNC_DONE_13_MASK                    =                      0x00100000
DCB_SYNC_DONE_13_OFS                     =                              20

# IDLE_PATTERN_DETECT_12 - Idle pattern detected on slot 12
DCB_IDLE_PATTERN_DETECT_12_REG           = DCB_REG_SERDES_STATUS_08_15
DCB_IDLE_PATTERN_DETECT_12_MASK          =                      0x00080000
DCB_IDLE_PATTERN_DETECT_12_OFS           =                              19

# BITSLIP_OK_12 - Bitslip successful on slot 12
DCB_BITSLIP_OK_12_REG                    = DCB_REG_SERDES_STATUS_08_15
DCB_BITSLIP_OK_12_MASK                   =                      0x00040000
DCB_BITSLIP_OK_12_OFS                    =                              18

# DELAY_OK_12 - Tap delay successfully set (min. 1 valid eye position found) on slot 12
DCB_DELAY_OK_12_REG                      = DCB_REG_SERDES_STATUS_08_15
DCB_DELAY_OK_12_MASK                     =                      0x00020000
DCB_DELAY_OK_12_OFS                      =                              17

# SYNC_DONE_12 - Overall syncronization procedure completed for slot 12
DCB_SYNC_DONE_12_REG                     = DCB_REG_SERDES_STATUS_08_15
DCB_SYNC_DONE_12_MASK                    =                      0x00010000
DCB_SYNC_DONE_12_OFS                     =                              16

# IDLE_PATTERN_DETECT_11 - Idle pattern detected on slot 11
DCB_IDLE_PATTERN_DETECT_11_REG           = DCB_REG_SERDES_STATUS_08_15
DCB_IDLE_PATTERN_DETECT_11_MASK          =                      0x00008000
DCB_IDLE_PATTERN_DETECT_11_OFS           =                              15

# BITSLIP_OK_11 - Bitslip successful on slot 11
DCB_BITSLIP_OK_11_REG                    = DCB_REG_SERDES_STATUS_08_15
DCB_BITSLIP_OK_11_MASK                   =                      0x00004000
DCB_BITSLIP_OK_11_OFS                    =                              14

# DELAY_OK_11 - Tap delay successfully set (min. 1 valid eye position found) on slot 11
DCB_DELAY_OK_11_REG                      = DCB_REG_SERDES_STATUS_08_15
DCB_DELAY_OK_11_MASK                     =                      0x00002000
DCB_DELAY_OK_11_OFS                      =                              13

# SYNC_DONE_11 - Overall syncronization procedure completed for slot 11
DCB_SYNC_DONE_11_REG                     = DCB_REG_SERDES_STATUS_08_15
DCB_SYNC_DONE_11_MASK                    =                      0x00001000
DCB_SYNC_DONE_11_OFS                     =                              12

# IDLE_PATTERN_DETECT_10 - Idle pattern detected on slot 10
DCB_IDLE_PATTERN_DETECT_10_REG           = DCB_REG_SERDES_STATUS_08_15
DCB_IDLE_PATTERN_DETECT_10_MASK          =                      0x00000800
DCB_IDLE_PATTERN_DETECT_10_OFS           =                              11

# BITSLIP_OK_10 - Bitslip successful on slot 10
DCB_BITSLIP_OK_10_REG                    = DCB_REG_SERDES_STATUS_08_15
DCB_BITSLIP_OK_10_MASK                   =                      0x00000400
DCB_BITSLIP_OK_10_OFS                    =                              10

# DELAY_OK_10 - Tap delay successfully set (min. 1 valid eye position found) on slot 10
DCB_DELAY_OK_10_REG                      = DCB_REG_SERDES_STATUS_08_15
DCB_DELAY_OK_10_MASK                     =                      0x00000200
DCB_DELAY_OK_10_OFS                      =                               9

# SYNC_DONE_10 - Overall syncronization procedure completed for slot 10
DCB_SYNC_DONE_10_REG                     = DCB_REG_SERDES_STATUS_08_15
DCB_SYNC_DONE_10_MASK                    =                      0x00000100
DCB_SYNC_DONE_10_OFS                     =                               8

# IDLE_PATTERN_DETECT_09 - Idle pattern detected on slot 9
DCB_IDLE_PATTERN_DETECT_09_REG           = DCB_REG_SERDES_STATUS_08_15
DCB_IDLE_PATTERN_DETECT_09_MASK          =                      0x00000080
DCB_IDLE_PATTERN_DETECT_09_OFS           =                               7

# BITSLIP_OK_09 - Bitslip successful on slot 9
DCB_BITSLIP_OK_09_REG                    = DCB_REG_SERDES_STATUS_08_15
DCB_BITSLIP_OK_09_MASK                   =                      0x00000040
DCB_BITSLIP_OK_09_OFS                    =                               6

# DELAY_OK_09 - Tap delay successfully set (min. 1 valid eye position found) on slot 9
DCB_DELAY_OK_09_REG                      = DCB_REG_SERDES_STATUS_08_15
DCB_DELAY_OK_09_MASK                     =                      0x00000020
DCB_DELAY_OK_09_OFS                      =                               5

# SYNC_DONE_09 - Overall syncronization procedure completed for slot 9
DCB_SYNC_DONE_09_REG                     = DCB_REG_SERDES_STATUS_08_15
DCB_SYNC_DONE_09_MASK                    =                      0x00000010
DCB_SYNC_DONE_09_OFS                     =                               4

# IDLE_PATTERN_DETECT_08 - Idle pattern detected on slot 8
DCB_IDLE_PATTERN_DETECT_08_REG           = DCB_REG_SERDES_STATUS_08_15
DCB_IDLE_PATTERN_DETECT_08_MASK          =                      0x00000008
DCB_IDLE_PATTERN_DETECT_08_OFS           =                               3

# BITSLIP_OK_08 - Bitslip successful on slot 8
DCB_BITSLIP_OK_08_REG                    = DCB_REG_SERDES_STATUS_08_15
DCB_BITSLIP_OK_08_MASK                   =                      0x00000004
DCB_BITSLIP_OK_08_OFS                    =                               2

# DELAY_OK_08 - Tap delay successfully set (min. 1 valid eye position found) on slot 8
DCB_DELAY_OK_08_REG                      = DCB_REG_SERDES_STATUS_08_15
DCB_DELAY_OK_08_MASK                     =                      0x00000002
DCB_DELAY_OK_08_OFS                      =                               1

# SYNC_DONE_08 - Overall syncronization procedure completed for slot 8
DCB_SYNC_DONE_08_REG                     = DCB_REG_SERDES_STATUS_08_15
DCB_SYNC_DONE_08_MASK                    =                      0x00000001
DCB_SYNC_DONE_08_OFS                     =                               0



# ****** Register 25 [0x0064]: SERDES_STATUS_17 - Input Serdes status for slot 17 (TCB slot) (Default: 0x00000000) ******

# IDLE_PATTERN_DETECT_17 - Idle pattern detected on slot 17
DCB_IDLE_PATTERN_DETECT_17_REG           =    DCB_REG_SERDES_STATUS_17
DCB_IDLE_PATTERN_DETECT_17_MASK          =                      0x00000008
DCB_IDLE_PATTERN_DETECT_17_OFS           =                               3

# BITSLIP_OK_17 - Bitslip successful on slot 17
DCB_BITSLIP_OK_17_REG                    =    DCB_REG_SERDES_STATUS_17
DCB_BITSLIP_OK_17_MASK                   =                      0x00000004
DCB_BITSLIP_OK_17_OFS                    =                               2

# DELAY_OK_17 - Tap delay successfully set (min. 1 valid eye position found) on slot 17
DCB_DELAY_OK_17_REG                      =    DCB_REG_SERDES_STATUS_17
DCB_DELAY_OK_17_MASK                     =                      0x00000002
DCB_DELAY_OK_17_OFS                      =                               1

# SYNC_DONE_17 - Overall syncronization procedure completed for slot 17
DCB_SYNC_DONE_17_REG                     =    DCB_REG_SERDES_STATUS_17
DCB_SYNC_DONE_17_MASK                    =                      0x00000001
DCB_SYNC_DONE_17_OFS                     =                               0



# ****** Register 26 [0x0068]: SERDES_ERR_CNT_00 - Input Serdes error count for slot 0 (Default: 0x00000000) ******

# CRC_ERRORS_00 - CRC error count of input serdes on slot 0 (255 = overflow)
DCB_CRC_ERRORS_00_REG                    =   DCB_REG_SERDES_ERR_CNT_00
DCB_CRC_ERRORS_00_MASK                   =                      0xFF000000
DCB_CRC_ERRORS_00_OFS                    =                              24

# FRAME_ERRORS_00 - Frame error count of input serdes on slot 0 (255 = overflow)
DCB_FRAME_ERRORS_00_REG                  =   DCB_REG_SERDES_ERR_CNT_00
DCB_FRAME_ERRORS_00_MASK                 =                      0x00FF0000
DCB_FRAME_ERRORS_00_OFS                  =                              16

# DATAGRAM_ERRORS_00 - Datagram error count of input serdes on slot 0 (255 = overflow)
DCB_DATAGRAM_ERRORS_00_REG               =   DCB_REG_SERDES_ERR_CNT_00
DCB_DATAGRAM_ERRORS_00_MASK              =                      0x0000FF00
DCB_DATAGRAM_ERRORS_00_OFS               =                               8

# SYNC_ERRORS_00 - Sync error count of input serdes on slot 0 (255 = overflow)
DCB_SYNC_ERRORS_00_REG                   =   DCB_REG_SERDES_ERR_CNT_00
DCB_SYNC_ERRORS_00_MASK                  =                      0x000000FF
DCB_SYNC_ERRORS_00_OFS                   =                               0



# ****** Register 27 [0x006C]: SERDES_ERR_CNT_01 - Input Serdes error count for slot 1 (Default: 0x00000000) ******

# CRC_ERRORS_01 - CRC error count of input serdes on slot 1 (255 = overflow)
DCB_CRC_ERRORS_01_REG                    =   DCB_REG_SERDES_ERR_CNT_01
DCB_CRC_ERRORS_01_MASK                   =                      0xFF000000
DCB_CRC_ERRORS_01_OFS                    =                              24

# FRAME_ERRORS_01 - Frame error count of input serdes on slot 1 (255 = overflow)
DCB_FRAME_ERRORS_01_REG                  =   DCB_REG_SERDES_ERR_CNT_01
DCB_FRAME_ERRORS_01_MASK                 =                      0x00FF0000
DCB_FRAME_ERRORS_01_OFS                  =                              16

# DATAGRAM_ERRORS_01 - Datagram error count of input serdes on slot 1 (255 = overflow)
DCB_DATAGRAM_ERRORS_01_REG               =   DCB_REG_SERDES_ERR_CNT_01
DCB_DATAGRAM_ERRORS_01_MASK              =                      0x0000FF00
DCB_DATAGRAM_ERRORS_01_OFS               =                               8

# SYNC_ERRORS_01 - Sync error count of input serdes on slot 1 (255 = overflow)
DCB_SYNC_ERRORS_01_REG                   =   DCB_REG_SERDES_ERR_CNT_01
DCB_SYNC_ERRORS_01_MASK                  =                      0x000000FF
DCB_SYNC_ERRORS_01_OFS                   =                               0



# ****** Register 28 [0x0070]: SERDES_ERR_CNT_02 - Input Serdes error count for slot 2 (Default: 0x00000000) ******

# CRC_ERRORS_02 - CRC error count of input serdes on slot 2 (255 = overflow)
DCB_CRC_ERRORS_02_REG                    =   DCB_REG_SERDES_ERR_CNT_02
DCB_CRC_ERRORS_02_MASK                   =                      0xFF000000
DCB_CRC_ERRORS_02_OFS                    =                              24

# FRAME_ERRORS_02 - Frame error count of input serdes on slot 2 (255 = overflow)
DCB_FRAME_ERRORS_02_REG                  =   DCB_REG_SERDES_ERR_CNT_02
DCB_FRAME_ERRORS_02_MASK                 =                      0x00FF0000
DCB_FRAME_ERRORS_02_OFS                  =                              16

# DATAGRAM_ERRORS_02 - Datagram error count of input serdes on slot 2 (255 = overflow)
DCB_DATAGRAM_ERRORS_02_REG               =   DCB_REG_SERDES_ERR_CNT_02
DCB_DATAGRAM_ERRORS_02_MASK              =                      0x0000FF00
DCB_DATAGRAM_ERRORS_02_OFS               =                               8

# SYNC_ERRORS_02 - Sync error count of input serdes on slot 2 (255 = overflow)
DCB_SYNC_ERRORS_02_REG                   =   DCB_REG_SERDES_ERR_CNT_02
DCB_SYNC_ERRORS_02_MASK                  =                      0x000000FF
DCB_SYNC_ERRORS_02_OFS                   =                               0



# ****** Register 29 [0x0074]: SERDES_ERR_CNT_03 - Input Serdes error count for slot 3 (Default: 0x00000000) ******

# CRC_ERRORS_03 - CRC error count of input serdes on slot 3 (255 = overflow)
DCB_CRC_ERRORS_03_REG                    =   DCB_REG_SERDES_ERR_CNT_03
DCB_CRC_ERRORS_03_MASK                   =                      0xFF000000
DCB_CRC_ERRORS_03_OFS                    =                              24

# FRAME_ERRORS_03 - Frame error count of input serdes on slot 3 (255 = overflow)
DCB_FRAME_ERRORS_03_REG                  =   DCB_REG_SERDES_ERR_CNT_03
DCB_FRAME_ERRORS_03_MASK                 =                      0x00FF0000
DCB_FRAME_ERRORS_03_OFS                  =                              16

# DATAGRAM_ERRORS_03 - Datagram error count of input serdes on slot 3 (255 = overflow)
DCB_DATAGRAM_ERRORS_03_REG               =   DCB_REG_SERDES_ERR_CNT_03
DCB_DATAGRAM_ERRORS_03_MASK              =                      0x0000FF00
DCB_DATAGRAM_ERRORS_03_OFS               =                               8

# SYNC_ERRORS_03 - Sync error count of input serdes on slot 3 (255 = overflow)
DCB_SYNC_ERRORS_03_REG                   =   DCB_REG_SERDES_ERR_CNT_03
DCB_SYNC_ERRORS_03_MASK                  =                      0x000000FF
DCB_SYNC_ERRORS_03_OFS                   =                               0



# ****** Register 30 [0x0078]: SERDES_ERR_CNT_04 - Input Serdes error count for slot 4 (Default: 0x00000000) ******

# CRC_ERRORS_04 - CRC error count of input serdes on slot 4 (255 = overflow)
DCB_CRC_ERRORS_04_REG                    =   DCB_REG_SERDES_ERR_CNT_04
DCB_CRC_ERRORS_04_MASK                   =                      0xFF000000
DCB_CRC_ERRORS_04_OFS                    =                              24

# FRAME_ERRORS_04 - Frame error count of input serdes on slot 4 (255 = overflow)
DCB_FRAME_ERRORS_04_REG                  =   DCB_REG_SERDES_ERR_CNT_04
DCB_FRAME_ERRORS_04_MASK                 =                      0x00FF0000
DCB_FRAME_ERRORS_04_OFS                  =                              16

# DATAGRAM_ERRORS_04 - Datagram error count of input serdes on slot 4 (255 = overflow)
DCB_DATAGRAM_ERRORS_04_REG               =   DCB_REG_SERDES_ERR_CNT_04
DCB_DATAGRAM_ERRORS_04_MASK              =                      0x0000FF00
DCB_DATAGRAM_ERRORS_04_OFS               =                               8

# SYNC_ERRORS_04 - Sync error count of input serdes on slot 4 (255 = overflow)
DCB_SYNC_ERRORS_04_REG                   =   DCB_REG_SERDES_ERR_CNT_04
DCB_SYNC_ERRORS_04_MASK                  =                      0x000000FF
DCB_SYNC_ERRORS_04_OFS                   =                               0



# ****** Register 31 [0x007C]: SERDES_ERR_CNT_05 - Input Serdes error count for slot 5 (Default: 0x00000000) ******

# CRC_ERRORS_05 - CRC error count of input serdes on slot 5 (255 = overflow)
DCB_CRC_ERRORS_05_REG                    =   DCB_REG_SERDES_ERR_CNT_05
DCB_CRC_ERRORS_05_MASK                   =                      0xFF000000
DCB_CRC_ERRORS_05_OFS                    =                              24

# FRAME_ERRORS_05 - Frame error count of input serdes on slot 5 (255 = overflow)
DCB_FRAME_ERRORS_05_REG                  =   DCB_REG_SERDES_ERR_CNT_05
DCB_FRAME_ERRORS_05_MASK                 =                      0x00FF0000
DCB_FRAME_ERRORS_05_OFS                  =                              16

# DATAGRAM_ERRORS_05 - Datagram error count of input serdes on slot 5 (255 = overflow)
DCB_DATAGRAM_ERRORS_05_REG               =   DCB_REG_SERDES_ERR_CNT_05
DCB_DATAGRAM_ERRORS_05_MASK              =                      0x0000FF00
DCB_DATAGRAM_ERRORS_05_OFS               =                               8

# SYNC_ERRORS_05 - Sync error count of input serdes on slot 5 (255 = overflow)
DCB_SYNC_ERRORS_05_REG                   =   DCB_REG_SERDES_ERR_CNT_05
DCB_SYNC_ERRORS_05_MASK                  =                      0x000000FF
DCB_SYNC_ERRORS_05_OFS                   =                               0



# ****** Register 32 [0x0080]: SERDES_ERR_CNT_06 - Input Serdes error count for slot 6 (Default: 0x00000000) ******

# CRC_ERRORS_06 - CRC error count of input serdes on slot 6 (255 = overflow)
DCB_CRC_ERRORS_06_REG                    =   DCB_REG_SERDES_ERR_CNT_06
DCB_CRC_ERRORS_06_MASK                   =                      0xFF000000
DCB_CRC_ERRORS_06_OFS                    =                              24

# FRAME_ERRORS_06 - Frame error count of input serdes on slot 6 (255 = overflow)
DCB_FRAME_ERRORS_06_REG                  =   DCB_REG_SERDES_ERR_CNT_06
DCB_FRAME_ERRORS_06_MASK                 =                      0x00FF0000
DCB_FRAME_ERRORS_06_OFS                  =                              16

# DATAGRAM_ERRORS_06 - Datagram error count of input serdes on slot 6 (255 = overflow)
DCB_DATAGRAM_ERRORS_06_REG               =   DCB_REG_SERDES_ERR_CNT_06
DCB_DATAGRAM_ERRORS_06_MASK              =                      0x0000FF00
DCB_DATAGRAM_ERRORS_06_OFS               =                               8

# SYNC_ERRORS_06 - Sync error count of input serdes on slot 6 (255 = overflow)
DCB_SYNC_ERRORS_06_REG                   =   DCB_REG_SERDES_ERR_CNT_06
DCB_SYNC_ERRORS_06_MASK                  =                      0x000000FF
DCB_SYNC_ERRORS_06_OFS                   =                               0



# ****** Register 33 [0x0084]: SERDES_ERR_CNT_07 - Input Serdes error count for slot 7 (Default: 0x00000000) ******

# CRC_ERRORS_07 - CRC error count of input serdes on slot 7 (255 = overflow)
DCB_CRC_ERRORS_07_REG                    =   DCB_REG_SERDES_ERR_CNT_07
DCB_CRC_ERRORS_07_MASK                   =                      0xFF000000
DCB_CRC_ERRORS_07_OFS                    =                              24

# FRAME_ERRORS_07 - Frame error count of input serdes on slot 7 (255 = overflow)
DCB_FRAME_ERRORS_07_REG                  =   DCB_REG_SERDES_ERR_CNT_07
DCB_FRAME_ERRORS_07_MASK                 =                      0x00FF0000
DCB_FRAME_ERRORS_07_OFS                  =                              16

# DATAGRAM_ERRORS_07 - Datagram error count of input serdes on slot 7 (255 = overflow)
DCB_DATAGRAM_ERRORS_07_REG               =   DCB_REG_SERDES_ERR_CNT_07
DCB_DATAGRAM_ERRORS_07_MASK              =                      0x0000FF00
DCB_DATAGRAM_ERRORS_07_OFS               =                               8

# SYNC_ERRORS_07 - Sync error count of input serdes on slot 7 (255 = overflow)
DCB_SYNC_ERRORS_07_REG                   =   DCB_REG_SERDES_ERR_CNT_07
DCB_SYNC_ERRORS_07_MASK                  =                      0x000000FF
DCB_SYNC_ERRORS_07_OFS                   =                               0



# ****** Register 34 [0x0088]: SERDES_ERR_CNT_08 - Input Serdes error count for slot 8 (Default: 0x00000000) ******

# CRC_ERRORS_08 - CRC error count of input serdes on slot 8 (255 = overflow)
DCB_CRC_ERRORS_08_REG                    =   DCB_REG_SERDES_ERR_CNT_08
DCB_CRC_ERRORS_08_MASK                   =                      0xFF000000
DCB_CRC_ERRORS_08_OFS                    =                              24

# FRAME_ERRORS_08 - Frame error count of input serdes on slot 8 (255 = overflow)
DCB_FRAME_ERRORS_08_REG                  =   DCB_REG_SERDES_ERR_CNT_08
DCB_FRAME_ERRORS_08_MASK                 =                      0x00FF0000
DCB_FRAME_ERRORS_08_OFS                  =                              16

# DATAGRAM_ERRORS_08 - Datagram error count of input serdes on slot 8 (255 = overflow)
DCB_DATAGRAM_ERRORS_08_REG               =   DCB_REG_SERDES_ERR_CNT_08
DCB_DATAGRAM_ERRORS_08_MASK              =                      0x0000FF00
DCB_DATAGRAM_ERRORS_08_OFS               =                               8

# SYNC_ERRORS_08 - Sync error count of input serdes on slot 8 (255 = overflow)
DCB_SYNC_ERRORS_08_REG                   =   DCB_REG_SERDES_ERR_CNT_08
DCB_SYNC_ERRORS_08_MASK                  =                      0x000000FF
DCB_SYNC_ERRORS_08_OFS                   =                               0



# ****** Register 35 [0x008C]: SERDES_ERR_CNT_09 - Input Serdes error count for slot 9 (Default: 0x00000000) ******

# CRC_ERRORS_09 - CRC error count of input serdes on slot 9 (255 = overflow)
DCB_CRC_ERRORS_09_REG                    =   DCB_REG_SERDES_ERR_CNT_09
DCB_CRC_ERRORS_09_MASK                   =                      0xFF000000
DCB_CRC_ERRORS_09_OFS                    =                              24

# FRAME_ERRORS_09 - Frame error count of input serdes on slot 9 (255 = overflow)
DCB_FRAME_ERRORS_09_REG                  =   DCB_REG_SERDES_ERR_CNT_09
DCB_FRAME_ERRORS_09_MASK                 =                      0x00FF0000
DCB_FRAME_ERRORS_09_OFS                  =                              16

# DATAGRAM_ERRORS_09 - Datagram error count of input serdes on slot 9 (255 = overflow)
DCB_DATAGRAM_ERRORS_09_REG               =   DCB_REG_SERDES_ERR_CNT_09
DCB_DATAGRAM_ERRORS_09_MASK              =                      0x0000FF00
DCB_DATAGRAM_ERRORS_09_OFS               =                               8

# SYNC_ERRORS_09 - Sync error count of input serdes on slot 9 (255 = overflow)
DCB_SYNC_ERRORS_09_REG                   =   DCB_REG_SERDES_ERR_CNT_09
DCB_SYNC_ERRORS_09_MASK                  =                      0x000000FF
DCB_SYNC_ERRORS_09_OFS                   =                               0



# ****** Register 36 [0x0090]: SERDES_ERR_CNT_10 - Input Serdes error count for slot 10 (Default: 0x00000000) ******

# CRC_ERRORS_10 - CRC error count of input serdes on slot 10 (255 = overflow)
DCB_CRC_ERRORS_10_REG                    =   DCB_REG_SERDES_ERR_CNT_10
DCB_CRC_ERRORS_10_MASK                   =                      0xFF000000
DCB_CRC_ERRORS_10_OFS                    =                              24

# FRAME_ERRORS_10 - Frame error count of input serdes on slot 10 (255 = overflow)
DCB_FRAME_ERRORS_10_REG                  =   DCB_REG_SERDES_ERR_CNT_10
DCB_FRAME_ERRORS_10_MASK                 =                      0x00FF0000
DCB_FRAME_ERRORS_10_OFS                  =                              16

# DATAGRAM_ERRORS_10 - Datagram error count of input serdes on slot 10 (255 = overflow)
DCB_DATAGRAM_ERRORS_10_REG               =   DCB_REG_SERDES_ERR_CNT_10
DCB_DATAGRAM_ERRORS_10_MASK              =                      0x0000FF00
DCB_DATAGRAM_ERRORS_10_OFS               =                               8

# SYNC_ERRORS_10 - Sync error count of input serdes on slot 10 (255 = overflow)
DCB_SYNC_ERRORS_10_REG                   =   DCB_REG_SERDES_ERR_CNT_10
DCB_SYNC_ERRORS_10_MASK                  =                      0x000000FF
DCB_SYNC_ERRORS_10_OFS                   =                               0



# ****** Register 37 [0x0094]: SERDES_ERR_CNT_11 - Input Serdes error count for slot 11 (Default: 0x00000000) ******

# CRC_ERRORS_11 - CRC error count of input serdes on slot 11 (255 = overflow)
DCB_CRC_ERRORS_11_REG                    =   DCB_REG_SERDES_ERR_CNT_11
DCB_CRC_ERRORS_11_MASK                   =                      0xFF000000
DCB_CRC_ERRORS_11_OFS                    =                              24

# FRAME_ERRORS_11 - Frame error count of input serdes on slot 11 (255 = overflow)
DCB_FRAME_ERRORS_11_REG                  =   DCB_REG_SERDES_ERR_CNT_11
DCB_FRAME_ERRORS_11_MASK                 =                      0x00FF0000
DCB_FRAME_ERRORS_11_OFS                  =                              16

# DATAGRAM_ERRORS_11 - Datagram error count of input serdes on slot 11 (255 = overflow)
DCB_DATAGRAM_ERRORS_11_REG               =   DCB_REG_SERDES_ERR_CNT_11
DCB_DATAGRAM_ERRORS_11_MASK              =                      0x0000FF00
DCB_DATAGRAM_ERRORS_11_OFS               =                               8

# SYNC_ERRORS_11 - Sync error count of input serdes on slot 11 (255 = overflow)
DCB_SYNC_ERRORS_11_REG                   =   DCB_REG_SERDES_ERR_CNT_11
DCB_SYNC_ERRORS_11_MASK                  =                      0x000000FF
DCB_SYNC_ERRORS_11_OFS                   =                               0



# ****** Register 38 [0x0098]: SERDES_ERR_CNT_12 - Input Serdes error count for slot 12 (Default: 0x00000000) ******

# CRC_ERRORS_12 - CRC error count of input serdes on slot 12 (255 = overflow)
DCB_CRC_ERRORS_12_REG                    =   DCB_REG_SERDES_ERR_CNT_12
DCB_CRC_ERRORS_12_MASK                   =                      0xFF000000
DCB_CRC_ERRORS_12_OFS                    =                              24

# FRAME_ERRORS_12 - Frame error count of input serdes on slot 12 (255 = overflow)
DCB_FRAME_ERRORS_12_REG                  =   DCB_REG_SERDES_ERR_CNT_12
DCB_FRAME_ERRORS_12_MASK                 =                      0x00FF0000
DCB_FRAME_ERRORS_12_OFS                  =                              16

# DATAGRAM_ERRORS_12 - Datagram error count of input serdes on slot 12 (255 = overflow)
DCB_DATAGRAM_ERRORS_12_REG               =   DCB_REG_SERDES_ERR_CNT_12
DCB_DATAGRAM_ERRORS_12_MASK              =                      0x0000FF00
DCB_DATAGRAM_ERRORS_12_OFS               =                               8

# SYNC_ERRORS_12 - Sync error count of input serdes on slot 12 (255 = overflow)
DCB_SYNC_ERRORS_12_REG                   =   DCB_REG_SERDES_ERR_CNT_12
DCB_SYNC_ERRORS_12_MASK                  =                      0x000000FF
DCB_SYNC_ERRORS_12_OFS                   =                               0



# ****** Register 39 [0x009C]: SERDES_ERR_CNT_13 - Input Serdes error count for slot 13 (Default: 0x00000000) ******

# CRC_ERRORS_13 - CRC error count of input serdes on slot 13 (255 = overflow)
DCB_CRC_ERRORS_13_REG                    =   DCB_REG_SERDES_ERR_CNT_13
DCB_CRC_ERRORS_13_MASK                   =                      0xFF000000
DCB_CRC_ERRORS_13_OFS                    =                              24

# FRAME_ERRORS_13 - Frame error count of input serdes on slot 13 (255 = overflow)
DCB_FRAME_ERRORS_13_REG                  =   DCB_REG_SERDES_ERR_CNT_13
DCB_FRAME_ERRORS_13_MASK                 =                      0x00FF0000
DCB_FRAME_ERRORS_13_OFS                  =                              16

# DATAGRAM_ERRORS_13 - Datagram error count of input serdes on slot 13 (255 = overflow)
DCB_DATAGRAM_ERRORS_13_REG               =   DCB_REG_SERDES_ERR_CNT_13
DCB_DATAGRAM_ERRORS_13_MASK              =                      0x0000FF00
DCB_DATAGRAM_ERRORS_13_OFS               =                               8

# SYNC_ERRORS_13 - Sync error count of input serdes on slot 13 (255 = overflow)
DCB_SYNC_ERRORS_13_REG                   =   DCB_REG_SERDES_ERR_CNT_13
DCB_SYNC_ERRORS_13_MASK                  =                      0x000000FF
DCB_SYNC_ERRORS_13_OFS                   =                               0



# ****** Register 40 [0x00A0]: SERDES_ERR_CNT_14 - Input Serdes error count for slot 14 (Default: 0x00000000) ******

# CRC_ERRORS_14 - CRC error count of input serdes on slot 14 (255 = overflow)
DCB_CRC_ERRORS_14_REG                    =   DCB_REG_SERDES_ERR_CNT_14
DCB_CRC_ERRORS_14_MASK                   =                      0xFF000000
DCB_CRC_ERRORS_14_OFS                    =                              24

# FRAME_ERRORS_14 - Frame error count of input serdes on slot 14 (255 = overflow)
DCB_FRAME_ERRORS_14_REG                  =   DCB_REG_SERDES_ERR_CNT_14
DCB_FRAME_ERRORS_14_MASK                 =                      0x00FF0000
DCB_FRAME_ERRORS_14_OFS                  =                              16

# DATAGRAM_ERRORS_14 - Datagram error count of input serdes on slot 14 (255 = overflow)
DCB_DATAGRAM_ERRORS_14_REG               =   DCB_REG_SERDES_ERR_CNT_14
DCB_DATAGRAM_ERRORS_14_MASK              =                      0x0000FF00
DCB_DATAGRAM_ERRORS_14_OFS               =                               8

# SYNC_ERRORS_14 - Sync error count of input serdes on slot 14 (255 = overflow)
DCB_SYNC_ERRORS_14_REG                   =   DCB_REG_SERDES_ERR_CNT_14
DCB_SYNC_ERRORS_14_MASK                  =                      0x000000FF
DCB_SYNC_ERRORS_14_OFS                   =                               0



# ****** Register 41 [0x00A4]: SERDES_ERR_CNT_15 - Input Serdes error count for slot 15 (Default: 0x00000000) ******

# CRC_ERRORS_15 - CRC error count of input serdes on slot 15 (255 = overflow)
DCB_CRC_ERRORS_15_REG                    =   DCB_REG_SERDES_ERR_CNT_15
DCB_CRC_ERRORS_15_MASK                   =                      0xFF000000
DCB_CRC_ERRORS_15_OFS                    =                              24

# FRAME_ERRORS_15 - Frame error count of input serdes on slot 15 (255 = overflow)
DCB_FRAME_ERRORS_15_REG                  =   DCB_REG_SERDES_ERR_CNT_15
DCB_FRAME_ERRORS_15_MASK                 =                      0x00FF0000
DCB_FRAME_ERRORS_15_OFS                  =                              16

# DATAGRAM_ERRORS_15 - Datagram error count of input serdes on slot 15 (255 = overflow)
DCB_DATAGRAM_ERRORS_15_REG               =   DCB_REG_SERDES_ERR_CNT_15
DCB_DATAGRAM_ERRORS_15_MASK              =                      0x0000FF00
DCB_DATAGRAM_ERRORS_15_OFS               =                               8

# SYNC_ERRORS_15 - Sync error count of input serdes on slot 15 (255 = overflow)
DCB_SYNC_ERRORS_15_REG                   =   DCB_REG_SERDES_ERR_CNT_15
DCB_SYNC_ERRORS_15_MASK                  =                      0x000000FF
DCB_SYNC_ERRORS_15_OFS                   =                               0



# ****** Register 42 [0x00A8]: SERDES_ERR_CNT_17 - Input Serdes error count for slot 17 (TCB slot) (Default: 0x00000000) ******

# CRC_ERRORS_17 - CRC error count of input serdes on slot 17 (255 = overflow)
DCB_CRC_ERRORS_17_REG                    =   DCB_REG_SERDES_ERR_CNT_17
DCB_CRC_ERRORS_17_MASK                   =                      0xFF000000
DCB_CRC_ERRORS_17_OFS                    =                              24

# FRAME_ERRORS_17 - Frame error count of input serdes on slot 17 (255 = overflow)
DCB_FRAME_ERRORS_17_REG                  =   DCB_REG_SERDES_ERR_CNT_17
DCB_FRAME_ERRORS_17_MASK                 =                      0x00FF0000
DCB_FRAME_ERRORS_17_OFS                  =                              16

# DATAGRAM_ERRORS_17 - Datagram error count of input serdes on slot 17 (255 = overflow)
DCB_DATAGRAM_ERRORS_17_REG               =   DCB_REG_SERDES_ERR_CNT_17
DCB_DATAGRAM_ERRORS_17_MASK              =                      0x0000FF00
DCB_DATAGRAM_ERRORS_17_OFS               =                               8

# SYNC_ERRORS_17 - Sync error count of input serdes on slot 17 (255 = overflow)
DCB_SYNC_ERRORS_17_REG                   =   DCB_REG_SERDES_ERR_CNT_17
DCB_SYNC_ERRORS_17_MASK                  =                      0x000000FF
DCB_SYNC_ERRORS_17_OFS                   =                               0



# ****** Register 43 [0x00AC]: APLY_CFG - Apply settings from regsiter bank to hardware units (Default: 0x00000000) ******

# APPLY_SETTINGS_LMK - Apply configuration from regsiter bank to LMK
DCB_APPLY_SETTINGS_LMK_REG               =            DCB_REG_APLY_CFG
DCB_APPLY_SETTINGS_LMK_MASK              =                      0x00000001
DCB_APPLY_SETTINGS_LMK_OFS               =                               0



# ****** Register 44 [0x00B0]: LMK_0 - LMK Register 0 (Default: 0x00020100) ******

# LMK0_RESET - Resets LMK Registers to Their Power-On State
DCB_LMK0_RESET_REG                       =               DCB_REG_LMK_0
DCB_LMK0_RESET_MASK                      =                      0x80000000
DCB_LMK0_RESET_OFS                       =                              31

# LMK0_CLKOUT_MUX - Channel 0 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed)
DCB_LMK0_CLKOUT_MUX_REG                  =               DCB_REG_LMK_0
DCB_LMK0_CLKOUT_MUX_MASK                 =                      0x00060000
DCB_LMK0_CLKOUT_MUX_OFS                  =                              17

# LMK0_CLKOUT_EN - Channel 0 Clock Output Enable (0 = Disabled, 1 = Enabled)
DCB_LMK0_CLKOUT_EN_REG                   =               DCB_REG_LMK_0
DCB_LMK0_CLKOUT_EN_MASK                  =                      0x00010000
DCB_LMK0_CLKOUT_EN_OFS                   =                              16

# LMK0_CLKOUT_DIV - Channel 0 Clock Output Divider (value x 2) (1..255)
DCB_LMK0_CLKOUT_DIV_REG                  =               DCB_REG_LMK_0
DCB_LMK0_CLKOUT_DIV_MASK                 =                      0x0000FF00
DCB_LMK0_CLKOUT_DIV_OFS                  =                               8

# LMK0_CLKOUT_DLY - Channel 0 Clock Output Delay (value x 150ps)
DCB_LMK0_CLKOUT_DLY_REG                  =               DCB_REG_LMK_0
DCB_LMK0_CLKOUT_DLY_MASK                 =                      0x000000F0
DCB_LMK0_CLKOUT_DLY_OFS                  =                               4



# ****** Register 45 [0x00B4]: LMK_1 - LMK Register 1 (Default: 0x00030101) ******

# LMK1_CLKOUT_MUX - Channel 1 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed)
DCB_LMK1_CLKOUT_MUX_REG                  =               DCB_REG_LMK_1
DCB_LMK1_CLKOUT_MUX_MASK                 =                      0x00060000
DCB_LMK1_CLKOUT_MUX_OFS                  =                              17

# LMK1_CLKOUT_EN - Channel 1 Clock Output Enable (0 = Disabled, 1 = Enabled)
DCB_LMK1_CLKOUT_EN_REG                   =               DCB_REG_LMK_1
DCB_LMK1_CLKOUT_EN_MASK                  =                      0x00010000
DCB_LMK1_CLKOUT_EN_OFS                   =                              16

# LMK1_CLKOUT_DIV - Channel 1 Clock Output Divider (value x 2) (1..255)
DCB_LMK1_CLKOUT_DIV_REG                  =               DCB_REG_LMK_1
DCB_LMK1_CLKOUT_DIV_MASK                 =                      0x0000FF00
DCB_LMK1_CLKOUT_DIV_OFS                  =                               8

# LMK1_CLKOUT_DLY - Channel 1 Clock Output Delay (value x 150ps)
DCB_LMK1_CLKOUT_DLY_REG                  =               DCB_REG_LMK_1
DCB_LMK1_CLKOUT_DLY_MASK                 =                      0x000000F0
DCB_LMK1_CLKOUT_DLY_OFS                  =                               4



# ****** Register 46 [0x00B8]: LMK_2 - LMK Register 2 (Default: 0x00020102) ******

# LMK2_CLKOUT_MUX - Channel 2 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed)
DCB_LMK2_CLKOUT_MUX_REG                  =               DCB_REG_LMK_2
DCB_LMK2_CLKOUT_MUX_MASK                 =                      0x00060000
DCB_LMK2_CLKOUT_MUX_OFS                  =                              17

# LMK2_CLKOUT_EN - Channel 2 Clock Output Enable (0 = Disabled, 1 = Enabled)
DCB_LMK2_CLKOUT_EN_REG                   =               DCB_REG_LMK_2
DCB_LMK2_CLKOUT_EN_MASK                  =                      0x00010000
DCB_LMK2_CLKOUT_EN_OFS                   =                              16

# LMK2_CLKOUT_DIV - Channel 2 Clock Output Divider (value x 2) (1..255)
DCB_LMK2_CLKOUT_DIV_REG                  =               DCB_REG_LMK_2
DCB_LMK2_CLKOUT_DIV_MASK                 =                      0x0000FF00
DCB_LMK2_CLKOUT_DIV_OFS                  =                               8

# LMK2_CLKOUT_DLY - Channel 2 Clock Output Delay (value x 150ps)
DCB_LMK2_CLKOUT_DLY_REG                  =               DCB_REG_LMK_2
DCB_LMK2_CLKOUT_DLY_MASK                 =                      0x000000F0
DCB_LMK2_CLKOUT_DLY_OFS                  =                               4



# ****** Register 47 [0x00BC]: LMK_3 - LMK Register 3 (Default: 0x00020103) ******

# LMK3_CLKOUT_MUX - Channel 3 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed)
DCB_LMK3_CLKOUT_MUX_REG                  =               DCB_REG_LMK_3
DCB_LMK3_CLKOUT_MUX_MASK                 =                      0x00060000
DCB_LMK3_CLKOUT_MUX_OFS                  =                              17

# LMK3_CLKOUT_EN - Channel 3 Clock Output Enable (0 = Disabled, 1 = Enabled)
DCB_LMK3_CLKOUT_EN_REG                   =               DCB_REG_LMK_3
DCB_LMK3_CLKOUT_EN_MASK                  =                      0x00010000
DCB_LMK3_CLKOUT_EN_OFS                   =                              16

# LMK3_CLKOUT_DIV - Channel 3 Clock Output Divider (value x 2) (1..255)
DCB_LMK3_CLKOUT_DIV_REG                  =               DCB_REG_LMK_3
DCB_LMK3_CLKOUT_DIV_MASK                 =                      0x0000FF00
DCB_LMK3_CLKOUT_DIV_OFS                  =                               8

# LMK3_CLKOUT_DLY - Channel 3 Clock Output Delay (value x 150ps)
DCB_LMK3_CLKOUT_DLY_REG                  =               DCB_REG_LMK_3
DCB_LMK3_CLKOUT_DLY_MASK                 =                      0x000000F0
DCB_LMK3_CLKOUT_DLY_OFS                  =                               4



# ****** Register 48 [0x00C0]: LMK_4 - LMK Register 4 (Default: 0x00000104) ******

# LMK4_CLKOUT_MUX - Channel 4 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed)
DCB_LMK4_CLKOUT_MUX_REG                  =               DCB_REG_LMK_4
DCB_LMK4_CLKOUT_MUX_MASK                 =                      0x00060000
DCB_LMK4_CLKOUT_MUX_OFS                  =                              17

# LMK4_CLKOUT_EN - Channel 4 Clock Output Enable (0 = Disabled, 1 = Enabled)
DCB_LMK4_CLKOUT_EN_REG                   =               DCB_REG_LMK_4
DCB_LMK4_CLKOUT_EN_MASK                  =                      0x00010000
DCB_LMK4_CLKOUT_EN_OFS                   =                              16

# LMK4_CLKOUT_DIV - Channel 4 Clock Output Divider (value x 2) (1..255)
DCB_LMK4_CLKOUT_DIV_REG                  =               DCB_REG_LMK_4
DCB_LMK4_CLKOUT_DIV_MASK                 =                      0x0000FF00
DCB_LMK4_CLKOUT_DIV_OFS                  =                               8

# LMK4_CLKOUT_DLY - Channel 4 Clock Output Delay (value x 150ps)
DCB_LMK4_CLKOUT_DLY_REG                  =               DCB_REG_LMK_4
DCB_LMK4_CLKOUT_DLY_MASK                 =                      0x000000F0
DCB_LMK4_CLKOUT_DLY_OFS                  =                               4



# ****** Register 49 [0x00C4]: LMK_5 - LMK Register 5 (Default: 0x00000105) ******

# LMK5_CLKOUT_MUX - Channel 5 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed)
DCB_LMK5_CLKOUT_MUX_REG                  =               DCB_REG_LMK_5
DCB_LMK5_CLKOUT_MUX_MASK                 =                      0x00060000
DCB_LMK5_CLKOUT_MUX_OFS                  =                              17

# LMK5_CLKOUT_EN - Channel 5 Clock Output Enable (0 = Disabled, 1 = Enabled)
DCB_LMK5_CLKOUT_EN_REG                   =               DCB_REG_LMK_5
DCB_LMK5_CLKOUT_EN_MASK                  =                      0x00010000
DCB_LMK5_CLKOUT_EN_OFS                   =                              16

# LMK5_CLKOUT_DIV - Channel 5 Clock Output Divider (value x 2) (1..255)
DCB_LMK5_CLKOUT_DIV_REG                  =               DCB_REG_LMK_5
DCB_LMK5_CLKOUT_DIV_MASK                 =                      0x0000FF00
DCB_LMK5_CLKOUT_DIV_OFS                  =                               8

# LMK5_CLKOUT_DLY - Channel 5 Clock Output Delay (value x 150ps)
DCB_LMK5_CLKOUT_DLY_REG                  =               DCB_REG_LMK_5
DCB_LMK5_CLKOUT_DLY_MASK                 =                      0x000000F0
DCB_LMK5_CLKOUT_DLY_OFS                  =                               4



# ****** Register 50 [0x00C8]: LMK_6 - LMK Register 6 (Default: 0x00000106) ******

# LMK6_CLKOUT_MUX - Channel 6 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed)
DCB_LMK6_CLKOUT_MUX_REG                  =               DCB_REG_LMK_6
DCB_LMK6_CLKOUT_MUX_MASK                 =                      0x00060000
DCB_LMK6_CLKOUT_MUX_OFS                  =                              17

# LMK6_CLKOUT_EN - Channel 6 Clock Output Enable (0 = Disabled, 1 = Enabled)
DCB_LMK6_CLKOUT_EN_REG                   =               DCB_REG_LMK_6
DCB_LMK6_CLKOUT_EN_MASK                  =                      0x00010000
DCB_LMK6_CLKOUT_EN_OFS                   =                              16

# LMK6_CLKOUT_DIV - Channel 6 Clock Output Divider (value x 2) (1..255)
DCB_LMK6_CLKOUT_DIV_REG                  =               DCB_REG_LMK_6
DCB_LMK6_CLKOUT_DIV_MASK                 =                      0x0000FF00
DCB_LMK6_CLKOUT_DIV_OFS                  =                               8

# LMK6_CLKOUT_DLY - Channel 6 Clock Output Delay (value x 150ps)
DCB_LMK6_CLKOUT_DLY_REG                  =               DCB_REG_LMK_6
DCB_LMK6_CLKOUT_DLY_MASK                 =                      0x000000F0
DCB_LMK6_CLKOUT_DLY_OFS                  =                               4



# ****** Register 51 [0x00CC]: LMK_7 - LMK Register 7 (Default: 0x00000107) ******

# LMK7_CLKOUT_MUX - Channel 7 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed)
DCB_LMK7_CLKOUT_MUX_REG                  =               DCB_REG_LMK_7
DCB_LMK7_CLKOUT_MUX_MASK                 =                      0x00060000
DCB_LMK7_CLKOUT_MUX_OFS                  =                              17

# LMK7_CLKOUT_EN - Channel 7 Clock Output Enable (0 = Disabled, 1 = Enabled)
DCB_LMK7_CLKOUT_EN_REG                   =               DCB_REG_LMK_7
DCB_LMK7_CLKOUT_EN_MASK                  =                      0x00010000
DCB_LMK7_CLKOUT_EN_OFS                   =                              16

# LMK7_CLKOUT_DIV - Channel 7 Clock Output Divider (value x 2) (1..255)
DCB_LMK7_CLKOUT_DIV_REG                  =               DCB_REG_LMK_7
DCB_LMK7_CLKOUT_DIV_MASK                 =                      0x0000FF00
DCB_LMK7_CLKOUT_DIV_OFS                  =                               8

# LMK7_CLKOUT_DLY - Channel 7 Clock Output Delay (value x 150ps)
DCB_LMK7_CLKOUT_DLY_REG                  =               DCB_REG_LMK_7
DCB_LMK7_CLKOUT_DLY_MASK                 =                      0x000000F0
DCB_LMK7_CLKOUT_DLY_OFS                  =                               4



# ****** Register 52 [0x00D0]: LMK_8 - LMK Register 8 (Default: 0x10000908) ******

# LMK8_PHASE_NOISE_OPT - Set LMK Register 8 (Phase Noise Optimization)
DCB_LMK8_PHASE_NOISE_OPT_REG             =               DCB_REG_LMK_8
DCB_LMK8_PHASE_NOISE_OPT_MASK            =                      0xFFFFFFF0
DCB_LMK8_PHASE_NOISE_OPT_OFS             =                               4



# ****** Register 53 [0x00D4]: LMK_9 - LMK Register 9 (Default: 0xA0022A09) ******

# LMK9_VBOOST - Voltage Level Boost for Clock Outputs
DCB_LMK9_VBOOST_REG                      =               DCB_REG_LMK_9
DCB_LMK9_VBOOST_MASK                     =                      0x00010000
DCB_LMK9_VBOOST_OFS                      =                              16



# ****** Register 54 [0x00D8]: LMK_11 - LMK Register 11 (Default: 0x0082000B) ******

# LMK11_DIV4 - Divider Enable for Digital Lock Detect Circuit
DCB_LMK11_DIV4_REG                       =              DCB_REG_LMK_11
DCB_LMK11_DIV4_MASK                      =                      0x00008000
DCB_LMK11_DIV4_OFS                       =                              15



# ****** Register 55 [0x00DC]: LMK_13 - LMK Register 13 (Default: 0x029400AD) ******

# LMK13_OSCIN_FREQ - Oscillator Input Calibration Adjustment in MHz (1..200)
DCB_LMK13_OSCIN_FREQ_REG                 =              DCB_REG_LMK_13
DCB_LMK13_OSCIN_FREQ_MASK                =                      0x003FC000
DCB_LMK13_OSCIN_FREQ_OFS                 =                              14

# LMK13_VCO_R4_LF - Value for Internal Loop Filter Resistor R4 (0..4) (see datasheet)
DCB_LMK13_VCO_R4_LF_REG                  =              DCB_REG_LMK_13
DCB_LMK13_VCO_R4_LF_MASK                 =                      0x00003800
DCB_LMK13_VCO_R4_LF_OFS                  =                              11

# LMK13_VCO_R3_LF - Value for Internal Loop Filter Resistor R3 (0..4) (see datasheet)
DCB_LMK13_VCO_R3_LF_REG                  =              DCB_REG_LMK_13
DCB_LMK13_VCO_R3_LF_MASK                 =                      0x00000700
DCB_LMK13_VCO_R3_LF_OFS                  =                               8

# LMK13_VCO_C3_C4_LF - Value for Internal Loop Filter Capacitors C3/C4 (0..11) (see ds)
DCB_LMK13_VCO_C3_C4_LF_REG               =              DCB_REG_LMK_13
DCB_LMK13_VCO_C3_C4_LF_MASK              =                      0x000000F0
DCB_LMK13_VCO_C3_C4_LF_OFS               =                               4



# ****** Register 56 [0x00E0]: LMK_14 - LMK Register 14 (Default: 0x0830140E) ******

# LMK14_EN_FOUT - Enable for the Fout Pin (0 = Disabled, 1 = Enabled)
DCB_LMK14_EN_FOUT_REG                    =              DCB_REG_LMK_14
DCB_LMK14_EN_FOUT_MASK                   =                      0x10000000
DCB_LMK14_EN_FOUT_OFS                    =                              28

# LMK14_EN_CLKOUT_GLOBAL - Global Clock Output Enable (0 = All Off, 1 = Normal Operation)
DCB_LMK14_EN_CLKOUT_GLOBAL_REG           =              DCB_REG_LMK_14
DCB_LMK14_EN_CLKOUT_GLOBAL_MASK          =                      0x08000000
DCB_LMK14_EN_CLKOUT_GLOBAL_OFS           =                              27

# LMK14_POWERDOWN - Powerdown (0 = Normal Operation, 1 = Device Powered Down)
DCB_LMK14_POWERDOWN_REG                  =              DCB_REG_LMK_14
DCB_LMK14_POWERDOWN_MASK                 =                      0x04000000
DCB_LMK14_POWERDOWN_OFS                  =                              26

# LMK14_PLL_MUX - Output Mode of  LD Pin (0..7,9,11)
DCB_LMK14_PLL_MUX_REG                    =              DCB_REG_LMK_14
DCB_LMK14_PLL_MUX_MASK                   =                      0x00F00000
DCB_LMK14_PLL_MUX_OFS                    =                              20

# LMK14_PLL_R - PLL R Divider Value (1..4095)
DCB_LMK14_PLL_R_REG                      =              DCB_REG_LMK_14
DCB_LMK14_PLL_R_MASK                     =                      0x000FFF00
DCB_LMK14_PLL_R_OFS                      =                               8



# ****** Register 57 [0x00E4]: LMK_15 - LMK Register 15 (Default: 0xE000280F) ******

# LMK15_PLL_CP_GAIN - PLL Charge Pump Gain (see datasheet) (0..4)
DCB_LMK15_PLL_CP_GAIN_REG                =              DCB_REG_LMK_15
DCB_LMK15_PLL_CP_GAIN_MASK               =                      0xC0000000
DCB_LMK15_PLL_CP_GAIN_OFS                =                              30

# LMK15_VCO_DIV - VCO Divider Value (2..8)
DCB_LMK15_VCO_DIV_REG                    =              DCB_REG_LMK_15
DCB_LMK15_VCO_DIV_MASK                   =                      0x3C000000
DCB_LMK15_VCO_DIV_OFS                    =                              26

# LMK15_PLL_N - PLL N Divider Value (1..0x3FFFF)
DCB_LMK15_PLL_N_REG                      =              DCB_REG_LMK_15
DCB_LMK15_PLL_N_MASK                     =                      0x03FFFF00
DCB_LMK15_PLL_N_OFS                      =                               8



# ****** Register 58 [0x00E8]: TIME_LSB - Current System Time (Default: 0x00000000) ******

# TIME_LSB - LSBs of 64bit system time counter (MSBs are latched upon read of LSB register)
DCB_TIME_LSB_REG                         =            DCB_REG_TIME_LSB
DCB_TIME_LSB_MASK                        =                      0xFFFFFFFF
DCB_TIME_LSB_OFS                         =                               0



# ****** Register 59 [0x00EC]: TIME_MSB - Current System Time (Default: 0x00000000) ******

# TIME_MSB - MSBs of 64bit system time counter (latched upon read of LSB register)
DCB_TIME_MSB_REG                         =            DCB_REG_TIME_MSB
DCB_TIME_MSB_MASK                        =                      0xFFFFFFFF
DCB_TIME_MSB_OFS                         =                               0



# ****** Register 60 [0x00F0]: TIME_LSB_SET - Set System Time (Default: 0x00000000) ******

# TIME_LSB_SET - LSBs of 64bit system time counter set value  (time is updated when MSBs are written)
DCB_TIME_LSB_SET_REG                     =        DCB_REG_TIME_LSB_SET
DCB_TIME_LSB_SET_MASK                    =                      0xFFFFFFFF
DCB_TIME_LSB_SET_OFS                     =                               0



# ****** Register 61 [0x00F4]: TIME_MSB_SET - Set System Time (Default: 0x00000000) ******

# TIME_MSB_SET - MSBs of 64bit system time counter set value  (time is updated when MSBs are written)
DCB_TIME_MSB_SET_REG                     =        DCB_REG_TIME_MSB_SET
DCB_TIME_MSB_SET_MASK                    =                      0xFFFFFFFF
DCB_TIME_MSB_SET_OFS                     =                               0



# ****** Register 62 [0x00F8]: EVENT_TX_RATE - Event Transmission Rate (Default: 0x00000000) ******

# EVENT_TX_RATE - Number of events transmitted per second
DCB_EVENT_TX_RATE_REG                    =       DCB_REG_EVENT_TX_RATE
DCB_EVENT_TX_RATE_MASK                   =                      0xFFFFFFFF
DCB_EVENT_TX_RATE_OFS                    =                               0



# ****** Register 63 [0x00FC]: EVENT_NR - Number of latest event (Default: 0x00000000) ******

# EVENT_NUMBER - Number of latest event
DCB_EVENT_NUMBER_REG                     =            DCB_REG_EVENT_NR
DCB_EVENT_NUMBER_MASK                    =                      0xFFFFFFFF
DCB_EVENT_NUMBER_OFS                     =                               0



# ****** Register 64 [0x0100]: TRG_CFG - Trigger Configuration (Default: 0x00000000) ******

# EXT_TRIGGER_OUT_ENABLE - Enable output of trigger signal to MCX connector
DCB_EXT_TRIGGER_OUT_ENABLE_REG           =             DCB_REG_TRG_CFG
DCB_EXT_TRIGGER_OUT_ENABLE_MASK          =                      0x00000001
DCB_EXT_TRIGGER_OUT_ENABLE_OFS           =                               0



# ****** Register 65 [0x0104]: SET_TRG_CFG - SET bit register for Trigger configuration register (Default: 0x00000000) ******

# SET_BIT_TRG_CFG - See TRG_CFG register
DCB_SET_BIT_TRG_CFG_REG                  =         DCB_REG_SET_TRG_CFG
DCB_SET_BIT_TRG_CFG_MASK                 =                      0xFFFFFFFF
DCB_SET_BIT_TRG_CFG_OFS                  =                               0



# ****** Register 66 [0x0108]: CLR_TRG_CFG - CLR bit register for Trigger configuration register (Default: 0x00000000) ******

# CLR_BIT_TRG_CFG - See TRG_CFG register
DCB_CLR_BIT_TRG_CFG_REG                  =         DCB_REG_CLR_TRG_CFG
DCB_CLR_BIT_TRG_CFG_MASK                 =                      0xFFFFFFFF
DCB_CLR_BIT_TRG_CFG_OFS                  =                               0



# ****** Register 67 [0x010C]: TRG_AUTO_PERIOD - Automatic Trigger Period (Default: 0x04C4B400) ******

# AUTO_TRIGGER_PERIOD - Period of automatic trigger in ticks of the DAQ clock
DCB_AUTO_TRIGGER_PERIOD_REG              =     DCB_REG_TRG_AUTO_PERIOD
DCB_AUTO_TRIGGER_PERIOD_MASK             =                      0xFFFFFFFF
DCB_AUTO_TRIGGER_PERIOD_OFS              =                               0



# ****** Register 68 [0x0110]: TRB_INFO_STAT - Trigger Information via Serial Trigger Bus Status (Default: 0x00000000) ******

# TRB_FLAG_NEW - Flag signalling that the current trigger information belongs to the latest trigger received
DCB_TRB_FLAG_NEW_REG                     =       DCB_REG_TRB_INFO_STAT
DCB_TRB_FLAG_NEW_MASK                    =                      0x80000000
DCB_TRB_FLAG_NEW_OFS                     =                              31

# TRB_FLAG_PARITY_ERROR - Parity error flag of the current trigger information
DCB_TRB_FLAG_PARITY_ERROR_REG            =       DCB_REG_TRB_INFO_STAT
DCB_TRB_FLAG_PARITY_ERROR_MASK           =                      0x40000000
DCB_TRB_FLAG_PARITY_ERROR_OFS            =                              30

# TRB_PARITY_ERROR_COUNT - Parity error count of the serial transmission
DCB_TRB_PARITY_ERROR_COUNT_REG           =       DCB_REG_TRB_INFO_STAT
DCB_TRB_PARITY_ERROR_COUNT_MASK          =                      0x0000FFFF
DCB_TRB_PARITY_ERROR_COUNT_OFS           =                               0



# ****** Register 69 [0x0114]: TRB_INFO_LSB - Trigger Information via Serial Trigger Bus LSBs (Default: 0x00000000) ******

# TRB_INFO_LSB - Trigger information LSBs
DCB_TRB_INFO_LSB_REG                     =        DCB_REG_TRB_INFO_LSB
DCB_TRB_INFO_LSB_MASK                    =                      0xFFFFFFFF
DCB_TRB_INFO_LSB_OFS                     =                               0



# ****** Register 70 [0x0118]: TRB_INFO_MSB - Trigger Information via Serial Trigger Bus MSBs (Default: 0x00000000) ******

# TRB_INFO_MSB - Trigger information MSBs
DCB_TRB_INFO_MSB_REG                     =        DCB_REG_TRB_INFO_MSB
DCB_TRB_INFO_MSB_MASK                    =                      0x0000FFFF
DCB_TRB_INFO_MSB_OFS                     =                               0



# ****** Register 71 [0x011C]: LMK_MOD_FLAG - Set if LMK configuraiton registers are modified (Default: 0x00000000) ******

# LMK_7_MOD - LMK channel 7 register modified flags
DCB_LMK_7_MOD_REG                        =        DCB_REG_LMK_MOD_FLAG
DCB_LMK_7_MOD_MASK                       =                      0x00000080
DCB_LMK_7_MOD_OFS                        =                               7

# LMK_6_MOD - LMK channel 6 register modified flags
DCB_LMK_6_MOD_REG                        =        DCB_REG_LMK_MOD_FLAG
DCB_LMK_6_MOD_MASK                       =                      0x00000040
DCB_LMK_6_MOD_OFS                        =                               6

# LMK_5_MOD - LMK channel 5 register modified flags
DCB_LMK_5_MOD_REG                        =        DCB_REG_LMK_MOD_FLAG
DCB_LMK_5_MOD_MASK                       =                      0x00000020
DCB_LMK_5_MOD_OFS                        =                               5

# LMK_4_MOD - LMK channel 4 register modified flags
DCB_LMK_4_MOD_REG                        =        DCB_REG_LMK_MOD_FLAG
DCB_LMK_4_MOD_MASK                       =                      0x00000010
DCB_LMK_4_MOD_OFS                        =                               4

# LMK_3_MOD - LMK channel 3 register modified flags
DCB_LMK_3_MOD_REG                        =        DCB_REG_LMK_MOD_FLAG
DCB_LMK_3_MOD_MASK                       =                      0x00000008
DCB_LMK_3_MOD_OFS                        =                               3

# LMK_2_MOD - LMK channel 2 register modified flags
DCB_LMK_2_MOD_REG                        =        DCB_REG_LMK_MOD_FLAG
DCB_LMK_2_MOD_MASK                       =                      0x00000004
DCB_LMK_2_MOD_OFS                        =                               2

# LMK_1_MOD - LMK channel 1 register modified flags
DCB_LMK_1_MOD_REG                        =        DCB_REG_LMK_MOD_FLAG
DCB_LMK_1_MOD_MASK                       =                      0x00000002
DCB_LMK_1_MOD_OFS                        =                               1

# LMK_0_MOD - LMK Register 0 modified flags
DCB_LMK_0_MOD_REG                        =        DCB_REG_LMK_MOD_FLAG
DCB_LMK_0_MOD_MASK                       =                      0x00000001
DCB_LMK_0_MOD_OFS                        =                               0



# ****** Register 72 [0x0120]: CMB_MSCB_ADR - MSCB Address of the CMB in the crate (Default: 0x00000000) ******

# CMB_MSCB_ADR - MSCB Address of the CMB in the crate
DCB_CMB_MSCB_ADR_REG                     =        DCB_REG_CMB_MSCB_ADR
DCB_CMB_MSCB_ADR_MASK                    =                      0xFFFFFFFF
DCB_CMB_MSCB_ADR_OFS                     =                               0



# ****** Register 73 [0x0124]: SD_PKT_CNT_0 - SERDES receiver packet count for slot 0 (Default: 0x00000000) ******

# SD_PKT_CNT_0 - SERDES receiver packet count for slot 0
DCB_SD_PKT_CNT_0_REG                     =        DCB_REG_SD_PKT_CNT_0
DCB_SD_PKT_CNT_0_MASK                    =                      0xFFFFFFFF
DCB_SD_PKT_CNT_0_OFS                     =                               0



# ****** Register 74 [0x0128]: SD_PKT_CNT_1 - SERDES receiver packet count for slot 1 (Default: 0x00000000) ******

# SD_PKT_CNT_1 - SERDES receiver packet count for slot 1
DCB_SD_PKT_CNT_1_REG                     =        DCB_REG_SD_PKT_CNT_1
DCB_SD_PKT_CNT_1_MASK                    =                      0xFFFFFFFF
DCB_SD_PKT_CNT_1_OFS                     =                               0



# ****** Register 75 [0x012C]: SD_PKT_CNT_2 - SERDES receiver packet count for slot 2 (Default: 0x00000000) ******

# SD_PKT_CNT_2 - SERDES receiver packet count for slot 2
DCB_SD_PKT_CNT_2_REG                     =        DCB_REG_SD_PKT_CNT_2
DCB_SD_PKT_CNT_2_MASK                    =                      0xFFFFFFFF
DCB_SD_PKT_CNT_2_OFS                     =                               0



# ****** Register 76 [0x0130]: SD_PKT_CNT_3 - SERDES receiver packet count for slot 3 (Default: 0x00000000) ******

# SD_PKT_CNT_3 - SERDES receiver packet count for slot 3
DCB_SD_PKT_CNT_3_REG                     =        DCB_REG_SD_PKT_CNT_3
DCB_SD_PKT_CNT_3_MASK                    =                      0xFFFFFFFF
DCB_SD_PKT_CNT_3_OFS                     =                               0



# ****** Register 77 [0x0134]: SD_PKT_CNT_4 - SERDES receiver packet count for slot 4 (Default: 0x00000000) ******

# SD_PKT_CNT_4 - SERDES receiver packet count for slot 4
DCB_SD_PKT_CNT_4_REG                     =        DCB_REG_SD_PKT_CNT_4
DCB_SD_PKT_CNT_4_MASK                    =                      0xFFFFFFFF
DCB_SD_PKT_CNT_4_OFS                     =                               0



# ****** Register 78 [0x0138]: SD_PKT_CNT_5 - SERDES receiver packet count for slot 5 (Default: 0x00000000) ******

# SD_PKT_CNT_5 - SERDES receiver packet count for slot 5
DCB_SD_PKT_CNT_5_REG                     =        DCB_REG_SD_PKT_CNT_5
DCB_SD_PKT_CNT_5_MASK                    =                      0xFFFFFFFF
DCB_SD_PKT_CNT_5_OFS                     =                               0



# ****** Register 79 [0x013C]: SD_PKT_CNT_6 - SERDES receiver packet count for slot 6 (Default: 0x00000000) ******

# SD_PKT_CNT_6 - SERDES receiver packet count for slot 6
DCB_SD_PKT_CNT_6_REG                     =        DCB_REG_SD_PKT_CNT_6
DCB_SD_PKT_CNT_6_MASK                    =                      0xFFFFFFFF
DCB_SD_PKT_CNT_6_OFS                     =                               0



# ****** Register 80 [0x0140]: SD_PKT_CNT_7 - SERDES receiver packet count for slot 7 (Default: 0x00000000) ******

# SD_PKT_CNT_7 - SERDES receiver packet count for slot 7
DCB_SD_PKT_CNT_7_REG                     =        DCB_REG_SD_PKT_CNT_7
DCB_SD_PKT_CNT_7_MASK                    =                      0xFFFFFFFF
DCB_SD_PKT_CNT_7_OFS                     =                               0



# ****** Register 81 [0x0144]: SD_PKT_CNT_8 - SERDES receiver packet count for slot 8 (Default: 0x00000000) ******

# SD_PKT_CNT_8 - SERDES receiver packet count for slot 8
DCB_SD_PKT_CNT_8_REG                     =        DCB_REG_SD_PKT_CNT_8
DCB_SD_PKT_CNT_8_MASK                    =                      0xFFFFFFFF
DCB_SD_PKT_CNT_8_OFS                     =                               0



# ****** Register 82 [0x0148]: SD_PKT_CNT_9 - SERDES receiver packet count for slot 9 (Default: 0x00000000) ******

# SD_PKT_CNT_9 - SERDES receiver packet count for slot 9
DCB_SD_PKT_CNT_9_REG                     =        DCB_REG_SD_PKT_CNT_9
DCB_SD_PKT_CNT_9_MASK                    =                      0xFFFFFFFF
DCB_SD_PKT_CNT_9_OFS                     =                               0



# ****** Register 83 [0x014C]: SD_PKT_CNT_10 - SERDES receiver packet count for slot 10 (Default: 0x00000000) ******

# SD_PKT_CNT_10 - SERDES receiver packet count for slot 10
DCB_SD_PKT_CNT_10_REG                    =       DCB_REG_SD_PKT_CNT_10
DCB_SD_PKT_CNT_10_MASK                   =                      0xFFFFFFFF
DCB_SD_PKT_CNT_10_OFS                    =                               0



# ****** Register 84 [0x0150]: SD_PKT_CNT_11 - SERDES receiver packet count for slot 11 (Default: 0x00000000) ******

# SD_PKT_CNT_11 - SERDES receiver packet count for slot 11
DCB_SD_PKT_CNT_11_REG                    =       DCB_REG_SD_PKT_CNT_11
DCB_SD_PKT_CNT_11_MASK                   =                      0xFFFFFFFF
DCB_SD_PKT_CNT_11_OFS                    =                               0



# ****** Register 85 [0x0154]: SD_PKT_CNT_12 - SERDES receiver packet count for slot 12 (Default: 0x00000000) ******

# SD_PKT_CNT_12 - SERDES receiver packet count for slot 12
DCB_SD_PKT_CNT_12_REG                    =       DCB_REG_SD_PKT_CNT_12
DCB_SD_PKT_CNT_12_MASK                   =                      0xFFFFFFFF
DCB_SD_PKT_CNT_12_OFS                    =                               0



# ****** Register 86 [0x0158]: SD_PKT_CNT_13 - SERDES receiver packet count for slot 13 (Default: 0x00000000) ******

# SD_PKT_CNT_13 - SERDES receiver packet count for slot 13
DCB_SD_PKT_CNT_13_REG                    =       DCB_REG_SD_PKT_CNT_13
DCB_SD_PKT_CNT_13_MASK                   =                      0xFFFFFFFF
DCB_SD_PKT_CNT_13_OFS                    =                               0



# ****** Register 87 [0x015C]: SD_PKT_CNT_14 - SERDES receiver packet count for slot 14 (Default: 0x00000000) ******

# SD_PKT_CNT_14 - SERDES receiver packet count for slot 14
DCB_SD_PKT_CNT_14_REG                    =       DCB_REG_SD_PKT_CNT_14
DCB_SD_PKT_CNT_14_MASK                   =                      0xFFFFFFFF
DCB_SD_PKT_CNT_14_OFS                    =                               0



# ****** Register 88 [0x0160]: SD_PKT_CNT_15 - SERDES receiver packet count for slot 15 (Default: 0x00000000) ******

# SD_PKT_CNT_15 - SERDES receiver packet count for slot 15
DCB_SD_PKT_CNT_15_REG                    =       DCB_REG_SD_PKT_CNT_15
DCB_SD_PKT_CNT_15_MASK                   =                      0xFFFFFFFF
DCB_SD_PKT_CNT_15_OFS                    =                               0



# ****** Register 89 [0x0164]: SD_PKT_CNT_17 - SERDES receiver packet count for slot 17 (TCB Slot) (Default: 0x00000000) ******

# SD_PKT_CNT_17 - SERDES receiver packet count for slot 17 (TCB Slot)
DCB_SD_PKT_CNT_17_REG                    =       DCB_REG_SD_PKT_CNT_17
DCB_SD_PKT_CNT_17_MASK                   =                      0xFFFFFFFF
DCB_SD_PKT_CNT_17_OFS                    =                               0



# ****** Register 90 [0x0168]: SD_EYE_STATUS_0 - SERDES receiver eye pattern status for slot 0 (Default: 0x00000000) ******

# SD_TAP_0 - SERDES receiver selected tap for slot 0
DCB_SD_TAP_0_REG                         =     DCB_REG_SD_EYE_STATUS_0
DCB_SD_TAP_0_MASK                        =                      0x1F000000
DCB_SD_TAP_0_OFS                         =                              24

# SD_EYE_0 - SERDES receiver eye pattern for slot 0
DCB_SD_EYE_0_REG                         =     DCB_REG_SD_EYE_STATUS_0
DCB_SD_EYE_0_MASK                        =                      0x000FFFFF
DCB_SD_EYE_0_OFS                         =                               0



# ****** Register 91 [0x016C]: SD_EYE_STATUS_1 - SERDES receiver eye pattern status for slot 1 (Default: 0x00000000) ******

# SD_TAP_1 - SERDES receiver selected tap for slot 1
DCB_SD_TAP_1_REG                         =     DCB_REG_SD_EYE_STATUS_1
DCB_SD_TAP_1_MASK                        =                      0x1F000000
DCB_SD_TAP_1_OFS                         =                              24

# SD_EYE_1 - SERDES receiver eye pattern for slot 1
DCB_SD_EYE_1_REG                         =     DCB_REG_SD_EYE_STATUS_1
DCB_SD_EYE_1_MASK                        =                      0x000FFFFF
DCB_SD_EYE_1_OFS                         =                               0



# ****** Register 92 [0x0170]: SD_EYE_STATUS_2 - SERDES receiver eye pattern status for slot 2 (Default: 0x00000000) ******

# SD_TAP_2 - SERDES receiver selected tap for slot 2
DCB_SD_TAP_2_REG                         =     DCB_REG_SD_EYE_STATUS_2
DCB_SD_TAP_2_MASK                        =                      0x1F000000
DCB_SD_TAP_2_OFS                         =                              24

# SD_EYE_2 - SERDES receiver eye pattern for slot 2
DCB_SD_EYE_2_REG                         =     DCB_REG_SD_EYE_STATUS_2
DCB_SD_EYE_2_MASK                        =                      0x000FFFFF
DCB_SD_EYE_2_OFS                         =                               0



# ****** Register 93 [0x0174]: SD_EYE_STATUS_3 - SERDES receiver eye pattern status for slot 3 (Default: 0x00000000) ******

# SD_TAP_3 - SERDES receiver selected tap for slot 3
DCB_SD_TAP_3_REG                         =     DCB_REG_SD_EYE_STATUS_3
DCB_SD_TAP_3_MASK                        =                      0x1F000000
DCB_SD_TAP_3_OFS                         =                              24

# SD_EYE_3 - SERDES receiver eye pattern for slot 3
DCB_SD_EYE_3_REG                         =     DCB_REG_SD_EYE_STATUS_3
DCB_SD_EYE_3_MASK                        =                      0x000FFFFF
DCB_SD_EYE_3_OFS                         =                               0



# ****** Register 94 [0x0178]: SD_EYE_STATUS_4 - SERDES receiver eye pattern status for slot 4 (Default: 0x00000000) ******

# SD_TAP_4 - SERDES receiver selected tap for slot 4
DCB_SD_TAP_4_REG                         =     DCB_REG_SD_EYE_STATUS_4
DCB_SD_TAP_4_MASK                        =                      0x1F000000
DCB_SD_TAP_4_OFS                         =                              24

# SD_EYE_4 - SERDES receiver eye pattern for slot 4
DCB_SD_EYE_4_REG                         =     DCB_REG_SD_EYE_STATUS_4
DCB_SD_EYE_4_MASK                        =                      0x000FFFFF
DCB_SD_EYE_4_OFS                         =                               0



# ****** Register 95 [0x017C]: SD_EYE_STATUS_5 - SERDES receiver eye pattern status for slot 5 (Default: 0x00000000) ******

# SD_TAP_5 - SERDES receiver selected tap for slot 5
DCB_SD_TAP_5_REG                         =     DCB_REG_SD_EYE_STATUS_5
DCB_SD_TAP_5_MASK                        =                      0x1F000000
DCB_SD_TAP_5_OFS                         =                              24

# SD_EYE_5 - SERDES receiver eye pattern for slot 5
DCB_SD_EYE_5_REG                         =     DCB_REG_SD_EYE_STATUS_5
DCB_SD_EYE_5_MASK                        =                      0x000FFFFF
DCB_SD_EYE_5_OFS                         =                               0



# ****** Register 96 [0x0180]: SD_EYE_STATUS_6 - SERDES receiver eye pattern status for slot 6 (Default: 0x00000000) ******

# SD_TAP_6 - SERDES receiver selected tap for slot 6
DCB_SD_TAP_6_REG                         =     DCB_REG_SD_EYE_STATUS_6
DCB_SD_TAP_6_MASK                        =                      0x1F000000
DCB_SD_TAP_6_OFS                         =                              24

# SD_EYE_6 - SERDES receiver eye pattern for slot 6
DCB_SD_EYE_6_REG                         =     DCB_REG_SD_EYE_STATUS_6
DCB_SD_EYE_6_MASK                        =                      0x000FFFFF
DCB_SD_EYE_6_OFS                         =                               0



# ****** Register 97 [0x0184]: SD_EYE_STATUS_7 - SERDES receiver eye pattern status for slot 7 (Default: 0x00000000) ******

# SD_TAP_7 - SERDES receiver selected tap for slot 7
DCB_SD_TAP_7_REG                         =     DCB_REG_SD_EYE_STATUS_7
DCB_SD_TAP_7_MASK                        =                      0x1F000000
DCB_SD_TAP_7_OFS                         =                              24

# SD_EYE_7 - SERDES receiver eye pattern for slot 7
DCB_SD_EYE_7_REG                         =     DCB_REG_SD_EYE_STATUS_7
DCB_SD_EYE_7_MASK                        =                      0x000FFFFF
DCB_SD_EYE_7_OFS                         =                               0



# ****** Register 98 [0x0188]: SD_EYE_STATUS_8 - SERDES receiver eye pattern status for slot 8 (Default: 0x00000000) ******

# SD_TAP_8 - SERDES receiver selected tap for slot 8
DCB_SD_TAP_8_REG                         =     DCB_REG_SD_EYE_STATUS_8
DCB_SD_TAP_8_MASK                        =                      0x1F000000
DCB_SD_TAP_8_OFS                         =                              24

# SD_EYE_8 - SERDES receiver eye pattern for slot 8
DCB_SD_EYE_8_REG                         =     DCB_REG_SD_EYE_STATUS_8
DCB_SD_EYE_8_MASK                        =                      0x000FFFFF
DCB_SD_EYE_8_OFS                         =                               0



# ****** Register 99 [0x018C]: SD_EYE_STATUS_9 - SERDES receiver eye pattern status for slot 9 (Default: 0x00000000) ******

# SD_TAP_9 - SERDES receiver selected tap for slot 9
DCB_SD_TAP_9_REG                         =     DCB_REG_SD_EYE_STATUS_9
DCB_SD_TAP_9_MASK                        =                      0x1F000000
DCB_SD_TAP_9_OFS                         =                              24

# SD_EYE_9 - SERDES receiver eye pattern for slot 9
DCB_SD_EYE_9_REG                         =     DCB_REG_SD_EYE_STATUS_9
DCB_SD_EYE_9_MASK                        =                      0x000FFFFF
DCB_SD_EYE_9_OFS                         =                               0



# ****** Register 100 [0x0190]: SD_EYE_STATUS_10 - SERDES receiver eye pattern status for slot 10 (Default: 0x00000000) ******

# SD_TAP_10 - SERDES receiver selected tap for slot 10
DCB_SD_TAP_10_REG                        =    DCB_REG_SD_EYE_STATUS_10
DCB_SD_TAP_10_MASK                       =                      0x1F000000
DCB_SD_TAP_10_OFS                        =                              24

# SD_EYE_10 - SERDES receiver eye pattern for slot 10
DCB_SD_EYE_10_REG                        =    DCB_REG_SD_EYE_STATUS_10
DCB_SD_EYE_10_MASK                       =                      0x000FFFFF
DCB_SD_EYE_10_OFS                        =                               0



# ****** Register 101 [0x0194]: SD_EYE_STATUS_11 - SERDES receiver eye pattern status for slot 11 (Default: 0x00000000) ******

# SD_TAP_11 - SERDES receiver selected tap for slot 11
DCB_SD_TAP_11_REG                        =    DCB_REG_SD_EYE_STATUS_11
DCB_SD_TAP_11_MASK                       =                      0x1F000000
DCB_SD_TAP_11_OFS                        =                              24

# SD_EYE_11 - SERDES receiver eye pattern for slot 11
DCB_SD_EYE_11_REG                        =    DCB_REG_SD_EYE_STATUS_11
DCB_SD_EYE_11_MASK                       =                      0x000FFFFF
DCB_SD_EYE_11_OFS                        =                               0



# ****** Register 102 [0x0198]: SD_EYE_STATUS_12 - SERDES receiver eye pattern status for slot 12 (Default: 0x00000000) ******

# SD_TAP_12 - SERDES receiver selected tap for slot 12
DCB_SD_TAP_12_REG                        =    DCB_REG_SD_EYE_STATUS_12
DCB_SD_TAP_12_MASK                       =                      0x1F000000
DCB_SD_TAP_12_OFS                        =                              24

# SD_EYE_12 - SERDES receiver eye pattern for slot 12
DCB_SD_EYE_12_REG                        =    DCB_REG_SD_EYE_STATUS_12
DCB_SD_EYE_12_MASK                       =                      0x000FFFFF
DCB_SD_EYE_12_OFS                        =                               0



# ****** Register 103 [0x019C]: SD_EYE_STATUS_13 - SERDES receiver eye pattern status for slot 13 (Default: 0x00000000) ******

# SD_TAP_13 - SERDES receiver selected tap for slot 13
DCB_SD_TAP_13_REG                        =    DCB_REG_SD_EYE_STATUS_13
DCB_SD_TAP_13_MASK                       =                      0x1F000000
DCB_SD_TAP_13_OFS                        =                              24

# SD_EYE_13 - SERDES receiver eye pattern for slot 13
DCB_SD_EYE_13_REG                        =    DCB_REG_SD_EYE_STATUS_13
DCB_SD_EYE_13_MASK                       =                      0x000FFFFF
DCB_SD_EYE_13_OFS                        =                               0



# ****** Register 104 [0x01A0]: SD_EYE_STATUS_14 - SERDES receiver eye pattern status for slot 14 (Default: 0x00000000) ******

# SD_TAP_14 - SERDES receiver selected tap for slot 14
DCB_SD_TAP_14_REG                        =    DCB_REG_SD_EYE_STATUS_14
DCB_SD_TAP_14_MASK                       =                      0x1F000000
DCB_SD_TAP_14_OFS                        =                              24

# SD_EYE_14 - SERDES receiver eye pattern for slot 14
DCB_SD_EYE_14_REG                        =    DCB_REG_SD_EYE_STATUS_14
DCB_SD_EYE_14_MASK                       =                      0x000FFFFF
DCB_SD_EYE_14_OFS                        =                               0



# ****** Register 105 [0x01A4]: SD_EYE_STATUS_15 - SERDES receiver eye pattern status for slot 15 (Default: 0x00000000) ******

# SD_TAP_15 - SERDES receiver selected tap for slot 15
DCB_SD_TAP_15_REG                        =    DCB_REG_SD_EYE_STATUS_15
DCB_SD_TAP_15_MASK                       =                      0x1F000000
DCB_SD_TAP_15_OFS                        =                              24

# SD_EYE_15 - SERDES receiver eye pattern for slot 15
DCB_SD_EYE_15_REG                        =    DCB_REG_SD_EYE_STATUS_15
DCB_SD_EYE_15_MASK                       =                      0x000FFFFF
DCB_SD_EYE_15_OFS                        =                               0



# ****** Register 106 [0x01A8]: SD_EYE_STATUS_17 - SERDES receiver eye pattern status for slot 17 (TCB slot) (Default: 0x00000000) ******

# SD_TAP_17 - SERDES receiver selected tap for slot 17 (TCB slot)
DCB_SD_TAP_17_REG                        =    DCB_REG_SD_EYE_STATUS_17
DCB_SD_TAP_17_MASK                       =                      0x1F000000
DCB_SD_TAP_17_OFS                        =                              24

# SD_EYE_17 - SERDES receiver eye pattern for slot 17 (TCB slot)
DCB_SD_EYE_17_REG                        =    DCB_REG_SD_EYE_STATUS_17
DCB_SD_EYE_17_MASK                       =                      0x000FFFFF
DCB_SD_EYE_17_OFS                        =                               0



# ****** Register 107 [0x01AC]: CRC32_REG_BANK - CRC32 Checksum of Register Bank Content (Default: 0x00000000) ******

# CRC32_REG_BANK - Keep at the end of the register bank
DCB_CRC32_REG_BANK_REG                   =      DCB_REG_CRC32_REG_BANK
DCB_CRC32_REG_BANK_MASK                  =                      0xFFFFFFFF
DCB_CRC32_REG_BANK_OFS                   =                               0



# Number of Registers

REG_NR_OF_REGS          = 108



# List of register names, offsets and writable info

DCB_WRITABLE_REG = False
DCB_READONLY_REG = True

dcb_reg_list = (
  ( "HW_VER"              , DCB_REG_HW_VER             , DCB_READONLY_REG ),
  ( "REG_LAYOUT_VER"      , DCB_REG_REG_LAYOUT_VER     , DCB_READONLY_REG ),
  ( "FW_BUILD_DATE"       , DCB_REG_FW_BUILD_DATE      , DCB_READONLY_REG ),
  ( "FW_BUILD_TIME"       , DCB_REG_FW_BUILD_TIME      , DCB_READONLY_REG ),
  ( "SW_BUILD_DATE"       , DCB_REG_SW_BUILD_DATE      , DCB_WRITABLE_REG ),
  ( "SW_BUILD_TIME"       , DCB_REG_SW_BUILD_TIME      , DCB_WRITABLE_REG ),
  ( "FW_GIT_HASH_TAG"     , DCB_REG_FW_GIT_HASH_TAG    , DCB_READONLY_REG ),
  ( "SW_GIT_HASH_TAG"     , DCB_REG_SW_GIT_HASH_TAG    , DCB_WRITABLE_REG ),
  ( "PROT_VER"            , DCB_REG_PROT_VER           , DCB_WRITABLE_REG ),
  ( "SN"                  , DCB_REG_SN                 , DCB_WRITABLE_REG ),
  ( "STATUS"              , DCB_REG_STATUS             , DCB_READONLY_REG ),
  ( "TEMP"                , DCB_REG_TEMP               , DCB_WRITABLE_REG ),
  ( "PLL_LOCK"            , DCB_REG_PLL_LOCK           , DCB_READONLY_REG ),
  ( "DCB_LOC"             , DCB_REG_DCB_LOC            , DCB_WRITABLE_REG ),
  ( "CTRL"                , DCB_REG_CTRL               , DCB_WRITABLE_REG ),
  ( "SET_CTRL"            , DCB_REG_SET_CTRL           , DCB_WRITABLE_REG ),
  ( "CLR_CTRL"            , DCB_REG_CLR_CTRL           , DCB_WRITABLE_REG ),
  ( "CLK_CTRL"            , DCB_REG_CLK_CTRL           , DCB_WRITABLE_REG ),
  ( "SET_CLK_CTRL"        , DCB_REG_SET_CLK_CTRL       , DCB_WRITABLE_REG ),
  ( "CLR_CLK_CTRL"        , DCB_REG_CLR_CLK_CTRL       , DCB_WRITABLE_REG ),
  ( "COM_CTRL"            , DCB_REG_COM_CTRL           , DCB_WRITABLE_REG ),
  ( "DPS_CTRL"            , DCB_REG_DPS_CTRL           , DCB_WRITABLE_REG ),
  ( "RST"                 , DCB_REG_RST                , DCB_WRITABLE_REG ),
  ( "SERDES_STATUS_00_07" , DCB_REG_SERDES_STATUS_00_07, DCB_READONLY_REG ),
  ( "SERDES_STATUS_08_15" , DCB_REG_SERDES_STATUS_08_15, DCB_READONLY_REG ),
  ( "SERDES_STATUS_17"    , DCB_REG_SERDES_STATUS_17   , DCB_READONLY_REG ),
  ( "SERDES_ERR_CNT_00"   , DCB_REG_SERDES_ERR_CNT_00  , DCB_READONLY_REG ),
  ( "SERDES_ERR_CNT_01"   , DCB_REG_SERDES_ERR_CNT_01  , DCB_READONLY_REG ),
  ( "SERDES_ERR_CNT_02"   , DCB_REG_SERDES_ERR_CNT_02  , DCB_READONLY_REG ),
  ( "SERDES_ERR_CNT_03"   , DCB_REG_SERDES_ERR_CNT_03  , DCB_READONLY_REG ),
  ( "SERDES_ERR_CNT_04"   , DCB_REG_SERDES_ERR_CNT_04  , DCB_READONLY_REG ),
  ( "SERDES_ERR_CNT_05"   , DCB_REG_SERDES_ERR_CNT_05  , DCB_READONLY_REG ),
  ( "SERDES_ERR_CNT_06"   , DCB_REG_SERDES_ERR_CNT_06  , DCB_READONLY_REG ),
  ( "SERDES_ERR_CNT_07"   , DCB_REG_SERDES_ERR_CNT_07  , DCB_READONLY_REG ),
  ( "SERDES_ERR_CNT_08"   , DCB_REG_SERDES_ERR_CNT_08  , DCB_READONLY_REG ),
  ( "SERDES_ERR_CNT_09"   , DCB_REG_SERDES_ERR_CNT_09  , DCB_READONLY_REG ),
  ( "SERDES_ERR_CNT_10"   , DCB_REG_SERDES_ERR_CNT_10  , DCB_READONLY_REG ),
  ( "SERDES_ERR_CNT_11"   , DCB_REG_SERDES_ERR_CNT_11  , DCB_READONLY_REG ),
  ( "SERDES_ERR_CNT_12"   , DCB_REG_SERDES_ERR_CNT_12  , DCB_READONLY_REG ),
  ( "SERDES_ERR_CNT_13"   , DCB_REG_SERDES_ERR_CNT_13  , DCB_READONLY_REG ),
  ( "SERDES_ERR_CNT_14"   , DCB_REG_SERDES_ERR_CNT_14  , DCB_READONLY_REG ),
  ( "SERDES_ERR_CNT_15"   , DCB_REG_SERDES_ERR_CNT_15  , DCB_READONLY_REG ),
  ( "SERDES_ERR_CNT_17"   , DCB_REG_SERDES_ERR_CNT_17  , DCB_READONLY_REG ),
  ( "APLY_CFG"            , DCB_REG_APLY_CFG           , DCB_WRITABLE_REG ),
  ( "LMK_0"               , DCB_REG_LMK_0              , DCB_WRITABLE_REG ),
  ( "LMK_1"               , DCB_REG_LMK_1              , DCB_WRITABLE_REG ),
  ( "LMK_2"               , DCB_REG_LMK_2              , DCB_WRITABLE_REG ),
  ( "LMK_3"               , DCB_REG_LMK_3              , DCB_WRITABLE_REG ),
  ( "LMK_4"               , DCB_REG_LMK_4              , DCB_WRITABLE_REG ),
  ( "LMK_5"               , DCB_REG_LMK_5              , DCB_WRITABLE_REG ),
  ( "LMK_6"               , DCB_REG_LMK_6              , DCB_WRITABLE_REG ),
  ( "LMK_7"               , DCB_REG_LMK_7              , DCB_WRITABLE_REG ),
  ( "LMK_8"               , DCB_REG_LMK_8              , DCB_WRITABLE_REG ),
  ( "LMK_9"               , DCB_REG_LMK_9              , DCB_WRITABLE_REG ),
  ( "LMK_11"              , DCB_REG_LMK_11             , DCB_WRITABLE_REG ),
  ( "LMK_13"              , DCB_REG_LMK_13             , DCB_WRITABLE_REG ),
  ( "LMK_14"              , DCB_REG_LMK_14             , DCB_WRITABLE_REG ),
  ( "LMK_15"              , DCB_REG_LMK_15             , DCB_WRITABLE_REG ),
  ( "TIME_LSB"            , DCB_REG_TIME_LSB           , DCB_READONLY_REG ),
  ( "TIME_MSB"            , DCB_REG_TIME_MSB           , DCB_READONLY_REG ),
  ( "TIME_LSB_SET"        , DCB_REG_TIME_LSB_SET       , DCB_WRITABLE_REG ),
  ( "TIME_MSB_SET"        , DCB_REG_TIME_MSB_SET       , DCB_WRITABLE_REG ),
  ( "EVENT_TX_RATE"       , DCB_REG_EVENT_TX_RATE      , DCB_READONLY_REG ),
  ( "EVENT_NR"            , DCB_REG_EVENT_NR           , DCB_READONLY_REG ),
  ( "TRG_CFG"             , DCB_REG_TRG_CFG            , DCB_WRITABLE_REG ),
  ( "SET_TRG_CFG"         , DCB_REG_SET_TRG_CFG        , DCB_WRITABLE_REG ),
  ( "CLR_TRG_CFG"         , DCB_REG_CLR_TRG_CFG        , DCB_WRITABLE_REG ),
  ( "TRG_AUTO_PERIOD"     , DCB_REG_TRG_AUTO_PERIOD    , DCB_WRITABLE_REG ),
  ( "TRB_INFO_STAT"       , DCB_REG_TRB_INFO_STAT      , DCB_READONLY_REG ),
  ( "TRB_INFO_LSB"        , DCB_REG_TRB_INFO_LSB       , DCB_READONLY_REG ),
  ( "TRB_INFO_MSB"        , DCB_REG_TRB_INFO_MSB       , DCB_READONLY_REG ),
  ( "LMK_MOD_FLAG"        , DCB_REG_LMK_MOD_FLAG       , DCB_READONLY_REG ),
  ( "CMB_MSCB_ADR"        , DCB_REG_CMB_MSCB_ADR       , DCB_WRITABLE_REG ),
  ( "SD_PKT_CNT_0"        , DCB_REG_SD_PKT_CNT_0       , DCB_READONLY_REG ),
  ( "SD_PKT_CNT_1"        , DCB_REG_SD_PKT_CNT_1       , DCB_READONLY_REG ),
  ( "SD_PKT_CNT_2"        , DCB_REG_SD_PKT_CNT_2       , DCB_READONLY_REG ),
  ( "SD_PKT_CNT_3"        , DCB_REG_SD_PKT_CNT_3       , DCB_READONLY_REG ),
  ( "SD_PKT_CNT_4"        , DCB_REG_SD_PKT_CNT_4       , DCB_READONLY_REG ),
  ( "SD_PKT_CNT_5"        , DCB_REG_SD_PKT_CNT_5       , DCB_READONLY_REG ),
  ( "SD_PKT_CNT_6"        , DCB_REG_SD_PKT_CNT_6       , DCB_READONLY_REG ),
  ( "SD_PKT_CNT_7"        , DCB_REG_SD_PKT_CNT_7       , DCB_READONLY_REG ),
  ( "SD_PKT_CNT_8"        , DCB_REG_SD_PKT_CNT_8       , DCB_READONLY_REG ),
  ( "SD_PKT_CNT_9"        , DCB_REG_SD_PKT_CNT_9       , DCB_READONLY_REG ),
  ( "SD_PKT_CNT_10"       , DCB_REG_SD_PKT_CNT_10      , DCB_READONLY_REG ),
  ( "SD_PKT_CNT_11"       , DCB_REG_SD_PKT_CNT_11      , DCB_READONLY_REG ),
  ( "SD_PKT_CNT_12"       , DCB_REG_SD_PKT_CNT_12      , DCB_READONLY_REG ),
  ( "SD_PKT_CNT_13"       , DCB_REG_SD_PKT_CNT_13      , DCB_READONLY_REG ),
  ( "SD_PKT_CNT_14"       , DCB_REG_SD_PKT_CNT_14      , DCB_READONLY_REG ),
  ( "SD_PKT_CNT_15"       , DCB_REG_SD_PKT_CNT_15      , DCB_READONLY_REG ),
  ( "SD_PKT_CNT_17"       , DCB_REG_SD_PKT_CNT_17      , DCB_READONLY_REG ),
  ( "SD_EYE_STATUS_0"     , DCB_REG_SD_EYE_STATUS_0    , DCB_READONLY_REG ),
  ( "SD_EYE_STATUS_1"     , DCB_REG_SD_EYE_STATUS_1    , DCB_READONLY_REG ),
  ( "SD_EYE_STATUS_2"     , DCB_REG_SD_EYE_STATUS_2    , DCB_READONLY_REG ),
  ( "SD_EYE_STATUS_3"     , DCB_REG_SD_EYE_STATUS_3    , DCB_READONLY_REG ),
  ( "SD_EYE_STATUS_4"     , DCB_REG_SD_EYE_STATUS_4    , DCB_READONLY_REG ),
  ( "SD_EYE_STATUS_5"     , DCB_REG_SD_EYE_STATUS_5    , DCB_READONLY_REG ),
  ( "SD_EYE_STATUS_6"     , DCB_REG_SD_EYE_STATUS_6    , DCB_READONLY_REG ),
  ( "SD_EYE_STATUS_7"     , DCB_REG_SD_EYE_STATUS_7    , DCB_READONLY_REG ),
  ( "SD_EYE_STATUS_8"     , DCB_REG_SD_EYE_STATUS_8    , DCB_READONLY_REG ),
  ( "SD_EYE_STATUS_9"     , DCB_REG_SD_EYE_STATUS_9    , DCB_READONLY_REG ),
  ( "SD_EYE_STATUS_10"    , DCB_REG_SD_EYE_STATUS_10   , DCB_READONLY_REG ),
  ( "SD_EYE_STATUS_11"    , DCB_REG_SD_EYE_STATUS_11   , DCB_READONLY_REG ),
  ( "SD_EYE_STATUS_12"    , DCB_REG_SD_EYE_STATUS_12   , DCB_READONLY_REG ),
  ( "SD_EYE_STATUS_13"    , DCB_REG_SD_EYE_STATUS_13   , DCB_READONLY_REG ),
  ( "SD_EYE_STATUS_14"    , DCB_REG_SD_EYE_STATUS_14   , DCB_READONLY_REG ),
  ( "SD_EYE_STATUS_15"    , DCB_REG_SD_EYE_STATUS_15   , DCB_READONLY_REG ),
  ( "SD_EYE_STATUS_17"    , DCB_REG_SD_EYE_STATUS_17   , DCB_READONLY_REG ),
  ( "CRC32_REG_BANK"      , DCB_REG_CRC32_REG_BANK     , DCB_WRITABLE_REG ),
)



# List of bit names and parameters

dcb_bit_group_list = (
  ( "BOARD_MAGIC"                   , DCB_BOARD_MAGIC_REG                   , DCB_BOARD_MAGIC_MASK                   , DCB_BOARD_MAGIC_OFS                   ),
  ( "VENDOR_ID"                     , DCB_VENDOR_ID_REG                     , DCB_VENDOR_ID_MASK                     , DCB_VENDOR_ID_OFS                     ),
  ( "BOARD_TYPE"                    , DCB_BOARD_TYPE_REG                    , DCB_BOARD_TYPE_MASK                    , DCB_BOARD_TYPE_OFS                    ),
  ( "BOARD_REVISION"                , DCB_BOARD_REVISION_REG                , DCB_BOARD_REVISION_MASK                , DCB_BOARD_REVISION_OFS                ),
  ( "BOARD_VARIANT"                 , DCB_BOARD_VARIANT_REG                 , DCB_BOARD_VARIANT_MASK                 , DCB_BOARD_VARIANT_OFS                 ),
  ( "REG_LAYOUT_COMP_LEVEL"         , DCB_REG_LAYOUT_COMP_LEVEL_REG         , DCB_REG_LAYOUT_COMP_LEVEL_MASK         , DCB_REG_LAYOUT_COMP_LEVEL_OFS         ),
  ( "REG_LAYOUT_VERSION"            , DCB_REG_LAYOUT_VERSION_REG            , DCB_REG_LAYOUT_VERSION_MASK            , DCB_REG_LAYOUT_VERSION_OFS            ),
  ( "FW_BUILD_YEAR"                 , DCB_FW_BUILD_YEAR_REG                 , DCB_FW_BUILD_YEAR_MASK                 , DCB_FW_BUILD_YEAR_OFS                 ),
  ( "FW_BUILD_MONTH"                , DCB_FW_BUILD_MONTH_REG                , DCB_FW_BUILD_MONTH_MASK                , DCB_FW_BUILD_MONTH_OFS                ),
  ( "FW_BUILD_DAY"                  , DCB_FW_BUILD_DAY_REG                  , DCB_FW_BUILD_DAY_MASK                  , DCB_FW_BUILD_DAY_OFS                  ),
  ( "FW_COMPAT_LEVEL"               , DCB_FW_COMPAT_LEVEL_REG               , DCB_FW_COMPAT_LEVEL_MASK               , DCB_FW_COMPAT_LEVEL_OFS               ),
  ( "FW_BUILD_HOUR"                 , DCB_FW_BUILD_HOUR_REG                 , DCB_FW_BUILD_HOUR_MASK                 , DCB_FW_BUILD_HOUR_OFS                 ),
  ( "FW_BUILD_MINUTE"               , DCB_FW_BUILD_MINUTE_REG               , DCB_FW_BUILD_MINUTE_MASK               , DCB_FW_BUILD_MINUTE_OFS               ),
  ( "FW_BUILD_SECOND"               , DCB_FW_BUILD_SECOND_REG               , DCB_FW_BUILD_SECOND_MASK               , DCB_FW_BUILD_SECOND_OFS               ),
  ( "SW_BUILD_YEAR"                 , DCB_SW_BUILD_YEAR_REG                 , DCB_SW_BUILD_YEAR_MASK                 , DCB_SW_BUILD_YEAR_OFS                 ),
  ( "SW_BUILD_MONTH"                , DCB_SW_BUILD_MONTH_REG                , DCB_SW_BUILD_MONTH_MASK                , DCB_SW_BUILD_MONTH_OFS                ),
  ( "SW_BUILD_DAY"                  , DCB_SW_BUILD_DAY_REG                  , DCB_SW_BUILD_DAY_MASK                  , DCB_SW_BUILD_DAY_OFS                  ),
  ( "SW_BUILD_HOUR"                 , DCB_SW_BUILD_HOUR_REG                 , DCB_SW_BUILD_HOUR_MASK                 , DCB_SW_BUILD_HOUR_OFS                 ),
  ( "SW_BUILD_MINUTE"               , DCB_SW_BUILD_MINUTE_REG               , DCB_SW_BUILD_MINUTE_MASK               , DCB_SW_BUILD_MINUTE_OFS               ),
  ( "SW_BUILD_SECOND"               , DCB_SW_BUILD_SECOND_REG               , DCB_SW_BUILD_SECOND_MASK               , DCB_SW_BUILD_SECOND_OFS               ),
  ( "FW_GIT_HASH_TAG"               , DCB_FW_GIT_HASH_TAG_REG               , DCB_FW_GIT_HASH_TAG_MASK               , DCB_FW_GIT_HASH_TAG_OFS               ),
  ( "SW_GIT_HASH_TAG"               , DCB_SW_GIT_HASH_TAG_REG               , DCB_SW_GIT_HASH_TAG_MASK               , DCB_SW_GIT_HASH_TAG_OFS               ),
  ( "PROTOCOL_VERSION"              , DCB_PROTOCOL_VERSION_REG              , DCB_PROTOCOL_VERSION_MASK              , DCB_PROTOCOL_VERSION_OFS              ),
  ( "SERIAL_NUMBER"                 , DCB_SERIAL_NUMBER_REG                 , DCB_SERIAL_NUMBER_MASK                 , DCB_SERIAL_NUMBER_OFS                 ),
  ( "FLASH_SEL"                     , DCB_FLASH_SEL_REG                     , DCB_FLASH_SEL_MASK                     , DCB_FLASH_SEL_OFS                     ),
  ( "BOARD_SEL"                     , DCB_BOARD_SEL_REG                     , DCB_BOARD_SEL_MASK                     , DCB_BOARD_SEL_OFS                     ),
  ( "SERIAL_BUSY"                   , DCB_SERIAL_BUSY_REG                   , DCB_SERIAL_BUSY_MASK                   , DCB_SERIAL_BUSY_OFS                   ),
  ( "DCB_BUSY"                      , DCB_DCB_BUSY_REG                      , DCB_DCB_BUSY_MASK                      , DCB_DCB_BUSY_OFS                      ),
  ( "SYS_BUSY"                      , DCB_SYS_BUSY_REG                      , DCB_SYS_BUSY_MASK                      , DCB_SYS_BUSY_OFS                      ),
  ( "TEMPERATURE"                   , DCB_TEMPERATURE_REG                   , DCB_TEMPERATURE_MASK                   , DCB_TEMPERATURE_OFS                   ),
  ( "SERDES_CLK_MGR_LOCK"           , DCB_SERDES_CLK_MGR_LOCK_REG           , DCB_SERDES_CLK_MGR_LOCK_MASK           , DCB_SERDES_CLK_MGR_LOCK_OFS           ),
  ( "WDB_CLK_MGR_LOCK"              , DCB_WDB_CLK_MGR_LOCK_REG              , DCB_WDB_CLK_MGR_LOCK_MASK              , DCB_WDB_CLK_MGR_LOCK_OFS              ),
  ( "SYS_DCM_LOCK"                  , DCB_SYS_DCM_LOCK_REG                  , DCB_SYS_DCM_LOCK_MASK                  , DCB_SYS_DCM_LOCK_OFS                  ),
  ( "LMK_PLL_LOCK"                  , DCB_LMK_PLL_LOCK_REG                  , DCB_LMK_PLL_LOCK_MASK                  , DCB_LMK_PLL_LOCK_OFS                  ),
  ( "CRATE_ID"                      , DCB_CRATE_ID_REG                      , DCB_CRATE_ID_MASK                      , DCB_CRATE_ID_OFS                      ),
  ( "SLOT_ID"                       , DCB_SLOT_ID_REG                       , DCB_SLOT_ID_MASK                       , DCB_SLOT_ID_OFS                       ),
  ( "SYNC_DELAY"                    , DCB_SYNC_DELAY_REG                    , DCB_SYNC_DELAY_MASK                    , DCB_SYNC_DELAY_OFS                    ),
  ( "DAQ_SOFT_TRIGGER"              , DCB_DAQ_SOFT_TRIGGER_REG              , DCB_DAQ_SOFT_TRIGGER_MASK              , DCB_DAQ_SOFT_TRIGGER_OFS              ),
  ( "DAQ_AUTO"                      , DCB_DAQ_AUTO_REG                      , DCB_DAQ_AUTO_MASK                      , DCB_DAQ_AUTO_OFS                      ),
  ( "DAQ_NORMAL"                    , DCB_DAQ_NORMAL_REG                    , DCB_DAQ_NORMAL_MASK                    , DCB_DAQ_NORMAL_OFS                    ),
  ( "DAQ_SINGLE"                    , DCB_DAQ_SINGLE_REG                    , DCB_DAQ_SINGLE_MASK                    , DCB_DAQ_SINGLE_OFS                    ),
  ( "SET_BIT_CTRL"                  , DCB_SET_BIT_CTRL_REG                  , DCB_SET_BIT_CTRL_MASK                  , DCB_SET_BIT_CTRL_OFS                  ),
  ( "CLR_BIT_CTRL"                  , DCB_CLR_BIT_CTRL_REG                  , DCB_CLR_BIT_CTRL_MASK                  , DCB_CLR_BIT_CTRL_OFS                  ),
  ( "DISTRIBUTOR_CLK_OUT_EN"        , DCB_DISTRIBUTOR_CLK_OUT_EN_REG        , DCB_DISTRIBUTOR_CLK_OUT_EN_MASK        , DCB_DISTRIBUTOR_CLK_OUT_EN_OFS        ),
  ( "DISTRIBUTOR_CLK_SRC_SEL"       , DCB_DISTRIBUTOR_CLK_SRC_SEL_REG       , DCB_DISTRIBUTOR_CLK_SRC_SEL_MASK       , DCB_DISTRIBUTOR_CLK_SRC_SEL_OFS       ),
  ( "BUS_CLK_SRC_SEL"               , DCB_BUS_CLK_SRC_SEL_REG               , DCB_BUS_CLK_SRC_SEL_MASK               , DCB_BUS_CLK_SRC_SEL_OFS               ),
  ( "LMK_CLK_SRC_SEL"               , DCB_LMK_CLK_SRC_SEL_REG               , DCB_LMK_CLK_SRC_SEL_MASK               , DCB_LMK_CLK_SRC_SEL_OFS               ),
  ( "EXT_CLK_IN_SEL"                , DCB_EXT_CLK_IN_SEL_REG                , DCB_EXT_CLK_IN_SEL_MASK                , DCB_EXT_CLK_IN_SEL_OFS                ),
  ( "SET_BIT_CLK_CTRL"              , DCB_SET_BIT_CLK_CTRL_REG              , DCB_SET_BIT_CLK_CTRL_MASK              , DCB_SET_BIT_CLK_CTRL_OFS              ),
  ( "CLR_BIT_CLK_CTRL"              , DCB_CLR_BIT_CLK_CTRL_REG              , DCB_CLR_BIT_CLK_CTRL_MASK              , DCB_CLR_BIT_CLK_CTRL_OFS              ),
  ( "INTER_PKG_DELAY"               , DCB_INTER_PKG_DELAY_REG               , DCB_INTER_PKG_DELAY_MASK               , DCB_INTER_PKG_DELAY_OFS               ),
  ( "DPS_EVENT_MODE"                , DCB_DPS_EVENT_MODE_REG                , DCB_DPS_EVENT_MODE_MASK                , DCB_DPS_EVENT_MODE_OFS                ),
  ( "DPS_SLOT_ENABLE"               , DCB_DPS_SLOT_ENABLE_REG               , DCB_DPS_SLOT_ENABLE_MASK               , DCB_DPS_SLOT_ENABLE_OFS               ),
  ( "ISERDES_RCVR_PACKET_COUNT_RST" , DCB_ISERDES_RCVR_PACKET_COUNT_RST_REG , DCB_ISERDES_RCVR_PACKET_COUNT_RST_MASK , DCB_ISERDES_RCVR_PACKET_COUNT_RST_OFS ),
  ( "WDB_SERDES_CLK_MGR_RST"        , DCB_WDB_SERDES_CLK_MGR_RST_REG        , DCB_WDB_SERDES_CLK_MGR_RST_MASK        , DCB_WDB_SERDES_CLK_MGR_RST_OFS        ),
  ( "WDB_REFCLK_MGR_RST"            , DCB_WDB_REFCLK_MGR_RST_REG            , DCB_WDB_REFCLK_MGR_RST_MASK            , DCB_WDB_REFCLK_MGR_RST_OFS            ),
  ( "TRIGGER_MGR_RST"               , DCB_TRIGGER_MGR_RST_REG               , DCB_TRIGGER_MGR_RST_MASK               , DCB_TRIGGER_MGR_RST_OFS               ),
  ( "TR_SYNC_BPL"                   , DCB_TR_SYNC_BPL_REG                   , DCB_TR_SYNC_BPL_MASK                   , DCB_TR_SYNC_BPL_OFS                   ),
  ( "LMK_SYNC_DCB"                  , DCB_LMK_SYNC_DCB_REG                  , DCB_LMK_SYNC_DCB_MASK                  , DCB_LMK_SYNC_DCB_OFS                  ),
  ( "ISERDES_RCVR_ERROR_COUNT_RST"  , DCB_ISERDES_RCVR_ERROR_COUNT_RST_REG  , DCB_ISERDES_RCVR_ERROR_COUNT_RST_MASK  , DCB_ISERDES_RCVR_ERROR_COUNT_RST_OFS  ),
  ( "ISERDES_RECEIVER_RESYNC"       , DCB_ISERDES_RECEIVER_RESYNC_REG       , DCB_ISERDES_RECEIVER_RESYNC_MASK       , DCB_ISERDES_RECEIVER_RESYNC_OFS       ),
  ( "ISERDES_RECEIVER_RST"          , DCB_ISERDES_RECEIVER_RST_REG          , DCB_ISERDES_RECEIVER_RST_MASK          , DCB_ISERDES_RECEIVER_RST_OFS          ),
  ( "RECONFIGURE_FPGA"              , DCB_RECONFIGURE_FPGA_REG              , DCB_RECONFIGURE_FPGA_MASK              , DCB_RECONFIGURE_FPGA_OFS              ),
  ( "IDLE_PATTERN_DETECT_07"        , DCB_IDLE_PATTERN_DETECT_07_REG        , DCB_IDLE_PATTERN_DETECT_07_MASK        , DCB_IDLE_PATTERN_DETECT_07_OFS        ),
  ( "BITSLIP_OK_07"                 , DCB_BITSLIP_OK_07_REG                 , DCB_BITSLIP_OK_07_MASK                 , DCB_BITSLIP_OK_07_OFS                 ),
  ( "DELAY_OK_07"                   , DCB_DELAY_OK_07_REG                   , DCB_DELAY_OK_07_MASK                   , DCB_DELAY_OK_07_OFS                   ),
  ( "SYNC_DONE_07"                  , DCB_SYNC_DONE_07_REG                  , DCB_SYNC_DONE_07_MASK                  , DCB_SYNC_DONE_07_OFS                  ),
  ( "IDLE_PATTERN_DETECT_06"        , DCB_IDLE_PATTERN_DETECT_06_REG        , DCB_IDLE_PATTERN_DETECT_06_MASK        , DCB_IDLE_PATTERN_DETECT_06_OFS        ),
  ( "BITSLIP_OK_06"                 , DCB_BITSLIP_OK_06_REG                 , DCB_BITSLIP_OK_06_MASK                 , DCB_BITSLIP_OK_06_OFS                 ),
  ( "DELAY_OK_06"                   , DCB_DELAY_OK_06_REG                   , DCB_DELAY_OK_06_MASK                   , DCB_DELAY_OK_06_OFS                   ),
  ( "SYNC_DONE_06"                  , DCB_SYNC_DONE_06_REG                  , DCB_SYNC_DONE_06_MASK                  , DCB_SYNC_DONE_06_OFS                  ),
  ( "IDLE_PATTERN_DETECT_05"        , DCB_IDLE_PATTERN_DETECT_05_REG        , DCB_IDLE_PATTERN_DETECT_05_MASK        , DCB_IDLE_PATTERN_DETECT_05_OFS        ),
  ( "BITSLIP_OK_05"                 , DCB_BITSLIP_OK_05_REG                 , DCB_BITSLIP_OK_05_MASK                 , DCB_BITSLIP_OK_05_OFS                 ),
  ( "DELAY_OK_05"                   , DCB_DELAY_OK_05_REG                   , DCB_DELAY_OK_05_MASK                   , DCB_DELAY_OK_05_OFS                   ),
  ( "SYNC_DONE_05"                  , DCB_SYNC_DONE_05_REG                  , DCB_SYNC_DONE_05_MASK                  , DCB_SYNC_DONE_05_OFS                  ),
  ( "IDLE_PATTERN_DETECT_04"        , DCB_IDLE_PATTERN_DETECT_04_REG        , DCB_IDLE_PATTERN_DETECT_04_MASK        , DCB_IDLE_PATTERN_DETECT_04_OFS        ),
  ( "BITSLIP_OK_04"                 , DCB_BITSLIP_OK_04_REG                 , DCB_BITSLIP_OK_04_MASK                 , DCB_BITSLIP_OK_04_OFS                 ),
  ( "DELAY_OK_04"                   , DCB_DELAY_OK_04_REG                   , DCB_DELAY_OK_04_MASK                   , DCB_DELAY_OK_04_OFS                   ),
  ( "SYNC_DONE_04"                  , DCB_SYNC_DONE_04_REG                  , DCB_SYNC_DONE_04_MASK                  , DCB_SYNC_DONE_04_OFS                  ),
  ( "IDLE_PATTERN_DETECT_03"        , DCB_IDLE_PATTERN_DETECT_03_REG        , DCB_IDLE_PATTERN_DETECT_03_MASK        , DCB_IDLE_PATTERN_DETECT_03_OFS        ),
  ( "BITSLIP_OK_03"                 , DCB_BITSLIP_OK_03_REG                 , DCB_BITSLIP_OK_03_MASK                 , DCB_BITSLIP_OK_03_OFS                 ),
  ( "DELAY_OK_03"                   , DCB_DELAY_OK_03_REG                   , DCB_DELAY_OK_03_MASK                   , DCB_DELAY_OK_03_OFS                   ),
  ( "SYNC_DONE_03"                  , DCB_SYNC_DONE_03_REG                  , DCB_SYNC_DONE_03_MASK                  , DCB_SYNC_DONE_03_OFS                  ),
  ( "IDLE_PATTERN_DETECT_02"        , DCB_IDLE_PATTERN_DETECT_02_REG        , DCB_IDLE_PATTERN_DETECT_02_MASK        , DCB_IDLE_PATTERN_DETECT_02_OFS        ),
  ( "BITSLIP_OK_02"                 , DCB_BITSLIP_OK_02_REG                 , DCB_BITSLIP_OK_02_MASK                 , DCB_BITSLIP_OK_02_OFS                 ),
  ( "DELAY_OK_02"                   , DCB_DELAY_OK_02_REG                   , DCB_DELAY_OK_02_MASK                   , DCB_DELAY_OK_02_OFS                   ),
  ( "SYNC_DONE_02"                  , DCB_SYNC_DONE_02_REG                  , DCB_SYNC_DONE_02_MASK                  , DCB_SYNC_DONE_02_OFS                  ),
  ( "IDLE_PATTERN_DETECT_01"        , DCB_IDLE_PATTERN_DETECT_01_REG        , DCB_IDLE_PATTERN_DETECT_01_MASK        , DCB_IDLE_PATTERN_DETECT_01_OFS        ),
  ( "BITSLIP_OK_01"                 , DCB_BITSLIP_OK_01_REG                 , DCB_BITSLIP_OK_01_MASK                 , DCB_BITSLIP_OK_01_OFS                 ),
  ( "DELAY_OK_01"                   , DCB_DELAY_OK_01_REG                   , DCB_DELAY_OK_01_MASK                   , DCB_DELAY_OK_01_OFS                   ),
  ( "SYNC_DONE_01"                  , DCB_SYNC_DONE_01_REG                  , DCB_SYNC_DONE_01_MASK                  , DCB_SYNC_DONE_01_OFS                  ),
  ( "IDLE_PATTERN_DETECT_00"        , DCB_IDLE_PATTERN_DETECT_00_REG        , DCB_IDLE_PATTERN_DETECT_00_MASK        , DCB_IDLE_PATTERN_DETECT_00_OFS        ),
  ( "BITSLIP_OK_00"                 , DCB_BITSLIP_OK_00_REG                 , DCB_BITSLIP_OK_00_MASK                 , DCB_BITSLIP_OK_00_OFS                 ),
  ( "DELAY_OK_00"                   , DCB_DELAY_OK_00_REG                   , DCB_DELAY_OK_00_MASK                   , DCB_DELAY_OK_00_OFS                   ),
  ( "SYNC_DONE_00"                  , DCB_SYNC_DONE_00_REG                  , DCB_SYNC_DONE_00_MASK                  , DCB_SYNC_DONE_00_OFS                  ),
  ( "IDLE_PATTERN_DETECT_15"        , DCB_IDLE_PATTERN_DETECT_15_REG        , DCB_IDLE_PATTERN_DETECT_15_MASK        , DCB_IDLE_PATTERN_DETECT_15_OFS        ),
  ( "BITSLIP_OK_15"                 , DCB_BITSLIP_OK_15_REG                 , DCB_BITSLIP_OK_15_MASK                 , DCB_BITSLIP_OK_15_OFS                 ),
  ( "DELAY_OK_15"                   , DCB_DELAY_OK_15_REG                   , DCB_DELAY_OK_15_MASK                   , DCB_DELAY_OK_15_OFS                   ),
  ( "SYNC_DONE_15"                  , DCB_SYNC_DONE_15_REG                  , DCB_SYNC_DONE_15_MASK                  , DCB_SYNC_DONE_15_OFS                  ),
  ( "IDLE_PATTERN_DETECT_14"        , DCB_IDLE_PATTERN_DETECT_14_REG        , DCB_IDLE_PATTERN_DETECT_14_MASK        , DCB_IDLE_PATTERN_DETECT_14_OFS        ),
  ( "BITSLIP_OK_14"                 , DCB_BITSLIP_OK_14_REG                 , DCB_BITSLIP_OK_14_MASK                 , DCB_BITSLIP_OK_14_OFS                 ),
  ( "DELAY_OK_14"                   , DCB_DELAY_OK_14_REG                   , DCB_DELAY_OK_14_MASK                   , DCB_DELAY_OK_14_OFS                   ),
  ( "SYNC_DONE_14"                  , DCB_SYNC_DONE_14_REG                  , DCB_SYNC_DONE_14_MASK                  , DCB_SYNC_DONE_14_OFS                  ),
  ( "IDLE_PATTERN_DETECT_13"        , DCB_IDLE_PATTERN_DETECT_13_REG        , DCB_IDLE_PATTERN_DETECT_13_MASK        , DCB_IDLE_PATTERN_DETECT_13_OFS        ),
  ( "BITSLIP_OK_13"                 , DCB_BITSLIP_OK_13_REG                 , DCB_BITSLIP_OK_13_MASK                 , DCB_BITSLIP_OK_13_OFS                 ),
  ( "DELAY_OK_13"                   , DCB_DELAY_OK_13_REG                   , DCB_DELAY_OK_13_MASK                   , DCB_DELAY_OK_13_OFS                   ),
  ( "SYNC_DONE_13"                  , DCB_SYNC_DONE_13_REG                  , DCB_SYNC_DONE_13_MASK                  , DCB_SYNC_DONE_13_OFS                  ),
  ( "IDLE_PATTERN_DETECT_12"        , DCB_IDLE_PATTERN_DETECT_12_REG        , DCB_IDLE_PATTERN_DETECT_12_MASK        , DCB_IDLE_PATTERN_DETECT_12_OFS        ),
  ( "BITSLIP_OK_12"                 , DCB_BITSLIP_OK_12_REG                 , DCB_BITSLIP_OK_12_MASK                 , DCB_BITSLIP_OK_12_OFS                 ),
  ( "DELAY_OK_12"                   , DCB_DELAY_OK_12_REG                   , DCB_DELAY_OK_12_MASK                   , DCB_DELAY_OK_12_OFS                   ),
  ( "SYNC_DONE_12"                  , DCB_SYNC_DONE_12_REG                  , DCB_SYNC_DONE_12_MASK                  , DCB_SYNC_DONE_12_OFS                  ),
  ( "IDLE_PATTERN_DETECT_11"        , DCB_IDLE_PATTERN_DETECT_11_REG        , DCB_IDLE_PATTERN_DETECT_11_MASK        , DCB_IDLE_PATTERN_DETECT_11_OFS        ),
  ( "BITSLIP_OK_11"                 , DCB_BITSLIP_OK_11_REG                 , DCB_BITSLIP_OK_11_MASK                 , DCB_BITSLIP_OK_11_OFS                 ),
  ( "DELAY_OK_11"                   , DCB_DELAY_OK_11_REG                   , DCB_DELAY_OK_11_MASK                   , DCB_DELAY_OK_11_OFS                   ),
  ( "SYNC_DONE_11"                  , DCB_SYNC_DONE_11_REG                  , DCB_SYNC_DONE_11_MASK                  , DCB_SYNC_DONE_11_OFS                  ),
  ( "IDLE_PATTERN_DETECT_10"        , DCB_IDLE_PATTERN_DETECT_10_REG        , DCB_IDLE_PATTERN_DETECT_10_MASK        , DCB_IDLE_PATTERN_DETECT_10_OFS        ),
  ( "BITSLIP_OK_10"                 , DCB_BITSLIP_OK_10_REG                 , DCB_BITSLIP_OK_10_MASK                 , DCB_BITSLIP_OK_10_OFS                 ),
  ( "DELAY_OK_10"                   , DCB_DELAY_OK_10_REG                   , DCB_DELAY_OK_10_MASK                   , DCB_DELAY_OK_10_OFS                   ),
  ( "SYNC_DONE_10"                  , DCB_SYNC_DONE_10_REG                  , DCB_SYNC_DONE_10_MASK                  , DCB_SYNC_DONE_10_OFS                  ),
  ( "IDLE_PATTERN_DETECT_09"        , DCB_IDLE_PATTERN_DETECT_09_REG        , DCB_IDLE_PATTERN_DETECT_09_MASK        , DCB_IDLE_PATTERN_DETECT_09_OFS        ),
  ( "BITSLIP_OK_09"                 , DCB_BITSLIP_OK_09_REG                 , DCB_BITSLIP_OK_09_MASK                 , DCB_BITSLIP_OK_09_OFS                 ),
  ( "DELAY_OK_09"                   , DCB_DELAY_OK_09_REG                   , DCB_DELAY_OK_09_MASK                   , DCB_DELAY_OK_09_OFS                   ),
  ( "SYNC_DONE_09"                  , DCB_SYNC_DONE_09_REG                  , DCB_SYNC_DONE_09_MASK                  , DCB_SYNC_DONE_09_OFS                  ),
  ( "IDLE_PATTERN_DETECT_08"        , DCB_IDLE_PATTERN_DETECT_08_REG        , DCB_IDLE_PATTERN_DETECT_08_MASK        , DCB_IDLE_PATTERN_DETECT_08_OFS        ),
  ( "BITSLIP_OK_08"                 , DCB_BITSLIP_OK_08_REG                 , DCB_BITSLIP_OK_08_MASK                 , DCB_BITSLIP_OK_08_OFS                 ),
  ( "DELAY_OK_08"                   , DCB_DELAY_OK_08_REG                   , DCB_DELAY_OK_08_MASK                   , DCB_DELAY_OK_08_OFS                   ),
  ( "SYNC_DONE_08"                  , DCB_SYNC_DONE_08_REG                  , DCB_SYNC_DONE_08_MASK                  , DCB_SYNC_DONE_08_OFS                  ),
  ( "IDLE_PATTERN_DETECT_17"        , DCB_IDLE_PATTERN_DETECT_17_REG        , DCB_IDLE_PATTERN_DETECT_17_MASK        , DCB_IDLE_PATTERN_DETECT_17_OFS        ),
  ( "BITSLIP_OK_17"                 , DCB_BITSLIP_OK_17_REG                 , DCB_BITSLIP_OK_17_MASK                 , DCB_BITSLIP_OK_17_OFS                 ),
  ( "DELAY_OK_17"                   , DCB_DELAY_OK_17_REG                   , DCB_DELAY_OK_17_MASK                   , DCB_DELAY_OK_17_OFS                   ),
  ( "SYNC_DONE_17"                  , DCB_SYNC_DONE_17_REG                  , DCB_SYNC_DONE_17_MASK                  , DCB_SYNC_DONE_17_OFS                  ),
  ( "CRC_ERRORS_00"                 , DCB_CRC_ERRORS_00_REG                 , DCB_CRC_ERRORS_00_MASK                 , DCB_CRC_ERRORS_00_OFS                 ),
  ( "FRAME_ERRORS_00"               , DCB_FRAME_ERRORS_00_REG               , DCB_FRAME_ERRORS_00_MASK               , DCB_FRAME_ERRORS_00_OFS               ),
  ( "DATAGRAM_ERRORS_00"            , DCB_DATAGRAM_ERRORS_00_REG            , DCB_DATAGRAM_ERRORS_00_MASK            , DCB_DATAGRAM_ERRORS_00_OFS            ),
  ( "SYNC_ERRORS_00"                , DCB_SYNC_ERRORS_00_REG                , DCB_SYNC_ERRORS_00_MASK                , DCB_SYNC_ERRORS_00_OFS                ),
  ( "CRC_ERRORS_01"                 , DCB_CRC_ERRORS_01_REG                 , DCB_CRC_ERRORS_01_MASK                 , DCB_CRC_ERRORS_01_OFS                 ),
  ( "FRAME_ERRORS_01"               , DCB_FRAME_ERRORS_01_REG               , DCB_FRAME_ERRORS_01_MASK               , DCB_FRAME_ERRORS_01_OFS               ),
  ( "DATAGRAM_ERRORS_01"            , DCB_DATAGRAM_ERRORS_01_REG            , DCB_DATAGRAM_ERRORS_01_MASK            , DCB_DATAGRAM_ERRORS_01_OFS            ),
  ( "SYNC_ERRORS_01"                , DCB_SYNC_ERRORS_01_REG                , DCB_SYNC_ERRORS_01_MASK                , DCB_SYNC_ERRORS_01_OFS                ),
  ( "CRC_ERRORS_02"                 , DCB_CRC_ERRORS_02_REG                 , DCB_CRC_ERRORS_02_MASK                 , DCB_CRC_ERRORS_02_OFS                 ),
  ( "FRAME_ERRORS_02"               , DCB_FRAME_ERRORS_02_REG               , DCB_FRAME_ERRORS_02_MASK               , DCB_FRAME_ERRORS_02_OFS               ),
  ( "DATAGRAM_ERRORS_02"            , DCB_DATAGRAM_ERRORS_02_REG            , DCB_DATAGRAM_ERRORS_02_MASK            , DCB_DATAGRAM_ERRORS_02_OFS            ),
  ( "SYNC_ERRORS_02"                , DCB_SYNC_ERRORS_02_REG                , DCB_SYNC_ERRORS_02_MASK                , DCB_SYNC_ERRORS_02_OFS                ),
  ( "CRC_ERRORS_03"                 , DCB_CRC_ERRORS_03_REG                 , DCB_CRC_ERRORS_03_MASK                 , DCB_CRC_ERRORS_03_OFS                 ),
  ( "FRAME_ERRORS_03"               , DCB_FRAME_ERRORS_03_REG               , DCB_FRAME_ERRORS_03_MASK               , DCB_FRAME_ERRORS_03_OFS               ),
  ( "DATAGRAM_ERRORS_03"            , DCB_DATAGRAM_ERRORS_03_REG            , DCB_DATAGRAM_ERRORS_03_MASK            , DCB_DATAGRAM_ERRORS_03_OFS            ),
  ( "SYNC_ERRORS_03"                , DCB_SYNC_ERRORS_03_REG                , DCB_SYNC_ERRORS_03_MASK                , DCB_SYNC_ERRORS_03_OFS                ),
  ( "CRC_ERRORS_04"                 , DCB_CRC_ERRORS_04_REG                 , DCB_CRC_ERRORS_04_MASK                 , DCB_CRC_ERRORS_04_OFS                 ),
  ( "FRAME_ERRORS_04"               , DCB_FRAME_ERRORS_04_REG               , DCB_FRAME_ERRORS_04_MASK               , DCB_FRAME_ERRORS_04_OFS               ),
  ( "DATAGRAM_ERRORS_04"            , DCB_DATAGRAM_ERRORS_04_REG            , DCB_DATAGRAM_ERRORS_04_MASK            , DCB_DATAGRAM_ERRORS_04_OFS            ),
  ( "SYNC_ERRORS_04"                , DCB_SYNC_ERRORS_04_REG                , DCB_SYNC_ERRORS_04_MASK                , DCB_SYNC_ERRORS_04_OFS                ),
  ( "CRC_ERRORS_05"                 , DCB_CRC_ERRORS_05_REG                 , DCB_CRC_ERRORS_05_MASK                 , DCB_CRC_ERRORS_05_OFS                 ),
  ( "FRAME_ERRORS_05"               , DCB_FRAME_ERRORS_05_REG               , DCB_FRAME_ERRORS_05_MASK               , DCB_FRAME_ERRORS_05_OFS               ),
  ( "DATAGRAM_ERRORS_05"            , DCB_DATAGRAM_ERRORS_05_REG            , DCB_DATAGRAM_ERRORS_05_MASK            , DCB_DATAGRAM_ERRORS_05_OFS            ),
  ( "SYNC_ERRORS_05"                , DCB_SYNC_ERRORS_05_REG                , DCB_SYNC_ERRORS_05_MASK                , DCB_SYNC_ERRORS_05_OFS                ),
  ( "CRC_ERRORS_06"                 , DCB_CRC_ERRORS_06_REG                 , DCB_CRC_ERRORS_06_MASK                 , DCB_CRC_ERRORS_06_OFS                 ),
  ( "FRAME_ERRORS_06"               , DCB_FRAME_ERRORS_06_REG               , DCB_FRAME_ERRORS_06_MASK               , DCB_FRAME_ERRORS_06_OFS               ),
  ( "DATAGRAM_ERRORS_06"            , DCB_DATAGRAM_ERRORS_06_REG            , DCB_DATAGRAM_ERRORS_06_MASK            , DCB_DATAGRAM_ERRORS_06_OFS            ),
  ( "SYNC_ERRORS_06"                , DCB_SYNC_ERRORS_06_REG                , DCB_SYNC_ERRORS_06_MASK                , DCB_SYNC_ERRORS_06_OFS                ),
  ( "CRC_ERRORS_07"                 , DCB_CRC_ERRORS_07_REG                 , DCB_CRC_ERRORS_07_MASK                 , DCB_CRC_ERRORS_07_OFS                 ),
  ( "FRAME_ERRORS_07"               , DCB_FRAME_ERRORS_07_REG               , DCB_FRAME_ERRORS_07_MASK               , DCB_FRAME_ERRORS_07_OFS               ),
  ( "DATAGRAM_ERRORS_07"            , DCB_DATAGRAM_ERRORS_07_REG            , DCB_DATAGRAM_ERRORS_07_MASK            , DCB_DATAGRAM_ERRORS_07_OFS            ),
  ( "SYNC_ERRORS_07"                , DCB_SYNC_ERRORS_07_REG                , DCB_SYNC_ERRORS_07_MASK                , DCB_SYNC_ERRORS_07_OFS                ),
  ( "CRC_ERRORS_08"                 , DCB_CRC_ERRORS_08_REG                 , DCB_CRC_ERRORS_08_MASK                 , DCB_CRC_ERRORS_08_OFS                 ),
  ( "FRAME_ERRORS_08"               , DCB_FRAME_ERRORS_08_REG               , DCB_FRAME_ERRORS_08_MASK               , DCB_FRAME_ERRORS_08_OFS               ),
  ( "DATAGRAM_ERRORS_08"            , DCB_DATAGRAM_ERRORS_08_REG            , DCB_DATAGRAM_ERRORS_08_MASK            , DCB_DATAGRAM_ERRORS_08_OFS            ),
  ( "SYNC_ERRORS_08"                , DCB_SYNC_ERRORS_08_REG                , DCB_SYNC_ERRORS_08_MASK                , DCB_SYNC_ERRORS_08_OFS                ),
  ( "CRC_ERRORS_09"                 , DCB_CRC_ERRORS_09_REG                 , DCB_CRC_ERRORS_09_MASK                 , DCB_CRC_ERRORS_09_OFS                 ),
  ( "FRAME_ERRORS_09"               , DCB_FRAME_ERRORS_09_REG               , DCB_FRAME_ERRORS_09_MASK               , DCB_FRAME_ERRORS_09_OFS               ),
  ( "DATAGRAM_ERRORS_09"            , DCB_DATAGRAM_ERRORS_09_REG            , DCB_DATAGRAM_ERRORS_09_MASK            , DCB_DATAGRAM_ERRORS_09_OFS            ),
  ( "SYNC_ERRORS_09"                , DCB_SYNC_ERRORS_09_REG                , DCB_SYNC_ERRORS_09_MASK                , DCB_SYNC_ERRORS_09_OFS                ),
  ( "CRC_ERRORS_10"                 , DCB_CRC_ERRORS_10_REG                 , DCB_CRC_ERRORS_10_MASK                 , DCB_CRC_ERRORS_10_OFS                 ),
  ( "FRAME_ERRORS_10"               , DCB_FRAME_ERRORS_10_REG               , DCB_FRAME_ERRORS_10_MASK               , DCB_FRAME_ERRORS_10_OFS               ),
  ( "DATAGRAM_ERRORS_10"            , DCB_DATAGRAM_ERRORS_10_REG            , DCB_DATAGRAM_ERRORS_10_MASK            , DCB_DATAGRAM_ERRORS_10_OFS            ),
  ( "SYNC_ERRORS_10"                , DCB_SYNC_ERRORS_10_REG                , DCB_SYNC_ERRORS_10_MASK                , DCB_SYNC_ERRORS_10_OFS                ),
  ( "CRC_ERRORS_11"                 , DCB_CRC_ERRORS_11_REG                 , DCB_CRC_ERRORS_11_MASK                 , DCB_CRC_ERRORS_11_OFS                 ),
  ( "FRAME_ERRORS_11"               , DCB_FRAME_ERRORS_11_REG               , DCB_FRAME_ERRORS_11_MASK               , DCB_FRAME_ERRORS_11_OFS               ),
  ( "DATAGRAM_ERRORS_11"            , DCB_DATAGRAM_ERRORS_11_REG            , DCB_DATAGRAM_ERRORS_11_MASK            , DCB_DATAGRAM_ERRORS_11_OFS            ),
  ( "SYNC_ERRORS_11"                , DCB_SYNC_ERRORS_11_REG                , DCB_SYNC_ERRORS_11_MASK                , DCB_SYNC_ERRORS_11_OFS                ),
  ( "CRC_ERRORS_12"                 , DCB_CRC_ERRORS_12_REG                 , DCB_CRC_ERRORS_12_MASK                 , DCB_CRC_ERRORS_12_OFS                 ),
  ( "FRAME_ERRORS_12"               , DCB_FRAME_ERRORS_12_REG               , DCB_FRAME_ERRORS_12_MASK               , DCB_FRAME_ERRORS_12_OFS               ),
  ( "DATAGRAM_ERRORS_12"            , DCB_DATAGRAM_ERRORS_12_REG            , DCB_DATAGRAM_ERRORS_12_MASK            , DCB_DATAGRAM_ERRORS_12_OFS            ),
  ( "SYNC_ERRORS_12"                , DCB_SYNC_ERRORS_12_REG                , DCB_SYNC_ERRORS_12_MASK                , DCB_SYNC_ERRORS_12_OFS                ),
  ( "CRC_ERRORS_13"                 , DCB_CRC_ERRORS_13_REG                 , DCB_CRC_ERRORS_13_MASK                 , DCB_CRC_ERRORS_13_OFS                 ),
  ( "FRAME_ERRORS_13"               , DCB_FRAME_ERRORS_13_REG               , DCB_FRAME_ERRORS_13_MASK               , DCB_FRAME_ERRORS_13_OFS               ),
  ( "DATAGRAM_ERRORS_13"            , DCB_DATAGRAM_ERRORS_13_REG            , DCB_DATAGRAM_ERRORS_13_MASK            , DCB_DATAGRAM_ERRORS_13_OFS            ),
  ( "SYNC_ERRORS_13"                , DCB_SYNC_ERRORS_13_REG                , DCB_SYNC_ERRORS_13_MASK                , DCB_SYNC_ERRORS_13_OFS                ),
  ( "CRC_ERRORS_14"                 , DCB_CRC_ERRORS_14_REG                 , DCB_CRC_ERRORS_14_MASK                 , DCB_CRC_ERRORS_14_OFS                 ),
  ( "FRAME_ERRORS_14"               , DCB_FRAME_ERRORS_14_REG               , DCB_FRAME_ERRORS_14_MASK               , DCB_FRAME_ERRORS_14_OFS               ),
  ( "DATAGRAM_ERRORS_14"            , DCB_DATAGRAM_ERRORS_14_REG            , DCB_DATAGRAM_ERRORS_14_MASK            , DCB_DATAGRAM_ERRORS_14_OFS            ),
  ( "SYNC_ERRORS_14"                , DCB_SYNC_ERRORS_14_REG                , DCB_SYNC_ERRORS_14_MASK                , DCB_SYNC_ERRORS_14_OFS                ),
  ( "CRC_ERRORS_15"                 , DCB_CRC_ERRORS_15_REG                 , DCB_CRC_ERRORS_15_MASK                 , DCB_CRC_ERRORS_15_OFS                 ),
  ( "FRAME_ERRORS_15"               , DCB_FRAME_ERRORS_15_REG               , DCB_FRAME_ERRORS_15_MASK               , DCB_FRAME_ERRORS_15_OFS               ),
  ( "DATAGRAM_ERRORS_15"            , DCB_DATAGRAM_ERRORS_15_REG            , DCB_DATAGRAM_ERRORS_15_MASK            , DCB_DATAGRAM_ERRORS_15_OFS            ),
  ( "SYNC_ERRORS_15"                , DCB_SYNC_ERRORS_15_REG                , DCB_SYNC_ERRORS_15_MASK                , DCB_SYNC_ERRORS_15_OFS                ),
  ( "CRC_ERRORS_17"                 , DCB_CRC_ERRORS_17_REG                 , DCB_CRC_ERRORS_17_MASK                 , DCB_CRC_ERRORS_17_OFS                 ),
  ( "FRAME_ERRORS_17"               , DCB_FRAME_ERRORS_17_REG               , DCB_FRAME_ERRORS_17_MASK               , DCB_FRAME_ERRORS_17_OFS               ),
  ( "DATAGRAM_ERRORS_17"            , DCB_DATAGRAM_ERRORS_17_REG            , DCB_DATAGRAM_ERRORS_17_MASK            , DCB_DATAGRAM_ERRORS_17_OFS            ),
  ( "SYNC_ERRORS_17"                , DCB_SYNC_ERRORS_17_REG                , DCB_SYNC_ERRORS_17_MASK                , DCB_SYNC_ERRORS_17_OFS                ),
  ( "APPLY_SETTINGS_LMK"            , DCB_APPLY_SETTINGS_LMK_REG            , DCB_APPLY_SETTINGS_LMK_MASK            , DCB_APPLY_SETTINGS_LMK_OFS            ),
  ( "LMK0_RESET"                    , DCB_LMK0_RESET_REG                    , DCB_LMK0_RESET_MASK                    , DCB_LMK0_RESET_OFS                    ),
  ( "LMK0_CLKOUT_MUX"               , DCB_LMK0_CLKOUT_MUX_REG               , DCB_LMK0_CLKOUT_MUX_MASK               , DCB_LMK0_CLKOUT_MUX_OFS               ),
  ( "LMK0_CLKOUT_EN"                , DCB_LMK0_CLKOUT_EN_REG                , DCB_LMK0_CLKOUT_EN_MASK                , DCB_LMK0_CLKOUT_EN_OFS                ),
  ( "LMK0_CLKOUT_DIV"               , DCB_LMK0_CLKOUT_DIV_REG               , DCB_LMK0_CLKOUT_DIV_MASK               , DCB_LMK0_CLKOUT_DIV_OFS               ),
  ( "LMK0_CLKOUT_DLY"               , DCB_LMK0_CLKOUT_DLY_REG               , DCB_LMK0_CLKOUT_DLY_MASK               , DCB_LMK0_CLKOUT_DLY_OFS               ),
  ( "LMK1_CLKOUT_MUX"               , DCB_LMK1_CLKOUT_MUX_REG               , DCB_LMK1_CLKOUT_MUX_MASK               , DCB_LMK1_CLKOUT_MUX_OFS               ),
  ( "LMK1_CLKOUT_EN"                , DCB_LMK1_CLKOUT_EN_REG                , DCB_LMK1_CLKOUT_EN_MASK                , DCB_LMK1_CLKOUT_EN_OFS                ),
  ( "LMK1_CLKOUT_DIV"               , DCB_LMK1_CLKOUT_DIV_REG               , DCB_LMK1_CLKOUT_DIV_MASK               , DCB_LMK1_CLKOUT_DIV_OFS               ),
  ( "LMK1_CLKOUT_DLY"               , DCB_LMK1_CLKOUT_DLY_REG               , DCB_LMK1_CLKOUT_DLY_MASK               , DCB_LMK1_CLKOUT_DLY_OFS               ),
  ( "LMK2_CLKOUT_MUX"               , DCB_LMK2_CLKOUT_MUX_REG               , DCB_LMK2_CLKOUT_MUX_MASK               , DCB_LMK2_CLKOUT_MUX_OFS               ),
  ( "LMK2_CLKOUT_EN"                , DCB_LMK2_CLKOUT_EN_REG                , DCB_LMK2_CLKOUT_EN_MASK                , DCB_LMK2_CLKOUT_EN_OFS                ),
  ( "LMK2_CLKOUT_DIV"               , DCB_LMK2_CLKOUT_DIV_REG               , DCB_LMK2_CLKOUT_DIV_MASK               , DCB_LMK2_CLKOUT_DIV_OFS               ),
  ( "LMK2_CLKOUT_DLY"               , DCB_LMK2_CLKOUT_DLY_REG               , DCB_LMK2_CLKOUT_DLY_MASK               , DCB_LMK2_CLKOUT_DLY_OFS               ),
  ( "LMK3_CLKOUT_MUX"               , DCB_LMK3_CLKOUT_MUX_REG               , DCB_LMK3_CLKOUT_MUX_MASK               , DCB_LMK3_CLKOUT_MUX_OFS               ),
  ( "LMK3_CLKOUT_EN"                , DCB_LMK3_CLKOUT_EN_REG                , DCB_LMK3_CLKOUT_EN_MASK                , DCB_LMK3_CLKOUT_EN_OFS                ),
  ( "LMK3_CLKOUT_DIV"               , DCB_LMK3_CLKOUT_DIV_REG               , DCB_LMK3_CLKOUT_DIV_MASK               , DCB_LMK3_CLKOUT_DIV_OFS               ),
  ( "LMK3_CLKOUT_DLY"               , DCB_LMK3_CLKOUT_DLY_REG               , DCB_LMK3_CLKOUT_DLY_MASK               , DCB_LMK3_CLKOUT_DLY_OFS               ),
  ( "LMK4_CLKOUT_MUX"               , DCB_LMK4_CLKOUT_MUX_REG               , DCB_LMK4_CLKOUT_MUX_MASK               , DCB_LMK4_CLKOUT_MUX_OFS               ),
  ( "LMK4_CLKOUT_EN"                , DCB_LMK4_CLKOUT_EN_REG                , DCB_LMK4_CLKOUT_EN_MASK                , DCB_LMK4_CLKOUT_EN_OFS                ),
  ( "LMK4_CLKOUT_DIV"               , DCB_LMK4_CLKOUT_DIV_REG               , DCB_LMK4_CLKOUT_DIV_MASK               , DCB_LMK4_CLKOUT_DIV_OFS               ),
  ( "LMK4_CLKOUT_DLY"               , DCB_LMK4_CLKOUT_DLY_REG               , DCB_LMK4_CLKOUT_DLY_MASK               , DCB_LMK4_CLKOUT_DLY_OFS               ),
  ( "LMK5_CLKOUT_MUX"               , DCB_LMK5_CLKOUT_MUX_REG               , DCB_LMK5_CLKOUT_MUX_MASK               , DCB_LMK5_CLKOUT_MUX_OFS               ),
  ( "LMK5_CLKOUT_EN"                , DCB_LMK5_CLKOUT_EN_REG                , DCB_LMK5_CLKOUT_EN_MASK                , DCB_LMK5_CLKOUT_EN_OFS                ),
  ( "LMK5_CLKOUT_DIV"               , DCB_LMK5_CLKOUT_DIV_REG               , DCB_LMK5_CLKOUT_DIV_MASK               , DCB_LMK5_CLKOUT_DIV_OFS               ),
  ( "LMK5_CLKOUT_DLY"               , DCB_LMK5_CLKOUT_DLY_REG               , DCB_LMK5_CLKOUT_DLY_MASK               , DCB_LMK5_CLKOUT_DLY_OFS               ),
  ( "LMK6_CLKOUT_MUX"               , DCB_LMK6_CLKOUT_MUX_REG               , DCB_LMK6_CLKOUT_MUX_MASK               , DCB_LMK6_CLKOUT_MUX_OFS               ),
  ( "LMK6_CLKOUT_EN"                , DCB_LMK6_CLKOUT_EN_REG                , DCB_LMK6_CLKOUT_EN_MASK                , DCB_LMK6_CLKOUT_EN_OFS                ),
  ( "LMK6_CLKOUT_DIV"               , DCB_LMK6_CLKOUT_DIV_REG               , DCB_LMK6_CLKOUT_DIV_MASK               , DCB_LMK6_CLKOUT_DIV_OFS               ),
  ( "LMK6_CLKOUT_DLY"               , DCB_LMK6_CLKOUT_DLY_REG               , DCB_LMK6_CLKOUT_DLY_MASK               , DCB_LMK6_CLKOUT_DLY_OFS               ),
  ( "LMK7_CLKOUT_MUX"               , DCB_LMK7_CLKOUT_MUX_REG               , DCB_LMK7_CLKOUT_MUX_MASK               , DCB_LMK7_CLKOUT_MUX_OFS               ),
  ( "LMK7_CLKOUT_EN"                , DCB_LMK7_CLKOUT_EN_REG                , DCB_LMK7_CLKOUT_EN_MASK                , DCB_LMK7_CLKOUT_EN_OFS                ),
  ( "LMK7_CLKOUT_DIV"               , DCB_LMK7_CLKOUT_DIV_REG               , DCB_LMK7_CLKOUT_DIV_MASK               , DCB_LMK7_CLKOUT_DIV_OFS               ),
  ( "LMK7_CLKOUT_DLY"               , DCB_LMK7_CLKOUT_DLY_REG               , DCB_LMK7_CLKOUT_DLY_MASK               , DCB_LMK7_CLKOUT_DLY_OFS               ),
  ( "LMK8_PHASE_NOISE_OPT"          , DCB_LMK8_PHASE_NOISE_OPT_REG          , DCB_LMK8_PHASE_NOISE_OPT_MASK          , DCB_LMK8_PHASE_NOISE_OPT_OFS          ),
  ( "LMK9_VBOOST"                   , DCB_LMK9_VBOOST_REG                   , DCB_LMK9_VBOOST_MASK                   , DCB_LMK9_VBOOST_OFS                   ),
  ( "LMK11_DIV4"                    , DCB_LMK11_DIV4_REG                    , DCB_LMK11_DIV4_MASK                    , DCB_LMK11_DIV4_OFS                    ),
  ( "LMK13_OSCIN_FREQ"              , DCB_LMK13_OSCIN_FREQ_REG              , DCB_LMK13_OSCIN_FREQ_MASK              , DCB_LMK13_OSCIN_FREQ_OFS              ),
  ( "LMK13_VCO_R4_LF"               , DCB_LMK13_VCO_R4_LF_REG               , DCB_LMK13_VCO_R4_LF_MASK               , DCB_LMK13_VCO_R4_LF_OFS               ),
  ( "LMK13_VCO_R3_LF"               , DCB_LMK13_VCO_R3_LF_REG               , DCB_LMK13_VCO_R3_LF_MASK               , DCB_LMK13_VCO_R3_LF_OFS               ),
  ( "LMK13_VCO_C3_C4_LF"            , DCB_LMK13_VCO_C3_C4_LF_REG            , DCB_LMK13_VCO_C3_C4_LF_MASK            , DCB_LMK13_VCO_C3_C4_LF_OFS            ),
  ( "LMK14_EN_FOUT"                 , DCB_LMK14_EN_FOUT_REG                 , DCB_LMK14_EN_FOUT_MASK                 , DCB_LMK14_EN_FOUT_OFS                 ),
  ( "LMK14_EN_CLKOUT_GLOBAL"        , DCB_LMK14_EN_CLKOUT_GLOBAL_REG        , DCB_LMK14_EN_CLKOUT_GLOBAL_MASK        , DCB_LMK14_EN_CLKOUT_GLOBAL_OFS        ),
  ( "LMK14_POWERDOWN"               , DCB_LMK14_POWERDOWN_REG               , DCB_LMK14_POWERDOWN_MASK               , DCB_LMK14_POWERDOWN_OFS               ),
  ( "LMK14_PLL_MUX"                 , DCB_LMK14_PLL_MUX_REG                 , DCB_LMK14_PLL_MUX_MASK                 , DCB_LMK14_PLL_MUX_OFS                 ),
  ( "LMK14_PLL_R"                   , DCB_LMK14_PLL_R_REG                   , DCB_LMK14_PLL_R_MASK                   , DCB_LMK14_PLL_R_OFS                   ),
  ( "LMK15_PLL_CP_GAIN"             , DCB_LMK15_PLL_CP_GAIN_REG             , DCB_LMK15_PLL_CP_GAIN_MASK             , DCB_LMK15_PLL_CP_GAIN_OFS             ),
  ( "LMK15_VCO_DIV"                 , DCB_LMK15_VCO_DIV_REG                 , DCB_LMK15_VCO_DIV_MASK                 , DCB_LMK15_VCO_DIV_OFS                 ),
  ( "LMK15_PLL_N"                   , DCB_LMK15_PLL_N_REG                   , DCB_LMK15_PLL_N_MASK                   , DCB_LMK15_PLL_N_OFS                   ),
  ( "TIME_LSB"                      , DCB_TIME_LSB_REG                      , DCB_TIME_LSB_MASK                      , DCB_TIME_LSB_OFS                      ),
  ( "TIME_MSB"                      , DCB_TIME_MSB_REG                      , DCB_TIME_MSB_MASK                      , DCB_TIME_MSB_OFS                      ),
  ( "TIME_LSB_SET"                  , DCB_TIME_LSB_SET_REG                  , DCB_TIME_LSB_SET_MASK                  , DCB_TIME_LSB_SET_OFS                  ),
  ( "TIME_MSB_SET"                  , DCB_TIME_MSB_SET_REG                  , DCB_TIME_MSB_SET_MASK                  , DCB_TIME_MSB_SET_OFS                  ),
  ( "EVENT_TX_RATE"                 , DCB_EVENT_TX_RATE_REG                 , DCB_EVENT_TX_RATE_MASK                 , DCB_EVENT_TX_RATE_OFS                 ),
  ( "EVENT_NUMBER"                  , DCB_EVENT_NUMBER_REG                  , DCB_EVENT_NUMBER_MASK                  , DCB_EVENT_NUMBER_OFS                  ),
  ( "EXT_TRIGGER_OUT_ENABLE"        , DCB_EXT_TRIGGER_OUT_ENABLE_REG        , DCB_EXT_TRIGGER_OUT_ENABLE_MASK        , DCB_EXT_TRIGGER_OUT_ENABLE_OFS        ),
  ( "SET_BIT_TRG_CFG"               , DCB_SET_BIT_TRG_CFG_REG               , DCB_SET_BIT_TRG_CFG_MASK               , DCB_SET_BIT_TRG_CFG_OFS               ),
  ( "CLR_BIT_TRG_CFG"               , DCB_CLR_BIT_TRG_CFG_REG               , DCB_CLR_BIT_TRG_CFG_MASK               , DCB_CLR_BIT_TRG_CFG_OFS               ),
  ( "AUTO_TRIGGER_PERIOD"           , DCB_AUTO_TRIGGER_PERIOD_REG           , DCB_AUTO_TRIGGER_PERIOD_MASK           , DCB_AUTO_TRIGGER_PERIOD_OFS           ),
  ( "TRB_FLAG_NEW"                  , DCB_TRB_FLAG_NEW_REG                  , DCB_TRB_FLAG_NEW_MASK                  , DCB_TRB_FLAG_NEW_OFS                  ),
  ( "TRB_FLAG_PARITY_ERROR"         , DCB_TRB_FLAG_PARITY_ERROR_REG         , DCB_TRB_FLAG_PARITY_ERROR_MASK         , DCB_TRB_FLAG_PARITY_ERROR_OFS         ),
  ( "TRB_PARITY_ERROR_COUNT"        , DCB_TRB_PARITY_ERROR_COUNT_REG        , DCB_TRB_PARITY_ERROR_COUNT_MASK        , DCB_TRB_PARITY_ERROR_COUNT_OFS        ),
  ( "TRB_INFO_LSB"                  , DCB_TRB_INFO_LSB_REG                  , DCB_TRB_INFO_LSB_MASK                  , DCB_TRB_INFO_LSB_OFS                  ),
  ( "TRB_INFO_MSB"                  , DCB_TRB_INFO_MSB_REG                  , DCB_TRB_INFO_MSB_MASK                  , DCB_TRB_INFO_MSB_OFS                  ),
  ( "LMK_7_MOD"                     , DCB_LMK_7_MOD_REG                     , DCB_LMK_7_MOD_MASK                     , DCB_LMK_7_MOD_OFS                     ),
  ( "LMK_6_MOD"                     , DCB_LMK_6_MOD_REG                     , DCB_LMK_6_MOD_MASK                     , DCB_LMK_6_MOD_OFS                     ),
  ( "LMK_5_MOD"                     , DCB_LMK_5_MOD_REG                     , DCB_LMK_5_MOD_MASK                     , DCB_LMK_5_MOD_OFS                     ),
  ( "LMK_4_MOD"                     , DCB_LMK_4_MOD_REG                     , DCB_LMK_4_MOD_MASK                     , DCB_LMK_4_MOD_OFS                     ),
  ( "LMK_3_MOD"                     , DCB_LMK_3_MOD_REG                     , DCB_LMK_3_MOD_MASK                     , DCB_LMK_3_MOD_OFS                     ),
  ( "LMK_2_MOD"                     , DCB_LMK_2_MOD_REG                     , DCB_LMK_2_MOD_MASK                     , DCB_LMK_2_MOD_OFS                     ),
  ( "LMK_1_MOD"                     , DCB_LMK_1_MOD_REG                     , DCB_LMK_1_MOD_MASK                     , DCB_LMK_1_MOD_OFS                     ),
  ( "LMK_0_MOD"                     , DCB_LMK_0_MOD_REG                     , DCB_LMK_0_MOD_MASK                     , DCB_LMK_0_MOD_OFS                     ),
  ( "CMB_MSCB_ADR"                  , DCB_CMB_MSCB_ADR_REG                  , DCB_CMB_MSCB_ADR_MASK                  , DCB_CMB_MSCB_ADR_OFS                  ),
  ( "SD_PKT_CNT_0"                  , DCB_SD_PKT_CNT_0_REG                  , DCB_SD_PKT_CNT_0_MASK                  , DCB_SD_PKT_CNT_0_OFS                  ),
  ( "SD_PKT_CNT_1"                  , DCB_SD_PKT_CNT_1_REG                  , DCB_SD_PKT_CNT_1_MASK                  , DCB_SD_PKT_CNT_1_OFS                  ),
  ( "SD_PKT_CNT_2"                  , DCB_SD_PKT_CNT_2_REG                  , DCB_SD_PKT_CNT_2_MASK                  , DCB_SD_PKT_CNT_2_OFS                  ),
  ( "SD_PKT_CNT_3"                  , DCB_SD_PKT_CNT_3_REG                  , DCB_SD_PKT_CNT_3_MASK                  , DCB_SD_PKT_CNT_3_OFS                  ),
  ( "SD_PKT_CNT_4"                  , DCB_SD_PKT_CNT_4_REG                  , DCB_SD_PKT_CNT_4_MASK                  , DCB_SD_PKT_CNT_4_OFS                  ),
  ( "SD_PKT_CNT_5"                  , DCB_SD_PKT_CNT_5_REG                  , DCB_SD_PKT_CNT_5_MASK                  , DCB_SD_PKT_CNT_5_OFS                  ),
  ( "SD_PKT_CNT_6"                  , DCB_SD_PKT_CNT_6_REG                  , DCB_SD_PKT_CNT_6_MASK                  , DCB_SD_PKT_CNT_6_OFS                  ),
  ( "SD_PKT_CNT_7"                  , DCB_SD_PKT_CNT_7_REG                  , DCB_SD_PKT_CNT_7_MASK                  , DCB_SD_PKT_CNT_7_OFS                  ),
  ( "SD_PKT_CNT_8"                  , DCB_SD_PKT_CNT_8_REG                  , DCB_SD_PKT_CNT_8_MASK                  , DCB_SD_PKT_CNT_8_OFS                  ),
  ( "SD_PKT_CNT_9"                  , DCB_SD_PKT_CNT_9_REG                  , DCB_SD_PKT_CNT_9_MASK                  , DCB_SD_PKT_CNT_9_OFS                  ),
  ( "SD_PKT_CNT_10"                 , DCB_SD_PKT_CNT_10_REG                 , DCB_SD_PKT_CNT_10_MASK                 , DCB_SD_PKT_CNT_10_OFS                 ),
  ( "SD_PKT_CNT_11"                 , DCB_SD_PKT_CNT_11_REG                 , DCB_SD_PKT_CNT_11_MASK                 , DCB_SD_PKT_CNT_11_OFS                 ),
  ( "SD_PKT_CNT_12"                 , DCB_SD_PKT_CNT_12_REG                 , DCB_SD_PKT_CNT_12_MASK                 , DCB_SD_PKT_CNT_12_OFS                 ),
  ( "SD_PKT_CNT_13"                 , DCB_SD_PKT_CNT_13_REG                 , DCB_SD_PKT_CNT_13_MASK                 , DCB_SD_PKT_CNT_13_OFS                 ),
  ( "SD_PKT_CNT_14"                 , DCB_SD_PKT_CNT_14_REG                 , DCB_SD_PKT_CNT_14_MASK                 , DCB_SD_PKT_CNT_14_OFS                 ),
  ( "SD_PKT_CNT_15"                 , DCB_SD_PKT_CNT_15_REG                 , DCB_SD_PKT_CNT_15_MASK                 , DCB_SD_PKT_CNT_15_OFS                 ),
  ( "SD_PKT_CNT_17"                 , DCB_SD_PKT_CNT_17_REG                 , DCB_SD_PKT_CNT_17_MASK                 , DCB_SD_PKT_CNT_17_OFS                 ),
  ( "SD_TAP_0"                      , DCB_SD_TAP_0_REG                      , DCB_SD_TAP_0_MASK                      , DCB_SD_TAP_0_OFS                      ),
  ( "SD_EYE_0"                      , DCB_SD_EYE_0_REG                      , DCB_SD_EYE_0_MASK                      , DCB_SD_EYE_0_OFS                      ),
  ( "SD_TAP_1"                      , DCB_SD_TAP_1_REG                      , DCB_SD_TAP_1_MASK                      , DCB_SD_TAP_1_OFS                      ),
  ( "SD_EYE_1"                      , DCB_SD_EYE_1_REG                      , DCB_SD_EYE_1_MASK                      , DCB_SD_EYE_1_OFS                      ),
  ( "SD_TAP_2"                      , DCB_SD_TAP_2_REG                      , DCB_SD_TAP_2_MASK                      , DCB_SD_TAP_2_OFS                      ),
  ( "SD_EYE_2"                      , DCB_SD_EYE_2_REG                      , DCB_SD_EYE_2_MASK                      , DCB_SD_EYE_2_OFS                      ),
  ( "SD_TAP_3"                      , DCB_SD_TAP_3_REG                      , DCB_SD_TAP_3_MASK                      , DCB_SD_TAP_3_OFS                      ),
  ( "SD_EYE_3"                      , DCB_SD_EYE_3_REG                      , DCB_SD_EYE_3_MASK                      , DCB_SD_EYE_3_OFS                      ),
  ( "SD_TAP_4"                      , DCB_SD_TAP_4_REG                      , DCB_SD_TAP_4_MASK                      , DCB_SD_TAP_4_OFS                      ),
  ( "SD_EYE_4"                      , DCB_SD_EYE_4_REG                      , DCB_SD_EYE_4_MASK                      , DCB_SD_EYE_4_OFS                      ),
  ( "SD_TAP_5"                      , DCB_SD_TAP_5_REG                      , DCB_SD_TAP_5_MASK                      , DCB_SD_TAP_5_OFS                      ),
  ( "SD_EYE_5"                      , DCB_SD_EYE_5_REG                      , DCB_SD_EYE_5_MASK                      , DCB_SD_EYE_5_OFS                      ),
  ( "SD_TAP_6"                      , DCB_SD_TAP_6_REG                      , DCB_SD_TAP_6_MASK                      , DCB_SD_TAP_6_OFS                      ),
  ( "SD_EYE_6"                      , DCB_SD_EYE_6_REG                      , DCB_SD_EYE_6_MASK                      , DCB_SD_EYE_6_OFS                      ),
  ( "SD_TAP_7"                      , DCB_SD_TAP_7_REG                      , DCB_SD_TAP_7_MASK                      , DCB_SD_TAP_7_OFS                      ),
  ( "SD_EYE_7"                      , DCB_SD_EYE_7_REG                      , DCB_SD_EYE_7_MASK                      , DCB_SD_EYE_7_OFS                      ),
  ( "SD_TAP_8"                      , DCB_SD_TAP_8_REG                      , DCB_SD_TAP_8_MASK                      , DCB_SD_TAP_8_OFS                      ),
  ( "SD_EYE_8"                      , DCB_SD_EYE_8_REG                      , DCB_SD_EYE_8_MASK                      , DCB_SD_EYE_8_OFS                      ),
  ( "SD_TAP_9"                      , DCB_SD_TAP_9_REG                      , DCB_SD_TAP_9_MASK                      , DCB_SD_TAP_9_OFS                      ),
  ( "SD_EYE_9"                      , DCB_SD_EYE_9_REG                      , DCB_SD_EYE_9_MASK                      , DCB_SD_EYE_9_OFS                      ),
  ( "SD_TAP_10"                     , DCB_SD_TAP_10_REG                     , DCB_SD_TAP_10_MASK                     , DCB_SD_TAP_10_OFS                     ),
  ( "SD_EYE_10"                     , DCB_SD_EYE_10_REG                     , DCB_SD_EYE_10_MASK                     , DCB_SD_EYE_10_OFS                     ),
  ( "SD_TAP_11"                     , DCB_SD_TAP_11_REG                     , DCB_SD_TAP_11_MASK                     , DCB_SD_TAP_11_OFS                     ),
  ( "SD_EYE_11"                     , DCB_SD_EYE_11_REG                     , DCB_SD_EYE_11_MASK                     , DCB_SD_EYE_11_OFS                     ),
  ( "SD_TAP_12"                     , DCB_SD_TAP_12_REG                     , DCB_SD_TAP_12_MASK                     , DCB_SD_TAP_12_OFS                     ),
  ( "SD_EYE_12"                     , DCB_SD_EYE_12_REG                     , DCB_SD_EYE_12_MASK                     , DCB_SD_EYE_12_OFS                     ),
  ( "SD_TAP_13"                     , DCB_SD_TAP_13_REG                     , DCB_SD_TAP_13_MASK                     , DCB_SD_TAP_13_OFS                     ),
  ( "SD_EYE_13"                     , DCB_SD_EYE_13_REG                     , DCB_SD_EYE_13_MASK                     , DCB_SD_EYE_13_OFS                     ),
  ( "SD_TAP_14"                     , DCB_SD_TAP_14_REG                     , DCB_SD_TAP_14_MASK                     , DCB_SD_TAP_14_OFS                     ),
  ( "SD_EYE_14"                     , DCB_SD_EYE_14_REG                     , DCB_SD_EYE_14_MASK                     , DCB_SD_EYE_14_OFS                     ),
  ( "SD_TAP_15"                     , DCB_SD_TAP_15_REG                     , DCB_SD_TAP_15_MASK                     , DCB_SD_TAP_15_OFS                     ),
  ( "SD_EYE_15"                     , DCB_SD_EYE_15_REG                     , DCB_SD_EYE_15_MASK                     , DCB_SD_EYE_15_OFS                     ),
  ( "SD_TAP_17"                     , DCB_SD_TAP_17_REG                     , DCB_SD_TAP_17_MASK                     , DCB_SD_TAP_17_OFS                     ),
  ( "SD_EYE_17"                     , DCB_SD_EYE_17_REG                     , DCB_SD_EYE_17_MASK                     , DCB_SD_EYE_17_OFS                     ),
  ( "CRC32_REG_BANK"                , DCB_CRC32_REG_BANK_REG                , DCB_CRC32_REG_BANK_MASK                , DCB_CRC32_REG_BANK_OFS                ),
)



#
# Register Restore
#

DCB_DONT_TOUCH_REG = False
DCB_RESTORE_REG    = True

reg_restore = (DCB_DONT_TOUCH_REG,   # Offset 0x0000 
               DCB_DONT_TOUCH_REG,   # Offset 0x0004 
               DCB_DONT_TOUCH_REG,   # Offset 0x0008 
               DCB_DONT_TOUCH_REG,   # Offset 0x000C 
               DCB_DONT_TOUCH_REG,   # Offset 0x0010 
               DCB_DONT_TOUCH_REG,   # Offset 0x0014 
               DCB_DONT_TOUCH_REG,   # Offset 0x0018 
               DCB_DONT_TOUCH_REG,   # Offset 0x001C 
               DCB_DONT_TOUCH_REG,   # Offset 0x0020 
               DCB_RESTORE_REG   ,   # Offset 0x0024 
               DCB_DONT_TOUCH_REG,   # Offset 0x0028 
               DCB_DONT_TOUCH_REG,   # Offset 0x002C 
               DCB_DONT_TOUCH_REG,   # Offset 0x0030 
               DCB_RESTORE_REG   ,   # Offset 0x0034 
               DCB_RESTORE_REG   ,   # Offset 0x0038 
               DCB_DONT_TOUCH_REG,   # Offset 0x003C 
               DCB_DONT_TOUCH_REG,   # Offset 0x0040 
               DCB_RESTORE_REG   ,   # Offset 0x0044 
               DCB_DONT_TOUCH_REG,   # Offset 0x0048 
               DCB_DONT_TOUCH_REG,   # Offset 0x004C 
               DCB_RESTORE_REG   ,   # Offset 0x0050 
               DCB_RESTORE_REG   ,   # Offset 0x0054 
               DCB_DONT_TOUCH_REG,   # Offset 0x0058 
               DCB_DONT_TOUCH_REG,   # Offset 0x005C 
               DCB_DONT_TOUCH_REG,   # Offset 0x0060 
               DCB_DONT_TOUCH_REG,   # Offset 0x0064 
               DCB_DONT_TOUCH_REG,   # Offset 0x0068 
               DCB_DONT_TOUCH_REG,   # Offset 0x006C 
               DCB_DONT_TOUCH_REG,   # Offset 0x0070 
               DCB_DONT_TOUCH_REG,   # Offset 0x0074 
               DCB_DONT_TOUCH_REG,   # Offset 0x0078 
               DCB_DONT_TOUCH_REG,   # Offset 0x007C 
               DCB_DONT_TOUCH_REG,   # Offset 0x0080 
               DCB_DONT_TOUCH_REG,   # Offset 0x0084 
               DCB_DONT_TOUCH_REG,   # Offset 0x0088 
               DCB_DONT_TOUCH_REG,   # Offset 0x008C 
               DCB_DONT_TOUCH_REG,   # Offset 0x0090 
               DCB_DONT_TOUCH_REG,   # Offset 0x0094 
               DCB_DONT_TOUCH_REG,   # Offset 0x0098 
               DCB_DONT_TOUCH_REG,   # Offset 0x009C 
               DCB_DONT_TOUCH_REG,   # Offset 0x00A0 
               DCB_DONT_TOUCH_REG,   # Offset 0x00A4 
               DCB_DONT_TOUCH_REG,   # Offset 0x00A8 
               DCB_DONT_TOUCH_REG,   # Offset 0x00AC 
               DCB_RESTORE_REG   ,   # Offset 0x00B0 
               DCB_RESTORE_REG   ,   # Offset 0x00B4 
               DCB_RESTORE_REG   ,   # Offset 0x00B8 
               DCB_RESTORE_REG   ,   # Offset 0x00BC 
               DCB_RESTORE_REG   ,   # Offset 0x00C0 
               DCB_RESTORE_REG   ,   # Offset 0x00C4 
               DCB_RESTORE_REG   ,   # Offset 0x00C8 
               DCB_RESTORE_REG   ,   # Offset 0x00CC 
               DCB_RESTORE_REG   ,   # Offset 0x00D0 
               DCB_RESTORE_REG   ,   # Offset 0x00D4 
               DCB_RESTORE_REG   ,   # Offset 0x00D8 
               DCB_RESTORE_REG   ,   # Offset 0x00DC 
               DCB_RESTORE_REG   ,   # Offset 0x00E0 
               DCB_RESTORE_REG   ,   # Offset 0x00E4 
               DCB_DONT_TOUCH_REG,   # Offset 0x00E8 
               DCB_DONT_TOUCH_REG,   # Offset 0x00EC 
               DCB_DONT_TOUCH_REG,   # Offset 0x00F0 
               DCB_DONT_TOUCH_REG,   # Offset 0x00F4 
               DCB_DONT_TOUCH_REG,   # Offset 0x00F8 
               DCB_DONT_TOUCH_REG,   # Offset 0x00FC 
               DCB_RESTORE_REG   ,   # Offset 0x0100 
               DCB_DONT_TOUCH_REG,   # Offset 0x0104 
               DCB_DONT_TOUCH_REG,   # Offset 0x0108 
               DCB_RESTORE_REG   ,   # Offset 0x010C 
               DCB_DONT_TOUCH_REG,   # Offset 0x0110 
               DCB_DONT_TOUCH_REG,   # Offset 0x0114 
               DCB_DONT_TOUCH_REG,   # Offset 0x0118 
               DCB_DONT_TOUCH_REG,   # Offset 0x011C 
               DCB_RESTORE_REG   ,   # Offset 0x0120 
               DCB_DONT_TOUCH_REG,   # Offset 0x0124 
               DCB_DONT_TOUCH_REG,   # Offset 0x0128 
               DCB_DONT_TOUCH_REG,   # Offset 0x012C 
               DCB_DONT_TOUCH_REG,   # Offset 0x0130 
               DCB_DONT_TOUCH_REG,   # Offset 0x0134 
               DCB_DONT_TOUCH_REG,   # Offset 0x0138 
               DCB_DONT_TOUCH_REG,   # Offset 0x013C 
               DCB_DONT_TOUCH_REG,   # Offset 0x0140 
               DCB_DONT_TOUCH_REG,   # Offset 0x0144 
               DCB_DONT_TOUCH_REG,   # Offset 0x0148 
               DCB_DONT_TOUCH_REG,   # Offset 0x014C 
               DCB_DONT_TOUCH_REG,   # Offset 0x0150 
               DCB_DONT_TOUCH_REG,   # Offset 0x0154 
               DCB_DONT_TOUCH_REG,   # Offset 0x0158 
               DCB_DONT_TOUCH_REG,   # Offset 0x015C 
               DCB_DONT_TOUCH_REG,   # Offset 0x0160 
               DCB_DONT_TOUCH_REG,   # Offset 0x0164 
               DCB_DONT_TOUCH_REG,   # Offset 0x0168 
               DCB_DONT_TOUCH_REG,   # Offset 0x016C 
               DCB_DONT_TOUCH_REG,   # Offset 0x0170 
               DCB_DONT_TOUCH_REG,   # Offset 0x0174 
               DCB_DONT_TOUCH_REG,   # Offset 0x0178 
               DCB_DONT_TOUCH_REG,   # Offset 0x017C 
               DCB_DONT_TOUCH_REG,   # Offset 0x0180 
               DCB_DONT_TOUCH_REG,   # Offset 0x0184 
               DCB_DONT_TOUCH_REG,   # Offset 0x0188 
               DCB_DONT_TOUCH_REG,   # Offset 0x018C 
               DCB_DONT_TOUCH_REG,   # Offset 0x0190 
               DCB_DONT_TOUCH_REG,   # Offset 0x0194 
               DCB_DONT_TOUCH_REG,   # Offset 0x0198 
               DCB_DONT_TOUCH_REG,   # Offset 0x019C 
               DCB_DONT_TOUCH_REG,   # Offset 0x01A0 
               DCB_DONT_TOUCH_REG,   # Offset 0x01A4 
               DCB_DONT_TOUCH_REG,   # Offset 0x01A8 
               DCB_DONT_TOUCH_REG)   # Offset 0x01AC 



#
# Register Defaults
#

ctrl_reg_default = (0xAC010307,   # Offset 0x0000 
                    0x00000000,   # Offset 0x0004 
                    0x00000000,   # Offset 0x0008 
                    0x00000000,   # Offset 0x000C 
                    0x00000000,   # Offset 0x0010 
                    0x00000000,   # Offset 0x0014 
                    0x00000000,   # Offset 0x0018 
                    0x00000000,   # Offset 0x001C 
                    0x00000000,   # Offset 0x0020 
                    0x00000000,   # Offset 0x0024 
                    0x00000000,   # Offset 0x0028 
                    0x00000000,   # Offset 0x002C 
                    0x00000000,   # Offset 0x0030 
                    0xFFFFFFFF,   # Offset 0x0034 
                    0x00000000,   # Offset 0x0038 
                    0x00000000,   # Offset 0x003C 
                    0x00000000,   # Offset 0x0040 
                    0xFFFFC00E,   # Offset 0x0044 
                    0x00000000,   # Offset 0x0048 
                    0x00000000,   # Offset 0x004C 
                    0x00000753,   # Offset 0x0050 
                    0x0001FFFF,   # Offset 0x0054 
                    0x00000000,   # Offset 0x0058 
                    0x00000000,   # Offset 0x005C 
                    0x00000000,   # Offset 0x0060 
                    0x00000000,   # Offset 0x0064 
                    0x00000000,   # Offset 0x0068 
                    0x00000000,   # Offset 0x006C 
                    0x00000000,   # Offset 0x0070 
                    0x00000000,   # Offset 0x0074 
                    0x00000000,   # Offset 0x0078 
                    0x00000000,   # Offset 0x007C 
                    0x00000000,   # Offset 0x0080 
                    0x00000000,   # Offset 0x0084 
                    0x00000000,   # Offset 0x0088 
                    0x00000000,   # Offset 0x008C 
                    0x00000000,   # Offset 0x0090 
                    0x00000000,   # Offset 0x0094 
                    0x00000000,   # Offset 0x0098 
                    0x00000000,   # Offset 0x009C 
                    0x00000000,   # Offset 0x00A0 
                    0x00000000,   # Offset 0x00A4 
                    0x00000000,   # Offset 0x00A8 
                    0x00000000,   # Offset 0x00AC 
                    0x00020100,   # Offset 0x00B0 
                    0x00030101,   # Offset 0x00B4 
                    0x00020102,   # Offset 0x00B8 
                    0x00020103,   # Offset 0x00BC 
                    0x00000104,   # Offset 0x00C0 
                    0x00000105,   # Offset 0x00C4 
                    0x00000106,   # Offset 0x00C8 
                    0x00000107,   # Offset 0x00CC 
                    0x10000908,   # Offset 0x00D0 
                    0xA0022A09,   # Offset 0x00D4 
                    0x0082000B,   # Offset 0x00D8 
                    0x029400AD,   # Offset 0x00DC 
                    0x0830140E,   # Offset 0x00E0 
                    0xE000280F,   # Offset 0x00E4 
                    0x00000000,   # Offset 0x00E8 
                    0x00000000,   # Offset 0x00EC 
                    0x00000000,   # Offset 0x00F0 
                    0x00000000,   # Offset 0x00F4 
                    0x00000000,   # Offset 0x00F8 
                    0x00000000,   # Offset 0x00FC 
                    0x00000000,   # Offset 0x0100 
                    0x00000000,   # Offset 0x0104 
                    0x00000000,   # Offset 0x0108 
                    0x04C4B400,   # Offset 0x010C 
                    0x00000000,   # Offset 0x0110 
                    0x00000000,   # Offset 0x0114 
                    0x00000000,   # Offset 0x0118 
                    0x00000000,   # Offset 0x011C 
                    0x00000000,   # Offset 0x0120 
                    0x00000000,   # Offset 0x0124 
                    0x00000000,   # Offset 0x0128 
                    0x00000000,   # Offset 0x012C 
                    0x00000000,   # Offset 0x0130 
                    0x00000000,   # Offset 0x0134 
                    0x00000000,   # Offset 0x0138 
                    0x00000000,   # Offset 0x013C 
                    0x00000000,   # Offset 0x0140 
                    0x00000000,   # Offset 0x0144 
                    0x00000000,   # Offset 0x0148 
                    0x00000000,   # Offset 0x014C 
                    0x00000000,   # Offset 0x0150 
                    0x00000000,   # Offset 0x0154 
                    0x00000000,   # Offset 0x0158 
                    0x00000000,   # Offset 0x015C 
                    0x00000000,   # Offset 0x0160 
                    0x00000000,   # Offset 0x0164 
                    0x00000000,   # Offset 0x0168 
                    0x00000000,   # Offset 0x016C 
                    0x00000000,   # Offset 0x0170 
                    0x00000000,   # Offset 0x0174 
                    0x00000000,   # Offset 0x0178 
                    0x00000000,   # Offset 0x017C 
                    0x00000000,   # Offset 0x0180 
                    0x00000000,   # Offset 0x0184 
                    0x00000000,   # Offset 0x0188 
                    0x00000000,   # Offset 0x018C 
                    0x00000000,   # Offset 0x0190 
                    0x00000000,   # Offset 0x0194 
                    0x00000000,   # Offset 0x0198 
                    0x00000000,   # Offset 0x019C 
                    0x00000000,   # Offset 0x01A0 
                    0x00000000,   # Offset 0x01A4 
                    0x00000000)   # Offset 0x01A8 


# #############################################################################
# #############################################################################

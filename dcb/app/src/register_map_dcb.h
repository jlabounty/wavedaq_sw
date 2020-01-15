/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  MEGII - DCB
 *
 *  Author  :  schmid_e (Author of generation script)
 *  Created :  15.01.2020 11:16:30
 *
 *  Description :  Register map definitions.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#ifndef __REGISTER_MAP_DCB_H__
#define __REGISTER_MAP_DCB_H__

#ifndef DCB_DONT_INCLUDE_REG_ACCESS_VARS
#include "drv_axi_dcb_reg_bank.h"
#endif

/******************************************************************************/
/* definitions                                                                */
/******************************************************************************/

/*
 * Register Offsets
 */

#define DCB_REG_HW_VER                        0x0000
#define DCB_REG_REG_LAYOUT_VER                0x0004
#define DCB_REG_FW_BUILD_DATE                 0x0008
#define DCB_REG_FW_BUILD_TIME                 0x000C
#define DCB_REG_SW_BUILD_DATE                 0x0010
#define DCB_REG_SW_BUILD_TIME                 0x0014
#define DCB_REG_FW_GIT_HASH_TAG               0x0018
#define DCB_REG_SW_GIT_HASH_TAG               0x001C
#define DCB_REG_PROT_VER                      0x0020
#define DCB_REG_SN                            0x0024
#define DCB_REG_STATUS                        0x0028
#define DCB_REG_TEMP                          0x002C
#define DCB_REG_PLL_LOCK                      0x0030
#define DCB_REG_DCB_LOC                       0x0034
#define DCB_REG_CTRL                          0x0038
#define DCB_REG_SET_CTRL                      0x003C
#define DCB_REG_CLR_CTRL                      0x0040
#define DCB_REG_CLK_CTRL                      0x0044
#define DCB_REG_SET_CLK_CTRL                  0x0048
#define DCB_REG_CLR_CLK_CTRL                  0x004C
#define DCB_REG_COM_CTRL                      0x0050
#define DCB_REG_RST                           0x0054
#define DCB_REG_APLY_CFG                      0x0058
#define DCB_REG_LMK_0                         0x005C
#define DCB_REG_LMK_1                         0x0060
#define DCB_REG_LMK_2                         0x0064
#define DCB_REG_LMK_3                         0x0068
#define DCB_REG_LMK_4                         0x006C
#define DCB_REG_LMK_5                         0x0070
#define DCB_REG_LMK_6                         0x0074
#define DCB_REG_LMK_7                         0x0078
#define DCB_REG_LMK_8                         0x007C
#define DCB_REG_LMK_9                         0x0080
#define DCB_REG_LMK_11                        0x0084
#define DCB_REG_LMK_13                        0x0088
#define DCB_REG_LMK_14                        0x008C
#define DCB_REG_LMK_15                        0x0090
#define DCB_REG_TIME_LSB                      0x0094
#define DCB_REG_TIME_MSB                      0x0098
#define DCB_REG_TIME_LSB_SET                  0x009C
#define DCB_REG_TIME_MSB_SET                  0x00A0
#define DCB_REG_EVENT_TX_RATE                 0x00A4
#define DCB_REG_EVENT_NR                      0x00A8
#define DCB_REG_TRG_CFG                       0x00AC
#define DCB_REG_SET_TRG_CFG                   0x00B0
#define DCB_REG_CLR_TRG_CFG                   0x00B4
#define DCB_REG_TRG_AUTO_PERIOD               0x00B8
#define DCB_REG_TRB_INFO_STAT                 0x00BC
#define DCB_REG_TRB_INFO_LSB                  0x00C0
#define DCB_REG_TRB_INFO_MSB                  0x00C4
#define DCB_REG_LMK_MOD_FLAG                  0x00C8
#define DCB_REG_CRC32_REG_BANK                0x00CC

/*
 * Bit Positions
 */

/* ****** Register 0 [0x0000]: HW_VER - Hardware version information of the PCB (Default: 0xAC010307) ****** */

/* BOARD_MAGIC - 0xAC, Magic number for board identification */
#define DCB_BOARD_MAGIC_REG                         DCB_REG_HW_VER
#define DCB_BOARD_MAGIC_MASK                            0xFF000000
#define DCB_BOARD_MAGIC_OFS                                     24
#define DCB_BOARD_MAGIC_CONST                                 0xAC

/* VENDOR_ID - ID of the board vendor (0x01 for PSI) */
#define DCB_VENDOR_ID_REG                           DCB_REG_HW_VER
#define DCB_VENDOR_ID_MASK                              0x00FF0000
#define DCB_VENDOR_ID_OFS                                       16
#define DCB_VENDOR_ID_CONST                                   0x01

/* BOARD_TYPE - DCB Number (0x03 for DCB ???) */
#define DCB_BOARD_TYPE_REG                          DCB_REG_HW_VER
#define DCB_BOARD_TYPE_MASK                             0x0000FF00
#define DCB_BOARD_TYPE_OFS                                       8
#define DCB_BOARD_TYPE_CONST                                  0x03

/* BOARD_REVISION - Board revision (A=0x00, B=0x01, C=0x02, D=0x03, E=0x04) */
#define DCB_BOARD_REVISION_REG                      DCB_REG_HW_VER
#define DCB_BOARD_REVISION_MASK                         0x000000FC
#define DCB_BOARD_REVISION_OFS                                   2
#define DCB_BOARD_REVISION_CONST                              0x01

/* BOARD_VARIANT - Version indicator pins reflecting the variant of the board (XXX,YYY) */
#define DCB_BOARD_VARIANT_REG                       DCB_REG_HW_VER
#define DCB_BOARD_VARIANT_MASK                          0x00000003
#define DCB_BOARD_VARIANT_OFS                                    0
#define DCB_BOARD_VARIANT_CONST                                0x3



/* ****** Register 1 [0x0004]: REG_LAYOUT_VER - Register map layout version information (Default: 0x00000000) ****** */

/* REG_LAYOUT_COMP_LEVEL - Register map layout compatibility level */
#define DCB_REG_LAYOUT_COMP_LEVEL_REG       DCB_REG_REG_LAYOUT_VER
#define DCB_REG_LAYOUT_COMP_LEVEL_MASK                  0xFFFF0000
#define DCB_REG_LAYOUT_COMP_LEVEL_OFS                           16
#define DCB_REG_LAYOUT_COMP_LEVEL_CONST                     0x0000

/* REG_LAYOUT_VERSION - Register map layout version */
#define DCB_REG_LAYOUT_VERSION_REG          DCB_REG_REG_LAYOUT_VER
#define DCB_REG_LAYOUT_VERSION_MASK                     0x0000FFFF
#define DCB_REG_LAYOUT_VERSION_OFS                               0
#define DCB_REG_LAYOUT_VERSION_CONST                        0x0000



/* ****** Register 2 [0x0008]: FW_BUILD_DATE - Date when the firmware was built (Default: 0x00000000) ****** */

/* FW_BUILD_YEAR - Year of the firmware build */
#define DCB_FW_BUILD_YEAR_REG                DCB_REG_FW_BUILD_DATE
#define DCB_FW_BUILD_YEAR_MASK                          0xFFFF0000
#define DCB_FW_BUILD_YEAR_OFS                                   16

/* FW_BUILD_MONTH - Month of the firmware build */
#define DCB_FW_BUILD_MONTH_REG               DCB_REG_FW_BUILD_DATE
#define DCB_FW_BUILD_MONTH_MASK                         0x0000FF00
#define DCB_FW_BUILD_MONTH_OFS                                   8

/* FW_BUILD_DAY - Day of the firmware build */
#define DCB_FW_BUILD_DAY_REG                 DCB_REG_FW_BUILD_DATE
#define DCB_FW_BUILD_DAY_MASK                           0x000000FF
#define DCB_FW_BUILD_DAY_OFS                                     0



/* ****** Register 3 [0x000C]: FW_BUILD_TIME - Time when the firmware was built and compatibility level (Default: 0x00000000) ****** */

/* FW_COMPAT_LEVEL - Firmware compatibility level */
#define DCB_FW_COMPAT_LEVEL_REG              DCB_REG_FW_BUILD_TIME
#define DCB_FW_COMPAT_LEVEL_MASK                        0xFF000000
#define DCB_FW_COMPAT_LEVEL_OFS                                 24
#define DCB_FW_COMPAT_LEVEL_CONST                             0x00

/* FW_BUILD_HOUR - Hour of the firmware build */
#define DCB_FW_BUILD_HOUR_REG                DCB_REG_FW_BUILD_TIME
#define DCB_FW_BUILD_HOUR_MASK                          0x00FF0000
#define DCB_FW_BUILD_HOUR_OFS                                   16

/* FW_BUILD_MINUTE - Minute of the firmware build */
#define DCB_FW_BUILD_MINUTE_REG              DCB_REG_FW_BUILD_TIME
#define DCB_FW_BUILD_MINUTE_MASK                        0x0000FF00
#define DCB_FW_BUILD_MINUTE_OFS                                  8

/* FW_BUILD_SECOND - Second of the firmware build */
#define DCB_FW_BUILD_SECOND_REG              DCB_REG_FW_BUILD_TIME
#define DCB_FW_BUILD_SECOND_MASK                        0x000000FF
#define DCB_FW_BUILD_SECOND_OFS                                  0



/* ****** Register 4 [0x0010]: SW_BUILD_DATE - Date when the software was built (Default: 0x00000000) ****** */

/* SW_BUILD_YEAR - Year of the software build */
#define DCB_SW_BUILD_YEAR_REG                DCB_REG_SW_BUILD_DATE
#define DCB_SW_BUILD_YEAR_MASK                          0xFFFF0000
#define DCB_SW_BUILD_YEAR_OFS                                   16

/* SW_BUILD_MONTH - Month of the software build */
#define DCB_SW_BUILD_MONTH_REG               DCB_REG_SW_BUILD_DATE
#define DCB_SW_BUILD_MONTH_MASK                         0x0000FF00
#define DCB_SW_BUILD_MONTH_OFS                                   8

/* SW_BUILD_DAY - Day of the software build */
#define DCB_SW_BUILD_DAY_REG                 DCB_REG_SW_BUILD_DATE
#define DCB_SW_BUILD_DAY_MASK                           0x000000FF
#define DCB_SW_BUILD_DAY_OFS                                     0



/* ****** Register 5 [0x0014]: SW_BUILD_TIME - Time when the software was built and compatibility level (Default: 0x00000000) ****** */

/* SW_BUILD_HOUR - Hour of the software build */
#define DCB_SW_BUILD_HOUR_REG                DCB_REG_SW_BUILD_TIME
#define DCB_SW_BUILD_HOUR_MASK                          0x00FF0000
#define DCB_SW_BUILD_HOUR_OFS                                   16

/* SW_BUILD_MINUTE - Minute of the software build */
#define DCB_SW_BUILD_MINUTE_REG              DCB_REG_SW_BUILD_TIME
#define DCB_SW_BUILD_MINUTE_MASK                        0x0000FF00
#define DCB_SW_BUILD_MINUTE_OFS                                  8

/* SW_BUILD_SECOND - Second of the software build */
#define DCB_SW_BUILD_SECOND_REG              DCB_REG_SW_BUILD_TIME
#define DCB_SW_BUILD_SECOND_MASK                        0x000000FF
#define DCB_SW_BUILD_SECOND_OFS                                  0



/* ****** Register 6 [0x0018]: FW_GIT_HASH_TAG - Hash tag of the firmware commit in the GIT repository (Default: 0x00000000) ****** */

/* FW_GIT_HASH_TAG - Hash tag of the firmware commit in the GIT repository */
#define DCB_FW_GIT_HASH_TAG_REG            DCB_REG_FW_GIT_HASH_TAG
#define DCB_FW_GIT_HASH_TAG_MASK                        0xFFFFFFFF
#define DCB_FW_GIT_HASH_TAG_OFS                                  0



/* ****** Register 7 [0x001C]: SW_GIT_HASH_TAG - Hash tag of the software commit in the GIT repository (Default: 0x00000000) ****** */

/* SW_GIT_HASH_TAG - Hash tag of the software commit in the GIT repository */
#define DCB_SW_GIT_HASH_TAG_REG            DCB_REG_SW_GIT_HASH_TAG
#define DCB_SW_GIT_HASH_TAG_MASK                        0xFFFFFFFF
#define DCB_SW_GIT_HASH_TAG_OFS                                  0



/* ****** Register 8 [0x0020]: PROT_VER - Vesion of the WaveDream2 protocol (Default: 0x00000000) ****** */

/* PROTOCOL_VERSION - Version of the WaveDream2 protocol */
#define DCB_PROTOCOL_VERSION_REG                  DCB_REG_PROT_VER
#define DCB_PROTOCOL_VERSION_MASK                       0x000000FF
#define DCB_PROTOCOL_VERSION_OFS                                 0



/* ****** Register 9 [0x0024]: SN - Serial Number of the WD2 Board (Board ID) (Default: 0x00000000) ****** */

/* SERIAL_NUMBER - Serial Number of the WD2 Board (Board ID) */
#define DCB_SERIAL_NUMBER_REG                           DCB_REG_SN
#define DCB_SERIAL_NUMBER_MASK                          0x0000FFFF
#define DCB_SERIAL_NUMBER_OFS                                    0



/* ****** Register 10 [0x0028]: STATUS - Status Register (Default: 0x00000000) ****** */

/* FLASH_SEL - SPI Flash select from backplane (inverted = high active) */
#define DCB_FLASH_SEL_REG                           DCB_REG_STATUS
#define DCB_FLASH_SEL_MASK                              0x00000020
#define DCB_FLASH_SEL_OFS                                        5

/* BOARD_SEL - Board select from backplane (inverted = high active) */
#define DCB_BOARD_SEL_REG                           DCB_REG_STATUS
#define DCB_BOARD_SEL_MASK                              0x00000010
#define DCB_BOARD_SEL_OFS                                        4

/* SERIAL_BUSY - "1" during serial activity like FLASH read/write */
#define DCB_SERIAL_BUSY_REG                         DCB_REG_STATUS
#define DCB_SERIAL_BUSY_MASK                            0x00000004
#define DCB_SERIAL_BUSY_OFS                                      2

/* DCB_BUSY - "1" while dcb is busy */
#define DCB_DCB_BUSY_REG                            DCB_REG_STATUS
#define DCB_DCB_BUSY_MASK                               0x00000002
#define DCB_DCB_BUSY_OFS                                         1

/* SYS_BUSY - Inverted busy signal from backplane (active low) */
#define DCB_SYS_BUSY_REG                            DCB_REG_STATUS
#define DCB_SYS_BUSY_MASK                               0x00000001
#define DCB_SYS_BUSY_OFS                                         0



/* ****** Register 11 [0x002C]: TEMP - Status Register (Default: 0x00000000) ****** */

/* TEMPERATURE - temperature in 0.0625 deg. C units */
#define DCB_TEMPERATURE_REG                           DCB_REG_TEMP
#define DCB_TEMPERATURE_MASK                            0x0000FFFF
#define DCB_TEMPERATURE_OFS                                      0



/* ****** Register 12 [0x0030]: PLL_LOCK - Lock Status of PLLs (Default: 0x00000000) ****** */

/* WDB_CLK_MGR_LOCK - Lock of the clock manager deriving clocks from the WDB clock (e.g. refclk for SYNC output delay) */
#define DCB_WDB_CLK_MGR_LOCK_REG                  DCB_REG_PLL_LOCK
#define DCB_WDB_CLK_MGR_LOCK_MASK                       0x00000004
#define DCB_WDB_CLK_MGR_LOCK_OFS                                 2

/* SYS_DCM_LOCK - Lock of system DCM (FPGA internal) */
#define DCB_SYS_DCM_LOCK_REG                      DCB_REG_PLL_LOCK
#define DCB_SYS_DCM_LOCK_MASK                           0x00000002
#define DCB_SYS_DCM_LOCK_OFS                                     1

/* LMK_PLL_LOCK - PLL lock signal of LMK (external) */
#define DCB_LMK_PLL_LOCK_REG                      DCB_REG_PLL_LOCK
#define DCB_LMK_PLL_LOCK_MASK                           0x00000001
#define DCB_LMK_PLL_LOCK_OFS                                     0



/* ****** Register 13 [0x0034]: DCB_LOC - Location where the WD2 is plugged in (Default: 0xFFFFFFFF) ****** */

/* CRATE_ID - ID of the crate where the current board is plugged in */
#define DCB_CRATE_ID_REG                           DCB_REG_DCB_LOC
#define DCB_CRATE_ID_MASK                               0x00FF0000
#define DCB_CRATE_ID_OFS                                        16

/* SLOT_ID - ID of the slot where the current board is plugged in */
#define DCB_SLOT_ID_REG                            DCB_REG_DCB_LOC
#define DCB_SLOT_ID_MASK                                0x000000FF
#define DCB_SLOT_ID_OFS                                          0



/* ****** Register 14 [0x0038]: CTRL - DCB control register (Default: 0x00000000) ****** */

/* SYNC_DELAY - Output delay of SYNC output to backplane */
#define DCB_SYNC_DELAY_REG                            DCB_REG_CTRL
#define DCB_SYNC_DELAY_MASK                             0x001F0000
#define DCB_SYNC_DELAY_OFS                                      16

/* DAQ_SOFT_TRIGGER - config 0 */
#define DCB_DAQ_SOFT_TRIGGER_REG                      DCB_REG_CTRL
#define DCB_DAQ_SOFT_TRIGGER_MASK                       0x00000001
#define DCB_DAQ_SOFT_TRIGGER_OFS                                 0



/* ****** Register 15 [0x003C]: SET_CTRL - SET bit register for DCB control register (Default: 0x00000000) ****** */

/* SET_BIT_CTRL - See CTRL register */
#define DCB_SET_BIT_CTRL_REG                      DCB_REG_SET_CTRL
#define DCB_SET_BIT_CTRL_MASK                           0xFFFFFFFF
#define DCB_SET_BIT_CTRL_OFS                                     0



/* ****** Register 16 [0x0040]: CLR_CTRL - CLR bit register for DCB control register (Default: 0x00000000) ****** */

/* CLR_BIT_CTRL - See CTRL register */
#define DCB_CLR_BIT_CTRL_REG                      DCB_REG_CLR_CTRL
#define DCB_CLR_BIT_CTRL_MASK                           0xFFFFFFFF
#define DCB_CLR_BIT_CTRL_OFS                                     0



/* ****** Register 17 [0x0044]: CLK_CTRL - Clock Control (Default: 0xFFFFC00E) ****** */

/* DISTRIBUTOR_CLK_OUT_EN - Clock distributor output enable (31:16 = LSK15:0, 15 = TCB, 14 = FPGA, 13:12 = spare) */
#define DCB_DISTRIBUTOR_CLK_OUT_EN_REG            DCB_REG_CLK_CTRL
#define DCB_DISTRIBUTOR_CLK_OUT_EN_MASK                 0xFFFFF000
#define DCB_DISTRIBUTOR_CLK_OUT_EN_OFS                          12

/* DISTRIBUTOR_CLK_SRC_SEL - Backplane clock distributor source select: 0 = external clock / 1 = LMK */
#define DCB_DISTRIBUTOR_CLK_SRC_SEL_REG           DCB_REG_CLK_CTRL
#define DCB_DISTRIBUTOR_CLK_SRC_SEL_MASK                0x00000008
#define DCB_DISTRIBUTOR_CLK_SRC_SEL_OFS                          3

/* BUS_CLK_SRC_SEL - BUS (backplane) clock source select: 0 = LMK output 2 / 1 = AUX_OUT from FPGA (BUS_CLK_SEL) */
#define DCB_BUS_CLK_SRC_SEL_REG                   DCB_REG_CLK_CTRL
#define DCB_BUS_CLK_SRC_SEL_MASK                        0x00000004
#define DCB_BUS_CLK_SRC_SEL_OFS                                  2

/* LMK_CLK_SRC_SEL - LMK clock source select: 0 = external clock / 1 = on board oscillator (CLK_SEL) */
#define DCB_LMK_CLK_SRC_SEL_REG                   DCB_REG_CLK_CTRL
#define DCB_LMK_CLK_SRC_SEL_MASK                        0x00000002
#define DCB_LMK_CLK_SRC_SEL_OFS                                  1

/* EXT_CLK_IN_SEL - External clk input select: 0 = FCI / 1 = MCX connector (CLK_SEL_EXT) */
#define DCB_EXT_CLK_IN_SEL_REG                    DCB_REG_CLK_CTRL
#define DCB_EXT_CLK_IN_SEL_MASK                         0x00000001
#define DCB_EXT_CLK_IN_SEL_OFS                                   0



/* ****** Register 18 [0x0048]: SET_CLK_CTRL - SET bit register for Clock control register (Default: 0x00000000) ****** */

/* SET_BIT_CLK_CTRL - See CLK_CTRL register */
#define DCB_SET_BIT_CLK_CTRL_REG              DCB_REG_SET_CLK_CTRL
#define DCB_SET_BIT_CLK_CTRL_MASK                       0xFFFFFFFF
#define DCB_SET_BIT_CLK_CTRL_OFS                                 0



/* ****** Register 19 [0x004C]: CLR_CLK_CTRL - CLR bit register for Clock control register (Default: 0x00000000) ****** */

/* CLR_BIT_CLK_CTRL - See CLK_CTRL register */
#define DCB_CLR_BIT_CLK_CTRL_REG              DCB_REG_CLR_CLK_CTRL
#define DCB_CLR_BIT_CLK_CTRL_MASK                       0xFFFFFFFF
#define DCB_CLR_BIT_CLK_CTRL_OFS                                 0



/* ****** Register 20 [0x0050]: COM_CTRL - Communication Control Register (Default: 0x00000753) ****** */

/* INTER_PKG_DELAY - Delay between transmission of two UDP packages in 8ns steps */
#define DCB_INTER_PKG_DELAY_REG                   DCB_REG_COM_CTRL
#define DCB_INTER_PKG_DELAY_MASK                        0x00FFFFFF
#define DCB_INTER_PKG_DELAY_OFS                                  0



/* ****** Register 21 [0x0054]: RST - Reset bits for specific firmwar units (Default: 0x00000000) ****** */

/* WDB_CLK_MGR_RST - Reset for clock manager deriving clocks from the WDB clock (e.g. refclk for SYNC output delay) */
#define DCB_WDB_CLK_MGR_RST_REG                        DCB_REG_RST
#define DCB_WDB_CLK_MGR_RST_MASK                        0x00000020
#define DCB_WDB_CLK_MGR_RST_OFS                                  5

/* TRIGGER_MGR_RST - Trigger manager reset */
#define DCB_TRIGGER_MGR_RST_REG                        DCB_REG_RST
#define DCB_TRIGGER_MGR_RST_MASK                        0x00000010
#define DCB_TRIGGER_MGR_RST_OFS                                  4

/* TR_SYNC_BPL - Trigger SYNC signal on the backplane */
#define DCB_TR_SYNC_BPL_REG                            DCB_REG_RST
#define DCB_TR_SYNC_BPL_MASK                            0x00000008
#define DCB_TR_SYNC_BPL_OFS                                      3

/* LMK_SYNC_DCB - Trigger SYNC signal of the LMK on the DCB */
#define DCB_LMK_SYNC_DCB_REG                           DCB_REG_RST
#define DCB_LMK_SYNC_DCB_MASK                           0x00000004
#define DCB_LMK_SYNC_DCB_OFS                                     2

/* DATA_LINK_IF_RST - Reset of the interface between packager and Ethernet/SERDES interface */
#define DCB_DATA_LINK_IF_RST_REG                       DCB_REG_RST
#define DCB_DATA_LINK_IF_RST_MASK                       0x00000002
#define DCB_DATA_LINK_IF_RST_OFS                                 1

/* RECONFIGURE_FPGA - Initiate FPGA Reconfiguration */
#define DCB_RECONFIGURE_FPGA_REG                       DCB_REG_RST
#define DCB_RECONFIGURE_FPGA_MASK                       0x00000001
#define DCB_RECONFIGURE_FPGA_OFS                                 0



/* ****** Register 22 [0x0058]: APLY_CFG - Apply settings from regsiter bank to hardware units (Default: 0x00000000) ****** */

/* APPLY_SETTINGS_LMK - Apply configuration from regsiter bank to LMK */
#define DCB_APPLY_SETTINGS_LMK_REG                DCB_REG_APLY_CFG
#define DCB_APPLY_SETTINGS_LMK_MASK                     0x00000001
#define DCB_APPLY_SETTINGS_LMK_OFS                               0



/* ****** Register 23 [0x005C]: LMK_0 - LMK Register 0 (Default: 0x00020100) ****** */

/* LMK0_RESET - Resets LMK Registers to Their Power-On State */
#define DCB_LMK0_RESET_REG                           DCB_REG_LMK_0
#define DCB_LMK0_RESET_MASK                             0x80000000
#define DCB_LMK0_RESET_OFS                                      31

/* LMK0_CLKOUT_MUX - Channel 0 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed) */
#define DCB_LMK0_CLKOUT_MUX_REG                      DCB_REG_LMK_0
#define DCB_LMK0_CLKOUT_MUX_MASK                        0x00060000
#define DCB_LMK0_CLKOUT_MUX_OFS                                 17

/* LMK0_CLKOUT_EN - Channel 0 Clock Output Enable (0 = Disabled, 1 = Enabled) */
#define DCB_LMK0_CLKOUT_EN_REG                       DCB_REG_LMK_0
#define DCB_LMK0_CLKOUT_EN_MASK                         0x00010000
#define DCB_LMK0_CLKOUT_EN_OFS                                  16

/* LMK0_CLKOUT_DIV - Channel 0 Clock Output Divider (value x 2) (1..255) */
#define DCB_LMK0_CLKOUT_DIV_REG                      DCB_REG_LMK_0
#define DCB_LMK0_CLKOUT_DIV_MASK                        0x0000FF00
#define DCB_LMK0_CLKOUT_DIV_OFS                                  8

/* LMK0_CLKOUT_DLY - Channel 0 Clock Output Delay (value x 150ps) */
#define DCB_LMK0_CLKOUT_DLY_REG                      DCB_REG_LMK_0
#define DCB_LMK0_CLKOUT_DLY_MASK                        0x000000F0
#define DCB_LMK0_CLKOUT_DLY_OFS                                  4



/* ****** Register 24 [0x0060]: LMK_1 - LMK Register 1 (Default: 0x00030101) ****** */

/* LMK1_CLKOUT_MUX - Channel 1 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed) */
#define DCB_LMK1_CLKOUT_MUX_REG                      DCB_REG_LMK_1
#define DCB_LMK1_CLKOUT_MUX_MASK                        0x00060000
#define DCB_LMK1_CLKOUT_MUX_OFS                                 17

/* LMK1_CLKOUT_EN - Channel 1 Clock Output Enable (0 = Disabled, 1 = Enabled) */
#define DCB_LMK1_CLKOUT_EN_REG                       DCB_REG_LMK_1
#define DCB_LMK1_CLKOUT_EN_MASK                         0x00010000
#define DCB_LMK1_CLKOUT_EN_OFS                                  16

/* LMK1_CLKOUT_DIV - Channel 1 Clock Output Divider (value x 2) (1..255) */
#define DCB_LMK1_CLKOUT_DIV_REG                      DCB_REG_LMK_1
#define DCB_LMK1_CLKOUT_DIV_MASK                        0x0000FF00
#define DCB_LMK1_CLKOUT_DIV_OFS                                  8

/* LMK1_CLKOUT_DLY - Channel 1 Clock Output Delay (value x 150ps) */
#define DCB_LMK1_CLKOUT_DLY_REG                      DCB_REG_LMK_1
#define DCB_LMK1_CLKOUT_DLY_MASK                        0x000000F0
#define DCB_LMK1_CLKOUT_DLY_OFS                                  4



/* ****** Register 25 [0x0064]: LMK_2 - LMK Register 2 (Default: 0x00020102) ****** */

/* LMK2_CLKOUT_MUX - Channel 2 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed) */
#define DCB_LMK2_CLKOUT_MUX_REG                      DCB_REG_LMK_2
#define DCB_LMK2_CLKOUT_MUX_MASK                        0x00060000
#define DCB_LMK2_CLKOUT_MUX_OFS                                 17

/* LMK2_CLKOUT_EN - Channel 2 Clock Output Enable (0 = Disabled, 1 = Enabled) */
#define DCB_LMK2_CLKOUT_EN_REG                       DCB_REG_LMK_2
#define DCB_LMK2_CLKOUT_EN_MASK                         0x00010000
#define DCB_LMK2_CLKOUT_EN_OFS                                  16

/* LMK2_CLKOUT_DIV - Channel 2 Clock Output Divider (value x 2) (1..255) */
#define DCB_LMK2_CLKOUT_DIV_REG                      DCB_REG_LMK_2
#define DCB_LMK2_CLKOUT_DIV_MASK                        0x0000FF00
#define DCB_LMK2_CLKOUT_DIV_OFS                                  8

/* LMK2_CLKOUT_DLY - Channel 2 Clock Output Delay (value x 150ps) */
#define DCB_LMK2_CLKOUT_DLY_REG                      DCB_REG_LMK_2
#define DCB_LMK2_CLKOUT_DLY_MASK                        0x000000F0
#define DCB_LMK2_CLKOUT_DLY_OFS                                  4



/* ****** Register 26 [0x0068]: LMK_3 - LMK Register 3 (Default: 0x00020103) ****** */

/* LMK3_CLKOUT_MUX - Channel 3 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed) */
#define DCB_LMK3_CLKOUT_MUX_REG                      DCB_REG_LMK_3
#define DCB_LMK3_CLKOUT_MUX_MASK                        0x00060000
#define DCB_LMK3_CLKOUT_MUX_OFS                                 17

/* LMK3_CLKOUT_EN - Channel 3 Clock Output Enable (0 = Disabled, 1 = Enabled) */
#define DCB_LMK3_CLKOUT_EN_REG                       DCB_REG_LMK_3
#define DCB_LMK3_CLKOUT_EN_MASK                         0x00010000
#define DCB_LMK3_CLKOUT_EN_OFS                                  16

/* LMK3_CLKOUT_DIV - Channel 3 Clock Output Divider (value x 2) (1..255) */
#define DCB_LMK3_CLKOUT_DIV_REG                      DCB_REG_LMK_3
#define DCB_LMK3_CLKOUT_DIV_MASK                        0x0000FF00
#define DCB_LMK3_CLKOUT_DIV_OFS                                  8

/* LMK3_CLKOUT_DLY - Channel 3 Clock Output Delay (value x 150ps) */
#define DCB_LMK3_CLKOUT_DLY_REG                      DCB_REG_LMK_3
#define DCB_LMK3_CLKOUT_DLY_MASK                        0x000000F0
#define DCB_LMK3_CLKOUT_DLY_OFS                                  4



/* ****** Register 27 [0x006C]: LMK_4 - LMK Register 4 (Default: 0x00000104) ****** */

/* LMK4_CLKOUT_MUX - Channel 4 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed) */
#define DCB_LMK4_CLKOUT_MUX_REG                      DCB_REG_LMK_4
#define DCB_LMK4_CLKOUT_MUX_MASK                        0x00060000
#define DCB_LMK4_CLKOUT_MUX_OFS                                 17

/* LMK4_CLKOUT_EN - Channel 4 Clock Output Enable (0 = Disabled, 1 = Enabled) */
#define DCB_LMK4_CLKOUT_EN_REG                       DCB_REG_LMK_4
#define DCB_LMK4_CLKOUT_EN_MASK                         0x00010000
#define DCB_LMK4_CLKOUT_EN_OFS                                  16

/* LMK4_CLKOUT_DIV - Channel 4 Clock Output Divider (value x 2) (1..255) */
#define DCB_LMK4_CLKOUT_DIV_REG                      DCB_REG_LMK_4
#define DCB_LMK4_CLKOUT_DIV_MASK                        0x0000FF00
#define DCB_LMK4_CLKOUT_DIV_OFS                                  8

/* LMK4_CLKOUT_DLY - Channel 4 Clock Output Delay (value x 150ps) */
#define DCB_LMK4_CLKOUT_DLY_REG                      DCB_REG_LMK_4
#define DCB_LMK4_CLKOUT_DLY_MASK                        0x000000F0
#define DCB_LMK4_CLKOUT_DLY_OFS                                  4



/* ****** Register 28 [0x0070]: LMK_5 - LMK Register 5 (Default: 0x00000105) ****** */

/* LMK5_CLKOUT_MUX - Channel 5 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed) */
#define DCB_LMK5_CLKOUT_MUX_REG                      DCB_REG_LMK_5
#define DCB_LMK5_CLKOUT_MUX_MASK                        0x00060000
#define DCB_LMK5_CLKOUT_MUX_OFS                                 17

/* LMK5_CLKOUT_EN - Channel 5 Clock Output Enable (0 = Disabled, 1 = Enabled) */
#define DCB_LMK5_CLKOUT_EN_REG                       DCB_REG_LMK_5
#define DCB_LMK5_CLKOUT_EN_MASK                         0x00010000
#define DCB_LMK5_CLKOUT_EN_OFS                                  16

/* LMK5_CLKOUT_DIV - Channel 5 Clock Output Divider (value x 2) (1..255) */
#define DCB_LMK5_CLKOUT_DIV_REG                      DCB_REG_LMK_5
#define DCB_LMK5_CLKOUT_DIV_MASK                        0x0000FF00
#define DCB_LMK5_CLKOUT_DIV_OFS                                  8

/* LMK5_CLKOUT_DLY - Channel 5 Clock Output Delay (value x 150ps) */
#define DCB_LMK5_CLKOUT_DLY_REG                      DCB_REG_LMK_5
#define DCB_LMK5_CLKOUT_DLY_MASK                        0x000000F0
#define DCB_LMK5_CLKOUT_DLY_OFS                                  4



/* ****** Register 29 [0x0074]: LMK_6 - LMK Register 6 (Default: 0x00000106) ****** */

/* LMK6_CLKOUT_MUX - Channel 6 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed) */
#define DCB_LMK6_CLKOUT_MUX_REG                      DCB_REG_LMK_6
#define DCB_LMK6_CLKOUT_MUX_MASK                        0x00060000
#define DCB_LMK6_CLKOUT_MUX_OFS                                 17

/* LMK6_CLKOUT_EN - Channel 6 Clock Output Enable (0 = Disabled, 1 = Enabled) */
#define DCB_LMK6_CLKOUT_EN_REG                       DCB_REG_LMK_6
#define DCB_LMK6_CLKOUT_EN_MASK                         0x00010000
#define DCB_LMK6_CLKOUT_EN_OFS                                  16

/* LMK6_CLKOUT_DIV - Channel 6 Clock Output Divider (value x 2) (1..255) */
#define DCB_LMK6_CLKOUT_DIV_REG                      DCB_REG_LMK_6
#define DCB_LMK6_CLKOUT_DIV_MASK                        0x0000FF00
#define DCB_LMK6_CLKOUT_DIV_OFS                                  8

/* LMK6_CLKOUT_DLY - Channel 6 Clock Output Delay (value x 150ps) */
#define DCB_LMK6_CLKOUT_DLY_REG                      DCB_REG_LMK_6
#define DCB_LMK6_CLKOUT_DLY_MASK                        0x000000F0
#define DCB_LMK6_CLKOUT_DLY_OFS                                  4



/* ****** Register 30 [0x0078]: LMK_7 - LMK Register 7 (Default: 0x00000107) ****** */

/* LMK7_CLKOUT_MUX - Channel 7 Clock Output Multiplexer (0=bypass, 1=divided, 2=delayed, 3=divided&delayed) */
#define DCB_LMK7_CLKOUT_MUX_REG                      DCB_REG_LMK_7
#define DCB_LMK7_CLKOUT_MUX_MASK                        0x00060000
#define DCB_LMK7_CLKOUT_MUX_OFS                                 17

/* LMK7_CLKOUT_EN - Channel 7 Clock Output Enable (0 = Disabled, 1 = Enabled) */
#define DCB_LMK7_CLKOUT_EN_REG                       DCB_REG_LMK_7
#define DCB_LMK7_CLKOUT_EN_MASK                         0x00010000
#define DCB_LMK7_CLKOUT_EN_OFS                                  16

/* LMK7_CLKOUT_DIV - Channel 7 Clock Output Divider (value x 2) (1..255) */
#define DCB_LMK7_CLKOUT_DIV_REG                      DCB_REG_LMK_7
#define DCB_LMK7_CLKOUT_DIV_MASK                        0x0000FF00
#define DCB_LMK7_CLKOUT_DIV_OFS                                  8

/* LMK7_CLKOUT_DLY - Channel 7 Clock Output Delay (value x 150ps) */
#define DCB_LMK7_CLKOUT_DLY_REG                      DCB_REG_LMK_7
#define DCB_LMK7_CLKOUT_DLY_MASK                        0x000000F0
#define DCB_LMK7_CLKOUT_DLY_OFS                                  4



/* ****** Register 31 [0x007C]: LMK_8 - LMK Register 8 (Default: 0x10000908) ****** */

/* LMK8_PHASE_NOISE_OPT - Set LMK Register 8 (Phase Noise Optimization) */
#define DCB_LMK8_PHASE_NOISE_OPT_REG                 DCB_REG_LMK_8
#define DCB_LMK8_PHASE_NOISE_OPT_MASK                   0xFFFFFFF0
#define DCB_LMK8_PHASE_NOISE_OPT_OFS                             4



/* ****** Register 32 [0x0080]: LMK_9 - LMK Register 9 (Default: 0xA0022A09) ****** */

/* LMK9_VBOOST - Voltage Level Boost for Clock Outputs */
#define DCB_LMK9_VBOOST_REG                          DCB_REG_LMK_9
#define DCB_LMK9_VBOOST_MASK                            0x00010000
#define DCB_LMK9_VBOOST_OFS                                     16



/* ****** Register 33 [0x0084]: LMK_11 - LMK Register 11 (Default: 0x0082000B) ****** */

/* LMK11_DIV4 - Divider Enable for Digital Lock Detect Circuit */
#define DCB_LMK11_DIV4_REG                          DCB_REG_LMK_11
#define DCB_LMK11_DIV4_MASK                             0x00008000
#define DCB_LMK11_DIV4_OFS                                      15



/* ****** Register 34 [0x0088]: LMK_13 - LMK Register 13 (Default: 0x029400AD) ****** */

/* LMK13_OSCIN_FREQ - Oscillator Input Calibration Adjustment in MHz (1..200) */
#define DCB_LMK13_OSCIN_FREQ_REG                    DCB_REG_LMK_13
#define DCB_LMK13_OSCIN_FREQ_MASK                       0x003FC000
#define DCB_LMK13_OSCIN_FREQ_OFS                                14

/* LMK13_VCO_R4_LF - Value for Internal Loop Filter Resistor R4 (0..4) (see datasheet) */
#define DCB_LMK13_VCO_R4_LF_REG                     DCB_REG_LMK_13
#define DCB_LMK13_VCO_R4_LF_MASK                        0x00003800
#define DCB_LMK13_VCO_R4_LF_OFS                                 11

/* LMK13_VCO_R3_LF - Value for Internal Loop Filter Resistor R3 (0..4) (see datasheet) */
#define DCB_LMK13_VCO_R3_LF_REG                     DCB_REG_LMK_13
#define DCB_LMK13_VCO_R3_LF_MASK                        0x00000700
#define DCB_LMK13_VCO_R3_LF_OFS                                  8

/* LMK13_VCO_C3_C4_LF - Value for Internal Loop Filter Capacitors C3/C4 (0..11) (see ds) */
#define DCB_LMK13_VCO_C3_C4_LF_REG                  DCB_REG_LMK_13
#define DCB_LMK13_VCO_C3_C4_LF_MASK                     0x000000F0
#define DCB_LMK13_VCO_C3_C4_LF_OFS                               4



/* ****** Register 35 [0x008C]: LMK_14 - LMK Register 14 (Default: 0x0830140E) ****** */

/* LMK14_EN_FOUT - Enable for the Fout Pin (0 = Disabled, 1 = Enabled) */
#define DCB_LMK14_EN_FOUT_REG                       DCB_REG_LMK_14
#define DCB_LMK14_EN_FOUT_MASK                          0x10000000
#define DCB_LMK14_EN_FOUT_OFS                                   28

/* LMK14_EN_CLKOUT_GLOBAL - Global Clock Output Enable (0 = All Off, 1 = Normal Operation) */
#define DCB_LMK14_EN_CLKOUT_GLOBAL_REG              DCB_REG_LMK_14
#define DCB_LMK14_EN_CLKOUT_GLOBAL_MASK                 0x08000000
#define DCB_LMK14_EN_CLKOUT_GLOBAL_OFS                          27

/* LMK14_POWERDOWN - Powerdown (0 = Normal Operation, 1 = Device Powered Down) */
#define DCB_LMK14_POWERDOWN_REG                     DCB_REG_LMK_14
#define DCB_LMK14_POWERDOWN_MASK                        0x04000000
#define DCB_LMK14_POWERDOWN_OFS                                 26

/* LMK14_PLL_MUX - Output Mode of  LD Pin (0..7,9,11) */
#define DCB_LMK14_PLL_MUX_REG                       DCB_REG_LMK_14
#define DCB_LMK14_PLL_MUX_MASK                          0x00F00000
#define DCB_LMK14_PLL_MUX_OFS                                   20

/* LMK14_PLL_R - PLL R Divider Value (1..4095) */
#define DCB_LMK14_PLL_R_REG                         DCB_REG_LMK_14
#define DCB_LMK14_PLL_R_MASK                            0x000FFF00
#define DCB_LMK14_PLL_R_OFS                                      8



/* ****** Register 36 [0x0090]: LMK_15 - LMK Register 15 (Default: 0xE000280F) ****** */

/* LMK15_PLL_CP_GAIN - PLL Charge Pump Gain (see datasheet) (0..4) */
#define DCB_LMK15_PLL_CP_GAIN_REG                   DCB_REG_LMK_15
#define DCB_LMK15_PLL_CP_GAIN_MASK                      0xC0000000
#define DCB_LMK15_PLL_CP_GAIN_OFS                               30

/* LMK15_VCO_DIV - VCO Divider Value (2..8) */
#define DCB_LMK15_VCO_DIV_REG                       DCB_REG_LMK_15
#define DCB_LMK15_VCO_DIV_MASK                          0x3C000000
#define DCB_LMK15_VCO_DIV_OFS                                   26

/* LMK15_PLL_N - PLL N Divider Value (1..0x3FFFF) */
#define DCB_LMK15_PLL_N_REG                         DCB_REG_LMK_15
#define DCB_LMK15_PLL_N_MASK                            0x03FFFF00
#define DCB_LMK15_PLL_N_OFS                                      8



/* ****** Register 37 [0x0094]: TIME_LSB - Current System Time (Default: 0x00000000) ****** */

/* TIME_LSB - LSBs of 64bit system time counter (MSBs are latched upon read of LSB register) */
#define DCB_TIME_LSB_REG                          DCB_REG_TIME_LSB
#define DCB_TIME_LSB_MASK                               0xFFFFFFFF
#define DCB_TIME_LSB_OFS                                         0



/* ****** Register 38 [0x0098]: TIME_MSB - Current System Time (Default: 0x00000000) ****** */

/* TIME_MSB - MSBs of 64bit system time counter (latched upon read of LSB register) */
#define DCB_TIME_MSB_REG                          DCB_REG_TIME_MSB
#define DCB_TIME_MSB_MASK                               0xFFFFFFFF
#define DCB_TIME_MSB_OFS                                         0



/* ****** Register 39 [0x009C]: TIME_LSB_SET - Set System Time (Default: 0x00000000) ****** */

/* TIME_LSB_SET - LSBs of 64bit system time counter set value  (time is updated when MSBs are written) */
#define DCB_TIME_LSB_SET_REG                  DCB_REG_TIME_LSB_SET
#define DCB_TIME_LSB_SET_MASK                           0xFFFFFFFF
#define DCB_TIME_LSB_SET_OFS                                     0



/* ****** Register 40 [0x00A0]: TIME_MSB_SET - Set System Time (Default: 0x00000000) ****** */

/* TIME_MSB_SET - MSBs of 64bit system time counter set value  (time is updated when MSBs are written) */
#define DCB_TIME_MSB_SET_REG                  DCB_REG_TIME_MSB_SET
#define DCB_TIME_MSB_SET_MASK                           0xFFFFFFFF
#define DCB_TIME_MSB_SET_OFS                                     0



/* ****** Register 41 [0x00A4]: EVENT_TX_RATE - Event Transmission Rate (Default: 0x00000000) ****** */

/* EVENT_TX_RATE - Number of events transmitted per second */
#define DCB_EVENT_TX_RATE_REG                DCB_REG_EVENT_TX_RATE
#define DCB_EVENT_TX_RATE_MASK                          0xFFFFFFFF
#define DCB_EVENT_TX_RATE_OFS                                    0



/* ****** Register 42 [0x00A8]: EVENT_NR - Number of latest event (Default: 0x00000000) ****** */

/* EVENT_NUMBER - Number of latest event */
#define DCB_EVENT_NUMBER_REG                      DCB_REG_EVENT_NR
#define DCB_EVENT_NUMBER_MASK                           0xFFFFFFFF
#define DCB_EVENT_NUMBER_OFS                                     0



/* ****** Register 43 [0x00AC]: TRG_CFG - Trigger Configuration (Default: 0x00000000) ****** */

/* EXT_TRIGGER_OUT_ENABLE - Enable output of trigger signal to MCX connector */
#define DCB_EXT_TRIGGER_OUT_ENABLE_REG             DCB_REG_TRG_CFG
#define DCB_EXT_TRIGGER_OUT_ENABLE_MASK                 0x00000004
#define DCB_EXT_TRIGGER_OUT_ENABLE_OFS                           2

/* ENABLE_AUTO_TRIGGER - Enable generation of automatic periodic trigger to backplane */
#define DCB_ENABLE_AUTO_TRIGGER_REG                DCB_REG_TRG_CFG
#define DCB_ENABLE_AUTO_TRIGGER_MASK                    0x00000002
#define DCB_ENABLE_AUTO_TRIGGER_OFS                              1

/* MANUAL_TRIGGER - Generate trigger pulse on backplane */
#define DCB_MANUAL_TRIGGER_REG                     DCB_REG_TRG_CFG
#define DCB_MANUAL_TRIGGER_MASK                         0x00000001
#define DCB_MANUAL_TRIGGER_OFS                                   0



/* ****** Register 44 [0x00B0]: SET_TRG_CFG - SET bit register for Trigger configuration register (Default: 0x00000000) ****** */

/* SET_BIT_TRG_CFG - See TRG_CFG register */
#define DCB_SET_BIT_TRG_CFG_REG                DCB_REG_SET_TRG_CFG
#define DCB_SET_BIT_TRG_CFG_MASK                        0xFFFFFFFF
#define DCB_SET_BIT_TRG_CFG_OFS                                  0



/* ****** Register 45 [0x00B4]: CLR_TRG_CFG - CLR bit register for Trigger configuration register (Default: 0x00000000) ****** */

/* CLR_BIT_TRG_CFG - See TRG_CFG register */
#define DCB_CLR_BIT_TRG_CFG_REG                DCB_REG_CLR_TRG_CFG
#define DCB_CLR_BIT_TRG_CFG_MASK                        0xFFFFFFFF
#define DCB_CLR_BIT_TRG_CFG_OFS                                  0



/* ****** Register 46 [0x00B8]: TRG_AUTO_PERIOD - Automatic Trigger Period (Default: 0x04C4B400) ****** */

/* AUTO_TRIGGER_PERIOD - Period of automatic trigger in ticks of the DAQ clock */
#define DCB_AUTO_TRIGGER_PERIOD_REG        DCB_REG_TRG_AUTO_PERIOD
#define DCB_AUTO_TRIGGER_PERIOD_MASK                    0xFFFFFFFF
#define DCB_AUTO_TRIGGER_PERIOD_OFS                              0



/* ****** Register 47 [0x00BC]: TRB_INFO_STAT - Trigger Information via Serial Trigger Bus Status (Default: 0x00000000) ****** */

/* TRB_FLAG_NEW - Flag signalling that the current trigger information belongs to the latest trigger received */
#define DCB_TRB_FLAG_NEW_REG                 DCB_REG_TRB_INFO_STAT
#define DCB_TRB_FLAG_NEW_MASK                           0x80000000
#define DCB_TRB_FLAG_NEW_OFS                                    31

/* TRB_FLAG_PARITY_ERROR - Parity error flag of the current trigger information */
#define DCB_TRB_FLAG_PARITY_ERROR_REG        DCB_REG_TRB_INFO_STAT
#define DCB_TRB_FLAG_PARITY_ERROR_MASK                  0x40000000
#define DCB_TRB_FLAG_PARITY_ERROR_OFS                           30

/* TRB_PARITY_ERROR_COUNT - Parity error count of the serial transmission */
#define DCB_TRB_PARITY_ERROR_COUNT_REG       DCB_REG_TRB_INFO_STAT
#define DCB_TRB_PARITY_ERROR_COUNT_MASK                 0x0000FFFF
#define DCB_TRB_PARITY_ERROR_COUNT_OFS                           0



/* ****** Register 48 [0x00C0]: TRB_INFO_LSB - Trigger Information via Serial Trigger Bus LSBs (Default: 0x00000000) ****** */

/* TRB_INFO_LSB - Trigger information LSBs */
#define DCB_TRB_INFO_LSB_REG                  DCB_REG_TRB_INFO_LSB
#define DCB_TRB_INFO_LSB_MASK                           0xFFFFFFFF
#define DCB_TRB_INFO_LSB_OFS                                     0



/* ****** Register 49 [0x00C4]: TRB_INFO_MSB - Trigger Information via Serial Trigger Bus MSBs (Default: 0x00000000) ****** */

/* TRB_INFO_MSB - Trigger information MSBs */
#define DCB_TRB_INFO_MSB_REG                  DCB_REG_TRB_INFO_MSB
#define DCB_TRB_INFO_MSB_MASK                           0x0000FFFF
#define DCB_TRB_INFO_MSB_OFS                                     0



/* ****** Register 50 [0x00C8]: LMK_MOD_FLAG - Set if LMK configuraiton registers are modified (Default: 0x00000000) ****** */

/* LMK_7_MOD - LMK channel 7 register modified flags */
#define DCB_LMK_7_MOD_REG                     DCB_REG_LMK_MOD_FLAG
#define DCB_LMK_7_MOD_MASK                              0x00000080
#define DCB_LMK_7_MOD_OFS                                        7

/* LMK_6_MOD - LMK channel 6 register modified flags */
#define DCB_LMK_6_MOD_REG                     DCB_REG_LMK_MOD_FLAG
#define DCB_LMK_6_MOD_MASK                              0x00000040
#define DCB_LMK_6_MOD_OFS                                        6

/* LMK_5_MOD - LMK channel 5 register modified flags */
#define DCB_LMK_5_MOD_REG                     DCB_REG_LMK_MOD_FLAG
#define DCB_LMK_5_MOD_MASK                              0x00000020
#define DCB_LMK_5_MOD_OFS                                        5

/* LMK_4_MOD - LMK channel 4 register modified flags */
#define DCB_LMK_4_MOD_REG                     DCB_REG_LMK_MOD_FLAG
#define DCB_LMK_4_MOD_MASK                              0x00000010
#define DCB_LMK_4_MOD_OFS                                        4

/* LMK_3_MOD - LMK channel 3 register modified flags */
#define DCB_LMK_3_MOD_REG                     DCB_REG_LMK_MOD_FLAG
#define DCB_LMK_3_MOD_MASK                              0x00000008
#define DCB_LMK_3_MOD_OFS                                        3

/* LMK_2_MOD - LMK channel 2 register modified flags */
#define DCB_LMK_2_MOD_REG                     DCB_REG_LMK_MOD_FLAG
#define DCB_LMK_2_MOD_MASK                              0x00000004
#define DCB_LMK_2_MOD_OFS                                        2

/* LMK_1_MOD - LMK channel 1 register modified flags */
#define DCB_LMK_1_MOD_REG                     DCB_REG_LMK_MOD_FLAG
#define DCB_LMK_1_MOD_MASK                              0x00000002
#define DCB_LMK_1_MOD_OFS                                        1

/* LMK_0_MOD - LMK Register 0 modified flags */
#define DCB_LMK_0_MOD_REG                     DCB_REG_LMK_MOD_FLAG
#define DCB_LMK_0_MOD_MASK                              0x00000001
#define DCB_LMK_0_MOD_OFS                                        0



/* ****** Register 51 [0x00CC]: CRC32_REG_BANK - CRC32 Checksum of Register Bank Content (Default: 0x00000000) ****** */

/* CRC32_REG_BANK - Keep at the end of the register bank */
#define DCB_CRC32_REG_BANK_REG              DCB_REG_CRC32_REG_BANK
#define DCB_CRC32_REG_BANK_MASK                         0xFFFFFFFF
#define DCB_CRC32_REG_BANK_OFS                                   0


/*
 * Number of Registers
 */

#define NR_OF_REGS          52

#ifndef DCB_DONT_INCLUDE_REG_ACCESS_VARS

typedef unsigned int (*dcb_reg_func)(unsigned int, unsigned int, unsigned int, unsigned int);

typedef struct
{
  dcb_reg_func  func;
  unsigned int par;
} dcb_reg_func_type;

extern const dcb_reg_func_type  dcb_reg_func_list[];

#endif /* DCB_DONT_INCLUDE_REG_ACCESS_VARS */

#ifndef DCB_DONT_INCLUDE_VARS

typedef struct {
  const char * name;
  const unsigned int reg;
  const unsigned int read_only;
} dcb_reg_entry_type;


typedef struct {
  const char * name;
  const unsigned int reg;
  const unsigned int mask;
  const unsigned int ofs;
} dcb_bit_group_entry_type;

extern const dcb_reg_entry_type  dcb_reg_list[];
extern const dcb_bit_group_entry_type  dcb_bit_group_list[];
extern const unsigned char reg_restore[];
extern const unsigned int reg_default[];

#define DCB_WRITABLE_REG     0
#define DCB_READONLY_REG     1

#define DCB_DONT_TOUCH_REG   0
#define DCB_RESTORE_REG      1

#endif /* DCB_DONT_INCLUDE_VARS */


/******************************************************************************/

#endif /* __REGISTER_MAP_DCB_H__ */

/******************************************************************************/

/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  MEGII - DCB
 *
 *  Author  :  schmid_e (Author of generation script)
 *  Created :  20.05.2021 11:27:05
 *
 *  Description :  Register map definitions.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#include "register_map_dcb.h"

#ifndef DCB_DONT_INCLUDE_REG_ACCESS_VARS


const dcb_reg_func_type  dcb_reg_func_list[] = {
  { dcb_hw_reg         , 0 },   /* register 0 [0x0000]: HW_VER */
  { dcb_hw_reg         , 0 },   /* register 1 [0x0004]: REG_LAYOUT_VER */
  { dcb_hw_reg         , 0 },   /* register 2 [0x0008]: FW_BUILD_DATE */
  { dcb_hw_reg         , 0 },   /* register 3 [0x000C]: FW_BUILD_TIME */
  { dcb_hw_reg         , 0 },   /* register 4 [0x0010]: SW_BUILD_DATE */
  { dcb_hw_reg         , 0 },   /* register 5 [0x0014]: SW_BUILD_TIME */
  { dcb_hw_reg         , 0 },   /* register 6 [0x0018]: FW_GIT_HASH_TAG */
  { dcb_hw_reg         , 0 },   /* register 7 [0x001C]: SW_GIT_HASH_TAG */
  { dcb_hw_reg         , 0 },   /* register 8 [0x0020]: PROT_VER */
  { dcb_hw_reg         , 0 },   /* register 9 [0x0024]: SN */
  { dcb_hw_reg         , 0 },   /* register 10 [0x0028]: STATUS */
  { dcb_hw_reg         , 0 },   /* register 11 [0x002C]: TEMP */
  { dcb_hw_reg         , 0 },   /* register 12 [0x0030]: PLL_LOCK */
  { dcb_hw_reg         , 0 },   /* register 13 [0x0034]: DCB_LOC */
  { dcb_hw_reg         , 0 },   /* register 14 [0x0038]: CTRL */
  { dcb_hw_reg         , 0 },   /* register 15 [0x003C]: SET_CTRL */
  { dcb_hw_reg         , 0 },   /* register 16 [0x0040]: CLR_CTRL */
  { dcb_hw_reg         , 0 },   /* register 17 [0x0044]: CLK_CTRL */
  { dcb_hw_reg         , 0 },   /* register 18 [0x0048]: SET_CLK_CTRL */
  { dcb_hw_reg         , 0 },   /* register 19 [0x004C]: CLR_CLK_CTRL */
  { dcb_hw_reg         , 0 },   /* register 20 [0x0050]: COM_CTRL */
  { dcb_sw_slot_en_reg , 0 },   /* register 21 [0x0054]: DPS_CTRL */
  { dcb_hw_reg         , 0 },   /* register 22 [0x0058]: RST */
  { dcb_hw_reg         , 0 },   /* register 23 [0x005C]: SERDES_STATUS_00_07 */
  { dcb_hw_reg         , 0 },   /* register 24 [0x0060]: SERDES_STATUS_08_15 */
  { dcb_hw_reg         , 0 },   /* register 25 [0x0064]: SERDES_STATUS_17 */
  { dcb_hw_reg         , 0 },   /* register 26 [0x0068]: SERDES_ERR_CNT_00 */
  { dcb_hw_reg         , 0 },   /* register 27 [0x006C]: SERDES_ERR_CNT_01 */
  { dcb_hw_reg         , 0 },   /* register 28 [0x0070]: SERDES_ERR_CNT_02 */
  { dcb_hw_reg         , 0 },   /* register 29 [0x0074]: SERDES_ERR_CNT_03 */
  { dcb_hw_reg         , 0 },   /* register 30 [0x0078]: SERDES_ERR_CNT_04 */
  { dcb_hw_reg         , 0 },   /* register 31 [0x007C]: SERDES_ERR_CNT_05 */
  { dcb_hw_reg         , 0 },   /* register 32 [0x0080]: SERDES_ERR_CNT_06 */
  { dcb_hw_reg         , 0 },   /* register 33 [0x0084]: SERDES_ERR_CNT_07 */
  { dcb_hw_reg         , 0 },   /* register 34 [0x0088]: SERDES_ERR_CNT_08 */
  { dcb_hw_reg         , 0 },   /* register 35 [0x008C]: SERDES_ERR_CNT_09 */
  { dcb_hw_reg         , 0 },   /* register 36 [0x0090]: SERDES_ERR_CNT_10 */
  { dcb_hw_reg         , 0 },   /* register 37 [0x0094]: SERDES_ERR_CNT_11 */
  { dcb_hw_reg         , 0 },   /* register 38 [0x0098]: SERDES_ERR_CNT_12 */
  { dcb_hw_reg         , 0 },   /* register 39 [0x009C]: SERDES_ERR_CNT_13 */
  { dcb_hw_reg         , 0 },   /* register 40 [0x00A0]: SERDES_ERR_CNT_14 */
  { dcb_hw_reg         , 0 },   /* register 41 [0x00A4]: SERDES_ERR_CNT_15 */
  { dcb_hw_reg         , 0 },   /* register 42 [0x00A8]: SERDES_ERR_CNT_17 */
  { dcb_hw_reg         , 0 },   /* register 43 [0x00AC]: APLY_CFG */
  { dcb_hw_reg         , 0 },   /* register 44 [0x00B0]: LMK_0 */
  { dcb_hw_reg         , 0 },   /* register 45 [0x00B4]: LMK_1 */
  { dcb_hw_reg         , 0 },   /* register 46 [0x00B8]: LMK_2 */
  { dcb_hw_reg         , 0 },   /* register 47 [0x00BC]: LMK_3 */
  { dcb_hw_reg         , 0 },   /* register 48 [0x00C0]: LMK_4 */
  { dcb_hw_reg         , 0 },   /* register 49 [0x00C4]: LMK_5 */
  { dcb_hw_reg         , 0 },   /* register 50 [0x00C8]: LMK_6 */
  { dcb_hw_reg         , 0 },   /* register 51 [0x00CC]: LMK_7 */
  { dcb_hw_reg         , 0 },   /* register 52 [0x00D0]: LMK_8 */
  { dcb_hw_reg         , 0 },   /* register 53 [0x00D4]: LMK_9 */
  { dcb_hw_reg         , 0 },   /* register 54 [0x00D8]: LMK_11 */
  { dcb_hw_reg         , 0 },   /* register 55 [0x00DC]: LMK_13 */
  { dcb_hw_reg         , 0 },   /* register 56 [0x00E0]: LMK_14 */
  { dcb_hw_reg         , 0 },   /* register 57 [0x00E4]: LMK_15 */
  { dcb_hw_reg         , 0 },   /* register 58 [0x00E8]: TIME_LSB */
  { dcb_hw_reg         , 0 },   /* register 59 [0x00EC]: TIME_MSB */
  { dcb_hw_reg         , 0 },   /* register 60 [0x00F0]: TIME_LSB_SET */
  { dcb_hw_reg         , 0 },   /* register 61 [0x00F4]: TIME_MSB_SET */
  { dcb_hw_reg         , 0 },   /* register 62 [0x00F8]: EVENT_TX_RATE */
  { dcb_hw_reg         , 0 },   /* register 63 [0x00FC]: EVENT_NR */
  { dcb_hw_reg         , 0 },   /* register 64 [0x0100]: TRG_CFG */
  { dcb_hw_reg         , 0 },   /* register 65 [0x0104]: SET_TRG_CFG */
  { dcb_hw_reg         , 0 },   /* register 66 [0x0108]: CLR_TRG_CFG */
  { dcb_hw_reg         , 0 },   /* register 67 [0x010C]: TRG_AUTO_PERIOD */
  { dcb_hw_reg         , 0 },   /* register 68 [0x0110]: TRB_INFO_STAT */
  { dcb_hw_reg         , 0 },   /* register 69 [0x0114]: TRB_INFO_LSB */
  { dcb_hw_reg         , 0 },   /* register 70 [0x0118]: TRB_INFO_MSB */
  { dcb_hw_reg         , 0 },   /* register 71 [0x011C]: LMK_MOD_FLAG */
  { cmb_mscb_adr_reg   , 0 },   /* register 72 [0x0120]: CMB_MSCB_ADR */
  { dcb_hw_reg         , 0 },   /* register 73 [0x0124]: SD_PKT_CNT_0 */
  { dcb_hw_reg         , 0 },   /* register 74 [0x0128]: SD_PKT_CNT_1 */
  { dcb_hw_reg         , 0 },   /* register 75 [0x012C]: SD_PKT_CNT_2 */
  { dcb_hw_reg         , 0 },   /* register 76 [0x0130]: SD_PKT_CNT_3 */
  { dcb_hw_reg         , 0 },   /* register 77 [0x0134]: SD_PKT_CNT_4 */
  { dcb_hw_reg         , 0 },   /* register 78 [0x0138]: SD_PKT_CNT_5 */
  { dcb_hw_reg         , 0 },   /* register 79 [0x013C]: SD_PKT_CNT_6 */
  { dcb_hw_reg         , 0 },   /* register 80 [0x0140]: SD_PKT_CNT_7 */
  { dcb_hw_reg         , 0 },   /* register 81 [0x0144]: SD_PKT_CNT_8 */
  { dcb_hw_reg         , 0 },   /* register 82 [0x0148]: SD_PKT_CNT_9 */
  { dcb_hw_reg         , 0 },   /* register 83 [0x014C]: SD_PKT_CNT_10 */
  { dcb_hw_reg         , 0 },   /* register 84 [0x0150]: SD_PKT_CNT_11 */
  { dcb_hw_reg         , 0 },   /* register 85 [0x0154]: SD_PKT_CNT_12 */
  { dcb_hw_reg         , 0 },   /* register 86 [0x0158]: SD_PKT_CNT_13 */
  { dcb_hw_reg         , 0 },   /* register 87 [0x015C]: SD_PKT_CNT_14 */
  { dcb_hw_reg         , 0 },   /* register 88 [0x0160]: SD_PKT_CNT_15 */
  { dcb_hw_reg         , 0 },   /* register 89 [0x0164]: SD_PKT_CNT_17 */
  { dcb_hw_reg         , 0 }    /* register 90 [0x0168]: CRC32_REG_BANK */
};

#endif /* DCB_DONT_INCLUDE_REG_ACCESS_VARS */

#ifndef DCB_DONT_INCLUDE_VARS

/******************************************************************************/
/* Register Mapping                                                           */
/******************************************************************************/

const dcb_reg_entry_type  dcb_reg_list[] = {
  { "HW_VER"              , DCB_REG_HW_VER             , DCB_READONLY_REG },
  { "REG_LAYOUT_VER"      , DCB_REG_REG_LAYOUT_VER     , DCB_READONLY_REG },
  { "FW_BUILD_DATE"       , DCB_REG_FW_BUILD_DATE      , DCB_READONLY_REG },
  { "FW_BUILD_TIME"       , DCB_REG_FW_BUILD_TIME      , DCB_READONLY_REG },
  { "SW_BUILD_DATE"       , DCB_REG_SW_BUILD_DATE      , DCB_WRITABLE_REG },
  { "SW_BUILD_TIME"       , DCB_REG_SW_BUILD_TIME      , DCB_WRITABLE_REG },
  { "FW_GIT_HASH_TAG"     , DCB_REG_FW_GIT_HASH_TAG    , DCB_READONLY_REG },
  { "SW_GIT_HASH_TAG"     , DCB_REG_SW_GIT_HASH_TAG    , DCB_WRITABLE_REG },
  { "PROT_VER"            , DCB_REG_PROT_VER           , DCB_WRITABLE_REG },
  { "SN"                  , DCB_REG_SN                 , DCB_WRITABLE_REG },
  { "STATUS"              , DCB_REG_STATUS             , DCB_READONLY_REG },
  { "TEMP"                , DCB_REG_TEMP               , DCB_WRITABLE_REG },
  { "PLL_LOCK"            , DCB_REG_PLL_LOCK           , DCB_READONLY_REG },
  { "DCB_LOC"             , DCB_REG_DCB_LOC            , DCB_WRITABLE_REG },
  { "CTRL"                , DCB_REG_CTRL               , DCB_WRITABLE_REG },
  { "SET_CTRL"            , DCB_REG_SET_CTRL           , DCB_WRITABLE_REG },
  { "CLR_CTRL"            , DCB_REG_CLR_CTRL           , DCB_WRITABLE_REG },
  { "CLK_CTRL"            , DCB_REG_CLK_CTRL           , DCB_WRITABLE_REG },
  { "SET_CLK_CTRL"        , DCB_REG_SET_CLK_CTRL       , DCB_WRITABLE_REG },
  { "CLR_CLK_CTRL"        , DCB_REG_CLR_CLK_CTRL       , DCB_WRITABLE_REG },
  { "COM_CTRL"            , DCB_REG_COM_CTRL           , DCB_WRITABLE_REG },
  { "DPS_CTRL"            , DCB_REG_DPS_CTRL           , DCB_WRITABLE_REG },
  { "RST"                 , DCB_REG_RST                , DCB_WRITABLE_REG },
  { "SERDES_STATUS_00_07" , DCB_REG_SERDES_STATUS_00_07, DCB_READONLY_REG },
  { "SERDES_STATUS_08_15" , DCB_REG_SERDES_STATUS_08_15, DCB_READONLY_REG },
  { "SERDES_STATUS_17"    , DCB_REG_SERDES_STATUS_17   , DCB_READONLY_REG },
  { "SERDES_ERR_CNT_00"   , DCB_REG_SERDES_ERR_CNT_00  , DCB_READONLY_REG },
  { "SERDES_ERR_CNT_01"   , DCB_REG_SERDES_ERR_CNT_01  , DCB_READONLY_REG },
  { "SERDES_ERR_CNT_02"   , DCB_REG_SERDES_ERR_CNT_02  , DCB_READONLY_REG },
  { "SERDES_ERR_CNT_03"   , DCB_REG_SERDES_ERR_CNT_03  , DCB_READONLY_REG },
  { "SERDES_ERR_CNT_04"   , DCB_REG_SERDES_ERR_CNT_04  , DCB_READONLY_REG },
  { "SERDES_ERR_CNT_05"   , DCB_REG_SERDES_ERR_CNT_05  , DCB_READONLY_REG },
  { "SERDES_ERR_CNT_06"   , DCB_REG_SERDES_ERR_CNT_06  , DCB_READONLY_REG },
  { "SERDES_ERR_CNT_07"   , DCB_REG_SERDES_ERR_CNT_07  , DCB_READONLY_REG },
  { "SERDES_ERR_CNT_08"   , DCB_REG_SERDES_ERR_CNT_08  , DCB_READONLY_REG },
  { "SERDES_ERR_CNT_09"   , DCB_REG_SERDES_ERR_CNT_09  , DCB_READONLY_REG },
  { "SERDES_ERR_CNT_10"   , DCB_REG_SERDES_ERR_CNT_10  , DCB_READONLY_REG },
  { "SERDES_ERR_CNT_11"   , DCB_REG_SERDES_ERR_CNT_11  , DCB_READONLY_REG },
  { "SERDES_ERR_CNT_12"   , DCB_REG_SERDES_ERR_CNT_12  , DCB_READONLY_REG },
  { "SERDES_ERR_CNT_13"   , DCB_REG_SERDES_ERR_CNT_13  , DCB_READONLY_REG },
  { "SERDES_ERR_CNT_14"   , DCB_REG_SERDES_ERR_CNT_14  , DCB_READONLY_REG },
  { "SERDES_ERR_CNT_15"   , DCB_REG_SERDES_ERR_CNT_15  , DCB_READONLY_REG },
  { "SERDES_ERR_CNT_17"   , DCB_REG_SERDES_ERR_CNT_17  , DCB_READONLY_REG },
  { "APLY_CFG"            , DCB_REG_APLY_CFG           , DCB_WRITABLE_REG },
  { "LMK_0"               , DCB_REG_LMK_0              , DCB_WRITABLE_REG },
  { "LMK_1"               , DCB_REG_LMK_1              , DCB_WRITABLE_REG },
  { "LMK_2"               , DCB_REG_LMK_2              , DCB_WRITABLE_REG },
  { "LMK_3"               , DCB_REG_LMK_3              , DCB_WRITABLE_REG },
  { "LMK_4"               , DCB_REG_LMK_4              , DCB_WRITABLE_REG },
  { "LMK_5"               , DCB_REG_LMK_5              , DCB_WRITABLE_REG },
  { "LMK_6"               , DCB_REG_LMK_6              , DCB_WRITABLE_REG },
  { "LMK_7"               , DCB_REG_LMK_7              , DCB_WRITABLE_REG },
  { "LMK_8"               , DCB_REG_LMK_8              , DCB_WRITABLE_REG },
  { "LMK_9"               , DCB_REG_LMK_9              , DCB_WRITABLE_REG },
  { "LMK_11"              , DCB_REG_LMK_11             , DCB_WRITABLE_REG },
  { "LMK_13"              , DCB_REG_LMK_13             , DCB_WRITABLE_REG },
  { "LMK_14"              , DCB_REG_LMK_14             , DCB_WRITABLE_REG },
  { "LMK_15"              , DCB_REG_LMK_15             , DCB_WRITABLE_REG },
  { "TIME_LSB"            , DCB_REG_TIME_LSB           , DCB_READONLY_REG },
  { "TIME_MSB"            , DCB_REG_TIME_MSB           , DCB_READONLY_REG },
  { "TIME_LSB_SET"        , DCB_REG_TIME_LSB_SET       , DCB_WRITABLE_REG },
  { "TIME_MSB_SET"        , DCB_REG_TIME_MSB_SET       , DCB_WRITABLE_REG },
  { "EVENT_TX_RATE"       , DCB_REG_EVENT_TX_RATE      , DCB_READONLY_REG },
  { "EVENT_NR"            , DCB_REG_EVENT_NR           , DCB_READONLY_REG },
  { "TRG_CFG"             , DCB_REG_TRG_CFG            , DCB_WRITABLE_REG },
  { "SET_TRG_CFG"         , DCB_REG_SET_TRG_CFG        , DCB_WRITABLE_REG },
  { "CLR_TRG_CFG"         , DCB_REG_CLR_TRG_CFG        , DCB_WRITABLE_REG },
  { "TRG_AUTO_PERIOD"     , DCB_REG_TRG_AUTO_PERIOD    , DCB_WRITABLE_REG },
  { "TRB_INFO_STAT"       , DCB_REG_TRB_INFO_STAT      , DCB_READONLY_REG },
  { "TRB_INFO_LSB"        , DCB_REG_TRB_INFO_LSB       , DCB_READONLY_REG },
  { "TRB_INFO_MSB"        , DCB_REG_TRB_INFO_MSB       , DCB_READONLY_REG },
  { "LMK_MOD_FLAG"        , DCB_REG_LMK_MOD_FLAG       , DCB_READONLY_REG },
  { "CMB_MSCB_ADR"        , DCB_REG_CMB_MSCB_ADR       , DCB_WRITABLE_REG },
  { "SD_PKT_CNT_0"        , DCB_REG_SD_PKT_CNT_0       , DCB_READONLY_REG },
  { "SD_PKT_CNT_1"        , DCB_REG_SD_PKT_CNT_1       , DCB_READONLY_REG },
  { "SD_PKT_CNT_2"        , DCB_REG_SD_PKT_CNT_2       , DCB_READONLY_REG },
  { "SD_PKT_CNT_3"        , DCB_REG_SD_PKT_CNT_3       , DCB_READONLY_REG },
  { "SD_PKT_CNT_4"        , DCB_REG_SD_PKT_CNT_4       , DCB_READONLY_REG },
  { "SD_PKT_CNT_5"        , DCB_REG_SD_PKT_CNT_5       , DCB_READONLY_REG },
  { "SD_PKT_CNT_6"        , DCB_REG_SD_PKT_CNT_6       , DCB_READONLY_REG },
  { "SD_PKT_CNT_7"        , DCB_REG_SD_PKT_CNT_7       , DCB_READONLY_REG },
  { "SD_PKT_CNT_8"        , DCB_REG_SD_PKT_CNT_8       , DCB_READONLY_REG },
  { "SD_PKT_CNT_9"        , DCB_REG_SD_PKT_CNT_9       , DCB_READONLY_REG },
  { "SD_PKT_CNT_10"       , DCB_REG_SD_PKT_CNT_10      , DCB_READONLY_REG },
  { "SD_PKT_CNT_11"       , DCB_REG_SD_PKT_CNT_11      , DCB_READONLY_REG },
  { "SD_PKT_CNT_12"       , DCB_REG_SD_PKT_CNT_12      , DCB_READONLY_REG },
  { "SD_PKT_CNT_13"       , DCB_REG_SD_PKT_CNT_13      , DCB_READONLY_REG },
  { "SD_PKT_CNT_14"       , DCB_REG_SD_PKT_CNT_14      , DCB_READONLY_REG },
  { "SD_PKT_CNT_15"       , DCB_REG_SD_PKT_CNT_15      , DCB_READONLY_REG },
  { "SD_PKT_CNT_17"       , DCB_REG_SD_PKT_CNT_17      , DCB_READONLY_REG },
  { "CRC32_REG_BANK"      , DCB_REG_CRC32_REG_BANK     , DCB_WRITABLE_REG },
  { (const char*)0        , 0                          , 0                }
};

/******************************************************************************/
/* Bit Mapping                                                                */
/******************************************************************************/

const dcb_bit_group_entry_type  dcb_bit_group_list[] = {
  { "BOARD_MAGIC"                  , DCB_BOARD_MAGIC_REG                  , DCB_BOARD_MAGIC_MASK                  , DCB_BOARD_MAGIC_OFS                  },
  { "VENDOR_ID"                    , DCB_VENDOR_ID_REG                    , DCB_VENDOR_ID_MASK                    , DCB_VENDOR_ID_OFS                    },
  { "BOARD_TYPE"                   , DCB_BOARD_TYPE_REG                   , DCB_BOARD_TYPE_MASK                   , DCB_BOARD_TYPE_OFS                   },
  { "BOARD_REVISION"               , DCB_BOARD_REVISION_REG               , DCB_BOARD_REVISION_MASK               , DCB_BOARD_REVISION_OFS               },
  { "BOARD_VARIANT"                , DCB_BOARD_VARIANT_REG                , DCB_BOARD_VARIANT_MASK                , DCB_BOARD_VARIANT_OFS                },
  { "REG_LAYOUT_COMP_LEVEL"        , DCB_REG_LAYOUT_COMP_LEVEL_REG        , DCB_REG_LAYOUT_COMP_LEVEL_MASK        , DCB_REG_LAYOUT_COMP_LEVEL_OFS        },
  { "REG_LAYOUT_VERSION"           , DCB_REG_LAYOUT_VERSION_REG           , DCB_REG_LAYOUT_VERSION_MASK           , DCB_REG_LAYOUT_VERSION_OFS           },
  { "FW_BUILD_YEAR"                , DCB_FW_BUILD_YEAR_REG                , DCB_FW_BUILD_YEAR_MASK                , DCB_FW_BUILD_YEAR_OFS                },
  { "FW_BUILD_MONTH"               , DCB_FW_BUILD_MONTH_REG               , DCB_FW_BUILD_MONTH_MASK               , DCB_FW_BUILD_MONTH_OFS               },
  { "FW_BUILD_DAY"                 , DCB_FW_BUILD_DAY_REG                 , DCB_FW_BUILD_DAY_MASK                 , DCB_FW_BUILD_DAY_OFS                 },
  { "FW_COMPAT_LEVEL"              , DCB_FW_COMPAT_LEVEL_REG              , DCB_FW_COMPAT_LEVEL_MASK              , DCB_FW_COMPAT_LEVEL_OFS              },
  { "FW_BUILD_HOUR"                , DCB_FW_BUILD_HOUR_REG                , DCB_FW_BUILD_HOUR_MASK                , DCB_FW_BUILD_HOUR_OFS                },
  { "FW_BUILD_MINUTE"              , DCB_FW_BUILD_MINUTE_REG              , DCB_FW_BUILD_MINUTE_MASK              , DCB_FW_BUILD_MINUTE_OFS              },
  { "FW_BUILD_SECOND"              , DCB_FW_BUILD_SECOND_REG              , DCB_FW_BUILD_SECOND_MASK              , DCB_FW_BUILD_SECOND_OFS              },
  { "SW_BUILD_YEAR"                , DCB_SW_BUILD_YEAR_REG                , DCB_SW_BUILD_YEAR_MASK                , DCB_SW_BUILD_YEAR_OFS                },
  { "SW_BUILD_MONTH"               , DCB_SW_BUILD_MONTH_REG               , DCB_SW_BUILD_MONTH_MASK               , DCB_SW_BUILD_MONTH_OFS               },
  { "SW_BUILD_DAY"                 , DCB_SW_BUILD_DAY_REG                 , DCB_SW_BUILD_DAY_MASK                 , DCB_SW_BUILD_DAY_OFS                 },
  { "SW_BUILD_HOUR"                , DCB_SW_BUILD_HOUR_REG                , DCB_SW_BUILD_HOUR_MASK                , DCB_SW_BUILD_HOUR_OFS                },
  { "SW_BUILD_MINUTE"              , DCB_SW_BUILD_MINUTE_REG              , DCB_SW_BUILD_MINUTE_MASK              , DCB_SW_BUILD_MINUTE_OFS              },
  { "SW_BUILD_SECOND"              , DCB_SW_BUILD_SECOND_REG              , DCB_SW_BUILD_SECOND_MASK              , DCB_SW_BUILD_SECOND_OFS              },
  { "FW_GIT_HASH_TAG"              , DCB_FW_GIT_HASH_TAG_REG              , DCB_FW_GIT_HASH_TAG_MASK              , DCB_FW_GIT_HASH_TAG_OFS              },
  { "SW_GIT_HASH_TAG"              , DCB_SW_GIT_HASH_TAG_REG              , DCB_SW_GIT_HASH_TAG_MASK              , DCB_SW_GIT_HASH_TAG_OFS              },
  { "PROTOCOL_VERSION"             , DCB_PROTOCOL_VERSION_REG             , DCB_PROTOCOL_VERSION_MASK             , DCB_PROTOCOL_VERSION_OFS             },
  { "SERIAL_NUMBER"                , DCB_SERIAL_NUMBER_REG                , DCB_SERIAL_NUMBER_MASK                , DCB_SERIAL_NUMBER_OFS                },
  { "FLASH_SEL"                    , DCB_FLASH_SEL_REG                    , DCB_FLASH_SEL_MASK                    , DCB_FLASH_SEL_OFS                    },
  { "BOARD_SEL"                    , DCB_BOARD_SEL_REG                    , DCB_BOARD_SEL_MASK                    , DCB_BOARD_SEL_OFS                    },
  { "SERIAL_BUSY"                  , DCB_SERIAL_BUSY_REG                  , DCB_SERIAL_BUSY_MASK                  , DCB_SERIAL_BUSY_OFS                  },
  { "DCB_BUSY"                     , DCB_DCB_BUSY_REG                     , DCB_DCB_BUSY_MASK                     , DCB_DCB_BUSY_OFS                     },
  { "SYS_BUSY"                     , DCB_SYS_BUSY_REG                     , DCB_SYS_BUSY_MASK                     , DCB_SYS_BUSY_OFS                     },
  { "TEMPERATURE"                  , DCB_TEMPERATURE_REG                  , DCB_TEMPERATURE_MASK                  , DCB_TEMPERATURE_OFS                  },
  { "SERDES_CLK_MGR_LOCK"          , DCB_SERDES_CLK_MGR_LOCK_REG          , DCB_SERDES_CLK_MGR_LOCK_MASK          , DCB_SERDES_CLK_MGR_LOCK_OFS          },
  { "WDB_CLK_MGR_LOCK"             , DCB_WDB_CLK_MGR_LOCK_REG             , DCB_WDB_CLK_MGR_LOCK_MASK             , DCB_WDB_CLK_MGR_LOCK_OFS             },
  { "SYS_DCM_LOCK"                 , DCB_SYS_DCM_LOCK_REG                 , DCB_SYS_DCM_LOCK_MASK                 , DCB_SYS_DCM_LOCK_OFS                 },
  { "LMK_PLL_LOCK"                 , DCB_LMK_PLL_LOCK_REG                 , DCB_LMK_PLL_LOCK_MASK                 , DCB_LMK_PLL_LOCK_OFS                 },
  { "CRATE_ID"                     , DCB_CRATE_ID_REG                     , DCB_CRATE_ID_MASK                     , DCB_CRATE_ID_OFS                     },
  { "SLOT_ID"                      , DCB_SLOT_ID_REG                      , DCB_SLOT_ID_MASK                      , DCB_SLOT_ID_OFS                      },
  { "SYNC_DELAY"                   , DCB_SYNC_DELAY_REG                   , DCB_SYNC_DELAY_MASK                   , DCB_SYNC_DELAY_OFS                   },
  { "DAQ_SOFT_TRIGGER"             , DCB_DAQ_SOFT_TRIGGER_REG             , DCB_DAQ_SOFT_TRIGGER_MASK             , DCB_DAQ_SOFT_TRIGGER_OFS             },
  { "DAQ_AUTO"                     , DCB_DAQ_AUTO_REG                     , DCB_DAQ_AUTO_MASK                     , DCB_DAQ_AUTO_OFS                     },
  { "DAQ_NORMAL"                   , DCB_DAQ_NORMAL_REG                   , DCB_DAQ_NORMAL_MASK                   , DCB_DAQ_NORMAL_OFS                   },
  { "DAQ_SINGLE"                   , DCB_DAQ_SINGLE_REG                   , DCB_DAQ_SINGLE_MASK                   , DCB_DAQ_SINGLE_OFS                   },
  { "SET_BIT_CTRL"                 , DCB_SET_BIT_CTRL_REG                 , DCB_SET_BIT_CTRL_MASK                 , DCB_SET_BIT_CTRL_OFS                 },
  { "CLR_BIT_CTRL"                 , DCB_CLR_BIT_CTRL_REG                 , DCB_CLR_BIT_CTRL_MASK                 , DCB_CLR_BIT_CTRL_OFS                 },
  { "DISTRIBUTOR_CLK_OUT_EN"       , DCB_DISTRIBUTOR_CLK_OUT_EN_REG       , DCB_DISTRIBUTOR_CLK_OUT_EN_MASK       , DCB_DISTRIBUTOR_CLK_OUT_EN_OFS       },
  { "DISTRIBUTOR_CLK_SRC_SEL"      , DCB_DISTRIBUTOR_CLK_SRC_SEL_REG      , DCB_DISTRIBUTOR_CLK_SRC_SEL_MASK      , DCB_DISTRIBUTOR_CLK_SRC_SEL_OFS      },
  { "BUS_CLK_SRC_SEL"              , DCB_BUS_CLK_SRC_SEL_REG              , DCB_BUS_CLK_SRC_SEL_MASK              , DCB_BUS_CLK_SRC_SEL_OFS              },
  { "LMK_CLK_SRC_SEL"              , DCB_LMK_CLK_SRC_SEL_REG              , DCB_LMK_CLK_SRC_SEL_MASK              , DCB_LMK_CLK_SRC_SEL_OFS              },
  { "EXT_CLK_IN_SEL"               , DCB_EXT_CLK_IN_SEL_REG               , DCB_EXT_CLK_IN_SEL_MASK               , DCB_EXT_CLK_IN_SEL_OFS               },
  { "SET_BIT_CLK_CTRL"             , DCB_SET_BIT_CLK_CTRL_REG             , DCB_SET_BIT_CLK_CTRL_MASK             , DCB_SET_BIT_CLK_CTRL_OFS             },
  { "CLR_BIT_CLK_CTRL"             , DCB_CLR_BIT_CLK_CTRL_REG             , DCB_CLR_BIT_CLK_CTRL_MASK             , DCB_CLR_BIT_CLK_CTRL_OFS             },
  { "INTER_PKG_DELAY"              , DCB_INTER_PKG_DELAY_REG              , DCB_INTER_PKG_DELAY_MASK              , DCB_INTER_PKG_DELAY_OFS              },
  { "DPS_EVENT_MODE"               , DCB_DPS_EVENT_MODE_REG               , DCB_DPS_EVENT_MODE_MASK               , DCB_DPS_EVENT_MODE_OFS               },
  { "DPS_SLOT_ENABLE"              , DCB_DPS_SLOT_ENABLE_REG              , DCB_DPS_SLOT_ENABLE_MASK              , DCB_DPS_SLOT_ENABLE_OFS              },
  { "WDB_SERDES_CLK_MGR_RST"       , DCB_WDB_SERDES_CLK_MGR_RST_REG       , DCB_WDB_SERDES_CLK_MGR_RST_MASK       , DCB_WDB_SERDES_CLK_MGR_RST_OFS       },
  { "WDB_REFCLK_MGR_RST"           , DCB_WDB_REFCLK_MGR_RST_REG           , DCB_WDB_REFCLK_MGR_RST_MASK           , DCB_WDB_REFCLK_MGR_RST_OFS           },
  { "TRIGGER_MGR_RST"              , DCB_TRIGGER_MGR_RST_REG              , DCB_TRIGGER_MGR_RST_MASK              , DCB_TRIGGER_MGR_RST_OFS              },
  { "TR_SYNC_BPL"                  , DCB_TR_SYNC_BPL_REG                  , DCB_TR_SYNC_BPL_MASK                  , DCB_TR_SYNC_BPL_OFS                  },
  { "LMK_SYNC_DCB"                 , DCB_LMK_SYNC_DCB_REG                 , DCB_LMK_SYNC_DCB_MASK                 , DCB_LMK_SYNC_DCB_OFS                 },
  { "ISERDES_RCVR_ERROR_COUNT_RST" , DCB_ISERDES_RCVR_ERROR_COUNT_RST_REG , DCB_ISERDES_RCVR_ERROR_COUNT_RST_MASK , DCB_ISERDES_RCVR_ERROR_COUNT_RST_OFS },
  { "ISERDES_RECEIVER_RESYNC"      , DCB_ISERDES_RECEIVER_RESYNC_REG      , DCB_ISERDES_RECEIVER_RESYNC_MASK      , DCB_ISERDES_RECEIVER_RESYNC_OFS      },
  { "ISERDES_RECEIVER_RST"         , DCB_ISERDES_RECEIVER_RST_REG         , DCB_ISERDES_RECEIVER_RST_MASK         , DCB_ISERDES_RECEIVER_RST_OFS         },
  { "RECONFIGURE_FPGA"             , DCB_RECONFIGURE_FPGA_REG             , DCB_RECONFIGURE_FPGA_MASK             , DCB_RECONFIGURE_FPGA_OFS             },
  { "IDLE_PATTERN_DETECT_07"       , DCB_IDLE_PATTERN_DETECT_07_REG       , DCB_IDLE_PATTERN_DETECT_07_MASK       , DCB_IDLE_PATTERN_DETECT_07_OFS       },
  { "DELAY_SYNC_DONE_07"           , DCB_DELAY_SYNC_DONE_07_REG           , DCB_DELAY_SYNC_DONE_07_MASK           , DCB_DELAY_SYNC_DONE_07_OFS           },
  { "SYNC_DONE_07"                 , DCB_SYNC_DONE_07_REG                 , DCB_SYNC_DONE_07_MASK                 , DCB_SYNC_DONE_07_OFS                 },
  { "IDLE_PATTERN_DETECT_06"       , DCB_IDLE_PATTERN_DETECT_06_REG       , DCB_IDLE_PATTERN_DETECT_06_MASK       , DCB_IDLE_PATTERN_DETECT_06_OFS       },
  { "DELAY_SYNC_DONE_06"           , DCB_DELAY_SYNC_DONE_06_REG           , DCB_DELAY_SYNC_DONE_06_MASK           , DCB_DELAY_SYNC_DONE_06_OFS           },
  { "SYNC_DONE_06"                 , DCB_SYNC_DONE_06_REG                 , DCB_SYNC_DONE_06_MASK                 , DCB_SYNC_DONE_06_OFS                 },
  { "IDLE_PATTERN_DETECT_05"       , DCB_IDLE_PATTERN_DETECT_05_REG       , DCB_IDLE_PATTERN_DETECT_05_MASK       , DCB_IDLE_PATTERN_DETECT_05_OFS       },
  { "DELAY_SYNC_DONE_05"           , DCB_DELAY_SYNC_DONE_05_REG           , DCB_DELAY_SYNC_DONE_05_MASK           , DCB_DELAY_SYNC_DONE_05_OFS           },
  { "SYNC_DONE_05"                 , DCB_SYNC_DONE_05_REG                 , DCB_SYNC_DONE_05_MASK                 , DCB_SYNC_DONE_05_OFS                 },
  { "IDLE_PATTERN_DETECT_04"       , DCB_IDLE_PATTERN_DETECT_04_REG       , DCB_IDLE_PATTERN_DETECT_04_MASK       , DCB_IDLE_PATTERN_DETECT_04_OFS       },
  { "DELAY_SYNC_DONE_04"           , DCB_DELAY_SYNC_DONE_04_REG           , DCB_DELAY_SYNC_DONE_04_MASK           , DCB_DELAY_SYNC_DONE_04_OFS           },
  { "SYNC_DONE_04"                 , DCB_SYNC_DONE_04_REG                 , DCB_SYNC_DONE_04_MASK                 , DCB_SYNC_DONE_04_OFS                 },
  { "IDLE_PATTERN_DETECT_03"       , DCB_IDLE_PATTERN_DETECT_03_REG       , DCB_IDLE_PATTERN_DETECT_03_MASK       , DCB_IDLE_PATTERN_DETECT_03_OFS       },
  { "DELAY_SYNC_DONE_03"           , DCB_DELAY_SYNC_DONE_03_REG           , DCB_DELAY_SYNC_DONE_03_MASK           , DCB_DELAY_SYNC_DONE_03_OFS           },
  { "SYNC_DONE_03"                 , DCB_SYNC_DONE_03_REG                 , DCB_SYNC_DONE_03_MASK                 , DCB_SYNC_DONE_03_OFS                 },
  { "IDLE_PATTERN_DETECT_02"       , DCB_IDLE_PATTERN_DETECT_02_REG       , DCB_IDLE_PATTERN_DETECT_02_MASK       , DCB_IDLE_PATTERN_DETECT_02_OFS       },
  { "DELAY_SYNC_DONE_02"           , DCB_DELAY_SYNC_DONE_02_REG           , DCB_DELAY_SYNC_DONE_02_MASK           , DCB_DELAY_SYNC_DONE_02_OFS           },
  { "SYNC_DONE_02"                 , DCB_SYNC_DONE_02_REG                 , DCB_SYNC_DONE_02_MASK                 , DCB_SYNC_DONE_02_OFS                 },
  { "IDLE_PATTERN_DETECT_01"       , DCB_IDLE_PATTERN_DETECT_01_REG       , DCB_IDLE_PATTERN_DETECT_01_MASK       , DCB_IDLE_PATTERN_DETECT_01_OFS       },
  { "DELAY_SYNC_DONE_01"           , DCB_DELAY_SYNC_DONE_01_REG           , DCB_DELAY_SYNC_DONE_01_MASK           , DCB_DELAY_SYNC_DONE_01_OFS           },
  { "SYNC_DONE_01"                 , DCB_SYNC_DONE_01_REG                 , DCB_SYNC_DONE_01_MASK                 , DCB_SYNC_DONE_01_OFS                 },
  { "IDLE_PATTERN_DETECT_00"       , DCB_IDLE_PATTERN_DETECT_00_REG       , DCB_IDLE_PATTERN_DETECT_00_MASK       , DCB_IDLE_PATTERN_DETECT_00_OFS       },
  { "DELAY_SYNC_DONE_00"           , DCB_DELAY_SYNC_DONE_00_REG           , DCB_DELAY_SYNC_DONE_00_MASK           , DCB_DELAY_SYNC_DONE_00_OFS           },
  { "SYNC_DONE_00"                 , DCB_SYNC_DONE_00_REG                 , DCB_SYNC_DONE_00_MASK                 , DCB_SYNC_DONE_00_OFS                 },
  { "IDLE_PATTERN_DETECT_15"       , DCB_IDLE_PATTERN_DETECT_15_REG       , DCB_IDLE_PATTERN_DETECT_15_MASK       , DCB_IDLE_PATTERN_DETECT_15_OFS       },
  { "DELAY_SYNC_DONE_15"           , DCB_DELAY_SYNC_DONE_15_REG           , DCB_DELAY_SYNC_DONE_15_MASK           , DCB_DELAY_SYNC_DONE_15_OFS           },
  { "SYNC_DONE_15"                 , DCB_SYNC_DONE_15_REG                 , DCB_SYNC_DONE_15_MASK                 , DCB_SYNC_DONE_15_OFS                 },
  { "IDLE_PATTERN_DETECT_14"       , DCB_IDLE_PATTERN_DETECT_14_REG       , DCB_IDLE_PATTERN_DETECT_14_MASK       , DCB_IDLE_PATTERN_DETECT_14_OFS       },
  { "DELAY_SYNC_DONE_14"           , DCB_DELAY_SYNC_DONE_14_REG           , DCB_DELAY_SYNC_DONE_14_MASK           , DCB_DELAY_SYNC_DONE_14_OFS           },
  { "SYNC_DONE_14"                 , DCB_SYNC_DONE_14_REG                 , DCB_SYNC_DONE_14_MASK                 , DCB_SYNC_DONE_14_OFS                 },
  { "IDLE_PATTERN_DETECT_13"       , DCB_IDLE_PATTERN_DETECT_13_REG       , DCB_IDLE_PATTERN_DETECT_13_MASK       , DCB_IDLE_PATTERN_DETECT_13_OFS       },
  { "DELAY_SYNC_DONE_13"           , DCB_DELAY_SYNC_DONE_13_REG           , DCB_DELAY_SYNC_DONE_13_MASK           , DCB_DELAY_SYNC_DONE_13_OFS           },
  { "SYNC_DONE_13"                 , DCB_SYNC_DONE_13_REG                 , DCB_SYNC_DONE_13_MASK                 , DCB_SYNC_DONE_13_OFS                 },
  { "IDLE_PATTERN_DETECT_12"       , DCB_IDLE_PATTERN_DETECT_12_REG       , DCB_IDLE_PATTERN_DETECT_12_MASK       , DCB_IDLE_PATTERN_DETECT_12_OFS       },
  { "DELAY_SYNC_DONE_12"           , DCB_DELAY_SYNC_DONE_12_REG           , DCB_DELAY_SYNC_DONE_12_MASK           , DCB_DELAY_SYNC_DONE_12_OFS           },
  { "SYNC_DONE_12"                 , DCB_SYNC_DONE_12_REG                 , DCB_SYNC_DONE_12_MASK                 , DCB_SYNC_DONE_12_OFS                 },
  { "IDLE_PATTERN_DETECT_11"       , DCB_IDLE_PATTERN_DETECT_11_REG       , DCB_IDLE_PATTERN_DETECT_11_MASK       , DCB_IDLE_PATTERN_DETECT_11_OFS       },
  { "DELAY_SYNC_DONE_11"           , DCB_DELAY_SYNC_DONE_11_REG           , DCB_DELAY_SYNC_DONE_11_MASK           , DCB_DELAY_SYNC_DONE_11_OFS           },
  { "SYNC_DONE_11"                 , DCB_SYNC_DONE_11_REG                 , DCB_SYNC_DONE_11_MASK                 , DCB_SYNC_DONE_11_OFS                 },
  { "IDLE_PATTERN_DETECT_10"       , DCB_IDLE_PATTERN_DETECT_10_REG       , DCB_IDLE_PATTERN_DETECT_10_MASK       , DCB_IDLE_PATTERN_DETECT_10_OFS       },
  { "DELAY_SYNC_DONE_10"           , DCB_DELAY_SYNC_DONE_10_REG           , DCB_DELAY_SYNC_DONE_10_MASK           , DCB_DELAY_SYNC_DONE_10_OFS           },
  { "SYNC_DONE_10"                 , DCB_SYNC_DONE_10_REG                 , DCB_SYNC_DONE_10_MASK                 , DCB_SYNC_DONE_10_OFS                 },
  { "IDLE_PATTERN_DETECT_09"       , DCB_IDLE_PATTERN_DETECT_09_REG       , DCB_IDLE_PATTERN_DETECT_09_MASK       , DCB_IDLE_PATTERN_DETECT_09_OFS       },
  { "DELAY_SYNC_DONE_09"           , DCB_DELAY_SYNC_DONE_09_REG           , DCB_DELAY_SYNC_DONE_09_MASK           , DCB_DELAY_SYNC_DONE_09_OFS           },
  { "SYNC_DONE_09"                 , DCB_SYNC_DONE_09_REG                 , DCB_SYNC_DONE_09_MASK                 , DCB_SYNC_DONE_09_OFS                 },
  { "IDLE_PATTERN_DETECT_08"       , DCB_IDLE_PATTERN_DETECT_08_REG       , DCB_IDLE_PATTERN_DETECT_08_MASK       , DCB_IDLE_PATTERN_DETECT_08_OFS       },
  { "DELAY_SYNC_DONE_08"           , DCB_DELAY_SYNC_DONE_08_REG           , DCB_DELAY_SYNC_DONE_08_MASK           , DCB_DELAY_SYNC_DONE_08_OFS           },
  { "SYNC_DONE_08"                 , DCB_SYNC_DONE_08_REG                 , DCB_SYNC_DONE_08_MASK                 , DCB_SYNC_DONE_08_OFS                 },
  { "IDLE_PATTERN_DETECT_17"       , DCB_IDLE_PATTERN_DETECT_17_REG       , DCB_IDLE_PATTERN_DETECT_17_MASK       , DCB_IDLE_PATTERN_DETECT_17_OFS       },
  { "DELAY_SYNC_DONE_17"           , DCB_DELAY_SYNC_DONE_17_REG           , DCB_DELAY_SYNC_DONE_17_MASK           , DCB_DELAY_SYNC_DONE_17_OFS           },
  { "SYNC_DONE_17"                 , DCB_SYNC_DONE_17_REG                 , DCB_SYNC_DONE_17_MASK                 , DCB_SYNC_DONE_17_OFS                 },
  { "CRC_ERRORS_00"                , DCB_CRC_ERRORS_00_REG                , DCB_CRC_ERRORS_00_MASK                , DCB_CRC_ERRORS_00_OFS                },
  { "FRAME_ERRORS_00"              , DCB_FRAME_ERRORS_00_REG              , DCB_FRAME_ERRORS_00_MASK              , DCB_FRAME_ERRORS_00_OFS              },
  { "DATAGRAM_ERRORS_00"           , DCB_DATAGRAM_ERRORS_00_REG           , DCB_DATAGRAM_ERRORS_00_MASK           , DCB_DATAGRAM_ERRORS_00_OFS           },
  { "SYNC_ERRORS_00"               , DCB_SYNC_ERRORS_00_REG               , DCB_SYNC_ERRORS_00_MASK               , DCB_SYNC_ERRORS_00_OFS               },
  { "CRC_ERRORS_01"                , DCB_CRC_ERRORS_01_REG                , DCB_CRC_ERRORS_01_MASK                , DCB_CRC_ERRORS_01_OFS                },
  { "FRAME_ERRORS_01"              , DCB_FRAME_ERRORS_01_REG              , DCB_FRAME_ERRORS_01_MASK              , DCB_FRAME_ERRORS_01_OFS              },
  { "DATAGRAM_ERRORS_01"           , DCB_DATAGRAM_ERRORS_01_REG           , DCB_DATAGRAM_ERRORS_01_MASK           , DCB_DATAGRAM_ERRORS_01_OFS           },
  { "SYNC_ERRORS_01"               , DCB_SYNC_ERRORS_01_REG               , DCB_SYNC_ERRORS_01_MASK               , DCB_SYNC_ERRORS_01_OFS               },
  { "CRC_ERRORS_02"                , DCB_CRC_ERRORS_02_REG                , DCB_CRC_ERRORS_02_MASK                , DCB_CRC_ERRORS_02_OFS                },
  { "FRAME_ERRORS_02"              , DCB_FRAME_ERRORS_02_REG              , DCB_FRAME_ERRORS_02_MASK              , DCB_FRAME_ERRORS_02_OFS              },
  { "DATAGRAM_ERRORS_02"           , DCB_DATAGRAM_ERRORS_02_REG           , DCB_DATAGRAM_ERRORS_02_MASK           , DCB_DATAGRAM_ERRORS_02_OFS           },
  { "SYNC_ERRORS_02"               , DCB_SYNC_ERRORS_02_REG               , DCB_SYNC_ERRORS_02_MASK               , DCB_SYNC_ERRORS_02_OFS               },
  { "CRC_ERRORS_03"                , DCB_CRC_ERRORS_03_REG                , DCB_CRC_ERRORS_03_MASK                , DCB_CRC_ERRORS_03_OFS                },
  { "FRAME_ERRORS_03"              , DCB_FRAME_ERRORS_03_REG              , DCB_FRAME_ERRORS_03_MASK              , DCB_FRAME_ERRORS_03_OFS              },
  { "DATAGRAM_ERRORS_03"           , DCB_DATAGRAM_ERRORS_03_REG           , DCB_DATAGRAM_ERRORS_03_MASK           , DCB_DATAGRAM_ERRORS_03_OFS           },
  { "SYNC_ERRORS_03"               , DCB_SYNC_ERRORS_03_REG               , DCB_SYNC_ERRORS_03_MASK               , DCB_SYNC_ERRORS_03_OFS               },
  { "CRC_ERRORS_04"                , DCB_CRC_ERRORS_04_REG                , DCB_CRC_ERRORS_04_MASK                , DCB_CRC_ERRORS_04_OFS                },
  { "FRAME_ERRORS_04"              , DCB_FRAME_ERRORS_04_REG              , DCB_FRAME_ERRORS_04_MASK              , DCB_FRAME_ERRORS_04_OFS              },
  { "DATAGRAM_ERRORS_04"           , DCB_DATAGRAM_ERRORS_04_REG           , DCB_DATAGRAM_ERRORS_04_MASK           , DCB_DATAGRAM_ERRORS_04_OFS           },
  { "SYNC_ERRORS_04"               , DCB_SYNC_ERRORS_04_REG               , DCB_SYNC_ERRORS_04_MASK               , DCB_SYNC_ERRORS_04_OFS               },
  { "CRC_ERRORS_05"                , DCB_CRC_ERRORS_05_REG                , DCB_CRC_ERRORS_05_MASK                , DCB_CRC_ERRORS_05_OFS                },
  { "FRAME_ERRORS_05"              , DCB_FRAME_ERRORS_05_REG              , DCB_FRAME_ERRORS_05_MASK              , DCB_FRAME_ERRORS_05_OFS              },
  { "DATAGRAM_ERRORS_05"           , DCB_DATAGRAM_ERRORS_05_REG           , DCB_DATAGRAM_ERRORS_05_MASK           , DCB_DATAGRAM_ERRORS_05_OFS           },
  { "SYNC_ERRORS_05"               , DCB_SYNC_ERRORS_05_REG               , DCB_SYNC_ERRORS_05_MASK               , DCB_SYNC_ERRORS_05_OFS               },
  { "CRC_ERRORS_06"                , DCB_CRC_ERRORS_06_REG                , DCB_CRC_ERRORS_06_MASK                , DCB_CRC_ERRORS_06_OFS                },
  { "FRAME_ERRORS_06"              , DCB_FRAME_ERRORS_06_REG              , DCB_FRAME_ERRORS_06_MASK              , DCB_FRAME_ERRORS_06_OFS              },
  { "DATAGRAM_ERRORS_06"           , DCB_DATAGRAM_ERRORS_06_REG           , DCB_DATAGRAM_ERRORS_06_MASK           , DCB_DATAGRAM_ERRORS_06_OFS           },
  { "SYNC_ERRORS_06"               , DCB_SYNC_ERRORS_06_REG               , DCB_SYNC_ERRORS_06_MASK               , DCB_SYNC_ERRORS_06_OFS               },
  { "CRC_ERRORS_07"                , DCB_CRC_ERRORS_07_REG                , DCB_CRC_ERRORS_07_MASK                , DCB_CRC_ERRORS_07_OFS                },
  { "FRAME_ERRORS_07"              , DCB_FRAME_ERRORS_07_REG              , DCB_FRAME_ERRORS_07_MASK              , DCB_FRAME_ERRORS_07_OFS              },
  { "DATAGRAM_ERRORS_07"           , DCB_DATAGRAM_ERRORS_07_REG           , DCB_DATAGRAM_ERRORS_07_MASK           , DCB_DATAGRAM_ERRORS_07_OFS           },
  { "SYNC_ERRORS_07"               , DCB_SYNC_ERRORS_07_REG               , DCB_SYNC_ERRORS_07_MASK               , DCB_SYNC_ERRORS_07_OFS               },
  { "CRC_ERRORS_08"                , DCB_CRC_ERRORS_08_REG                , DCB_CRC_ERRORS_08_MASK                , DCB_CRC_ERRORS_08_OFS                },
  { "FRAME_ERRORS_08"              , DCB_FRAME_ERRORS_08_REG              , DCB_FRAME_ERRORS_08_MASK              , DCB_FRAME_ERRORS_08_OFS              },
  { "DATAGRAM_ERRORS_08"           , DCB_DATAGRAM_ERRORS_08_REG           , DCB_DATAGRAM_ERRORS_08_MASK           , DCB_DATAGRAM_ERRORS_08_OFS           },
  { "SYNC_ERRORS_08"               , DCB_SYNC_ERRORS_08_REG               , DCB_SYNC_ERRORS_08_MASK               , DCB_SYNC_ERRORS_08_OFS               },
  { "CRC_ERRORS_09"                , DCB_CRC_ERRORS_09_REG                , DCB_CRC_ERRORS_09_MASK                , DCB_CRC_ERRORS_09_OFS                },
  { "FRAME_ERRORS_09"              , DCB_FRAME_ERRORS_09_REG              , DCB_FRAME_ERRORS_09_MASK              , DCB_FRAME_ERRORS_09_OFS              },
  { "DATAGRAM_ERRORS_09"           , DCB_DATAGRAM_ERRORS_09_REG           , DCB_DATAGRAM_ERRORS_09_MASK           , DCB_DATAGRAM_ERRORS_09_OFS           },
  { "SYNC_ERRORS_09"               , DCB_SYNC_ERRORS_09_REG               , DCB_SYNC_ERRORS_09_MASK               , DCB_SYNC_ERRORS_09_OFS               },
  { "CRC_ERRORS_10"                , DCB_CRC_ERRORS_10_REG                , DCB_CRC_ERRORS_10_MASK                , DCB_CRC_ERRORS_10_OFS                },
  { "FRAME_ERRORS_10"              , DCB_FRAME_ERRORS_10_REG              , DCB_FRAME_ERRORS_10_MASK              , DCB_FRAME_ERRORS_10_OFS              },
  { "DATAGRAM_ERRORS_10"           , DCB_DATAGRAM_ERRORS_10_REG           , DCB_DATAGRAM_ERRORS_10_MASK           , DCB_DATAGRAM_ERRORS_10_OFS           },
  { "SYNC_ERRORS_10"               , DCB_SYNC_ERRORS_10_REG               , DCB_SYNC_ERRORS_10_MASK               , DCB_SYNC_ERRORS_10_OFS               },
  { "CRC_ERRORS_11"                , DCB_CRC_ERRORS_11_REG                , DCB_CRC_ERRORS_11_MASK                , DCB_CRC_ERRORS_11_OFS                },
  { "FRAME_ERRORS_11"              , DCB_FRAME_ERRORS_11_REG              , DCB_FRAME_ERRORS_11_MASK              , DCB_FRAME_ERRORS_11_OFS              },
  { "DATAGRAM_ERRORS_11"           , DCB_DATAGRAM_ERRORS_11_REG           , DCB_DATAGRAM_ERRORS_11_MASK           , DCB_DATAGRAM_ERRORS_11_OFS           },
  { "SYNC_ERRORS_11"               , DCB_SYNC_ERRORS_11_REG               , DCB_SYNC_ERRORS_11_MASK               , DCB_SYNC_ERRORS_11_OFS               },
  { "CRC_ERRORS_12"                , DCB_CRC_ERRORS_12_REG                , DCB_CRC_ERRORS_12_MASK                , DCB_CRC_ERRORS_12_OFS                },
  { "FRAME_ERRORS_12"              , DCB_FRAME_ERRORS_12_REG              , DCB_FRAME_ERRORS_12_MASK              , DCB_FRAME_ERRORS_12_OFS              },
  { "DATAGRAM_ERRORS_12"           , DCB_DATAGRAM_ERRORS_12_REG           , DCB_DATAGRAM_ERRORS_12_MASK           , DCB_DATAGRAM_ERRORS_12_OFS           },
  { "SYNC_ERRORS_12"               , DCB_SYNC_ERRORS_12_REG               , DCB_SYNC_ERRORS_12_MASK               , DCB_SYNC_ERRORS_12_OFS               },
  { "CRC_ERRORS_13"                , DCB_CRC_ERRORS_13_REG                , DCB_CRC_ERRORS_13_MASK                , DCB_CRC_ERRORS_13_OFS                },
  { "FRAME_ERRORS_13"              , DCB_FRAME_ERRORS_13_REG              , DCB_FRAME_ERRORS_13_MASK              , DCB_FRAME_ERRORS_13_OFS              },
  { "DATAGRAM_ERRORS_13"           , DCB_DATAGRAM_ERRORS_13_REG           , DCB_DATAGRAM_ERRORS_13_MASK           , DCB_DATAGRAM_ERRORS_13_OFS           },
  { "SYNC_ERRORS_13"               , DCB_SYNC_ERRORS_13_REG               , DCB_SYNC_ERRORS_13_MASK               , DCB_SYNC_ERRORS_13_OFS               },
  { "CRC_ERRORS_14"                , DCB_CRC_ERRORS_14_REG                , DCB_CRC_ERRORS_14_MASK                , DCB_CRC_ERRORS_14_OFS                },
  { "FRAME_ERRORS_14"              , DCB_FRAME_ERRORS_14_REG              , DCB_FRAME_ERRORS_14_MASK              , DCB_FRAME_ERRORS_14_OFS              },
  { "DATAGRAM_ERRORS_14"           , DCB_DATAGRAM_ERRORS_14_REG           , DCB_DATAGRAM_ERRORS_14_MASK           , DCB_DATAGRAM_ERRORS_14_OFS           },
  { "SYNC_ERRORS_14"               , DCB_SYNC_ERRORS_14_REG               , DCB_SYNC_ERRORS_14_MASK               , DCB_SYNC_ERRORS_14_OFS               },
  { "CRC_ERRORS_15"                , DCB_CRC_ERRORS_15_REG                , DCB_CRC_ERRORS_15_MASK                , DCB_CRC_ERRORS_15_OFS                },
  { "FRAME_ERRORS_15"              , DCB_FRAME_ERRORS_15_REG              , DCB_FRAME_ERRORS_15_MASK              , DCB_FRAME_ERRORS_15_OFS              },
  { "DATAGRAM_ERRORS_15"           , DCB_DATAGRAM_ERRORS_15_REG           , DCB_DATAGRAM_ERRORS_15_MASK           , DCB_DATAGRAM_ERRORS_15_OFS           },
  { "SYNC_ERRORS_15"               , DCB_SYNC_ERRORS_15_REG               , DCB_SYNC_ERRORS_15_MASK               , DCB_SYNC_ERRORS_15_OFS               },
  { "CRC_ERRORS_17"                , DCB_CRC_ERRORS_17_REG                , DCB_CRC_ERRORS_17_MASK                , DCB_CRC_ERRORS_17_OFS                },
  { "FRAME_ERRORS_17"              , DCB_FRAME_ERRORS_17_REG              , DCB_FRAME_ERRORS_17_MASK              , DCB_FRAME_ERRORS_17_OFS              },
  { "DATAGRAM_ERRORS_17"           , DCB_DATAGRAM_ERRORS_17_REG           , DCB_DATAGRAM_ERRORS_17_MASK           , DCB_DATAGRAM_ERRORS_17_OFS           },
  { "SYNC_ERRORS_17"               , DCB_SYNC_ERRORS_17_REG               , DCB_SYNC_ERRORS_17_MASK               , DCB_SYNC_ERRORS_17_OFS               },
  { "APPLY_SETTINGS_LMK"           , DCB_APPLY_SETTINGS_LMK_REG           , DCB_APPLY_SETTINGS_LMK_MASK           , DCB_APPLY_SETTINGS_LMK_OFS           },
  { "LMK0_RESET"                   , DCB_LMK0_RESET_REG                   , DCB_LMK0_RESET_MASK                   , DCB_LMK0_RESET_OFS                   },
  { "LMK0_CLKOUT_MUX"              , DCB_LMK0_CLKOUT_MUX_REG              , DCB_LMK0_CLKOUT_MUX_MASK              , DCB_LMK0_CLKOUT_MUX_OFS              },
  { "LMK0_CLKOUT_EN"               , DCB_LMK0_CLKOUT_EN_REG               , DCB_LMK0_CLKOUT_EN_MASK               , DCB_LMK0_CLKOUT_EN_OFS               },
  { "LMK0_CLKOUT_DIV"              , DCB_LMK0_CLKOUT_DIV_REG              , DCB_LMK0_CLKOUT_DIV_MASK              , DCB_LMK0_CLKOUT_DIV_OFS              },
  { "LMK0_CLKOUT_DLY"              , DCB_LMK0_CLKOUT_DLY_REG              , DCB_LMK0_CLKOUT_DLY_MASK              , DCB_LMK0_CLKOUT_DLY_OFS              },
  { "LMK1_CLKOUT_MUX"              , DCB_LMK1_CLKOUT_MUX_REG              , DCB_LMK1_CLKOUT_MUX_MASK              , DCB_LMK1_CLKOUT_MUX_OFS              },
  { "LMK1_CLKOUT_EN"               , DCB_LMK1_CLKOUT_EN_REG               , DCB_LMK1_CLKOUT_EN_MASK               , DCB_LMK1_CLKOUT_EN_OFS               },
  { "LMK1_CLKOUT_DIV"              , DCB_LMK1_CLKOUT_DIV_REG              , DCB_LMK1_CLKOUT_DIV_MASK              , DCB_LMK1_CLKOUT_DIV_OFS              },
  { "LMK1_CLKOUT_DLY"              , DCB_LMK1_CLKOUT_DLY_REG              , DCB_LMK1_CLKOUT_DLY_MASK              , DCB_LMK1_CLKOUT_DLY_OFS              },
  { "LMK2_CLKOUT_MUX"              , DCB_LMK2_CLKOUT_MUX_REG              , DCB_LMK2_CLKOUT_MUX_MASK              , DCB_LMK2_CLKOUT_MUX_OFS              },
  { "LMK2_CLKOUT_EN"               , DCB_LMK2_CLKOUT_EN_REG               , DCB_LMK2_CLKOUT_EN_MASK               , DCB_LMK2_CLKOUT_EN_OFS               },
  { "LMK2_CLKOUT_DIV"              , DCB_LMK2_CLKOUT_DIV_REG              , DCB_LMK2_CLKOUT_DIV_MASK              , DCB_LMK2_CLKOUT_DIV_OFS              },
  { "LMK2_CLKOUT_DLY"              , DCB_LMK2_CLKOUT_DLY_REG              , DCB_LMK2_CLKOUT_DLY_MASK              , DCB_LMK2_CLKOUT_DLY_OFS              },
  { "LMK3_CLKOUT_MUX"              , DCB_LMK3_CLKOUT_MUX_REG              , DCB_LMK3_CLKOUT_MUX_MASK              , DCB_LMK3_CLKOUT_MUX_OFS              },
  { "LMK3_CLKOUT_EN"               , DCB_LMK3_CLKOUT_EN_REG               , DCB_LMK3_CLKOUT_EN_MASK               , DCB_LMK3_CLKOUT_EN_OFS               },
  { "LMK3_CLKOUT_DIV"              , DCB_LMK3_CLKOUT_DIV_REG              , DCB_LMK3_CLKOUT_DIV_MASK              , DCB_LMK3_CLKOUT_DIV_OFS              },
  { "LMK3_CLKOUT_DLY"              , DCB_LMK3_CLKOUT_DLY_REG              , DCB_LMK3_CLKOUT_DLY_MASK              , DCB_LMK3_CLKOUT_DLY_OFS              },
  { "LMK4_CLKOUT_MUX"              , DCB_LMK4_CLKOUT_MUX_REG              , DCB_LMK4_CLKOUT_MUX_MASK              , DCB_LMK4_CLKOUT_MUX_OFS              },
  { "LMK4_CLKOUT_EN"               , DCB_LMK4_CLKOUT_EN_REG               , DCB_LMK4_CLKOUT_EN_MASK               , DCB_LMK4_CLKOUT_EN_OFS               },
  { "LMK4_CLKOUT_DIV"              , DCB_LMK4_CLKOUT_DIV_REG              , DCB_LMK4_CLKOUT_DIV_MASK              , DCB_LMK4_CLKOUT_DIV_OFS              },
  { "LMK4_CLKOUT_DLY"              , DCB_LMK4_CLKOUT_DLY_REG              , DCB_LMK4_CLKOUT_DLY_MASK              , DCB_LMK4_CLKOUT_DLY_OFS              },
  { "LMK5_CLKOUT_MUX"              , DCB_LMK5_CLKOUT_MUX_REG              , DCB_LMK5_CLKOUT_MUX_MASK              , DCB_LMK5_CLKOUT_MUX_OFS              },
  { "LMK5_CLKOUT_EN"               , DCB_LMK5_CLKOUT_EN_REG               , DCB_LMK5_CLKOUT_EN_MASK               , DCB_LMK5_CLKOUT_EN_OFS               },
  { "LMK5_CLKOUT_DIV"              , DCB_LMK5_CLKOUT_DIV_REG              , DCB_LMK5_CLKOUT_DIV_MASK              , DCB_LMK5_CLKOUT_DIV_OFS              },
  { "LMK5_CLKOUT_DLY"              , DCB_LMK5_CLKOUT_DLY_REG              , DCB_LMK5_CLKOUT_DLY_MASK              , DCB_LMK5_CLKOUT_DLY_OFS              },
  { "LMK6_CLKOUT_MUX"              , DCB_LMK6_CLKOUT_MUX_REG              , DCB_LMK6_CLKOUT_MUX_MASK              , DCB_LMK6_CLKOUT_MUX_OFS              },
  { "LMK6_CLKOUT_EN"               , DCB_LMK6_CLKOUT_EN_REG               , DCB_LMK6_CLKOUT_EN_MASK               , DCB_LMK6_CLKOUT_EN_OFS               },
  { "LMK6_CLKOUT_DIV"              , DCB_LMK6_CLKOUT_DIV_REG              , DCB_LMK6_CLKOUT_DIV_MASK              , DCB_LMK6_CLKOUT_DIV_OFS              },
  { "LMK6_CLKOUT_DLY"              , DCB_LMK6_CLKOUT_DLY_REG              , DCB_LMK6_CLKOUT_DLY_MASK              , DCB_LMK6_CLKOUT_DLY_OFS              },
  { "LMK7_CLKOUT_MUX"              , DCB_LMK7_CLKOUT_MUX_REG              , DCB_LMK7_CLKOUT_MUX_MASK              , DCB_LMK7_CLKOUT_MUX_OFS              },
  { "LMK7_CLKOUT_EN"               , DCB_LMK7_CLKOUT_EN_REG               , DCB_LMK7_CLKOUT_EN_MASK               , DCB_LMK7_CLKOUT_EN_OFS               },
  { "LMK7_CLKOUT_DIV"              , DCB_LMK7_CLKOUT_DIV_REG              , DCB_LMK7_CLKOUT_DIV_MASK              , DCB_LMK7_CLKOUT_DIV_OFS              },
  { "LMK7_CLKOUT_DLY"              , DCB_LMK7_CLKOUT_DLY_REG              , DCB_LMK7_CLKOUT_DLY_MASK              , DCB_LMK7_CLKOUT_DLY_OFS              },
  { "LMK8_PHASE_NOISE_OPT"         , DCB_LMK8_PHASE_NOISE_OPT_REG         , DCB_LMK8_PHASE_NOISE_OPT_MASK         , DCB_LMK8_PHASE_NOISE_OPT_OFS         },
  { "LMK9_VBOOST"                  , DCB_LMK9_VBOOST_REG                  , DCB_LMK9_VBOOST_MASK                  , DCB_LMK9_VBOOST_OFS                  },
  { "LMK11_DIV4"                   , DCB_LMK11_DIV4_REG                   , DCB_LMK11_DIV4_MASK                   , DCB_LMK11_DIV4_OFS                   },
  { "LMK13_OSCIN_FREQ"             , DCB_LMK13_OSCIN_FREQ_REG             , DCB_LMK13_OSCIN_FREQ_MASK             , DCB_LMK13_OSCIN_FREQ_OFS             },
  { "LMK13_VCO_R4_LF"              , DCB_LMK13_VCO_R4_LF_REG              , DCB_LMK13_VCO_R4_LF_MASK              , DCB_LMK13_VCO_R4_LF_OFS              },
  { "LMK13_VCO_R3_LF"              , DCB_LMK13_VCO_R3_LF_REG              , DCB_LMK13_VCO_R3_LF_MASK              , DCB_LMK13_VCO_R3_LF_OFS              },
  { "LMK13_VCO_C3_C4_LF"           , DCB_LMK13_VCO_C3_C4_LF_REG           , DCB_LMK13_VCO_C3_C4_LF_MASK           , DCB_LMK13_VCO_C3_C4_LF_OFS           },
  { "LMK14_EN_FOUT"                , DCB_LMK14_EN_FOUT_REG                , DCB_LMK14_EN_FOUT_MASK                , DCB_LMK14_EN_FOUT_OFS                },
  { "LMK14_EN_CLKOUT_GLOBAL"       , DCB_LMK14_EN_CLKOUT_GLOBAL_REG       , DCB_LMK14_EN_CLKOUT_GLOBAL_MASK       , DCB_LMK14_EN_CLKOUT_GLOBAL_OFS       },
  { "LMK14_POWERDOWN"              , DCB_LMK14_POWERDOWN_REG              , DCB_LMK14_POWERDOWN_MASK              , DCB_LMK14_POWERDOWN_OFS              },
  { "LMK14_PLL_MUX"                , DCB_LMK14_PLL_MUX_REG                , DCB_LMK14_PLL_MUX_MASK                , DCB_LMK14_PLL_MUX_OFS                },
  { "LMK14_PLL_R"                  , DCB_LMK14_PLL_R_REG                  , DCB_LMK14_PLL_R_MASK                  , DCB_LMK14_PLL_R_OFS                  },
  { "LMK15_PLL_CP_GAIN"            , DCB_LMK15_PLL_CP_GAIN_REG            , DCB_LMK15_PLL_CP_GAIN_MASK            , DCB_LMK15_PLL_CP_GAIN_OFS            },
  { "LMK15_VCO_DIV"                , DCB_LMK15_VCO_DIV_REG                , DCB_LMK15_VCO_DIV_MASK                , DCB_LMK15_VCO_DIV_OFS                },
  { "LMK15_PLL_N"                  , DCB_LMK15_PLL_N_REG                  , DCB_LMK15_PLL_N_MASK                  , DCB_LMK15_PLL_N_OFS                  },
  { "TIME_LSB"                     , DCB_TIME_LSB_REG                     , DCB_TIME_LSB_MASK                     , DCB_TIME_LSB_OFS                     },
  { "TIME_MSB"                     , DCB_TIME_MSB_REG                     , DCB_TIME_MSB_MASK                     , DCB_TIME_MSB_OFS                     },
  { "TIME_LSB_SET"                 , DCB_TIME_LSB_SET_REG                 , DCB_TIME_LSB_SET_MASK                 , DCB_TIME_LSB_SET_OFS                 },
  { "TIME_MSB_SET"                 , DCB_TIME_MSB_SET_REG                 , DCB_TIME_MSB_SET_MASK                 , DCB_TIME_MSB_SET_OFS                 },
  { "EVENT_TX_RATE"                , DCB_EVENT_TX_RATE_REG                , DCB_EVENT_TX_RATE_MASK                , DCB_EVENT_TX_RATE_OFS                },
  { "EVENT_NUMBER"                 , DCB_EVENT_NUMBER_REG                 , DCB_EVENT_NUMBER_MASK                 , DCB_EVENT_NUMBER_OFS                 },
  { "EXT_TRIGGER_OUT_ENABLE"       , DCB_EXT_TRIGGER_OUT_ENABLE_REG       , DCB_EXT_TRIGGER_OUT_ENABLE_MASK       , DCB_EXT_TRIGGER_OUT_ENABLE_OFS       },
  { "SET_BIT_TRG_CFG"              , DCB_SET_BIT_TRG_CFG_REG              , DCB_SET_BIT_TRG_CFG_MASK              , DCB_SET_BIT_TRG_CFG_OFS              },
  { "CLR_BIT_TRG_CFG"              , DCB_CLR_BIT_TRG_CFG_REG              , DCB_CLR_BIT_TRG_CFG_MASK              , DCB_CLR_BIT_TRG_CFG_OFS              },
  { "AUTO_TRIGGER_PERIOD"          , DCB_AUTO_TRIGGER_PERIOD_REG          , DCB_AUTO_TRIGGER_PERIOD_MASK          , DCB_AUTO_TRIGGER_PERIOD_OFS          },
  { "TRB_FLAG_NEW"                 , DCB_TRB_FLAG_NEW_REG                 , DCB_TRB_FLAG_NEW_MASK                 , DCB_TRB_FLAG_NEW_OFS                 },
  { "TRB_FLAG_PARITY_ERROR"        , DCB_TRB_FLAG_PARITY_ERROR_REG        , DCB_TRB_FLAG_PARITY_ERROR_MASK        , DCB_TRB_FLAG_PARITY_ERROR_OFS        },
  { "TRB_PARITY_ERROR_COUNT"       , DCB_TRB_PARITY_ERROR_COUNT_REG       , DCB_TRB_PARITY_ERROR_COUNT_MASK       , DCB_TRB_PARITY_ERROR_COUNT_OFS       },
  { "TRB_INFO_LSB"                 , DCB_TRB_INFO_LSB_REG                 , DCB_TRB_INFO_LSB_MASK                 , DCB_TRB_INFO_LSB_OFS                 },
  { "TRB_INFO_MSB"                 , DCB_TRB_INFO_MSB_REG                 , DCB_TRB_INFO_MSB_MASK                 , DCB_TRB_INFO_MSB_OFS                 },
  { "LMK_7_MOD"                    , DCB_LMK_7_MOD_REG                    , DCB_LMK_7_MOD_MASK                    , DCB_LMK_7_MOD_OFS                    },
  { "LMK_6_MOD"                    , DCB_LMK_6_MOD_REG                    , DCB_LMK_6_MOD_MASK                    , DCB_LMK_6_MOD_OFS                    },
  { "LMK_5_MOD"                    , DCB_LMK_5_MOD_REG                    , DCB_LMK_5_MOD_MASK                    , DCB_LMK_5_MOD_OFS                    },
  { "LMK_4_MOD"                    , DCB_LMK_4_MOD_REG                    , DCB_LMK_4_MOD_MASK                    , DCB_LMK_4_MOD_OFS                    },
  { "LMK_3_MOD"                    , DCB_LMK_3_MOD_REG                    , DCB_LMK_3_MOD_MASK                    , DCB_LMK_3_MOD_OFS                    },
  { "LMK_2_MOD"                    , DCB_LMK_2_MOD_REG                    , DCB_LMK_2_MOD_MASK                    , DCB_LMK_2_MOD_OFS                    },
  { "LMK_1_MOD"                    , DCB_LMK_1_MOD_REG                    , DCB_LMK_1_MOD_MASK                    , DCB_LMK_1_MOD_OFS                    },
  { "LMK_0_MOD"                    , DCB_LMK_0_MOD_REG                    , DCB_LMK_0_MOD_MASK                    , DCB_LMK_0_MOD_OFS                    },
  { "CMB_MSCB_ADR"                 , DCB_CMB_MSCB_ADR_REG                 , DCB_CMB_MSCB_ADR_MASK                 , DCB_CMB_MSCB_ADR_OFS                 },
  { "SD_PKT_CNT_0"                 , DCB_SD_PKT_CNT_0_REG                 , DCB_SD_PKT_CNT_0_MASK                 , DCB_SD_PKT_CNT_0_OFS                 },
  { "SD_PKT_CNT_1"                 , DCB_SD_PKT_CNT_1_REG                 , DCB_SD_PKT_CNT_1_MASK                 , DCB_SD_PKT_CNT_1_OFS                 },
  { "SD_PKT_CNT_2"                 , DCB_SD_PKT_CNT_2_REG                 , DCB_SD_PKT_CNT_2_MASK                 , DCB_SD_PKT_CNT_2_OFS                 },
  { "SD_PKT_CNT_3"                 , DCB_SD_PKT_CNT_3_REG                 , DCB_SD_PKT_CNT_3_MASK                 , DCB_SD_PKT_CNT_3_OFS                 },
  { "SD_PKT_CNT_4"                 , DCB_SD_PKT_CNT_4_REG                 , DCB_SD_PKT_CNT_4_MASK                 , DCB_SD_PKT_CNT_4_OFS                 },
  { "SD_PKT_CNT_5"                 , DCB_SD_PKT_CNT_5_REG                 , DCB_SD_PKT_CNT_5_MASK                 , DCB_SD_PKT_CNT_5_OFS                 },
  { "SD_PKT_CNT_6"                 , DCB_SD_PKT_CNT_6_REG                 , DCB_SD_PKT_CNT_6_MASK                 , DCB_SD_PKT_CNT_6_OFS                 },
  { "SD_PKT_CNT_7"                 , DCB_SD_PKT_CNT_7_REG                 , DCB_SD_PKT_CNT_7_MASK                 , DCB_SD_PKT_CNT_7_OFS                 },
  { "SD_PKT_CNT_8"                 , DCB_SD_PKT_CNT_8_REG                 , DCB_SD_PKT_CNT_8_MASK                 , DCB_SD_PKT_CNT_8_OFS                 },
  { "SD_PKT_CNT_9"                 , DCB_SD_PKT_CNT_9_REG                 , DCB_SD_PKT_CNT_9_MASK                 , DCB_SD_PKT_CNT_9_OFS                 },
  { "SD_PKT_CNT_10"                , DCB_SD_PKT_CNT_10_REG                , DCB_SD_PKT_CNT_10_MASK                , DCB_SD_PKT_CNT_10_OFS                },
  { "SD_PKT_CNT_11"                , DCB_SD_PKT_CNT_11_REG                , DCB_SD_PKT_CNT_11_MASK                , DCB_SD_PKT_CNT_11_OFS                },
  { "SD_PKT_CNT_12"                , DCB_SD_PKT_CNT_12_REG                , DCB_SD_PKT_CNT_12_MASK                , DCB_SD_PKT_CNT_12_OFS                },
  { "SD_PKT_CNT_13"                , DCB_SD_PKT_CNT_13_REG                , DCB_SD_PKT_CNT_13_MASK                , DCB_SD_PKT_CNT_13_OFS                },
  { "SD_PKT_CNT_14"                , DCB_SD_PKT_CNT_14_REG                , DCB_SD_PKT_CNT_14_MASK                , DCB_SD_PKT_CNT_14_OFS                },
  { "SD_PKT_CNT_15"                , DCB_SD_PKT_CNT_15_REG                , DCB_SD_PKT_CNT_15_MASK                , DCB_SD_PKT_CNT_15_OFS                },
  { "SD_PKT_CNT_17"                , DCB_SD_PKT_CNT_17_REG                , DCB_SD_PKT_CNT_17_MASK                , DCB_SD_PKT_CNT_17_OFS                },
  { "CRC32_REG_BANK"               , DCB_CRC32_REG_BANK_REG               , DCB_CRC32_REG_BANK_MASK               , DCB_CRC32_REG_BANK_OFS               },
  { (const char*)0                 , 0                                    , 0                                     , 0                                    }
};

/******************************************************************************/
/* Register Restore                                                          */
/******************************************************************************/

const unsigned char reg_restore[] = {
  DCB_DONT_TOUCH_REG,   /* Offset 0x0000 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0004 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0008 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x000C */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0010 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0014 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0018 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x001C */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0020 */
  DCB_RESTORE_REG   ,   /* Offset 0x0024 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0028 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x002C */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0030 */
  DCB_RESTORE_REG   ,   /* Offset 0x0034 */
  DCB_RESTORE_REG   ,   /* Offset 0x0038 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x003C */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0040 */
  DCB_RESTORE_REG   ,   /* Offset 0x0044 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0048 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x004C */
  DCB_RESTORE_REG   ,   /* Offset 0x0050 */
  DCB_RESTORE_REG   ,   /* Offset 0x0054 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0058 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x005C */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0060 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0064 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0068 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x006C */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0070 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0074 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0078 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x007C */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0080 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0084 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0088 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x008C */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0090 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0094 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0098 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x009C */
  DCB_DONT_TOUCH_REG,   /* Offset 0x00A0 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x00A4 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x00A8 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x00AC */
  DCB_RESTORE_REG   ,   /* Offset 0x00B0 */
  DCB_RESTORE_REG   ,   /* Offset 0x00B4 */
  DCB_RESTORE_REG   ,   /* Offset 0x00B8 */
  DCB_RESTORE_REG   ,   /* Offset 0x00BC */
  DCB_RESTORE_REG   ,   /* Offset 0x00C0 */
  DCB_RESTORE_REG   ,   /* Offset 0x00C4 */
  DCB_RESTORE_REG   ,   /* Offset 0x00C8 */
  DCB_RESTORE_REG   ,   /* Offset 0x00CC */
  DCB_RESTORE_REG   ,   /* Offset 0x00D0 */
  DCB_RESTORE_REG   ,   /* Offset 0x00D4 */
  DCB_RESTORE_REG   ,   /* Offset 0x00D8 */
  DCB_RESTORE_REG   ,   /* Offset 0x00DC */
  DCB_RESTORE_REG   ,   /* Offset 0x00E0 */
  DCB_RESTORE_REG   ,   /* Offset 0x00E4 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x00E8 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x00EC */
  DCB_DONT_TOUCH_REG,   /* Offset 0x00F0 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x00F4 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x00F8 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x00FC */
  DCB_RESTORE_REG   ,   /* Offset 0x0100 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0104 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0108 */
  DCB_RESTORE_REG   ,   /* Offset 0x010C */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0110 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0114 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0118 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x011C */
  DCB_RESTORE_REG   ,   /* Offset 0x0120 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0124 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0128 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x012C */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0130 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0134 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0138 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x013C */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0140 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0144 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0148 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x014C */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0150 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0154 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0158 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x015C */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0160 */
  DCB_DONT_TOUCH_REG,   /* Offset 0x0164 */
  DCB_DONT_TOUCH_REG    /* Offset 0x0168 */
};


/******************************************************************************/
/* Register Defaults                                                          */
/******************************************************************************/

const unsigned int reg_default[] = {
  0xAC010307,   /* Offset 0x0000 */
  0x00000000,   /* Offset 0x0004 */
  0x00000000,   /* Offset 0x0008 */
  0x00000000,   /* Offset 0x000C */
  0x00000000,   /* Offset 0x0010 */
  0x00000000,   /* Offset 0x0014 */
  0x00000000,   /* Offset 0x0018 */
  0x00000000,   /* Offset 0x001C */
  0x00000000,   /* Offset 0x0020 */
  0x00000000,   /* Offset 0x0024 */
  0x00000000,   /* Offset 0x0028 */
  0x00000000,   /* Offset 0x002C */
  0x00000000,   /* Offset 0x0030 */
  0xFFFFFFFF,   /* Offset 0x0034 */
  0x00000000,   /* Offset 0x0038 */
  0x00000000,   /* Offset 0x003C */
  0x00000000,   /* Offset 0x0040 */
  0xFFFFC00E,   /* Offset 0x0044 */
  0x00000000,   /* Offset 0x0048 */
  0x00000000,   /* Offset 0x004C */
  0x00000753,   /* Offset 0x0050 */
  0x0001FFFF,   /* Offset 0x0054 */
  0x00000000,   /* Offset 0x0058 */
  0x00000000,   /* Offset 0x005C */
  0x00000000,   /* Offset 0x0060 */
  0x00000000,   /* Offset 0x0064 */
  0x00000000,   /* Offset 0x0068 */
  0x00000000,   /* Offset 0x006C */
  0x00000000,   /* Offset 0x0070 */
  0x00000000,   /* Offset 0x0074 */
  0x00000000,   /* Offset 0x0078 */
  0x00000000,   /* Offset 0x007C */
  0x00000000,   /* Offset 0x0080 */
  0x00000000,   /* Offset 0x0084 */
  0x00000000,   /* Offset 0x0088 */
  0x00000000,   /* Offset 0x008C */
  0x00000000,   /* Offset 0x0090 */
  0x00000000,   /* Offset 0x0094 */
  0x00000000,   /* Offset 0x0098 */
  0x00000000,   /* Offset 0x009C */
  0x00000000,   /* Offset 0x00A0 */
  0x00000000,   /* Offset 0x00A4 */
  0x00000000,   /* Offset 0x00A8 */
  0x00000000,   /* Offset 0x00AC */
  0x00020100,   /* Offset 0x00B0 */
  0x00030101,   /* Offset 0x00B4 */
  0x00020102,   /* Offset 0x00B8 */
  0x00020103,   /* Offset 0x00BC */
  0x00000104,   /* Offset 0x00C0 */
  0x00000105,   /* Offset 0x00C4 */
  0x00000106,   /* Offset 0x00C8 */
  0x00000107,   /* Offset 0x00CC */
  0x10000908,   /* Offset 0x00D0 */
  0xA0022A09,   /* Offset 0x00D4 */
  0x0082000B,   /* Offset 0x00D8 */
  0x029400AD,   /* Offset 0x00DC */
  0x0830140E,   /* Offset 0x00E0 */
  0xE000280F,   /* Offset 0x00E4 */
  0x00000000,   /* Offset 0x00E8 */
  0x00000000,   /* Offset 0x00EC */
  0x00000000,   /* Offset 0x00F0 */
  0x00000000,   /* Offset 0x00F4 */
  0x00000000,   /* Offset 0x00F8 */
  0x00000000,   /* Offset 0x00FC */
  0x00000000,   /* Offset 0x0100 */
  0x00000000,   /* Offset 0x0104 */
  0x00000000,   /* Offset 0x0108 */
  0x04C4B400,   /* Offset 0x010C */
  0x00000000,   /* Offset 0x0110 */
  0x00000000,   /* Offset 0x0114 */
  0x00000000,   /* Offset 0x0118 */
  0x00000000,   /* Offset 0x011C */
  0x00000000,   /* Offset 0x0120 */
  0x00000000,   /* Offset 0x0124 */
  0x00000000,   /* Offset 0x0128 */
  0x00000000,   /* Offset 0x012C */
  0x00000000,   /* Offset 0x0130 */
  0x00000000,   /* Offset 0x0134 */
  0x00000000,   /* Offset 0x0138 */
  0x00000000,   /* Offset 0x013C */
  0x00000000,   /* Offset 0x0140 */
  0x00000000,   /* Offset 0x0144 */
  0x00000000,   /* Offset 0x0148 */
  0x00000000,   /* Offset 0x014C */
  0x00000000,   /* Offset 0x0150 */
  0x00000000,   /* Offset 0x0154 */
  0x00000000,   /* Offset 0x0158 */
  0x00000000,   /* Offset 0x015C */
  0x00000000,   /* Offset 0x0160 */
  0x00000000    /* Offset 0x0164 */
};

#endif /* DCB_DONT_INCLUDE_VARS */


/******************************************************************************/

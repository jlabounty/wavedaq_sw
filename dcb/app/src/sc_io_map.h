/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  MEGII - DCB
 *
 *  Author  :  schmid_e (Author of generation script)
 *  Created :  03.05.2019 15:45:07
 *
 *  Description :  Slow Control IO definitions.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#ifndef __SC_IO_MAP_H__
#define __SC_IO_MAP_H__

/* Registers */
/*#define SYS_GPIO_OUT                                    1 */
/*#define SYS_GPIO_IN                                     2 */

/* EMIO Banks */
#define EMIO_CTRL_OFFSET                                0
#define EMIO_STAT_OFFSET                               52


/* Bit indices */
/*   AXI MIO GPIO   */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000001 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                    0 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                       0 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000002 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                    1 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                       1 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000004 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                    2 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                       2 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000008 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                    3 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                       3 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000010 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                    4 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                       4 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000020 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                    5 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                       5 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000040 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                    6 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                       6 */
#define BIT_IDX_AXI_CTRL_MIO_LED_MASK              0x00000080
#define BIT_IDX_AXI_CTRL_MIO_LED_OFFSET                     7
#define BIT_IDX_AXI_CTRL_MIO_LED_PIN                        7
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000100 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                    8 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                       8 */
#define BIT_IDX_AXI_SI_RESET_RESERVED_MASK         0x00000200
#define BIT_IDX_AXI_SI_RESET_RESERVED_OFFSET                9
#define BIT_IDX_AXI_SI_RESET_RESERVED_PIN                   9
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000400 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   10 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      10 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000800 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   11 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      11 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00001000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   12 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      12 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00002000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   13 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      13 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00004000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   14 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      14 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00008000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   15 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      15 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00010000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   16 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      16 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00020000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   17 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      17 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00040000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   18 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      18 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00080000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   19 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      19 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00100000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   20 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      20 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00200000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   21 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      21 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00400000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   22 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      22 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00800000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   23 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      23 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x01000000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   24 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      24 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x02000000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   25 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      25 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x04000000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   26 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      26 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x08000000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   27 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      27 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x10000000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   28 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      28 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x20000000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   29 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      29 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x40000000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   30 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      30 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x80000000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   31 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      31 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000001 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                    0 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      32 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000002 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                    1 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      33 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000004 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                    2 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      34 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000008 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                    3 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      35 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000010 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                    4 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      36 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000020 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                    5 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      37 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000040 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                    6 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      38 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000080 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                    7 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      39 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000100 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                    8 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      40 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000200 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                    9 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      41 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000400 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   10 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      42 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00000800 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   11 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      43 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00001000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   12 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      44 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00002000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   13 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      45 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00004000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   14 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      46 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00008000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   15 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      47 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00010000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   16 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      48 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00020000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   17 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      49 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00040000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   18 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      50 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00080000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   19 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      51 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00100000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   20 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      52 */
/*#define BIT_IDX_AXI_...._RESERVED_MASK             0x00200000 */
/*#define BIT_IDX_AXI_...._RESERVED_OFFSET                   21 */
/*#define BIT_IDX_AXI_...._RESERVED_PIN                      53 */



/*   EMIO GPIO   */
#define BIT_IDX_EMIO_CTRL_INIT_MASK                  0x00000001
#define BIT_IDX_EMIO_CTRL_INIT_OFFSET                         0
#define BIT_IDX_EMIO_CTRL_INIT_PIN                           54
#define BIT_IDX_EMIO_CTRL_FLASH_SEL_MASK             0x00000002
#define BIT_IDX_EMIO_CTRL_FLASH_SEL_OFFSET                    1
#define BIT_IDX_EMIO_CTRL_FLASH_SEL_PIN                      55
#define BIT_IDX_EMIO_CTRL_BPL_SPI_SCHEME_MASK        0x00000004
#define BIT_IDX_EMIO_CTRL_BPL_SPI_SCHEME_OFFSET               2
#define BIT_IDX_EMIO_CTRL_BPL_SPI_SCHEME_PIN                 56
#define BIT_IDX_EMIO_CTRL_MASTER_SPI_DE_MASK         0x00000008
#define BIT_IDX_EMIO_CTRL_MASTER_SPI_DE_OFFSET                3
#define BIT_IDX_EMIO_CTRL_MASTER_SPI_DE_PIN                  57
/*#define BIT_IDX_EMIO_CTRL_RESERVED_MASK              0x00000010 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_OFFSET                     4 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_PIN                       58*/
/*#define BIT_IDX_EMIO_CTRL_RESERVED_MASK              0x00000020 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_OFFSET                     5 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_PIN                       59 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_MASK              0x00000040 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_OFFSET                     6 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_PIN                       60 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_MASK              0x00000080 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_OFFSET                     7 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_PIN                       61 */
#define BIT_IDX_EMIO_CTRL_SFP1_RS0_MASK              0x00000100
#define BIT_IDX_EMIO_CTRL_SFP1_RS0_OFFSET                     8
#define BIT_IDX_EMIO_CTRL_SFP1_RS0_PIN                       62
#define BIT_IDX_EMIO_CTRL_SFP1_RS1_MASK              0x00000200
#define BIT_IDX_EMIO_CTRL_SFP1_RS1_OFFSET                     9
#define BIT_IDX_EMIO_CTRL_SFP1_RS1_PIN                       63
#define BIT_IDX_EMIO_CTRL_SFP1_DISABLE_MASK          0x00000400
#define BIT_IDX_EMIO_CTRL_SFP1_DISABLE_OFFSET                10
#define BIT_IDX_EMIO_CTRL_SFP1_DISABLE_PIN                   64
#define BIT_IDX_EMIO_CTRL_ETH0_RST_MASK              0x00000800
#define BIT_IDX_EMIO_CTRL_ETH0_RST_OFFSET                    11
#define BIT_IDX_EMIO_CTRL_ETH0_RST_PIN                       65
#define BIT_IDX_EMIO_CTRL_SFP2_RS0_MASK              0x00001000
#define BIT_IDX_EMIO_CTRL_SFP2_RS0_OFFSET                    12
#define BIT_IDX_EMIO_CTRL_SFP2_RS0_PIN                       66
#define BIT_IDX_EMIO_CTRL_SFP2_RS1_MASK              0x00002000
#define BIT_IDX_EMIO_CTRL_SFP2_RS1_OFFSET                    13
#define BIT_IDX_EMIO_CTRL_SFP2_RS1_PIN                       67
#define BIT_IDX_EMIO_CTRL_SFP2_DISABLE_MASK          0x00004000
#define BIT_IDX_EMIO_CTRL_SFP2_DISABLE_OFFSET                14
#define BIT_IDX_EMIO_CTRL_SFP2_DISABLE_PIN                   68
#define BIT_IDX_EMIO_CTRL_ETH1_RST_MASK              0x00008000
#define BIT_IDX_EMIO_CTRL_ETH1_RST_OFFSET                    15
#define BIT_IDX_EMIO_CTRL_ETH1_RST_PIN                       69

#define SW_STATE_OFFSET                                      70

#define BIT_IDX_EMIO_CTRL_SW_STATE_DCB_ACCESS_MASK   0x00010000
#define BIT_IDX_EMIO_CTRL_SW_STATE_DCB_ACCESS_OFFSET         16
#define BIT_IDX_EMIO_CTRL_SW_STATE_DCB_ACCESS_PIN            70
#define BIT_IDX_EMIO_CTRL_SW_STATE_SW_UPDATE_MASK    0x00020000
#define BIT_IDX_EMIO_CTRL_SW_STATE_SW_UPDATE_OFFSET          17
#define BIT_IDX_EMIO_CTRL_SW_STATE_SW_UPDATE_PIN             71
#define BIT_IDX_EMIO_CTRL_SW_STATE_FW_UPDATE_MASK    0x00040000
#define BIT_IDX_EMIO_CTRL_SW_STATE_FW_UPDATE_OFFSET          18
#define BIT_IDX_EMIO_CTRL_SW_STATE_FW_UPDATE_PIN             72
#define BIT_IDX_EMIO_CTRL_SW_STATE_SW_READY_MASK     0x00080000
#define BIT_IDX_EMIO_CTRL_SW_STATE_SW_READY_OFFSET           19
#define BIT_IDX_EMIO_CTRL_SW_STATE_SW_READY_PIN              73
#define BIT_IDX_EMIO_CTRL_SW_STATE_BL_FAIL_MASK      0x00100000
#define BIT_IDX_EMIO_CTRL_SW_STATE_BL_FAIL_OFFSET            20
#define BIT_IDX_EMIO_CTRL_SW_STATE_BL_FAIL_PIN               74
#define BIT_IDX_EMIO_CTRL_SW_STATE_DHCP_REQ_MASK     0x00200000
#define BIT_IDX_EMIO_CTRL_SW_STATE_DHCP_REQ_OFFSET           21
#define BIT_IDX_EMIO_CTRL_SW_STATE_DHCP_REQ_PIN              75
#define BIT_IDX_EMIO_CTRL_SW_STATE_MARKER_MASK       0x00400000
#define BIT_IDX_EMIO_CTRL_SW_STATE_MARKER_OFFSET             22
#define BIT_IDX_EMIO_CTRL_SW_STATE_MARKER_PIN                76
#define BIT_IDX_EMIO_CTRL_SW_STATE_ERROR_MASK        0x00800000
#define BIT_IDX_EMIO_CTRL_SW_STATE_ERROR_OFFSET              23
#define BIT_IDX_EMIO_CTRL_SW_STATE_ERROR_PIN                 77

/*#define BIT_IDX_EMIO_CTRL_RESERVED_MASK              0x01000000 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_OFFSET                    24 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_PIN                       78 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_MASK              0x02000000 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_OFFSET                    25 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_PIN                       79 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_MASK              0x04000000 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_OFFSET                    26 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_PIN                       80 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_MASK              0x08000000 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_OFFSET                    27 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_PIN                       81 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_MASK              0x10000000 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_OFFSET                    28 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_PIN                       82 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_MASK              0x20000000 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_OFFSET                    29 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_PIN                       83 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_MASK              0x40000000 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_OFFSET                    30 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_PIN                       84 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_MASK              0x80000000 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_OFFSET                    31 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_PIN                       85 */

#define BOARD_SEL_OFFSET                                     86

#define BIT_IDX_EMIO_CTRL_BOARD_SEL0_MASK            0x00000001
#define BIT_IDX_EMIO_CTRL_BOARD_SEL0_OFFSET                   0
#define BIT_IDX_EMIO_CTRL_BOARD_SEL0_PIN                     86
#define BIT_IDX_EMIO_CTRL_BOARD_SEL1_MASK            0x00000002
#define BIT_IDX_EMIO_CTRL_BOARD_SEL1_OFFSET                   1
#define BIT_IDX_EMIO_CTRL_BOARD_SEL1_PIN                     87
#define BIT_IDX_EMIO_CTRL_BOARD_SEL2_MASK            0x00000004
#define BIT_IDX_EMIO_CTRL_BOARD_SEL2_OFFSET                   2
#define BIT_IDX_EMIO_CTRL_BOARD_SEL2_PIN                     88
#define BIT_IDX_EMIO_CTRL_BOARD_SEL3_MASK            0x00000008
#define BIT_IDX_EMIO_CTRL_BOARD_SEL3_OFFSET                   3
#define BIT_IDX_EMIO_CTRL_BOARD_SEL3_PIN                     89
#define BIT_IDX_EMIO_CTRL_BOARD_SEL4_MASK            0x00000010
#define BIT_IDX_EMIO_CTRL_BOARD_SEL4_OFFSET                   4
#define BIT_IDX_EMIO_CTRL_BOARD_SEL4_PIN                     90
#define BIT_IDX_EMIO_CTRL_BOARD_SEL5_MASK            0x00000020
#define BIT_IDX_EMIO_CTRL_BOARD_SEL5_OFFSET                   5
#define BIT_IDX_EMIO_CTRL_BOARD_SEL5_PIN                     91
#define BIT_IDX_EMIO_CTRL_BOARD_SEL6_MASK            0x00000040
#define BIT_IDX_EMIO_CTRL_BOARD_SEL6_OFFSET                   6
#define BIT_IDX_EMIO_CTRL_BOARD_SEL6_PIN                     92
#define BIT_IDX_EMIO_CTRL_BOARD_SEL7_MASK            0x00000080
#define BIT_IDX_EMIO_CTRL_BOARD_SEL7_OFFSET                   7
#define BIT_IDX_EMIO_CTRL_BOARD_SEL7_PIN                     93
#define BIT_IDX_EMIO_CTRL_BOARD_SEL8_MASK            0x00000100
#define BIT_IDX_EMIO_CTRL_BOARD_SEL8_OFFSET                   8
#define BIT_IDX_EMIO_CTRL_BOARD_SEL8_PIN                     94
#define BIT_IDX_EMIO_CTRL_BOARD_SEL9_MASK            0x00000200
#define BIT_IDX_EMIO_CTRL_BOARD_SEL9_OFFSET                   9
#define BIT_IDX_EMIO_CTRL_BOARD_SEL9_PIN                     95
#define BIT_IDX_EMIO_CTRL_BOARD_SEL10_MASK           0x00000400
#define BIT_IDX_EMIO_CTRL_BOARD_SEL10_OFFSET                 10
#define BIT_IDX_EMIO_CTRL_BOARD_SEL10_PIN                    96
#define BIT_IDX_EMIO_CTRL_BOARD_SEL11_MASK           0x00000800
#define BIT_IDX_EMIO_CTRL_BOARD_SEL11_OFFSET                 11
#define BIT_IDX_EMIO_CTRL_BOARD_SEL11_PIN                    97
#define BIT_IDX_EMIO_CTRL_BOARD_SEL12_MASK           0x00001000
#define BIT_IDX_EMIO_CTRL_BOARD_SEL12_OFFSET                 12
#define BIT_IDX_EMIO_CTRL_BOARD_SEL12_PIN                    98
#define BIT_IDX_EMIO_CTRL_BOARD_SEL13_MASK           0x00002000
#define BIT_IDX_EMIO_CTRL_BOARD_SEL13_OFFSET                 13
#define BIT_IDX_EMIO_CTRL_BOARD_SEL13_PIN                    99
#define BIT_IDX_EMIO_CTRL_BOARD_SEL14_MASK           0x00004000
#define BIT_IDX_EMIO_CTRL_BOARD_SEL14_OFFSET                 14
#define BIT_IDX_EMIO_CTRL_BOARD_SEL14_PIN                   100
#define BIT_IDX_EMIO_CTRL_BOARD_SEL15_MASK           0x00008000
#define BIT_IDX_EMIO_CTRL_BOARD_SEL15_OFFSET                 15
#define BIT_IDX_EMIO_CTRL_BOARD_SEL15_PIN                   101
#define BIT_IDX_EMIO_CTRL_BOARD_SEL16_MASK           0x00010000
#define BIT_IDX_EMIO_CTRL_BOARD_SEL16_OFFSET                 16
#define BIT_IDX_EMIO_CTRL_BOARD_SEL16_PIN                   102
/*#define BIT_IDX_EMIO_CTRL_RESERVED_MASK              0x00020000 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_OFFSET                    17 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_PIN                      103 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_MASK              0x00040000 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_OFFSET                    18 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_PIN                      104 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_MASK              0x00080000 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_OFFSET                    19 */
/*#define BIT_IDX_EMIO_CTRL_RESERVED_PIN                      105 */

#define BIT_IDX_EMIO_STAT_FS_INIT_MASK               0x00100000
#define BIT_IDX_EMIO_STAT_FS_INIT_OFFSET                     20
#define BIT_IDX_EMIO_STAT_FS_INIT_PIN                       106
#define BIT_IDX_EMIO_STAT_SPI_CS_MASK                0x00200000
#define BIT_IDX_EMIO_STAT_SPI_CS_OFFSET                      21
#define BIT_IDX_EMIO_STAT_SPI_CS_PIN                        107
#define BIT_IDX_EMIO_STAT_BOARD_SEL_MASK             0x00400000
#define BIT_IDX_EMIO_STAT_BOARD_SEL_OFFSET                   22
#define BIT_IDX_EMIO_STAT_BOARD_SEL_PIN                     108
/* The last eight are controlled by the ethernet/SFP driver */
/*#define BIT_IDX_EMIO_STAT_RESERVED_MASK              0x00800000 */
/*#define BIT_IDX_EMIO_STAT_RESERVED_OFFSET                    23 */
/*#define BIT_IDX_EMIO_STAT_RESERVED_PIN                      109 */
/*#define BIT_IDX_EMIO_STAT_SFP1_TX_FAULT_MASK         0x01000000 */
/*#define BIT_IDX_EMIO_STAT_SFP1_TX_FAULT_OFFSET               24 */
/*#define BIT_IDX_EMIO_STAT_SFP1_TX_FAULT_PIN                 110 */
/*#define BIT_IDX_EMIO_STAT_SFP1_MOD_MASK              0x02000000 */
/*#define BIT_IDX_EMIO_STAT_SFP1_MOD_OFFSET                    25 */
/*#define BIT_IDX_EMIO_STAT_SFP1_MOD_PIN                      111 */
/*#define BIT_IDX_EMIO_STAT_SFP1_LOS_MASK              0x04000000 */
/*#define BIT_IDX_EMIO_STAT_SFP1_LOS_OFFSET                    26 */
/*#define BIT_IDX_EMIO_STAT_SFP1_LOS_PIN                      112 */
/*#define BIT_IDX_EMIO_STAT_RESERVED_MASK              0x08000000 */
/*#define BIT_IDX_EMIO_STAT_RESERVED_OFFSET                    27 */
/*#define BIT_IDX_EMIO_STAT_RESERVED_PIN                      113 */
/*#define BIT_IDX_EMIO_STAT_SFP2_TX_FAULT_MASK         0x10000000 */
/*#define BIT_IDX_EMIO_STAT_SFP2_TX_FAULT_OFFSET               28 */
/*#define BIT_IDX_EMIO_STAT_SFP2_TX_FAULT_PIN                 114 */
/*#define BIT_IDX_EMIO_STAT_SFP2_MOD_MASK              0x20000000 */
/*#define BIT_IDX_EMIO_STAT_SFP2_MOD_OFFSET                    29 */
/*#define BIT_IDX_EMIO_STAT_SFP2_MOD_PIN                      115 */
/*#define BIT_IDX_EMIO_STAT_SFP2_LOS_MASK              0x40000000 */
/*#define BIT_IDX_EMIO_STAT_SFP2_LOS_OFFSET                    30 */
/*#define BIT_IDX_EMIO_STAT_SFP2_LOS_PIN                      116 */
/*#define BIT_IDX_EMIO_STAT_RESERVED_MASK              0x80000000 */
/*#define BIT_IDX_EMIO_STAT_RESERVED_OFFSET                    31 */
/*#define BIT_IDX_EMIO_STAT_RESERVED_PIN                      117 */

#endif /* __SC_IO_MAP_H__ */

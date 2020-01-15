/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  MEG - DCB
 *
 *  Author  :  schmid_e
 *  Created :  21.09.2018 09:29:35
 *
 *  Description :  Central control for hardware access.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "drv_axi_dcb_reg_bank.h"
#include "drv_lmk.h"
#include "drv_sys_mon.h"
#include "drv_si5324.h"
#include "drv_bpl.h"

#ifndef LINUX_COMPILE
#include "term_cmd_input.h"
#include "xqspips.h"
#include "xiicps.h"
#include "sfp_ctrl.h"
#include "xspips.h"
#include "xgpiops.h"
#include "fw_env.h"
#include "xemacps.h"
#endif

/******************************************************************************/

#define STDOUT_IS_PS7_UART
#define UART_DEVICE_ID 0

#define MAX_HOSTNAME_LENGTH  62

#define SYSPTR(x) (&(system_hw.x))

/* ENVIRONMENT STORAGE */
#define ENV_STORAGE_ENTRIES     2

#define SFP_IIC_SCLK_RATE               100000   /* Hz */
/* Max. for Finisar FCLF8521-3 is 100kHz */

/* SPI Devices */
#define SPI_DEV_BPL                          1
#define SPI_DEV_ECLK_LMK_ADC                 2

/* SPI Slaves */
/* Device 1 */
#define SPI_SLAVE_SLOT_FPGA                  0
#define SPI_SLAVE_SLOT_WDB_FLASH             1
#define SPI_SLAVE_SLOT_TCB_FLASH             2
/* Device 2 */
#define SPI_SLAVE_NR_SI3524                  0
#define SPI_SLAVE_NR_LMK                     1
#define SPI_SLAVE_NR_SYS_MON                 2

/* Board Type IDs */
#define BRD_TYPE_ID_WDB    0
#define BRD_TYPE_ID_TCB    1
#define BRD_TYPE_ID_DCB    2

/* DCB Board Revision IDs */
#define DCB_BRD_REV_ID_A   0
#define DCB_BRD_REV_ID_B   1
/* WDB Board Revision IDs */
#define WDB_BRD_REV_ID_C   2
#define WDB_BRD_REV_ID_D   3
#define WDB_BRD_REV_ID_E   4
#define WDB_BRD_REV_ID_F   5
#define WDB_BRD_REV_ID_G   6
#define WDB_BRD_REV_ID_H   7
/* TCB Board Revision IDs */
#define TCB_BRD_REV_ID_1   1
#define TCB_BRD_REV_ID_2   2
#define TCB_BRD_REV_ID_3   3


#ifdef LINUX_COMPILE
/* Flash MTDs */
#define MTD_WDB_FLASH_BITSTREAM   "/dev/mtd0"
#define MTD_WDB_FLASH_SOFTWARE    "/dev/mtd1"
#define MTD_WDB_FLASH_RESERVED    "/dev/mtd2"
#define MTD_TCB_FLASH_BITSTREAM   "/dev/mtd3"
#define MTD_QSPI_FLASH_HEADER     "/dev/mtd4"
#define MTD_QSPI_FLASH_REGCONTENT "/dev/mtd5"
#define MTD_QSPI_FLASH_FSBL       "/dev/mtd6"
#define MTD_QSPI_FLASH_BITSTREAM  "/dev/mtd7"
#define MTD_QSPI_FLASH_RESERVED   "/dev/mtd8"
#define MTD_QSPI_FLASH_ENV        "/dev/mtdf"
#endif

/******************************************************************************/
/* System Environment                                                         */
/******************************************************************************/

/* environment type */
typedef struct
{
  unsigned int   serial_no;
  char           hostname[MAX_HOSTNAME_LENGTH];
  unsigned int   nw_data_src_port;
} sys_cfg_type;

/******************************************************************************/

typedef struct
{
  //XSpi                       spi_bpl;      /* SPI connection to backplane (WDB, TCB) */
  bpl_spi_type               spi_bpl;      /* SPI connection to backplane (WDB, TCB) */
  axi_dcb_register_bank      reg_bank;
  lmk_ctrl_type              lmk;
  sysmon_ctrl_type           sys_mon;
  si5324_ctrl_type           si5324;
#ifndef LINUX_COMPILE
  term_cmd_input_type        term_stdin;   /* Std input terminal */
  XEmacPs                    emac_0;       /* ETH0 MAC */
  XGpioPs                    gpio_mio;	   /* GPIO for MIO pins */
  XQspiPs                    spi_flash;    /* DCB SPI flash memory */
  XIicPs                     iic_sfp[2];   /* I2C control link for SFP 1&2 */
  sfp_ctrl_type              sfp_ctrl[2];  /* Controller for SFP 1&2 */
  XSpiPs                     spi_eclk_lmk_adc;
  fw_env_storage_desc_type   env_storage_description[ENV_STORAGE_ENTRIES];
  fw_env_type                env;          /* Firmware environment */
  sys_cfg_type               cfg;          /* Basic system configuration */
#endif
} system_type;

extern system_type system_hw;

extern const char wdb_rf_default_path[];
extern const char wdb_rg_default_path[];
extern const char tcb_t1_default_path[];
extern const char tcb_t2_default_path[];
extern const char tcb_t3_default_path[];

extern const char wdb_fw_default_file[];
extern const char wdb_sw_default_file[];
extern const char tcb_fw_default_file[];

extern const unsigned int bpl_spi_scheme[2][8];

int init_system();
void init_spi_bpl();
void init_reg_bank();
void init_lmk03000();
void init_si5324();
void init_sysmon();
void init_gpio_mio();
void init_settings(int snr);
void init_env_settings(int snr);
void init_reg_settings(int snr);
void print_sys_info(void);
int get_serial_number();
int is_dir(char* path);
int is_file(char* path);
void byte_swap_uint32(unsigned int* src, unsigned int* dst, unsigned int len);
void display_progress(char* prefix, xfs_u32 percent, char idle_char, char prog_char);

#endif /* __SYSTEM_H__ */

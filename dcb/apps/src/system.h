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

#include "xspi.h"
#include "drv_axi_dcb_reg_bank.h"

#ifndef LINUX_COMPILE
#include "term_cmd_input.h"
#include "drv_lmk.h"
#include "drv_si5324.h"
#include "drv_sys_mon.h"
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

/* SPI Slaves */
#define SPI_SLAVE_NR_SI3524                  0
#define SPI_SLAVE_NR_LMK                     1
#define SPI_SLAVE_NR_SYS_MON                 2

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
  XSpi                       spi_bpl;      /* SPI connection to backplane (WDB, TCB) */
  axi_dcb_register_bank      reg_bank;
#ifndef LINUX_COMPILE
  term_cmd_input_type        term_stdin;   /* Std input terminal */
  lmk_ctrl_type              lmk;
  si5324_ctrl_type           si5324;
  sysmon_ctrl_type           sys_mon;
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

int init_system();
int init_spi_bpl();
void init_reg_bank();
void init_settings(int snr);
void init_env_settings(int snr);
void init_reg_settings(int snr);
void print_sys_info(void);

#endif /* __SYSTEM_H__ */

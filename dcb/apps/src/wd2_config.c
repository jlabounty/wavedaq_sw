/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WaveDream2
 *
 *  Author  :  schmid_e, theidel
 *  Created :  24.04.2014 11:53:05
 *
 *  Description :  Structure of table to list names of implemented commands that can be
 *                 interpreted plus a pointer to the function to be called by this
 *                 command.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */
#include "cmd_processor.h"
#include "wd2_config.h"



extern cmd_table_entry_type adc_cmd_table[];
extern cmd_table_entry_type dac_cmd_table[];
extern cmd_table_entry_type drp_pll_cmd_table[];
extern cmd_table_entry_type drs4_control_cmd_table[];
extern cmd_table_entry_type ext_mem_cmd_table[];
extern cmd_table_entry_type frontend_shiftreg_cmd_table[];
extern cmd_table_entry_type fw_env_cmd_table[];
extern cmd_table_entry_type gmac_cmd_table[];
extern cmd_table_entry_type hv_dac_adc_cmd_table[];
extern cmd_table_entry_type status_cmd_table[];
extern cmd_table_entry_type led_cmd_table[];
extern cmd_table_entry_type ll_cmd_table[];
extern cmd_table_entry_type lmk_cmd_table[];
extern cmd_table_entry_type pn_test_cmd_table[];
extern cmd_table_entry_type reg_access_cmd_table[];
extern cmd_table_entry_type spi_flash_cmd_table[];
extern cmd_table_entry_type gpio_mio_cmd_table[];
extern cmd_table_entry_type system_management_cmd_table[];
extern cmd_table_entry_type crate_com_cmd_table[];



  /* Main command table collecting sub command */
  /* tables of modules */
  cmd_table_entry_type *cmd_list[] =
  {
#if CFG_INCLUDE_INFO
    status_cmd_table,
#endif
#if CFG_INCLUDE_DCB_REG_ACCESS
    reg_access_cmd_table,
#endif
#if CFG_INCLUDE_FW_ENV
    fw_env_cmd_table,
#endif
#if CFG_INCLUDE_SPI_FLASH
  spi_flash_cmd_table,
#endif
#if CFG_INCLUDE_GPIO_MIO
  gpio_mio_cmd_table,
#endif
//#if CFG_INCLUDE_SPI_SYSLINK_TEST
//    spi_syslink_test_cmd_table,
//#endif
//#if CFG_INCLUDE_LMK
//    lmk_cmd_table,
//#endif
#if CFG_INCLUDE_LED_CONTROL
    led_cmd_table,
#endif
//#if CFG_INCLUDE_EXT_MEMORY
//    ext_mem_cmd_table,
//#endif
#if CFG_INCLUDE_SYSTEM_MANAGEMENT
    system_management_cmd_table,
#endif
//#if CFG_INCLUDE_GMAC
//    gmac_cmd_table,
//#endif
#if CFG_INCLUDE_CRATE_COM
    crate_com_cmd_table,
#endif
#if CFG_INCLUDE_HELP
    cmd_table_cmd_proc,
#endif
    0
  };

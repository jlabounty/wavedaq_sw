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

/* system init cache */
/* see hello world app */

#include "system.h"
#include "xparameters.h"
#include "xfs_printf.h"
#include "dbg.h"
#include "xstatus.h"
#include "sc_io.h"
#include "register_map_dcb.h"
#include "../../../../git-revision.h"
#ifndef LINUX_COMPILE
#include "sw_state.h"
#include "drv_qspi_flash.h"
#include "dcb_flash_memory_map.h"
#endif

/******************************************************************************/

#ifdef STDOUT_IS_16550
 #include "xuartns550_l.h"

 #define UART_BAUD 9600
#endif

/******************************************************************************/
/* global vars                                                                */
/******************************************************************************/

system_type system_hw;

const char system_sw_build_date[] = __DATE__;
const char system_sw_build_time[] = __TIME__;
const char *system_month_str[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

#ifdef LINUX_COMPILE
static int sys_mon_initialized  = 0;
static int lmk03000_initialized = 0;
static int si5324_initialized   = 0;
static int reg_bank_initialized = 0;
#endif /* LINUX_COMPILE */

/******************************************************************************/

unsigned int reg_sw_build_date()
{
 /* STATUS REGISTERS SW_BUILD_DATE            Read only Register */
 /* */
/*  31:16 sw_build_year  unsigned int16, Year of the DCB software build Encoded as packed BCD */
/*  15:8  sw_build_month unsigned int8, Month of the DCB software build Encoded as packed BCD */
/*  7:0   sw_build_day   unsigned int8, Day of the DCB software build   Encoded as packed BCD */

  const char *s = system_sw_build_date;
  int m;

  for(m=1; m<=12; m++) if (fstrpcmp(system_month_str[m-1], s)) break;

  return ( ((s[7]-'0')<<28) | ((s[8]-'0')<<24) | ((s[9]-'0')<<20) | ((s[10]-'0')<<16) /* Year  */
         | ((m/10)<<12) | ((m%10)<<8)                     /* Month */
         | ((s[4]==' ')?0:(s[4]-'0')<<4) | (s[5]-'0') );  /* Day   */
}

/******************************************************************************/

unsigned int reg_sw_build_time()
{
 /* STATUS REGISTERS SW_BUILD_TIME            Read only Register */
 /* */
/*  31:24 reserved                                                                   */
/*  23:16 sw_build_hour   unsigned int8, Hour of the DCB software build   Encoded as packed BCD */
/*  15:8  sw_build_minute unsigned int8, Minute of the DCB software build Encoded as packed BCD */
/*  7:0   sw_build_second unsigned int8, Second of the DCB software build Encoded as packed BCD */

  const char *s = system_sw_build_time;

  return ((s[0]-'0')<<20)|((s[1]-'0')<<16)|((s[3]-'0')<<12)|((s[4]-'0')<<8)|((s[6]-'0')<<4)|(s[7]-'0');
}

/******************************************************************************/

unsigned int get_sw_git_hash()
{
  const char *git_rev_sw_ptr;
  char sw_git_hash[12] = "0xFFFFFFFF\0";

  git_rev_sw_ptr = GIT_REVISION + 13;
  ncpy(&sw_git_hash[2], git_rev_sw_ptr, 8);
  return xfs_atoui((const char*)sw_git_hash);
}

/******************************************************************************/

void init_uart()
{
#ifdef STDOUT_IS_16550
    XUartNs550_SetBaud(STDOUT_BASEADDR, XPAR_XUARTNS550_CLOCK_HZ, UART_BAUD);
    XUartNs550_SetLineControlReg(STDOUT_BASEADDR, XUN_LCR_8_DATA_BITS);
#endif
    /* Bootrom/BSP configures PS7/PSU UART to 115200 bps */
    xfs_printf("\r\n\r\n");
}

/******************************************************************************/

#ifndef LINUX_COMPILE
int init_emac()
{
  int Status;
  XEmacPs_Config *Config;

  Config = XEmacPs_LookupConfig(XPAR_XEMACPS_0_DEVICE_ID);
  Status = XEmacPs_CfgInitialize(SYSPTR(emac_0), Config, Config->BaseAddress);
  if (Status != XST_SUCCESS)
  {
    if(DBG_ERR) xfs_printf("ETH0 Error: error in initialize\r\n");
    return XST_FAILURE;
  }

  return XST_SUCCESS;
}
#endif

/******************************************************************************/

#ifndef LINUX_COMPILE
int init_iic()
{
  XIicPs_Config *iic_cfg;
  int Status;

  /* Init SFP 1 IIC */
  iic_cfg = XIicPs_LookupConfig(XPAR_PS7_I2C_0_DEVICE_ID);
  if (NULL == iic_cfg)
  {
    if(DBG_ERR) xfs_printf("IIC SFP 1 Error: configuration lookup failed\r\n");
    return XST_FAILURE;
  }

  Status = XIicPs_CfgInitialize(SYSPTR(iic_sfp[0]), iic_cfg, iic_cfg->BaseAddress);
  if (Status != XST_SUCCESS)
  {
    if(DBG_ERR) xfs_printf("IIC SFP 1 Error: initialization failed\r\n");
    return XST_FAILURE;
  }

  /*Status = XIicPs_SelfTest(SYSPTR(iic_sfp[0]));
   *if (Status != XST_SUCCESS)
   *{
   *  if(DBG_ERR) xfs_printf("IIC SFP 1 Error: selftest failed\r\n");
   *  return XST_FAILURE;
   *}
   */

  XIicPs_SetSClk(SYSPTR(iic_sfp[0]), SFP_IIC_SCLK_RATE);

  /* Init SFP 2 IIC */
  iic_cfg = XIicPs_LookupConfig(XPAR_PS7_I2C_1_DEVICE_ID);
  if (NULL == iic_cfg)
  {
    if(DBG_ERR) xfs_printf("IIC SFP 2 Error: configuration lookup failed\r\n");
    return XST_FAILURE;
  }

  Status = XIicPs_CfgInitialize(SYSPTR(iic_sfp[1]), iic_cfg, iic_cfg->BaseAddress);
  if (Status != XST_SUCCESS)
  {
    if(DBG_ERR) xfs_printf("IIC SFP 2 Error: initialization failed\r\n");
    return XST_FAILURE;
  }

  /*Status = XIicPs_SelfTest(SYSPTR(iic_sfp[1]));
   *if (Status != XST_SUCCESS)
   *{
   *  if(DBG_ERR) xfs_printf("IIC SFP 2 Error: selftest failed\r\n");
   *  return XST_FAILURE;
   *}
   */

  XIicPs_SetSClk(SYSPTR(iic_sfp[1]), SFP_IIC_SCLK_RATE);


  if(DBG_INIT) xfs_printf("IIC initialization -> OK\r\n");
  return XST_SUCCESS;
}
#endif

/******************************************************************************/

#ifndef LINUX_COMPILE
int init_gpio_mio()
{
  XGpioPs_Config *ConfigPtr;
  int Status;

  /* Initialize the MIO GPIO driver. */
  ConfigPtr = XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID);
  Status = XGpioPs_CfgInitialize(SYSPTR(gpio_mio), ConfigPtr, ConfigPtr->BaseAddr);
  if (Status != XST_SUCCESS) {
    return XST_FAILURE;
  }

  emio_init(SYSPTR(gpio_mio));

  return XST_SUCCESS;
}
#else
int init_gpio_mio()
{
  gpio_init();
}
#endif

/******************************************************************************/

#ifndef LINUX_COMPILE
int init_sfp()
{
  sfp_ctrl_init(SYSPTR(sfp_ctrl[0]), SYSPTR(iic_sfp[0]), SYSPTR(gpio_mio),
                BIT_IDX_EMIO_CTRL_SFP1_RS1_PIN,
                BIT_IDX_EMIO_CTRL_SFP1_RS0_PIN,
                BIT_IDX_EMIO_CTRL_SFP1_DISABLE_PIN,
                BIT_IDX_EMIO_STAT_SFP1_TX_FAULT_PIN,
                BIT_IDX_EMIO_STAT_SFP1_MOD_PIN,
                BIT_IDX_EMIO_STAT_SFP1_LOS_PIN);

  sfp_ctrl_init(SYSPTR(sfp_ctrl[1]), SYSPTR(iic_sfp[1]), SYSPTR(gpio_mio),
                BIT_IDX_EMIO_CTRL_SFP2_RS1_PIN,
                BIT_IDX_EMIO_CTRL_SFP2_RS0_PIN,
                BIT_IDX_EMIO_CTRL_SFP2_DISABLE_PIN,
                BIT_IDX_EMIO_STAT_SFP2_TX_FAULT_PIN,
                BIT_IDX_EMIO_STAT_SFP2_MOD_PIN,
                BIT_IDX_EMIO_STAT_SFP2_LOS_PIN);

  return XST_SUCCESS;
}
#endif

/******************************************************************************/

#ifndef LINUX_COMPILE
int init_spi_eclk_lmk_adc()
{
  XSpiPs_Config *spi_cfg;
  int Status;

  spi_cfg = XSpiPs_LookupConfig(XPAR_PS7_SPI_1_DEVICE_ID);
  if (NULL == spi_cfg)
  {
    if(DBG_ERR) xfs_printf("SPI ECLK-LMK-ADC Error: configuration lookup failed\r\n");
    return XST_FAILURE;
  }

  Status = XSpiPs_CfgInitialize(SYSPTR(spi_eclk_lmk_adc), spi_cfg, spi_cfg->BaseAddress);
  if (Status != XST_SUCCESS)
  {
    if(DBG_ERR) xfs_printf("SPI ECLK-LMK-ADC Error: initialization failed\r\n");
    return XST_FAILURE;
  }

  Status = XSpiPs_SelfTest(SYSPTR(spi_eclk_lmk_adc));
  if (Status != XST_SUCCESS)
  {
    if(DBG_ERR) xfs_printf("SPI ECLK-LMK-ADC Error: selftest failed\r\n");
    return XST_FAILURE;
  }

//  XSpiPs_SetOptions(SYSPTR(spi_eclk_lmk_adc), XSPIPS_MASTER_OPTION | XSPIPS_FORCE_SSELECT_OPTION);
  XSpiPs_SetOptions(SYSPTR(spi_eclk_lmk_adc), XSPIPS_MASTER_OPTION | XSPIPS_FORCE_SSELECT_OPTION | XSPIPS_CLK_ACTIVE_LOW_OPTION | XSPIPS_CLK_PHASE_1_OPTION);
  XSpiPs_SetClkPrescaler(SYSPTR(spi_eclk_lmk_adc), XSPIPS_CLK_PRESCALE_16);

  return XST_SUCCESS;
}
#endif

/******************************************************************************/

int init_spi_bpl()
{
  XSpi_Config *spi_cfg;
  int Status;

  spi_cfg = XSpi_LookupConfig(XPAR_AXI_QUAD_SPI_TO_BPL_0_DEVICE_ID);
  if (NULL == spi_cfg)
  {
    if(DBG_ERR) xfs_printf("SPI Backplane Error: configuration lookup failed\r\n");
    return XST_FAILURE;
  }

#ifdef LINUX_COMPILE
  spi_cfg->BaseAddress = (unsigned int)(io_remap(spi_cfg->BaseAddress));
#endif
  Status = XSpi_CfgInitialize(SYSPTR(spi_bpl), spi_cfg, spi_cfg->BaseAddress);
  if (Status != XST_SUCCESS)
  {
    if(DBG_ERR) xfs_printf("SPI Backplane Error: initialization failed\r\n");
    return XST_FAILURE;
  }

  Status = XSpi_SelfTest(SYSPTR(spi_bpl));
  if (Status != XST_SUCCESS)
  {
    if(DBG_ERR) xfs_printf("SPI Backplane Error: selftest failed\r\n");
    return XST_FAILURE;
  }

  /* The SPI slaves on the WDB are CPOL=0, CPHA=0 */
  Status = XSpi_SetOptions(SYSPTR(spi_bpl), XSP_MASTER_OPTION | XSP_MANUAL_SSELECT_OPTION);
  /* XSP_CLK_ACTIVE_LOW_OPTION   XSP_CLK_PHASE_1_OPTION   XSP_LOOPBACK_OPTION */
  if (Status != XST_SUCCESS)
  {
    if(DBG_ERR) xfs_printf("SPI Backplane Error: set options failed\r\n");
    return XST_FAILURE;
  }

  XSpi_Start(SYSPTR(spi_bpl));
  /* Configure polled mode operation */
  XSpi_IntrGlobalDisable(SYSPTR(spi_bpl));

  return XST_SUCCESS;
}

/******************************************************************************/

void init_reg_bank()
{
  if(reg_bank_initialized)
  {
    return;
  }
  else
  {
    reg_bank_initialized = 1;
    reg_bank_init(XPAR_REGISTER_BANK_0_AXI_DCB_REGISTER_BANK_0_S00_AXI_BASEADDR);
  }
}

/******************************************************************************/

#ifndef LINUX_COMPILE
int fw_env_storage_handler_spi(fw_env_storage_desc_type *storage_desc, unsigned int cmd, char* mem_addr, unsigned int size)
{
  if (cmd == FW_ENV_STORAGE_READ)
  {
    xfs_printf("reading SPI flash: %d bytes at 0x%08x\r\n", size, storage_desc->addr);

    qspi_flash_read((XQspiPs*)(storage_desc->storage_ptr), storage_desc->addr, size, QSFL_QUAD_READ_CMD, (unsigned char*)mem_addr);
    return FW_ENV_STORAGE_OK;
    /* tbd: check errors /  return FW_ENV_STORAGE_ERROR; */

  }
  else if (cmd == FW_ENV_STORAGE_WRITE)
  {
    xfs_printf("writing SPI flash: %d bytes at 0x%08x\r\n", size, storage_desc->addr);

//    qspi_flash_parameter_erase(SYSPTR(spi_flash), storage_desc->addr);
    qspi_flash_erase((XQspiPs*)(storage_desc->storage_ptr), storage_desc->addr, size);
    qspi_flash_write((XQspiPs*)(storage_desc->storage_ptr), storage_desc->addr, size, QSFL_QUAD_WRITE_CMD, (unsigned char*)mem_addr);

    return FW_ENV_STORAGE_OK;
    /* tbd: check errors /  return FW_ENV_STORAGE_ERROR; */
  }

  return FW_ENV_STORAGE_ERROR;
}
#endif

/******************************************************************************/

#ifndef LINUX_COMPILE
void set_hostname_func(const char *name, const char* val)
{
  ncpy(SYSPTR(cfg)->hostname, val, MAX_HOSTNAME_LENGTH);
  SYSPTR(cfg)->hostname[MAX_HOSTNAME_LENGTH-1]=0;
};
#endif

/******************************************************************************/

#ifndef LINUX_COMPILE
void set_sn_func(const char *name, const char* val)
{
  SYSPTR(cfg)->serial_no = xfs_atoi(val);
};
#endif

/******************************************************************************/

#ifndef LINUX_COMPILE
void set_dhcp_func(const char *name, const char* val)
{
//  nw_if_set_dhcp(SYSPTR(nw_if_gmac_0), xfs_atoi(val));
//
//  if (!SYSPTR(nw_if_gmac_0)->do_dhcp)
//  {
    int status;
    unsigned char ip_addr[4];
    status = parse_ip(fw_getenv(SYSPTR(env), "ipaddr"), ip_addr);
//    if (status == XFS_OK)
//    {
//      nw_if_set_ip_address(SYSPTR(nw_if_gmac_0), ip_addr);
//    }
//  }
};
#endif

/******************************************************************************/

#ifndef LINUX_COMPILE
void set_mac_func(const char *name, const char* val)
{
  int status;
  unsigned char mac_addr[6];

  status = parse_mac(val, mac_addr);
//  if (status == XFS_OK)
//  {
//    nw_if_set_mac_address(SYSPTR(nw_if_gmac_0), mac_addr);
//  }
};
#endif

/******************************************************************************/

#ifndef LINUX_COMPILE
void set_ip_func(const char *name, const char* val)
{
//  if (!SYSPTR(nw_if_gmac_0)->do_dhcp)
//  {
    int status;
    unsigned char ip_addr[4];

    status = parse_ip(val, ip_addr);
//    if (status == XFS_OK)
//    {
//      nw_if_set_ip_address(SYSPTR(nw_if_gmac_0), ip_addr);
//    }
//  }
};
#endif

/******************************************************************************/

#ifndef LINUX_COMPILE
void set_srcport_func(const char *name, const char* val)
{
  parse_port(val, &(SYSPTR(cfg)->nw_data_src_port));
}
#endif

/******************************************************************************/

#ifndef LINUX_COMPILE
void set_dbglvl_func(const char *name, const char* val)
{
  unsigned int d;

  d = get_dbg_level();
  xfs_printf("Old dbglvl: %2d  (%s)\r\n", d, dbg_level_str[d]);

  d = parse_dbglvl(val);
  set_dbg_level(d);

  d = get_dbg_level();
  xfs_printf("New dbglvl: %2d  (%s)\r\n", d, dbg_level_str[d]);
}
#endif

/******************************************************************************/

#ifndef LINUX_COMPILE
fw_env_trigger_entry_type fw_env_trigger_table[] =
{
  {"hostname",   set_hostname_func},
  {"sn",         set_sn_func},
  {"ipaddr",     set_ip_func},
  {"ethaddr",    set_mac_func},
  {"ethdhcp",    set_dhcp_func},
  {"srcport",    set_srcport_func},
  {"dbglvl",     set_dbglvl_func},
  {NULL, NULL}
};
#endif

/************************************************************/

#ifndef LINUX_COMPILE
char env_mem[QSPI_FLASH_ENVIRONMENT_SIZE];

char default_env[] = "sn=0\0"
                     "hostname=DCBnew\0"
                     "ethaddr=00:50:c2:46:d9:04\0"
                     "ipaddr=10.1.0.1\0"
                     "ethdhcp=1\0"
                     "srcport=3000\0"
                     "\0";

#define DEFAULT_ENV_SIZE  sizeof(default_env)
#endif

/******************************************************************************/

void init_lmk03000()
{
#ifdef LINUX_COMPILE
  if(lmk03000_initialized)
  {
    return;
  }
  else
  {
    lmk03000_initialized = 1;
    lmk03000_init(SYSPTR(lmk), SPI_DEV_ECLK_LMK_ADC, SPI_SLAVE_NR_LMK);
  }
#else /* LINUX_COMPILE */
  lmk03000_init(SYSPTR(lmk),     SYSPTR(spi_eclk_lmk_adc), SPI_SLAVE_NR_LMK);
#endif /* LINUX_COMPILE */
}

/******************************************************************************/

void init_si5324()
{
#ifdef LINUX_COMPILE
  if(si5324_initialized)
  {
    return;
  }
  else
  {
    si5324_initialized = 1;
    si5324_init(SYSPTR(si5324), SPI_DEV_ECLK_LMK_ADC, SPI_SLAVE_NR_SI3524);
  }
#else /* LINUX_COMPILE */
  si5324_init(SYSPTR(si5324),  SYSPTR(spi_eclk_lmk_adc), SPI_SLAVE_NR_SI3524);
#endif /* LINUX_COMPILE */
}

/******************************************************************************/

void init_sysmon()
{
#ifdef LINUX_COMPILE
  if(sys_mon_initialized)
  {
    return;
  }
  else
  {
    sys_mon_initialized = 1;
    sysmon_init(SYSPTR(sys_mon), SPI_DEV_ECLK_LMK_ADC, SPI_SLAVE_NR_SYS_MON);
  }
#else /* LINUX_COMPILE */
  sysmon_init(SYSPTR(sys_mon), SYSPTR(spi_eclk_lmk_adc), SPI_SLAVE_NR_SYS_MON);
#endif /* LINUX_COMPILE */
}

/******************************************************************************/

int init_system()
{
  unsigned int reg_val;

#ifndef LINUX_COMPILE
  /* ps7_init();*/
  /* psu_init();*/
  /*enable_caches();*/
  init_uart();

  init_emac();
#endif

  init_gpio_mio();

  emio_flash_sw_state(BIT_IDX_EMIO_CTRL_SW_STATE_DCB_ACCESS_PIN);

  init_spi_bpl();

#ifndef LINUX_COMPILE
  /* Environment initialization */
  system_hw.env_storage_description[0].storage_ptr     = SYSPTR(spi_flash);
  system_hw.env_storage_description[0].addr            = QSPI_FLASH_ENVIRONMENT_ADDR;
  system_hw.env_storage_description[0].storage_handler = fw_env_storage_handler_spi;
  system_hw.env_storage_description[1].storage_ptr     = SYSPTR(spi_flash);
  system_hw.env_storage_description[1].addr            = QSPI_FLASH_REDUNDANT_ENVIRONMENT_ADDR;
  system_hw.env_storage_description[1].storage_handler = fw_env_storage_handler_spi;
  qspi_flash_init(SYSPTR(spi_flash), XPAR_PS7_QSPI_0_DEVICE_ID);
  fw_env_init(SYSPTR(env), env_mem, QSPI_FLASH_ENVIRONMENT_SIZE, default_env, DEFAULT_ENV_SIZE, system_hw.env_storage_description, ENV_STORAGE_ENTRIES, fw_env_trigger_table);
  fw_env_load(SYSPTR(env));
  /* End of environment initialization */

#endif
  /* Register bank initialization */
  init_reg_bank();
  reg_bank_load();
  /* write software build date to status register */
  reg_val = reg_sw_build_date();
  reg_bank_write(DCB_REG_SW_BUILD_DATE, &reg_val, 1);
  /* write software build time to status register */
  reg_val = reg_sw_build_time();
  reg_bank_write(DCB_REG_SW_BUILD_TIME, &reg_val, 1);
  /* write software GIT hashtag to status register */
  reg_val = get_sw_git_hash();
  reg_bank_write(DCB_REG_SW_GIT_HASH_TAG, &reg_val, 1);
#ifndef LINUX_COMPILE

  init_iic();

  init_sfp();

  init_spi_eclk_lmk_adc();
#endif /* not LINUX_COMPILE */
  /* init_si5324(); */ /* done by fsbl, not needed in application */
  init_lmk03000();
  init_sysmon();

  return XST_SUCCESS;
}

/******************************************************************************/

void init_settings(int snr)
{
#ifndef LINUX_COMPILE
  init_env_settings(snr);
#endif
  init_reg_settings(snr);
  xfs_printf("\r\n*** System Initialization Complete ***\r\n\r\n");
}

/******************************************************************************/

#ifndef LINUX_COMPILE
void init_env_settings(int snr)
{
  int cmd_buf_size = 10;
  int name_buf_size = 10;
  int val_buf_size = 30;
  char command[cmd_buf_size];
  char name[name_buf_size];
  char value[val_buf_size];
  char *buffer_ptr[3] = {command, name, value};

  xfs_printf("\r\nInitializing environment:\r\n");

  xfs_snprintf(command, cmd_buf_size, "setenv\0");

  /*** Set Environment ******************************************/
  /* set envirnment serial number */
  xfs_snprintf(name,  name_buf_size, "sn\0");
  xfs_snprintf(value, val_buf_size,  "%d\0", (unsigned int)snr);
  xfs_printf("%s %s %s\r\n", command, name, value);
  fw_setenv(SYSPTR(env), 3, buffer_ptr);
  /* set envirnment hostname */
  xfs_snprintf(name,  name_buf_size, "hostname\0");
  xfs_snprintf(value, val_buf_size,  "dcb%03d\0", (unsigned int)snr);
  xfs_printf("%s %s %s\r\n", command, name, value);
  fw_setenv(SYSPTR(env), 3, buffer_ptr);
  /* set envirnment mac address */
  xfs_snprintf(name,  name_buf_size, "ethaddr\0");
  xfs_snprintf(value, val_buf_size,  "00:50:C2:46:D5:%02X\0", (unsigned int)(snr*2));
  xfs_printf("%s %s %s\r\n", command, name, value);
  fw_setenv(SYSPTR(env), 3, buffer_ptr);

  /* set envirnment dhcp */
  xfs_snprintf(name,  name_buf_size, "ethdhcp\0");
  xfs_snprintf(value, val_buf_size,  "1\0");
  xfs_printf("%s %s %s\r\n", command, name, value);
  fw_setenv(SYSPTR(env), 3, buffer_ptr);
  /* set envirnment debug level */
  xfs_snprintf(name,  name_buf_size, "dbglvl\0");
  xfs_snprintf(value, val_buf_size,  "none\0");
  xfs_printf("%s %s %s\r\n", command, name, value);
  fw_setenv(SYSPTR(env), 3, buffer_ptr);
  /* set envirnment static ip address */
  xfs_snprintf(name,  name_buf_size, "ipaddr\0");
  xfs_snprintf(value, val_buf_size,  "10.1.0.1\0");
  xfs_printf("%s %s %s\r\n", command, name, value);
  fw_setenv(SYSPTR(env), 3, buffer_ptr);
  /* set envirnment udp source port */
  xfs_snprintf(name,  name_buf_size, "srcport\0");
  xfs_snprintf(value, val_buf_size,  "3000\0");
  xfs_printf("%s %s %s\r\n", command, name, value);
  fw_setenv(SYSPTR(env), 3, buffer_ptr);

  /* store values in SPI flash */
  xfs_printf("\r\nStoring environment in QSPI flash\r\n");
  fw_env_save(SYSPTR(env));
}
#endif

/******************************************************************************/

void init_reg_settings(int snr)
{
  unsigned int reg_val;

  xfs_printf("\r\nInitializing Control Register:\r\n");
  for(unsigned int i=0;i<NR_OF_REGS-1;i++) /* Last register is the checksum */
  {
    if(!dcb_reg_list[i].read_only)
    xfs_printf("[0x%08X]: 0x%08X\r\n", i*4, reg_default[i]);
    reg_bank_write(i*4, (unsigned int*)(&reg_default[i]), 1);
  }

  reg_bank_write(DCB_SERIAL_NUMBER_REG, (unsigned int*)(&snr), 1);
   /* write software build date to status register */
  reg_val = reg_sw_build_date();
  reg_bank_write(DCB_REG_SW_BUILD_DATE, &reg_val, 1);
  /* write software build time to status register */
  reg_val = reg_sw_build_time();
  reg_bank_write(DCB_REG_SW_BUILD_TIME, &reg_val, 1);
  /* write software GIT hashtag to status register */
  reg_val = get_sw_git_hash();
  reg_bank_write(DCB_REG_SW_GIT_HASH_TAG, &reg_val, 1);

  xfs_printf("\r\nStoring register bank contents in SPI flash\r\n");
  reg_bank_store();
}

/******************************************************************************/

void print_sys_info(void)
{
  const char *git_rev_sw_ptr;

//  /*unsigned int version; */
//  unsigned int build_date;
//  unsigned int build_time;
////  unsigned int git_rev_fw;
  unsigned int hw_version;

//  unsigned short year;
//  unsigned char month;
//  unsigned char day;
//
//  unsigned char hour;
//  unsigned char minute;
//  unsigned char second;
//  unsigned char compat_level;

  unsigned char board_variant;
  unsigned char board_type;
  unsigned char board_revision;


//  /* version = xfs_in32(baseaddr); */
//  build_date = reg_bank_get(DCB_REG_FW_BUILD_DATE);
//  build_time = reg_bank_get(DCB_REG_FW_BUILD_TIME);
////  git_rev_fw = reg_bank_get(DCB_REG_FW_GIT_HASH_TAG);
  hw_version = reg_bank_get(DCB_REG_HW_VER);
//
//
//  /* read and convert from BCD to binary */
//  year         = (build_date & DCB_FW_BUILD_YEAR_MASK)  >> DCB_FW_BUILD_YEAR_OFS;
//  year         = ((year >> 12) & 0xF) * 1000 + ((year >> 8) & 0xF) * 100 + ((year >> 4) & 0xF) * 10 + (year & 0xF);
//  month        = (build_date & DCB_FW_BUILD_MONTH_MASK) >> DCB_FW_BUILD_MONTH_OFS;
//  month        = ((month >> 4) & 0xF) * 10 + (month & 0xF);
//  day          = (build_date & DCB_FW_BUILD_DAY_MASK)   >> DCB_FW_BUILD_DAY_OFS;
//  day          = ((day >> 4) & 0xF) * 10 + (day & 0xF);
//
//
//  compat_level = (build_time & DCB_FW_COMPAT_LEVEL_MASK) >> DCB_FW_COMPAT_LEVEL_OFS;
//
//  /* read and convert from BCD to binary */
//  hour         = (build_time & DCB_FW_BUILD_HOUR_MASK)   >> DCB_FW_BUILD_HOUR_OFS;
//  hour         = ((hour >> 4) & 0xF) * 10 + (hour & 0xF);
//  minute       = (build_time & DCB_FW_BUILD_MINUTE_MASK) >> DCB_FW_BUILD_MINUTE_OFS;
//  minute       = ((minute >> 4) & 0xF) * 10 + (minute & 0xF);
//  second       = (build_time & DCB_FW_BUILD_SECOND_MASK) >> DCB_FW_BUILD_SECOND_OFS;
//  second       = ((second >> 4) & 0xF) * 10 + (second & 0xF);


  git_rev_sw_ptr = GIT_REVISION + 13;

  board_variant  = (hw_version & DCB_BOARD_VARIANT_MASK)  >> DCB_BOARD_VARIANT_OFS;
  board_type     = (hw_version & DCB_BOARD_TYPE_MASK)     >> DCB_BOARD_TYPE_OFS;
  board_revision = (hw_version & DCB_BOARD_REVISION_MASK) >> DCB_BOARD_REVISION_OFS;


//  xfs_printf("-- Compatibility Level: %d\r\n\r\n", compat_level);
////  xfs_printf("-- FW GIT Revision:     0x%07X\r\n", git_rev_fw);
//
  xfs_printf("-- SW GIT Revision:     0x%s\r\n\r\n", git_rev_sw_ptr);
////  xfs_printf("-- FW Build:            %s %2d %04d  %02d:%02d:%02d\r\n", system_month_str[(month-1)%12], day, year, hour, minute, second);

  xfs_printf("-- SW Build:            %s  %s (UTC)\r\n\r\n",system_sw_build_date,system_sw_build_time);
  if(board_type == 0x03) xfs_printf("-- Board Type:          WaveDAQ DCB\r\n");
  else                   xfs_printf("-- Board Type:          0x%02X -> error\r\n", board_type);
  xfs_printf("-- Board Revision:      %c\r\n", 0x41 + board_revision); /* 0x41 = ASCII "A" */
  xfs_printf("-- Board Variant:       0x%02X\r\n", board_variant);
}

/******************************************************************************/

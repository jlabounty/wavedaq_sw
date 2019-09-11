/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WDAQ - DCB
 *
 *  Author  :  schmid_e
 *  Created :  23.11.2018 14:51:32
 *
 *  Description :  SPI driver for external System Monitor ADC.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#include "drv_sys_mon.h"
#include "system.h"
//#include "dbg.h"
#include "xfs_printf.h"

/******************************************************************************/

#define SYSMON_CMD_MAN_CONV         0x00
#define SYSMON_CMD_RD_ALARM         0x10
#define SYSMON_CMD_RD_CH_DATA       0x20
#define SYSMON_CMD_RD_ALL_DATA      0x30
#define SYSMON_CMD_RD_CH_CFG        0x40
#define SYSMON_CMD_RD_GLOB_CFG      0x50
/*#define SYSMON_CMD_RESERVED         0x60 */
#define SYSMON_CMD_RESET            0x70
#define SYSMON_CMD_CLR_CH_ALARM     0x80
#define SYSMON_CMD_CLR_ALL_ALARMS   0x90
#define SYSMON_CMD_WR_CH_DATA       0xA0
#define SYSMON_CMD_WR_ALL_DATA      0xB0
#define SYSMON_CMD_WR_CH_CFG        0xC0
#define SYSMON_CMD_WR_GLOB_CFG      0xD0
/*#define SYSMON_CMD_RESERVED         0xE0 */
/*#define SYSMON_CMD_RESERVED         0xF0 */

#define SYSMON_VREF                  2.5   /* V */

#define SYSMON_MASTER_AVG                0x0
#define SYSMON_MASTER_FAULT              0x0
#define SYSMON_MASTER_UNI_UPPER_THRESH   0xFFF
#define SYSMON_MASTER_UNI_LOWER_THRESH   0x000
#define SYSMON_MASTER_BIP_UPPER_THRESH   0x7FF
#define SYSMON_MASTER_BIP_LOWER_THRESH   0x800

/******************************************************************************/
/******************************************************************************/

#ifdef LINUX_COMPILE
static int initialized = 0;

void sysmon_init(sysmon_ctrl_type *self, unsigned char device_nr, unsigned char slave_nr)
{
  const unsigned char ch_cfg = (SYSMON_MASTER_FAULT << SYSMON_CH_CFG_FAULT_OFFSET) | SYSMON_MASTER_AVG;
  const unsigned int ch_en = SYSMON_BIT_CH_ALL;
  const unsigned int input_cfg = (SYSMON_IN_CFG_SE_SE << SYSMON_CFG_AIN0_1_OFFSET) |
                                 (SYSMON_IN_CFG_SE_SE << SYSMON_CFG_AIN2_3_OFFSET) |
                                 (SYSMON_IN_CFG_SE_SE << SYSMON_CFG_AIN4_5_OFFSET) |
                                  SYSMON_IN_CFG_SE_SE;
  const unsigned char setup = SYSMON_BIT_SETUP_SAMPLE_WAIT_312000US |
                              SYSMON_BIT_SETUP_INT_PUSH_PULL |
                              SYSMON_BIT_SETUP_INT_ACTIVE_HIGH |
                              SYSMON_BIT_SETUP_AUTOSCAN |
                              SYSMON_BIT_SETUP_REF_MODE_EXT;

  initialized = 1;
  spi_ps_init((spi_ps_type*)self, device_nr, slave_nr, 0, 8, 1000000, 0);

  sysmon_write_channel_config(self, SYSMON_ADR_TEMP, SYSMON_MASTER_BIP_UPPER_THRESH, SYSMON_MASTER_BIP_LOWER_THRESH, ch_cfg);
  sysmon_write_channel_config(self, SYSMON_ADR_VDD,  SYSMON_MASTER_UNI_UPPER_THRESH, SYSMON_MASTER_UNI_LOWER_THRESH, ch_cfg);
  sysmon_write_channel_config(self, SYSMON_ADR_AIN0, SYSMON_MASTER_UNI_UPPER_THRESH, SYSMON_MASTER_UNI_LOWER_THRESH, ch_cfg);
  sysmon_write_channel_config(self, SYSMON_ADR_AIN1, SYSMON_MASTER_UNI_UPPER_THRESH, SYSMON_MASTER_UNI_LOWER_THRESH, ch_cfg);
  sysmon_write_channel_config(self, SYSMON_ADR_AIN2, SYSMON_MASTER_UNI_UPPER_THRESH, SYSMON_MASTER_UNI_LOWER_THRESH, ch_cfg);
  sysmon_write_channel_config(self, SYSMON_ADR_AIN3, SYSMON_MASTER_UNI_UPPER_THRESH, SYSMON_MASTER_UNI_LOWER_THRESH, ch_cfg);
  sysmon_write_channel_config(self, SYSMON_ADR_AIN4, SYSMON_MASTER_UNI_UPPER_THRESH, SYSMON_MASTER_UNI_LOWER_THRESH, ch_cfg);
  sysmon_write_channel_config(self, SYSMON_ADR_AIN5, SYSMON_MASTER_UNI_UPPER_THRESH, SYSMON_MASTER_UNI_LOWER_THRESH, ch_cfg);
  sysmon_write_channel_config(self, SYSMON_ADR_AIN6, SYSMON_MASTER_UNI_UPPER_THRESH, SYSMON_MASTER_UNI_LOWER_THRESH, ch_cfg);
  sysmon_write_channel_config(self, SYSMON_ADR_AIN7, SYSMON_MASTER_UNI_UPPER_THRESH, SYSMON_MASTER_UNI_LOWER_THRESH, ch_cfg);

  sysmon_write_global_config(self, ch_en, input_cfg, setup);
}

#else /* LINUX_COMPILE */

void sysmon_init(sysmon_ctrl_type *self, XSpiPs *spi_if_ptr_init, unsigned char slave_nr_init)
{
  const unsigned char ch_cfg = (SYSMON_MASTER_FAULT << SYSMON_CH_CFG_FAULT_OFFSET) | SYSMON_MASTER_AVG;
  const unsigned int ch_en = SYSMON_BIT_CH_ALL;
  const unsigned int input_cfg = (SYSMON_IN_CFG_SE_SE << SYSMON_CFG_AIN0_1_OFFSET) |
                                 (SYSMON_IN_CFG_SE_SE << SYSMON_CFG_AIN2_3_OFFSET) |
                                 (SYSMON_IN_CFG_SE_SE << SYSMON_CFG_AIN4_5_OFFSET) |
                                  SYSMON_IN_CFG_SE_SE;
  const unsigned char setup = SYSMON_BIT_SETUP_SAMPLE_WAIT_312000US |
                              SYSMON_BIT_SETUP_INT_PUSH_PULL |
                              SYSMON_BIT_SETUP_INT_ACTIVE_HIGH |
                              SYSMON_BIT_SETUP_AUTOSCAN |
                              SYSMON_BIT_SETUP_REF_MODE_EXT;

  self->spi_if_ptr = spi_if_ptr_init;
  self->slave_nr   = slave_nr_init;

  sysmon_write_channel_config(self, SYSMON_ADR_TEMP, SYSMON_MASTER_BIP_UPPER_THRESH, SYSMON_MASTER_BIP_LOWER_THRESH, ch_cfg);
  sysmon_write_channel_config(self, SYSMON_ADR_VDD,  SYSMON_MASTER_UNI_UPPER_THRESH, SYSMON_MASTER_UNI_LOWER_THRESH, ch_cfg);
  sysmon_write_channel_config(self, SYSMON_ADR_AIN0, SYSMON_MASTER_UNI_UPPER_THRESH, SYSMON_MASTER_UNI_LOWER_THRESH, ch_cfg);
  sysmon_write_channel_config(self, SYSMON_ADR_AIN1, SYSMON_MASTER_UNI_UPPER_THRESH, SYSMON_MASTER_UNI_LOWER_THRESH, ch_cfg);
  sysmon_write_channel_config(self, SYSMON_ADR_AIN2, SYSMON_MASTER_UNI_UPPER_THRESH, SYSMON_MASTER_UNI_LOWER_THRESH, ch_cfg);
  sysmon_write_channel_config(self, SYSMON_ADR_AIN3, SYSMON_MASTER_UNI_UPPER_THRESH, SYSMON_MASTER_UNI_LOWER_THRESH, ch_cfg);
  sysmon_write_channel_config(self, SYSMON_ADR_AIN4, SYSMON_MASTER_UNI_UPPER_THRESH, SYSMON_MASTER_UNI_LOWER_THRESH, ch_cfg);
  sysmon_write_channel_config(self, SYSMON_ADR_AIN5, SYSMON_MASTER_UNI_UPPER_THRESH, SYSMON_MASTER_UNI_LOWER_THRESH, ch_cfg);
  sysmon_write_channel_config(self, SYSMON_ADR_AIN6, SYSMON_MASTER_UNI_UPPER_THRESH, SYSMON_MASTER_UNI_LOWER_THRESH, ch_cfg);
  sysmon_write_channel_config(self, SYSMON_ADR_AIN7, SYSMON_MASTER_UNI_UPPER_THRESH, SYSMON_MASTER_UNI_LOWER_THRESH, ch_cfg);

  sysmon_write_global_config(self, ch_en, input_cfg, setup);
}

#endif /* LINUX_COMPILE */

/******************************************************************************/

void sysmon_transfer(sysmon_ctrl_type* self, char* tx_buf, char* rx_buf, unsigned int len)
{
#ifdef LINUX_COMPILE
  if(!initialized)
  {
    initialized = 1;
    init_sysmon();
  }
#endif

  spi_ps_transfer((spi_ps_type*)self, tx_buf, rx_buf, len);
}

/******************************************************************************/

void sysmon_trigger_conversion(sysmon_ctrl_type *self, unsigned char channel)
{
  unsigned char tx_buffer[1];

  tx_buffer[0] = SYSMON_CMD_MAN_CONV | (0x0F & channel);

  sysmon_transfer(self, tx_buffer, NULL, 1);
}

/******************************************************************************/

float sysmon_get_temp(sysmon_ctrl_type *self)
{
  float temp;
  unsigned int temp_reg;

  temp_reg = sysmon_read_channel(self, SYSMON_ADR_TEMP);
  if(temp_reg & 0x800)
  {
    /* sign extension */
    temp_reg |= 0xFFFFF000;
  }

  temp = (float)temp_reg / 8.0;

  return temp;
}

/******************************************************************************/

int sysmon_get_temp_mdeg(sysmon_ctrl_type *self)
{
  return (int)(1000.0 * sysmon_get_temp(self));
}

/******************************************************************************/

float sysmon_get_vdd(sysmon_ctrl_type *self)
{
  float vdd;
  unsigned int vdd_reg;

  vdd_reg = sysmon_read_channel(self, SYSMON_ADR_VDD);

  vdd = 2.0 * SYSMON_VREF * (float)vdd_reg / 4096.0;

  return vdd;
}

/******************************************************************************/

int sysmon_get_vdd_mv(sysmon_ctrl_type *self)
{
  return (int)(1000.0 * sysmon_get_vdd(self));
}

/******************************************************************************/

float sysmon_get_voltage(sysmon_ctrl_type *self, unsigned char channel)
{
  float ain;
  unsigned int ain_reg;

  ain_reg = sysmon_read_channel(self, channel);

  ain = SYSMON_VREF * (float)ain_reg / 4096.0;

  return ain;
}

/******************************************************************************/

int sysmon_get_voltage_mv(sysmon_ctrl_type *self, unsigned char channel)
{
  return (int)(1000.0 * sysmon_get_voltage(self, channel));
}

/******************************************************************************/

unsigned int sysmon_read_alarms(sysmon_ctrl_type *self)
{
  unsigned char tx_buffer[4] = {0,0,0,0};
  unsigned char rx_buffer[4];
  unsigned int rx_data;

  tx_buffer[0] = SYSMON_CMD_RD_ALARM;

  sysmon_transfer(self, tx_buffer, rx_buffer, 4);

  rx_data = ((unsigned int)(rx_buffer[1]) << 16) |
            ((unsigned int)(rx_buffer[2]) <<  8) |
             (unsigned int)(rx_buffer[3]);

  return rx_data;
}

/******************************************************************************/

unsigned int sysmon_read_channel(sysmon_ctrl_type *self, unsigned char channel)
{
  unsigned char tx_buffer[3] = {0,0,0};
  unsigned char rx_buffer[3];
  unsigned int rx_data;

  tx_buffer[0] = SYSMON_CMD_RD_CH_DATA | (0x0F & channel);

  sysmon_transfer(self, tx_buffer, rx_buffer, 3);

  rx_data = (((unsigned int)rx_buffer[1]) << 4) | (((unsigned int)rx_buffer[2]) >> 4);

  return rx_data;
}

/******************************************************************************/

void sysmon_read_channel_config(sysmon_ctrl_type *self, unsigned char channel, unsigned int *upper_threshold, unsigned int *lower_threshold, unsigned char *configuration)
{
  unsigned char tx_buffer[6] = {0,0,0,0,0,0};
  unsigned char rx_buffer[6];

  tx_buffer[0] = SYSMON_CMD_RD_CH_CFG | (0x0F & channel);

  sysmon_transfer(self, tx_buffer, rx_buffer, 6);

  *upper_threshold = ((unsigned int)(rx_buffer[1]) << 4) | ((unsigned int)(rx_buffer[2]) >> 4);
  *lower_threshold = ((unsigned int)(rx_buffer[3]) << 4) | ((unsigned int)(rx_buffer[4]) >> 4);
  *configuration   =  (unsigned int)(rx_buffer[5]);
}

/******************************************************************************/

void sysmon_read_global_config(sysmon_ctrl_type *self, unsigned int *channel_en, unsigned int *input_cfg, unsigned char *setup)
{
  unsigned char tx_buffer[6] = {0,0,0,0,0,0};
  unsigned char rx_buffer[6];

  tx_buffer[0] = SYSMON_CMD_RD_GLOB_CFG;

  sysmon_transfer(self, tx_buffer, rx_buffer, 6);

  *channel_en = ((unsigned int)(rx_buffer[1]) << 4) | ((unsigned int)(rx_buffer[2]) >> 4);
  *input_cfg  = ((unsigned int)(rx_buffer[3]) << 4) | ((unsigned int)(rx_buffer[4]) >> 4);
  *setup      =  (unsigned int)(rx_buffer[5]);
}

/******************************************************************************/

void sysmon_reset(sysmon_ctrl_type *self)
{
  unsigned char tx_buffer[1];

  tx_buffer[0] = SYSMON_CMD_RESET;

  sysmon_transfer(self, tx_buffer, NULL, 1);
}

/******************************************************************************/

void sysmon_clear_channel_alarm(sysmon_ctrl_type *self, unsigned char channel)
{
  unsigned char tx_buffer[1];

  tx_buffer[0] = SYSMON_CMD_CLR_CH_ALARM | (0x0F & channel);

  sysmon_transfer(self, tx_buffer, NULL, 1);
}

/******************************************************************************/

void sysmon_clear_alarms(sysmon_ctrl_type *self)
{
  unsigned char tx_buffer[1];

  tx_buffer[0] = SYSMON_CMD_CLR_ALL_ALARMS;

  sysmon_transfer(self, tx_buffer, NULL, 1);
}

/******************************************************************************/

void sysmon_write_channel(sysmon_ctrl_type *self, unsigned char channel)
{
  unsigned char tx_buffer[3] = {0,0,0};

  tx_buffer[0] = SYSMON_CMD_WR_CH_DATA | (0x0F & channel);

  sysmon_transfer(self, tx_buffer, NULL, 3);
}

/******************************************************************************/

void sysmon_write_channel_config(sysmon_ctrl_type *self, unsigned char channel, unsigned int upper_threshold, unsigned int lower_threshold, unsigned char configuration)
{
  unsigned char tx_buffer[6] = {0,0,0,0,0,0};

  tx_buffer[0] = SYSMON_CMD_WR_CH_CFG | (0x0F & channel);
  tx_buffer[1] = (unsigned char)(upper_threshold >> 4);
  tx_buffer[2] = (unsigned char)((upper_threshold & 0x0F) << 4);
  tx_buffer[3] = (unsigned char)(lower_threshold >> 8);
  tx_buffer[4] = (unsigned char)((lower_threshold & 0x0F) << 4);
  tx_buffer[5] = configuration;

  sysmon_transfer(self, tx_buffer, NULL, 6);
}

/******************************************************************************/

void sysmon_write_global_config(sysmon_ctrl_type *self, unsigned int channel_en, unsigned int input_cfg, unsigned char setup)
{
  unsigned char tx_buffer[6] = {0,0,0,0,0,0};

  tx_buffer[0] = SYSMON_CMD_WR_GLOB_CFG;
  tx_buffer[1] = (unsigned char)(channel_en >> 4);
  tx_buffer[2] = (unsigned char)((channel_en & 0x0F) << 4);
  tx_buffer[3] = (unsigned char)(input_cfg >> 4);
  tx_buffer[4] = (unsigned char)((input_cfg & 0x0F) << 4);
  tx_buffer[5] = setup;

  sysmon_transfer(self, tx_buffer, NULL, 6);
}

/******************************************************************************/
/******************************************************************************/

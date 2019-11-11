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

#ifndef __DRV_SYSMON_H__
#define __DRV_SYSMON_H__

#ifndef LINUX_COMPILE
#include "xspips.h"
#endif
#include "drv_spi_if.h"

#define SYSMON_ADR_TEMP                         0x00
#define SYSMON_ADR_VDD                          0x01
#define SYSMON_ADR_AIN0                         0x02
#define SYSMON_ADR_AIN1                         0x03
#define SYSMON_ADR_AIN2                         0x04
#define SYSMON_ADR_AIN3                         0x05
#define SYSMON_ADR_AIN4                         0x06
#define SYSMON_ADR_AIN5                         0x07
#define SYSMON_ADR_AIN6                         0x08
#define SYSMON_ADR_AIN7                         0x09

#define SYSMON_BIT_CH_TEMP                    0x0800
#define SYSMON_BIT_CH_VDD                     0x0400
#define SYSMON_BIT_CH_AIN0                    0x0200
#define SYSMON_BIT_CH_AIN1                    0x0100
#define SYSMON_BIT_CH_AIN2                    0x0080
#define SYSMON_BIT_CH_AIN3                    0x0040
#define SYSMON_BIT_CH_AIN4                    0x0020
#define SYSMON_BIT_CH_AIN5                    0x0010
#define SYSMON_BIT_CH_AIN6                    0x0008
#define SYSMON_BIT_CH_AIN7                    0x0004
#define SYSMON_BIT_CH_ALL                     0x0FFC

#define SYSMON_IN_CFG_SE_SE                      0x0
#define SYSMON_IN_CFG_SE_SETEMP                  0x1
#define SYSMON_IN_CFG_SETEMP_SE                  0x2
#define SYSMON_IN_CFG_SETEMP_SETEMP              0x3
#define SYSMON_IN_CFG_DIFF_UNIPOLAR              0x4
#define SYSMON_IN_CFG_DIFF_BIPOPLAR              0x5
#define SYSMON_IN_CFG_DIFF_TEMP                  0x6
#define SYSMON_IN_CFG_RESERVED                   0x7

#define SYSMON_BIT_SETUP_SAMPLE_WAIT_0US        0x00
#define SYSMON_BIT_SETUP_SAMPLE_WAIT_80US       0x20
#define SYSMON_BIT_SETUP_SAMPLE_WAIT_395US      0x40
#define SYSMON_BIT_SETUP_SAMPLE_WAIT_1310US     0x60
#define SYSMON_BIT_SETUP_SAMPLE_WAIT_4970US     0x80
#define SYSMON_BIT_SETUP_SAMPLE_WAIT_19600US    0xA0
#define SYSMON_BIT_SETUP_SAMPLE_WAIT_78200US    0xC0
#define SYSMON_BIT_SETUP_SAMPLE_WAIT_312000US   0xE0

#define SYSMON_BIT_SETUP_INT_PUSH_PULL          0x10 /* 0 = HiZ when low, 1 = '0' when low */
#define SYSMON_BIT_SETUP_INT_ACTIVE_HIGH        0x08 /* 0 = active low, 1 = active high */
#define SYSMON_BIT_SETUP_AUTOSCAN               0x04 /* 0 = manual, 1 = automatic */
#define SYSMON_BIT_SETUP_REF_MODE_EXT           0x00 /* External reference */
#define SYSMON_BIT_SETUP_REF_MODE_INT_DLY       0x01 /* Internal reference delayed*/
#define SYSMON_BIT_SETUP_REF_MODE_INT           0x02 /* Internal reference */
#define SYSMON_BIT_SETUP_REF_MODE_RESERVED      0x03 /* Reserved */

#define SYSMON_BIT_ALARM_TEMP_OVER          0x800000
#define SYSMON_BIT_ALARM_TEMP_UNDER         0x400000
#define SYSMON_BIT_ALARM_VDD_OVER           0x200000
#define SYSMON_BIT_ALARM_VDD_UNDER          0x100000
#define SYSMON_BIT_ALARM_AIN0_OVER          0x080000
#define SYSMON_BIT_ALARM_AIN0_UNDER         0x040000
#define SYSMON_BIT_ALARM_AIN1_OVER          0x020000
#define SYSMON_BIT_ALARM_AIN1_UNDER         0x010000
#define SYSMON_BIT_ALARM_AIN2_OVER          0x008000
#define SYSMON_BIT_ALARM_AIN2_UNDER         0x004000
#define SYSMON_BIT_ALARM_AIN3_OVER          0x002000
#define SYSMON_BIT_ALARM_AIN3_UNDER         0x001000
#define SYSMON_BIT_ALARM_AIN4_OVER          0x000800
#define SYSMON_BIT_ALARM_AIN4_UNDER         0x000400
#define SYSMON_BIT_ALARM_AIN5_OVER          0x000200
#define SYSMON_BIT_ALARM_AIN5_UNDER         0x000100
#define SYSMON_BIT_ALARM_AIN6_OVER          0x000080
#define SYSMON_BIT_ALARM_AIN6_UNDER         0x000040
#define SYSMON_BIT_ALARM_AIN7_OVER          0x000020
#define SYSMON_BIT_ALARM_AIN7_UNDER         0x000010

#define SYSMON_AIN7_OFFSET                         2
#define SYSMON_AIN6_OFFSET                         3
#define SYSMON_AIN5_OFFSET                         4
#define SYSMON_AIN4_OFFSET                         5
#define SYSMON_AIN3_OFFSET                         6
#define SYSMON_AIN2_OFFSET                         7
#define SYSMON_AIN1_OFFSET                         8
#define SYSMON_AIN0_OFFSET                         9
#define SYSMON_VDD_OFFSET                         10
#define SYSMON_TEMP_OFFSET                        11

#define SYSMON_CFG_AIN6_7_OFFSET                   0
#define SYSMON_CFG_AIN4_5_OFFSET                   3
#define SYSMON_CFG_AIN2_3_OFFSET                   6
#define SYSMON_CFG_AIN0_1_OFFSET                   9

#define SYSMON_CH_CFG_FAULT_OFFSET                 4

#define SYSMON_BIT_AVERAGE_1                     0x0 /* No averaging */
#define SYSMON_BIT_AVERAGE_2                     0x1
#define SYSMON_BIT_AVERAGE_4                     0x2
#define SYSMON_BIT_AVERAGE_8                     0x3
#define SYSMON_BIT_AVERAGE_16                    0x4
#define SYSMON_BIT_AVERAGE_32                    0x5
#define SYSMON_BIT_AVERAGE_64                    0x6
#define SYSMON_BIT_AVERAGE_128                   0x7
#define SYSMON_BIT_AVERAGE_256                   0x8
#define SYSMON_BIT_AVERAGE_512                   0x9
#define SYSMON_BIT_AVERAGE_1024                  0xA
#define SYSMON_BIT_AVERAGE_2048                  0xB



typedef spi_if_type sysmon_ctrl_type;

#ifdef LINUX_COMPILE
void sysmon_init(sysmon_ctrl_type *self, unsigned char device_nr, unsigned char slave_nr);
#else /* LINUX_COMPILE */
void sysmon_init(sysmon_ctrl_type *self, XSpiPs *spi_if_ptr_init, unsigned char slave_nr_init);
#endif /* LINUX_COMPILE */
void sysmon_trigger_conversion(sysmon_ctrl_type *self, unsigned char channel);
float sysmon_get_temp(sysmon_ctrl_type *self);
int sysmon_get_temp_mdeg(sysmon_ctrl_type *self);
float sysmon_get_vdd(sysmon_ctrl_type *self);
int sysmon_get_vdd_mv(sysmon_ctrl_type *self);
float sysmon_get_voltage(sysmon_ctrl_type *self, unsigned char channel);
int sysmon_get_voltage_mv(sysmon_ctrl_type *self, unsigned char channel);
unsigned int sysmon_read_alarms(sysmon_ctrl_type *self);
unsigned int sysmon_read_channel(sysmon_ctrl_type *self, unsigned char channel);
void sysmon_read_channel_config(sysmon_ctrl_type *self, unsigned char channel, unsigned int *upper_threshold, unsigned int *lower_threshold, unsigned char *configuration);
void sysmon_read_global_config(sysmon_ctrl_type *self, unsigned int *channel_en, unsigned int *input_cfg, unsigned char *setup);
void sysmon_reset(sysmon_ctrl_type *self);
void sysmon_clear_channel_alarm(sysmon_ctrl_type *self, unsigned char channel);
void sysmon_clear_alarms(sysmon_ctrl_type *self);
void sysmon_write_channel(sysmon_ctrl_type *self, unsigned char channel);
void sysmon_write_channel_config(sysmon_ctrl_type *self, unsigned char channel, unsigned int upper_threshold, unsigned int lower_threshold, unsigned char configuration);
void sysmon_write_global_config(sysmon_ctrl_type *self, unsigned int channel_en, unsigned int input_cfg, unsigned char setup);

#endif /* __DRV_SYSMON_H__ */

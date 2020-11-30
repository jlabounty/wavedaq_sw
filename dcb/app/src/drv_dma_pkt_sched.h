/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WDAQ - DCB
 *
 *  Author  :  schmid_e
 *  Created :  26.11.2020 11:05:30
 *
 *  Description :  High level driver interface to the kernel driver of the
 *                 dma_packet_scheduler Vivado IP.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#ifndef __DRV_DMA_PKT_SCHED__
#define __DRV_DMA_PKT_SCHED__

#include <libudev.h>

#define DPS_EVENT_MODE_FREERUN   0
#define DPS_EVENT_MODE_COMMON    1

typedef struct dps_dev
{
  struct udev * udev;
  struct udev_device * dev;
} dps_dev_t;

int dps_dev_init (dps_dev_t * p_dps_dev, const char * p_sys_path);
int dps_get_data_bytes (dps_dev_t * p_dps_dev);
int dps_enable (dps_dev_t * p_dps_dev);
int dps_disable (dps_dev_t * p_dps_dev);
int dps_is_enabled (dps_dev_t * p_dps_dev);
int dps_set_event_mode (dps_dev_t * p_dps_dev, unsigned int value);
int dps_get_event_mode (dps_dev_t * p_dps_dev);
int dps_clr_buffers (dps_dev_t * p_dps_dev, unsigned int nr_of_buffers);
int dps_get_nr_of_buffers (dps_dev_t * p_dps_dev);
int dps_set_slot_enable (dps_dev_t * p_dps_dev, unsigned int value);
int dps_get_slot_enable (dps_dev_t * p_dps_dev);
int dps_reset (dps_dev_t * p_dps_dev);
int dps_set_udp_dst_ip_addr_charr (dps_dev_t * p_dps_dev, const unsigned char * p_ip_addr);
int dps_set_udp_dst_ip_addr_str (dps_dev_t * p_dps_dev, char * p_ip_addr);
const char * dps_get_udp_dst_ip_addr (dps_dev_t * p_dps_dev);
int dps_set_udp_dst_port (dps_dev_t * p_dps_dev, const unsigned int port);
int dps_get_udp_dst_port (dps_dev_t * p_dps_dev);
int dps_get_slots (dps_dev_t * p_dps_dev);
int dps_get_windows (dps_dev_t * p_dps_dev);
int dps_get_win_size (dps_dev_t * p_dps_dev);

#endif /* __DRV_DMA_PKT_SCHED__ */

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

#include "drv_dma_pkt_sched.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define DPS_DATA_BYTES_ATTR        "dps_ctrl/data_bytes\0" /* read only */
#define DPS_ENABLE_ATTR            "dps_ctrl/enable\0"
#define DPS_EVENT_MODE_ATTR        "dps_ctrl/event_mode\0"
#define DPS_NEXT_BUFFER_ATTR       "dps_ctrl/next_buffer\0"
#define DPS_RESET_ATTR             "dps_ctrl/reset\0"
#define DPS_SLOT_ENABLE_ATTR       "dps_ctrl/slot_enable\0"
#define DPS_UDP_DST_IP_ADDR_ATTR   "dps_ctrl/udp_dst_ip_addr\0"
#define DPS_UDP_DST_PORT_ATTR      "dps_ctrl/udp_dst_port\0"
#define DPS_SLOTS_ATTR             "dps_config/slots\0"    /* read only */
#define DPS_WIN_SIZE_ATTR          "dps_config/win_size\0" /* read only */
#define DPS_WINDOWS_ATTR           "dps_config/windows\0"  /* read only */

/**
 * @brief Initialization of the dps_dev structure
 *
 * Initializes the corresponding structure by creating a udev and a dev structure
 * and setting the corresponding pointers.
 *
 * @param p_dps_dev pointer to the dps_dev instance to be initialized
 * @param p_sys_path sysfs path to the dma_packet_scheduler where the parameters can be found
 * @return int 0 on success, the corresponding errno on failure
 */
int dps_dev_init (dps_dev_t * p_dps_dev, const char * p_sys_path)
{
  p_dps_dev->udev = udev_new();
  if (NULL == p_dps_dev->udev)
  {
    return errno;
  }

  p_dps_dev->dev = udev_device_new_from_syspath(p_dps_dev->udev, p_sys_path);
  if (NULL == p_dps_dev->dev)
  {
    return errno;
  }

  return 0;
}

/**
 * @brief Get the dma_packet_scheduler kernel drivers number of bytes in current packet
 *
 * @param p_dps_dev pointer to the dps_dev instance to be accessed
 * @return int number of bytes in current packet
 */
int dps_get_data_bytes (dps_dev_t * p_dps_dev)
{
  int val;

  if((NULL == p_dps_dev) || (NULL == p_dps_dev->dev))
  {
    val = 0;
  }
  else
  {
    val = strtol(udev_device_get_sysattr_value(p_dps_dev->dev, DPS_DATA_BYTES_ATTR), NULL, 0);
  }

  return val;
}

/**
 * @brief Enable dma_packet_scheduler Vivado IP through kernel driver
 *
 * @param p_dps_dev pointer to the dps_dev instance to be accessed
 * @return int greater or equal 0 on success, negative error code on failure
 */
int dps_enable (dps_dev_t * p_dps_dev)
{
  return udev_device_set_sysattr_value(p_dps_dev->dev, DPS_ENABLE_ATTR, "1\0");
}

/**
 * @brief Disable dma_packet_scheduler Vivado IP through kernel driver
 *
 * @param p_dps_dev pointer to the dps_dev instance to be accessed
 * @return int greater or equal 0 on success, negative error code on failure
 */
int dps_disable (dps_dev_t * p_dps_dev)
{
  return udev_device_set_sysattr_value(p_dps_dev->dev, DPS_ENABLE_ATTR, "0\0");
}

/**
 * @brief Check the dma_packet_scheduler kernel drivers enable status
 *
 * @param p_dps_dev pointer to the dps_dev instance to be accessed
 * @return int 0 if the DMA packet scheduler is disabled, 1 if it's enabled and -1 on error
 */
int dps_is_enabled (dps_dev_t * p_dps_dev)
{
  int val;

  if((NULL == p_dps_dev) || (NULL == p_dps_dev->dev))
  {
    val = -1;
  }
  else
  {
    val = strtol(udev_device_get_sysattr_value(p_dps_dev->dev, DPS_ENABLE_ATTR), NULL, 0);
  }

  return val;
}

/**
 * @brief Set dma_packet_scheduler kernel driver event mode attribute
 *
 * @param p_dps_dev pointer to the dps_dev instance to be accessed
 * @param value event mode specifier
 * @return int greater or equal 0 on success, negative error code on failure
 */
int dps_set_event_mode (dps_dev_t * p_dps_dev, unsigned int value)
{
  char buffer[3];

  sprintf(buffer, "%d\0", value);
  return udev_device_set_sysattr_value(p_dps_dev->dev, DPS_EVENT_MODE_ATTR, buffer);
}

/**
 * @brief Get the dma_packet_scheduler kernel drivers event mode attribute
 *
 * @param p_dps_dev pointer to the dps_dev instance to be accessed
 * @return int representing the event mode
 */
int dps_get_event_mode (dps_dev_t * p_dps_dev)
{
  int val;

  if((NULL == p_dps_dev) || (NULL == p_dps_dev->dev))
  {
    val = 0;
  }
  else
  {
    val = strtol(udev_device_get_sysattr_value(p_dps_dev->dev, DPS_EVENT_MODE_ATTR), NULL, 0);
  }

  return val;
}

/**
 * @brief Clear dma_packet_scheduler kernel driver buffers
 *
 * Note: If data is forwarded to UDP, this attribute should not be set.
 *
 * @param p_dps_dev pointer to the dps_dev instance to be accessed
 * @param nr_of_buffers number of buffers to be cleared
 * @return int greater or equal 0 on success, negative error code on failure
 */
int dps_clr_buffers (dps_dev_t * p_dps_dev, unsigned int nr_of_buffers)
{
  char buffer[32];

  sprintf(buffer, "%d\0", nr_of_buffers);
  return udev_device_set_sysattr_value(p_dps_dev->dev, DPS_NEXT_BUFFER_ATTR, buffer);
}

/**
 * @brief Get the dma_packet_scheduler kernel drivers number of buffers in the queue for reading
 *
 * Note that this information is only used when buffers are read directly. If data is forwarded to
 * UDP, there are no buffers in the read queue.
 *
 * @param p_dps_dev pointer to the dps_dev instance to be accessed
 * @return int number of buffers available
 */
int dps_get_nr_of_buffers (dps_dev_t * p_dps_dev)
{
  int val;

  if((NULL == p_dps_dev) || (NULL == p_dps_dev->dev))
  {
    val = 0;
  }
  else
  {
    val = strtol(udev_device_get_sysattr_value(p_dps_dev->dev, DPS_NEXT_BUFFER_ATTR), NULL, 0);
  }

  return val;
}

/**
 * @brief Set dma_packet_scheduler kernel driver slot enable bits
 *
 * @param p_dps_dev pointer to the dps_dev instance to be accessed
 * @param value slot enable bits as unsigned integer
 * @return int greater or equal 0 on success, negative error code on failure
 */
int dps_set_slot_enable (dps_dev_t * p_dps_dev, unsigned int value)
{
  char buffer[32];

  sprintf(buffer, "%d\0", value);
  return udev_device_set_sysattr_value(p_dps_dev->dev, DPS_SLOT_ENABLE_ATTR, buffer);
}

/**
 * @brief Get the dma_packet_scheduler kernel drivers slot enable bits
 *
 * @param p_dps_dev pointer to the dps_dev instance to be accessed
 * @return int with the slot enable bits
 */
int dps_get_slot_enable (dps_dev_t * p_dps_dev)
{
  int val;

  if((NULL == p_dps_dev) || (NULL == p_dps_dev->dev))
  {
    val = 0;
  }
  else
  {
    val = strtol(udev_device_get_sysattr_value(p_dps_dev->dev, DPS_SLOT_ENABLE_ATTR), NULL, 0);
  }

  return val;
}

/**
 * @brief Reset dma_packet_scheduler kernel driver
 *
 * @param p_dps_dev pointer to the dps_dev instance to be accessed
 * @return int greater or equal 0 on success, negative error code on failure
 */
int dps_reset (dps_dev_t * p_dps_dev)
{
  return udev_device_set_sysattr_value(p_dps_dev->dev, DPS_RESET_ATTR, "1\0");
}

/**
 * @brief Set dma_packet_scheduler kernel driver UDP destination IP address attribute
 *
 * @param p_dps_dev pointer to the dps_dev instance to be accessed
 * @param p_ip_addr pointer to an unsigned char array containing the IP address
 *                  (address format addr[0].addr[1].addr[2].addr[3])
 * @return int greater or equal 0 on success, negative error code on failure
 */
int dps_set_udp_dst_ip_addr_charr (dps_dev_t * p_dps_dev, const unsigned char * p_ip_addr)
{
  char buffer[32];

  sprintf(buffer, "%d.%d.%d.%d\0", p_ip_addr[0], p_ip_addr[1], p_ip_addr[2], p_ip_addr[3]);
  return udev_device_set_sysattr_value(p_dps_dev->dev, DPS_UDP_DST_IP_ADDR_ATTR, buffer);
}

/**
 * @brief Set dma_packet_scheduler kernel driver UDP destination IP address attribute
 *
 * @param p_dps_dev pointer to the dps_dev instance to be accessed
 * @param p_ip_addr pointer to a string containing the IP address (format n.n.n.n)
 *                  (address format addr[0].addr[1].addr[2].addr[3])
 * @return int greater or equal 0 on success, negative error code on failure
 */
int dps_set_udp_dst_ip_addr_str (dps_dev_t * p_dps_dev, char * p_ip_addr)
{
  return udev_device_set_sysattr_value(p_dps_dev->dev, DPS_UDP_DST_IP_ADDR_ATTR, p_ip_addr);
}

/**
 * @brief Get the dma_packet_scheduler kernel drivers UDP destination IP address attribute
 *
 * @param p_dps_dev pointer to the dps_dev instance to be accessed
 * @return int representing the UDP destination IP address
 */
const char * dps_get_udp_dst_ip_addr (dps_dev_t * p_dps_dev)
{
  if((NULL == p_dps_dev) || (NULL == p_dps_dev->dev))
  {
    return NULL;
  }
  else
  {
    return udev_device_get_sysattr_value(p_dps_dev->dev, DPS_UDP_DST_IP_ADDR_ATTR);
  }
}

/**
 * @brief Set dma_packet_scheduler kernel driver UDP destination port attribute
 *
 * @param p_dps_dev pointer to the dps_dev instance to be accessed
 * @param port port number
 * @return int greater or equal 0 on success, negative error code on failure
 */
int dps_set_udp_dst_port (dps_dev_t * p_dps_dev, const unsigned int port)
{
  char buffer[32];

  sprintf(buffer, "%d\0", port);
  return udev_device_set_sysattr_value(p_dps_dev->dev, DPS_UDP_DST_PORT_ATTR, buffer);
}

/**
 * @brief Get the dma_packet_scheduler kernel drivers UDP destination port attribute
 *
 * @param p_dps_dev pointer to the dps_dev instance to be accessed
 * @return int representing the UDP destination port, -1 on error
 */
int dps_get_udp_dst_port (dps_dev_t * p_dps_dev)
{
  int val;

  if((NULL == p_dps_dev) || (NULL == p_dps_dev->dev))
  {
    val = -1;
  }
  else
  {
    val = strtol(udev_device_get_sysattr_value(p_dps_dev->dev, DPS_UDP_DST_PORT_ATTR), NULL, 0);
  }

  return val;
}

/**
 * @brief Get the dma_packet_scheduler kernel drivers number of slots attribute
 *
 * Note: the slots are defined in the device-tree
 *
 * @param p_dps_dev pointer to the dps_dev instance to be accessed
 * @return int representing the number or slots, -1 on error
 */
int dps_get_slots (dps_dev_t * p_dps_dev)
{
  int val;

  if((NULL == p_dps_dev) || (NULL == p_dps_dev->dev))
  {
    val = -1;
  }
  else
  {
    val = strtol(udev_device_get_sysattr_value(p_dps_dev->dev, DPS_SLOTS_ATTR), NULL, 0);
  }

  return val;
}

/**
 * @brief Get the dma_packet_scheduler kernel drivers number of windows attribute
 *
 * Note: the number of windows are set by a driver module parameter
 *
 * @param p_dps_dev pointer to the dps_dev instance to be accessed
 * @return int representing the number of windows, -1 on error
 */
int dps_get_windows (dps_dev_t * p_dps_dev)
{
  int val;

  if((NULL == p_dps_dev) || (NULL == p_dps_dev->dev))
  {
    val = -1;
  }
  else
  {
    val = strtol(udev_device_get_sysattr_value(p_dps_dev->dev, DPS_WINDOWS_ATTR), NULL, 0);
  }

  return val;
}

/**
 * @brief Get the dma_packet_scheduler kernel drivers window size attribute
 *
 * Note: the window size is set by a driver module parameter
 *
 * @param p_dps_dev pointer to the dps_dev instance to be accessed
 * @return int representing the window size, -1 on error
 */
int dps_get_win_size (dps_dev_t * p_dps_dev)
{
  int val;

  if((NULL == p_dps_dev) || (NULL == p_dps_dev->dev))
  {
    val = -1;
  }
  else
  {
    val = strtol(udev_device_get_sysattr_value(p_dps_dev->dev, DPS_WIN_SIZE_ATTR), NULL, 0);
  }

  return val;
}

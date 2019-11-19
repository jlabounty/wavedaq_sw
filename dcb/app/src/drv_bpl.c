/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WDAQ - DCB
 *
 *  Author  :  schmid_e
 *  Created :  09.05.2019 12:43:45
 *
 *  Description :  SPI functions for communication DCB<->Slots.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#include "drv_bpl.h"
#include "system.h"
#include "drv_axi_dcb_reg_bank.h"
#include "register_map_dcb.h"
#include "sc_io.h"
#include "xfs_printf.h"
#include "dbg.h"
#ifndef LINUX_COMPILE
#include "sleep.h"
#else
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#endif

/******************************************************************************/

#ifdef LINUX_COMPILE
#undef Xil_AssertNonvoid
#define Xil_AssertNonvoid   assert
#define SPI_ASCII_TX_BUF_SIZE   512
#endif

/******************************************************************************/
/******************************************************************************/

void bpl_spi_init(bpl_spi_type *self, unsigned char device_nr, unsigned char slot_nr)
{
  spi_if_init(&(self->slot[slot_nr]), device_nr, slot_nr, 0, 8, 5000000, 0);
}

/******************************************************************************/

void bpl_spi_drive_en(int enable)
{
  unsigned int reg_val = DCB_ENABLE_BPL_SPI_DRIVER_MASK;

  if(enable)
  {
    reg_bank_write(DCB_REG_SET_CTRL, &reg_val, 1);
  }
  else
  {
    reg_bank_write(DCB_REG_CLR_CTRL, &reg_val, 1);
  }
}

/******************************************************************************/

int spi_transfer(bpl_spi_type *self, unsigned char slot_nr, char *SendBufPtr, char *RecvBufPtr, unsigned int ByteCount)
{
  spi_if_transfer(&(self->slot[slot_nr]), SendBufPtr, RecvBufPtr, ByteCount);
  return 1;
}

/******************************************************************************/

void spi_ascii_cmd(char* buff, unsigned char slot_nr)
{
  unsigned char tx_buff[SPI_ASCII_TX_BUF_SIZE];
  unsigned char txc;
  unsigned char rxc;
  int count = 0;
  int Status;
  int i;

  if (!buff) return;
  if (slot_nr > 16) return;

#ifdef LINUX_COMPILE
  init_spi_bpl(slot_nr);
#endif

  // count bytes to send...
  while ( (buff[count]!=0x00) && (buff[count]!=0x0a) && (buff[count]!=0x0d) ) count++;

//  XSpi_SetSlaveSelectReg(SYSPTR(spi_bpl), spi_slave_select[slot_nr]);

  if(count > SPI_ASCII_TX_BUF_SIZE-2)
  {
    if(DBG_ERR) xfs_printf("SPI Backplane ASCII command too long (max %d characters)\r\n", SPI_ASCII_TX_BUF_SIZE-2);
    return;
  }

  /* Add Start of Text */
  tx_buff[0] = 0x02;
  /* Copy Command */
  memcpy(&tx_buff[1], buff, count);
  /* Add End of Line */
  tx_buff[count+1] = 0x0D;

  /* Enable SPI driver */
  bpl_spi_drive_en(1);
  /* Transmit command */
  Status = spi_transfer(SYSPTR(spi_bpl), slot_nr, tx_buff, NULL, count+2);
  if (!Status)
  {
    if(DBG_ERR) xfs_printf("SPI Backplane Error: transmission error EOL\r\n");
  }

  txc = 0x00;
  count = 0;
  do
  {
    Status = spi_transfer(SYSPTR(spi_bpl), slot_nr, &txc, &rxc, 1);
    if (!Status)
    {
      if(DBG_ERR) xfs_printf("SPI Backplane Error: receive error in loop\r\n");
    }
    usleep(100);
    if (rxc>= 10) xfs_printf("%c",rxc);
  } while ((rxc != 0x03) && (++count < 10000));

  /* Disable SPI driver (wait for CS pullup first) */
  usleep(2000);
  bpl_spi_drive_en(0);
//  XSpi_SetSlaveSelectReg(SYSPTR(spi_bpl), 0xFFFFFFFF);
}

/******************************************************************************/

void spi_binary_cmd(char* tx_buff, char* rx_buff, unsigned char slot_nr, unsigned int len)
{
  int Status;

  if (!tx_buff) return;
  if (len==0) return;
  if (slot_nr > 16) return;

#ifdef LINUX_COMPILE
  init_spi_bpl(slot_nr);
#endif

//  XSpi_SetSlaveSelectReg(SYSPTR(spi_bpl), spi_slave_select[slot_nr]);

  /* Enable SPI driver */
  bpl_spi_drive_en(1);
  /* Send Command */
  Status = spi_transfer(SYSPTR(spi_bpl), slot_nr, tx_buff, rx_buff, len);
  if (!Status)
  {
    if(DBG_ERR) xfs_printf("SPI Backplane Error: transmission error buffer\r\n");
  }

  /* Disable SPI driver (wait for CS pullup first) */
  usleep(2000);
  bpl_spi_drive_en(0);
//  XSpi_SetSlaveSelectReg(SYSPTR(spi_bpl), 0xFFFFFFFF);
}

/******************************************************************************/

void spi_flash_id_cmd(unsigned char slot_nr)
{
  unsigned char tx_buf[4] = {0x9F, 0x00, 0x00, 0x00};
  unsigned char rx_buf[4] = {0x00, 0x00, 0x00, 0x00};
  int Status;

#ifdef LINUX_COMPILE
  init_spi_bpl(slot_nr);
#endif

  if (slot_nr > 16) return;

  /* Enable SPI driver */
  bpl_spi_drive_en(1);
  set_gpio(BIT_IDX_EMIO_CTRL_FLASH_SEL_PIN, 1);
  set_gpio(BIT_IDX_EMIO_CTRL_INIT_PIN, 1);
  usleep(1000);
//  XSpi_SetSlaveSelectReg(SYSPTR(spi_bpl), spi_slave_select[slot_nr]);
//  XSpi_SetSlaveSelect(SYSPTR(spi_bpl), ~spi_slave_select[slot_nr]);
  Status = spi_transfer(SYSPTR(spi_bpl), slot_nr, tx_buf, rx_buf, 4);
  if (!Status)
  {
    if(DBG_ERR) xfs_printf("Read Flash ID Error\r\n");
  }
//  XSpi_SetSlaveSelectReg(SYSPTR(spi_bpl), 0xFFFFFFFF);
  set_gpio(BIT_IDX_EMIO_CTRL_INIT_PIN, 0);
  set_gpio(BIT_IDX_EMIO_CTRL_FLASH_SEL_PIN, 0);
  /* Disable SPI driver (wait for CS pullup first) */
  usleep(2000);
  bpl_spi_drive_en(0);
  //emio_set_pin(SYSPTR(gpio_mio), BIT_IDX_EMIO_CTRL_INIT_PIN, 0);
  xfs_printf("Flash ID (0x%02X) 0x%02X 0x%02X 0x%02X\r\n", rx_buf[0], rx_buf[1], rx_buf[2], rx_buf[3]);
}

/******************************************************************************/
/******************************************************************************/

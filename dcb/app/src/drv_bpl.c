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
#define SPI_ASCII_TX_BUF_SIZE     512
#define SPI_ASCII_RX_BURST_LEN     32 /* Must be smaller than SPI_ASCII_TX_BUF_SIZE */
#endif

/******************************************************************************/
/******************************************************************************/

#define BIN_CMD_WRITE8    0x11
#define BIN_CMD_WRITE16   0x12
#define BIN_CMD_WRITE32   0x14
#define BIN_CMD_READ8     0x21
#define BIN_CMD_READ16    0x22
#define BIN_CMD_READ32    0x24

#define BPL_SPI_SCHEME(x)     (set_gpio(BIT_IDX_EMIO_CTRL_BPL_SPI_SCHEME_PIN, x))
#define BPL_FLASH_SEL(x)      (set_gpio(BIT_IDX_EMIO_CTRL_FLASH_SEL_PIN, x))
#define BPL_INIT(x)           (set_gpio(BIT_IDX_EMIO_CTRL_INIT_PIN, x))

#define HW_VERS_WDB_MAGIC_MASK    0xFF000000
#define HW_VERS_WDB_VENDOR_MASK   0x00FF0000
#define HW_VERS_WDB_TYPE_MASK     0x0000FF00
#define HW_VERS_REV_MASK          0x000000FC
#define HW_VERS_VAR_MASK          0x00000003
#define HW_VERS_WDB_COMMON_MASK   (HW_VERS_WDB_MAGIC_MASK | HW_VERS_WDB_VENDOR_MASK | HW_VERS_WDB_TYPE_MASK)
#define HW_VERS_WDB_MAGIC_VAL     0xAC000000
#define HW_VERS_WDB_VENDOR_VAL    0x00010000
#define HW_VERS_WDB_TYPE_VAL      0x00000200
#define HW_VERS_WDB_REV_F_VAL     0x00000014
#define HW_VERS_WDB_REV_G_VAL     0x00000018
#define HW_VERS_WDB_COMMON_VAL    (HW_VERS_WDB_MAGIC_VAL | HW_VERS_WDB_VENDOR_VAL | HW_VERS_WDB_TYPE_VAL)

/******************************************************************************/
/******************************************************************************/

char* set_bpl_spi_scheme(unsigned int slot_nr);

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

void select_slot(unsigned int slot_nr)
{
  if ( (slot_nr > 17) || (slot_nr == 16) ) return;

  if ( slot_nr == 17 )
  {
    /* special case TCB slot select */
    set_gpio(BOARD_SEL_OFFSET+16, 1);
  }
  else
  {
    set_gpio(BOARD_SEL_OFFSET+slot_nr, 1);
  }
}

/******************************************************************************/

void deselect_all_slots()
{
  int i;

  for(i=0;i<17;i++)
  {
    set_gpio(BOARD_SEL_OFFSET+i, 0);
  }
}

/******************************************************************************/

int connect_fpga(unsigned int slot_nr)
{
  /* Add user space mutex to make sure only one board is selected at a time */
    /* Return 1 if connection established successfully else 0 */
  if(set_bpl_spi_scheme(slot_nr))
  {
    /* Configure for board in slot */
    bpl_spi_drive_en(1);
    select_slot(slot_nr);
    return 1;
  }
  else
  {
    return 0;
  }
}

/******************************************************************************/

char* connect_flash(unsigned int slot_nr)
{
  /* Add user space mutex to make sure only one board is selected at a time */
    /* Return 1 if connection established successfully else 0 */
  char *default_fw_sw_path;

  if( default_fw_sw_path = set_bpl_spi_scheme(slot_nr) )
  {
    /* Configure for board in slot */
    bpl_spi_drive_en(1);
    BPL_FLASH_SEL(1);
    BPL_INIT(1);
    select_slot(slot_nr);
  }
  return default_fw_sw_path;
}

/******************************************************************************/

void disconnect()
{
  deselect_all_slots();
  usleep(2000);
  BPL_FLASH_SEL(0);
  BPL_INIT(0);
  bpl_spi_drive_en(0);
}

/******************************************************************************/

void bpl_spi_init(bpl_spi_type *self, unsigned char device_nr)
{
  spi_if_init(&(self->slot_fpga), device_nr, SPI_SLAVE_SLOT_FPGA, 0, 8, 5000000, 0);
//  spi_if_init(&(self->slot_wdb_flash), device_nr, SPI_SLAVE_SLOT_WDB_FLASH, 0, 8, 5000000, 0);
//  spi_if_init(&(self->slot_tcb_flash), device_nr, SPI_SLAVE_SLOT_TCB_FLASH, 0, 8, 5000000, 0);
  deselect_all_slots();
}

/******************************************************************************/

int spi_transfer(bpl_spi_type *self, unsigned char slot_nr, char *SendBufPtr, char *RecvBufPtr, unsigned int ByteCount)
{
  spi_if_transfer(&(self->slot_fpga), SendBufPtr, RecvBufPtr, ByteCount);
  return 1;
}

/******************************************************************************/

void spi_ascii_cmd(char* txbuff, char *rxbuff, unsigned int rxsize, unsigned char slot_nr)
{
  unsigned char tx_buff[SPI_ASCII_TX_BUF_SIZE];
  unsigned char rx_buff[SPI_ASCII_RX_BURST_LEN];
  int eot = 0;
  int count = 0;
  int Status;
  int i;

  if (!txbuff) return;

#ifdef LINUX_COMPILE
  init_spi_bpl();
#endif

  /* count bytes to send... */
  while ( (txbuff[count]!=0x00) && (txbuff[count]!=0x0a) && (txbuff[count]!=0x0d) ) count++;

  if(count > SPI_ASCII_TX_BUF_SIZE-2)
  {
    if(DBG_ERR) xfs_printf("SPI Backplane ASCII command too long (max %d characters)\r\n", SPI_ASCII_TX_BUF_SIZE-2);
    return;
  }

  /* Add Start of Text */
  tx_buff[0] = 0x02;
  /* Copy Command */
  memcpy(&tx_buff[1], txbuff, count);
  /* Add End of Line */
  tx_buff[count+1] = 0x0D;

  /* clear return buffer */
  memset(rxbuff, 0, rxsize);

  if(connect_fpga(slot_nr))
  {
    /* Transmit command */
    Status = spi_transfer(SYSPTR(spi_bpl), slot_nr, tx_buff, NULL, count+2);
    if (!Status)
    {
      if(DBG_ERR) xfs_printf("SPI Backplane Error: transmission error EOL\r\n");
    }

    memset(tx_buff, 0, SPI_ASCII_RX_BURST_LEN);
    count = 0;
    do
    {
      memset(rx_buff, 0, SPI_ASCII_RX_BURST_LEN);
      Status = spi_transfer(SYSPTR(spi_bpl), slot_nr, tx_buff, rx_buff, SPI_ASCII_RX_BURST_LEN);
      if (!Status)
      {
        if(DBG_ERR) xfs_printf("SPI Backplane Error: receive error in loop\r\n");
      }
      usleep(100);
      i = 0;
      while( (i < SPI_ASCII_RX_BURST_LEN) && (rx_buff[i] != 0x03) )
      {
        if (count < rxsize && rx_buff[i]>=10)
           rxbuff[count++] = rx_buff[i];
        i++;
      }
      if (count < rxsize)
         rxbuff[count] = 0;
    } while ((rx_buff[i] != 0x03) && (count < rxsize));
  }

  disconnect();
}

/******************************************************************************/

void spi_binary_cmd(char* tx_buff, char* rx_buff, unsigned char slot_nr, unsigned int len)
{
  int Status;

  if (!tx_buff) return;
  if (len==0) return;
  if (slot_nr > 16) return;

#ifdef LINUX_COMPILE
  init_spi_bpl();
#endif

  if(connect_fpga(slot_nr))
  {
    /* Send Command */
    Status = spi_transfer(SYSPTR(spi_bpl), slot_nr, tx_buff, rx_buff, len);
    if (!Status)
    {
      if(DBG_ERR) xfs_printf("SPI Backplane Error: transmission error buffer\r\n");
    }
  }

  disconnect();
}

/******************************************************************************/

void bpl_upload_fw_sw(slot_op_en_type *slot, char *fw_spec_p, char *sw_spec_p)
{
  int i;
  char fw_def_path[250];
  char sw_def_path[250];
  char *fwp;
  char *swp;
  int use_default_files;
  char *default_fw_sw_path = NULL;

#ifdef LINUX_COMPILE
  init_spi_bpl();
#endif

  if( (fw_spec_p==NULL) && (sw_spec_p==NULL) )
  {
    use_default_files = 1;
    fwp = fw_def_path;
    swp = sw_def_path;
  }
  else
  {
    use_default_files = 0;
    fwp = fw_spec_p;
    swp = sw_spec_p;
  }

  for(i=0;i<17;i++)
  {
    if(slot->op_en[i])
    {
      if( default_fw_sw_path = connect_flash(i) )
      {
        if( use_default_files )
        {
          printf("default path: %s\n", default_fw_sw_path);
          if(strstr(default_fw_sw_path, "/wdb/"))
          {
            /* Copy directory and filename to fw_def_path */
            strcpy(fwp, default_fw_sw_path);
            strcpy(&fwp[strlen(default_fw_sw_path)], wdb_fw_default_file);
            printf("slot %d: uploading WDB firmware %s ... ", i, fwp);
            /* Generate Header for flash */
            /* Check FPGA (local header) */
            /* Erase block */
            /* Transfer bitfile */
            /* Transfer header */
            printf("done\n");
            /* Copy directory and filename to sw_def_path */
            strcpy(swp, default_fw_sw_path);
            strcpy(&swp[strlen(default_fw_sw_path)], wdb_sw_default_file);
            printf("slot %d: uploading WDB software %s ... ", i, fwp);
            /* Generate Header for flash */
            /* Check FPGA (local header) */
            /* Erase block */
            /* Transfer srec file */
            /* Transfer header */
            printf("done\n");
          }
          if(strstr(default_fw_sw_path, "/tcb/"))
          {
            /* Copy directory and filename to fw_def_path */
            strcpy(fwp, default_fw_sw_path);
            strcpy(&fwp[strlen(default_fw_sw_path)], tcb_fw_default_file);
            printf("slot %d: uploading TCB firmware %s ... ", i, fwp);
            /* Generate Header for flash */
            /* Check FPGA (local header) */
            /* Erase block */
            /* Transfer bitfile */
            /* Transfer header */
            printf("done\n");
          }
        }
        else
        {
          if(fwp)
          {
            printf("slot %d: uploading firmware %s ... ", i, fwp);
            printf("done\n");
          }
          if(swp)
          {
            printf("slot %d: uploading software %s ... ", i, swp);
            printf("done\n");
          }
        }
      }
      else
      {
        printf("Error: unable to connect to slot %d\n", i);
      }

      disconnect();
    }
  }
  printf("\n");
}

/******************************************************************************/

void spi_flash_id_cmd(unsigned char slot_nr)
{
  unsigned char tx_buf[4] = {0x9F, 0x00, 0x00, 0x00};
  unsigned char rx_buf[4] = {0x00, 0x00, 0x00, 0x00};
  int Status;

#ifdef LINUX_COMPILE
  init_spi_bpl();
#endif

  if (slot_nr > 16) return;

  /* Enable SPI driver */
  bpl_spi_drive_en(1);
  BPL_FLASH_SEL(1);
  BPL_INIT(1);
  usleep(1000);
//  XSpi_SetSlaveSelectReg(SYSPTR(spi_bpl), spi_slave_select[slot_nr]);
//  XSpi_SetSlaveSelect(SYSPTR(spi_bpl), ~spi_slave_select[slot_nr]);
  Status = spi_transfer(SYSPTR(spi_bpl), slot_nr, tx_buf, rx_buf, 4);
  if (!Status)
  {
    if(DBG_ERR) xfs_printf("Read Flash ID Error\r\n");
  }
//  XSpi_SetSlaveSelectReg(SYSPTR(spi_bpl), 0xFFFFFFFF);
  BPL_INIT(0);
  BPL_FLASH_SEL(0);
  /* Disable SPI driver (wait for CS pullup first) */
  usleep(2000);
  bpl_spi_drive_en(0);
  //emio_set_pin(SYSPTR(gpio_mio), BIT_IDX_EMIO_CTRL_INIT_PIN, 0);
  xfs_printf("Flash ID (0x%02X) 0x%02X 0x%02X 0x%02X\r\n", rx_buf[0], rx_buf[1], rx_buf[2], rx_buf[3]);
}

/******************************************************************************/

unsigned int spi_get_ref_reg(unsigned char slot_nr)
{
  char tx_buff[10] = {BIN_CMD_READ32, 0x00, 0x00, 0x00, 0x00, 0xFF,  0x00, 0x00, 0x00, 0x00};
  char rx_buff[10] = {0};
  unsigned int hw_rev_val;
  int Status;
  int i;

  if (slot_nr > 16) return 0;

  /* Enable SPI driver */
  bpl_spi_drive_en(1);
  select_slot(slot_nr);

  /* Send Command */
  Status = spi_transfer(SYSPTR(spi_bpl), slot_nr, tx_buff, rx_buff, sizeof(tx_buff));
  if (!Status)
  {
    if(DBG_ERR) xfs_printf("SPI Backplane Error: transmission error when reading reference register\r\n");
    return 0;
  }

  for(i=6;i<10;i++)
  {
    hw_rev_val <<= 8;
    hw_rev_val |= (0xFF & (unsigned int)(rx_buff[i]));
  }

  /* Disable SPI driver (wait for CS pullup first) */
  deselect_all_slots();
  usleep(2000);
  bpl_spi_drive_en(0);
  return hw_rev_val;
}

/******************************************************************************/

char* set_bpl_spi_scheme(unsigned int slot_nr)
{
  /* Returns pointer to default fw/sw path if successfull else NULL pointer */
  unsigned int hw_rev_val;

  /* Set scheme 0 */
  BPL_SPI_SCHEME(0);
  /* Check connection */
  hw_rev_val = spi_get_ref_reg(slot_nr);
  if( (hw_rev_val&HW_VERS_WDB_COMMON_MASK) == HW_VERS_WDB_COMMON_VAL)
  {
    if( (hw_rev_val&HW_VERS_REV_MASK) <= HW_VERS_WDB_REV_F_VAL)
    {
      if(DBG_SPAM) xfs_printf("Scheme 0 selected for slot %d\r\n", slot_nr);
      return (char*)wdb_rf_default_path;
    }
  }
  /* Add TCB case */

  /* Set scheme 1 */
  BPL_SPI_SCHEME(1);
  /* Check connection */
  hw_rev_val = spi_get_ref_reg(slot_nr);
  if( (hw_rev_val&HW_VERS_WDB_COMMON_MASK) == HW_VERS_WDB_COMMON_VAL)
  {
    if( (hw_rev_val&HW_VERS_REV_MASK) >= HW_VERS_WDB_REV_G_VAL)
    {
      if(DBG_SPAM) xfs_printf("Scheme 1 selected for slot %d\r\n", slot_nr);
      return (char*)wdb_rg_default_path;
    }
  }

  if(DBG_SPAM) xfs_printf("Board identification failed for slot %d\r\n", slot_nr);
  return NULL;
}

/******************************************************************************/
/******************************************************************************/

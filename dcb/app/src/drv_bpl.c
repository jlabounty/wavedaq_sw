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
#include "xilinx_cfg.h"
#include "drv_qspi_flash.h"
#include "flash_memory_maps.h"
#include "xfs_printf.h"
#include "dbg.h"
#ifndef LINUX_COMPILE
#include "sleep.h"
#else
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
//#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
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
#define HW_VERS_REV_OFFS          2
#define HW_VERS_WDB_COMMON_VAL    (HW_VERS_WDB_MAGIC_VAL | HW_VERS_WDB_VENDOR_VAL | HW_VERS_WDB_TYPE_VAL)

#define FLASH_BUF_SIZE            8192 /* 8k */

/******************************************************************************/
/******************************************************************************/

int get_slot_board_info(unsigned int slot_nr, unsigned int *board_type_id, unsigned int *board_rev_id);

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

int connect_fpga(unsigned int slot_nr, unsigned int board_type, unsigned int board_rev)
{
  /* Add user space mutex to make sure only one board is selected at a time */
  /* Configure for board in slot */
  BPL_SPI_SCHEME(bpl_spi_scheme[board_type][board_rev]);
  bpl_spi_drive_en(1);
  select_slot(slot_nr);
  return 1;
}

/******************************************************************************/

flash_memory_map_type* connect_flash(unsigned int slot_nr, unsigned int board_type, unsigned int board_rev)
{
  /* Add user space mutex to make sure only one board is selected at a time */
  /* Return 1 if connection established successfully else 0 */
  flash_memory_map_type *flash_mem_map = NULL;

  flash_mem_map = get_flash_mem_map(board_type, board_rev);

  if( flash_mem_map )
  {
    /* Configure for board in slot */
    BPL_SPI_SCHEME(bpl_spi_scheme[board_type][board_rev]);
    bpl_spi_drive_en(1);
    BPL_FLASH_SEL(1);
    BPL_INIT(1);
    select_slot(slot_nr);
  }
  return flash_mem_map;
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

void spi_ascii_cmd(char* txbuff, char *rxbuff, unsigned int rxsize, unsigned char slot_nr, unsigned int board_type, unsigned int board_revision)
{
  unsigned char tx_buff[SPI_ASCII_TX_BUF_SIZE];
  unsigned char rx_buff[SPI_ASCII_RX_BURST_LEN];
  int eot = 0;
  int count = 0;
  int Status;
  int i;

  if (!txbuff) return;
  if ( (slot_nr > 17) || (slot_nr == 16) ) return;

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

  if(connect_fpga(slot_nr, board_type, board_revision))
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

void spi_binary_cmd(char* tx_buff, char* rx_buff, unsigned int len, unsigned char slot_nr, unsigned int board_type, unsigned int board_revision)
{
  int Status;

  if (!tx_buff) return;
  if (len==0) return;
  if ( (slot_nr > 17) || (slot_nr == 16) ) return;

#ifdef LINUX_COMPILE
  init_spi_bpl();
#endif

  if(connect_fpga(slot_nr, board_type, board_revision))
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

void wr_fw(char *fw_file, flash_memory_map_type *flash_mem_map, const char *flash_partition_name)
{
  int header_len;
  unsigned int len;
  bitfile_info_type bit_inf;
  bitfile_info_type bit_inf_swapped;
  qspi_flash_partition flash_partition;
  flash_partition_type *mtd_ptr = NULL;
  int fd;
  unsigned int   ers_size;
  unsigned int   tot_ers_size;
  unsigned int   flash_offs;
  unsigned int   flash_len;
  unsigned char  buff[FLASH_BUF_SIZE];
  int i;

  /* open bitfile */
  fd = open(fw_file, O_RDONLY);

  /* return if no valid file */
  if(!fd) return;

  /* check flash partition */
  if( !(mtd_ptr = get_flash_partition(flash_mem_map, flash_partition_name)) )
  {
    if(DBG_ERR) printf("Error: partition %s not found\n", flash_partition_name);
    return;
  }

  if( !(qspi_flash_init(&flash_partition, mtd_ptr->mtd_partition)) )
  {
    if(DBG_ERR) printf("Error: flash partition %s accesse failed\n", flash_partition_name);
    return;
  }

  /* parse header for flash */
  len = read(fd, buff, 1024);
  header_len = parse_bitfile(buff, len, &bit_inf);

  /* Check FPGA (local header) */
  if (header_len > 0)
  {
    /* got valid header */
    if(DBG_INF0)
    {
      printf("Bit file header:\n");
      for (i=0; i<4; i++)
      {
        printf("%-10s : %s\r\n", info_field_name[i], buff + bit_inf.field[i]);
      }
      printf("Image size : %d Bytes\r\n", bit_inf.info.data_len);
    }
    byte_swap_uint32(bit_inf.field, bit_inf_swapped.field, sizeof(bit_inf)/sizeof(unsigned int));

    /* check fpga type */
    if(flash_mem_map->fpga_type)
    {
      len = bit_inf.info.date_offs - bit_inf.info.fpga_offs;
      if (strncmp(flash_mem_map->fpga_type, (const char*) buff + bit_inf.info.fpga_offs, len) != 0)
      {
        if (DBG_WARN) printf("Warning: Bitfile for wrong FPGA type: %s  expected: %s\r\n", buff + bit_inf.info.fpga_offs, flash_mem_map->fpga_type);
        return;
      }
    }

    /* check fpga uid */
/*
    if (flash_mem_map->fpga_uid)
    {
      len = bit_inf.info.date_offs - bit_inf.info.fpga_offs;
      if (strncmp(flash_mem_map->fpga_type, (const char*) buff + bit_inf.info.fpga_offs, len) != 0)
      {
        if (DBG_WARN) xfs_local_printf("Warning: Bitfile for wrong FPGA type: %s  expected: %s\r\n", buff + bit_inf.info.fpga_offs, flash_mem_map->fpga_type);
      }
    }
 */

    /* Erase partition */
    /* qspi_flash_erase_partition(&flash_partition); */
    /* Erase header only */
    if(DBG_INF0) printf("deleting header...");
    fflush(stdout);
    qspi_flash_erase_sector(&flash_partition, mtd_ptr->header_offset);
    if(DBG_INF0) printf("done\n");
    /* Erase bitfile only */
    ers_size = 0;
    tot_ers_size=0;
    while(tot_ers_size<bit_inf.info.data_len)
    {
      ers_size = qspi_flash_erase_sector(&flash_partition, tot_ers_size);
      tot_ers_size += ers_size;
      if(tot_ers_size>bit_inf.info.data_len) tot_ers_size = bit_inf.info.data_len; /* Keep progress bar <= 100% */
      display_progress("deleting bitstream ", 100*tot_ers_size/bit_inf.info.data_len, ' ', '-');
      fflush(stdout);
    }

    /* write bitfile excluding header */
    lseek(fd, header_len, SEEK_SET); /* go back to start of file */
    flash_offs = 0;
    flash_len  = FLASH_BUF_SIZE;
    while(flash_len == FLASH_BUF_SIZE)
    {
      flash_len = read(fd, buff, FLASH_BUF_SIZE);
      qspi_flash_write(&flash_partition, flash_offs, flash_len, buff);
      flash_offs += flash_len;
      display_progress("writing bitstream  ", 100*flash_offs/bit_inf.info.data_len, '-', '#');
      fflush(stdout);
    }
    if(DBG_INF0) printf("\n");

    /* write header */
    lseek(fd, 0, SEEK_SET); /* go back to start of file */
    if(mtd_ptr->header_offset) /* check if header has to be written */
    {
      if(DBG_INF0) printf("writing header...");
      fflush(stdout);
      flash_offs = mtd_ptr->header_offset;
      flash_len  = sizeof(bitfile_info_type);
      qspi_flash_write(&flash_partition, flash_offs, flash_len, (unsigned char*) &bit_inf_swapped);
      flash_offs += flash_len;
      flash_len   = header_len;
      read(fd, buff, flash_len);
      qspi_flash_write(&flash_partition, flash_offs, flash_len, buff);
      if(DBG_INF0) printf("done\n");
    }
  }

  fsync(fd); /* flush caches to make sure operation completes before desecting board */
  if(close(fd) < 0) if(DBG_INF0) printf("Error closing file\n");
}

/******************************************************************************/

void wr_sw(char *sw_file, flash_memory_map_type *flash_mem_map, const char *flash_partition_name)
{
  int header_len;
  unsigned int len;
  sw_file_info_type sw_info;
  qspi_flash_partition flash_partition;
  flash_partition_type *mtd_ptr = NULL;
  int fd;
  unsigned int   ers_size;
  unsigned int   tot_ers_size;
  unsigned int   flash_offs;
  unsigned int   flash_len;
  unsigned char  buff[FLASH_BUF_SIZE];
  unsigned char sr_header_buf[SREC_MAX_BYTES];
  struct stat file_stat;
  int i;

  /* open bitfile */
  fd = open(sw_file, O_RDONLY);

  /* return if no valid file */
  if(!fd) return;
  stat(sw_file, &file_stat);

  /* check flash partition */
  if( !(mtd_ptr = get_flash_partition(flash_mem_map, flash_partition_name)) )
  {
    if(DBG_ERR) printf("Error: partition %s not found\n", flash_partition_name);
    return;
  }

  if( !(qspi_flash_init(&flash_partition, mtd_ptr->mtd_partition)) )
  {
    if(DBG_ERR) printf("Error: flash partition %s accesse failed\n", flash_partition_name);
    return;
  }

  /* parse header for flash */
  len = read(fd, buff, SREC_MAX_BYTES);
  header_len = parse_srec(buff, sr_header_buf);

  /* Check FPGA (local header) */
  if (header_len > 0)
  {
    /* got valid header */
    if( DBG_INF0 ) printf("SREC header:\n%s \r\n", sr_header_buf);
//par->fw_comp_lvl = get_sw_fcl((char*)sr_header_buf);
//par->reg_layout_comp_lvl = get_sw_rcl((char*)sr_header_buf);

    /* Erase partition */
   /* qspi_flash_erase_partition(&flash_partition); */
    ers_size = 0;
    tot_ers_size=0;
    while(tot_ers_size<flash_partition.mtd_info.size)
    {
      ers_size = qspi_flash_erase_sector(&flash_partition, tot_ers_size);
      tot_ers_size += ers_size;
      display_progress("deleting software  ", 100*tot_ers_size/flash_partition.mtd_info.size, ' ', '-');
      fflush(stdout);
    }

    /* write bitfile excluding header */
    lseek(fd, 0, SEEK_SET); /* go back to start of file */
    flash_len  = FLASH_BUF_SIZE;
    flash_offs = 0;
    while(flash_len == FLASH_BUF_SIZE)
    {
      flash_len = read(fd, buff, FLASH_BUF_SIZE);
      qspi_flash_write(&flash_partition, flash_offs, flash_len, buff);
      flash_offs += flash_len;
      display_progress("writing software   ", 100*flash_offs/file_stat.st_size, '-', '#');
      fflush(stdout);
    }
    if(DBG_INF0) printf("\n");

    /* write header part 1 (info) */
    if(DBG_INF0) printf("writing header (info)...");
    fflush(stdout);
    sw_info.info.name_offs = sizeof(sw_file_info_type);
    sw_info.info.data_len  = file_stat.st_size;
    sw_info.info.head_len  = header_len;
    sw_info.info.checksum  = sw_file_info_checksum(&sw_info);
    flash_offs = mtd_ptr->header_offset;
    flash_len  = sizeof(sw_file_info_type);
    qspi_flash_write(&flash_partition, flash_offs, flash_len, (unsigned char*) &sw_info);
    if(DBG_INF0) printf("done\n");
    /* write header part 2 (filename) */
    if(DBG_INF0) printf("writing header (filename)...");
    fflush(stdout);
    flash_offs = mtd_ptr->header_offset + sizeof(sw_file_info_type);
    flash_len  = header_len+1;
    qspi_flash_write(&flash_partition, flash_offs, flash_len, sr_header_buf);
    if(DBG_INF0) printf("done\n");
  }

  fsync(fd); /* flush caches to make sure operation completes before desecting board */
  if(close(fd) < 0) if(DBG_INF0) printf("Error closing file\n");
}

/******************************************************************************/

void slot_upload_fw_sw(unsigned int slot_nr, int load_fw, char *fw_spec_p, int load_sw, char *sw_spec_p, unsigned int board_type, unsigned int board_rev)
{
  char fw_def_path[250];
  char sw_def_path[250];
  char *fwp;
  char *swp;
#ifdef LINUX_COMPILE
  flash_memory_map_type *flash_mem_map = NULL;

  init_spi_bpl();
#endif

  if(fw_spec_p) fwp = fw_spec_p;
  else          fwp = fw_def_path;

  if(sw_spec_p) swp = sw_spec_p;
  else          swp = sw_def_path;

  if(DBG_INF0) printf("\nSlot %d:\n", slot_nr);

  if(flash_mem_map = connect_flash(slot_nr, board_type, board_rev))
  {
    if(DBG_INF0) printf("default path: %s\n", flash_mem_map->default_fw_path);
  }
  else
  {
    if(DBG_ERR) printf("Error: flash memory map not found (type %d, revision %d)\n", board_type, board_rev);
    return;
  }

  if(strstr(flash_mem_map->default_fw_path, "/wdb/"))
  {
    /* WDB */
    if(load_fw)
    {
      if(!fw_spec_p)
      {
        /* set default path according to type and revision */
        strcpy(fwp, flash_mem_map->default_fw_path);
        strcpy(&fwp[strlen(flash_mem_map->default_fw_path)], wdb_fw_default_file);
      }
      /* upload firmware */
      if(DBG_INF0) printf("-> Uploading WDB firmware %s\n", fwp);
      wr_fw(fwp, flash_mem_map, "fw");
    }
    if(load_sw)
    {
      if(!sw_spec_p)
      {
        /* set default path according to type and revision */
        strcpy(swp, flash_mem_map->default_fw_path);
        strcpy(&swp[strlen(flash_mem_map->default_fw_path)], wdb_sw_default_file);
      }
      /* upload sofware */
      if(DBG_INF0) printf("-> Uploading WDB software %s\n", swp);
      wr_sw(swp, flash_mem_map, "sw");
    }
  }
  else if(strstr(flash_mem_map->default_fw_path, "/tcb/"))
  {
    /* TCB */
    if(load_fw)
    {
      if(!fw_spec_p)
      {
        /* set default path according to type and revision */
        strcpy(fwp, flash_mem_map->default_fw_path);
        strcpy(&fwp[strlen(flash_mem_map->default_fw_path)], tcb_fw_default_file);
      }
      /* upload firmware */
      if(DBG_INF0) printf("-> Uploading TCB firmware %s\n", fwp);
      wr_fw(fwp, flash_mem_map, "fw");
    }
  }

  disconnect();

  if(DBG_INF0) printf("\n");
}

/******************************************************************************/

void crate_upload_fw_sw(slot_op_en_type *slot, int load_fw, char *fw_spec_p, int load_sw, char *sw_spec_p, unsigned int board_type, unsigned int board_rev, unsigned int force)
{
  int i;
  unsigned int slot_board_type;
  unsigned int slot_board_rev;

#ifdef LINUX_COMPILE
  init_spi_bpl();
#endif

  for(i=0;i<18;i++)
  {
    if( (slot->op_en[i]) && (i!=16) ) /* don't do DCB slot (16) */
    {
      if(get_slot_board_info(i, &slot_board_type, &slot_board_rev))
      {
        if(force)
        {
          /* get forced upload information */
          if(DBG_INF0) printf("FORCED upload\n");
          if( (board_type != slot_board_type) || (board_rev != slot_board_rev) )
          {
            if(DBG_ERR) printf("Error: present board in slot %d does not match type and revision\n", i);
            continue;
          }
        }
        else
        {
          if(DBG_INF0) printf("Standard upload\n");
        }
      }
      else
      {
        if(force)
        {
          slot_board_type = board_type;
          slot_board_rev  = board_rev;
        }
        else
        {
          /* no slot board information for standard upload */
          if(DBG_ERR) printf("Error: board information for slot %d could not be read\n", i);
          return;
        }
      }

      slot_upload_fw_sw(i, load_fw, fw_spec_p, load_sw, sw_spec_p, slot_board_type, slot_board_rev);
    }
  }
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

  if (slot_nr > 17) return 0;
  if (slot_nr ==16) return 0;

#ifdef LINUX_COMPILE
  init_spi_bpl();
#endif

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

/* Remove when TCB is modified to instantly reply on SPI read */
unsigned int spi_get_ref_reg_tcb(unsigned char slot_nr)
{
  char tx_buff[11] = {BIN_CMD_READ32, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00};
  char rx_buff[11] = {0};
  unsigned int hw_rev_val;
  int Status;
  int i;

  if (slot_nr > 17) return 0;
  if (slot_nr ==16) return 0;

#ifdef LINUX_COMPILE
  init_spi_bpl();
#endif

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

  for(i=7;i<11;i++)
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

int get_slot_board_info(unsigned int slot_nr, unsigned int *board_type_id, unsigned int *board_rev_id)
{
  unsigned int hw_rev_val;

  /* Set scheme 0 */
  BPL_SPI_SCHEME(0);
  /* Check connection */
  hw_rev_val = spi_get_ref_reg(slot_nr);
  if( (hw_rev_val&HW_VERS_WDB_COMMON_MASK) == HW_VERS_WDB_COMMON_VAL)
  { /* WDB */
    *board_type_id = BRD_TYPE_ID_WDB;
    *board_rev_id  = (hw_rev_val&HW_VERS_REV_MASK)>>HW_VERS_REV_OFFS;
    return 1;
  }
  //else
  //{
  //  printf("Scheme 0 unrecognized HW revision      : 0x%08X\n", hw_rev_val);
  //}
  /* TBD: remove else cases and replace constants by defines */
  hw_rev_val = spi_get_ref_reg_tcb(slot_nr);
  if( ((hw_rev_val&0xFF000000) == 0x01000000) ||
      ((hw_rev_val&0xFF000000) == 0x02000000) ||
      ((hw_rev_val&0xFF000000) == 0x03000000) )
  { /* TCB */
    *board_type_id = BRD_TYPE_ID_TCB;
    *board_rev_id  = (hw_rev_val&0xFF000000)>>24;
    return 1;
  }
  //else
  //{
  //  printf("Scheme 0 unrecognized HW revision (tcb): 0x%08X\n", hw_rev_val);
  //}

  /* Set scheme 1 */
  BPL_SPI_SCHEME(1);
  /* Check connection */
  hw_rev_val = spi_get_ref_reg(slot_nr);
  if( (hw_rev_val&HW_VERS_WDB_COMMON_MASK) == HW_VERS_WDB_COMMON_VAL)
  {
    *board_type_id = BRD_TYPE_ID_WDB;
    *board_rev_id  = (hw_rev_val&HW_VERS_REV_MASK)>>HW_VERS_REV_OFFS;
    return 1;
  }

  if(DBG_WARN) xfs_printf("Warning: board identification failed for slot %d\r\n", slot_nr);
  *board_type_id = -1; // indicate no board
  *board_rev_id = -1;
  return 0;
}

/******************************************************************************/
/******************************************************************************/

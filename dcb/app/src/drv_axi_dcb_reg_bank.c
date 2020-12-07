/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  MEG - DCB
 *
 *  Author  :  schmid_e
 *  Created :  14.12.2018 16:41:35
 *
 *  Description :  DCB Register Bank high level driver.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

/***************************** Include Files *******************************/

#include "drv_axi_dcb_reg_bank.h"
#include "system.h"
#include "wdaq_board_id.h"
#include "xfs_printf.h"
#include "dbg.h"
#include "utilities.h"
#include "crc32.h"
#include "drv_qspi_flash.h"
#include "flash_memory_maps.h"
#ifndef LINUX_COMPILE
#include "axi_dcb_register_bank.h"
#include "dcb_flash_memory_map.h"
#include "fw_env.h"
#endif /* not LINUX_COMPILE */

#undef DCB_DONT_INCLUDE_REG_ACCESS_VARS
#undef DCB_DONT_INCLUDE_VARS
#include "register_map_dcb.h"

#ifndef DCB_DONT_IMPLEMENT_SW_REGISTERS

#include "drv_dma_pkt_sched.h"

#endif /* DCB_DONT_IMPLEMENT_SW_REGISTERS */

/************************** Function Definitions ***************************/

#ifndef LINUX_COMPILE
void reg_bank_init(unsigned int base_address)
{
  SYSPTR(reg_bank)->base_address = base_address;
}
#else /* No LINUX_COMPILE */
void reg_bank_init(unsigned int base_address)
{
  SYSPTR(reg_bank)->base_address = (unsigned int)(io_remap(base_address));
}
#endif

/***************************************************************************/

#ifdef DCB_DONT_IMPLEMENT_SW_REGISTERS

unsigned int reg_read(unsigned int offs)
{
  unsigned int val;

  val = dcb_hw_reg(DCB_REG_READ, 0, offs, 0);

  if (DBG_ALL) xfs_printf("simple reg_read:  reg[0x%04X] => 0x%08X (%d)\r\n", offs,val,val);
  return val;
}

#else

unsigned int reg_read(unsigned int offs)
{
  unsigned int val;
  unsigned int i_reg;

  i_reg = (offs/4) % NR_OF_REGS;
  val = dcb_reg_func_list[i_reg].func(DCB_REG_READ, dcb_reg_func_list[i_reg].par, offs, 0);

  if (DBG_ALL) xfs_printf("reg_read:  reg[0x%04X] => 0x%08X (%d)\r\n", offs,val,val);
  return val;
}

#endif

/***************************************************************************/

#ifdef DCB_DONT_IMPLEMENT_SW_REGISTERS

void reg_write(unsigned int offs, unsigned int data)
{
  dcb_hw_reg(DCB_REG_WRITE, 0, offs, data);

  if (DBG_ALL) xfs_printf("simple reg_write: reg[0x%04X] <= 0x%08x (%d)\r\n", offs,data,data);
}

#else

void reg_write(unsigned int offs, unsigned int data)
{
  unsigned int i_reg;

  i_reg = (offs/4) % NR_OF_REGS;
  dcb_reg_func_list[i_reg].func(DCB_REG_WRITE, dcb_reg_func_list[i_reg].par, offs, data);

  if (DBG_ALL) xfs_printf("reg_write: reg[0x%04X] <= 0x%08x (%d)\r\n", offs,data,data);
}

#endif

/***************************************************************************/

void reg_bank_write(unsigned int offset, unsigned int *buffer_ptr, unsigned int no_words)
{
  unsigned int i;

  for(i=0;i<no_words;i++)
  {
    reg_write(offset+(i*4), buffer_ptr[i]);
  }
}

/***************************************************************************/

void reg_bank_restore(unsigned int offset, unsigned int *buffer_ptr, unsigned int no_words)
{
  unsigned int i;

  for(i=0;i<no_words;i++)
  {
    /* Only write register if it is marked to be restored in the register map */
    if(reg_restore[i]) reg_write(offset+(i*4), buffer_ptr[i]);
  }
}

/***************************************************************************/

void reg_bank_mask_write(unsigned int offset, unsigned int *buffer_ptr, unsigned int *mask_ptr, unsigned int no_words)
{
  unsigned int i;
  int reg_content;

  for(i=0;i<no_words;i++)
  {
    /* read */
    reg_content = reg_read(offset+(i*4));
    /* modify */
    reg_content = (reg_content & ~mask_ptr[i]) | (buffer_ptr[i] & mask_ptr[i]);
    /* write */
    reg_write(offset+(i*4), reg_content);
  }
}

/***************************************************************************/

void reg_bank_set(unsigned int offset, unsigned int *buffer_ptr, unsigned int no_words)
{
  unsigned int i;
  int reg_content;

  for(i=0;i<no_words;i++)
  {
    /* read */
    reg_content = reg_read(offset+(i*4));
    /* modify */
    reg_content = reg_content | buffer_ptr[i];
    /* write */
    reg_write(offset+(i*4), reg_content);
  }
}

/***************************************************************************/

void reg_bank_clr(unsigned int offset, unsigned int *buffer_ptr, unsigned int no_words)
{
  unsigned int i;
  int reg_content;

  for(i=0;i<no_words;i++)
  {
    /* read */
    reg_content = reg_read(offset+(i*4));
    /* modify */
    reg_content = reg_content & ~buffer_ptr[i];
    /* write */
    reg_write(offset+(i*4), reg_content);
  }
}

/***************************************************************************/

void reg_bank_read(unsigned int offset, unsigned int *buffer_ptr, unsigned int no_words)
{
  unsigned int i;

  for(i=0;i<no_words;i++)
  {
    buffer_ptr[i] = reg_read(offset+(i*4));
  }
}

/***************************************************************************/

unsigned int reg_bank_get(unsigned int offset)
{
  return reg_read(offset);
}

/***************************************************************************/

void reg_bank_load()
{
  unsigned int reg_buffer[NR_OF_REGS];
  unsigned int checksum;
  int sn;
  char *cp;
#ifdef LINUX_COMPILE
  qspi_flash_partition flash_partition;
  flash_partition_type *mtd_ptr;

  /* read register contents from SPI flash */
  if( !(mtd_ptr = get_flash_partition(get_flash_mem_map(BRD_TYPE_ID_DCB, DCB_BRD_REV_ID_B), "qspi-regcontent")) )
  {
    if(DBG_ERR) xfs_printf("Error: flash partitions for register content not found");
    return;
  }
  if( !(qspi_flash_init(&flash_partition, mtd_ptr->mtd_partition)) )
  {
    if(DBG_ERR) printf("Error: register value flash partition accesse failed\n");
    return;
  }
  qspi_flash_read(&flash_partition, 0, sizeof(reg_buffer), (unsigned char*)reg_buffer);
#else
  qspi_flash_read(SYSPTR(spi_flash), QSPI_FLASH_REG_CONTENTS_ADDR, NR_OF_REGS*4, QSFL_QUAD_READ_CMD, (unsigned char*)(reg_buffer));
#endif

  /* verify crc32 checksum */
  checksum = crc32 (0, (unsigned char*)(reg_buffer), (NR_OF_REGS-1)*4);

  /* if checksum us ok, copy contents into register bank else issue warning */
  if(checksum == reg_buffer[NR_OF_REGS-1])
  {
    /* memcpy((unsigned char*)(SYSPTR(reg_bank)->control_reg_base_address), reg_buffer_cptr, NR_OF_REGS*4); */
    reg_bank_restore(0, reg_buffer, NR_OF_REGS);
  }
  else
  {
    if(DBG_WARN)
    {
      xfs_printf("Warning: CRC checksum of register bank invalid.\r\n");
      xfs_printf("         Calculated: 0x%08X\r\n", checksum);
      xfs_printf("         From flash: 0x%08X\r\n", reg_buffer[NR_OF_REGS-1]);
    }

    sn = get_serial_number();
    if(sn)
    {
      if(DBG_WARN)
      {
        xfs_printf("         Valid serial number found.\r\n");
        xfs_printf("         Board is being re-initialized with \"init %d\".\r\n\r\n", sn);
      }
      init_settings(sn);
    }
    else
    {
      if(DBG_WARN)
      {
        xfs_printf("         No valid serial number found.\r\n");
        xfs_printf("         Register contents are not updated.\r\n\r\n");
      }
    }
  }
}

/***************************************************************************/
#ifndef DCB_DONT_IMPLEMENT_REGISTER_STORE

void reg_bank_store()
{
  unsigned int reg_buffer[NR_OF_REGS];
  unsigned int checksum;
#ifdef LINUX_COMPILE
  qspi_flash_partition flash_partition;
  flash_partition_type *mtd_ptr;
#endif

  reg_bank_read(0, reg_buffer, NR_OF_REGS);

  /* calculate and store crc32 checksum */
  checksum = crc32 (0, (unsigned char*)(reg_buffer), (NR_OF_REGS-1)*4);
  if(DBG_INFO) xfs_printf("\r\nRegister CRC = 0x%08X\r\n", checksum);
  reg_bank_write(DCB_REG_CRC32_REG_BANK, &checksum, 1);
  reg_buffer[NR_OF_REGS-1] = checksum;

#ifdef LINUX_COMPILE
  if( !(mtd_ptr = get_flash_partition(get_flash_mem_map(BRD_TYPE_ID_DCB, DCB_BRD_REV_ID_B), "qspi-regcontent")) )
  {
    if(DBG_ERR) xfs_printf("Error: flash partitions for register content not found");
    return;
  }
  if( !(qspi_flash_init(&flash_partition, mtd_ptr->mtd_partition)) )
  {
    if(DBG_ERR) printf("Error: register value flash partition accesse failed\n");
    return;
  }
  qspi_flash_erase_partition(&flash_partition);
  qspi_flash_write(&flash_partition, 0, sizeof(reg_buffer), (unsigned char*)reg_buffer);
#else
  /* erase SPI flash sector */
  qspi_flash_parameter_erase(SYSPTR(spi_flash), QSPI_FLASH_REG_CONTENTS_ADDR);
  /* store register bank contents */
  qspi_flash_write(SYSPTR(spi_flash), QSPI_FLASH_REG_CONTENTS_ADDR, NR_OF_REGS*4, QSFL_QUAD_WRITE_CMD, (unsigned char*)(reg_buffer));
#endif
}

#endif /* DCB_DONT_IMPLEMENT_REGISTER_STORE */

/***************************************************************************/
/* register handler functions                                              */
/***************************************************************************/

#ifndef LINUX_COMPILE
unsigned int dcb_hw_reg(unsigned int cmd, unsigned int par, unsigned int offs, unsigned int data)
{
  unsigned int base_address;

  base_address = SYSPTR(reg_bank)->base_address;

  if ( cmd == DCB_REG_WRITE )
  {
    AXI_DCB_REGISTER_BANK_mWriteReg(base_address, offs, data);
  }
  else if ( cmd == DCB_REG_READ )
  {
    return AXI_DCB_REGISTER_BANK_mReadReg(base_address, offs);
  }

  return 0;
}
#else /* No LINUX_COMPILE */
unsigned int dcb_hw_reg(unsigned int cmd, unsigned int par, unsigned int offs, unsigned int data)
{
  unsigned int base_address;

#ifdef LINUX_COMPILE
  init_reg_bank();
#endif
  base_address = SYSPTR(reg_bank)->base_address;

  if ( cmd == DCB_REG_WRITE )
  {
    xfs_out32(base_address+offs, data);
  }
  else if ( cmd == DCB_REG_READ )
  {
    return xfs_in32(base_address+offs);
  }

  return 0;
}
#endif

/***************************************************************************/

/* Only use special functions if function list in register map is active */
#ifndef DCB_DONT_IMPLEMENT_SW_REGISTERS

/***************************************************************************/

unsigned int dcb_sw_slot_en_reg(unsigned int cmd, unsigned int par, unsigned int offs, unsigned int data)
{
  unsigned int rd_data;

  rd_data = 0;

  if (cmd == DCB_REG_WRITE)
  {
    dps_set_slot_enable(SYSPTR(dma_pkt_sched), data & DCB_DPS_SLOT_ENABLE_MASK);
    if (data & DCB_DPS_EVENT_MODE_MASK)
    {
      dps_set_event_mode(SYSPTR(dma_pkt_sched), 1);
    }
    else
    {
      dps_set_event_mode(SYSPTR(dma_pkt_sched), 0);
    }
  }
  else if (cmd == DCB_REG_READ)
  {
    rd_data  = (dps_get_slot_enable(SYSPTR(dma_pkt_sched)) << DCB_DPS_SLOT_ENABLE_OFS);
    rd_data |= (dps_get_event_mode(SYSPTR(dma_pkt_sched))  << DCB_DPS_EVENT_MODE_OFS);
  }

  return rd_data;
}

#endif /* DCB_DONT_IMPLEMENT_SW_REGISTERS */

/***************************************************************************/

/***************************************************************************/
/***************************************************************************/

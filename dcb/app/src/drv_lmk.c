/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WDAQ - DCB
 *
 *  Author  :  schmid_e
 *  Created :  20.11.2018 11:27:35
 *
 *  Description :  SPI driver for LMK03000.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#include "system.h"
#include "drv_lmk.h"
#include "drv_axi_dcb_reg_bank.h"
#include "register_map_dcb.h"
#include "xfs_printf.h"
#include "dbg.h"

/******************************************************************************/
/******************************************************************************/

void lmk03000_send(lmk_ctrl_type *self, unsigned int tx_data)
{
  unsigned char tx_buffer[4];

#ifdef LINUX_COMPILE
  init_reg_bank();
  init_lmk03000();
#endif

  for(int i=3;i>=0;i--)
  {
    tx_buffer[i] = (unsigned char)tx_data;
    tx_data = tx_data >> 8;
  }

  spi_if_transfer((spi_if_type*)self, tx_buffer, NULL, 4);
}

/******************************************************************************/

#ifdef LINUX_COMPILE
void lmk03000_init(lmk_ctrl_type *self, unsigned char device_nr, unsigned char slave_nr)
{
  spi_if_init((spi_if_type*)self, device_nr, slave_nr, 0, 8, 1000000, 0);

  lmk03000_send(self, DCB_LMK0_RESET_MASK);

  lmk03000_upload_configuration(self);

  /* for(unsigned int i=0;i<14;i++)
   * {
   *   lmk03000_send(self, reg_default[(DCB_REG_LMK_0)/4 + i]);
   * }
   */
}
#else /* LINUX_COMPILE */
void lmk03000_init(lmk_ctrl_type *self, XSpiPs *spi_if_ptr_init, unsigned char slave_nr_init)
{
  self->spi_if_ptr = spi_if_ptr_init;
  self->slave_nr   = slave_nr_init;

  lmk03000_send(self, DCB_LMK0_RESET_MASK);

  lmk03000_upload_configuration(self);

  /* for(unsigned int i=0;i<14;i++)
   * {
   *   lmk03000_send(self, reg_default[(DCB_REG_LMK_0)/4 + i]);
   * }
   */
}
#endif /* LINUX_COMPILE */

/******************************************************************************/

int lmk03000_set_channel(lmk_ctrl_type *self, unsigned int value)
{
  if( (value & 0x0F) > 7) return -1; /* there are only channels 0..7 */

  lmk03000_send(self, value);

  return 0;
}

/******************************************************************************/
void lmk03000_upload_configuration(lmk_ctrl_type *self)
{
  /* If register entries are valid set all LMK device registers to the corresponding values */
  /* if register entries are invalid set all LMK device registers to the default values */
  unsigned int lmk_reg_addr[14] = {0,1,2,3,4,5,6,7,8,9,11,13,14,15}; /* Registers 10 and 12 do are not writable on LMK */
  unsigned int reg_value;
  /*unsigned int mod_flag_mask;*/
  /*unsigned int mod_flag_offset;*/
  unsigned char valid = 1;

  /* check if all register bank contents can be assumed to be valid */
  for(unsigned int i=0;i<14;i++)
  {
    reg_value = reg_bank_get(DCB_REG_LMK_0+(i*4));
    if( lmk_reg_addr[i] != (reg_value&0x0F) )
    {
      if(DBG_INFO) xfs_local_printf("\r\n"
                                    "Error: Invalid LMK setting [0x%04X]: 0x%08X in register bank\r\n"
                                    "Setting default LMK Configuration...\r\n"
                                    "\r\n", DCB_REG_LMK_0+(i*4), reg_value);
      valid = 0;
      break;
    }
  }

  /* if all register bank are assumed invalid: set them to the default values */
  if(!valid)
  {
    for(unsigned int i=0;i<14;i++)
    {
      reg_value = reg_default[(DCB_REG_LMK_0)/4 + i];
      reg_bank_write(DCB_REG_LMK_0+(i*4), &reg_value, 1);
    }
  }

  /* reset register configuration */
  reg_value = DCB_LMK0_RESET_MASK;
  lmk03000_send(self, reg_value);

  /* configure the LMK */
/*  mod_flag_mask = DCB_LMK_0_MOD_MASK;
 *  mod_flag_offset = DCB_REG_LMK_0_7_MOD_FLAG;
 */
  for(unsigned int i=0;i<14;i++)
  {
/*    reg_bank_write(mod_flag_offset, &mod_flag_mask, 1);*/ /* clears modified flag !!! */
    reg_value = reg_bank_get(DCB_REG_LMK_0+(i*4));

    lmk03000_send(self, reg_value);

/*     if(i==7)
 *     {
 *       mod_flag_mask = DCB_LMK_8_MOD_MASK;
 *       mod_flag_offset = DCB_REG_LMK_8_15_MOD_FLAG;
 *     }
 *     else
 *     {
 *       mod_flag_mask >>= 4;
 *     }
 */
  }
}

/******************************************************************************/

void lmk03000_reset(lmk_ctrl_type *self)
{
  unsigned int tx_val = DCB_LMK0_RESET_MASK;

  /* reset register configuration */
  lmk03000_send(self, tx_val);
}

/******************************************************************************/

/* void lmk03000_sync(lmk_ctrl_type *self)
 * {
 *   unsigned int data;
 *
 *   data = DCB_LMK_SYNC_LOCAL_MASK;
 *   reg_bank_set(DCB_LMK_SYNC_LOCAL_REG, &data, 1);
 *   usleep(100);
 *   reg_bank_clr(DCB_LMK_SYNC_LOCAL_REG, &data, 1);
 * }
 */
/******************************************************************************/

/* int lmk03000_get_ld(lmk_ctrl_type *self)
 * {
 *   if( reg_bank_get(DCB_REG_STATUS) & DCB_LMK_PLL_LOCK_MASK ) return 1;
 *   else                                                       return 0;
 * }
 */
/******************************************************************************/
/******************************************************************************/

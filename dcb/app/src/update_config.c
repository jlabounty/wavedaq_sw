/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WaveDream2
 *
 *  Author  :  schmid_e
 *  Created :  19.09.2014 13:45:08
 *
 *  Description :  Updating external devices via serial protocols if corresponding
 *                 register bank settings have changed.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

/***************************** Include Files *******************************/

#include "update_config.h"
#include "system.h"
#include "xfs_printf.h"
#include "dbg.h"
#include "register_map_dcb.h"
#include "drv_lmk.h"

/************************** Variable Definitions ***************************/

unsigned int ones = 0xFFFFFFFF;
unsigned int zero = 0;

/************************** Function Definitions ***************************/

int auto_update_configurations()
{
  unsigned int modified;

  /* Check for modifications in LMK configuration registers and update configuration if necessary*/
  modified = reg_bank_get(DCB_REG_LMK_MOD_FLAG);
  if(modified)
  {
    if(DBG_SPAM) xfs_local_printf("Auto-Update Configuration Value LMK Channel:  0x%08X\r\n", modified);
    update_lmk_ch(modified);
  }

  return 1;
}

/******************************************************************************/

int trigger_update_configurations()
{
  unsigned int apply_settings;

  apply_settings = reg_bank_get(DCB_REG_APLY_CFG);
  reg_bank_write(DCB_REG_APLY_CFG, &zero, 1); /* Clear apply settings register !!! */

  if(!apply_settings) return 0;

  /* Check for trigger of LMK configuration registers and configure if necessary*/
  if(apply_settings & DCB_APPLY_SETTINGS_LMK_MASK)
  {
    if(DBG_INFO) xfs_local_printf("Triggered Update Configuration LMK\r\n");
    update_lmk();
  }

  return 1;
}

/******************************************************************************/

int update_lmk_ch(unsigned int mod_reg)
{
  unsigned int mask;
  unsigned int value;
  
  if(DBG_INFO) xfs_local_printf("Updating LMK channel configuration\r\n\r\n");

  mask = DCB_LMK_0_MOD_MASK;
  for(int i=0;i<8;i++)
  {
    if( mod_reg & mask )
    {
      value = 0;
      reg_bank_write(DCB_REG_LMK_MOD_FLAG, &value, 1); /* Clear modified flags !!! */
      value = reg_bank_get(DCB_REG_LMK_0+(i*4));
      /* validate register content by channel number */
      if( (value & 0x0F) == i)
      {
        lmk03000_set_channel(SYSPTR(lmk), value);
      }
      else
      {
        return -1;
      }
    }
    mask <<= 1;
  }

  return 1;
}

/******************************************************************************/

int update_lmk()
{
  if(DBG_INFO) xfs_local_printf("Updating LMK configuration\r\n\r\n");

  lmk03000_upload_configuration(SYSPTR(lmk));

  return 1;
}

/***************************************************************************/
/***************************************************************************/

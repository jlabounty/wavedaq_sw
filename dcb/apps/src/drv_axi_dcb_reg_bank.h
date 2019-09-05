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

#ifndef __DRV_AXI_DCB_REG_BANK_H__
#define __DRV_AXI_DCB_REG_BANK_H__

/***************************** Include Files *******************************/

#include "utilities.h"

/************************** Constant Definitions ***************************/

#define DCB_REG_READ     0x01
#define DCB_REG_WRITE    0x02

/**************************** Type Definitions *****************************/

typedef struct {
  unsigned int  base_address;
} axi_dcb_register_bank;

/************************** Function Prototypes ****************************/

void reg_bank_init(unsigned int base_address);
void reg_bank_write(unsigned int offset, unsigned int *buffer_ptr, unsigned int no_words);
void reg_bank_mask_write(unsigned int offset, unsigned int *buffer_ptr, unsigned int *mask_ptr, unsigned int no_words);
void reg_bank_set(unsigned int offset, unsigned int *buffer_ptr, unsigned int no_words);
void reg_bank_clr(unsigned int offset, unsigned int *buffer_ptr, unsigned int no_words);
void reg_bank_read(unsigned int offset, unsigned int *buffer_ptr, unsigned int no_words);
unsigned int reg_bank_get(unsigned int offset);

#ifndef LINUX_COMPILE
void reg_bank_load();

#ifndef DCB_DONT_IMPLEMENT_REGISTER_STORE
void reg_bank_store();
#endif /* DCB_DONT_IMPLEMENT_REGISTER_STORE */

#endif /* No LINUX_COMPILE */

/***************************************************************************/

unsigned int dcb_hw_reg(unsigned int cmd, unsigned int par, unsigned int offs, unsigned int data);

#ifndef DCB_DONT_IMPLEMENT_SW_REGISTERS
/*
 * See wd2 implementations as template for software registers
 */
/*
 * unsigned int dcb_reg_adc_glob(unsigned int cmd, unsigned int par, unsigned int offs, unsigned int data);
 * unsigned int dcb_reg_adc0_ch(unsigned int cmd, unsigned int par, unsigned int offs, unsigned int data);
 * unsigned int dcb_reg_adc1_ch(unsigned int cmd, unsigned int par, unsigned int offs, unsigned int data);
 */
#endif /* DCB_DONT_IMPLEMENT_SW_REGISTERS */

#endif /** __DRV_AXI_DCB_REG_BANK_H__ */

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

#ifndef __DRV_LMK_H__
#define __DRV_LMK_H__


#ifndef LINUX_COMPILE
#include "xspips.h"
#endif /* LINUX_COMPILE */
#include "drv_spi_ps.h"

typedef spi_ps_type lmk_ctrl_type;

#ifdef LINUX_COMPILE
void lmk03000_init(lmk_ctrl_type *self, unsigned char device_nr, unsigned char slave_nr);
#else /* LINUX_COMPILE */
void lmk03000_init(lmk_ctrl_type *self, XSpiPs *spi_if_ptr_init, unsigned char slave_nr_init);
#endif /* LINUX_COMPILE */
void lmk03000_reset(lmk_ctrl_type *self);
int  lmk03000_set_channel(lmk_ctrl_type *self, unsigned int value);
void lmk03000_upload_configuration(lmk_ctrl_type *self);
/* void lmk03000_sync(lmk_ctrl_type *self);
 * int  lmk03000_get_ld(lmk_ctrl_type *self);
 */

#endif /* __DRV_LMK_H__ */

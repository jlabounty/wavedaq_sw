/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WDAQ - DCB
 *
 *  Author  :  schmid_e
 *  Created :  22.11.2018 08:23:32
 *
 *  Description :  SPI driver for SI5324.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#ifndef __DRV_SI5324_H__
#define __DRV_SI5324_H__

#ifndef LINUX_COMPILE
#include "xspips.h"
#endif
#include "drv_spi_ps.h"

typedef spi_ps_type si5324_ctrl_type;

typedef struct
{
	unsigned char address;	/* Register address */
	unsigned char data;		  /* Register value */
} si5324_reg_type;

#ifdef LINUX_COMPILE
void si5324_init(si5324_ctrl_type *self, unsigned char device_nr, unsigned char slave_nr);
#else /* LINUX_COMPILE */
void si5324_init(si5324_ctrl_type *self, XSpiPs *spi_if_ptr_init, unsigned char slave_nr_init);
#endif /* LINUX_COMPILE */
void si5324_write(si5324_ctrl_type *self, unsigned char addr, unsigned char tx_data);
unsigned char si5324_read(si5324_ctrl_type *self, unsigned char addr);
void si5324_cal(si5324_ctrl_type *self);
void si5324_reset(si5324_ctrl_type *self);

#endif /* __DRV_SI5324_H__ */

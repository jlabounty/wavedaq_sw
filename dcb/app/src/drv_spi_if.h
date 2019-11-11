/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WDAQ - DCB
 *
 *  Author  :  schmid_e
 *  Created :  09.09.2019 14:32:48
 *
 *  Description :  SPI driver for SPIDEV.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#ifndef __DRV_SPI_IF_H__
#define __DRV_SPI_IF_H__

#ifdef LINUX_COMPILE

#include <linux/spi/spidev.h>

typedef struct
{
  unsigned char device_nr;
  unsigned char slave_nr;
  struct spi_ioc_transfer xfer;
} spi_if_type;

#else /* LINUX_COMPILE */

#include "xspips.h"

typedef struct
{
  XSpiPs        *spi_if_ptr;
  unsigned char slave_nr;
} spi_if_type;

#endif /* LINUX_COMPILE */

#ifdef LINUX_COMPILE
int spi_if_init(spi_if_type* self, unsigned char device_nr, unsigned char slave_nr, unsigned char lsb, unsigned char bits, unsigned int speed, unsigned char mode);
#endif /* LINUX_COMPILE */
char* spi_if_transfer(spi_if_type* self, char* tx_buf, char* rx_buf, unsigned int len);

#endif /* __DRV_SPI_IF_H__ */

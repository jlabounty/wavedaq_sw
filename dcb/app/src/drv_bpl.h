/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WDAQ - DCB
 *
 *  Author  :  schmid_e
 *  Created :  09.05.2019 12:43:51
 *
 *  Description :  SPI functions for communication DCB<->Slots.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#ifndef __DRV_BPL__
#define __DRV_BPL__

#include "drv_spi_if.h"

typedef struct
{
  spi_if_type slot_fpga;
} bpl_spi_type;

void bpl_spi_init(bpl_spi_type *self, unsigned char device_nr);
void spi_ascii_cmd(char* buff, unsigned char slot_nr);
void spi_binary_cmd(char* tx_buff, char* rx_buff, unsigned char slot_nr, unsigned int len);
void spi_flash_id_cmd(unsigned char slot_nr);

#endif /* __DRV_BPL__ */

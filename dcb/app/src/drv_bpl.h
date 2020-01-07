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
  //spi_if_type slot_wdb_flash;
  //spi_if_type slot_tcb_flash;
} bpl_spi_type;

typedef struct
{
  unsigned char op_en[18];
} slot_op_en_type;

void bpl_spi_init(bpl_spi_type *self, unsigned char device_nr);
void spi_ascii_cmd(char* txbuff, char *rxbuf, unsigned int rxsize, unsigned char slot_nr);
void spi_binary_cmd(char* tx_buff, char* rx_buff, unsigned char slot_nr, unsigned int len);
void bpl_upload_fw_sw(slot_op_en_type *slot, int load_fw, char *fw_spec_p, int load_sw, char *sw_spec_p, char *board_type, char *board_rev);
void spi_flash_id_cmd(unsigned char slot_nr);

#endif /* __DRV_BPL__ */

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
void spi_ascii_cmd(char* txbuff, char *rxbuf, unsigned int rxsize, unsigned char slot_nr, unsigned int board_type, unsigned int board_revision);
void spi_binary_cmd(char* tx_buff, char* rx_buff, unsigned int len, unsigned char slot_nr, unsigned int board_type, unsigned int board_revision);
void slot_upload_fw_sw(unsigned int slot_nr, int load_fw, char *fw_spec_p, int load_sw, char *sw_spec_p, unsigned int board_type, unsigned int board_rev);
void crate_upload_fw_sw(slot_op_en_type *slot, int load_fw, char *fw_spec_p, int load_sw, char *sw_spec_p, unsigned int board_type, unsigned int board_rev, unsigned int force);
void spi_flash_id_cmd(unsigned char slot_nr);
int get_slot_board_info(unsigned int slot_nr, unsigned int *board_vendor_id, unsigned int *board_type_id, unsigned int *board_revision_id, unsigned int *board_variant_id);

#endif /* __DRV_BPL__ */

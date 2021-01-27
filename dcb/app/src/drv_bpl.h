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

#include "wdaq_board_id.h"
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
void init_slot(unsigned int slot_nr, unsigned int len_us);
void spi_ascii_cmd(char* txbuff, char *rxbuf, unsigned int rxsize, unsigned char slot_nr, unsigned int board_type, unsigned int board_revision);
void spi_binary_cmd(char* tx_buff, char* rx_buff, unsigned int len, unsigned char slot_nr, unsigned int board_type, unsigned int board_revision);
void slot_upload_fw_sw(unsigned int slot_nr, int load_fw, char *fw_spec_p, int load_sw, char *sw_spec_p, unsigned int board_type, unsigned int board_rev);
void crate_upload_fw_sw(slot_op_en_type *slot, int load_fw, char *fw_spec_p, int load_sw, char *sw_spec_p, unsigned int board_type, unsigned int board_rev, unsigned int force);
int is_flash_available(unsigned char slot_nr);
int get_slot_board_info(unsigned int slot_nr, WDAQ_BRD *wdaq_board_info_ptr);
void bpl_sync();

#endif /* __DRV_BPL__ */

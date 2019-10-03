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

#ifndef __SPI_BPL__
#define __SPI_BPL__

void spi_ascii_cmd(char* buff, unsigned char slot_nr);
void spi_binary_cmd(char* tx_buff, char* rx_buff, unsigned char slot_nr, unsigned int len);
void spi_flash_id_cmd(unsigned char slot_nr);

#endif /* __SPI_BPL__ */

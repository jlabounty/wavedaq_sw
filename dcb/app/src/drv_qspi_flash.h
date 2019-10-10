/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  MEGII - DCB
 *
 *  Author  :  schmid_e (Author of generation script)
 *  Created :  13.09.2019 15:01:46
 *
 *  Description :  Linux user space QSPI Flash driver.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#ifndef __DRV_QSPI_FLASH_H__
#define __DRV_QSPI_FLASH_H__

void qspi_flash_write(const char *mtd_path, unsigned int offset, unsigned int byte_count, unsigned char *wr_buffer_ptr);
void qspi_flash_read(const char *mtd_path, unsigned int offset, unsigned int byte_count, unsigned char *rd_buffer_ptr);
void qspi_flash_erase_partition(const char *mtd_path);

#endif /* __DRV_QSPI_FLASH_H__ */

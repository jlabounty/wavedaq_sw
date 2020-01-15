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

#include <mtd/mtd-user.h>

typedef struct
{
  char* mtd_path;
  mtd_info_t mtd_info;
} qspi_flash_partition;

int qspi_flash_init(qspi_flash_partition *self, const char *mtd_path);
int qspi_flash_write(qspi_flash_partition *self, unsigned int offset, unsigned int byte_count, unsigned char *wr_buffer_ptr);
int qspi_flash_read(qspi_flash_partition *self, unsigned int offset, unsigned int byte_count, unsigned char *rd_buffer_ptr);
int qspi_flash_erase_partition(qspi_flash_partition *self);
unsigned int qspi_flash_erase_sector(qspi_flash_partition *self, unsigned int ers_start);

#endif /* __DRV_QSPI_FLASH_H__ */

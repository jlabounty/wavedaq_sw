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
#include "drv_qspi_flash.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "dbg.h"

int qspi_flash_init(qspi_flash_partition *self, const char *mtd_path)
{
  int fd;

  fd = open(mtd_path, O_RDWR);
  if(fd == -1) return 0;

  ioctl(fd, MEMGETINFO, &(self->mtd_info));
  if(DBG_SPAM) printf("MTD type: %u\n", self->mtd_info.type);
  if(DBG_SPAM) printf("MTD total size : %u bytes\n", self->mtd_info.size);
  if(DBG_SPAM) printf("MTD erase size : %u bytes\n", self->mtd_info.erasesize);
  close(fd);

  self->mtd_path = (char*)mtd_path;

  return 1;
}

int qspi_flash_write(qspi_flash_partition *self, unsigned int offset, unsigned int byte_count, unsigned char *wr_buffer_ptr)
{
  int fd;

  fd = open(self->mtd_path, O_RDWR);
  if(fd == -1) return 0;

  lseek(fd, offset, SEEK_SET);
  write(fd, wr_buffer_ptr, byte_count);
  close(fd);

  return 1;
}

int qspi_flash_read(qspi_flash_partition *self, unsigned int offset, unsigned int byte_count, unsigned char *rd_buffer_ptr)
{
  int fd;

  fd = open(self->mtd_path, O_RDONLY);
  if(fd == -1) return 0;

  lseek(fd, offset, SEEK_SET);
  read(fd, rd_buffer_ptr, byte_count);
  close(fd);

  return 1;
}

int qspi_flash_erase_partition(qspi_flash_partition *self)
{
  erase_info_t ers_info;
  int fd;

  fd = open(self->mtd_path, O_RDWR);
  if(fd == -1) return 0;

  ers_info.length = self->mtd_info.erasesize;
  for(ers_info.start = 0; ers_info.start < self->mtd_info.size; ers_info.start += self->mtd_info.erasesize)
  {
    ioctl(fd, MEMUNLOCK, &ers_info);
    ioctl(fd, MEMERASE, &ers_info);
  }

  close(fd);

  return 1;
}

unsigned int qspi_flash_erase_sector(qspi_flash_partition *self, unsigned int ers_start)
{
  erase_info_t ers_info;
  int fd;

  fd = open(self->mtd_path, O_RDWR);
  if(fd == -1) return 0;

  ers_info.start  = (ers_start/self->mtd_info.erasesize)*self->mtd_info.erasesize;
  ers_info.length = self->mtd_info.erasesize;
  ioctl(fd, MEMUNLOCK, &ers_info);
  ioctl(fd, MEMERASE, &ers_info);

  close(fd);

  return ers_info.length;
}

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
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <mtd/mtd-user.h>
#include "dbg.h"

void qspi_flash_write(const char *mtd_path, unsigned int offset, unsigned int byte_count, unsigned char *wr_buffer_ptr)
{
  mtd_info_t mtd_info;
  int fd;

  fd = open(mtd_path, O_RDWR);

  ioctl(fd, MEMGETINFO, &mtd_info);
  if(DBG_SPAM) printf("MTD type: %u\n", mtd_info.type);
  if(DBG_SPAM) printf("MTD total size : %u bytes\n", mtd_info.size);
  if(DBG_SPAM) printf("MTD erase size : %u bytes\n", mtd_info.erasesize);

  lseek(fd, offset, SEEK_SET);
  write(fd, wr_buffer_ptr, byte_count);
  close(fd);
}

void qspi_flash_read(const char *mtd_path, unsigned int offset, unsigned int byte_count, unsigned char *rd_buffer_ptr)
{
  mtd_info_t mtd_info;
  int fd;

  fd = open(mtd_path, O_RDONLY);

  ioctl(fd, MEMGETINFO, &mtd_info);
  if(DBG_SPAM) printf("MTD type: %u\n", mtd_info.type);
  if(DBG_SPAM) printf("MTD total size : %u bytes\n", mtd_info.size);
  if(DBG_SPAM) printf("MTD erase size : %u bytes\n", mtd_info.erasesize);

  lseek(fd, offset, SEEK_SET);
  read(fd, rd_buffer_ptr, byte_count);
  close(fd);
}

void qspi_flash_erase_partition(const char *mtd_path)
{
  mtd_info_t mtd_info;
  erase_info_t ers_info;
  int fd;

  fd = open(mtd_path, O_RDWR);
  ioctl(fd, MEMGETINFO, &mtd_info);

  if(DBG_SPAM) printf("MTD type: %u\n", mtd_info.type);
  if(DBG_SPAM) printf("MTD total size : %u bytes\n", mtd_info.size);
  if(DBG_SPAM) printf("MTD erase size : %u bytes\n", mtd_info.erasesize);

  ers_info.length = mtd_info.erasesize;
  for(ers_info.start = 0; ers_info.start < mtd_info.size; ers_info.start += mtd_info.erasesize)
  {
    ioctl(fd, MEMUNLOCK, &ers_info);
    ioctl(fd, MEMERASE, &ers_info);
  }

  close(fd);
}

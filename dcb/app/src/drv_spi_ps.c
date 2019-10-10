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


#include "drv_spi_ps.h"
#include "dbg.h"
#ifdef LINUX_COMPILE
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#endif /* LINUX_COMPILE */

#ifdef LINUX_COMPILE

int spi_ps_init(spi_ps_type* self, unsigned char device_nr, unsigned char slave_nr, unsigned char lsb, unsigned char bits, unsigned int speed, unsigned char mode)
{
  /* possible modes: SPI_LOOP, SPI_CPHA, SPI_CPOL, SPI_LSB_FIRST, SPI_CS_HIGH, SPI_3WIRE, SPI_NO_CS, SPI_READY */
  int file;
  char filename[40];

  /* self->xfer.tx_buf = (unsigned long)buf; */
  /* self->xfer.len = ; */ /* Length of  command to write*/
  self->xfer.cs_change = 0; /* Keep CS activated */
  self->xfer.delay_usecs = 0, /* delay in us */
  self->xfer.speed_hz = speed, /* speed */
  self->xfer.bits_per_word = bits, /* bites per word */

  sprintf(filename, "/dev/spidev%d.%d", device_nr, slave_nr);

  if ((file = open(filename,O_RDWR)) < 0)
  {
    if(DBG_ERR) printf("Failed to open the bus.");
    /* ERROR HANDLING; you can check errno to see what went wrong */
    //com_serial=0;
    exit(1);
  }

  /* Verifications */
  /*
  if (ioctl(file, SPI_IOC_WR_MODE, &mode)<0)
  {
    if(DBG_ERR) perror("can't set spi mode");
    return -1;
  }
  */
  if (ioctl(file, SPI_IOC_RD_MODE, &mode) < 0)
  {
    if(DBG_ERR) perror("SPI rd_mode");
    return -1;
  }
  if (ioctl(file, SPI_IOC_RD_LSB_FIRST, &lsb) < 0)
  {
    if(DBG_ERR) perror("SPI rd_lsb_fist");
    return -1;
  }
  /* sunxi supports only 8 bits */
  /*
  if (ioctl(file, SPI_IOC_WR_BITS_PER_WORD, (xfs_u8[1]){8})<0)
  {
    perror("can't set bits per word");
    return -1;
  }
  */
  if (ioctl(file, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0)
  {
    if(DBG_ERR) perror("SPI bits_per_word");
    return -1;
  }
  /*
  if (ioctl(file, SPI_IOC_WR_MAX_SPEED_HZ, &speed)<0)
  {
    if(DBG_ERR) perror("can't set max speed hz");
    return -1;
  }
  */
  if (ioctl(file, SPI_IOC_RD_MAX_SPEED_HZ, &speed) < 0)
  {
    if(DBG_ERR) perror("SPI max_speed_hz");
    return -1;
  }

  if(DBG_INF0) printf("%s: spi mode %d, %d bits %sper word, %d Hz max\n",filename, mode, bits, lsb ? "(lsb first) " : "", speed);

  self->device_nr = device_nr;
  self->slave_nr  = slave_nr;
  close(file);
  return file;
}

char* spi_ps_transfer(spi_ps_type* self, char* tx_buf, char* rx_buf, unsigned int len)
{
  int file;
  char filename[40];
  int status;

  sprintf(filename, "/dev/spidev%d.%d", self->device_nr, self->slave_nr);
  if ((file = open(filename,O_RDWR)) < 0)
  {
    if(DBG_ERR) printf("Failed to open the bus.");
    /* ERROR HANDLING; you can check errno to see what went wrong */
    //com_serial=0;
    exit(1);
  }

  if(rx_buf)
  {
    memset(rx_buf, 0, len);
    self->xfer.rx_buf = (unsigned long)rx_buf;
  }

  self->xfer.tx_buf = (unsigned long)tx_buf;
  self->xfer.len = len; /* Length of Data to read */

//  printf("doing transfer\r\n");
  status = ioctl(file, SPI_IOC_MESSAGE(1), &(self->xfer));
  if (status < 0)
  {
    if(DBG_ERR) perror("SPI_IOC_MESSAGE");
    return NULL;
  }
  //printf("env: %02x %02x %02x\n", buf[0], buf[1], buf[2]);
  //printf("ret: %02x %02x %02x %02x\n", buf2[0], buf2[1], buf2[2], buf2[3]);

  close(file);
  return rx_buf;
}

#else /* LINUX_COMPILE */

char* spi_ps_transfer(spi_ps_type* self, char* tx_buf, char* rx_buf, unsigned int len)
{
  XSpiPs_SetSlaveSelect(self->spi_if_ptr, self->slave_nr);
  XSpiPs_PolledTransfer(self->spi_if_ptr, tx_buf, rx_buf, len);
  return rx_buf;
}

#endif /* LINUX_COMPILE */

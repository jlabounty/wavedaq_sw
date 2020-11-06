#include "dma_packet_scheduler_v1_0.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

void usage(char *name)
{
  printf("Usage: <slot enable vector>\n", name);
}

int main(int argc, char *argv[])
{
  int ret;
  unsigned int slot_enable = 0x1FFFF;
  char opt;
  FILE *f;
  int fd;

  if (argc == 2) {
    slot_enable = 0x1FFFF & (unsigned int)strtol(argv[1], NULL, 0);
    printf("target slots: 0x%08X\n", slot_enable);
  }

  opt = argv[1][0];

  /* open device file */
  fd = open("/dev/dma_pkt_sched0", O_RDONLY);

  printf("enabling slots (0x%08X)\n", slot_enable);
  ret = ioctl(fd, DPS_IOCT_SLOT_EN, slot_enable);
  if(ret < 0)
    return ret;

  printf("enabling IP\n");
  ret = ioctl(fd, DPS_IOCT_EN, 1);
  if(ret < 0)
    return ret;

  ret = ioctl(fd, DPS_IOCQ_WINSIZE);
  if(ret < 0)
    return ret;
  printf("window size = 0x%08X (%d)\n", ret, ret);

  ret = ioctl(fd, DPS_IOCQ_NOWINDOWS);
  if(ret < 0)
    return ret;
  printf("#windows = %d\n", ret);

  return 0;
}

#include "dma_packet_scheduler_v1_0.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

void usage(char *name)
{
  printf("Usage: %s <option to call> [option argument]\n", name);
}


int main(int argc, char *argv[])
{
  int ret;
  unsigned int value;
  char opt;
  FILE *f;
  int fd;

  if (argc < 2) {
    usage(argv[0]);
    return -1;
  }

  opt = argv[1][0];

  /* open device file */
  fd = open("/dev/dma_pkt_sched0", O_RDONLY);

  if(argc == 3) value = (unsigned int)strtol(argv[2], NULL, 0);

  switch(opt)
  {
    /* enable */
    case 'e':
      ret = ioctl(fd, DMA_PSCHED_EN_IOCTL);
      if (ret < 0)
        perror("enable");
      break;
    case 'd':
      /* disable */
      ret = ioctl(fd, DMA_PSCHED_DIS_IOCTL);
      if (ret < 0) perror("disable");
      break;
    case 's':
      /* set slots */
      ret = ioctl(fd, DMA_PSCHED_EN_SLOT_IOCTL, value);
      if (ret < 0) perror("enable slot");
      break;
    default:
      perror("invalid argument");
      break;
  }

  return 0;
}

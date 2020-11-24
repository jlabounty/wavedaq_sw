#include "dma_packet_scheduler_v1_0.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

static const char udp_dst_ip_addr[16] = "129.129.193.185\0";
static unsigned int udp_dst_port = 5232;

void usage(char *name)
{
  printf("Usage: <slot enable vector>\n", name);
}

int main(int argc, char *argv[])
{
  int ret;
  int val;
  unsigned int slot_enable = 0x1FFFF;
  char opt;
  FILE *f;
  int fd;
  char buffer[32];

  if (argc == 2) {
    slot_enable = 0x1FFFF & (unsigned int)strtol(argv[1], NULL, 0);
  }

  opt = argv[1][0];

  printf("Setting IP Controls:\n\n");
  /* Configure Slot Enables */
  printf("enabling slots (0x%08X)\n", slot_enable);
  /* open device file */
  fd = open("/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_ctrl/slot_enable", O_RDWR);
  if(fd < 0)
  {
    perror("/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_ctrl/slot_enable");
    return fd;
  }
  ret = sprintf(buffer, "0x%08X\n", slot_enable);
  write(fd, buffer, ret);
  close(fd);

  /* Configure UDP Destination IP Address */
  printf("setting UDP destination ip address %s\n", udp_dst_ip_addr);
  /* open device file */
  fd = open("/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_ctrl/udp_dst_ip_addr", O_RDWR);
  if(fd < 0)
  {
    perror("/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_ctrl/udp_dst_ip_addr");
    return fd;
  }
  ret = sprintf(buffer, "%s\n", udp_dst_ip_addr);
  write(fd, buffer, ret);
  close(fd);

  /* Configure UDP Destination Port */
  printf("setting UDP destination port %d\n", udp_dst_port);
  /* open device file */
  fd = open("/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_ctrl/udp_dst_port", O_RDWR);
  if(fd < 0)
  {
    perror("/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_ctrl/udp_dst_port");
    return fd;
  }
  ret = sprintf(buffer, "%d\n", udp_dst_port);
  write(fd, buffer, ret);
  close(fd);

  /* Configure Core Enable */
  printf("enabling IP\n");
  /* open device file */
  fd = open("/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_ctrl/enable", O_RDWR);
  if(fd < 0)
  {
    perror("/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_ctrl/enable");
    return fd;
  }
  ret = sprintf(buffer, "1\n");
  write(fd, buffer, ret);
  close(fd);

  printf("\n\nReading IP Configuration:\n\n");

  printf("Device-Tree Settings:\n");
  /* open device file */
  fd = open("/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_config/slots", O_RDONLY);
  if(fd < 0)
  {
    perror("/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_config/slots");
    return fd;
  }
  ret = read(fd, buffer, sizeof(buffer));
  buffer[ret] = 0;
  printf("#slots = %s\n", buffer);
  close(fd);

  printf("Driver module parameters:\n");
  /* open device file */
  fd = open("/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_config/windows", O_RDONLY);
  if(fd < 0)
  {
    perror("/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_config/windows");
    return fd;
  }
  ret = read(fd, buffer, sizeof(buffer));
  buffer[ret] = 0;
  val = strtol(buffer, NULL, 0);
  printf("#windows = 0x%08X (%d)\n", val, val);
  close(fd);
  /* open device file */
  fd = open("/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_config/win_size", O_RDONLY);
  if(fd < 0)
  {
    perror("/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_config/win_size");
    return fd;
  }
  ret = read(fd, buffer, sizeof(buffer));
  buffer[ret] = 0;
  val = strtol(buffer, NULL, 0);
  printf("window size = 0x%08X (%d)\n", val, val);
  close(fd);

#if 0
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

  close(fd);
#endif

  return 0;
}

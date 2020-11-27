#include <stdio.h>
#include <stdlib.h>
#include "../../../app/src/drv_dma_pkt_sched.h"

//static const char udp_dst_ip_addr[16] = "129.129.193.185\0";
static const char udp_dst_ip_addr[4] = {129,129,193,185};
static unsigned int udp_dst_port = 5232;

void usage(char *name)
{
  printf("Usage: <slot enable vector>\n", name);
}

int main(int argc, char *argv[])
{
  int ret;
  int val;
  struct udev *udev;
  struct udev_device *dev;
  unsigned int slot_enable = 0x1FFFF;
  char opt;
  char buffer[32];
  dps_dev_t dps_dev;

  if (argc == 2) {
    slot_enable = 0x1FFFF & (unsigned int)strtol(argv[1], NULL, 0);
  }

  opt = argv[1][0];

  dps_dev_init(&dps_dev, "/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi");

  printf("IP Controls:\n\n");

  dps_set_slot_enable (&dps_dev, slot_enable);
  printf("enabled slots 0x%08X\n", dps_get_slot_enable(&dps_dev));

  dps_set_udp_dst_ip_addr(&dps_dev, udp_dst_ip_addr);
  printf("UDP destination ip address %s\n", dps_get_udp_dst_ip_addr(&dps_dev));

  dps_set_udp_dst_port(&dps_dev, udp_dst_port);
  printf("UDP destination port %d\n", dps_get_udp_dst_port(&dps_dev));

  dps_set_event_mode(&dps_dev, DPS_EVENT_MODE_FREERUN); /* DPS_EVENT_MODE_COMMON, DPS_EVENT_MODE_FREERUN */
  printf("event mode %d\n", dps_get_event_mode(&dps_dev));

  printf("enabling IP... ");
  dps_enable(&dps_dev);
  if (dps_is_enabled(&dps_dev))
  {
    printf("enabled\n");
  }
  else
  {
    printf("still disabled\n");
  }

  printf("\n\nIP Configuration:\n\n");

  printf("Device-Tree Settings:\n");
  printf("#slots: %d\n", dps_get_slots(&dps_dev));

  printf("Driver module parameters:\n");

  val = dps_get_windows(&dps_dev);
  printf("#windows = 0x%08X (%d)\n", val, val);

  val = dps_get_win_size(&dps_dev);
  printf("window size = 0x%08X (%d)\n", val, val);

  printf("\n\nResetting IP\n");
  dps_reset(&dps_dev);

  return 0;
}

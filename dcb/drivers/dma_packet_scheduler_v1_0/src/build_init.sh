#!/bin/bash
# . /opt/poky-lsb/2.7/environment-setup-cortexa9t2hf-neon-poky-linux-gnueabi
$CC $CFLAGS -o dps_init ../../../app/src/drv_dma_pkt_sched.c dps_init.c -ludev

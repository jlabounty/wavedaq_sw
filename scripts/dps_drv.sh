#! /bin/sh

### BEGIN INIT INFO
# Provides:        dma_packet_scheduler_v1_0
# Required-Start:  
# Required-Stop:   
# Default-Start:   2 3 4 5
# Default-Stop:    
# Short-Description: Load DMA packet scheduler ip driver
### END INIT INFO

# Source function library.
. /etc/init.d/functions

# Loading driver for DMA packet scheduler Vivado IP
# 
# Module parameters:
# windows    number of windows (=buffers) per crate slot
# win_size   size of a window in bytes

case "$1" in
  start)
      echo "Loading DMA packet scheduler driver"
      insmod /fw_sw/dcb/prod/dma_packet_scheduler_v1_0.ko windows=2 win_size=0x1000
      ;;
  stop)
      rmmod dma_packet_scheduler_v1_0.ko
      ;;
  restart)
      rmmod dma_packet_scheduler_v1_0.ko
      insmod /fw_sw/dcb/prod/dma_packet_scheduler_v1_0.ko windows=2 win_size=0x1000
      ;;
  *)
      exit 1
      ;;
esac

exit 0


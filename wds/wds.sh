#! /bin/sh

### BEGIN INIT INFO
# Provides:        wds
# Required-Start:  $network $remote_fs $syslog dma_packet_scheduler_v1_0 dcbs
# Required-Stop:   $network $remote_fs $syslog
# Default-Start:   2 3 4 5
# Default-Stop:
# Short-Description: Start WaveDAQ server
### END INIT INFO

# Source function library.
. /etc/init.d/functions

case "$1" in
  start)
     /fw_sw/dcb/prod/wds -p 80 -W /fw_sw/dcb/prod -D
     ;;
  stop)
     killall wds
     ;;
  restart)
     killall -w -v wds
     /fw_sw/dcb/prod/wds -p 80 -W /fw_sw/dcb/prod -D
     ;;
  *)
     echo "Usage: wds { start | stop | restart }" >&2
     exit 1
     ;;
esac

exit 0

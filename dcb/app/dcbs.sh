#! /bin/sh

### BEGIN INIT INFO
# Provides:        dcbs
# Required-Start:  $network $remote_fs $syslog
# Required-Stop:   $network $remote_fs $syslog
# Default-Start:   2 3 4 5
# Default-Stop:
# Short-Description: Start DCB UDP server
### END INIT INFO

# Source function library.
. /etc/init.d/functions

case "$1" in
  start)
     /fw_sw/dcb/prod/dcbs -D
     ;;
  stop)
     killall dcbs
     ;;
  restart)
     killall -w -v dcbs
     /fw_sw/dcb/prod/dcbs -D
     ;;
  *)
     echo "Usage: dcbs { start | stop | restart }" >&2
     exit 1
     ;;
esac

exit 0

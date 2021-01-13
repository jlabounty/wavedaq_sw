# DCB - Setting up the DMA and SERDES Cores for testing

## Author
Elmar Schmid [elmar.schmid@psi.ch]

## Description
This file describes the procedure for using the DMA-packet-scheduler and SERDES-receiver core during the commissioning of the SERDES links in a MEGII crate.

## Procedure
Before starting tests, please make sure that all prerequisites (see below) are fullfilled.

Note that register addresses and bit positions refer to the current register bank state and might change in the future.
Please refer to the corresponding register bank documentation in this folder to check for the most recent register adresses and bit positions.

There is a high level driver drv_dma_pkt_sched.c/h for the DMA core. In C or C++ code, all driver settings that are described with shell commands are covered by the high level driver functions.

1. On each WDB:
   1. Reset if necessary (WDB LED must be green or blue)
   2. WDB must run on backplane clock
      Register __CLK_CTRL__ (0x100C)
      - Bit 17 __daq_clk_src_sel__ = 0
      - Bit 16 __ext_clk_is_sel__ = 0
      - Bit 15:8 __ext_clk_freq__ = 0x50 (80)
   3. Configure for SERDES transmission:
      Register __COM_CTRL__ (0x1014)
      - Bit 25 __serdes_com_en__ = 1
      - Bit 24 __eth_com_en__ = 0
   4. Don't forget to set...
      - the proper daq mode (single, normal, auto) in register __CTRL__ (0x1004)
      - the proper trigger configuration in register __TRG_CFG__ (0x1124) ff
   5. `regstore` to save the settings for subsequent boots/resets
   6. If necessary, turn off DHCP
      `setenv ethdhcp 0`
      `saveenv` to store the setting
   7. The WDB LED should be blue
2. Configure the destination for the UDP packets.
   This can be done in two ways:
   1. Using the cfgdst command on the data receiver specifying just the port (also done by WDS)
      E.g. `cfgdst 5232` if done on the data receiver
      E.g. `cfgdst 5232 129.129.188.245` if done on on any machine on dcbs
   2. Using the Linux shell (as root)
      E.g. `echo 127.0.0.1 > /sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_ctrl/udp_dst_ip_addr`
      E.g. `echo 5232 >/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_ctrl/udp_dst_port`
3. Enable slots
   Per default, all slots are enabled and this does not have to be changed in free running mode
   If it has to be changed, it can be done from the Linux shell (as root). Note that the DMA core has to be reset after a change.
   E.g. `echo 0x1FFFF > /sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_ctrl/slot_enable`
   `echo 1 > /sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_ctrl/reset`
4. SERDES receiver control and status
   The following DCB registers control the SERDES receiver (commands for dcbs)
   1. Resets
      Register __RST__ (0x58)
      Bit 3 __iserdes_rcvr_error_count_rst__ : Resets the error counters
      Bit 2 __iserdes_receiver_resync__ : Resynchronizes all SERDES receivers
      Bit 1 __iserdes_receiver_rst__ : Fully resets all SERDES receivers
      - `rw 0x58 0x8` (on dcbs) resets the receivers
      - `rw 0x58 0x2` (on dcbs) resets the error counters
   2. Status
      `rr 0x58 20` can be done on dcbs to check all checked registers at once
      - Receiver Status
      Register __SERDES_STATUS_00_07__ (0x5C) : Status for slot 7 (Bits 30:28) down to 0 (Bits 2:0)
      Register __SERDES_STATUS_08_15__ (0x60) : Status for slot 15 (Bits 30:28) down to 8 (Bits 2:0)
      Register __SERDES_STATUS_17__ (0x64) : Status for slot 17 (Bits 2:0)
      For each set
      MSB:    __idle_pattern_detect_nn__ : An idle pattern is currently detected on slot nn
      Middle: __delay_sync_done__ : Delay sync calibration completed on slot nn
      LSB: __sync_done_nn__ : Sync calibration (delay and bitslip) completed on slot nn
      - Error Counts (0xFF (255) corresponds to a counter overflow)
      Register __SERDES_ERR_CNT_00__ (0x68) to __SERDES_ERR_CNT_17__ (0xA8) : Error counts of the corresponding slot
      Bits 31:24 __crc_errors_nn__ : CRC Errors on slot nn
      Bits 23:16 __frame_errors_nn__ : Frame Errors on slot nn (Corrupt SOF or buffer overflow)
      Bits 15:8 __datagram_errors_nn__ : Datagram Errors on slot nn (Inconsistencies with SOE, EOE and Event Number)
      Bits 7:0 __sync_errors_nn__ : Sync Errors on slot nn (No idle pattern received when link should be idle)
5. Start triggering and observe arriving packets ...

## Prerequisites
The driver for the DMA packet scheduler has to be loaded before dcbs is started.
As a preliminary solution -i.e. as long as it's not integrated in the kernel-, this can be done by calling the script https://bitbucket.org/twavedaq/wavedaq_sw/src/master/scripts/dps_drv.sh.

### To automatically load the driver
To add the script to the initialization sequence, do the following:
1. Copy the script from the repository to /etc/init.d
2. Add it to the boot sequence
   `chkconfig --add dps_drv.sh`
   `chkconfig --level 2345 dps_drv.sh on`
3. You might have to remove the dcbs and add it agait to make sure it's started after the driver is loaded
   `chkconfig --del dcbs.sh`
   `chkconfig --add dcbs.sh`
   `chkconfig --level 2345 dcbs.sh on`

### To manually load the driver
The driver can also be loaded from the shell
`insmod /fw_sw/dcb/prod/dma_packet_scheduler_v1_0.ko`
Apply a reset after loading
`echo 1 > /sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_ctrl/reset`

### To check if driver is loaded
To check if the driver is loaded from the shell, call
`lsmod`

## Additional Information
Driver parameters can be viewed here:

/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_ctrl/ :
parameters to control core operation

/sys/devices/soc0/amba_pl/43c10000.dma_pkt_sched_axi/dps_config/ :
read only configuration controlled by device tree and driver module parameter settings

The parameters next_buffer and data_bytes in the dps_ctrl subfolder were used with the original setup where the incoming data was organized in a queue. They might be used again to optimize data throuphput when WDS is running locally on the DCB. In cases where the DCB just forwards the data through UDP, these configuration files have no meaning and should not be touched.

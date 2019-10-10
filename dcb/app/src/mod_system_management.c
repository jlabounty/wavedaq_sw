/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WaveDream2
 *
 *  Author  :  schmid_e
 *  Created :  22.05.2014 13:30:33
 *
 *  Description :  Module for configuring doing system management and housekeeping.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#include "system.h"
#include "cmd_processor.h"
#include "sc_io.h"
#include "xfs_printf.h"
#include "utilities.h"
#include "dbg.h"

#ifndef LINUX_COMPILE
/*#include "udp_terminal.h"*/
/*#include "fw_env.h"*/
/*#include "register_map_wd2.h"*/
#include "sw_state.h"
#include <stdlib.h>
#include "sfp_ctrl.h"
#include "xparameters.h"
/*#include "clock_measure.h"*/
#endif /* LINUX_COMPILE */

/************************************************************/
/*
  int sm_reset(int argc, char **argv)
  {
    unsigned int data = WD2_RECONFIGURE_FPGA_MASK;

    CMD_HELP("",
             "starts an fpga reconfiguration",
             "Reconfigures the FPGA from the flash memory.\r\n"
            );

    reg_bank_set(WD2_REG_RST, &data, 1);

    return 0;
  }
*/
/************************************************************/

  int sm_mark_board(int argc, char **argv)
  {
    CMD_HELP("",
             "mark board by letting led blink magenta"
            );

    emio_set_sw_state(BIT_IDX_EMIO_CTRL_SW_STATE_MARKER_PIN);

    return 0;
  }

/************************************************************/

  int sm_unmark_board(int argc, char **argv)
  {
    CMD_HELP("",
             "remove board marking board resetting the led state"
            );

    emio_clr_sw_state(BIT_IDX_EMIO_CTRL_SW_STATE_MARKER_PIN);

    return 0;
  }

/************************************************************/

  int sm_init(int argc, char **argv)
  {
    CMD_HELP("<snr>",
             "initializes environment variables",
             "Initializes board environment variables (hostname, mac address, ...)\r\n"
             "with the serial number.\r\n"
             "  <snr> : Serial number (digits only)\r\n"
            );

    /* Check for minimum number of arguments */
    if(argc < 2)
    {
      xfs_printf("E%02X: Too few arguments\r\n", ERR_TOO_FEW_ARGS);
      return 0;
    }

    /* set envirnment variables and control registers */
    init_settings(xfs_atoi(argv[1]));

    return 0;
  }

/************************************************************/
/*
  int sm_frequency_info(int argc, char **argv)
  {
    CMD_HELP("",
             "Report clock frequency measurements"
            );

    xfs_printf("F grefclk     = %9d Hz\r\n", ClockMeasure_GetFreq(XPAR_CLOCK_MEASURE_0_BASEADDR, 0) );
    xfs_printf("F userclk     = %9d Hz\r\n", ClockMeasure_GetFreq(XPAR_CLOCK_MEASURE_0_BASEADDR, 1) );
    xfs_printf("F userclk2    = %9d Hz\r\n", ClockMeasure_GetFreq(XPAR_CLOCK_MEASURE_0_BASEADDR, 2) );
    xfs_printf("F sgmii_clk_r = %9d Hz\r\n", ClockMeasure_GetFreq(XPAR_CLOCK_MEASURE_0_BASEADDR, 3) );
    xfs_printf("F fpga_clk    = %9d Hz (Nominal 80 MHz)\r\n\r\n", ClockMeasure_GetFreq(XPAR_CLOCK_MEASURE_0_BASEADDR, 4) );

    return 0;
  }
*/
/************************************************************/
/*
  int sm_cfg_data_dst(int argc, char **argv)
  {
    unsigned char mac[6];
    unsigned char ip[6];
    unsigned int header_num = 0;
    udp_gen_header_entry_type udp_gen_entry;
    int target_num, current_target = -1;

    CMD_HELP("<port> [<ip_addr> <mac_addr>]",
             "configure data destination settings",
             "Configurest the destination port, ip and address\r\n"
             "for event data.\r\n"
             "If the ip and mac addresse are not specified they\r\n"
             "are obtained from the latest command packet sent via UDP.\r\n"
             "  <port>     : destination port\r\n"
             "  <ip_addr>  : destination ip address\r\n"
             "  <mac_addr> : destination mac address\r\n"
            );

    if(argc < 2)
    {
      xfs_printf("E%02X: Too few arguments\r\n", ERR_TOO_FEW_ARGS);
      return 0;
    }
    else
    {
      if(argc == 2)
      {
*/        /* search for latest communication target */
/*        for (target_num=0; target_num < NUM_UDP_TERMINAL_CMD_PORTS; target_num++)
        {
          if ( udp_terminal_targets[target_num].valid && udp_terminal_targets[target_num].current_target )
          {
            current_target = target_num;
          }
        }

        if(current_target >= 0)
        {
          SYSPTR(nw_data_target)->dst_port = strtol(argv[1], NULL, 0);
          ncpy(SYSPTR(nw_data_target)->dst_mac_addr, udp_terminal_targets[current_target].dst_mac, 6);
          ncpy(SYSPTR(nw_data_target)->dst_ip_addr,  udp_terminal_targets[current_target].dst_ip,  4);
        }
        else
        {
          xfs_printf("E%02X: Invalid arguments. Type \"cfgdst help\" for help.\r\n", ERR_INVALID_ARGS);
          return 0;
        }
      }
      else if(argc == 3)
      {
        xfs_printf("E%02X: Invalid arguments. Type \"cfgdst help\" for help.\r\n", ERR_INVALID_ARGS);
        return 0;
      }
      else if(argc > 3)
      {
        if( !parse_ip((const char*)argv[2], ip) && !parse_mac((const char*)argv[3], mac) )
        {
          SYSPTR(nw_data_target)->dst_port = strtol(argv[1], NULL, 0);
          ncpy(SYSPTR(nw_data_target)->dst_mac_addr, mac, 6);
          ncpy(SYSPTR(nw_data_target)->dst_ip_addr,  ip,  4);
        }
        else
        {
          xfs_printf("E%02X: Invalid arguments. Type \"cfgdst help\" for help.\r\n", ERR_INVALID_ARGS);
          return 0;
        }
      }

      if(DBG_INFO)
      {
        xfs_printf("\r\nNew data destination:\r\n");
        xfs_printf("PORT: %d\r\n", SYSPTR(nw_data_target)->dst_port);
        xfs_printf("MAC:  %02X:%02X:%02X:%02X:%02X:%02X\r\n", SYSPTR(nw_data_target)->dst_mac_addr[0], SYSPTR(nw_data_target)->dst_mac_addr[1], SYSPTR(nw_data_target)->dst_mac_addr[2], SYSPTR(nw_data_target)->dst_mac_addr[3], SYSPTR(nw_data_target)->dst_mac_addr[4], SYSPTR(nw_data_target)->dst_mac_addr[5]);
        xfs_printf("IP:   %d.%d.%d.%d\r\n", SYSPTR(nw_data_target)->dst_ip_addr[0], SYSPTR(nw_data_target)->dst_ip_addr[1], SYSPTR(nw_data_target)->dst_ip_addr[2], SYSPTR(nw_data_target)->dst_ip_addr[3]);
      }
*/      /* configure UDP default header for packager */
/*      if(DBG_INFO) xfs_printf("Updating UDP default header...\r\n");
      udpgen_create_header_entry(SYSPTR(udp_pack_gen), &udp_gen_entry,
                                 SYSPTR(nw_if_gmac_0)->mac_addr,         SYSPTR(nw_if_gmac_0)->ip_addr,         SYSPTR(cfg)->nw_data_src_port,
                                 SYSPTR(nw_data_target)->dst_mac_addr, SYSPTR(nw_data_target)->dst_ip_addr, SYSPTR(nw_data_target)->dst_port);

      udpgen_header_to_plb_bram(SYSPTR(udp_pack_gen), &udp_gen_entry, header_num);
*/        /* enable data transmission */
/*      if(DBG_INFO) xfs_printf("Enabling data transmission...\r\n");
      gpio_sc_enable_event_data_transmission();
      if(DBG_INFO) xfs_printf("Done\r\n\r\n");
    }

    return 1;
  }
*/
/************************************************************/
/*
  int sm_data_tx_on_off(int argc, char **argv)
  {
    CMD_HELP("on | off",
             "enable or disable event data transmission",
             "Description: Enables or disables event data transmission.\r\n"
             "  on | off:   state state of event data transmission.\r\n"
            );
*/
    /* Check for minimum number of arguments */
/*    if(argc < 2)
    {
      xfs_printf("E%02X: Too few arguments\r\n", ERR_TOO_FEW_ARGS);
      return 0;
    }

    if(fstrcmp(argv[1],"on"))
    {
      gpio_sc_enable_event_data_transmission();
    }
    else if(fstrcmp(argv[1],"off"))
    {
      gpio_sc_disable_event_data_transmission();
    }
    else
    {
      xfs_printf("E%02X: Invalid arguments. Type \"calbuf help\" for help.\r\n", ERR_INVALID_ARGS);
      return 0;
    }

    return 1;
  }
*/
/************************************************************/
/*
  int sm_get_version(int argc, char **argv)
  {
    CMD_HELP("",
             "returns the version indicator values",
             "Returns the HW version information (VERS_IND).\r\n"
            );

    xfs_printf("\r\nCurrently not available.\r\nPins used for UART\r\n\r\n");

    return 0;
  }
*/
/************************************************************/

  int module_sm_help(int argc, char **argv)
  {
    CMD_HELP("",
             "System Management Module",
             "Commands for system mamangement functions"
            );

    return 0;
  }

/************************************************************/
/* COMMAND TABLE                                            */
/************************************************************/

  cmd_table_entry_type system_management_cmd_table[] =
  {
    {0, "sm", module_sm_help},
/*    {0, "reset", sm_reset}, */
    {0, "mark", sm_mark_board},
    {0, "unmark", sm_unmark_board},
    {0, "init", sm_init},
/*    {0, "fi", sm_frequency_info},     */
/*    {0, "cfgdst", sm_cfg_data_dst},   */
/*    {0, "datatx", sm_data_tx_on_off}, */
/*    {0, "version", sm_get_version},   */
    {0, NULL, NULL}
  };

/************************************************************/

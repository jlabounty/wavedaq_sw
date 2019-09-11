/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WaveDream2
 *
 *  Author  :  schmid_e
 *  Created :  09.09.2014 15:52:50
 *
 *  Description :  Info module for a command line interpreter.
 *                 Used to report general system and version information.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#include "wd2_config.h"
#include "xfs_printf.h"
#include "utilities.h"
/*#include "register_map_wd2.h"*/
#include "system.h"
#include "dbg.h"
#include "cmd_processor.h"
#include "drv_sys_mon.h"
#include <stdlib.h>


/************************************************************/

/* int print_ethernet_status(int argc, char **argv)
 * {
 *   CMD_HELP("","display network interface status");
 *
 *   nw_if_print_status(SYSPTR(nw_if_gmac_0));
 *
 *   return 0;
 * }
 */
/************************************************************/

/* int sm_sfp_info(int argc, char **argv)
 * {
 *   CMD_HELP("",
 *            "print SFP module info"
 *           );
 *
 *   xfs_printf("\r\nSFP 1\r\n");
 *   sfp_module_info(SYSPTR(sfp_ctrl[0]));
 *
 *   xfs_printf("\r\nSFP 2\r\n");
 *   sfp_module_info(SYSPTR(sfp_ctrl[1]));
 *
 *   xfs_printf("\r\n");
 *
 *   return 0;
 * }
 */
/************************************************************/

int cmd_sysmon(int argc, char **argv)
{
  int temp;
  int vdd;
  int i_tot;
  int v_5_0, v_3_3, v_2_5, v_2_0, v_1_8, v_1_5, v_1_0;

  CMD_HELP("",
           "print system monitor info"
          );

  temp  = sysmon_get_temp_mdeg(SYSPTR(sys_mon));
  vdd   = sysmon_get_vdd_mv(SYSPTR(sys_mon));
  i_tot = (int)(1000.0 * sysmon_get_voltage(SYSPTR(sys_mon), SYSMON_ADR_AIN0) * 0.5);
  v_5_0 = (int)(1000.0 * sysmon_get_voltage(SYSPTR(sys_mon), SYSMON_ADR_AIN1) * 2.5);
  v_3_3 = (int)(1000.0 * sysmon_get_voltage(SYSPTR(sys_mon), SYSMON_ADR_AIN2) * 5.0/3.0);
  v_2_5 = (int)(1000.0 * sysmon_get_voltage(SYSPTR(sys_mon), SYSMON_ADR_AIN3) * 1.22);
  v_2_0 = sysmon_get_voltage_mv(SYSPTR(sys_mon), SYSMON_ADR_AIN4);
  v_1_8 = sysmon_get_voltage_mv(SYSPTR(sys_mon), SYSMON_ADR_AIN5);
  v_1_5 = sysmon_get_voltage_mv(SYSPTR(sys_mon), SYSMON_ADR_AIN6);
  v_1_0 = sysmon_get_voltage_mv(SYSPTR(sys_mon), SYSMON_ADR_AIN7);

  xfs_printf("\r\nExternel System Monitor:\r\n\r\n");
  xfs_printf("Temperature      T: %4d.%03d deg C\r\n", temp/1000, temp%1000);
  xfs_printf("System Monitor Vdd: %4d.%03d V\r\n", vdd/1000, vdd%1000);
  xfs_printf("Main Current     I: %4d.%03d A\r\n", i_tot/1000, i_tot%1000);
  xfs_printf("Voltage    V(5.0V): %4d.%03d V\r\n", v_5_0/1000, v_5_0%1000);
  xfs_printf("Voltage    V(3.3V): %4d.%03d V\r\n", v_3_3/1000, v_3_3%1000);
  xfs_printf("Voltage    V(2.5V): %4d.%03d V\r\n", v_2_5/1000, v_2_5%1000);
  xfs_printf("Voltage    V(2.0V): %4d.%03d V\r\n", v_2_0/1000, v_2_0%1000);
  xfs_printf("Voltage    V(1.8V): %4d.%03d V\r\n", v_1_8/1000, v_1_8%1000);
  xfs_printf("Voltage    V(1.5V): %4d.%03d V\r\n", v_1_5/1000, v_1_5%1000);
  xfs_printf("Voltage    V(1.0V): %4d.%03d V\r\n", v_1_0/1000, v_1_0%1000);

  xfs_printf("\r\n");

  return 0;
}

/************************************************************/

int set_debug_level(int argc, char **argv)
{
  int d;
  CMD_HELP("[<debug_level>]",
           "show current or set new debug level",
           "Show / Set the debug level to control the amount\r\n"
           "of text output on the terminal.\r\n"
           "Shortform:  dbg    Longform:  dbglvl\r\n"
           "  <debug_level> :   0 .. 10 or name (not cast sensitive):\r\n"
           "                    NONE, ERR,  WARN, INIT, INF0, INF1,\r\n"
           "                          INF2, INF3, INF4, SPAM, ALL\r\n"
          );


  /* Check for minimum number of arguments */
  if(argc > 1)
  {
    d = get_dbg_level();
    xfs_printf("Previous dbglvl: %2d  (%s)\r\n", d, dbg_level_str[d]);
    d = parse_dbglvl(argv[1]);
    set_dbg_level(d);
  }

  d = get_dbg_level();
  xfs_printf("Current  dbglvl: %2d  (%s)\r\n", d, dbg_level_str[d]);

  return 0;
}

/************************************************************/

int cmd_echo(int argc, char **argv)
{
  CMD_HELP("<text>","display a line of text");

  if (argc < 2) return -1;

  xfs_printf("%s\r\n", argv[1]);
  return 0;
}

/************************************************************/

/* int cmd_uptime(int argc, char **argv)
 * {
 *   unsigned int total;
 *   unsigned int days;
 *   unsigned int hours;
 *   unsigned int minutes;
 *   unsigned int seconds;
 *
 *   CMD_HELP("","show time since system boot");
 *
 *   total    = time_get_sec();
 *   seconds  = total;
 *   days     = seconds / (60 * 60 * 24);
 *   seconds -= days    * (60 * 60 * 24);
 *   hours    = seconds / (60 * 60);
 *   seconds -= hours   * (60 * 60);
 *   minutes  = seconds / (60);
 *   seconds -= minutes * (60);
 *
 *   xfs_printf("uptime %3d days %02d:%02d:%02d  (total %d seconds)\r\n", days, hours, minutes, seconds, total);
 *
 *   return 0;
 * }
 */
/************************************************************/

/* int max31723_temp(int argc, char **argv)
 * {
 *   CMD_HELP("",
 *            "reads and prints the current temperature",
 *            "Allows access to temperature sensor MAX31723 via SPI\r\n"
 *           );
 *
 *   xfs_printf("\r\nT = ");
 *   max31723_print_temp();
 *   xfs_printf(" deg. C\r\n\r\n");
 *   return 0;
 * }
 */
/************************************************************/

int cmd_info(int argc, char **argv)
{
  CMD_HELP("",
           "display system information"
          );

  xfs_printf("\r\nVersion Information of DCB:\r\n\r\n");
  print_sys_info();
/*  xfs_printf("\r\n\r\nSerial Number: %d\r\n", reg_bank_get(WD2_REG_SN)); */
  xfs_printf("\r\n");

  return 0;
}
/************************************************************/

int module_status_help(int argc, char **argv)
{
  CMD_HELP("",
           "Status Module",
           "Reports system information like firmware version etc."
          );

  return 0;
}

/************************************************************/
/* COMMAND TABLE                                            */
/************************************************************/

cmd_table_entry_type status_cmd_table[] =
{
  {0, "status",   module_status_help},
  {0, "info",     cmd_info},
  {0, "sysmon",   cmd_sysmon},
  {2, "echo",     cmd_echo},
/*  {0, "ifconfig", print_ethernet_status}, */
/*  {0, "sfpinfo", sm_sfp_info}, */
  {0, "dbglvl",   set_debug_level},
  {0, "dbg",      set_debug_level},
/*  {0, "uptime",   cmd_uptime}, */
/*  {0, "temp",     max31723_temp}, */
  {0, NULL, NULL}
};

/************************************************************/

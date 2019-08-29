/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WaveDream2
 *
 *  Author  :  schmid_e
 *  Created :  26.08.2014 09:10:02
 *
 *  Description :  Module for accessing WDBs and TCB via the backplane SPI link.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#include "spi_bpl.h"
#include "dbg.h"
#include "xfs_printf.h"
#include "utilities.h"
#include "system.h"
#include "cmd_processor.h"

/************************************************************/

#define BIN_BUF_SIZE   64

/************************************************************/

  int slot_fpga_com(int argc, char **argv)
  {
    unsigned int wdb_slot;
    unsigned int idx;
    unsigned char bin_val;
    unsigned int len;
    unsigned int i;
    unsigned char tx_buff[BIN_BUF_SIZE];
    unsigned char rx_buff[BIN_BUF_SIZE];

    CMD_HELP("<wdb slot> <cmd>",
             "communicate to WDB via backplane SPI ASCII command.\r\n",
             "  <wdb slot> : WDB slot (0..15)\r\n"
             "  <cmd>      : command to send to WDB\r\n"
            );

    /* Check for minimum number of arguments */
    if(argc < 3)
    {
      xfs_printf("E%02X: Too few arguments\r\n", ERR_TOO_FEW_ARGS);
      return 0;
    }

    wdb_slot = strtoul(argv[1], NULL, 0);

    if(fstrpcmp("0x", argv[2]) || fstrpcmp("0X", argv[2])) /* binary command */
    {
      xfs_printf("Processing binary command\r\n");
      idx=2;
      len=0;
      /* convert hex string */
      while(argv[2][idx]!=0 && len<BIN_BUF_SIZE)
      {
        bin_val = hex_val(argv[2][idx])*16;
        idx++;
        if(argv[2][idx]!=0)
        {
          bin_val += hex_val(argv[2][idx]);
          idx++;
        }
        tx_buff[len] = bin_val;
        len++;
      }

      /* transmit */
      spi_binary_cmd(tx_buff, rx_buff, wdb_slot, len);

      /* report transmission results */
      xfs_printf("      TX byte   RX byte\r\n");
      for(i=0;i<len;i++)
      {
        xfs_printf("%3d   0x%02X      0x%02X\r\n", i, tx_buff[i], rx_buff[i]);
      }
      xfs_printf("\r\n");
    }
    else /* ascii command */
    {
      xfs_printf("Processing ASCII command\r\n");
      spi_ascii_cmd(argv[2], wdb_slot);
    }

    return 0;
  }

/************************************************************/

  int slot_flash_com(int argc, char **argv)
  {
    unsigned int wdb_slot;

    CMD_HELP("<wdb slot> <cmd>",
             "communicate to WDB flash via backplane.\r\n",
             "  <wdb slot> : WDB slot (0..15)\r\n"
             "  <cmd>      : command to send to WDB flash\r\n"
             "               e.g. id\r\n"
            );

    /* Check for minimum number of arguments */
    if(argc < 3)
    {
      xfs_printf("E%02X: Too few arguments\r\n", ERR_TOO_FEW_ARGS);
      return 0;
    }

    wdb_slot = strtoul(argv[1], NULL, 0);

    if(fstrcmp(argv[2],"id"))
    {
      spi_flash_id_cmd(wdb_slot);
    }

    return 0;
  }

/************************************************************/

  int module_crate_com_help(int argc, char **argv)
  {
    CMD_HELP("",
             "Register Bank Module",
             "Can be used to read and write registers of the register bank"
            );

    return 0;
  }

/************************************************************/
/* COMMAND TABLE                                            */
/************************************************************/

  cmd_table_entry_type crate_com_cmd_table[] =
  {
    {0, "crt_com", module_crate_com_help},
    {3, "wdb", slot_fpga_com},
    {0, "wdbf", slot_flash_com},
    {0, NULL, NULL}
  };

/************************************************************/

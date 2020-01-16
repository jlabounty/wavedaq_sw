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

#include "drv_bpl.h"
#include "dbg.h"
#include "xfs_printf.h"
#include "utilities.h"
#include "system.h"
#include "wdaq_board_id.h"
#include "cmd_processor.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/************************************************************/

#define BIN_BUF_SIZE   64

/************************************************************/

int parse_slot_selection(int argc, char **argv, slot_op_en_type *slot)
{
  int offset = 0;
  char *dashp = NULL;
  int from, to;
  int i;

  /* initialize operation enable for each slot */
  for(i=0;i<18;i++) slot->op_en[i]=0;

  if( (argc == 0) || !isdigit(argv[0][0]) )
  {
    /* set all */
    for(i=0;i<18;i++) slot->op_en[i] = 1;
    slot->op_en[16] = 0; /* DCB slot */
    if( fstrpcmp("all", argv[0]) )
    {
      return 1;
    }
    return 0;
  }

  while( (offset < argc) && isdigit(argv[offset][0]) )
  {
    from = (int)strtol(argv[offset], NULL, 10);
    if( from>17 ) from = 17;
    to   = 0;
    dashp = strstr(argv[offset],"-");
    if(dashp)
    {
      to = (int)strtol(dashp+1, NULL, 10);
      if( to>17 ) to = 17;
    }

    do
    {
      /* don't enable DCB slot (16) */
      if(from!=16)slot->op_en[from++] = 1;
    }
    while( from<=to );

    offset++;
  }

  return offset;
}

/************************************************************/

int crate_slot_fpga_com(int argc, char **argv)
{
  unsigned int slot;
  unsigned int idx;
  unsigned char bin_val;
  unsigned int len;
  unsigned int i;
  WDAQ_BRD board_info;
  unsigned char tx_buff[BIN_BUF_SIZE];
  unsigned char rx_buff[BIN_BUF_SIZE];

  CMD_HELP("<slot> <cmd>",
            "communicate to WDB/TCB via backplane SPI ASCII command.\r\n",
            "  <slot> : WDB/TCB slot (0..17 except 16 (DCB slot))\r\n"
            "  <cmd>  : command to send to WDB/TCB\r\n"
          );

  /* Check for minimum number of arguments */
  if(argc < 3)
  {
    xfs_printf("E%02X: Too few arguments\r\n", ERR_TOO_FEW_ARGS);
    return 0;
  }

  slot = strtoul(argv[1], NULL, 0);

  if(!get_slot_board_info(slot, &board_info)) return 0;

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
    spi_binary_cmd(tx_buff, rx_buff, len, slot, board_info.type_id, board_info.rev_id);

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
    char buffer[1600];
    xfs_printf("Processing ASCII command\r\n");
    spi_ascii_cmd(argv[2], buffer, sizeof(buffer), slot, board_info.type_id, board_info.rev_id);
    xfs_printf("%s\n", buffer);
  }

  return 0;
}

/************************************************************/

int crate_slot_upload_fw_sw(int argc, char **argv)
{
  slot_op_en_type slot;
  int offset;
  int opt;
  int load_fw = 0;
  int load_sw = 0;
  char *fwp = NULL;
  char *swp = NULL;
  WDAQ_BRD board_info;
  unsigned int board_type = 0;
  unsigned int board_rev = 0;
  unsigned int t_force = 0;
  unsigned int r_force = 0;

  CMD_HELP("[slot] [-f[firmware path]] [-s[software path]] [-t<board type> -r<board revision>]",
            "upload new firm- or software to WDB/TCB via backplane. If no files are specified,\r\n"
            "the standard firmware/software is taken from the /firmware/.../prod/... directory.\r\n",
            "  [slot] : WDB/TCB slot, optional, multiple entries possible separated by spaces.\r\n"
            "           Ranges (e.g. 4-7) can also be specified.\r\n"
            "  [-f[firmware path]]  : WDB/TCB firmware file (optional).\r\n"
            "  [-s[software path]]  : WDB software file (optional).\r\n"
            "  [-t<board type>]     : wdb or tcb (needed to \"force\" upload).\r\n"
            "  [-r<board revision>] : f, g etc for wdb 1, 2 etc for tcb (needed to \"force\" upload).\r\n"
          );

  offset = parse_slot_selection(argc-1, &argv[1], &slot);

  while((opt = getopt(argc, argv, ":f::s::t:r:")) != -1)
  {
    switch(opt)
    {
      case 'f':
        load_fw = 1;
        /* printf("firmware filename: %s\n", optarg); */
        if(optarg)
        {
          if(is_file(optarg))
          {
            fwp = optarg;
          }
          else
          {
            printf("firmware file %s not found\n", optarg);
            return -1;
          }
        }
        break;
      case 's':
        load_sw = 1;
        /* printf("software filename: %s\n", optarg); */
        if(optarg)
        {
          if(is_file(optarg))
          {
            swp = optarg;
          }
          else
          {
            printf("software file %s not found\n", optarg);
            return -1;
          }
        }
        break;
      case 't':
        /* printf("board type: %s\n", optarg); */
        t_force = 1;
        if( !strcmp(optarg, "wdb") )
        {
          board_type = BRD_TYPE_ID_WDB;
        }
        else if( !strcmp(optarg, "tcb") )
        {
          board_type = BRD_TYPE_ID_TCB;
        }
        else
        {
          printf("Error: unknown board type: %s\n", optarg);
          t_force = 0;
          return -1;
        }
        break;
      case 'r':
        /* printf("board revision: %s\n", optarg); */
        r_force = 1;
        if( optarg[0]>='0' && optarg[0]<='9' )
        {
          board_rev = strtoul(optarg, NULL, 0);
        }
        else if( optarg[0]>='a' && optarg[0]<='z' )
        {
          board_rev = optarg[0] - 'a';
        }
        else if( optarg[0]>='A' && optarg[0]<='Z' )
        {
          board_rev = optarg[0] - 'A';
        }
        else
        {
          printf("Error: invalid board revision: %s\n", optarg);
          r_force = 0;
          return -1;
        }
        break;
      case ':':
        printf("option needs a value\n");
        break;
      case '?':
        printf("unknown option: %c\n", optopt);
        break;
    }
  }
  if(load_fw==0 && load_sw==0)
  {
    load_fw = 1;
    load_sw = 1;
  }
  if(t_force && r_force)
  {
    /* forced upload */
    crate_upload_fw_sw(&slot, load_fw, fwp, load_sw, swp, board_type, board_rev, 1);
  }
  else
  {
    /* standard upload */
    crate_upload_fw_sw(&slot, load_fw, fwp, load_sw, swp, board_type, board_rev, 0);
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
  {3, "sltc", crate_slot_fpga_com},
  {0, "upload", crate_slot_upload_fw_sw},
  {0, NULL, NULL}
};

/************************************************************/

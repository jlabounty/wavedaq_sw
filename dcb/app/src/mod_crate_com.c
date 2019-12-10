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
  for(i=0;i<17;i++) slot->op_en[i]=0;

  if( (argc == 0) || !isdigit(argv[0][0]) )
  {
    /* set all */
    for(i=0;i<17;i++) slot->op_en[i] = 1;
    if( fstrpcmp("all", argv[0]) )
    {
      return 1;
    }
    return 0;
  }

  while( (offset < argc) && isdigit(argv[offset][0]) )
  {
    from = (int)strtol(argv[offset], NULL, 10);
    if( from>16 ) from = 16;
    to   = 0;
    dashp = strstr(argv[offset],"-");
    if(dashp)
    {
      to = (int)strtol(dashp+1, NULL, 10);
      if( to>16 ) to = 16;
    }

    do
    {
      slot->op_en[from++] = 1;
    }
    while( from<=to );

    offset++;
  }

  return offset;
}

/************************************************************/

int slot_fpga_com(int argc, char **argv)
{
  unsigned int slot;
  unsigned int idx;
  unsigned char bin_val;
  unsigned int len;
  unsigned int i;
  unsigned char tx_buff[BIN_BUF_SIZE];
  unsigned char rx_buff[BIN_BUF_SIZE];

  CMD_HELP("<slot> <cmd>",
            "communicate to WDB/TCB via backplane SPI ASCII command.\r\n",
            "  <slot> : WDB/TCB slot (0..15)\r\n"
            "  <cmd>  : command to send to WDB/TCB\r\n"
          );

  /* Check for minimum number of arguments */
  if(argc < 3)
  {
    xfs_printf("E%02X: Too few arguments\r\n", ERR_TOO_FEW_ARGS);
    return 0;
  }

  slot = strtoul(argv[1], NULL, 0);

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
    spi_binary_cmd(tx_buff, rx_buff, slot, len);

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
    spi_ascii_cmd(argv[2], slot);
  }

  return 0;
}

/************************************************************/

int slot_upload_fw_sw(int argc, char **argv)
{
  slot_op_en_type slot;
  int offset;
  int opt;
  char *fwp = NULL;
  char *swp = NULL;

  CMD_HELP("[slot] [-f <firmware path>] [-s <software path>]",
            "upload new firm- or software to WDB/TCB via backplane. If no files are specified,\r\n"
            "the standard firmware/software is taken from the /firmware/.../prod/... directory.\r\n",
            "  [slot] : WDB/TCB slot, optional, multiple entries possible separated by spaces.\r\n"
            "           Ranges (e.g. 4-7) can also be specified.\r\n"
            "  [-f <firmware path>] : WDB/TCB firmware file (optional).\r\n"
            "  [-s <software path>] : WDB software file (optional).\r\n"
          );

  offset = parse_slot_selection(argc-1, &argv[1], &slot);

  while((opt = getopt(argc, argv, ":f:s:")) != -1)
  {
    switch(opt)
    {
      case 'f':
        /* printf("firmware filename: %s\n", optarg); */
        if(is_file(optarg)) fwp = optarg;
        else printf("firmware file %s not found", optarg);
        break;
      case 's':
        /* printf("software filename: %s\n", optarg); */
        if(is_file(optarg)) swp = optarg;
        else printf("software file %s not found", optarg);
        break;
      case ':':
        printf("option needs a value\n");
        break;
      case '?':
        printf("unknown option: %c\n", optopt);
        break;
    }
  }
  bpl_upload_fw_sw(&slot, fwp, swp);
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
  {3, "sltc", slot_fpga_com},
  {0, "upload", slot_upload_fw_sw},
  {0, NULL, NULL}
};

/************************************************************/

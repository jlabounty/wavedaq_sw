/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WaveDream2
 *
 *  Author  :  schmid_e
 *  Created :  26.08.2014 09:10:02
 *
 *  Description :  Module for accessing control and status registers from cmd line.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#include "drv_axi_dcb_reg_bank.h"
//#include "register_map_dcb.h"
#include "dbg.h"
#include "xfs_printf.h"
#include "utilities.h"
#include "system.h"
#include "cmd_processor.h"
#include <ctype.h>
#include <stdlib.h>

#ifndef LINUX_COMPILE
#include "drv_qspi_flash.h"
#include "dcb_flash_memory_map.h"
#endif

#define REGDIFF_CMP_INITIAL  0
#define REGDIFF_CMP_STORED   1
#define REGDIFF_CMP_CURRENT  2

#define REGDIFF_POS_A  24
#define REGDIFF_POS_B  45

#define REG_START   0x0000
#define REG_END     (REG_START + ((NR_OF_REGS-2)*4))


/************************************************************/

  int reg_write_cmd(int argc, char **argv)
  {
    unsigned int offset;
    unsigned int data;

    CMD_HELP("<offset> <data>",
             "write to (control) register bank",
             "Longform: regwr / Shortform: rw\r\n"
             "Writes the data value to the corresponding register.\r\n"
             "  <offset> : offset from base address\r\n"
             "  <data>   : 32bit value to write\r\n"
            );


    /* Check for minimum number of arguments */
    if(argc < 3)
    {
      xfs_printf("E%02X: Too few arguments\r\n", ERR_TOO_FEW_ARGS);
      return 0;
    }

    offset = strtoul(argv[1], NULL, 0);
    data   = strtoul(argv[2], NULL, 0);

    xfs_printf("[0x%04X]: 0x%08X\r\n", offset, data);
    reg_bank_write(offset, &data, 1);

    return 0;
  }

/************************************************************/

  int reg_set_cmd(int argc, char **argv)
  {
    unsigned int offset;
    unsigned int data;

    CMD_HELP("<offset> <data>",
             "set bits of (control) register bank",
             "Longform: regset / Shortform: rs\r\n"
             "Sets the data bits of the corresponding register."
             "  <offset> : offset from base address\r\n"
             "  <data>   : 32bit value to write\r\n"
            );

    /* Check for minimum number of arguments */
    if(argc < 3)
    {
      xfs_printf("E%02X: Too few arguments\r\n", ERR_TOO_FEW_ARGS);
      return 0;
    }

    offset = strtoul(argv[1], NULL, 0);
    data   = strtoul(argv[2], NULL, 0);

    xfs_printf("setting [0x%04X]: 0x%08X\r\n", offset, data);
    reg_bank_set(offset, &data, 1);

    return 0;
  }

/************************************************************/

  int reg_clr_cmd(int argc, char **argv)
  {
    unsigned int offset;
    unsigned int data;

    CMD_HELP("<offset> <data>",
             "clear bits of (control) register bank",
             "Longform: regclr / Shortform: rc\r\n"
             "Clears the data bits of the corresponding register."
             "  <offset> : offset from base address\r\n"
             "  <data>   : 32bit value to write\r\n"
            );

    /* Check for minimum number of arguments */
    if(argc < 3)
    {
      xfs_printf("E%02X: Too few arguments\r\n", ERR_TOO_FEW_ARGS);
      return 0;
    }

    offset = strtoul(argv[1], NULL, 0);
    data   = strtoul(argv[2], NULL, 0);

    xfs_printf("clearing [0x%04X]: 0x%08X\r\n", offset, data);
    reg_bank_clr(offset, &data, 1);

    return 0;
  }

/************************************************************/

 int reg_mask_write_cmd(int argc, char **argv)
  {
    unsigned int offset;
    unsigned int mask;
    unsigned int data;

    CMD_HELP("<offset> <mask> <data>",
             "set bits of (control) register bank",
             "Longform: regset / Shortform: rs\r\n"
             "Sets the data bits of the corresponding register."
             "  <offset> : offset from base address\r\n"
             "  <mask>   : 32bit mask of bits to be written\r\n"
             "  <data>   : 32bit value to write\r\n"
            );

    /* Check for minimum number of arguments */
    if(argc < 4)
    {
      xfs_printf("E%02X: Too few arguments\r\n", ERR_TOO_FEW_ARGS);
      return 0;
    }

    offset = strtoul(argv[1], NULL, 0);
    mask   = strtoul(argv[2], NULL, 0);
    data   = strtoul(argv[3], NULL, 0);

    xfs_printf("writing [0x%04X]: 0x%08X (mask 0x%08X)\r\n", offset, mask & data, mask);
    reg_bank_mask_write(offset, &data, &mask, 1);

    return 0;
  }

/************************************************************/

int reg_read_cmd(int argc, char **argv)
  {
    unsigned int offset;
    unsigned int data;
    unsigned int nr_of_regs;

    CMD_HELP("<offset> <nr_of_regs>",
             "read from register bank",
             "Longform: regrd / Shortform: rr\r\n"
             "Reads the data value from the corresponding register.\r\n"
             "  <offset>     : Offset from register bank base address\r\n"
             "  <nr_of_regs> : Number of registers to read\r\n");

    /* Check for minimum number of arguments */
    if(argc < 2)
    {
      xfs_printf("E%02X: Too few arguments\r\n", ERR_TOO_FEW_ARGS);
      return 0;
    }

    offset     = strtoul(argv[1], NULL, 0);

    if(argc > 2) nr_of_regs = strtoul(argv[2], NULL, 0);
    else        nr_of_regs = 1;

    for(unsigned int i=0;i<nr_of_regs;i++)
    {
      reg_bank_read(offset+i*4, &data, 1);
      xfs_printf("[0x%04X]: 0x%08X\r\n", offset+i*4, data);
    }

    return 0;
  }

/************************************************************/

#ifndef LINUX_COMPILE
  int reg_store_cmd(int argc, char **argv)
  {
    CMD_HELP("",
             "store register bank contents into SPI flash"
            );

    if(DBG_INFO) xfs_printf("\r\nStoring register bank contents in SPI flash\r\n");
    reg_bank_store();

    return 0;
  }

/************************************************************/

  int reg_load_cmd(int argc, char **argv)
  {
    CMD_HELP("",
             "loads the register contents from the SPI flash"
            );

    if(DBG_INFO) xfs_printf("\r\nLoading register bank contents from SPI flash\r\n");
    reg_bank_load();

    return 0;
  }

/************************************************************/

  unsigned int regdiff_getreg(unsigned int reg, int sel )
  {
    unsigned int val;
    unsigned char flash_reg[4];

    if (sel == REGDIFF_CMP_INITIAL)
    {
      val = reg_default[reg/4];
    }
    else if (sel == REGDIFF_CMP_STORED)
    {
      qspi_flash_read(SYSPTR(spi_flash), QSPI_FLASH_REG_CONTENTS_ADDR+reg, 4, QSFL_QUAD_READ_CMD, (unsigned char*)(&flash_reg));
      val = 0;
      for(int i=3;i>=0;i--)
      {
        val = val << 8;
        val |= flash_reg[i];
      }
    }
    else /* REGDIFF_CMP_CURRENT */
    {
      reg_bank_read(reg, &val, 1);
    }

    return val;
  }

/************************************************************/

  int reg_diff_cmd(int argc, char **argv)
  {
    int ac = 0;
    int show_all = 0;
    int show_readonly = 0;
    int regcmp[2] = {REGDIFF_CMP_STORED, REGDIFF_CMP_CURRENT};
    int rc = 0;
    const char *rc_names[3] = {"initial", "stored", "current"};
    unsigned int reg_sel[2] = {REG_START, REG_END};
    unsigned int max_regs;
    unsigned int mask, reg, val_a, val_b;
    unsigned int rs = 0;
    int i, changed;
    char diff_line[REGDIFF_POS_B + 11];


    CMD_HELP("[-a][-r] [i|s|c [i|s|c]] [<reg> [<count>]]","compare control registers",
             "       -a : show all registers, even when equal\r\n"
             "       -r : show read-only registers when not equal\r\n"
             "        i : initial register\r\n"
             "        s : stored  register, default for left column\r\n"
             "        c : current register, default for right column\r\n"
             "    <reg> : starting register, default: first ctrl reg\r\n"
             "  <count> : number of registers, default 1 if <reg> is specified, otherwise all\r\n"
             );

    while (++ac < argc)
    {
      if (fstrcmp(argv[ac], "-a")) show_all = 1;
      else if (fstrcmp(argv[ac], "-r")) show_readonly = 1;
      else if (fstrcmp(argv[ac], "i" )  || fstrcmp(argv[ac], rc_names[REGDIFF_CMP_INITIAL]))  regcmp[rc++ & 1] = REGDIFF_CMP_INITIAL;
      else if (fstrcmp(argv[ac], "s" )  || fstrcmp(argv[ac], rc_names[REGDIFF_CMP_STORED]))   regcmp[rc++ & 1] = REGDIFF_CMP_STORED;
      else if (fstrcmp(argv[ac], "c" )  || fstrcmp(argv[ac], rc_names[REGDIFF_CMP_CURRENT]))  regcmp[rc++ & 1] = REGDIFF_CMP_CURRENT;
      else if (isdigit(argv[ac][0]))  reg_sel[rs++ & 1] = strtol(argv[ac], 0, 0);
    }

    /* check boundaries */
    if (reg_sel[0] <  REG_START) reg_sel[0] = REG_START;
    if (reg_sel[0] >  REG_END)   reg_sel[0] = REG_END;
    if (rs == 1) reg_sel[1] = 1;
    else
    {
      max_regs = (((REG_END - reg_sel[0]) / 4 ) + 1);
      if (reg_sel[1] > max_regs) reg_sel[1] = max_regs;
    }

    /*
    xfs_printf("show_all  : %d\r\n",show_all);
    xfs_printf("left      : %s\r\n",rc_names[regcmp[0]]);
    xfs_printf("right     : %s\r\n",rc_names[regcmp[1]]);
    xfs_printf("reg start : 0x%04x\r\n",reg_sel[0]);
    xfs_printf("reg count : %d\r\n",reg_sel[1]);
    */

    for (i = 0; i < (REGDIFF_POS_B + 8); i++) diff_line[i]=' ';
    diff_line[REGDIFF_POS_B + 8]  = '\r';
    diff_line[REGDIFF_POS_B + 9]  = '\n';
    diff_line[REGDIFF_POS_B + 10] = '\0';

    reg = reg_sel[0];
    for (rs=0; rs < reg_sel[1]; rs++)
    {
      val_a = regdiff_getreg(reg, regcmp[0]);
      val_b = regdiff_getreg(reg, regcmp[1]);
      changed = (val_a != val_b);
      if ( (changed && (!dcb_reg_list[reg/4].read_only || show_readonly)) || show_all)
      {
        xfs_printf("reg[0x%04x]  %7s: 0x%08x  %7s: 0x%08x  %s\r\n", reg, rc_names[regcmp[0]], val_a, rc_names[regcmp[1]], val_b, (changed && show_all) ? "!!!" : "" );
        if (changed)
        {
          for (i = 0; i <  8; i++)
          {
            mask = 0xf0000000 >> (4 * i);

            if ((val_a & mask) == (val_b & mask))
            {
              diff_line[REGDIFF_POS_A + i] = '=';
              diff_line[REGDIFF_POS_B + i] = '=';
            }
            else
            {
              diff_line[REGDIFF_POS_A + i] = '^';
              diff_line[REGDIFF_POS_B + i] = '^';
            }
          }
          xfs_printf(diff_line);
        }
      }
      reg += 4;
    }

    return 0;
  }
#endif /* No LINUX_COMPILE */

/************************************************************/

  int module_reg_help(int argc, char **argv)
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

  cmd_table_entry_type reg_access_cmd_table[] =
  {
    {0, "reg", module_reg_help},
    {0, "regwr", reg_write_cmd},
    {0, "rw", reg_write_cmd},
    {0, "regrd", reg_read_cmd},
    {0, "rr", reg_read_cmd},
    {0, "regset", reg_set_cmd},
    {0, "rs", reg_set_cmd},
    {0, "regclr", reg_clr_cmd},
    {0, "rc", reg_clr_cmd},
    {0, "regmwr", reg_mask_write_cmd},
    {0, "rmw", reg_mask_write_cmd},
#ifndef LINUX_COMPILE
    {0, "regstore", reg_store_cmd},
    {0, "regload", reg_load_cmd},
    {0, "regdiff", reg_diff_cmd},
#endif
    {0, NULL, NULL}
  };

/************************************************************/

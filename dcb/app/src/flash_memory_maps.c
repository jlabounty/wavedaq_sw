/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  MEG DCB
 *
 *  Author  :  schmid_e
 *  Created :  17.12.2019 12:04:14
 *
 *  Description :  Central control for hardware access.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#include "system.h"
#include "flash_memory_maps.h"
#include <stdio.h>
#include <string.h>

/* TBD: sizes and partition numbers can be filled by parsing /proc/mtd */
flash_partition_type dcb_flash_partitions[] =
{
  /* Name           , Size      , Base Offs , Head Offs , MTD Part. Nr. */
  {"qspi-header"    , 0x00010000, 0x00000000, 0x00000000, MTD_QSPI_FLASH_HEADER},
  {"qspi-regcontent", 0x00010000, 0x00000000, 0x00000000, MTD_QSPI_FLASH_REGCONTENT},
  {"qspi-fsbl"      , 0x00200000, 0x00000000, 0x00000000, MTD_QSPI_FLASH_FSBL},
  {"qspi-bitstream" , 0x005c0000, 0x00000000, 0x00000000, MTD_QSPI_FLASH_BITSTREAM},
  {"qspi-reserved"  , 0x017e0000, 0x00000000, 0x00000000, MTD_QSPI_FLASH_RESERVED},
  {"qspi-env"       , 0x00040000, 0x00000000, 0x00000000, MTD_QSPI_FLASH_ENV},
  {NULL, 0, 0, 0, 0}
};

flash_partition_type wdb_flash_partitions[] =
{
  /* Name    , Size      , Base Offs , Head Offs , MTD Part. Nr. */
  {"fw"      , 0x00420000, 0x00000000, 0x0041F000, MTD_WDB_FLASH_BITSTREAM},
  {"sw"      , 0x00200000, 0x00000000, 0x001FF000, MTD_WDB_FLASH_SOFTWARE},
  {"reserved", 0x009e0000, 0x00000000, 0x00000000, MTD_WDB_FLASH_RESERVED},
  {NULL, 0, 0, 0, 0}
};

flash_partition_type tcb_flash_partitions[] =
{
  /* Name, Size    , Base Offs , Head Offs , MTD Part. Nr. */
  {"fw", 0x01000000, 0x00000000, 0x00FF0000, MTD_TCB_FLASH_BITSTREAM},
  {NULL, 0, 0, 0, 0}
};

flash_memory_map_type flash_memories[] =
{
  {BRD_TYPE_ID_DCB, DCB_BRD_REV_ID_B, "7z030fbg676"  , NULL               , dcb_flash_partitions},
  {BRD_TYPE_ID_WDB, WDB_BRD_REV_ID_E, "6slx100fgg484", wdb_rf_default_path, wdb_flash_partitions},
  {BRD_TYPE_ID_WDB, WDB_BRD_REV_ID_F, "6slx100fgg484", wdb_rf_default_path, wdb_flash_partitions},
  {BRD_TYPE_ID_WDB, WDB_BRD_REV_ID_G, "6slx150fgg484", wdb_rg_default_path, wdb_flash_partitions},
  {BRD_TYPE_ID_TCB, TCB_BRD_REV_ID_1, "7k325tffg900" , tcb_t1_default_path, tcb_flash_partitions},
  {BRD_TYPE_ID_TCB, TCB_BRD_REV_ID_2, "7k325tffg900" , tcb_t2_default_path, tcb_flash_partitions},
  {BRD_TYPE_ID_TCB, TCB_BRD_REV_ID_3, "7k325tffg900" , tcb_t3_default_path, tcb_flash_partitions},
  {0, 0, NULL, NULL, NULL}
};

/******************************************************************************/

flash_memory_map_type* get_flash_mem_map(unsigned int board_type, unsigned int board_rev)
{
  flash_memory_map_type *flash_ptr;

  for(flash_ptr = flash_memories; flash_ptr->fpga_type ; flash_ptr++)
  {
    if( (flash_ptr->board_type == board_type) && (flash_ptr->board_rev == board_rev) )
    {
      return flash_ptr;
    }
  }
  return NULL;
}

/******************************************************************************/

flash_partition_type* get_flash_partition(flash_memory_map_type *flash_ptr, const char* partition_name)
{
  flash_partition_type  *partition_ptr;

//  printf("  => looking for partition %s:\n", partition_name);
  if(flash_ptr)
  {
    for(partition_ptr = flash_ptr->partition_table; partition_ptr; partition_ptr++)
    {
//      printf("    partition %s", partition_ptr->name);
      if(!strcmp(partition_ptr->name, partition_name))
      {
//        printf(" -> Match\n");
        return partition_ptr;
      }
//      else printf(" -> NO\n");
    }
  }
  return NULL;
}

/******************************************************************************/

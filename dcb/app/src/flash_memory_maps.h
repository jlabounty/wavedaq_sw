/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  MEG DCB
 *
 *  Author  :  schmid_e
 *  Created :  17.12.2019 12:04:52
 *
 *  Description :  Central control for hardware access.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#ifndef __FLASH_MEMORY_MAPS_H__
#define __FLASH_MEMORY_MAPS_H__

#define BOARD_TYPE_ID_DCB   1
#define BOARD_TYPE_ID_WDB   2
#define BOARD_TYPE_ID_TCB   3

#define BOARD_REV_ID_A      0x00000001
#define BOARD_REV_ID_B      0x00000002
#define BOARD_REV_ID_C      0x00000003
#define BOARD_REV_ID_D      0x00000004
#define BOARD_REV_ID_E      0x00000005
#define BOARD_REV_ID_F      0x00000006
#define BOARD_REV_ID_G      0x00000007
#define BOARD_REV_ID_H      0x00000008
#define BOARD_REV_ID_I      0x00000009
#define BOARD_REV_ID_J      0x0000000A
#define BOARD_REV_ID_K      0x0000000B
#define BOARD_REV_ID_1      0x00000100
#define BOARD_REV_ID_2      0x00000200
#define BOARD_REV_ID_3      0x00000300


typedef struct
{
  const char   *name;
  unsigned int size;
  unsigned int base_offset;
  unsigned int header_offset;
  const char   *mtd_partition;
} flash_partition_type;

typedef struct
{
  unsigned int board_type;
  unsigned int board_rev;
  const char *fpga_type;
  const char *default_fw_path;
  flash_partition_type *partition_table;
} flash_memory_map_type;

extern flash_memory_map_type   flash_memories[];

extern flash_partition_type    dcb_flash_partitions[];
extern flash_partition_type    wdb_flash_partitions[];
extern flash_partition_type    tcb_flash_partitions[];

flash_memory_map_type* get_flash_mem_map(unsigned int board_type, unsigned int board_rev);
flash_partition_type* get_flash_partition(flash_memory_map_type *flash_ptr, const char* partition_name);

/******************************************************************************/

#endif /* __FLASH_MEMORY_MAPS_H__  */

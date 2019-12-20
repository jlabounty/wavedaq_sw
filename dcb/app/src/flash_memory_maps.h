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
  const char *board_type;
const char *board_rev;
  const char *fpga_type;
  const char *default_fw_path;
  flash_partition_type *partition_table;
} flash_memory_map_type;

extern flash_memory_map_type   flash_memories[];

extern flash_partition_type    dcb_flash_partitions[];
extern flash_partition_type    wdb_flash_partitions[];
extern flash_partition_type    tcb_flash_partitions[];

flash_memory_map_type* get_flash_mem_map(const char *board_type, const char *board_rev);
flash_partition_type* get_flash_partition(flash_memory_map_type *flash_ptr, const char* partition_name);

/******************************************************************************/

#endif /* __FLASH_MEMORY_MAPS_H__  */

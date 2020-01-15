/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WaveDream2
 *
 *  Author  :  schmid_e, theidel
 *  Created :  11.10.2018 14:46
 *
 *  Description :  Central control for hardware access.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#ifndef __DCB_FLASH_MEMORY_MAP_H__
#define __DCB_FLASH_MEMORY_MAP_H__

/* SPI Flash Memory Map */
#define QSPI_FLASH_BOOTROM_HDR_ADDR                0x00000000
#define QSPI_FLASH_BOOTROM_HDR_SIZE                0x00001000
#define QSPI_FLASH_BOOTROM_HDR_SECTORS_4KB         1

#define QSPI_FLASH_REG_CONTENTS_ADDR               0x00010000
#define QSPI_FLASH_REG_CONTENTS_SIZE               0x00001000
#define QSPI_FLASH_REG_CONTENTS_SECTORS_4KB        1

#define QSPI_FLASH_ENVIRONMENT_ADDR                0x01FC0000
#define QSPI_FLASH_ENVIRONMENT_NAME                "/dev/mtd9"
#define QSPI_FLASH_REDUNDANT_ENVIRONMENT_ADDR      0x01FD0000
/*#define QSPI_FLASH_REDUNDANT_ENVIRONMENT_NAME      "/dev/mtd9"*/
#define QSPI_FLASH_REDUNDANT_ENVIRONMENT_OFFSET    0x00010000
#define QSPI_FLASH_ENVIRONMENT_SIZE                0x00010000
#define QSPI_FLASH_ENVIRONMENT_SECTORS             1

#define QSPI_FLASH_FSBL_ADDR                       0x00020000
#define QSPI_FLASH_FSBL_HEADER_OFFS                0x001F0000
#define QSPI_FLASH_FSBL_SIZE                       0x00200000
#define QSPI_FLASH_FSBL_SECTORS                    32

#define QSPI_FLASH_PL_BITSTREAM_ADDR               0x00220000
#define QSPI_FLASH_PL_BITS_HEADER_OFFS             0x005BF000 /* caution: 64kB sectors */
#define QSPI_FLASH_PL_BITSTREAM_SIZE               0x005C0000
#define WD2_FPGA_TYPE                              "7z030fbg676"
#define WD2_FPGA_UID                               0xFFFFFFFF
#define QSPI_FLASH_BITSTREAM_SECTORS               92

#define QSPI_FLASH_SOFTWARE_ADDR                   0x007E0000
#define QSPI_FLASH_SW_HEADER_OFFS                  0x009F0000
#define QSPI_FLASH_SOFTWARE_SIZE                   0x00A00000
#define QSPI_FLASH_SOFTWARE_SECTORS                160

/* #define QSPI_FLASH_MSCB_CONFIG_ADDR           0x007E0000
 * #define QSPI_FLASH_MSCB_CONFIG_SIZE           0x00001000
 * #define QSPI_FLASH_MSCB_CONFIG_SECTORS        1
 */

/******************************************************************************/

#endif /* __DCB_FLASH_MEMORY_MAP_H__  */

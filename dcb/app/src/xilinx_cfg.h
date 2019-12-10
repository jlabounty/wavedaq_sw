/******************************************************************************/
/*                                                                            */
/*  file: xilinx_cfg.h                                                        */
/*                                                                            */
/*  (c) 2016 PSI tg32                                                         */
/*                                                                            */
/******************************************************************************/

#ifndef __XILINX_CFG_H__
#define __XILINX_CFG_H__


/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/

#include "srec.h"

/******************************************************************************/
/* constant definitions                                                       */
/******************************************************************************/

#define BITFILE_HEADER_ID        0xBF8EADE9


#define XCFG_FIELD_NAME_OFFS     0
#define XCFG_FIELD_FPGA_OFFS     1
#define XCFG_FIELD_DATE_OFFS     2
#define XCFG_FIELD_TIME_OFFS     3 
#define XCFG_FIELD_DATA_LEN      4
#define XCFG_FIELD_HEAD_LEN      5
#define XCFG_FIELD_HEAD_ID       6
#define XCFG_FIELD_CHECKSUM      7

#define XSW_FIELD_NAME_OFFS      0
#define XSW_FIELD_DATA_LEN       1
#define XSW_FIELD_HEAD_REC_LEN   2
#define XSW_FIELD_CHECKSUM       4

/* Spartan 6 Bitstream definitions */
#define XCFG_6S_SPI_READ_CMD              0x6b
#define XCFG_6S_DUMMY_WORD                0xFFFF
#define XCFG_6S_SYNC_0                    0xAA99
#define XCFG_6S_SYNC_1                    0x5566
#define XCFG_6S_NOOP                      0x2000
#define XCFG_6S_BITGEN_OFFS               0x0044

#define XCFG_6S_HC_OPT_DO_NOT_SKIP_INIT   0x001F
#define XCFG_6S_HC_OPT_SKIP_INIT          0x005F


/******************************************************************************/
/* type definitions                                                           */
/******************************************************************************/

typedef struct
{
  unsigned int name_offs;
  unsigned int fpga_offs;
  unsigned int date_offs;     
  unsigned int time_offs; 
  unsigned int data_len;     /* Binary Len in byte */
  unsigned int head_len;     /* Header len in byte */
  unsigned int head_id;      /* 0xBF8EADE9 */
  unsigned int checksum;     /* ~ (name_offs + fpga_offs + ... + head_id) */
} bitfile_struct_type;


typedef union 
{
   unsigned int field[sizeof(bitfile_struct_type)/sizeof(unsigned int)];
   bitfile_struct_type info;
} bitfile_info_type;


typedef struct
{
  unsigned int name_offs;
  unsigned int data_len;     /* SREC file size in byte */
  unsigned int head_len;     /* Header len in byte */
  unsigned int checksum;     /* ~ (name_offs + data_len + ... + data_len) */
} sw_file_struct_type;


typedef union 
{
   unsigned int field[sizeof(sw_file_struct_type)/sizeof(unsigned int)];
   sw_file_struct_type info;
} sw_file_info_type;


unsigned int bitfile_info_checksum(bitfile_info_type *biptr);
int parse_bitfile(unsigned char *buf, unsigned int len, bitfile_info_type *biptr);
unsigned int sw_file_info_checksum(sw_file_info_type *siptr);
int parse_srec(unsigned char *buf, unsigned char *header_data_buf);


#endif /* __XILINX_CFG_H__ */

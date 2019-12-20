/******************************************************************************/
/*                                                                            */
/*  file: xilinx_cfg.c                                                        */
/*                                                                            */
/*  (c) 2016 PSI tg32                                                         */
/*                                                                            */
/******************************************************************************/


/******************************************************************************/
/* include files                                                              */
/******************************************************************************/

#include <stddef.h>
#include "xilinx_cfg.h"

/******************************************************************************/
/* functions                                                                  */
/******************************************************************************/

unsigned int bitfile_info_checksum(bitfile_info_type *biptr)
{
  unsigned int i;

  unsigned int checksum = biptr->field[0];
  for (i=1; i < sizeof(bitfile_info_type)/sizeof(unsigned int) - 1; i++)
  {
    checksum += biptr->field[i];
  }
  return (~checksum);  /* bitwise invert checksum */
}


/******************************************************************************/

int parse_bitfile(unsigned char *buf, unsigned int len, bitfile_info_type *biptr)
{
  unsigned char magic_header[] = {0x00, 0x09, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x00, 0x00, 0x01 };
  unsigned int pos = 0;
  unsigned int field;
  unsigned int field_len;


  if (len < sizeof(magic_header) + 20) return -1;

  for (pos=0; pos < sizeof(magic_header); pos++)  if (buf[pos] !=  magic_header[pos]) return -1;

  for (field=0; field <= XCFG_FIELD_DATA_LEN; field++)
  {
    if (len < (pos + 3)) return -1;

    /* check key */
    if (buf[pos++] != ('a' + field)) return -1;

    if (field == XCFG_FIELD_DATA_LEN)
    {
      if (len < (pos + 4)) return -1;
      if (biptr)
      {
        biptr->field[XCFG_FIELD_DATA_LEN] = (buf[pos]   << 24) + (buf[pos+1] << 16) +
                                            (buf[pos+2] <<  8) +  buf[pos+3] ;
        biptr->field[XCFG_FIELD_HEAD_LEN] = pos + 4;
        biptr->field[XCFG_FIELD_HEAD_ID]  = BITFILE_HEADER_ID;
        biptr->field[XCFG_FIELD_CHECKSUM] = bitfile_info_checksum(biptr);
      }
      return pos + 4;
    }

    /* get field length */
    field_len =  (buf[pos] <<  8) +  buf[pos+1] ;
    pos += 2;

    if (len < (pos + field_len)) return -1;

    if (biptr) biptr->field[field] = pos;
    pos += field_len ;
  }

  /* never reached, returns inside loop */
  return -1;
}

/******************************************************************************/

unsigned int sw_file_info_checksum(sw_file_info_type *siptr)
{
  unsigned int i;

  unsigned int checksum = siptr->field[0];
  for (i=1; i < sizeof(sw_file_info_type)/sizeof(unsigned int) - 1; i++)
  {
    checksum += siptr->field[i];
  }
  return (~checksum);  /* bitwise invert checksum */
}


/******************************************************************************/

int parse_srec(unsigned char *buf, unsigned char *header_data_buf)
{
  srec_info_t srec_info;
  unsigned char status;

  srec_info.sr_data     = NULL;
  srec_info.sr_hdr_data = header_data_buf;

  status = decode_srec_line (buf, &srec_info);
  if(status) return -1; /* OK=0, SREC_PARSE_ERROR=3, SREC_CKSUM_ERROR=4 */

  if(srec_info.dlen >= SREC_DATA_MAX_BYTES) srec_info.dlen = SREC_DATA_MAX_BYTES;
  srec_info.sr_hdr_data[srec_info.dlen] = 0; /* terminate header string */

  return srec_info.dlen;
}


/******************************************************************************/

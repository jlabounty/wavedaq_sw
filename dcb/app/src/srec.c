/*
 *
 * Copyright (c) 2004 Xilinx, Inc. All Rights Reserved.
 *
 * You may copy and modify these files for your own internal use solely with
 * Xilinx programmable logic devices and  Xilinx EDK system or create IP
 * modules solely for Xilinx programmable logic devices and Xilinx EDK system.
 * No rights are granted to distribute any files unless they are distributed in
 * Xilinx programmable logic devices.
 */

#include "xfs_types.h"
#include "srec.h"
#include "errors.h"

xfs_u8  grab_hex_byte (xfs_u8 *buf);
xfs_u16 grab_hex_word (xfs_u8 *buf);
xfs_u32 grab_hex_dword (xfs_u8 *buf);
xfs_u32 grab_hex_word24 (xfs_u8 *buf);

int srec_line = 0;

xfs_u8 nybble_to_val (char x)
{
    if (x >= '0' && x <= '9')
        return (xfs_u8)(x-'0');
    
    return (xfs_u8)((x-'A') + 10);
}

xfs_u8 grab_hex_byte (xfs_u8 *buf)
{
    return  (xfs_u8)((nybble_to_val ((char)buf[0]) << 4) + 
                       nybble_to_val ((char)buf[1]));
}

xfs_u16 grab_hex_word (xfs_u8 *buf)
{
    return (xfs_u16)(((xfs_u16)grab_hex_byte (buf) << 8) 
                      + grab_hex_byte ((xfs_u8*)((int)buf+2))
                     );
}

xfs_u32 grab_hex_word24 (xfs_u8 *buf)
{
    return (xfs_u32)(((xfs_u32)grab_hex_byte (buf) << 16) 
                      + grab_hex_word ((xfs_u8*)((int)buf+2))
                     );
}

xfs_u32 grab_hex_dword (xfs_u8 *buf)
{
    return (xfs_u32)(((xfs_u32)grab_hex_word (buf) << 16) 
                      + grab_hex_word ((xfs_u8*)((int)buf+4))
                     );
}

xfs_u8 decode_srec_data (xfs_u8 *bufs, xfs_u8 *bufd, xfs_u8 count, xfs_u8 skip)
{
    xfs_u8 cksum = 0, cbyte;
    int i;

    /* Parse remaining character pairs */
    for (i=0; i < count; i++) {
        cbyte = grab_hex_byte (bufs);
        if ((i >= skip - 1) && (i != count-1))   /* Copy over only data bytes */
            *bufd++ = cbyte;
        bufs  += 2;
        cksum += cbyte;
    }

    return cksum;
}

xfs_u8 eatup_srec_line (xfs_u8 *bufs, xfs_u8 count)
{
    int i;
    xfs_u8 cksum = 0;

    for (i=0; i < count; i++) {
        cksum += grab_hex_byte(bufs);
        bufs += 2;
    }

    return cksum;
}

xfs_u8 decode_srec_line (xfs_u8 *sr_buf, srec_info_t *info)
{
    xfs_u8 count;
    xfs_u8 *bufs;
    xfs_u8 cksum = 0, skip;
    int type;

    bufs = sr_buf;

    srec_line++; /* for debug purposes on errors */

    if ( *bufs != 'S') {
        return SREC_PARSE_ERROR;
    }
    
    type = *++bufs - '0';
    count = grab_hex_byte (++bufs);
    bufs += 2;
    cksum = count;

    switch (type)
    {
        case 0: 
            info->type = SREC_TYPE_0;
            skip = 3;
            info->dlen = count - skip;
            cksum += decode_srec_data (bufs, info->sr_hdr_data, count, skip);
            break;
        case 1: 
            info->type = SREC_TYPE_1;
            skip = 3;
            info->addr = (xfs_u8*)(xfs_u32)grab_hex_word (bufs);
            info->dlen = count - skip;
            cksum += decode_srec_data (bufs, info->sr_data, count, skip);
            break;
        case 2: 
            info->type = SREC_TYPE_2;
            skip = 4;
            info->addr = (xfs_u8*)(xfs_u32)grab_hex_word24 (bufs);
            info->dlen = count - skip;
            cksum += decode_srec_data (bufs, info->sr_data, count, skip);
            break;
        case 3: 
            info->type = SREC_TYPE_3;
            skip = 5;
            info->addr = (xfs_u8*)(xfs_u32)grab_hex_dword (bufs);
            info->dlen = count - skip;
            cksum += decode_srec_data (bufs, info->sr_data, count, skip);
            break;
        case 5:
            info->type = SREC_TYPE_5;
            info->addr = (xfs_u8*)(xfs_u32)grab_hex_word (bufs);
            cksum += eatup_srec_line (bufs, count);
            break;
        case 7:
            info->type = SREC_TYPE_7;
            info->addr = (xfs_u8*)(xfs_u32)grab_hex_dword (bufs);
            cksum += eatup_srec_line (bufs, count);
            break;
        case 8:
            info->type = SREC_TYPE_8;
            info->addr = (xfs_u8*)(xfs_u32)grab_hex_word24 (bufs);
            cksum += eatup_srec_line (bufs, count);
            break;
        case 9:
            info->type = SREC_TYPE_9;
            info->addr = (xfs_u8*)(xfs_u32)grab_hex_word (bufs);
            cksum += eatup_srec_line (bufs, count);
            break;
        default:
            return SREC_PARSE_ERROR;
    }

    if (++cksum) {
        return SREC_CKSUM_ERROR;
    }
   
    return 0;
}



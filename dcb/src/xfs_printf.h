/******************************************************************************/
/*                                                                            */
/*  file: xfs_printf.h                                                        */
/*                                                                            */
/*  (c) 2010 PSI se32                                                         */
/*                                                                            */
/******************************************************************************/

#ifndef __XFS_PRINTF_H__
#define __XFS_PRINTF_H__

/******************************************************************************/

#ifdef LINUX_COMPILE
#include <stdio.h>

#define xfs_printf          printf
#define xfs_local_printf    printf
#define xfs_terminal_printf printf
#define xfs_snprintf        snprintf

/******************************************************************************/
#else  // no LINUX_COMPILE
/******************************************************************************/

#include <stdarg.h>
#include <string.h>

#define STRING_BUFFER_SIZE 256

#define XFS_PRINTF_REPLY_MODE_ALL      0
#define XFS_PRINTF_REPLY_MODE_SENDER   1

#define XFS_PRINTF_TARGET_NONE    0x0000
#define XFS_PRINTF_TARGET_LOCAL   0x0001
#define XFS_PRINTF_TARGET_UDP     0x0002
#define XFS_PRINTF_TARGET_SPI     0x0004
#define XFS_PRINTF_TARGET_ALL     0x0007

/*****************************************************************/

typedef char * charptr;

int xfs_printf(const char *format, ...);
int xfs_vsnprintf(char *outbuf1, int max_buffer_size, const char *format, va_list argp);
int xfs_snprintf(char *outbuf1, int max_buffer_size, const char *format, ...);

int xfs_local_printf(const char *format, ...);
int xfs_terminal_printf(const char *format, ...);

void set_cmd_sender(unsigned int sender);
void no_cmd_sender();
void reapply_cmd_sender();
unsigned int get_cmd_sender();
void set_cmd_reply_mode(unsigned int reply_mode);
unsigned int get_xfs_printf_targets();

#endif /*  LINUX_COMPILE */

/******************************************************************************/

#endif /* __XFS_PRINTF_H__ */

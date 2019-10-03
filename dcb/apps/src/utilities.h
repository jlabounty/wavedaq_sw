/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WaveDream2
 *
 *  Authr  :  schmid_e, tg32
 *  Created :  02.05.2014 13:24:35
 *
 *  Description :  Utilities such as string operation functions.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#ifndef __UTILITIES_H__
#define __UTILITIES_H__

/******************************************************************************/
/* include files                                                              */
/******************************************************************************/

#include "xfs_types.h"
#include <stdio.h>
#include <stdlib.h>
//#include "xil_io.h"

#ifdef LINUX_COMPILE
#include <unistd.h>
#else
//#include "xtime.h"
#endif
/******************************************************************************/
/* definitions                                                                */
/******************************************************************************/

#define XFS_SUCCESS          0L
#define XFS_FAILURE          1L

#define XFS_TRUE             1
#define XFS_FALSE            0


/******************************************************************************/
/* type definitions                                                           */
/******************************************************************************/

typedef  void (*void_func_type)(void) ;


/******************************************************************************/
/* macro definitions                                                          */
/******************************************************************************/

#define fcp(dst,src)  ncpy((char *)&dst,(char *)&src,sizeof(src))
#define fcmp(cp1,cp2) ncmp((char *)&cp1,(char *)&cp2,sizeof(cp2))
#define ncpy(dst,src,n)  ncpy_c((char *)(dst),(const char *)(src),(n))

#define btst(val,num) (((val)>>(num))&0x0001)

#define SYNCHRONIZE_IO   dsb
#define dsb(option) __asm__ __volatile__ ("dsb " #option : : : "memory")

/* #define fstrcmp(cp1,cp2) ncmp((char *)(cp1),(char *)(cp2),(sizeof(cp2)-1)) */

/******************************************************************************/
/* function prototypes                                                        */
/******************************************************************************/
int xfs_atoi(const char *str);
unsigned int xfs_atoui(const char *str);


void func_call(unsigned int func_addr);
void ncpy_c(char *cp1, const char *cp2, int len);
int  ncmp(const char *cp1, const char *cp2, int len);
int fstrpcmp(const char *cp1, const char *cp2);
int  fstrcmp(const char *cp1, const char *cp2);
int  fstricmp(const char *cp1, const char *cp2);
int  fstrcmpwc(const char *cp1, const char *cp2);
char *xfs_strchr(char * str, int character);
void print_fw_version(void);
void print_frame(unsigned char* fbuff, int len);
int parse_ip(const char *str, unsigned char *ip);
int parse_mac(const char *str, unsigned char *mac);
int parse_port(const char *str, unsigned int *port);
char *sprint_mac(char *str, unsigned char *mac);
char *sprint_ip(char *str, unsigned char *ip);
int hex_val(char c);
int hatoi(const char *str);
int is_num(char c);

unsigned int packed_bcd_to_dec(unsigned int pbcd);
unsigned int dec_to_packed_bcd(unsigned int dec);


#ifdef LINUX_COMPILE
xfs_u32 io_remap(xfs_u32 phys_address);
#else
#define io_remap(phys_address)  ((xfs_u32)(phys_address))
#endif


/******************************************************************************/
/* static inline functions                                                    */
/******************************************************************************/

static inline xfs_u8 xfs_in8(xfs_u32 InAddress)
{
    /* read the contents of the I/O location and then synchronize the I/O
     * such that the I/O operation completes before proceeding on
     */

    xfs_u8 IoContents;
    SYNCHRONIZE_IO();
    IoContents = (*(volatile xfs_u8 *)(InAddress));
    /*__asm__ volatile ("eieio; lbz %0,0(%1)":"=r" (IoContents):"b" */
    /*          (InAddress));                                       */
    return IoContents;
}

/******************************************************************************/

static inline xfs_u16 xfs_in16(xfs_u32 InAddress)
{
    /* read the contents of the I/O location and then synchronize the I/O
     * such that the I/O operation completes before proceeding on
     */

    xfs_u16 IoContents;
    SYNCHRONIZE_IO();
    IoContents = *((volatile xfs_u16 *)(InAddress));
    /*__asm__ volatile ("eieio; lhz %0,0(%1)":"=r" (IoContents):"b" */
    /*          (InAddress));                                       */
    return IoContents;
}

/******************************************************************************/

static inline xfs_u32 xfs_in32(xfs_u32 InAddress)
{
    /* read the contents of the I/O location and then synchronize the I/O
     * such that the I/O operation completes before proceeding on
     */

    xfs_u32 IoContents;
    SYNCHRONIZE_IO();
    IoContents = *((volatile xfs_u32 *)(InAddress));
    /*__asm__ volatile ("eieio; lwz %0,0(%1)":"=r" (IoContents):"b" */
    /*          (InAddress));                                       */
    return IoContents;
}

/******************************************************************************/

static inline void xfs_out8(xfs_u32 OutAddress, xfs_u8 Value)
{
    /* write the contents of the I/O location and then synchronize the I/O
     * such that the I/O operation completes before proceeding on
     */

    *((volatile xfs_u8 *)(OutAddress)) = Value;
    SYNCHRONIZE_IO();
    /*__asm__ volatile ("stb %0,0(%1); eieio"::"r" (Value), "b"(OutAddress)); */
}

/******************************************************************************/
static inline void xfs_out16(xfs_u32 OutAddress, xfs_u16 Value)
{
    /* write the contents of the I/O location and then synchronize the I/O
     * such that the I/O operation completes before proceeding on
     */

    *((volatile xfs_u16 *)(OutAddress)) = Value;
    SYNCHRONIZE_IO();
    /*__asm__ volatile ("sth %0,0(%1); eieio"::"r" (Value), "b"(OutAddress)); */
}

/******************************************************************************/

static inline void xfs_out32(xfs_u32 OutAddress, xfs_u32 Value)
{
    /* write the contents of the I/O location and then synchronize the I/O
     * such that the I/O operation completes before proceeding on
     */

    *((volatile xfs_u32 *)(OutAddress)) = Value;
    SYNCHRONIZE_IO();
    /*__asm__ volatile ("stw %0,0(%1); eieio"::"r" (Value), "b"(OutAddress)); */
}

/******************************************************************************/

#endif /* __UTILITIES_H__ */

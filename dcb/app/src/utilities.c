/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WaveDream2
 *
 *  Author  :  schmid_e, tg32
 *  Created :  02.05.2014 13:24:35
 *
 *  Description :  Utilities such as string operation functions.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

/******************************************************************************/
/* include files                                                              */
/******************************************************************************/

#include "utilities.h"
#include <ctype.h>

#include "xfs_printf.h"

#ifdef LINUX_COMPILE
#include <fcntl.h>
#include <sys/mman.h>

#define IO_REMAP_INFO 0
#endif  /* LINUX_COMPILE */

/******************************************************************************/
#ifdef LINUX_COMPILE
/******************************************************************************/

xfs_u32 io_remap(xfs_u32 phys_address)
{
  xfs_u32 virt_address;


  int fd = open("/dev/mem",O_RDWR|O_SYNC);
  if(fd < 0)
  {
    xfs_printf("Can't open /dev/mem\n");
    return 0;
  }

  virt_address = (xfs_u32) mmap(0, getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED, fd, phys_address);
  if(!virt_address)
  {
    xfs_printf("ERROR: Can't mmap phys_address 0x%08x\n",phys_address);
    return 0;
  }

#if IO_REMAP_INFO
  xfs_printf("remapped phys_address 0x%08x to 0x%08x\n",phys_address ,virt_address );
  xfs_printf("pagesize 0x%08x (%u)\n",getpagesize(), getpagesize());
#endif

  return virt_address;
}

/******************************************************************************/
#elif defined (FPGA_FC) // Frost CTRL
/******************************************************************************/

void func_call(unsigned int func_addr)
{
  unsigned volatile int dummy_read;
  void_func_type func = (void_func_type)func_addr;

  dummy_read += *(unsigned volatile int*) func;
  func();
}

/******************************************************************************/

#endif  /* LINUX_COMPILE */

/******************************************************************************/



int xfs_atoi(const char *str)
{
  if (str) return strtol(str, 0, 0);
  return 0;
}

/******************************************************************************/


int is_num(char c)
{
  return (c >= '0' &&  c<= '9');
}

/************************************************************/

unsigned int xfs_atoui(const char *str)
{
  if (str) return strtoul(str, 0, 0);
  return 0;
}
/******************************************************************************/

#if 0
const char* pad(int l)
{
  static const char pad_str[] = "                                        ";
  const int max_pad = (sizeof(pad_str)-1);

  if (l>max_pad) l = max_pad;
  if (l<0) l = 0;

  return pad_str+max_pad-l;
}
#endif

/******************************************************************************/

void ncpy_c(char *cp1, const char *cp2, int len)
{
 int i;
 for (i=0; i<len; i++)
 {
   cp1[i] = cp2[i];
 }
}

/******************************************************************************/

int ncmp(const char *cp1, const char *cp2, int len)
{
 int i;

 if (!cp1 | !cp2) return 0;

 for (i=0; i<len; i++)
 {
   if (cp1[i] != cp2[i]) return 0;
 }

 return 1;
}

/******************************************************************************/

/*  cp1 must match beginning part of cp2 */
int fstrpcmp(const char *cp1, const char *cp2)
{
  int i=0;

  if (!cp1 | !cp2) return 0;
  while(1)
  {
     if(cp1[i] == 0) return 1;
     if(cp1[i] != cp2[i]) return 0;
     i++;
  }
}

/******************************************************************************/

/*  cp1 must match cp2 completely */
int fstrcmp(const char *cp1, const char *cp2)
{
  int i=0;

  if (!cp1 | !cp2) return 0;

  while(1)
  {
     if(cp1[i] != cp2[i]) return 0;
     if(cp1[i] == 0) return 1;
     i++;
  }
}
/******************************************************************************/

int fstricmp(const char *cp1, const char *cp2)
{
  int i=0;

  if (!cp1 | !cp2) return 0;
  while(1)
  {
     if (tolower((int)(cp1[i])) != tolower((int)(cp2[i]))) return 0;
     if (cp1[i] == 0) return 1;
     i++;
  }
}
/******************************************************************************/

/* wildcard compare
 * NOTE:  first * matches rest of string, e.g.
 *        abc*   matched everything starting with abc
 * WARNING:
 *        *xys   matches everything, same as * alone !!!
 */

int fstrcmpwc(const char *cp1, const char *cp2)
{
  int i=0;

  if (!cp1 | !cp2) return 0;
  while(1)
  {
     if((cp1[i] == '*') || (cp2[i] == '*')) return 1;
     if(cp1[i] != cp2[i]) return 0;
     if(cp1[i] == 0) return 1;
     i++;
  }
}

/******************************************************************************/

char *xfs_strchr(char * str, int character)
{
  while(*str)
  {
    if(*str == character)
    {
      return str;
    }
    str++;
  }
  return 0;
}

/******************************************************************************/

void print_frame(unsigned char* fbuff, int len)
{
  int i;

  xfs_local_printf("\r\n----Frame of len : %d Byte\r\n", len);
  for (i=0; i<len; i++)
  {
    xfs_local_printf("%02x ",fbuff[i] );
    if ((i&0xf) == 0x7) xfs_local_printf(" ");
    if ((i&0xf) == 0xf) xfs_local_printf("\r\n");
  }
  xfs_local_printf("\r\n");
}

/******************************************************************************/

int hex_val(char c)
{
  if (c >= '0' &&  c <= '9')
  {
    return (c - '0');
  }
  else if (c >= 'a' &&  c <= 'f')
  {
    return (c - 'a' + 10);
  }
  else if (c >= 'A' &&  c <= 'F')
  {
    return (c - 'A' + 10);
  }
  else
  {
    return -1;
  }
}

/******************************************************************************/

int parse_ip(const char *str, unsigned char *ip)
{
  int i;
  int count = 0;
  const char *ip_str[4];

  if (!str) return -1;
  for (i=0; i<4; i++) ip[i]=0;

  ip_str[0] = str;
  while (*str && count <= 4)
  {
    if (*str == '.')
    {
/*      *str = 0; */
      if (++count < 4)
      {
        ip_str[count] = ++str;
      }
    }
    else if (*str>='0' &&  *str<='9')
    {
       ++str;
    }
    else
    {
      count = 999;
    }
  }

  if  (count == 3)
  {
    for (i=0; i<4; i++) ip[i] = xfs_atoi(ip_str[i]);
/*    xfs_printf("ip-address : %d.%d.%d.%d\r\n",ip[0],ip[1],ip[2],ip[3]); */
    return 0;
  }
  else
  {
    for (i=0; i<4; i++) ip[i] = 0;
/*    xfs_printf("Wrong ip-address format!\r\n"); */
    return -1;
  }
}

/******************************************************************************/

int parse_port(const char *str, unsigned int *port)
{
  if (!str) return -1;

  *port = (unsigned int)xfs_atoi(str);

  return 0;
}

/******************************************************************************/

int parse_mac(const char *str, unsigned char *mac)
{
  int i;
  int count = 0;
  const char *mac_str[6];

  if (!str) return -1;

  for (i=0; i<6; i++) mac[i]=0;

  mac_str[0] = str;
  while (*str && count <= 6)
  {
    if (*str == ':')
    {
      if (++count < 6)
      {
        mac_str[count] = ++str;
      }
    }
    else if (hex_val(*str)>=0)
    {
       str++;
    }
    else
    {
      count = 999;
    }
  }

  if  (count == 5)
  {
    for (i=0; i<6; i++)
    {
      mac[i] = hatoi(mac_str[i]);
    }

    return 0;
  }
  else
  {
 /*   if (DBG_ERR) xfs_printf("Wrong mac-address format : %s\r\n",str); */
    return -1;
  }
}

/******************************************************************************/

char *sprint_mac(char *str, unsigned char *mac)
{
  xfs_snprintf(str, 20, "%02x:%02x:%02x:%02x:%02x:%02x",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
  return str;
}

/******************************************************************************/

char *sprint_ip(char *str, unsigned char *ip)
{
  xfs_snprintf(str, 20, "%d.%d.%d.%d",ip[0],ip[1],ip[2],ip[3]);
  return str;
}

/******************************************************************************/

int hatoi(const char *str)
{
  int val = 0;
  int digit;

  while(*str && (*str != ':'))
  {
    digit = hex_val(*str++);
    if (digit<0) return 0;
    val = val*16 + digit;
  }
  return val;
}

/******************************************************************************/

unsigned int dec_to_packed_bcd(unsigned int dec)
{
  unsigned int pbcd = 0;
  unsigned int base = 0x01;

  while(dec > 0)
  {
    pbcd += base * (dec % 10);
    base <<= 4;
    dec  /= 10;
  }
  return pbcd;
}


/******************************************************************************/

unsigned int packed_bcd_to_dec(unsigned int pbcd)
{
  unsigned int dec  = 0;
  unsigned int base = 1;
  unsigned int digit;

  while(pbcd > 0)
  {
    digit = (pbcd % 16);
    if (digit > 9) digit = 9;
    dec  += base * digit;
    base *= 10;
    pbcd >>= 4;
  }
  return dec;
}

/******************************************************************************/

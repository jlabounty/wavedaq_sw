/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WaveDream2
 *
 *  Author  :  schmid_e, theidel
 *  Created :  31.07.2014 08:14:22
 *
 *  Description :  Debug level output control.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#ifndef __DBG_H__
#define __DBG_H__

/******************************************************************************/
/* definitions                                                                */
/******************************************************************************/

#define DBG_LEVEL_NONE     0
#define DBG_LEVEL_ERR      1
#define DBG_LEVEL_WARN     2
#define DBG_LEVEL_INIT     3
#define DBG_LEVEL_INF0     4
#define DBG_LEVEL_INF1     5
#define DBG_LEVEL_INF2     6
#define DBG_LEVEL_INF3     7
#define DBG_LEVEL_INF4     8
#define DBG_LEVEL_SPAM     9
#define DBG_LEVEL_ALL     10

#define DBG_LEVEL_MAX     DBG_LEVEL_ALL

/*
 *  NOTE:
 *  adjust dbg_level_str in dbg.c whenn changing debug levels 
 */
 
extern const char *dbg_level_str[];

/* Error Flags: */
#define ERR_UNKNOWN_CMD      0x01
#define ERR_INVALID_ARGS     0x02
#define ERR_TOO_FEW_ARGS     0x03
#define ERR_WD2_HV           0x10
#define ERR_WD2_PLL_CONFIG   0x11

#define DBG_LEVEL_DEFAULT  DBG_LEVEL_INFO

#define DBG_LEVEL_INFO  DBG_LEVEL_INF0
#define DBG_INFO        DBG_INF0

#define DBG_ERR   (global_dbg_level >= DBG_LEVEL_ERR )
#define DBG_WARN  (global_dbg_level >= DBG_LEVEL_WARN)
#define DBG_INIT  (global_dbg_level >= DBG_LEVEL_INIT)
#define DBG_INF0  (global_dbg_level >= DBG_LEVEL_INF0)
#define DBG_INF1  (global_dbg_level >= DBG_LEVEL_INF1)
#define DBG_INF2  (global_dbg_level >= DBG_LEVEL_INF2)
#define DBG_INF3  (global_dbg_level >= DBG_LEVEL_INF3)
#define DBG_INF4  (global_dbg_level >= DBG_LEVEL_INF4)
#define DBG_SPAM  (global_dbg_level >= DBG_LEVEL_SPAM)
#define DBG_ALL   (global_dbg_level >= DBG_LEVEL_ALL )



/******************************************************************************/
/* external global var                                                        */
/******************************************************************************/

extern unsigned int global_dbg_level;

/*
  -- use as follows
  if (DBG_ERR)  xfs_printf("Error in xxxx\r\n");
*/

/******************************************************************************/
/* function prototypes                                                        */
/******************************************************************************/

void set_error_flag(unsigned int error_flag);
void set_dbg_level(unsigned int dbg_level);
unsigned int get_dbg_level(void);
unsigned int parse_dbglvl(const char *str);

/******************************************************************************/

#endif /* __DBG_H__ */

/******************************************************************************/


/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WaveDream2
 *
 *  Author  :  schmid_e, theidel
 *  Created :  24.04.2014 11:53:05
 *
 *  Description :  Structure of table to list names of implemented commands that can be
 *                 interpreted plus a pointer to the function to be called by this
 *                 command.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#ifndef __WD2_CONFIG_H__
#define __WD2_CONFIG_H__

/******************************************************************************/
/* include files                                                              */
/******************************************************************************/

#include "cmd_processor.h"

/******************************************************************************/
/* definitions                                                                */
/******************************************************************************/

/* modules */
#define CFG_INCLUDE_HELP                1
#define CFG_INCLUDE_INFO                1
#define CFG_INCLUDE_DCB_REG_ACCESS      1
#define CFG_INCLUDE_FW_ENV              0
#define CFG_INCLUDE_SPI_FLASH           0
#define CFG_INCLUDE_GPIO_MIO            0
//#define CFG_INCLUDE_SPI_SYSLINK_TEST    0
//#define CFG_INCLUDE_TEMP                1
//#define CFG_INCLUDE_LMK                 1
#define CFG_INCLUDE_LED_CONTROL         0
//#define CFG_INCLUDE_EXT_MEMORY          0
#define CFG_INCLUDE_SYSTEM_MANAGEMENT   0
//#define CFG_INCLUDE_GMAC                1
#define CFG_INCLUDE_CRATE_COM           1

/******************************************************************************/

#endif /* __WD2_CONFIG_H__ */

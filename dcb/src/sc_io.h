/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  MEGII - DCB
 *
 *  Author  :  schmid_e (Author of generation script)
 *  Created :  03.05.2019 15:45:07
 *
 *  Description :  Slow Control IO under Linux.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#ifndef __SC_IO_H__
#define __SC_IO_H__

#include "sc_io_map.h"

void gpio_init();
void set_gpio(unsigned int pin, unsigned int value);
unsigned int get_gpio(unsigned int pin);
void emio_set_sw_state(unsigned int state);
void emio_clr_sw_state(unsigned int state);
void emio_flash_sw_state(unsigned int state);
void emio_reset_sw_state();

#endif /* __SC_IO_H__ */

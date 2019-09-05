/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  MEGII - DCB
 *
 *  Author  :  schmid_e (Author of generation script)
 *  Created :  03.05.2019 15:45:07
 *
 *  Description :  Slow Control IO definitions.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "sc_io.h"

#define NR_OF_MIOS        54
#define NR_OF_EMIOS       64
#define MIO_PIN_OFFSET     0
#define EMIO_PIN_OFFSET   54

#define NR_OF_SW_STATES    8

#define OUTPUT             0
#define INPUT              1

/* TBD: Offset is not necessarily constant. Find a way to check for the correct value. */
/*      Could be done by checking /sys/class/gpio/gpiochip906/label for "zynq_gpio" */
//#define ZYNQ_GPIO_OFFS   906
#define ZYNQ_GPIO_OFFS     0

/******************************************************************************/

void init_gpio_pin(unsigned int pin, unsigned int direction)
{
  int fd;
  int len;
  int gpio_nr;
  char data_str[50];

  gpio_nr = ZYNQ_GPIO_OFFS + pin;

  /* export gpio */
  fd = open("/sys/class/gpio/export", O_WRONLY);
  if (fd < 0)
  {
      printf("Cannot open GPIO to export for pin %d\n", pin);
      exit(1);
  }
  len = sprintf(data_str, "%d", gpio_nr);
  write(fd, data_str, len);
  close(fd);

  /* set direction */
  sprintf(data_str, "/sys/class/gpio/gpio%d/direction", gpio_nr);
  fd = open(data_str, O_RDWR);
  if (fd < 0)
  {
      printf("Cannot open GPIO direction for pin %d\n", pin);
      exit(1);
  }
  if(direction == INPUT) write(fd, "in",  3);
  else                   write(fd, "out", 4);
  close(fd);
}

/******************************************************************************/

void gpio_init()
{
  int i;

  init_gpio_pin(BIT_IDX_AXI_CTRL_MIO_LED_PIN, OUTPUT);

  for(i=0;i<NR_OF_EMIOS;i++)
  {
    if(i<32)
    {
      /* init control outputs */
      init_gpio_pin(EMIO_PIN_OFFSET+i, OUTPUT);
    }
    else
    {
      /* init status inputs */
      init_gpio_pin(EMIO_PIN_OFFSET+i, INPUT);
    }
  }
}

/******************************************************************************/

void set_gpio(unsigned int pin, unsigned int value)
{
  int fd;
  int gpio_nr;
  char data_str[50];

  gpio_nr = ZYNQ_GPIO_OFFS + pin;

  /* set value */
  sprintf(data_str, "/sys/class/gpio/gpio%d/value", gpio_nr);
  fd = open(data_str, O_RDWR);
  if (fd < 0)
  {
      printf("Cannot open GPIO value for pin %d\n", pin);
      exit(1);
  }
  if(value) write(fd, "1", 2);
  else      write(fd, "0", 2);
  close(fd);
}

/******************************************************************************/

unsigned int get_gpio(unsigned int pin)
{
  int fd;
  int gpio_nr;
  char data_str[50];
  char value;

  gpio_nr = ZYNQ_GPIO_OFFS + pin;

  /* set value */
  sprintf(data_str, "/sys/class/gpio/gpio%d/value", gpio_nr);
  fd = open(data_str, O_RDWR);
  if (fd < 0)
  {
      printf("Cannot open GPIO value for pin %d\n", pin);
      exit(1);
  }
  read(fd, &value, 1);
  close(fd);

  if(value=='0') return 0;
  else           return 1;
}

/******************************************************************************/

void emio_set_sw_state(unsigned int state)
{
  set_gpio(state, 1);
}

/******************************************************************************/

void emio_clr_sw_state(unsigned int state)
{
  set_gpio(state, 0);
}

/******************************************************************************/

void emio_flash_sw_state(unsigned int state)
{
  set_gpio(state, 1);
  set_gpio(state, 0);
}

/******************************************************************************/

void emio_reset_sw_state()
{
  int i;

  for(i=0;i<NR_OF_SW_STATES;i++)
  {
    set_gpio(SW_STATE_OFFSET + i, 0);
  }
}

/******************************************************************************/
/******************************************************************************/

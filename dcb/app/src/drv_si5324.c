/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WDAQ - DCB
 *
 *  Author  :  schmid_e
 *  Created :  22.11.2018 08:23:32
 *
 *  Description :  SPI driver for SI5324.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#include "drv_si5324.h"
#include "system.h"
//#include "dbg.h"

/******************************************************************************/

#define SI5324_NR_OF_CTRL_REGS   43
#define SI5324_NR_OF_STAT_REGS    5
#define SI5324_NR_OF_REGS          (SI5324_NR_OF_CTRL_REGS+SI5324_NR_OF_STAT_REGS)

#define SI5324_CMD_SET_ADDR    0x00
#define SI5324_CMD_WRITE       0x40
#define SI5324_CMD_WRITE_INC   0x60
#define SI5324_CMD_READ        0x80
#define SI5324_CMD_READ_INC    0x90

/******************************************************************************/

const si5324_reg_type si5324_reg_init[SI5324_NR_OF_CTRL_REGS] = {
  {  0, 0x54},  /* Register 0 */
  {  1, 0xE4},  /* Register 1 */
  {  2, 0x32},  /* Register 2 */
  {  3, 0x15},  /* Register 3 */
  {  4, 0x92},  /* Register 4 */
  {  5, 0xED},  /* Register 5 */
  {  6, 0x2D},  /* Register 6 */
  {  7, 0x2A},  /* Register 7 */
  {  8, 0x00},  /* Register 8 */
  {  9, 0xC0},  /* Register 9 */
  { 10, 0x08},  /* Register 10 */
  { 11, 0x40},  /* Register 11 */
  { 19, 0x29},  /* Register 19 */
  { 20, 0x3E},  /* Register 20 */
  { 21, 0xFF},  /* Register 21 */
  { 22, 0xDF},  /* Register 22 */
  { 23, 0x1F},  /* Register 23 */
  { 24, 0x3F},  /* Register 24 */
  { 25, 0x60},  /* Register 25 */
  { 31, 0x00},  /* Register 31 */
  { 32, 0x00},  /* Register 32 */
  { 33, 0x05},  /* Register 33 */
  { 34, 0x00},  /* Register 34 */
  { 35, 0x00},  /* Register 35 */
  { 36, 0x05},  /* Register 36 */
  { 40, 0xC2},  /* Register 40 */
  { 41, 0x22},  /* Register 41 */
  { 42, 0xDF},  /* Register 42 */
  { 43, 0x00},  /* Register 43 */
  { 44, 0x77},  /* Register 44 */
  { 45, 0x0B},  /* Register 45 */
  { 46, 0x00},  /* Register 46 */
  { 47, 0x77},  /* Register 47 */
  { 48, 0x0B},  /* Register 48 */
  { 55, 0x00},  /* Register 55 */
  {131, 0x1F},  /* Register 131 */
  {132, 0x02},  /* Register 132 */
  {136, 0x00},  /* Register 136 */
  {137, 0x01},  /* Register 137 */
  {138, 0x0F},  /* Register 138 */
  {139, 0xFF},  /* Register 139 */
  {142, 0x00},  /* Register 142 */
  {143, 0x00}   /* Register 143 */
};

/******************************************************************************/
/******************************************************************************/

#ifdef LINUX_COMPILE
void si5324_init(si5324_ctrl_type *self, unsigned char device_nr, unsigned char slave_nr)
{
  spi_ps_init((spi_ps_type*)self, device_nr, slave_nr, 0, 8, 1000000, 0);

  for(unsigned int i=0;i<SI5324_NR_OF_CTRL_REGS;i++)
  {
    si5324_write(self, si5324_reg_init[i].address, si5324_reg_init[i].data);
  }

  /* si5324_cal(self); */ /* Causes ETH to fail */
}
#else /* LINUX_COMPILE */
void si5324_init(si5324_ctrl_type *self, XSpiPs *spi_if_ptr_init, unsigned char slave_nr_init)
{
  self->spi_if_ptr = spi_if_ptr_init;
  self->slave_nr   = slave_nr_init;

  for(unsigned int i=0;i<SI5324_NR_OF_CTRL_REGS;i++)
  {
    si5324_write(self, si5324_reg_init[i].address, si5324_reg_init[i].data);
  }

  si5324_cal(self);
}
#endif /* LINUX_COMPILE */


/******************************************************************************/

void si5324_transfer(si5324_ctrl_type *self, char* tx_buf, char* rx_buf, unsigned int len)
{
#ifdef LINUX_COMPILE
  init_si5324();
#endif

  spi_ps_transfer((spi_ps_type*)self, tx_buf, rx_buf, len);
}

/******************************************************************************/

void si5324_write(si5324_ctrl_type *self, unsigned char addr, unsigned char tx_data)
{
  unsigned char tx_buffer[2];

  tx_buffer[0] = SI5324_CMD_SET_ADDR;
  tx_buffer[1] = addr;

  si5324_transfer(self, tx_buffer, NULL, 2);

  tx_buffer[0] = SI5324_CMD_WRITE;
  tx_buffer[1] = tx_data;

  si5324_transfer(self, tx_buffer, NULL, 2);
}

/******************************************************************************/

unsigned char si5324_read(si5324_ctrl_type *self, unsigned char addr)
{
  unsigned char tx_buffer[2];
  unsigned char rx_buffer[2];

  tx_buffer[0] = SI5324_CMD_SET_ADDR;
  tx_buffer[1] = addr;

  si5324_transfer(self, tx_buffer, NULL, 2);

  tx_buffer[0] = SI5324_CMD_READ;
  tx_buffer[1] = 0;

  si5324_transfer(self, tx_buffer, rx_buffer, 2);

  return rx_buffer[1];
}

/******************************************************************************/

void si5324_cal(si5324_ctrl_type *self)
{
  si5324_write(self, 136, 0x40);
}

/******************************************************************************/

void si5324_reset(si5324_ctrl_type *self)
{
  si5324_write(self, 136, 0x80);
}

/******************************************************************************/
/******************************************************************************/

/*-------------------------------------------------------------------------------------
 *  Paul Scherrer Institut
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WDAQ - DCB
 *
 *  Author  :  schmid_e
 *  Created :  09.05.2019 12:43:45
 *
 *  Description :  SPI functions for communication DCB<->Slots.
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#include "spi_bpl.h"
#include "system.h"
#include "sc_io.h"
#include "xfs_printf.h"
#include "xparameters.h"
#include "dbg.h"
#ifndef LINUX_COMPILE
#include "sleep.h"
#else
#include <unistd.h>
#include <assert.h>
#endif

/******************************************************************************/

#ifdef LINUX_COMPILE
#undef Xil_AssertNonvoid
#define Xil_AssertNonvoid   assert
#endif

/******************************************************************************/

const unsigned int spi_slave_select[18] = {0xFFFFFFFE,
                                           0xFFFFFFFD,
                                           0xFFFFFFFB,
                                           0xFFFFFFF7,
                                           0xFFFFFFEF,
                                           0xFFFFFFDF,
                                           0xFFFFFFBF,
                                           0xFFFFFF7F,
                                           0xFFFFFEFF,
                                           0xFFFFFDFF,
                                           0xFFFFFBFF,
                                           0xFFFFF7FF,
                                           0xFFFFEFFF,
                                           0xFFFFDFFF,
                                           0xFFFFBFFF,
                                           0xFFFF7FFF,
                                           0xFFFFFFFF, /* reserved (DCB slot) */
                                           0xFFFEFFFF};

/******************************************************************************/
/******************************************************************************/
unsigned int read_spi_reg(unsigned int offset)
{
  return XSpi_In32(XPAR_AXI_QUAD_SPI_TO_BPL_0_BASEADDR + offset);
}

void print_regs()
{
/* #define XSP_DGIER_OFFSET   0x1C   DGIER    Device Global Interrupt Enable Register */
/* #define XSP_IISR_OFFSET    0x20   IPISR    Interrupt Status Register */
/* #define XSP_IIER_OFFSET    0x28   IPIER    Interrupt Enable Register */
/* #define XSP_SRR_OFFSET     0x40   SRR      Software Reset Register */
/* #define XSP_CR_OFFSET      0x60   SPICR    SPI Control Register */
/* #define XSP_SR_OFFSET      0x64   SPISR    SPI Status Register */
/* #define XSP_DTR_OFFSET     0x68   SPIDTR   SPI Data Transmit Register */
/* #define XSP_DRR_OFFSET     0x6C   SPIDRR   SPI Data Receive Register */
/* #define XSP_SSR_OFFSET     0x70   SPISSR   SPI Slave Select Register */
/* #define XSP_TFO_OFFSET     0x74   TFOCY    SPI Transmit FIFO Occupancy Register */
/* #define XSP_RFO_OFFSET     0x78   RFOCY    SPI Receive FIFO Occupancy Register */

  xfs_printf("SRR      0x%08X\r\n", read_spi_reg(0x40));
  xfs_printf("SPICR    0x%08X\r\n", read_spi_reg(0x60));
  xfs_printf("SPISR    0x%08X\r\n", read_spi_reg(0x64));
//  xfs_printf("SPIDTR   0x%08X\r\n", read_spi_reg(0x68));
//  xfs_printf("SPIDRR   0x%08X\r\n", read_spi_reg(0x6C));
  xfs_printf("SPISSR   0x%08X\r\n", read_spi_reg(0x70));
  xfs_printf("TFOCY    0x%08X\r\n", read_spi_reg(0x74));
  xfs_printf("RFOCY    0x%08X\r\n", read_spi_reg(0x78));
  xfs_printf("IPIER    0x%08X\r\n", read_spi_reg(0x28));
  xfs_printf("DGIER    0x%08X\r\n", read_spi_reg(0x1C));
  xfs_printf("IPISR    0x%08X\r\n", read_spi_reg(0x20));
}

/******************************************************************************/

int spi_transfer(XSpi *InstancePtr, u8 *SendBufPtr, u8 *RecvBufPtr, unsigned int ByteCount)
{
  u32 ControlReg;
  u32 GlobalIntrReg;
  u32 StatusReg;
  u32 Data = 0;
  u8  DataWidth;

  /*
   * The RecvBufPtr argument can be NULL.
   */
  Xil_AssertNonvoid(InstancePtr != NULL);
  Xil_AssertNonvoid(SendBufPtr != NULL);
  Xil_AssertNonvoid(ByteCount > 0);
  Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
//  if( (InstancePtr == NULL) || (SendBufPtr == NULL) || (ByteCount <= 0) || (InstancePtr->IsReady != XIL_COMPONENT_IS_READY) )
//  {
//    return -1;
//  }

  if (InstancePtr->IsStarted != XIL_COMPONENT_IS_STARTED)
  {
    return XST_DEVICE_IS_STOPPED;
  }

  if (InstancePtr->IsBusy)
  {
    return XST_DEVICE_BUSY;
  }

  /*
   * Save the Global Interrupt Enable Register.
   */
  GlobalIntrReg = XSpi_IsIntrGlobalEnabled(InstancePtr);

  /*
   * Enter a critical section from here to the end of the function since
   * state is modified, an interrupt is enabled, and the control register
   * is modified (r/m/w).
   */
  XSpi_IntrGlobalDisable(InstancePtr);

  ControlReg = XSpi_GetControlReg(InstancePtr);

  /*
   * If configured as a master, be sure there is a slave select bit set
   * in the slave select register. If no slaves have been selected, the
   * value of the register will equal the mask.  When the device is in
   * loopback mode, however, no slave selects need be set.
   */
  if (ControlReg & XSP_CR_MASTER_MODE_MASK)
  {
    if ((ControlReg & XSP_CR_LOOPBACK_MASK) == 0)
    {
      if ( ( !(ControlReg & XSP_CR_MANUAL_SS_MASK) && (InstancePtr->SlaveSelectReg == InstancePtr->SlaveSelectMask) ) ||
           (  (ControlReg & XSP_CR_MANUAL_SS_MASK) && (XSpi_GetSlaveSelectReg(InstancePtr) == InstancePtr->SlaveSelectMask) ) )
      {
        if (GlobalIntrReg == TRUE)
        {
          /* Interrupt Mode of operation */
          XSpi_IntrGlobalEnable(InstancePtr);
        }
        return XST_SPI_NO_SLAVE;
      }
    }
  }

  /*
   * Set the busy flag, which will be cleared when the transfer
   * is completely done.
   */
  InstancePtr->IsBusy = TRUE;

  /*
   * Set up buffer pointers.
   */
  InstancePtr->SendBufferPtr = SendBufPtr;
  InstancePtr->RecvBufferPtr = RecvBufPtr;

  InstancePtr->RequestedBytes = ByteCount;
  InstancePtr->RemainingBytes = ByteCount;

  DataWidth = InstancePtr->DataWidth;

  /*
   * Fill the DTR/FIFO with as many bytes as it will take (or as many as
   * we have to send). We use the tx full status bit to know if the device
   * can take more data. By doing this, the driver does not need to know
   * the size of the FIFO or that there even is a FIFO. The downside is
   * that the status register must be read each loop iteration.
   */
  StatusReg = XSpi_GetStatusReg(InstancePtr);

  while (((StatusReg & XSP_SR_TX_FULL_MASK) == 0) && (InstancePtr->RemainingBytes > 0))
  {
    if (DataWidth == XSP_DATAWIDTH_BYTE)
    {
      /* Data Transfer Width is Byte (8 bit). */
      Data = *InstancePtr->SendBufferPtr;
    }
    else if (DataWidth == XSP_DATAWIDTH_HALF_WORD)
    {
      /* Data Transfer Width is Half Word (16 bit). */
      Data = *(u16 *)InstancePtr->SendBufferPtr;
    }
    else if (DataWidth == XSP_DATAWIDTH_WORD)
    {
      /* Data Transfer Width is Word (32 bit). */
      Data = *(u32 *)InstancePtr->SendBufferPtr;
    }

    XSpi_WriteReg(InstancePtr->BaseAddr, XSP_DTR_OFFSET, Data);
    InstancePtr->SendBufferPtr += (DataWidth >> 3);
    InstancePtr->RemainingBytes -= (DataWidth >> 3);
    StatusReg = XSpi_GetStatusReg(InstancePtr);
  }


  /*
   * Set the slave select register to select the device on the SPI before
   * starting the transfer of data.
   */
    if(!(ControlReg & XSP_CR_MANUAL_SS_MASK))
  {
    XSpi_SetSlaveSelectReg(InstancePtr, InstancePtr->SlaveSelectReg);
  }

  /*
   * Start the transfer by no longer inhibiting the transmitter and
   * enabling the device. For a master, this will in fact start the
   * transfer, but for a slave it only prepares the device for a transfer
   * that must be initiated by a master.
   */
  ControlReg = XSpi_GetControlReg(InstancePtr);
  ControlReg &= ~XSP_CR_TRANS_INHIBIT_MASK;
  XSpi_SetControlReg(InstancePtr, ControlReg);

  /*
   * If the interrupts are enabled as indicated by Global Interrupt
   * Enable Register, then enable the transmit empty interrupt to operate
   * in Interrupt mode of operation.
   */
  if (GlobalIntrReg == TRUE) /* Interrupt Mode of operation */
  {
    /*
     * Enable the transmit empty interrupt, which we use to
     * determine progress on the transmission.
     */
    XSpi_IntrEnable(InstancePtr, XSP_INTR_TX_EMPTY_MASK);

    /*
     * End critical section.
     */
    XSpi_IntrGlobalEnable(InstancePtr);

  }
  else /* Polled mode of operation */
  {
    /*
     * If interrupts are not enabled, poll the status register to
     * Transmit/Receive SPI data.
     */
    while(ByteCount > 0)
    {
      /*
       * Wait for the transfer to be done by polling the
       * Transmit empty status bit
       */
      do
      {
        StatusReg = XSpi_IntrGetStatus(InstancePtr);
      } while ((StatusReg & XSP_INTR_TX_EMPTY_MASK) == 0);
      XSpi_IntrClear(InstancePtr,XSP_INTR_TX_EMPTY_MASK);

      /*
       * A transmit has just completed. Process received data
       * and check for more data to transmit. Always inhibit
       * the transmitter while the transmit register/FIFO is
       * being filled, or make sure it is stopped if we're
       * done.
       */
      ControlReg = XSpi_GetControlReg(InstancePtr);
      XSpi_SetControlReg(InstancePtr, ControlReg | XSP_CR_TRANS_INHIBIT_MASK);

      /*
       * First get the data received as a result of the
       * transmit that just completed. We get all the data
       * available by reading the status register to determine
       * when the Receive register/FIFO is empty. Always get
       * the received data, but only fill the receive
       * buffer if it points to something (the upper layer
       * software may not care to receive data).
       */
      StatusReg = XSpi_GetStatusReg(InstancePtr);

      while ((StatusReg & XSP_SR_RX_EMPTY_MASK) == 0)
      {
        Data = XSpi_ReadReg(InstancePtr->BaseAddr,
                XSP_DRR_OFFSET);
        if (DataWidth == XSP_DATAWIDTH_BYTE)
        {
          /* Data Transfer Width is Byte (8 bit). */
          if(InstancePtr->RecvBufferPtr != NULL)
          {
            *InstancePtr->RecvBufferPtr++ = (u8)Data;
          }
        }
        else if (DataWidth == XSP_DATAWIDTH_HALF_WORD)
        {
          /* Data Transfer Width is Half Word (16 bit). */
          if (InstancePtr->RecvBufferPtr != NULL)
          {
            *(u16 *)InstancePtr->RecvBufferPtr = (u16)Data;
            InstancePtr->RecvBufferPtr += 2;
          }
        }
        else if (DataWidth == XSP_DATAWIDTH_WORD)
        {
          /* Data Transfer Width is Word (32 bit). */
          if (InstancePtr->RecvBufferPtr != NULL)
          {
            *(u32 *)InstancePtr->RecvBufferPtr = Data;
            InstancePtr->RecvBufferPtr += 4;
          }
        }
        InstancePtr->Stats.BytesTransferred += (DataWidth >> 3);
        ByteCount -= (DataWidth >> 3);
        StatusReg = XSpi_GetStatusReg(InstancePtr);
      }

      if (InstancePtr->RemainingBytes > 0)
      {
        /*
         * Fill the DTR/FIFO with as many bytes as it
         * will take (or as many as we have to send).
         * We use the Tx full status bit to know if the
         * device can take more data.
         * By doing this, the driver does not need to
         * know the size of the FIFO or that there even
         * is a FIFO.
         * The downside is that the status must be read
         * each loop iteration.
         */
        StatusReg = XSpi_GetStatusReg(InstancePtr);

        while(((StatusReg & XSP_SR_TX_FULL_MASK)== 0) && (InstancePtr->RemainingBytes > 0))
        {
          if (DataWidth == XSP_DATAWIDTH_BYTE)
          {
            /* Data Transfer Width is Byte (8 bit). */
            Data = *InstancePtr-> SendBufferPtr;
          }
          else if (DataWidth == XSP_DATAWIDTH_HALF_WORD)
          {
            /* Data Transfer Width is Half Word (16 bit). */
            Data = *(u16 *)InstancePtr-> SendBufferPtr;
          }
          else if (DataWidth == XSP_DATAWIDTH_WORD)
          {
            /* Data Transfer Width is Word (32 bit). */
            Data = *(u32 *)InstancePtr-> SendBufferPtr;
          }
          XSpi_WriteReg(InstancePtr->BaseAddr, XSP_DTR_OFFSET, Data);
          InstancePtr->SendBufferPtr += (DataWidth >> 3);
          InstancePtr->RemainingBytes -= (DataWidth >> 3);
          StatusReg = XSpi_GetStatusReg(InstancePtr);
        }

        /*
         * Start the transfer by not inhibiting the
         * transmitter any longer.
         */
        ControlReg = XSpi_GetControlReg(InstancePtr);
        ControlReg &= ~XSP_CR_TRANS_INHIBIT_MASK;
        XSpi_SetControlReg(InstancePtr, ControlReg);
      }
    }

    /*
     * Stop the transfer (hold off automatic sending) by inhibiting
     * the transmitter.
     */
    ControlReg = XSpi_GetControlReg(InstancePtr);
    XSpi_SetControlReg(InstancePtr, ControlReg | XSP_CR_TRANS_INHIBIT_MASK);

    /*
     * Select the slave on the SPI bus when the transfer is
     * complete, this is necessary for some SPI devices,
     * such as serial EEPROMs work correctly as chip enable
     * may be connected to slave select
     */
    if(!(ControlReg & XSP_CR_MANUAL_SS_MASK))
    {
      XSpi_SetSlaveSelectReg(InstancePtr, InstancePtr->SlaveSelectMask);
    }
    InstancePtr->IsBusy = FALSE;
  }

  return XST_SUCCESS;
}

/******************************************************************************/

void spi_ascii_cmd(char* buff, unsigned char slot_nr)
{
  unsigned char txc;
  unsigned char rxc;
  int count = 0;
  int Status;

  if (!buff) return;
  if (slot_nr > 17) return;

#ifdef LINUX_COMPILE
  init_spi_bpl();
#endif

  // count bytes to send...
  while ( (buff[count]!=0x00) && (buff[count]!=0x0a) && (buff[count]!=0x0d) ) count++;

  XSpi_SetSlaveSelectReg(SYSPTR(spi_bpl), spi_slave_select[slot_nr]);

  /* Send Start of Text */
  txc = 0x02;
  Status = spi_transfer(SYSPTR(spi_bpl), &txc, NULL, 1);
  if (Status != XST_SUCCESS)
  {
    if(DBG_ERR) xfs_printf("SPI Backplane Error: transmission error SOT\r\n");
  }

  /* Send Command */
  Status = spi_transfer(SYSPTR(spi_bpl), (unsigned char*)buff, NULL, count);
  if (Status != XST_SUCCESS)
  {
    if(DBG_ERR) xfs_printf("SPI Backplane Error: transmission error buffer\r\n");
  }

  /* Send End of Line */
  txc = 0x0D;
  Status = spi_transfer(SYSPTR(spi_bpl), &txc, NULL, 1);
  if (Status != XST_SUCCESS)
  {
    if(DBG_ERR) xfs_printf("SPI Backplane Error: transmission error EOL\r\n");
  }

  txc = 0x00;
  count = 0;
  do
  {
    Status = spi_transfer(SYSPTR(spi_bpl), &txc, &rxc, 1);
    if (Status != XST_SUCCESS)
    {
      if(DBG_ERR) xfs_printf("SPI Backplane Error: receive error in loop\r\n");
    }
    //xfs_printf("wd rx %03d\r\n",rxc);
    usleep(100);
    if (rxc>= 10) xfs_printf("%c",rxc);
  } while ((rxc != 0x03) && (++count < 10000));

  XSpi_SetSlaveSelectReg(SYSPTR(spi_bpl), 0xFFFFFFFF);
}

/******************************************************************************/

void spi_binary_cmd(char* tx_buff, char* rx_buff, unsigned char slot_nr, unsigned int len)
{
  int Status;

  if (!tx_buff) return;
  if (len==0) return;
  if (slot_nr > 17) return;

#ifdef LINUX_COMPILE
  init_spi_bpl();
#endif

  XSpi_SetSlaveSelectReg(SYSPTR(spi_bpl), spi_slave_select[slot_nr]);

  /* Send Command */
  Status = spi_transfer(SYSPTR(spi_bpl), (unsigned char*)tx_buff, (unsigned char*)rx_buff, len);
  if (Status != XST_SUCCESS)
  {
    if(DBG_ERR) xfs_printf("SPI Backplane Error: transmission error buffer\r\n");
  }

  XSpi_SetSlaveSelectReg(SYSPTR(spi_bpl), 0xFFFFFFFF);
}

/******************************************************************************/

void spi_flash_id_cmd(unsigned char slot_nr)
{
  unsigned char tx_buf[4] = {0x9F, 0x00, 0x00, 0x00};
  unsigned char rx_buf[4] = {0x00, 0x00, 0x00, 0x00};
  int Status;

#ifdef LINUX_COMPILE
  init_spi_bpl();
#endif

  if (slot_nr > 17) return;

  set_gpio(BIT_IDX_EMIO_CTRL_FLASH_SEL_PIN, 1);
  //emio_set_pin(SYSPTR(gpio_mio), BIT_IDX_EMIO_CTRL_INIT_PIN, 1);
  usleep(1000);
  XSpi_SetSlaveSelectReg(SYSPTR(spi_bpl), spi_slave_select[slot_nr]);
//  XSpi_SetSlaveSelect(SYSPTR(spi_bpl), ~spi_slave_select[slot_nr]);
  Status = spi_transfer(SYSPTR(spi_bpl), tx_buf, rx_buf, 4);
  if (Status != XST_SUCCESS)
  {
    if(DBG_ERR) xfs_printf("Read Flash ID Error\r\n");
  }
  usleep(1000);
  XSpi_SetSlaveSelectReg(SYSPTR(spi_bpl), 0xFFFFFFFF);
  set_gpio(BIT_IDX_EMIO_CTRL_FLASH_SEL_PIN, 0);
  //emio_set_pin(SYSPTR(gpio_mio), BIT_IDX_EMIO_CTRL_INIT_PIN, 0);
  xfs_printf("Flash ID (0x%02X) 0x%02X 0x%02X 0x%02X\r\n", rx_buf[0], rx_buf[1], rx_buf[2], rx_buf[3]);
}

/******************************************************************************/
/******************************************************************************/

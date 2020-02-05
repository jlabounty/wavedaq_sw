/*-------------------------------------------------------------------------------------
 *  Infn Pisa
 *-------------------------------------------------------------------------------------
 *
 *  Project :  WDAQ - DCB
 *
 *  Author  :  francesconi_m 
 *  Created :  04.02.2020 16:36:00
 *
 *  Description : simple interface to TCB buffers
 *
 *-------------------------------------------------------------------------------------
 *-------------------------------------------------------------------------------------
 */

#ifndef __DRV_TCB__
#define __DRV_TCB__

#include "wdaq_board_id.h"

#define EOE 1
#define SOE 2
#define EOT 4
#define SOT 8

//typedefs
#pragma pack(1) // byte-level alignement

typedef struct {
      unsigned int nBanks;
      unsigned int eventCounter;
      unsigned int totalTime;
      unsigned int triggerType;
      unsigned int triggerCounter;
} TcbSpiBufferHeader;

typedef struct {
   char name[4];
   unsigned int size;
} TcbSpiBankHeader;

typedef struct {
   unsigned char  protocol_version;
   unsigned char  board_type_revision;
   unsigned short reserved1;
   unsigned short serial_number;
   unsigned char  crate_id;
   unsigned char  slot_id;
   unsigned short packet_number;
   unsigned char  data_type;
   unsigned char  wdaq_flags;
   unsigned short payload_length;
   unsigned short data_chunk_offset;
} WdaqUdpPacketHeader;

typedef struct {
   char           bank_name[4];
   unsigned int   time_stamp;
   unsigned int   event_number;
   unsigned char  trigger_information[8];
   unsigned short temperature;
   unsigned short reserved;
} TcbUdpPacketHeader;

//register I/O through SPI
unsigned int readReg(int slot, WDAQ_BRD *board, unsigned int addr);
void readBlock(int slot, WDAQ_BRD* board, unsigned int addr, unsigned short size, unsigned int *data);
void writeReg(int slot, WDAQ_BRD *board, unsigned int addr, unsigned int val);

//packet sender
void sendPacket(unsigned int pkgnum, unsigned int npkg, TcbSpiBufferHeader* bufferhead, TcbSpiBankHeader* bankhead, unsigned int *data);

//high level interface funcitons
void setTcbDataDestination(char *ip_address, int port);
int hasData(int slot, WDAQ_BRD *board);
void processData(int slot, WDAQ_BRD *board);

#endif /* __DRV_TCB__ */

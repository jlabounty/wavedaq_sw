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

#define WDAQ_UDP_PROTOCOL_VERSION 8

#define EOE 1
#define SOE 2
#define EOT 4
#define SOT 8

#define DATA_TYPE_DUMMY 5
#define DATA_TYPE_TCB 8

#define MAXWORDSINPACKET 200

//typedefs
#pragma pack(push, 1) // byte-level alignment

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
   unsigned short serial_number;
   unsigned char  crate_id;
   unsigned char  slot_id;
   unsigned short packet_number;
   unsigned char  data_type;
   unsigned char  wdaq_flags;
   unsigned short trigger_information1;
   unsigned int   trigger_information0;
   unsigned int   event_number;
   unsigned short payload_length;
   unsigned short data_chunk_offset;
} WdaqUdpPacketHeader;

typedef struct {
   char           bank_name[4];
   unsigned int   time_stamp;
   unsigned short temperature;
   char           reserved[6];
} TcbUdpPacketHeader;

#pragma pack(pop) // restore original alignment

//register I/O through SPI
unsigned int readReg(int slot, WDAQ_BRD *board, unsigned int addr);
void readBlock(int slot, WDAQ_BRD* board, unsigned int addr, unsigned short size, unsigned int *data, int correctEndianness);//correctEndianness must be 1 to use data on ARM
void writeReg(int slot, WDAQ_BRD *board, unsigned int addr, unsigned int val);

//packet sender
void sendPacket(unsigned int slot, unsigned int* pkgnum, unsigned int ibank, unsigned int nbank, TcbSpiBufferHeader* bufferhead, TcbSpiBankHeader* bankhead, unsigned int *data);

//endianess correction before sending
void correctEndianness(WdaqUdpPacketHeader* wdaqheader, TcbUdpPacketHeader* tcbheader);

//high level interface funcitons
void setTcbDataDestination(char *ip_address, int port);//use negative port to invalid destination
int hasTcbDataDestination();
int hasData(int slot, WDAQ_BRD *board);
void processData(int slot, WDAQ_BRD *board);

#endif /* __DRV_TCB__ */

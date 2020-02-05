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

#include "drv_tcb.h"
#include "drv_bpl.h"
#include "register_map_dcb.h"

#include <string.h>
#include <stdio.h>
#include <byteswap.h>
#include <stdlib.h>
#include <errno.h>

#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/uio.h>

#define BUFFERBASE         0x02000000 //Buffer base address
#define BUFFERSIZE         8192
#define BUFFERSTATE        BUFFERBASE+BUFFERSIZE

//global destination address
struct sockaddr_in tcb_destination_addr;
int tcb_destination_valid = 0;

/******************************************************************************/
/******************************************************************************/

unsigned int readReg(int slot, WDAQ_BRD* board, unsigned int addr){
   char buffer[10];
   char rbuffer[10];

   //READ32
   buffer[0] = 0x24;
   //correct address endianess
   *(unsigned int*)(buffer+1) = bswap_32(addr);
   //byte 5 is dummy
   //buffer[5] = 0;
   
   spi_binary_cmd(buffer, rbuffer, 1 + 4 + 1 + 4, slot, board->type_id, board->rev_id);

   //results start from byte 6
   unsigned int* outptr = (unsigned int*)(rbuffer + 6);

   //correct endianess
   return bswap_32(*outptr);
   
}

/******************************************************************************/

void readBlock(int slot, WDAQ_BRD* board, unsigned int addr, unsigned short size, unsigned int *data){
   char* txbuffer = (char*)malloc(sizeof(unsigned int)*size + sizeof(char)*6);
   char* rxbuffer = (char*)malloc(sizeof(unsigned int)*size + sizeof(char)*6);

   //READ32
   txbuffer[0] = 0x24;
   //correct address endianess
   *(unsigned int*)(txbuffer+1) = bswap_32(addr);
   //byte 5 is dummy
   //txbuffer[5] = 0;
   
   spi_binary_cmd(txbuffer, rxbuffer, 1 + 4 + 1 + size*sizeof(unsigned int), slot, board->type_id, board->rev_id);

   //results start from byte 6
   unsigned int* outptr = (unsigned int*)(rxbuffer + 6);

   //correct endianess
   for(int i=0; i<size; i++){
      data[i] = bswap_32(outptr[i]);
   }

   free(txbuffer);
   free(rxbuffer);
}

/******************************************************************************/

void writeReg(int slot, WDAQ_BRD* board, unsigned int addr, unsigned int val){
   char buffer[9];
   char rbuffer[9];

   //WRITE32
   buffer[0] = 0x14;
   //correct address endianess
   *(unsigned int*)(buffer+1) = bswap_32(addr);
   //correct value endianess
   *(unsigned int*)(buffer+5) = bswap_32(val);
   
   spi_binary_cmd(buffer, rbuffer, 1 + 4 + 4, slot, board->type_id, board->rev_id);
   
}

/******************************************************************************/

int hasData(int slot, WDAQ_BRD* board){
   unsigned int val = readReg(slot, board, BUFFERSTATE);

   if(val>>16!=0){
      return 1;
   } else {
      return 0;
   }
}


/******************************************************************************/

void processData(int slot, WDAQ_BRD* board){
   TcbSpiBufferHeader headerdata;

   readBlock(slot, board, BUFFERBASE, 5, (unsigned int*)&headerdata);

   //printf("processing data from TCB of slot %d: %08lx\n", slot, headerdata.nBanks);

   unsigned int address = BUFFERBASE + 5;
   unsigned int pkgnum = 0;
   for(unsigned int iBank=0; iBank < headerdata.nBanks; iBank++){
      TcbSpiBankHeader bankhead;

      readBlock(slot, board, address, 2, (unsigned int*)&bankhead);
      //printf("Got bank %c%c%c%c size %08lx\n", bankhead.name[3], bankhead.name[2], bankhead.name[1], bankhead.name[0], bankhead.size);
      unsigned int data = 0xA5A5A5A5;

      sendPacket(pkgnum, headerdata.nBanks, &headerdata, &bankhead, &data);

      pkgnum++;
      address += bankhead.size+2;
   }

   //sends dummy packet if no data was sent
   if(pkgnum == 0){
      sendPacket(0, 1, &headerdata, 0, 0);
   }

   //done, move to next buffer
   writeReg(slot, board, BUFFERSTATE, 0x1);
}

/******************************************************************************/

void sendPacket(unsigned int pkgnum, unsigned int npkg, TcbSpiBufferHeader* bufferhead, TcbSpiBankHeader* bankhead, unsigned int* data){
   if(tcb_destination_valid==0){
      printf("cannot send TCB data: destination not configured! send a cfgdst command!\n");
      return;
   }

   //open socket
   int fd=socket(AF_INET,SOCK_DGRAM,0);
   if (fd==-1) {
      printf("cannot open socket for TCB data: %s\n",strerror(errno));
      return;
   }

   //get crate and slot id
   unsigned int loc;
   reg_bank_read(DCB_REG_DCB_LOC, &loc, 1);
   unsigned int crate_id = (loc & DCB_CRATE_ID_MASK) >> DCB_CRATE_ID_OFS;
   unsigned int slot_id = (loc & DCB_SLOT_ID_MASK) >> DCB_SLOT_ID_OFS;

   //allocate packet header
   WdaqUdpPacketHeader udpwdaqhead;

   udpwdaqhead.board_type_revision = 1<<4; //TCB board
   udpwdaqhead.serial_number = (crate_id << 8) | slot_id; //unique board identifier
   udpwdaqhead.crate_id = crate_id;
   udpwdaqhead.slot_id = slot_id;
   udpwdaqhead.packet_number = pkgnum;
   udpwdaqhead.data_chunk_offset = 0;
   udpwdaqhead.payload_length = 0;
   udpwdaqhead.wdaq_flags = EOT | SOT;
   if(pkgnum == 0) udpwdaqhead.wdaq_flags |= SOE; // begin of event
   else if(pkgnum == (npkg-1)) udpwdaqhead.wdaq_flags |= EOE; //end of event

   //prepare message structure
   struct iovec iov[3];
   struct msghdr message;
   message.msg_name=&tcb_destination_addr; //address
   message.msg_namelen=sizeof(tcb_destination_addr);
   message.msg_iov=iov; // vector for scatter-getter
   message.msg_control=0;
   message.msg_controllen=0;

   //additional stuff
   TcbUdpPacketHeader udptcbhead;

   //check if tcb bank is given
   if(bankhead!=0){
      udpwdaqhead.payload_length = bankhead->size * 4;

      //TCB Packet header TODO: swap with dummy if no banks
      for(int i=0; i<4; i++) udptcbhead.bank_name[i] = bankhead->name[i];
      udptcbhead.time_stamp = bufferhead->totalTime;
      udptcbhead.event_number = bufferhead->eventCounter;
      *(unsigned int*) udptcbhead.trigger_information = bufferhead->triggerCounter; 
      *(unsigned int*)(udptcbhead.trigger_information+4) = bufferhead->triggerType;
      //udptcbhead.temperature = 0;
      //udptcbhead.reserved = 0;

      //prepare scatter-gather
      iov[0].iov_base = &udpwdaqhead;
      iov[0].iov_len = sizeof(WdaqUdpPacketHeader);
      iov[1].iov_base = &udptcbhead;
      iov[1].iov_len = sizeof(TcbUdpPacketHeader);
      iov[2].iov_base = data;
      iov[2].iov_len = sizeof(unsigned int);
      message.msg_iovlen=3;

   } else {
      //no bank given: prepare DUMMY packet
      iov[0].iov_base = &udpwdaqhead;
      iov[0].iov_len = sizeof(WdaqUdpPacketHeader);
      message.msg_iovlen=1;
   }

   //send
   if (sendmsg(fd,&message,0)==-1) {
      printf("error sending TCB data: %s\n",strerror(errno));
   }

   close(fd);

}

/******************************************************************************/

void setTcbDataDestination(char *ip_address, int port){
   
   //prepare address
   memset(&tcb_destination_addr, 0, sizeof(tcb_destination_addr));
   tcb_destination_addr.sin_family = AF_INET;
   tcb_destination_addr.sin_port = htons(port);
   inet_aton(ip_address, &tcb_destination_addr.sin_addr);

   //flags it as valid
   tcb_destination_valid = 1;

}

/******************************************************************************/
/******************************************************************************/

/*--------------------------------------------------------------

  File    : wddump.cpp
  Created : July 8th, 2015 Stefan Ritt
 
  Simple dump program to write data received from WD2 board to
  text file.
 
--------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <assert.h>

#define WD2_PORT 2000

#pragma pack(1) // byte-level alignement for frame header

typedef struct {
   unsigned char  protocol_version;
   unsigned char  board_version;
   unsigned short board_id;
   unsigned char  crate_id;
   unsigned char  slot_id;
   unsigned char  adc_and_channel_info;
   unsigned char  segment_and_package_type;
   unsigned int   event_number;
   unsigned short sampling_frequency;
   unsigned short payload_length;
   unsigned short trigger_number;
   unsigned short drs0_trigger_cell;
   unsigned short drs1_trigger_cell;
   unsigned short trigger_type;
   unsigned short temperature;
   unsigned int   reserved;
   unsigned short packet_sequence_number;
} WD2_FRAME_HEADER;

/* Byte and Word swapping big endian <-> little endian */
#define SWAP_UINT16(x) (((x) >> 8) | ((x) << 8))
#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))

int main()
{
   int s, i, n, status, n_packet;
   unsigned char buffer[1800];
   fd_set readfds;
   struct sockaddr_in addr, rem_addr;
   struct timeval timeout;
   WD2_FRAME_HEADER *ph;
   unsigned char *pd;
   short data[512];
   socklen_t len;
   
#ifdef _MSC_VER
   {
   WSADATA WSAData;
   
   // Start windows sockets
   if (WSAStartup(MAKEWORD(1, 1), &WSAData) != 0)
      return -1;
   }
#endif

   // create UDB socket
   s = socket(AF_INET, SOCK_DGRAM, 0);
   assert(s);
   
   // bind socket to port WD2_PORT
   memset((char*)&addr, 0, sizeof(addr));
   addr.sin_family = AF_INET;
   addr.sin_port = htons(WD2_PORT);
   addr.sin_addr.s_addr = htonl(INADDR_ANY);
   if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
      perror("bind");
      return 1;
   }

   printf("Waiting for packets ...\n");
   n_packet = 0;
   
   printf("Source IP:Port          Frame   ADC/Ch/Segment\n\r");
   do {

      FD_ZERO(&readfds);
      FD_SET(s, &readfds);
      
      timeout.tv_sec = 0;
      timeout.tv_usec = 100000;

      do {
         status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
      } while (status == -1);        // don't return if an alarm signal was cought
      
      if (FD_ISSET(s, &readfds)) {
         
         // packet is available, so receive it
         len = sizeof(rem_addr);
         n = (int)recvfrom(s, (char *)buffer, sizeof(buffer), 0, (struct sockaddr *)&rem_addr, (socklen_t *)&len);
         if (n > sizeof(WD2_FRAME_HEADER)) {
            ph = (WD2_FRAME_HEADER*)buffer;
            pd = (unsigned char*)(ph+1);
            
            // correct endianness of header data
            ph->board_id                 = SWAP_UINT16(ph->board_id);
            int header_adc               = (ph->adc_and_channel_info >> 4) & 0x0f;
            int header_channel           = (ph->adc_and_channel_info) & 0x0f;
            int channel_segment          = (ph->segment_and_package_type >> 4) & 0x0f;
            int package_type             = (ph->segment_and_package_type) & 0x0f;
            ph->event_number             = SWAP_UINT32(ph->event_number);
            ph->sampling_frequency       = SWAP_UINT16(ph->sampling_frequency);
            ph->payload_length           = SWAP_UINT16(ph->payload_length);
            ph->trigger_number           = SWAP_UINT16(ph->trigger_number);
            ph->drs0_trigger_cell        = SWAP_UINT16(ph->drs0_trigger_cell);
            ph->drs1_trigger_cell        = SWAP_UINT16(ph->drs1_trigger_cell);
            ph->trigger_type             = SWAP_UINT16(ph->trigger_type);
            ph->temperature              = SWAP_UINT16(ph->temperature);
            ph->packet_sequence_number   = SWAP_UINT16(ph->packet_sequence_number);
            
            unsigned int d               = SWAP_UINT32(*((unsigned int *)pd));
            
            printf("#%06d from %s:%d, event=%5d type=%d ADC/Chn/Segment=%d/%d/%d Tcell=%04d/%04d T=%1.1lf d=%d\n",
                   n_packet++,
                   inet_ntoa(rem_addr.sin_addr),
                   ntohs(rem_addr.sin_port),
                   ph->event_number,
                   package_type,
                   header_adc,
                   header_channel,
                   channel_segment,
                   ph->drs0_trigger_cell,
                   ph->drs1_trigger_cell,
                   ph->temperature*0.0625,
                   d);
            
            // decode waveform data
            for (i=0 ; i<512 ; i+=2) {
               data[i]   = ((pd[1] & 0x0F) << 8) | pd[0];
               if(data[i] >= 0x0800) {
                  // expand two's complement
                  data[i] -= 0x1000;
               }
               data[i+1] = ((unsigned short)pd[2] << 4) | (pd[1] >> 4);
               if(data[i+1] >= 0x0800) {
                  // expand two's complement
                  data[i+1] -= 0x1000;
               }
               pd+=3;
            }
         } else
            printf("Received packet from %s:%d, %d bytes\n", inet_ntoa(rem_addr.sin_addr), ntohs(rem_addr.sin_port), n);
      }
      
   } while (1);
   
   return 0;
}

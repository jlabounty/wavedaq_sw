//
//  interface.cpp
//  WaveDAQ Ethernet Interface
//
//  Created by Stefan Ritt on 13/8/15.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "wds.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <assert.h>
#include <errno.h>

#define WD2_PORT 2000

#pragma pack(1)

typedef struct {
   unsigned char  protocol_version;
   unsigned short board_id;
   unsigned short sampling_frequency;
   unsigned short number_of_samples;
   unsigned char  adc_and_channel_info;
   unsigned short channel_segment_number;
   unsigned short data_sequence_number;
   unsigned short packet_sequence_number;
   unsigned short reserved;
} WD2_FRAME_HEADER;

int interface_socket;

int interface_init(GLOBALS *gl)
{
   struct sockaddr_in addr;

#ifdef _MSC_VER
   {
   WSADATA WSAData;
   
   // Start windows sockets
   if (WSAStartup(MAKEWORD(1, 1), &WSAData) != 0)
   return -1;
   }
#endif

   // create UDB socket
   interface_socket = socket(AF_INET, SOCK_DGRAM, 0);
   assert(interface_socket);
   
   // bind socket to port WD2_PORT
   memset((char*)&addr, 0, sizeof(addr));
   addr.sin_family = AF_INET;
   addr.sin_port = htons(WD2_PORT);
   addr.sin_addr.s_addr = htonl(INADDR_ANY);
   if (bind(interface_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
      if (errno == EADDRINUSE)
         printf("Another instance of this program is alredy listening at port %d\n", WD2_PORT);
      else
         perror("bind");
      return FAILURE;
   }

   printf("WD2 Interface listening on port %d ...\n", WD2_PORT);
   return SUCCESS;
}

#define Sleep(x) usleep(x*1000)

double time_ms()
{
   struct timeval tv;
   gettimeofday(&tv, NULL);
   return tv.tv_sec*1000 + tv.tv_usec/1000.0;
}

int interface_read(int millisec, float waveform[16][1024])
{
   int i, status, waveform_channel, current_frame;
   fd_set readfds;
   struct timeval timeout;
   WD2_FRAME_HEADER *ph;
   unsigned char *pd;
   short data1, data2;
   struct sockaddr_in remote_addr;
   unsigned char buffer[1800];
   int header_adc, header_channel;
   double start_time;

   // tag waveforms as invalid
   for (i=0 ; i<16 ; i++) {
      waveform[i][0]   = nanf("");
      waveform[i][512] = nanf("");
   }
   
   current_frame = -1;
   start_time = time_ms();
   
   do { // until all channels received
      
      FD_ZERO(&readfds);
      FD_SET(interface_socket, &readfds);
      
      timeout.tv_sec = millisec / 1000;
      timeout.tv_usec = (millisec % 1000) * 1000;

      do {
         status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
      } while (status == -1 && errno == EINTR);  // don't return if an alarm signal was caught
      
      if (status == -1)
         perror("select");
      
      // if we are waiting more than 1 second, return error
      if (time_ms() - start_time > 1000)
         return FAILURE;
      
      if (FD_ISSET(interface_socket, &readfds)) {
         int len, n;
         
         // packet is available, so receive it
         len = sizeof(remote_addr);
         n = (int)recvfrom(interface_socket, (char *)buffer, sizeof(buffer), 0,
                           (struct sockaddr *)&remote_addr, (socklen_t *)&len);
         if (n > sizeof(WD2_FRAME_HEADER)) {
            ph = (WD2_FRAME_HEADER *)buffer;
            
            // correct endianness of header data
            ph->board_id               = SWAP_UINT16(ph->board_id);
            ph->sampling_frequency     = SWAP_UINT16(ph->sampling_frequency);
            ph->number_of_samples      = SWAP_UINT16(ph->number_of_samples);
            header_adc                 = (ph->adc_and_channel_info >> 4) & 0x0f;
            header_channel             = (ph->adc_and_channel_info) & 0x0f;
            ph->channel_segment_number = SWAP_UINT16(ph->channel_segment_number);
            ph->data_sequence_number   = SWAP_UINT16(ph->data_sequence_number);
            ph->packet_sequence_number = SWAP_UINT16(ph->packet_sequence_number);
            ph->reserved               = SWAP_UINT16(ph->reserved);
            
            /*
            printf("From %s:%d, Frame %5d, ADC/Chn/Segment %d/%d/%d\n", inet_ntoa(remote_addr.sin_addr),
                   ntohs(remote_addr.sin_port),
                   ph->data_sequence_number,
                   header_adc,
                   header_channel,
                   ph->channel_segment_number);
            */
            
            if (current_frame == -1)
               current_frame = ph->data_sequence_number;
            
            // drop package if it does not belong to current frame
            if (ph->data_sequence_number != current_frame)
               continue;
            
            waveform_channel = header_adc*8+header_channel;
            assert(waveform_channel < 16);
            
            // decode waveform data
            pd = (unsigned char*)(ph+1);
            for (i=0 ; i<512 ; i+=2) {
               data1   = ((pd[1] & 0x0F) << 8) | pd[0];
               if(data1 >= 0x0800) {
                  // expand two's complement
                  data1 -= 0x1000;
               }
               data2 = ((unsigned short)pd[2] << 4) | (pd[1] >> 4);
               if(data2 >= 0x0800) {
                  // expand two's complement
                  data2 -= 0x1000;
               }
               pd+=3;
               
               if (ph->channel_segment_number == 0) {
                  // first segment
                  waveform[waveform_channel][i]       = (float)data1 * (0.63 / 4096.0); // 2V range with 12 bits
                  waveform[waveform_channel][i+1]     = (float)data2 * (0.63 / 4096.0);
               } else {
                  // second segment
                  waveform[waveform_channel][512+i]   = (float)data1 * (0.63 / 4096.0);
                  waveform[waveform_channel][512+i+1] = (float)data2 * (0.63 / 4096.0);
               }
            }
            
            // test if all waveforms are received
            for (i=0 ; i<16 ; i++)
               if (isnan(waveform[i][0]) || isnan(waveform[i][512]))
                   break;
            if (i == 16)
               return SUCCESS;
            
         } else {
            printf("Unexpected UDP packet received\n");
            return FAILURE;
         }
      }
      
   } while (1);
   
   return FAILURE;
}


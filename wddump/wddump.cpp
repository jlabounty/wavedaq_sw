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

int main()
{
   int s, i, n, status;
   unsigned char buffer[1800];
   fd_set readfds;
   struct sockaddr_in addr, rem_addr;
   struct timeval timeout;
   WD2_FRAME_HEADER *ph;
   unsigned char *pd;
   short data[512];
   unsigned short header_adc;
   unsigned short header_ch;
   socklen_t len;
   FILE *f;
   //FILE *l;
   
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
            // correct endianness of header data
            ph->board_id               = 0xFFFF & ((ph->board_id<<8)|(ph->board_id>>8));
            ph->sampling_frequency     = 0xFFFF & ((ph->sampling_frequency<<8)|(ph->sampling_frequency>>8)); 
            ph->number_of_samples      = 0xFFFF & ((ph->number_of_samples<<8)|(ph->number_of_samples>>8));
            header_adc                 = 0x0F   & (ph->adc_and_channel_info >> 4);
            header_ch                  = 0x0F   & ph->adc_and_channel_info;
            ph->channel_segment_number = 0xFFFF & ((ph->channel_segment_number<<8)|(ph->channel_segment_number>>8));
            ph->data_sequence_number   = 0xFFFF & ((ph->data_sequence_number<<8)|(ph->data_sequence_number>>8));
            ph->packet_sequence_number = 0xFFFF & ((ph->packet_sequence_number<<8)|(ph->packet_sequence_number>>8));
            ph->reserved               = 0xFFFF & ((ph->reserved<<8)|(ph->reserved>>8));
            //printf("Received packet from   : %s:%d\n", inet_ntoa(rem_addr.sin_addr), ntohs(rem_addr.sin_port));
            //printf("xxx.xxx.xxx.xxx:xxxxx   xxxxx      x/x/x\n\r");
            printf("%s:%5d   %5d      %d/%d/%d\n\r", inet_ntoa(rem_addr.sin_addr), ntohs(rem_addr.sin_port), ph->data_sequence_number, header_adc, header_ch, ph->channel_segment_number);
            //printf("Protocol version       : %d\n", ph->protocol_version);
            //printf("Board ID               : %d\n", ph->board_id);
            //printf("Sampling frequency     : %d\n", ph->sampling_frequency);
            //printf("Number of Samples      : %d\n", ph->number_of_samples);
            //printf("ADC/Channel Number     : %d/%d\n", header_adc,  header_ch);
            //printf("Channel Segment Number : %d\n", ph->channel_segment_number);
            //printf("Data Sequence Number   : %d\n", ph->data_sequence_number);
            //printf("Packet Sequence Number : %d\n", ph->packet_sequence_number);
            //printf("Reserved               : %d\n", ph->reserved);
            //printf("\n");
            
            // decode waveform data
            pd = (unsigned char*)(ph+1);
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
            
            // write data to file
            f = fopen("dump.txt", "a");
            assert(f);
            // header information
            fprintf(f, "%d\n", ph->board_id);
            fprintf(f, "%d\n", ph->sampling_frequency); 
            fprintf(f, "%d\n", ph->number_of_samples);
            fprintf(f, "%d\n", header_adc);
            fprintf(f, "%d\n", header_ch);
            fprintf(f, "%d\n", ph->channel_segment_number);
            fprintf(f, "%d\n", ph->data_sequence_number);
            fprintf(f, "%d\n", ph->packet_sequence_number);
            fprintf(f, "%d\n", ph->reserved);
            // data
            for (i=0 ; i<512 ; i++)
               fprintf(f, "%d\n", data[i]);
            fprintf(f, "\n");
            fclose(f);
            // write log to file
            /*
            l = fopen("log.txt", "a");
            assert(l);
            fprintf(l, "Frame %d | ADC/Channel %d/%d | Segment %d", ph->data_sequence_number, header_adc, header_ch, ph->channel_segment_number);
            fprintf(l, "\n");
            fclose(l);
            */
         } else
            printf("Received packet from %s:%d, %d bytes\n", inet_ntoa(rem_addr.sin_addr), ntohs(rem_addr.sin_port), n);
      }
      
   } while (1);
   
   return 0;
}

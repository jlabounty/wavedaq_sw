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

#define WD2_PORT 1850

typedef struct {
   unsigned char  protocol_version;
   unsigned short board_id;
   unsigned short sampling_frequency;
   unsigned short number_of_samples;
   unsigned char  channel_info_adc;
   unsigned char  channel_info_channel;
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
   unsigned short data[512];
   socklen_t len;
   FILE *f;
   
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
            printf("Received packet from : %s:%d\n", inet_ntoa(rem_addr.sin_addr), ntohs(rem_addr.sin_port));
            printf("Protocol version     : %d\n", ph->protocol_version);
            printf("Board ID             : %d\n", ph->board_id);
            printf("Sampling frequency   : %d\n", ph->sampling_frequency);
            
            // decode waveform data
            for (i=0 ; i<512 / 2 ; ) {
               pd = (unsigned char*)(ph+1);
               data[i++] = pd[0] | ((pd[1] & 0x0F) << 8);
               pd++;
               data[i++] = (pd[0] >> 4) | ((unsigned short)pd[1] << 4);
               pd++;
            }
            
            // write data to file
            f = fopen("dump.txt", "a");
            assert(f);
            for (i=0 ; i<512 ; i++)
               fprintf(f, "%d\n", data[i]);
            fprintf(f, "\n");
            fclose(f);
            
         } else
            printf("Received packet from %s:%d, %d bytes\n", inet_ntoa(rem_addr.sin_addr), ntohs(rem_addr.sin_port), n);
      }
      
   } while (1);
   
   return 0;
}
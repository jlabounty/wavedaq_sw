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
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <assert.h>
#include <errno.h>

#ifdef __linux__
#include <linux/sockios.h>
#include <sys/ioctl.h>
#include <net/if.h>
#endif
#ifdef __APPLE__
#include <net/if_dl.h>
#endif

#define WD2_CMD_PORT   3000
#define WD2_DATA_PORT  2000

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

/*-----------------------------------------------------------------------------------------*/

size_t strlcpy(char *dst, const char *src, size_t size)
{
   char *d = dst;
   const char *s = src;
   size_t n = size;
   
   /* Copy as many bytes as will fit */
   if (n != 0 && --n != 0) {
      do {
         if ((*d++ = *s++) == 0)
            break;
      } while (--n != 0);
   }
   
   /* Not enough room in dst, add NUL and traverse rest of src */
   if (n == 0) {
      if (size != 0)
         *d = '\0';             /* NUL-terminate dst */
      while (*s++);
   }
   
   return (s - src - 1);        /* count does not include NUL */
}

size_t strlcat(char *dst, const char *src, size_t size)
{
   char *d = dst;
   const char *s = src;
   size_t n = size;
   size_t dlen;
   
   /* Find the end of dst and adjust bytes left but don't go past end */
   while (n-- != 0 && *d != '\0')
      d++;
   dlen = d - dst;
   n = size - dlen;
   
   if (n == 0)
      return (dlen + strlen(s));
   while (*s != '\0') {
      if (n != 1) {
         *d++ = *s;
         n--;
      }
      s++;
   }
   *d = '\0';
   
   return (dlen + (s - src));   /* count does not include NUL */
}

/*-----------------------------------------------------------------------------------------*/

void get_mac_addr(int socket, const char *interface, char *mac_addr)
{
#ifdef __linux__
   struct ifreq ifinfo;
   unsigned char mac[6];
   strcpy(ifinfo.ifr_name, interface);
   int result = ioctl(socket, SIOCGIFHWADDR, &ifinfo);
    
   if ((result == 0) && (ifinfo.ifr_hwaddr.sa_family == 1)) {
      memcpy(mac, ifinfo.ifr_hwaddr.sa_data, IFHWADDRLEN);
      sprintf(mac_addr, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
      return;
   }
#endif

#ifdef __APPLE__
   struct ifaddrs *if_addr = NULL;

   getifaddrs(&if_addr);
   for ( ; if_addr != NULL ; if_addr = if_addr->ifa_next) {
      if (strcmp(if_addr->ifa_name, interface) == 0) {
         if (if_addr->ifa_addr != NULL && if_addr->ifa_addr->sa_family == AF_LINK) {
            struct sockaddr_dl * sdl = (struct sockaddr_dl *)if_addr->ifa_addr;
            unsigned char mac[6];
            memcpy(mac, LLADDR(sdl), sdl->sdl_alen);
            sprintf(mac_addr, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
            return;
         }
      }
   }
#endif
}

void get_ip_addr(int socket, const char *interface, char *ip_addr)
{
   struct ifaddrs *if_addr = NULL;
   
   getifaddrs(&if_addr);
   for ( ; if_addr != NULL ; if_addr = if_addr->ifa_next) {
      if (strcmp(if_addr->ifa_name, interface) == 0) {
         if (if_addr->ifa_addr != NULL && if_addr->ifa_addr->sa_family == AF_INET) {
            inet_ntop(AF_INET, &((struct sockaddr_in *)if_addr->ifa_addr)->sin_addr, ip_addr, INET_ADDRSTRLEN);
            return;
         }
      }
   }
}


/*-----------------------------------------------------------------------------------------*/

int interface_send(GLOBALS *gl, int board, const char *str, char *result, int *size)
{
   size_t n, i;
   fd_set readfds;
   struct timeval timeout;
   int    status;
   int    millisec = 100;
   struct sockaddr_in client_addr;
   char   buffer[1600], prompt[80];

   // send request
   memcpy(&client_addr, gl->eth_addr[board], sizeof(client_addr));
   
   i = sendto(gl->cmd_socket[board],
                  str,
                  strlen(str),
                  0,
                  (struct sockaddr *)&client_addr,
                  sizeof(client_addr));
   assert(i = strlen(str));
   
   // retrieve reply
   // TBD: retry a few times
   n = 0;
   do {
      memset(buffer, 0, sizeof(buffer));
      
      FD_ZERO(&readfds);
      FD_SET(gl->cmd_socket[board], &readfds);
      
      timeout.tv_sec = millisec / 1000;
      timeout.tv_usec = (millisec % 1000) * 1000;
      
      do {
         status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
      } while (status == -1);        /* dont return if an alarm signal was cought */
      
      if (!FD_ISSET(gl->cmd_socket[board], &readfds)) {
         if (size != NULL)
            *size = 0;
         return 0;
      }
      
      i = recv(gl->cmd_socket[board], buffer, sizeof(buffer), 0);
      assert(i > 0);
      
      if (buffer[i] == 0) // don't count trailing zero
         i--;
      
      if (result != NULL)
         memcpy(result+n, buffer, i);
      n += i;
      
      // check for prompt
      strlcpy(prompt, gl->board_name[board], sizeof(prompt));
      strlcat(prompt, " > ", sizeof(prompt));
      
      if (strcmp(buffer+strlen(buffer)-strlen(prompt), prompt) == 0)
         break;
      
   } while (1);
   
   // chop off prompt
   if (result != NULL)
      result[strlen(result)-strlen(prompt)] = 0;
   n -= strlen(prompt);
          
   if (size != NULL)
      *size = (int)n;
   
   return SUCCESS;
}

/*-----------------------------------------------------------------------------------------*/

int interface_init(GLOBALS *gl)
{
   struct sockaddr_in server_addr;
   struct sockaddr_in client_addr;
   char addr_str[32], str[256], reply[10000], interface[32];
   struct hostent *phe;
   int size;
   
#ifdef _MSC_VER
   {
   WSADATA WSAData;
   
   // Start windows sockets
   if (WSAStartup(MAKEWORD(1, 1), &WSAData) != 0)
   return -1;
   }
#endif

   gl->cmd_socket = (int *)malloc(sizeof(int)*gl->n_boards);
   gl->data_socket = (int *)malloc(sizeof(int)*gl->n_boards);
   gl->eth_addr = (unsigned char **)malloc(sizeof(unsigned char *)*gl->n_boards);
   for (int i=0 ; i<gl->n_boards ; i++)
      gl->eth_addr[i] = (unsigned char *)malloc(sizeof(unsigned char)*16);
 
   for (int i=0 ; i<gl->n_boards ; i++) {
      
      // create UDB socket for command interpreter
      if (i == 0) {
         gl->cmd_socket[i] = socket(AF_INET, SOCK_DGRAM, 0);
         assert(gl->cmd_socket[i]);
         
         // bind socket to any port
         memset((char*)&server_addr, 0, sizeof(server_addr));
         server_addr.sin_family = AF_INET;
         server_addr.sin_port = htons(3000); // use any port
         server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
         if (bind(gl->cmd_socket[i], (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
            perror("bind");
            return FAILURE;
         }
         
         // find out which port we were bound
         size = sizeof(server_addr);
         getsockname(gl->cmd_socket[i], (struct sockaddr *) &server_addr, (socklen_t *)&size);
         if (gl->verbose_flag)
            printf("Listening on command port %d\n", ntohs(server_addr.sin_port));
      } else
         gl->cmd_socket[i] = gl->cmd_socket[0]; // reuse socket
      
      // create UDB socket to receive binary data
      if (i == 0) {
         gl->data_socket[i] = socket(AF_INET, SOCK_DGRAM, 0);
         assert(gl->data_socket[i]);
         
         // bind socket to port WD2_DATA_PORT
         memset((char*)&server_addr, 0, sizeof(server_addr));
         server_addr.sin_family = AF_INET;
         server_addr.sin_port = htons(WD2_DATA_PORT);
         server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
         if (bind(gl->data_socket[i], (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
            perror("bind");
            return FAILURE;
         }
         
         // find out which port we were bound
         size = sizeof(server_addr);
         getsockname(gl->data_socket[i], (struct sockaddr *) &server_addr, (socklen_t *)&size);
         if (gl->verbose_flag)
            printf("Listening on data port %d\n", ntohs(server_addr.sin_port));
      } else
         gl->data_socket[i] = gl->data_socket[0]; // reuse socket
      
      // retrieve Ethernet address of board
      phe = gethostbyname(gl->board_name[i]);
      if (phe == NULL) {
         printf("Cannot resolve host name \"%s\"\n", gl->board_name[i]);
         return 0;
      }
      memcpy((char *)&client_addr.sin_addr, phe->h_addr, phe->h_length);
      client_addr.sin_family = AF_INET;
      client_addr.sin_port = htons(WD2_CMD_PORT);
      size = sizeof(client_addr);
      memcpy(gl->eth_addr[i], &client_addr, sizeof(client_addr));

#ifdef __linux__
      strcpy(interface, "eth0");
#endif
#ifdef __APPLE__
      strcpy(interface, "en0");
#endif

      // check if board is alive
      size = sizeof(reply);
      interface_send(gl, i, "info", reply, &size);
      if (!size) {
         printf("Board %s does not reply, aborting.\n", gl->board_name[i]);
         return 0;
      }
      if (gl->verbose_flag) {
         char *p = strstr(reply, "-- Version");
         if (p != NULL) {
            char *p2 = strstr(p, "\r\n\r\n");
            if (p2 != NULL)
               *p2 = 0;
            printf("Board %s info:\n%s", gl->board_name[i], p);
         }
      }

      // set destinantion port in WD board
      get_mac_addr(gl->cmd_socket[i], interface, addr_str);
      sprintf(str, "setenv dstport %d", WD2_DATA_PORT);
      size = sizeof(reply);
      interface_send(gl, i, str, reply, &size);
      if (gl->verbose_flag)
         printf("Set dstport = %d at %s\n", WD2_DATA_PORT, gl->board_name[i]);

      // set MAC address in WD board
      get_mac_addr(gl->cmd_socket[i], interface, addr_str);
      sprintf(str, "setenv ethaddrdst %s", addr_str);
      size = sizeof(reply);
      interface_send(gl, i, str, reply, &size);
      if (gl->verbose_flag)
         printf("Set ethaddrdst = %s at %s\n", addr_str, gl->board_name[i]);
      
      // set IP address in WD board
      get_ip_addr(gl->cmd_socket[i], interface, addr_str);
      sprintf(str, "setenv ipaddrdst %s", addr_str);
      size = sizeof(reply);
      interface_send(gl, i, str, reply, &size);
      if (gl->verbose_flag)
         printf("Set ipaddrdst = %s at %s\n", addr_str, gl->board_name[i]);
   }
   
   return SUCCESS;
}

/*-----------------------------------------------------------------------------------------*/

#define Sleep(x) usleep(x*1000)

double time_ms()
{
   struct timeval tv;
   gettimeofday(&tv, NULL);
   return tv.tv_sec*1000 + tv.tv_usec/1000.0;
}

/*-----------------------------------------------------------------------------------------*/

int interface_read_waveform(GLOBALS *gl, int board, int millisec, float waveform[16][1024])
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
      FD_SET(gl->data_socket[board], &readfds);
      
      timeout.tv_sec = millisec / 1000;
      timeout.tv_usec = (millisec % 1000) * 1000;

      do {
         status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
      } while (status == -1 && errno == EINTR);  // don't return if an alarm signal was caught
      
      if (status == -1)
         perror("select");
      
      // if we are waiting more than 1 second, return error
      if (time_ms() - start_time > 1000) {
         if (gl->verbose_flag)
            printf("Timeout in receiving complete frame\n");
         return FAILURE;
      }
      
      if (FD_ISSET(gl->data_socket[board], &readfds)) {
         int len, n;
         
         // packet is available, so receive it
         len = sizeof(remote_addr);
         n = (int)recvfrom(gl->data_socket[board], (char *)buffer, sizeof(buffer), 0,
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
            
            if (gl->verbose_flag)
               printf("From %s:%d, Frame %5d, ADC/Chn/Segment %d/%d/%d\n", inet_ntoa(remote_addr.sin_addr),
                      ntohs(remote_addr.sin_port),
                      ph->data_sequence_number,
                      header_adc,
                      header_channel,
                      ph->channel_segment_number);
            
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

//
//  wd
//  WaveDAQ Ethernet Interface
//
//  Created by Stefan Ritt on 13/8/15.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>

#include "wds.h"
#include "averager.h"

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
   unsigned char  board_version;
   unsigned short board_id;
   unsigned char  crate_id;
   unsigned char  slot_id;
   unsigned char  adc_and_channel_info;
   unsigned char  channel_segment_number;
   unsigned short readout_sequence_number;
   unsigned short hardware_sequence_number;
   unsigned short sampling_frequency;
   unsigned short number_of_samples;
   unsigned short drs0_trigger_cell;
   unsigned short drs1_trigger_cell;
   unsigned short trigger_type;
   unsigned short packet_sequence_number;
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

int wd_send(GLOBALS *gl, int b, int timeout_ms, const char *str, char *result, int *size)
{
   size_t n, i;
   fd_set readfds;
   struct timeval timeout;
   int    status;
   struct sockaddr_in client_addr;
   char   tx_buffer[1600], rx_buffer[1600], prompt[80];

   memcpy(&client_addr, gl->board[b].eth_addr, sizeof(client_addr));
   strlcpy(tx_buffer, str, sizeof(tx_buffer));
   if (tx_buffer[strlen(tx_buffer)-1] != '\n')
      strlcat(tx_buffer, "\n", sizeof(tx_buffer));

   if (result != NULL)
      memset(result, 0, *size);
   n = 0;

   // assemble prompt
   strlcpy(prompt, gl->board[b].name, sizeof(prompt));
   strlcat(prompt, " > ", sizeof(prompt));
   
   // retry max five times
   for (int retry=0 ; retry < 5 ; retry++) {
      
      // send request
      i = sendto(gl->board[b].cmd_socket,
                 tx_buffer,
                 strlen(tx_buffer),
                 0,
                 (struct sockaddr *)&client_addr,
                 sizeof(client_addr));
      
      if (i != strlen(tx_buffer)) {
         printf("%s send retry %d\n", gl->board[b].name, retry+1);
         continue;
      }
      
      // retrieve reply until prompt is found
      n = 0;
      do {
         memset(rx_buffer, 0, sizeof(rx_buffer));
         
         FD_ZERO(&readfds);
         FD_SET(gl->board[b].cmd_socket, &readfds);
         
         timeout.tv_sec = timeout_ms / 1000;
         timeout.tv_usec = (timeout_ms % 1000) * 1000;
         
         do {
            status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
         } while (status == -1);        /* dont return if an alarm signal was cought */
         
         if (!FD_ISSET(gl->board[b].cmd_socket, &readfds))
            break;
         
         i = recv(gl->board[b].cmd_socket, rx_buffer, sizeof(rx_buffer), 0);
         assert(i > 0);
         
         if (rx_buffer[i-1] == 0) // don't count trailing zero
            i--;
         
         if (result != NULL)
            memcpy(result+n, rx_buffer, i);
         n += i;
         
         // check for prompt
         if (strcmp(rx_buffer+strlen(rx_buffer)-strlen(prompt), prompt) == 0)
            break;
         
      } while (1);
      
      // check for prompt
      if (strcmp(rx_buffer+strlen(rx_buffer)-strlen(prompt), prompt) == 0)
         break;
      
      printf("%s retry %d\n", gl->board[b].name, retry+1);
   }

   if (n == 0) {
      if (size != NULL)
         *size = 0;
      return -1;
   }

   // chop off prompt
   if (result != NULL)
      result[strlen(result)-strlen(prompt)] = 0;
   n -= strlen(prompt);
          
   if (size != NULL)
      *size = (int)n;
   
   return SUCCESS;
}

/*-----------------------------------------------------------------------------------------*/

int wd_init(GLOBALS *gl)
{
   struct sockaddr_in server_addr;
   struct sockaddr_in client_addr;
   char str[256], reply[10000];
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

   if (gl->demo_flag)
      return SUCCESS;
   
   for (int index=0 ; index<gl->n_boards ; index++) {
      
      // create UDB socket for command interpreter on any port
      if (index == 0) {
         gl->board[index].cmd_socket = socket(AF_INET, SOCK_DGRAM, 0);
         assert(gl->board[index].cmd_socket);
      } else
         gl->board[index].cmd_socket = gl->board[0].cmd_socket; // reuse socket
      
      // create UDB socket to receive binary data on port WD2_DATA_PORT
      if (index == 0) {
         gl->board[index].data_socket = socket(AF_INET, SOCK_DGRAM, 0);
         assert(gl->board[index].data_socket);
         
         // bind socket to port WD2_DATA_PORT
         memset((char*)&server_addr, 0, sizeof(server_addr));
         server_addr.sin_family = AF_INET;
         server_addr.sin_port = htons(WD2_DATA_PORT);
         server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
         if (bind(gl->board[index].data_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
            if (errno == 1)
               printf("wds server is already running\n");
            else
               perror("bind");
            return FAILURE;
         }
         if (gl->verbose_flag)
            printf("Listening on data port %d\n", WD2_DATA_PORT);
      } else
         gl->board[index].data_socket = gl->board[0].data_socket; // reuse socket

      // retrieve Ethernet address of board
      phe = gethostbyname(gl->board[index].name);
      if (phe == NULL) {
         printf("Cannot resolve host name \"%s\"\n", gl->board[index].name);
         return 0;
      }
      memcpy((char *)&client_addr.sin_addr, phe->h_addr, phe->h_length);
      client_addr.sin_family = AF_INET;
      client_addr.sin_port = htons(WD2_CMD_PORT);
      size = sizeof(client_addr);
      memcpy(gl->board[index].eth_addr, &client_addr, sizeof(client_addr));

      // check if board is alive
      if (wd_send(gl, index, 1000, "", NULL, NULL) < 0) {
         printf("Cannot connect to board \"%s\"\n", gl->board[index].name);
         return 0;
      }
      
      // set dbglevel none
      assert(wd_send(gl, index, 100, "dbglvl none", NULL, NULL) > 0);

      // print board info
      if (gl->verbose_flag) {
         size = sizeof(reply);
         wd_send(gl, index, 1000, "info", reply, &size); // first access long timeout
         if (!size) {
            printf("Board %s does not reply, aborting.\n", gl->board[index].name);
            return 0;
         }
         char *p = strstr(reply, "-- Version");
         if (p != NULL) {
            char *p2 = strstr(p, "\r\n\r\n");
            if (p2 != NULL)
               *p2 = 0;
            printf("\n**** Board %s info: ****\n%s", gl->board[index].name, p);
         }
      }

      // set destinantion port in WD board
      sprintf(str, "setenv dstport %d", WD2_DATA_PORT);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      if (gl->verbose_flag)
         printf("Set dstport       = %d\n", WD2_DATA_PORT);

      // set MAC address and IP address of this computer in WD board
      assert(wd_send(gl, index, 100, "cfgdst", NULL, NULL) > 0);
      
      if (gl->verbose_flag) {
         size = sizeof(reply);
         wd_send(gl, index, 100, "printenv -n ethaddrdst", reply, &size);
         if (strchr(reply, '\n'))
            *strchr(reply, '\n') = 0;
         if (gl->verbose_flag)
            printf("Set ethaddrdst    = %s\n", reply);
         
         size = sizeof(reply);
         wd_send(gl, index, 100, "printenv -n ipaddrdst", reply, &size);
         if (strchr(reply, '\n'))
            *strchr(reply, '\n') = 0;
         if (gl->verbose_flag)
            printf("Set ipaddrdst     = %s\n", reply);
      }
      
      // set input configuration
      if (gl->board[index].pzc) { // pole zero cancellation on (bit=0)
         if (gl->board[index].gain == 0)
            sprintf(str, "feset all 02");
         else if (gl->board[index].gain == 1)
            sprintf(str, "feset all 1a");
         else if (gl->board[index].gain == 2)
            sprintf(str, "feset all 3a");
         assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      } else { // pole zero cancellation off (bit=1)
         if (gl->board[index].gain == 0)
            sprintf(str, "feset all 82");
         else if (gl->board[index].gain == 1)
            sprintf(str, "feset all 9a");
         else if (gl->board[index].gain == 2)
            sprintf(str, "feset all ba");
         assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      }

      // trun on comparator power
      assert(wd_send(gl, index, 100, "pwrcmp on", NULL, NULL) > 0);

      // set comparator level
      if (gl->verbose_flag)
         printf("Set trigger level = %d mV\n", gl->board[index].trigger_level);
      sprintf(str, "dacset tlevel1 %d", gl->board[index].trigger_level);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      sprintf(str, "dacset tlevel2 %d", gl->board[index].trigger_level);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      sprintf(str, "dacset tlevel3 %d", gl->board[index].trigger_level);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      sprintf(str, "dacset tlevel4 %d", gl->board[index].trigger_level);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      
      // set offset
      if (gl->verbose_flag)
         printf("Set offset level  = %g V\n", gl->board[index].offset);
      sprintf(str, "dacset ofs %d", (int)(gl->board[index].offset*1000));
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      
      // set sampling frequency
      if (gl->verbose_flag)
         printf("Set sampling frequency to %d GSPS", gl->sampling_speed);
      if (gl->sampling_speed == 1)
         assert(wd_send(gl, index, 100, "regwr 2c 0003c800", NULL, NULL) > 0);
      else if (gl->sampling_speed == 2)
         assert(wd_send(gl, index, 100, "regwr 2c 0003c800", NULL, NULL) > 0);
      else if (gl->sampling_speed == 3)
         assert(wd_send(gl, index, 100, "regwr 2c 00038500", NULL, NULL) > 0);
      else if (gl->sampling_speed == 4)
         assert(wd_send(gl, index, 100, "regwr 2c 00036400", NULL, NULL) > 0);
      else if (gl->sampling_speed == 5)
         assert(wd_send(gl, index, 100, "regwr 2c 00035000", NULL, NULL) > 0);
      
      // enable local trigger
      if (gl->board[index].trigger_level != 0) {
         // trigger_cfg_or
         sprintf(str, "regwr d4 %s", gl->board[index].trigger_mask);
         assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
         // trigger_enable, trigger_falling_edge
         assert(wd_send(gl, index, 100, "regwr d8 000C0000", NULL, NULL) > 0);
      } else {
         assert(wd_send(gl, index, 100, "regwr d4 00000000", NULL, NULL) > 0);
         assert(wd_send(gl, index, 100, "regwr d8 00000000", NULL, NULL) > 0);
      }
   
      // set DRS readout mode to ROI
      assert(wd_send(gl, index, 100, "regwr 10 0D0D0030", NULL, NULL) > 0);
      
      // load calibration for board from file (for now...)
      char str[80];
      sprintf(str, "%s.cal", gl->board[index].name);
      int fh = open(str, O_RDONLY, 0644);
      if (fh > 0) {
         assert(read(fh, gl->board[index].wf_offset1, sizeof(float)*16*1024) == sizeof(float)*16*1024);
         assert(read(fh, gl->board[index].wf_offset2, sizeof(float)*16*1024) == sizeof(float)*16*1024);
      } else {
         memset(gl->board[index].wf_offset1, 0, sizeof(float)*16*1024);;
         memset(gl->board[index].wf_offset2, 0, sizeof(float)*16*1024);;
      }
   }
   
   if (gl->verbose_flag)
      printf("\n");
   
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

int wd_read_waveform(GLOBALS *gl, int b, int millisec, WD2_EVENT *pe, float waveform[16][1024])
{
   int i, status, waveform_channel, current_frame;
   fd_set readfds;
   struct timeval timeout;
   unsigned char *pd;
   WD2_FRAME_HEADER *ph;
   short data1, data2;
   struct sockaddr_in remote_addr;
   unsigned char buffer[1800];
   int header_adc, header_channel;
   double start_time;
   static float wf1[16][1024], wf2[16][1024];

   // tag waveforms as invalid
   for (i=0 ; i<16 ; i++) {
      waveform[i][0]   = nanf("");
      waveform[i][512] = nanf("");
   }
   
   current_frame = -1;
   start_time = time_ms();
   
   do { // until all channels received
      
      FD_ZERO(&readfds);
      FD_SET(gl->board[b].data_socket, &readfds);
      
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
      
      if (FD_ISSET(gl->board[b].data_socket, &readfds)) {
         int len, n;
         
         // packet is available, so receive it
         len = sizeof(remote_addr);
         n = (int)recvfrom(gl->board[b].data_socket, (char *)buffer, sizeof(buffer), 0,
                           (struct sockaddr *)&remote_addr, (socklen_t *)&len);
         if (n > sizeof(WD2_FRAME_HEADER)) {
            ph = (WD2_FRAME_HEADER *)buffer;
            
            // correct endianness of header data
            ph->board_id                 = SWAP_UINT16(ph->board_id);
            header_adc                   = (ph->adc_and_channel_info >> 4) & 0x0f;
            header_channel               = (ph->adc_and_channel_info) & 0x0f;
            ph->readout_sequence_number  = SWAP_UINT16(ph->readout_sequence_number);
            ph->hardware_sequence_number = SWAP_UINT16(ph->hardware_sequence_number);
            ph->sampling_frequency       = SWAP_UINT16(ph->sampling_frequency);
            ph->number_of_samples        = SWAP_UINT16(ph->number_of_samples);
            ph->drs0_trigger_cell        = SWAP_UINT16(ph->drs0_trigger_cell);
            ph->drs1_trigger_cell        = SWAP_UINT16(ph->drs1_trigger_cell);
            ph->trigger_type             = SWAP_UINT16(ph->trigger_type);
            ph->packet_sequence_number   = SWAP_UINT16(ph->packet_sequence_number);
           
            // copy some data to event header
            pe->board_id = ph->board_id;
            pe->crate_id = ph->crate_id;
            pe->slot_id = ph->slot_id;
            pe->readout_sequence_number = ph->readout_sequence_number;
            pe->hardware_sequence_number = 0; // not yet implemented
            pe->sampling_frequency = ph->sampling_frequency;
            pe->number_of_samples = 1024;
            pe->drs0_trigger_cell = ph->drs0_trigger_cell;
            pe->drs1_trigger_cell = ph->drs1_trigger_cell;
            pe->trigger_type = 0; // not yet implemented
            
            if (gl->verbose_flag)
               printf("From %s:%d, Frame %5d, ADC/Chn/Segment %d/%d/%d - %04d/%04d\n",
                      inet_ntoa(remote_addr.sin_addr),
                      ntohs(remote_addr.sin_port),
                      ph->readout_sequence_number,
                      header_adc,
                      header_channel,
                      ph->channel_segment_number,
                      ph->drs0_trigger_cell,
                      ph->drs1_trigger_cell);
            
            if (current_frame == -1)
               current_frame = ph->readout_sequence_number;
            
            // drop package if it belongs to older frame
            if (ph->readout_sequence_number < current_frame) {
               printf("Package dropped, package frame=%d, current frame=%d\n", ph->readout_sequence_number, current_frame);
               continue;
            }
            
            // drop whole frame if package of next frame received
            if (ph->readout_sequence_number > current_frame) {
               printf("Frame dropped, package frame=%d, current frame=%d\n", ph->readout_sequence_number, current_frame);

               // switch to new frame
               current_frame = ph->readout_sequence_number;
               
               // tag waveforms as invalid
               for (i=0 ; i<16 ; i++) {
                  waveform[i][0]   = nanf("");
                  waveform[i][512] = nanf("");
               }
            }
            
            // drop package if it does not belong to current board
            /*
            if (ph->board_id != b) {
               printf("Package dropped, package board=%d, current board=%d\n", ph->board_id, b);
               continue;
            }
            */
            
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
            if (i == 16) {

               for (i=0 ; i<16 ; i++)
                  for (int j=0 ; j<1024 ; j++)
                     wf2[i][j] = waveform[i][j];

               // un-rotate waveforms
               if (gl->rotate_flag) {
                  for (i=0 ; i<8 ; i++)
                     for (int j=0 ; j<1024 ; j++)
                        waveform[i][j] = wf1[i][j];
               } else {
                  for (i=0 ; i<8 ; i++) {
                     for (int j=0 ; j<1024 ; j++)
                        waveform[i][(j+pe->drs0_trigger_cell) % 1024] = wf1[i][j];
                  }
                  for (i=8 ; i<16 ; i++) {
                     for (int j=0 ; j<1024 ; j++)
                        waveform[i][(j+pe->drs1_trigger_cell) % 1024] = wf1[i][j];
                  }
               }
               
               for (i=0 ; i<16 ; i++)
                  for (int j=0 ; j<1024 ; j++)
                     wf1[i][j] = wf2[i][j];
              
               // calibrate waveforms
               if (!gl->adc_flag) { // don't calibrate in ADC mode
                  
                  // cell-by-cell offset calibration
                  if (gl->ofs_calib1_flag) {
                     if (gl->rotate_flag) {
                        for (i=0 ; i<8 ; i++)
                           for (int j=0 ; j<1024 ; j++)
                              waveform[i][j] -= gl->board[b].wf_offset1[i][(j+pe->drs0_trigger_cell) % 1024];
                        for (i=8 ; i<16 ; i++)
                           for (int j=0 ; j<1024 ; j++)
                              waveform[i][j] -= gl->board[b].wf_offset1[i][(j+pe->drs1_trigger_cell) % 1024];
                     } else {
                        for (i=0 ; i<16 ; i++)
                           for (int j=0 ; j<1024 ; j++)
                              waveform[i][j] -= gl->board[b].wf_offset1[i][j];
                     }
                  }
                  
                  // start-to-end offset calibration
                  if (gl->ofs_calib2_flag) {
                     for (i=0 ; i<16 ; i++)
                        for (int j=0 ; j<1024 ; j++)
                           waveform[i][j] -= gl->board[b].wf_offset2[i][j];
                  }
               }

               return SUCCESS;
            }
            
         } else {
            printf("Unexpected UDP packet received\n");
            return FAILURE;
         }
      }
      
   } while (1);
   
   return FAILURE;
}

/*-----------------------------------------------------------------------------------------*/


int wd_calibrate(GLOBALS *gl)
{
   float wfU[16][1024], awf1[16][1024], awf2[16][1024];
   int i, n, prog, old_prog;
   WD2_EVENT eventHeader;
   char str[80];
   
   n = 500;

   printf("Calibration boards\n");
   
   for (int board=0 ; board<gl->n_boards ; board++) {

      printf("%s: [                                                 ]\r%s: [",
             gl->board[board].name, gl->board[board].name);
      fflush(stdout);
      
      old_prog = 0;

      //---- Primary Calibration ----
      
      Averager *ave = new Averager(2, 8, 1024, n);
      memset(awf1, 0, sizeof(awf1));
      gl->rotate_flag = 0;
      gl->ofs_calib1_flag = 0;
      gl->ofs_calib2_flag = 0;
      
      for (i=0 ; i<n ; i++) {
         wd_send(gl, board, 100, "drsget\n", NULL, NULL);
         assert(wd_read_waveform(gl, board, 1000, &eventHeader, wfU) == SUCCESS);
         
         for (int ch=0 ; ch<16 ; ch++)
            for (int bin=0 ; bin<1024 ; bin++)
               ave->Add(ch/8, ch%8, bin, wfU[ch][bin]);

         /* update progress bar */
         prog = (int)((double)(i/2)/(n)*50);
         if (prog > old_prog) {
            old_prog = prog;
            printf("=");
            fflush(stdout);
         }
      }

      for (int ch=0 ; ch<16 ; ch++)
         for (int bin=0 ; bin<1024 ; bin++)
            awf1[ch][bin] = ave->Median(ch/8, ch%8, bin);
      
      // ave->SaveNormalizedDistribution("wf.csv", 0);
      
      // save calibration
      sprintf(str, "%s.cal", gl->board[board].name);
      int fh = open(str, O_WRONLY | O_CREAT, 0644);
      assert(fh > 0);
      assert(write(fh, awf1, sizeof(awf1)) == sizeof(awf1));
      
      for (i=0 ; i<16 ; i++)
         for (int j=0 ; j<1024 ; j++)
            gl->board[board].wf_offset1[i][j] = awf1[i][j];
      
      //---- Secondary Calibration
      
      ave->Reset();
      memset(awf2, 0, sizeof(awf2));
      old_prog = 0;
      gl->rotate_flag = 1; // now rotate waveforms
      gl->ofs_calib1_flag = 1; // and do 1st calibration
      gl->ofs_calib2_flag = 0;
      
      for (i=0 ; i<n ; i++) {
         wd_send(gl, board, 100, "drsget\n", NULL, NULL);
         assert(wd_read_waveform(gl, board, 1000, &eventHeader, wfU) == SUCCESS);
         
         Sleep(10);
         
         for (int ch=0 ; ch<16 ; ch++)
            for (int bin=0 ; bin<1024 ; bin++)
               ave->Add(ch/8, ch%8, bin, wfU[ch][bin]);
         
         /* update progress bar */
         prog = (int)((double)(n/2+i/2)/(n)*50);
         if (prog > old_prog) {
            old_prog = prog;
            printf("=");
            fflush(stdout);
         }
      }
      
      for (int ch=0 ; ch<16 ; ch++)
         for (int bin=0 ; bin<1024 ; bin++)
            awf2[ch][bin] = ave->Median(ch/8, ch%8, bin);
      
      printf("\n");
      
      // save calibration
      assert(write(fh, awf2, sizeof(awf2)) == sizeof(awf2));
      
      close(fh);
   }

   return SUCCESS;
}

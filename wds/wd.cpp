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

#include "averager.h"
#include "wds.h"

#include <sys/types.h>
#include <assert.h>
#include <errno.h>

#ifdef _MSC_VER
#include <windows.h>
#include <io.h>
#include <time.h>
#include <float.h>

union { unsigned int i ; float f; } _nanf = { 0x7fc00000 };
#define NANF (_nanf.f)
#endif

#ifdef __linux__
#include <sys/socket.h>
#include <sys/select.h>
#include <linux/sockios.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <netdb.h>

#define NANF nanf("")
#endif

#ifdef __APPLE__
#include <arpa/inet.h>
#include <netdb.h>
#include <net/if.h>

#define NANF nanf("")
#endif

#define WD2_CMD_PORT   3000

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

void remove_spikes(GLOBALS *gl, short trigger_cell, float wf[][1024]);

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

void wd_set_fe(GLOBALS *gl, int index)
{
   char str[256];
   int byte;
   
   if (gl->demo_flag)
      return;
   
   if (gl->verbose_flag)
      printf("Set gain %d, PZC %d, mux %d\n", gl->board[index].gain, gl->board[index].pzc, gl->mux_flag);

   // set input configuration
   if (gl->board[index].pzc) { // pole zero cancellation on (bit=0)
      if (gl->board[index].gain == 0)
         byte = 0x02;
      else if (gl->board[index].gain == 1)
         byte = 0x0a;
      else if (gl->board[index].gain == 2)
         byte = 0x2A;
   } else { // pole zero cancellation off (bit=1)
      if (gl->board[index].gain == 0)
         byte = 0x82;
      else if (gl->board[index].gain == 1)
         byte = 0x8a;
      else if (gl->board[index].gain == 2)
         byte = 0xaa;
   }
   
   if (gl->mux_flag)
      byte |= 0x01;

   sprintf(str, "feset all %02X", byte);
   assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
   
   // adjust range offset which depends on gain
   wd_set_range(gl, index);
}

/*-----------------------------------------------------------------------------------------*/

void wd_set_trigger_level(GLOBALS *gl, int index)
{
   char str[256];

   if (gl->demo_flag)
      return;

   if (gl->verbose_flag)
      printf("Set trigger level = %d mV\n", (int)(gl->board[index].trigger_level*1000));
   
   sprintf(str, "dacset tlevel1 %d", (int)(gl->board[index].trigger_level*1000+900));
   assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
   sprintf(str, "dacset tlevel2 %d", (int)(gl->board[index].trigger_level*1000+900));
   assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
   sprintf(str, "dacset tlevel3 %d", (int)(gl->board[index].trigger_level*1000+900));
   assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
   sprintf(str, "dacset tlevel4 %d", (int)(gl->board[index].trigger_level*1000+900));
   assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
}

/*-----------------------------------------------------------------------------------------*/

void wd_set_trigger_mode(GLOBALS *gl, int index)
{
   char str[256];
   
   if (gl->demo_flag)
      return;
   
   if (gl->verbose_flag)
      printf("Set trigger mode  %d\n", gl->trigger_mode);

   // enable local trigger
   if (gl->trigger_mode == TM_NORMAL) {
      // trigger_cfg_or
      sprintf(str, "regwr d4 %s", gl->board[index].trigger_mask);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
 
      // trigger_enable, trigger_falling_edge
      assert(wd_send(gl, index, 100, "regwr d8 000C0000", NULL, NULL) > 0);
   } else {
      // disable all trigger
      assert(wd_send(gl, index, 100, "regwr d4 00000000", NULL, NULL) > 0);
      assert(wd_send(gl, index, 100, "regwr d8 00000000", NULL, NULL) > 0);
   }
}

/*-----------------------------------------------------------------------------------------*/

void wd_set_osctca(GLOBALS *gl, int index)
{
   if (gl->demo_flag)
      return;
   
   if (gl->verbose_flag)
      printf("Set TCA oscillator %d\n", gl->osctca_flag);

   if (gl->osctca_flag) {
      assert(wd_send(gl, index, 100, "calosc on", NULL, NULL) > 0);  // enable TCA_CTRL
   } else {
      assert(wd_send(gl, index, 100, "calosc off", NULL, NULL) > 0);
   }
}

/*-----------------------------------------------------------------------------------------*/

void wd_set_sampling_frequency(GLOBALS *gl, int index)
{
   if (gl->demo_flag)
      return;
   
   // set sampling frequency
   if (gl->verbose_flag)
      printf("Set sampling frequency to %f GSPS\n", gl->sampling_frequency);
   
   if (gl->sampling_frequency == 1)
      assert(wd_send(gl, index, 100, "regwr 2c 0003c800", NULL, NULL) > 0); // to be corrected!
   else if (gl->sampling_frequency == 2)
      assert(wd_send(gl, index, 100, "regwr 2c 0003c800", NULL, NULL) > 0);
   else if (gl->sampling_frequency == 3)
      assert(wd_send(gl, index, 100, "regwr 2c 00038500", NULL, NULL) > 0);
   else if (gl->sampling_frequency == 4)
      assert(wd_send(gl, index, 100, "regwr 2c 00036400", NULL, NULL) > 0);
   else if (gl->sampling_frequency == 5)
      assert(wd_send(gl, index, 100, "regwr 2c 00035000", NULL, NULL) > 0);
}

/*-----------------------------------------------------------------------------------------*/

void wd_set_range(GLOBALS *gl, int index)
{
   char str[256];
   
   if (gl->demo_flag)
      return;

   if (gl->verbose_flag)
      printf("Set range = %g V\n", gl->board[index].range);
   
   if (fabs(gl->board[index].range) < 0.001) {
      if (gl->board[index].gain == 2)
         sprintf(str, "dacset ofs %d", 1270);
      else
         sprintf(str, "dacset ofs %d", 1300);
   } else if (fabs(gl->board[index].range - (-0.45)) < 0.001) {
      if (gl->board[index].gain == 2)
         sprintf(str, "dacset ofs %d", 1640);
      else
         sprintf(str, "dacset ofs %d", 2000);
   } else if (fabs(gl->board[index].range - 0.45) < 0.001) {
      if (gl->board[index].gain == 2)
         sprintf(str, "dacset ofs %d", 890);
      else
         sprintf(str, "dacset ofs %d", 580);
   }

   assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
}

/*-----------------------------------------------------------------------------------------*/

void wd_set_dcv_flag(GLOBALS *gl, int index)
{
   if (gl->demo_flag)
      return;
   
   if (gl->verbose_flag)
      printf("Set DC power = %d\n", gl->dcv_flag);
   
   if (gl->dcv_flag)
      assert(wd_send(gl, index, 100, "calbuf on", NULL, NULL) > 0);  // enable BUFFER_CTRL
   else
      assert(wd_send(gl, index, 100, "calbuf off", NULL, NULL) > 0);  // disable BUFFER_CTRL
}

/*-----------------------------------------------------------------------------------------*/

void wd_set_dcv(GLOBALS *gl, int index)
{
   char str[256];
   
   if (gl->demo_flag)
      return;
   
   if (gl->verbose_flag)
      printf("Set DC voltage = %g V\n", gl->dcv);
   
   sprintf(str, "dacset caldc %d", (int)(1280-gl->dcv*1000)); // shift by 1.28V
   assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
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
   return FAILURE;
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
      
      // create UDB socket to receive binary data
      if (index == 0) {
         gl->board[index].data_socket = socket(AF_INET, SOCK_DGRAM, 0);
         assert(gl->board[index].data_socket);
         
         // bind socket to port chosen by OS
         memset((char*)&server_addr, 0, sizeof(server_addr));
         server_addr.sin_family = AF_INET;
         server_addr.sin_port = htons(0); // let OS choose port
         server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
         if (bind(gl->board[index].data_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
            perror("bind");
            return FAILURE;
         }
         size = sizeof(server_addr);
         getsockname(gl->board[index].data_socket, (struct sockaddr *) &server_addr, (socklen_t *) &size);
         gl->board[index].server_port = ntohs(server_addr.sin_port);

         if (gl->verbose_flag)
            printf("Listening on data port %d\n", gl->board[index].server_port);
      } else {
         gl->board[index].data_socket = gl->board[0].data_socket; // reuse socket
         gl->board[index].server_port = gl->board[0].server_port; // and port
      }

      // retrieve Ethernet address of board
      phe = gethostbyname(gl->board[index].name);
      if (phe == NULL) {
         printf("Cannot resolve host name \"%s\"\n", gl->board[index].name);
         return FAILURE;
      }
      memcpy((char *)&client_addr.sin_addr, phe->h_addr, phe->h_length);
      client_addr.sin_family = AF_INET;
      client_addr.sin_port = htons(WD2_CMD_PORT);
      size = sizeof(client_addr);
      memcpy(gl->board[index].eth_addr, &client_addr, sizeof(client_addr));

      // check if board is alive
      if (wd_send(gl, index, 1000, "", NULL, NULL) < 0) {
         printf("Cannot connect to board \"%s\"\n", gl->board[index].name);
         return FAILURE;
      }
      
      // set dbglevel none
      assert(wd_send(gl, index, 100, "dbglvl none", NULL, NULL) > 0);

      // print board info
      if (gl->verbose_flag) {
         size = sizeof(reply);
         wd_send(gl, index, 1000, "info", reply, &size); // first access long timeout
         if (!size) {
            printf("Board %s does not reply, aborting.\n", gl->board[index].name);
            return FAILURE;
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
      sprintf(str, "setenv dstport %d", gl->board[index].server_port);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      if (gl->verbose_flag)
         printf("Set dstport       = %d\n", gl->board[index].server_port);

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
      
      wd_set_fe(gl, index);

      // trun on comparator power
      assert(wd_send(gl, index, 100, "pwrcmp on", NULL, NULL) > 0);

      // set bias
      assert(wd_send(gl, index, 100, "dacset bias 700", NULL, NULL) > 0);

      // set ROFS
      assert(wd_send(gl, index, 100, "dacset rofs 1550", NULL, NULL) > 0);
      
      // set caldc to zero
      assert(wd_send(gl, index, 100, "dacset caldc 1280", NULL, NULL) > 0);

      wd_set_trigger_level(gl, index);
      wd_set_range(gl, index);
      wd_set_sampling_frequency(gl, index);
      wd_set_trigger_mode(gl, index);
      wd_set_osctca(gl, index);
   
      // set DRS readout mode to ROI
      assert(wd_send(gl, index, 100, "regwr 10 17170030", NULL, NULL) > 0);
      
      // read current temperature
      wd_read_temp(gl, index);
      
      // load calibration for board from file (for now...)
      char str[80];
      sprintf(str, "%s.cal", gl->board[index].name);
      int fh = open(str, O_RDONLY, 0644);
      if (fh > 0) {
         size = read(fh, &gl->board[index].calib, sizeof(CALIB_DATA));
         if (size != sizeof(CALIB_DATA)) {
            printf("Invalid calibration file size of \"%s\". Aborting.\n", str);
            return FAILURE;
         }
         
         if (memcmp(gl->board[index].calib.version_id, "CAL1", 4) != 0) {
            printf("Invalid calibration file format in \"%s\". Aborting.\n", str);
            return FAILURE;
         }

         if (fabs(gl->board[index].calib.sampling_frequency - gl->sampling_frequency) > 0.001) {
            printf("Warning: Calibration data is for %3g GSPS, running now at %3g GSPS\n",
                   gl->board[index].calib.sampling_frequency, gl->sampling_frequency);
         }

         if (fabs(gl->board[index].calib.temperature - gl->board[index].temperature) > 5) {
            printf("Warning: Calibration data is for %3g deg. C, running now at %3g deg. C\n",
                   gl->board[index].calib.temperature, gl->board[index].temperature);
         }

         // ## please remove after testing!!!
         /*
         for (int ch=0 ; ch < 16 ; ch++) {
            gl->board[index].calib.offset_range0[ch] = 0.45;
            gl->board[index].calib.offset_range1[ch] = 0;
            gl->board[index].calib.offset_range2[ch] = -0.45;
         }
          */

      } else {
         memset(gl->board[index].calib.wf_offset1, 0, sizeof(float)*16*1024);
         memset(gl->board[index].calib.wf_offset2, 0, sizeof(float)*16*1024);
         for (int ch=0 ; ch < 16 ; ch++) {
            for (int bin=0 ; bin<1024 ; bin++) {
               gl->board[index].calib.wf_gain1[ch][bin] = 1;
               gl->board[index].calib.wf_gain2[ch][bin] = 1;
            }
            gl->board[index].calib.offset_range0[ch] = 0.45;
            gl->board[index].calib.offset_range1[ch] = 0;
            gl->board[index].calib.offset_range2[ch] = -0.45;
         }
      }
   }
   
   if (gl->verbose_flag)
      printf("\n");
   
   return SUCCESS;
}

/*-----------------------------------------------------------------------------------------*/

double time_ms()
{
#ifdef _MSC_VER
   return GetTickCount();
#else
   struct timeval tv;
   gettimeofday(&tv, NULL);
   return tv.tv_sec*1000 + tv.tv_usec/1000.0;
#endif
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
   static float wf1[16][1024];

   // tag waveforms as invalid
   for (i=0 ; i<16 ; i++) {
      waveform[i][0]   = NANF;
      waveform[i][512] = NANF;
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
            
            /*
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
            */
            
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
                  waveform[i][0]   = NANF;
                  waveform[i][512] = NANF;
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
                  waveform[waveform_channel][i]       = (float)(data1 * (1 / 4096.0)); // 1V DRS range with 12 bits
                  waveform[waveform_channel][i+1]     = (float)(data2 * (1 / 4096.0));
               } else {
                  // second segment
                  waveform[waveform_channel][512+i]   = (float)(data1 * (1 / 4096.0));
                  waveform[waveform_channel][512+i+1] = (float)(data2 * (1 / 4096.0));
               }
            }
            
            // test if all waveforms are received
            for (i=0 ; i<16 ; i++)
               if (isnan(waveform[i][0]) || isnan(waveform[i][512]))
                   break;
            if (i == 16) {

               for (i=0 ; i<16 ; i++)
                  for (int j=0 ; j<1024 ; j++)
                     wf1[i][j] = waveform[i][j];

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
               
               // calibrate waveforms
               if (!gl->adc_flag) { // don't calibrate in ADC mode
                  
                  // cell-by-cell offset calibration
                  if (gl->ofs_calib1_flag) {
                     if (gl->rotate_flag) {
                        for (i=0 ; i<8 ; i++)
                           for (int j=0 ; j<1024 ; j++)
                              waveform[i][j] -= gl->board[b].calib.wf_offset1[i][(j+pe->drs0_trigger_cell) % 1024];
                        for (i=8 ; i<16 ; i++)
                           for (int j=0 ; j<1024 ; j++)
                              waveform[i][j] -= gl->board[b].calib.wf_offset1[i][(j+pe->drs1_trigger_cell) % 1024];
                     } else {
                        for (i=0 ; i<16 ; i++)
                           for (int j=0 ; j<1024 ; j++)
                              waveform[i][j] -= gl->board[b].calib.wf_offset1[i][j];
                     }
                  }
                  
                  // gain calibration
                  if (gl->gain_calib_flag) {
                     if (gl->rotate_flag) {
                        for (i=0 ; i<8 ; i++)
                           for (int j=0 ; j<1024 ; j++) {
                              if (waveform[i][j] > 0)
                                 waveform[i][j] /= gl->board[b].calib.wf_gain1[i][(j+pe->drs0_trigger_cell) % 1024];
                              else
                                 waveform[i][j] /= gl->board[b].calib.wf_gain2[i][(j+pe->drs0_trigger_cell) % 1024];
                           }
                        for (i=8 ; i<16 ; i++)
                           for (int j=0 ; j<1024 ; j++) {
                              if (waveform[i][j] > 0)
                                 waveform[i][j] /= gl->board[b].calib.wf_gain1[i][(j+pe->drs1_trigger_cell) % 1024];
                              else
                                 waveform[i][j] /= gl->board[b].calib.wf_gain2[i][(j+pe->drs1_trigger_cell) % 1024];
                           }
                     } else {
                        for (i=0 ; i<16 ; i++)
                           for (int j=0 ; j<1024 ; j++) {
                              if (waveform[i][j] > 0)
                                 waveform[i][j] /= gl->board[b].calib.wf_gain1[i][j];
                              else
                                 waveform[i][j] /= gl->board[b].calib.wf_gain2[i][j];
                           }
                     }
                  }

                  // start-to-end offset calibration
                  if (gl->ofs_calib2_flag) {
                     for (i=0 ; i<16 ; i++)
                        for (int j=0 ; j<1024 ; j++)
                           waveform[i][j] -= gl->board[b].calib.wf_offset2[i][j];
                  }
                  
                  // range calibration
                  if (gl->range_calib_flag) {
                     float ofs;
                     
                     for (i=0 ; i<16 ; i++) {
                        if (fabs(gl->board[b].range - (-0.45)) < 0.001)
                           ofs = gl->board[b].calib.offset_range0[i];
                        else if (fabs(gl->board[b].range) < 0.001)
                           ofs = gl->board[b].calib.offset_range1[i];
                        else if (fabs(gl->board[b].range - 0.45) < 0.001)
                           ofs = gl->board[b].calib.offset_range2[i];
                        else
                           ofs = 0;
                        for (int j=0 ; j<1024 ; j++)
                           waveform[i][j] -= ofs;
                     }
                  }

                  // remove spikes
                  if (gl->remove_spikes) {
                     remove_spikes(gl, pe->drs0_trigger_cell, waveform);
                     remove_spikes(gl, pe->drs1_trigger_cell, waveform+8);
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

int wd_calibrate(GLOBALS *gl, CALIB_PROGRESS *pr)
{
   float wfU[16][1024];
   WD2_EVENT eventHeader;
   char str[80];
   int i;
   
   /* turn off clock if it is on */
   if (gl->osctca_flag) {
      gl->osctca_flag = 0;
      for (int i=0 ; i<gl->n_boards ; i++)
         wd_set_osctca(gl, i);
   }
   
   if (pr->state == CS_FIRST_BOARD) {
      memset(pr, 0, sizeof(CALIB_PROGRESS));
      pr->state   = CS_FIRST_SAMPLE;
      pr->n_iter1 = 200;
      pr->n_iter2 = 200;
      pr->n_iter3 = 200;
      pr->n_iter4 = 200;
      pr->n_board = gl->n_boards;
      pr->i_board = 0;
   }

   if (pr->state == CS_FIRST_SAMPLE) {
      pr->progress = 0;
      pr->i_iter1  = 0;
      pr->i_iter2  = 0;
      pr->i_iter3  = 0;
      pr->i_iter4  = 0;
      pr->state    = CS_RUNNING;
   }

   //---- Primary Calibration ----
   
   if (pr->i_iter1 < pr->n_iter1) {

      // initialize data on first iteration
      if (pr->i_iter1 == 0) {
         gl->rotate_flag      = 0;
         gl->ofs_calib1_flag  = 0;
         gl->ofs_calib2_flag  = 0;
         gl->gain_calib_flag  = 0;
         gl->range_calib_flag = 0;
         gl->remove_spikes    = 0;
         
         pr->prev_range = gl->board[pr->i_board].range;
         gl->board[pr->i_board].range = 0; // range -0.5 ... + 0.5V
         wd_set_range(gl, pr->i_board);
         gl->mux_flag         = 1;
         gl->dcv_flag         = 1;
         gl->dcv              = 0;
         wd_set_fe(gl, pr->i_board);
         wd_set_dcv(gl, pr->i_board);
         wd_set_dcv_flag(gl, pr->i_board);
         
         pr->ave = new Averager(2, 8, 1024, pr->n_iter1);
      }

      pr->i_iter1++;
      
      for (i=0 ; i<10 ; i++) {
         wd_send(gl, pr->i_board, 100, "drsget\n", NULL, NULL);
         if (wd_read_waveform(gl, pr->i_board, 1000, &eventHeader, wfU) == SUCCESS)
            break;
      }
      assert(i < 10);
      
      sleep_ms(10);

      for (int ch=0 ; ch<16 ; ch++)
         for (int bin=0 ; bin<1024 ; bin++)
            pr->ave->Add(ch/8, ch%8, bin, wfU[ch][bin]);
      
      pr->progress = (double)(pr->i_iter1 + pr->i_iter2 + pr->i_iter3 + pr->i_iter4) /
                             (pr->n_iter1 + pr->n_iter2 + pr->n_iter3 + pr->n_iter4);
      
      // calibration finished
      if (pr->i_iter1 == pr->n_iter1) {
         for (int ch=0 ; ch<16 ; ch++)
            for (int bin=0 ; bin<1024 ; bin++)
               gl->board[pr->i_board].calib.wf_offset1[ch][bin] = (float)pr->ave->Median(ch/8, ch%8, bin);
         
         // ave->SaveNormalizedDistribution("wf.csv", 0);
      }

      return SUCCESS;
   }
   
   //---- Secondary Calibration
   
   if (pr->i_iter2 < pr->n_iter2) {
   
      // initialize data on first iteration
      if (pr->i_iter2 == 0) {
         pr->ave->Reset();
         gl->rotate_flag      = 1; // rotate waveforms
         gl->ofs_calib1_flag  = 1; // do 1st calibration
         gl->ofs_calib2_flag  = 0;
         gl->gain_calib_flag  = 0;
         gl->range_calib_flag = 0;
      }

      pr->i_iter2++;
      
      for (i=0 ; i<10 ; i++) {
         wd_send(gl, pr->i_board, 100, "drsget\n", NULL, NULL);
         if (wd_read_waveform(gl, pr->i_board, 1000, &eventHeader, wfU) == SUCCESS)
            break;
      }
      assert(i < 10);

      sleep_ms(10);
      
      for (int ch=0 ; ch<16 ; ch++)
         for (int bin=0 ; bin<1024 ; bin++)
            pr->ave->Add(ch/8, ch%8, bin, wfU[ch][bin]);
      
      pr->progress = (double)(pr->i_iter1 + pr->i_iter2 + pr->i_iter3 + pr->i_iter4) /
                             (pr->n_iter1 + pr->n_iter2 + pr->n_iter3 + pr->n_iter4);
      
      // calibration finished
      if (pr->i_iter2 == pr->n_iter2) {
         for (int ch=0 ; ch<16 ; ch++)
            for (int bin=0 ; bin<1024 ; bin++)
               gl->board[pr->i_board].calib.wf_offset2[ch][bin] = (float)pr->ave->Median(ch/8, ch%8, bin);
      }
      
      return SUCCESS;
   }
   
   //---- Positive Gain Calibration
   
   if (pr->i_iter3 < pr->n_iter3) {
      
      // initialize data on first iteration
      if (pr->i_iter3 == 0) {
         pr->ave->Reset();
         gl->rotate_flag      = 0;
         gl->ofs_calib1_flag  = 1; // do 1st calibration
         gl->ofs_calib2_flag  = 0;
         gl->gain_calib_flag  = 0;
         gl->range_calib_flag = 0;

         gl->mux_flag         = 1;
         gl->dcv_flag         = 1;
         gl->dcv              = 0.45;
         wd_set_fe(gl, pr->i_board);
         wd_set_dcv(gl, pr->i_board);
         wd_set_dcv_flag(gl, pr->i_board);
      }
      
      pr->i_iter3++;
      
      for (i=0 ; i<10 ; i++) {
         wd_send(gl, pr->i_board, 100, "drsget\n", NULL, NULL);
         if (wd_read_waveform(gl, pr->i_board, 1000, &eventHeader, wfU) == SUCCESS)
            break;
      }
      assert(i < 10);
      
      sleep_ms(10);
      
      for (int ch=0 ; ch<16 ; ch++)
         for (int bin=0 ; bin<1024 ; bin++)
            pr->ave->Add(ch/8, ch%8, bin, wfU[ch][bin]);
      
      pr->progress = (double)(pr->i_iter1 + pr->i_iter2 + pr->i_iter3 + pr->i_iter4) /
                             (pr->n_iter1 + pr->n_iter2 + pr->n_iter3 + pr->n_iter4);
      
      // calibration finished
      if (pr->i_iter3 == pr->n_iter3) {
         for (int ch=0 ; ch<16 ; ch++)
            for (int bin=0 ; bin<1024 ; bin++)
               gl->board[pr->i_board].calib.wf_gain1[ch][bin] = pr->ave->Median(ch/8, ch%8, bin) / 0.45;
      }
      
      return SUCCESS;
   }

   //---- Negative Gain Calibration
   
   if (pr->i_iter4 < pr->n_iter4) {
      
      // initialize data on first iteration
      if (pr->i_iter4 == 0) {
         pr->ave->Reset();
         gl->rotate_flag      = 0;
         gl->ofs_calib1_flag  = 1; // do 1st calibration
         gl->ofs_calib2_flag  = 0;
         gl->gain_calib_flag  = 0;
         gl->range_calib_flag = 0;

         gl->dcv              = -0.45;
         wd_set_dcv(gl, pr->i_board);
      }
      
      pr->i_iter4++;
      
      for (i=0 ; i<10 ; i++) {
         wd_send(gl, pr->i_board, 100, "drsget\n", NULL, NULL);
         if (wd_read_waveform(gl, pr->i_board, 1000, &eventHeader, wfU) == SUCCESS)
            break;
      }
      assert(i < 10);
      
      sleep_ms(10);
      
      for (int ch=0 ; ch<16 ; ch++)
         for (int bin=0 ; bin<1024 ; bin++)
            pr->ave->Add(ch/8, ch%8, bin, wfU[ch][bin]);
      
      pr->progress = (double)(pr->i_iter1 + pr->i_iter2 + pr->i_iter3 + pr->i_iter4) /
                             (pr->n_iter1 + pr->n_iter2 + pr->n_iter3 + pr->n_iter4);
      
      // calibration finished
      if (pr->i_iter4 == pr->n_iter4) {
         for (int ch=0 ; ch<16 ; ch++)
            for (int bin=0 ; bin<1024 ; bin++)
               gl->board[pr->i_board].calib.wf_gain2[ch][bin] = pr->ave->Median(ch/8, ch%8, bin) / -0.45;
         
         delete pr->ave;
         pr->ave = NULL;
      }
      
      return SUCCESS;
   }
   
   // reset board
   gl->dcv = 0;
   gl->dcv_flag = 0;
   wd_set_dcv(gl, pr->i_board);

   gl->rotate_flag      = 1;
   gl->ofs_calib1_flag  = 1;
   gl->ofs_calib2_flag  = 1;
   gl->gain_calib_flag  = 1;
   gl->range_calib_flag = 0;
   gl->remove_spikes    = 0;

   // measure offset without DCV at different ranges
   assert(wd_send(gl, pr->i_board, 100, "calbuf off", NULL, NULL) > 0);    // disable BUFFER_CTRL
   assert(wd_send(gl, pr->i_board, 100, "feset all 82", NULL, NULL) > 0);  // gain 1, PZC off, MUX off

   // Range -0.45
   gl->board[pr->i_board].range = -0.45;
   wd_set_range(gl, pr->i_board);
   
   for (int i=0 ; i<10 ; i++) {
      wd_send(gl, pr->i_board, 100, "drsget\n", NULL, NULL);
      if (wd_read_waveform(gl, pr->i_board, 1000, &eventHeader, wfU) != SUCCESS)
         i--;
      sleep_ms(10);
   }
   
   for (int ch=0 ; ch<16 ; ch++) {
      float sum = 0;
      for (int i=10 ; i<1020 ; i++)
         sum += wfU[ch][i];
      gl->board[pr->i_board].calib.offset_range0[ch] = sum / 1010;
      // gl->board[pr->i_board].calib.offset_range0[ch] = 0.45;
   }
   
   // Range 0
   gl->board[pr->i_board].range = 0;
   wd_set_range(gl, pr->i_board);
   
   for (int i=0 ; i<10 ; i++) {
      wd_send(gl, pr->i_board, 100, "drsget\n", NULL, NULL);
      if (wd_read_waveform(gl, pr->i_board, 1000, &eventHeader, wfU) != SUCCESS)
         i--;
      sleep_ms(10);
   }
   
   for (int ch=0 ; ch<16 ; ch++) {
      float sum = 0;
      for (int i=10 ; i<1020 ; i++)
         sum += wfU[ch][i];
      gl->board[pr->i_board].calib.offset_range1[ch] = sum / 1010;
      // gl->board[pr->i_board].calib.offset_range1[ch] = 0;
   }

   // Range 0.45
   gl->board[pr->i_board].range = 0.45;
   wd_set_range(gl, pr->i_board);
   
   for (int i=0 ; i<10 ; i++) {
      wd_send(gl, pr->i_board, 100, "drsget\n", NULL, NULL);
      if (wd_read_waveform(gl, pr->i_board, 1000, &eventHeader, wfU) != SUCCESS)
         i--;
      sleep_ms(10);
   }
   
   for (int ch=0 ; ch<16 ; ch++) {
      float sum = 0;
      for (int i=10 ; i<1020 ; i++)
         sum += wfU[ch][i];
      gl->board[pr->i_board].calib.offset_range2[ch] = sum / 1010;
      // gl->board[pr->i_board].calib.offset_range2[ch] = 0.45;
   }

   // set everything back to normal values
   gl->board[pr->i_board].range = pr->prev_range;
   gl->mux_flag                 = 0;
   gl->dcv_flag                 = 0;
   gl->dcv                      = 0;
   wd_set_fe(gl, pr->i_board);
   wd_set_dcv(gl, pr->i_board);
   wd_set_dcv_flag(gl, pr->i_board);
   wd_set_range(gl, pr->i_board);

   // save calibration
   memcpy(gl->board[pr->i_board].calib.version_id, "CAL1", 4);
   gl->board[pr->i_board].calib.sampling_frequency = gl->sampling_frequency;
   gl->board[pr->i_board].calib.temperature = gl->board[pr->i_board].temperature;
   
   sprintf(str, "%s.cal", gl->board[pr->i_board].name);
   pr->fh = open(str, O_WRONLY | O_CREAT, 0644);
   assert(pr->fh > 0);
   assert(write(pr->fh, &gl->board[pr->i_board].calib, sizeof(CALIB_DATA)) == sizeof(CALIB_DATA));
   close(pr->fh);

   // switch to next board
   pr->i_board++;
   pr->state = CS_FIRST_SAMPLE;
   pr->progress = 1;
   
   if (pr->i_board == pr->n_board) {
      pr->state = CS_INACTIVE;
      gl->rotate_flag = 1;
      gl->ofs_calib1_flag  = 1;
      gl->ofs_calib2_flag  = 1;
      gl->gain_calib_flag  = 1;
      gl->range_calib_flag = 1;
      gl->remove_spikes    = 1;
   }

   return SUCCESS;
}

/*-----------------------------------------------------------------------------------------*/

int histo[50];

void remove_spikes(GLOBALS *gl, short trigger_cell, float wf[][1024])
{
/*
   Remove a specific kind of spike on DRS4.
   
   This spike has some specific features, namely:
     - Common on all the channels on a chip
     - Constant heigh and width
     - Two spikes per channel
     - Symmetric to cell #0.
   
 
   This is not general purpose spike-removing function.
*/
 
   int i, j, k, l;
   double hp, x, y;
   int sp[8][10];
   int rsp[10], rot_sp[10];
   int n_sp[8], n_rsp;
   int  nNeighbor, nSymmetric;
   float cwf[16][1024];

   /*
   FILE *f = fopen("wf.csv", "wt");
   fprintf(f, "tc=%d\n", trigger_cell);
   fprintf(f, "i, CH0, CH1, CH2, CH3, CH4, CH5, CH6, CH7\n");
   for (j=0 ; j<1024 ; j++) {
      fprintf(f, "%d, ", j);
      for (i=0 ; i<8 ; i++)
         fprintf(f, "%0.3lf, ", wf[i][j]);
      fprintf(f, "\n");
   }
   fclose(f);
   */
   
   /* rotate waveform back relative to cell #0 */
   if (gl->rotate_flag) {
      for (i=0 ; i<8 ; i++)
         for (j=0 ; j<1024 ; j++)
            cwf[i][(j+trigger_cell) % 1024] = wf[i][j];
   } else {
      for (i=0 ; i<8 ; i++)
         for (j=0 ; j<1024 ; j++)
            cwf[i][j] = wf[i][j];
   }

   memset(sp, 0, sizeof(sp));
   memset(n_sp, 0, sizeof(n_sp));
   memset(rsp, 0, sizeof(rsp));
   n_rsp = 0;
   
   /* find spikes with special high-pass filter, skip last values */
   for (j=0 ; j<1020 ; j++) {
      for (i=1 ; i<4 ; i++) { // TBD: temporary fix for bad channels 1,5,6,7
         hp = -cwf[i][j] + cwf[i][(j+1)%1024]+cwf[i][(j+2)%1024] - cwf[i][(j+3) % 1024];
         if (hp > 0.020) {
            if (n_sp[i] < 10) // record maximum of 10 spikes
               sp[i][n_sp[i]++] = j;
            else
               return;        // too many spikes -> something wrong
         }
      }
   }

   /* find spikes at cell #0 and #1023 */
   /*
   for (i=0 ; i<8 ; i++) {
      if (wf[i][0]+wf[i][1]-2*wf[i][2] > 0.020) {
         if (n_sp[i] < 10)
            sp[i][n_sp[i]++] = 0;
      }
      if (-2*wf[i][1021]+wf[i][1022]+wf[i][1023] > 0.020) {
         if (n_sp[i] < 10)
            sp[i][n_sp[i]++] = 1020;
      }
   }
   */
   
   /* go through all spikes and look for symmetric spikes and neighbors */
   for (i=0 ; i<8 ; i++) {
      for (j=0 ; j<n_sp[i] ; j++) {
         /* check if this spike has a symmetric partner in any channel */
         for (k=nSymmetric=0 ; k<8 ; k++) {
            for (l=0 ; l<n_sp[k] ; l++)
               if (sp[i][j] == (1020-sp[k][l]+1024) % 1024) {
                  nSymmetric++;
                  break;
               }
         }
         
         /* check if this spike has same spike in any other channels */
         for (k=nNeighbor=0 ; k<8 ; k++)
            if (i != k) {
               for (l=0 ; l<n_sp[k] ; l++)
                  if (sp[i][j] == sp[k][l]) {
                     nNeighbor++;
                     break;
                  }
            }
         
         if (nSymmetric + nNeighbor >= 2) {
            /* if at least two matching spikes, treat this as a real spike */
            for (k=0 ; k<n_rsp ; k++)
               if (rsp[k] == sp[i][j])
                  break;
            if (n_rsp < 10 && k == n_rsp)
               rsp[n_rsp++] = sp[i][j];
         }
      }
   }
   
   /* rotate spikes according to trigger cell */
   if (gl->rotate_flag) {
      for (i=0 ; i<n_rsp ; i++)
         rot_sp[i] = (rsp[i] - trigger_cell + 1024) % 1024;
   } else {
      for (i=0 ; i<n_rsp ; i++)
         rot_sp[i] = rsp[i];
   }
   
   /* recognize spikes if at least one channel has it */
   for (k=0 ; k<n_rsp ; k++) {
      for (i=0 ; i<8 ; i++) {
         
         if (k < n_rsp-1 && rsp[k] == 0 && rsp[k+1] == 1020) {
            /* remove double spike */
            j = rot_sp[k] > rot_sp[k+1] ? rot_sp[k+1] : rot_sp[k];
            x = wf[i][(j+1) % 1024];
            y = wf[i][(j+6) % 1024];
            if (fabs(x-y) < 0.015) {
               wf[i][(j+2) % 1024] = (float)(x + 1*(y-x)/5);
               wf[i][(j+3) % 1024] = (float)(x + 2*(y-x)/5);
               wf[i][(j+4) % 1024] = (float)(x + 3*(y-x)/5);
               wf[i][(j+5) % 1024] = (float)(x + 4*(y-x)/5);
            } else {
               wf[i][(j+2) % 1024] -= 0.0148f;
               wf[i][(j+3) % 1024] -= 0.0148f;
               wf[i][(j+4) % 1024] -= 0.0148f;
               wf[i][(j+5) % 1024] -= 0.0148f;
            }
         } else {
            /* remove single spike */
            x = wf[i][rot_sp[k]];
            y = wf[i][(rot_sp[k]+3) % 1024];
            
            if (fabs(x-y) < 0.010) {
               wf[i][(rot_sp[k]+1) % 1024] = (float)(x + 1*(y-x)/3);
               wf[i][(rot_sp[k]+2) % 1024] = (float)(x + 2*(y-x)/3);
            } else {
               wf[i][(rot_sp[k]+1) % 1024] -= 0.009f;
               wf[i][(rot_sp[k]+2) % 1024] -= 0.009f;
            }
         }
      }
      if (k < n_rsp-1 && rsp[k] == 0 && rsp[k+1] == 1020)
         k++; // skip second half of double spike
   }
}

/*-----------------------------------------------------------------------------------------*/

void wd_read_temp(GLOBALS *gl, int index)
{
   static time_t last[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
   time_t now;
   
   time(&now);
   if (now > last[index] + 10) {
         int size;
         char str[80];
         size = sizeof(str);
         assert(wd_send(gl, index, 100, "temp", str, &size) > 0);
         gl->board[index].temperature = atof(str+5);

      last[index] = now;
   }
      
}

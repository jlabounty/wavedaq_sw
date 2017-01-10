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

#include "mxml.h"
#include "strlcpy.h"
#include "averager.h"
#include "wds.h"
#include "register_map.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <errno.h>

#ifdef _MSC_VER
#include <windows.h>
#include <io.h>
#include <time.h>
#include <float.h>
#include <direct.h>

union { unsigned int i ; float f; } _nanf = { 0x7fc00000 };
#define NANF (_nanf.f)

#define getcwd(x,y) _getcwd(x,y)
#define mkdir(x,h) _mkdir(x)
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
#include <time.h>

#define NANF nanf("")
#endif

#ifdef __APPLE__
#include <arpa/inet.h>
#include <netdb.h>
#include <net/if.h>

#define NANF nanf("")
#endif

#ifndef MAX
#define MAX(x,y) ((x>y)?(x):(y))
#endif

#define WD2_CMD_PORT   3000

#pragma pack(1)

#define UDP_PROTOCOL_VERSION 3

typedef struct {
   unsigned char  protocol_version;
   unsigned char  board_version;
   unsigned short board_id;
   unsigned char  crate_id;
   unsigned char  slot_id;
   unsigned char  adc_and_channel_info;
   unsigned char  channel_segment_number;
   unsigned int   event_number;
   unsigned short sampling_frequency;
   unsigned short number_of_samples;
   unsigned short trigger_number;
   unsigned short drs0_trigger_cell;
   unsigned short drs1_trigger_cell;
   unsigned short trigger_type;
   unsigned short temperature;
   unsigned int   reserved;
   unsigned short packet_sequence_number;
} WD2_FRAME_HEADER;

/*-----------------------------------------------------------------------------------------*/

void remove_spikes(GLOBALS *gl, short trigger_cell, float wf[][1024]);

/*-----------------------------------------------------------------------------------------*/

void GetTimeStamp(TIMESTAMP &ts)
{
#ifdef _MSC_VER
   SYSTEMTIME t;
   static unsigned int ofs = 0;
   
   GetLocalTime(&t);
   if (ofs == 0)
      ofs = timeGetTime() - t.wMilliseconds;
   ts.Year         = t.wYear;
   ts.Month        = t.wMonth;
   ts.Day          = t.wDay;
   ts.Hour         = t.wHour;
   ts.Minute       = t.wMinute;
   ts.Second       = t.wSecond;
   ts.Milliseconds = (timeGetTime() - ofs) % 1000;
#else
   struct timeval t;
   struct tm *lt;
   time_t now;
   
   gettimeofday(&t, NULL);
   time(&now);
   lt = localtime(&now);
   
   ts.Year         = lt->tm_year+1900;
   ts.Month        = lt->tm_mon+1;
   ts.Day          = lt->tm_mday;
   ts.Hour         = lt->tm_hour;
   ts.Minute       = lt->tm_min;
   ts.Second       = lt->tm_sec;
   ts.Milliseconds = t.tv_usec/1000;
#endif /* OS_UNIX */
}

/*-----------------------------------------------------------------------------------------*/

int wd_send(GLOBALS *gl, int b, int timeout_ms, const char *str, char *result, int *size)
{
   size_t n;
   int    i;
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
   if (strchr(gl->board[b].name, '.'))
      strlcpy(prompt, " > ", sizeof(prompt));
   else {
      strlcpy(prompt, gl->board[b].name, sizeof(prompt));
      strlcat(prompt, " > ", sizeof(prompt));
   }
   
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

void wd_set_fe(GLOBALS *gl, int index, int channel)
{
   char str[256];
   int byte = 0;
   
   if (gl->demo_flag)
      return;
   
   // channel == -1 means all channels
   if (channel == -1) {
      for (channel=0 ; channel<WD_N_CHANNELS ; channel++)
         wd_set_fe(gl, index, channel);
      return;
   }
   
   if (gl->verbose_flag)
      printf("Set gain channel %d to %g, PZC %d, mux %d\n", channel, gl->board[index].gain[channel], gl->board[index].pzc[channel], gl->mux_flag);

   if (gl->board[index].revision == WD_REV_D) {
      // set input configuration
      if (gl->board[index].gain[channel] == 1)
         byte = 0x02;
      else if (gl->board[index].gain[channel] == 10)
         byte = 0x0a;
      else if (gl->board[index].gain[channel] == 100)
         byte = 0x2A;
      else
         byte = 0x02;
      
      if (!gl->board[index].pzc[channel]) // pole zero cancellation off (bit=1)
         byte |= 0x80;
      
      if (gl->mux_flag)
         byte |= 0x01;
   }
   
   if (gl->board[index].revision == WD_REV_E) {
      // set input configuration according to FE_bits_2E.xlsx
      if (gl->board[index].gain[channel] == 0.5)
         byte = 0x06;
      else if (gl->board[index].gain[channel] == 1)
         byte = 0x02;
      else if (gl->board[index].gain[channel] == 2.5)
         byte = 0x1A;
      else if (gl->board[index].gain[channel] == 5)
         byte = 0x16;
      else if (gl->board[index].gain[channel] == 10)
         byte = 0x12;
      else if (gl->board[index].gain[channel] == 25)
         byte = 0x5A;
      else if (gl->board[index].gain[channel] == 50)
         byte = 0x56;
      else if (gl->board[index].gain[channel] == 100)
         byte = 0x52;
      else
         byte = 0x02;
      
      if (!gl->board[index].pzc[channel]) // pole zero cancellation off (bit=1)
         byte |= 0x100;
      
      if (gl->mux_flag)
         byte |= 0x01;
   }

   sprintf(str, "feset %d %02X", channel, byte);
   assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
   
   // set MUX of channel 9
   if (gl->mux_flag) {
      if (gl->verbose_flag)
         printf("Set channel 9 input to LMK output\n");;
      assert(wd_send(gl, index, 100, "calclk tca a", NULL, NULL) > 0);
      assert(wd_send(gl, index, 100, "calclk tca b", NULL, NULL) > 0);
   } else {
      if (gl->verbose_flag)
         printf("Set channel 9 input to TCA output\n");;
      assert(wd_send(gl, index, 100, "calclk lmk a", NULL, NULL) > 0);
      assert(wd_send(gl, index, 100, "calclk lmk b", NULL, NULL) > 0);
   }
   
   // adjust range offset which depends on gain
   wd_set_range(gl, index);
}

/*-----------------------------------------------------------------------------------------*/

void wd_set_pzc_level(GLOBALS *gl, int index)
{
   char str[256];
   int  l;
   
   int level[] = {0, 500, 1000, 1500, 1800, 2000, 2500};
   if (gl->demo_flag)
      return;
   
   l = gl->board[index].pzc_level;
   if (l < 1)
      l = 1;
   if (l > sizeof(level)/sizeof(int))
      l = sizeof(level)/sizeof(int);
   
   if (gl->verbose_flag)
      printf("Set PZC level = %d\n", l);
   
   if (gl->board[index].revision == WD_REV_E) {
      sprintf(str, "dacset pzclevel %d", level[l-1]);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
   }
}

/*-----------------------------------------------------------------------------------------*/

void wd_set_trigger_level(GLOBALS *gl, int index, int channel)
{
   char str[256];

   if (gl->demo_flag)
      return;

   if (gl->verbose_flag) {
      if (channel != -1)
         printf("Set trigger level channel %d = %d mV\n", channel, (int)(gl->board[index].trigger_level[channel]*1000));
      else
         printf("Set trigger level all channels = %d mV\n", (int)(gl->board[index].trigger_level[0]*1000));
   }
   
   if (gl->board[index].revision == WD_REV_D) {
      sprintf(str, "dacset tlevel0 %d", (int)(gl->board[index].trigger_level[channel]*500+900));
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      sprintf(str, "dacset tlevel1 %d", (int)(gl->board[index].trigger_level[channel]*500+900));
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      sprintf(str, "dacset tlevel2 %d", (int)(gl->board[index].trigger_level[channel]*500+900));
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      sprintf(str, "dacset tlevel3 %d", (int)(gl->board[index].trigger_level[channel]*500+900));
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
   }
   
   if (gl->board[index].revision == WD_REV_E) {
      if (channel == -1) {
         sprintf(str, "dacset tlevelall %d", (int)(gl->board[index].trigger_level[0]*500+900));
         assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      } else {
         sprintf(str, "dacset tlevel%d %d", channel, (int)(gl->board[index].trigger_level[channel]*500+900));
         assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      }
   }
}

/*-----------------------------------------------------------------------------------------*/

void wd_set_trigger_mode(GLOBALS *gl, int index)
{
   char str[256];
   int delay;
   
   if (gl->demo_flag)
      return;
   
   if (gl->verbose_flag)
      printf("Set trigger mode %d, delay = %1.0lf, source = %s\n", gl->trigger_mode,
             gl->board[index].trigger_delay,
             gl->trigger_source == WD_TS_INTERNAL ? "internal" : "external");

   if (gl->board[index].trigger_delay == 0)
      delay = 0x100;
   else {
      delay = (int)(gl->board[index].trigger_delay / 450 * 255);
      if (delay > 255)
         delay = 255;
      if (delay < 0)
         delay = 0;
   }
   
   // enable local trigger
   if (gl->trigger_mode == WD_TM_NORMAL) {
      // trigger_cfg_or
      sprintf(str, "regwr %02x %s", REG_TRIGGER_CFG_A_OFFSET, gl->board[index].trigger_mask);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
 
      // trigger_enable, trigger_falling_edge
      sprintf(str, "regwr %02x 000C%04x", REG_TRIGGER_CFG_OFFSET, delay);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
   } else {
      // disable all trigger
      sprintf(str, "regwr %02x 00000000", REG_TRIGGER_CFG_A_OFFSET);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      
      sprintf(str, "regwr %02x 0000%04x", REG_TRIGGER_CFG_OFFSET, delay);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
   }
}

/*-----------------------------------------------------------------------------------------*/

void wd_set_osctca(GLOBALS *gl, int index)
{
   char str[80];
   
   if (gl->demo_flag)
      return;
   
   if (gl->verbose_flag)
      printf("Set TCA oscillator %d\n", gl->osctca_flag);

   if (gl->osctca_flag) {
      assert(wd_send(gl, index, 100, "calosc on", NULL, NULL) > 0);  // enable TCA_CTRL
   } else {
      assert(wd_send(gl, index, 100, "calosc off", NULL, NULL) > 0);
   }

   if (gl->board[index].revision == WD_REV_E) {
      if (gl->osctca_flag) {
         if (gl->osctca_delay != 0) {
            if (gl->osctca_delay > 0) {
               // delay channel 6
               sprintf(str, "lmksetch 6 3 2 %d 1", gl->osctca_delay);
               assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
               
               sprintf(str, "lmksetch 0 1 %d 0 1", gl->lmk_divider);
               assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
            } else {
               // delay channel 0
               sprintf(str, "lmksetch 6 1 2 0 1");
               assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
               
               sprintf(str, "lmksetch 0 3 %d %d 1", gl->lmk_divider, -gl->osctca_delay);
               assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
            }
         } else {
            sprintf(str, "lmksetch 6 1 2 0 1");
            assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
            sprintf(str, "lmksetch 0 1 %d 0 1", gl->lmk_divider);
            assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
         }
      } else {
         assert(wd_send(gl, index, 100, "lmksetch 6 1 2 0 0", NULL, NULL) > 0);
      }
   }
}

/*-----------------------------------------------------------------------------------------*/

void wd_set_clocksource(GLOBALS *gl, int index)
{
   char str[80];
   
   if (gl->demo_flag)
      return;
   
   if (gl->verbose_flag) {
      if (gl->clock_source == 1)
         printf("Set clock source to external\n");
      else
         printf("Set clock source to internal\n");
   }
   
   if (gl->clock_source == 1) {
      // switch clock source
      assert(wd_send(gl, index, 100, "regclr c 20000", NULL, NULL) > 0);
      
      // enable LMK outputs 1 & 2 for channel 9
      sprintf(str, "regwr %02x 00030101", REG_LMK_1_OFFSET);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      sprintf(str, "regwr %02x 00030102", REG_LMK_1_OFFSET);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
   } else {
      assert(wd_send(gl, index, 100, "regset c 20000", NULL, NULL) > 0);

      sprintf(str, "regwr %02x 00020101", REG_LMK_1_OFFSET);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      sprintf(str, "regwr %02x 00020102", REG_LMK_1_OFFSET);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
   }
}

/*-----------------------------------------------------------------------------------------*/

void wd_set_channel9(GLOBALS *gl, int index)
{
   char str[80];
   
   if (gl->demo_flag)
      return;
   
   if (gl->verbose_flag) {
      if (gl->read_channel9)
         printf("Enable channel 9 readout\n");
      else
         printf("Disable channel 9 readout\n");
   }
   
   if (gl->read_channel9)
      sprintf(str, "regwr %02x 01FF01FF", REG_CHANNEL_TX_EN_OFFSET);
   else
      sprintf(str, "regwr %02x 00FF00FF", REG_CHANNEL_TX_EN_OFFSET);
   
   assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
}

/*-----------------------------------------------------------------------------------------*/

void wd_set_sampling_frequency(GLOBALS *gl, int index)
{
   char str[80];
   
   if (gl->demo_flag) {
      gl->actual_sampling_frequency = gl->nominal_sampling_frequency;
      return;
   }
   
   // 200 MHz LMK bus frequency
   gl->lmk_divider = (int) (200.0 / gl->nominal_sampling_frequency * 2.048 + 0.5);
   
   // calculate real frequency
   gl->actual_sampling_frequency = (float)(200.0 / gl->lmk_divider * 2.048);
   
   // set sampling frequency
   if (gl->verbose_flag)
      printf("Set sampling frequency to %1.3lg GSPS (%1.4lg GSPS)\n", gl->nominal_sampling_frequency,
             gl->actual_sampling_frequency);
   
   sprintf(str, "lmksetch 0 1 %d 0 1", gl->lmk_divider);
   assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
   
   // turn off time calibration if calibrated frequency is different
   if (fabs(gl->actual_sampling_frequency - gl->board[index].tcalib.sampling_frequency) > 0.001) {
      gl->time_calib1_flag = 0;
      gl->time_calib2_flag = 0;
   }
}

/*-----------------------------------------------------------------------------------------*/

void wd_set_range(GLOBALS *gl, int index)
{
   char str[256];
   
   if (gl->demo_flag)
      return;

   if (gl->verbose_flag)
      printf("Set range = %g V\n", gl->board[index].range);
   
   if (gl->board[index].revision == WD_REV_D) {
      gl->board[index].range_ofs = 0;
      if (fabs(gl->board[index].range) < 0.001) {                  // -0.5 ... +0.5
         if (gl->board[index].gain[0] == 2)
            sprintf(str, "dacset ofs %d", 1270);
         else
            sprintf(str, "dacset ofs %d", 1300);
      } else if (fabs(gl->board[index].range - (-0.45)) < 0.001) { // -1 ... 0
         if (gl->board[index].gain[0] == 2)
            sprintf(str, "dacset ofs %d", 1640);
         else
            sprintf(str, "dacset ofs %d", 2000);
      } else if (fabs(gl->board[index].range - 0.45) < 0.001) {    // 0 ... +1
         if (gl->board[index].gain[0] == 2)
            sprintf(str, "dacset ofs %d", 890);
         else
            sprintf(str, "dacset ofs %d", 580);
      }
   } else if (gl->board[index].revision == WD_REV_E) {
      if (fabs(gl->board[index].range) < 0.001) {                  // -0.5 ... +0.5
         gl->board[index].range_ofs = 0.700;
      } else if (fabs(gl->board[index].range - (-0.45)) < 0.001) { // -1 ... 0
         gl->board[index].range_ofs = 1.230;
      } else if (fabs(gl->board[index].range - 0.45) < 0.001) {    // 0 ... +1
         gl->board[index].range_ofs = 0.140;
      }
      sprintf(str, "dacset ofs %d", (int)(gl->board[index].range_ofs*1000));
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
      printf("Set DC voltage = %g V\n", gl->dc_offset);
   
   sprintf(str, "dacset caldc %d", (int)(1280-gl->dc_offset*1000)); // shift by 1.28V
   assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
}

/*-----------------------------------------------------------------------------------------*/

// general function working both for revisitn 2D and 2E
void wd_set_dc_offset(GLOBALS *gl, int index)
{
   char str[256];
   
   if (gl->demo_flag)
      return;

   if (gl->board[index].revision == WD_REV_D) {
      wd_set_dcv_flag(gl, index);
      wd_set_dcv(gl, index);
   }

   if (gl->board[index].revision == WD_REV_E) {
      if (gl->verbose_flag)
         printf("Set offset voltage = %g V\n", gl->dc_offset);
      
      sprintf(str, "dacset ofs %d", (int)((gl->board[index].range_ofs+gl->dc_offset*1.09)*1000));
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
   }
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

   if (gl->demo_flag) {
      gl->nominal_sampling_frequency = gl->actual_sampling_frequency = 5;
      return SUCCESS;
   }
   
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
      
      // set LED red
      assert(wd_send(gl, index, 100, "ledset r", NULL, NULL) > 0);

      // set dbglevel none
      assert(wd_send(gl, index, 100, "dbglvl none", NULL, NULL) > 0);

      // get board info
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

      // get board type
      size = sizeof(reply);
      sprintf(str, "regrd stat %X", REG_HW_VERSION_OFFSET);
      assert(wd_send(gl, index, 1000, str, reply, &size) > 0);
      if (strlen(reply) == 25) {
         unsigned int dw = strtol(reply+15, NULL, 16);
         gl->board[index].type     = (dw >> 8) & 0xFF; // WD2
         gl->board[index].revision = dw & 0xFF;        // A:0, B:1, C:2, D:3, E:4
         gl->board[index].type     = 2; //## temporary fix until firmware is ready
         gl->board[index].revision = 4;
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
      
      wd_set_fe(gl, index, -1);

      // trun on comparator power
      assert(wd_send(gl, index, 100, "pwrcmp on", NULL, NULL) > 0);

      // enable all comparators
      sprintf(str, "regwr %02x 0000FFFF", REG_TRIGGER_COMP_MASK_OFFSET);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      
      // set simple trigger scheme
      sprintf(str, "regwr %02x 00000000", REG_TRIGGER_SCHEME_SELECT_OFFSET);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);

      // set bias
      assert(wd_send(gl, index, 100, "dacset bias 700", NULL, NULL) > 0);

      // set ROFS
      assert(wd_send(gl, index, 100, "dacset rofs 1550", NULL, NULL) > 0);
      
      // set caldc to zero
      assert(wd_send(gl, index, 100, "dacset caldc 1280", NULL, NULL) > 0);

      // set DRS readout mode to ROI and ADC ISERDES delay
      sprintf(str, "regwr %02x 1F1F0030", REG_CONTROL_OFFSET);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);

      // set LMK registers to their defaults, see "LMK regs.xls"
      sprintf(str, "regwr %02x 00032800", REG_LMK_0_OFFSET);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      sprintf(str, "regwr %02x 00020101", REG_LMK_1_OFFSET);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      sprintf(str, "regwr %02x 00020102", REG_LMK_2_OFFSET);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      sprintf(str, "regwr %02x 029900AD", REG_LMK_13_OFFSET);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      sprintf(str, "regwr %02x 0830140E", REG_LMK_14_OFFSET);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);
      sprintf(str, "regwr %02x D800280F", REG_LMK_15_OFFSET);
      assert(wd_send(gl, index, 100, str, NULL, NULL) > 0);

      // switch channel 9 to LMK input
      assert(wd_send(gl, index, 100, "calclk lmk a", NULL, NULL) > 0);
      assert(wd_send(gl, index, 100, "calclk lmk b", NULL, NULL) > 0);

      for (int channel=0 ; channel<WD_N_INPUT_CHN ; channel++)
         wd_set_trigger_level(gl, index, channel);
      wd_set_range(gl, index);
      wd_set_trigger_mode(gl, index);
      wd_set_osctca(gl, index);
      wd_set_clocksource(gl, index);
      wd_set_channel9(gl, index);
      wd_read_board_status(gl, index);
      wd_set_dcv_flag(gl, index);
      wd_set_dc_offset(gl, index);

      // set LED green
      assert(wd_send(gl, index, 100, "ledset g", NULL, NULL) > 0);
      
      // load voltage calibration for board from file (for now...)
      char str[80], dir[256];
      getcwd(dir, sizeof(dir));
      strcat(dir, "/calib");
      sprintf(str, "%s/%s.vcal", dir, gl->board[index].name);
      int fh = open(str, O_RDONLY, 0644);
      if (fh > 0) {
         size = read(fh, &gl->board[index].vcalib, sizeof(VCALIB_DATA));
         if (size != sizeof(VCALIB_DATA)) {
            printf("Invalid voltage calibration file size of %s. Aborting.\n", str);
            return FAILURE;
         }
         if (memcmp(gl->board[index].vcalib.version_id, "CAL1", 4) != 0) {
            printf("Invalid voltage calibration file format in %s. Aborting.\n", str);
            return FAILURE;
         }
         if (fabs(gl->board[index].vcalib.temperature - gl->board[index].temperature) > 5) {
            printf("Warning: Voltage calibration data in \"%s/%s\" is for %3g deg. C, running now at %3g deg. C\n",
                   dir, str, gl->board[index].vcalib.temperature, gl->board[index].temperature);
         }
         
         // set sampling frequency from calibration data
         if (gl->actual_sampling_frequency == 0) {
            gl->actual_sampling_frequency = gl->board[index].vcalib.sampling_frequency;
            gl->nominal_sampling_frequency = gl->actual_sampling_frequency;
         } else {
            if (fabs(gl->board[index].vcalib.sampling_frequency - gl->actual_sampling_frequency) > 0.001) {
               printf("Warning: Voltage calibration data in \"%s/%s\" is for %3g GSPS, running now at %3g GSPS\n",
                      dir, str, gl->board[index].vcalib.sampling_frequency, gl->actual_sampling_frequency);
            }
         }
         close(fh);

      } else {
         memset(gl->board[index].vcalib.wf_offset1, 0, sizeof(float)*16*1024);
         memset(gl->board[index].vcalib.wf_offset2, 0, sizeof(float)*16*1024);
         for (int ch=0 ; ch < WD_N_CHANNELS ; ch++) {
            for (int bin=0 ; bin<1024 ; bin++) {
               gl->board[index].vcalib.wf_gain1[ch][bin] = 1;
               gl->board[index].vcalib.wf_gain2[ch][bin] = 1;
            }
            gl->board[index].vcalib.drs_offset_range0[ch] = 0.45f;
            gl->board[index].vcalib.drs_offset_range1[ch] = 0;
            gl->board[index].vcalib.drs_offset_range2[ch] = -0.45f;

            gl->board[index].vcalib.adc_offset_range0[ch] = 0;
            gl->board[index].vcalib.adc_offset_range1[ch] = 0;
            gl->board[index].vcalib.adc_offset_range2[ch] = 0;
         }
      }

      // load timing calibration for board from file (for now...)
      sprintf(str, "%s/%s.tcal", dir, gl->board[index].name);
      fh = open(str, O_RDONLY, 0644);
      if (fh > 0) {
         size = read(fh, &gl->board[index].tcalib, sizeof(TCALIB_DATA));
         if (size != sizeof(TCALIB_DATA)) {
            printf("Invalid time calibration file size of \"%s\". Aborting.\n", str);
            return FAILURE;
         }
         if (memcmp(gl->board[index].tcalib.version_id, "CAL1", 4) != 0) {
            printf("Invalid time calibration file format in \"%s\". Aborting.\n", str);
            return FAILURE;
         }
         if (fabs(gl->board[index].tcalib.temperature - gl->board[index].temperature) > 5) {
            printf("Warning: Time calibration data in \"%s/%s\" is for %3g deg. C, running now at %3g deg. C\n",
                   dir, str, gl->board[index].tcalib.temperature, gl->board[index].temperature);
         }
         
         // set sampling frequency from calibration data
         if (gl->actual_sampling_frequency == 0) {
            gl->actual_sampling_frequency = gl->board[index].tcalib.sampling_frequency;
            gl->nominal_sampling_frequency = gl->actual_sampling_frequency;
         } else {
            if (fabs(gl->board[index].vcalib.sampling_frequency - gl->actual_sampling_frequency) > 0.001) {
               printf("Warning: Time calibration data in \"%s/%s\" is for %3g GSPS, running now at %3g GSPS\n",
                      dir, str, gl->board[index].tcalib.sampling_frequency, gl->actual_sampling_frequency);
            }
         }
         close(fh);
         
      } else {
         for (int ch=0 ; ch < WD_N_CHANNELS ; ch++)
            for (int bin=0 ; bin<1024 ; bin++)
               gl->board[index].tcalib.dt[ch][bin] = (float)(1E-9 / gl->actual_sampling_frequency);
      }

      if (gl->nominal_sampling_frequency == 0)
         gl->nominal_sampling_frequency = gl->actual_sampling_frequency = 5;

      // set sampling frequency after time calibration has been loaded
      wd_set_sampling_frequency(gl, index);
      
      // read current board status (temperature + PLL lock)
      wd_read_board_status(gl, index);
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

int wd_read_waveform(GLOBALS *gl, int b, int millisec, WD2_EVENT *pe, float wfU[WD_N_CHANNELS][1024], float wfT[WD_N_CHANNELS][1024])
{
   int i, status, waveform_channel;
   unsigned int current_event_number;
   fd_set readfds;
   struct timeval timeout;
   unsigned char *pd;
   WD2_FRAME_HEADER *ph;
   short data1, data2;
   struct sockaddr_in remote_addr;
   unsigned char buffer[1800];
   int header_adc, header_channel;
   double start_time;
   static float wf1[WD_N_CHANNELS][1024];

   // tag waveforms as invalid
   for (i=0 ; i<WD_N_CHANNELS ; i++) {
      wfU[i][0]   = NANF;
      wfU[i][512] = NANF;
   }
   
   current_event_number = -1;
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
            
            // check protocol version
            if (ph->protocol_version != UDP_PROTOCOL_VERSION) {
               printf("Invalid protocol version %d, expected %d. Probably WD firmware update required.\n", ph->protocol_version, UDP_PROTOCOL_VERSION);
               continue;
            }
            
            // correct endianness of header data
            ph->board_id                 = SWAP_UINT16(ph->board_id);
            header_adc                   = (ph->adc_and_channel_info >> 4) & 0x0f;
            header_channel               = (ph->adc_and_channel_info) & 0x0f;
            ph->event_number             = SWAP_UINT32(ph->event_number);
            ph->sampling_frequency       = SWAP_UINT16(ph->sampling_frequency);
            ph->number_of_samples        = SWAP_UINT16(ph->number_of_samples);
            ph->trigger_number           = SWAP_UINT16(ph->trigger_number);
            ph->drs0_trigger_cell        = SWAP_UINT16(ph->drs0_trigger_cell);
            ph->drs1_trigger_cell        = SWAP_UINT16(ph->drs1_trigger_cell);
            ph->trigger_type             = SWAP_UINT16(ph->trigger_type);
            ph->temperature              = SWAP_UINT16(ph->temperature);
            ph->packet_sequence_number   = SWAP_UINT16(ph->packet_sequence_number);
           
            // check packet length
            if (n != sizeof(WD2_FRAME_HEADER) + ph->number_of_samples * 1.5) {
               printf("Wrong UDP packet size %d, expected %d.\n", n, (int)sizeof(WD2_FRAME_HEADER) + (int)(ph->number_of_samples * 1.5));
               continue;
            }
            
            // copy some data to event header
            pe->board_id = ph->board_id;
            pe->crate_id = ph->crate_id;
            pe->slot_id = ph->slot_id;
            pe->event_number = ph->event_number;
            pe->sampling_frequency = ph->sampling_frequency;
            pe->number_of_samples = 1024;
            pe->drs0_trigger_cell = ph->drs0_trigger_cell;
            pe->drs1_trigger_cell = ph->drs1_trigger_cell;
            pe->trigger_type = 0; // not yet implemented
            
            /*
            if (gl->verbose_flag)
               printf("From %s:%d, Event %5d, ADC/Chn/Segment %d/%d/%d - %04d/%04d\n",
                      inet_ntoa(remote_addr.sin_addr),
                      ntohs(remote_addr.sin_port),
                      ph->event_number,
                      header_adc,
                      header_channel,
                      ph->channel_segment_number,
                      ph->drs0_trigger_cell,
                      ph->drs1_trigger_cell);
            */
            
            if (current_event_number == -1)
               current_event_number = ph->event_number;
            
            // drop package if it belongs to older frame
            if (ph->event_number < current_event_number) {
               printf("Package dropped, package event number=%d, current event number=%d\n", ph->event_number, current_event_number);
               continue;
            }
            
            // drop whole frame if package of next frame received
            if (ph->event_number > current_event_number) {
               printf("Frame dropped, package frame=%d, current frame=%d\n", ph->event_number, current_event_number);

               // switch to new frame
               current_event_number = ph->event_number;
               
               // tag waveforms as invalid
               for (i=0 ; i<WD_N_CHANNELS ; i++) {
                  wfU[i][0]   = NANF;
                  wfU[i][512] = NANF;
               }
            }
            
            // drop package if it does not belong to current board
            /*
            if (ph->board_id != b) {
               printf("Package dropped, package board=%d, current board=%d\n", ph->board_id, b);
               continue;
            }
            */
            
            // map ADC and channel to WD channel (0..7, 8..15, 16+17)
            if (header_channel == 8)
               waveform_channel = 16 + header_adc;
            else
               waveform_channel = header_adc*8+header_channel;
            assert(waveform_channel < WD_N_CHANNELS);
            
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
                  wfU[waveform_channel][i]       = (float)(data1 * (1 / 4096.0)); // 1V DRS range with 12 bits
                  wfU[waveform_channel][i+1]     = (float)(data2 * (1 / 4096.0));
               } else {
                  // second segment
                  wfU[waveform_channel][512+i]   = (float)(data1 * (1 / 4096.0));
                  wfU[waveform_channel][512+i+1] = (float)(data2 * (1 / 4096.0));
               }
            }
            
            // test if all waveforms are received
            for (i=0 ; i<WD_N_CHANNELS ; i++)
               if (isnan(wfU[i][0]) || isnan(wfU[i][512]))
                   break;
            if ((gl->read_channel9 && i == WD_N_CHANNELS) ||
                ((!gl->read_channel9 || gl->adc_flag) && i == WD_N_CHANNELS-2)) {

               for (i=0 ; i<WD_N_CHANNELS ; i++)
                  for (int j=0 ; j<1024 ; j++)
                     wf1[i][j] = wfU[i][j];

               // un-rotate waveforms
               if (gl->rotate_flag || gl->adc_flag) {
                  for (i=0 ; i<WD_N_CHANNELS ; i++)
                     for (int j=0 ; j<1024 ; j++)
                        wfU[i][j] = wf1[i][j];
               } else {
                  for (i=0 ; i<WD_N_CHANNELS ; i++) {
                     int tc = i < 8 || i == 16 ? pe->drs0_trigger_cell : pe->drs1_trigger_cell;
                     for (int j=0 ; j<1024 ; j++)
                        wfU[i][(j+tc) % 1024] = wf1[i][j];
                  }
               }
               
               // calibrate waveforms
               if (gl->adc_flag) { // calibrate ADC data
                  
                  if (gl->range_calib_flag) {
                     float ofs;
                     
                     for (i=0 ; i<WD_N_CHANNELS ; i++) {
                        if (fabs(gl->board[b].range - (-0.45)) < 0.001)
                           ofs = gl->board[b].vcalib.adc_offset_range0[i];
                        else if (fabs(gl->board[b].range) < 0.001)
                           ofs = gl->board[b].vcalib.adc_offset_range1[i];
                        else if (fabs(gl->board[b].range - 0.45) < 0.001)
                           ofs = gl->board[b].vcalib.adc_offset_range2[i];
                        else
                           ofs = 0;
                        for (int j=0 ; j<1024 ; j++)
                           wfU[i][j] -= ofs;
                     }
                  }
                  
                  for (i=0 ; i<WD_N_CHANNELS ; i++)
                     for (int j=0 ; j<1024 ; j++)
                        wfT[i][j] = (float)(j * 1E-9/gl->actual_sampling_frequency);
                  
                  
               } else { // calibrate DRS data
               
                  // cell-by-cell offset calibration
                  if (gl->ofs_calib1_flag) {
                     if (gl->rotate_flag) {
                        for (i=0 ; i<WD_N_CHANNELS ; i++) {
                           int tc = i < 8 || i == 16  ? pe->drs0_trigger_cell : pe->drs1_trigger_cell;
                           for (int j=0 ; j<1024 ; j++)
                              wfU[i][j] -= gl->board[b].vcalib.wf_offset1[i][(j+tc) % 1024];
                        }
                     } else {
                        for (i=0 ; i<WD_N_CHANNELS ; i++)
                           for (int j=0 ; j<1024 ; j++)
                              wfU[i][j] -= gl->board[b].vcalib.wf_offset1[i][j];
                     }
                  }
                  
                  // start-to-end offset calibration
                  if (gl->ofs_calib2_flag) {
                     for (i=0 ; i<WD_N_CHANNELS ; i++)
                        for (int j=0 ; j<1024 ; j++)
                           wfU[i][j] -= gl->board[b].vcalib.wf_offset2[i][j];
                  }
                  
                  // gain calibration
                  if (gl->gain_calib_flag) {
                     if (gl->rotate_flag) {
                        for (i=0 ; i<WD_N_CHANNELS-2 ; i++) { // exclude clock channels
                           int tc = i < 8 || i == 16  ? pe->drs0_trigger_cell : pe->drs1_trigger_cell;
                           for (int j=0 ; j<1024 ; j++) {
                              if (wfU[i][j] > 0)
                                 wfU[i][j] /= gl->board[b].vcalib.wf_gain1[i][(j+tc) % 1024];
                              else
                                 wfU[i][j] /= gl->board[b].vcalib.wf_gain2[i][(j+tc) % 1024];
                           }
                        }
                     } else {
                        for (i=0 ; i<WD_N_CHANNELS-2 ; i++)
                           for (int j=0 ; j<1024 ; j++) {
                              if (wfU[i][j] > 0)
                                 wfU[i][j] /= gl->board[b].vcalib.wf_gain1[i][j];
                              else
                                 wfU[i][j] /= gl->board[b].vcalib.wf_gain2[i][j];
                           }
                     }
                  }

                  // range calibration
                  if (gl->range_calib_flag) {
                     float ofs;
                     
                     for (i=0 ; i<WD_N_CHANNELS-2 ; i++) { // exclude clock channels
                        if (fabs(gl->board[b].range - (-0.45)) < 0.001)
                           ofs = gl->board[b].vcalib.drs_offset_range0[i];
                        else if (fabs(gl->board[b].range) < 0.001)
                           ofs = gl->board[b].vcalib.drs_offset_range1[i];
                        else if (fabs(gl->board[b].range - 0.45) < 0.001)
                           ofs = gl->board[b].vcalib.drs_offset_range2[i];
                        else
                           ofs = 0;
                        for (int j=0 ; j<1024 ; j++)
                           wfU[i][j] -= ofs;
                     }
                  }

                  // remove spikes
                  if (gl->remove_spikes) {
                     remove_spikes(gl, pe->drs0_trigger_cell, wfU);
                     remove_spikes(gl, pe->drs1_trigger_cell, wfU+WD_N_CHANNELS/2);
                  }
                  
                  // calculate calibrated time for each bin
                  if (gl->time_calib1_flag) {
                     // integrate time from delta-t values
                     for (int ch=0 ; ch<WD_N_CHANNELS ; ch++) {
                        int tc = ch < 8 || ch == 16 ? pe->drs0_trigger_cell : pe->drs1_trigger_cell;
                        wfT[ch][0] = 0;
                        for (int i=1 ; i<1024 ; i++)
                           wfT[ch][i] = wfT[ch][i-1] + gl->board[b].tcalib.dt[ch][(i-1+tc)%1024];
                     }
                     // align cell#0 of all channels inside chip0
                     float t1 = wfT[0][(1024-pe->drs0_trigger_cell) % 1024];
                     for (int ch=1 ; ch<8 ; ch++) {
                        float t2 = wfT[ch][(1024-pe->drs0_trigger_cell) % 1024];
                        float dt = t1 - t2;
                        for (int i=0 ; i<1024 ; i++)
                           wfT[ch][i] += dt;
                     }
                     float t2 = wfT[16][(1024-pe->drs0_trigger_cell) % 1024];
                     float dt = t1 - t2;
                     for (int i=0 ; i<1024 ; i++)
                        wfT[16][i] += dt;
                     
                     // align cell#0 of all channels inside chip1 to chip0
                     for (int ch=8 ; ch<16 ; ch++) {
                        float t2 = wfT[ch][(1024-pe->drs1_trigger_cell) % 1024];
                        float dt = t1 - t2;
                        for (int i=0 ; i<1024 ; i++)
                           wfT[ch][i] += dt;
                     }
                     t2 = wfT[17][(1024-pe->drs1_trigger_cell) % 1024];
                     dt = t1 - t2;
                     for (int i=0 ; i<1024 ; i++)
                        wfT[17][i] += dt;
                     
                  } else {
                     // set nominal sampling interval
                     for (i=0 ; i<WD_N_CHANNELS ; i++)
                        for (int j=0 ; j<1024 ; j++)
                           wfT[i][j] = (float)(j * 1E-9/gl->actual_sampling_frequency);
                  }
                  
                  // apply time offsets
                  if (gl->time_calib2_flag) {
                     for (i=0 ; i<WD_N_CHANNELS ; i++)
                        for (int j=0 ; j<1024 ; j++)
                           wfT[i][j] -= gl->board[b].tcalib.offset[i];
                  }
                  
                  // apply horizontal trigger position correction
                  if (gl->time_calib3_flag) {
                     // find first crossing of the trigger level
                     for (int i=4 ; i<1020 ; i++) {
                        for (int c=0 ; c<16 ; c++) {
                           double tl =gl->board[b].trigger_level[c];
                           if (wfU[c][i] > tl && wfU[c][i+1] <= tl) {
                              double t0 = wfT[c][i] + (wfT[c][i+1]-wfT[c][i])*(tl-wfU[c][i])/(wfU[c][i+1]-wfU[c][i]);
                              t0 -= 1024*1E-9/gl->actual_sampling_frequency - 30E-9 - gl->board[b].trigger_delay * 1E-9;
                              for (i=0 ; i<WD_N_CHANNELS ; i++)
                                 for (int j=0 ; j<1024 ; j++)
                                    wfT[i][j] -= (float)t0;
                              i = 1020;
                              c = 16;
                           }
                        }
                     }
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

int wd_save_waveform(GLOBALS *gl, int b, int chn, WD2_EVENT *pe, float wfU[WD_N_CHANNELS][1024], float wfT[WD_N_CHANNELS][1024])
{
   static unsigned char *buffer = NULL;
   unsigned char *p;
   
   int buffer_size = 8 + 4 + (1024*4+12)*18 + (1024*2+12)*18;
   if (!buffer)
      buffer = (unsigned char *)malloc(buffer_size);
   
   // open file on new request
   if (gl->li.nRequest && gl->li.nLogged == 0) {

      if (gl->li.format == LI_FORMAT_BIN) {
         if (gl->li.fh > 0)
            close(gl->li.fh);
         
         gl->li.fh = open(gl->li.filename, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0644);
         assert(gl->li.fh > 0);
      }
      
      if (gl->li.format == LI_FORMAT_XML) {
         if (gl->li.xml)
            mxml_close_file(gl->li.xml);
         
         gl->li.xml = mxml_open_file(gl->li.filename);
         assert(gl->li.xml);
      }
   }
   
   if (gl->li.fh == 0 && gl->li.xml == NULL)
      return SUCCESS;
   
   TIMESTAMP ts;
   GetTimeStamp(ts);

   if (gl->li.format == LI_FORMAT_XML) {
      char str[256];
      mxml_start_element(gl->li.xml, "Event");
      sprintf(str, "%d", gl->li.nLogged+1);
      mxml_write_element(gl->li.xml, "Serial", str);
      sprintf(str, "%4d/%02d/%02d %02d:%02d:%02d.%03d", ts.Year, ts.Month,
              ts.Day, ts.Hour, ts.Minute, ts.Second, ts.Milliseconds);
      mxml_write_element(gl->li.xml, "Time", str);
      mxml_write_element(gl->li.xml, "HUnit", "ns");
      mxml_write_element(gl->li.xml, "VUnit", "mV");
      
      for (int b=0 ; b<gl->n_boards ; b++) {
         sprintf(str, "Board_%d", gl->board[b].serial_number);
         mxml_start_element(gl->li.xml, str);
         for (int i=0 ; i<WD_N_CHANNELS ; i++) {
            if (1/*##*/) {
               sprintf(str, "CHN%d", i);
               mxml_start_element(gl->li.xml, str);
               sprintf(str, "%d", i < WD_N_CHANNELS/2 ? pe->drs0_trigger_cell : pe->drs1_trigger_cell);
               mxml_write_element(gl->li.xml, "Trigger_Cell", str);
               sprintf(str, "%u", gl->board[b].scaler[i]);
               mxml_write_element(gl->li.xml, "Scaler", str);
               mxml_start_element(gl->li.xml, "Waveform");
               strcpy(str, "\n");
               for (int j=0 ; j<1024 ; j++) {
                  sprintf(str, "%1.3f,%1.1f", wfT[i][j]*1E9, wfU[i][j]*1E3);
                  mxml_write_element(gl->li.xml, "Data", str);
               }
               mxml_end_element(gl->li.xml); // CHNx
               mxml_end_element(gl->li.xml); // CHNx
            }
         }
         mxml_end_element(gl->li.xml); //Board
      }
      mxml_end_element(gl->li.xml); // Event
   }
   
   if (gl->li.format == LI_FORMAT_BIN) {
      p = buffer;
      
      if (gl->li.nLogged == 0) {
         memcpy(p, "DRS8", 4); // File identifier and version
         p += 4;
         
         // time calibration header
         memcpy(p, "TIME", 4);
         p += 4;
         
         for (int b=0 ; b<gl->n_boards ; b++) {
            // store board serial number
            sprintf((char *)p, "B#");
            p += 2;
            *(unsigned short *)p = gl->board[b].serial_number;
            p += sizeof(unsigned short);
            
            for (int i=0 ; i<WD_N_CHANNELS ; i++) {
               if (chn && (1 << i)){
                  sprintf((char *)p, "C%03d", i);
                  p += 4;
                  for (int j=0 ; j<1024 ; j++) {
                     // save binary time as 32-bit float value
                     *(float *)p = gl->board[b].tcalib.dt[i][j];
                     p += sizeof(float);
                  }
               }
            }
         }
      }
      
      memcpy(p, "EHDR", 4);
      p += 4;
      *(int *)p = gl->li.nLogged;
      p += sizeof(int);
      *(unsigned short *)p = ts.Year;
      p += sizeof(unsigned short);
      *(unsigned short *)p = ts.Month;
      p += sizeof(unsigned short);
      *(unsigned short *)p = ts.Day;
      p += sizeof(unsigned short);
      *(unsigned short *)p = ts.Hour;
      p += sizeof(unsigned short);
      *(unsigned short *)p = ts.Minute;
      p += sizeof(unsigned short);
      *(unsigned short *)p = ts.Second;
      p += sizeof(unsigned short);
      *(unsigned short *)p = ts.Milliseconds;
      p += sizeof(unsigned short);
      *(unsigned short *)p = (unsigned short)(gl->board[0].range * 1000); // range
      p += sizeof(unsigned short);
      
      for (int b=0 ; b<gl->n_boards ; b++) {
         
         // store board serial number
         sprintf((char *)p, "B#");
         p += 2;
         *(unsigned short *)p = gl->board[b].serial_number;
         p += sizeof(unsigned short);
         
         for (int i=0 ; i<WD_N_CHANNELS ; i++) {
            if (chn && (1 << i)) {
               // channel header
               sprintf((char *)p, "C%03d", i);
               p += 4;

               // write scaler
               unsigned int s = gl->board[b].scaler[i];
               memcpy(p, &s, sizeof(int));
               p += sizeof(int);

               // write trigger cell
               sprintf((char *)p, "T#");
               p += 2;
               *(unsigned short *)p = i < WD_N_CHANNELS/2 ? pe->drs0_trigger_cell : pe->drs1_trigger_cell;
               p += sizeof(unsigned short);

               for (int j=0 ; j<1024 ; j++) {
                  // save binary date as 16-bit value:
                  // 0 = -0.5V,  65535 = +0.5V    for range 0
                  // 0 = -0.05V, 65535 = +0.95V   for range 0.45
                  unsigned short d = (unsigned short)((wfU[i][j] - gl->board[b].range + 0.5) * 65535);
                  *(unsigned short *)p = d;
                  p += sizeof(unsigned short);
               }
            }
         }
      }
      
      int size = p - buffer;
      int n = write(gl->li.fh, buffer, size);
      assert(n == size);
      assert(size < buffer_size);
   }
   
   if (gl->li.nLogged == gl->li.nRequest && gl->li.fh) {
      close(gl->li.fh);
      gl->li.fh = 0;
   }

   gl->li.nLogged++;

   return SUCCESS;
}

/*-----------------------------------------------------------------------------------------*/

int wd_calibrate_voltage(GLOBALS *gl, VCALIB_PROGRESS *pr)
{
   float wfU[WD_N_CHANNELS][1024], wfT[WD_N_CHANNELS][1024];
   WD2_EVENT eventHeader;
   char str[80];
   
   /* turn off clock if it is on */
   if (gl->osctca_flag) {
      gl->osctca_flag = 0;
      for (int i=0 ; i<gl->n_boards ; i++)
         wd_set_osctca(gl, i);
   }
   
   if (pr->state == WD_CS_FIRST_BOARD) {
      memset(pr, 0, sizeof(VCALIB_PROGRESS));
      pr->state   = WD_CS_FIRST_SAMPLE;
      pr->n_iter1 = 200;
      pr->n_iter2 = 200;
      pr->n_iter3 = 200;
      pr->n_iter4 = 200;
      pr->n_board = gl->n_boards;
      pr->i_board = 0;
   }

   if (pr->state == WD_CS_FIRST_SAMPLE) {
      pr->progress = 0;
      pr->i_iter1  = 0;
      pr->i_iter2  = 0;
      pr->i_iter3  = 0;
      pr->i_iter4  = 0;
      pr->state    = WD_CS_RUNNING;
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
         gl->dc_offset        = 0;
         wd_set_fe(gl, pr->i_board, -1);
         wd_set_dcv_flag(gl, pr->i_board);
         wd_set_dc_offset(gl, pr->i_board);
         
         int n = pr->n_iter1;
         n = MAX(n, pr->n_iter2);
         n = MAX(n, pr->n_iter3);
         n = MAX(n, pr->n_iter4);
         
         pr->ave = new Averager(1, WD_N_CHANNELS, 1024, n);
      }

      pr->i_iter1++;
      
      wd_send(gl, pr->i_board, 100, "drsget\n", NULL, NULL);
      if (wd_read_waveform(gl, pr->i_board, 1000, &eventHeader, wfU, wfT) != SUCCESS)
         return SUCCESS; // just skip this event
      
      for (int ch=0 ; ch<WD_N_CHANNELS ; ch++)
         for (int bin=0 ; bin<1024 ; bin++)
            pr->ave->Add(0, ch, bin, wfU[ch][bin]);
      
      pr->progress = (double)(pr->i_iter1 + pr->i_iter2 + pr->i_iter3 + pr->i_iter4) /
                             (pr->n_iter1 + pr->n_iter2 + pr->n_iter3 + pr->n_iter4);
      
      // calibration finished
      if (pr->i_iter1 == pr->n_iter1) {
         for (int ch=0 ; ch<WD_N_CHANNELS ; ch++)
            for (int bin=0 ; bin<1024 ; bin++)
               gl->board[pr->i_board].vcalib.wf_offset1[ch][bin] = (float)pr->ave->Median(0, ch, bin);
         
         // ave->SaveNormalizedDistribution("wf.csv", 0);
         pr->ave->Reset();
      }

      sleep_ms(10); // obtain 100 Hz rate
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
      
      wd_send(gl, pr->i_board, 100, "drsget\n", NULL, NULL);
      if (wd_read_waveform(gl, pr->i_board, 1000, &eventHeader, wfU, wfT) != SUCCESS)
         return SUCCESS; // just skip this event

      for (int ch=0 ; ch<WD_N_CHANNELS ; ch++)
         for (int bin=0 ; bin<1024 ; bin++)
            pr->ave->Add(0, ch, bin, wfU[ch][bin]);
      
      pr->progress = (double)(pr->i_iter1 + pr->i_iter2 + pr->i_iter3 + pr->i_iter4) /
                             (pr->n_iter1 + pr->n_iter2 + pr->n_iter3 + pr->n_iter4);
      
      // calibration finished
      if (pr->i_iter2 == pr->n_iter2) {
         for (int ch=0 ; ch<WD_N_CHANNELS ; ch++)
            for (int bin=0 ; bin<1024 ; bin++)
               gl->board[pr->i_board].vcalib.wf_offset2[ch][bin] = (float)pr->ave->Median(0, ch, bin);
         
         pr->ave->Reset();
      }
      
      sleep_ms(10); // obtain 100 Hz rate
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
         gl->dc_offset        = 0.45f;
         wd_set_fe(gl, pr->i_board, -1);
         wd_set_dcv_flag(gl, pr->i_board);
         wd_set_dc_offset(gl, pr->i_board);
      }
      
      pr->i_iter3++;
      
      wd_send(gl, pr->i_board, 100, "drsget\n", NULL, NULL);
      if (wd_read_waveform(gl, pr->i_board, 1000, &eventHeader, wfU, wfT) != SUCCESS)
         return SUCCESS; // just skip this event
      
      for (int ch=0 ; ch<WD_N_CHANNELS ; ch++)
         for (int bin=0 ; bin<1024 ; bin++)
            pr->ave->Add(0, ch, bin, wfU[ch][bin]);
      
      pr->progress = (double)(pr->i_iter1 + pr->i_iter2 + pr->i_iter3 + pr->i_iter4) /
                             (pr->n_iter1 + pr->n_iter2 + pr->n_iter3 + pr->n_iter4);
      
      // calibration finished
      if (pr->i_iter3 == pr->n_iter3) {
         for (int ch=0 ; ch<WD_N_CHANNELS-2 ; ch++) // exclude clock channels
            for (int bin=0 ; bin<1024 ; bin++)
               gl->board[pr->i_board].vcalib.wf_gain1[ch][bin] = (float)(pr->ave->Median(0, ch, bin) / 0.45);
         
         pr->ave->Reset();
      }
      
      sleep_ms(10); // obtain 100 Hz rate
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

         gl->dc_offset        = -0.45f;
         wd_set_dc_offset(gl, pr->i_board);
      }
      
      pr->i_iter4++;
      
      wd_send(gl, pr->i_board, 100, "drsget\n", NULL, NULL);
      if (wd_read_waveform(gl, pr->i_board, 1000, &eventHeader, wfU, wfT) != SUCCESS)
         return SUCCESS; // just skip this event
      
      for (int ch=0 ; ch<WD_N_CHANNELS ; ch++)
         for (int bin=0 ; bin<1024 ; bin++)
            pr->ave->Add(0, ch, bin, wfU[ch][bin]);
      
      pr->progress = (double)(pr->i_iter1 + pr->i_iter2 + pr->i_iter3 + pr->i_iter4) /
                             (pr->n_iter1 + pr->n_iter2 + pr->n_iter3 + pr->n_iter4);
      
      // calibration finished
      if (pr->i_iter4 == pr->n_iter4) {
         for (int ch=0 ; ch<WD_N_CHANNELS-2 ; ch++) // exclude clock channels
            for (int bin=0 ; bin<1024 ; bin++)
               gl->board[pr->i_board].vcalib.wf_gain2[ch][bin] = (float)(pr->ave->Median(0, ch, bin) / -0.45);
         
         delete pr->ave;
         pr->ave = NULL;
      }
      
      sleep_ms(10); // obtain 100 Hz rate
      return SUCCESS;
   }
   
   // reset board
   gl->dc_offset = 0;
   gl->dcv_flag = 0;
   wd_set_dc_offset(gl, pr->i_board);

   gl->rotate_flag      = 1;
   gl->ofs_calib1_flag  = 1;
   gl->ofs_calib2_flag  = 1;
   gl->gain_calib_flag  = 1;
   gl->range_calib_flag = 0;
   gl->remove_spikes    = 0;

   // measure offset without DCV at different ranges
   assert(wd_send(gl, pr->i_board, 100, "calbuf off", NULL, NULL) > 0);    // disable BUFFER_CTRL
   assert(wd_send(gl, pr->i_board, 100, "feset all 102", NULL, NULL) > 0);  // gain 1, PZC off, MUX off

   // Range -0.45
   gl->board[pr->i_board].range = -0.45f;
   wd_set_range(gl, pr->i_board);
   
   for (int i=0 ; i<10 ; i++) {
      wd_send(gl, pr->i_board, 100, "drsget\n", NULL, NULL);
      if (wd_read_waveform(gl, pr->i_board, 1000, &eventHeader, wfU, wfT) != SUCCESS)
         i--;
      sleep_ms(10);
   }
   
   for (int ch=0 ; ch<WD_N_CHANNELS-2 ; ch++) {
      float sum = 0;
      for (int i=10 ; i<1020 ; i++)
         sum += wfU[ch][i];
      gl->board[pr->i_board].vcalib.drs_offset_range0[ch] = sum / 1010;
   }
   
   gl->adc_flag = 1;
   do {
      wd_send(gl, pr->i_board, 100, "adcget\n", NULL, NULL);
   } while (wd_read_waveform(gl, pr->i_board, 1000, &eventHeader, wfU, wfT) != SUCCESS);
   
   for (int ch=0 ; ch<WD_N_CHANNELS-2 ; ch++) {
      float sum = 0;
      for (int i=10 ; i<1020 ; i++)
         sum += wfU[ch][i];
      gl->board[pr->i_board].vcalib.adc_offset_range0[ch] = sum / 1010;
   }
   gl->adc_flag = 0;
   
   // Range 0
   gl->board[pr->i_board].range = 0;
   wd_set_range(gl, pr->i_board);
   
   for (int i=0 ; i<10 ; i++) {
      wd_send(gl, pr->i_board, 100, "drsget\n", NULL, NULL);
      if (wd_read_waveform(gl, pr->i_board, 1000, &eventHeader, wfU, wfT) != SUCCESS)
         i--;
      sleep_ms(10);
   }
   
   for (int ch=0 ; ch<WD_N_CHANNELS-2 ; ch++) {
      float sum = 0;
      for (int i=10 ; i<1020 ; i++)
         sum += wfU[ch][i];
      gl->board[pr->i_board].vcalib.drs_offset_range1[ch] = sum / 1010;
   }

   gl->adc_flag = 1;
   do {
      wd_send(gl, pr->i_board, 100, "adcget\n", NULL, NULL);
   } while (wd_read_waveform(gl, pr->i_board, 1000, &eventHeader, wfU, wfT) != SUCCESS);
   
   for (int ch=0 ; ch<WD_N_CHANNELS-2 ; ch++) {
      float sum = 0;
      for (int i=10 ; i<1020 ; i++)
         sum += wfU[ch][i];
      gl->board[pr->i_board].vcalib.adc_offset_range1[ch] = sum / 1010;
   }
   gl->adc_flag = 0;

   // Range 0.45
   gl->board[pr->i_board].range = 0.45f;
   wd_set_range(gl, pr->i_board);
   
   for (int i=0 ; i<10 ; i++) {
      wd_send(gl, pr->i_board, 100, "drsget\n", NULL, NULL);
      if (wd_read_waveform(gl, pr->i_board, 1000, &eventHeader, wfU, wfT) != SUCCESS)
         i--;
      sleep_ms(10);
   }
   
   for (int ch=0 ; ch<WD_N_CHANNELS-2 ; ch++) {
      float sum = 0;
      for (int i=10 ; i<1020 ; i++)
         sum += wfU[ch][i];
      gl->board[pr->i_board].vcalib.drs_offset_range2[ch] = sum / 1010;
   }

   gl->adc_flag = 1;
   do {
      wd_send(gl, pr->i_board, 100, "adcget\n", NULL, NULL);
   } while (wd_read_waveform(gl, pr->i_board, 1000, &eventHeader, wfU, wfT) != SUCCESS);
   
   for (int ch=0 ; ch<WD_N_CHANNELS-2 ; ch++) {
      float sum = 0;
      for (int i=10 ; i<1020 ; i++)
         sum += wfU[ch][i];
      gl->board[pr->i_board].vcalib.adc_offset_range2[ch] = sum / 1010;
   }
   gl->adc_flag = 0;

   // set everything back to normal values
   gl->board[pr->i_board].range = pr->prev_range;
   gl->mux_flag                 = 0;
   gl->dcv_flag                 = 0;
   gl->dc_offset                = 0;
   wd_set_fe(gl, pr->i_board, -1);
   wd_set_dcv_flag(gl, pr->i_board);
   wd_set_dc_offset(gl, pr->i_board);
   wd_set_range(gl, pr->i_board);

   // save calibration
   memcpy(gl->board[pr->i_board].vcalib.version_id, "CAL1", 4);
   gl->board[pr->i_board].vcalib.sampling_frequency = gl->actual_sampling_frequency;
   gl->board[pr->i_board].vcalib.temperature = gl->board[pr->i_board].temperature;
   
   mkdir("calib", 0755);
   sprintf(str, "calib/%s.vcal", gl->board[pr->i_board].name);
   pr->fh = open(str, O_WRONLY | O_CREAT, 0644);
   assert(pr->fh > 0);
   assert(write(pr->fh, &gl->board[pr->i_board].vcalib, sizeof(VCALIB_DATA)) == sizeof(VCALIB_DATA));
   close(pr->fh);

   // switch to next board
   pr->i_board++;
   pr->state = WD_CS_FIRST_SAMPLE;
   pr->progress = 1;
   
   if (pr->i_board == pr->n_board) {
      pr->state = WD_CS_INACTIVE;
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
   float cwf[WD_N_CHANNELS][1024];

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

void wd_read_board_status(GLOBALS *gl, int index)
{
   int size;
   char str[10000];

   if (gl->demo_flag) {
      gl->board[index].temperature = 36.9f;
      gl->board[index].pll_locked = 1;
      return;
   }

   size = sizeof(str);
   assert(wd_send(gl, index, 100, "temp", str, &size) > 0);
   gl->board[index].temperature = (float)atof(str+5);
   
   size = sizeof(str);
   assert(wd_send(gl, index, 100, "lmklock", str, &size) > 0);
   gl->board[index].pll_locked = (str[8] == 'L');
}

/*-----------------------------------------------------------------------------------------*/

void wd_read_scalers(GLOBALS *gl, int index)
{
   int size;
   char str[10000], cmd[100], *p;
   
   if (gl->demo_flag) {
      for (int i=0 ; i<16 ; i++)
         gl->board[index].scaler[i] = (unsigned int)((float)rand()/RAND_MAX*9999.);
      return;
   }
   
   sprintf(cmd, "llrd c301%04x 34", REG_SCALER_1_LSB_OFFSET);
   size = sizeof(str);
   assert(wd_send(gl, index, 100, cmd, str, &size) > 0);
   
   p = str;
   for (int i=0 ; i<18 ; i++) {
      p = strchr(p, ' ');
      if (p == NULL)
         break;
      gl->board[index].scaler[i] = strtol(p, NULL, 16);
      p = strchr(p+1, ' ');
      if (p == NULL)
         break;
      p++;  // skip MSB
   }
}

/*-----------------------------------------------------------------------------------------*/

void wd_analyze_period(GLOBALS *gl, WD2_EVENT *pe, int b, float wfU[WD_N_CHANNELS][1024])
{
   int tc;
   
   for (int ch=0 ; ch<WD_N_CHANNELS ; ch++) {
      if (ch < WD_N_CHANNELS/2)
         tc = pe->drs0_trigger_cell;
      else
         tc = pe->drs1_trigger_cell;
      
      // rising edges
      for (int i1=tc+5; i1<tc+1024-5 ; i1++) {
         if (wfU[ch][i1 % 1024] <= 0 && wfU[ch][(i1+1) % 1024] > 0) {
            for (int i2=i1+1 ; i2<i1+1024 && i2<tc+1024-3; i2++) {
               if (wfU[ch][i2 % 1024] <= 0 && wfU[ch][(i2+1) % 1024] > 0) {
                  
                  // first partial cell
                  double tPeriod = gl->board[b].tcalib.dt[ch][i1%1024]*(1/(1-wfU[ch][i1%1024]/wfU[ch][(i1+1)%1024]));
                  
                  // full cells between i1 and i2
                  if (i2 < i1)
                     i2 += 1024;
                  for (int j=i1+1 ; j<i2 ; j++)
                     tPeriod += gl->board[b].tcalib.dt[ch][j%1024];
                  
                  // second partial cell
                  tPeriod += gl->board[b].tcalib.dt[ch][i2 % 1024]*(1/(1-wfU[ch][(i2+1)%1024]/wfU[ch][i2%1024]));
                  
                  gl->board[b].tcalib.period[ch][i1%1024] = (float)tPeriod;
                  
                  break;
               }
            }
         }
      }
      
      // falling edges
      for (int i1=tc+5; i1<tc+1024-5 ; i1++) {
         if (wfU[ch][i1 % 1024] >= 0 && wfU[ch][(i1+1) % 1024] < 0) {
            for (int i2=i1+1 ; i2<i1+1024 && i2<tc+1024-3; i2++) {
               if (wfU[ch][i2 % 1024] >= 0 && wfU[ch][(i2+1) % 1024] < 0) {
                  
                  // first partial cell
                  double tPeriod = gl->board[b].tcalib.dt[ch][i1%1024]*(1/(1-wfU[ch][i1%1024]/wfU[ch][(i1+1)%1024]));
                  
                  // full cells between i1 and i2
                  if (i2 < i1)
                     i2 += 1024;
                  for (int j=i1+1 ; j<i2 ; j++)
                     tPeriod += gl->board[b].tcalib.dt[ch][j%1024];
                  
                  // second partial cell
                  tPeriod += gl->board[b].tcalib.dt[ch][i2 % 1024]*(1/(1-wfU[ch][(i2+1)%1024]/wfU[ch][i2%1024]));
                  
                  gl->board[b].tcalib.period[ch][i1%1024] = (float)tPeriod;
                  
                  break;
               }
            }
         }
      }
   }
}

/*-----------------------------------------------------------------------------------------*/

void wd_analyze_time_offset(GLOBALS *gl, float wfU[WD_N_CHANNELS][1024], float wfT[WD_N_CHANNELS][1024], TCALIB_PROGRESS *pr)
{
   
   // find rising edge in channel #0
   for (int i=20; i<1024-20 ; i++) {
      if (wfU[0][i] <= 0 && wfU[0][i+1] > 0) {
         double t0 = wfT[0][i] + (wfT[0][i+1]-wfT[0][i])*(1/(1-wfU[0][i]/wfU[0][i+1]));
         
         for (int ch=1 ; ch<WD_N_CHANNELS ; ch++) {
            for (int j=i-10; j<i+10 ; j++) {
               if (wfU[ch][j] <= 0 && wfU[ch][j+1] > 0) {
                  double t = wfT[ch][j] + (wfT[ch][j+1]-wfT[ch][j])*(1/(1-wfU[ch][j]/wfU[ch][j+1]));
                  double dt = t - t0;
                  pr->ave->Add(0, ch, 0, (float)dt);
                  break;
               }
            }
         }
      }
   }
}

/*-----------------------------------------------------------------------------------------*/

void wd_calibrate_local(GLOBALS *gl, WD2_EVENT *pe, int b, float wfU[WD_N_CHANNELS][1024], TCALIB_PROGRESS *pr)
{
   int tc;
   float dv, llim, ulim;
   
   if (gl->nominal_sampling_frequency >= 3) {
      llim = -0.15f;
      ulim =  0.15f;
   } else {
      llim = -0.3f;
      ulim =  0.3f;
   }
   
   for (int ch=0 ; ch<WD_N_CHANNELS ; ch++) {
      tc = ch < 8 || ch == 16 ? pe->drs0_trigger_cell : pe->drs1_trigger_cell;
      
      for (int i=tc+5; i<tc+1024-5 ; i++) {

         // rising edges

         // test slope between previous and next cell to allow for negative cell width
         if (wfU[ch][(i+1024-1) % 1024] < wfU[ch][(i+2) % 1024] &&
             wfU[ch][i % 1024] > llim &&
             wfU[ch][(i+1) % 1024] < ulim) {
            
            // calculate delta_v
            dv = wfU[ch][(i+1) % 1024] - wfU[ch][i % 1024];
            
            // average delta_v
            pr->ave->Add(0, ch, i % 1024, dv);
         }
         
         // falling edges
         if (wfU[ch][(i+1024-1) % 1024] > wfU[ch][(i+2) % 1024] &&
             wfU[ch][i % 1024] < ulim &&
             wfU[ch][(i+1) % 1024] > llim) {
            
            // calculate delta_v
            dv = wfU[ch][(i+1) % 1024] - wfU[ch][i % 1024];
            
            // average delta_v
            pr->ave->Add(0, ch, i % 1024, -dv);
         }
      }
      
      // calculate calibration every 100 events
      if (pr->i_iter1 % 100 == 0) {
         // average over all 1024 dU
         double sum = 0;
         double cellDV[1024];
         
         for (int i=0 ; i<1024 ; i++) {
            cellDV[i] = pr->ave->RobustAverage(0, ch, i);
            sum += cellDV[i];
         }
         
         sum /= 1024;
         double dtCell = 1.0/gl->actual_sampling_frequency*1E-9;
         
         // here comes the central calculation, dT = dV/average * dtCell
         for (int i=0 ; i<1024 ; i++)
            gl->board[b].tcalib.dt[ch][i] = (float)(cellDV[i] / sum * dtCell);
      }

   }
}

/*-----------------------------------------------------------------------------------------*/

void wd_calibrate_global(GLOBALS *gl, WD2_EVENT *pe, int b, float wfU[WD_N_CHANNELS][1024], TCALIB_PROGRESS *pr)
{
   int tc;
   float damping = 0.1f;
   
   for (int ch=0 ; ch<WD_N_CHANNELS ; ch++) {
      tc = ch < 8 || ch == 16 ? pe->drs0_trigger_cell : pe->drs1_trigger_cell;
      
      // rising edges
      for (int i1=tc+5; i1<tc+1024-5 ; i1++) {
         if (wfU[ch][i1 % 1024] <= 0 && wfU[ch][(i1+1) % 1024] > 0) {
            for (int i2=i1+1 ; i2<i1+1024 && i2<tc+1024-3; i2++) {
               if (wfU[ch][i2 % 1024] <= 0 && wfU[ch][(i2+1) % 1024] > 0) {
                  
                  // first partial cell
                  double tPeriod = gl->board[b].tcalib.dt[ch][i1%1024]*(1/(1-wfU[ch][i1%1024]/wfU[ch][(i1+1)%1024]));
                  
                  // full cells between i1 and i2
                  if (i2 < i1)
                     i2 += 1024;
                  for (int j=i1+1 ; j<i2 ; j++)
                     tPeriod += gl->board[b].tcalib.dt[ch][j%1024];
                  
                  // second partial cell
                  tPeriod += gl->board[b].tcalib.dt[ch][i2 % 1024]*(1/(1-wfU[ch][(i2+1)%1024]/wfU[ch][i2%1024]));
                  
                  // calculate correction to nominal period of 10 ns as a fraction
                  float corr = (float)((10E-9) / tPeriod);
                  
                  // skip big corrections (probably noise)
                  if (corr > 1.01 || corr < 0.99)
                     continue;
                  
                  // apply damping factor
                  corr = (corr - 1)*damping + 1;
                  
                  // distribute correction equally into bin inside the region
                  for (int j=i1+1 ; j<i2 ; j++)
                     gl->board[b].tcalib.dt[ch][j % 1024] *= corr;
                  
                  break;
               }
            }
         }
      }
      
      // falling edges
      for (int i1=tc+5; i1<tc+1024-5 ; i1++) {
         if (wfU[ch][i1 % 1024] >= 0 && wfU[ch][(i1+1) % 1024] < 0) {
            for (int i2=i1+1 ; i2<i1+1024 ; i2++) {
               if (wfU[ch][i2 % 1024] >= 0 && wfU[ch][(i2+1) % 1024] < 0) {
                  
                  // first partial cell
                  double tPeriod = gl->board[b].tcalib.dt[ch][i1%1024]*(1/(1-wfU[ch][i1%1024]/wfU[ch][(i1+1)%1024]));
                  
                  // full cells between i1 and i2
                  if (i2 < i1)
                     i2 += 1024;
                  for (int j=i1+1 ; j<i2 ; j++)
                     tPeriod += gl->board[b].tcalib.dt[ch][j%1024];
                  
                  // second partial cell
                  tPeriod += gl->board[b].tcalib.dt[ch][i2 % 1024]*(1/(1-wfU[ch][(i2+1)%1024]/wfU[ch][i2%1024]));
                  
                  // calculate correction to nominal period of 10 ns as a fraction
                  float corr = (float)((10E-9) / tPeriod);
                  
                  // skip big corrections (probably noise)
                  if (corr > 1.01 || corr < 0.99)
                     continue;
                  
                  // apply damping factor
                  corr = (corr - 1)*damping + 1;
                  
                  // distribute correction equally into bin inside the region
                  for (int j=i1+1 ; j<i2 ; j++)
                     gl->board[b].tcalib.dt[ch][j % 1024] *= corr;
                  
                  break;
               }
            }
         }
      }
   }
}

/*-----------------------------------------------------------------------------------------*/


int wd_calibrate_time(GLOBALS *gl, TCALIB_PROGRESS *pr)
{
   float wfU[WD_N_CHANNELS][1024], wfT[WD_N_CHANNELS][1024];
   WD2_EVENT eventHeader;
   char str[80];
   
   if (pr->state == WD_CS_FIRST_BOARD || pr->state == WD_CS_SINGLE_BOARD) {
      memset(pr, 0, sizeof(VCALIB_PROGRESS));
      pr->state             = WD_CS_FIRST_SAMPLE;
      pr->n_iter1           = 500;
      pr->n_iter2           = 500;
      pr->n_iter3           = 100;
      pr->phase             = 0;
      pr->n_board           = gl->n_boards;
      if (pr->state == WD_CS_FIRST_BOARD)
         pr->i_board           = 0;
      gl->rotate_flag       = 0;
      gl->adc_flag          = 0;
      gl->ofs_calib1_flag   = 1;
      gl->ofs_calib2_flag   = 1;
      gl->gain_calib_flag   = 1;
      gl->range_calib_flag  = 1;
      gl->time_calib1_flag  = 0;
      gl->time_calib2_flag  = 0;
      gl->time_calib3_flag  = 0;
   }
   
   if (pr->state == WD_CS_FIRST_SAMPLE) {
      pr->progress = 0;
      pr->i_iter1  = 0;
      pr->i_iter2  = 0;
      pr->state    = WD_CS_RUNNING;

      // initialize delta-t array with nominal values
      for (int ch=0 ; ch<WD_N_CHANNELS ; ch++)
         for (int bin=0 ; bin<1024 ; bin++) {
            gl->board[pr->i_board].tcalib.dt[ch][bin] = (float)(1/gl->actual_sampling_frequency*1E-9); // [s]
            gl->board[pr->i_board].tcalib.period[ch][bin] = 0;
         }

      // switch to -0.5 ... + 0.5V range, timing oscillator on
      pr->prev_range = gl->board[pr->i_board].range;
      gl->board[pr->i_board].range = 0; // range -0.5 ... + 0.5V
      wd_set_range(gl, pr->i_board);
      gl->mux_flag         = 1;
      gl->dcv_flag         = 1;
      gl->dc_offset        = 0;
      gl->osctca_flag      = 1;
      gl->osctca_delay     = -2250;
      wd_set_fe(gl, pr->i_board, -1);
      wd_set_dcv_flag(gl, pr->i_board);
      wd_set_dc_offset(gl, pr->i_board);
      wd_set_osctca(gl, pr->i_board);
      
      pr->ave = new Averager(1, WD_N_CHANNELS, 1024, MAX(pr->n_iter1, pr->n_iter2));
   }
   
   //---- Local Calibration ----
   
   if (pr->i_iter1 < pr->n_iter1) {
      
      pr->i_iter1++;
      
      // switch phase of LMK clock
      if (pr->i_iter1 > pr->n_iter1/20 * (1+pr->phase)) {
         pr->phase++;
         gl->osctca_delay = (pr->phase-10)*2250/10;
         wd_set_osctca(gl, pr->i_board);
      }
      
      wd_send(gl, pr->i_board, 100, "drsget\n", NULL, NULL);
      if (wd_read_waveform(gl, pr->i_board, 1000, &eventHeader, wfU, wfT) != SUCCESS)
         return SUCCESS; // just skip this event
      
      wd_analyze_period(gl, &eventHeader, pr->i_board, wfU);
      wd_calibrate_local(gl, &eventHeader, pr->i_board, wfU, pr);
      
      pr->progress = (double)(pr->i_iter1 + pr->i_iter2 + pr->i_iter3) / (pr->n_iter1 + pr->n_iter2 + pr->n_iter3);
      
      if (pr->i_iter1 == pr->n_iter1) {
         pr->ave->Reset();
         
         pr->phase = 0;
         gl->osctca_delay = -2250;
         wd_set_osctca(gl, pr->i_board);
      }
      
      sleep_ms(10); // obtain 100 Hz rate
      return SUCCESS;
   }
   
   //---- Global Calibration
   
   if (pr->i_iter2 < pr->n_iter2) {
      
      pr->i_iter2++;
      
      // switch phase of LMK clock
      if (pr->i_iter2 > pr->n_iter2/20 * (1+pr->phase)) {
         pr->phase++;
         gl->osctca_delay = (pr->phase-10)*2250/10;
         wd_set_osctca(gl, pr->i_board);
      }

      wd_send(gl, pr->i_board, 100, "drsget\n", NULL, NULL);
      if (wd_read_waveform(gl, pr->i_board, 1000, &eventHeader, wfU, wfT) != SUCCESS)
         return SUCCESS; // just skip this event
      
      wd_analyze_period(gl, &eventHeader, pr->i_board, wfU);
      wd_calibrate_global(gl, &eventHeader, pr->i_board, wfU, pr);
      
      pr->progress = (double)(pr->i_iter1 + pr->i_iter2 + pr->i_iter3) / (pr->n_iter1 + pr->n_iter2 + pr->n_iter3);
      
      if (pr->i_iter2 == pr->n_iter2) {
         pr->ave->Reset();
         gl->time_calib1_flag  = 1;
         gl->rotate_flag       = 1;
         gl->osctca_delay = 0;
         wd_set_osctca(gl, pr->i_board);
      }

      sleep_ms(10); // obtain 100 Hz rate
      return SUCCESS;
   }

   //---- Offset Calibration
   
   if (pr->i_iter3 < pr->n_iter3) {
      
      pr->i_iter3++;
      
      wd_send(gl, pr->i_board, 100, "drsget\n", NULL, NULL);
      if (wd_read_waveform(gl, pr->i_board, 1000, &eventHeader, wfU, wfT) != SUCCESS)
         return SUCCESS; // just skip this event
      
      wd_analyze_time_offset(gl, wfU, wfT, pr);
      
      pr->progress = (double)(pr->i_iter1 + pr->i_iter2 + pr->i_iter3) / (pr->n_iter1 + pr->n_iter2 + pr->n_iter3);
      
      if (pr->i_iter3 == pr->n_iter3) {
         gl->board[pr->i_board].tcalib.offset[0] = 0; // by definition
         for (int ch=1 ; ch<WD_N_CHANNELS ; ch++)
            gl->board[pr->i_board].tcalib.offset[ch] = (float)(pr->ave->RobustAverage(0, ch, 0));
      }
      
      sleep_ms(10); // obtain 100 Hz rate
      return SUCCESS;
   }

   delete pr->ave;
   pr->ave = NULL;
   
   // set everything back to normal values
   gl->board[pr->i_board].range = pr->prev_range;
   gl->mux_flag                 = 0;
   gl->dcv_flag                 = 0;
   gl->dc_offset                = 0;
   gl->osctca_flag              = 0;
   gl->osctca_delay             = 0;
   wd_set_fe(gl, pr->i_board, -1);
   wd_set_dcv_flag(gl, pr->i_board);
   wd_set_dc_offset(gl, pr->i_board);
   wd_set_range(gl, pr->i_board);
   wd_set_osctca(gl, pr->i_board);
   
   // save calibration
   memcpy(gl->board[pr->i_board].tcalib.version_id, "CAL1", 4);
   gl->board[pr->i_board].tcalib.sampling_frequency = gl->actual_sampling_frequency;
   gl->board[pr->i_board].tcalib.temperature = gl->board[pr->i_board].temperature;
   
   sprintf(str, "calib/%s.tcal", gl->board[pr->i_board].name);
   pr->fh = open(str, O_WRONLY | O_CREAT, 0644);
   assert(pr->fh > 0);
   assert(write(pr->fh, &gl->board[pr->i_board].tcalib, sizeof(TCALIB_DATA)) == sizeof(TCALIB_DATA));
   close(pr->fh);
   
   // switch to next board
   pr->i_board++;
   pr->state             = WD_CS_FIRST_SAMPLE;
   pr->progress          = 1;
   gl->time_calib1_flag  = 0;
   gl->rotate_flag       = 0;
   
   if (pr->i_board == pr->n_board) {
      pr->state             = WD_CS_INACTIVE;
      gl->rotate_flag       = 1;
      gl->ofs_calib1_flag   = 1;
      gl->ofs_calib2_flag   = 1;
      gl->gain_calib_flag   = 1;
      gl->range_calib_flag  = 1;
      gl->remove_spikes     = 1;
      gl->time_calib1_flag  = 1;
      gl->time_calib2_flag  = 1;
   }
   
   return SUCCESS;
}

/*-----------------------------------------------------------------------------------------*/


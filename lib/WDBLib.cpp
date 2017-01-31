//
//  wd
//  WaveDAQ Ethernet Interface
//
//  Created by Stefan Ritt on 13/8/15.
//

#if 0
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>

#include "midas.h"
#include "experim.h"
#include "WD.h"
#include "register_map.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <assert.h>
#include <errno.h>

#include <exception>
#include <stdexcept>

#ifdef __linux__
#include <linux/sockios.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <pthread.h>
#endif
#ifdef __APPLE__
#include <net/if_dl.h>
#include <pthread.h>
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

int WDB::fDataSocket = 0;
int WDB::fServerPort = 0;

/*-----------------------------------------------------------------------------------------*/

int WDB::SendReceive(const char *str, char *result, int *size, int timeout_ms)
{
   size_t n, i;
   fd_set readfds;
   struct timeval timeout;
   int    status, ms;
   struct sockaddr_in client_addr;
   char   tx_buffer[1600], rx_buffer[1600], prompt[80];

   memcpy(&client_addr, fEthAddr, sizeof(client_addr));
   strlcpy(tx_buffer, str, sizeof(tx_buffer));
   if (tx_buffer[strlen(tx_buffer)-1] != '\n')
      strlcat(tx_buffer, "\n", sizeof(tx_buffer));

   if (result != NULL)
      memset(result, 0, *size);
   n = 0;

   // assemble prompt
   strlcpy(prompt, fName, sizeof(prompt));
   strlcat(prompt, " > ", sizeof(prompt));
   
   // retry max five times
   for (int retry=0 ; retry < 5 ; retry++) {
      
      // send request
      i = sendto(fCmdSocket,
                 tx_buffer,
                 strlen(tx_buffer),
                 0,
                 (struct sockaddr *)&client_addr,
                 sizeof(client_addr));
      
      if (i != strlen(tx_buffer)) {
         printf("%s send retry %d\n", fName, retry+1);
         continue;
      }
      
      // retrieve reply until prompt is found
      n = 0;
      do {
         memset(rx_buffer, 0, sizeof(rx_buffer));
         
         FD_ZERO(&readfds);
         FD_SET(fCmdSocket, &readfds);
         
         ms = timeout_ms;
         if (retry == 0) // first trial times out faster
            ms = 100;
         
         timeout.tv_sec = ms / 1000;
         timeout.tv_usec = (ms % 1000) * 1000;
         
         do {
            status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
         } while (status == -1);        /* dont return if an alarm signal was cought */
         
         if (!FD_ISSET(fCmdSocket, &readfds))
            break;
         
         i = recv(fCmdSocket, rx_buffer, sizeof(rx_buffer), 0);
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
      
      printf("%s retry %d\n", fName, retry+1);
   }

   if (n == 0) {
      if (size != NULL)
         *size = 0;
      throw std::runtime_error(std::string("Error sending \"")+str+"\" to "+fName);
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

int WDB::Send(const char *format, ...)
{
   char str[1000];
   
   va_list argptr;
   va_start(argptr, format);
   vsprintf(str, format, argptr);
   va_end(argptr);
   
   return WDB::SendReceive(str);
}

/*-----------------------------------------------------------------------------------------*/

int WDB::Init(TRIGGER_SETTINGS *ts, int iwd)
{
   struct sockaddr_in server_addr;
   struct sockaddr_in client_addr;
   char str[256], dir[256];
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

   // create UDB socket for command interpreter on any port
   fCmdSocket = socket(AF_INET, SOCK_DGRAM, 0);
   assert(fCmdSocket);
   
   // create UDB socket to receive binary data on port WD2_DATA_PORT
   if (fDataSocket == 0) {
      fDataSocket = socket(AF_INET, SOCK_DGRAM, 0);
      assert(fDataSocket);
      
      // bind socket to port chosen by OS
      memset((char*)&server_addr, 0, sizeof(server_addr));
      server_addr.sin_family = AF_INET;
      server_addr.sin_port = htons(0); // let OS choose port
      server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
      if (bind(fDataSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
         perror("bind");
         throw std::runtime_error(std::string("Cannot bind socket"));
      }
      size = sizeof(server_addr);
      getsockname(fDataSocket, (struct sockaddr *) &server_addr, (socklen_t *) &size);
      fServerPort = ntohs(server_addr.sin_port);
      
      printf("Listening on data port %d\n", fServerPort);
   }
   
   // retrieve Ethernet address of board
   phe = gethostbyname(fName);
   if (phe == NULL)
      throw std::runtime_error(std::string("Cannot resolve host name ")+fName);

   memcpy((char *)&client_addr.sin_addr, phe->h_addr, phe->h_length);
   client_addr.sin_family = AF_INET;
   client_addr.sin_port = htons(WD2_CMD_PORT);
   size = sizeof(client_addr);
   memcpy(fEthAddr, &client_addr, sizeof(client_addr));
   
   // check if board is alive
   try {
      SendReceive("", NULL, NULL, 500);
   } catch (...) {
      throw std::runtime_error(std::string("Cannot connect to board ")+fName);
   }
   
   // derive serial number from network name (for now...)
   fSerialNumber = atoi(fName+2);
   
   // set dbglevel none
   Send("dbglvl none");
   
   // set destinantion port in WD board
   sprintf(str, "setenv dstport %d", fServerPort);
   Send(str);
   
   // set MAC address and IP address of this computer in WD board
   Send("cfgdst");
   
   SetGain(ts->wdb[iwd].gain);
   SetPZC(ts->wdb[iwd].pzc);
   SetTriggerLevel(&ts->wdb[iwd].trigger_level[0]);
   SetClockSource(1);
   SetSamplingFrequency(ts->wdb[iwd].sampling_frequency);
  
   // Now some trigger setup: comparator mask and patterns
   SetMasks(ts, iwd);
   SetPatterns(ts, iwd);

   ConfigureBoard(iwd);
   
   // load voltage calibration for board from file (for now...)
   sprintf(str, "/home/meg/meg2/online/frontends/wd_fe/calib/%s.vcal", fName);
   int fh = open(str, O_RDONLY, 0644);
   if (fh < 0)
      throw std::runtime_error(std::string("Cannot find voltage calibration file \"")+str+"\"");

   size = read(fh, &fVCalib, sizeof(VCALIB_DATA));
   if (size != sizeof(VCALIB_DATA)) {
      close(fh);
      throw std::runtime_error(std::string("Invalid voltage calibration file size of \"")+str+"\"");
   }

   if (memcmp(fVCalib.version_id, "CAL1", 4) != 0) {
      close(fh);
      throw std::runtime_error(std::string("Invalid voltage calibration file format in \"")+str+"\"");
   }
   
   // set sampling frequency from calibration data
   if (fabs(fVCalib.sampling_frequency - fSamplingFrequency) > 0.01) {
      char err[1000];
      sprintf(err, "Warning: Voltage calibration data in \"%s/%s\" is for %3g GSPS, running now at %3g GSPS\n",
              dir, str, fVCalib.sampling_frequency, fSamplingFrequency);
      close(fh);
      throw std::runtime_error(std::string(err));
   }
   close(fh);
   
   // load timing calibration for board from file (for now...)
   sprintf(str, "/home/meg/meg2/online/frontends/wd_fe/calib/%s.tcal", fName);
   fh = open(str, O_RDONLY, 0644);
   if (fh < 0)
      throw std::runtime_error(std::string("Cannot find time calibration file \"")+str+"\"");

   size = read(fh, &fTCalib, sizeof(TCALIB_DATA));
   if (size != sizeof(TCALIB_DATA)) {
      close(fh);
      throw std::runtime_error(std::string("Invalid time calibration file size of \"")+str+"\"");
   }
   
   if (memcmp(fTCalib.version_id, "CAL1", 4) != 0) {
      close(fh);
      throw std::runtime_error(std::string("Invalid time calibration file format in \"")+str+"\"");
   }
   
   close(fh);
   
   return SUCCESS;
}

/*-----------------------------------------------------------------------------------------*/

void WDB::SetTriggerLevel(int *tl)
{
   fTriggerLevel[0] = tl[0];
   fTriggerLevel[1] = tl[1];
   fTriggerLevel[2] = tl[2];
   fTriggerLevel[3] = tl[3];
}

/*-----------------------------------------------------------------------------------------*/

void WDB::ConfigureBoard(int iwd)
{
   char str[80];
   int byte;
   
   // set LED red
   Send("ledset r");

   // set dbglevel none
   Send("dbglvl none");
   
   // set input configuration
   byte = 0;
   if (fPZC) { // pole zero cancellation on (bit=0)
      if (fGain == 0)
         byte = 0x02;
      else if (fGain == 1)
         byte = 0x0a;
      else if (fGain == 2)
         byte = 0x2a;
   } else { // pole zero cancellation off (bit=1)
      if (fGain == 0)
         byte = 0x82;
      else if (fGain == 1)
         byte = 0x8a;
      else if (fGain == 2)
         byte = 0xaa;
   }
   
   sprintf(str, "feset all %02X", byte);
   Send(str);
   
   // trun on comparator power
   Send("pwrcmp on");

   // set comparator level
   Send("dacset tlevel1 %d", fTriggerLevel[0]/2+900);
   Send("dacset tlevel2 %d", fTriggerLevel[1]/2+900);
   Send("dacset tlevel3 %d", fTriggerLevel[2]/2+900);
   Send("dacset tlevel4 %d", fTriggerLevel[3]/2+900);

   // set range to -0.95V ... +0.05V
   if (fGain == 2)
      Send("dacset ofs 1640");
   else
      Send("dacset ofs 2000");
   
   // set DACs
   Send("dacset bias 700");
   Send("dacset rofs 1550");
   Send("dacset caldc 1280");

   // disable local trigger
   Send("regwr %02x 00000000", REG_TRIGGER_CFG_A_OFFSET);
   
   // trigger_enable, trigger_falling_edge, enable external trigger
   // set the trigger delay to be 0x3F and the signal shaping 4 (80MHz clk cycles)
   Send("regwr %02x 040E0034", REG_TRIGGER_CFG_OFFSET);
   
   // set DRS readout mode to ROI and drs_active
   Send("regwr %02x 17170030", REG_CONTROL_OFFSET);
   
   // set clock source
   if (fClockSource == 1)
      Send("regclr %02x 20000", REG_CLK_CALIB_CTRL_OFFSET);
   else
      Send("regset %02x 20000", REG_CLK_CALIB_CTRL_OFFSET);
   
   // set inter-packet delay
   Send("regwr %02x FF00", REG_COM_CONTROL_OFFSET);
   
   // set LMK registers to their defaults, see "LMK regs.xls"
   Send("regwr %02x 00032800", REG_LMK_0_OFFSET);
   Send("regwr %02x 00020101", REG_LMK_1_OFFSET);
   Send("regwr %02x 00020102", REG_LMK_2_OFFSET);
   Send("regwr %02x 029900AD", REG_LMK_13_OFFSET);
   Send("regwr %02x 0830140E", REG_LMK_14_OFFSET);
   Send("regwr %02x D800280F", REG_LMK_15_OFFSET);

   // set LMK register to current sampling frequency
   int divider = (int) (200.0 / fSamplingFrequency * 2.048 / 2 + 0.5);
   Send("regwr %02x 0003%02X00", REG_LMK_0_OFFSET, divider);

   // initialize FSM and frame counter
   Send("drsreinit");
   
   // set LED red
   Send("ledset g");
}

/*-----------------------------------------------------------------------------------------*/

int WDB::StartDRS()
{
   return Send("drsstart");
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

namespace {
  // waveform buffer for one event
  float wf[16][16][1024];
  float waveform[16][16][1024];
  int   triggerCell[16][2];
  float wft[16][16][1024];
  float wftime[16][16][1024];
  int   new_event = 0;
  int   _nWdb;
}

void *wdb_collector(void *param);

/*-----------------------------------------------------------------------------------------*/

int wdb_start_collector(WDB *wdb[], int nWdb)
{
   INT status;
   pthread_t thread_id;

   _nWdb = nWdb;
   status = pthread_create(&thread_id, NULL, wdb_collector, (void *)wdb);
   return status;
}

/*-----------------------------------------------------------------------------------------*/

int wdb_read_waveform(float *pwf, int *ptc, float *pwft)
{
   double start_time;
   
   start_time = time_ms();
   while (!new_event) {
      sleep(10);
      
      // time-out after one second
      if (time_ms() - start_time > 1000)
         return 0;
   }
   
   memcpy(pwf, waveform, sizeof(float)*_nWdb*16*1024);
   memcpy(ptc, triggerCell, sizeof(int)*_nWdb*2);
   memcpy(pwft, wftime, sizeof(float)*_nWdb*16*1024);
   
   new_event = 0;
   return 1;
}

/*-----------------------------------------------------------------------------------------*/

void *wdb_collector(void *param)
{
   int i, b, c, s, status, current_frame, np;
   fd_set readfds;
   struct timeval timeout;
   struct sockaddr_in remote_addr;
   WD2_FRAME_HEADER *ph;
   unsigned char *pd;
   short data1, data2;
   unsigned char buffer[1800];
   int header_adc, header_channel, waveform_channel, board;

   WDB **wdb = (WDB **)param;
   s = wdb[0]->fDataSocket;
   current_frame = -1;
   np = 0;
   for (int b=0 ; b<_nWdb ; b++)
      for (int c=0 ; c<16 ; c++) {
         wf[b][c][0]   = nanf("");
         wf[b][c][512] = nanf("");
      }

   while (1) {

      FD_ZERO(&readfds);
      FD_SET(s, &readfds);
      
      timeout.tv_sec = 1;
      timeout.tv_usec = 0;
      
      do {
         status = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
      } while (status == -1 && errno == EINTR);  // don't return if an alarm signal was caught
      
      if (status == -1)
         perror("select");
      
      if (FD_ISSET(s, &readfds)) {
         int len, n;
         
         // packet is available, so receive it
         len = sizeof(remote_addr);
         n = (int)recvfrom(s, (char *)buffer, sizeof(buffer), 0,
                           (struct sockaddr *)&remote_addr, (socklen_t *)&len);
         if (n > (int)sizeof(WD2_FRAME_HEADER)) {
            ph = (WD2_FRAME_HEADER *)buffer;
            np++;
            
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

            /*
            printf("%5d, From %s, Board %2d, Frame %5d, ADC/Chn/Segment %d/%d/%d\n",
                   np,
                   inet_ntoa(remote_addr.sin_addr),
                   ph->board_id,
                   ph->readout_sequence_number,
                   header_adc,
                   header_channel,
                   ph->channel_segment_number);
            */
            
            if (current_frame == -1)
               current_frame = ph->readout_sequence_number;
            
            // drop package if it belongs to older frame
            if (ph->readout_sequence_number < current_frame) {
               printf("Package dropped, package frame=%d, current frame=%d, board id = %d\n", ph->readout_sequence_number, current_frame, ph->board_id);
               continue;
            }
            
            // drop whole frame if package of next frame received
            if (ph->readout_sequence_number > current_frame) {
               printf("Frame dropped, package frame=%d, current frame=%d\n", ph->readout_sequence_number, current_frame);
               
               // switch to new frame
               current_frame = ph->readout_sequence_number;
               
               // tag waveforms as invalid
               for (int b=0 ; b<_nWdb ; b++)
                  for (int c=0 ; c<16 ; c++) {
                     wf[b][c][0]   = nanf("");
                     wf[b][c][512] = nanf("");
                  }

               np = 1;
            }
            
            waveform_channel = header_adc*8+header_channel;
            assert(waveform_channel < 16);
            
            // ensure board id is in our receive list
            for (i=0 ; i<_nWdb ; i++)
               if (ph->board_id == wdb[i]->fSerialNumber)
                  break;
            assert(i < _nWdb);
            board = i;
            
            // copy trigger cell
            if (waveform_channel < 8)
               triggerCell[board][0] = ph->drs0_trigger_cell;
            else
               triggerCell[board][1] = ph->drs1_trigger_cell;
            
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
                  wf[board][waveform_channel][i]       = (float)data1 * (1 / 4096.0); // 1V DRS range with 12 bits
                  wf[board][waveform_channel][i+1]     = (float)data2 * (1 / 4096.0);
               } else {
                  // second segment
                  wf[board][waveform_channel][512+i]   = (float)data1 * (1 / 4096.0);
                  wf[board][waveform_channel][512+i+1] = (float)data2 * (1 / 4096.0);
               }
            }
         }
      }
      
      // check if we got all fragments
      for (b=i=0 ; b<_nWdb ; b++)
         for (c=0 ; c<16 ; c++)
            if (!isnan(wf[b][c][0]) && !isnan(wf[b][c][512]))
               i++;
      if (i == _nWdb*16) {

         // cell-by-cell offset calibration
         for (b=0 ; b<_nWdb ; b++) {
            for (c=0 ; c<16 ; c++) {
               int tc = c<8 ? triggerCell[b][0] : triggerCell[b][1];
               for (i=0 ; i<1024 ; i++)
                  wf[b][c][i] -= wdb[b]->fVCalib.wf_offset1[c][(i+tc)%1024];
            }
         }

         // gain calibration
         for (b=0 ; b<_nWdb ; b++) {
            for (c=0 ; c<16 ; c++) {
               int tc = c<8 ? triggerCell[b][0] : triggerCell[b][1];
               for (int i=0 ; i<1024 ; i++) {
                  if (wf[b][c][i] > 0)
                     wf[b][c][i] /= wdb[b]->fVCalib.wf_gain1[c][(i+tc) % 1024];
                  else
                     wf[b][c][i] /= wdb[b]->fVCalib.wf_gain2[c][(i+tc) % 1024];
               }
            }
         }

         // start-to-end offset calibration
         for (b=0 ; b<_nWdb ; b++) {
            for (c=0 ; c<16 ; c++)
               for (i=0 ; i<1024 ; i++)
                  wf[b][c][i] -= wdb[b]->fVCalib.wf_offset2[c][i];
         }
         
         // range calibration
         for (b=0 ; b<_nWdb ; b++)
            for (c=0 ; c<16 ; c++)
               for (int i=0 ; i<1024 ; i++)
                  wf[b][c][i] -= wdb[b]->fVCalib.drs_offset_range0[c]; // -0.95 ... 0.05 V

         // calculate calibrated time for each bin

         // integrate time from delta-t values
         for (b=0 ; b<_nWdb ; b++) {
            for (c=0 ; c<16 ; c++) {
               int tc = c<8 ? triggerCell[b][0] : triggerCell[b][1];
               wft[b][c][0] = 0;
               for (int i=1 ; i<1024 ; i++)
                  wft[b][c][i] = wft[b][c][i-1] + wdb[b]->fTCalib.dt[c][(i-1+tc)%1024];
            }
            // align cell#0 of all channels inside chip0
            float t1 = wft[b][0][(1024-triggerCell[b][0]) % 1024];
            for (c=1 ; c<8 ; c++) {
               float t2 = wft[b][c][(1024-triggerCell[b][0]) % 1024];
               float dt = t1 - t2;
               for (int i=0 ; i<1024 ; i++)
                  wft[b][c][i] += dt;
            }
            // align cell#0 of all channels inside chip1 to chip0
            for (c=8 ; c<16 ; c++) {
               float t2 = wft[b][c][(1024-triggerCell[b][1]) % 1024];
               float dt = t1 - t2;
               for (int i=0 ; i<1024 ; i++)
                  wft[b][c][i] += dt;
            }
         }
         
         // copy waveform to buffer and signal new event
         memcpy(waveform, wf, sizeof(waveform));
         memcpy(wftime, wft, sizeof(wftime));
         new_event = 1;
         current_frame = -1;
         np = 0;

         // tag waveforms as invalid
         for (int b=0 ; b<_nWdb ; b++)
            for (int c=0 ; c<16 ; c++) {
               wf[b][c][0]   = nanf("");
               wf[b][c][512] = nanf("");
            }

      }
   }
}

// this funtion sets a link from WD to TCB to be AND/OR/Pattern
// this is written on the word type
// 0 = AND
// 1 = OR
// 2 = PATTERN
// 3 = UNUSED
void WDB::SetTCBLink(int ltype, int port)
{
   //first reset the bits
   Send("regclr %x %x", REG_TRIGGER_SCHEME_SELECT_OFFSET, (3<<14)>>(port*2));
   // then set them
   Send("regset %x %x", REG_TRIGGER_SCHEME_SELECT_OFFSET, (ltype<<14)>>(port*2));
}

//THIS FUNCTION SET THE PATTERNS TO A WDB TAKEN FROM ODB (ONE SET FOR THE WHOLE SYSTEM SO FAR)
void WDB::SetPatterns(TRIGGER_SETTINGS *ts,int iwd)
{
   // first load the pattern enable
   for(int ipatten = 0; ipatten<8; ipatten++)
      Send("regwr %x %x", 4*ipatten+REG_TRIGGER_PATTERN_EN_BPL0_OFFSET, ts->wdb[iwd].pattern_enable[ipatten]);
   // then load the patterns itself
   for(int ipatt = 0; ipatt<32; ipatt++)
      Send("regwr %x %x", 4*ipatt+REG_TRIGGER_PATTERN0_OFFSET, ts->wdb[iwd].pattern[ipatt]);
}

// SET THE MASKS FROM ODB (ONE MASK SETTING PER BOARD PER CHANNEL)
void WDB::SetMasks(TRIGGER_SETTINGS *ts, int iwd)
{
   Send("regwr %x %x", REG_TRIGGER_COMP_MASK_OFFSET, ts->wdb[iwd].masks);
}

#endif // 0

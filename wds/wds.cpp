//
//  wds.cpp
//  WaveDAQ Server Application
//
//  Created by Stefan Ritt on 5/8/15.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#ifdef _MSC_VER
#include <time.h>
#else
#include <getopt.h>
#endif

#include "averager.h"
#include "wds.h"
#include "mongoose.h"

#define CMD_VOLTAGE_CALIB 1
#define CMD_TIME_CALIB 2

VCALIB_PROGRESS vcalib_prog;
TCALIB_PROGRESS tcalib_prog;

/*-----------------------------------------------------------------------------------------*/

static struct mg_serve_http_opts s_http_server_opts;

// This function will be called by mongoose on every new request
static void wds_handler(struct mg_connection *nc, int event, void *p)
{
   char str[256], value[256];
   GLOBALS *gl;
   WD2_EVENT eventHeader;
   
   struct http_message *hm = (struct http_message *)p;
   
   gl = (GLOBALS *)nc->mgr->user_data;
   
   if (event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->method, "PUT") == 0) {
      
      value[0] = 0;
      if (hm->body.p) {
         strlcpy(value, hm->body.p, sizeof(value));
         value[hm->body.len] = 0;
      }

      if (mg_vcmp(&hm->uri, "/gl/pzc") == 0) {
         for (int i=0 ; i<gl->n_boards ; i++) {
            gl->board[i].pzc = atoi(value);
            wd_set_fe(gl, i);
         }
      }
      
      else if (mg_vcmp(&hm->uri, "/gl/gain") == 0) {
         for (int i=0 ; i<gl->n_boards ; i++) {
            gl->board[i].gain = atoi(value);
            wd_set_fe(gl, i);
         }
      }

      else if (mg_vcmp(&hm->uri, "/gl/trigger_level") == 0) {
         for (int i=0 ; i<gl->n_boards ; i++) {
            gl->board[i].trigger_level = (float)atof(value);
            if (gl->board[i].trigger_level > 0.5)
               gl->board[i].trigger_level = 0.5;
            if (gl->board[i].trigger_level < -0.5)
               gl->board[i].trigger_level = -0.5;
            wd_set_trigger_level(gl, i);
         }
      }

      else if (mg_vcmp(&hm->uri, "/gl/trigger_delay") == 0) {
         for (int i=0 ; i<gl->n_boards ; i++) {
            gl->board[i].trigger_delay = (float)atof(value);
            if (gl->board[i].trigger_delay > 500)
               gl->board[i].trigger_delay = 500;
            if (gl->board[i].trigger_delay < 0)
               gl->board[i].trigger_delay = 0;
            wd_set_trigger_mode(gl, i);
         }
      }

      else if (mg_vcmp(&hm->uri, "/gl/trigger_mode") == 0) {
         gl->trigger_mode = atoi(value);
         for (int i=0 ; i<gl->n_boards ; i++)
            wd_set_trigger_mode(gl, i);
      }

      else if (mg_vcmp(&hm->uri, "/gl/osctca_flag") == 0) {
         gl->osctca_flag = atoi(value);
         gl->mux_flag = atoi(value);
         gl->dcv_flag = atoi(value);
         for (int i=0 ; i<gl->n_boards ; i++) {
            wd_set_osctca(gl, i);
            wd_set_fe(gl, i);
            wd_set_dcv_flag(gl, i);
         }
      }

      else if (mg_vcmp(&hm->uri, "/gl/clock_source") == 0) {
         gl->clock_source = atoi(value);
         for (int i=0 ; i<gl->n_boards ; i++) {
            wd_set_clocksource(gl, i);
            wd_read_board_status(gl, i); // check LMK PLL lock
         }
      }

      else if (mg_vcmp(&hm->uri, "/gl/nominal_sampling_frequency") == 0) {
         gl->nominal_sampling_frequency = (float)(atof(value));
         for (int i=0 ; i<gl->n_boards ; i++)
            wd_set_sampling_frequency(gl, i);
      }

      else if (mg_vcmp(&hm->uri, "/gl/range") == 0) {
         for (int i=0 ; i<gl->n_boards ; i++) {
            gl->board[i].range = (float)atof(value);
            wd_set_range(gl, i);
         }
      }

      else if (mg_vcmp(&hm->uri, "/gl/mux_flag") == 0) {
         gl->mux_flag = atoi(value);
         for (int i=0 ; i<gl->n_boards ; i++)
            wd_set_fe(gl, i);
      }

      else if (mg_vcmp(&hm->uri, "/gl/dcv_flag") == 0) {
         gl->dcv_flag = atoi(value);
         for (int i=0 ; i<gl->n_boards ; i++)
            wd_set_dcv_flag(gl, i);
      }

      else if (mg_vcmp(&hm->uri, "/gl/dcv") == 0) {
         gl->dcv = (float)atof(value);
         for (int i=0 ; i<gl->n_boards ; i++)
            wd_set_dcv(gl, i);
      }

      else if (mg_vcmp(&hm->uri, "/gl/adc_flag") == 0) {
         gl->adc_flag = atoi(value);
         if (gl->adc_flag)
            gl->actual_sampling_frequency = 0.080f; // ADC 80 MHz
         else
            wd_set_sampling_frequency(gl, 0);
      }

      else if (mg_vcmp(&hm->uri, "/gl/ofs_calib1_flag") == 0)
         gl->ofs_calib1_flag = atoi(value);
      else if (mg_vcmp(&hm->uri, "/gl/ofs_calib2_flag") == 0)
         gl->ofs_calib2_flag = atoi(value);
      else if (mg_vcmp(&hm->uri, "/gl/gain_calib_flag") == 0)
         gl->gain_calib_flag = atoi(value);
      else if (mg_vcmp(&hm->uri, "/gl/range_calib_flag") == 0)
         gl->range_calib_flag = atoi(value);
      else if (mg_vcmp(&hm->uri, "/gl/remove_spikes") == 0)
         gl->remove_spikes = atoi(value);
      else if (mg_vcmp(&hm->uri, "/gl/rotate_flag") == 0)
         gl->rotate_flag = atoi(value);
      else if (mg_vcmp(&hm->uri, "/gl/time_calib1_flag") == 0)
         gl->time_calib1_flag = atoi(value);
      else if (mg_vcmp(&hm->uri, "/gl/time_calib2_flag") == 0)
         gl->time_calib2_flag = atoi(value);
      else if (mg_vcmp(&hm->uri, "/gl/time_calib3_flag") == 0)
         gl->time_calib3_flag = atoi(value);

      else if (mg_vcmp(&hm->uri, "/vcalib") == 0) {
         if (!gl->demo_flag)
            vcalib_prog.state = CS_FIRST_BOARD;
      }

      else if (mg_vcmp(&hm->uri, "/tcalib") == 0) {
         if (!gl->demo_flag) {
            mg_get_http_var(&hm->query_string, "b", str, sizeof(str));
            if (str[0]) {
               int b = atoi(str);
               tcalib_prog.state = CS_SINGLE_BOARD;
               tcalib_prog.i_board = b;
            } else
               tcalib_prog.state = CS_FIRST_BOARD;
         }
      }

      else if (mg_vcmp(&hm->uri, "/tcaliball") == 0) {
         if (!gl->demo_flag)
            tcalib_prog.state = CS_FIRST_BOARD;
      }

      mg_printf(nc, "HTTP/1.1 204 No Content\r\n");
   }
   
   // gloabls
   if (event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/gl") == 0) {
      if (gl->verbose_flag)
         printf("Load /gl\n");
      
      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");
      
      mg_printf_http_chunk(nc, "{\n");
      mg_printf_http_chunk(nc, "   \"demo_flag\": %s,\n",          gl->demo_flag ? "true" : "false");
      mg_printf_http_chunk(nc, "   \"rotate_flag\": %s,\n",        gl->rotate_flag ? "true" : "false");
      mg_printf_http_chunk(nc, "   \"verbose_flag\": %s,\n",       gl->verbose_flag ? "true" : "false");
      mg_printf_http_chunk(nc, "   \"adc_flag\": %s,\n",           gl->adc_flag ? "true" : "false");
      mg_printf_http_chunk(nc, "   \"ofs_calib1_flag\": %s,\n",    gl->ofs_calib1_flag ? "true" : "false");
      mg_printf_http_chunk(nc, "   \"ofs_calib2_flag\": %s,\n",    gl->ofs_calib2_flag ? "true" : "false");
      mg_printf_http_chunk(nc, "   \"gain_calib_flag\": %s,\n",    gl->gain_calib_flag ? "true" : "false");
      mg_printf_http_chunk(nc, "   \"range_calib_flag\": %s,\n",   gl->range_calib_flag ? "true" : "false");
      mg_printf_http_chunk(nc, "   \"time_calib1_flag\": %s,\n",   gl->time_calib1_flag ? "true" : "false");
      mg_printf_http_chunk(nc, "   \"time_calib2_flag\": %s,\n",   gl->time_calib2_flag ? "true" : "false");
      mg_printf_http_chunk(nc, "   \"time_calib3_flag\": %s,\n",   gl->time_calib3_flag ? "true" : "false");
      mg_printf_http_chunk(nc, "   \"remove_spikes\": %s,\n",      gl->remove_spikes ? "true" : "false");
      mg_printf_http_chunk(nc, "   \"http_port\": %d,\n",          gl->http_port);
      mg_printf_http_chunk(nc, "   \"n_boards\": %d,\n",           gl->n_boards);
      mg_printf_http_chunk(nc, "   \"nominal_sampling_frequency\": %1.3lf,\n", gl->nominal_sampling_frequency);
      mg_printf_http_chunk(nc, "   \"actual_sampling_frequency\": %1.3lf,\n", gl->actual_sampling_frequency);
      mg_printf_http_chunk(nc, "   \"trigger_mode\": %d,\n",       gl->trigger_mode);
      mg_printf_http_chunk(nc, "   \"osctca_flag\": %s,\n",        gl->osctca_flag ? "true" : "false");
      mg_printf_http_chunk(nc, "   \"clock_source\": %d,\n",       gl->clock_source);
      mg_printf_http_chunk(nc, "   \"mux_flag\": %s,\n",           gl->mux_flag ? "true" : "false");
      mg_printf_http_chunk(nc, "   \"dcv_flag\": %s,\n",           gl->dcv_flag ? "true" : "false");
      mg_printf_http_chunk(nc, "   \"dcv\": %1.3lf,\n",            gl->dcv);
      
      mg_printf_http_chunk(nc, "   \"board\": [\n");
      
      for (int i=0 ; i<gl->n_boards ; i++) {
         mg_printf_http_chunk(nc, "      {\n");
         mg_printf_http_chunk(nc, "         \"name\": \"%s\" ,\n",         gl->board[i].name);
         mg_printf_http_chunk(nc, "         \"trigger_level\": %1.3lf,\n", gl->board[i].trigger_level);
         mg_printf_http_chunk(nc, "         \"trigger_delay\": %1.0lf,\n", gl->board[i].trigger_delay);
         mg_printf_http_chunk(nc, "         \"trigger_mask\": \"%s\",\n",  gl->board[i].trigger_mask);
         mg_printf_http_chunk(nc, "         \"gain\": %d,\n",              gl->board[i].gain);
         mg_printf_http_chunk(nc, "         \"pzc\": %s,\n",               gl->board[i].pzc ? "true" : "false");
         mg_printf_http_chunk(nc, "         \"range\": %1.3lf,\n",         gl->board[i].range);
         mg_printf_http_chunk(nc, "         \"temperature\": %1.1lf,\n",   gl->board[i].temperature);
         mg_printf_http_chunk(nc, "         \"pll_locked\": %s,\n",        gl->board[i].pll_locked ? "true" : "false");
         mg_printf_http_chunk(nc, "         \"scaler\": [\n");
         int s;
         for (s=0 ; s<15 ; s++)
            mg_printf_http_chunk(nc, "            %d,\n", gl->board[i].scaler[s]);
         mg_printf_http_chunk(nc, "            %d]\n", gl->board[i].scaler[s]);
         mg_printf_http_chunk(nc, "      }\n");
         if (i<gl->n_boards-1)
            mg_printf_http_chunk(nc, ",");
         mg_printf_http_chunk(nc, "\n");
      }
      
      mg_printf_http_chunk(nc, "   ]\n");
      
      mg_printf_http_chunk(nc, "}\n");
      
      mg_send_http_chunk(nc, "", 0); // end of response
      return;
   }
   
   // temperature
   if (event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/status") == 0) {
      mg_get_http_var(&hm->query_string, "b", str, sizeof(str));
      int b = atoi(str);

      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");
      mg_printf_http_chunk(nc, "{\n");
      mg_printf_http_chunk(nc, "   \"temp\": %1.1lf,\n",   gl->board[b].temperature);
      mg_printf_http_chunk(nc, "   \"pll_locked\": %s\n",  gl->board[b].pll_locked ? "true" : "false");
      mg_printf_http_chunk(nc, "}\n");
      mg_send_http_chunk(nc, "", 0);
      return;
   }

   // scalers
   if (event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/scalers") == 0) {
      mg_get_http_var(&hm->query_string, "b", str, sizeof(str));
      int b = atoi(str);
      
      wd_read_scalers(gl, b);
      
      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");
      mg_printf_http_chunk(nc, "{\n");
      mg_printf_http_chunk(nc, "         \"scaler\": [\n");
      int s;
      for (s=0 ; s<15 ; s++)
         mg_printf_http_chunk(nc, "            %d,\n", gl->board[b].scaler[s]);
      mg_printf_http_chunk(nc, "            %d]\n", gl->board[b].scaler[s]);
      mg_printf_http_chunk(nc, "}\n");
      mg_send_http_chunk(nc, "", 0);
      return;
   }

   // software build
   if (event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/build") == 0) {
      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");
      mg_printf_http_chunk(nc, "{\n");
      mg_printf_http_chunk(nc, "   \"build\": \"%s\"\n", __DATE__);
      mg_printf_http_chunk(nc, "}\n");
      mg_send_http_chunk(nc, "", 0);
      return;
   }

   // binary encoded waveforms
   if (event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/wf") == 0) {
      float wfT[16][1024], wfU[16][1024];
      int status;

      mg_get_http_var(&hm->query_string, "b", str, sizeof(str));
      int b = atoi(str);

      mg_get_http_var(&hm->query_string, "c", str, sizeof(str));
      int chn = atoi(str);

      mg_send_response_line(nc, 200, "Content-Type: application/octet-stream\r\nTransfer-Encoding: chunked\r\n");

      // return progress if in voltage calibration mode
      if (vcalib_prog.state) {
         int t = 10;    // array type
         mg_send_http_chunk(nc, (const char *)&t, 4);
         
         mg_send_http_chunk(nc, (const char *)&vcalib_prog.i_board, 4);
         
         float f = (float)vcalib_prog.progress;
         mg_send_http_chunk(nc, (const char *)&f, 4);
         
         mg_send_http_chunk(nc, "", 0);
         return;
      }

      // return progress and period in time calibration mode
      if (tcalib_prog.state) {
         int t = 11;    // array type
         mg_send_http_chunk(nc, (const char *)&t, 4);
         
         float f = (float)tcalib_prog.i_board;
         mg_send_http_chunk(nc, (const char *)&f, 4);
         
         f = (float)tcalib_prog.progress;
         mg_send_http_chunk(nc, (const char *)&f, 4);
         
         for (int c=0 ; c<16 ; c++)
            if (chn & (1 << c)) {
               int n = 1024;
               mg_send_http_chunk(nc, (const char *)&c, 4);
               mg_send_http_chunk(nc, (const char *)&n, 4);

               mg_send_http_chunk(nc, (const char *)gl->board[tcalib_prog.i_board].tcalib.period[c], sizeof(float)*n);
            }

         mg_send_http_chunk(nc, "", 0);
         return;
      }

      // avoid invalid board index
      if (b < 0 || b >= gl->n_boards)
         b = 0;
      
      if (gl->demo_flag) {
         status = SUCCESS;
         for (int c=0 ; c<16 ; c++) {
            for (int i=0 ; i<1024 ; i++) {
               wfT[c][i] = (float)(i*1E-9 / gl->actual_sampling_frequency);
               wfU[c][i] = (float)(sin((wfT[c][i]+c*1E-9)*gl->actual_sampling_frequency / 1E-9 / 50) / 4 + ((float)random()/RAND_MAX-0.5) / 300);
            }
            // add spikes
            for (int i=0 ; i<1024 ; i++) {
               if ((float)random()/RAND_MAX < 0.00005) {
                  float s = ((float)random()/RAND_MAX-0.5) / 5;
                  int j = i-5;
                  float f;
                  for (f=0 ; f<1 ; f += 0.2,j++)
                     if (j >= 0 && j< 1024)
                        wfU[c][j] += s * f;
                  for (f=1 ; f>0 ; f -= 0.2,j++)
                     if (j >= 0 && j< 1024)
                        wfU[c][j] += s * f;
               }
            }
         }
      } else {

         if (gl->adc_flag) {
            // issue single ADC software trigger
            wd_send(gl, b, 100, "adcget\n", NULL, NULL);
         } else {
            if (gl->trigger_mode == TM_AUTO)
               // issue single DRS software trigger
               wd_send(gl, b, 100, "drsget\n", NULL, NULL);
            else
               // just start DRS and wait for trigger
               wd_send(gl, b, 100, "drsstart\n", NULL, NULL);
         }
         // read waveforms
         status = wd_read_waveform(gl, b, 1000, &eventHeader, wfU, wfT);
      }

      if (gl->demo_flag)
         b = 0xFF; // signals demo data
      
      if (status == SUCCESS) {
         int t = 1;    // array type
         int n = 1024; // number of elements
         int f = 0;    // frame number
         for (int c=0 ; c<16 ; c++) {
            if (chn & (1 << c)) {
               t = 1; // time array
               mg_send_http_chunk(nc, (const char *)&t, 4);
               mg_send_http_chunk(nc, (const char *)&b, 4);
               mg_send_http_chunk(nc, (const char *)&f, 4);
               mg_send_http_chunk(nc, (const char *)&c, 4);
               mg_send_http_chunk(nc, (const char *)&n, 4);
               mg_send_http_chunk(nc, (const char *)wfT[c], sizeof(float)*n);
            }
         }
         
         for (int c=0 ; c<16 ; c++) {
            if (chn & (1 << c)) {
               t = 2; // voltage array
               mg_send_http_chunk(nc, (const char *)&t, 4);
               mg_send_http_chunk(nc, (const char *)&b, 4);
               mg_send_http_chunk(nc, (const char *)&f, 4);
               mg_send_http_chunk(nc, (const char *)&c, 4);
               mg_send_http_chunk(nc, (const char *)&n, 4);
               mg_send_http_chunk(nc, (const char *)wfU[c], sizeof(float)*n);
            }
         }
         
      } else {
         // just return idle message
         int t = 0;
         mg_send_http_chunk(nc, (const char *)&t, 4);
         mg_send_http_chunk(nc, (const char *)&b, 4);
      }

      mg_send_http_chunk(nc, "", 0);

      return;
   }

   // globals PUT
   /*
   if (event == MG_RECV && strcmp(conn->uri, "/gl") == 0) {
      return MG_TRUE;
   }
   */
   
   // file serving
   if (event == MG_EV_HTTP_REQUEST) {
      mg_serve_http(nc, hm, s_http_server_opts);
   }
   
}

/*-----------------------------------------------------------------------------------------*/

int main(int argc, char *argv[]) 
{
   int i, j, i1, i2, cmd = 0;
   GLOBALS gl;
   char str[256], *p;
   
   memset(&gl, 0, sizeof(gl));
   gl.http_port                  = 8080; // default port
   gl.nominal_sampling_frequency = 0;
   gl.actual_sampling_frequency  = 0;
   gl.ofs_calib1_flag            = 1;
   gl.ofs_calib2_flag            = 1;
   gl.gain_calib_flag            = 1;
   gl.range_calib_flag           = 1;
   gl.rotate_flag                = 1;
   gl.remove_spikes              = 1;
   gl.time_calib1_flag           = 1;
   gl.time_calib2_flag           = 1;
   gl.time_calib3_flag           = 0;
   gl.trigger_mode               = TM_AUTO;
   gl.osctca_flag                = 0;
   gl.clock_source               = 0;
   gl.mux_flag                   = 0;
   gl.dcv_flag                   = 0;
   gl.dcv                        = 0;
   gl.adc_flag                   = 0;

   for (i=0 ; i<16 ; i++) {
      gl.board[i].trigger_level  = 0;
      gl.board[i].trigger_delay  = 0;
      gl.board[i].gain           = 0;       // gain 1
      gl.board[i].range          = 0;       // range +-0.5V
      gl.board[i].pzc            = 0;       // PZC off
      strlcpy(gl.board[i].trigger_mask, "FFFF0000", sizeof(gl.board[i].trigger_mask)); // or of all 16 channels
   }
   
   i1 = 0;
   i2 = 15;
   
   // parse command line parameters
   for (i=1 ; i<argc ; i++) {
      if (argv[i][0] == '-' && argv[i][1] == 'd')
         gl.demo_flag = 1;
      
      else if (argv[i][0] == '-' && argv[i][1] == 'm') {
         if (strlen(argv[i+1]) != 8) {
            printf("invalid trigger mask, please use xxxxyyyy\n");
            return 1;
         }
         for (j=0 ; j<16 ; j++)
            strlcpy(gl.board[j].trigger_mask, argv[i+1], sizeof(gl.board[j].trigger_mask));
         i++;
      }
      
      else if (argv[i][0] == '-' && argv[i][1] == 'p')
         gl.http_port = atoi(argv[++i]);

      else if (argv[i][0] == '-' && argv[i][1] == 'v')
         gl.verbose_flag = 1;

      else if (argv[i][0] == '-' && argv[i][1] == 'w') {
         
         if (isdigit(argv[i+1][0]) && !strchr(argv[i+1], '.')) {
            if (strchr(argv[i+1], '-')) {
               i1 = atoi(argv[i+1]);
               p = strchr(argv[i+1], '-') + 1;
               i2 = atoi(p);
               if (i1 >= 0 && i1 < 14 && i2>0 && i2<16) {
                  for (int j=i1 ; j<=i2; j++) {
                     sprintf(gl.board[gl.n_boards++].name, "wd%03d", j);
                  }
               } else {
                  printf("invalid argument \"-w %s\"\n", argv[i+1]);
                  return 1;
               }
            } else if (argc > i+1 && isdigit(argv[i+1][0])) {
               while (argc > i+1 && isdigit(argv[i+1][0])) {
                  sprintf(gl.board[gl.n_boards++].name, "wd%03d", atoi(argv[i+1]));
                  i++;
               }
               continue;
            } else
               sprintf(gl.board[gl.n_boards++].name, "wd%03d", atoi(argv[i+1]));
         } else
            strlcpy(gl.board[gl.n_boards++].name, argv[i+1], 32);
         i++;
      }

      else if (argv[i][0] == '-' && argv[i][1] == 'z') {
         for (j=0 ; j<16 ; j++)
            gl.board[j].pzc = 1;
      }

      else {
         printf("usage: wsd [options] [-w <address> [-w <address> ...]]\n");
         printf("valid options:\n");
         printf(" -d                 Demo mode\n");
         printf(" -m <mask>          Trigger mask xxxxyyyy (xxxx=16 bit OR, yyyy=16bit AND)\n");
         printf(" -p <port>          HTTP server port\n");
         printf(" -w <a1> [<a2> ...] Internet address(es) of WaveDREAM board(s)\n");
         printf(" -v                 Print extra debugging information\n");
         return 1;
      }
   }
   
   if (gl.n_boards == 0 && !gl.demo_flag) {
      printf("You have to specify at least one WaveDREAM board via the -w option.\n");
      return 1;
   }
   
   if (gl.demo_flag) {
      gl.n_boards = 1;
      strlcpy(gl.board[0].name, "wd000", 32);
   }
   
   // initialize ethernet interface to WD board
   if (wd_init(&gl) != SUCCESS)
      return FAILURE;
   
   // do calibration
   if (cmd == CMD_VOLTAGE_CALIB) {
      VCALIB_PROGRESS prog;
      
      printf("Calibrating boards\n");
      prog.state = CS_FIRST_BOARD;

      do {
         double old_prog;
         int old_board;
         
         if (prog.state == CS_FIRST_BOARD || prog.state == CS_FIRST_SAMPLE) {
            printf("%s: [                                                 ]\r%s: [",
                   gl.board[prog.i_board].name, gl.board[prog.i_board].name);
            fflush(stdout);
            old_prog = 0;
            old_board = 0;
         }

         wd_calibrate_voltage(&gl, &prog);
         
         if (prog.progress >= old_prog + 0.02) {
            old_prog += 0.02;
            printf("=");
            fflush(stdout);
         }
         if (prog.state == CS_FIRST_SAMPLE)
            printf("\r\n");
         
      } while (prog.state != CS_INACTIVE);
      printf("\r\n");
      
      return 0;
   }
   
   // initialize web server
   struct mg_mgr mgr;
   struct mg_connection *con;
   
   mg_mgr_init(&mgr, &gl);
   sprintf(str, "%d", gl.http_port);
   con = mg_bind(&mgr, str, wds_handler);
   if (con == NULL) {
      printf("Cannot bind to port %d. Probably other server is already running.\n", gl.http_port);
      return 0;
   }
   mg_set_protocol_http_websocket(con);
   s_http_server_opts.document_root = ".";  // Serve current directory
   s_http_server_opts.dav_auth_file = "-";  // Allow access via WebDav
   s_http_server_opts.enable_directory_listing = "yes";
   
   printf("Starting HTTP server at port %d...\n", gl.http_port);
   
   if (gl.demo_flag)
      printf("Starting in DEMO mode.\n");
   
   time_t last = 0, now;
   for (;;) {
      // do calibration if asked for
      if (vcalib_prog.state != CS_INACTIVE) {
         wd_calibrate_voltage(&gl, &vcalib_prog);
         
         // Yield to server, no timeout
         mg_mgr_poll(&mgr, 0);
      } else if (tcalib_prog.state != CS_INACTIVE) {
         wd_calibrate_time(&gl, &tcalib_prog);
         
         // Yield to server, no timeout
         mg_mgr_poll(&mgr, 0);
      } else
         // Yield to server, 10ms timeout
         mg_mgr_poll(&mgr, 10);
      
      // read board temperatures periodically
      time(&now);
      if (now > last + 10) {
         for (int i=0 ; i<gl.n_boards ; i++)
            wd_read_board_status(&gl, i);
         last = now;
      }
   }

   // mg_mgr_free(&mgr);

   return 0;
}

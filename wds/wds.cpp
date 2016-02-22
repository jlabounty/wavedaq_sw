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
#else
#include <getopt.h>
#endif

#include "averager.h"
#include "wds.h"
#include "mongoose.h"

#define CMD_OFS_CALIB 1
#define CMD_TIME_CALIB 2

CALIB_PROGRESS ofs_prog;

/*-----------------------------------------------------------------------------------------*/

static struct mg_serve_http_opts s_http_server_opts;

// This function will be called by mongoose on every new request
static void wds_handler(struct mg_connection *nc, int event, void *p)
{
   char str[256];
   GLOBALS *gl;
   WD2_EVENT eventHeader;
   
   struct http_message *hm = (struct http_message *)p;
   
   gl = (GLOBALS *)nc->mgr->user_data;
   
   if (event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->method, "PUT") == 0) {
      if (mg_vcmp(&hm->uri, "/gl/ofs_calib1_flag") == 0)
         gl->ofs_calib1_flag = atoi(hm->body.p);
      else if (mg_vcmp(&hm->uri, "/gl/ofs_calib2_flag") == 0)
         gl->ofs_calib2_flag = atoi(hm->body.p);
      else if (mg_vcmp(&hm->uri, "/gl/remove_spikes") == 0)
         gl->remove_spikes = atoi(hm->body.p);
      else if (mg_vcmp(&hm->uri, "/gl/rotate_flag") == 0)
         gl->rotate_flag = atoi(hm->body.p);

      else if (mg_vcmp(&hm->uri, "/vcalib") == 0)
         if (!gl->demo_flag)
            ofs_prog.state = CS_FIRST_BOARD;
      
      mg_printf(nc, "HTTP/1.1 204 No Content\r\n");
   }
   
   // gloabls
   if (event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/gl") == 0) {
      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");
      
      mg_printf_http_chunk(nc, "{\n");
      mg_printf_http_chunk(nc, "   \"demo_flag\": \"%d\",\n",       gl->demo_flag);
      mg_printf_http_chunk(nc, "   \"rotate_flag\": \"%d\",\n",     gl->rotate_flag);
      mg_printf_http_chunk(nc, "   \"verbose_flag\": \"%d\",\n",    gl->verbose_flag);
      mg_printf_http_chunk(nc, "   \"adc_flag\": \"%d\",\n",        gl->adc_flag);
      mg_printf_http_chunk(nc, "   \"ofs_calib1_flag\": \"%d\",\n", gl->ofs_calib1_flag);
      mg_printf_http_chunk(nc, "   \"ofs_calib2_flag\": \"%d\",\n", gl->ofs_calib2_flag);
      mg_printf_http_chunk(nc, "   \"tcalib_flag\": \"%d\",\n",     gl->tcalib_flag);
      mg_printf_http_chunk(nc, "   \"remove_spikes\": \"%d\",\n",   gl->remove_spikes);
      mg_printf_http_chunk(nc, "   \"http_port\": \"%d\",\n",       gl->http_port);
      mg_printf_http_chunk(nc, "   \"n_boards\": \"%d\",\n",        gl->n_boards);
      mg_printf_http_chunk(nc, "   \"sampling_speed\": \"%d\",\n",  gl->sampling_speed);
      
      mg_printf_http_chunk(nc, "   \"boards\": [\n");
      
      for (int i=0 ; i<gl->n_boards ; i++) {
         mg_printf_http_chunk(nc, "      { \"name\": \"%s\" }", gl->board[i].name);
         if (i<gl->n_boards-1)
            mg_printf_http_chunk(nc, ",");
         mg_printf_http_chunk(nc, "\n");
      }
      
      mg_printf_http_chunk(nc, "   ]\n");
      
      mg_printf_http_chunk(nc, "}\n");
      
      mg_send_http_chunk(nc, "", 0); // end of response
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

      mg_send_response_line(nc, 200, "Content-Type: application/octet-stream\r\nTransfer-Encoding: chunked\r\n");

      // return progress if in calibration mode
      if (ofs_prog.state) {
         int t = 10;    // array type
         mg_send_http_chunk(nc, (const char *)&t, 4);
         
         float f = (float)ofs_prog.i_board;
         mg_send_http_chunk(nc, (const char *)&f, 4);
         
         f = (float)ofs_prog.progress;
         mg_send_http_chunk(nc, (const char *)&f, 4);
         
         mg_send_http_chunk(nc, "", 0);
         return;
      }

      mg_get_http_var(&hm->query_string, "b", str, sizeof(str));
      int b = atoi(str);
      
      // avoid invalid board index
      if (b < 0 || b >= gl->n_boards)
         b = 0;
      
      if (gl->demo_flag) {
         status = SUCCESS;
         for (int c=0 ; c<16 ; c++) {
            for (int i=0 ; i<1024 ; i++) {
               wfT[c][i] = (float)(i*1E-9);
               wfU[c][i] = (float)(sin(wfT[c][i] / 50 / 1E-9) / 4 + ((float)random()/RAND_MAX-0.5) / 30);
            }
         }
      } else {

         if (gl->adc_flag) {
            // issue single ADC software trigger
            wd_send(gl, b, 100, "adcgeteth 1\n", NULL, NULL);
         } else {
            if (gl->board[b].trigger_level == 0)
               // issue single DRS software trigger
               wd_send(gl, b, 100, "drsget\n", NULL, NULL);
            else
               // just start DRS and wait for trigger
               wd_send(gl, b, 100, "drsstart\n", NULL, NULL);
         }
         // read waveforms
         status = wd_read_waveform(gl, b, 1000, &eventHeader, wfU);
      
         for (int c=0 ; c<16 ; c++) {
            for (int i=0 ; i<1024 ; i++) {
               wfT[c][i] = (float)(i*1E-9);
            }
         }
      }

      if (gl->demo_flag)
         b = 0xFF; // signals demo data
      
      if (status == SUCCESS) {
         
         mg_get_http_var(&hm->query_string, "c", str, sizeof(str));
         int chn = atoi(str);
         
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
   gl.http_port       = 8080; // default port
   gl.sampling_speed  = 2;
   gl.ofs_calib1_flag = 1;
   gl.ofs_calib2_flag = 1;
   gl.rotate_flag     = 1;
   gl.remove_spikes   = 1;

   for (i=0 ; i<16 ; i++) {
      gl.board[i].trigger_level = 0;
      gl.board[i].gain          = 0;       // gain 1
      gl.board[i].offset        = 1.25;    // center offset
      gl.board[i].pzc           = 0;       // PZC off
      strlcpy(gl.board[i].trigger_mask, "FFFF0000", sizeof(gl.board[i].trigger_mask)); // or of all 16 channels
   }
   
   i1 = 0;
   i2 = 15;
   
   // parse command line parameters
   for (i=1 ; i<argc ; i++) {
      if (argv[i][0] == '-' && argv[i][1] == 'a')
         gl.adc_flag = 1;
      
      else if (argv[i][0] == '-' && argv[i][1] == 'c')
         cmd = CMD_OFS_CALIB;
      
      else if (argv[i][0] == '-' && argv[i][1] == 'd')
         gl.demo_flag = 1;
      
      else if (argv[i][0] == '-' && argv[i][1] == 'g') {
         for (j=0 ; j<16 ; j++)
            gl.board[j].gain = atoi(argv[i+1]);
         i++;
      }
      
      else if (argv[i][0] == '-' && argv[i][1] == 'm') {
         if (strlen(argv[i+1]) != 8) {
            printf("invalid trigger mask, please use xxxxyyyy\n");
            return 1;
         }
         for (j=0 ; j<16 ; j++)
            strlcpy(gl.board[j].trigger_mask, argv[i+1], sizeof(gl.board[j].trigger_mask));
         i++;
      }
      
      else if (argv[i][0] == '-' && argv[i][1] == 'o') {
         for (j=0 ; j<16 ; j++)
            gl.board[j].offset = (float)atoi(argv[i+1]);
         i++;
      }
      
      else if (argv[i][0] == '-' && argv[i][1] == 'd')
         gl.http_port = atoi(argv[++i]);

      else if (argv[i][0] == '-' && argv[i][1] == 'r') {
         gl.ofs_calib1_flag = 0;
         gl.ofs_calib2_flag = 0;
      }
      
      else if (argv[i][0] == '-' && argv[i][1] == 's')
         gl.sampling_speed = atoi(argv[++i]);
      
      else if (argv[i][0] == '-' && argv[i][1] == 't') {
         for (j=0 ; j<16 ; j++)
            gl.board[j].trigger_level = atoi(argv[i+1]);
         i++;
      }
      
      else if (argv[i][0] == '-' && argv[i][1] == 'v')
         gl.verbose_flag = 1;

      else if (argv[i][0] == '-' && argv[i][1] == 'w') {
         
         if (isdigit(argv[i+1][0])) {
            if (strchr(argv[i+1], '-')) {
               i1 = atoi(argv[i+1]);
               p = strchr(argv[i+1], '-') + 1;
               i2 = atoi(p);
               if (i1 >= 0 && i1 < 14 && i2>1 && i2<16) {
                  for (i=i1 ; i<=i2; i++) {
                     sprintf(gl.board[gl.n_boards++].name, "wd%03d", i);
                  }
               } else {
                  printf("invalid argument \"-w %s\"\n", argv[i+1]);
                  return 1;
               }
            }  else
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
         printf(" -a               Read ADC instead DRS\n");
         printf(" -c               Calibrate DRS chips\n");
         printf(" -d               Demo mode\n");
         printf(" -g 0/1/2         Input gain (0=1, 1=10, 2=100)\n");
         printf(" -t <level>       Trigger level in mV (0=auto)\n");
         printf(" -m <mask>        Trigger mask xxxxyyyy (xxxx=16 bit OR, yyyy=16bit AND)\n");
         printf(" -o <offset>      Set channel offset in V\n");
         printf(" -p <port>        HTTP server port\n");
         printf(" -r               Show raw (uncalibrated) data\n");
         printf(" -w <address>     Internet address of WaveDREAM board\n");
         printf(" -v               Print extra statistics\n");
         printf(" -z               Turn on pole-zero-canellation\n");
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
   if (cmd == CMD_OFS_CALIB) {
      CALIB_PROGRESS prog;
      
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

         wd_calibrate(&gl, &prog);
         
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
   mg_set_protocol_http_websocket(con);
   s_http_server_opts.document_root = ".";  // Serve current directory
   s_http_server_opts.dav_auth_file = "-";  // Allow access via WebDav
   s_http_server_opts.enable_directory_listing = "yes";
   
   printf("Starting HTTP server at port %d...\n", gl.http_port);
   
   if (gl.demo_flag)
      printf("Starting in DEMO mode.\n");
   
   for (;;) {

      // do calibration if asked for
      if (ofs_prog.state != CS_INACTIVE) {
         wd_calibrate(&gl, &ofs_prog);
         printf("%1.2lf\n", ofs_prog.progress);
      
         // Yield to server, not timeout
         mg_mgr_poll(&mgr, 0);
      } else
         // Yield to server, 10ms timeout
         mg_mgr_poll(&mgr, 10);
   }

   // mg_mgr_free(&mgr);

   return 0;
}

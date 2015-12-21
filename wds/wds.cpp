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
#include <getopt.h>
#include <ctype.h>

#include "wds.h"
#include "mongoose.h"

/*-----------------------------------------------------------------------------------------*/

// This function will be called by mongoose on every new request
static int wds_handler(struct mg_connection *conn, enum mg_event event)
{
   char str[256];
   GLOBALS *gl;
   
   gl = (GLOBALS *)conn->server_param;
   
   if (event == MG_AUTH)
      return MG_TRUE; // authorize all events
   
   // list of boards
   if (event == MG_REQUEST && !strcmp(conn->uri, "/list")) {
      mg_printf_data(conn, "{\n");
      mg_printf_data(conn, "   \"boards\": [\n");
      
      for (int i=0 ; i<gl->n_boards ; i++) {
         mg_printf_data(conn, "      { \"name\": \"%s\" }", gl->board[i].name);
         if (i<gl->n_boards-1)
            mg_printf_data(conn, ",");
         mg_printf_data(conn, "\n");
      }

      mg_printf_data(conn, "   ]\n");
      mg_printf_data(conn, "}\n");
      return MG_TRUE;
   }
   
   // binary encoded waveforms
   if (event == MG_REQUEST && strcmp(conn->uri, "/wf") == 0) {
      float wfT[16][1024], wfU[16][1024];
      int status;
      
      mg_get_var(conn, "b", str, sizeof(str));
      int b = atoi(str);
      
      // avoid invalid board index
      if (b < 0 || b >= gl->n_boards)
         b = 0;
      
      if (gl->demo_flag) {
         status = SUCCESS;
         for (int c=0 ; c<16 ; c++) {
            for (int i=0 ; i<1024 ; i++) {
               wfT[c][i] = i*1E-9;
               wfU[c][i] = (float)sin(wfT[c][i] / 50 / 1E-9) / 4 + ((float)random()/RAND_MAX-0.5) / 30;
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
         status = wd_read_waveform(gl, b, 1000, wfU);
      
         for (int c=0 ; c<16 ; c++) {
            for (int i=0 ; i<1024 ; i++) {
               wfT[c][i] = i*1E-9;
            }
         }
      }

      if (gl->demo_flag)
         b = 0xFF; // signals demo data
      
      if (status == SUCCESS) {
         
         mg_get_var(conn, "c", str, sizeof(str));
         int chn = atoi(str);
         
         int t = 1;    // array type
         int n = 1024; // number of elements
         int f = 0;    // frame number
         for (int c=0 ; c<16 ; c++) {
            if (chn & (1 << c)) {
               t = 1; // time array
               mg_send_data(conn, &t, 4);
               mg_send_data(conn, &b, 4);
               mg_send_data(conn, &f, 4);
               mg_send_data(conn, &c, 4);
               mg_send_data(conn, &n, 4);
               mg_send_data(conn, wfT[c], sizeof(float)*n);
            }
            
         }
         
         for (int c=0 ; c<16 ; c++) {
            if (chn & (1 << c)) {
               t = 2; // voltage array
               mg_send_data(conn, &t, 4);
               mg_send_data(conn, &b, 4);
               mg_send_data(conn, &f, 4);
               mg_send_data(conn, &c, 4);
               mg_send_data(conn, &n, 4);
               mg_send_data(conn, wfU[c], sizeof(float)*n);
            }
         }
         
      } else {
         // just return idle message
         int t = 0;
         mg_send_data(conn, &t, 4);
         mg_send_data(conn, &b, 4);
      }
      
      return MG_TRUE;
   }

   
   return MG_FALSE;
}

int main(int argc, char *argv[]) {
   int ch, i, i1, i2;
   GLOBALS gl;
   char str[256], *p;
   
   static struct option longopts[] = {
      { "adc",         no_argument,        NULL, 'a' },
      { "calibrate",   no_argument,        NULL, 'c' },
      { "demo",        no_argument,        NULL, 'd' },
      { "gain",        required_argument,  NULL, 'g' },
      { "mask",        required_argument,  NULL, 'm' },
      { "offset",      required_argument,  NULL, 'o' },
      { "port",        required_argument,  NULL, 'p' },
      { "tlevel",      required_argument,  NULL, 't' },
      { "raw",         required_argument,  NULL, 'r' },
      { "verbose",     no_argument,        NULL, 'v' },
      { "wd",          required_argument,  NULL, 'w' },
      { "zero",        no_argument,        NULL, 'z' },
      { 0, 0, 0, 0}
   };
   
   memset(&gl, 0, sizeof(gl));
   gl.http_port = 8080; // default port

   for (i=0 ; i<16 ; i++) {
      gl.board[i].trigger_level = 0;
      gl.board[i].gain = 0; // gain 1
      gl.board[i].pzc = 0;  // PZC off
      strcpy(gl.board[i].trigger_mask, "FFFF0000"); // or of all 16 channels
   }
   
   i1 = 0;
   i2 = 15;
   
   while ((ch = getopt_long(argc, argv, "acdg:m:o:p:t:rvw:z", longopts, NULL)) != -1) {
      switch (ch) {
         case 'a':
            gl.adc_flag = 1;
            break;
         case 'c':
            gl.calibrate_flag = 1;
            break;
         case 'd':
            gl.demo_flag = 1;
            break;
         case 'g':
            if (optarg)
               for (i=0 ; i<16 ; i++)
                  gl.board[i].gain = atoi(optarg);
            break;
         case 'm':
            if (optarg) {
               if (strlen(optarg) != 8) {
                  printf("invalid trigger mask, please use xxxxyyyy\n");
                  return 1;
               }
               for (i=0 ; i<16 ; i++)
                  strlcpy(gl.board[i].trigger_mask, optarg, sizeof(gl.board[i].trigger_mask));
            }
            break;
         case 'o':
            if (optarg)
               for (i=0 ; i<16 ; i++)
                  gl.board[i].offset = atoi(optarg);
            break;
         case 'p':
            if (optarg)
               gl.http_port = atoi(optarg);
            break;
         case 'r':
            gl.raw_flag = 1;
            break;
         case 't':
            if (optarg)
               for (i=0 ; i<16 ; i++)
                  gl.board[i].trigger_level = atoi(optarg);
            break;
         case 'v':
            gl.verbose_flag = 1;
            break;
         case 'w':
            if (optarg) {
               if (isdigit(optarg[0])) {
                  if (strchr(optarg, '-')) {
                     i1 = atoi(optarg);
                     p = strchr(optarg, '-') + 1;
                     i2 = atoi(p);
                     if (i1 >= 0 && i1 < 14 && i2>1 && i2<16) {
                        for (i=i1 ; i<=i2; i++) {
                           sprintf(gl.board[gl.n_boards++].name, "wd%03d", i);
                        }
                     } else {
                        printf("invalid argument \"-w %s\"\n", optarg);
                        return 1;
                     }
                  }  else
                     sprintf(gl.board[gl.n_boards++].name, "wd%03d", atoi(optarg));
               } else
                  strlcpy(gl.board[gl.n_boards++].name, optarg, 32);
            }
            break;
         case 'z':
            for (i=0 ; i<16 ; i++)
               gl.board[i].pzc = 1;
            break;
         default:
            printf("usage: wsd [-adv] [-w <address> [-w <address> ...]]\n");
            printf(" -a --adc         Read ADC instead DRS\n");
            printf(" -d --demo        Demo mode\n");
            printf(" -g --gain        Input gain (0=1, 1=10, 2=100)\n");
            printf(" -t --tlevel      Trigger level in mV (0=auto)\n");
            printf(" -m --mask        Trigger mask xxxxyyyy (xxxx=16 bit OR, yyyy=16bit AND)\n");
            printf(" -p --port        HTTP server port\n");
            printf(" -r --raw         Show raw (uncalibrated) data\n");
            printf(" -w --wd          Internet address of WaveDREAM board\n");
            printf(" -v --verbose     Print extra statistics\n");
            printf(" -z --zero        Turn on pole-zero-canellation\n");
            return 1;
            break;
      }
   }
   argc -= optind;
   argv += optind;
   
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
   if (gl.calibrate_flag) {
      wd_calibrate(&gl);
      return 0;
   }
   
   // initialize web server
   struct mg_server *server = mg_create_server(&gl, wds_handler);
   mg_set_option(server, "document_root", ".");      // Serve current directory
   sprintf(str, "%d", gl.http_port);
   mg_set_option(server, "listening_port", str);     // Define listening port
   
   printf("Starting HTTP server at port %d...\n", gl.http_port);
   
   if (gl.demo_flag)
      printf("Starting in DEMO mode.\n");
   
   for (;;) {
      mg_poll_server(server, 1000);   // Infinite loop, Ctrl-C to stop
   }
   
   // mg_destroy_server(&server);
   
   return 0;
}

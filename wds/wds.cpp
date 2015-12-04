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
         mg_printf_data(conn, "      { \"name\": \"%s\" }", gl->board_name[i]);
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
      
      if (gl->demo_flag) {
         status = SUCCESS;
         for (int c=0 ; c<16 ; c++) {
            for (int i=0 ; i<1024 ; i++) {
               wfT[c][i] = i*1E-9;
               wfU[c][i] = (float)sin(wfT[c][i] / 50 / 1E-9) / 4 + ((float)random()/RAND_MAX-0.5) / 30;
            }
         }
      } else {

         mg_get_var(conn, "b", str, sizeof(str));
         int board = atoi(str);
         
         // avoid invalid board index
         if (board < 0 || board >= gl->n_boards)
            board = 0;

         if (gl->adc_flag) {
            // issue single ADC software trigger
            interface_send(gl, board, 100, "adcgeteth 1\n", NULL, NULL);
         } else {
            // issue single DRS software trigger
            interface_send(gl, board, 100, "drsget\n", NULL, NULL);
         }
         // read waveforms
         status = interface_read_waveform(gl, board, 1000, wfU);
      
         for (int c=0 ; c<16 ; c++) {
            for (int i=0 ; i<1024 ; i++) {
               wfT[c][i] = i*1E-9;
            }
         }
      }

      int wd = (gl->demo_flag) ? 0xFF : atoi(gl->board_name[0]+3);
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
               mg_send_data(conn, &wd, 4);
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
               mg_send_data(conn, &wd, 4);
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
         mg_send_data(conn, &wd, 4);
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
      { "demo",        no_argument,        NULL, 'd' },
      { "gain",        required_argument,  NULL, 'g' },
      { "port",        required_argument,  NULL, 'p' },
      { "verbose",     no_argument,        NULL, 'v' },
      { "wd",          required_argument,  NULL, 'w' },
      { "zero",        no_argument,        NULL, 'z' },
      { 0, 0, 0, 0}
   };
   
   memset(&gl, 0, sizeof(gl));
   gl.board_name = (char **)malloc(sizeof(char *) * 16);
   for (i=0 ; i<16 ; i++)
      gl.board_name[i] = (char *)malloc(32);
   gl.http_port = 8080; // default port
   gl.gain = 2; // gain 100
   gl.pzc = 1;
   i1 = 0;
   i2 = 15;
   
   while ((ch = getopt_long(argc, argv, "adg:p:vw:z", longopts, NULL)) != -1) {
      switch (ch) {
         case 'a':
            gl.adc_flag = 1;
            break;
         case 'd':
            gl.demo_flag = 1;
            break;
         case 'g':
            if (optarg)
               gl.gain = atoi(optarg);
            break;
         case 'p':
            if (optarg)
               gl.http_port = atoi(optarg);
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
                           sprintf(gl.board_name[gl.n_boards++], "wd%03d", i);
                        }
                     } else {
                        printf("invalid argument \"-w %s\"\n", optarg);
                        return 1;
                     }
                  }  else
                     sprintf(gl.board_name[gl.n_boards++], "wd%03d", atoi(optarg));
               } else
                  strlcpy(gl.board_name[gl.n_boards++], optarg, 32);
            }
            break;
         case 'z':
            gl.pzc = 0;
            break;
         default:
            printf("usage: wsd [-adv] [-w <address> [-w <address> ...]]\n");
            printf(" -a --adc         Read ADC instead DRS\n");
            printf(" -g --gain        Input gain (0=1, 1=10, 2=100)\n");
            printf(" -p --port        HTTP server port\n");
            printf(" -d --demo        Demo mode\n");
            printf(" -w --wd          Internet address of WaveDREAM board\n");
            printf(" -v --verbose     Print extra statistics\n");
            printf(" -z --zero        Turn off pole-zero-canellation (on by default)\n");
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
      strlcpy(gl.board_name[0], "wd000", 32);
   }
   
   // initialize ethernet interface to WD board
   if (interface_init(&gl) != SUCCESS)
      return FAILURE;
   
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

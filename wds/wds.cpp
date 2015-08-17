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

#include "wds.h"
#include "mongoose.h"

// This function will be called by mongoose on every new request
static int wds_handler(struct mg_connection *conn, enum mg_event event)
{
   char str[256];
   GLOBALS *gl;
   
   gl = (GLOBALS *)conn->server_param;
   
   if (event == MG_AUTH)
      return MG_TRUE; // authorize all events
   
   // binary encoded waveforms
   if (event == MG_REQUEST && !strcmp(conn->uri, "/wf")) {
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
         status = interface_read(1000, wfU);
      
         for (int c=0 ; c<16 ; c++) {
            for (int i=0 ; i<1024 ; i++) {
               wfT[c][i] = i*1E-9;
            }
         }
      }

      if (status == SUCCESS) {
         
         mg_get_var(conn, "chn", str, sizeof(str));
         int chn = atoi(str);
         
         int t = 1;    // array type
         int n = 1024; // number of elements
         int f = 0;    // frame number
         for (int c=0 ; c<16 ; c++) {
            if (chn & (1 << c)) {
               t = 1; // time array
               mg_send_data(conn, &t, 4);
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
      }
      
      return MG_TRUE;
   }

   
   return MG_FALSE;
}

int main(int argc, char *argv[]) {
   int ch;
   GLOBALS gl;
   
   static struct option longopts[] = {
      { "demo",        no_argument,     NULL, 'd' },
      { "verbose",     no_argument,     NULL, 'v' },
   };
   
   memset(&gl, 0, sizeof(gl));
   
   while ((ch = getopt_long(argc, argv, "dv", longopts, NULL)) != -1) {
      switch (ch) {
         case 'd':
            gl.demo_flag = 1;
            break;
         case 'v':
            gl.verbose_flag = 1;
            break;
         default:
            printf("usage: wsd [-dv] [<address> [<address> ...]]\n");
            printf(" -d --demo        Demo mode\n");
            printf(" -v --verbose     Print extra statistics\n");
            return 1;
            break;
      }
   }
   argc -= optind;
   argv += optind;
   
   gl.board_address = (char **)malloc(sizeof(char *) * (argc+1));
   
   int i;
   for (i=0 ; i<argc && argv[i][0] ; i++)
      gl.board_address[i] = argv[i];
   gl.board_address[i] = NULL;
   
   // initialize ethernet interface to WD board
   if (interface_init(&gl) != SUCCESS)
      return FAILURE;
   
   // initialize web server
   struct mg_server *server = mg_create_server(&gl, wds_handler);
   mg_set_option(server, "document_root", ".");      // Serve current directory
   mg_set_option(server, "listening_port", "8080");  // Open port 8080
   
   printf("Starting HTTP server at port 8080...\n");
   
   if (gl.demo_flag)
      printf("Starting in DEMO mode.\n");
   
   for (;;) {
      mg_poll_server(server, 1000);   // Infinite loop, Ctrl-C to stop
   }
   
   // mg_destroy_server(&server);
   
   return 0;
}
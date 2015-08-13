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

#include "wds.h"
#include "mongoose.h"

// This function will be called by mongoose on every new request
static int wds_handler(struct mg_connection *conn, enum mg_event event)
{
   char str[256];
   
   if (event == MG_AUTH)
      return MG_TRUE; // authorize all events
   
   // JSON encoded waveforms
   if (event == MG_REQUEST && !strcmp(conn->uri, "/wfj")) {
      float wfT[16][1024], wfU[16][1024];
      
      for (int c=0 ; c<16 ; c++) {
         for (int i=0 ; i<1024 ; i++) {
            wfT[c][i] = i*1E-9;
            wfU[c][i] = (float)sin(wfT[c][i] / 50 / 1E-9) / 4 + ((float)random()/RAND_MAX-0.5) / 30;
         }
      }
      
      mg_get_var(conn, "chn", str, sizeof(str));
      int chn = atoi(str);
      
      int n = 1024;
      mg_printf_data(conn, "{\"T\":[");
      for (int c=0 ; c<16 ; c++) {
         mg_printf_data(conn, "[");
         
         if (chn & (1 << c)) {
            for (int i=0 ; i<n ; i++) {
               mg_printf_data(conn, "%1.4lg", wfT[c][i]);
               if (i < n-1)
                  mg_printf_data(conn, ",\n");
            }
         }
         
         mg_printf_data(conn, "]");
         if (c < 16-1)
            mg_printf_data(conn, ",\n");
      }
      mg_printf_data(conn, "],\n");

      mg_printf_data(conn, "\"U\":[");
      for (int c=0 ; c<16 ; c++) {
         mg_printf_data(conn, "[");
         
         if (chn & (1 << c)) {
            for (int i=0 ; i<n ; i++) {
               mg_printf_data(conn, "%1.4lg", wfU[c][i]);
               if (i < n-1)
                  mg_printf_data(conn, ",\n");
            }
         }
         
         mg_printf_data(conn, "]");
         if (c < 16-1)
            mg_printf_data(conn, ",\n");
      }
      mg_printf_data(conn, "]}\n");

      return MG_TRUE;
   }

   // binary encoded waveforms
   if (event == MG_REQUEST && !strcmp(conn->uri, "/wfb")) {
      float wfT[16][1024], wfU[16][1024];
      int status;
      
      status = interface_read(1000, wfU);
      
      for (int c=0 ; c<16 ; c++) {
         for (int i=0 ; i<1024 ; i++) {
            wfT[c][i] = i*1E-9;
            // wfU[c][i] = (float)sin(wfT[c][i] / 50 / 1E-9) / 4 + ((float)random()/RAND_MAX-0.5) / 30;
         }
      }

      if (status == SUCCESS) {
         
         mg_get_var(conn, "chn", str, sizeof(str));
         int chn = atoi(str);
         
         int n = 1024;
         int t = 1;
         for (int c=0 ; c<16 ; c++) {
            if (chn & (1 << c)) {
               t = 1; // time array
               mg_send_data(conn, &t, 4);
               mg_send_data(conn, &c, 4);
               mg_send_data(conn, &n, 4);
               mg_send_data(conn, wfT[c], sizeof(float)*n);
            }
            
         }
         
         for (int c=0 ; c<16 ; c++) {
            if (chn & (1 << c)) {
               t = 2; // voltage array
               mg_send_data(conn, &t, 4);
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

int main(void) {
   // initialize ethernet interface to WD board
   if (interface_init() != SUCCESS)
      return FAILURE;
   
   // initialize web server
   struct mg_server *server = mg_create_server(NULL, wds_handler);
   mg_set_option(server, "document_root", ".");      // Serve current directory
   mg_set_option(server, "listening_port", "8080");  // Open port 8080
   
   printf("Starting HTTP server at port 8080...\n");
   
   for (;;) {
      mg_poll_server(server, 1000);   // Infinite loop, Ctrl-C to stop
   }
   
   // mg_destroy_server(&server);
   
   return 0;
}
//
//  wdbtest.cpp
//  Test program for WDBLib.cpp
//
//  Stefan Ritt 31 Jan 2017
//


#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <thread>

#include "WDBLib.h"
#include "mongoose.h"

/*-- Globals -------------------------------------------------------*/

std::vector<std::string> wdbName = { "wd094" };

typedef struct {
   bool demoMode;
   int  serverPort;
   bool verbose;
   std::vector<WDB*> wdb;
   WP*  wp;
} GLOBALS;

/*------------------------------------------------------------------*/

static struct mg_serve_http_opts s_http_server_opts;

// This function will be called by mongoose on every new request
static void wds_handler(struct mg_connection *nc, int event, void *p)
{
   struct http_message *hm = (struct http_message *)p;
   char str[256];
   
   GLOBALS *gl = (GLOBALS *)nc->mgr->user_data;

   if (event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->method, "PUT") == 0) {
   }
   
   // gloabls
   if (event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/gl") == 0) {
      if (gl->verbose)
         std::cout<< "Sending /gl to browser" << std::endl;
      
      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");
      
      mg_printf_http_chunk(nc, "{\n");
      mg_printf_http_chunk(nc, "   \"demo_flag\": %s,\n",          gl->demoMode ? "true" : "false");
      
      mg_printf_http_chunk(nc, "   \"board\": [\n");
      
      for (auto &b: gl->wdb) {
         mg_printf_http_chunk(nc, "      {\n");
         mg_printf_http_chunk(nc, "         \"name\": \"%s\"\n",         b->getName().c_str());
         mg_printf_http_chunk(nc, "      }");
         if (b != gl->wdb.back())
            mg_printf_http_chunk(nc, ",");
         mg_printf_http_chunk(nc, "\n");
      }
      
      mg_printf_http_chunk(nc, "   ]\n");
      mg_printf_http_chunk(nc, "}\n");
      mg_send_http_chunk(nc, "", 0); // end of response
      return;
   }
   
   // boards
   if (event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/wdb") == 0) {
      if (gl->verbose)
         std::cout<< "Sending /wdb to browser" << std::endl;
      mg_get_http_var(&hm->query_string, "b", str, sizeof(str));
      int b1, b2;
      if (str[0]) {
         int b = atoi(str);
         if (b < 0) {
            b1 = 0;
            b2 = gl->wdb.size();
         } else {
            b1 = b2 = b;
         }
      } else {
         b1 = 0;
         b2 = 1;
      }
      
      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");
      mg_printf_http_chunk(nc, "{\n");
      mg_printf_http_chunk(nc, "  \"board\": [\n");
      
      for (int b = b1 ; b<b2 ; b++) {
         mg_printf_http_chunk(nc, "    {\n");
         mg_printf_http_chunk(nc, "      \"temperature\": %1.1lf,\n",            gl->wdb[b]->GetTemperature(false));
         mg_printf_http_chunk(nc, "      \"sysBusy\": %s,\n",                    gl->wdb[b]->IsSysBusy() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"wdbBusy\": %s,\n",                    gl->wdb[b]->IsSysBusy() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"hvBoardPlugged\": %s,\n",             gl->wdb[b]->IsHvBoardPlugged() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"hvBackplanePlugged\": %s,\n",         gl->wdb[b]->IsBackplanePlugged() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"extPllLck\": %s,\n",                  gl->wdb[b]->IsExtPllLck() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"intPllLck\": %s,\n",                  gl->wdb[b]->IsIntPllLck() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"drsSampleFreq\": %d,\n",              gl->wdb[b]->GetDrsSampleFreq());
         mg_printf_http_chunk(nc, "      \"adcSampleFreq\": %d,\n",              gl->wdb[b]->GetAdcSampleFreq());
         mg_printf_http_chunk(nc, "      \"compChannelStatus\": %d,\n",          gl->wdb[b]->GetCompChannelStatus());
         mg_printf_http_chunk(nc, "      \"lastEventNumber\": %d,\n",            gl->wdb[b]->GetLastEventNumber());
         mg_printf_http_chunk(nc, "      \"triggerBusParityErrorCount\": %d,\n", gl->wdb[b]->GetLastEventNumber());
         mg_printf_http_chunk(nc, "      \"triggerBusType\": %d,\n",             gl->wdb[b]->GetTriggerBusType());
         mg_printf_http_chunk(nc, "      \"triggerBusNumber\": %d,\n",           gl->wdb[b]->GetTriggerBusNumber());
         mg_printf_http_chunk(nc, "      \"crateId\": %d,\n",                    gl->wdb[b]->GetCrateId());
         mg_printf_http_chunk(nc, "      \"slotId\": %d,\n",                     gl->wdb[b]->GetSlotId());
         mg_printf_http_chunk(nc, "      \"readoutSrcSel\": %d,\n",              gl->wdb[b]->GetReadoutSrcSel());
         mg_printf_http_chunk(nc, "      \"daqNormal\": %s,\n",                  gl->wdb[b]->IsDAQNormal() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"daqSingle\": %s,\n",                  gl->wdb[b]->IsDAQSingle() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"drs0TimingRefSel\": %d,\n",           gl->wdb[b]->GetDRS0TimingRefSel());
         mg_printf_http_chunk(nc, "      \"drs1TimingRefSel\": %d,\n",           gl->wdb[b]->GetDRS1TimingRefSel());
         mg_printf_http_chunk(nc, "      \"timingCalibBufferEnable\": %s,\n",    gl->wdb[b]->IsTimingCalibBufferEnable() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"timingCalibSignalEnable\": %s,\n",    gl->wdb[b]->IsTimingCalibSignalEnable() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"daqClkSrcSel\": %d,\n",               gl->wdb[b]->GetDAQClkSrcSel());
         mg_printf_http_chunk(nc, "      \"extClkInSel\": %d,\n",                gl->wdb[b]->GetExtClkInSel());
         mg_printf_http_chunk(nc, "      \"extClkFreq\": %d,\n",                 gl->wdb[b]->GetExtClkFreq());
         mg_printf_http_chunk(nc, "      \"localClkFreq\": %d,\n",               gl->wdb[b]->GetLocalClkFreq());
         mg_printf_http_chunk(nc, "      \"drs0ChnTxEnable\": %d,\n",            gl->wdb[b]->GetDRS0ChnTxEnable());
         mg_printf_http_chunk(nc, "      \"drs1ChnTxEnable\": %d,\n",            gl->wdb[b]->GetDRS1ChnTxEnable());
         mg_printf_http_chunk(nc, "      \"dacPZCLevel\": %d,\n",                gl->wdb[b]->GetDacPZCLevel());

         mg_printf_http_chunk(nc, "      \"dacTlevel\": [\n");
         for (int i=0 ; i<14 ; i++)
            mg_printf_http_chunk(nc, "        %d,\n",                            gl->wdb[b]->GetDacTlevel(i));
         mg_printf_http_chunk(nc, "        %d ],\n",                             gl->wdb[b]->GetDacTlevel(15));

         mg_printf_http_chunk(nc, "      \"fePZC\": [\n");
         for (int i=0 ; i<14 ; i++)
            mg_printf_http_chunk(nc, "        %s,\n",                            gl->wdb[b]->IsFEPZC(i) ? "true" : "false");
         mg_printf_http_chunk(nc, "        %s ],\n",                             gl->wdb[b]->IsFEPZC(15) ? "true" : "false");

         mg_printf_http_chunk(nc, "      \"feGain\": [\n");
         for (int i=0 ; i<14 ; i++)
            mg_printf_http_chunk(nc, "        %1g,\n",                           gl->wdb[b]->GetFEGain(i));
         mg_printf_http_chunk(nc, "        %1g ],\n",                            gl->wdb[b]->GetFEGain(15));

         mg_printf_http_chunk(nc, "      \"feMux\": [\n");
         for (int i=0 ; i<14 ; i++)
            mg_printf_http_chunk(nc, "        %1g,\n",                           gl->wdb[b]->GetFEMux(i));
         mg_printf_http_chunk(nc, "        %1g ],\n",                            gl->wdb[b]->GetFEMux(15));

         mg_printf_http_chunk(nc, "      \"triggerShaperEnable\": %s,\n",        gl->wdb[b]->IsTriggerShaperEnable() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"triggerPulseLength\": %d,\n",         gl->wdb[b]->GetTriggerPulseLength());
         mg_printf_http_chunk(nc, "      \"triggerEnable\": %s,\n",              gl->wdb[b]->IsTriggerEnable() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"triggerFallingEdge\": %s,\n",         gl->wdb[b]->IsTriggerFallingEdge() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"triggerExternalOr\": %s,\n",          gl->wdb[b]->IsTriggerExternalOr() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"triggerExternalAnd\": %s,\n",         gl->wdb[b]->IsTriggerExternalAnd() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"triggerDelayEnable\": %s,\n",         gl->wdb[b]->IsTriggerDelayEnable() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"triggerDelay\": %d,\n",               gl->wdb[b]->GetTriggerDelay());
         mg_printf_http_chunk(nc, "      \"triggerComparatorMask\": %d,\n",      gl->wdb[b]->GetTriggerComparatorMask());
         mg_printf_http_chunk(nc, "      \"triggerCfgOr\": %d,\n",               gl->wdb[b]->GetTriggerCfgOr());
         mg_printf_http_chunk(nc, "      \"triggerCfgAnd\": %d,\n",              gl->wdb[b]->GetTriggerCfgAnd());

         mg_printf_http_chunk(nc, "    }\n");
      }
      
      mg_printf_http_chunk(nc, "  ]\n");
      mg_printf_http_chunk(nc, "}\n");
      mg_send_http_chunk(nc, "", 0);
   }
   
   // temperature & PLL lock status
   if (event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/status") == 0) {
      if (gl->verbose)
         std::cout<< "Sending /status to browser" << std::endl;
      mg_get_http_var(&hm->query_string, "b", str, sizeof(str));
      int b = atoi(str);
      
      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");
      mg_printf_http_chunk(nc, "{\n");
      mg_printf_http_chunk(nc, "   \"temp\": %1.1lf,\n",   gl->wdb[b]->GetTemperature(false));
      mg_printf_http_chunk(nc, "   \"pll_locked\": %s\n",  gl->wdb[b]->IsExtPllLck() && gl->wdb[b]->IsIntPllLck() ? "true" : "false");
      mg_printf_http_chunk(nc, "}\n");
      mg_send_http_chunk(nc, "", 0);
      return;
   }

   // scalers
   if (event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/scalers") == 0) {
      if (gl->verbose)
         std::cout<< "Sending /scalers to browser" << std::endl;
      mg_get_http_var(&hm->query_string, "b", str, sizeof(str));
      int b = atoi(str);
      
      std::vector<unsigned long> scaler;
      gl->wdb[b]->GetScalers(scaler);
      
      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");
      mg_printf_http_chunk(nc, "{\n");
      mg_printf_http_chunk(nc, "         \"scaler\": [\n");
      for (auto &s: scaler)
         if (s != scaler.back())
            mg_printf_http_chunk(nc, "            %d,\n", s);
         else
            mg_printf_http_chunk(nc, "            %d]\n", s);
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

   // file serving
   if (event == MG_EV_HTTP_REQUEST) {
      mg_serve_http(nc, hm, s_http_server_opts);
   }

}

/*------------------------------------------------------------------*/

void showUsage(std::string name)
{
   if (name.find("/") != std::string::npos)
      name = name.substr(name.rfind("/")+1); // strip path
      
   std::cerr << "usage: " << name << " [options] [-w <address> [-w <address> ...]]" << std::endl;
   std::cerr << "valud options:" << std::endl;
   std::cerr << "  -h              Show this help" << std::endl;
   std::cerr << "  -d              Demo mode" << std::endl;
   std::cerr << "  -p              HTTP server port" << std::endl;
   std::cerr << "  -w <address>    Internet address(es) of WaveDREAM board(s)" << std::endl;
   std::cerr << "  -v              Print extra information (verbose)" << std::endl;
}

int main(int argc, const char * argv[])
{
   GLOBALS gl;
   
   // default values
   gl.serverPort = 8080;
   
   // parse command line parameters
   if (argc < 2) {
      showUsage(argv[0]);
      return 1;
   }
   
   for (int i=1 ; i<argc ; i++) {
      std::string arg = argv[i];
      if (arg == "-h" || arg == "-help" || arg == "--help") {
         showUsage(argv[0]);
         return 0;
      } else if (arg == "-d")
         gl.demoMode = true;
      
      else if (arg == "-p")
         gl.serverPort = std::stoi(argv[++i]);
      
      else if (arg == "-v")
         gl.verbose = true;
      
      else if (arg == "-w") {
         
         if (i+1 == argc) {
            showUsage(argv[0]);
            return 0;
         }
         std::string b = argv[i+1];
         if (isdigit(b.c_str()[0]) && b.find(".") == std::string::npos) {
            if (b.find("-") != std::string::npos) {
               int i1 = std::stoi(b);
               int i2 = std::stoi(b.substr(b.find("-")+1));
               if (i1 >= 0 && i1 < 1000 && i2>0 && i2<1000) {
                  for (int j=i1 ; j<=i2; j++) {
                     std::ostringstream name;
                     name << "wd" << std::setfill('0') << std::setw(3) << j;
                     gl.wdb.push_back(new WDB(name.str()));
                  }
               } else {
                  std::cerr << "invalid argument \"-w " << b << "\"" << std::endl;
                  return 1;
               }
            } else {
               if (argc > i+1 && isdigit(argv[i+1][0])) {
                  while (argc > i+1 && isdigit(argv[i+1][0])) {
                     std::ostringstream name;
                     name << "wd" << std::setfill('0') << std::setw(3) << atoi(argv[i+1]);
                     gl.wdb.push_back(new WDB(name.str()));
                     i++;
                  }
                  continue;
               }
            }
         } else
            gl.wdb.push_back(new WDB(b));
         i++;
      } else {
         showUsage(argv[0]);
         return 1;
      }
   }
   
   if (gl.demoMode) {
      gl.wdb.clear();
      gl.wdb.push_back(new WDB("demo"));
   }

   if (gl.wdb.size() == 0) {
      std::cerr << "You have to specify at least one WaveDREAM board via the \"-w\" option." << std::endl;
      return 1;
   }
   
   // instantiate waveform processor
   gl.wp = new WP(gl.verbose, gl.demoMode);
   
   // connect to all WDB and retrieve registers
   for (auto &b: gl.wdb) {
      std::cout << "Connect to " << b->getName() << " ... " << std::flush;
      try {
         if (!gl.demoMode) {
            b->SetVerbose(gl.verbose);
            b->Connect(gl.wp->GetServerPort());
            b->ReceiveStatusRegisters();
            b->ReceiveControlRegisters();
            if (gl.verbose)
               b->PrintVersion();
         }
      } catch (std::runtime_error &e) {
         std::cout << std::endl;
         std::cout << e.what() << std::endl;
         std::cout << "Aborting." << std::endl;
         return 1;
      }
      std::cout << " OK" << std::endl;
   }

   // set active WDB
   for (auto &b: gl.wdb)
      gl.wp->AddActiveWDB(b->GetSerialNumber());
   
   /*
   try {
      std::vector<unsigned long> s;
      do {
         gl.wdb[0]->GetScalers(s);
         std::cout << "S: " << s[0] << std::endl;
         
         std::cout << "T: " << gl.wdb[0]->GetTemperature() << std::endl;
         
         sleep(1000);
      } while (1);
      
   } catch  (std::runtime_error &e) {
      std::cout << std::endl;
      std::cout << e.what() << std::endl;
      std::cout << "Aborting." << std::endl;
      return 1;
   }
   */
   
   // initialize web server
   struct mg_mgr mgr;
   struct mg_connection *con;
   
   mg_mgr_init(&mgr, &gl);
   con = mg_bind(&mgr, std::to_string(gl.serverPort).c_str(), wds_handler);
   if (con == NULL) {
      std::cerr << "Cannot bind to port " << gl.serverPort << ". Probably other server is already running." << std::endl;
      return 1;
   }
   mg_set_protocol_http_websocket(con);
   s_http_server_opts.document_root = ".";  // Serve current directory
   s_http_server_opts.dav_auth_file = "-";  // Allow access via WebDav
   s_http_server_opts.enable_directory_listing = "yes";
   
   std::cout << "Starting HTTP server at port " << gl.serverPort << std::endl;
   
   if (gl.demoMode)
      std::cout << "Starting in DEMO mode." << std::endl;
   
   time_t last = 0, now;
   for (;;) {
      /*
      // do calibration if asked for
      if (vcalib_prog.state != WD_CS_INACTIVE) {
         wd_calibrate_voltage(&gl, &vcalib_prog);
         
         // Yield to server, no timeout
         mg_mgr_poll(&mgr, 0);
      } else if (tcalib_prog.state != WD_CS_INACTIVE) {
         wd_calibrate_time(&gl, &tcalib_prog);
         
         // Yield to server, no timeout
         mg_mgr_poll(&mgr, 0);
      } else
         // Yield to server, 10ms timeout
         mg_mgr_poll(&mgr, 10);
      */

      // Yield to server, 10ms timeout
      mg_mgr_poll(&mgr, 10);

      // read board temperatures periodically
      time(&now);
      if (now > last + 10) {
         for (auto &b: gl.wdb)
            b->GetTemperature(true);
         last = now;
      }
   }
   
   // mg_mgr_free(&mgr);
   
   return 0;
}

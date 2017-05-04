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
#include <random>

#include "WDBLib.h"
#include "mongoose.h"

/*-- Globals -------------------------------------------------------*/

std::vector<std::string> wdbName = { "wd094" };

const int cTriggerModeNormal    = 1;
const int cTriggerModeAuto      = 2;

typedef struct {
   bool demoMode;
   int  serverPort;
   bool verbose;
   std::vector<WDB*> wdb;
   WP*  wp;
   int  triggerMode;
} GLOBALS;

/*------------------------------------------------------------------*/

std::vector<std::string> split(const std::string&input , char separator)
{
   std::vector<std::string> output;
   
   std::istringstream stream(input);
   std::string s;
   while (getline(stream, s, separator)) {
      // trim leading spaces
      size_t startpos = s.find_first_not_of(" \t\r\n");
      if (startpos != std::string::npos)
         s = s.substr(startpos);
      // trim trailing spaces
      size_t endpos = s.find_last_not_of(" \t\r\n");
      if (endpos != std::string::npos)
         s = s.substr(0, endpos+1);
      output.push_back(s);
   }
   
   return output;
}

/*------------------------------------------------------------------*/

static struct mg_serve_http_opts s_http_server_opts;

// This function will be called by mongoose on every new request
static void wds_handler(struct mg_connection *nc, int event, void *p)
{
   struct http_message *hm = (struct http_message *)p;
   char str[256];
   static std::default_random_engine randomGenerator;
   
   GLOBALS *gl = (GLOBALS *)nc->mgr->user_data;

   if (event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->method, "PUT") == 0) {
      std::string uri, value, item;
      std::vector<std::string> args;
      int iBoard = -1, iChannel = -1;
      
      // get parameters from URI
      if (hm->uri.p) {
         uri = split(std::string(hm->uri.p), ' ')[0];
         args = split(uri, '/');
         if (args.size() > 3) {
            iBoard = std::stoi(args[2]);
            item = args[3];
         }
         if (args.size() > 4)
            iChannel = std::stoi(args[4]);
      }
      if (hm->body.p)
         value = std::string(hm->body.p, hm->body.len);
      
      if (item == "rotateWaveform") {
         gl->wp->SetRotateWaveform(value == "1");
      }

      else if (item == "timeCalib1") {
         gl->wp->SetTimeCalib1(value == "1");
      }

      else if (item == "timeCalib2") {
         gl->wp->SetTimeCalib2(value == "1");
      }

      else if (item == "timeCalib3") {
         gl->wp->SetTimeCalib3(value == "1");
      }

      else if (item == "daqClkSrcSel") {
         assert(iBoard != -1);
         gl->wdb[iBoard]->SetDaqClkSrcSel(std::stoi(value));
      }

      else if (item == "dacTriggerLevel") {
         assert(iBoard != -1);
         gl->wdb[iBoard]->SetDacTriggerLevelV(iChannel, std::stof(value));
      }

      else if (item == "triggerDelay") {
         assert(iBoard != -1);
         gl->wdb[iBoard]->SetTriggerDelayNs(std::stoi(value));
      }

      else if (item == "triggerFallingEdge") {
         assert(iBoard != -1);
         gl->wdb[iBoard]->SetTriggerFallingEdge(std::stoi(value));
      }

      else if (item == "triggerMode") {
         gl->triggerMode = std::stoi(value);
      }

      else if (item == "triggerSource") {
         assert(iBoard != -1);
         if (value == "0") {
            // internal trigger
            gl->wdb[iBoard]->SetTriggerEnable(true);
            gl->wdb[iBoard]->SetTriggerCfgOr(0xFFFF);
            gl->wdb[iBoard]->SetTriggerExternalOr(false);
            gl->wdb[iBoard]->SetTriggerExternalAnd(false);
         } else {
            // external trigger
            gl->wdb[iBoard]->SetTriggerEnable(true);
            gl->wdb[iBoard]->SetTriggerCfgOr(0);
            gl->wdb[iBoard]->SetTriggerExternalOr(true);
            gl->wdb[iBoard]->SetTriggerExternalAnd(false);
         }
      }

      else if (item == "gain") {
         assert(iBoard != -1);
         gl->wdb[iBoard]->SetFeGain(iChannel, std::stof(value));
      }

      else if (item == "pzc") {
         assert(iBoard != -1);
         gl->wdb[iBoard]->SetFePzc(iChannel, std::stoi(value));
      }

      else if (item == "pzcLevel") {
         assert(iBoard != -1);
         gl->wdb[iBoard]->SetDacPZCLevelN(std::stoi(value));
      }

      else if (item == "range") {
         assert(iBoard != -1);
         std::cout << value << std::endl;
      }

      else if (item == "readoutSrc") {
         assert(iBoard != -1);
         gl->wdb[iBoard]->SetReadoutSrcSel(std::stoi(value));
      }

      else if (item == "calibBufferEnable") {
         assert(iBoard != -1);
         gl->wdb[iBoard]->SetCalibBufferEnable(std::stoi(value));
      }

      else if (item == "timingCalibSignalEnable") {
         assert(iBoard != -1);
         gl->wdb[iBoard]->SetTimingCalibSignalEnable(std::stoi(value));
      }

      else if (item == "feMux") {
         assert(iBoard != -1);
         gl->wdb[iBoard]->SetFeMux(iChannel, std::stoi(value) ? 0x03 : 0x02);
      }

      else if (item == "drsSampleFreq") {
         assert(iBoard != -1);
         gl->wdb[iBoard]->SetDrsSampleFreq(std::stoi(value));
      }

      else if (item == "dacCalDc") {
         assert(iBoard != -1);
         gl->wdb[iBoard]->SetDacCalDcV(std::stof(value));
      }

      mg_printf(nc, "HTTP/1.1 204 No Content\r\n");
   }
   
   // gloabls
   if (event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/gl") == 0) {
      if (gl->verbose)
         std::cout<< "Sending /gl to browser" << std::endl;
      
      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");
      
      mg_printf_http_chunk(nc, "{\n");
      mg_printf_http_chunk(nc, "   \"gl\": {\n");
      mg_printf_http_chunk(nc, "      \"demoMode\": %s,\n",                      gl->demoMode ? "true" : "false");
      mg_printf_http_chunk(nc, "      \"triggerMode\": %d,\n",                   gl->triggerMode);
      mg_printf_http_chunk(nc, "      \"nWdb\": %d\n",                           gl->wdb.size());
      mg_printf_http_chunk(nc, "   },\n");
      mg_printf_http_chunk(nc, "   \"wp\": {\n");
      mg_printf_http_chunk(nc, "      \"rotateWaveform\": %s,\n",                gl->wp->IsRotateWaveform() ? "true" : "false");
      mg_printf_http_chunk(nc, "      \"ofsCalib1\": %s,\n",                     gl->wp->IsOfsCalib1() ? "true" : "false");
      mg_printf_http_chunk(nc, "      \"ofsCalib2\": %s,\n",                     gl->wp->IsOfsCalib2() ? "true" : "false");
      mg_printf_http_chunk(nc, "      \"gainCalib\": %s,\n",                     gl->wp->IsGainCalib() ? "true" : "false");
      mg_printf_http_chunk(nc, "      \"rangeCalib\": %s,\n",                    gl->wp->IsRangeCalib() ? "true" : "false");
      mg_printf_http_chunk(nc, "      \"timeCalib1\": %s,\n",                    gl->wp->IsTimeCalib1() ? "true" : "false");
      mg_printf_http_chunk(nc, "      \"timeCalib2\": %s,\n",                    gl->wp->IsTimeCalib2() ? "true" : "false");
      mg_printf_http_chunk(nc, "      \"timeCalib3\": %s,\n",                    gl->wp->IsTimeCalib3() ? "true" : "false");
      mg_printf_http_chunk(nc, "      \"removeSpikes\": %s\n",                   gl->wp->IsRemoveSpikes() ? "true" : "false");
      mg_printf_http_chunk(nc, "   }\n");
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
      mg_printf_http_chunk(nc, "  \"wdb\": [\n");
      
      for (int b = b1 ; b<b2 ; b++) {
         auto w = gl->wdb[b];
         mg_printf_http_chunk(nc, "    {\n");
         mg_printf_http_chunk(nc, "      \"name\": \"%s\",\n",                   w->GetName().c_str());
         mg_printf_http_chunk(nc, "      \"temperature\": %1.1lf,\n",            w->GetTemperature(false));
         mg_printf_http_chunk(nc, "      \"sysBusy\": %s,\n",                    w->IsSysBusy() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"wdbBusy\": %s,\n",                    w->IsSysBusy() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"hvBoardPlugged\": %s,\n",             w->IsHvBoardPlugged() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"hvBackplanePlugged\": %s,\n",         w->IsBackplanePlugged() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"extPllLck\": %s,\n",                  w->IsExtPllLck() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"intPllLck\": %s,\n",                  w->IsIntPllLck() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"drsSampleFreq\": %d,\n",              w->GetDrsSampleFreq());
         mg_printf_http_chunk(nc, "      \"adcSampleFreq\": %d,\n",              w->GetAdcSampleFreq());
         mg_printf_http_chunk(nc, "      \"compChannelStatus\": %d,\n",          w->GetCompChannelStatus());
         mg_printf_http_chunk(nc, "      \"lastEventNumber\": %d,\n",            w->GetLastEventNumber());
         mg_printf_http_chunk(nc, "      \"triggerBusParityErrorCount\": %d,\n", w->GetLastEventNumber());
         mg_printf_http_chunk(nc, "      \"triggerBusType\": %d,\n",             w->GetTriggerBusType());
         mg_printf_http_chunk(nc, "      \"triggerBusNumber\": %d,\n",           w->GetTriggerBusNumber());
         mg_printf_http_chunk(nc, "      \"crateId\": %d,\n",                    w->GetCrateId());
         mg_printf_http_chunk(nc, "      \"slotId\": %d,\n",                     w->GetSlotId());
         mg_printf_http_chunk(nc, "      \"readoutSrcSel\": %d,\n",              w->GetReadoutSrcSel());
         mg_printf_http_chunk(nc, "      \"daqNormal\": %s,\n",                  w->IsDAQNormal() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"daqSingle\": %s,\n",                  w->IsDaqSingle() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"drs0TimingRefSel\": %d,\n",           w->GetDrs0TimingRefSel());
         mg_printf_http_chunk(nc, "      \"drs1TimingRefSel\": %d,\n",           w->GetDrs1TimingRefSel());
         mg_printf_http_chunk(nc, "      \"calibBufferEnable\": %s,\n",          w->IsCalibBufferEnable() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"timingCalibSignalEnable\": %s,\n",    w->IsTimingCalibSignalEnable() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"daqClkSrcSel\": %d,\n",               w->GetDaqClkSrcSel());
         mg_printf_http_chunk(nc, "      \"extClkInSel\": %d,\n",                w->GetExtClkInSel());
         mg_printf_http_chunk(nc, "      \"extClkFreq\": %d,\n",                 w->GetExtClkFreq());
         mg_printf_http_chunk(nc, "      \"localClkFreq\": %d,\n",               w->GetLocalClkFreq());
         mg_printf_http_chunk(nc, "      \"drs0ChnTxEnable\": %d,\n",            w->GetDrs0ChnTxEnable());
         mg_printf_http_chunk(nc, "      \"drs1ChnTxEnable\": %d,\n",            w->GetDrs1ChnTxEnable());
         
         mg_printf_http_chunk(nc, "      \"dacOfs\": %f,\n",                     w->GetDacOfsV());
         mg_printf_http_chunk(nc, "      \"dacCalDc\": %f,\n",                   w->GetDacCalDcV());
         mg_printf_http_chunk(nc, "      \"dacPZCLevel\": %f,\n",                w->GetDacPZCLevelV());

         mg_printf_http_chunk(nc, "      \"dacTriggerLevel\": [\n");
         for (int i=0 ; i<15 ; i++)
            mg_printf_http_chunk(nc, "        %f,\n",                            w->GetDacTriggerLevelV(i));
         mg_printf_http_chunk(nc, "        %f ],\n",                             w->GetDacTriggerLevelV(15));

         mg_printf_http_chunk(nc, "      \"fePZC\": [\n");
         for (int i=0 ; i<15 ; i++)
            mg_printf_http_chunk(nc, "        %s,\n",                            w->IsFePzc(i) ? "true" : "false");
         mg_printf_http_chunk(nc, "        %s ],\n",                             w->IsFePzc(15) ? "true" : "false");

         mg_printf_http_chunk(nc, "      \"feGain\": [\n");
         for (int i=0 ; i<15 ; i++)
            mg_printf_http_chunk(nc, "        %1g,\n",                           w->GetFeGain(i));
         mg_printf_http_chunk(nc, "        %1g ],\n",                            w->GetFeGain(15));

         mg_printf_http_chunk(nc, "      \"feMux\": [\n");
         for (int i=0 ; i<15 ; i++)
            mg_printf_http_chunk(nc, "        %d,\n",                            w->GetFeMux(i));
         mg_printf_http_chunk(nc, "        %d ],\n",                             w->GetFeMux(15));

         mg_printf_http_chunk(nc, "      \"triggerShaperEnable\": %s,\n",        w->IsTriggerShaperEnable() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"triggerPulseLength\": %d,\n",         w->GetTriggerPulseLength());
         mg_printf_http_chunk(nc, "      \"triggerEnable\": %s,\n",              w->IsTriggerEnable() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"triggerFallingEdge\": %s,\n",         w->IsTriggerFallingEdge() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"triggerExternalOr\": %s,\n",          w->IsTriggerExternalOr() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"triggerExternalAnd\": %s,\n",         w->IsTriggerExternalAnd() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"triggerDelayEnable\": %s,\n",         w->IsTriggerDelayEnable() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"triggerDelay\": %d,\n",               w->GetTriggerDelayNs());
         mg_printf_http_chunk(nc, "      \"triggerComparatorMask\": %d,\n",      w->GetTriggerComparatorMask());
         mg_printf_http_chunk(nc, "      \"triggerCfgOr\": %d,\n",               w->GetTriggerCfgOr());
         mg_printf_http_chunk(nc, "      \"triggerCfgAnd\": %d\n",               w->GetTriggerCfgAnd());

         if (b == b2-1)
            mg_printf_http_chunk(nc, "    }\n");
         else
            mg_printf_http_chunk(nc, "    },\n");
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
      mg_printf_http_chunk(nc, "   \"temperature\": %1.1lf,\n",   gl->wdb[b]->GetTemperature(false));
      mg_printf_http_chunk(nc, "   \"pllLck\": %s\n",             gl->wdb[b]->IsExtPllLck(false) && gl->wdb[b]->IsIntPllLck(false) ? "true" : "false");
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
      if (gl->demoMode) {
         std::poisson_distribution<int> dist(1000);
         
         for (auto i=0 ; i<34 ; i++)
            scaler.push_back(dist(randomGenerator));
      } else
         gl->wdb[b]->GetScalers(scaler);
      
      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");
      mg_printf_http_chunk(nc, "{\n");
      mg_printf_http_chunk(nc, "         \"scaler\": [\n");
      for (auto &s: scaler) {
         if (&s != &scaler.back())
            mg_printf_http_chunk(nc, "            %d,\n", s);
         else
            mg_printf_http_chunk(nc, "            %d]\n", s);
      }
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
      
      mg_get_http_var(&hm->query_string, "b", str, sizeof(str));
      int b = atoi(str);
      
      mg_get_http_var(&hm->query_string, "c", str, sizeof(str));
      int chn = atoi(str);
      
      mg_send_response_line(nc, 200, "Content-Type: application/octet-stream\r\nTransfer-Encoding: chunked\r\n");
      
      // return progress if in voltage calibration mode
//      if (vcalib_prog.state) {
//         int t = 10;    // array type
//         mg_send_http_chunk(nc, (const char *)&t, 4);
//         
//         mg_send_http_chunk(nc, (const char *)&vcalib_prog.i_board, 4);
//         
//         float f = (float)vcalib_prog.progress;
//         mg_send_http_chunk(nc, (const char *)&f, 4);
//         
//         mg_send_http_chunk(nc, "", 0);
//         return;
//      }
      
      // return progress and period in time calibration mode
//      if (tcalib_prog.state) {
//         int t = 11;    // array type
//         mg_send_http_chunk(nc, (const char *)&t, 4);
//         
//         float f = (float)tcalib_prog.i_board;
//         mg_send_http_chunk(nc, (const char *)&f, 4);
//         
//         f = (float)tcalib_prog.progress;
//         mg_send_http_chunk(nc, (const char *)&f, 4);
//         
//         for (int c=0 ; c<WD_N_CHANNELS ; c++)
//            if (chn & (1 << c)) {
//               int n = 1024;
//               mg_send_http_chunk(nc, (const char *)&c, 4);
//               mg_send_http_chunk(nc, (const char *)&n, 4);
//               
//               mg_send_http_chunk(nc, (const char *)gl->board[tcalib_prog.i_board].tcalib.period[c], sizeof(float)*n);
//            }
//         
//         mg_send_http_chunk(nc, "", 0);
//         return;
//      }
      
      // avoid invalid board index
      if (b < 0 || b >= gl->wdb.size())
         b = 0;
      
      WDEvent *event = nullptr;

      if (gl->demoMode) {
         event = new WDEvent(b);
         for (int c=0 ; c<WD_N_CHANNELS ; c++) {
            for (int i=0 ; i<1024 ; i++) {
               event->mWfT[c][i] = (float)(i*1E-6 / gl->wdb[b]->GetDrsSampleFreq());
               event->mWfU[c][i] = (float)(sin((event->mWfT[c][i]+c*1E-9)*gl->wdb[b]->GetDrsSampleFreq() / 1E-6 / 50) / 4 + ((float)random()/RAND_MAX-0.5) / 300);
            }
            // add spikes
            for (int i=0 ; i<1024 ; i++) {
               if ((float)random()/RAND_MAX < 0.00005) {
                  float s = ((float)random()/RAND_MAX-0.5) / 5;
                  int j = i-5;
                  float f;
                  for (f=0 ; f<1 ; f += 0.2,j++)
                     if (j >= 0 && j< 1024)
                        event->mWfU[c][j] += s * f;
                  for (f=1 ; f>0 ; f -= 0.2,j++)
                     if (j >= 0 && j< 1024)
                        event->mWfU[c][j] += s * f;
               }
            }
         }
      } else {
         
         // request single event
         for (auto &b: gl->wdb) {
            if (gl->triggerMode == cTriggerModeAuto)
               b->RequestEvent();
            else if (gl->triggerMode == cTriggerModeNormal)
               b->StartDaqSingle();
         }
         
         // read waveforms
         auto eVector = gl->wp->GetEvent(300);
         if (eVector) {
            if (eVector->size() > 0)
               event = (*eVector)[0];
            delete eVector;
         }
      }
      
      // save waveforms
      // wd_save_waveform(gl, b, chn, &eventHeader, wfU, wfT);
      
      if (gl->demoMode)
         b = 0xFF; // signals demo data
      
      if (event) {
         int t = 1;                 // array type
         int n = 1024;              // number of elements
         int l = 0; // gl->li.nLogged;    // number of logged events
         for (int c=0 ; c<WD_N_CHANNELS ; c++) {
            if (chn & (1 << c)) {
               t = 1; // time array
               mg_send_http_chunk(nc, (const char *)&t, 4);
               mg_send_http_chunk(nc, (const char *)&b, 4);
               mg_send_http_chunk(nc, (const char *)&l, 4);
               mg_send_http_chunk(nc, (const char *)&c, 4);
               mg_send_http_chunk(nc, (const char *)&n, 4);
               mg_send_http_chunk(nc, (const char *)event->mWfT[c], sizeof(float)*n);
            }
         }
         
         for (int c=0 ; c<WD_N_CHANNELS ; c++) {
            if (chn & (1 << c)) {
               t = 2; // voltage array
               mg_send_http_chunk(nc, (const char *)&t, 4);
               mg_send_http_chunk(nc, (const char *)&b, 4);
               mg_send_http_chunk(nc, (const char *)&l, 4);
               mg_send_http_chunk(nc, (const char *)&c, 4);
               mg_send_http_chunk(nc, (const char *)&n, 4);
               mg_send_http_chunk(nc, (const char *)event->mWfU[c], sizeof(float)*n);
            }
         }
         
      } else {
         // just return idle message
         int t = 0;
         mg_send_http_chunk(nc, (const char *)&t, 4);
         mg_send_http_chunk(nc, (const char *)&b, 4);
      }
      
      mg_send_http_chunk(nc, "", 0);
      
      delete event;
      
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

#include <execinfo.h>

void handler(int sig) {
   void *array[10];
   size_t size;
   
   // get void*'s for all entries on the stack
   size = backtrace(array, 10);
   
   // print out all the frames to stderr
   fprintf(stderr, "Error: signal %d:\n", sig);
   backtrace_symbols_fd(array, size, STDERR_FILENO);
   exit(1);
}

int main(int argc, const char * argv[])
{
   GLOBALS gl = {};
   
   // install handle to show stack trace on segment violation
   signal(SIGSEGV, handler);
   
   // default values
   gl.serverPort = 8080;
   gl.triggerMode = cTriggerModeAuto;
   
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
      std::cout << "Connect to " << b->GetName() << " ... " << std::flush;
      try {
         if (!gl.demoMode) {
            b->SetVerbose(gl.verbose);
            b->Connect(gl.wp->GetServerPort());
            b->ReceiveStatusRegisters();
            b->ReceiveControlRegisters();
            if (gl.verbose)
               b->PrintVersion();

            // fix wrong default registers
            b->SetDRSWaveContinous(true);
            b->SetDRSReadoutMode(true);
            b->SetCompPowerEnable(true);
            //b->SetDacTriggerLevelV(-1, 0);
            //b->SetDacCalDcV(0);
            
            //b->SetTriggerEnable(true);
            //b->SetTriggerCfgOr(0xFFFF);
            //b->SetTriggerExternalOr(false);
            //b->SetTriggerExternalAnd(false);
         }
      } catch (std::runtime_error &e) {
         std::cout << std::endl;
         std::cout << e.what() << std::endl;
         std::cout << "Aborting." << std::endl;
         return 1;
      }
      std::cout << " OK" << std::endl;
   }

   // tell waveform processor which WDB are active
   for (auto &b: gl.wdb)
      gl.wp->AddEventRequest(b->GetSerialNumber());

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
   
   try {
      while (true) {
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
            for (auto &b: gl.wdb) {
               b->GetTemperature(true);
            }
            last = now;
         }
        
         
      }
   } catch  (std::runtime_error &e) {
      std::cout << std::endl;
      std::cout << e.what() << std::endl;
      std::cout << "Aborting." << std::endl;
      
      mg_mgr_free(&mgr);
      
      return 1;
   }
   
   return 0;
}

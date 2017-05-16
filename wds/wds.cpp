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

#define LI_FORMAT_BIN  1
#define LI_FORMAT_XML  2

typedef struct {
   bool demoMode;
   int  serverPort;
   int  verbose;
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
      
      // get parameters from URI in the format /<item>/<board>/<channel>
      if (hm->uri.p) {
         uri = split(std::string(hm->uri.p), ' ')[0];
         args = split(uri, '/');
         if (args.size() > 1)
            item = args[1];
         if (args.size() > 2) {
            if (args[2] == "ALL")
               iBoard = -1;
            else
               iBoard = std::stoi(args[2]);
         }
         if (args.size() > 3)
            iChannel = std::stoi(args[4]);
      }
      if (hm->body.p)
         value = std::string(hm->body.p, hm->body.len);
      
      if (gl->verbose)
         std::cout << "Received item " << item
         << ", value " << value
         << ", board " << iBoard
         << ", channel " << iChannel
         << " from browser"
         << std::endl;
      
      if (item == "enableChannel") {
         // bits0-15 normal DRS channels bit16: clock0, bit17: clock1
         auto mask = std::stoi(value);
         auto mask0 = (mask & 0xFF);
         auto mask1 = (mask & 0xFF00) >> 8;
         if (mask & 0x10000)
            mask0 |= 0x100;
         if (mask & 0x20000)
            mask1 |= 0x100;
         if (iBoard == -1)
            for (auto &b: gl->wdb) {
               b->SetDrs0ChnTxEnable(mask0);
               b->SetDrs1ChnTxEnable(mask1);
            }
         else {
            gl->wdb[iBoard]->SetDrs0ChnTxEnable(mask0);
            gl->wdb[iBoard]->SetDrs1ChnTxEnable(mask1);
         }
      }

      else if (item == "rotateWaveform") {
         gl->wp->SetRotateWaveform(value == "true");
      }

      else if (item == "ofsCalib1") {
         gl->wp->SetOfsCalib1(value == "true");
      }

      else if (item == "ofsCalib2") {
         gl->wp->SetOfsCalib2(value == "true");
      }

      else if (item == "gainCalib") {
         gl->wp->SetGainCalib(value == "true");
      }

      else if (item == "rangeCalib") {
         gl->wp->SetRangeCalib(value == "true");
      }

      else if (item == "removeSpikes") {
         gl->wp->SetRemoveSpikes(value == "true");
      }

      else if (item == "timeCalib1") {
         gl->wp->SetTimeCalib1(value == "true");
      }

      else if (item == "timeCalib2") {
         gl->wp->SetTimeCalib2(value == "true");
      }

      else if (item == "timeCalib3") {
         gl->wp->SetTimeCalib3(value == "true");
      }

      else if (item == "daqClkSrcSel") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetDaqClkSrcSel(std::stoi(value));
         else
            gl->wdb[iBoard]->SetDaqClkSrcSel(value == "true");
      }

      else if (item == "dacTriggerLevel") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetDacTriggerLevelV(iChannel, std::stof(value));
         else
            gl->wdb[iBoard]->SetDacTriggerLevelV(iChannel, std::stof(value));
      }

      else if (item == "triggerDelay") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetTriggerDelayNs(std::stoi(value));
         else
            gl->wdb[iBoard]->SetTriggerDelayNs(std::stoi(value));
      }

      else if (item == "triggerFallingEdge") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetTriggerFallingEdge(value == "true");
         else
            gl->wdb[iBoard]->SetTriggerFallingEdge(value == "true");
      }

      else if (item == "triggerMode") {
         gl->triggerMode = std::stoi(value);
      }

      else if (item == "triggerSource") {
         for (int i=0 ; i<gl->wdb.size() ; i++) {
            if (iChannel == -1 || i == iChannel) {
               if (value == "0") {
                  // internal trigger
                  gl->wdb[i]->SetTriggerEnable(true);
                  gl->wdb[i]->SetTriggerCfgOr(0xFFFF);
                  gl->wdb[i]->SetTriggerExternalOr(false);
                  gl->wdb[i]->SetTriggerExternalAnd(false);
               } else {
                  // external trigger
                  gl->wdb[i]->SetTriggerEnable(true);
                  gl->wdb[i]->SetTriggerCfgOr(0);
                  gl->wdb[i]->SetTriggerExternalOr(true);
                  gl->wdb[i]->SetTriggerExternalAnd(false);
               }
            }
         }
      }

      else if (item == "feGain") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetFeGain(iChannel, std::stof(value));
         else
            gl->wdb[iBoard]->SetFeGain(iChannel, std::stof(value));
      }

      else if (item == "fePzc") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetFePzc(iChannel, value == "true");
         else
            gl->wdb[iBoard]->SetFePzc(iChannel, value == "true");
      }

      else if (item == "dacPzcLevel") {
         assert(iBoard != -1);
         gl->wdb[iBoard]->SetDacPzcLevelN(std::stoi(value));
      }

      else if (item == "range") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetRange(std::stof(value));
         else
            gl->wdb[iBoard]->SetRange(std::stof(value));
      }

      else if (item == "readoutSrcSel") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetReadoutSrcSel(std::stoi(value));
         else
            gl->wdb[iBoard]->SetReadoutSrcSel(std::stoi(value));
      }

      else if (item == "calibBufferEnable") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetCalibBufferEnable(value == "true");
         else
            gl->wdb[iBoard]->SetCalibBufferEnable(value == "true");
      }

      else if (item == "timingCalibSignalEnable") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetTimingCalibSignalEnable(value == "true");
         else
            gl->wdb[iBoard]->SetTimingCalibSignalEnable(value == "true");
      }

      else if (item == "feMux") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetFeMux(iChannel, value == "true" ? WDB::cFeMuxCalSource : WDB::cFeMuxInput);
         else
            gl->wdb[iBoard]->SetFeMux(iChannel, value == "true" ? WDB::cFeMuxCalSource : WDB::cFeMuxInput);
      }

      else if (item == "drsSampleFreq") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetDrsSampleFreq(std::stoi(value));
         else
         gl->wdb[iBoard]->SetDrsSampleFreq(std::stoi(value));
      }

      else if (item == "dacCalDc") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetDacCalDcV(std::stof(value));
         else
            gl->wdb[iBoard]->SetDacCalDcV(std::stof(value));
      }

      else if (item == "hvDemand") {
      }

      //---------- commands ----------
      else if (item == "vcalib") {
         if (!gl->demoMode)
            gl->wp->StartCalibrationVoltage(iBoard);
      }

      else if (item == "tcalib") {
         if (!gl->demoMode)
            gl->wp->StartCalibrationTime(iBoard);
      }

      else if (item == "save") {
         if (value == "stop")
            gl->wp->StopLogging();
         else if (item != "") {
            auto args = split(value, '\n');
            gl->wp->StartWaveformSaving(args[0],
                                        args[1] == "bin" ? WP::cLiFormatBinary : WP::cLiFormatXML,
                                        args[2] == "all",
                                        std::stoi(args[3]));
         }
      }

      else {
         assert(0);
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
            b1 = b;
            b2 = b + 1;
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
         
         mg_printf_http_chunk(nc, "      \"dacOfs\": %1.3f,\n",                  w->GetDacOfsV());
         mg_printf_http_chunk(nc, "      \"dacCalDc\": %1.3f,\n",                w->GetDacCalDcV());
         mg_printf_http_chunk(nc, "      \"dacPzcLevel\": %d,\n",                w->GetDacPzcLevelN());

         mg_printf_http_chunk(nc, "      \"dacTriggerLevel\": [\n");
         for (int i=0 ; i<15 ; i++)
            mg_printf_http_chunk(nc, "        %1.3f,\n",                         w->GetDacTriggerLevelV(i));
         mg_printf_http_chunk(nc, "        %1.3f ],\n",                          w->GetDacTriggerLevelV(15));

         mg_printf_http_chunk(nc, "      \"fePzc\": [\n");
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
      mg_get_http_var(&hm->query_string, "b", str, sizeof(str));
      int b = atoi(str);

      if (gl->verbose)
         std::cout<< "Sending /status board " << b << " to browser" << std::endl;

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
      mg_get_http_var(&hm->query_string, "b", str, sizeof(str));
      int b = atoi(str);
      
      if (gl->verbose)
         std::cout<< "Sending /scalers board " << b << " to browser" << std::endl;

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
      if (gl->wp->IsVcalibActive()) {
         int t = 10;    // array type
         mg_send_http_chunk(nc, (const char *)&t, 4);
         
         int b = gl->wp->GetVcalibBoard();
         mg_send_http_chunk(nc, (const char *)&b, 4);
         
         float f = gl->wp->GetVcalibProgress();
         mg_send_http_chunk(nc, (const char *)&f, 4);
         
         mg_send_http_chunk(nc, "", 0);
         return;
      }
      
      // return progress and period in time calibration mode
      if (gl->wp->IsTcalibActive()) {
         int t = 11;    // array type
         mg_send_http_chunk(nc, (const char *)&t, 4);
         
         int b = gl->wp->GetTcalibBoard();
         mg_send_http_chunk(nc, (const char *)&b, 4);
         
         float f = gl->wp->GetVcalibProgress();
         mg_send_http_chunk(nc, (const char *)&f, 4);
         
         for (int c=0 ; c<WD_N_CHANNELS ; c++)
            if (chn & (1 << c)) {
               int n = 1024;
               mg_send_http_chunk(nc, (const char *)&c, 4);
               mg_send_http_chunk(nc, (const char *)&n, 4);
               
               mg_send_http_chunk(nc, (const char *)gl->wdb[b]->mTCalib.mCalib.period[c], sizeof(float)*n);
            }
         
         mg_send_http_chunk(nc, "", 0);
         return;
      }
      
      // avoid invalid board index
      if (b < 0 || b >= gl->wdb.size())
         b = 0;
      
      WDEvent *event = nullptr;

      if (gl->demoMode) {
         event = new WDEvent(b);
         for (int c=0 ; c<WD_N_CHANNELS ; c++) {
            for (int i=0 ; i<1024 ; i++) {
               float t = i*1E-6 / gl->wdb[b]->GetDrsSampleFreq();
               event->mWfT[c][i] = t;
               event->mWfU[c][i] = (float)(sin(M_PI*2 * 100E6 * t + c/8.0)/2 + ((float)random()/RAND_MAX-0.5) / 300);
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
         if (b == -1) {
            // all boards
            gl->wp->RequestAllBoards();

            for (auto &b: gl->wdb) {
               if (gl->triggerMode == cTriggerModeAuto)
                  b->RequestEvent();
               else if (gl->triggerMode == cTriggerModeNormal)
                  b->StartDaqSingle();
            }
         } else {
            // only current board
            gl->wp->RequestBoard(gl->wdb[b]);

            if (gl->triggerMode == cTriggerModeAuto)
               gl->wdb[b]->RequestEvent();
            else if (gl->triggerMode == cTriggerModeNormal)
               gl->wdb[b]->StartDaqSingle();
         }
         
         // read waveforms
         auto eVector = gl->wp->GetEvent(500);
         if (eVector) {
            if (eVector->size() > 0)
               event = (*eVector)[0];
            delete eVector;
         }
      }
      
      if (gl->demoMode)
         b = 0xFF; // signals demo data
      
      if (event) {
         int t = 1;                    // array type
         int n = 1024;                 // number of elements
         int l = gl->wp->GetNLogged(); // number of logged events
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
   std::cerr << "valid options:" << std::endl;
   std::cerr << "  -h              Show this help" << std::endl;
   std::cerr << "  -d              Demo mode" << std::endl;
   std::cerr << "  -p              HTTP server port (default is 8080)" << std::endl;
   std::cerr << "  -w <address>    Internet address(es) of WaveDREAM board(s)" << std::endl;
   std::cerr << "  -v 1            Print extra information (verbose)" << std::endl;
   std::cerr << "  -v 2            Print in addition each received waveform packet header" << std::endl;
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
   gl.verbose = 0;
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
      
      else if (arg == "-v") {
         gl.verbose = 1;
         if (i < argc-1 && isdigit(argv[i+1][0]))
            gl.verbose = std::stoi(argv[++i]);
      }
      
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
   
   // connect to all WDB and retrieve registers
   for (auto &b: gl.wdb) {
      std::cout << "Connect to " << b->GetName() << " ... " << std::flush;
      try {
         if (!gl.demoMode) {
            b->SetVerbose(gl.verbose);
            b->Connect();
            b->ReceiveStatusRegisters();
            b->ReceiveControlRegisters();
            if (gl.verbose) {
               std::cout << std::endl << "========== Board Info ==========" << std::endl;
               b->PrintVersion();
            }

            // load calibration data for board
            b->LoadVoltageCalibration();
            b->LoadTimeCalibration();
            
         } else {
            // turnall channels on in demo mode
            b->SetDrs0ChnTxEnable(0xFFFF);
            b->SetDrs1ChnTxEnable(0xFFFF);
         }
      } catch (std::runtime_error &e) {
         std::cout << std::endl;
         std::cout << e.what() << std::endl;
         std::cout << "Aborting." << std::endl;
         return 1;
      }
      std::cout << "OK" << std::endl;
      if (gl.verbose)
         std::cout << std::endl << std::endl;
   }
   
   // instantiate waveform processor
   gl.wp = new WP(gl.wdb, gl.verbose, gl.demoMode);
   if (gl.wdb[0]->mVCalib.IsValid()) {
      gl.wp->SetOfsCalib1(true);
      gl.wp->SetOfsCalib2(true);
      gl.wp->SetGainCalib(true);
      gl.wp->SetRangeCalib(true);
      gl.wp->SetRemoveSpikes(true);
   }
   if (gl.wdb[0]->mTCalib.IsValid()) {
      gl.wp->SetTimeCalib1(true);
      gl.wp->SetTimeCalib2(true);
      gl.wp->SetTimeCalib3(true);
   }

   // set destination port after WP has been initialized
   for (auto &b: gl.wdb)
      b->SetDestinationPort(gl.wp->GetServerPort());
   
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
         
         // do calibration if asked for
         if (gl.wp->IsVcalibActive()) {
            gl.wp->DoCalibrationVoltageStep();
            
            // Yield to server, no timeout
            mg_mgr_poll(&mgr, 0);
         
         } else if (gl.wp->IsTcalibActive()) {
            gl.wp->DoCalibrationTimeStep();
            
            // Yield to server, no timeout
            mg_mgr_poll(&mgr, 0);
         
         } else
            // Yield to server, 10ms timeout
            mg_mgr_poll(&mgr, 10);
         
         // read board temperatures and lock status periodically
         time(&now);
         if (now > last + 10) {
            for (auto &b: gl.wdb) {
               b->GetTemperature(true);
               b->IsExtPllLck(true);
               b->IsIntPllLck(true);
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

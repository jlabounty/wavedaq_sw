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

enum TRIGGERMODE {
   cTriggerModeNormal = 1,
   cTriggerModeAuto   = 2
};

enum READOUTMODE {
   cReadoutModeDRS    = 1,
   cReadoutModeADC    = 2,
   cREadoutModeTDC    = 3
};

#define LI_FORMAT_BIN  1
#define LI_FORMAT_XML  2

typedef struct {
   bool              demoMode;
   int               serverPort;
   int               verbose;
   std::string       logFileName;
   bool              reset;
   std::vector<WDB*> wdb;
   WP*               wp;
   TRIGGERMODE       triggerMode;
   int               triggerSelfArm;
   int               triggerHoldoff;
   READOUTMODE       readoutMode;
   bool              specialTest;
   bool              updatePeriodic;
   int               dbgRx;
   int               dbgTx;
} GLOBALS;

unsigned int demoDrsSampleFreq = 5016;

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
            iChannel = std::stoi(args[3]);
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
         if (iBoard == -1)
            for (auto &b: gl->wdb) {
               b->SetChnTxEn(mask);
               if (gl->readoutMode == cReadoutModeDRS)
                  b->SetDrsChTxEn(mask);
               else
                  b->SetAdcChTxEn(mask);
            }
         else {
            gl->wdb[iBoard]->SetChnTxEn(mask);
            if (gl->readoutMode == cReadoutModeDRS)
               gl->wdb[iBoard]->SetDrsChTxEn(mask);
            else
               gl->wdb[iBoard]->SetAdcChTxEn(mask);
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

      else if (item == "triggerMode") {
         gl->triggerMode = (TRIGGERMODE) std::stoi(value);
      }

      else if (item == "triggerHoldoff") {
         gl->triggerHoldoff = std::stoi(value);
      }

      else if (item == "triggerSource") {
         for (int i=0 ; i<gl->wdb.size() ; i++) {
            if (iChannel == -1 || i == iChannel) {
               if (value == "0") {
                  // internal trigger
                  gl->wdb[i]->SetTriggerTypeSel(1);
               } else {
                  // external trigger
                  gl->wdb[i]->SetTriggerTypeSel(0);
               }
            }
         }
      }
      
      else if (item == "triggerDelay") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetTriggerDelayNs(std::stoi(value));
         else
            gl->wdb[iBoard]->SetTriggerDelayNs(std::stoi(value));
      }

      else if (item == "triggerLeadTrailEdgeSel") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetLeadTrailEdgeSel(std::stoi(value));
         else
            gl->wdb[iBoard]->SetLeadTrailEdgeSel(std::stoi(value));
      }

      else if (item == "triggerSrcPolarity") {
         if (iBoard == -1)
            for (auto &b: gl->wdb) {
               b->SetTrgSrcPolarity(std::stoi(value));
            }
         else {
            gl->wdb[iBoard]->SetTrgSrcPolarity(std::stoi(value));
         }
      }

      else if (item == "triggerPtrnEn") {
         if (iBoard == -1)
            for (auto &b: gl->wdb) {
               b->SetTrgPtrnEn(std::stoi(value));
            }
         else {
            gl->wdb[iBoard]->SetTrgPtrnEn(std::stoi(value));
         }
      }

      else if (item == "triggerSrcEnPtrn") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetTrgSrcEnPtrn(iChannel, std::stoi(value));
         else
            gl->wdb[iBoard]->SetTrgSrcEnPtrn(iChannel, std::stoi(value));
      }

      else if (item == "triggerStatePtrn") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetTrgStatePtrn(iChannel, std::stoi(value));
         else
            gl->wdb[iBoard]->SetTrgStatePtrn(iChannel, std::stoi(value));
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
         gl->wdb[iBoard]->SetDacPzcLevelN(std::stoi(value)-1);
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
            for (auto &b: gl->wdb) {
               if (std::stoi(value) == (int)cReadoutModeDRS) {
                  gl->readoutMode = cReadoutModeDRS;
                  b->SetDrsChTxEn(b->GetChnTxEn());
                  b->SetAdcChTxEn(0);
               } else {
                  gl->readoutMode = cReadoutModeADC;
                  b->SetDrsChTxEn(0);
                  b->SetAdcChTxEn(b->GetChnTxEn());
               }
            }
         else {
            if (std::stoi(value) == (int)cReadoutModeDRS) {
               gl->readoutMode = cReadoutModeDRS;
               gl->wdb[iBoard]->SetDrsChTxEn(gl->wdb[iBoard]->GetChnTxEn());
               gl->wdb[iBoard]->SetAdcChTxEn(0);
            } else {
               gl->readoutMode = cReadoutModeADC;
               gl->wdb[iBoard]->SetDrsChTxEn(0);
               gl->wdb[iBoard]->SetAdcChTxEn(gl->wdb[iBoard]->GetChnTxEn());
            }
         }
         if (gl->readoutMode == cReadoutModeDRS)
            gl->wp->SetRequestedSegments(2);
         else if (gl->readoutMode == cReadoutModeADC)
            gl->wp->SetRequestedSegments(3);
      }

      else if (item == "calibBufferEnable") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetCalibBufferEn(value == "true");
         else
            gl->wdb[iBoard]->SetCalibBufferEn(value == "true");
      }

      else if (item == "timingCalibSignalEnable") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetTimingCalibSignalEnable(value == "true");
         else
            gl->wdb[iBoard]->SetTimingCalibSignalEnable(value == "true");
      }

      else if (item == "timingReferenceSignal") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetTimingReferenceSignal(std::stoi(value));
         else
            gl->wdb[iBoard]->SetTimingReferenceSignal(std::stoi(value));
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
            for (auto &b: gl->wdb) {
               b->SetDrsSampleFreq(std::stoi(value));
               b->LoadVoltageCalibration(b->GetDrsSampleFreqMhz());
               b->LoadTimeCalibration(b->GetDrsSampleFreqMhz());
            }
         else {
            gl->wdb[iBoard]->SetDrsSampleFreq(std::stoi(value));
            gl->wdb[iBoard]->LoadVoltageCalibration(gl->wdb[iBoard]->GetDrsSampleFreqMhz());
            gl->wdb[iBoard]->LoadTimeCalibration(gl->wdb[iBoard]->GetDrsSampleFreqMhz());
         }
         demoDrsSampleFreq = std::stoi(value);
      }

      else if (item == "dacCalDc") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetDacCalDcV(std::stof(value));
         else
            gl->wdb[iBoard]->SetDacCalDcV(std::stof(value));
      }

      else if (item == "hvTarget") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetHVTarget(iChannel, std::stof(value));
         else
            gl->wdb[iBoard]->SetHVTarget(iChannel, std::stof(value));
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
                                        args[2] == "all" ? -1 : std::stoi(args[2]),
                                        std::stoi(args[3]));
         }
      }

      else {
         std::cout << "Invalid command \"" << item << "\" received. Aborting." << std::endl;
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
      mg_printf_http_chunk(nc, "      \"updatePeriodic\": %d,\n",                gl->updatePeriodic);
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
      mg_printf_http_chunk(nc, "      \"timeCalib3\": %s\n",                    gl->wp->IsTimeCalib3() ? "true" : "false");
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

         // simulate gaussian distributed scalers in demo mode
         std::vector<unsigned long> scaler;
         if (gl->demoMode) {
            std::poisson_distribution<int> dist(1000);
            
            for (auto i=0 ; i<34 ; i++)
               scaler.push_back(dist(randomGenerator));
         } else
            w->GetScalers(scaler, false);
         
         // obtain HVs
         std::vector<float> hv_target;
         std::vector<float> hv_current;
         std::vector<float> hv_temp;
         float hv_base;
         if (gl->demoMode) {
            for (auto i=0 ; i<16 ; i++) {
               hv_target.push_back(0);
               hv_current.push_back(0);
            }
            for (auto i=0 ; i<4 ; i++) {
               hv_temp.push_back(20.0);
            }
            hv_base = 0;
         } else {
            w->GetHVTarget(hv_target);
            w->GetHVCurrents(hv_current);
            w->Get1wireTemperatures(hv_temp);
            w->GetHVBaseVoltage(hv_base);
         }
         
         mg_printf_http_chunk(nc, "    {\n");
         mg_printf_http_chunk(nc, "      \"name\": \"%s\",\n",                   w->GetName().c_str());
         mg_printf_http_chunk(nc, "      \"temperature\": %1.1lf,\n",            w->GetTemperatureDegree(false));
         mg_printf_http_chunk(nc, "      \"sysBusy\": %s,\n",                    w->GetSysBusy() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"wdbBusy\": %s,\n",                    w->GetWdbBusy() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"hvBoardPlugged\": %s,\n",             w->GetHvBoardPlugged() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"hvBackplanePlugged\": %s,\n",         w->GetBackplanePlugged() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"pllLck\": %d,\n",                     w->GetPllLock(false));
         mg_printf_http_chunk(nc, "      \"drsSampleFreq\": %d,\n",              gl->demoMode ?
                                                                                   demoDrsSampleFreq : w->GetDrsSampleFreqMhz());
         mg_printf_http_chunk(nc, "      \"adcSampleFreq\": %d,\n",              w->GetAdcSampleFreq() / 1000);
         mg_printf_http_chunk(nc, "      \"compChannelStatus\": %d,\n",          w->GetCompChStat());
         mg_printf_http_chunk(nc, "      \"lastEventNumber\": %d,\n",            w->GetEventNumber());
         mg_printf_http_chunk(nc, "      \"triggerBusParityErrorCount\": %d,\n", w->GetTrbParityErrorCount());
         mg_printf_http_chunk(nc, "      \"triggerBusType\": %d,\n",             w->GetTrbInfoLsb() & 0xFF); // ??
         mg_printf_http_chunk(nc, "      \"triggerBusNumber\": %d,\n",           w->GetTrbInfoLsb() >> 8);   // ??
         mg_printf_http_chunk(nc, "      \"crateId\": %d,\n",                    w->GetCrateId());
         mg_printf_http_chunk(nc, "      \"slotId\": %d,\n",                     w->GetSlotId());
         mg_printf_http_chunk(nc, "      \"readoutSrcSel\": %d,\n",              gl->readoutMode);
         mg_printf_http_chunk(nc, "      \"daqNormal\": %s,\n",                  w->GetDaqNormal() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"daqSingle\": %s,\n",                  w->GetDaqSingle() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"drs0TimingRefSel\": %d,\n",           w->GetDrs0TimingRefSel());
         mg_printf_http_chunk(nc, "      \"drs1TimingRefSel\": %d,\n",           w->GetDrs1TimingRefSel());
         mg_printf_http_chunk(nc, "      \"calibBufferEnable\": %s,\n",          w->GetCalibBufferEn() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"timingCalibSignalEnable\": %d,\n",    w->GetTimingCalibSignalEn());
         mg_printf_http_chunk(nc, "      \"timingReferenceSignal\": %d,\n",      w->GetTimingReferenceSignal());
         mg_printf_http_chunk(nc, "      \"daqClkSrcSel\": %d,\n",               w->GetDaqClkSrcSel());
         mg_printf_http_chunk(nc, "      \"extClkInSel\": %d,\n",                w->GetExtClkInSel());
         mg_printf_http_chunk(nc, "      \"extClkFreq\": %d,\n",                 w->GetExtClkFreq());
         mg_printf_http_chunk(nc, "      \"localClkFreq\": %d,\n",               w->GetLocalClkFreq());
         mg_printf_http_chunk(nc, "      \"chnTxEn\": %d,\n",                    w->GetChnTxEn());
         
         mg_printf_http_chunk(nc, "      \"dacOfs\": %1.3f,\n",                  w->GetDacOfsV());
         mg_printf_http_chunk(nc, "      \"dacCalDc\": %1.3f,\n",                w->GetDacCalDcV());
         mg_printf_http_chunk(nc, "      \"dacPzcLevel\": %d,\n",                w->GetDacPzcLevelN());

         mg_printf_http_chunk(nc, "      \"dacTriggerLevel\": [\n");
         for (int i=0 ; i<15 ; i++)
            mg_printf_http_chunk(nc, "        %1.3f,\n",                         w->GetDacTriggerLevelV(i));
         mg_printf_http_chunk(nc, "        %1.3f ],\n",                          w->GetDacTriggerLevelV(15));

         mg_printf_http_chunk(nc, "      \"fePzc\": [\n");
         for (int i=0 ; i<15 ; i++)
            mg_printf_http_chunk(nc, "        %s,\n",                            w->GetFePzc(i) ? "true" : "false");
         mg_printf_http_chunk(nc, "        %s ],\n",                             w->GetFePzc(15) ? "true" : "false");

         mg_printf_http_chunk(nc, "      \"feGain\": [\n");
         for (int i=0 ; i<15 ; i++)
            mg_printf_http_chunk(nc, "        %1g,\n",                           w->GetFeGain(i));
         mg_printf_http_chunk(nc, "        %1g ],\n",                            w->GetFeGain(15));

         mg_printf_http_chunk(nc, "      \"feMux\": [\n");
         for (int i=0 ; i<15 ; i++)
            mg_printf_http_chunk(nc, "        %d,\n",                            w->GetFeMux(i));
         mg_printf_http_chunk(nc, "        %d ],\n",                             w->GetFeMux(15));

         mg_printf_http_chunk(nc, "      \"triggerMode\": %d,\n",                gl->triggerMode);
         mg_printf_http_chunk(nc, "      \"triggerHoldoff\": %d,\n",             gl->triggerHoldoff);
         mg_printf_http_chunk(nc, "      \"triggerLeadTrailEdgeSel\": %d,\n",    w->GetLeadTrailEdgeSel());
         mg_printf_http_chunk(nc, "      \"triggerExtTriggerOutEnable\": %s,\n", w->GetExtTriggerOutEnable() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"triggerSource\": %d,\n",              w->GetTriggerTypeSel() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"triggerOutPulseLength\": %d,\n",      w->GetTriggerOutPulseLength());
         mg_printf_http_chunk(nc, "      \"triggerDelay\": %d,\n",               w->GetTriggerDelayNs());
         mg_printf_http_chunk(nc, "      \"triggerSrcPolarity\": %d,\n",         w->GetTrgSrcPolarity());
         mg_printf_http_chunk(nc, "      \"triggerAutoTriggerPeriod\": %d,\n",   w->GetAutoTriggerPeriod());
         mg_printf_http_chunk(nc, "      \"triggerPtrnEn\": %d,\n",              w->GetTrgPtrnEn());

         mg_printf_http_chunk(nc, "      \"triggerSrcEnPtrn\": [\n");
         for (int i=0 ; i<17 ; i++)
            mg_printf_http_chunk(nc, "        %d,\n",                            w->GetTrgSrcEnPtrn(i));
         mg_printf_http_chunk(nc, "        %d ],\n",                             w->GetTrgSrcEnPtrn(17));

         mg_printf_http_chunk(nc, "      \"triggerStatePtrn\": [\n");
         for (int i=0 ; i<17 ; i++)
            mg_printf_http_chunk(nc, "        %d,\n",                            w->GetTrgStatePtrn(i));
         mg_printf_http_chunk(nc, "        %d ],\n",                             w->GetTrgStatePtrn(17));

         mg_printf_http_chunk(nc, "      \"scaler\": [\n");
         for (auto &s: scaler) {
            if (&s != &scaler.back())
               mg_printf_http_chunk(nc, "        %d,\n", s);
            else
               mg_printf_http_chunk(nc, "        %d],\n", s);
         }
         
         mg_printf_http_chunk(nc, "      \"hv\": {\n");

         mg_printf_http_chunk(nc, "        \"target\": [\n");
         for (auto &s: hv_target) {
            if (&s != &hv_target.back())
               mg_printf_http_chunk(nc, "            %g,\n", s);
            else
               mg_printf_http_chunk(nc, "            %g],\n", s);
         }
         mg_printf_http_chunk(nc, "        \"current\": [\n");
         for (auto &s: hv_current) {
            if (&s != &hv_current.back())
               mg_printf_http_chunk(nc, "            %g,\n", s);
            else
               mg_printf_http_chunk(nc, "            %g],\n", s);
         }
         mg_printf_http_chunk(nc, "        \"temperature\": [\n");
         for (auto &s: hv_temp) {
            if (&s != &hv_temp.back())
               mg_printf_http_chunk(nc, "            %g,\n", s);
            else
               mg_printf_http_chunk(nc, "            %g],\n", s);
         }
         mg_printf_http_chunk(nc, "        \"baseVoltage\": %g\n\n", hv_base);

         mg_printf_http_chunk(nc, "      }\n");

         if (b == b2-1)
            mg_printf_http_chunk(nc, "    }\n");
         else
            mg_printf_http_chunk(nc, "    },\n");
      }
      
      mg_printf_http_chunk(nc, "  ]\n");
      mg_printf_http_chunk(nc, "}\n");
      mg_send_http_chunk(nc, "", 0);
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
         
         float f = gl->wp->GetTcalibProgress();
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
      
      WDEvent event(gl->wdb[b]->GetSerialNumber());
      bool bNewEvent = false;
      
      if (gl->demoMode) {
         bNewEvent = true;
         event.mVCalibrated = true;
         event.mTCalibrated = true;
         for (int c=0 ; c<WD_N_CHANNELS ; c++) {
            for (int i=0 ; i<1024 ; i++) {
               float t = i*1E-6 / demoDrsSampleFreq;
               event.mWfT[c][i] = t;
               event.mWfU[c][i] = (float)(sin(M_PI*2 * 100E6 * t + c/8.0)/2 + ((float)random()/RAND_MAX-0.5) / 300);
            }
            // add spikes
            for (int i=0 ; i<1024 ; i++) {
               if ((float)random()/RAND_MAX < 0.00005) {
                  float s = ((float)random()/RAND_MAX-0.5) / 5;
                  int j = i-5;
                  float f;
                  for (f=0 ; f<1 ; f += 0.2,j++)
                     if (j >= 0 && j< 1024)
                        event.mWfU[c][j] += s * f;
                  for (f=1 ; f>0 ; f -= 0.2,j++)
                     if (j >= 0 && j< 1024)
                        event.mWfU[c][j] += s * f;
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
                  b->SetDaqSingle(1);
            }
         } else {
            // only current board
            gl->wp->RequestBoard(gl->wdb[b]);

            if (gl->triggerMode == cTriggerModeAuto)
               gl->wdb[b]->RequestEvent();
            else if (gl->triggerMode == cTriggerModeNormal) {
               if (!gl->triggerSelfArm)
                  gl->wdb[b]->SetDaqSingle(1);
            }
         }
         
         // read waveforms
         bNewEvent = gl->wp->GetLastEvent(gl->wdb[b], 100, event);
      }
      
      if (gl->demoMode)
         b = 0xFF; // signals demo data
      
      if (bNewEvent) {
         if (event.mWFTypeADC) { //---- ADC waveforms
            int t = 1;                    // array type
            int n = 1024;                 // number of elements
            int vc = event.mVCalibrated;  // voltage calibrated
            int tc = event.mTCalibrated;  // time calibrated
            int l = gl->wp->GetNLogged(); // number of logged events
            for (int c=0 ; c<WD_N_CHANNELS ; c++) {
               if (chn & (1 << c)) {
                  t = 1; // time array
                  mg_send_http_chunk(nc, (const char *)&t, 4);
                  mg_send_http_chunk(nc, (const char *)&b, 4);
                  mg_send_http_chunk(nc, (const char *)&tc, 4);
                  mg_send_http_chunk(nc, (const char *)&l, 4);
                  mg_send_http_chunk(nc, (const char *)&c, 4);
                  mg_send_http_chunk(nc, (const char *)&n, 4);
                  mg_send_http_chunk(nc, (const char *)&event.mWfTADC[c][0], sizeof(float)*n);
               }
            }
            
            for (int c=0 ; c<WD_N_CHANNELS ; c++) {
               if (chn & (1 << c)) {
                  t = 2; // voltage array
                  mg_send_http_chunk(nc, (const char *)&t, 4);
                  mg_send_http_chunk(nc, (const char *)&b, 4);
                  mg_send_http_chunk(nc, (const char *)&vc, 4);
                  mg_send_http_chunk(nc, (const char *)&l, 4);
                  mg_send_http_chunk(nc, (const char *)&c, 4);
                  mg_send_http_chunk(nc, (const char *)&n, 4);
                  mg_send_http_chunk(nc, (const char *)&event.mWfUADC[c][1024], sizeof(float)*n);
               }
            }
         } else { //---- DRS waveforms
            int t = 1;                    // array type
            int n = 1024;                 // number of elements
            int vc = event.mVCalibrated;  // voltage calibrated
            int tc = event.mTCalibrated;  // time calibrated
            int l = gl->wp->GetNLogged(); // number of logged events
            for (int c=0 ; c<WD_N_CHANNELS ; c++) {
               if (chn & (1 << c)) {
                  t = 1; // time array
                  mg_send_http_chunk(nc, (const char *)&t, 4);
                  mg_send_http_chunk(nc, (const char *)&b, 4);
                  mg_send_http_chunk(nc, (const char *)&tc, 4);
                  mg_send_http_chunk(nc, (const char *)&l, 4);
                  mg_send_http_chunk(nc, (const char *)&c, 4);
                  mg_send_http_chunk(nc, (const char *)&n, 4);
                  mg_send_http_chunk(nc, (const char *)event.mWfT[c], sizeof(float)*n);
               }
            }
            
            for (int c=0 ; c<WD_N_CHANNELS ; c++) {
               if (chn & (1 << c)) {
                  t = 2; // voltage array
                  mg_send_http_chunk(nc, (const char *)&t, 4);
                  mg_send_http_chunk(nc, (const char *)&b, 4);
                  mg_send_http_chunk(nc, (const char *)&vc, 4);
                  mg_send_http_chunk(nc, (const char *)&l, 4);
                  mg_send_http_chunk(nc, (const char *)&c, 4);
                  mg_send_http_chunk(nc, (const char *)&n, 4);
                  mg_send_http_chunk(nc, (const char *)event.mWfU[c], sizeof(float)*n);
               }
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
   std::cerr << "  -g rx tx        Debug output at RX/TX ports" << std::endl;
   std::cerr << "  -l <logfile>    Log file for debugging" << std::endl;
   std::cerr << "  -p              HTTP server port (default is 8080)" << std::endl;
   std::cerr << "  -r              Reset all PLLs" << std::endl;
   std::cerr << "  -s              Run WDB in self-arm mode (use with caution!)" << std::endl;
   std::cerr << "  -u              Retrieve WDB registers once per second to capture changes by other control programs" << std::endl;
   std::cerr << "  -w <address>    Internet address(es) of WaveDREAM board(s)" << std::endl;
   std::cerr << "  -v 1            Print extra information (verbose)" << std::endl;
   std::cerr << "  -v 2            Print each received waveform packet header" << std::endl;
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
   gl.logFileName = "";
   gl.reset = false;
   gl.triggerMode = cTriggerModeAuto;
   gl.triggerSelfArm = false;
   gl.triggerHoldoff = 0;
   gl.readoutMode = cReadoutModeDRS;
   gl.updatePeriodic = false;
   gl.dbgRx = gl.dbgTx = 0;
   
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

      else if (arg == "-g") {
         gl.dbgRx = std::stoi(argv[++i]);
         gl.dbgTx = std::stoi(argv[++i]);
      }

      else if (arg == "-l")
         gl.logFileName = std::string(argv[++i]);

      else if (arg == "-r")
         gl.reset = true;

      else if (arg == "-s")
         gl.triggerSelfArm = true;

      else if (arg == "-u")
         gl.updatePeriodic = true;
      
      else if (arg == "-v") {
         gl.verbose = 1;
         if (i < argc-1 && isdigit(argv[i+1][0]))
            gl.verbose = std::stoi(argv[++i]);
      }

      else if (arg == "-t")
         gl.specialTest = true;

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
            b->SetLogFile(gl.logFileName);
            b->Connect();
            b->ReceiveStatusRegisters();
            b->ReceiveControlRegisters();
            if (gl.verbose) {
               std::cout << std::endl << "========== Board Info ==========" << std::endl;
               b->PrintVersion();
            }

            // load calibration data for board
            b->LoadVoltageCalibration(b->GetDrsSampleFreqMhz());
            b->LoadTimeCalibration(b->GetDrsSampleFreqMhz());
            
            // debug output
            if (gl.dbgRx > 0)
               b->SetMcxRxSigSel(gl.dbgRx);
            if (gl.dbgTx > 0)
               b->SetMcxTxSigSel(gl.dbgTx);
            
            // reset PLLs
            if (gl.reset) {
               b->ResetAllPll();
               auto f = b->GetDrsSampleFreqMhz();
               if (f > 5120)
                  f = 5120;
               if (f < 700)
                  f = 700;
               b->SetDrsSampleFreq(f);
               sleep_ms(10);
               b->GetPllLock(true);
            }
            
            // check PLL locked status
            if (!b->GetPllLock(false)) {
               std::ostringstream str;
               str << "PLL not locked on board " << b->GetName() << ". Mask = 0x" << std::hex << b->GetPllLock(false);
               throw std::runtime_error(str.str());
            }
            
            if (b->GetDrsChTxEn() > 0) {
               gl.readoutMode = cReadoutModeDRS;
               b->SetChnTxEn(b->GetDrsChTxEn());
            } else if (b->GetAdcChTxEn() > 0) {
               gl.readoutMode = cReadoutModeADC;
               b->SetChnTxEn(b->GetAdcChTxEn());
            }
            else {
               b->SetDrsChTxEn(0xFFFF);
               b->SetChnTxEn(0xFFFF);
            }

         } else {
            // turn all channels on in demo mode
            b->SetDrsChTxEn(0xFFFF);
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
   
   if (gl.reset) {
      std::cout << "All PLLs reset" << std::endl;
      return 0;
   }
   // instantiate waveform processor
   gl.wp = new WP(gl.wdb, gl.verbose, gl.logFileName, gl.demoMode);
   if (gl.wdb[0]->mVCalib.IsValid()) {
      gl.wp->SetOfsCalib1(true);
      gl.wp->SetOfsCalib2(true);
      gl.wp->SetGainCalib(true);
      gl.wp->SetRangeCalib(true);
   }
   if (gl.wdb[0]->mTCalib.IsValid()) {
      gl.wp->SetTimeCalib1(true);
      gl.wp->SetTimeCalib2(true);
      gl.wp->SetTimeCalib3(true);
   }

   // set destination port after WP has been initialized
   for (auto &b: gl.wdb)
      b->SetDestinationPort(gl.wp->GetServerPort());
   
   // switch boards to normal mode to send events
   if (gl.triggerSelfArm)
      gl.triggerMode = cTriggerModeNormal;
   else {
      for (auto &b: gl.wdb) {
         b->SetDaqNormal(false);
      }
   }

   if (gl.specialTest) {
   }
   
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

         if (now > last) {
            // update every second all status registers
            for (auto &b: gl.wdb)
               b->ReceiveStatusRegisters();
            // update all control registers if requested
            if (gl.updatePeriodic) {
               for (auto &b: gl.wdb)
                  b->ReceiveControlRegisters();
            }
            last = now;
         }
      }
   } catch  (std::runtime_error &e) {
      std::cout << std::endl;
      std::cout << e.what() << std::endl;
      std::cout << "Aborting." << std::endl;
      
      return 1;
   }
   
   return 0;
}

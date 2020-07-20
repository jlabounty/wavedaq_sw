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
#include <random>
#include <execinfo.h>
#include <fstream>
#include <algorithm>

#include "WDBLib.h"
#include "DCBLib.h"

#include "mongoose.h"

/*-- Globals -------------------------------------------------------*/

enum TRIGGERMODE {
   cTriggerModeNormal = 1,
   cTriggerModeAuto = 2
};

enum READOUTMODE {
   cReadoutModeDRS = 1,
   cReadoutModeADC = 2,
   cReadoutModeTDC = 3
};

typedef struct {
   bool demoMode;
   int serverPort;
   int verbose;
   std::string logFileName;
   bool reset;
   std::vector<WDB *> wdb;
   std::vector<DCB *> dcb;
   WP *wp;
   TRIGGERMODE triggerMode;
   int triggerSelfArm;
   READOUTMODE readoutMode;
   bool specialTest;
   bool updatePeriodic;
   int dbgRx;
   int dbgTx;
   std::string wdsDir;
} GLOBALS;

unsigned int demoDrsSampleFreq = 5016;

/*------------------------------------------------------------------*/

std::vector<std::string> split(const std::string &input, char separator) {
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
         s = s.substr(0, endpos + 1);
      output.push_back(s);
   }

   return output;
}

/*------------------------------------------------------------------*/

static struct mg_serve_http_opts s_http_server_opts;

// This function will be called by mongoose on every new request
static void wds_handler(struct mg_connection *nc, int http_event, void *p) {
   struct http_message *hm = (struct http_message *) p;
   char str[256];
   static std::default_random_engine randomGenerator;

   GLOBALS *gl = (GLOBALS *) nc->mgr->user_data;

   if (http_event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->method, "PUT") == 0) {
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
               if (b->GetAdcChTxEn() != 0 || gl->readoutMode == cReadoutModeADC) b->SetAdcChTxEn(mask);
               if (b->GetTdcChTxEn() != 0 || gl->readoutMode == cReadoutModeTDC) b->SetTdcChTxEn(mask);
               if (b->GetDrsChTxEn() != 0 || gl->readoutMode == cReadoutModeDRS) b->SetDrsChTxEn(mask);
            }
         else {
            gl->wdb[iBoard]->SetChnTxEn(mask);
            if (gl->wdb[iBoard]->GetAdcChTxEn() != 0 || gl->readoutMode == cReadoutModeADC)
               gl->wdb[iBoard]->SetAdcChTxEn(mask);
            if (gl->wdb[iBoard]->GetTdcChTxEn() != 0 || gl->readoutMode == cReadoutModeTDC)
               gl->wdb[iBoard]->SetTdcChTxEn(mask);
            if (gl->wdb[iBoard]->GetDrsChTxEn() != 0 || gl->readoutMode == cReadoutModeDRS)
               gl->wdb[iBoard]->SetDrsChTxEn(mask);
         }
      } else if (item == "rotateWaveform") {
         gl->wp->SetRotateWaveform(value == "true");
      } else if (item == "ofsCalib1") {
         gl->wp->SetOfsCalib1(value == "true");
      } else if (item == "ofsCalib2") {
         gl->wp->SetOfsCalib2(value == "true");
      } else if (item == "gainCalib") {
         gl->wp->SetGainCalib(value == "true");
      } else if (item == "rangeCalib") {
         gl->wp->SetRangeCalib(value == "true");
      } else if (item == "timeCalib1") {
         gl->wp->SetTimeCalib1(value == "true");
      } else if (item == "timeCalib2") {
         gl->wp->SetTimeCalib2(value == "true");
      } else if (item == "timeCalib3") {
         gl->wp->SetTimeCalib3(value == "true");
      } else if (item == "daqClkSrcSel") {
         if (iBoard == -1)
            for (auto &b: gl->wdb) {
               if (value == "true") {
                  b->SetDaqClkSrcSel(1);
                  sleep_ms(2000);
               } else {
                  b->SetExtClkFreq(80);
                  sleep_ms(2000);
                  b->SetDaqClkSrcSel(0);
                  sleep_ms(2000);
               }
            }
         else {
            if (value == "true") {
               gl->wdb[iBoard]->SetDaqClkSrcSel(1);
               sleep_ms(2000);
            } else {
               gl->wdb[iBoard]->SetExtClkFreq(80);
               sleep_ms(2000);
               gl->wdb[iBoard]->SetDaqClkSrcSel(0);
               sleep_ms(2000);
            }
         }
      } else if (item == "dacTriggerLevel") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetDacTriggerLevelV(iChannel, std::stof(value));
         else
            gl->wdb[iBoard]->SetDacTriggerLevelV(iChannel, std::stof(value));
      } else if (item == "triggerMode") {
         gl->triggerMode = (TRIGGERMODE) std::stoi(value);
         gl->wdb[iBoard]->SetDaqSoftTrigger(false);
      } else if (item == "triggerHoldoff") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetTriggerHoldoff(std::stof(value));
         else
            gl->wdb[iBoard]->SetTriggerHoldoff(std::stof(value));
      } else if (item == "triggerSource") {
         for (int i = 0; i < gl->wdb.size(); i++) {
            if (iChannel == -1 || i == iChannel) {
               if (value == "0") {
                  // internal trigger
                  gl->wdb[i]->SetExtAsyncTriggerEn(0);
                  gl->wdb[i]->SetPatternTriggerEn(1);
               } else {
                  // external trigger
                  gl->wdb[i]->SetExtAsyncTriggerEn(1);
                  gl->wdb[i]->SetPatternTriggerEn(0);
               }
            }
         }
      } else if (item == "triggerDelay") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetTriggerDelayNs(std::stoi(value));
         else
            gl->wdb[iBoard]->SetTriggerDelayNs(std::stoi(value));
      } else if (item == "triggerLeadTrailEdgeSel") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetLeadTrailEdgeSel(std::stoi(value));
         else
            gl->wdb[iBoard]->SetLeadTrailEdgeSel(std::stoi(value));
      } else if (item == "triggerSrcPolarity") {
         if (iBoard == -1)
            for (auto &b: gl->wdb) {
               b->SetTrgSrcPolarity(std::stoi(value));
            }
         else {
            gl->wdb[iBoard]->SetTrgSrcPolarity(std::stoi(value));
         }
      } else if (item == "triggerPtrnEn") {
         if (iBoard == -1)
            for (auto &b: gl->wdb) {
               b->SetTrgPtrnEn(std::stoi(value));
            }
         else {
            gl->wdb[iBoard]->SetTrgPtrnEn(std::stoi(value));
         }
      } else if (item == "triggerSrcEnPtrn") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetTrgSrcEnPtrn(iChannel, std::stoi(value));
         else
            gl->wdb[iBoard]->SetTrgSrcEnPtrn(iChannel, std::stoi(value));
      } else if (item == "triggerStatePtrn") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetTrgStatePtrn(iChannel, std::stoi(value));
         else
            gl->wdb[iBoard]->SetTrgStatePtrn(iChannel, std::stoi(value));
      } else if (item == "feGain") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetFeGain(iChannel, std::stof(value));
         else
            gl->wdb[iBoard]->SetFeGain(iChannel, std::stof(value));
      } else if (item == "fePzc") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetFePzc(iChannel, value == "true");
         else
            gl->wdb[iBoard]->SetFePzc(iChannel, value == "true");
      } else if (item == "dacPzcLevel") {
         assert(iBoard != -1);
         gl->wdb[iBoard]->SetDacPzcLevelN(std::stoi(value) - 1);
      } else if (item == "fePower") {
         if (iBoard == -1)
            for (auto &b: gl->wdb) {
               try {
                  b->SetFePower(value == "true");
                  if (std::stoi(value) == 1) {
                     for (int i = 0; i < 16; i++) {
                        b->SetFeAmp1Comp(i, 0);
                        b->SetFeAmp2Comp(i, 0);
                     }
                  }
               } catch(std::invalid_argument) {
                  // E board has not SetFePower
               }
            }
         else {
            try {
               gl->wdb[iBoard]->SetFePower(value == "true");
               if (value == "true") {
                  for (int i = 0; i < 16; i++) {
                     gl->wdb[iBoard]->SetFeAmp1Comp(i, 0);
                     gl->wdb[iBoard]->SetFeAmp2Comp(i, 0);
                  }
               }
            } catch(std::invalid_argument) {
               // E board has not SetFePower
            }
         }
      } else if (item == "range") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetRange(std::stof(value));
         else
            gl->wdb[iBoard]->SetRange(std::stof(value));
      } else if (item == "readoutSrcSel") {
         if (iBoard == -1)
            for (auto &b: gl->wdb) {
               if (std::stoi(value) == (int) cReadoutModeDRS) {
                  gl->readoutMode = cReadoutModeDRS;
                  b->SetDrsChTxEn(b->GetChnTxEn());
               } else if (std::stoi(value) == (int) cReadoutModeADC) {
                  gl->readoutMode = cReadoutModeADC;
                  b->SetAdcChTxEn(b->GetChnTxEn());
               } else {
                  gl->readoutMode = cReadoutModeTDC;
                  b->SetTdcChTxEn(b->GetChnTxEn());
               }
            }
         else {
            if (std::stoi(value) == (int) cReadoutModeDRS) {
               gl->readoutMode = cReadoutModeDRS;
               gl->wdb[iBoard]->SetDrsChTxEn(gl->wdb[iBoard]->GetChnTxEn());
            } else if (std::stoi(value) == (int) cReadoutModeADC) {
               gl->readoutMode = cReadoutModeADC;
               gl->wdb[iBoard]->SetAdcChTxEn(gl->wdb[iBoard]->GetChnTxEn());
            } else {
               gl->readoutMode = cReadoutModeTDC;
               gl->wdb[iBoard]->SetTdcChTxEn(gl->wdb[iBoard]->GetChnTxEn());
            }
         }
      } else if (item.find("readoutEnable") == 0) {
         std::string source = item.substr(13, 3);
         if (iBoard == -1)
            for (auto &b: gl->wdb) {
               if (source == "DRS") {
                  if (value == "true")
                     b->SetDrsChTxEn(b->GetChnTxEn());
                  else
                     b->SetDrsChTxEn(0);

               } else if (source == "ADC") {
                  if (value == "true")
                     b->SetAdcChTxEn(b->GetChnTxEn());
                  else
                     b->SetAdcChTxEn(0);

               } else if (source == "TDC") {
                  if (value == "true")
                     b->SetTdcChTxEn(b->GetChnTxEn());
                  else
                     b->SetTdcChTxEn(0);
               } else if (source == "TRG") {
                  if (value == "true")
                     b->SetTrgTxEn(1);
                  else
                     b->SetTrgTxEn(0);
               }
            }
         else {
            if (source == "DRS") {
               if (value == "true")
                  gl->wdb[iBoard]->SetDrsChTxEn(gl->wdb[iBoard]->GetChnTxEn());
               else
                  gl->wdb[iBoard]->SetDrsChTxEn(0);

            } else if (source == "ADC") {
               if (value == "true")
                  gl->wdb[iBoard]->SetAdcChTxEn(gl->wdb[iBoard]->GetChnTxEn());
               else
                  gl->wdb[iBoard]->SetAdcChTxEn(0);

            } else if (source == "TDC") {
               if (value == "true")
                  gl->wdb[iBoard]->SetTdcChTxEn(gl->wdb[iBoard]->GetChnTxEn());
               else
                  gl->wdb[iBoard]->SetTdcChTxEn(0);
            } else if (source == "TRG") {
               if (value == "true")
                  gl->wdb[iBoard]->SetTrgTxEn(1);
               else
                  gl->wdb[iBoard]->SetTrgTxEn(0);
            }
         }
      } else if (item == "calibBufferEnable") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetCalibBufferEn(value == "true");
         else
            gl->wdb[iBoard]->SetCalibBufferEn(value == "true");
      } else if (item == "timingCalibSignalEnable") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetSineWaveEnable(value == "true");
         else
            gl->wdb[iBoard]->SetSineWaveEnable(value == "true");
      } else if (item == "timingReferenceSignal") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetTimingReferenceSignal(std::stoi(value));
         else
            gl->wdb[iBoard]->SetTimingReferenceSignal(std::stoi(value));
      } else if (item == "feMux") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetFeMux(iChannel, value == "true" ? WDB::cFeMuxCalSource : WDB::cFeMuxInput);
         else
            gl->wdb[iBoard]->SetFeMux(iChannel, value == "true" ? WDB::cFeMuxCalSource : WDB::cFeMuxInput);
      } else if (item == "drsSampleFreq") {
         if (iBoard == -1)
            for (auto &b: gl->wdb) {
               b->SetDrsSampleFreq(std::stoi(value));
               b->LoadVoltageCalibration(b->GetDrsSampleFreqMhz(), gl->wdsDir);
               b->LoadTimeCalibration(b->GetDrsSampleFreqMhz(), gl->wdsDir);
               if (b->mVCalib.IsValid()) {
                  gl->wp->SetOfsCalib1(true);
                  gl->wp->SetOfsCalib2(true);
                  gl->wp->SetGainCalib(true);
                  gl->wp->SetRangeCalib(true);
               }
               if (b->mTCalib.IsValid()) {
                  gl->wp->SetTimeCalib1(true);
                  gl->wp->SetTimeCalib2(true);
                  gl->wp->SetTimeCalib3(true);
               }
            }
         else {
            gl->wdb[iBoard]->SetDrsSampleFreq(std::stoi(value));
            gl->wdb[iBoard]->LoadVoltageCalibration(gl->wdb[iBoard]->GetDrsSampleFreqMhz(), gl->wdsDir);
            gl->wdb[iBoard]->LoadTimeCalibration(gl->wdb[iBoard]->GetDrsSampleFreqMhz(), gl->wdsDir);

            if (gl->wdb[iBoard]->mVCalib.IsValid()) {
               gl->wp->SetOfsCalib1(true);
               gl->wp->SetOfsCalib2(true);
               gl->wp->SetGainCalib(true);
               gl->wp->SetRangeCalib(true);
            }
            if (gl->wdb[iBoard]->mTCalib.IsValid()) {
               gl->wp->SetTimeCalib1(true);
               gl->wp->SetTimeCalib2(true);
               gl->wp->SetTimeCalib3(true);
            }
         }
         demoDrsSampleFreq = std::stoi(value);
      } else if (item == "dacCalDc") {
         if (iBoard == -1)
            for (auto &b: gl->wdb)
               b->SetDacCalDcV(std::stof(value));
         else
            gl->wdb[iBoard]->SetDacCalDcV(std::stof(value));
      } else if (item == "hvTarget") {
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
      } else if (item == "tcalib") {
         if (!gl->demoMode)
            gl->wp->StartCalibrationTime(iBoard);
      } else if (item == "save") {
         if (value == "stop")
            gl->wp->StopLogging();
         else if (item != "") {
            auto a = split(value, '\n');
            gl->wp->StartWaveformSaving(std::string(s_http_server_opts.document_root) + "/" + a[0],
                                        a[1] == "bin" ? WP::cLiFormatBinary : WP::cLiFormatXML,
                                        a[2] == "all",
                                        a[2] == "all" ? -1 : std::stoi(a[2]),
                                        std::stoi(a[3]));
         }
      } else if (item == "reboot") {
         std::cout << "Reboot " << gl->wdb[iBoard]->GetName() << std::endl;
         auto b = gl->wdb[iBoard];
         b->ReconfigureFpga();
         sleep_ms(15000);
         std::cout << "Finished" << std::endl;

         b->Connect();
         b->ReceiveControlRegisters();
         b->ReceiveStatusRegisters();
         b->LoadVoltageCalibration(b->GetDrsSampleFreqMhz(), gl->wdsDir);
         b->LoadTimeCalibration(b->GetDrsSampleFreqMhz(), gl->wdsDir);

         b->SetDrsChTxEn(0xFFFF);
         b->SetChnTxEn(0xFFFF);
         gl->readoutMode = cReadoutModeDRS;

         // enable internal trigger if external trigger is not enabled
         if (!b->GetExtAsyncTriggerEn())
            b->SetPatternTriggerEn(1);

         // set destination port and set DAQ to "normal"
         b->SetDestinationPort(gl->wp->GetServerPort());
         b->SetDaqNormal(false);

      } else {
         std::cout << "Invalid command \"" << item << "\" received. Aborting." << std::endl;
         assert(0);
      }

      mg_printf(nc, "HTTP/1.1 204 No Content\r\n");
   }

   // gloabls
   if (http_event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/gl") == 0) {
      if (gl->verbose)
         std::cout << "Sending /gl to browser" << std::endl;

      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");

      mg_printf_http_chunk(nc, "{\n");
      mg_printf_http_chunk(nc, "   \"gl\": {\n");
      mg_printf_http_chunk(nc, "      \"demoMode\": %s,\n", gl->demoMode ? "true" : "false");
      mg_printf_http_chunk(nc, "      \"updatePeriodic\": %d,\n", gl->updatePeriodic);
      mg_printf_http_chunk(nc, "      \"nWdb\": %d\n", gl->wdb.size());
      mg_printf_http_chunk(nc, "   },\n");
      mg_printf_http_chunk(nc, "   \"wp\": {\n");
      mg_printf_http_chunk(nc, "      \"rotateWaveform\": %s,\n", gl->wp->IsRotateWaveform() ? "true" : "false");
      mg_printf_http_chunk(nc, "      \"ofsCalib1\": %s,\n", gl->wp->IsOfsCalib1() ? "true" : "false");
      mg_printf_http_chunk(nc, "      \"ofsCalib2\": %s,\n", gl->wp->IsOfsCalib2() ? "true" : "false");
      mg_printf_http_chunk(nc, "      \"gainCalib\": %s,\n", gl->wp->IsGainCalib() ? "true" : "false");
      mg_printf_http_chunk(nc, "      \"rangeCalib\": %s,\n", gl->wp->IsRangeCalib() ? "true" : "false");
      mg_printf_http_chunk(nc, "      \"timeCalib1\": %s,\n", gl->wp->IsTimeCalib1() ? "true" : "false");
      mg_printf_http_chunk(nc, "      \"timeCalib2\": %s,\n", gl->wp->IsTimeCalib2() ? "true" : "false");
      mg_printf_http_chunk(nc, "      \"timeCalib3\": %s\n", gl->wp->IsTimeCalib3() ? "true" : "false");
      mg_printf_http_chunk(nc, "   }\n");
      mg_printf_http_chunk(nc, "}\n");
      mg_send_http_chunk(nc, "", 0); // end of response
      return;
   }

   // boards
   if (http_event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/wdb") == 0) {
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

      for (int b = b1; b < b2; b++) {
         auto w = gl->wdb[b];

         // simulate gaussian distributed scalers in demo mode
         std::vector<uint64_t> scaler;
         if (gl->demoMode) {
            std::poisson_distribution<int> dist(1000);

            for (auto i = 0; i < 34; i++)
               scaler.push_back(dist(randomGenerator));
         } else
            w->GetScalers(scaler, false);

         // obtain HVs
         std::vector<float> hv_target;
         std::vector<float> hv_current;
         std::vector<float> hv_temp;
         float hv_base;
         if (gl->demoMode) {
            for (auto i = 0; i < 16; i++) {
               hv_target.push_back(0);
               hv_current.push_back(0);
            }
            for (auto i = 0; i < 4; i++) {
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
         mg_printf_http_chunk(nc, "      \"name\": \"%s\",\n", w->GetName().c_str());
         mg_printf_http_chunk(nc, "      \"address\": \"%s\",\n", w->GetEthAddrStr().c_str());
         mg_printf_http_chunk(nc, "      \"revision\": \"%c\",\n", 'A' + w->GetBoardRevision());
         mg_printf_http_chunk(nc, "      \"fwRevision\": \"%s\",\n", w->GetFwGitHashStr().c_str());
         mg_printf_http_chunk(nc, "      \"fwBuild\": \"%s\",\n", gl->demoMode ? "N/A" : w->GetFwBuild().c_str());
         mg_printf_http_chunk(nc, "      \"swRevision\": \"%s\",\n", w->GetSwGitHashStr().c_str());
         mg_printf_http_chunk(nc, "      \"swBuild\": \"%s\",\n", gl->demoMode ? "N/A" : w->GetSwBuild().c_str());
         mg_printf_http_chunk(nc, "      \"temperature\": %1.1lf,\n", w->GetTemperatureDegree(false));
         mg_printf_http_chunk(nc, "      \"sysBusy\": %s,\n", w->GetSysBusy() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"drsctrlBusy\": %s,\n", w->GetDrsCtrlBusy() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"packagerBusy\": %s,\n", w->GetPackagerBusy() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"hvBoardPlugged\": %s,\n", w->GetHvBoardPlugged() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"hvVersion\": \"%s\",\n", w->GetHvVersion().c_str());
         mg_printf_http_chunk(nc, "      \"backplanePlugged\": %s,\n", w->GetBackplanePlugged() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"pllLck\": %d,\n", w->GetPllLock(false));
         mg_printf_http_chunk(nc, "      \"drsSampleFreq\": %d,\n", gl->demoMode ?
                                                                    demoDrsSampleFreq : w->GetDrsSampleFreqMhz());
         mg_printf_http_chunk(nc, "      \"adcSampleFreq\": %d,\n", w->GetAdcSampleFreq() / 1000);
         mg_printf_http_chunk(nc, "      \"tdcSampleFreq\": %d,\n", w->GetTdcSampleFreq() / 1000);
         mg_printf_http_chunk(nc, "      \"compChannelStatus\": %d,\n", w->GetCompChStat());
         mg_printf_http_chunk(nc, "      \"eventTxRate\": %d,\n", w->GetEventTxRate());
         mg_printf_http_chunk(nc, "      \"lastEventNumber\": %d,\n", w->GetEventNumber());
         mg_printf_http_chunk(nc, "      \"triggerBusParityErrorCount\": %d,\n", w->GetTrbParityErrorCount());
         mg_printf_http_chunk(nc, "      \"triggerBusType\": %d,\n", w->GetTrbInfoLsb() & 0xFF); // ??
         mg_printf_http_chunk(nc, "      \"triggerBusNumber\": %d,\n", w->GetTrbInfoLsb() >> 8);   // ??
         mg_printf_http_chunk(nc, "      \"crateId\": %d,\n", w->GetCrateId());
         mg_printf_http_chunk(nc, "      \"slotId\": %d,\n", w->GetSlotId());
         mg_printf_http_chunk(nc, "      \"readoutSrcSel\": %d,\n", gl->readoutMode);
         mg_printf_http_chunk(nc, "      \"readoutEnable\": %d,\n", ((w->GetTrgTxEn() != 0) << 3)
                                                                    | ((w->GetTdcChTxEn() != 0) << 2)
                                                                    | ((w->GetAdcChTxEn() != 0) << 1)
                                                                    | (w->GetDrsChTxEn() != 0));
         mg_printf_http_chunk(nc, "      \"daqNormal\": %s,\n", w->GetDaqNormal() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"daqSingle\": %s,\n", w->GetDaqSingle() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"drs0TimingRefSel\": %d,\n", w->GetDrs0TimingRefSel());
         mg_printf_http_chunk(nc, "      \"drs1TimingRefSel\": %d,\n", w->GetDrs1TimingRefSel());
         mg_printf_http_chunk(nc, "      \"calibBufferEnable\": %s,\n", w->GetCalibBufferEn() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"timingCalibSignalEnable\": %d,\n", w->GetTimingCalibSignalEn());
         mg_printf_http_chunk(nc, "      \"timingReferenceSignal\": %d,\n", w->GetTimingReferenceSignal());
         mg_printf_http_chunk(nc, "      \"daqClkSrcSel\": %d,\n", w->GetDaqClkSrcSel());
         mg_printf_http_chunk(nc, "      \"extClkInSel\": %d,\n", w->GetExtClkInSel());
         mg_printf_http_chunk(nc, "      \"extClkFreq\": %d,\n", w->GetExtClkFreq());
         mg_printf_http_chunk(nc, "      \"localClkFreq\": %d,\n", w->GetLocalClkFreq());
         mg_printf_http_chunk(nc, "      \"calibClkFreq\": %d,\n", w->GetCalibClkFreq());
         mg_printf_http_chunk(nc, "      \"chnTxEn\": %d,\n", w->GetChnTxEn());

         mg_printf_http_chunk(nc, "      \"dacOfs\": %1.3f,\n", w->GetDacOfsV());
         mg_printf_http_chunk(nc, "      \"dacCalDc\": %1.3f,\n", w->GetDacCalDcV());
         mg_printf_http_chunk(nc, "      \"dacPzcLevel\": %d,\n", w->GetDacPzcLevelN());

         mg_printf_http_chunk(nc, "      \"dacTriggerLevel\": [\n");
         for (int i = 0; i < 15; i++)
            mg_printf_http_chunk(nc, "        %1.3f,\n", w->GetDacTriggerLevelV(i));
         mg_printf_http_chunk(nc, "        %1.3f ],\n", w->GetDacTriggerLevelV(15));

         mg_printf_http_chunk(nc, "      \"fePzc\": [\n");
         for (int i = 0; i < 15; i++)
            mg_printf_http_chunk(nc, "        %s,\n", w->GetFePzc(i) ? "true" : "false");
         mg_printf_http_chunk(nc, "        %s ],\n", w->GetFePzc(15) ? "true" : "false");

         mg_printf_http_chunk(nc, "      \"feGain\": [\n");
         for (int i = 0; i < 15; i++)
            mg_printf_http_chunk(nc, "        %1g,\n", w->GetFeGain(i));
         mg_printf_http_chunk(nc, "        %1g ],\n", w->GetFeGain(15));

         mg_printf_http_chunk(nc, "      \"feMux\": [\n");
         for (int i = 0; i < 15; i++)
            mg_printf_http_chunk(nc, "        %d,\n", w->GetFeMux(i));
         mg_printf_http_chunk(nc, "        %d ],\n", w->GetFeMux(15));

         try {
            mg_printf_http_chunk(nc, "      \"fePower\": %d,\n", w->GetFePower());
         } catch(std::invalid_argument &e) {
            mg_printf_http_chunk(nc, "      \"fePower\": -1,\n");
         }

         mg_printf_http_chunk(nc, "      \"triggerMode\": %d,\n", gl->triggerMode);
         mg_printf_http_chunk(nc, "      \"triggerHoldoff\": %d,\n", w->GetTriggerHoldoff());
         mg_printf_http_chunk(nc, "      \"triggerLeadTrailEdgeSel\": %d,\n", w->GetLeadTrailEdgeSel());
         mg_printf_http_chunk(nc, "      \"triggerExtTriggerOutEnable\": %s,\n",
                              w->GetExtTriggerOutEnable() ? "true" : "false");
         mg_printf_http_chunk(nc, "      \"triggerSource\": %d,\n", w->GetExtAsyncTriggerEn());
         mg_printf_http_chunk(nc, "      \"triggerOutPulseLength\": %d,\n", w->GetTriggerOutPulseLength());
         mg_printf_http_chunk(nc, "      \"triggerDelay\": %d,\n", w->GetTriggerDelayNs());
         mg_printf_http_chunk(nc, "      \"triggerSrcPolarity\": %d,\n", w->GetTrgSrcPolarity());
         mg_printf_http_chunk(nc, "      \"triggerAutoTriggerPeriod\": %d,\n", w->GetAutoTriggerPeriod());
         mg_printf_http_chunk(nc, "      \"triggerPtrnEn\": %d,\n", w->GetTrgPtrnEn());

         mg_printf_http_chunk(nc, "      \"triggerSrcEnPtrn\": [\n");
         for (int i = 0; i < 17; i++)
            mg_printf_http_chunk(nc, "        %d,\n", w->GetTrgSrcEnPtrn(i));
         mg_printf_http_chunk(nc, "        %d ],\n", w->GetTrgSrcEnPtrn(17));

         mg_printf_http_chunk(nc, "      \"triggerStatePtrn\": [\n");
         for (int i = 0; i < 17; i++)
            mg_printf_http_chunk(nc, "        %d,\n", w->GetTrgStatePtrn(i));
         mg_printf_http_chunk(nc, "        %d ],\n", w->GetTrgStatePtrn(17));

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
         mg_printf_http_chunk(nc, "        \"temperature1Wire\": [\n");
         for (auto &s: hv_temp) {
            if (&s != &hv_temp.back())
               mg_printf_http_chunk(nc, "            %g,\n", s);
            else
               mg_printf_http_chunk(nc, "            %g],\n", s);
         }
         mg_printf_http_chunk(nc, "        \"baseVoltage\": %g\n\n", hv_base);

         mg_printf_http_chunk(nc, "      }\n");

         if (b == b2 - 1)
            mg_printf_http_chunk(nc, "    }\n");
         else
            mg_printf_http_chunk(nc, "    },\n");
      }

      mg_printf_http_chunk(nc, "  ]\n");
      mg_printf_http_chunk(nc, "}\n");
      mg_send_http_chunk(nc, "", 0);
   }

   // software build
   if (http_event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/build") == 0) {
      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");
      mg_printf_http_chunk(nc, "{\n");
      mg_printf_http_chunk(nc, "   \"build\": \"%s\"\n", __DATE__);
      mg_printf_http_chunk(nc, "}\n");
      mg_send_http_chunk(nc, "", 0);
      return;
   }

   // binary encoded waveforms
   if (http_event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/wf") == 0) {

      mg_get_http_var(&hm->query_string, "b", str, sizeof(str));
      int brd = atoi(str);

      mg_get_http_var(&hm->query_string, "c", str, sizeof(str));
      int chn = atoi(str);

      mg_send_response_line(nc, 200, "Content-Type: application/octet-stream\r\nTransfer-Encoding: chunked\r\n");

      // return progress if in voltage calibration mode
      if (gl->wp->IsVcalibActive()) {
         int t = 10;    // array type
         mg_send_http_chunk(nc, (const char *) &t, 4);

         int vcb = gl->wp->GetVcalibBoard();
         mg_send_http_chunk(nc, (const char *) &vcb, 4);

         float f = gl->wp->GetVcalibProgress();
         mg_send_http_chunk(nc, (const char *) &f, 4);

         mg_send_http_chunk(nc, "", 0);
         return;
      }

      // return error code from time calibration
      if (gl->wp->IsTcalibError()) {
         gl->wp->ClearTcalibError();

         int t = 12;    // array type indicating error
         mg_send_http_chunk(nc, (const char *) &t, 4);

         int tcb = gl->wp->GetTcalibBoard();
         mg_send_http_chunk(nc, (const char *) &tcb, 4);

         mg_send_http_chunk(nc, "", 0);
         return;

      }

      // return progress and period in time calibration mode
      if (gl->wp->IsTcalibActive()) {
         int t = 11;    // array type
         mg_send_http_chunk(nc, (const char *) &t, 4);

         int tcb = gl->wp->GetTcalibBoard();
         mg_send_http_chunk(nc, (const char *) &tcb, 4);

         float f = gl->wp->GetTcalibProgress();
         mg_send_http_chunk(nc, (const char *) &f, 4);

         for (int c = 0; c < WD_N_CHANNELS; c++)
            if (chn & (1 << c)) {
               int n = 1024;
               mg_send_http_chunk(nc, (const char *) &c, 4);
               mg_send_http_chunk(nc, (const char *) &n, 4);

               mg_send_http_chunk(nc, (const char *) gl->wdb[brd]->mTCalib.mCalib.period[c], sizeof(float) * n);
            }

         mg_send_http_chunk(nc, "", 0);
         return;
      }

      // avoid invalid board index
      if (brd < 0 || brd >= gl->wdb.size())
         brd = 0;

      WDEvent event(gl->wdb[brd]->GetSerialNumber());
      bool bNewEvent;

      if (gl->demoMode) {
         bNewEvent = true;
         event.mVCalibrated = true;
         event.mTCalibrated = true;
         if (gl->readoutMode == cReadoutModeDRS) {
            event.mTypeValid[cDataTypeDRS] = true;
            for (int c = 0; c < WD_N_CHANNELS; c++) {
               for (int i = 0; i < 1024; i++) {
                  float t = i * 1E-6 / demoDrsSampleFreq;
                  event.mWfTDRS[c][i] = t;
                  event.mWfUDRS[c][i] = (float) (sin(M_PI * 2 * 100E6 * t + c / 8.0) / 2 +
                                                 ((float) random() / RAND_MAX - 0.5) / 300);
               }
               // add spikes
               for (int i = 0; i < 1024; i++) {
                  if ((float) random() / RAND_MAX < 0.00005) {
                     float s = ((float) random() / RAND_MAX - 0.5) / 5;
                     int j = i - 5;
                     float f;
                     for (f = 0; f < 1; f += 0.2, j++)
                        if (j >= 0 && j < 1024)
                           event.mWfUDRS[c][j] += s * f;
                     for (f = 1; f > 0; f -= 0.2, j++)
                        if (j >= 0 && j < 1024)
                           event.mWfUDRS[c][j] += s * f;
                  }
               }
            }
         }
      } else {

         // request single event
         if (brd == -1) {
            // all boards
            gl->wp->RequestAllBoards();

            for (auto &b: gl->wdb) {
               if (gl->triggerMode == cTriggerModeAuto)
                  b->TriggerSoftEvent();
               else if (gl->triggerMode == cTriggerModeNormal)
                  b->SetDaqSingle(1);
            }
         } else {
            // only current board
            gl->wp->RequestSingleBoard(gl->wdb[brd]);

            if (gl->triggerMode == cTriggerModeAuto)
               gl->wdb[brd]->TriggerSoftEvent();
            else if (gl->triggerMode == cTriggerModeNormal) {
               if (!gl->triggerSelfArm) {
                  sleep_ms(gl->wdb[brd]->GetTriggerHoldoff());
                  gl->wdb[brd]->SetDaqSingle(1);
               }
            }
         }

         // read waveforms
         if (gl->wp->IsXMLLogging())
            // increase timeout for slow XML logging
            bNewEvent = gl->wp->GetLastEvent(gl->wdb[brd], 5000, event);
         else
            bNewEvent = gl->wp->GetLastEvent(gl->wdb[brd], 500, event);
      }

      if (gl->demoMode)
         brd = 0xFF; // signals demo data

      if (bNewEvent) {
         if (event.mTypeValid[cDataTypeADC] && gl->readoutMode == cReadoutModeADC) { //---- ADC waveforms
            int t;                        // array type
            int n = 1024;                 // number of elements
            int vc = event.mVCalibrated;  // voltage calibrated
            int tc = event.mTCalibrated;  // time calibrated
            int l = gl->wp->GetNLogged(); // number of logged events
            for (int c = 0; c < WD_N_CHANNELS; c++) {
               if (chn & (1 << c)) {
                  t = 1; // time array
                  mg_send_http_chunk(nc, (const char *) &t, 4);
                  mg_send_http_chunk(nc, (const char *) &brd, 4);
                  mg_send_http_chunk(nc, (const char *) &tc, 4);
                  mg_send_http_chunk(nc, (const char *) &l, 4);
                  mg_send_http_chunk(nc, (const char *) &c, 4);
                  mg_send_http_chunk(nc, (const char *) &n, 4);
                  mg_send_http_chunk(nc, (const char *) &event.mWfTADC[c][0], sizeof(float) * n);
               }
            }

            for (int c = 0; c < WD_N_CHANNELS; c++) {
               if (chn & (1 << c)) {
                  t = 2; // voltage array
                  mg_send_http_chunk(nc, (const char *) &t, 4);
                  mg_send_http_chunk(nc, (const char *) &brd, 4);
                  mg_send_http_chunk(nc, (const char *) &vc, 4);
                  mg_send_http_chunk(nc, (const char *) &l, 4);
                  mg_send_http_chunk(nc, (const char *) &c, 4);
                  mg_send_http_chunk(nc, (const char *) &n, 4);
                  mg_send_http_chunk(nc, (const char *) &event.mWfUADC[c][1024], sizeof(float) * n);
               }
            }
         } else if (event.mTypeValid[cDataTypeTDC] && gl->readoutMode == cReadoutModeTDC) { //---- TDC waveforms
            int t;                        // array type
            int n = 512 * 8;              // number of elements
            int vc = event.mVCalibrated;  // voltage calibrated
            int tc = event.mTCalibrated;  // time calibrated
            int l = gl->wp->GetNLogged(); // number of logged events
            float time[512 * 8];
            for (int i = 0; i < 512 * 8; i++) {
               time[i] = i * 1.56e-9;
            }
            for (int c = 0; c < WD_N_CHANNELS; c++) {
               if (chn & (1 << c)) {
                  t = 1; // time array
                  mg_send_http_chunk(nc, (const char *) &t, 4);
                  mg_send_http_chunk(nc, (const char *) &brd, 4);
                  mg_send_http_chunk(nc, (const char *) &tc, 4);
                  mg_send_http_chunk(nc, (const char *) &l, 4);
                  mg_send_http_chunk(nc, (const char *) &c, 4);
                  mg_send_http_chunk(nc, (const char *) &n, 4);
                  mg_send_http_chunk(nc, (const char *) &time[0], sizeof(float) * n);
               }
            }
            for (int c = 0; c < WD_N_CHANNELS; c++) {
               if (chn & (1 << c)) {
                  t = 3; // bit value array
                  mg_send_http_chunk(nc, (const char *) &t, 4);
                  mg_send_http_chunk(nc, (const char *) &brd, 4);
                  mg_send_http_chunk(nc, (const char *) &vc, 4);
                  mg_send_http_chunk(nc, (const char *) &l, 4);
                  mg_send_http_chunk(nc, (const char *) &c, 4);
                  mg_send_http_chunk(nc, (const char *) &n, 4);
                  unsigned char ampl[512 * 8];
                  for (int i = 0; i < 512; i++) {
                     unsigned char binval = event.mWfTDC[c][i];
                     for (int j = 0; j < 8; j++) {
                        ampl[8 * i + 7 - j] = (binval & (1 << j)) ? 1 : 0;
                     }
                  }
                  mg_send_http_chunk(nc, (const char *) &ampl[0], sizeof(unsigned char) * n);
               }
            }
         } else if (event.mTypeValid[cDataTypeDRS] && gl->readoutMode == cReadoutModeDRS) { //---- DRS waveforms
            int t;                        // array type
            int n = 1024;                 // number of elements
            int vc = event.mVCalibrated;  // voltage calibrated
            int tc = event.mTCalibrated;  // time calibrated
            int l = gl->wp->GetNLogged(); // number of logged events
            for (int c = 0; c < WD_N_CHANNELS; c++) {
               if (chn & (1 << c)) {
                  t = 1; // time array
                  mg_send_http_chunk(nc, (const char *) &t, 4);
                  mg_send_http_chunk(nc, (const char *) &brd, 4);
                  mg_send_http_chunk(nc, (const char *) &tc, 4);
                  mg_send_http_chunk(nc, (const char *) &l, 4);
                  mg_send_http_chunk(nc, (const char *) &c, 4);
                  mg_send_http_chunk(nc, (const char *) &n, 4);
                  mg_send_http_chunk(nc, (const char *) event.mWfTDRS[c], sizeof(float) * n);
               }
            }

            for (int c = 0; c < WD_N_CHANNELS; c++) {
               if (chn & (1 << c)) {
                  t = 2; // voltage array
                  mg_send_http_chunk(nc, (const char *) &t, 4);
                  mg_send_http_chunk(nc, (const char *) &brd, 4);
                  mg_send_http_chunk(nc, (const char *) &vc, 4);
                  mg_send_http_chunk(nc, (const char *) &l, 4);
                  mg_send_http_chunk(nc, (const char *) &c, 4);
                  mg_send_http_chunk(nc, (const char *) &n, 4);
                  mg_send_http_chunk(nc, (const char *) event.mWfUDRS[c], sizeof(float) * n);
               }
            }
         }

      } else {
         // just return idle message
         int t = 0;
         mg_send_http_chunk(nc, (const char *) &t, 4);
         mg_send_http_chunk(nc, (const char *) &brd, 4);
         if (gl->verbose)
            printf("Idle\n");
      }

      mg_send_http_chunk(nc, "", 0);

      return;
   }

   // file serving
   if (http_event == MG_EV_HTTP_REQUEST) {
      mg_serve_http(nc, hm, s_http_server_opts);
   }

}

/*------------------------------------------------------------------*/

void showUsage(std::string name) {
   if (name.find("/") != std::string::npos)
      name = name.substr(name.rfind("/") + 1); // strip path

   std::cerr << "usage: " << name << " [options] [-w <address> [-w <address> ...]]" << std::endl;
   std::cerr << "valid options:" << std::endl;
   std::cerr << "  -demo           Demo mode" << std::endl;
   std::cerr << "  -g rx tx        Debug output at RX/TX ports" << std::endl;
   std::cerr << "  -h              Show this help" << std::endl;
   std::cerr << "  -l <logfile>    Log file for debugging" << std::endl;
   std::cerr << "  -p              HTTP server port (default is 8080)" << std::endl;
   std::cerr << "  -r              Reset all PLLs" << std::endl;
   std::cerr << "  -s              Run WDB in self-arm mode (use with caution!)" << std::endl;
   std::cerr << "  -u              Retrieve WDB regs once per second to capture changes by other control programs"
             << std::endl;
   std::cerr << "  -v 1            Print extra information (verbose)" << std::endl;
   std::cerr << "  -v 2            Print each received waveform packet header" << std::endl;
   std::cerr << "  -w <address>    Address(es) of WaveDREAM board(s) in the form" << std::endl;
   std::cerr << "     wd<nnn>      IP address of board wd<nnn>" << std::endl;
   std::cerr << "     nnn          Number of board wd<nnn>" << std::endl;
   std::cerr << "     dcb<nn>:<mm> Board in slot <mm> controlled by dcb<nn>" << std::endl;
   std::cerr << "     dcb<nn>:*    All boards controlled by dcb<nn>" << std::endl;
   std::cerr << "     dcb<nn>      All boards controlled by dcb<nn>" << std::endl;
   std::cerr << "                  multiple -w <> -w <> flags are possible" << std::endl;
}

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

int main(int argc, const char *argv[]) {
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
   gl.updatePeriodic = false;
   gl.dbgRx = gl.dbgTx = 0;
   gl.wdsDir = "";

   // find wds directory
   char tmp[256];
   getcwd(tmp, sizeof(tmp));
   std::string dir(tmp);
   std::ifstream f1(dir + "/html/index.html");
   if (f1.good()) {
      gl.wdsDir = dir;
   } else {
      if (getenv("WDBSYS")) {
         std::ifstream f3(std::string(getenv("WDBSYS")) + "/sw/wds/html/index.html");
         if (f3.good()) {
            gl.wdsDir = std::string(getenv("WDBSYS")) + "/sw/wds";
         } else {
            std::cerr << "Cannot find 'html' directory. Please corret 'WDBSYS' environment variable." << std::endl;
            std::cerr << "WDBSYS currently points to '" << getenv("WDBSYS") << "'" <<std::endl;
            return 1;
         }
      } else {
         std::cerr << "Cannot find 'WDBSYS' environment variable. Please set it to the wavedaq_main directory." << std::endl;
         return 1;
      }
   }

   // parse command line parameters
   if (argc < 2) {
      showUsage(argv[0]);
      return 1;
   }

   for (int i = 1; i < argc; i++) {
      std::string arg = argv[i];
      if (arg == "-h" || arg == "-help" || arg == "--help") {
         showUsage(argv[0]);
         return 0;
      } else if (arg == "-demo")
         gl.demoMode = true;

      else if (arg == "-p")
         gl.serverPort = std::stoi(argv[++i]);

      else if (arg == "-g") {
         gl.dbgRx = std::stoi(argv[++i]);
         gl.dbgTx = std::stoi(argv[++i]);
      } else if (arg == "-l")
         gl.logFileName = std::string(argv[++i]);

      else if (arg == "-r")
         gl.reset = true;

      else if (arg == "-s")
         gl.triggerSelfArm = true;

      else if (arg == "-u")
         gl.updatePeriodic = true;

      else if (arg == "-v") {
         gl.verbose = 1;
         if (i < argc - 1 && isdigit(argv[i + 1][0]))
            gl.verbose = std::stoi(argv[++i]);
      } else if (arg == "-t")
         gl.specialTest = true;

      else if (arg == "-w") {

         if (i + 1 == argc) {
            showUsage(argv[0]);
            return 0;
         }
         std::string b = argv[i + 1];
         if (isdigit(b.at(0)) && b.find('.') == std::string::npos) {
            if (b.find('-') != std::string::npos) {
               int i1 = std::stoi(b);
               int i2 = std::stoi(b.substr(b.find('-') + 1));
               if (i1 >= 0 && i1 < 1000 && i2 > 0 && i2 < 1000) {
                  for (int j = i1; j <= i2; j++) {
                     std::ostringstream name;
                     name << "wd" << std::setfill('0') << std::setw(3) << j;
                     gl.wdb.push_back(new WDB(name.str()));
                  }
               } else {
                  std::cerr << "invalid argument \"-w " << b << "\"" << std::endl;
                  return 1;
               }
            } else {
               if (argc > i + 1 && isdigit(argv[i + 1][0])) {
                  while (argc > i + 1 && isdigit(argv[i + 1][0])) {
                     std::ostringstream name;
                     name << "wd" << std::setfill('0') << std::setw(3) << std::stoi(argv[i + 1]);
                     gl.wdb.push_back(new WDB(name.str()));
                     i++;
                  }
                  continue;
               }
            }
         } else {
            std::for_each(b.begin(), b.end(), [](char &c) {
               c = ::toupper(c);
            });

            if (b.substr(0, 3) == "DCB") {
               try {
                  DCB *dcb;
                  if (b.find(':')) {
                     std::cout << "Connect to " << b.substr(0, b.find(':')) << " ... " << std::flush;
                     dcb = new DCB(b.substr(0, b.find(':')), gl.verbose);
                  } else {
                     std::cout << "Connect to " << b << " ... " << std::flush;
                     dcb = new DCB(b, gl.verbose);
                  }
                  dcb->Connect();
                  dcb->ScanCrate();
                  if (gl.verbose) {
                     std::cout << std::endl << "========== DCB Info ==========" << std::endl;
                     dcb->PrintVersion();
                     std::cout << std::endl << "Board scan:" << std::endl;
                     dcb->PrintCrate();
                     std::cout << std::endl;
                  }
                  gl.dcb.push_back(dcb);

                  if (b.find(':') == std::string::npos || b.find('*') != std::string::npos) {
                     for (int j=0 ; j<16 ; j++) {
                        if (dcb->GetBoardId(j)->type_id == BRD_TYPE_ID_WDB) {
                           gl.wdb.push_back(new WDB(dcb, j, gl.verbose));
                        }
                     }
                  } else {
                     gl.wdb.push_back(new WDB(dcb, std::stoi(b.substr(b.find(':')+1)), gl.verbose));
                  }
               } catch (std::runtime_error &e) {
                  std::cout << std::endl;
                  std::cout << e.what() << std::endl;
                  std::cout << "Aborting." << std::endl;
                  return 1;
               }
               std::cout << "OK" << std::endl;
               if (gl.verbose)
                  std::cout << std::endl;

            } else
               gl.wdb.push_back(new WDB(b));
         }
         i++;

      } else if (arg == "-d") {

         if (i + 3 > argc) {
            showUsage(argv[0]);
            return 0;
         }
         std::string name = argv[i + 1];
         if (isdigit(name.c_str()[0]))
            name = std::string("dcb") + argv[i + 1];

         if (!isdigit(argv[i + 2][0])) {
            showUsage(argv[0]);
            return 0;
         }
         int slot = std::stoi(argv[i + 2]);
         gl.wdb.push_back(new WDB(name, slot));

         i += 2;

      } else {
         showUsage(argv[0]);
         return 1;
      }
   }

   if (gl.demoMode) {
      gl.wdb.clear();
      gl.wdb.push_back(new WDB("demo"));
      gl.readoutMode = cReadoutModeDRS;
   }

   if (gl.wdb.empty()) {
      std::cerr << "You have to specify at least one WaveDREAM board via the \"-w\" or the \"-d\" option." << std::endl;
      return 1;
   }

   // connect to all WDB and retrieve registers
   for (auto &b: gl.wdb) {
      std::cout << "Connect to " << b->GetAddr() << " ... " << std::flush;
      try {
         if (!gl.demoMode) {
            b->SetVerbose(gl.verbose);
            b->SetLogFile(gl.logFileName);
            b->Connect();
            b->ReceiveStatusRegisters();
            b->ReceiveControlRegisters();
            if (gl.verbose) {
               std::cout << std::endl << "========== WDB Info ==========" << std::endl;
               b->PrintVersion();
            }

            // load calibration data for board
            b->LoadVoltageCalibration(b->GetDrsSampleFreqMhz(), gl.wdsDir);
            b->LoadTimeCalibration(b->GetDrsSampleFreqMhz(), gl.wdsDir);

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
            if (b->GetPllLock(false) != 0x1FF) {
               std::ostringstream str;
               str << "PLL not locked on board " << b->GetAddr() << ". Mask = 0x" << std::hex << b->GetPllLock(false);
               throw std::runtime_error(str.str());
            }

            if (b->GetDrsChTxEn() > 0) {
               gl.readoutMode = cReadoutModeDRS;
               b->SetChnTxEn(b->GetDrsChTxEn());
            } else if (b->GetAdcChTxEn() > 0) {
               gl.readoutMode = cReadoutModeADC;
               b->SetChnTxEn(b->GetAdcChTxEn());
            } else if (b->GetTdcChTxEn() > 0) {
               gl.readoutMode = cReadoutModeTDC;
               b->SetChnTxEn(b->GetTdcChTxEn());
            } else {
               b->SetDrsChTxEn(0xFFFF);
               b->SetChnTxEn(0xFFFF);
               gl.readoutMode = cReadoutModeDRS;
            }

            // enable internal trigger if external trigger is not enabled
            if (!b->GetExtAsyncTriggerEn())
               b->SetPatternTriggerEn(1);

            // disable scaler readout
            b->SetSclTxEn(0);

         } else {
            b->Connect();

            // turn all channels on in demo mode
            b->SetDrsChTxEn(0xFFFF);
            b->SetChnTxEn(0xFFFF);
         }
      } catch (std::runtime_error &e) {
         std::cout << std::endl;
         std::cout << e.what() << std::endl;
         std::cout << "Aborting." << std::endl;
         return 1;
      }
      std::cout << "OK" << std::endl;
      if (gl.verbose)
         std::cout << std::endl;
   }

   if (gl.reset) {
      std::cout << "All PLLs reset" << std::endl;
      return 0;
   }
   // instantiate waveform processor
   gl.wp = new WP(gl.wdb, gl.verbose, gl.wdsDir, gl.logFileName, gl.demoMode);
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
      std::cerr << "Cannot bind to port " << gl.serverPort << ". Probably other server is already running."
                << std::endl;
      return 1;
   }

   mg_set_protocol_http_websocket(con);
   s_http_server_opts.dav_auth_file = "-";     // Allow access via WebDav
   s_http_server_opts.enable_directory_listing = "yes";

   // set document_root
   std::string d(gl.wdsDir + "/html");
   s_http_server_opts.document_root = d.c_str();

   std::cout << "GIT revision: " << getWdbLibRevision() << std::endl;
   std::cout << "Starting HTTP server at port " << gl.serverPort << std::endl;

   if (gl.demoMode)
      std::cout << "Starting in DEMO mode." << std::endl;

   time_t last = 0, now;

   try {
      while (true) {

         // do calibration if asked for
         if (gl.wp->IsVcalibActive()) {
            gl.wp->DoVoltageCalibrationStep();

            // Yield to server, no timeout
            mg_mgr_poll(&mgr, 0);

         } else if (gl.wp->IsTcalibActive()) {
            gl.wp->DoTimeCalibrationStep();

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

            // cycle phase of sine wave
            //static int delay = 0;
            //for (auto &b: gl.wdb)
            //   b->SetSineWaveDelay(delay);
            //delay = (delay == 16) ? -16 : delay + 1;

            last = now;
         }

      }
   } catch (std::runtime_error &e) {
      std::cout << std::endl;
      std::cout << e.what() << std::endl;
      std::cout << "Aborting." << std::endl;

      return 1;
   }

   return 0;
}

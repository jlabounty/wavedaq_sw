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
   std::vector<WDB *> wdb;
   std::vector<DCB *> dcb;
   WP *wp;
   TRIGGERMODE triggerMode;
   int triggerSelfArm;
   READOUTMODE readoutMode;
   bool updatePeriodic;
   std::string wdsDir;
   std::map<std::string, time_t> recent;
} GLOBALS;

unsigned int demoDrsSampleFreq = 5016;

std::vector<std::string> split(const std::string &input, char separator);
void connectWDB(GLOBALS *gl, WDB *b);
void connectDCB(GLOBALS *gl, DCB *d);

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

DCB *get_dcb_from_query(const struct mg_str *buf, GLOBALS *gl) {
   char str[256];
   mg_get_http_var(buf, "adr", str, sizeof(str));
   auto adr = std::string(str);
   for (auto &c: adr) c = toupper(c);

   DCB *dcb = nullptr;
   for (auto &d : gl->dcb) {
      if (d->GetName() == std::string(adr)) {
         dcb = d;
         break;
      }
   }

   return dcb;
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
      std::string wdbAddress;
      int iChannel = -1;

      // get parameters from URI in the format /<item>/<board>/<channel>
      if (hm->uri.p) {
         uri = split(std::string(hm->uri.p), ' ')[0];
         args = split(uri, '/');
         if (args.size() > 1)
            item = args[1];
         if (args.size() > 2) {
            wdbAddress = std::string(args[2]);
         }
         if (args.size() > 3)
            iChannel = std::stoi(args[3]);
      }
      if (hm->body.p)
         value = std::string(hm->body.p, hm->body.len);

      // search board in list
      for (auto &c: wdbAddress) c = toupper(c);
      std::vector<WDB *> wdbList;
      for (auto &wdb: gl->wdb) {
         if (wdbAddress == std::string("ALL") || wdb->GetAddr() == wdbAddress) {
            wdbList.push_back(wdb);
         }
      }

      if (wdbList.size() == 0) {
         std::cout << "Received item " << item
                   << ", value " << value
                   << ", channel " << iChannel
                   << " from browser for invalid board \"" << wdbAddress << "\""
                   << std::endl;
         return;
      }

      if (gl->verbose)
         std::cout << "Received item \"" << item
                   << "\", value \"" << value
                   << "\", board \"" << wdbAddress
                   << "\", channel " << iChannel
                   << std::endl;

      if (item == "enableChannel") {
         // bits0-15 normal DRS channels bit16: clock0, bit17: clock1
         auto mask = std::stoi(value);
         for (auto &b: wdbList) {
            b->SetChnTxEn(mask);
            if (b->GetAdcChTxEn() != 0 || gl->readoutMode == cReadoutModeADC) b->SetAdcChTxEn(mask);
            if (b->GetTdcChTxEn() != 0 || gl->readoutMode == cReadoutModeTDC) b->SetTdcChTxEn(mask);
            if (b->GetDrsChTxEn() != 0 || gl->readoutMode == cReadoutModeDRS) b->SetDrsChTxEn(mask);
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
         for (auto &b: wdbList) {
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
      } else if (item == "dacTriggerLevel") {
         for (auto &b: wdbList)
            b->SetDacTriggerLevelV(iChannel, std::stof(value));
      } else if (item == "triggerMode") {
         gl->triggerMode = (TRIGGERMODE) std::stoi(value);
         for (auto &b: wdbList)
            b->SetDaqSoftTrigger(false);
      } else if (item == "triggerHoldoff") {
         for (auto &b: wdbList)
            b->SetTriggerHoldoff(std::stof(value));
      } else if (item == "triggerSource") {
         for (auto &b: wdbList) {
            if (value == "0") {
               // internal trigger
               b->SetExtAsyncTriggerEn(0);
               b->SetPatternTriggerEn(1);
            } else {
               // external trigger
               b->SetExtAsyncTriggerEn(1);
               b->SetPatternTriggerEn(0);
            }
         }
      } else if (item == "triggerDelay") {
         for (auto &b: wdbList)
            b->SetTriggerDelayNs(std::stoi(value));
      } else if (item == "triggerOutPulseLength") {
         for (auto &b: wdbList)
            b->SetTriggerOutPulseLength(std::stoi(value));
      } else if (item == "triggerLeadTrailEdgeSel") {
         for (auto &b: wdbList)
            b->SetLeadTrailEdgeSel(std::stoi(value));
      } else if (item == "triggerSrcPolarity") {
         for (auto &b: wdbList)
            b->SetTrgSrcPolarity(std::stoi(value));
      } else if (item == "triggerPtrnEn") {
         for (auto &b: wdbList)
            b->SetTrgPtrnEn(std::stoi(value));
      } else if (item == "triggerSrcEnPtrn") {
         for (auto &b: wdbList)
            b->SetTrgSrcEnPtrn(iChannel, std::stoi(value));
      } else if (item == "triggerStatePtrn") {
         for (auto &b: wdbList)
            b->SetTrgStatePtrn(iChannel, std::stoi(value));
      } else if (item == "feGain") {
         for (auto &b: wdbList)
            b->SetFeGain(iChannel, std::stof(value));
      } else if (item == "fePzc") {
         for (auto &b: wdbList)
            b->SetFePzc(iChannel, value == "true");
      } else if (item == "dacPzcLevel") {
         for (auto &b: wdbList)
            b->SetDacPzcLevelN(std::stoi(value) - 1);
      } else if (item == "fePower") {
         for (auto &b: wdbList) {
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
      } else if (item == "range") {
         for (auto &b: wdbList)
            b->SetRange(std::stof(value));
      } else if (item == "readoutSrcSel") {
         for (auto &b: wdbList) {
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
      } else if (item.find("readoutEnable") == 0) {
         std::string source = item.substr(13, 3);
         for (auto &b: wdbList) {
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
      } else if (item == "calibBufferEnable") {
         for (auto &b: wdbList)
            b->SetCalibBufferEn(value == "true");
      } else if (item == "timingCalibSignalEnable") {
         for (auto &b: wdbList)
            b->SetSineWaveEnable(value == "true");
      } else if (item == "timingReferenceSignal") {
         for (auto &b: wdbList)
            b->SetTimingReferenceSignal(std::stoi(value));
      } else if (item == "feMux") {
         for (auto &b: wdbList)
            b->SetFeMux(iChannel, value == "true" ? WDB::cFeMuxCalSource : WDB::cFeMuxInput);
      } else if (item == "drsSampleFreq") {
         for (auto &b: wdbList) {
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
         demoDrsSampleFreq = std::stoi(value);
      } else if (item == "dacCalDc") {
         for (auto &b: wdbList)
            b->SetDacCalDcV(std::stof(value));
      } else if (item == "hvTarget") {
         for (auto &b: wdbList)
            b->SetHVTarget(iChannel, std::stof(value));
      } else if (item == "resetPLL") {
         // reset PLLs
         for (auto &b: wdbList) {
            b->SetDrsSampleFreq(std::stoi(value));
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
      } else if (item == "debugOutput") {
         // set debug output on front-panel MCX
         for (auto &b: wdbList) {
            b->SetMcxRxSigSel(1);
            b->SetMcxTxSigSel(1);
         }
      }

      //---------- commands ----------
      else if (item == "vcalib") {
         if (!gl->demoMode)
            gl->wp->StartCalibrationVoltage(0);
      } else if (item == "tcalib") {
         if (!gl->demoMode)
            gl->wp->StartCalibrationTime(0);
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
         for (auto &b: wdbList) {
            std::cout << "Reboot " << b->GetAddr() << std::endl;

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
            if (b->IsDcbInterface()) {
               //reconfigure full crate through DCB
               b->GetDcbInterface()->SetDestinationPort(gl->wp->GetServerPort());
            } else {
               b->SetDestinationPort(gl->wp->GetServerPort());
            }

            b->SetDaqNormal(false);
         }

      } else {
         std::cout << "Invalid command \"" << item << "\" received. Aborting." << std::endl;
         assert(0);
      }

      mg_printf(nc, "HTTP/1.1 204 No Content\r\n");
      return;
   }

   // globals
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

   if (http_event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/connect") == 0) {
      char str[256];
      mg_get_http_var(&hm->query_string, "adr", str, sizeof(str));
      auto adr = std::string(str);
      for (auto &c: adr) c = toupper(c);

      if (gl->verbose)
         std::cout << "Trying to connect to " << adr << std::endl;

      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");

      if (adr[0] == 'W') {
         WDB *wdb = nullptr;
         int i = 0;
         for (auto &b: gl->wdb) {
            // check if we are already connected
            if (std::string(adr) == b->GetAddr()) {
               wdb = b;
               if (wdb->Ping()) {
                  if (gl->verbose)
                     std::cout << "OK" << std::endl;
                  mg_printf_http_chunk(nc, "OK\n");
               } else {
                  // delete board from gl->wdb
                  gl->wdb.erase(gl->wdb.begin()+i);
                  std::string s = std::string("Cannot connect to board ") + adr;
                  mg_printf_http_chunk(nc, "%s\n", s.c_str());
               }
               break;
            }
            i++;
         }

         if (wdb == nullptr) {
            // create new board
            wdb = new WDB(adr, gl->verbose);
            try {
               std::cout << "Connect to " << wdb->GetAddr() << " ... " << std::flush;
               connectWDB(gl, wdb);
               gl->wdb.push_back(wdb);
               gl->wp->SetWDBList(gl->wdb);
               mg_printf_http_chunk(nc, "OK\n");
               std::cout << "OK" << std::endl;
            } catch (std::runtime_error &e) {
               std::cout << "Failure" << std::endl;
               mg_printf_http_chunk(nc, "%s\n", e.what());
               delete wdb;
               wdb = nullptr;
            }
         }

         if (wdb != nullptr)
            gl->recent[wdb->GetName()] = std::time(nullptr);

      } else if (adr[0] == 'D') {
         DCB *dcb = nullptr;
         int i = 0;
         for (auto &d: gl->dcb) {
            // check if we are already connected
            if (std::string(adr) == d->GetName()) {
               dcb = d;
               if (dcb->Ping()) {
                  if (gl->verbose)
                     std::cout << "OK" << std::endl;
                  mg_printf_http_chunk(nc, "OK\n");
               } else {
                  // delete board from gl->dcb
                  gl->dcb.erase(gl->dcb.begin()+i);
                  std::string s = std::string("Cannot connect to board ") + adr;
                  mg_printf_http_chunk(nc, "%s\n", s.c_str());
               }
               break;
            }
            i++;
         }
         if (dcb == nullptr) {
            // create new board
            dcb = new DCB(adr, gl->verbose);
            try {
               std::cout << "Connect to " << dcb->GetName() << " ... " << std::flush;
               dcb->Connect();
               dcb->ScanCrate();
               std::cout << "OK" << std::endl;
               if (gl->verbose) {
                  std::cout << std::endl << "========== DCB Info ==========" << std::endl;
                  dcb->PrintVersion();
                  std::cout << std::endl << "Board scan:" << std::endl;
                  dcb->PrintCrate();
                  std::cout << std::endl;
               }
               gl->dcb.push_back(dcb);
               mg_printf_http_chunk(nc, "OK\n");

               connectDCB(gl, dcb);

            } catch (std::runtime_error &e) {
               std::cout << "Failure" << std::endl;
               mg_printf_http_chunk(nc, "%s\n", e.what());
               delete dcb;
               dcb = nullptr;
            }
         }

         if (dcb != nullptr)
            gl->recent[dcb->GetName()] = std::time(nullptr);

      } else
         mg_printf_http_chunk(nc, "Invalid address \"%s\"\n", adr.c_str());

      // write recent list to file
      std::map<time_t,std::string> rs;
      for (auto e: gl->recent)
         rs[e.second] = e.first;
      std::ofstream f;
      f.open(gl->wdsDir + "/recent.txt");
      for (auto e: rs)
         f << e.second << " " << e.first << std::endl;
      f.close();


      mg_send_http_chunk(nc, "", 0);
      return;
   }

   // crate
   static int slotHvOn = 0;
   if (http_event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/crate") == 0) {
      char str[256];
      mg_get_http_var(&hm->query_string, "adr", str, sizeof(str));
      auto adr = std::string(str);
      for (auto &c: adr) c = toupper(c);

      mg_get_http_var(&hm->query_string, "fl", str, sizeof(str));
      bool flag = atoi(str);

      if (gl->verbose)
         std::cout << "Doing " << (flag ? "full " : " ") << "scrate scan" << std::endl;

      DCB *dcb = nullptr;
      for (auto &d : gl->dcb) {
         if (d->GetName() == std::string(adr)) {
            dcb = d;
            break;
         }
      }

      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");

      // if not connected, try to connect
      if (dcb == nullptr) {
         dcb = new DCB(adr);
         try {
            std::cout << "Connect to " << dcb->GetName() << " ... " << std::flush;
            dcb->Connect();
            gl->dcb.push_back(dcb);
            std::cout << "OK" << std::endl;

            if (gl->verbose) {
               std::cout << std::endl << "========== DCB Info ==========" << std::endl;
               dcb->PrintVersion();
               std::cout << std::endl << "Board scan:" << std::endl;
               dcb->ScanCrate();
               dcb->PrintCrate();
               std::cout << std::endl;
            }

         } catch (std::runtime_error &e) {
            std::cout << "Failure" << std::endl;
            mg_printf_http_chunk(nc, "{\n");
            mg_printf_http_chunk(nc, "  \"error\": \"%s\"\n", e.what());
            mg_printf_http_chunk(nc, "}\n");
            mg_send_http_chunk(nc, "", 0);
            delete dcb;
            return;
         }
      }

      if (flag) {
         dcb->ScanCrate();
//         dcb->PrintCrate();
//         std::cout << std::endl;
         connectDCB(gl, dcb);
      }

      mg_printf_http_chunk(nc, "{\n");
      mg_printf_http_chunk(nc, "   \"DCB\": \"%s\",\n", dcb->GetName().c_str());
      mg_printf_http_chunk(nc, "   \"CMB\": \"%s\",\n", "MSCBXXX");
      mg_printf_http_chunk(nc, "   \"slot\": [\n");
      for (int i=0 ; i<16 ; i++) {
         if (dcb->GetWDB(i) != nullptr && !dcb->GetWDB(i)->Ping()) {
            std::cout << "Disconnected from " << dcb->GetWDB(i)->GetAddr() << std::endl;
            delete dcb->GetWDB(i);
            dcb->SetWDB(i, nullptr);
            dcb->ClearBoardId(i);
         }

         mg_printf_http_chunk(nc, "      {\n");
         mg_printf_http_chunk(nc, "        \"vendor_id\": %d,\n", dcb->GetBoardId(i)->vendor_id);
         mg_printf_http_chunk(nc, "        \"type_id\": %d,\n", dcb->GetBoardId(i)->type_id);
         mg_printf_http_chunk(nc, "        \"rev_id\": %d,\n", dcb->GetBoardId(i)->rev_id);

         // WDB specific items
         if (dcb->GetBoardId(i)->type_id == BRD_TYPE_ID_WDB) {
            mg_printf_http_chunk(nc, "        \"variant_id\": %d,\n", dcb->GetBoardId(i)->variant_id);

            mg_printf_http_chunk(nc, "        \"serial\": %d,\n", dcb->GetWDB(i)->GetSerialNumber());
            float hv = 0;
            dcb->GetWDB(i)->GetHVBaseVoltage(hv);
            mg_printf_http_chunk(nc, "        \"hv_on\": %d\n", hv > 10 ? 1:0);
         } else {
            mg_printf_http_chunk(nc, "        \"variant_id\": %d\n", dcb->GetBoardId(i)->variant_id);
         }

         if (i == 15)
            mg_printf_http_chunk(nc, "      }\n");
         else
            mg_printf_http_chunk(nc, "      },\n");
      }
      slotHvOn = (slotHvOn + 1) % 16;
      mg_printf_http_chunk(nc, "   ]\n");
      mg_printf_http_chunk(nc, "}\n");
      mg_send_http_chunk(nc, "", 0); // end of response
      return;
   }

   // DCB
   if (http_event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/dcb") == 0) {
      DCB *dcb = get_dcb_from_query(&hm->query_string, gl);

      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");
      if (dcb != nullptr) {
         auto str = dcb->SendReceiveUDP("jinfo");
         mg_printf_http_chunk(nc, "%s", str.c_str());
      }
      mg_send_http_chunk(nc, "", 0); // end of response
      return;
   }

   // mark
   if (http_event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/mark") == 0) {
      DCB *dcb = get_dcb_from_query(&hm->query_string, gl);
      mg_get_http_var(&hm->query_string, "fl", str, sizeof(str));
      bool flag = atoi(str);

      if (gl->verbose)
         std::cout << "Received \"mark " << (flag ? "on" : "off") << "\" command" << std::endl;

      if (dcb != nullptr)
         dcb->SendReceiveUDP(flag ? "mark" : "unmark");

      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");
      mg_printf_http_chunk(nc, "{\n");
      mg_printf_http_chunk(nc, "   \"status\": \"1\",\n");
      mg_printf_http_chunk(nc, "}\n");
      mg_send_http_chunk(nc, "", 0);
      return;
   }

   // boards
   if (http_event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/wdb") == 0) {
      char str[256];
      mg_get_http_var(&hm->query_string, "adr", str, sizeof(str));
      auto adr = std::string(str);
      for (auto &c: adr) c = toupper(c);

      WDB *b = nullptr;
      if (adr[0] == 'D') {
         std::string dcbName = adr.substr(0, adr.find(":"));
         int slot = std::stoi(adr.substr(adr.find(":")+1));

         DCB *dcb = nullptr;
         for (auto &d : gl->dcb) {
            if (d->GetName() == dcbName) {
               dcb = d;
               break;
            }
         }
         if (dcb == nullptr) {
            // create new board
            dcb = new DCB(dcbName, gl->verbose);
            try {
               std::cout << "Connect to " << dcbName << " ... " << std::flush;
               dcb->Connect();
               dcb->ScanCrate();
               std::cout << "OK" << std::endl;
               if (gl->verbose) {
                  std::cout << std::endl << "========== DCB Info ==========" << std::endl;
                  dcb->PrintVersion();
                  std::cout << std::endl << "Board scan:" << std::endl;
                  dcb->PrintCrate();
                  std::cout << std::endl;
               }
               gl->dcb.push_back(dcb);

               connectDCB(gl, dcb);

            } catch (std::runtime_error &e) {
               std::cout << "Failure" << std::endl;
               mg_printf_http_chunk(nc, "%s\n", e.what());
               delete dcb;
            }
         }

         b = dcb->GetWDB(slot);

      } else {
         for (auto &wdb : gl->wdb) {
            if (wdb->GetAddr() == std::string(adr)) {
               b = wdb;
               break;
            }
         }
      }

      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");

      // if not connected, try to connect
      if (b == nullptr) {
         b = new WDB(adr);
         try {
            std::cout << "Connect to " << b->GetAddr() << " ... " << std::flush;
            connectWDB(gl, b);
            gl->wdb.push_back(b);
            gl->wp->SetWDBList(gl->wdb);
            std::cout << "OK" << std::endl;
         } catch (std::runtime_error &e) {
            std::cout << "Failure" << std::endl;
            mg_printf_http_chunk(nc, "{\n");
            mg_printf_http_chunk(nc, "  \"error\": \"%s\"\n", e.what());
            mg_printf_http_chunk(nc, "}\n");
            mg_send_http_chunk(nc, "", 0);
            delete b;
            return;
         }
      }

      mg_printf_http_chunk(nc, "{\n");
      mg_printf_http_chunk(nc, "  \"wdb\": {\n");

      // simulate gaussian distributed scalers in demo mode
      std::vector<uint64_t> scaler;
      if (gl->demoMode) {
         std::poisson_distribution<int> dist(1000);

         for (auto i = 0; i < 34; i++)
            scaler.push_back(dist(randomGenerator));
      } else
         b->GetScalers(scaler, false);

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
         b->GetHVTarget(hv_target);
         b->GetHVCurrents(hv_current);
         b->Get1wireTemperatures(hv_temp);
         b->GetHVBaseVoltage(hv_base);
      }

      mg_printf_http_chunk(nc, "    \"name\": \"%s\",\n", b->GetName().c_str());
      mg_printf_http_chunk(nc, "    \"address\": \"%s\",\n", b->GetEthAddrStr().c_str());
      mg_printf_http_chunk(nc, "    \"revision\": \"%c\",\n", 'A' + b->GetBoardRevision());
      mg_printf_http_chunk(nc, "    \"fwRevision\": \"%s\",\n", b->GetFwGitHashStr().c_str());
      mg_printf_http_chunk(nc, "    \"fwBuild\": \"%s\",\n", gl->demoMode ? "N/A" : b->GetFwBuild().c_str());
      mg_printf_http_chunk(nc, "    \"swRevision\": \"%s\",\n", b->GetSwGitHashStr().c_str());
      mg_printf_http_chunk(nc, "    \"swBuild\": \"%s\",\n", gl->demoMode ? "N/A" : b->GetSwBuild().c_str());
      mg_printf_http_chunk(nc, "    \"temperature\": %1.1lf,\n", b->GetTemperatureDegree(false));
      mg_printf_http_chunk(nc, "    \"tempVCalib\": %1.1lf,\n", b->GetVCalibTemperature());
      mg_printf_http_chunk(nc, "    \"tempTCalib\": %1.1lf,\n", b->GetVCalibTemperature());
      mg_printf_http_chunk(nc, "    \"sysBusy\": %s,\n", b->GetSysBusy() ? "true" : "false");
      mg_printf_http_chunk(nc, "    \"drsctrlBusy\": %s,\n", b->GetDrsCtrlBusy() ? "true" : "false");
      mg_printf_http_chunk(nc, "    \"packagerBusy\": %s,\n", b->GetPackagerBusy() ? "true" : "false");
      mg_printf_http_chunk(nc, "    \"hvBoardPlugged\": %s,\n", b->GetHvBoardPlugged() ? "true" : "false");
      mg_printf_http_chunk(nc, "    \"hvVersion\": \"%s\",\n", b->GetHvVersion().c_str());
      mg_printf_http_chunk(nc, "    \"backplanePlugged\": %s,\n", b->GetBackplanePlugged() ? "true" : "false");
      mg_printf_http_chunk(nc, "    \"pllLck\": %d,\n", b->GetPllLock(false));
      mg_printf_http_chunk(nc, "    \"drsSampleFreq\": %d,\n", gl->demoMode ?
                                                               demoDrsSampleFreq : b->GetDrsSampleFreqMhz());
      mg_printf_http_chunk(nc, "    \"adcSampleFreq\": %d,\n", b->GetAdcSampleFreq() / 1000);
      mg_printf_http_chunk(nc, "    \"tdcSampleFreq\": %d,\n", b->GetTdcSampleFreq() / 1000);
      mg_printf_http_chunk(nc, "    \"compChannelStatus\": %d,\n", b->GetCompChStat());
      mg_printf_http_chunk(nc, "    \"eventTxRate\": %d,\n", b->GetEventTxRate());
      mg_printf_http_chunk(nc, "    \"lastEventNumber\": %d,\n", b->GetEventNumber());
      mg_printf_http_chunk(nc, "    \"triggerBusParityErrorCount\": %d,\n", b->GetTrbParityErrorCount());
      mg_printf_http_chunk(nc, "    \"triggerBusType\": %d,\n", b->GetTrbInfoLsb() & 0xFF); // ??
      mg_printf_http_chunk(nc, "    \"triggerBusNumber\": %d,\n", b->GetTrbInfoLsb() >> 8);   // ??
      mg_printf_http_chunk(nc, "    \"crateId\": %d,\n", b->GetCrateId());
      mg_printf_http_chunk(nc, "    \"slotId\": %d,\n", b->GetSlotId());
      mg_printf_http_chunk(nc, "    \"readoutSrcSel\": %d,\n", gl->readoutMode);
      mg_printf_http_chunk(nc, "    \"readoutEnable\": %d,\n", ((b->GetTrgTxEn() != 0) << 3)
                                                               | ((b->GetTdcChTxEn() != 0) << 2)
                                                               | ((b->GetAdcChTxEn() != 0) << 1)
                                                               | (b->GetDrsChTxEn() != 0));
      mg_printf_http_chunk(nc, "    \"daqNormal\": %s,\n", b->GetDaqNormal() ? "true" : "false");
      mg_printf_http_chunk(nc, "    \"daqSingle\": %s,\n", b->GetDaqSingle() ? "true" : "false");
      mg_printf_http_chunk(nc, "    \"drs0TimingRefSel\": %d,\n", b->GetDrs0TimingRefSel());
      mg_printf_http_chunk(nc, "    \"drs1TimingRefSel\": %d,\n", b->GetDrs1TimingRefSel());
      mg_printf_http_chunk(nc, "    \"calibBufferEnable\": %s,\n", b->GetCalibBufferEn() ? "true" : "false");
      mg_printf_http_chunk(nc, "    \"timingCalibSignalEnable\": %d,\n", b->GetTimingCalibSignalEn());
      mg_printf_http_chunk(nc, "    \"timingReferenceSignal\": %d,\n", b->GetTimingReferenceSignal());
      mg_printf_http_chunk(nc, "    \"daqClkSrcSel\": %d,\n", b->GetDaqClkSrcSel());
      mg_printf_http_chunk(nc, "    \"extClkInSel\": %d,\n", b->GetExtClkInSel());
      mg_printf_http_chunk(nc, "    \"extClkFreq\": %d,\n", b->GetExtClkFreq());
      mg_printf_http_chunk(nc, "    \"localClkFreq\": %d,\n", b->GetLocalClkFreq());
      mg_printf_http_chunk(nc, "    \"calibClkFreq\": %d,\n", b->GetCalibClkFreq());
      mg_printf_http_chunk(nc, "    \"chnTxEn\": %d,\n", b->GetChnTxEn());

      mg_printf_http_chunk(nc, "    \"packetEfficiency\": %lf,\n", gl->wp->GetWDPacketEfficiency());

      mg_printf_http_chunk(nc, "    \"dacOfs\": %1.3f,\n", b->GetDacOfsV());
      mg_printf_http_chunk(nc, "    \"dacCalDc\": %1.3f,\n", b->GetDacCalDcV());
      mg_printf_http_chunk(nc, "    \"dacPzcLevel\": %d,\n", b->GetDacPzcLevelN());

      mg_printf_http_chunk(nc, "    \"dacTriggerLevel\": [\n");
      for (int i = 0; i < 15; i++)
         mg_printf_http_chunk(nc, "      %1.3f,\n", b->GetDacTriggerLevelV(i));
      mg_printf_http_chunk(nc, "      %1.3f ],\n", b->GetDacTriggerLevelV(15));

      mg_printf_http_chunk(nc, "    \"fePzc\": [\n");
      for (int i = 0; i < 15; i++)
         mg_printf_http_chunk(nc, "      %s,\n", b->GetFePzc(i) ? "true" : "false");
      mg_printf_http_chunk(nc, "      %s ],\n", b->GetFePzc(15) ? "true" : "false");

      mg_printf_http_chunk(nc, "    \"feGain\": [\n");
      for (int i = 0; i < 15; i++)
         mg_printf_http_chunk(nc, "      %1g,\n", b->GetFeGain(i));
      mg_printf_http_chunk(nc, "      %1g ],\n", b->GetFeGain(15));

      mg_printf_http_chunk(nc, "    \"feMux\": [\n");
      for (int i = 0; i < 15; i++)
         mg_printf_http_chunk(nc, "      %d,\n", b->GetFeMux(i));
      mg_printf_http_chunk(nc, "      %d ],\n", b->GetFeMux(15));

      try {
         mg_printf_http_chunk(nc, "    \"fePower\": %d,\n", b->GetFePower());
      } catch(std::invalid_argument &e) {
         mg_printf_http_chunk(nc, "    \"fePower\": -1,\n");
      }

      mg_printf_http_chunk(nc, "    \"triggerMode\": %d,\n", gl->triggerMode);
      mg_printf_http_chunk(nc, "    \"triggerHoldoff\": %d,\n", b->GetTriggerHoldoff());
      mg_printf_http_chunk(nc, "    \"triggerLeadTrailEdgeSel\": %d,\n", b->GetLeadTrailEdgeSel());
      mg_printf_http_chunk(nc, "    \"triggerExtTriggerOutEnable\": %s,\n", b->GetExtTriggerOutEnable() ? "true" : "false");
      mg_printf_http_chunk(nc, "    \"triggerSource\": %d,\n", b->GetExtAsyncTriggerEn());
      mg_printf_http_chunk(nc, "    \"triggerOutPulseLength\": %d,\n", b->GetTriggerOutPulseLength());
      mg_printf_http_chunk(nc, "    \"triggerDelay\": %d,\n", b->GetTriggerDelayNs());
      mg_printf_http_chunk(nc, "    \"triggerSrcPolarity\": %d,\n", b->GetTrgSrcPolarity());
      mg_printf_http_chunk(nc, "    \"triggerAutoTriggerPeriod\": %d,\n", b->GetAutoTriggerPeriod());
      mg_printf_http_chunk(nc, "    \"triggerPtrnEn\": %d,\n", b->GetTrgPtrnEn());

      mg_printf_http_chunk(nc, "    \"triggerSrcEnPtrn\": [\n");
      for (int i = 0; i < 17; i++)
         mg_printf_http_chunk(nc, "      %d,\n", b->GetTrgSrcEnPtrn(i));
      mg_printf_http_chunk(nc, "      %d ],\n", b->GetTrgSrcEnPtrn(17));

      mg_printf_http_chunk(nc, "    \"triggerStatePtrn\": [\n");
      for (int i = 0; i < 17; i++)
         mg_printf_http_chunk(nc, "      %d,\n", b->GetTrgStatePtrn(i));
      mg_printf_http_chunk(nc, "      %d ],\n", b->GetTrgStatePtrn(17));

      mg_printf_http_chunk(nc, "    \"scaler\": [\n");
      for (auto &s: scaler) {
         if (&s != &scaler.back())
            mg_printf_http_chunk(nc, "      %d,\n", s);
         else
            mg_printf_http_chunk(nc, "      %d],\n", s);
      }

      mg_printf_http_chunk(nc, "    \"hv\": {\n");

      mg_printf_http_chunk(nc, "      \"target\": [\n");
      for (auto &s: hv_target) {
         if (&s != &hv_target.back())
            mg_printf_http_chunk(nc, "          %g,\n", s);
         else
            mg_printf_http_chunk(nc, "          %g],\n", s);
      }
      mg_printf_http_chunk(nc, "      \"current\": [\n");
      for (auto &s: hv_current) {
         if (&s != &hv_current.back())
            mg_printf_http_chunk(nc, "          %g,\n", s);
         else
            mg_printf_http_chunk(nc, "          %g],\n", s);
      }
      mg_printf_http_chunk(nc, "      \"temperature1Wire\": [\n");
      for (auto &s: hv_temp) {
         if (&s != &hv_temp.back())
            mg_printf_http_chunk(nc, "          %g,\n", s);
         else
            mg_printf_http_chunk(nc, "          %g],\n", s);
      }
      mg_printf_http_chunk(nc, "      \"baseVoltage\": %g\n\n", hv_base);

      mg_printf_http_chunk(nc, "    }\n");
      mg_printf_http_chunk(nc, "  }\n");
      mg_printf_http_chunk(nc, "}\n");
      mg_send_http_chunk(nc, "", 0);
      return;
   }

   // software build
   if (http_event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/build") == 0) {
      if (gl->verbose)
         std::cout << "Sending /build to browser" << std::endl;

      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");
      mg_printf_http_chunk(nc, "{\n");
      mg_printf_http_chunk(nc, "   \"build\": \"%s\",\n", __DATE__);
      mg_printf_http_chunk(nc, "   \"git revision\": \"%s\"\n", getWdbLibRevision().c_str());
      mg_printf_http_chunk(nc, "}\n");
      mg_send_http_chunk(nc, "", 0);
      return;
   }

   // return list of recent boards
   if (http_event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/recent") == 0) {
      if (gl->verbose)
         std::cout << "Sending /recent to browser" << std::endl;

      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");
      mg_printf_http_chunk(nc, "{\n");
      mg_printf_http_chunk(nc, "   \"recent\": [\n");

      // rs contains recent boards sorted by time in reverse order
      std::map<time_t,std::string,std::greater<time_t>> rs;
      for (auto e: gl->recent)
         rs[e.second] = e.first;
      std::vector<std::string> v;
      for (auto e: rs)
         v.push_back(e.second);
      for (auto &s: v) {
         if (&s != &v.back())
            mg_printf_http_chunk(nc, "      \"%s\",\n", s.c_str());
         else
            mg_printf_http_chunk(nc, "      \"%s\"\n", s.c_str());
      }

      mg_printf_http_chunk(nc, "   ]\n");
      mg_printf_http_chunk(nc, "}\n");
      mg_send_http_chunk(nc, "", 0);
      return;
   }

   // binary encoded waveforms
   if (http_event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/wf") == 0) {

      mg_get_http_var(&hm->query_string, "adr", str, sizeof(str));
      auto adr = std::string(str);
      for (auto &c: adr) c = toupper(c);

      mg_get_http_var(&hm->query_string, "chn", str, sizeof(str));
      int chn = atoi(str);

      WDB *wdb = nullptr;
      if (adr[0] == 'D') {
         std::string dcbName = adr.substr(0, adr.find(":"));
         int slot = std::stoi(adr.substr(adr.find(":")+1));

         DCB *dcb = nullptr;
         for (auto &d : gl->dcb) {
            if (d->GetName() == dcbName) {
               dcb = d;
               break;
            }
         }
         wdb = dcb->GetWDB(slot);

      } else {
         for (auto &b : gl->wdb) {
            if (b->GetAddr() == std::string(adr)) {
               wdb = b;
               break;
            }
         }
      }
      if (wdb == nullptr) {
         mg_printf_http_chunk(nc, "Board %s not found", adr.c_str());
         mg_send_http_chunk(nc, "", 0);
         return;
      }

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

               mg_send_http_chunk(nc, (const char *) wdb->mTCalib.mCalib.period[c], sizeof(float) * n);
            }

         mg_send_http_chunk(nc, "", 0);
         return;
      }

      WDEvent event(wdb->GetSerialNumber());
      bool bNewEvent;

      if (gl->demoMode) {
         bNewEvent = true;
         event.mVCalibrated = true;
         event.mTCalibrated = true;
         if (gl->readoutMode == cReadoutModeDRS) {
            event.mHasDRSData = true;
            for (int c = 0; c < WD_N_CHANNELS; c++) {
               for (int i = 0; i < 1024; i++) {
                  float t = i * 1E-6 / demoDrsSampleFreq;
                  event.mWfTDRS[c][i] = t;
                  event.mWfUDRS[c][i] = (float) (sin(M_PI * 2 * 100E6 * t + c / 8.0) / 2 +
                                                 ((float) random() / (float) RAND_MAX - 0.5) / 300);
               }
               // add spikes
               for (int i = 0; i < 1024; i++) {
                  if ((float) random() / (float) RAND_MAX < 0.00005) {
                     float s = ((float) random() / (float) RAND_MAX - 0.5) / 5;
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

         // only current board
         if (gl->triggerMode == cTriggerModeAuto)
            wdb->TriggerSoftEvent();
         else if (gl->triggerMode == cTriggerModeNormal) {
            if (!gl->triggerSelfArm) {
               sleep_ms(wdb->GetTriggerHoldoff());
               wdb->SetDaqSingle(1);
            }
         }

         // read waveforms
         if (gl->wp->IsXMLLogging())
            // increase timeout for slow XML logging
            bNewEvent = gl->wp->GetLastEvent(wdb, 5000, event);
         else
            bNewEvent = gl->wp->GetLastEvent(wdb, 500, event);
      }

      if (gl->demoMode)
         wdb = nullptr; // signals demo data

      if (bNewEvent) {
         if (event.mHasADCData && gl->readoutMode == cReadoutModeADC) { //---- ADC waveforms
            int t;                        // array type
            int brd = 0;                  // board index
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
         } else if (event.mHasTDCData && gl->readoutMode == cReadoutModeTDC) { //---- TDC waveforms
            int t;                        // array type
            int brd = 0;                  // board index
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
         } else if (event.mHasDRSData && gl->readoutMode == cReadoutModeDRS) { //---- DRS waveforms
            int t;                        // array type
            int brd = 0;                  // board index
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
         int brd = 0;                  // board index
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

      if (gl->verbose) {
         auto uri = std::string(hm->uri.p);
         if (uri.find(" HTTP") != std::string::npos)
            uri = uri.substr(0, uri.find(" HTTP"));
         std::cout << "File request: " << uri
                   << std::endl;
      }

      mg_serve_http(nc, hm, s_http_server_opts);
   }

}

/*------------------------------------------------------------------*/

void showUsage(std::string name) {
   if (name.find("/") != std::string::npos)
      name = name.substr(name.rfind("/") + 1); // strip path

   std::cerr << "usage: " << name << " [options]" << std::endl;
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

void connectWDB(GLOBALS *gl, WDB *b) {

   b->SetVerbose(gl->verbose);
   b->SetLogFile(gl->logFileName);
   b->Connect();

   do {
      b->ReceiveStatusRegisters();
      int s = b->GetSerialNumber();
      if (s == 0) {
         sleep_ms(100);
         std::cout << "Wait for serial" << std::endl;
      } else
         break;
   } while (true);

   b->ReceiveControlRegisters();
   if (gl->verbose) {
      std::cout << std::endl << "========== WDB Info ==========" << std::endl;
      b->PrintVersion();
   }

   // load calibration data for board
   b->LoadVoltageCalibration(b->GetDrsSampleFreqMhz(), gl->wdsDir);
   b->LoadTimeCalibration(b->GetDrsSampleFreqMhz(), gl->wdsDir);

   // check PLL locked status
   if (b->GetPllLock(false) != 0x1FF)
      std::cout << "PLL not locked on board " << b->GetAddr() << ". Mask = 0x" << std::hex << b->GetPllLock(false) << std::endl;

   if (b->GetDrsChTxEn() > 0) {
      gl->readoutMode = cReadoutModeDRS;
      b->SetChnTxEn(b->GetDrsChTxEn());
   } else if (b->GetAdcChTxEn() > 0) {
      gl->readoutMode = cReadoutModeADC;
      b->SetChnTxEn(b->GetAdcChTxEn());
   } else if (b->GetTdcChTxEn() > 0) {
      gl->readoutMode = cReadoutModeTDC;
      b->SetChnTxEn(b->GetTdcChTxEn());
   } else {
      b->SetDrsChTxEn(0xFFFF);
      b->SetChnTxEn(0xFFFF);
      gl->readoutMode = cReadoutModeDRS;
   }

   // enable internal trigger if external trigger is not enabled
   if (!b->GetExtAsyncTriggerEn())
      b->SetPatternTriggerEn(1);

   // disable scaler readout
   b->SetSclTxEn(0);

   // set destination
   b->SetDestinationPort(gl->wp->GetServerPort());

   // set DAQ mode
   b->SetDaqNormal(false);
}

void connectDCB(GLOBALS *gl, DCB *dcb) {
   for (int i=0 ; i<16 ; i++) {
      if (dcb->GetBoardId(i)->type_id == BRD_TYPE_ID_WDB) {
         if (dcb->GetWDB(i) == nullptr) {
            WDB *wdb = new WDB(dcb, i, gl->verbose);
            std::cout << "Connect to " << wdb->GetAddr() << " ... " << std::flush;
            connectWDB(gl, wdb);
            std::cout << "OK" << std::endl;
            dcb->SetWDB(i, wdb);
         }
      } else if (dcb->GetWDB(i) != nullptr) {
         std::cout << "Disconnected from " << dcb->GetWDB(i)->GetAddr() << std::endl;
         delete dcb->GetWDB(i);
         dcb->SetWDB(i, nullptr);
      }

   }
}

int main(int argc, const char *argv[]) {
   GLOBALS gl = {};

   // install handle to show stack trace on segment violation
   signal(SIGSEGV, handler);

   // default values
   gl.serverPort = 8080;
   gl.verbose = 0;
   gl.logFileName = "";
   gl.triggerMode = cTriggerModeAuto;
   gl.triggerSelfArm = false;
   gl.updatePeriodic = false;
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

   // read recent.txt file
   std::ifstream f;
   std::string line;
   f.open(gl.wdsDir + "/recent.txt");
   if (f.is_open()) {
      while (std::getline(f, line)) {
         std::istringstream s(line);
         std::string w;
         time_t t;
         s >> w >> t;
         // discard if more than one month old
         if (std::time(nullptr) - t < 3600*24*30)
            gl.recent[w] = t;
      }
      f.close();
   }

   // parse command line parameters

   for (int i = 1; i < argc; i++) {
      std::string arg = argv[i];
      if (arg == "-h" || arg == "-help" || arg == "--help") {
         showUsage(argv[0]);
         return 0;
      } else if (arg == "-demo")
         gl.demoMode = true;

      else if (arg == "-p")
         gl.serverPort = std::stoi(argv[++i]);

      else if (arg == "-l")
         gl.logFileName = std::string(argv[++i]);

      else if (arg == "-s")
         gl.triggerSelfArm = true;

      else if (arg == "-u")
         gl.updatePeriodic = true;

      else if (arg == "-v") {
         gl.verbose = 1;
         if (i < argc - 1 && isdigit(argv[i + 1][0]))
            gl.verbose = std::stoi(argv[++i]);
      }

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
                  DCB *dcb = new DCB(b, gl.verbose);
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

                  for (int j=0 ; j<16 ; j++) {
                     if (dcb->GetBoardId(j)->type_id == BRD_TYPE_ID_WDB) {
                        WDB *wdb = new WDB(dcb, j, gl.verbose);
                        connectWDB(&gl, wdb);
                        dcb->SetWDB(j, wdb);
                        gl.wdb.push_back(wdb);
                     }
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

   // instantiate waveform processor
   gl.wp = new WP(gl.verbose, gl.wdsDir, gl.logFileName, gl.demoMode);

   // remember trigger mode
   if (gl.triggerSelfArm)
      gl.triggerMode = cTriggerModeNormal;

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
         if (gl.wp != NULL && gl.wp->IsVcalibActive()) {
            gl.wp->DoVoltageCalibrationStep();

            // Yield to server, no timeout
            mg_mgr_poll(&mgr, 0);

         } else if (gl.wp != NULL && gl.wp->IsTcalibActive()) {
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
            int i=0;
            for (auto &b: gl.wdb) {
               try {
                  b->ReceiveStatusRegisters();
               } catch (...) {
                  gl.wdb.erase(gl.wdb.begin()+i);
                  std::cout << "Disconnected from " << b->GetAddr() << std::endl;
                  delete b;
               }
               i++;
            }
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

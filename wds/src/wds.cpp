//
//  wds.cpp
//  WaveDream Server Program
//
//  Stefan Ritt 31 Jan 2017
//

//
// Commands directly from command line:
//
// - connect to DCB or WDB:
//   $ curl -X PUT -d "" http://host:port/connect/DCBnn
//
// - firmware upload slot x:
//   $ curl -X PUT -d "" http://host:port/upload/DCBnn:x
//
// - firmware upload all slots:
//   $ curl -X PUT -d "" http://host:port/upload/DCBnn:*
//
// - firmware upload all slots with limited type:
//   $ curl -X PUT -d "" http://host:port/upload/DCBnn:*/lll
//   with lll=tcb or lll=wdb to limit to that type
//
// - issue "init" on WDB in slot x:
//   $ curl -X PUT -d "" http://host:port/init/DCBnn:x
//
// - issue "init" on WDB in slot x with different serial number y:
//   $ curl -X PUT -d "" http://host:port/init/DCBnn:x/y
//
// - issue "init" on WDB in all slots:
//   $ curl -X PUT -d "" http://host:port/init/DCBnn:*
//
// - voltage calibration slot x
//   $ curl -X PUT -d "" http://host:port/vcalib/DCBnn:x
//
// - voltage calibration all slots
//   $ curl -X PUT -d "" http://host:port/vcalib/DCBnn:*
//
// - time calibration slot x
//   $ curl -X PUT -d "" http://host:port/tcalib/DCBnn:x
//
// - time calibration all slots
//   $ curl -X PUT -d "" http://host:port/tcalib/DCBnn:*
//
// - query progress:
//   $ curl http://host:port/progress
//   returns:
//   {
//     "Mode": "Voltage|Time|Upload|Finished",
//     "Board": "DCBnn:x",
//     "Progress": "12.4"  <-- in percent
//   }
//
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
   bool daemonMode;
   bool demoMode;
   int serverPort;
   int verbose;
   std::string directConnect;
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
   enum { upload, vcalib, tcalib, finished } progressMode;
   std::string progressBoard;
   double progressPercentage;
   std::string cmdDCB;
} GLOBALS;

unsigned int demoDrsSampleFreq = 5016;

std::vector<std::string> split(const std::string &input, char separator);
void connectWDB(GLOBALS *gl, WDB *b);
void connectAllWDB(GLOBALS *gl, DCB *d);
void disconnectWDB(GLOBALS *gl, WDB *b);
void disconnectDCB(GLOBALS *gl, DCB *d);

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

WDB* findBoard(std::vector<DCB *> vdcb, std::vector<WDB *> vwdb, std::string adr) {
   for (auto &c: adr) c = toupper(c);

   WDB *wdb = nullptr;
   if (adr[0] == 'D') {
      std::string dcbName = adr.substr(0, adr.find(":"));
      int slot = std::stoi(adr.substr(adr.find(":") + 1));

      DCB *dcb = nullptr;
      for (auto &d : vdcb) {
         if (d->GetName() == dcbName) {
            dcb = d;
            break;
         }
      }
      wdb = dcb->GetWDB(slot);
   } else {
      for (auto &b : vwdb) {
         if (b->GetAddr() == adr) {
            wdb = b;
            break;
         }
      }
   }
   return wdb;
}

/*------------------------------------------------------------------*/

static struct mg_serve_http_opts s_http_server_opts;

// This function will be called by mongoose on every new request
static void wds_handler(struct mg_connection *nc, int http_event, void *pmsg) {
   struct http_message *hm = (struct http_message *) pmsg;
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
         if (args.size() > 3 && std::isdigit(args[3][0]))
            iChannel = std::stoi(args[3]);
      }
      if (hm->body.p)
         value = std::string(hm->body.p, hm->body.len);

      // search board in list
      for (auto &c: wdbAddress) c = toupper(c);
      std::vector<WDB *> wdbList;
      DCB *dcb = nullptr;
      int slot = -1;

      if (wdbAddress[0] == 'D') {
         std::string dcbName = wdbAddress.substr(0, wdbAddress.find(":"));
         if (wdbAddress.find(":") != std::string::npos) {
            auto s = wdbAddress.substr(wdbAddress.find(":") + 1);
            if (s == "*")
               slot = -1;
            else
               slot = std::stoi(s);
         }

         for (auto &d : gl->dcb) {
            if (d->GetName() == dcbName) {
               dcb = d;
               break;
            }
         }
         if (dcb == nullptr && item != "connect") {
            mg_send_response_line(nc, 200, "Content-Type: application/json\r\nTransfer-Encoding: chunked\r\n");
            mg_printf_http_chunk(nc, "{\n");
            mg_printf_http_chunk(nc, "  \"Error\": \"Not connected to %s\"\n", dcbName.c_str());
            mg_printf_http_chunk(nc, "}\n");
            mg_send_http_chunk(nc, "", 0);
            return;
         }

         if (slot != -1)
            wdbList.push_back(dcb->GetWDB(slot));

      } else {
         for (auto &wdb : gl->wdb) {
            if (wdbAddress == std::string("*") || wdb->GetAddr() == wdbAddress) {
               wdbList.push_back(wdb);
            }
         }
      }

      if (item == "connect") {
         for (auto &c: wdbAddress) c = toupper(c);

         if (gl->verbose)
            std::cout << "Trying to connect to " << wdbAddress << std::endl;

         mg_send_response_line(nc, 200, "Content-Type: application/json\r\nTransfer-Encoding: chunked\r\n");

         // treat numeric IP address as WDB board
         if (wdbAddress[0] == 'W' || isdigit(wdbAddress[0])) {
            WDB *wdb = nullptr;
            int i = 0;
            for (auto &b: gl->wdb) {
               // check if we are already connected
               if (std::string(wdbAddress) == b->GetAddr()) {
                  wdb = b;
                  if (wdb->Ping()) {
                     if (gl->verbose)
                        std::cout << "OK" << std::endl;
                     mg_printf_http_chunk(nc, "{\n   \"Status\": \"OK\"\n}\n");
                  } else {
                     // delete board from gl->wdb
                     gl->wdb.erase(gl->wdb.begin()+i);
                     std::string s = std::string("Cannot connect to board ") + wdbAddress;
                     mg_printf_http_chunk(nc, "{\n   \"Status\": \"%s\"\n}\n", s.c_str());
                  }
                  break;
               }
               i++;
            }

            if (wdb == nullptr) {
               // create new board
               wdb = new WDB(wdbAddress, gl->verbose);
               try {
                  if (gl->verbose)
                     std::cout << "Connect to " << wdb->GetAddr() << " ... " << std::flush;
                  connectWDB(gl, wdb);
                  gl->wdb.push_back(wdb);
                  gl->wp->SetWDBList(gl->wdb);
                  mg_printf_http_chunk(nc, "{\n   \"Status\": \"OK\"\n}\n");
                  if (gl->verbose)
                     std::cout << "OK" << std::endl;
               } catch (std::runtime_error &e) {
                  if (gl->verbose)
                     std::cout << "Failure" << std::endl;
                  mg_printf_http_chunk(nc, "{\n   \"Status\": \"%s\"\n}\n", e.what());
                  delete wdb;
                  wdb = nullptr;
               }
            }

            if (wdb != nullptr) {
               if (isdigit(wdbAddress[0]))
                  gl->recent[wdbAddress] = std::time(nullptr);
               else
                  gl->recent[wdb->GetName()] = std::time(nullptr);
            }

         } else if (wdbAddress[0] == 'D') {
            dcb = nullptr;
            int i = 0;
            for (auto &d: gl->dcb) {
               // check if we are already connected
               if (std::string(wdbAddress) == d->GetName()) {
                  dcb = d;
                  if (dcb->Ping()) {
                     if (gl->verbose)
                        std::cout << "OK" << std::endl;
                     mg_printf_http_chunk(nc, "{\n   \"Status\": \"OK\"\n}\n");
                  } else {
                     // delete board from gl->dcb
                     gl->dcb.erase(gl->dcb.begin()+i);
                     std::string s = std::string("Cannot connect to board ") + wdbAddress;
                     mg_printf_http_chunk(nc, "{\n   \"Status\": \"%s\"\n}\n", s.c_str());
                  }
                  break;
               }
               i++;
            }
            if (dcb == nullptr) {
               // create new board
               dcb = new DCB(wdbAddress, gl->verbose);
               try {
                  if (gl->verbose)
                     std::cout << "Connect to " << dcb->GetName() << " ... " << std::flush;
                  dcb->Connect();
                  dcb->ScanCrate();
                  if (gl->verbose)
                     std::cout << "OK" << std::endl;
                  if (gl->verbose) {
                     std::cout << std::endl << "========== DCB Info ==========" << std::endl;
                     dcb->PrintVersion();
                     std::cout << std::endl << "Board scan:" << std::endl;
                     dcb->PrintCrate();
                     std::cout << std::endl;
                  }
                  gl->dcb.push_back(dcb);
                  mg_printf_http_chunk(nc, "{\n   \"Status\": \"OK\"\n}\n");

                  connectAllWDB(gl, dcb);

               } catch (std::runtime_error &e) {
                  if (gl->verbose)
                     std::cout << "Failure" << std::endl;
                  mg_printf_http_chunk(nc, "{\n   \"Status\": \"%s\"\n}\n", e.what());
                  delete dcb;
                  dcb = nullptr;
               }
            }

            // set destination port for DCB, MAC and IP is used automatically from UDP packet
            if (dcb != nullptr)
               dcb->SetDestinationPort(gl->wp->GetServerPort());

            if (dcb != nullptr)
               gl->recent[dcb->GetName()] = std::time(nullptr);

         } else
            mg_printf_http_chunk(nc, "{\n   \"Status\": \"Invalid address %s\"\n}\n", wdbAddress.c_str());

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


      if (wdbList.size() == 0 && dcb == nullptr) {
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
         for (auto &b: wdbList) {
            b->SetDaqSoftTrigger(false);
            b->SetDaqSoftNormal(gl->triggerMode == cTriggerModeNormal ? 1 : 0);
         }
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
         std::vector<DCB *> dcbList;

         for (auto &b: wdbList) {
            b->SetDrsSampleFreq(std::stoi(value));

            // build list of all DCBs
            if (b->IsDcbInterface()) {
               auto d = b->GetDcbInterface();
               if (std::find(dcbList.begin(), dcbList.end(), d) == dcbList.end())
                  dcbList.push_back(d);
            }

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

         // serdes links might have dropped during LMK reprogramming, so issue reset
         for (auto &d: dcbList)
            d->ResetSerdes(0, true);

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
      } else if (item == "zeroSuppression") {
         // set zero suppression flag
         for (auto &b: wdbList) {
            b->SetZeroSuprEn(value == "true");
         }
      }

      //---------- commands ----------
      else if (item == "vcalib") {

         // prophylactially issue a SERDES reset
         for (auto &d : gl->dcb) {
            d->ResetSerdes(0, false);
            d->ResetSerdes(1, false);
         }

         // re-set destination address in case frontend has changed it
         for (auto &d : gl->dcb)
            d->SetDestinationPort(gl->wp->GetServerPort());

         if (!gl->demoMode) {
            if (slot == -1)
               gl->wp->StartCalibrationVoltage(nullptr);
            else {
               auto wdb = findBoard(gl->dcb, gl->wdb, wdbAddress);
               gl->wp->StartCalibrationVoltage(wdb);
            }
         }

      } else if (item == "tcalib") {

         // re-set destination address in case frontend has changed it
         for (auto &d : gl->dcb)
            d->SetDestinationPort(gl->wp->GetServerPort());

         if (!gl->demoMode) {
            if (slot == -1)
               gl->wp->StartCalibrationTime(nullptr);
            else {
               auto wdb = findBoard(gl->dcb, gl->wdb, wdbAddress);
               gl->wp->StartCalibrationTime(wdb);
            }
         }

      } else if (item == "save") {

         if (value == "stop")
            gl->wp->StopLogging();
         else if (item != "") {
            auto a = split(value, '\n');

            auto wdb = findBoard(gl->dcb, gl->wdb, a[2]);
            if (wdb) {
               gl->wp->StartWaveformSaving(std::string(s_http_server_opts.document_root) + "/" + a[0],
                                           a[1] == "bin" ? WP::cLiFormatBinary : WP::cLiFormatXML,
                                           a[2] == "all",
                                           a[2] == "all" ? -1 : wdb->GetSerialNumber(),
                                           std::stoi(a[3]));
            }
         }

      } else if (item == "reboot") {

         for (auto &b: wdbList) {
            if (gl->verbose)
               std::cout << "Reboot " << b->GetAddr() << std::endl;

            b->ReconfigureFpga();
            sleep_ms(5000);
            if (gl->verbose)
               std::cout << "Finished" << std::endl;

            connectWDB(gl, b);
         }

         if (dcb != nullptr) {
            dcb->SwitchDaqClocks();
            dcb->WaitLockAfterClockSwitch();
         }

      } else if (item == "mark") { // mark ------------------------------

         bool flag = (value[0] == '1');
         if (gl->verbose)
            std::cout << "Received \"mark " << (flag ? "on" : "off") << "\" command" << std::endl;
         if (dcb != nullptr)
            dcb->SendReceiveUDP(flag ? "mark" : "unmark");

      } else if (item == "sync") { // sync ------------------------------

         if (dcb != nullptr)
            dcb->SendReceiveUDP("sync");

      } else if (item == "sdreset") { // SERDES reset ------------------------------

         if (dcb != nullptr) {
            if (iChannel == 0)
               dcb->ResetSerdes(0, false);
            else
               dcb->ResetSerdes(1, false);
         }

      } else if (item == "upload") { // upload ------------------------------

         std::string result;
         if (dcb != nullptr) {
            gl->progressMode = GLOBALS::upload;
            gl->progressBoard = dcb->GetName() + ":" + std::to_string(slot);
            gl->progressPercentage = 0;

            std::string flags("");
            if (args.size() > 3 && args[3] == "tcb")
               flags += "-l tcb";
            if (args.size() > 3 && args[3] == "wdb")
               flags += "-l wdb";

            if (slot == -1) {
               result = dcb->UploadStart(-1, 0, flags);
               if (result.find(">") != std::string::npos) {
                  // immediate prompt: no board to upload
                  if (gl->verbose)
                     std::cout << "No board found to upload" << std::endl;
                  gl->progressMode = GLOBALS::finished;
                  result = "No board found to upload";
               }
            } else {
               if(dcb->GetBoardId(slot)->type_id == BRD_TYPE_ID_WDB || dcb->GetBoardId(slot)->type_id == BRD_TYPE_ID_BLANK){
                  auto b = dcb->GetWDB(slot);
                  if (b != nullptr && b->GetBoardRevision() == 4) // Rev. E
                     result = dcb->UploadStart(slot, 4, flags);
                  else if (b != nullptr && b->GetBoardRevision() == 5) // Rev. F
                     result = dcb->UploadStart(slot, 5, flags);
                  else if (b != nullptr && b->GetBoardRevision() == 6) // Rev. G
                     result = dcb->UploadStart(slot, 6, flags);
                  else
                     result = dcb->UploadStart(slot, 6, flags); // use G for empty board
               } else if(dcb->GetBoardId(slot)->type_id == BRD_TYPE_ID_TCB){
                  result = dcb->UploadStart(slot, 0, flags);
               } else {
                  if (gl->verbose)
                     std::cout << "No board found to upload" << std::endl;
                  gl->progressMode = GLOBALS::finished;
                  result = "No board found to upload";
               }
            }
         }

         mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
         mg_printf_http_chunk(nc, "{\n   \"Status\": \"%s\"\n}\n", result.c_str());
         mg_send_http_chunk(nc, "", 0); // end of response
         return;

      } else if (item == "init") { // init ------------------------------

         if (dcb != nullptr) {
            if (args.size() < 2)
               return;

            if (slot == -1) {
               int serial = iChannel;
               dcb->ScanCrate();

               for (int i=0 ; i<16 ; i++) {
                  if (dcb->GetBoardId(i)->type_id == BRD_TYPE_ID_WDB) {
                     if (dcb->GetWDB(i) == nullptr) {
                        if (gl->verbose)
                           std::cout << "Init new board in slot " << i << " with serial " << serial << std::endl;

                        // send ASCII command to WDB
                        auto result = dcb->SendToSlot("init " + std::to_string(serial), i);
                        serial++;
                     } else {
                        int s = dcb->GetWDB(i)->GetSerialNumber();
                        if (gl->verbose)
                           std::cout << "Init board in slot " << i << " with serial " << s << std::endl;

                        // send ASCII command to WDB
                        auto result = dcb->SendToSlot("init " + std::to_string(s), i);
                     }
                  }

                  if (dcb->GetWDB(i) != nullptr)
                     disconnectWDB(gl, dcb->GetWDB(i));
               }

            } else {
               int serial = iChannel;
               if (serial == -1)
                  serial = dcb->GetWDB(slot)->GetSerialNumber();

               if (gl->verbose)
                  std::cout << "Init board in slot " << slot << " with serial " << serial << std::endl;

               // send ASCII command to WDB
               auto result = dcb->SendToSlot("init " + std::to_string(serial), slot);

               if (dcb->GetWDB(slot) != nullptr)
                  disconnectWDB(gl, dcb->GetWDB(slot));
            }

            dcb->ScanCrate();
            connectAllWDB(gl, dcb);

            mg_send_response_line(nc, 200, "Content-Type: application/json\r\nTransfer-Encoding: chunked\r\n");
            mg_printf_http_chunk(nc, "{\n   \"Status\": \"OK\"\n}\n");
            mg_send_http_chunk(nc, "", 0); // end of response
            return;
         }

      } else {
         std::cout << "Invalid command \"" << item << "\" received. Aborting." << std::endl;
      }

      mg_send_response_line(nc, 200, "Content-Type: text/plain\r\nTransfer-Encoding: chunked\r\n");
      mg_send_http_chunk(nc, "", 0); // end of response
      return;
   } // method == PUT

   // globals
   if (http_event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/gl") == 0) {
      if (gl->verbose)
         std::cout << "Sending /gl to browser" << std::endl;

      mg_send_response_line(nc, 200, "Content-Type: application/json\r\nTransfer-Encoding: chunked\r\n");

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

   // crate ------------------------------
   static int slotHvOn = 0;
   if (http_event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/crate") == 0) {

      if (gl->progressMode != GLOBALS::finished)
         return;

      char str[256];
      static time_t lastFullScan = 0;
      mg_get_http_var(&hm->query_string, "adr", str, sizeof(str));
      auto adr = std::string(str);
      for (auto &c: adr) c = toupper(c);
      mg_get_http_var(&hm->query_string, "slot", str, sizeof(str));
      int slot = -1;
      if (str[0])
         slot = atoi(str);

      bool flag = false;
      if (std::time(nullptr) > lastFullScan + 10) {
         flag = true;
         lastFullScan = std::time(nullptr);
      }

      if (gl->verbose)
         std::cout << "Doing " << (flag ? "full" : "quick") << " crate scan" << std::endl;

      DCB *dcb = nullptr;
      for (auto &d : gl->dcb) {
         if (d->GetName() == std::string(adr)) {
            dcb = d;
            break;
         }
      }

      mg_send_response_line(nc, 200, "Content-Type: application/json\r\nTransfer-Encoding: chunked\r\n");

      // if not connected, try to connect
      if (dcb == nullptr) {
         dcb = new DCB(adr, gl->verbose);
         try {
            if (gl->verbose)
               std::cout << "Connect to " << dcb->GetName() << " ... " << std::flush;
            dcb->Connect();
            // set destination port for DCB, MAC and IP is used automatically from UDP packet
            dcb->SetDestinationPort(gl->wp->GetServerPort());
            gl->dcb.push_back(dcb);
            connectAllWDB(gl, dcb);

            if (gl->verbose)
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
            if (gl->verbose)
               std::cout << "Failure" << std::endl;
            mg_printf_http_chunk(nc, "{\n");
            mg_printf_http_chunk(nc, "  \"error\": \"Failed to connect to %s\"\n", adr.c_str());
            mg_printf_http_chunk(nc, "}\n");
            mg_send_http_chunk(nc, "", 0);
            delete dcb;
            return;
         }
      }

      std::string dcbinfo;
      try {
         if (flag) {
            // do full crate scan, look for new board
            dcb->ScanCrate();
            connectAllWDB(gl, dcb);
         }

         dcbinfo = dcb->SendReceiveUDP("jinfo");

      } catch (std::runtime_error &e) {
         if (gl->verbose)
            std::cout << e.what() << std::endl;
         mg_printf_http_chunk(nc, "{\n");
         mg_printf_http_chunk(nc, "   \"error\": \"Communication failure with %s: %s\"\n",
                              dcb->GetName().c_str(), e.what());
         mg_printf_http_chunk(nc, "}\n");
         mg_send_http_chunk(nc, "", 0);
         disconnectDCB(gl, dcb);
         return;
      }

      mg_printf_http_chunk(nc, "{\n");
      mg_printf_http_chunk(nc, "   \"DCB\":\n");
      mg_printf_http_chunk(nc, "%s,\n", dcbinfo.c_str());
      mg_printf_http_chunk(nc, "   \"slot\": [\n");

      // check for removed WDB boards
      auto p = dcbinfo.substr(dcbinfo.find("\"ping\": ") + 10);
      p = p.substr(0, p.find(" "));
      auto ap = split(p, ',');
      for (int i = 0; i < 16; i++) {
         auto b = dcb->GetWDB(i);
         if (b != nullptr && std::stod(ap[i]) == 0)
            disconnectWDB(gl, b);
      }

      for (int i = 0; i < 16; i++) {

         mg_printf_http_chunk(nc, "      {\n");
         mg_printf_http_chunk(nc, "        \"vendor_id\": %d,\n", dcb->GetBoardId(i)->vendor_id);
         mg_printf_http_chunk(nc, "        \"type_id\": %d,\n", dcb->GetBoardId(i)->type_id);
         mg_printf_http_chunk(nc, "        \"rev_id\": %d,\n", dcb->GetBoardId(i)->rev_id);

         // WDB specific items
         if (dcb->GetBoardId(i)->type_id == BRD_TYPE_ID_WDB) {
            WDB *b = dcb->GetWDB(i);
            if (i == slot)
               b->ReceiveStatusRegisters();

            mg_printf_http_chunk(nc, "        \"name\": \"%s\",\n", b->GetName().c_str());
            mg_printf_http_chunk(nc, "        \"variant_id\": %d,\n", dcb->GetBoardId(i)->variant_id);

            mg_printf_http_chunk(nc, "        \"serial\": %d,\n", b->GetSerialNumber());
            mg_printf_http_chunk(nc, "        \"crateId\": %d,\n", b->GetCrateId());
            mg_printf_http_chunk(nc, "        \"slotId\": %d,\n", b->GetSlotId());
            mg_printf_http_chunk(nc, "        \"revision\": \"%c\",\n", 'A' + b->GetBoardRevision());
            mg_printf_http_chunk(nc, "        \"fwRevision\": \"%s\",\n", b->GetFwGitHashStr().c_str());
            mg_printf_http_chunk(nc, "        \"fwBuild\": \"%s\",\n", gl->demoMode ? "N/A" : b->GetFwBuild().c_str());
            mg_printf_http_chunk(nc, "        \"swRevision\": \"%s\",\n", b->GetSwGitHashStr().c_str());
            mg_printf_http_chunk(nc, "        \"swBuild\": \"%s\",\n", gl->demoMode ? "N/A" : b->GetSwBuild().c_str());
            mg_printf_http_chunk(nc, "        \"hvBoardPlugged\": %s,\n", b->GetHvBoardPlugged() ? "true" : "false");
            mg_printf_http_chunk(nc, "        \"hvVersion\": \"%s\",\n", b->GetHvVersion().c_str());
            float hv_base;
            b->GetHVBaseVoltage(hv_base, false);
            mg_printf_http_chunk(nc, "        \"hvBaseVoltage\": %g,\n", hv_base);
            mg_printf_http_chunk(nc, "        \"temperature\": %1.1lf,\n", b->GetTemperatureDegree(false));
            mg_printf_http_chunk(nc, "        \"temperature1Wire\": [\n");
            std::vector<float> hv_temp;
            b->Get1wireTemperatures(hv_temp, false);
            for (auto &s: hv_temp) {
               if (&s != &hv_temp.back())
                  mg_printf_http_chunk(nc, "          %g,\n", s);
               else
                  mg_printf_http_chunk(nc, "          %g],\n", s);
            }
            mg_printf_http_chunk(nc, "        \"uptime\": %d,\n", b->GetUptime());
            mg_printf_http_chunk(nc, "        \"pllLck\": %d,\n", b->GetPllLock(false));
            mg_printf_http_chunk(nc, "        \"LEDstate\": %d,\n", b->GetLEDState(true));
            mg_printf_http_chunk(nc, "        \"sysBusy\": %s,\n", b->GetSysBusy() ? "true" : "false");
            mg_printf_http_chunk(nc, "        \"drsctrlBusy\": %s,\n", b->GetDrsCtrlBusy() ? "true" : "false");
            mg_printf_http_chunk(nc, "        \"triggerBusParityErrorCount\": %d,\n", b->GetTrbParityErrorCount());
            mg_printf_http_chunk(nc, "        \"compChannelStatus\": %d,\n", b->GetCompChStat());
            float hv = 0;
            b->GetHVBaseVoltage(hv, false);
            mg_printf_http_chunk(nc, "        \"hv_on\": %d\n", hv > 10 ? 1 : 0);
         } else {
            mg_printf_http_chunk(nc, "        \"variant_id\": %d\n", dcb->GetBoardId(i)->variant_id);
         }

         mg_printf_http_chunk(nc, "      },\n");
      }

      // slot 16
      mg_printf_http_chunk(nc, "      {\n");
      mg_printf_http_chunk(nc, "        \"vendor_id\": %d,\n", dcb->GetVendorId());
      mg_printf_http_chunk(nc, "        \"type_id\": %d,\n", dcb->GetBoardType());
      mg_printf_http_chunk(nc, "        \"rev_id\": %d,\n", dcb->GetBoardRevision());
      mg_printf_http_chunk(nc, "        \"variant_id\": %d\n", dcb->GetBoardVariant());
      mg_printf_http_chunk(nc, "      },\n");

      // slot 17
      mg_printf_http_chunk(nc, "      {\n");
      mg_printf_http_chunk(nc, "        \"vendor_id\": %d,\n", dcb->GetBoardId(17)->vendor_id);
      mg_printf_http_chunk(nc, "        \"type_id\": %d,\n", dcb->GetBoardId(17)->type_id);
      mg_printf_http_chunk(nc, "        \"rev_id\": %d,\n", dcb->GetBoardId(17)->rev_id);

      if (dcb->GetBoardId(17)->type_id == BRD_TYPE_ID_TCB) {
         mg_printf_http_chunk(nc, "        \"variant_id\": %d,\n", dcb->GetBoardId(17)->variant_id);

         auto reg = dcb->ReadUDP(17, 0, 16);
         int crateId  = (reg[6] >> 24) & 0xFF;
         int slotId   = (reg[6] >> 16) & 0xFF;
         int boardId  = reg[6] & 0xFFFF;
         int fwId     = (reg[0] >> 2) & 0x2F;
         int runStatus = (reg[1] >> 0) & 0x01;
         int boardBusy = (reg[1] >> 1) & 0x01;
         int crateBusy = (reg[1] >> 3) & 0x01;

         char fwBuild[256];
         unsigned int d = reg[15];
         sprintf(fwBuild, "%02d/%02d/20%02d %02d:%02d:%02d",
            (d&0xF8000000)>>27, (d&0x7800000)>>23, (d&0x7e0000)>>17, (d&0x1F000)>>12, (d&0xFC0)>>6, (d&0x3F));

         mg_printf_http_chunk(nc, "        \"crateId\": %d,\n", crateId);
         mg_printf_http_chunk(nc, "        \"slotId\": %d,\n",  slotId);
         mg_printf_http_chunk(nc, "        \"boardId\": %d,\n", boardId);
         mg_printf_http_chunk(nc, "        \"firmwareId\": %d,\n", fwId);
         mg_printf_http_chunk(nc, "        \"firmwareBuild\": \"%s\",\n", fwBuild);

         mg_printf_http_chunk(nc, "        \"runStatus\": %d,\n", runStatus);
         mg_printf_http_chunk(nc, "        \"boardBusy\": %d,\n", boardBusy);
         mg_printf_http_chunk(nc, "        \"crateBusy\": %d\n", crateBusy);
      } else
         mg_printf_http_chunk(nc, "        \"variant_id\": %d\n", dcb->GetBoardId(17)->variant_id);

      mg_printf_http_chunk(nc, "      }\n");

      slotHvOn = (slotHvOn + 1) % 16;
      mg_printf_http_chunk(nc, "   ]\n");
      mg_printf_http_chunk(nc, "}\n");
      mg_send_http_chunk(nc, "", 0); // end of response
      return;
   }

   // boards ------------------------------
   if (http_event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/wdb") == 0) {
      char str[256];
      mg_get_http_var(&hm->query_string, "adr", str, sizeof(str));
      auto adr = std::string(str);
      for (auto &c: adr) c = toupper(c);

      if (gl->wp->IsVcalibActive() || gl->wp->IsTcalibActive())
         adr = gl->wp->GetWDB(gl->wp->GetVcalibBoard())->GetAddr();

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
               if (gl->verbose)
                  std::cout << "Connect to " << dcbName << " ... " << std::flush;
               dcb->Connect();
               dcb->ScanCrate();
               // set destination port for DCB, MAC and IP is used automatically from UDP packet
               dcb->SetDestinationPort(gl->wp->GetServerPort());
               if (gl->verbose)
                  std::cout << "OK" << std::endl;
               if (gl->verbose) {
                  std::cout << std::endl << "========== DCB Info ==========" << std::endl;
                  dcb->PrintVersion();
                  std::cout << std::endl << "Board scan:" << std::endl;
                  dcb->PrintCrate();
                  std::cout << std::endl;
               }
               gl->dcb.push_back(dcb);
               connectAllWDB(gl, dcb);

            } catch (std::runtime_error &e) {
               if (gl->verbose)
                  std::cout << "Failure" << std::endl;
               mg_printf_http_chunk(nc, "%s\n", e.what());
               delete dcb;
            }
         }

         b = dcb->GetWDB(slot);
         if (b == nullptr) {
            mg_send_response_line(nc, 200, "Content-Type: application/json\r\nTransfer-Encoding: chunked\r\n");
            mg_printf_http_chunk(nc, "{\n");
            mg_printf_http_chunk(nc, "  \"error\": \"Board %s does not respond\"\n", adr.c_str());
            mg_printf_http_chunk(nc, "}\n");
            mg_send_http_chunk(nc, "", 0);
            return;
         }

      } else {
         for (auto &wdb : gl->wdb) {
            if (wdb->GetAddr() == std::string(adr)) {
               b = wdb;
               break;
            }
         }
      }

      mg_send_response_line(nc, 200, "Content-Type: application/json\r\nTransfer-Encoding: chunked\r\n");

      // if not connected, try to connect
      if (b == nullptr) {
         b = new WDB(adr);
         try {
            if (gl->verbose)
               std::cout << "Connect to " << b->GetAddr() << " ... " << std::flush;
            connectWDB(gl, b);
            gl->wdb.push_back(b);
            gl->wp->SetWDBList(gl->wdb);
            if (gl->verbose)
               std::cout << "OK" << std::endl;
         } catch (std::runtime_error &e) {
            if (gl->verbose)
               std::cout << "Failure" << std::endl;
            mg_printf_http_chunk(nc, "{\n");
            mg_printf_http_chunk(nc, "  \"error\": \"%s\"\n", e.what());
            mg_printf_http_chunk(nc, "}\n");
            mg_send_http_chunk(nc, "", 0);
            delete b;
            return;
         }
      }

      // receive current board status registers
      try {
         b->ReceiveStatusRegisters();
         b->ReceiveControlRegisters(); // if modified by other program
      } catch (...) {
         mg_printf_http_chunk(nc, "{\n");
         mg_printf_http_chunk(nc, "  \"error\": \"Board %s stopped to respond\"\n", b->GetAddr().c_str());
         mg_printf_http_chunk(nc, "}\n");
         mg_send_http_chunk(nc, "", 0);
         disconnectWDB(gl, b);
         gl->wp->SetRequestedBoard(gl->wdb);
         return;
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
      if (b->IsDcbInterface())
         mg_printf_http_chunk(nc, "    \"address\": \"%s\",\n", b->GetAddr().c_str());
      else
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
      mg_printf_http_chunk(nc, "    \"zeroSuppression\": %d,\n", b->GetZeroSuprEn());
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

   // software build ------------------------------
   if (http_event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/build") == 0) {
      if (gl->verbose)
         std::cout << "Sending /build to browser" << std::endl;

      mg_send_response_line(nc, 200, "Content-Type: application/json\r\nTransfer-Encoding: chunked\r\n");
      mg_printf_http_chunk(nc, "{\n");
      mg_printf_http_chunk(nc, "   \"build\": \"%s\",\n", __DATE__);
      mg_printf_http_chunk(nc, "   \"git revision\": \"%s\"\n", getWdbLibRevision().c_str());
      mg_printf_http_chunk(nc, "}\n");
      mg_send_http_chunk(nc, "", 0);
      return;
   }

   // return list of recent boards ------------------------------
   if (http_event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/recent") == 0) {
      if (gl->verbose)
         std::cout << "Sending /recent to browser" << std::endl;

      mg_send_response_line(nc, 200, "Content-Type: application/json\r\nTransfer-Encoding: chunked\r\n");
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

   //  progress for calibration and upload ------------------------------
   if (http_event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/progress") == 0) {

      mg_send_response_line(nc, 200, "Content-Type: application/json\r\nTransfer-Encoding: chunked\r\n");

      if (gl->wp->IsVcalibActive()) {

         std::string adr = gl->wp->GetWDB(gl->wp->GetVcalibBoard())->GetAddr();
         float f = gl->wp->GetVcalibProgress();
         mg_printf_http_chunk(nc, "{\n");
         mg_printf_http_chunk(nc, "   \"Mode\": \"Voltage\",\n");
         mg_printf_http_chunk(nc, "   \"Board\": \"%s\",\n", adr.c_str());
         mg_printf_http_chunk(nc, "   \"Progress\": \"%1.1lf\"\n", f*100);
         mg_printf_http_chunk(nc, "}\n");

      } else if (gl->wp->IsTcalibActive()) {

         std::string adr = gl->wp->GetWDB(gl->wp->GetTcalibBoard())->GetAddr();
         float f = gl->wp->GetTcalibProgress();
         mg_printf_http_chunk(nc, "{\n");
         mg_printf_http_chunk(nc, "   \"Mode\": \"Time\",\n");
         mg_printf_http_chunk(nc, "   \"Board\": \"%s\",\n", adr.c_str());
         mg_printf_http_chunk(nc, "   \"Progress\": \"%1.1lf\"\n", f*100);
         mg_printf_http_chunk(nc, "}\n");

      } else if (gl->progressMode == GLOBALS::upload) {

         mg_printf_http_chunk(nc, "{\n");
         mg_printf_http_chunk(nc, "   \"Mode\": \"Upload\",\n");
         mg_printf_http_chunk(nc, "   \"Board\": \"%s\",\n", gl->progressBoard.c_str());
         mg_printf_http_chunk(nc, "   \"Progress\": \"%1.1lf\"\n", gl->progressPercentage);
         mg_printf_http_chunk(nc, "}\n");

      } else {
         mg_printf_http_chunk(nc, "{\n");
         mg_printf_http_chunk(nc, "   \"Mode\": \"Finished\"\n");
         mg_printf_http_chunk(nc, "}\n");
      }

      mg_send_http_chunk(nc, "", 0);
      return;
   }

   // binary encoded waveforms ------------------------------
   if (http_event == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/wf") == 0) {
      char str[256];
      mg_get_http_var(&hm->query_string, "adr", str, sizeof(str));
      auto wdb = findBoard(gl->dcb, gl->wdb, str);
      if (wdb == nullptr) {
         mg_send_response_line(nc, 200, "Content-Type: application/octet-stream\r\nTransfer-Encoding: chunked\r\n");
         mg_printf_http_chunk(nc, "Board %s not found", str);
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
         wdb =  gl->wp->GetWDB(vcb);

         float f = gl->wp->GetVcalibProgress();
         mg_send_http_chunk(nc, (const char *) &f, 4);

         for (int c = 0; c < WD_N_CHANNELS; c++) {
            int n = 1024;
            mg_send_http_chunk(nc, (const char *) &c, 4);
            mg_send_http_chunk(nc, (const char *) &n, 4);

            mg_send_http_chunk(nc, (const char *) wdb->mVCalib.mCalib.wf_calibrated[c], sizeof(float) * n);
         }

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
         wdb =  gl->wp->GetWDB(tcb);

         float f = gl->wp->GetTcalibProgress();
         mg_send_http_chunk(nc, (const char *) &f, 4);

         for (int c = 0; c < WD_N_CHANNELS; c++) {
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
               event.mDRSChannelPresent[c] = true;
               for (int i = 0; i < 1024; i++) {
                  float t = i * 1E-6 / demoDrsSampleFreq;
                  event.mWfTDRS[c][i] = t;
                  event.mWfUDRS[c][i] = (float) (sin(M_PI * 2 * 800E6 * t + c / 8.0) / 2 +
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
         gl->wp->SetRequestedBoard(wdb);
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
               if (event.mADCChannelPresent[c]) {
                  t = 1; // time array
                  int trcell = (c < 8 || c == 16) ? event.mTriggerCellDrs0 : event.mTriggerCellDrs1;
                  mg_send_http_chunk(nc, (const char *) &t, 4);
                  mg_send_http_chunk(nc, (const char *) &brd, 4);
                  mg_send_http_chunk(nc, (const char *) &tc, 4);
                  mg_send_http_chunk(nc, (const char *) &l, 4);
                  mg_send_http_chunk(nc, (const char *) &c, 4);
                  mg_send_http_chunk(nc, (const char *) &n, 4);
                  mg_send_http_chunk(nc, (const char *) &trcell, 4);
                  mg_send_http_chunk(nc, (const char *) &event.mWfTADC[c][0], sizeof(float) * n);
               }
            }

            for (int c = 0; c < WD_N_CHANNELS; c++) {
               if (event.mADCChannelPresent[c]) {
                  printf("## t=2, c=%d, n=%d\n", c, n);
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
               if (event.mTDCChannelPresent[c]) {
                  t = 1; // time array
                  int trcell = (c < 8 || c == 16) ? event.mTriggerCellDrs0 : event.mTriggerCellDrs1;
                  mg_send_http_chunk(nc, (const char *) &t, 4);
                  mg_send_http_chunk(nc, (const char *) &brd, 4);
                  mg_send_http_chunk(nc, (const char *) &tc, 4);
                  mg_send_http_chunk(nc, (const char *) &l, 4);
                  mg_send_http_chunk(nc, (const char *) &c, 4);
                  mg_send_http_chunk(nc, (const char *) &n, 4);
                  mg_send_http_chunk(nc, (const char *) &trcell, 4);
                  mg_send_http_chunk(nc, (const char *) &time[0], sizeof(float) * n);
               }
            }
            for (int c = 0; c < WD_N_CHANNELS; c++) {
               if (event.mTDCChannelPresent[c]) {
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
            int brd = gl->demoMode ? 0xFF : 0; // board index
            int n = 1024;                 // number of elements
            int vc = event.mVCalibrated;  // voltage calibrated
            int tc = event.mTCalibrated;  // time calibrated
            int l = gl->wp->GetNLogged(); // number of logged events
            for (int c = 0; c < WD_N_CHANNELS; c++) {
               if (event.mDRSChannelPresent[c]) {
                  t = 1; // time array
                  int trcell = (c < 8 || c == 16) ? event.mTriggerCellDrs0 : event.mTriggerCellDrs1;
                  mg_send_http_chunk(nc, (const char *) &t, 4);
                  mg_send_http_chunk(nc, (const char *) &brd, 4);
                  mg_send_http_chunk(nc, (const char *) &tc, 4);
                  mg_send_http_chunk(nc, (const char *) &l, 4);
                  mg_send_http_chunk(nc, (const char *) &c, 4);
                  mg_send_http_chunk(nc, (const char *) &n, 4);
                  mg_send_http_chunk(nc, (const char *) &trcell, 4);
                  mg_send_http_chunk(nc, (const char *) event.mWfTDRS[c], sizeof(float) * n);
               }
            }

            for (int c = 0; c < WD_N_CHANNELS; c++) {
               if (event.mDRSChannelPresent[c]) {
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

   // file serving ------------------------------
   if (http_event == MG_EV_HTTP_REQUEST) {

      auto uri = std::string(hm->uri.p);
      if (uri.find(" HTTP") != std::string::npos)
         uri = uri.substr(0, uri.find(" HTTP"));

      if (gl->verbose) {
         std::cout << "File request: " << uri
                   << std::endl;
      }

      if (uri == "/") {
         char host[256];
         gethostname(host, sizeof(host));
         if (strncmp(host, "dcb", 3) == 0 || strncmp(host, "DCB", 3) == 0) {
            if (strchr(host, '.'))
               *strchr(host, '.') = 0; // strip domain
         } else
            host[0] = 0;

         auto str = gl->cmdDCB;
         if (str == "")
            str = std::string(host);

         // redirect to DCB if running on DCB
         if (str != "") {
            std::string url = "HTTP/1.1 301 Moved\r\nLocation: crate.html?adr=";
            url += str;
            url += "\r\nContent-Length: 0\r\n\r\n";
            mg_printf(nc, "%s", url.c_str());
         } else {
            if (gl->demoMode) {
               std::string url = "HTTP/1.1 301 Moved\r\nLocation: osc.html?adr=WD000";
               url += "\r\nContent-Length: 0\r\n\r\n";
               mg_printf(nc, "%s", url.c_str());
            }
            // redirect if connected already from command line
            if (!gl->directConnect.empty()) {
               std::string url = "HTTP/1.1 301 Moved\r\nLocation: osc.html?adr=";
               url += gl->directConnect;
               url += "\r\nContent-Length: 0\r\n\r\n";
               mg_printf(nc, "%s", url.c_str());
            } else
               mg_serve_http(nc, hm, s_http_server_opts);
         }

      } else
         mg_serve_http(nc, hm, s_http_server_opts);
   }

}

/*------------------------------------------------------------------*/

void showUsage(std::string name) {
   if (name.find("/") != std::string::npos)
      name = name.substr(name.rfind("/") + 1); // strip path

   std::cerr << "usage: " << name << " [options]" << std::endl;
   std::cerr << "valid options:" << std::endl;
   std::cerr << "  -D              Become a daemon" << std::endl;
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
   std::cerr << "  -W <dir>        Specify directory in which \"html\" resides" << std::endl;
   std::cerr << "  -w <wdb>        Connect directly to WDxxx or DCBxx" << std::endl;
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
   b->Setup(gl->wdsDir, gl->wp != nullptr ? gl->wp->GetServerPort() : 0);

   // determine mode according to enabled channels
   if (b->GetDrsChTxEn() > 0) {
      b->SetChnTxEn(b->GetDrsChTxEn());
      gl->readoutMode = cReadoutModeDRS;
   } else if (b->GetAdcChTxEn() > 0) {
      b->SetChnTxEn(b->GetAdcChTxEn());
      gl->readoutMode = cReadoutModeADC;
   } else if (b->GetTdcChTxEn() > 0) {
      b->SetChnTxEn(b->GetTdcChTxEn());
      gl->readoutMode = cReadoutModeTDC;
   } else {
      b->SetDrsChTxEn(0xFFFF);
      b->SetChnTxEn(0xFFFF);
      gl->readoutMode = cReadoutModeDRS;
   }

   // disable scaler readout
   b->SetSclTxEn(0);

   // obtain soft auto trigger mode from board
   gl->triggerMode = b->GetDaqSoftNormal() ? cTriggerModeNormal : cTriggerModeAuto;
}

void connectAllWDB(GLOBALS *gl, DCB *dcb) {
   bool newBoard = false;
   for (int i=0 ; i<16 ; i++) {
      if (dcb->GetBoardId(i)->type_id == BRD_TYPE_ID_WDB) {
         if (dcb->GetWDB(i) == nullptr) {
            WDB *wdb = new WDB(dcb, i, gl->verbose);
            if (gl->verbose)
               std::cout << "Connect to " << wdb->GetAddr() << " ... " << std::flush;
            connectWDB(gl, wdb);
            gl->wdb.push_back(wdb);
            if (gl->wp != nullptr)
               gl->wp->SetWDBList(gl->wdb);
            if (gl->verbose)
               std::cout << "OK" << std::endl;
            dcb->SetWDB(i, wdb);
            newBoard = true;
         }
      } else if (dcb->GetWDB(i) != nullptr) {
         disconnectWDB(gl, dcb->GetWDB(i));
      }
   }

   dcb->SwitchDaqClocks();
   dcb->WaitLockAfterClockSwitch();
}

void disconnectWDB(GLOBALS *gl, WDB *b) {
   if (gl->verbose)
      std::cout << "Disconnect from " << b->GetAddr() << std::endl;
   for (auto &dcb: gl->dcb) {
      for (int i=0 ; i<16 ; i++)
         if (dcb->GetWDB(i) == b) {
            dcb->SetWDB(i, nullptr);
            dcb->ClearBoardId(i);
         }
   }
   gl->wdb.erase(std::remove(gl->wdb.begin(), gl->wdb.end(), b), gl->wdb.end());
   delete b;
}

void disconnectDCB(GLOBALS *gl, DCB *d) {
   for (int i=0 ; i<16 ; i++)
      if (d->GetWDB(i) != nullptr)
         disconnectWDB(gl, d->GetWDB(i));
   if (gl->verbose)
      std::cout << "Disconnect from " << d->GetName() << std::endl;
   gl->dcb.erase(std::remove(gl->dcb.begin(), gl->dcb.end(), d), gl->dcb.end());
   delete d;
}

int main(int argc, const char *argv[]) {
   GLOBALS gl = {};

   std::cout << "WDS starting" << std::endl;
   std::cout << "WDS GIT revision: " << getWdbLibRevision() << std::endl;

   // install handle to show stack trace on segment violation
   signal(SIGSEGV, handler);

   // default values
   gl.daemonMode = false;
   gl.serverPort = 8080;
   gl.verbose = 0;
   gl.directConnect = "";
   gl.logFileName = "";
   gl.triggerMode = cTriggerModeAuto;
   gl.triggerSelfArm = false;
   gl.updatePeriodic = false;
   gl.wdsDir = "";
   gl.progressMode  = GLOBALS::finished;
   gl.progressBoard = "";
   gl.progressPercentage = 0;
   gl.wp = nullptr;

   // extract wds directory from command line parameters
   std::string dir;
   for (int i = 1; i < argc; i++) {
      std::string arg = argv[i];
      if (arg == "-W" && argc > i + 1) {
         dir = std::string(argv[i + 1]);
         break;
      }
   }

   // find wds directory
   if (dir == "") {
      char tmp[256];
      getcwd(tmp, sizeof(tmp));
      dir = tmp;
   }
   std::ifstream f1(dir + "/html/index.html");
   if (f1.good()) {
      gl.wdsDir = dir;
   } else {
      if (getenv("WDBSYS")) {
         std::ifstream f3(std::string(getenv("WDBSYS")) + "/sw/wds/html/index.html");
         if (f3.good()) {
            gl.wdsDir = std::string(getenv("WDBSYS")) + "/sw/wds";
         } else {
            std::ifstream f4(std::string(getenv("WDBSYS")) + "/html/index.html");
            if (f4.good()) {
               gl.wdsDir = std::string(getenv("WDBSYS"));
            } else {
               std::cerr << "Cannot find 'html' directory. Please corret 'WDBSYS' environment variable." << std::endl;
               std::cerr << "WDBSYS currently points to '" << getenv("WDBSYS") << "'" << std::endl;
               return 1;
            }
         }
      } else {
         std::cerr << "Cannot find 'WDBSYS' environment variable. Please set it to the wavedaq_main directory." << std::endl;
         std::cerr << "Alternatively, use the '-W <dir>' argument to point to the directory where 'html' resides." << std::endl;
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
      }

      else if (arg == "-D")
         gl.daemonMode = true;

      else if (arg == "-demo")
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

      else if (arg == "-W") { i++; }

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
               gl.directConnect = b;

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
                  gl.cmdDCB = b;
                  connectAllWDB(&gl, dcb);

               } catch (std::runtime_error &e) {
                  std::cout << std::endl;
                  std::cout << e.what() << std::endl;
                  std::cout << "Aborting." << std::endl;
                  return 1;
               }
               if (gl.verbose)
                  std::cout << "OK" << std::endl;
               gl.directConnect = b;

            } else {
               gl.directConnect = b;

               // connect to board directly
               try {
                  WDB *wdb = new WDB(gl.directConnect, gl.verbose);
                  if (gl.verbose)
                     std::cout << "Connect to " << wdb->GetAddr() << " ... " << std::flush;
                  connectWDB(&gl, wdb);
                  gl.wdb.push_back(wdb);
               } catch (std::runtime_error &e) {
                  std::cout << std::endl << "Error connecting to " << gl.directConnect << ": " << e.what() << std::endl;
                  return 1;
               }
            }
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
      gl.wdb.push_back(new WDB("WD000"));
      gl.readoutMode = cReadoutModeDRS;
   }

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

   // if running on DCB, directly connect to local crate
   char host[256];
   gethostname(host, sizeof(host));
   if (strncmp(host, "dcb", 3) == 0 || strncmp(host, "DCB", 3) == 0) {
      if (strchr(host, '.'))
         *strchr(host, '.') = 0; // strip domain
      std::string adr = host;
      for (auto &c: adr) c = toupper(c);

      // create new board
      DCB *dcb = new DCB(adr, gl.verbose);
      try {
         std::cout << "WDS connect to " << dcb->GetName() << " ... " << std::flush;
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
         connectAllWDB(&gl, dcb);

         if (!gl.verbose)
            std::cout << "OK" << std::endl;
      } catch (std::runtime_error &e) {
         std::cout << std::endl << "Error connecting to " << dcb->GetName() << ": " << e.what() << std::endl;
         delete dcb;
         dcb = nullptr;
      }
   }

   std::cout << "WDS starting HTTP server at port " << gl.serverPort << std::endl;

   if (gl.demoMode)
      std::cout << "WDS starting in DEMO mode" << std::endl;

   if (gl.daemonMode) {
      std::cout << "WDS becoming a daemon..." << std::endl;
      int fd, pid;

      if ((pid = fork()) < 0)
         return 1;
      else if (pid != 0)
         exit(0);  // parent finished

      /* child continues here */

      setsid(); // become session leader
   }

   // instantiate waveform processor
   gl.wp = new WP(gl.verbose, gl.wdsDir, gl.logFileName, gl.demoMode);

   // set destination port for DCB, MAC and IP is used automatically from UDP packet
   for (auto &db : gl.dcb)
      db->SetDestinationPort(gl.wp->GetServerPort());

   for (auto &wb : gl.wdb)
      wb->SetDestinationPort(gl.wp->GetServerPort());

   gl.wp->SetWDBList(gl.wdb);

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

         } else if (gl.progressMode == GLOBALS::upload) {

            auto dcb = gl.dcb[0];
            if (dcb != nullptr) {
               auto s = dcb->UploadProgress();
               if (s != "") {
                  if (s.find(">") != std::string::npos) {
                     if (gl.verbose)
                        std::cout << "Upload finished" << std::endl;
                     gl.progressMode = GLOBALS::finished;
                  } else {
                     if (gl.verbose)
                        std::cout << "Upload progress returned \"" << s << "\"" << std::endl;
                     gl.progressBoard = dcb->GetName() + ":" + std::to_string(std::stoi(s));
                     gl.progressPercentage = std::stod(s.substr(s.find(" ") + 1));
                  }
               }
            }

            // Yield to server, 10ms timeout
            mg_mgr_poll(&mgr, 10);

         } else
            // Yield to server, 10ms timeout
            mg_mgr_poll(&mgr, 10);

         // cycle phase of sine wave
         //static int delay = 0;
         //for (auto &b: gl.wdb)
         //   b->SetSineWaveDelay(delay);
         //delay = (delay == 16) ? -16 : delay + 1;

      }
   } catch (std::runtime_error &e) {
      std::cout << std::endl;
      std::cout << e.what() << std::endl;
      std::cout << "Aborting." << std::endl;

      return 1;
   }

   return 0;
}

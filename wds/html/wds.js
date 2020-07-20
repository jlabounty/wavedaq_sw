//
//  wds.js
//  WaveDAQ Server Application JavaScript Code
//
//  Created by Stefan Ritt on 5/8/15.
//

// demo mode
var demoMode = false;

var OSC; // global scope object

var progressInd = 0;
var progressOldBoard = 0;

function init() {
   // prevent mouse events to go up to the browser
   let c = document.getElementById("controls");
   c.addEventListener("click", function (e) {
      e.preventDefault()
   });
   c.addEventListener("mousemove", function (e) {
      e.preventDefault()
   });

   c = document.getElementById("scope");
   c.addEventListener("click", function (e) {
      e.preventDefault()
   });
   c.addEventListener("mousemove", function (e) {
      e.preventDefault()
   });

   // capture all key events
   document.addEventListener("keypress", oscKeypress, false);

   // create Scope object
   OSC = new Oscilloscope(document.getElementById("scope"));

   /* test for measurements */
   OSC.measList = document.getElementById("measList");

   // load globals including board list from server
   loadGl(true);

   // load build and put into about box
   loadBuild();

   // hide config panel
   let config = document.getElementById("config");
   config.t = 0;
   config.slider = 0;
   config.visible = false;

   // fill channels panel
   let chTable = document.getElementById("channelsTable");
   for (let r = 0; r < 16; r++) {
      let row = chTable.insertRow(-1);
      row.className = "channelsRow";

      let cell = row.insertCell(-1);
      cell.className = "channelsTd";
      cell.appendChild(document.createTextNode(r.toString()));
      cell.style.backgroundColor = OSC.chnColors[r];

      cell = row.insertCell(-1);
      cell.className = "channelsTd";
      let sel = document.createElement('select');
      sel.id = "selGain" + r;
      sel.name = "feGain";
      sel.setAttribute("onchange", "setParam(this," + r + ")");
      let gains = ["0.5", "1", "2.5", "5", "10", "25", "50", "100"];
      for (let i = 0; i < gains.length; i++) {
         let op = document.createElement('option');
         op.value = op.textContent = gains[i];
         if (gains[i] === "1")
            op.selected = true;
         sel.appendChild(op);
      }
      cell.appendChild(sel);

      cell = row.insertCell(-1);
      cell.className = "channelsTd";
      let cb = document.createElement('input');
      cb.type = "checkbox";
      cb.name = "fePzc";
      cb.id = "cbPzc" + r;
      cb.checked = false;
      cb.setAttribute("onclick", "setParam(this," + r + ")");
      cell.appendChild(cb);

      cell = row.insertCell(-1);
      cell.className = "channelsTd";
      let inp = document.createElement('input');
      inp.type = "text";
      inp.value = "0";
      inp.name = "dacTriggerLevel";
      inp.id = "inpDacTriggerLevel" + r;
      inp.style.width = "60px";
      inp.setAttribute("onkeypress", "keyParam(event, this," + r + ")");
      inp.setAttribute("onblur", "validateParam(this," + r + ")");
      let index = 100+r;
      inp.setAttribute("tabindex", index.toString());
      cell.appendChild(inp);
      cell.appendChild(document.createTextNode(" mV"));

      cell = row.insertCell(-1);
      cell.className = "channelsTd";
      inp = document.createElement('input');
      inp.type = "text";
      inp.value = "N/A";
      inp.name = "hvTarget";
      inp.id = "inpHvTarget" + r;
      inp.style.width = "80px";
      inp.setAttribute("onkeypress", "keyParam(event, this," + r + ")");
      inp.setAttribute("onblur", "validateParam(this," + r + ")");
      index = 116 + r;
      inp.setAttribute("tabindex", index.toString());
      cell.appendChild(inp);
      let e = document.createElement("span");
      e.innerHTML = "&nbsp;V&nbsp;";
      cell.appendChild(e);

      cell = row.insertCell(-1);
      cell.className = "channelsTd";
      inp = document.createElement('input');
      inp.type = "text";
      inp.value = "N/A";
      inp.name = "hvCurrent";
      inp.id = "inpHvCurrent" + r;
      inp.style.width = "80px";
      inp.disabled = true;
      cell.appendChild(inp);
      cell.appendChild(document.createTextNode(" uA"));
   }

   resize();

   // add resize event handler
   window.addEventListener("resize", resize);

   // draw empty scope
   OSC.redraw();

   // schedule first waveform load
   OSC.timer.loadWF = window.setTimeout(loadWF, 10);

   // schedule loadWdb()
   OSC.timer.loadWdb = window.setTimeout(loadWdb, 1000);

   // load spinning wheel image
   OSC.spinningWheel = new Image();
   OSC.spinningWheel.src = "spinning-wheel-wds.gif";
}

function loadWdb() {
   let now = new Date()/1000;

   if (now > OSC.lastParamSet + 2) {
      readWdb(OSC.curBoard).then(function () {
         OSC.timer.loadWdb = window.setTimeout(loadWdb, 1000);
      }).catch();
   } else {
      OSC.timer.loadWdb = window.setTimeout(loadWdb, 1000);
   }
}

function connectionBroken() {
   if (OSC.connected) {
      OSC.dlgReconnect = dlgMessage("Error", "Connection to server broken.<br>Trying to reconnect ..." +
         "<br /><br /><br /><img alt=\"Please wait\" src=\"spinning-wheel-wds.gif\">", true, true);
      let b = document.getElementById("dlgMessageButton");
      b.innerHTML = "Cancel";
      OSC.connected = false;
      OSC.timer.reconnect = window.setTimeout(reconnect, 1000);
   }

   if (OSC.timer.loadGl !== undefined)
      clearTimeout(OSC.timer.loadGl);
   if (OSC.timer.loadWdb !== undefined)
      clearTimeout(OSC.timer.loadWdb);
   if (OSC.timer.loadWF !== undefined)
      clearTimeout(OSC.timer.loadWF);
}

function reconnect() {
   if (OSC.dlgReconnect.parentElement === undefined)
      return;
   let req = new XMLHttpRequest();
   req.onreadystatechange = function () {
      if (req.readyState === 4 && req.status === 200) {
         // reload page
         location.reload();
      } else if (req.readyState === 4) {
         OSC.timer.reconnect = window.setTimeout(reconnect, 1000);
      }
   };

   req.open("GET", "build", true);
   req.send();
}

function wdSelect(s) {
   OSC.curBoard = s.selectedIndex;
   populateControls(false);
}

function populateAllControls(init) {
   // populate board list
   let sel = document.getElementById("wdSelect");
   for (let i = 0; i < OSC.wdb.length; i++) {
      let opt = document.createElement('option');
      opt.innerHTML = OSC.wdb[i].name;
      opt.value = OSC.wdb[i].name;
      if (sel.childNodes[i + 1] === undefined)
         sel.appendChild(opt);
      else if (sel.childNodes[i + 1].innerHTML !== opt.innerHTML)
         sel.replaceChild(opt, sel.childNodes[i + 1]);
   }

   populateControls(init);
}

function populateControls(init) {
   // populate channel buttons
   for (let i = 0; i < 18; i++)
      OSC.chOn[i] = (OSC.wdb[OSC.curBoard].chnTxEn & (1 << i)) > 0;
   OSC.drawChnButtons();

   // populate config
   if (document.getElementById("inpDacTriggerLevel") !== document.activeElement) {
      document.getElementById("sldDacTriggerLevel").set(OSC.wdb[OSC.curBoard].dacTriggerLevel[0] + 0.5);
      document.getElementById("inpDacTriggerLevel").value = Math.round(OSC.wdb[OSC.curBoard].dacTriggerLevel[0] * 1000);
   }

   if (document.getElementById("inpTriggerDelay") !== document.activeElement) {
      document.getElementById("sldTriggerDelay").set(1 - OSC.wdb[OSC.curBoard].triggerDelay / 1600);
      document.getElementById("inpTriggerDelay").value = Math.round(OSC.wdb[OSC.curBoard].triggerDelay);
   }
   if (OSC.wdb[OSC.curBoard].triggerMode === 1) {
      document.getElementById("rbTriggerModeNormal").checked = true;
      document.getElementById("rbTriggerModeAuto").checked = false;
   } else if (OSC.wdb[OSC.curBoard].triggerMode === 2) {
      document.getElementById("rbTriggerModeNormal").checked = false;
      document.getElementById("rbTriggerModeAuto").checked = true;
   }
   if (document.getElementById("triggerHoldoff") !== document.activeElement) {
      document.getElementById("triggerHoldoff").value = OSC.wdb[OSC.curBoard].triggerHoldoff;
   }
   if (OSC.wdb[OSC.curBoard].triggerSource === 0) {
      document.getElementById("rbTriggerSourceInt").checked = true;
      document.getElementById("rbTriggerSourceExt").checked = false;
   } else if (OSC.wdb[OSC.curBoard].triggerSource === 1) {
      document.getElementById("rbTriggerSourceInt").checked = false;
      document.getElementById("rbTriggerSourceExt").checked = true;
   }

   if (OSC.wdb[OSC.curBoard].triggerLeadTrailEdgeSel) {
      document.getElementById("trgEdgeLead").style.display = "none";
      document.getElementById("trgEdgeTrail").style.display = "inline";
   } else {
      document.getElementById("trgEdgeLead").style.display = "inline";
      document.getElementById("trgEdgeTrail").style.display = "none";
   }

   document.getElementById("cbPzc").checked = OSC.wdb[OSC.curBoard].fePzc[0];
   document.getElementById("selGain").value = OSC.wdb[OSC.curBoard].feGain[0];
   document.getElementById("selPzcLevel").value = OSC.wdb[OSC.curBoard].dacPzcLevel;

   if (OSC.wdb[OSC.curBoard].fePower === -1) {
      document.getElementById("fePower").disabled = true;
      document.getElementById("fePower").checked = false;
   } else {
      document.getElementById("fePower").disabled = false;
      document.getElementById("fePower").checked = (OSC.wdb[OSC.curBoard].fePower === 1)
      ;
   }

   document.getElementById("inputReadoutSrcDRS").checked = (OSC.wdb[OSC.curBoard].readoutSrcSel === 1);
   document.getElementById("inputReadoutSrcADC").checked = (OSC.wdb[OSC.curBoard].readoutSrcSel === 2);
   document.getElementById("inputReadoutSrcTDC").checked = (OSC.wdb[OSC.curBoard].readoutSrcSel === 3);

   document.getElementById("readoutDRSEnable").checked = (OSC.wdb[OSC.curBoard].readoutEnable & 0x1);
   document.getElementById("readoutADCEnable").checked = (OSC.wdb[OSC.curBoard].readoutEnable & 0x2);
   document.getElementById("readoutTDCEnable").checked = (OSC.wdb[OSC.curBoard].readoutEnable & 0x4);
   document.getElementById("readoutTRGEnable").checked = (OSC.wdb[OSC.curBoard].readoutEnable & 0x8);

   document.getElementById("timingCalibSignalEnable").checked = OSC.wdb[OSC.curBoard].timingCalibSignalEnable;

   if (OSC.wdb[OSC.curBoard].dacCalDc > 0.4)
      document.getElementById("selRange").value = -0.45;
   else if (OSC.wdb[OSC.curBoard].dacCalDc < -0.4)
      document.getElementById("selRange").value = 0.45;
   else
      document.getElementById("selRange").value = 0;

   document.getElementById("feMux").checked = (OSC.wdb[OSC.curBoard].feMux[0] === 3);
   document.getElementById("calibBufferEnable").checked = OSC.wdb[OSC.curBoard].calibBufferEnable;

   if (document.getElementById("inpDacCalDc") !== document.activeElement) {
      document.getElementById("sldDacCalDc").set(OSC.wdb[OSC.curBoard].dacCalDc / 1.2 + 0.5);
      document.getElementById("inpDacCalDc").value = Math.round(OSC.wdb[OSC.curBoard].dacCalDc * 1000);
   }

   if (document.getElementById("drsSampleFreq") !== document.activeElement) {
      document.getElementById("drsSampleFreq").value = Math.round(OSC.wdb[OSC.curBoard].drsSampleFreq / 1000 * 10) / 10;
      document.getElementById("drsActualSampleFreq").innerHTML = OSC.wdb[OSC.curBoard].drsSampleFreq / 1000 + " GSPS";
   }
   let s = document.getElementById("timingReferenceSignalSelect");
   s.selectedIndex = OSC.wdb[OSC.curBoard].timingReferenceSignal;

   document.getElementById("calib1").checked = OSC.wp.ofsCalib1;
   document.getElementById("calib2").checked = OSC.wp.ofsCalib2;
   document.getElementById("calib3").checked = OSC.wp.gainCalib;
   document.getElementById("calib4").checked = OSC.wp.rangeCalib;
   document.getElementById("rotate").checked = OSC.wp.rotateWaveform;

   document.getElementById("tcalib1").checked = OSC.wp.timeCalib1;
   document.getElementById("tcalib2").checked = OSC.wp.timeCalib2;
   document.getElementById("tcalib3").checked = OSC.wp.timeCalib3;

   document.getElementById("clksource").checked = (OSC.wdb[OSC.curBoard].daqClkSrcSel === 1);
   document.getElementById("clksource").disabled = OSC.wdb[OSC.curBoard].scaler[18] < 79000000;

   // channels dialog box with FE gain and HV
   if (document.getElementById("inpDacTriggerLevel0") !== null) {
      for (i = 0; i < 16; i++) {
         if (document.getElementById("inpDacTriggerLevel" + i) !== document.activeElement)
            document.getElementById("inpDacTriggerLevel" + i).value = Math.round(OSC.wdb[OSC.curBoard].dacTriggerLevel[i] * 1000);

         document.getElementById("selGain" + i).value = OSC.wdb[OSC.curBoard].feGain[i];
         document.getElementById("cbPzc" + i).checked = OSC.wdb[OSC.curBoard].fePzc[i];

         let e = document.getElementById("inpHvTarget" + i);
         if (e !== document.activeElement)
            e.value = OSC.wdb[OSC.curBoard].hv.target[i];
         document.getElementById("inpHvCurrent" + i).value = OSC.wdb[OSC.curBoard].hv.current[i];
      }
   }

   // trigger pattern dialog box
   for (i = 0; i < 18; i++) {
      let p = document.getElementById(i < 10 ? 'P0' + i : 'P' + i);
      p.enabled = (OSC.wdb[OSC.curBoard].triggerPtrnEn & (1 << i)) > 0;
      if (p.enabled) {
         p.style.backgroundColor = 'darkgreen';
         p.style.color = 'white';
      } else {
         p.style.backgroundColor = '#DDDDDD';
         p.style.color = 'black';
      }

      for (let j = 0; j < 17; j++) {
         let c = document.getElementById('L' + (j < 10 ? '0' + j : j));
         if ((OSC.wdb[OSC.curBoard].triggerSrcPolarity & (1 << j)) === 0)
            c.innerHTML = "+";
         else
            c.innerHTML = "-";
      }

      for (j = 0; j < 17; j++) {
         c = document.getElementById('C' + (j < 10 ? '0' + j : j) + (i < 10 ? '0' + i : i));

         c.mode = 0;
         if ((OSC.wdb[OSC.curBoard].triggerSrcEnPtrn[i] & (1 << j)) === 0)
            c.mode = 0;
         else {
            if ((OSC.wdb[OSC.curBoard].triggerStatePtrn[i] & (1 << j)) > 0)
               c.mode = 1;
            else
               c.mode = 2;
         }
         if (c.mode === 0)
            c.innerHTML = '';
         if (c.mode === 1)
            c.innerHTML = '&bull;';
         if (c.mode === 2)
            c.innerHTML = '&times';
      }
   }

   if (init) {
      // set scale according to sampling frequency
      if (OSC.wdb[OSC.curBoard].drsSampleFreq < 2000)
         OSC.wfTScaleIndex = 6; // 100 ns
      else if (OSC.wdb[OSC.curBoard].drsSampleFreq < 4000)
         OSC.wfTScaleIndex = 5; // 50 ns
      else
         OSC.wfTScaleIndex = 4; // 20 ns
      setTScale();
   }
}

function populateInfo() {
   document.getElementById("infoName").innerHTML = OSC.wdb[OSC.curBoard].name;
   document.getElementById("infoRevision").innerHTML = OSC.wdb[OSC.curBoard].revision;
   document.getElementById("infoFwRevision").innerHTML = OSC.wdb[OSC.curBoard].fwRevision;
   document.getElementById("infoFwBuild").innerHTML = OSC.wdb[OSC.curBoard].fwBuild;
   document.getElementById("infoSwRevision").innerHTML = OSC.wdb[OSC.curBoard].swRevision;
   document.getElementById("infoSwBuild").innerHTML = OSC.wdb[OSC.curBoard].swBuild;

   let i = parseInt(OSC.wdb[OSC.curBoard].name.substr(2));
   let mac = "00-50-c2-46-d4-" + i.toString(16);
   document.getElementById("infoAddress").innerHTML = OSC.wdb[OSC.curBoard].address + " / " + mac;

   document.getElementById("infoBackplanePlugged").innerHTML = OSC.wdb[OSC.curBoard].backplanePlugged;
   document.getElementById("infoCrateSlotID").innerHTML = OSC.wdb[OSC.curBoard].crateId + " / " +
      OSC.wdb[OSC.curBoard].slotId;

   document.getElementById("infoHVVersion").innerHTML = !OSC.wdb[OSC.curBoard].hvBoardPlugged ?
      OSC.wdb[OSC.curBoard].hvVersion : "none";
   document.getElementById("infoHVBaseVoltage").innerHTML = OSC.wdb[OSC.curBoard].hv.baseVoltage.toFixed(3);

   document.getElementById("infoTemp").innerHTML = OSC.wdb[OSC.curBoard].temperature;
   document.getElementById("info1WireTemp").innerHTML =
      OSC.wdb[OSC.curBoard].hv.temperature1Wire[0] + " / " +
      OSC.wdb[OSC.curBoard].hv.temperature1Wire[1] + " / " +
      OSC.wdb[OSC.curBoard].hv.temperature1Wire[2] + " / " +
      OSC.wdb[OSC.curBoard].hv.temperature1Wire[3];

   let s = "";
   for (i = 8; i >= 0; i--) {
      if ((OSC.wdb[OSC.curBoard].pllLck & (1 << 8)) > 0)
         s += "1";
      else
         s += "0";
   }
   document.getElementById("infoPLL").innerHTML = s;

   document.getElementById("infoBusy").innerHTML = OSC.wdb[OSC.curBoard].drsctrlBusy + " / " +
      OSC.wdb[OSC.curBoard].sysBusy;
   document.getElementById("infoTRGParityErrors").innerHTML = OSC.wdb[OSC.curBoard].triggerBusParityErrorCount;

   s = "";
   for (i = 0; i < 16; i++) {
      if ((OSC.wdb[OSC.curBoard].compChannelStatus & (1 << 8)) > 0)
         s += "1";
      else
         s += "0";
      if (i % 4 === 3)
         s += " ";
   }
   document.getElementById("infoCompStatus").innerHTML = s;

   document.getElementById("lastEventNumber").innerHTML = OSC.wdb[OSC.curBoard].lastEventNumber;
   document.getElementById("WPS").innerHTML = OSC.wdb[OSC.curBoard].eventTxRate;
}

function wdbReboot() {
   dlgConfirm("Are you sure?", wdbDoReboot);
}

let progress;

function updateProgress() {
   progress += 0.1;
   d = document.getElementById("progressWait");
   d.set(progress / 15);
   if (progress >= 15)
      dlgHide("dlgWait");
   else
      window.setTimeout(updateProgress, 100);
}

function wdbDoReboot(flag) {
   if (flag) {
      progress = 0;
      dlgShow("dlgWait", true);
      window.setTimeout(updateProgress, 100);

      // send AJAX request
      let req = new XMLHttpRequest();
      req.onreadystatechange = function () {
         if (req.readyState === 4 && req.status === 200) {
            readWdb(-1, init); // daisy-chain for loading all WDBs
         } else if (req.readyState === 4 && req.status === 0) {
            connectionBroken();
         }
      };

      req.open("PUT", "reboot/" + OSC.curBoard + "&" + Math.random(), true); // avoid cached results

      try {
         req.send();
      } catch (e) {
         connectionBroken();
      }
   }
}

function loadGl(init) {
   if (OSC.demoMode) {
      OSC.gl = { demoMode: true, nWdb: 1, updatePeriodic: 0 };
      OSC.wp = { gainCalib: true, ofsCalib1: true, ofsCalib2: true,
                 rangeCalib: true, rotateWaveform: true,
                 timeCalib1: true, timeCalib2: true, timeCalib3: true
      };
      readWdb(-1, init);
      return;
   }
   // send AJAX request
   let req = new XMLHttpRequest();
   req.onreadystatechange = function () {
      if (req.readyState === 4 && req.status === 200) {
         let o = JSON.parse(req.responseText);
         OSC.gl = o.gl;
         OSC.wp = o.wp;
         readWdb(-1, init); // daisy-chain for loading all WDBs
      } else if (req.readyState === 4 && req.status === 0) {
         connectionBroken();
      }
   };

   req.open("GET", "gl?r=" + Math.random(), true); // avoid cached results

   try {
      req.send();
   } catch (e) {
      connectionBroken();
   }
}

function readWdb(b, init) {

   if (OSC.demoMode) {
      return new Promise(function(resolve) {
         if (OSC.wdb === undefined) {
            OSC.wdb = [];
            OSC.wdb[0] = {
               "name": "demo",
               "revision": "G",
               "fwRevision": "N/A",
               "fwBuild": "N/A",
               "swRevision": "N/A",
               "swBuild": "N/A",
               "temperature": 37.5,
               "sysBusy": false,
               "drsctrlBusy": false,
               "packagerBusy": false,
               "hvBoardPlugged": false,
               "hvVersion": "80 V / 10 uA",
               "backplanePlugged": false,
               "pllLck": 511,
               "drsSampleFreq": 5016,
               "adcSampleFreq": 80,
               "tdcSampleFreq": 640,
               "compChannelStatus": 0,
               "lastEventNumber": 0,
               "triggerBusParityErrorCount": 0,
               "triggerBusType": 0,
               "triggerBusNumber": 0,
               "crateId": 0,
               "slotId": 0,
               "readoutSrcSel": 1,
               "daqNormal": false,
               "daqSingle": false,
               "drs0TimingRefSel": 0,
               "drs1TimingRefSel": 0,
               "calibBufferEnable": false,
               "timingCalibSignalEnable": 0,
               "timingReferenceSignal": 0,
               "daqClkSrcSel": 0,
               "extClkInSel": 0,
               "extClkFreq": 0,
               "localClkFreq": 0,
               "calibClkFreq": 100,
               "chnTxEn": 3,
               "dacOfs": 0.000,
               "dacCalDc": 0.000,
               "dacPzcLevel": 1,
               "dacTriggerLevel": new Array(16).fill(0),
               "fePzc": new Array(16).fill(false),
               "feGain": new Array(16).fill(0),
               "feMux": new Array(16).fill(0),
               "fePower": false,
               "triggerMode": 2,
               "triggerLeadTrailEdgeSel": 0,
               "triggerExtTriggerOutEnable": false,
               "triggerSource": 220152992,
               "triggerOutPulseLength": 0,
               "triggerDelay": 0,
               "triggerSrcPolarity": 0,
               "triggerAutoTriggerPeriod": 0,
               "triggerPtrnEn": 0,
               "triggerSrcEnPtrn": new Array(18).fill(0),
               "triggerStatePtrn": new Array(18).fill(0),
               "scaler": new Array(34).fill(0),
               "hv": {
                  "target": new Array(16).fill(0),
                  "current": new Array(16).fill(0),
                  "temperature1Wire": new Array(4).fill(37.5),
                  "baseVoltage": 0
               }
            }
         }

         if (OSC.wdb !== undefined) {
            for (let i = 0; i < 18; i++)
               OSC.wdb[0].scaler[i] = ((Math.random() + Math.random() + Math.random() + Math.random()) * 500).toFixed(0);
         }

         populateAllControls(init);
         populateInfo();
         OSC.connected = true;
         resolve();
      });
   }

   return new Promise(function(resolve, reject) {
      // send AJAX request
      let req = new XMLHttpRequest();
      req.onreadystatechange = function () {
         if (req.readyState === 4 && req.status === 200) {
            if (b === -1)
               OSC.wdb = JSON.parse(req.responseText).wdb;
            else {
               if (OSC.wdb === undefined)
                  OSC.wdb = [];
               OSC.wdb[b] = JSON.parse(req.responseText).wdb[0];
            }

            // remember which input channel is active (needed for trigger level display)
            OSC.wdb[OSC.curBoard].triggerChannelActive = new Array(16).fill(false);
            for (i=0 ; i<16 ; i++) {
               for (j=0 ; j<18 ; j++) {
                  if ((OSC.wdb[OSC.curBoard].triggerSrcEnPtrn[j] & (1 << i)) > 0) {
                     OSC.wdb[OSC.curBoard].triggerChannelActive[i] = true;
                     break;
                  }
               }
            }

            populateAllControls(init);
            populateInfo();
            OSC.connected = true;
            resolve(req);

         } else if (req.readyState === 4 && req.status === 0) {
            connectionBroken();
            reject(req);
         }
      };

      req.open("GET", "wdb?b=" + b + "&r=" + Math.random(), true); // avoid cached results
      req.send();
   });
}

function setCalibClock(e) {
   setParam(e);
   let c = document.getElementById("feMux");
   c.checked = e.checked;
   setParam(c);
   c = document.getElementById("calibBufferEnable");
   c.checked = e.checked;
   setParam(c);
   c = document.getElementById("timingReferenceSignalSelect");
   c.selectedIndex = e.checked ? 1 : 0;
}

function setReferenceSignal(e) {
   setParam(e);
   if (e.selectedIndex === 1) {
      let c = document.getElementById("calibBufferEnable");
      c.checked = true;
      setParam(c);
      c = document.getElementById("timingCalibSignalEnable");
      c.checked = true;
      setParam(c);
   }
}

function setDrsSamplFreq(e) {
   setParam(e);
   loadGl(false);
}

function setParam(e, channel) {
   if (OSC.demoMode)
      return;

   // suppress automatic updates for few seconds, otherwise a pending update
   // could overwrite the current dialog box setting
   OSC.lastParamSet = new Date() / 1000;

   let req = new XMLHttpRequest();

   req.onreadystatechange = function () {
      if (req.readyState === 4 && req.status === 204) {
         // success
         if (e.name === "range") {
            // read back DC offset which gets shifted by range change
            readWdb(-1);
         }
         if (e.name === "drsSampleFreq") {
            // chaning sampling frequency can change calibration flags
            loadGl(false);
         }
      } else if (req.readyState === 4 && req.status === 0) {
         connectionBroken();
      }
   };

   if (e.name === "dacTriggerLevel" && channel === undefined) {
      for (let i = 0; i < 16; i++)
         document.getElementById("inpDacTriggerLevel" + i).value = e.value;
   }

   if (e.name === "feGain" && channel === undefined) {
      for (let i = 0; i < 16; i++)
         document.getElementById("selGain" + i).value = e.value;
   }

   if (e.name === "fePzc" && channel === undefined) {
      for (let i = 0; i < 16; i++)
         document.getElementById("cbPzc" + i).checked = e.checked;
   }

   if (e.name === "clkSource" && e.checked === true) {
      if (OSC.wdb[OSC.curBoard].scaler[17] < 79E6)
         dlgMessage("Error", "No external clock present", true, true);
   }

   let uri = e.name + "/";
   if (OSC.applyAll)
      uri += "ALL";
   else
      uri += OSC.curBoard + "";
   if (channel !== undefined)
      uri += "/" + channel;

   let value = "";
   if (e.type === "select-one") {
      if (e.selectedIndex !== -1) {
         value = e.selectedOptions[0].value;
      }
   } else if (e.type === "checkbox") {
      value = e.checked;
   } else if (e.name === "dacTriggerLevel") {
      value = parseInt(e.value) / 1000;
   } else if (e.name === "dacCalDc") {
      value = parseInt(e.value) / 1000;
   } else if (e.name === "drsSampleFreq") {
      value = parseFloat(e.value) * 1000;
   } else {
      value = e.value;
   }

   req.open("PUT", uri, true);
   req.send(value);

   // set variable locally
   if (OSC.wp[e.name] !== undefined)
      OSC.wp[e.name] = value;
   else if (OSC.wdb[OSC.curBoard][e.name] !== undefined) {
      if (OSC.applyAll) {
         for (let i = 0; i < OSC.wdb.length; i++) {
            if (OSC.wdb[i][e.name] instanceof Array) {
               if (channel === undefined) {
                  for (let j = 0; j < OSC.wdb[i][e.name].length; j++)
                     OSC.wdb[i][e.name][j] = value;
               } else
                  OSC.wdb[i][e.name][channel] = value;
            } else
               OSC.wdb[i][e.name] = value;
         }
      } else {
         if (OSC.wdb[OSC.curBoard][e.name] instanceof Array) {
            // gain, pzc, femux, trigger level arrays
            if (channel === undefined) {
               for (let i = 0; i < OSC.wdb[OSC.curBoard][e.name].length; i++)
                  OSC.wdb[OSC.curBoard][e.name][i] = value;
            } else
               OSC.wdb[OSC.curBoard][e.name][channel] = value;
         } else
            OSC.wdb[OSC.curBoard][e.name] = value;
      }
   }
}

function setDisp(e) {
   if (e.name === "scaler") {
      OSC.disp.scaler = e.checked;
      OSC.resizeCanvas();
      OSC.redraw();
   }
   if (e.name === "invert") {
      OSC.disp.invert = e.checked;
      OSC.newImage = true;
      OSC.redraw();
   }
}

function setPers(s) {
   OSC.clearPersistency();
   OSC.redraw();
   OSC.disp.persistency = parseFloat(s.value);
}

function keyParam(event, input, channel) {
   let charCode = (typeof event.which == "number") ? event.which : event.keyCode;

   if (charCode === 13) {
      validateParam(input, channel);
      input.focus();
      input.setSelectionRange(0, input.value.length);
   }
}

function validateParam(input, channel) {
   if (input.id.substring(0, 18) === "inpDacTriggerLevel") {
      if (input.value < -500)
         input.value = -500;
      if (input.value > 500)
         input.value = 500;
      if (input.id === "inpDacTriggerLevel")
         document.getElementById("sldDacTriggerLevel").set(input.value / 1000 + 0.5);
   }

   if (input.id === "inpTriggerDelay") {
      if (input.value < 0)
         input.value = 0;
      if (input.value > 1600)
         input.value = 1600;
      document.getElementById("sldTriggerDelay").set(1 - input.value / 1600);
   }

   if (input.id === "drsSampleFreq") {
      let divider = Math.round(240.0 / input.value * 2.048);
      divider = 2 * Math.floor(divider / 2);
      OSC.wdb[OSC.curBoard].drsSampleFreq = Math.round(240 / divider * 2048);
      document.getElementById("drsActualSampleFreq").innerHTML = OSC.wdb[OSC.curBoard].drsSampleFreq / 1000 + " GSPS";
   }

   if (input.id === "inpDacCalDc") {
      if (input.value < -1000)
         input.value = -1000;
      if (input.value > 1000)
         input.value = 1000;
      document.getElementById("sldDacCalDc").set(input.value / 1200 + 0.5);
   }

   if (input.id.substr(0, 11) === "inpHvTarget") {
      if (input.value < 0)
         input.value = 0;
      if (input.value > 210)
         input.value = 210;
   }

   setParam(input, channel);
}

function doVCalib(all) {
   dlgHide("dlgVCalib");
   if (OSC.demoMode) {
      alert("Not available in demo mode");
      return;
   }
   progressOldBoard = OSC.curBoard;

   let req = new XMLHttpRequest();
   if (all)
      req.open("PUT", "vcalib/ALL");
   else
      req.open("PUT", "vcalib/" + OSC.curBoard);
   req.send();
}

function doTCalib(all) {
   dlgHide("dlgTCalib");
   if (OSC.demoMode) {
      alert("Not available in demo mode");
      return;
   }
   progressOldBoard = OSC.curBoard;

   let req = new XMLHttpRequest();
   if (all)
      req.open("PUT", "tcalib/ALL");
   else
      req.open("PUT", "tcalib/" + OSC.curBoard);
   req.send();
}

function loadBuild() {
   if (OSC.demoMode) {
      let e = document.getElementById("build");
      e.innerHTML = "Demo Mode";
      return;
   }
   // send AJAX request
   let req = new XMLHttpRequest();
   req.onreadystatechange = function () {
      if (req.readyState === 4 && req.status === 200) {
         let build = JSON.parse(req.responseText);
         let e = document.getElementById("build");
         e.innerHTML = "Built " + build.build;
      } else if (req.readyState === 4 && req.status === 0) {
         connectionBroken();
      }
   };
   req.open("GET", "build?r=" + Math.random(), true); // avoid cached results

   try {
      req.send();
   } catch (e) {
      connectionBroken();
   }
}

function loadWF() {
   // wait until list of boards has been loaded
   if (!OSC.connected) {
      OSC.timer.loadWF = window.setTimeout(loadWF, 10);
      return;
   }

   let i, c, chn;

   if (OSC.demoMode) {
      // create 18 empty waveforms
      let wf = {T: [], U: []};
      OSC.i1 = 0;
      OSC.i2 = 1023;
      for (c = 0; c < 20; c++) {
         wf.T[c] = [];
         wf.U[c] = [];
         for (i = 0; i < 1024; i++) {
            let t = i * 1E-6 / OSC.wdb[OSC.curBoard].drsSampleFreq;
            wf.T[c][i] = t;
            wf.U[c][i] = Math.sin((wf.T[c][i] + c * 1E-6) * OSC.wdb[OSC.curBoard].drsSampleFreq /
                  1E-6 / 50) / 4 + (Math.random() - 0.5) / 300;

            let xt = OSC.timeToX(t);
            if (OSC.i1 === 0 && xt >= OSC.x1)
               OSC.i1 = i;
            if (xt <= OSC.x2)
               OSC.i2 = i;
         }
         // add spikes
         for (i = 0; i < 1024; i++) {
            if (Math.random() < 0.00005) {
               let s = (Math.random() - 0.5) / 5;
               let j = i - 5;
               for (let f = 0; f < 1; f += 0.2, j++)
                  if (j >= 0 && j < 1024)
                     wf.U[c][j] += s * f;
               for (f = 1; f > 0; f -= 0.2, j++)
                  if (j >= 0 && j < 1024)
                     wf.U[c][j] += s * f;
            }
         }
      }

      OSC.idle = false;

      if (OSC.running)
         OSC.timer.loadWF = window.setTimeout(loadWF, 0); // schedule next waveform read

      // calculate sum and FFT waveforms
      calcMathWF(wf);

      OSC.sendWaveforms(wf);
      OSC.redraw();
      return;
   }

   // build mask with active channels
   for (chn = 0, c = 0; c < 18; c++)
      if (OSC.chOn[c])
         chn |= (1 << c);

   for (i = 0; i < OSC.measList.childNodes.length; i++)
      if (OSC.measList.childNodes[i].measurement) {
         for (let p = 0; p < OSC.measList.childNodes[i].measurement.param.length; p++) {
            if (OSC.measList.childNodes[i].measurement.param[p].type === "CH")
               chn |= (1 << OSC.measList.childNodes[i].measurement.param[p].value);
         }
      }

   if (chn === 0 && OSC.running) {
      OSC.timer.loadWF = window.setTimeout(loadWF, 0); // schedule next waveform read
      return;
   }

   // send AJAX request
   OSC.req = new XMLHttpRequest();
   OSC.req.onreadystatechange = receiveWF;
   OSC.req.open("GET", "wf?b=" + OSC.curBoard + "&c=" + chn + "&r=" + Math.random(), true); // avoid cached results
   OSC.req.responseType = "arraybuffer";

   try {
      OSC.req.send();
   } catch (e) {
      connectionBroken();
   }
}

function receiveWF() {
   if (OSC.req.readyState === 4 && OSC.req.status === 200) {
      // this.wf = JSON.parse(OSC.req.responseText); // use this for JSON encoded data

      // create 16+2+2 empty waveforms
      let wf = {T: [], U: [], type: 1};
      for (let i = 0; i < 20; i++) {
         wf.T[i] = [];
         wf.U[i] = [];
      }

      let intArray = new Uint32Array(OSC.req.response);
      let charArray = new Uint8Array(OSC.req.response);
      let floatArray = new Float32Array(OSC.req.response);
      let responsetype;

      for (i = 0; i < intArray.length;) {
         responseType = intArray[i];

         if (responseType === 0) {        // idle message
            OSC.idle = true;
            break;
         } else if (responseType === 1) { // time array
            i++;
            OSC.wd = intArray[i++];
            OSC.tCalibrated = intArray[i++];
            OSC.nLogged = intArray[i++];
            let c = intArray[i++];
            let n = intArray[i++];
            OSC.i1 = undefined;
            OSC.i2 = undefined;
            for (let j = 0; j < n; j++) {
               let t = floatArray[i++];
               wf.T[c][j] = t;
               let xt = OSC.timeToX(t);
               if (OSC.i1 === undefined && xt >= OSC.x1)
                  OSC.i1 = j;
               if (xt <= OSC.x2)
                  OSC.i2 = j;
            }

            // check for progress bar
            if (progressInd > 0) {
               progressInd = 0;
               let e = document.getElementById("progressIndVcalib");
               e.set(0);
               e = document.getElementById("progressIndTcalib");
               e.set(0);

               OSC.clearPersistency();

               document.getElementById("wdSelect").selectedIndex = progressOldBoard;
               document.getElementById("btnVCalib").innerHTML = "Execute Voltage Calibration";
               document.getElementById("btnVCalib").disabled = false;
               document.getElementById("btnTCalib").innerHTML = "Execute Time Calibration";
               document.getElementById("btnTCalib").disabled = false;
               OSC.curBoard = progressOldBoard;

               OSC.timer.loadGl = window.setTimeout(loadGl, 10);
            }

         } else if (responseType === 2) { // voltage array
            i++;
            OSC.idle = false;
            OSC.wd = intArray[i++];
            OSC.vCalibrated = intArray[i++];
            OSC.nLogged = intArray[i++];
            c = intArray[i++];
            n = intArray[i++];
            for (j = 0; j < n; j++)
               wf.U[c][j] = floatArray[i++];
            OSC.remoteDemo = (OSC.wd === 0xFF);

         } else if (responseType === 3) { // tdc array
            i++;
            OSC.idle = false;
            OSC.wd = intArray[i++];
            OSC.vCalibrated = intArray[i++];
            OSC.nLogged = intArray[i++];
            c = intArray[i++];
            n = intArray[i++];
            for (j = 0; j < n; j++){
               wf.U[c][j] = charArray[4*i+j];
            }
            i += n/4;
            OSC.remoteDemo = (OSC.wd === 0xFF);


         } else if (responseType === 10) { // vcalib progress data
            let b = intArray[1];
            progressInd = floatArray[2];

            e = document.getElementById("progressIndVcalib");
            e.set(progressInd);

            document.getElementById("wdSelect").selectedIndex = b;
            document.getElementById("btnVCalib").innerHTML = document.getElementById("wdSelect").value;
            document.getElementById("btnVCalib").disabled = true;

            OSC.timer.loadWF = window.setTimeout(loadWF, 250);
            return;

         } else if (responseType === 11) { // tcalib progress data
            let b = intArray[1];
            progressInd = floatArray[2];
            i += 3;

            wf.type = 2; // indicate delta-T array

            e = document.getElementById("progressIndTcalib");
            e.set(progressInd);

            document.getElementById("wdSelect").selectedIndex = b;
            document.getElementById("btnTCalib").innerHTML = document.getElementById("wdSelect").value;
            document.getElementById("btnTCalib").disabled = true;

            while (i < intArray.length) {
               c = intArray[i++];
               n = intArray[i++];
               for (j = 0; j < n; j++)
                  wf.T[c][j] = floatArray[i++];
            }

         } else if (responseType === 12) { // tcalib error
            dlgMessage("Error", "Board has no calibration oscillator", true, true);
            break;
         } else {
            dlgMessage("Error", "Invalid binary data received form server", true, true);
            break;
         }
      }

      // calculate sum and FFT waveforms
      calcMathWF(wf);

      if (responseType === 11) {
         OSC.timer.loadWF = window.setTimeout(loadWF, 250);
         OSC.sendWaveforms(wf);

      } else {
         // schedule next waveform read
         if (OSC.running)
            OSC.timer.loadWF = window.setTimeout(loadWF, 0);

         // send waveforms to oscilloscope
         if (!OSC.idle)
            OSC.sendWaveforms(wf);
      }

      // redraw oscilloscope to show new waveforms
      OSC.redraw();

      // if logging file is complete, load it
      if (OSC.logFlag && OSC.nLogged === OSC.nRequested) {
         OSC.logFlag = false;

         let e = document.getElementById('btnSave');
         e.innerHTML = "Save";
         e.style.border = "2px solid #C0C0C0";

         // trigger loading of file
         downloadFile(OSC.logfile);
      }
   } else if (OSC.req.readyState === 4 && OSC.req.status === 0) {
      connectionBroken();
   }
}

function calcMathWF(wf)
{
   // add sum waveform
   if (OSC.chOn[18]) {
      for (let i = 0; i < 1024; i++) {
         wf.U[18][i] = 0;
         for (let j = 0; j < 16; j++)
            if (OSC.chOn[j]) {
               wf.T[18][i] = wf.T[j][i];
               wf.U[18][i] += wf.U[j][i];
            }
      }
   }

   // add FFT waveform
   if (OSC.chOn[19]) {
      let w = [];
      let t = [];
      let e = document.getElementById('chnFft');
      let c = e.options[e.selectedIndex].value;


      for (i = 1; i < 1024; i++)
         w[i] = wf.U[c][i];

      /*
       // resample channel

       for (let i = 0; i < 1024; i++)
       t[i] = i * 1E-6 /OSC.wdb[OSC.curBoard].drsSampleFreq;

       w[0] = wf.U[c][0];
       for (i=1; i < 1024; i++) {
       w[i] = wf.U[c][i];
       }

       console.log("----------");
       for (i=0 ; i<10 ; i++)
       console.log((wf.T[0][i]*1E9).toFixed(3)+" "+wf.U[0][i].toFixed(3));

       console.log("");
       for (i=0 ; i<10 ; i++)
       console.log((t[i]*1E9).toFixed(3)+" "+w[i].toFixed(3));
       */


      w[0] = w[1]; // fix for spike

      fft(w);

      for (i = 0; i < 512; i++)
         wf.U[19][i] = Math.log(w[i]);
      wf.T[19] = wf.T[19].slice(0, 512);
      wf.U[19] = wf.U[19].slice(0, 512);
   }
}

/*---- UI event handler ----*/

function resize()
// called when screen got resized
{
   let ctls = document.getElementById("controls");
   let config = document.getElementById("config");

   if (ctls.hidden === true) {
      // hide panels
      ctls.style.display = "none";
      config.style.display = "none";
      OSC.resize(document.documentElement.clientWidth,
         document.documentElement.clientHeight);
   } else {
      ctls.style.display = "block";
      ctls.style.opacity = 1; // make it visible again (pre-hidden in CSS)

      if (config.slider > 0)
         config.style.display = "block";
      else
         config.style.display = "none";
      config.style.opacity = 1;

      OSC.resize(document.documentElement.clientWidth - ctls.offsetWidth -
         config.offsetWidth * config.slider -
         document.documentElement.clientHeight);

      // config full visible (configSlider = 1), hidden (configSlider = 0)
      ctls.style.left = (document.documentElement.clientWidth - ctls.offsetWidth -
         config.offsetWidth * config.slider + "px");
      ctls.style.height = document.documentElement.clientHeight + "px";

      config.style.left = (document.documentElement.clientWidth -
         config.offsetWidth * config.slider) + "px";
      config.style.height = document.documentElement.clientHeight + "px";

      OSC.resize(document.documentElement.clientWidth - ctls.offsetWidth -
         config.offsetWidth * config.slider,
         document.documentElement.clientHeight);
   }
}

function oscKeypress(e) {
   let charCode = (typeof e.which === "number") ? e.which : e.keyCode;

   // check if for some dialog box etc.
   if (e.target !== document.body && e.target.id !== "btnHelp")
      return;

   if (charCode === ' '.charCodeAt(0)) {
      btnStop();
   }

   if (charCode === 's'.charCodeAt(0)) {
      btnSingle();
   }

   if (charCode === ']'.charCodeAt(0)) {
      let ctls = document.getElementById("controls");
      ctls.hidden = !ctls.hidden;
      resize();
   }

   if (charCode === 'c'.charCodeAt(0)) {
      btnConfig();
   }

   if (charCode === 'a'.charCodeAt(0)) {
      btnChnAll();
   }

   if (charCode >= '0'.charCodeAt(0) && charCode <= '9'.charCodeAt(0)) {
      let c = charCode - '0'.charCodeAt(0);
      for (let i = 0; i < 20; i++)
         OSC.chOnSelected[i] = (i === c);
      OSC.drawChnButtons();
   }

   if (charCode === 'o'.charCodeAt(0)) {
      btnOn();
   }

   if (charCode === '^'.charCodeAt(0)) {
      btnOfsDist();
   }

   if (charCode === 'v'.charCodeAt(0)) {
      btnOfsZero();
   }

}

function btnStop()
// start/stop oscilloscope
{
   let e = document.getElementById("btnStop");
   if (OSC.running) {
      OSC.running = false;
      e.innerHTML = "Start";
      e.style.backgroundColor = "#FFA0A0";
   } else {
      OSC.running = true;
      e.innerHTML = "Stop";
      e.style.backgroundColor = "#A0FFA0";
      OSC.timer.loadWF = window.setTimeout(loadWF, 10);
   }
}

function btnSingle()
// trigger single acquisition
{
   if (OSC.running) {
      let e = document.getElementById("btnStop");
      OSC.running = false;
      e.innerHTML = "Start";
      e.style.backgroundColor = "#FFA0A0";
   }

   OSC.timer.loadWF = window.setTimeout(loadWF, 10);
}

function enableDRSChannels() {
   let mask = 0;
   for (let i = 0; i < 18; i++)
      if (OSC.chOn[i])
         mask |= (1 << i);

   OSC.wdb[OSC.curBoard].chnTxEn = 0;
   for (let i = 0; i < 18; i++)
      if (OSC.chOn[i])
         OSC.wdb[OSC.curBoard].chnTxEn |= (1 << i);

   if (OSC.demoMode)
      return;

   let req = new XMLHttpRequest();

   if (OSC.applyAll) {
      for (let i = 0; i < OSC.wdb.length; i++)
         OSC.wdb[i].chnTxEn = OSC.wdb[OSC.curBoard].chnTxEn;
      req.open("PUT", "/enableChannel/ALL", true);
   } else {
      req.open("PUT", "/enableChannel/" + OSC.curBoard, true);
   }
   req.send(mask);
}

function btnChnAll() {
   let i;

   for (i = 0; i < 16; i++)
      OSC.chOnSelected[i] = true;

   // set scale according to first active channel
   for (i = 0; i < 19; i++)
      if (OSC.chOn[i])
         break;
   if (i === 18)
      i = 0;
   document.getElementById("UScale").innerHTML = OSC.UScaleTable[OSC.wfScaleIndex[i]][1];

   document.getElementById("chOn").innerHTML = "On";

   OSC.drawChnButtons();
}

function btnChn(event, c)
// select channel "c" and set controls to reflect channel status (c === -1 means all channels)
{
   event.preventDefault(); // suppress context menu for Ctrl-click

   // unselect all channels
   if (!event.ctrlKey && !event.shiftKey)
      for (let i = 0; i < 20; i++)
         if (i !== c)
            OSC.chOnSelected[i] = false;

   if (event.shiftKey) {
      // find last selected channel
      let last;
      for (last = 15; last >= 0; last--)
         if (OSC.chOnSelected[last])
            break;
      // select all channels betweeen last and current
      if (c > last)
         for (let i = last; i < c; i++)
            OSC.chOnSelected[i] = true;
      if (c < last)
         for (let i = last; i > c; i--)
            OSC.chOnSelected[i] = true;
   }

   // if channel already selected, toggle it
   if (OSC.chOnSelected[c])
      OSC.chOn[c] = !OSC.chOn[c];  // if current channel clicked, toggle it
   else
      OSC.chOn[c] = true;          // if other channel clicked, enable it

   // select current channel
   OSC.chOnSelected[c] = true;

   if (c < 16) {
      let o = document.getElementById("chOn");
      o.innerHTML = OSC.chOn[c] ? "Off" : "On";
   }

   // set scale according to channel
   document.getElementById("UScale").innerHTML = OSC.UScaleTable[OSC.wfScaleIndex[c]][1];

   enableDRSChannels();
   OSC.clearPersistency();
   OSC.drawChnButtons();
   OSC.redraw();
}

function btnOn()
// turn current channel(s) on and off
{
   for (let i = 0; i < 16; i++) {
      if (!OSC.chOnSelected[i])
         continue;
      let cb = document.getElementById("ch" + i);
      let bt = document.getElementById("chOn");
      if (bt.innerHTML === "On") {
         OSC.chOn[i] = true;
         cb.style.backgroundColor = OSC.chnColors[i];
      } else {
         OSC.chOn[i] = false;
         cb.style.backgroundColor = "#E0E0E0";
      }
   }
   if (bt !== undefined)
      bt.innerHTML = bt.innerHTML === "On" ? "Off" : "On";

   enableDRSChannels();
   OSC.clearPersistency();
   OSC.redraw();
}

function btnScale(inc)
// change vertical scale, update label
{
   for (let i = 0; i < 19; i++)
      if (OSC.chOnSelected[i])
         break;
   if (i === 19)
      i = 0;

   let index = OSC.wfScaleIndex[i] + inc;
   if (index < 0)
      index = 0;
   if (index === OSC.UScaleTable.length)
      index--;

   for (i = 0; i < 19; i++) {
      if (!OSC.chOnSelected[i])
         continue;

      OSC.wfScaleIndex[i] = index;
      OSC.wfScale[i] = OSC.UScaleTable[OSC.wfScaleIndex[i]][0];
      document.getElementById("UScale").innerHTML = OSC.UScaleTable[OSC.wfScaleIndex[i]][1];
   }
   OSC.clearPersistency();
   OSC.calcScaleOffset();
   OSC.redraw();
}

function btnTScale(inc)
// change horizontal scale, update label
{
   let index = OSC.wfTScaleIndex + inc;
   if (index < 0)
      index = 0;
   if (index === OSC.TScaleTable.length)
      index--;

   OSC.wfTScaleIndex = index;
   setTScale();
}

function setTScale() {
   OSC.wfTScale = OSC.TScaleTable[OSC.wfTScaleIndex][0];
   document.getElementById("TScale").innerHTML = OSC.TScaleTable[OSC.wfTScaleIndex][1];

   document.getElementById("tofsSlider").set(0.5);
   sldTOffset(0.5);
   clearStat();
   OSC.calcScaleOffset();
   OSC.redraw();
}

function sldUOffset(value) {
   for (let i = 0; i < 19; i++) {
      if (!OSC.chOnSelected[i])
         continue;
      OSC.wfOffset[i] = value - 0.5;
   }
   OSC.calcScaleOffset();
   OSC.clearPersistency();
   OSC.redraw();
}

function setSldUOffset(value) {
   document.getElementById("uofsSlider").set(value);
}

var tLevelLast = -1;

function sldDacTriggerLevel(value) {
   if (OSC.demoMode)
      return;

   value = Math.round((value - 0.5) * 1000) / 1000; // convert to V

   if (value === tLevelLast) // only send if changed
      return;

   tLevelLast = value;

   document.getElementById("inpDacTriggerLevel").value = value * 1000;
   setParam(document.getElementById("inpDacTriggerLevel"));

   let d = new Date();
   OSC.lastTriggerLevelChange = d.getTime();
   clearStat();
   OSC.redraw();
}

function sldTriggerDelay(value) {
   if (OSC.demoMode)
      return;
   let del = 1600 - Math.round(value * 1600);

   OSC.wdb[OSC.curBoard].triggerDelay = del;
   document.getElementById("inpTriggerDelay").value = del;
   let e = {};
   e.name = "triggerDelay";
   e.value = del;
   setParam(e);
   clearStat();
}

function btnTedge(value) {
   if (OSC.demoMode)
      return;

   let e = {};
   e.name = "triggerLeadTrailEdgeSel";
   e.value = value;
   setParam(e);

   for (let i=0 ; i<18 ; i++)
      triggerSendCell(i);

   if (value === 1) {
      document.getElementById('trgEdgeLead').style.display = "none";
      document.getElementById('trgEdgeTrail').style.display = "inline";
   } else {
      document.getElementById('trgEdgeLead').style.display = "inline";
      document.getElementById('trgEdgeTrail').style.display = "none";
   }
}

function sldDacCalDc(value) {
   if (OSC.demoMode)
      return;

   document.getElementById("inpDacCalDc").value = Math.round((value * 1200 - 600)/10)*10;
   setParam(document.getElementById("inpDacCalDc"));
}

function setRange(s) {
   if (OSC.demoMode)
      return;

   let e = {};
   e.name = "range";
   e.value = parseFloat(s.value);
   setParam(e);
}

function btnOfsZero() {
   for (i = 0; i < 19; i++) {
      if (OSC.chOn[i])
         OSC.wfOffset[i] = 0;
   }
   OSC.clearPersistency();
   OSC.calcScaleOffset();
   OSC.redraw();

   let sl = document.getElementsByName("ctrlVSlider");
   sl[0].position = 0.5;
   sl[0].draw();
}

function btnOfsDist() {
   // count active channels
   let n = 0;
   for (i = 0; i < 19; i++) {
      if (OSC.chOn[i])
         n++;
   }

   // calculate offset between channels
   let d = 1 / (n + 1);

   // set offset
   let o = 0.5 - d;
   for (i = 0; i < 19; i++) {
      if (OSC.chOn[i]) {
         OSC.wfOffset[i] = o;
         o -= d;
      }
   }
   OSC.clearPersistency();
   OSC.calcScaleOffset();
   OSC.redraw();
}

function sldTOffset(value) {
   let wfWidth=0;
   if(OSC.wdb[OSC.curBoard].readoutSrcSel === 1)
      wfWidth = 1024. / OSC.wdb[OSC.curBoard].drsSampleFreq * 1E-6;
   else if (OSC.wdb[OSC.curBoard].readoutSrcSel === 2)
      wfWidth = 1024. / OSC.wdb[OSC.curBoard].adcSampleFreq * 1E-6;
   else if (OSC.wdb[OSC.curBoard].readoutSrcSel === 3)
      wfWidth = 512. / OSC.wdb[OSC.curBoard].adcSampleFreq * 1E-6;

   let scWidth = OSC.wfTScale * 10;
   if (wfWidth >= scWidth)
      OSC.wfTOffset = 0.9 * scWidth - wfWidth - value * (0.8 * scWidth - wfWidth);
   else
      OSC.wfTOffset = 0.9 * scWidth - wfWidth - (1 - value) * (0.8 * scWidth - wfWidth);

   clearStat();
   OSC.clearPersistency();
   OSC.calcScaleOffset();
   OSC.redraw();
}

function setSldTOffset(tOffset)
{
   let wfWidth=0;
   if(OSC.wdb[OSC.curBoard].readoutSrcSel === 1)
      wfWidth = 1024. / OSC.wdb[OSC.curBoard].drsSampleFreq * 1E-6;
   else if (OSC.wdb[OSC.curBoard].readoutSrcSel === 2)
      wfWidth = 1024. / OSC.wdb[OSC.curBoard].adcSampleFreq * 1E-6;
   else if (OSC.wdb[OSC.curBoard].readoutSrcSel === 2)
      wfWidth = 512. / OSC.wdb[OSC.curBoard].adcSampleFreq * 1E-6;

   let scWidth = OSC.wfTScale * 10;
   if (wfWidth >= scWidth)
      value = (0.9 * scWidth - wfWidth - tOffset) / (0.8 * scWidth - wfWidth);
   else
      value = 1 - (0.9 * scWidth - wfWidth - tOffset) / (0.8 * scWidth - wfWidth);

   let s = document.getElementById("tofsSlider");
   s.set(value);

   sldTOffset(value);
}

function btnConfig() {
   let config = document.getElementById("config");
   config.visible = !config.visible;
   config.t = 0;
   window.setTimeout(configSlide, 20);
}

function btnSave() {
   if (OSC.demoMode) {
      alert("Not available in demo mode");
      return;
   }

   let e = document.getElementById('btnSave');
   if (e.innerHTML === "Stop") {
      let req = new XMLHttpRequest();

      req.onreadystatechange = function () {
         if (req.readyState === 4 && req.status === 204) {
            downloadFile(OSC.logfile);
         }
      };

      req.open("PUT", "save", true);
      req.send("stop");

      OSC.logFlag = false;
      e.innerHTML = "Save";
      e.style.border = "2px solid #C0C0C0";

   } else {
      dlgShow('dlgSave');
      document.getElementById('filename').focus();
   }
}

function btnStart() {
   if (OSC.demoMode)
      return;

   // check for download attribute
   let link = document.createElement("a");
   let filename = document.getElementById("filename").value;
   if (!("download" in link)) {
      alert("Downloading of files in not supported in your browser. Please use Firefox or Chrome.");
      return;
   }

   if (document.getElementById("filename").value === "") {
      dlgMessage("Error", "Please enter a valid file name", true, true);
      return;
   }

   let ne = document.getElementById("nevents").value;
   if (isNaN(parseInt(ne)) || parseInt(ne) < 1 || parseInt(ne) > 1E6) {
      dlgMessage("Error", "Please enter a valid number of events", true, true);
      return;
   }

   if (document.getElementById("saveboards").selectedOptions[0].value === "all") {
      dlgMessage("Error", "Saving all boards only works with a global crate trigger", true, true);
      return;
   }

   let b = document.getElementById('btnSave');
   b.innerHTML = "Stop";
   b.style.border = "3px solid #00A0FF";

   OSC.logfile = filename;
   OSC.nRequested = parseInt(ne);
   OSC.nLogged = 0;

   let req = new XMLHttpRequest();
   req.onreadystatechange = function () {
      if (req.readyState === 4 && req.status === 204) {
         OSC.logFlag = true;
      }
   };

   let param = OSC.logfile;
   param += "\n";
   param += document.getElementById("fileformat").selectedOptions[0].value;
   param += "\n";
   param += document.getElementById("saveboards").selectedOptions[0].value === "all" ? "all" : OSC.curBoard;
   param += "\n";
   param += ne;
   req.open("PUT", "save", true);
   req.send(param);

   dlgHide('dlgSave');
}

function btnVcalib() {
   if (OSC.wdb.length > 1)
      dlgShow('dlgVCalib');
   else
      doVCalib(false);
}

function btnTcalib() {
   if (OSC.wdb.length > 1)
      dlgShow('dlgTCalib');
   else
      doTCalib(false);
}

function downloadFile(filename) {
   let link = document.createElement("a");
   document.body.appendChild(link);
   link.download = filename;
   link.href = filename;
   link.click();
   document.body.removeChild(link);
   window.URL.revokeObjectURL(filename);
}

function configSlide() {
   let config = document.getElementById("config");

   //config.t += 1;
   config.t += 10;

   if (config.visible) {
      config.slider = 1 - (1 - config.t / 10) * (1 - config.t / 10);
   } else {
      config.slider = (1 - config.t / 10) * (1 - config.t / 10);
   }

   resize();

   if (config.t < 10)
      window.setTimeout(configSlide, 20);
}

function measRem() {
   this.parentNode.parentNode.removeChild(this.parentNode);
   setCursorsOff();
}

function measAdd() {
   // remove hint on first call
   let h = document.getElementById("addHint");
   if (h)
      h.parentNode.removeChild(h);

   let l = document.getElementById("measList");

   // overall <div> for measurement
   let meas = document.createElement("div");
   l.insertBefore(meas, l.childNodes[l.childNodes.length - 2]);

   let prev;
   if (l.childNodes.length > 6)
      prev = l.childNodes[l.childNodes.length - 4].measurement;

   // create measurement object and attach it to <div>
   meas.measurement = new Measurement();

   // minus button
   let b = document.createElement("button");
   b.type = "button";
   b.className = "plusButton";
   b.style.color = "red";
   b.onclick = measRem;
   b.innerHTML = "-";
   meas.appendChild(b);

   // Measurement select
   let s = document.createElement("select");
   s.className = "measSelect";
   s.onchange = function () {
      measSelect(meas, s);
   };
   for (let i = 0; i < measList.length; i++) {
      o = document.createElement("option");
      o.value = measList[i].name;
      o.innerHTML = measList[i].name;
      if (prev) {
         if (measList[i].name === prev.name)
            o.selected = true;
      }
      s.appendChild(o);
   }
   meas.appendChild(s);

   measSelect(meas, s, prev);
}

function measSelect(meas, sel, prev) {

   OSC.timeCursor.on = false; // remove any cursor
   OSC.voltageCursor.on = false;

   // remove previous input fields
   for (let i = meas.childNodes.length - 1; i > 1; i--)
      meas.removeChild(meas.childNodes[i]);

   meas.measurement.setFunc(sel.value);

   // add input fields for measurement
   let input = [];
   for (let pi = 0; pi < meas.measurement.param.length; pi++) {

      if (meas.measurement.param[pi].type === "WD") {
         input[pi] = document.createElement("select");
         input[pi].className = "measSelect";
         input[pi].onchange = function () {
            measParamChange(meas);
         };
         for (i = 0; i < OSC.wdb.length; i++) {
            let o = document.createElement("option");
            o.value = i;
            o.innerHTML = OSC.wdb[i].name;
            if (prev) {
               if (prev.param[pi].value === i)
                  o.selected = true;
            }
            input[pi].appendChild(o);
         }
         meas.appendChild(input[pi]);
      }
      else if (meas.measurement.param[pi].type === "CH") {
         input[pi] = document.createElement("select");
         input[pi].className = "measSelect";
         input[pi].onchange = function () {
            measParamChange(meas);
         };
         for (i = 0; i < 19; i++) {
            o = document.createElement("option");
            o.value = i;
            if (i === 18)
               o.innerHTML = "SUM";
            else
               o.innerHTML = "CH" + i;
            if (prev) {
               if (prev.param[pi].value + 1 === i)
                  o.selected = true;
            }
            input[pi].appendChild(o);
         }
         meas.appendChild(input[pi]);
      }
      else {
         input[pi] = document.createElement("input");
         input[pi].type = "text";
         input[pi].size = 10;
         input[pi].style.width = "50px";
         input[pi].value = meas.measurement.param[pi].value;
         input[pi].onchange = function () {
            measParamChange(meas);
         };

         if (meas.measurement.param[pi].type === "tcursor")
            input[pi].addEventListener('focus', function(e) {
               OSC.timeCursor.on = true;
               OSC.voltageCursor.on = false;
               OSC.timeCursor.input = this;
               OSC.timeCursor.time = this.value;
            }, false);

         else if (meas.measurement.param[pi].type === "ucursor")
            input[pi].addEventListener('focus', function(e) {
               OSC.timeCursor.on = false;
               OSC.voltageCursor.on = true;
               OSC.voltageCursor.input = this;
               OSC.voltageCursor.voltage = this.value;
               OSC.voltageCursor.channel = meas.measurement.param[1].value;
            }, false);

         else
            input[pi].addEventListener('focus', function(e) {
               setCursorsOff();
            }, false);

         let text = document.createElement("span");
         text.innerHTML = "&nbsp;" + meas.measurement.param[pi].name + ":&nbsp;";
         meas.appendChild(text);
         meas.appendChild(input[pi]);
      }

      measParamChange(meas);
   }

}

function measParamChange(meas) {
   let n = 0;
   for (let i = 2; i < meas.childNodes.length; i++) {
      if (meas.childNodes[i].type) {
         meas.measurement.param[n++].value = parseFloat(meas.childNodes[i].value);
         meas.measurement.resetStat();
      }
   }
}

function measZoomIn() {
   OSC.histo.autoAxis = false;

   let x = OSC.histo.xMax;
   let d = 0.25 * (OSC.histo.axisMax - OSC.histo.axisMin);

   OSC.histo.axisMin = x - d;
   OSC.histo.axisMax = x + d;
}

function measZoomOut() {
   OSC.histo.autoAxis = false;
   let d = 0.5 * (OSC.histo.axisMax - OSC.histo.axisMin);
   OSC.histo.axisMin -= d;
   OSC.histo.axisMax += d;
}

function measZoomFit() {
   OSC.histo.autoAxis = true;
}

function measLogY() {
   OSC.histo.logY = ! OSC.histo.logY;
}

function measFilter() {
   OSC.histo.filter = ! OSC.histo.filter;
}

function setNStat(v) {
   for (i = 0; i < OSC.measList.childNodes.length; i++)
      if (OSC.measList.childNodes[i].measurement)
         OSC.measList.childNodes[i].measurement.setNStat(v);
}

function clearStat() {
   for (i = 0; i < OSC.measList.childNodes.length; i++)
      if (OSC.measList.childNodes[i].measurement)
         OSC.measList.childNodes[i].measurement.resetStat();
}

function measSave() {
   let text = OSC.saveHistos();
   let blob = new Blob([text], {type:"text/plain"});
   let url = window.URL.createObjectURL(blob);

   let downloadLink = document.createElement("a");
   let d = new Date();
   let y = d.getFullYear() % 100;
   downloadLink.download = "histos_"+(y<10?"0":"")+y+
      (d.getMonth()+1<10?"0":"")+(d.getMonth()+1)+
      (d.getDate()<10?"0":"")+d.getDate()+"_"+
      (d.getHours()<10?"0":"")+d.getHours()+
      (d.getMinutes()<10?"0":"")+d.getMinutes()+
      (d.getSeconds()<10?"0":"")+d.getSeconds()+".txt";
   downloadLink.innerHTML = "Download File";
   downloadLink.href = url;
   downloadLink.onclick = function(e) {
      document.body.removeChild(event.target);
   };
   downloadLink.style.display = "none";
   document.body.appendChild(downloadLink);

   downloadLink.click();
}

function dispHisto(c) {
   OSC.disp.histo = c.checked;
   OSC.resizeCanvas();
}

function triggerSendPattern() {
   let e = {};
   e.name = "triggerPtrnEn";
   e.value = 0;
   for (let i = 0; i < 18; i++) {
      if (document.getElementById(i<10? 'P0'+i : 'P'+i).enabled)
         e.value += (1 << i);
   }

   setParam(e);
}

function triggerSendPolarity() {
   let e = {};
   e.name = "triggerSrcPolarity";
   e.value = 0;
   for (let i = 0; i < 17; i++) {
      if (document.getElementById(i<10? 'L0'+i : 'L'+i).innerHTML === '-')
         e.value += (1 << i);
   }

   setParam(e);
}

function triggerSendCell(p) {
   let e = {};
   e.name = "triggerSrcEnPtrn";
   e.value = 0;
   for (let i = 0; i < 17; i++) {
      if (document.getElementById('C' + (i < 10 ? '0' + i : i) + (p < 10 ? '0' + p : p)).mode > 0)
         e.value += (1 << i);
   }
   setParam(e, p);

   e.name = "triggerStatePtrn";
   e.value = 0;
   for (let i = 0; i < 17; i++) {
      if (document.getElementById('C' + (i < 10 ? '0' + i : i) + (p < 10 ? '0' + p : p)).mode === 1)
         e.value += (1 << i);
   }
   setParam(e, p);
}

function triggerClickPattern() {
   this.enabled = !this.enabled;
   if (this.enabled) {
      this.style.backgroundColor = 'darkgreen';
      this.style.color = 'white';
   } else {
      this.style.backgroundColor = '#DDDDDD';
      this.style.color = 'black';
   }

   triggerSendPattern();
}

function triggerClickPolarity() {
   if (this.innerHTML === 'Pol') {
      for (let i=0; i <17 ; i++) {
         let cell = document.getElementById((i<10) ? 'L0' + i : 'L' + i);
         if (cell.innerHTML === '+')
            cell.innerHTML = '-';
         else
            cell.innerHTML = '+';
      }
   } else {
      if (this.innerHTML === '+')
         this.innerHTML = '-';
      else
         this.innerHTML = '+';
   }

   triggerSendPolarity();
}

function triggerClickCell() {
   // enable pattern for this cell
   let p = document.getElementById('P' + this.id.substr(3));
   p.enabled = true;
   p.style.backgroundColor = 'darkgreen';
   p.style.color = 'white';

   // switch OR-AND-NULL
   this.mode = (this.mode + 1) % 3;
   if (this.mode === 0)
      this.innerHTML = '';
   if (this.mode === 1)
      this.innerHTML = '&bull;';
   if (this.mode === 2)
      this.innerHTML = '&times;';

   triggerSendPattern();
   triggerSendCell(this.pa);
}

function triggerClearAll() {
   for (let i = 0; i < 16; i++) {
      let p = document.getElementById(i<10?'P0'+i:'P'+i);
      p.enabled = false;
      p.style.backgroundColor = '#DDDDDD';
      p.style.color = 'black';
   }
   for (let i = 16; i < 18; i++) {
      let p = document.getElementById(i<10?'P0'+i:'P'+i);
      p.enabled = false;
      p.style.backgroundColor = '#DDDDDD';
      p.style.color = 'black';
   }

   for (i = 0; i < 17; i++)
      for (let j = 0; j < 18; j++) {
         let c = document.getElementById('C' + (i < 10 ? '0' + i : i) + (j < 10 ? '0' + j : j));
         c.mode = 0;
         c.innerHTML = '';
      }

   triggerSendPattern();
   for (i = 0; i < 18; i++)
      triggerSendCell(i);
}

function triggerOrAll() {
   for (let i = 0; i < 16; i++) {
      let p = document.getElementById(i<10?'P0'+i:'P'+i);
      p.enabled = true;
      p.style.backgroundColor = 'darkgreen';
      p.style.color = 'white';
   }
   for (let i = 16; i < 18; i++) {
      let p = document.getElementById(i<10?'P0'+i:'P'+i);
      p.enabled = false;
      p.style.backgroundColor = '#DDDDDD';
      p.style.color = 'black';
   }

   for (i = 0; i < 17; i++)
      for (let j = 0; j < 18; j++) {
         let c = document.getElementById('C' + (i < 10 ? '0' + i : i) + (j < 10 ? '0' + j : j));
         if (i === j && j<16) {
            c.mode = 1;
            c.innerHTML = '&bull;';
         } else {
            c.mode = 0;
            c.innerHTML = '';
         }
      }

   triggerSendPattern();
   for (i = 0; i < 18; i++)
      triggerSendCell(i);
}


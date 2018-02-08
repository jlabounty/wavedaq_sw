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
   var c = document.getElementById("controls");
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
   var config = document.getElementById("config");
   config.t = 0;
   config.slider = 0;
   config.visible = false;

   // fill channels panel
   var chTable = document.getElementById("channelsTable");
   for (var r = 0; r < 16; r++) {
      var row = chTable.insertRow(-1);
      row.className = "channelsRow";

      var cell = row.insertCell(-1);
      cell.className = "channelsTd";
      cell.appendChild(document.createTextNode(r));
      cell.style.backgroundColor = OSC.chnColors[r];

      cell = row.insertCell(-1);
      cell.className = "channelsTd";
      var sel = document.createElement('select');
      sel.id = "selGain" + r;
      sel.name = "feGain";
      sel.setAttribute("onchange", "setParam(this," + r + ")");
      var gains = ["0.5", "1", "2.5", "5", "10", "25", "50", "100"];
      for (var i = 0; i < gains.length; i++) {
         var op = document.createElement('option');
         op.value = op.textContent = gains[i];
         if (gains[i] == "1")
            op.selected = true;
         sel.appendChild(op);
      }
      cell.appendChild(sel);

      cell = row.insertCell(-1);
      cell.className = "channelsTd";
      var cb = document.createElement('input');
      cb.type = "checkbox";
      cb.name = "fePzc";
      cb.id = "cbPzc" + r;
      cb.checked = false;
      cb.setAttribute("onclick", "setParam(this," + r + ")");
      cell.appendChild(cb);

      cell = row.insertCell(-1);
      cell.className = "channelsTd";
      var inp = document.createElement('input');
      inp.type = "text";
      inp.value = "0";
      inp.name = "dacTriggerLevel";
      inp.id = "inpDacTriggerLevel" + r;
      inp.style.width = "60px";
      inp.setAttribute("onkeypress", "keyParam(event, this," + r + ")");
      inp.setAttribute("onblur", "validateParam(this," + r + ")");
      inp.setAttribute("tabindex", 100 + r);
      cell.appendChild(inp);
      cell.appendChild(document.createTextNode(" mV"));

      cell = row.insertCell(-1);
      cell.className = "channelsTd";
      var inp = document.createElement('input');
      inp.type = "text";
      inp.value = "N/A";
      inp.name = "hvTarget";
      inp.id = "inpHvTarget" + r;
      inp.style.width = "80px";
      inp.setAttribute("onkeypress", "keyParam(event, this," + r + ")");
      inp.setAttribute("onblur", "validateParam(this," + r + ")");
      inp.setAttribute("tabindex", 116 + r);
      cell.appendChild(inp);
      var e = document.createElement("span");
      e.innerHTML = "&nbsp;V&nbsp;";
      cell.appendChild(e);

      cell = row.insertCell(-1);
      cell.className = "channelsTd";
      var inp = document.createElement('input');
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
   var now = new Date()/1000;

   if (now > OSC.lastParamSet + 2) {
      readWdb(OSC.curBoard).then(function (result) {
         OSC.timer.loadWdb = window.setTimeout(loadWdb, 1000);
      }).catch();
   } else {
      OSC.timer.loadWdb = window.setTimeout(loadWdb, 1000);
   }
}


function connectionBroken() {
   if (OSC.connected) {
      OSC.dlgReconnect = dlgMessage("Error", "Connection to server broken.<br>Trying to reconnect ..." +
         "<br /><br /><br /><img src=\"spinning-wheel-wds.gif\">", true, true);
      var b = document.getElementById("dlgMessageButton");
      b.innerHTML = "Cancel";
      OSC.connected = false;
      OSC.timer.reconnect = window.setTimeout(reconnect, 1000);
   }

   if (OSC.timer.loadGl != undefined)
      clearTimeout(OSC.timer.loadGl);
   if (OSC.timer.loadWdb != undefined)
      clearTimeout(OSC.timer.loadWdb);
   if (OSC.timer.loadWF != undefined)
      clearTimeout(OSC.timer.loadWF);
}

function reconnect() {
   if (OSC.dlgReconnect.parentElement == undefined)
      return;
   var req = new XMLHttpRequest();
   req.onreadystatechange = function () {
      if (req.readyState == 4 && req.status == 200) {
         // reload page
         location.reload();
      } else if (req.readyState == 4) {
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

function loadHv() {
   if (OSC.demoMode) {
      for (var i = 0; i < 16; i++) {
         OSC.wdb[OSC.curBoard].hv.target[i] = 0;
         OSC.wdb[OSC.curBoard].hv.current[i] = 0;
      }
      for (var i = 0; i < 4; i++)
         OSC.wdb[OSC.curBoard].hv.temperature[i] = 0;
      OSC.wdb[OSC.curBoard].hv.baseVoltage = 0;
      return;
   }
}

function populateAllControls(init) {
   // populate board list
   var sel = document.getElementById("wdSelect");
   for (var i = 0; i < OSC.wdb.length; i++) {
      var opt = document.createElement('option');
      opt.innerHTML = OSC.wdb[i].name;
      opt.value = OSC.wdb[i].name;
      if (sel.childNodes[i + 1] == undefined)
         sel.appendChild(opt);
      else if (sel.childNodes[i + 1].innerHTML != opt.innerHTML)
         sel.replaceChild(opt, sel.childNodes[i + 1]);
   }

   populateControls(init);
}

function populateControls(init) {
   // populate channel buttons
   for (var i = 0; i < 18; i++)
      OSC.chOn[i] = (OSC.wdb[OSC.curBoard].drsDrsChnTxEn & (1 << i)) > 0;
   OSC.drawChnButtons();

   // populate config
   if (document.getElementById("inpDacTriggerLevel") != document.activeElement) {
      document.getElementById("sldDacTriggerLevel").set(OSC.wdb[OSC.curBoard].dacTriggerLevel[0] + 0.5);
      document.getElementById("inpDacTriggerLevel").value = Math.round(OSC.wdb[OSC.curBoard].dacTriggerLevel[0] * 1000);
   }

   if (document.getElementById("inpTriggerDelay") != document.activeElement) {
      document.getElementById("sldTriggerDelay").set(1 - OSC.wdb[OSC.curBoard].triggerDelay / 450);
      document.getElementById("inpTriggerDelay").value = Math.round(OSC.wdb[OSC.curBoard].triggerDelay);
   }
   if (OSC.wdb[OSC.curBoard].triggerMode == 1) {
      document.getElementById("rbTriggerModeNormal").checked = true;
      document.getElementById("rbTriggerModeAuto").checked = false;
   } else if (OSC.wdb[OSC.curBoard].triggerMode == 2) {
      document.getElementById("rbTriggerModeNormal").checked = false;
      document.getElementById("rbTriggerModeAuto").checked = true;
   }

   if (OSC.wdb[OSC.curBoard].triggerSource == 0) {
      document.getElementById("rbTriggerSourceInt").checked = true;
      document.getElementById("rbTriggerSourceExt").checked = false;
   } else if (OSC.wdb[OSC.curBoard].triggerSource == 1) {
      document.getElementById("rbTriggerSourceInt").checked = false;
      document.getElementById("rbTriggerSourceExt").checked = true;
   }

   if (OSC.wdb[OSC.curBoard].triggerFallingEdge) {
      document.getElementById("trgEdgeUp").style.display = "none";
      document.getElementById("trgEdgeDown").style.display = "inline";
   } else {
      document.getElementById("trgEdgeUp").style.display = "inline";
      document.getElementById("trgEdgeDown").style.display = "none";
   }

   document.getElementById("cbPzc").checked = OSC.wdb[OSC.curBoard].fePzc[0];
   document.getElementById("selGain").value = OSC.wdb[OSC.curBoard].feGain[0];
   document.getElementById("selPzcLevel").value = OSC.wdb[OSC.curBoard].dacPzcLevel;

   document.getElementById("inputReadoutSrcDRS").checked = (OSC.wdb[OSC.curBoard].readoutSrcSel == 1);
   document.getElementById("inputReadoutSrcADC").checked = (OSC.wdb[OSC.curBoard].readoutSrcSel == 2);

   document.getElementById("timingCalibSignalEnable").checked = OSC.wdb[OSC.curBoard].timingCalibSignalEnable;

   if (OSC.wdb[OSC.curBoard].dacCalDc > 0.4)
      document.getElementById("selRange").value = -0.45;
   else if (OSC.wdb[OSC.curBoard].dacCalDc < -0.4)
      document.getElementById("selRange").value = 0.45;
   else
      document.getElementById("selRange").value = 0;

   document.getElementById("feMux").checked = (OSC.wdb[OSC.curBoard].feMux[0] == 3);
   document.getElementById("calibBufferEnable").checked = OSC.wdb[OSC.curBoard].calibBufferEnable;

   if (document.getElementById("inpDacCalDc") != document.activeElement) {
      document.getElementById("sldDacCalDc").set(OSC.wdb[OSC.curBoard].dacCalDc / 2 + 0.5);
      document.getElementById("inpDacCalDc").value = Math.round(OSC.wdb[OSC.curBoard].dacCalDc * 1000);
   }

   if (document.getElementById("drsSampleFreq") != document.activeElement) {
      document.getElementById("drsSampleFreq").value = Math.round(OSC.wdb[OSC.curBoard].drsSampleFreq / 1000 * 10) / 10;
      document.getElementById("drsActualSampleFreq").innerHTML = OSC.wdb[OSC.curBoard].drsSampleFreq / 1000 + " GSPS";
   }
   var s = document.getElementById("timingReferenceSignalSelect");
   if (OSC.wdb[OSC.curBoard].drs0TimingRefSel > 0)
      s.selectedIndex = 2;
   else if (OSC.wdb[OSC.curBoard].timingCalibSignalEnable)
      s.selectedIndex = 1;

   document.getElementById("calib1").checked = OSC.wp.ofsCalib1;
   document.getElementById("calib2").checked = OSC.wp.ofsCalib2;
   document.getElementById("calib3").checked = OSC.wp.gainCalib;
   document.getElementById("calib4").checked = OSC.wp.rangeCalib;
   document.getElementById("spikes").checked = OSC.wp.removeSpikes;
   document.getElementById("rotate").checked = OSC.wp.rotateWaveform;

   document.getElementById("tcalib1").checked = OSC.wp.timeCalib1;
   document.getElementById("tcalib2").checked = OSC.wp.timeCalib2;
   document.getElementById("tcalib3").checked = OSC.wp.timeCalib3;

   // document.getElementById("clksource").checked = (OSC.wdb[OSC.curBoard].daqClkSrcSel == 1);
   document.getElementById("clksource").checked = true;
   document.getElementById("clksource").disabled = true;

   // channels dialog box with FE gain and HV
   for (i = 0; i < 16; i++) {
      if (document.getElementById("inpDacTriggerLevel" + i) != document.activeElement)
         document.getElementById("inpDacTriggerLevel" + i).value = Math.round(OSC.wdb[OSC.curBoard].dacTriggerLevel[i] * 1000);

      document.getElementById("selGain" + i).value = OSC.wdb[OSC.curBoard].feGain[i];
      document.getElementById("cbPzc" + i).checked = OSC.wdb[OSC.curBoard].fePzc[i];

      var e = document.getElementById("inpHvTarget" + i);
      if (e != document.activeElement)
         e.value = OSC.wdb[OSC.curBoard].hv.target[i];
      document.getElementById("inpHvCurrent" + i).value = OSC.wdb[OSC.curBoard].hv.current[i];
   }

   // trigger pattern dialog box
   for (i = 0; i < 18; i++) {
      var p = document.getElementById(i<10 ? 'P0'+i : 'P'+i);
      p.enabled = (OSC.wdb[OSC.curBoard].triggerPatternEnLocal & (1 << i)) > 0;
      if (p.enabled) {
         p.style.backgroundColor = 'darkgreen';
         p.style.color = 'white';
      } else {
         p.style.backgroundColor = '#DDDDDD';
         p.style.color = 'black';
      }

      for (var j = 0; j < 16; j++) {
         var c = document.getElementById('C' + (j < 10 ? '0' + j : j) + (i < 10 ? '0' + i : i));

         c.mode = 0;

         // invert pattern for negative trigger
         if (OSC.wdb[OSC.curBoard].triggerFallingEdge) {
            if ((OSC.wdb[OSC.curBoard].triggerPattern[i] & (1 << (j+16))) > 0)
               c.mode = 1;
            if ((OSC.wdb[OSC.curBoard].triggerPattern[i] & (1 << j)) > 0)
               c.mode = 2;
         } else {
            if ((OSC.wdb[OSC.curBoard].triggerPattern[i] & (1 << j)) > 0)
               c.mode = 1;
            if ((OSC.wdb[OSC.curBoard].triggerPattern[i] & (1 << (j+16))) > 0)
               c.mode = 2;
         }
         if (c.mode == 0)
            c.innerHTML = '';
         if (c.mode == 1)
            c.innerHTML = '&bull;';
         if (c.mode == 2)
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

function loadGl(init) {
   // send AJAX request
   var req = new XMLHttpRequest();
   req.onreadystatechange = function () {
      if (req.readyState == 4 && req.status == 200) {
         var o = JSON.parse(req.responseText);
         OSC.gl = o.gl;
         OSC.wp = o.wp;
         readWdb(-1, init); // daisy-chain for loading all WDBs
      } else if (req.readyState == 4 && req.status == 0) {
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

   return new Promise(function(resolve, reject) {
      // send AJAX request
      var req = new XMLHttpRequest();
      req.onreadystatechange = function () {
         if (req.readyState == 4 && req.status == 200) {
            if (b == -1)
               OSC.wdb = JSON.parse(req.responseText).wdb;
            else
               OSC.wdb[b] = JSON.parse(req.responseText).wdb[0];
            populateAllControls(init);
            OSC.connected = true;
            resolve(req);

         } else if (req.readyState == 4 && req.status == 0) {
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
   var c = document.getElementById("feMux");
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
   if (e.selectedIndex == 1) {
      var c = document.getElementById("calibBufferEnable");
      c.checked = true;
      setParam(c);
      var c = document.getElementById("timingCalibSignalEnable");
      c.checked = true;
      setParam(c);
   }
}

function setDrsSamplFreq(e) {
   setParam(e);
}

function setParam(e, channel) {
   if (OSC.demoMode)
      return;

   // suppress automatic updates for few seconds, otherwise a pending update
   // could overwrite the current dialog box setting
   OSC.lastParamSet = new Date() / 1000;

   var req = new XMLHttpRequest();

   req.onreadystatechange = function () {
      if (req.readyState == 4 && req.status == 204) {
         // success
         if (e.name == "range") {
            // read back DC offset which gets shifted by range change
            readWdb(-1);
         }
      } else if (req.readyState == 4 && req.status == 0) {
         connectionBroken();
      }
   };

   if (e.name == "dacTriggerLevel" && channel == undefined) {
      for (var i = 0; i < 16; i++)
         document.getElementById("inpDacTriggerLevel" + i).value = e.value;
   }

   if (e.name == "feGain" && channel == undefined) {
      for (var i = 0; i < 16; i++)
         document.getElementById("selGain" + i).value = e.value;
   }

   if (e.name == "fePzc" && channel == undefined) {
      for (var i = 0; i < 16; i++)
         document.getElementById("cbPzc" + i).checked = e.checked;
   }

   if (e.name == "clkSource" && e.checked == true) {
      if (OSC.wdb[OSC.curBoard].scaler[17] < 79E6)
         dlgMessage("Error", "No external clock present", true, true);
   }

   var uri = e.name + "/";
   if (OSC.applyAll)
      uri += "ALL";
   else
      uri += OSC.curBoard + "";
   if (channel != undefined)
      uri += "/" + channel;

   var value = "";
   if (e.type == "select-one") {
      if (e.selectedIndex != -1) {
         value = e.selectedOptions[0].value;
      }
   } else if (e.type == "checkbox") {
      value = e.checked;
   } else if (e.name == "dacTriggerLevel") {
      value = parseInt(e.value) / 1000;
   } else if (e.name == "dacCalDc") {
      value = parseInt(e.value) / 1000;
   } else if (e.name == "drsSampleFreq") {
      value = parseFloat(e.value) * 1000;
   } else {
      value = e.value;
   }

   req.open("PUT", uri, true);
   req.send(value);

   // set variable locally
   if (OSC.wp[e.name] != undefined)
      OSC.wp[e.name] = value;
   else if (OSC.wdb[OSC.curBoard][e.name] != undefined) {
      if (OSC.applyAll) {
         for (var i = 0; i < OSC.wdb.length; i++) {
            if (OSC.wdb[i][e.name] instanceof Array) {
               if (channel == undefined) {
                  for (var j = 0; j < OSC.wdb[i][e.name].length; j++)
                     OSC.wdb[i][e.name][j] = value;
               } else
                  OSC.wdb[i][e.name][channel] = value;
            } else
               OSC.wdb[i][e.name] = value;
         }
      } else {
         if (OSC.wdb[OSC.curBoard][e.name] instanceof Array) {
            // gain, pzc, femux, trigger level arrays
            if (channel == undefined) {
               for (var i = 0; i < OSC.wdb[OSC.curBoard][e.name].length; i++)
                  OSC.wdb[OSC.curBoard][e.name][i] = value;
            } else
               OSC.wdb[OSC.curBoard][e.name][channel] = value;
         } else
            OSC.wdb[OSC.curBoard][e.name] = value;
      }
   }
}

function setDisp(e) {
   if (e.name == "scaler") {
      OSC.disp.scaler = e.checked;
      OSC.resizeCanvas();
      OSC.redraw();
   }
}

function setPers(s) {
   OSC.clearPersistency();
   OSC.redraw();
   OSC.disp.persistency = parseFloat(s.value);
}

function keyParam(event, input, channel) {
   var charCode = (typeof event.which == "number") ? event.which : event.keyCode;

   if (charCode == 13) {
      validateParam(input, channel);
      input.focus();
      input.setSelectionRange(0, input.value.length);
   }
}

function validateParam(input, channel) {
   if (input.id.substring(0, 18) == "inpDacTriggerLevel") {
      if (input.value < -500)
         input.value = -500;
      if (input.value > 500)
         input.value = 500;
      if (input.id == "inpDacTriggerLevel")
         document.getElementById("sldDacTriggerLevel").set(input.value / 1000 + 0.5);
   }

   if (input.id == "inpTriggerDelay") {
      if (input.value < 0)
         input.value = 0;
      if (input.value > 450)
         input.value = 450;
      document.getElementById("sldTriggerDelay").set(1 - input.value / 450);
   }

   if (input.id == "drsSampleFreq") {
      var divider = Math.round(240.0 / input.value * 2.048);
      divider = 2 * Math.floor(divider / 2);
      OSC.wdb[OSC.curBoard].drsSampleFreq = Math.round(240 / divider * 2048);
      document.getElementById("drsActualSampleFreq").innerHTML = OSC.wdb[OSC.curBoard].drsSampleFreq / 1000 + " GSPS";
   }

   if (input.id == "inpDacCalDc") {
      if (input.value < -1000)
         input.value = -1000;
      if (input.value > 1000)
         input.value = 1000;
      document.getElementById("sldDacCalDc").set(input.value / 2000 + 0.5);
   }

   if (input.id.substr(0, 11) == "inpHvTarget") {
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

   var req = new XMLHttpRequest();
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

   var req = new XMLHttpRequest();
   if (all)
      req.open("PUT", "tcalib/ALL");
   else
      req.open("PUT", "tcalib/" + OSC.curBoard);
   req.send();
}

function loadBuild() {
   if (OSC.demoMode) {
      var e = document.getElementById("build");
      e.innerHTML = "Demo Mode";
      return;
   }
   // send AJAX request
   var req = new XMLHttpRequest();
   req.onreadystatechange = function () {
      if (req.readyState == 4 && req.status == 200) {
         var build = JSON.parse(req.responseText);
         var e = document.getElementById("build");
         e.innerHTML = "Built " + build.build;
      } else if (req.readyState == 4 && req.status == 0) {
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

   var i, c, chn;

   if (OSC.demoMode) {
      // create 18 empty waveforms
      var wf = {T: [], U: []};
      OSC.i1 = 0;
      OSC.i2 = 1023;
      for (c = 0; c < 18; c++) {
         wf.T[c] = [];
         wf.U[c] = [];
         for (i = 0; i < 1024; i++) {
            var t = i * 1E-9 / OSC.wdb[OSC.curBoard].drsSampleFreq;
            wf.T[c][i] = t;
            wf.U[c][i] = Math.sin((wf.T[c][i] + c * 1E-9) * OSC.wdb[OSC.curBoard].drsSampleFreq /
                  1E-9 / 50) / 4 + (Math.random() - 0.5) / 300;

            var xt = OSC.timeToX(t);
            if (OSC.i1 == 0 && xt >= OSC.x1)
               OSC.i1 = i;
            if (xt <= OSC.x2)
               OSC.i2 = i;
         }
         // add spikes
         for (i = 0; i < 1024; i++) {
            if (Math.random() < 0.00005) {
               var s = (Math.random() - 0.5) / 5;
               var j = i - 5;
               for (var f = 0; f < 1; f += 0.2, j++)
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
         OSC.timer.loadWF = window.setTimeout(loadWF, 10); // schedule next waveform read

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
         for (var p = 0; p < OSC.measList.childNodes[i].measurement.param.length; p++) {
            if (OSC.measList.childNodes[i].measurement.param[p].type == "CH")
               chn |= (1 << OSC.measList.childNodes[i].measurement.param[p].value);
         }
      }

   if (chn == 0 && OSC.running) {
      OSC.timer.loadWF = window.setTimeout(loadWF, 10); // schedule next waveform read
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
   if (OSC.req.readyState == 4 && OSC.req.status == 200) {
      // this.wf = JSON.parse(OSC.req.responseText); // use this for JSON encoded data

      // create 16+2+2 empty waveforms
      var wf = {T: [], U: [], type: 1};
      for (var i = 0; i < 20; i++) {
         wf.T[i] = [];
         wf.U[i] = [];
      }

      var intArray = new Uint32Array(OSC.req.response);
      var floatArray = new Float32Array(OSC.req.response);

      for (i = 0; i < intArray.length;) {
         var responseType = intArray[i];

         if (responseType == 0) {        // idle message
            OSC.idle = true;
            break;
         } else if (responseType == 1) { // time array
            i++;
            OSC.wd = intArray[i++];
            OSC.tCalibrated = intArray[i++];
            OSC.nLogged = intArray[i++];
            var c = intArray[i++];
            var n = intArray[i++];
            OSC.i1 = 0;
            OSC.i2 = 1023;
            for (var j = 0; j < n; j++) {
               var t = floatArray[i++];
               wf.T[c][j] = t;
               var xt = OSC.timeToX(t);
               if (OSC.i1 == 0 && xt >= OSC.x1)
                  OSC.i1 = j;
               if (xt <= OSC.x2)
                  OSC.i2 = j;
            }

            // check for progress bar
            if (progressInd > 0) {
               progressInd = 0;
               var e = document.getElementById("progressIndVcalib");
               e.style.width = "0";
               e = document.getElementById("progressIndTcalib");
               e.style.width = "0";

               OSC.clearPersistency();

               document.getElementById("wdSelect").selectedIndex = progressOldBoard;
               document.getElementById("btnVCalib").innerHTML = "Execute Voltage Calibration";
               document.getElementById("btnVCalib").disabled = false;
               document.getElementById("btnTCalib").innerHTML = "Execute Time Calibration";
               document.getElementById("btnTCalib").disabled = false;
               OSC.curBoard = progressOldBoard;

               OSC.timer.loadGl = window.setTimeout(loadGl, 10);
            }

         } else if (responseType == 2) { // voltage array
            i++;
            OSC.idle = false;
            OSC.wd = intArray[i++];
            OSC.vCalibrated = intArray[i++];
            OSC.nLogged = intArray[i++];
            c = intArray[i++];
            n = intArray[i++];
            for (j = 0; j < n; j++)
               wf.U[c][j] = floatArray[i++];
            OSC.remoteDemo = (OSC.wd == 0xFF);

         } else if (responseType == 10) { // vcalib progress data
            var b = intArray[1];
            progressInd = floatArray[2];

            e = document.getElementById("progressIndVcalib");
            e.style.width = (progressInd * 270) + "px";

            document.getElementById("wdSelect").selectedIndex = b;
            document.getElementById("btnVCalib").innerHTML = document.getElementById("wdSelect").value;
            document.getElementById("btnVCalib").disabled = true;

            OSC.timer.loadWF = window.setTimeout(loadWF, 250);
            return;

         } else if (responseType == 11) { // tcalib progress data
            var b = intArray[1];
            progressInd = floatArray[2];
            i += 3;

            wf.type = 2; // indicate delta-T array

            e = document.getElementById("progressIndTcalib");
            e.style.width = (progressInd * 270) + "px";

            document.getElementById("wdSelect").selectedIndex = b;
            document.getElementById("btnTCalib").innerHTML = document.getElementById("wdSelect").value;
            document.getElementById("btnTCalib").disabled = true;

            while (i < intArray.length) {
               c = intArray[i++];
               n = intArray[i++];
               for (j = 0; j < n; j++)
                  wf.T[c][j] = floatArray[i++];
            }

         } else {
            alert("WDS: Invalid binary data received form server");
            break;
         }
      }

      // calculate sum and FFT waveforms
      calcMathWF(wf);

      if (responseType == 11) {
         OSC.timer.loadWF = window.setTimeout(loadWF, 250);
         OSC.sendWaveforms(wf);

      } else {
         // schedule next waveform read
         if (OSC.running)
            OSC.timer.loadWF = window.setTimeout(loadWF, 10);

         // send waveforms to oscilloscope
         if (!OSC.idle)
            OSC.sendWaveforms(wf);
      }

      // redraw oscilloscope to show new waveforms
      OSC.redraw();

      // if logging file is complete, load it
      if (OSC.logFlag && OSC.nLogged == OSC.nRequested) {
         OSC.logFlag = false;

         var e = document.getElementById('btnSave');
         e.innerHTML = "Save";
         e.style.border = "2px solid #C0C0C0";

         // trigger loading of file
         downloadFile(OSC.logfile);
      }
   } else if (OSC.req.readyState == 4 && OSC.req.status == 0) {
      connectionBroken();
   }
}

function calcMathWF(wf)
{
   // add sum waveform
   for (i = 0; i < 1024; i++) {
      var t = i * 1E-6 / OSC.wdb[OSC.curBoard].drsSampleFreq;
      wf.T[18][i] = t;

      wf.U[18][i] = 0;
      for (var j=0 ; j<16 ; j++)
         if (OSC.chOn[j])
            wf.U[18][i] += wf.U[j][i];
   }

   var w = new Float32Array(1024);
   for (var i = 0; i < 1024; i++) {
      w[i] = Math.sin(880 * Math.PI * 2 * (i / 44000));
   }
   spectrum = fft(w);

   // add FFT waveform
   for (i = 0; i < 1024; i++) {
      var t = i * 1E-6 / OSC.wdb[OSC.curBoard].drsSampleFreq;
      wf.T[19][i] = t;
      wf.U[19][i] = w[i]/1000;
   }
}

/*---- UI event handler ----*/

function resize()
// called when screen got resized
{
   var ctls = document.getElementById("controls");
   var config = document.getElementById("config");

   if (ctls.hidden == true) {
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

      config.style.left = (document.documentElement.clientWidth -
         config.offsetWidth * config.slider) + "px";
      config.style.height = document.documentElement.clientHeight + "px";

      OSC.resize(document.documentElement.clientWidth - ctls.offsetWidth -
         config.offsetWidth * config.slider,
         document.documentElement.clientHeight);
   }
}

function oscKeypress(e) {
   var charCode = (typeof e.which == "number") ? e.which : e.keyCode;

   // check if for some dialog box etc.
   if (e.target != document.body)
      return;

   if (charCode == ' '.charCodeAt(0)) {
      btnStop();
   }

   if (charCode == ']'.charCodeAt(0)) {
      var ctls = document.getElementById("controls");
      ctls.hidden = !ctls.hidden;
      resize();
   }

   if (charCode == 'c'.charCodeAt(0)) {
      btnConfig();
   }

   if (charCode == 'a'.charCodeAt(0)) {
      btnChnAll();
   }

   if (charCode == 'o'.charCodeAt(0)) {
      btnOn();
   }

   if (charCode == '^'.charCodeAt(0)) {
      btnOfsDist();
   }

   if (charCode == 'v'.charCodeAt(0)) {
      btnOfsZero();
   }

}

function btnStop()
// start/stop oscilloscope
{
   var e = document.getElementById("btnStop");
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
      var e = document.getElementById("btnStop");
      OSC.running = false;
      e.innerHTML = "Start";
      e.style.backgroundColor = "#FFA0A0";
   }

   OSC.timer.loadWF = window.setTimeout(loadWF, 10);
}

function enableDRSChannels() {
   var mask = 0;
   for (var i = 0; i < 18; i++)
      if (OSC.chOn[i])
         mask |= (1 << i);

   OSC.wdb[OSC.curBoard].drsDrsChnTxEn = 0;
   for (var i = 0; i < 18; i++)
      if (OSC.chOn[i])
         OSC.wdb[OSC.curBoard].drsDrsChnTxEn |= (1 << i);

   var req = new XMLHttpRequest();

   if (OSC.applyAll) {
      for (var i = 0; i < OSC.wdb.length; i++)
         OSC.wdb[i].drsDrsChnTxEn = OSC.wdb[OSC.curBoard].drsDrsChnTxEn;
      req.open("PUT", "/enableChannel/ALL", true);
   } else {
      req.open("PUT", "/enableChannel/" + OSC.curBoard, true);
   }
   req.send(mask);
}

function btnChnAll() {
   var i;

   for (i = 0; i < 16; i++)
      OSC.chOnSelected[i] = true;

   // set scale according to first active channel
   for (i = 0; i < 19; i++)
      if (OSC.chOn[i])
         break;
   if (i == 18)
      i = 0;
   document.getElementById("UScale").innerHTML = OSC.UScaleTable[OSC.wfScaleIndex[i]][1];

   document.getElementById("chOn").innerHTML = "On";

   OSC.drawChnButtons();
}

function btnChn(event, c)
// select channel "c" and set controls to reflect channel status (c == -1 means all channels)
{
   event.preventDefault(); // suppress context menu for Ctrl-click

   // unselect all channels
   if (!event.ctrlKey && !event.shiftKey)
      for (var i = 0; i < 20; i++)
         if (i != c)
            OSC.chOnSelected[i] = false;

   if (event.shiftKey) {
      // find last selected channel
      var last;
      for (last = 15; last >= 0; last--)
         if (OSC.chOnSelected[last])
            break;
      // select all channels betweeen last and current
      if (c > last)
         for (var i = last; i < c; i++)
            OSC.chOnSelected[i] = true;
      if (c < last)
         for (var i = last; i > c; i--)
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
      var o = document.getElementById("chOn");
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
   for (var i = 0; i < 16; i++) {
      if (!OSC.chOnSelected[i])
         continue;
      var cb = document.getElementById("ch" + i);
      var bt = document.getElementById("chOn");
      if (bt.innerHTML == "On") {
         OSC.chOn[i] = true;
         cb.style.backgroundColor = OSC.chnColors[i];
      } else {
         OSC.chOn[i] = false;
         cb.style.backgroundColor = "#E0E0E0";
      }
   }
   if (bt != undefined)
      bt.innerHTML = bt.innerHTML == "On" ? "Off" : "On";

   enableDRSChannels();
   OSC.clearPersistency();
   OSC.redraw();
}

function btnScale(inc)
// change vertical scale, update label
{
   for (var i = 0; i < 19; i++)
      if (OSC.chOnSelected[i])
         break;
   if (i == 19)
      i = 0;

   var index = OSC.wfScaleIndex[i] + inc;
   if (index < 0)
      index = 0;
   if (index == OSC.UScaleTable.length)
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
   var index = OSC.wfTScaleIndex + inc;
   if (index < 0)
      index = 0;
   if (index == OSC.TScaleTable.length)
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
   for (var i = 0; i < 19; i++) {
      if (!OSC.chOnSelected[i])
         continue;
      OSC.wfOffset[i] = value - 0.5;
   }
   OSC.calcScaleOffset();
   OSC.clearPersistency();
   OSC.redraw();
}

var tLevelLast = -1;

function sldDacTriggerLevel(value) {
   if (OSC.demoMode)
      return;

   value = Math.round((value - 0.5) * 1000) / 1000; // convert to V

   if (value == tLevelLast) // only send if changed
      return;

   tLevelLast = value;

   document.getElementById("inpDacTriggerLevel").value = value * 1000;
   setParam(document.getElementById("inpDacTriggerLevel"));

   var d = new Date();
   OSC.lastTriggerLevelChange = d.getTime();
   clearStat();
   OSC.redraw();
}

function sldTriggerDelay(value) {
   if (OSC.demoMode)
      return;
   var del = 450 - Math.round(value * 450);

   OSC.wdb[OSC.curBoard].triggerDelay = del;
   document.getElementById("inpTriggerDelay").value = del;
   var e = {};
   e.name = "triggerDelay";
   e.value = del;
   setParam(e);
   clearStat();
}

function btnTedge(value) {
   if (OSC.demoMode)
      return;

   var e = {};
   e.name = "triggerFallingEdge";
   e.value = (value == 1);
   setParam(e);

   for (var i=0 ; i<18 ; i++)
      triggerSendCell(i);

   if (value == 1) {
      document.getElementById('trgEdgeUp').style.display = "none";
      document.getElementById('trgEdgeDown').style.display = "inline";
   } else {
      document.getElementById('trgEdgeUp').style.display = "inline";
      document.getElementById('trgEdgeDown').style.display = "none";
   }
}

function sldDacCalDc(value) {
   if (OSC.demoMode)
      return;

   document.getElementById("inpDacCalDc").value = Math.round(value * 2000 - 1000);
   setParam(document.getElementById("inpDacCalDc"));
}

function setRange(s) {
   if (OSC.demoMode)
      return;

   var e = {};
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

   var sl = document.getElementsByName("ctrlVSlider");
   sl[0].position = 0.5;
   sl[0].draw();
}

function btnOfsDist() {
   // count active channels
   var n = 0;
   for (i = 0; i < 19; i++) {
      if (OSC.chOn[i])
         n++;
   }

   // calculate offset between channels
   var d = 1 / (n + 1);

   // set offset
   var o = 0.5 - d;
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
   var wfWidth = 1024 / OSC.wdb[OSC.curBoard].drsSampleFreq * 1E-6;
   var scWidth = OSC.wfTScale * 10;
   if (wfWidth >= scWidth)
      OSC.wfTOffset = 0.9 * scWidth - wfWidth - value * (0.8 * scWidth - wfWidth);
   else
      OSC.wfTOffset = 0.9 * scWidth - wfWidth - (1 - value) * (0.8 * scWidth - wfWidth);

   clearStat();
   OSC.clearPersistency();
   OSC.calcScaleOffset();
   OSC.redraw();
}

function btnConfig() {
   var config = document.getElementById("config");
   config.visible = !config.visible;
   config.t = 0;
   window.setTimeout(configSlide, 20);
}

function btnSave() {
   var e = document.getElementById('btnSave');
   if (e.innerHTML == "Stop") {
      var req = new XMLHttpRequest();

      req.onreadystatechange = function () {
         if (req.readyState == 4 && req.status == 204) {
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
   // check for download attribute
   var link = document.createElement("a");
   var filename = document.getElementById("filename").value;
   if (!("download" in link)) {
      alert("Downloading of files in not supported in your browser. Please use Firefox or Chrome.");
      return;
   }

   if (document.getElementById("filename").value == "") {
      dlgMessage("Error", "Please enter a valid file name", true, true);
      return;
   }

   var ne = document.getElementById("nevents").value;
   if (isNaN(parseInt(ne)) || parseInt(ne) < 1 || parseInt(ne) > 1E6) {
      dlgMessage("Error", "Please enter a valid number of events", true, true);
      return;
   }

   if (document.getElementById("saveboards").selectedOptions[0].value == "all") {
      dlgMessage("Error", "Saving all boards only works with a global crate trigger", true, true);
      return;
   }

   var b = document.getElementById('btnSave');
   b.innerHTML = "Stop";
   b.style.border = "3px solid #00A0FF";

   OSC.logfile = filename;
   OSC.nRequested = parseInt(ne);
   OSC.nLogged = 0;

   var req = new XMLHttpRequest();
   req.onreadystatechange = function () {
      if (req.readyState == 4 && req.status == 204) {
         OSC.logFlag = true;
      }
   };

   var param = OSC.logfile;
   param += "\n";
   param += document.getElementById("fileformat").selectedOptions[0].value;
   param += "\n";
   param += document.getElementById("saveboards").selectedOptions[0].value == "all" ? "all" : OSC.curBoard;
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
   var link = document.createElement("a");
   document.body.appendChild(link);
   link.download = filename;
   link.href = filename;
   link.click();
   document.body.removeChild(link);
   window.URL.revokeObjectURL(filename);
}

function configSlide() {
   var config = document.getElementById("config");

   config.t++;

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
}

function measAdd() {
   // remove hint on first call
   var h = document.getElementById("addHint");
   if (h)
      h.parentNode.removeChild(h);

   var l = document.getElementById("measList");

   // overall <div> for measurement
   var meas = document.createElement("div");
   l.insertBefore(meas, l.childNodes[l.childNodes.length - 2]);

   if (l.childNodes.length > 6)
      var prev = l.childNodes[l.childNodes.length - 4].measurement;

   // create measurement object and attach it to <div>
   meas.measurement = new Measurement();

   // minus button
   var b = document.createElement("button");
   b.type = "button";
   b.className = "plusButton";
   b.style.color = "red";
   b.onclick = measRem;
   b.innerHTML = "-";
   meas.appendChild(b);

   // Measurement select
   var s = document.createElement("select");
   s.className = "measSelect";
   s.onchange = function () {
      measSelect(meas, s);
   };
   for (var i = 0; i < measList.length; i++) {
      o = document.createElement("option");
      o.value = measList[i].name;
      o.innerHTML = measList[i].name;
      if (prev) {
         if (measList[i].name == prev.name)
            o.selected = true;
      }
      s.appendChild(o);
   }
   meas.appendChild(s);

   measSelect(meas, s, prev);
}

function measSelect(meas, sel, prev) {

   // remove previous input fields
   for (var i = meas.childNodes.length - 1; i > 1; i--)
      meas.removeChild(meas.childNodes[i]);

   meas.measurement.setFunc(sel.value);

   // add input fields for measurement
   var input = [];
   for (var pi = 0; pi < meas.measurement.param.length; pi++) {

      if (meas.measurement.param[pi].type == "WD") {
         input[pi] = document.createElement("select");
         input[pi].className = "measSelect";
         input[pi].onchange = function () {
            measParamChange(meas);
         };
         for (i = 0; i < OSC.wdb.length; i++) {
            var o = document.createElement("option");
            o.value = i;
            o.innerHTML = OSC.wdb[i].name;
            if (prev) {
               if (prev.param[pi].value == i)
                  o.selected = true;
            }
            input[pi].appendChild(o);
         }
         meas.appendChild(input[pi]);
      }
      else if (meas.measurement.param[pi].type == "CH") {
         input[pi] = document.createElement("select");
         input[pi].className = "measSelect";
         input[pi].onchange = function () {
            measParamChange(meas);
         };
         for (i = 0; i < 19; i++) {
            o = document.createElement("option");
            o.value = i;
            if (i == 18)
               o.innerHTML = "SUM";
            else
               o.innerHTML = "CH" + i;
            if (prev) {
               if (prev.param[pi].value + 1 == i)
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
         input[pi].value = meas.measurement.param[pi].value;
         input[pi].onchange = function () {
            measParamChange(meas);
         };
         input[pi].addEventListener('focus', function(e) {
            OSC.timeCursor.input = this;
            OSC.timeCursor.time = this.value;
         }, false);

         var text = document.createElement("span");
         text.innerHTML = "&nbsp;" + meas.measurement.param[pi].name + ":&nbsp;";
         meas.appendChild(text);
         meas.appendChild(input[pi]);
      }

      measParamChange(meas);
   }

}

function measParamChange(meas) {
   var n = 0;
   for (var i = 2; i < meas.childNodes.length; i++) {
      if (meas.childNodes[i].type) {
         meas.measurement.param[n++].value = parseFloat(meas.childNodes[i].value);
         meas.measurement.resetStat();
      }
   }
}

function measZoomIn() {
   OSC.histo.autoAxis = false;

   var x = OSC.histo.xMax;
   var d = 0.25 * (OSC.histo.axisMax - OSC.histo.axisMin);

   OSC.histo.axisMin = x - d;
   OSC.histo.axisMax = x + d;
}

function measZoomOut() {
   OSC.histo.autoAxis = false;
   var d = 0.5 * (OSC.histo.axisMax - OSC.histo.axisMin);
   OSC.histo.axisMin -= d;
   OSC.histo.axisMax += d;
}

function measZoomFit() {
   OSC.histo.autoAxis = true;
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

function dispHisto(c) {
   OSC.disp.histo = c.checked;
   OSC.resizeCanvas();
}

function triggerSendPattern() {
   var e = {};
   e.name = "triggerPatternEnLocal";
   e.value = 0;
   for (var i = 0; i < 18; i++) {
      if (document.getElementById(i<10? 'P0'+i : 'P'+i).enabled)
         e.value += (1 << i);
   }

   setParam(e);
}

function triggerSendCell(p) {
   var e = {};
   e.name = "triggerPattern";
   e.value = 0;
   for (var i = 0; i < 16; i++) {
      if (OSC.wdb[OSC.curBoard].triggerFallingEdge) {
         if (document.getElementById('C' + (i < 10 ? '0' + i : i) + (p < 10 ? '0' + p : p)).mode == 1)
            e.value += (1 << (i + 16));
         if (document.getElementById('C' + (i < 10 ? '0' + i : i) + (p < 10 ? '0' + p : p)).mode == 2)
            e.value += (1 << i);
      } else {
         if (document.getElementById('C' + (i < 10 ? '0' + i : i) + (p < 10 ? '0' + p : p)).mode == 1)
            e.value += (1 << i);
         if (document.getElementById('C' + (i < 10 ? '0' + i : i) + (p < 10 ? '0' + p : p)).mode == 2)
            e.value += (1 << (i + 16));
      }
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

function triggerClickCell() {
   // enable pattern for this cell
   var p = document.getElementById('P' + this.id.substr(3));
   p.enabled = true;
   p.style.backgroundColor = 'darkgreen';
   p.style.color = 'white';

   // switch OR-AND-NULL
   this.mode = (this.mode + 1) % 3;
   if (this.mode == 0)
      this.innerHTML = '';
   if (this.mode == 1)
      this.innerHTML = '&bull;';
   if (this.mode == 2)
      this.innerHTML = '&times;';

   triggerSendPattern();
   triggerSendCell(this.pa);
}

function triggerClearAll() {
   for (var i = 0; i < 16; i++) {
      var p = document.getElementById(i<10?'P0'+i:'P'+i);
      p.enabled = false;
      p.style.backgroundColor = '#DDDDDD';
      p.style.color = 'black';
   }
   for (var i = 16; i < 18; i++) {
      var p = document.getElementById(i<10?'P0'+i:'P'+i);
      p.enabled = false;
      p.style.backgroundColor = '#DDDDDD';
      p.style.color = 'black';
   }

   for (i = 0; i < 16; i++)
      for (var j = 0; j < 18; j++) {
         var c = document.getElementById('C' + (i < 10 ? '0' + i : i) + (j < 10 ? '0' + j : j));
         c.mode = 0;
         c.innerHTML = '';
      }

   triggerSendPattern();
   for (i = 0; i < 18; i++)
      triggerSendCell(i);
}

function triggerOrAll() {
   for (var i = 0; i < 16; i++) {
      var p = document.getElementById(i<10?'P0'+i:'P'+i);
      p.enabled = true;
      p.style.backgroundColor = 'darkgreen';
      p.style.color = 'white';
   }
   for (var i = 16; i < 18; i++) {
      var p = document.getElementById(i<10?'P0'+i:'P'+i);
      p.enabled = false;
      p.style.backgroundColor = '#DDDDDD';
      p.style.color = 'black';
   }

   for (i = 0; i < 16; i++)
      for (var j = 0; j < 18; j++) {
         var c = document.getElementById('C' + (i < 10 ? '0' + i : i) + (j < 10 ? '0' + j : j));
         if (i == j && j<16) {
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


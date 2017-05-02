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
   for (var r=0 ; r<16 ; r++) {
      var row = chTable.insertRow(-1);
      row.className = "channelsRow";

      var cell = row.insertCell(-1);
      cell.className = "channelsTd";
      cell.appendChild(document.createTextNode(r));
      cell.style.backgroundColor = OSC.chnColors[r];

      cell = row.insertCell(-1);
      cell.className = "channelsTd";
      var sel = document.createElement('select');
      sel.id = "gain"+r;
      sel.name = "gain";
      sel.setAttribute("onchange", "setParam(this,"+r+")");
      var gains = ["0.5", "1", "2.5", "5", "10", "25", "50", "100"];
      for (var i=0 ; i<gains.length ; i++) {
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
      cb.name = "pzc";
      cb.id = "pzc"+r;
      cb.checked = false;
      cb.setAttribute("onclick", "setParam(this,"+r+")");
      cell.appendChild(cb);

      cell = row.insertCell(-1);
      cell.className = "channelsTd";
      var inp = document.createElement('input');
      inp.type = "text";
      inp.value = "0";
      inp.name = "triggerLevel";
      inp.id = "triggerLevel"+r;
      inp.setAttribute("onkeypress", "keyParam(event, this,"+r+")");
      cell.appendChild(inp);
      cell.appendChild(document.createTextNode(" mV"));
   }

   // hide channels panel
   var channels = document.getElementById("channels");
   channels.t = 0;
   channels.slider = 0;
   channels.visible = false;

   resize();

   // add resize event handler
   window.addEventListener("resize", resize);

   // preselect first channel
   btnChn(0);

   // draw empty scope
   OSC.redraw();

   // schedule first waveform load
   OSC.timer.loadWF = window.setTimeout(loadWF, 10);

   // schedule loadStatus()
   //## OSC.timer.loadStatus = window.setTimeout(loadStatus, 10000);

   // schedule loadScalers()
   //## OSC.timer.loadScalers = window.setTimeout(loadScalers, 1000);
}

function connectionBroken() {
   if (OSC.connected) {
      alert("Connection to server broken.\nPlease reload page.");
      OSC.connected = false;
   }

   if (OSC.timer.loadGl != undefined)
      clearTimeout(OSC.timer.loadGl);
   if (OSC.timer.loadStatus != undefined)
      clearTimeout(OSC.timer.loadStatus);
   if (OSC.timer.loadScalers != undefined)
      clearTimeout(OSC.timer.loadScalers);
   if (OSC.timer.loadWF != undefined)
      clearTimeout(OSC.timer.loadWF);
}

function wdSelect(s) {
   OSC.curBoard = s.selectedIndex;
}

function loadStatus() {
   if (OSC.demoMode) {
      OSC.wdb[OSC.curBoard].temperature = 37.8;
      OSC.wdb[OSC.curBoard].pllLck = true;
      return;
   }

   // send AJAX request
   var req = new XMLHttpRequest();
   req.onreadystatechange = function () {
      if (req.readyState == 4 && req.status == 200) {
         var t = JSON.parse(req.responseText);

         OSC.wdb[OSC.curBoard].temperature = parseFloat(t.temperature);
         OSC.wdb[OSC.curBoard].pllLck = t.pllLck;
         OSC.redraw();
      } else if (req.readyState == 4 && req.status == 0) {
         connectionBroken();
      }
   };

   req.open("GET", "status?b=" + OSC.curBoard + "&r=" + Math.random(), true); // avoid cached results

   try {
      req.send();
      OSC.timer.loadStatus = window.setTimeout(loadStatus, 10000);
   } catch (e) {
      connectionBroken();
   }
}

function loadScalers() {
   if (OSC.demoMode) {
      for (var i = 0; i < 16; i++)
         OSC.wdb[OSC.curBoard].scaler[i] = Math.floor(Math.random() * 9999);
      window.setTimeout(loadScalers, 1000);
      return;
   }

   // send AJAX request
   var req = new XMLHttpRequest();
   req.onreadystatechange = function () {
      if (req.readyState == 4 && req.status == 200) {
         OSC.wdb[OSC.curBoard].scaler = JSON.parse(req.responseText).scaler;
         OSC.redraw();
      } else if (req.readyState == 4 && req.status == 0) {
         connectionBroken();
      }
   };

   req.open("GET", "scalers?b=" + OSC.curBoard + "&r=" + Math.random(), true); // avoid cached results

   try {
      req.send();
      OSC.timer.loadScalers = window.setTimeout(loadScalers, 1000);
   } catch (e) {
      connectionBroken();
   }
}

function populateControls(init)
{
   // populate board list
   var sel = document.getElementById("wdSelect");
   for (var i = 0; i < OSC.gl.nWdb; i++) {
      var opt = document.createElement('option');
      opt.innerHTML = OSC.wdb[i].name;
      opt.value = OSC.wdb[i].name;
      if (sel.childNodes[i + 1] == undefined)
         sel.appendChild(opt);
      else if (sel.childNodes[i + 1].innerHTML != opt.innerHTML)
         sel.replaceChild(opt, sel.childNodes[i + 1]);
   }
   OSC.nWdb = OSC.gl.nWdb;

   // populate config
   document.getElementById("trgSlider").set(OSC.wdb[0].dacTlevel[0] + 0.5);
   document.getElementById("inpTlevel").value = Math.round(OSC.wdb[0].dacTlevel[0] * 1000);
   document.getElementById("trgDelaySlider").set(1 - OSC.wdb[0].triggerDelay / 450);
   document.getElementById("inpTDelay").value = Math.round(OSC.wdb[0].triggerDelay);
   
   if (OSC.wdb[0].triggerEnable) {
      document.config.trigger_mode[0].checked = false;
      document.config.trigger_mode[1].checked = false;
   } else
      document.config.trigger_mode[0].checked = true; //##
   
   if (OSC.wdb[0].triggerFallingEdge) {
      document.getElementById('trgEdgeUp').style.display = "none";
      document.getElementById('trgEdgeDown').style.display = "inline";
   } else {
      document.getElementById('trgEdgeUp').style.display = "inline";
      document.getElementById('trgEdgeDown').style.display = "none";
   }

   document.getElementById("pzc").checked = OSC.wdb[0].fePZC[0];
   document.getElementById("gain").value = OSC.wdb[0].feGain[0];
   
   document.getElementById("inputReadoutSrcDRS").checked = (OSC.wdb[0].readoutSrcSel == 1);
   document.getElementById("inputReadoutSrcADC").checked = (OSC.wdb[0].readoutSrcSel == 2);
   
   document.getElementById("timingCalibSignalEnable").checked = OSC.wdb[0].timingCalibSignalEnable;

   document.getElementById("rangeSelect").value = 0; // ##

   document.getElementById("feMux").checked = OSC.wdb[0].feMux[0];
   document.getElementById("calibBufferEnable").checked = OSC.wdb[0].calibBufferEnable;

   document.getElementById("dcOffsetSlider").set(OSC.wdb[0].dacCalDC / 2 + 0.5);
   document.getElementById("inpDcOffset").value = OSC.wdb[0].dacCalDC * 1000;

   document.getElementById("nominal_sampling_frequency").value = Math.round(OSC.wdb[0].drsSampleFreq/1000 * 10) / 10;
   document.getElementById("actual_sampling_frequency").innerHTML = OSC.wdb[0].drsSampleFreq/1000 + " GSPS";

   document.getElementById("calib1").checked = OSC.wp.ofsCalib1;
   document.getElementById("calib2").checked = OSC.wp.ofsCalib2;
   document.getElementById("calib3").checked = OSC.wp.gainCalib;
   document.getElementById("calib4").checked = OSC.wp.rangeCalib;
   document.getElementById("spikes").checked = OSC.wp.removeSpikes;
   document.getElementById("rotate").checked = OSC.wp.rotateWaveform;

   document.getElementById("tcalib1").checked = OSC.wp.timeCalib1;
   document.getElementById("tcalib2").checked = OSC.wp.timeCalib2;
   document.getElementById("tcalib3").checked = OSC.wp.timeCalib3;

   document.getElementById("clksource").checked = (OSC.wdb[0].daqClkSrcSel == 1);

   if (init) {
      // set scale according to sampling frequency
      if (OSC.wdb[0].drsSampleFreq < 2000)
         OSC.wfTScaleIndex = 6; // 100 ns
      else if (OSC.wdb[0].drsSampleFreq < 4000)
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
         loadWdb(-1, init); // daisy-chain for loading all WDBs
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

function loadWdb(b, init) {
   // send AJAX request
   var req = new XMLHttpRequest();
   req.onreadystatechange = function () {
      if (req.readyState == 4 && req.status == 200) {
         OSC.wdb = JSON.parse(req.responseText).wdb;
         populateControls(init);
         OSC.connected = true;
      } else if (req.readyState == 4 && req.status == 0) {
         connectionBroken();
      }
   };

   req.open("GET", "wdb?b=" + b + "&r=" + Math.random(), true); // avoid cached results
   req.send();
}

function setParam(e, channel) {
   if (OSC.demoMode)
      return;

   var req = new XMLHttpRequest();

   req.onreadystatechange = function (e) {
      if (req.readyState == 4 && req.status == 204) {
         // success
      }
   };

   if (e.name == "triggerLevel" && channel == undefined) {
      for (var i=0 ; i<16 ; i++)
         document.getElementById("triggerLevel"+i).value = e.value;
   }

   if (e.name == "gain" && channel == undefined) {
      for (var i=0 ; i<16 ; i++)
         document.getElementById("gain"+i).value = e.value;
   }

   if (e.name == "pzc" && channel == undefined) {
      for (var i=0 ; i<16 ; i++)
         document.getElementById("pzc"+i).checked = e.checked;
   }

   if (e.name == "clock_source" && e.checked == true) {
      if (OSC.wdb[OSC.curBoard].scaler[17] < 79E6)
         dlgMessage("Warning", "No external clock present");
   }
   
   var uri = "param/" + OSC.curBoard + "/"+ e.name;
   if (channel != undefined)
      uri += "/" + channel;

   if (e.type == "select-one") {
      if (e.selectedIndex != -1) {
         req.open("PUT", uri, true);
         req.send(e.selectedOptions[0].value);
      }
   } else if (e.type == "checkbox") {
      req.open("PUT", uri, true);
      req.send(e.checked ? "1" : "0");
   } else if (e.type == "radio") {
      req.open("PUT", uri, true);
      req.send(e.value);
   } else if (e.type == "text") {
      req.open("PUT", uri, true);
      if (e.name == "triggerLevel") {
         req.send(parseInt(e.value) / 1000);
      } else if (e.name == "range") {
         req.send(parseInt(e.value));
      } else if (e.name == "dc_offset") {
         req.send(parseInt(e.value) / 1000);
      } else if (e.name == "nominal_sampling_frequency") {
         req.send(parseFloat(e.value));
      } else
         req.send(e.value);
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
      if (input.id == "inpTlevel") {
         if (input.value < -500)
            input.value = -500;
         if (input.value > 500)
            input.value = 500;
         document.getElementById("trgSlider").set(input.value/1000 + 0.5);
      }
      
      if (input.id == "inpTDelay") {
         if (input.value < 0)
            input.value = 0;
         if (input.value > 450)
            input.value = 450;
         document.getElementById("trgDelaySlider").set(1 - input.value/450);
      }
      
      setParam(input, channel);
   }
}

function doVCalib() {
   if (OSC.demoMode) {
      alert("Not available in demo mode");
      return;
   }
   progressOldBoard = OSC.curBoard;

   var req = new XMLHttpRequest();
   req.open("PUT", "vcalib");
   req.send();
}

function doTCalib() {
   if (OSC.demoMode) {
      alert("Not available in demo mode");
      return;
   }
   progressOldBoard = OSC.curBoard;

   var req = new XMLHttpRequest();
   req.open("PUT", "tcalib");
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
            var t = i * 1E-9 / OSC.wdb[0].drsSampleFreq;
            wf.T[c][i] = t;
            wf.U[c][i] = Math.sin((wf.T[c][i] + c * 1E-9) * OSC.wdb[0].drsSampleFreq /
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

      // create 18 empty waveforms
      var wf = {T: [], U: [], type: 1};
      for (var i = 0; i < 18; i++) {
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
            i++;
            OSC.wd = floatArray[i++];
            wf.type = 2; // indicate delta-T array

            progressInd = floatArray[i++];

            e = document.getElementById("progressIndTcalib");
            e.style.width = (progressInd * 270) + "px";

            document.getElementById("wdSelect").selectedIndex = OSC.wd;
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

/*---- UI event handler ----*/

function resize()
// called when screen got resized
{
   var ctls = document.getElementById("controls");
   var config = document.getElementById("config");
   var channels = document.getElementById("channels");

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

      if (channels.slider > 0)
         channels.style.display = "block";
      else
         channels.style.display = "none";
      channels.style.opacity = 1;

      OSC.resize(document.documentElement.clientWidth - ctls.offsetWidth -
         config.offsetWidth * config.slider -
         channels.offsetWidth * channels.slider,
         document.documentElement.clientHeight);

      // config full visible (configSlider = 1), hidden (configSlider = 0)
      ctls.style.left = (document.documentElement.clientWidth - ctls.offsetWidth -
         config.offsetWidth * config.slider -
         channels.offsetWidth * channels.slider) + "px";

      channels.style.left = (document.documentElement.clientWidth -
         config.offsetWidth * config.slider - channels.offsetWidth * channels.slider) + "px";
      channels.style.height = document.documentElement.clientHeight + "px";

      config.style.left = (document.documentElement.clientWidth -
         config.offsetWidth * config.slider) + "px";
      config.style.height = document.documentElement.clientHeight + "px";

      OSC.resize(document.documentElement.clientWidth - ctls.offsetWidth -
         config.offsetWidth * config.slider -
         channels.offsetWidth * channels.slider,
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
      btnChn(-1);
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
   } else {
      OSC.running = true;
      e.innerHTML = "Stop";
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
   }

   OSC.timer.loadWF = window.setTimeout(loadWF, 10);
}

function btnChn(c)
// select channel "c" and set controls to reflect channel status (c == -1 means all channels)
{
   if (c != -1) {
      if (OSC.currentChn == c)
         OSC.chOn[c] = !OSC.chOn[c];
      else
         OSC.chOn[c] = true;
   }

   OSC.currentChn = c;
   var o = document.getElementById("chOn");
   if (c == -1)
      o.innerHTML = "On";
   else
      o.innerHTML = OSC.chOn[c] ? "Off" : "On";

   // set scale according to first active channel
   var index = c;
   if (c == -1) {
      for (index = 0; index < 18; index++)
         if (OSC.chOn[index])
            break;
      if (index == 18)
         index = 0;
   }
   document.getElementById("UScale").innerHTML = OSC.UScaleTable[OSC.wfScaleIndex[index]][1];

   // set blue border of active channel buttons
   for (var i = 0; i < 18; i++) {
      var cb = document.getElementById("ch" + i);
      if (cb == undefined)
         continue;
      if (i == c || (c == -1 && i < 16))
         cb.style.border = "3px solid blue";
      else
         cb.style.border = "2px solid #C0C0C0";
      if (OSC.chOn[i])
         cb.style.backgroundColor = OSC.chnColors[i];
      else
         cb.style.backgroundColor = "#E0E0E0";
   }

   OSC.clearPersistency();
   OSC.redraw();
}

function btnOn()
// turn current channel(s) on and off
{
   for (var i = 0; i < 16; i++) {
      if (OSC.currentChn != -1 && i != OSC.currentChn)
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
   bt.innerHTML = bt.innerHTML == "On" ? "Off" : "On";

   OSC.clearPersistency();
   OSC.redraw();
}

function btnScale(inc)
// change vertical scale, update label
{
   if (OSC.currentChn == -1) {
      for (var i = 0; i < 18; i++)
         if (OSC.chOn[i])
            break;
      if (i == 18)
         i = 0;
   } else
      i = OSC.currentChn;

   var index = OSC.wfScaleIndex[i] + inc;
   if (index < 0)
      index = 0;
   if (index == OSC.UScaleTable.length)
      index--;

   for (i = 0; i < 18; i++) {
      if (OSC.currentChn != -1 && i != OSC.currentChn)
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
   for (var i = 0; i < 18; i++) {
      if (OSC.currentChn != -1 && i != OSC.currentChn)
         continue;
      OSC.wfOffset[i] = value - 0.5;
   }
   OSC.calcScaleOffset();
   OSC.clearPersistency();
   OSC.redraw();
}

var tLevelLast = -1;

function sldTLevel(value) {
   if (OSC.demoMode)
      return;

   value = Math.round((value - 0.5)*1000)/1000; // convert to V

   if (value == tLevelLast) // only send if changed
      return;
   
   tLevelLast = value;
   var req = new XMLHttpRequest();
   req.open("PUT", "gl/"+OSC.curBoard+"/triggerLevel", true);
   req.send(value);

   document.getElementById("inpTlevel").value = value * 1000;
   for (var i=0 ; i<16 ; i++) {
      OSC.wdb[OSC.curBoard].dacTlevel[i] = value;
      document.getElementById("triggerLevel"+i).value = value * 1000;
   }
   
   var d = new Date();
   OSC.lastTriggerLevelChange = d.getTime();
   clearStat();
   OSC.redraw();
}

function sldTDelay(value) {
   if (OSC.demoMode)
      return;
   var del = 450 - Math.round(value * 450);
   var req = new XMLHttpRequest();
   req.open("PUT", "gl/"+OSC.curBoard+"/triggerDelay", true);
   req.send(del);

   OSC.wdb[OSC.curBoard].triggerDelay = del;
   document.getElementById("inpTDelay").value = del;
   clearStat();
}

function btnTedge(value) {
   if (OSC.demoMode)
      return;
   var req = new XMLHttpRequest();
   req.open("PUT", "gl/"+OSC.curBoard+"/triggerFallingEdge", true);
   req.send(value);

   OSC.wdb[OSC.curBoard].triggerFallingEdge = (value == 1);

   if (value == 1) {
      document.getElementById('trgEdgeUp').style.display = "none";
      document.getElementById('trgEdgeDown').style.display = "inline";
   } else {
      document.getElementById('trgEdgeUp').style.display = "inline";
      document.getElementById('trgEdgeDown').style.display = "none";
   }
}

function sldDcOffset(value) {
   if (OSC.demoMode)
      return;
   var req = new XMLHttpRequest();
   req.open("PUT", "gl/"+OSC.curBoard+"/dc_offset", true);
   req.send(Math.round(value * 2000 - 1000) / 1000);

   document.getElementById("inpDcOffset").value = Math.round(value * 2000 - 1000);
}

function setRange(s) {
   if (OSC.demoMode)
      return;
   var req = new XMLHttpRequest();
   req.open("PUT", "gl/"+OSC.curBoard+"/range", true);
   req.send(parseFloat(s.value));
}

function btnOfsZero() {
   for (i = 0; i < 18; i++) {
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
   for (i = 0; i < 18; i++) {
      if (OSC.chOn[i])
         n++;
   }

   // calculate offset between channels
   var d = 1 / (n + 1);

   // set offset
   var o = 0.5 - d;
   for (i = 0; i < 18; i++) {
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

function btnChannels() {
   var channels = document.getElementById("channels");
   channels.visible = !channels.visible;
   channels.t = 0;
   window.setTimeout(channelsSlide, 20);
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
      dlgMessage("Warning", "Please enter a valid file name");
      return;
   }

   var ne = document.getElementById("nevents").value;
   if (isNaN(parseInt(ne)) || parseInt(ne) < 1 || parseInt(ne) > 1E6) {
      dlgMessage("Warning", "Please enter a valid number of events");
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
   param += document.getElementById("saveboards").selectedOptions[0].value;
   param += "\n";
   param += ne;
   req.open("PUT", "save", true);
   req.send(param);

   dlgHide('dlgSave');
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

function channelsSlide() {
   var channels = document.getElementById("channels");

   channels.t++;

   if (channels.visible) {
      channels.slider = 1 - (1 - channels.t / 10) * (1 - channels.t / 10);
   } else {
      channels.slider = (1 - channels.t / 10) * (1 - channels.t / 10);
   }

   resize();

   if (channels.t < 10)
      window.setTimeout(channelsSlide, 20);
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
         for (i = 0; i < OSC.GL.board.length; i++) {
            var o = document.createElement("option");
            o.value = i;
            o.innerHTML = OSC.GL.board[i].name;
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
         for (i = 0; i < 18; i++) {
            o = document.createElement("option");
            o.value = i;
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

//
//  wds.js
//  WaveDAQ Server Application JavaScript Code
//
//  Created by Stefan Ritt on 5/8/15.
//

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
   resize();

   // add resize event handler
   window.addEventListener("resize", resize);

   // preselect first channel
   btnChn(0);

   // draw empty scope
   OSC.redraw();

   // schedule first waveform load
   window.setTimeout(loadWF, 10);

   // schedule loadStatus()
   window.setTimeout(loadStatus, 10000);

   // schedule loadScalers()
   window.setTimeout(loadScalers, 1000);
}

function wdSelect(s) {
   OSC.board = s.selectedIndex;
}

function loadStatus() {
   // send AJAX request
   var req = new XMLHttpRequest();
   req.onreadystatechange = function () {
      if (req.readyState == 4 && req.status == 200) {
         var t = JSON.parse(req.responseText);

         OSC.GL.board[OSC.board].temperature = parseFloat(t.temp);
         OSC.GL.board[OSC.board].pll_locked = t.pll_locked;
      }
   };

   req.open("GET", "status?b=" + OSC.board + "&r=" + Math.random(), true); // avoid cached results
   req.send();

   window.setTimeout(loadStatus, 10000);
}

function loadScalers() {
   // send AJAX request
   var req = new XMLHttpRequest();
   req.onreadystatechange = function () {
      if (req.readyState == 4 && req.status == 200) {
         OSC.GL.board[OSC.board].scaler = JSON.parse(req.responseText).scaler;
      }
   };

   req.open("GET", "scalers?b=" + OSC.board + "&r=" + Math.random(), true); // avoid cached results
   req.send();

   window.setTimeout(loadScalers, 1000);
}

function loadGl(init) {
   // send AJAX request
   var req = new XMLHttpRequest();
   req.onreadystatechange = function () {
      if (req.readyState == 4 && req.status == 200) {
         OSC.GL = JSON.parse(req.responseText);

         // populate board list
         var sel = document.getElementById("wdSelect");
         for (var i = 0; i < OSC.GL.board.length; i++) {
            var opt = document.createElement('option');
            opt.innerHTML = OSC.GL.board[i].name;
            opt.value = OSC.GL.board[i].name;
            if (sel.childNodes[i + 1] == undefined)
               sel.appendChild(opt);
            else if (sel.childNodes[i + 1].innerHTML != opt.innerHTML)
               sel.replaceChild(opt, sel.childNodes[i + 1]);
         }
         OSC.nWd = OSC.GL.board.length;

         // populate config
         document.getElementById("trgSlider").set(OSC.GL.board[0].trigger_level + 0.5);
         document.getElementById("inpTLevel").value = Math.round(OSC.GL.board[0].trigger_level * 1000);
         document.getElementById("trgDelaySlider").set(1 - OSC.GL.board[0].trigger_delay / 450);
         document.getElementById("inpTDelay").value = Math.round(OSC.GL.board[0].trigger_delay);
         document.config.trigger_mode[OSC.GL.trigger_mode].checked = true;

         document.getElementById("pzc").checked = OSC.GL.board[0].pzc;
         document.config.gain[parseInt(OSC.GL.board[0].gain)].checked = true;
         document.getElementById("osctca_flag").checked = OSC.GL.osctca_flag;

         document.getElementById("rangeSelect").value = OSC.GL.board[0].range;

         document.getElementById("mux_flag").checked = OSC.GL.mux_flag;
         document.getElementById("dcv_flag").checked = OSC.GL.dcv_flag;

         document.getElementById("dcvSlider").set(OSC.GL.dcv / 2 + 0.5);
         document.getElementById("inpDcv").value = OSC.GL.dcv * 1000;

         document.getElementById("nominal_sampling_frequency").value = Math.round(OSC.GL.actual_sampling_frequency * 10) / 10;
         document.getElementById("actual_sampling_frequency").innerHTML = OSC.GL.actual_sampling_frequency + " GSPS";

         document.getElementById("calib1").checked = OSC.GL.ofs_calib1_flag;
         document.getElementById("calib2").checked = OSC.GL.ofs_calib2_flag;
         document.getElementById("calib3").checked = OSC.GL.gain_calib_flag;
         document.getElementById("calib4").checked = OSC.GL.range_calib_flag;
         document.getElementById("spikes").checked = OSC.GL.remove_spikes;
         document.getElementById("rotate").checked = OSC.GL.rotate_flag;

         document.getElementById("tcalib1").checked = OSC.GL.time_calib1_flag;
         document.getElementById("tcalib2").checked = OSC.GL.time_calib2_flag;
         document.getElementById("tcalib3").checked = OSC.GL.time_calib3_flag;
         document.getElementById("clksource").checked = OSC.GL.clock_source;

         if (init) {
            // set scale according to sampling frequency
            if (OSC.GL.actual_sampling_frequency < 2)
               OSC.wfTScaleIndex = 6; // 100 ns
            else if (OSC.GL.actual_sampling_frequency < 4)
               OSC.wfTScaleIndex = 5; // 50 ns
            else
               OSC.wfTScaleIndex = 4; // 20 ns
            setTScale();
         }
      }
   };
   req.open("GET", "gl?r=" + Math.random(), true); // avoid cached results
   req.send();
}

function setGl(e) {
   var req = new XMLHttpRequest();

   req.onreadystatechange = function () {
      if (req.readyState == 4 && req.status == 204) {
         loadGl();
      }
   };

   if (e.type == "checkbox") {
      req.open("PUT", "gl/" + e.name, true);
      req.send(e.checked ? "1" : "0");
   } else if (e.type == "radio") {
      req.open("PUT", "gl/" + e.name, true);
      req.send(e.value);
   } else if (e.type == "text") {
      req.open("PUT", "gl/" + e.name, true);
      if (e.name == "trigger_level") {
         req.send(parseInt(e.value) / 1000);
      } else if (e.name == "range") {
         req.send(parseInt(e.value));
      } else if (e.name == "dcv") {
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
   }
   if (e.name == "persist") {
      OSC.disp.persistency = e.checked;
      OSC.resizeCanvas();
   }
}

function keyGl(event, input) {
   var charCode = (typeof event.which == "number") ? event.which : event.keyCode;

   if (charCode == 13) {
      setGl(input);
   }
}

function doVCalib() {
   progressOldBoard = OSC.board;

   var req = new XMLHttpRequest();
   req.open("PUT", "vcalib");
   req.send();
}

function doTCalib() {
   progressOldBoard = OSC.board;

   var req = new XMLHttpRequest();
   req.open("PUT", "tcalib");
   req.send();
}

function loadBuild() {
   // send AJAX request
   var req = new XMLHttpRequest();
   req.onreadystatechange = function () {
      if (req.readyState == 4 && req.status == 200) {
         var build = JSON.parse(req.responseText);
         var e = document.getElementById("build");
         e.innerHTML = "Built " + build.build;
      }
   };
   req.open("GET", "build?r=" + Math.random(), true); // avoid cached results
   req.send();
}

function loadWF() {
   // wait until list of boards has been loaded
   if (OSC.nWd == 0) {
      window.setTimeout(loadWF, 10);
      return;
   }

   var i, c, chn;

   if (false) { // set true to simulate waveforms
      // create 16 empty waveforms
      var wf = {T: [], U: []};
      for (var c = 0; c < 16; c++) {
         wf.T[c] = [];
         wf.U[c] = [];
         for (i = 0; i < 1024; i++) {
            wf.T[c][i] = i * 1E-9;
            wf.U[c][i] = Math.sin(wf.T[c][i] / 50 / 1E-9) / 4 + (Math.random() - 0.5) / 30;
         }
      }

      if (OSC.running)
         window.setTimeout(loadWF, 10); // schedule next waveform read

      OSC.sendWaveforms(wf);
      OSC.redraw();
      return;
   }

   // build mask with active channels
   for (chn = 0, c = 0; c < 16; c++)
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
      window.setTimeout(loadWF, 10); // schedule next waveform read
      return;
   }

   // send AJAX request
   OSC.req = new XMLHttpRequest();
   OSC.req.onreadystatechange = receiveWF;
   OSC.req.open("GET", "wf?b=" + OSC.board + "&c=" + chn + "&r=" + Math.random(), true); // avoid cached results
   OSC.req.responseType = "arraybuffer";
   OSC.req.send();
}

function receiveWF() {
   if (OSC.req.readyState == 4 && OSC.req.status == 200) {
      // this.wf = JSON.parse(OSC.req.responseText); // use this for JSON encoded data

      // create 16 empty waveforms
      var wf = {T: [], U: [], type: 1};
      for (var i = 0; i < 16; i++) {
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
            var f = intArray[i++];
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
               if (xt <=  OSC.x2)
                  OSC.i2 = j;
            }

            // check for progress bar
            if (progressInd > 0) {
               progressInd = 0;
               var e = document.getElementById("progressIndVcalib");
               e.style.width = "0";
               e = document.getElementById("progressIndTcalib");
               e.style.width = "0";

               document.getElementById("wdSelect").selectedIndex = progressOldBoard;
               document.getElementById("btnVCalib").innerHTML = "Execute Voltage Calibration";
               document.getElementById("btnVCalib").disabled = false;
               document.getElementById("btnTCalib").innerHTML = "Execute Time Calibration";
               document.getElementById("btnTCalib").disabled = false;
               OSC.board = progressOldBoard;

               window.setTimeout(loadGl, 10);
            }

         } else if (responseType == 2) { // voltage array
            i++;
            OSC.idle = false;
            OSC.wd = intArray[i++];
            f = intArray[i++];
            c = intArray[i++];
            n = intArray[i++];
            for (j = 0; j < n; j++)
               wf.U[c][j] = floatArray[i++];
            OSC.demo = (OSC.wd == 0xFF);

         } else if (responseType == 10) { // vcalib progress data
            var b = intArray[1];
            progressInd = floatArray[2];

            e = document.getElementById("progressIndVcalib");
            e.style.width = (progressInd * 270) + "px";

            document.getElementById("wdSelect").selectedIndex = b;
            document.getElementById("btnVCalib").innerHTML = document.getElementById("wdSelect").value;
            document.getElementById("btnVCalib").disabled = true;

            window.setTimeout(loadWF, 250);
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
         window.setTimeout(loadWF, 250);
         OSC.sendWaveforms(wf);

      } else {
         // schedule next waveform read
         if (OSC.running)
            window.setTimeout(loadWF, 10);

         // send waveforms to oscilloscope
         if (!OSC.idle)
            OSC.sendWaveforms(wf);
      }

      // redraw oscilloscope to show new waveforms
      OSC.redraw();
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
         config.offsetWidth * config.slider,
         document.documentElement.clientHeight);

      // config full visible (configSlider = 1), hidden (configSlider = 0)
      ctls.style.left = (document.documentElement.clientWidth - ctls.offsetWidth -
         config.offsetWidth * config.slider) + "px";
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
      window.setTimeout(loadWF, 10);
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

   window.setTimeout(loadWF, 10);
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
      for (index = 0; index < 16; index++)
         if (OSC.chOn[index])
            break;
      if (index == 16)
         index = 0;
   }
   document.getElementById("UScale").innerHTML = OSC.UScaleTable[OSC.wfScaleIndex[index]][1];

   // set blue border of active channel buttons
   for (var i = 0; i < 16; i++) {
      var cb = document.getElementById("ch" + i);
      if (i == c || c == -1)
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
      for (var i = 0; i < 16; i++)
         if (OSC.chOn[i])
            break;
      if (i == 16)
         i = 0;
   } else
      i = OSC.currentChn;

   var index = OSC.wfScaleIndex[i] + inc;
   if (index < 0)
      index = 0;
   if (index == OSC.UScaleTable.length)
      index--;

   for (i = 0; i < 16; i++) {
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
   for (var i = 0; i < 16; i++) {
      if (OSC.currentChn != -1 && i != OSC.currentChn)
         continue;
      OSC.wfOffset[i] = value - 0.5;
   }
   OSC.calcScaleOffset();
   OSC.clearPersistency();
   OSC.redraw();
}

function sldTLevel(value) {
   var req = new XMLHttpRequest();
   req.open("PUT", "gl/trigger_level", true);
   req.send(Math.round(value * 1000 - 500) / 1000);

   document.getElementById("inpTLevel").value = Math.round(value * 1000 - 500);
   var d = new Date();
   OSC.lastTriggerLevelChange = d.getTime();
   clearStat();
}

function sldTDelay(value) {
   var del = 450 - Math.round(value * 450);
   var req = new XMLHttpRequest();
   req.open("PUT", "gl/trigger_delay", true);
   req.send(del);

   document.getElementById("inpTDelay").value = del;
   clearStat();
}

function sldDcv(value) {
   var req = new XMLHttpRequest();
   req.open("PUT", "gl/dcv", true);
   req.send(Math.round(value * 2000 - 1000) / 1000);

   document.getElementById("inpDcv").value = Math.round(value * 2000 - 1000);
}

function setRange(s) {
   var req = new XMLHttpRequest();
   req.open("PUT", "gl/range", true);
   req.send(parseFloat(s.value));
}

function btnOfsZero() {
   for (i = 0; i < 16; i++) {
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
   for (i = 0; i < 16; i++) {
      if (OSC.chOn[i])
         n++;
   }

   // calculate offset between channels
   var d = 1 / (n + 1);

   // set offset
   var o = 0.5 - d;
   for (i = 0; i < 16; i++) {
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
   var wfWidth = 1024 / OSC.GL.actual_sampling_frequency * 1E-9;
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
         for (i = 0; i < 16; i++) {
            o = document.createElement("option");
            o.value = i;
            o.innerHTML = "CH" + i;
            if (prev) {
               if (prev.param[pi].value+1 == i)
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

function dispHisto(c)
{
   OSC.disp.histo = c.checked;
   OSC.resizeCanvas();
}
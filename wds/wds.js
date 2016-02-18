//
//  wds.js
//  WaveDAQ Server Application JavaScript Code
//
//  Created by Stefan Ritt on 5/8/15.
//

var OSC; // global scope object

var progressInd = 0;
var progressOldBoard = 0;

function init()
{
   // prevent mouse events to go up to the browser
   var c = document.getElementById("controls");
   c.addEventListener("click", function(e){e.preventDefault()});
   c.addEventListener("mousemove", function(e){e.preventDefault()});

   var c = document.getElementById("scope");
   c.addEventListener("click", function(e){e.preventDefault()});
   c.addEventListener("mousemove", function(e){e.preventDefault()});

   // capture all key events
   document.addEventListener("keypress", oscKeypress, false);
   
   // create Scope object
   OSC = new Oscilloscope(document.getElementById("scope"));

   // size to fit screen
   var ctls = document.getElementById("controls");
   var config = document.getElementById("config");
   OSC.resize(document.documentElement.clientWidth - ctls.offsetWidth - config.offsetWidth,
              document.documentElement.clientHeight);
   ctls.style.left = (document.documentElement.clientWidth - ctls.offsetWidth - config.offsetWidth) + "px";
   config.style.left = (document.documentElement.clientWidth - config.offsetWidth) + "px";
 
   // add resize event handler
   window.addEventListener("resize", resize);

   // preselect first channel
   btnChn(0);
   
   // draw empty scope
   OSC.redraw();
   
   // load globals including board list from server
   loadGl();
   
   // load build and put into about box
   loadBuild();
   
   // schedule first waveform load
   window.setTimeout(loadWF, 10);
}

function loadGl()
{
   // send AJAX request
   var req = new XMLHttpRequest();
   req.onreadystatechange = function() {
      if (req.readyState == 4 && req.status == 200) {
         OSC.GL = JSON.parse(req.responseText);
         
         // populate board list
         var sel = document.getElementById("wdSelect");
         for (var i=0 ; i<OSC.GL.boards.length ; i++) {
            var opt = document.createElement('option');
            opt.innerHTML = OSC.GL.boards[i].name;
            opt.value = OSC.GL.boards[i].name;
            sel.appendChild(opt);
         }
         OSC.nWd = OSC.GL.boards.length;

         // populate config
         document.getElementById("calib1").checked = (OSC.GL.ofs_calib1_flag == "1");
         document.getElementById("calib2").checked = (OSC.GL.ofs_calib2_flag == "1");
         document.getElementById("spikes").checked = (OSC.GL.remove_spikes == "1");
         document.getElementById("rotate").checked = (OSC.GL.rotate_flag == "1");
      }
   };
   req.open("GET", "gl?r=" + Math.random(), true); // avoid cached results
   req.send();
}

function setGl(e)
{
   var req = new XMLHttpRequest();
   req.open("PUT", "gl/" + e.name, true);
   req.send(e.checked ? "1" : "0");
}

function btnVCalib(e)
{
   progressOldBoard = document.getElementById("wdSelect").selectedIndex;

   var req = new XMLHttpRequest();
   req.open("PUT", "vcalib");
   req.send();
}

function loadBuild()
{
   // send AJAX request
   var req = new XMLHttpRequest();
   req.onreadystatechange = function() {
      if (req.readyState == 4 && req.status == 200) {
         build = JSON.parse(req.responseText);
         var e = document.getElementById("build");
         e.innerHTML = "Built "+build.build;
      }
   };
   req.open("GET", "build?r=" + Math.random(), true); // avoid cached results
   req.send();
}

function loadWF()
{
   // wait until list of boards has been loaded
   if (OSC.nWd == 0) {
      window.setTimeout(loadWF, 10);
      return;
   }
   
   if (false) { // set true to simulate waveforms
      // create 16 empty waveforms
      var wf = {T:[], U:[]};
      for (var i=0 ; i<16 ; i++) {
         wf.T[i] = [];
         wf.U[i] = [];
      }
      for (c=0 ; c<16 ; c++) {
         for (i=0 ; i<1024 ; i++) {
            wf.T[c][i] = i*1E-9;
            wf.U[c][i] = Math.sin(wf.T[c][i] / 50 / 1E-9) / 4 + (Math.random()-0.5) / 30;
         }
      }
      
      if (OSC.running)
         window.setTimeout(loadWF, 10); // schedule next waveform read
      
      OSC.sendWaveforms(wf);
      OSC.redraw();
      return;
   }
   
   // build mask with active channels
   for (var chn=0,c=0 ; c<16 ; c++)
      if (OSC.chOn[c])
         chn |= (1<<c);
   
   if (chn == 0 && OSC.running) {
      window.setTimeout(loadWF, 10); // schedule next waveform read
      return;
   }
   
   // get active board
   var board = document.getElementById("wdSelect").selectedIndex;
   
   // send AJAX request
   OSC.req = new XMLHttpRequest();
   OSC.req.onreadystatechange = receiveWF;
   OSC.req.open("GET", "wf?b=" + board + "&c=" + chn + "&r=" + Math.random(), true); // avoid cached results
   OSC.req.responseType = "arraybuffer";
   OSC.req.send();
}

function receiveWF()
{
   if (OSC.req.readyState == 4 && OSC.req.status == 200) {
      // this.wf = JSON.parse(OSC.req.responseText); // use this for JSON encoded data
      
      // create 16 empty waveforms
      var wf = {T:[], U:[]};
      for (var i=0 ; i<16 ; i++) {
         wf.T[i] = [];
         wf.U[i] = [];
      }
      
      var intArray = new Uint32Array(OSC.req.response);
      var floatArray = new Float32Array(OSC.req.response);
      
      for (var i=0 ; i<intArray.length ; ) {
         if (intArray[i] == 0) {        // idle message
            OSC.idle = true;
            break;
         } else if (intArray[i] == 1) { // time array
            i++;
            OSC.wd = intArray[i++];
            var f = intArray[i++];
            var c = intArray[i++];
            var n = intArray[i++];
            for (var j=0 ; j<n ; j++)
               wf.T[c][j] = floatArray[i++];
            
            // check for progress bar
            if (progressInd > 0) {
               progressInd = 0;
               var e = document.getElementById("progressIndVcalib");
               e.style.width = "0";
               
               document.getElementById("wdSelect").selectedIndex = progressOldBoard;
            }
               
         } else if (intArray[i] == 2) { // voltage array
            i++;
            OSC.idle = false;
            OSC.wd = intArray[i++];
            var f = intArray[i++];
            var c = intArray[i++];
            var n = intArray[i++];
            for (var j=0 ; j<n ; j++)
               wf.U[c][j] = floatArray[i++];
            OSC.demo = (OSC.wd == 0xFF);
         } else if (intArray[i] == 10) { // progress data
            var b = floatArray[1];
            progressInd = floatArray[2];

            var e = document.getElementById("progressIndVcalib");
            e.style.width = (progressInd*280) + "px";
            
            document.getElementById("wdSelect").selectedIndex = b;

            window.setTimeout(loadWF, 250);
            return;
         } else {
            alert("WDS: Invalid binary data received form server");
            break;
         }
      }
      
      if (OSC.running)
         window.setTimeout(loadWF, 10); // schedule next waveform read
      
      // send waveforms to oscilloscope
      if (!OSC.idle)
         OSC.sendWaveforms(wf);
      
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
      OSC.resize(document.documentElement.clientWidth,
                 document.documentElement.clientHeight);
      ctls.style.left = (document.documentElement.clientWidth) + "px";
      config.style.left = (document.documentElement.clientWidth) + "px";
   }  else {
      OSC.resize(document.documentElement.clientWidth - ctls.offsetWidth - config.offsetWidth,
                 document.documentElement.clientHeight);
      ctls.style.left = (document.documentElement.clientWidth - ctls.offsetWidth - config.offsetWidth) + "px";
      config.style.left = (document.documentElement.clientWidth - config.offsetWidth) + "px";
      config.style.height = document.documentElement.clientHeight + "px";
   }
}

function oscKeypress(e)
{
   var charCode = (typeof e.which == "number") ? e.which : e.keyCode;
   
   if (charCode == 's'.charCodeAt(0)) {
      btnStop();
   }

   if (charCode == ']'.charCodeAt(0)) {
      var ctls = document.getElementById("controls");
      if (ctls.hidden == true)
         ctls.hidden = false;
      else
         ctls.hidden = true;
      resize();
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
      for (index=0 ; index<16 ; index++)
         if (OSC.chOn[index])
            break;
      if (index == 16)
         index = 0;
   }
   document.getElementById("UScale").innerHTML = OSC.UScaleTable[OSC.wfScaleIndex[index]][1];

   // set blue border of active channel buttons
   for (i=0 ; i<16 ; i++) {
      var cb = document.getElementById("ch"+i);
      if (i == c || c == -1)
         cb.style.border = "3px solid blue";
      else
         cb.style.border = "2px solid #C0C0C0";
      if (OSC.chOn[i])
         cb.style.backgroundColor = OSC.chnColors[i];
      else
         cb.style.backgroundColor = "#E0E0E0";
   }
   
   OSC.redraw();
}

function btnOn()
// turn current channel(s) on and off
{
   for (i=0 ; i<16 ; i++) {
      if (OSC.currentChn != -1 && i != OSC.currentChn)
         continue;
      var cb = document.getElementById("ch"+i);
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
   
   OSC.redraw();
}

function btnScale(inc)
// change vertical scale, update label
{
   if (OSC.currentChn == -1) {
      for (i=0 ; i<16 ; i++)
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
   
   for (i=0 ; i<16 ; i++) {
      if (OSC.currentChn != -1 && i != OSC.currentChn)
         continue;
      
      OSC.wfScaleIndex[i] = index;
      OSC.wfScale[i] = OSC.UScaleTable[OSC.wfScaleIndex[i]][0];
      document.getElementById("UScale").innerHTML = OSC.UScaleTable[OSC.wfScaleIndex[i]][1];
   }
   OSC.calcScaleOffset();
   OSC.redraw();
}

function btnTScale(inc)
// change horizontal scale, update label
{
   if (OSC.currentChn == -1) {
      for (i=0 ; i<16 ; i++)
         if (OSC.chOn[i])
            break;
      if (i == 16)
         i = 0;
   } else
      i = OSC.currentChn;
   
   var index = OSC.wfTScaleIndex + inc;
   if (index < 0)
      index = 0;
   if (index == OSC.TScaleTable.length)
      index--;
   
   OSC.wfTScaleIndex = index;
   OSC.wfTScale = OSC.TScaleTable[OSC.wfTScaleIndex][0];
   document.getElementById("TScale").innerHTML = OSC.TScaleTable[OSC.wfTScaleIndex][1];

   OSC.calcScaleOffset();
   OSC.redraw();
}

function sldUOffset(value)
{
   for (i=0 ; i<16 ; i++) {
      if (OSC.currentChn != -1 && i != OSC.currentChn)
         continue;
      OSC.wfOffset[i] = value-0.5;
   }
   OSC.calcScaleOffset();
   OSC.redraw();
}

function btnOfsZero()
{
   for (i=0 ; i<16 ; i++) {
      if (OSC.chOn[i])
         OSC.wfOffset[i] = 0;
   }
   OSC.calcScaleOffset();
   OSC.redraw();
   
   var sl = document.getElementsByName("ctrlVSlider");
   sl[0].position = 0.5;
   sl[0].draw();
}

function btnOfsDist()
{
   // count active channels
   var n = 0;
   for (i=0 ; i<16 ; i++) {
      if (OSC.chOn[i])
         n++;
   }

   // calculate offset between channels
   var d = 1/(n+1);
   
   // set offset
   var o = 0.5-d;
   for (i=0 ; i<16 ; i++) {
      if (OSC.chOn[i]) {
         OSC.wfOffset[i] = o;
         o -= d;
      }
   }
   OSC.calcScaleOffset();
   OSC.redraw();
}

function sldTOffset(value)
{
   OSC.wfTOffset = (value-0.5) * OSC.wfTScale;
   OSC.calcScaleOffset();
   OSC.redraw();
}

function btnConfig()
{
   var e = document.getElementById("config");
   if (e.style.display == "none" || e.style.display == "")
      e.style.display = "block";
   else
      e.style.display = "none";
   resize();
}

function btnAbout()
{
   var e = document.getElementById("about");
   e.style.display = "block";
   e.style.left = document.documentElement.clientWidth/2 - e.offsetWidth/2 + "px";
   e.style.top  = document.documentElement.clientHeight/2 - e.offsetHeight/2 + "px";
   
   this.addEventListener("mousedown",  aboutDrag, true);
   this.addEventListener("mousemove",  aboutDrag, true);
   this.addEventListener("mouseup",    aboutDrag, true);
   this.addEventListener("touchstart", aboutDrag, true);
   this.addEventListener("touchmove",  aboutDrag, true);
}

var Ax, Ay, Dx, Dy;

function aboutDrag(e)
{
   var x = undefined;
   var dlg = document.getElementById("about");

   if (e.type == "mouseup") {
      Ax = 0;
      Ay = 0;
   }

   if (e.target == document.getElementById("aboutTitle") && e.type == "mousedown") {
      Ax = e.clientX;
      Ay = e.clientY;
      Dx = parseInt(dlg.style.left);
      Dy = parseInt(dlg.style.top);
   }
   
   if (e.target == document.getElementById("aboutTitle") && e.type == "touchstart") {
      e.preventDefault();
      Ax = e.targetTouches[0].clientX;
      Ay = e.targetTouches[0].clientY;
      Dx = parseInt(dlg.style.left);
      Dy = parseInt(dlg.style.top);
   }

   if (e.buttons == 1 && e.type == "mousemove" && Ax > 0 && Ay > 0) {
      e.preventDefault();
      x = e.clientX;
      y = e.clientY;
      dlg.style.left = (Dx + (x - Ax)) + "px";
      dlg.style.top  = (Dy + (y - Ay)) + "px";
   }
   

   if (e.type == "touchmove" && Ax > 0 && Ay > 0) {
      x = e.changedTouches[e.changedTouches.length-1].clientX;
      y = e.changedTouches[e.changedTouches.length-1].clientY;
      dlg.style.left = (Dx + (x - Ax)) + "px";
      dlg.style.top  = (Dy + (y - Ay)) + "px";
    }
}


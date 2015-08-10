//
//  wds.js
//  WaveDAQ Server Application JavaScript Code
//
//  Created by Stefan Ritt on 5/8/15.
//

const CONTROLS_WIDTH = 190;

var s; // global scope object

var chnColors = [
   "#FFFF00", "#B0B0FF", "#FFA0A0", "#A0FFA0",
   "#FF9000", "#00AAFF", "#FF0020", "#00C030",
   "#D0A060", "#A0C0D0", "#C04010", "#807060",
   "#F0C000", "#2090A0", "#D040D0", "#90B000",
];

var scaleTable = [
  [ 0.001, "1 mV"   ],
  [ 0.002, "2 mV"   ],
  [ 0.005, "5 mV"   ],
  [ 0.01,  "10 mV"  ],
  [ 0.02,  "20 mV"  ],
  [ 0.05,  "50 mV"  ],
  [ 0.1,   "100 mV" ],
  [ 0.2,   "200 mV" ],
  [ 0.5,   "500 mV" ],
  [ 1,     "1 V"    ],
  [ 2,     "2 V"    ],
  [ 5,     "5 V"    ],
  [ 10,    "10 V"   ],
];

function init()
{
   // prevent mouse events to go up to the browser
   var c = document.getElementById("controls");
   c.addEventListener("click", function(e){e.preventDefault()});
   c.addEventListener("mousemove", function(e){e.preventDefault()});
   
   // initialize custom controls
   controlsInit();
   var sl = document.getElementsByName("ctrlVSlider");
   sl[0].update = sldOffset;
   
   // create Scope object
   s = new Scope();
   for (i=0 ; i<16 ; i++) {
      s.chOn[i] = false;
      s.wf.T[i] = [];
      s.wf.U[i] = [];
      s.wfScale[i] = 0.1;
      s.wfScaleIndex[i] = 6;
      s.wfOffset[i] = 0;
   }
   s.chOn[0] = true;
   var b = document.getElementById("ch0");
   b.style.backgroundColor = chnColors[0];
   
   // size to fit screen
   s.resize();
 
   // add resize event handler
   var z = s.resize.bind(s);
   window.addEventListener("resize", z);

   // preselect first channel
   btnChn(0);
   
   // draw empty scope
   s.redraw();
   
   // schedule first waveform read
   var r = s.readWF.bind(s);
   window.setTimeout(r, 10);
   
   // schedule FPS calculator
   var c = s.calcFPS.bind(s);
   s.t = setTimeout(c, 1000);
}

/*---- Scope Class ----*/

function Scope() { // constructor
   this.nFrames = 0;
   this.nFPS = 0;
   this.previousWidth = 0;
   this.previousHeight = 0;
   this.bottomHeight = 25;
   this.gridPath = null;
   this.chOn = [];
   this.wf = {T:[], U:[]};
   this.wfScale = [];      // volts per division
   this.wfScaleIndex = [];
   this.wfOffset = [];     // -0.5 .. +0.5
   this.wfTOffset = 0;     // seconds
   this.wfTScale = 100E-9; // seconds per division
   this.wfTScaleIndex = [];
   this.wfUO = [];
   this.wfUS = [];
   this.running = true;
   this.currentChn = 0;
}

Scope.prototype.readWF = function()
{
   /* simulate local data
   for (c=0 ; c<16 ; c++) {
      for (i=0 ; i<10 ; i++) {
         this.wf.T[c][i] = i*1E-9;
         this.wf.U[c][i] = Math.sin(this.wf.T[c][i] / 50 / 1E-9) / 4 + (Math.random()-0.5) / 30;
      }
   }

   if (this.running) {
      var r = this.readWF.bind(this);
      window.setTimeout(r, 20);
   }
   */
   for (chn=0,c=0 ; c<16 ; c++)
      if (this.chOn[c])
         chn |= (1<<c);

   req = new XMLHttpRequest();
   req.onreadystatechange = this.receiveWF.bind(this);
   req.open("GET", "wfb?chn=" + chn + "&r=" + Math.random(), true); // avoid cached results
   req.responseType = "arraybuffer";
   req.send();
}

Scope.prototype.receiveWF = function()
{
   if (req.readyState == 4 && req.status == 200) {
      // this.wf = JSON.parse(req.responseText);
      
      var intArray = new Uint32Array(req.response);
      var floatArray = new Float32Array(req.response);
      
      for (var i=0 ; i<intArray.length ; ) {
         if (intArray[i] == 1) { // time array
            i++;
            var c = intArray[i++];
            var n = intArray[i++];
            for (var j=0 ; j<n ; j++)
               this.wf.T[c][j] = floatArray[i++];
         } else if (intArray[i] == 2) { // voltage array
            i++;
            var c = intArray[i++];
            var n = intArray[i++];
            for (var j=0 ; j<n ; j++)
               this.wf.U[c][j] = floatArray[i++];
         } else {
            alert("WDS: Invalid binary data received form server");
            break;
         }
      }
      
      if (this.running) {
         var r = this.readWF.bind(this);
         window.setTimeout(r, 10); // schedule next waveform read
      }
      
      this.redraw();
   }
}

Scope.prototype.calcFPS = function()
{
   this.nFPS = this.nFrames;
   this.nFrames = 0;
   
   var c = this.calcFPS.bind(this);
   this.t = setTimeout(c, 1000);
}

Scope.prototype.resize = function()
{
   var canvas = document.getElementById("scope");
   if (canvas == undefined)
      return;
   
   // resize canvas according to window size
   canvas.width = document.documentElement.clientWidth - CONTROLS_WIDTH;
   canvas.height = document.documentElement.clientHeight;
   
   this.redraw();
}

Scope.prototype.redraw = function()
{
   var d = s.draw.bind(s);
   window.requestAnimationFrame(d);
}

Scope.prototype.draw = function()
{
   var canvas = document.getElementById("scope");
   if (canvas == undefined)
      return;
   
   this.nFrames++;

   var ctx = canvas.getContext("2d");
   
   this.width = canvas.width;
   this.height = canvas.height;
   this.wfWidth = this.width;
   this.wfHeight = this.height - this.bottomHeight;
   this.x1 = 10+4; // leave space for marker
   this.y1 = 4;    // leave space for frame
   this.x2 = this.wfWidth-4;
   this.y2 = this.wfHeight-4;
   this.w = this.x2-this.x1;
   this.h = this.y2-this.y1;
   
   if (this.width != this.previousWidth ||
       this.height != this.previousHeight)
      this.gridPath = null;
   this.previousWidth = this.width;
   this.previousHeight = this.height;
   
   this.drawGrid(ctx);
   this.drawFPS(ctx);
   this.drawWF(ctx);
}

Scope.prototype.drawFPS = function(ctx)
{
   ctx.fillStyle = 'white';
   ctx.strokeStyle = 'white';
   ctx.font = '14px sans-serif';
   ctx.textAlign = "left";
   ctx.textBaseline = "top"
   ctx.fillText(this.nFPS + " Acquisitions / sec.", 10, this.y2+8);
}

Scope.prototype.drawGrid = function(ctx)
{
   ctx.fillStyle = "black";
   ctx.fillRect(0, 0, s.width, s.height);
   
   ctx.strokeStyle = "#808080";
   ctx.lineWidth = 4;
   ctx.strokeRect(this.x1-2, this.y1-2, this.w+4, this.h+4);
   
   if (this.gridPath == null) {
      this.calcScaleOffset();
      
      var p = new Path2D();
      p.moveTo(this.x1, this.y1);
      p.lineTo(this.x1, this.y2);
      p.lineTo(this.x2, this.y2);
      p.lineTo(this.x2, this.y1);
      p.lineTo(this.x1, this.y1);
      
      p.moveTo(this.x1, this.y1+this.h/2);
      p.lineTo(this.x2, this.y1+this.h/2);
      p.moveTo(this.x1+this.w/2, this.y1);
      p.lineTo(this.x1+this.w/2, this.y2);
      
      // horizontal lines
      for (i=1 ; i<50 ; i++) {
         var x = this.x1+i*this.w/50.0;
         
         for (j=1 ; j<10 ; j++)
            p.rect(x, this.y1+j*this.h/10.0, 1, 1);
         
         p.moveTo(x, this.y1);
         if (i % 5 == 0)
            p.lineTo(x, this.y1+10);
         else
            p.lineTo(x, this.y1+6);
         
         var y = this.y1 + this.h/2;
         if (i % 5 == 0) {
            p.moveTo(x, y-5);
            p.lineTo(x, y+5);
         } else {
            p.moveTo(x, y-3);
            p.lineTo(x, y+3);
         }
         
         p.moveTo(x, this.y2);
         if (i % 5 == 0)
            p.lineTo(x, this.y2-10);
         else
            p.lineTo(x, this.y2-6);
      }
      
      // vertical lines
      for (i=1 ; i<50 ; i++) {
         var y = this.y1+i*this.h/50.0;
         
         for (j=1 ; j<10 ; j++)
            p.rect(this.x1+j*this.w/10.0, y, 1, 1);
         
         p.moveTo(this.x1, y);
         if (i % 5 == 0)
            p.lineTo(this.x1+10, y);
         else
            p.lineTo(this.x1+6, y);
         
         var x = this.x1 + this.w/2;
         if (i % 5 == 0) {
            p.moveTo(x-5, y);
            p.lineTo(x+5, y);
         } else {
            p.moveTo(x-3, y);
            p.lineTo(x+3, y);
         }
         
         p.moveTo(this.x2, y);
         if (i % 5 == 0)
            p.lineTo(this.x2-10, y);
         else
            p.lineTo(this.x2-6, y);
      }
      this.gridPath = p;
   }
   
   ctx.lineWidth = 1;
   ctx.strokeStyle = "rgb(146,136,110)";
   ctx.fillStyle = ctx.strokeStyle;
   ctx.stroke(this.gridPath);
}

Scope.prototype.calcScaleOffset = function()
{
   this.wfTO = this.wfTOffset + this.x1;
   this.wfTS = 1/this.wfTScale/10 * this.w;
   
   for (c=0 ; c<16 ; c++) {
      this.wfUO[c] = (this.y1+this.y2)/2 - this.wfOffset[c]*this.h;
      this.wfUS[c] = -this.h/this.wfScale[c]/10;
   }
}

Scope.prototype.drawWF = function(ctx)
{
   for (c=15 ; c>=0 ; c--) {
      if (this.chOn[c]) {
         var y = this.wfUO[c];
         ctx.fillStyle = chnColors[c];
         ctx.strokeStyle = "#E0E0E0";
         ctx.beginPath();
         ctx.arc(8, y, 8, 0, 2*Math.PI);
         ctx.fill();
         ctx.stroke();
         ctx.strokeStyle = "#000000";
         ctx.fillStyle = "#000000";
         ctx.textAlign = "center";
         ctx.textBaseline = "middle";
         ctx.font = '10px sans-serif';
         ctx.fillText(c, 8, y);
      }
   }
   
   ctx.save();
   ctx.rect(this.x1, this.y1, this.w, this.h);
   ctx.clip();

   for (c=0 ; c<16 ; c++) {
      if (this.chOn[c]) {
         ctx.beginPath();
         for (i=0 ; i<1024 ; i++) {
            var x = this.wf.T[c][i] * this.wfTS + this.wfTO;
            var y = this.wf.U[c][i] * this.wfUS[c] + this.wfUO[c];
            if (i == 0)
               ctx.moveTo(x, y);
            else
               ctx.lineTo(x, y);
         }
         ctx.strokeStyle = chnColors[c];
         ctx.stroke();
      }
   }
   
   ctx.restore(); // remove clipping
}

/*---- UI event handler ----*/

function btnStop()
{
   e = document.getElementById("btnStop");
   if (s.running) {
      s.running = false;
      e.innerHTML = "Start";
   } else {
      s.running = true;
      e.innerHTML = "Stop";
      var r = s.readWF.bind(s);
      window.setTimeout(r, 10);
   }
}

function btnSingle()
{
   if (!s.running) {
      var r = s.readWF.bind(s);
      window.setTimeout(r, 10);
   }
}

function btnChn(c)
{
   s.currentChn = c;
   var o = document.getElementById("chOn");
   if (c == -1)
      o.innerHTML = "On";
   else
      o.innerHTML = s.chOn[c] ? "Off" : "On";
   
   var index = c;
   if (c == -1) {
      for (index=0 ; index<16 ; index++)
         if (s.chOn[index])
            break;
      if (index == 16)
         index = 0;
   }

   document.getElementById("UScale").innerHTML = scaleTable[s.wfScaleIndex[index]][1];
   
   for (i=0 ; i<16 ; i++) {
      var cb = document.getElementById("ch"+i);
      if (i == c || c == -1)
         cb.style.border = "3px solid blue";
      else
         cb.style.border = "2px solid #C0C0C0";
   }
   
   s.redraw();
}

function btnOn()
{
   for (i=0 ; i<16 ; i++) {
      if (s.currentChn != -1 && i != s.currentChn)
         continue;
      var cb = document.getElementById("ch"+i);
      var bt = document.getElementById("chOn");
      if (bt.innerHTML == "On") {
         s.chOn[i] = true;
         cb.style.backgroundColor = chnColors[i];
      } else {
         s.chOn[i] = false;
         cb.style.backgroundColor = "#E0E0E0";
      }
   }
   bt.innerHTML = bt.innerHTML == "On" ? "Off" : "On";
   s.redraw();
}

function btnScale(inc)
{
   if (s.currentChn == -1) {
      for (i=0 ; i<16 ; i++)
         if (s.chOn[i])
            break;
      if (i == 16)
         i = 0;
   } else
      i = s.currentChn;
   
   index = s.wfScaleIndex[i] + inc;
   if (index < 0)
      index = 0;
   if (index == scaleTable.length)
      index--;
   
   for (i=0 ; i<16 ; i++) {
      if (s.currentChn != -1 && i != s.currentChn)
         continue;
      
      s.wfScaleIndex[i] = index;
      s.wfScale[i] = scaleTable[s.wfScaleIndex[i]][0];
      document.getElementById("UScale").innerHTML = scaleTable[s.wfScaleIndex[i]][1];
   }
   s.calcScaleOffset();
   s.redraw();
}

function sldOffset(value)
{
   for (i=0 ; i<16 ; i++) {
      if (s.currentChn != -1 && i != s.currentChn)
         continue;
      s.wfOffset[i] = value-0.5;
   }
   s.calcScaleOffset();
   s.redraw();
}

function btnOfsZero()
{
   for (i=0 ; i<16 ; i++) {
      if (s.chOn[i])
         s.wfOffset[i] = 0;
   }
   s.calcScaleOffset();
   s.redraw();
   
   var sl = document.getElementsByName("ctrlVSlider");
   sl[0].position = 0.5;
   ctrlVSliderDraw(sl[0]);
}

function btnOfsDistr()
{
   // count active channels
   var n = 0;
   for (i=0 ; i<16 ; i++) {
      if (s.chOn[i])
         n++;
   }

   // calculate offset between channels
   var d = 1/(n+1);
   
   // set offset
   var o = 0.5-d;
   for (i=0 ; i<16 ; i++) {
      if (s.chOn[i]) {
         s.wfOffset[i] = o;
         o -= d;
      }
   }
   s.calcScaleOffset();
   s.redraw();
}

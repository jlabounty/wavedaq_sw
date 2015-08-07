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
   // set initial colors for buttons
   for (i=0 ; i<16 ; i++) {
      var b = document.getElementById("ch"+i);
      b.style.backgroundColor = chnColors[i];
   }
   
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
      s.chOn[i] = true;
      s.wfT[i] = [];
      s.wfU[i] = [];
      s.wfScale[i] = 0.1;
      s.wfScaleIndex[i] = 6;
      s.wfOffset[i] = -0.4 + i/20;
   }
   
   var d = s.draw.bind(s);
   window.requestAnimationFrame(d);
   
   var r = s.readWF.bind(s);
   window.setTimeout(r, 20);
   
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
   this.wfT = [];
   this.wfU = [];
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
   for (c=0 ; c<16 ; c++) {
      for (i=0 ; i<1024 ; i++) {
         this.wfT[c][i] = i*1E-9;
         this.wfU[c][i] = Math.sin(this.wfT[c][i] / 50 / 1E-9) / 4 + (Math.random()-0.5) / 30;
      }
   }

   if (this.running) {
      var r = this.readWF.bind(this);
      window.setTimeout(r, 20);
   }
}

Scope.prototype.calcFPS = function()
{
   this.nFPS = this.nFrames;
   this.nFrames = 0;
   
   var c = this.calcFPS.bind(this);
   this.t = setTimeout(c, 1000);
}

Scope.prototype.draw = function()
{
   this.nFrames++;
   var canvas = document.getElementById("scope");
   var ctx = canvas.getContext("2d");
   
   // resize canvas according to window size
   canvas.width = window.innerWidth - CONTROLS_WIDTH;
   canvas.height = window.innerHeight;
   
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
   
   var d = this.draw.bind(this);
   window.requestAnimationFrame(d);
}

Scope.prototype.drawFPS = function(ctx)
{
   ctx.fillStyle = 'white';
   ctx.strokeStyle = 'white';
   ctx.font = '14px sans-serif';
   ctx.fillText(this.nFPS + " Acquisitions / sec.", 10, this.y2+20);
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
   ctx.rect(this.x1, this.y1, this.w, this.h);
   ctx.clip();

   for (c=0 ; c<16 ; c++) {
      if (this.chOn[c]) {
         ctx.beginPath();
         for (i=0 ; i<1024 ; i++) {
            var x = this.wfT[c][i] * this.wfTS + this.wfTO;
            var y = this.wfU[c][i] * this.wfUS[c] + this.wfUO[c]
            if (i == 0)
               ctx.moveTo(x, y);
            else
               ctx.lineTo(x, y);
         }
         ctx.strokeStyle = chnColors[c];
         ctx.stroke();
      }
   }
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
      window.setTimeout(r, 20);
   }
}

function btnSingle()
{
   if (!s.running) {
      var r = s.readWF.bind(s);
      window.setTimeout(r, 20);
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
   
   for (i=0 ; i<16 ; i++) {
      var cb = document.getElementById("ch"+i);
      if (i == c || c == -1)
         cb.style.border = "3px solid blue";
      else
         cb.style.border = "2px solid #C0C0C0";
   }
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
}

function btnScale(inc)
{
   for (i=0 ; i<16 ; i++) {
      if (s.currentChn != -1 && i != s.currentChn)
         continue;
      s.wfScaleIndex[i] += inc;
      if (s.wfScaleIndex[i] < 0)
         s.wfScaleIndex[i] = 0;
      if (s.wfScaleIndex[i] == scaleTable.length)
         s.wfScaleIndex[i]--;
      
      s.wfScale[i] = scaleTable[s.wfScaleIndex[i]][0];
      document.getElementById("UScale").innerHTML = scaleTable[s.wfScaleIndex[i]][1];
   }
   s.calcScaleOffset();
}

function sldOffset(value)
{
   for (i=0 ; i<16 ; i++) {
      if (s.currentChn != -1 && i != s.currentChn)
         continue;
      s.wfOffset[i] = value-0.5;
   }
   s.calcScaleOffset();
}

//
//  osc.js
//  Oscilloscope Application JavaScript Code
//
//  Created by Stefan Ritt on 12/8/15.
//

function Oscilloscope(div) { // constructor
   
   // constants
   this.chnColors = ["#FFFF00", "#B0B0FF", "#FFA0A0", "#A0FFA0",
                     "#FF9000", "#00AAFF", "#FF0020", "#00C030",
                     "#D0A060", "#A0C0D0", "#C04010", "#807060",
                     "#F0C000", "#2090A0", "#D040D0", "#90B000"];
   
   this.UScaleTable = [[ 0.001, "1 mV"   ],
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
                       [ 10,    "10 V"   ]];

   this.TScaleTable = [[ 1E-9,   "1 ns"   ],
                       [ 2E-9,   "2 ns"   ],
                       [ 5E-9,   "5 ns"   ],
                       [ 10E-9,  "10 ns"  ],
                       [ 20E-9,  "20 ns"  ],
                       [ 50E-9,  "50 ns"  ],
                       [ 100E-9, "100 ns" ],
                       [ 200E-9, "200 ns" ],
                       [ 500E-9, "500 ns" ],
                       [ 1E-6,   "1 us"   ],
                       [ 2E-6,   "2 us"   ],
                       [ 5E-6,   "5 us"   ],
                       [ 10E-6, "10 us"   ],
                       [ 20E-6, "20 us"   ],
                       [ 50E-6, "50 us"   ],
                       [ 100E-6,"100 us"  ]];

   // create canvas inside div
   this.canvas = document.createElement("canvas");
   div.appendChild(this.canvas);
   
   this.running = true;
   this.currentChn = 0;
   this.idle = true;
   this.demo = false;
   
   this.nFrames = 0;
   this.nFPS = 0;
   this.nEvents = 0;
   this.nEPS = 0;
   
   this.previousWidth = 0;
   this.previousHeight = 0;
   this.bottomHeight = 25;
   
   this.chOn = [];         // on/off switch for channels
   this.wf = {T:[], U:[]}; // waveforms
   this.wd = 0;            // WaveDREAM board
   this.nWd = 0;           // number of boards
   
   this.wfScale = [];      // volts per division
   this.wfScaleIndex = [];
   
   this.wfOffset = [];     // -0.5 .. +0.5
   this.wfTOffset = 0;     // seconds
   
   this.wfTScale = 20E-9;  // seconds per division
   this.wfTScaleIndex = 4;
   
   this.wfUO = [];         // offset and scale optimized
   this.wfUS = [];
   
   // default values
   for (var i=0 ; i<16 ; i++) {
      this.chOn[i] = false;
      this.wf.T[i] = [];
      this.wf.U[i] = [];
      this.wfScale[i] = 0.1;
      this.wfScaleIndex[i] = 6;
      this.wfOffset[i] = 0;
   }
   
   // current board
   this.board = 0;
   
   // schedule FPS calculator
   var f = this.calcFPS.bind(this);
   this.t = setTimeout(f, 1000);
   
   // measurements
   this.lastMeasurement = 0;
   this.sigma = [];
}

Oscilloscope.prototype.sendWaveforms = function(wf)
{
   this.nEvents++;
   this.wf = wf;
}

Oscilloscope.prototype.calcFPS = function()
{
   this.nFPS = this.nFrames;
   this.nFrames = 0;
   
   this.nEPS = this.nEvents;
   this.nEvents = 0;
   
   // call again in one second
   var f = this.calcFPS.bind(this);
   this.t = setTimeout(f, 1000);
}

Oscilloscope.prototype.resize = function(width, height)
{
   this.canvas.width = width;
   this.canvas.height = height > width ? width : height;
   this.redraw();
}

Oscilloscope.prototype.redraw = function()
{
   var f = this.draw.bind(this);
   window.requestAnimationFrame(f);
}

Oscilloscope.prototype.draw = function()
{
   this.nFrames++;
   
   var ctx = this.canvas.getContext("2d");
   
   this.width = this.canvas.width;
   this.height = this.canvas.height;
   this.wfWidth = this.width;
   this.wfHeight = this.height - this.bottomHeight;
   this.x1 = 10+4; // leave space for marker
   this.y1 = 4;    // leave space for frame
   this.x2 = this.wfWidth-4;
   this.y2 = this.wfHeight-4;
   this.w = this.x2-this.x1;
   this.h = this.y2-this.y1;
   this.previousWidth = this.width;
   this.previousHeight = this.height;
   
   this.drawGrid(ctx);
   
   if (this.wf.type == 2) {
      this.drawDT(ctx);
   } else {
      this.drawWF(ctx);
      this.drawFPS(ctx);
      this.drawTemperature(ctx);
      this.drawMeasurements(ctx);
      this.drawStatus(ctx);
   }
}

Oscilloscope.prototype.drawFPS = function(ctx)
{
   ctx.fillStyle = 'white';
   ctx.strokeStyle = 'white';
   ctx.font = '14px sans-serif';
   ctx.textAlign = "left";
   ctx.textBaseline = "top";
   ctx.fillText(this.nEPS + " EPS  " + this.nFPS + " FPS", 10, this.y2+8);
}

Oscilloscope.prototype.drawTemperature = function(ctx)
{
   ctx.fillStyle = 'white';
   ctx.strokeStyle = 'white';
   ctx.font = '14px sans-serif';
   ctx.textAlign = "left";
   ctx.textBaseline = "top";
   
   if (OSC.GL != undefined) {
      var board = document.getElementById("wdSelect").selectedIndex;
      var t = OSC.GL.board[board].temperature;
      
      ctx.fillText("T=" + t.toFixed(1) + " C", 130, this.y2+8);
   }
}

Oscilloscope.prototype.drawMeasurements = function(ctx)
{
   var d = new Date();
   if (d.getTime() > this.lastMeasurement + 500) {
      for (var c=0 ; c<16 ; c++) {
         if (this.chOn[c]) {
            var mean = 0;
            var sigma = 0;
            
            // skip first and last values
            for (i=6 ; i<1022 ; i++)
               mean += this.wf.U[c][i];
            mean /= 1016;
            for (i=6 ; i<1022 ; i++)
               sigma += (this.wf.U[c][i]-mean) * (this.wf.U[c][i]-mean);
            
            sigma = Math.sqrt(sigma/1016);
            sigma = sigma * 1000; // mV
            this.sigma[c] = sigma;
         }
      }
      this.lastMeasurement = d.getTime();
   }
   
   x = 220;
   for (var c=0 ; c<16 ; c++) {
      if (this.chOn[c] && this.sigma[c] != undefined) {
         ctx.fillStyle = this.chnColors[c];
         ctx.strokeStyle = this.chnColors[c];
         ctx.font = '14px sans-serif';
         ctx.textAlign = "left";
         ctx.textBaseline = "top";
         var t = this.sigma[c].toFixed(2) + " mV";
         ctx.fillText(t, x, this.y2+8);
         x += ctx.measureText(t).width + 10;
      }
   }
}

Oscilloscope.prototype.drawStatus = function(ctx)
{
   if (OSC.GL != undefined) {
      var board = document.getElementById("wdSelect").selectedIndex;
      var locked = OSC.GL.board[board].pll_locked;
      
      if (locked == 0) {
         ctx.fillStyle = 'red';
         ctx.strokeStyle = 'red';
         ctx.font = '48px sans-serif';
         ctx.textAlign = "center";
         ctx.textBaseline = "middle";
         ctx.fillText("LMK PLL not locked!", (this.x1+this.x2)/2, (this.y1+this.y2)/2);
      }
   }
}

Oscilloscope.prototype.drawGrid = function(ctx)
{
   ctx.fillStyle = "black";
   ctx.fillRect(0, 0, this.width, this.height);
   
   ctx.strokeStyle = "#808080";
   ctx.lineWidth = 4;
   ctx.strokeRect(this.x1-2, this.y1-2, this.w+4, this.h+4);
   
   this.calcScaleOffset();
   
   ctx.beginPath();
   ctx.moveTo(this.x1, this.y1);
   ctx.lineTo(this.x1, this.y2);
   ctx.lineTo(this.x2, this.y2);
   ctx.lineTo(this.x2, this.y1);
   ctx.lineTo(this.x1, this.y1);
   
   ctx.moveTo(this.x1, this.y1+this.h/2);
   ctx.lineTo(this.x2, this.y1+this.h/2);
   ctx.moveTo(this.x1+this.w/2, this.y1);
   ctx.lineTo(this.x1+this.w/2, this.y2);
   
   // horizontal lines
   for (i=1 ; i<50 ; i++) {
      var x = this.x1+i*this.w/50.0;
      
      for (j=1 ; j<10 ; j++)
         ctx.rect(x, this.y1+j*this.h/10.0, 1, 1);
      
      ctx.moveTo(x, this.y1);
      if (i % 5 == 0)
         ctx.lineTo(x, this.y1+10);
      else
         ctx.lineTo(x, this.y1+6);
      
      var y = this.y1 + this.h/2;
      if (i % 5 == 0) {
         ctx.moveTo(x, y-5);
         ctx.lineTo(x, y+5);
      } else {
         ctx.moveTo(x, y-3);
         ctx.lineTo(x, y+3);
      }
      
      ctx.moveTo(x, this.y2);
      if (i % 5 == 0)
         ctx.lineTo(x, this.y2-10);
      else
         ctx.lineTo(x, this.y2-6);
   }
   
   // vertical lines
   for (i=1 ; i<50 ; i++) {
      var y = this.y1+i*this.h/50.0;
      
      for (j=1 ; j<10 ; j++)
         ctx.rect(this.x1+j*this.w/10.0, y, 1, 1);
      
      ctx.moveTo(this.x1, y);
      if (i % 5 == 0)
         ctx.lineTo(this.x1+10, y);
      else
         ctx.lineTo(this.x1+6, y);
      
      var x = this.x1 + this.w/2;
      if (i % 5 == 0) {
         ctx.moveTo(x-5, y);
         ctx.lineTo(x+5, y);
      } else {
         ctx.moveTo(x-3, y);
         ctx.lineTo(x+3, y);
      }
      
      ctx.moveTo(this.x2, y);
      if (i % 5 == 0)
         ctx.lineTo(this.x2-10, y);
      else
         ctx.lineTo(this.x2-6, y);
   }
   
   ctx.lineWidth = 1;
   ctx.strokeStyle = "rgb(146,136,110)";
   ctx.fillStyle = ctx.strokeStyle;
   ctx.stroke();

   ctx.strokeStyle = "#FFFFFF";
   ctx.fillStyle = "#FFFFFF";
   ctx.textAlign = "right";
   ctx.textBaseline = "middle";
   ctx.font = '24px sans-serif';

   if (this.idle)
      ctx.fillText("Trig ?", this.x2-10, this.x1+10);
   else if (this.demo)
      ctx.fillText("DEMO", this.x2-10, this.x1+10);
   
   /*
   else
      ctx.fillText(this.wd<10 ? "WD00"+this.wd : (this.wd<100 ? "WD0"+this.wd : "WD"+this.wd), this.x2-10, this.x1+10);
    */
}

Oscilloscope.prototype.calcScaleOffset = function()
{
   this.wfTO = this.wfTOffset/(this.wfTScale*10) * this.w + this.x1;
   this.wfTS = 1/(this.wfTScale*10) * this.w;
   
   for (c=0 ; c<16 ; c++) {
      this.wfUO[c] = (this.y1+this.y2)/2 - this.wfOffset[c]*this.h;
      this.wfUS[c] = -this.h/this.wfScale[c]/10;
   }
}

Oscilloscope.prototype.drawWF = function(ctx)
{
   if (OSC.GL == undefined)
      return;
   
   for (c=15 ; c>=0 ; c--) {
      if (this.chOn[c]) {
         var y = this.wfUO[c];
         ctx.fillStyle = this.chnColors[c];
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
   
   var spacing = this.wfTS / (OSC.GL.actual_sampling_frequency * 1E9);
   
   for (c=0 ; c<16 ; c++) {
      if (this.chOn[c]) {
         ctx.beginPath();
         ctx.fillStyle = this.chnColors[c];
         ctx.strokeStyle = this.chnColors[c];
         for (i=0 ; i<1024 ; i++) {
            var x = this.wf.T[c][i] * this.wfTS + this.wfTO;
            var y = this.wf.U[c][i] * this.wfUS[c] + this.wfUO[c];
            if (i == 0)
               ctx.moveTo(x, y);
            else
               ctx.lineTo(x, y);
            if (spacing > 5)
               ctx.fillRect(x-2, y-2, 5, 5);
         }
         ctx.stroke();
      }
   }
   
   ctx.restore(); // remove clipping
}

Oscilloscope.prototype.drawDT = function(ctx)
{
   if (OSC.GL == undefined)
      return;
   
   for (c=15 ; c>=0 ; c--) {
      if (this.chOn[c]) {
         var y = this.wfUO[c];
         ctx.fillStyle = this.chnColors[c];
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
         ctx.fillStyle = this.chnColors[c];
         ctx.strokeStyle = this.chnColors[c];
         for (i=0 ; i<1024 ; i++) {
            var x = this.x1 + i/1024.0 * this.w;
            var y = (10 - this.wf.T[c][i]*1E9) * this.h/10 + this.wfUO[c];
            
            if (this.wf.T[c][i]*1E9 != 0)
              ctx.fillRect(x, y, 1, 1);
         }
         ctx.stroke();
      }
   }
   
   ctx.restore(); // remove clipping
}

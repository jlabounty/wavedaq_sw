//
//  osc.js
//  Oscilloscope Application JavaScript Code
//
//  Created by Stefan Ritt on 12/8/15.
//

// extend 2d canvas object
CanvasRenderingContext2D.prototype.drawLine = function (x1, y1, x2, y2) {
   this.beginPath();
   this.moveTo(x1, y1);
   this.lineTo(x2, y2);
   this.stroke();
};

var ChannelColors = [
   "#FFFF00", "#B0B0FF", "#FFA0A0", "#A0FFA0",
   "#FF9000", "#00AAFF", "#FF00A0", "#00C030",
   "#D0A060", "#A0C0D0", "#C04010", "#807060",
   "#F0C000", "#2090A0", "#D040D0", "#90B000",
   "#FFFFFF", "#FFFFFF", "#FF0000", "#FF0000" ];

function Oscilloscope(div) { // constructor

   // constants
   this.chnColors = ChannelColors;

   this.UScaleTable =
      [[0.001, "1 mV"],
      [0.002, "2 mV"],
      [0.005, "5 mV"],
      [0.01, "10 mV"],
      [0.02, "20 mV"],
      [0.05, "50 mV"],
      [0.1, "100 mV"],
      [0.2, "200 mV"],
      [0.5, "500 mV"],
      [1, "1 V"],
      [2, "2 V"],
      [5, "5 V"],
      [10, "10 V"]];

   this.TScaleTable =
      [[1E-9, "1 ns"],
      [2E-9, "2 ns"],
      [5E-9, "5 ns"],
      [10E-9, "10 ns"],
      [20E-9, "20 ns"],
      [50E-9, "50 ns"],
      [100E-9, "100 ns"],
      [200E-9, "200 ns"],
      [500E-9, "500 ns"],
      [1E-6, "1 us"],
      [2E-6, "2 us"],
      [5E-6, "5 us"],
      [10E-6, "10 us"],
      [20E-6, "20 us"],
      [50E-6, "50 us"],
      [100E-6, "100 us"]];

   // create canvas inside div
   this.canvas = document.createElement("canvas");
   div.appendChild(this.canvas);

   this.applyAll = false;
   this.running = true;
   this.currentChn = 0;
   this.idle = true;
   this.demoMode = demoMode;
   this.connected = false;

   this.logFlag = false;
   this.logfile = "";
   this.nLogged = 0;
   this.nRequested = 0;
   
   this.vCalibrated = true;
   this.tCalibrated = true;

   this.nFrames = 0;
   this.nFPS = 0;
   this.nEvents = 0;
   this.nEPS = 0;

   this.chOn = [];         // on/off switch for channels
   this.chOnSelected = []  // channel button selected
   this.wf = {T: [], U: []}; // waveforms
   this.wd = 0;            // WaveDREAM board
   this.nWd = 0;           // number of boards

   this.wfScale = [];      // volts per division
   this.wfScaleIndex = [];

   this.wfOffset = [];     // -0.5 .. +0.5
   this.wfTOffset = 0;     // seconds

   this.wfTScaleIndex = 4;
   this.wfTScale = this.TScaleTable[this.wfTScaleIndex][0];

   this.wfUO = [];         // offset and scale optimized
   this.wfUS = [];

   this.i1 = 0;
   this.i2 = 0;

   this.timeCursor =  { input: undefined, drag: false, time: 0, x: 0 };
   this.voltCursor =  { input: undefined, drag: false, volt: 0, y: 0 };

   // display object
   this.disp = {
      scaler: false,
      histo: false,
      histoDivider: 0.5,
      persistency: 0,
      persDeltaInt: 0
   };
   this.newImage = true;

   // default values
   for (var i = 0; i < 20; i++) {
      this.chOn[i] = false;
      this.chOnSelected[i] = false;
      this.wf.T[i] = [];
      this.wf.U[i] = [];
      this.wfScale[i] = 0.1;
      this.wfScaleIndex[i] = 6;
      this.wfOffset[i] = 0;
   }

   // current board
   this.curBoard = 0;

   // schedule FPS calculator
   var f = this.calcFPS.bind(this);
   this.t = setTimeout(f, 1000);

   // used for trigger lines
   this.lastTriggerLevelChange = 0;

   // used to suppress updates after a parameter change
   this.lastParamSet = new Date() / 1000;

   // histogram settings
   this.histo = {
      autoAxis: true,
      axisMin: 0,
      axisMax: 0,
      xMax: 0,
      dragLeftHandle: false,
      dragRightHande: false,
      dragX: 0,
      button: []
   };

   this.histo.button[0] = document.getElementById("measClear");
   this.histo.button[1] = document.getElementById("measZoomIn");
   this.histo.button[2] = document.getElementById("measZoomOut");
   this.histo.button[3] = document.getElementById("measZoomFit");

   // mouse event handlers
   window.addEventListener("mousedown", this.mouseEvent.bind(this), true);
   window.addEventListener("mousemove", this.mouseEvent.bind(this), true);
   window.addEventListener("mouseup", this.mouseEvent.bind(this), true);
   window.addEventListener("touchstart", this.mouseEvent.bind(this), true);
   window.addEventListener("touchmove", this.mouseEvent.bind(this), true);

   // timers
   this.timer = {};
}

Oscilloscope.prototype.sendWaveforms = function (wf) {
   this.nEvents++;
   this.wf = wf;

   // execute measurements
   for (var i = 0; i < this.measList.childNodes.length; i++)
      if (this.measList.childNodes[i].measurement)
         this.measList.childNodes[i].measurement.measure(wf.T, wf.U, this.i1, this.i2, true, undefined);

};

Oscilloscope.prototype.calcFPS = function () {
   this.nFPS = this.nFrames;
   this.nFrames = 0;

   this.nEPS = this.nEvents;
   this.nEvents = 0;

   // call again in one second
   var f = this.calcFPS.bind(this);
   this.t = setTimeout(f, 1000);
};

Oscilloscope.prototype.resize = function (width, height) {
   this.canvas.width = width;
   this.canvas.height = height > width ? width : height;
   this.resizeCanvas();
   this.redraw();
};

Oscilloscope.prototype.clearPersistency = function () {
   this.newImage = true;
};

Oscilloscope.prototype.redraw = function () {
   var f = this.draw.bind(this);
   window.requestAnimationFrame(f);
};

Oscilloscope.prototype.mouseEvent = function (e) {

   // fix buttons for IE
   if (!e.which && e.button) {
      if ((e.button & 1) > 0) e.which = 1;      // Left
      else if ((e.button & 4) > 0) e.which = 2; // Middle
      else if ((e.button & 2) > 0) e.which = 3; // Right
   }

   if (this.disp.histo && e.target == this.canvas) {

      // division bar
      if (Math.abs(e.clientY - this.hiy1) < 10 &&
         e.clientX > this.x1 && e.clientX < this.x2 &&
         e.type == "mousedown")
         this.dragDivider = true;

      if (e.type == "mousemove" && this.dragDivider) {
         this.disp.histoDivider = 1 - e.clientY / this.height;
         if (this.disp.histoDivider < 0.1)
            this.disp.histoDivider = 0.1;
         if (this.disp.histoDivider > 0.9)
            this.disp.histoDivider = 0.9;
         OSC.resizeCanvas();
      }

      if (e.type == "mouseup")
         this.dragDivider = false;

      // left drag handle
      if (e.clientX > this.x1 && e.clientX < this.x1 + 15 &&
         e.clientY > this.hiy1 + this.hiHeight / 2 - 15 &&
         e.clientY < this.hiy1 + this.hiHeight / 2 + 15 &&
         e.type == "mousedown") {
         this.histo.dragLeftHandle = true;
      }

      if (e.type == "mousemove" && this.histo.dragLeftHandle || this.histo.dragRightHandle) {
         this.histo.dragX = e.clientX;
         if (this.histo.dragX < this.x1)
            this.histo.dragX = this.x1;
         if (this.histo.dragX > this.x2)
            this.histo.dragX = this.x2;
      }

      if (e.type == "mouseup") {
         if (this.histo.dragLeftHandle) {
            this.histo.autoAxis = false;
            this.histo.axisMin = this.histo.axisMin + (this.histo.dragX - this.x1) / (this.x2 - this.x1) * (this.histo.axisMax - this.histo.axisMin);
            this.histo.dragLeftHandle = false;
         }
         if (this.histo.dragRightHandle) {
            this.histo.autoAxis = false;
            this.histo.axisMax = this.histo.axisMin + (this.histo.dragX - this.x1) / (this.x2 - this.x1) * (this.histo.axisMax - this.histo.axisMin);
            this.histo.dragRightHandle = false;
         }
      }

      // right drag handle
      if (e.clientX < this.x2 && e.clientX > this.x2 - 15 &&
         e.clientY > this.hiy1 + this.hiHeight / 2 - 15 &&
         e.clientY < this.hiy1 + this.hiHeight / 2 + 15 &&
         e.type == "mousedown") {
         this.histo.dragRightHandle = true;
      }
   }

   if (this.timeCursor.input != undefined && e.target == this.canvas) {

      if (e.clientX > this.x1 && e.clientX < this.x2 &&
          e.clientY > this.y1 && e.clientY < this.y2 &&
          e.type == "mousedown")
         this.timeCursor.drag = true;

      if (e.type == "mouseup") {
         this.timeCursor.drag = false;
      }

      if (e.type == "mousemove" && this.timeCursor.drag) {
         this.timeCursor.dragX = e.clientX;
         var t = (this.XToTime(e.clientX) / 1E-9).toFixed(1);
         this.timeCursor.x = e.clientX;
         this.timeCursor.time = t;
         this.timeCursor.input.value = t;
      }
   }
};

Oscilloscope.prototype.setTimeCursor = function(i) {
   this.timeCursor.input = i;
}

Oscilloscope.prototype.resizeCanvas = function () {
   this.width = this.canvas.width;
   this.height = this.canvas.height;

   this.wfWidth = this.width;
   this.hiWidth = this.width;
   if (this.disp.histo) {
      this.wfHeight = this.height * (1 - this.disp.histoDivider);
      this.hiHeight = this.height * this.disp.histoDivider;
   } else {
      this.wfHeight = this.height;
   }

   this.x1 = 11; // leave space for marker
   if (this.disp.scaler) // leave space for scaler
      this.x1 += 125;

   this.y1 = 2;    // leave space for frame
   this.x2 = this.wfWidth - 2;
   this.y2 = this.wfHeight - 2;
   this.w = this.x2 - this.x1;
   this.h = this.y2 - this.y1;

   this.hiy1 = this.wfHeight;
   this.hiy2 = this.height - 28;
   this.hiWidth = this.x2 - this.x1;
   this.hiHeight = this.hiy2 - this.hiy1;

   this.calcScaleOffset();
   this.clearPersistency();
};

Oscilloscope.prototype.draw = function () {
   
   // wait until globals are loaded
   if (!OSC.connected)
      return;
   
   this.nFrames++;

   var ctx = this.canvas.getContext("2d");

   // create new waveform image if canvas has been resized
   if (this.newImage) {
      this.newImage = false;
      this.wfImg = ctx.createImageData(this.x2 - this.x1, this.y2 - this.y1);
      for (var i = 0; i < this.wfImg.data.length; i += 4) {
         this.wfImg.data[i] = 0;
         this.wfImg.data[i + 1] = 0;
         this.wfImg.data[i + 2] = 0;
         this.wfImg.data[i + 3] = 255;
      }
      this.wfImgOccupied = new Uint8ClampedArray(this.wfImg.data.length / 4);
   }

   this.blackCanvas(ctx);
   if (this.wf.type == 2) {
      this.drawGrid(ctx);
      this.drawDT(ctx);
   } else {
      this.drawGrid(ctx);
      this.drawWF(ctx);
      this.drawMarker(ctx);
      this.drawMeasurements(ctx);
      this.drawCursors(ctx);
      this.printFPS(ctx);
      this.printTemperature(ctx);
      this.printLogged(ctx);
      this.printScalers(ctx);
      this.printMeasurements(ctx);
      this.printStatus(ctx);

      if (this.disp.histo)
         this.drawHisto(ctx);
      else
         for (i = 0; i < OSC.histo.button.length; i++)
            OSC.histo.button[i].style.display = "none";
   }
};

Oscilloscope.prototype.drawChnButtons = function () {
   // set blue border of active channel buttons
   for (var i = 0; i < 20; i++) {
      var cb = document.getElementById("ch" + i);
      if (cb == undefined)
         continue;
      if (this.chOnSelected[i])
         cb.style.border = "3px solid blue";
      else
         cb.style.border = "2px solid #C0C0C0";
      if (this.chOn[i])
         cb.style.backgroundColor = this.chnColors[i];
      else {
         if (i < 16)
            cb.style.backgroundColor = "#E0E0E0";
         else
            cb.style.backgroundColor = "#A0A0A0";
      }
   }
}

Oscilloscope.prototype.printFPS = function () {
   document.getElementById("EPS").innerHTML = this.nEPS;
   document.getElementById("FPS").innerHTML = this.nFPS;
};

Oscilloscope.prototype.printTemperature = function (ctx) {
   ctx.fillStyle = 'white';
   ctx.strokeStyle = 'white';
   ctx.font = '14px sans-serif';
   ctx.textAlign = "left";
   ctx.textBaseline = "top";

   if (OSC.wdb != undefined) {
      var t = OSC.wdb[OSC.curBoard].temperature;
      ctx.fillText("T = " + t.toFixed(1) + " C", this.x1 + 12, this.y2 - 24);
   }
};

Oscilloscope.prototype.printLogged = function (ctx) {
   if (OSC.logFlag) {
      ctx.fillStyle = 'white';
      ctx.strokeStyle = 'white';
      ctx.font = '14px sans-serif';
      ctx.textAlign = "left";
      ctx.textBaseline = "top";

      var t = OSC.nLogged + "/" + OSC.nRequested + " events logged to " + OSC.logfile;
      ctx.fillText(t, this.x2 - ctx.measureText(t).width - 10, this.y2 - 24);
   }
};

Oscilloscope.prototype.printMeasurements = function (ctx) {
   var n = 0;
   for (var i = 0; i < this.measList.childNodes.length; i++)
      if (this.measList.childNodes[i].nodeName == "DIV")
         n++;

   if (n > 1) {
      ctx.fillStyle = 'white';
      ctx.strokeStyle = 'white';
      ctx.font = '14px monospace';
      ctx.textAlign = "left";
      ctx.textBaseline = "top";
      ctx.fillText("    Value        Min       Max      Mean       Std         N", OSC.x1 + 250, OSC.y1 + 10);

      n = 0;
      for (i = 0; i < this.measList.childNodes.length; i++)
         if (this.measList.childNodes[i].measurement)
            this.measList.childNodes[i].measurement.print(n++, ctx);
   }
};

Oscilloscope.prototype.drawMeasurements = function (ctx) {
   for (var i = 0; i < this.measList.childNodes.length; i++)
      if (this.measList.childNodes[i].measurement)
         this.measList.childNodes[i].measurement.draw(ctx, this.wf.T, this.wf.U, this.i1, this.i2);
};

Oscilloscope.prototype.drawCursors = function (ctx) {
   if (this.timeCursor.input) {
      ctx.strokeStyle = 'white';
      ctx.lineWidth = 2;
      ctx.drawLine(this.timeCursor.x, this.y1, this.timeCursor.x, this.y2);
      ctx.lineWidth = 1;
   }
};

Oscilloscope.prototype.printStatus = function (ctx) {
   if (OSC.wdb != undefined) {
      if (OSC.wdb[OSC.curBoard].pllLck != 0x1FF) {
         ctx.fillStyle = 'red';
         ctx.strokeStyle = 'red';
         ctx.font = '48px sans-serif';
         ctx.textAlign = "center";
         ctx.textBaseline = "middle";
         ctx.fillText("PLL not locked! (m=0x"+OSC.wdb[OSC.curBoard].pllLck.toString(16)+")", (this.x1 + this.x2) / 2, (this.y1 + this.y2) / 2);
      }
      
      if (!OSC.vCalibrated) {
         ctx.fillStyle = 'red';
         ctx.strokeStyle = 'red';
         ctx.font = '18px sans-serif';
         ctx.textAlign = "left";
         ctx.textBaseline = "top";
         var t = "Voltage calibrated";
         ctx.fillText(t, this.x1 + 12, this.y2 - 55);
         ctx.drawLine(this.x1+10, this.y2-57, this.x1+14+ctx.measureText(t).width, this.y2-46+14);
         ctx.drawLine(this.x1+10, this.y2-46+14, this.x1+14+ctx.measureText(t).width, this.y2-57);
      }
      
      if (!OSC.tCalibrated) {
         ctx.fillStyle = 'red';
         ctx.strokeStyle = 'red';
         ctx.font = '18px sans-serif';
         ctx.textAlign = "left";
         ctx.textBaseline = "top";
         var t = "Time calibrated";
         ctx.fillText(t, this.x1 + 12, this.y2 - 85);
         ctx.drawLine(this.x1+10, this.y2-87, this.x1+14+ctx.measureText(t).width, this.y2-76+14);
         ctx.drawLine(this.x1+10, this.y2-76+14, this.x1+14+ctx.measureText(t).width, this.y2-87);
      }

   }
};

Oscilloscope.prototype.printScalers = function (ctx) {
   if (OSC.wdb != undefined && OSC.disp.scaler && OSC.wdb[OSC.curBoard].scaler) {
      var scaler = OSC.wdb[OSC.curBoard].scaler;

      for (var c = 0; c < 18; c++) {
         ctx.fillStyle = this.chnColors[c];
         ctx.strokeStyle = this.chnColors[c];
         ctx.font = '14px sans-serif';
         ctx.textBaseline = "top";

         ctx.textAlign = "right";
         if (c == 16)
            ctx.fillText("T", 20, 4 + c * 20);
         else if (c == 17)
            ctx.fillText("E", 20, 4 + c * 20);
         else
            ctx.fillText(c.toString(), 20, 4 + c * 20);

         var s = scaler[c];
         if (s < 1E3) {
            ctx.fillText(s, 85, 4 + c * 20);
            ctx.textAlign = "left";
            ctx.fillText("Hz", 90, 4 + c * 20);
         } else if (s < 1E6) {
            s /= 1E3;
            ctx.fillText(s.toFixed(3), 85, 4 + c * 20);
            ctx.textAlign = "left";
            ctx.fillText("kHz", 90, 4 + c * 20);
         } else {
            s /= 1E6;
            ctx.fillText(s.toFixed(3), 85, 4 + c * 20);
            ctx.textAlign = "left";
            ctx.fillText("MHz", 90, 4 + c * 20);
         }
      }
   }
};

Oscilloscope.prototype.blackCanvas = function (ctx) {
   ctx.fillStyle = "black";
   ctx.fillRect(0, 0, this.width, this.height);
};

Oscilloscope.prototype.drawGrid = function (ctx) {
   ctx.strokeStyle = "#808080";
   ctx.lineWidth = 2;
   ctx.strokeRect(this.x1 - 1, this.y1 - 1, this.w + 2, this.h + 2);

   ctx.beginPath();
   ctx.moveTo(this.x1, this.y1);
   ctx.lineTo(this.x1, this.y2);
   ctx.lineTo(this.x2, this.y2);
   ctx.lineTo(this.x2, this.y1);
   ctx.lineTo(this.x1, this.y1);

   ctx.moveTo(this.x1, this.y1 + this.h / 2);
   ctx.lineTo(this.x2, this.y1 + this.h / 2);
   ctx.moveTo(this.x1 + this.w / 2, this.y1);
   ctx.lineTo(this.x1 + this.w / 2, this.y2);

   // horizontal lines
   for (var i = 1; i < 50; i++) {
      var x = this.x1 + i * this.w / 50.0;

      for (var j = 1; j < 10; j++)
         ctx.rect(x, this.y1 + j * this.h / 10.0, 1, 1);

      ctx.moveTo(x, this.y1);
      if (i % 5 == 0)
         ctx.lineTo(x, this.y1 + 10);
      else
         ctx.lineTo(x, this.y1 + 6);

      var y = this.y1 + this.h / 2;
      if (i % 5 == 0) {
         ctx.moveTo(x, y - 5);
         ctx.lineTo(x, y + 5);
      } else {
         ctx.moveTo(x, y - 3);
         ctx.lineTo(x, y + 3);
      }

      ctx.moveTo(x, this.y2);
      if (i % 5 == 0)
         ctx.lineTo(x, this.y2 - 10);
      else
         ctx.lineTo(x, this.y2 - 6);
   }

   // vertical lines
   for (i = 1; i < 50; i++) {
      y = this.y1 + i * this.h / 50.0;

      for (j = 1; j < 10; j++)
         ctx.rect(this.x1 + j * this.w / 10.0, y, 1, 1);

      ctx.moveTo(this.x1, y);
      if (i % 5 == 0)
         ctx.lineTo(this.x1 + 10, y);
      else
         ctx.lineTo(this.x1 + 6, y);

      x = this.x1 + this.w / 2;
      if (i % 5 == 0) {
         ctx.moveTo(x - 5, y);
         ctx.lineTo(x + 5, y);
      } else {
         ctx.moveTo(x - 3, y);
         ctx.lineTo(x + 3, y);
      }

      ctx.moveTo(this.x2, y);
      if (i % 5 == 0)
         ctx.lineTo(this.x2 - 10, y);
      else
         ctx.lineTo(this.x2 - 6, y);
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

   if (this.gl.demoMode || this.demoMode)
      ctx.fillText("DEMO", this.x2 - 10, this.y1 + 20);
   else if (this.idle)
      ctx.fillText("Trig ?", this.x2 - 10, this.y1 + 20);

   ctx.beginPath(); // ?? needed to avoid problems later...
   ctx.stroke();
};

Oscilloscope.prototype.calcScaleOffset = function () {
   this.wfTO = this.wfTOffset / (this.wfTScale * 10) * this.w + this.x1;
   this.wfTS = 1 / (this.wfTScale * 10) * this.w;

   for (var c = 0; c < 20; c++) {
      this.wfUO[c] = (this.y1 + this.y2) / 2 - this.wfOffset[c] * this.h;
      this.wfUS[c] = -this.h / this.wfScale[c] / 10;
   }
};

Oscilloscope.prototype.timeToX = function (t) {
   return t * this.wfTS + this.wfTO;
};

Oscilloscope.prototype.XToTime = function (x) {
   return (x - this.wfTO) / this.wfTS;
};

Oscilloscope.prototype.voltToY = function (v, c) {
   return v * this.wfUS[c] + this.wfUO[c];
};

Oscilloscope.prototype.drawWF = function (ctx) {
   if (!OSC.connected)
      return;

   // Waveforms
   if (this.disp.persistency == 0) {
      ctx.save();
      ctx.rect(this.x1, this.y1, this.w, this.h);
      ctx.clip();
      var spacing = this.wfTS / (OSC.wdb[OSC.curBoard].drsSampleFreq * 1E6);
      for (var c = 0; c < 20; c++) {
         if (this.chOn[c]) {
            ctx.beginPath();
            ctx.fillStyle = this.chnColors[c];
            ctx.strokeStyle = this.chnColors[c];
            for (var i = 0; i < 1024; i++) {
               var x = this.wf.T[c][i] * this.wfTS + this.wfTO;
               var y = this.wf.U[c][i] * this.wfUS[c] + this.wfUO[c];
               if (x > -100 && x < this.w + 100) {
                  if (i == 0)
                     ctx.moveTo(x, y);
                  else
                     ctx.lineTo(x, y);
                  if (spacing > 5)
                     ctx.fillRect(x - 2, y - 2, 5, 5);
               }
            }
            ctx.stroke();
         }
      }
      ctx.restore(); // remove clipping

   } else {

      // reduce alpha
      if (!isNaN(this.disp.persistency)) {
         var delta;
         if (OSC.nEPS == 0)
            delta = 200 / this.disp.persistency;
         else
            delta = 200 / this.disp.persistency / OSC.nEPS;
         this.disp.persDeltaInt += delta;
         if (this.disp.persDeltaInt >= 1) {
            delta = Math.floor(this.disp.persDeltaInt);
            this.disp.persDeltaInt -= delta;

            for (i = 0; i < this.wfImgOccupied.length; i++) {
               if (this.wfImgOccupied[i]) {
                  var i1 = i * 4;
                  if (this.wfImg.data[i1] > 0) {
                     if (this.wfImg.data[i1] >= delta)
                        this.wfImg.data[i1] -= delta;
                     else
                        this.wfImg.data[i1] = 0;
                  }
                  if (this.wfImg.data[i1 + 1] > 0) {
                     if (this.wfImg.data[i1 + 1] >= delta)
                        this.wfImg.data[i1 + 1] -= delta;
                     else
                        this.wfImg.data[i1 + 1] = 0;
                  }
                  if (this.wfImg.data[i1 + 2] > 0) {
                     if (this.wfImg.data[i1 + 2] >= delta)
                        this.wfImg.data[i1 + 2] -= delta;
                     else
                        this.wfImg.data[i1 + 2] = 0;
                  }
                  if (this.wfImg.data[i1] == 0 &&
                     this.wfImg.data[i1 + 1] == 0 &&
                     this.wfImg.data[i1 + 2] == 0)
                     this.wfImgOccupied[i] = 0;
               }
            }
         }
      }


      for (c = 0; c < 20; c++) {
         if (this.chOn[c]) {
            var col = parseInt(this.chnColors[c].substr(1, 6), 16);
            var r = (col >> 16) & 0xFF;
            var g = (col >> 8) & 0xFF;
            var b = col & 0xFF;
            var x1 = 0, y1 = 0, x2 = 0, y2 = 0;

            for (i = 0; i < 1024; i++) {
               x1 = Math.floor(this.wf.T[c][i] * this.wfTS + this.wfTO);
               y1 = Math.floor(this.wf.U[c][i] * this.wfUS[c] + this.wfUO[c]);

               if (i == 0) {
                  x = x1;
                  y = y1;
                  if (x >= this.x1 && x < this.x2 &&
                     y >= this.y1 && y < this.y2) {
                     x -= this.x1;
                     y -= this.y1;
                     var i2 = y * this.wfImg.width + x;
                     i1 = i2 * 4;
                     this.wfImg.data[i1] = r;
                     this.wfImg.data[i1 + 1] = g;
                     this.wfImg.data[i1 + 2] = b;
                     this.wfImgOccupied[i2] = 1;
                  }
               } else {
                  var dx = x1 - x2;
                  var dy = y1 - y2;
                  var n = Math.max(Math.abs(dx), Math.abs(dy));
                  for (var j = 0; j < n; j++) {
                     x = Math.floor(x2 + j * dx / n);
                     y = Math.floor(y2 + j * dy / n);
                     if (x >= this.x1 && x < this.x2 &&
                        y >= this.y1 && y < this.y2) {
                        x -= this.x1;
                        y -= this.y1;
                        i2 = y * this.wfImg.width + x;
                        i1 = i2 * 4;
                        this.wfImg.data[i1] = r;
                        this.wfImg.data[i1 + 1] = g;
                        this.wfImg.data[i1 + 2] = b;
                        this.wfImgOccupied[i2] = 1;
                     }
                  }
               }
               x2 = x1;
               y2 = y1;
            }
         }
      }
      ctx.putImageData(this.wfImg, this.x1, this.y1);
   }
};

Oscilloscope.prototype.drawMarker = function (ctx) {
   // Circular markers on left side
   for (var c = 18; c >= 0; c--) {
      if (this.chOn[c]) {
         var y = this.wfUO[c];
         ctx.fillStyle = this.chnColors[c];
         ctx.strokeStyle = this.chnColors[c];
         ctx.beginPath();
         ctx.arc(this.x1 - 2, y, 8, 0, 2 * Math.PI);
         ctx.fill();
         ctx.stroke();
         ctx.strokeStyle = "#000000";
         ctx.fillStyle = "#000000";
         ctx.textAlign = "center";
         ctx.textBaseline = "middle";
         ctx.font = '10px sans-serif';
         if (c == 18)
            ctx.fillText("\u03A3", this.x1 - 2, y);
         else
            ctx.fillText(c.toString(), this.x1 - 2, y);
      }
   }

   // Trigger levels
   for (c = 15; c >= 0; c--) {
      if (this.chOn[c]) {
         ctx.fillStyle = this.chnColors[c];
         ctx.strokeStyle = this.chnColors[c];

         y = (OSC.wdb[OSC.curBoard].dacTriggerLevel[c]) * this.wfUS[c] + this.wfUO[c];

         ctx.beginPath();
         ctx.moveTo(this.x2 - 2, y - 5);
         ctx.lineTo(this.x2 - 2, y + 5);
         ctx.lineTo(this.x2 - 10, y);
         ctx.lineTo(this.x2 - 2, y - 5);
         ctx.closePath();
         ctx.fill();
         ctx.stroke();

         var d = new Date();
         if (d.getTime() < this.lastTriggerLevelChange + 1000) {
            ctx.beginPath();
            ctx.moveTo(this.x2 - 10, y);
            ctx.lineTo(this.x1, y);
            ctx.stroke();
         }
      }
   }

   // Trigger marker
   ctx.fillStyle = 'white';
   ctx.strokeStyle = 'white';

   var t = 1024 / OSC.wdb[OSC.curBoard].drsSampleFreq * 1E-6;
   t -= (30 + OSC.wdb[OSC.curBoard].triggerDelay) * 1E-9;
   var xt = this.timeToX(t);

   ctx.beginPath();
   ctx.moveTo(xt - 4, this.y1 + 2);
   ctx.lineTo(xt - 4, this.y1 + 9);
   ctx.lineTo(xt,     this.y1 + 13);
   ctx.lineTo(xt + 4, this.y1 + 9);
   ctx.lineTo(xt + 4, this.y1 + 2);
   ctx.lineTo(xt - 4, this.y1 + 2)
   ctx.closePath();
   ctx.fill();
   ctx.stroke();

   ctx.beginPath();
   ctx.fillStyle = 'black';
   ctx.strokeStyle = 'black';
   ctx.moveTo(xt - 3, this.y1 + 4);
   ctx.lineTo(xt + 3, this.y1 + 4);
   ctx.stroke();

   ctx.beginPath();
   ctx.moveTo(xt, this.y1 + 4);
   ctx.lineTo(xt, this.y1 + 12);
   ctx.stroke();
};

Oscilloscope.prototype.drawDT = function (ctx) {
   if (!OSC.connected)
      return;

   for (var c = 15; c >= 0; c--) {
      if (this.chOn[c]) {
         var y = this.wfUO[c];
         ctx.fillStyle = this.chnColors[c];
         ctx.strokeStyle = "#E0E0E0";
         ctx.beginPath();
         ctx.arc(8, y, 8, 0, 2 * Math.PI);
         ctx.fill();
         ctx.stroke();
         ctx.strokeStyle = "#000000";
         ctx.fillStyle = "#000000";
         ctx.textAlign = "center";
         ctx.textBaseline = "middle";
         ctx.font = '10px sans-serif';
         ctx.fillText(c.toString(), 8, y);
      }
   }

   ctx.save();
   ctx.rect(this.x1, this.y1, this.w, this.h);
   ctx.clip();

   for (c = 0; c < 18; c++) {
      if (this.chOn[c]) {
         ctx.beginPath();
         ctx.fillStyle = this.chnColors[c];
         ctx.strokeStyle = this.chnColors[c];
         for (var i = 0; i < 1024; i++) {
            var x = this.x1 + i / 1024.0 * this.w;
            y = (10 - this.wf.T[c][i] * 1E9) * this.h / 10 + this.wfUO[c];

            if (this.wf.T[c][i] * 1E9 != 0)
               ctx.fillRect(x, y, 3, 3);
         }
         ctx.stroke();
      }
   }

   ctx.restore(); // remove clipping
};

Oscilloscope.prototype.drawHisto = function (ctx) {
   if (!OSC.connected)
      return;

   // draw overall frame
   ctx.fillStyle = "black";
   ctx.fillRect(this.x1, this.wfHeight, this.hiWidth, this.hiHeight);

   ctx.strokeStyle = "#808080";
   ctx.lineWidth = 1;
   ctx.strokeRect(this.x1 - 1, this.hiy1 - 1, this.hiWidth + 2, this.hiHeight + 2);

   if (this.histo.autoAxis) {
      this.histo.axisMin = undefined;
      this.histo.axisMax = undefined;
      for (var i = 0; i < this.measList.childNodes.length; i++) {
         var m = this.measList.childNodes[i].measurement;
         if (m) {
            if (!this.histo.axisMin || m.min < this.histo.axisMin)
               this.histo.axisMin = m.min;
            if (!this.histo.axisMax || m.max > this.histo.axisMax)
               this.histo.axisMax = m.max;
         }
      }
   }

   if (this.histo.axisMin == this.histo.axisMax)
      return;

   var nMeas = 0;
   var histo = [];
   var uflowBin = 0;
   var oflowBin = 0;
   this.histo.xMax = 0;
   for (var idx = 0; idx < this.measList.childNodes.length; idx++) {
      m = this.measList.childNodes[idx].measurement;
      if (m) {
         var histoSum = 0;
         var histoSum2 = 0;
         var histoN = 0;

         nMeas++;
         var nBins = Math.floor(1.5 * Math.sqrt(m.nMeasured));
         if (nBins > 1000)
            nBins = 1000;
         for (i = 0; i < nBins; i++)
            histo[i] = 0;
         var oflow = 0;
         var uflow = 0;

         // fill data into histo
         for (i = 0; i < m.nMeasured; i++) {
            var bin = Math.floor((m.statArray[i] - this.histo.axisMin) /
               (this.histo.axisMax - this.histo.axisMin) * (nBins - 1));
            if (bin >= nBins)
               oflow++;
            else if (bin < 0)
               uflow++;
            else {
               histo[bin]++;
               histoSum += m.statArray[i];
               histoSum2 += m.statArray[i] * m.statArray[i];
               histoN++;
            }
         }

         var hmax = histo[0];
         for (i = 0; i < nBins; i++)
            if (histo[i] > hmax) {
               hmax = histo[i];
               this.histo.xMax = i/nBins * (this.histo.axisMax - this.histo.axisMin) + this.histo.axisMin;
            }

         // draw histo
         ctx.strokeStyle = m.color;
         ctx.fillStyle = m.color;
         ctx.beginPath();
         var x, y;
         var x_old = 0;
         var y_old = 0;
         for (i = 0; i < nBins; i++) {
            x = this.x1 + Math.floor(i / nBins * (this.hiWidth));
            y = this.hiy2 - Math.floor(histo[i] / hmax * (this.hiHeight - 30));
            if (i == 0) {
               ctx.moveTo(x, this.hiy2);
               ctx.lineTo(x, y);
            } else {
               ctx.lineTo(x, y_old);
               ctx.lineTo(x, y);
            }
            x_old = x;
            y_old = y;
         }
         x = this.x1 + this.hiWidth;
         ctx.lineTo(x, y);
         ctx.lineTo(x, this.hiy2);
         ctx.lineTo(this.x1, this.hiy2);
         ctx.closePath();
         ctx.save();
         ctx.globalAlpha = 0.4;
         ctx.stroke();
         ctx.fill();
         ctx.restore();

         // draw underflow and overflow bins
         if (uflow) {
            y = this.hiy2 - Math.floor(uflow / hmax * (this.hiHeight - 30));
            if (y < this.hiy1)
               y = this.hiy1;
            ctx.fillRect(this.x1 + uflowBin * 3, y, 3, this.hiy2 - y);
            uflowBin++;
         }

         if (oflow) {
            y = this.hiy2 - Math.floor(oflow / hmax * (this.hiHeight - 30));
            if (y < this.hiy1)
               y = this.hiy1;
            ctx.fillRect(this.x2 - 3 * (oflowBin + 1), y, 3, this.hiy2 - y);
            oflowBin++;
         }

         // print statistics
         var mean = histoSum / histoN;
         var std = Math.sqrt(histoSum2 / histoN - histoSum * histoSum / histoN / histoN);

         ctx.font = "14px monospace";

         if (nMeas == 1) {
            ctx.save();
            ctx.fillStyle = "white";
            ctx.fillText("      Mean       Std         N     UFlow     OFlow", this.x1, this.hiy1 + 10);
            ctx.restore();
         }
         ctx.fillText(pad(mean, 10, 3) +
            pad(std, 10, 4) +
            pad(histoN, 10, 0) +
            pad(uflow, 10, 0) +
            pad(oflow, 10, 0),
            this.x1, this.hiy1 + 10 + nMeas * 20);
      }
   }

   ctx.fillStyle = "#808080";
   ctx.strokeStyle = "#808080";

   // draw horizontal axis
   if (nMeas > 0)
      this.drawHAxis(ctx, this.x1, this.hiy2, this.hiWidth, 5, 7, 9, 10, 0, this.histo.axisMin, this.histo.axisMax);

   // draw drag handles
   ctx.save();

   if (this.histo.dragLeftHandle)
   // drag line
      ctx.drawLine(this.histo.dragX, this.hiy1, this.histo.dragX, this.hiy2);
   else {
      ctx.beginPath();
      ctx.moveTo(this.x1, this.hiy1 + this.hiHeight / 2 - 15);
      ctx.lineTo(this.x1 + 5, this.hiy1 + this.hiHeight / 2 - 15);
      ctx.arcTo(this.x1 + 15, this.hiy1 + this.hiHeight / 2 - 15, this.x1 + 15, this.hiy1 + this.hiHeight / 2 - 5, 10);
      ctx.lineTo(this.x1 + 15, this.hiy1 + this.hiHeight / 2 + 5);
      ctx.arcTo(this.x1 + 15, this.hiy1 + this.hiHeight / 2 + 15, this.x1 + 5, this.hiy1 + this.hiHeight / 2 + 15, 10);
      ctx.lineTo(this.x1, this.hiy1 + this.hiHeight / 2 + 15);
      ctx.closePath();
      ctx.globalAlpha = 0.4;
      ctx.stroke();
      ctx.fill();
      ctx.globalAlpha = 1;
      ctx.strokeStyle = "#808080";
      ctx.drawLine(this.x1 + 4, this.hiy1 + this.hiHeight / 2 - 12, this.x1 + 4, this.hiy1 + this.hiHeight / 2 + 12);
      ctx.drawLine(this.x1 + 10, this.hiy1 + this.hiHeight / 2 - 10, this.x1 + 10, this.hiy1 + this.hiHeight / 2 + 10);
   }

   if (this.histo.dragRightHandle)
   // drag line
      ctx.drawLine(this.histo.dragX, this.hiy1, this.histo.dragX, this.hiy2);
   else {

      ctx.beginPath();
      ctx.moveTo(this.x2, this.hiy1 + this.hiHeight / 2 - 15);
      ctx.lineTo(this.x2 - 5, this.hiy1 + this.hiHeight / 2 - 15);
      ctx.arcTo(this.x2 - 15, this.hiy1 + this.hiHeight / 2 - 15, this.x2 - 15, this.hiy1 + this.hiHeight / 2 - 5, 10);
      ctx.lineTo(this.x2 - 15, this.hiy1 + this.hiHeight / 2 + 5);
      ctx.arcTo(this.x2 - 15, this.hiy1 + this.hiHeight / 2 + 15, this.x2 - 5, this.hiy1 + this.hiHeight / 2 + 15, 10);
      ctx.lineTo(this.x2, this.hiy1 + this.hiHeight / 2 + 15);
      ctx.closePath();
      ctx.globalAlpha = 0.4;
      ctx.stroke();
      ctx.fill();
      ctx.globalAlpha = 1;
      ctx.strokeStyle = "#808080";
      ctx.drawLine(this.x2 - 4, this.hiy1 + this.hiHeight / 2 - 12, this.x2 - 4, this.hiy1 + this.hiHeight / 2 + 12);
      ctx.drawLine(this.x2 - 10, this.hiy1 + this.hiHeight / 2 - 10, this.x2 - 10, this.hiy1 + this.hiHeight / 2 + 10);
   }

   ctx.restore();

   // move buttons to right place
   for (i = 0; i < this.histo.button.length; i++) {
      if (this.histo.button[i].id == "measZoomFit") {
         if (this.histo.autoAxis)
            this.histo.button[i].style.display = "none";
         else
            this.histo.button[i].style.display = "block";
      } else
         this.histo.button[i].style.display = "block";
      this.histo.button[i].style.left = (this.x2 - 70) + "px";
      this.histo.button[i].style.top = (this.hiy1 + 10 + 30 * i) + "px";
   }
};

const LN10 = 2.302585094;
const LOG2 = 0.301029996;
const LOG5 = 0.698970005;

String.prototype.stripZeros = function () {
   var s = this.trim();
   if (s.search("[.]") >= 0) {
      while (s.charAt(s.length - 1) == "0")
         s = s.substring(0, s.length - 1);
      if (s.charAt(s.length - 1) == ".")
         s = s.substring(0, s.length - 1);
   }
   return s;
};

Oscilloscope.prototype.drawHAxis = function (ctx, x1, y1, width, minor, major, text, label, grid, xmin, xmax) {
   var dx, int_dx, frac_dx, x_act, label_dx, major_dx, x_screen, maxwidth;
   var tick_base, major_base, label_base, n_sig1, n_sig2, xs;
   var base = [1, 2, 5, 10, 20, 50, 100, 200, 500, 1000];

   ctx.textAlign = "center";

   if (xmax <= xmin || width <= 0)
      return;

   /* use 10 as min tick distance */
   dx = (xmax - xmin) / (width / 10);

   int_dx = Math.floor(Math.log(dx) / LN10);
   frac_dx = Math.log(dx) / LN10 - int_dx;

   if (frac_dx < 0) {
      frac_dx += 1;
      int_dx -= 1;
   }

   tick_base = frac_dx < LOG2 ? 1 : frac_dx < LOG5 ? 2 : 3;
   major_base = label_base = tick_base + 1;

   /* rounding up of dx, label_dx */
   dx = Math.pow(10, int_dx) * base[tick_base];
   major_dx = Math.pow(10, int_dx) * base[major_base];
   label_dx = major_dx;

   do {
      /* number of significant digits */
      if (xmin == 0)
         n_sig1 = 0;
      else
         n_sig1 = Math.floor(Math.log(Math.abs(xmin)) / LN10) - Math.floor(Math.log(Math.abs(label_dx)) / LN10) + 1;

      if (xmax == 0)
         n_sig2 = 0;
      else
         n_sig2 = Math.floor(Math.log(Math.abs(xmax)) / LN10) - Math.floor(Math.log(Math.abs(label_dx)) / LN10) + 1;

      n_sig1 = Math.max(n_sig1, n_sig2);
      // n_sig1 = Math.max(n_sig1, 2);

      /* determination of maximal width of labels */
      var str = (Math.floor(xmin / dx) * dx).toPrecision(n_sig1);
      var ext = ctx.measureText(str);
      maxwidth = ext.width;

      str = (Math.floor(xmax / dx) * dx).toPrecision(n_sig1).stripZeros();
      ext = ctx.measureText(str);
      maxwidth = Math.max(maxwidth, ext.width);
      str = (Math.floor(xmax / dx) * dx + label_dx).toPrecision(n_sig1).stripZeros();
      maxwidth = Math.max(maxwidth, ext.width);

      /* increasing label_dx, if labels would overlap */
      if (maxwidth > 0.5 * label_dx / (xmax - xmin) * width) {
         label_base++;
         label_dx = Math.pow(10, int_dx) * base[label_base];
         if (label_base % 3 == 2 && major_base % 3 == 1) {
            major_base++;
            major_dx = Math.pow(10, int_dx) * base[major_base];
         }
      } else
         break;

   } while (true);

   x_act = Math.floor(xmin / dx) * dx;

   ctx.drawLine(x1, y1, x1 + width, y1);

   do {
      x_screen = (x_act - xmin) / (xmax - xmin) * width + x1;
      xs = Math.floor(x_screen + 0.5);

      if (x_screen > x1 + width + 0.001)
         break;

      if (x_screen >= x1) {
         if (Math.abs(Math.floor(x_act / major_dx + 0.5) - x_act / major_dx) <
            dx / major_dx / 10.0) {

            if (Math.abs(Math.floor(x_act / label_dx + 0.5) - x_act / label_dx) <
               dx / label_dx / 10.0) {
               /* label tick mark */
               ctx.drawLine(xs, y1, xs, y1 + text);

               /* grid line */
               if (grid != 0 && xs > x1 && xs < x1 + width)
                  ctx.drawLine(xs, y1, xs, y1 + grid);

               /* label */
               if (label != 0) {
                  str = x_act.toPrecision(n_sig1).stripZeros();
                  ext = ctx.measureText(str);
                  ctx.save();
                  ctx.fillStyle = "white";
                  if (xs - ext.width / 2 > x1 &&
                     xs + ext.width / 2 < x1 + width)
                     ctx.fillText(str, xs, y1 + label);
                  ctx.restore();
               }
            } else {
               /* major tick mark */
               ctx.drawLine(xs, y1, xs, y1 + major);

               /* grid line */
               if (grid != 0 && xs > x1 && xs < x1 + width)
                  ctx.drawLine(xs, y1 - 1, xs, y1 + grid);
            }

         } else
         /* minor tick mark */
            ctx.drawLine(xs, y1, xs, y1 + minor);

      }

      x_act += dx;

      /* supress 1.23E-17 ... */
      if (Math.abs(x_act) < dx / 100)
         x_act = 0;

   } while (1);
};

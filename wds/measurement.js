//
//  measurement.js
//  Waveform Measurements
//
//  Created by Stefan Ritt on 26/8/16.
//

function Measurement(index, board1, channel1, board2, channel2) // constructor
{
   this.list = [
      { name:"Mean",      unit:"mV",  digits:1, f:this.MMean   },
      { name:"Sigma",     unit:"mV",  digits:1, f:this.MSigma  },
      { name:"Pk-Pk",     unit:"mV",  digits:1, f:this.MPkPk   },
      { name:"VSlice",    unit:"mV",  digits:1 },
      { name:"Charge",    unit:"pC",  digits:1 },

      { name:"Freq",      unit:"MHz", digits:1, f:this.MFreq   },
      { name:"Period",    unit:"ns",  digits:1, f:this.MPeriod },
      { name:"Rise",      unit:"ns",  digits:1 },
      { name:"Fall",      unit:"ns",  digits:1 },
      { name:"Pos Width", unit:"ns",  digits:1 },
      { name:"Neg Width", unit:"ns",  digits:1 },
      { name:"Chn delay", unit:"ns",  digits:1 },
      { name:"HSlice",    unit:"ns",  digits:3 },
   ];

   if (index >= this.list.length) {
      console.log("Measurement: invalid index");
      return;
   }

   this.board1 = board1;
   this.board2 = board2;
   this.channel1 = channel1;
   this.channel2 = channel2;
   this.index = index;
   this.param = [];
   this.value = undefined;
   this.setNStat(1000);
}

Measurement.prototype.resetStat = function() // reset statistics
{
   this.nMeasured = 0;
   this.statIndex = 0;
};

Measurement.prototype.setNStat = function(n)
{
   if (n > 1000000)
      n = 1000000;
   if (n < 1)
      n = 1;
   this.nStat = n;
   this.statArray = new Array(n);
   this.resetStat();
};

Measurement.prototype.getName = function()
{
   return this.list[this.index].name;
};

Measurement.prototype.measure = function(x1, y1, x2, y2, update, ctx)
{
   // execute measurement function in context of "this" object
   this.value = this.list[this.index].f.call(this, x1, y1, x2, y2, ctx);

   // update statistics
   if (update && this.value != undefined) {
      this.statArray[this.statIndex] = this.value;
      this.statIndex = (this.statIndex + 1) % this.nStat;

      var na;
      if (this.nMeasured < this.nStat) {
         this.nMeasured++;
         na = this.nMeasured;
      } else {
         na = this.nStat;
      }

      var vsum = 0;
      var vvsum = 0;
      this.min = this.max = this.value;

      for (var i=0 ; i<na ; i++) {
         vsum += this.statArray[i];
         vvsum += (this.statArray[i] * this.statArray[i]);
         if (this.statArray[i] < this.min)
            this.min = this.statArray[i];
         if (this.statArray[i] > this.max)
            this.max = this.statArray[i];
      }
      this.mean = vsum / this.nMeasured;
      this.std = Math.sqrt(vvsum/this.nMeasured - vsum*vsum/this.nMeasured/this.nMeasured);
   }

   return this.value;
};

function pad(number, chars, digits)
{
   if (number == undefined)
      return "             N/A".slice(-chars);
   if (digits == 0)
      return ("           "+number).slice(-chars);
   return ("           "+number.toFixed(digits)).slice(-chars);
}

Measurement.prototype.getString = function()
{
   if (this.value == undefined)
      return "      N/A";
   var str = pad(this.value, 6, this.list[this.index].digits);
   str += " "+this.list[this.index].unit;
   return str;
};

Measurement.prototype.print = function(index, ctx)
{
   ctx.fillStyle = OSC.chnColors[this.channel1];
   ctx.strokeStyle = 'white';
   ctx.font = '14px sans-serif';
   ctx.textAlign = "left";
   ctx.textBaseline = "top";
   ctx.fillText(this.list[this.index].name + " [CH" + this.channel1 + "]", OSC.x1+20, 35+index*20);

   ctx.font = "14px monospace";
   ctx.fillText(this.getString() +
                pad(this.min, 10, 3) +
                pad(this.max, 10, 3) +
                pad(this.mean, 10, 3) +
                pad(this.std, 10, 3) +
                pad(this.nMeasured, 10, 0),
                OSC.x1+150, 35+index*20);
};

Measurement.prototype.draw = function(ctx)
{
   ctx.fillStyle = OSC.chnColors[this.channel1];
   ctx.strokeStyle = OSC.chnColors[this.channel1];

   // execute measurement function in context of "this" object
   this.value = this.list[this.index].f.call(this, x1, y1, x2, y2, false, ctx);
}

//-------------------------------------------

Measurement.prototype.MMean = function(x, y, x2, y1, ctx)
{
   var mean = 0;
   for (var i = 0; i < x.length; i++)
      mean += y[i];

   if (x.length > 0)
      mean /= x.length;

   if (ctx != undefined)
      ctx.drawLine(OSC.timeToX(x[0]), OSC.voltToY(mean, 0), OSC.timeToX(x[x.length-1]), OSC.voltToY(mean, 0));

   return mean * 1000;
};

Measurement.prototype.MSigma = function(x, y, x2, y2, ctx)
{
   var mean = 0;
   var rms  = 0;

   if (x.legnth <= 0)
      return 0;

   for (var i=0 ; i< x.length ; i++)
      mean += y[i];
   mean /= x.length;

   for (i=0 ; i< x.length ; i++)
      rms += (y[i]-mean)*(y[i]-mean);
   rms = Math.sqrt(rms/x.length);

   if (ctx != undefined) {
      var ym = OSC.voltToY(mean, 0);
      ctx.beginPath();
      ctx.moveTo(OSC.timeToX(x[0]), ym);

      for (i=0 ; i< x.length; i++) {
         ctx.lineTo(OSC.timeToX(x[i]), OSC.voltToY(y[i], 0));
      }

      ctx.lineTo(OSC.timeToX(x[x.length-1]), ym);
      ctx.lineTo(OSC.timeToX(x[0]), ym);

      ctx.closePath();
      ctx.stroke();
      ctx.fill();
   }

   return rms * 1000;
};

Measurement.prototype.MPkPk = function(x, y, x2, y2, ctx)
{
   var min_x, min_y, max_x, max_y;

   min_x = max_x = x[0];
   min_y = max_y = y[0];
   for (var i = 0; i < x.length; i++)
   {
      if (y[i] < min_y) {
         min_x = x[i];
         min_y = y[i];
      }
      if (y[i] > max_y) {
         max_x = x[i];
         max_y = y[i];
      }
   }

   if (ctx != undefined) {
      var x_min = OSC.timeToX(min_x);
      var x_max = OSC.timeToX(max_x);
      var y_min = OSC.voltToY(min_y, 0);
      var y_max = OSC.voltToY(max_y, 0);

      var x_center = (x_min + x_max) / 2;

      if (x_max > x_min) {
         ctx.drawLine(x_min-20, y_min, x_center+20, y_min);
         ctx.drawLine(x_center-20, y_max, x_max+20, y_max);
      } else {
         ctx.drawLine(x_max-20, y_max, x_center+20, y_max);
         ctx.drawLine(x_center-20, y_min, x_min+20, y_min);
      }

      ctx.drawLine(x_center, y_max, x_center, y_min);

      ctx.beginPath();
      ctx.moveTo(x_center, y_max);
      ctx.lineTo(x_center+4, y_max+8);
      ctx.lineTo(x_center-4, y_max+8);
      ctx.moveTo(x_center, y_max);
      ctx.closePath();
      ctx.fill();

      ctx.beginPath();
      ctx.moveTo(x_center, y_min);
      ctx.lineTo(x_center+4, y_min-8);
      ctx.lineTo(x_center-4, y_min-8);
      ctx.moveTo(x_center, y_min);
      ctx.closePath();
      ctx.fill();
   }

   return (max_y - min_y) * 1000;
};

//-------------------------------------------

Measurement.prototype.MFreq = function(x, y, x2, y2, ctx)
{
   var p = this.MPeriod(x, y, x2, y2, ctx);

   if (p != undefined)
      return 1000/p;

   return undefined;
}

Measurement.prototype.MPeriod = function(x, y, x2, y2, ctx)
{
   var i;

   if (x.length <= 0)
      return 0;

   var miny = maxy = y[0];
   var mean = 0;
   for (i=0 ; i< x.length ; i++) {
      if (y[i] > maxy)
         maxy = y[i];
      if (y[i] < miny)
         miny = y[i];
      mean += y[i];
   }
   if (x.length < 5 || maxy - miny < 0.01)
      return undefined;

   mean = mean / x.length;
   for (i=0 ; i< x.length ; i++)
      y[i] -= mean;

   var xing = [];

   /* search and store zero crossings wiht noise rejection */
   for (i=5 ; i<x.length-5 ; i++) {
      if (y[i] > 0 && y[i+3] > 0 && y[i-1] <= 0 && y[i-4] <= 0)
         xing.push(i);
      if (y[i] < 0 && y[i+3] < 0 && y[i-1] >= 0 && y[i-4] >= 0)
         xing.push(i);
   }

   /* search zero crossing close to center */
   var min = 1;
   var mid = x[x.length/2];
   var i1;
   for (i=0 ; i<xing.length ; i++) {
      if (mid-x[xing[i]] < min && x[xing[i]] < mid) {
         min = mid-x[xing[i]];
         i1 = i;
      }
   }
   /* no edge on left half found, take first on right */
   if (i1 == undefined && xing.length > 0) {
      i1 = 0;
   }
   if (i1 == undefined)
      return undefined;

   i = xing[i1];
   var pos_edge = y[i] > 0;

   var t1 = (x[i-1]*y[i]-x[i]*y[i-1])/(y[i]-y[i-1]);

   /* search next zero crossing */
   var i2;
   for (i = i1+1 ; i<xing.length ; i++) {
      if (pos_edge && y[xing[i]] > 0) {
         i2 = i;
         break;
      }
      if (!pos_edge && y[xing[i]] < 0) {
         i2 = i;
         break;
      }
   }

   if (i2 == undefined)
      return undefined;

   i = xing[i2];
   var t2 = (x[i-1]*y[i]-x[i]*y[i-1])/(y[i]-y[i-1]);

   if (ctx != undefined) {
      var ym = OSC.voltToY(mean, 0);
      var x1 = OSC.timeToX(t1);
      var x2 = OSC.timeToX(t2);

      ctx.drawLine(x1, ym-10, x1, ym+10);

      ctx.beginPath();
      ctx.moveTo(x1, ym);
      ctx.lineTo(x1+8, ym+4);
      ctx.lineTo(x1+8, ym-4);
      ctx.moveTo(x1, ym);
      ctx.closePath();
      ctx.fill();

      ctx.drawLine(x1, ym, x2, ym);

      ctx.drawLine(x2, ym-10, x2, ym+10);

      ctx.beginPath();
      ctx.moveTo(x2, ym);
      ctx.lineTo(x2-8, ym+4);
      ctx.lineTo(x2-8, ym-4);
      ctx.moveTo(x2, ym);
      ctx.closePath();
      ctx.fill();
   }

   return (t2 - t1) * 1E9;
}


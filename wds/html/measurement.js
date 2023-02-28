//
//  measurement.js
//  Waveform Measurements
//
//  Created by Stefan Ritt on 26/8/16.
//

let measList = [
   {
      name: "Mean",
      unit: "mV",
      digits: 1,
      f: measMean,
      param: [{name: "WD", type: "WD", value: 0}, {name: "CH", type: "CH", value: 0}]
   },
   {
      name: "Sigma",
      unit: "mV",
      digits: 1,
      f: measSigma,
      param: [{name: "WD", type: "WD", value: 0}, {name: "CH", type: "CH", value: 0}]
   },
   {
      name: "Pk-Pk",
      unit: "mV",
      digits: 1,
      f: measPkPk,
      param: [{name: "WD", type: "WD", value: 0}, {name: "CH", type: "CH", value: 0}]
   },

   {
      name: "VSlice",
      unit: "mV",
      digits: 1,
      f: measVSlice,
      param: [
         {name: "WD", type: "WD", value: 0},
         {name: "CH", type: "CH", value: 0},
         {name: "Time", type: "tcursor", value: 100}
      ]
   },
   {
      name: "Charge",
      unit: "pC",
      digits: 1,
      f: measCharge,
      param: [
         {name: "WD", type: "WD", value: 0},
         {name: "CH", type: "CH", value: 0},
         {name: "T1Baseline", type: "tcursor", value: 10},
         {name: "T2Baseline", type: "tcursor", value: 20},
         {name: "T1Int", type: "tcursor", value: 150},
         {name: "T2Int", type: "tcursor", value: 180}
      ]
   },
   {
      name: "Chn correl",
      unit: "",
      digits: 3,
      f: measChnCorrel,
      param: [
         {name: "WD1", type: "WD", value: 0},
         {name: "CH1", type: "CH", value: 0},
         {name: "WD2", type: "WD", value: 0},
         {name: "CH2", type: "CH", value: 1},
      ]
   },
   //------------------
   {
      name: "Freq",
      unit: "MHz",
      digits: 1,
      f: measFreq,
      param: [{name: "WD", type: "WD", value: 0}, {name: "CH", type: "CH", value: 0}]
   },
   {
      name: "Period",
      unit: "ns",
      digits: 1,
      f: measPeriod,
      param: [{name: "WD", type: "WD", value: 0}, {name: "CH", type: "CH", value: 0}]
   },
   {
      name: "Rise",
      unit: "ns",
      digits: 1,
      f: measRise,
      param: [
         {name: "WD", type: "WD", value: 0},
         {name: "CH", type: "CH", value: 0},
         {name: "Low Level", type: "ucursor", value: 10},
         {name: "High Level", type: "ucursor", value: 100},
         ]
   },
   {
      name: "Fall",
      unit: "ns",
      digits: 1,
      f: measFall,
      param: [
         {name: "WD", type: "WD", value: 0},
         {name: "CH", type: "CH", value: 0},
         {name: "Low Level", type: "ucursor", value: 10},
         {name: "High Level", type: "ucursor", value: 100},
      ]
   },
   {
      name: "Pos Width",
      unit: "ns",
      digits: 1,
      f: measPosWidth,
      param: [
         {name: "WD", type: "WD", value: 0},
         {name: "CH", type: "CH", value: 0},
         {name: "Level", type: "ucursor", value: 50},
         ]
   },
   {
      name: "Neg Width",
      unit: "ns",
      digits: 1,
      f: measNegWidth,
      param: [
         {name: "WD", type: "WD", value: 0},
         {name: "CH", type: "CH", value: 0},
         {name: "Level", type: "ucursor", value: -20},
      ]
   },
   {
      name: "Chn delay",
      unit: "ns",
      digits: 1,
      f: measChnDelay,
      param: [
         {name: "WD1", type: "WD", value: 0},
         {name: "CH1", type: "CH", value: 0},
         {name: "Thr1", type: "ucursor", value: -10},
         {name: "WD2", type: "WD", value: 0},
         {name: "CH2", type: "CH", value: 0},
         {name: "Thr2", type: "ucursor", value: -10}
      ]
   },
   {
      name: "HSlice",
      unit: "ns",
      digits: 3,
      f: measHSlice,
      param: [
         {name: "WD", type: "WD", value: 0},
         {name: "CH", type: "CH", value: 0},
         {name: "Level", type: "ucursor", value: 100},
         {name: "T1", type: "tcursor", value: 50},
         {name: "T2", type: "tcursor", value: 150}
      ]
   },
];

function Measurement() // constructor
{
   this.index = undefined;
   this.value = undefined;
   this.color = undefined;
   this.setNStat(1000);
}

Measurement.prototype.setFunc = function (name) {

   // find name in array
   for (var i = 0; i < measList.length; i++) {
      if (measList[i].name == name)
         break;
   }
   if (i == measList.length) {
      console.log("Measurement: invalid index");
      return;
   }

   this.index = i;
   this.name = measList[i].name;
   this.unit = measList[i].unit;
   this.param = JSON.parse(JSON.stringify(measList[i].param)); // clone whole array
};

Measurement.prototype.resetStat = function () // reset statistics
{
   this.nMeasured = 0;
   this.statIndex = 0;
   this.min = undefined;
   this.max = undefined;
   this.mean = undefined;
   this.std = undefined;
};

Measurement.prototype.setNStat = function (n) {
   if (n > 1000000)
      n = 1000000;
   if (n < 1)
      n = 1;
   this.nStat = n;
   this.statArray = new Array(n);
   this.resetStat();
};

Measurement.prototype.measure = function (x, y, i1, i2, update, ctx) {

   if (i1 >= i2)
      return;

   // execute measurement function in context of "this" object
   this.value = measList[this.index].f.call(this, ctx, x, y, i1, i2);

   // update statistics
   if (update && this.value != undefined && !isNaN(this.value)) {
      this.statArray[this.statIndex] = this.value;
      this.statIndex = (this.statIndex + 1) % this.nStat;

      if (this.nMeasured < this.nStat) {
         this.nMeasured++;
      }

      let vsum = 0;
      let vvsum = 0;
      this.min = this.max = this.value;

      for (let i = 0; i < this.nMeasured; i++) {
         vsum += this.statArray[i];
         vvsum += (this.statArray[i] * this.statArray[i]);
         if (this.statArray[i] < this.min)
            this.min = this.statArray[i];
         if (this.statArray[i] > this.max)
            this.max = this.statArray[i];
      }
      this.mean = vsum / this.nMeasured;
      this.std = Math.sqrt(vvsum / this.nMeasured - vsum * vsum / this.nMeasured / this.nMeasured);
   }

   return this.value;
};

function pad(number, chars, digits) {
   if (number == undefined)
      return "             N/A".slice(-chars);
   if (digits == 0)
      return ("           " + number).slice(-chars);
   return ("           " + (number.toFixed(digits))).slice(-chars);
}

Measurement.prototype.getString = function () {
   if (this.value == undefined)
      return "      N/A";
   var str = pad(this.value, 6, measList[this.index].digits);
   str += " " + measList[this.index].unit;
   if (measList[this.index].unit.length == 2)
      str += " ";
   return str;
};

Measurement.prototype.print = function (index, ctx) {
   ctx.fillStyle = 'white';
   ctx.strokeStyle = 'white';
   ctx.font = '14px sans-serif';
   ctx.textAlign = "left";
   ctx.textBaseline = "top";

   var name = measList[this.index].name;
   var nCh = 0;
   for (var i = 0; i < this.param.length; i++) {
      if (this.param[i].type == "WD")
         name += "";
      if (this.param[i].type == "CH") {
         nCh++;
         name += "-CH" + this.param[i].value;
         if (nCh == 1) {
            if (OSC.disp.invert)
               this.color = OSC.chnColorsInverted[this.param[i].value];
            else
               this.color = OSC.chnColors[this.param[i].value];
         } else
            this.color = "#E0E0E0";
         ctx.fillStyle = this.color;
      }
   }

   ctx.fillText(name, OSC.x1 + 20, OSC.y1 + 10 + (index + 1) * 20);

   ctx.font = "14px monospace";
   ctx.fillText(this.getString() +
      pad(this.min, 10, 3) +
      pad(this.max, 10, 3) +
      pad(this.mean, 10, 3) +
      pad(this.std, 10, 4) +
      pad(this.nMeasured, 10, 0),
      OSC.x1 + 250, OSC.y1 + 10 + (index + 1) * 20);
};

Measurement.prototype.draw = function (ctx, x, y, i1, i2) {
   ctx.fillStyle = this.color;
   ctx.strokeStyle = this.color;

   // execute measurement function in context of "this" object
   this.value = measList[this.index].f.call(this, ctx, x, y, i1, i2);
};

//-------------------------------------------

function measMean(ctx, x, y, i1, i2) {
   var c = this.param[1].value;
   var mean = 0;
   for (var i = i1; i < i2; i++)
      mean += y[c][i];

   if (i2 > i1)
      mean /= (i2 - i1);

   if (ctx != undefined && OSC.chOn[c])
      ctx.drawLine(OSC.timeToX(x[c][i1]), OSC.voltToY(mean, c), OSC.timeToX(x[c][i2 - 1]), OSC.voltToY(mean, c));

   return mean * 1000;
}

function measSigma(ctx, x, y, i1, i2) {
   var c = this.param[1].value;
   var mean = 0;
   var rms = 0;

   for (var i = i1; i < i2; i++)
      mean += y[c][i];
   mean /= (i2 - i1);

   for (i = i1; i < i2; i++)
      rms += (y[c][i] - mean) * (y[c][i] - mean);
   rms = Math.sqrt(rms / (i2 - i1));

   if (ctx != undefined && OSC.chOn[c]) {
      var ym = OSC.voltToY(mean, c);
      ctx.beginPath();
      ctx.moveTo(OSC.timeToX(x[c][i1]), ym);

      for (i = i1; i < i2; i++) {
         ctx.lineTo(OSC.timeToX(x[c][i]), OSC.voltToY(y[c][i], c));
      }

      ctx.lineTo(OSC.timeToX(x[c][i2 - 1]), ym);
      ctx.lineTo(OSC.timeToX(x[c][i1]), ym);

      ctx.closePath();
      ctx.stroke();
      ctx.fill();
   }

   return rms * 1000;
}

function measPkPk(ctx, x, y, i1, i2) {
   var c = this.param[1].value;
   var min_x, min_y, max_x, max_y;

   min_x = max_x = x[c][i1];
   min_y = max_y = y[c][i1];
   for (var i = i1; i < i2; i++) {
      if (y[c][i] < min_y) {
         min_x = x[c][i];
         min_y = y[c][i];
      }
      if (y[c][i] > max_y) {
         max_x = x[c][i];
         max_y = y[c][i];
      }
   }

   if (ctx != undefined) {
      var x_min = OSC.timeToX(min_x);
      var x_max = OSC.timeToX(max_x);
      var y_min = OSC.voltToY(min_y, c);
      var y_max = OSC.voltToY(max_y, c);

      var x_center = (x_min + x_max) / 2;

      if (x_max > x_min) {
         ctx.drawLine(x_min - 20, y_min, x_center + 20, y_min);
         ctx.drawLine(x_center - 20, y_max, x_max + 20, y_max);
      } else {
         ctx.drawLine(x_max - 20, y_max, x_center + 20, y_max);
         ctx.drawLine(x_center - 20, y_min, x_min + 20, y_min);
      }

      ctx.drawLine(x_center, y_max, x_center, y_min);

      ctx.beginPath();
      ctx.moveTo(x_center, y_max);
      ctx.lineTo(x_center + 4, y_max + 8);
      ctx.lineTo(x_center - 4, y_max + 8);
      ctx.moveTo(x_center, y_max);
      ctx.closePath();
      ctx.fill();

      ctx.beginPath();
      ctx.moveTo(x_center, y_min);
      ctx.lineTo(x_center + 4, y_min - 8);
      ctx.lineTo(x_center - 4, y_min - 8);
      ctx.moveTo(x_center, y_min);
      ctx.closePath();
      ctx.fill();
   }

   return (max_y - min_y) * 1000;
}

function measVSlice(ctx, x, y) {
   var c = this.param[1].value;

   for (var i = 0; i < x[c].length - 1; i++)
      if (x[c][i] <= this.param[2].value * 1E-9 &&
         x[c][i + 1] > this.param[2].value * 1E-9)
         break;

   if (i == x[c].length - 1)
      return;

   if (x[c][i] == x[c][i + 1])
      return;

   var u = y[c][i] + (y[c][i + 1] - y[c][i]) * (this.param[2].value * 1E-9 - x[c][i]) / (x[c][i + 1] - x[c][i]);

   if (ctx != undefined && OSC.chOn[c]) {
      ctx.drawLine(OSC.timeToX(this.param[2].value * 1E-9), OSC.y1,
         OSC.timeToX(this.param[2].value * 1E-9), OSC.y2);
      ctx.drawLine(OSC.timeToX(this.param[2].value * 1E-9) - 10, OSC.voltToY(u, c),
         OSC.timeToX(this.param[2].value * 1E-9) + 10, OSC.voltToY(u, c));
   }

   return u * 1000;
}

function measCharge(ctx, x, y) {
   var c = this.param[1].value;

   var baseline = 0;
   var baseline_n = 0;
   var q = 0;
   var p1 = this.param[2].value * 1E-9;
   var p2 = this.param[3].value * 1E-9;
   var p3 = this.param[4].value * 1E-9;
   var p4 = this.param[5].value * 1E-9;
   var x1, y1, x2, y2;
   var first = true;

   for (var i = 0; i < x[c].length - 1; i++) {
      if (x[c][i] >= p1 && x[c][i] <= p2) {
         baseline += y[c][i];
         baseline_n++;
      }
   }

   // average baseline
   if (baseline_n > 0) {
      baseline /= baseline_n;

      if (ctx != undefined && OSC.chOn[c]) {
         ctx.beginPath();
         ctx.lineWidth = 3;
         ctx.moveTo(OSC.timeToX(p1), OSC.voltToY(baseline, c));
         ctx.lineTo(OSC.timeToX(p2), OSC.voltToY(baseline, c));

         ctx.moveTo(OSC.timeToX(p1), OSC.voltToY(baseline, c) - 10);
         ctx.lineTo(OSC.timeToX(p1), OSC.voltToY(baseline, c) + 10);

         ctx.moveTo(OSC.timeToX(p2), OSC.voltToY(baseline, c) - 10);
         ctx.lineTo(OSC.timeToX(p2), OSC.voltToY(baseline, c) + 10);

         ctx.stroke();
         ctx.lineWidth = 1;
      }
   }

   for (var i = 0; i < x[c].length - 1; i++) {

      if (x[c][i + 1] >= p3 && x[c][i] < p4) {
         if (x[c][i] < p3) {
            x1 = p3;
            y1 = y[c][i] + (y[c][i + 1] - y[c][i]) * (p3 - x[c][i]) / (x[c][i + 1] - x[c][i]);
         } else {
            x1 = x[c][i];
            y1 = y[c][i];
         }
         if (x[c][i + 1] > p4) {
            x2 = p4;
            y2 = y[c][i] + (y[c][i + 1] - y[c][i]) * (p4 - x[c][i]) / (x[c][i + 1] - x[c][i]);
         } else {
            x2 = x[c][i + 1];
            y2 = y[c][i + 1];
         }

         q += 0.5 * ((y1 + y2 - 2*baseline) * (x2 - x1));

         if (ctx != undefined && OSC.chOn[c]) {
            ctx.beginPath();
            ctx.moveTo(OSC.timeToX(x1), OSC.voltToY(baseline, c));
            ctx.lineTo(OSC.timeToX(x1), OSC.voltToY(y1, c));
            ctx.lineTo(OSC.timeToX(x2), OSC.voltToY(y2, c));
            ctx.lineTo(OSC.timeToX(x2), OSC.voltToY(baseline, c));
            ctx.closePath();
            ctx.stroke();
            ctx.fill();
         }
      }
   }

   return q / 50 * 1E12; // pC signal into 50 Ohm
}

//-------------------------------------------

function measFreq(ctx, x, y, i1, i2) {
   var p = measPeriod.call(this, ctx, x, y, i1, i2);

   if (p != undefined)
      return 1000 / p;
}

function measPeriod(ctx, xa, ya, i1, i2) {
   var c = this.param[1].value;
   var x = xa[c];
   var y = [];
   for (var i = 0; i < 1024; i++)
      y[i] = ya[c][i];

   var miny = y[i1];
   var maxy = y[i1];
   var mean = 0;
   for (i = i1; i < i2; i++) {
      if (y[i] > maxy)
         maxy = y[i];
      if (y[i] < miny)
         miny = y[i];
      mean += y[i];
   }
   if (i2 - i1 < 5 || maxy - miny < 0.01)
      return;

   mean = mean / (i2 - i1);
   for (i = i1; i < i2; i++)
      y[i] -= mean;

   var xing = [];

   /* search and store zero crossings with noise rejection */
   for (i = i1 + 5; i < i2 - 5; i++) {
      if (y[i] > 0 && y[i + 3] > 0 && y[i - 1] <= 0 && y[i - 4] <= 0)
         xing.push(i);
      if (y[i] < 0 && y[i + 3] < 0 && y[i - 1] >= 0 && y[i - 4] >= 0)
         xing.push(i);
   }

   /* search zero crossing close to center */
   var min = 1;
   var mid = x[Math.floor((i2 + i1) / 2)];
   var ia;
   for (i = 0; i < xing.length; i++) {
      if (mid - x[xing[i]] < min && x[xing[i]] < mid) {
         min = mid - x[xing[i]];
         ia = i;
      }
   }
   /* no edge on left half found, take first on right */
   if (ia == undefined && xing.length > 0) {
      ia = 0;
   }
   if (ia == undefined)
      return;

   i = xing[ia];
   var pos_edge = y[i] > 0;

   var t1 = (x[i - 1] * y[i] - x[i] * y[i - 1]) / (y[i] - y[i - 1]);

   /* search next zero crossing */
   var ib;
   for (i = ia + 1; i < xing.length; i++) {
      if (pos_edge && y[xing[i]] > 0) {
         ib = i;
         break;
      }
      if (!pos_edge && y[xing[i]] < 0) {
         ib = i;
         break;
      }
   }

   if (ib == undefined)
      return;

   i = xing[ib];
   var t2 = (x[i - 1] * y[i] - x[i] * y[i - 1]) / (y[i] - y[i - 1]);

   if (ctx != undefined && OSC.chOn[c]) {
      var ym = OSC.voltToY(mean, c);
      var x1 = OSC.timeToX(t1);
      var x2 = OSC.timeToX(t2);

      ctx.drawLine(x1, ym - 10, x1, ym + 10);

      ctx.beginPath();
      ctx.moveTo(x1, ym);
      ctx.lineTo(x1 + 8, ym + 4);
      ctx.lineTo(x1 + 8, ym - 4);
      ctx.moveTo(x1, ym);
      ctx.closePath();
      ctx.fill();

      ctx.drawLine(x1, ym, x2, ym);

      ctx.drawLine(x2, ym - 10, x2, ym + 10);

      ctx.beginPath();
      ctx.moveTo(x2, ym);
      ctx.lineTo(x2 - 8, ym + 4);
      ctx.lineTo(x2 - 8, ym - 4);
      ctx.moveTo(x2, ym);
      ctx.closePath();
      ctx.fill();
   }

   return (t2 - t1) * 1E9;
}

function measRise(ctx, xa, ya, i1, i2) {
   var c = this.param[1].value;
   var x = xa[c];
   var y = ya[c];

   var low =  parseFloat(this.param[2].value)/1000;
   var high =  parseFloat(this.param[3].value)/1000;

   /* search level crossings with noise rejection */
   var t1 = undefined;
   var t2 = undefined;
   for (i = i1 + 5; i < i2 - 5; i++) {
      if (y[i] < low && y[i - 3] < low && y[i + 1] >= low && y[i + 3] >= low && t1 === undefined)
         t1 = x[i] + (y[i]-low) * (x[i + 1] - x[i]) / (y[i] - y[i+1]);
      if (y[i] < high && y[i - 3] < high && y[i + 1] >= high && y[i + 3] >= high && t1 !== undefined && t2 === undefined)
         t2 = x[i] + (y[i]-high) * (x[i + 1] - x[i]) / (y[i] - y[i+1]);
   }

   if (ctx !== undefined && OSC.chOn[c]) {
      var x1 = OSC.timeToX(t1);
      var x2 = OSC.timeToX(t2);
      var y1 = OSC.voltToY(low, c);
      var y2 = OSC.voltToY(high, c);

      ctx.drawLine(x1, y1, x1, (y1+y2)/2-10);
      ctx.drawLine(x2, y2, x2, (y1+y2)/2+10);
      ctx.drawLine(x1, (y1+y2)/2, x2, (y1+y2)/2);

      ctx.drawLine(x1, (y1+y2)/2, x1+4, (y1+y2)/2-4);
      ctx.drawLine(x1, (y1+y2)/2, x1+4, (y1+y2)/2+4);

      ctx.drawLine(x2, (y1+y2)/2, x2-4, (y1+y2)/2-4);
      ctx.drawLine(x2, (y1+y2)/2, x2-4, (y1+y2)/2+4);
   }

   return (t2 - t1) * 1E9;
}

function measPosWidth(ctx, xa, ya, i1, i2) {
   var c = this.param[1].value;
   var x = xa[c];
   var y = ya[c];

   var level =  parseFloat(this.param[2].value)/1000;

   /* search level crossings with noise rejection */
   var t1 = undefined;
   var t2 = undefined;
   for (i = i1 + 5; i < i2 - 5; i++) {
      if (y[i] < level && y[i - 3] < level && y[i + 1] >= level && y[i + 3] >= level && t1 === undefined)
         t1 = x[i] + (y[i]-level) * (x[i + 1] - x[i]) / (y[i] - y[i+1]);
      if (y[i] > level && y[i - 3] > level && y[i + 1] <= level && y[i + 3] <= level && t1 !== undefined && t2 === undefined)
         t2 = x[i] + (y[i]-level) * (x[i + 1] - x[i]) / (y[i] - y[i+1]);
   }

   if (ctx !== undefined && OSC.chOn[c]) {
      var x1 = OSC.timeToX(t1);
      var x2 = OSC.timeToX(t2);
      var y  = OSC.voltToY(level, c);

      ctx.drawLine(x1, y, x2, y);
      ctx.drawLine(x1, y-10, x1, y+10);
      ctx.drawLine(x2, y-10, x2, y+10);

      ctx.drawLine(x1, y, x1+4, y-4);
      ctx.drawLine(x1, y, x1+4, y+4);

      ctx.drawLine(x2, y, x2-4, y-4);
      ctx.drawLine(x2, y, x2-4, y+4);
   }

   return (t2 - t1) * 1E9;
}

function measNegWidth(ctx, xa, ya, i1, i2) {
   var c = this.param[1].value;
   var x = xa[c];
   var y = ya[c];

   var level =  parseFloat(this.param[2].value)/1000;

   /* search level crossings with noise rejection */
   var t1 = undefined;
   var t2 = undefined;
   for (i = i1 + 5; i < i2 - 5; i++) {
      if (y[i] > level && y[i - 3] > level && y[i + 1] <= level && y[i + 3] <= level && t1 === undefined)
         t1 = x[i] + (y[i]-level) * (x[i + 1] - x[i]) / (y[i] - y[i+1]);
      if (y[i] < level && y[i - 3] < level && y[i + 1] >= level && y[i + 3] >= level && t1 !== undefined && t2 === undefined)
         t2 = x[i] + (y[i]-level) * (x[i + 1] - x[i]) / (y[i] - y[i+1]);
   }

   if (ctx !== undefined && OSC.chOn[c]) {
      var x1 = OSC.timeToX(t1);
      var x2 = OSC.timeToX(t2);
      var y  = OSC.voltToY(level, c);

      ctx.drawLine(x1, y, x2, y);
      ctx.drawLine(x1, y-10, x1, y+10);
      ctx.drawLine(x2, y-10, x2, y+10);

      ctx.drawLine(x1, y, x1+4, y-4);
      ctx.drawLine(x1, y, x1+4, y+4);

      ctx.drawLine(x2, y, x2-4, y-4);
      ctx.drawLine(x2, y, x2-4, y+4);
   }

   return (t2 - t1) * 1E9;
}

function measFall(ctx, xa, ya, i1, i2) {
   var c = this.param[1].value;
   var x = xa[c];
   var y = ya[c];

   var low =  parseFloat(this.param[2].value)/1000;
   var high =  parseFloat(this.param[3].value)/1000;

   /* search low level crossings with noise rejection */
   var t1 = undefined;
   var t2 = undefined;
   for (i = i1 + 5; i < i2 - 5; i++) {
      if (y[i] > high && y[i - 3] > high && y[i + 1] <= high && y[i + 3] <= high && t1 === undefined)
         t1 = x[i] + (y[i]-high) * (x[i + 1] - x[i]) / (y[i] - y[i+1]);
      if (y[i] > low && y[i - 3] > low && y[i + 1] <= low && y[i + 3] <= low && t1 !== undefined && t2 === undefined)
         t2 = x[i] + (y[i]-low) * (x[i + 1] - x[i]) / (y[i] - y[i+1]);
   }

   if (ctx !== undefined && OSC.chOn[c]) {
      var x1 = OSC.timeToX(t1);
      var x2 = OSC.timeToX(t2);
      var y1 = OSC.voltToY(high, c);
      var y2 = OSC.voltToY(low, c);

      ctx.drawLine(x1, y1, x1, (y1+y2)/2+10);
      ctx.drawLine(x2, y2, x2, (y1+y2)/2-10);
      ctx.drawLine(x1, (y1+y2)/2, x2, (y1+y2)/2);

      ctx.drawLine(x1, (y1+y2)/2, x1+4, (y1+y2)/2-4);
      ctx.drawLine(x1, (y1+y2)/2, x1+4, (y1+y2)/2+4);

      ctx.drawLine(x2, (y1+y2)/2, x2-4, (y1+y2)/2-4);
      ctx.drawLine(x2, (y1+y2)/2, x2-4, (y1+y2)/2+4);
   }

   return (t2 - t1) * 1E9;
}

function measHSlice(ctx, xa, ya, i1, i2) {
   var c = this.param[1].value;
   var x = xa[c];
   var y = ya[c];
   var level = this.param[2].value / 1000;
   var t1 = this.param[3].value * 1E-9;
   var t2 = this.param[4].value * 1E-9;

   var t = undefined;
   for (i = i1 + 5; i < i2 - 5; i++) {
      if (x[i] > t1 && x[i + 1] < t2) {
         if (y[i] < level && y[i - 3] < level && y[i + 1] >= level && y[i + 4] >= level) {
            if (y[i] < level && y[i - 3] < level && y[i + 1] >= level && y[i + 3] >= level && t === undefined)
               t = x[i] + (y[i] - level) * (x[i + 1] - x[i]) / (y[i] - y[i + 1]);
         }
      }
   }

   if (ctx != undefined && OSC.chOn[c]) {
      ctx.drawLine(OSC.timeToX(t1), OSC.voltToY(level, c), OSC.timeToX(t2), OSC.voltToY(level, c));
      ctx.drawLine(OSC.timeToX(t), OSC.voltToY(level, c)-10, OSC.timeToX(t), OSC.voltToY(level, c)+10);
   }

   return t * 1E9;
}


function measChnDelay(ctx, x, y, i1, i2) {
   var c1 = this.param[1].value;
   var thr1 = this.param[2].value / 1000;
   var c2 = this.param[4].value;
   var thr2 = this.param[5].value / 1000;

   if (thr1 < 0) {
      for (var i = i1; i < i2; i++)
         if (y[c1][i] >= thr1 && y[c1][i + 1] < thr1)
            break;
   } else {
      for (var i = i1; i < i2; i++)
         if (y[c1][i] <= thr1 && y[c1][i + 1] > thr1)
            break;
   }


   if (i == i2)
      return;

   if (x[c1][i + 1] == x[c1][i])
      return;

   var t1 = x[c1][i] + (thr1 - y[c1][i]) * (x[c1][i + 1] - x[c1][i]) / (y[c1][i + 1] - y[c1][i]);

   if (thr2 < 0) {
      for (i = i1; i < i2; i++)
         if (y[c2][i] >= thr2 && y[c2][i + 1] < thr2)
            break;
   } else {
      for (i = i1; i < i2; i++)
         if (y[c2][i] <= thr2 && y[c2][i + 1] > thr2)
            break;
   }

   if (i == i2)
      return;

   if (x[c2][i + 1] == x[c2][i])
      return;

   var t2 = x[c2][i] + (thr2 - y[c2][i]) * (x[c2][i + 1] - x[c2][i]) / (y[c2][i + 1] - y[c2][i]);

   if (ctx != undefined && OSC.chOn[c1] && OSC.chOn[c2]) {

      var x1 = OSC.timeToX(t1);
      var y1 = OSC.voltToY(thr1, c1);

      var x2 = OSC.timeToX(t2);
      var y2 = OSC.voltToY(thr2, c2);

      ctx.drawLine(x1 - 10, y1, x1 + 10, y1);
      ctx.drawLine(x1, y1, x1, (y1 + y2) / 2);
      ctx.drawLine(x1, (y1 + y2) / 2, x2, (y1 + y2) / 2);
      ctx.drawLine(x2, (y1 + y2) / 2, x2, y2);
      ctx.drawLine(x2 - 10, y2, x2 + 10, y2);
   }

   return (t1 - t2) * 1E9;
}

function measChnCorrel(ctx, x, y, i1, i2) {
   var c1 = this.param[1].value;
   var c2 = this.param[3].value;

   var mean1 = 0;
   var mean2 = 0;
   var rms1 = 0;
   var rms2 = 0;
   var cov = 0;

   if (i2 <= i1)
      return undefined;

   //calculate average
   for (var i = i1; i < i2; i++){
      mean1 += y[c1][i];
      mean2 += y[c2][i];
   }

   mean1 /= (i2 - i1);
   mean2 /= (i2 - i1);

   //calculate rms
   for (i = i1; i < i2; i++){
      rms1 += (y[c1][i] - mean1) * (y[c1][i] - mean1);
      rms2 += (y[c2][i] - mean2) * (y[c2][i] - mean2);
      cov  += (y[c2][i] - mean2) * (y[c1][i] - mean1);
   }
   rms1 = Math.sqrt(rms1 / (i2 - i1));
   rms2 = Math.sqrt(rms2 / (i2 - i1));
   cov = cov / (i2 - i1);
   cov = cov / (rms1*rms2);

   return cov;
}

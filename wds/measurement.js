//
//  measurement.js
//  Waveform Measurements
//
//  Created by Stefan Ritt on 26/8/16.
//

function Measurement(index, board1, channel1, board2, channel2) // constructor
{
   this.list = [
      { name:"Level",     unit:"mV",  digits:1, f:this.MLevel  },
      { name:"Pk-Pk",     unit:"mV",  digits:1, f:this.MPkPk   },
      { name:"RMS",       unit:"mV",  digits:1, f:this.MRMS    },
      { name:"VSlice",    unit:"mV",  digits:1 },
      { name:"Charge",    unit:"pC",  digits:1 },

      { name:"Freq",      unit:"MHz", digits:1 },
      { name:"Period",    unit:"ns",  digits:1 },
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
   this.statIndex = 0;
   this.nMeasured = 0;
   this.nStat = 1000;
   this.statArray = new Array(this.nStat);
   this.resetStat();
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
   this.value = this.list[this.index].f(x1, y1, x2, y2, ctx);

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

Measurement.prototype.draw = function(index, ctx)
{
   ctx.fillStyle = OSC.chnColors[this.channel1];
   ctx.strokeStyle = 'white';
   ctx.font = '14px sans-serif';
   ctx.textAlign = "left";
   ctx.textBaseline = "top";
   ctx.fillText(this.list[this.index].name + " [CH" + this.channel1 + "]", 20, 35+index*20);

   ctx.font = "14px monospace";
   ctx.fillText(this.getString() +
                pad(this.min, 10, 3) +
                pad(this.max, 10, 3) +
                pad(this.mean, 10, 3) +
                pad(this.std, 10, 3) +
                pad(this.nMeasured, 10, 0),
                150, 35+index*20);
};

//-------------------------------------------

Measurement.prototype.MLevel = function(x, y, x2, y1, ctx)
{
   var l = 0;
   for (var i = 0; i < x.length; i++)
      l += y[i];

   if (x.length > 0)
      l /= x.length;

   if (ctx != undefined) {
      //s->GetDC()->DrawLine(s->timeToX(x[0]), s->voltToY(l),
      //    s->timeToX(x[n-1]), s->voltToY(l));
   }
   return l * 1000;
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

   return (max_y - min_y) * 1000;
};

Measurement.prototype.MRMS = function(x, y, x2, y2, ctx)
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
   rms = Math.sqrt(rms/ x.length);

   return rms * 1000;
};

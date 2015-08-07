//
//  wds.js
//  WaveDAQ Server Application JavaScript Code
//
//  Created by Stefan Ritt on 5/8/15.
//

const CONTROLS_WIDTH = 200;

var s; // global scope object

var chnColors = [ "rgb(255, 255,   0)", // yellow
                  "rgb(170, 170, 255)", // light blue
                  "rgb(255, 150, 150)", // light red
                  "rgb(150, 255, 150)", // light green
                  "rgb(170, 170, 170)", // grey
                 ];

function Scope() { // constructor
   this.nFrames = 0;
   this.nFPS = 0;
   this.previousWidth = 0;
   this.previousHeight = 0;
   this.bottomHeight = 25;
   this.gridPath = null;
   this.wfT = [];
   this.wfU = [];
   this.wfScale = [];      // volts per division
   this.wfOffset = [];     // volts
   this.wfTOffset = 0;     // seconds
   this.wfTScale = 100E-9; // seconds per division
   this.wfUO = [];
   this.wfUS = [];
}

function init()
{
   s = new Scope();
   for (i=0 ; i<16 ; i++) {
      s.wfT[i] = [];
      s.wfU[i] = [];
      s.wfScale[i] = 0.1;
      s.wfOffset[i] = -0.5 + i/4;
   }
   
   var d = s.draw.bind(s);
   window.requestAnimationFrame(d);
   
   var r = s.readWF.bind(s);
   window.setTimeout(r, 20);
   
   var c = s.calcFPS.bind(s);
   s.t = setTimeout(c, 1000);
}

Scope.prototype.readWF = function()
{
   for (c=0 ; c<16 ; c++) {
      for (i=0 ; i<1024 ; i++) {
         this.wfT[c][i] = i*1E-9;
         this.wfU[c][i] = Math.sin(this.wfT[c][i] / 20 / 1E-9) / 4 + (Math.random()-0.5) / 30;
      }
   }

   var r = s.readWF.bind(s);
   window.setTimeout(r, 20);
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
      this.wfUO[c] = (this.y1+this.y2)/2 - this.wfOffset[c]/2*this.h;
      this.wfUS[c] = -this.h/this.wfScale[c]/10;
   }
}

Scope.prototype.drawWF = function(ctx)
{
   ctx.rect(this.x1, this.y1, this.w, this.h);
   ctx.clip();

   for (c=0 ; c<4 ; c++) {
      ctx.beginPath();
      for (i=0 ; i<1024 ; i++) {
         //var x = this.TtoX(this.wfT[c][i]);
         //var y = this.UtoY(c, this.wfU[c][i]);
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
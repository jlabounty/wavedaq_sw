//
//  wds.js
//  WaveDAQ Server Application JavaScript Code
//
//  Created by Stefan Ritt on 5/8/15.
//

const CONTROLS_WIDTH = 200;

var s; // global scope object

function Scope() { // constructor
   this.nFrames = 0;
   this.nFPS = 0;
   this.width = 0;
   this.height = 0;
   this.wfWidth = 0;
   this.wfHeight = 0;
   this.bottomHeight = 25;
   this.calcFPS();
}

Scope.prototype = {
   calcFPS: function() {
      var closure = this.Bind(this.calcFPS);
      this.nFPS = this.nFrames;
      this.nFrames = 0;
      this.t = setTimeout(closure, 1000);
   },
   
   Bind: function(method) {
      var _this = this;
      return (
         function() {
            return(method.apply(_this, arguments));
         }
      );
   }
}

function init()
{
   s = new Scope();
   window.requestAnimationFrame(s.drawScope);
}

Scope.prototype.drawScope = function()
{
   s.draw(); // allow access to "this"
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
   
   this.drawGrid(ctx);
   this.drawFPS(ctx);
   
   window.requestAnimationFrame(this.drawScope);
}

Scope.prototype.drawFPS = function(ctx)
{
   ctx.fillStyle = 'white';
   ctx.strokeStyle = 'white';
   ctx.font = '10pt Sans Serif';
   ctx.fillText(this.nFPS, 10, 15);
}

Scope.prototype.drawGrid = function(ctx)
{
   ctx.fillStyle = "black";
   ctx.fillRect(0, 0, s.width, s.height);
   
   ctx.strokeStyle = "#808080";
   ctx.lineWidth = 4;
   ctx.strokeRect(2, 2, this.wfWidth-4, this.wfHeight-4);
   var p = new Path2D();
   p.moveTo(0, 0);
   p.lineTo(ctx.canvas.width, ctx.canvas.height);
   
   ctx.stroke(p);
}

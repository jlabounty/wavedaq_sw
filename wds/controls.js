//
//  controls.js
//  Custom Controsl
//
//  Created by Stefan Ritt on 5/8/15.
//

(function(window) { // anonymous global function
   window.addEventListener("load", ctlInit, false);
})(window);

function ctlInit()
{
   var CTL = new Controls();
   CTL.init();
}

function Controls() // constructor
{
}

Controls.prototype.init = function() // scan DOM
{
   // scan DOM for controls
   this.ctrlButtonUp    = document.getElementsByName("ctrlButtonUp");
   this.ctrlButtonDown  = document.getElementsByName("ctrlButtonDown");
   this.ctrlButtonLeft  = document.getElementsByName("ctrlButtonLeft");
   this.ctrlButtonRight = document.getElementsByName("ctrlButtonRight");
   this.ctrlButtonZero  = document.getElementsByName("ctrlButtonZero");
   this.ctrlButtonDist  = document.getElementsByName("ctrlButtonDist");
   this.ctrlVSlider     = document.getElementsByName("ctrlVSlider");
   this.ctrlHSlider     = document.getElementsByName("ctrlHSlider");

   // ctrlButtonUp
   for (var i=0 ; i<this.ctrlButtonUp.length ; i++) {
      var cvs =  document.createElement("canvas");
      this.ctrlButtonUp[i].appendChild(cvs);

      cvs.width = 36;
      cvs.height = 32;
      var ctx = cvs.getContext("2d");
      ctx.fillStyle = "#E0E0E0";
      ctx.fillRect(0, 0, 36, 36);
      ctx.beginPath();
      ctx.moveTo(18, 7);
      ctx.lineTo(31, 27);
      ctx.lineTo(5, 27);
      ctx.lineTo(18, 7);
      ctx.closePath();
      ctx.fillStyle = "#808080";
      ctx.fill();
   }
   
   // ctrlButtonDown
   for (var i=0 ; i<this.ctrlButtonDown.length ; i++) {
      var cvs =  document.createElement("canvas");
      this.ctrlButtonDown[i].appendChild(cvs);

      cvs.width = 36;
      cvs.height = 32;
      var ctx = cvs.getContext("2d");
      ctx.fillStyle = "#E0E0E0";
      ctx.fillRect(0, 0, 36, 32);
      ctx.beginPath();
      ctx.moveTo(18, 29);
      ctx.lineTo(31, 9);
      ctx.lineTo(5, 9);
      ctx.lineTo(18, 29);
      ctx.closePath();
      ctx.fillStyle = "#808080";
      ctx.fill();
   }

   // ctrlButtonLeft
   for (var i=0 ; i<this.ctrlButtonLeft.length ; i++) {
      var cvs =  document.createElement("canvas");
      this.ctrlButtonLeft[i].appendChild(cvs);
      
      cvs.width = 36;
      cvs.height = 32;
      var ctx = cvs.getContext("2d");
      ctx.fillStyle = "#E0E0E0";
      ctx.fillRect(0, 0, 36, 32);
      ctx.beginPath();
      ctx.moveTo(7, 18);
      ctx.lineTo(27, 31);
      ctx.lineTo(27, 5);
      ctx.lineTo(7, 18);
      ctx.closePath();
      ctx.fillStyle = "#808080";
      ctx.fill();
   }
   
   // ctrlButtonRight
   for (var i=0 ; i<this.ctrlButtonRight.length ; i++) {
      var cvs =  document.createElement("canvas");
      this.ctrlButtonRight[i].appendChild(cvs);
      
      cvs.width = 36;
      cvs.height = 32;
      var ctx = cvs.getContext("2d");
      ctx.fillStyle = "#E0E0E0";
      ctx.fillRect(0, 0, 36, 32);
      ctx.beginPath();
      ctx.moveTo(29, 18);
      ctx.lineTo(9, 31);
      ctx.lineTo(9, 5);
      ctx.lineTo(29, 18);
      ctx.closePath();
      ctx.fillStyle = "#808080";
      ctx.fill();
   }
   
   // ctrlButtonZero
   for (var i=0 ; i<this.ctrlButtonZero.length ; i++) {
      var cvs =  document.createElement("canvas");
      this.ctrlButtonZero[i].appendChild(cvs);
      
      cvs.width = 36;
      cvs.height = 40;
      var ctx = cvs.getContext("2d");
      ctx.fillStyle = "#E0E0E0";
      ctx.fillRect(0, 0, 36, 32);
      ctx.fillStyle = "#808080";
      ctx.beginPath();
      ctx.moveTo(18, 22);
      ctx.lineTo(31, 7);
      ctx.lineTo(5, 7);
      ctx.lineTo(18, 22);
      ctx.closePath();
      ctx.fill();
      ctx.beginPath();
      ctx.moveTo(18, 22);
      ctx.lineTo(31, 37);
      ctx.lineTo(5, 37);
      ctx.lineTo(18, 22);
      ctx.fill();
   }

   // ctrlButtonDist
   for (var i=0 ; i<this.ctrlButtonDist.length ; i++) {
      var cvs =  document.createElement("canvas");
      this.ctrlButtonDist[i].appendChild(cvs);

      cvs.width = 36;
      cvs.height = 40;
      var ctx = cvs.getContext("2d");
      ctx.fillStyle = "#E0E0E0";
      ctx.fillRect(0, 0, 36, 32);
      ctx.fillStyle = "#808080";
      ctx.beginPath();
      ctx.moveTo(18, 3);
      ctx.lineTo(31, 18);
      ctx.lineTo(5, 18);
      ctx.lineTo(18, 3);
      ctx.closePath();
      ctx.fill();
      ctx.beginPath();
      ctx.moveTo(18, 39);
      ctx.lineTo(31, 24);
      ctx.lineTo(5, 24);
      ctx.lineTo(18, 39);
      ctx.fill();
   }

   // ctrlVSlider
   for (var i=0 ; i<this.ctrlVSlider.length ; i++) {
      var cvs =  document.createElement("canvas");
      var sl = this.ctrlVSlider[i];
      cvs.width = sl.clientWidth;
      cvs.height = sl.clientHeight;
      sl.appendChild(cvs);
      sl.canvas = cvs;
      
      sl.position = 0.5; // slider position 0...1
      sl.addEventListener("click", this.ctrlVSliderHandler.bind(this));
      sl.addEventListener("mousemove", this.ctrlVSliderHandler.bind(this));
      sl.addEventListener("touchmove", this.ctrlVSliderHandler.bind(this));
      sl.draw = this.ctrlVSliderDraw;
      sl.draw(sl);
   }

   // ctrlHSlider
   for (var i=0 ; i<this.ctrlHSlider.length ; i++) {
      var cvs =  document.createElement("canvas");
      var sl = this.ctrlHSlider[i];
      cvs.width = sl.clientWidth;
      cvs.height = sl.clientHeight;
      sl.appendChild(cvs);
      sl.canvas = cvs;
      
      sl.position = 0.5; // slider position 0...1
      sl.addEventListener("click", this.ctrlHSliderHandler.bind(this));
      sl.addEventListener("mousemove", this.ctrlHSliderHandler.bind(this));
      sl.addEventListener("touchmove", this.ctrlHSliderHandler.bind(this));
      sl.draw = this.ctrlHSliderDraw;
      sl.draw(sl);
      sl.set = this.ctrlHSliderSet;
   }

};

Controls.prototype.roundedRect = function(ctx, x, y, w, h, r)
{
   // correct for line width
   x += ctx.lineWidth/2;
   y += ctx.lineWidth/2;
   w -= ctx.lineWidth;
   h -= ctx.lineWidth;
   
   ctx.beginPath();
   
   // draw top and top right corner
   ctx.moveTo(x+r,y);
   ctx.arcTo(x+w,y,x+w,y+r,r);
   
   // draw right side and bottom right corner
   ctx.arcTo(x+w,y+h,x+w-r,y+h,r);
   
   // draw bottom and bottom left corner
   ctx.arcTo(x,y+h,x,y+h-r,r);
   
   // draw left and top left corner
   ctx.arcTo(x,y,x+r,y,r);
   
   ctx.fill();
   ctx.stroke();
}


Controls.prototype.ctrlVSliderDraw = function(b)
{
   if (b == undefined)
      b = this;
   var w = b.canvas.width;
   var h = b.canvas.height;
   b.sliderOfs = 20;
   
   var ctx = b.canvas.getContext("2d");
   ctx.fillStyle = "#E0E0E0";
   ctx.fillRect(0, 0, b.canvas.width, b.canvas.height);
   
   var knob = b.sliderOfs + (1-b.position)*(h-2*b.sliderOfs);
   
   ctx.strokeStyle = "#A0A0A0";
   ctx.lineWidth = 3;
   ctx.beginPath();
   ctx.moveTo(w/2, b.sliderOfs);
   ctx.lineTo(w/2, knob);
   ctx.stroke();
   
   ctx.strokeStyle = "#00A0FF";
   ctx.beginPath();
   ctx.moveTo(w/2, knob);
   ctx.lineTo(w/2, h-b.sliderOfs);
   ctx.stroke();
   
   ctx.fillStyle = "#E0E0E0";
   ctx.strokeStyle = "#C0C0C0";
   ctx.beginPath();
   ctx.arc(w/2, knob, 10, 0, 2*Math.PI);
   ctx.stroke();
   ctx.fill();
}

Controls.prototype.ctrlVSliderHandler = function(e)
{
   e.preventDefault();
   var y = undefined;
   var b = e.currentTarget;
   
   if (b.canvas == undefined) // we can get events from parent node
      return;
   
   if ((e.buttons == 1 && e.type == "mousemove") || e.type == "click")
      y = e.offsetY;
   if (e.type == "touchmove")
      y = e.changedTouches[e.changedTouches.length-1].clientY - b.getBoundingClientRect().top;
   
   if (y != undefined) {
      b.position = 1 - (y-b.sliderOfs)/(b.clientHeight-2*b.sliderOfs);
      if (b.position < 0)
         b.position = 0;
      if (b.position > 1)
         b.position = 1;
      this.ctrlVSliderDraw(b);
      var f = b.dataset.update;
      if (f.indexOf("("))
         f = f.substr(0, f.indexOf("("));
      window[f](b.position);
   }
}

Controls.prototype.ctrlHSliderDraw = function(b)
{
   if (b == undefined)
      b = this;
   var w = b.canvas.width;
   var h = b.canvas.height;
   b.sliderOfs = 20;
   
   var ctx = b.canvas.getContext("2d");
   ctx.fillStyle = "#E0E0E0";
   ctx.fillRect(0, 0, b.canvas.width, b.canvas.height);
   
   var knob = b.sliderOfs + (b.position)*(w-2*b.sliderOfs);
   
   ctx.strokeStyle = "#A0A0A0";
   ctx.lineWidth = 3;
   ctx.beginPath();
   ctx.moveTo(w-b.sliderOfs, h/2);
   ctx.lineTo(knob, h/2);
   ctx.stroke();
   
   ctx.strokeStyle = "#00A0FF";
   ctx.beginPath();
   ctx.moveTo(knob, h/2);
   ctx.lineTo(b.sliderOfs, h/2);
   ctx.stroke();
   
   ctx.fillStyle = "#E0E0E0";
   ctx.strokeStyle = "#C0C0C0";
   ctx.beginPath();
   ctx.arc(knob, h/2, 10, 0, 2*Math.PI);
   ctx.stroke();
   ctx.fill();
}

Controls.prototype.ctrlHSliderSet = function(pos)
{
   this.position = pos;
   this.draw();
}

Controls.prototype.ctrlHSliderHandler = function(e)
{
   e.preventDefault();
   var x = undefined;
   var b = e.currentTarget;
   
   if (b.canvas == undefined) // we can get events from parent node
      return;
   
   if ((e.buttons == 1 && e.type == "mousemove") || e.type == "click")
      x = e.offsetX;
   if (e.type == "touchmove")
      x = e.changedTouches[e.changedTouches.length-1].clientX - b.getBoundingClientRect().left;
   
   if (x != undefined) {
      b.position = (x-b.sliderOfs)/(b.clientWidth-2*b.sliderOfs);
      if (b.position < 0)
         b.position = 0;
      if (b.position > 1)
         b.position = 1;
      this.ctrlHSliderDraw(b);
      var f = b.dataset.update;
      if (f.indexOf("("))
         f = f.substr(0, f.indexOf("("));
      window[f](b.position);
   }
}

//
//  controls.js
//  Custom Controsl
//
//  Created by Stefan Ritt on 5/8/15.
//

function roundedRect(ctx, x, y, w, h, r)
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

function controlsInit() {
   
   // ctrlButtonUp
   var b = document.getElementsByName("ctrlButtonUp");
   for (i=0 ; i<b.length ; i++) {
      var cvs =  document.createElement("canvas");
      b[i].appendChild(cvs);

      cvs.width = 36;
      cvs.height = 32;
      var ctx = cvs.getContext("2d");
      ctx.fillStyle = "#E0E0E0";
      ctx.fillRect(0, 0, 36, 32);
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
   var b = document.getElementsByName("ctrlButtonDown");
   for (i=0 ; i<b.length ; i++) {
      var cvs =  document.createElement("canvas");
      b[i].appendChild(cvs);

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

   // ctrlButtonZero
   var b = document.getElementsByName("ctrlButtonZero");
   for (i=0 ; i<b.length ; i++) {
      var cvs =  document.createElement("canvas");
      b[i].appendChild(cvs);
      
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
   var b = document.getElementsByName("ctrlButtonDistr");
   for (i=0 ; i<b.length ; i++) {
      var cvs =  document.createElement("canvas");
      b[i].appendChild(cvs);

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
   var b = document.getElementsByName("ctrlVSlider");
   for (i=0 ; i<b.length ; i++) {
      var cvs =  document.createElement("canvas");
      cvs.width = b[i].clientWidth;
      cvs.height = b[i].clientHeight;
      b[i].appendChild(cvs);
      b[i].canvas = cvs;
      
      b[i].position = 0.5;
      b[i].addEventListener("click", ctrlVSlider);
      b[i].addEventListener("mousemove", ctrlVSlider);
      b[i].addEventListener("touchmove", ctrlVSlider);
      ctrlVSliderDraw(b[i]);
   }
   
}

function ctrlVSliderDraw(b)
{
   var w = b.clientWidth;
   var h = b.clientHeight;
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

function ctrlVSlider(e)
{
   e.preventDefault();
   var y = undefined;
   var b = e.target.parentNode;
   
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
      ctrlVSliderDraw(b);
      var f = b.dataset.update;
      if (f.indexOf("("))
         f = f.substr(0, f.indexOf("("));
      window[f](b.position);
   }
}
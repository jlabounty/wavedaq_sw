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
   var cvs = document.getElementsByName("ctrlButtonUp");
   for (i=0 ; i<cvs.length ; i++) {
      cvs[i].width = 36;
      cvs[i].height = 32;
      var ctx = cvs[i].getContext("2d");
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
   var cvs = document.getElementsByName("ctrlButtonDown");
   for (i=0 ; i<cvs.length ; i++) {
      cvs[i].width = 36;
      cvs[i].height = 32;
      var ctx = cvs[i].getContext("2d");
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
   
   // ctrlVSlider
   var sl = document.getElementsByName("ctrlVSlider");
   for (i=0 ; i<sl.length ; i++) {
      sl[i].position = 0.5;
      sl[i].addEventListener("click", dummy);
      sl[i].addEventListener("mousemove", ctrlVSlider);
      sl[i].addEventListener("touchmove", dummy);
      ctrlVSliderDraw(sl[i]);
   }
   
}

function dummy(e)
{
   console.log(e);
}

function ctrlVSliderDraw(sl)
{
   var w = sl.width;
   var h = sl.height;
   sl.sliderOfs = 20;
   
   var ctx = sl.getContext("2d");
   ctx.fillStyle = "#E0E0E0";
   ctx.strokeStyle = "#C0C0C0";
   ctx.lineWidth = 2;
   roundedRect(ctx, 0, 0, w, h, 5);
   
   var knob = sl.sliderOfs + (1-sl.position)*(h-2*sl.sliderOfs);
   
   ctx.strokeStyle = "#A0A0A0";
   ctx.lineWidth = 3;
   ctx.beginPath();
   ctx.moveTo(w/2, sl.sliderOfs);
   ctx.lineTo(w/2, knob);
   ctx.stroke();
   
   ctx.strokeStyle = "#00A0FF";
   ctx.beginPath();
   ctx.moveTo(w/2, knob);
   ctx.lineTo(w/2, h-sl.sliderOfs);
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
   if (e.buttons == 1) {
      e.target.position = 1- (e.offsetY-e.target.sliderOfs)/(e.target.height-2*e.target.sliderOfs);
      if (e.target.position < 0)
         e.target.position = 0;
      if (e.target.position > 1)
         e.target.position = 1;
      ctrlVSliderDraw(e.target);
   }
   e.preventDefault();
   e.target.update(e.target.position);
}
//
//  controls.js
//  Custom Controls
//
//  Created by Stefan Ritt on 5/8/15.
//

/*

 Usage
 =====

 Dialogs
 -------

 <button type="button" onClick="dlgShow('dlgXXX')">XXX</button>


 <div id="dlgXXX" class="dlgFrame">
 <div class="dlgTitlebar">Title</div>
 <div class="dlgPanel">
 <div>Dialog Contents</div>
 <button type="button" onClick="dlgHide('dlgXXX')">Close</button>
 </div>
 </div>



 Sliders
 -------

 <button name="ctrlHSlider" type="button" data-update="xxx()"></button>

 <button name="ctrlVSlider" type="button" data-update="xxx()"></button>



 Icon buttons
 ------------

 <button name="ctrlButton" data-icon="<icon>" type="button"></button>

 <icon> = up, down, left, right, vcoll, vexp, add, remove

 */

document.write("<style>" +
   ".dlgFrame {" +
   "   border: 1px solid black;" +
   "   border-radius: 6px;" +
   "   position: absolute;" +
   "   top: 0;" +
   "   left: 0;" +
   "   display: none; // pre-hidden" +
   "}" +
   ".dlgTitlebar {" +
   "   text-align: center;" +
   "   background-color: #C0C0C0;" +
   "   border-top-left-radius: 6px;" +
   "   border-top-right-radius: 6px;" +
   "   font-size: 10pt;" +
   "   padding: 2px;" +
   "}" +
   ".dlgPanel {" +
   "   background-color: #F0F0F0;" +
   "   text-align: center;" +
   "   padding: 5px;" +
   "   border-bottom-left-radius: 6px;" +
   "   border-bottom-right-radius: 6px;" +
   "}" +
   "</style>");

(function (window) { // anonymous global function
   window.addEventListener("load", ctlInit, false);
})(window);

function ctlInit() {
   var CTL = new Controls();
   CTL.init();
}

function Controls() // constructor
{
}

Controls.prototype.init = function () // scan DOM
{
   // scan DOM for controls
   this.ctrlButton = document.getElementsByName("ctrlButton");
   this.ctrlVSlider = document.getElementsByName("ctrlVSlider");
   this.ctrlHSlider = document.getElementsByName("ctrlHSlider");

   // ctrlButton
   for (var i = 0; i < this.ctrlButton.length; i++) {
      var cvs = document.createElement("canvas");
      this.ctrlButton[i].appendChild(cvs);

      if (this.ctrlButton[i].dataset.icon == "up") {
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

      if (this.ctrlButton[i].dataset.icon == "down") {
         cvs.width = 36;
         cvs.height = 32;
         ctx = cvs.getContext("2d");
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

      if (this.ctrlButton[i].dataset.icon == "left") {
         cvs.width = 36;
         cvs.height = 32;
         ctx = cvs.getContext("2d");
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

      if (this.ctrlButton[i].dataset.icon == "right") {
         cvs.width = 36;
         cvs.height = 32;
         ctx = cvs.getContext("2d");
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

      if (this.ctrlButton[i].dataset.icon == "plus") {
         cvs.width = 36;
         cvs.height = 36;
         ctx = cvs.getContext("2d");
         ctx.fillStyle = "#E0E0E0";
         ctx.fillRect(0, 0, 36, 36);
         ctx.strokeStyle = "#808080";
         ctx.lineWidth = 3;
         ctx.drawLine(18, 7, 18, 29);
         ctx.drawLine(7, 18, 29, 18);
      }

      if (this.ctrlButton[i].dataset.icon == "minus") {
         cvs.width = 36;
         cvs.height = 36;
         ctx = cvs.getContext("2d");
         ctx.fillStyle = "#E0E0E0";
         ctx.fillRect(0, 0, 36, 36);
         ctx.strokeStyle = "#FF0000";
         ctx.lineWidth = 3;
         ctx.drawLine(7, 18, 29, 18);
      }

      if (this.ctrlButton[i].dataset.icon == "vcoll") {
         cvs.width = 36;
         cvs.height = 40;
         ctx = cvs.getContext("2d");
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

      if (this.ctrlButton[i].dataset.icon == "vexp") {
         cvs.width = 36;
         cvs.height = 40;
         ctx = cvs.getContext("2d");
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
   }

   // ctrlVSlider
   for (i = 0; i < this.ctrlVSlider.length; i++) {
      cvs = document.createElement("canvas");
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
   for (i = 0; i < this.ctrlHSlider.length; i++) {
      cvs = document.createElement("canvas");
      sl = this.ctrlHSlider[i];
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

Controls.prototype.ctrlVSliderDraw = function (b) {
   if (b == undefined)
      b = this;
   var w = b.canvas.width;
   var h = b.canvas.height;
   b.sliderOfs = 20;

   var ctx = b.canvas.getContext("2d");
   ctx.fillStyle = "#E0E0E0";
   ctx.fillRect(0, 0, b.canvas.width, b.canvas.height);

   var knob = b.sliderOfs + (1 - b.position) * (h - 2 * b.sliderOfs);

   ctx.strokeStyle = "#A0A0A0";
   ctx.lineWidth = 3;
   ctx.beginPath();
   ctx.moveTo(w / 2, b.sliderOfs);
   ctx.lineTo(w / 2, knob);
   ctx.stroke();

   ctx.strokeStyle = "#00A0FF";
   ctx.beginPath();
   ctx.moveTo(w / 2, knob);
   ctx.lineTo(w / 2, h - b.sliderOfs);
   ctx.stroke();

   ctx.fillStyle = "#E0E0E0";
   ctx.strokeStyle = "#C0C0C0";
   ctx.beginPath();
   ctx.arc(w / 2, knob, 10, 0, 2 * Math.PI);
   ctx.stroke();
   ctx.fill();
};

Controls.prototype.ctrlVSliderHandler = function (e) {
   e.preventDefault();
   var y = undefined;
   var b = e.currentTarget;

   if (b.canvas == undefined) // we can get events from parent node
      return;

   if ((e.buttons == 1 && e.type == "mousemove") || e.type == "click")
      y = e.offsetY;
   if (e.type == "touchmove")
      y = e.changedTouches[e.changedTouches.length - 1].clientY - b.getBoundingClientRect().top;

   if (y != undefined) {
      b.position = 1 - (y - b.sliderOfs) / (b.clientHeight - 2 * b.sliderOfs);
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
};

Controls.prototype.ctrlHSliderDraw = function (b) {
   if (b == undefined)
      b = this;
   var w = b.canvas.width;
   var h = b.canvas.height;
   b.sliderOfs = 20;

   var ctx = b.canvas.getContext("2d");
   ctx.fillStyle = "#E0E0E0";
   ctx.fillRect(0, 0, b.canvas.width, b.canvas.height);

   var knob = b.sliderOfs + (b.position) * (w - 2 * b.sliderOfs);

   ctx.strokeStyle = "#A0A0A0";
   ctx.lineWidth = 3;
   ctx.beginPath();
   ctx.moveTo(w - b.sliderOfs, h / 2);
   ctx.lineTo(knob, h / 2);
   ctx.stroke();

   ctx.strokeStyle = "#00A0FF";
   ctx.beginPath();
   ctx.moveTo(knob, h / 2);
   ctx.lineTo(b.sliderOfs, h / 2);
   ctx.stroke();

   ctx.fillStyle = "#E0E0E0";
   ctx.strokeStyle = "#C0C0C0";
   ctx.beginPath();
   ctx.arc(knob, h / 2, 10, 0, 2 * Math.PI);
   ctx.stroke();
   ctx.fill();
};

Controls.prototype.ctrlHSliderSet = function (pos) {
   this.position = pos;
   this.draw();
};

Controls.prototype.ctrlHSliderHandler = function (e) {
   e.preventDefault();
   var x = undefined;
   var b = e.currentTarget;

   if (b.canvas == undefined) // we can get events from parent node
      return;

   if ((e.buttons == 1 && e.type == "mousemove") || e.type == "click")
      x = e.offsetX;
   if (e.type == "touchmove")
      x = e.changedTouches[e.changedTouches.length - 1].clientX - b.getBoundingClientRect().left;

   if (x != undefined) {
      b.position = (x - b.sliderOfs) / (b.clientWidth - 2 * b.sliderOfs);
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
};

//-------------------------------------------------------------------------------------------------

function dlgShow(dlg) {
   var d = document.getElementById(dlg);

   d.dlgAx = 0;
   d.dlgAy = 0;
   d.dlgDx = 0;
   d.dlgDy = 0;

   d.style.display = "block";
   d.style.left = document.documentElement.clientWidth / 2 - d.offsetWidth / 2 + "px";
   if (document.documentElement.clientHeight / 2 - d.offsetHeight / 2 < 0)
      d.style.top = "0px";
   else
      d.style.top = document.documentElement.clientHeight / 2 - d.offsetHeight / 2 + "px";

   d.dlgMouseDown = function (e) {
      if ((e.target == this || e.target.parentNode == this) &&
         e.target.className == "dlgTitlebar") {
         this.Ax = e.clientX;
         this.Ay = e.clientY;
         this.Dx = parseInt(this.style.left);
         this.Dy = parseInt(this.style.top);
      }
   };

   d.dlgMouseMove = function (e) {
      if (this.Ax > 0 && this.Ay > 0) {
         e.preventDefault();
         var x = e.clientX;
         var y = e.clientY;
         this.style.left = (this.Dx + (x - this.Ax)) + "px";
         this.style.top = (this.Dy + (y - this.Ay)) + "px";
      }
   };

   d.dlgMouseUp = function () {
      this.Ax = 0;
      this.Ay = 0;
   };

   d.dlgTouchStart = function (e) {
      if (e.target == this || e.target.parentNode == this) {
         e.preventDefault();
         this.Ax = e.targetTouches[0].clientX;
         this.Ay = e.targetTouches[0].clientY;
         this.Dx = parseInt(this.style.left);
         this.Dy = parseInt(this.style.top);
      }
   };

   d.dlgTouchMove = function (e) {
      var x = e.changedTouches[e.changedTouches.length - 1].clientX;
      var y = e.changedTouches[e.changedTouches.length - 1].clientY;
      this.style.left = (this.Dx + (x - this.Ax)) + "px";
      this.style.top = (this.Dy + (y - this.Ay)) + "px";
   };

   window.addEventListener("mousedown", d.dlgMouseDown.bind(d), true);
   window.addEventListener("mousemove", d.dlgMouseMove.bind(d), true);
   window.addEventListener("mouseup", d.dlgMouseUp.bind(d), true);
   window.addEventListener("touchstart", d.dlgTouchStart.bind(d), true);
   window.addEventListener("touchmove", d.dlgTouchMove.bind(d), true);
}

function dlgHide(dlg) {
   var d = document.getElementById(dlg);
   d.style.display = "none";
}

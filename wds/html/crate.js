//
//  crate.js
//  JavaScript Code for WaveDAQ crate display
//
//  Created by Stefan Ritt on 02/12/2020.
//

var CRATE; // global crate object

// extend 2d canvas object
CanvasRenderingContext2D.prototype.drawLine = function (x1, y1, x2, y2) {
   this.beginPath();
   this.moveTo(x1, y1);
   this.lineTo(x2, y2);
   this.stroke();
};

function init() {
   // prevent mouse events to go up to the browser
   let c = document.getElementById("controls");
   c.addEventListener("click", function (e) {
      e.preventDefault()
   });
   c.addEventListener("mousemove", function (e) {
      e.preventDefault()
   });

   c = document.getElementById("crate");
   c.addEventListener("click", function (e) {
      e.preventDefault()
   });
   c.addEventListener("mousemove", function (e) {
      e.preventDefault()
   });

   // create Scope object
   CRATE = new Crate(document.getElementById("crate"));
   resize();

   // add resize event handler
   window.addEventListener("resize", resize);

   // load spinning wheel image
   CRATE.spinningWheel = new Image();
   CRATE.spinningWheel.src = "spinning-wheel-wds.gif";
}

function resize() {
   CRATE.resize(document.documentElement.clientWidth,
      document.documentElement.clientHeight);
}

function Crate(div) { // constructor
   this.canvas = document.createElement("canvas");
   div.appendChild(this.canvas);
}

Crate.prototype.resize = function (width, height) {
   this.canvas.width = width;
   this.canvas.height = width / 5;
   this.draw();
}

Crate.prototype.draw = function () {
   let ctx = this.canvas.getContext("2d");

   // scale canvas such that a 1000x200 px rectangle fills the whole window
   ctx.scale(this.canvas.width / 1000, this.canvas.width / 1000);

   ctx.fillStyle = "#E0E0E0";
   ctx.fillRect(0, 0, 1000, 200);

   ctx.fillStyle = "black";
   ctx.fillRect(30, 30, 940, 140);
}
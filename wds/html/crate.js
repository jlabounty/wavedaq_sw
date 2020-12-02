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

   // create 16 WDB
   CRATE.wdb = [];
   for (let i=0 ; i<16 ; i++) {
      CRATE.wdb[i] = new WDB();
      CRATE.wdb[i].slot = i;
   }
   CRATE.wdb[3].hvOn = true;

   // draw crate
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

function WDB() {
  this.slot = 0;
  this.status = 0;
  this.hvOn = false;
}

function Crate(div) { // constructor
   this.canvas = document.createElement("canvas");
   div.appendChild(this.canvas);
}

Crate.prototype.resize = function (width, height) {
   this.canvas.width = width;
   this.canvas.height = width / 1000 * 270;
   this.draw();
}

Crate.prototype.draw = function () {
   let ctx = this.canvas.getContext("2d");

   // scale canvas such that a 1000x270 px rectangle fills the whole window
   ctx.scale(this.canvas.width / 1000, this.canvas.width / 1000);

   ctx.fillStyle = "#E0E0E0";
   ctx.fillRect(0, 0, 1000, 270);
   ctx.fillStyle = "#808080";
   ctx.fillRect(60, 5, 880, 260);

   // handles
   ctx.fillStyle = "#A0A0A0";
   ctx.fillRect(15, 35, 30, 200);
   ctx.fillRect(955, 35, 30, 200);

   // CMB
   ctx.save();
   ctx.translate(807.5, 7.5);
   ctx.fillStyle = "#E0E0E0";
   ctx.fillRect(0, 0, 130, 255);

   ctx.textAlign = "center";
   ctx.textBaseline = "middle";
   ctx.fillStyle = "#000000";
   ctx.font = "14px Sans-Serif"
   ctx.fillText("MSCBXXX", 65, 10);

   ctx.fillStyle = "#A0A0A0";
   ctx.fillRect(45, 18.5, 30, 6);
   ctx.fillStyle = "#000000";
   ctx.font = "10px Sans-Serif"
   ctx.fillText("PSI", 60, 22);

   ctx.font = "10px Sans-Serif"
   ctx.fillText("CMB", 80, 247);

   // screws
   ctx.fillStyle = "#928775";
   ctx.beginPath();
   ctx.arc(12, 28, 5, 0, 2*Math.PI);
   ctx.fill();
   ctx.fillStyle = "#D3D5C5";
   ctx.beginPath();
   ctx.arc(12, 28, 2, 0, 2*Math.PI);
   ctx.fill();

   ctx.fillStyle = "#928775";
   ctx.beginPath();
   ctx.arc(76, 162, 5, 0, 2*Math.PI);
   ctx.fill();
   ctx.fillStyle = "#D3D5C5";
   ctx.beginPath();
   ctx.arc(76, 162, 2, 0, 2*Math.PI);
   ctx.fill();

   ctx.fillStyle = "#202020";
   ctx.fillRect(50, 30, 60, 7);
   ctx.fillRect(50, 45, 60, 7);
   ctx.fillRect(50, 60, 60, 7);
   ctx.fillRect(50, 75, 60, 7);

   ctx.fillRect(50, 200, 60, 7);
   ctx.fillRect(50, 215, 60, 7);
   ctx.fillRect(50, 230, 60, 7);

   // ethernet port
   ctx.fillStyle = "#202020";
   ctx.fillRect(8, 45, 34, 38);

   // display box
   ctx.fillStyle = "#404040";
   ctx.fillRect(20, 105, 90, 20);

   // MSCB port
   ctx.fillStyle = "#202020";
   ctx.fillRect(10, 158, 20, 42);
   ctx.fillStyle = "#D1AE70";
   for (let i=0 ; i<5 ; i++) {
      ctx.beginPath();
      ctx.arc(16, 165+i*7, 1, 0, 2*Math.PI);
      ctx.fill();
      ctx.beginPath();
      ctx.arc(24, 165+i*7, 1, 0, 2*Math.PI);
      ctx.fill();
   }

   // buttons
   ctx.fillStyle = "#505050";
   ctx.beginPath();
   ctx.arc(58, 148, 8, 0, 2*Math.PI);
   ctx.fill();
   ctx.beginPath();
   ctx.arc(95, 148, 8, 0, 2*Math.PI);
   ctx.fill();
   ctx.beginPath();
   ctx.arc(58, 180, 8, 0, 2*Math.PI);
   ctx.fill();
   ctx.beginPath();
   ctx.arc(95, 180, 8, 0, 2*Math.PI);
   ctx.fill();

   ctx.textAlign = "center";
   ctx.textBaseline = "middle";
   ctx.font = "6px Sans-Serif"
   ctx.fillStyle = "#000000";
   ctx.fillText("PREV", 58, 136);
   ctx.fillText("ON/+", 95, 136);
   ctx.fillText("NEXT", 58, 168);
   ctx.fillText("OFF/-", 95, 168);
   ctx.fillText("RS 485", 20, 152);

   // lower handle
   ctx.fillStyle = "#404040";
   ctx.fillRect(0, 212, 44, 44);
   ctx.fillStyle = "#A83737";
   ctx.fillRect(13, 212, 18, 10);
   ctx.fillStyle = "#A39C8D";
   ctx.fillRect(0, 222, 44, 6);

   // text
   ctx.fillStyle = "#EF1C1E";
   ctx.font = "18px Courier New"
   ctx.fillText("***OK***", 65, 115);

   // LED
   ctx.fillStyle = "#60D838";
   ctx.beginPath();
   ctx.arc(62, 98, 4, 0, 2*Math.PI);
   ctx.fill();
   ctx.font = "6px Sans-Serif"
   ctx.fillStyle = "#000000";
   ctx.fillText("POWER ON", 62, 89);

   ctx.fillStyle = "#60D838";
   ctx.beginPath();
   ctx.arc(36, 162, 4, 0, 2*Math.PI);
   ctx.fill();
   ctx.beginPath();
   ctx.arc(36, 179, 4, 0, 2*Math.PI);
   ctx.fill();
   ctx.fillStyle = "#57241A";
   ctx.beginPath();
   ctx.arc(36, 196, 4, 0, 2*Math.PI);
   ctx.fill();

   ctx.restore();

   // WDB
   for (let slot=0 ; slot<16 ; slot++) {
      ctx.save();

      if (slot < 8)
         ctx.translate(62.5+slot*41.4, 7.5);
      else
         ctx.translate(62.5+(slot+2)*41.4, 7.5);

      ctx.fillStyle = "#2D674A";
      ctx.fillRect(0, 0, 40, 255);

      ctx.textAlign = "center";
      ctx.textBaseline = "middle";
      ctx.font = "5px Sans-Serif"
      ctx.fillStyle = "#B5CFBB";
      ctx.fillText("WaveDREAM2", 20, 10);

      // screw
      ctx.fillStyle = "#928775";
      ctx.beginPath();
      ctx.arc(12, 28, 5, 0, 2*Math.PI);
      ctx.fill();
      ctx.fillStyle = "#D3D5C5";
      ctx.beginPath();
      ctx.arc(12, 28, 2, 0, 2*Math.PI);
      ctx.fill();

      // logo
      ctx.fillStyle = "#5F826D";
      ctx.fillRect(3, 37, 20, 3);
      ctx.font = "7px Sans-Serif"
      ctx.fillStyle = "#B5CFBB";
      ctx.fillText("PSI", 13, 38.5);

      // holes
      ctx.fillStyle = "#202020";
      ctx.fillRect(26, 22, 11, 24);
      ctx.fillRect(26, 67, 11, 24);
      ctx.fillRect(26, 94, 11, 24);
      ctx.fillRect(26, 176, 11, 24);

      // input MCX
      ctx.fillStyle = "#BBA76E";
      ctx.fillRect(5, 45, 12, 167);
      for (let c=0 ; c<16 ; c++) {
         ctx.fillStyle = "#7E5A21";
         ctx.strokeStyle = "#E1C591";
         ctx.beginPath();
         ctx.arc(11, 50+c*10.4, 4, 0, 2*Math.PI);
         ctx.fill();
         ctx.stroke();

         ctx.fillStyle = "#7E5A21";
         ctx.strokeStyle = "#E1C591";
         ctx.beginPath();
         ctx.arc(11, 50+c*10.4, 1, 0, 2*Math.PI);
         ctx.fill();
         ctx.stroke();
      }
      ctx.font = "5px Sans-Serif"
      ctx.fillStyle = "#B5CFBB";
      ctx.fillText("CH0", 24, 50);
      ctx.fillText("CH15", 25, 207);

      // Status LED
      ctx.fillStyle = "#5EE5AA";
      ctx.beginPath();
      ctx.arc(30, 61, 4, 0, 2*Math.PI);
      ctx.fill();

      // HV LED
      if (this.wdb[slot].hvOn)
         ctx.fillStyle = "#FF2020";
      else
         ctx.fillStyle = "#57241A";
      ctx.beginPath();
      ctx.arc(30, 127, 4, 0, 2*Math.PI);
      ctx.fill();

      for (let c=0 ; c<3 ; c++) {
         ctx.fillStyle = "#7E5A21";
         ctx.strokeStyle = "#E1C591";
         ctx.beginPath();
         ctx.arc(32, 140+c*14, 4, 0, 2*Math.PI);
         ctx.fill();
         ctx.stroke();

         ctx.fillStyle = "#7E5A21";
         ctx.strokeStyle = "#E1C591";
         ctx.beginPath();
         ctx.arc(32, 140+c*14, 1, 0, 2*Math.PI);
         ctx.fill();
         ctx.stroke();
      }

      ctx.save();
      ctx.fillStyle = "#B5CFBB";
      ctx.rotate(Math.PI/2);
      ctx.fillText("RDY", 62, -22);
      ctx.fillText("HV ON", 126, -22);
      ctx.fillText("CK", 141, -22);
      ctx.fillText("TR", 154, -22);
      ctx.fillText("TMP", 168, -22);
      ctx.restore();

      // lower handle
      ctx.fillStyle = "#404040";
      ctx.fillRect(1, 212, 38, 44);
      ctx.fillStyle = "#A83737";
      ctx.fillRect(12, 212, 17, 10);
      ctx.fillStyle = "#A39C8D";
      ctx.fillRect(1, 222, 38, 6);

      // label
      ctx.fillStyle = "#FFFFFF";
      ctx.fillRect(4, 234, 33, 18);
      ctx.fillStyle = "#000000";
      ctx.font = "8px Sans-Serif"
      ctx.fillText("WDXXX", 20, 243);

      ctx.restore();
   }
}
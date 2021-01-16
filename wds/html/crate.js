//
//  crate.js
//  JavaScript Code for WaveDAQ crate display
//
//  Created by Stefan Ritt on 02/12/2020.
//

let CRATE; // global crate object

// Board vendor IDs
const BRD_VENDOR_ID_UNKNOWN = 0;
const BRD_VENDOR_ID_PSI     = 1;
const BRD_VENDOR_ID_PISA    = 2;

// Board type IDs
const BRD_TYPE_ID_NONE0     = 0;
const BRD_TYPE_ID_NONE1     = 1;
const BRD_TYPE_ID_WDB       = 2;
const BRD_TYPE_ID_DCB       = 3;
const BRD_TYPE_ID_TCB       = 4;
const BRD_TYPE_ID_BLANK     = 254;
const BRD_TYPE_ID_EMPTY     = 255;

// extend 2d canvas object
CanvasRenderingContext2D.prototype.drawLine = function (x1, y1, x2, y2) {
   this.beginPath();
   this.moveTo(x1, y1);
   this.lineTo(x2, y2);
   this.stroke();
};

function init() {
   // create Crate object
   CRATE = new Crate(document.getElementById("crate"));

   // obtain DCB address from URL
   let url = new URL(window.location.href);
   CRATE.dcbAddress = url.searchParams.get("adr");

   if (CRATE.dcbAddress === null) {
      dlgAlert("Missing parameter \"adr\" in URL");
      return;
   }

   // draw crate
   resize();

   // add resize event handler
   window.addEventListener("resize", resize);

   // mouse event handlers
   window.addEventListener("mousedown", CRATE.mouseEvent.bind(CRATE), true);
   window.addEventListener("mousemove", CRATE.mouseEvent.bind(CRATE), true);
   window.addEventListener("mouseup", CRATE.mouseEvent.bind(CRATE), true);
   window.addEventListener("dblclick", CRATE.mouseEvent.bind(CRATE), true);
   window.addEventListener("touchstart", CRATE.mouseEvent.bind(CRATE), true);
   window.addEventListener("touchmove", CRATE.mouseEvent.bind(CRATE), true);

   // schedule loadCrate()
   CRATE.timer = {};
   CRATE.timer.loadCrate = window.setTimeout(loadCrate, 10, true);

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

   // initialize member variables
   this.selectedWDB = undefined;
   this.selectedDCB = false;
   this.selectedTCB = false;

   this.wdb = [];
   this.dcb = {};
   this.tcb = {};
}

Crate.prototype.resize = function (width) {
   this.canvas.width = width;
   this.canvas.height = width / 1000 * 270;
   this.draw();
}

Crate.prototype.mouseEvent = function (e) {

   // fix buttons for IE
   if (!e.which && e.button) {
      if ((e.button & 1) > 0) e.which = 1;      // Left
      else if ((e.button & 4) > 0) e.which = 2; // Middle
      else if ((e.button & 2) > 0) e.which = 3; // Right
   }

   // set default cursor to be changed below
   let cursor = "default";

   if ((e.type === "mousemove" || e.type === "mousedown" || e.type === "dblclick")
      && e.target === this.canvas) {
      let x = e.clientX - this.canvas.offsetLeft;
      let y = e.clientY - this.canvas.offsetTop;
      let scale = this.canvas.width / 1000;

      if (y/scale > 7.5 && y/scale < 255+7.5) {
         let slot = Math.floor((x / scale - 62.5) / 41.4);
         if (slot < 0)
            slot = undefined;
         else if (slot < 8)
            slot += 0;
         else if (slot === 8)
            slot = 16;
         else if (slot === 9)
            slot = 17;
         else if (slot > 8 && slot < 18)
            slot -= 2;
         else
            slot = undefined;

         if (slot === 16 || slot === 17 ||
            (CRATE.crate !== undefined &&
               slot >= 0 && slot < 16 &&
               (CRATE.crate.slot[slot].type_id === BRD_TYPE_ID_WDB ||
                  CRATE.crate.slot[slot].type_id === BRD_TYPE_ID_BLANK))) {
            cursor = "pointer";
         }

         if (e.type === "dblclick" && slot < 16 &&
            CRATE.crate.slot[slot].type_id === BRD_TYPE_ID_WDB) {
            window.location.href = "osc.html?adr=" + CRATE.dcbAddress + ":" + slot;
         }

         if (e.type === "mousedown") {
            if (slot === 17) {
               CRATE.selectedWDB = undefined;
               CRATE.selectedDCB = false;
               CRATE.selectedTCB = true;
               document.getElementById('dlgInfoWDB').style.display = 'none';
               document.getElementById('dlgInfoDCB').style.display = 'none';
               document.getElementById('dlgInfoTCB').style.display = 'revert';
            } else if (slot === 16) {
               CRATE.selectedWDB = undefined;
               CRATE.selectedDCB = true;
               CRATE.selectedTCB = false;
               document.getElementById('dlgInfoWDB').style.display = 'none';
               document.getElementById('dlgInfoDCB').style.display = 'revert';
               document.getElementById('dlgInfoTCB').style.display = 'none';
            } else if (slot < 16) {
               if (CRATE.crate.slot[slot].type_id === BRD_TYPE_ID_WDB)
                  CRATE.selectedWDB = slot;
               else
                  CRATE.selectedWDB = undefined;
               CRATE.selectedDCB = false;
               CRATE.selectedTCB = false;
               if (CRATE.crate.slot[slot].type_id === BRD_TYPE_ID_WDB)
                  document.getElementById('dlgInfoWDB').style.display = 'revert';
               else
                  document.getElementById('dlgInfoWDB').style.display = 'none';
               document.getElementById('dlgInfoDCB').style.display = 'none';
               document.getElementById('dlgInfoTCB').style.display = 'none';
            }
            CRATE.draw();
            loadCrate();
         }
      }
   }

   document.getElementById('crate').style.cursor = cursor;
}

Crate.prototype.draw = function () {
   let ctx = this.canvas.getContext("2d");

   // scale canvas such that a 1000x270 px rectangle fills the whole window
   ctx.save();
   ctx.scale(this.canvas.width / 1000, this.canvas.width / 1000);

   ctx.fillStyle = "#E0E0E0";
   ctx.fillRect(0, 0, 1000, 270);
   ctx.fillStyle = "#808080";
   ctx.fillRect(60, 5, 880, 260);

   // handles
   ctx.fillStyle = "#A0A0A0";
   ctx.fillRect(15, 35, 30, 200);
   ctx.fillRect(955, 35, 30, 200);

   //---- draw CMB
   drawCMB(ctx);

   if (CRATE.crate === undefined) {
      ctx.restore();
      return;
   }

   //---- draw DCB
   ctx.save();
   ctx.translate(62.5 + 8 * 41.4, 7.5);
   drawDCB(ctx);
   ctx.restore();

   //---- draw slots
   for (let slot=0 ; slot<16 ; slot++) {
      if (CRATE.crate.slot !== undefined &&
          CRATE.crate.slot[slot].vendor_id === BRD_VENDOR_ID_PSI &&
          CRATE.crate.slot[slot].type_id === BRD_TYPE_ID_WDB) {
         ctx.save();
         if (slot < 8)
            ctx.translate(62.5 + slot * 41.4, 7.5);
         else
            ctx.translate(62.5 + (slot + 2) * 41.4, 7.5);
         drawWDB(ctx, slot);
         ctx.restore();
      } else if (CRATE.crate.slot !== undefined &&
                 CRATE.crate.slot[slot].vendor_id === BRD_TYPE_ID_BLANK &&
                 CRATE.crate.slot[slot].type_id === BRD_TYPE_ID_BLANK) {
         ctx.save();
         if (slot < 8)
            ctx.translate(62.5 + slot * 41.4, 7.5);
         else
            ctx.translate(62.5 + (slot + 2) * 41.4, 7.5);
         drawWDBEmpty(ctx, slot);
         ctx.restore();
      } else {
         ctx.save();
         if (slot < 8)
            ctx.translate(62.5 + slot * 41.4, 7.5);
         else
            ctx.translate(62.5 + (slot + 2) * 41.4, 7.5);
         drawEmptySlot(ctx, slot);
         ctx.restore();
      }
   }

   //---- draw TCB
   ctx.save();
   ctx.translate(62.5 + 9 * 41.4, 7.5);
   drawTCB(ctx, 17);
   ctx.restore();

   ctx.restore();
}

function drawCMB(ctx) {

   ctx.save();
   ctx.translate(807.5, 7.5);
   ctx.fillStyle = "#E0E0E0";
   ctx.fillRect(0, 0, 130, 255);

   if (CRATE.crate !== undefined) {
      ctx.textAlign = "center";
      ctx.textBaseline = "middle";
      ctx.fillStyle = "#000000";
      ctx.font = "14px Sans-Serif"
      ctx.fillText("MSCBXXX", 65, 10);
   }

   ctx.fillStyle = "#A0A0A0";
   ctx.fillRect(45, 18.5, 30, 6);
   ctx.fillStyle = "#000000";
   ctx.font = "10px Sans-Serif"
   ctx.fillText("PSI", 60, 22);

   ctx.font = "10px Sans-Serif"
   ctx.fillText("CMB", 80, 247);

   // screws
   ctx.fillStyle = "#928776";
   ctx.beginPath();
   ctx.arc(12, 28, 5, 0, 2*Math.PI);
   ctx.fill();
   ctx.fillStyle = "#D3D5C6";
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
}

function drawEmptySlot(ctx, slot) {
   ctx.fillStyle = "#808080";
   ctx.fillRect(0, 0, 40, 255);
   ctx.fillStyle = "#404040";
   ctx.fillRect(2, 2, 36, 251);

   ctx.textAlign = "center";
   ctx.textBaseline = "middle";
   ctx.font = "8px Sans-Serif"
   ctx.fillStyle = "#E0E0E0";
   ctx.fillText(slot, 20, 240);
}

function drawWDB(ctx, slot) {
   ctx.save();

   if (CRATE.selectedWDB === slot)
      ctx.fillStyle = "#4DA76A";
   else
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
   ctx.arc(12, 28, 5, 0, 2 * Math.PI);
   ctx.fill();
   ctx.fillStyle = "#D3D5C5";
   ctx.beginPath();
   ctx.arc(12, 28, 2, 0, 2 * Math.PI);
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
   for (let c = 0; c < 16; c++) {
      ctx.fillStyle = "#7E5A21";
      ctx.strokeStyle = "#E1C591";
      ctx.beginPath();
      ctx.arc(11, 50 + c * 10.4, 4, 0, 2 * Math.PI);
      ctx.fill();
      ctx.stroke();

      ctx.fillStyle = "#7E5A21";
      ctx.strokeStyle = "#E1C591";
      ctx.beginPath();
      ctx.arc(11, 50 + c * 10.4, 1, 0, 2 * Math.PI);
      ctx.fill();
      ctx.stroke();
   }

   // Status LED
   ctx.fillStyle = "#5EE5AA";
   ctx.beginPath();
   ctx.arc(30, 61, 4, 0, 2 * Math.PI);
   ctx.fill();

   // HV LED
   if (CRATE.crate.slot !== undefined && CRATE.crate.slot[slot].hv_on)
      ctx.fillStyle = "#FF2020";
   else
      ctx.fillStyle = "#57241A";
   ctx.beginPath();
   ctx.arc(30, 127, 4, 0, 2 * Math.PI);
   ctx.fill();

   for (let c = 0; c < 3; c++) {
      ctx.fillStyle = "#7E5A21";
      ctx.strokeStyle = "#E1C591";
      ctx.beginPath();
      ctx.arc(32, 140 + c * 14, 4, 0, 2 * Math.PI);
      ctx.fill();
      ctx.stroke();

      ctx.fillStyle = "#7E5A21";
      ctx.strokeStyle = "#E1C591";
      ctx.beginPath();
      ctx.arc(32, 140 + c * 14, 1, 0, 2 * Math.PI);
      ctx.fill();
      ctx.stroke();
   }

   ctx.save();
   ctx.fillStyle = "#B5CFBB";
   ctx.font = "4px Sans-Serif";
   ctx.rotate(Math.PI / 2);
   ctx.fillText("RDY", 61, -22);
   ctx.fillText("HV-ON", 126, -22);
   ctx.fillText("RX", 140, -22);
   ctx.fillText("TX", 154, -22);
   ctx.fillText("TEMP", 168, -22);
   for (let c=0 ; c<16 ; c++)
      ctx.fillText("CH"+c, 50+c*10.45, -2);
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
   if (CRATE.crate.slot !== undefined)
      ctx.fillText("WD" + CRATE.crate.slot[slot].serial, 20, 243);
   else
      ctx.fillText("WDXXX", 20, 243);

   ctx.restore();
}

function drawWDBEmpty(ctx, slot) {
   ctx.save();

   ctx.fillStyle = "#C0C0C0";
   ctx.fillRect(0, 0, 40, 255);

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
   ctx.textAlign = "center";
   ctx.textBaseline = "middle";
   ctx.font = "8px Sans-Serif"
   ctx.fillText("WDXXX", 20, 243);

   ctx.restore();
}

function drawDCB(ctx, slot) {
   ctx.save();

   if (CRATE.selectedDCB)
      ctx.fillStyle = "#4DA76A";
   else
      ctx.fillStyle = "#2D674A";
   ctx.fillRect(0, 0, 40, 255);

   ctx.textAlign = "center";
   ctx.textBaseline = "middle";
   ctx.font = "8px Sans-Serif"
   ctx.fillStyle = "#B5CFBB";
   ctx.fillText("DCB", 20, 10);

   // screw
   ctx.fillStyle = "#928775";
   ctx.beginPath();
   ctx.arc(12, 24, 5, 0, 2 * Math.PI);
   ctx.fill();
   ctx.fillStyle = "#D3D5C5";
   ctx.beginPath();
   ctx.arc(12, 24, 2, 0, 2 * Math.PI);
   ctx.fill();

   // Logo
   ctx.fillStyle = "#5F826D";
   ctx.fillRect(12, 37, 20, 3);
   ctx.font = "7px Sans-Serif"
   ctx.fillStyle = "#B5CFBB";
   ctx.fillText("PSI", 22, 38.5);

   // USB
   ctx.fillStyle = "#999A97";
   ctx.fillRect(8, 44, 29, 15);
   ctx.fillStyle = "#202020";
   ctx.fillRect(10, 46, 25, 11);
   ctx.fillStyle = "#5E6467";
   ctx.fillRect(12, 48, 21, 3);

   ctx.fillStyle = "#999A97";
   ctx.fillRect(8, 63, 7, 15);
   ctx.fillStyle = "#202020";
   ctx.fillRect(9, 64, 5, 13);
   ctx.fillStyle = "#5E6467";
   ctx.fillRect(11, 65, 2, 11);

   // SFP
   ctx.fillStyle = "#999A97";
   ctx.fillRect(8, 84, 19, 29);
   ctx.fillStyle = "#202020";
   ctx.fillRect(9, 85, 17, 27);
   ctx.fillStyle = "#999A97";
   ctx.fillRect(8, 113, 19, 29);
   ctx.fillStyle = "#202020";
   ctx.fillRect(9, 114, 17, 27);

   // Trigger
   ctx.fillStyle = "#999A97";
   ctx.fillRect(4, 152, 19, 22);
   ctx.fillStyle = "#202020";
   ctx.fillRect(5, 153, 17, 20);

   // Status LED
   ctx.fillStyle = "#5EE5AA";
   ctx.beginPath();
   ctx.arc(28, 71, 4, 0, 2 * Math.PI);
   ctx.fill();

   // MCX
   ctx.fillStyle = "#7E5A21";
   ctx.strokeStyle = "#E1C591";
   ctx.beginPath();
   ctx.arc(13, 190, 4, 0, 2 * Math.PI);
   ctx.fill();
   ctx.stroke();
   ctx.fillStyle = "#7E5A21";
   ctx.strokeStyle = "#E1C591";
   ctx.beginPath();
   ctx.arc(13, 190, 1, 0, 2 * Math.PI);
   ctx.fill();
   ctx.stroke();

   ctx.fillStyle = "#7E5A21";
   ctx.strokeStyle = "#E1C591";
   ctx.beginPath();
   ctx.arc(24, 190, 4, 0, 2 * Math.PI);
   ctx.fill();
   ctx.stroke();
   ctx.fillStyle = "#7E5A21";
   ctx.strokeStyle = "#E1C591";
   ctx.beginPath();
   ctx.arc(24, 190, 1, 0, 2 * Math.PI);
   ctx.fill();
   ctx.stroke();

   ctx.fillStyle = "#7E5A21";
   ctx.strokeStyle = "#E1C591";
   ctx.beginPath();
   ctx.arc(13, 205, 4, 0, 2 * Math.PI);
   ctx.fill();
   ctx.stroke();
   ctx.fillStyle = "#7E5A21";
   ctx.strokeStyle = "#E1C591";
   ctx.beginPath();
   ctx.arc(13, 205, 1, 0, 2 * Math.PI);
   ctx.fill();
   ctx.stroke();

   ctx.fillStyle = "#7E5A21";
   ctx.strokeStyle = "#E1C591";
   ctx.beginPath();
   ctx.arc(24, 205, 4, 0, 2 * Math.PI);
   ctx.fill();
   ctx.stroke();
   ctx.fillStyle = "#7E5A21";
   ctx.strokeStyle = "#E1C591";
   ctx.beginPath();
   ctx.arc(24, 205, 1, 0, 2 * Math.PI);
   ctx.fill();
   ctx.stroke();

   // Labels
   ctx.fillStyle = "#B5CFBB";
   ctx.font = "4px Sans-Serif";
   ctx.fillText("RDY", 28, 64);

   ctx.save();
   ctx.rotate(Math.PI / 2);
   ctx.fillText("USB", 51, -4);
   ctx.fillText("USB", 71, -18);
   ctx.fillText("CONFIG", 71, -4);
   ctx.fillText("ETHERNET", 100, -4);
   ctx.fillText("SFP+", 128, -4);
   ctx.fillText("TRIGGER", 163, -28);
   ctx.fillText("CLOCK", 190, -4);
   ctx.fillText("TRG", 205, -4);
   ctx.restore();

   ctx.fillText("IN", 13, 180);
   ctx.fillText("OUT", 24, 180);

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
   ctx.font = "8px Sans-Serif";
   if (CRATE.crate.DCB.name !== undefined)
      ctx.fillText(CRATE.crate.DCB.name, 20, 243);
   else
      ctx.fillText("DCBXX", 20, 243);

   ctx.restore();
}

function drawTCB(ctx, slot) {
   ctx.save();

   if (CRATE.selectedTCB)
      ctx.fillStyle = "#3F78A9";
   else
      ctx.fillStyle = "#1F5889";
   ctx.fillRect(0, 0, 40, 255);

   ctx.textAlign = "center";
   ctx.textBaseline = "middle";
   ctx.font = "8px Sans-Serif"
   ctx.fillStyle = "#B5CFBB";
   ctx.fillText("TCB", 20, 10);

   // screw
   ctx.fillStyle = "#928775";
   ctx.beginPath();
   ctx.arc(12, 24, 5, 0, 2 * Math.PI);
   ctx.fill();
   ctx.fillStyle = "#D3D5C5";
   ctx.beginPath();
   ctx.arc(12, 24, 2, 0, 2 * Math.PI);
   ctx.fill();

   // Logo
   ctx.font = "5px Sans-Serif"
   ctx.fillStyle = "#B5CFBB";
   ctx.fillText("INFN", 27, 25);

   // Trigger
   ctx.fillStyle = "#999A97";
   ctx.fillRect(3, 94, 19, 22);
   ctx.fillStyle = "#202020";
   ctx.fillRect(4, 95, 17, 20);

   ctx.fillStyle = "#999A97";
   ctx.fillRect(3, 126, 19, 22);
   ctx.fillStyle = "#202020";
   ctx.fillRect(4, 127, 17, 20);

   ctx.fillStyle = "#999A97";
   ctx.fillRect(3, 157, 19, 22);
   ctx.fillStyle = "#202020";
   ctx.fillRect(4, 158, 17, 20);

   ctx.fillStyle = "#999A97";
   ctx.fillRect(3, 188, 19, 22);
   ctx.fillStyle = "#202020";
   ctx.fillRect(4, 189, 17, 20);

   // LEDs
   ctx.fillStyle = "#4E080B";
   ctx.beginPath();
   ctx.arc(14, 55, 4, 0, 2 * Math.PI);
   ctx.fill();
   ctx.beginPath();
   ctx.arc(14, 67, 4, 0, 2 * Math.PI);
   ctx.fill();
   ctx.beginPath();
   ctx.arc(14, 79, 4, 0, 2 * Math.PI);
   ctx.fill();
   ctx.fillStyle = "#063427";
   ctx.beginPath();
   ctx.arc(25, 55, 4, 0, 2 * Math.PI);
   ctx.fill();
   ctx.beginPath();
   ctx.arc(25, 67, 4, 0, 2 * Math.PI);
   ctx.fill();
   ctx.beginPath();
   ctx.arc(25, 79, 4, 0, 2 * Math.PI);
   ctx.fill();

   // Labels
   ctx.fillStyle = "#B5CFBB";
   ctx.font = "3px Sans-Serif";
   ctx.fillText("LED1", 5, 55);
   ctx.fillText("LED0", 35, 55);
   ctx.fillText("LOCK", 5, 67);
   ctx.fillText("DTACK", 35, 67);
   ctx.fillText("BUSY", 5, 79);
   ctx.fillText("RUN", 35, 79);

   ctx.save();
   ctx.font = "6px Sans-Serif";
   ctx.rotate(Math.PI / 2);
   ctx.fillText("TRG0", 105, -29);
   ctx.fillText("TRG1", 137, -29);
   ctx.fillText("TRG2", 168, -29);
   ctx.fillText("TRG3", 200, -29);
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
   ctx.fillText("TCBXX", 20, 243);

   ctx.restore();
}

function loadCrate() {
   if (CRATE.timer.loadCrate !== undefined)
      window.clearTimeout(CRATE.timer.loadCrate);

   // send AJAX request
   CRATE.req = new XMLHttpRequest();
   CRATE.req.onreadystatechange = receiveCrate;
   CRATE.req.open("GET", "crate?adr=" + CRATE.dcbAddress +
         "&r=" + Math.random(), true); // avoid cached results

   try {
      CRATE.req.send();
   } catch (e) {
      connectionBroken();
   }
}

function receiveCrate() {
   if (CRATE.req.readyState === 4 && CRATE.req.status === 200) {
      CRATE.crate = JSON.parse(CRATE.req.responseText);
      CRATE.draw();
      CRATE.connected = true;

      let dcb = CRATE.crate.DCB;
      setItem("infoDCBName", dcb.name);
      setItem("infoDCBRevision", dcb.revision);
      setItem("infoDCBFwRevision", dcb.fwRevision);
      setItem("infoDCBSwBuild", dcb.swBuild);
      setItem("infoDCBTemp", dcb.temperature);
      setItem("infoDCBVDD", dcb.vdd);
      setItem("infoDCBCurrent", dcb.current);
      setItem("infoDCBV5_0", dcb.v5_0);
      setItem("infoDCBV3_3", dcb.v3_3);
      setItem("infoDCBV2_5", dcb.v2_5);

      if (CRATE.selectedWDB !== undefined) {
         let wdb = CRATE.crate.slot[CRATE.selectedWDB];

         setItem("infoWDBName", wdb.name);
         setItem("infoWDBCrateSlotID", wdb.crateId + " / " +wdb.slotId);
         setItem("infoWDBRevision", wdb.revision);
         setItem("infoWDBFwRevision", wdb.fwRevision);
         setItem("infoWDBFwBuild", wdb.fwBuild);
         setItem("infoWDBSwRevision", wdb.swRevision);
         setItem("infoWDBSwBuild", wdb.swBuild);
         setItem("infoWDBHVVersion", wdb.hvBoardPlugged ? wdb.hvVersion : "none");
         setItem("infoWDBHVBaseVoltage", wdb.hvBaseVoltage);
         setItem("infoWDBTemp", wdb.temperature);
         setItem("infoWDB1WireTemp", wdb.temperature1Wire[0] + " / " +
            wdb.temperature1Wire[1] + " / " +
            wdb.temperature1Wire[2] + " / " +
            wdb.temperature1Wire[3]);
         setItem("infoWDBTemp", wdb.temperature);

         let s = "";
         for (i = 8; i >= 0; i--) {
            if ((wdb.pllLck & (1 << 8)) > 0)
               s += "1";
            else
               s += "0";
         }
         setItem("infoWDBPLL", s);

         setItem("infoWDBBusy", wdb.drsctrlBusy + " / " + wdb.sysBusy);
         setItem("infoWDBTRGParityErrors", wdb.triggerBusParityErrorCount);

         s = "";
         for (i = 0; i < 16; i++) {
            if ((wdb.compChannelStatus & (1 << 8)) > 0)
               s += "1";
            else
               s += "0";
            if (i % 4 === 3)
               s += " ";
         }
         setItem("infoWDBCompStatus", s);
      }

      CRATE.timer.loadCrate = window.setTimeout(loadCrate, 1000);
   } else if (CRATE.req.readyState === 4 && CRATE.req.status === 0) {
      connectionBroken();
   }
}

function setItem(id, str)
{
   let i = document.getElementById(id);
   if (typeof str !== 'string')
      str = str.toString();
   if (i !== undefined)
      if (i.innerHTML !== str)
         i.innerHTML = str;
}

function connectionBroken() {
   if (CRATE.connected) {
      CRATE.dlgReconnect = dlgMessage("Error", "Connection to server broken.<br>Trying to reconnect ..." +
         "<br /><br /><br /><img alt=\"Please wait\" src=\"spinning-wheel-wds.gif\">", true, true);
      let b = document.getElementById("dlgMessageButton");
      b.innerHTML = "Cancel";
      CRATE.connected = false;
      CRATE.timer.reconnect = window.setTimeout(reconnect, 1000);
   }

   if (CRATE.timer.loadCrate !== undefined)
      clearTimeout(CRATE.timer.loadCrate);
}

function reconnect() {
   if (CRATE.dlgReconnect.parentElement === undefined)
      return;
   let req = new XMLHttpRequest();
   req.onreadystatechange = function () {
      if (req.readyState === 4 && req.status === 200) {
         // reload page
         location.reload();
      } else if (req.readyState === 4) {
         CRATE.timer.reconnect = window.setTimeout(reconnect, 1000);
      }
   };

   req.open("GET", "build", true);
   req.send();
}

function DCBmark() {
   if (CRATE.markDCB) {
      CRATE.markDCB = false;
      document.getElementById('btnDCBMark').innerText = 'Mark';
   } else {
      CRATE.markDCB = true;
      document.getElementById('btnDCBMark').innerText = 'Unmark';
   }

   let req = new XMLHttpRequest();
   req.open("GET", "mark?adr=" + CRATE.dcbAddress + "&fl=" + (CRATE.markDCB ? "1" : "0"), true);
   req.send();

}

let progress;

function updateProgress() {
   progress += 0.1;
   d = document.getElementById("progressWait");
   d.set(progress / 15);
   if (progress >= 15) {
      dlgHide("dlgWait");
   } else
      window.setTimeout(updateProgress, 100);
}

function WDBrebootQuery() {
   dlgConfirm("Are you sure?", WDBreboot);
}

function WDBreboot(flag) {
   if (flag) {
      progress = 0;
      dlgShow("dlgWait", true);
      window.setTimeout(updateProgress, 100);

      // kill update times
      if (CRATE.timer.loadCrate !== undefined)
         window.clearTimeout(CRATE.timer.loadCrate);

      // send AJAX request
      let req = new XMLHttpRequest();
      req.onreadystatechange = function () {
         if (req.readyState === 4 && req.status === 200) {
            dlgHide("dlgWait");
            loadCrate(); // restart crate-scan
         } else if (req.readyState === 4 && req.status === 0) {
            connectionBroken();
         }
      };

      req.open("PUT", "reboot/" + CRATE.dcbAddress + ":" + CRATE.selectedWDB, true); // avoid cached results

      try {
         req.send();
      } catch (e) {
         connectionBroken();
      }
   }
}

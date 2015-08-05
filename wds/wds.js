//
//  wds.js
//  WaveDAQ Server Application JavaScript Code
//
//  Created by Stefan Ritt on 5/8/15.
//

const CONTROLS_WIDTH = 200;

function init() {
   window.requestAnimationFrame(draw);
}

function draw() {
   var canvas = document.getElementById("scope");
   var ctx = canvas.getContext("2d");
   
   canvas.width = window.innerWidth - CONTROLS_WIDTH;
   canvas.height = window.innerHeight;
   
   var p = new Path2D();
   
   p.moveTo(0, 0);
   p.lineTo(canvas.width, canvas.height);
   
   ctx.stroke(p);
   
   window.requestAnimationFrame(draw);
}
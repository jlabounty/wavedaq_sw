//
//  buttons.js
//  Custom Buttons used by controls.js
//
//  Created by Stefan Ritt on 10/4/18.
//

function ButtonDrawUp(cvs)
{
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

function ButtonDrawDown(cvs)
{
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

function ButtonDrawLeft(cvs)
{
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

function ButtonDrawRight(cvs)
{
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

function ButtonDrawPlus(cvs)
{
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

function ButtonDrawMinus(cvs)
{
   cvs.width = 36;
   cvs.height = 36;
   ctx = cvs.getContext("2d");
   ctx.fillStyle = "#E0E0E0";
   ctx.fillRect(0, 0, 36, 36);
   ctx.strokeStyle = "#FF0000";
   ctx.lineWidth = 3;
   ctx.drawLine(7, 18, 29, 18);
}

function ButtonDrawVColl(cvs)
{
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

function ButtonDrawVExp(cvs)
{
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

function ButtonDrawEdgeUp(cvs)
{
   cvs.width = 36;
   cvs.height = 36;
   ctx = cvs.getContext("2d");
   ctx.fillStyle = "#E0E0E0";
   ctx.fillRect(0, 0, 36, 36);
   ctx.strokeStyle = "#808080";
   ctx.fillStyle = "#808080";
   ctx.lineWidth = 2;
   ctx.beginPath();
   ctx.moveTo(3, 31);
   ctx.lineTo(13, 31);
   ctx.lineTo(23, 5);
   ctx.lineTo(33, 5);
   ctx.stroke();
   ctx.beginPath();
   ctx.moveTo(20, 12);
   ctx.lineTo(22, 26);
   ctx.lineTo(10, 22);
   ctx.closePath();
   ctx.fill();
}

function ButtonDrawEdgeDown(cvs)
{
   cvs.width = 36;
   cvs.height = 36;
   ctx = cvs.getContext("2d");
   ctx.fillStyle = "#E0E0E0";
   ctx.fillRect(0, 0, 36, 36);
   ctx.strokeStyle = "#808080";
   ctx.fillStyle = "#808080";
   ctx.lineWidth = 2;
   ctx.beginPath();
   ctx.moveTo(3, 5);
   ctx.lineTo(13, 5);
   ctx.lineTo(23, 31);
   ctx.lineTo(33, 31);
   ctx.stroke();
   ctx.beginPath();
   ctx.moveTo(20, 24);
   ctx.lineTo(22, 10);
   ctx.lineTo(10, 14);
   ctx.closePath();
   ctx.fill();
}

function ButtonDrawEdgeLead(cvs)
{
   cvs.width = 36;
   cvs.height = 36;
   ctx = cvs.getContext("2d");
   ctx.fillStyle = "#E0E0E0";
   ctx.fillRect(0, 0, 36, 36);
   ctx.strokeStyle = "#808080";
   ctx.fillStyle = "#808080";
   ctx.lineWidth = 2;
   ctx.beginPath();
   ctx.moveTo(3, 18);
   ctx.lineTo(10, 18);
   ctx.lineTo(10, 5);
   ctx.lineTo(26, 5);
   ctx.lineTo(26, 18);
   ctx.lineTo(33, 18);
   ctx.stroke();
   ctx.beginPath();
   ctx.lineTo(10, 18);
   ctx.lineTo(10, 31);
   ctx.lineTo(26, 31);
   ctx.lineTo(26, 18);
   ctx.stroke();
   ctx.beginPath();
   ctx.moveTo(13, 18);
   ctx.lineTo(20, 11);
   ctx.lineTo(20, 25);
   ctx.lineTo(13, 18);
   ctx.closePath();
   ctx.fill();
}

function ButtonDrawEdgeTrail(cvs)
{
   cvs.width = 36;
   cvs.height = 36;
   ctx = cvs.getContext("2d");
   ctx.fillStyle = "#E0E0E0";
   ctx.fillRect(0, 0, 36, 36);
   ctx.strokeStyle = "#808080";
   ctx.fillStyle = "#808080";
   ctx.lineWidth = 2;
   ctx.beginPath();
   ctx.moveTo(3, 18);
   ctx.lineTo(10, 18);
   ctx.lineTo(10, 5);
   ctx.lineTo(26, 5);
   ctx.lineTo(26, 18);
   ctx.lineTo(33, 18);
   ctx.stroke();
   ctx.beginPath();
   ctx.lineTo(10, 18);
   ctx.lineTo(10, 31);
   ctx.lineTo(26, 31);
   ctx.lineTo(26, 18);
   ctx.stroke();
   ctx.beginPath();
   ctx.moveTo(23, 18);
   ctx.lineTo(16, 11);
   ctx.lineTo(16, 25);
   ctx.lineTo(23, 18);
   ctx.closePath();
   ctx.fill();
}


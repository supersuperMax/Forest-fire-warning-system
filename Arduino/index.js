"use strict";
const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');
const port = new SerialPort('COM3', { baudRate: 9600 });
const http = require("http");
const parser = port.pipe(new Readline({ delimiter: '\n' }));// Read the port data
port.on("open", () => {
  console.log('serial port open');
});
parser.on('data', data =>{
  console.log('got word from arduino:', data);
var req = http.request({
    hostname: '34.91.158.95',
    method: 'POST',
    port: 3000,
    path: '/sensor',
    headers: {
    'Content-Type': 'application/json',
    'Content-Length': data.length
  }
}, function(res){
	console.log("response =" + res.statusCode);
});
req.on('error', function(err) {
	console.log("error =" + err);
});
req.write(data);
req.end();
});
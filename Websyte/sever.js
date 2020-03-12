const express = require('express');
const fs = require('fs');
const app = express();
var path = require("path");

app.get('/', function (req, res) { 
    res.sendFile(path.join(__dirname + '/map.html'));
    //res.sendFile(path.join(__dirname + '/map_code.js'));//
} );

app.get('/sensor', function (req, res) { 
    res.sendFile(path.join(__dirname + '/sensor.json'));
} );

app.post('/sensor', function (req, res) {
    fs.writeFile('sensor.json', data, (err) => {
    if(err) res.send(500);
      else res.send(200);
} );
} );

app.listen(3000);

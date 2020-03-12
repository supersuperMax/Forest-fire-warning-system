const express = require('express');
const fs = require('fs');
const app = express();
var path = require("path");

app.get('/', function (req, res) { 
    res.sendFile(path.join(__dirname + '/map.html'));
    res.sendFile(path.join(__dirname + '/map_code.js'));//
} );

app.get('/sensor', function (req, res) { 
    res.sendFile(path.join(__dirname + '/sensor.json'));
} );

app.listen(3000);

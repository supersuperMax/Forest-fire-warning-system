const express = require('express');
const fs = require('fs');
const app = express();
var path = require("path");
var bodyParser = require('body-parser');

app.use(bodyParser.json());

app.get('/', function (req, res) { 
    res.sendFile(path.join(__dirname + '/map.html'));
    //res.sendFile(path.join(__dirname + '/map_code.js'));//
} );

app.get('/sensor', function (req, res) { 
    res.sendFile(path.join(__dirname + '/sensor.json'));
} );

app.post('/sensor', function (req, res) {
	
	console.log('receiving data ...');
    console.log('body is ',req.body);

    fs.writeFile('sensor.json', req.body, (err) => {
    if(err) res.sendStatus(500);
      else res.sendStatus(200);
} );
} );

app.listen(3000);

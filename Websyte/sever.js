const express = require('express');
const fs = require('fs');
const app = express();
const myEnv = require('./prod-env.json')
var path = require("path");
var bodyParser = require('body-parser');
var gulp = require('gulp');
var replace = require('gulp-replace');

  gulp.src([__dirname + '/map.html'])
    .pipe(replace('GOOGLE_API_KEY', myEnv.GOOGLE_API_KEY))
    .pipe(gulp.dest(__dirname + '/build/'));

gulp.src([__dirname + '/sensor.json'])
    .pipe(gulp.dest(__dirname + '/build/'));

app.use(bodyParser.json());

app.get('/', function (req, res) { 
    res.sendFile(path.join(__dirname + '/build/map.html'));
    //res.sendFile(path.join(__dirname + '/map_code.js'));//
} );

app.get('/sensor', function (req, res) { 
    res.sendFile(path.join(__dirname + '/build/sensor.json'));
} );

app.post('/sensor', function (req, res) {
	
	console.log('receiving data ...');
    console.log('body is ',req.body);

    fs.writeFile('build/sensor.json', JSON.stringify(req.body), (err) => {
    if(err) res.sendStatus(500);
      else res.sendStatus(200);
} );
} );

app.listen(3000);

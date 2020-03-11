const express = require('express');
const fs = require('fs');
const app = express();
var path = require("path");

app.get('/', function (req, res) { 
    res.sendFile(path.join(__dirname + '/map.html'));
} );
app.listen(3000);

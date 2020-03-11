const express = require('express');
const fs = require('fs');
const app = express();
app.get('/', function (req, res) { 
    res.sendFile('map.html');
} );
app.listen(3000);

const express = require('express');
const fs = require('fs');
const app = express();
app.get('/', function (req, res) { 
  
fs.readFile('map.html', (err, data) => {
     if(err) throw err;
     res.set('Content-Type', 'text/html; charset=utf-8');
     res.set('Access-Control-Allow-Origin', '*');
     res.send(data);
});
} );
app.listen(3000);

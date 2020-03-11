const express = require('express');
const fs = require('fs');
const app = express();
app.get('/', function (req, res) { 
  
fs.readFile('map.html', (err, data) => {
     if(err) throw err;
     res.send(data);
});
} );
app.listen(3000);

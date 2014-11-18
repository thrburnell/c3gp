var express = require('express');
var directions = require('../directions/directions')
var router = express.Router();
var exec = require('child_process').exec;

/* GET home page. */
router.get('/', function(req, res) {
  res.render('index', { title: 'Express' });
});

router.get('/route', function(req, res) {
  res.send("Need POST request");
});

router.get('/cpp', function(req, res) {
  res.send("Need POST request");
});

router.post('/cpp', function(req, res) {

  //TODO: written this for when the JSON parsing C++ is ready
  var placeholderData = {};
  placeholderData.origin = {"lat":51.50055501480524,"lng":-0.17445087432861328};
  placeholderData.destination = {"lat":51.50055501480524,"lng":-0.17445087432861328};
  placeholderData.waypoints = [];
  placeholderData.waypoints.push({"lat":51.497843351035144,"lng":-0.1702022552285598});
  placeholderData.waypoints.push({"lat":51.497629616981214,"lng":-0.17346382139066918});
  placeholderData.waypoints.push({"lat":51.49841775633878,"lng":-0.17533063886503442});
  placeholderData.waypoints.push({"lat":51.497910142721445,"lng":-0.17936468122343285});
  placeholderData.waypoints.push({"lat":51.495759401256,"lng":-0.1717901229653762});
  placeholderData.waypoints.push({"lat":51.49644070301275,"lng":-0.17026662824491723});
  var dataInAsJson = JSON.stringify(placeholderData);

  //TODO: Change this once the final artifact place is known
  //TODO: Security flaw: Bash injection. We have to use files I guess?
  var cppCommand = 'echo \'' + dataInAsJson + '\' | ./algorithm/build/tsp.bin';

  var child = exec(cppCommand, function (error, stdout, stderr) {
    if (error !== null) {
      console.log('exec error: ' + error);
    }
    res.send(stdout);
  });

});

router.get('/cpptest', function(req, res) {
  res.render('cpptest');
});

router.post('/route', function(req, res) {

  // var data = JSON.parse(req.body.data);
  var origin = '31.470656,74.412929';
  var destination = '31.470789,74.408619';
  var waypoints = ['31.470789,74.428661', '31.470789,74.409632']

  directions(origin, destination, waypoints, function(data) {
    res.json(data);
  });

});

module.exports = router;

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

  var postReq;

  for (var p in req.body) {
    postReq = p;
  }

  postReq = JSON.parse(postReq);

  //TODO: written this for when the JSON parsing C++ is ready
  var placeholderData = {};
  placeholderData.origin = postReq.origin;
  placeholderData.destination = postReq.destination;
  placeholderData.waypoints = postReq.waypoints;

  var dataInAsJson = JSON.stringify(placeholderData);

  console.log(dataInAsJson);

  //TODO: Change this once the final artifact place is known
  //TODO: Security flaw: Bash injection. We have to use files I guess?
  var cppCommand = 'echo \'' + dataInAsJson + '\' | ./algorithm/build/tsp.bin';

  var child = exec(cppCommand, function (error, stdout, stderr) {
    if (error !== null) {
      console.log('exec error: ' + error);
      res.send(500).end();
      return;
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

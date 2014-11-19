var express = require('express');
var directions = require('../directions/directions')
var router = express.Router();
var exec = require('child_process').exec;

/* GET home page. */
router.get('/', function(req, res) {
    res.render('index', { title: 'Express' });
});

router.get('/cpp', function(req, res) {
    res.send("Need POST request");
});

router.post('/cpp', function(req, res) {

    var postReq = JSON.parse(Object.keys(req.body)[0]);

    var jsonInformation = {};
    jsonInformation.origin = postReq.origin;
    jsonInformation.destination = postReq.destination;
    jsonInformation.waypoints = postReq.waypoints;

    //TODO: Security flaw: Bash injection. We have to use files I guess?
    var cppCommand = 'echo \'' + JSON.stringify(jsonInformation) + '\' | ./algorithm/build/tsp.bin';

    var child = exec(cppCommand, function (error, stdout, stderr) {
        if (error !== null) {
            console.log('exec error: ' + error);
            res.send(500).end();
            return;
        }
        res.send(stdout);
    });

});

module.exports = router;

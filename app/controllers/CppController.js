var exec = require('child_process').exec;

exports.controller = function(req, res) {
    var postReq = JSON.parse(Object.keys(req.body)[0]);

    var jsonInformation = {
        origin : postReq.origin,
        destination : postReq.destination,
        waypoints : postReq.waypoints
    };

    //TODO: Security flaw: Bash injection. We have to use files I guess?
    var cppCommand = 'echo \'' + JSON.stringify(jsonInformation) + '\' | ./algorithm/build/tsp.bin';

    var child = exec(cppCommand, function (error, stdout, stderr) {
        if (error !== null) {
            console.log('exec error: ' + error);
            res.status(500).end();
            return;
        }
        res.send(stdout);
    });
};

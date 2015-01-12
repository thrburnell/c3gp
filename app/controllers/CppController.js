var exec = require('child_process').exec;

exports.controller = function(req, res) {
    var postReq = req.body;

    //TODO: Security flaw: Bash injection. We have to use files I guess?
    var cppCommand = 'echo \'' + JSON.stringify(postReq) + '\' | ./algorithm/build/tsp.bin';

    var child = exec(cppCommand, function (error, stdout, stderr) {
        if (error !== null) {
            console.log('exec error: ' + error);
            res.status(500).end();
            return;
        }
        res.send(stdout);
    });
};

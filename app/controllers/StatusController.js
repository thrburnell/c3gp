var exec = require('child_process').exec;

exports.controller = function(req, res) {

    var cppCommand = 'git log -1';

    var child = exec(cppCommand, function (error, stdout, stderr) {
        if (error !== null) {
            console.log('exec error: ' + error);
            res.status(500).end();
            return;
        }
        res.send(stdout.replace("\n", "<br />"));
    });
}

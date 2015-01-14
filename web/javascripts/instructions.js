var locals = require('./locals.js');

module.exports = (function() {

    var setText = function(message) {
        $("#instructions").text(message);
    };

    var startSpinner = function() {
    	$("#spinner").show();
    };

    var stopSpinner = function() {
    	$("#spinner").hide();
    };

    return {
        setText: setText,
        startSpinner: startSpinner,
        stopSpinner: stopSpinner,
    };

})();

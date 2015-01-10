var locals = require('./locals.js');

module.exports = (function() {

    var setText = function(message) {
        $("#instructions").text(message);
    };

    return {
        setText: setText
    };

})();

var api = require('./api.js');
var splash = require('./splash.js');

module.exports = (function() {

    // Add listeners to the page
    var listen = function() {
        $("#button a").click(function() {
            console.log("Getting your route...");
            api.calcRoute();
        });

        $("#b-start").click(function() {
            splash.hideSplash();
            splash.splashAddCookie();
        });
    }

    return {
        listen: listen
    };

})();

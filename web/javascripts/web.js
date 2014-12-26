var map = require('./map.js');
var api = require('./api.js');
var splash = require('./splash.js');

$(document).ready(function() {

    google.maps.event.addDomListener(window, 'load', map.initialize);
    splash.checkForSplash();

    $("#button a").click(function() {
        console.log("Getting your route...");
        api.calcRoute();
    });

    $("#b-start").click(function() {
        splash.hideSplash();
        splash.splashAddCookie();
    });

});

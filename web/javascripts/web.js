/*global $:false */
/*global google:false */

"use strict";

var map = require('./map.js');
var api = require('./api.js');
var splash = require('./splash.js');
var listeners = require('./listeners.js');

$(document).ready(function() {

    google.maps.event.addDomListener(window, 'load', map.initialize);

    // Presents a first-time user with an informative splash
    splash.checkForSplash();
    // Activate listeners on the page
    listeners.listen();

});

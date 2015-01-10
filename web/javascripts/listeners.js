var api = require('./api.js');
var map = require('./map.js');
var splash = require('./splash.js');
var search = require('./search.js');
var menu = require('./menu.js');
var locals = require('./locals.js');
var instructions = require('./instructions.js');

module.exports = (function() {

    // Add listeners to the page
    var listen = function() {
        $("#get-route").click(function() {
            api.calcRoute();
        });

        $("#b-edit-route").click(function() {
            menu.changeToInputStripe();
        });

        $("#b-start").click(function() {
            splash.hideSplash();
            splash.splashAddCookie();
        });

        $("#origin-button").click(function() {
            search.searchOriginAddress();
        });

        $("#origin-input").keyup(function(event) {
            if (event.keyCode === 13) {
                $("#origin-button").click();
            }
        });

        $("#gps-button").click(function() {
            map.setCurrentLocation();
        });

        $("#search-button").click(function() {
            search.makeSearch();
        });

        $("#search-input").keyup(function(event) {
            if (event.keyCode === 13) {
                $("#search-button").click();
            }
        });

        $("#origin-point").hover(function() {
            instructions.setText(locals.originInputText);
        });

        $("#search-point").hover(function() {
            instructions.setText(locals.searchText);
        });

        $("#errands-point").hover(function() {
            instructions.setText(locals.errandText);
        });

    };

    return {
        listen: listen
    };

})();

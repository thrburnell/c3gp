var api = require('./api.js');
var map = require('./map.js');
var splash = require('./splash.js');
var search = require('./search.js');
var menu = require('./menu.js');
var locals = require('./locals.js');
var instructions = require('./instructions.js');
var errand = require('./errand.js');
var markers = require('./markers.js');
var constants = require('./constants.js');
var route = require('./route.js');

module.exports = (function() {

    // Add listeners to the page
    var listen = function() {
        $("#get-route").click(function() {
            api.calcRoute();
            api.setGtspFlagOff();
        });

        $("#b-edit-route").click(function() {
            menu.changeToInputStripe();
        });

        $("#b-clear-route").click(function() {
            menu.clearInputStripe();
            menu.changeToInputStripe();
            route.clearRoute();
        });

        $("#b-start").click(function() {
            splash.hideSplash();
            splash.splashAddCookie();
        });

        $("#origin-input-primary").keyup(function(event) {
            if (event.keyCode === 13) {
                search.searchOriginAddress();
            }
        });

        $("#gps-button").click(function() {
            map.setCurrentLocation();
        });

        $("#errand-input-primary").keyup(function(event) {
            errand.makeSearch(event.target);
        });

        $("#errand-input-primary").click(function(event) {
            errand.makeSearch(event.target);
        });

        $("#errand-input-primary, #errand-template").keyup(function(event) {

            if (event.which !== 13) {
                event.target.title = '';
                return;
            }

            markers.clearTemporaries();

            if (event.target.title !== '') {
                search.makeErrandSearch(event.target.title,
                                        event.target.colloquial);
            } else {
                search.makeSearch(event.target.value);
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

        $("#stripe-input").slimScroll({
            width: constants.menuStripeWidth + 'px',
            height: '100%',
            size: '10px',
            float: 'left',
            position: 'right',
            color: '#ffffff',
            alwaysVisible: false,
            distance: '5px',
            railVisible: false,
            wheelStep: 10,
            allowPageScroll: false,
            disableFadeOut: false
        });

        $("#b-use-gtsp").click(function() {
            api.setGtspFlagOn();
            markers.convertTemporariesToPermanent();
            menu.disableNextErrandInput();
        });

    };

    return {
        listen: listen
    };

})();

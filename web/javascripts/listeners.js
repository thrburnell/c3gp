var api = require('./api.js');
var splash = require('./splash.js');
var search = require('./search.js');
var menu = require('./menu.js');

module.exports = (function() {

    // Add listeners to the page
    var listen = function() {
        $("#get-route").click(function() {
            api.calcRoute();
            menu.changeToResultsStripe();
        });

        $("#b-edit-route").click(function() {
            menu.changeToInputStripe();
        });

        $("#b-start").click(function() {
            splash.hideSplash();
            splash.splashAddCookie();
        });

        $("#search-button").click(function() {
            search.makeSearch();
        });

        $("#search-input").keyup(function(event) {
            if (event.keyCode === 13) {
                $("#search-button").click();
            }
        });
    };

    return {
        listen: listen
    };

})();

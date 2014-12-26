module.exports = (function() {

    var splashHasCookie = function() {
        var cookie = $.cookie('splash');
        return cookie === 'true';
    };

    var checkForSplash = function() {
        if (splashHasCookie()) {
            return;
        }

        var welcomeSplash = $("#d-welcome");
        welcomeSplash.show();

        var topBar = $("#top-bar");
        topBar.hide();
    };

    var hideSplash = function() {
        var welcomeSplash = $("#d-welcome");
        welcomeSplash.hide();

        var topBar = $("#top-bar");
        topBar.show();
    };

    var splashAddCookie = function() {
        $.cookie("splash", "true");
    };

    return {
        checkForSplash: checkForSplash,
        hideSplash: hideSplash,
        splashAddCookie: splashAddCookie
    };

})();

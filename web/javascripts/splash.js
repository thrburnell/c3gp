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

        $("input").one("click", function() {
            hideSplash();
        });
    };

    var hideSplash = function() {

        splashAddCookie();

        var welcomeSplash = $("#d-welcome");
        welcomeSplash.hide(500);

        var topBar = $("#top-bar");
        topBar.show(500);
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

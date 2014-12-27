var markers = require('./markers.js');
var route = require('./route.js');

module.exports = (function() {

    var formRequest = function() {
        var indexes = markers.getSortedMarkers();

        var origPos = markers.getOrigin().getPosition();
        var origLat = origPos.lat();
        var origLng = origPos.lng();

        var origin = {
            "lat": origLat,
            "lng": origLng
        };

        var destination = origin;
        var points = markers.getMarkers();
        var waypoints = [];

        // Temporary behaviour - to be replaced with system that maps errands
        // to points. Currently, the user is required to click on the relevant
        // points, which are used to form this array of waypoints.
        for (var i = 1; i < indexes.length; i++) {
            var position = points[indexes[i]].getPosition();
            waypoints.push({
                "lat": position.lat(),
                "lng": position.lng()
            });
        }

        return {
            "origin": origin,
            "destination": destination,
            "waypoints": waypoints
        };

    };

    var calcRoute = function() {

        $.ajax({
            url: "/cpp",
            method: "POST",
            data: JSON.stringify(formRequest()),
            success: function(ret) {
                route.displayRoute(JSON.parse(ret));
            }
        });
    };

    return {
        calcRoute: calcRoute
    };

})();

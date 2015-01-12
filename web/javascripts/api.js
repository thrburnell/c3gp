var markers = require('./markers.js');
var route = require('./route.js');

module.exports = (function() {

    var useGtsp = false;

    var formRequest = function() {
        var indexes = markers.getSortedMarkers();

        var origPos = markers.getOrigin().getPosition();
        var origLat = origPos.lat();
        var origLng = origPos.lng();

        var origin = {
            "lat": origLat,
            "lng": origLng,
            "group": 0
        };

        var destination = origin;
        var points = markers.getMarkers();
        var waypoints = [];

        // Temporary behaviour - to be replaced with system that maps errands
        // to points. Currently, the user is required to click on the relevant
        // points, which are used to form this array of waypoints.
        for (var i = 1; i < indexes.length; i++) {
            for (var j = 0; j < points[indexes[i]].length; j++) {
                var position = points[indexes[i]][j].getPosition();
                waypoints.push({
                    "lat": position.lat(),
                    "lng": position.lng(),
                    "group": i
                });
            }
        }

        var data = {
            "origin": origin,
            "destination": destination,
            "waypoints": waypoints
        };

        var ret = {};
        if (useGtsp) {
            ret.algorithm = 'gtsp';
        } else {
            ret.algorithm = 'tsp';
        }

        ret.data = data;

        return ret;

    };

    var setGtsp = function() {
        useGtsp = true;
    };

    var calcRoute = function() {

        console.log(JSON.stringify(formRequest()));

        $.ajax({
            url: "/cpp",
            method: "POST",
            data: JSON.stringify(formRequest()),
            contentType: "application/json",
            success: function(ret) {
                route.displayRoute(JSON.parse(ret));
            }
        });
    };

    return {
        calcRoute: calcRoute,
        setGtsp: setGtsp
    };

})();

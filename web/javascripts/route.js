var markers = require('./markers.js');
var map = require('./map.js');

module.exports = (function() {

    var displayRoute = function(route) {

        var start = new google.maps.LatLng(route[0].lat, route[0].lng);
        var end = start;
        var waypoints = [];

        for (var i = 1; i < route.length; i++) {
            waypoints.push({
                location: new google.maps.LatLng(route[i].lat, route[i].lng),
                stopover: true
            });
        }

        var request = {
            origin: start,
            destination: end,
            waypoints: waypoints,
            travelMode: google.maps.TravelMode.WALKING
        };

        map.getDirectionsService().route(request, function(response, status) {
            if (status == google.maps.DirectionsStatus.OK) {
                map.getDirectionsDisplay().setDirections(response);
                markers.clear();
            }
        });
    };

    return {
        displayRoute: displayRoute
    };

})();

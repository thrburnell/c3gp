var markers = require('./markers.js');
var map = require('./map.js');

module.exports = (function() {

    var displayRoute = function(route) {

        var start = new google.maps.LatLng(route[0].lat, route[0].lng);
        var end = start;
        var waypoints = [];

        for (var i = 1; i < route.length; i++) {
            waypoints.push({
                location: new google.maps.LatLng(route[i].lat, route[i].lng)
            });
        }

        var request1 = {
            origin: start,
            destination: waypoints[0].location,
            travelMode: google.maps.TravelMode.WALKING
        };

        var request2 = {
            origin: waypoints[0].location,
            destination: waypoints[1].location,
            travelMode: google.maps.TravelMode.WALKING
        };

        map.getDirectionsService().route(request1, function(response, status) {
            if (status == google.maps.DirectionsStatus.OK) {
                var directionsRenderer = new google.maps.DirectionsRenderer();
                directionsRenderer.setMap(map.getMap());
                directionsRenderer.setDirections(response);
                markers.clear();
            }
        });

        setTimeout(function() {
            map.getDirectionsService().route(request2, function(response, status) {
                if (status == google.maps.DirectionsStatus.OK) {
                    var directionsRenderer = new google.maps.DirectionsRenderer();
                    directionsRenderer.setMap(map.getMap());
                    directionsRenderer.setDirections(response);
                    markers.clear();
                }
            });
        }, 2000);

    };

    return {
        displayRoute: displayRoute
    };

})();

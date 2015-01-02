var markers = require('./markers.js');
var map = require('./map.js');

module.exports = (function() {

    var currRequest = 0;
    var locations = [];

    var displayRoute = function(route) {

        var start = new google.maps.LatLng(route[0].lat, route[0].lng);
        var end = start;

        locations.push(start);
        for (var i = 1; i < route.length; i++) {
            locations.push(new google.maps.LatLng(route[i].lat, route[i].lng));
        }
        locations.push(end);

        markers.clear();

        currRequest = 0;
        nextRequest();

    };

    /**
     * Hack. Too lazy to see what a promise is.
     */
    var nextRequest = function() {
        if (currRequest === locations.length - 1) {
            return;
        }

        var request = {
            origin: locations[currRequest],
            destination: locations[currRequest+1],
            travelMode: google.maps.TravelMode.WALKING
        };

        currRequest++;
        requestForRoute(request);
    };

    var requestForRoute = function(request, index) {
        map.getDirectionsService().route(request, function(response, status) {
            if (status === google.maps.DirectionsStatus.OK) {
                renderDirections(response);
                markers.add(map.getMapCanvas(), request.origin, index);
                nextRequest();
            }
        });
    };

    var renderDirections = function(result) {
        var directionsRenderer = new google.maps.DirectionsRenderer();
        directionsRenderer.setMap(map.getMapCanvas());
        directionsRenderer.setOptions ({
            suppressMarkers: true,
            preserveViewport: true,
            // polylineOptions: {
                // strokeColor: "#000000"
            // }
        });
        directionsRenderer.setDirections(result);
    };

    return {
        displayRoute: displayRoute
    };

})();

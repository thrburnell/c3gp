var markers = require('./markers.js');
var map = require('./map.js');
var menu = require('./menu.js');
var polyline = require('./polyline.js');

module.exports = (function() {

    var currRequest = 0;
    var locations = [];
    var directionsRenderers = [];

    var displayRoute = function(route) {

        var i;
        var start = new google.maps.LatLng(route[0].lat, route[0].lng);
        var end = start;

        var resultsArray = {
            origin: "Current Location",
            errands: [],
            destination: "Current Location"
        };
        for (i = 1; i < route.length; i++) {
            var temp = String.fromCharCode('A'.charCodeAt(0) + i);
            resultsArray.errands.push("Step towards point " + temp);
        }

        menu.clearResults();
        menu.setResults(resultsArray);
        menu.changeToResultsStripe();

        clearRoute();
        locations = [];
        locations.push(start);
        for (i = 1; i < route.length; i++) {
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
            } else if (status === google.maps.DirectionsStatus.OVER_QUERY_LIMIT) {
                currRequest--;
                setTimeout(function() {
                    nextRequest();
                }, 1000);
            }
        });
    };

    var renderDirections = function(result) {
        var directionsRenderer = new google.maps.DirectionsRenderer();
        directionsRenderer.setMap(map.getMapCanvas());

        var newPolyline = polyline.createPolyline(map.getMapCanvas());
        polyline.addPolyline(newPolyline);

        directionsRenderer.setOptions({
            suppressMarkers: true,
            preserveViewport: true,
            polylineOptions: newPolyline
        });
        directionsRenderer.setDirections(result);
        directionsRenderers.push(directionsRenderer);
    };

    var clearRoute = function() {
        directionsRenderers.forEach(function(renderer) {
            renderer.setMap(null);
        });
        directionsRenderers = [];
        polyline.clearPolylines();
    };

    return {
        displayRoute: displayRoute
    };

})();

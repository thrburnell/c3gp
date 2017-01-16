var markers = require('./markers.js');
var map = require('./map.js');
var menu = require('./menu.js');
var polyline = require('./polyline.js');

module.exports = (function() {

    var currRequest = 0;
    var locations = [];
    var directionsRenderers = [];

    // An array of strings corresponding to the google.maps.TravelMode constants
    // transitToPoint[i] = 'transit' means we take the tube to reach that point
    // transitToPoint[0] === null because that is the origin (we are already there)
    var transitToPoint = [];

    var displayRoute = function(route) {

        computeMenuItems(route);
        computeTransitToPoints(route);
        computeLocationsArray(route);

        clearRoute();

        currRequest = 0;
        nextRequest();
    };

    var computeMenuItems = function(route) {

        console.log(route);
        var resultsArray = {
            origin: "Current Location",
            errands: [],
            destination: "Current Location"
        };
        for (var i = 1; i < route.length - 1; i++) {
            var letter = String.fromCharCode('A'.charCodeAt(0) + i);
            // resultsArray.errands.push("Step towards point " + letter);
            var errandsInfo = markers.getErrandsInfo();
            var info;
            for (var errandKey in errandsInfo) {
                if (isSamePosition(errandKey, route[i].lat, route[i].lng)) {
                    info = errandsInfo[errandKey];
                    break;
                }
            }

            resultsArray.errands.push(info.placeName + ": " + info.errand);
        }

        menu.clearResults();
        menu.setResults(resultsArray);
        menu.changeToResultsStripe();
    };

    var isSamePosition = function(key, lat, lng) {
        var epsilon = 0.00001;
        var keyPos = key.split(",");
        var keyLat = keyPos[0];
        var keyLng = keyPos[1];
        return Math.abs(keyLat - lat) < epsilon &&
                     Math.abs(keyLng - lng) < epsilon;
    };

    var computeTransitToPoints = function(route) {
        transitToPoint = [];
        transitToPoint.push(null);
        for (var i = 1; i < route.length; i++) {
            transitToPoint.push(route[i].transit);
        }
    };

    var computeLocationsArray = function(route) {
        locations = [];
        for (var i = 0; i < route.length; i++) {
            locations.push(new google.maps.LatLng(route[i].lat, route[i].lng));
        }
    };

    /**
     * Hack. Too lazy to see what a promise is.
     */
    var nextRequest = function() {
        if (currRequest === locations.length - 1) {
            return;
        }

        var travelMode;
        if (transitToPoint[currRequest + 1] === 'transit') {
            travelMode = google.maps.TravelMode.TRANSIT;
        } else {
            travelMode = google.maps.TravelMode.WALKING;
        }

        var request = {
            origin: locations[currRequest],
            destination: locations[currRequest+1],
            travelMode: travelMode
        };

        currRequest++;
        requestForRoute(request);
    };

    var requestForRoute = function(request, index) {
        map.getDirectionsService().route(request, function(response, status) {
            if (status === google.maps.DirectionsStatus.OK) {
                // computeMenuItems(response);
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
        markers.clear();
        directionsRenderers.forEach(function(renderer) {
            renderer.setMap(null);
        });
        directionsRenderers = [];
        polyline.clearPolylines();
    };

    return {
        displayRoute: displayRoute,
        clearRoute: clearRoute,
    };

})();

var instructions = require('./instructions.js');
var locals = require('./locals.js');
var markers = require('./markers.js');
var menu = require('./menu.js');

module.exports = (function() {
    var directionsService = new google.maps.DirectionsService();
    var startingLocation = new google.maps.LatLng(51.498800,-0.174877);
    var map;

    var initialize = function() {
        // This deactivates points of interest on the map.
        var mapStyles = [{
            featureType: "poi",
            elementType: "labels",
            stylers: [{ visibility: "off" }]
        }];

        var mapOptions = {
            center: startingLocation,
            zoom: 16,
            styles: mapStyles
        };

        map = new google.maps.Map(document.getElementById('map-canvas'),
            mapOptions);

        google.maps.event.addListener(map, 'mouseover', function() {
            instructions.setText(locals.mapText);
        });

        google.maps.event.addListener(map, 'click', function(event) {
            var marker = markers.add(map, event.latLng);
            menu.insertTextIntoNextBox(locals.pointOnMap);

            google.maps.event.addListener(marker, 'click', function(point) {
                markers.remove(marker);
            });
        });

    };

    var setCurrentLocation = function() {
        instructions.startSpinner();
        navigator.geolocation.getCurrentPosition(function(pos) {
            instructions.stopSpinner();
            var loc = new google.maps.LatLng(pos.coords.latitude,
                                             pos.coords.longitude);
            menu.setOriginText(locals.currentLocation);
            setStartingLocation(loc);
        });
    };

    var setStartingLocation = function(loc) {
        startingLocation = loc;
        map.setCenter(startingLocation);
        markers.setOrigin(map, startingLocation);
        menu.lockOriginInput();
    };

    return {
        initialize: initialize,
        getMapCanvas: function() { return map; },
        getDirectionsService: function() { return directionsService; },
        getStartingLocation: function() { return startingLocation; },
        setCurrentLocation: setCurrentLocation,
        setStartingLocation: setStartingLocation
    };

})();

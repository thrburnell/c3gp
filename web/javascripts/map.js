var instructions = require('./instructions.js');
var markers = require('./markers.js');

module.exports = (function() {
    var directionsService = new google.maps.DirectionsService();
    var startingLocation = new google.maps.LatLng(51.498800,-0.174877);
    var directionsDisplay;
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

        // Listener to drop pin on mouse click
        google.maps.event.addListener(map, 'click', function(event) {
            instructions.defaultMessage();
            var marker = markers.add(map, event.latLng);

            google.maps.event.addListener(marker, 'click', function(point) {
                markers.remove(marker);
            });
        });

        directionsDisplay = new google.maps.DirectionsRenderer();
        directionsDisplay.setMap(map);

    };

    return {
        initialize: initialize,
        getMapCanvas: function() { return map; },
        getDirectionsDisplay: function() { return directionsDisplay; },
        getDirectionsService: function() { return directionsService; },
        getStartingLocation: function() { return startingLocation; }
    };

})();

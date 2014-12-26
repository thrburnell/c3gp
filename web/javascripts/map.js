var instructions = require('./instructions.js');
var markers = require('./markers.js');

module.exports = (function() {
    var directionsService = new google.maps.DirectionsService();
    var directionsDisplay;

    var initialize = function() {

        var mapOptions = {
            center: {lat: 51.498800, lng: -0.174877},
            zoom: 16
        };

        var map = new google.maps.Map(document.getElementById('map-canvas'),
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
        getDirectionsDisplay: function() { return directionsDisplay; },
        getDirectionsService: function() { return directionsService; }
    };

})();

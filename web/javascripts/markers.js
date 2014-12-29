var instructions = require('./instructions.js');

module.exports = (function() {

    var markers = [];
    var temporaryMarkers = [];
    var pinIndex = 0;
    var redColour = "F7574C";
    var greenColour = "7BCC70";
    var letterColour = "000000";
    var infoWindow = new google.maps.InfoWindow();

    var add = function(map, position, letter) {
        var marker = createMarker(map, position, letter);
        markers[pinIndex++] = marker;
        return marker;
    };

    var addTemporaries = function(map, results) {
        for (var i = 0; i < results.length; i++) {
            var place = results[i];
            var marker = createMarker(map, place.geometry.location,
                                    null, greenColour);
            google.maps.event.addListener(marker, 'click',
                displayInfoBox(map, place, marker));
            temporaryMarkers.push(marker);
        }
    };

    var createMarker = function(map, position, letter, colour) {
        colour = colour || redColour;
        letter = letter || String.fromCharCode('A'.charCodeAt(0) + pinIndex);
        var markerUrl = "http://chart.apis.google.com/chart?chst=d_map_pin" +
                        "_letter&chld=" + letter + "|" + colour + "|" +
                        letterColour;
        var myPin = new google.maps.MarkerImage(markerUrl);
        var marker = new google.maps.Marker({
            position: position,
            map: map,
            icon: myPin
        });
        return marker;
    };

    var displayInfoBox = function(map, place, marker) {
        var content = document.createElement('div');
        var button;
        content.innerHTML = 'Name: ' + place.name + '<br />' +
                            'Rating: ' + place.rating + '<br />';
        button = content.appendChild(document.createElement('input'));
        button.type = 'button';
        button.value = 'Add me';
        google.maps.event.addDomListener(button, 'click', function() {
            add(map, place.geometry.location);
            clearTemporaries();
        });

        return function() {
            infoWindow.setContent(content);
            infoWindow.open(map, marker);
        };
    };

    var remove = function(marker) {
        if (marker.index === 0) {
            instructions.originError();
        } else {
            marker.setMap(null);
            delete markers[marker.index];
            instructions.defaultMessage();
        }
    };

    var clear = function() {
        markers.map(function(m) { m.setMap(null); });
        markers = [];
        pinIndex = 0;
    };

    var clearTemporaries = function() {
        temporaryMarkers.map(function(m) { m.setMap(null); });
    };

    return {
        add: add,
        addTemporaries: addTemporaries,
        remove: remove,
        clear: clear,
        clearTemporaries: clearTemporaries,
        getSortedMarkers: function() { return Object.keys(markers).sort(); },
        getOrigin: function() { return markers[0]; },
        getMarkers: function() { return markers; }
    };

})();

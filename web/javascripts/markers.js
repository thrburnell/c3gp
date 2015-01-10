var instructions = require('./instructions.js');
var locals = require('./locals.js');

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
        if (pinIndex > 0) {
            addInstructionToMarker(marker, locals.defaultMarker,
                                 locals.mapText);
        }
        markers[pinIndex++] = marker;
        return marker;
    };

    var addTemporaries = function(map, results) {
        results.forEach(function(place) {
            var marker = createMarker(map, place.geometry.location,
                                    null, greenColour);

            google.maps.event.addListener(marker, 'click', function() {
                displayInfoBox(map, place, marker);
            });

            addInstructionToMarker(marker, locals.temporaryMarker,
                                 locals.mapText);
            temporaryMarkers.push(marker);
        });
    };

    var setOrigin = function(map, position) {
        if (markers.length === 0) {
            add(map, position, 'A');
        } else {
            var previous = markers[0];
            markers[0] = createMarker(map, position, 'A');
            previous.setMap(null);
        }
        markers[0].isOrigin = true;
        addInstructionToMarker(markers[0], locals.originMarker,
                             locals.mapText);
    };

    var createMarker = function(map, position, letter, colour) {
        colour = colour || redColour;
        letter = letter || String.fromCharCode('A'.charCodeAt(0) + pinIndex);
        var draggable = letter === 'A';
        var markerUrl = "http://chart.apis.google.com/chart?chst=d_map_pin" +
                        "_letter&chld=" + letter + "|" + colour + "|" +
                        letterColour;
        var myPin = new google.maps.MarkerImage(markerUrl);
        var marker = new google.maps.Marker({
            position: position,
            map: map,
            icon: myPin,
            draggable: draggable
        });
        return marker;
    };

    var displayInfoBox = function(map, place, marker) {

        var content = $('<div>');

        ["Name: " + place.name,
        "Rating: " + (place.rating || "N/A")
        ].forEach(function(line) {
            content.append($("<div>", {
                class: "nowrap"
            }).html(line));
        });

        var button = $('<input>', {
            type: 'button',
            value: 'Add me'
        });
        content.append(button);
        google.maps.event.addDomListener(button[0], 'click', function() {
            add(map, place.geometry.location);
            clearTemporaries();
        });

        infoWindow.open(map, marker);
        infoWindow.setContent(content[0]);
    };

    var remove = function(marker) {
        marker.setMap(null);
        delete markers[marker.index];
        pinIndex--;
    };

    var addInstructionToMarker = function(marker, mouseoverText,
                                          mouseoutText) {
        google.maps.event.addListener(marker, 'mouseover', function() {
            instructions.setText(mouseoverText);
        });

        // When the mouse is away from the marker sets back the map message
        google.maps.event.addListener(marker, 'mouseout', function() {
            instructions.setText(mouseoutText);
        });
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
        getMarkers: function() { return markers; },
        setOrigin: setOrigin
    };

})();

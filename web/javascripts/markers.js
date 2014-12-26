var instructions = require('./instructions.js');

module.exports = (function() {

    var markers = [];
    var pin_index = 0;

    var add = function(map, position) {
        var m_index = pin_index++;
        var marker = new google.maps.Marker({
            position: position,
            map: map,
            index: m_index
        });

        // The starting point will bounce so it's easier to identify it
        if (marker.index === 0) {
            marker.setAnimation(google.maps.Animation.BOUNCE);
        }

        markers[m_index] = marker;
        return marker;
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
        for (var i = 0; i < markers.length; i++) {
            markers[i].setMap(null);
        }
        markers = [];
        pin_index = 0;
    };

    return {
        add: add,
        remove: remove,
        clear: clear,
        getSortedMarkers: function() { return Object.keys(markers).sort(); },
        getOrigin: function() { return markers[0]; },
        getMarkers: function() { return markers; }
    };

})();

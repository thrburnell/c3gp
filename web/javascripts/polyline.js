module.exports = (function() {

    var polylines = [];
    var polylineDefaultOpacity = 0.6;
    var polylineDefaultWeight = 6;
    var polylineDefaultZIndex = 1;
    var polylineDefaultColor = '#0088FF';
    var polylineHighlightColor = '#EA7260';

    var highlightSegment = function(segmentNumber) {
        segmentNumber = segmentNumber || 0;

        if (segmentNumber >= polylines.length) {
            console.error("Segment does not exist");
            return;
        }

        polylines[segmentNumber].setOptions({
            strokeColor: polylineHighlightColor,
            strokeWeight: 8,
            strokeOpacity: 1,
            zIndex: 1000000
        });
    };

    var normalizeSegment = function(segmentNumber) {
        segmentNumber = segmentNumber || 0;
        if (segmentNumber >= polylines.length) {
            console.error("Segment does not exist");
            return;
        }

        polylines[segmentNumber].setOptions({
            strokeColor: polylineDefaultColor,
            strokeWeight: polylineDefaultWeight,
            strokeOpacity: polylineDefaultOpacity,
            zIndex: polylineDefaultZIndex
        });
    };

    var addPolyline = function(polyline) {
        polylines.push(polyline);
    };

    var clearPolylines = function() {
        polylines = [];
    };

    var createPolyline = function(map) {
        return new google.maps.Polyline({
            map: map,
            strokeColor: polylineDefaultColor,
            strokeWeight: polylineDefaultWeight,
            strokeOpacity: polylineDefaultOpacity
        });
    };

    return {
        polylineDefaultColor: polylineDefaultColor,
        polylineDefaultOpacity: polylineDefaultOpacity,
        polylineDefaultWeight: polylineDefaultWeight,
        highlightSegment: highlightSegment,
        normalizeSegment: normalizeSegment,
        addPolyline: addPolyline,
        clearPolylines: clearPolylines,
        createPolyline: createPolyline
    };

})();

var markers = require('./markers.js');
var map = require('./map.js');

module.exports = (function() {

    var makeSearch = function() {
        // Clear any previous search
        markers.clearTemporaries();
        var searchInput = $("#search-input").val();
        var request = {
            location: map.getStartingLocation(),
            keyword: searchInput,
            radius: '500'
        };
        service = new google.maps.places.PlacesService(map.getMapCanvas());
        service.nearbySearch(request, function(results, status) {
            if (status === google.maps.places.PlacesServiceStatus.OK) {
                markers.addTemporaries(map.getMapCanvas(), results);
            }
        });
    };


    return {
        makeSearch: makeSearch
    };

})();

var markers = require('./markers.js');
var map = require('./map.js');

module.exports = (function() {

    var makeSearch = function() {
        // Clear any previous search
        markers.clearTemporaries();
        var searchInput = $('#search-input').val();
        var request = {
            location: map.getStartingLocation(),
            keyword: searchInput,
            radius: '500'
        };
        var service = new google.maps.places.PlacesService(map.getMapCanvas());
        service.nearbySearch(request, function(results, status) {
            if (status === google.maps.places.PlacesServiceStatus.OK) {
                markers.addTemporaries(map.getMapCanvas(), results);
            }
        });
    };

    var searchOriginAddress = function() {
        var locationInput = $('#origin-input').val();
        var request = {
            location: map.getStartingLocation(),
            address: locationInput
        };
        var geocoder = new google.maps.Geocoder();
        geocoder.geocode(request, function(results, status) {
            if (status === google.maps.GeocoderStatus.OK) {
                map.setStartingLocation(results[0].geometry.location);
            }
        });
    };

    return {
        makeSearch: makeSearch,
        searchOriginAddress: searchOriginAddress
    };

})();

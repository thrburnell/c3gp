var markers = require('./markers.js');
var map = require('./map.js');

module.exports = (function() {

    var makeSearch = function(searchInput) {
        // Clear any previous search
        markers.clearTemporaries();
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
        var locationInput = $('#origin-input-primary').val();
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

    var makeErrandSearch = function(api_id, colloquial) {
        markers.clearTemporaries();

        var requestData = {
            errand: api_id,
            areas: []
        };

        markers.getMarkers().forEach(function(marker) {
            var newLocation = {
                location: {
                    lat: marker.position.lat(),
                    lng: marker.position.lng()
                }
            };
            requestData.areas.push(newLocation);
        });

        jQuery.ajax({
            url: '/errand',
            method: "POST",
            contentType: "application/json",
            data: JSON.stringify(requestData),
            success: function(ret, status) {
                markers.buildErrandsInfo(ret, colloquial);
                markers.addTemporaries(map.getMapCanvas(), ret);
            }
        });
    };

    return {
        makeSearch: makeSearch,
        searchOriginAddress: searchOriginAddress,
        makeErrandSearch: makeErrandSearch
    };

})();

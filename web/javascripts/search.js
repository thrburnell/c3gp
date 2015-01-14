var markers = require('./markers.js');
var map = require('./map.js');
var instructions = require('./instructions.js');
var locals = require('./locals.js');

module.exports = (function() {

    var makeSearch = function(searchInput) {
        // Clear any previous search
        markers.clearTemporaries();
        var request = {
            location: map.getStartingLocation(),
            keyword: searchInput,
            radius: '500'
        };
        instructions.startSpinner();
        var service = new google.maps.places.PlacesService(map.getMapCanvas());
        service.nearbySearch(request, function(results, status) {
            instructions.stopSpinner();
            if (status === google.maps.places.PlacesServiceStatus.OK) {
                markers.buildErrandsInfo(results, locals.goTo + ' ' + searchInput);
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
        instructions.startSpinner();
        geocoder.geocode(request, function(results, status) {
            instructions.stopSpinner();
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
                    lat: marker[0].position.lat(),
                    lng: marker[0].position.lng()
                }
            };
            requestData.areas.push(newLocation);
        });

        instructions.startSpinner();
        jQuery.ajax({
            url: '/errand',
            method: "POST",
            contentType: "application/json",
            data: JSON.stringify(requestData),
            success: function(ret, status) {
                markers.buildErrandsInfo(ret, colloquial);
                markers.addTemporaries(map.getMapCanvas(), ret);
            },
            complete: function() {
                instructions.stopSpinner();
            }
        });
    };

    return {
        makeSearch: makeSearch,
        searchOriginAddress: searchOriginAddress,
        makeErrandSearch: makeErrandSearch
    };

})();

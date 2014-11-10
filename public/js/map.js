var markers = [];

function initialize() {
  var mapOptions = {
    center: {lat: 51.498800, lng: -0.174877},
    zoom: 16
  };

  var map = new google.maps.Map(document.getElementById('map-canvas'),
                                mapOptions);

  google.maps.event.addListener(map, 'click', function(event) {
    var marker = new google.maps.Marker({
      position: event.latLng,
      map: map
    });

    // TODO Eventually we should change this to push just the position.
    markers.push(marker);
    console.log(markers);

    google.maps.event.addListener(marker, 'click', function(point) {
      marker.setMap(null); // removes the marker from the map
      for(var i = 0; i < markers.length; ++i) {
        if(markers[i] === marker) {
          markers.splice(i, 1); // removes marker from array of markers
        }
      }
      console.log(markers);
    });
  });
}

google.maps.event.addDomListener(window, 'load', initialize);

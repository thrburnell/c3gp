var markers = {};

function initialize() {
  var mapOptions = {
    center: {lat: 51.498800, lng: -0.174877},
    zoom: 16
  };

  var map = new google.maps.Map(document.getElementById('map-canvas'),
                                mapOptions);

  // Listener to drop pin on mouse click
  google.maps.event.addListener(map, 'click', function(event) {

    // Identify marker by string representation of lat/lng
    var m_id = event.latLng.toString();
    var marker = new google.maps.Marker({
      position: event.latLng,
      map: map,
      id: m_id
    });

    markers[m_id] = marker;
    console.log(markers);

    // Listener to remove pin on click
    google.maps.event.addListener(marker, 'click', function(point) {
      marker.setMap(null);
      delete markers[marker.id];
      console.log(markers);
    });
  });
}

google.maps.event.addDomListener(window, 'load', initialize);


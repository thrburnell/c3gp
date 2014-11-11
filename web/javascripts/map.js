$(document).ready(function() {
  var markers = {};

  function initialize() {
    var pin_index = 0;

    var mapOptions = {
      center: {lat: 51.498800, lng: -0.174877},
      zoom: 16
    };

    var map = new google.maps.Map(document.getElementById('map-canvas'),
                                  mapOptions);

    // Listener to drop pin on mouse click
    google.maps.event.addListener(map, 'click', function(event) {

      // Identify markers by index (i.e. position in list of visiting points)
      var m_index = pin_index++;
      var marker = new google.maps.Marker({
        position: event.latLng,
        map: map,
        index: m_index
      });

      if (marker.index == 0) {
        marker.setAnimation(google.maps.Animation.BOUNCE);
      }

      markers[m_index] = marker;
      $("#instructions").text("Select points of interest");
      console.log(markers);

      // Listener to remove pin on click
      google.maps.event.addListener(marker, 'click', function(point) {
        if (marker.index == 0) {
          // give message
          $("#instructions").text("Cannot delete starting position!");
        } else {
          marker.setMap(null);
          delete markers[marker.index];
          $("#instructions").text("Select points of interest");
          console.log(markers);
        }
      });
    });
  }

  function formRequest() {
    
    var indexes = Object.keys(markers).sort();

    // Get the origin
    var orig_pos = markers[0].getPosition();
    var orig_lat = orig_pos.lat();
    var orig_lng = orig_pos.lng();
    
    var origin = {
      "lat": orig_lat,
      "lng": orig_lng
    };
    var destination = origin;
    var waypoints = [];

    for (var i = 1; i < indexes.length; i++) {
      var position = markers[indexes[i]].getPosition();
      waypoints.push({
        "lat": position.lat(),
        "lng": position.lng()
      });
    }

    return {
      "origin": origin,
      "destination": destination,
      "waypoints": waypoints
    };
  }

  google.maps.event.addDomListener(window, 'load', initialize);

  $("#button a").click(function() {
    console.log("Getting your route...");
    console.log(formRequest());
  });
});


$(document).ready(function() {
  var markers = {};
  var directionsService = new google.maps.DirectionsService();
  var directionsDisplay;

  function initialize() {
    var pin_index = 0;

    var mapOptions = {
      center: {lat: 51.498800, lng: -0.174877},
      zoom: 16
    };

    var map = new google.maps.Map(document.getElementById('map-canvas'),
                                  mapOptions);

    // Instruction messages to provide to the user.
    var default_message = 'Select points of interest.';
    var delete_origin_error_message = 'Cannot delete starting position!';

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
      setInstruction(default_message);
      console.log(markers);

      // Listener to remove pin on click
      google.maps.event.addListener(marker, 'click', function(point) {
        if (marker.index == 0) {
          // give message
          setInstruction(delete_origin_error_message);
        } else {
          marker.setMap(null);
          delete markers[marker.index];
          setInstruction(default_message);
          console.log(markers);
        }
      });
    });

    directionsDisplay = new google.maps.DirectionsRenderer();
    directionsDisplay.setMap(map);
  }

  function setInstruction(message) {
    $("#instructions").text(message);
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

    // Temporary behaviour - to be replaced with system that maps errands
    // to points. Currently, the user is required to click on the relevant
    // points, which are used to form this array of waypoints.
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
    routeRequest = formRequest();
    console.log(routeRequest);
    calcRoute(routeRequest);

  });

  function calcRoute(routeRequest) {

    jsonData = JSON.stringify(routeRequest);

    $.ajax({
      url: "/cpp",
      method: "POST",
      data: jsonData,
      success: function(ret) {
        displayRoute(JSON.parse(ret));
      }
    });



  }

  function displayRoute(route) {

    var n = route.length;

    console.log(n);
    var start = new google.maps.LatLng(route[0].lat, route[0].lng)
    var end = new google.maps.LatLng(route[0].lat, route[0].lng)
    var waypoints = [];

    for (var i = 1; i < n; i++) {
      var pt = new google.maps.LatLng(route[i].lat, route[i].lng)
      waypoints.push({
        location: pt,
        stopover: true
      });
    }

    var request = {
        origin: start,
        destination: end,
        waypoints: waypoints,
        travelMode: google.maps.TravelMode.WALKING
    };
    directionsService.route(request, function(response, status) {
      if (status == google.maps.DirectionsStatus.OK) {
        directionsDisplay.setDirections(response);
      }
    });


  }
});


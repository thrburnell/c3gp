function initialize() {
	var mapOptions = {
		center: {lat: 51.498800, lng: -0.174877},
		zoom: 16
	};
	var map = new google.maps.Map(document.getElementById('map-canvas'),
								  mapOptions);
	}
google.maps.event.addDomListener(window, 'load', initialize);
var gm = require('googlemaps');
var util = require('util');

var directions = function(origin, destination, waypoints, callback) {
  gm.config('key', process.env.GMAPS_KEY)
  gm.directions(origin, destination, function(err, data) {
      util.puts(JSON.stringify(data));
      callback(data);
  }, false, undefined, waypoints);

};

module.exports = directions;

var errandDefinitions = require('./errand-definitions')
var request = require('request');
var sleep = require('sleep');
var Q = require('q');

// Environment variable GMAPS_KEY provides Google Maps API key
var API_KEY = process.env.GMAPS_KEY;

// The default radius to search around given point, if not specified
var DEFAULT_AREA_RADIUS = 500;

// Makes a request to the given Google Maps API URL, and returns a promise 
// representing the result of the call. The promise is resolved with the 
// place results upon success, or rejected with the Google Maps `status` 
// and `error_message` upon failure.
// If `retry` is `true`, then an OVER_QUERY_LIMIT Google Maps response 
// results in promise rejection; otherwise, the request is retried after the 
// instructed 2 seconds.
var makeRequest = function(url, retry) {

  var deferred = Q.defer();

  request(url, function(error, response, body) {

    body = JSON.parse(body);
    
    if (error || response.statusCode != 200) {
      deferred.reject(error);
      return deferred.promise;
    }

    var googleStatus = body.status;

    if (googleStatus == "OK" || googleStatus == "ZERO_RESULTS") {
      deferred.resolve(body.results);
    } else if (googleStatus == "OVER_QUERY_LIMIT" && !retry) {
      makeRequest(url, true).then(deferred.resolve, deferred.reject);
    } else {
      deferred.reject({
        status: googleStatus,
        error_message: body.error_message
      });
    }
  });

  return deferred.promise;
};

module.exports = {

  // Returns a promise which, upon success, is resolved with an array of 
  // places where a user can complete the given errand. The places are all 
  // within the specified vicinities, and if a `name` is given then the 
  // names of all places match. Additionally, if the openNow flag is 
  // given, all places are open at the time of calling.
  // Please refer to `schemas` for detail on the place structure.
  findPlaces: function(errand, areas, name, openNow) {

    // Get the Google Places types/keywords corresponding to this errand
    var googleVals = errandDefinitions[errand].googleAttributes;
    var types = googleVals.types || [];
    var keyword = googleVals.keyword || "";

    // Construct the Google Places request URL common to each request
    // (a separate request is made for each search area)
    var baseUrl = "https://maps.googleapis.com/maps/api/place/" + 
                  "nearbysearch/json?";
    
    baseUrl += "key=" + API_KEY;
    baseUrl += "&types=" + types.join('|');
    baseUrl += "&keyword=" + keyword;
    if (openNow) baseUrl += "&opennow";
    if (name)    baseUrl += "&name=" + name;

    // Make a Google Places request for each search area
    var promises = [];
    for (var i = 0; i < areas.length; i++) {
      var area = areas[i];
      var requestUrl = baseUrl +
        "&location=" + area.location.lat + "," + area.location.lng +
        "&radius=" + (area.radius || DEFAULT_AREA_RADIUS);

      promises.push(makeRequest(requestUrl));
    }

    var deferred = Q.defer();

    // Resolve returned promise with concat of all request results, or 
    // propagate error
    Q.all(promises).then(
      function(res) { deferred.resolve([].concat.apply([], res)); },
      function(err) { deferred.reject(err); });

    return deferred.promise;
  }

};


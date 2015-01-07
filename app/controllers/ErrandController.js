var errand = require('../errand');

exports.controller = function(req, res) {

  var qErrand = req.body.errand;
  var areas = req.body.areas;
  var name = req.body.name;
  var openNow = req.body.opennow;

  errand.findPlaces(qErrand, areas, name, openNow)
    .then(
      function(result) {
        res.send(result);
      },
      function(err) {
        console.error(err);
        res.status(500).end();
      }
    );
};


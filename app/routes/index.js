var express = require('express');
var directions = require('../directions/directions')
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res) {
  res.render('index', { title: 'Express' });
});

router.get('/route', function(req, res) {
	res.send("Need POST request");
});

router.post('/route', function(req, res) {

	// var data = JSON.parse(req.body.data);
  var origin = '31.470656,74.412929';
  var destination = '31.470789,74.408619';
  var waypoints = ['31.470789,74.428661', '31.470789,74.409632']

  directions(origin, destination, waypoints, function(data) {
    res.json(data);
  });

});

module.exports = router;

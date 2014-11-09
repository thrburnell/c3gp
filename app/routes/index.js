var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res) {
  res.render('index', { title: 'Express' });
});


router.get('/route', function(req, res) {
	res.send("Need POST request");
})

//TODO: Extract int into a controller

/**
 * Sample data
 *
 * [
 * 	{"id":"0", x":"1.0005","y":"2.0005"},
 * 	{"id":"1", x":"4.0005","y":"3.0005"}
 * ]
 */
router.post('/route', function(req, res) {

	var body_data = req.body.data;

	data = JSON.parse(body_data);


	var nodes = data.length;

	var result = [];
	for (var i = 0; i < nodes; i++) {
		result.push(i);
	}

	result.push(0);

	res.send(result);
})


module.exports = router;

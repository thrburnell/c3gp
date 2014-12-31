var express = require('express');
var router = express.Router();

var CppController = require('../controllers/CppController');
var IndexController = require('../controllers/IndexController');
var StatusController = require('../controllers/StatusController');
var ResultsController = require('../controllers/ResultsController');

router.get('/', IndexController.controller);
router.get('/status', StatusController.controller);
router.get('/results', ResultsController.controller);

router.post('/cpp', CppController.controller);

module.exports = router;

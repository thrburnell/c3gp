var express = require('express');
var router = express.Router();

var CppController = require('../controllers/CppController');
var IndexController = require('../controllers/IndexController');
var StatusController = require('../controllers/StatusController');
var ResultsController = require('../controllers/ResultsController');
var ErrandController = require('../controllers/ErrandController');

router.get('/', IndexController.controller);
router.get('/status', StatusController.controller);
router.get('/results', ResultsController.controller);

router.post('/cpp', CppController.controller);

router.post('/errand', ErrandController.controller);

module.exports = router;

var express = require('express');
var router = express.Router();

var CppController = require('../controllers/CppController');
var IndexController = require('../controllers/IndexController');
var StatusController = require('../controllers/StatusController');

router.get('/', IndexController.controller);

router.post('/cpp', CppController.controller);
router.get('/status', StatusController.controller);

module.exports = router;

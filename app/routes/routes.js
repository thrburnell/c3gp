var express = require('express');
var router = express.Router();

var CppController = require('../controllers/CppController');
var IndexController = require('../controllers/IndexController');

router.get('/', IndexController.controller);

router.get('/cpp', CppController.controller);
router.post('/cpp', CppController.controller);

module.exports = router;

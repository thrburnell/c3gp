var schemas = require('../schemas');
var tv4 = require('tv4');


module.exports = {

  configure: function(app) {

    // Validate request data
    app.use('/errand', function(req, res, next) {

      if (!tv4.validate(req.body, schemas.errand.post)) {
        res.status(400).end();
      } else {
        next();
      }
    });

  }

};


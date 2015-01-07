var schemas = require('../schemas');
var googleMapping = require('../errand/google-mapping');
var tv4 = require('tv4');

module.exports = {

  // Configures the given app with midware
  configure: function(app) {

    // Validate request data
    app.use('/errand', function(req, res, next) {

      if (!tv4.validate(req.body, schemas.errand.post) || 
          !googleMapping[req.body.errand]) {

        res.status(400).end();
      } else {
        next();
      }
    });

  }

};


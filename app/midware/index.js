var schemas = require('../schemas');
var errandDefinitions = require('../errand/errand-definitions');
var tv4 = require('tv4');

module.exports = {

  // Configures the given app with midware
  configure: function(app) {

    // Validate request data
    app.use('/errand', function(req, res, next) {

      if (!tv4.validate(req.body, schemas.errand.post) || 
          !errandDefinitions[req.body.errand]) {

        res.status(400).end();
      } else {
        next();
      }
    });

  }

};


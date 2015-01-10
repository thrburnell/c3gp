// This task generates a JSON file, errands.json, defining all supported 
// errands, which is dumped in the web/javascripts directory. The resulting 
// file is of the format:
//
// [
//  {
//    "colloquial": "Post a letter",
//    "search_keywords": [ ],
//    "api_id": "post_letter"
//  },
//  ...
// ]

var fs = require('fs');
var errandDefinitions = require('../app/errand/errand-definitions');

module.exports = function(grunt) {

  grunt.registerTask('client-errands',
      'Generate public errand definitions file in public/js',
      function() {

        var clientErrands = [];

        var errandIds = Object.keys(errandDefinitions);
        for (var i = 0; i < errandIds.length; i++) {
          var errand = errandDefinitions[errandIds[i]];
          clientErrands.push({
            "colloquial": errand.colloquial,
            "search_keywords": errand.search_keywords,
            "api_id": errandIds[i]
          });
        }
        
        // Write the file
        fs.writeFileSync('./web/javascripts/errands.json',
          JSON.stringify(clientErrands, null, 2));

        console.log("Generated web/javascripts/errands.json with success.");
       
      });

};


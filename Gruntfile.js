require('shelljs/global');

module.exports = function(grunt) {

  // Configuration for grunt tasks
  grunt.initConfig({
   
    // Location of server script
    serverScript: 'bin/www',

    // Load global project config
    pkg: grunt.file.readJSON('package.json'),

    // Config for nodemon server
    nodemon: {
      dev: {
        script: 'bin/www'
      }
    },

    // Config for running nodemon and watch tasks concurrently
    concurrent: {
      target: {
        tasks: ['nodemon', 'watch'],
        options: {
          logConcurrentOutput: true
        }
      }
    },

    // Configure tasks to run on watched file changes
    watch: {
      sass: {
        files: ['web/stylesheets/*.scss'],
        tasks: ['sass']
      },
      jshint: {
        files: ['*.js', 'web/javascripts/**/*.js', 'app/**/*.js'],
        tasks: ['jshint']
      },
      jsonlint: {
        files: ['*.json'],
        tasks: ['jsonlint']
      },
      js: {
        files: ['web/javascripts/**/*.js'],
        tasks: ['copy:js']
      },
      css: {
        files: ['web/stylesheets/**/*.css'],
        tasks: ['copy:css']
      }
    },

    // Config for copying js/css files from web to public
    copy: {
      js: {
        expand: true,
        cwd: 'web/javascripts',
        src: '*.js',
        dest: 'public/js'
      },
      css: {
        expand: true,
        cwd: 'web/stylesheets',
        src: '*.css',
        dest: 'public/css'
      }
    },

    // Config for compiling sass from web/stylesheets to public/css
    sass: {
      dist: {
        files: [{
          expand: true,
          cwd: 'web/stylesheets',
          src: ['*.scss'],
          dest: 'public/css',
          ext: '.css'
        }]
      }
    },

    // Config for hinting all js files
    jshint: {
      all: ['*.js', 'web/javascripts/**/*.js', 'app/**/*.js']
    },

    // Config for linting all json files
    jsonlint: {
      jsonlint: {
        src: ['*.json']
      }
    },

    // Config specifying location of test run scripts
    test: {
      algorithm: {
        dir: 'algorithm',
        script: 'runTests.py'
      },

      server: {
        dir: '.',
        script: 'runTests.py'
      }
    }

  });

  grunt.registerTask('algorithm', 
      'Installs all libraries and compiles algorithm code.',
      function() {
        // Execute install script in algorithm dir
        exec('(cd algorithm; ./install.py)');
      });

  // grunt test:{algorithm / server / front}
  grunt.registerMultiTask('test',
      'Runs (optionally specified) test suites.',
      function() {
        // Run test script for specified target
        exec('(cd ' + this.data.dir + '; ./' + this.data.script + ')');
      });

  grunt.registerTask('public',
      'Generates public static files.',
      ['copy']);

  grunt.registerTask('dev',
      'Compiles all code, starts server, watches for all file changes.',
      ['prepare', 'concurrent']);

  grunt.registerTask('prepare',
      'Runs all tasks (e.g. compilation) needed to start the server.',
      function() {

        // If additional tasks need to be run before the server can be 
        // started, they should be implemented here

        // npm install
        if (exec('npm install').code !== 0) {
          grunt.log.writeln('Failed to install npm modules.');
        }

        // bower install
        if (exec('bower install').code !== 0) {
          grunt.log.writeln('Failed to install bower components.');
        }

        // Compile all algorithm code and generate public files
        grunt.task.run(['algorithm', 'public']);

      });

  grunt.registerTask('forever-start',
      'Starts/restarts a forever process to run the server.',
      function() {

        script = grunt.config('serverScript');

        // Attempt to restart process
        if (exec('forever restart ' + script).code !== 0) {
          
          // Restart failed (i.e. it was never started to begin with)
          if (exec('forever start ' + script).code !== 0) {
            // Start failed unexpectedly
            grunt.log.writeln('Failed to start forever process.');
          }
        }

      });

  grunt.registerTask('forever-end',
      'Stops all forever processes running the server.',
      function() {
        exec('forever stop ' + grunt.config('serverScript'));
      });

  // Load npm tasks
  grunt.loadNpmTasks('grunt-sass');
  grunt.loadNpmTasks('grunt-contrib-copy');
  grunt.loadNpmTasks('grunt-nodemon');
  grunt.loadNpmTasks('grunt-concurrent');
  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.loadNpmTasks('grunt-contrib-jshint');
  grunt.loadNpmTasks('grunt-jsonlint');

};


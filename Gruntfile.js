require('shelljs/global');

// We use Grunt as a task runner. All tasks, such as compilation or test
// running, should be achieved by running one of these tasks.
//
// For a list of available tasks, run `grunt -h`. For example, running
// `grunt dev` compiles all code, moves all public files into place,
// starts the server, and watches for all file changes (restarting the
// server when necessary, and moving public files across when modified).
//
// Additionally, all our production and demo environments run `grunt prepare`
// before `grunt forever-start`. The first compiles all code and moves
// everything into place for server start, and the second starts/restarts
// the server process. If additional jobs need to be carried out before
// starting the server, one should add the necessary code to the 'prepare'
// task.
//
// During development, developers will often want to make use of `grunt dev`.
// This task moves all public files into place, compiles all server code, and
// starts the server, after which making sure all files are watched for
// changes.

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
        script: 'bin/www',
        options: {
          watch: ['app']
        }
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
        tasks: ['browserify']
      },
      css: {
        files: ['web/stylesheets/**/*.css'],
        tasks: ['copy:css']
      }
    },

    browserify: {
      dist: {
        files: {
          'public/js/web.js': ['web/javascripts/*.js']
        }
      }
    },

    // Config for copying js/css files from web to public
    copy: {
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
      options: {
        browserify: true
      },
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
    },

    // Config specifying tasks to run for validating different file types
    validate: {
      json: 'jsonlint',
      js: 'jshint'
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
      ['copy', 'sass', 'browserify']);

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
        grunt.task.run(['client-errands', 'algorithm', 'public']);

      });

  grunt.registerTask('forever-start',
      'Starts/restarts a forever process to run the server.',
      function() {

        script = grunt.config('serverScript');

        // Stop server (will fail if server isn't running)
        exec('forever stop ' + script);

        // Start server
        if (exec('forever start ' + script).code !== 0) {
          // Start failed unexpectedly
          grunt.log.writeln('Failed to start forever process.');
        }

      });

  grunt.registerTask('forever-end',
      'Stops all forever processes running the server.',
      function() {
        exec('forever stop ' + grunt.config('serverScript'));
      });

  grunt.registerMultiTask('validate',
      'Runs validation checks over all registered file types.',
      function() {
        grunt.task.run(this.data);
      });

  // Load npm tasks
  grunt.loadNpmTasks('grunt-sass');
  grunt.loadNpmTasks('grunt-contrib-copy');
  grunt.loadNpmTasks('grunt-nodemon');
  grunt.loadNpmTasks('grunt-concurrent');
  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.loadNpmTasks('grunt-contrib-jshint');
  grunt.loadNpmTasks('grunt-jsonlint');
  grunt.loadNpmTasks('grunt-browserify');

  // Load custom tasks
  grunt.loadTasks('grunt');

};


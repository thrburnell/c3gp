module.exports = function(grunt) {
  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),

    concat: {
      options: {
        separator: ';'
      },
      dist: {
        src: ['web/javascripts/*.js'],
        dest: 'public/js/<%= pkg.name %>.js'
      }
    },

    uglify: {
      options: {
        banner: '/* <%= pkg.name %> <%= grunt.template.today("dd-mm-yyyy") %> */\n'
      },
      dist: {
        files: {
          'public/js/<%= pkg.name %>.min.js': ['<%= concat.dist.dest %>']
        }
      }
    },

    cssmin: {
      options: {
        banner: '/* <%= pkg.name %> <%= grunt.template.today("dd-mm-yyyy") %> */\n'
      },
      minify: {
        expand: true,
        cwd: 'web/stylesheets/',
        src: ['*.css'],
        dest: 'public/css/',
        ext: '.min.css'
      }
    },

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

    jshint: {
      all: ['*.js', 'web/javascripts/**/*.js', 'app/**/*.js']
    },

    jsonlint: {
      jsonlint: {
        src: ['*.json']
      }
    },

    watch: {
      sass: {
        files: ['web/stylesheets/*.scss'],
        tasks: ['sass']
      },
      jshint: {
        files: ['*.js', 'web/javascripts/**/*.js', 'app/**/*.js'],
        tasks: ['jshint']
      }
    }
  });

  grunt.loadNpmTasks('grunt-contrib-uglify');
  grunt.loadNpmTasks('grunt-contrib-concat');
  grunt.loadNpmTasks('grunt-contrib-cssmin');
  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.loadNpmTasks('grunt-contrib-jshint');
  grunt.loadNpmTasks('grunt-jsonlint');
  grunt.loadNpmTasks('grunt-sass');

  grunt.registerTask('static', ['concat', 'uglify', 'cssmin']);
};


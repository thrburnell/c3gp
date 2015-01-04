var supertest = require('supertest');
var should = require('should');

var app = require('../app');

describe("Routes", function() {

  beforeEach(function() {
    this.request = supertest(app);
  });

  describe("GET /", function() {
    
    it("should return 200", function(done) {
      this.request
        .get('/')      
        .expect(200, done);
    });

  });

  describe("GET /status", function() {

    it("should return 200", function(done) {
      this.request
        .get('/status')
        .expect(200, done);
    });

  });

  describe("POST /cpp", function() {

    it("should return 200 given valid request", function(done) {

      var data = {
        "origin":      
          { "lat": 51.499633334377386, "lng": -0.1795792579650879 },
        "destination": 
          { "lat": 51.499633334377386, "lng": -0.1795792579650879 },
        "waypoints": [
          { "lat": 51.49999399415595, "lng": -0.17475128173828125 }, 
          { "lat": 51.49887193213894, "lng": -0.17691850662231445 }
        ]
      };

      this.request
        .post('/cpp')
        .send(data)
        .expect(200, done);

    });

  });

  describe("POST /errand", function() {

    it("should return 200 given valid request", function(done) {
      this.request
        .post('/errand')
        .send(makeRequest("coffee", makeAreas()))
        .expect(200, done);
    });

    it("should return 400 given unrecognised errand", function(done) {
      this.request
        .post('/errand')
        .send(makeRequest("unknown", makeAreas()))
        .expect(400, done);
    });

    it("should return 400 given no errand", function(done) {
      this.request
        .post('/errand')
        .send({ "areas": makeAreas() })
        .expect(400, done);
    });

    it("should return 400 given no areas", function(done) {
      this.request
        .post('/errand')
        .send({ "errand": "coffee" })
        .expect(400, done);
    });

    it("should return 400 given empty areas", function(done) {
      this.request
        .post('/errand')
        .send({ "errand": "coffee", "areas": [] })
        .expect(400, done);
    });

    var makeAreas = function() {
      return [
        {
          "location": 
            { "lat": 51.499633334377386, "lng": -0.1795792579650879 }, 
          "radius": 500 
        }
      ];
    };

    var makeRequest = function(errand, areas) {
      return {
        "errand": errand,
        "areas": areas
      };
    };

  });

});

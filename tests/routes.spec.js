var request = require('supertest');
var express = require('express');
var app = require('../app');

request = request(app);

describe("Accessibility to all routes", function() {

    it("should have index", function(done) {
        request
        .get('/')
        .expect(200)
        .end(function(err, res) {
            expect(err).toBe(null);
            done();
        });
    }, 1000);

    it("should have the cpp page", function(done) {
        var data = {"origin":{"lat":51.499633334377386,"lng":-0.1795792579650879},"destination":{"lat":51.499633334377386,"lng":-0.1795792579650879},"waypoints":[{"lat":51.49999399415595,"lng":-0.17475128173828125},{"lat":51.49887193213894,"lng":-0.17691850662231445}]};
        data = JSON.stringify(data);

        request
        .post('/cpp')
        .send(data)
        .expect(200)
        .end(function(err) {
            expect(err).toBe(null);
            done();
        });
    }, 1000);


});

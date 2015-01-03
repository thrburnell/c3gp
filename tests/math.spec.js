var should = require('should');

describe("My First Test", function() {
  it("should be equal", function() {
    (1+2).should.equal(3);
  });

  it("should not be equal", function() {
    (4 + 3).should.not.equal(8);
  });
});

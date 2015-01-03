exports.controller = function(req, res) {

  var response = {
    foo: "hello",
    bar: "world"
  };

  res.send(response);

};


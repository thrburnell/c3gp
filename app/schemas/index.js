module.exports = {
  errand: {
    post: {
      "title": "Errand",
      "description": "A request to POST /errand",
      "type": "object",
      "properties": {
          "errand": {
              "description": "The errand to search for",
              "type": "string"
          },
          "areas": {
              "description": "Array of coordinate/radius objects defining search space",
              "type": "array",
              "items": {
                  "type": "object",
                  "properties": {
                    "location": {
                      "description": "The location to search near",
                      "type": "object",
                      "properties": {
                        "lat": {
                          "type": "number"
                        },
                        "lng": {
                          "type": "number"
                        }
                      },
                      "required": ["lat", "lng"]
                    },
                    "radius": {
                      "description": "The radius in meters to search over",
                      "type": "number"
                    }
                  },
                  "required": ["location"]
              },
              "minItems": 1
          },
          "opennow": {
              "description": "Flag if only currently open places should be returned",
              "type": "boolean"
          }
      },
      "required": ["errand", "areas"]
    }
  }
};


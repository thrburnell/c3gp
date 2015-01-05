#include "lib/rapidjson/document.h"
#include "lib/rapidjson/writer.h"
#include "lib/rapidjson/stringbuffer.h"

#include "json_parse.h"

namespace rj = rapidjson;

/**
 * For sample data, see testData/coordinates.json
 */
MapPoints* parse_coordinates(const char* const json) {
    rj::Document document;
    document.Parse(json);

    MapPoints* mapPoints = new MapPoints();

    Coordinate* origin = new Coordinate();
    origin->lat = document["origin"]["lat"].GetDouble();
    origin->lng = document["origin"]["lng"].GetDouble();
    origin->group = 0;

    Coordinate* destination = new Coordinate();
    destination->lat = document["destination"]["lat"].GetDouble();
    destination->lng = document["destination"]["lng"].GetDouble();
    destination->group = 0;

    std::vector<Coordinate*>* errands = new std::vector<Coordinate*>();

    const rj::Value & waypoints = document["waypoints"];
    for (int i = 0; i < waypoints.Size(); i++) {
        Coordinate* newCoordinate = new Coordinate();
        newCoordinate->lat = waypoints[i]["lat"].GetDouble();
        newCoordinate->lng = waypoints[i]["lng"].GetDouble();

        if (waypoints[i].HasMember("group")) {
            newCoordinate->group = waypoints[i]["group"].GetInt();
        } else {
            newCoordinate->group = 0;
        }

        errands->push_back(newCoordinate);
    }

    mapPoints->origin = origin;
    mapPoints->destination = destination;
    mapPoints->errands = errands;

    return mapPoints;
}


/**
 * @return JSON encoding of the given struct
 * The JSON returned is of the form [{"lat": 123, "lng": 321}, ...]
 * The first point is the origin
 * The second point is the first errand to visit
 * The destination is not represented because it is assumed to be the origin
 */
std::string print_coordinates(MapPoints* map_points) {

    rj::StringBuffer s;
    rj::Writer<rj::StringBuffer> writer(s);

    writer.StartArray();

    writer.StartObject();

    writer.String("lat");
    writer.Double(map_points->origin->lat);

    writer.String("lng");
    writer.Double(map_points->origin->lng);

    writer.EndObject();

    for (auto it = map_points->errands->begin(); it != map_points->errands->end(); it++) {
        writer.StartObject();

        writer.String("lat");
        writer.Double((*it)->lat);

        writer.String("lng");
        writer.Double((*it)->lng);

        writer.EndObject();
    }

    writer.EndArray();

    return s.GetString();
}

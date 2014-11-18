#include "lib/rapidjson/document.h"
#include "lib/rapidjson/writer.h"
#include "lib/rapidjson/stringbuffer.h"

#include <iostream>

#include "map_points.h"

namespace rj = rapidjson;
using std::unique_ptr;

/**
 * For sample data, see testData/coordinates.json
 */
unique_ptr<MapPoints> parse_coordinates(const char * const json) {
    rj::Document document;
    document.Parse(json);

    unique_ptr<MapPoints> mapPoints(new MapPoints);

    unique_ptr<Coordinate> origin(new Coordinate);
    origin->lat = document["origin"]["lat"].GetDouble();
    origin->lng = document["origin"]["lng"].GetDouble();

    unique_ptr<Coordinate> destination(new Coordinate);
    destination->lat = document["destination"]["lat"].GetDouble();
    destination->lng = document["destination"]["lng"].GetDouble();

    unique_ptr<std::vector<unique_ptr<Coordinate>>> errands(new std::vector<unique_ptr<Coordinate>>);

    const rj::Value & waypoints = document["waypoints"];
    for (int i = 0; i < waypoints.Size(); i++) {
        unique_ptr<Coordinate> newCoordinate(new Coordinate);
        newCoordinate->lat = waypoints[i]["lat"].GetDouble();
        newCoordinate->lng = waypoints[i]["lng"].GetDouble();
        errands->push_back(move(newCoordinate));
    }

    mapPoints->origin = move(origin);
    mapPoints->destination = move(destination);
    mapPoints->errands = move(errands);

    return mapPoints;
}


/**
 * TODO: We should 1) Move this to a process file 2) implement
 * @param The given data points
 * @return Some processing on this data (possibly)
 */
unique_ptr<MapPoints> process_coordinates(unique_ptr<MapPoints> map_points) {
    return move(map_points);
}


/**
 * @return JSON encoding of the given struct
 */
void print_coordinates(unique_ptr<MapPoints> map_points) {
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

    std::cout << s.GetString() << std::endl;
}

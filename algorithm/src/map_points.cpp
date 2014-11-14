#include "lib/rapidjson/document.h"
#include "lib/rapidjson/writer.h"
#include "lib/rapidjson/stringbuffer.h"

#include <iostream>

#include "map_points.h"

using namespace rapidjson;
using namespace std;

/**
 * For sample data, see testData/coordinates.json
 */
unique_ptr<MapPoints> parse_coordinates(char * json) {
    Document document;
    document.Parse(json);

    unique_ptr<MapPoints> mapPoints(new MapPoints);

    unique_ptr<Coordinate> origin(new Coordinate);
    origin->lat = document["origin"]["lat"].GetDouble();
    origin->lng = document["origin"]["lng"].GetDouble();

    unique_ptr<Coordinate> destination(new Coordinate);
    destination->lat = document["destination"]["lat"].GetDouble();
    destination->lng = document["destination"]["lng"].GetDouble();

    unique_ptr<vector<unique_ptr<Coordinate>>> errands(new vector<unique_ptr<Coordinate>>);

    const Value & waypoints = document["waypoints"];
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
 * @return Some processing on this data (possibly )
 */
unique_ptr<MapPoints> process_coordinates(unique_ptr<MapPoints> map_points) {
    return move(map_points);
}


/**
 * @return JSON Encode of the given struct
 */
void print_coordinates(unique_ptr<MapPoints> map_points) {
    StringBuffer s;
    Writer<StringBuffer> writer(s);

    writer.StartArray();

    for (auto it = map_points->errands->begin(); it != map_points->errands->end(); it++) {
        writer.StartObject();

        writer.String("lat");
        writer.Double((*it)->lat);

        writer.String("lng");
        writer.Double((*it)->lng);

        writer.EndObject();
    }

    writer.EndArray();

    cout << s.GetString() << endl;
}

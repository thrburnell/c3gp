#include "lib/rapidjson/document.h"
#include "lib/rapidjson/writer.h"
#include "lib/rapidjson/stringbuffer.h"

#include <iostream>

#include "map_points.h"
#include "haversine.h"

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


//TODO: Use unique_ptr properly in this function
/**
 * @param The given data points
 * @return Some processing on this data (possibly)
 */
unique_ptr<MapPoints> process_coordinates(unique_ptr<MapPoints> map_points) {

    unique_ptr<std::vector<unique_ptr<Coordinate>>> r_errands(new std::vector<unique_ptr<Coordinate>>);

    std::vector<Coordinate *> v;

    Coordinate * origin = new Coordinate();
    origin->lat = map_points->origin->lat;
    origin->lng = map_points->origin->lng;

    Coordinate * destination = new Coordinate();
    destination->lat = map_points->destination->lat;
    destination->lng = map_points->destination->lng;

    for (std::vector<unique_ptr<Coordinate>>::iterator it = map_points->errands->begin(); it != map_points->errands->end(); it++) {
        Coordinate * newCoord = new Coordinate();
        newCoord->lat = (*it)->lat;
        newCoord->lng = (*it)->lng;

        v.push_back(newCoord);
    }

    Coordinate * iterator = origin;

    while (! v.empty()) {
        double min_dist = 1023456789.0;
        std::vector<Coordinate *>::iterator min_dist_iterator;
        for (std::vector<Coordinate *>::iterator it = v.begin(); it != v.end(); it++) {
            double curr_dist = calculate_distance((const Coordinate&) (*iterator), (const Coordinate&) (*(*it)));
            if (curr_dist < min_dist) {
                min_dist = curr_dist;
                min_dist_iterator = it;
            }
        }

        unique_ptr<Coordinate> temp_coordinate(new Coordinate);
        temp_coordinate->lat = (*min_dist_iterator)->lat;
        temp_coordinate->lng = (*min_dist_iterator)->lng;


        r_errands->push_back(move(temp_coordinate));

        iterator = *min_dist_iterator;
        v.erase(min_dist_iterator);
    }

    unique_ptr<MapPoints> result(new MapPoints);

    unique_ptr<Coordinate> r_origin(new Coordinate);
    r_origin->lat = origin->lat;
    r_origin->lng = origin->lng;

    unique_ptr<Coordinate> r_destination(new Coordinate);
    r_destination->lat = destination->lat;
    r_destination->lat = destination->lng;

    result->origin = move(r_origin);
    result->destination = move(r_destination);
    result->errands = move(r_errands);

    return move(result);
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

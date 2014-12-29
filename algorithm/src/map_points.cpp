#include "lib/rapidjson/document.h"
#include "lib/rapidjson/writer.h"
#include "lib/rapidjson/stringbuffer.h"

#include <iostream>
#include <limits>

#include "map_points.h"
#include "haversine.h"

namespace rj = rapidjson;

/**
 * For sample data, see testData/coordinates.json
 */
MapPoints * parse_coordinates(const char * const json) {
    rj::Document document;
    document.Parse(json);

    MapPoints * mapPoints = new MapPoints();

    Coordinate * origin = new Coordinate();
    origin->lat = document["origin"]["lat"].GetDouble();
    origin->lng = document["origin"]["lng"].GetDouble();

    Coordinate * destination = new Coordinate();
    destination->lat = document["destination"]["lat"].GetDouble();
    destination->lng = document["destination"]["lng"].GetDouble();

    std::vector<Coordinate *> * errands = new std::vector<Coordinate *>();

    const rj::Value & waypoints = document["waypoints"];
    for (int i = 0; i < waypoints.Size(); i++) {
        Coordinate * newCoordinate = new Coordinate();
        newCoordinate->lat = waypoints[i]["lat"].GetDouble();
        newCoordinate->lng = waypoints[i]["lng"].GetDouble();
        errands->push_back(newCoordinate);
    }

    mapPoints->origin = origin;
    mapPoints->destination = destination;
    mapPoints->errands = errands;

    return mapPoints;
}


//TODO: Use unique_ptr properly in this function
/**
 * @param The given data points
 * @return Some processing on this data (possibly)
 */
MapPoints * process_coordinates(MapPoints * map_points) {

    std::vector<Coordinate *> * r_errands = new std::vector<Coordinate *>();

    std::vector<Coordinate *> v;

    Coordinate * origin = new Coordinate();
    origin->lat = map_points->origin->lat;
    origin->lng = map_points->origin->lng;

    Coordinate * destination = new Coordinate();
    destination->lat = map_points->destination->lat;
    destination->lng = map_points->destination->lng;

    for (
            std::vector<Coordinate *>::iterator it = map_points->errands->begin();
            it != map_points->errands->end();
            it++) {
        Coordinate * newCoord = new Coordinate();
        newCoord->lat = (*it)->lat;
        newCoord->lng = (*it)->lng;

        v.push_back(newCoord);
    }

    Coordinate * iterator = origin;

    while (! v.empty()) {
        double min_dist = std::numeric_limits<double>::max();
        std::vector<Coordinate *>::iterator min_dist_iterator;
        for (std::vector<Coordinate *>::iterator it = v.begin(); it != v.end(); it++) {
            double curr_dist = calculate_distance((const Coordinate&) (*iterator), (const Coordinate&) (*(*it)));
            if (curr_dist < min_dist) {
                min_dist = curr_dist;
                min_dist_iterator = it;
            }
        }

        Coordinate * temp_coordinate = new Coordinate();
        temp_coordinate->lat = (*min_dist_iterator)->lat;
        temp_coordinate->lng = (*min_dist_iterator)->lng;

        r_errands->push_back(temp_coordinate);

        iterator = *min_dist_iterator;
        v.erase(min_dist_iterator);
    }

    MapPoints * result = new MapPoints();

    Coordinate * r_origin = new Coordinate();
    r_origin->lat = origin->lat;
    r_origin->lng = origin->lng;

    Coordinate * r_destination = new Coordinate();
    r_destination->lat = destination->lat;
    r_destination->lat = destination->lng;

    result->origin = r_origin;
    result->destination = r_destination;
    result->errands = r_errands;

    return result;
}


/**
 * @return JSON encoding of the given struct
 */
void print_coordinates(MapPoints * map_points) {
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

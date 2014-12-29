#include <iostream>
#include <limits>

#include "map_points.h"
#include "haversine.h"

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

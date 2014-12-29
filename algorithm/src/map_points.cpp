#include <iostream>
#include <limits>

#include "map_points.h"
#include "haversine.h"

/**
 * @param The given data points
 * @return Some processing on this data (possibly)
 */
MapPoints * process_coordinates(MapPoints * map_points) {

    std::vector<Coordinate *> * unordered_errands = map_points->errands;
    std::vector<Coordinate *> * ordered_errands = new std::vector<Coordinate *>();

    Coordinate * pivot = map_points->origin;

    while (! unordered_errands->empty()) {
        double min_dist = std::numeric_limits<double>::max();
        std::vector<Coordinate *>::iterator min_dist_iterator;

        for (std::vector<Coordinate *>::iterator it = unordered_errands->begin();
                it != unordered_errands->end();
                it++) {
            double curr_dist = calculate_distance(*pivot, **it);
            if (curr_dist < min_dist) {
                min_dist = curr_dist;
                min_dist_iterator = it;
            }
        }

        pivot = *min_dist_iterator;
        ordered_errands->push_back(pivot);
        unordered_errands->erase(min_dist_iterator);
    }

    delete map_points->errands;
    map_points->errands = ordered_errands;

    return map_points;
}

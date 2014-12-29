#include "haversine.h"
#include "tube_network.h"
#include "simple_travel_time_computer.h"

#include <string>
#include <limits>

#include <iostream>

double SimpleTravelTimeComputer::find_time(const Coordinate& from,
                                           const Coordinate& to) {
    std::vector<TubeStation> nearest_to_origin = 
        tube.find_nearest_stations(from, 3);
    std::vector<TubeStation> nearest_to_destination = 
        tube.find_nearest_stations(to, 3);

    double tube_time = std::numeric_limits<double>::infinity();
    for (TubeStation orig : nearest_to_origin) {
        for (TubeStation dest : nearest_to_destination) {
            tube_time = std::min(tube_time,
                                 walk_time(from, orig.location) +
                                 tube.find_time_in_network(orig, dest) +
                                 walk_time(dest.location, to));
        }
    }

    return std::min(walk_time(from, to), tube_time);
}

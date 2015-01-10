#include "haversine.h"
#include "tube_network.h"
#include "simple_travel_time_computer.h"
#include "transit_type.h"

#include <string>
#include <limits>
#include <utility>

std::pair<double, transit_type>
SimpleTravelTimeComputer::find_time(const Coordinate& from, const Coordinate& to) {

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

    double walk_time_value = walk_time(from, to);

    if (walk_time_value < tube_time) {
        return std::make_pair(walk_time_value, WALKING);
    } else {
        return std::make_pair(tube_time, TRANSIT);
    }
}

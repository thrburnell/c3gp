#ifndef MAP_POINTS_H
#define MAP_POINTS_H

#include <memory>
#include <vector>

#include "coordinate.h"
#include "travel_time_computer.h"

struct MapPoints {
    Coordinate* origin;
    Coordinate* destination;
    std::vector<Coordinate*>* errands;
    std::string algorithm_to_use;
};

MapPoints* process_coordinates(MapPoints* map_points,
                               TravelTimeComputer* computer);

#endif /* MAP_POINTS_H */

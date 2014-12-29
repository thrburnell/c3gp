#ifndef MAP_POINTS_H
#define MAP_POINTS_H

#include <memory>
#include <vector>

struct Coordinate {
    double lat;
    double lng;
};

struct MapPoints {
    Coordinate * origin;
    Coordinate * destination;
    std::vector<Coordinate *> * errands;
};

MapPoints * process_coordinates(MapPoints * map_points);

#endif /* MAP_POINTS_H */

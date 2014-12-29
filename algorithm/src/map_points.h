#ifndef MAP_POINTS_H
#define MAP_POINTS_H

#include <memory>
#include <vector>

using std::unique_ptr;

struct Coordinate {
    double lat;
    double lng;
};

struct MapPoints {
    Coordinate * origin;
    Coordinate * destination;
    std::vector<Coordinate *> * errands;
};

MapPoints * parse_coordinates(const char * const json);
MapPoints * process_coordinates(MapPoints * map_points);
void print_coordinates(MapPoints * map_points);

#endif /* MAP_POINTS_H */

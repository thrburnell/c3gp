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
    unique_ptr<Coordinate> origin;
    unique_ptr<Coordinate> destination;
    unique_ptr<std::vector<unique_ptr<Coordinate>>> errands;
};

unique_ptr<MapPoints> parse_coordinates(const char * const json);
unique_ptr<MapPoints> process_coordinates(unique_ptr<MapPoints> map_points);
void print_coordinates(unique_ptr<MapPoints> map_points);

#endif /* MAP_POINTS_H */

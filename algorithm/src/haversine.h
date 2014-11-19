#ifndef HAVERSINE_H
#define HAVERSINE_H

#include "map_points.h"

static double calculate_distance(const Coordinate& origin,
                                 const Coordinate& destination);
static inline double to_radians(double d);
static inline bool are_valid_coordinates(const Coordinate& c);                   

#endif /* HAVERSINE_H */

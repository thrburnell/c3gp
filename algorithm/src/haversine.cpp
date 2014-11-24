#include <cmath>
#include <iostream>
#include <cassert>
#include <tuple>
#include "map_points.h"
#include "haversine.h"

/*
    PRE:    Takes two points, represented by two pairs of coordinates
            (latitude, longitude) - of type double - as input.

    POST:   If the provided coordinates are valid, returns the distance
            - of type double, in meters - between the two points using the
            Haversine Formula where:
                distance = 2 * (earth radius)
                             * arcsin (sqrt (
                                 (sin((lat1 - lat2)/2))^2
                                + cos(lat1) * cos(lat2)
                                            * (sin((lng1 - lng2)/2))^2
                                            )
                                      )
            Else, if at least one of the coordinates is invalid, returns -1.
*/
double calculate_distance(const Coordinate& origin,
                                 const Coordinate& destination) {

    /*  Check that the provided coordinates are valid */
    assert(are_valid_coordinates(origin));
    assert(are_valid_coordinates(destination));

    /* latitude and longitude of the origin in radians */
    double lat1 = to_radians(origin.lat);
    double lng1 = to_radians(origin.lng);

    /* latitude and longitude of the destination in radians */
    double lat2 = to_radians(destination.lat);
    double lng2 = to_radians(destination.lng);

    double dlat = lat1 - lat2;          /* difference of the two latitudes */
    double dlng = lng1 - lng2;          /* difference of the two longitudes */

    static const double earth_radius = 6371*1000;    /* in metres */

    double distance = 2 * (earth_radius)
                        * asin (sqrt( pow(sin((dlat)/2), 2)
                            + cos(lat1) * cos(lat2) * pow(sin((dlng)/2), 2)));

    return distance;                    /* in metres */
}


/*
    PRE:    Takes a double as input.
    POST:   Returns the input converted to radians.
*/
static inline double to_radians(double d) {
    return d * (M_PI/180);
}


/*
    PRE:    Takes a pair of double as input.
    POST:   Returns TRUE if the input is a valid coordinate, i.e its
            latitude is comprised between -90 and +90 degrees and its longitude
            is comprised between -180 and +180 degrees,
                    FALSE otherwise.
*/
static inline bool are_valid_coordinates(const Coordinate& c) {
    return c.lat >= -90  && c.lat <= 90
        && c.lng >= -180 && c.lng <= 180;
}

/* Commented out temporarily, for compatibility purposes with scons. Cannot
 * have more than one main() method.
int main() {
    double lat1;
    double lng1;

    double lat2;
    double lng2;

    std::cout << "Enter lat1:\n";
    std::cin >> lat1;
    std::cout << "Enter lng1:\n";
    std::cin >> lng1;
    std::cout << "Enter lat2:\n";
    std::cin >> lat2;
    std::cout << "Enter lng2:\n";
    std::cin >> lng2;
    std::cout << "\n";

    struct Coordinate origin;
    origin.lat = lat1;
    origin.lng = lng1;

    struct Coordinate destination;
    destination.lat = lat2;
    destination.lng = lng2;

    double distance = calculate_distance(origin, destination);
    assert(distance >= 0);

    if(distance >= 0) {
        std::cout << "The distance is: " << distance << "\n";
    }

    return 0;
}
*/

#ifndef COORDINATE_H
#define COORDINATE_H

#include "transit_type.h"

struct Coordinate {
    double lat;
    double lng;
    int group;

    // Represents the transit type (walking, public transport) to reach this point
    // Only used for the output
    transit_type transit;

    bool operator==(const Coordinate& other) const {
    	return other.lat == this->lat && other.lng == this->lng;
    }
};

#endif /* COORDINATE_H */

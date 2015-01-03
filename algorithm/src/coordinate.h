#ifndef COORDINATE_H
#define COORDINATE_H

struct Coordinate {
    double lat;
    double lng;

    bool operator==(const Coordinate& other) const {
    	return other.lat == this->lat && other.lng == this->lng;
    }
};

#endif /* COORDINATE_H */

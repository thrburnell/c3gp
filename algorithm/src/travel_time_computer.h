#ifndef TRAVEL_TIME_COMPUTER_H
#define TRAVEL_TIME_COMPUTER_H

#include "map_points.h"

class TravelTimeComputer {
public:
	virtual double find_time(const Coordinate& from,
		                     const Coordinate& to) = 0;
	virtual ~TravelTimeComputer() {};
};

#endif /* TRAVEL_TIME_COMPUTER_H */

#ifndef TRAVEL_TIME_COMPUTER_H
#define TRAVEL_TIME_COMPUTER_H

#include "coordinate.h"
#include "transit_type.h"

#include <utility>

class TravelTimeComputer {
public:
	virtual std::pair<double, transit_type> find_time(const Coordinate& from,
		                                              const Coordinate& to) = 0;
	virtual ~TravelTimeComputer() {};
};

#endif /* TRAVEL_TIME_COMPUTER_H */

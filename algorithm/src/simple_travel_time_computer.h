#ifndef SIMPLE_TRAVEL_TIME_COMPUTER_H
#define SIMPLE_TRAVEL_TIME_COMPUTER_H

#include "map_points.h"
#include "travel_time_computer.h"
#include "tube_network.h"

#include <string>

class SimpleTravelTimeComputer : public TravelTimeComputer {
/* This implementation considers both walking from the start to end point
 * using an adjusted form of the straight-line distance divided by a user's
 * walking speed, as well as walking to any of the three nearest tube stations,
 * taking the tube to one of the three nearest stations to the destination
 * and then walking to the destination.
 */
public:
    SimpleTravelTimeComputer(const std::string& tube_path,
        double walking_speed) : tube(tube_path), walk_speed(walking_speed)
        {};
    virtual double find_time(const Coordinate& from,
                             const Coordinate& to);
private:
    TubeNetwork tube;
    double walk_speed; // kilometers per hour

    // Constant indicating fudge factor introduced due to being unable to
    // physically walk the straight line distance between 2 points
    static constexpr double kFudge = 1.25;

    inline double walk_time(const Coordinate& from, const Coordinate& to) {
        // Converting km per hour to metres per minute.
        return calculate_distance(from, to) / (walk_speed * 1000 / 60)
               * kFudge;
    };
};

#endif /* SIMPLE_TRAVEL_TIME_COMPUTER_H */

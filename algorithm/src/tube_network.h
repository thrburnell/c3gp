#ifndef TUBE_NETWORK_H
#define TUBE_NETWORK_H

#include "transport_network.h"

#include <stdexcept>
#include <map>

// This implementation of the London tube network requires initialisation

class TubeStation : public TransportNode {
    // Has a location field, which stores coordinates of this station.

public:
    // Tests equality
    bool operator=(const TubeStation& other) {
        return other.location.lat == this->location.lat &&
               other.location.lng == this->location.lng;
    }

    // Tests less-than (needed for map data structure)
    bool operator<(const TubeStation& other) {
        return other.location.lat < this->location.lat ||
               (other.location.lat == this->location.lat &&
                other.location.lng < this->location.lng);
    }
};



class TubeNetwork : public TransportNetwork {
/* This implementation of the TubeNetwork assumes that all inter-station times
 * can be successfully cached and are loaded into the timings map.
 */

public:
    TubeNetwork() {
        // TODO Jeremy: Implement this method
    }

    double find_time_in_network(const TransportNode& origin,
                                const TransportNode& destination) {
        TubeStation *origin_station = dynamic_cast<TubeStation>(&origin);
        TubeStation *dest_station = dynamic_cast<TubeStation>(&destination);
        if (origin_station == nullptr || dest_station == nullptr) {
            // This happens if the dynamic_cast fails.
            throw std::domain_error("Origin or destination node is not " +
                                    "a tube station!");
        }

        // We can assume that both are tube stations from here on out.
        map<pair<TubeStation, TubeStation>, double>::iterator it =
            timings.find(std::make_pair(*origin_station, *dest_station));
        if (it == timings.end()) {
            throw std::domain_error("Tube stations can't be linked!");
        }
        return it->second;
    }

private:
    map<pair<TubeStation, TubeStation>, double> timings;

    // No copy construction or assignment construction, this is expensive.
    TubeNetwork(TubeNetwork const&);
    void operator=(TubeNetwork const&);
};

#endif /* TUBE_NETWORK_H */
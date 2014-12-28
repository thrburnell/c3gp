#ifndef TUBE_NETWORK_H
#define TUBE_NETWORK_H

#include "transport_network.h"

#include <stdexcept>
#include <map>

// This implementation of the London tube network requires initialisation
enum TubeLine {
    BAKERLOO,
    CENTRAL,
    CIRCLE,
    DISTRICT,
    HAMMERSMITH_AND_CITY,
    METROPOLITAN,
    NORTHERN,
    PICCADILLY,
    VICTORIA,
    WATERLOO_AND_CITY,
    UNDEFINED
};

class TubeStation : public TransportNode {
    // Has a location field, which stores coordinates of this station.
public:
    std::string name; // Station name.

    // Travel overhead if entering, changing or leaving here
    double travel_overhead = -1;

    // Adjacency list of TubeStations that this station connects to.
    std::vector<std::pair<std::pair<TubeStation*, TubeLine>, double>> edge_list;

    TubeStation(std::string st_name) : name(st_name) {};

    // Tests equality
    bool operator=(const TubeStation& other) const {
        return other.location.lat == this->location.lat &&
               other.location.lng == this->location.lng;
    }

    // Tests less-than (needed for map data structure)
    bool operator<(const TubeStation& other) const {
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

    virtual double find_time_in_network(const TransportNode& origin,
                                        const TransportNode& destination) {
        const TubeStation origin_station =
            static_cast<const TubeStation&>(origin);
        const TubeStation dest_station =
            static_cast<const TubeStation&>(destination);

        // We can assume that both are tube stations from here on out.
        std::map<std::pair<TubeStation, TubeStation>, double>::iterator it =
            timings.find(std::make_pair(origin_station, dest_station));
        if (it == timings.end()) {
            throw std::domain_error("Tube stations can't be linked!");
        }
        return it->second;
    }

private:
    std::map<std::pair<TubeStation, TubeStation>, double> timings;

    // No copy construction or assignment construction, this is expensive.
    TubeNetwork(TubeNetwork const&);
    void operator=(TubeNetwork const&);
};

#endif /* TUBE_NETWORK_H */
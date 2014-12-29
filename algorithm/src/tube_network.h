#ifndef TUBE_NETWORK_H
#define TUBE_NETWORK_H

#include "transport_network.h"

#include <stdexcept>
#include <map>
#include <iostream>

// This implementation of the London tube network requires initialisation
// from a file which is specified in the constructor.

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

    // Travel overhead if entering, changing or leaving here.
    // Do NOT use outside the Network Generator.
    double travel_overhead = -1;

    // Adjacency list of TubeStations that this station connects to.
    // Do NOT use outside the Network Generator.
    std::vector<std::pair<std::pair<TubeStation*, TubeLine>, double>> edge_list;

    TubeStation() {};
    TubeStation(std::string st_name) { name = st_name; };

    // Tests equality
    virtual bool operator=(const TubeStation& other) const {
        return this->name == other.name; // tube stations identifiable by name
    }

    // Tests less-than (needed for map data structure)
    virtual bool operator<(const TubeStation& other) const {
        return this->name < other.name;
    }
};



class TubeNetwork : public TransportNetwork {
/* This implementation of the TubeNetwork assumes that all inter-station times
 * can be successfully cached and are loaded into the timings map.
 */

public:
    // Path to a data file consisting of the network information.
    TubeNetwork(const std::string& path);

    virtual double find_time_in_network(const TransportNode& origin,
                                        const TransportNode& destination);

private:
    std::map<std::pair<TubeStation, TubeStation>, double> timings;

    // No copy construction or assignment construction, this is expensive.
    TubeNetwork(TubeNetwork const&);
    void operator=(TubeNetwork const&);
};

#endif /* TUBE_NETWORK_H */

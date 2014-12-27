#ifndef TRANSPORT_NETWORK_H
#define TRANSPORT_NETWORK_H

#include "map_points.h"

class TransportNode {
public:
    Coordinate location;

    virtual bool operator= (const TransportNode& other) {
        return this->location.lat == other.location.lat &&
               this->location.lng == other.location.lng;
    }

    virtual ~TransportNode() {};
};

class TransportNetwork {
public:
    virtual double find_time_in_network(const TransportNode& origin,
                                        const TransportNode& destination) = 0;

    virtual ~TransportNetwork() {};
};

#endif /* TRANSPORT_NETWORK_H */

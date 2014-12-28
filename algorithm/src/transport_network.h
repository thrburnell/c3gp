#ifndef TRANSPORT_NETWORK_H
#define TRANSPORT_NETWORK_H

#include "map_points.h"

class TransportNode {
public:
    Coordinate location;
};

class TransportNetwork {
public:
    virtual double find_time_in_network(const TransportNode& origin,
                                        const TransportNode& destination) = 0;
};

#endif /* TRANSPORT_NETWORK_H */
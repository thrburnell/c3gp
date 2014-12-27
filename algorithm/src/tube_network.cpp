#include "tube_network.h"
#include "csv_parser.h"
#include "distance_queue.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Finds the time required to get from the origin to the destination using
// this transport network (here, the Tube network).
// Assumes that origin and destination are points in the network.
double TubeNetwork::find_time_in_network(const TransportNode& origin,
                                         const TransportNode& destination) {
    const TubeStation origin_station =
        dynamic_cast<const TubeStation&>(origin);
    const TubeStation dest_station =
        dynamic_cast<const TubeStation&>(destination);

    // We can assume that both are tube stations from here on out.
    std::map<std::pair<TubeStation, TubeStation>, double>::iterator it =
        timings.find(std::make_pair(origin_station, dest_station));
    if (it == timings.end()) {
        throw std::domain_error("Tube stations can't be linked!");
    }
    return it->second;
}

// Constructor for the TubeNetwork class.
// This might be called with "data/tube_matrix.csv" as the path, if using
// the generated network.
TubeNetwork::TubeNetwork(const std::string& file_path) {
    std::ifstream ifs(file_path, std::ifstream::in);

    // Number of stations
    size_t N;
    ifs >> N;

    // Dump the extra newline after N.
    std::string str;
    std::getline(ifs, str);

    // Read N lines, for each station.
    stations.resize(N);
    for (int i = 0; i < N; ++i) {
        std::vector<std::string> data;
        csv_parse_next_line(&ifs, &data);

        stations[i].name = data[0];
        stations[i].location.lat = stod(data[1]);
        stations[i].location.lng = stod(data[2]);
    }

    // Read N lines for the adjacency matrix.
    for (int i = 0; i < N; ++i) {
        std::vector<std::string> data;
        csv_parse_next_line(&ifs, &data);

        for (int j = 0; j < N; ++j) {
            timings[std::make_pair(stations[i], 
                                   stations[j])] = stod(data[j]);
        }
    }
}

// Finds the nearest stations (by Euclidean distance) to a given point.
std::vector<TubeStation> TubeNetwork::find_nearest_stations
    (const Coordinate& c,
     int num_stations) {
    DistanceQueue queue(c, num_stations);
    for (const auto& station : stations) {
        queue.push(station.location);
    }
    std::vector<Coordinate> coordinates = queue.finish();

    std::vector<TubeStation> result;
    // O(num_stations * |stations|). Definitely not optimal but for our
    // purposes this is sufficient.
    for (const auto& coord : coordinates) {
        for (const auto& station : stations) {
            if(station.location == coord) {
                result.push_back(station);
            }
        }
    }
    return result;
}

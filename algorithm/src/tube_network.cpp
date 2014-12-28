#include "tube_network.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// This should really be in a utility, I know.
void split(const std::string& s, char delim, std::vector<std::string>* vec) {
    int i = 0;
    int j = s.find(delim);

    while (j != std::string::npos) {
        vec->push_back(s.substr(i, j-i));
        i = j + 1; // Could be ++j but this is clearer I think.
        j++;
        j = s.find(delim, j);

        if (j == std::string::npos) {
            vec->push_back(s.substr(i, s.size()));
        }
    }
}

void parse_csv(std::ifstream* ifs, std::vector<std::string>* data) {
    std::string str;
    std::getline(*ifs, str);
    split(str, ',', data);
}



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

// Constructor for the TubeNetwork class
TubeNetwork::TubeNetwork() {
    std::ifstream ifs("data/tube_matrix.csv", std::ifstream::in);

    // Number of stations
    size_t N;
    ifs >> N;

    // Dump the extra newline after N.
    std::string str;
    std::getline(ifs, str);

    // Read N lines, for each station.
    std::vector<TubeStation> tube_stations(N);
    for (int i = 0; i < N; ++i) {
        std::vector<std::string> data;
        parse_csv(&ifs, &data);

        tube_stations[i].name = data[0];
        tube_stations[i].location.lat = stod(data[1]);
        tube_stations[i].location.lng = stod(data[2]);
    }

    // Read N lines for the adjacency matrix.
    for (int i = 0; i < N; ++i) {
        std::vector<std::string> data;
        parse_csv(&ifs, &data);

        for (int j = 0; j < N; ++j) {
            timings[std::make_pair(tube_stations[i], 
                                   tube_stations[j])] = stod(data[j]);
        }
    }
}

int main(void) {
    TubeNetwork net;
    TubeStation s1("Sloane Square");
    s1.location.lat = 51.492359782932;
    s1.location.lng = -0.1564744555002;

    TubeStation s2("Knightsbridge");
    s2.location.lat = 51.501354916808;
    s2.location.lng = -0.16065008131194;

    TubeStation s3("Gloucester Road");
    s3.location.lat = 51.494499579725;
    s3.location.lng = -0.18352915689619;

    TubeStation s4("Heathrow Terminal 5");
    s4.location.lat = 51.470025485584;
    s4.location.lng = -0.49063310869077;

    std::cout << s1.name << std::endl;
    std::cout << s2.name << std::endl;
    std::cout << s3.name << std::endl;
    std::cout << s4.name << std::endl;

    std::cout << "The time taken from " << s1.name << " to " << s2.name << " is " << net.find_time_in_network(s1, s2) << std::endl;
    std::cout << "The time taken from " << s1.name << " to " << s3.name << " is " << net.find_time_in_network(s1, s3) << std::endl;
    std::cout << "The time taken from " << s1.name << " to " << s4.name << " is " << net.find_time_in_network(s1, s4) << std::endl;
    std::cout << "The time taken from " << s2.name << " to " << s3.name << " is " << net.find_time_in_network(s2, s3) << std::endl;
    std::cout << "The time taken from " << s2.name << " to " << s4.name << " is " << net.find_time_in_network(s2, s4) << std::endl;
    std::cout << "The time taken from " << s3.name << " to " << s4.name << " is " << net.find_time_in_network(s3, s4) << std::endl;
}
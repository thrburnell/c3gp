#include "../tube_network.h"
#include "../map_points.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

using std::string;
using std::vector;
using std::pair;

// Splits a string by delim, storing the results in vec.
void split(const string& s, char delim, vector<string>* vec) {
    int i = 0;
    int j = s.find(delim);

    while (j != string::npos) {
        vec->push_back(s.substr(i, j-i));
        i = j + 1;
        j++;
        j = s.find(delim, j);

        if (j == string::npos) {
            vec->push_back(s.substr(i, s.size()));
        }
    }
}

TubeLine get_line_index(const string& str) {
    // Note that switch-case doesn't work on strings.
    if (str == "Bakerloo") {
        return TubeLine::BAKERLOO;
    }
    if (str == "Central") {
        return TubeLine::CENTRAL;
    }
    if (str == "Circle") {
        return TubeLine::CIRCLE;
    }
    if (str == "District") {
        return TubeLine::DISTRICT;
    }
    if (str == "Hammersmith and City") {
        return TubeLine::HAMMERSMITH_AND_CITY;
    }
    if (str == "Metropolitan") {
        return TubeLine::METROPOLITAN;
    }
    if (str == "Northern") {
        return TubeLine::NORTHERN;
    }
    if (str == "Piccadilly") {
        return TubeLine::PICCADILLY;
    }
    if (str == "Victoria") {
        return TubeLine::VICTORIA;
    }
    if (str == "Waterloo and City") {
        return TubeLine::WATERLOO_AND_CITY;
    }
    // shouldn't happen actually.
    return TubeLine::UNDEFINED;
}

// Used to have the priority queue explore edges in the right order.
struct ReversePairComparator {
    bool operator() (const pair<double, pair<TubeStation*, TubeLine>>& lhs,
                     const pair<double, pair<TubeStation*, TubeLine>>& rhs){
        return lhs > rhs;
    }
};

int main(int argc, char** argv) {
    std::ifstream ifs ("tube_stations.csv", std::ifstream::in);
    string str;
    std::getline(ifs, str); // flush header line

    // Constants
    static const int kStationIndex = 0;
    static const int kLatitudeIndex = 3;
    static const int kLongitudeIndex = 4;    

    std::map<string, TubeStation*> tube_stations;

    while (std::getline(ifs, str)) {
        // Read each line, and build the list of nodes.
        vector<string> v;
        split(str, ',', &v);

        TubeStation *station = new TubeStation(v[0]);

        station->location.lat = stod(v[3]);
        station->location.lng = stod(v[4]);

        tube_stations.insert(std::make_pair(v[0], station));
    }
    std::cout << "Read in " << tube_stations.size() << " candidate stations." 
        << std::endl;

    ifs.close();
    ifs.open("tube_station_overhead.csv", std::ifstream::in);
    std::getline(ifs, str); // flush header line

    while (std::getline(ifs, str)) {
        // Read each line and use it to add the overhead of transitting through
        // each specific station.
        vector<string> v;
        split(str, ',', &v);

        if (tube_stations.find(v[0]) != tube_stations.end()) {
            tube_stations[v[0]]->travel_overhead = std::stoi(v[1]);            
        }
    }

    std::map<string, TubeStation*> valid_tube_stations;
    for (const auto& station : tube_stations) {
        // A bit of a hack to clean up the data file, which has some extra tube
        // stations (includes overground and DLR too).
        if (station.second->travel_overhead != -1) {
            valid_tube_stations.insert(station);
        }
    }
    std::cout << "Obtained " << valid_tube_stations.size() << " tube stations."
        << std::endl;

    // Build up the graph.
    ifs.close();
    ifs.open("tube_lines.csv", std::ifstream::in);
    std::getline(ifs, str); // flush header line (again).

    // Constants
    static const int kLineIndex = 0;
    static const int kFromStation = 1;
    static const int kToStation = 2;
    static const int kFromToWeight = 3;
    static const int kToFromWeight = 4;

    int edge_counter = 0;

    while (std::getline(ifs, str)) {
        // Read each line and use it to build up the adjacency lists in the
        // network.
        vector<string> v;
        split(str, ',', &v);

        TubeStation* first_station = valid_tube_stations[v[kFromStation]];
        TubeStation* second_station = valid_tube_stations[v[kToStation]];

        first_station->edge_list.push_back(
            std::make_pair(std::make_pair(second_station, 
                                          get_line_index(v[kLineIndex])),
            std::stod(v[kFromToWeight])));

        second_station->edge_list.push_back(
            std::make_pair(std::make_pair(first_station, 
                                          get_line_index(v[kLineIndex])),
            std::stod(v[kToFromWeight])));

        edge_counter++;
    }
    edge_counter *= 2;
    std::cout << "Constructed graph with " << edge_counter << " edges.\n"
        << "Now running simulation..." << std::endl;

    // Build up the network.

    // Constants - we can refine this later if necessary/desired
    static const double kTrainOverhead = 5.0;
    static const double kMaxDetourEstimate = 5.0;

    // This is NOT the most efficient algorithm (there are some overlapping
    // subproblems), but we don't expect to run this that often so it seems
    // fine to me. Output as an adjacency matrix (output graph is complete).
    // Output consists of: a list of stations alphabetically sorted,
    //                     followed by the corresponding adjacency matrix.
    int counter = 0;
    for (const auto& iter : valid_tube_stations) {
        // We run a Dijkstra-esque simulation using a priority queue.
        // This looks awkward but makes comparison/ordering of the queue
        // easier.
        std::cout << "Simulating " << iter.second->name << std::endl;
        std::priority_queue<pair<double, pair<TubeStation*, TubeLine>>,
                            vector<pair<double, 
                                        pair<TubeStation*, TubeLine>>>,
                            ReversePairComparator> queue;

        // Keep track of the best time to every possible station.
        std::map<string, double> best_time;

        // To travel from a station to itself takes no time.
        best_time[iter.second->name] = 0;

        // Initialise the queue with the first station.
        queue.push(std::make_pair(0, 
                        std::make_pair(iter.second, TubeLine::UNDEFINED)));

        while (!queue.empty()) {
            // std::cout << "Queue size: " << queue.size() << std::endl;
            pair<double, pair<TubeStation*, TubeLine>> curr = queue.top();
            queue.pop();

            TubeStation* curr_station = curr.second.first;
            TubeLine curr_line = curr.second.second;
            for (const auto& iter : curr_station->edge_list) {
                // Is this the best way to get to this stop?
                TubeStation* target_station = iter.first.first;
                string target_name = target_station->name;
                double dest_time = curr.first + iter.second;
                bool changed_train = (iter.first.second != curr_line &&
                                      curr_line != TubeLine::UNDEFINED);

                if (changed_train) {
                    // Factor in the overhead of changing trains.
                    // Not always perfect, but will do for now (think
                    // Circle-District vs Circle-Piccadilly at SK e.g.)
                    dest_time += kTrainOverhead +
                                 target_station->travel_overhead;
                }

                if (best_time.find(target_name) == best_time.end() ||
                    (best_time.find(target_name) != best_time.end() &&
                     best_time[target_name] > dest_time)) {
                    // So we have done better than the best_time seen so far.
                    best_time[target_name] = dest_time;
                }

                // Heuristic: If you didn't change then there's no way
                // to do better. If you did change then maybe (we consider
                // kMaxDetourEstimate the time we expect you might save)
                if ((changed_train && dest_time - kMaxDetourEstimate 
                        <= best_time[target_name]) ||
                    (!changed_train && dest_time == best_time[target_name])) {
                    // We explore travelling to this station.
                    queue.push(std::make_pair(dest_time,
                        std::make_pair(target_station, iter.first.second)));
                }

            }
            // queue.push(std::make_pair(transit_time_to_adj, adj.first));
        }
        if (++counter % 50 == 0) {
            std::cout << "Simulated " << counter << " stations." << std::endl;
        }

        if (counter == 247) {
            for(const auto& m : best_time) {
                std::cout << m.first << " " << m.second << std::endl;
            }
        }
    }

    // Debug sanity check
    for (const auto& p : tube_stations) {
//        std::cout << (p.second)->name << (p.second)->location.lat << (p.second)->location.lng << std::endl;
    }
}
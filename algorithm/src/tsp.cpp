#include <iostream>
#include <string>

#include "tsp.h"
#include "json_parse.h"
#include "map_points.h"
#include "simple_travel_time_computer.h"

using std::string;

int main() {

    static const double kStandardWalkSpeed = 5.0; // In km/h

    SimpleTravelTimeComputer sttc(
        "/vagrant/algorithm/src/data/tube_matrix.csv", kStandardWalkSpeed);

    // Weird way of getting a file into a char*
    string ss;
    getline(std::cin, ss);
    const char* const json = (const char* const) ss.c_str();

    MapPoints* mp = parse_coordinates(json);
    mp = process_coordinates(mp, &sttc);
    string result = print_coordinates(mp);

    std::cout << result;

    return EXIT_SUCCESS;
}

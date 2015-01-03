#include <iostream>
#include <string>

#include "tsp.h"
#include "json_parse.h"
#include "map_points.h"
#include "simple_travel_time_computer.h"

using std::string;

int main() {

    SimpleTravelTimeComputer sttc("data/tube_matrix.csv", 5.0);

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

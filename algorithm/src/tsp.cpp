#include <iostream>
#include <memory>
#include <string>

#include "tsp.h"
#include "map_points.h"

using std::unique_ptr;
using std::string;

int main() {

    // Weird way of getting a file into a char*
    string ss;
    getline(std::cin, ss);
    const char * const json = (const char * const) ss.c_str();

    MapPoints * mp = parse_coordinates(json);
    mp = process_coordinates(mp);
    print_coordinates(mp);

    return EXIT_SUCCESS;
}

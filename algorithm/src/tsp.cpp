#include <iostream>
#include <string>

#include "tsp.h"
#include "json_parse.h"
#include "map_points.h"

using std::string;

int main() {

    // Weird way of getting a file into a char*
    string ss;
    getline(std::cin, ss);
    const char* const json = (const char* const) ss.c_str();

    MapPoints* mp = parse_coordinates(json);
    mp = process_coordinates(mp);
    string result = print_coordinates(mp);

    std::cout << result;

    return EXIT_SUCCESS;
}

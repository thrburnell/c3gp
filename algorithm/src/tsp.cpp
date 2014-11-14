#include <iostream>
#include <memory>
#include <string>

#include "tsp.h"
#include "map_points.h"

using namespace std;

int main() {

    // Weird way of getting a file into a char*
    string ss;
    getline(cin, ss);
    char * json = (char*) ss.c_str();

    unique_ptr<MapPoints> mp = parse_coordinates(json);
    mp = process_coordinates(move(mp));
    print_coordinates(move(mp));


    return EXIT_SUCCESS;
}


#ifndef JSON_PARSE
#define JSON_PARSE

#include "map_points.h"

MapPoints* parse_coordinates(const char* const json);
std::string print_coordinates(MapPoints* map_points);

#endif /* JSON_PARSE */

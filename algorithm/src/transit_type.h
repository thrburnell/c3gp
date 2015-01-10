#ifndef TRANSIT_TYPE
#define TRANSIT_TYPE

#include <string>

enum transit_type {
	WALKING, TRANSIT
};

std::string transit_type_to_string(transit_type t);

#endif /* TRANSIT_TYPE */

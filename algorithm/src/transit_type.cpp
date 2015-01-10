#include "transit_type.h"

std::string transit_type_to_string(transit_type t) {
	switch (t) {
		case WALKING: return "walking";
		case TRANSIT: return "transit";
		default: return "";
	}
}

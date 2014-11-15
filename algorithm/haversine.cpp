#include <cmath>
#include <iostream>
#include <tuple>

using namespace std;

static double calculate_distance(pair<double, double> origin,
								 pair<double, double> destination);
static double radians(double d);
static bool valid_coordinates(pair<double, double> coordinate);								 

/*	
	PRE:	Takes two points, represented by two pairs of coordinates
			(latitude, longitude) - of type double - as input.

	POST: 	If the provided coordinates are valid, returns the distance
			- of type double - between the two points using the Haversine
			Formula where:
				distance = 2 * (earth radius)
							 * arcsin (sqrt	(
							 	 (sin((lat1 - lat2)/2))^2
							 	+ cos(lat1) * cos(lat2)
							 	  			* (sin((long1 - long2)/2))^2 
							 				)
							 		  )
			Else, if at least one of the coordinates is invalid, returns -1.
*/
static double calculate_distance(pair<double, double> origin,
								 pair<double, double> destination) {

	/* 	Check that the provided coordinates are valid */
	if(!valid_coordinates(origin)) {
		cout << "ERROR: The coordinates of the origin are invalid!\n";
		return -1;
	}

	if(!valid_coordinates(destination)) {
		cout << "ERROR: The coordinates of the destination are invalid!\n";
		return -1;
	}

	/* latitude and longitude of the origin in radians */
	double lat1  = radians(origin.first);		
	double long1 = radians(origin.second);		

	/* latitude and longitude of the destination in radians */
	double lat2  = radians(destination.first);
	double long2 = radians(destination.second);	

	double dlat  = lat1 - lat2;			/* difference of the two latitudes */
	double dlong = long1 - long2;		/* difference of the two longitudes */

	double earth_radius = 6371;			/* in kilometres */

	double distance = 2 * (earth_radius)
						* asin (sqrt( pow(sin((dlat)/2), 2)
						  	+ cos(lat1) * cos(lat2) * pow(sin((dlong)/2), 2)));

	return distance;					/* in kilometres */
}


/*
	PRE:	Takes a double as input.
	POST:	Returns the input converted to radians.
*/
static double radians(double d) {
	return d * (M_PI/180);
}


/*
	PRE:	Takes a pair of double as input.
	POST:	Returns TRUE if the input is a valid coordinate, i.e both its
			latitude and longitude are comprised between -90 and +90 degrees,
					FALSE otherwise.
*/
static bool valid_coordinates(pair<double, double> coordinate) {
	return coordinate.first >= -90 && coordinate.first <= 90
		&& coordinate.second >= -90 && coordinate.second <= 90;
}


int main() {
	double lat1;
	double long1;

	double lat2;
	double long2;

	cout << "Enter lat1:\n";
	cin >> lat1;
	cout << "Enter long1:\n";
	cin >> long1;
	cout << "Enter lat2:\n";
	cin >> lat2;
	cout << "Enter long2:\n";
	cin >> long2;
	cout << "\n";

	pair<double, double> origin = make_pair(lat1, long1);
	pair<double, double> destination = make_pair(lat2, long2);

	double distance = calculate_distance(origin, destination);

	if(distance >= 0) {
		cout << "The distance is: " << distance << "\n";
	}

	return 0;
}
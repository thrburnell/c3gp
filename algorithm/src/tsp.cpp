// rapidjson/example/simpledom/simpledom.cpp`
#include "lib/rapidjson/document.h"
#include "lib/rapidjson/writer.h"
#include "lib/rapidjson/stringbuffer.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <memory>

using namespace rapidjson;
using namespace std;


struct Coordinate {
    double lat;
    double lng;
};

struct MapPoints {
    unique_ptr<Coordinate> origin;
    unique_ptr<Coordinate> destination;
    unique_ptr<vector<unique_ptr<Coordinate>>> errands;
};

unique_ptr<MapPoints> parse_coordinates(char * json) {
    Document document;
    document.Parse(json);

    unique_ptr<MapPoints> mapPoints(new MapPoints);

    unique_ptr<Coordinate> origin(new Coordinate);
    origin->lat = document["origin"]["lat"].GetDouble();
    origin->lng = document["origin"]["lng"].GetDouble();

    unique_ptr<Coordinate> destination(new Coordinate);
    destination->lat = document["destination"]["lat"].GetDouble();
    destination->lng = document["destination"]["lng"].GetDouble();

    unique_ptr<vector<unique_ptr<Coordinate>>> errands(new vector<unique_ptr<Coordinate>>);

    const Value & waypoints = document["waypoints"];
    for (int i = 0; i < waypoints.Size(); i++) {
        unique_ptr<Coordinate> newCoordinate(new Coordinate);
        newCoordinate->lat = waypoints[i]["lat"].GetDouble();
        newCoordinate->lng = waypoints[i]["lng"].GetDouble();
        errands->push_back(move(newCoordinate));
    }

    mapPoints->origin = move(origin);
    mapPoints->destination = move(destination);
    mapPoints->errands = move(errands);

    return mapPoints;
}


unique_ptr<MapPoints> process_coordinates(unique_ptr<MapPoints> map_points) {

    return move(map_points);

}

void print_coordinates(unique_ptr<MapPoints> map_points) {

    StringBuffer s;
    Writer<StringBuffer> writer(s);

    writer.StartArray();

    for (auto it = map_points->errands->begin(); it != map_points->errands->end(); it++) {
        writer.StartObject();

        writer.String("lat");
        writer.Double((*it)->lat);


        writer.String("lng");
        writer.Double((*it)->lng);

        writer.EndObject();
    }

    writer.EndArray();

    cout << s.GetString() << endl;
}



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




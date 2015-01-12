#include <iostream>
#include <limits>
#include <utility>

#include "map_points.h"
#include "haversine.h"
#include "tsp_solver.h"
#include "travel_time_computer.h"
#include "transit_type.h"

/**
 * @param The given data points
 * @return Some processing on this data (possibly)
 */
MapPoints* process_coordinates(MapPoints* map_points,
                               TravelTimeComputer* time_computer) {


    if (map_points->algorithm_to_use == "gtsp") {

        return map_points;
    }

    std::vector<Coordinate*> points;
    points.push_back(map_points->origin);
    for (const auto& it : *map_points->errands) {
        points.push_back(it);
    }

    transit_type transit_matrix[points.size()][points.size()];

    TspSolver * tspSolver = new TspSolver();
    tspSolver->setNumberOfNodes(points.size());
    for (int i = 0; i < points.size(); i++) {
        for (int j = 0 ; j < points.size(); j++) {
            std::pair<double, transit_type> best_time = time_computer->find_time(*points[i], *points[j]);
            tspSolver->addPoint(i, j, best_time.first);
            transit_matrix[i][j] = best_time.second;
        }
    }
    tspSolver->setStartingPoint(0);
    std::vector<int>* nodesOrder = tspSolver->solveTsp();

    int last_point = nodesOrder->at(0);
    std::vector<Coordinate*>* ordered_errands = new std::vector<Coordinate*>();
    for (int i = 1; i < points.size(); i++) {
        int current_point = nodesOrder->at(i);
        points[current_point]->transit = transit_matrix[last_point][current_point];
        ordered_errands->push_back(points[current_point]);
        last_point = current_point;
    }
    map_points->errands = ordered_errands;

    map_points->destination->transit = transit_matrix[last_point][nodesOrder->at(0)];

    return map_points;
}

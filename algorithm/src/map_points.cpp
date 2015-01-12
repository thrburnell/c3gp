#include <iostream>
#include <limits>
#include <utility>

#include "map_points.h"
#include "haversine.h"
#include "solver.h"
#include "tsp_solver.h"
#include "gtsp_solver.h"
#include "travel_time_computer.h"
#include "transit_type.h"

/**
 * @param The given data points
 * @return Some processing on this data (possibly)
 */
MapPoints* process_coordinates(MapPoints* map_points,
                               TravelTimeComputer* time_computer) {

    std::vector<Coordinate*> points;
    points.push_back(map_points->origin);
    for (const auto& it : *map_points->errands) {
        points.push_back(it);
    }

    transit_type transit_matrix[points.size()][points.size()];

    Solver * solver;
    if (map_points->algorithm_to_use == "gtsp") {
        solver = new GtspSolver();
    } else {
        solver = new TspSolver();
    }

    solver->setNumberOfNodes(points.size());
    for (int i = 0; i < points.size(); i++) {
        for (int j = 0 ; j < points.size(); j++) {
            std::pair<double, transit_type> best_time = time_computer->find_time(*points[i], *points[j]);
            solver->addPoint(i, j, best_time.first);
            transit_matrix[i][j] = best_time.second;
        }
    }
    solver->setStartingPoint(0);

    if (map_points->algorithm_to_use == "gtsp") {
        for (int i = 0; i < points.size(); i++) {
            solver->setGroupForNode(i, points[i]->group);
        }
    }

    std::vector<int>* nodesOrder = solver->solve();

    int last_point = nodesOrder->at(0);
    std::vector<Coordinate*>* ordered_errands = new std::vector<Coordinate*>();
    for (int i = 1; i < nodesOrder->size(); i++) {
        int current_point = nodesOrder->at(i);
        points[current_point]->transit = transit_matrix[last_point][current_point];
        ordered_errands->push_back(points[current_point]);
        last_point = current_point;
    }
    map_points->errands = ordered_errands;

    map_points->destination->transit = transit_matrix[last_point][nodesOrder->at(0)];

    return map_points;
}

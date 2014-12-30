#include <iostream>
#include <limits>

#include "map_points.h"
#include "haversine.h"
#include "tsp_solver.h"


/**
 * @param The given data points
 * @return Some processing on this data (possibly)
 */
MapPoints* process_coordinates(MapPoints* map_points) {

    std::vector<Coordinate*> points;
    points.push_back(map_points->origin);
    for (const auto& it : *map_points->errands) {
        points.push_back(it);
    }

    TspSolver * tspSolver = new TspSolver();
    tspSolver->setNumberOfNodes(points.size());
    for (int i = 0; i < points.size(); i++) {
        for (int j = 0 ; j < points.size(); j++) {
            double distance = calculate_distance(*points[i], *points[j]);
            tspSolver->addPoint(i, j, distance);
        }
    }
    tspSolver->setStartingPoint(0);
    std::vector<int>* nodesOrder = tspSolver->solveTsp();

    std::vector<Coordinate*>* ordered_errands = new std::vector<Coordinate*>();
    for (int i = 1; i < points.size(); i++) {
        ordered_errands->push_back(points[nodesOrder->at(i)]);
    }
    map_points->errands = ordered_errands;

    return map_points;
}

#include "lib/gtest/gtest.h"

#include "gtsp_solver.h"

#include <future>
#include <vector>
#include <set>
#include <fstream>
#include <utility>

using std::pair;
using std::make_pair;

TEST(GtspSolverTest, GTSPSimpleCoordinates) {

    std::vector<pair<int, int>> points;
    points.push_back(make_pair(3, 3)); // Origin
    points.push_back(make_pair(3, 6)); // Group 1
    points.push_back(make_pair(3, 7)); // Group 1
    points.push_back(make_pair(7, 3)); // Group 2
    points.push_back(make_pair(9, 3)); // Group 2

    GtspSolver* solver = new GtspSolver();
    solver->setNumberOfNodes(5);
    solver->setStartingPoint(0);

    for (int i = 0; i < points.size(); i++) {
        for (int j = 0 ; j < points.size(); j++) {
            double x_leg = (points[i].first - points[j].first);
            double y_leg = (points[i].second - points[j].second);
            double distance = sqrt(x_leg * x_leg + y_leg * y_leg);
            solver->addPoint(i, j, distance);
        }
    }

    solver->setGroupForNode(0, 0);
    solver->setGroupForNode(1, 1);
    solver->setGroupForNode(2, 1);
    solver->setGroupForNode(3, 2);
    solver->setGroupForNode(4, 2);

    std::vector<int>* result = solver->solve();
    std::set<std::vector<int>> expected = {{0, 1, 3}, {0, 3, 1}};
    EXPECT_TRUE(expected.find(*result) != expected.end());
}

TEST(GtspSolverTest, GeneticAlgorithmSimpleCoordinates) {

    std::vector<pair<int, int>> points;
    points.push_back(make_pair(3, 3)); // Origin
    points.push_back(make_pair(3, 6)); // Group 1
    points.push_back(make_pair(3, 7)); // Group 1
    points.push_back(make_pair(7, 3)); // Group 2
    points.push_back(make_pair(9, 3)); // Group 2

    GtspSolver* solver = new GtspSolver();
    solver->setNumberOfNodes(5);
    solver->setStartingPoint(0);

    for (int i = 0; i < points.size(); i++) {
        for (int j = 0 ; j < points.size(); j++) {
            double x_leg = (points[i].first - points[j].first);
            double y_leg = (points[i].second - points[j].second);
            double distance = sqrt(x_leg * x_leg + y_leg * y_leg);
            solver->addPoint(i, j, distance);
        }
    }

    solver->setGroupForNode(0, 0);
    solver->setGroupForNode(1, 1);
    solver->setGroupForNode(2, 1);
    solver->setGroupForNode(3, 2);
    solver->setGroupForNode(4, 2);

    std::vector<int>* result = solver->solveGtspWithGeneticAlgorithm();
    std::set<std::vector<int>> expected = {{0, 1, 3}, {0, 3, 1}};
    EXPECT_TRUE(expected.find(*result) != expected.end());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

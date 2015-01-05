#include "lib/gtest/gtest.h"

#include "tsp_solver.h"

#include <future>
#include <vector>
#include <set>

static TspSolver* setupCanonicalTestExample() {
    TspSolver* solver = new TspSolver();
    solver->setNumberOfNodes(4);
    solver->setStartingPoint(0);

    for (int i = 0; i < 4; ++i) {
        solver->addPoint(i, i, 0);
    }
    solver->addPoint(0, 1, 1);
    solver->addPoint(0, 2, 2);
    solver->addPoint(0, 3, 500);
    solver->addPoint(1, 2, 1);
    solver->addPoint(1, 3, 2);
    solver->addPoint(2, 3, 1);
    solver->addPoint(1, 0, 1);
    solver->addPoint(2, 0, 2);
    solver->addPoint(3, 0, 500);
    solver->addPoint(2, 1, 1);
    solver->addPoint(3, 1, 2);
    solver->addPoint(3, 2, 1);

    return solver;
}

static TspSolver* setupLargeTestExample() {
    const int kNumNodes = 100;
    TspSolver* solver = new TspSolver();
    solver->setNumberOfNodes(kNumNodes);
    solver->setStartingPoint(0);

    for (int i = 0; i < kNumNodes; ++i) {
        for (int j = 0; j < kNumNodes; ++j) {
            solver->addPoint(i, j, 2);
        }
    }

    return solver;
}

TEST(TspSolverTest, MustInitialiseTotalNodes) {
    TspSolver solver;
    ASSERT_ANY_THROW(solver.addPoint(0, 1, 1));
}

TEST(TspSolverTest, CannotDefineOutOfRangeNodes) {
    TspSolver solver;
    solver.setNumberOfNodes(2);
    ASSERT_ANY_THROW(solver.addPoint(0, 2, 3));
    ASSERT_ANY_THROW(solver.addPoint(-1, 1, 3));
}

TEST(TspSolverTest, FailsOnInvalidStartingPoints) {
    TspSolver* solver = setupCanonicalTestExample();
    solver->setStartingPoint(-1);
    ASSERT_ANY_THROW(solver->solveTsp());
    solver->setStartingPoint(6); // The underlying graph has 4 nodes.
    ASSERT_ANY_THROW(solver->solveTsp());
}

TEST(TspSolverTest, NNGreedyWorks) {
    TspSolver* solver = setupCanonicalTestExample();

    // Nearest Neighbour heuristic explores the closest unvisited node.
    // The heuristic explores the nodes in order 0-1-2-3.
    // (The graph above is a particularly pathological case for this.)
    std::vector<int>* result = solver->solveTspWithNNGreedy();
    std::vector<int> expected = {0, 1, 2, 3};
    EXPECT_EQ(expected, *result);
}

TEST(TspSolverTest, BacktrackingWorks) {
    TspSolver* solver = setupCanonicalTestExample();

    // Backtracking should find one of the shortest tours, which is length
    // 6. Which one is returned doesn't really matter.
    std::vector<int>* result = solver->solveTspWithBacktracking();
    std::set<std::vector<int>> expected = {{0, 1, 3, 2}, {0, 2, 3, 1}};
    EXPECT_TRUE(expected.find(*result) != expected.end());
}

TEST(TspSolverTest, ChoosesBacktrackingAlgorithmForSmallCase) {
    TspSolver* solver = setupCanonicalTestExample();

    std::vector<int>* result = solver->solveTsp();

    // Since the number of points is small, the backtracking method should
    // be selected.
    std::set<std::vector<int>> expected = {{0, 1, 3, 2}, {0, 2, 3, 1}};
    EXPECT_TRUE(expected.find(*result) != expected.end());    
}

TEST(TspSolverTest, ChoosesNNGreedyAlgorithmForLargeCase) {
    // Lambda function, used to check timelimit (otherwise unsupported
    // by GoogleTest).
    auto timeLimitCheck = std::async(std::launch::async, [this]()->void {
        TspSolver* solver = setupLargeTestExample();

        // There are 100 nodes so backtracking will fail horribly.
        // The key is we don't want this to be overly slow.
        std::vector<int>* result = solver->solveTsp();
        return;
    });

    // The future above should complete itself in 1 second, or the test fails.
    EXPECT_TRUE(timeLimitCheck.wait_for(std::chrono::milliseconds(1000)) != 
                std::future_status::timeout);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

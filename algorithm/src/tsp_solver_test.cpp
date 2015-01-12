#include "lib/gtest/gtest.h"

#include "tsp_solver.h"

#include <future>
#include <vector>
#include <set>
#include <fstream>

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

static TspSolver* setup2OptTestExample() {
    TspSolver* solver = new TspSolver();
    solver->setNumberOfNodes(5);
    solver->setStartingPoint(0);

    for (int i = 0; i < 5; ++i) {
        solver->addPoint(i, i, 0);
    }
    solver->addPoint(0, 1, 1);
    solver->addPoint(0, 2, 2);
    solver->addPoint(0, 3, 2);
    solver->addPoint(0, 4, 1000);
    solver->addPoint(1, 2, 1);
    solver->addPoint(1, 3, 2);
    solver->addPoint(1, 4, 500);
    solver->addPoint(2, 3, 1);
    solver->addPoint(2, 4, 2);
    solver->addPoint(3, 4, 1);

    solver->addPoint(1, 0, 1);
    solver->addPoint(2, 0, 2);
    solver->addPoint(3, 0, 2);
    solver->addPoint(4, 0, 1000);
    solver->addPoint(2, 1, 1);
    solver->addPoint(3, 1, 2);
    solver->addPoint(4, 1, 500);
    solver->addPoint(3, 2, 1);
    solver->addPoint(4, 2, 2);
    solver->addPoint(4, 3, 1);

    return solver;
}

static TspSolver* setupLargeTestExample() {
    const int kNumNodes = 500;
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

static TspSolver* setupBenchmarkTestExample(const std::string& file_path,
                                            int numNodes) {
    TspSolver* solver = new TspSolver();
    solver->setNumberOfNodes(numNodes);
    solver->setStartingPoint(0);

    std::ifstream ifs(file_path, std::ifstream::in);
    for(int i = 0; i < numNodes; ++i) {
        for(int j = 0; j < numNodes; ++j) {
            double cost;
            ifs >> cost;
            solver->addPoint(i, j, cost);
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
    ASSERT_ANY_THROW(solver->solve());
    solver->setStartingPoint(6); // The underlying graph has 4 nodes.
    ASSERT_ANY_THROW(solver->solve());
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

TEST(TspSolverTest, NNGreedyWorksOnBiggerExample) {
    TspSolver* solver = setup2OptTestExample();

    // Nearest Neighbour heuristic explores the closest unvisited node.
    // The heuristic explores the nodes in order 0-1-2-3-4.
    std::vector<int>* result = solver->solveTspWithNNGreedy();
    std::vector<int> expected = {0, 1, 2, 3, 4};
    EXPECT_EQ(expected, *result);
}

TEST(TspSolverTest, NNGreedyWith2OptWorks) {
    TspSolver* solver = setupCanonicalTestExample();

    // 2-Opt should fix the Nearest Neighbour heuristic's mistake.
    std::vector<int>* result = solver->solveTspWithNNGreedy();
    solver->apply2OptLocalSearch(result);
    std::set<std::vector<int>> expected = {{0, 1, 3, 2}, {0, 2, 3, 1}};
    EXPECT_TRUE(expected.find(*result) != expected.end());
}

TEST(TspSolverTest, NNGreedyWith2OptWorksOnBiggerExample) {
    TspSolver* solver = setup2OptTestExample();

    // Again, 2-Opt should fix the Nearest Neighbour heuristic's mistake.
    std::vector<int>* result = solver->solveTspWithNNGreedy();
    solver->apply2OptLocalSearch(result);
    std::vector<int> expected = {0, 1, 2, 4, 3};
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

TEST(TspSolverTest, BacktrackingWorksOnBiggerExample) {
    TspSolver* solver = setup2OptTestExample();

    // The optimal tour is 0-1-2-4-3 with length 7.
    std::vector<int>* result = solver->solveTspWithBacktracking();
    std::vector<int> expected = {0, 1, 2, 4, 3};
    EXPECT_EQ(expected, *result);
}

TEST(TspSolverTest, FindsOptimalSolutionForSmallCase) {
    TspSolver* solver = setupCanonicalTestExample();

    std::vector<int>* result = solver->solve();

    // Since the number of points is small, we should find an optimal
    // solution.
    std::set<std::vector<int>> expected = {{0, 1, 3, 2}, {0, 2, 3, 1}};
    EXPECT_TRUE(expected.find(*result) != expected.end());
}

TEST(TspSolverTest, AllowsApproximateSolutionForLargeCase) {
    // Lambda function, used to check timelimit (otherwise unsupported
    // by GoogleTest).
    auto timeLimitCheck = std::async(std::launch::async, [this]()->void {
        TspSolver* solver = setupLargeTestExample();

        // There are 500 nodes so backtracking will fail horribly.
        // The key is we don't want this to be overly slow.
        std::vector<int>* result = solver->solve();
        return;
    });

    // The future above should complete itself in 1 second, or the test fails.
    EXPECT_TRUE(timeLimitCheck.wait_for(std::chrono::milliseconds(1000)) !=
                std::future_status::timeout);
}

TEST(TspSolverTest, ApproximateSolutionForBR17Benchmark) {
    // Lambda function, used to check timelimit (otherwise unsupported
    // by GoogleTest).
    auto timeLimitCheck = std::async(std::launch::async, [this]()->void {
        TspSolver* solver = setupBenchmarkTestExample("testData/br17.atsp",
                                                      17);
        std::vector<int>* result = solver->solve();
        // Optimal solution is 39.
        EXPECT_LE(solver->computeTourWeight(result), 39 * 1.1);
        return;
    });

    // The future above should complete itself in 1 second, or the test fails.
    EXPECT_TRUE(timeLimitCheck.wait_for(std::chrono::milliseconds(1000)) !=
                std::future_status::timeout);
}

TEST(TspSolverTest, ApproximateSolutionForFTV44Benchmark) {
    // Lambda function, used to check timelimit (otherwise unsupported
    // by GoogleTest).
    auto timeLimitCheck = std::async(std::launch::async, [this]()->void {
        TspSolver* solver = setupBenchmarkTestExample("testData/ftv44.atsp",
                                                      44);
        std::vector<int>* result = solver->solve();
        // Optimal solution is 1613.
        EXPECT_LE(solver->computeTourWeight(result), 1613 * 1.5);
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

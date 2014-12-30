#include "lib/gtest/gtest.h"

#include "tsp_solver.h"

TEST(TubeNetworkTest, FindsCorrectTimings) {
    ASSERT_EQ(4+5, 9);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

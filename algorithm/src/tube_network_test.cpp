#include "lib/gtest/gtest.h"

#include "tube_network.h"

TEST(TubeNetworkTest, FindsCorrectTimings) {
    TubeNetwork net("testData/fake_tube_network.csv");

    TubeStation alpha("Alpha");
    TubeStation beta("Beta");
    TubeStation gamma("Gamma");

    ASSERT_EQ(net.find_time_in_network(alpha, alpha), 0);
    ASSERT_EQ(net.find_time_in_network(alpha, beta), 10.0);
    ASSERT_EQ(net.find_time_in_network(alpha, gamma), 20.0);
    ASSERT_EQ(net.find_time_in_network(beta, alpha), 9.0);
    ASSERT_EQ(net.find_time_in_network(beta, beta), 0.0);
    ASSERT_EQ(net.find_time_in_network(beta, gamma), 40.0);
    ASSERT_EQ(net.find_time_in_network(gamma, alpha), 19.0);
    ASSERT_EQ(net.find_time_in_network(gamma, beta), 39.0);
    ASSERT_EQ(net.find_time_in_network(gamma, gamma), 0.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

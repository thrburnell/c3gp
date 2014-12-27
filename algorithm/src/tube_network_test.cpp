#include "lib/gtest/gtest.h"

#include "tube_network.h"
#include "map_points.h"

TEST(TubeNetworkTest, FindsCorrectTimings) {
    TubeNetwork net("testData/fake_tube_network.csv");

    TubeStation alpha("Alpha");
    TubeStation beta("Beta");
    TubeStation gamma("Gamma");

    ASSERT_EQ(0, net.find_time_in_network(alpha, alpha));
    ASSERT_EQ(10.0, net.find_time_in_network(alpha, beta));
    ASSERT_EQ(20.0, net.find_time_in_network(alpha, gamma));
    ASSERT_EQ(9.0, net.find_time_in_network(beta, alpha));
    ASSERT_EQ(0.0, net.find_time_in_network(beta, beta));
    ASSERT_EQ(4.0, net.find_time_in_network(beta, gamma));
    ASSERT_EQ(19.0, net.find_time_in_network(gamma, alpha));
    ASSERT_EQ(39.0, net.find_time_in_network(gamma, beta));
    ASSERT_EQ(0.0, net.find_time_in_network(gamma, gamma));
}

TEST(TubeNetworkTest, FindsNearestStations) {
    TubeNetwork net("testData/fake_tube_network.csv");
    Coordinate c1;
    c1.lat = 0;
    c1.lng = 0;
    std::vector<TubeStation> closest_1 = net.find_nearest_stations(c1, 1);
    std::vector<TubeStation> closest_2 = net.find_nearest_stations(c1, 2);
    std::vector<TubeStation> closest_3 = net.find_nearest_stations(c1, 3);
    std::vector<TubeStation> closest_4 = net.find_nearest_stations(c1, 4);

    ASSERT_EQ(1, closest_1.size());
    ASSERT_EQ("Alpha", closest_1[0].name);

    ASSERT_EQ(2, closest_2.size());
    ASSERT_EQ("Alpha", closest_2[0].name);
    ASSERT_EQ("Beta", closest_2[1].name);

    ASSERT_EQ(3, closest_3.size());
    ASSERT_EQ("Alpha", closest_3[0].name);
    ASSERT_EQ("Beta", closest_3[1].name);
    ASSERT_EQ("Gamma", closest_3[2].name);

    // There are only three stations, so closest_4 = closest_3.
    ASSERT_EQ(3, closest_4.size());
    ASSERT_EQ("Alpha", closest_4[0].name);
    ASSERT_EQ("Beta", closest_4[1].name);
    ASSERT_EQ("Gamma", closest_4[2].name);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

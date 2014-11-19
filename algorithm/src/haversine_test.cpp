#include "lib/gtest/gtest.h"

#include "haversine.h"
#include "map_points.h"

TEST(CalculateDistanceTest, CalculatesZeroDistanceCorrectly) {
    Coordinate c1;
    c1.lat = 0.3;
    c1.lng = 0.3;
    EXPECT_EQ(0, calculate_distance(c1, c1));
    c1.lat = -43.27;
    c1.lng = -43.27;
    EXPECT_EQ(0, calculate_distance(c1, c1));
}

TEST(CalculateDistanceTest, CalculatesGreatCircleDistancesCorrectly) {
    Coordinate c1;
    c1.lat = 36;
    c1.lng = 36;
    Coordinate c2;
    c2.lat = -36;
    c2.lng = -36;
    EXPECT_DOUBLE_EQ(10923257.61276965, calculate_distance(c1, c2));
    EXPECT_DOUBLE_EQ(10923257.61276965, calculate_distance(c2, c1));
}

TEST(CalculateDistanceTest, CalculatesRoundTheWorldDistancesCorrectly) {
    Coordinate c1;
    c1.lat = 0;
    c1.lng = -180;
    Coordinate c2;
    c2.lat = 0;
    c2.lng = -179;
    EXPECT_DOUBLE_EQ(111194.92664455747, calculate_distance(c1, c2));

    // Check going in the other direction.
    c2.lng = 179;
    EXPECT_DOUBLE_EQ(111194.92664455905, calculate_distance(c1, c2));
}

TEST(CalculateDistanceTest, CalculatesImperialToSKDistanceCorrectly) {
    Coordinate c1;
    c1.lat = 51.4988;
    c1.lng = -0.174877;
    Coordinate c2;
    c2.lat = 51.494072;
    c2.lng = -0.173898;
    EXPECT_DOUBLE_EQ(530.0798892133387, calculate_distance(c1, c2));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

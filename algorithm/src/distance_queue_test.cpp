#include "lib/gtest/gtest.h"

#include "haversine.h"
#include "map_points.h"
#include "distance_queue.h"

TEST(DistanceQueueTest, KeepsCorrectPoints) {
    Coordinate c1;
    c1.lat = 0.3;
    c1.lng = 0.3;
    DistanceQueue dq(c1, 3);

    Coordinate c2;
    c2.lat = 0.4;
    c2.lng = 0.3;
    dq.push(c2);

    c2.lat = 0.1;
    dq.push(c2);

    c2.lat = 2;
    dq.push(c2);

    c2.lat = 1;
    dq.push(c2);

    // Clearly, the closest point is the one with lat 0.4, then 0.1, then 1.
    // Since we keep three points, the point with lat 2 shouldn't be in the
    // output at all.
    std::vector<Coordinate> v = dq.finish();

    ASSERT_EQ(v[0].lat, 0.4);
    ASSERT_EQ(v[1].lat, 0.1);
    ASSERT_EQ(v[2].lat, 1);
    ASSERT_EQ(v.size(), 3);
}

TEST(DistanceQueueTest, KeepsAllPointsUpToThree) {
    Coordinate c1;
    c1.lat = 0.3;
    c1.lng = 0.3;
    DistanceQueue dq(c1, 3);

    Coordinate c2;
    c2.lat = 0.4;
    c2.lng = 0.3;
    dq.push(c2);

    c2.lat = -89;
    dq.push(c2);

    c2.lat = 89;
    dq.push(c2);

    // The closest point should be the one at 0.4, then 89, then -89.
    // But we should keep all of them.
    std::vector<Coordinate> v = dq.finish();

    ASSERT_EQ(v[0].lat, 0.4);
    ASSERT_EQ(v[1].lat, 89);
    ASSERT_EQ(v[2].lat, -89);
    ASSERT_EQ(v.size(), 3);
}

TEST(DistanceQueueTest, KeepsOnePoint) {
    Coordinate c1;
    c1.lat = 0.3;
    c1.lng = 0.3;
    DistanceQueue dq(c1, 3);

    Coordinate c2;
    c2.lat = 0.4;
    c2.lng = 0.3;
    dq.push(c2);

    // We should keep the one point.
    std::vector<Coordinate> v = dq.finish();

    ASSERT_EQ(v[0].lat, 0.4);
    ASSERT_EQ(v.size(), 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

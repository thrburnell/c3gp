#include "lib/gtest/gtest.h"

#include "map_points.h"
#include "simple_travel_time_computer.h"

TEST(MapPointsTest, OrdersPointsAsExpected) {

    MapPoints* mp = new MapPoints();
    mp->errands = new std::vector<Coordinate*>();

    // I know, this looks weird, but this is how multiple declaration of
    // pointers looks like in C++.
    Coordinate *c1, *c2, *c3, *c4, *c5;

    c1 = new Coordinate();
    c1->lat = 50;
    c1->lng = 50;
    mp->origin = c1;
    mp->destination = c1;

    c2 = new Coordinate();
    c2->lat = 51;
    c2->lng = 50;
    mp->errands->push_back(c2);

    c3 = new Coordinate();
    c3->lat = 53;
    c3->lng = 50;
    mp->errands->push_back(c3);

    c4 = new Coordinate();
    c4->lat = 55;
    c4->lng = 50;
    mp->errands->push_back(c4);

    SimpleTravelTimeComputer sttc("testData/fake_tube_network.csv", 5.0);

    // The fake tube network is essentially useless for this test case.
    mp = process_coordinates(mp, &sttc);

    // The correct solution is to travel a straight line from c1 out,
    // walking 10 degrees total in terms of latitude. Note that comparison
    // is nontrivial since there are many valid routes; it would be sufficient
    // to ensure that there is a unique local maximum at the furthest point out
    // but this is also OK.
    double distance = abs(((*(mp->errands))[0])->lat - 
                          (mp->origin)->lat);
    for(int i = 1; i < 3; ++i) {
        distance += abs(((*(mp->errands))[i])->lat - 
                        ((*(mp->errands))[i - 1])->lat);
    }
    distance += abs(((*(mp->errands))[2])->lat - 
                    (mp->destination)->lat);

    ASSERT_DOUBLE_EQ(10, distance);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

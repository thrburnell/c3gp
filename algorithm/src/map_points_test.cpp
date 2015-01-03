#include "lib/gtest/gtest.h"

#include "map_points.h"

// TODO: As Jeremy was saying, this is a crappy test. We cannot manually
// see that these coordinates will come in this order. This will be
// moved anyway, as this logic is now part of the TspSolver class
TEST(MapPointsTest, OrdersPointsAsExpected) {

    MapPoints* mp = new MapPoints();
    mp->errands = new std::vector<Coordinate*>();

    Coordinate* c;

    c = new Coordinate();
    c->lat = 51.497843351035144;
    c->lng = -0.1702022552285598;
    mp->errands->push_back(c);

    c = new Coordinate();
    c->lat = 51.497629616981214;
    c->lng = -0.17346382139066918;
    mp->errands->push_back(c);

    c = new Coordinate();
    c->lat = 51.49841775633878;
    c->lng = -0.17533063886503442;
    mp->errands->push_back(c);

    c = new Coordinate();
    c->lat = 51.497910142721445;
    c->lng = -0.17936468122343285;
    mp->errands->push_back(c);

    c = new Coordinate();
    c->lat = 51.495759401256;
    c->lng = -0.1717901229653762;
    mp->errands->push_back(c);

    c = new Coordinate();
    c->lat = 51.49644070301275;
    c->lng = -0.17026662824491723;
    mp->errands->push_back(c);

    c = new Coordinate();
    c->lat = 51.50055501480524;
    c->lng = -0.17445087432861328;
    mp->origin = c;

    c = new Coordinate();
    c->lat = 51.50055501480524;
    c->lng = -0.17445087432861328;
    mp->destination = c;

    // TODO jeremykong: Clean up this test.
    // mp = process_coordinates(mp);

    // EXPECT_EQ(mp->errands->at(0)->lat, 51.497843351035147);
    // EXPECT_EQ(mp->errands->at(0)->lng, -0.1702022552285598);

    // EXPECT_EQ(mp->errands->at(1)->lat, 51.49644070301275);
    // EXPECT_EQ(mp->errands->at(1)->lng, -0.17026662824491724);

    // EXPECT_EQ(mp->errands->at(2)->lat, 51.495759401256);
    // EXPECT_EQ(mp->errands->at(2)->lng, -0.1717901229653762);

    // EXPECT_EQ(mp->errands->at(3)->lat, 51.497629616981217);
    // EXPECT_EQ(mp->errands->at(3)->lng, -0.17346382139066919);

    // EXPECT_EQ(mp->errands->at(4)->lat, 51.49841775633878);
    // EXPECT_EQ(mp->errands->at(4)->lng, -0.17533063886503442);

    // EXPECT_EQ(mp->errands->at(5)->lat, 51.497910142721448);
    // EXPECT_EQ(mp->errands->at(5)->lng, -0.17936468122343286);

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

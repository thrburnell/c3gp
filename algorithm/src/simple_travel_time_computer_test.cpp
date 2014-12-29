#include "lib/gtest/gtest.h"

#include "haversine.h"
#include "map_points.h"
#include "simple_travel_time_computer.h"

TEST(SimpleTravelTimeComputerTest, IdentityTimeIsZero) {
    SimpleTravelTimeComputer sttc("../testData/fake_tube_network.csv", 5.0);
    Coordinate c1;

    c1.lat = 0.3;
    c1.lng = 0.3;
    EXPECT_EQ(0, sttc.find_time(c1, c1));

    c1.lat = -38.88;
    c1.lng = 51.72;
    EXPECT_EQ(0, sttc.find_time(c1, c1));
}

TEST(SimpleTravelTimeComputerTest, DoesntUseTubeUnlessUseful) {
    SimpleTravelTimeComputer sttc("testData/fake_tube_network.csv", 5.0);
    Coordinate alpha;
    alpha.lat = 0;
    alpha.lng = 0;
    Coordinate beta;
    beta.lng = 0.000001;
    beta.lat = 0.000001;

    // There is a (useless) tube connection taking 10 minutes from alpha to
    // beta, which should not be used.
    EXPECT_NEAR(0.681431, sttc.find_time(alpha, beta), 0.00001);
}

TEST(SimpleTravelTimeComputerTest, ConsidersNearbyTubeStops) {
    SimpleTravelTimeComputer sttc("testData/fake_tube_network.csv", 5.0);
    Coordinate alpha;
    alpha.lat = 0;
    alpha.lng = 0;
    Coordinate gamma;
    gamma.lng = 0.5;
    gamma.lat = 0.5;

    // Walk to the station Beta (0.681431 min) and take the 4-minute train
    // from there instead of the 20-minute train from Alpha.
    EXPECT_NEAR(4.68143, sttc.find_time(alpha, gamma), 0.00001);
}

TEST(SimpleTravelTimeComputerTest, ChoosesCorrectStoppingPoint) {
    SimpleTravelTimeComputer sttc("testData/fake_tube_network.csv", 5.0);
    Coordinate ab_midpoint;
    ab_midpoint.lat = 0.0000005;
    ab_midpoint.lng = 0.0000005;
    Coordinate gamma;
    gamma.lng = 0.5;
    gamma.lat = 0.5;

    // It's faster to take the train back to alpha and walk than to beta.
    EXPECT_NEAR(19.340715, sttc.find_time(gamma, ab_midpoint), 0.00001);
}

TEST(EdgeFindingIntegrationTest, SloaneSquareToGloucesterRoad) {
    SimpleTravelTimeComputer sttc("src/data/tube_matrix.csv", 5.0);
    Coordinate sloane_square;
    sloane_square.lat = 51.492359782932;
    sloane_square.lng = -0.1564744555002;
    Coordinate gloucester_road;
    gloucester_road.lat = 51.494499579725;
    gloucester_road.lng = -0.18352915689619;

    EXPECT_NEAR(12, sttc.find_time(sloane_square, gloucester_road), 3);
}

TEST(EdgeFindingIntegrationTest, SloaneSquareToKnightsbridge) {
    // This must be quite a bit worse than the Gloucester Road one, since
    // we need to change trains.
    SimpleTravelTimeComputer sttc("src/data/tube_matrix.csv", 5.0);
    Coordinate sloane_square;
    sloane_square.lat = 51.492359782932;
    sloane_square.lng = -0.1564744555002;
    Coordinate knightsbridge;
    knightsbridge.lat = 51.501354916808;
    knightsbridge.lng = -0.16065008131194;

    EXPECT_NEAR(18, sttc.find_time(sloane_square, knightsbridge), 3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

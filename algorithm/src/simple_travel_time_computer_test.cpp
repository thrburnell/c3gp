#include "lib/gtest/gtest.h"

#include "haversine.h"
#include "map_points.h"
#include "simple_travel_time_computer.h"

TEST(SimpleTravelTimeComputerTest, IdentityTimeIsZero) {
    SimpleTravelTimeComputer sttc("testData/fake_tube_network.csv", 5.0);
    Coordinate c1;

    c1.lat = 0.3;
    c1.lng = 0.3;
    EXPECT_EQ(0, sttc.find_time(c1, c1).first);

    c1.lat = -38.88;
    c1.lng = 51.72;
    EXPECT_EQ(0, sttc.find_time(c1, c1).first);
}

TEST(SimpleTravelTimeComputerTest, DoesntUseTubeUnlessUseful) {
    SimpleTravelTimeComputer sttc("testData/fake_tube_network.csv", 5.0);
    Coordinate alpha;
    alpha.lat = 0;
    alpha.lng = 0;
    Coordinate beta;
    beta.lng = 0.0001;
    beta.lat = 0.0001;

    // There is a (useless) tube connection taking 20 minutes from alpha to
    // beta, which should not be used.
    EXPECT_NEAR(0.23588, sttc.find_time(alpha, beta).first, 0.00001);
}

TEST(SimpleTravelTimeComputerTest, ConsidersNearbyTubeStops) {
    SimpleTravelTimeComputer sttc("testData/fake_tube_network.csv", 5.0);
    Coordinate alpha;
    alpha.lat = 0;
    alpha.lng = 0;
    Coordinate gamma;
    gamma.lng = 5;
    gamma.lat = 5;

    // Walk to the station Beta (0.23588 min) and take the 4-minute train
    // from there instead of the 20-minute train from Alpha.
    EXPECT_NEAR(4.23588, sttc.find_time(alpha, gamma).first, 0.00001);
}

TEST(SimpleTravelTimeComputerTest, ChoosesCorrectStoppingPoint) {
    SimpleTravelTimeComputer sttc("testData/fake_tube_network.csv", 5.0);
    Coordinate ab_midpoint;
    ab_midpoint.lat = 0.00005;
    ab_midpoint.lng = 0.00005;
    Coordinate gamma;
    gamma.lng = 5;
    gamma.lat = 5;

    // It's faster to take the train back to alpha and walk than to beta.
    EXPECT_NEAR(19.11794, sttc.find_time(gamma, ab_midpoint).first, 0.00001);
}

TEST(EdgeFindingIntegrationTest, SloaneSquareToGloucesterRoad) {
    SimpleTravelTimeComputer sttc("src/data/tube_matrix.csv", 5.0);
    Coordinate sloane_square;
    sloane_square.lat = 51.492359782932;
    sloane_square.lng = -0.1564744555002;
    Coordinate gloucester_road;
    gloucester_road.lat = 51.494499579725;
    gloucester_road.lng = -0.18352915689619;

    EXPECT_NEAR(12, sttc.find_time(sloane_square, gloucester_road).first, 1);
}

TEST(EdgeFindingIntegrationTest, SloaneSquareToKnightsbridge) {
    // This must be quite a bit worse than the Gloucester Road one, since
    // we need to change trains. In fact it's not recommended you take the
    // tube at all, even.
    SimpleTravelTimeComputer sttc("src/data/tube_matrix.csv", 5.0);
    Coordinate sloane_square;
    sloane_square.lat = 51.492359782932;
    sloane_square.lng = -0.1564744555002;
    Coordinate knightsbridge;
    knightsbridge.lat = 51.501354916808;
    knightsbridge.lng = -0.16065008131194;

    EXPECT_NEAR(16, sttc.find_time(sloane_square, knightsbridge).first, 1);
}

TEST(EdgeFindingIntegrationTest, PiccadilyCircusToTottenhamCourtRoad) {
    // Do not take the tube. It'll only slow you down.
    SimpleTravelTimeComputer sttc("src/data/tube_matrix.csv", 5.0);
    Coordinate pc;
    pc.lat = 51.509696764476;
    pc.lng = -0.13369718974012;
    Coordinate tcr;
    tcr.lat = 51.51621088565;
    tcr.lng = -0.13109602942553;

    EXPECT_NEAR(11.195, sttc.find_time(pc, tcr).first, 1);
}

TEST(EdgeFindingIntegrationTest, PiccadilyCircusToLeicesterSquare) {
    // MUCH faster to walk than take the tube!
    SimpleTravelTimeComputer sttc("src/data/tube_matrix.csv", 5.0);
    Coordinate pc;
    pc.lat = 51.509696764476;
    pc.lng = -0.13369718974012;
    Coordinate ls;
    ls.lat = 51.511291196842;
    ls.lng = -0.12822773962177;

    EXPECT_NEAR(6.2696, sttc.find_time(pc, ls).first, 1);
}

TEST(EdgeFindingIntegrationTest, UxbridgeToCockfosters) {
    // Definitely take the tube for this one.
    SimpleTravelTimeComputer sttc("src/data/tube_matrix.csv", 5.0);
    Coordinate ux;
    ux.lat = 51.546454564696;
    ux.lng = -0.47708714109832;
    Coordinate cf;
    cf.lat = 51.652024496788;
    cf.lng = -0.14990225857042;

    EXPECT_NEAR(87.25, sttc.find_time(ux, cf).first, 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

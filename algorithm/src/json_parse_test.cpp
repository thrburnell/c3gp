#include "lib/gtest/gtest.h"

#include "json_parse.h"
#include "map_points.h"

using std::string;

TEST(MapPointsTest, CanParseJSONObjectsCorrectly) {
	string json = "{\"origin\":{\"lat\":51.50055501480524,\"lng\":-0.17445087432861328},\"destination\":{\"lat\":51.50055501480524,\"lng\":-0.17445087432861328},\"waypoints\":[{\"lat\":51.497843351035144,\"lng\":-0.1702022552285598},{\"lat\":51.497629616981214,\"lng\":-0.17346382139066918},{\"lat\":51.49841775633878,\"lng\":-0.17533063886503442},{\"lat\":51.497910142721445,\"lng\":-0.17936468122343285},{\"lat\":51.495759401256,\"lng\":-0.1717901229653762},{\"lat\":51.49644070301275,\"lng\":-0.17026662824491723}]}\n";
	MapPoints * mp = parse_coordinates(json.c_str());

	EXPECT_EQ(mp->origin->lat, 51.50055501480524);
	EXPECT_EQ(mp->origin->lng, -0.17445087432861328);

	EXPECT_EQ(mp->destination->lat, 51.50055501480524);
	EXPECT_EQ(mp->destination->lng, -0.17445087432861328);
}

TEST(MapPointsTest, CanParseErrandsCorrectly) {
	string json = "{\"origin\":{\"lat\":51.50055501480524,\"lng\":-0.17445087432861328},\"destination\":{\"lat\":51.50055501480524,\"lng\":-0.17445087432861328},\"waypoints\":[{\"lat\":51.497843351035144,\"lng\":-0.1702022552285598},{\"lat\":51.497629616981214,\"lng\":-0.17346382139066918},{\"lat\":51.49841775633878,\"lng\":-0.17533063886503442},{\"lat\":51.497910142721445,\"lng\":-0.17936468122343285},{\"lat\":51.495759401256,\"lng\":-0.1717901229653762},{\"lat\":51.49644070301275,\"lng\":-0.17026662824491723}]}\n";
	MapPoints * mp = parse_coordinates(json.c_str());

	EXPECT_EQ(mp->errands->at(0)->lat, 51.497843351035144);
	EXPECT_EQ(mp->errands->at(0)->lng, -0.1702022552285598);

	EXPECT_EQ(mp->errands->at(1)->lat, 51.497629616981214);
	EXPECT_EQ(mp->errands->at(1)->lng, -0.17346382139066918);

	EXPECT_EQ(mp->errands->at(2)->lat, 51.49841775633878);
	EXPECT_EQ(mp->errands->at(2)->lng, -0.17533063886503442);

	EXPECT_EQ(mp->errands->at(3)->lat, 51.497910142721445);
	EXPECT_EQ(mp->errands->at(3)->lng, -0.17936468122343285);

	EXPECT_EQ(mp->errands->at(4)->lat, 51.495759401256);
	EXPECT_EQ(mp->errands->at(4)->lng, -0.1717901229653762);

	EXPECT_EQ(mp->errands->at(5)->lat, 51.49644070301275);
	EXPECT_EQ(mp->errands->at(5)->lng, -0.17026662824491723);
}

TEST(MapPointsTest, HasEnoughErrands) {
	string json = "{\"origin\":{\"lat\":51.50055501480524,\"lng\":-0.17445087432861328},\"destination\":{\"lat\":51.50055501480524,\"lng\":-0.17445087432861328},\"waypoints\":[{\"lat\":51.497843351035144,\"lng\":-0.1702022552285598},{\"lat\":51.497629616981214,\"lng\":-0.17346382139066918},{\"lat\":51.49841775633878,\"lng\":-0.17533063886503442},{\"lat\":51.497910142721445,\"lng\":-0.17936468122343285},{\"lat\":51.495759401256,\"lng\":-0.1717901229653762},{\"lat\":51.49644070301275,\"lng\":-0.17026662824491723}]}\n";
	MapPoints * mp = parse_coordinates(json.c_str());

	EXPECT_EQ(mp->errands->size(), 6);
}

TEST(MapPointsTest, CanEncodeJSONCorrectly) {
	string json = "{\"origin\":{\"lat\":51.50055501480524,\"lng\":-0.17445087432861328},\"destination\":{\"lat\":51.50055501480524,\"lng\":-0.17445087432861328},\"waypoints\":[{\"lat\":51.497843351035144,\"lng\":-0.1702022552285598},{\"lat\":51.497629616981214,\"lng\":-0.17346382139066918},{\"lat\":51.49841775633878,\"lng\":-0.17533063886503442},{\"lat\":51.497910142721445,\"lng\":-0.17936468122343285},{\"lat\":51.495759401256,\"lng\":-0.1717901229653762},{\"lat\":51.49644070301275,\"lng\":-0.17026662824491723}]}\n";
	MapPoints * mp = parse_coordinates(json.c_str());

	string actual = print_coordinates(mp);
	string expected = "[{\"lat\":51.50055501480524,\"lng\":-0.17445087432861329},{\"lat\":51.497843351035147,\"lng\":-0.1702022552285598},{\"lat\":51.497629616981217,\"lng\":-0.17346382139066919},{\"lat\":51.49841775633878,\"lng\":-0.17533063886503442},{\"lat\":51.497910142721448,\"lng\":-0.17936468122343286},{\"lat\":51.495759401256,\"lng\":-0.1717901229653762},{\"lat\":51.49644070301275,\"lng\":-0.17026662824491724}]";

	EXPECT_EQ(actual.compare(expected), 0);
	EXPECT_EQ(expected.compare(actual), 0);
}


/**
 * This is a failing test which does not report fail. We have to investigate
 */
// TEST(MapPointsTest, CanParseJSONObjectsCorrectly) {
//     //TODO: Feed proper test data into this method.

//	string json = "{'origin':{'lat':51.50055501480524,'lng':-0.17445087432861328},'destination':{'lat':51.50055501480524,'lng':-0.17445087432861328},'waypoints':[{'lat':51.497843351035144,'lng':-0.1702022552285598},{'lat':51.497629616981214,'lng':-0.17346382139066918},{'lat':51.49841775633878,'lng':-0.17533063886503442},{'lat':51.497910142721445,'lng':-0.17936468122343285},{'lat':51.495759401256,'lng':-0.1717901229653762},{'lat':51.49644070301275,'lng':-0.17026662824491723}]}\n";
// 	MapPoints * mp = parse_coordinates(json.c_str());

// 	EXPECT_EQ(mp->origin->lat, 51.50055501480524);
// 	EXPECT_EQ(mp->origin->lng, 51.50055501480524);

//     EXPECT_EQ(1 + 2, 3);
// }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

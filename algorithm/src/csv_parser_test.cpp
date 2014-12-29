#include "lib/gtest/gtest.h"

#include "csv_parser.h"

TEST(CSVParserTest, SplitsString) {
    std::vector<std::string> vec;
    split("Jeremy,Tom,Andrei,Andrea,Alice", ',', &vec);

    ASSERT_EQ(vec[0], "Jeremy");
    ASSERT_EQ(vec[1], "Tom");
    ASSERT_EQ(vec[2], "Andrei");
    ASSERT_EQ(vec[3], "Andrea");
    ASSERT_EQ(vec[4], "Alice");
    ASSERT_EQ(vec.size(), 5);
}

TEST(CSVParserTest, ParsesCSV) {
    std::ifstream ifs("testData/csv_test.csv", std::ifstream::in);
    std::vector<std::string> vec;
    parse_csv(&ifs, &vec);
    parse_csv(&ifs, &vec);
    parse_csv(&ifs, &vec);
    ASSERT_EQ(vec.size(), 9);
    ASSERT_EQ(vec[0], "3");
    ASSERT_EQ(vec[1], "1");
    ASSERT_EQ(vec[2], "4");
    ASSERT_EQ(vec[3], "1");
    ASSERT_EQ(vec[4], "5");
    ASSERT_EQ(vec[5], "9");
    ASSERT_EQ(vec[6], "2");
    ASSERT_EQ(vec[7], "6");
    ASSERT_EQ(vec[8], "5");
    ifs.close();
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

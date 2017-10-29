#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <tuple>
#include "donation_analysis.h"
#include "gtest/gtest.h"

TEST(TestTrackerDate, DateCmp){
    using namespace donation_analysis;
    DateCmp cmp;
    EXPECT_TRUE(cmp("01012014", "01012015"));
    EXPECT_TRUE(cmp("01012014", "02012014"));
    EXPECT_TRUE(cmp("01112014", "01212014"));
}

TEST(TestTrackerDate, Constructor){
    using namespace donation_analysis;
    TrackerDate td;
}

TEST(TestTrackerDate, InsertComponents){
    using namespace donation_analysis;
    TrackerDate td;
    td.add("01012010", 100);
    std::string id, date;
    std::int64_t median, amt;
    size_t cnt;
    td.resetGetter();
    std::tie(date, median, cnt, amt) = td.getData();
    EXPECT_EQ("01012010", date);
    EXPECT_EQ(100, median);
    EXPECT_EQ(1, cnt);
    EXPECT_EQ(100, amt);
}

TEST(TestTrackerZip, Constructor){
    using namespace donation_analysis;
    TrackerZip tz;
}

TEST(TestTrackerZip, InsertComponents){
    using namespace donation_analysis;
    TrackerZip tz;
    tz.add("01012010", 100);
    std::string id, date;
    std::int64_t median, amt;
    size_t cnt;
    std::tie(date, median, cnt, amt) = tz.getData();
    EXPECT_EQ("01012010", date);
    EXPECT_EQ(100, median);
    EXPECT_EQ(1, cnt);
    EXPECT_EQ(100, amt);
    tz.add("02012010", 200);
    std::tie(date, median, cnt, amt) = tz.getData();
    EXPECT_EQ("02012010", date);
    EXPECT_EQ(200, median);
    EXPECT_EQ(1, cnt);
    EXPECT_EQ(200, amt);
    tz.add("01012010",144);
    std::tie(date, median, cnt, amt) = tz.getData();
    EXPECT_EQ("01012010", date);
    EXPECT_EQ(122, median);
    EXPECT_EQ(2, cnt);
    EXPECT_EQ(244, amt);
}

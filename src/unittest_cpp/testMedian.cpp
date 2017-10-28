#include <iostream>
#include <vector>
#include "donation_analysis.h"
#include "gtest/gtest.h"

TEST(TestMedianRunning, Constructor){
    using namespace donation_analysis;
    MedianRunning mr;
    EXPECT_EQ(0u, mr.getCnt());
    EXPECT_EQ(0, mr.getAmt());
    EXPECT_EQ(0, mr.calcMedian());
    MedianRunning mr2 = mr;
    EXPECT_EQ(0u, mr2.getCnt());
    EXPECT_EQ(0, mr2.getAmt());
}

TEST(TestMedian, CalcMedian){
    using namespace donation_analysis;
    std::vector<int> vals {1,2,3,4,5,6,7,8,9,10,11,12,13,14,10,8};
    std::vector<int> meds {1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,8};
    std::vector<int> amts {1,3,6,10,15,21,28,36,45,55,66,78,91,105,115,123};
    MedianRunning mr;
    for(int i = 0; i < 16; ++i){
        mr.push(vals[i]);
        EXPECT_EQ(meds[i], mr.calcMedian());
        EXPECT_EQ(amts[i], mr.getAmt());
    }

    MedianStatic ms;
    for(int i = 0; i < 16; ++i){
        ms.push(vals[i]);
        EXPECT_EQ(meds[i], ms.calcMedian());
        EXPECT_EQ(amts[i], ms.getAmt());
    }
}

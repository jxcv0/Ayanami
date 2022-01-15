#include <gtest/gtest.h>

#include "avellaneda_stoikov.hpp"

TEST(AvellanedaStoikovTests, generate_bids_test) {
    Ayanami::AV::AvOut out;
    out.res = 1011.5;
    out.spread = 3; // optimal bid should be 1010

    std::map<double, int> bids;

    Ayanami::AV::generate_bids(out, bids, 0.5, 5);

    ASSERT_EQ(bids.size(), 5);
    ASSERT_TRUE(bids.contains(1010));
    ASSERT_TRUE(bids.contains(1009.5));
    ASSERT_TRUE(bids.contains(1009));
    ASSERT_TRUE(bids.contains(1008.5));
    ASSERT_TRUE(bids.contains(1008));
}

TEST(AvellanedaStoikovTests, generate_asks_test) {
    Ayanami::AV::AvOut out;
    out.res = 1011.5;
    out.spread = 3; // optimal ask should be 1013

    std::map<double, int> asks;

    Ayanami::AV::generate_asks(out, asks, 0.5, 5);

    ASSERT_EQ(asks.size(), 5);
    ASSERT_TRUE(asks.contains(1013));
    ASSERT_TRUE(asks.contains(1013.5));
    ASSERT_TRUE(asks.contains(1014));
    ASSERT_TRUE(asks.contains(1014.5));
    ASSERT_TRUE(asks.contains(1015));
}
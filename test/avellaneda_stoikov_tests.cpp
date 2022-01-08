#include <gtest/gtest.h>

#include "avellaneda_stoikov.hpp"

TEST(avellaneda_stoikov_tests, generate_bids_test) {
    ayanami::av::av_out out;
    out.res = 1011.5;
    out.spread = 3; // optimal bid should be 1010

    std::map<double, ayanami::av::order> bids;

    ayanami::av::generate_bids(out, bids, 0.5, 5);

    ASSERT_EQ(bids.size(), 5);
    ASSERT_TRUE(bids.contains(1010));
    ASSERT_TRUE(bids.contains(1009.5));
    ASSERT_TRUE(bids.contains(1009));
    ASSERT_TRUE(bids.contains(1008.5));
    ASSERT_TRUE(bids.contains(1008));
}

TEST(avellaneda_stoikov_tests, generate_asks_test) {
    ayanami::av::av_out out;
    out.res = 1011.5;
    out.spread = 3; // optimal ask should be 1013

    std::map<double, ayanami::av::order> asks;

    ayanami::av::generate_asks(out, asks, 0.5, 5);

    ASSERT_EQ(asks.size(), 5);
    ASSERT_TRUE(asks.contains(1013));
    ASSERT_TRUE(asks.contains(1013.5));
    ASSERT_TRUE(asks.contains(1014));
    ASSERT_TRUE(asks.contains(1014.5));
    ASSERT_TRUE(asks.contains(1015));
}
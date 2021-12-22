#include <gtest/gtest.h>

#include "TradeSeries.hpp"

TEST(TradeSeriesTests, max_size_test) {
    ayanami::Series ts(3);
    for (size_t i = 0; i < 10; i++) {
        ts.add_trade(i, i, i);
        ASSERT_LE(ts.size(), 3);
    }
}
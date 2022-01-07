#include <gtest/gtest.h>

#include "trade_series.hpp"

TEST(trade_series_tests, max_size_test) {
    ayanami::series ts(3);
    for (size_t i = 0; i < 10; i++) {
        ts.add_trade(i, i, i);
        ASSERT_LE(ts.size(), 3);
    }
}
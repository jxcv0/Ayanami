#include <gtest/gtest.h>
#include "TradeSeries.hpp"

TEST(TradeSeriestTests, maximumSizeTest) {
    Ayanami::TradeSeries::Series ts(3);
    for (size_t i = 0; i < 10; i++) {
        ts.add_trade(i, i, i);
        ASSERT_LE(ts.size(), 3);
    }
}
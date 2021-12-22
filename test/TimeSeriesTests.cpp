#include <gtest/gtest.h>

#include "TimeSeries.hpp"

TEST(TimeSeriesTests, max_size_test) {
    ayanami::TimeSeries ts(3);
    for (size_t i = 0; i < 10; i++) {
        ts.add_candle(i, i, i, i, i, i);
        ASSERT_LE(ts.size(), 3);
    }
}
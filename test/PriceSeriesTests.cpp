#include <gtest/gtest.h>

#include "PriceSeries.hpp"

TEST(PriceSeriesTests, max_size_test) {
    ayanami::PriceSeries s(3);
    for (size_t i = 0; i < 10; i++) {
        s.add_price(i);
        ASSERT_LE(s.size(), 3);
    }
}

TEST(PriceSeriesTests, mean_test) {
    ayanami::PriceSeries s1(10);
    for (size_t i = 1; i <= 10; i++) {
        s1.add_price(i);
    }
    ASSERT_DOUBLE_EQ(s1.mean(), 5.5);

    ayanami::PriceSeries s2(10);
    for (size_t i = 1; i <= 100; i++) {
        s2.add_price(i);
    }
    ASSERT_DOUBLE_EQ(s2.mean(), 95.5);
}

TEST(PriceSeriesTests, variance_test) {
    ayanami::PriceSeries s(100);
    double arr[] = {10, 12, 23, 23, 16, 23, 21, 16};

    for (auto &&i : arr) {
        s.add_price(i);
    }
    ASSERT_DOUBLE_EQ(s.variance(), 24);
}

TEST(PriceSeriesTests, std_dev_test) {
    ayanami::PriceSeries s(100);
    double arr[] = {10, 12, 23, 23, 16, 23, 21, 16};

    for (auto &&i : arr) {
        s.add_price(i);
    }
    ASSERT_DOUBLE_EQ(s.std_dev(), 4.8989794855663558);
}
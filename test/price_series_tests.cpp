#include <gtest/gtest.h>

#include "price_series.hpp"

TEST(price_series_tests, max_size_test) {
    ayanami::price_series s(3);
    for (size_t i = 0; i < 10; i++) {
        s.add_price(i);
        ASSERT_LE(s.size(), 3);
    }
}

TEST(price_series_tests, mean_test) {
    ayanami::price_series s1(10);
    for (size_t i = 1; i <= 10; i++) {
        s1.add_price(i);
    }
    ASSERT_DOUBLE_EQ(s1.mean(), 5.5);

    ayanami::price_series s2(10);
    for (size_t i = 1; i <= 100; i++) {
        s2.add_price(i);
    }
    ASSERT_DOUBLE_EQ(s2.mean(), 95.5);
}

TEST(price_series_tests, variance_test) {
    ayanami::price_series s(100);
    double arr[] = {10, 12, 23, 23, 16, 23, 21, 16};

    for (auto &&i : arr) {
        s.add_price(i);
    }
    ASSERT_DOUBLE_EQ(s.variance(), 24);
}

TEST(price_series_tests, std_dev_test) {
    ayanami::price_series s(100);
    double arr[] = {10, 12, 23, 23, 16, 23, 21, 16};

    for (auto &&i : arr) {
        s.add_price(i);
    }
    ASSERT_DOUBLE_EQ(s.std_dev(), 4.8989794855663558);
}
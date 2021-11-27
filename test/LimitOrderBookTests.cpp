#include <gtest/gtest.h>
#include "LimitOrderBook.hpp"

// Test that insert() can add, overwrite, and remove values.
TEST(LimitOrderBookTests, insertTest) {
    Ayanami::LimitOrderBook lob;

    // Insert
    double price = 1000.45;
    double size = 100.0;
    lob.insert(price, size);
    ASSERT_EQ(100.0, lob.atPrice(1000.45));

    // Overwrite
    double newSize = 99.85;
    lob.insert(price, newSize);
    ASSERT_EQ(99.85, lob.atPrice(price));

    // Remove
    double removeWithZero = 0;
    lob.insert(price, removeWithZero);
    EXPECT_ANY_THROW(lob.atPrice(price));
}
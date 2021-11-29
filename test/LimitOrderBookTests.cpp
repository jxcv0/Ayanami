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

TEST(LimitOrderBookTests, getAsksTest) {
    Ayanami::LimitOrderBook lob;
    lob.insert(104, -100);
    lob.insert(103, -100);
    lob.insert(102, -100);
    lob.insert(101, -100);
    lob.insert(100, 100);
    lob.insert(99, 100);
    lob.insert(98, 100);
    lob.insert(97, 100);

    std::map<double, double> asks = {
        {104, -100},
        {103, -100},
        {102, -100},
        {101, -100},
    };

    ASSERT_EQ(asks, lob.getAsks());
}

TEST(LimitOrderBookTests, getBidsTest) {
    Ayanami::LimitOrderBook lob;
    lob.insert(104, -100);
    lob.insert(103, -100);
    lob.insert(102, -100);
    lob.insert(101, -100);
    lob.insert(100, 100);
    lob.insert(99, 100);
    lob.insert(98, 100);
    lob.insert(97, 100);

    std::map<double, double> bids = {
        {100, 100},
        {99, 100},
        {98, 100},
        {97, 100},
    };

    ASSERT_EQ(bids, lob.getBids());
}

TEST(LimitOrderBookTests, bestBidAskTest) {
    Ayanami::LimitOrderBook lob;
    lob.insert(104, -100);
    lob.insert(103, -100);
    lob.insert(102, -100);
    lob.insert(101, -100);
    lob.insert(100, 100);
    lob.insert(99, 100);
    lob.insert(98, 100);
    lob.insert(97, 100);

    ASSERT_EQ(100, lob.bestBid());
    ASSERT_EQ(101, lob.bestAsk());
}

TEST(LimitOrderBookTests, totaldepthTest) {
    Ayanami::LimitOrderBook lob;
    lob.insert(104, -100);
    lob.insert(103, -100);
    lob.insert(102, -100);
    lob.insert(101, -100);
    lob.insert(100, 100);
    lob.insert(99, 100);
    lob.insert(98, 100);
    lob.insert(97, 100);

    ASSERT_EQ(800, lob.depth());
}

TEST(LimitOrderBookTests, partialdepthTest) {
    Ayanami::LimitOrderBook lob;
    lob.insert(104, -100);
    lob.insert(103, -100);
    lob.insert(102, -100);
    lob.insert(101, -100);
    lob.insert(100, 100);
    lob.insert(99, 100);
    lob.insert(98, 100);
    lob.insert(97, 100);

    ASSERT_EQ(400, lob.depth(1));
    ASSERT_EQ(600, lob.depth(2));
}
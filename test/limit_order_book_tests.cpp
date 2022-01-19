#include <gtest/gtest.h>

#include "limit_order_book.hpp"
#include "simdjson.h"

TEST(LimitOrderBookTests, update_orderbook) {

    // set up orderbook
    std::map<double, double> orderbook = {
        // asks
        {43081.0, -2.5841},
        {43080.0, -1.103},
        {43079.0, -0.6228},
        {43078.0, -0.5563},
        {43077.0, -3.6275},
        {43076.0, -1.443},
        // bids
        {43075.0, 5.7513},
        {43074.0, 0.1735},
        {43073.0, 0.5737},
        {43072.0, 0.0212},
        {43071.0, 0.484},
        {43070.0, 2.675}
    };

    // set up update
    std::map<double, double> update = {
        // asks
        {43077.0, -6.6028},
        {43076.0, -12.9434},
        // bids
        {43075.0, 1.8567},
        {43074.0, 0.109},
        {43073.0, 1.2402},
        {43072.0, 10.6792},
        {43071.0, 0.561},
        {43070.0, 0}
    };

    Ayanami::LOB::update_orderbook(orderbook, update);

    ASSERT_DOUBLE_EQ(orderbook[43081.0], -2.5841);  // unchanged
    ASSERT_DOUBLE_EQ(orderbook[43080.0], -1.103);   // unchanged
    ASSERT_DOUBLE_EQ(orderbook[43079.0], -0.6228);  // unchanged
    ASSERT_DOUBLE_EQ(orderbook[43078.0], -0.5563);  // unchanged
    ASSERT_DOUBLE_EQ(orderbook[43077.0], -6.6028);  // altered
    ASSERT_DOUBLE_EQ(orderbook[43076.0], -12.9434); // altered
    ASSERT_DOUBLE_EQ(orderbook[43075.0], 1.8567);   // altered
    ASSERT_DOUBLE_EQ(orderbook[43074.0], 0.109);    // altered
    ASSERT_DOUBLE_EQ(orderbook[43073.0], 1.2402);   // altered
    ASSERT_DOUBLE_EQ(orderbook[43072.0], 10.6792);  // altered
    ASSERT_DOUBLE_EQ(orderbook[43071.0], 0.561);    // altered
    ASSERT_ANY_THROW(orderbook.at(43070));          // removed
    ASSERT_EQ(orderbook.size(), 11);                // no unexpected additions
}
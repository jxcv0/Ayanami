#include <gtest/gtest.h>
#include "Trade.hpp"

// Not neccessary
TEST(TradeTests, constructorTest) {
  Ayanami::Trade trade(1636567906, 49010.71, 15000, "BTCUSD");
  ASSERT_EQ(trade.getTime(), 1636567906);
  ASSERT_EQ(trade.getPrice(), 49010.71);
  ASSERT_EQ(trade.getQty(), 15000);
  ASSERT_EQ(trade.getSymbol(), "BTCUSD");
}
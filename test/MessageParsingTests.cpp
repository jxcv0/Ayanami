#include <gtest/gtest.h>

#include "MessageParsing.hpp"
#include "TradeSeries.hpp"

TEST(MessageParsingTests, parse_FTX_trade_msg) {
    std::string msg = "{\"channel\": \"trades\", \"market\": \"BTC-PERP\", \"type\": \"update\", \"data\": [{\"id\": 2867749033, \"price\": 48907.0, \"size\": 0.0025, \"side\": \"buy\", \"liquidation\": false, \"time\": \"2021-12-22T21:13:19.773172+00:00\"}]}";
    ayanami::connections::TradeMessage t = ayanami::connections::parse_FTX_trade_msg(msg);
    ASSERT_EQ(t.price, 48907.0);
    ASSERT_EQ(t.qty, 0.0025);
} 
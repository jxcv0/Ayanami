#include <gtest/gtest.h>

#include "ftx/FTX_WSMessage.hpp"

TEST(FTX_WSMessageTests, parse_test) {
    std::string msg = "{\"channel\":\"orderbook\",\"market\":\"BTC-PERP\",\"type\":\"update\",\"data\":{\"time\":1641365337.7947907,\"checksum\":3785472758,\"bids\":[],\"asks\":[[46411,0.46999999999999997]],\"action\":\"update\"}}";
}
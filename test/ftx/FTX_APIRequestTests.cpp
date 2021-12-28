#include <gtest/gtest.h>

#include "ftx/FTX_APIRequest.hpp"
#include "APIKeys.hpp"

TEST(FTX_APIRequestsTests, generate_order_json_test) {
    std::string json = ayanami::ftx::generate_order_json("BTC-PERP", "buy", 8500, "limit", 1, false, false);
    std::string example = "{\"market\":\"BTC-PERP\",\"side\":\"buy\",\"price\":8500,\"size\":1,\"type\":\"limit\",\"reduceOnly\":false,\"ioc\":false,\"postOnly\":false,\"clientId\":null}";
    ASSERT_EQ(json, example);
}

TEST(FTX_APIRequestsTests, generate_order_req_test) {
    std::string json = "{\"market\":\"BTC-PERP\",\"side\":\"buy\",\"price\":8500,\"size\":1,\"type\":\"limit\",\"reduceOnly\":false,\"ioc\":false,\"postOnly\":false,\"clientId\":null}";
    std::string req = ayanami::ftx::generate_order_header(1588591856950, json);
    std::string expected = "1588591856950POST/api/orders{\"market\":\"BTC-PERP\",\"side\":\"buy\",\"price\":8500,\"size\":1,\"type\":\"limit\",\"reduceOnly\":false,\"ioc\":false,\"postOnly\":false,\"clientId\":null}";

    ASSERT_EQ(req, expected);
}
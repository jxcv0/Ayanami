#include <gtest/gtest.h>

#include "ftx/FTX_APIRequest.hpp"
#include "APIKeys.hpp"

TEST(FTX_APIRequestsTests, generate_request_test) {
    std::string order_req = ayanami::ftx::generate_order_req("BTC-PERP", "buy", 8500, "limit", 1, false, false);
    std::string example = "{\"market\":\"BTC-PERP\",\"side\":\"buy\",\"price\":8500,\"size\":1,\"type\":\"limit\",\"reduceOnly\":false,\"ioc\":false,\"postOnly\":false,\"clientId\":null}";
    ASSERT_EQ(example, order_req);
}
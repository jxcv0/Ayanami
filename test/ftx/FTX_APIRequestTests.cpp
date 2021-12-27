#include <gtest/gtest.h>

#include "ftx/FTX_APIRequest.hpp"

TEST(FTX_APIRequestsTests, generate_order_request_test) {
    std::string order_req = ayanami::ftx::generate_order_request("BTC-PERP", "buy", 8500, "limit", 1, false, false);
    std::string example = "{\"market\":\"BTC-PERP\",\"side\":\"buy\",\"price\":8500,\"size\":1,\"type\":\"limit\",\"reduceOnly\":false,\"postOnly\":false}";
    ASSERT_EQ(example, order_req);
}

TEST(AuthentificationTests, generate_POST_sign_test) {
    long time = 1588591856950;
    std::string secret = "T4lPid48QtjNxjLUFOcUZghD7CUJ7sTVsfuvQZF2";
    std::string order_req = ayanami::ftx::generate_order_request("BTC-PERP", "buy", 8500, "Limit", 1, false, true);

    std::string sign = ayanami::ftx::generate_sign(time, "POST", "api/orders", order_req);

    std::string example = "c4fbabaf178658a59d7bbf57678d44c369382f3da29138f04cd46d3d582ba4ba";
    ASSERT_EQ(sign, example);
}
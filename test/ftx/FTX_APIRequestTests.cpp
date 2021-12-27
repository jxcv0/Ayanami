#include <gtest/gtest.h>

#include "ftx/FTX_APIRequest.hpp"

TEST(FTX_APIRequestsTests, generate_order_request_test) {
    
}

TEST(AuthentificationTests, generate_POST_sign_test) {
    long time = 1588591856950;
    std::string secret = "T4lPid48QtjNxjLUFOcUZghD7CUJ7sTVsfuvQZF2";

    std::string sign = ayanami::ftx::generate_sign(time, "POST", "api/orders", "JSONhere");

    std::string example = "c4fbabaf178658a59d7bbf57678d44c369382f3da29138f04cd46d3d582ba4ba";
    ASSERT_EQ(sign, example);
}
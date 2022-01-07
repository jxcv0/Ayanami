#include <gtest/gtest.h>

#include "encryption.hpp"

TEST(encryption_tests, spacify_test) {
    std::string input = "1588591856950POST/api/orders{\"market\":\"BTC-PERP\",\"side\":\"buy\",\"price\":8500,\"size\":1,\"type\":\"limit\",\"reduceOnly\":false,\"ioc\":false,\"postOnly\":false,\"clientId\":null}";
    std::string expected = "1588591856950POST/api/orders{\"market\": \"BTC-PERP\", \"side\": \"buy\", \"price\": 8500, \"size\": 1, \"type\": \"limit\", \"reduceOnly\": false, \"ioc\": false, \"postOnly\": false, \"clientId\": null}";
    ASSERT_NE(input, expected);
    ASSERT_EQ(ayanami::spacify(input), expected);
}

TEST(encryption_tests, hmac_sha256_POST_test) {
    std::string text = "1588591856950POST/api/orders{\"market\": \"BTC-PERP\", \"side\": \"buy\", \"price\": 8500, \"size\": 1, \"type\": \"limit\", \"reduceOnly\": false, \"ioc\": false, \"postOnly\": false, \"clientId\": null}";
    std::string secret = "T4lPid48QtjNxjLUFOcUZghD7CUJ7sTVsfuvQZF2";
    std::string expected = "c4fbabaf178658a59d7bbf57678d44c369382f3da29138f04cd46d3d582ba4ba";

    std::string actual = ayanami::hmac_sha256(secret.c_str(), text.c_str());
    ASSERT_EQ(actual, expected);
}

TEST(encryption_tests, hmac_sha256_GET_test) {
    std::string text = "1588591511721GET/api/markets";
    std::string secret = "T4lPid48QtjNxjLUFOcUZghD7CUJ7sTVsfuvQZF2";
    std::string expected = "dbc62ec300b2624c580611858d94f2332ac636bb86eccfa1167a7777c496ee6f";

    std::string actual = ayanami::hmac_sha256(secret.c_str(), text.c_str());
    ASSERT_EQ(actual, expected);
}
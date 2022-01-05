#include <gtest/gtest.h>

#include "ftx/FTX_APIRequests.hpp"
#include "APIKeys.hpp"

TEST(FTX_APIRequestsTests, generate_order_json_test) {
    std::string json = ayanami::ftx::generate_order_json("BTC-PERP", "buy", 8500, "limit", 1, false, false);
    std::string example = "{\"market\": \"BTC-PERP\", \"side\": \"buy\", \"price\": 8500, \"size\": 1, \"type\": \"limit\", \"reduceOnly\": false, \"ioc\": false, \"postOnly\": false, \"clientId\": null}";
    ASSERT_EQ(json, example);
}

TEST(FTX_APIRequestsTests, generate_order_req_test) {
    std::string json = "{\"market\": \"BTC-PERP\", \"side\": \"buy\", \"price\": 8500, \"size\": 1, \"type\": \"limit\", \"reduceOnly\": false, \"ioc\": false, \"postOnly\": false, \"clientId\": null}";
    std::string req = ayanami::ftx::generate_order_header(1588591856950, json);
    std::string expected = "1588591856950POST/api/orders{\"market\": \"BTC-PERP\", \"side\": \"buy\", \"price\": 8500, \"size\": 1, \"type\": \"limit\", \"reduceOnly\": false, \"ioc\": false, \"postOnly\": false, \"clientId\": null}";

    ASSERT_EQ(req, expected);
}

TEST(FTX_APIRequestsTests, generate_ws_sign_test) {
    long time = 1557246346499;
    std::string secret = "Y2QTHI23f23f23jfjas23f23To0RfUwX3H42fvN-";
    std::string expected = "d10b5a67a1a941ae9463a60b285ae845cdeac1b11edc7da9977bef0228b96de9";
    std::string actual = ayanami::ftx::generate_ws_sign(time, secret.c_str());
    ASSERT_EQ(actual, expected);
}

TEST(FTX_APIRequestsTests, generate_ws_login) {
    long time = 1557246346499;
    std::string key("key");
    std::string secret("Y2QTHI23f23f23jfjas23f23To0RfUwX3H42fvN-");
    std::string expected("{\"op\": \"login\", \"args\": {\"key\": \"key\", \"sign\": \"d10b5a67a1a941ae9463a60b285ae845cdeac1b11edc7da9977bef0228b96de9\", \"time\": 1557246346499}}");

    ASSERT_EQ(ayanami::ftx::generate_ws_login(time, key.c_str(), secret.c_str()), expected);
}
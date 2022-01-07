#include <gtest/gtest.h>

#include "ftx/ftx_rest.hpp"
#include "encryption.hpp"
#include "https.hpp"
#include "api_keys.hpp"

TEST(ftx_rest_test, 200_ok_test) {
    long t = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
    std::string time_now = std::to_string(t);

    // get account information - requires authentification
    http::request<http::string_body> req;
    http::response<http::dynamic_body> res;
    req.method(http::verb::get);
    req.target("https://ftx.com/api/account");
    req.set(http::field::host, "ftx.com");
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    req.set("FTX-KEY", APIKeys::KEY);
    req.set("FTX-TS", time_now);
    std::string sign = time_now + "GET" + "/api/account";
    req.set("FTX-SIGN", ayanami::hmac_sha256(APIKeys::SECRET, sign.c_str()));

    ayanami::connections::send_req(req, res);
    ASSERT_EQ(res.result_int(), 200);
}

TEST(ftx_rest_test, generate_order_json_test) {
    std::string json = ayanami::ftx::generate_order_json("BTC-PERP", "buy", 8500, "limit", 1, false, false);
    std::string example = "{\"market\": \"BTC-PERP\", \"side\": \"buy\", \"price\": 8500, \"size\": 1, \"type\": \"limit\", \"reduceOnly\": false, \"ioc\": false, \"postOnly\": false, \"clientId\": null}";
    ASSERT_EQ(json, example);
}

TEST(ftx_rest_test, generate_order_req_test) {
    std::string json = "{\"market\": \"BTC-PERP\", \"side\": \"buy\", \"price\": 8500, \"size\": 1, \"type\": \"limit\", \"reduceOnly\": false, \"ioc\": false, \"postOnly\": false, \"clientId\": null}";
    std::string req = ayanami::ftx::generate_order_header(1588591856950, json);
    std::string expected = "1588591856950POST/api/orders{\"market\": \"BTC-PERP\", \"side\": \"buy\", \"price\": 8500, \"size\": 1, \"type\": \"limit\", \"reduceOnly\": false, \"ioc\": false, \"postOnly\": false, \"clientId\": null}";

    ASSERT_EQ(req, expected);
}

TEST(ftx_rest_test, generate_ws_sign_test) {
    long time = 1557246346499;
    std::string secret = "Y2QTHI23f23f23jfjas23f23To0RfUwX3H42fvN-";
    std::string expected = "d10b5a67a1a941ae9463a60b285ae845cdeac1b11edc7da9977bef0228b96de9";
    std::string actual = ayanami::ftx::generate_ws_sign(time, secret.c_str());
    ASSERT_EQ(actual, expected);
}

TEST(ftx_rest_test, generate_ws_login) {
    long time = 1557246346499;
    std::string key("key");
    std::string secret("Y2QTHI23f23f23jfjas23f23To0RfUwX3H42fvN-");
    std::string expected("{\"op\": \"login\", \"args\": {\"key\": \"key\", \"sign\": \"d10b5a67a1a941ae9463a60b285ae845cdeac1b11edc7da9977bef0228b96de9\", \"time\": 1557246346499}}");

    ASSERT_EQ(ayanami::ftx::generate_ws_login(time, key.c_str(), secret.c_str()), expected);
}
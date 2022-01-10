#include <gtest/gtest.h>

#include "ftx/ftx_rest.hpp"
#include "encryption.hpp"
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
    std::string example("{\"market\": \"BTC-PERP\", \"side\": \"buy\", \"price\": 8500, \"size\": 1, \"type\": \"limit\", \"reduceOnly\": false, \"ioc\": false, \"postOnly\": false, \"clientId\": null}");

    ASSERT_EQ(json, example);
}

TEST(ftx_rest_test, generate_sign_str_test) {
    std::string json("{\"market\": \"BTC-PERP\", \"side\": \"buy\", \"price\": 8500, \"size\": 1, \"type\": \"limit\", \"reduceOnly\": false, \"ioc\": false, \"postOnly\": false, \"clientId\": null}");
    std::string req = ayanami::ftx::generate_sign_str(1588591856950, "/api/orders", json);
    std::string expected("1588591856950POST/api/orders{\"market\": \"BTC-PERP\", \"side\": \"buy\", \"price\": 8500, \"size\": 1, \"type\": \"limit\", \"reduceOnly\": false, \"ioc\": false, \"postOnly\": false, \"clientId\": null}");

    ASSERT_EQ(req, expected);
}

TEST(ftx_rest_test, generate_ws_sign_test) {
    long time = 1557246346499;
    std::string secret("Y2QTHI23f23f23jfjas23f23To0RfUwX3H42fvN-");
    std::string expected("d10b5a67a1a941ae9463a60b285ae845cdeac1b11edc7da9977bef0228b96de9");
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

TEST(ftx_rest_test, generate_order_request) {
    std::string key("LR0RQT6bKjrUNh38eCw9jYC89VDAbRkCogAc_XAm");
    std::string secret("T4lPid48QtjNxjLUFOcUZghD7CUJ7sTVsfuvQZF2");
    http::request<http::string_body> req;

    long ts = 1588591856950;
    auto ts_str = std::to_string(ts);

    std::string json("{\"market\": \"BTC-PERP\", \"side\": \"buy\", \"price\": 8500, \"size\": 1, \"type\": \"limit\", \"reduceOnly\": false, \"ioc\": false, \"postOnly\": false, \"clientId\": null}");
    std::string sign_str = ayanami::ftx::generate_sign_str(ts, "/api/orders", json);
    std::string sign = ayanami::hmac_sha256(secret.c_str(), sign_str.c_str());
    ayanami::ftx::generate_order_request(req, ts_str, key.c_str(), sign);

    ASSERT_EQ(req.method(), http::verb::post);
    ASSERT_EQ(req.target().to_string(), "https://ftx.com/api/orders");
    ASSERT_EQ(req.at("FTX-KEY"), key);
    ASSERT_EQ(req.at("FTX-TS"), ts_str);
    ASSERT_EQ(req.at("FTX-SIGN").to_string(), "c4fbabaf178658a59d7bbf57678d44c369382f3da29138f04cd46d3d582ba4ba");
}

TEST(ftx_rest_test, generate_modify_request_test) {
    std::string key("LR0RQT6bKjrUNh38eCw9jYC89VDAbRkCogAc_XAm");
    std::string secret("T4lPid48QtjNxjLUFOcUZghD7CUJ7sTVsfuvQZF2");
    http::request<http::string_body> req;

    long ts = 1588591856950;
    auto ts_str = std::to_string(ts);

    ayanami::ftx::generate_modify_request(req, ts_str, key.c_str(), secret.c_str(), 123456, 1000, 123);
    ASSERT_EQ(req.method(), http::verb::post);
    ASSERT_EQ(req.target().to_string(), "https://ftx.com/orders/123456/modify");
    ASSERT_EQ(req.at("FTX-KEY"), key);
    ASSERT_EQ(req.at("FTX-TS"), ts_str);
    ASSERT_EQ(req.at("FTX-SIGN").to_string(), "85354a555e4175fe14b4630e553c6168b0c263e0b3b8a3c5232da30290b48dbe");
}
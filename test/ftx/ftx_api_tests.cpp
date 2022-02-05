#include <gtest/gtest.h>

#include "ftx/ftx_api.hpp"
#include "encryption.hpp"
#include "api_keys.hpp"

TEST(FTXRestTests, generate_order_json) {
    std::string json = Ayanami::FTX::generate_order_json("BTC-PERP", "buy", 8500, "limit", 1, false, false);
    std::string example("{\"market\": \"BTC-PERP\", \"side\": \"buy\", \"price\": 8500, \"size\": 1, \"type\": \"limit\", \"reduceOnly\": false, \"ioc\": false, \"postOnly\": false, \"clientId\": null}");

    ASSERT_EQ(json, example);
}

TEST(FTXRestTests, generate_sign_str) {
    std::string json("{\"market\": \"BTC-PERP\", \"side\": \"buy\", \"price\": 8500, \"size\": 1, \"type\": \"limit\", \"reduceOnly\": false, \"ioc\": false, \"postOnly\": false, \"clientId\": null}");
    std::string req = Ayanami::FTX::generate_sign_str(1588591856950, "/api/orders", json);
    std::string expected("1588591856950POST/api/orders{\"market\": \"BTC-PERP\", \"side\": \"buy\", \"price\": 8500, \"size\": 1, \"type\": \"limit\", \"reduceOnly\": false, \"ioc\": false, \"postOnly\": false, \"clientId\": null}");

    ASSERT_EQ(req, expected);
}

TEST(FTXRestTests, generate_ws_sign) {
    long time = 1557246346499;
    std::string secret("Y2QTHI23f23f23jfjas23f23To0RfUwX3H42fvN-");
    std::string expected("d10b5a67a1a941ae9463a60b285ae845cdeac1b11edc7da9977bef0228b96de9");
    std::string actual = Ayanami::FTX::generate_ws_sign(time, secret.c_str());

    ASSERT_EQ(actual, expected);
}

TEST(FTXRestTests, generate_ws_login) {
    long time = 1557246346499;
    std::string key("key");
    std::string secret("Y2QTHI23f23f23jfjas23f23To0RfUwX3H42fvN-");
    std::string expected("{\"op\": \"login\", \"args\": {\"key\": \"key\", \"sign\": \"d10b5a67a1a941ae9463a60b285ae845cdeac1b11edc7da9977bef0228b96de9\", \"time\": 1557246346499}}");

    ASSERT_EQ(Ayanami::FTX::generate_ws_login(time, key.c_str(), secret.c_str()), expected);
}

TEST(FTXRestTests, generate_order_request) {
    std::string key("LR0RQT6bKjrUNh38eCw9jYC89VDAbRkCogAc_XAm");
    std::string secret("T4lPid48QtjNxjLUFOcUZghD7CUJ7sTVsfuvQZF2");
    http::request<http::string_body> req;

    long ts = 1588591856950;
    auto ts_str = std::to_string(ts);

    std::string json("{\"market\": \"BTC-PERP\", \"side\": \"buy\", \"price\": 8500, \"size\": 1, \"type\": \"limit\", \"reduceOnly\": false, \"ioc\": false, \"postOnly\": false, \"clientId\": null}");
    std::string sign_str = Ayanami::FTX::generate_sign_str(ts, "/api/orders", json);
    std::string sign = Ayanami::hmac_sha256(secret.c_str(), sign_str.c_str());
    Ayanami::FTX::generate_order_request(req, ts_str, key.c_str(), sign);

    ASSERT_EQ(req.method(), http::verb::post);
    ASSERT_EQ(req.target().to_string(), "https://FTX.com/api/orders");
    ASSERT_EQ(req.at("FTX-KEY"), key);
    ASSERT_EQ(req.at("FTX-TS"), ts_str);
    ASSERT_EQ(req.at("FTX-SIGN").to_string(), "c4fbabaf178658a59d7bbf57678d44c369382f3da29138f04cd46d3d582ba4ba");
}

TEST(FTXRestTests, generate_modify_request) {
    std::string key("LR0RQT6bKjrUNh38eCw9jYC89VDAbRkCogAc_XAm");
    std::string secret("T4lPid48QtjNxjLUFOcUZghD7CUJ7sTVsfuvQZF2");
    http::request<http::string_body> req;

    long ts = 1588591856950;
    auto ts_str = std::to_string(ts);

    Ayanami::FTX::generate_modify_request(req, ts_str, key.c_str(), secret.c_str(), 123456, 1000, 123);
    ASSERT_EQ(req.method(), http::verb::post);
    ASSERT_EQ(req.target().to_string(), "https://FTX.com/orders/123456/modify");
    ASSERT_EQ(req.at("FTX-KEY"), key);
    ASSERT_EQ(req.at("FTX-TS"), ts_str);
    ASSERT_EQ(req.at("FTX-SIGN").to_string(), "85354a555e4175fe14b4630e553c6168b0c263e0b3b8a3c5232da30290b48dbe");
}

TEST(FTXFixTest, get_timestamp_string) {
    boost::gregorian::date d(2022, boost::date_time::Jan, 1);
}

TEST(FTXFixTests, set_default_fix_header) {
    std::string key("LR0RQT6bKjrUNh38eCw9jYC89VDAbRkCogAc_XAm");
    std::string secret("T4lPid48QtjNxjLUFOcUZghD7CUJ7sTVsfuvQZF2");
    int seq = 13;
    std::map<std::string_view, std::string_view> expected = {
        {"8", "FIX.4.2"},
        {"9", "162"},
        {"34", "13"},
        {"35", "A"},
        {"49", "LR0RQT6bKjrUNh38eCw9jYC89VDAbRkCogAc_XAm"},
        {"56", "FTX"}
    };

    std::map<std::string_view, std::string_view> actual;
    Ayanami::FTX::set_fix_default(actual, key.c_str(), seq, "");

    std::for_each(expected.begin(), expected.end(), [&](const auto &kv){
        ASSERT_EQ(kv.second, actual.at(kv.first));
    });
}

TEST(FTXFixTests, set_fix_logon_header) {
    std::string key("LR0RQT6bKjrUNh38eCw9jYC89VDAbRkCogAc_XAm");
    std::string secret("T4lPid48QtjNxjLUFOcUZghD7CUJ7sTVsfuvQZF2");
    int seq = 13;

    std::map<std::string_view, std::string_view> base;
    Ayanami::FTX::set_fix_default(base, key.c_str(), seq, "");
    Ayanami::FTX::set_fix_logon(base, secret.c_str());

    std::map<std::string_view, std::string_view> expected = {
        {"8", "FIX.4.2"},
        {"9", "162"},
        {"35", "A"},
        {"49", "zyfvB4QPg0A3kkVgqUE9V1fOA-Y6jhdG3seqIIZx"},
        {"56", "FTX"},
        {"96", ""}, // sign
        {"98", "0"},
        {"108", "30"},
        {"8013", "Y"}
    };

    ASSERT_TRUE(false);
}
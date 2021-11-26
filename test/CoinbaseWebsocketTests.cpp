#include <gtest/gtest.h>
#include <vector>
#include <cpprest/json.h>
#include "CoinbaseWebsocket.hpp"

TEST(CoinbaseWebsocketTests, generateSubscriptionMessageTest) {

    Ayanami::CoinbaseWebsocket ws;

    std::vector<std::string> productIds;
    productIds.push_back("BTC-USD");
    productIds.push_back("BTC-GBP");
    productIds.push_back("BTC-EUR");

    std::vector<std::string> channels;
    channels.push_back("level2");
    channels.push_back("matches");

    web::json::value expectedJSON;
    expectedJSON[U("type")] = web::json::value("subscribe");
    expectedJSON[U("product_ids")][0] = web::json::value("BTC-USD");
    expectedJSON[U("product_ids")][1] = web::json::value("BTC-GBP");
    expectedJSON[U("product_ids")][2] = web::json::value("BTC-EUR");
    expectedJSON[U("channels")][0] = web::json::value("level2");
    expectedJSON[U("channels")][1] = web::json::value("matches");

    auto actualJSON = ws.generateSubscriptionMessage(productIds, channels);

    ASSERT_EQ(expectedJSON.serialize(), actualJSON.serialize());
}
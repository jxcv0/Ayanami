#include <gtest/gtest.h>
#include "CBProWebsocket.hpp"
#include <cpprest/json.h>

TEST(CBProWebsocketTests, addLOBTest) {
    Ayanami::CBProWebsocket ws;
    Ayanami::LimitOrderBook btcusdLOB = ws.addLOB("BTC-USD");
    ASSERT_EQ(ws.getLOBCount(), 1);
}

TEST(CBProWebsocketTests, parseSnapshotMessageTest) {

    // Create snapshot message
    web::json::value obj;
    obj[U("type")] = web::json::value("snapshot");
    obj[U("product_id")] = web::json::value("BTC-USD");
    obj[U("bids")] = web::json::value::parse(U("[\"10101.10\", \"0.45054140\"]"));
    obj[U("asks")] = web::json::value::parse(U("[\"10102.55\", \"0.57753524\"]"));

}
#include <gtest/gtest.h>

#include "ftx/ftx_websocket.hpp"

#include <map>

TEST(FTXWebsocketMessageTests, parse_orderbook_snapshot_message) {
    std::string in = Ayanami::file_to_string("test/json_test_cases/ftx_orderbook_snapshot.json");
    Ayanami::FTX::FTX_WebsocketMessage update;
    Ayanami::FTX::parse_ws_response(update, in);

    ASSERT_EQ(update.type, Ayanami::FTX::Type::PARTIAL);
    ASSERT_EQ(update.channel, Ayanami::FTX::Channel::ORDERBOOK);
    ASSERT_EQ(update.market, "BTC-PERP");
    ASSERT_EQ(update.code, 200);
    ASSERT_EQ(update.msg, "OK");

    // bids
    ASSERT_DOUBLE_EQ(update.orderbookData[43075.0], 5.7513);
    ASSERT_DOUBLE_EQ(update.orderbookData[43074.0], 0.1735);
    ASSERT_DOUBLE_EQ(update.orderbookData[43073.0], 0.5737);
    ASSERT_DOUBLE_EQ(update.orderbookData[43072.0], 0.0212);
    ASSERT_DOUBLE_EQ(update.orderbookData[43071.0], 0.484);

    // asks
    ASSERT_DOUBLE_EQ(update.orderbookData[43076.0], -1.443);
    ASSERT_DOUBLE_EQ(update.orderbookData[43077.0], -3.6275);
    ASSERT_DOUBLE_EQ(update.orderbookData[43078.0], -0.5563);
    ASSERT_DOUBLE_EQ(update.orderbookData[43079.0], -0.6228);
    ASSERT_DOUBLE_EQ(update.orderbookData[43080.0], -1.103);
}

TEST(FTXWebsocketMessageTests, parse_orderbook_update_message) {
    std::string in = Ayanami::file_to_string("test/json_test_cases/ftx_orderbook_update.json");
    Ayanami::FTX::FTX_WebsocketMessage update;

    // mock previous data
    update.orderbookData[50694] = 0.1;

    Ayanami::FTX::parse_ws_response(update, in);

    ASSERT_EQ(update.type, Ayanami::FTX::Type::UPDATE);
    ASSERT_EQ(update.channel, Ayanami::FTX::Channel::ORDERBOOK);
    ASSERT_EQ(update.market, "BTC-PERP");
    ASSERT_EQ(update.code, 200);
    ASSERT_EQ(update.msg, "OK");

    // bids
    ASSERT_DOUBLE_EQ(update.orderbookData[42729.0], 6.6028);
    ASSERT_DOUBLE_EQ(update.orderbookData[42698.0], 12.9434);

    // asks
    ASSERT_DOUBLE_EQ(update.orderbookData[42730.0], -1.8567);
    ASSERT_DOUBLE_EQ(update.orderbookData[42732.0], -0.109);
    ASSERT_DOUBLE_EQ(update.orderbookData[42737.0], -1.2402);
    ASSERT_DOUBLE_EQ(update.orderbookData[42741.0], -10.6792);
    ASSERT_DOUBLE_EQ(update.orderbookData[42742.0], -0.561);
    ASSERT_DOUBLE_EQ(update.orderbookData[42747.0], -1.0843);
    ASSERT_DOUBLE_EQ(update.orderbookData[42776.0], -11.1424);
    ASSERT_DOUBLE_EQ(update.orderbookData[42779.0], -2.8618);
    ASSERT_DOUBLE_EQ(update.orderbookData[42825.0], -12.4236);

    // check that previous data has been removed
    ASSERT_EQ(update.orderbookData.size(), 11);
}
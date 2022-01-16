#include <gtest/gtest.h>

#include "ftx/ftx_websocket.hpp"

#include <map>

TEST(FTXWebsocketMessageTests, populate_test) {

    std::map<double, double> orderbook;

    std::string msg = Ayanami::file_to_string("test/json_test_cases/ftx_orderbook_snapshot.json");
    web::json::value json = web::json::value::parse(msg);

    Ayanami::FTX::populate_orderbook(orderbook, json);

    // asks
    ASSERT_DOUBLE_EQ(orderbook[50736], -0.12690000000000001);
    ASSERT_DOUBLE_EQ(orderbook[50737], -0.095699999999999993);
    ASSERT_DOUBLE_EQ(orderbook[50738], -0.68589999999999995);
    ASSERT_DOUBLE_EQ(orderbook[50739], -1.4262999999999999);
    ASSERT_DOUBLE_EQ(orderbook[50740], -1.5772999999999999);
    ASSERT_DOUBLE_EQ(orderbook[50741], -0.098599999999999993);
    ASSERT_DOUBLE_EQ(orderbook[50742], -0.74150000000000005);
    ASSERT_DOUBLE_EQ(orderbook[50743], -0.59109999999999996);

    // bids
    ASSERT_DOUBLE_EQ(orderbook[50735], 6.0541999999999998);
    ASSERT_DOUBLE_EQ(orderbook[50734], 0.053699999999999998);
    ASSERT_DOUBLE_EQ(orderbook[50733], 0.55689999999999995);
    ASSERT_DOUBLE_EQ(orderbook[50732], 0.12529999999999999);
    ASSERT_DOUBLE_EQ(orderbook[50731], 1.8452999999999999);
    ASSERT_DOUBLE_EQ(orderbook[50730], 0.18149999999999999);
    ASSERT_DOUBLE_EQ(orderbook[50729], 1.3488);
    ASSERT_DOUBLE_EQ(orderbook[50728], 0.050000000000000003);
}

TEST(FTXWebsocketMessageTests, update_test) {

    std::map<double, double> orderbook;
    orderbook[50673.0] = 10;
    orderbook[50694.0] = -10;
    orderbook[50696.0] = -10;
    orderbook[50711.0] = -10;
    orderbook[50786.0] = -10;

    std::string msg = Ayanami::file_to_string("test/json_test_cases/ftx_orderbook_update.json");
    web::json::value json = web::json::value::parse(msg);
    Ayanami::FTX::update_orderbook(orderbook, json);

    // bids
    ASSERT_DOUBLE_EQ(orderbook[50673.0], 17.8263);
    
    // asks
    ASSERT_DOUBLE_EQ(orderbook.at(50694.0), -0.35);
    ASSERT_DOUBLE_EQ(orderbook.at(50711.0), -3.2091);
    ASSERT_DOUBLE_EQ(orderbook.at(50786.0), -0.8365);

    // rm 0
    ASSERT_ANY_THROW(orderbook.at(50696));
    ASSERT_EQ(orderbook.size(), 4);
}

TEST(FTXWebsocketMessageTests, parse_trades_msg_test) {
    std::string msg = Ayanami::file_to_string("test/json_test_cases/ftx_trades.json");
    auto ftxMessage = Ayanami::FTX::parse(msg);

    ASSERT_EQ(ftxMessage.type, Ayanami::FTX::Type::UPDATE);
    ASSERT_EQ(ftxMessage.channel, Ayanami::FTX::Channel::TRADES);
    ASSERT_EQ(ftxMessage.market, Ayanami::FTX::Market::BTCPERP);
    ASSERT_EQ(ftxMessage.code, 200);
    ASSERT_EQ(ftxMessage.msg, "OK");
    ASSERT_TRUE(std::holds_alternative<std::vector<Ayanami::FTX::Trades>>(ftxMessage.data));
    
    auto data = std::get<std::vector<Ayanami::FTX::Trades>>(ftxMessage.data);
    ASSERT_EQ(data.size(), 1);

    auto trade = data.front();
    ASSERT_EQ(trade.id, 3084555351);
    ASSERT_DOUBLE_EQ(trade.price, 43345.0);
    ASSERT_DOUBLE_EQ(trade.size, 0.0023);
    ASSERT_EQ(trade.side, Ayanami::FTX::Side::SELL);
    ASSERT_FALSE(trade.liquidation);
    ASSERT_EQ(trade.time, "2022-01-14T21:39:17.451561+00:00");
}

TEST(FTXWebsocketMessageTests, parse_orderbook_msg_test) {
    // std::string msg("TODO");
    // auto parsed_message = Ayanami::FTX::parse(msg);
    ASSERT_TRUE(false);
}
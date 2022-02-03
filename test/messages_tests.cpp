#include <gtest/gtest.h>

#include "messages.hpp"

TEST(MessagesTests, visitor_test) {
    struct IntMessage {
        std::string msg = "int";
    } int_msg;

    struct StringMessage {
        std::string msg = "str";
    } str_msg;

    struct DoubleMessage {
        std::string msg = "double";
    } double_msg;
    
    double result;
    std::string msg;

    Ayanami::Messages::Visitor v {
        [&result, &msg](const IntMessage &m){
            result+=10;
            msg = m.msg;
        },

        [&result, &msg](const StringMessage &m){
            result+=3;
            msg = m.msg;
        },
        
        [&result, &msg](const DoubleMessage &m){
            result+=1.1;
            msg = m.msg;
        }
    };

    Ayanami::Messages::MessageBus<IntMessage, StringMessage, DoubleMessage> bus;
    
    bus(v, int_msg);
    ASSERT_EQ(result, 10);
    ASSERT_EQ(msg, "int");
    bus(v, str_msg);
    ASSERT_EQ(result, 13);
    ASSERT_EQ(msg, "str");
    bus(v, double_msg);
    ASSERT_EQ(result, 14.1);
    ASSERT_EQ(msg, "double");
}

TEST(MessagesTests, push_messages_to_queue) {
    struct Message {};
    Ayanami::Messages::MessageBus<Message> bus;
    for (size_t i = 1; i <= 10; i++) {
        bus.push_back(Message {});
        ASSERT_EQ(bus.size(), i);
    }
}

TEST(MessagesTests, json_file_to_string) {
    std::string expected("{\"channel\": \"trades\", \"market\": \"BTC-PERP\", \"type\": \"update\", \"data\": [{\"id\": 3084555351, \"price\": 43345.0, \"size\": 0.0023, \"side\": \"sell\", \"liquidation\": false, \"time\": \"2022-01-14T21:39:17.451561+00:00\"}]}");
    std::string actual = Ayanami::Messages::file_to_string("test/json_test_cases/ftx_trades.json");
    ASSERT_EQ(actual, expected);
}

TEST(MessagesTests, constexpr_find_type_map) {
    std::string_view sv1("info");
    std::string_view sv2("error");
    ASSERT_EQ(Ayanami::Messages::type_lookup_map[sv1], Ayanami::Messages::MessageType::INFO);
    ASSERT_EQ(Ayanami::Messages::type_lookup_map[sv2], Ayanami::Messages::MessageType::ERROR);
}

TEST(MessageTests, get_message_type) {
    std::string error_json = Ayanami::Messages::file_to_string("test/json_test_cases/ftx_error.json");
    std::string update_json = Ayanami::Messages::file_to_string("test/json_test_cases/ftx_orderbook_update.json");
    std::string snapshot_json = Ayanami::Messages::file_to_string("test/json_test_cases/ftx_orderbook_snapshot.json");
    std::string subscribed_json = Ayanami::Messages::file_to_string("test/json_test_cases/ftx_subscribed.json");

    ASSERT_EQ(Ayanami::Messages::get_type(error_json), Ayanami::Messages::MessageType::ERROR);
    ASSERT_EQ(Ayanami::Messages::get_type(update_json), Ayanami::Messages::MessageType::UPDATE);
    ASSERT_EQ(Ayanami::Messages::get_type(snapshot_json), Ayanami::Messages::MessageType::PARTIAL);
    ASSERT_EQ(Ayanami::Messages::get_type(subscribed_json), Ayanami::Messages::MessageType::SUBSCRIBED);
}

TEST(MessageTests, get_message_channel) {
    std::string update_json = Ayanami::Messages::file_to_string("test/json_test_cases/ftx_orderbook_update.json");
    std::string snapshot_json = Ayanami::Messages::file_to_string("test/json_test_cases/ftx_orderbook_snapshot.json");
    std::string orders_json = Ayanami::Messages::file_to_string("test/json_test_cases/ftx_orders.json");

    ASSERT_EQ(Ayanami::Messages::get_channel(update_json), Ayanami::Messages::Channel::ORDERBOOK);
    ASSERT_EQ(Ayanami::Messages::get_channel(snapshot_json), Ayanami::Messages::Channel::ORDERBOOK);
    ASSERT_EQ(Ayanami::Messages::get_channel(orders_json), Ayanami::Messages::Channel::ORDERS);
}

TEST(MessageTests, get_bids_str) {
    std::string update_json = Ayanami::Messages::file_to_string("test/json_test_cases/ftx_orderbook_update.json");
    Ayanami::Messages::isolate_bid_cluster(update_json);
    ASSERT_EQ(update_json, "[42729.0, 6.6028], [42698.0, 12.9434]");
}

TEST(MessageTests, get_asks_str) {
    std::string update_json = Ayanami::Messages::file_to_string("test/json_test_cases/ftx_orderbook_update.json");
    Ayanami::Messages::isolate_ask_cluster(update_json);
    ASSERT_EQ(update_json, "[42730.0, 1.8567], [42732.0, 0.109], [42737.0, 1.2402], [42741.0, 10.6792], [42742.0, 0.561], [42747.0, 1.0843], [42776.0, 11.1424], [42779.0, 2.8618], [42825.0, 12.4236]");
}

TEST(MessageTests, bids_cluster_to_map) {
    std::map<double, double> bids;
    std::string update_json = Ayanami::Messages::file_to_string("test/json_test_cases/ftx_orderbook_update.json");
    Ayanami::Messages::isolate_bid_cluster(update_json);
    Ayanami::Messages::map_json_cluster(bids, update_json);
    ASSERT_DOUBLE_EQ(bids.at(42729.0), 6.6028);
    ASSERT_DOUBLE_EQ(bids.at(42698.0), 12.9434);
}

TEST(MessageTests, asks_cluster_to_map) {
    std::map<double, double> asks;
    std::string update_json = Ayanami::Messages::file_to_string("test/json_test_cases/ftx_orderbook_update.json");
    Ayanami::Messages::isolate_ask_cluster(update_json);
    Ayanami::Messages::map_json_cluster(asks, update_json);
    ASSERT_DOUBLE_EQ(asks.at(42730.0), 1.8567);
    ASSERT_DOUBLE_EQ(asks.at(42732.0), 0.109);
    ASSERT_DOUBLE_EQ(asks.at(42737.0), 1.2402);
    ASSERT_DOUBLE_EQ(asks.at(42741.0), 10.6792);
    ASSERT_DOUBLE_EQ(asks.at(42742.0), 0.561);
    ASSERT_DOUBLE_EQ(asks.at(42747.0), 1.0843);
    ASSERT_DOUBLE_EQ(asks.at(42776.0), 11.1424);
    ASSERT_DOUBLE_EQ(asks.at(42779.0), 2.8618);
    ASSERT_DOUBLE_EQ(asks.at(42825.0), 12.4236);
}
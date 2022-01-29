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
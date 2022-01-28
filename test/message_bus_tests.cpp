#include <gtest/gtest.h>

#include "message_bus.hpp"

TEST(MessageBusTests, visitor_test) {
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

    Ayanami::Visitor v {
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

    Ayanami::MessageBus<IntMessage, StringMessage, DoubleMessage> bus;
    
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

TEST(MessageBusTests, push_messages_to_queue) {
    struct Message {};
    Ayanami::MessageBus<Message> bus;
    for (size_t i = 1; i <= 10; i++) {
        bus.push_back(Message {});
        ASSERT_EQ(bus.size(), i);
    }
}
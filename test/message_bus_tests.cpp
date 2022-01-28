#include <gtest/gtest.h>

#include "message_bus.hpp"

TEST(MessageBusTests, intended_usage) {
    struct TestMessage1 {};
    struct TestMessage2 {};
    int count = 0;
    Ayanami::MessageBus<TestMessage1, TestMessage2> bus;
    Ayanami::register_callback<TestMessage1>(bus, [&](auto message){ count++; });

    TestMessage1 test1_1;
    TestMessage1 test1_2;

    TestMessage2 test2_1;
    TestMessage2 test2_2;
    TestMessage2 test2_3;

    Ayanami::emplace_message(bus, test1_1);
    Ayanami::emplace_message(bus, test1_2);
    Ayanami::emplace_message(bus, test2_1);
    Ayanami::emplace_message(bus, test2_2);
    Ayanami::emplace_message(bus, test2_3);

    // whyyyyyyyyyyyyy
    ASSERT_EQ(bus.messages().size(), 5);
    // bus.dispatch();
    ASSERT_EQ(count, 2);
}
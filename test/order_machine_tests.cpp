#include <gtest/gtest.h>

#include "order_machine.hpp"

TEST(order_machine_tests, state_test) {


    auto machine = ayanami::get_order_machine();
    machine.on_event(ayanami::place{});
    machine.on_event(ayanami::modify{});
    machine.on_event(ayanami::cancel{});
}
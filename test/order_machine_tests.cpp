#include <gtest/gtest.h>

#include "order_machine.hpp"

#include <map>

TEST(order_machine_tests, state_test) {
    std::map<double, std::pair<double, int>> orders;
    // init orders ...

    // supply orders
    auto machine = ayanami::get_order_machine(orders);

    // mutate
    std::cout << "start collecting\n";
    machine.on_event(ayanami::collect{});
    std::cout << "place orders\n";
    machine.on_event(ayanami::init{});
    std::cout << "modifying orders\n";
    machine.on_event(ayanami::run{});
    std::cout << "closing orders and positions\n";
    machine.on_event(ayanami::close{});
}
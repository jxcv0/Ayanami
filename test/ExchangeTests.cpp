#include <gtest/gtest.h>
#include "Exchange.hpp"

TEST(ExchangeTests, connect_to_ws_test) {
    Ayanami::Exchange ex;
    ex.connect_to_ws();
}
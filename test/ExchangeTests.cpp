#include <gtest/gtest.h>
#include <boost/asio.hpp>
#include "Exchange.hpp"
#include "BybitWS.hpp"

TEST(ExchangeTests, connect_to_ws_test) {
    boost::asio::io_context ioc;
    std::make_shared<Ayanami::Exchange::BybitWS>(ioc)->run();
    ioc.run();
}
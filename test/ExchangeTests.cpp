#include <gtest/gtest.h>
#include <boost/asio.hpp>
#include "Exchange.hpp"
#include "BybitWS.hpp"

TEST(ExchangeTests, connect_to_ws_test) {
    boost::asio::io_context ioc;
    ssl::context ctx{ssl::context::tlsv12_client};
    
    std::make_shared<Ayanami::Exchange::BybitWS>(ioc, ctx)->run();
    ioc.run();
}
#include "BybitWS.hpp"

int main(int argc, char const *argv[])
{
    boost::asio::io_context ioc;
    ssl::context ctx{ssl::context::tlsv12_client};
    
    std::make_shared<ayanami::exchange::BybitWS>(ioc, ctx)
        ->run("{\"op\": \"subscribe\", \"args\": [\"trade.BTCUSD\", \"orderBookL2_25.BTCUSD\"]}");
    ioc.run();
    
    return 0;
}
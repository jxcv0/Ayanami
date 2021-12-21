#include "BybitWSSession.hpp"

int main(int argc, char const *argv[]) {
    boost::asio::io_context ioc;
    ssl::context ctx{ssl::context::tlsv12_client};
    
    std::make_shared<Ayanami::Exchange::BybitWSSession>(ioc, ctx)->run();
    ioc.run();
    
    return 0;
}

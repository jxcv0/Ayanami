#include "Websocket.hpp"

int main(int argc, char const *argv[])
{
    boost::asio::io_context ioc;
    ssl::context ctx{ssl::context::tlsv12_client};

    std::make_shared<ayanami::exchange::Websocket>(ioc, ctx)
        ->run(
            "ftx.com",
            "/ws/",
            "{\"op\": \"subscribe\", \"channel\": \"trades\", \"market\": \"BTC-PERP\"}"
        );

    ioc.run();

    return 0;
}

#include "Websocket.hpp"

int main(int argc, char const *argv[]) {

    // TODO wip

    struct context {
        int inventory_position;
        long time_horizon;
        double risk_aversion;
        double liquidity_param;
    };

    boost::asio::io_context ioc;
    ssl::context ctx{ssl::context::tlsv12_client};
    
    std::make_shared<ayanami::exchange::Websocket>(ioc, ctx)
        ->run(
            "stream.bybit.com",
            "/realtime",
            "{\"op\": \"subscribe\", \"args\": [\"trade.BTCUSD\", \"orderBookL2_25.BTCUSD\"]}"
        );

    ioc.run();
    
    return 0;
}

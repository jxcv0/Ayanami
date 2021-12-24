#include "Websocket.hpp"

#include <iostream>
#include <cpprest/json.h>

/**
 * @brief Strategy state data
 * 
 */
struct State {
    int inventory_position;
    long time_horizon;
    const double risk_aversion = 0.1;
    const double liquidity_param = 1;
    double midprice;
};

/**
 * @brief Market making auto-trader based on the 2008 paper by M. Avellaneda and S. Stoikov
 * 
 * https://www.math.nyu.edu/~avellane/HighFrequencyTrading.pdf
 * 
 */
int main(int argc, char const *argv[]) {
    State state;

    // Subscribe to ticker channel of FTX websocket
    boost::asio::io_context ioc;
    ssl::context ctx{ssl::context::tlsv12_client};
    std::make_shared<ayanami::connections::Websocket>(ioc, ctx)
        ->run(
            "ftx.com",
            "/ws/",
            "{\"op\": \"subscribe\", \"channel\": \"ticker\", \"market\": \"BTC-PERP\"}",
            [&](std::string msg){
                web::json::value json = web::json::value::parse(msg);
                if (json.at("type").as_string() == "update") {
                    web::json::value data = json.at("data");

                    //get midprice
                    state.midprice = (data.at("bid").as_double() + data.at("ask").as_double()) / 2;

                    
                    std::cout << state.midprice << std::endl;
                } else {
                    std::cout << "Un-actionable message recieved: " << msg << std::endl;
                };
            }
        );

    ioc.run();
    return 0;
}
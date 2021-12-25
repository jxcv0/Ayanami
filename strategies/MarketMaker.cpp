#include "Websocket.hpp"
#include "PriceSeries.hpp"
#include "LimitOrderBook.hpp"
#include "ftx/FTX_OrderBookMsgs.hpp"

#include <iostream>
#include <cpprest/json.h>

/**
 * @brief Market making auto-trader based on the 2008 paper by M. Avellaneda and S. Stoikov
 * 
 * https://www.math.nyu.edu/~avellane/HighFrequencyTrading.pdf
 * 
 * 
 * TODO - compare latency with forward declaration
 */
int main(int argc, char const *argv[]) {
    constexpr double RISK_AVERSION_PARAM = 0.01;
    constexpr double LIQUIDITY_PARAM = 1;

    int inv = 0;
    // TODO - time horizon
    long time_horizon = 1;
    double mid;
    
    std::map<double, double> orderbook;
    ayanami::PriceSeries series(1000);

    // Subscribe to ticker channel of FTX websocket
    boost::asio::io_context ioc;
    ssl::context ctx{ssl::context::tlsv12_client};
    std::make_shared<ayanami::connections::Websocket>(ioc, ctx)
        ->run(
            "ftx.com",
            "/ws/",
            "{\"op\": \"subscribe\", \"channel\": \"orderbook\", \"market\": \"BTC-PERP\"}",
            [&](std::string msg){
                web::json::value json = web::json::value::parse(msg);

                std::string type = json.at("type").as_string();

                if (type == "update") { // Update state
                    web::json::value data = json.at("data");
                    ayanami::ftx::update_orderbook(orderbook, data);
                    mid = ayanami::lobs::mid_price(orderbook);
                    series.add_price(mid);

                    // TODO - add time horizon
                    double res_price = mid - (inv * RISK_AVERSION_PARAM * std::pow(series.std_dev(), 2));

                    long time = (long) data.at("time").as_number().to_double();

                    std::cout << mid << " " << res_price << " " << time << std::endl;
                } else if (type == "partial") { // Populate orderbook
                    std::cout << "Populating " << json["market"].as_string() << " orderbook..." << "\n";
                    web::json::value data = json.at("data");
                    ayanami::ftx::populate_orderbook(orderbook, data);
                } else {
                    std::cout << "Message recieved: " << msg << "\n";
                }
            }
        );

    ioc.run();
    return 0;
}
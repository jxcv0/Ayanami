#include "PriceSeries.hpp"
#include "LimitOrderBook.hpp"
#include "ftx/FTX_OrderBookMsgs.hpp"
#include "ftx/FTX_APIRequests.hpp"
#include "APIKeys.hpp"

#include <cpprest/json.h>
#include <cpprest/ws_client.h>

#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <math.h>

/**
 * @brief Market making auto-trader based on the 2008 paper by M. Avellaneda and S. Stoikov
 * 
 * https://www.math.nyu.edu/~avellane/HighFrequencyTrading.pdf
 * 
 * 
 */
int main(int argc, char const *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: market_maker <session duration in mins>\n"
            << "Example:\n" <<
            "   market_maker 60\n";
        return 1;
    }

    // Set up some state data
    constexpr double RISK_AVERSION_PARAM = 0.01;
    constexpr double LIQUIDITY_PARAM = 0.5;

    std::stringstream str(argv[1]);
    unsigned int inc;
    str >> inc;

    assert(inc > 0);

    auto t = std::chrono::system_clock::now();
    double start = std::chrono::duration_cast<std::chrono::milliseconds>(
        t.time_since_epoch()
    ).count();
    
    t += std::chrono::minutes(inc);
    double end = std::chrono::duration_cast<std::chrono::milliseconds>(
        t.time_since_epoch()
    ).count();

    double mid_price;
    int inv = 0;
    
    std::map<double, double> orderbook;

    // TODO - This should use trade feed
    ayanami::PriceSeries series(10000);

    web::websockets::client::websocket_callback_client ws;

    // Main path
    auto path = [&](web::websockets::client::websocket_incoming_message m){
        web::json::value json = web::json::value::parse(
            m.extract_string().get()
        );

        std::string type = json.at("type").as_string();

        if (type == "update") { // Actionable message

            web::json::value data = json.at("data");
            ayanami::ftx::update_orderbook(orderbook, data);

            // Update state
            // TODO - position subscription
            mid_price = ayanami::lobs::mid_price(orderbook);
            series.add_price(mid_price);
            double vol_param = series.variance();

            // Calculate (T - t)
            double time_now = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
            ).count();

            double time_param = (time_now - start) / (end - start);

            if (time_param > 1) {
                ws.close().wait();
            }
            
            // Calculate reservation price
            double res_price = mid_price - (inv * RISK_AVERSION_PARAM * vol_param * time_param);

            // Calculate quotes
            double half_spread = (RISK_AVERSION_PARAM * vol_param * time_param) + ((2 / RISK_AVERSION_PARAM) * log(1 + (RISK_AVERSION_PARAM / LIQUIDITY_PARAM))) / 2;
            double ask = std::round(res_price + half_spread);
            double bid = std::round(res_price - half_spread);
            double spread = ask - bid;

            std::cout << "b: " << bid << " " << "a: " << ask << " spread: " << spread << "\n";

            // Check if orders need changing. If yes place orders

        } else if (type == "partial") { // Populate orderbook
            std::cout << "Populating " << json["market"].as_string() << " orderbook...\n";
            web::json::value data = json.at("data");
            ayanami::ftx::populate_orderbook(orderbook, data);
            std::cout << "Executing...\n" << "\n";

        } else if (type == "error") { // Error messages
            std::cout << "Error: " << json << "\n";
            ws.close().get();

        } else { // All other message types
            std::cout << "Msg: " << json << "\n";
        }
    };

    // Connect to ws
    long time = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();

    web::websockets::client::websocket_outgoing_message login;
    login.set_utf8_message(
        ayanami::ftx::generate_ws_login(time, APIKeys::KEY, APIKeys::SECRET)
    );

    web::websockets::client::websocket_outgoing_message sub_msg;
    sub_msg.set_utf8_message(
        "{\"op\": \"subscribe\", \"channel\": \"orderbook\", \"market\": \"BTC-PERP\"}"
    );

    ws.set_message_handler(path);

    ws.connect("wss://ftx.com/ws/").then([&](){
        ws.send(login);
    }).then([&](){
        ws.send(sub_msg);
    });

    while(true) {
        // do nothing
    }

    // TODO - send subscription msg

    return 0;
}
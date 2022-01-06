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
 */
int main(int argc, char const *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ftxmm <session duration in seconds>\n"
            << "Example:\n" <<
            "   ftxmm 600\n";
        return EXIT_FAILURE;
    }

    // Set up some state data
    constexpr double RISK_AVERSION_PARAM = 0.01; // place holder - needs calculating
    constexpr double LIQUIDITY_PARAM = 0.5; // place holder - needs calculating

    std::stringstream str(argv[1]);
    unsigned int inc;
    str >> inc;

    // start time
    auto t = std::chrono::system_clock::now();
    double start = std::chrono::duration_cast<std::chrono::milliseconds>(
        t.time_since_epoch()
    ).count();
    
    // end time
    t += std::chrono::seconds(inc);
    double end = std::chrono::duration_cast<std::chrono::milliseconds>(
        t.time_since_epoch()
    ).count();

    double mid_price;
    int inv = 0;
    double bid_quote;
    double ask_quote;
    std::map<double, double> market_orderbook;
    ayanami::PriceSeries series(100);
    bool should_close = false;

    // Websocket
    web::websockets::client::websocket_callback_client ws;

    // Forward declaration of JSON objs
    web::json::value json;
    web::json::value data;
    std::string type;
    std::string channel;

    // Main path
    auto path = [&](web::websockets::client::websocket_incoming_message m){
        json = web::json::value::parse(m.extract_string().get());

        type = json.at("type").as_string();
        if (type == "pong") {
            return;
        }

        channel = json.at("channel").as_string();

        if (channel == "orderbook") {
            if (type == "update") { // Update midprice
                data = json.at("data");
                ayanami::ftx::update_orderbook(market_orderbook, data);
                mid_price = ayanami::lobs::mid_price(market_orderbook);

            } else if (type == "partial") { // Populate orderbook
                std::cout << "Populating " << json["market"].as_string() << " orderbook...\n";
                
                data = json.at("data");
                ayanami::ftx::populate_orderbook(market_orderbook, data);

                std::cout << "Executing...\n" << "\n";
            }

        } else if (channel == "trades") { // Update sigma^2
            if (type == "update") {
                data = json.at("data");
                for (auto &&i : data.as_array()) {
                    series.add_price(i.at("price").as_double());
                }
            }

        } else if (channel == "orders") { // Update orders
            if (type == "update") {
                data = json.at("data");
                if (data.at("side").as_string() == "buy") {
                    bid_quote = data.at("price").as_double();

                } else if (data.at("side").as_string() == "sell") {
                    ask_quote = data.at("price").as_double();
                }
            }

        } else if (type == "error") { // Error messages
            std::cout << "Error: " << json << "\n";

            // TODO decide if to close
            // ws.close().get();

        } else { // All other messages
            std::cout << "Msg: " << json << "\n";
        }

        double time_now = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();

        double time_param = (time_now - start) / (end - start);

        if (time_param > 1) {
            should_close = true;
            return;
        }

        double vol = series.variance();

        // Calculate reservation price
        double res_price = 
            mid_price
            - (inv * RISK_AVERSION_PARAM * vol * time_param);

        // Calculate quotes
        double half_spread = 
            ((RISK_AVERSION_PARAM * vol * time_param)
            + ((2 / RISK_AVERSION_PARAM)
            * log(1 + (RISK_AVERSION_PARAM / LIQUIDITY_PARAM)))) / 2;

        double bid = std::round(res_price - half_spread);
        double ask = std::round(res_price + half_spread);

        if (bid != bid_quote) {
            std::cout << "Changing bid from " << bid_quote << " to " << bid << "\n";
            bid_quote = bid;
        }

        if (ask != ask_quote) {
            std::cout << "Changing ask from " << ask_quote << " to " << ask << "\n";
            ask_quote = ask;
        }
    };

    // Connect to ws
    web::websockets::client::websocket_outgoing_message login;
    login.set_utf8_message(
        ayanami::ftx::generate_ws_login(start, APIKeys::KEY, APIKeys::SECRET)
    );

    web::websockets::client::websocket_outgoing_message trade_msg;
    trade_msg.set_utf8_message(
        "{\"op\": \"subscribe\", \"channel\": \"trades\", \"market\": \"BTC-PERP\"}"
    );

    web::websockets::client::websocket_outgoing_message lob_msg;
    lob_msg.set_utf8_message(
        "{\"op\": \"subscribe\", \"channel\": \"orderbook\", \"market\": \"BTC-PERP\"}"
    );

    web::websockets::client::websocket_outgoing_message orders_msg;
    orders_msg.set_utf8_message(
        "{\"op\": \"subscribe\", \"channel\": \"orders\"}"
    );

    web::websockets::client::websocket_outgoing_message ping;
    ping.set_utf8_message(
        "{\"op\": \"ping\"}"
    );

    ws.set_message_handler(path);

    ws.connect("wss://ftx.com/ws/").then([&](){
        std::cout << "Authenticating websocket connection ...\n";
        ws.send(login);
    }).then([&](){
        std::cout << "Subscribing to trades channel ...\n";
        ws.send(trade_msg);
    }).then([&](){
        std::cout << "Subscribing to orderbook channel ...\n";
        ws.send(lob_msg);
    }).then([&](){
        std::cout << "Subscribing to orders channel ...\n";
        ws.send(orders_msg);
    });

    while(!should_close) {
        sleep(15);
        std::cout << "Sending ping\n";
        ws.send(ping);
    }

    ws.close().wait();

    return EXIT_SUCCESS;
}
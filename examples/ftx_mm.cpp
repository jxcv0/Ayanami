#include "price_series.hpp"
#include "limit_order_book.hpp"
#include "ftx/ftx_ws.hpp"
#include "ftx/ftx_rest.hpp"
#include "api_keys.hpp"
#include "avellaneda_stoikov.hpp"

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

    std::map<double, double> market_orderbook;
    ayanami::price_series series(50);
    ayanami::av::av_in av_in(0.01, 0.1, 0);
    ayanami::av::av_out av_out;

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
                av_in.mid = ayanami::lobs::mid_price(market_orderbook);

            } else if (type == "partial") { // Populate orderbook
                std::cout << "Populating " << json["market"].as_string() << " orderbook...\n";
                
                data = json.at("data");
                ayanami::ftx::populate_orderbook(market_orderbook, data);

                std::cout << "Executing...\n" << "\n";
            }

        } else if (channel == "trades") { // Update vol
            if (type == "update") {
                data = json.at("data");
                for (auto &&i : data.as_array()) {
                    series.add_price(i.at("price").as_double());
                }

                double time_now = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()
                ).count();

                av_in.time = (time_now - start) / (end - start);

                if (av_in.time > 1) {
                    // TODO decide if to close
                    ws.close().get();
                    return;
                }

                av_in.vol = series.variance();

                // Calculate reservation price
                ayanami::av::res_price(av_in, av_out);

                // Calculate spread
                ayanami::av::spread(av_in, av_out);

                // Calculate quotes
                std::cout << "bid: " << std::round(av_out.res - (av_out.spread / 2)) << "\n";
                std::cout << "ask: " << std::round(av_out.res + (av_out.spread / 2)) << "\n\n";

                std::cout << "mid: " << av_in.mid << "\n";
                std::cout << "inv: " << av_in.inv << "\n";
                std::cout << "risk: " << av_in.risk << "\n";
                std::cout << "vol: " << av_in.vol << "\n";
                std::cout << "liq: " << av_in.liq << "\n";
                std::cout << "time: " << av_in.time << "\n\n";
            }

        } else if (channel == "orders") { // Update orders
            if (type == "update") {
                data = json.at("data");
                if (data.at("side").as_string() == "buy") {
                    // TODO

                } else if (data.at("side").as_string() == "sell") {
                    // TODO ? = data.at("price").as_double();
                }
            }

        } else if (type == "error") { // Error messages
            std::cout << "Error: " << json << "\n";

            // TODO decide if to close
            ws.close().get();

        } else { // All other messages
            std::cout << "Msg: " << json << "\n";
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

    for(;;) {
        sleep(15);
        std::cout << "Sending ping\n";
        ws.send(ping); // this crashes if ws is closed
    }

    return EXIT_SUCCESS;
}
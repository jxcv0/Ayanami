#define _TURN_OFF_PLATFORM_STRING

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

    constexpr double TICK_SIZE = 1;
    constexpr double ORDER_SIZE = 0.0001;

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

    http::request<http::string_body> req;
    http::response<http::dynamic_body> res;

    std::map<double, double> market_orderbook;
    std::map<double, int> bids; // strategy bids
    std::map<double, int> asks; // strategy asks
    ayanami::price_series series(50);
    ayanami::av::av_in av_in(0.01, 0.1, 0);
    ayanami::av::av_out av_out;

    // Websocket and Https
    web::websockets::client::websocket_callback_client ws;
    web::json::value json;
    web::json::value data;
    std::string type;
    std::string channel;

    bool ready = false;

    // Main path
    auto path = [&](web::websockets::client::websocket_incoming_message m){
        // TODO - This time with no spaghetti
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
        ready = true;
        ws.send(ping); // this crashes if ws is closed
    }

    return EXIT_SUCCESS;
}
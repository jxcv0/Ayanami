#define _TURN_OFF_PLATFORM_STRING

#include "limit_order_book.hpp"
#include "ftx/ftx_websocket.hpp"
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
 * 
 * @brief WORK IN PROGRESS
 * 
 */
int main(int argc, char const *argv[]) {

    // market orderbook
    std::map<float, float> orderbook;

    // strategy orderbook
    std::map<float, std::pair<float, int>> orders;

    // websocket
    web::websockets::client::websocket_callback_client ws;

    // Main path
    auto path = [&](web::websockets::client::websocket_incoming_message msg){
        // TODO - This time with no spaghetti
        std::string sv_msg(msg.extract_string().get());
        std::cout << sv_msg << "\n";
    };

    // Connect to ws - TODO start time
    web::websockets::client::websocket_outgoing_message login;
    login.set_utf8_message(
        Ayanami::FTX::generate_ws_login(1, APIKeys::KEY, APIKeys::SECRET)
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
        std::cout << "Sending ping\n\n";
        ws.send(ping); // this crashes if ws is closed
        std::cout << "\n\n";
    }

    return EXIT_SUCCESS;
}
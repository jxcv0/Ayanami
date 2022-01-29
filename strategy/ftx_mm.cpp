#define _TURN_OFF_PLATFORM_STRING // cppresdk

#include "limit_order_book.hpp"
#include "ftx/ftx_api.hpp"
#include "api_keys.hpp"
#include "encryption.hpp"
#include "avellaneda_stoikov.hpp"
#include "https.hpp"
#include "simdjson.h"

#include <cpprest/ws_client.h>

/**
 *
 * @brief WORK IN PROGRESS
 *
 */
int main(int argc, char const *argv[]) {
    // strategy state
    Ayanami::AV::AvIn in(1, 1, 1, 1);
    Ayanami::AV::AvOut out;

    // req and res
    http::request<http::string_body> req;
    http::response<http::dynamic_body> res;

    // market orderbook
    std::map<double, double> orderbook;
    std::map<double, double> update;

    // strategy orderbook
    std::map<double, std::pair<double, int>> bids;
    std::map<double, std::pair<double, int>> asks;

    // websocket
    web::websockets::client::websocket_callback_client ws;

    // TODO - MessageBus

    // Main path
    simdjson::dom::parser parser;
    auto handle_message = [&](web::websockets::client::websocket_incoming_message msg){
        simdjson::dom::object doc = parser.parse(msg.extract_string().get());
        // 
    };

    // Connect to ws
    web::websockets::client::websocket_outgoing_message login;
    login.set_utf8_message(
        Ayanami::FTX::generate_ws_login(Ayanami::get_time(), APIKeys::KEY, APIKeys::SECRET));

    web::websockets::client::websocket_outgoing_message lobMessage;
    lobMessage.set_utf8_message(
        "{\"op\": \"subscribe\", \"channel\": \"orderbook\", \"market\": \"BTC-PERP\"}");

    web::websockets::client::websocket_outgoing_message ordersMessage;
    ordersMessage.set_utf8_message("{\"op\": \"subscribe\", \"channel\": \"orders\"}");

    web::websockets::client::websocket_outgoing_message fillsMessage;
    fillsMessage.set_utf8_message("{\"op\": \"subscribe\", \"channel\": \"fills\"}");

    web::websockets::client::websocket_outgoing_message ping;
    ping.set_utf8_message("{\"op\": \"ping\"}");

    ws.set_message_handler(handle_message);

    ws.connect("wss://ftx.com/ws/")
        .then([&](){ ws.send(login); })
        .then([&](){ ws.send(lobMessage); })
        .then([&](){ ws.send(ordersMessage); })
        .then([&](){ ws.send(fillsMessage); })
        .wait();

    for(;;) {
        std::this_thread::sleep_for(std::chrono::seconds(15));
        std::cout << "[INFO] Ping sent\n";
        ws.send(ping);
    }

    return 0;
}
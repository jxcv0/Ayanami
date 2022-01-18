#define _TURN_OFF_PLATFORM_STRING // cppresdk

#include "limit_order_book.hpp"
#include "ftx/ftx_rest.hpp"
#include "api_keys.hpp"

#include "simdjson.h"

#include <cpprest/ws_client.h>

/**
 * 
 * @brief WORK IN PROGRESS
 * 
 */
int main(int argc, char const *argv[]) {

    // market orderbook
    std::map<double, double> orderbook;

    // strategy orderbook
    std::map<double, std::pair<double, int>> orders;

    // websocket
    web::websockets::client::websocket_callback_client ws;

    // TODO - make constexpr
    std::map<std::string_view, std::function<void(const simdjson::dom::element&)>> funcMap = {
        // type
        {"update", [&](auto doc){ funcMap[doc["channel"]](doc); }},

        {"partial", [&](auto doc){ funcMap[doc["channel"]](doc); }},

        {"error", [&](auto doc){
            std::cout << "[ERROR] Code: "<< doc["code"] << " " << doc["msg"] << "\n";
            ws.close();
            exit(1);
        }},

        {"subscribed", [&](auto doc){
            std::cout << "[SUBSCRIBED] Channel: " << doc["channel"] << "\n"; }},

        {"unsubscribed", [&](auto doc){
            std::cout << "[UNSUBSCRIBED] Channel: " << doc["channel"] << "\n"; }},

        {"info", [&](auto doc){ 
            std::cout << "[INFO] Message: " << doc["msg"] << "\nCode: " << doc["code"] << "\n";}},

        // channel
        {"orderbook", [&](auto doc){
            // handle orderbook message 
            std::cout << doc["channel"] << "\n";
        }},
        {"orders", [&](auto doc){
            // handle orders message
            std::cout << doc["channel"] << "\n";
        }},
        {"fills", [&](auto doc){
            // handle fills message
            std::cout << doc["channel"] << "\n";
        }}
        // {"trades", [&](){ /* not required if using constant volatility */ }}
    };

    // Main path
    simdjson::dom::parser parser;
    auto handle_message = [&](web::websockets::client::websocket_incoming_message msg){
        simdjson::padded_string json(msg.extract_string().get());
        simdjson::dom::element doc = parser.parse(json);
        funcMap[doc["type"]](doc);
    };

    // Connect to ws - TODO start time
    web::websockets::client::websocket_outgoing_message login;
    login.set_utf8_message(Ayanami::FTX::generate_ws_login(1, APIKeys::KEY, APIKeys::SECRET));

    web::websockets::client::websocket_outgoing_message lobMessage;
    lobMessage.set_utf8_message(
        "{\"op\": \"subscribe\", \"channel\": \"orderbook\", \"market\": \"BTC-PERP\"}");

    web::websockets::client::websocket_outgoing_message ordersMessage;
    ordersMessage.set_utf8_message("{\"op\": \"subscribe\", \"channel\": \"orders\"}");

    web::websockets::client::websocket_outgoing_message fillsMessage;
    ordersMessage.set_utf8_message("{\"op\": \"subscribe\", \"channel\": \"fills\"}");

    web::websockets::client::websocket_outgoing_message ping;
    ping.set_utf8_message("{\"op\": \"ping\"}");

    ws.set_message_handler(handle_message);

    ws.connect("wss://ftx.com/ws/")
        .then([&](){ws.send(login);})
        .then([&](){ ws.send(lobMessage); })
        .then([&](){ ws.send(ordersMessage); });

    for(;;) {
        sleep(15);
        std::cout << "[PING]\n";
        ws.send(ping); // this crashes if ws is closed
    }

    return EXIT_SUCCESS;
}
#include "Exchange.hpp"
#include <cpprest/ws_client.h>
#include <cpprest/ws_msg.h>

void Ayanami::Exchange::connect_to_ws() {
    web::web_sockets::client::websocket_callback_client client;

    web::web_sockets::client::websocket_outgoing_message msg; 
    msg.set_utf8_message("{\"op\": \"subscribe\", \"args\": [\"trade.*\"]}");

    client.connect(U("wss://stream.bybit.com/realtime")).then([&](){client.send(msg); }).get();

    client.set_message_handler([](web::web_sockets::client::websocket_incoming_message msg){
        std::cout << msg.extract_string().get() << "\n";
    });
};
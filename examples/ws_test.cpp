#include <cpprest/ws_client.h>

int main() {
    web::websockets::client::websocket_outgoing_message msg;
    msg.set_utf8_message("{\"op\": \"subscribe\", \"args\": [\"trade\"]}");

    web::websockets::client::websocket_callback_client ws;
    auto on_msg = [](web::websockets::client::websocket_incoming_message m) {
        std::string s = m.extract_string().get();
        std::cout << s << "\n";
    };
    ws.set_message_handler(on_msg);

    ws.connect("wss://stream.bybit.com/realtime").then([&](){
        ws.send(msg);
    }).wait();

    while(true) {
        // do nothing
    }
}
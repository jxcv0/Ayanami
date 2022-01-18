#define _TURN_OFF_PLATFORM_STRING // cppresdk

#include <cpprest/ws_client.h>
#include <cpprest/json.h>

#include <fstream>

int main() {
    
    std::ofstream file;
    web::websockets::client::websocket_callback_client ws;

    // save json to file
    ws.set_message_handler([&](const auto &message){
        file.open("strategy/backtest.json", std::ios_base::app);
        web::json::value json = web::json::value::parse(message.extract_string().get());
        file << json;
        file << "\n";
        file.close();
    });

    // ping
    web::websockets::client::websocket_outgoing_message ping;
    ping.set_utf8_message(
        "{\"op\": \"ping\"}"
    );

    // subscribe
    web::websockets::client::websocket_outgoing_message lobMessage;
    lobMessage.set_utf8_message(
        "{\"op\": \"subscribe\", \"channel\": \"orderbook\", \"market\": \"BTC-PERP\"}"
    );
    
    // connect
    ws.connect("wss://ftx.com/ws/").then([&](){ ws.send(lobMessage); }).get();

    for(;;) {
        sleep(15);
        std::cout << "Sending ping\n";
        ws.send(ping);
    }
}
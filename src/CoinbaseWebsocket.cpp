#include "CoinbaseWebsocket.hpp"

Ayanami::CoinbaseWebsocket::CoinbaseWebsocket() {};

void Ayanami::CoinbaseWebsocket::connect() {
    client.connect(web::uri::encode_uri("wss://ws-feed.exchange.coinbase.com"));
}

web::json::value Ayanami::CoinbaseWebsocket::generateSubscriptionMessage(
    std::vector<std::string> &productIds,
    std::vector<std::string> &channels) {

    web::json::value message;
    message[U("type")] = web::json::value("subscribe");

    for (size_t i = 0; i < productIds.size(); i++)
    {
        message[U("product_ids")][i] = web::json::value(productIds.at(i));
    }

    for (size_t i = 0; i < channels.size(); i++)
    {
        message[U("channels")][i] = web::json::value(channels.at(i));
    }

    return message;
};
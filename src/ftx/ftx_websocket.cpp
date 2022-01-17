#include "ftx/ftx_websocket.hpp"

#include <cpprest/json.h>

/**
 * @brief Reset all fields in this message
 * 
 */
void Ayanami::FTX::FTX_WebsocketMessage::reset() {
    this->type = Type::NONE;
    this->channel = Channel::NONE;
    this->market = "";
    this->code = 0;
    this->msg = "";
    this->orderbookData.clear();
    this->ordersData.clear();
}

/**
 * @brief Convrt an orderbook message from the FTX websocket into the standard OrderbookMsg
 * type
 * 
 * @param str the message to parse
 * @return a struct containing the message values
 */
void Ayanami::FTX::parse_ws_response(FTX_WebsocketMessage &update, const std::string& str) {
    update.reset();
    web::json::value json = web::json::value::parse(str); // TODO - faster
    update.type = typeMap.at(json["type"].as_string().c_str());

    // update and partial types will always have a data field
    if (update.type == Type::UPDATE || update.type == Type::PARTIAL) {
        update.channel = channelMap.at(json["channel"].as_string().c_str());
        update.market = json["market"].as_string().c_str();
        update.code = 200;
        update.msg = "OK";

        // orderbook
        if (update.channel == Channel::ORDERBOOK) {

            // bids
            auto bids = json["data"]["bids"].as_array();
            std::for_each(bids.begin(), bids.end(), [&](auto &bid){
                    update.orderbookData[bid[0].as_double()] = bid[1].as_double();
                }
            );

            // asks
            auto asks = json["data"]["asks"].as_array();
            std::for_each(asks.begin(), asks.end(), [&](auto &ask){
                    update.orderbookData[ask[0].as_double()] = -ask[1].as_double();
                }
            );
        }
    }
}
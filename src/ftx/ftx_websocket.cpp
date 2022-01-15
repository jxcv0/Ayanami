#include "ftx/ftx_websocket.hpp"

#include <cpprest/json.h>

// TODO - this can be made wayyyy faster
Ayanami::FTX::FTXWebsocketMsg Ayanami::FTX::parse(const std::string& str) {
    web::json::value json = web::json::value::parse(str);
    FTXWebsocketMsg message;

    // message will always have a type
    std::string_view type(json["type"].as_string().c_str());
    message.type = typeMap.at(type);

    // update and partial types will always have a data field
    if (message.type == Type::UPDATE) {
        std::string_view channel(json["channel"].as_string().c_str());
        std::string_view market(json["market"].as_string().c_str());
        message.channel = channelMap.at(channel);
        message.market = marketMap.at(market);
        message.code = 200;
        message.msg = "OK";

        // trades data comes in a JSON array of JSON objs
        if (message.channel == Channel::TRADES) {
            std::vector<Trades> vec;
            for (auto &&i : json["data"].as_array()) {
                Trades trades;
                trades.id = i["id"].as_integer();
                trades.price = i["price"].as_double();
                trades.size = i["size"].as_double();
                std::string_view side = i["side"].as_string().c_str();
                trades.side = sideMap.at(side);
                trades.liquidation = i["liquidation"].as_bool();
                trades.time = i["time"].as_string().c_str();
                vec.push_back(trades);
            }
        
        // orderbook data comes in JSON obj of arrays
        } else if (message.channel == Channel::ORDERBOOK) {
            // do the things
        }
    // message is an orderbook snapshot    
    } else if (message.type == Type::PARTIAL) {
        // do the things
    }
    std::string_view market(json["market"].as_string().c_str());
    message.market = marketMap.at(market);

    return message;
}

/**
 * @brief Populate an orderbook with a "partial" JSON message
 * 
 * @param orderbook the orderbook to populate
 * @param data the "data" field of the JSON message
 */
void Ayanami::FTX::populate_orderbook(std::map<double, double>& orderbook, web::json::value& data) {
    web::json::array asks = data["asks"].as_array();
    for (auto &&i : asks) {
        orderbook[i[0].as_double()] = -i[1].as_double();
    }
    web::json::array bids = data["bids"].as_array();
    for (auto &&i : bids) {
        orderbook[i[0].as_double()] = i[1].as_double();
    }
}

/**
 * @brief Update and orderbook with an "update" JSON message
 * 
 * @param orderbook the orderbook to update
 * @param data the "data" field of the JSON message
 */
void Ayanami::FTX::update_orderbook(std::map<double, double>& orderbook, web::json::value& data) {
    for (auto &&i : data["asks"].as_array()) {
        double key = i[0].as_double();
        double val = -i[1].as_double();
        if (val < 0) {
            orderbook[key] = val;
        } else {
            orderbook.erase(key);
        }
    }

    for (auto &&i : data["bids"].as_array()) {
        double key = i[0].as_double();
        double val = i[1].as_double();
        if (val > 0) {
            orderbook[key] = val;
        } else {
            orderbook.erase(key);
        }
    }
}
#include "ftx/FTX_OrderBookMsgs.hpp"

#include <algorithm>

/**
 * @brief Populate an orderbook with a "partial" JSON message
 * 
 * @param orderbook the orderbook to populate
 * @param data the "data" field of the JSON message
 */
void ayanami::ftx::populate_orderbook(std::map<double, double>& orderbook, web::json::value data) {
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
void ayanami::ftx::update_orderbook(std::map<double, double>& orderbook, web::json::value data) {
    web::json::array asks = data["asks"].as_array();
    for (auto &&i : asks) {
        double val = -i[1].as_double();
        if (val < 0) {
            orderbook[i[0].as_double()] = val;
        } else {
            orderbook.erase(i[0].as_double());
        }
    }
    web::json::array bids = data["bids"].as_array();
    for (auto &&i : bids) {
        double val = i[1].as_double();
        if (val > 0) {
            orderbook[i[0].as_double()] = val;
        } else {
            orderbook.erase(i[0].as_double());
        }
    }
}
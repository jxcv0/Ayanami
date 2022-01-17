#include "limit_order_book.hpp"

#include <algorithm>


void Ayanami::LOB::update_orderbook(std::map<double, double> &orderbook,
    const std::map<double, double> &update) {
    // TODO
}

/**
 * @brief Get the best bid from an orderbook
 * 
 * @param orderbook the orderbook
 * @return the best buying price
 */
double Ayanami::LOB::best_bid(std::map<double, double>& orderbook) {
    std::map<double, double> bids;
    std::copy_if(orderbook.begin(), orderbook.end(), std::inserter(bids, bids.begin()),
        [](std::pair<double, double> p){ return p.second > 0; });

    return bids.rbegin()->first;
}

/**
 * @brief Get the best ask from an orderbook
 * 
 * @param orderbook the orderbook
 * @return the best asking price
 */
double Ayanami::LOB::best_ask(std::map<double, double>& orderbook) {
    std::map<double, double> asks;
    std::copy_if(orderbook.begin(), orderbook.end(), std::inserter(asks, asks.begin()),
        [](std::pair<double, double> p){ return p.second < 0; });

    return asks.begin()->first;
}

/**
 * @brief Get the midprice of an orderbook
 * 
 * @param orderbook the orderbook
 * @return the midprice
 */
double Ayanami::LOB::mid_price(std::map<double, double>& orderbook) {
    return (best_ask(orderbook) + best_bid(orderbook)) / 2;
}
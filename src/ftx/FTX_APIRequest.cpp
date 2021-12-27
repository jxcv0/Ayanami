#include "ftx/FTX_APIRequest.hpp"

#include <cpprest/json.h>

#include <iostream>
/**
 * @brief Create the JSON for an order reqest to the FTX API
 * 
 * @param market e.g. "BTC/USD" for spot, "XRP-PERP" for futures
 * @param side "buy" or "sell"
 * @param price the order price (null for market orders)
 * @param type "limit" or "market"
 * @param size the order size
 * @param reduce_only true if order should be reduce only
 * @param post_only true if order should be post only
 * @return std::string 
 */
std::string ayanami::ftx::generate_order_request(std::string market, std::string side, double price, std::string type, double size, bool reduce_only, bool post_only) {
    // TODO
    web::json::keep_object_element_order(true);
    web::json::value req;
    req[U("market")] = web::json::value(market);
    req[U("side")] = web::json::value(side);
    req[U("price")] = web::json::value(price);
    req[U("size")] = web::json::value(size);
    req[U("type")] = web::json::value(type);
    req[U("reduceOnly")] = web::json::value(reduce_only);
    req[U("postOnly")] = web::json::value(post_only);
    return req.serialize().c_str();
}

/**
 * @brief Generate encryption sign for requests to private endpoints
 * 
 * @param timestamp Number of milliseconds since Unix epoch
 * @param method HTTP method in uppercase (e.g. GET or POST)
 * @param path Request path, including leading slash and any URL parameters but not including the hostname (e.g. /account)
 * @param post (POST only) Request body (JSON-encoded)
 * @return the sign
 */
std::string ayanami::ftx::generate_sign(long timestamp, std::string method, std::string path, std::string post) {
    // TODO
}
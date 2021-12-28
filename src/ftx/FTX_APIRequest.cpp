#include "ftx/FTX_APIRequest.hpp"
#include "Encryption.hpp"
#include "APIKeys.hpp"

#include <cpprest/json.h>
#include <iostream>

/**
 * @brief Create order request string for the FTX API
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
std::string ayanami::ftx::generate_order_req(std::string market, std::string side, double price, std::string type, double size, bool reduce_only, bool post_only) {
    // TODO
    web::json::keep_object_element_order(true);
    web::json::value req;
    req[U("market")] = web::json::value(market);
    req[U("side")] = web::json::value(side);
    req[U("price")] = web::json::value(price);
    req[U("size")] = web::json::value(size);
    req[U("type")] = web::json::value(type);
    req[U("reduceOnly")] = web::json::value(reduce_only);
    req[U("ioc")] = web::json::value(false);
    req[U("postOnly")] = web::json::value(post_only);
    req[U("clientId")] = web::json::value(web::json::value::null());
    return req.serialize().c_str();
}
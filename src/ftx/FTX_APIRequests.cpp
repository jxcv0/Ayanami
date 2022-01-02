#include "ftx/FTX_APIRequests.hpp"
#include "Encryption.hpp"
#include "APIKeys.hpp"

#include <cpprest/json.h>
#include <string>

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
std::string ayanami::ftx::generate_order_json(std::string market, std::string side, double price, std::string type, double size, bool reduce_only, bool post_only) {
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
    std::string str(req.serialize());
    return ayanami::spacify(str);
}

/**
 * @brief Create string for order POST request header for the FTX API
 * 
 * @param time the time in epoch seconds
 * @param json the order JSON
 * @return the request header string
 */
std::string ayanami::ftx::generate_order_header(long time, std::string& json) {
    return std::to_string(time) + "POST" + "/api/orders" + json;
}

/**
 * @brief Generate authentification sign for private topics
 * 
 * @param time int timestamp in ms (unix)
 * @param secret the secret key
 * @return the login sign
 */
std::string ayanami::ftx::generate_ws_sign(long time, const char* secret) {
    std::string str(std::to_string(time) + "websocket_login");
    return ayanami::hmac_sha256(secret, str.c_str());
}

/**
 * @brief Generate ftx websocket login JSON
 * 
 * @param time int timestamp in seconds (unix)
 * @param key the public key
 * @param secret the secret key
 * @return the login JSON
 */
std::string ayanami::ftx::generate_ws_login(long time, const char *key, const char *secret) {
    web::json::keep_object_element_order(true);
    web::json::value args;
    args[U("key")] = web::json::value(key);
    args[U("sign")] = web::json::value(generate_ws_sign(time, secret));
    args[U("time")] = web::json::value(time);

    web::json::value msg;
    msg[U("args")] = web::json::value(args);
    msg[U("op")] = web::json::value("login");
    std::string str(msg.serialize());
    return ayanami::spacify(str);
}
#include "ftx/ftx_api.hpp"
#include "encryption.hpp"
#include "api_keys.hpp"
#include "https.hpp"

#include <cpprest/json.h>
#include <string>
#include <functional>

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
std::string Ayanami::FTX::generate_order_json(
    std::string market, std::string side, double price, std::string type, double size, bool reduce_only,
    bool post_only) {
        
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
    return Ayanami::spacify(str);
}

/**
 * @brief Create string for order POST request header for the FTX API
 * 
 * @param time the time in epoch seconds
 * @param json the order JSON
 * @return the request header string
 */
std::string Ayanami::FTX::generate_sign_str(long time, const char* target, std::string& json) {
    return std::to_string(time) + "POST" + target + json;
}

/**
 * @brief Generate authentification sign for private topics
 * 
 * @param time int timestamp in ms (unix)
 * @param secret the secret key
 * @return the login sign
 */
std::string Ayanami::FTX::generate_ws_sign(long time, const char* secret) {
    std::string str(std::to_string(time) + "websocket_login");
    return Ayanami::hmac_sha256(secret, str.c_str());
}

/**
 * @brief Generate FTX websocket login JSON
 * 
 * @param time int timestamp in seconds (unix)
 * @param key the public key
 * @param secret the secret key
 * @return the login JSON
 */
std::string Ayanami::FTX::generate_ws_login(long time, const char* key, const char* secret) {
    web::json::keep_object_element_order(true);
    web::json::value args;
    args[U("key")] = web::json::value(key);
    args[U("sign")] = web::json::value(generate_ws_sign(time, secret));
    args[U("time")] = web::json::value(time);

    web::json::value msg;
    msg[U("op")] = web::json::value("login");
    msg[U("args")] = web::json::value(args);
    std::string str(msg.serialize());
    return Ayanami::spacify(str);
}

using request = http::request<http::string_body>;
using response = http::response<http::dynamic_body>;

void Ayanami::FTX::generate_order_request(request& req, std::string time, const char* key,
    std::string sign) {

    req.clear();
    
    req.method(http::verb::post);
    req.target("https://FTX.com/api/orders");
    req.set("FTX-KEY", key);
    req.set("FTX-TS", time);
    req.set("FTX-SIGN", sign);
}

void Ayanami::FTX::generate_modify_request(request& req, std::string time, const char* key,
    const char* secret, int id, double price, double size) { 

    req.clear();

    std::string id_str = std::to_string(id);
    std::string target("https://FTX.com/orders/" + id_str + "/modify");

    std::string json(
        "{\"price\": " + std::to_string(price) + ", \"size\": " + std::to_string(size) + "}"
    );
    std::string sign(time + "POST" + "/orders/" + id_str + "/modify" + json);
    req.method(http::verb::post);
    req.target("https://FTX.com/orders/123456/modify");
    req.set("FTX-KEY", key);
    req.set("FTX-TS", time);
    req.set("FTX-SIGN", Ayanami::hmac_sha256(secret, sign.c_str()));
}

std::map<std::string_view, std::string_view> Ayanami::FTX::get_fix_default(const char *key) {
    std::map<std::string_view, std::string_view> map = {
        {"8", "FIX.4.2"},
        {"9", "162"},
        {"35", "A"},
        {"49", key},
        {"56", "FTX"}
    };
    return map;
}
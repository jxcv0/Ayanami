#ifndef FTX_APIREQUESTS_HPP
#define FTX_APIREQUESTS_HPP

#include "https.hpp"

#include <string>
#include <map>

namespace Ayanami {

    /**
     * @brief Connection managment for FTX exchange
     * 
     */
    namespace FTX {

        /**
         * @brief Create order JSON for the FTX API
         * 
         * @param market e.g. "BTC/USD" for spot, "XRP-PERP" for futures
         * @param side "buy" or "sell"
         * @param price the order price (null for market orders)
         * @param type "limit" or "market"
         * @param size the order size
         * @param reduce_only true if order should be reduce only
         * @param post_only true if order should be post only
         * @return the order JSON
         */
        std::string generate_order_json(
            std::string market, std::string side, double price, std::string type, double size,
            bool reduce_only, bool post_only);

        /**
         * @brief Create string for order POST request header for the FTX API
         * 
         * @param time the time in epoch seconds
         * @param json the order JSON
         * @return the request header string
         */
        std::string generate_sign_str(long time, const char* target, std::string& json);

        /**
         * @brief Generate authentification sign for private topics
         * 
         * @param time int timestamp in seconds (unix)
         * @param secret the secret key
         * @return the login sign
         */
        std::string generate_ws_sign(long time, const char* secret);

        /**
         * @brief Generate FTX websocket login JSON
         * 
         * @param time int timestamp in seconds (unix)
         * @param key the public key
         * @param secret the secret key
         * @return the login JSON
         */
        std::string generate_ws_login(long time, const char* key, const char* secret);

        using request = http::request<http::string_body>;
        using response = http::response<http::dynamic_body>;

        /**
         * @brief Set up an order request so that it places an order when send
         * 
         * @param req the request
         * @param res the response
         * @param time the time as epoch millisecond
         * @param key the api key
         * @param sign the authentification sign for private api endpoints
         */
        void generate_order_request(request& req, std::string time, const char* key, std::string sign);

        /**
         * @brief Set up a request so that it modifies an order when sent
         * 
         * @param req the request
         * @param time the response
         * @param key the api key
         * @param secret the api secret
         * @param id the order id
         * @param price the new price
         * @param size the new size
         */
        void generate_modify_request(request& req, std::string time, const char* key,
            const char* secret, int id, double price, double size);

        /**
         * @brief Generate the mandatory default header fields for FTX FIX api messsages as key
         * value pairs
         * 
         * @param key the API key
         * @return map of mandatory default key values pair 
         */
        std::map<std::string_view, std::string_view> get_fix_default(const char *key);

        std::map<std::string_view, std::string_view> get_fix_logon(
            std::map<std::string_view, std::string_view> &base);
    } // namespace FTX
} // namespace Ayanami

#endif
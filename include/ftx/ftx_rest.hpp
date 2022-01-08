#ifndef FTX_APIREQUESTS_HPP
#define FTX_APIREQUESTS_HPP

#include "https.hpp"

#include <string>
#include <map>

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace ayanami {

    /**
     * @brief Connection managment for FTX exchange
     * 
     */
    namespace ftx {

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
        std::string generate_order_header(long time, std::string& json);

        /**
         * @brief Generate authentification sign for private topics
         * 
         * @param time int timestamp in seconds (unix)
         * @param secret the secret key
         * @return the login sign
         */
        std::string generate_ws_sign(long time, const char* secret);

        /**
         * @brief Generate ftx websocket login JSON
         * 
         * @param time int timestamp in seconds (unix)
         * @param key the public key
         * @param secret the secret key
         * @return the login JSON
         */
        std::string generate_ws_login(long time, const char* key, const char* secret);
    } // namespace ftx
} // namespace ayanami

#endif
#ifndef FTX_APIREQUESTS_HPP
#define FTX_APIREQUESTS_HPP

#include <string>

namespace ayanami {
    namespace ftx {

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
        std::string generate_order_request(std::string market, std::string side, double price, std::string type, double size, bool reduce_only, bool post_only);

        /**
         * @brief Generate encryption sign for requests to private endpoints
         * 
         * @param timestamp Number of milliseconds since Unix epoch
         * @param method HTTP method in uppercase (e.g. GET or POST)
         * @param path Request path, including leading slash and any URL parameters but not including the hostname (e.g. /account)
         * @param post (POST only) Request body (JSON-encoded)
         * @return the sign
         */
        std::string generate_sign(long timestamp, std::string method, std::string path, std::string post);
    } // namespace ftx
} // namespace ayanami

#endif
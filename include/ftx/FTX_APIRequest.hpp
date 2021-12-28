#ifndef FTX_APIREQUESTS_HPP
#define FTX_APIREQUESTS_HPP

#include <string>

namespace ayanami {
    namespace ftx {

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
        std::string generate_order_req(std::string market, std::string side, double price, std::string type, double size, bool reduce_only, bool post_only);
    } // namespace ftx
} // namespace ayanami

#endif
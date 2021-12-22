#ifndef MESSAGEPARSING_HPP
#define MESSAGEPARSING_HPP

#include "TradeSeries.hpp"

#include <string>

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace ayanami {

    /**
     * @brief Exchange connections and data handling
     * 
     */
    namespace connections {

        /**
         * @brief The exctracted relevant data from a websocket message
         * 
         */
        struct TradeMessage {
            long time;
            double price;
            double qty;
        };

        /**
         * @brief Parse a trade message from an ftx websocket connection
         * 
         * @param msg the message
         * @return the trade data 
         */
        TradeMessage parse_FTX_trade_msg(std::string msg);
        
    } // namespace connections
} // namespace ayanami

#endif
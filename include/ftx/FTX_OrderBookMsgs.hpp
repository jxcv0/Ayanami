#ifndef FTX_LIMITORDERBOOK_HPP
#define FTX_LIMITORDERBOOK_HPP

#include <cpprest/json.h>
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
         * @brief Populate an orderbook with a "partial" JSON message
         * 
         * @param orderbook the orderbook to populate
         * @param data the "data" field of the JSON message
         */
        void populate_orderbook(std::map<double, double>& orderbook, web::json::value data);

        /**
         * @brief Update and orderbook with an "update" JSON message
         * 
         * @param orderbook the orderbook to update
         * @param data the "data" field of the JSON message
         */
        void update_orderbook(std::map<double, double>& orderbook, web::json::value data);
    } // namespace ftx
} // namespace ayanami

#endif
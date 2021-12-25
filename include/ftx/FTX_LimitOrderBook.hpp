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
         * @brief Populate an orderbook with a "partial" JSON response
         * 
         * @param orderbook the orderbook to populate
         * @param json the JSON
         */
        void populate(std::map<double, double> orderbook, web::json::value json);
    } // namespace ftx
} // namespace ayanami

#endif
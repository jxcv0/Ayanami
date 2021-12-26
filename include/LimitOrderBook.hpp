#ifndef LIMITORDERBOOK_HPP
#define LIMITORDERBOOK_HPP

#include <map>

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace ayanami {

    /**
     * @brief limit order book functions
     * 
     */
    namespace lobs {

        /**
         * @brief Get the best bid from an orderbook
         * 
         * @param orderbook the orderbook
         * @return the best buying price
         */
        double best_bid(std::map<double, double>& orderbook);

        /**
         * @brief Get the best ask from an orderbook
         * 
         * @param orderbook the orderbook
         * @return the best asking price
         */
        double best_ask(std::map<double, double>& orderbook);

        /**
         * @brief Get the midprice of an orderbook
         * 
         * @param orderbook the orderbook
         * @return the midprice
         */
        double mid_price(std::map<double, double>& orderbook);
    } // namespace lobs
} // namespace ayanami

#endif
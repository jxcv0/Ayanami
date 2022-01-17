#ifndef LIMITORDERBOOK_HPP
#define LIMITORDERBOOK_HPP

#include <map>

namespace Ayanami {

    /**
     * @brief limit order book logic module
     * 
     */
    namespace LOB {

        /**
         * @brief Update an orderbook with data from an orderbook message
         * 
         * @param orderbook the orderbook to update
         * @param update the map of updates
         */
        void update_orderbook(std::map<double, double> &orderbook,
            const std::map<double, double> &update);

        /**
         * @brief Get the best bid from an orderbook
         * 
         * @param orderbook the orderbook
         * @return the best buying price
         */
        double best_bid(std::map<double, double> &orderbook);

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
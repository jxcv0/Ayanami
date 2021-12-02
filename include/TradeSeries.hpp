#ifndef TRADESERIES_HPP
#define TRADESERIES_HPP

#include <vector>
#include "Trade.hpp"

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace Ayanami {

    /**
     * @brief Represents a time series of trades.
     * 
     */
    class TradeSeries {

        private:

            /**
             * The Trades contained within this time series.
             * 
             */
            std::vector<Trade> series;

            /**
             * The maximum size of the series.
             * 
             */
            int _maxSize;

            /**
             * @brief Private member funtion that manages the number of Trades within the series
             * 
             */
            void trim();
        
        public:

            /**
             * @brief Construct a new Trade Series object
             * 
             */
            TradeSeries();

            /**
             * @brief Construct a new Trade Series object with a maximum size.
             * Adding new Trades to this object will push out out ones if size > maxSize;
             * 
             * @param maxSize 
             */
            TradeSeries(const int& maxSize);

            /**
             * @brief Get the Trades within this object.
             * 
             * @return the Trades.
             */
            std::vector<Trade> getTrades();

            /**
             * @brief Add a Trade to the series.
             * 
             * @param trade the trade.
             */
            void addTrade(const Trade& trade);

            /**
             * @brief Instatiate and add a Trade to the series.
             * 
             * @param t The unix time
             * @param p The price
             * @param q The quantity
             * @param sym The trades symbol
             */
            void addTrade(const int& t, const double& p, const double& q, const std::string& sym);
    };
}

#endif 
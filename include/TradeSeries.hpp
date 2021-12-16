#ifndef TRADESERIES_HPP
#define TRADESERIES_HPP

#include <map>

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace Ayanami {

    namespace TradeSeries {

        /**
         * @brief Represents a trade with price and quantity
         * 
         */
        struct Trade {

            /**
             * @brief Construct a new Trade object
             * 
             * @param price the price
             * @param qty the signed trade volume
             */
            Trade(const double& price, const double& qty);

            double price;

            double qty;
        }; 

        /**
         * @brief Represents a time series of trades.
         * 
         */
        class Series {

            private:

                std::map<long, Trade> series;

                int _maxSize;
            
            public:

                /**
                 * @brief Construct a new Series object with a maximum size.
                 * 
                 * @param lag the maximum lookback period in seconds
                 */
                Series(const int& maxSize);

                /**
                 * @brief Get the size of the series
                 * 
                 * @return the size
                 */
                int size();

                /**
                 * @brief Add a trade to the series
                 * 
                 * @param time the time of the trade (unix)
                 * @param price the executed price of the trade
                 * @param qty the signed volume of the trade
                 */
                void add_trade(const long& time, const double& price, const double& qty);

                /**
                 * @brief Manages the size of the series
                 * 
                 */
                void trim();
        };
    } // TradeSeries
} // Ayanami

#endif 
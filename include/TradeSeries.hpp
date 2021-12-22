#ifndef TRADESERIES_HPP
#define TRADESERIES_HPP

#include <map>

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace ayanami {

    /**
     * @brief Represents a time series of trades.
     * 
     */
    class Series {

        std::map<long, std::pair<double, double>> series_;

        int maxSize_;

        /**
         * @brief Manages the size of the series
         * 
         */
        void trim();
        
    public:

        /**
         * @brief Construct a new Series object with a maximum size.
         * 
         * @param lag the maximum lookback period in seconds
         */
        Series(int maxSize);

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
        void add_trade(long time, double price, double qty);
    };
} // Ayanami

#endif 
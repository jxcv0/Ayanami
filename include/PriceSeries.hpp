#ifndef PRICESERIES_HPP
#define PRICESERIES_HPP

#include <vector>

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace ayanami {

    /**
     * @brief Chache and operate on a series of price data
     * 
     */
    class PriceSeries {

        const int max_size_;

        std::vector<double> series_;

        /**
         * @brief Trim values exceeding the maximum series size
         * 
         */
        void trim();

    public:

        /**
         * @brief Construct a new Price Series object
         * 
         * @param max the lag period of the series
         */
        PriceSeries(int max);

        /**
         * @brief Add a price to the series
         * 
         * @param price the new price
         */
        void add_price(double price);

        /**
         * @brief Get the series size
         * 
         * @return the size
         */
        int size();

        /**
         * @brief Caculate the mean of the series
         * 
         * @return the mean 
         */
        double mean();

        /**
         * @brief Calculate the standard devition of the price series
         * 
         * @return Tthehe standard deviation
         */
        double std_dev();
    };    
} // namespace ayanami

#endif
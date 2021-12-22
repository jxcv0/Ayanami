#ifndef TIMESERIES_HPP
#define TIMESERIES_HPP

#include <map>

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace ayanami {

    /**
     * @brief Time series analysis tools
     * 
     */
    namespace timeseries {

        /**
         * @brief A time series Candle
         * 
         */
        struct Candle {
            double open;
            double high;
            double low;
            double close;
            double vol;
            Candle(double o, double h, double l, double c,double v);
        };

        /**
         * @brief A price time series
         * 
         */
        class TimeSeries {

            /**
             * @brief The time series data is represented by a time and a Candle
             * 
             */
            std::map<long, Candle> series_;

            int maxSize_;

            /**
             * @brief Manages the size of the series
             * 
             */
            void trim();

        public:

            /**
             * @brief Construct a new Time Series object
             * 
             */
            TimeSeries(int maxSize);

            /**
             * @brief Insert or replace a Candle
             * 
             * @param t 
             * @param o 
             * @param h 
             * @param l 
             * @param c 
             * @param v 
             */
            void add_candle(long t, double o, double h, double l, double c,double v);

            /**
             * @brief Get the latest candle before time t
             * 
             * @param t the time
             */
            void at(long t);

            /**
             * @brief Get the size of the series
             * 
             * @return int 
             */
            int size();
        };
        
    } // namespace timeseries
} // namespace ayanami

#endif
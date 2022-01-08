#ifndef AV_STATE_HPP
#define AV_STATE_HPP

#include <map>
#include <functional>

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace ayanami {

    /**
     * @brief Market making auto-trader based on the 2008 paper by M. Avellaneda and S. Stoikov.
     * This immplimentation of the strategy maintains an orderbook with "buffered" orders to 
     * ensure better placement within orderbook queues.
     * 
     * https://www.math.nyu.edu/~avellane/HighFrequencyTrading.pdf
     */
    namespace av {

        /**
         * @brief State data required to calulate reservation price and optimal bid/ask spread
         * 
         */
        struct av_in {
            double mid;         // Current market midprice
            double inv;        // Current inventory value
            double risk;        // Risk aversion parameter
            double vol;     // volatility parameter
            double liq;         // liquidity parameter
            double time;        // time parameter (T-t)
            av_in(double r, double l, double i); 
        };

        /**
         * @brief State data required to calculate optimal bid and ask prices 
         * 
         */
        struct av_out {
            double res;         // Reservation price
            double spread;      // Spread
        };
        
        /**
         * @brief Calculate the reservation price
         * 
         * @param in state in
         * @param out state out
         */
        void res_price(const av_in& in, av_out& out);

        /**
         * @brief Calculate the spread
         * 
         * @param in state in
         * @param out state out
         */
        void spread(const av_in& in, av_out& out);

        /**
         * @brief Initialize bid quotes and store the values in a vector 
         * 
         * @param in the strategy state
         * @param bids the bids
         * @param interval interval between orders
         * @param buffer the number of ticks away from optimal to buffer orders
         */
        void generate_bids(const av_out& out, std::map<double, int>& bids, double interval, int buffer);

        /**
         * @brief Initialize bid quotes
         * 
         * @param in the strategy state
         * @param asks the asks
         * @param interval interval between orders
         * @param buffer the number of ticks away from optimal to buffer orders
         */
        void generate_asks(const av_out& out, std::map<double, int>& asks, double interval, int buffer);
    } // namespace av
} // namespace ayanami

#endif
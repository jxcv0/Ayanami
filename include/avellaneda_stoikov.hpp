#ifndef AVELLANEDA_STOIKOV_HPP
#define AVELLANEDA_STOIKOV_HPP

#include <map>

namespace Ayanami {

    /**
     * @brief Market making auto-trader based on the 2008 paper by M. Avellaneda and S. Stoikov.
     * This immplimentation of the strategy maintains an orderbook with "buffered" orders to 
     * ensure better placement within orderbook queues.
     * 
     * https://www.math.nyu.edu/~avellane/HighFrequencyTrading.pdf
     */
    namespace AV {

        /**
         * @brief State data required to calulate reservation price and optimal bid/ask spread
         * 
         */
        struct AvIn {
            double mid;         // Current market midprice
            double inv;        // Current inventory value
            double risk;        // Risk aversion parameter
            double vol;     // volatility parameter
            double liq;         // liquidity parameter
            double time;        // time parameter (T-t)
            AvIn(double r, double l, double i); 
        };

        /**
         * @brief State data required to calculate optimal bid and ask prices 
         * 
         */
        struct AvOut{
            double res;         // Reservation price
            double spread;      // Spread
        };
        
        /**
         * @brief Calculate the reservation price
         * 
         * @param in state in
         * @param out state out
         */
        void res_price(const AvIn& in, AvOut& out);

        /**
         * @brief Calculate the spread
         * 
         * @param in state in
         * @param out state out
         */
        void spread(const AvIn& in, AvOut& out);

        /**
         * @brief Initialize bid quotes and store the values in a map 
         * 
         * @param in the strategy state
         * @param bids the bids
         * @param interval interval between orders
         * @param buffer the number of ticks away from optimal to buffer orders
         */
        void generate_bids(const AvOut& out, std::map<double, int>& bids, double interval, int buffer);

        /**
         * @brief Initialize ask quotes and store the values in a map 
         * 
         * @param in the strategy state
         * @param asks the asks
         * @param interval interval between orders
         * @param buffer the number of ticks away from optimal to buffer orders
         */
        void generate_asks(const AvOut& out, std::map<double, int>& asks, double interval, int buffer);
    } // namespace av
} // namespace ayanami

#endif
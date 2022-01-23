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
            double inv;         // Current inventory value
            double risk;        // Risk aversion parameter
            const double vol;   // volatility parameter of constant value
            double liq;         // liquidity parameter
            double time;        // time parameter (T-t)
            
            // these values are required before strategy execution
            AvIn(double r, double l, double i, double v);
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
    } // namespace av
} // namespace ayanami

#endif
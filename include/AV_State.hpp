#ifndef AV_STATE_HPP
#define AV_STATE_HPP

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace ayanami {

    /**
     * @brief Market making auto-trader based on the 2008 paper by M. Avellaneda and S. Stoikov
     * 
     * https://www.math.nyu.edu/~avellane/HighFrequencyTrading.pdf
     */
    namespace av {

        /**
         * @brief calculate the reservation price
         * 
         * @return the reservation price
         */
        
        /**
         * @brief Calculate the reservation price
         * 
         * @param mid the current market mid price
         * @param inv net inventory position
         * @param risk risk parameter
         * @param vol volatility parameter
         * @param time time parameter
         * @return the reservation price 
         */
        double res_price(double mid, int inv, double risk, double vol, double time);

        /**
         * @brief Calculate symetrical spread
         * 
         * @param risk risk aversion param
         * @param vol volatility parameter
         * @param time time parameter
         * @param k liquidity parameter (kappa)
         * @return the symetrical spread around the reservation price
         */
        double spread(double risk, double vol, double time, double k);
    } // namespace av
} // namespace ayanami

#endif
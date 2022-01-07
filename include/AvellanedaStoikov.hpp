#ifndef AV_STATE_HPP
#define AV_STATE_HPP

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace ayanami {

    /**
     * @brief Market making auto-trader based on the 2008 paper by M. Avellaneda and S. Stoikov.
     * This immplimentation of the strategy maintains an orderbook with "buffered" orders to 
     * ensure better placement within orderbook queues
     * https://www.math.nyu.edu/~avellane/HighFrequencyTrading.pdf
     */
    namespace av {

        /**
         * @brief State data in for strategy calculations
         * 
         */
        struct AV_in {
            double mid;         // Current market midprice
            int inv;            // Current inventory value
            double risk;        // Risk aversion parameter
            double vol = 0;     // volatility parameter
            double time;        // time parameter (T-t)
            double bid;         // Latest strategy bid quote
            double ask;         // Latest strategy ask quote
            double tick;        // Instrument tick size
        };

        /**
         * @brief Generic order datatype
         * 
         */
        struct Order {
            double price;       // Order price
            double size;        // Order size
            int id;             // some kind of id (exchange dependant)
        };
        
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
        double res_price(AV_in in, double mid, int inv, double risk, double vol, double time);

        /**
         * @brief Calculate symetrical spread
         * 
         * @param risk risk aversion param
         * @param vol volatility parameter
         * @param time time parameter
         * @param k liquidity parameter (kappa)
         * @return the symetrical spread around the reservation price
         */
        double spread(AV_in in, double risk, double vol, double time, double k);

        /**
         * @brief Initialize bids quotes and store the values in a vector 
         * 
         * @param in the strategy state
         * @param bids the bids
         * @param place the function used to place an order
         */
        void init_bids(AV_in in, std::vector<Order>& bids, std::function<void(const Order&)> place);

        /**
         * @brief Check and modify orders if required by moving them to the back of the queue
         * 
         * NOTE: This function does not modify the vector of orders. After init, that is the
         * responsibility of the websocket JSON proccessing function which is API specific.
         * 
         * @param in the strategy state
         * @param bids the bids
         * @param modify_orders the function used to modify an order
         */
        void modify_bids(AV_in in, std::vector<Order>& bids, std::function<void(const Order&)> modify);

        /**
         * @brief Initialize bids quotes
         * 
         * @param in the strategy state
         * @param asks the asks
         * @param place the function used to place an order
         */
        void init_asks(AV_in in, std::vector<Order>& asks, std::function<void(const Order&)> place);

        /**
         * @brief Check and modify orders if required by moving them to the back of the queue
         * 
         * NOTE: This function does not modify the vector of orders. After init, that is the
         * responsibility of the websocket JSON proccessing function which is API specific.
         * 
         * @param in the strategy state
         * @param asks the asks
         * @param modify_orders the function used to modify an order
         */
        void modify_asks(AV_in in, std::vector<Order>& asks, std::function<void(const Order&)> modify);
    } // namespace av
} // namespace ayanami

#endif
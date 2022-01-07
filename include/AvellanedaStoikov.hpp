#ifndef AV_STATE_HPP
#define AV_STATE_HPP

#include <vector>
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
        struct AV_in {
            double mid;         // Current market midprice
            int inv;            // Current inventory value
            double risk;        // Risk aversion parameter
            double vol = 0;     // volatility parameter
            double liq;         // liquidity parameter
            double time;        // time parameter (T-t)
            double bid;         // Latest strategy bid quote
            double ask;         // Latest strategy ask quote
        };

        /**
         * @brief State data required to calculate optimal bid and ask prices 
         * 
         */
        struct AV_out {
            double res;         // Reservation price
            double spread;      // Spread 
        };

        /**
         * @brief Generic order datatype
         * 
         */
        struct Order {
            double price;       // Order price
            double size;        // Order size
            int id;             // some kind of id (exchange dependant)
            double tick;        // instrument tick size;
            Order(double t);
        };
        
        /**
         * @brief Calculate the reservation price
         * 
         * @param in state in
         * @param out state out
         */
        void res_price(const AV_in& in, AV_out& out);

        /**
         * @brief Calculate the spread
         * 
         * @param in state in
         * @param out state out
         */
        void spread(const AV_in& in, AV_out& out);

        /**
         * @brief Initialize bid quotes and store the values in a vector 
         * 
         * @param in the strategy state
         * @param bids the bids
         * @param place the function used to place an order
         */
        void init_bids(const AV_out& out, std::vector<Order>& bids, std::function<void(const Order&)> place);

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
        void modify_bids(const AV_out& out, std::vector<Order>& bids, std::function<void(const Order&)> modify);

        /**
         * @brief Initialize bid quotes
         * 
         * @param in the strategy state
         * @param asks the asks
         * @param place the function used to place an order
         */
        void init_asks(const AV_out& out, std::vector<Order>& asks, std::function<void(const Order&)> place);

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
        void modify_asks(const AV_out& out, std::vector<Order>& asks, std::function<void(const Order&)> modify);
    } // namespace av
} // namespace ayanami

#endif
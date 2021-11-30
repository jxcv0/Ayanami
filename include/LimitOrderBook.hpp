#ifndef LIMITORDERBOOK_HPP
#define LIMITORDERBOOK_HPP

#include <map>

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace Ayanami {

    /**
     * @brief Represents an exchange orderbook
     * 
     */
    class LimitOrderBook {
        private:
            /**
             * @brief A map containing the values of the orderbook.
             * Used to get the total volume of orders at price levels.
             * Bids are represented by positive vales, asks by negative values.
             * 
             */
            std::map<double, double> values;

            /**
             * @brief A flag indicating if the orderbook has been populated and is ready to
             * run computations.
             * 
             */
            bool populated;
        
        public:

            /**
             * @brief Construct a new Limit Order Book object
             * Populated flag defaults to false;
             * 
             */
            LimitOrderBook();

            /**
             * @brief Construct a new Limit Order Book object from a map.
             * 
             */
            LimitOrderBook(std::map<double, double>& map);

            /**
             * @brief Insert a signed value at a price into the orderbook.
             * If the value is 0 then the entry is removed from the orderbook.
             * 
             * @param price the price.
             * @param size the size.
             */
            void insert(const double& price, const double& size);

            /**
             * @brief Remove an entry from the orderbook.
             * 
             * @param price the price of the entry to remove.
             */
            void remove(const double& price);

            /**
             * @brief Get signed volume of all orders at a price.
             * 
             * @param price the price level.
             * @return the order volume. 
             */
            double atPrice(const double& price);

            /**
             * @brief Set the populated flag.
             * 
             * @param flag the flag
             */
            void setPopulated(bool flag);

            /**
             * @brief Get the lowest asking price from the orderbook
             * 
             * @return the lowest asking price
             */
            double bestAsk();

            /**
             * @brief Get the highes bidding price from the orderbook.
             * 
             * @return double 
             */
            double bestBid();

            /**
             * @brief Calculate the total (unsigned) volume of the orderbook.
             * 
             * @return the total volume in the orderbook.
             */
            double depth();

            /**
             * @brief Calculate the (unsigned) volume of the orderbook within a price
             * range of the best bid and ask prices.
             * 
             * @param range the price range.
             */
            double depth(const double& range);
            
            /**
             * @brief Get the all asks from the orderbook.
             * Returns all orders with size < 0;
             * 
             * @return the asks.
             */
            std::map<double, double> getAsks();

            /**
             * @brief Get the all bids from the orderbook.
             * Returns all orders with size > 0;
             * 
             * @return the bids.
             */
            std::map<double, double> getBids();

            /**
             * @brief Calculate the order imbalance of the orderbooks.
             * The signed sum of all orders.
             * 
             * @return the order imbalalance. 
             */
            double delta();

            /**
             * @brief Calculate the order imbalance of the orderbook within a price
             * range of the best bid and ask prices.
             * 
             * @param range the price range.
             * @return the order imbalance.
             */
            double delta(const double& range);
    };
}

#endif
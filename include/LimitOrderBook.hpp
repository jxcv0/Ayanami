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
             * @brief Insert a signed value at a price into the orderbook.
             * If the value is 0 then the entry is removed from the orderbook.
             * 
             * @param price the price to insert at.
             * @param size the value to enter.
             */
            void insert(const double &price, const double &size);

            /**
             * @brief Remove an entry from the orderbook.
             * 
             * @param price the price of the entry to remove.
             */
            void remove(const double &price);

            /**
             * @brief Get signed volume of all orders at a price.
             * 
             * @param price the price level.
             * @return the order volume. 
             */
            double atPrice(const double &price);

            /**
             * @brief Set the populated flag.
             * 
             * @param flag the flag
             */
            void setPopulated(bool flag);

            /**
             * @brief Calculate the total (unsigned) volume of the orderbook.
             * 
             * @return the total volume in the orderbook.
             */
            double depth();

            /**
             * @brief Calculate the (unsigned) volume of the orderbook within a percentage
             * range of the best bid and ask prices.
             * 
             * @param range the percentage range to include.
             */
            double depth(const double &range);
    };
}

#endif
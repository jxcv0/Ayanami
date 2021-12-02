#ifndef TRADE_HPP
#define TRADE_HPP

#include <iostream>

namespace Ayanami {
    // Represents a trade event
   class Trade {

        private:

            /**
             * The unix at which the trade occured
             */
            int _time;

            /**
             * the price at which the trade occured
             */
            double _price;

            /**
             * The signed trade volume
             * sell orders have a negative sign
             */
            double _qty;

            /**
             * The traded symbol/pair, i.e, "BTCUSD"
             */
            std::string _symbol;
            
        public:

            /**
             * @brief Construct a new Trade object
             * 
             * @param time the unix time
             * @param price the price
             * @param qty the quantity
             * @param symbol the trade symbol
             */
            Trade(const int& time, const double& price, const double& qty, const std::string& symbol);

            /**
             * @brief Get the time
             * 
             * @return The unix time as int
             */
            int getTime();

            /**
             * @brief Get the price
             * 
             * @return The price as double
             */
            double getPrice();

            /**
             * @brief Get the quantity
             * 
             * @return The quantity as double
             */
            double getQty();

            /**
             * @brief Get the Symbol
             * 
             * @return The symbol as string
             */
            std::string getSymbol();
    };
}

#endif
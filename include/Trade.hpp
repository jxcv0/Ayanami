#ifndef TRADE_HPP
#define TRADE_HPP

#include <iostream>

using namespace std;

namespace Ayanami {
    // Represents a trade event
   class Trade {

        private:

            /**
             * The unix at which the trade occured
             */
            int time;

            /**
             * the price at which the trade occured
             */
            double price;

            /**
             * The signed trade volume
             * sell orders have a negative sign
             */
            double qty;

            /**
             * The traded symbol/pair, i.e, "BTCUSD"
             */
            string symbol;
            
        public:

            /**
             * @brief Construct a new Trade object
             * 
             * @param t The unix time
             * @param p The price
             * @param q The quantity
             * @param sym The trades symbol
             */
            Trade(int t, double p, double q, string sym);

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
            string getSymbol();
    };
}

#endif
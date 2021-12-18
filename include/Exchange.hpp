#ifndef LIMITORDERBOOK_HPP
#define LIMITORDERBOOK_HPP

#include <map>

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace Ayanami {

    /**
     * @brief Connections to and data from exchanges
     * 
     */
    namespace Exchange {

        /**
         * @brief Represents an exchange
         * 
         */
        class Exchange {

            /**
             * Orderbooks of all connected markets on exchange
             * 
             */
            std::map<std::string, std::map<double, double>> limitOrderBooks;
            
        public:
            /**
             * @brief Connect to all symbols on bybit exchange via websocket
             * 
             */
            void connect_to_ws();

        };
    }
}

#endif
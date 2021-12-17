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
    class Exchange {
        
        /**
         * @brief The symbol enums of the Bybit API
         * 
         */
        enum class BybitSymbol {
            BTCUSD,
            ETHUSD,
            EOSUSD,
            XRPUSD,
            DOTUSD
        };

        private:

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

#endif
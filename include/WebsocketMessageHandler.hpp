#ifndef WEBSOCKET_HANDLER_HPP
#define WEBSOCKET_HANDLER_HPP

#include <iostream>

using namespace std;

namespace Ayanami {

    /**
     * @brief Interface for classes that handle JSON responses from exchanges
     * 
     */
    class WebsocketMessageHandler {
        private:
            /* data */
        public:
            
            /**
             * @brief Map a json message from a JSON trade message to a Trade object
             * 
             * @param msg the JSON message as a string
             */
            virtual void handleTradeMessage(string msg);

            // TODO - more handler functions will be defined after other classes, i.e, Liquidation, Orderbook
    };
}

#endif
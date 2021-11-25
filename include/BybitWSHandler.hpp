#ifndef BYBITWSHANDLER_HPP
#define BYBITWSHANDLER_HPP

#include <iostream>
#include "Trade.hpp"

using namespace std;

namespace Ayanami
{
    /**
     * @brief Responsible for parsing websocket messages into an appropriate object.
     * Each subscription topic to the websocket has one or more functions dedicated to parsing it.
     * 
     */
    class BybitWSHander {
        public:

            /**
             * @brief Parse messages related to matched trade events.
             * 
             * @param message the JSON message from the websocket
             * @return <code>Trade</code> containing the parsed information
             */
            Trade parseTradeMessage(string message);

    };
}

#endif
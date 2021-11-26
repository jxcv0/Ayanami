#ifndef BYBITWEBSOCKET_HPP
#define BYBITWEBSOCKET_HPP

#include "Websocket.hpp"
#include <iostream>

namespace Ayanami {
    class BybitWebsocket : websocket_callback_client {
        public:
            BybitWebsocket();
    };
}

#endif
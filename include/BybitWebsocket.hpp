#ifndef BYBITWEBSOCKET_HPP
#define BYBITWEBSOCKET_HPP

#include "Websocket.hpp"
#include <iostream>

class BybitWebsocket : Ayanami::Websocket {
    public:
        BybitWebsocket(std::string key, std::string secret);
};

#endif
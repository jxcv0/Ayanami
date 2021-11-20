#ifndef WEBSOCKET_HPP
#define WEBSOCKET_HPP

#include <thread>
#include <cpprest/ws_client.h>

using namespace std;

/**
 * @brief Represents a connection to a single Exchange websocket
 * each Websocket object may represent many subscriptions to a single exchange
 * 
 */
class Websocket: public std::thread {
    private:
        /* data */
    public:
        Websocket(/* args */);
};

#endif
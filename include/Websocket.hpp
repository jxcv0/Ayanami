#ifndef WEBSOCKET_HPP
#define WEBSOCKET_HPP

#include <cpprest/ws_client.h>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace std;
// using namespace web;
using namespace web::websockets::client;

namespace Ayanami{  

    /**
     * @brief An abstract class that represents an Exchange API
     * 
     */
    class Websocket {

        protected:

            // the account api key
            string key;

            // The account api secret
            string secret;

            // The base endpoint of the websocket
            string wsEndpoint;

            // The websocket client
            websocket_callback_client wsClient;

            // The number of milliseconds until rate limit is reset
            int rateLimitResetms;

        public:

            /**
             * @brief Construct a new Websocket object
             * 
             * @param key api key
             * @param secret api secret
             * @param wsEndpoint The base url of the endpoint 
             */
            Websocket(string key, string secret, string wsEndpoint);

            /**
             * @brief Destroy the Websocket object
             * 
             */
            ~Websocket();

            /**
             * @brief Subscribe to a topic
             * 
             * @param topics The topic
             */
            void subscribeToTopic(string topics);
    };
}

#endif
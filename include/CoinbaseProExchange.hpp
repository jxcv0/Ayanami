#ifndef COINBASEPROEXCHANGE_HPP
#define COINBASEPROEXCHANGE_HPP

#include <iostream>
#include <vector>
#include <cpprest/json.h>
#include <cpprest/ws_client.h>

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace Ayanami {

    /**
     * @brief Represents the Coinbase Pro Websocket API.
     * Responsible for creating and managing subscriptions and for parsing response messages.
     * 
     */
    class CoinbaseProExchange {
        private:

            /**
             * @brief The websocket client.
             * 
             */
            web::websockets::client::websocket_callback_client client;

            /**
             * @brief Stores user API key.
             * 
             */
            std::string apiKey;

            /**
             * @brief Stores user API secret.
             * 
             */
            std::string apiSecret;
            
        public:
            /**
             * @brief Construct a new Coinbase Websocket object
             * 
             */
         CoinbaseProExchange();

            /**
             * @brief Supply API keys for connection authentification.
             * These are supplied by the exchange and are required for subscribing to private 
             * channels.
             * 
             * @param key the user API key.
             * @param secret the user API secret.
             */
            void setAPIKeys(std::string key, std::string secret);

            /**
             * @brief Connect to Websocket
             *  TODO
             */
            void connectToWebsocket();

            /**
             * @brief Generate a JSON subscription message.
             * Each product id will have every declared subscription generated for it.
             * 
             * @param productIds a vector containing the trading pairs, such as "BTC-USD". 
             * @param channels a vector containing the subscription channels.
             * @return the JSON subscription message.
             */
            web::json::value generateSubscriptionMessage(
                std::vector<std::string> &productIds, std::vector<std::string> &channels);
    };
}

#endif
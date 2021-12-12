#ifndef CBPROWEBSOCKET_HPP
#define CBPROWEBSOCKET_HPP

#include <cpprest/ws_client.h>
#include "LimitOrderBook.hpp"
#include "TradeSeries.hpp"

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace Ayanami {

    /**
     * @brief Parses level2 messages fron CP Pro websocket
     * 
     */
    class CBProWebsocket {
        private:

            std::string baseURI;

            // TODO
            std::vector<LimitOrderBook> lobs;

            std::vector<TradeSeries::Series> series;

            web::websockets::client::websocket_callback_client client;

        public:

            /**
             * @brief Construct a new CBProWebsocket object
             * 
             */
            CBProWebsocket();

            /**
             * @brief Connect to Coinbase Websocket
             * 
             */
            void connect();

            /**
             * @brief Create a subscription message
             * 
             */
            std::string createSubscribeMsg(const std::string& productId, const std::string& channel);

            /**
             * @brief Subscribe to an orderbook channel
             * 
             * @param productId the product_id
             */
            Ayanami::LimitOrderBook addLOB(const std::string& productId);

            /**
             * @brief Parse a snapshot message and use it to update a LOB
             * 
             * @param msg the message to proccess
             */
            void proccessSnapshotMsg(web::websockets::client::websocket_incoming_message msg);
            
    };
} // namespace Ayanami

#endif
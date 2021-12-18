#ifndef BYBITWS_HPP
#define BYBITWS_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/websocket.hpp>

#include <memory>

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

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
         * @brief The bybit websocket
         * https://www.boost.org/doc/libs/develop/libs/beast/example/websocket/client/async/websocket_client_async.cpp
         */
        class BybitWS : public std::enable_shared_from_this<BybitWS> {
            tcp::resolver resolver_;
            websocket::stream<beast::tcp_stream> ws_;
            beast::flat_buffer buffer_;

        public:

            /**
             * @brief Construct a new BybitWS object
             * 
             * @param ioc resolver and socket require an io_context
             */
            explicit BybitWS(net::io_context& ioc);

            /**
             * @brief Find domain name and start async operation
             * 
             */
            void run();

            /**
             * @brief 
             * 
             * @param ec the boost/beast error code
             * @param results the endpoints
             */
            void on_resolve(beast::error_code ec, tcp::resolver::results_type results);
        };
    } // namespace Exchange
} // namespace Ayanami

#endif
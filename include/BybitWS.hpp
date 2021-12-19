#ifndef BYBITWS_HPP
#define BYBITWS_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>

#include <memory>

namespace beast = boost::beast;         
namespace http = beast::http;           
namespace websocket = beast::websocket; 
namespace net = boost::asio;            
namespace ssl = boost::asio::ssl;       
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
            websocket::stream<beast::ssl_stream<beast::tcp_stream>> ws_;
            beast::flat_buffer buffer_;
            std::string host_;

        public:

            /**
             * @brief Construct a new BybitWS object
             * 
             * @param ioc resolver and socket require an io_context
             */
            explicit BybitWS(net::io_context& ioc, ssl::context& ctx);

            /**
             * @brief start async operation
             * 
             */
            void run();

            /**
             * @brief Actions on resolve
             * 
             * @param ec boost/beast error code
             * @param results results of on_resolve
             */
            void on_resolve(beast::error_code ec, tcp::resolver::results_type results);

            /**
             * @brief Actions on connect
             * 
             * @param ec boost/beast error code
             * @param ep endpoints
             */
            void on_connect(beast::error_code ec, tcp::resolver::endpoint_type ep);

            /**
             * @brief Actions on ssl handshake
             * 
             * @param ec boost/beast error code
             */
            void on_ssl_handshake(beast::error_code ec);

            /**
             * @brief Actions on handshake
             * 
             * @param ec boost/beast error code
             */
            void on_handshake(beast::error_code ec);

            /**
             * @brief Actions on write
             * 
             * @param ec boost/beast error code
             * @param bytes_transferred bytes transferred
             */
            void on_write(beast::error_code ec, std::size_t bytes_transferred);

            /**
             * @brief Actions on read
             * 
             * @param ec boost/beast error code
             * @param bytes_transferred bytes transferred
             */
            void on_read(beast::error_code ec, std::size_t bytes_transferred);

            /**
             * @brief Acions on close
             * 
             * @param ec boost/beast error code
             */
            void on_close(beast::error_code ec);
        };
    } // namespace Exchange
} // namespace Ayanami

#endif
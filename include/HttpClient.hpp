#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <cstdlib>
#include <iostream>
#include <memory>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;
using tcp = boost::asio::ip::tcp;
     

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace ayanami {

    /**
     * @brief Exchange connections and data handling
     * 
     */
    namespace connections {

        /**
         * @brief Report an error
         * 
         * @param ec beast error code
         * @param what a helpful string
         */
        void fail(beast::error_code ec, char const* what);

        /**
         * @brief An HTTP client for placing orders 
         * 
         */
        class HttpClient : public std::enable_shared_from_this<HttpClient> {

            tcp::resolver resolver_;
            beast::ssl_stream<beast::tcp_stream> stream_;
            beast::flat_buffer buffer_;
            http::request<http::string_body> req_; // string body?
            http::response<http::string_body> res_;

        public:

            /**
             * @brief Construct a new Http Client object
             * 
             * @param ex io executor
             * @param ctx ssl context
             */
            explicit HttpClient(net::any_io_executor ex, ssl::context& ctx);

            /**
             * @brief Start asynchronous operation
             * 
             * @param host the host
             * @param port the port
             * @param target the target
             * @param version the message version
             */
            void run(char const* host, char const* port, char const* target);

            /**
             * @brief On resolve
             * 
             * @param ec beast error code
             * @param results resolver results
             */
            void on_resolve(beast::error_code ec, tcp::resolver::results_type results);
            
            /**
             * @brief On connect
             * 
             * @param ec beast error code
             */
            void on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type);

            /**
             * @brief On handshake
             * 
             * @param ec beast error code
             */
            void on_handshake(beast::error_code ec);

            /**
             * @brief On write
             * 
             * @param ec beast error code
             * @param bytes_transferred bytes transferred 
             */
            void on_write(beast::error_code ec, std::size_t bytes_transferred);

            /**
             * @brief On read
             * 
             * @param ec beast error code
             * @param bytes_transferred bytes transferred
             */
            void on_read(beast::error_code ec, std::size_t bytes_transferred);

            /**
             * @brief On shutdown
             * 
             * @param ec beast error code
             */
            void on_shutdown(beast::error_code ec);
        };
    } // namespace connections
} // namespace ayanami
#endif
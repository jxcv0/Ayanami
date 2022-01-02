#ifndef WebsocketSESSION_HPP
#define WebsocketSESSION_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>

#include <memory>
#include <functional>
#include <string>

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
namespace ayanami {

    /**
     * @brief Exchange connections and data handling
     * 
     */
    namespace connections {

        /**
         * @brief A websocket
         * 
         */
        class Websocket : public std::enable_shared_from_this<Websocket> {
            tcp::resolver resolver_;
            websocket::stream<beast::ssl_stream<beast::tcp_stream>> ws_;
            beast::flat_buffer buffer_;
            std::string host_;
            std::string text_;
            std::string path_;
            std::function<void(std::string)> on_msg_;
            bool close_;

        public:

            // TODO handle_error()

            /**
             * @brief Construct a new Websocket object
             * 
             * @param ioc resolver and socket require an io_context
             */
            explicit Websocket(net::io_context& ioc, ssl::context& ctx);

            /**
             * @brief Start operation
             * 
             * @param host the websocket host
             * @param path the uri path
             * @param text the message to send upon successful connection
             * @param on_msg the message handling function
             */
            void run(char const* host, char const* path, char const* text, std::function<void(std::string)> on_msg);

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

            /**
             * @brief Send a message via the websocket
             * 
             *  TODO
             * 
             * @param msg 
             */
            void send(std::string msg);

            /**
             * @brief Close the connection
             * 
             */
            void close();
        };
    } // namespace exchange
} // namespace ayanami

#endif
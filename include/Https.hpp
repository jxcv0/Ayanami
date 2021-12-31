#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <functional>

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
     * @brief Connection managment for FTX exchange
     * 
     */
    namespace connections {

        /**
         * @brief send a request to an FTX api endpoint
         * 
         * @param req the request
         */
        void send_req(http::request<http::string_body> req,
            std::function<void(http::response<http::dynamic_body>)> func);
    } // namespace connections
} // namespace ayanami
#endif
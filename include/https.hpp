#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;
using tcp = boost::asio::ip::tcp;
     

namespace Ayanami {

    /**
     * @brief Connection managment for FTX exchange
     * 
     */
    namespace Connections {

        /**
         * @brief send a request to an FTX api endpoint
         * 
         * @param req the request
         * @param res the forward declared response object
         * 
         */
        void send_req(http::request<http::string_body> req,
            http::response<http::dynamic_body>& res);
    } // namespace connections
} // namespace ayanami
#endif
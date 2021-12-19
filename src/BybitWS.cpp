#include "BybitWS.hpp"

#include <boost/asio/strand.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/beast/ssl.hpp>

#include <iostream>
#include <memory>

Ayanami::Exchange::BybitWS::BybitWS(net::io_context& ioc, ssl::context& ctx) 
    : resolver_(net::make_strand(ioc))
    , ws_(net::make_strand(ioc), ctx){};

void Ayanami::Exchange::BybitWS::run() {
    // auto const host = "wss://stream.bybit.com/realtime";
    auto const host = "stream.bybit.com";
    auto const port = "443";
    host_ = host;

    resolver_.async_resolve(
        host,
        port,
        beast::bind_front_handler(&BybitWS::on_resolve, shared_from_this())
    );
};

void Ayanami::Exchange::BybitWS::on_resolve(beast::error_code ec, tcp::resolver::results_type results) {
    if (ec) {
        std::cerr << "On Resolve: " << ec.message() << "\n"; 
    }

    beast::get_lowest_layer(ws_).expires_after(std::chrono::seconds(30));

    beast::get_lowest_layer(ws_).async_connect(
        results,
        beast::bind_front_handler(&BybitWS::on_connect, shared_from_this())
    );
};

void Ayanami::Exchange::BybitWS::on_connect(beast::error_code ec, tcp::resolver::endpoint_type ep) {
    if (ec) {
        std::cerr << "On Connect: " << ec.message() << "\n"; 
    }

    beast::get_lowest_layer(ws_).expires_after(std::chrono::seconds(30));

    if (!SSL_set_tlsext_host_name(ws_.next_layer().native_handle(), host_.c_str())) {
        ec = beast::error_code(
            static_cast<int>(::ERR_get_error()),
            net::error::get_ssl_category()
        );
        std::cerr << "On Connect: " << ec.message() << "\n"; 
    }

    host_ += ':' + std::to_string(ep.port());

    ws_.next_layer().async_handshake(
        ssl::stream_base::client,
        beast::bind_front_handler(&BybitWS::on_ssl_handshake, shared_from_this())
    );
};

void Ayanami::Exchange::BybitWS::on_ssl_handshake(beast::error_code ec) {
    if (ec) {
        std::cerr << "On Handshake: " << ec.message() << "\n"; 
    }

    beast::get_lowest_layer(ws_).expires_never();

    ws_.set_option(websocket::stream_base::timeout::suggested(beast::role_type::client));

    ws_.set_option(
        websocket::stream_base::decorator(
            [](websocket::request_type& req) {
                req.set(http::field::user_agent,
                std::string(BOOST_BEAST_VERSION_STRING) + " websocket-client-async-ssl");
            })
    );

    ws_.async_handshake(host_, "/realtime",
        beast::bind_front_handler(&BybitWS::on_handshake, shared_from_this())
    );
};

void Ayanami::Exchange::BybitWS::on_handshake(beast::error_code ec) {
    if (ec) {
        std::cerr << "On Handshake: " << ec.message() << "\n"; 
    }

    // TODO Subscribe here
    ws_.async_write(
        net::buffer("{\"op\": \"subscribe\", \"args\": [\"trade.BTCUSD\"]}"),
        beast::bind_front_handler(&BybitWS::on_write, shared_from_this())
    );
};

void Ayanami::Exchange::BybitWS::on_write(beast::error_code ec, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (ec) {
        std::cerr << "On Write: " << ec.message() << "\n"; 
    }

    ws_.async_read(
            buffer_,
            beast::bind_front_handler(&BybitWS::on_read, shared_from_this())
    );
};

void Ayanami::Exchange::BybitWS::on_read(beast::error_code ec, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (ec) {
        std::cerr << "On Read: " << ec.message() << "\n"; 
    }

    ws_.async_close(
            websocket::close_code::normal,
            beast::bind_front_handler(&BybitWS::on_close, shared_from_this())
    );
}

void Ayanami::Exchange::BybitWS::on_close(beast::error_code ec) {
    if (ec) {
        std::cerr << "On Close: " << ec.message() << "\n"; 
    }

    // Parse here?
    std::cout << beast::make_printable(buffer_.data()) << std::endl;
};
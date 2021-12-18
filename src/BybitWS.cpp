#include "BybitWS.hpp"

#include <boost/asio/strand.hpp>

#include <iostream>
#include <memory>

Ayanami::Exchange::BybitWS::BybitWS(net::io_context& ioc) 
    : resolver_(net::make_strand(ioc))
    , ws_(net::make_strand(ioc)){}

void Ayanami::Exchange::BybitWS::run() {

    auto handler = [](beast::error_code ec, tcp::resolver::results_type results){
        if (ec) {
            std::cerr << "Connect: " << ec.message() << "\n"; 
        }
    };

    auto const host = "wss://stream.bybit.com/realtime";
    auto const port = 80;

    resolver_.async_resolve(
        host,
        port,
        beast::bind_front_handler(&BybitWS::on_resolve, shared_from_this())
    );
};

void Ayanami::Exchange::BybitWS::on_resolve(beast::error_code ec, tcp::resolver::results_type results) {
    if (ec) {
        std::cerr << "Connect: " << ec.message() << "\n"; 
    }
}
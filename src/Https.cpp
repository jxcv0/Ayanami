#include "Https.hpp"

#include <iostream>

void ayanami::connections::send_req(http::request<http::string_body> req,
    std::function<void(http::response<http::dynamic_body>)> func) {

    try {
        net::io_context ioc;
        ssl::context ctx(ssl::context::tlsv12_client);
        ctx.set_verify_mode(ssl::verify_peer);

        tcp::resolver resolver(ioc);
        beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);

        std::string host = req[http::field::host].to_string();

        if (!SSL_set_tlsext_host_name(stream.native_handle(), host.c_str())) {
            beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
            throw beast::system_error{ec};
        }

        auto const results = resolver.resolve(host, "443", tcp::resolver::numeric_service);
        beast::get_lowest_layer(stream).connect(results);
        stream.handshake(ssl::stream_base::client);
        http::write(stream, req);
        beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(stream, buffer, res);
        func(res);

        beast::error_code ec;
        stream.shutdown(ec);
        if(ec == net::error::eof) {
            ec = {};
        }

        if (ec) {
            throw beast::system_error(ec);
        }
    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
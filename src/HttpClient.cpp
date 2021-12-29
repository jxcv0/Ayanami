#include "HttpClient.hpp"

void ayanami::connections::fail(beast::error_code ec, char const* what) {
    std::cerr << what << ": " << ec.message() << "\n";
}

ayanami::connections::HttpClient::HttpClient(net::any_io_executor ex, ssl::context& ctx)
    : resolver_(ex)
    , stream_(ex, ctx) {}

void ayanami::connections::HttpClient::run(char const* host, char const* port, char const* target) {
    if (!SSL_set_tlsext_host_name(stream_.native_handle(), host)) {
        beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
        std::cerr << ec.message() << "\n";
        return;
    }

    // create request
    req_.method(http::verb::post);
    req_.target(target);
    req_.set(http::field::host, host);
    req_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    resolver_.async_resolve(
        host,
        port,
        beast::bind_front_handler(&HttpClient::on_resolve, shared_from_this())
    );
}

void ayanami::connections::HttpClient::on_resolve(beast::error_code ec, tcp::resolver::results_type results) {
    if (ec) {
        return ayanami::connections::fail(ec, "On resolve");
    }

    beast::get_lowest_layer(stream_).expires_after(std::chrono::seconds(30));

    beast::get_lowest_layer(stream_).async_connect(
        results,
        beast::bind_front_handler(&HttpClient::on_connect, shared_from_this())
    );
}

void ayanami::connections::HttpClient::on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type) {
    if (ec) {
        return fail(ec, "On connect");
    }

    stream_.async_handshake(
        ssl::stream_base::client,
        beast::bind_front_handler(&HttpClient::on_handshake, shared_from_this())
    );
}

void ayanami::connections::HttpClient::on_write(beast::error_code ec, std::size_t bytes_transferred) {
    if (ec) {
        return fail(ec, "On write");
    }

    beast::get_lowest_layer(stream_).expires_after(std::chrono::seconds(30));

    http::async_write(
        stream_,
        req_,
        beast::bind_front_handler(&HttpClient::on_write, shared_from_this())
    );
}

void ayanami::connections::HttpClient::on_read(beast::error_code ec, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (ec) {
        return fail(ec, "On read");
    }

    // TODO - here
    std::cout << res_ << std::endl;

    beast::get_lowest_layer(stream_).expires_after(std::chrono::seconds(30));

    stream_.async_shutdown(
        beast::bind_front_handler(&HttpClient::on_shutdown, shared_from_this())
    );
}

void ayanami::connections::HttpClient::on_shutdown(beast::error_code ec) {
    if (ec == net::error::eof) {
        ec = {};
    }

    if (ec) {
        return fail(ec, "On shutdown");
    }
}
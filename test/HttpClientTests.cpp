#include <gtest/gtest.h>

#include "HttpClient.hpp"

TEST(HttpClientTests, 200_ok_test) {
    net::io_context ioc;
    net::any_io_executor ex;
    ssl::context ctx{ssl::context::tlsv12_client};
    ctx.set_verify_mode(ssl::verify_peer);

    http::request<http::string_body> req;

    http::response<http::string_body> res;

    std::make_shared<ayanami::connections::HttpClient>(net::make_strand(ioc), ctx)
     ->run(req, "666", "api.bybit.com", "/v2/public/time",
        [&](http::response<http::string_body> r){ res = r; });

    std::cout << req << "\n";
    std::cout << res.body().c_str() << "\n";
    // ASSERT_EQ(res.)
}
#include <gtest/gtest.h>

#include "HttpClient.hpp"
#include "Encryption.hpp"
#include "APIKeys.hpp"

#include <boost/asio/buffers_iterator.hpp>

#include <iomanip>

TEST(HttpClientTests, 200_ok_test) {
    net::io_context ioc;
    net::any_io_executor ex;
    ssl::context ctx{ssl::context::tlsv12_client};
    ctx.set_verify_mode(ssl::verify_peer);

    std::string time_now = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    // get account information - requires authentification
    http::request<http::string_body> req;
    req.method(http::verb::get);
    req.target("/api/account");
    req.set(http::field::host, "ftx.com");
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    req.set("FTX-KEY", APIKeys::KEY);
    req.set("FTX-TS", time_now);
    std::string sign = time_now + "GET" + "/account";
    req.set("FTX-SIGN", ayanami::hmac_sha256(APIKeys::SECRET, sign.c_str()));

    std::cout << "Request: " << req << "\n";

    std::make_shared<ayanami::connections::HttpClient>(net::make_strand(ioc), ctx)
        ->run(req, "666", [&](http::response<http::string_body> r){ std::cout << r << "\n"; });
    ioc.run();

    // ASSERT_EQ(res.)
}
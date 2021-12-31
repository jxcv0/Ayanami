#include <gtest/gtest.h>

#include "Https.hpp"
#include "Encryption.hpp"
#include "APIKeys.hpp"

TEST(HttpClientTests, 200_ok_test) {
    

    std::string time_now = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());

    // get account information - requires authentification
    http::request<http::string_body> req;
    req.method(http::verb::get);
    req.target("https://ftx.com/api/account");
    req.set(http::field::host, "ftx.com");
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    req.set("FTX-KEY", APIKeys::KEY);
    req.set("FTX-TS", time_now);
    std::string sign = time_now + "GET" + "/account";
    req.set("FTX-SIGN", ayanami::hmac_sha256(APIKeys::SECRET, sign.c_str()));

    std::cout << "Request: " << req << "\n";

    ayanami::connections::send_req(req, [](http::response<http::dynamic_body> res){
        std::cout << res << "\n";
    });
}
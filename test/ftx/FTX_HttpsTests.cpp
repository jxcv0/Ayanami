#include <gtest/gtest.h>

#include "Https.hpp"
#include "Encryption.hpp"
#include "APIKeys.hpp"

TEST(FTX_Https_tests, 200_ok_test) {
    long t = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
    std::string time_now = std::to_string(t);

    // get account information - requires authentification
    http::request<http::string_body> req;
    http::response<http::dynamic_body> res;
    req.method(http::verb::get);
    req.target("https://ftx.com/api/account");
    req.set(http::field::host, "ftx.com");
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    req.set("FTX-KEY", APIKeys::KEY);
    req.set("FTX-TS", time_now);
    std::string sign = time_now + "GET" + "/api/account";
    req.set("FTX-SIGN", ayanami::hmac_sha256(APIKeys::SECRET, sign.c_str()));

    ayanami::connections::send_req(req, res);
    ASSERT_EQ(res.result_int(), 200);
}
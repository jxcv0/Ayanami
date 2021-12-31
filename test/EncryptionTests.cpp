#include <gtest/gtest.h>

#include "Encryption.hpp"

TEST(EncryptionTests, hmac_sha256_test) {
    std::string text = "1588591856950POST/api/orders{\"market\":\"BTC-PERP\",\"side\":\"buy\",\"price\":8500,\"size\":1,\"type\":\"limit\",\"reduceOnly\":false,\"ioc\":false,\"postOnly\":false,\"clientId\":null}";
    std::string secret = "T4lPid48QtjNxjLUFOcUZghD7CUJ7sTVsfuvQZF2";
    std::string expected = "2832d853e55db715f59aaadd966cdc51913967da8bf687aad8457a5ac609313e";

    std::string actual = ayanami::hmac_sha256(secret.c_str(), text.c_str());
    ASSERT_EQ(actual, expected);
}
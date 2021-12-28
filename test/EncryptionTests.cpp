#include <gtest/gtest.h>

#include "Encryption.hpp"

TEST(EncryptionTests, hmac_sha256_test) {
    std::string text = "1588591856950POST/api/orders{\"market\": \"BTC-PERP\", \"side\": \"buy\", \"price\": 8500, \"size\": 1, \"type\": \"limit\", \"reduceOnly\": false, \"ioc\": false, \"postOnly\": false, \"clientId\": null}";
    std::string secret = "T4lPid48QtjNxjLUFOcUZghD7CUJ7sTVsfuvQZF2";
    std::string expected = "c4fbabaf178658a59d7bbf57678d44c369382f3da29138f04cd46d3d582ba4ba";

    std::string actual = ayanami::hmac_sha256(secret.c_str(), text.c_str());
    ASSERT_EQ(actual, expected);
}
#include <gtest/gtest.h>

#include "Encryption.hpp"

TEST(EncryptionTests, hmac_sha256_test) {
    std::string text = "exampletext";
    std::string secret = "secretkey";
    std::string expected = "4d0c766a259aa479b7d5a1a9f668b43765be5e49b54de0203febe28a3ba8d132";

    std::string actual = ayanami::hmac_sha256(secret.c_str(), text.c_str());
    ASSERT_EQ(actual, expected);
}
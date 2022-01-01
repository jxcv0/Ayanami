#include "Encryption.hpp"

#include <openssl/hmac.h>
#include <openssl/evp.h>

#include <algorithm>
#include <string.h>
#include <iomanip>

std::string ayanami::spacify(std::string& str) {
    std::string out;
    for (char c : str) {
        switch (c) {
        case ':':
        case ',':
            out += c;
            out += ' ';
            break;
        
        default:
            out += c;
        }
    }
    return out;
}

/**
 * @brief Generate SHA256 HMAC of an input using a secret key
 * 
 * @param key the secret key
 * @param input the input to encrypt
 * @return the encrypted string 
 */
std::string ayanami::hmac_sha256(const char *key, const char *input) {
    unsigned char hash[32];

    HMAC_CTX *ctx = HMAC_CTX_new();
    HMAC_Init_ex(ctx, &key[0], strlen(key), EVP_sha256(), NULL);
    HMAC_Update(ctx, (unsigned char*) &input[0], strlen(input));
    unsigned int len = 32;
    HMAC_Final(ctx, hash, &len);
    HMAC_CTX_reset(ctx);

    std::stringstream str;
    str << std::setfill('0');
    for (int i = 0; i < len; i++) {
        str << std::hex << std::setw(2) << (unsigned int)hash[i];
    }

    return str.str();
}
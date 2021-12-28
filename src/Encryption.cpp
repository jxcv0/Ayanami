#include "Encryption.hpp"

#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <string.h>

/**
 * @brief Generate SHA256 HMAC of an input using a secret key
 * 
 * @param key the secret key
 * @param input the input to encrypt
 * @return the encrypted string 
 */
std::string ayanami::hmac_sha256(const char *key, const char *input) {
    unsigned char *p = (unsigned char*) malloc(1024);
    char buf[1024] = {0};  
    char tmp[3] = {0}; 
    unsigned int output_length = 0;
    p = (unsigned char*) malloc(EVP_MAX_MD_SIZE);

    HMAC_CTX *ctx = HMAC_CTX_new();
    HMAC_Init_ex(ctx, key, strlen(key), EVP_sha256(), NULL);
    HMAC_Update(ctx, (unsigned char*)input, strlen(input)); 

    HMAC_Final(ctx, p, &output_length);
    HMAC_CTX_reset(ctx);
    for (int i = 0; i<32; i++)  
    {  
        sprintf(tmp, "%02x", p[i]);  
        strcat(buf, tmp);  
    }  
    return std::string(buf);
}
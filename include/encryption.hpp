#ifndef ENCRYPTION_HPP
#define ENCRYPTION_HPP

#include <string>

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace ayanami {

    /**
     * @brief Add spaces to a JSON string after every ':' and ',';
     * This functions is reqired as Cpprestdk does not do it
     * 
     * @param str the string to spacify
     */
    std::string spacify(std::string& str);

    /**
     * @brief Generate SHA256 HMAC of an input using a secret key
     * 
     * @param key the secret key
     * @param input the input to encrypt
     * @return the encrypted string 
     */
    std::string hmac_sha256(const char *secret, const char *input);
} // namespace ayanami

#endif
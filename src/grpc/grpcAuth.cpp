//
// Created by ztk on 19.03.24.
//

#include "grpcAuth.h"

std::string grpcAuth::digest(const std::string& signing_key, const std::string& message) {
    unsigned char hmac_result[EVP_MAX_MD_SIZE];
    unsigned int hmac_len;
    HMAC(EVP_sha256(), signing_key.c_str(), signing_key.length(),
         reinterpret_cast<const unsigned char*>(message.c_str()), message.length(),
         hmac_result, &hmac_len);

    // Convert binary digest to hexadecimal string
    std::string hex_digest;
    for (unsigned int i = 0; i < hmac_len; ++i) {
        char buf[3];
        sprintf(buf, "%02x", hmac_result[i]);
        hex_digest.append(buf);
    }
    return hex_digest;
}

std::string grpcAuth::sha256(const std::string& message) {
    unsigned char sha_result[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(message.c_str()), message.length(), sha_result);
    char sha_hex[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&sha_hex[i * 2], "%02x", sha_result[i]);
    }
    sha_hex[2 * SHA256_DIGEST_LENGTH] = '\0';
    return std::string(sha_hex);
}

std::string grpcAuth::sign(const std::string& access_key,
                 const std::string& secret_key,
                 const std::string& expiration,
                 const std::string& signing_string) {
    std::string first = digest(expiration, signing_string);
    std::string second = digest(access_key, first);
    std::string final = digest(secret_key, second);
    return final;
}
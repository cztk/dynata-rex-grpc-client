//
// Created by ztk on 19.03.24.
//

#ifndef DYNATA_REX_GRPC_CLIENT_GRPCAUTH_H
#define DYNATA_REX_GRPC_CLIENT_GRPCAUTH_H

#include <iostream>
#include <string>
#include <openssl/hmac.h>
#include <openssl/sha.h>

class grpcAuth {
public:


    static std::string digest(const std::string &signing_key, const std::string &message);

    static std::string sha256(const std::string &message);

    static std::string sign(const std::string &access_key, const std::string &secret_key, const std::string &expiration,
                     const std::string &signing_string);
};


#endif //DYNATA_REX_GRPC_CLIENT_GRPCAUTH_H

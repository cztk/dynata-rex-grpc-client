//
// Created by ztk on 19.03.24.
//

#ifndef DYNATA_REX_GRPC_CLIENT_GRPCCLIENT_H
#define DYNATA_REX_GRPC_CLIENT_GRPCCLIENT_H
#include <iostream>
#include <grpcpp/grpcpp.h>
#include <grpcpp/security/credentials.h>
#include "proto/definition.grpc.pb.h"
#include "../queue/locked_queue.h"
#include "../daemonize/daemonize.h"


class grpcClient {
private:
    utils::LockedQueue<std::string> *messages;
    std::unique_ptr<eventstream::EventStream::Stub> stub_;
    grpc::ClientContext context;
public:
    explicit grpcClient(const std::shared_ptr<grpc::Channel>& channel, utils::LockedQueue<std::string> *pQueue);
    void Listen(const eventstream::Auth &auth);

    void tryStop();
};



#endif //DYNATA_REX_GRPC_CLIENT_GRPCCLIENT_H

//
// Created by ztk on 15.03.24.
//

#include <grpcpp/security/credentials.h>
#include <grpcpp/create_channel.h>
#include "InputHandler.h"
#include "../grpc/proto/definition.pb.h"
#include "../grpc/grpcClient.h"
#include "../grpc/grpcAuth.h"

InputHandler::InputHandler(Config *pConfig, utils::LockedQueue<std::string> *pQueue) : config(pConfig), messages(pQueue) {

}

InputHandler::~InputHandler() = default;

void InputHandler::initialize() {
    this->clientThread = this->run();
}

void InputHandler::thread_client() {

    grpc::SslCredentialsOptions ssl_opts;
    // Provide paths to your SSL certificates
    ssl_opts.pem_root_certs = ""; // Path to your root certificate
    ssl_opts.pem_private_key = ""; // Path to your private key
    ssl_opts.pem_cert_chain = ""; // Path to your certificate chain

    auto creds = grpc::SslCredentials(ssl_opts);

    // Create a channel to the server with SSL credentials
    std::string server_address = "events.rex.dynata.com:443";

    grpc::ChannelArguments channelArguments;
    channelArguments.SetInt(GRPC_ARG_KEEPALIVE_TIME_MS, 10000);
    channelArguments.SetInt(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 10000);
    channelArguments.SetInt(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);
    channelArguments.SetInt(GRPC_ARG_HTTP2_BDP_PROBE, 1);
    channelArguments.SetInt(GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS, 5000);
    channelArguments.SetInt(GRPC_ARG_HTTP2_MIN_SENT_PING_INTERVAL_WITHOUT_DATA_MS, 10000);
    channelArguments.SetInt(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA, 0);

    auto channel = grpc::CreateCustomChannel(server_address, creds, channelArguments);

    // Instantiate your gRPC client
    client = new grpcClient(channel, messages);

    auto signature = grpcAuth::sign(config->dynataAccessKey, config->dynataSecretKey, "2025-01-01T22:22:22Z", "respondent.events");

    // Define authentication parameters
    eventstream::Auth auth;
    // Fill in the authentication parameters
    auth.set_expiration("2025-01-01T22:22:22Z");
    auth.set_access_key(config->dynataAccessKey);
    auth.set_signature(signature);

    // Make RPC call to listen for events
    status = 1;
    client->Listen(auth);
    status = 0;
}

std::thread InputHandler::run() {
    return std::thread([this] { this->thread_client(); });
}

void InputHandler::deinitialize() {

    client->tryStop();
        if(this->clientThread.joinable()) {
            this->clientThread.join();
        }

    delete client;

}

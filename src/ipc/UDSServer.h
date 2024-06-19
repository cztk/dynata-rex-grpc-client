//
// Created by ztk on 22.03.24.
//

#ifndef DYNATA_REX_GRPC_CLIENT_UDSSERVER_H
#define DYNATA_REX_GRPC_CLIENT_UDSSERVER_H

#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include "../queue/locked_queue.h"
#include "../timer/timed_waiter.h"
#include "../daemonize/daemonize.h"



class Session : public std::enable_shared_from_this<Session>
{
private:
public:
    boost::asio::local::stream_protocol::socket socket_;

    Session(boost::asio::local::stream_protocol::socket socket)
            : socket_(std::move(socket)) {}

    void start() {
        // Session initialization...
    }
    bool is_connected() {
        return socket_.is_open();
    }
};

class UDSServer {

public:
    UDSServer(boost::asio::io_context& io_context, const std::string& file);

    // Broadcasts a message to all clients
    void broadcast(const std::string& message);

    // Accepts incoming connections and adds them to the clients' list
    void run();

    void startBroadcast(utils::LockedQueue<std::string> *pQueue);

    void stop();

private:
    boost::asio::io_context& io_context;
    std::string file;
    std::vector<std::shared_ptr<Session>> clients;
    boost::asio::local::stream_protocol::acceptor acceptor;
    std::atomic<bool> stopFlag{false};

    void cleanupSessions();

};

#endif //DYNATA_REX_GRPC_CLIENT_UDSSERVER_H

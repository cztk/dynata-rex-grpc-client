//
// Created by ztk on 21.03.24.
//

#ifndef DYNATA_REX_GRPC_CLIENT_OUTPUTHANDLER_H
#define DYNATA_REX_GRPC_CLIENT_OUTPUTHANDLER_H

#include <boost/asio.hpp>
#include <string>
#include <thread>
#include <iostream>
#include <vector>
#include <filesystem>

#include "../daemonize/daemonize.h"
#include "../ipc/UDSServer.h"
#include "../queue/locked_queue.h"
#include "../config/config.h"
#include "../timer/timed_waiter.h"

class OutputHandler {
public:
    OutputHandler(Config *pConfig, utils::LockedQueue<std::string> *pQueue);
    ~OutputHandler();
    void initialize();
    void deinitialize();
private:
    Config *config;
    utils::LockedQueue<std::string> *messages;
    std::thread socketOutThread;
    timed_waiter m_timer;
    // Holds the list of connected clients
    std::vector<boost::asio::local::stream_protocol::socket> clients;

    std::thread run();

    void runOutput();

    void stop();

    bool stop_ = false;
    UDSServer *myudsserver{};

};

#endif //DYNATA_REX_GRPC_CLIENT_OUTPUTHANDLER_H

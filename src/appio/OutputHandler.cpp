//
// Created by ztk on 21.03.24.
//

#include "OutputHandler.h"


OutputHandler::OutputHandler(Config *pConfig, utils::LockedQueue<std::string> *pQueue) : config(pConfig), messages(pQueue) {

}

OutputHandler::~OutputHandler() = default;



void OutputHandler::runOutput() {
    //socketOutThread
    std::string message;

    boost::asio::io_context io_context;
    std::string socket_path = config->app_socket;

    std::filesystem::remove(socket_path);

    UDSServer server(io_context, socket_path);

    myudsserver = &server;

    myudsserver->run();

    std::thread ioContextThread([&](){ io_context.run(); });
    std::thread broadcastThread(&UDSServer::startBroadcast, myudsserver, messages);


    // ... when you want to stop
    //server.stop();

    if(ioContextThread.joinable()) {
        ioContextThread.join();
    }

    if(broadcastThread.joinable()) {
        broadcastThread.join();
    }

}

std::thread OutputHandler::run() {
    return std::thread([this] { this->runOutput(); });
}

void OutputHandler::initialize() {

    this->socketOutThread = this->run();
}

void OutputHandler::stop() {
    {
         this->stop_ = true;
         //TODO check object is valid aka myudsserver is in fact a pointer to server
        myudsserver->stop();
    }
}


void OutputHandler::deinitialize() {

    this->stop();
    if(this->socketOutThread.joinable()) {
        this->socketOutThread.join();
    }
}

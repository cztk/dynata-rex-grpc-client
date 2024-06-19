//
// Created by ztk on 15.03.24.
//

#ifndef DYNATA_REX_GRPC_CLIENT_INPUTHANDLER_H
#define DYNATA_REX_GRPC_CLIENT_INPUTHANDLER_H

#include <thread>
#include "../config/config.h"
#include "../queue/locked_queue.h"
#include "../grpc/grpcClient.h"

class InputHandler {
private:

    Config *config;
    utils::LockedQueue<std::string> *messages;
    grpcClient *client;
    std::thread clientThread;

public:
    //! constructor.
    /*!

    */
    InputHandler(Config *pConfig, utils::LockedQueue<std::string> *pQueue);

    //! destructor.
    /*!
    */
    ~InputHandler();

    void initialize();
    void deinitialize();
    int status = 0;

    std::thread run();

    void thread_client();
};


#endif //DYNATA_REX_GRPC_CLIENT_INPUTHANDLER_H

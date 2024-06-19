//
// Created by ztk on 22.03.24.
//
#include "UDSServer.h"

UDSServer::UDSServer(boost::asio::io_context& io_context, const std::string& file)
        : io_context(io_context), file(file), acceptor(io_context, boost::asio::local::stream_protocol::endpoint(file)) {}


// Broadcasts a message to all clients
void UDSServer::broadcast(const std::string &message) {
    std::string send_msg = message;
    send_msg.append("\n");
        for(auto& session : clients) {
            boost::asio::async_write(session->socket_, boost::asio::buffer(send_msg), [](...){});
        }
}

// Accepts incoming connections and adds them to the clients' list
void UDSServer::run() {
    acceptor.async_accept([this](boost::system::error_code ec, boost::asio::local::stream_protocol::socket socket) {
        if (!ec) {
            auto session = std::make_shared<Session>(std::move(socket));
            session->start();
            clients.push_back(session);
        }
        if (APP_RUNNING == 0) return;
        if(!stopFlag) {
            run();
        }
    });
}

void UDSServer::cleanupSessions() {
    clients.erase(std::remove_if(clients.begin(), clients.end(),
                                 [](const std::shared_ptr<Session>& session) {
                                     return !session->is_connected();
                                 }), clients.end());
}

void UDSServer::stop() {
    stopFlag = true;
    acceptor.close();
    io_context.stop();
}

// Periodically sends broadcast messages
void UDSServer::startBroadcast(utils::LockedQueue<std::string> *pQueue) {
    timed_waiter m_timer;
    while (m_timer.wait_for(std::chrono::microseconds(1000))) {
        while (!pQueue->empty()) {
            if(stopFlag) { return; }
            if (APP_RUNNING == 0) return;
            cleanupSessions();
            broadcast(pQueue->pop());
        }
    }
}
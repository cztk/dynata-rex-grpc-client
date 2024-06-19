//
// Created by ztk on 19.03.24.
//

#include "grpcClient.h"


grpcClient::grpcClient(const std::shared_ptr<grpc::Channel>& channel, utils::LockedQueue<std::string> *pQueue)
            : stub_(eventstream::EventStream::NewStub(channel)), messages(pQueue) {}

void grpcClient::tryStop() {
    context.TryCancel();
}

void grpcClient::Listen(const eventstream::Auth& auth) {

        auto reader = stub_->Listen(&context, auth);
        eventstream::Event event;
        while (reader->Read(&event)) {
            if(0 == APP_RUNNING) break;

            std::string event_msg = "{";
            event_msg.append(R"("session": ")");
            event_msg.append(event.session());
            event_msg.append("\"");

            if( event.has_start() ) {
                event_msg.append(", \"start\": 1");
                event_msg.append(", \"end\": 0");

                event_msg.append(", \"group_id\": ");
                event_msg.append(std::to_string(event.start().group_id()));

            }
            if( event.has_end() ) {
                event_msg.append(", \"start\": 0");
                event_msg.append(", \"end\": 1");

                event_msg.append(", \"disposition\": ");
                event_msg.append(event.end().disposition());

                event_msg.append(", \"status\": ");
                event_msg.append(event.end().status());

            }
            event_msg.append(R"(, "timestamp": ")");
            event_msg.append(event.timestamp());
            event_msg.append("\"");

            event_msg.append("}");

            messages->push(event_msg);

            // Do something with the received event

            //std::cout << "Received event: " << event.DebugString() << std::endl;
        }
        grpc::Status status = reader->Finish();
        if (!status.ok()) {
            std::cerr << "RPC failed: " << status.error_message() << std::endl;
        }
}
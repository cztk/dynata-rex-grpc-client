cmake_minimum_required(VERSION 3.15)
project(dynata_rex_grpc_client)

set(CMAKE_CXX_STANDARD 20)


add_executable(dynata_rex_grpc_client main.cpp
        src/config/config.h
        src/daemonize/daemonize.h
        src/timer/timed_waiter.h
        src/queue/locked_queue.h
        src/daemonize/daemonize.cpp
        src/grpc/proto/definition.grpc.pb.cc
        src/grpc/proto/definition.grpc.pb.h
        src/grpc/proto/definition.pb.cc
        src/grpc/proto/definition.pb.h
        src/appio/InputHandler.cpp
        src/appio/InputHandler.h
        src/grpc/grpcClient.cpp
        src/grpc/grpcClient.h
        src/grpc/grpcAuth.cpp
        src/grpc/grpcAuth.h
        src/appio/OutputHandler.cpp
        src/appio/OutputHandler.h
        src/ipc/UDSServer.cpp
        src/ipc/UDSServer.h)

#target_link_libraries(${PROJECT_NAME} PRIVATE protobuf::libprotobuf)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lgrpc++ -lcrypto -lprotobuf ${PROTOBUF_LIBRARY})
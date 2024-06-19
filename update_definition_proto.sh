#!/bin/bash

# apt install protobuf-compiler

protoc -I=. --cpp_out=src/grpc/proto definition.proto

# apt install protobuf-compiler-grpc

protoc -I=. --grpc_out=src/grpc/proto --plugin=protoc-gen-grpc=/usr/bin/grpc_cpp_plugin definition.proto
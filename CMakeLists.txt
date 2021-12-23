cmake_minimum_required(VERSION 3.5.1)

project(Calculator)

set (CMAKE_CXX_STANDARD 11)

######################################################################

find_package(Threads REQUIRED)

######################################################################

set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

######################################################################

find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)

######################################################################

add_library(hw_grpc_proto
    calculator.pb.cc
    calculator.pb.h
    calculator.grpc.pb.cc
    calculator.grpc.pb.h)

target_link_libraries(hw_grpc_proto
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})

foreach(_target
    client server)
    add_executable(${_target} "${_target}.cc")
    target_link_libraries(${_target}
        hw_grpc_proto
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})
endforeach()

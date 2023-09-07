# Minimum CMake required
cmake_minimum_required(VERSION 3.14)

# Project name and version
project(protos_lib VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set (proto_name service)

# Get proto files
get_filename_component(proto "${CMAKE_CURRENT_SOURCE_DIR}/${proto_name}.proto" ABSOLUTE)
get_filename_component(proto_dir "${proto}" DIRECTORY)

# Generate source files
find_program(_PROTOBUF_PROTOC protoc)
find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)

# Generate source files
set(proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/${proto_name}.pb.cc")
set(proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/${proto_name}.pb.h")
set(grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/${proto_name}.grpc.pb.cc")
set(grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/${proto_name}.grpc.pb.h")

add_custom_command(
    OUTPUT "${proto_srcs}" "${proto_hdrs}" "${grpc_srcs}" "${grpc_hdrs}"
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
         --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
         -I "${proto_dir}"
         --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
         "${proto}"
    DEPENDS "${proto}"
)

# Include directories
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR} 
)

add_library(${PROJECT_NAME}  STATIC "${proto_srcs}" "${proto_hdrs}" "${grpc_srcs}" "${grpc_hdrs}")
target_include_directories(${PROJECT_NAME} 
 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link libraries
target_link_libraries(${PROJECT_NAME}  PRIVATE 
    ${_REFLECTION} 
    ${_GRPC_GRPCPP} 
    ${_PROTOBUF_LIBPROTOBUF}
      

)

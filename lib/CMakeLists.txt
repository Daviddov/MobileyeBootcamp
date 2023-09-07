cmake_minimum_required(VERSION 3.10)

project(lib VERSION 1.0)

# List of source files
file(GLOB SRCS *.cpp )

# Create the library
add_library(${PROJECT_NAME} ${SRCS})

# Include headers
target_include_directories(${PROJECT_NAME} 
PRIVATE ${OpenCV_INCLUDE_DIRS}
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

# Find and link OpenCV
find_package(OpenCV REQUIRED)

target_link_libraries(${PROJECT_NAME} 
PRIVATE 
	${OpenCV_LIBS}
    ${_PROTOBUF_LIBPROTOBUF}
        ${_GRPC_GRPCPP}
)

set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})


target_include_directories(${PROJECT_NAME} PUBLIC ${GEN_PROTO_DIR})
find_package(gRPC CONFIG REQUIRED)
find_package(gRPC  REQUIRED)

# Find gRPC package
set(_REFLECTION gRPC::grpc++_reflection)
set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobufd)
set(_REFLECTION gRPC::grpc++_reflection)

if(CMAKE_CROSSCOMPILING)
  find_program(_PROTOBUF_PROTOC protoc)
else()
  set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
endif()

set(_GRPC_GRPCPP gRPC::grpc++)
if(CMAKE_CROSSCOMPILING)
  find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
  set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()



#automAutomatic command file generatoraticly :

set(GEN_PROTO_DIR "${CMAKE_CURRENT_BINARY_DIR}/proto_gen")

# replace it with the lib/camera_service.proto for me its not work
set(PROTO_FILE "${CMAKE_CURRENT_SOURCE_DIR}/camera_service.proto")

get_filename_component(PROTO_NAME ${PROTO_FILE} NAME_WE)

set(GEN_PROTO_SRC "${CMAKE_CURRENT_BINARY_DIR}/${PROTO_NAME}.pb.cc")
set(GEN_PROTO_HDR "${CMAKE_CURRENT_BINARY_DIR}/${PROTO_NAME}.pb.h")
set(GEN_GRPC_SRC "${CMAKE_CURRENT_BINARY_DIR}/${PROTO_NAME}.grpc.pb.cc")
set(GEN_GRPC_HDR "${CMAKE_CURRENT_BINARY_DIR}/${PROTO_NAME}.grpc.pb.h")


add_custom_command(
    OUTPUT "${GEN_PROTO_SRC}" "${GEN_PROTO_HDR}" "${GEN_GRPC_SRC}" "${GEN_GRPC_HDR}"
    COMMAND protoc
    ARGS -I=${CMAKE_CURRENT_SOURCE_DIR}
         --cpp_out=${CMAKE_CURRENT_BINARY_DIR}
         --grpc_out=${CMAKE_CURRENT_BINARY_DIR}
         --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
         ${PROTO_FILE}
    DEPENDS ${PROTO_FILE}
)


set_source_files_properties(
  ${GEN_PROTO_SRC}
  ${GEN_PROTO_HDR}
  ${GEN_GRPC_SRC}
  ${GEN_GRPC_HDR}
  PROPERTIES GENERATED TRUE
)
add_custom_target(YourRealCustomTargetThatRunsProtoc DEPENDS ${GEN_PROTO_SRC} ${GEN_GRPC_SRC})
add_dependencies(${PROJECT_NAME} YourRealCustomTargetThatRunsProtoc)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${OpenCV_INCLUDE_DIRS})



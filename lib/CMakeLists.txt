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

find_package(Protobuf CONFIG REQUIRED)
# Find gRPC package
find_package(gRPC REQUIRED)
message(STATUS "Using protobuf ${protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobufd)
set(_REFLECTION gRPC::grpc++_reflection)
if(CMAKE_CROSSCOMPILING)
  find_program(_PROTOBUF_PROTOC protoc)
else()
  set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
endif()



target_link_libraries(${PROJECT_NAME} 
PRIVATE 
	${OpenCV_LIBS}

	gRPC::grpc++_reflection
    protobuf::libprotobuf
)

#replace it with enviroment variable
set(PROTO_SRC_DIR "C:\\Program Files\\grpc\\bin")

set(GEN_PROTO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/proto_gen")

# replace it with the lib/camera_service.proto for me its not work
set(PROTO_FILE "${PROTO_SRC_DIR}/camera_service.proto")

get_filename_component(PROTO_NAME ${PROTO_FILE} NAME_WE)

set(GEN_PROTO_SRC "${GEN_PROTO_DIR}/${PROTO_NAME}.pb.cc")
set(GEN_PROTO_HDR "${GEN_PROTO_DIR}/${PROTO_NAME}.pb.h")
set(GEN_GRPC_SRC "${GEN_PROTO_DIR}/${PROTO_NAME}.grpc.pb.cc")
set(GEN_GRPC_HDR "${GEN_PROTO_DIR}/${PROTO_NAME}.grpc.pb.h")


add_custom_command(
    OUTPUT "${GEN_PROTO_SRC}" "${GEN_PROTO_HDR}" "${GEN_GRPC_SRC}" "${GEN_GRPC_HDR}"
    COMMAND protoc
    ARGS -I=${PROTO_SRC_DIR}
         --cpp_out=${GEN_PROTO_DIR}
         --grpc_out=${GEN_PROTO_DIR}
         --plugin=protoc-gen-grpc="${PROTO_SRC_DIR}/grpc_cpp_plugin.exe"
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


   message(STATUS "43333333Protobuf Compiler Libraries: ${_PROTOBUF_PROTOC}")

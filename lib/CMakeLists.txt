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
message(STATUS "Using protobuf ${Protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
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

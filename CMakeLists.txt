cmake_minimum_required(VERSION 3.14)

project(Main VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
if(CMAKE_CROSSCOMPILING)
  find_program(_PROTOBUF_PROTOC protoc)
else()
  set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
endif()

# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
if(CMAKE_CROSSCOMPILING)
  find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
  set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()



# Add example projects
add_subdirectory(protos)

# Define the directory for copying assets
set(ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)


# Add subdirectories for libraries
add_subdirectory(lib)
#add_subdirectory(lib_Test)
add_subdirectory(lib_logger)
add_subdirectory(nlohmann)
add_subdirectory(sqlite3)

# Find and link OpenCV
find_package(OpenCV REQUIRED)

# Find gRPC and protobuf packages
find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)  # Use CONFIG to find gRPC

message(STATUS "Using protobuf ${protobuf_VERSION}")

# Function to create an executable with common settings
function(add_common_executable TARGET_NAME SOURCE_FILE)
    add_executable(${TARGET_NAME} ${SOURCE_FILE})
    target_link_libraries(${TARGET_NAME}
        PRIVATE
        lib
        ${OpenCV_LIBS}
        sqlite3
        ${_REFLECTION} 
        ${_GRPC_GRPCPP} 
        ${_PROTOBUF_LIBPROTOBUF} 
        protos_lib
    )

    target_include_directories(${TARGET_NAME}
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR} 
        ${OpenCV_INCLUDE_DIRS}
    )
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} $<TARGET_FILE_DIR:${TARGET_NAME}>/assets
    )
endfunction()

# Build ClientMain executable
add_common_executable(ClientMain ClientMain.cpp)
# Build ServerMain executable
add_common_executable(ServerMain ServerMain.cpp)




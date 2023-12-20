cmake_minimum_required(VERSION 3.14)

project(Main VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)

find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
if(CMAKE_CROSSCOMPILING)
  find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
  set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()

# Define the directory for copying assets
set(ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)



# Add subdirectories for libraries
add_subdirectory(lib)
add_subdirectory(thirdParty)

# Add an option to enable/disable building the tests
option(DBUILD_TESTS "Build the tests" OFF)

if(DBUILD_TESTS)
  add_subdirectory(lib_Test)
endif()

# Set the desired OpenCV directory using CMAKE_PREFIX_PATH
#set(OpenCV_DIR "C:/Users/Admin/Downloads/mobileye_project/opencv/build/install")
set(OpenCV_DIR "C:/Users/Admin/Downloads/mobileye_project/opencv-win/build")
#for dll
#set(OpenCV_DIR "C:/Users/Admin/Downloads/mobileye_project/opencv-win/build/x64/vc16/bin")
find_package(OpenCV REQUIRED)

message(STATUS "Using OpenCV ${OpenCV_VERSION}")

# Function to create an executable with common settings
function(add_common_executable TARGET_NAME SOURCE_FILE)
  add_executable(${TARGET_NAME} ${SOURCE_FILE})
  target_link_libraries(${TARGET_NAME}
    PRIVATE
    lib
    protos_lib
    ${OpenCV_LIBS}
    sqlite3
    ${_REFLECTION} 
    ${_GRPC_GRPCPP} 
    ${_PROTOBUF_LIBPROTOBUF} 
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

# Add options to build server, client, or both
option(DBUILD_SERVER "Build the server" OFF)
option(DBUILD_CLIENT "Build the client" ON)

# Conditionally build ServerMain and/or ClientMain based on the options
if(DBUILD_SERVER)
  add_common_executable(ServerMain ServerMain.cpp)
endif()

if(DBUILD_CLIENT)
  add_common_executable(ClientMain ClientMain.cpp)
endif()


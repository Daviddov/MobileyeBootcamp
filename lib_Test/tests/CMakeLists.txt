cmake_minimum_required(VERSION 3.14)

# Enable testing
enable_testing()

# Include Google Test
include(GoogleTest)

# Find and link OpenCV
find_package(OpenCV REQUIRED)

# Find and link Protobuf
set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

# Find gRPC installation
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

# Function to add a test executable
function(add_test_executable test_name)
    add_executable(${test_name} ${ARGN})
    target_include_directories(${test_name}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_BINARY_DIR}
            ${OpenCV_INCLUDE_DIRS}
    )
    target_link_libraries(${test_name}
        PRIVATE
            lib  # Link your main project library if needed
            gtest_main
            gmock
            ${OpenCV_LIBS}  # Link OpenCV to the test executable
            sqlite3
            ${_REFLECTION} 
            ${_GRPC_GRPCPP} 
            ${_PROTOBUF_LIBPROTOBUF} 
            protos_lib
    )
    gtest_discover_tests(${test_name})
endfunction()

# Discover test source files
file(GLOB TEST_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*Test.cpp")

# Add individual test executables
foreach(test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    add_test_executable(${test_name} ${test_source} functionForTests.cpp functionForTests.h)
endforeach()

# Function to add an executable for running all tests
function(add_test_runner_executable)
    add_executable(run_all_tests ${TEST_SOURCES} functionForTests.cpp functionForTests.h)
    target_include_directories(run_all_tests
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_BINARY_DIR}
            ${OpenCV_INCLUDE_DIRS}
    )
    target_link_libraries(run_all_tests
        PRIVATE
            lib  # Link your main project library if needed
            gtest_main
            gmock
            ${OpenCV_LIBS}  # Link OpenCV to the test executable
            sqlite3
            ${_REFLECTION} 
            ${_GRPC_GRPCPP} 
            ${_PROTOBUF_LIBPROTOBUF} 
            protos_lib
    )
    gtest_discover_tests(run_all_tests)
endfunction()

# Add an executable to run all tests
add_test_runner_executable()

# Include the Google Test framework
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/master.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

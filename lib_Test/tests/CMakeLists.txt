cmake_minimum_required(VERSION 3.14)

# Enable testing
enable_testing()

# Include Google Test
include(GoogleTest)

# Find and link OpenCV
find_package(OpenCV REQUIRED)

# Include directories 
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${OpenCV_INCLUDE_DIRS}
    ${WindowsSDK_INCLUDE_DIRS}  # Windows SDK include directory
    ${gRPC_INCLUDE_DIRS}        # gRPC include directory
)


# Discover test source files
file(GLOB TEST_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*Test.cpp")

# Find gRPC and protobuf packages
find_package(protobuf CONFIG REQUIRED)
find_package(gRPC REQUIRED)

message(STATUS "Using protobuf ${protobuf_VERSION}")

# Function to add a test executable
function(add_test_executable test_name)
    add_executable(${test_name} ${ARGN})
    target_link_libraries(${test_name}
        lib  # Link your main project library if needed
        gtest_main
        gmock
        ${OpenCV_LIBS}  # Link OpenCV to the test executable
        sqlite3
        gRPC::grpc++
        protobuf::libprotobuf
    )
    gtest_discover_tests(${test_name})
endfunction()

# Add individual test executables
foreach(test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    add_test_executable(${test_name} ${test_source} functionForTests.cpp functionForTests.h)
endforeach()



# Add an executable to run all tests
add_executable(run_all_tests ${TEST_SOURCES} functionForTests.cpp functionForTests.h)
target_link_libraries(run_all_tests
    lib  # Link your main project library if needed
    gtest_main
    gmock
    ${OpenCV_LIBS}  # Link OpenCV to the test executable
    sqlite3
    gRPC::grpc++
    protobuf::libprotobuf
)
gtest_discover_tests(run_all_tests)

# Include the Google Test framework
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/master.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
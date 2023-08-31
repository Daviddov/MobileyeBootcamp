cmake_minimum_required(VERSION 3.14)

# Enable testing
enable_testing()

# Include Google Test
include(GoogleTest)
# Find and link OpenCV for the test executable
find_package(OpenCV REQUIRED)

# Include directories for OpenCV and Google Test headers
include_directories(
    ${OpenCV_INCLUDE_DIRS}
)

# List of test sources
set(TEST_SOURCES
    CalcAbsDiffTest.cpp
    CurrentTimeTest.cpp
    YoloRectTest.cpp
    SqlHandlerTest.cpp
)

# Function to add a test executable
function(add_test_executable test_name)
    add_executable(${test_name} ${ARGN})
    target_link_libraries(${test_name}
        lib  # Link your main project library if needed
        gtest_main
        gmock
        ${OpenCV_LIBS}  # Link OpenCV to the test executable
        sqlite3
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

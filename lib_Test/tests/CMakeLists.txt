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
# Add the test executable for CalcAbsDiffTest
add_executable(CalcAbsDiffTest CalcAbsDiffTest.cpp "functionForTests.cpp" "functionForTests.h")
target_link_libraries(CalcAbsDiffTest
    lib  # Link your main project library if needed
    gtest_main
    gmock
    ${OpenCV_LIBS}  # Link OpenCV to the test executable
    sqlite3
)

# Add the test executable for CurrentTimeTest
add_executable(CurrentTimeTest CurrentTimeTest.cpp "functionForTests.cpp" "functionForTests.h")
target_link_libraries(CurrentTimeTest
    lib  # Link your main project library if needed
    gtest_main
    gmock
    ${OpenCV_LIBS}  # Link OpenCV to the test executable
    sqlite3
)

# Add the test executable for YoloRectTest
add_executable(YoloRectTest YoloRectTest.cpp "functionForTests.cpp" "functionForTests.h")
target_link_libraries(YoloRectTest
    lib  # Link your main project library if needed
    gtest_main
    gmock
    ${OpenCV_LIBS}  # Link OpenCV to the test executable
    sqlite3
)

# Add the test executable for SqlHandlerTest
add_executable(SqlHandlerTest SqlHandlerTest.cpp "functionForTests.cpp" "functionForTests.h")
target_link_libraries(SqlHandlerTest
    lib  # Link your main project library if needed
    gtest_main
    gmock
    ${OpenCV_LIBS}  # Link OpenCV to the test executable
    sqlite3
)

# Include the Google Test framework
gtest_discover_tests(CalcAbsDiffTest)
gtest_discover_tests(CurrentTimeTest)
gtest_discover_tests(YoloRectTest)
gtest_discover_tests(SqlHandlerTest)

# Google Test setup (fetching from GoogleTest repository)
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/master.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

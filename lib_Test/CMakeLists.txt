cmake_minimum_required(VERSION 3.14)
file(GLOB SRCS *.cpp)
project(lib_Test VERSION 1.0)
# Find and link OpenCV for the test executable
find_package(OpenCV REQUIRED)
# Include directories for OpenCV and Google Test headers
include_directories(
    ${OpenCV_INCLUDE_DIRS}
)
# link against gtest or gtest_main as needed. Eg
add_executable(${PROJECT_NAME}  ${SRCS})
target_link_libraries(${PROJECT_NAME}
    lib
    gtest_main
    gmock
    gmock_main
    ${OpenCV_LIBS}  # Link OpenCV to the test executable 
    sqlite3
)
# post build command
add_custom_command(
    TARGET ${PROJECT_NAME}
    COMMENT "Run tests"
    POST_BUILD
    COMMAND ${PROJECT_NAME}
)
# Google Test setup
if (NOT googletest) # is googletest defined if already built?
    include(FetchContent)
    FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/refs/heads/master.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()
# Google Test setup - (if it's a test project)
if (BUILD_TESTING)
    # Add your gtest configuration here
endif()
add_test(NAME Test COMMAND ${PROJECT_NAME})
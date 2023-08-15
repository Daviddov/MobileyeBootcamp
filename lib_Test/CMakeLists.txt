cmake_minimum_required(VERSION 3.14)

project(lib_Test VERSION 1.0)
set(OpenCV_DIR "C:\\Users\\1\\Desktop\\KamaTech\\Bootcamp\\OpenCV\\opencv\\build")

# Find and link OpenCV for the test executable
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# link against gtest or gtest_main as needed. Eg
add_executable(${PROJECT_NAME} "Tests.cpp")
target_link_libraries(${PROJECT_NAME}
    lib
    gtest_main
    ${OpenCV_LIBS}  # Link OpenCV to the test executable 
    sqlite3
)


add_test(NAME Test COMMAND ${PROJECT_NAME})

# post build command
add_custom_command(
    TARGET ${PROJECT_NAME}
    COMMENT "Run tests"
    POST_BUILD
    COMMAND ${PROJECT_NAME}
)

cmake_minimum_required(VERSION 3.14)

project(ServerMain VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the directory for copying assets
set(ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)

# Link lib
add_subdirectory(lib)
add_subdirectory(lib_Test)
add_subdirectory(lib_logger)
add_subdirectory(nlohmann)
add_subdirectory(sqlite3)

# Find and link OpenCV for the executables
find_package(OpenCV REQUIRED)

# Build ServerMain executable
add_executable(ServerMain
    ServerMain.cpp
)

target_link_libraries(ServerMain
    PRIVATE
    lib
    ${OpenCV_LIBS}
    sqlite3
)

# Build ClientMain executable
add_executable(ClientMain
    ClientMain.cpp
)

target_link_libraries(ClientMain
    PRIVATE
    lib
    ${OpenCV_LIBS}
    sqlite3
)

# Include directories for OpenCV and other dependencies if necessary
target_include_directories(ServerMain
    PRIVATE
    ${OpenCV_INCLUDE_DIRS}
)

target_include_directories(ClientMain
    PRIVATE
    ${OpenCV_INCLUDE_DIRS}
)

# Copy assets after building the executables
add_custom_command(TARGET ServerMain POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} $<TARGET_FILE_DIR:ServerMain>/assets
)

add_custom_command(TARGET ClientMain POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} $<TARGET_FILE_DIR:ClientMain>/assets
)

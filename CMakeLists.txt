cmake_minimum_required(VERSION 3.14)

project(ServerMain VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the directory for copying assets
set(ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)

# Add subdirectories for libraries
add_subdirectory(lib)
add_subdirectory(lib_Test)
add_subdirectory(lib_logger)
add_subdirectory(nlohmann)
add_subdirectory(sqlite3)

# Find and link OpenCV
find_package(OpenCV REQUIRED)

# Function to create an executable with common settings
function(add_common_executable TARGET_NAME SOURCE_FILE)
    add_executable(${TARGET_NAME} ${SOURCE_FILE})
    target_link_libraries(${TARGET_NAME}
        PRIVATE
        lib
        ${OpenCV_LIBS}
        sqlite3
    )
    target_include_directories(${TARGET_NAME}
        PRIVATE
        ${OpenCV_INCLUDE_DIRS}
    )
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} $<TARGET_FILE_DIR:${TARGET_NAME}>/assets
    )
endfunction()

# Build ServerMain executable
add_common_executable(ServerMain ServerMain.cpp)

# Build ClientMain executable
add_common_executable(ClientMain ClientMain.cpp)

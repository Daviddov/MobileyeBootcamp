cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the directory for copying assets
set(ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)
set(ROOT_DIR ${CMAKE_SOURCE_DIR})

# Link lib
add_subdirectory(lib)
add_subdirectory(lib_Test)
add_subdirectory(lib_logger)
add_subdirectory(nlohmann)
add_subdirectory(sqlite3)
add_subdirectory(ServerMain)
add_subdirectory(ClientMain)



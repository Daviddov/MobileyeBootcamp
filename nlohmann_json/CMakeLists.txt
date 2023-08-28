cmake_minimum_required(VERSION 3.10)

project(nlohmann_json VERSION 1.0)
add_library(${PROJECT_NAME} INTERFACE)
# Include headers
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

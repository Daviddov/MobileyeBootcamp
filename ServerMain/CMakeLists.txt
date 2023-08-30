project(ServerMain VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(${PROJECT_NAME}
    ServerMain.cpp
)


# Find and link OpenCV for the test executable
find_package(OpenCV REQUIRED)

# Include directories for OpenCV and Google Test headers
include_directories(
    ${OpenCV_INCLUDE_DIRS}

)

target_link_libraries(${PROJECT_NAME}
    lib
    ${OpenCV_LIBS}  # Link OpenCV to the test executable 
    sqlite3
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)
cmake_minimum_required(VERSION 3.0)

project(main VERSION 0.1.0)

# Add the C++ standard for the project (replace 'XX' with the desired C++ version, e.g., 11, 14, 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source files to a variable (you can add more if needed)
set(SOURCES
    main.cpp
    Header.h
)

# Create the executable target
add_executable(main ${SOURCES})

# Find and link OpenCV
find_package(OpenCV REQUIRED)
target_include_directories(main PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(main PRIVATE ${OpenCV_LIBS})

# If you are using threads, ensure you link against them (only necessary if you explicitly use threads)
find_package(Threads REQUIRED)
target_link_libraries(main PRIVATE Threads::Threads)

# Define the directory for copying assets
set(ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)

# Custom command to copy the entire "assets" folder during the build process
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} $<TARGET_FILE_DIR:main>/assets
)

# Set the working directory to the build directory so that the assets are accessible during runtime
set_target_properties(main PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:main>")

# Include the "sql" subdirectory containing SQLite source files
add_subdirectory(sqlite_build)

# Link SQLite to the main executable
target_link_libraries(main PRIVATE sqlite3)

# Copy the SQLite DLL to the build directory
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sqlite3>
        $<TARGET_FILE_DIR:main>
)
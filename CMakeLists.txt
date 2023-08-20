cmake_minimum_required(VERSION 3.14)

project(Main VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Main executable
add_executable(${PROJECT_NAME} Main.cpp "lib_logger/Logger.h")

# Link lib
add_subdirectory(lib)
add_subdirectory(lib_Test)
target_link_libraries(${PROJECT_NAME} PRIVATE lib)

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
set(OpenCV_DIR "C:\\Users\\1\\Desktop\\KamaTech\\Bootcamp\\OpenCV\\opencv\\build")
# Find and link OpenCV
find_package(OpenCV REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

# Define the directory for copying assets
set(ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)

# Custom command to copy the entire "assets" folder during the build process
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)


# Include the "sql" subdirectory containing SQLite source files
add_subdirectory(sqlite3)

# Link SQLite to the main executable
target_link_libraries(${PROJECT_NAME} PRIVATE sqlite3)

# Copy the SQLite DLL to the build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sqlite3>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)


# Set the working directory to the build directory so that the assets are accessible during runtime
set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")

# Google Test setup - (if it's a test project)
if (BUILD_TESTING)
    # Add your gtest configuration here
endif()

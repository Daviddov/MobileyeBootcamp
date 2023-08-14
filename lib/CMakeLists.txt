project(lib)

set(lib_Src
	Header.h
	"Source.cpp"	
 "Camera.cpp" "Server.cpp")

add_library(${PROJECT_NAME} ${lib_Src})


# Find and link OpenCV
find_package(OpenCV REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})


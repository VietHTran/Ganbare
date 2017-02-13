cmake_minimum_required(VERSION 2.8)
project( Ganbare )
find_package( OpenCV REQUIRED )
find_package( Threads )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( ganbare Ganbare.cpp )
target_link_libraries( ganbare ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(ganbare PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

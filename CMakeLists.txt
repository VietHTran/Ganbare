cmake_minimum_required(VERSION 2.8)
project( Ganbare )
find_package( OpenCV REQUIRED )
find_package( Threads )

#Change 2 below directories based on where you install socket.io
set(SOCKET_IO_INCLUDE_DIRS "/home/viet/socket.io-client-cpp/build/include")
set(SOCKET_IO_LIBS "/home/viet/socket.io-client-cpp/build/lib")

include_directories( ${OpenCV_INCLUDE_DIRS} ${SOCKET_IO_INCLUDE_DIRS})
add_executable( ganbare Ganbare.cpp common.cpp server.cpp)
target_link_libraries( ganbare ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT} ${SOCKET_IO_LIBS})
set_target_properties(ganbare PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

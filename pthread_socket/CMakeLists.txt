cmake_minimum_required(VERSION 3.0.0)

project(server_pthread)

find_package(Threads)

add_executable(server_pthread main.c ./src/socket.c ./include/socket.h)

target_link_libraries(server_pthread ${CMAKE_THREAD_LIBS_INIT})


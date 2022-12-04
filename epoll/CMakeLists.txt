cmake_minimum_required(VERSION 3.0.0)

project(select)

find_package(Threads)

add_executable(select main.c ./src/socket.c ./include/socket.h)

target_link_libraries(select ${CMAKE_THREAD_LIBS_INIT})


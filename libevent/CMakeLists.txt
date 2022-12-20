cmake_minimum_required(VERSION 3.0.0)

project(Select)

find_package(Threads)

add_executable(select select.c ./src/socket.c ./include/socket.h)
add_executable(client client.c ./src/socket.c ./include/socket.h)

target_link_libraries(select ${CMAKE_THREAD_LIBS_INIT})


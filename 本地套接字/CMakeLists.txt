cmake_minimum_required(VERSION 3.0.0)

project(UDP)

add_executable(server server.c ./src/socket.c ./include/socket.h)
add_executable(client client.c ./src/socket.c ./include/socket.h)
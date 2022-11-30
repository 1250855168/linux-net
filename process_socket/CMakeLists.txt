cmake_minimum_required(VERSION 3.0.0)

project(server_process)

add_executable(server_process main.c ./src/socket.c ./include/socket.h)


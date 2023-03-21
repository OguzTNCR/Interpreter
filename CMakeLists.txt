cmake_minimum_required(VERSION 3.24)
project(cmpe230 C)

set(CMAKE_C_STANDARD 11)

add_executable(cmpe230 main.c token.h parser.h parser.c)

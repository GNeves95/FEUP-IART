cmake_minimum_required(VERSION 3.13)
project(klotski C)

set(CMAKE_C_STANDARD 11)

add_executable(klotski main.c board.h block.h vector.h vector.c utils.h block.c board.c)
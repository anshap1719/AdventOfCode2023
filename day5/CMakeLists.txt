cmake_minimum_required(VERSION 3.27)
project(day5 C)

set(CMAKE_C_STANDARD 11)

add_executable(day5 main.c
        types.h
        parse.c
        parse.h
        types.c
        almanac.c
        almanac.h)

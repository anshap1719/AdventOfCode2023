cmake_minimum_required(VERSION 3.26)
project(day3 C)

set(CMAKE_C_STANDARD 11)

add_executable(day3
        main.c
        contents.c
        contents.h
        types.h
        engine_part.c
        position.c
        position.h
        engine_part.h
        gear_ratio.c
        gear_ratio.h)

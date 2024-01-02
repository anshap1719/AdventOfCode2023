cmake_minimum_required(VERSION 3.26)
project(day4 C)

set(CMAKE_C_STANDARD 11)

add_executable(day4
        main.c
        card.c
        card.h
        types.h
        points.c
        points.h
        cards.c
        cards.h)

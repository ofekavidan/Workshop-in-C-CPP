cmake_minimum_required(VERSION 3.16)
project(ex1_ofek_avidan C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(ex1_ofek_avidan
        cipher.c
        cipher.h
        main.c
        tests.c
        tests.h)

cmake_minimum_required(VERSION 3.16)
project(ex3a_ofek_avidan C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(ex3a_ofek_avidan
        linked_list.c
        linked_list.h
        ../ex3b-ofek.avidan/markov_chain.c
        markov_chain.h
        tweets_generator.c)

cmake_minimum_required(VERSION 3.30)
project(spaceXplorer C)

set(CMAKE_C_STANDARD 99)

add_executable(spaceXplorer spaceXplorer.c
        game.c
        game.h)

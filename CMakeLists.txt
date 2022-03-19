cmake_minimum_required(VERSION 3.0.0)
project(vector_arr)

OPTION(TEST "Run test" OFF)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic")

if (TEST)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage -fPIC -O0")
endif()

ADD_SUBDIRECTORY(project)

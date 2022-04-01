cmake_minimum_required(VERSION 3.0.0)
project(CompareImpl)



OPTION(TEST "Run test" OFF)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Werror -Wpedantic")

if (TEST)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread -coverage -lgcov" )
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage -fPIC -O0")
endif()

ADD_SUBDIRECTORY(project)
cmake_minimum_required(VERSION 3.0.0)
project(vector_arr)

OPTION(TEST "Run test" OFF)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

ADD_SUBDIRECTORY(project)

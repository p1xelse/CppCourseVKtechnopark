cmake_minimum_required(VERSION 3.0.0)
project(vector_arr)

OPTION(WITH_MEMCHECK "Run with memcheck" OFF)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

# ENABLE_TESTING()

ADD_SUBDIRECTORY(project)
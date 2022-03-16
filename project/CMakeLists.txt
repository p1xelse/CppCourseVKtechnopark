cmake_minimum_required(VERSION 3.0.0)
project(vector_arr)

add_subdirectory(vector_array)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")


add_executable(${PROJECT_NAME} main.c)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${VECTOR_ARRAY_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${VECTOR_ARRAY_LIB_LIBRARIES})

message("SOURCES = ${SOURCES}")

add_subdirectory(tests)
cmake_minimum_required(VERSION 3.14)
project(test)

set(CMAKE_CXX_STANDARD 11)

if (TEST)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -O0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread" )
endif()

file(GLOB SOURCES_WORDS_ARRAY test_words_array.cpp)

find_package(GTest REQUIRED)

set(words_array_test "${PROJECT_NAME}_words_array")

add_executable(${words_array_test} ${SOURCES_WORDS_ARRAY})
target_include_directories(${words_array_test} PUBLIC ${WORDS_ARRAY_LIB_INCLUDE_DIRS})
target_link_libraries(${words_array_test} ${WORDS_ARRAY_LIB} GTest::gtest_main)



file(GLOB SOURCES_ST_LARGEST_WORD test_st_largest_word.cpp)

find_package(GTest REQUIRED)

set(st_largest_word_test "${PROJECT_NAME}_st_largest_word")

add_executable(${st_largest_word_test} ${SOURCES_ST_LARGEST_WORD})
target_include_directories(${st_largest_word_test} PUBLIC ${ST_LARGEST_WORD_INCLUDE_DIRS})
target_link_libraries(${st_largest_word_test} ${ST_LARGEST_WORD_LIB} GTest::gtest_main)

set(file "${CMAKE_CURRENT_SOURCE_DIR}/1.txt")
message("file = ${file}")

file(GLOB SOURCES_DYN_LARGEST_WORD test_dyn_largest_word.cpp)

find_package(GTest REQUIRED)

set(dyn_largest_word_test "${PROJECT_NAME}_dyn_largest_word")

add_executable(${dyn_largest_word_test} ${SOURCES_DYN_LARGEST_WORD})
target_include_directories(${dyn_largest_word_test} PUBLIC ${DYN_LARGEST_WORD_INCLUDE_DIRS})
target_link_libraries(${dyn_largest_word_test} ${DYN_LARGEST_WORD_LIB} GTest::gtest_main)

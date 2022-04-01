cmake_minimum_required(VERSION 3.0.0)
project(dyn_largest_word_lib)
  
file(GLOB SOURCES *.c)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread" )

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${WORDS_ARRAY_LIB})
target_include_directories(${PROJECT_NAME} PUBLIC ${WORDS_ARRAY_LIB_INCLUDE_DIRS})

# link_directories()
# target_include_directories()

set(DYN_LARGEST_WORD_LIB ${PROJECT_NAME} PARENT_SCOPE)
set(DYN_LARGEST_WORD_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)

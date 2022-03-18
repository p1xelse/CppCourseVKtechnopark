add_subdirectory(vector_array)

add_executable(${PROJECT_NAME} main.c)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${VECTOR_ARRAY_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${VECTOR_ARRAY_LIB_LIBRARIES})

message("SOURCES = ${SOURCES}")

add_subdirectory(tests)
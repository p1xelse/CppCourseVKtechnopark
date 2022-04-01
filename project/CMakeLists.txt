add_subdirectory(words_array)
add_subdirectory(st_largest_word)
add_subdirectory(dyn_largest_word)

add_executable(${PROJECT_NAME} main.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${DYN_LARGEST_WORD_INCLUDE_DIRS} ${ST_LARGEST_WORD_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${DYN_LARGEST_WORD_LIB} ${ST_LARGEST_WORD_LIB})

message("LIBS = ${WORDS_ARRAY_LIB_INCLUDE_DIRS} ${DYN_LARGEST_WORD_INCLUDE_DIRS} ${ST_LARGEST_WORD_INCLUDE_DIRS}")

add_subdirectory(tests)

#ifndef PROJECT_DYN_LARGEST_WORD_DYN_LARGEST_WORD_H_
#define PROJECT_DYN_LARGEST_WORD_DYN_LARGEST_WORD_H_

#define ERR_THREAD_CREATE 5
#define ERR_THREAD_JOIN 6
#define ERR_MEMORY_ALLOC 7
#define ERR_MUTEX_EXCHANGE 8

#define ERR_NULL_STR 10
#define ERR_NULL_DELIM 11

int get_largest_word_thread(char *str, const char **word, char *delimeters);

#endif  // PROJECT_DYN_LARGEST_WORD_DYN_LARGEST_WORD_H_

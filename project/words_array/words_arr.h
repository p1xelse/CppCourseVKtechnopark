#ifndef PROJECT_WORDS_ARRAY_WORDS_ARR_H_
#define PROJECT_WORDS_ARRAY_WORDS_ARR_H_

#define ERR_MEM 20
#define ERR_NO_WORDS 21

typedef struct {
    const char **arr;
    int len;
} words_arr_t;

void init_words_array(words_arr_t *arr);
void free_words_array(words_arr_t *arr);

int get_count_words(char *str, char *delimeters);
int str_split(char *str, char *delimeters, words_arr_t *arr);
int find_index_largest_word(const char **arr, int len);

#endif  // PROJECT_WORDS_ARRAY_WORDS_ARR_H_

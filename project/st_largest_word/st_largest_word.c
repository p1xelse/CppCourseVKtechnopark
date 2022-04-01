#define _GNU_SOURCE

#include "st_largest_word.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "words_arr.h"

int get_largest_word(char *str, const char **word, char *delimeters) {
    if (str == NULL) return ERR_NULL_STR;

    if (delimeters == NULL) {
        return ERR_NULL_DELIM;
    }

    words_arr_t arr;
    init_words_array(&arr);
    int err = 0;
    err = str_split(str, delimeters, &arr);

    if (err) {
        free_words_array(&arr);
        return err;
    }

    int ind = find_index_largest_word(arr.arr, arr.len);
    *word = strdup(arr.arr[ind]);

    if (*word == NULL) {
        err = ERR_MEMORY_ALLOC;
    }
    free_words_array(&arr);
    return err;
}

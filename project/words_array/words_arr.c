#define _GNU_SOURCE

#include "words_arr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_count_words(char *str, char *delimeters) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (strchr(delimeters, str[i]) == NULL &&
            strchr(delimeters, str[i + 1]) != NULL) {
            count++;
        }
    }

    return count;
}

int init_words_array(words_arr_t *arr) {
    if (arr == NULL) {
        return ERR_NULL_PTR_INIT;
    }

    arr->arr = NULL;
    arr->len = 0;

    return 0;
}

void free_words_array(words_arr_t *arr) {
    for (int i = 0; i < arr->len; ++i) {
        free((void *)(arr->arr)[i]);
    }

    free(arr->arr);
    arr->arr = NULL;
    arr->len = 0;
}

int str_split(char *str, char *delimeters, words_arr_t *arr) {
    int count_words = get_count_words(str, delimeters);

    if (count_words == 0) return ERR_NO_WORDS;

    arr->len = count_words;
    arr->arr = malloc(sizeof(char *) * count_words);

    if (!arr->arr) {
        return ERR_MEM;
    }

    int idx = 0;
    char *saveptr = NULL;
    char *token = strtok_r(str, delimeters, &saveptr);

    while (token) {
        *(arr->arr + idx++) = strdup(token);
        token = strtok_r(NULL, delimeters, &saveptr);
    }

    return 0;
}

int find_index_largest_word(const char **arr, int len) {
    size_t max_len = 0;
    int ans_ind = 0;
    for (int i = 0; i < len; i++) {
        if (strlen(arr[i]) > max_len) {
            max_len = strlen(arr[i]);
            ans_ind = i;
        }
    }
    return ans_ind;
}

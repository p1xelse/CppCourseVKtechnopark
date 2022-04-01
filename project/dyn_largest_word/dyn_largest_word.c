#define _GNU_SOURCE

#include <ctype.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dyn_largest_word.h"
#include "words_arr.h"

typedef struct {
    pthread_mutex_t mutex;
    size_t max_len;
    size_t index_max_len_word;
    int errflag;
} data_t;

typedef struct {
    size_t beg_ind;
    size_t len;
} chank_t;

static data_t data = {PTHREAD_MUTEX_INITIALIZER, 0, 0};
static words_arr_t words_arr;

static void data_init() {
    data.max_len = 0;
    data.index_max_len_word = 0;
}

static void *thread_find_largest_word(void *arg) {
    chank_t *chank = arg;

    int ind =
        find_index_largest_word(words_arr.arr + chank->beg_ind, chank->len);

    int cur_index = chank->beg_ind + ind;

    pthread_mutex_t *mutex = &data.mutex;

    if (cur_index < words_arr.len) {
        int errflag = 0;
        errflag = pthread_mutex_lock(mutex);
        if (errflag) {
            data.errflag = ERR_MUTEX_EXCHANGE;
            return arg;
        }
        int cur_len = strlen(words_arr.arr[cur_index]);
        if (cur_len > data.max_len) {
            data.max_len = cur_len;
            data.index_max_len_word = cur_index;
        }

        errflag = pthread_mutex_unlock(mutex);

        if (errflag) {
            data.errflag = ERR_MUTEX_EXCHANGE;
            return arg;
        }
    }
    return arg;
}

static void split_len_to_chank(chank_t *arr, int count_chanks, int len) {
    int chank_len = 0;
    chank_len = len / count_chanks;
    int mod = len % count_chanks;

    arr[0].beg_ind = 0;

    for (int i = 0; i < count_chanks; i++) {
        int cur_len = chank_len;

        if (mod > 0) {
            cur_len++;
            mod--;
        }

        arr[i].len = cur_len;

        if (i == 0) {
            arr[i].beg_ind = 0;
        } else {
            arr[i].beg_ind = arr[i - 1].beg_ind + arr[i - 1].len;
        }
    }
}

int get_largest_word_thread(char *str, const char **word, char *delimeters) {
    if (str == NULL) {
        return ERR_NULL_STR;
    }

    if (delimeters == NULL) {
        return ERR_NULL_DELIM;
    }
    
    int err = 0;

    words_arr_t arr;
    init_words_array(&arr);

    err = str_split(str, delimeters, &arr);

    if (err) {
        return err;
    }

    words_arr = arr;

    const int THREAD_COUNT = sysconf(_SC_NPROCESSORS_ONLN);

    pthread_t threadIds[THREAD_COUNT];
    chank_t info_arr[THREAD_COUNT];

    split_len_to_chank(info_arr, THREAD_COUNT, arr.len);

    data_init();

    for (int i = 0; !err && i < THREAD_COUNT; i++) {
        int errflag = pthread_create(&threadIds[i], NULL,
                                     thread_find_largest_word, &info_arr[i]);
        if (errflag != 0) {
            err = ERR_THREAD_CREATE;
        }
    }

    if (!err && data.errflag != 0) {
        err = data.errflag;
    }

    for (int i = 0; !err && i < THREAD_COUNT; i++) {
        int errflag = pthread_join(threadIds[i], NULL);
        if (errflag != 0) {
            err = ERR_THREAD_JOIN;
        }
    }

    if (!err) {
        *word = strdup(arr.arr[data.index_max_len_word]);
    }

    free_words_array(&arr);

    if (*word == NULL) {
        err = ERR_MEMORY_ALLOC;
    }

    return err;
}

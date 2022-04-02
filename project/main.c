#define _GNU_SOURCE

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dyn_largest_word.h"
#include "st_largest_word.h"

#define ERR_MEM 10
#define ERR_OPEN_FILE 11
#define ERR_ARGC 12
#define ERR_FUNC 13

char *read_file(char *filename, int *err) {
    *err = 0;
    FILE *f = fopen(filename, "r");

    if (!f) {
        *err = ERR_OPEN_FILE;
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);

    char *str = malloc(size + 1);

    if (str == NULL) {
        *err = ERR_MEM;
    }

    if (!*err) {
        str[size] = '\0';
        fseek(f, 0, SEEK_SET);
        fread(str, size, 1, f);
    }

    fclose(f);
    return str;
}

typedef enum { BASIC_IMPL, THREAD_IMPL } impl_t;

int get_avg_time(char *str, const int count_measurments, impl_t type,
                 double *avg_time) {
    int err = 0;
    double elapsed_finish = 0;

    for (int i = 0; i < count_measurments; i++) {
        const char *word = NULL;
        char delim[] = " ;,\n.";
        char *str1 = strdup(str);

        if (!str1) {
            printf("Error mem during stress test");
            return ERR_MEM;
        }

        struct timespec start, finish;

        if (type == BASIC_IMPL) {
            clock_gettime(CLOCK_MONOTONIC, &start);
            err = get_largest_word(str1, &word, delim);
            clock_gettime(CLOCK_MONOTONIC, &finish);
        } else if (type == THREAD_IMPL) {
            clock_gettime(CLOCK_MONOTONIC, &start);
            err = get_largest_word_thread(str1, &word, delim);
            clock_gettime(CLOCK_MONOTONIC, &finish);
        }

        if (err) {
            free(str1);
            printf("Error in func during stress test");
            return ERR_FUNC;
        }

        free((void *)word);

        double elapsed;
        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
        elapsed_finish += elapsed;

        free(str1);
    }

    elapsed_finish /= count_measurments;
    *avg_time = elapsed_finish;

    return err;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return ERR_ARGC;
    }

    int err = 0;
    char *str = read_file(argv[1], &err);

    if (err) {
        free(str);
        printf("Error read file");
        return err;
    }

    const int COUNT_MEASUREMENTS = 20;

    double avg_time_basic;
    err = get_avg_time(str, COUNT_MEASUREMENTS, BASIC_IMPL, &avg_time_basic);

    double avg_time_thread;
    if (!err) {
        err = get_avg_time(str, COUNT_MEASUREMENTS, THREAD_IMPL,
                           &avg_time_thread);
    }

    free(str);

    if (!err) {
        printf("Basic impl time - %lf\n", avg_time_basic);
        printf("Threads impl time - %lf\n", avg_time_thread);
    } else {
        printf("Error during measurments");
    }

    return err;
}
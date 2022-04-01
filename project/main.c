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

char *readFile(char *filename, int *err) {
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
        *err = 11;
    }

    if (!*err) {
        str[size] = '\0';
        fseek(f, 0, SEEK_SET);
        fread(str, size, 1, f);
    }

    fclose(f);
    return str;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return ERR_ARGC;
    }

    int err = 0;
    char *str = readFile(argv[1], &err);

    if (err) {
        free(str);
        printf("Error read file");
        return err;
    }

    const int COUNT_MEASUREMENTS = 20;
    double elapsed_1_finish = 0;

    for (int i = 0; i < COUNT_MEASUREMENTS; i++) {
        const char *word = NULL;
        char delim[] = " ;,\n.";
        char *str1 = strdup(str);

        if (!str1) {
            printf("Error mem during stress test");
            return ERR_MEM;
        }

        struct timespec start, finish;
        clock_gettime(CLOCK_MONOTONIC, &start);
        err = get_largest_word(str1, &word, delim);
        clock_gettime(CLOCK_MONOTONIC, &finish);

        if (err) {
            free(str1);
            printf("Error in func during stress test");
            return ERR_FUNC;
        }

        free((void *)word);

        double elapsed_1;
        elapsed_1 = (finish.tv_sec - start.tv_sec);
        elapsed_1 += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
        elapsed_1_finish += elapsed_1;

        free(str1);
    }

    elapsed_1_finish /= COUNT_MEASUREMENTS;

    double elapsed_2_finish = 0;

    for (int i = 0; i < COUNT_MEASUREMENTS; i++) {
        const char *word = NULL;
        char delim[] = " ;,\n.";
        char *str1 = strdup(str);

        if (!str1) {
            printf("Error mem during stress test");
            return ERR_MEM;
        }

        struct timespec start, finish;
        clock_gettime(CLOCK_MONOTONIC, &start);
        err = get_largest_word_thread(str1, &word, delim);
        clock_gettime(CLOCK_MONOTONIC, &finish);

        if (err) {
            free(str1);
            printf("Error in func during stress test");
            return ERR_FUNC;
        }

        free((void *)word);

        double elapsed_1;
        elapsed_1 = (finish.tv_sec - start.tv_sec);
        elapsed_1 += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
        elapsed_2_finish += elapsed_1;

        free(str1);
    }

    free(str);

    elapsed_2_finish /= COUNT_MEASUREMENTS;

    printf("Basic impl time - %lf\n", elapsed_1_finish);
    printf("Threads impl time - %lf\n", elapsed_2_finish);

    return 0;
}
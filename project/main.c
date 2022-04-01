#define _GNU_SOURCE

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dyn_largest_word.h"
#include "st_largest_word.h"

char *readFile(char *filename, int *err) {
    *err = 0;
    FILE *f = fopen(filename, "r");

    if (!f) {
        *err = 10;
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    
    char *str = malloc(size);

    if (str == NULL) {
        *err = 11;
    }

    if (!*err) {
        fseek(f, 0, SEEK_SET);
        fread(str, size, 1, f);
    }

    fclose(f);
    return str;
}

int main(int argc, char *argv[]) {
    int err = 0;
    char *str = readFile("project/tests/2.txt", &err);
    char *str1 = strdup(str);

    if (err) {
        free(str);
        free(str1);
        printf("Error");
        return 10;
    }

    const char *word = NULL;
    const char *word1 = NULL;

    char delim[] = " ;,\n.";
    struct timespec start, finish;
    clock_gettime(CLOCK_MONOTONIC, &start);
    get_largest_word(str, &word, delim);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    double elapsed_1;
    elapsed_1 = (finish.tv_sec - start.tv_sec);
    elapsed_1 += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    free(str);
    // printf("string %s", str1);
    clock_gettime(CLOCK_MONOTONIC, &start);
    get_largest_word_thread(str1, &word1, delim);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    free(str1);

    double elapsed_2;
    elapsed_2 = (finish.tv_sec - start.tv_sec);
    elapsed_2 += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Basic impl result - %s\nTime  - %lf\n", word, elapsed_1);
    printf("Threads impl result - %s\nTime - %lf\n", word1, elapsed_2);

    return 0;
}
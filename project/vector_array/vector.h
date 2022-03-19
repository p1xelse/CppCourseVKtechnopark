#ifndef PROJECT_VECTOR_ARRAY_VECTOR_H_
#define PROJECT_VECTOR_ARRAY_VECTOR_H_

#include <stdio.h>
#include <stdlib.h>

#define ERR_MEM 10
#define ERR_READ_ELEMENTS 11
#define ERR_EXTEND_SIZE 12
#define ERR_ZERO_BYTES_ALLOC 13

typedef struct {
    int *buffer;
    int size;
    int capacity;
} vector_t;

vector_t *vector_init();
int vector_push_back(vector_t *const vector, const int elem);
int vector_pop_back(vector_t *const vector);
void vector_free(vector_t *const vector);
int vector_read(vector_t *const vector, FILE *f);
int vector_extend(vector_t *const vector, const int extend_size);
void print_vector(vector_t *const vector);

#endif  // PROJECT_VECTOR_ARRAY_VECTOR_H_

#ifndef PROJECT_VECTOR_ARRAY_VECTOR_ARRAY_H_
#define PROJECT_VECTOR_ARRAY_VECTOR_ARRAY_H_

#include <stdio.h>

#include "vector.h"

#define ERR_READ_DIMENSION 5
#define ERR_NEG_DIMENSION 6
#define ERR_DIM_EQ_ZERO 7

int find_max_vector_size(vector_t **arr, const int len_arr);
vector_t **read_vector_array(FILE *f, const int len, int *err);
int read_array_len(FILE *f, int *const len);
void free_vector_array(vector_t **arr, const int count);
int align_vectors_len_in_arr(vector_t **arr, const int len);
void print_vector_arr(vector_t **arr, const int len);

#endif  // PROJECT_VECTOR_ARRAY_VECTOR_ARRAY_H_

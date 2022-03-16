#include "vector_array.h"

int find_max_vector_size(vector_t **arr, int len_arr) {
    int max_vector_size = arr[0]->size;

    for (int i = 1; i < len_arr; i++) {
        if (max_vector_size < arr[i]->size) max_vector_size = arr[i]->size;
    }

    return max_vector_size;
}

int read_array_len(FILE *f, int *len) {
    int err = 0;
    if (fscanf(f, "%d", len)) {
        err = *len < 0 ? ERR_NEG_DIMENSION : 0;
        err = *len == 0 ? ERR_DIM_EQ_ZERO : err;
    } else {
        err = ERR_READ_DIMENSION;
    }

    return err;
}

void free_vector_array(vector_t **arr, int count) {
    for (int i = 0; i < count; i++) {
        vector_free(arr[i]);
    }

    free(arr);
}

vector_t **read_vector_array(FILE *f, int len, int *err) {
    vector_t **out_arr = NULL;
    if (len * sizeof(vector_t *) != 0) {
        out_arr = malloc(len * sizeof(vector_t *));
    } else {
        *err = ERR_ZERO_BYTES_ALLOC;
        return NULL;
    }

    if (!out_arr) {
        *err = ERR_MEM;
        return NULL;
    }

    for (int i = 0; i < len && !*err; i++) {
        vector_t *new_vector = vector_init();

        if (new_vector) {
            *err = vector_read(new_vector, f);
        } else {
            *err = ERR_MEM;
            free_vector_array(out_arr, i);
            return NULL;
        }

        if (!*err) {
            out_arr[i] = new_vector;
        } else {
            vector_free(new_vector);
            free_vector_array(out_arr, i);
            out_arr = NULL;
        }
    }

    return out_arr;
}

void print_vector_arr(vector_t **arr, int len) {
    for (int i = 0; i < len; i++) {
        print_vector(arr[i]);
    }
}

int align_vectors_len_in_arr(vector_t **arr, int len) {
    int max = find_max_vector_size(arr, len);
    int err = 0;
    for (int i = 0; i < len && !err; i++) {
        err = vector_extend(arr[i], max);
    }

    return err;
}

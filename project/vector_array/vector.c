#include <stdio.h>
#include "vector.h"

#define DEFAULT_INIT_SIZE 10
#define STEP_CAPACITY_GROW 2

vector_t *vector_init()
{
    vector_t *vector = malloc(sizeof(vector_t));

    if (vector != NULL)
    {
        vector->buffer = NULL;
        vector->size = 0;
        vector->capacity = 0;
    }

    return vector;
}

static int vector_grow(vector_t *vector)
{
    int newBufferSize = vector->capacity > DEFAULT_INIT_SIZE * STEP_CAPACITY_GROW
                        ? vector->size
                        : DEFAULT_INIT_SIZE * STEP_CAPACITY_GROW;

    int *tmp_buff = realloc(vector->buffer, newBufferSize * sizeof(int));

    if (tmp_buff)
    {
        vector->buffer = tmp_buff;
        vector->capacity = newBufferSize;
    }
    else
        return ERR_MEM;

    return 0;
}

int vector_push_back(vector_t *vector, int elem)
{
    int err = 0;
    if (vector->size == vector->capacity)
        err = vector_grow(vector);

    if (!err)
        vector->buffer[vector->size++] = elem;

    return err;
}

int vector_read(vector_t *vector, FILE *f)
{
    int err = 0;

    int cur_number = 1;

    for (int i = 0; !err && cur_number; i++)
    {
        if (fscanf(f, "%d", &cur_number))
            err = vector_push_back(vector, cur_number);
        else
            err = ERR_READ_ELEMENTS;
    }

    return err;
}

void vector_free(vector_t *vector)
{
    free(vector->buffer);
    free(vector);
}

int vector_extend(vector_t *vector, int extend_size)
{
    int err = 0;
    if (extend_size < vector->size)
        err = ERR_EXTEND_SIZE;

    int origin_vector_size = vector->size;
    for (int i = 0; i < extend_size - origin_vector_size && !err; i++)
        err = vector_push_back(vector, 0);

    return err;
}

void print_vector(vector_t *vector)
{
    for (int i = 0; i < vector->size; i++)
    {
        printf("%d ", vector->buffer[i]);
    }

    printf("\n");
}

/*
Вариант #53
Составить программу выравнивания длин серии векторов по длине вектора наибольшей
длины. Выравнивание оформить в виде функции, принимающей на вход указатель на
массив указателей на векторы целых чисел и длину указанного массива и
заполняющей недостающие элементы нулевыми значениями. Конец каждого вектора
задан значением 0. На выход функция должна возвращать указатель на массив
указателей на векторы увеличенного размера.
*/

#include <stdio.h>

#include "vector_array.h"

#define PROMPT_STR                                          \
    "The program expands all vectors to the largest size\n" \
    "Enter the number of vectors.\n"                        \
    "Then the vectors themselves ending in zero.\n"         \
    "\n"                                                    \
    "Example:\n"                                            \
    "2\n"                                                   \
    "1 2 3 4 0\n"                                           \
    "1 3 0\n"                                               \
    "----START----\n"

void error_handler(int err) {
    switch (err) {
        case ERR_MEM:
            printf("ERROR: Memory allocated error\n");
            break;
        case ERR_READ_ELEMENTS:
            printf("ERROR: Error reading elements\n");
            break;
        case ERR_READ_DIMENSION:
            printf("ERROR: Error reading dimension\n");
            break;
        case ERR_NEG_DIMENSION:
            printf("ERROR: Negative dimension\n");
            break;
        case ERR_DIM_EQ_ZERO:
            printf(
                "ERROR: To solve the problem, you need at least one vector\n");
            break;
        case 0:
            printf("SUCCESS\n");
    }
}

void print_input_prompt() {
    printf(PROMPT_STR);
}

int main() {
    print_input_prompt();
    FILE *f = stdin;
    int len = 0;
    int err = read_array_len(f, &len);
    vector_t **arr = NULL;

    if (!err) arr = read_vector_array(f, len, &err);

    if (!err && arr != NULL) err = align_vectors_len_in_arr(arr, len);

    if (!err) {
        printf("Result:\n");
        print_vector_arr(arr, len);
        free_vector_array(arr, len);
    }

    error_handler(err);
}
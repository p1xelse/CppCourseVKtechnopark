#include <gtest/gtest.h>

extern "C" {
#include "words_arr.h"
}

void EXPECT_EQ_WORDS_ARR(words_arr_t *expected, words_arr_t *arr) {
    if (expected->len == arr->len) {
        for (int i = 0; i < expected->len; i++) {
            EXPECT_STREQ(arr->arr[i], expected->arr[i]);
        }
    }

    EXPECT_EQ(expected->len, arr->len);
}

TEST(getCountWords, testBasic) {
    char inputStr[] = "Hello world, I'm fine";
    char delim[] = " ";

    int count = get_count_words(inputStr, delim);
    EXPECT_EQ(4, count);
}

TEST(getCountWords, testManyDelimeters) {
    char inputStr[] = "Hello world; I:m, fine";
    char delim[] = ",;: ";

    int count = get_count_words(inputStr, delim);
    EXPECT_EQ(5, count);
}

TEST(getCountWords, testOneWord) {
    char inputStr[] = "Hello";
    char delim[] = " ";

    int count = get_count_words(inputStr, delim);
    EXPECT_EQ(1, count);
}

TEST(getCountWords, testEmptyStr) {
    char inputStr[] = "";
    char delim[] = " ";

    int count = get_count_words(inputStr, delim);
    EXPECT_EQ(0, count);
}

TEST(strSplit, testBasic) {
    const char *expect_words[] = {"Hello", "world", "Bay"};
    int expect_len = 3;
    words_arr_t expect_arr = {expect_words, expect_len};

    words_arr_t arr;
    int err = init_words_array(&arr);

    if (!err) {
        char inputStr[] = "Hello world Bay";
        char delim[] = " ";
        err = str_split(inputStr, delim, &arr);
    }

    if (0 != err) {
        EXPECT_EQ_WORDS_ARR(&arr, &expect_arr);
    }
    EXPECT_EQ(0, err);
    free_words_array(&arr);
}

TEST(strSplit, testOneWord) {
    const char *expect_words[] = {"Helloasdasdasdsadasdasd"};
    int expect_len = 1;
    words_arr_t expect_arr = {expect_words, expect_len};

    words_arr_t arr;
    int err = init_words_array(&arr);

    if (!err) {
        char inputStr[] = "Helloasdasdasdsadasdasd";
        char delim[] = " ";
        err = str_split(inputStr, delim, &arr);
    }

    if (0 != err) {
        EXPECT_EQ_WORDS_ARR(&arr, &expect_arr);
    }
    EXPECT_EQ(0, err);
    free_words_array(&arr);
}

TEST(strSplit, testEmptyStr) {
    words_arr_t arr;
    int err = init_words_array(&arr);
    if (!err) {
        char inputStr[] = "";
        char delim[] = " ";
        err = str_split(inputStr, delim, &arr);
    }
    free_words_array(&arr);
    EXPECT_NE(0, err);
}

TEST(findIndexLargestWord, testBasic) {
    const char *words[] = {"Hello", "world", "asdasdasdasdasdasdasdasdasdasd",
                           "asdada", "asdasdasdasdasdassda"};
    int expected_index = 2;

    int index =
        find_index_largest_word(words, sizeof(words) / sizeof(words[0]));

    EXPECT_EQ(index, expected_index);
}

TEST(findIndexLargestWord, testFirstIndex) {
    const char *words[] = {"Hello", "world", "Bay"};
    int expected_index = 0;

    int index =
        find_index_largest_word(words, sizeof(words) / sizeof(words[0]));

    EXPECT_EQ(index, expected_index);
}

TEST(findIndexLargestWord, testLastIndex) {
    const char *words[] = {"Hello", "world", "Bay", "asdada",
                           "asdasdasdasdasdassda"};
    int expected_index = sizeof(words) / sizeof(words[0]) - 1;

    int index =
        find_index_largest_word(words, sizeof(words) / sizeof(words[0]));

    EXPECT_EQ(index, expected_index);
}
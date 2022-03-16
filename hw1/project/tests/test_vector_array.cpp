#include <gtest/gtest.h>

#include <vector>

extern "C"
{
#include "vector_array.h"
#include <string.h>
#include <stdio.h>
}

TEST(ReadArrayLen, TestBasic)
{

    char input_str[] = "3 "
                       "7 5 16 0"
                       "1 2 3 4 5 0"
                       "1 2 0";

    FILE *f = fmemopen(input_str, strlen(input_str), "r");
    int len = 0;
    int err = read_array_len(f, &len);
    EXPECT_EQ(0, err);
    EXPECT_EQ(3, len);
    fclose(f);
}

TEST(ReadArrayLen, NegTestNegativeLen)
{

    char input_str[] = "-1 "
                       "7 5 16 0"
                       "1 2 3 4 5 0"
                       "1 2 0";

    FILE *f = fmemopen(input_str, strlen(input_str), "r");
    int len = 0;
    int err = read_array_len(f, &len);
    EXPECT_NE(0, err);
    fclose(f);
}

TEST(ReadArrayLen, NegTestZeroLen)
{
    char input_str[] = "0  "
                       "7 5 16 0"
                       "1 2 3 4 5 0"
                       "1 2 0";

    FILE *f = fmemopen(input_str, strlen(input_str), "r");
    int len = 0;
    int err = read_array_len(f, &len);
    EXPECT_NE(0, err);
    fclose(f);
}

TEST(ReadArrayLen, NegTestInvalidLen)
{

    char input_str[] = "a "
                       "7 5 16 0"
                       "1 2 3 4 5 0"
                       "1 2 0";

    FILE *f = fmemopen(input_str, strlen(input_str), "r");
    int len = 0;
    int err = read_array_len(f, &len);
    EXPECT_NE(0, err);
    fclose(f);
}

void ASSERT_EQ_VECTORS(vector_t *vector, std::vector<int> vector_stl, int len)
{
    for (int i = 0; i < len; i++)
    {
        ASSERT_EQ(vector->buffer[i], vector_stl[i]);
    }
}

TEST(ReadVectorArray, TestBasic)
{

    std::vector<int> expected_arr[3];
    expected_arr[0] = {7, 5, 16, 0};
    expected_arr[1] = {1, 2, 3, 4, 5, 0};
    expected_arr[2] = {1, 2, 0};

    char input_str[] = "3 "
                       "7 5 16 0 "
                       "1 2 3 4 5 0 "
                       "1 2 0 ";

    FILE *f = fmemopen(input_str, strlen(input_str), "r");

    int len = 0;
    int err = read_array_len(f, &len);

    ASSERT_EQ(0, err);
    ASSERT_EQ(3, len);

    vector_t **arr = read_vector_array(f, len, &err);

    ASSERT_EQ(err, 0);
    ASSERT_NE(arr, nullptr);

    for (size_t i = 0; i < len; i++)
    {
        ASSERT_EQ(expected_arr[i].size(), arr[i]->size);
        ASSERT_EQ_VECTORS(arr[i], expected_arr[i], arr[i]->size);
    }

    free_vector_array(arr, len);

    fclose(f);
}

TEST(ReadVectorArray, NegTestInvalidData)
{
    char input_str[] = "3 "
                       "a 5 16 0 "
                       "1 2 3 4 5 0 "
                       "1 2 0 ";

    FILE *f = fmemopen(input_str, strlen(input_str), "r");

    int len = 0;
    int err = read_array_len(f, &len);

    ASSERT_EQ(0, err);
    ASSERT_EQ(3, len);

    vector_t **arr = read_vector_array(f, len, &err);

    ASSERT_NE(err, 0);
    ASSERT_EQ(arr, nullptr);

    fclose(f);
}

TEST(AligVectors, TestBasic)
{
    std::vector<int> expected_arr[3];
    expected_arr[0] = {7, 5, 16, 0, 0, 0};
    expected_arr[1] = {1, 2, 3, 4, 5, 0};
    expected_arr[2] = {1, 2, 0, 0, 0, 0};

    char input_str[] = "3 "
                       "7 5 16 0 "
                       "1 2 3 4 5 0 "
                       "1 2 0 ";

    FILE *f = fmemopen(input_str, strlen(input_str), "r");

    int len = 0;
    int err = read_array_len(f, &len);

    ASSERT_EQ(0, err);
    ASSERT_EQ(3, len);

    vector_t **arr = read_vector_array(f, len, &err);

    ASSERT_EQ(err, 0);
    ASSERT_NE(arr, nullptr);

    err = align_vectors_len_in_arr(arr, len);

    ASSERT_EQ(err, 0);

    for (size_t i = 0; i < len; i++)
    {
        ASSERT_EQ(expected_arr[i].size(), arr[i]->size);
        ASSERT_EQ_VECTORS(arr[i], expected_arr[i], arr[i]->size);
    }
    free_vector_array(arr, len);
    fclose(f);
}

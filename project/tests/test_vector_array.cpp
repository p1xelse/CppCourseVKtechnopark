#include <gtest/gtest.h>

#include <vector>

extern "C"
{
#include "vector_array.h"
#include <string.h>
#include <stdio.h>
}

TEST(readArrayLen, testBasic)
{

    char inputStr[] = "3 "
                       "7 5 16 0"
                       "1 2 3 4 5 0"
                       "1 2 0";

    FILE *f = fmemopen(inputStr, strlen(inputStr), "r");
    int len = 0;
    int err = read_array_len(f, &len);
    EXPECT_EQ(0, err);
    EXPECT_EQ(3, len);
    fclose(f);
}

TEST(readArrayLen, negTestNegativeLen)
{

    char inputStr[] = "-1 "
                       "7 5 16 0"
                       "1 2 3 4 5 0"
                       "1 2 0";

    FILE *f = fmemopen(inputStr, strlen(inputStr), "r");
    int len = 0;
    int err = read_array_len(f, &len);
    EXPECT_NE(0, err);
    fclose(f);
}

TEST(readArrayLen, negTestZeroLen)
{
    char inputStr[] = "0  "
                       "7 5 16 0"
                       "1 2 3 4 5 0"
                       "1 2 0";

    FILE *f = fmemopen(inputStr, strlen(inputStr), "r");
    int len = 0;
    int err = read_array_len(f, &len);
    EXPECT_NE(0, err);
    fclose(f);
}

TEST(readArrayLen, negTestInvalidLen)
{

    char inputStr[] = "a "
                       "7 5 16 0"
                       "1 2 3 4 5 0"
                       "1 2 0";

    FILE *f = fmemopen(inputStr, strlen(inputStr), "r");
    int len = 0;
    int err = read_array_len(f, &len);
    EXPECT_NE(0, err);
    fclose(f);
}

void ASSERT_EQ_VECTORS(vector_t *vector, std::vector<int> vectorStl, int len)
{
    for (int i = 0; i < len; i++)
    {
        ASSERT_EQ(vector->buffer[i], vectorStl[i]);
    }
}

TEST(readVectorArray, testBasic)
{
    std::vector<int> expectedArr[3];
    expectedArr[0] = {7, 5, 16, 0};
    expectedArr[1] = {1, 2, 3, 4, 5, 0};
    expectedArr[2] = {1, 2, 0};

    char inputStr[] = "3 "
                       "7 5 16 0 "
                       "1 2 3 4 5 0 "
                       "1 2 0 ";

    FILE *f = fmemopen(inputStr, strlen(inputStr), "r");

    int len = 0;
    int err = read_array_len(f, &len);

    ASSERT_EQ(0, err);
    ASSERT_EQ(3, len);

    vector_t **arr = read_vector_array(f, len, &err);

    ASSERT_EQ(err, 0);
    ASSERT_NE(arr, nullptr);

    for (size_t i = 0; i < len; i++)
    {
        ASSERT_EQ(expectedArr[i].size(), arr[i]->size);
        ASSERT_EQ_VECTORS(arr[i], expectedArr[i], arr[i]->size);
    }

    free_vector_array(arr, len);

    fclose(f);
}

TEST(readVectorArray, negTestInvalidData)
{
    char inputStr[] = "3 "
                       "a 5 16 0 "
                       "1 2 3 4 5 0 "
                       "1 2 0 ";

    FILE *f = fmemopen(inputStr, strlen(inputStr), "r");

    int len = 0;
    int err = read_array_len(f, &len);

    ASSERT_EQ(0, err);
    ASSERT_EQ(3, len);

    vector_t **arr = read_vector_array(f, len, &err);

    ASSERT_NE(err, 0);
    ASSERT_EQ(arr, nullptr);

    fclose(f);
}

TEST(aligVectors, testBasic)
{
    std::vector<int> expectedArr[3];
    expectedArr[0] = {7, 5, 16, 0, 0, 0};
    expectedArr[1] = {1, 2, 3, 4, 5, 0};
    expectedArr[2] = {1, 2, 0, 0, 0, 0};

    char inputStr[] = "3 "
                       "7 5 16 0 "
                       "1 2 3 4 5 0 "
                       "1 2 0 ";

    FILE *f = fmemopen(inputStr, strlen(inputStr), "r");

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
        ASSERT_EQ(expectedArr[i].size(), arr[i]->size);
        ASSERT_EQ_VECTORS(arr[i], expectedArr[i], arr[i]->size);
    }
    free_vector_array(arr, len);
    fclose(f);
}

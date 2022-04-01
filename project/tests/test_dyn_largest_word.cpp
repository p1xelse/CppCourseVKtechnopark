#include <gtest/gtest.h>

#include <fstream>

extern "C" {
#include "dyn_largest_word.h"
}

char *readFile(const std::string &fileName, int *err) {
    *err = 0;
    std::ifstream f(fileName);
    if (!f) {
        *err = 10;
        return NULL;
    }

    f.seekg(0, std::ios::end);
    size_t size = f.tellg();
    char *str = new char[size + 1];

    if (str == NULL) {
        *err = 11;
        return NULL;
    }

    f.seekg(0);
    f.read(str, size);
    str[size] = '\0';

    return str;
}

TEST(get_largest_word_thread, testBasic) {
    char *inputStr = strdup("Hello worldsssss I'm fine");
    ASSERT_TRUE(inputStr != NULL) << "Error memory allocate during test";
    char delim[] = " ";
    const char *word = NULL;
    int err = get_largest_word_thread(inputStr, &word, delim);
    if (0 == err) {
        const char *expectedWord = "worldsssss";
        EXPECT_STREQ(word, expectedWord);
    }
    free((void *)word);
    free(inputStr);
    ASSERT_EQ(0, err);
}

TEST(get_largest_word_thread, testOneWord) {
    char *inputStr = strdup("Hello");
    ASSERT_TRUE(inputStr != NULL) << "Error memory allocate during test";
    char delim[] = " ";
    const char *word = NULL;
    int err = get_largest_word_thread(inputStr, &word, delim);
    if (0 == err) {
        const char *expectedWord = "Hello";
        EXPECT_STREQ(word, expectedWord);
    }
    free((void *)word);
    free(inputStr);
    ASSERT_EQ(0, err);
}

TEST(get_largest_word_thread, testTwoEqWords) {
    char *inputStr = strdup("first_word first_word adas asd a sdfa");
    ASSERT_TRUE(inputStr != NULL) << "Error memory allocate during test";
    char delim[] = " ";
    const char *word = NULL;
    int err = get_largest_word_thread(inputStr, &word, delim);
    if (0 == err) {
        const char *expectedWord = "first_word";
        EXPECT_STREQ(word, expectedWord);
    }
    free((void *)word);
    free(inputStr);
    ASSERT_EQ(0, err);
}

TEST(get_largest_word_thread, negTestEmptyStr) {
    char *inputStr = strdup("");
    ASSERT_TRUE(inputStr != NULL) << "Error memory allocate during test";
    char delim[] = " ";
    const char *word = NULL;
    int err = get_largest_word_thread(inputStr, &word, delim);
    free((void *)word);
    free(inputStr);
    ASSERT_NE(0, err);
}

TEST(get_largest_word_thread, negTestNullStr) {
    char *inputStr = NULL;
    char delim[] = " ";
    const char *word = NULL;
    int err = get_largest_word_thread(inputStr, &word, delim);
    free((void *)word);
    ASSERT_NE(0, err);
}

TEST(get_largest_word_thread, negTestNullDelim) {
    char *inputStr = strdup("first_word first_word adas asd a sdfa");
    ASSERT_TRUE(inputStr != NULL) << "Error memory allocate during test";
    char *delim = NULL;
    const char *word = NULL;
    int err = get_largest_word_thread(inputStr, &word, delim);
    free(inputStr);
    free((void *)word);
    ASSERT_NE(0, err);
}

TEST(get_largest_word_thread, stressTest) {
    int err = 0;
    char *str = readFile(std::string("project/tests/1.txt"), &err);
    ASSERT_EQ(err, 0);

    char delim[] = " ;,\n.";
    const char *word = NULL;
    err = get_largest_word_thread(str, &word, delim);
    if (0 == err) {
        const char *expectedWord =
            "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";
        EXPECT_STREQ(word, expectedWord);
    }
    free((void *)word);
    delete[] str;
    ASSERT_EQ(0, err);
}

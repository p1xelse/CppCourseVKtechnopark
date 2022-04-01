#include <gtest/gtest.h>

#include <fstream>

extern "C" {
#include "st_largest_word.h"
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

TEST(get_largest_word, testBasic) {
    char inputStr[] = "Hello worldsssss I'm fine";
    char delim[] = " ";
    const char *word = NULL;
    int err = get_largest_word(inputStr, &word, delim);
    if (0 == err) {
        const char *expectedWord = "worldsssss";
        EXPECT_STREQ(word, expectedWord);
    }
    free((void *)word);
    ASSERT_EQ(0, err);
}

TEST(get_largest_word, testOneWord) {
    char inputStr[] = "Hello";
    char delim[] = " ";
    const char *word = NULL;
    int err = get_largest_word(inputStr, &word, delim);
    if (0 == err) {
        const char *expectedWord = "Hello";
        EXPECT_STREQ(word, expectedWord);
    }
    free((void *)word);
    ASSERT_EQ(0, err);
}

TEST(get_largest_word, testTwoEqWords) {
    char inputStr[] = "first_word first_word adas asd a sdfa";
    char delim[] = " ";
    const char *word = NULL;
    int err = get_largest_word(inputStr, &word, delim);
    if (0 == err) {
        const char *expectedWord = "first_word";
        EXPECT_STREQ(word, expectedWord);
    }
    free((void *)word);
    ASSERT_EQ(0, err);
}

TEST(get_largest_word, negTestEmptyStr) {
    char inputStr[] = "";
    char delim[] = " ";
    const char *word = NULL;
    int err = get_largest_word(inputStr, &word, delim);
    free((void *)word);
    ASSERT_NE(0, err);
}

TEST(get_largest_word, negTestNullStr) {
    char *inputStr = NULL;
    char delim[] = " ";
    const char *word = NULL;
    int err = get_largest_word(inputStr, &word, delim);
    free((void *)word);
    ASSERT_NE(0, err);
}

TEST(get_largest_word, negTestNullDelim) {
    char inputStr[] = "first_word first_word adas asd a sdfa";
    char *delim = NULL;
    const char *word = NULL;
    int err = get_largest_word(inputStr, &word, delim);
    free((void *)word);
    ASSERT_NE(0, err);
}

TEST(get_largest_word, stressTest) {
    int err = 0;
    char *str = readFile(std::string("project/tests/1.txt"), &err);
    ASSERT_EQ(err, 0);

    char delim[] = " ;,\n.";
    const char *word = NULL;
    err = get_largest_word(str, &word, delim);
    if (0 == err) {
        const char *expectedWord =
            "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";
        EXPECT_STREQ(word, expectedWord);
    }
    delete[] str;
    free((void *)word);
    ASSERT_EQ(0, err);
}

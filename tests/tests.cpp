#define _CRT_SECURE_NO_WARNINGS
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 1000

// для ex1
int Test_isUpperCaseWord(char arr[], int start, int end) {
    for (int i = start; i <= end; i++) {
        if (!isupper(arr[i])) return 0;
    }
    return 1;
}

void Test_replaceWithXO(char arr[], int start, int end) {
    int length = end - start + 1;
    for (int i = start; i <= end; i++) {
        if ((i - start) % 2 == 0) arr[i] = 'X';
        else arr[i] = 'O';
    }
}

void Test_processStringArray(char arr[], int length) {
    int start = -1;
    for (int i = 0; i <= length; i++) {
        if (i < length && isalpha(arr[i])) {
            if (start == -1) start = i;
        }
        else {
            if (start != -1) {
                int end = i - 1;
                if (Test_isUpperCaseWord(arr, start, end)) {
                    Test_replaceWithXO(arr, start, end);
                }
                start = -1;
            }
        }
    }
}

// Для ex2
int Test_isUpperCaseWordCString(const char* str, int start, int end) {
    for (int i = start; i <= end; i++) {
        if (!isupper(str[i])) return 0;
    }
    return 1;
}

void Test_replaceWithXOCString(char* str, int start, int end) {
    int length = end - start + 1;
    for (int i = start; i <= end; i++) {
        if ((i - start) % 2 == 0) str[i] = 'X';
        else str[i] = 'O';
    }
}

void Test_processCString(char* str) {
    int length = (int)strlen(str);
    int start = -1;
    for (int i = 0; i <= length; i++) {
        if (i < length && isalpha(str[i])) {
            if (start == -1) start = i;
        }
        else {
            if (start != -1) {
                int end = i - 1;
                if (Test_isUpperCaseWordCString(str, start, end)) {
                    Test_replaceWithXOCString(str, start, end);
                }
                start = -1;
            }
        }
    }
}

// Дл ex3
int Test_processFile(const char* inputFilename, const char* outputFilename) {
    FILE* inputFile, * outputFile;
    char str[MAX_LENGTH];
    int length = 0;
    char ch;

    inputFile = fopen(inputFilename, "r");
    if (inputFile == NULL) return -1;

    while ((ch = fgetc(inputFile)) != EOF && ch != '\n' && length < MAX_LENGTH - 1) {
        str[length++] = ch;
    }
    fclose(inputFile);

    Test_processStringArray(str, length);

    outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) return -2;

    for (int i = 0; i < length; i++) fputc(str[i], outputFile);
    fclose(outputFile);
    return 0;
}

// Тесты
TEST(Ex1Tests, AllUpperCaseWordReplacement) {
    char str[] = "HELLO world";
    int length = 11;

    Test_processStringArray(str, length);

    EXPECT_EQ(str[0], 'X');
    EXPECT_EQ(str[1], 'O');
    EXPECT_EQ(str[2], 'X');
    EXPECT_EQ(str[3], 'O');
    EXPECT_EQ(str[4], 'X');
    EXPECT_EQ(str[5], ' ');
    EXPECT_EQ(str[6], 'w');
}

TEST(Ex1Tests, MixedCaseWords) {
    char str[] = "TEST Mixed CASE";
    int length = 14;

    Test_processStringArray(str, length);

    EXPECT_EQ(str[0], 'X');
    EXPECT_EQ(str[1], 'O');
    EXPECT_EQ(str[2], 'X');
    EXPECT_EQ(str[3], 'O');
    EXPECT_EQ(str[5], 'M');
    EXPECT_EQ(str[11], 'C');
}

TEST(Ex1Tests, NoUpperCaseWords) {
    char str[] = "hello world test";
    int length = 16;

    Test_processStringArray(str, length);

    EXPECT_EQ(str[0], 'h');
    EXPECT_EQ(str[6], 'w');
    EXPECT_EQ(str[12], 't');
}

TEST(Ex2Tests, CStringReplacement) {
    char str[] = "HELLO WORLD";
    Test_processCString(str);

    EXPECT_EQ(str[0], 'X');
    EXPECT_EQ(str[1], 'O');
    EXPECT_EQ(str[2], 'X');
    EXPECT_EQ(str[3], 'O');
    EXPECT_EQ(str[4], 'X');
    EXPECT_EQ(str[5], ' ');
    EXPECT_EQ(str[6], 'W');
}

TEST(Ex2Tests, CStringEmpty) {
    char str[] = "";
    Test_processCString(str);
    EXPECT_EQ(str[0], '\0');
}

TEST(Ex2Tests, CStringSpecialChars) {
    char str[] = "ABC!DEF@GHI";
    Test_processCString(str);

    EXPECT_EQ(str[0], 'X');
    EXPECT_EQ(str[1], 'O');
    EXPECT_EQ(str[2], 'X');
    EXPECT_EQ(str[8], 'X');
    EXPECT_EQ(str[9], 'O');
    EXPECT_EQ(str[10], 'X');
}

TEST(Ex3Tests, FileProcessingSuccess) {
    const char* inputFilename = "test_input.txt";
    const char* outputFilename = "test_output.txt";

    std::ofstream inputFile(inputFilename);
    inputFile << "HELLO world TEST";
    inputFile.close();

    int result = Test_processFile(inputFilename, outputFilename);
    EXPECT_EQ(result, 0);

    std::ifstream outputFile(outputFilename);
    std::string content;
    std::getline(outputFile, content);
    outputFile.close();

    EXPECT_EQ(content, "XOXOX world XOXO");

    std::remove(inputFilename);
    std::remove(outputFilename);
}

TEST(Ex3Tests, FileNotFound) {
    const char* inputFilename = "nonexistent.txt";
    const char* outputFilename = "output.txt";

    int result = Test_processFile(inputFilename, outputFilename);
    EXPECT_EQ(result, -1);
}

TEST(Ex3Tests, EmptyFile) {
    const char* inputFilename = "empty_input.txt";
    const char* outputFilename = "empty_output.txt";

    std::ofstream inputFile(inputFilename);
    inputFile.close();

    int result = Test_processFile(inputFilename, outputFilename);
    EXPECT_EQ(result, 0);

    std::ifstream outputFile(outputFilename);
    EXPECT_TRUE(outputFile.peek() == std::ifstream::traits_type::eof());
    outputFile.close();

    std::remove(inputFilename);
    std::remove(outputFilename);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
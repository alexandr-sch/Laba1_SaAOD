#define _CRT_SECURE_NO_WARNINGS
#include "ex3.h"
#include <stdio.h>
#include <ctype.h>

int isUpperCaseWordFile(char arr[], int start, int end) {
    for (int i = start; i <= end; i++) {
        if (!isupper(arr[i])) {
            return 0;
        }
    }
    return 1;
}

void replaceWithXOFile(char arr[], int start, int end) {
    int length = end - start + 1;
    for (int i = start; i <= end; i++) {
        if ((i - start) % 2 == 0) {
            arr[i] = 'X';
        }
        else {
            arr[i] = 'O';
        }
    }
}

void processStringArrayFile(char arr[], int length) {
    int start = -1;

    for (int i = 0; i <= length; i++) {
        if (i < length && isalpha(arr[i])) {
            if (start == -1) {
                start = i;
            }
        }
        else {
            if (start != -1) {
                int end = i - 1;
                if (isUpperCaseWordFile(arr, start, end)) {
                    replaceWithXOFile(arr, start, end);
                }
                start = -1;
            }
        }
    }
}


int processFile(const char* inputFilename, const char* outputFilename) {
    FILE* inputFile, * outputFile;
    char str[MAX_LENGTH];
    int length = 0;
    char ch;

    inputFile = fopen(inputFilename, "r");
    if (inputFile == NULL) {
        return -1;
    }

    while ((ch = fgetc(inputFile)) != EOF && ch != '\n' && length < MAX_LENGTH - 1) {
        str[length++] = ch;
    }
    fclose(inputFile);

    processStringArrayFile(str, length);

    outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        return -2; 
    }

    for (int i = 0; i < length; i++) {
        fputc(str[i], outputFile);
    }
    fclose(outputFile);

    return 0; 
}

int main() {
    FILE* inputFile, * outputFile;
    char inputFilename[100], outputFilename[100];
    char str[MAX_LENGTH];
    int length = 0;
    char ch;

    printf("Vvedite imya vhodnogo faila: ");
    scanf("%s", inputFilename);
    printf("Vvedite imya vyhodnogo faila: ");
    scanf("%s", outputFilename);

    inputFile = fopen(inputFilename, "r");
    if (inputFile == NULL) {
        printf("Oshibka: ne udalos otkryt fail %s\n", inputFilename);
        return 1;
    }

    while ((ch = fgetc(inputFile)) != EOF && ch != '\n' && length < MAX_LENGTH - 1) {
        str[length++] = ch;
    }
    fclose(inputFile);

    printf("Ishodnaya stroka: ");
    for (int i = 0; i < length; i++) {
        printf("%c", str[i]);
    }
    printf("\n");

    processStringArrayFile(str, length);

    printf("Obrabotannaya stroka: ");
    for (int i = 0; i < length; i++) {
        printf("%c", str[i]);
    }
    printf("\n");

    outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        printf("Oshibka: ne udalos sozdat fail %s\n", outputFilename);
        return 1;
    }

    for (int i = 0; i < length; i++) {
        fputc(str[i], outputFile);
    }
    fclose(outputFile);

    printf("Rezultat zapisan v fail: %s\n", outputFilename);
    return 0;
}













/*Лабораторная работа №1

Тема: Обработка строки символов различными способами хранения

Цель: Изучить различные способы хранения и обработки строк символов в языке C/C++. Овладеть навыками работы с массивами символов, строками Cи, а также обработки данных, хранящихся в файле.

Задание: Написать три программы для обработки строки символов в соответствии с индивидуальным заданием (выдается на л/р), используя следующие способы хранения:
1. Строка как массив символов.
- Строка хранится в виде одномерного массива символов (char[]).
- Выполните обработку строки, используя только исходный массив. Дополнительные массивы вводить нельзя.
2. Строка как строка в стиле языка Си (строка, завершающаяся символом '\0').
- Строка хранится в виде Cи-строки, которая завершается нулевым символом ('\0').
- Выполните обработку строки, не используя дополнительных массивов.
3. Строка хранится в файле.
- Строка записана в файл 1.
- Программа должна считать строку из файла, обработать ее по первому или второму варианту, и записать результат в файл 2.
- Использование дополнительных массивов запрещено.

Требования к выполнению задания:
- Все операции производить исключительно с исходным массивом или строкой.
- В каждой программе предусмотреть ввод строки пользователем (для вариантов 1 и 2), либо чтение строки из файла (для варианта 3).
- После выполнения обработки в варианте 3 результат должен быть записан в файл.

Ожидаемые результаты:
- В результате выполнения работы должны быть созданы три программы, демонстрирующие разные способы работы со строками символов.
- В третьем варианте должна быть реализована работа с файлами на уровне ввода/вывода данных.

Дополнительные указания:
- Для чтения и записи файлов используйте стандартные функции языка C/C++ (fopen(), fgets(), fputs(), fclose()).
- Обработку строки выберите сами (например, инвертирование строки, удаление определенных символов, замена символов и т.д.).

Критерии оценки:
- Корректность выполнения каждой из программ.
- Отсутствие использования дополнительных массивов для обработки строки.
- Соответствие структуры программы стандартам написания на языке C/C++.

Решение Л/Р загружаете на GitHub (не забудьте добавить .gitignore файл, чтобы избежать загрузки ненужных файлов).

Задание:
Найти все слова, состоящие только из заглавных букв, и заменить их на последовательность из «X» и «O» (по количеству букв в слове).*/
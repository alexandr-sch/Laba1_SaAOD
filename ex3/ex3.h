#pragma once
#ifndef EX3_H
#define EX3_H

#define MAX_LENGTH 1000

int isUpperCaseWordFile(char arr[], int start, int end);
void replaceWithXOFile(char arr[], int start, int end);
void processStringArrayFile(char arr[], int length);
int processFile(const char* inputFilename, const char* outputFilename);

#endif

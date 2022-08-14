#pragma once
#include <stdio.h>
#include <fstream>
#include <filesystem>

#define GREEN 2
#define RED 4
#define LIGHTCYAN 11
#define YELLOW 14
#define WHITE 15

/** Lamo xd kms pretty colors */
#define LOGSUCCESS(format, ...) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN), printf(format, __VA_ARGS__), SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
#define LOGFAIL(format, ...) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED), printf(format, __VA_ARGS__), SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
#define LOGINFO(format, ...) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTCYAN), printf(format, __VA_ARGS__), SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

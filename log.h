#pragma once

#define GREEN 2
#define RED 4
#define YELLOW 14
#define WHITE 15

#define LogSuccess(format, ...) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN), printf(format, __VA_ARGS__), SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
#define LogError(format, ...) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED), printf(format, __VA_ARGS__), SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
#define Log(format, ...) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW), printf(format, __VA_ARGS__), SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

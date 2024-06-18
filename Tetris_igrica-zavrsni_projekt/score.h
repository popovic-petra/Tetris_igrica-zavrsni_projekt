#pragma once

#define MAX_USERNAME_LENGTH 100
#define MAX_PLAYERS 100

typedef struct user{
    char username[MAX_USERNAME_LENGTH];
    int score;
}USER;

void enterUsername(USER* user);
USER* allocateUser();
void freeUser(USER* user);
void removeNewline(char* str);

void createAndRenameFiles(const char* prompt);
void cleanupFiles(const char* prompt);

void saveScore(const USER* user, const char* prompt);
int loadScore(USER scores[], const int maxUsers, const char* prompt);

int compareAsc(const void* a, const void* b);
int compareDesc(const void* a, const void* b);
static int partition(USER* users, int low, int high, int (*compare)(const void*, const void*));
void quickSort(USER* users, int low, int high, int (*compare)(const void*, const void*));
int compareUsernames(const void* a, const void* b);

void deleteHighscores(const char* prompt);
char doubleCheck();

void displayRules(const char* prompt);
int sizeOfFile(const char* prompt);
void setConsoleSize(int width, int height);
#pragma once

#define MAX_USERNAME_LENGTH 100
#define MAX_PLAYERS 100

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    int score;
}USER;

void enterUsername(USER* user);
USER* allocateUser();
void freeUser(USER* user);
static void removeNewline(char* str);

void saveScore(const USER* user);
void loadScores(USER** users, int* count);
static void saveScoresToFile(const USER* users, int count);
static void handleFileError(FILE* file);

static void sortUsersDesc(USER* users, int count);
static void sortUsersAsc(USER* users, int count);
static int compareAsc(const void* a, const void* b);
static int compareDesc(const void* a, const void* b);
void displayScoresAscending();
void displayScoresDescending();

void getInputUsername(char* username, int size);
int searchUser(const USER* users, int count, const char* username);
int compareUsernames(const void* a, const void* b);
void searchUsername(const USER* users, int count, const char* username);

void deleteHighscores();


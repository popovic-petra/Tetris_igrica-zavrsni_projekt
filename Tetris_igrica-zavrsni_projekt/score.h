#pragma once

#define MAX_USERNAME_LENGTH 100

typedef struct user {
    char username[MAX_USERNAME_LENGTH];
    int score;
}USER;

static int compareAsc(const void* a, const void* b);
static int compareDesc(const void* a, const void* b);
void displayScoresAscending();
void displayScoresDescending();
void deleteHighscores();
void searchHighscores();

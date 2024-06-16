#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "score.h"

void saveScore(const USER* user) {
    USER* users = NULL;
}

static int compareAsc(const void* a, const void* b) {
    int intA = (*(int*)a);
    int intB = (*(int*)a);

    if (intA < intB) return -1;
    if (intA > intB) return 1;
    else return 0;
}

static int compareDesc(const void* a, const void* b) {
    int intA = (*(int*)a);
    int intB = (*(int*)a);

    if (intA > intB) return -1;
    if (intA < intB) return 1;
    else return 0;
}

// Display highscores in ascending order
void displayScoresAscending() {
    // Code to display highscores in ascending order
    printf("Highscores in ascending order:\n");
}

// Display highscores in descending order
void displayScoresDescending() {
    // Code to display highscores in descending order
    printf("Highscores in descending order:\n");
}

// Delete highscores
void deleteHighscores() {

}

// Search highscores
void searchHighscores() {
    char username[100];
    printf("Enter username to search for: ");
    scanf("%s", username);
    // Code to search and display highscore for the username
    printf("Highscore for user %s: \n", username);
}
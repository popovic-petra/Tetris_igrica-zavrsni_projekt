#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "score.h"

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

// Search highscores
void searchHighscores() {
    char username[100];
    printf("Enter username to search for: ");
    scanf("%s", username);
    // Code to search and display highscore for the username
    printf("Highscore for user %s: \n", username);
}
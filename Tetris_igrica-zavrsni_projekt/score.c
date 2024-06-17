#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "score.h"

USER* allocateUser() {
    USER* user = (USER*)calloc(1, sizeof(USER));
    if (user == NULL) {
        fprintf(stderr, "Error allocating memory\n");
        exit(EXIT_FAILURE);
    }
    return user;
}

void freeUser(USER* user) {
    free(user);
}

void enterUsername(USER* user) {
    getchar();
    printf("Enter username\n>>> ");
    if (fgets(user->username, MAX_USERNAME_LENGTH, stdin) == NULL) {
        printf("Failed to read username\n");
        exit(EXIT_FAILURE);
    }

    removeNewline(user->username);
}

void removeNewline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void saveScore(const USER* user) {
    FILE* file = fopen("scores.txt", "a"); // Otvara datoteku u režimu dodatka
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s\t\t%d\n", user->username, user->score);
    fclose(file);
}

int loadScore(USER scores[], int maxUsers) {
    FILE* fp = fopen("scores.txt", "r");
    if (fp == NULL) {
        perror("Error opening file for reading\n");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    while (count < maxUsers && fscanf(fp, "%s\t\t%d\n", scores[count].username, &scores[count].score) == 2) {
        count++;    
    }

    fclose(fp);
    return count;
}

int compareDesc(const void* a, const void* b) {
    const USER* scoreA = (const USER*)a;
    const USER* scoreB = (const USER*)b;

    if (scoreA->score > scoreB->score) return -1;
    if (scoreA->score < scoreB->score) return 1;
    return 0;
}

int compareAsc(const void* a, const void* b) {
    const USER* scoreA = (const USER*)a;
    const USER* scoreB = (const USER*)b;

    if (scoreA->score < scoreB->score) return -1;
    if (scoreA->score > scoreB->score) return 1;
    return 0;
}

int compareUsernames(const void* a, const void* b) {
    return strcmp(((USER*)a)->username, ((USER*)b)->username);
}

void deleteHighscores() {
    FILE* file = fopen("scores.txt", "w");
    if (file) {
        fclose(file);
    }
    else {
        perror("Error opening file");
    }
}

char doubleCheck() {
    char check;
    printf("Do you really want to delete ALL saved usernames\nand highscores (y/n) ?\n>>> ");
    scanf(" %c", &check);       // Reads one char
    while (getchar() != '\n');  // Removes \n
    return check;
}
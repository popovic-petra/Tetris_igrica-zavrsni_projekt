#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "score.h"

USER* allocateUser() {
    USER* user = (USER*)malloc(sizeof(USER));
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
    
    system("cls");
    getchar();

    printf("Enter username\n>>> ");
    if (fgets(user->username, MAX_USERNAME_LENGTH, stdin) == NULL) {
        printf("Failed to read username\n");
        exit(EXIT_FAILURE);
    }
    
    removeNewline(user->username);
}

static void removeNewline(char* str) {
    char len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}


void saveScore(const USER* user) {
    USER* users = NULL;
    int count = 0;
    loadScores(&users, &count);

    int index = searchUser(users, count, user->username);
    if (index == -1) {
        // New user
        users = realloc(users, (count + 1) * sizeof(USER));
        if (!users) {
            perror("Failed to allocate memory");
            exit(1);
        }
        users[count] = *user;
        count++;
    }
    else {
        // Update existing user's score if it's higher
        if (users[index].score < user->score) {
            users[index].score = user->score;
        }
    }

    saveScoresToFile(users, count);
    free(users);
    users = NULL;
}

void loadScores(USER** users, int* count) {
    FILE* file = fopen("scores.txt", "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    *users = NULL; // Initialize to NULL to handle realloc properly
    *count = 0;

    while (1) {
        USER* temp = realloc(*users, (*count + 1) * sizeof(USER));
        if (!temp) {
            perror("Failed to allocate memory");
            free(*users); // Free previously allocated memory before exiting
            exit(1);
        }
        *users = temp;

        if (fscanf(file, "%10s %d", (*users)[*count].username, &(*users)[*count].score) != 2) {
            break; // Break if fscanf does not return 2 (EOF or read error)
        }
        (*count)++;
    }

    handleFileError(file);
    fclose(file);
}

static void saveScoresToFile(const USER* users, int count) {
    FILE* file = fopen("scores.txt", "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d\n", users[i].username, users[i].score);
    }

    handleFileError(file);
    fclose(file);
}

static void handleFileError(FILE* file) {
    if (ferror(file)) {
        perror("Error reading/writing file");
        clearerr(file);
    }
}

/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/

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

static void sortUsersDesc(USER* users, int count) {
    qsort(users, count, sizeof(USER), compareDesc);
}

static void sortUsersAsc(USER* users, int count) {
    qsort(users, count, sizeof(USER), compareAsc);
}

// Display highscores in ascending order
void displayScoresAscending() {
    USER* users = NULL;
    int count = 0;
    loadScores(&users, &count);
    sortUsersAsc(users, count);

    printf("Username       Score\n");
    printf("---------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-10s %10d\n", users[i].username, users[i].score);
    }

    free(users);
}

// Display highscores in descending order
void displayScoresDescending() {
    USER* users = NULL;
    int count = 0;
    loadScores(&users, &count);
    sortUsersDesc(users, count);

    printf("Username       Score\n");
    printf("---------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-10s %10d\n", users[i].username, users[i].score);
    }

    free(users);
}

/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/

// Search highscores

void getInputUsername(char* username, int size) {
    printf("Enter the username to search\n>>> ");
    scanf("%101s", username);
}

int searchUser(const USER* users, int count, const char* username) {
    USER key;
    strncpy(key.username, username, 10);
    key.username[10] = '\0';
    USER* found = bsearch(&key, users, count, sizeof(USER), compareUsernames);
    if (found) {
        return found - users;
    }
    return -1;
}

int compareUsernames(const void* a, const void* b) {
    USER* userA = (USER*)a;
    USER* userB = (USER*)b;
    return strcmp(userA->username, userB->username);
}

void searchUsername(const USER* users, int count, const char* username) {
    int index = searchUser(users, count, username);
    if (index != -1) {
        printf("Username: %s, Score: %d\n", users[index].username, users[index].score);
    }
    else {
        printf("Username %s not found.\n", username);
    }
}

/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/


// Delete highscores
void deleteHighscores() {

}
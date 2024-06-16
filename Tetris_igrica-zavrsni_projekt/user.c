#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "tetris.h"

void initPlayerManager(USER_MANAGER* um) {
    um->numPlayers = 0;
}

void addUser(USER_MANAGER* um) {
    if (um->numPlayers >= MAX_PLAYERS) {
        printf("Maximum number of players reached. Unable to add new user.\n");
        return;
    }

    // Add user to the system
    printf("Enter new username (up to %d characters)\n>>>", MAX_USERNAME_LENGTH - 1);
    fgets(um->players[um->numPlayers].username, MAX_USERNAME_LENGTH, stdin);

    // Remove newline character from the username
    um->players[um->numPlayers].username[strcspn(um->players[um->numPlayers].username, "\n")] = '\0';

    // Initialize user's score to 0
    um->players[um->numPlayers].score = 0;

    // Increment number of players
    um->numPlayers++;

    // Code to add user to the system
    FILE* file = fopen("usernames.txt", "a");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s\n", um->players[um->numPlayers - 1].username); // Write username to file
    fclose(file);

    printf("User %s added successfully\n", um->players[um->numPlayers - 1].username);
}

void saveUsersToFile(const char* filename, const USER_MANAGER* um) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < um->numPlayers; i++) {
        fprintf(file, "Username: %s\nScore: %d\n", um->players[i].username, um->players[i].score);
    }

    fclose(file);
}

// Rename an existing user
void renameUser(USER_MANAGER* um, const char* oldUsername, const char* newUsername) {
    int found = 0;
    for (int i = 0; i < um->numPlayers; i++) {
        if (strcmp(um->players[i].username, oldUsername) == 0) {
            strcpy(um->players[i].username, newUsername);
            found = 1;
            break;
        }
    }

    if (found) {
        printf("User %s renamed to %s successfully.\n", oldUsername, newUsername);
    }
    else {
        printf("User %s not found.\n", oldUsername);
    }
}

// Delete a user
void deleteUser() {
    char username[100];
    printf("Enter username to delete: ");
    scanf("%s", username);
    // Code to delete user
    printf("User %s deleted successfully.\n", username);
}

// Delete all users
void deleteAllUsers() {
    // Code to delete all users
    printf("All users deleted successfully.\n");
}

// Display all users
void displayAllUsers(USER_MANAGER* um) {

    system("cls");
    
    FILE* file = fopen("usernames.txt", "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    char username[100];
    printf("\n\t\tDisplaying all users:\n");
    printf("**************************************************\n");
    while (fscanf(file, "%99s", username) == 1) {
        printf("\t\t%s\n", username);
    }
    
    /*printf("Displaying all users:\n");
    for (int i = 0; i < um->numPlayers; i++) {
        printf("%s\n", um->players[i].username);
    }*/

    fclose(file);
    printf("**************************************************\n");
    printf("Press any key to return to previous menu...\n>>> ");
    getchar();
    getchar();
}

// Return value is negative if first username comes before the other
// Return value is positive if first username comes after the other 
// Return value is zero if usernames are the same

// Two arguments, first is key, socond one is pointer to element in array
static int comparePlayer(const void* pkey, const void* pelem) {
    return strcmp(((const USER*)pkey)->username, ((const USER*)pelem)->username);
}

// Function to pick a user using bsearch

void pickUser(const USER* players, int numPlayers, char* username) {
   
    printf("Enter the username to start the game with\n>>> ");
    scanf("%99s", username);

    USER key;
    strcpy(&key.username, username);

    // bsearch performs a binary search on a sorted array of elements to find desired element

    // Searches the given 'key' in the array pointed to by 'players' (which is formed by 'numPlayer' elements, each of size bytes), 
    // and returns a void* pointer to a matching element, if found.
    
    // To perform the search, the function performs a series of calls to 'comparePlayer' with key as 
    // first argument and elements of the array pointed to by 'player' as second argument.
    USER* found = NULL;
    found = bsearch(&key, players, numPlayers, sizeof(USER), comparePlayer);

    if (found != NULL) {
        printf("Starting game for user %s...\n", username);
    }
    else {
        printf("User %s not found...\n", username);
        username[0] = '\0';
    }
}




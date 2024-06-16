#pragma once

#define MAX_PLAYERS 100
#define MAX_USERNAME_LENGTH 100

typedef struct user {
    char username[MAX_USERNAME_LENGTH];
    int score;
}USER;

typedef struct userMenager{
    USER players[MAX_PLAYERS];
    int numPlayers;
}USER_MANAGER;

void initPlayerManager(USER_MANAGER* um);

void addUser(USER_MANAGER* um);
void renameUser();
void deleteUser();
void deleteAllUsers();
void displayAllUsers();
static int comparePlayer(const void* a, const void* b);
void pickUser(const USER* players, int numPlayers);
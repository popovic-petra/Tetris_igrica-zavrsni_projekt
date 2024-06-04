#pragma once

typedef struct player {
    char username[100];
    int score;
}PLAYER;


int sizeOfFile(const char* prompt);
void rules();
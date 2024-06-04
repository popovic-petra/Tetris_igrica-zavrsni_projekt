#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include "menu.h"
#include "tetris.h"
#include "user.h"


void menuDisplay() {
    //printf("\n\n\n");
    printf("\n*************** TETRIS Version 1.0 ***************");
    printf("\n\n\tCreated By: P. Popovic, SR-1.god");
    printf("\n\n");
    printf("\n\t\t0. Start new game\n");
    printf("\n\t\t1. Tetris rules\n");
    printf("\n\t\t2. View highscores\n");
    printf("\n\t\t3. Exit\n");
    printf("\n\n");
    printf("**************************************************\n");
    printf("Enter your choice\n>>> ");
}

MENU_OPTION getMenuChoice() {
    int choice;
    scanf("%d", &choice);
    return (MENU_OPTION)choice;
}

void menuReturn(void) {
    printf("\n");
    printf("Enter 0 to go back to main menu\n>>> ");
    printf("\n");
    int option;
    do {
        if (scanf("%d", &option) != 1) { // Check if input is not an integer
            printf("Invalid input. Please enter an integer: ");
            while (getchar() != '\n'); // Clear input buffer
        }
    } while (option != 0);
    system("cls");
    menuDisplay();
}

void game() {
    menuDisplay();
    int choice = getMenuChoice();

    switch (choice) {
    case START:
        system("cls");
        tetris();
        menuReturn();
        break;
    case RULES:
        system("cls");
        rules();
        break;
    case HIGHSCORE:
        break;
    case EXIT:
        break;
    }
}



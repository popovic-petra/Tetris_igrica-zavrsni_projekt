#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include "menu.h"
#include "score.h"
#include "tetris.h"

static void mainMenu() {
    printf("\n*************** TETRIS Version 1.0 ***************");
    printf("\n\n\tCreated By: P. Popovic, SR-1.god");
    printf("\n\n");

    printf("\n\t\t0. Start new game\n");
    printf("\n\t\t1. Tetris rules\n");
    printf("\n\t\t2. View highscores\n");
    printf("\n\t\t3. Exit\n");

    printf("\n\n");
    printf("**************************************************\n");
}

static void highscoreMenu() {
    printf("\n*************** TETRIS Version 1.0 ***************");
    printf("\n\n\tCreated By: P. Popovic, SR-1.god");
    printf("\n\n");

    printf("\n\t0. View highscores in ascending order\n");
    printf("\n\t1. View highscores in descending order\n");
    printf("\n\t2. Search highscores\n");
    printf("\n\t3. Delete all highscores\n");
    printf("\n\t4. Back to main menu\n");

    printf("\n\n");
    printf("**************************************************\n");
}


void displayMainMenu() {

    int showMainMenu = 1;
    
    while (showMainMenu) {
        system("cls");
        mainMenu();

        int choice = getMainMenuOption(EXIT);

        switch (choice) {
        case START:
            system("cls");
            // TODO unesi username i zapocni igru
            break;
        case RULES:
            system("cls");
            displayRules();
            break;
        case HIGHSCORE:
            system("cls");
            displayHighscoreMenu();
            break;
        case EXIT:
            showMainMenu = 0;
            break;
        }
    }
}

void displayHighscoreMenu() {
    
    int showHighscoreMenu = 1;

    while (showHighscoreMenu) {
        
        highscoreMenu();
        int choice = getHighscoreMenuOption(BACK);

        switch (choice) {
        case ASCENDING:
            //displayScoresAscending();
            break;
        case DESCENDING:
            //displayScoresDescending();
            break;
        case SEARCH:
            //searchHighscores();
            break;
        case DEL:
            //TODO izbrisi sve scores, prompt y/n
            //deleteHighscores();
            break;
        case BACK:
            showHighscoreMenu = 0;
            break;
        }
    }
}

int getMenuChoice(int maxOption) {
    int choice;
    do {
        printf("Enter your choice\n>>> ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter an integer.\n");
            while (getchar() != '\n');
        }
        if (choice < 0 || choice > maxOption) {
            printf("Choice out of range. Try again.\n");
        }
    } while (choice < 0 || choice > maxOption);

    return choice;
}


MENU_MAIN_OPTION getMainMenuOption() {
    return (MENU_MAIN_OPTION)getMenuChoice(EXIT);
}

MENU_HIGHSCORE_OPTION getHighscoreMenuOption() {
    return (MENU_HIGHSCORE_OPTION)getMenuChoice(BACK);
}


void displayRules() {

    FILE* fp = NULL;
    fp = fopen("rules.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    /*int d = sizeOfFile("rules.txt");
    printf("%d", d);*/

    char r[1000] = { '\0' };

    while (fgets(r, 1000, fp)) {
        printf("%s", r);
    }
    fclose(fp);

    printf("\nPress any key to return to previous menu...\n");
    getchar();
    getchar();

}

int sizeOfFile(const char* prompt) {
    FILE* f = fopen(prompt, "r");

    if (f == NULL) {
        fprintf(stderr, "Failed to open file\n");
        exit(EXIT_FAILURE);
    }

    fseek(f, 0, SEEK_END);
    //printf("%ld", ftell(f));

    int d = ftell(f);

    fclose(f);
    f = NULL;

    return d;
}

void setConsoleSize(int width, int height) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Postavljanje veličine buffer-a konzole
    COORD bufferSize = { width, height };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    // Postavljanje veličine prozora konzole
    SMALL_RECT windowSize = { 0, 0, width - 1, height - 1 };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

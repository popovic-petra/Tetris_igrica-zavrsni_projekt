#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include "menu.h"
#include "user.h"
#include "score.h"
#include "tetris.h"

static void mainMenu() {
    printf("\n*************** TETRIS Version 1.0 ***************");
    printf("\n\n\tCreated By: P. Popovic, SR-1.god");
    printf("\n\n");

    printf("\n\t\t0. Start new game\n");
    printf("\n\t\t1. Manage user\n");
    printf("\n\t\t2. Tetris rules\n");
    printf("\n\t\t3. View highscores\n");
    printf("\n\t\t4. Exit\n");

    printf("\n\n");
    printf("**************************************************\n");
}

static void startGameMenu() {
    printf("\n*************** TETRIS Version 1.0 ***************");
    printf("\n\n\tCreated By: P. Popovic, SR-1.god");
    printf("\n\n");

    printf("\n\t\t0. Select existing user\n");
    printf("\n\t\t1. Add new user\n");
    printf("\n\t\t2. Back to main menu\n");

    printf("\n\n");
    printf("**************************************************\n");
}

static void userMenu() {
    printf("\n*************** TETRIS Version 1.0 ***************");
    printf("\n\n\tCreated By: P. Popovic, SR-1.god");
    printf("\n\n");

    printf("\n\t\t0. Show all users\n");
    printf("\n\t\t1. Add new user\n");
    printf("\n\t\t2. Rename user\n");
    printf("\n\t\t3. Delete user\n");
    printf("\n\t\t4. Delete all users\n");
    printf("\n\t\t5. Back to main menu\n");

    printf("\n\n");
    printf("**************************************************\n");
}

static void highscoreMenu() {
    printf("\n*************** TETRIS Version 1.0 ***************");
    printf("\n\n\tCreated By: P. Popovic, SR-1.god");
    printf("\n\n");

    printf("\n\t0. View highscores in ascending order\n");
    printf("\n\t1. View highscores in descending order\n");
    printf("\n\t2. Search highscore\n");
    printf("\n\t3. Back to main menu\n");

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
            displayStartGameMenu();
            break;
        case MENAGE_USER:
            system("cls");
            displayUserMenu();
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

void displayStartGameMenu() {
    
    int showStartMenu = 1;
    
    while (showStartMenu) {
        system("cls");
        startGameMenu();

        int choice = getStartMenuOption(BACK_MAIN_MENU);
        char username[MAX_USERNAME_LENGTH] = { '\0' };
        
        USER_MANAGER um = { .numPlayers = 0 };
        initPlayerManager(&um);

        switch (choice) {

        case EXISTING:
            system("cls");
            if (um.numPlayers == 0) {
                printf("No users available. Please add a user first.\n");
                break;
            }
          
            printf("Select user to start Tetris:\n");
            for (int i = 0; i < um.numPlayers; i++) {
                printf("%d. %s\n", i + 1, um.players[i].username);
            }

            int userIndex;
            printf("Enter user number: ");
            scanf("%d", &userIndex);
            getchar(); // Consume newline character left in the input buffer

            if (userIndex < 1 || userIndex > um.numPlayers) {
                printf("Invalid user number.\n");
            }
            else {
                runTetrisForUser(&um, userIndex - 1);
            }
            //if (um.numPlayers == 0) {
            //    printf("No users available. Please add a user first.\n");
            //    break;
            //}
            ////displayAllUsers(&um);     TODO mora biti nova funkcija jer ova samo prikazuje usere
            //pickUser(um.players, um.numPlayers, username);
            //if (username[0] != '\0') {
            //    tetrisRun(username, BOARD_WIDTH, BOARD_HEIGHT, 0);
            //}
            break;

        case NEW:
            system("cls");
            addUser(&um);
            tetrisRun(um.players->username, BOARD_WIDTH, BOARD_HEIGHT, 0);
            break;

        case BACK_MAIN_MENU:
            showStartMenu = 0;
            break;

        default:
            printf("Invalid choice.\n");
        }
    }
    
}

void displayUserMenu() {
    int showUserMenu = 1;

    while (showUserMenu) {
        system("cls");
        userMenu();

        int choice = getUserMenuOption(BACK_MAIN);
        
        USER_MANAGER um;
        initPlayerManager(&um);

        switch (choice) {
        case ALL_USER:
            system("cls");
            displayAllUsers(&um);
            break;
        case ADD:
            system("cls");
            addUser(&um);
            break;
        case RENAME:
            renameUser();
            break;
        case DEL:
            deleteUser();
            break;
        case DEL_ALL:
            deleteAllUsers();
            break;
        case BACK_MAIN:
            showUserMenu = 0;
            break;
        }
    }
}

void displayHighscoreMenu() {
    
    int showHighscoreMenu = 1;

    while (showHighscoreMenu) {
        
        highscoreMenu();
        int choice = getHighscoreMenuOption(BACK_MENU);

        switch (choice) {
        case ASCENDING:
            displayScoresAscending();
            break;
        case DESCENDING:
            displayScoresDescending();
            break;
        case SEARCH:
            searchHighscores();
            break;
        case BACK_MENU:
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

MENU_START_OPTION getStartMenuOption() {
    return (MENU_START_OPTION)getMenuChoice(BACK_MAIN_MENU);
}

MENU_EXISTING_OPTION getExistingMenuOption() {
    return (MENU_EXISTING_OPTION)getMenuChoice(BACK_START);
}

MENU_USER_OPTION getUserMenuOption() {
    return (MENU_USER_OPTION)getMenuChoice(BACK_MAIN);
}

MENU_HIGHSCORE_OPTION getHighscoreMenuOption() {
    return (MENU_HIGHSCORE_OPTION)getMenuChoice(BACK_MENU);
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

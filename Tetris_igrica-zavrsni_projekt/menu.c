#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include "menu.h"
#include "score.h"
#include "tetris.h"

static void printStars(int count) {
    for (int i = 0; i < count; i++) {
        printf("*");
    }
    printf("\n");
}

static void mainMenu() {
    printStars(51);
    printf("*                TETRIS Version 1.0               *\n");
    printStars(51);
    printf("\n\tCreated By: P. Popovic, SR-1.god");
    printf("\n\n");

    printf("\n\t\t0. Start new game\n");
    printf("\n\t\t1. Tetris rules\n");
    printf("\n\t\t2. View highscores\n");
    printf("\n\t\t3. Exit\n");

    printf("\n\n");
    printStars(51);
}

static void highscoreMenu() {
    printStars(51);
    printf("*                TETRIS Version 1.0               *\n");
    printStars(51);
    printf("\n\tCreated By: P. Popovic, SR-1.god");
    printf("\n\n");

    printf("\n\t0. View highscores\n");
    printf("\n\t1. Sort highscores in ascending order\n");
    printf("\n\t2. Sort highscores in descending order\n");
    printf("\n\t3. Search highscores\n");
    printf("\n\t4. Delete all highscores\n");
    printf("\n\t5. Back to main menu\n");

    printf("\n\n");
    printStars(51);
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
            tetrisRun(BOARD_WIDTH, BOARD_HEIGHT, 0);
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
        system("cls");
        highscoreMenu();
        int choice = getHighscoreMenuOption(BACK);

        USER users[MAX_PLAYERS] = { '\0' };
        int count = loadScore(users, MAX_PLAYERS);

        char check;

        switch (choice) {
        case VIEW:
            system("cls");
            printStars(51);
            printf("*                   HIGH SCORES                   *\n");
            printStars(51);
            printf("\tUSERNAME\t\t\SCORE\n\n");
            
            for (int i = 0; i < count; i++) {
               printf("\t%-16s\t%d\n", users[i].username, users[i].score);
            }
            printf("\nPress ENTER to return to previous menu...\n");
            getchar();
            getchar();
            break;
        case ASCENDING:
            system("cls");
            printStars(51);
            printf("*                 SORTED ASCENDING                *\n");
            printStars(51);
            qsort(users, count, sizeof(USER), compareAsc);
            printf("\tUSERNAME\t\t\SCORE\n\n");
            for (int i = 0; i < count; i++) {
                printf("\t%-16s\t%d\n", users[i].username, users[i].score);
            }
            printf("\nPress ENTER to return to previous menu...\n");
            getchar();
            getchar();
            break;

        case DESCENDING:
            system("cls");
            printStars(51);
            printf("*                 SORTED DESCENDING               *\n");
            printStars(51);
            qsort(users, count, sizeof(USER), compareDesc);
            printf("\tUSERNAME\t\t\SCORE\n\n");
            for (int i = 0; i < count; i++) {
                printf("\t%-16s\t%d\n", users[i].username, users[i].score);
            }
            printf("\nPress ENTER to return to previous menu...\n");
            getchar();
            getchar();

        case SEARCH:
            system("cls");
            qsort(users, count, sizeof(USER), compareUsernames);
            
            char searchName[MAX_USERNAME_LENGTH + 1];
            printf("Enter username to search\n>>> ");
            getchar();
            fgets(searchName, MAX_USERNAME_LENGTH, stdin);
            removeNewline(searchName);

            USER key;
            strncpy(key.username, searchName, MAX_USERNAME_LENGTH);

            USER* found = bsearch(&key, users, count, sizeof(USER), compareUsernames);
            
            if (found) {
                system("cls");
                printStars(51);
                printf("*                 SEARCH RESULT                   *\n");
                printStars(51);
                printf("Found user: %s with score: %d\n", found->username, found->score);
                printf("\nPress ENTER to return to previous menu...\n");
                getchar();
            }
            else {
                printStars(51);
                printf("\nUser %s not found.\n", searchName);
                printStars(51);
                printf("\nPress ENTER to return to previous menu...\n");
                getchar();
                getchar();
            }

            break;
        case DEL:
            system("cls");
            check = doubleCheck();
            getchar();
            
            if (check == 'y' || check == 'Y') {
                deleteHighscores();
                printf("File was successfully deleted.\n");
            }
            else if (check == 'n' || check == 'N') {
                printf("File clearing was successfully canceled.\n");
            }
            else {
                printf("Invalid input. File clearing canceled.\n");
            }
            printf("\nPress ENTER to return to previous menu...\n");
            getchar();              
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

    char r[1000] = { '\0' };

    while (fgets(r, 1000, fp)) {
        printf("%s", r);
    }
    fclose(fp);

    int len = sizeOfFile("rules.txt");
    printf("Total size of rules.txt = %d bytes\n", len);

    printf("\nPress any key to return to previous menu...\n");
    getchar();
    getchar();

}

int sizeOfFile(const char* prompt) {
    FILE* fp = NULL;
    int len = 0;

    fp = fopen(prompt, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open file\n");
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0, SEEK_END);
    len = ftell(fp);
    fclose(fp);
    fp = NULL;

    return len;
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
